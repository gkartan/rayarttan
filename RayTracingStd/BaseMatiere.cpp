#include "stdio.h"
#include "BaseMatiere.h"
#include "BaseModelLight.h"
#include <afxmt.h>

CMutex	MatiereMutex(FALSE,"MATIEREMUTEX");

CBaseMatiere::CBaseMatiere()
{
	m_Specular.SetColor(CColor(1,1,1)); 
	m_Ambient.SetCoeff(0.1); 
	m_Diffuse.SetCoeff(1); 
	m_Specular.SetCoeff(1); 
	m_Kr=0; 
	m_Transparent.SetCoeff(0);
	m_Milieu1=1;
	m_Milieu2=1;

	m_pModelLight=NULL;
	m_NbRef=0;
}

CBaseMatiere::CBaseMatiere(CColor &param)
{
	m_Specular.SetColor(CColor(1,1,1)); 
	m_Ambient.SetCoeff(0.1); 
	m_Diffuse.SetCoeff(1); 
	m_Specular.SetCoeff(1); 
	m_Kr=0; 
	m_Transparent.SetCoeff(0);
	m_Milieu1=1;
	m_Milieu2=1;

	SetColorGeneral(param);

	m_pModelLight=NULL;
	m_NbRef=0;
}

CBaseMatiere::CBaseMatiere(CColor &param,CBaseModelLight *pLight)
{
	m_Specular.SetColor(CColor(1,1,1)); 
	m_Ambient.SetCoeff(0.1); 
	m_Diffuse.SetCoeff(1); 
	m_Specular.SetCoeff(1); 
	m_Kr=0; 
	m_Transparent.SetCoeff(0);
	m_Milieu1=1;
	m_Milieu2=1;

	SetColorGeneral(param);

	m_pModelLight=pLight;
	m_pModelLight->AddRef();
	m_NbRef=0;
}

CBaseMatiere::~CBaseMatiere()
{
	if(m_pModelLight!=NULL)
		m_pModelLight->Release();
}

CBaseMatiere&	CBaseMatiere::operator=(CBaseMatiere	&Origin)
{
	m_Ambient=Origin.m_Ambient;
	m_Specular=Origin.m_Specular;		
	m_Diffuse=Origin.m_Diffuse;	
	m_Transparent=Origin.m_Transparent;	

	m_Milieu1=Origin.m_Milieu1;
	m_Milieu2=Origin.m_Milieu2;

	m_pModelLight=Origin.m_pModelLight;
	if(m_pModelLight!=NULL)
		m_pModelLight->AddRef();
	m_NbRef=0;
	m_Kr=Origin.m_Kr;

	m_Dispersion=Origin.m_Dispersion;	
	m_PhotonParameters=Origin.m_PhotonParameters;	

	return (*this);
}

void CBaseMatiere::SetColorGeneral(CColor &Color)
{
	m_Ambient.SetColorGeneral(Color);
	m_Diffuse.SetColorGeneral(Color);	
	m_Transparent.SetColorGeneral(Color);	

}

void	CBaseMatiere::AddRef()	
{
	CSingleLock singleLock(&MatiereMutex);
	singleLock.Lock();  // Attempt to lock the shared resource

	m_NbRef++;

	singleLock.Unlock();
}
void	CBaseMatiere::Release()
{
	CSingleLock singleLock(&MatiereMutex);
	singleLock.Lock();  // Attempt to lock the shared resource

	m_NbRef--;
	if(m_NbRef<=0) delete(this);

	singleLock.Unlock();
}

bool	CBaseMatiere::IsTexture(ENUM_TYPECOLOR Type)
{
	switch(Type)
	{
		case TYPE_AMBIENT:
			return(m_Ambient.IsTexture());
			break;
		case TYPE_SPECULAR:
			return(m_Specular.IsTexture());
			break;
		case TYPE_DIFFUSE:
			return(m_Diffuse.IsTexture());
			break;
		case TYPE_TRANSPARENT:
			return(m_Transparent.IsTexture());
			break;
		default:
			return false;
	}
}

