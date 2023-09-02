#include <clex.h>

#line 1 "FormulaDerivatePreProc.l"

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


#line 22 "FormulaDerivatePreProc.l.cpp"
// repeated because of possible precompiled header
#include <clex.h>

#include "FormulaDerivatePreProc.l.h"

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
#line 45 "FormulaDerivatePreProc.l"
return FLOAT_TOKEN;
#line 85 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 2:
		{
#line 46 "FormulaDerivatePreProc.l"
return FLOAT_TOKEN;
#line 92 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 3:
		{
#line 48 "FormulaDerivatePreProc.l"
 return (PIXEL_TOKEN);
#line 99 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 4:
		{
#line 49 "FormulaDerivatePreProc.l"
 return (INIT_TOKEN);
#line 106 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 5:
		{
#line 50 "FormulaDerivatePreProc.l"
 return (EXP_TOKEN);
#line 113 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 6:
		{
#line 51 "FormulaDerivatePreProc.l"
 return (SIN_TOKEN);
#line 120 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 7:
		{
#line 52 "FormulaDerivatePreProc.l"
 return (COS_TOKEN);
#line 127 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 8:
		{
#line 53 "FormulaDerivatePreProc.l"
 return (TAN_TOKEN);
#line 134 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 9:
		{
#line 54 "FormulaDerivatePreProc.l"
 return (COTAN_TOKEN);
#line 141 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 10:
		{
#line 55 "FormulaDerivatePreProc.l"
 return (LOG_TOKEN);
#line 148 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 11:
		{
#line 56 "FormulaDerivatePreProc.l"
 return (ASIN_TOKEN);
#line 155 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 12:
		{
#line 57 "FormulaDerivatePreProc.l"
 return (ACOS_TOKEN);
#line 162 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 13:
		{
#line 58 "FormulaDerivatePreProc.l"
 return (ATAN_TOKEN);
#line 169 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 14:
		{
#line 59 "FormulaDerivatePreProc.l"
 return (ACOTAN_TOKEN);
#line 176 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 15:
		{
#line 60 "FormulaDerivatePreProc.l"
 return (SQRT_TOKEN);
#line 183 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 16:
		{
#line 61 "FormulaDerivatePreProc.l"
 return (QUATER_TOKEN);
#line 190 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 17:
		{
#line 62 "FormulaDerivatePreProc.l"
 return '='; 
#line 197 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 18:
		{
#line 63 "FormulaDerivatePreProc.l"
 return PLUS_TOKEN; 
#line 204 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 19:
		{
#line 64 "FormulaDerivatePreProc.l"
 return DASH_TOKEN; 
#line 211 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 20:
		{
#line 65 "FormulaDerivatePreProc.l"
 return MULT_TOKEN; 
#line 218 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 21:
		{
#line 66 "FormulaDerivatePreProc.l"
 return DIV_TOKEN; 
#line 225 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 22:
		{
#line 67 "FormulaDerivatePreProc.l"
 return HAT_TOKEN; 
#line 232 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 23:
		{
#line 68 "FormulaDerivatePreProc.l"
 return '('; 
#line 239 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 24:
		{
#line 69 "FormulaDerivatePreProc.l"
 return ')'; 
#line 246 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 25:
		{
#line 70 "FormulaDerivatePreProc.l"
 return WHITE_TOKEN;
#line 253 "FormulaDerivatePreProc.l.cpp"
		}
		break;
	case 26:
		{
#line 71 "FormulaDerivatePreProc.l"
 ; 
#line 260 "FormulaDerivatePreProc.l.cpp"
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
#line 73 "FormulaDerivatePreProc.l"


void   CDataDerivatePreProcLexer::Create(CDataDerivatePreProcParser *Parser)
{
	yycreate(Parser);

	m_pParser=Parser;
}
#line 285 "FormulaDerivatePreProc.l.cpp"

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
		{ 21, 1 },
		{ 21, 1 },
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
		{ 36, 24 },
		{ 15, 1 },
		{ 36, 24 },
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
		{ 53, 44 },
		{ 8, 1 },
		{ 61, 56 },
		{ 6, 1 },
		{ 58, 50 },
		{ 34, 11 },
		{ 46, 32 },
		{ 28, 7 },
		{ 38, 25 },
		{ 47, 33 },
		{ 10, 1 },
		{ 62, 58 },
		{ 45, 31 },
		{ 30, 8 },
		{ 25, 4 },
		{ 29, 7 },
		{ 42, 29 },
		{ 7, 1 },
		{ 9, 1 },
		{ 52, 42 },
		{ 24, 3 },
		{ 33, 11 },
		{ 35, 11 },
		{ 27, 6 },
		{ 12, 1 },
		{ 50, 38 },
		{ 43, 30 },
		{ 44, 30 },
		{ 55, 48 },
		{ 56, 48 },
		{ 59, 51 },
		{ 40, 27 },
		{ 48, 34 },
		{ 32, 10 },
		{ 54, 47 },
		{ 39, 26 },
		{ 57, 49 },
		{ 41, 28 },
		{ 60, 53 },
		{ 63, 61 },
		{ 37, 37 },
		{ 37, 37 },
		{ 37, 37 },
		{ 37, 37 },
		{ 37, 37 },
		{ 37, 37 },
		{ 37, 37 },
		{ 37, 37 },
		{ 37, 37 },
		{ 37, 37 },
		{ 26, 5 },
		{ 51, 39 },
		{ 49, 35 },
		{ 31, 9 }
	};
	yytransition = transition;

	static const yystate_t YYNEARFAR YYBASED_CODE state[] = {
		{ 0, 0, 0 },
		{ -22, 1, 0 },
		{ 1, 0, 0 },
		{ 50, 18, 2 },
		{ 27, 1, 26 },
		{ 39, 44, 26 },
		{ 38, 2, 26 },
		{ 39, 1, 26 },
		{ 34, 1, 26 },
		{ 56, 55, 26 },
		{ 34, 21, 26 },
		{ 51, 5, 26 },
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
		{ 0, 0, 26 },
		{ 37, 28, 1 },
		{ 37, 2, 0 },
		{ 39, 2, 0 },
		{ 61, 24, 0 },
		{ 0, 18, 0 },
		{ 61, 26, 0 },
		{ 0, 1, 0 },
		{ 51, 10, 0 },
		{ 61, 1, 0 },
		{ 0, 2, 0 },
		{ 39, 3, 0 },
		{ 0, 20, 0 },
		{ 56, 54, 0 },
		{ 37, 0, 0 },
		{ 0, 91, 2 },
		{ 0, 4, 0 },
		{ 0, 45, 0 },
		{ 0, 0, 5 },
		{ 0, 0, 6 },
		{ 51, 2, 0 },
		{ 0, 0, 7 },
		{ 56, 2, 0 },
		{ 0, 0, 8 },
		{ 0, 0, 10 },
		{ 61, 23, 0 },
		{ 51, 12, 0 },
		{ 61, 25, 0 },
		{ 0, 2, 0 },
		{ 0, 13, 0 },
		{ 0, 0, 15 },
		{ 61, 27, 0 },
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
		0,
		0
	};
	yybackup = backup;
}
