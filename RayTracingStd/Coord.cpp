#include "stdio.h"
#include "Coord.h"
#include <math.h>

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