//////////////////////////////////////////////////////////////////////////////
///Définitions d'une structure réunissant les composants du calcul d'une image
//////////////////////////////////////////////////////////////////////////////
#ifndef _RENDERSTRUCTURE
#define _RENDERSTRUCTURE

#pragma	warning(disable : 4305)	//double to float

#define NOMINMAX 
#include "TypeDefinitions.h"

#include "FrontalCamera.h"
#include "FrontalLight.h"
#include "FractalZ2.h"
#include "Quaternion.h"
#include "CamParalPlane.h"
#include "LightPoint.h"
#include "FrontalFractal.h"
#include "FrontalGeometry.h"
#include "FrontalMaterial.h"
#include "ModelLightMetallicFresnel.h"
#include "ProcSimpleNoiseMatiere.h"
#include "Noise3DGranite.h"
#include "Plan.h"
#include "Structures.h"
#include "BaseImage.h"

typedef CQuaternion<double,HYPERFONCTION_NORMAL> TypeDefaultAlgebra;
typedef enum
{
	ALGO_NORMAL=0,
	ALGO_ANTIALIAS
} TYPE_ALGO;

class wxImage;
class CRenderStructure
{
public:
		inline CRenderStructure();
		inline virtual ~CRenderStructure();

		inline void SetDefault();
		inline void	BuildFrontals();

public:
		CBaseImage*				GetImage() const		{return m_pImage;}

		CBaseCamera*			GetCamera()	const		{return m_pCamera->GetCamera();}
		CBaseListGeometry*		GetListGeometry() const {return m_pGeometry->GetListGeometry();}
		TypeVectorLight*		GetListLight()	const	{return m_pLight->GetListLight();}
		
		CFrontalCamera*			GetFrontalCamera() const		{return m_pCamera;}	
		CFrontalLight*			GetFrontalLight()  const		{return m_pLight;}	
		CFrontalFractal*		GetFrontalFractal()const		{return m_pFractal;}	
		CFrontalGeometry*		GetFrontalGeometry() const	{return m_pGeometry;}
		CFrontalMaterial*		GetFrontalMaterial() const	{return m_pMatiere;}
		
		CAlgorithmModifier&		GetRefStructAlgo()				{return m_StructAlgo;}
		CAlgorithmModifier		GetStructAlgo()	const			{return m_StructAlgo;}

		TYPE_ALGO				GetTypeAlgo()	const {return m_TypeAlgo;}
		void					SetTypeAlgo(TYPE_ALGO Algo)	{m_TypeAlgo=Algo;}

		void					SetComputing(bool bCompute) {m_bCompute=bCompute;}
		bool					GetComputing()				{return m_bCompute;}
protected:
		CBaseImage				*m_pImage;
		CFrontalCamera			*m_pCamera;
		CFrontalGeometry		*m_pGeometry;
		CFrontalLight			*m_pLight;
		CFrontalMaterial		*m_pMatiere;
		CFrontalFractal			*m_pFractal;
		TYPE_ALGO				m_TypeAlgo;
		CAlgorithmModifier		m_StructAlgo;
		bool					m_bCompute;

	////Operators
public:
		inline friend	ostream&	operator<<(ostream& o,const CRenderStructure& c);

};

CRenderStructure::CRenderStructure()
{
	m_pImage=NULL;
	m_pCamera=NULL;
	m_pLight=NULL;
	m_pFractal=NULL;
	m_pGeometry=NULL;
	m_pMatiere=NULL;
	m_bCompute=false;
	m_TypeAlgo=ALGO_NORMAL;
}

CRenderStructure::~CRenderStructure()
{
	if(m_pImage!=NULL)
	{
		delete m_pImage;
	}
	if(m_pCamera!=NULL)
	{
		delete m_pCamera;
		m_pCamera=NULL;
	}
	if(m_pLight!=NULL)
	{
		delete m_pLight;
		m_pLight=NULL;
	}
	if(m_pGeometry!=NULL)
	{
		delete m_pGeometry;
		m_pGeometry=NULL;
	}

	if(m_pFractal!=NULL)
	{
		delete m_pFractal;
		m_pFractal=NULL;
	}

	if(m_pMatiere!=NULL)
	{
		delete m_pMatiere;
		m_pMatiere=NULL;
	}

}

