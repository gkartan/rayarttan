#if !defined(AFX_RENDERINGDOC_H__B4C736C3_EBA7_489D_9E6E_44780F28FBA5__INCLUDED_)
#define AFX_RENDERINGDOC_H__B4C736C3_EBA7_489D_9E6E_44780F28FBA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenderingDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRenderingDoc document
#include "RenderStructure.h"

class CRenderingDoc : public CDocument
{
protected:
	CRenderingDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRenderingDoc)

// Attributes
public:
	CRenderStructure		m_RenderStructure;///Elements 
	CString					m_Name;

// Operations
public:
	inline CRenderStructure*		GetRenderStructure() {return &m_RenderStructure;}
	inline void	InitializeStructure()	{m_RenderStructure.SetDefault();}
	inline void SetName(CString str)	{m_Name=str;}
	inline CString GetName()			{return(m_Name);}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRenderingDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRenderingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRenderingDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENDERINGDOC_H__B4C736C3_EBA7_489D_9E6E_44780F28FBA5__INCLUDED_)
