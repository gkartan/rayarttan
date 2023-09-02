// FractalPage.cpp : implementation file
//
#pragma warning(disable : 4005)

#include "stdafx.h"
#include "raytracingstd.h"
#include "FractalPage.h"
#include <time.h>
#include "TraceService.h"
#include "IhmConstants.h"
#include "RandomFractal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFractalPage property page

IMPLEMENT_DYNCREATE(CFractalPage, CPropertyPage)

CFractalPage::CFractalPage() : CPropertyPage(CFractalPage::IDD)
{
	//{{AFX_DATA_INIT(CFractalPage)
	m_sFractalFormula = _T("");
	m_sFractalDerivate = _T("");
	m_fNbStep = 0.0;
	m_lMaxIter = 0;
	m_sFractalType = _T("");
	m_fAngle = 0.0;
	m_fBoundSize = 0.0;
	m_fBailout = 0.0;
	//}}AFX_DATA_INIT

	m_pFractal=NULL;

	///Initialise la séquence aléatoire
	srand( (unsigned)time( NULL ) );
	m_ForceDerivate=false;
}

CFractalPage::~CFractalPage()
{
}

void CFractalPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFractalPage)
	DDX_Control(pDX, IDC_FRACTALTEXTURE, m_sListTextureCtrl);
	DDX_Control(pDX, IDC_FRACTALOPTIM, m_FractalOptimButton);
	DDX_Text(pDX, IDC_FRACTALFORMULA, m_sFractalFormula);
	DDX_Text(pDX, IDC_FRACTALDERIVATE, m_sFractalDerivate);
	DDX_Text(pDX, IDC_FRACTALSTEP, m_fNbStep);
	DDX_Text(pDX, IDC_FRACTALITER, m_lMaxIter);
	DDX_CBString(pDX, IDC_FRACTALTYPE, m_sFractalType);
	DDX_Text(pDX, IDC_FRACTALANGLE, m_fAngle);
	DDX_Text(pDX,IDC_FRACTALTEXTURE,m_sTextureName);
	DDX_Text(pDX, IDC_FRACTALLIMIT, m_fBoundSize);
	DDX_Text(pDX, IDC_FRACTALBAILOUT, m_fBailout);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_FRACTALCSTR, m_InitialValue.GetRefX());
	DDX_Text(pDX, IDC_FRACTALCSTI, m_InitialValue.GetRefY());
	DDX_Text(pDX, IDC_FRACTALCSTJ, m_InitialValue.GetRefZ());
	DDX_Text(pDX, IDC_FRACTALCSTK, m_InitialValue.GetRefW());
	DDX_Text(pDX, IDC_FRACPOSX, m_Position.GetRefX());
	DDX_Text(pDX, IDC_FRACPOSY, m_Position.GetRefY());
	DDX_Text(pDX, IDC_FRACPOSZ, m_Position.GetRefZ());
	DDX_Text(pDX, IDC_FRACROTX, m_Rotation.GetRefX());
	DDX_Text(pDX, IDC_FRACROTY, m_Rotation.GetRefY());
	DDX_Text(pDX, IDC_FRACROTZ, m_Rotation.GetRefZ());

}


