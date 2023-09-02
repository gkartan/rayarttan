// MainFrm.cpp : implementation of the CMainFrame class
//
#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#pragma warning(disable : 4530)
#pragma warning(disable : 4096)
#pragma warning(disable : 4005)

#include "RenderInterface.h"

#include "stdafx.h"
#include <afxmt.h>
#include "RayTracingStd.h"
#include "IhmInterface.h"

#include "MainFrm.h"
#include "RenderingView.h"
#include "RenderingDoc.h"
 

#define _IHMMESSAGE
#include "IhmConstants.h"

#include "RunRender.h"

#include "RenderingFrame.h"
#include "FractalSheet.h"
#include "TextureSheet.h"
 
#include "fstream.h"

#include "ComputeRegisterKey.h"
#include "RegisterDlg.h"

#include "ConfigDlg.h"

#include "LicenceDlg.h"
#include "ClassicFunctions.h"

#include "SaverWnd.h"

#include "Register.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
extern void InitEnvironnement();
extern CRayTracingStdApp theApp;

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_MENU_FORMULA_EDIT, OnMenuFormulaEdit)
	ON_COMMAND(ID_RENDERING_RENDER, OnRenderingRender)
	ON_COMMAND(ID_RENDERING_ALEA, OnRenderingRandom)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_WM_CLOSE()
	ON_REGISTERED_MESSAGE(MS_RANDOM,OnRandom)
	ON_REGISTERED_MESSAGE(MS_RENDER,OnRender)
	ON_REGISTERED_MESSAGE(MS_RENDER_FINISHED,OnRenderFinished)
	ON_REGISTERED_MESSAGE(MS_STOP_RENDER,OnStopRender)
	ON_REGISTERED_MESSAGE(MS_MAJ_PROPERTIES,OnMajProperties)
	ON_REGISTERED_MESSAGE(MS_FILEOPEN,OnFileOpenExtern)
	ON_REGISTERED_MESSAGE(MS_FILEOPEN_SECOND,OnFileOpenSecond)
	ON_REGISTERED_MESSAGE(MS_FILENEW_SECOND,OnFileNewSecond)
	ON_REGISTERED_MESSAGE(MS_SIZE_VIEW,OnSizeView)
	ON_REGISTERED_MESSAGE(MS_ANTIPIRATAGE,OnAntiPiratage)
	ON_REGISTERED_MESSAGE(MS_TESTANTIPIRATAGE,OnTestAntiPiratage)
	ON_REGISTERED_MESSAGE(MS_POSTANTIPIRATAGE,OnPostAntiPiratage)
	ON_REGISTERED_MESSAGE(MS_SELECT_OTHER,OnSelectOther)
	ON_REGISTERED_MESSAGE(MS_SELECT_OTHER_SECOND,OnSelectOtherSecond)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_WINDOW_SHOWHIDEPROPERTIES, OnWindowShowhideproperties)
	ON_COMMAND(ID_FICHIER_ENREGISTRE, OnFichierEnregistre)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_REGISTERED_MESSAGE(MS_OPEN_TEXTURE,OnOpenTexture)
	ON_COMMAND(ID_APP_PREFERENCE, OnAppPreference)
	ON_COMMAND(ID_STOP_RENDER, OnStopRenderMenu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destructionunsigned long x,
typedef CBaseColor<unsigned char> BaseColorChar;

CMutex	mutex(FALSE,"IHMMUTEX");

void	  RenderViewSetColor(unsigned long CurY,
							 std::list<BaseColorChar>& ColorOptimise)
{
	///Si on n'est pas en mode console ni en mode screensaver
	if(		!((CRayTracingStdApp*) AfxGetApp())->GetModeConsole()
	   &&	!((CRayTracingStdApp*) AfxGetApp())->GetModeScreenSaver())
	{
		CSingleLock singleLock(&mutex);
		singleLock.Lock();  // Attempt to lock the shared resource

		CMainFrame	*pMainFrame=(CMainFrame*)AfxGetMainWnd();
		if(pMainFrame!=NULL)
		{
			pMainFrame->m_pIhmInterface->SetColor(pMainFrame->GetCurrentView(),CurY,ColorOptimise);
		}

		singleLock.Unlock();
	} else

	//////On est en mode screensaver
	if(((CRayTracingStdApp*) AfxGetApp())->GetModeScreenSaver())
	{

		_FTRACE(_STR("Affichage Ligne %d",CurY));
		CSingleLock singleLock(&mutex);
		singleLock.Lock();  // Attempt to lock the shared resource

		CSaverWnd	*pWnd=(CSaverWnd*)AfxGetMainWnd();
		if(pWnd!=NULL)
		{
			pWnd->SetColor(CurY,ColorOptimise);
		}

		singleLock.Unlock();
	}
}

CMainFrame::CMainFrame()
{
	m_pIhmInterface=new CIhmInterface;
	m_pTestRender=new CRenderInterface;

	CString str;
	str.LoadString(IDS_FRACTAL_TITLE);
	m_pdlgFractalSheet=new CFractalSheet(str);
	str.LoadString(IDS_TEXTURE_TITLE);
	m_pdlgTextureSheet=new CTextureSheet(str);
	m_bModeRandom=false;
	m_FrontalThreadHandle=NULL;
	m_pRenderStructure=NULL;
	m_MiniMutex=true;
	m_RegisterOk=false;
	m_bNewMenu=false;
	m_pNewMenu=NULL;
	m_pDefaultMenu=NULL;
	m_pRenderFrame=NULL;
}

CMainFrame::~CMainFrame()
{
	if(m_pIhmInterface!=NULL)
	{
		delete m_pIhmInterface;
	}
	if(m_pTestRender!=NULL)
	{
		delete m_pTestRender;
	}
	if(m_pdlgFractalSheet!=NULL)
	{
		delete m_pdlgFractalSheet;
	}
	if(m_pdlgTextureSheet!=NULL)
	{
		delete m_pdlgTextureSheet;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_pdlgFractalSheet->Create(this,WS_SYSMENU | WS_POPUP | WS_CAPTION | DS_MODALFRAME );
	m_pdlgTextureSheet->Create(this,WS_SYSMENU | WS_POPUP | WS_CAPTION | DS_MODALFRAME );

	///Hide the windows
	m_pdlgFractalSheet->ShowWindow(FALSE);	
	m_pdlgTextureSheet->ShowWindow(FALSE);


	///Test enregistrement
	TestRegister();

	PostMessage(MS_POSTANTIPIRATAGE,NULL,NULL);

	///Init dse variables
	InitEnvironnement();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

/////***Obsolete
void CMainFrame::OnMenuFormulaEdit() 
{
/*	//Ouverture de la fenêtre d'édition de formule
	CFormulaDlg	Dlg;
	if(Dlg.DoModal()==IDOK)
	{
		CRenderInterface::SetFormula(Dlg.GetFormula());
		double X,Y,Z;
		Dlg.GetRotation(X,Y,Z);
		CRenderInterface::SetRotation(X,Y,Z);
	}*/
}

void CMainFrame::OnRenderingRender() 
{
	OnRender(NULL,NULL);
}

void CMainFrame::OnRenderingRandom() 
{
	OnRandom(NULL,NULL);
	OnRender(NULL,NULL);
}



void CMainFrame::OnClose() 
{
	OnStopRender(NULL,NULL);
	
	CMDIFrameWnd::OnClose();
}

LRESULT CMainFrame::OnRender(WPARAM wParam,LPARAM lParam)
{
	if(m_bModeRandom)
	{
		m_pdlgFractalSheet->Random();
	}

	if(m_pRenderStructure==NULL)
	{
		return 0;
	}

	if(m_FrontalThreadHandle==NULL)
	{
		m_pRenderStructure->SetComputing(true);
		m_pRenderStructureComputing=m_pRenderStructure;
		MajSheets(m_pRenderStructureComputing);

		///********************************************************************
		///Mise à jour des données
		CRenderInterface::pCamera=m_pRenderStructure->GetCamera();
		CRenderInterface::pImage=m_pRenderStructure->GetImage();
		CRenderInterface::pListGeometry=m_pRenderStructure->GetListGeometry();
		CRenderInterface::pListLight=m_pRenderStructure->GetListLight();
		CRenderInterface::pRenderStructure=m_pRenderStructure;
		CRenderInterface::m_bIhm=!m_bModeRandom;
		//*********************************************************************

		//*********************************************************************
		///Stockage de la fenêtre active courante
		CMDIChildWnd *pChild = (CMDIChildWnd *) GetActiveFrame();
		m_pRenderView=(CRenderingView *) pChild->GetActiveView();

		if(m_pRenderView==NULL)
		{
			m_pIhmInterface->OpenView(RENDERVIEW_WND);
			m_pRenderView=(CRenderingView *)m_pIhmInterface->GetPVisu(RENDERVIEW_WND);
		}
		m_pRenderView->Initialize();
		m_pRenderFrame=(CRenderingFrame*) pChild;
		//***********************************************************************


		//***********************************************************************
		////////////////Création du thread frontal de controle
		DWORD	ThreadId;
		m_FrontalThreadHandle = CreateThread(NULL,
											   0,
											   CRunRender::Run,
											   m_pRenderStructure,
											   0,
											   &ThreadId);
		//************************************************************************
	} else {
		CString str;
		str.LoadString(IDS_CURRENT_COMPUTING);
		AfxMessageBox(str);
	}

	return 0;
}

LRESULT CMainFrame::OnRenderFinished(WPARAM wParam,LPARAM lParam)
{
	::CloseHandle(m_FrontalThreadHandle);

	m_FrontalThreadHandle=NULL;

	if(m_pRenderStructureComputing!=NULL)
		m_pRenderStructureComputing->SetComputing(false);

	if(m_bModeRandom)
	{
		//On relance
		PostMessage(MS_RENDER,NULL,NULL);
	}

	if(m_pRenderStructureComputing==m_pRenderStructure)
		MajSheets(m_pRenderStructureComputing);

	m_pRenderFrame=NULL;
	m_pRenderStructureComputing=NULL;

	return 0;
}

LRESULT CMainFrame::OnStopRender(WPARAM wParam,LPARAM lParam)
{
	if(m_FrontalThreadHandle!=NULL)
	{
		if(m_pRenderStructureComputing!=NULL)
			m_pRenderStructureComputing->SetComputing(false);

		CRunRender::TerminateAll();

		TerminateThread(m_FrontalThreadHandle,0);

		::CloseHandle(m_FrontalThreadHandle);

		m_FrontalThreadHandle=NULL;

		Sleep(1000);	//Attendre un peu que les threads se terminent

		if(m_pRenderStructureComputing==m_pRenderStructure)
			MajSheets(m_pRenderStructureComputing);

		//Mise à jour du titre
		if(m_pRenderFrame!=NULL)
		{
			CRenderingDoc * pDoc=(CRenderingDoc *)m_pRenderFrame->GetActiveDocument();
			CString str;
			str.LoadString(IDS_RENDU_ANNULE);
			pDoc->SetTitle(pDoc->GetName()+CString(" - ")+str);
		}

		m_pRenderFrame=NULL;
		m_pRenderStructureComputing=NULL;

	}


	return 0;
}

////////////////////////////////////////////////////////////////
//Stockage des données courantes
//Mise à jour de la fenêtre de propriété
LRESULT CMainFrame::OnMajProperties(WPARAM wParam,LPARAM lParam)
{
	CMDIChildWnd	*pFrame=(CMDIChildWnd	*)(wParam);
	if(pFrame!=NULL)
	{
		if(!::IsWindow(pFrame->m_hWnd)) return 0;

		CRenderingDoc * pDoc=(CRenderingDoc *)pFrame->GetActiveDocument();

		if(pDoc!=NULL)
		{
			m_pRenderStructure=pDoc->GetRenderStructure();

			MajSheets(m_pRenderStructure);
		}
	} else {
		m_pRenderStructure=NULL;
	}
	return 0;
}

///***************************
///*Ouverture de la fenêtre d'édition de texture avec une texture sélectionnée
///*****************************
LRESULT CMainFrame::OnOpenTexture(WPARAM wParam,LPARAM lParam)
{
	CString *pstr=(CString*) wParam;
	CString str(*pstr);
	delete pstr;

	m_pdlgTextureSheet->SelectMaterial(str);
	m_pdlgTextureSheet->ShowWindow(TRUE);

	return 0;
}

///////*************************************************
///////*Nouvelle fractale -> on met les valeurs par défaut
void CMainFrame::OnFileNew() 
{	
	m_MiniMutex=false;
	m_pIhmInterface->OpenView(RENDERVIEW_WND);
	m_pdlgFractalSheet->ShowWindow(TRUE);
	PostMessage(MS_FILENEW_SECOND,NULL,NULL);

	AfficheMenuPrincipal();
}

LRESULT CMainFrame::OnFileNewSecond(WPARAM wParam,LPARAM lParam)
{
	m_pRenderStructure->SetDefault();
	m_MiniMutex=true;
	MajSheets(m_pRenderStructure);
	return 0;
}
///*******************************************************


void CMainFrame::MajSheets(CRenderStructure *pStructure)
{
	if(m_MiniMutex && pStructure!=NULL) //évite d'avoir des maj intempestives
	{
		m_pdlgFractalSheet->Update(pStructure);
		m_pdlgTextureSheet->Update(pStructure,false);
	}
}


LRESULT CMainFrame::OnRandom(WPARAM wParam,LPARAM lParam)
{
	m_bModeRandom=true;

	return 0;
}
////******************************************************************************
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(IDREGISTER, OnRegister)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_NbProcessors = _T("");
	m_Register = _T("");
	//}}AFX_DATA_INIT

	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);

	m_NbProcessors.Format("%d",SystemInfo.dwNumberOfProcessors);

	CMainFrame *pFrame=(CMainFrame*) AfxGetMainWnd();

	if(pFrame->GetRegisterOk())
	{
		m_Register.LoadString(IDS_REGISTER_OK);
	} else {
		m_Register.LoadString(IDS_REGISTER_NOK);
	}
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_NBPROCESSORS, m_NbProcessors);
	DDX_Text(pDX, IDC_ENREGISTRE, m_Register);
	//}}AFX_DATA_MAP
}

