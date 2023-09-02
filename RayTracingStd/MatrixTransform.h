/////Etat classe : EN COURS

#ifndef	_CMATRIXTRANSFORM
#define _CMATRIXTRANSFORM
#pragma warning(disable : 4530)

#include "MatrixSqr.h"
#include "Coord.h"
#include "Vector.h"
#include "BaseVector.h"

class CMatrixTransform
{
// Construction
public:
	CMatrixTransform();
	CMatrixTransform(const CMatrixSqr&);


private:
	CMatrixSqr m_Mat;
	CMatrixSqr m_InvMat;

	bool		  m_bExist;

//Operations
public:
	inline void		SetExist(bool bParam) {m_bExist=bParam;};
	inline bool		GetExist()	const	  {return m_bExist;}

	void	Initialize();

	///Operations de conversion vers les quaternions
	void	QuatToMat(const CBaseVector<4,double>&);
	void	MatToQuat(CBaseVector<4,double>&) const;

	//***********************************************
	///operations modifiant la matrice
	void			Scale(const CVector&);
	void			Translate(const CVector&);
	void			Rotate(const CVector &Vect);

	///N'utilise pas la matrice inverse
	void			SimpleRotate(const CVector &Vect);

	//Ne touche pas à la matrice existante (composition + ...) et pas de calcul inverse
	void			SimpleComposeAndRotate(const CVector &Vect);

	///operations calculant la transformation
	///a l'aide de la matrice
	CCoord			Trans(const CCoord&)	const;
	CVector			Trans(const CVector&)	const;
	CCoord			InvTrans(const CCoord&)	const;
	CVector			InvTrans(const CVector&)const;
	CVector			TransNormal(const CVector&)	const;

	void			Compose(const CMatrixTransform&);


	//***********************************************
	//Opérations spéciales modifiant la matrice
	//rotation d'un angle autour d'un axe --> modifie la matrice
	void			AxisRotate(const CVector &Vect, double angle);
	//***********************************************

	//***********************************************
	//Calculs de la transformation pour aboutir à un changement de système de coordonnées
	//Le but étant de se ramener à un système canonique <1,1,1>
	//Modifie la matrice
	void			ChangeCoordinateSystem(const CCoord &Origin,const CVector &Up,double Radius, double Length );


//Operators
public:
	CMatrixTransform& operator = (const CMatrixTransform&);

// Implementation
public:
	virtual ~CMatrixTransform();
};

#endif
