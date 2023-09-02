/////////////////////////////////////////////////////
///Definition d'un certain nombre de macros
/////////////////////////////////////////////////////
#include "Constants.h"

#define CONVERT_COLORIHM(a) (short(a*255))	//conversion pour l'ihm
#define CONVERT_COLORENG(a)	(float(a/255.0))  //conversion pour le moteur de rendu (engine)

#define CONVERT_RADTODEG(a) (a*PI_DIV_180)
#define CONVERT_DEGTORAD(a) (a/PI_DIV_180)

#define MAX(a,b)	(a<b)?a:b
#define EXCHANGE(a,b) double c=b;b=a;a=c;
