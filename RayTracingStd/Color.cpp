#pragma warning(disable : 4244)

#include "stdio.h"
#include "Color.h"
#include <cmath>
#include "Power.h"

double	CColor::gamma=0;

CColor::CColor()
{

}

CColor::CColor(const CColor &color)
{
	m_R=color.m_R;
	m_G=color.m_G;
	m_B=color.m_B;
	//m_A=color.m_A;
}

CColor::CColor(float Red,float Green,float Blue)
{
	m_R=Red;
	m_G=Green;
	m_B=Blue;
}

CColor::CColor(float c[3])
{
	m_R=c[0];
	m_G=c[1];
	m_B=c[2];
}

CColor::CColor(double c[3])
{
	m_R=float(c[0]);
	m_G=float(c[1]);
	m_B=float(c[2]);
}

CColor::~CColor()
{
}

CColor&	CColor::operator=(const CColor	&Origin)
{
	m_R=Origin.m_R;
	m_G=Origin.m_G;
	m_B=Origin.m_B;
//	m_A=Origin.m_A;

	return (*this);
}


CColor&	CColor::operator*=(float cste)
{
	m_R*=cste;
	m_G*=cste;
	m_B*=cste;

	return (*this);
}

CColor&	CColor::operator*=(const CColor	&Origin)
{

	m_R*=Origin.m_R;
	m_G*=Origin.m_G;
	m_B*=Origin.m_B;

	return (*this);
}

CColor	CColor::operator+(const CColor	&Origin)
{
	CColor res;

	res.m_R=m_R+Origin.m_R;
	res.m_G=m_G+Origin.m_G;
	res.m_B=m_B+Origin.m_B;

	return (res);
}

CColor	CColor::operator-(const CColor	&Origin)
{
	CColor res;

	res.m_R=m_R-Origin.m_R;
	res.m_G=m_G-Origin.m_G;
	res.m_B=m_B-Origin.m_B;

	return (res);
}

CColor	CColor::operator*(const CColor	&Origin)
{
	CColor res;

	res.m_R=m_R*Origin.m_R;
	res.m_G=m_G*Origin.m_G;
	res.m_B=m_B*Origin.m_B;

	return (res);
}

CColor	CColor::operator*(float Coeff)
{
	CColor res;

	res.m_R=m_R*Coeff;
	res.m_G=m_G*Coeff;
	res.m_B=m_B*Coeff;

	return (res);
}

CColor	CColor::operator/(float Coeff)
{
	CColor res;

	res.m_R=m_R/Coeff;
	res.m_G=m_G/Coeff;
	res.m_B=m_B/Coeff;

	return (res);
}

CColor	CColor::operator+(float Coeff)
{
	CColor res;

	res.m_R=m_R+Coeff;
	res.m_G=m_G+Coeff;
	res.m_B=m_B+Coeff;

	return (res);
}

CColor	CColor::operator-(float Coeff)
{
	CColor res;

	res.m_R=m_R-Coeff;
	res.m_G=m_G-Coeff;
	res.m_B=m_B-Coeff;

	return (res);
}

CColor CColor::Merge(const CColor & c,float m) const
{
  CColor res;

  // On borne le coefficient de melange par l'intervalle [0,1]
  if (m>1)
    m=1;
  if (m<0)
    m=0;

  res.m_R=(m_R*(1-m))+(c.m_R*m);
  res.m_G=(m_G*(1-m))+(c.m_G*m);
  res.m_B=(m_B*(1-m))+(c.m_B*m);

  return res;
}

void	CColor::Correction(double g)
{
	m_R=power(m_R,1/g);
	m_G=power(m_G,1/g);
	m_B=power(m_B,1/g);
}

void	CColor::Correction(CColor ColorPixel)
{
	ColorPixel.SetRed(power(ColorPixel.GetRed(),1/gamma));
	ColorPixel.SetGreen(power(ColorPixel.GetGreen(),1/gamma));
	ColorPixel.SetBlue(power(ColorPixel.GetBlue(),1/gamma));
}

void	CColor::SetCorrection(double g)
{
	gamma=g;
}


ostream& operator<<(ostream &o,const CColor &c)
{
	o << "rgb <" << c.GetRed() << "," << c.GetGreen() << "," << c.GetBlue() << ">";

	return o;
}
