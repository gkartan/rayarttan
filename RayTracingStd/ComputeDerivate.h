#ifndef _COMPUTEDERIVATE
#define _COMPUTEDERIVATE

/////Etat classe : VALIDE
/////Futures évolutions : permettre la dérivation d'expression + complexes
#pragma warning(disable : 4530)

#include <string>
#include <map>

#include "ComputeExpr.h"
#include "FormulaDerivate.l.h"
#include "FormulaDerivate.h"
//#include "FormulaDerivatePreProc.l.h"
//#include "FormulaDerivatePreProc.h"
#include "DerivateFileParser.l.h"
#include "DerivateFileParser.h"

class CComputeDerivate
{
public:
	CComputeDerivate();
	CComputeDerivate(const std::string &str);
	static int ParseCompression();
	static int ParseDerivate();

	virtual ~CComputeDerivate();

	static bool Derivate(std::string Input,std::string &);
	static std::string GetExpr();
	static bool	SearchDerivate(const std::string &Input,std::string &);
private:
	static std::string	m_str;
	static std::string	m_strIntermediate;
	static std::string	m_strDerivate;

};

#endif

