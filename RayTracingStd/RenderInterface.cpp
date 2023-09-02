//#pragma warning(disable : 4786)
//#pragma warning(disable : 4275)
//#pragma warning(disable : 4305)
#pragma warning(disable : 4530)
#pragma warning(disable : 4096)
#pragma warning(disable : 4005)

#include "stdafx.h"
#include "stdio.h"
#include "RenderInterface.h"
#include "RenderType.h"
#include "resource.h"		//pour l'affichage du texte dans la boite de dialogue
#define NOMINMAX
#include "ClassicFunctions.h"
#include "IhmConstants.h"

CBaseImage*					CRenderInterface::pImage=NULL;
CBaseCamera*				CRenderInterface::pCamera=NULL;
CBaseListGeometry*			CRenderInterface::pListGeometry=NULL;
TypeVectorLight*			CRenderInterface::pListLight=NULL;
std::string					CRenderInterface::m_InitPath;
std::string					CRenderInterface::m_FileName;
CBaseListGeometry**			CRenderInterface::pListOfListGeometry=NULL;
CRenderStructure*			CRenderInterface::pRenderStructure=NULL;
CPhotonTracer*				CRenderInterface::pPhotonTracer=NULL;		//la photon map
std::string					CRenderInterface::m_ScreenSaverLoadPath;
bool						CRenderInterface::m_FileSave=true;
long						CRenderInterface::m_NbLine=0;
bool						CRenderInterface::m_bContinue=false;
bool						CRenderInterface::m_bIhm=true;

long						CRenderInterface::Number=0;

CRenderInterface::CRenderInterface()
{
}

CRenderInterface::~CRenderInterface()
{
}

int	 CRenderInterface::FindLastNumber()
{
	CFileFind	search;

	CString	swildcard;
	swildcard.Format("%s\\%s*.tif",m_InitPath.c_str(),m_FileName.c_str());

	char *pBuffer=swildcard.GetBuffer(swildcard.GetLength());

	BOOL bWorking=search.FindFile(swildcard);
	bool AuMoinsUn=false;
	while(bWorking)
	{
		bWorking=search.FindNextFile();
		AuMoinsUn=true;
		
	}

	if(AuMoinsUn)
	{
		//calcul le dernier numéro
		CString file=search.GetFilePath();

		CString sChaineLongueur;
		sChaineLongueur.Format("%s\\%s",m_InitPath.c_str(),m_FileName.c_str());

		CString Number=file.Mid(sChaineLongueur.GetLength(),file.ReverseFind('.')-sChaineLongueur.GetLength());

		search.Close();

		return  (atoi(Number.GetBuffer(Number.GetLength()))+1);
	}

	return 0;
}

void CRenderInterface::AfterRender(bool bPartialRender)
{
	if(pImage==NULL)
	{
		return;
	}

	if(m_FileSave)
	{
		Number=FindLastNumber();

		CString	str;
		str.Format("%s\\%s%d",m_InitPath.c_str(),m_FileName.c_str(),Number);

		std::string completestr;

		if(!pImage->SaveFile(std::string(str.GetBuffer(str.GetLength())),completestr))
		{
			CString str;
			str.Format("Erreur sauve : %s",completestr.c_str());
			AfxMessageBox(str);
			createDirectory(m_InitPath.c_str());
			pImage->SaveFile(std::string(str.GetBuffer(str.GetLength())),completestr);
		}

		///Si c'est une sauvegarde partiel -- on sauvegarde caractéristiques
		///dans fichier .part
		CString sFilePart;
		sFilePart.Format("%s\\%s.part",m_InitPath.c_str(),m_FileName.c_str());

		if(bPartialRender)
		{
			CString strsave;
			strsave.Format("%d",m_NbLine);

			WritePrivateProfileString("Properties","Lines",strsave,sFilePart);
			WritePrivateProfileString("Properties","OutputFileName",completestr.c_str(),sFilePart);

		} else {
			//Effacement d'un fichier .part éventuel
			CString strsave("complete");
			CString NameFormula;
			NameFormula.Format("Formula%d",Number);
			WritePrivateProfileString("Properties","State",strsave,sFilePart);
			WritePrivateProfileString("Formula",NameFormula.GetBuffer(NameFormula.GetLength()),pRenderStructure->GetFrontalFractal()->GetFractal()->GetStrExpr().c_str(),sFilePart);
		}

		Number++;
	}

	//pImage->Clear();
}

