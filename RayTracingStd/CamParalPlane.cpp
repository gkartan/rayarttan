#pragma warning(disable : 4530)


#include "CamParalPlane.h"

CCamParalPlane::CCamParalPlane()
{
}

CCamParalPlane::~CCamParalPlane()
{
}

void	CCamParalPlane::GetRay(float CurX,
							  float CurY,
							  CCoord &RayCoord,
							  CVector&RayDirect)
{
	RayCoord=m_TopLeft+(m_RightVect*(m_dx*CurX))-(GetTop()*(m_dy*CurY));
	RayDirect=GetDirect();
}

std::string CCamParalPlane::GetType()
{
	return("orthographic");
}

void CCamParalPlane::GetOuputStream(ostream &o)
{
	o <<	"\ncamera\n{\n"		<<		"\torthographic\n";
	o <<	"\tlocation"		<<		GetCenter()		<<	"\n";
	//o <<	"\tup"				<<		GetTop()		<<	"\n";	
	//o <<	"\tdirection"		<<		GetDirect()		<<	"\n";
	o <<	"\tlook_at"			<<		GetLookAt()		<<	"\n";
	o <<	"\twidth "			<<		GetWidth()		<<	"\n";
	o <<	"\theight "			<<		GetHeight()		<<	"\n";
	o <<	"}\n";
}
