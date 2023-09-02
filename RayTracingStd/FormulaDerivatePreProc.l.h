#ifndef _FORMULADERIVATEPREPROC_L_H
#define _FORMULADERIVATEPREPROC_L_H

#include <clex.h>

#line 20 "FormulaDerivatePreProc.l"

// forward references
class CDataDerivatePreProcLexer;
class CDataDerivatePreProcParser;

#line 13 "FormulaDerivatePreProc.l.h"
/////////////////////////////////////////////////////////////////////////////
// CDataDerivatePreProcLexer

#ifndef YYDECLSPEC
#define YYDECLSPEC
#endif

class YYFAR YYDECLSPEC CDataDerivatePreProcLexer : public yyflexer {
public:
	CDataDerivatePreProcLexer();

protected:
	void yytables();
	virtual int yyaction(int action);

public:
#line 29 "FormulaDerivatePreProc.l"

// Attributes
public:
	inline void SetString(std::string &str) {m_str=str;}
	void   Create(CDataDerivatePreProcParser *Parser);
private:
	CDataDerivatePreProcParser *m_pParser;
	std::string	m_str;

#line 40 "FormulaDerivatePreProc.l.h"
};

#ifndef YYLEXNAME
#define YYLEXNAME CDataDerivatePreProcLexer
#endif

#ifndef INITIAL
#define INITIAL 0
#endif

#endif
