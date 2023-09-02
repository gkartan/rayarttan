/////Etat classe : EN COURS
#ifndef _PHOTON_TRACER_H_
#define _PHOTON_TRACER_H_

#include <queue>

#include "Photon.h"
#include "KDTree.h"
#include "RayEye.h"
#include "BaseListGeometry.h"
#include "BaseLight.h"
#include "Constants.h"
#include "Rand.h"
#include "Sphere.h"
#include "MatrixTransform.h"
#include "Dispersion.h"


#define LIGHT_POWER         1.0f
#define SEARCH_RADIUS       1.0f
#define MIN_NUM_SEARCH_PHOTONS  20
#define NUM_SEARCH_PHOTONS  100
#define LIGHT_POWER 1.0f


class CPhotonTracer 
{
 public:
  inline CPhotonTracer();
  inline ~CPhotonTracer();

  inline void EmitCausticPhotons(TypeVectorLight      &ListLight,
                          TypeVectorGeometry &ListGeometry);
  inline void EmitCausticPhotons(CBaseLight       &theLight,
                          CBaseGeometry       &theObject,
                          TypeVectorGeometry &ListGeometry);

  inline void PhotonTraceRefract(CRayEye *pRay,
								TypeVectorGeometry &ListGeometry,
							    CPhoton &PhotonIncident,
								int NbRecursivity,
								const CBaseIntersection&Intersection,
								char  WaveLength,
								const CDispersion	&Disp);
  inline void PhotonTraceRefract(CRayEye *pRay,
								TypeVectorGeometry &ListGeometry,
							    const CPhoton &PhotonIncident,
								int NbRecursivity,
								const CBaseIntersection&Intersection);

  inline void PhotonTrace(CRayEye *pRay,TypeVectorGeometry &ListGeometry,const CPhoton &PhotonIncident);
  inline void PhotonTrace(CRayEye   *pRay,
                          TypeVectorGeometry &ListGeometry,
                          const CPhoton &PhotonIncident,
                          int NbRecursivity);
  inline CColor FindPhotonPower(const CCoord& vPosition,
                                const CVector& vNormal,
                                float Radius,
                                int NumberPhotons);
  inline void   LocatePhotons(int p);

  /////**********Les filtres******
  inline CColor GaussFilter(CPhoton *pPhoton,
                            const CVectorFloat &vPosition,
                            float Radius);
  inline CColor ConeFilter(CPhoton *pPhoton,
                            const CVectorFloat &vPosition,
                            float Radius);
  /////***************************


 private:
  int                       m_NbRecursivity;
  CKDTree					m_Kdtree;
  std::vector<CPhoton *>    m_Photon;

  //variables de travail
  std::priority_queue <CPhoton*,std::vector<CPhoton*>,CPhotonCompare> m_P_Queue;
  CVectorFloat              m_SearchCenter;
  float                     m_Radius;
  int                       m_Pq_Num_Photons;

  long						m_NbPhotonMono;	//Nombre de photons monochromatiques	

};

CPhotonTracer::CPhotonTracer()
{
    m_NbRecursivity=10;
	m_NbPhotonMono=0;
}

CPhotonTracer::~CPhotonTracer()
{
	std::vector<CPhoton*>::iterator k;
	for (k=m_Photon.begin();k!=m_Photon.end();k++) 
	{
		delete (*k);
	}
	m_Photon.clear();
}

void CPhotonTracer::EmitCausticPhotons(TypeVectorLight    &ListLight,
                                       TypeVectorGeometry &ListGeometry)
{
    TypeVectorLight::iterator   theIterator;
    
    //A REVOIR
    //Pour chaque lumière de type omni pour l'instant----
    for(theIterator=ListLight.begin();
        theIterator<ListLight.end();
        theIterator++)
    {

        if((*theIterator)->GetType().compare(std::string("pointlight"))==0)
        {


            TypeVectorGeometry::iterator    theIteratorObj;
    
            for(theIteratorObj=ListGeometry.begin();
                theIteratorObj<ListGeometry.end();
                theIteratorObj++)
            {

                if((*theIteratorObj)->GetMatiere()->GetPhotonsParameters().m_Actif)
                {
                    EmitCausticPhotons(*(*theIterator),*(*theIteratorObj),ListGeometry);
                }
            }
        }
    }

    ///Creation de la photon_map (kd_tree)
    m_Kdtree.Init(m_Photon);

	//desctruction de la liste
	std::vector<CPhoton*>::iterator k;
	for (k=m_Photon.begin();k!=m_Photon.end();k++) 
	{
		delete (*k);
	}
	m_Photon.clear();
}


