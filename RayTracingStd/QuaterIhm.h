/////Etat classe : EN COURS
#ifndef _QUATERIHM
#define _QUATERIHM

#include "BaseVector.h"

class CQuaterIhm : public CBaseVector<4,double>
{
// Construction
public:
	CQuaterIhm();


// Operations publiques
public:
	inline  double&		GetRefX()  {return m_Value[0];}
	inline  double&		GetRefY()  {return m_Value[1];}
	inline  double&		GetRefZ()  {return m_Value[2];}
	inline  double&		GetRefW()  {return m_Value[3];}

	inline	void	Set(double X,double Y,double Z,double W) {m_Value[0]=X;m_Value[1]=Y;m_Value[2]=Z;m_Value[3]=W;}

	CQuaterIhm& operator = (const CBaseVector<4,double>&);
// Implementation
public:
	virtual ~CQuaterIhm();

	// Generated message map functions
protected:
};

#endif

