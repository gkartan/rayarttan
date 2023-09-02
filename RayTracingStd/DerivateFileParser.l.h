#ifndef _DERIVATEFILEPARSER_L_H
#define _DERIVATEFILEPARSER_L_H

#include <clex.h>

#line 20 "DerivateFileParser.l"

// forward references
class CDerivateFileLexer;
class CDerivateFileParser;

#line 13 "DerivateFileParser.l.h"
/////////////////////////////////////////////////////////////////////////////
// CDerivateFileLexer

#ifndef YYDECLSPEC
#define YYDECLSPEC
#endif

class YYFAR YYDECLSPEC CDerivateFileLexer : public yyflexer {
public:
	CDerivateFileLexer();

protected:
	void yytables();
	virtual int yyaction(int action);

public:
#line 29 "DerivateFileParser.l"

// Attributes
private:
	CDerivateFileParser *m_pParser;
public:
	void   Create(CDerivateFileParser *Parser);

#line 38 "DerivateFileParser.l.h"
};

#ifndef YYLEXNAME
#define YYLEXNAME CDerivateFileLexer
#endif

#ifndef INITIAL
#define INITIAL 0
#endif

#endif
