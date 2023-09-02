//***********************************************************************************
// Génére un bruit aléatoire suivant un signal 1/f
//	cd SIGGRAPH 85 Ken Perlin
// Permet de réaliser un bruit type granite (faible grain)

/////Etat classe : EN COURS

#ifndef _CNOISE3DGRANITE
#define _CNOISE3DGRANITE

#include "Noise3D.h"


class CNoise3DGranite : public CNoise3D
{

public:
///Constructors
  CNoise3DGranite();
  ~CNoise3DGranite();

  virtual std::string	GetType()	{return std::string("granite");}

protected:
	double	m_alpha;
	double	m_beta;
	double	m_expn;
	double	m_Scale;
  ///Operations
public:
  virtual double GetNoise(const CCoord&);
};

#endif
