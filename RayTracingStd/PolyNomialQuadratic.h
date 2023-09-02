/////Etat classe : VALIDE

/////////Polynome du 2ème ordre
#ifndef	_POLYNOMIALQUADRATIC
#define _POLYNOMIALQUADRATIC

#include "PolyNomialCubic.h"

class	CPolynomialQuadratic : public CPolynomialCubic
{
public:
	CPolynomialQuadratic();

	///Résolution du polynome du 2ème ordre par la méthode classique -> discriminant
	virtual bool	Solve(TypeVectorDouble& roots);

// Implementation
public:
	virtual ~CPolynomialQuadratic();

};

#endif