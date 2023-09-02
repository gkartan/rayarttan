// outviewView.h : Schnittstelle der Klasse COutviewView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTVIEWVIEW_H__466F86F5_BEF5_41CC_9DFE_A734A66C3715__INCLUDED_)
#define AFX_OUTVIEWVIEW_H__466F86F5_BEF5_41CC_9DFE_A734A66C3715__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COutviewView : public CEditView
{
protected: // Nur aus Serialisierung erzeugen
	COutviewView();
	DECLARE_DYNCREATE(COutviewView)

// Attribute
public:
			void *			GetDocument		();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(COutviewView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual					~COutviewView	();
#ifdef _DEBUG
	virtual void			AssertValid		() const;
	virtual void			Dump			( CDumpContext&	dc
											) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(COutviewView)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBrush		m_cBgBrush;
	CFont		m_cFont;
};

#ifndef _DEBUG  // Testversion in outviewView.cpp
inline void*  COutviewView::GetDocument()
   { return NULL; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_OUTVIEWVIEW_H__466F86F5_BEF5_41CC_9DFE_A734A66C3715__INCLUDED_)
