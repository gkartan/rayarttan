/////Etat classe : VALIDE


#ifndef _BASEMODELLIGHT
#define _BASEMODELLIGHT

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "Color.h"
#include "RayEye.h"
#include "BaseIntersection.h"

//Modèle par défaut ---> Phong
class CBaseModelLight
{
// Construction
public:
	CBaseModelLight();
	CBaseModelLight(double PhongExp);

///Attributes
protected:
	double		m_PhongExp;
	double		m_Intensity;

private:
	long			m_NbRef;

// Operations
protected:
	virtual CColor	ComputeDiffuse(const CBaseIntersection &Intersection,
						   const CVector			 &vIntersectToLight);

	virtual CColor	ComputeSpecular(const CBaseIntersection &Intersection,
							const CVector			 &vIntersectToLight,
							const CVector			 &vIntersectToEye,
							const CBaseLight		 &Light);
//Operations
public:

	virtual CColor	ComputeColor(const CBaseIntersection &Intersection,
						 const CVector			 &vIntersectToLight,
						 const CVector			 &vIntersectToEye,
						 const CBaseLight		 &Light);


	void	AddRef();
	void	Release();

	inline void		SetPhongExp(double param)	{m_PhongExp=param;}
	inline double	GetPhongExp()				{return(m_PhongExp);}

// Implementation
public:
	virtual ~CBaseModelLight();

	// Generated message map functions
protected:
};


#endif