#include "stdio.h"
#include "ModelLightMetallic.h"
#include "BaseLight.h"

CModelLightMetallic::CModelLightMetallic()
{
	m_Metallic=0;
}

CModelLightMetallic::CModelLightMetallic(double PhongExp,double Metallic)
:CBaseModelLight(PhongExp)
{
	m_Metallic=Metallic;
}


CModelLightMetallic::~CModelLightMetallic()
{
}


// Calcul de la composante sp�culaire
// Mod�le �l�mentaire d'�clairement 
// Mod�le de Bui-Tuong Phong Etendue avec composante m�tallique :
// Is = Il * Ks * cosalpha^n * [m * LightColor + (1 - m)]
// O� m est la composante m�tallique
// cf CBaseModelLight pour mod�le Phong
CColor CModelLightMetallic::ComputeSpecular(const CBaseIntersection &Intersection,
										const CVector			 &vIntersectToLight,
										const CVector			 &vIntersectToEye,
										const CBaseLight		 &Light)
{
		
	CColor res(CBaseModelLight::ComputeSpecular(Intersection,
												vIntersectToLight,
												vIntersectToEye,
												Light));
	
	res = res * (Light.GetColor() * m_Metallic + (1-m_Metallic));

	return res;

}