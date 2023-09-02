/////Etat classe : VALIDE


#include "LightPoint.h"

//une lumière conique est une lumère ponctuelle
//dont on restreint l'effet
class CLightSpot : public CLightPoint
{
// Construction
public:
	CLightSpot();
	CLightSpot(CColor&,CCoord&,CVector&,double,const std::string &);
	CLightSpot(const CLightSpot&);

// Attributes
protected:
  CVector m_Direct;		// Direction de la lumiere
  double  m_CosGamma;    // Cosinus de l'Angle d'eclairage de la lumiere

// Operations
public:

// Implementation
public:
	virtual CColor Illumination(CRayEye &,
								TypeVectorGeometry &);
	virtual ~CLightSpot();

	virtual std::string GetType();

	virtual	void GetOuputStream(ostream&) {};

	virtual void ForceEqual(CBaseLight&);
	// Generated message map functions
protected:
};


  // Methodes
