/////Etat classe : VALIDE
#ifndef _BASECAMERA
#define _BASECAMERA

#include "Coord.h"
#include "Vector.h"
#include <string>
#include <ostream.h>

class CBaseCamera
{
// Construction
public:
	CBaseCamera();

// Attributes
protected:
	CCoord		m_Center;  // Centre de l'ecran de la camera
	CCoord		m_LookAt;  // Point vers lequel regarde la camera
	double		m_Focal;    // Distance focale de la camera
	CVector		m_Direct;  // Direction de vue de la camera
	CVector		m_Top;    // Vecteur definissant l'orientation de la "tete" de la camera
	double		m_WidthScreen;	//Largeur ecran
	double		m_HeightScreen;	//Hauteur ecran

// Operations publiques
public:
	inline	const	CCoord&	GetCenter() const {return m_Center;}
	inline  double	GetFocal()  const {return m_Focal;}
	inline	const	CVector& GetDirect()const {return m_Direct;}
	inline	const	CVector& GetTop()	const {return m_Top;}
	inline  double  GetWidth()  const {return m_WidthScreen;}
	inline	double	GetHeight() const {return m_HeightScreen;}
	inline	const	CCoord&	GetLookAt() const {return m_LookAt;}

	inline	void	SetCenter(CCoord &Center) {m_Center=Center;}
	inline  void	SetFocal(double Focal)	  {m_Focal=Focal;}
	inline	void	SetDirect(CVector &Dir)	  {m_Direct=Dir;}
	inline	void	SetDirect (CCoord & c)    {CCoord Point=c-m_Center; m_Direct=Point; m_Direct.Normalize();m_LookAt=c;}
	inline  void	SetWidth(double W)		  {m_WidthScreen=W;}
	inline	void	SetHeight(double H)		  {m_HeightScreen=H;}
	inline	void	SetLookAt(CCoord &c)	  {SetDirect(c);}
	inline  void	SetUp(CVector &Top)		  {m_Top=Top;};	

	virtual void	SetTop(CVector &Top)=0;	
	virtual void	Init(long,long)=0;
	virtual void	GetRay(float,float,CCoord&,CVector&)=0;
	virtual std::string GetType()=0;

	virtual	void GetOuputStream(ostream&)=0;

	//******Permet de renvoyer des références pour modifier directement les valeurs
	//******Utile pour l'ihm-> à banir pour les autres utilisations
	inline  double&	GetRefFocal()			{return m_Focal;}
	inline	double& GetRefWidthScreen()		{return m_WidthScreen;}
	inline	double& GetRefHeightScreen()	{return m_HeightScreen;}

// Implementation
public:
	virtual ~CBaseCamera();

	// Generated message map functions
protected:
};

#endif

