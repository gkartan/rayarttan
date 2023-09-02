#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "stdio.h"
#include "Color.h"
#include "Ray.h"
#include "BaseRenderPixel.h"

CBaseRenderPixel::CBaseRenderPixel()
{
}

CBaseRenderPixel::CBaseRenderPixel(long x,long y)
{
	m_lCoordX=x;
	m_lCoordY=y;
}


CBaseRenderPixel::~CBaseRenderPixel()
{
}


void CBaseRenderPixel::Compute(CRay &Ray)
{
}