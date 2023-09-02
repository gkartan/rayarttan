// RegisterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "raytracingstd.h"
#include "RegisterDlg.h"
#include "IhmConstants.h"
#include "Constants.h"
#include "Register.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg dialog

 
CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegisterDlg)
	m_Key = _T("");
	m_Name = _T("");
	//}}AFX_DATA_INIT
}


void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegisterDlg)
	DDX_Text(pDX, IDC_REGISTER_KEY, m_Key);
	DDX_Text(pDX, IDC_REGISTER_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialog)
	//{{AFX_MSG_MAP(CRegisterDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg message handlers

void CRegisterDlg::OnOK() 
{
	//Evite le piratage simple consistant en l'attente message fenêtre
	UpdateData(TRUE);

	CString *pName=new CString(m_Name);
	CString *pKey=new CString(m_Key);

#ifndef _SCREENSAVER	
	///a détruire à la réception
	//Envoyer 1 message vers MainFrame pour désynchroniser
	AfxGetMainWnd()->PostMessage(MS_ANTIPIRATAGE,(WPARAM) pName,(LPARAM) pKey);
	AfxGetMainWnd()->PostMessage(MS_TESTANTIPIRATAGE,NULL,NULL);
#else
	if(CRegister::Verify(*pName,*pKey))
	{
		CString str;
		str.LoadString(IDS_REGISTER_THANK_OK);
		AfxMessageBox(str);
	} else {
		CString str;
		str.LoadString(IDS_REGISTER_ERROR_NOK);
		AfxMessageBox(str);
	}

	delete pName;
	delete pKey;
#endif

	//Fermeture de la fenêtre
	CDialog::OnOK();
}

void CRegisterDlg::OnCancel() 
{	
	CDialog::OnCancel();
}

 