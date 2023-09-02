/////Etat classe : VALIDE

#ifndef _RAYLIGHT
#define _RAYLIGHT

#include "Ray.h"

class CRayLight : public CRay
{
// Construction
public:
	CRayLight();
	CRayLight(const CCoord&,const CVector&);

//Attributes
private:
	CColor	m_ColorResult;

	static	unsigned long m_NbRayLight;

//operations
public:
	static unsigned long	GetNbRay() {return m_NbRayLight;};

	bool	RayTrace(TypeVectorGeometry &);
	CColor  GetColorResult();


// Implementation
public:
	virtual ~CRayLight();
};

#endif