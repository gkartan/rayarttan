// Test.cpp : Defines the class behaviors for the application.
//
#pragma warning(disable : 4530)
#pragma warning(disable : 4005)

#include "RenderInterface.h"

#include "stdafx.h"
#include "RayTracingStd.h"
#include "MainFrm.h"
#include "IhmConstants.h"
#include "Accueil.h"
#include "RunRender.h"
#include "ClassicFunctions.h"
#include "SaverWnd.h"
#include "TraceService.h"
#include "ScreenSaverDlg.h"
#include "Register.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
CRayTracingStdApp theApp;

ENUM_APP_MODE	GetMode() 
{return ((CRayTracingStdApp*)AfxGetApp())->GetMode();}

BEGIN_MESSAGE_MAP(CRayTracingStdApp, CWinApp)
	//{{AFX_MSG_MAP(CRayTracingStdApp)
	ON_REGISTERED_THREAD_MESSAGE(MS_RENDER_FINISHED,OnRenderFinished)
	ON_REGISTERED_THREAD_MESSAGE(MS_PARTIAL_RENDER,OnPartialRender)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestApp construction

CRayTracingStdApp::CRayTracingStdApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestApp object


/////////////////////////////////////////////////////////////////////////////
// CTestApp initialization
#ifdef _DEBUG
static CMemoryState oldstate, newstate, diffstate;
#endif


/////////////////////fonction d'enregistrement
BOOL PutStrToReg(const TCHAR *RegPath, const TCHAR *ValueName, const TCHAR *Value, HKEY hKey)
{
	HKEY l_OpenKey;
	DWORD tmp;
	BOOL l_bResult = FALSE;

	if (ERROR_SUCCESS==RegCreateKeyEx(hKey,RegPath,0,NULL,
	                                REG_OPTION_NON_VOLATILE,KEY_SET_VALUE,NULL,&l_OpenKey,&tmp))
 	{
		DWORD size;
		#ifndef UNICODE 
			size = strlen(Value)+1;
		#else
			size = wcslen(Value)+1;
		#endif
		if (ERROR_SUCCESS==RegSetValueEx(l_OpenKey,ValueName,0,REG_SZ,(BYTE *)Value,size))
			l_bResult = TRUE;
		RegCloseKey(l_OpenKey);
	}

	return l_bResult;
}

void InitEnvironnement()
{
	char sKeyValue[MAX_CHAR_KEYS];
	CString CompletePath("./RayArtTan.ini");

#ifdef _SCREENSAVER	
	GetSystemDirectory(sKeyValue,MAX_CHAR_KEYS);

	CompletePath.Format("%s\\RayArtTan.ini",sKeyValue);
#endif

	GetPrivateProfileString("Configuration","SaveBitmapPath","",sKeyValue,MAX_CHAR_KEYS,CompletePath);
	CRenderInterface::m_InitPath=std::string(sKeyValue);

#ifdef _SCREENSAVER	
	GetPrivateProfileString("ScreenSaver","Path","",sKeyValue,MAX_CHAR_KEYS,CompletePath);
	CRenderInterface::m_ScreenSaverLoadPath=std::string(sKeyValue);

	CString tmp;
	GetPrivateProfileString("ScreenSaver","Save","",sKeyValue,MAX_CHAR_KEYS,CompletePath);
	tmp.Format("%s",sKeyValue);
	if(tmp.CompareNoCase("TRUE")==0)
	{
		CRenderInterface::m_FileSave=true;
	} else {
		CRenderInterface::m_FileSave=false;
	}
#endif
}

#define REG_FILE_DESC    "Fichier de RayArtTan"


bool	CRayTracingStdApp::InitIhm()
{
	#ifdef _DEBUG
	oldstate.Checkpoint();
#endif

	AfxEnableControlContainer();

	//afxMemDF = afxMemDF |  delayFreeMemDF | checkAlwaysMemDF;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	CAccueil	Accueil;
	Accueil.Create(IDD_ACCUEIL,NULL);
	Accueil.ShowWindow(SW_SHOW);
	
	//Attente 
	Sleep(2000);

	///Initialize
	if (m_lpCmdLine[0] == '\0')
	{
		char ExeFileName[256];
		CString lpCmdLine = GetCommandLine();
		strcpy(ExeFileName,LPCTSTR(lpCmdLine));

		PutStrToReg(".tan","","tan_file",HKEY_CLASSES_ROOT);
		PutStrToReg("tan_file","",REG_FILE_DESC,HKEY_CLASSES_ROOT);
		PutStrToReg("tan_file\\DefaultIcon","",CString(ExeFileName)+",0",HKEY_CLASSES_ROOT);
		PutStrToReg("tan_file\\shell\\open\\command","",ExeFileName,HKEY_CLASSES_ROOT);
	}


	CMDIFrameWnd* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create main MDI frame window
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return false;

	pFrame->ShowWindow(SW_SHOW);
	Accueil.SetForegroundWindow();

	Accueil.ShowWindow(SW_HIDE);

	return true;
}

