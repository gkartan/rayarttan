#include "stdio.h"
#include "BaseGeometry.h"
#include "Cone.h"
#include "Ray.h"
#include "Constants.h"
#include "Macros.h"
#include "Power.h"
#include "TraceService.h"
#include "Sphere.h"

CCone::CCone()
{
	m_IsCylinder=false;
}

CCone::CCone(const CCoord &base,double baseRadius,
					 const CCoord &cap, double capRadius)
{
	m_Base=base;
	m_Cap=cap;
	m_Radius=baseRadius;
	m_CapRadius=capRadius;
	m_IsCylinder=false;

	InitTrans();
}

CCone::~CCone()
{
}

CCone&	CCone::operator=(CCone	&Origin)
{
	CCylinder::operator=(Origin);

	m_CapRadius=Origin.m_CapRadius;
	m_IsCylinder=Origin.m_IsCylinder;
	m_Dist=Origin.m_Dist;

	return (*this);
}

/////////////////////////////////////////
//Calcul de l'intersection d'un vecteur avec un cone
bool	CCone::Intersection(CRay &Ray)
{ 
	if(m_IsCylinder) 
	{
		return(CCylinder::Intersection(Ray));
	}

	double			Distance[4];
	INTERSECT_ENUM  TypeHit[4];

	///On met le rayon dans les coordonnées du cylindre
	CRay NewRay;
	NewRay.SetRayClear(Ray);
	double NewLength=1;


	if(GetExistTrans())
	{
		NewRay.SetOrigin(m_Trans.InvTrans(Ray.GetOrigin()));
		CVector	NewDirect(m_Trans.InvTrans(Ray.GetDirect()));
		NewLength=NewDirect.Length();
		NewRay.SetDirect(NewDirect);
	}


	//Init TypeHit
	for(int i=0;i<4;i++) TypeHit[i]=NO_INTERSECT;

	if(Intersection(NewRay,Distance,TypeHit))
	{
		for(i=0;i<4;i++)
		{
			if(TypeHit[i]!=NO_INTERSECT)
			{
				if(TypeHit[i]==SIDE_INTERSECT)
				{
					double z = NewRay.GetOrigin().GetZ() + Distance[i] * NewRay.GetDirect().GetZ();
					if(z>=m_Dist && z<=1.0)
					{
						AddIntersect(Ray,Distance[i]/NewLength,TypeHit[i]);
					}
				} else
					AddIntersect(Ray,Distance[i]/NewLength,TypeHit[i]);
			}
		}

		return true;
	}

	return false;
}

bool	CCone::Intersection(const CRay &Ray,
								double   *Distance,
								INTERSECT_ENUM *TypeHit)
{
	bool bRes=false;
	////Calcul des différents éléments du déterminants
	////de l'équation du second degrée
    double a = Ray.GetDirect().GetX()*Ray.GetDirect().GetX()+
			   Ray.GetDirect().GetY()*Ray.GetDirect().GetY()-
			   Ray.GetDirect().GetZ()*Ray.GetDirect().GetZ();	

	double b = Ray.GetOrigin().GetX() * Ray.GetDirect().GetX()+
			   Ray.GetOrigin().GetY() * Ray.GetDirect().GetY()-
			   Ray.GetOrigin().GetZ() * Ray.GetDirect().GetZ();

	double	c = Ray.GetOrigin().GetX() * Ray.GetOrigin().GetX()+
				Ray.GetOrigin().GetY() * Ray.GetOrigin().GetY()-
				Ray.GetOrigin().GetZ() * Ray.GetOrigin().GetZ();

	if(fabs(a)<EPSILON)
	{
		if(fabs(b)>EPSILON)
		{
			//1 intersection
			Distance[0]=-0.5*c/b;
			TypeHit[0] = SIDE_INTERSECT;
			bRes=true;
		}
	} else {

		double delta = b * b - a * c;

		if (delta >= 0.0)
		{
			delta = sqrt(delta);

			Distance[0] = (-b + delta) / a;
			Distance[1] = (-b - delta) / a;
			TypeHit[0] = SIDE_INTERSECT;
			TypeHit[1] = SIDE_INTERSECT;

			bRes=true;
		} 
	}

	///Test est-ce que le rayon traverse un des bouts du cylindre
  if (fabs(Ray.GetDirect().GetZ()) > EPSILON)
  {
    double d = (1.0 - Ray.GetOrigin().GetZ()) / Ray.GetDirect().GetZ();
    double a = (Ray.GetOrigin().GetX() + d * Ray.GetDirect().GetX());
    double b = (Ray.GetOrigin().GetY() + d * Ray.GetDirect().GetY());

	if((SQR(a) + SQR(b)) <= 1.0)
	{
		Distance[2] = d;
		TypeHit[2] = CAP_INTERSECT;
		bRes=true;
	}

    d =  (m_Dist - Ray.GetOrigin().GetZ()) / Ray.GetDirect().GetZ();
    a = (Ray.GetOrigin().GetX() + d * Ray.GetDirect().GetX());
    b = (Ray.GetOrigin().GetY() + d * Ray.GetDirect().GetY());

	if((SQR(a) + SQR(b)) <= SQR(m_Dist))
	{
		Distance[3] = d;
		TypeHit[3] = BASE_INTERSECT;
		bRes=true;
	}
  }

  return bRes;
}



