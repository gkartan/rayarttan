#include <cyacc.h>

#line 1 "FormulaParser.y"

/* 
 * compilateur d'expression mathematique
 */
#pragma warning(disable : 4530)
#include "TraceService.h"
#include "ListExpr.h"
#include <string>
#include "FormulaParser.l.h"


#line 16 "FormulaParser.cpp"
// repeated because of possible precompiled header
#include <cyacc.h>

#include "FormulaParser.h"

/////////////////////////////////////////////////////////////////////////////
// constructor

YYPARSENAME::YYPARSENAME()
{
	yytables();
}

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYSTACK_SIZE
#define YYSTACK_SIZE 100
#endif

// yyattribute
#ifdef YYDEBUG
void YYFAR* YYPARSENAME::yyattribute1(int index) const
{
	YYSTYPE YYFAR* p = &((YYSTYPE YYFAR*)yyattributestackptr)[yytop + index];
	return p;
}
#define yyattribute(index) (*(YYSTYPE YYFAR*)yyattribute1(index))
#else
#define yyattribute(index) (((YYSTYPE YYFAR*)yyattributestackptr)[yytop + (index)])
#endif

#ifdef YYDEBUG
void YYPARSENAME::yyinitdebug(void YYFAR** p, int count) const
{
	yyassert(p != NULL);
	yyassert(count >= 1);

	YYSTYPE YYFAR** p1 = (YYSTYPE YYFAR**)p;
	for (int i = 0; i < count; i++) {
		p1[i] = &((YYSTYPE YYFAR*)yyattributestackptr)[yytop + i - (count - 1)];
	}
}
#endif

void YYPARSENAME::yyaction(int action)
{
	switch (action) {
	case 0:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 68 "FormulaParser.y"
	
											_TRACE_INFO("End Parsing");
											m_Result=0;
									
#line 77 "FormulaParser.cpp"
			}
		}
		break;
	case 1:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 72 "FormulaParser.y"
 _TRACE_ERROR("Error Parsing Formula");m_Result=-1;
#line 90 "FormulaParser.cpp"
			}
		}
		break;
	case 2:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 79 "FormulaParser.y"
 
																m_pExpr->AddOp(TYPE_OP_MULT);
																_TRACE_INFO("TYPE_OP_MULT");
																_TRACE_INFO("TYPE_OP_STOCK");
															
#line 107 "FormulaParser.cpp"
			}
		}
		break;
	case 3:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 84 "FormulaParser.y"
 
																m_pExpr->AddOp(TYPE_OP_DIV);
																_TRACE_INFO("TYPE_OP_DIV");
																_TRACE_INFO("TYPE_OP_STOCK");
															
#line 124 "FormulaParser.cpp"
			}
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 90 "FormulaParser.y"
 
																m_pExpr->AddOp(TYPE_OP_ADD); 
																_TRACE_INFO("TYPE_OP_ADD");
																_TRACE_INFO("TYPE_OP_STOCK");
															
#line 141 "FormulaParser.cpp"
			}
		}
		break;
	case 5:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 95 "FormulaParser.y"
 
																m_pExpr->AddOp(TYPE_OP_MINUS); 
																_TRACE_INFO("TYPE_OP_MINUS");
																_TRACE_INFO("TYPE_OP_STOCK");
															
#line 158 "FormulaParser.cpp"
			}
		}
		break;
	case 6:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 101 "FormulaParser.y"

																_TRACE_INFO("TYPE_OP_MINUS_ALONE");
																m_pExpr->AddOp(TYPE_OP_MINUS_ALONE);
																_TRACE_INFO("TYPE_OP_STOCK");
															
#line 175 "FormulaParser.cpp"
			}
		}
		break;
	case 7:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 109 "FormulaParser.y"

																m_pExpr->AddOp(TYPE_OP_LOAD); 
																_TRACE_INFO("TYPE_OP_LOAD");
																m_pExpr->AddOp(TYPE_OP_POWER,yyattribute(3 - 3).ival);
																_TRACE_INFO("TYPE_OP_POWER");
																_TRACE_INFO("TYPE_OP_STOCK");
															
