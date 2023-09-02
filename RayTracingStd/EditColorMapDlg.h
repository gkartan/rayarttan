#if !defined(AFX_EDITCOLORMAPDLG_H__15E75F48_9C26_4A71_94D9_0AD3DAA48000__INCLUDED_)
#define AFX_EDITCOLORMAPDLG_H__15E75F48_9C26_4A71_94D9_0AD3DAA48000__INCLUDED_

/////Etat classe : VALIDE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditColorMapDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditColorMapDlg dialog
#include "CoordIhm.h"
#include "ColorIhm.h"
#include "OXColorPickerButton.h"

#define		CONVERT_TO_SLIDER(a)	(a*10)
#define		CONVERT_FROM_SLIDER(a)  (float(a/10.0))

class CEditColorMapDlg : public CDialog
{
// Construction
public:
	CEditColorMapDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditColorMapDlg)
	enum { IDD = IDD_EDIT_COLORMAP };
	CString		m_EditPosition;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditColorMapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	CColorIhm				m_Color;
	COXColorPickerButton	m_BColor;
	float					m_Position;
	bool					m_bModify;

public:
	void	Init(float	Position,const CColor& color,bool);
	void	RetrieveData(float &Position,CColor &color);
 
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditColorMapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnColorMap();
	afx_msg void OnKillfocusEditPosition();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCOLORMAPDLG_H__15E75F48_9C26_4A71_94D9_0AD3DAA48000__INCLUDED_)
