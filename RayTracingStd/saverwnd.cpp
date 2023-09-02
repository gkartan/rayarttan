// Fenêtre utilisé dans le cas ou RayArtTan est en mode ScreenSaver sous Windows
//

#include "stdafx.h"
#include "renderingwnd.h"
#include "saverwnd.h"
#include "ihmconstants.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaverWnd

CSaverWnd::CSaverWnd()
{
	m_ptLast = CPoint(-1, -1);
}

CSaverWnd::~CSaverWnd()
{
}


BEGIN_MESSAGE_MAP(CSaverWnd, CRenderingWnd)
	//{{AFX_MSG_MAP(CSaverWnd)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_WM_NCACTIVATE()
	ON_WM_ACTIVATE()
	ON_WM_ACTIVATEAPP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSaverWnd message handlers

BOOL CSaverWnd::Create()
{
	CRect rect(0, 0, ::GetSystemMetrics(SM_CXSCREEN),
		::GetSystemMetrics(SM_CYSCREEN));

	return CRenderingWnd::Create(WS_EX_TOPMOST, WS_VISIBLE|WS_POPUP, rect, NULL,
		0, NULL);
}

void CSaverWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID == SC_SCREENSAVE) || (nID == SC_CLOSE))
		return;
	CRenderingWnd::OnSysCommand(nID, lParam);
}

void CSaverWnd::OnDestroy()
{
	PostQuitMessage(0);
	CRenderingWnd::OnDestroy();
}

BOOL CSaverWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	SetCursor(NULL);
	return TRUE;
}

BOOL CSaverWnd::OnNcActivate(BOOL bActive)
{
	if (!bActive)
		return FALSE;
	return CRenderingWnd::OnNcActivate(bActive);
}

void CSaverWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if (nState == WA_INACTIVE)
	{
		AfxGetApp()->PostThreadMessage(MS_PARTIAL_RENDER,NULL,NULL);

		PostMessage(WM_CLOSE);
	}
	CRenderingWnd::OnActivate(nState, pWndOther, bMinimized);
}

void CSaverWnd::OnActivateApp(BOOL bActive, HTASK hTask)
{
	if (!bActive)
	{
		AfxGetApp()->PostThreadMessage(MS_PARTIAL_RENDER,NULL,NULL);
		PostMessage(WM_CLOSE);
	}
	CRenderingWnd::OnActivateApp(bActive, hTask);
}

void CSaverWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_ptLast == CPoint(-1,-1))
		m_ptLast = point;
	else if (m_ptLast != point)
	{
		AfxGetApp()->PostThreadMessage(MS_PARTIAL_RENDER,NULL,NULL);
		PostMessage(WM_CLOSE);
	}
	CRenderingWnd::OnMouseMove(nFlags, point);
}

void CSaverWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	AfxGetApp()->PostThreadMessage(MS_PARTIAL_RENDER,NULL,NULL);
	PostMessage(WM_CLOSE);
	CRenderingWnd::OnLButtonDown(nFlags, point);
}

void CSaverWnd::OnMButtonDown(UINT nFlags, CPoint point)
{
	AfxGetApp()->PostThreadMessage(MS_PARTIAL_RENDER,NULL,NULL);
	PostMessage(WM_CLOSE);
	CRenderingWnd::OnMButtonDown(nFlags, point);
}

void CSaverWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	AfxGetApp()->PostThreadMessage(MS_PARTIAL_RENDER,NULL,NULL);
	PostMessage(WM_CLOSE);
	CRenderingWnd::OnRButtonDown(nFlags, point);
}

void CSaverWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	AfxGetApp()->PostThreadMessage(MS_PARTIAL_RENDER,NULL,NULL);
	PostMessage(WM_CLOSE);
	CRenderingWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSaverWnd::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	AfxGetApp()->PostThreadMessage(MS_PARTIAL_RENDER,NULL,NULL);
	PostMessage(WM_CLOSE);
	CRenderingWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CSaverWnd::OnClose() 
{
	//Sauvegarde éventuelle du fichier pour reprise ultérieure
	
	CRenderingWnd::OnClose();
}
