

//Pompé quasi intégral de POV
//A RECODER ULTERIEUREMENT EN OBJET
#include "TextChar.h"
#include "TraceService.h"
#include "FormatGlyph.h"
#include "FontFile.h"
#include "Ray.h"
#include <afxmt.h>


CMutex	TextCharMutex(FALSE,"TEXTCHARMUTEX");


CTextChar::CTextChar()
{
	m_Depth=0.3;
	m_DistanceTolerance=1e-6;
	m_NbRef=0;
}


CTextChar::~CTextChar()
{
}


void	CTextChar::ProcessCharacter(unsigned char search_char,CTextFont &font,unsigned int &glyph_index)
{
  CGlyph	*pglyph;
  /* See if we have already processed this glyph */
  for (pglyph = font.GetCurrentFont().glyphs; pglyph != NULL; pglyph = pglyph->next)
  {
    if (pglyph->c == search_char)
    {
      /* Found it, no need to do any more work */
      glyph_index = pglyph->glyph_index;
	  m_Glyph=*pglyph;

      return;
    }
  }

  glyph_index = ProcessCharMap(font.GetCurrentFont(), search_char);

  /*if (glyph_index == 0)
    _TRACE_WARNING(_STR("Character %d (0x%X) not found in %s", (BYTE)search_char,
            search_char, font.GetCurrentFont().filename));*/

  /* See if we have already processed this glyph (using the glyph index) */
  for (pglyph = font.GetCurrentFont().glyphs; pglyph != NULL; pglyph = pglyph->next)
  {
    if (pglyph->glyph_index == glyph_index)
    {
      /* Found it, no need to do any more work */
      glyph_index = pglyph->glyph_index;
	  m_Glyph=*pglyph;

      return;
    }
  }

  ExtractGlyphInfo(font.GetCurrentFont(), glyph_index, search_char,m_Glyph);

  /* Add this glyph to the ones we already know about */
  
  m_Glyph.next = font.GetCurrentFont().glyphs;
  font.GetCurrentFont().glyphs = &m_Glyph;
}



unsigned short CTextChar::ProcessCharMap(CFontFileInfo &ffile, unsigned int search_char)
{
	long old_table_offset;
	long entry_offset;
	C_sfnt_platformEntry cmapEntry;
	C_sfnt_mappingTable encodingTable;
	int i, j, table_count;

	/* Move to the start of the character map, skipping the 2 byte version */
	ffile.fp.Seek (ffile.cmap_table_offset + 2,CFile::begin) ;

	table_count = CFontFile::readUSHORT(ffile.fp);

	/*
	 * Search the tables until we find the glyph index for the search character.
	 * Just return the first one we find...
	 */

	for(j = 0; j <= 3; j++)
	{
		for (i = 0; i < table_count; i++)
		{
			cmapEntry.platformID = CFontFile::readUSHORT(ffile.fp);
			cmapEntry.specificID = CFontFile::readUSHORT(ffile.fp);
			cmapEntry.offset     = CFontFile::readULONG(ffile.fp);

			/*
			 * Check if this is the encoding table we want to use.
			 * The search is done according to user preference.
			 */
			if ( ffile.platformID[j] != cmapEntry.platformID ) /* [JAC 01/99] */
			{
				continue;
			}

			entry_offset = cmapEntry.offset;

			old_table_offset = ffile.fp.GetPosition(); /* Save the current position */

			ffile.fp.Seek(ffile.cmap_table_offset + entry_offset,CFile::begin) ;

			encodingTable.format = CFontFile::readUSHORT(ffile.fp);
			encodingTable.length = CFontFile::readUSHORT(ffile.fp);
			encodingTable.version = CFontFile::readUSHORT(ffile.fp);

			if (encodingTable.format == 0)
			{
				/*
				 * Translation is simple - add 'entry_char' to the start of the
				 * table and grab what's there.
				 */
				return(CFormatGlyph::ProcessFormat0Glyph(ffile, search_char));
			}
/*			#if 0  /* Want to get the rest of these working first */
/*			else if (encodingTable.format == 2)
			{
				/* Used for multi-byte character encoding (Chinese, Japanese, etc) */
/*				#ifdef TTF_DEBUG
				Debug_Info("High-byte index mapping\n");
				#endif

				return(ProcessFormat2Glyph(ffile, search_char));
			}
			#endif*/
			else if (encodingTable.format == 4)
			{
				/* Microsoft UGL encoding */

				return(CFormatGlyph::ProcessFormat4Glyph(ffile, search_char));
			}
			else if (encodingTable.format == 6)
			{

				return(CFormatGlyph::ProcessFormat6Glyph(ffile, search_char));
			}
			else
				_TRACE_ERROR("Format non supporté");

			/* Go to the next table entry if we didn't find a match */
			ffile.fp.Seek (old_table_offset,CFile::begin) ;
		}
	}

	/*
	 * No character mapping was found - very odd, we should really have had the
	 * character in at least one table.  Perhaps getting here means we didn't
	 * have any character mapping tables.  '0' means no mapping.
	 */
	
	return 0;
}


