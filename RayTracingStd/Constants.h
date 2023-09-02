/////////////////////////////////////////////////////
//Utilisé pour résoudre les équations polynomial
/////////////////////////////////////////////////////

#ifndef FUDGE_FACTOR1
 #define FUDGE_FACTOR1 1.0e12
#endif
#ifndef FUDGE_FACTOR2
 #define FUDGE_FACTOR2 -1.0e-5
#endif
#ifndef FUDGE_FACTOR3 
 #define FUDGE_FACTOR3 1.0e-7
#endif
 
/* Constants. */
#ifndef M_PI
#define M_PI   3.1415926535897932384626
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

#define TWO_M_PI_3  2.0943951023931954923084
#define FOUR_M_PI_3 4.1887902047863909846168

#define M_127_PI 127.0/M_PI
#define M_PI_127 M_PI/127.0

/* Smallest relative error we want. */
#define RELERROR 1.0e-12

#define MAX_ORDER 15

#define MAX_DISTANCE 1.0e7

#define EPSILON 1.0e-10 ///Zero 
#define TEST_EPSILON 1.0e-6 ///Zero on certain evaluations

#define MAX_HUGE_OBJECT 2.0e10

#ifndef PI_DIV_180
#define PI_DIV_180 0.01745329251994329576
#endif

#ifndef INV_PI_180
#define INV_PI_180 180.0 / M_PI
#endif


#define DEFAULT_PHONGSIZE	40
#define DEFAULT_BOUNDSIZE	2		///taille de la sphère englobante par défaut pour les fractales

///////////////////Default keys
#define DEFAULT_TIME	912345671
#define DEFAULT_KEYTIME 1223650215
#define KEY_MULTVALUE	235
#define TRENTEJOURSSEC	2592000

//////////////Default algorithm values
#define DEFAULT_ALGORITHM_THRESHOLD 0.5
#define DEFAULT_ALGORITHM_DEPTH 2

////Definition des longueurs d'ondes en nm
#define WAVELENGTH_RED		650
#define WAVELENGTH_GREEN	450
#define WAVELENGTH_BLUE		535
#define TYPE_RED			0
#define TYPE_GREEN			1
#define TYPE_BLUE			2