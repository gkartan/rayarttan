#ifndef __OXCOLORPICKERBUTTON_H__
#define __OXCOLORPICKERBUTTON_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXBitmapButton.h"
#include "OXColorPickerCtrl.h"


// The following function was introduced in order to be specifically used in 
// DoDataExchange function of any Dialog or FormView based application for 
// Color Picker buttons. 
void AFXAPI DDX_ColorPicker(CDataExchange *pDX, int nIDC, COLORREF& clr);

class COXColorPickerButton : public COXBitmapButton
{
DECLARE_DYNAMIC(COXColorPickerButton);

// Data members -------------------------------------------------------------
public:
	COXColorPickerButton(COXColorPickerButton &m_ColorButton)
	{
		*this=m_ColorButton;
	}

protected:
	// offset for color band to be drawn on the button
	static CPoint m_ptColorBandOffset;

	// height of color band to be drawn on the button
	UINT m_nColorBandHeight;

	// color associated with the button
	COLORREF m_clr;

	// color picker control used to pick color
	COXColorPickerCtrl m_colorPicker;

	// flag that specifies that button has been created explicitly 
	BOOL m_bCreatedExplicitly;


public:
	COXColorPickerButton& operator=(COXColorPickerButton& m_ColorButton)
	{
		//m_ptColorBandOffset = m_ColorButton.m_ptColorBandOffset;
		m_nColorBandHeight	= m_ColorButton.m_nColorBandHeight;
		m_clr				= m_ColorButton.m_clr;
		m_colorPicker		= m_ColorButton.m_colorPicker;
		m_bCreatedExplicitly= m_ColorButton.m_bCreatedExplicitly;

		return(*this);
	}

// Member functions ---------------------------------------------------------
public:
	// --- In  :	nButtons			-	number of buttons in the popup bar (doesn't 
	//										include	default and custom buttons)
	//				nRows				-	number of button rows (cannot be more than the 
	//										number of buttons)
	//				dwDefault			-	value to be associated with default button
	//				sizeButton			-	size of buttons (not applicable for default and 
	//										custom buttons their size are calculated 
	//										automatically and depend on the size of 
	//										Popup Bar window)
	//				sDefaultButtonText	-	text to be drawn on default button
	//				sCustomButtonText	-	text to be drawn on custom button
	//				
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructs the object. All the arguments used to initiate 
	//				COXColorPickerCtrl control
	COXColorPickerButton(UINT nColors=40, UINT nRows=4, 
		COLORREF m_clrDefault=ID_CLRPICK_COLOR_NONE,
		CSize sizeButton=CSize(18,18),
		CString sDefaultButtonText=_T("Default"),
		CString sCustomButtonText=_T("Custom..."));


	inline BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, 
		CWnd* pParentWnd, UINT nID) {
		m_bCreatedExplicitly=TRUE;
		return COXBitmapButton::Create(lpszCaption,dwStyle,rect,pParentWnd,nID);
	}


	// --- In  :	
	// --- Out : 
	// --- Returns: size of reserved space (from the bottom and right) that shouldn't be
	//				filled withh button's image or text
	// --- Effect : helper function
	virtual CSize GetReservedSpace();


	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect : Destructor of the object
	virtual ~COXColorPickerButton();


	// --- In  :
	// --- Out : 
	// --- Returns:	pointer to COXColorPickerCtrl object associated with button
	// --- Effect : 
	inline COXColorPickerCtrl* GetColorPickerCtrl() { return &m_colorPicker; }


	// --- In  :	nColorBandHeight	-	height of color band in pixels
	// --- Out : 
	// --- Returns:	
	// --- Effect : set the height of color band. By default it is set to 5
	inline void SetColorBandHeight(UINT nColorBandHeight) { 
		m_nColorBandHeight=nColorBandHeight; 
	}
	
	// --- In  :
	// --- Out : 
	// --- Returns:	the height of color band
	// --- Effect : 
	inline UINT GetColorBandHeight() { return m_nColorBandHeight; }


	// --- In  :	clr			-	color to be associated with the button
	//				bRedraw		-	if TRUE then button will be redrawn
	// --- Out :	
	// --- Returns:	
	// --- Effect : associate button with color
	void SetColor(COLORREF clr, BOOL bRedraw=TRUE);

	// --- In  :	
	// --- Out :	
	// --- Returns:	color associated with button
	// --- Effect : 
	inline COLORREF GetColor() { return m_clr; }

	// --- In  :	clrDefault	-	color that will be used in associated 
	//								COXColorPickerCtrl as default
	// --- Out :	
	// --- Returns:	
	// --- Effect : set default color of associated COXColorPickerCtrl object
	inline void SetDefaultColor(COLORREF clrDefault) { 
		m_colorPicker.SetDefaultData(clrDefault); 
	}

	// --- In  :	
	// --- Out :	
	// --- Returns:	default color of associated COXColorPickerCtrl object
	// --- Effect : 
	inline COLORREF GetDefaultColor() { return m_colorPicker.GetDefaultData(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXColorPickerButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

public:
	// we provide our implementation of this virtual function to display
	// COXColorPickerCtrl
	virtual void OnDropDown();

	// virtual functions that draws color band
	virtual void DrawColorBand(CDC* pDC, UINT nState, CRect colorBandRect);

	//{{AFX_MSG(COXColorPickerButton)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

#endif // __OXCOLORPICKERBUTTON_H__
// ==========================================================================
