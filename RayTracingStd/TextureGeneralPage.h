#if !defined(AFX_TEXTUREGENERALPAGE_H__CFDDDC7D_4EC5_413D_9D4A_7B921AC44A31__INCLUDED_)
#define AFX_TEXTUREGENERALPAGE_H__CFDDDC7D_4EC5_413D_9D4A_7B921AC44A31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextureGeneralPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextureGeneralPage dialog
#include "CoordIhm.h"
#include "ColorIhm.h"
#include "OXColorPickerButton.h"
#include "FrontalMaterial.h"

class CTextureGeneralPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CTextureGeneralPage)

// Construction
public:
	CTextureGeneralPage();
	~CTextureGeneralPage();

// Dialog Data
	//{{AFX_DATA(CTextureGeneralPage)
	enum { IDD = IDD_TEXTURE_GENERAL };
	CButton	m_BTextTransparent;
	CButton	m_BTextSpecular;
	CButton	m_BTextAmbient;
	CButton	m_BTextDiffuse;
	CComboBox	m_sMatiereNameCtrl;
	CString	m_sMatiereName;
	double	m_PhongSize;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CTextureGeneralPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	CFrontalMaterial		*m_pMatiere;


	CColorIhm				m_ColorDiffuse;
	COXColorPickerButton	m_BColorDiffuse;
	CColorIhm				m_ColorAmbient;
	COXColorPickerButton	m_BColorAmbient;
	CColorIhm				m_ColorSpecular;
	COXColorPickerButton	m_BColorSpecular;
	CColorIhm				m_ColorTransparent;
	COXColorPickerButton	m_BColorTransparent;

// Operations
public:
	inline		CColor GetColorDiffuse() {return m_ColorDiffuse.ConvertEng();}
	inline		CColor GetColorAmbient() {return m_ColorAmbient.ConvertEng();}
	inline		CColor GetColorSpecular() {return m_ColorSpecular.ConvertEng();}
	inline		CColor GetColorTransparent() {return m_ColorTransparent.ConvertEng();}

	inline		void SetColorDiffuse(const CColor& color)  {m_ColorDiffuse=color;}
	inline		void SetColorAmbient(const CColor& color)  {m_ColorAmbient=color;}
	inline		void SetColorSpecular(const CColor& color) {m_ColorSpecular=color;}
	inline		void SetColorTransparent(const CColor& color) {m_ColorTransparent=color;}

	void		Update();
	void		Update(CBaseMatiere*);
	void		Update(CFrontalMaterial*);
	void		InitList();

// Implementation
protected:
	//{{AFX_MSG(CTextureGeneralPage)
	afx_msg void OnButtonColorAmbient();
	afx_msg void OnButtonColorDiffuse();
	afx_msg void OnButtonColorTransparent();
	afx_msg void OnButtonColorSpecular();
	afx_msg void OnSelendokMatierename();
	afx_msg void OnTextdiffuse();
	virtual BOOL OnInitDialog();
	afx_msg void OnTextambient();
	afx_msg void OnTextspecular();
	afx_msg void OnTexttransparent();
	afx_msg void OnKillfocusPhongsize();
	afx_msg void OnTextureSuppr();
	afx_msg void OnKillfocusMatierename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTUREGENERALPAGE_H__CFDDDC7D_4EC5_413D_9D4A_7B921AC44A31__INCLUDED_)
