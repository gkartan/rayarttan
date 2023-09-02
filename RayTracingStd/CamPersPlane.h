/////Etat classe : VALIDE

#ifndef _CAMPERSPLANE
#define _CAMPERSPLANE

#include "BaseCamera.h"

class CCamPersPlane : public CBaseCamera
{
// Construction
public:
	CCamPersPlane();

// Attributes
protected:
	double m_dx;
	double m_dy;

	CVector	m_RightVect;
	CCoord	m_TopLeft;
	CCoord	m_Focus;

// Operations publiques
public:
	virtual void	SetTop(CVector &Top);	
	virtual void	Init(long,long);
	virtual void	GetRay(float,float,CCoord&,CVector&);
	virtual std::string GetType();

	virtual	void GetOuputStream(ostream&);
// Implementation
public:
	virtual ~CCamPersPlane();

	// Generated message map functions
protected:
};

#endif

