#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include <list>
#include "Coord.h"
#include "Vector.h"
#include "RayEye.h"
#include "RayLight.h"
#include "BaseCamera.h"
#include "RenderStdRaytracing.h"
#include "TraceService.h"
#include "PhotonTracer.h"
#include "BaseImage.h"
#include "RenderInterface.h"

extern void	  RenderViewSetColor(unsigned long CurY,
								std::list<BaseColorChar>& ColorOptimise);

CRenderStdRaytracing::CRenderStdRaytracing()
{
	m_NbRecursivity=10;
}

CRenderStdRaytracing::CRenderStdRaytracing(CBaseCamera *pCamera,
										   CBaseImage  *pImage,
										   TypeVectorGeometry &ListGeometry,
										   TypeVectorLight	  &ListLight,
										   CPhotonTracer*	pPhotonTracer)
: CBaseRender(pCamera,pImage,ListGeometry,ListLight,pPhotonTracer)
{
	m_NbRecursivity=10;
}

CRenderStdRaytracing::~CRenderStdRaytracing()
{
	///Effacement si besoin

}

/////////////////////////////////////////////////////////////
///Moteur de rendu --> boucle sur les points de l'image
/////////////////////////////////////////////////////////////
void CRenderStdRaytracing::Render(long BeginLine,long EndLine)
{
  m_pCamera->Init(m_pImage->GetWidth(),m_pImage->GetHeight());

  // Pour chaque pixel de l'image a calculer
  int NumPixel=0;

  for (int CurY=BeginLine;CurY<=EndLine;CurY++)
  {
	std::list<BaseColorChar>	CurLine;

    for (int CurX=0;CurX<m_pImage->GetWidth();CurX++)
    {
		if((*m_pTerminated)) return;	//fin du thread

		RenderPixel(CurX,CurY,CurLine);
    }

	DoEndLine(CurY,CurLine);
  }
  ///////////Statistiques
  //_TRACE_INFO(_STR("Nombre Eye Rayons : %d",CRayEye::GetNbRay()));
  //_TRACE_INFO(_STR("Nombre Light Rayons : %d",CRayLight::GetNbRay()));
}

void	CRenderStdRaytracing::BeforeRenderPixel(float CurX,float CurY,
												CCoord& PtIntersect,
												CVector& RayVect)
{
	// On calcule la position dans l'espace de ce point
	m_pCamera->GetRay(CurX,CurY,PtIntersect,RayVect);
}

void	CRenderStdRaytracing::RunRenderPixel(CCoord& PtIntersect,
											 CVector& RayVect,
											 CColor& color)
{
	// On prepare le rayon qui part du foyer et qui passe par ce point
	CRayEye Ray;
	Ray.SetOrigin(PtIntersect);

	RayVect.Normalize();
	Ray.SetDirect(RayVect);
	Ray.SetMilieu(1);/* Cette supposition n'est pas toujours vraie */

	// Et on enregistre la couleur du rayon dans l'image
	// On Lance le rayon et on calcule la couleur résultante
	color=RayTrace(&Ray,m_ListeObjects,m_ListeLights);
}

void	CRenderStdRaytracing::AfterRenderPixel(CColor &ColorRes,
											   std::list<BaseColorChar> &CurLine)
{
	ColorRes.SetLimits(0,1);
	CBaseColor<unsigned char> ColorOptimise;

	ColorOptimise.SetColor(ColorRes.GetRed()*255,
						   ColorRes.GetGreen()*255,
						   ColorRes.GetBlue()*255);

	CurLine.push_back(ColorOptimise);
}

/////////////////////////////////////////////////////////////
///Moteur de rendu --> Rendu d'1 pixel
/////////////////////////////////////////////////////////////
void	CRenderStdRaytracing::RenderPixel(float CurX,float CurY,
										  std::list<BaseColorChar> &CurLine)
{
	CCoord PtIntersect;
	CVector	RayVect;


	BeforeRenderPixel(CurX,CurY,PtIntersect,RayVect);

	CColor ColorRes;
	RunRenderPixel(PtIntersect,RayVect,ColorRes);

	AfterRenderPixel(ColorRes,CurLine);
}





CColor	CRenderStdRaytracing::RayTrace(CRayEye *pRayEye,
									   TypeVectorGeometry &ListGeometry,
									   TypeVectorLight &ListLight)
{
	return(RayTrace(pRayEye,ListGeometry,ListLight,m_NbRecursivity));
}

CColor	CRenderStdRaytracing::RayTrace(CRayEye *pRayEye,
									   TypeVectorGeometry &ListGeometry,
									   TypeVectorLight &ListLight,
									   int NbRecursivity)
{
	CColor res(CColor(0,0,0));

	//Si Le rayon a touché ---> on calcule l'illumination
	if(pRayEye->RayTrace(ListGeometry))
	{
		TypeVectorLight::iterator	theIterator;
		
		for(theIterator=ListLight.begin();
			theIterator<ListLight.end();
			theIterator++)
			{
				res=res+(*theIterator)->Illumination(*pRayEye,ListGeometry);
			}

		//Evolution v1.1
		//Calcul avec la photon map
		res= res + m_pPhotonTracer->FindPhotonPower(pRayEye->GetImpactPosition(),
													pRayEye->GetNormal(),
													SEARCH_RADIUS, 
													NUM_SEARCH_PHOTONS);
        

	  ////////////////////////////////////////////////
	  ///Si il doit avoir une réflexion on la calcule
	  ////////////////////////////////////////////////
	  if (NbRecursivity>=1)
      {
        // On regarde s'il faut continuer a tracer le parcours du rayon

		const CBaseIntersection	&Intersection=pRayEye->GetImpactIntersection();

		////S'il y a une réflexion à traiter on y va
        if (Intersection.GetMatiere()->Kr()!=0)
        {
			CRayEye	RayReflect(pRayEye->GetImpactPosition(),
							   pRayEye->GetDirect().Reflect(Intersection.GetNormal()));

			RayReflect.SetMilieu(pRayEye->GetMilieu());
			// On cree un rayon reflechi
			res=res.Merge(RayTrace(&RayReflect,ListGeometry,ListLight,NbRecursivity-1),
						  Intersection.GetMatiere()->Kr());
        }

		////S'il y a une réfraction à traiter on y va
		if(Intersection.GetMatiere()->IsTransparent())
		{
		  CRayEye RayRefract(pRayEye->GetImpactPosition(),
							 pRayEye->GetDirect().Refract(Intersection.GetNormal(),
														  pRayEye->GetMilieu(),
														  Intersection.GetMilieu()));

		  if(!RayRefract.GetDirect().IsNull())
		  {
			  RayRefract.SetMilieu(Intersection.GetMilieu());

			  res=res.Merge(RayTrace(&RayRefract,ListGeometry,ListLight,NbRecursivity-1),
						  Intersection.GetMatiere()->GetTransparentCoeff());
		  }

		}

	  } 
	}

	return res;
}

void CRenderStdRaytracing::DoEndLine(long CurY,std::list<BaseColorChar> &CurLine)
{

	m_pImage->SetLine(CurY,CurLine);
	RenderViewSetColor(CurY,CurLine);   //Mise à jour Affichage
	CurLine.clear();

	CRenderInterface::m_NbLine=CurY;
}