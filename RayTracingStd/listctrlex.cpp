/////////////////////////////////////////////////////////////////////////////
// CSCI EXP
// LOGICIEL D'EXPLOITATION DU PRODUIT SMART AIR
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSCI IHM
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// DESCRIPTION DE CSU
//
// Nom du CSU  : CListCtrlEx
// Role du CSU : Gestion etandue de listes
//
// Calculateur : PC WinNT 4.0
//
// Historique des modifications :
//
// Identification :
// Description    : Creation
// Date           : 10/04/97
// Auteur         : Thierry HAURIE
//
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// ENVIRONNEMENT DU CSU
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GESTION DES MESSAGES DU CSU
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx : Constructeur
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : aucune
// Sorties   : aucune
// Retour    : aucun
// 
/////////////////////////////////////////////////////////////////////////////
CListCtrlEx::CListCtrlEx()
{
	Parent		= NULL;
	Item		= 0;
	Index		= -1;
	NoSelection = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ~CListCtrlEx : Destructeur
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : aucune
// Sorties   : aucune
// Retour    : aucun
// 
/////////////////////////////////////////////////////////////////////////////
CListCtrlEx::~CListCtrlEx()
{
	
}

/////////////////////////////////////////////////////////////////////////////
// AddColumn : Ajout d'une colonne à une position déterminée
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : strItem	-> Nom de la colonne
//			   nItem	-> Index de l'item
//			   cx		-> Largeur de la colonne
//			   nFmt		-> Format d'affichage
//			   nSubItem	-> Index de la colonne
//			   nMask	-> Masque de commande
// Sorties   : aucune	
// Retour    : cf. MFC
// 
/////////////////////////////////////////////////////////////////////////////
BOOL CListCtrlEx::AddColumn(LPCTSTR strItem,int nItem,int cx,int nFmt,int nSubItem,int nMask)
{
	LV_COLUMN lvc;
	
	// Initialisation
	lvc.mask	= nMask;
	lvc.fmt		= nFmt;
	lvc.pszText = (LPTSTR) strItem;
	if(nMask & LVCF_SUBITEM)
	{
		if(nSubItem != -1)
			lvc.iSubItem = nSubItem;
		else
			lvc.iSubItem = nItem;
	}

	// Défini la largeur de la colonne
	if (cx != -1)
		lvc.cx = cx;
	else
		lvc.cx = GetStringWidth(lvc.pszText) + 15;

		
	return (InsertColumn(nItem,&lvc) != -1);
}

/////////////////////////////////////////////////////////////////////////////
// AddColumn : Ajout de plusieurs colonnes
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : strItem,...	-> Noms de chaque colonne
// Sorties   : aucune	
// Retour    : cf. MFC (InsertColumn)
// 
/////////////////////////////////////////////////////////////////////////////
BOOL CListCtrlEx::AddColumn(LPCTSTR strItem,...)
{
	LV_COLUMN lvc;
	va_list marker;
	int		i = 0;
	LPCTSTR str = strItem;
	BOOL	result = TRUE;
		
	// Initialisation
	va_start( marker, strItem );

	lvc.mask	= LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt		= LVCFMT_LEFT;
	
	

	// Pour chaque chaine de caratères, ajout d'une colonne
	while (lstrlen(str)>0)
	{
		lvc.iSubItem = i;
		lvc.pszText = (LPTSTR) str;
		// Calcule la largeur de la colonne
		lvc.cx = GetStringWidth(lvc.pszText) + 15;
		result &= (InsertColumn(i,&lvc)!=-1);
		// Lecture de la nouvelle chaine de carateres
		str = va_arg(marker, LPCTSTR);
		i++;
	}
	va_end( marker );

	return result;
}

/////////////////////////////////////////////////////////////////////////////
// SetColumnSize : Change la taille de la colonne
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : idx		-> Index de la colonne
//			   cx		-> Taille de la colonne
// Sorties   : aucune	
// Retour    : aucun
// 
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::SetColumnSize(int idx,int cx)
{
	LV_COLUMN lvc;
	
	lvc.cx = cx;
	lvc.mask	= LVCF_WIDTH;
	SetColumn(idx,&lvc);
}

/////////////////////////////////////////////////////////////////////////////
// GetColumnSize : Retourne la taille de la colonne
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : idx		-> Index de la colonne
// Sorties   : aucune	
// Retour    : Taille de la colonne
// 
/////////////////////////////////////////////////////////////////////////////
int CListCtrlEx::GetColumnSize(int idx)
{
	LV_COLUMN lvc;
	
	lvc.mask	= LVCF_WIDTH;
	GetColumn(idx,&lvc);

	return lvc.cx;
}

/////////////////////////////////////////////////////////////////////////////
// SetColumnSize : Change la taille de la colonne
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : idx		-> Index de la colonne
//			   cx		-> Taille de la colonne
// Sorties   : aucune	
// Retour    : aucun
// 
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::DeleteColumns()
{
	while (DeleteColumn(0))	{ }
}

/////////////////////////////////////////////////////////////////////////////
// AddItem : Ajout d'un item
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : nItem		-> Numero de l'item
//			   strItem		-> Nom de l'item
//			   nImageIndex	-> Index de l'icone associe
//			   data			-> Donnees associees a l'item
// Sorties   : aucune	
// Retour    : cf. MFC
// 
/////////////////////////////////////////////////////////////////////////////
BOOL CListCtrlEx::AddItem(int nItem, LPCTSTR strItem,int nImageIndex, LPARAM data)
{
	LV_ITEM lvItem;
	
	// Initialisation
	lvItem.mask = LVIF_TEXT | LVIF_PARAM;
	lvItem.iItem = nItem;
	lvItem.iSubItem = 0;
	lvItem.pszText = (LPTSTR) strItem;

	// Ajout de l'icone de l'item
	if(nImageIndex != -1){
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage = nImageIndex;
	}
	
	// Attribution du pointeur sur les données de l'item (utilisé pour la mise en ordre)
	lvItem.lParam = (LPARAM)data;

	// Ajout de l'item
	return (InsertItem(&lvItem) != -1);
}



/////////////////////////////////////////////////////////////////////////////
// AddItemInfo : Ajout d'une info pour un item donné à une colonne
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : nItem	-> Numero de l'item
//			   nSubItem	-> Numero de la colonne
//			   strItem	-> Chaine contenant l'info associee
// Sorties   : aucune	
// Retour    : 
// 
/////////////////////////////////////////////////////////////////////////////
BOOL CListCtrlEx::AddItemInfo(int nItem, int nSubItem, LPCTSTR strItem)
{
	LV_ITEM lvItem;

	if (strItem != NULL)
	{
		// Initialisation
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = nItem;
		lvItem.iSubItem = nSubItem;
		if (lstrlen(strItem)>0)
			lvItem.pszText = (LPTSTR)strItem;
		else
			lvItem.pszText = _T(" ");

		// Ajout de l'info
		return SetItem(&lvItem);
	}
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// AddItemInfo : Ajout d'infos sur plusieurs colonnes pour un item donné
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : nItem	-> Numero de l'item
//			   strItem	-> Chaines contenant les infos associees
// Sorties   : aucune	
// Retour    : 
// 
/////////////////////////////////////////////////////////////////////////////
BOOL CListCtrlEx::AddItemInfo(int nItem, LPCTSTR strItem, ...)
{
	LV_ITEM lvItem;
	va_list marker;
	int		i = 1;
	LPCTSTR str = strItem;
	BOOL	result = TRUE;
	
	// Initialisation
	va_start( marker, strItem );
	
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	
	// Pour chaque chaine de caratères, ajout d'une info dans la colonne suivante
	while (lstrlen(str)>0)
	{
		lvItem.iSubItem = i;
		if (lstrlen(str)>0)
			lvItem.pszText = (LPTSTR)str;
		else
			lvItem.pszText = _T(" ");
		// Ajout d'une info
		result &= SetItem(&lvItem);
		// Lecture de la nouvelle chaine de carateres
		str = va_arg(marker, LPCTSTR);
		i++;
	}
	va_end( marker );

	return result;
}

/////////////////////////////////////////////////////////////////////////////
// SetItemImage : Change l'image d'un item donné
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : nItem	-> Numero de l'item
//		   nImage	-> Numero de l'image dans la liste des images
//				   (Image List)
// Sorties   : aucune	
// Retour    : TRUE si succès, FALSE sinon 
// 
/////////////////////////////////////////////////////////////////////////////
BOOL CListCtrlEx::SetItemImage(int nItem, int nImage)
{
	LV_ITEM lvItem;

	// Initialisation
	lvItem.mask = LVIF_IMAGE;
	lvItem.iItem = nItem;
	lvItem.iSubItem = 0;
	lvItem.iImage = nImage;

	// Mise à jour de l'info
	return SetItem(&lvItem);
}

/////////////////////////////////////////////////////////////////////////////
// DrawListViewItem : Dessine l'item demande pour une OWNERDRAW ListCtrl
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : cf. MFC
// Sorties   : aucune	
// Retour    : aucun
// 
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::DrawListViewItem(LPDRAWITEMSTRUCT lpDrawItem)
{

    CString		str;
    CImageList* iml;
	IMAGEINFO	imageInfo;
    LV_ITEM		lvi;
	LV_COLUMN   pColumn;
	RECT		rcClip;
	CSize		sizeString;

	CString	sTemp;
    int iColumn = 1;
	int cxImage = 0, cyImage = 0;
	int i;
	UINT uiFlags = ILD_TRANSPARENT;
	static CDC*	   dc;

	// Recupere le context de l'item
	dc = CDC::FromHandle(lpDrawItem->hDC);
		
	// Test si l'item est selectionne
    if ((lpDrawItem->itemState & ODS_SELECTED) && (!NoSelection))
    {
        // Initialise les couleurs de texte et de fond
        dc->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
        dc->SetBkColor(GetSysColor(COLOR_HIGHLIGHT));

		// Ajout de ILD_BLEND50 pour que l'icone soit selectionne
		uiFlags |= ILD_BLEND50;
    }
    else
    {
        // Initialise les couleurs standard de texte et de fond
        dc->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
        dc->SetBkColor(GetSysColor(COLOR_WINDOW));
    }
	
	
	// Recupere l'icone de l'item
    lvi.mask	 = LVIF_IMAGE | LVIF_STATE;
    lvi.iItem	 = lpDrawItem->itemID;
    lvi.iSubItem = 0;
    GetItem(&lvi);

     // Dessine l'icone
    iml = GetImageList(LVSIL_SMALL);
    if (iml!=NULL)
    {
        iml->Draw(dc,lvi.iImage,CPoint(lpDrawItem->rcItem.left,lpDrawItem->rcItem.top), uiFlags);

        // Recupere les infos sur l'icone 
 		iml->GetImageInfo(lvi.iImage,&imageInfo);

    }

	// Recupere le texte de l'item
	str = GetItemText(lpDrawItem->itemID,0);

    // Calcule le rectangle dans lequel est dessine le texte
	rcClip = lpDrawItem->rcItem;
    rcClip.right  = rcClip.left + GetColumnWidth(0);
	if (iml!=NULL)
		rcClip.left	  = rcClip.left + imageInfo.rcImage.right-imageInfo.rcImage.left;
        
	pColumn.mask = LVCF_FMT;
	GetColumn(0,&pColumn);
	
	sTemp = CalcStringEllipsis(dc,str, rcClip.right - rcClip.left+1);
	sizeString = dc->GetTextExtent(sTemp);

	// Dessine le texte
	switch (pColumn.fmt & LVCFMT_JUSTIFYMASK)
	{
		case LVCFMT_LEFT   : dc->ExtTextOut(rcClip.left, rcClip.top+1, ETO_CLIPPED | ETO_OPAQUE, &rcClip, sTemp, sTemp.GetLength(), NULL);
						     break;

		case LVCFMT_RIGHT  : dc->ExtTextOut(rcClip.right-sizeString.cx, rcClip.top+1, ETO_CLIPPED | ETO_OPAQUE, &rcClip, sTemp, sTemp.GetLength(), NULL);
							 break;
		
		case LVCFMT_CENTER : dc->ExtTextOut(rcClip.left+(rcClip.right-rcClip.left+1-sizeString.cx)/2, rcClip.top+1, ETO_CLIPPED | ETO_OPAQUE, &rcClip, sTemp, sTemp.GetLength(), NULL);
						     break;
	}
		
	i=1;
	pColumn.mask = LVCF_FMT;
	
	// Pour chaque colonne on dessine les infos de l'item
	while(GetColumn(i,&pColumn)) 
	{
		rcClip.left = rcClip.right;
		rcClip.right = rcClip.left + GetColumnWidth(i);
		str = GetItemText(lpDrawItem->itemID,i);
		sTemp = CalcStringEllipsis(dc, str, rcClip.right - rcClip.left+1);
		sizeString = dc->GetTextExtent(sTemp);
		switch (pColumn.fmt & LVCFMT_JUSTIFYMASK)
		{	
			case LVCFMT_LEFT   : dc->ExtTextOut(rcClip.left, rcClip.top+1, ETO_CLIPPED | ETO_OPAQUE, &rcClip, sTemp, sTemp.GetLength(), NULL);
							     break;
	
			case LVCFMT_RIGHT  : dc->ExtTextOut(rcClip.right-sizeString.cx, rcClip.top+1, ETO_CLIPPED | ETO_OPAQUE, &rcClip, sTemp, sTemp.GetLength(), NULL);
								 break;
		
			case LVCFMT_CENTER : dc->ExtTextOut(rcClip.left+(rcClip.right-rcClip.left+1-sizeString.cx)/2, rcClip.top+1, ETO_CLIPPED | ETO_OPAQUE, &rcClip, sTemp, sTemp.GetLength(), NULL);
							     break;
		}
		i++;
	}

    // Mise a jour des couleurs de texte et de fond
    if ((lpDrawItem->itemState & ODS_SELECTED) && (!NoSelection))
    {
        dc->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
        dc->SetBkColor(GetSysColor(COLOR_WINDOW));
    }

    // Si l'item est selectionne, on dessine le rectangle de focus
    if ((lpDrawItem->itemState & ODS_FOCUS) && (!NoSelection))
    {
        // Calcule le rectangle de focus
		rcClip = lpDrawItem->rcItem;
        rcClip.left += cxImage;

        // Dessine le rectangle de focus
        dc->DrawFocusRect(&rcClip);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CalcStringEllipsis : Ajout de la chaine "..." si la colonne est trop etroite
/////////////////////////////////////////////////////////////////////////////
//
// Entrees   : dc			-> Device contexte de la liste
//			   s			-> Chaine a afficher dans la colonne
//			   uColWidth	-> Largeur de la colonne
// Sorties   : aucune	
// Retour    : Chaine modifiee
// 
/////////////////////////////////////////////////////////////////////////////
CString CListCtrlEx::CalcStringEllipsis(CDC* dc, CString s, UINT uColWidth)
{
    CString szEllipsis = _T("...");
    CSize   sizeString;
    CSize   sizeEllipsis;
    CString sTemp;

    // Ajuste la largeur de la colonne pour prendre en compte les bords
    uColWidth -= 4;
	sTemp = s;
	    
	// Teste si la chaine est valide
	if (sTemp.GetLength()>0)
	{
		// Calcule la taille de la chaine
		sizeString = dc->GetTextExtent(sTemp);
		// Calcule la taille de la chaine "..."
		sizeEllipsis = dc->GetTextExtent(szEllipsis);
    
		// Teste la taille de la chaine par rapport a la largeur de la colonne
		if (((ULONG)sizeString.cx > uColWidth) && (sizeString.cy > 0))
		{
			while (sTemp.GetLength() > 0)
			{
				// Retire de dernier caratere de la chaine
				sTemp = sTemp.Left(sTemp.GetLength()-1);
				// Calcule la nouvelle taille de la chaine
				sizeString = dc->GetTextExtent(sTemp);
				// Si la taille est correct on ajoute la chaine "..."
				if ((ULONG)(sizeString.cx + sizeEllipsis.cx) <= uColWidth)
				{
					sTemp = sTemp + szEllipsis;
					return (sTemp);
				}
			}
		}
	}
	// Revoie de la chaine de caratres modifie
    return (sTemp);
}

/////////////////////////////////////////////////////////////////////////////
// DrawItem : Affiche l'item demande
/////////////////////////////////////////////////////////////////////////////
//
// DrawItem  : cf. MFC
// Sorties   : aucune	
// Retour    : aucun
// 
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	// Make sure the control is the listview control
    if (lpDrawItemStruct->CtlType == ODT_LISTVIEW)
	{

		switch (lpDrawItemStruct->itemAction)
		{
			// Just in case the implementation of the control changes in the
			// future, let's handle the other itemAction types too.
			case ODA_DRAWENTIRE:
			case ODA_FOCUS:
			case ODA_SELECT:
				  DrawListViewItem(lpDrawItemStruct);
				break;
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
// SelectionMessage : Initalisation pour la notification d'une selection d'item
/////////////////////////////////////////////////////////////////////////////
//
// DrawItem  : parent	-> Fenetre parent ou est transmise la notification
//			   msg		-> Message a transmetre
// Sorties   : aucune	
// Retour    : aucun
// 
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::SelectionMessage(CWnd* parent,UINT msg)
{
	Parent	 = parent;
	Msg		 = msg;
}

/////////////////////////////////////////////////////////////////////////////
// OnItemchanged : Notification de la selection d'un item
/////////////////////////////////////////////////////////////////////////////
//
// DrawItem  : cf. MFC
// Sorties   : aucune	
// Retour    : aucun
// 
/////////////////////////////////////////////////////////////////////////////
void CListCtrlEx::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	if ((pNMListView->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))  && (!NoSelection))
	{
		Index = pNMListView->iItem;
		Item = pNMListView->lParam;
	}
	else
		Item = 0;
	
	if (Parent!=NULL)
		Parent->SendMessage(Msg,Index,Item);
	
	*pResult = 0;
}

void CListCtrlEx::OnSetFocus(CWnd* pOldWnd) 
{
	if (NoSelection)
		pOldWnd->SetFocus();
	else
		CListCtrl::OnSetFocus(pOldWnd);
}

void CListCtrlEx::SelectAll() 
{
	int i;
	
	if (GetItemCount() != 0)
	{
		for(i=0;i<GetItemCount();i++)
			SetItemState(i,LVIS_FOCUSED | LVIS_SELECTED,0xF);
	}
}


void CListCtrlEx::SetStringID(UINT nID)
{
	CString strHeadings;
	strHeadings.LoadString(nID);

	int nPos;
	int nCount=0;

	CString strItem;

	while((nPos = strHeadings.Find(_T(","))) != -1)
	{
		strItem=strHeadings.Left(nPos);

		placeInList(/*WIDTH_INI*/-1,strItem);

		strItem = strHeadings.Mid(nPos+1);
		strHeadings=strItem;
	}

	placeInList(/*WIDTH_INI*/-1,strItem);

}

void CListCtrlEx::placeInList(int width, CString name)
{
	TInfoCol	infoCol;
	infoCol.m_width = width;
	infoCol.m_name	= name;

	m_infoCol.AddTail(infoCol);
}

void CListCtrlEx::InsertColumnHeadings(void* InfoCol, bool bChCol)
{
	if(bChCol==FALSE)
	{
		//Delete data user keep in the node of the list view
		//deleteDataUser();
		DeleteAllItems();
	}

	POSITION	pos;
	int nCount=0;

	TInfoCol	info;

	CListToInfoCol	oldInfoCol;

	//ClearList((void*) &oldInfoCol);
	DeleteColumns();

	for((pos = ((CListToInfoCol*) InfoCol)->GetHeadPosition()); pos!=NULL;)
	{
		info=((CListToInfoCol*) InfoCol)->GetNext(pos);
		AddColumn(info.m_name,nCount++,info.m_width);
	}

	m_nNbColumn = nCount;


}


