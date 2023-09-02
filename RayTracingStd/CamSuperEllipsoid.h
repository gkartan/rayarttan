/////Etat classe : EN COURS
#ifndef _CAMSUPERELLIPSOID
#define _CAMSUPERELLIPSOID

#include "BaseCamera.h"


////////////////////////////////////////////////////
///La superellipsoid est le produit sphérique de 2 superellipses
///permettant ainsi de trouver le pt (x,y,z) de la courbe
///à partir de 2 angles
////////////////////////////////////////////////////
class CCamSuperEllipsoid : public CBaseCamera
{
// Construction
public:
	CCamSuperEllipsoid();
	CCamSuperEllipsoid(const CCoord &Center,
					   const CCoord &LookAt);

	CCamSuperEllipsoid(const CCoord &Center,
					   const CCoord &LookAt,
					   double AngleWidth,
					   double AngleHeight);
 
//	Attributes
protected:
	double m_Angledx;		//les angles en degrées
	double m_Angledy;
	double m_AngleWidth;	//Angle Maximum 360°
	double m_AngleHeight;	//Angle Maximum 180°

	double m_ScaleX;
	double m_ScaleY;
	double m_ScaleZ;
	double m_Epsilon1;
	double m_Epsilon2;

	CCoord	m_First;

// Operations publiques
public:
	virtual void	SetTop(CVector &Top);	
	virtual void	Init(long,long);
	virtual void	GetRay(float,float,CCoord&,CVector&);
	virtual std::string GetType();

	virtual	void GetOuputStream(ostream&);

	void	SetAngle(double,double);
	void	SetScale(const CVector&);
	void	SetEpsilon(double,double);
// Implementation
public:
	virtual ~CCamSuperEllipsoid();

	// Generated message map functions
protected:
};

#endif

