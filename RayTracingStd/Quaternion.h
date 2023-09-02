////**************************************************************************
/// CLASSE IMPLEMENTANT LES QUATERNIONS d'HAMILTON
/// La table de multiplication est la suivante :
///   *  ||  r |  i |  j |  k |
///  ==========================
///  | r ||  r |  i |  j |  k |
///  __________________________
///  | i ||  i | -r |  k | -j |
///  __________________________
///  | j ||  j | -k | -r |  i |
///  __________________________
///  | k ||  k |  j | -i | -r | 
///  __________________________

/// Etat classe : EN COURS

#ifndef	_CQUATERNION
#define _CQUATERNION

#include "BaseHyperAlgebra.h"
#include "emmintrin.h"
#include "mm3dnow.h"

///Coordonnées dans un espace tridimensionnel

template<class Type_Elem,HYPERFONCTION_TYPE Type>
class CQuaternion : public CBaseHyperAlgebra<CQuaternion,Type_Elem> 
{
// Construction
public:
	inline CQuaternion();
	inline CQuaternion(Type_Elem a,Type_Elem b,Type_Elem c, Type_Elem d);
	inline CQuaternion(const CQuaternion&);
	inline CQuaternion(const CBaseHyperAlgebra<CQuaternion,Type_Elem>&);

	inline	virtual std::string	GetAlgebraType() {return("quaternion");};
// Operations
public:
	inline CQuaternion& operator = (const CBaseVector<4,double>&);
	inline CQuaternion& operator = (const CQuaternion&);
	inline CQuaternion& operator = (Type_Elem);
	inline CQuaternion& operator += (const CQuaternion&);
	inline CQuaternion& operator -= (const CQuaternion&);
	inline virtual CQuaternion& operator *= (const CQuaternion&);
	inline virtual CQuaternion& operator *= (Type_Elem);

