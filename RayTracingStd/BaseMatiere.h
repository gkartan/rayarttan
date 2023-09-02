/////Etat classe : VALIDE

#ifndef	_BASEMATIERE
#define _BASEMATIERE

#include <stdio.h>
#include "Color.h"
#include "Coord.h"
#include <string>
#include "TextureElement.h"
#include "CommonMatiere.h"
#include "Dispersion.h"
#include "Photon.h"

class CBaseModelLight;


/////A REVOIR compl�tement pour simplifier les m�thodes d'acc�s
class CBaseMatiere
{
// Construction // Destruction
public:
	CBaseMatiere();
	CBaseMatiere(CColor&);
	CBaseMatiere(CColor&,CBaseModelLight*);

	virtual ~CBaseMatiere();

// Attributes
protected:
	std::string	m_sName;			//Nom de la matiere
	float     m_Milieu1;      // Indice de milieu d'un cote de l'objet
	float	  m_Milieu2;      // Indice de milieu de l'autre cote de l'objet
	float	  m_Kr;			  //coeff r�flexion

	CTextureElement	m_Ambient;
	CTextureElement	m_Diffuse;
	CTextureElement	m_Transparent;
	CTextureElement	m_Specular;

	
	///Si la matiere utilise un mod�le d'�clairement particulier
	CBaseModelLight *m_pModelLight;

	CDispersion		m_Dispersion;	//mod�le de dispersion utilis� dans cette mati�re
	CPhotonParameters m_PhotonParameters;	//param�tres des photons s'il y a lieu

	long			m_NbRef;

// Operations
public:
	//*********************************************************
	///////////Param�tres g�n�raux
	inline std::string	GetName()	const {return m_sName;}
	inline void		SetName(const std::string &Name) {m_sName=Name;}
	void	AddRef();
	void	Release();
	virtual	void GetOuputStream(ostream&);

	//*********************************************************
	///////////Gestion R�flexion/R�fraction
	////A REVOIR --> gestion r�flexion
	virtual void SetReflexion   (float r)	{m_Kr=r;}
	float	Kr() const	{return m_Kr;}
	inline float	GetMilieu1()     const {return m_Milieu1;}
	inline float	GetMilieu2()     const {return m_Milieu2;}
	inline void		SetMilieu1(float m)		{m_Milieu1=m;}
	inline void		SetMilieu2(float m)		{m_Milieu2=m;}

	inline const CDispersion&	GetDispersion()	const						{return m_Dispersion;}
	inline		 CDispersion&	GetRefDispersion()							{return m_Dispersion;}
	inline void					SetDispersion(const CDispersion &Param)		{m_Dispersion=Param;}

	inline CPhotonParameters&	GetRefPhotonsParameters()					{return m_PhotonParameters;}
	inline CPhotonParameters	GetPhotonsParameters()	const				{return m_PhotonParameters;}
	//*********************************************************
	/////////////Gestion couleurs

	inline void		SetColorGeneral(CColor &Color); 

	inline void		SetColorAmbient(const CColor &Color)	{m_Ambient.SetColor(Color);}
	inline const	CColor	GetColorAmbient() const			{return m_Ambient.GetColor();}

	inline void		SetColorTransparent(const CColor &Color)	{m_Transparent.SetColor(Color);}
	inline const	CColor	GetColorTransparent() const			{return m_Transparent.GetColor();}

	inline void		SetTextureDiffuse(const CTextureElement &Text)			{m_Diffuse=Text;}
	inline void		SetColorDiffuse(const CColor &Color)			{m_Diffuse.SetColor(Color);}
	inline CColor	GetColorDiffuse(const CCoord &coord,const CCoord& objcenter)	const 	{return m_Diffuse.GetColor(coord,objcenter);}
	inline CColor	GetColorDiffuse()	const 						{return m_Diffuse.GetColor();}

	inline void		SetColorSpecular(const CColor &Color)			{m_Specular.SetColor(Color);}
	inline			CColor	GetColorSpecular(const CCoord &coord,const CCoord& objcenter)	const 	{return m_Specular.GetColor(coord,objcenter);}
	inline			CColor	GetColorSpecular()	const 				{return m_Specular.GetColor();}

	//*********************************************************
	/////////////Gestion Coefficients couleurs
	virtual void Ambient  (float a)			{m_Ambient.SetCoeff(a);}
	virtual void Diffuse     (float d)		{m_Diffuse.SetCoeff(d);}
	virtual void Specular	(float s)		{m_Specular.SetCoeff(s);}
	virtual void SetTransparency(float t)	{m_Transparent.SetCoeff(t);}
	inline float GetTransparentCoeff() const {return m_Transparent.GetCoeff();}

	//*********************************************************
	////////////Gestion mod�le lumi�re
	inline  bool GetIsModelLight() const {return (m_pModelLight!=NULL);}
	inline  CBaseModelLight* GetModelLight() const {return m_pModelLight;}
	inline	void SetModelLight(CBaseModelLight* pLight) {m_pModelLight=pLight;}

	//*********************************************************
	////////////Divers Tests
	inline bool	IsTransparent() const {return m_Transparent.IsNotNull();}

	//*********************************************************
	/////////////Gestion Texture
	bool	IsTexture(ENUM_TYPECOLOR Type);
	CTextureElement*	GetTexture(ENUM_TYPECOLOR Type);
	void				SetTexture(ENUM_TYPECOLOR Type,const CTextureElement &Text);

	CBaseProcedural*	GetProcedural(ENUM_TYPECOLOR Type);
	void				SetProcedural(ENUM_TYPECOLOR Type,CBaseProcedural*);
	void				SetTypeTexture(ENUM_TYPECOLOR Type,CNoise3D*);
	void				SetTypeTexture(ENUM_TYPECOLOR Type,CBaseProcedural*);


	//**********************************************************
	///////////Les op�rateurs
	CBaseMatiere&	operator =  (CBaseMatiere&);

};

#endif

