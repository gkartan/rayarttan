/////Etat classe : VALIDE
#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#ifndef _BASEFILEMANAGER
#define _BASEFILEMANAGER

#include "Color.h"
#include <mtl\matrix.h>

/////////////////////A REVOIR

//dense matrix 
typedef mtl::matrix<CBaseColor<unsigned char>*>::type ColorMatrix;


class CBaseFileManager
{
// Construction
public:
	CBaseFileManager();

// Attributes
protected:
	FILE*	m_phandle;
	char*	m_name;
	int		m_mode;
	long	m_Height;
	long	m_Width;
	ColorMatrix	m_Image;


// Operations
public:
	virtual	bool	Write()=0;

	void Redimensionner(int l,int h);
	void Copy(ColorMatrix& matrix);

	void SetName(const char *name) {m_name=new char[strlen(name)+1];strcpy(m_name,name);}


// Implementation
public:
	virtual ~CBaseFileManager();

	// Generated message map functions
protected:
};


#endif
