// EditColorMapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "raytracingstd.h"
#include "EditColorMapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditColorMapDlg dialog


CEditColorMapDlg::CEditColorMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditColorMapDlg::IDD, pParent)
{
	m_Position=-1;
	m_bModify=false;
	//{{AFX_DATA_INIT(CEditColorMapDlg)
	m_EditPosition = "";
	//}}AFX_DATA_INIT
}


void CEditColorMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditColorMapDlg)
	DDX_Text(pDX, IDC_EDIT_POSITION, m_EditPosition);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COLOR_MAP, m_BColor);
	DDX_ColorPicker(pDX, IDC_COLOR_MAP, m_Color.GetColorRef());

	//*******
	//Maj Pos --- ATTENTION PAS COMPATIBLE UNICODE
	m_Position=float(atof(m_EditPosition.GetBuffer(m_EditPosition.GetLength())));
}


BEGIN_MESSAGE_MAP(CEditColorMapDlg, CDialog)
	//{{AFX_MSG_MAP(CEditColorMapDlg)
	ON_BN_CLICKED(IDC_COLOR_MAP, OnColorMap)
	ON_EN_KILLFOCUS(IDC_EDIT_POSITION, OnKillfocusEditPosition)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditColorMapDlg message handlers
void	CEditColorMapDlg::Init(float	Position,
							   const CColor&	color,
							   bool		Modify)
{
	m_Color=color;
	m_Position=Position;
	m_EditPosition.Format("%.2f",m_Position);
	m_bModify=Modify;

}

void	CEditColorMapDlg::RetrieveData(float &Position,CColor &color)
{
	Position=m_Position;
	color=m_Color.ConvertEng();
}


BOOL CEditColorMapDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if(m_bModify && (m_Position==0 || m_Position==1))
	{
		CWnd *pWnd=GetDlgItem(IDC_EDIT_POSITION);
		pWnd->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CEditColorMapDlg::OnColorMap() 
{
	m_Color.UpdateColorRef(m_BColor.GetColor());
	UpdateData(FALSE);	
}

void CEditColorMapDlg::OnKillfocusEditPosition() 
{
	UpdateData(TRUE);	
}

void CEditColorMapDlg::OnOK() 
{
	UpdateData(TRUE);

	CDialog::OnOK();
}