void CTextChar::ExtractGlyphInfo(CFontFileInfo &ffile, unsigned int glyph_index, unsigned int c,CGlyph &glyph)
{
  CGlyphOutline ttglyph;

  CFormatGlyph::ExtractGlyphOutline(ffile, glyph_index, c,ttglyph);

  /*
   * Convert the glyph outline information from TrueType layout into a more
   * easily processed format
   */

  CFormatGlyph::ConvertOutlineToGlyph(ffile, ttglyph,glyph);
  glyph.c = c;
  glyph.glyph_index = glyph_index;
  glyph.myMetrics = ttglyph.myMetrics;
    
}



///////////////////////////////////////////////////////////////
//*************************************************************
//VIRTUAL MEMBERS
//*************************************************************

/////////////////////////////////////////
//Calcul de l'intersection d'un vecteur avec un caractère
/*
 * Solving for a linear sweep of a non-linear curve can be performed by
 * projecting the ray onto the x-y plane, giving a parametric equation for the
 * ray as:
 * 
 * x = x0 + x1 t, y = y0 + y1 t
 * 
 * Eliminating t from the above gives the implicit equation:
 * 
 * y1 x - x1 y - (x0 y1 - y0 x1) = 0.
 * 
 * Substituting a parametric equation for x and y gives:
 * 
 * y1 x(s) - x1 y(s) - (x0 y1 - y0 x1) = 0.
 * 
 * which can be written as
 * 
 * a x(s) + b y(s) + c = 0,
 * 
 * where a = y1, b = -x1, c = (y0 x1 - x0 y1).
 * 
 * For piecewise quadratics, the parametric equations will have the forms:
 * 
 * x(s) = (1-s)^2 P0(x) + 2 s (1 - s) P1(x) + s^2 P2(x) y(s) = (1-s)^2 P0(y) + 2 s
 * (1 - s) P1(y) + s^2 P2(y)
 * 
 * where P0 is the first defining vertex of the spline, P1 is the second, P2 is
 * the third.  Using the substitutions:
 * 
 * xt2 = x0 - 2 x1 + x2, xt1 = 2 * (x1 - x0), xt0 = x0; yt2 = y0 - 2 y1 + y2, yt1
 * = 2 * (y1 - y0), yt0 = y0;
 * 
 * the equations can be written as:
 * 
 * x(s) = xt2 s^2 + xt1 s + xt0, y(s) = yt2 s^2 + yt1 s + yt0.
 * 
 * Substituting and multiplying out gives the following equation in s:
 * 
 * s^2 * (a*xt2 + b*yt2) + s   * (a*xt1 + b*yt1) + c + a*xt0 + b*yt0
 * 
 * This is then solved using the quadratic formula.  Any solutions of s that are
 * between 0 and 1 (inclusive) are valid solutions.
 */