	inline virtual  Type_Elem  norm() const;		//calcul optimisé
	inline virtual  Type_Elem  norm2() const;		//calcul optimisé
	inline virtual	void	Sqr();
	inline virtual  void	Add(const CQuaternion&);
	inline virtual  void	Sub(const CQuaternion&);
	inline virtual  void	Mult(const CQuaternion&);
	inline virtual  void	Div(const CQuaternion&);
	inline virtual  void	Mult(Type_Elem Param) {CBaseHyperAlgebra<CQuaternion,Type_Elem>::Mult(Param);};

// Implementation
public:
	inline virtual ~CQuaternion();
};

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>::CQuaternion<Type_Elem,Type>()
:CBaseHyperAlgebra<CQuaternion,Type_Elem>(Type)
{
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>::CQuaternion<Type_Elem,Type>(Type_Elem a,Type_Elem b,Type_Elem c, Type_Elem d)
:CBaseHyperAlgebra<CQuaternion,Type_Elem>(Type)
{
	m_Value[0]=a;
	m_Value[1]=b;
	m_Value[2]=c;
	m_Value[3]=d;
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>::CQuaternion<Type_Elem,Type>(const CQuaternion &Param)
:CBaseHyperAlgebra<CQuaternion,Type_Elem>(Type)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>::CQuaternion<Type_Elem,Type>(const CBaseHyperAlgebra<CQuaternion,Type_Elem> &Param)
:CBaseHyperAlgebra<CQuaternion,Type_Elem>(Type)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>::~CQuaternion<Type_Elem,Type>()
{
}

////////////////////////////////////////////////////////////////////////
////Opérateur = utilisé pour les classes génériques ne connaissant
////pas le type de l'instance template
////Notamment utilisé pour l'affichage des valeurs
////Les valeurs sont en type double
template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>& CQuaternion<Type_Elem,Type>::operator = (const CBaseVector<4,double> &Param)
{
	//On caste dans le type du template
	m_Value[0]=Type_Elem(Param.m_Value[0]);
	m_Value[1]=Type_Elem(Param.m_Value[1]);
	m_Value[2]=Type_Elem(Param.m_Value[2]);
	m_Value[3]=Type_Elem(Param.m_Value[3]);

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>& CQuaternion<Type_Elem,Type>::operator = (const CQuaternion &Param)
{
	m_Value[0]=Param.m_Value[0];
	m_Value[1]=Param.m_Value[1];
	m_Value[2]=Param.m_Value[2];
	m_Value[3]=Param.m_Value[3];

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>& CQuaternion<Type_Elem,Type>::operator = (Type_Elem Param)
{
	m_Value[0]=Param;
	m_Value[1]=0;
	m_Value[2]=0;
	m_Value[3]=0;

	return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>& CQuaternion<Type_Elem,Type>::operator += (const CQuaternion &Param)
{
	return((*this)+Param);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>& CQuaternion<Type_Elem,Type>::operator -= (const CQuaternion &Param)
{
	return((*this)-Param);
}


template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>& CQuaternion<Type_Elem,Type>::operator *= (const CQuaternion &Param)
{
   Mult(Param);

   return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
CQuaternion<Type_Elem,Type>& CQuaternion<Type_Elem,Type>::operator *= (Type_Elem Param)
{
	m_Value[0]*=Param;
	m_Value[1]*=Param;
	m_Value[2]*=Param;
	m_Value[3]*=Param;

   return(*this);
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CQuaternion<Type_Elem,Type>::Sqr()
{
	Type_Elem Temp(2.0*m_Value[0]);

	m_Value[0]=		 m_Value[0]*m_Value[0]-
					 m_Value[1]*m_Value[1]-
					 m_Value[2]*m_Value[2]-
				     m_Value[3]*m_Value[3];
	m_Value[1] *= Temp;			
	m_Value[2] *= Temp;
	m_Value[3] *= Temp;

}

/////////////////////////////////////////////////////////
///Description : Ajout d'un quaternion à cette instance
///
///Remarques :	
/////////////////////////////////////////////////////////
template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CQuaternion<Type_Elem,Type>::Add(const CQuaternion &Param)
{
	///////////////////////////////
	m_Value[0]+=Param.m_Value[0];
	m_Value[1]+=Param.m_Value[1];
	m_Value[2]+=Param.m_Value[2];
	m_Value[3]+=Param.m_Value[3];
	////////////////////////////////
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CQuaternion<Type_Elem,Type>::Sub(const CQuaternion &Param)
{
	///////////////////////////////
	m_Value[0]-=Param.m_Value[0];
	m_Value[1]-=Param.m_Value[1];
	m_Value[2]-=Param.m_Value[2];
	m_Value[3]-=Param.m_Value[3];
	////////////////////////////////
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CQuaternion<Type_Elem,Type>::Mult(const CQuaternion &Param)
{
   Type_Elem x = m_Value[0]*Param.m_Value[0]-
				m_Value[1]*Param.m_Value[1]-
				m_Value[2]*Param.m_Value[2]-
				m_Value[3]*Param.m_Value[3];

   m_Value[1] = m_Value[0]*Param.m_Value[1]+ 
				m_Value[1]*Param.m_Value[0];
   m_Value[2] = m_Value[0]*Param.m_Value[2]+
				m_Value[2]*Param.m_Value[0];
   m_Value[3] = m_Value[0]*Param.m_Value[3]+
				m_Value[3]*Param.m_Value[0];

   m_Value[0]=x;
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
void CQuaternion<Type_Elem,Type>::Div(const CQuaternion &Param)
{
   Type_Elem x = m_Value[0]*Param.m_Value[0]-
				m_Value[1]*Param.m_Value[1]-
				m_Value[2]*Param.m_Value[2]-
				m_Value[3]*Param.m_Value[3];

   m_Value[1] = m_Value[0]*Param.m_Value[1]+ 
				m_Value[1]*Param.m_Value[0];
   m_Value[2] = m_Value[0]*Param.m_Value[2]+
				m_Value[2]*Param.m_Value[0];
   m_Value[3] = m_Value[0]*Param.m_Value[3]+
				m_Value[3]*Param.m_Value[0];

   m_Value[0]=x;
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
Type_Elem	CQuaternion<Type_Elem,Type>::norm()	const
{
	return(::sqrt(m_Value[0]*m_Value[0]+
				  m_Value[1]*m_Value[1]+
				  m_Value[2]*m_Value[2]+
				  m_Value[3]*m_Value[3]));
}

template<class Type_Elem,HYPERFONCTION_TYPE Type>
Type_Elem	CQuaternion<Type_Elem,Type>::norm2()	const
{
	return(m_Value[0]*m_Value[0]+
			   m_Value[1]*m_Value[1]+
		       m_Value[2]*m_Value[2]+
		       m_Value[3]*m_Value[3]);
}



#endif
