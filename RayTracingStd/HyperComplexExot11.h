////**************************************************************************
/// CLASSE IMPLEMENTANT LES HYPERCOMPLEXES exotiques n°11
/// La table de multiplication est la suivante :
///
///
///  11	*||  r |  i |  j |  k |
///  ==========================
///  | r ||  r |  i | -j |  k |
///  __________________________
///  | i ||  i |  j |  k |  r |
///  __________________________
///  | j || -j | -k | -r |  i |
///  __________________________
///  | k ||  k | -r | -i |  j | 
///  __________________________

///
/// Etat classe : EN COURS

#ifndef	_CHyperComplexExot11
#define _CHyperComplexExot11

#include "BaseHyperAlgebra.h"



template<class Type_Elem,HYPERFONCTION_TYPE Type>
class CHyperComplexExot11 : public CBaseHyperAlgebra<CHyperComplexExot11,Type_Elem>
{
// Construction
public:
	inline CHyperComplexExot11();
	inline CHyperComplexExot11(Type_Elem a,Type_Elem b,Type_Elem c, Type_Elem d);
	inline CHyperComplexExot11(const CHyperComplexExot11<Type_Elem,Type>&);
	inline CHyperComplexExot11(const CBaseHyperAlgebra<CHyperComplexExot11<Type_Elem,Type>,Type_Elem>&);

	inline	virtual std::string	GetAlgebraType() {return("algebra11");};
// Operations
public:
	inline CHyperComplexExot11& operator = (const CBaseVector<4,double>&);
	inline CHyperComplexExot11& operator = (const CHyperComplexExot11<Type_Elem,Type>&);
	inline CHyperComplexExot11& operator = (Type_Elem);
	inline virtual CHyperComplexExot11& operator *= (const CHyperComplexExot11<Type_Elem,Type>&);
	inline virtual CHyperComplexExot11& operator *= (Type_Elem);

