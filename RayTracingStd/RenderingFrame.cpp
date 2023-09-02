// RenderingFrame.cpp : implementation file
//
#pragma warning(disable : 4530)
#pragma warning(disable : 4005)

#include "stdafx.h"
#include "RayTracingStd.h"
#include "RenderingFrame.h"
#include "IhmConstants.h"
#include "CameraPage.h"
#include "LightPage.h"
#include "FractalPage.h"
#include "RenderingDOc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int WM_DISPLAY_PIXEL;
extern int WM_SETSIZE;

/////////////////////////////////////////////////////////////////////////////
// CRenderingFrame

IMPLEMENT_DYNCREATE(CRenderingFrame, CMDIChildWnd)

CRenderingFrame::CRenderingFrame()
{
}

CRenderingFrame::~CRenderingFrame()
{
}


BEGIN_MESSAGE_MAP(CRenderingFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CRenderingFrame)
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CRenderingFrame::OnClose() 
{
	if(((CRenderingDoc*) GetActiveDocument())->GetRenderStructure()->GetComputing())
	{
		//Envoi d'un message au thread principal
		AfxGetMainWnd()->SendMessage(MS_STOP_RENDER,NULL,NULL);
		//AfxGetMainWnd()->PostMessage(MS_MAJ_PROPERTIES,NULL,NULL);
	}

	//Sélection de la fenêtre suivante
	AfxGetMainWnd()->SendMessage(MS_SELECT_OTHER,NULL,NULL);	
	
	CMDIChildWnd::OnClose();
}

int CRenderingFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyleEx(0,WS_EX_STATICEDGE);
	
	return 0;
}

void CRenderingFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);
	
	if(::IsWindow(m_hWnd))
	{
		///Prévenir la mainframe de mettre à jour 
		///la fenêtre de propriétés
		AfxGetMainWnd()->PostMessage(MS_MAJ_PROPERTIES,(LPARAM) this,NULL);
	}
}
