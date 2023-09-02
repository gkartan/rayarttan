///////////////////////////////////////////////////////////////////////////////

#ifndef __OXBITMAPBUTTON_H__
#define __OXBITMAPBUTTON_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXBitmapButtonRes.h"

// The maximum number of images we have to build per bitmap button
#define OX_MAX_IMAGE_COUNT 5

#ifndef WM_OX_APP
// You can redefine WM_OX_APP by defining it before including this file
#define WM_OX_APP WM_APP + 100
#endif
#define WM_CHECK_TRACK_LOOK			(WM_OX_APP + 100)

// dropdown notification sent to parent window 
#define OXBBN_DROPDOWN				(WM_OX_APP + 110)
// toggle notification sent to parent window 
#define OXBBN_TOGGLE				(WM_OX_APP + 121)

// special extended style
#define	OXBB_EX_DROPDOWN			0x00000001
#define	OXBB_EX_TOGGLE				0x00000002
#define	OXBB_EX_DROPDOWNRIGHT		0x00010000
#define	OXBB_EX_DROPDOWNNOARROW		0x00020000
#define	OXBB_EX_TOGGLE3STATE		0x00040000

// special state
#define	OXBB_STATE_CHECKED			0x00000001
#define	OXBB_STATE_INDETERMINATE	0x00000002


// tooltip ID
#define OXBB_TOOLTIP_ID				1000


BOOL CALLBACK CallbackDrawState(HDC hdc, LPARAM lData, WPARAM wData, int cx, int cy);
BOOL CALLBACK CallbackGrayString(HDC hdc, LPARAM lData, int nCount);

// Next function was introduced to be specifically used in DoDataExchange function
// of any Dialog or FormView based application for Toogle buttons. Parameter value 
// can be one of the next:
//		0	-	unchecked
//		1	-	checked
//		2	-	indeterminate
void AFXAPI DDX_Toggle(CDataExchange *pDX, int nIDC, int& value);

class COXBitmapButton : public CButton
{
DECLARE_DYNAMIC(COXBitmapButton);

// Data members -------------------------------------------------------------
public:

protected:
	// control to play AVI file if any was loaded
    CAnimateCtrl	m_animateCtrl;
	// TRUE if currently playing AVI file
    BOOL m_bPlaying;

	CImageList		m_imageList;
	CPalette		m_palette;
	COLORREF		m_textColor;
	CFont			m_textFont;
	CToolTipCtrl	m_toolTip;

	BOOL	m_bTrackLook;
	BOOL	m_bMouseOverButton;
	BOOL	m_bMouseDown;

	BOOL	m_bHyperLook;
	CImageList m_backgroundImage;
	BOOL	m_bBackgroundGrabbed;
	UINT	m_nDefaultCursorID;
	HCURSOR m_hDefaultCursor;
	UINT	m_nDisabledCursorID;
	HCURSOR m_hDisabledCursor;

	BOOL	m_bPseudoDisableMode;
	BOOL	m_bEnabled;
	BOOL	m_bHasTabStop;

	CPoint m_ptImageOffset;
	CPoint m_ptTextOffset;
	CPoint m_ptOuterFocusOffset;
	CPoint m_ptInnerFocusOffset;
	CSize  m_hyperFocusSize;
	CPoint m_ptDownOffset;
	CPoint m_ptCheckedOffset;
	CPoint m_ptHyperOffset;
	CPoint m_ptArrowOffset;

	static const int m_nNormalImageIndex;
	static const int m_nInactiveImageIndex;
	static const int m_nDisabledImageIndex;

	static COLORREF m_defaultButtonColor;

	DWORD m_dwStyleEx;
	int m_nDropDownArrowWidth;
	
	DWORD m_dwStateEx;

private:
	
// Member functions ---------------------------------------------------------
public:
	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect: Constructs the object
	COXBitmapButton();