#line 194 "FormulaParser.cpp"
			}
		}
		break;
	case 8:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 120 "FormulaParser.y"
	
												_TRACE_INFO("TYPE_OP_STOCK");
												m_pExpr->AddOp(TYPE_OP_STOCK);
											
#line 210 "FormulaParser.cpp"
			}
		}
		break;
	case 9:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 124 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_STOCK_CST");
												m_pExpr->AddOp(TYPE_OP_STOCK_CST,yyattribute(1 - 1).fval);
											
#line 226 "FormulaParser.cpp"
			}
		}
		break;
	case 10:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 135 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_EXP");
												m_pExpr->AddOp(TYPE_OP_EXP);
												_TRACE_INFO("TYPE_OP_STOCK");
											
#line 243 "FormulaParser.cpp"
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 140 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_SIN");
												m_pExpr->AddOp(TYPE_OP_SIN);
												_TRACE_INFO("TYPE_OP_STOCK");
											
#line 260 "FormulaParser.cpp"
			}
		}
		break;
	case 12:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 145 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_COS");
												m_pExpr->AddOp(TYPE_OP_COS);
												_TRACE_INFO("TYPE_OP_STOCK");
											
#line 277 "FormulaParser.cpp"
			}
		}
		break;
	case 13:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 150 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_TAN");
												m_pExpr->AddOp(TYPE_OP_TAN);
												_TRACE_INFO("TYPE_OP_STOCK");
											
#line 294 "FormulaParser.cpp"
			}
		}
		break;
	case 14:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 155 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_COTAN");
												m_pExpr->AddOp(TYPE_OP_COTAN);
												_TRACE_INFO("TYPE_OP_STOCK");
											
#line 311 "FormulaParser.cpp"
			}
		}
		break;
	case 15:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 160 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_LOG");
												m_pExpr->AddOp(TYPE_OP_LOG);
												_TRACE_INFO("TYPE_OP_STOCK");
											
#line 328 "FormulaParser.cpp"
			}
		}
		break;
	case 16:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 165 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_ASIN");
												m_pExpr->AddOp(TYPE_OP_ASIN);
												_TRACE_INFO("TYPE_OP_STOCK");
											
#line 345 "FormulaParser.cpp"
			}
		}
		break;
	case 17:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 170 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_ACOS");
												m_pExpr->AddOp(TYPE_OP_ACOS);
												_TRACE_INFO("TYPE_OP_STOCK");
											
#line 362 "FormulaParser.cpp"
			}
		}
		break;
	case 18:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 175 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_ATAN");
												m_pExpr->AddOp(TYPE_OP_ATAN);
												_TRACE_INFO("TYPE_OP_STOCK");
											
#line 379 "FormulaParser.cpp"
			}
		}
		break;
	case 19:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 180 "FormulaParser.y"

												_TRACE_INFO("TYPE_OP_ACOTAN");
												m_pExpr->AddOp(TYPE_OP_ACOTAN);
												_TRACE_INFO("TYPE_OP_STOCK");
											
#line 396 "FormulaParser.cpp"
			}
		}
		break;
	case 20:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 186 "FormulaParser.y"

												m_pExpr->AddOp(TYPE_OP_SQRT);
												_TRACE_INFO("TYPE_OP_SQRT");
											
#line 412 "FormulaParser.cpp"
			}
		}
		break;
	case 21:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 197 "FormulaParser.y"

													_TRACE_INFO("TYPE_OP_STOCK");
													m_pExpr->AddOp(TYPE_OP_STOCK);
												
#line 428 "FormulaParser.cpp"
			}
		}
		break;
	case 22:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 201 "FormulaParser.y"

													m_pExpr->AddOp(TYPE_OP_POWER,yyattribute(3 - 3).ival); 
													_TRACE_INFO("TYPE_OP_POWER");
													_TRACE_INFO("TYPE_OP_STOCK");
												
#line 445 "FormulaParser.cpp"
			}
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 208 "FormulaParser.y"

								m_pExpr->AddOp(TYPE_OP_INIT); 
								_TRACE_INFO("TYPE_OP_INIT");
							
