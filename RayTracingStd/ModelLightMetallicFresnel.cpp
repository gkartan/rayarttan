#include "stdio.h"
#include "ModelLightMetallicFresnel.h"
#include "BaseLight.h"
#include "Constants.h"
#include <cmath>

CModelLightMetallicFresnel::CModelLightMetallicFresnel()
:CModelLightMetallic()
{
}

CModelLightMetallicFresnel::CModelLightMetallicFresnel(double PhongExp,double Metallic)
:CModelLightMetallic(PhongExp,Metallic)
{
	m_Metallic=Metallic;
}


CModelLightMetallicFresnel::~CModelLightMetallicFresnel()
{
}


// Calcul de la composante spéculaire
// Calcul avec terme de Fresnel empirique -- tiré de POV
// cf CBaseModelLight pour modèle Phong
CColor CModelLightMetallicFresnel::ComputeSpecular(const CBaseIntersection &Intersection,
										const CVector			 &vIntersectToLight,
										const CVector			 &vIntersectToEye,
										const CBaseLight		 &Light)
{
	///Calcul de l'intensité par la méthode de Phong
	CBaseModelLight::ComputeSpecular(Intersection,
												vIntersectToLight,
												vIntersectToEye,
												Light);

	///Calcul du terme de Fresnel de la réflectance	
	///Empirique
	double x=fabs(acos(Intersection.GetNormal()*vIntersectToLight)) / M_PI_2;
	double F=0.014567225 / ((x - 1.12)*(x - 1.12)) - 0.011612903;
	double MinF=(F>0.0)?F:0.0;
    F=(MinF>1.0)?1.0:MinF;

	CColor res = Light.GetColor() * ((Intersection.GetColorSpecular() - 1.0) * (m_Metallic * (1.0 - F)) + 1.0) * m_Intensity;

	return res;

}