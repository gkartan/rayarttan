/////////////////////////////////////////////////////////////////////////////
// CSCI EXP
// LOGICIEL D'EXPLOITATION DU PRODUIT TRC8050FAX
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

#ifndef _ListCtrlEx_h_
#define _ListCtrlEx_h_

#include <Afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx window
#define WIDTH_INI		0		//largeur par defaut d'une colonne

struct TInfoCol
{
	int		m_width;
	CString	m_name;
};

typedef CList<TInfoCol,TInfoCol&>	CListToInfoCol;

class AFX_EXT_CLASS  CListCtrlEx : public CListCtrl
{
// Attributes
public:
	LPARAM	Item;
	int		Index;
	CWnd*	Parent;
	UINT	Msg;
	BOOL	NoSelection;
	CListToInfoCol	m_infoCol;
	int				m_nNbColumn;	//nombre de colonnes

public:
	// Constructeur
	CListCtrlEx();
	// detructeur
	virtual ~CListCtrlEx();

	// Recupere le pointeur sur item selectionne
	LPARAM GetSelectedItem() { return Item; };
	// Recupere l'index de l'item selectionne
	int	 GetSelectedIndex() { return Index; };
	// Initalisation mpour la notification
	void SelectionMessage(CWnd* parent,UINT msg);

	void SetNoSelection(BOOL mode) { NoSelection = mode; };

// Operations
public:
	// Ajout de plusieurs colonnes
	BOOL AddColumn(LPCTSTR strItem,...);
	// Ajout d'une colonne à une position déterminée
	BOOL AddColumn(LPCTSTR strItem,int nItem,int cx = -1,int nFmt = LVCFMT_LEFT, int nSubItem = -1,
				   int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM);
	// Ajout d'un item
	BOOL AddItem(int nItem, LPCTSTR strItem,int nImageIndex=-1, LPARAM data=0);
	// Ajout d'infos sur plusieurs colonnes pour un item donné
	BOOL AddItemInfo(int nItem, LPCTSTR strItem, ...);
	// Ajout d'une info pour un item donné à une colonne
	BOOL AddItemInfo(int nItem, int nSubItem, LPCTSTR strItem);
	// Dessine l'item demande pour une OWNERDRAW ListCtrl
	BOOL SetItemImage(int nItem, int nImage);
	// Change l'image d'un item donné
	void DrawListViewItem(LPDRAWITEMSTRUCT lpDrawItem);
	// Ajout de la chaine "..." si la colonne est trop etroite
	CString CalcStringEllipsis(CDC* dc, CString s, UINT uColWidth);
	// Change la taille de la colonne
	void SetColumnSize(int idx,int cx);
	// Retourne la taille de la colonne
	int GetColumnSize(int idx);
	// Supprimme toutes le colonnes
	void DeleteColumns();
	// Sélectionne tout les éléments
	void SelectAll();

	void	SetStringID(UINT nID);
	void	InsertColumnHeadings(void* InfoCol, bool bChCol);
	void	placeInList(int width, CString name);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx)

	// Affiche l'item demande
	virtual void DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct );

	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx)
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif

/////////////////////////////////////////////////////////////////////////////