CColor CPhotonTracer::FindPhotonPower(const CCoord& vParamPosition,
                                      const CVector& vNormal,
                                      float Radius,
                                      int   NumberPhotons)
{

  CVectorFloat  vPosition(vParamPosition);

  m_SearchCenter=vPosition;
  m_Radius=Radius/2.;
  m_Pq_Num_Photons=NumberPhotons;

  CPhotonCompare photcmp(m_SearchCenter);

  //Pour s'assurer qu'on aura un minimum de photon dans la liste
  int IterNum=0;
  while(m_P_Queue.size()<MIN_NUM_SEARCH_PHOTONS && IterNum<2)
  {
    m_Radius*=2;
    while (!m_P_Queue.empty()) 
    {   
        m_P_Queue.pop();
    }

    m_P_Queue = std::priority_queue <CPhoton*, std::vector<CPhoton*>, CPhotonCompare>(photcmp); 
    LocatePhotons(0);

    IterNum++;
  }


  CColor color(0,0,0);

  m_Radius = Radius /10.0f;
  int i=0;

  while (!m_P_Queue.empty()) 
  {
    CPhoton *pPhoton = m_P_Queue.top();
    m_P_Queue.pop();
    i++;
    // set radius to outer most photon
    float rd = CVectorFloat::length(vPosition,pPhoton->Position);
    if (m_Radius < rd) m_Radius = rd;

    color = color + GaussFilter(pPhoton,vPosition,m_Radius);
  }


  // gauss filter
  color = color.operator/(m_Radius*m_Radius*M_PI);

  return color;
}

void CPhotonTracer::EmitCausticPhotons(CBaseLight         &theLight,
                                       CBaseGeometry      &theObject,
                                       TypeVectorGeometry &ListGeometry)
{
	long Max_Photons=theObject.GetMatiere()->GetPhotonsParameters().m_Count;
    ////////////////////
    //***Preparation calcul des angles pour la spirale
    CSphere *pBoundSphere=(CSphere*) theObject.GetBoundSphere();

    //Calcul de theta
    CVector ToCenter(pBoundSphere->GetCenter()-theLight.GetPosition());
    double DistToCenter=ToCenter.Length();
    double Rayon2=pBoundSphere->GetRay()*pBoundSphere->GetRay();

    double theta=atan(pBoundSphere->GetRay()/DistToCenter);
    //double omega=(pBoundSphere->GetRay()/sqrt(m_Max_Photons))*DistToCenter;
    double omega=sqrt(Rayon2/Max_Photons)*2;
    double NbStep=pBoundSphere->GetRay()/omega;

    
    //Matrice de translation inverse de la lumière
    //pour ramener la boundsphere dans le repère de la lumière
    CMatrixTransform MLight;
    MLight.Translate(-theLight.GetPosition()); 

    float emitted=0;

    double delta_theta=(theta*INV_PI_180)/NbStep;


	double PartialCirconf=(2*M_PI*pBoundSphere->GetRay())/omega;
    for(int i=0;i<=NbStep;i++)
    {
        //Nombre de pas sur le cercle
        int NbCirconfStep=int(PartialCirconf*i/NbStep);

        //on trouve le premier point du cercle
        CMatrixTransform M1(MLight);
        M1.SimpleComposeAndRotate(CVector(0,0,delta_theta*i));

        CVector FirstVectTemp=M1.Trans(ToCenter);
        CVector FirstVect=MLight.InvTrans(FirstVectTemp);

        double delta_circonf=(NbCirconfStep==0)?0:360./NbCirconfStep;

        for(int j=0;j<=NbCirconfStep;j++)
        {
            //On calcule la rotation du premier point
            CMatrixTransform M2;
            M2.AxisRotate(ToCenter,delta_circonf*j);

            CVector vDir=M2.Trans(FirstVect);

            CPhoton photon;
			photon.Power=CColor(1,1,1);

            //Init du rayon
            CRayEye PhotonRay;
            PhotonRay.SetOrigin(theLight.GetPosition());

            vDir.Normalize();
            PhotonRay.SetDirect(vDir);
            PhotonRay.SetMilieu(1);   //choix arbitraire

            PhotonTrace(&PhotonRay,ListGeometry,photon);


            emitted++;
        }
    }

	// Intensité d'un photon
    // Calcul sans atténuation
    // Iphoton=Ilight*Rayon^2*DistanceAuCentre^2/NbPhoton
	//  scale power of stored photons with 1/emittedphotons
	//Nombre de photon = taille du vector - le nombre de division pour la dispersion*3
	CColor color=theLight.GetColor().operator*(Rayon2/(m_Photon.size()-m_NbPhotonMono+m_NbPhotonMono/3))*theObject.GetMatiere()->GetPhotonsParameters().m_Intensity;

	std::vector<CPhoton*>::iterator k;
	for (k=m_Photon.begin();k!=m_Photon.end();k++) 
	{
		(*k)->Power*=color;
	}
}

