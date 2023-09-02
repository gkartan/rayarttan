#pragma warning(disable : 4530)
#pragma warning(disable : 4786)
#pragma warning(disable : 4005)

#include "stdafx.h"
#include "resource.h"
#include <list>
#include "IhmInterface.h"
#include "RenderingDoc.h"
#include "RenderingView.h"
#include "RenderingFrame.h"
#include "IhmConstants.h"

CIhmInterface::CIhmInterface()
{
	InitIhm();
}

CIhmInterface::~CIhmInterface()
{
	m_Template.RemoveAll();
}


void CIhmInterface::InitIhm()
{
	CMultiDocTemplate *pTemplate=new CMultiDocTemplate(
														IDR_RAYTRATYPE,
														RUNTIME_CLASS(CRenderingDoc),
														RUNTIME_CLASS(CRenderingFrame), 
														RUNTIME_CLASS(CRenderingView));

	m_Template.SetAt(RENDERVIEW_WND,pTemplate);

	AfxGetApp()->AddDocTemplate(pTemplate);
}



void CIhmInterface::OpenView(CString NameWindow)
{
	CMultiDocTemplate *pTemplate;

	if(m_Template.Lookup(NameWindow,pTemplate)!=0)
	{
		CDocument* pDocument = pTemplate->CreateNewDocument();
		if (pDocument != NULL)
		{
			//CFrameWnd*	pMainFrame=dynamic_cast<CFrameWnd*>(AfxGetApp()->m_pMainWnd);
			CFrameWnd*	pMainFrame=(CFrameWnd*)(AfxGetApp()->m_pMainWnd);

			CFrameWnd*	pFrame = pTemplate->CreateNewFrame(pDocument,pMainFrame);
			if (pFrame != NULL)
			{
				if (pDocument->OnNewDocument())
				{
					if (pTemplate->GetFirstDocPosition()!=0)
					{
						pTemplate->InitialUpdateFrame(pFrame,pDocument);
					}
				}

			}
		}
	}

}


CView* CIhmInterface::GetCurrentView(CDocument *pDoc)
{
	POSITION Pos=pDoc->GetFirstViewPosition();
	VERIFY(Pos!=NULL);

	if(Pos!=NULL)
	{
		//CView *pView=dynamic_cast<CView *>(pDoc->GetNextView(Pos));
		CView *pView=(CView *)(pDoc->GetNextView(Pos));
		return pView;
	}

	return NULL;

}

void CIhmInterface::CloseView(CString nameWnd)
{
	CView	*pView=GetPVisu(nameWnd);

	if(pView!=NULL)
	{
		CFrameWnd	*pFrame=pView->GetParentFrame();

		if(pFrame!=NULL)
		{
			pFrame->DestroyWindow();
		}
	}
}


CView * CIhmInterface::GetPVisu(CString nameWnd)
{

  		POSITION  pos,posv;
		
		pos=NULL;

		CMultiDocTemplate *pTemplate;
		if(m_Template.Lookup(nameWnd,pTemplate)!=0)
		{
			pos=pTemplate->GetFirstDocPosition(); //un doc une vue

			if (pos!=NULL)
			{
				CDocument * ledoc = pTemplate->GetNextDoc(pos);

				posv= ledoc->GetFirstViewPosition();
				while (posv != NULL)
				   {
					  CView* pView = ledoc->GetNextView(posv);
					  return pView;
					   
				   }   
				
				
			}
		}

		return NULL;
}

bool CIhmInterface::ExisteDoc(CString nameWnd)
{
    POSITION  pos=NULL;
	CMultiDocTemplate *pTemplate;
	if(m_Template.Lookup(nameWnd,pTemplate)!=0)
	{
		pos=pTemplate->GetFirstDocPosition();

		if (pos==NULL) return false;


		return true;
	}

	return false;

}


void	CIhmInterface::SendMessage(UINT num,WPARAM wParam, LPARAM lParam)
{
	POSITION Pos=m_Template.GetStartPosition();

	while(Pos!=NULL)
	{
		CString				nameWnd;
		CMultiDocTemplate*	pTemplate;

		m_Template.GetNextAssoc(Pos,nameWnd,pTemplate);

		CView	*pView=GetPVisu(nameWnd);
		if(pView!=NULL)
		{
			pView->SendMessage(num,wParam,lParam);
		}
	}
}



////////Specific methods//////////////////////
void CIhmInterface::InitControlBar(CString nameWnd)
{
/*	if(nameWnd==PALETTE_WND)
	{
		InitControlBar(&m_Palette,IDD_PALETTE_COULEUR);
	}*/ 
}

void CIhmInterface::ShowControlBar(CString nameWnd)
{												
/*	if(nameWnd==CARTOTOOLBAR_WND)
	{
		ShowControlBar(&m_CartoToolbar,CBRS_ALIGN_TOP);
	} */ 
}

