#ifndef _PHOTON_H_
#define _PHOTON_H_

#include "Vector.h"
#include "Color.h"
#include "Constants.h"

/*class CPhoton
{
public:
	inline	CPhoton()	{};
	inline	CPhoton(const CPhoton &Photon)
		: Position(Photon.Position),Direction(Photon.Direction),Power(Photon.Power),Flag(Photon.Flag) {};
	inline	CPhoton(const CVector&Pos,const CVector&Dir,const CColor&color)
				: Position(Pos),Direction(Dir),Power(color) {};
public:
  CVector Position;		//position
  CVector Direction;	//direction
  CColor  Power;		//couleur du photon
  int	  Flag;			//indicateurs
};*/

//structure optimisée
//pour ne pas appeler de constructeurs

class	CVectorFloat
{
public:
	float	m_Value[3];

public:
	inline CVectorFloat()	{m_Value[0]=0;m_Value[1]=0;m_Value[2]=0;}
	inline CVectorFloat(const CVectorFloat &Param)	{m_Value[0]=Param.m_Value[0];m_Value[1]=Param.m_Value[1];m_Value[2]=Param.m_Value[2];}
	inline CVectorFloat(const CCoord &coord)	{m_Value[0]=coord.m_Value[0]; m_Value[1]=coord.m_Value[1]; m_Value[2]=coord.m_Value[2];}

public:
	inline static float   length(const CVectorFloat &Param1,const CVectorFloat &Param2);
	inline static float   length2(const CVectorFloat &Param1,const CVectorFloat &Param2);

	//definition d'opérateurs spécifiques optimisés
	inline CVectorFloat& operator= (const CVectorFloat&);
	inline CVectorFloat operator+ (const CVectorFloat&) const;
	inline CVectorFloat operator/ (float) const;
};

CVectorFloat CVectorFloat::operator+ (const CVectorFloat &Param1) const
{
	CVectorFloat	Res;

	Res.m_Value[0]=m_Value[0]+Param1.m_Value[0];
	Res.m_Value[1]=m_Value[1]+Param1.m_Value[1];
	Res.m_Value[2]=m_Value[2]+Param1.m_Value[2];

	return Res;
}

CVectorFloat CVectorFloat::operator/ (float Param1) const
{
	CVectorFloat	Res;

	Res.m_Value[0]=m_Value[0]/Param1;
	Res.m_Value[1]=m_Value[1]/Param1;
	Res.m_Value[2]=m_Value[2]/Param1;

	return Res;
}

CVectorFloat& CVectorFloat::operator= (const CVectorFloat &Param1)
{
	m_Value[0]=Param1.m_Value[0];
	m_Value[1]=Param1.m_Value[1];
	m_Value[2]=Param1.m_Value[2];

	return(*this);
}

float   CVectorFloat::length(const CVectorFloat &Param1,const CVectorFloat &Param2)
{
	float Value0=Param2.m_Value[0]-Param1.m_Value[0];
	float Value1=Param2.m_Value[1]-Param1.m_Value[1];
	float Value2=Param2.m_Value[2]-Param1.m_Value[2];

	return sqrt(Value0*Value0+Value1*Value1+Value2*Value2);
}

float   CVectorFloat::length2(const CVectorFloat &Param1,const CVectorFloat &Param2)
{
	float Value0=Param2.m_Value[0]-Param1.m_Value[0];
	float Value1=Param2.m_Value[1]-Param1.m_Value[1];
	float Value2=Param2.m_Value[2]-Param1.m_Value[2];

	return (Value0*Value0+Value1*Value1+Value2*Value2);
}


class	CVectorOptim
{
public:
	inline CVectorOptim() {}
	inline CVectorOptim(const CVectorFloat&);
	inline CVectorOptim(const CVector&);
	inline CVectorFloat	GetVector();
public:
	signed char	Phi;
	signed char	Theta;

public:
	inline CVectorOptim operator/ (float) const;
	inline CVectorOptim operator+ (const CVectorOptim&) const;
};

