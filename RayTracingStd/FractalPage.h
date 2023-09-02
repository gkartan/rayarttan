#if !defined(AFX_FRACTALPAGE_H__5DA9D83B_C7C4_4A8F_BFDC_ADFE9D60935B__INCLUDED_)
#define AFX_FRACTALPAGE_H__5DA9D83B_C7C4_4A8F_BFDC_ADFE9D60935B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FractalPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFractalPage dialog
#include "QuaterIhm.h"
#include "CoordIhm.h"
#include "FrontalFractal.h"
#include "FrontalGeometry.h"
#include "FrontalMaterial.h"

class CFractalPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFractalPage)

// Construction
public:
	CFractalPage();
	~CFractalPage();

// Dialog Data
	//{{AFX_DATA(CFractalPage)
	enum { IDD = IDD_FRACTAL_PAGE };
	CComboBox	m_sListTextureCtrl;
	CButton	m_FractalOptimButton;
	CString	m_sFractalFormula;
	CString	m_sFractalDerivate;
	double	m_fNbStep;
	long	m_lMaxIter;
	CString	m_sFractalType;
	double	m_fAngle;
	CString	m_sTextureName;
	double	m_fBoundSize;
	double	m_fBailout;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFractalPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	CCoordIhm			m_Position;
	CCoordIhm			m_Rotation;
	CQuaterIhm			m_InitialValue;
	CFrontalFractal		*m_pFractal;
	CFrontalGeometry	*m_pListGeometry;
	CFrontalMaterial	*m_pMaterial;

	bool				m_ForceDerivate;
	bool				m_bEnable;
public:
	void				SetInitialValue(const CBaseVector<4,double>&value) {m_InitialValue=value;}
	void				SetMaxIter(long MaxIter)		{m_lMaxIter=MaxIter;};
	void				SetNbStep(double Step)			{m_fNbStep=Step;};
	void				SetAngle(double Angle)			{m_fAngle=Angle;};
	void				SetBoundSize(double BoundSize)	{m_fBoundSize=BoundSize;};
	void				SetBailout(double Bailout)		{m_fBailout=Bailout;};
	void				SetFormula(const std::string& Formula ) {m_sFractalFormula=Formula.c_str();};
	void				SetDerivate(const std::string& Formula ) {m_sFractalDerivate=Formula.c_str();};
	void				SetType(const std::string &str) {m_sFractalType=str.c_str();}
	void				SetOptimisation(const bool bOpt) {m_FractalOptimButton.SetCheck(bOpt);}
	void				SetPosition(const CCoord& coord) {m_Position=coord;}
	void				SetRotation(const CCoord& coord) {m_Rotation=coord;}
	CBaseVector<4,double> GetInitialValue()				 {return(m_InitialValue);}
	long				GetMaxIter()					 {return(m_lMaxIter);};
	double				GetNbStep()						 {return(m_fNbStep);};
	double				GetAngle()						 {return(m_fAngle);};
	double				GetBailout()					 {return(m_fBailout);};
	double				GetBoundSize()					 {return(m_fBoundSize);}
	std::string			GetFormula()					 {return(m_sFractalFormula);};
	CCoord				GetPosition()					 {return(m_Position);}
	CCoord				GetRotation()					 {return(m_Rotation);}
	bool				GetRenderOk()					 {return(m_sFractalDerivate.Left(1).Compare("%")!=0);}

	void				Update(CFrontalFractal*,CFrontalGeometry*,CFrontalMaterial*);
	void				Update();

	void				Random();

	void				SetEnableWindow(bool	bEnable)	{m_bEnable=bEnable;}

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFractalPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusFractalformula();
	afx_msg void OnKillfocusFractalcsti();
	afx_msg void OnKillfocusFractalcstj();
	afx_msg void OnKillfocusFractalcstk();
	afx_msg void OnKillfocusFractalcstr();
	afx_msg void OnKillfocusFractaliter();
	afx_msg void OnFractaloptim();
	afx_msg void OnKillfocusFractalstep();
	afx_msg void OnSelendokFractaltype();
	afx_msg void OnBfractaltexture();
	afx_msg void OnKillfocusFractalderivate();
	afx_msg void OnFormulaRecord();
	afx_msg void OnKillfocusFractalangle();
	afx_msg void OnKillfocusFracrotz();
	afx_msg void OnKillfocusFracroty();
	afx_msg void OnKillfocusFracrotx();
	afx_msg void OnKillfocusFracposz();
	afx_msg void OnKillfocusFracposy();
	afx_msg void OnKillfocusFracposx();
	afx_msg void OnSelendokFractaltexture();
	afx_msg void OnKillfocusFractallimit();
	afx_msg void OnChangeFractalderivate();
	afx_msg void OnFormulaDeriveEdit();
	afx_msg void OnKillfocusFractalbailout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRACTALPAGE_H__5DA9D83B_C7C4_4A8F_BFDC_ADFE9D60935B__INCLUDED_)
