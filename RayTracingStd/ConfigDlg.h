#if !defined(AFX_CONFIGDLG_H__1F92AFF4_058E_4EC2_A9CB_3744930394B1__INCLUDED_)
#define AFX_CONFIGDLG_H__1F92AFF4_058E_4EC2_A9CB_3744930394B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_PREFERENCE };
	CString	m_strFolderPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	afx_msg void OnConfigBrowse();
	virtual void OnOK();
	afx_msg void OnKillfocusEdFolder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__1F92AFF4_058E_4EC2_A9CB_3744930394B1__INCLUDED_)
