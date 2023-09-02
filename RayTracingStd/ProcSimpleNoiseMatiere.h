/////Etat classe : VALIDE

#ifndef	_NOISEMATIERE
#define _NOISEMATIERE

#include <stdio.h>
#include "BaseProcedural.h"
#include "Noise3D.h"

class CProcSimpleNoiseMatiere : public CBaseProcedural
{
// Construction
public:
	CProcSimpleNoiseMatiere();
	CProcSimpleNoiseMatiere(CColor& color);

// Attributes
protected:
	CNoise3D		*m_pNoise;
	
// Operations
public:
	void	ChangeFunctionNoise(CNoise3D*);
	void	ChangeFreq(float Freq);

	virtual CColor	GetColor(const CCoord&,const CCoord&)	const;

	CProcSimpleNoiseMatiere&	operator =  (CProcSimpleNoiseMatiere&);

	virtual std::string	GetType() const;
	virtual bool		  Compatible(ENUM_TYPETEXTURE);

// Implementation
public:
	virtual ~CProcSimpleNoiseMatiere();

public:
	virtual	void GetOuputStream(ostream&);
};

#endif

