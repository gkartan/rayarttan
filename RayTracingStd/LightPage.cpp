// LightPage.cpp : implementation file
//

#include "stdafx.h"
#include "raytracingstd.h"
#include "LightPage.h"
#include "TraceService.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightPage property page

IMPLEMENT_DYNCREATE(CLightPage, CPropertyPage)

CLightPage::CLightPage() : CPropertyPage(CLightPage::IDD)
{
	//{{AFX_DATA_INIT(CLightPage)
	m_sLightType = _T("");
	m_sLightName = _T("");
	//}}AFX_DATA_INIT
	m_pLight=NULL;
}

CLightPage::~CLightPage()
{
}

void CLightPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightPage)
	DDX_Control(pDX, IDC_LIGHTNAME, m_sLightNameCtrl);
	DDX_CBString(pDX, IDC_LIGHTTYPE, m_sLightType);
	DDX_CBString(pDX, IDC_LIGHTNAME, m_sLightName);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_LIGHTPOSX, m_Position.GetRefX());
	DDX_Text(pDX, IDC_LIGHTPOSY, m_Position.GetRefY());
	DDX_Text(pDX, IDC_LIGHTPOSZ, m_Position.GetRefZ());
	DDX_Text(pDX, IDC_LIGHTCOLORR, m_Color.GetRed());
	DDX_Text(pDX, IDC_LIGHTCOLORG, m_Color.GetGreen());
	DDX_Text(pDX, IDC_LIGHTCOLORB, m_Color.GetBlue());
	DDX_Control(pDX, IDC_LIGHTCOLOR, m_ColorButton);
	DDX_ColorPicker(pDX, IDC_LIGHTCOLOR, m_Color.GetColorRef());
}


BEGIN_MESSAGE_MAP(CLightPage, CPropertyPage)
	//{{AFX_MSG_MAP(CLightPage)
	ON_CBN_SELENDOK(IDC_LIGHTNAME, OnSelendokLightname)
	ON_EN_KILLFOCUS(IDC_LIGHTCOLORB, OnKillfocusLightcolorb)
	ON_EN_KILLFOCUS(IDC_LIGHTCOLORG, OnKillfocusLightcolorg)
	ON_EN_KILLFOCUS(IDC_LIGHTCOLORR, OnKillfocusLightcolorr)
	ON_EN_KILLFOCUS(IDC_LIGHTPOSX, OnKillfocusLightposx)
	ON_EN_KILLFOCUS(IDC_LIGHTPOSY, OnKillfocusLightposy)
	ON_EN_KILLFOCUS(IDC_LIGHTPOSZ, OnKillfocusLightposz)
	ON_CBN_SELENDOK(IDC_LIGHTTYPE, OnSelendokLighttype)
	ON_BN_CLICKED(IDC_LIGHTCOLOR, OnButtonLightColor)
	ON_BN_CLICKED(IDC_LIGHTDELETE, OnLightdelete)
	ON_BN_CLICKED(IDC_LIGHTADD, OnLightadd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightPage message handlers
////////////////////////////////////////////////
//Mise à jour IHM 
void CLightPage::InitList()
{
	///Remove all the combo box
	m_sLightNameCtrl.ResetContent();


	if(m_pLight->GetListLight()->size()==0) 
	{
		m_sLightName="";
		UpdateData(FALSE);
		return;
	}

	TypeVectorLight::iterator	theIterator;
	int i=1;	
	for(theIterator=m_pLight->GetListLight()->begin();
		theIterator<m_pLight->GetListLight()->end();
		theIterator++)
		{
			m_sLightNameCtrl.AddString((*theIterator)->GetName().c_str());
			i++;
		}
}

void CLightPage::ResetList()
{

	InitList();

	m_sLightNameCtrl.SetCurSel(0);

			///Initialisation de l'ihm avec la première lumière
	TypeVectorLight::iterator theIterator=m_pLight->GetListLight()->begin();

	if(theIterator==NULL) return;

	CBaseLight *ptheLight=(*theIterator);
	SetColor(ptheLight->GetColor());

	m_sLightType=ptheLight->GetType().c_str();

	m_pLight->SetCurrentLight(ptheLight);

	if(EnablePosition(m_pLight->GetIsPosition()))
	{
		SetPosition(m_pLight->GetPosition());
	}

	m_sLightName=ptheLight->GetName().c_str();

	UpdateData(FALSE);


}
void CLightPage::Update(CFrontalLight *pLight)
{
	if(pLight==NULL) return;

	///Stockage de tous les noms de lumières 
	///dans la combo box
	///Stockage du pointeur
	m_pLight=pLight;

	if(::IsWindow(m_sLightNameCtrl.m_hWnd))
	{
		EnableWindow(true);

		ResetList();

	}


}

void CLightPage::Update(CBaseLight *pLight)
{
	if(EnablePosition(pLight->GetIsPosition()))
	{
		SetPosition(pLight->GetPosition());
	}

	SetColor(pLight->GetColor());

	m_sLightType=pLight->GetType().c_str();


	UpdateData(FALSE);
}

void CLightPage::Update()
{
	std::string OldValueType=m_sLightType;
	std::string OldValueName=m_sLightName;

	UpdateData(TRUE);

	if(m_pLight!=NULL)
	{
		////Si c'est une nouvelle lumière on effectue l'ajout
		if(OldValueName.compare(m_sLightName)!=0)
		{
			///Création de la lumière
			m_pLight->AddLight(m_sLightName.GetBuffer(m_sLightName.GetLength()));
			m_pLight->ChangeType(std::string(m_sLightType));
			InitList();
			m_sLightNameCtrl.SelectString(0,m_sLightName);
		}

		m_pLight->SetColor(GetColor());

		///Si la lumière n'accepte pas de position (ambient) 
		///la fonction ne fait rien
		///Gestion dans le polymorphisme
		m_pLight->SetPosition(GetPosition());

		if(OldValueType.compare(m_sLightType)!=0)
		{
			m_pLight->ChangeType(std::string(m_sLightType));

			//Récupération éléments courant sélectionné
			int ElCurSel=m_sLightNameCtrl.GetCurSel();
			Update(m_pLight);
			//sélectionné le bon élément
			m_sLightNameCtrl.SetCurSel(ElCurSel);
			OnSelendokLightname();
		}
	}
}

BOOL CLightPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	if(m_pLight!=NULL)
		Update(m_pLight);
	
	UpdateData(FALSE);
	m_sLightNameCtrl.SetCurSel(0);
	UpdateData(TRUE);

	EnableWindow(m_bEnable);

	return TRUE;  
}

