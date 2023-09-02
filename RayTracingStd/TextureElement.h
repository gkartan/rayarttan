/////Etat classe : EN COURS

#ifndef	_TEXTUREELEMENT
#define _TEXTUREELEMENT

#include <stdio.h>
#include "Color.h"
#include "Coord.h"
#include <string>
#include "BaseProcedural.h"

class CTextureElement
{
// Construction
public:
	CTextureElement();
	CTextureElement(CColor&);
	CTextureElement(CBaseProcedural*);

// Attributes
protected:
	float				m_k;			//Le coefficient
	CColor				m_Color;		//La couleur éventuelle
	CBaseProcedural	   *m_pProcedure;	//L'algo de calcul de la couleur si besoin

public:
	inline	void		SetCoeff(float k)				{m_k=k;}
	inline	void		SetColorGeneral(CColor& color)	{m_Color=color*m_k;}
	inline	void		SetColor(const CColor& color)	{m_Color=color;}
	inline	void		SetColor(float Position,const CColor& color)	{m_pProcedure->SetColor(Position,color);}
			void		SetProcedural(CBaseProcedural *pProc);	
	inline  TypeColorMap& GetColorMap()					{return m_pProcedure->GetColorMap();}

	inline	bool		IsColor() const						{return m_pProcedure==NULL;}
	inline	bool		IsTexture() const					{return m_pProcedure!=NULL;}
	inline	bool		IsNotNull()	const					{return m_k!=0.0;}
	inline	float		GetCoeff()	const					{return m_k;}
	inline	CColor		GetColor() const					{return m_Color;}
	inline  CColor		GetColor(const CCoord& coord,
								 const CCoord& objcenter) const	{if(m_pProcedure!=NULL) return(m_pProcedure->GetColor(coord,objcenter)); else return(m_Color);}
	std::string GetType();
	inline	CBaseProcedural*	GetProcedural()				{return m_pProcedure;}
	void	ChangeFunctionNoise(CNoise3D *pNoise);

	virtual ~CTextureElement();

public:
	CTextureElement&	operator =  (const CTextureElement&);

	inline	void GetOutputStream(ostream& o)	const			{if(m_pProcedure!=NULL) m_pProcedure->GetOuputStream(o);};
	friend ostream&	operator<<(ostream& o,const CTextureElement& c);
};

#endif