bool	CTextChar::Intersection(CRay &Ray)
{ 
  //_FTRACE("Intersection","CTextChar");
  CRay NewRay;
  NewRay.SetRayClear(Ray);

  if(GetExistTrans())
  {
	NewRay.SetOrigin(m_Trans.InvTrans(Ray.GetOrigin()));
	NewRay.SetDirect(m_Trans.InvTrans(Ray.GetDirect()));
  }

  /*
   * First thing to do is to get any hits at z = 0 and z = 1 (which are the
   * bottom and top surfaces of the glyph.
   */
  double t0,t1;
  bool	 Flag=false;
  double z=0;
  double t=0;

  GetZeroOneHits(m_Glyph, NewRay,m_Depth, t0, t1);

  if (t0 > 0.0)
  {
	//_TRACE_INFO("intersect ok","CTextChar");
	AddIntersect(Ray,t0,GLYPH_SIDE_0);
	Flag = true;
  }

  if (t1 > 0.0)
  {
	//_TRACE_INFO("intersect ok","CTextChar");
	AddIntersect(Ray,t1,GLYPH_SIDE_1);
	Flag = true;
  }

  /* Simple test to see if we can just toss this ray */
  double dirflag;
  if (fabs(NewRay.GetDirect().GetX()) < EPSILON)
  {
    if (fabs(NewRay.GetDirect().GetY()) < EPSILON)
    {
      /*
       * This means the ray is moving parallel to the walls of the sweep
       * surface
       */
      return Flag;
    }
    else
    {
	  //_TRACE_WARNING("Rayon parallèle sur X");
      dirflag = 0;
    }
  }
  else
  {
	//_TRACE_WARNING("Rayon parallèle sur Y");
    dirflag = 1;
  }

  /*
   * Now walk through the glyph, looking for places where the ray hits the
   * walls
   */
  
  double a = NewRay.GetDirect().GetY();
  double b = -NewRay.GetDirect().GetX();
  double c = (NewRay.GetOrigin().GetY() * NewRay.GetDirect().GetX() 
	         - NewRay.GetOrigin().GetX() * NewRay.GetDirect().GetY());

  int n = m_Glyph.header.numContours;
  
  CContour *contour=m_Glyph.contours;


  for (int i = 0; i < n; i++, contour++)
  {
    double* xv = contour->x;
    double* yv = contour->y;
    char* fv = contour->flags;
    double x0 = xv[0];
    double y0 = yv[0];
    int m = contour->count;
  
    for (int j = 1; j <= m; j++)
    {
      double x1 = xv[j];
      double y1 = yv[j];
	  double x2,y2;
    
      if (fv[j] & ONCURVE)
      {
        /* Straight line */
        double d0 = (x1 - x0);
        double d1 = (y1 - y0);

        t0 = d1 * NewRay.GetDirect().GetX() - d0 * NewRay.GetDirect().GetY();
        
        if (fabs(t0) < EPSILON)
          /* No possible intersection */
          goto end_line_test;
        
        t = (NewRay.GetDirect().GetX() * (NewRay.GetOrigin().GetY() - y0) - 
			NewRay.GetDirect().GetY() * (NewRay.GetOrigin().GetX() - x0)) / t0;
        
        if (t < 0.0 || t > 1.0)
          goto end_line_test;
        
        if (dirflag)
          t = ((x0 + t * d0) - NewRay.GetOrigin().GetX()) / NewRay.GetDirect().GetX();
        else
          t = ((y0 + t * d1) - NewRay.GetOrigin().GetY()) / NewRay.GetDirect().GetY();
        
        z = NewRay.GetOrigin().GetZ() + t * NewRay.GetDirect().GetZ();
        
        if (z >= 0 && z <= m_Depth)
        {
		//_TRACE_INFO("intersect ok","CTextChar");

		  CVector vNormal(d1,-d0,0.0);
		  if(m_Trans.GetExist())
		  {
			vNormal=m_Trans.TransNormal(vNormal);
		  }
		  AddIntersect(Ray,t,vNormal);
          Flag = true;
        }
      end_line_test:
        x0 = x1;
        y0 = y1;
      }
      else
      {
        if (j == m)
        {
          x2 = xv[0];
          y2 = yv[0];
        }
        else
        {
          x2 = xv[j + 1];
          y2 = yv[j + 1];
          
          if (!(fv[j + 1] & ONCURVE))
          {

            /*
             * Parabola with far end DBLing - readjust the far end so that it
             * is on the curve.  (In the correct place too.)
             */
            
            x2 = 0.5 * (x1 + x2);
            y2 = 0.5 * (y1 + y2);
          }
        }

        /* Make the interpolating quadrics */
        
        double xt2 = x0 - 2.0 * x1 + x2;
        double xt1 = 2.0 * (x1 - x0);
        double xt0 = x0;
        double yt2 = y0 - 2.0 * y1 + y2;
        double yt1 = 2.0 * (y1 - y0);
        double yt0 = y0;

		double C[3];
        C[0] = a * xt2 + b * yt2;
        C[1] = a * xt1 + b * yt1;
        C[2] = a * xt0 + b * yt0 + c;

		double S[2];	//2 solutions possible
        int k = solve_quad(C, S, 0.0, 1.0);	//on utilise la méthode locale -> A REVOIR

        for (int l = 0; l < k; l++)
        {
          if (dirflag)
            t = ((S[l] * S[l] * xt2 + S[l] * xt1 + xt0) - NewRay.GetOrigin().GetX()) / NewRay.GetDirect().GetX();
          else
            t = ((S[l] * S[l] * yt2 + S[l] * yt1 + yt0) - NewRay.GetOrigin().GetY()) / NewRay.GetDirect().GetY();

          /*
           * If the intersection with this wall is between 0 and glyph_depth
           * along the z-axis, then it is a valid hit.
           */

		  z = NewRay.GetOrigin().GetZ() + t * NewRay.GetDirect().GetZ();
                    
          if (z >= 0 && z <= m_Depth)
          {
			  	//_TRACE_INFO("intersect ok","CTextChar");

			CVector vNormal(2.0 * yt2 * S[l] + yt1, -2.0 * xt2 * S[l] - xt1, 0.0);
			if(m_Trans.GetExist())
			{
				vNormal=m_Trans.TransNormal(vNormal);
			}
			AddIntersect(Ray,t,vNormal);
            Flag = true;
          }
        }
        
        x0 = x2;
        y0 = y2;
      }
    }
  }
  
  return Flag;
}

