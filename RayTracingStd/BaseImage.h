/////Etat classe : VALIDE -- A OPTIMISE EN N'utilisant pas la mtl
#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#ifndef _BASEIMAGE
#define _BASEIMAGE

#include <list>
#include "BaseColor.h"
#include "wx/image.h"
#include  <string>

typedef CBaseColor<unsigned char> BaseColorChar;

typedef enum
{
	IMAGE_TYPE_TIFF=0
} ENUM_IMAGE_TYPE;

class CBaseImage
{
// Construction
public:
	CBaseImage();

// Attributes
protected:
	long	m_Width;			// Largeur de l'image
	long	m_Height;			// Hauteur de l'image
	long	m_NbLineRendered;	// Compte le nombre de ligne rendue --> sert à la reprise

public:
	ENUM_IMAGE_TYPE	m_Type;
	wxImage	m_Map;	   // Liste des couleurs

// Operations
public:
  // Methodes
  //void Correction(double);           // Correction Gamma
  void Normaliser();                 // Normalisation de l'image
  bool SaveFile(std::string &str);
  bool SaveFile(std::string &str,std::string &output);
  bool LoadFile(std::string &str);

  inline long		GetWidth()	const		{return m_Width;};
  inline long		GetHeight()	const		{return m_Height;};

  inline unsigned char GetRed(int x,int y)		{return m_Map.GetRed(x,y);}
  inline unsigned char GetGreen(int x,int y)	{return m_Map.GetGreen(x,y);}
  inline unsigned char GetBlue(int x,int y)		{return m_Map.GetBlue(x,y);}


  void	SetSize(long H,long W);
  inline void	SetColor(long X,long Y,CBaseColor<unsigned char> &color) 
	{m_Map.SetRGB(X,Y,color.GetRed(),color.GetGreen(),color.GetBlue());}

  void	SetLine(long,std::list<BaseColorChar>&);

  void  Clear();
  

  void	SetAdaptativeSampling();	//Retaille l'image pour accueillir un sur_échantillonage
  unsigned char*	GetArray();


// Implementation
public:
	virtual ~CBaseImage();

	//Operators
public:
	friend ostream&	operator<<(ostream& o,const CBaseImage& c);
};

#endif