void CAboutDlg::OnRegister() 
{
	CRegisterDlg	dlg;
	dlg.DoModal();
}

void CAboutDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/



void CMainFrame::OnAppAbout() 
{
	CAboutDlg	dlg;
	dlg.DoModal();
}


void CMainFrame::OnWindowShowhideproperties() 
{
	m_pdlgFractalSheet->ShowWindow(!m_pdlgFractalSheet->IsWindowVisible());
}

///***********************************************************************
///***********************************************************************
///*****Gestion Sauvegarde/chargement fichier
void CMainFrame::OnFichierEnregistre() 
{
	///Sauvegarde des informations de la fenêtre courante	
	///Boite de dialogue --> nom du fichier de sauvegarde
	CFileDialog	dlg(FALSE,".tan",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"RayArtTan (*.tan) | *.tan");
	dlg.DoModal();

	///Ouverture de la fstream et envoi de la chaine
	ofstream fichier(dlg.GetPathName());

	if(fichier)
	{
		fichier << (*m_pRenderStructure);
	}

	fichier.close();

	////////////Maj des variables
	m_TmpPath=dlg.GetPathName();

	CString Name;
	ExtractName(m_TmpPath,Name);

	if(CRenderInterface::pRenderStructure==m_pRenderStructure)
		CRenderInterface::m_FileName=Name.GetBuffer(Name.GetLength());

	///Le titre
	CMDIChildWnd *pChild=MDIGetActive();
	if(pChild!=NULL) 
	{
		CRenderingDoc *pDoc=(CRenderingDoc *) pChild->GetActiveDocument();
		pDoc->SetName(Name);
		pDoc->SetTitle(Name);
	}
}

