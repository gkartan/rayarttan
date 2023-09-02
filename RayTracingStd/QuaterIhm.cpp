#include "stdafx.h"
#include "QuaterIhm.h"

CQuaterIhm::CQuaterIhm()
{
	m_Value[0]=0;
	m_Value[1]=0;	
	m_Value[2]=0;
	m_Value[3]=0;
}

CQuaterIhm::~CQuaterIhm()
{
}


CQuaterIhm& CQuaterIhm::operator = (const CBaseVector<4,double> &Origin)
{
	m_Value[0]=Origin.m_Value[0];
	m_Value[1]=Origin.m_Value[1];
	m_Value[2]=Origin.m_Value[2];
	m_Value[3]=Origin.m_Value[3];

	return (*this);
}