bool CRayTracingStdApp::MatchOption(LPTSTR lpsz, LPTSTR lpszOption)
{
	if (lpsz[0] == '-' || lpsz[0] == '/')
		lpsz++;
	if (lstrcmpi(lpsz, lpszOption) == 0)
		return true;
	return false;
}


BOOL CRayTracingStdApp::InitInstance()
{
	_TRACE_LINKINIT("RayArtTan","RayArtTan");
	_FTRACE("InitInstance","CRayTracingStdApp");

    ParseCommandLine(m_CmdInfo);

#ifdef _SCREENSAVER	
	if(m_CmdInfo.m_bModeScreenSaverConfig ||
	   __argc == 1 || 
	   MatchOption(__argv[1], _T("c"))
	   || MatchOption(__argv[1], _T("p")))
	{
		CScreenSaverDlg dlg;
		dlg.DoModal();

		return FALSE;

	} else

	if(m_CmdInfo.m_bModeScreenSaver ||
	   MatchOption(__argv[1], _T("s")))
	{
		/////Test licence -- en mode screensaver uniquement lorsqu'il se lance
		/////pour un calcul
		CString sName,sKey;
		if(!CRegister::TestRegister(sName,sKey))
				if(!CRegister::TestNoRegister())
					return FALSE;

		m_CmdInfo.m_bModeScreenSaver=true;

		m_Mode=MODE_SCREENSAVER;
		InitEnvironnement();

		CString str;
		if(SearchFileToRender(str))
		{
			ParserAndRender(str);
   
			CSaverWnd* pWnd = new CSaverWnd;
			pWnd->Create();
			m_pMainWnd = (CWnd*) pWnd;
		} else {
			CString str;
			str.LoadString(IDS_ERROR_SCREENSAVER);
			AfxMessageBox(str);
		}

		return TRUE;
	}

#else	
	if(m_CmdInfo.m_bModeConsole)
	{
		m_Mode=MODE_CONSOLE;
		if (!m_CmdInfo.m_sFile.IsEmpty())
		{
			///Ouverture du fichier
			ParserAndRender(m_CmdInfo.m_sFile);

			/////Obligatoire sinon l'application se ferme
			CMainFrame* pFrame = new CMainFrame;
	 		m_pMainWnd = pFrame;
		}

	} else {
		m_Mode=MODE_NORMAL;

		if(InitIhm())
		{

			if (!m_CmdInfo.m_sFile.IsEmpty())
			{
				///Ouverture du fichier
				CString *pstr=new CString(m_CmdInfo.m_sFile);

				m_pMainWnd->PostMessage(MS_FILEOPEN,(WPARAM) pstr,NULL);
			}


			return TRUE;
		}

		return FALSE;
	}
#endif

 
	return FALSE;
}

BOOL CRayTracingStdApp::ExitInstance()
{
		_TRACE_CLOSE();
#ifdef _DEBUG

		oldstate.DumpAllObjectsSince();
		newstate.Checkpoint();
		if( diffstate.Difference( oldstate, newstate ))
		{
			TRACE( "Memory leaked!\n" );
			diffstate.DumpStatistics();
		}
#endif
		return TRUE;
}

#include "FileParser.l.h"
#include "FileParser.h"

