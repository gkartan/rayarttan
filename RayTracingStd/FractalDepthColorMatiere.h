/////Etat classe : VALIDE

#ifndef	_FRACTALDEPTHCOLORMATIERE
#define _FRACTALDEPTHCOLORMATIERE

#include "BaseMatiere.h"

class CDepthColorModelLight;

class CFractalDepthColorMatiere : public CBaseMatiere
{
// Construction
public:
	CFractalDepthColorMatiere();
	CFractalDepthColorMatiere(CColor&);
	CFractalDepthColorMatiere(CColor&,CDepthColorModelLight*);

// Attributes
protected:
	CColor			m_DepthColor;

// Operations
public:
	inline void		SetDepthColor(CColor &Color); 
	inline const    CColor&	GetDepthColor() const {return m_DepthColor;}
	void		SetIteration(long It);

	//inline  CDepthModelLight* GetDepthModelLight() const {return m_pModelLight;}

	CFractalDepthColorMatiere&	operator =  (CFractalDepthColorMatiere&);

// Implementation
public:
	virtual ~CFractalDepthColorMatiere();

	// Generated message map functions
protected:
};

#endif

