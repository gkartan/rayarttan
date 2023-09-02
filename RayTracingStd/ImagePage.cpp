// CImagePage.cpp : implementation file
//
#pragma warning(disable : 4530)
#pragma warning(disable : 4005)

#include "stdafx.h"
#include "resource.h"
#include "ImagePage.h"
#include "IhmConstants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCameraPage property page

IMPLEMENT_DYNCREATE(CImagePage, CPropertyPage)

CImagePage::CImagePage() : CPropertyPage(CImagePage::IDD)
{
	//{{AFX_DATA_INIT(CImagePage)
	m_sRenderType = _T("");
	m_ImageWidth = 0;
	m_ImageHeight = 0;
	//}}AFX_DATA_INIT
}

CImagePage::~CImagePage()
{
}

void CImagePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImagePage)
	DDX_Control(pDX, IDC_RENDERTYPE, m_RenderTypeCtrl);
	DDX_Control(pDX, IDC_IMAGEHEIGHT, m_ImageHeightCtrl);
	DDX_Control(pDX, IDC_IMAGEWIDTH, m_ImageWidthCtrl);
	DDX_CBString(pDX, IDC_RENDERTYPE, m_sRenderType);
	DDX_Text(pDX, IDC_IMAGEWIDTH, m_ImageWidth);
	DDX_Text(pDX, IDC_IMAGEHEIGHT, m_ImageHeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImagePage, CPropertyPage)
	//{{AFX_MSG_MAP(CImagePage)
	ON_CBN_SELENDOK(IDC_IMAGEHEIGHT, OnSelendokImageheight)
	ON_CBN_SELENDOK(IDC_IMAGEWIDTH, OnSelendokImagewidth)
	ON_CBN_SELENDOK(IDC_RENDERTYPE, OnSelendokRendertype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


////////////////////////////////////////////////
//Mise à jour IHM 
void CImagePage::Update(CBaseImage *pImage,CRenderStructure	*pRenderStruct)
{
	if(pImage==NULL) return;

	if(::IsWindow(m_hWnd))
	{
		m_ImageWidth=pImage->GetWidth();
		m_ImageHeight=pImage->GetHeight();
		CString	str;
		str.Format("%d",m_ImageWidth);
		m_ImageWidthCtrl.SelectString(0,str);
		str.Format("%d",m_ImageHeight);
		m_ImageHeightCtrl.SelectString(0,str);

		m_RenderTypeCtrl.SetCurSel(pRenderStruct->GetTypeAlgo());

		UpdateData(FALSE);
	}
	m_pImage=pImage;
	m_pRenderStructure=pRenderStruct;
}



void CImagePage::OnSelendokImageheight() 
{
	UpdateData(TRUE);

	if(m_pImage!=NULL)
	{
		m_pImage->SetSize(m_ImageWidth,m_ImageHeight);
		AfxGetMainWnd()->PostMessage(MS_SIZE_VIEW,NULL,NULL);
	}
}

void CImagePage::OnSelendokImagewidth() 
{
	UpdateData(TRUE);

	if(m_pImage!=NULL)
	{
		m_pImage->SetSize(m_ImageWidth,m_ImageHeight);
		AfxGetMainWnd()->PostMessage(MS_SIZE_VIEW,NULL,NULL);
	}
	
}

void CImagePage::OnSelendokRendertype() 
{
	UpdateData(TRUE);
	if(m_pRenderStructure!=NULL)
	{
		m_pRenderStructure->SetTypeAlgo(TYPE_ALGO(m_RenderTypeCtrl.GetCurSel()));
	}
}

BOOL CImagePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	EnableWindow(m_bEnable);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