	// --- In  :	lpszBitmapResource	-	bitmap resource string
	//				nIDBitmapResource	-	bitmap resource ID
	//				bResize				-	whether to resize the button to 
	//										fit the size of bitmap and text
	//				crMask				-	mask color to use for the bitmap
	//										(this color of the bitmap will be 
	//										shown transparently)
	// --- Out : 
	// --- Returns: TRUE if bitmap was loaded successfully 
	// --- Effect: loads the bitmap from resource
	BOOL LoadBitmap(LPCTSTR lpszBitmapResource, BOOL bResize = TRUE, 
		COLORREF crMask = CLR_NONE);
	inline BOOL LoadBitmap(UINT nIDBitmapResource, BOOL bResize = TRUE, 
		COLORREF crMask = CLR_NONE) { 
		return LoadBitmap(MAKEINTRESOURCE(nIDBitmapResource),bResize,crMask); 
	}


	// --- In  :	lpszBitmapResource	-	bitmap resource string
	//				nIDBitmapResource	-	bitmap resource ID
	//				crMask				-	mask color to use for the bitmap
	//										(this color of the bitmap will be 
	//										shown transparently)
	// --- Out : 
	// --- Returns: TRUE if bitmap was loaded successfully 
	// --- Effect: loads the bitmap from resource
	BOOL LoadInactiveBitmap(LPCTSTR lpszBitmapResource);
	inline BOOL LoadInactiveBitmap(UINT nIDBitmapResource) { 
		return LoadInactiveBitmap(MAKEINTRESOURCE(nIDBitmapResource)); 
	}


	// --- In  :	lpszBitmapResource	-	bitmap resource string
	//				nIDBitmapResource	-	bitmap resource ID
	//				crMask				-	mask color to use for the bitmap
	//										(this color of the bitmap will be 
	//										shown transparently)
	// --- Out : 
	// --- Returns: TRUE if bitmap was loaded successfully 
	// --- Effect: loads the bitmap from resource
	BOOL LoadDisabledBitmap(LPCTSTR lpszBitmapResource);
	inline BOOL LoadDisabledBitmap(UINT nIDBitmapResource) { 
		return LoadDisabledBitmap(MAKEINTRESOURCE(nIDBitmapResource)); 
	}


	// --- In  :	lpszIconResource	-	icon  resource string
	//				nIDIconResource		-	icon  resource ID
	//				bResize				-	whether to resize the button to 
	//										fit the size of bitmap and text
	//				nWidth				-	width of the icon
	//				nHeight				-	height of the icon
	// --- Out : 
	// --- Returns: TRUE if icon was loaded successfully 
	// --- Effect: loads the icon from resource
	BOOL LoadIcon(LPCTSTR lpszIconResource, BOOL bResize = TRUE,
		UINT nWidth = 0, UINT nHeight = 0);
	inline BOOL LoadIcon(UINT nIDIconResource, BOOL bResize = TRUE,
		UINT nWidth = 0, UINT nHeight = 0) {
		return LoadIcon(MAKEINTRESOURCE(nIDIconResource),bResize,nWidth,nHeight); 
	}


	// --- In  :	lpszIconResource	-	icon  resource string
	//				nIDIconResource		-	icon  resource ID
	//				nWidth				-	width of the icon
	//				nHeight				-	height of the icon
	// --- Out : 
	// --- Returns: TRUE if icon was loaded successfully 
	// --- Effect: loads the icon from resource
	BOOL LoadInactiveIcon(LPCTSTR lpszIconResource, UINT nWidth = 0, UINT nHeight = 0);
	inline BOOL LoadInactiveIcon(UINT nIDIconResource,UINT nWidth = 0, UINT nHeight = 0) {
		return LoadInactiveIcon(MAKEINTRESOURCE(nIDIconResource),nWidth,nHeight); 
	}


