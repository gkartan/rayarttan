#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#pragma warning(disable : 4530)

#include "CamSuperEllipsoid.h"
#include "Constants.h"
#include "Power.h"


CCamSuperEllipsoid::CCamSuperEllipsoid()
{
	m_ScaleX=3;
	m_ScaleY=3;
	m_ScaleZ=3;
	m_Epsilon1=0.5;
	m_Epsilon2=0.5;
	m_AngleWidth=180.;
	m_AngleHeight=180.;
}

CCamSuperEllipsoid::CCamSuperEllipsoid( const CCoord &Center,
						const CCoord &LookAt)
{
	m_ScaleX=1;
	m_ScaleY=1;
	m_ScaleZ=1;
	m_Epsilon1=1;
	m_Epsilon2=1;

	m_Center=Center;
	m_LookAt=LookAt;
	m_AngleWidth=360.;
	m_AngleHeight=360.;
}


CCamSuperEllipsoid::CCamSuperEllipsoid(const CCoord &Center,
					   const CCoord &LookAt,
					   double AngleWidth,
					   double AngleHeight)
{
	m_ScaleX=1;
	m_ScaleY=1;
	m_ScaleZ=1;
	m_Epsilon1=1;
	m_Epsilon2=1;

	m_Center=Center;
	m_LookAt=LookAt;
	m_AngleWidth=AngleWidth;
	m_AngleHeight=AngleHeight;
}

CCamSuperEllipsoid::~CCamSuperEllipsoid()
{
}


void CCamSuperEllipsoid::SetTop(CVector &Top)
{
  m_Top=Top;
}


void	CCamSuperEllipsoid::Init(long Width,long Height)
{
  // On calcule le deltaX et le deltaY
  m_Angledx=m_AngleWidth/Width;
  m_Angledy=m_AngleHeight/Height;

  // On calcule la position du premier point de l'ecran que l'on calculera
  m_First=m_Center;
}

void	CCamSuperEllipsoid::GetRay(float CurX,
								   float CurY,
								   CCoord &RayCoord,
								   CVector&RayDirect)
{

	double RadAngleX=CurX*m_Angledx*PI_DIV_180-M_PI_2;
	double RadAngleY=CurY*m_Angledy*PI_DIV_180-M_PI;

	double cosx=cos(RadAngleX);
	double cosy=cos(RadAngleY);
	double sinx=sin(RadAngleX);
	double siny=sin(RadAngleY);
	double abs_cosx=fabs(cosx);
	double abs_cosy=fabs(cosy);
	double abs_sinx=fabs(sinx);
	double abs_siny=fabs(siny);


	register sign_cosx=SIGN(cosx);
	register sign_cosy=SIGN(cosy);
	register sign_sinx=SIGN(sinx);
	register sign_siny=SIGN(siny);

	CCoord coord(m_ScaleX*power(abs_cosx,m_Epsilon1)*power(abs_cosy,m_Epsilon2)*sign_cosx*sign_cosy,
				 m_ScaleY*power(abs_cosx,m_Epsilon1)*power(abs_siny,m_Epsilon2)*sign_cosx*sign_siny,	
				 m_ScaleZ*power(abs_sinx,m_Epsilon1)*sign_sinx);

	RayCoord=coord;	//Coordonnées initiale du rayon - il se situe sur la courbe

	//Calcul de la normale pour avoir la direction du rayon
	CVector vector((1.0/m_ScaleX)*power(abs_cosx,2.0-m_Epsilon1)*power(abs_cosy,2.0-m_Epsilon2)*sign_cosx*sign_cosy,
				   (1.0/m_ScaleY)*power(abs_cosx,2.0-m_Epsilon1)*power(abs_siny,2.0-m_Epsilon2)*sign_cosx*sign_siny,	
				   (1.0/m_ScaleZ)*power(abs_sinx,2.0-m_Epsilon1)*sign_sinx);
	RayDirect=-vector;	//le vecteur doit pointer vers l'intérieur de la courbe
	RayDirect.Normalize();


}

std::string CCamSuperEllipsoid::GetType()
{
	return("superellipsoid");
}

void CCamSuperEllipsoid::GetOuputStream(ostream &o)
{
	o <<	"\ncamera\n{\n"		<<		"\tsuperellipsoid\n";
	o <<	"\tlocation"		<<		GetCenter()		<<	"\n";
	o <<	"\tlook_at"			<<		GetLookAt()		<<	"\n";
	o <<	"\twidth "			<<		GetWidth()		<<	"\n";
	o <<	"\theight "			<<		GetHeight()		<<	"\n";
	o <<	"\tscale  <"		<<		m_ScaleX		<<	","  << m_ScaleY  << "," << m_ScaleZ << ">\n";
	o <<	"\tepsilon "		<<		m_Epsilon1		<<	","  << m_Epsilon2 << "\n";
	o <<	"\tangle "			<<		m_AngleWidth	<<	","	<< m_AngleHeight	<<"\n";
	o <<	"}\n";
}


void	CCamSuperEllipsoid::SetAngle(double Width, double Height)
{
	m_AngleWidth=Width;
	m_AngleHeight=Height;
}

void	CCamSuperEllipsoid::SetScale(const CVector &vector)
{
	m_ScaleX=vector.GetX();
	m_ScaleY=vector.GetY();
	m_ScaleZ=vector.GetZ();
}

void	CCamSuperEllipsoid::SetEpsilon(double Epsilon1,double Epsilon2)
{
	m_Epsilon1=Epsilon1;
	m_Epsilon2=Epsilon2;
}


