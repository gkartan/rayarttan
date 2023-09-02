/////Etat classe : EN COURS

#ifndef	_BASEPROCEDURAL
#define _BASEPROCEDURAL

#include <stdio.h>
#include "Color.h"
#include "Coord.h"
#include <map>
#include <string>
#include "CommonMatiere.h"

typedef std::map<float,CColor>		TypeColorMap;

class CNoise3D;

class CBaseProcedural
{
// Construction
public:
	CBaseProcedural();
	CBaseProcedural(CColor&);

	virtual CColor	GetColor(const CCoord&,const CCoord&)	const=0;
			CColor	GetColorMap(float k) const;
	void	SetColor(const CColor &color);
	void	SetColor(float Position,const CColor &color);
	void	Clear();
		
	TypeColorMap& GetColorMap()	{ return m_ColorMap;}
	virtual std::string	  GetType()	const=0;
	virtual bool		  Compatible(ENUM_TYPETEXTURE)=0;
	virtual void	ChangeFunctionNoise(CNoise3D*)=0;
protected:
	//mutable pour qu'on puisse l'utiliser de facon 
	//inofensive dans les const members fonctions
	//la colormap est géré comme un tableau de paires --> Attention à l'ordre
	mutable TypeColorMap	m_ColorMap;	
	long			m_NbRef;
	
// Implementation
public:
	virtual ~CBaseProcedural();

	void	AddRef();
	void	Release();

public:
	virtual	void GetOuputStream(ostream&);
};

#endif

