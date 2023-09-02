/////Etat classe : VALIDE

#ifndef _BASEGEOMETRY
#define _BASEGEOMETRY

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "BaseMatiere.h"
#include "Vector.h"
#include "MatrixTransform.h"
#include <ostream.h>

class CRay;

class  CBaseGeometry
{
// Construction
public:
	CBaseGeometry();

// Attributes
protected:
	CBaseMatiere    *m_pMatiere;

	double			m_DistanceTolerance; //tolerance en distance pour éviter les artefacts


	CMatrixTransform m_Trans;			//Matrice de tranformation par rapport à l'origine

	////Sauvegarde des vecteurs de transformation
	////Non utile dans les calculs
	CVector			m_Translate;
	CVector			m_Scale;
	CVector			m_Rotate;

protected:
	virtual	void	ForceEqual(CBaseGeometry&)=0;
	void	Equal(CBaseGeometry&);					//operator = descendant
public:
	virtual CBaseGeometry*	Instantiate()=0;		//instancie un nouvel objet de ce type

// Operations
public:
	inline  double  GetDistanceTolerance() const {return m_DistanceTolerance;};
	virtual	bool	Intersection(CRay&)=0;
	virtual bool	AddIntersect(CRay&,double Distance)=0;

	virtual CVector	Normal(const CCoord &coord)=0;
	virtual	void	Scale(const CVector&);
	virtual	void	Rotate(const CVector&);
	virtual	void	Translate(const CVector&);
	virtual void	RazTransform();
	CVector			GetScale()		{return m_Scale;}
	CVector			GetRotate()		{return m_Rotate;}
	CVector			GetTranslate()	{return m_Translate;}

	virtual CBaseGeometry* GetBoundSphere()=0;

	virtual CBaseGeometry& operator=(CBaseGeometry&);

public:
	inline bool	GetExistTrans()	const		  {return m_Trans.GetExist();}
	inline virtual void	SetMatiere(CBaseMatiere *pMatiere) {m_pMatiere=pMatiere;m_pMatiere->AddRef();}
	inline void	SetTrans(const CMatrixTransform &Trans) {m_Trans=Trans;}
	inline const CMatrixTransform&	GetTrans()	const	{return m_Trans;}
	inline CBaseMatiere *GetMatiere()			{return m_pMatiere;}

// Implementation
public:
	virtual ~CBaseGeometry();

public:
	virtual	void	GetOutputStream(ostream&)=0;
};

#endif