bool CTextChar::AddIntersect(CRay &Ray,double Distance)
{
	return false;

}

bool	CTextChar::AddIntersect(CRay &Ray,double Distance,GLYPH_SIDE_ENUM Side)
{
	CBaseIntersection *pIntersection=new CBaseIntersection;

	CCoord	&ImpactPt=Ray.GetOrigin()+Ray.GetDirect()*Distance;
	pIntersection->SetDistance(Distance,ImpactPt);
	pIntersection->SetObjet(this);


    if (Distance>0)
      pIntersection->SetMilieu(m_pMatiere->GetMilieu2());
    else
      pIntersection->SetMilieu(m_pMatiere->GetMilieu1());

	pIntersection->SetMatiere(m_pMatiere);

	CVector vNormal=Normal(Side);

    pIntersection->SetNormal(vNormal);

    // Puis on la rajoute dans la liste des intersections
    return(Ray.AddIntersect(pIntersection));
}

bool	CTextChar::AddIntersect(CRay &Ray,double Distance,CVector &vNormal)
{
	CBaseIntersection *pIntersection=new CBaseIntersection;

	CCoord	&ImpactPt=Ray.GetOrigin()+Ray.GetDirect()*Distance;
	pIntersection->SetDistance(Distance,ImpactPt);
	pIntersection->SetObjet(this);


    if (Distance>0)
      pIntersection->SetMilieu(m_pMatiere->GetMilieu2());
    else
      pIntersection->SetMilieu(m_pMatiere->GetMilieu1());

	pIntersection->SetMatiere(m_pMatiere);

    pIntersection->SetNormal(vNormal);

    // Puis on la rajoute dans la liste des intersections
    return(Ray.AddIntersect(pIntersection));

}


//////////////////////////////////////////
//Normal au plan ---> coefficients directeurs sans la constante
CVector	CTextChar::Normal(const CCoord &coord)
{
	return CVector(0,0,0);
}

CVector	CTextChar::Normal(GLYPH_SIDE_ENUM Side)
{
	CVector vNormal;
	switch(Side)
	{
		case GLYPH_SIDE_0:
			vNormal.Set(0,0,-1);
			break;
		case GLYPH_SIDE_1:
			vNormal.Set(0,0,1);
			break;
		default:
			return CVector(0,0,0);
	}

	if(m_Trans.GetExist())
	{
		vNormal=m_Trans.TransNormal(vNormal);
	}

	return vNormal;
}


void	CTextChar::GetOutputStream(ostream &o)
{
}

void CTextChar::ForceEqual(CBaseGeometry &Origin)
{
	CTextChar *pTrueOrigin=static_cast<CTextChar*>(&Origin);
	if(pTrueOrigin!=NULL)
	{
		*this=*pTrueOrigin;
	}
}

