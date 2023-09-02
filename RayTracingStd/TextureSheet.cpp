// FractalSheet.cpp : implementation file
//
#pragma warning(disable : 4530)
#pragma	warning(disable : 4096) 
#pragma warning(disable : 4005)

#include "stdafx.h"
#include "raytracingstd.h"
#include "TextureSheet.h"
#include "IhmConstants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFractalSheet

IMPLEMENT_DYNAMIC(CTextureSheet, CPropertySheet)

CTextureSheet::CTextureSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_pTextureAmbientPage=NULL;
	m_pTextureDiffusePage=NULL;
	m_pTextureSpecularPage=NULL;
	m_pTextureTransparentPage=NULL;

	m_pGeneralPage=new CTextureGeneralPage;
	AddPage(m_pGeneralPage);
}

CTextureSheet::CTextureSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pTextureAmbientPage=NULL;
	m_pTextureDiffusePage=NULL;
	m_pTextureSpecularPage=NULL;
	m_pTextureTransparentPage=NULL;

	m_pGeneralPage=new CTextureGeneralPage;
	AddPage(m_pGeneralPage);
}

CTextureSheet::~CTextureSheet()
{
	if(m_pGeneralPage!=NULL)
		delete m_pGeneralPage;

	if(m_pTextureAmbientPage!=NULL)
		delete 	m_pTextureAmbientPage;

	if(m_pTextureDiffusePage!=NULL)
		delete m_pTextureDiffusePage;

	if(m_pTextureSpecularPage!=NULL)
		delete m_pTextureSpecularPage;

	if(m_pTextureTransparentPage!=NULL)
		delete m_pTextureTransparentPage;
}


BEGIN_MESSAGE_MAP(CTextureSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CFractalSheet)
	ON_WM_CLOSE()
	ON_REGISTERED_MESSAGE(MS_REMOVE_PAGE,OnRemovePage)
	ON_REGISTERED_MESSAGE(MS_ADD_PAGE,OnAddPage)
	ON_REGISTERED_MESSAGE(MS_UPDATE,OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFractalSheet message handlers

BOOL CTextureSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
		
	return bResult;
}

void CTextureSheet::Update(CRenderStructure *pRender,bool bFromDescendant)
{
	m_pRenderStructure=pRender;

	if(pRender!=NULL)
	{
		CFrontalMaterial	*pFrontal=m_pRenderStructure->GetFrontalMaterial();

		if(pFrontal==NULL) return;

		if(!bFromDescendant)
			m_pGeneralPage->Update(pFrontal);

		if(pFrontal->IsTexture(TYPE_AMBIENT))
		{
			AddProceduralPage(TYPE_AMBIENT,m_pTextureAmbientPage,pFrontal->GetTexture(TYPE_AMBIENT));
		} else {
			if(m_pTextureAmbientPage!=NULL)
				RemoveProceduralPage(TYPE_AMBIENT);
		}
		if(pFrontal->IsTexture(TYPE_DIFFUSE))
		{
			AddProceduralPage(TYPE_DIFFUSE,m_pTextureDiffusePage,pFrontal->GetTexture(TYPE_DIFFUSE));
		} else {
			if(m_pTextureDiffusePage!=NULL)
				RemoveProceduralPage(TYPE_DIFFUSE);
		}
		if(pFrontal->IsTexture(TYPE_SPECULAR))
		{
			AddProceduralPage(TYPE_SPECULAR,m_pTextureSpecularPage,pFrontal->GetTexture(TYPE_SPECULAR));
		} else {
			if(m_pTextureSpecularPage!=NULL)
				RemoveProceduralPage(TYPE_SPECULAR);
		}
		if(pFrontal->IsTexture(TYPE_TRANSPARENT))
		{
			AddProceduralPage(TYPE_TRANSPARENT,m_pTextureTransparentPage,pFrontal->GetTexture(TYPE_TRANSPARENT));
		} else {
			if(m_pTextureTransparentPage!=NULL)
				RemoveProceduralPage(TYPE_TRANSPARENT);
		}

		if(!bFromDescendant)
			m_pGeneralPage->EnableWindow(!pRender->GetComputing());

	} else {
		if(!bFromDescendant)
			m_pGeneralPage->EnableWindow(false);
	}
}

