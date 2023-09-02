/////Etat classe : EN COURS


#ifndef _MODELLIGHTMETALLIC
#define _MODELLIGHTMETALLIC

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "BaseModelLight.h"

//Modèle par défaut ajoutant une composante métallique
//Modèle Phong Metallic
class CModelLightMetallic : public CBaseModelLight
{
// Construction
public:
	CModelLightMetallic();
	CModelLightMetallic(double PhongExp,double Metallic);

///Attributes
protected:
	double		m_Metallic;

// Operations
protected:

	//Seule la composante spéculaire est surchargée
	virtual CColor	ComputeSpecular(const CBaseIntersection &Intersection,
							const CVector			 &vIntersectToLight,
							const CVector			 &vIntersectToEye,
							const CBaseLight		 &Light);
// Implementation
public:
	virtual ~CModelLightMetallic();

	// Generated message map functions
protected:
};


#endif