#include "FileParser.l.h"
#include "FileParser.h"

void CMainFrame::CommonOpen(const CString &str)
{
	m_MiniMutex=false;
	m_TmpPath=str;

	CString Name;
	ExtractName(m_TmpPath,Name);

	CRenderInterface::m_FileName=Name.GetBuffer(Name.GetLength());

	m_pIhmInterface->OpenView(RENDERVIEW_WND);
	m_pdlgFractalSheet->ShowWindow(TRUE);

	PostMessage(MS_FILEOPEN_SECOND,NULL,NULL);

}

void CMainFrame::OnFileOpen() 
{
	//On va chercher le fichier à ouvrir
	CFileDialog	dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"RayArtTan (*.tan) | *.tan");
	if(dlg.DoModal()==IDOK)
	{
		CommonOpen(dlg.GetPathName());
	}
}

LRESULT CMainFrame::OnFileOpenExtern(WPARAM wParam,LPARAM lParam) 
{
	CommonOpen(*(CString*) wParam);

	delete((CString*) wParam);

	return 0;
}

LRESULT CMainFrame::OnFileOpenSecond(WPARAM wParam,LPARAM lParam)
{

	///Le titre
	CMDIChildWnd *pChild=MDIGetActive();
	if(pChild!=NULL)
	{
		CRenderingDoc * pDoc=(CRenderingDoc *) pChild->GetActiveDocument();

		if(pDoc!=NULL)
		{
			pDoc->SetTitle(CRenderInterface::m_FileName.c_str());
			pDoc->SetName(CRenderInterface::m_FileName.c_str());
		}
	}

	PostMessage(MS_SIZE_VIEW,NULL,NULL);

	//ouverture du fichier et compilation de la structure
	CFileParser Parser;
	CFileLexer *pLexer=Parser.CreateLexer();

	m_pRenderStructure->BuildFrontals();	//init des variables
	Parser.SetRenderStructure(m_pRenderStructure);

	m_MiniMutex=true;


	////Init de l'analyseur lexical avec la chaine
	pLexer->yyin=fopen(m_TmpPath,"r");

	if(pLexer->yyin!=NULL)
	{

		///lancement du parser
		Parser.yyparse();

		fclose(pLexer->yyin);

		if(Parser.GetResult()!=0)
		{
			CString str;
			str.LoadString(IDS_ERROR_PARSINGFILE);

			CString sDisplay;
			sDisplay.Format("%s %d",str,Parser.GetResult());
			AfxMessageBox(sDisplay);
			pChild->PostMessage(WM_CLOSE,NULL,NULL);
			//m_pRenderStructure->SetDefault();
			//MajSheets(m_pRenderStructure);
		} else {
			//Vérification de l'existence d'une caméra --> fichier .tan non vide
			if(m_pRenderStructure->GetFrontalFractal()->GetFractal()!=NULL)
				MajSheets(m_pRenderStructure);
			else {
				CString str;
				str.LoadString(IDS_ERROR_NOFRACTAL);
				AfxMessageBox(str);
				m_pRenderStructure->SetDefault();
				MajSheets(m_pRenderStructure);
			}

			AfficheMenuPrincipal();

		}
	}

	return 0;
}

