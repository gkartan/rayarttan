// FractalSheet.cpp : implementation file
//
#pragma warning(disable : 4530)
#pragma warning(disable : 4005)

#include "stdafx.h"
#include "raytracingstd.h"
#include "FractalSheet.h"
#include "IhmConstants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFractalSheet

IMPLEMENT_DYNAMIC(CFractalSheet, CPropertySheet)

CFractalSheet::CFractalSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pImagePage=new CImagePage;
	m_pCameraPage=new CCameraPage;
	m_pLightPage=new CLightPage;
	m_pFractalPage=new CFractalPage;
	AddPage(m_pImagePage);
	AddPage(m_pCameraPage);
	AddPage(m_pLightPage);
	AddPage(m_pFractalPage);
}

CFractalSheet::CFractalSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pImagePage=new CImagePage;
	m_pCameraPage=new CCameraPage;
	m_pLightPage=new CLightPage;
	m_pFractalPage=new CFractalPage;
	AddPage(m_pImagePage);
	AddPage(m_pCameraPage);
	AddPage(m_pLightPage);
	AddPage(m_pFractalPage);
}

CFractalSheet::~CFractalSheet()
{
	if(m_pImagePage!=NULL)
	{
		delete m_pImagePage;
	}
	if(m_pCameraPage!=NULL)
	{
		delete m_pCameraPage;
	}
	if(m_pLightPage!=NULL)
	{
		delete m_pLightPage;
	}
	if(m_pFractalPage!=NULL)
	{
		delete m_pFractalPage;
	}
}


BEGIN_MESSAGE_MAP(CFractalSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CFractalSheet)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDC_BUTTON_RENDER, OnRenderButton)
	ON_COMMAND(IDC_BUTTON_RANDOM, OnRandomButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFractalSheet message handlers

BOOL CFractalSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
          RECT rc;
          GetWindowRect (&rc);
          // Increase the height of the CPropertySheet by 30
          rc.bottom += 30;
          // Resize the CPropertySheet
          MoveWindow (rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top);
          // Convert to client coordinates
          ScreenToClient (&rc);
          // m_Button is of type CButton and is a member of CMySheet

		  CString str;
		  str.LoadString(IDS_NOMBOUTON_RENDER);
          m_RenderButton.Create (str, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                              CRect (5, rc.bottom-30, 80, rc.bottom-5),
                              this, IDC_BUTTON_RENDER);

          // m_Button is of type CButton and is a member of CMySheet
		  //str.LoadString(IDS_NOMBOUTON_RANDOM);
          //m_RenderAleaButton.Create (str, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
          //                   CRect (110, rc.bottom-30, 185, rc.bottom-5),
          //                    this, IDC_BUTTON_RANDOM);
	
	return bResult;
}

void CFractalSheet::OnRenderButton ()
{
	if(m_pFractalPage->GetRenderOk())
	{
		AfxGetMainWnd()->PostMessage(MS_RENDER,NULL,NULL);
	} else {
		CString str;
		str.LoadString(IDS_ERROR_RENDER);
		AfxMessageBox(str);
	}
} 

void CFractalSheet::OnRandomButton ()
{
	AfxGetMainWnd()->PostMessage(MS_RANDOM,NULL,NULL); //Init le random
	AfxGetMainWnd()->PostMessage(MS_RENDER,NULL,NULL); //lance le premier calcul
} 



void CFractalSheet::Update(CRenderStructure *pRender)
{
	m_pRenderStructure=pRender;

	if(pRender!=NULL)
	{
		m_pImagePage->Update(m_pRenderStructure->GetImage(),m_pRenderStructure);
		m_pCameraPage->Update(m_pRenderStructure->GetFrontalCamera());
		m_pLightPage->Update(m_pRenderStructure->GetFrontalLight());
		m_pFractalPage->Update(m_pRenderStructure->GetFrontalFractal(),
							   m_pRenderStructure->GetFrontalGeometry(),
							   m_pRenderStructure->GetFrontalMaterial());


		if(::IsWindow(m_pImagePage->m_hWnd))
			m_pImagePage->EnableWindow(!pRender->GetComputing());
		else
			m_pImagePage->SetEnableWindow(!pRender->GetComputing());

		if(::IsWindow(m_pCameraPage->m_hWnd))
			m_pCameraPage->EnableWindow(!pRender->GetComputing());
		else
			m_pCameraPage->SetEnableWindow(!pRender->GetComputing());

		if(::IsWindow(m_pLightPage->m_hWnd))
			m_pLightPage->EnableWindow(!pRender->GetComputing());
		else
			m_pLightPage->SetEnableWindow(!pRender->GetComputing());

		if(::IsWindow(m_pFractalPage->m_hWnd))
			m_pFractalPage->EnableWindow(!pRender->GetComputing());
		else
			m_pFractalPage->SetEnableWindow(!pRender->GetComputing());

	} else {
		m_pImagePage->EnableWindow(false);
		m_pCameraPage->EnableWindow(false);
		m_pLightPage->EnableWindow(false);
		m_pFractalPage->EnableWindow(false);
	}
}

void CFractalSheet::OnClose() 
{
	ShowWindow(!IsWindowVisible());	
	//CPropertySheet::OnClose();
}

void CFractalSheet::Random()
{
	m_pFractalPage->Random();
}
