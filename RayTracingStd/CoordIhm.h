/////Etat classe : EN COURS
#ifndef _COORDIHM
#define _COORDIHM

#include "Coord.h"

class CCoordIhm : public CCoord
{
// Construction
public:
	CCoordIhm();


// Operations publiques
public:
	inline  double&	GetRefX() {return m_Value[0];}
	inline  double&	GetRefY() {return m_Value[1];}
	inline  double&	GetRefZ() {return m_Value[2];}

	CCoordIhm& operator = (const CCoord&);
// Implementation
public:
	virtual ~CCoordIhm();

	// Generated message map functions
protected:
};

#endif

