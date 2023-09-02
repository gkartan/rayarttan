#include "stdio.h"
#include "BaseGeometry.h"
#include "Box.h"
#include "BaseIntersection.h"
#include "Ray.h"
#include "Constants.h"

CBox::CBox()
{
	m_DistanceTolerance=1e-6;
	m_BeginCoord=CCoord(0,0,0);
	m_EndCoord=CCoord(0,0,0);
}

CBox::CBox(const CCoord &Coord1,const CCoord &Coord2)
{
	m_DistanceTolerance=1e-6;
	m_BeginCoord=Coord1;
	m_EndCoord=Coord2;
}

CBox::~CBox()
{
}

CBox&	CBox::operator=(CBox	&Origin)
{
	m_BeginCoord=Origin.m_BeginCoord;
	m_EndCoord=Origin.m_EndCoord;

	return (*this);
}


bool	CBox::Intersection(CRay &Ray,bool bAdd)
{ 
	CRay NewRay=Ray;
	if(GetExistTrans())
	{
		NewRay.SetOrigin(m_Trans.InvTrans(Ray.GetOrigin()));
		NewRay.SetDirect(m_Trans.InvTrans(Ray.GetDirect()));
	}

	double TNear=0;
	double TFar=MAX_HUGE_OBJECT;
	SIDE_ENUM_IND SideNear=SIDE_IND;
	SIDE_ENUM_IND SideFar=SIDE_IND;
	SIDE_ENUM SideNearFinal=SIDE_INIT;
	SIDE_ENUM SideFarFinal=SIDE_INIT;

	////Test intersection en X
	if(!Intersection(m_BeginCoord.GetX(),
					 m_EndCoord.GetX(),
					 NewRay.GetOrigin().GetX(),
					 NewRay.GetDirect().GetX(),
					 TNear,TFar,
					 SideNear,SideFar)) 
	{
		return false;
	}

	if(SideNear!=SIDE_IND) SideNearFinal=Convert(SideNear,SIDE_X);
	if(SideFar!=SIDE_IND) SideFarFinal=Convert(SideFar,SIDE_X);
	SideNear=SIDE_IND;
	SideFar=SIDE_IND;

	////Test intersection en Y
	if(!Intersection(m_BeginCoord.GetY(),
					 m_EndCoord.GetY(),
					 NewRay.GetOrigin().GetY(),
					 NewRay.GetDirect().GetY(),
					 TNear,TFar,
					 SideNear,SideFar))
	{
		return false;
	}

	if(SideNear!=SIDE_IND) SideNearFinal=Convert(SideNear,SIDE_Y);
	if(SideFar!=SIDE_IND) SideFarFinal=Convert(SideFar,SIDE_Y);
	SideNear=SIDE_IND;
	SideFar=SIDE_IND;

	////Test intersection en Z
	if(!Intersection(m_BeginCoord.GetZ(),
					 m_EndCoord.GetZ(),
					 NewRay.GetOrigin().GetZ(),
					 NewRay.GetDirect().GetZ(),
					 TNear,TFar,
					 SideNear,SideFar))
	{
		return false;
	}

	if(SideNear!=SIDE_IND) SideNearFinal=Convert(SideNear,SIDE_Z);
	if(SideFar!=SIDE_IND) SideFarFinal=Convert(SideFar,SIDE_Z);

	///Ajout des 2 intersections
	if(bAdd)
	{
		if(SideNearFinal!=SIDE_INIT) AddIntersect(Ray,TNear,SideNearFinal);
		if(SideFarFinal!=SIDE_INIT) AddIntersect(Ray,TFar,SideFarFinal);
	}

	return true;
}

