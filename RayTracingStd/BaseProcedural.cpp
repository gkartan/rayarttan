#pragma warning(disable : 4786)

#include "stdio.h"
#include "BaseProcedural.h"
#include <algorithm>
#include <afxmt.h>
#include "TraceService.h"

CMutex	ProcMutex(FALSE,"PROCMUTEX");


CBaseProcedural::CBaseProcedural()
{
	m_ColorMap[0.0]=CColor(0,0,0);
	m_ColorMap[1.0]=CColor(1,1,1);
	m_NbRef=0;
}

CBaseProcedural::CBaseProcedural(CColor &param)
{
	m_ColorMap[0.0]=CColor(0,0,0);
	m_ColorMap[1.0]=param;
	m_NbRef=0;
}


CBaseProcedural::~CBaseProcedural()
{
}

///***************************************************
///Implémentation classique car algo un peu spéciale
///Je ne voyais pas comment utiliser la stl simplement dans ce cas
///---->A REVOIR ---> peut-être avec equal_range
CColor	CBaseProcedural::GetColorMap(float k) const
{
	if(k<0.0) k=0.0;
	if(k>1.0) k=1.0;

	TypeColorMap::iterator theIterator;
	theIterator=m_ColorMap.begin();
	TypeColorMap::iterator theIteratorNext;
	theIteratorNext=m_ColorMap.begin();

	theIteratorNext++;

	bool bFound=false;
	while(theIteratorNext!=m_ColorMap.end() && !bFound)
	{
		if((*theIterator).first<=k &&
		   (*theIteratorNext).first>=k)
		{
			bFound=true;
			break;
		}	
		theIterator++;
		theIteratorNext++;
	}

	double I1=(*theIterator).first;
	double I2=(*theIteratorNext).first;
	double Rapport=(k-(*theIterator).first)/((*theIteratorNext).first-(*theIterator).first);

	if(!bFound)
	{
		if((*theIterator).first<=k &&
		   (*theIteratorNext).first>=k)
		{
			return ((*theIteratorNext).second*(1.0-Rapport)+(*theIterator).second*Rapport);
		}

		return CColor(0,0,0); ///Not found
	}

	return ((*theIteratorNext).second*(1.0-Rapport)+(*theIterator).second*Rapport);
}


///////
//The procedural contain only one color + black
void	CBaseProcedural::SetColor(const CColor &color)
{
	m_ColorMap.clear();
	m_ColorMap[0.0]=CColor(0,0,0);
	m_ColorMap[1.0]=color;
}

void	CBaseProcedural::SetColor(float Position,const CColor &color)
{
	if(Position<0.0 || Position>1.0) return;

	///On retrouve l'endroit ou il faut insérer
	TypeColorMap::iterator theIterator;
	theIterator=m_ColorMap.begin();

	while(theIterator!=m_ColorMap.end() && (*theIterator).first<Position)
	{
		theIterator++;
	}

	if(theIterator!=m_ColorMap.end())
	{
		//insertion
		theIterator--;
		m_ColorMap.insert(TypeColorMap::value_type(Position,color));
	} else {
		//if(m_ColorMap.size()<2)
		m_ColorMap.insert(TypeColorMap::value_type(Position,color));
	}

}

void	CBaseProcedural::Clear()
{
	m_ColorMap.clear();
}

void	CBaseProcedural::AddRef()	
{
	CSingleLock singleLock(&ProcMutex);
	singleLock.Lock();  // Attempt to lock the shared resource

	m_NbRef++;

	singleLock.Unlock();
}
void	CBaseProcedural::Release()
{
	CSingleLock singleLock(&ProcMutex);
	singleLock.Lock();  // Attempt to lock the shared resource

	m_NbRef--;
	if(m_NbRef<=0) delete(this);

	singleLock.Unlock();
}

void CBaseProcedural::GetOuputStream(ostream &o)
{
	o	<<	"\n\t\t\t\tcolor_map\n\t\t\t\t{\n";

	TypeColorMap::iterator theIterator;
	for(theIterator=m_ColorMap.begin();
		theIterator!=m_ColorMap.end();
		theIterator++)
		{
			o << "\t\t\t\t\t"	<<	"[ " << (*theIterator).first << " " 
				<< (*theIterator).second << " ]\n";
		}

	o	<<	"\n\t\t\t\t}\n";
}