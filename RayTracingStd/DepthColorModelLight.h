/////Etat classe : VALIDE


#ifndef _DEPTHCOLORMODELLIGHT
#define _DEPTHCOLORMODELLIGHT

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "BaseModelLight.h"

class CDepthColorModelLight : public CBaseModelLight
{
// Construction
public:
	CDepthColorModelLight();


// Operations
protected:
	virtual CColor	ComputeDiffuse(const CBaseIntersection &Intersection,
						   const CVector			 &vIntersectToLight);

	virtual CColor	ComputeSpecular(const CBaseIntersection &Intersection,
							const CVector			 &vIntersectToLight,
							const CVector			 &vIntersectToEye);
//Operations
public:

	virtual CColor	ComputeColor(const CBaseIntersection &Intersection,
						 const CVector			 &vIntersectToLight,
						 const CVector			 &vIntersectToEye);

// Implementation
public:
	virtual ~CDepthColorModelLight();

	// Generated message map functions
protected:
};


#endif