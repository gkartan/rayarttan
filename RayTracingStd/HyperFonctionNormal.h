#ifndef	_CHYPERFONCTIONNORMAL
#define _CHYPERFONCTIONNORMAL

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include <valarray>
#include <complex>
#include <cmath>
#include "BaseHyperFonction.h"

template<class Type_Elem>
class CHyperFonctionNormal : public CBaseHyperFonction<Type_Elem>
{
// Construction
public:
	CHyperFonctionNormal();

	inline  virtual bool	GetOptimisation() {return false;};
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

	/*******************Liste des fonctions spéciales dans les complexes*******************/	
	/***********fonctions non implémentées dans la stl********************************/
	std::complex<Type_Elem>	tan(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	cotan(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	asin(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	acos(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	atanh(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	atan(const std::complex<Type_Elem>&a)	const;
	std::complex<Type_Elem>	acotan(const std::complex<Type_Elem>&a) const;
	/*******************Fin Liste des fonctions spéciales dans les complexes*******************/	
// Implementation
public:
	virtual ~CHyperFonctionNormal();
};

template<class Type_Elem>
CHyperFonctionNormal<Type_Elem>::CHyperFonctionNormal<Type_Elem>()
{
}

template<class Type_Elem>
CHyperFonctionNormal<Type_Elem>::~CHyperFonctionNormal<Type_Elem>()
{
}

template<class Type_Elem>
void	CHyperFonctionNormal<Type_Elem>::sin(std::complex<Type_Elem> &a,
											 std::complex<Type_Elem> &b) const
{
	a=std::sin(a);
	b=std::sin(b);
}

template<class Type_Elem>
void	CHyperFonctionNormal<Type_Elem>::cos(std::complex<Type_Elem> &a,
											 std::complex<Type_Elem> &b) const
{
	a=std::cos(a);
	b=std::cos(b);
}

template<class Type_Elem>
void	CHyperFonctionNormal<Type_Elem>::tan(std::complex<Type_Elem> &a,
											 std::complex<Type_Elem> &b) const
{
	a=tan(a);
	b=tan(b);
}

template<class Type_Elem>
void	CHyperFonctionNormal<Type_Elem>::cotan(std::complex<Type_Elem> &a,
											   std::complex<Type_Elem> &b) const
{
	a=cotan(a);
	b=cotan(b);
}

template<class Type_Elem>
void	CHyperFonctionNormal<Type_Elem>::exp(std::complex<Type_Elem> &a,
											 std::complex<Type_Elem> &b) const
{
	a=std::exp(a);
	b=std::exp(b);
}

template<class Type_Elem>
void	CHyperFonctionNormal<Type_Elem>::log(std::complex<Type_Elem> &a,
											 std::complex<Type_Elem> &b) const
{
	a=std::log(a);
	b=std::log(b);
}

template<class Type_Elem>
void CHyperFonctionNormal<Type_Elem>::asin(std::complex<Type_Elem> &a,
										   std::complex<Type_Elem> &b) const
{
	a=asin(a);
	b=asin(b);
}

template<class Type_Elem>
void CHyperFonctionNormal<Type_Elem>::acos(std::complex<Type_Elem> &a,
										   std::complex<Type_Elem> &b) const
{
	a=acos(a);
	b=acos(b);
}

template<class Type_Elem>
void CHyperFonctionNormal<Type_Elem>::atan(std::complex<Type_Elem> &a,
										   std::complex<Type_Elem> &b) const
{
	a=atan(a);
	b=atan(b);
}

template<class Type_Elem>
void CHyperFonctionNormal<Type_Elem>::acotan(std::complex<Type_Elem> &a,
											 std::complex<Type_Elem> &b) const
{
	a=acotan(a);
	b=acotan(b);
}



/*************************************************************************/
/* Definitions des fonctions spéciales dans les complexes */
/* Ces fonctions ne sont pas implémentées dans la stl*/
/* Comme elles ne sont utilisées qu'ici leurs définitions ne fait dans cette classe
/* A FAIRE ----------> exporter ces fonctions dans une classe spéciale
/**************************************************************************/
template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionNormal<Type_Elem>::tan(const std::complex<Type_Elem> &a) const
{
	return(std::operator/(std::sin(a),std::cos(a)));
}

template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionNormal<Type_Elem>::cotan(const std::complex<Type_Elem> &a) const
{
	return(std::operator/(std::cos(a),std::sin(a)));
}


/* rz=Arcsin(z)=-i*Log{i*z+sqrt(1-z*z)} */
template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionNormal<Type_Elem>::asin(const std::complex<Type_Elem>&a) const
{
	std::complex<Type_Elem> temp1(std::operator*(a,a));

	temp1=std::complex<Type_Elem>(1-temp1.real(),-temp1.imag());
	temp1=std::sqrt(temp1);
	temp1+=std::complex<Type_Elem>(-a.imag(),a.real());

	temp1=std::log(temp1);

	return(std::complex<Type_Elem>(temp1.imag(),-temp1.real()));
}

template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionNormal<Type_Elem>::acos(const std::complex<Type_Elem>&a) const
{
	std::complex<Type_Elem> temp(std::operator*(a,a));
	temp-=1;
	temp=std::sqrt(temp);
	temp+=a;
	temp=std::log(temp);

	return(std::complex<Type_Elem>(temp.imag(),-temp.real()));
}

/* rz=Arctanh(z)=1/2*Log{(1+z)/(1-z)} */
template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionNormal<Type_Elem>::atanh(const std::complex<Type_Elem>&a) const
{
	if(a.real()==0.0)
	{
		return(std::complex<Type_Elem>(0,::atan(a.imag())));
	} else
	{
		if(fabs(a.real()) == 1.0 && a.imag() == 0.0)
		{
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
			temp=std::log(temp);
			return(std::complex<Type_Elem>(.5*temp.real(),.5*temp.imag()));
		}
	}
}

/* rz=Arctan(z)=i/2*Log{(1-i*z)/(1+i*z)} */
template<class Type_Elem>
std::complex<Type_Elem>		CHyperFonctionNormal<Type_Elem>::atan(const std::complex<Type_Elem>&a) const
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
std::complex<Type_Elem>		CHyperFonctionNormal<Type_Elem>::acotan(const std::complex<Type_Elem>&a) const
{
	return(atan(std::operator/(std::complex<Type_Elem>(1,0),a)));
}
/*************************************************************************************/
/*************************************************************************************/

#endif