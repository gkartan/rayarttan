// TextureGeneralPage.cpp : implementation file
//

#include "stdafx.h"
#include "raytracingstd.h"
#include "TextureGeneralPage.h"
#include "IhmConstants.h"
#include "Constants.h"
#include "BaseModelLight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureGeneralPage property page

IMPLEMENT_DYNCREATE(CTextureGeneralPage, CPropertyPage)

CTextureGeneralPage::CTextureGeneralPage() : CPropertyPage(CTextureGeneralPage::IDD)
{
	//{{AFX_DATA_INIT(CTextureGeneralPage)
	m_sMatiereName = _T("");
	m_PhongSize = 0.0;
	//}}AFX_DATA_INIT
}

CTextureGeneralPage::~CTextureGeneralPage()
{
}

void CTextureGeneralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureGeneralPage)
	DDX_Control(pDX, IDC_TEXTTRANSPARENT, m_BTextTransparent);
	DDX_Control(pDX, IDC_TEXTSPECULAR, m_BTextSpecular);
	DDX_Control(pDX, IDC_TEXTAMBIENT, m_BTextAmbient);
	DDX_Control(pDX, IDC_TEXTDIFFUSE, m_BTextDiffuse);
	DDX_Control(pDX, IDC_MATIERENAME, m_sMatiereNameCtrl);
	DDX_CBString(pDX, IDC_MATIERENAME, m_sMatiereName);
	DDX_Text(pDX, IDC_PHONGSIZE, m_PhongSize);
	//}}AFX_DATA_MAP

	//DoData -- Color Diffuse ---Begin
	DDX_Control(pDX, IDC_BCOLORDIFFUSE, m_BColorDiffuse);
	DDX_ColorPicker(pDX, IDC_BCOLORDIFFUSE, m_ColorDiffuse.GetColorRef());
	//DoData -- Color Diffuse ---End
	//DoData -- Color Ambient ---Begin
	DDX_Control(pDX, IDC_BCOLORAMB, m_BColorAmbient);
	DDX_ColorPicker(pDX, IDC_BCOLORAMB, m_ColorAmbient.GetColorRef());
	//DoData -- Color Ambient ---End
	//DoData -- Color Specular ---Begin
	DDX_Control(pDX, IDC_BCOLORSPEC, m_BColorSpecular);
	DDX_ColorPicker(pDX, IDC_BCOLORSPEC, m_ColorSpecular.GetColorRef());
	//DoData -- Color Specular ---End
	//DoData -- Color Transparent ---Begin
	DDX_Control(pDX, IDC_BCOLORTRANS, m_BColorTransparent);
	DDX_ColorPicker(pDX, IDC_BCOLORTRANS, m_ColorTransparent.GetColorRef());
	//DoData -- Color Transparent ---End
}