	// --- In  :	lpszIconResource	-	icon  resource string
	//				nIDIconResource		-	icon  resource ID
	//				nWidth				-	width of the icon
	//				nHeight				-	height of the icon
	// --- Out : 
	// --- Returns: TRUE if icon was loaded successfully 
	// --- Effect: loads the icon from resource
	BOOL LoadDisabledIcon(LPCTSTR lpszIconResource, UINT nWidth = 0, UINT nHeight = 0);
	inline BOOL LoadDisabledIcon(UINT nIDIconResource, UINT nWidth = 0, UINT nHeight = 0) {
		return LoadDisabledIcon(MAKEINTRESOURCE(nIDIconResource),nWidth,nHeight); 
	}


	// --- In  :	nIDAviResource		-	AVI resource ID
	//				lpszFileName		-	the name of the AVI file
	//				bResize				-	whether to resize the button to 
	//										fit the size of bitmap and text
	// --- Out : 
	// --- Returns: TRUE if AVI was loaded successfully 
	// --- Remarks: you have to set either ID or FileName, if both are not NULL
	//				then we use lpszFileName as valid parameter
	//
	// Animation controls can play only simple AVI clips. Specifically, 
	// the clips to be played by an animation control must meet the following 
	// requirements:
	//		- There must be exactly one video stream and it must have at least 
	//			one frame.
	//		- There can be at most two streams in the file (typically the other 
	//			stream, if present, is an audio stream, although the animation 
	//			control ignores audio information).
	//		- The clip must either be uncompressed or compressed with RLE8 
	//			compression. 
	//		- No palette changes are allowed in the video stream. 
	BOOL LoadAvi(UINT nIDAviResource, LPCTSTR lpszFileName = NULL, BOOL bResize = TRUE);

	
	// --- In  :	bResize				-	whether to resize the button to 
	//										fit the size of bitmap and text
	// --- Out : 
	// --- Returns: TRUE if successful or FALSE otherwise
	// --- Effect: remove any images (bitmaps, icons or avi) previously set to control
	BOOL RemoveImage(BOOL bResize = TRUE);

	////////////////////////////

	// --- In  : 
	// --- Out : 
	// --- Returns: The palette of the bitmap button
	//				 This object is valid after a successful LoadBitmap or LoadIcon
	// --- Effect: 
	CPalette* GetPalette();


	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect: Sizes the button to fit its contents (image and text)
	virtual void SizeToContent();

	
	// --- In  :
	// --- Out : 
	// --- Returns: Whether the track look mode is enabled
	// --- Effect: 
	BOOL GetTrackLook() const;


	// --- In  : bTrackLook : Whether enable or disable the track look mode
	// --- Out : 
	// --- Returns: Whether is was successful or not
	// --- Effect: 
	BOOL SetTrackLook(BOOL bTrackLook = TRUE);


	// --- In  : nAlignment : The horizontal alignment of the image and text
	//						  (BS_LEFT, BS_CENTER or BS_RIGHT)
	// --- Out : 
	// --- Returns: 
	// --- Effect: 
	void SetHorizontalAlignment(DWORD nAlignment = BS_CENTER);


	// --- In  : 
	// --- Out : 
	// --- Returns:	The horizontal alignment of the image and text 
	//				(BS_LEFT, BS_CENTER or BS_RIGHT)
	// --- Effect: 
	DWORD GetHorizontalAlignment() const;


	// --- In  : nAlignment : The vertical alignment of the image and text
	//						  (BS_TOP, BS_VCENTER or BS_BOTTOM)
	// --- Out : 
	// --- Returns: 
	// --- Effect: 
	void SetVerticalAlignment(DWORD nAlignment = BS_VCENTER);


	// --- In  : 
	// --- Out : 
	// --- Returns: The vertical alignment of the image and text 
	//				(BS_TOP, BS_VCENTER or BS_BOTTOM)
	// --- Effect: 
	DWORD GetVerticalAlignment() const;


	// --- In  : 
	// --- Out : 
	// --- Returns: The current text color
	// --- Effect: 
	COLORREF GetTextColor() const;

