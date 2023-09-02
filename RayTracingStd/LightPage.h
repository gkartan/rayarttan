#if !defined(AFX_LIGHTPAGE_H__CECE2176_2B4E_4349_ADD3_EA87365C62E7__INCLUDED_)
#define AFX_LIGHTPAGE_H__CECE2176_2B4E_4349_ADD3_EA87365C62E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLightPage dialog
#include "CoordIhm.h"
#include "ColorIhm.h"
#include "FrontalLight.h"
#include "OXColorPickerButton.h"

class CLightPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CLightPage)

// Construction
public:
	CLightPage();
	~CLightPage();

// Dialog Data
	//{{AFX_DATA(CLightPage)
	enum { IDD = IDD_LIGHT_PAGE };
	CComboBox	m_sLightNameCtrl;
	CString	m_sLightType;
	CString	m_sLightName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLightPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	CCoordIhm		m_Position;
	CColorIhm		m_Color;
	CFrontalLight	*m_pLight;

	COXColorPickerButton	m_ColorButton;

	bool			m_bEnable;

public:
	inline		CCoord GetPosition() {return m_Position;}
	inline		CColor GetColor() {return m_Color.ConvertEng();}
	inline		void SetPosition(const CCoord& coord) {m_Position=coord;}
	inline		void SetColor(const CColor& color) {m_Color=color;}

	void				Update(CFrontalLight*);
	void				Update(CBaseLight*);
	void				Update();

	void				ResetList();
	void				InitList();
	void				SetEnableWindow(bool	bEnable)	{m_bEnable=bEnable;}


protected:
	////Gestion affichage des données -- grisage/dégrisage certaines données
	bool		EnablePosition(bool);

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLightPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokLightname();
	afx_msg void OnKillfocusLightcolorb();
	afx_msg void OnKillfocusLightcolorg();
	afx_msg void OnKillfocusLightcolorr();
	afx_msg void OnKillfocusLightposx();
	afx_msg void OnKillfocusLightposy();
	afx_msg void OnKillfocusLightposz();
	afx_msg void OnSelendokLighttype();
	afx_msg void OnButtonLightColor();
	afx_msg void OnLightdelete();
	afx_msg void OnLightadd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTPAGE_H__CECE2176_2B4E_4349_ADD3_EA87365C62E7__INCLUDED_)
