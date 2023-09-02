//******************************************************************************
//*VERSION OPTIMISEE DES FONCTIONS HYPERBOLIQUES
//*Utilisé pour les processeurs AMD
#ifndef	_AMDTRIGOH
#define _AMDTRIGOH

#include "amath.h"

inline float	_sinh(float a)
{
	return((_exp(a)-_exp(-a))/2.0);
}

inline float	_cosh(float a)
{
	return((_exp(a)+_exp(-a))/2.0);
}


#endif