bool	CRayTracingStdApp::ParserAndRender(const CString &str)
{	
	_FTRACE("ParserAndRender","CRayTracingStdApp");

	////**********************************************
	////Parsing file
	CFileParser Parser;
	CFileLexer *pLexer=Parser.CreateLexer();

	m_pRenderStructure=new CRenderStructure;
	m_pRenderStructure->BuildFrontals();	//init des variables
	Parser.SetRenderStructure(m_pRenderStructure);

	////Init de l'analyseur lexical avec la chaine
	pLexer->yyin=fopen(str,"r");

	if(pLexer->yyin==NULL) return false;

	///lancement du parser
	Parser.yyparse();

	fclose(pLexer->yyin);

	if(Parser.GetResult()!=0)
	{
		CString str;
		str.LoadString(IDS_ERROR_PARSINGFILE);

		CString sDisplay;
		sDisplay.Format("%s %d",str,Parser.GetResult());

		cout << sDisplay.GetBuffer(sDisplay.GetLength());

	} else {
		//Vérification de l'existence d'une caméra --> fichier .tan non vide
		if(m_pRenderStructure->GetFrontalFractal()->GetFractal()==NULL)
		{
			CString str;
			str.LoadString(IDS_ERROR_NOFRACTAL);

			cout << str.GetBuffer(str.GetLength());

			m_pRenderStructure->SetDefault();
		}
	}
	//**********************************************************

	//*Debut rendering****************************************
	m_pRenderStructure->SetComputing(true);

	///********************************************************************
	///Mise à jour des données
	CRenderInterface::pCamera=m_pRenderStructure->GetCamera();
	CRenderInterface::pImage=m_pRenderStructure->GetImage();
	CRenderInterface::pListGeometry=m_pRenderStructure->GetListGeometry();
	CRenderInterface::pListLight=m_pRenderStructure->GetListLight();
	CRenderInterface::pRenderStructure=m_pRenderStructure;

	CString Name;
	ExtractName(str,Name);
	CRenderInterface::m_FileName=Name.GetBuffer(Name.GetLength());
	//test si on poursuit une image déjà calculé en partie
	if(!CRenderInterface::TestContinue())
	{
		//Image déjà calculée on passe au suivant
		PostThreadMessage(MS_RENDER_FINISHED,NULL,NULL);
		return true;
	}
	//*********************************************************************

	//***********Init IHm
	if(m_pMainWnd!=NULL)
		((CRenderingWnd*) m_pMainWnd)->Init();
	//***********Fin Init Ihm

	//***********************************************************************
	////////////////Création du thread frontal de controle
	DWORD	ThreadId;
	m_FrontalThreadHandle = ::CreateThread(NULL,
										   0,
										   CRunRender::Run,
										   NULL,
										   0,
										   &ThreadId);
	//************************************************************************
	//********************************************************

	return true;
}

bool	CRayTracingStdApp::SearchFileToRender(CString &str)
{
	_FTRACE("SearchFileToRender","CRayTracingStdApp");
	if(!CRenderInterface::m_ScreenSaverLoadPath.empty())
	{
		CString	swildcard;
		swildcard.Format("%s\\*.tan",CRenderInterface::m_ScreenSaverLoadPath.c_str());

		if(m_ListFileToRender.FindFile(swildcard))
		{
			m_bMoreFiles=(m_ListFileToRender.FindNextFile()!=0);
			str=m_ListFileToRender.GetFilePath();
			_TRACE_ERROR(str);
		}
	}

	if(str.IsEmpty())
		return false;
	else
		return true;
}

LRESULT CRayTracingStdApp::OnRenderFinished(WPARAM wParam,LPARAM lParam)
{
	_FTRACE("OnRenderFinished","CRayTracingStdApp");
	//Effacement de la structure
	delete m_pRenderStructure;

	
	if(m_bMoreFiles)
	{
		m_bMoreFiles=(m_ListFileToRender.FindNextFile()!=0);
		CString str;
		str=m_ListFileToRender.GetFilePath();
		_TRACE_ERROR(str);
		ParserAndRender(str);
	} else {
		_TRACE_ERROR("Pas d'affichage");
		//On arrete le rendu
		CString str;
		str.LoadString(IDS_ERROR_SCREENSAVER2);
		AfxMessageBox(str);
		PostThreadMessage(WM_QUIT,NULL,NULL);
	}

	return 0;
}

LRESULT CRayTracingStdApp::OnPartialRender(WPARAM wParam,LPARAM lParam)
{
	_FTRACE("PartialRender","CRayTracingStdApp");

	if(m_FrontalThreadHandle!=NULL)
	{
		CRunRender::TerminateAll();

		TerminateThread(m_FrontalThreadHandle,0);

		::CloseHandle(m_FrontalThreadHandle);

		m_FrontalThreadHandle=NULL;

		//Sauvegarde partielle du fichier
		CRenderInterface::AfterRender(true);

	}

	return 0;
}

//**************************************
CMyCommandLine::CMyCommandLine()
{
	m_bModeConsole=false;
	m_bModeScreenSaver=false;
}

void CMyCommandLine::ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast )
{
	if (lstrcmpi(lpszParam, "console") == 0)
	{
		m_bModeConsole=true;
	} else 
	if(lstrcmpi(lpszParam, "s") == 0)
	{
		m_bModeScreenSaver=true;
	} else
	if(lstrcmpi(lpszParam, "c") == 0)
	{
		m_bModeScreenSaverConfig=true;
	} else
		m_sFile=lpszParam;

}
