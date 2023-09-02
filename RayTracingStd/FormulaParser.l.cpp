#include <clex.h>

/* #line 1 "FormulaParser.l" */

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

// repeated because of possible precompiled header
#include <clex.h>

#include "FormulaParser.l.h"

/////////////////////////////////////////////////////////////////////////////
// constructor

YYLEXNAME::YYLEXNAME()
{
	yytables();
}

#ifndef YYTEXT_SIZE
#define YYTEXT_SIZE 100
#endif
#ifndef YYUNPUT_SIZE
#define YYUNPUT_SIZE YYTEXT_SIZE
#endif

// backwards compatability with lex
#ifdef input
int YYLEXNAME::yyinput()
{
	return input();
}
#else
#define input yyinput
#endif

#ifdef output
void YYLEXNAME::yyoutput(int ch)
{
	output(ch);
}
#else
#define output yyoutput
#endif

#ifdef unput
void YYLEXNAME::yyunput(int ch)
{
	unput(ch);
}
#else
#define unput yyunput
#endif

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn -rch		// <warning: unreachable code> off
#endif
#endif

int YYLEXNAME::yyaction(int action)
{
	yyreturnflg = 1;
	switch (action) {
	case 1:
		{
/* #line 45 "FormulaParser.l" */
return FLOAT_TOKEN;
		}
		break;
	case 2:
		{
/* #line 46 "FormulaParser.l" */
return FLOAT_TOKEN;
		}
		break;
	case 3:
		{
/* #line 48 "FormulaParser.l" */
 return (PIXEL_TOKEN);
		}
		break;
	case 4:
		{
/* #line 49 "FormulaParser.l" */
 return (INIT_TOKEN);
		}
		break;
	case 5:
		{
/* #line 50 "FormulaParser.l" */
 return (EXP_TOKEN);
		}
		break;
	case 6:
		{
/* #line 51 "FormulaParser.l" */
 return (SIN_TOKEN);
		}
		break;
	case 7:
		{
/* #line 52 "FormulaParser.l" */
 return (COS_TOKEN);
		}
		break;
	case 8:
		{
/* #line 53 "FormulaParser.l" */
 return (TAN_TOKEN);
		}
		break;
	case 9:
		{
/* #line 54 "FormulaParser.l" */
 return (LOG_TOKEN);
		}
		break;
	case 10:
		{
/* #line 55 "FormulaParser.l" */
 return (COTAN_TOKEN);
		}
		break;
	case 11:
		{
/* #line 56 "FormulaParser.l" */
 return (ASIN_TOKEN);
		}
		break;
	case 12:
		{
/* #line 57 "FormulaParser.l" */
 return (ACOS_TOKEN);
		}
		break;
	case 13:
		{
/* #line 58 "FormulaParser.l" */
 return (ATAN_TOKEN);
		}
		break;
	case 14:
		{
/* #line 59 "FormulaParser.l" */
 return (ACOTAN_TOKEN);
		}
		break;
	case 15:
		{
/* #line 60 "FormulaParser.l" */
 return (SQRT_TOKEN);
		}
		break;
	case 16:
		{
/* #line 61 "FormulaParser.l" */
 return (QUATER_TOKEN);
		}
		break;
	case 17:
		{
/* #line 62 "FormulaParser.l" */
 return '='; 
		}
		break;
	case 18:
		{
/* #line 63 "FormulaParser.l" */
 return PLUS_TOKEN; 
		}
		break;
	case 19:
		{
/* #line 64 "FormulaParser.l" */
 return DASH_TOKEN; 
		}
		break;
	case 20:
		{
/* #line 65 "FormulaParser.l" */
 return MULT_TOKEN; 
		}
		break;
	case 21:
		{
/* #line 66 "FormulaParser.l" */
 return DIV_TOKEN; 
		}
		break;
	case 22:
		{
/* #line 67 "FormulaParser.l" */
 return HAT_TOKEN; 
		}
		break;
	case 23:
		{
/* #line 68 "FormulaParser.l" */
 return '('; 
		}
		break;
	case 24:
		{
/* #line 69 "FormulaParser.l" */
 return ')'; 
		}
		break;
	case 25:
		{
/* #line 70 "FormulaParser.l" */
 return ';'; 
		}
		break;
	case 26:
		{
/* #line 71 "FormulaParser.l" */

		}
		break;
	case 27:
		{
/* #line 72 "FormulaParser.l" */

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
		break;
	case 28:
		{
/* #line 89 "FormulaParser.l" */
 ; 
		}
		break;
	default:
		yyassert(0);
		break;
	}
	yyreturnflg = 0;
	return 0;
}

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn .rch		// <warning: unreachable code> to the old state
#endif
#endif
/* #line 91 "FormulaParser.l" */


void   CDataFormulaLexer::Create(CDataFormulaParser *Parser)
{
	yycreate(Parser);
	m_pParser=Parser;
}

void YYLEXNAME::yytables()
{
	yystext_size = YYTEXT_SIZE;
	yysunput_size = YYUNPUT_SIZE;

	static const yymatch_t YYNEARFAR YYBASED_CODE match[] = {
		0
	};
	yymatch = match;

	yytransitionmax = 153;
	static const yytransition_t YYNEARFAR YYBASED_CODE transition[] = {
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 1 },
		{ 0, 36 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 4, 1 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 19, 1 },
		{ 20, 1 },
		{ 16, 1 },
		{ 14, 1 },
		{ 38, 24 },
		{ 15, 1 },
		{ 38, 24 },
		{ 17, 1 },
		{ 3, 1 },
		{ 3, 1 },
		{ 3, 1 },
		{ 3, 1 },
		{ 3, 1 },
		{ 3, 1 },
		{ 3, 1 },
		{ 3, 1 },
		{ 3, 1 },
		{ 3, 1 },
		{ 0, 0 },
		{ 21, 1 },
		{ 0, 0 },
		{ 13, 1 },
		{ 0, 0 },
		{ 23, 3 },
		{ 5, 1 },
		{ 3, 3 },
		{ 3, 3 },
		{ 3, 3 },
		{ 3, 3 },
		{ 3, 3 },
		{ 3, 3 },
		{ 3, 3 },
		{ 3, 3 },
		{ 3, 3 },
		{ 3, 3 },
		{ 23, 23 },
		{ 23, 23 },
		{ 23, 23 },
		{ 23, 23 },
		{ 23, 23 },
		{ 23, 23 },
		{ 23, 23 },
		{ 23, 23 },
		{ 23, 23 },
		{ 23, 23 },
		{ 0, 0 },
		{ 24, 3 },
		{ 37, 17 },
		{ 0, 0 },
		{ 0, 0 },
		{ 12, 1 },
		{ 0, 0 },
		{ 36, 17 },
		{ 0, 0 },
		{ 18, 1 },
		{ 0, 0 },
		{ 0, 0 },
		{ 11, 1 },
		{ 55, 46 },
		{ 8, 1 },
		{ 63, 58 },
		{ 6, 1 },
		{ 60, 52 },
		{ 34, 11 },
		{ 48, 32 },
		{ 28, 7 },
		{ 40, 25 },
		{ 49, 33 },
		{ 10, 1 },
		{ 64, 60 },
		{ 47, 31 },
		{ 30, 8 },
		{ 25, 4 },
		{ 29, 7 },
		{ 44, 29 },
		{ 7, 1 },
		{ 9, 1 },
		{ 54, 44 },
		{ 24, 3 },
		{ 33, 11 },
		{ 35, 11 },
		{ 27, 6 },
		{ 12, 1 },
		{ 52, 40 },
		{ 45, 30 },
		{ 46, 30 },
		{ 57, 50 },
		{ 58, 50 },
		{ 61, 53 },
		{ 42, 27 },
		{ 50, 34 },
		{ 32, 10 },
		{ 56, 49 },
		{ 41, 26 },
		{ 59, 51 },
		{ 43, 28 },
		{ 62, 55 },
		{ 65, 63 },
		{ 39, 39 },
		{ 39, 39 },
		{ 39, 39 },
		{ 39, 39 },
		{ 39, 39 },
		{ 39, 39 },
		{ 39, 39 },
		{ 39, 39 },
		{ 39, 39 },
		{ 39, 39 },
		{ 26, 5 },
		{ 53, 41 },
		{ 51, 35 },
		{ 31, 9 }
	};
	yytransition = transition;

	static const yystate_t YYNEARFAR YYBASED_CODE state[] = {
		{ 0, 0, 0 },
		{ -22, 1, 0 },
		{ 1, 0, 0 },
		{ 52, 18, 2 },
		{ 27, 1, 28 },
		{ 41, 44, 28 },
		{ 40, 2, 28 },
		{ 41, 1, 28 },
		{ 34, 1, 28 },
		{ 58, 55, 28 },
		{ 34, 21, 28 },
		{ 53, 5, 28 },
		{ 0, 0, 16 },
		{ 0, 0, 17 },
		{ 0, 0, 18 },
		{ 0, 0, 19 },
		{ 0, 0, 20 },
		{ 0, 46, 21 },
		{ 0, 0, 22 },
		{ 0, 0, 23 },
		{ 0, 0, 24 },
		{ 0, 0, 25 },
		{ 0, 0, 28 },
		{ 39, 28, 1 },
		{ 39, 2, 0 },
		{ 41, 2, 0 },
		{ 63, 24, 0 },
		{ 0, 18, 0 },
		{ 63, 26, 0 },
		{ 0, 1, 0 },
		{ 53, 10, 0 },
		{ 63, 1, 0 },
		{ 0, 2, 0 },
		{ 41, 3, 0 },
		{ 0, 20, 0 },
		{ 58, 54, 0 },
		{ -36, 2, 26 },
		{ 0, 0, 27 },
		{ 39, 0, 0 },
		{ 0, 91, 2 },
		{ 0, 4, 0 },
		{ 0, 45, 0 },
		{ 0, 0, 5 },
		{ 0, 0, 6 },
		{ 53, 2, 0 },
		{ 0, 0, 7 },
		{ 58, 2, 0 },
		{ 0, 0, 8 },
		{ 0, 0, 9 },
		{ 63, 23, 0 },
		{ 53, 12, 0 },
		{ 63, 25, 0 },
		{ 0, 2, 0 },
		{ 0, 13, 0 },
		{ 0, 0, 15 },
		{ 63, 27, 0 },
		{ 0, 0, 11 },
		{ 0, 0, 12 },
		{ 0, 4, 0 },
		{ 0, 0, 13 },
		{ 0, 2, 0 },
		{ 0, 0, 4 },
		{ 0, 0, 10 },
		{ 0, 28, 0 },
		{ 0, 0, 3 },
		{ 0, 0, 14 }
	};
	yystate = state;

	static const yybackup_t YYNEARFAR YYBASED_CODE backup[] = {
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};
	yybackup = backup;
}
