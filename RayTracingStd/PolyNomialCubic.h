/////Etat classe : VALIDE

#ifndef	_POLYNOMIALCUBIC
#define _POLYNOMIALCUBIC

#include "PolyNomialQuartic.h"

class	CPolynomialCubic : public CPolynomialQuartic
{
public:
	CPolynomialCubic();

	///Résolution du polunome du 3ème ordre par la méthode trigo
	virtual bool	Solve(TypeVectorDouble& roots,double RootsTolerance);

public:
	virtual ~CPolynomialCubic();

};

#endif