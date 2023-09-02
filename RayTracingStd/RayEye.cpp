#include "stdio.h"
#include "RayEye.h"
#include "BaseIntersection.h"
#include "BaseGeometry.h"
#include "BaseLight.h"

unsigned long CRayEye::m_NbRayEye=0;

CRayEye::CRayEye()
{
	m_Milieu=1;
	m_NbRayEye++;
}

CRayEye::CRayEye(const CCoord &coord,
				 const CVector &vect)
:CRay(coord,vect)
{
	m_Milieu=1;
	m_NbRayEye++;
}

CRayEye::CRayEye(const CCoord &coord,
				 const CVector &vect,
				 char  WaveLength)
:CRay(coord,vect,WaveLength)
{
	m_Milieu=1;
	m_NbRayEye++;
}


CRayEye::~CRayEye()
{
}

bool CRayEye::RayTrace(TypeVectorGeometry &ListGeometry)
{
	// On recherche l'impact du rayon
	if (Intersections(ListGeometry))
	{
		m_ImpactIntersection=*(m_ListIntersection[0]);

		m_ImpactPosition=m_Coord+m_Direction*m_ImpactIntersection.GetDistance();

		return true;
	}
	
	return false;
}