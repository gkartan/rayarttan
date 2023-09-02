// outviewView.cpp : Implementierung der Klasse COutviewView
//

#include "stdafx.h"
#include "outviewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutviewView

IMPLEMENT_DYNCREATE(COutviewView, CEditView)

BEGIN_MESSAGE_MAP(COutviewView, CEditView)
	//{{AFX_MSG_MAP(COutviewView)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutviewView Konstruktion/Destruktion

COutviewView::COutviewView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einf�gen,

}

COutviewView::~COutviewView()
{
}

BOOL COutviewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: �ndern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COutviewView Drucken

BOOL COutviewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void COutviewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zus�tzliche Initialisierung vor dem Drucken hier einf�gen
}

void COutviewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einf�gen
}

/////////////////////////////////////////////////////////////////////////////
// COutviewView Diagnose

#ifdef _DEBUG
void COutviewView::AssertValid() const
{
	CEditView::AssertValid();
}

void COutviewView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

void* COutviewView::GetDocument() // Die endg�ltige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	return NULL;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutviewView Nachrichten-Handler

void COutviewView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	GetEditCtrl().SetReadOnly();
}

HBRUSH COutviewView::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkColor(RGB(255,255,255));
	return m_cBgBrush;
}

int COutviewView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_cBgBrush.CreateSolidBrush(RGB(255,255,255));
	m_cFont.CreatePointFont(10,"Courier",GetEditCtrl().GetWindowDC());
	GetEditCtrl().SetFont(&m_cFont);
	return 0;
}


