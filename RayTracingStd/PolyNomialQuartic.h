/////Etat classe : VALIDE

#ifndef	_POLYNOMIALQUARTIC
#define _POLYNOMIALQUARTIC

#include "PolyNomial.h"

class	CPolynomialQuartic : public CPolynomial
{
public:
	CPolynomialQuartic();

	///Résolution du polynome par la méthode de FERRARI
	virtual bool	Solve(TypeVectorDouble& roots,double RootsTolerance);

// Implementation
public:
	virtual ~CPolynomialQuartic();

};

#endif