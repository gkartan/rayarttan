/////Etat classe : EN COURS


#ifndef _MODELLIGHTMETALLICFRESNEL
#define _MODELLIGHTMETALLICFRESNEL

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "ModelLightMetallic.h"

//Mod�le par d�faut ajoutant une composante m�tallique
//Mod�le Phong Metallic
class CModelLightMetallicFresnel : public CModelLightMetallic
{
// Construction
public:
	CModelLightMetallicFresnel();
	CModelLightMetallicFresnel(double PhongExp,double Metallic);

// Operations
protected:

	//Seule la composante sp�culaire est surcharg�e
	virtual CColor	ComputeSpecular(const CBaseIntersection &Intersection,
							const CVector			 &vIntersectToLight,
							const CVector			 &vIntersectToEye,
							const CBaseLight		 &Light);
// Implementation
public:
	virtual ~CModelLightMetallicFresnel();

	// Generated message map functions
protected:
};


#endif