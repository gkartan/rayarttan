/////Etat classe : VALIDE

#ifndef	_CVECTOR
#define _CVECTOR

#include "Coord.h"
#include <cmath>

class CVector : public CCoord
{
// Construction
public:
	inline CVector();
	inline CVector(const CVector&);
	inline CVector(const CCoord&);
	inline CVector(const CCoord&,const CCoord&);
	inline CVector(double X,double Y,double Z);///Constructor for V^3
	inline CVector(double coord[3]);
	inline CVector(float coord[3]);

//Attributes
private:

//operations
public:
	inline const double& operator[](int index) const {return m_Value[index];}  
	inline CVector& operator *= (double);	
	inline CVector operator - (const CVector&) const;
	inline CVector operator - () const;			// V2=-V1
	inline CVector operator * (double) const;	// V2=V1.k
	inline CVector operator / (double) const;	// V2=V1.k
	inline double  operator * (const CCoord &) const; // k =V1.V2 //produit scalaire
	inline double  operator * (const CVector &) const; // k =V1.V2 //produit scalaire


	inline bool	IsNull() const;
public:
	inline CVector Cross(const CVector & v) const;
	inline double	Length() const;
	inline double	LengthSqr() const;
	inline void	Normalize();
	inline CVector Reflect(const CVector & vNormal) const;
	inline CVector Refract(const CVector & vNormal,double,double) const;
	inline CVector Refract(const CVector & vNormal,double,double,char) const;

// Implementation
public:
	inline virtual ~CVector();
};

CVector::CVector()
{
}

CVector::CVector(const CVector &Vect)
:CCoord(Vect)
{
}

CVector::CVector(const CCoord &coord)
:CCoord(coord)
{
}

CVector::CVector(const CCoord &pt1,const CCoord &pt2)
{
	m_Value[0]=pt2.m_Value[0]-pt1.m_Value[0];
	m_Value[1]=pt2.m_Value[1]-pt1.m_Value[1];
	m_Value[2]=pt2.m_Value[2]-pt1.m_Value[2];
}
	
CVector::CVector(double X,double Y,double Z)
:CCoord(X,Y,Z)
{
}

CVector::CVector(double coord[3])
:CCoord(coord)
{
}

CVector::CVector(float coord[3])
:CCoord(coord)
{
}


CVector::~CVector()
{
}

CVector& CVector::operator *= (double Param)
{
	m_Value[0]*=m_Value[0];
	m_Value[1]*=m_Value[1];
	m_Value[2]*=m_Value[2];

	return(*this);
}

CVector CVector::operator - () const
{
	CVector res;

	res.m_Value[0]=-m_Value[0];
	res.m_Value[1]=-m_Value[1];
	res.m_Value[2]=-m_Value[2];

	return(res);
}

CVector	CVector::operator-(const CVector & Param1Input) const
{
	CVector res;

	res.m_Value[0]=m_Value[0]-Param1Input.m_Value[0];
	res.m_Value[1]=m_Value[1]-Param1Input.m_Value[1];
	res.m_Value[2]=m_Value[2]-Param1Input.m_Value[2];

	return(res);
}

CVector CVector::operator * (double Cste)  const
{
	CVector res;

	res.m_Value[0]=m_Value[0]*Cste;
	res.m_Value[1]=m_Value[1]*Cste;
	res.m_Value[2]=m_Value[2]*Cste;

	return(res);

}

CVector CVector::operator / (double Cste)  const
{
	CVector res;

	res.m_Value[0]=m_Value[0]/Cste;
	res.m_Value[1]=m_Value[1]/Cste;
	res.m_Value[2]=m_Value[2]/Cste;

	return(res);

}

///////////////////////////////////////////////
double CVector::operator * (const CVector & Origin) const
{
  double res=m_Value[0]*Origin.m_Value[0]+
			 m_Value[1]*Origin.m_Value[1]+
			 m_Value[2]*Origin.m_Value[2];

  return (res);
}

double CVector::operator * (const CCoord & Origin) const
{
  double res=m_Value[0]*Origin.m_Value[0]+
			 m_Value[1]*Origin.m_Value[1]+
			 m_Value[2]*Origin.m_Value[2];

  return (res);
}

bool	CVector::IsNull() const
{
	return(m_Value[0]==0 && m_Value[1]==0 && m_Value[2]==0);
}


CVector CVector::Cross(const CVector & v) const
{
	//Le vecteur résultant est le déterminant de chaque matrice
	////////////////
	CVector res;

	res.m_Value[0]=m_Value[1]*v.m_Value[2]-m_Value[2]*v.m_Value[1];
	res.m_Value[1]=m_Value[2]*v.m_Value[0]-m_Value[0]*v.m_Value[2];
	res.m_Value[2]=m_Value[0]*v.m_Value[1]-m_Value[1]*v.m_Value[0];

	return res;
}


double CVector::Length() const
{
	return sqrt(m_Value[0]*m_Value[0]+m_Value[1]*m_Value[1]+m_Value[2]*m_Value[2]);
}

double CVector::LengthSqr() const
{
	return (m_Value[0]*m_Value[0]+m_Value[1]*m_Value[1]+m_Value[2]*m_Value[2]);
}

void CVector::Normalize()
{
	double longueur=Length();

	if ((longueur!=1.0) && (longueur!=0.0))
	{
		m_Value[0]/=longueur;
		m_Value[1]/=longueur;
		m_Value[2]/=longueur;
	}
}

CVector CVector::Reflect(const CVector & vNormal) const
{
  CVector res=(*this)-(vNormal*(2*(vNormal*(*this))));

  return res;
}

/////////////////////////////////////////
//Calcul du vecteur réfracté par rapport à une normale
//Application dee la Loi de Descartes : n1*sin(theta) = n2*sin(thetaprime)
CVector CVector::Refract(const CVector & vNormal,double n1,double n2) const
{
  double coeff=n1/n2; //=sin(thetaprime)/sin(theta)

  // Vecteur normal corrige pour aller dans la direction de l'origine
  CVector vNormalCorrected;
  if ( ((*this)*vNormal) >= 0)
    vNormalCorrected=-vNormal;
  else
    vNormalCorrected=vNormal;

  // Vecteur inverse du vecteur incident
  CVector InverseIncident=-(*this);

  //Cosinus angle incident = cos(theta)
  double costheta=vNormalCorrected*InverseIncident;

  // Carre du cosinus de l'angle d'emission
  double costhetaprime2=1-(coeff*coeff*(1-costheta*costheta));

  if (costhetaprime2>=0)
    return((vNormalCorrected  *  
		  ( (coeff*costheta) - sqrt(costhetaprime2) )  )-(InverseIncident*coeff));
  else
    return(CVector(0,0,0));
}

#endif
