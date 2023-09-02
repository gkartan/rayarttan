#ifndef	_CHYPERFONCTIONAMD
#define _CHYPERFONCTIONAMD

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include <valarray>
#include <complex>
#include <cmath>
#include "BaseHyperFonction.h"
#include "amath.h"
#include "TrigohAMD.h"

template<class Type_Elem>
class CHyperFonctionAMD : public CBaseHyperFonction<Type_Elem>
{
// Construction
public:
	CHyperFonctionAMD();

	inline  virtual bool	GetOptimisation() {return true;};
// Operations
public:

	virtual void sin(std::complex<Type_Elem>&,std::complex<Type_Elem>&)		const;
	virtual void asin(std::complex<Type_Elem>&,std::complex<Type_Elem>&)	const;
	virtual void cos(std::complex<Type_Elem>&,std::complex<Type_Elem>&)		const;
	virtual void acos(std::complex<Type_Elem>&,std::complex<Type_Elem>&)	const;
	virtual void tan(std::complex<Type_Elem>&,std::complex<Type_Elem>&)		const;
	virtual void atan(std::complex<Type_Elem>&,std::complex<Type_Elem>&)	const;
	virtual void cotan(std::complex<Type_Elem>&,std::complex<Type_Elem>&)	const;
	virtual void acotan(std::complex<Type_Elem>&,std::complex<Type_Elem>&)	const;
	virtual void exp(std::complex<Type_Elem>&,std::complex<Type_Elem>&)		const;
	virtual void log(std::complex<Type_Elem>&,std::complex<Type_Elem>&)		const;


