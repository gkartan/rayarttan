#ifndef _FORMULAPARSER_L_H
#define _FORMULAPARSER_L_H

#include <clex.h>

/* #line 18 "FormulaParser.l" */

// forward references
class CDataFormulaLexer;
class CDataFormulaParser;

/////////////////////////////////////////////////////////////////////////////
// CDataFormulaLexer

#ifndef YYDECLSPEC
#define YYDECLSPEC
#endif

class YYFAR YYDECLSPEC CDataFormulaLexer : public yyflexer {
public:
	CDataFormulaLexer();

protected:
	void yytables();
	virtual int yyaction(int action);

public:
/* #line 27 "FormulaParser.l" */

// Attributes
private:
	CDataFormulaParser *m_pParser;
public:
	void   Create(CDataFormulaParser *Parser);

};

#ifndef YYLEXNAME
#define YYLEXNAME CDataFormulaLexer
#endif

#ifndef INITIAL
#define INITIAL 0
#endif

#endif
