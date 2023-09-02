#include <stdio.h>
#include "Power.h"
#include "PolyNomialQuadratic.h"

CPolynomialCubic::CPolynomialCubic()
{
	m_Order=3;
}


CPolynomialCubic::~CPolynomialCubic()
{
}

/////////////////////////////////////////////////////////
//Resolution Polynome du troisieme degré 
///     x[0] * x^3 + x[1] * x^2 + x[2] * x + x[3] = 0.
///Methode trigonométrique
bool	CPolynomialCubic::Solve(TypeVectorDouble& roots,double RootsTolerance)
{
	////Test racines
	if (RootsTolerance > 0.0)
	{
		if ((m_Coeff[2] != 0.0) && (fabs(m_Coeff[3]/m_Coeff[2]) < RootsTolerance))
		{
			CPolynomialQuadratic quadratic;
			quadratic.SetCoeff(2,GetCoeff(2));
			quadratic.SetCoeff(1,GetCoeff(1));
			quadratic.SetCoeff(0,GetCoeff(0));
			return(quadratic.Solve(roots));
		}
	}

  double Q, R, Q3, R2, sQ, d, an, theta;
  double A2, a0, a1, a2, a3;

  a0 = m_Coeff[3];

	if (a0 != 1.0)
	{
	  a1 = m_Coeff[2] / a0;
	  a2 = m_Coeff[1] / a0;
	  a3 = m_Coeff[0] / a0;
	}
	else
	{
	  a1 = m_Coeff[2];
	  a2 = m_Coeff[1];
	  a3 = m_Coeff[0];
	}

  A2 = a1 * a1;

  Q = (A2 - 3.0 * a2) / 9.0;

  /* Modified to save some multiplications and to avoid a floating point
     exception that occured with DJGPP and full optimization. [DB 8/94] */

  R = (a1 * (A2 - 4.5 * a2) + 13.5 * a3) / 27.0;

  Q3 = Q * Q * Q;

  R2 = R * R;

  d = Q3 - R2;

  an = a1 / 3.0;

  if (d >= 0.0)
  {
    /* Three real roots. */

    d = R / sqrt(Q3);

    theta = acos(d) / 3.0;

    sQ = -2.0 * sqrt(Q);

    double dRoots1 = sQ * cos(theta) - an;
    double dRoots2 = sQ * cos(theta + TWO_M_PI_3) - an;
    double dRoots3 = sQ * cos(theta + FOUR_M_PI_3) - an;

    roots.push_back(dRoots1);
    roots.push_back(dRoots2);
    roots.push_back(dRoots3);


    return(true);
  }
  else
  {
    sQ = power(sqrt(R2 - Q3) + fabs(R), 1.0 / 3.0);

    if (R < 0)
    {
      double dRoots1 = (sQ + Q / sQ) - an;
	  roots.push_back(dRoots1);
    }
    else
    {
      double dRoots1 = -(sQ + Q / sQ) - an;
	  roots.push_back(dRoots1);
    }

    return(1);
  }
}

