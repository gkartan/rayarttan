#include "stdio.h"
#include "BaseLight.h"
#include "BaseModelLight.h"

CBaseLight::CBaseLight()
{
	m_color=CColor(0,0,0);
	m_pModelLight=new CBaseModelLight(); //Modèle d'éclairement par défaut
	m_pModelLight->AddRef();
}

CBaseLight::CBaseLight(CColor &color,const std::string &str)
{
	m_color=color;
	m_sName=str;
	m_pModelLight=new CBaseModelLight(); //Modèle d'éclairement par défaut
	m_pModelLight->AddRef();
}

CBaseLight::CBaseLight(CColor &color,CBaseModelLight *pLight)
{
	m_color=color;
	m_pModelLight=pLight;
	m_pModelLight->AddRef();
}


CBaseLight::~CBaseLight()
{
	if(m_pModelLight!=NULL)
	{
		m_pModelLight->Release();
		m_pModelLight=NULL;
	}
}


CBaseLight&	CBaseLight::operator =  (CBaseLight&Param)
{
	m_sName=Param.m_sName;
	m_color=Param.m_color;
	m_pModelLight=Param.m_pModelLight;
	m_pModelLight->AddRef();

	ForceEqual(Param);

	return(*this);
}

