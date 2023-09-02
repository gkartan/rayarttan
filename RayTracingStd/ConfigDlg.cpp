// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "raytracingstd.h"
#include "ConfigDlg.h"
#include "IhmConstants.h"
#include "ClassicFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_strFolderPath = _T("");
	//}}AFX_DATA_INIT

	char sKeyValue[MAX_CHAR_KEYS];
	GetPrivateProfileString("Configuration","SaveBitmapPath","",sKeyValue,MAX_CHAR_KEYS,"./RayArtTan.ini");
	m_strFolderPath.Format("%s",sKeyValue);
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Text(pDX, IDC_ED_FOLDER, m_strFolderPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_BN_CLICKED(ID_GETFOLDER, OnConfigBrowse)
	ON_EN_KILLFOCUS(IDC_ED_FOLDER, OnKillfocusEdFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

void CConfigDlg::OnConfigBrowse() 
{
	CString strFolderPath;
	if (GetFolder(&strFolderPath, "Sample of  getting folder.", this->m_hWnd, NULL, m_strFolderPath.GetBuffer(m_strFolderPath.GetLength()))){
		if (!strFolderPath.IsEmpty()){
			m_strFolderPath = strFolderPath;
			UpdateData(FALSE);
		}
	}
}




void CConfigDlg::OnOK() 
{
	WritePrivateProfileString("Configuration","SaveBitmapPath",m_strFolderPath,"./RayArtTan.ini");
	
	CDialog::OnOK();
}

void CConfigDlg::OnKillfocusEdFolder() 
{
	UpdateData(TRUE);
}
