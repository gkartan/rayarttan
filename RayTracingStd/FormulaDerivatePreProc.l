%{
/* Dérivation symbolique à partir d'une chaine
 * G.CADOU mai 2002
 */
#include "TraceService.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <string>

class CDataDerivatePreProcLexer;

#include "ListExpr.h"
#include "FormulaDerivatePreProc.h"

%}

// include file
%include {
// forward references
class CDataDerivatePreProcLexer;
class CDataDerivatePreProcParser;
}

%name CDataDerivatePreProcLexer

// class definition
{
// Attributes
public:
	inline void SetString(std::string &str) {m_str=str;}
	void   Create(CDataDerivatePreProcParser *Parser);
private:
	CDataDerivatePreProcParser *m_pParser;
	std::string	m_str;
}

QUATER	 "z"|"Z"
DIGIT       [0-9]
EXPFIELD    ([Ee][+-]?[0-9]+)


%%
{DIGIT}+"."{DIGIT}*				{return FLOAT_TOKEN;}
{DIGIT}+{EXPFIELD}?				{return FLOAT_TOKEN;}

"#pixel"			{ return (PIXEL_TOKEN);}
"@init"				{ return (INIT_TOKEN);}	
"exp"				{ return (EXP_TOKEN);}
"sin"				{ return (SIN_TOKEN);}
"cos"				{ return (COS_TOKEN);}
"tan"				{ return (TAN_TOKEN);}
"cotan"				{ return (COTAN_TOKEN);}
"log"				{ return (LOG_TOKEN);}
"asin"				{ return (ASIN_TOKEN);}
"acos"				{ return (ACOS_TOKEN);}
"atan"				{ return (ATAN_TOKEN);}
"acotan"			{ return (ACOTAN_TOKEN);}
"sqrt"				{ return (SQRT_TOKEN);}
{QUATER}			{ return (QUATER_TOKEN);}
"="					{ return '='; }
"+"					{ return PLUS_TOKEN; }
"-"					{ return DASH_TOKEN; }
"*"					{ return MULT_TOKEN; }
"/"					{ return DIV_TOKEN; }
"^"					{ return HAT_TOKEN; }
"("					{ return '('; }
")"					{ return ')'; }
[\t\n]				{ return WHITE_TOKEN;}
.					{ ; }

%%

void   CDataDerivatePreProcLexer::Create(CDataDerivatePreProcParser *Parser)
{
	yycreate(Parser);

	m_pParser=Parser;
}