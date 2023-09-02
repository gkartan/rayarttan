/////Etat classe : EN COURS
#ifndef _COLORIHM
#define _COLORIHM

#include "Color.h"

class CColorIhm : public CColor
{
// Construction
public:
	CColorIhm();


// Operations publiques
public:
	inline float&	GetRed()	{return m_R;};
	inline float&	GetGreen()	{return m_G;};
	inline float&	GetBlue()	{return m_B;};

	inline COLORREF& GetColorRef()	{return m_ColorRef;} //Traduction en COLORREF pour IHM

	CColor			ConvertEng();

	void		UpdateColorRef(COLORREF);

	CColorIhm& operator = (const CColor&);
// Implementation
public:
	virtual ~CColorIhm();

private:
	COLORREF		m_ColorRef;

	// Generated message map functions
protected:
};

#endif

