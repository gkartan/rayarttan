#ifndef _RENDERINGWND
#define _RENDERINGWND

#include <list>

#include "BaseColor.h"
#include "resource.h"

typedef CBaseColor<unsigned char> BaseColorChar;

class CRenderingWnd : public CWnd
{
// Construction
public:
	CRenderingWnd(BOOL bAutoDelete = TRUE);

// Attributes
public:
	static LPCTSTR m_lpszClassName;

	unsigned long	m_Width;
	unsigned long	m_Height;
	CBitmap			m_Bitmap;
	CDC				m_dcMem;
	bool			m_bFirst;
	bool			m_bInit;
	bool			m_bChangeSize;
	OLE_COLOR		m_couleurFond;

	///Valeurs temporaires
	unsigned long	m_CurY;
	std::list<BaseColorChar> m_ListColor;

// Operations
public:
	void Init();
	void Draw(CDC& dc);
	void	SetColor(unsigned long y,
					 std::list<BaseColorChar>&);
	void	InitBitmap();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawWnd)
	public:
	virtual BOOL Create(DWORD dwExStyle, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRenderingWnd();

protected:
	BOOL m_bAutoDelete;

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawWnd)
	afx_msg LRESULT  OnDisplayPixel(WPARAM wparam,LPARAM lparam);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	
