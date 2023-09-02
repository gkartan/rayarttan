/////Etat classe : ESSAI EN COURS

#ifndef _FRACTALZ2
#define _FRACTALZ2

#include "Fractal.h"
#include "Constants.h"

template <class T>
class CFractalZ2 : public CFractal<T>
{
// Construction
public:
	inline CFractalZ2();
	inline CFractalZ2(const T &InitVal,long NbIt,double,double);

public:
	inline virtual CFractalZ2& operator=(CFractalZ2&);

protected:
	inline  virtual CVector	Normal(const CCoord &coord);

private:
	inline	bool	Estimator(CRay&,double Dist);
	inline 	bool	D_Estimator(const CCoord&,double &Dist);
	virtual bool	Derivate() {m_sExprDerivate=std::string("2*Z"); return true;}; //inutile de dériver --> les expressions sont en dur

// Implementation
public:
	inline virtual ~CFractalZ2();

public:
	inline virtual CBaseGeometry*	Instantiate();		//instancie un nouvel objet de ce type
};

template<class T>
CFractalZ2<T>::CFractalZ2<T>()
:CFractal<T>()
{
}

template<class T>
CFractalZ2<T>::CFractalZ2<T>(const T& InitVal,long NbIt,double precision,double Angle)
{
	m_sExpr=std::string("Z^2+@init");
	m_sExprDerivate=std::string("2*Z");
	m_DistanceTolerance=1e-7;
	m_FractalTolerance=1e-8;
	m_InitValue=InitVal;
	m_NbIteration=NbIt;
	m_MaxLimits=16;
	m_Increment=precision;
	m_BoundSphere=CSphere(CCoord(0,0,0),2);
	m_Angle=Angle;
}

template<class T>
CFractalZ2<T>::~CFractalZ2<T>()
{
}

template<class T>
CFractalZ2<T>&	CFractalZ2<T>::operator=(CFractalZ2<T>	&Origin)
{
	CFractal<T>::operator=(Origin);

	return (*this);
}


//////////////////////////////////////////
///Normale à la fractale
///On calcule la normale itérativement car la fractale est indérivable
///Calcul du tenseur itérativement
template<class T>
CVector	CFractalZ2<T>::Normal(const CCoord &vInit)
{
	T	QInit(vInit.GetX(),vInit.GetY(),vInit.GetZ(),0);
	T	Qn(vInit.GetX(),vInit.GetY(),vInit.GetZ(),0);
	T	Tx(1,0,0,0);
	T	Ty(0,1,0,0);
	T	Tz(0,0,1,0);


	if(m_Angle!=0.0)
	{
		///Rotation de la fractale dans le plan complexe
		T	ei_theta(cos(m_Angle),sin(m_Angle),sin(m_Angle),sin(m_Angle));
		T	ei_mtheta(cos(-m_Angle),sin(-m_Angle),sin(-m_Angle),sin(-m_Angle));

		T	Constant=ei_theta*m_InitValue;

		for(int i=1;i<=m_NbIteration;i++)
		{
			Tx*=Qn;
			Ty*=Qn;
			Tz*=Qn;
			Tx*=2;
			Ty*=2;
			Tz*=2;
			Qn.Sqr();
			Qn.Mult(ei_mtheta);
			Qn.Add(Constant);
		}
	} else {
		////Traditionnel
		for(int i=1;i<=m_NbIteration;i++)
		{
			Tx*=Qn;
			Ty*=Qn;
			Tz*=Qn;
			Tx*=2;
			Ty*=2;
			Tz*=2;
			Qn.Sqr();
			Qn.Add(m_InitValue);
		}
	}

	CVector Res(Tx.Scalar(Qn,AXE_X),
				Ty.Scalar(Qn,AXE_Y),
				Tz.Scalar(Qn,AXE_Z));

	Res.Normalize();

	return(Res);
}


////////////////////////////////////////////////////
//Première estimation grossière de la distance à la fractale
//Parcours le rayon par pas de 0.1
template<class T>
bool	CFractalZ2<T>::Estimator(CRay &Ray,
							     double Dist)
{

  CVector &Scale=Ray.GetDirect()*Dist;
  CCoord  &Init=Ray.GetOrigin()+Scale;

  T			    QInit(Init.GetX(),
				   Init.GetY(),
				   Init.GetZ(),
				   0);
  T				Qn(Init.GetX(),
				   Init.GetY(),
				   Init.GetZ(),
				   0);

  unsigned long NumIteration=0;

  if(m_Angle!=0.0)
  {
	  T				ei_theta(cos(m_Angle),sin(m_Angle),sin(m_Angle),sin(m_Angle));
	  T				ei_mtheta(cos(-m_Angle),sin(-m_Angle),sin(-m_Angle),sin(-m_Angle));

	  T				Constant=ei_theta*m_InitValue;


	  while(Qn.norm2()<m_MaxLimits && NumIteration<m_NbIteration)
	  {
	  		Qn.Sqr();
			Qn.Mult(ei_mtheta);
			Qn.Add(Constant);
			NumIteration++;
	  }
  } else {
	  while(Qn.norm2()<m_MaxLimits && NumIteration<m_NbIteration)
	  {
	  		Qn.Sqr();
			Qn.Add(m_InitValue);
			NumIteration++;
	  }
  }

  if(NumIteration==m_NbIteration)
  {
	  return(true);
  } 

  return(false);
}

template<class T>
CBaseGeometry*	CFractalZ2<T>::Instantiate()
{
	return new CFractalZ2<T>;
}

#endif



