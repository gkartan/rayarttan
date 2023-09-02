#include <stdio.h>
#include <cmath>
#include "PolyNomialQuartic.h"
#include "PolyNomialCubic.h"	///ATTENTION rebouclage de dependences -> appel le solveur d'un cubic

CPolynomialQuartic::CPolynomialQuartic()
{
	m_Order=0;
}


CPolynomialQuartic::~CPolynomialQuartic()
{
}

/////////////////////////////////////////////////////////
///Methode de FERRARI
bool	CPolynomialQuartic::Solve(TypeVectorDouble& roots,double RootsTolerance)
{
	////Test racines
	if (RootsTolerance > 0.0)
	{
		if ((m_Coeff[3] != 0.0) && (fabs(m_Coeff[4]/m_Coeff[3]) < RootsTolerance))
		{
			CPolynomialCubic cubic;
			cubic.SetCoeff(3,GetCoeff(3));
			cubic.SetCoeff(2,GetCoeff(2));
			cubic.SetCoeff(1,GetCoeff(1));
			cubic.SetCoeff(0,GetCoeff(0));
			return(cubic.Solve(roots,RootsTolerance));
		}
	}

  double a0, a1, y, d1, x1, t1, t2;
  double c0, c1, c2, c3, c4, d2, q1, q2;
  int i;

  c0 = m_Coeff[4];

  if (c0 != 1.0)
  {
    c1 = m_Coeff[3] / c0;
    c2 = m_Coeff[2] / c0;
    c3 = m_Coeff[1] / c0;
    c4 = m_Coeff[0] / c0;
  }
  else
  {
    c1 = m_Coeff[3];
    c2 = m_Coeff[2];
    c3 = m_Coeff[1];
    c4 = m_Coeff[0];
  }

  /* The first step is to take the original equation:

       x^4 + b*x^3 + c*x^2 + d*x + e = 0

     and rewrite it as:

       x^4 + b*x^3 = -c*x^2 - d*x - e,

     adding (b*x/2)^2 + (x^2 + b*x/2)y + y^2/4 to each side gives a
     perfect square on the lhs:

       (x^2 + b*x/2 + y/2)^2 = (b^2/4 - c + y)x^2 + (b*y/2 - d)x + y^2/4 - e

     By choosing the appropriate value for y, the rhs can be made a perfect
     square also.  This value is found when the rhs is treated as a quadratic
     in x with the discriminant equal to 0.  This will be true when:

       (b*y/2 - d)^2 - 4.0 * (b^2/4 - c*y)*(y^2/4 - e) = 0, or

       y^3 - c*y^2 + (b*d - 4*e)*y - b^2*e + 4*c*e - d^2 = 0.

     This is called the resolvent of the quartic equation.  */

  a0 = 4.0 * c4;

  CPolynomialCubic	cubic;
  cubic.SetCoeff(3,1);
  cubic.SetCoeff(2,-1.0 * c2);
  cubic.SetCoeff(1,c1 * c3 - a0);
  cubic.SetCoeff(0,a0 * c2 - c1 * c1 * c4 - c3 * c3);

  TypeVectorDouble cubicroots;
  cubic.Solve(cubicroots,RootsTolerance);

  if(cubicroots.size()>0)
  {
    y = cubicroots[0];
  } else 
	  return false;

  /* What we are left with is a quadratic squared on the lhs and a
     linear term on the right.  The linear term has one of two signs,
     take each and add it to the lhs.  The form of the quartic is now:

       a' = b^2/4 - c + y,    b' = b*y/2 - d, (from rhs quadritic above)

       (x^2 + b*x/2 + y/2) = +sqrt(a'*(x + 1/2 * b'/a')^2), and
       (x^2 + b*x/2 + y/2) = -sqrt(a'*(x + 1/2 * b'/a')^2).

     By taking the linear term from each of the right hand sides and
     adding to the appropriate part of the left hand side, two quadratic
     formulas are created.  By solving each of these the four roots of
     the quartic are determined.
  */

  i = 0;

  a0 = c1 / 2.0;
  a1 = y / 2.0;

  t1 = a0 * a0 - c2 + y;

  if (t1 < 0.0)
  {
    if (t1 > FUDGE_FACTOR2)
    {
      t1 = 0.0;
    }
    else
    {
      /* First Special case, a' < 0 means all roots are complex. */

      return(false);
      }
    }

  if (t1 < FUDGE_FACTOR3)
{
    /* Second special case, the "x" term on the right hand side above
       has vanished.  In this case:

         (x^2 + b*x/2 + y/2) = +sqrt(y^2/4 - e), and
         (x^2 + b*x/2 + y/2) = -sqrt(y^2/4 - e).  */

    t2 = a1 * a1 - c4;

    if (t2 < 0.0)
    {
      return(false);
    }

    x1 = 0.0;
    d1 = sqrt(t2);
  }
  else
  {
    x1 = sqrt(t1);
    d1 = 0.5 * (a0 * y - c3) / x1;
  }

  /* Solve the first quadratic */

  q1 = -a0 - x1;
  q2 = a1 + d1;
  d2 = q1 * q1 - 4.0 * q2;

  if (d2 >= 0.0)
{
    d2 = sqrt(d2);

    double dRoots0 = 0.5 * (q1 + d2);
    double dRoots1 = 0.5 * (q1 - d2);

	roots.push_back(dRoots0);
	roots.push_back(dRoots1);

    i = 2;
  }

  /* Solve the second quadratic */

  q1 = q1 + x1 + x1;
  q2 = a1 - d1;
  d2 = q1 * q1 - 4.0 * q2;

  if (d2 >= 0.0)
{
    d2 = sqrt(d2);

    double dRoots0 = 0.5 * (q1 + d2);
    double dRoots1 = 0.5 * (q1 - d2);

	roots.push_back(dRoots0);
	roots.push_back(dRoots1);
  }

  return(true);
}