//*************************************************************
//*La photon_map ne va nous servir uniquement pour les caustiques
//*************************************************************
void CPhotonTracer::PhotonTrace(CRayEye *pRay,TypeVectorGeometry &ListGeometry,const CPhoton &PhotonIncident)
{
    PhotonTrace(pRay,ListGeometry,PhotonIncident,m_NbRecursivity);
}


//*************************************************************
//*Voir RenderStdRayTracing --> méthode très similaire
//*A voir si on les regroupe -> je ne pense pas car elles vont diverger
//*au fur et à mesure des implémentations 
//*************************************************************
void CPhotonTracer::PhotonTrace(CRayEye *pRay,
                                TypeVectorGeometry &ListGeometry,
                                const CPhoton &PhotonIncident,
                                int NbRecursivity)
{
  
    //*******************
    //Test Intersection
    //******************
    if(pRay->RayTrace(ListGeometry))
    {
   
      CPhoton PhotonImpact(pRay->GetImpactPosition(),
                           pRay->GetDirect(),
                           PhotonIncident.Power);


      if (NbRecursivity>=1)
      {
            const CBaseIntersection &Intersection=pRay->GetImpactIntersection();

			//Test est-ce que le photon est absorbé ou réfléchi
			if(Intersection.GetMatiere()->GetPhotonsParameters().GetProbReflect()>drand48())
			{
				//photon réfléchi
				CRayEye	RayReflect(pRay->GetImpactPosition(),
								   pRay->GetDirect().Reflect(Intersection.GetNormal()));

				RayReflect.SetMilieu(pRay->GetMilieu());
				// On cree un rayon reflechi
				PhotonTrace(&RayReflect,ListGeometry,PhotonImpact,NbRecursivity-1);

			} else

            if(Intersection.GetMatiere()->IsTransparent())
            {
				const CDispersion &Disp=Intersection.GetMatiere()->GetDispersion();
				if(Disp.IsActif() && !pRay->GetIsMonochrom())
				{
					for(int i=0;i<Disp.GetCountSamples();i++)
					{
						CPhoton PhotonImpact(PhotonImpact);
						PhotonTraceRefract(pRay,ListGeometry,PhotonImpact,NbRecursivity-1,Intersection,i,Disp);
					}
				} else {
					PhotonTraceRefract(pRay,ListGeometry,PhotonImpact,NbRecursivity-1,Intersection);
				}

            } else

            //on ne stocke pas la lumière directe
            if(NbRecursivity<m_NbRecursivity)
            {
				if(pRay->GetIsMonochrom())
					m_NbPhotonMono++;
                //stockage photon si surface diffuse
                CPhoton *pPhoton=new CPhoton(PhotonImpact);
                m_Photon.push_back(pPhoton);
            }

        }
    }
}

