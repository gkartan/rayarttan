#include "stdio.h"
#include "FractalDepthColorMatiere.h"

CFractalDepthColorMatiere::CFractalDepthColorMatiere()
:CBaseMatiere()
{
	m_DepthColor=CColor(0,0,0);
}

CFractalDepthColorMatiere::CFractalDepthColorMatiere(CColor &param)
:CBaseMatiere(param)
{
	m_DepthColor=param; 
}

CFractalDepthColorMatiere::CFractalDepthColorMatiere(CColor &param,CDepthColorModelLight *pLight)
:CBaseMatiere(param,(CBaseModelLight*) pLight)
{
	m_DepthColor=param; 
}

CFractalDepthColorMatiere::~CFractalDepthColorMatiere()
{
}

CFractalDepthColorMatiere&	CFractalDepthColorMatiere::operator=(CFractalDepthColorMatiere	&Origin)
{
	m_ColorGeneral=Origin.m_ColorGeneral;
	m_ColorAmbient=Origin.m_ColorAmbient;
	m_ColorSpecular=Origin.m_ColorSpecular;		
	m_ColorDiffuse=Origin.m_ColorDiffuse;	
	m_ColorTransparency=Origin.m_ColorTransparency;	

	m_Milieu1=Origin.m_Milieu1;
	m_Milieu2=Origin.m_Milieu2;

	m_ka=Origin.m_ka; 
	m_kd=Origin.m_kd; 
	m_ks=Origin.m_ks; 
	m_kr=Origin.m_kr; 
	m_kt=Origin.m_kt;
	m_DepthColor=Origin.m_DepthColor; 

	return (*this);
}

void CFractalDepthColorMatiere::SetDepthColor(CColor &Color)
{
	m_DepthColor=Color;
}

void	CFractalDepthColorMatiere::SetIteration(long It)
{
	m_DepthColor.SetColor(It,It,It);
}