void CTextureSheet::OnClose() 
{
	ShowWindow(!IsWindowVisible());	
	//CPropertySheet::OnClose();
}

void CTextureSheet::AddProceduralPage(ENUM_TYPECOLOR Type,
									  CTextureProceduralPage* &pPage,
									  CTextureElement *pTexture)
{
	if(pPage!=NULL)
	{
		RemovePage(pPage);
		delete pPage;
	}

	pPage=new CTextureProceduralPage(Type+IDS_TEXTUREPAGE_DIFFUSE);

	if(pPage!=NULL)
		pPage->Update(Type,
					  m_pRenderStructure->GetFrontalMaterial(),
					  pTexture);

	AddPage(pPage);

}

/////////*****************************************************///////////
////////GESTION RECEPTION DE MESSAGES///////////////////////////////////
void	CTextureSheet::RemoveProceduralPage(ENUM_TYPECOLOR type)
{
	switch(type)
	{
		case TYPE_AMBIENT:
			RemovePage(m_pTextureAmbientPage);
			m_pTextureAmbientPage=NULL;
			break;
		case TYPE_DIFFUSE:
			RemovePage(m_pTextureDiffusePage);
			m_pTextureDiffusePage=NULL;
			break;
		case TYPE_SPECULAR:
			RemovePage(m_pTextureSpecularPage);
			m_pTextureSpecularPage=NULL;
			break;
		case TYPE_TRANSPARENT:
			RemovePage(m_pTextureTransparentPage);
			m_pTextureTransparentPage=NULL;
			break;
	}

}
//*RemovePage : le premier paramètre est le type de la page à enlever
LRESULT  CTextureSheet::OnRemovePage(WPARAM wparam,LPARAM lparam)
{
	RemoveProceduralPage(ENUM_TYPECOLOR(wparam));
	return 0;
}

//*AddPage : le premier paramètre est le type de la page à ajouter
LRESULT  CTextureSheet::OnAddPage(WPARAM wparam,LPARAM lparam)
{
	CFrontalMaterial	*pFrontal=m_pRenderStructure->GetFrontalMaterial();

	switch(ENUM_TYPECOLOR(wparam))
	{
		case TYPE_AMBIENT:
			AddProceduralPage(TYPE_AMBIENT,m_pTextureAmbientPage,pFrontal->GetTexture(TYPE_AMBIENT));
			break;
		case TYPE_DIFFUSE:
			AddProceduralPage(TYPE_DIFFUSE,m_pTextureDiffusePage,pFrontal->GetTexture(TYPE_DIFFUSE));
			break;
		case TYPE_SPECULAR:
			AddProceduralPage(TYPE_SPECULAR,m_pTextureSpecularPage,pFrontal->GetTexture(TYPE_SPECULAR));
			break;
		case TYPE_TRANSPARENT:
			AddProceduralPage(TYPE_TRANSPARENT,m_pTextureTransparentPage,pFrontal->GetTexture(TYPE_TRANSPARENT));
			break;
	}
	return 0;
}

void	CTextureSheet::SelectMaterial(CString &str)
{
	CFrontalMaterial *pFrontal=m_pRenderStructure->GetFrontalMaterial();
	pFrontal->SetCurrentMaterial(pFrontal->GetMaterial(str.GetBuffer(str.GetLength())));
	Update(m_pRenderStructure,false);
}

LRESULT  CTextureSheet::OnUpdate(WPARAM wparam,LPARAM lparam)
{
	Update(m_pRenderStructure,true);

	return 0;
}