#line 461 "FormulaParser.cpp"
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 212 "FormulaParser.y"

								m_pExpr->AddOp(TYPE_OP_PIXEL); 
								_TRACE_INFO("TYPE_OP_PIXEL");
							
#line 477 "FormulaParser.cpp"
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 224 "FormulaParser.y"
 (*(YYSTYPE YYFAR*)yyvalptr).fval = - yyattribute(2 - 2).fval; 
#line 490 "FormulaParser.cpp"
			}
		}
		break;
	case 26:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 226 "FormulaParser.y"
 char   *string; (*(YYSTYPE YYFAR*)yyvalptr).fval = (double) strtod(m_plexer->yytext,&string);
#line 503 "FormulaParser.cpp"
			}
		}
		break;
	case 27:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 233 "FormulaParser.y"
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (int) yyattribute(1 - 1).fval; 
#line 516 "FormulaParser.cpp"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}
#line 236 "FormulaParser.y"


CDataFormulaParser::~CDataFormulaParser()
{
	delete m_plexer;
}

CDataFormulaLexer* CDataFormulaParser::CreateLexer()
{
	m_bvaluecste=false;
	m_bvaluecsteLeft=false;

	m_plexer=new CDataFormulaLexer;

	if (!yycreate(m_plexer)) {
		return 0;
	}

	m_plexer->Create(this);

	return m_plexer;	// success
}

void CDataFormulaParser::SetExpr(CListExpr<double>* Expr)
{
	m_pExpr=Expr;
}