	std::complex<Type_Elem> log(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem> exp(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem> cos(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem> sin(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem> tan(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem> cotan(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	asin(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	acos(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	atanh(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	atan(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	acotan(const std::complex<Type_Elem>&a) const;

// Implementation
public:
	virtual ~CHyperFonctionAMD();
};

template<class Type_Elem>
CHyperFonctionAMD<Type_Elem>::CHyperFonctionAMD<Type_Elem>()
{
}

template<class Type_Elem>
CHyperFonctionAMD<Type_Elem>::~CHyperFonctionAMD<Type_Elem>()
{
}

/*******************************************************************************/
/***********Definition des fonctions virtuelles********************************/
/*******************************************************************************/
template<class Type_Elem>
void	CHyperFonctionAMD<Type_Elem>::sin(std::complex<Type_Elem> &a,
										  std::complex<Type_Elem> &b) const
{
	a=sin(a);
	b=sin(b);
}

template<class Type_Elem>
void	CHyperFonctionAMD<Type_Elem>::cos(std::complex<Type_Elem> &a,
										  std::complex<Type_Elem> &b) const
{
	a=cos(a);
	b=cos(b);
}

template<class Type_Elem>
void	CHyperFonctionAMD<Type_Elem>::tan(std::complex<Type_Elem> &a,
										  std::complex<Type_Elem> &b) const
{
	a=tan(a);
	b=tan(b);
}

template<class Type_Elem>
void	CHyperFonctionAMD<Type_Elem>::cotan(std::complex<Type_Elem> &a,
											 std::complex<Type_Elem> &b) const
{
	a=cotan(a);
	b=cotan(b);
}

template<class Type_Elem>
void	CHyperFonctionAMD<Type_Elem>::exp(std::complex<Type_Elem> &a,
										  std::complex<Type_Elem> &b) const
{
	a=exp(a);
	b=exp(b);
}

template<class Type_Elem>
void	CHyperFonctionAMD<Type_Elem>::log(std::complex<Type_Elem> &a,
										  std::complex<Type_Elem> &b) const
{
	a=log(a);
	b=log(b);
}

template<class Type_Elem>
void CHyperFonctionAMD<Type_Elem>::asin(std::complex<Type_Elem> &a,
										std::complex<Type_Elem> &b) const
{
	a=asin(a);
	b=asin(b);
}

template<class Type_Elem>
void CHyperFonctionAMD<Type_Elem>::acos(std::complex<Type_Elem> &a,
										std::complex<Type_Elem> &b) const
{
	a=acos(a);
	b=acos(b);
}

template<class Type_Elem>
void CHyperFonctionAMD<Type_Elem>::atan(std::complex<Type_Elem> &a,
										std::complex<Type_Elem> &b) const
{
	a=atan(a);
	b=atan(b);
}

template<class Type_Elem>
void CHyperFonctionAMD<Type_Elem>::acotan(std::complex<Type_Elem> &a,
										  std::complex<Type_Elem> &b) const
{
	a=acotan(a);
	b=acotan(b);
}

/***********Fin fonctions virtuelles********************************/
/******************************************************************************/


/////////////////////////////////////////////////////////////////////////////
///Fonction : sin
///
///Remarque : cette fonction a été optimisé pour les processeurs AMD
///			  perte de précision --> on cast en float
/////////////////////////////////////////////////////////////////////////////
template<class Type_Elem>
std::complex<Type_Elem> CHyperFonctionAMD<Type_Elem>::sin(const std::complex<Type_Elem> &a) const
{
  float	Res[2];
  ::_sincos(float(a.real()),Res);	///fonction optimisé MMX
  return(std::complex<Type_Elem>(Res[1] * ::_cosh(a.imag()),
								 Res[0] * ::_sinh(a.imag())));
} 

/////////////////////////////////////////////////////////////////////////////
///Fonction : cos
///
///Remarque : cette fonction a été optimisé pour les processeurs AMD
///			  perte de précision --> on cast en float
/////////////////////////////////////////////////////////////////////////////
template<class Type_Elem>
std::complex<Type_Elem> CHyperFonctionAMD<Type_Elem>::cos(const std::complex<Type_Elem> &a) const
{
  float	Res[2];
  ::_sincos(float(a.real()),Res);	///fonction optimisé MMX
  return(std::complex<Type_Elem>(Res[1] * ::_cosh(a.imag()),
								 -Res[0] * ::_sinh(a.imag())));
} 

/////////////////////////////////////////////////////////////////////////////
///Fonction : exp
///
///Remarque : cette fonction a été optimisé pour les processeurs AMD
///			  perte de précision --> on cast en float
/////////////////////////////////////////////////////////////////////////////
template<class Type_Elem>
std::complex<Type_Elem> CHyperFonctionAMD<Type_Elem>::exp(const std::complex<Type_Elem> &a) const
{
  float expx(::_exp(a.real()));
  return(std::complex<Type_Elem>(expx * ::_cos(a.imag()),
								 expx * ::_sin(a.imag())));
} 

/////////////////////////////////////////////////////////////////////////////
///Fonction : log
///
///Remarque : cette fonction a été optimisé pour les processeurs AMD
///			  perte de précision --> on cast en float
/////////////////////////////////////////////////////////////////////////////
template<class Type_Elem>
std::complex<Type_Elem> CHyperFonctionAMD<Type_Elem>::log(const std::complex<Type_Elem> &a) const
{
  float mod(::_sqrt(a.real() * a.real() + a.imag() * a.imag()));
  return(std::complex<Type_Elem>(::_log(mod),
								 ::_atan2(a.imag(),a.real())));
} 

template<class Type_Elem>
std::complex<Type_Elem> CHyperFonctionAMD<Type_Elem>::tan(const std::complex<Type_Elem> &a) const
{
	return(std::operator/(sin(a),cos(a)));
}

template<class Type_Elem>
std::complex<Type_Elem> CHyperFonctionAMD<Type_Elem>::cotan(const std::complex<Type_Elem> &a) const
{
	return(std::operator/(cos(a),sin(a)));
}


/******************************************************************/
/**Liste des fonctions identiques  Normal**/
/**ATTENTION --------> FONCTIONS DOUBLONS ------> A REVOIR

/* rz=Arcsin(z)=-i*Log{i*z+sqrt(1-z*z)} */
template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionAMD<Type_Elem>::asin(const std::complex<Type_Elem>&a) const
{
	std::complex<Type_Elem> temp1(a*a);

	temp1=std::complex<Type_Elem>(1-temp1.real(),-temp1.imag());
	temp1=std::sqrt(temp1);
	temp1+=std::complex<Type_Elem>(-a.imag(),a.real());

	temp1=std::log(temp1);

	return(std::complex<Type_Elem>(temp1.imag(),-temp1.real()));
}

template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionAMD<Type_Elem>::acos(const std::complex<Type_Elem>&a) const
{
	std::complex<Type_Elem> temp(a*a);
	temp-=1;
	temp=std::sqrt(temp);
	temp+=a;
	temp=std::log(temp);

	return(std::complex<Type_Elem>(temp.imag(),-temp.real()));
}

/* rz=Arctanh(z)=1/2*Log{(1+z)/(1-z)} */
template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionAMD<Type_Elem>::atanh(const std::complex<Type_Elem>&a) const
{
	if(a.real()==0.0)
	{
		return(std::complex<Type_Elem>(0,::atan(a.imag())));
	} else
	{
		if(fabs(a.real()) == 1.0 && a.imag() == 0.0)
		{
			//_TRACE_ERROR("Error dans Atanh -> valeurs impossibles");
			return(std::complex<Type_Elem>(0,0)); ////error
		} else
		if(fabs(a.real())<1.0 && a.imag() == 0.0)
		{
			return(std::complex<Type_Elem>(::log((1+a.real())/(1-a.real()))/2.0,0));
		} else
		{
			std::complex<Type_Elem> temp1(1+a.real(),a.imag());
			std::complex<Type_Elem> temp2(1-a.real(),-a.imag());

			std::complex<Type_Elem> temp=std::operator/(temp,temp2);
			temp=log(temp);
			return(std::complex<Type_Elem>(.5*temp.real(),.5*temp.imag()));
		}
	}
}

/* rz=Arctan(z)=i/2*Log{(1-i*z)/(1+i*z)} */
template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionAMD<Type_Elem>::atan(const std::complex<Type_Elem>&a) const
{

	if(a.real()==0.0 && a.imag()==0.0)
		return(std::complex<Type_Elem>(0,0));
	else
	if(a.real()!=0.0 && a.imag()==0.0)
		return(std::complex<Type_Elem>(::atan(a.real()),0));
	else
	if(a.real()==0.0 && a.imag()!=0.0)
	{
		std::complex<Type_Elem> temp(a.imag(),0);
		temp=atanh(temp);
		return(std::complex<Type_Elem>(-temp.imag(),temp.real()));
	}
	else
	{
		std::complex<Type_Elem> temp1(1+a.imag(),-a.real());
		std::complex<Type_Elem> temp2(1-a.imag(),a.real());

		std::complex<Type_Elem> temp=std::operator/(temp1,temp2);
		temp=std::log(temp);
		return(std::complex<Type_Elem>(-temp.imag()*.5,temp.real()*.5));
	}

}

/* acotan(a)=atan(1/a)*/
template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionAMD<Type_Elem>::acotan(const std::complex<Type_Elem>&a) const
{
	return(atan(std::operator/(std::complex<Type_Elem>(1,0),a)));
}


#endif