/////Etat classe : VALIDE

#ifndef	_POLYNOMIALQUARTIC
#define _POLYNOMIALQUARTIC

#include "PolyNomial.h"

class	CPolynomialQuartic : public CPolynomial
{
public:
	CPolynomialQuartic();

	///R�solution du polynome par la m�thode de FERRARI
	virtual bool	Solve(TypeVectorDouble& roots,double RootsTolerance);

// Implementation
public:
	virtual ~CPolynomialQuartic();

};

#endif