/////Etat classe : VALIDE

#ifndef _CBASEINTERSECTION
#define _CBASEINTERSECTION

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "BaseGeometry.h"
#include "Vector.h"

class CBaseMatiere;

class CBaseIntersection
{
// Construction
public:
	CBaseIntersection();
	CBaseIntersection(const CBaseIntersection&);

// Attributes
protected:

	double			m_Distance;     // Distance entre le point d'intersection et l'origine du rayon
	CBaseGeometry*	m_pObjet;       // Objet intersecte par le rayon
	CBaseMatiere*	m_pMatiere;
	CCoord			m_Point;		// Point d'intersection
	CVector			m_Normal;		// Normale de l'objet au point d'intersection
	double			m_IndiceMilieu; // Indice de milieu apres l'intersection

// Operations
public:
	inline	void	SetDistance(double Dist,const CCoord &coord)		{m_Distance=Dist; m_Point=coord;};
	inline	double	GetDistance() const				{return(m_Distance);};
	inline	double	GetDistanceTolerance() const	{return(m_pObjet->GetDistanceTolerance());};

	inline	void	SetObjet(CBaseGeometry *pObj)	{m_pObjet=pObj;};
	inline  CBaseGeometry* GetObjet()				{return m_pObjet;}

	inline	void	SetNormal(CVector& vect)		{m_Normal=vect;};
	inline  CVector GetNormal()	const				{return m_Normal;}

	inline	void	SetMilieu(double Im)			{m_IndiceMilieu=Im;};
	inline	double	GetMilieu()	const				{return(m_IndiceMilieu);};

	inline  void	SetMatiere(CBaseMatiere *pMat)  {m_pMatiere=pMat;m_pMatiere->AddRef();}
	inline  const   CBaseMatiere* GetMatiere()	const		{return m_pMatiere;}

	inline  CColor	GetColorDiffuse()	const 	 {return m_pMatiere->GetColorDiffuse(m_Point,m_pObjet->GetTranslate());}
	inline  CColor	GetColorSpecular()	const 	 {return m_pMatiere->GetColorSpecular(m_Point,m_pObjet->GetTranslate());}

	//opérateurs
	CBaseIntersection operator = (const CBaseIntersection&);

// Implementation
public:
	virtual ~CBaseIntersection();

	// Generated message map functions
protected:
};

#endif