////////////////////////
//Normale au cylindre
//La normale dans l'espace du cylindre est trivial
CVector	CCone::Normal(const CCoord &coord,INTERSECT_ENUM Type)
{
	if(m_IsCylinder) 
	{
		return(CCylinder::Normal(coord,Type));
	}
	/* On met la coordonnée dans l'espace du cylindre */
	CVector res(coord);

	if(m_Trans.GetExist())
	{
		res=m_Trans.InvTrans(coord);
	} 

	switch (Type)
	{
		case SIDE_INTERSECT:
			res.m_Value[2] = -res.m_Value[2];	
		  break;

		case BASE_INTERSECT:
			res.Set(0,0,-1);
		  break;

		case CAP_INTERSECT:
			res.Set(0.0, 0.0, 1.0);
		  break;
	}

	if(m_Trans.GetExist())
	{
		res=m_Trans.TransNormal(res);
	}

	res.Normalize();

	return res;
}


//OK
void	CCone::GetOutputStream(ostream &o)
{
	o	<<	"cone\n{ " << m_Base << " , " << m_Radius
					   << m_Cap <<  " , " << m_CapRadius << "\n";
	o	<< "\ttexture{ \""		<< m_pMatiere->GetName().c_str()		<< "\" }\n";
	o	<<	"\n}\n";
}

//OK
void CCone::ForceEqual(CBaseGeometry &Origin)
{
	CCone *pTrueOrigin=static_cast<CCone*>(&Origin);
	if(pTrueOrigin!=NULL)
	{
		*this=*pTrueOrigin;
	}
}

//OK
CBaseGeometry*	CCone::Instantiate()
{
	return new CCone;
}


//*******
//Initialisation du changement de base du cone
void	CCone::InitTrans()
{
	if(fabs(m_Radius-m_CapRadius)<EPSILON)
	{
		//C'est un cylindre
		CCylinder::InitTrans();
		m_IsCylinder=true;

		return;
	}

	if(m_CapRadius<m_Radius)
	{
		//On inverse le tout pour avoir le plus grand rayon en haut
		CCoord	tmp(m_Base);
		m_Base=m_Cap;
		m_Cap=tmp;

		double tmpRadius=m_Radius;
		m_Radius=m_CapRadius;
		m_CapRadius=tmpRadius;
	}

	CVector	Axis(m_Cap-m_Base);
	double	AxisLength=Axis.Length();

	if(AxisLength<EPSILON)
	{
		//Erreur -> cone/cylindre dégénéré en disque
	} else {
		Axis.Normalize();
	}

	//calcul du changement de base
	double tmp=m_Radius*AxisLength/(m_CapRadius-m_Radius);
	CCoord	Origin(Axis*tmp);
	Origin=m_Base-Origin;

	double tmpLength=tmp+AxisLength;

	m_Trans.ChangeCoordinateSystem(Origin,Axis,m_CapRadius,tmpLength);
	m_Dist=tmp/tmpLength;

}

CBaseGeometry* CCone::GetBoundSphere()
{
	return(new CSphere((m_Cap+m_Base)/2.0,MAX(m_Radius,m_CapRadius)));
}