BEGIN_MESSAGE_MAP(CFractalPage, CPropertyPage)
	//{{AFX_MSG_MAP(CFractalPage)
	ON_EN_KILLFOCUS(IDC_FRACTALFORMULA, OnKillfocusFractalformula)
	ON_EN_CHANGE(IDC_FRACTALFORMULA, OnKillfocusFractalformula)
	ON_EN_KILLFOCUS(IDC_FRACTALCSTI, OnKillfocusFractalcsti)
	ON_EN_KILLFOCUS(IDC_FRACTALCSTJ, OnKillfocusFractalcstj)
	ON_EN_KILLFOCUS(IDC_FRACTALCSTK, OnKillfocusFractalcstk)
	ON_EN_KILLFOCUS(IDC_FRACTALCSTR, OnKillfocusFractalcstr)
	ON_EN_KILLFOCUS(IDC_FRACTALITER, OnKillfocusFractaliter)
	ON_BN_CLICKED(IDC_FRACTALOPTIM, OnFractaloptim)
	ON_EN_KILLFOCUS(IDC_FRACTALSTEP, OnKillfocusFractalstep)
	ON_CBN_SELENDOK(IDC_FRACTALTYPE, OnSelendokFractaltype)
	ON_BN_CLICKED(IDC_BFRACTALTEXTURE, OnBfractaltexture)
	ON_EN_KILLFOCUS(IDC_FRACTALDERIVATE, OnKillfocusFractalderivate)
	ON_BN_CLICKED(IDC_FORMULA_RECORD, OnFormulaRecord)
	ON_EN_KILLFOCUS(IDC_FRACTALANGLE, OnKillfocusFractalangle)
	ON_EN_KILLFOCUS(IDC_FRACROTZ, OnKillfocusFracrotz)
	ON_EN_KILLFOCUS(IDC_FRACROTY, OnKillfocusFracroty)
	ON_EN_KILLFOCUS(IDC_FRACROTX, OnKillfocusFracrotx)
	ON_EN_KILLFOCUS(IDC_FRACPOSZ, OnKillfocusFracposz)
	ON_EN_KILLFOCUS(IDC_FRACPOSY, OnKillfocusFracposy)
	ON_EN_KILLFOCUS(IDC_FRACPOSX, OnKillfocusFracposx)
	ON_CBN_SELENDOK(IDC_FRACTALTEXTURE, OnSelendokFractaltexture)
	ON_EN_KILLFOCUS(IDC_FRACTALLIMIT, OnKillfocusFractallimit)
	ON_EN_CHANGE(IDC_FRACTALDERIVATE, OnChangeFractalderivate)
	ON_BN_CLICKED(IDC_FORMULA_DERIVE_EDIT, OnFormulaDeriveEdit)
	ON_EN_KILLFOCUS(IDC_FRACTALBAILOUT, OnKillfocusFractalbailout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFractalPage message handlers
////////////////////////////////////////////////
//Mise à jour IHM 
void CFractalPage::Update(CFrontalFractal *pFractal,
						  CFrontalGeometry *pListGeometry,
						  CFrontalMaterial *pMaterial)
{
	if(::IsWindow(m_hWnd))
	{
		m_ForceDerivate=pFractal->GetFractal()->GetManualDerivative();
		((CButton*) GetDlgItem(IDC_FORMULA_DERIVE_EDIT))->SetCheck(m_ForceDerivate);
		GetDlgItem(IDC_FRACTALDERIVATE)->EnableWindow(m_ForceDerivate);

		//EnableWindow(true);
		SetPosition(pFractal->GetFractal()->GetTranslate());
		SetRotation(pFractal->GetFractal()->GetRotate());

		///*****
		///Remplissage liste des textures
		m_sListTextureCtrl.ResetContent();


		TypeVectorMaterial::iterator	theIterator;
		for(theIterator=pMaterial->GetListMaterial()->begin();
			theIterator<pMaterial->GetListMaterial()->end();
			theIterator++)
			{
				CString	str;
				str.Format("%s",(*theIterator)->GetName().c_str());
				m_sListTextureCtrl.AddString(str);
			}
		///Fin remplissage
		///Sélection de la texture
		m_sListTextureCtrl.SelectString(0,pFractal->GetFractal()->GetMatiere()->GetName().c_str());
		//m_sListTextureCtrl.SetCurSel(0);

		SetInitialValue(pFractal->GetInitValue());
		SetMaxIter(pFractal->GetMaxIter());
		SetNbStep(pFractal->GetNbStep());
		SetFormula(pFractal->GetStrExpr());
		SetDerivate(pFractal->GetStrExprDerivate());
		SetType(pFractal->GetAlgebraType());
		SetOptimisation(pFractal->GetOptimisation());
		SetAngle(pFractal->GetAngle());
		SetBailout(pFractal->GetFractal()->GetBailout());
		SetBoundSize(pFractal->GetFractal()->GetBoundSize());

		UpdateData(FALSE);
	}

	m_pFractal=pFractal;
	m_pListGeometry=pListGeometry;
	m_pMaterial=pMaterial;
}

void CFractalPage::Update()
{
	UpdateData(TRUE);

	if(m_pFractal!=NULL)
	{
		CBaseFractal	*pOldFractal=m_pFractal->GetFractal();
		///*****
		std::string OldValue=m_sFractalType;
		std::string OldExpr=m_pFractal->GetStrExpr();

		m_pFractal->SetInitValue(GetInitialValue());
		m_pFractal->SetMaxIter(GetMaxIter());
		m_pFractal->SetNbStep(GetNbStep());
		m_pFractal->SetStrExpr(GetFormula());	//le calcul de la dérivée se fait ici
		m_pFractal->SetAngle(GetAngle());
		m_pFractal->GetFractal()->SetBailout(GetBailout());
		m_pFractal->GetFractal()->SetBoundSize(GetBoundSize());
		m_pFractal->GetFractal()->RazTransform();
		m_pFractal->GetFractal()->Translate(CVector(GetPosition()));
		m_pFractal->GetFractal()->Rotate(CVector(GetRotation()));

		//if(OldValue.compare(m_sFractalType)!=0 ||
		//  OldExpr.compare(m_sFractalFormula)!=0)
		if(!m_ForceDerivate)
		{
			int iError=m_pFractal->ChangeType(std::string(m_sFractalType),
								   std::string(m_sFractalFormula),
								   m_pFractal->GetOptimisation());

			switch(iError)
			{
				case -1:
					{
						CString str;
						str.LoadString(IDS_ERROR_DERIVEE);
						SetDerivate(std::string(str.GetBuffer(str.GetLength())));
					}
					break;
				case -2:
					{
						CString str;
						str.LoadString(IDS_ERROR_EXPRESSION);
						SetDerivate(std::string(str.GetBuffer(str.GetLength())));
					}
					break;
				default:
					SetDerivate(m_pFractal->GetStrExprDerivate());
			}
		} else {
			m_pFractal->ChangeType(std::string(m_sFractalType),
								   std::string(m_sFractalFormula),
								   std::string(m_sFractalDerivate),
								   m_pFractal->GetOptimisation());
		}

		///Mise à jour de la dérivée
		UpdateData(FALSE);

		m_pListGeometry->Update(pOldFractal,m_pFractal->GetFractal()); //raz de la fractale puis jout
	}
}

BOOL CFractalPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	if(m_pFractal!=NULL)
	{
		Update(m_pFractal,m_pListGeometry,m_pMaterial);
		UpdateData(FALSE);
	}

	EnableWindow(m_bEnable);
	
	return TRUE;  
}

