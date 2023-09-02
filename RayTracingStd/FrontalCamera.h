//***********************************************************************************
//* CLASSE FRONTALE DE GESTION DES CAMERAS
//* Mots clés : automate, frontal, camera

/////Etat classe : EN COURS
#pragma warning(disable : 4786)

#ifndef _FRONTALCAMERA
#define _FRONTALCAMERA
#undef min
#undef max
#include "CamParalPlane.h"
#include "CamSphere.h"
#include "CamPersPlane.h"
#include <map>
#include <string>
#include <ostream.h>

typedef enum
{
	CAM_PERSPECTIVE=0,
	CAM_ORTHOGRAPHIC,
	CAM_SPHERIC,
	CAM_SUPERELLIPSOID,
} ENUM_CAMERATYPE;

typedef std::map<std::string, ENUM_CAMERATYPE, std::less<std::string>, std::allocator<ENUM_CAMERATYPE> >	CAMERATYPE; 

class CFrontalCamera
{
// Construction
public:
	inline CFrontalCamera();

// Attributes
protected:
	CBaseCamera		*m_pCamera; //Pointeur sur la vrai camera
	CAMERATYPE		m_listType;

// Operations publiques
public:
	inline	const CCoord&	GetCenter() const {return m_pCamera->GetCenter();}
	inline	const CCoord&  GetLookAt()const {return m_pCamera->GetLookAt();}

	inline	void	SetCenter(CCoord &Center) {m_pCamera->SetCenter(Center);}
	inline	void	SetLookAt (CCoord & c)    {m_pCamera->SetDirect(c);}
	inline  void	SetWidth(double W)		  {m_pCamera->SetWidth(W);}
	inline	void	SetHeight(double H)		  {m_pCamera->SetHeight(H);}

	inline  std::string GetType() {return m_pCamera->GetType();};

	inline	void	ChangeType(const std::string &NewType);

	inline  CBaseCamera* GetCamera() const {return m_pCamera;};
	inline	void		 SetCamera(CBaseCamera*);

// Implementation
public:
	inline virtual ~CFrontalCamera();

	////Operators
public:
	inline friend	ostream&	operator<<(ostream& o,const CFrontalCamera& c);

};


CFrontalCamera::CFrontalCamera()
{
	//Remplissage des types
	m_listType["perspective"]=CAM_PERSPECTIVE;
	m_listType["orthographic"]=CAM_ORTHOGRAPHIC;
	m_listType["spheric"]=CAM_SPHERIC;
	m_listType["superellipsoid"]=CAM_SUPERELLIPSOID;

	//Camera par défaut
	m_pCamera=new CCamParalPlane;
}

CFrontalCamera::~CFrontalCamera()
{
	if(m_pCamera!=NULL)
	{
		delete m_pCamera;
	}
}

//*******************
//*Force le changement de camera
void	CFrontalCamera::SetCamera(CBaseCamera *pNewCamera)
{
	delete m_pCamera;
	m_pCamera=pNewCamera;
}

///**********************************************************
///*Gestion automate
void	CFrontalCamera::ChangeType(const std::string &NewType)
{
	//On retrouve la bonne classe à l'aide d'une variable globale
	//de mapping chaine vers classe
	CAMERATYPE::iterator theIterator=m_listType.find(NewType);
	ENUM_CAMERATYPE Type=(*theIterator).second;

	CBaseCamera *pNewCamera=NULL;

	switch(Type)
	{
		case CAM_PERSPECTIVE:
			pNewCamera=new CCamPersPlane;
		break;

		case CAM_ORTHOGRAPHIC:
			pNewCamera=new CCamParalPlane;
		break;

		case CAM_SPHERIC:
			pNewCamera=new CCamSphere;
		break;

		case CAM_SUPERELLIPSOID:
			pNewCamera=new CCamSuperEllipsoid;
		break;

		default:
			//no changes
			return;
	}

	*pNewCamera=*m_pCamera;	//On remet les valeurs dans la nouvelle camera

	delete m_pCamera;
	m_pCamera=pNewCamera;
}

ostream&	operator<<(ostream& o,const CFrontalCamera& c)
{
	c.GetCamera()->GetOuputStream(o);

	return o;
}


#endif