LRESULT CMainFrame::OnSizeView(WPARAM wParam,LPARAM lParam)
{
	CMDIChildWnd *pChild=MDIGetActive();

	CRenderingDoc * pDoc=(CRenderingDoc *) pChild->GetActiveDocument();

	if(pDoc!=NULL)
	{

		POSITION pos = pDoc->GetFirstViewPosition();
		CRenderingView* pView = (CRenderingView*) pDoc->GetNextView(pos);

		if(pView!=NULL)
			pView->SetSize(m_pRenderStructure->GetImage()->GetWidth(),
						   m_pRenderStructure->GetImage()->GetHeight());
	}

	return 0;
}

LRESULT CMainFrame::OnSelectOther(WPARAM wParam,LPARAM lParam)
{
	m_pRenderStructure=NULL;

	MDINext();

	PostMessage(MS_SELECT_OTHER_SECOND,NULL,NULL);

	return 0;
}

LRESULT CMainFrame::OnSelectOtherSecond(WPARAM wParam,LPARAM lParam)
{
	CMDIChildWnd *pChild=MDIGetActive();
	if(pChild==NULL)
	{
		m_pdlgFractalSheet->ShowWindow(FALSE);
		m_pdlgTextureSheet->ShowWindow(FALSE);

		if(m_pDefaultMenu!=NULL) delete m_pDefaultMenu;

		m_pDefaultMenu=new CMenu;

		m_pDefaultMenu->LoadMenu(IDR_MAINFRAME);

		// Remove and destroy the old menu
		SetMenu(NULL);
		::DestroyMenu(m_hMenuDefault);

		// Add the new menu
		SetMenu(m_pDefaultMenu);

		// Assign default menu
		m_hMenuDefault = m_pDefaultMenu->GetSafeHmenu();  // or m_NewMenu.m_hMenu;

		m_bNewMenu=false;
	}

	return 0;
}