void CPhotonTracer::PhotonTraceRefract(CRayEye *pRay,
								TypeVectorGeometry &ListGeometry,
							    CPhoton &PhotonIncident,
								int NbRecursivity,
								const CBaseIntersection&Intersection,
								char  WaveLength,
								const CDispersion	&Disp)
{
	//Modification de la couleur du photon
	PhotonIncident.Power=Disp.GetColor(WaveLength);

	CRayEye RayRefract(pRay->GetImpactPosition(),
					   pRay->GetDirect().Refract(Intersection.GetNormal(),
													pRay->GetMilieu(),
													Disp.GetIor(WaveLength)),
					   WaveLength);
	if(!RayRefract.GetDirect().IsNull())
	{
		RayRefract.SetMilieu(Intersection.GetMilieu());

		PhotonTrace(&RayRefract,ListGeometry,PhotonIncident,NbRecursivity-1);
	}

}

void CPhotonTracer::PhotonTraceRefract(CRayEye *pRay,
								TypeVectorGeometry &ListGeometry,
							    const CPhoton &PhotonIncident,
								int NbRecursivity,
								const CBaseIntersection&Intersection)
{
	CRayEye RayRefract(pRay->GetImpactPosition(),
					   pRay->GetDirect().Refract(Intersection.GetNormal(),
												 pRay->GetMilieu(),
												 Intersection.GetMilieu()));

	if(!RayRefract.GetDirect().IsNull())
	{
		RayRefract.SetIsMonochrom(pRay->GetIsMonochrom());
		RayRefract.SetMilieu(Intersection.GetMilieu());

		PhotonTrace(&RayRefract,ListGeometry,PhotonIncident,NbRecursivity-1);
	}

}

void CPhotonTracer::LocatePhotons(int p)
{
    int p2=2*p;
    float dist; 

    CPhoton *pPhoton=m_Kdtree.m_Tree[p];
    
    if (pPhoton!=NULL) 
    {
        int splitplane = pPhoton->Flag;

        if ((p2 + 2)<m_Kdtree.m_Tree.size())
        { // examine child nodes
            // signed distance to splitting plane?
            
            dist = m_SearchCenter.m_Value[splitplane] - pPhoton->Position.m_Value[splitplane];
            
            if (dist < 0)
            { // we are left of plane - search left subtree first
                LocatePhotons(p2 + 1);
                if (dist * dist < m_Radius * m_Radius)
                    LocatePhotons(p2 + 2); // search right subtree
            } else {
                LocatePhotons(p2 + 2); // check right subtree
                if (dist * dist < m_Radius * m_Radius)
                    LocatePhotons(p2 + 1); // check left subtree
                
            }
        }

        dist = CVectorFloat::length2(m_SearchCenter,pPhoton->Position);
        
        if (dist < m_Radius * m_Radius)
        { // check if the photon is close enough
            m_P_Queue.push(pPhoton);
            
            // adjust squared distance 
            if (m_P_Queue.size() > m_Pq_Num_Photons)
            {
                m_P_Queue.pop();
                const CPhoton *t_photon = m_P_Queue.top();
                m_Radius = CVectorFloat::length(m_SearchCenter,t_photon->Position);
            }    
        } 
    }
}

CColor CPhotonTracer::GaussFilter(CPhoton *pPhoton,
                                  const CVectorFloat &vPosition,
                                  float Radius)
{

  float alpha,beta,wpg;

  float dist = CVectorFloat::length(vPosition,pPhoton->Position);



  alpha = 0.918f;
  beta = 1.953f;
  wpg = alpha *(1.0f - (1.0f - exp(-beta*(dist*dist)/(2*Radius*Radius)))/(1.0f-exp(-beta)));
  
  CColor color(pPhoton->Power*wpg);

  return color;
}

CColor CPhotonTracer::ConeFilter(CPhoton *pPhoton,
                                 const CVectorFloat &vPosition,
                                 float Radius)
{
  float k = 1.0f; //filter constant
  float dist = CVectorFloat::length(vPosition,pPhoton->Position);
  float wpc = 1.0f - (dist/(k*Radius));

  CColor color(pPhoton->Power*wpc);

  return color;
}

#endif // _PHOTON_TRACER_H_
