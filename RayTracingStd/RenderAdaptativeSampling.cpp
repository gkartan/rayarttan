#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#include <list>

#include "Coord.h"
#include "Vector.h"
#include "RayEye.h"
#include "RayLight.h"
#include "BaseCamera.h"
#include "RenderAdaptativeSampling.h"
#include "TraceService.h"
#include "BaseImage.h"
#include "RenderInterface.h"

CRenderAdaptativeSampling::CRenderAdaptativeSampling()
:CRenderStdRaytracing()
{
}

CRenderAdaptativeSampling::CRenderAdaptativeSampling(CBaseCamera *pCamera,
										   CBaseImage  *pImage,
										   TypeVectorGeometry &ListGeometry,
										   TypeVectorLight	  &ListLight,
										   CPhotonTracer	*pPhotonTracer)
: CRenderStdRaytracing(pCamera,pImage,ListGeometry,ListLight,pPhotonTracer)
{
	m_AntialiasThreshold=DEFAULT_ALGORITHM_THRESHOLD;
	m_AntialiasDepth=DEFAULT_ALGORITHM_DEPTH;

	for(int i=0;i<2;i++)
	{
		m_TabLine[i].reserve(pImage->GetWidth()+2);
	}
}

CRenderAdaptativeSampling::~CRenderAdaptativeSampling()
{
	///Effacement si besoin

}

/////////////////////////////////////////////////////////////
///Moteur de rendu --> Rendu d'1 pixel
/////////////////////////////////////////////////////////////
///1ère étape un peu particulière car on sauvegarde le résultat
void	CRenderAdaptativeSampling::RenderPixel(float CurX,float CurY,
										  std::list<BaseColorChar> &CurLine)
{
	CColor ColorRes;

	float InX0=CurX-0.5;
	float InY0=CurY-0.5;
	float InY2=CurY+0.5;
	float OutX0=CurX-1;
	float OutX1=OutX0+1;
	float OutX2=CurX;

	///Stockage première ligne
	if(CurY==CRenderInterface::m_NbLine) //0 si nouvelle image - nbligne si reprise
	{
		RenderPixel(InX0,InY0,OutX0,m_TabLine[0]);
		return;
	}

	RenderPixel(InX0,InY2,OutX2,m_TabLine[1]);
	if(CurX==0) return;	//Pas de calcul de pixel pour la première colonne

	///On test les valeurs et on sur échantillonne
	SuperSample(OutX0,InY0,OutX2,InY2,
				m_TabLine[0][OutX0],m_TabLine[1][OutX0],
				m_TabLine[0][OutX2],m_TabLine[1][OutX2],
				ColorRes,m_AntialiasDepth);

	AfterRenderPixel(ColorRes,CurLine);
}

void	CRenderAdaptativeSampling::RenderPixel(float InX,float InY,
											   CColor &ColorRes)
{
	CCoord PtIntersect;
	CVector	RayVect;

	BeforeRenderPixel(InX,InY,PtIntersect,RayVect);

	RunRenderPixel(PtIntersect,RayVect,ColorRes);
}

void	CRenderAdaptativeSampling::RenderPixel(float InX,float InY,
											   float OutX,
											   std::vector<CColor> &theLine)
{
	CColor ColorRes;
	RenderPixel(InX,InY,ColorRes);
	theLine.push_back(ColorRes);
}


void CRenderAdaptativeSampling::DoEndLine(long CurY,std::list<BaseColorChar> &CurLine)
{
	CRenderStdRaytracing::DoEndLine(CurY,CurLine);

	//Copie des lignes locales -- la ligne 1 devient la ligne 0
	m_TabLine[0].clear();

	///Copie des éléments
	for(std::vector<CColor>::iterator i=m_TabLine[1].begin();
		i!=m_TabLine[1].end();i++)
	{
		m_TabLine[0].push_back(*i);
	}

	m_TabLine[1].clear();
}