void CLightPage::OnSelendokLightname() 
{
	UpdateData(TRUE);

	int Index=m_sLightNameCtrl.GetCurSel();

	m_pLight->SetCurrentLight(m_sLightNameCtrl.GetCurSel());

	Update(m_pLight->GetCurrentLight());

	m_sLightNameCtrl.SetCurSel(Index);

	UpdateData(TRUE);
}

void CLightPage::OnKillfocusLightcolorb() 
{
	Update();	
}

void CLightPage::OnKillfocusLightcolorg() 
{
	Update();	
}

void CLightPage::OnKillfocusLightcolorr() 
{
	Update();	
}

void CLightPage::OnKillfocusLightposx() 
{
	Update();	
}

void CLightPage::OnKillfocusLightposy() 
{
	Update();	
}

void CLightPage::OnKillfocusLightposz() 
{
	Update();	
}


bool CLightPage::EnablePosition(bool bEnable)
{
	GetDlgItem(IDC_LIGHTPOSX)->EnableWindow(bEnable);
	GetDlgItem(IDC_LIGHTPOSY)->EnableWindow(bEnable);
	GetDlgItem(IDC_LIGHTPOSZ)->EnableWindow(bEnable);

	return bEnable;
}

void CLightPage::OnSelendokLighttype() 
{
	Update();		
}

void CLightPage::OnButtonLightColor()
{
	m_Color.UpdateColorRef(m_ColorButton.GetColor());

	UpdateData(FALSE);	

	Update();		
}

//*******
//*Effacement de la lumière courante
//*******
void CLightPage::OnLightdelete() 
{
	m_pLight->DelCurrentLight();	
	ResetList();
	UpdateData(FALSE);
}


void CLightPage::OnLightadd() 
{
	UpdateData(TRUE);
	m_pLight->AddLight(m_sLightName.GetBuffer(m_sLightName.GetLength()));
	ResetList();
	UpdateData(FALSE);
	m_sLightNameCtrl.SetCurSel(0);
	UpdateData(TRUE);
}
