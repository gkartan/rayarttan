#ifndef _FORMULADERIVATE_L_H
#define _FORMULADERIVATE_L_H

#include <clex.h>

/* #line 20 "FormulaDerivate.l" */

// forward references
class CDataDerivateLexer;
class CDataDerivateParser;

/////////////////////////////////////////////////////////////////////////////
// CDataDerivateLexer

#ifndef YYDECLSPEC
#define YYDECLSPEC
#endif

class YYFAR YYDECLSPEC CDataDerivateLexer : public yyflexer {
public:
	CDataDerivateLexer();

protected:
	void yytables();
	virtual int yyaction(int action);

public:
/* #line 29 "FormulaDerivate.l" */

// Attributes
public:
	inline void SetString(std::string &str) {m_str=str;}
	void   Create(CDataDerivateParser *Parser);
private:
	std::string	m_str;
	CDataDerivateParser *m_pParser;

};

#ifndef YYLEXNAME
#define YYLEXNAME CDataDerivateLexer
#endif

#ifndef INITIAL
#define INITIAL 0
#endif

#endif