	// --- In  : textColor : The new text color
	// --- Out : 
	// --- Returns: 
	// --- Effect: 
	void SetTextColor(COLORREF textColor);


	// --- In  : 
	// --- Out : 
	// --- Returns: The current text font
	// --- Effect: 
	CFont* GetTextFont();

	// --- In  : pTextFont : The new text font
	// --- Out : 
	// --- Returns: 
	// --- Effect: A copy of the font will be made and stored internally
	void SetTextFont(CFont* pTextFont);


	// --- In  :
	// --- Out : 
	// --- Returns: The text of this button 
	//				 (window text upto but not including the first '\n")
	// --- Effect: 
	CString GetText() const;

	// --- In  : pszText : The new button text
	// --- Out : 
	// --- Returns: 
	// --- Effect: Sets the new text of this button 
	//				(window text upto but not including the first '\n")
	void SetText(LPCTSTR pszText);


	// --- In  :
	// --- Out : 
	// --- Returns: The tool tip text of this button 
	//				 (window text starting from but not including the first '\n")
	// --- Effect: 
	CString GetToolTipText() const;

	// --- In  : pszToolTipText : The new tool tip text
	// --- Out : 
	// --- Returns: 
	// --- Effect: Sets the new text of the tool tip
	//				(window text starting from but not including the first '\n")
	void SetToolTipText(LPCTSTR pszToolTipText);


	// --- In  : 
	// --- Out : 
	// --- Returns: Whether tooltip is enabled for this window
	// --- Effect: 
	BOOL GetToolTip() const;

	// --- In  : 
	// --- Out : 
	// --- Returns: Whether the function was successful
	// --- Effect: Enable tooltip for this window
	BOOL SetToolTip(BOOL bEnable = TRUE);


	// --- In  :
	// --- Out : 
	// --- Returns: The size of button in pixels when it fits its entire contents
	// --- Effect: 
	virtual CSize GetFitButtonSize();


	// --- In  :
	// --- Out : 
	// --- Returns: The present size of the button in pixels
	// --- Effect: 
	CSize GetButtonSize() const;


	// --- In  :
	// --- Out : 
	// --- Returns: The present size of the image in pixels
	// --- Effect: 
	CSize GetImageSize() const;


	// --- In  :
	// --- Out : 
	// --- Returns: The size of the text in pixels
	// --- Effect: 
	CSize GetTextSize(BOOL bCompact=FALSE);


	// --- In  :
	// --- Out : 
	// --- Returns: Whether the hyper look mode is enabled
	// --- Effect: 
	BOOL GetHyperLook() const;


	// --- In  : bHyperLook : Whether enable or disable the hyper look mode
	// --- Out : 
	// --- Returns: Whether is was successful or not
	// --- Effect: 
	BOOL SetHyperLook(BOOL bHyperLook = TRUE);


	// --- In  : 
	// --- Out : 
	// --- Returns: Whether is was successful or not
	// --- Effect: This functions deletes an old copy of the button background 
	//				and grabs a new one.
	//				This function can be useful when you change the background
	//				during the lifetime of a bitmap button
	BOOL RegrabBackground();


	// --- In  : nCursorID : The new cursor ID to use (0 resets to default cursor)
	// --- Out : 
	// --- Returns: Whether the function was successful (the resource was found)
	// --- Effect: Sets the default cursor of this window
	//				Possible values are : IDC_OX_HAND_CURSOR and IDC_OX_NO_HAND_CURSOR
	BOOL SetDefaultCursor(UINT nCursorID = 0);


	// --- In  :
	// --- Out : 
	// --- Returns: The ID of the current default cursor (0 when none is set)
	// --- Effect: 
	UINT GetDefaultCursor() const;


	// --- In  : nCursorID : The new cursor ID to use (0 resets to default cursor)
	// --- Out : 
	// --- Returns: Whether the function was successful (the resource was found)
	// --- Effect: Sets the default cursor of this window
	//				Possible values are : IDC_OX_HAND_CURSOR and IDC_OX_NO_HAND_CURSOR
	//				The pseudo-disable mode must be activated before the
	//				disabled cursor will be shown
	BOOL SetDisabledCursor(UINT nCursorID = 0);

