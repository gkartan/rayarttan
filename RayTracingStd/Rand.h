//******************************************************************************
//*DEFINITION DE FONCTIONS ALEATOIRES
#ifndef	_RAND
#define _RAND

#include <stdlib.h>
#include <time.h>

inline void		initrand()
{
	srand( (unsigned)time( NULL ) );
}

inline double	drand48()
{
	return((double) rand() / RAND_MAX);
}

inline short	random()
{
	return(short(((double) rand() / RAND_MAX)*256));
}

inline double nrand(void)
{
  return drand48()*2.0f-1.0f;
}


#endif