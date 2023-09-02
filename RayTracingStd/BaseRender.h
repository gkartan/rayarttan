/////Etat classe : VALIDE
#ifndef	_BASERENDER
#define _BASERENDER

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#pragma warning(disable : 4530)

#include <vector>
#include "BaseGeometry.h"
#include "BaseLight.h"
#include "TypeDefinitions.h"

class CBaseFileManager;
class CBaseCamera;
class CBaseImage;
class CRayEye;
class CIhmInterface;
class CPhotonTracer;

class CBaseRender
{
// Construction
public:
	CBaseRender();
	CBaseRender(CBaseCamera *pCamera,
				CBaseImage  *pImage,
				TypeVectorGeometry &ListGeometry,
				TypeVectorLight	  &ListLight,
				CPhotonTracer*	pPhotonTracer);

// Attributes
protected:
	CBaseCamera*			m_pCamera;		//Definition du point de vue
	TypeVectorGeometry		m_ListeObjects;	//Input Data
	TypeVectorLight			m_ListeLights;	//Liste des lumières

	CPhotonTracer*			m_pPhotonTracer;//la photon map
	CBaseImage*				m_pImage;		//Image en sortie

	bool*					m_pTerminated;	//booléen de test de sortie de thread

// Operations
public:
	inline  void	SetTerminated(bool *Param)		{m_pTerminated=Param;}

protected:
	virtual	void	Render(long,long)=0;
	virtual CColor	RayTrace(CRayEye*,TypeVectorGeometry&,TypeVectorLight&)=0;

// Implementation
public:
	virtual ~CBaseRender();

	// Generated message map functions
protected:
};

#endif