///***********************************************************************
///***********************************************************************
///***********************************************************************

/**********GESTION ENREGISTREMENT***********/
///**********Vérification de l'enregistrement si oui
///**********Stockage des valeurs dans un fichier
///**********Pour vérification à chaque lancement
LRESULT CMainFrame::OnAntiPiratage(WPARAM wParam,LPARAM lParam)
{

	CString	*pName=(CString*) wParam;
	CString *pKey=(CString*) lParam;

	m_RegisterOk=CRegister::Verify(*pName,*pKey);
  
	delete pName;
	delete pKey;

	return 0;
}

LRESULT CMainFrame::OnTestAntiPiratage(WPARAM wParam,LPARAM lParam)
{
	if(m_RegisterOk)
	{
		CString str;
		str.LoadString(IDS_REGISTER_THANK_OK);
		AfxMessageBox(str);
	} else {
		CString str;
		str.LoadString(IDS_REGISTER_ERROR_NOK);
		AfxMessageBox(str);
	}
	return 0;
}

LRESULT CMainFrame::OnPostAntiPiratage(WPARAM wParam,LPARAM lParam)
{
	if(!m_RegisterOk)
	{
		if(!CRegister::TestNoRegister())
			PostMessage(WM_QUIT,NULL,NULL);
	}

	return 0;
}
  
