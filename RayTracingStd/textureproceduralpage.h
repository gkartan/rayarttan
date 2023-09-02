#if !defined(AFX_TEXTUREPROCEDURALPAGE_H__AC228EC8_574A_476C_BF0A_0CB7FAFB6E94__INCLUDED_)
#define AFX_TEXTUREPROCEDURALPAGE_H__AC228EC8_574A_476C_BF0A_0CB7FAFB6E94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextureProceduralPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextureProceduralPage dialog
#include "CoordIhm.h"
#include "ColorIhm.h"
#include "OXColorPickerButton.h"
#include "FrontalMaterial.h"
#include "listctrlex.h"


class CTextureProceduralPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CTextureProceduralPage)

// Construction
public:
	CTextureProceduralPage();
	CTextureProceduralPage(int Title);
	~CTextureProceduralPage();

// Dialog Data
	//{{AFX_DATA(CTextureProceduralPage)
	enum { IDD = IDD_TEXTURE_PROCEDURAL };
	CComboBox	m_ProcedureCtrl;
	CListCtrlEx	m_ListCtrl;
	CString	m_Procedure;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTextureProceduralPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	ENUM_TYPECOLOR			m_MyType;
	CFrontalMaterial		*m_pMatiere;
	CTextureElement			*m_pTextureElement;

public:
	void	Update(ENUM_TYPECOLOR,
				   CFrontalMaterial	*,
				   CTextureElement	*);
	void	UpdateColorMap();
	bool	GetColorMapSelect(TypeColorMap::iterator&);

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTextureProceduralPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickColormap(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg	void OnInsertcolorColorMap();
	afx_msg	void OnDeletecolorColorMap();
	afx_msg	void OnModifycolorColorMap();
	afx_msg void OnSelendokProcedure();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTUREPROCEDURALPAGE_H__AC228EC8_574A_476C_BF0A_0CB7FAFB6E94__INCLUDED_)
