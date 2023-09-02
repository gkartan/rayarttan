 /////Etat classe : VALIDE

#ifndef _CAMPARALPLANE
#define _CAMPARALPLANE

#include "CamPersPlane.h"

class CCamParalPlane : public CCamPersPlane
{
// Construction
public:
	CCamParalPlane();


// Operations publiques
public:

	virtual void		GetRay(float,float,CCoord&,CVector&);
	virtual std::string GetType();

	virtual	void GetOuputStream(ostream&);

// Implementation
public:
	virtual ~CCamParalPlane();

	// Generated message map functions
protected:
};

#endif