#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "stdio.h"
#include "RayLight.h"
#include "LightSpot.h"
#include "BaseMatiere.h"
#include "BaseListIntersection.h"
#include "BaseModelLight.h"

CLightSpot::CLightSpot()
{
}

CLightSpot::CLightSpot(CColor &color,CCoord &coord,
					   CVector &vect,double cosgamma,
					   const std::string &str)
:CLightPoint(color,coord,str)
{
	m_Direct=vect;
	m_CosGamma=cosgamma;
}

CLightSpot::CLightSpot(const CLightSpot &Param)
{
	m_sName=Param.m_sName;
	m_color=Param.m_color;
	m_Direct=Param.m_Direct;	
	m_CosGamma=Param.m_CosGamma;    
	m_pModelLight=m_pModelLight;
	m_pModelLight->AddRef();
}


CLightSpot::~CLightSpot()
{
}


CColor CLightSpot::Illumination(	CRayEye &ParamRay,
									TypeVectorGeometry &ParamListGeo) 
{
	// Calcul du vecteur allant du point d'intersection vers la lumiere
	CVector vIntersectToLight=m_Position-ParamRay.GetImpactPosition();
	vIntersectToLight.Normalize();

	// Puis le cosinus de l'angle entre ce vecteur directeur et la direction
	// principale de la lumiere
	double cosbeta=vIntersectToLight*m_Direct;

	if (cosbeta<=m_CosGamma)
	{
		return CLightPoint::Illumination(ParamRay,ParamListGeo);
	}
	else
	{
		// Le point se trouve hors du cone de lumiere. La contribution de la
		// lumiere a son eclairage est donc nulle
		return CColor(0,0,0);
	}

	return CColor(0,0,0);
}

std::string CLightSpot::GetType()
{
	return("spotlight");
}

void CLightSpot::ForceEqual(CBaseLight &Param)
{
	CLightSpot *pTrueOrigin=static_cast<CLightSpot*>(&Param);
	if(pTrueOrigin!=NULL)
	{
		m_Direct=pTrueOrigin->m_Direct;	
		m_CosGamma=pTrueOrigin->m_CosGamma;    

	}

	///appel à la méthode de la classe parente
	CLightPoint::ForceEqual(Param);
}