BEGIN_MESSAGE_MAP(CTextureGeneralPage, CPropertyPage)
	//{{AFX_MSG_MAP(CTextureGeneralPage)
	ON_BN_CLICKED(IDC_BCOLORAMB, OnButtonColorAmbient)
	ON_BN_CLICKED(IDC_BCOLORDIFFUSE, OnButtonColorDiffuse)
	ON_BN_CLICKED(IDC_BCOLORTRANS, OnButtonColorTransparent)
	ON_BN_CLICKED(IDC_BCOLORSPEC, OnButtonColorSpecular)
	ON_CBN_SELENDOK(IDC_MATIERENAME, OnSelendokMatierename)
	ON_BN_CLICKED(IDC_TEXTDIFFUSE, OnTextdiffuse)
	ON_BN_CLICKED(IDC_TEXTAMBIENT, OnTextambient)
	ON_BN_CLICKED(IDC_TEXTSPECULAR, OnTextspecular)
	ON_BN_CLICKED(IDC_TEXTTRANSPARENT, OnTexttransparent)
	ON_EN_KILLFOCUS(IDC_PHONGSIZE, OnKillfocusPhongsize)
	ON_BN_CLICKED(IDC_TEXTURE_SUPPR, OnTextureSuppr)
	ON_CBN_KILLFOCUS(IDC_MATIERENAME, OnKillfocusMatierename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureGeneralPage message handlers
void CTextureGeneralPage::OnButtonColorDiffuse()
{
	m_ColorDiffuse.UpdateColorRef(m_BColorDiffuse.GetColor());
	UpdateData(FALSE);	
	Update();
}

void CTextureGeneralPage::OnButtonColorAmbient()
{
	m_ColorAmbient.UpdateColorRef(m_BColorAmbient.GetColor());
	UpdateData(FALSE);	
	Update();
}

void CTextureGeneralPage::OnButtonColorSpecular()
{
	m_ColorSpecular.UpdateColorRef(m_BColorSpecular.GetColor());
	UpdateData(FALSE);	
	Update();
}

void CTextureGeneralPage::OnButtonColorTransparent()
{
	m_ColorTransparent.UpdateColorRef(m_BColorTransparent.GetColor());
	UpdateData(FALSE);
	Update();
}



void CTextureGeneralPage::Update(CFrontalMaterial *pMatiere)
{
	if(pMatiere==NULL) return;

	m_pMatiere=pMatiere;
		///Stockage de tous les noms de lumières 
	///dans la combo box
	if(::IsWindow(m_sMatiereNameCtrl.m_hWnd))
	{
		EnableWindow(true);
		///Remove all the combo box
		InitList();

	}
}

void CTextureGeneralPage::Update(CBaseMatiere *pMatiere)
{
	SetColorDiffuse(pMatiere->GetColorDiffuse());
	SetColorAmbient(pMatiere->GetColorAmbient());
	SetColorSpecular(pMatiere->GetColorSpecular());
	SetColorTransparent(pMatiere->GetColorTransparent());

	if(pMatiere->IsTexture(TYPE_AMBIENT))
	{
		m_BColorAmbient.EnableWindow(FALSE);
		m_BTextAmbient.SetCheck(1);
	}else {
		m_BColorAmbient.EnableWindow(TRUE);
		m_BTextAmbient.SetCheck(0);
	}
	if(pMatiere->IsTexture(TYPE_DIFFUSE))
	{
		m_BColorDiffuse.EnableWindow(FALSE);
		m_BTextDiffuse.SetCheck(1);
	}else{
		m_BColorDiffuse.EnableWindow(TRUE);
		m_BTextDiffuse.SetCheck(0);
	}
	if(pMatiere->IsTexture(TYPE_SPECULAR))
	{
		m_BColorSpecular.EnableWindow(FALSE);
		m_BTextSpecular.SetCheck(1);
	}else{
		m_BColorSpecular.EnableWindow(TRUE);
		m_BTextSpecular.SetCheck(0);
	}
	if(pMatiere->IsTexture(TYPE_TRANSPARENT))
	{
		m_BColorTransparent.EnableWindow(FALSE);
		m_BTextTransparent.SetCheck(1);
	}else{
		m_BColorTransparent.EnableWindow(TRUE);
		m_BTextTransparent.SetCheck(0);
	}

	if(pMatiere->GetModelLight()==NULL)
		m_PhongSize=DEFAULT_PHONGSIZE;
	else
		m_PhongSize=pMatiere->GetModelLight()->GetPhongExp();

	UpdateData(FALSE);

}

void CTextureGeneralPage::Update()
{
	UpdateData(TRUE);

	if(m_pMatiere!=NULL)
	{
		m_pMatiere->SetColorDiffuse(GetColorDiffuse());
		m_pMatiere->SetColorAmbient(GetColorAmbient());
		m_pMatiere->SetColorSpecular(GetColorSpecular());
		m_pMatiere->SetColorTransparent(GetColorTransparent());

		if(m_pMatiere->GetCurrentMaterial()->GetModelLight()!=NULL)
		{
			m_pMatiere->GetCurrentMaterial()->GetModelLight()->SetPhongExp(m_PhongSize);
		} else {
			if(m_PhongSize!=DEFAULT_PHONGSIZE)
			{
				m_pMatiere->GetCurrentMaterial()->SetModelLight(new CBaseModelLight(m_PhongSize));
			}
		}
	}
}



void CTextureGeneralPage::OnSelendokMatierename() 
{
	//m_pMatiere->SetCurrentMaterial(m_pMatiere->GetMaterial(m_sMatiereName.GetBuffer(m_sMatiereName.GetLength())));
	//Update(m_pMatiere->GetCurrentMaterial());

	UpdateData(TRUE);

	int Index=m_sMatiereNameCtrl.GetCurSel();

	m_pMatiere->SetCurrentMaterial(m_sMatiereNameCtrl.GetCurSel());

	Update(m_pMatiere->GetCurrentMaterial());

	m_sMatiereNameCtrl.SetCurSel(Index);

	UpdateData(TRUE);

	GetParent()->PostMessage(MS_UPDATE,NULL,NULL);
}

void CTextureGeneralPage::OnTextdiffuse() 
{
	if(m_BTextDiffuse.GetCheck())
	{
		GetParent()->PostMessage(MS_ADD_PAGE,TYPE_DIFFUSE,NULL);
		m_BColorDiffuse.EnableWindow(FALSE);
	} else {
		m_pMatiere->GetCurrentMaterial()->SetProcedural(TYPE_DIFFUSE,NULL);
		GetParent()->PostMessage(MS_REMOVE_PAGE,TYPE_DIFFUSE,NULL);
		m_BColorDiffuse.EnableWindow(TRUE);
	}
}
void CTextureGeneralPage::OnTextambient() 
{
	if(m_BTextAmbient.GetCheck())
	{
		GetParent()->PostMessage(MS_ADD_PAGE,TYPE_AMBIENT,NULL);
		m_BColorAmbient.EnableWindow(FALSE);
	} else {
		m_pMatiere->GetCurrentMaterial()->SetProcedural(TYPE_AMBIENT,NULL);
		GetParent()->PostMessage(MS_REMOVE_PAGE,TYPE_AMBIENT,NULL);
		m_BColorAmbient.EnableWindow(TRUE);
	}
	
}

void CTextureGeneralPage::OnTextspecular() 
{
	if(m_BTextSpecular.GetCheck())
	{
		GetParent()->PostMessage(MS_ADD_PAGE,TYPE_SPECULAR,NULL);
		m_BColorSpecular.EnableWindow(FALSE);
	} else {
		m_pMatiere->GetCurrentMaterial()->SetProcedural(TYPE_SPECULAR,NULL);
		GetParent()->PostMessage(MS_REMOVE_PAGE,TYPE_SPECULAR,NULL);
		m_BColorSpecular.EnableWindow(TRUE);
	}
	
}

void CTextureGeneralPage::OnTexttransparent() 
{
	if(m_BTextTransparent.GetCheck())
	{
		GetParent()->PostMessage(MS_ADD_PAGE,TYPE_TRANSPARENT,NULL);
		m_BColorTransparent.EnableWindow(FALSE);
	} else {
		m_pMatiere->GetCurrentMaterial()->SetProcedural(TYPE_TRANSPARENT,NULL);
		GetParent()->PostMessage(MS_REMOVE_PAGE,TYPE_TRANSPARENT,NULL);
		m_BColorTransparent.EnableWindow(TRUE);
	}
	
}

BOOL CTextureGeneralPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CTextureGeneralPage::OnKillfocusPhongsize() 
{
	Update();	
}

void CTextureGeneralPage::OnTextureSuppr() 
{
	m_pMatiere->DelCurrentMaterial();	
	InitList();
	UpdateData(FALSE);
	
}

void CTextureGeneralPage::InitList()
{
	m_sMatiereNameCtrl.ResetContent();

	TypeVectorMaterial::iterator	theIterator;
	for(theIterator=m_pMatiere->GetListMaterial()->begin();
		theIterator<m_pMatiere->GetListMaterial()->end();
		theIterator++)
		{
			std::string stdstr((*theIterator)->GetName());
			CString	str;
			str.Format("%s",stdstr.c_str());
			m_sMatiereNameCtrl.AddString(str);
		}

	if(m_pMatiere->GetCurrentMaterial()!=NULL)
	{
		m_sMatiereName=m_pMatiere->GetCurrentMaterial()->GetName().c_str();
		//m_sMatiereNameCtrl.SelectString(0,pMatiere->GetCurrentMaterial()->GetName().c_str());
	}
	else
		m_sMatiereNameCtrl.SetCurSel(0);

	///Initialisation
	theIterator=m_pMatiere->GetListMaterial()->begin();

	if(theIterator==NULL) return;

	if(m_pMatiere->GetCurrentMaterial()==NULL)
	{
		CBaseMatiere *pFirstMatiere=(*theIterator);
		m_pMatiere->SetCurrentMaterial(pFirstMatiere);

		Update(pFirstMatiere);
	} else {
		Update(m_pMatiere->GetCurrentMaterial());
	}
}

void CTextureGeneralPage::OnKillfocusMatierename() 
{
	UpdateData(TRUE);
	//effectue l'ajout
	std::string str(m_sMatiereName.GetBuffer(m_sMatiereName.GetLength()));
	if(!m_pMatiere->IsMaterial(str))
	{
		m_pMatiere->AddMatiere(str);
	}

	InitList();

	GetParent()->PostMessage(MS_UPDATE,NULL,NULL);
}
