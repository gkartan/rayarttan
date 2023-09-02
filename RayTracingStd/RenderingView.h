#if !defined(AFX_RENDERINGVIEW_H__46D50C74_7634_411F_BE1B_B7097FC1D811__INCLUDED_)
#define AFX_RENDERINGVIEW_H__46D50C74_7634_411F_BE1B_B7097FC1D811__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenderingView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRenderingView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#pragma warning(disable : 4530)

#include "BaseColor.h"
#include "resource.h"

typedef CBaseColor<unsigned char> BaseColorChar;
class CRenderingView : public CFormView
{
protected:
	CRenderingView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRenderingView)

// Form Data
public:
	//{{AFX_DATA(CRenderingView)
	enum { IDD = IDD_FORMVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	unsigned long	m_Width;
	unsigned long	m_Height;
	CBitmap			m_Bitmap;
	CDC				m_dcMem;
	bool			m_bFirst;
	bool			m_bInit;
	bool			m_bChangeSize;
	OLE_COLOR		m_couleurFond;
	unsigned		m_NbLineComputed;

	///Valeurs temporaires
	unsigned long	m_CurY;
	std::list<BaseColorChar> m_ListColor;

	CString			m_Name;

// Operations
public:
	void	SetColor(unsigned long y,
					 std::list<BaseColorChar>&);

	void	SetSize(unsigned long Width,unsigned long Height);
	void	DessineFond(CDC* pdc);
	void	InitBitmap();

	void	Initialize();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRenderingView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRenderingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	// Generated message map functions
	//{{AFX_MSG(CRenderingView)
	afx_msg LRESULT  OnDisplayPixel(WPARAM wparam,LPARAM lparam);
	afx_msg LRESULT  OnSetSize(WPARAM wparam,LPARAM lparam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENDERINGVIEW_H__46D50C74_7634_411F_BE1B_B7097FC1D811__INCLUDED_)
