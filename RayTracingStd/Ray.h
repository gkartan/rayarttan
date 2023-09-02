/////Etat classe : VALIDE

#ifndef _RAY
#define _RAY

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "Coord.h"
#include "Vector.h"
#include "Color.h"
#include "TypeDefinitions.h"
#include "BaseListIntersection.h"

class CRay
{
// Construction
public:
	CRay();
	CRay(const CRay &Ray);
	CRay(const CCoord&,const CVector&);
	CRay(const CCoord&,const CVector&, char WaveLength);

//Attributes
protected:
	bool					m_bDestroyList;
	bool					m_bInside;		//pour savoir si c'est un rayon réfracté
	CCoord					m_Coord;
	CVector					m_Direction;

	CBaseListIntersection	m_ListIntersection;

	//used for dispersion
	bool					m_bIsMonochrom;	//vrai si c'est un rayon monochromatique
	//double					m_Wavelength;
	char					m_PrimaryColor;	//est-ce un rayon rouge,vert ou bleu?

//operations
public:
	void	SetRayClear(const CRay &Ray);
	CRay&	operator=(const CRay&);

	inline const CVector&	GetDirect() const {return m_Direction;};
	inline void				SetDirect(CVector &Vect) {m_Direction=Vect; m_Direction.Normalize();};
	inline const CCoord&	GetOrigin() const {return m_Coord;};
	inline void				SetOrigin(CCoord &Orig) {m_Coord=Orig;};
	inline bool				IsIntersection() const {return m_ListIntersection.GetSize()!=0;}

	inline bool				GetIsMonochrom()				{return m_bIsMonochrom;}
	inline void				SetIsMonochrom(bool param)		{m_bIsMonochrom=param;}

					bool	Intersections(TypeVectorGeometry &ListGeometry);
					bool	AddIntersect(CBaseIntersection*);
					bool	FilterDist(double);


	template <class TVALUE,class TOP>
		TVALUE Accumulate(TVALUE ValueInit,TOP BinaryOp)
	{
		return(m_ListIntersection.Accumulate(ValueInit,BinaryOp));
	}

// Implementation
public:
	virtual ~CRay();
};

#endif