	// --- In  :
	// --- Out : 
	// --- Returns: The ID of the current default cursor (0 when none is set)
	// --- Effect: 
	UINT GetDisabledCursor() const;


	// --- In  :
	// --- Out : 
	// --- Returns: Whether the pseudo-disable mode is active
	// --- Effect: 
	BOOL GetPseudoDisableMode() const;

	// --- In  : bPseudoDisableMode : Whether use pseudo-disable mode or not
	// --- Out : 
	// --- Returns: Whether is was successful or not
	// --- Effect: In pseudo disable mode the control is visually disabled
	//				but not really disabled according to Windows.
	//				This provides the opportunity to receive messages
	//				even when the window is (psudo)disabled.
	//				This mode must be set for the disabled cursor to work.
	BOOL SetPseudoDisableMode(BOOL bPseudoDisableMode = TRUE);


	// --- In  :
	// --- Out : 
	// --- Returns: Whether this window is enabled or not
	// --- Effect: This function also works when in pseudo-disable mode 
	BOOL IsWindowEnabled() const;

	// --- In  : bEnable : Whether to enable (TRUE) or disable (FALSE) this window
	// --- Out : 
	// --- Returns: The old state before the requested state was set
	// --- Effect: This function also works when in pseudo-disable mode 
	BOOL EnableWindow(BOOL bEnable = TRUE);


	// --- In  :
	// --- Out : 
	// --- Returns: Whether the background was grabbed again
	// --- Effect: This functions grabs the image that is currently painted
	//              on the rect used by the bitmap button
	//				When this function is called during OnEraseBkgnd() it will
	//				grab the background of the button
	BOOL AdjustBackground();


	// --- In  :	dwStyleEx	-	extended COXBitmapButton style to set
	//				bRedraw		-	flag that specifies whether the control should
	//								be redrawn or not
	// --- Out : 
	// --- Returns: 
	// --- Effect: This functions sets extended style of COXBitmapButton control.
	void SetStyleEx(DWORD dwStyleEx, BOOL bRedraw=TRUE);

	// --- In  :	
	// --- Out : 
	// --- Returns: extended COXBitmapButton style
	// --- Effect: 
	DWORD GetStyleEx();


	// --- In  :	
	// --- Out : 
	// --- Returns: TRUE if OXBB_EX_DROPDOWN extended style is set
	// --- Effect: helper function
	BOOL IsDropDownButton();


	// --- In  :	
	// --- Out : 
	// --- Returns: TRUE if OXBB_EX_TOGGLE extended style is set
	// --- Effect: helper function
	BOOL IsToggleButton();


	// --- In  :	dwStateEx	-	extended COXBitmapButton state to set
	//				bRedraw		-	flag that specifies whether the control should
	//								be redrawn or not
	// --- Out : 
	// --- Returns: 
	// --- Effect: This functions sets extended state of COXBitmapButton control.
	void SetStateEx(DWORD dwStateEx, BOOL bRedraw=TRUE);
	// --- In  :	
	// --- Out : 
	// --- Returns: extended COXBitmapButton state
	// --- Effect: 
	DWORD GetStateEx();


	// --- In  :	
	// --- Out : 
	// --- Returns: TRUE if button is toggle and has OXBB_STATE_CHECKED state set
	// --- Effect: helper function
	BOOL IsChecked();

	// --- In  :	
	// --- Out : 
	// --- Returns: TRUE if button is toggle and has OXBB_STATE_INDETERMINATE state set
	// --- Effect: helper function
	BOOL IsIndeterminate();


