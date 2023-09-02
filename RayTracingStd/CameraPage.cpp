// CameraPage.cpp : implementation file
//
#pragma warning(disable : 4530)

#include "stdafx.h"
#include "resource.h"
#include "CameraPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCameraPage property page

IMPLEMENT_DYNCREATE(CCameraPage, CPropertyPage)

CCameraPage::CCameraPage() : CPropertyPage(CCameraPage::IDD)
{
	//{{AFX_DATA_INIT(CCameraPage)
	m_sCameraType = _T("");
	m_IhmFocal = 0.0;
	m_IhmWidth = 0.0;
	m_IhmHeight = 0.0;
	//}}AFX_DATA_INIT
	m_pCamera=NULL;
}

CCameraPage::~CCameraPage()
{
}

void CCameraPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameraPage)
	DDX_Control(pDX, IDC_CAMTYPE, m_sCameraTypeCtrl);
	DDX_CBString(pDX, IDC_CAMTYPE, m_sCameraType);
	DDX_Text(pDX, IDC_FOCALEVALUE, m_IhmFocal);
	DDX_Text(pDX, IDC_SCREENWIDTH, m_IhmWidth);
	DDX_Text(pDX, IDC_SCREENHEIGHT, m_IhmHeight);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_CAMPOSX, m_Position.GetRefX());
	DDX_Text(pDX, IDC_CAMPOSY, m_Position.GetRefY());
	DDX_Text(pDX, IDC_CAMPOSZ, m_Position.GetRefZ());
	DDX_Text(pDX, IDC_CAMLOOKX, m_LookAt.GetRefX());
	DDX_Text(pDX, IDC_CAMLOOKY, m_LookAt.GetRefY());
	DDX_Text(pDX, IDC_CAMLOOKZ, m_LookAt.GetRefZ());
	DDX_Text(pDX, IDC_CAMTOPX, m_Up.GetRefX());
	DDX_Text(pDX, IDC_CAMTOPY, m_Up.GetRefY());
	DDX_Text(pDX, IDC_CAMTOPZ, m_Up.GetRefZ());

	DDX_Text(pDX, IDC_FOCALEVALUE,m_IhmFocal);
	DDX_Text(pDX, IDC_SCREENWIDTH,m_IhmWidth);
	DDX_Text(pDX, IDC_SCREENHEIGHT,m_IhmHeight);
}


BEGIN_MESSAGE_MAP(CCameraPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCameraPage)
	ON_EN_KILLFOCUS(IDC_CAMPOSX, OnKillfocusCamposx)
	ON_EN_KILLFOCUS(IDC_CAMPOSY, OnKillfocusCamposy)
	ON_EN_KILLFOCUS(IDC_CAMPOSZ, OnKillfocusCamposz)
	ON_EN_KILLFOCUS(IDC_CAMLOOKX, OnKillfocusCamlookx)
	ON_EN_KILLFOCUS(IDC_CAMLOOKY, OnKillfocusCamlooky)
	ON_EN_KILLFOCUS(IDC_CAMLOOKZ, OnKillfocusCamlookz)
	ON_EN_KILLFOCUS(IDC_CAMTOPX, OnKillfocusCamupx)
	ON_EN_KILLFOCUS(IDC_CAMTOPY, OnKillfocusCamupy)
	ON_EN_KILLFOCUS(IDC_CAMTOPZ, OnKillfocusCamupz)
	ON_CBN_SELENDOK(IDC_CAMTYPE, OnSelendokCamtype)
	ON_EN_KILLFOCUS(IDC_FOCALEVALUE, OnKillfocusFocalevalue)
	ON_EN_KILLFOCUS(IDC_SCREENHEIGHT, OnKillfocusScreenheight)
	ON_EN_KILLFOCUS(IDC_SCREENWIDTH, OnKillfocusScreenwidth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameraPage message handlers

void CCameraPage::OnKillfocusCamposx() 
{
	Update();
}

void CCameraPage::OnKillfocusCamposy() 
{
	Update();
}

void CCameraPage::OnKillfocusCamposz() 
{
	Update();
}

void CCameraPage::OnKillfocusCamlookx() 
{
	Update();
}

void CCameraPage::OnKillfocusCamlooky() 
{
	Update();
}

void CCameraPage::OnKillfocusCamlookz() 
{
	Update();
}

void CCameraPage::OnKillfocusCamupx() 
{
	Update();
}

void CCameraPage::OnKillfocusCamupy() 
{
	Update();
}

void CCameraPage::OnKillfocusCamupz() 
{
	Update();
}

void CCameraPage::OnKillfocusFocalevalue() 
{
	Update();	
}

void CCameraPage::OnKillfocusScreenheight() 
{
	Update();	
}

void CCameraPage::OnKillfocusScreenwidth() 
{
	Update();	
}


BOOL CCameraPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	if(m_pCamera!=NULL)
		Update(m_pCamera);
	
	UpdateData(FALSE);

	EnableWindow(m_bEnable);
	
	return TRUE;                
}

////////////////////////////////////////////////
//Mise à jour IHM 
void CCameraPage::Update(CFrontalCamera *pCamera)
{
	if(pCamera==NULL) return;

	m_pCamera=pCamera;

	if(::IsWindow(m_hWnd))
	{
		EnableWindow(true);
		SetPosition(pCamera->GetCenter());
		SetLookAt(pCamera->GetLookAt());
		SetUp(pCamera->GetCamera()->GetTop());
		m_IhmFocal=pCamera->GetCamera()->GetFocal();
		m_IhmWidth=pCamera->GetCamera()->GetWidth();
		m_IhmHeight=pCamera->GetCamera()->GetHeight();

		m_sCameraType=pCamera->GetType().c_str();

		UpdateData(FALSE);

		EnableWindows();
	}
}

void CCameraPage::Update()
{
	std::string OldValue=m_sCameraType;
	UpdateData(TRUE);

	if(m_pCamera!=NULL)
	{
		m_pCamera->SetCenter(GetPosition());
		m_pCamera->SetLookAt(GetLookAt());
		m_pCamera->GetCamera()->SetUp(CVector(GetUp()));
		m_pCamera->SetWidth(m_IhmWidth);
		m_pCamera->SetHeight(m_IhmHeight);
		m_pCamera->GetCamera()->SetFocal(m_IhmFocal);

		if(OldValue.compare(m_sCameraType)!=0)
		{
			m_pCamera->ChangeType(std::string(m_sCameraType));
		}

		EnableWindows();

	}
}


void CCameraPage::OnSelendokCamtype() 
{
	Update();	
}

void		CCameraPage::EnableWindows()
{
	std::string sType(m_pCamera->GetType());
	if(sType.compare(std::string("perspective"))==0)
	{
		GetDlgItem(IDC_FOCALEVALUE)->EnableWindow(TRUE);
	} else {
		GetDlgItem(IDC_FOCALEVALUE)->EnableWindow(FALSE);
	}

}


