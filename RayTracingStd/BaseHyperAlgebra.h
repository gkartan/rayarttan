#ifndef	_CBASEHYPERALGEBRA
#define _CBASEHYPERALGEBRA

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "BaseVector.h"
#include "SinC.h"
#include "SinhC.h"
#include <valarray>
#include <complex>
#include <cmath>
#include "HyperFonctionAmd.h"
#include "HyperFonctionNormal.h"
#include <ostream.h>

///Coordonnées dans un espace tridimensionnel

typedef enum 
{
	AXE_X=0,
	AXE_Y,
	AXE_Z
} AxeType;

typedef enum
{
	HYPERFONCTION_NORMAL=0,
	HYPERFONCTION_AMD,
} HYPERFONCTION_TYPE;


////Optimisation comme pour l'instant on utilise pas les fonctions avancées
////optimisé processeur
extern CHyperFonctionNormal<double>		Global_HyperFonction;


template<class T,class Type_Elem>
class CBaseHyperAlgebra : public CBaseVector<4,Type_Elem>
{
// Construction
public:
	CBaseHyperAlgebra();
	CBaseHyperAlgebra(HYPERFONCTION_TYPE);

	inline  Type_Elem	GetX() const {return m_Value[0];}
	inline  Type_Elem	GetY() const {return m_Value[1];}
	inline  Type_Elem	GetZ() const {return m_Value[2];}
	inline  Type_Elem	GetW() const {return m_Value[3];}
	inline  void		SetX(Type_Elem elem)  {m_Value[0]=elem;}
	inline  void		SetY(Type_Elem elem)  {m_Value[1]=elem;}
	inline  void		SetZ(Type_Elem elem)  {m_Value[2]=elem;}
	inline  void		SetW(Type_Elem elem)  {m_Value[3]=elem;}

	inline	Type_Elem	real()   const {return m_Value[0];}
	inline  T			unreal() const {return T(0,m_Value[1],m_Value[2],m_Value[3]);}

	inline	virtual std::string			GetAlgebraType()=0;
	inline  virtual bool				GetOptimisation() const	{return m_pHyperFonction->GetOptimisation();}; //classe non optimisé 3DNow
	inline			HYPERFONCTION_TYPE	GetType() const			{return((m_pHyperFonction->GetOptimisation()==true)?HYPERFONCTION_AMD:HYPERFONCTION_NORMAL);}; //classe non optimisé 3DNow

private:
	CBaseHyperFonction<Type_Elem>		*m_pHyperFonction;
// Operations
public:
	T operator + (const T&) const;
	T operator + (Type_Elem) const;
	//virtual T operator * (const T&) const {return(*this);};  
	//virtual T operator * (Type_Elem) const   {return(*this);}; 
	//virtual T operator *= (Type_Elem) const   {return(*this);}; 

	T conjg() const;	//Calcul du conjugué
	T inv()   const;		//Calcul de l'inverse
	virtual   Type_Elem		norm()  const;		//Calcul de la norme
	Type_Elem		norm2() const;	//Calcul de la norme au carré

	void		BeginFunct( std::complex<Type_Elem> &a,
							std::complex<Type_Elem> &b) const;
	void		EndFunct(std::complex<Type_Elem> &a,
						 std::complex<Type_Elem> &b);

	Type_Elem	Abs() const;
	virtual Type_Elem		Scalar(const T &Param,const AxeType) const;
// Implementation
public:
	virtual ~CBaseHyperAlgebra();

public:
	/*******************Liste des fonctions spéciales*******************/	
	T			sin()		const;
	T			asin()		const;
	T			cos()		const;
	T			acos()		const;
	T			tan()		const;
	T			atan()		const;
	T			cotan()		const;
	T			acotan()	const;
	T			exp()		const;
	T			log()		const;
	T			pow(int n)	const;
	T			sqrt()		const;
	/*******************Fin Liste des fonctions spéciales*******************/	

	/*******************Liste des fonctions non const qui modifie lui-même**/
	inline	 void	Pow(int n);
	virtual	 void	Sqr()=0;
	virtual  void	Add(const T&)=0;
	virtual  void	Sub(const T&)=0;
	virtual  void	Mult(const T&)=0;
	inline	 void	Div(const T&);
	inline	 void	Mult(const Type_Elem);
	/***************Fin Liste des fonctions non const qui modifie lui-même**/

public:
	/******************opérateurs globaux*********************/
	//------------------division
	inline friend	T	operator/ (double,const T&);
	inline friend	T	operator/ (const T&,const T&);
	inline friend	T	operator/ (const T&,double);
	inline friend	T	operator/ (const T &,const CBaseHyperAlgebra<T,Type_Elem>&);
	//------------------soustraction
	inline friend	T	operator- (double,const T&);
	//inline friend	T	operator- (const T&,const T&);
	inline friend	T	operator- (const T&,double);
	inline friend	T	operator- (const T&);
	//------------------multiplication
	inline friend	T	operator* (const T&,const T&);
	inline friend	T	operator* (const T&,double);
	inline friend	T	operator* (const T&,const CBaseHyperAlgebra<T,Type_Elem>&);
	inline friend	T	operator* (const CBaseHyperAlgebra<T,Type_Elem>&,const T&);