	// --- In  :	
	// --- Out : 
	// --- Returns: size of reserved space (from the bottom and right) that shouldn't be
	//				filled with button's image or text
	// --- Effect: helper function
	virtual CSize GetReservedSpace();

#ifdef _DEBUG
	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect: AssertValid performs a validity check on this object 
	//				by checking its internal state. 
	//				In the Debug version of the library, AssertValid may assert and 
	//				thus terminate the program.
	virtual void AssertValid() const;
	
	// --- In  : dc : The diagnostic dump context for dumping, usually afxDump.
	// --- Out : 
	// --- Returns:
	// --- Effect: Dumps the contents of the object to a CDumpContext object. 
	//				It provides diagnostic services for yourself and 
	//				 other users of your class. 
	//				Note  The Dump function does not print a newline character
	//				 at the end of its output. 
	virtual void Dump(CDumpContext& dc) const;
#endif

	// --- Returns:	image offset from the control border
	// --- Effect: 
	inline CPoint GetImageOffset() { return m_ptImageOffset; }

	// --- In  :	image offset from the control border
	// --- Effect: set image offset
	inline void SetImageOffset(CPoint ptImageOffset) { m_ptImageOffset=ptImageOffset; }


	// --- Returns:	text offset from the control border
	// --- Effect: 
	inline CPoint GetTextOffset() { return m_ptTextOffset; }

	// --- In  :	text offset from the control border
	// --- Effect: set text offset
	inline void SetTextOffset(CPoint ptTextOffset) { m_ptTextOffset=ptTextOffset; }


	// --- Returns:	outer focus rectangle offset from the control border
	// --- Effect: 
	inline CPoint GetOuterFocusOffset() { return m_ptOuterFocusOffset; }

	// --- In  :	outer focus rectangle offset from the control border
	// --- Effect: set outer focus rectangle offset
	inline void SetOuterFocusOffset(CPoint ptOuterFocusOffset) { 
		m_ptOuterFocusOffset=ptOuterFocusOffset; }


	// --- Returns:	inner focus rectangle offset from the control border
	// --- Effect: 
	inline CPoint GetInnerFocusOffset() { return m_ptInnerFocusOffset; }

	// --- In  :	inner focus rectangle offset from the control border
	// --- Effect: set inner focus rectangle offset
	inline void SetInnerFocusOffset(CPoint ptInnerFocusOffset) { 
		m_ptInnerFocusOffset=ptInnerFocusOffset; }


	// --- Returns:	focus rectangle size in hyper look mode
	// --- Effect: 
	inline CSize GetHyperFocusSize() { return m_hyperFocusSize; }

	// --- In  :	focus rectangle size in hyper look mode
	// --- Effect: set focus rectangle size in hyper look mode
	inline void SetHyperFocusSize(CSize hyperFocusSize) { 
		m_hyperFocusSize=hyperFocusSize; }


	// --- Returns:	offset used to show button face in pressed down state
	// --- Effect: 
	inline CPoint GetPressedDownOffset() { return m_ptDownOffset; }

	// --- In  :	offset used to show button face in pressed down state
	// --- Effect: set offset used to show button face in pressed down state
	inline void SetPressedDownOffset(CPoint ptDownOffset) { 
		m_ptDownOffset=ptDownOffset; }


	// --- Returns:	offset used to show button face in checked state
	// --- Effect: 
	inline CPoint GetCheckedOffset() { return m_ptCheckedOffset; }

	// --- In  :	offset used to show button face in checked state
	// --- Effect: set offset used to show button face in checked state
	inline void SetCheckedOffset(CPoint ptCheckedOffset) { 
		m_ptCheckedOffset=ptCheckedOffset; }

	
	// --- Returns:	offset used to show button face when the mouse
	//			    is over the button and  hyper look and track look are set.
	// --- Effect: 
	inline CPoint GetHyperOffset() { return m_ptHyperOffset; }

	// --- In  :	offset used to show button face when the mouse
	//			    is over the button and  hyper look and track look are set.
	// --- Effect: set offset used to show button face when the mouse
	//			    is over the button and  hyper look and track look are set.
	inline void SetHyperOffset(CPoint ptHyperOffset) { m_ptHyperOffset=ptHyperOffset; }


