#pragma warning(disable : 4786)

#include "stdio.h"
#include "ProcSimpleNoiseMatiere.h"
#include "Noise3D.h"

CProcSimpleNoiseMatiere::CProcSimpleNoiseMatiere()
{
	m_pNoise=new CNoise3D;
}

CProcSimpleNoiseMatiere::CProcSimpleNoiseMatiere(CColor& color)
:CBaseProcedural(color)
{
	m_pNoise=new CNoise3D;
}


CProcSimpleNoiseMatiere::~CProcSimpleNoiseMatiere()
{
	if(m_pNoise!=NULL)
		delete m_pNoise;
}

CProcSimpleNoiseMatiere&	CProcSimpleNoiseMatiere::operator=(CProcSimpleNoiseMatiere	&Origin)
{
	m_pNoise=Origin.m_pNoise;
	return (*this);
}

CColor	CProcSimpleNoiseMatiere::GetColor(const CCoord& coord,const CCoord&)	const
{
	return GetColorMap(m_pNoise->GetNoise(coord));
}

void	CProcSimpleNoiseMatiere::ChangeFunctionNoise(CNoise3D* pNoise)
{
	if(m_pNoise!=NULL)
		delete m_pNoise;

	m_pNoise=pNoise;
}

void	CProcSimpleNoiseMatiere::ChangeFreq(float Freq)
{
//  TEMPORAIRE COMMENTAIRE
//	m_pNoise->SetFreq(Freq);
}

std::string	CProcSimpleNoiseMatiere::GetType() const	
{
	if(m_pNoise==NULL)
		return(std::string(""));
	else
		return(m_pNoise->GetType());
}

bool	CProcSimpleNoiseMatiere::Compatible(ENUM_TYPETEXTURE Type)
{
	return((Type==TEXTURE_SPOTTED) || (Type==TEXTURE_GRANITE));
}


void CProcSimpleNoiseMatiere::GetOuputStream(ostream &o)
{
	o	<< "\n\t\t\tpigment\n\t\t\t{\n\t\t\t\t"	<< m_pNoise->GetType().c_str() << "\n";
	CBaseProcedural::GetOuputStream(o);
	o   << "\t\t\t}\n";
}

