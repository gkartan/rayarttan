// Accueil.cpp : implementation file
//

#include "stdafx.h"
#include "raytracingstd.h"
#include "Accueil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccueil dialog


CAccueil::CAccueil(CWnd* pParent /*=NULL*/)
	: CDialog(CAccueil::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccueil)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAccueil::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccueil)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccueil, CDialog)
	//{{AFX_MSG_MAP(CAccueil)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccueil message handlers