CVectorOptim::CVectorOptim(const CVectorFloat &Vect)
{
	float	Ro=sqrt(Vect.m_Value[0]*Vect.m_Value[0]+Vect.m_Value[2]*Vect.m_Value[2]);
	if(Vect.m_Value[2]>=0)
	{
		Phi=acos(Vect.m_Value[0]/Ro)*M_127_PI;
	} else {
		Phi=-acos(Vect.m_Value[0]/Ro)*M_127_PI;
	}

	if(Vect.m_Value[1]>=0)
	{
		Theta=acos(Ro)*M_127_PI;
	} else {
		Theta=-acos(Ro)*M_127_PI;
	}

}

CVectorOptim::CVectorOptim(const CVector &Vect)
{
	float	Ro=sqrt(Vect.m_Value[0]*Vect.m_Value[0]+Vect.m_Value[2]*Vect.m_Value[2]);
	if(Vect.m_Value[2]>=0)
	{
		Phi=acos(Vect.m_Value[0]/Ro)*M_127_PI;
	} else {
		Phi=-acos(Vect.m_Value[0]/Ro)*M_127_PI;
	}

	if(Vect.m_Value[1]>=0)
	{
		Theta=acos(Ro)*M_127_PI;
	} else {
		Theta=-acos(Ro)*M_127_PI;
	}

}

CVectorOptim CVectorOptim::operator+ (const CVectorOptim &Param1) const
{
	CVectorOptim	Res;

	Res.Theta=Theta+Param1.Theta;
	Res.Phi=Phi+Param1.Phi;

	return Res;
}

CVectorOptim CVectorOptim::operator/ (float Param1) const
{
	CVectorOptim	Res;

	Res.Theta=Theta/Param1;
	Res.Phi=Phi/Param1;

	return Res;
}

CVectorFloat CVectorOptim::GetVector()
{
	CVectorFloat Res;

	Res.m_Value[0]=cos(Theta*M_PI_127);
	Res.m_Value[1]=sin(Theta*M_PI_127);
	Res.m_Value[2]=Res.m_Value[0]*sin(Phi*M_PI_127);
	Res.m_Value[0]*=cos(Phi*M_PI_127);

	return(Res);
}


class	CPhoton
{
public:
	inline	CPhoton()	{};
	inline	CPhoton(const CPhoton &Photon)
		:Power(Photon.Power)
	{
		Position.m_Value[0]=Photon.Position.m_Value[0];
		Position.m_Value[1]=Photon.Position.m_Value[1];
		Position.m_Value[2]=Photon.Position.m_Value[2];
		Direction.Theta=Photon.Direction.Theta;
		Direction.Phi=Photon.Direction.Phi;
		Flag=Photon.Flag;
	}
	inline	CPhoton(const CVector&Pos,const CVector&Dir,const CColor&color)
		:Power(color),Direction(Dir)
	{
		Position.m_Value[0]=Pos.m_Value[0];
		Position.m_Value[1]=Pos.m_Value[1];
		Position.m_Value[2]=Pos.m_Value[2];
	}

public:
	CVectorFloat	Position;
	CVectorOptim	Direction;
	CColor			Power;
	char			Flag;


};



class CPhotonCompare
{
  CVectorFloat comparepoint;

public:
  CPhotonCompare()	{};
  CPhotonCompare(CVectorFloat const& comparepoint)
    :comparepoint(comparepoint){};

    
  inline bool operator()(CPhoton *v1, CPhoton *v2) const
  {
    // compares distance from (0,0,0)
    return (CVectorFloat::length2(comparepoint,v1->Position)<CVectorFloat::length2(comparepoint,v2->Position));
  }
};


///structure de données photons utilisés dans matiere
class	CPhotonParameters
{
public:
	CPhotonParameters()	{m_Actif=false;};

	void	SetCount(long Param)		{m_Count=Param; m_Actif=true;}
	void	SetIntensity(float Param)	{m_Intensity=Param; m_Actif=true;}
	void	SetProbReflect(float Param)	{m_ProbReflect=Param; m_Actif=true;}
	float	GetProbReflect() const		{return(m_ProbReflect);}

public:
	bool	m_Actif;
	long	m_Count;
	float	m_Intensity;
	float	m_ProbReflect;
};


#endif // _PHOTON_H_
