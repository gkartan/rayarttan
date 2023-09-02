#ifndef _RAYTRACINGAPP
#define _RAYTRACINGAPP

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdApp:
// See RayTracingStd.cpp for the implementation of this class
//
typedef enum {
	MODE_NORMAL=0,
	MODE_CONSOLE,
	MODE_SCREENSAVER
} ENUM_APP_MODE;

class CMyCommandLine : public CCommandLineInfo
{
public:
	CMyCommandLine();

	bool	m_bModeConsole;
	bool	m_bModeScreenSaver;
	bool	m_bModeScreenSaverConfig;

	CString m_sFile;

public:
	virtual void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast );
};

class CRenderStructure;
class CRayTracingStdApp : public CWinApp
{
public:
	CRayTracingStdApp();

	bool	InitIhm();
	bool	ParserAndRender(const CString &str);
	bool	SearchFileToRender(CString &str);
	bool	MatchOption(LPTSTR lpsz, LPTSTR lpszOption);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRayTracingStdApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	//}}AFX_VIRTUAL

	inline CRenderStructure	*GetRenderStructure() {return m_pRenderStructure;};
	inline bool				GetModeConsole()	  {return m_CmdInfo.m_bModeConsole;}
	inline bool				GetModeScreenSaver()  {return m_CmdInfo.m_bModeScreenSaver;}
	inline ENUM_APP_MODE	GetMode()			  {return m_Mode;}
//Variables pour le mode console
private:
	ENUM_APP_MODE		m_Mode;
	CMyCommandLine		m_CmdInfo;
	CRenderStructure	*m_pRenderStructure;	//Paramètres courants
	HANDLE				m_FrontalThreadHandle;
	CFileFind			m_ListFileToRender;
	bool				m_bMoreFiles;


	//{{AFX_MSG(CMainFrame)
	afx_msg LRESULT OnRenderFinished(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnPartialRender(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


#endif