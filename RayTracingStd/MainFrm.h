// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__FE850D60_CBB7_466F_918F_ADC581AA374D__INCLUDED_)
#define AFX_MAINFRM_H__FE850D60_CBB7_466F_918F_ADC581AA374D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRenderingView;
class CRenderingFrame;
class CIhmInterface;
class CRenderInterface;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_NbProcessors;
	CString	m_Register;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnRegister();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CFractalSheet;
class CRenderStructure;
class CTextureSheet;

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	CMenu				*m_pDefaultMenu;
	CMenu				*m_pNewMenu;
	bool				m_bNewMenu;

	CIhmInterface		*m_pIhmInterface;									//IHM	
	CRenderingFrame		*m_pRenderFrame;
	CRenderingView		*m_pRenderView;		//Vue de rendu courante			//IHM
	CRenderInterface	*m_pTestRender;		//Interface du moteur de rendu	//TRAITEMENT
	CFractalSheet		*m_pdlgFractalSheet;
	CTextureSheet		*m_pdlgTextureSheet;

	CRenderStructure	*m_pRenderStructure;	//Paramètres courants
	CRenderStructure	*m_pRenderStructureComputing;	//Paramètres sélectionnées pour le calcul

	HANDLE				m_FrontalThreadHandle;

	bool				m_MiniMutex;		//sert à gérer les conflits lors de maj ihm

	//temporary variables
private:
	CString				m_TmpPath;
	bool				m_RegisterOk;

public:
	bool				GetRegisterOk()		{return m_RegisterOk;}
	CRenderingView	*	GetCurrentView()	{return m_pRenderView;}
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	void		MajSheets(CRenderStructure*);
	void		AfficheMenuPrincipal();
	void		TestRegister();
	void		TestNoRegister();

	void		CommonOpen(const CString&);
protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

	////Variables d'états
	bool		m_bModeRandom;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMenuFormulaEdit();
	afx_msg void OnRenderingRender();
	afx_msg void OnRenderingRandom();
	afx_msg void OnAppAbout();
	afx_msg void OnClose();
	afx_msg LRESULT OnRandom(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRender(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnRenderFinished(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnStopRender(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMajProperties(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnFileOpenSecond(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnFileOpenExtern(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnFileNewSecond(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSizeView(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnAntiPiratage(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnTestAntiPiratage(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnPostAntiPiratage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnFileNew();
	afx_msg void OnWindowShowhideproperties();
	afx_msg void OnFichierEnregistre();
	afx_msg void OnFileOpen();
	afx_msg LRESULT OnOpenTexture(WPARAM wParam,LPARAM lParam);
	afx_msg void OnAppPreference();
	afx_msg void OnStopRenderMenu();
	afx_msg LRESULT OnSelectOther(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSelectOtherSecond(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
 
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__FE850D60_CBB7_466F_918F_ADC581AA374D__INCLUDED_)
