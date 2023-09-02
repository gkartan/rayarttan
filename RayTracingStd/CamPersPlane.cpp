#pragma warning(disable : 4530)

#include "CamPersPlane.h"

CCamPersPlane::CCamPersPlane()
{
}

CCamPersPlane::~CCamPersPlane()
{
}

void CCamPersPlane::SetTop(CVector &Top)
{
  m_Top=Top-(m_Direct*(m_Direct*Top));
  if(!m_Top.IsNull())
  {
	  m_Top.Normalize();
  }
}
 
void	CCamPersPlane::Init(long Width,long Height)
{
  // On calcule la position du foyer de la camera
  m_Focus=m_Center-(m_Direct*m_Focal);

  // On calcule le vecteur unitaire "droite" du plan
  m_RightVect=m_Direct.Cross(m_Top);

  // On calcule le deltaX et le deltaY
  m_dx=m_WidthScreen/Width;
  m_dy=m_HeightScreen/Height;

  // On calcule la position du premier point de l'ecran que l'on calculera
  m_TopLeft=(m_RightVect*((m_dx/2)-(m_WidthScreen/2)))+
			     (m_Top*((m_HeightScreen/2)-(m_dy/2)))+
				  m_Center;

}

void	CCamPersPlane::GetRay(float CurX,
							  float CurY,
							  CCoord &RayCoord,
							  CVector&RayDirect)
{
	RayCoord=m_TopLeft+(m_RightVect*(m_dx*CurX))-(m_Top*(m_dy*CurY));
	RayDirect=RayCoord-m_Focus;
}

std::string CCamPersPlane::GetType()
{
	return("perspective");
}


void CCamPersPlane::GetOuputStream(ostream &o)
{
	o <<	"\ncamera\n{\n"		<<		"\tperspective\n";
	o <<	"\tlocation"		<<		GetCenter()		<<	"\n";
	o <<	"\tlook_at"			<<		GetLookAt()		<<	"\n";
	o <<	"\twidth "			<<		GetWidth()		<<	"\n";
	o <<	"\theight "			<<		GetHeight()		<<	"\n";
	o <<	"\tfocus  "			<<		GetFocal()		<<	"\n";
	o <<	"}\n";
}

