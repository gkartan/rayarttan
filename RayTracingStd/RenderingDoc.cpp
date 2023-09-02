// RenderingDoc.cpp : implementation file
//
#pragma warning(disable : 4530)
#pragma warning(disable : 4005)

#include "stdafx.h"
#include "RayTracingStd.h"
#include "RenderingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRenderingDoc

IMPLEMENT_DYNCREATE(CRenderingDoc, CDocument)

CRenderingDoc::CRenderingDoc()
{
}

BOOL CRenderingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	return TRUE;
}

CRenderingDoc::~CRenderingDoc()
{
}


BEGIN_MESSAGE_MAP(CRenderingDoc, CDocument)
	//{{AFX_MSG_MAP(CRenderingDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenderingDoc diagnostics

#ifdef _DEBUG
void CRenderingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRenderingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRenderingDoc serialization

void CRenderingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRenderingDoc commands
