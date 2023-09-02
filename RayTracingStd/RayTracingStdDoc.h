// RayTracingStdDoc.h : interface of the CRayTracingStdDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAYTRACINGSTDDOC_H__69182660_C23D_4B28_859D_4413933A92FB__INCLUDED_)
#define AFX_RAYTRACINGSTDDOC_H__69182660_C23D_4B28_859D_4413933A92FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRayTracingStdDoc : public CDocument
{
protected: // create from serialization only
	CRayTracingStdDoc();
	DECLARE_DYNCREATE(CRayTracingStdDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRayTracingStdDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRayTracingStdDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRayTracingStdDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAYTRACINGSTDDOC_H__69182660_C23D_4B28_859D_4413933A92FB__INCLUDED_)