void CMainFrame::TestRegister()
{
	CString *pName=new CString;
	CString *pKey=new CString;

	if(CRegister::TestRegister(*pName,*pKey))
	{
		///Désynchronisation
		PostMessage(MS_ANTIPIRATAGE,(WPARAM) pName,(LPARAM) pKey);
		
	} else {
		m_RegisterOk=false;
	}
}


void CMainFrame::OnAppPreference() 
{
	CConfigDlg	dlg;
	dlg.DoModal();
	InitEnvironnement();
}


void CMainFrame::OnStopRenderMenu() 
{
	OnStopRender(NULL,NULL);	
}

void CMainFrame::AfficheMenuPrincipal()
{ 
   if(!m_bNewMenu)
   {
	   if(m_pNewMenu!=NULL) delete m_pNewMenu;
	
	   m_pNewMenu=new CMenu;

	   m_pNewMenu->LoadMenu(IDR_PRINCIPAL);

	   // Remove and destroy the old menu
	   SetMenu(NULL);
	   ::DestroyMenu(m_hMenuDefault);

	   // Add the new menu
	   SetMenu(m_pNewMenu);

	   // Assign default menu
	   m_hMenuDefault = m_pNewMenu->GetSafeHmenu();  // or m_NewMenu.m_hMenu;

	   m_bNewMenu=true;
   }

}
