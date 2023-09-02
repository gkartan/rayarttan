/////Etat classe : EN COURS

#ifndef _BASEFRACTAL
#define _BASEFRACTAL

#include "Vector.h"
#include "BaseGeometry.h"
#include "ComputeExpr.h"
#include "Sphere.h"
#include "Ray.h"
#include "Macros.h"
#include <ostream.h>

class CBaseFractal : public CBaseGeometry
{
// Construction
public:
	inline CBaseFractal();

//Attributes
protected:
	unsigned long				m_NbIteration;
	double						m_MaxLimits;
	double						m_Increment;
	double						m_InitIncrement;
	double						m_FractalTolerance;
	CSphere						m_BoundSphere;
	double						m_IncrementBeyond;
	std::string					m_sExpr;
	std::string					m_sExprDerivate;
	double						m_Angle;
	bool						m_bManualDerivative;

protected:
	inline virtual void	ForceEqual(CBaseGeometry&);
	inline virtual CBaseGeometry*	Instantiate()=0;		//instancie un nouvel objet de ce type

public:
///Fonctions d'accès pour les clients style IHM
	virtual CBaseVector<4,double>		GetInitValue()=0;
	long						GetMaxIter() {return m_NbIteration;};
	double						GetNbStep()	 {return m_Increment;}
	std::string					GetStrExpr() {return m_sExpr;}
	std::string					GetStrExprDerivate() {return m_sExprDerivate;}
	virtual std::string			GetAlgebraType()=0; //Type de la fractale Quaternion,...
	virtual bool				GetOptimisation()=0; //Permet de savoir si la classe est optimisé 3DNow
	double						GetAngleDeg()	 {return CONVERT_RADTODEG(m_Angle);}
	double						GetBoundSize()	 {return m_BoundSphere.GetRay();}
	double						GetBailout()	 {return sqrt(m_MaxLimits);}

	virtual void				SetInitValue(const CBaseVector<4,double>&)=0;
	void						SetMaxIter(const long Iter) {m_NbIteration=Iter;};
	void						SetNbStep(double Step)	 {m_Increment=Step;}
	void						SetStrExpr(const std::string& str) {m_sExpr=str;}
	void						SetStrExprDerivate(const std::string& str) {m_sExprDerivate=str;}
	void						SetAngleDeg(double Angle)	 {m_Angle=CONVERT_DEGTORAD(Angle);}
	void						SetBailout(const double value) {m_MaxLimits=value*value;}
	void						SetBoundSize(double BoundSize)		 {m_BoundSphere.SetRay(BoundSize);}
	virtual bool				Derivate()=0;
	virtual int					Parse()=0;

	void						SetManualDerivative(bool param) {m_bManualDerivative=param;};
	bool						GetManualDerivative()			{return(m_bManualDerivative);};
	///
public:
	inline virtual	void	Translate(const CVector&);
	inline virtual	void	Rotate(const CVector&);

	inline virtual CBaseFractal& operator=(CBaseFractal&);
	virtual void	ForceEqualFractal(CBaseFractal&)=0;			//Permet de forcer l'égalité des dérivées

//operations dérivées
public:
	inline virtual	bool	Intersection(CRay&);
	inline virtual bool	AddIntersect(CRay&,double Distance);
	inline		   bool	AddIntersect(CRay&,double Distance,CVector&);

	virtual CBaseGeometry* GetBoundSphere()	{return &m_BoundSphere;};

protected:
	inline virtual CVector	Normal(const CCoord &coord)=0;

protected:
	////operations spécialisés
	virtual	bool	Estimator(CRay&,double Dist)=0; //un inline sur cette ligne ralentit
	inline		    bool	Intersection(CRay&,double DistMin,double DistMax,
								 double &Dist,CCoord&);
	inline	     	bool	SearchIntersection(CRay&,double DistMin,double DistMax,
								 double &Dist);

	inline			bool	PreIntersection(const CRay&,CRay&);
	inline			CVector	PostIntersection(const CCoord&);
 
// Implementation
public:
	inline	virtual ~CBaseFractal();

	////Gestion stream
public:
	virtual	void	GetOutputStream(ostream&)=0;

};

CBaseFractal::CBaseFractal()
{
	m_DistanceTolerance=1e-7;
	m_FractalTolerance=1e-4;
	m_NbIteration=5;
	m_MaxLimits=16;
	m_BoundSphere=CSphere(CCoord(0,0,0),DEFAULT_BOUNDSIZE);
	m_Angle=0.0;
	m_bManualDerivative=false;
}



