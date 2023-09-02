#include "stdio.h"
#include "BaseGeometry.h"

CBaseGeometry::CBaseGeometry()
{
	m_DistanceTolerance=0;
	m_pMatiere=NULL;
	m_Translate=CVector(0,0,0);
	m_Rotate=CVector(0,0,0);
	m_Scale=CVector(0,0,0);
}

CBaseGeometry::~CBaseGeometry()
{
	if(m_pMatiere!=NULL)
		m_pMatiere->Release();
}

void	CBaseGeometry::Scale(const CVector &Vect)
{
	if(Vect!=CVector(0,0,0))
	{
		CMatrixTransform	Matrix;
		Matrix.Scale(Vect);
		m_Trans.Compose(Matrix);
		m_Scale=Vect;
	}
}

void	CBaseGeometry::Rotate(const CVector &Vect)
{
	if(Vect!=CVector(0,0,0))
	{
		CMatrixTransform	Matrix;
		Matrix.Rotate(Vect);
		m_Trans.Compose(Matrix);
		m_Rotate=Vect;
	}
}

void	CBaseGeometry::Translate(const CVector &Vect)
{
	if(Vect!=CVector(0,0,0))
	{
		CMatrixTransform	Matrix;
		Matrix.Translate(Vect);
		m_Trans.Compose(Matrix);
		m_Translate=Vect;
	}
}

void	CBaseGeometry::RazTransform()
{
	m_Trans.Initialize();
	m_Rotate=CVector(0,0,0);
	m_Scale=CVector(0,0,0);
	m_Translate=CVector(0,0,0);
}

CBaseGeometry& CBaseGeometry::operator=(CBaseGeometry &Origin)
{
	ForceEqual(Origin);
	Equal(Origin);
	return(*this);
}

void	CBaseGeometry::Equal(CBaseGeometry &Origin)
{
	m_DistanceTolerance=Origin.m_DistanceTolerance;
	m_Trans=Origin.m_Trans;		
	m_pMatiere=Origin.m_pMatiere;
	m_Translate=Origin.m_Translate;
	m_Rotate=Origin.m_Rotate;
	m_Scale=Origin.m_Scale;


	if(m_pMatiere!=NULL)
		m_pMatiere->AddRef();

}

