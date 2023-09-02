#include "BaseVector.h"

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

