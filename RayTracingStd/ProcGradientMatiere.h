/////Etat classe : EN COURS

#ifndef	_GRADIENTMATIERE
#define _GRADIENTMATIERE

#include <stdio.h>
#include "BaseProcedural.h"

class CProcGradientMatiere : public CBaseProcedural
{
// Construction
public:
	CProcGradientMatiere();
	CProcGradientMatiere(CColor& color);
	
// Operations
public:
	virtual CColor	GetColor(const CCoord&,const CCoord&)	const;

	CProcGradientMatiere&	operator =  (CProcGradientMatiere&);

	virtual std::string	GetType() const {return std::string("gradient");};
	virtual bool		  Compatible(ENUM_TYPETEXTURE);

	virtual void	ChangeFunctionNoise(CNoise3D*) {/*Ne fait rien;*/};
// Implementation
public:
	virtual ~CProcGradientMatiere();

//Attributes
protected:
	double	m_Bound;

public:
	virtual	void GetOuputStream(ostream&);
};

#endif