void CRenderStructure::SetDefault()
{  
  m_TypeAlgo=ALGO_NORMAL;

  //Definitions des lumières
  m_pLight=new CFrontalLight;
  CLightPoint *pLightPoint1=new CLightPoint(CColor(1,1,1),CCoord(0,10,10),"Light1");
  CLightAmbient *pLightAmbient=new CLightAmbient(CColor(0.2,0.2,0.2),"Light4");
  m_pLight->AddLight(pLightPoint1);
  m_pLight->AddLight(pLightAmbient);

  m_pMatiere=new CFrontalMaterial;

  //////ATTENTION -->  A VOIR LA DESTRUCTION DU MODELE
  //CModelLightMetallicFresnel	*pMetal=new CModelLightMetallicFresnel(10,1); 
  CBaseMatiere *pMatiereGold=new CBaseMatiere(CColor(0,0,0));
  
  pMatiereGold->SetColorDiffuse(CColor(0,0.5,1));
  pMatiereGold->SetColorAmbient(CColor(0.12,0.1175,0.1115));
  pMatiereGold->SetColorSpecular(CColor(0.75,0.6875,0.5375));
  //pMatiereGold->SetModelLight(pMetal);
  pMatiereGold->SetName("Gold");
  m_pMatiere->AddMatiere(pMatiereGold);

  m_pFractal=new CFrontalFractal;
  CFractalZ2<TypeDefaultAlgebra> *pFractal=new CFractalZ2<TypeDefaultAlgebra>(TypeDefaultAlgebra(0.745,0,0.113,0.05),7,0.1,0.0);
  pFractal->SetMatiere(pMatiereGold);
  m_pFractal->SetFractal(pFractal,true);

  /*CBaseMatiere *pMatierePlane=new CBaseMatiere(CColor(1,0,0)); 
  CTextureElement TexturePlane;
  CSimpleNoiseMatiere *pProcedureGranite=new CSimpleNoiseMatiere(CColor(1,0,0));
  CNoise3DGranite *pNoise=new CNoise3DGranite;
  pProcedureGranite->ChangeFunctionNoise(pNoise);
  pMatierePlane->SetTextureDiffuse(TexturePlane);
  pMatierePlane->SetProcedural(TYPE_DIFFUSE,pProcedureGranite);
  pMatierePlane->SetName("RedCloud");
  m_pMatiere->AddMatiere(pMatierePlane);

  CPlane	*pPlane=new CPlane(CVector(0,1,0),CCoord(0,0,0));
  pPlane->SetMatiere(pMatierePlane);*/

  m_pGeometry=new CFrontalGeometry;
  m_pGeometry->AddGeo(pFractal);
  //m_pGeometry->AddGeo(pPlane);

  m_pCamera=new CFrontalCamera;
  m_pCamera->SetCenter(CCoord(0,10,0));
  m_pCamera->SetLookAt(CCoord(0,0,0));
  m_pCamera->SetWidth(6.65);
  m_pCamera->SetHeight(5);

  m_pImage=new CBaseImage;
  m_pImage->SetSize(800,600);
}

void CRenderStructure::BuildFrontals()
{ 
	 m_pImage=new CBaseImage;
	 m_pLight=new CFrontalLight;
	 m_pMatiere=new CFrontalMaterial;
	 m_pFractal=new CFrontalFractal;
	 m_pGeometry=new CFrontalGeometry;
	 m_pCamera=new CFrontalCamera;
}


ostream&	operator<<(ostream& o,const CRenderStructure& c)
{
	o << *(c.GetImage());
	o << "algorithm { "; 

	std::string str;
	switch(c.GetTypeAlgo())
	{
		case ALGO_NORMAL:
		default:
			o << "default";
			break;
		case ALGO_ANTIALIAS:
			o << "\tantialias\n" << "\tthreshold " << c.GetStructAlgo().m_Threshold;
			o << "\n\tdepth " << c.GetStructAlgo().m_Depth;
			break;
	}
	o << "\n }\n";

	o << *(c.GetFrontalMaterial()) ;
	o << *(c.GetFrontalCamera()); 
	o << *(c.GetFrontalLight()); 
	o << *(c.GetFrontalGeometry());

	return o;
}


#endif