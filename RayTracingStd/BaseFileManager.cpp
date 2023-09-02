#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#pragma warning(disable : 4530)

#include <stdio.h>
//#include <mtl\mtl.h>
#include "BaseFileManager.h"

CBaseFileManager::CBaseFileManager()
{
	m_name=NULL;
	m_phandle=NULL;
}

CBaseFileManager::~CBaseFileManager()
{
	if(m_name!=NULL)
		delete m_name;

	if(m_phandle!=NULL)
		delete m_phandle;
}

void CBaseFileManager::Redimensionner(int l,int h)
{
	m_Height=h;
	m_Width=l;

	ColorMatrix map(h,l);

	CBaseColor<unsigned char>	*pcolor=NULL;
	mtl::set_value(map, pcolor);

	m_Image=map;
}


void CBaseFileManager::Copy(ColorMatrix& m)
{
	ColorMatrix	ImageTrans(m_Height,m_Width);

	CBaseColor<unsigned char>	*pcolor=NULL;
	mtl::set_value(ImageTrans, pcolor);

	mtl::transpose(m,ImageTrans);

	ColorMatrix::iterator theIterator;

	theIterator=m_Image.end();
	theIterator--;
	for (ColorMatrix::iterator i = ImageTrans.begin(); i != ImageTrans.end(); ++i) 
	{
		ColorMatrix::OneD::iterator theInnerIterator=(*theIterator).begin();
		for (ColorMatrix::OneD::iterator j = (*i).begin(); j != (*i).end(); ++j) 
		{
			(*theInnerIterator)=*(j);
			theInnerIterator++;
		}
		theIterator--;
	}
}