CTextureElement*	CBaseMatiere::GetTexture(ENUM_TYPECOLOR Type)
{
	switch(Type)
	{
		case TYPE_AMBIENT:
			return(&m_Ambient);
			break;
		case TYPE_SPECULAR:
			return(&m_Specular);
			break;
		case TYPE_DIFFUSE:
			return(&m_Diffuse);
			break;
		case TYPE_TRANSPARENT:
			return(&m_Transparent);
			break;
		default:
			return NULL;
	}
}

CBaseProcedural*	CBaseMatiere::GetProcedural(ENUM_TYPECOLOR Type)
{
	switch(Type)
	{
		case TYPE_AMBIENT:
			return(m_Ambient.GetProcedural());
			break;
		case TYPE_SPECULAR:
			return(m_Specular.GetProcedural());
			break;
		case TYPE_DIFFUSE:
			return(m_Diffuse.GetProcedural());
			break;
		case TYPE_TRANSPARENT:
			return(m_Transparent.GetProcedural());
			break;
		default:
			return NULL;
	}
}

void	CBaseMatiere::SetProcedural(ENUM_TYPECOLOR Type,CBaseProcedural *pProc)
{
	switch(Type)
	{
		case TYPE_AMBIENT:
			m_Ambient.SetProcedural(pProc);
			break;
		case TYPE_SPECULAR:
			m_Specular.SetProcedural(pProc);
			break;
		case TYPE_DIFFUSE:
			m_Diffuse.SetProcedural(pProc);
			break;
		case TYPE_TRANSPARENT:
			m_Transparent.SetProcedural(pProc);
			break;
		default:;
			
	}
}

void	CBaseMatiere::SetTypeTexture(ENUM_TYPECOLOR Type,CNoise3D *pNoise)
{
	switch(Type)
	{
		case TYPE_AMBIENT:
			m_Ambient.ChangeFunctionNoise(pNoise);
			break;
		case TYPE_SPECULAR:
			m_Specular.ChangeFunctionNoise(pNoise);
			break;
		case TYPE_DIFFUSE:
			m_Diffuse.ChangeFunctionNoise(pNoise);
			break;
		case TYPE_TRANSPARENT:
			m_Transparent.ChangeFunctionNoise(pNoise);
			break;
		default:;
			
	}
}

void	CBaseMatiere::SetTypeTexture(ENUM_TYPECOLOR Type,CBaseProcedural *pProc)
{
	switch(Type)
	{
		case TYPE_AMBIENT:
			m_Ambient.SetProcedural(pProc);
			break;
		case TYPE_SPECULAR:
			m_Specular.SetProcedural(pProc);
			break;
		case TYPE_DIFFUSE:
			m_Diffuse.SetProcedural(pProc);
			break;
		case TYPE_TRANSPARENT:
			m_Transparent.SetProcedural(pProc);
			break;
		default:;
			
	}
}

void CBaseMatiere::SetTexture(ENUM_TYPECOLOR Type,const CTextureElement &Text)
{
	switch(Type)
	{
		case TYPE_AMBIENT:
			m_Ambient=Text;
			break;
		case TYPE_SPECULAR:
			m_Specular=Text;
			break;
		case TYPE_DIFFUSE:
			m_Diffuse=Text;
			break;
		case TYPE_TRANSPARENT:
			m_Transparent=Text;
			break;
		default:;
			
	}

}


void CBaseMatiere::GetOuputStream(ostream &o)
{
	o	<<	"texture\n{\n";
	o	<<	"\t\"" << GetName().c_str() << "\"\n";

	///Couleur générale (pas besoin)
	//o	<<	"\tpigment\n{";
	//o	<<	"\t rgb " << m_colorGeneral << "\t}\n";

	///Les différentes textures
	o	<<	"\tfinish\n\t{\n";
	o	<<	"\t\tambient "	<< m_Ambient;
	o	<<  "\t\tdiffuse "	<< m_Diffuse;
	o	<<	"\t\ttransparent "	<< m_Transparent;
	o	<<	"\t\tspecular "	<< m_Specular;

	if(m_Kr!=0.0)
		o	<<	"\t\treflection " << m_Kr;

	if(m_pModelLight!=NULL)
		o << "\t\tphong_size " << m_pModelLight->GetPhongExp();

	o	<<	"\n\t}\n";
	o	<<	"}\n";
}


