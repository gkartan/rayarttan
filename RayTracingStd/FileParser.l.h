#ifndef _FILEPARSER_L_H
#define _FILEPARSER_L_H

#include <clex.h>

#line 25 "FileParser.l"

// forward references
class CFileLexer;
class CFileParser;

#line 13 "FileParser.l.h"
/////////////////////////////////////////////////////////////////////////////
// CFileLexer

#ifndef YYDECLSPEC
#define YYDECLSPEC
#endif

class YYFAR YYDECLSPEC CFileLexer : public yyflexer {
public:
	CFileLexer();

protected:
	void yytables();
	virtual int yyaction(int action);

public:
#line 34 "FileParser.l"

// Attributes
private:
	CFileParser *m_pParser;
public:
	void   Create(CFileParser *Parser);

#line 38 "FileParser.l.h"
};

#ifndef YYLEXNAME
#define YYLEXNAME CFileLexer
#endif

#ifndef INITIAL
#define INITIAL 0
#endif

#endif
