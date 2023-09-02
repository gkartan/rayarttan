/////Etat classe : TEST
#ifndef _CAMSPHERE
#define _CAMSPHERE

#include "CamSuperEllipsoid.h"
#include "MatrixTransform.h"

///////////////////////////////////////////////////
///La sphere est une superellipsoid est un peu speciale
///on utilise les matrices de rotations pour calculer plus vite
class CCamSphere : public CCamSuperEllipsoid
{
// Construction
public:
	CCamSphere();
	CCamSphere(const CCoord &Center,
			   const CCoord &LookAt);

	CCamSphere(const CCoord &Center,
					   const CCoord &LookAt,
					   double AngleWidth,
					   double AngleHeight);
 
// Attributes
protected:
	CMatrixTransform	m_Matrix;

// Operations publiques
public:
	virtual void	GetRay(float,float,CCoord&,CVector&);
	virtual std::string GetType();

	virtual	void GetOuputStream(ostream&);
// Implementation
public:
	virtual ~CCamSphere();

	// Generated message map functions
protected:
};

#endif