/////////////////////////////////////////////////////////////
///Moteur de rendu --> boucle sur les points de l'image
/////////////////////////////////////////////////////////////
void CRenderAdaptativeSampling::Render(long BeginLine,long EndLine)
{
  m_pCamera->Init(m_pImage->GetWidth(),m_pImage->GetHeight());

  // Pour chaque pixel de l'image a calculer
  int NumPixel=0;

  //_TRACE_INFO(_STR("Begin : %d - End : %d",BeginLine,EndLine+1));
  for (int CurY=BeginLine;CurY<=EndLine+2;CurY++)
  {
	std::list<BaseColorChar>	CurLine;

    for (int CurX=0;CurX<m_pImage->GetWidth()+1;CurX++)
    {
		if((*m_pTerminated)) return;	//fin du thread

		RenderPixel(CurX,CurY,CurLine);
    }

	if(CurY>BeginLine)
		DoEndLine(CurY-1,CurLine);
  }
  ///////////Statistiques
  //_TRACE_INFO(_STR("Sur Echantillonnage - Nombre Eye Rayons : %d",CRayEye::GetNbRay()));
  //_TRACE_INFO(_STR("Sur Echantillonnage - Nombre Light Rayons : %d",CRayLight::GetNbRay()));
}


void	CRenderAdaptativeSampling::SuperSample(
					double X0,double Y0,double X2,double Y2,
					CColor& C00,CColor& C02,CColor& C20,CColor& C22,
					CColor& ColorRes,
					long Depth)
{
	if((Depth>0) &&
	   (C00.Distance(C02) > m_AntialiasThreshold ||
	   C02.Distance(C22) > m_AntialiasThreshold ||
	   C20.Distance(C22) > m_AntialiasThreshold ||
	   C00.Distance(C20) > m_AntialiasThreshold ||
	   C00.Distance(C22) > m_AntialiasThreshold ||
	   C02.Distance(C20) > m_AntialiasThreshold))
	{


		//Calcul des points intermédiaires
		float	X1=(X0+X2)/2.0;
		float   Y1=(Y0+Y2)/2.0;
		//Les couleurs moyennes de chaque bloc
		CColor	cB1Mean,cB2Mean,cB3Mean,cB4Mean;

		///Calcul premier bloc
		CColor C10,C01,C11;
		RenderPixel(X1,Y0,C10);
		RenderPixel(X0,Y1,C01);
		RenderPixel(X1,Y1,C11);
		SuperSample(X0,Y0,X1,Y1,C00,C01,C10,C11,cB1Mean,Depth-1);

		///Calcul second bloc
		CColor C21;
		RenderPixel(X2,Y1,C21);
		SuperSample(X1,Y1,X2,Y2,C10,C11,C20,C21,cB2Mean,Depth-1);

		///Calcul troisième bloc
		CColor C12;
		RenderPixel(X1,Y2,C12);
		SuperSample(X0,Y1,X1,Y2,C01,C02,C11,C12,cB3Mean,Depth-1);

		///Calcul second bloc
		SuperSample(X1,Y1,X2,Y2,C11,C12,C21,C22,cB4Mean,Depth-1);


		//Calcul moyenne
		//Appel explicite à l'opérateur pour éviter
		//l'erreur avec BaseHyperAlgebra
		ColorRes=(cB1Mean+cB2Mean+cB3Mean+cB4Mean).operator/(4.0);
		return;
	}


	////Calcul moyenne
		//Appel explicite à l'opérateur pour éviter
		//l'erreur avec BaseHyperAlgebra
	ColorRes=(C00+C02+C20+C22).operator/(4.0);

}

void	CRenderAdaptativeSampling::SetAlgo(const CAlgorithmModifier &Algo)
{
	m_AntialiasThreshold=Algo.m_Threshold;
	m_AntialiasDepth=Algo.m_Depth;
}

