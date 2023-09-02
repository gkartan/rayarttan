#pragma warning(disable : 4786)

#include "stdio.h"
#include "TextureElement.h"
#include "ProcSimpleNoiseMatiere.h"

CTextureElement::CTextureElement()
{
	m_pProcedure=NULL;
	m_k=0;
}

CTextureElement::CTextureElement(CColor &param)
{
	m_pProcedure=NULL;
	m_k=0;
	m_Color=param;
}

CTextureElement::CTextureElement(CBaseProcedural *pProcedure)
{
	m_pProcedure=pProcedure;

	if(m_pProcedure!=NULL)
		m_pProcedure->AddRef();
}

CTextureElement::~CTextureElement()
{
	if(m_pProcedure!=NULL)
		m_pProcedure->Release();	//destroy procedure if nobody have it
}


/////A REVOIR
/////LA FONCTION SIMPLENOISE N'est PAS A AFFECTER ICI
/////A VERIFIER DANS LES SCHEMAS UML
void CTextureElement::ChangeFunctionNoise(CNoise3D *pNoise)
{
	if(m_pProcedure==NULL)
	{
		m_pProcedure=new CProcSimpleNoiseMatiere;
		m_pProcedure->AddRef();
	}
		
		
	m_pProcedure->ChangeFunctionNoise(pNoise);
}

std::string CTextureElement::GetType()
{
	if(m_pProcedure!=NULL) 
		return(m_pProcedure->GetType()); 
	else 
		return(std::string("Solid"));
}

CTextureElement&	CTextureElement::operator =  (const CTextureElement &Param)
{
	m_k=Param.m_k;
	m_Color=Param.m_Color;

	if(Param.m_pProcedure==NULL)
	{
		if(m_pProcedure!=NULL) m_pProcedure->Release();
	} else {
		Param.m_pProcedure->AddRef();
	}

	if(m_pProcedure!=NULL) m_pProcedure->Release();
	m_pProcedure=Param.m_pProcedure;

	return(*this);
}

void		CTextureElement::SetProcedural(CBaseProcedural *pProc)
{
	if(pProc!=NULL)
		pProc->AddRef();
	else 
		if(m_pProcedure!=NULL)
			m_pProcedure->Release();

	m_pProcedure=pProc; 
}

ostream&	operator<<(ostream& o,const CTextureElement& c)
{
	if(c.IsColor())
	{
		//if(m_k!=0)
		//	o << " "
			
		o << " " << c.GetColor() << "\n";
	} else {
		c.GetOutputStream(o);
	}

	return o;
}


