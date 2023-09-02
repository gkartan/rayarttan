//***********************************************************************************
//* CLASSE FRONTALE DE GESTION DES MATIERES
//* Mots clés : automate, frontal, matiere
//*
//* Elle sert à manipuler l'ensemble des matières présentes dans la scène
//* Notamment pour les présenter à l'IHM

/////Etat classe : EN COURS
#pragma warning(disable : 4786)

#ifndef _FRONTALMATERIAL
#define _FRONTALMATERIAL
#undef min
#undef max
#include <map>
#include <string>
#include "TypeDefinitions.h"
#include "BaseMatiere.h"
#include "Noise3DGranite.h"
#include <ostream.h>
#include "CommonMatiere.h"
#include "ProcSimpleNoiseMatiere.h"
#include "ProcGradientMatiere.h"

typedef std::map<std::string, ENUM_TYPETEXTURE, std::less<std::string>, std::allocator<ENUM_TYPETEXTURE> >	TEXTURETYPE; 


class CFrontalMaterial
{
// Construction
public:
	inline CFrontalMaterial();

// Attributes
protected:
	TypeVectorMaterial		*m_pListMaterial;
	CBaseMatiere			*m_pCurrentMatiere;

	TEXTURETYPE				m_listTypeTexture;

// Operations publiques
public:
	inline	void					SetCurrentLight(int Index);
	inline	void					SetCurrentMaterial(CBaseMatiere *pMatiere)		{m_pCurrentMatiere=pMatiere;};
	inline	void					SetCurrentMaterial(int Index);

	inline	CBaseMatiere*			GetCurrentMaterial()							{return m_pCurrentMatiere;};
	inline	void					DelCurrentMaterial();

	inline	TypeVectorMaterial*		GetListMaterial() const							{return m_pListMaterial;}
	inline  CBaseMatiere*			GetMaterial(const std::string&);

	/****************Modification de la liste*************************/
	inline  void					AddMatiere(const std::string &);
	inline  void					AddMatiere(CBaseMatiere *pMaterial)				{m_pListMaterial->push_back(pMaterial); pMaterial->AddRef();}

	/****************Recherche****************************************/
	inline  bool					IsMaterial(const std::string &);

	inline	void	SetColorDiffuse(const CColor &color)		{if(m_pCurrentMatiere!=NULL) m_pCurrentMatiere->SetColorDiffuse(color);}
	inline	void	SetColorAmbient(const CColor &color)		{if(m_pCurrentMatiere!=NULL) m_pCurrentMatiere->SetColorAmbient(color);}
	inline	void	SetColorSpecular(const CColor &color)		{if(m_pCurrentMatiere!=NULL) m_pCurrentMatiere->SetColorSpecular(color);}
	inline	void	SetColorTransparent(const CColor &color)	{if(m_pCurrentMatiere!=NULL) m_pCurrentMatiere->SetColorTransparent(color);}

	inline	bool				IsTexture(ENUM_TYPECOLOR Type)	{return((m_pCurrentMatiere==NULL)?false:m_pCurrentMatiere->IsTexture(Type));}
	inline	CTextureElement*	GetTexture(ENUM_TYPECOLOR Type) {return((m_pCurrentMatiere==NULL)?NULL:m_pCurrentMatiere->GetTexture(Type));}

	inline void					ChangeTypeTexture(ENUM_TYPECOLOR,const std::string &str);
// Implementation
public:
	inline virtual ~CFrontalMaterial();

public:
	inline friend ostream&	operator<<(ostream& o,const CFrontalMaterial& c);

};


CFrontalMaterial::CFrontalMaterial()
{
	m_pCurrentMatiere=NULL;
	m_pListMaterial=new TypeVectorMaterial;

	//Init de la liste
	m_listTypeTexture["solid"]=TEXTURE_SOLID;
	m_listTypeTexture["spotted"]=TEXTURE_SPOTTED;
	m_listTypeTexture["granite"]=TEXTURE_GRANITE;
	m_listTypeTexture["gradient"]=TEXTURE_GRADIENT;

}

CFrontalMaterial::~CFrontalMaterial()
{
	if(m_pListMaterial!=NULL)
	{
		//Destruction de la liste et son contenu
		TypeVectorMaterial::iterator	theIterator;
		
		for(theIterator=m_pListMaterial->begin();
			theIterator<m_pListMaterial->end();
			theIterator++)
			{
				CBaseMatiere	*pMaterial=(*theIterator);
				if(pMaterial!=NULL)
				{
					pMaterial->Release();
				}

			}

		delete m_pListMaterial;
		m_pListMaterial=NULL;
	}

}

void CFrontalMaterial::SetCurrentLight(int Index)
{
	if(Index<m_pListMaterial->size())
	{
		m_pCurrentMatiere=(*m_pListMaterial)[Index];
	}
}

