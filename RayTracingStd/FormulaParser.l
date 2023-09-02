%{
/* rom.l: Roman numerals, trickier yacc, simpler lex
 * R Dowling 96Oct20
 */
#include "TraceService.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
using namespace std;

class CDataFormulaLexer;
#include "ListExpr.h"
#include "FormulaParser.h"
%}

// include file
%include {
// forward references
class CDataFormulaLexer;
class CDataFormulaParser;
}

%name CDataFormulaLexer

// class definition
{
// Attributes
private:
	CDataFormulaParser *m_pParser;
public:
	void   Create(CDataFormulaParser *Parser);
}

QUATER	 "z"|"Z"
DIGIT       [0-9]
ALPHA       [a-zA-Z]
ALPHANUM    {ALPHA}|{DIGIT}

EXPFIELD    ([Ee][+-]?[0-9]+)

IDENTIFIER  ({ALPHA}|"_")({ALPHANUM}|"_")*

%%
{DIGIT}+"."{DIGIT}*				{return FLOAT_TOKEN;}
{DIGIT}+{EXPFIELD}?				{return FLOAT_TOKEN;}

"#pixel"			{ return (PIXEL_TOKEN);}
"@init"				{ return (INIT_TOKEN);}	
"exp"				{ return (EXP_TOKEN);}
"sin"				{ return (SIN_TOKEN);}
"cos"				{ return (COS_TOKEN);}
"tan"				{ return (TAN_TOKEN);}
"log"				{ return (LOG_TOKEN);}
"cotan"				{ return (COTAN_TOKEN);}
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
";"					{ return ';'; }
"//".*      {} 
"/*"        {
			   int c;
			   for (;;)
			   {
				while ((c=input())!='*' && c!=EOF) ;
				if (c=='*')
				{
					while ((c=input())=='*') ;
					if (c=='/') break;
				}
				if (c==EOF)
				{
					//Error("EOF in comment");
					break;
				}
			   }
			}
.					{ ; }

%%

void   CDataFormulaLexer::Create(CDataFormulaParser *Parser)
{
	yycreate(Parser);
	m_pParser=Parser;
}