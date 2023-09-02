/////Etat classe : EN COURS

#ifndef _BASELISTGEOMETRY
#define _BASELISTGEOMETRY

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#define NOMINMAX
#include "BaseGeometry.h"
#include "TypeDefinitions.h"
#include <map>
#include <ostream.h>
#include <numeric>
#include "TypeDefinitions.h"
#include "BaseIntersection.h"
#include "Color.h"

class CBaseListGeometry
{
// Construction
public:
	inline CBaseListGeometry();

// Attributes
protected:
	TypeVectorGeometry		m_ListGeometry;

// Operations
public:
	inline  void	Add(CBaseGeometry *);
	inline	void	ClearAndUpdate(CBaseGeometry *pObjet);
	inline  void	Update(CBaseGeometry *poldObjet,CBaseGeometry *pObjet);
	inline	void	RemoveAll();
	inline	TypeVectorGeometry&		GetVectorGeometry() {return m_ListGeometry;}

// Implementation
public:
	inline virtual ~CBaseListGeometry();

	inline virtual CBaseListGeometry& operator=(CBaseListGeometry&);

public:
	inline friend ostream&	operator<<(ostream& o,CBaseListGeometry& c);


};

CBaseListGeometry::CBaseListGeometry()
{
}

CBaseListGeometry::~CBaseListGeometry()
{
	RemoveAll();
}

void	CBaseListGeometry::RemoveAll()
{
	//Destruction du contenu de la liste
	TypeVectorGeometry::iterator	theIterator;
	
	for(theIterator=m_ListGeometry.begin();
		theIterator<m_ListGeometry.end();
		theIterator++)
		{
			CBaseGeometry	*pGeometry=(*theIterator);
			if(pGeometry!=NULL)
			{
				delete pGeometry;
			}

		}

	m_ListGeometry.clear();
}


void CBaseListGeometry::Add(CBaseGeometry *pObjet)
{
	m_ListGeometry.push_back(pObjet);
}

void CBaseListGeometry::ClearAndUpdate(CBaseGeometry *pObjet)
{
	m_ListGeometry.clear();
	m_ListGeometry.push_back(pObjet);
}

void CBaseListGeometry::Update(CBaseGeometry *poldObjet,CBaseGeometry *pObjet)
{
	TypeVectorGeometry::iterator	theIterator;

	for(theIterator=m_ListGeometry.begin();
	theIterator<m_ListGeometry.end();
	theIterator++)
	{
		CBaseGeometry	*pGeometry=(*theIterator);
		if(pGeometry==poldObjet)
		{
			//on efface l'ancien objet
			m_ListGeometry.erase(theIterator);
			break;
		}

	}

	m_ListGeometry.push_back(pObjet);
}

CBaseListGeometry& CBaseListGeometry::operator=(CBaseListGeometry &Origin)
{
	//On efface l'ancienne liste
	RemoveAll();

	TypeVectorGeometry::iterator	theIterator;

	for(theIterator=Origin.m_ListGeometry.begin();
	theIterator<Origin.m_ListGeometry.end();
	theIterator++)
	{
		CBaseGeometry	*pGeometry=(*theIterator);

		CBaseGeometry	*pNewGeometry=pGeometry->Instantiate();
		*pNewGeometry=*pGeometry;

		Add(pNewGeometry);
	}

	return(*this);

}

ostream&	operator<<(ostream& o,CBaseListGeometry& c)
{
	////On sauvegarde tous les élements géométriques
	TypeVectorGeometry::iterator	theIterator;

	for(theIterator=c.m_ListGeometry.begin();
		theIterator<c.m_ListGeometry.end();
		theIterator++)
		{
			CBaseGeometry	*pGeometry=(*theIterator);
			if(pGeometry!=NULL)
			{
				pGeometry->GetOutputStream(o);
			}

		}

	return o;
}



#endif