bool	CBox::Intersection(	 double BeginCoord,
							 double EndCoord,
							 double RayBegin,
							 double RayDirect,
							 double &TNear,
							 double &TFar,
							 SIDE_ENUM_IND &SideNear,
							 SIDE_ENUM_IND &SideFar)
{
  double t=0;

  if (RayDirect < -EPSILON)
  {
    t = (BeginCoord - RayBegin) / RayDirect;

    if (t < TNear-TEST_EPSILON) return(false);

    if (t <= TFar-TEST_EPSILON)
    {
	  SideFar=SIDE_0;
      TFar = t;
    }

    t = (EndCoord - RayBegin) / RayDirect;

    if (t >= TNear-TEST_EPSILON)
    {
      if (t > TFar-TEST_EPSILON) return(false);

	  SideNear=SIDE_1;
      TNear = t;
    }
  }
  else
  {
    if (RayDirect > EPSILON)
    {
      t = (EndCoord - RayBegin) / RayDirect;

      if (t < TNear-TEST_EPSILON) return(false);

      if (t <= TFar-TEST_EPSILON)
      {
		SideFar=SIDE_0;
        TFar = t;
      }

      t = (BeginCoord - RayBegin) / RayDirect;

      if (t >= TNear-TEST_EPSILON)
      {
        if (t > TFar-TEST_EPSILON) return(false);

		SideNear=SIDE_1;
        TNear = t;
      }
    }
    else
    {
      if ((RayBegin < BeginCoord) || (RayBegin > EndCoord))
      {
        return(false);
      }
    }
  }

  return true;
}


bool CBox::AddIntersect(CRay &Ray,double Distance,SIDE_ENUM Side)
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
	double NormalDirect=vNormal*Ray.GetDirect();
	if(NormalDirect>0.0)
	{
		vNormal=-vNormal;
	}

    pIntersection->SetNormal(vNormal);


    // Puis on la rajoute dans la liste des intersections
    return(Ray.AddIntersect(pIntersection));

}

bool CBox::AddIntersect(CRay &Ray,double Distance)
{
	return false;
}


/////A implémenter + tard
CVector	CBox::Normal(const CCoord &coord)
{
	return CVector(0,0,0);
}

CVector	CBox::Normal(const SIDE_ENUM Side)
{
	CVector res(0,0,0);

	switch (Side)
	{
		case SIDE_X_0: 
			res=CVector(-1.0,  0.0,  0.0);
			break;

		case SIDE_X_1: 
			res=CVector(1.0,  0.0,  0.0);
			break;

		case SIDE_Y_0: 
			res=CVector(0.0, -1.0,  0.0);
			break;

		case SIDE_Y_1: 
			res=CVector(0.0,  1.0,  0.0);
			break;

		case SIDE_Z_0: 
			res=CVector(0.0,  0.0, -1.0);
			break;

		case SIDE_Z_1: 
			res=CVector(0.0,  0.0,  1.0);
			break;

		default: ;
	}

	if(GetExistTrans())
	{
		res=m_Trans.TransNormal(res);
		res.Normalize();
	}

	return res;

}


double CBox::Distance(CCoord & point)
{
	return 0;
}


void	CBox::GetOutputStream(ostream &o)
{
	o	<<	"box\n{ " << m_BeginCoord << " , " << m_EndCoord << "\n";
	o	<< "\ttexture{ \""		<< m_pMatiere->GetName().c_str()		<< "\" }\n";
	o	<<	"\n}\n";
}

void CBox::ForceEqual(CBaseGeometry &Origin)
{
	CBox *pTrueOrigin=static_cast<CBox*>(&Origin);
	if(pTrueOrigin!=NULL)
	{
		*this=*pTrueOrigin;
	}
}

CBaseGeometry*	CBox::Instantiate()
{
	return new CBox;
}


CBaseGeometry* CBox::GetBoundSphere()
{
    double Rayon=(m_EndCoord-m_BeginCoord).Length()/2.0;

	CSphere *pSphere=new CSphere((m_EndCoord+m_BeginCoord)/2.0,Rayon);
	pSphere->SetTrans(GetTrans());

	return pSphere;
};
