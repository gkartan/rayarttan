#if !defined(AFX_CAMERAPAGE_H__2DF2D6BF_B431_46DE_A30F_5A3A61A966F2__INCLUDED_)
#define AFX_CAMERAPAGE_H__2DF2D6BF_B431_46DE_A30F_5A3A61A966F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CameraPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCameraPage dialog
#include "CoordIhm.h"
#include "FrontalCamera.h"

class CCameraPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCameraPage)

// Construction
public:
	CCameraPage();
	~CCameraPage();

// Dialog Data
	//{{AFX_DATA(CCameraPage)
	enum { IDD = IDD_CAMERA_PAGE };
	CComboBox	m_sCameraTypeCtrl;
	CString	m_sCameraType;
	double	m_IhmFocal;
	double	m_IhmWidth;
	double	m_IhmHeight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCameraPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	CCoordIhm		m_Position;
	CCoordIhm		m_LookAt;
	CCoordIhm		m_Up;
	CFrontalCamera	*m_pCamera;

	bool			m_bEnable;

public:
	inline		CCoord GetPosition() {return m_Position;}
	inline		CCoord GetLookAt() {return m_LookAt;}
	inline		CCoord GetUp() {return m_Up;}
	inline		void SetPosition(const CCoord& coord) {m_Position=coord;}
	inline		void SetLookAt(const CCoord& coord) {m_LookAt=coord;}
	inline		void SetUp(const CCoord& coord)		{m_Up=coord;}
	//inline		ENUM_CAMERA_TYPE GetCameraType();

	void				Update(CFrontalCamera*);
	void				Update();
	void				SetEnableWindow(bool	bEnable)	{m_bEnable=bEnable;}


protected:
	void		EnableWindows();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCameraPage)
	afx_msg void OnKillfocusCamposx();
	afx_msg void OnKillfocusCamposy();
	afx_msg void OnKillfocusCamposz();
	afx_msg void OnKillfocusCamlookx();
	afx_msg void OnKillfocusCamlooky();
	afx_msg void OnKillfocusCamlookz();
	afx_msg void OnKillfocusCamupx();
	afx_msg void OnKillfocusCamupy();
	afx_msg void OnKillfocusCamupz();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokCamtype();
	afx_msg void OnKillfocusFocalevalue();
	afx_msg void OnKillfocusScreenheight();
	afx_msg void OnKillfocusScreenwidth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERAPAGE_H__2DF2D6BF_B431_46DE_A30F_5A3A61A966F2__INCLUDED_)
