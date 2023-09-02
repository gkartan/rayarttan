/////Etat classe : VALIDE

#ifndef	_CCOORD
#define _CCOORD

#include "BaseVector.h"
#include <cmath>
#include <ostream.h>

///Coordonnées dans un espace tridimensionnel

class CCoord : public CBaseVector<3,double>
{
// Construction
public:
	inline CCoord();
	inline CCoord(const CCoord&);
	inline CCoord(double X,double Y,double Z);///Constructor for V^3
	inline CCoord(double coord[3]);///Constructor for V^3
	inline CCoord(float coord[3]);///Constructor for V^3

//operations
public:
	inline const double& operator[](int index) const {return m_Value[index];}  
	inline CCoord& operator = (const CCoord&);
	inline CCoord operator - () const;			// V2=-V1
	inline CCoord operator * (double) const;	// V2=V1.k
	inline CCoord operator / (double) const;	// V2=V1.k
	inline CCoord operator + (const CCoord&) const;
	inline CCoord operator - (const CCoord&)const;

	inline friend ostream& operator<<(ostream&,const CCoord&);
	inline friend bool     operator != (const CCoord&,const CCoord&);
	inline static double   length(const CCoord&,const CCoord&);
	inline static double   length2(const CCoord&,const CCoord&);

public:
	inline  double	GetX() const {return m_Value[0];}
	inline  double	GetY() const {return m_Value[1];}
	inline  double	GetZ() const {return m_Value[2];}
	inline  void	SetX(double param) {m_Value[0]=param;}
	inline  void	SetY(double param) {m_Value[1]=param;}
	inline  void	SetZ(double param) {m_Value[2]=param;}
	inline	void	Set(double X,double Y,double Z) {m_Value[0]=X;m_Value[1]=Y;m_Value[2]=Z;}
	inline double  Sum() const;				//Sum of there coordinate (in V3 X+Y+Z)
	inline void	Print() const;
	inline double	Length() const;
	inline void	Normalize();
	inline double	Max();
	//inline	void	SetMin(const CCoord&);
	//inline	void	SetMax(const CCoord&);
// Implementation
public:
	inline virtual ~CCoord();
};

CCoord::CCoord()
{
}

CCoord::CCoord(const CCoord &coord)
{
	m_Value[0]=coord.m_Value[0];
	m_Value[1]=coord.m_Value[1];
	m_Value[2]=coord.m_Value[2];
}


CCoord::CCoord(double X,double Y,double Z)///Constructor for V^3
{
	m_Value[0]=X;
	m_Value[1]=Y;
	m_Value[2]=Z;
}

CCoord::CCoord(double coord[3])///Constructor for V^3
{
	m_Value[0]=coord[0];
	m_Value[1]=coord[1];
	m_Value[2]=coord[2];
}

CCoord::CCoord(float coord[3])///Constructor for V^3
{
	m_Value[0]=coord[0];
	m_Value[1]=coord[1];
	m_Value[2]=coord[2];
}


CCoord::~CCoord()
{
}

CCoord&	CCoord::operator=(const CCoord  & Origin)
{
	m_Value[0]=Origin.m_Value[0];
	m_Value[1]=Origin.m_Value[1];
	m_Value[2]=Origin.m_Value[2];

	return (*this);
}



CCoord	CCoord::operator+(const CCoord &Param1Input) const
{
	CCoord res;

	res.m_Value[0]=m_Value[0]+Param1Input.m_Value[0];
	res.m_Value[1]=m_Value[1]+Param1Input.m_Value[1];
	res.m_Value[2]=m_Value[2]+Param1Input.m_Value[2];

	return(res);
}


CCoord	CCoord::operator-(const CCoord & Param1Input) const
{
	CCoord res;

	res.m_Value[0]=m_Value[0]-Param1Input.m_Value[0];
	res.m_Value[1]=m_Value[1]-Param1Input.m_Value[1];
	res.m_Value[2]=m_Value[2]-Param1Input.m_Value[2];

	return(res);
}

CCoord CCoord::operator - () const
{
	CCoord res;

	res.m_Value[0]=-m_Value[0];
	res.m_Value[1]=-m_Value[1];
	res.m_Value[2]=-m_Value[2];

	return(res);
}

CCoord CCoord::operator * (double Cste) const
{
	CCoord res;

	res.m_Value[0]=m_Value[0]*Cste;
	res.m_Value[1]=m_Value[1]*Cste;
	res.m_Value[2]=m_Value[2]*Cste;

	return(res);
}

CCoord CCoord::operator / (double Cste) const
{
	CCoord res;

	res.m_Value[0]=m_Value[0]/Cste;
	res.m_Value[1]=m_Value[1]/Cste;
	res.m_Value[2]=m_Value[2]/Cste;

	return(res);
}

//Sum of there coordinate (in V3 X+Y+Z)	
double CCoord::Sum() const
{
	double Res=m_Value[0]+m_Value[1]+m_Value[2];

	return(Res);

}

void	CCoord::Print() const
{
/*	CString str;
	str.Format("Coord :: X : %.4f - Y : %.4f - Z : %.4f \n",m_Value[0],m_Value[1],m_Value[2]);
	OutputDebugString(str);*/
}

double CCoord::Length() const
{
	double Sum=m_Value[0]*m_Value[0]+m_Value[1]*m_Value[1]+m_Value[2]*m_Value[2];

	return sqrt(Sum);
}

void CCoord::Normalize()
{
	double longueur=Length();

	if ((longueur!=1.0) && (longueur!=0.0))
	{
		m_Value[0]/=longueur;
		m_Value[1]/=longueur;
		m_Value[2]/=longueur;
	}
}

ostream& operator<<(ostream &o,const CCoord &c)
{
	o << "<" << c.GetX() << "," << c.GetY() << "," << c.GetZ() << ">";

	return o;
}

bool   operator != (const CCoord &Param1,const CCoord &Param2)
{
		return((Param1.m_Value[0]!=Param2.m_Value[0]) ||
			   (Param1.m_Value[1]!=Param2.m_Value[1]) ||
			   (Param1.m_Value[2]!=Param2.m_Value[2]));
}

double   CCoord::length(const CCoord &Param1,const CCoord &Param2)
{
	double Value0=Param2.m_Value[0]-Param1.m_Value[0];
	double Value1=Param2.m_Value[1]-Param1.m_Value[1];
	double Value2=Param2.m_Value[2]-Param1.m_Value[2];

	return sqrt(Value0*Value0+Value1*Value1+Value2*Value2);
}

double   CCoord::length2(const CCoord &Param1,const CCoord &Param2)
{
	double Value0=Param2.m_Value[0]-Param1.m_Value[0];
	double Value1=Param2.m_Value[1]-Param1.m_Value[1];
	double Value2=Param2.m_Value[2]-Param1.m_Value[2];

	return (Value0*Value0+Value1*Value1+Value2*Value2);
}

double	CCoord::Max()
{
	double Max=m_Value[0];
	if(m_Value[1]>m_Value[0]) Max=m_Value[1];
	if(m_Value[2]>m_Value[1]) Max=m_Value[2];

	return Max;
}


#endif
