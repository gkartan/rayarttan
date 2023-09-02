////**************************************************************************
/// CLASSE IMPLEMENTANT LES HYPERCOMPLEXES exotiques n°2
/// La table de multiplication est la suivante :
///
///  2  *||  r |  i |  j |  k |
///  ==========================
///  | r ||  r |  i | -j |  k |
///  __________________________
///  | i ||  i | -r |  r | -i |
///  __________________________
///  | j || -j |  k | -k |  j |
///  __________________________
///  | k ||  r | -i |  j |  k | 
///  __________________________

/// Etat classe : EN COURS

#ifndef	_CHyperComplexExot02
#define _CHyperComplexExot02

#include "BaseHyperAlgebra.h"



template<class Type_Elem,HYPERFONCTION_TYPE Type>
class CHyperComplexExot02 : public CBaseHyperAlgebra<CHyperComplexExot02,Type_Elem>
{
// Construction
public:
	inline CHyperComplexExot02();
	inline CHyperComplexExot02(Type_Elem a,Type_Elem b,Type_Elem c, Type_Elem d);
	inline CHyperComplexExot02(const CHyperComplexExot02<Type_Elem,Type>&);
	inline CHyperComplexExot02(const CBaseHyperAlgebra<CHyperComplexExot02<Type_Elem,Type>,Type_Elem>&);

	inline	virtual std::string	GetAlgebraType() {return("algebra02");};
// Operations
public:
	inline CHyperComplexExot02& operator = (const CBaseVector<4,double>&);
	inline CHyperComplexExot02& operator = (const CHyperComplexExot02<Type_Elem,Type>&);
	inline CHyperComplexExot02& operator = (Type_Elem);
	inline virtual CHyperComplexExot02& operator *= (const CHyperComplexExot02<Type_Elem,Type>&);
	inline virtual CHyperComplexExot02& operator *= (Type_Elem);