	//-------------------stream
	inline	friend	ostream&	operator<<(ostream&,const CBaseHyperAlgebra<T,Type_Elem>&);
	/******************fin opérateurs globaux*****************/
};

template<class T,class Type_Elem>
CBaseHyperAlgebra<T,Type_Elem>::CBaseHyperAlgebra<T,Type_Elem>()
{
	//m_pHyperFonction=NULL;
	m_pHyperFonction=&Global_HyperFonction;
}

template<class T,class Type_Elem>
CBaseHyperAlgebra<T,Type_Elem>::CBaseHyperAlgebra<T,Type_Elem>(HYPERFONCTION_TYPE Type)
{
	/*switch(Type)
	{
		case HYPERFONCTION_NORMAL:
			m_pHyperFonction=new CHyperFonctionNormal<Type_Elem>;
			break;
		//case HYPERFONCTION_AMD:
		//	m_pHyperFonction=new CHyperFonctionAMD<Type_Elem>;
		//	break;
		default:
			m_pHyperFonction=new CHyperFonctionNormal<Type_Elem>;
	}*/
	m_pHyperFonction=&Global_HyperFonction;
}


template<class T,class Type_Elem>
CBaseHyperAlgebra<T,Type_Elem>::~CBaseHyperAlgebra<T,Type_Elem>()
{
	/*if(m_pHyperFonction!=NULL)
	{		delete m_pHyperFonction;
		m_pHyperFonction=NULL;
	}*/
}

template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::operator + (const T &Param) const
{
	T Res;

	Res.m_Value[0]=m_Value[0]+Param.m_Value[0];
	Res.m_Value[1]=m_Value[1]+Param.m_Value[1];
	Res.m_Value[2]=m_Value[2]+Param.m_Value[2];
	Res.m_Value[3]=m_Value[3]+Param.m_Value[3];

	return(Res);
}

template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::operator + (Type_Elem Param) const
{
	T Res(*this);

	Res.m_Value[0]=m_Value[0]+Param;

	return(Res);
}



//Calcul du conjugué
template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::conjg() const
{
	T Res;

	Res.m_Value[0]=m_Value[0];
	Res.m_Value[1]=-m_Value[1];
	Res.m_Value[2]=-m_Value[2];
	Res.m_Value[3]=-m_Value[3];

	return(Res);
}

//Calcul de l'inverse
template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::inv() const
{
	return(conjg()/norm2());
}

//Calcul de la norme
template<class T,class Type_Elem>
Type_Elem	CBaseHyperAlgebra<T,Type_Elem>::norm()	const
{
	T Res=(*this)*conjg();

	return(::sqrt(Res.m_Value[0]));
}

//Calcul de la norme au carré
template<class T,class Type_Elem>
Type_Elem	CBaseHyperAlgebra<T,Type_Elem>::norm2() const
{
	T Res=(*this)*conjg();

	return(Res.m_Value[0]);
}

template<class T,class Type_Elem>
Type_Elem CBaseHyperAlgebra<T,Type_Elem>::Scalar(const T &Param,const AxeType Type) const
{
  Type_Elem res=m_Value[0]*Param.m_Value[0]+
			 m_Value[1]*Param.m_Value[1]+
			 m_Value[2]*Param.m_Value[2]+
			 m_Value[3]*Param.m_Value[3];

  return (res);
}



template<class T,class Type_Elem>
Type_Elem	CBaseHyperAlgebra<T,Type_Elem>::Abs() const
{
	std::valarray<Type_Elem>    temp(4);             
                                        
    temp[0] = m_Value[0];        
    temp[1] = m_Value[1];        
    temp[2] = m_Value[2];        
    temp[3] = m_Value[3];

    Type_Elem	maxim = abs(temp).max();    // overflow protection
            
    if    (maxim == 0.0)
    {
        return(maxim);
    }
    else
    {
        Type_Elem    mixam = 1.0/maxim;    // prefer multiplications over divisions
        
        temp *= mixam;
        
        temp *= temp;
        
        return(maxim*sqrt(temp.sum()));
    }
}



