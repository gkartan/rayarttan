// RayTracingStdView.cpp : implementation of the CRayTracingStdView class
//

#include "stdafx.h"
#include "RayTracingStd.h"

#include "RayTracingStdDoc.h"
#include "RayTracingStdView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdView

IMPLEMENT_DYNCREATE(CRayTracingStdView, CView)

BEGIN_MESSAGE_MAP(CRayTracingStdView, CView)
	//{{AFX_MSG_MAP(CRayTracingStdView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdView construction/destruction

CRayTracingStdView::CRayTracingStdView()
{
	// TODO: add construction code here

}

CRayTracingStdView::~CRayTracingStdView()
{
}

BOOL CRayTracingStdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdView drawing

void CRayTracingStdView::OnDraw(CDC* pDC)
{
	CRayTracingStdDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdView printing

BOOL CRayTracingStdView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRayTracingStdView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRayTracingStdView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdView diagnostics

#ifdef _DEBUG
void CRayTracingStdView::AssertValid() const
{
	CView::AssertValid();
}

void CRayTracingStdView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRayTracingStdDoc* CRayTracingStdView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRayTracingStdDoc)));
	return (CRayTracingStdDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRayTracingStdView message handlers
