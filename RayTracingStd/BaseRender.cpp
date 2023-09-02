#include "stdio.h"
#include "BaseRender.h"

CBaseRender::CBaseRender()
{
	m_pTerminated=NULL;
}

CBaseRender::CBaseRender(CBaseCamera *pCamera,
						 CBaseImage  *pImage,
						 TypeVectorGeometry &ListGeometry,
						 TypeVectorLight	  &ListLight,
						 CPhotonTracer*	pPhotonTracer)
{
	m_pCamera=pCamera;		
	m_ListeObjects=ListGeometry;
	m_ListeLights=ListLight;	
	m_pImage=pImage;
	m_pTerminated=NULL;
	m_pPhotonTracer=pPhotonTracer;
}


CBaseRender::~CBaseRender()
{
}