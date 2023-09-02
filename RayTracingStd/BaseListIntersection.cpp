#pragma warning(disable : 4530)

#include <algorithm>
#include "BaseListIntersection.h"
#include "BaseMatiere.h"

double CBaseListIntersection::m_FilterDist=0;	

CBaseListIntersection::CBaseListIntersection()
{
	m_NbElements=0;
}

CBaseListIntersection::~CBaseListIntersection()
{
	m_ListIntersection.clear();
}

void CBaseListIntersection::RemoveAll()
{
	TypeVectorIntersection::iterator	theIterator;
	for(theIterator=m_ListIntersection.begin();
	    theIterator!=m_ListIntersection.end();
		theIterator++)
		{
			if((*theIterator)!=NULL)
				delete (*theIterator);
		}
	m_ListIntersection.clear();
}

void CBaseListIntersection::Add(CBaseIntersection *pIntersect)
{
	m_ListIntersection.push_back(pIntersect);
	m_NbElements++;
}

/////////////////////////////////////////////////////////////////
////Tri de la liste des intersections en fonction de la distance
bool CBaseListIntersection::OperatorPrec(const CBaseIntersection *Param1,
										 const CBaseIntersection *Param2)
{
	return Param1->GetDistance()<Param2->GetDistance();
}

bool CBaseListIntersection::OperatorDistSup(const CBaseIntersection *Param1)
{
	return Param1->GetDistance()>m_FilterDist;
}

bool CBaseListIntersection::OperatorDistInf(const CBaseIntersection *Param1)
{
	return Param1->GetDistance()<=m_FilterDist;
}

void CBaseListIntersection::Sort()
{
	std::sort(m_ListIntersection.begin(),
			  m_ListIntersection.end(),
			  CBaseListIntersection::OperatorPrec);
}

void CBaseListIntersection::FilterDistSup(double Dist)
{
	m_FilterDist=Dist;
	TypeVectorIntersection::iterator last;
	last=std::remove_if(m_ListIntersection.begin(),
						m_ListIntersection.end(),
						CBaseListIntersection::OperatorDistSup);

	m_NbElements=m_NbElements-(m_ListIntersection.end()-last);

}

void CBaseListIntersection::FilterDistInf(double Dist)
{
	m_FilterDist=Dist;
	TypeVectorIntersection::iterator last;

	last=std::remove_if(m_ListIntersection.begin(),
				   m_ListIntersection.end(),
				   CBaseListIntersection::OperatorDistInf);

	m_NbElements=m_NbElements-(m_ListIntersection.end()-last);

}

CColor	CBaseListIntersection::MultColorTransp(CColor &Param1,
											   const CBaseIntersection *Param2)
{
	return(Param1*Param2->GetMatiere()->GetColorTransparent());
}

/////////////////////////////////////////////////////////////////
///Opérateurs
CBaseIntersection* CBaseListIntersection::operator[] (long Index)
{
	return m_ListIntersection[Index];
}


CColor	CBaseListIntersection::GetColorResult()
{
	return(Accumulate(CColor(1,1,1),CBaseListIntersection::MultColorTransp));
}

