/////Etat classe : VALIDE
#ifndef	_RUNRENDER
#define _RUNRENDER

#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

class CMainFrame;

class CRunRender
{
// Construction
public:
	CRunRender();

// Attributes
protected:

// Operations
public:
	static unsigned long __stdcall Run(void* pFrame);
	static void TerminateAll();

// Implementation
public:
	virtual ~CRunRender();

	// Generated message map functions
protected:
};

#endif
