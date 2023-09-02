#include "stdio.h"
#include "BaseModelLight.h"
#include "Power.h"
#include <afxmt.h>
#include "TraceService.h"

CMutex	LightMutex(FALSE,"LIGHTMUTEX");

CBaseModelLight::CBaseModelLight()
{
	m_PhongExp=40;
	m_Intensity=0.0;
	m_NbRef=0;
}

CBaseModelLight::CBaseModelLight(double PhongExp)
{
	m_PhongExp=PhongExp;
	m_Intensity=0.0;
	m_NbRef=0;
}


CBaseModelLight::~CBaseModelLight()
{
}

///////////////////////////////////////////////////////////////////////////
///Mod�le �l�mentaire d'�clairement :
/// Diffusion : loi de lambert
/// Speculaire : Phong
CColor	CBaseModelLight::ComputeColor(const CBaseIntersection &Intersection,
									  const CVector			 &vIntersectToLight,
									  const CVector			 &vIntersectToEye,
									  const CBaseLight		 &Light)
{
	return(ComputeDiffuse(Intersection,vIntersectToLight)+
		   ComputeSpecular(Intersection,vIntersectToLight,
						   vIntersectToEye,Light));
}

// Calcul la composante diffuse
// Mod�le �l�mentaire d'�clairement --> R�flexion de la lumi�re par un diffuseur parfait
// Loi de Lambert : Id = Il * Kd * costheta
// GetColorDiffuse = Il * Kd
// costheta = cos (angle entre la normale et le rayon entre le pt d'intersection et 
//				   le rayon venant de la lumi�re
// (cf p375) 
CColor CBaseModelLight::ComputeDiffuse(const CBaseIntersection &Intersection,
								       const CVector		   &vIntersectToLight)
{
	double costheta=fabs(Intersection.GetNormal()*vIntersectToLight);

	return(Intersection.GetColorDiffuse() * costheta);
}

// Calcul de la composante sp�culaire
// Mod�le �l�mentaire d'�clairement 
// Mod�le de Bui-Tuong Phong : Is = Il * Ks * cosalpha^n
// GetColorSpecular = Il * Ks
// cosalpha = cos (angle rayon r�fl�chi (lumi�re par rapport pt intersection et
//				   le rayon visuel)
// (cf p377)
CColor CBaseModelLight::ComputeSpecular(const CBaseIntersection &Intersection,
										const CVector			 &vIntersectToLight,
										const CVector			 &vIntersectToEye,
										const CBaseLight		 &Light)
{
	CColor res(0,0,0);
	//calcul rayon r�fl�chi
	//sym�trie angle lumineux par rapport � la normale au pt d'intersection
    CVector vLightReflected=(-vIntersectToLight).Reflect(Intersection.GetNormal());

	double cosalpha=-(vLightReflected*vIntersectToEye);

    if (cosalpha>0)
	{
	  m_Intensity=power(cosalpha,m_PhongExp);

      res=Intersection.GetColorSpecular()  *  m_Intensity;

	} else {
		m_Intensity=0.0;
	}

	return res;

}


void	CBaseModelLight::AddRef()	
{
	CSingleLock singleLock(&LightMutex);
	singleLock.Lock();  // Attempt to lock the shared resource

	m_NbRef++;

	singleLock.Unlock();
}
void	CBaseModelLight::Release()
{
	CSingleLock singleLock(&LightMutex);
	singleLock.Lock();  // Attempt to lock the shared resource

	m_NbRef--;
	if(m_NbRef<=0) delete(this);

	singleLock.Unlock();
}