CBaseFractal::~CBaseFractal()
{
}

CBaseFractal&	CBaseFractal::operator=(CBaseFractal	&Origin)
{
	ForceEqualFractal(Origin);

	m_NbIteration=Origin.m_NbIteration;
	m_MaxLimits=Origin.m_MaxLimits;
	m_Increment=Origin.m_Increment;
	m_InitIncrement=Origin.m_InitIncrement;
	m_FractalTolerance=Origin.m_FractalTolerance;

	m_BoundSphere=Origin.m_BoundSphere;

	m_IncrementBeyond=Origin.m_IncrementBeyond;

	m_sExpr=Origin.m_sExpr;
	m_sExprDerivate=Origin.m_sExprDerivate;

	m_Angle=Origin.m_Angle;

	m_bManualDerivative=Origin.m_bManualDerivative;

	CBaseGeometry::Equal(Origin);

	return (*this);
}

bool	CBaseFractal::PreIntersection(const CRay &Ray,CRay &NewRay)
{
  NewRay=Ray;
  if(GetExistTrans())
  {
	  NewRay.SetDirect(m_Trans.InvTrans(Ray.GetDirect()));
	  double Len=NewRay.GetDirect()*NewRay.GetDirect();
	  if(Len == 0.0)
	  {
		  return false;
	  }

	  if(Len!=1.0)
	  {
		  Len = 1.0/sqrt(Len);
		  NewRay.SetDirect(NewRay.GetDirect()*Len);
	  }

	  NewRay.SetOrigin(m_Trans.InvTrans(Ray.GetOrigin()));
  } 

  return true;
}

////////////
////Calcul de la normale-> si transformation ou pas
CVector	CBaseFractal::PostIntersection(const CCoord &Init)
{
	CVector NewNormal;

	if(GetExistTrans())
	{
		NewNormal=m_Trans.TransNormal(Normal(Init));
	} else {
		NewNormal=Normal(Init);
	}

	NewNormal.Normalize();

	return NewNormal;

}

/////////////////////////////////////////
//Calcul de l'intersection d'un vecteur avec l'objet fractal
//Le calcul de l'intersection et de la normale sont effectué en même temps
//Le pt d'intersection est calculée en traversant la sphère de rayon 2
//englobant la fractale
//La normale est calculée est prenant comme origine la normale à la sphère
//et en appliquant la même transformation
bool	CBaseFractal::Intersection(CRay &Ray)
{ 
  bool Res=false;

  //Si le rayon part de l'intérieur de l'objet
  //utilisé si l'objet est transparent
  if(Estimator(Ray,-m_DistanceTolerance) && Estimator(Ray,m_DistanceTolerance))
  {
	  ///Calcul du point de départ
	  double DistMin=0;
	  double DistMax=0;
	  CCoord Impact;
	  if(m_BoundSphere.Intersection(Ray,DistMin,DistMax,Impact))
	  {
			CRay NewRay;
			if(!PreIntersection(Ray,NewRay)) return false;

			if(DistMin<0) DistMin=0;

			double Dist=DistMin;

			//variables de sauvegarde
			CCoord SauvInit;
			double SauvDist=0;

			while(Dist<DistMax)
			{
				CCoord Init;
				double Distance;
				if(Intersection(NewRay,Dist,DistMax,Distance,Init))
				{
					SauvInit=Init;
					SauvDist=Distance;
				} else {

					//on recalcule l'intersection en partant de la nouvelle distance
					//On prend le vecteur  l'envers pour calculer le point d'intersection
					//le + extérieur possible
					CRay FinalRay(NewRay);
					FinalRay.SetOrigin(NewRay.GetOrigin()*Dist);
					FinalRay.SetDirect(-FinalRay.GetDirect());
					double FinalDist;
					Intersection(FinalRay,0,m_Increment,FinalDist,SauvInit);
					SauvDist=Dist-FinalDist;

					//sauvegarde 
					//L'intersection doit être rajouté à l'instance
					//de l'objet rayon appelant
					Res=AddIntersect(Ray,SauvDist,PostIntersection(SauvInit));		
					//rétablissement du repère initial
				} 
				///Reinitialisation de l'increment courant
				Dist=Distance+m_Increment;

				if(Res)
				{
					break;
				}
			}

	  }
  } else {

	  ///Calcul du point de départ
	  double DistMin=0;
	  double DistMax=0;
	  CCoord Impact;
	  if(m_BoundSphere.Intersection(Ray,DistMin,DistMax,Impact))
	  {
			CRay NewRay;
			if(!PreIntersection(Ray,NewRay)) return false;

			if(DistMin<0) DistMin=0;

			double Dist=DistMin;
			while(Dist<DistMax)
			{
				CCoord Init;
				double Distance;
				if(Intersection(NewRay,Dist,DistMax,Distance,Init))
				{
					//L'intersection doit être rajouté à l'instance
					//de l'objet rayon appelant
					Res=AddIntersect(Ray,Distance,PostIntersection(Init));		
					//rétablissement du repère initial
				} else return false;
				///Reinitialisation de l'increment courant
				Dist=Distance+m_Increment;

				if(/*!m_pMatiere->IsTransparent() &&*/ Res)
				{
					break;
				}
			}

	  }
  }
						
  return Res;

}

