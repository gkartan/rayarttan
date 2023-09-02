#include "stdio.h"
#include "BaseGeometry.h"
#include "Plan.h"
#include "BaseIntersection.h"
#include "Ray.h"
#include "Constants.h"

CPlane::CPlane()
{
	m_DistanceTolerance=EPSILON;
}

CPlane::CPlane(CVector &Vect,
			 double Cste)
{
	m_DistanceTolerance=EPSILON;
	Vect.Normalize();
	m_Coeff=Vect;
	m_Cste=Cste;
}

CPlane::CPlane(CVector &Vect,
			 CCoord  &Point)
{
  Vect.Normalize();
  m_Coeff=Vect;

  m_Cste=-(Vect*Point);
}

CPlane::~CPlane()
{
}

CPlane&	CPlane::operator=(CPlane	&Origin)
{
	m_DistanceTolerance=Origin.m_DistanceTolerance;

	m_Coeff=Origin.m_Coeff;	
	m_Cste=Origin.m_Cste;		

	return (*this);
}

void	CPlane::SetPlane(CVector &Vect,double Dist)
{
	CVector	vector=Vect;
	vector.Normalize();
	m_Coeff=vector;

	m_Cste=-(Dist*m_Coeff.Length());
}


/////////////////////////////////////////
//Calcul de l'intersection d'un vecteur avec un plan
bool	CPlane::Intersection(CRay &Ray)
{ 
  CRay NewRay;
  NewRay.SetRayClear(Ray);

  if(GetExistTrans())
  {
	NewRay.SetOrigin(m_Trans.InvTrans(Ray.GetOrigin()));
	NewRay.SetDirect(m_Trans.InvTrans(Ray.GetDirect()));
  }


  double cosalpha;				  // Cosinus de l'angle entre le vecteur directeur du rayon et la normale au plan
  CBaseIntersection Intersection; // Intersection entre le rayon et le plan

  cosalpha=Normal()*NewRay.GetDirect();

  if (fabs(cosalpha)<EPSILON)
  {
    // Les deux vecteurs sont perpendiculaires

    return false;
  }
  else
  {
	return(AddIntersect(Ray,-(Distance(Ray.GetOrigin())/cosalpha)));
  }

  return false;

}

bool CPlane::AddIntersect(CRay &Ray,double Distance)
{
	CBaseIntersection *pIntersection=new CBaseIntersection;

	CCoord	&ImpactPt=Ray.GetOrigin()+Ray.GetDirect()*Distance;
	pIntersection->SetDistance(Distance,ImpactPt);
	pIntersection->SetObjet(this);
    pIntersection->SetNormal(Normal());

    if (Distance>0)
      pIntersection->SetMilieu(m_pMatiere->GetMilieu2());
    else
      pIntersection->SetMilieu(m_pMatiere->GetMilieu1());

	pIntersection->SetMatiere(m_pMatiere);

    // Puis on la rajoute dans la liste des intersections
    return(Ray.AddIntersect(pIntersection));

}

//////////////////////////////////////////
//Normal au plan ---> coefficients directeurs sans la constante
CVector	CPlane::Normal(const CCoord &coord)
{
	return(m_Coeff);
}

CVector	CPlane::Normal()
{
	return(m_Coeff);
}


//////////////////////////////////////////
///Distance entre un point et le plan
double CPlane::Distance(const CCoord & point)
{
	return(m_Coeff*point+m_Cste);
}

void	CPlane::GetOutputStream(ostream &o)
{
	o	<<	"\nplane\n{\n";						//entete
	o   <<  "\t" << m_Coeff << "\n";		//normal
	o	<<	"\tconstant "	<< m_Cste << "\n";		//constante
	o	<< "\ttexture{ \""		<< m_pMatiere->GetName().c_str()		<< "\" }\n";
	o	<<	"}\n";
}

void CPlane::ForceEqual(CBaseGeometry &Origin)
{
	CPlane *pTrueOrigin=static_cast<CPlane*>(&Origin);
	if(pTrueOrigin!=NULL)
	{
		*this=*pTrueOrigin;
	}
}

CBaseGeometry*	CPlane::Instantiate()
{
	return new CPlane;
}

