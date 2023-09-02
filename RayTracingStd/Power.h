//******************************************************************************
//*VERSION OPTIMISEE DE LA FONCTION PUISSANCE jusqu'à la puissance 6
#ifndef	_POWER
#define _POWER

#include <cmath>

#define SQR(a)  ((a)*(a))

#define SIGN(a) (((a) >= 0.0) ? 1.0 : -1.0)

inline double power(double x, double  e)
{
  register int i;

  double b=x;

  i = (int)e;

  /* Test if we have an integer power. */

  if (e == (double)i)
  {
    switch (i)
    {
      case 0: return(1.0);

      case 1: return(b);

      case 2: return(SQR(b));

      case 3: return(SQR(b) * b);

      case 4: b *= b; return(SQR(b));

      case 5: b *= b; return(SQR(b) * x);

      case 6: b *= b; return(SQR(b) * b);

      default: return(pow(x, e));
    }
  }
  else
  {
    return(pow(x, e));
  }
}

#endif