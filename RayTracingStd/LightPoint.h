/////Etat classe : VALIDE

#ifndef _LIGHTPOINT
#define _LIGHTPOINT

#include "BaseLight.h"

class CLightPoint : public CBaseLight
{
// Construction
public:
	CLightPoint();
	CLightPoint(CColor&,CCoord&,const std::string&);
	CLightPoint(const CLightPoint&);

// Attributes
protected:
	CCoord		m_Position;

// Operations
public:
	inline		virtual void	SetPosition(const CCoord &coord) {m_Position=coord;}
	inline		virtual CCoord	GetPosition() const {return m_Position;}

// Implementation
public:
	virtual CColor Illumination(CRayEye &,
								TypeVectorGeometry &);


	virtual ~CLightPoint();

	virtual std::string GetType();

	inline 	virtual bool		GetIsPosition() const {return true;}


	virtual	void GetOuputStream(ostream&);

	virtual void ForceEqual(CBaseLight&);
	// Generated message map functions
protected:
};

#endif
  
