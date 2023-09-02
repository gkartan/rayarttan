#include "stdio.h"
#include "BaseGeometry.h"
#include "Sphere.h"
#include "Ray.h"
#include "Constants.h"

CSphere::CSphere()
{
	m_DistanceTolerance=EPSILON;
}

CSphere::CSphere(const CCoord &center,double ray)
{
	m_DistanceTolerance=EPSILON;
	m_Center=center;
	m_Ray=ray;
}

CSphere::~CSphere()
{
}

CSphere&	CSphere::operator=(CSphere	&Origin)
{
	m_DistanceTolerance=Origin.m_DistanceTolerance;
	m_Center=Origin.m_Center;
	m_Ray=Origin.m_Ray;

	return (*this);
}

/////////////////////////////////////////
//Calcul de l'intersection d'un vecteur avec une sphère
bool	CSphere::Intersection(CRay &Ray)
{ 
	double	DistMin=0;
	double  DistMax=0;
	CCoord	Impact;

	/////Test
	CRay NewRay;
	NewRay.SetRayClear(Ray);

	if(GetExistTrans())
	{
		NewRay.SetOrigin(m_Trans.InvTrans(Ray.GetOrigin()));
		NewRay.SetDirect(m_Trans.InvTrans(Ray.GetDirect()));
	}


	if(Intersection(NewRay,DistMin,DistMax,Impact))
	{
		if(DistMin!=0)
		{
			AddIntersect(Ray,DistMin);
		}
		if(DistMax!=0)
		{
			AddIntersect(Ray,DistMax);
		}

		return true;
	}

	return false;
}

bool	CSphere::Intersection(CRay &Ray,
							  double &DistMin,
							  double &DistMax,
							  CCoord &ImpactPt)
{
	CVector vCenterToOrigRay=Ray.GetOrigin()-m_Center;

	//Calcul des coefficients de l'équation du second degré
	double b=2*(Ray.GetDirect()*vCenterToOrigRay);
	double c=vCenterToOrigRay*vCenterToOrigRay-m_Ray*m_Ray;

	///Calcul du discriminant
	double delta=b*b-4*c;

	if (delta<0)
	{
		// Le rayon ne traverse pas la sphere. Il n'y a donc pas d'intersection

		return false;
	}
	else
	if (fabs(delta)<EPSILON)
	{
		// Le rayon est tangeant a la sphere. Il y a une intersection unique
		// On place l'intersection dans la liste des intersections
		DistMin=Distance(b,0,true);

		ImpactPt=Ray.GetOrigin()+Ray.GetDirect()*DistMin;

		return true;
	}
	else
	{
	// Il existe deux points d'intersections

	  // On place la première intersection dans la liste des intersections
	  DistMax=Distance(b,delta,true);

	  // On place la deuxième intersection dans la liste des intersections
	  DistMin=Distance(b,delta,false);

	  ImpactPt=Ray.GetOrigin()+Ray.GetDirect()*DistMin;

	  return true;
	}

}

bool CSphere::AddIntersect(CRay &Ray,double Distance)
{
	CBaseIntersection	*pIntersection=new CBaseIntersection;

	// On calcule le point d'intersection
	CCoord	&ImpactPt=Ray.GetOrigin()+Ray.GetDirect()*Distance;

	// Et la normale qu'a la sphere en ce point
	CVector &vNormal=Normal(ImpactPt);

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
//Normale à la sphere en 1 coordonnée
CVector	CSphere::Normal(const CCoord &coord)
{
	CCoord newcoord(coord);

	if(m_Trans.GetExist())
	{
		newcoord=m_Trans.InvTrans(newcoord);
	}

	CVector res(m_Center,newcoord);

	//Si la sphere a subi une transformation alors on transforme la normale
	if(m_Trans.GetExist())
	{
		res=m_Trans.TransNormal(res);
	}

	res.Normalize();
	return res;
}


//////////////////////////////////////////
///Calcul d'une distance pour l'intersection
double CSphere::Distance(double b,double delta,bool IsFirst)
{
	if(IsFirst)
	{
		return(-(b-sqrt(delta))/2);
	} else {
		return(-(b+sqrt(delta))/2);
	}
}

////////////////////////////////////////////
////Les transformations
void	CSphere::Scale(const CVector &Vect)
{
	///Seul le rayon bouge
	if(Vect.GetX()==Vect.GetY() && Vect.GetY()==Vect.GetZ())
	{
		m_Ray*=Vect.GetX();
	} else {
		///La sphere devient une ellipsoide
		///A VOIR
	}
}


void	CSphere::Translate(const CVector &Vect)
{
	m_Center=m_Center+Vect;
}

void	CSphere::GetOutputStream(ostream &o)
{
	o	<<	"sphere\n{ " << m_Center << " , " << m_Ray << "\n";
	o	<< "\ttexture{ \""		<< m_pMatiere->GetName().c_str()		<< "\" }\n";
	o	<<	"\n}\n";
}

void CSphere::ForceEqual(CBaseGeometry &Origin)
{
	CSphere *pTrueOrigin=static_cast<CSphere*>(&Origin);
	if(pTrueOrigin!=NULL)
	{
		*this=*pTrueOrigin;
	}
}

CBaseGeometry*	CSphere::Instantiate()
{
	return new CSphere;
}

