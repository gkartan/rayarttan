#include "PhotonTracer.h"
#include "Rand.h"
#include "RayEye.h"
#include "Sphere.h"

CPhotonTracer::CPhotonTracer()
{
	m_Max_Photons=10000;
	m_NbRecursivity=10;
}

/*void CPhotonTracer::EmitCausticPhotons(TypeVectorLight	  &ListLight,
									   TypeVectorGeometry &ListGeometry)
{
  ///A REVOIR
  ///Test avec la première lumière
  TypeVectorLight::iterator	theLight=ListLight.begin();
	
  float x, y, z; 
  int emitted = 0;
  srand(33534);
  
  while(emitted < m_Max_Photons)
  {
    do 
	{ 
      x = nrand();
      y = nrand();
      z = nrand();
    } while ( x * x + y * y + z * z > 1);
        
    CVector dir(x, y, z);
    CPhoton *p = new CPhoton;

    // strength of lightsource
    float lumen = LIGHT_POWER;
    lumen*=m_Max_Photons;
	p->Power=CColor(lumen,lumen,lumen);

	//Init du rayon
	CRayEye	*pPhotonRay=new CRayEye();
	pPhotonRay->SetOrigin((*theLight)->GetPosition());

	dir.Normalize();
	pPhotonRay->SetDirect(dir);
	pPhotonRay->SetMilieu(1);	//choix arbitraire

    PhotonTrace(pPhotonRay,ListGeometry,*p);


    // more than one photon can be stored for each trace
    //    photon.push_back(p);    
    //emitted = photon.size();
    // ALWAYS emit atleast max_photons, could be buggy?!
    // because more than max_photons are emitted;
    emitted++;
  }

  
  //  scale power of stored photons with 1/emittedphotons
  float scale = 1.0f/(float)(emitted);
  std::vector<CPhoton*>::iterator i;

  int j=0;
  for (i=m_Photon.begin();i!=m_Photon.end();i++) 
  {
    j++;
    (*i)->Power=(*i)->Power*scale;
  }
  
  // build KDTree
  m_Kdtree = new CKDTree(m_Photon);
}*/

/*void CPhotonTracer::EmitCausticPhotons(TypeVectorLight	  &ListLight,
									   TypeVectorGeometry &ListGeometry)
{
	TypeVectorLight::iterator	theIterator;
	
	//A REVOIR
	//Pour chaque lumière de type omni pour l'instant----
	for(theIterator=ListLight.begin();
		theIterator<ListLight.end();
		theIterator++)
	{

		if((*theIterator)->GetType().compare(std::string("pointlight"))==0)
		{


      		TypeVectorGeometry::iterator	theIteratorObj;
	
			for(theIteratorObj=ListGeometry.begin();
				theIteratorObj<ListGeometry.end();
				theIteratorObj++)
			{

				//Test si objet transparent
				if((*theIteratorObj)->GetMatiere()->IsTransparent())
				{
					EmitCausticPhotons(*(*theIterator),*(*theIteratorObj),ListGeometry);
				}
			}
		}
	}

	///Creation de la photon_map (kd_tree)
	m_Kdtree = new CKDTree(m_Photon);
}*/

void CPhotonTracer::EmitCausticPhotons(CBaseLight		  &theLight,
									   CBaseGeometry	  &theObject,
									   TypeVectorGeometry &ListGeometry)
{
	////////////////////
	//***Preparation calcul des angles pour la spirale
	CSphere	*pBoundSphere=(CSphere*) theObject.GetBoundSphere();

	//Calcul de theta
	//CVector	ToCenter(pBoundSphere->GetCenter()-theLight.GetPosition());
	//double DistToCenter=ToCenter.Length();
	//ToCenter.Normalize();

	//double theta=atan(pBoundSphere->GetRay()/DistToCenter);

	int emitted = 0;
	srand(33534);

	float x,y,z;

	while(emitted < m_Max_Photons)
	{
		do 
		{ 
			x = nrand();
			y = nrand();
			z = nrand();
		} while ( x * x + y * y + z * z > 1);


		CCoord	NewTarget(pBoundSphere->GetCenter().GetX()+pBoundSphere->GetRay()*x,
						  pBoundSphere->GetCenter().GetY()+pBoundSphere->GetRay()*y,
						  pBoundSphere->GetCenter().GetZ()+pBoundSphere->GetRay()*z);

		CPhoton *p = new CPhoton;

		// strength of lightsource
		//float lumen = LIGHT_POWER;
		//lumen*=m_Max_Photons;
		//p->Power=CColor(lumen,lumen,lumen);
		p->Power=CColor(0.001,0.001,0.001);

		//Init du rayon
		CRayEye	*pPhotonRay=new CRayEye();
		pPhotonRay->SetOrigin(theLight.GetPosition());

		CVector	vDir(NewTarget-theLight.GetPosition());
		vDir.Normalize();
		pPhotonRay->SetDirect(vDir);
		pPhotonRay->SetMilieu(1);	//choix arbitraire

		PhotonTrace(pPhotonRay,ListGeometry,*p);


		emitted++;
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
void CPhotonTracer::PhotonTrace(CRayEye	*pRay,
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
		  	const CBaseIntersection	&Intersection=pRay->GetImpactIntersection();

			if(Intersection.GetMatiere()->IsTransparent())
			{
				//Surface transparent on relance un photon
				CRayEye RayRefract(pRay->GetImpactPosition(),
								   pRay->GetDirect().Refract(Intersection.GetNormal(),
															 pRay->GetMilieu(),
															 Intersection.GetMilieu()));

				if(!RayRefract.GetDirect().IsNull())
				{
					RayRefract.SetMilieu(Intersection.GetMilieu());

					PhotonTrace(&RayRefract,ListGeometry,PhotonImpact,NbRecursivity-1);
				}

			} else {
				//stockage photon si surface diffuse
				CPhoton	*pPhoton=new CPhoton(PhotonImpact);
				m_Photon.push_back(pPhoton);
			}


		}
	}
}


