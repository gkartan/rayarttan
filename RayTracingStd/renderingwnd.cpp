// Fenêtre de rendu dans le cas du mode screensaver de RayArtTan
//

#include "stdafx.h"
#include "renderingwnd.h"
#include "resource.h"
#include "IhmConstants.h"
#include "TraceService.h"
#include "BaseImage.h"
#include "RenderInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

LPCTSTR CRenderingWnd::m_lpszClassName = NULL;

/////////////////////////////////////////////////////////////////////////////
// CDrawWnd

CRenderingWnd::CRenderingWnd(BOOL bAutoDelete)
{
	m_bAutoDelete = bAutoDelete;
	m_bFirst=true;
}

CRenderingWnd::~CRenderingWnd()
{
}


BEGIN_MESSAGE_MAP(CRenderingWnd, CWnd)
	//{{AFX_MSG_MAP(CRenderingWnd)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(WM_DISPLAY_PIXEL,OnDisplayPixel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CRenderingWnd::Init()
{
	m_Width=CRenderInterface::pImage->GetWidth();
	m_Height=CRenderInterface::pImage->GetHeight();
	m_bFirst=true;
	m_dcMem.DeleteDC();
	m_Bitmap.DeleteObject();
}


void CRenderingWnd::Draw(CDC& dc)
{
	
	CRect rect;
	GetClientRect(&rect);

	//DessineFond(pDC);
 
	if(m_bFirst)
	{
		dc.BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&m_dcMem,0,0,BLACKNESS);
		m_dcMem.CreateCompatibleDC(&dc);
		m_Bitmap.CreateCompatibleBitmap(&dc,m_Width,m_Height);
		m_dcMem.SelectObject(&m_Bitmap);
		InitBitmap();
		m_bFirst=false;

	}  else {
		dc.StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&m_dcMem,
					  rect.left,rect.top,m_Width,m_Height,SRCCOPY);
	}

}

void CRenderingWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	Draw(dc);
}

void CRenderingWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
}

int CRenderingWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CRenderingWnd::Create(DWORD dwExStyle, DWORD dwStyle, const RECT& rect,
	CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	Init();

	// Register a class with no cursor
	if (m_lpszClassName == NULL)
	{
		m_lpszClassName = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,
			::LoadCursor(AfxGetResourceHandle(),
			MAKEINTRESOURCE(IDC_NULLCURSOR)));
	}

	// TODO: Add your specialized code here and/or call the base class
	return CreateEx(dwExStyle, m_lpszClassName, _T(""), dwStyle,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		pParentWnd->GetSafeHwnd(), NULL, NULL );
}

void CRenderingWnd::PostNcDestroy()
{
	if (m_bAutoDelete)
		delete this;
}


void CRenderingWnd::SetColor(unsigned long y,
							  std::list<BaseColorChar> &listColor)
{

	//Stockage valeur
	m_CurY=y;
	m_ListColor.clear();
	m_ListColor.swap(listColor);

	//Envoi d'un message au thread principal
	::SendMessage(m_hWnd,WM_DISPLAY_PIXEL,NULL,NULL);
}

LRESULT  CRenderingWnd::OnDisplayPixel(WPARAM wparam,LPARAM lparam)
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

	return 0;
}

void CRenderingWnd::InitBitmap()
{
	BYTE *parray=new BYTE[m_Width*m_Height*4];
	memset(parray,0,m_Width*m_Height*4);

	m_Bitmap.SetBitmapBits(m_Width*m_Height*4,parray);

	delete parray;

	////Si on continue on affiche le fichier déjà calculé
	if(CRenderInterface::m_bContinue)
	{
		for(int i=0;i<=CRenderInterface::m_NbLine;i++)
			for(int j=0;j<m_Width;j++)
				m_dcMem.SetPixel(j,i,RGB(CRenderInterface::pImage->GetRed(j,i),
										 CRenderInterface::pImage->GetGreen(j,i),
										 CRenderInterface::pImage->GetBlue(j,i)));

	}

}