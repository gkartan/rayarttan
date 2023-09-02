/////Etat classe : VALIDE

#ifndef _RAYEYE
#define _RAYEYE

#include "Ray.h"

class CRayEye : public CRay
{
// Construction
public:
	CRayEye();
	CRayEye(const CCoord&,const CVector&);
	CRayEye(const CCoord&,const CVector&, char WaveLength);

//Attributes
private:
	CCoord				m_ImpactPosition;	//Coordonnées de l'impact du rayon
	CBaseIntersection	m_ImpactIntersection;

	double				m_Milieu;			//Coeff de réfraction du milieu du rayon

	static unsigned long m_NbRayEye;
//operations
public:
	static unsigned long	GetNbRay() {return m_NbRayEye;};

	const CBaseIntersection&	GetImpactIntersection()		 {return m_ImpactIntersection;}
	const CCoord&				GetImpactPosition() 		 {return m_ImpactPosition;}
	const CVector				GetNormal()					 {return m_ImpactIntersection.GetNormal();}

	inline void	  SetMilieu(double milieu)  {m_Milieu=milieu;}
	inline double GetMilieu()				{return(m_Milieu);}

public:
	bool	RayTrace(TypeVectorGeometry &);


// Implementation
public:
	virtual ~CRayEye();
};

#endif