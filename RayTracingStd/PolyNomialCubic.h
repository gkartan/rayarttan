/////Etat classe : VALIDE

#ifndef	_POLYNOMIALCUBIC
#define _POLYNOMIALCUBIC

#include "PolyNomialQuartic.h"

class	CPolynomialCubic : public CPolynomialQuartic
{
public:
	CPolynomialCubic();

	///R�solution du polunome du 3�me ordre par la m�thode trigo
	virtual bool	Solve(TypeVectorDouble& roots,double RootsTolerance);

public:
	virtual ~CPolynomialCubic();

};

#endif