/////Etat classe : VALIDE


#ifndef _BASELIGHT
#define _BASELIGHT

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "Color.h"
#include "RayEye.h"
#include "BaseIntersection.h"

class CBaseModelLight;

class CBaseLight
{
// Construction
public:
	CBaseLight();
	CBaseLight(CColor&,const std::string &);
	CBaseLight(CColor&,CBaseModelLight*);

// Attributes
protected:
	std::string		m_sName;			//Nom de la lumiere
	CColor			m_color;
	CBaseModelLight *m_pModelLight;

// Operations
public:
	inline std::string	GetName()	const {return m_sName;}
	inline void		SetName(const std::string &Name) {m_sName=Name;}

	inline		void SetColor(CColor &color) {m_color=color;}
	inline		CColor	 GetColor()	 const {return m_color;}


// Implementation
public:
	virtual CColor Illumination(CRayEye &,
								TypeVectorGeometry &) = 0;
	virtual ~CBaseLight();
	virtual std::string GetType()=0;

	virtual bool			GetIsPosition() const=0;
	virtual CCoord			GetPosition() const =0;
	virtual void			SetPosition(const CCoord&)=0;

	virtual	void GetOuputStream(ostream&)=0;

	CBaseLight&	operator =  (CBaseLight&);
	virtual void ForceEqual(CBaseLight&)=0;

	// Generated message map functions
protected:
};


#endif