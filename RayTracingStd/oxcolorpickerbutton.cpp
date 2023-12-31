#include "stdafx.h"
#include "OXColorPickerButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void AFXAPI DDX_ColorPicker(CDataExchange *pDX, int nIDC, COLORREF& clr)
{
    HWND hWnd=pDX->PrepareCtrl(nIDC);
    ASSERT(hWnd!=NULL);                
    
    COXColorPickerButton* pButton=(COXColorPickerButton*)CWnd::FromHandle(hWnd);
    if(pDX->m_bSaveAndValidate)
    {
        clr=pButton->GetColor();
    }
    else 
    {
        pButton->SetColor(clr);
    }
}

IMPLEMENT_DYNAMIC(COXColorPickerButton, COXBitmapButton)

// Member functions ---------------------------------------------------------
// public:

// ... The number of pixels the dropdown arrow rect is offset from the button border
CPoint COXColorPickerButton::m_ptColorBandOffset = CPoint(-5,-2);

BEGIN_MESSAGE_MAP(COXColorPickerButton, COXBitmapButton)
	//{{AFX_MSG_MAP(COXColorPickerButton)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

COXColorPickerButton::COXColorPickerButton(UINT nColors, UINT nRows, 
										   COLORREF m_clrDefault,
										   CSize sizeButton,
										   CString sDefaultButtonText,
										   CString sCustomButtonText):
	m_colorPicker(nColors, nRows, m_clrDefault, sizeButton, 
		sDefaultButtonText, sCustomButtonText)
{
	m_nColorBandHeight=5;
	m_clr=ID_CLRPICK_COLOR_NONE;
	SetStyleEx(OXBB_EX_DROPDOWN);

	m_bCreatedExplicitly=FALSE;
}


COXColorPickerButton::~COXColorPickerButton()
{
}


int COXColorPickerButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXBitmapButton::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}
	


	if(!::IsWindow(m_colorPicker.m_hWnd))
	{
		if(!m_colorPicker.Create(this))
		{
			TRACE(_T("COXColorPickerButton::OnCreate: Creation of COXColorPickerCtrl failed"));
			return -1;
		}
	}

	return 0;
}

void COXColorPickerButton::PreSubclassWindow() 
{

	
	if(!::IsWindow(m_colorPicker.m_hWnd) && !m_bCreatedExplicitly)
	{
		VERIFY(m_colorPicker.Create(this));
	}

	COXBitmapButton::PreSubclassWindow();
}

void COXColorPickerButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct != NULL);

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT nState = lpDrawItemStruct->itemState;
	CRect itemRect = lpDrawItemStruct->rcItem;
	CRect buttonRect;
	CRect imageRect;
	CRect textRect;
	CRect arrowRect=itemRect;
	CRect colorBandRect=itemRect;

	// Adjust the state for a possible pseudo-disable mode
	if (IsWindowEnabled())
		nState &= ~ODS_DISABLED;
	else
		nState |= ODS_DISABLED;

	// First distribute the available space (image etc)
	CRect rectFree=itemRect;
	rectFree.right-=GetReservedSpace().cx;
	rectFree.bottom-=GetReservedSpace().cy;
	arrowRect=rectFree;
	DistributeSpace(nState, rectFree, buttonRect, imageRect, textRect);

	// ... Select and realize palette
	CPalette* pOldPalette = NULL;
	SelectPalette(pDC, nState, buttonRect, pOldPalette);

	// ... Draw the button borders 
	DrawButton(pDC, nState, itemRect);
	// ... Draw the image in its correct state
	DrawImage(pDC, nState, &m_imageList, imageRect);
	DrawText(pDC, nState, GetText(), textRect);

	if(HasDropDownArrow())
	{
		arrowRect.left=arrowRect.right;
		arrowRect.right=arrowRect.left+(m_nDropDownArrowWidth-m_ptArrowOffset.x);
		arrowRect.bottom+=m_nColorBandHeight>0 ? 
			m_nColorBandHeight-m_ptColorBandOffset.y : 0;
		arrowRect.InflateRect(0,m_ptArrowOffset.y,m_ptArrowOffset.x,m_ptArrowOffset.y);
		DrawDropDownArrow(pDC,nState,arrowRect);
	}
	else
	{
		arrowRect.left=arrowRect.right;
	}

	if(m_nColorBandHeight>0)
	{
		colorBandRect.right=arrowRect.left;
		if(imageRect.IsRectEmpty() && textRect.IsRectEmpty())
		{
			colorBandRect.InflateRect(m_ptImageOffset.x,m_ptImageOffset.y);
		}
		else
		{
			colorBandRect.top=rectFree.bottom+m_ptTextOffset.x-m_ptColorBandOffset.y+1;
			colorBandRect.bottom=colorBandRect.top+m_nColorBandHeight;
			colorBandRect.InflateRect(m_ptColorBandOffset.x,0);
		}
		DrawColorBand(pDC,nState,colorBandRect);
	}

	if (nState & ODS_FOCUS)
	{
		// ... Draw a focus rectangle on top of the button and image
		DrawFocusRectangle(pDC, nState, itemRect, imageRect);
	}

	// adjust the position of animate control window if any AVI was loaded
    if (::IsWindow(m_animateCtrl))
	{
		m_animateCtrl.SetWindowPos(NULL,imageRect.left+1,imageRect.top+1,0,0,
			SWP_NOSIZE|SWP_NOZORDER);
		m_animateCtrl.Invalidate();
	}
    
	// ... Deselect palette
	RestorePalette(pDC, nState, buttonRect, pOldPalette);
}

void COXColorPickerButton::DrawColorBand(CDC* pDC, UINT nState, CRect colorBandRect)
{
	COLORREF clrShadow=::GetSysColor(COLOR_BTNSHADOW);
	CRect rect=colorBandRect;
	
	if ((GetStateEx()&OXBB_STATE_CHECKED)==OXBB_STATE_CHECKED)
	{
		rect+=m_ptDownOffset;
	}
	else if ((nState&ODS_SELECTED)==ODS_SELECTED)
	{
		rect+=m_ptDownOffset;
	}

	CBrush brushFrame(clrShadow);
	pDC->FrameRect(&rect,&brushFrame);
	rect.DeflateRect(1,1);

	if(m_clr!=ID_CLRPICK_COLOR_NONE && (nState&ODS_DISABLED)!=ODS_DISABLED)
	{
//		CBrush brush(PALETTERGB(GetRValue(m_clr),GetGValue(m_clr),GetBValue(m_clr)));
		CBrush brush(m_clr);
		pDC->FillRect(&rect,&brush);
	}
}

void COXColorPickerButton::OnDropDown()
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(IsDropDownButton());

	ASSERT(::IsWindow(m_colorPicker.m_hWnd));

	m_colorPicker.SetSelectedColor(m_clr);
	if(m_colorPicker.Pick(((GetStyleEx()&OXBB_EX_DROPDOWNRIGHT)==
		OXBB_EX_DROPDOWNRIGHT) ? ID_POPUPBAR_ALIGNRIGHT : ID_POPUPBAR_ALIGNBOTTOM))
	{
		m_clr=m_colorPicker.GetSelectedColor();
		Invalidate();
	}

}

CSize COXColorPickerButton::GetReservedSpace()
{
	CSize sizeReserved=COXBitmapButton::GetReservedSpace();

	if(m_nColorBandHeight>0)
	{
		sizeReserved.cy+=m_nColorBandHeight-m_ptColorBandOffset.y;
	}

	return sizeReserved;
}

void COXColorPickerButton::SetColor(COLORREF clr, BOOL bRedraw/*=TRUE*/) 
{ 
	m_clr=clr;
		
	if(bRedraw && ::IsWindow(m_hWnd))
	{
		Invalidate();
	}
}

