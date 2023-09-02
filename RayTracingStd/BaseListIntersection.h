/////Etat classe : VALIDE

#ifndef _BASELISTINTERSECTION
#define _BASELISTINTERSECTION

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include <numeric>
#include "TypeDefinitions.h"
#include "BaseIntersection.h"
#include "Color.h"

class CBaseListIntersection
{
// Construction
public:
	CBaseListIntersection();

// Attributes
protected:
	TypeVectorIntersection	m_ListIntersection;
	long					m_NbElements;

	//
	static double					m_FilterDist;	//Distance utilisé pour le filtrage des intersections (méthodes FilterDist)

// Operations
public:
	inline long GetSize() const {return m_NbElements;}

	void Add(CBaseIntersection *);
	void RemoveAll();

	////////////////////////////////////////
	///Opérateurs binaires utilisé par la STL
	static bool		OperatorPrec(const CBaseIntersection *Param1,
								 const CBaseIntersection *Param2);
	static bool		OperatorDistInf(const CBaseIntersection *Param1);
	static bool		OperatorDistSup(const CBaseIntersection *Param1);
	static CColor	MultColorTransp(CColor&,
									const CBaseIntersection*);

	////////////////////////////////////////
	///Algorithmes appliqués à la liste
	void	Sort();		//Tri en fonction de la distance à l'intersection (Z-Buffer)
	void	FilterDistSup(double);	//Effacement en fonction de la distance à l'intersection (Z-Buffer)
	void	FilterDistInf(double);	//Effacement en fonction de la distance à l'intersection (Distance trop petite négative ou nulle)
	CColor	GetColorResult();

	template <class TVALUE,class TOP>
		TVALUE Accumulate(TVALUE ValueInit,TOP BinaryOp)
	{
		return(std::accumulate(m_ListIntersection.begin(),
						m_ListIntersection.end(),
						ValueInit,
						BinaryOp));
	}

	///opérateurs
	CBaseIntersection*		  operator[] (long Index);
	//friend bool				  operator<  (CBaseIntersection&,CBaseIntersection&);

// Implementation
public:
	virtual ~CBaseListIntersection();

};

#endif