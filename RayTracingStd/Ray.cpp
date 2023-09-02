#include "stdio.h"
#include "Ray.h"
#include "BaseIntersection.h"
#include "BaseGeometry.h"
#include "BaseLight.h"
#include "Constants.h"
#include "TraceService.h"

CRay::CRay()
{
	m_bDestroyList=true;
	m_bIsMonochrom=false;
}

CRay::CRay(const CRay &Ray)
{
	m_Coord=Ray.m_Coord;
	m_Direction=Ray.m_Direction;
	m_ListIntersection=Ray.m_ListIntersection;
	m_bDestroyList=false; //C'est une copie d'une autre liste d'intersection
	m_bIsMonochrom=false;
}

CRay::CRay(const CCoord &coord,
		   const CVector &vect)
{
	m_Coord=coord;
	m_Direction=vect;
	m_Direction.Normalize();
	m_bIsMonochrom=false;
	m_bDestroyList=true;
}

CRay::CRay(const CCoord &coord,
		   const CVector &vect,
		   char	 WaveLength)
{
	m_Coord=coord;
	m_Direction=vect;
	m_Direction.Normalize();
	m_bIsMonochrom=true;
	m_PrimaryColor=WaveLength;
	m_bDestroyList=true;
}


CRay::~CRay()
{
	if(m_bDestroyList)
		m_ListIntersection.RemoveAll();

}

/////Copie sans la liste d'intersection
void	CRay::SetRayClear(const CRay &Ray)
{
	m_Coord=Ray.m_Coord;
	m_Direction=Ray.m_Direction;
	m_bDestroyList=false; //C'est une copie d'une autre liste d'intersection
	m_bIsMonochrom=Ray.m_bIsMonochrom;
	m_PrimaryColor=Ray.m_PrimaryColor;
}


CRay&	CRay::operator=(const CRay	&Origin)
{
	m_Coord=Origin.m_Coord;
	m_Direction=Origin.m_Direction;
	m_ListIntersection=Origin.m_ListIntersection;
	m_bDestroyList=false; //C'est une copie d'une autre liste d'intersection
	m_bIsMonochrom=Origin.m_bIsMonochrom;
	m_PrimaryColor=Origin.m_PrimaryColor;

	return (*this);
}

bool	CRay::AddIntersect(CBaseIntersection *pIntersect)
{
	//_FTRACE("AddIntersect","CRay");
	if(pIntersect->GetDistance()>pIntersect->GetDistanceTolerance())
	{
		m_ListIntersection.Add(pIntersect);

		return true;
	} else {
		delete pIntersect; //effacement de l'intersection
	}

	return false;
}

bool CRay::Intersections(TypeVectorGeometry &ListGeometry)
{
	// Il n'y a pas d'intersection au depart
	//m_ListIntersection.clear();
	
	// Pour chaque objet 3D
	TypeVectorGeometry::iterator	theIterator;
	
	for(theIterator=ListGeometry.begin();
		theIterator<ListGeometry.end();
		theIterator++)
		{
			(*theIterator)->Intersection(*this);
		}
		  
	///On tri les intersections
	m_ListIntersection.Sort();
	return IsIntersection();
}


/////////////////////////////////////////////////////
///Enlève les intersections dont la distance à l'origine
///du rayon est supérieur à la longueur du rayon
///ce sont des fausses intersections!!!
bool	CRay::FilterDist(double Distance)
{
	m_ListIntersection.FilterDistSup(Distance);

	return IsIntersection();
}