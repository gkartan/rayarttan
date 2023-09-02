#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "stdio.h"
#include "RayLight.h"
#include "LightPoint.h"
#include "BaseMatiere.h"
#include "BaseListIntersection.h"
#include "BaseModelLight.h"

CLightPoint::CLightPoint()
{
	m_Position=CCoord(0,0,0);
}

CLightPoint::CLightPoint(CColor &color,CCoord &coord,const std::string &str)
:CBaseLight(color,str)
{
	m_Position=coord;
}

CLightPoint::CLightPoint(const CLightPoint &Param)
{
	m_sName=Param.m_sName;
	m_color=Param.m_color;
	m_pModelLight=m_pModelLight;
	m_pModelLight->AddRef();
}

CLightPoint::~CLightPoint()
{
}


CColor CLightPoint::Illumination(	CRayEye &ParamRay,
									TypeVectorGeometry &ParamListGeo) 
{
  // Calcul du vecteur allant du point d'intersection vers la lumiere
  CVector vIntersectToLight=m_Position-ParamRay.GetImpactPosition();

  double dist=vIntersectToLight.Length();

  // Creation du rayon partant du point d'intersection vers la lumiere
  CRayLight	RayIntersectToLight(ParamRay.GetImpactPosition(),vIntersectToLight);

  // On calcule les intersections rencontrees par ce rayon, et la couleur
  // qu'a la lumiere a l'issue de la traversee des intersections entre
  // le point a illuminer et la lumiere

  //Au début la couleur est celle de la lumière brute
  CColor	res=m_color;

  //////////TEST
  //on lance le rayon
  //Calcul des ombres et effets de transparence
  if(RayIntersectToLight.RayTrace(ParamListGeo))
  {
	  //Enleve les intersections qui ne nous préoccupe pas
	  //Filtrage en fonction de la distance du rayon
	  if(RayIntersectToLight.FilterDist(dist))
	  {
		///On calcule la lumière arrivant au point d'impact
		res = res * RayIntersectToLight.GetColorResult();
	  }
  }

  // Maintenant qu'on a la quantite de lumiere qui atteint le point, on va
  // calculer la partie qui en est reflechie vers le rayon
  if (!res.IsBlack())
  {
	vIntersectToLight.Normalize();

	if(ParamRay.GetImpactIntersection().GetMatiere()->GetIsModelLight())
	{
		//On utilise le modèle d'éclairement particulier de l'objet
		res = res * ParamRay.GetImpactIntersection().GetMatiere()->GetModelLight()->ComputeColor(ParamRay.GetImpactIntersection(),
																								 vIntersectToLight,
																								 ParamRay.GetDirect(),
																								 *this);
	} else {
		///Si on utilise le modèle d'éclairement global de la scène
		res = res * m_pModelLight->ComputeColor(ParamRay.GetImpactIntersection(),
												vIntersectToLight,
												ParamRay.GetDirect(),
												*this);
	}

  }


  return res;
}

std::string CLightPoint::GetType()
{
	return("pointlight");
}

void CLightPoint::ForceEqual(CBaseLight &Param)
{
	CLightPoint *pTrueOrigin=static_cast<CLightPoint*>(&Param);
	if(pTrueOrigin!=NULL)
	{
		if(pTrueOrigin->GetType()==GetType())
			m_Position=pTrueOrigin->m_Position;
	}
}



void CLightPoint::GetOuputStream(ostream &o)
{
	o <<	"\nlight_source\n{\n";
	o <<	"\tpointlight\n";
	o <<	"\t\""						<< GetName().c_str()		<<		"\"\n";
	o <<	"\t"						<< GetPosition()			<<		"\n";
	o <<	"\tcolor "					<< GetColor()				<<		"\n";
	o <<	"}\n";
}
