#ifndef _TEXTURESHEET
#define _TEXTURESHEET


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TextureGeneralPage.h"
#include "TextureProceduralPage.h"
#include "RenderStructure.h"

class CTextureSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CTextureSheet)

// Construction
public:
	CTextureSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CTextureSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

protected:
	CTextureGeneralPage		*m_pGeneralPage;
	CTextureProceduralPage	*m_pTextureAmbientPage;
	CTextureProceduralPage	*m_pTextureDiffusePage;
	CTextureProceduralPage	*m_pTextureSpecularPage;
	CTextureProceduralPage	*m_pTextureTransparentPage;


	CRenderStructure	*m_pRenderStructure;

// Operations
public:
	void				Update(CRenderStructure*,bool);
	void				AddProceduralPage(ENUM_TYPECOLOR,
										  CTextureProceduralPage*&,
										  CTextureElement *);
	void				RemoveProceduralPage(ENUM_TYPECOLOR type);
	void				SelectMaterial(CString &str);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFractalSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTextureSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextureSheet)
	afx_msg void OnClose();
	//}}AFX_MSG
	LRESULT  OnRemovePage(WPARAM wparam,LPARAM lparam);
	LRESULT  OnAddPage(WPARAM wparam,LPARAM lparam);
	LRESULT	 OnUpdate(WPARAM wparam,LPARAM lparam);

	DECLARE_MESSAGE_MAP()
};

#endif
