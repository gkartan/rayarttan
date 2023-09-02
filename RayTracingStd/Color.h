/////Etat classe : VALIDE
#ifndef _CCOLOR
#define _CCOLOR

#include "BaseColor.h"
#include <ostream.h>

class CColor : public CBaseColor<float>
{
// Construction
public:
	CColor();
	CColor(const CColor&);
	CColor(float,float,float);
	CColor(float c[3]);
	CColor(double c[3]);

//operations
public:
	CColor&	operator=  (const CColor&);
	CColor& operator*= (float);
	CColor&	operator*= (const CColor&);
	CColor	operator+  (const CColor&);
	CColor	operator-  (const CColor&);
	CColor	operator*  (const CColor&);
	CColor	operator*  (float);
	CColor	operator/  (float);
	CColor	operator+  (float);
	CColor	operator-  (float);


	friend ostream& operator<<(ostream&,const CColor&);

//attributs statiques
	static  double	gamma;
//operations statiques
public:
			void Correction(double g);
	static  void Correction(CColor);
	static  void SetCorrection(double g);

	CColor	Merge(const CColor & c,float m) const;


	inline void SetRGB(float c[3])	{m_R=c[0];m_G=c[1];m_B=c[2];}
	inline void SetRGB(double c[3])	{m_R=float(c[0]);m_G=float(c[1]);m_B=float(c[2]);}
// Implementation
public:
	virtual ~CColor();
};

#endif