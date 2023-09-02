#ifndef _FORMULAPARSER
#define _FORMULAPARSER

#include "stdio.h"

#include <string>

#include "ComputeExpr.h"
#include "FormulaParser.l.h"
#include "FormulaParser.h"

template<class T,class Type_Elem>
class CFormulaParser
{
public:
	CFormulaParser();
	CFormulaParser(const std::string &str);
	int Parse(CListExpr<Type_Elem>&);

	virtual ~CFormulaParser();

private:
	std::string m_str;

};

template<class T,class Type_Elem>
CFormulaParser<T,Type_Elem>::CFormulaParser<T,Type_Elem>()
{
}

template<class T,class Type_Elem>
CFormulaParser<T,Type_Elem>::CFormulaParser<T,Type_Elem>(const std::string &str)
{
	m_str=str;
}

template<class T,class Type_Elem>
CFormulaParser<T,Type_Elem>::~CFormulaParser<T,Type_Elem>()
{
}

template<class T,class Type_Elem>
int CFormulaParser<T,Type_Elem>::Parse(CListExpr<Type_Elem> &Expr)
{
	
	CDataFormulaParser Parser;
	CDataFormulaLexer *pLexer=Parser.CreateLexer();
	Parser.SetExpr(&Expr);

	////Init de l'analyseur lexical avec la chaine
	pLexer->yyin = fopen("data","w+");
	fputs(m_str.c_str(),pLexer->yyin);
	fclose(pLexer->yyin);
	pLexer->yyin=fopen("data","r");

	///lancement du parser
	Parser.yyparse();

	return Parser.GetResult();
}

#endif
