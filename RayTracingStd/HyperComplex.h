////**************************************************************************
/// CLASSE IMPLEMENTANT LES HYPERCOMPLEXES classiques (multiplication commutative)
/// La table de multiplication est la suivante :
///		*||  r |  i |  j |  k |
///  ==========================
///  | r ||  r |  i |  j |  k |
/// __________________________
///  | i ||  i | -r |  k | -j |
///  __________________________
///  | j ||  j |  k | -r | -i |
///  __________________________
///  | k ||  k | -j | -i |  r | 
///  __________________________

/// Etat classe : EN COURS


#ifndef	_CHyperComplex
#define _CHyperComplex

#include "BaseHyperAlgebra.h"



template<class Type_Elem,HYPERFONCTION_TYPE Type>
class CHyperComplex : public CBaseHyperAlgebra<CHyperComplex,Type_Elem>
{
// Construction
public:
	inline CHyperComplex();
	inline CHyperComplex(Type_Elem a,Type_Elem b,Type_Elem c, Type_Elem d);
	inline CHyperComplex(const CHyperComplex<Type_Elem,Type>&);
	inline CHyperComplex(const CBaseHyperAlgebra<CHyperComplex<Type_Elem,Type>,Type_Elem>&);

	inline	virtual std::string	GetAlgebraType() {return("hypercomplex");};
// Operations
public:
	inline CHyperComplex& operator = (const CBaseVector<4,double>&);
	inline CHyperComplex& operator = (const CHyperComplex<Type_Elem,Type>&);
	inline CHyperComplex& operator = (Type_Elem);
	inline virtual CHyperComplex& operator *= (const CHyperComplex<Type_Elem,Type>&);
	inline virtual CHyperComplex& operator *= (Type_Elem);

	//inline virtual Type_Elem Scalar(const CHyperComplex<Type_Elem,Type> &Param,const AxeType Type) const;

