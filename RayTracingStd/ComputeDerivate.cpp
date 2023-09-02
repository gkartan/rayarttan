#pragma warning(disable : 4786)

#include "ComputeDerivate.h"


std::string	CComputeDerivate::m_str;
std::string	CComputeDerivate::m_strDerivate;
std::string	CComputeDerivate::m_strIntermediate;

CComputeDerivate::CComputeDerivate()
{
}

CComputeDerivate::CComputeDerivate(const std::string &str)
{
	m_str=str;
}

CComputeDerivate::~CComputeDerivate()
{
}

//////////////////////////
///Préprocesseur de la formule
/*int CComputeDerivate::ParseCompression()
{
	CDataDerivatePreProcParser Parser;
	CDataDerivatePreProcLexer *pLexer=Parser.CreateLexer();
	Parser.SetOutputString(&m_strIntermediate);

	////Init de l'analyseur lexical avec la chaine
	pLexer->yyin = fopen("data","w+");
	fputs(m_str.c_str(),pLexer->yyin);
	fclose(pLexer->yyin);
	pLexer->yyin=fopen("data","r");

	///lancement du parser
	Parser.yyparse();

	return Parser.GetResult();
}*/

int CComputeDerivate::ParseDerivate()
{
	CDataDerivateParser Parser;
	CDataDerivateLexer *pLexer=Parser.CreateLexer();
	Parser.SetOutputString(&m_strDerivate);

	////Init de l'analyseur lexical avec la chaine
	pLexer->yyin = fopen("data","w+");
	//fputs(m_strIntermediate.c_str(),pLexer->yyin);
	fputs(m_str.c_str(),pLexer->yyin);
	fclose(pLexer->yyin);
	pLexer->yyin=fopen("data","r");

	///lancement du parser
	Parser.yyparse();

	

	return Parser.GetResult();

}

bool CComputeDerivate::Derivate(std::string Input,std::string &Output)
{
	m_str=Input;
	m_strIntermediate.erase(m_strIntermediate.begin(),m_strIntermediate.end());
	m_strDerivate.erase(m_strDerivate.begin(),m_strDerivate.end());


	//int Result=ParseCompression();
	//if(Result!=-1 && ParseDerivate()!=-1)
	if(ParseDerivate()!=-1)
	{
		//::DeleteFile("data");	//Effacement du fichier après utilisation

		Output=m_strDerivate;
		return true;
	} else {
		///Recherche de la dérivée dans le fichier de dérivée
		return(SearchDerivate(Input,Output));
	}
}

std::string CComputeDerivate::GetExpr()
{
	return(m_str);
}

bool CComputeDerivate::SearchDerivate(const std::string &Input,std::string &strDerivate)
{
	////////Chargement de la map de dérivée
	CDerivateFileParser Parser;
	CDerivateFileLexer *pLexer=Parser.CreateLexer();
	pLexer->yyin=fopen("derivation.inc","r");

	///lancement du parser
	Parser.yyparse();

	////////On cherche la dérivée
	std::map<std::string,std::string>	&mapstr=Parser.GetMapStr();
	std::map<std::string,std::string>::iterator MyIterator;

	MyIterator=mapstr.find(Input);
	if(MyIterator!=mapstr.end())
	{
		strDerivate=(*MyIterator).second;
		return true;
	} else {
		strDerivate=std::string("#error");
		return false;
	}
}
