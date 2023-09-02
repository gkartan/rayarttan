// LicenceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "raytracingstd.h"
#include "LicenceDlg.h"
#include "RegisterDlg.h"
#include "IhmConstants.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicenceDlg dialog
 
 
CLicenceDlg::CLicenceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLicenceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLicenceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLicenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicenceDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicenceDlg, CDialog)
	//{{AFX_MSG_MAP(CLicenceDlg)
	ON_BN_CLICKED(IDREGISTER, OnRegister)
	ON_REGISTERED_MESSAGE(MS_ANTIPIRATAGE,OnAntiPiratage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicenceDlg message handlers

void CLicenceDlg::OnRegister() 
{
	CRegisterDlg	dlg;
	dlg.DoModal();

	///Attente que l'enregistrement soit testé
	PostMessage(MS_ANTIPIRATAGE,NULL,NULL);
}

LRESULT CLicenceDlg::OnAntiPiratage(WPARAM wParam,LPARAM lParam)
{
/*	CMainFrame *pFrame=(CMainFrame*) AfxGetMainWnd();

	if(!pFrame->GetRegisterOk())
		PostMessage(WM_CLOSE,NULL,NULL);
	else 
	{
		PostMessage(WM_CLOSE,NULL,NULL);
	}*/
	CDialog::OnOK();
		
	return 0;
}
