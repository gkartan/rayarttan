#ifndef	_CBASEHYPERFONCTION
#define _CBASEHYPERFONCTION

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include <complex>

template<class Type_Elem>
class CBaseHyperFonction
{
// Construction
public:
	CBaseHyperFonction();

	inline  virtual bool	GetOptimisation()=0;
// Operations
public:

	virtual void sin(std::complex<Type_Elem>&,std::complex<Type_Elem>&)		const=0;
	virtual void asin(std::complex<Type_Elem>&,std::complex<Type_Elem>&)	const=0;
	virtual void cos(std::complex<Type_Elem>&,std::complex<Type_Elem>&)		const=0;
	virtual void acos(std::complex<Type_Elem>&,std::complex<Type_Elem>&)	const=0;
	virtual void tan(std::complex<Type_Elem>&,std::complex<Type_Elem>&)		const=0;
	virtual void atan(std::complex<Type_Elem>&,std::complex<Type_Elem>&)	const=0;
	virtual void cotan(std::complex<Type_Elem>&,std::complex<Type_Elem>&)	const=0;
	virtual void acotan(std::complex<Type_Elem>&,std::complex<Type_Elem>&)	const=0;
	virtual void exp(std::complex<Type_Elem>&,std::complex<Type_Elem>&)		const=0;
	virtual void log(std::complex<Type_Elem>&,std::complex<Type_Elem>&)		const=0;

// Implementation
public:
	virtual ~CBaseHyperFonction();
};

template<class Type_Elem>
CBaseHyperFonction<Type_Elem>::CBaseHyperFonction<Type_Elem>()
{
}

template<class Type_Elem>
CBaseHyperFonction<Type_Elem>::~CBaseHyperFonction<Type_Elem>()
{
}

#endif