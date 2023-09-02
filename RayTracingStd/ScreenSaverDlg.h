#if !defined(AFX_SCREENSAVERDLG_H__C2109A63_1A11_4531_B0B3_AAA12D2E6E44__INCLUDED_)
#define AFX_SCREENSAVERDLG_H__C2109A63_1A11_4531_B0B3_AAA12D2E6E44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScreenSaverDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScreenSaverDlg dialog
#include "HyperLink.h"

class CScreenSaverDlg : public CDialog
{
// Construction
public:
	CScreenSaverDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScreenSaverDlg)
	enum { IDD = IDD_SCREENSAVER_PROP };
	CString	m_strFolderPath;
	CString	m_strFolderPath2;
	BOOL	m_bFileSave;
	CHyperLink	m_HyperLink;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScreenSaverDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScreenSaverDlg)
	afx_msg void OnConfigBrowse();
	afx_msg void OnConfigBrowse2();
	virtual void OnOK();
	afx_msg void OnKillfocusEdFolder();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCREENSAVERDLG_H__C2109A63_1A11_4531_B0B3_AAA12D2E6E44__INCLUDED_)