///*********************
///Gestion Automate des textures
void	CFrontalMaterial::ChangeTypeTexture(ENUM_TYPECOLOR ColorType,
											const std::string &str)
{
	//On retrouve la bonne classe à l'aide d'une variable
	//de mapping chaine vers classe
	TEXTURETYPE::iterator theIterator=m_listTypeTexture.find(str);
	ENUM_TYPETEXTURE Type=(*theIterator).second;

	CNoise3D			*pNewNoise=NULL;
	CBaseProcedural		*pProc=NULL;

	switch(Type)
	{
		case TEXTURE_SOLID:
			pNewNoise=NULL;///plus de texture
			m_pCurrentMatiere->SetTypeTexture(ColorType,pNewNoise);
		break;
		case TEXTURE_SPOTTED:
			if(m_pCurrentMatiere->GetProcedural(ColorType)==NULL || !m_pCurrentMatiere->GetProcedural(ColorType)->Compatible(TEXTURE_SPOTTED))
			{
				pProc=new CProcSimpleNoiseMatiere;
				m_pCurrentMatiere->SetTypeTexture(ColorType,pProc);
			}
			pNewNoise=new CNoise3D;
			m_pCurrentMatiere->SetTypeTexture(ColorType,pNewNoise);
		break;
		case TEXTURE_GRANITE:
			if(m_pCurrentMatiere->GetProcedural(ColorType)==NULL || !m_pCurrentMatiere->GetProcedural(ColorType)->Compatible(TEXTURE_GRANITE))
			{
				pProc=new CProcSimpleNoiseMatiere;
				m_pCurrentMatiere->SetTypeTexture(ColorType,pProc);
			}
			pNewNoise=new CNoise3DGranite;
			m_pCurrentMatiere->SetTypeTexture(ColorType,pNewNoise);
		break;
		case TEXTURE_GRADIENT:
			pProc=new CProcGradientMatiere;
			m_pCurrentMatiere->SetTypeTexture(ColorType,pProc);
		break;
	}

}

////Recherche de la matiere en O(n/2)
CBaseMatiere*	CFrontalMaterial::GetMaterial(const std::string &MatName)
{
	TypeVectorMaterial::iterator	theIterator;

	for(theIterator=m_pListMaterial->begin();
		theIterator<m_pListMaterial->end();
		theIterator++)
		{
			if((*theIterator)->GetName()==MatName)
			{
				return (*theIterator);
			}
		}

	return NULL;
}

void	CFrontalMaterial::DelCurrentMaterial()
{
	if(m_pListMaterial->size()==0)
	{
		m_pCurrentMatiere=NULL;
		return;
	}

	TypeVectorMaterial::iterator	ItMat;

	for(ItMat=m_pListMaterial->begin();
	ItMat<m_pListMaterial->end();
	ItMat++)
	{
		///Si c'est le bon pointeur
		if((*ItMat)==m_pCurrentMatiere)
		{
			delete (*ItMat);
			m_pListMaterial->erase(ItMat);
			break;
		}
	}

	//la lumière courante devient la première de la liste
	ItMat=m_pListMaterial->begin();
	m_pCurrentMatiere=(*ItMat);
}

void CFrontalMaterial::SetCurrentMaterial(int Index)
{
	if(Index<m_pListMaterial->size())
	{
		m_pCurrentMatiere=(*m_pListMaterial)[Index];
	}

}


void CFrontalMaterial::AddMatiere(const std::string &str)
{
	CBaseMatiere *pMatiere=new CBaseMatiere;

	//Copie de la matiere courante si elle existe
	if(m_pCurrentMatiere!=NULL) *pMatiere=*m_pCurrentMatiere;

	AddMatiere(pMatiere);
	m_pCurrentMatiere=pMatiere;
	m_pCurrentMatiere->SetName(str);
}

////////////****
////////////Test si le nom correspond à une matiere
bool CFrontalMaterial::IsMaterial(const std::string &str)
{
	TypeVectorMaterial::iterator	ItMat;

	for(ItMat=m_pListMaterial->begin();
	ItMat<m_pListMaterial->end();
	ItMat++)
	{
		///Si c'est le bon pointeur
		if((*ItMat)->GetName().compare(str)==0)
		{		
			return true;
		}
	}

	return false;
}

/***********************************************************/
/*************************************************************/

ostream&	operator<<(ostream& o,const CFrontalMaterial& c)
{
	TypeVectorMaterial::iterator	theIterator;

	for(theIterator=c.GetListMaterial()->begin();
		theIterator<c.GetListMaterial()->end();
		theIterator++)
		{
			(*theIterator)->GetOuputStream(o);
		}

	return o;
}


#endif