#include "stdio.h"
#include "BaseListPolynomial.h"


CBaseListPolynomial::CBaseListPolynomial()
{
}

CBaseListPolynomial::~CBaseListPolynomial()
{
}


/////////////////////////////////////////////////////////////////
///Op�rateurs
CPolynomial* CBaseListPolynomial::operator[] (long Index)
{
	return m_ListPolynomial[Index];
}

