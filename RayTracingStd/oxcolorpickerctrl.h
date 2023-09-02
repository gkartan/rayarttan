#if !defined(_OXCOLORPICKERCTRL_H_)
#define _OXCOLORPICKERCTRL_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXPopupBarCtrl.h"

// OXColorPickerCtrl.h : header file
//

// special color specifies that none was chosen
// equivalent to ID_POPUPBAR_DATA_NONE
#define ID_CLRPICK_COLOR_NONE		0xffffffff

// the number of predefined tooltiptext - color pairs in the default table
#define CLRPICK_DEFINEDCOLORS		40


/////////////////////////////////////////////////////////////////////////////
// COXColorPickerCtrl window

class COXColorPickerCtrl : public COXPopupBarCtrl
{
// Construction
public:
	// --- In  :	nColors				-	number of color buttons in the Color Picker 
	//										(doesn't include	default and custom buttons)
	//				nRows				-	number of button rows (cannot be more than the 
	//										number of buttons)
	//				clrDefault			-	color to be associated with default button
	//				sizeButton			-	size of buttons (not applicable for default and 
	//										custom buttons their size are calculated 
	//										automatically and depend on the size of 
	//										Color Picker window)
	//				sDefaultButtonText	-	text to be drawn on default button
	//				sCustomButtonText	-	text to be drawn on custom button
	//				
	// --- Out : 
	// --- Returns:
	// --- Effect : Constructs the object
	COXColorPickerCtrl(UINT nColors=20, UINT nRows=4, 
		COLORREF clrDefault=ID_CLRPICK_COLOR_NONE,
		CSize sizeButton=CSize(18,18),
		CString sDefaultButtonText=_T("Default"),
		CString sCustomButtonText=_T("Custom..."));

// Data
protected:
	// array of predefined colors used in the control by default
	static COLORREF m_defaultArrColor[];

	// array of predefined tooltip - color pairs used in the control by default
	static ButtonToolTipTable m_defaultArrToolTipText[];

// data for inner use
public:
    COXColorPickerCtrl& operator=(COXColorPickerCtrl& m_ColorCtrl)
	{
		/*m_defaultArrColor=m_ColorCtrl.m_defaultArrColor;
		m_defaultArrToolTipText=m_ColorCtrl.m_defaultArrToolTipText;*/

		return(*this);
	}

// Attributes
public:

// Operations
public:
	// --- In  :	nAlignment	-	color picker control window alignment relatively to 
	//								pParentRect	rectangle if it's not NULL or to parent 
	//								window rectangle otherwise. Can be one of:
	//
	//							ID_POPUPBAR_ALIGNLEFT	-	control's window RightTop will 
	//														be displayed at the LeftBottom 
	//														point of relative rectangle
	//							ID_POPUPBAR_ALIGNRIGHT	-	control's window LeftTop will 
	//														be displayed at the RightTop 
	//														point of relative rectangle
	//							ID_POPUPBAR_ALIGNTOP	-	control's window LeftBottom will 
	//														be displayed at the LeftTop 
	//														point of relative rectangle
	//							ID_POPUPBAR_ALIGNBOTTOM	-	control's window LeftTop will be 
	//														displayed at the LeftBottom 
	//														point of relative rectangle
	//
	//				pParentRect	-	if it's not NULL then it will be used as relative 
	//								rectangle to position Color Picker
	//				sizeOffset	-	size of Color Picker window position offset
	// --- Out : 
	// --- Returns:	TRUE if user selects any button, or FALSE otherwise
	// --- Effect : Displays Color Picker control. To get color of selected button call 
	//				GetSelectedColor function
	virtual BOOL Pick(UINT nAlignment=ID_POPUPBAR_ALIGNBOTTOM, 
		CRect* pParentRect=NULL, CSize sizeOffset=CSize(0,0));


	// --- In  :	nStartFrom			-	index of color in current or system palette to 
	//										start from filling array of colors
	//				bUseSystemPalette	-	if TRUE then color entries will be taken from
	//										system palette (available only in 256 - color 
	//										video regime)
	// --- Out : 
	// --- Returns:	real number of colors included in array of colors
	// --- Effect : fill array of colors with values from current or system palette 
	//				starting from m_nStartFrom color index in the palette
	int PopulateColorTable(UINT nStartFrom=0, BOOL bUseSystemPalette=FALSE);

	// --- In  :	arrIndexes			-	array of indexes of colors in current or system 
	//										palette
	//				nElements			-	the number of elements in arrIndexes array
	//				bUseSystemPalette	-	if TRUE then color entries will be taken from
	//										system palette (available only in 256 - color 
	//										video regime)
	// --- Out : 
	// --- Returns:	real number of colors included in array of colors
	// --- Effect : fill array of colors with values from current or system palette 
	//				starting from m_nStartFrom color index in the palette
	int PopulateColorTable(UINT* arrIndexes, UINT nElements, BOOL bUseSystemPalette=FALSE);


	// --- In  :	clrSelected	-	color associated with button
	// --- Out : 
	// --- Returns:	
	// --- Effect : set selected button using color associated with it
	inline void SetSelectedColor(const COLORREF clrSelected) { 
		SetSelectedData(clrSelected); 
	}

	// --- In  :	
	// --- Out : 
	// --- Returns:	color of selected button
	// --- Effect : 
	inline COLORREF GetSelectedColor() const { return GetSelectedData(); }

	// --- In  :	clrDefault	-	color associated with button
	// --- Out : 
	// --- Returns:	
	// --- Effect : set color to be associated with default button
	inline void SetDefaultColor(const COLORREF clrDefault) { 
		SetDefaultData(clrDefault); 
	}

	// --- In  :	
	// --- Out : 
	// --- Returns:	color of default button
	// --- Effect : 
	inline COLORREF GetDefaultColor() const { return GetDefaultData(); }


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXColorPickerCtrl)
	//}}AFX_VIRTUAL
public:
	virtual ~COXColorPickerCtrl() {} ;

// implementation
protected:
	// Well, the class is for professionals, so we provide as
	// much functionality as we can. You can even populate 
	// array of displayed colors with entries from current palette. 
	// Following function retrieves current system palette
	BOOL GetSystemPalette(CPalette* pPalette);
	// Sometimes current system palette doesn't match all colors we want
	// to show on the control that is a problem if current video mode is 256 colors. 
	// If this is a case then we build our own custom palette that will be saved 
	// in m_customPalette variable and will be realized as appropriate
	BOOL BuildCustomPalette(COLORREF* arrColor, UINT nEntries, CPalette* pPalette);
	BOOL BuildCustomPalette(ButtonDataTable* arrColor, CPalette* pPalette);

	// find index of button in the control
	// 0 - default button
	// 1 ... m_nColors - color button(s)
	// m_nColors+1 - custom button
	virtual void DrawButton(CDC* pDC, UINT nIndex);
	virtual void DrawDefaultButton(CDC* pDC);

	virtual BOOL OnCustomButton();

// Generated message map functions
protected:
	//{{AFX_MSG(COXColorPickerCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(_OXCOLORPICKERCTRL_H_)