template<class T,class Type_Elem>
void CBaseHyperAlgebra<T,Type_Elem>::BeginFunct(std::complex<Type_Elem> &a,
												std::complex<Type_Elem> &b) const
{
	a=std::complex<Type_Elem>(m_Value[0] - m_Value[3],m_Value[1]+m_Value[2]);
	b=std::complex<Type_Elem>(m_Value[0] + m_Value[3],m_Value[1]-m_Value[2]);
}

template<class T,class Type_Elem>
void CBaseHyperAlgebra<T,Type_Elem>::EndFunct(std::complex<Type_Elem> &a,
											  std::complex<Type_Elem> &b)
{

	m_Value[0] = .5 * (a.real() + b.real());
	m_Value[1] = .5 * (a.imag() + b.imag());
	m_Value[2] = .5 * (a.imag() - b.imag());
	m_Value[3] = .5 * (b.real() - a.real());
}




/*************************************************************************/
/* Definitions des fonctions spéciales */
/**************************************************************************/
template<class T,class Type_Elem>
T	CBaseHyperAlgebra<T,Type_Elem>::sin() const
{
	T res;

	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	m_pHyperFonction->sin(a,b);
	res.EndFunct(a,b);

	return res;
}

template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::cos() const
{
	T res;

	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	m_pHyperFonction->cos(a,b);
	res.EndFunct(a,b);

	return res;

}

template<class T,class Type_Elem>
T	CBaseHyperAlgebra<T,Type_Elem>::tan() const
{
	T res;
	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	m_pHyperFonction->tan(a,b);
	res.EndFunct(a,b);

	return res;
}

template<class T,class Type_Elem>
T	CBaseHyperAlgebra<T,Type_Elem>::cotan() const
{
	T res;
	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	m_pHyperFonction->cotan(a,b);
	res.EndFunct(a,b);

	return res;
}

template<class T,class Type_Elem>
T	CBaseHyperAlgebra<T,Type_Elem>::exp() const
{
	T res;
	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	res.EndFunct(std::exp(a),std::exp(b));

	return res;
}

template<class T,class Type_Elem>
T	CBaseHyperAlgebra<T,Type_Elem>::log() const
{
	T res;
	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	m_pHyperFonction->log(a,b);
	res.EndFunct(a,b);

	return res;
}

template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::asin() const
{
	T res;
	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	m_pHyperFonction->asin(a,b);
	res.EndFunct(a,b);

	return res;

}

template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::acos() const
{
	T res;
	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	m_pHyperFonction->acos(a,b);
	res.EndFunct(a,b);

	return res;

}

template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::atan() const
{
	T res;
	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	m_pHyperFonction->atan(a,b);
	res.EndFunct(a,b);

	return res;

}

template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::acotan() const
{
	T res;
	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	m_pHyperFonction->acotan(a,b);
	res.EndFunct(a,b);

	return res;

}

/*template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::pow(int n) const
{
    if        (n > 1)
    {
        int    m = n>>1;
        
        T Res(pow(m));
        
        Res.Sqr();
        
        if    (n != (m<<1))
        {
            Res.Mult(*this); // n odd
        }
        
        return(Res);
    }
    else if    (n == 1)
    {
        return(*this);
    }
    else if    (n == 0)
    {
        return(T(1,0,0,0));
    }
    else    /* n < 0 */
/*    {
		T Res(T(1,0,0,0)/(*this));
		Res.pow(-n);
		return(Res);
    }
}*/


//Fonction pow dérécursivé pour éviter les copies
template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::pow(int n) const
{
	if(n==0)
		return(T(1,0,0,0));

	T Res(*this);
	while(n>2)
	{
		n = n >> 1;
		Res.Sqr();
	}

	if(n==2)
		Res.Sqr();
	else
	if(n==1)
		Res.Mult(*this);

	return(Res);
}

template<class T,class Type_Elem>
T CBaseHyperAlgebra<T,Type_Elem>::sqrt() const
{
	T	res;

	std::complex<Type_Elem> a;
	std::complex<Type_Elem> b;

	BeginFunct(a,b);
	res.EndFunct(std::sqrt(a),std::sqrt(b));

	return(res);
}
/*************************************************************************/


/*************************************************************************/


/*************************************************************************/
/* Definitions des opérateurs globaux */
/**************************************************************************/
template<class T,class Type_Elem>
ostream&	operator<<(ostream &o,const CBaseHyperAlgebra<T,Type_Elem> &h)
{
	o << "<" << h.m_Value[0] << "," << h.m_Value[1] 
	  << "," << h.m_Value[2] << "," << h.m_Value[3] << ">";

	return(o);
}