/*CColor CPhotonTracer::FindPhotonPower(const CCoord& vPosition,
									  const CVector& vNormal,
									  float Radius,
									  int	NumberPhotons)
{

  m_SearchCenter=vPosition;
  m_Radius=Radius;
  m_Pq_Num_Photons=NumberPhotons;

  CPhotonCompare photcmp(m_SearchCenter);

  // find a good way to do this?
  m_P_Queue = std::priority_queue <CPhoton*, std::vector<CPhoton*>, CPhotonCompare>(photcmp); 
  LocatePhotons(0);


  CColor color(0,0,0);

  m_Radius = Radius /10.0f;
  int i=0;

  while (!m_P_Queue.empty()) 
  {
    CPhoton *pPhoton = m_P_Queue.top();
    m_P_Queue.pop();
    i++;
    // set radius to outer most photon
	float rd = CCoord::length(vPosition,pPhoton->Position);
    if (m_Radius < rd) m_Radius = rd;

    color = color + GaussFilter(pPhoton,vPosition,vNormal,m_Radius);
  }


  // gauss filter
  color = color / (m_Radius*m_Radius*M_PI);

  return color;
}*/

void CPhotonTracer::LocatePhotons(int p)
{
	float dist;

	CPhoton	*pPhoton=m_Kdtree->m_Tree[p];
	
	if (pPhoton!=NULL) 
	{
		if ((2 * p + 2)<m_Kdtree->m_Tree.size())
		{ // examine child nodes
			// signed distance to splitting plane?
			
			int splitplane = pPhoton->Flag;
			dist = m_SearchCenter[splitplane] - pPhoton->Position[splitplane];
			
			if (dist < 0)
			{ // we are left of plane - search left subtree first
				LocatePhotons(2 * p + 1);
				if (dist * dist < m_Radius * m_Radius)
					LocatePhotons(2 * p + 2); // search right subtree
			} else {
				LocatePhotons(2 * p + 2); // check right subtree
				if (dist * dist < m_Radius * m_Radius)
					LocatePhotons(2 * p + 1); // check left subtree
				
			}
		}
		CVector t = pPhoton->Position - m_SearchCenter;
		dist = t[0]*t[0]+ t[1]*t[1]+ t[2]*t[2];
		
		if (dist < m_Radius * m_Radius)
		{ // check if the photon is close enough
			m_P_Queue.push(pPhoton);
			
			// adjust squared distance 
			if (m_P_Queue.size() > m_Pq_Num_Photons)
			{
				m_P_Queue.pop();
				const CPhoton *t_photon = m_P_Queue.top();
				m_Radius = CCoord::length(m_SearchCenter,t_photon->Position);
			}    
		} 
	}
}

CColor CPhotonTracer::GaussFilter(CPhoton *pPhoton,
								  const CCoord &vPosition,
								  const CVector &vNormal,
								  float Radius)
{
  float alpha,beta,wpg;

  float dist = CCoord::length(vPosition,pPhoton->Position);

  CColor color;

  alpha = 0.918f;
  beta = 1.953f;
  wpg = alpha *(1.0f - (1.0f - exp(-beta*(dist*dist)/(2*Radius*Radius)))/(1.0f-exp(-beta)));
  
  color.m_R = pPhoton->Power.m_R*wpg;
  color.m_G = pPhoton->Power.m_G*wpg;
  color.m_B = pPhoton->Power.m_B*wpg;

  return color;
}
