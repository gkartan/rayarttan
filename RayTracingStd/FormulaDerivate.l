%{
/* Dérivation symbolique à partir d'une chaine
 * G.CADOU mai 2002
 */
#pragma warning(disable : 4786)
#include "TraceService.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <stack>

class CDataDerivateLexer;
#include "ListExpr.h"
#include "FormulaDerivate.h"

%}

// include file
%include {
// forward references
class CDataDerivateLexer;
class CDataDerivateParser;
}

%name CDataDerivateLexer

// class definition
{
// Attributes
public:
	inline void SetString(std::string &str) {m_str=str;}
	void   Create(CDataDerivateParser *Parser);
private:
	std::string	m_str;
	CDataDerivateParser *m_pParser;
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
.					{ ; }

%%

void   CDataDerivateLexer::Create(CDataDerivateParser *Parser)
{
	yycreate(Parser);

	m_pParser=Parser;
}