	// --- Returns:	dropdown arrow rectangle offset from the control border
	// --- Effect: 
	inline CPoint GetArrowOffset() { return m_ptArrowOffset; }
	// --- In  :	dropdown arrow rectangle offset from the control border
	// --- Effect: set dropdown arrow rectangle offset from the control border
	inline void SetArrowOffset(CPoint ptArrowOffset) { m_ptArrowOffset=ptArrowOffset; }


	// --- In  :
	// --- Out : 
	// --- Returns:
	// --- Effect: Destructor of the object
	virtual ~COXBitmapButton();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXBitmapButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	virtual void DistributeSpace(UINT nState, CRect itemRect, 
		CRect& buttonRect, CRect& imageRect, CRect& textRect);
	virtual void SelectPalette(CDC* pDC, UINT nState, CRect buttonRect, 
		CPalette*& pOldPalette);
	virtual void DrawButton(CDC* pDC, UINT nState, CRect buttonRect);
	virtual void DrawImage(CDC* pDC, UINT nState, CImageList* pImageList, 
		CRect imageRect);
	virtual void DrawText(CDC* pDC, UINT nState, CString sText, CRect textRect);
	virtual void DrawFocusRectangle(CDC* pDC, UINT nState, CRect buttonRect, 
		CRect bitmapRect);
	virtual void RestorePalette(CDC* pDC, UINT nState, CRect buttonRect, 
		CPalette* pOldPalette);

	BOOL BuildGrayBitmap(LPCTSTR lpszBitmapResource, COLORREF crMask, 
		CBitmap* pGrayBitmap);
	BOOL BuildGrayIcon(LPCTSTR lpszIconResource, HICON* phIcon);
	BOOL MakeGray(LPBITMAPINFOHEADER pBitmapInfoHeader, COLORREF crMask = CLR_NONE);
	BOOL BuildDisabledImage(HICON hSourceIcon, CSize imageSize, HICON& hDestIcon);

	static BOOL GetBitmapPalette(LPCTSTR lpszBitmapResource, CPalette& palette);
	static BOOL GetIconPalette(LPCTSTR lpszIconResource, CPalette& palette);
	static BOOL GetImagePalette(LPBITMAPINFOHEADER pBitmapInfoHeader, CPalette& palette);

	void CheckTrackLook(CPoint point);
	void PostCheckTrackLook();

	static CString GetSubString(LPCTSTR pszFullString, int nSubIndex, TCHAR cDelimiter);
	static CString RemoveAmpersand(LPCTSTR pszText);
	static BOOL LoadBitmap(LPCTSTR lpszBitmapResource, CBitmap& bitmap, 
		CPalette& palette);

	virtual int GetDropDownArrowWidth();
	virtual void DrawDropDownArrow(CDC* pDC, UINT nState, CRect arrowRect);
	virtual void OnDropDown();

	virtual void OnToggle();


	// --- In  :	
	// --- Out : 
	// --- Returns: TRUE if OXBB_STATE_CHECKED is set in result of this function,
	//				or FALSE otherwise
	// --- Effect: toggle between checked and unchecked state
	BOOL Toggle();

	// --- In  :	
	// --- Out : 
	// --- Returns: TRUE if OXBB_EX_DROPDOWN extended style is set and 
	//				OXBB_EX_DROPDOWNNOARROW is not (i.e. dropdown arrow will be drawn)
	// --- Effect: helper function
	BOOL HasDropDownArrow();

	//{{AFX_MSG(COXBitmapButton)
	afx_msg void OnSysColorChange();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCheckTrackLook(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClick(WPARAM wParam, LPARAM lParam);

	virtual afx_msg BOOL OnClicked();

	DECLARE_MESSAGE_MAP()

private:
                   
};

#endif // __OXBITMAPBUTTON_H__
// ==========================================================================