CBaseGeometry*	CTextChar::Instantiate()
{
	return new CTextChar;
}

CTextChar&	CTextChar::operator=(const CTextChar &Param)
{
	m_Glyph=Param.m_Glyph;

	return(*this);
}

#define COEFF_LIMIT 1.0e-20
int CTextChar::solve_quad(double *x, double *y, double mindist, double maxdist)
{
  double d, t, a, b, c, q;

  a = x[0];
  b = -x[1];
  c = x[2];
  
  if (fabs(a) < COEFF_LIMIT)
  {
    if (fabs(b) < COEFF_LIMIT)
      return 0;
  
    q = c / b;
  
    if (q >= mindist && q <= maxdist)
    {
      y[0] = q;
      return 1;
    }
    else
      return 0;
  }
  
  d = b * b - 4.0 * a * c;

  if (d < EPSILON)
    return 0;

  d = sqrt(d);
  t = 2.0 * a;
  q = (b + d) / t;
  
  if (q >= mindist && q <= maxdist)
  {
    y[0] = q;
    q = (b - d) / t;
    
    if (q >= mindist && q <= maxdist)
    {
      y[1] = q;
      return 2;
    }
    
    return 1;
  }
  
  q = (b - d) / t;
  
  if (q >= mindist && q <= maxdist)
  {
    y[0] = q;
    return 1;
  }
  
  return 0;
}

/*
 * Returns the distance to z = 0 in t0, and the distance to z = 1 in t1.
 * These distances are to the the bottom and top surfaces of the glyph.
 * The distances are set to -1 if there is no hit.
 */
void CTextChar::GetZeroOneHits(CGlyph &glyph, CRay& Ray, double glyph_depth, double &t0, double &t1)
{
  double x0, y0, t;

  t0 = -1.0;
  t1 = -1.0;

  /* Are we parallel to the x-y plane? */
  
  if (fabs(Ray.GetDirect().GetZ()) < EPSILON)
  {
    return;
  }

  /* Solve: P[Y] + t * D[Y] = 0 */
  
  t = -Ray.GetOrigin().GetZ() / Ray.GetDirect().GetZ();
  
  x0 = Ray.GetOrigin().GetX() + t * Ray.GetDirect().GetX();
  y0 = Ray.GetOrigin().GetY() + t * Ray.GetDirect().GetY();
  
  if (Inside_Glyph(x0, y0, glyph))
    t0 = t;

  /* Solve: P[Y] + t * D[Y] = glyph_depth */
  
  t += (glyph_depth / Ray.GetDirect().GetZ());
  
  x0 = Ray.GetOrigin().GetX() + t * Ray.GetDirect().GetX();
  y0 = Ray.GetOrigin().GetY() + t * Ray.GetDirect().GetY();
  
  if (Inside_Glyph(x0, y0, glyph))
    t1 = t;
}


