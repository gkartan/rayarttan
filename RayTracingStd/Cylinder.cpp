#include "stdio.h"
#include "BaseGeometry.h"
#include "Cylinder.h"
#include "Ray.h"
#include "Constants.h"
#include "Power.h"
#include "TraceService.h"
#include "Sphere.h"

CCylinder::CCylinder()
{
	m_DistanceTolerance=1e-6;
}

CCylinder::CCylinder(const CCoord &base,const CCoord &cap,double ray)
{
	m_DistanceTolerance=1e-6;
	m_Base=base;
	m_Cap=cap;
	m_Radius=ray;

	InitTrans();
}

CCylinder::~CCylinder()
{
}

CCylinder&	CCylinder::operator=(CCylinder	&Origin)
{
	m_DistanceTolerance=Origin.m_DistanceTolerance;
	m_Base=Origin.m_Base;
	m_Cap=Origin.m_Cap;
	m_Radius=Origin.m_Radius;

	return (*this);
}

/////////////////////////////////////////
//Calcul de l'intersection d'un vecteur avec une sphère
bool	CCylinder::Intersection(CRay &Ray)
{ 
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
					if(z>=0.0 && z<=1.0)
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

bool	CCylinder::Intersection(const CRay &Ray,
								double   *Distance,
								INTERSECT_ENUM *TypeHit)
{
	bool bRes=false;
	////Calcul des différents éléments du déterminants
	////de l'équation du second degrée
    double a = Ray.GetDirect().GetX()*Ray.GetDirect().GetX()+
			   Ray.GetDirect().GetY()*Ray.GetDirect().GetY();	

    if (a > EPSILON)
    {
      double b = Ray.GetOrigin().GetX() * Ray.GetDirect().GetX()+
				 Ray.GetOrigin().GetY() * Ray.GetDirect().GetY();

      double	c = Ray.GetOrigin().GetX() * Ray.GetOrigin().GetX()+
				    Ray.GetOrigin().GetY() * Ray.GetOrigin().GetY()-1.0;

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

    d =  - Ray.GetOrigin().GetZ() / Ray.GetDirect().GetZ();
    a = (Ray.GetOrigin().GetX() + d * Ray.GetDirect().GetX());
    b = (Ray.GetOrigin().GetY() + d * Ray.GetDirect().GetY());

	if((SQR(a) + SQR(b)) <= 1.0)
	{
		Distance[3] = d;
		TypeHit[3] = BASE_INTERSECT;
		bRes=true;
	}
  }

  return bRes;
}

bool CCylinder::AddIntersect(CRay &Ray,double Distance)
{
	return false;
}


bool CCylinder::AddIntersect(CRay &Ray,double Distance,INTERSECT_ENUM Type)
{
	CBaseIntersection	*pIntersection=new CBaseIntersection;

	// On calcule le point d'intersection
	CCoord	&ImpactPt=Ray.GetOrigin()+Ray.GetDirect()*Distance;

	// Et la normale du cylindre en ce point
	CVector &vNormal=Normal(ImpactPt,Type);

	// On calcule le cosinus que font le rayon et la normale
	double cosangle=Ray.GetDirect()*vNormal;


	pIntersection->SetDistance(Distance,ImpactPt);
	pIntersection->SetObjet(this);
	pIntersection->SetNormal(vNormal);
	pIntersection->SetMatiere(m_pMatiere);

	if (cosangle>0)
	  pIntersection->SetMilieu(m_pMatiere->GetMilieu2());
	else
	  pIntersection->SetMilieu(m_pMatiere->GetMilieu1());

	// Puis on la rajoute dans la liste des intersections
	return(Ray.AddIntersect(pIntersection));
}

//////////////////////////////////////////
//Normale au cylindre
//Non implémenté --> on doit savoir ou on a intersecte
CVector	CCylinder::Normal(const CCoord &coord)
{
	return CVector(0,0,0);
}

////////////////////////
//Normale au cylindre
//La normale dans l'espace du cylindre est trivial
CVector	CCylinder::Normal(const CCoord &coord,INTERSECT_ENUM Type)
{
  /* On met la coordonnée dans l'espace du cylindre */
  CVector res(coord);

  if(m_Trans.GetExist())
  {
 	res=m_Trans.InvTrans(coord);
  } 

  switch (Type)
  {
    case SIDE_INTERSECT:
        res.m_Value[2] = 0.0;	///Z=0
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
void	CCylinder::GetOutputStream(ostream &o)
{
	o	<<	"cylinder\n{ " << m_Base << " , " << m_Cap << " , " << m_Radius << "\n";
	o	<< "\ttexture{ \""		<< m_pMatiere->GetName().c_str()		<< "\" }\n";
	o	<<	"\n}\n";
}

//OK
void CCylinder::ForceEqual(CBaseGeometry &Origin)
{
	CCylinder *pTrueOrigin=static_cast<CCylinder*>(&Origin);
	if(pTrueOrigin!=NULL)
	{
		*this=*pTrueOrigin;
	}
}

//OK
CBaseGeometry*	CCylinder::Instantiate()
{
	return new CCylinder;
}


//*******
//Initialisation du changement de base du cylindre
void	CCylinder::InitTrans()
{
	CVector	Axis(m_Cap-m_Base);
	double	AxisLength=Axis.Length();

	if(AxisLength<EPSILON)
	{
		//Erreur -> cylindre dégénéré en disque
	} else {
		Axis.Normalize();
		m_Trans.ChangeCoordinateSystem(m_Base,Axis,m_Radius,AxisLength);
	}
}

CBaseGeometry* CCylinder::GetBoundSphere()
{
	return(new CSphere((m_Cap+m_Base)/2.0,m_Radius));
}

