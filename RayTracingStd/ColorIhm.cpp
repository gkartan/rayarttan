#include "stdafx.h"
#include "ColorIhm.h"
#include "Macros.h"

CColorIhm::CColorIhm()
{
	m_R=0;
	m_G=0;	
	m_B=0;
	m_ColorRef=0;
}

CColorIhm::~CColorIhm()
{

}


CColorIhm& CColorIhm::operator = (const CColor &Origin)
{
	m_R=CONVERT_COLORIHM(Origin.m_R);
	m_G=CONVERT_COLORIHM(Origin.m_G);
	m_B=CONVERT_COLORIHM(Origin.m_B);

	m_ColorRef=RGB(m_R,
				   m_G,
				   m_B);

	return (*this);
}

void	CColorIhm::UpdateColorRef(COLORREF color)
{
	m_ColorRef=color;
	m_R=GetRValue(m_ColorRef);
	m_G=GetGValue(m_ColorRef);
	m_B=GetBValue(m_ColorRef);
}

CColor	CColorIhm::ConvertEng()
{
	CColor color(CONVERT_COLORENG(m_R),
				 CONVERT_COLORENG(m_G),
				 CONVERT_COLORENG(m_B));

	return color;
}


