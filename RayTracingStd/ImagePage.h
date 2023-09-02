
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CameraPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCameraPage dialog
#include "CoordIhm.h"
#include "BaseImage.h"
#include "RenderStructure.h"

class CImagePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CImagePage)

// Construction
public:
	CImagePage();
	~CImagePage();

// Dialog Data
	//{{AFX_DATA(CImagePage)
	enum { IDD = IDD_IMAGE_PAGE };
	CComboBox	m_RenderTypeCtrl;
	CComboBox	m_ImageHeightCtrl;
	CComboBox	m_ImageWidthCtrl;
	CString	m_sRenderType;
	long	m_ImageWidth;
	long	m_ImageHeight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CImagePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	CBaseImage			*m_pImage;
	CRenderStructure	*m_pRenderStructure;
	bool				m_bEnable;

public:
	void				Update(CBaseImage*,CRenderStructure	*);
	void				SetEnableWindow(bool	bEnable)	{m_bEnable=bEnable;}

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CImagePage)
	afx_msg void OnSelendokImageheight();
	afx_msg void OnSelendokImagewidth();
	afx_msg void OnSelendokRendertype();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
