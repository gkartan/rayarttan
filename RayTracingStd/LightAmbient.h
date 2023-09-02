/////Etat classe : VALIDE
#ifndef _LIGHTAMBIENT
#define _LIGHTAMBIENT

#include "BaseLight.h"

class CLightAmbient : public CBaseLight
{
// Construction
public:
	CLightAmbient();
	CLightAmbient(CColor&,const std::string &);
	CLightAmbient(const CLightAmbient&);

// Attributes
protected:

// Operations
public:

// Implementation
public:
	virtual CColor Illumination(CRayEye &,
								TypeVectorGeometry &);
	virtual ~CLightAmbient();

	virtual std::string GetType();

	inline 	virtual bool		GetIsPosition() const {return false;} //Pas d'infos de position disponible
	inline  virtual CCoord		GetPosition() const  {return CCoord(0,0,0);}; //Pas de position dispo
	inline	virtual void		SetPosition(const CCoord&) {/*ne fait rien*/} ;

	virtual	void GetOuputStream(ostream&);


	virtual void ForceEqual(CBaseLight&)	{/*No attributes->do nothing*/};
	// Generated message map functions
protected:
};

#endif
  
