//***********************************************************************************
//Classe gérant un maillage de nombres aléatoires -- Implémentation élémentaire
//	     interpole ce maillage pour produire des nombres aléatoires intermédiaires
//		 permet le calcul de bruits pour les textures
//		 le bruit généré est de type Spotted (à gros grain)
//		 cf SIGGRAPH 85 Ken perlin
/////Etat classe : EN COURS
///		Algo de Ken Perlin -> codé par Paul Bourke
///
/// CLASSE A REVOIR POUR ADOPTER LES STRUCTURES DE DONNEES DU RESTE DU MOTEUR
/// A REDEVELOPPER EN C++ -> fonctions inline,.....
#ifndef _CNOISE3D
#define _CNOISE3D


#include <string>
#include "Coord.h"

#define INIT_RAND 1234
#define NOISE_B 0x100
#define NOISE_BM 0xff
#define NOISE_N 0x1000
#define NOISE_NP 12   /* 2^N */
#define NOISE_NM 0xfff

#define s_curve(t) ( t * t * (3. - 2. * t) )
#define lerp(t, a, b) ( a + t * (b - a) )
#define setup(i,b0,b1,r0,r1)\
        t = vec[i] + NOISE_N;\
        b0 = ((int)t) & NOISE_BM;\
        b1 = (b0+1) & NOISE_BM;\
        r0 = t - (int)t;\
        r1 = r0 - 1.;
#define at2(rx,ry) ( rx * q[0] + ry * q[1] )
#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

class CNoise3D 
{

public:
///Constructors
  CNoise3D();
  ~CNoise3D();

  ///Operations
public:
  void  Init();
  void normalize3(double *);

  double getNoiseValue(double vector[3]);

  virtual double GetNoise(const CCoord&);

  virtual std::string	GetType()	{return std::string("spotted");}

  //Attributes
protected:
	int			m_p[NOISE_B + NOISE_B + 2];
	double		m_g3[NOISE_B + NOISE_B + 2][3];

};

#endif
