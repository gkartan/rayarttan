#include <stdio.h>
#include <cmath>
#include "PolyNomialQuadratic.h"

CPolynomialQuadratic::CPolynomialQuadratic()
{
	m_Order=2;
}


CPolynomialQuadratic::~CPolynomialQuadratic()
{
}


/////////////////////////////////////////////////////////////
//Resolution Polynome du second degré 
//    x[0] * x^2 + x[1] * x + x[2] = 0.
//Méthode classique par discriminant
bool	CPolynomialQuadratic::Solve(TypeVectorDouble& roots)
{
  double t, a, b, c;

  a = m_Coeff[2];
  b = -m_Coeff[1];
  c = m_Coeff[0];

  ///Polynome linéaire
  if (a == 0.0)
  {
    if (b == 0.0)
    {
      return(false);
    }

	double dRoots=c / b;
    roots.push_back(dRoots);

    return(true);
  }

  double delta = b * b - 4.0 * a * c;

  /* Treat values of d around 0 as 0. */
  if ((delta > -EPSILON) && (delta < EPSILON))
  {
    double dRoots = 0.5 * b / a;
    roots.push_back(dRoots);

    return(true);
  }
  else
  {
    if (delta < 0.0)
    {
      return(false);
    }
  }

  delta = sqrt(delta);

  t = 2.0 * a;

  double dRoots1 = (b + delta) / t;
  double dRoots2 = (b - delta) / t;

  roots.push_back(dRoots1);
  roots.push_back(dRoots2);

  return(true);
}

