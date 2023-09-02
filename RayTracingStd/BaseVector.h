/////Etat classe : VALIDE

#ifndef	_CBASEVECTOR
#define _CBASEVECTOR

#include <stdio.h>

template<unsigned short N,class Type_Elem>
class CBaseVector
{
// Construction
public:
	CBaseVector();
	CBaseVector(Type_Elem coord[N]);

	void	SetMin(const CBaseVector<N,Type_Elem> &Param);
	void	SetMax(const CBaseVector<N,Type_Elem> &Param);

//Attributes
public:
	Type_Elem	m_Value[N];

// Implementation
public:
	virtual ~CBaseVector();
};

#ifndef __BORLANDC__

template <unsigned short N,class Type_Elem>
CBaseVector<N,Type_Elem>::CBaseVector<N,Type_Elem>()
{
}

template <unsigned short N,class Type_Elem>
CBaseVector<N,Type_Elem>::CBaseVector<N,Type_Elem>(Type_Elem coord[N])
{
	for(int i=0;i<N;i++)
	{
		m_Value[i]=coord[i];
	}
}


template <unsigned short N,class Type_Elem>
CBaseVector<N,Type_Elem>::~CBaseVector<N,Type_Elem>()
{
}

template <unsigned short N,class Type_Elem>
void	CBaseVector<N,Type_Elem>::SetMin(const CBaseVector<N,Type_Elem> &Param)
{
	for(int i=0;i<N;i++)
	{
		if(m_Value[i]>Param.m_Value[i])
			m_Value[i]=Param.m_Value[i];
	}
}

template <unsigned short N,class Type_Elem>
void	CBaseVector<N,Type_Elem>::SetMax(const CBaseVector<N,Type_Elem> &Param)
{
	for(int i=0;i<N;i++)
	{
		if(m_Value[i]<Param.m_Value[i])
			m_Value[i]=Param.m_Value[i];
	}
}

#endif

#endif