unsigned long CRenderInterface::LancementRayTracing(void* lpParameter)
{

	if(pCamera!=NULL && pImage!=NULL && pListGeometry!=NULL && pListLight!=NULL)
	{
		StructRenderType *pType=static_cast<StructRenderType *>(lpParameter);

		if(pType!=NULL)
		{
			//Calcul ligne début et fin
			long NbLineCompute=pType->NbLines/pType->TotalThread;

			long BeginLine=0;

			BeginLine=NbLineCompute*pType->NumThread;
			long EndLine=BeginLine+NbLineCompute-1;

			////Si on continue une image on prend la ligne suivante
			////Ne marche qu'en mono-processeur
			if(m_bContinue)
				BeginLine=m_NbLine;


			DWORD Start=GetTickCount();

			pType->bTerminated=false;

			switch(pType->TypeAlgo)
			{

				case ALGO_ANTIALIAS:
				{
					CRenderAdaptativeSampling	Rendering(pCamera,pImage,
														  (pListOfListGeometry[pType->NumThread])->GetVectorGeometry(),
														  *pListLight,
														  pPhotonTracer);
					Rendering.SetAlgo(pRenderStructure->GetStructAlgo());
					Rendering.SetTerminated(&pType->bTerminated);
					Rendering.Render(BeginLine,EndLine);
				}
				break;

				case ALGO_NORMAL:
				default:
				{
					CRenderStdRaytracing	Rendering(pCamera,pImage,
													  (pListOfListGeometry[pType->NumThread])->GetVectorGeometry(),
													  *pListLight,
													  pPhotonTracer);
					Rendering.SetTerminated(&pType->bTerminated);
					Rendering.Render(BeginLine,EndLine);
				}
				break;
			}

			pType->Duree=GetTickCount()-Start;
		}

		ExitThread(0);
	}

	return 0;

}


void	CRenderInterface::Initialize(int Number)
{
	///Génère une liste de géométrie par processeurs
	typedef CBaseListGeometry* P_TypeVectorGeometry;
	pListOfListGeometry=new P_TypeVectorGeometry[Number];

	for(int i=0;i<Number;i++)
	{
		CBaseListGeometry		*pTempListGeometry=new CBaseListGeometry;

		*pTempListGeometry=*pListGeometry;	//Copie de la liste des géometries

		pListOfListGeometry[i]=pTempListGeometry;
	}

	
}

void	CRenderInterface::Destroy(int Number)
{
	if(pListOfListGeometry!=NULL)
	{
		for(int i=0;i<Number;i++)
		{
			if(pListOfListGeometry[i]!=NULL)
				delete pListOfListGeometry[i];
		}

		delete	pListOfListGeometry;
		pListOfListGeometry=NULL;
	}
}

//*****************************************
/////Test si on doit continuer une image
/////Les structure de CRenderInterface doivent être renseignés avant
/////l'appel à cette méthode
/////Sert également à savoir si le fichier a déjà été calculé
bool	CRenderInterface::TestContinue()
{
	CString sFilePart;
	sFilePart.Format("%s\\%s.part",m_InitPath.c_str(),m_FileName.c_str());

	if(fopen(sFilePart.GetBuffer(sFilePart.GetLength()),"r"))
	{
		char sKeyValue[MAX_CHAR_KEYS];
		GetPrivateProfileString("Properties","State","",sKeyValue,MAX_CHAR_KEYS,sFilePart);

		if(strcmp(sKeyValue,"complete")==0)
		{
			m_bContinue=false;
			return false;
		} else {

			m_bContinue=true;

			GetPrivateProfileString("Properties","Lines","",sKeyValue,MAX_CHAR_KEYS,sFilePart);

			m_NbLine=atol(sKeyValue);

			//On charge l'image 
			GetPrivateProfileString("Properties","OutputFileName","",sKeyValue,MAX_CHAR_KEYS,sFilePart);
			pImage->LoadFile(std::string(sKeyValue));
		}
	}
	else 
		m_bContinue=false;

	return true;

}

//****************************************************
//Effectue les calculs non parallélisables
//****************************************************
void	CRenderInterface::CommonComputation()
{
	ComputePhotonMap();
}
 

void	CRenderInterface::ComputePhotonMap()
{
	pPhotonTracer=new CPhotonTracer;

	//on prend la liste du premier thread
	if(pPhotonTracer!=NULL && pListGeometry!=NULL && pListLight!=NULL)
		pPhotonTracer->EmitCausticPhotons(*pListLight,(pListOfListGeometry[0])->GetVectorGeometry());

}



