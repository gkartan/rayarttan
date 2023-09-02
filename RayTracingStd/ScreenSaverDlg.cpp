// ScreenSaverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "raytracingstd.h"
#include "ScreenSaverDlg.h"
#include "ClassicFunctions.h"
#include "IhmConstants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScreenSaverDlg dialog


CScreenSaverDlg::CScreenSaverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScreenSaverDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScreenSaverDlg)
	m_strFolderPath="";
	m_strFolderPath2="";
	m_bFileSave = FALSE;
	//}}AFX_DATA_INIT


	char sKeyValue[MAX_CHAR_KEYS];
	GetSystemDirectory(sKeyValue,MAX_CHAR_KEYS);

	CString CompletePath;
	CompletePath.Format("%s\\RayArtTan.ini",sKeyValue);

	GetPrivateProfileString("ScreenSaver","Path","",sKeyValue,MAX_CHAR_KEYS,CompletePath);
	m_strFolderPath.Format("%s",sKeyValue);

	GetPrivateProfileString("Configuration","SaveBitmapPath","",sKeyValue,MAX_CHAR_KEYS,CompletePath);
	m_strFolderPath2.Format("%s",sKeyValue);

	CString tmp;
	GetPrivateProfileString("ScreenSaver","Save","",sKeyValue,MAX_CHAR_KEYS,CompletePath);
	tmp.Format("%s",sKeyValue);
	if(tmp.CompareNoCase("TRUE")==0)
	{
		m_bFileSave=TRUE;
	}

}


void CScreenSaverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScreenSaverDlg)
	DDX_Text(pDX, IDC_ED_FOLDER, m_strFolderPath);
	DDX_Text(pDX, IDC_ED_FOLDER2, m_strFolderPath2);
	DDX_Check(pDX, IDC_SCREEN_SAVE, m_bFileSave);
	DDX_Control(pDX, IDC_HYPERLINK, m_HyperLink);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScreenSaverDlg, CDialog)
	//{{AFX_MSG_MAP(CScreenSaverDlg)
	ON_BN_CLICKED(ID_GETFOLDER, OnConfigBrowse)
	ON_BN_CLICKED(ID_GETFOLDER2, OnConfigBrowse2)
	ON_EN_KILLFOCUS(IDC_ED_FOLDER, OnKillfocusEdFolder)
	ON_EN_KILLFOCUS(IDC_ED_FOLDER2, OnKillfocusEdFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CConfigDlg message handlers

void CScreenSaverDlg::OnConfigBrowse() 
{
	CString strFolderPath;
	if (GetFolder(&strFolderPath, "Sample of  getting folder.", this->m_hWnd, NULL, m_strFolderPath.GetBuffer(m_strFolderPath.GetLength()))){
		if (!strFolderPath.IsEmpty()){
			m_strFolderPath = strFolderPath;
			UpdateData(FALSE);
		}
	}
}

void CScreenSaverDlg::OnConfigBrowse2() 
{
	CString strFolderPath;
	if (GetFolder(&strFolderPath, "Sample of  getting folder.", this->m_hWnd, NULL, m_strFolderPath2.GetBuffer(m_strFolderPath2.GetLength()))){
		if (!strFolderPath.IsEmpty()){
			m_strFolderPath2 = strFolderPath;
			UpdateData(FALSE);
		}
	}
}

void CScreenSaverDlg::OnOK() 
{
	char sKeyValue[MAX_CHAR_KEYS];
	GetSystemDirectory(sKeyValue,MAX_CHAR_KEYS);

	CString CompletePath;
	CompletePath.Format("%s\\RayArtTan.ini",sKeyValue);

	WritePrivateProfileString("ScreenSaver","Path",m_strFolderPath,CompletePath);
	WritePrivateProfileString("Configuration","SaveBitmapPath",m_strFolderPath2,CompletePath);

	CString strsave;
	if(m_bFileSave)
	{
		strsave="TRUE";
	} else {
		strsave="FALSE";
	}
	WritePrivateProfileString("ScreenSaver","Save",strsave,CompletePath);

	
	CDialog::OnOK();
}

void CScreenSaverDlg::OnKillfocusEdFolder() 
{
	UpdateData(TRUE);
}

BOOL CScreenSaverDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_HyperLink.SetURL(_T("http://rayarttan.mailurl.com"));
	m_HyperLink.SetUnderline(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
