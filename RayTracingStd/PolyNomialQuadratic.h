/////Etat classe : VALIDE

/////////Polynome du 2�me ordre
#ifndef	_POLYNOMIALQUADRATIC
#define _POLYNOMIALQUADRATIC

#include "PolyNomialCubic.h"

class	CPolynomialQuadratic : public CPolynomialCubic
{
public:
	CPolynomialQuadratic();

	///R�solution du polynome du 2�me ordre par la m�thode classique -> discriminant
	virtual bool	Solve(TypeVectorDouble& roots);

// Implementation
public:
	virtual ~CPolynomialQuadratic();

};

#endif