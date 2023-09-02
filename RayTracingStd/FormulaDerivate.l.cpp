#include <clex.h>

/* #line 1 "FormulaDerivate.l" */

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


// repeated because of possible precompiled header
#include <clex.h>

#include "FormulaDerivate.l.h"

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
/* #line 45 "FormulaDerivate.l" */
return FLOAT_TOKEN;
		}
		break;
	case 2:
		{
/* #line 46 "FormulaDerivate.l" */
return FLOAT_TOKEN;
		}
		break;
	case 3:
		{
/* #line 48 "FormulaDerivate.l" */
 return (PIXEL_TOKEN);
		}
		break;
	case 4:
		{
/* #line 49 "FormulaDerivate.l" */
 return (INIT_TOKEN);
		}
		break;
	case 5:
		{
/* #line 50 "FormulaDerivate.l" */
 return (EXP_TOKEN);
		}
		break;
	case 6:
		{
/* #line 51 "FormulaDerivate.l" */
 return (SIN_TOKEN);
		}
		break;
	case 7:
		{
/* #line 52 "FormulaDerivate.l" */
 return (COS_TOKEN);
		}
		break;
	case 8:
		{
/* #line 53 "FormulaDerivate.l" */
 return (TAN_TOKEN);
		}
		break;
	case 9:
		{
/* #line 54 "FormulaDerivate.l" */
 return (COTAN_TOKEN);
		}
		break;
	case 10:
		{
/* #line 55 "FormulaDerivate.l" */
 return (LOG_TOKEN);
		}
		break;
	case 11:
		{
/* #line 56 "FormulaDerivate.l" */
 return (ASIN_TOKEN);
		}
		break;
	case 12:
		{
/* #line 57 "FormulaDerivate.l" */
 return (ACOS_TOKEN);
		}
		break;
	case 13:
		{
/* #line 58 "FormulaDerivate.l" */
 return (ATAN_TOKEN);
		}
		break;
	case 14:
		{
/* #line 59 "FormulaDerivate.l" */
 return (ACOTAN_TOKEN);
		}
		break;
	case 15:
		{
/* #line 60 "FormulaDerivate.l" */
 return (SQRT_TOKEN);
		}
		break;
	case 16:
		{
/* #line 61 "FormulaDerivate.l" */
 return (QUATER_TOKEN);
		}
		break;
	case 17:
		{
/* #line 62 "FormulaDerivate.l" */
 return '='; 
		}
		break;
	case 18:
		{
/* #line 63 "FormulaDerivate.l" */
 return PLUS_TOKEN; 
		}
		break;
	case 19:
		{
/* #line 64 "FormulaDerivate.l" */
 return DASH_TOKEN; 
		}
		break;
	case 20:
		{
/* #line 65 "FormulaDerivate.l" */
 return MULT_TOKEN; 
		}
		break;
	case 21:
		{
/* #line 66 "FormulaDerivate.l" */
 return DIV_TOKEN; 
		}
		break;
	case 22:
		{
/* #line 67 "FormulaDerivate.l" */
 return HAT_TOKEN; 
		}
		break;
	case 23:
		{
/* #line 68 "FormulaDerivate.l" */
 return '('; 
		}
		break;
	case 24:
		{
/* #line 69 "FormulaDerivate.l" */
 return ')'; 
		}
		break;
	case 25:
		{
/* #line 70 "FormulaDerivate.l" */
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
/* #line 72 "FormulaDerivate.l" */


void   CDataDerivateLexer::Create(CDataDerivateParser *Parser)
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
		{ 35, 23 },
		{ 15, 1 },
		{ 35, 23 },
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
		{ 0, 0 },
		{ 0, 0 },
		{ 13, 1 },
		{ 0, 0 },
		{ 22, 3 },
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
		{ 22, 22 },
		{ 22, 22 },
		{ 22, 22 },
		{ 22, 22 },
		{ 22, 22 },
		{ 22, 22 },
		{ 22, 22 },
		{ 22, 22 },
		{ 22, 22 },
		{ 22, 22 },
		{ 0, 0 },
		{ 23, 3 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 12, 1 },
		{ 0, 0 },
		{ 0, 0 },
		{ 0, 0 },
		{ 18, 1 },
		{ 0, 0 },
		{ 0, 0 },
		{ 11, 1 },
		{ 52, 43 },
		{ 8, 1 },
		{ 60, 55 },
		{ 6, 1 },
		{ 57, 49 },
		{ 33, 11 },
		{ 45, 31 },
		{ 27, 7 },
		{ 37, 24 },
		{ 46, 32 },
		{ 10, 1 },
		{ 61, 57 },
		{ 44, 30 },
		{ 29, 8 },
		{ 24, 4 },
		{ 28, 7 },
		{ 41, 28 },
		{ 7, 1 },
		{ 9, 1 },
		{ 51, 41 },
		{ 23, 3 },
		{ 32, 11 },
		{ 34, 11 },
		{ 26, 6 },
		{ 12, 1 },
		{ 49, 37 },
		{ 42, 29 },
		{ 43, 29 },
		{ 54, 47 },
		{ 55, 47 },
		{ 58, 50 },
		{ 39, 26 },
		{ 47, 33 },
		{ 31, 10 },
		{ 53, 46 },
		{ 38, 25 },
		{ 56, 48 },
		{ 40, 27 },
		{ 59, 52 },
		{ 62, 60 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 36, 36 },
		{ 25, 5 },
		{ 50, 38 },
		{ 48, 34 },
		{ 30, 9 }
	};
	yytransition = transition;

	static const yystate_t YYNEARFAR YYBASED_CODE state[] = {
		{ 0, 0, 0 },
		{ -21, 1, 0 },
		{ 1, 0, 0 },
		{ 49, 18, 2 },
		{ 26, 1, 25 },
		{ 38, 44, 25 },
		{ 37, 2, 25 },
		{ 38, 1, 25 },
		{ 33, 1, 25 },
		{ 55, 55, 25 },
		{ 33, 21, 25 },
		{ 50, 5, 25 },
		{ 0, 0, 16 },
		{ 0, 0, 17 },
		{ 0, 0, 18 },
		{ 0, 0, 19 },
		{ 0, 0, 20 },
		{ 0, 0, 21 },
		{ 0, 0, 22 },
		{ 0, 0, 23 },
		{ 0, 0, 24 },
		{ 0, 0, 25 },
		{ 36, 28, 1 },
		{ 36, 2, 0 },
		{ 38, 2, 0 },
		{ 60, 24, 0 },
		{ 0, 18, 0 },
		{ 60, 26, 0 },
		{ 0, 1, 0 },
		{ 50, 10, 0 },
		{ 60, 1, 0 },
		{ 0, 2, 0 },
		{ 38, 3, 0 },
		{ 0, 20, 0 },
		{ 55, 54, 0 },
		{ 36, 0, 0 },
		{ 0, 91, 2 },
		{ 0, 4, 0 },
		{ 0, 45, 0 },
		{ 0, 0, 5 },
		{ 0, 0, 6 },
		{ 50, 2, 0 },
		{ 0, 0, 7 },
		{ 55, 2, 0 },
		{ 0, 0, 8 },
		{ 0, 0, 10 },
		{ 60, 23, 0 },
		{ 50, 12, 0 },
		{ 60, 25, 0 },
		{ 0, 2, 0 },
		{ 0, 13, 0 },
		{ 0, 0, 15 },
		{ 60, 27, 0 },
		{ 0, 0, 11 },
		{ 0, 0, 12 },
		{ 0, 4, 0 },
		{ 0, 0, 13 },
		{ 0, 2, 0 },
		{ 0, 0, 4 },
		{ 0, 0, 9 },
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
		0
	};
	yybackup = backup;
}