	inline virtual	void	Sqr();
	inline  void	Add(const CHyperComplexExot02<Type_Elem,Type>&);
	inline  void	Sub(const CHyperComplexExot02<Type_Elem,Type>&);
	inline  void	Mult(const CHyperComplexExot02<Type_Elem,Type>&);
	inline  void	Mult(Type_Elem Param) {CBaseHyperAlgebra<CHyperComplexExot02,Type_Elem>::Mult(Param);};
// Implementation
public:
	inline virtual ~CHyperComplexExot02();
};

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot02<Type_Elem,Type>::CHyperComplexExot02<Type_Elem,Type>()
:CBaseHyperAlgebra<CHyperComplexExot02,Type_Elem>(Type)
{
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot02<Type_Elem,Type>::CHyperComplexExot02<Type_Elem,Type>(Type_Elem a,Type_Elem b,
												   Type_Elem c, Type_Elem d)
:CBaseHyperAlgebra<CHyperComplexExot02,Type_Elem>(Type)
{
	m_Value[0]=a;
	m_Value[1]=b;
	m_Value[2]=c;
	m_Value[3]=d;
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot02<Type_Elem,Type>::CHyperComplexExot02<Type_Elem,Type>(const CHyperComplexExot02 &Param)
:CBaseHyperAlgebra<CHyperComplexExot02,Type_Elem>(Type)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot02<Type_Elem,Type>::CHyperComplexExot02<Type_Elem,Type>(const CBaseHyperAlgebra<CHyperComplexExot02,Type_Elem> &Param)
:CBaseHyperAlgebra<CHyperComplexExot02,Type_Elem>(Type)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot02<Type_Elem,Type>::~CHyperComplexExot02<Type_Elem,Type>()
{
}


////////////////////////////////////////////////////////////////////////
////Opérateur = utilisé pour les classes génériques ne connaissant
////pas le type de l'instance template
////Notamment utilisé pour l'affichage des valeurs
////Les valeurs sont en type double
template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot02<Type_Elem,Type>& CHyperComplexExot02<Type_Elem,Type>::operator = (const CBaseVector<4,double> &Param)
{
	//On caste dans le type du template
	m_Value[0]=Type_Elem(Param.m_Value[0]);
	m_Value[1]=Type_Elem(Param.m_Value[1]);
	m_Value[2]=Type_Elem(Param.m_Value[2]);
	m_Value[3]=Type_Elem(Param.m_Value[3]);

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot02<Type_Elem,Type>& CHyperComplexExot02<Type_Elem,Type>::operator = (const CHyperComplexExot02<Type_Elem,Type> &Param)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot02<Type_Elem,Type>& CHyperComplexExot02<Type_Elem,Type>::operator = (Type_Elem Param)
{
	m_Value[0]=Param;
	m_Value[1]=0;
	m_Value[2]=0;
	m_Value[3]=0;

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot02<Type_Elem,Type>& CHyperComplexExot02<Type_Elem,Type>::operator *= (const CHyperComplexExot02<Type_Elem,Type> &Param)
{
   Mult(Param);
   return(*this);

}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CHyperComplexExot02<Type_Elem,Type>& CHyperComplexExot02<Type_Elem,Type>::operator *= (Type_Elem Param)
{
	m_Value[0]*=Param;
	m_Value[1]*=Param;
	m_Value[2]*=Param;
	m_Value[3]*=Param;

   return(*this);
}


template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplexExot02<Type_Elem,Type>::Sqr()
{
   double x= m_Value[0]*m_Value[0]+
					m_Value[3]*m_Value[0]- 
					m_Value[1]*m_Value[1]+ 
					m_Value[1]*m_Value[2]; //ok

   double y = m_Value[1]*m_Value[0]+ 
					m_Value[0]*m_Value[1]- 
					m_Value[3]*m_Value[1]- 
					m_Value[1]*m_Value[3]; //ok

   double z = -m_Value[2]*m_Value[0]-
					m_Value[0]*m_Value[2]+
					m_Value[3]*m_Value[2]+
					m_Value[2]*m_Value[3]; 

   double w = m_Value[2]*m_Value[1]-
					m_Value[2]*m_Value[2]+
					m_Value[0]*m_Value[3]+ 
					m_Value[3]*m_Value[3]; 

   m_Value[0]=x;
   m_Value[1]=y;
   m_Value[2]=z;
   m_Value[3]=w;
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplexExot02<Type_Elem,Type>::Add(const CHyperComplexExot02<Type_Elem,Type> &Param)
{
	///////////////////////////////
	m_Value[0]+=Param.m_Value[0];
	m_Value[1]+=Param.m_Value[1];
	m_Value[2]+=Param.m_Value[2];
	m_Value[3]+=Param.m_Value[3];
	////////////////////////////////
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplexExot02<Type_Elem,Type>::Sub(const CHyperComplexExot02<Type_Elem,Type> &Param)
{
	///////////////////////////////
	m_Value[0]-=Param.m_Value[0];
	m_Value[1]-=Param.m_Value[1];
	m_Value[2]-=Param.m_Value[2];
	m_Value[3]-=Param.m_Value[3];
	////////////////////////////////
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CHyperComplexExot02<Type_Elem,Type>::Mult(const CHyperComplexExot02<Type_Elem,Type> &Param)
{
   double x= m_Value[0]*Param.m_Value[0]+
					m_Value[3]*Param.m_Value[0]- 
					m_Value[1]*Param.m_Value[1]+ 
					m_Value[1]*Param.m_Value[2]; //ok

   double y = m_Value[1]*Param.m_Value[0]+ 
					m_Value[0]*Param.m_Value[1]- 
					m_Value[3]*Param.m_Value[1]- 
					m_Value[1]*Param.m_Value[3]; //ok

   double z = -m_Value[2]*Param.m_Value[0]-
					m_Value[0]*Param.m_Value[2]+
					m_Value[3]*Param.m_Value[2]+
					m_Value[2]*Param.m_Value[3]; 

   double w = m_Value[2]*Param.m_Value[1]-
					m_Value[2]*Param.m_Value[2]+
					m_Value[0]*Param.m_Value[3]+ 
					m_Value[3]*Param.m_Value[3]; 

   m_Value[0]=x;
   m_Value[1]=y;
   m_Value[2]=z;
   m_Value[3]=w;

}

#endif
