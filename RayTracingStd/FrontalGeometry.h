//***************************************************************************************
//* CLASSE FRONTALE DE GESTION DES OBJETS GEOMETRIQUES
//* Mots clés : automate, frontal, geometrie
/////Etat classe : EN COURS


#ifndef _FRONTALGEOMETRY
#define _FRONTALGEOMETRY

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#define NOMINMAX
#include "BaseGeometry.h"
#include "TypeDefinitions.h"
#include <map>
#include <ostream.h>
#include "BaseListGeometry.h"

class CFrontalGeometry
{
// Construction
public:
	inline CFrontalGeometry();
	inline virtual ~CFrontalGeometry();

	inline CBaseListGeometry* GetListGeometry() const {return m_pListGeometry;}

	inline  void	AddGeo(CBaseGeometry *pObjet)			{m_pListGeometry->Add(pObjet);}
	inline	void	ClearAndUpdate(CBaseGeometry *pObjet)	{m_pListGeometry->ClearAndUpdate(pObjet);};
	inline  void	Update(CBaseGeometry *poldObjet,CBaseGeometry *pObjet) 
	{m_pListGeometry->Update(poldObjet,pObjet);};

protected:
	CBaseListGeometry		*m_pListGeometry;

public:
	inline friend ostream&	operator<<(ostream& o,const CFrontalGeometry& c);
};


CFrontalGeometry::CFrontalGeometry()
{	
	//Création de la liste des lumières
	m_pListGeometry=new CBaseListGeometry;
}

CFrontalGeometry::~CFrontalGeometry()
{
	delete m_pListGeometry;
	m_pListGeometry=NULL;
}


ostream&	operator<<(ostream& o,const CFrontalGeometry& c)
{
	o << *(c.m_pListGeometry);

	return o;
}


#endif