void CIhmInterface::HideControlBar(CString nameWnd)
{												
/*	if(nameWnd==CARTOTOOLBAR_WND)
	{
		HideControlBar(&m_CartoToolbar);
	}*/ 

}

CControlBar*	CIhmInterface::GetControlBar(CString nameWnd)
{
	/*if(nameWnd==CARTOTOOLBAR_WND)
	{
		return(&m_CartoToolbar);
	}*/

	
	return NULL;
}
////////End ofSpecific methods//////////////////////



///////////////Generic methods//////////////////////
void CIhmInterface::InitControlBar(CDialogBar *pCtrlBar,UINT IdCtrl)
{
/*	CString tmp;
   	
	if (!pCtrlBar->Create(AfxGetApp()->m_pMainWnd, IdCtrl,
						 WS_VISIBLE|WS_CHILD|CBRS_ALIGN_ANY|CBRS_TOOLTIPS|CBRS_FLYBY, 
						 IdCtrl))
	{
		TRACE0("Failed to create infobar\n");
		return ;     
	}

	pCtrlBar->EnableDocking(CBRS_ALIGN_ANY);
	
	HideControlBar(pCtrlBar);
	pCtrlBar->SetOwner(&m_IhmMessageWnd);*/
}


void CIhmInterface::HideControlBar(CControlBar *pCtrlBar)
{
	//CFrameWnd	*pFrame=dynamic_cast<CFrameWnd*>(AfxGetApp()->m_pMainWnd);
	CFrameWnd	*pFrame=(CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	VERIFY(pFrame!=NULL);
	if(pFrame!=NULL)
	{
		pFrame->ShowControlBar(pCtrlBar, false,false);
	}
}

void CIhmInterface::ShowControlBar(CControlBar *pCtrlBar,DWORD Style,CControlBar *pCtrlBarNext)
{
	//CFrameWnd	*pFrame=dynamic_cast<CFrameWnd*>(AfxGetApp()->m_pMainWnd);
	CFrameWnd	*pFrame=(CFrameWnd*)(AfxGetApp()->m_pMainWnd);
	VERIFY(pFrame!=NULL);
	if(pFrame!=NULL)
	{
		pFrame->ShowControlBar(pCtrlBar, true,false);

		CRect	*pRect=NULL;
		if(pCtrlBarNext!=NULL)
		{
			pRect=new CRect;
		   pCtrlBarNext->GetWindowRect(pRect);
		}

		switch(Style)
		{
			case CBRS_ALIGN_TOP :
				pFrame->DockControlBar(pCtrlBar,AFX_IDW_DOCKBAR_TOP,pRect);	
				break;

			case CBRS_ALIGN_BOTTOM :
 				pFrame->DockControlBar(pCtrlBar,AFX_IDW_DOCKBAR_BOTTOM,pRect);	
				break;

			case CBRS_ALIGN_LEFT :
 				pFrame->DockControlBar(pCtrlBar,AFX_IDW_DOCKBAR_LEFT,pRect);	
				break;

			case CBRS_ALIGN_RIGHT :
 				pFrame->DockControlBar(pCtrlBar,AFX_IDW_DOCKBAR_RIGHT,pRect);	
				break;
		}

		delete pRect;
	}

}


void CIhmInterface::CreateToolBar(CString nameWnd)
{
/*	if(nameWnd==CARTOTOOLBAR_WND)
	{
		CreateToolBar(&m_CartoToolbar,IDR_TOOLBAR_CA);
		m_CartoToolbar.SetOwner(&m_IhmMessageWnd);
	}*/
}

void CIhmInterface::CreateToolBar(CToolBar *pToolBar,UINT IdToolBar)
{
	if (!pToolBar->Create(AfxGetMainWnd()) ||
		!pToolBar->LoadToolBar(IdToolBar))
	{
		TRACE0("Failed to create toolbar\n");
	}
	pToolBar->SetBarStyle(pToolBar->GetBarStyle() | CBRS_FLYBY|
		CBRS_TOOLTIPS |  CBRS_SIZE_DYNAMIC);

	pToolBar->EnableDocking(CBRS_ALIGN_TOP);

	HideControlBar(pToolBar);

}

void CIhmInterface::HideAll()
{
}

void CIhmInterface::ShowAll()
{
}

void CIhmInterface::SetColor(CView *pView,
							 unsigned long y,
							 std::list<BaseColorChar> &listColor)
{
	if(pView!=NULL)
	{
		CRenderingView	*pRender=(CRenderingView*)pView;

		if(pRender!=NULL)
		{
			pRender->SetColor(y,listColor);
		}
	}
}