	inline virtual	void	Sqr();
	inline  void	Add(const CHyperComplexExot11<Type_Elem,Type>&);
	inline  void	Sub(const CHyperComplexExot11<Type_Elem,Type>&);
	inline  void	Mult(const CHyperComplexExot11<Type_Elem,Type>&);
	inline  void	Mult(Type_Elem Param) {CBaseHyperAlgebra<CHyperComplexExot11,Type_Elem>::Mult(Param);};

// Implementation
public:
	inline virtual ~CHyperComplexExot11();
};

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot11<Type_Elem,Type>::CHyperComplexExot11<Type_Elem,Type>()
:CBaseHyperAlgebra<CHyperComplexExot11,Type_Elem>(Type)
{
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot11<Type_Elem,Type>::CHyperComplexExot11<Type_Elem,Type>(Type_Elem a,Type_Elem b,
												   Type_Elem c, Type_Elem d)
:CBaseHyperAlgebra<CHyperComplexExot11,Type_Elem>(Type)
{
	m_Value[0]=a;
	m_Value[1]=b;
	m_Value[2]=c;
	m_Value[3]=d;
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot11<Type_Elem,Type>::CHyperComplexExot11<Type_Elem,Type>(const CHyperComplexExot11 &Param)
:CBaseHyperAlgebra<CHyperComplexExot11,Type_Elem>(Type)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot11<Type_Elem,Type>::CHyperComplexExot11<Type_Elem,Type>(const CBaseHyperAlgebra<CHyperComplexExot11,Type_Elem> &Param)
:CBaseHyperAlgebra<CHyperComplexExot11,Type_Elem>(Type)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot11<Type_Elem,Type>::~CHyperComplexExot11<Type_Elem,Type>()
{
}


////////////////////////////////////////////////////////////////////////
////Opérateur = utilisé pour les classes génériques ne connaissant
////pas le type de l'instance template
////Notamment utilisé pour l'affichage des valeurs
////Les valeurs sont en type double
template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot11<Type_Elem,Type>& CHyperComplexExot11<Type_Elem,Type>::operator = (const CBaseVector<4,double> &Param)
{
	//On caste dans le type du template
	m_Value[0]=Type_Elem(Param.m_Value[0]);
	m_Value[1]=Type_Elem(Param.m_Value[1]);
	m_Value[2]=Type_Elem(Param.m_Value[2]);
	m_Value[3]=Type_Elem(Param.m_Value[3]);

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot11<Type_Elem,Type>& CHyperComplexExot11<Type_Elem,Type>::operator = (const CHyperComplexExot11<Type_Elem,Type> &Param)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot11<Type_Elem,Type>& CHyperComplexExot11<Type_Elem,Type>::operator = (Type_Elem Param)
{
	m_Value[0]=Param;
	m_Value[1]=0;
	m_Value[2]=0;
	m_Value[3]=0;

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot11<Type_Elem,Type>& CHyperComplexExot11<Type_Elem,Type>::operator *= (const CHyperComplexExot11<Type_Elem,Type> &Param)
{
   Mult(Param);
   return(*this);

}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot11<Type_Elem,Type>& CHyperComplexExot11<Type_Elem,Type>::operator *= (Type_Elem Param)
{
	m_Value[0]*=Param;
	m_Value[1]*=Param;
	m_Value[2]*=Param;
	m_Value[3]*=Param;

   return(*this);
}



template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplexExot11<Type_Elem,Type>::Sqr()
{
   double x= m_Value[0]*m_Value[0]-
					m_Value[3]*m_Value[1]-
					m_Value[2]*m_Value[2]+ 
					m_Value[1]*m_Value[3]; //ok 

   double y = m_Value[1]*m_Value[0]+ 
					m_Value[0]*m_Value[1]- 
					m_Value[3]*m_Value[2]+
					m_Value[2]*m_Value[3];  //ok

   double z = -m_Value[2]*m_Value[0]+
					m_Value[1]*m_Value[1]-
					m_Value[0]*m_Value[2]+
					m_Value[3]*m_Value[3]; //ok

   double w = m_Value[3]*m_Value[0]-
					m_Value[2]*m_Value[1]+
					m_Value[1]*m_Value[2]+ 
					m_Value[0]*m_Value[3];  //ok

   m_Value[0]=x;
   m_Value[1]=y;
   m_Value[2]=z;
   m_Value[3]=w;
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplexExot11<Type_Elem,Type>::Add(const CHyperComplexExot11<Type_Elem,Type> &Param)
{
	///////////////////////////////
	m_Value[0]+=Param.m_Value[0];
	m_Value[1]+=Param.m_Value[1];
	m_Value[2]+=Param.m_Value[2];
	m_Value[3]+=Param.m_Value[3];
	////////////////////////////////
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplexExot11<Type_Elem,Type>::Sub(const CHyperComplexExot11<Type_Elem,Type> &Param)
{
	///////////////////////////////
	m_Value[0]-=Param.m_Value[0];
	m_Value[1]-=Param.m_Value[1];
	m_Value[2]-=Param.m_Value[2];
	m_Value[3]-=Param.m_Value[3];
	////////////////////////////////
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplexExot11<Type_Elem,Type>::Mult(const CHyperComplexExot11<Type_Elem,Type> &Param)
{
   double x= m_Value[0]*Param.m_Value[0]-
					m_Value[3]*Param.m_Value[1]- 
					m_Value[2]*Param.m_Value[2]+ 
					m_Value[1]*Param.m_Value[3]; //ok 

   double y = m_Value[1]*Param.m_Value[0]+ 
					m_Value[0]*Param.m_Value[1]- 
					m_Value[3]*Param.m_Value[2]+
					m_Value[2]*Param.m_Value[3];  //ok

   double z = -m_Value[2]*Param.m_Value[0]+
					m_Value[1]*Param.m_Value[1]-
					m_Value[0]*Param.m_Value[2]+
					m_Value[3]*Param.m_Value[3]; //ok

   double w = m_Value[3]*Param.m_Value[0]-
					m_Value[2]*Param.m_Value[1]+
					m_Value[1]*Param.m_Value[2]+ 
					m_Value[0]*Param.m_Value[3];  //ok

   m_Value[0]=x;
   m_Value[1]=y;
   m_Value[2]=z;
   m_Value[3]=w;

}

#endif
