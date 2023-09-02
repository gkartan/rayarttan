#if !defined(AFX_LICENCEDLG_H__E66958C6_0D67_4CF1_A093_F71EED79C0B3__INCLUDED_)
#define AFX_LICENCEDLG_H__E66958C6_0D67_4CF1_A093_F71EED79C0B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LicenceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLicenceDlg dialog

class CLicenceDlg : public CDialog
{
// Construction
public:
	CLicenceDlg(CWnd* pParent = NULL);   // standard constructor
 
// Dialog Data
	//{{AFX_DATA(CLicenceDlg)
	enum { IDD = IDD_LICENCE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicenceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLicenceDlg)
	afx_msg void OnRegister();
	afx_msg LRESULT OnAntiPiratage(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LICENCEDLG_H__E66958C6_0D67_4CF1_A093_F71EED79C0B3__INCLUDED_)