/////////////Definitions des opérateurs de division////////////////////
template<class T>
T	operator / (double Param1,const T& Param2)
{
	T Numerateur(Param1,0,0,0);

	return(Numerateur*Param2.inv());
}

template<class T>
T	operator / (const T &Param1,const T &Param2)
{
	return(Param1*Param2.inv());
}

template<class T>
T	operator / (const T &Param1,double Param2)
{
	T Res;

	Res.m_Value[0]=Param1.m_Value[0]/Param2;
	Res.m_Value[1]=Param1.m_Value[1]/Param2;
	Res.m_Value[2]=Param1.m_Value[2]/Param2;
	Res.m_Value[3]=Param1.m_Value[3]/Param2;

	return(Res);
}

template<class T,class Type_Elem>
T	operator / (const T &Param1,const CBaseHyperAlgebra<T,Type_Elem>& Param2)
{
	return(Param1*Param2.inv());
}

////////////Fin opérateurs de divisions///////////////////////////


/////////////Definitions des opérateurs de soustraction////////////////////
template<class T>
T	operator - (double Param1,const T &Param2)
{
	T Res(Param1,0,0,0);

	Res=Res-Param2;

	return(Res);
}

/*template<class T,class Type_Elem>
T	CBaseHyperAlgebra<T,Type_Elem>::operator- (const T &Param1,const T& Param2)
{
	T Res;

	Res.m_Value[0]=Param1.m_Value[0]-Param2.m_Value[0];
	Res.m_Value[1]=Param1.m_Value[1]-Param2.m_Value[1];
	Res.m_Value[2]=Param1.m_Value[2]-Param2.m_Value[2];
	Res.m_Value[3]=Param1.m_Value[3]-Param2.m_Value[3];

	return(Res);
}*/

template<class T>
T	operator - (const T &Param1,double Param)
{
	T Res(Param1);

	Res.m_Value[0]-=Param;

	return(Res);
}

template<class T>
T	operator - (const T &Param1)
{
	T Res;

	Res.m_Value[0]=-Param1.m_Value[0];
	Res.m_Value[1]=-Param1.m_Value[1];
	Res.m_Value[2]=-Param1.m_Value[2];
	Res.m_Value[3]=-Param1.m_Value[3];

	return(Res);
}


////////////Fin opérateurs de soustraction///////////////////////////

/////////////Definitions des opérateurs de multiplication////////////////////
template<class T>
T	operator * (const T &Param1,
				const T &Param2)
{
   T Res(Param1);
   Res.Mult(Param2);

   return(Res);
}

template<class T>
T	operator * (const T &Param1,
				double Param2)
{
	T Res;
	Res.m_Value[0]*=Param;
	Res.m_Value[1]*=Param;
	Res.m_Value[2]*=Param;
	Res.m_Value[3]*=Param;

   return(Res);
}

template<class T,class Type_Elem>
T	operator * (const T &Param1,const CBaseHyperAlgebra<T,Type_Elem>& Param2)
{
   T Res(Param1);
   Res.Mult(Param2);

   return(Res);
}

template<class T,class Type_Elem>
T	operator * (const CBaseHyperAlgebra<T,Type_Elem>& Param1,const T&Param2)
{
   T Res(Param1);
   Res.Mult(Param2);

   return(Res);
}

/////////////Fin opérateurs de multiplication/////////////////////////


/*************************************************************************/
/* Definitions des fonctions spéciales modifiant l'élément (non const) */
/**************************************************************************/
template<class T,class Type_Elem>
void CBaseHyperAlgebra<T,Type_Elem>::Pow(int n)
{
	if(n==0)
	{
		m_Value[0]=1;
		m_Value[1]=0;
		m_Value[2]=0;
		m_Value[3]=0;
	}
	if(n==1)
	{
		//On ne fait rien
		return;
	}

	while(n>2)
	{
		n = n >> 1;
		Sqr();
	}

	if(n==2)
		Sqr();
	else
	if(n==1)  //nothing
		Mult(*this);
}

template<class T,class Type_Elem>
void	CBaseHyperAlgebra<T,Type_Elem>::Mult(const Type_Elem Param)
{
	m_Value[0]*=Param;
	m_Value[1]*=Param;
	m_Value[2]*=Param;
	m_Value[3]*=Param;
}

template<class T,class Type_Elem>
void	CBaseHyperAlgebra<T,Type_Elem>::Div(const T &Param)
{
	Mult(Param.inv());
}

#endif
