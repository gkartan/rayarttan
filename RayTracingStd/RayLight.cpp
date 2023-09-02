#include "stdio.h"
#include "RayLight.h"
#include "BaseIntersection.h"
#include "BaseGeometry.h"
#include "BaseLight.h"


unsigned long CRayLight::m_NbRayLight=0;

CRayLight::CRayLight()
{
	m_NbRayLight++;
}

CRayLight::CRayLight(const CCoord &coord,
					 const CVector &vect)
:CRay(coord,vect)
{
	m_NbRayLight++;
}


CRayLight::~CRayLight()
{
}


bool CRayLight::RayTrace(TypeVectorGeometry &ListGeometry)
{
	// On recherche l'impact du rayon
	if (Intersections(ListGeometry))
	{
		return true;
	}

	return false;
}

CColor  CRayLight::GetColorResult()
{
	return(m_ListIntersection.GetColorResult());
}