int CTextChar::Inside_Glyph(double x, double y, CGlyph &glyph)
{
  int i, j, k, n, n1, crossings;
  int qi, ri, qj, rj;
  CContour *contour;
  double xt[3], yt[3], roots[2];
  double *xv, *yv;
  double x0, x1, x2, t;
  double y0, y1, y2;
  double m, b, xc;
  char *fv;

  crossings = 0;
  
  n = glyph.header.numContours;
  
  contour = glyph.contours;
  
  for (i = 0; i < n; i++)
  {
    xv = contour[i].x;
    yv = contour[i].y;
    fv = contour[i].flags;
    x0 = xv[0];
    y0 = yv[0];
    n1 = contour[i].count;
  
    for (j = 1; j <= n1; j++)
    {
      x1 = xv[j];
      y1 = yv[j];
      
      if (fv[j] & ONCURVE)
      {
        /* Straight line - first set up for the next */
        /* Now do the crossing test */
        
        qi = ri = qj = rj = 0;
        
        if (y0 == y1)
          goto end_line_test;
        
        /* if (fabs((y - y0) / (y1 - y0)) < EPSILON) goto end_line_test; */
        
        if (y0 < y)
          qi = 1;
        
        if (y1 < y)
          qj = 1;
        
        if (qi == qj)
          goto end_line_test;
        
        if (x0 > x)
          ri = 1;
        
        if (x1 > x)
          rj = 1;
        
        if (ri & rj)
        {
          crossings++;
          goto end_line_test;
        }
        
        if ((ri | rj) == 0)
          goto end_line_test;
        
        m = (y1 - y0) / (x1 - x0);
        b = (y1 - y) - m * (x1 - x);
        
        if ((b / m) < EPSILON)
        {
          crossings++;
        }
      
      end_line_test:
        x0 = x1;
        y0 = y1;
      }
      else
      {
        if (j == n1)
        {
          x2 = xv[0];
          y2 = yv[0];
        }
        else
        {
          x2 = xv[j + 1];
          y2 = yv[j + 1];
      
          if (!(fv[j + 1] & ONCURVE))
          {
            /*
             * Parabola with far end floating - readjust the far end so that it
             * is on the curve.
             */
            
            x2 = 0.5 * (x1 + x2);
            y2 = 0.5 * (y1 + y2);
          }
        }

        /* only test crossing when y is in the range */
        /* this should also help saving some computations */
        if (((y0 < y) && (y1 < y) && (y2 < y)) ||
            ((y0 > y) && (y1 > y) && (y2 > y)))
          goto end_curve_test;

        yt[0] = y0 - 2.0 * y1 + y2;
        yt[1] = 2.0 * (y1 - y0);
        yt[2] = y0 - y;
        
        k = solve_quad(yt, roots, 0.0, 1.0);

        for (ri = 0; ri < k;) {
          if (roots[ri] <= EPSILON) {
            /* if y actually is not in range, discard the root */
            if (((y <= y0) && (y < y1)) || ((y >= y0) && (y > y1))) {
              k--;
              if (k > ri)
                roots[ri] = roots[ri+1];
              continue;
            }
          }
         else if (roots[ri] >= (1.0 - EPSILON)) {
            /* if y actually is not in range, discard the root */
            if (((y < y2) && (y < y1)) || ((y > y2) && (y > y1))) {
              k--;
              if (k > ri)
                roots[ri] = roots[ri+1];
              continue;
            }
          }

          ri++;
        }
        
        if (k > 0)
        {
          xt[0] = x0 - 2.0 * x1 + x2;
          xt[1] = 2.0 * (x1 - x0);
          xt[2] = x0;
        
          t = roots[0];
          
          xc = (xt[0] * t + xt[1]) * t + xt[2];
          
          if (xc > x)
            crossings++;
          
          if (k > 1)
          {
            t = roots[1];
            xc = (xt[0] * t + xt[1]) * t + xt[2];
          
            if (xc > x)
              crossings++;
          }
        }

end_curve_test:
        
        x0 = x2;
        
        y0 = y2;
      }
    }
  }
  
  return (crossings & 1);
}

void	CTextChar::AddRef()	
{
	CSingleLock singleLock(&TextCharMutex);
	singleLock.Lock();  // Attempt to lock the shared resource

	m_NbRef++;

	singleLock.Unlock();
}
void	CTextChar::Release()
{
	CSingleLock singleLock(&TextCharMutex);
	singleLock.Lock();  // Attempt to lock the shared resource

	m_NbRef--;
	if(m_NbRef<=0) delete(this);

	singleLock.Unlock();
}

#define EXCHANGE(a,b) double c=b;b=a;a=c;

void	CTextChar::ComputeBoundingBox(CCoord &Min,CCoord &Max)
{
  double funit_size = 1.0 / (double)(m_Glyph.unitsPerEm);

  double xMin = (double)m_Glyph.header.xMin * funit_size;
  double yMin = (double)m_Glyph.header.yMin * funit_size;
  double zMin = -m_DistanceTolerance;

  double xMax = (double)m_Glyph.header.xMax * funit_size;
  double yMax = (double)m_Glyph.header.yMax * funit_size;
  double zMax = m_Depth + m_DistanceTolerance;


  Min=CCoord(xMin,yMin,zMin);
  Max=CCoord(xMax,yMax,zMax);

  Min=m_Trans.Trans(Min);
  Max=m_Trans.Trans(Max);

  for(int i=0;i<3;i++)
  {
	if(Min.m_Value[i]>Max.m_Value[i]) 
	{
		EXCHANGE(Min.m_Value[i],Max.m_Value[i]);
	}
  }
}

