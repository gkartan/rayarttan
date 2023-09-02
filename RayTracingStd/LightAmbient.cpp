#include "stdio.h"
#include "LightAmbient.h"
#include "BaseMatiere.h"
#include "BaseModelLight.h"

CLightAmbient::CLightAmbient()
{
}

CLightAmbient::CLightAmbient(CColor &color,const std::string &str)
:CBaseLight(color,str)
{
}

CLightAmbient::CLightAmbient(const CLightAmbient& Param)
{
	m_sName=Param.m_sName;
	m_color=Param.m_color;
	m_pModelLight=m_pModelLight;
	m_pModelLight->AddRef();
}


CLightAmbient::~CLightAmbient()
{
}


CColor CLightAmbient::Illumination(	CRayEye &ParamRay,
									TypeVectorGeometry &ParamListGeo)
{
	return(m_color*ParamRay.GetImpactIntersection().GetMatiere()->GetColorAmbient());
}

std::string CLightAmbient::GetType()
{
	return("ambient");
}

void CLightAmbient::GetOuputStream(ostream &o)
{
	o <<	"\nlight_source\n{\n";
	o <<	"\tambient\n";
	o <<	"\t \""						<<		GetName().c_str()	<<	"\"\n";
	o <<	"\tcolor "					<<		GetColor()			<<	"\n";
	o <<	"}\n";
}
