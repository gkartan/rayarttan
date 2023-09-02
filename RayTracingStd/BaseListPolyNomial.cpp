#include "stdio.h"
#include "BaseListPolynomial.h"


CBaseListPolynomial::CBaseListPolynomial()
{
}

CBaseListPolynomial::~CBaseListPolynomial()
{
}


/////////////////////////////////////////////////////////////////
///Opérateurs
CPolynomial* CBaseListPolynomial::operator[] (long Index)
{
	return m_ListPolynomial[Index];
}

