#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#pragma warning(disable : 4530)

#include "CamSphere.h"

CCamSphere::CCamSphere()
{
	m_AngleWidth=360.;
	m_AngleHeight=360.;
}

CCamSphere::CCamSphere( const CCoord &Center,
						const CCoord &LookAt)
{
	m_Center=Center;
	m_LookAt=LookAt;
	m_AngleWidth=360.;
	m_AngleHeight=360.;
}

CCamSphere::CCamSphere(const CCoord &Center,
					   const CCoord &LookAt,
					   double AngleWidth,
					   double AngleHeight)
{
	m_Center=Center;
	m_LookAt=LookAt;
	m_AngleWidth=AngleWidth;
	m_AngleHeight=AngleHeight;
}


CCamSphere::~CCamSphere()
{
}

void	CCamSphere::GetRay(float CurX,
							  float CurY,
							  CCoord &RayCoord,
							  CVector&RayDirect)
{
	m_Matrix.Rotate(CVector(CurX*m_Angledx,CurY*m_Angledy,0));
	RayCoord=m_Matrix.Trans(m_First);
	RayDirect=CVector(RayCoord,m_LookAt);
	RayDirect.Normalize();
}

std::string CCamSphere::GetType()
{
	return("spheric");
}

void CCamSphere::GetOuputStream(ostream &o)
{
	o <<	"\ncamera\n{\n"		<<		"\tspheric\n";
	o <<	"\tlocation"		<<		GetCenter()		<<	"\n";
	o <<	"\tlook_at"			<<		GetLookAt()		<<	"\n";
	o <<	"\twidth "			<<		GetWidth()		<<	"\n";
	o <<	"\theight "			<<		GetHeight()		<<	"\n";
	o <<	"\tangle "			<<		m_AngleWidth	<<	","	<< m_AngleHeight	<<"\n";
	o <<	"}\n";

}