bool	CBaseFractal::Intersection(CRay &Ray,
							   double DistMin,
							   double DistMax,
							   double &Distance,
							   CCoord &Init)
{
	///Le rayon commence dans la fractale --> Rayon lumineux
	if(Estimator(Ray,DistMin-m_DistanceTolerance))
	{
		if(Estimator(Ray,DistMin+m_DistanceTolerance))
		{
			Distance=DistMin+2*m_DistanceTolerance;
			CVector &Scale=Ray.GetDirect()*Distance;
			Init=Ray.GetOrigin()+Scale;
			return true;
		} 
	}

	for(double dist=DistMin;dist<DistMax;dist+=m_Increment)
	{
		if(Estimator(Ray,dist+m_Increment))
		{
			///Dichotomie
			if(SearchIntersection(Ray,dist,dist+m_Increment,Distance))
			{
				  CVector &Scale=Ray.GetDirect()*Distance;
				  Init=Ray.GetOrigin()+Scale;
				  return true;
			}

			///Il y a un problème car on a croisé la fractale --> ne doit pas arriver
			///sans trouver d'intersection;
			Distance=DistMax;
			return false;
		}
	}

	Distance=DistMax;
	return false;
}

/////////////////////////////////////////////////////
///Recherche par dichotomie
///Si la fractale est découpé - risque de traverse
///+rapide que la méthode systématique
bool	CBaseFractal::SearchIntersection(CRay &Ray,
							   double DistMin,
							   double DistMax,
							   double &Distance)
{
	double Middle=(DistMin+DistMax)/2;

	if(fabs(Middle-DistMin)<m_FractalTolerance)
	{
		if(Estimator(Ray,DistMax))
		{
			Distance=Middle;
			return true;
		} else {
			return false;
		}
	}

	if(Estimator(Ray,Middle))
	{
		return(SearchIntersection(Ray,DistMin,Middle,Distance));
	} else {
		return(SearchIntersection(Ray,Middle,DistMax,Distance));
	}
}


bool	CBaseFractal::AddIntersect(CRay &Ray,double Distance,CVector &vNormal)
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

	double NormalDirect=vNormal*Ray.GetDirect();
	if(NormalDirect>0.0)
	{
		vNormal=-vNormal;
	}

	pIntersection->SetNormal(vNormal);
    // Puis on la rajoute dans la liste des intersections
    return(Ray.AddIntersect(pIntersection));

}


bool CBaseFractal::AddIntersect(CRay &Ray,double Distance)
{
	//////////NON UTILISE/////////////
    return(false);
}


void CBaseFractal::Translate(const CVector& Vect)
{
	CBaseGeometry::Translate(Vect);

	////Transform bounding sphere
	m_BoundSphere.Translate(Vect);
}

void CBaseFractal::Rotate(const CVector& Vect)
{
	CBaseGeometry::Rotate(Vect);

	////Transform bounding sphere
	m_BoundSphere.Rotate(Vect);
}

void CBaseFractal::ForceEqual(CBaseGeometry &Origin)
{
	CBaseFractal *pTrueOrigin=static_cast<CBaseFractal*>(&Origin);
	if(pTrueOrigin!=NULL)
	{
		*this=*pTrueOrigin;
	}
}

#endif
