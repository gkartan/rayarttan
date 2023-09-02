#pragma warning(disable : 4786)

#include "stdio.h"
#include "ProcGradientMatiere.h"
#include "Constants.h"
#include "Vector.h"
#include "TraceService.h"

CProcGradientMatiere::CProcGradientMatiere()
{
	m_Bound=DEFAULT_BOUNDSIZE;
}

CProcGradientMatiere::CProcGradientMatiere(CColor& color)
:CBaseProcedural(color)
{
}


CProcGradientMatiere::~CProcGradientMatiere()
{
}

CProcGradientMatiere&	CProcGradientMatiere::operator=(CProcGradientMatiere	&Origin)
{
	return (*this);
}

CColor	CProcGradientMatiere::GetColor(const CCoord& coord,const CCoord& objCenter)	const
{
	return GetColorMap(CVector(coord-objCenter).Length()/m_Bound);
}

bool	CProcGradientMatiere::Compatible(ENUM_TYPETEXTURE Type)
{
	return(Type==TEXTURE_GRADIENT);
}

void CProcGradientMatiere::GetOuputStream(ostream &o)
{
	o	<< "\n\t\t\tpigment\n\t\t\t{\n\t\t\t\t"	<< GetType().c_str() << "\n";
	CBaseProcedural::GetOuputStream(o);
	o   << "\t\t\t}\n";
}

