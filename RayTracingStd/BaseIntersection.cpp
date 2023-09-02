#include "stdio.h"
#include "BaseIntersection.h"


CBaseIntersection::CBaseIntersection()
{
	m_pMatiere=NULL;
}

CBaseIntersection::CBaseIntersection(const CBaseIntersection &Origin)
{
	m_Distance=Origin.m_Distance;     
	m_pObjet=Origin.m_pObjet;       
	m_pMatiere=Origin.m_pMatiere;
	m_Normal=Origin.m_Normal;		
	m_IndiceMilieu=Origin.m_IndiceMilieu; 
	m_Point=Origin.m_Point;

	if(m_pMatiere!=NULL)
		m_pMatiere->AddRef();
}

CBaseIntersection::~CBaseIntersection()
{
	if(m_pMatiere!=NULL)
		m_pMatiere->Release();
}

CBaseIntersection	CBaseIntersection::operator=(const CBaseIntersection  & Origin)
{
	m_Distance=Origin.m_Distance;     
	m_pObjet=Origin.m_pObjet;       
	m_pMatiere=Origin.m_pMatiere;
	m_Normal=Origin.m_Normal;		
	m_IndiceMilieu=Origin.m_IndiceMilieu; 
	m_Point=Origin.m_Point;

	if(m_pMatiere!=NULL)
		m_pMatiere->AddRef();

	return (*this);
}
