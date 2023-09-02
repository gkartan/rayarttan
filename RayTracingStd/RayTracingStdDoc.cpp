// RayTracingStdDoc.cpp : implementation of the CRayTracingStdDoc class
//
#include "stdafx.h"
#include "RayTracingStd.h"

#include "RayTracingStdDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdDoc

IMPLEMENT_DYNCREATE(CRayTracingStdDoc, CDocument)

BEGIN_MESSAGE_MAP(CRayTracingStdDoc, CDocument)
	//{{AFX_MSG_MAP(CRayTracingStdDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdDoc construction/destruction

CRayTracingStdDoc::CRayTracingStdDoc()
{
	// TODO: add one-time construction code here

}

CRayTracingStdDoc::~CRayTracingStdDoc()
{
}

BOOL CRayTracingStdDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdDoc serialization

void CRayTracingStdDoc::Serialize(CArchive& ar)
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
// CRayTracingStdDoc diagnostics

#ifdef _DEBUG
void CRayTracingStdDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRayTracingStdDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdDoc commands
