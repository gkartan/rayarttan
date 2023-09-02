// TextureProceduralPage.cpp : implementation file
//
#pragma	warning(disable : 4096)

#include "stdafx.h"
#include "raytracingstd.h"
#include "TextureProceduralPage.h"
#include "Macros.h"
#include "EditColorMapDlg.h"
#include "IhmConstants.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureProceduralPage property page

IMPLEMENT_DYNCREATE(CTextureProceduralPage, CPropertyPage)

CTextureProceduralPage::CTextureProceduralPage() : CPropertyPage(CTextureProceduralPage::IDD)
{
	//{{AFX_DATA_INIT(CTextureProceduralPage)
	m_Procedure = _T("");
	//}}AFX_DATA_INIT
}

CTextureProceduralPage::CTextureProceduralPage(int Title) : CPropertyPage(CTextureProceduralPage::IDD,Title)
{
	//{{AFX_DATA_INIT(CTextureProceduralPage)
	m_Procedure = _T("");
	//}}AFX_DATA_INIT
}

CTextureProceduralPage::~CTextureProceduralPage()
{
}

void CTextureProceduralPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureProceduralPage)
	DDX_Control(pDX, IDC_PROCEDURE, m_ProcedureCtrl);
	DDX_Control(pDX, IDC_COLORMAP, m_ListCtrl);
	DDX_CBString(pDX, IDC_PROCEDURE, m_Procedure);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureProceduralPage, CPropertyPage)
	//{{AFX_MSG_MAP(CTextureProceduralPage)
	ON_NOTIFY(NM_RCLICK, IDC_COLORMAP, OnRclickColormap)
	ON_CBN_SELENDOK(IDC_PROCEDURE, OnSelendokProcedure)
	ON_COMMAND(ID_COLORMAP_INSERTCOLOR,OnInsertcolorColorMap)
	ON_COMMAND(ID_COLORMAP_DELETECOLOR,OnDeletecolorColorMap)
	ON_COMMAND(ID_COLORMAP_MODIFYCOLOR,OnModifycolorColorMap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void	CTextureProceduralPage::Update(ENUM_TYPECOLOR Type,
									   CFrontalMaterial	*pMatiere,
									   CTextureElement	*pTexture)
{
	m_pMatiere=pMatiere;
	m_pTextureElement=pTexture;
	m_MyType=Type;

	m_Procedure.Format("%s",m_pTextureElement->GetType().c_str());

	//Remplissage des données
	if(::IsWindow(m_ListCtrl.m_hWnd) && m_pTextureElement->IsTexture())
	{
		UpdateColorMap();
		UpdateData(FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTextureProceduralPage message handlers

BOOL CTextureProceduralPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	///Initialisation de la liste colormap
	CString str;
	m_ListCtrl.DeleteColumns();
	m_ListCtrl.DeleteAllItems();
	str.LoadString(IDS_COLORMAP_COLUMN1);
	m_ListCtrl.AddColumn(str,0);
	str.LoadString(IDS_COLORMAP_COLUMN2);
	m_ListCtrl.AddColumn(str,1);
	str.LoadString(IDS_COLORMAP_COLUMN3);
	m_ListCtrl.AddColumn(str,2);
	str.LoadString(IDS_COLORMAP_COLUMN4);
	m_ListCtrl.AddColumn(str,3);

	if(m_pTextureElement!=NULL)
		Update(m_MyType,m_pMatiere,m_pTextureElement);
	
	UpdateData(FALSE);	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/********************************************************************************/
/***********************GESTION DE LA COLORMAP**********************************/
/********************************************************************************/
void CTextureProceduralPage::OnRclickColormap(NMHDR* pNMHDR, LRESULT* pResult) 
{
	///Ouverture d'un menu permet l'ajout et l'effacement d'une couleur
	CMenu *Popupmenu, menu;
	CPoint posMouse;

	GetCursorPos(&posMouse);

	if (menu.LoadMenu(IDR_MENU_COLORMAP))
	{
		Popupmenu = menu.GetSubMenu(0);

		if (m_ListCtrl.GetNextItem(-1, LVNI_SELECTED) == 0)
		{
			Popupmenu->EnableMenuItem(ID_COLORMAP_DELETECOLOR, MF_GRAYED);
		}
		if (m_ListCtrl.GetNextItem(-1, LVNI_SELECTED)==m_ListCtrl.GetItemCount()-1)
		{
			Popupmenu->EnableMenuItem(ID_COLORMAP_DELETECOLOR, MF_GRAYED);
		}

		Popupmenu->TrackPopupMenu(TPM_RIGHTBUTTON, posMouse.x, posMouse.y, this);

	}
	
	*pResult = 0;
}

/////////////////////////////////////////////////
///Insertion d'un élément dans la liste
void CTextureProceduralPage::OnInsertcolorColorMap()
{
	////////Appel de la boite de dialgue de saisie
	CEditColorMapDlg	dlg;
	dlg.DoModal();
	////////Maj structures internes
	float	Position;
	CColor	Color;
	dlg.RetrieveData(Position,Color);
	m_pTextureElement->SetColor(Position,Color);

	////////Rafraichissement affichage
	UpdateColorMap();
}

/////////////////////////////////////////////////
///Effacement d'un élément de la liste
void CTextureProceduralPage::OnDeletecolorColorMap()
{
	////////Effacement de la liste interne
	TypeColorMap::iterator	theIterator;
	TypeColorMap	&ColorMap=m_pTextureElement->GetColorMap();

	if(GetColorMapSelect(theIterator))
	{
		ColorMap.erase(theIterator);
	}

	////////Rafraichissement de l'affichage
	int	Index=m_ListCtrl.GetSelectedIndex();
	m_ListCtrl.DeleteItem(Index);
}

/////////////////////////////////////////////////
///Modification d'un élément de la liste
void CTextureProceduralPage::OnModifycolorColorMap()
{
	TypeColorMap::iterator	theIterator;
	TypeColorMap	&ColorMap=m_pTextureElement->GetColorMap();

	if(GetColorMapSelect(theIterator))
	{
		////////Init la boite de dialogue
		CEditColorMapDlg	dlg;
		dlg.Init((*theIterator).first,(*theIterator).second,true);
		////////Appel boite de dialogue
		dlg.DoModal();
		////////Maj structures internes
		float Position=0;
		dlg.RetrieveData(Position,(*theIterator).second);
		if(Position!=(*theIterator).first)
		{
			ColorMap[Position]=ColorMap[(*theIterator).first];
			ColorMap.erase((*theIterator).first);
		}

		////////Rafraichissement de l'affichage
		UpdateColorMap();
	}
}

void	CTextureProceduralPage::UpdateColorMap()
{
	if(m_pTextureElement==NULL)
	{
		m_ListCtrl.EnableWindow(FALSE);
		return;
	}

	m_ListCtrl.EnableWindow(TRUE);
	m_ListCtrl.DeleteAllItems();

	//Pour toutes les couleurs de la map insertion
	TypeColorMap	&ColorMap=m_pTextureElement->GetColorMap();

	TypeColorMap::iterator	theIterator;
	int i=0;
	for(theIterator=ColorMap.begin();theIterator!=ColorMap.end();theIterator++)
	{
		CString strPos;
		strPos.Format("%.2f",(*theIterator).first);
		CString strRed;
		strRed.Format("%d",CONVERT_COLORIHM((*theIterator).second.GetRed()));
		CString strGreen;
		strGreen.Format("%d",CONVERT_COLORIHM((*theIterator).second.GetGreen()));
		CString strBlue;
		strBlue.Format("%d",CONVERT_COLORIHM((*theIterator).second.GetBlue()));
		m_ListCtrl.AddItem(i,strPos.GetBuffer(strPos.GetLength()));
		m_ListCtrl.AddItemInfo(i,strRed.GetBuffer(strRed.GetLength()),
								 strGreen.GetBuffer(strGreen.GetLength()),
								 strBlue.GetBuffer(strBlue.GetLength()));
		i++;
	}
}


//************
//Retrouve l'itérateur correspond à l'élément sélectionné dans la liste
bool		CTextureProceduralPage::GetColorMapSelect(TypeColorMap::iterator &theIterator)
{
	int	Index=m_ListCtrl.GetSelectedIndex();
	TypeColorMap	&ColorMap=m_pTextureElement->GetColorMap();

	///trouve le nième élément de la map
	int i=0;
	theIterator=ColorMap.begin();
	while(i<Index && theIterator!=ColorMap.end())
	{
		theIterator++;
		i++;
	}

	if(theIterator!=ColorMap.end())
	{
		return true;
	}

	return false;
}
/*****************FIN GESTION COLORMAP****************************************************/
/*****************************************************************************************/

void CTextureProceduralPage::OnSelendokProcedure() 
{
	UpdateData(TRUE);

	/////A REVOIR
	/////Pour une raison inconnue la variable m_Procedure n'est pas mis à jour
	/////encore, j'accède donc à la valeur sélectionné par le contrôle
	CString strTemp;
	m_ProcedureCtrl.GetLBText(m_ProcedureCtrl.GetCurSel(),strTemp);

	////Les CString ne sont utilisés que dans l'IHM 
	///tout sortie de l'ihm provoque une conversion en std::string
	//std::string	str(m_Procedure.GetBuffer(m_Procedure.GetLength()));
	std::string str(strTemp.GetBuffer(m_Procedure.GetLength()));
	m_pMatiere->ChangeTypeTexture(m_MyType,str);

	if(m_pTextureElement->IsTexture())
	{
		UpdateColorMap();
	}
}
