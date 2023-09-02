// RenderingView.cpp : implementation file
//
#pragma warning(disable : 4530)
#pragma warning(disable : 4005)

#include "stdafx.h"
#include <list>
#include "RayTracingStd.h"
#include "RenderingView.h"
#include "RenderingDoc.h"
#include "IhmConstants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRenderingView

IMPLEMENT_DYNCREATE(CRenderingView, CFormView)

CRenderingView::CRenderingView()
	: CFormView(CRenderingView::IDD)
{
	m_bFirst=true;
	m_bInit=false;
	m_bChangeSize=false;
	m_Width=800;
	m_Height=600;
	m_CurY=0;
	m_couleurFond=0;
	m_NbLineComputed=0;

	//{{AFX_DATA_INIT(CRenderingView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CRenderingView::~CRenderingView()
{
}

void CRenderingView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRenderingView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CRenderingView::SetColor(unsigned long y,
							  std::list<BaseColorChar> &listColor)
{

	//Stockage valeur
	m_CurY=y;
	m_ListColor.clear();
	m_ListColor.swap(listColor);

	//Envoi d'un message au thread principal
	::SendMessage(m_hWnd,WM_DISPLAY_PIXEL,NULL,NULL);
}

void	CRenderingView::SetSize(unsigned long Width,unsigned long Height)
{
	CRect rect;
	GetClientRect(&rect);

	m_Width=Width;
	m_Height=Height;

	m_bChangeSize=true;

	//Envoi d'un message au thread principal
	::SendMessage(m_hWnd,WM_SETSIZE,NULL,NULL);

	GetParent()->MoveWindow(rect.left,rect.top,
			   rect.left+m_Width+13,
			   rect.top+m_Height+32,TRUE);

}

LRESULT  CRenderingView::OnSetSize(WPARAM wparam,LPARAM lparam)
{
	CRect rect;
	GetClientRect(rect);

	SetWindowPos(&wndTop,rect.left,rect.top,rect.left+m_Width,rect.top+m_Height,SWP_SHOWWINDOW);

	return 0;

}

LRESULT  CRenderingView::OnDisplayPixel(WPARAM wparam,LPARAM lparam)
{
	int CurX=0;
	for(std::list<BaseColorChar>::iterator i=m_ListColor.begin();
		i!=m_ListColor.end();i++)
	{
		m_dcMem.SetPixel(CurX,m_CurY,RGB((*i).GetRed(),
							(*i).GetGreen(),
							(*i).GetBlue()));

		CurX++;
	}

	//On invalide à chaque fin de ligne
	Invalidate(FALSE);

	m_NbLineComputed+=1;

	CString	str;
	//str.Format("%d %% complete",long((float(m_CurY)/float(m_Height-1))*100));
	long PourCen=long((float(m_NbLineComputed)/float(m_Height-1))*100);
	if(PourCen>100) PourCen=100;
	str.Format("- %d %% complete",PourCen);
	GetDocument()->SetTitle(((CRenderingDoc*)GetDocument())->GetName()+str);

	return 0;
}

BEGIN_MESSAGE_MAP(CRenderingView, CFormView)
	//{{AFX_MSG_MAP(CRenderingView)
	ON_REGISTERED_MESSAGE(WM_DISPLAY_PIXEL,OnDisplayPixel)
	ON_REGISTERED_MESSAGE(WM_SETSIZE,OnSetSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenderingView diagnostics

#ifdef _DEBUG
void CRenderingView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRenderingView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRenderingView message handlers

void CRenderingView::OnInitialUpdate() 
{

	SetSize(m_Width,m_Height);

	CFormView::OnInitialUpdate();
}

void CRenderingView::OnDraw(CDC* pDC) 
{	
	CRect rect;
	GetClientRect(&rect);

	//DessineFond(pDC);

	if(m_bFirst)
	{
		pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&m_dcMem,0,0,BLACKNESS);

		m_dcMem.CreateCompatibleDC(pDC);
		m_Bitmap.CreateCompatibleBitmap(pDC,m_Width,m_Height);
		m_dcMem.SelectObject(&m_Bitmap);
		InitBitmap();
		m_bFirst=false;
	} else
	if(m_bChangeSize)
	{
		pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&m_dcMem,0,0,BLACKNESS);
		m_Bitmap.DeleteObject();
		m_Bitmap.CreateCompatibleBitmap(pDC,m_Width,m_Height);
		m_dcMem.SelectObject(&m_Bitmap);
		InitBitmap();
		m_bChangeSize=false;
	} else
		pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&m_dcMem,0,0,SRCCOPY);
}

void CRenderingView::DessineFond(CDC* pdc)
{
	CRect	rect;
	GetClientRect(&rect);
	CBrush BrushFond;
	BrushFond.CreateSolidBrush(m_couleurFond);

	pdc->FillRect(rect, &BrushFond);
	pdc->SetBkColor(m_couleurFond);

}

void CRenderingView::Initialize()
{
	m_NbLineComputed=0;
}

void CRenderingView::InitBitmap()
{
	BYTE *parray=new BYTE[m_Width*m_Height*4];
	memset(parray,0,m_Width*m_Height*4);

	m_Bitmap.SetBitmapBits(m_Width*m_Height*4,parray);

	delete parray;

}

