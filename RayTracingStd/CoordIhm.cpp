#include "stdafx.h"
#include "CoordIhm.h"

CCoordIhm::CCoordIhm()
{
	m_Value[0]=0;
	m_Value[1]=0;	
	m_Value[2]=0;
}

CCoordIhm::~CCoordIhm()
{
}


CCoordIhm& CCoordIhm::operator = (const CCoord &Origin)
{
	m_Value[0]=Origin.m_Value[0];
	m_Value[1]=Origin.m_Value[1];
	m_Value[2]=Origin.m_Value[2];

	return (*this);
}



