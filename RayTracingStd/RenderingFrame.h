#if !defined(AFX_RENDERINGFRAME_H__20CCA1C1_A59B_46C3_A614_27D768AFF2FC__INCLUDED_)
#define AFX_RENDERINGFRAME_H__20CCA1C1_A59B_46C3_A614_27D768AFF2FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenderingFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRenderingFrame frame

class CRenderingFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CRenderingFrame)
public:
	CRenderingFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRenderingFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRenderingFrame();

	// Generated message map functions
	//{{AFX_MSG(CRenderingFrame)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENDERINGFRAME_H__20CCA1C1_A59B_46C3_A614_27D768AFF2FC__INCLUDED_)