	inline virtual	void	Sqr();
	inline  void	Add(const CHyperComplex<Type_Elem,Type>&);
	inline  void	Sub(const CHyperComplex<Type_Elem,Type>&);
	inline  void	Mult(const CHyperComplex<Type_Elem,Type>&);
	inline  void	Mult(Type_Elem Param) {CBaseHyperAlgebra<CHyperComplex,Type_Elem>::Mult(Param);};


// Implementation
public:
	inline virtual ~CHyperComplex();
};

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplex<Type_Elem,Type>::CHyperComplex<Type_Elem,Type>()
:CBaseHyperAlgebra<CHyperComplex,Type_Elem>(Type)
{
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplex<Type_Elem,Type>::CHyperComplex<Type_Elem,Type>(Type_Elem a,Type_Elem b,
												   Type_Elem c, Type_Elem d)
:CBaseHyperAlgebra<CHyperComplex,Type_Elem>(Type)
{
	m_Value[0]=a;
	m_Value[1]=b;
	m_Value[2]=c;
	m_Value[3]=d;
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplex<Type_Elem,Type>::CHyperComplex<Type_Elem,Type>(const CHyperComplex &Param)
:CBaseHyperAlgebra<CHyperComplex,Type_Elem>(Type)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplex<Type_Elem,Type>::CHyperComplex<Type_Elem,Type>(const CBaseHyperAlgebra<CHyperComplex,Type_Elem> &Param)
:CBaseHyperAlgebra<CHyperComplex,Type_Elem>(Type)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplex<Type_Elem,Type>::~CHyperComplex<Type_Elem,Type>()
{
}


////////////////////////////////////////////////////////////////////////
////Opérateur = utilisé pour les classes génériques ne connaissant
////pas le type de l'instance template
////Notamment utilisé pour l'affichage des valeurs
////Les valeurs sont en type double
template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplex<Type_Elem,Type>& CHyperComplex<Type_Elem,Type>::operator = (const CBaseVector<4,double> &Param)
{
	//On caste dans le type du template
	m_Value[0]=Type_Elem(Param.m_Value[0]);
	m_Value[1]=Type_Elem(Param.m_Value[1]);
	m_Value[2]=Type_Elem(Param.m_Value[2]);
	m_Value[3]=Type_Elem(Param.m_Value[3]);

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplex<Type_Elem,Type>& CHyperComplex<Type_Elem,Type>::operator = (const CHyperComplex<Type_Elem,Type> &Param)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplex<Type_Elem,Type>& CHyperComplex<Type_Elem,Type>::operator = (Type_Elem Param)
{
	m_Value[0]=Param;
	m_Value[1]=0;
	m_Value[2]=0;
	m_Value[3]=0;

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplex<Type_Elem,Type>& CHyperComplex<Type_Elem,Type>::operator *= (const CHyperComplex<Type_Elem,Type> &Param)
{
   Mult(Param);
   return(*this);

}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplex<Type_Elem,Type>& CHyperComplex<Type_Elem,Type>::operator *= (Type_Elem Param)
{
	m_Value[0]*=Param;
	m_Value[1]*=Param;
	m_Value[2]*=Param;
	m_Value[3]*=Param;

   return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplex<Type_Elem,Type>::Sqr()
{
	//Mult(*this);
	double x = m_Value[0] * m_Value[0] -
			   m_Value[1] * m_Value[1] -
			   m_Value[2] * m_Value[2] +
			   m_Value[3] * m_Value[3];
	double y=  2.0 * (m_Value[0] * m_Value[1] - m_Value[2] * m_Value[3]);
	double z=  2.0 * (m_Value[2] * m_Value[0] - m_Value[3] * m_Value[1]);
	double w=  2.0 * (m_Value[3] * m_Value[0] + m_Value[2] * m_Value[1]);

   m_Value[0]=x;
   m_Value[1]=y;
   m_Value[2]=z;
   m_Value[3]=w;

}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplex<Type_Elem,Type>::Add(const CHyperComplex<Type_Elem,Type> &Param)
{
	///////////////////////////////
	m_Value[0]+=Param.m_Value[0];
	m_Value[1]+=Param.m_Value[1];
	m_Value[2]+=Param.m_Value[2];
	m_Value[3]+=Param.m_Value[3];
	////////////////////////////////
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplex<Type_Elem,Type>::Sub(const CHyperComplex<Type_Elem,Type> &Param)
{
	///////////////////////////////
	m_Value[0]-=Param.m_Value[0];
	m_Value[1]-=Param.m_Value[1];
	m_Value[2]-=Param.m_Value[2];
	m_Value[3]-=Param.m_Value[3];
	////////////////////////////////
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplex<Type_Elem,Type>::Mult(const CHyperComplex<Type_Elem,Type> &Param)
{
   double x= m_Value[0]*Param.m_Value[0]- //x1*x2
					m_Value[1]*Param.m_Value[1]- //y1*y2
					m_Value[2]*Param.m_Value[2]+ //z1*z2
					m_Value[3]*Param.m_Value[3]; //w1*w2

   double y = m_Value[1]*Param.m_Value[0]+ //y1*x2
					m_Value[0]*Param.m_Value[1]- //x1*y2
					m_Value[3]*Param.m_Value[2]- //w1*z2
					m_Value[2]*Param.m_Value[3]; //z1*w2

   double z = m_Value[2]*Param.m_Value[0]- //z1*x2
					m_Value[3]*Param.m_Value[1]+ //w1*y2
					m_Value[0]*Param.m_Value[2]- //x1*z2
					m_Value[1]*Param.m_Value[3]; //y1*w2

   double w = m_Value[3]*Param.m_Value[0]+ //w1*x2
					m_Value[2]*Param.m_Value[1]+ //z1*y2
					m_Value[1]*Param.m_Value[2]+ //y1*z2
					m_Value[0]*Param.m_Value[3]; //x1*w2

   m_Value[0]=x;
   m_Value[1]=y;
   m_Value[2]=z;
   m_Value[3]=w;

}

#endif