void CFractalPage::OnKillfocusFractalformula() 
{
	Update();	
}

void CFractalPage::OnKillfocusFractalcsti() 
{
	Update();		
}

void CFractalPage::OnKillfocusFractalcstj() 
{
	Update();		
}

void CFractalPage::OnKillfocusFractalcstk() 
{
	Update();		
}

void CFractalPage::OnKillfocusFractalcstr() 
{
	Update();		
}

void CFractalPage::OnKillfocusFractaliter() 
{
	Update();		
}

void CFractalPage::OnFractaloptim() 
{
	UpdateData(TRUE);

	CBaseFractal	*pOldFractal=m_pFractal->GetFractal();

	m_pFractal->ChangeType(std::string(m_sFractalType),
						   std::string(m_sFractalFormula),
						   bool(m_FractalOptimButton.GetCheck()));

	m_pListGeometry->Update(pOldFractal,m_pFractal->GetFractal()); //raz de la fractale puis jout
}

void CFractalPage::OnKillfocusFractalstep() 
{
	Update();		
}

void CFractalPage::OnSelendokFractaltype() 
{
	Update();		
}

void CFractalPage::Random()
{
	///Prend une valeur initiale au hasard
	m_InitialValue.m_Value[0]=double(rand())/32767.0;
	m_InitialValue.m_Value[1]=double(rand())/32767.0;
	m_InitialValue.m_Value[2]=double(rand())/32767.0;
	m_InitialValue.m_Value[3]=double(rand())/32767.0;
	m_pFractal->SetInitValue(GetInitialValue());

	_TRACE_INFO(_STR("Init Value : X:%.6f - Y:%6f - Z:%.6f - W:%.6f",
				 m_InitialValue.m_Value[0],
				 m_InitialValue.m_Value[1],
				 m_InitialValue.m_Value[2],
				 m_InitialValue.m_Value[3]));


	std::string strFormula=CRandomFractal::Generate();
	std::string strType=CRandomFractal::GenerateType();

	CBaseFractal	*pOldFractal=m_pFractal->GetFractal();

	m_pFractal->ChangeType(strType,
						   strFormula,
						   bool(m_FractalOptimButton.GetCheck()));
	m_pListGeometry->Update(pOldFractal,m_pFractal->GetFractal()); //raz de la fractale puis jout

	if(IsWindow(m_hWnd))
		UpdateData(FALSE);

}

