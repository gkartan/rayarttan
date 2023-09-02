#include "stdio.h"
#include "BaseGeometry.h"
#include "Torus.h"
#include "Ray.h"
#include "PolynomialQuartic.h"
#include "PolynomialQuadratic.h"

#define ROOTS_TOLERANCE 0.0001

CTorus::CTorus()
:m_Center(0,0,0)
{
	m_DistanceTolerance=0.0005;
	m_Major=1;
	m_Minor=0;
}

CTorus::CTorus(const CCoord &center, double Major,double Minor)
{
	m_Center=center;
	m_DistanceTolerance=0.0005;
	m_Major=Major;
	m_Minor=Minor;
}

CTorus::CTorus(double Major,double Minor)
:m_Center(0,0,0)
{
	m_DistanceTolerance=0.0005;
	m_Major=Major;
	m_Minor=Minor;
}

CTorus::~CTorus()
{
}

CTorus&	CTorus::operator=(CTorus	&Origin)
{
	m_DistanceTolerance=Origin.m_DistanceTolerance;
	m_Major=Origin.m_Major;
	m_Minor=Origin.m_Minor;

	return (*this);
}

/////////////////////////////////////////
//Calcul de l'intersection d'un vecteur avec une sphère
bool	CTorus::Intersection(CRay &Ray)
{ 
	double Major2=m_Major*m_Major;
	double Minor2=m_Minor*m_Minor;

	CVector RayOrigin(Ray.GetOrigin());

	double RayScalar=Ray.GetDirect()*Ray.GetOrigin();
	double DirectY2=Ray.GetDirect().GetY()*Ray.GetDirect().GetY();
	double OriginY2=Ray.GetOrigin().GetY()*Ray.GetOrigin().GetY();
	double DirectOriginY2=Ray.GetOrigin().GetY()*Ray.GetDirect().GetY();
	double Expr1=RayOrigin.LengthSqr()-Major2-Minor2;
	//double Expr2=RayOrigin.LengthSqr()-(m_Major-m_Minor)*(m_Major-m_Minor);
	//double Expr3=RayOrigin.LengthSqr()-(m_Major+m_Minor)*(m_Major+m_Minor);

	///Equation du type : a4*x^4+a3*x^3+a2*x^2+a1*x+a0=0
	CPolynomialQuartic	EquationToSolve; //Polynome d'ordre 4
	//CPolynomial EquationToSolve(4);

	//On considère que la norme du rayon est 1
	//coeff de l'ordre 4
	//a4=||Rayon.Direct||^4=1
	double a4=1;
	EquationToSolve.SetCoeff(4,a4);	
	//coeff de l'order 3
	//a3=4*<Rayon.Origine,Rayon.Direct> * ||Rayon.Direct^2||=4*<Rayon.Origine,Rayon.Direct>
	double a3=4*RayScalar;
	EquationToSolve.SetCoeff(3,a3);
	//coeff de l'ordre 2
	//a2=4*<Rayon.Origine,Rayon.Direct>^2+2*(||Rayon.Origine||^2-(ToreRayonMajor^2+ToreRayonMinor^2))+4*Vz^2*Major^2
	//double a2=4*RayScalar*RayScalar+2*Expr1+
	//		  4*Ray.GetDirect().GetY()*4*Ray.GetDirect().GetY()*Major2;
	double a2=2*(Expr1+2*(RayScalar*RayScalar+Major2*DirectY2));
	EquationToSolve.SetCoeff(2,a2);
	//coeff de l'ordre 1
	//a1=4*<Rayon.Origine,Rayon.Direct>*(||Rayon.Origine||^2-(ToreRayonMajor^2+ToreRayonMinor^2))+8*Vz*Oz*Major^2*
	//double a1=4*RayScalar*Expr1+8*Major2*Ray.GetOrigin().GetY()*Ray.GetDirect().GetY();
	double a1=4*(RayScalar*Expr1+2*Major2*DirectOriginY2);
	EquationToSolve.SetCoeff(1,a1);

	//coeff de l'ordre 0
	//a0=(||Rayon.Origine||^2-(R-r)^2)*(||Rayon.Origine||^2-(R+r)^2)+4*Oz^2
	//double a0=Expr2*Expr3+4*Major2*(Ray.GetOrigin().GetY()*Ray.GetOrigin().GetY()-Minor2);
	double a0=Expr1*Expr1+4*Major2*(OriginY2-Minor2);
	EquationToSolve.SetCoeff(0,a0);


	TypeVectorDouble	roots;

	if(EquationToSolve.Solve(roots,ROOTS_TOLERANCE))
	{
		double vLength=Ray.GetDirect().Length();
		for(int i=0;i<roots.size();i++)
		{
			//Ajout d'intersections
			AddIntersect(Ray,Distance(roots[i],vLength));
		}
		return true;
	} else {
		return false;
	}

}

bool CTorus::AddIntersect(CRay &Ray,double Distance)
{
	CBaseIntersection	*pIntersection=new CBaseIntersection;

	// On calcule le point d'intersection
	CCoord	&ImpactPt=Ray.GetOrigin()+Ray.GetDirect()*Distance;

	// Et la normale qu'a la sphere en ce point
	CVector &vNormal=Normal(ImpactPt);

	// On calcule le cosinus que font le rayon et la normale
	double cosangle=Ray.GetDirect()*vNormal;

	// On initialise l'intersection
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
//Normal au tore
CVector	CTorus::Normal(const CCoord &coord)
{
	double X=coord.GetX();
	double Z=coord.GetZ();
	CVector res;
	double dist=sqrt(X*X+Z*Z);

	if(dist>EPSILON)
	{
		res=CVector(m_Major*X/dist,
					0,
					m_Major*Z/dist);
	} else {
		res=CVector(0,0,0);
	}

	CVector vcoord(coord);
	res=vcoord-res;
	res.Normalize();

	return res;
}


//////////////////////////////////////////
///Distance entre un point et le tore
///Root : racine du polynome 
///Length : longueur du vecteur directeur du rayon
double CTorus::Distance(double root,double Length)
{
	return root/Length;
}


void	CTorus::GetOutputStream(ostream &o)
{
	o	<<	"torus\n{ " << m_Center << " , " << m_Major << " , " << m_Minor << "\n";
	o	<< "\ttexture{ \""		<< m_pMatiere->GetName().c_str()		<< "\" }\n";
	o	<<	"\n}\n";
}

void CTorus::ForceEqual(CBaseGeometry &Origin)
{
	CTorus *pTrueOrigin=static_cast<CTorus*>(&Origin);
	if(pTrueOrigin!=NULL)
	{
		*this=*pTrueOrigin;
	}
}

CBaseGeometry*	CTorus::Instantiate()
{
	return new CTorus;
}

