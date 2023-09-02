/////Etat classe : VALIDE
#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#pragma warning(disable : 4530)

#include "PolyNomial.h"

class	CBaseListPolynomial
{
public:
	CBaseListPolynomial();

protected:
	TypeVectorPolynomial	m_ListPolynomial;

public:
	CPolynomial*		  operator[] (long Index);

// Implementation
public:
	virtual ~CBaseListPolynomial();

};