#line 555 "FormulaParser.cpp"
void YYPARSENAME::yytables()
{
	yyattribute_size = sizeof(YYSTYPE);
	yysstack_size = YYSTACK_SIZE;

#ifdef YYDEBUG
	static const yysymbol_t YYNEARFAR YYBASED_CODE symbol[] = {
		{ "$end", 0 },
		{ "\'(\'", 40 },
		{ "\')\'", 41 },
		{ "error", 256 },
		{ "QUATER_TOKEN", 257 },
		{ "EXP_TOKEN", 258 },
		{ "SIN_TOKEN", 259 },
		{ "COS_TOKEN", 260 },
		{ "TAN_TOKEN", 261 },
		{ "LOG_TOKEN", 262 },
		{ "COTAN_TOKEN", 263 },
		{ "ASIN_TOKEN", 264 },
		{ "ACOS_TOKEN", 265 },
		{ "ATAN_TOKEN", 266 },
		{ "ACOTAN_TOKEN", 267 },
		{ "SQRT_TOKEN", 268 },
		{ "FLOAT_TOKEN", 269 },
		{ "PIXEL_TOKEN", 270 },
		{ "INIT_TOKEN", 271 },
		{ "PLUS_TOKEN", 272 },
		{ "MULT_TOKEN", 273 },
		{ "HAT_TOKEN", 274 },
		{ "DASH_TOKEN", 275 },
		{ "DIV_TOKEN", 276 },
		{ "PSEUDO_MINUS", 277 },
		{ NULL, 0 }
	};
	yysymbol = symbol;

	static const char* const YYNEARFAR YYBASED_CODE rule[] = {
		"$accept: file",
		"file: addsub_expr",
		"file: error",
		"addsub_expr: addsub_expr MULT_TOKEN addsub_expr",
		"addsub_expr: addsub_expr DIV_TOKEN addsub_expr",
		"addsub_expr: addsub_expr PLUS_TOKEN addsub_expr",
		"addsub_expr: addsub_expr DASH_TOKEN addsub_expr",
		"addsub_expr: DASH_TOKEN addsub_expr",
		"addsub_expr: \'(\' addsub_expr \')\'",
		"addsub_expr: element_expr",
		"addsub_expr: addsub_expr HAT_TOKEN integer",
		"element_expr: puiss_expr",
		"element_expr: constant",
		"element_expr: double",
		"func_expr: EXP_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: SIN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: COS_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: TAN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: COTAN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: LOG_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: ASIN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: ACOS_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: ATAN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: ACOTAN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: SQRT_TOKEN \'(\' addsub_expr \')\'",
		"puiss_expr: puiss_quater",
		"puiss_expr: func_expr",
		"puiss_quater: QUATER_TOKEN",
		"puiss_quater: QUATER_TOKEN HAT_TOKEN integer",
		"constant: INIT_TOKEN",
		"constant: PIXEL_TOKEN",
		"double: fexpr",
		"fexpr: DASH_TOKEN fexpr",
		"fexpr: FLOAT_TOKEN",
		"integer: double"
	};
	yyrule = rule;
#endif

	static const yyreduction_t YYNEARFAR YYBASED_CODE reduction[] = {
		{ 0, 1, -1 },
		{ 1, 1, 0 },
		{ 1, 1, 1 },
		{ 2, 3, 2 },
		{ 2, 3, 3 },
		{ 2, 3, 4 },
		{ 2, 3, 5 },
		{ 2, 2, 6 },
		{ 2, 3, -1 },
		{ 2, 1, -1 },
		{ 2, 3, 7 },
		{ 3, 1, -1 },
		{ 3, 1, 8 },
		{ 3, 1, 9 },
		{ 4, 4, 10 },
		{ 4, 4, 11 },
		{ 4, 4, 12 },
		{ 4, 4, 13 },
		{ 4, 4, 14 },
		{ 4, 4, 15 },
		{ 4, 4, 16 },
		{ 4, 4, 17 },
		{ 4, 4, 18 },
		{ 4, 4, 19 },
		{ 4, 4, 20 },
		{ 5, 1, -1 },
		{ 5, 1, -1 },
		{ 6, 1, 21 },
		{ 6, 3, 22 },
		{ 7, 1, 23 },
		{ 7, 1, 24 },
		{ 8, 1, -1 },
		{ 9, 2, 25 },
		{ 9, 1, 26 },
		{ 10, 1, 27 }
	};
	yyreduction = reduction;

	static const yytokenaction_t YYNEARFAR YYBASED_CODE tokenaction[] = {
		{ 47, YYAT_SHIFT, 1 },
		{ 66, YYAT_SHIFT, 44 },
		{ 66, YYAT_SHIFT, 45 },
		{ 64, YYAT_SHIFT, 45 },
		{ 66, YYAT_SHIFT, 47 },
		{ 62, YYAT_SHIFT, 79 },
		{ 22, YYAT_SHIFT, 43 },
		{ 22, YYAT_SHIFT, 44 },
		{ 22, YYAT_SHIFT, 45 },
		{ 22, YYAT_SHIFT, 46 },
		{ 22, YYAT_SHIFT, 47 },
		{ 49, YYAT_SHIFT, 15 },
		{ 63, YYAT_SHIFT, 44 },
		{ 63, YYAT_SHIFT, 45 },
		{ 61, YYAT_SHIFT, 78 },
		{ 63, YYAT_SHIFT, 47 },
		{ 60, YYAT_SHIFT, 77 },
		{ 49, YYAT_SHIFT, 49 },
		{ 67, YYAT_SHIFT, 44 },
		{ 67, YYAT_SHIFT, 45 },
		{ 59, YYAT_SHIFT, 76 },
		{ 58, YYAT_SHIFT, 75 },
		{ 57, YYAT_SHIFT, 74 },
		{ 56, YYAT_SHIFT, 73 },
		{ 55, YYAT_SHIFT, 72 },
		{ 54, YYAT_SHIFT, 71 },
		{ 53, YYAT_SHIFT, 70 },
		{ 52, YYAT_SHIFT, 69 },
		{ 42, YYAT_SHIFT, 45 },
		{ 39, YYAT_SHIFT, 61 },
		{ 38, YYAT_SHIFT, 60 },
		{ 37, YYAT_SHIFT, 59 },
		{ 36, YYAT_SHIFT, 58 },
		{ 35, YYAT_SHIFT, 57 },
		{ 34, YYAT_SHIFT, 56 },
		{ 33, YYAT_SHIFT, 55 },
		{ 32, YYAT_SHIFT, 54 },
		{ 31, YYAT_SHIFT, 53 },
		{ 30, YYAT_SHIFT, 52 },
		{ 28, YYAT_SHIFT, 48 },
		{ 21, YYAT_ACCEPT, 0 },
		{ 14, YYAT_SHIFT, 40 },
		{ 13, YYAT_SHIFT, 39 },
		{ 12, YYAT_SHIFT, 38 },
		{ 11, YYAT_SHIFT, 37 },
		{ 10, YYAT_SHIFT, 36 },
		{ 9, YYAT_SHIFT, 35 },
		{ 8, YYAT_SHIFT, 34 },
		{ 7, YYAT_SHIFT, 33 },
		{ 6, YYAT_SHIFT, 32 },
		{ 5, YYAT_SHIFT, 31 },
		{ 4, YYAT_SHIFT, 30 },
		{ 3, YYAT_SHIFT, 29 },
		{ 0, YYAT_SHIFT, 2 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 47, YYAT_SHIFT, 3 },
		{ 47, YYAT_SHIFT, 4 },
		{ 47, YYAT_SHIFT, 5 },
		{ 47, YYAT_SHIFT, 6 },
		{ 47, YYAT_SHIFT, 7 },
		{ 47, YYAT_SHIFT, 8 },
		{ 47, YYAT_SHIFT, 9 },
		{ 47, YYAT_SHIFT, 10 },
		{ 47, YYAT_SHIFT, 11 },
		{ 47, YYAT_SHIFT, 12 },
		{ 47, YYAT_SHIFT, 13 },
		{ 47, YYAT_SHIFT, 14 },
		{ -1, YYAT_ERROR, 0 },
		{ 47, YYAT_SHIFT, 16 },
		{ 47, YYAT_SHIFT, 17 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 47, YYAT_SHIFT, 18 },
		{ 62, YYAT_SHIFT, 43 },
		{ 62, YYAT_SHIFT, 44 },
		{ 62, YYAT_SHIFT, 45 },
		{ 62, YYAT_SHIFT, 46 },
		{ 62, YYAT_SHIFT, 47 }
	};
	yytokenaction = tokenaction;
	yytokenaction_size = 241;

	static const yystateaction_t YYNEARFAR YYBASED_CODE stateaction[] = {
		{ -203, 1, YYAT_DEFAULT, 47 },
		{ 0, 0, YYAT_DEFAULT, 47 },
		{ 0, 0, YYAT_REDUCE, 2 },
		{ -222, 1, YYAT_REDUCE, 27 },
		{ 11, 1, YYAT_DEFAULT, 14 },
		{ 10, 1, YYAT_DEFAULT, 14 },
		{ 9, 1, YYAT_DEFAULT, 14 },
		{ 8, 1, YYAT_DEFAULT, 14 },
		{ 7, 1, YYAT_DEFAULT, 14 },
		{ 6, 1, YYAT_DEFAULT, 14 },
		{ 5, 1, YYAT_DEFAULT, 14 },
		{ 4, 1, YYAT_DEFAULT, 14 },
		{ 3, 1, YYAT_DEFAULT, 14 },
		{ 2, 1, YYAT_DEFAULT, 14 },
		{ 1, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 33 },
		{ 0, 0, YYAT_REDUCE, 30 },
		{ 0, 0, YYAT_REDUCE, 29 },
		{ 0, 0, YYAT_DEFAULT, 47 },
		{ 0, 0, YYAT_REDUCE, 31 },
		{ 0, 0, YYAT_REDUCE, 13 },
		{ 40, 1, YYAT_ERROR, 0 },
		{ -266, 1, YYAT_REDUCE, 1 },
		{ 0, 0, YYAT_REDUCE, 9 },
		{ 0, 0, YYAT_REDUCE, 11 },
		{ 0, 0, YYAT_REDUCE, 12 },
		{ 0, 0, YYAT_REDUCE, 26 },
		{ 0, 0, YYAT_REDUCE, 25 },
		{ -2, 1, YYAT_DEFAULT, 62 },
		{ 0, 0, YYAT_DEFAULT, 49 },
		{ -219, 1, YYAT_DEFAULT, 39 },
		{ -220, 1, YYAT_DEFAULT, 39 },
		{ -221, 1, YYAT_DEFAULT, 39 },
		{ -222, 1, YYAT_DEFAULT, 39 },
		{ -223, 1, YYAT_DEFAULT, 39 },
		{ -224, 1, YYAT_DEFAULT, 39 },
		{ -225, 1, YYAT_DEFAULT, 39 },
		{ -226, 1, YYAT_DEFAULT, 39 },
		{ -227, 1, YYAT_DEFAULT, 39 },
		{ -228, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 47 },
		{ 0, 0, YYAT_REDUCE, 31 },
		{ -246, 1, YYAT_REDUCE, 7 },
		{ 0, 0, YYAT_DEFAULT, 47 },
		{ 0, 0, YYAT_DEFAULT, 47 },
		{ 0, 0, YYAT_DEFAULT, 49 },
		{ 0, 0, YYAT_DEFAULT, 47 },
		{ -40, 1, YYAT_DEFAULT, 49 },
		{ 0, 0, YYAT_REDUCE, 8 },
		{ -258, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 34 },
		{ 0, 0, YYAT_REDUCE, 28 },
		{ -14, 1, YYAT_DEFAULT, 61 },
		{ -15, 1, YYAT_DEFAULT, 61 },
		{ -16, 1, YYAT_DEFAULT, 61 },
		{ -17, 1, YYAT_DEFAULT, 61 },
		{ -18, 1, YYAT_DEFAULT, 61 },
		{ -19, 1, YYAT_DEFAULT, 61 },
		{ -20, 1, YYAT_DEFAULT, 61 },
		{ -21, 1, YYAT_DEFAULT, 61 },
		{ -25, 1, YYAT_DEFAULT, 61 },
		{ -27, 1, YYAT_ERROR, 0 },
		{ -36, 1, YYAT_DEFAULT, 61 },
		{ -261, 1, YYAT_REDUCE, 5 },
		{ -271, 1, YYAT_REDUCE, 3 },
		{ 0, 0, YYAT_REDUCE, 10 },
		{ -272, 1, YYAT_REDUCE, 6 },
		{ -255, 1, YYAT_REDUCE, 4 },
		{ 0, 0, YYAT_REDUCE, 32 },
		{ 0, 0, YYAT_REDUCE, 14 },
		{ 0, 0, YYAT_REDUCE, 15 },
		{ 0, 0, YYAT_REDUCE, 16 },
		{ 0, 0, YYAT_REDUCE, 17 },
		{ 0, 0, YYAT_REDUCE, 19 },
		{ 0, 0, YYAT_REDUCE, 18 },
		{ 0, 0, YYAT_REDUCE, 20 },
		{ 0, 0, YYAT_REDUCE, 21 },
		{ 0, 0, YYAT_REDUCE, 22 },
		{ 0, 0, YYAT_REDUCE, 23 },
		{ 0, 0, YYAT_REDUCE, 24 }
	};
	yystateaction = stateaction;

	static const yynontermgoto_t YYNEARFAR YYBASED_CODE nontermgoto[] = {
		{ 47, 67 },
		{ 47, 23 },
		{ 47, 26 },
		{ 47, 24 },
		{ 47, 27 },
		{ 47, 25 },
		{ 47, 20 },
		{ 47, 19 },
		{ 18, 42 },
		{ 45, 50 },
		{ 45, 19 },
		{ 45, 65 },
		{ 0, 21 },
		{ 0, 22 },
		{ 49, 68 },
		{ 18, 41 },
		{ 46, 66 },
		{ 44, 64 },
		{ 43, 63 },
		{ 40, 62 },
		{ 29, 51 },
		{ 1, 28 }
	};
	yynontermgoto = nontermgoto;
	yynontermgoto_size = 22;

	static const yystategoto_t YYNEARFAR YYBASED_CODE stategoto[] = {
		{ 11, 47 },
		{ 19, 47 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 6, 47 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 10, 45 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 17, 47 },
		{ 0, -1 },
		{ 0, -1 },
		{ 16, 47 },
		{ 15, 47 },
		{ 1, -1 },
		{ 14, 47 },
		{ -2, -1 },
		{ 0, -1 },
		{ 5, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 }
	};
	yystategoto = stategoto;

	yydestructorptr = NULL;

	yytokendestptr = NULL;
	yytokendest_size = 0;
	yytokendestbase = 0;
}
