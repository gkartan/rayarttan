#if !defined(AFX_FRACTALSHEET_H__7B47B463_C471_4F73_9BA0_6AB5890F3FAC__INCLUDED_)
#define AFX_FRACTALSHEET_H__7B47B463_C471_4F73_9BA0_6AB5890F3FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FractalSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFractalSheet
#include "ImagePage.h"
#include "CameraPage.h"
#include "LightPage.h"
#include "FractalPage.h"
#include "RenderStructure.h"

class CFractalSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CFractalSheet)

// Construction
public:
	CFractalSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CFractalSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CButton		m_RenderButton;
	CButton		m_RenderAleaButton;

protected:
	CImagePage			*m_pImagePage;
	CCameraPage			*m_pCameraPage;
	CLightPage			*m_pLightPage;
	CFractalPage		*m_pFractalPage;

	CRenderStructure	*m_pRenderStructure;

// Operations
public:
	void				Update(CRenderStructure*);
	void				Random();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFractalSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFractalSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFractalSheet)
	afx_msg void OnClose();
	//}}AFX_MSG
	void OnRenderButton ();
	void OnRandomButton ();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRACTALSHEET_H__7B47B463_C471_4F73_9BA0_6AB5890F3FAC__INCLUDED_)