void CFractalPage::OnBfractaltexture() 
{
	CString *pstr=new CString;
	m_sListTextureCtrl.GetWindowText(*pstr);
	AfxGetMainWnd()->PostMessage(MS_OPEN_TEXTURE,(WPARAM) pstr,NULL);

}

void CFractalPage::OnKillfocusFractalderivate() 
{
	Update();
}


//***********Enregistrement de la formule et de sa dérivée dans la bibliothèque
void CFractalPage::OnFormulaRecord() 
{
	FILE *pfile=fopen("derivation.inc","a");
	if(pfile!=NULL)
	{
		std::string	str;
		str=std::string("{\n")+std::string("\t\"")+
			m_sFractalFormula.GetBuffer(m_sFractalFormula.GetLength())+
			std::string("\" \n\t\"")+m_sFractalDerivate.GetBuffer(m_sFractalDerivate.GetLength())+
			std::string("\" \n}");

		fputs(str.c_str(),pfile);
		fclose(pfile);
	} else {
		CString str;
		str.LoadString(IDS_ERROR_SAVEFILE);
		AfxMessageBox(str);
	}
}

void CFractalPage::OnKillfocusFractalangle() 
{
	Update();		
	
}

void CFractalPage::OnKillfocusFracrotz() 
{
	Update();		
	
}

void CFractalPage::OnKillfocusFracroty() 
{
	Update();		
	
}

void CFractalPage::OnKillfocusFracrotx() 
{
	Update();		
	
}

void CFractalPage::OnKillfocusFracposz() 
{
	Update();		
	
}

void CFractalPage::OnKillfocusFracposy() 
{
	Update();		
	
}

void CFractalPage::OnKillfocusFracposx() 
{
	Update();		
	
}

void CFractalPage::OnSelendokFractaltexture() 
{
	UpdateData(TRUE);

	CBaseMatiere* pMatiere=m_pMaterial->GetMaterial(m_sTextureName.GetBuffer(m_sTextureName.GetLength()));
	m_pMaterial->SetCurrentMaterial(pMatiere);
	m_pFractal->GetFractal()->SetMatiere(pMatiere);
}

void CFractalPage::OnKillfocusFractallimit() 
{
	Update();	
}

void CFractalPage::OnChangeFractalderivate() 
{
}

void CFractalPage::OnFormulaDeriveEdit() 
{
	m_ForceDerivate=!m_ForceDerivate;	
	
	GetDlgItem(IDC_FRACTALDERIVATE)->EnableWindow(m_ForceDerivate);
	((CButton*) GetDlgItem(IDC_FORMULA_DERIVE_EDIT))->SetCheck(m_ForceDerivate);
	m_pFractal->GetFractal()->SetManualDerivative(m_ForceDerivate);
}

void CFractalPage::OnKillfocusFractalbailout() 
{
	Update();	
}
