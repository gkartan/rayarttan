//***************************************************************************************
//* CLASSE FRONTALE DE GESTION DES LUMIERES
//* Mots clés : automate, frontal, lumiere
/////Etat classe : EN COURS


#ifndef _FRONTALLIGHT
#define _FRONTALLIGHT

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#undef min
#undef max
#include "BaseLight.h"
#include "LightAmbient.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "TypeDefinitions.h"
#include <map>
#include <ostream.h>

typedef enum
{
	LIGHT_AMBIENT=0,
	LIGHT_POINT,
	LIGHT_SPOT,
} ENUM_LIGHTTYPE;

typedef std::map<std::string, ENUM_LIGHTTYPE, std::less<std::string>, std::allocator<ENUM_LIGHTTYPE> >	LIGHTTYPE; 

class CFrontalLight
{
// Construction
public:
	inline CFrontalLight();
	inline virtual ~CFrontalLight();

	///************Méthodes d'accès
	inline TypeVectorLight* GetListLight() const {return m_pListLight;}
	inline void	SetCurrentLight(int Index);
	inline void	SetCurrentLight(CBaseLight *pLight) {m_pCurrentLight=pLight;};
	inline CBaseLight*	GetCurrentLight() {return m_pCurrentLight;};

	///*****Modification attributs de la lumière courante
	inline	void	SetColor(CColor &color) {if(m_pCurrentLight!=NULL) m_pCurrentLight->SetColor(color);}

	///*****Modification de la liste
	inline  void	AddLight(const std::string &);
	inline  void	AddLight(CBaseLight *pLight) {m_pListLight->push_back(pLight);}
	inline  void	DelLight(CBaseLight *pLight) {/**Rien pour l'instant -- non utilisé**/}
	inline	void	DelCurrentLight();


	////Test typage --> pour ihm
	////L'ihm doit savoir si certain valeurs sont disponibles pour l'affichage
	inline bool				GetIsPosition() const	{return ((m_pCurrentLight==NULL)?false:m_pCurrentLight->GetIsPosition());}
	inline CCoord			GetPosition()	const   {return ((m_pCurrentLight==NULL)?CCoord(0,0,0):m_pCurrentLight->GetPosition());}
	inline void				SetPosition(const CCoord &coord)	const   {if(m_pCurrentLight!=NULL) m_pCurrentLight->SetPosition(coord);}

	inline  std::string GetType() {return((m_pCurrentLight==NULL)?"":m_pCurrentLight->GetType());};

	inline	void	ChangeType(const std::string &NewType,bool Effacement=true);
protected:
	TypeVectorLight		*m_pListLight;
	CBaseLight			*m_pCurrentLight;
	LIGHTTYPE			m_listType;


	// Generated message map functions
protected:

	//Operators
public:
	inline friend ostream&	operator<<(ostream& o,const CFrontalLight& c);

};


CFrontalLight::CFrontalLight()
{	
	//Remplissage des types
	m_listType["ambient"]=LIGHT_AMBIENT;
	m_listType["pointlight"]=LIGHT_POINT;
	m_listType["spotlight"]=LIGHT_SPOT;

	//Création de la liste des lumières
	m_pListLight=new TypeVectorLight;
	m_pCurrentLight=NULL;
}

CFrontalLight::~CFrontalLight()
{
	if(m_pListLight!=NULL)
	{
		//Destruction de la liste et son contenu
		TypeVectorLight::iterator	theIterator;
		
		for(theIterator=m_pListLight->begin();
			theIterator<m_pListLight->end();
			theIterator++)
			{
				CBaseLight	*pLight=(*theIterator);
				if(pLight!=NULL)
				{
					delete pLight;
				}

			}

		delete m_pListLight;
		m_pListLight=NULL;
	}

	//Ne pas détruire m_pCurrentLight --> il était dans la liste
}

void CFrontalLight::SetCurrentLight(int Index)
{
	if(Index<m_pListLight->size())
	{
		m_pCurrentLight=(*m_pListLight)[Index];
	}

}


///**********************************************************
///*Gestion automate
void	CFrontalLight::ChangeType(const std::string &NewType,bool Effacement)
{
	//On retrouve la bonne classe à l'aide d'une variable globale
	//de mapping chaine vers classe
	LIGHTTYPE::iterator theIterator=m_listType.find(NewType);
	ENUM_LIGHTTYPE Type=(*theIterator).second;

	CBaseLight *pNewLight=NULL;

	switch(Type)
	{
		case LIGHT_AMBIENT:
			pNewLight=new CLightAmbient;
		break;

		case LIGHT_POINT:
			pNewLight=new CLightPoint;
		break;

		case LIGHT_SPOT:
			pNewLight=new CLightSpot;
		break;

		default:
			//no changes
			return;
	}

	*pNewLight=*m_pCurrentLight;	//On remet les valeurs dans la nouvelle lumière

	//On met à jour la liste
	//On le fait en 2 passes
	//Une première étape pour insérer le nouvel élément juste derrière l'ancien
	//Une seconde étape pour effacer l'ancien
	//ATTENTION : Le faire en 1 boucle pose problème 
	//			  les itérateurs ne doivent pas être à jour dans ce cas
	TypeVectorLight::iterator	ItLight;
	
	if(Effacement)
	{
		for(ItLight=m_pListLight->begin();
			ItLight<m_pListLight->end();
			ItLight++)
			{
				///Si c'est le bon pointeur
				if((*ItLight)==m_pCurrentLight)
				{
					m_pListLight->insert(ItLight,pNewLight);
					break;
				}
			}

		DelCurrentLight();
	} else
		m_pListLight->push_back(pNewLight);


	m_pCurrentLight=pNewLight;
}


//***********************************
//**Ajout/effacement de lumières
//***********************************
void	CFrontalLight::AddLight(const std::string &str)
{
	if(m_pListLight->size()==0 || m_pCurrentLight==NULL) m_pCurrentLight=new CLightPoint;

	ChangeType(m_pCurrentLight->GetType(),false);
	m_pCurrentLight->SetName(str);
}


void	CFrontalLight::DelCurrentLight()
{
	if(m_pListLight->size()==0)
	{
		m_pCurrentLight=NULL;
		return;
	}

	TypeVectorLight::iterator	ItLight;

	for(ItLight=m_pListLight->begin();
	ItLight<m_pListLight->end();
	ItLight++)
	{
		///Si c'est le bon pointeur
		if((*ItLight)==m_pCurrentLight)
		{
			delete (*ItLight);
			m_pListLight->erase(ItLight);
			break;
		}
	}

	//la lumière courante devient la première de la liste
	ItLight=m_pListLight->begin();
	m_pCurrentLight=(*ItLight);
}



/******************************************************/
/******Méthodes globales*******************************/
/******************************************************/
ostream&	operator<<(ostream& o,const CFrontalLight& c)
{
	TypeVectorLight::iterator	ItLight;
	
	for(ItLight=c.GetListLight()->begin();
		ItLight<c.GetListLight()->end();
		ItLight++)
		{
			(*ItLight)->GetOuputStream(o);
		}

	return o;
}


#endif