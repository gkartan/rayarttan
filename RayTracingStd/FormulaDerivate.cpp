#include <cyacc.h>

#line 1 "FormulaDerivate.y"

/* Dérivation symbolique à partir d'une chaine
 * G.CADOU mai 2002
 */
#pragma warning(disable : 4530)
#pragma warning(disable : 4786)
#include "TraceService.h"
#include "ListExpr.h"
#include <string>
#include <stack>
#include "FormulaDerivate.l.h"


#line 18 "FormulaDerivate.cpp"
// repeated because of possible precompiled header
#include <cyacc.h>

#include "FormulaDerivate.h"

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
#line 72 "FormulaDerivate.y"

									(*m_pstr)=m_DstrTemp;
									m_Result=0;
								
#line 79 "FormulaDerivate.cpp"
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
#line 76 "FormulaDerivate.y"

									_TRACE_ERROR("Error Parsing Derivate");
									m_Result=-1;
								
#line 95 "FormulaDerivate.cpp"
			}
		}
		break;
	case 2:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 83 "FormulaDerivate.y"

													m_strTempLeft.push(m_strTemp);
													m_DstrTempLeft.push(m_DstrTemp);
													m_strTemp="";
													m_DstrTemp="";
												
#line 113 "FormulaDerivate.cpp"
			}
		}
		break;
	case 3:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 90 "FormulaDerivate.y"

													m_strValue=m_strTempLeft.top();
													m_DstrValue=m_DstrTempLeft.top();
													m_strTempLeft.pop();
													m_DstrTempLeft.pop();
													m_strTempRight=m_strTemp;
													m_DstrTempRight=m_DstrTemp;
													m_strTemp=std::string("(")+m_strValue+std::string("*")+m_strTempRight+std::string(")");

													//S'il ya des zéros dans les dérivées
													//Test pour simplifier l'expression
													if(m_DstrValue.compare(std::string("0"))==0 && 
													   m_DstrTempRight.compare(std::string("0"))==0)
													{
														m_DstrTemp=std::string("0");
													} else
													if(m_DstrValue.compare(std::string("0"))==0)
													{
														m_DstrTemp=std::string("(")+
																   m_strValue+std::string("*")+m_DstrTempRight+
																   std::string(")");

													} else
													if(m_DstrTempRight.compare(std::string("0"))==0)
													{
														m_DstrTemp=std::string("(")+
																   m_DstrValue+std::string("*")+m_strTempRight+
																   std::string(")");
													} else {
														m_DstrTemp=std::string("(")+
																   m_DstrValue+std::string("*")+m_strTempRight+
																   std::string("+")+
																   m_strValue+std::string("*")+m_DstrTempRight+
																   std::string(")");
													}
												
#line 161 "FormulaDerivate.cpp"
			}
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 126 "FormulaDerivate.y"

													m_strTempLeft.push(m_strTemp);
													m_DstrTempLeft.push(m_DstrTemp);
													m_strTemp="";
													m_DstrTemp="";
												
#line 179 "FormulaDerivate.cpp"
			}
		}
		break;
	case 5:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 133 "FormulaDerivate.y"

													m_strValue=m_strTempLeft.top();
													m_DstrValue=m_DstrTempLeft.top();
													m_strTempLeft.pop();
													m_DstrTempLeft.pop();
													m_strTempRight=m_strTemp;
													m_DstrTempRight=m_DstrTemp;
													m_strTemp=std::string("(")+m_strValue+std::string("/")+m_strTempRight+std::string(")");
													
													//S'il ya des zéros dans les dérivées
													//Test pour simplifier l'expression
													if(m_DstrValue.compare(std::string("0"))==0 && 
													   m_DstrTempRight.compare(std::string("0"))==0)
													{
														m_DstrTemp=std::string("0");
													} else
													if(m_DstrValue.compare(std::string("0"))==0)
													{
														m_DstrTemp=std::string("(-")+m_DstrTempRight+std::string("*")+m_strValue+
																   std::string(")/(")+m_strTempRight+
																   std::string(")^2");
													} else
													if(m_DstrTempRight.compare(std::string("0"))==0)
													{
														m_DstrTemp=std::string("(")+m_DstrValue+std::string("*")+m_strTempRight+
																   std::string(")/(")+m_strTempRight+
																   std::string(")^2");
													} else
														m_DstrTemp=std::string("(")+m_DstrValue+std::string("*")+m_strTempRight+
																   std::string("-")+m_DstrTempRight+std::string("*")+m_strValue+
																   std::string(")/(")+m_strTempRight+
																   std::string(")^2");
												
#line 224 "FormulaDerivate.cpp"
			}
		}
		break;
	case 6:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 167 "FormulaDerivate.y"

											m_strTempLeft.push(m_strTemp);
											m_DstrTempLeft.push(m_DstrTemp);
											m_strTemp="";
											m_DstrTemp="";
										
#line 242 "FormulaDerivate.cpp"
			}
		}
		break;
	case 7:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 174 "FormulaDerivate.y"

											m_strValue=m_strTempLeft.top();
											m_DstrValue=m_DstrTempLeft.top();
											m_strTempLeft.pop();
											m_DstrTempLeft.pop();
											m_strTempRight=m_strTemp;
											m_DstrTempRight=m_DstrTemp;
											m_strTemp=std::string("(")+m_strValue+std::string("+")+m_strTempRight+std::string(")");

											//Test simplification
											if(m_DstrValue.compare(std::string("0"))==0 && 
											   m_DstrTempRight.compare(std::string("0"))==0)
											{
												m_DstrTemp=std::string("0");
											} else
											if(m_DstrValue.compare(std::string("0"))==0)
											{
												m_DstrTemp=std::string("(")+m_DstrTempRight+std::string(")");
											} else
											if(m_DstrTempRight.compare(std::string("0"))==0)
											{
												m_DstrTemp=std::string("(")+m_DstrValue+std::string(")");
											} else
												m_DstrTemp=std::string("(")+m_DstrValue+std::string("+")+m_DstrTempRight+std::string(")");
										
#line 279 "FormulaDerivate.cpp"
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
#line 199 "FormulaDerivate.y"

											m_strTempLeft.push(m_strTemp);
											m_DstrTempLeft.push(m_DstrTemp);
											m_strTemp="";
											m_DstrTemp="";
										
#line 297 "FormulaDerivate.cpp"
			}
		}
		break;
	case 9:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 206 "FormulaDerivate.y"

											m_strValue=m_strTempLeft.top();
											m_DstrValue=m_DstrTempLeft.top();
											m_strTempLeft.pop();
											m_DstrTempLeft.pop();
											m_strTempRight=m_strTemp;
											m_DstrTempRight=m_DstrTemp;
											m_strTemp=std::string("(")+m_strValue+std::string("-")+m_strTempRight+std::string(")");
											//Test simplification
											if(m_DstrValue.compare(std::string("0"))==0 && 
											   m_DstrTempRight.compare(std::string("0"))==0)
											{
												m_DstrTemp=std::string("0");
											} else
											if(m_DstrValue.compare(std::string("0"))==0)
											{
												m_DstrTemp=std::string("-(")+m_DstrTempRight+std::string(")");
											} else
											if(m_DstrTempRight.compare(std::string("0"))==0)
											{
												m_DstrTemp=std::string("(")+m_DstrValue+std::string(")");
											} else
												m_DstrTemp=std::string("(")+m_DstrValue+std::string("-")+m_DstrTempRight+std::string(")");
										
#line 333 "FormulaDerivate.cpp"
			}
		}
		break;
	case 10:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 232 "FormulaDerivate.y"

													char buffer[255],Dbuffer[255];
													sprintf(buffer,"%d",yyattribute(3 - 3).ival);
													sprintf(Dbuffer,"%d",yyattribute(3 - 3).ival-1);
													m_strValue=m_strTemp;
													m_DstrValue=m_DstrTemp;
													m_strTemp=std::string("(")+m_strValue+std::string("^")+std::string(buffer)+std::string(")");
													if(m_DstrValue.compare(std::string("0"))==0)
													{
														m_DstrTemp=std::string("0");
													} else {
														m_DstrTemp=std::string("(")+std::string(buffer)+std::string("*")+m_DstrValue+
																   std::string("*")+m_strValue+std::string("^")+std::string(Dbuffer)+std::string(")");
													}
												
#line 360 "FormulaDerivate.cpp"
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 252 "FormulaDerivate.y"

			 									char buffer[255];
												sprintf(buffer,"%.10f",yyattribute(1 - 1).fval);
												m_strTemp+=std::string(buffer);
												m_DstrTemp+=std::string("0");
											
#line 378 "FormulaDerivate.cpp"
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
#line 263 "FormulaDerivate.y"
m_DstrTemp+=std::string("cos(z)");					m_strTemp+=std::string("sin(z)");
#line 391 "FormulaDerivate.cpp"
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
#line 264 "FormulaDerivate.y"
m_DstrTemp+=std::string("(-sin(z))");					m_strTemp+=std::string("cos(z)");
#line 404 "FormulaDerivate.cpp"
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
#line 265 "FormulaDerivate.y"
m_DstrTemp+=std::string("exp(z)");					m_strTemp+=std::string("exp(z)");
#line 417 "FormulaDerivate.cpp"
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
#line 266 "FormulaDerivate.y"
m_DstrTemp+=std::string("(1+tan(z)*tan(z))");			m_strTemp+=std::string("tan(z)");
#line 430 "FormulaDerivate.cpp"
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
#line 267 "FormulaDerivate.y"
m_DstrTemp+=std::string("(-(1+cotan(z)*cotan(z)))");	m_strTemp+=std::string("cotan(z)");
#line 443 "FormulaDerivate.cpp"
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
#line 268 "FormulaDerivate.y"
m_DstrTemp+=std::string("(1/z)");						m_strTemp+=std::string("log(z)");
#line 456 "FormulaDerivate.cpp"
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
#line 269 "FormulaDerivate.y"
m_DstrTemp+=std::string("(1/sqrt(1-z^2))");			m_strTemp+=std::string("asin(z)");
#line 469 "FormulaDerivate.cpp"
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
#line 270 "FormulaDerivate.y"
m_DstrTemp+=std::string("(-(1/sqrt(1-z^2)))");		m_strTemp+=std::string("acos(z)");
#line 482 "FormulaDerivate.cpp"
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
#line 271 "FormulaDerivate.y"
m_DstrTemp+=std::string("(1/(1+z^2))");			m_strTemp+=std::string("atan(z)");
#line 495 "FormulaDerivate.cpp"
			}
		}
		break;
	case 21:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 272 "FormulaDerivate.y"
m_DstrTemp+=std::string("(-(1/(1+z^2)))");			m_strTemp+=std::string("acotan(z)");
#line 508 "FormulaDerivate.cpp"
			}
		}
		break;
	case 22:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 273 "FormulaDerivate.y"
m_DstrTemp+=std::string("(1/(2*sqrt(z)))");		m_strTemp+=std::string("sqrt(z)");
#line 521 "FormulaDerivate.cpp"
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
#line 283 "FormulaDerivate.y"

						m_strTemp+=std::string("Z");
						m_DstrTemp+=std::string("1");
					
#line 537 "FormulaDerivate.cpp"
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 287 "FormulaDerivate.y"

											char buffer[255],buffer1[255];
											sprintf(buffer,"%d",yyattribute(3 - 3).ival);
											sprintf(buffer1,"%d",yyattribute(3 - 3).ival-1);
											m_strTemp+=std::string("Z^")+std::string(buffer);
											m_DstrTemp+=std::string(buffer)+std::string("*Z^")+std::string(buffer1);
										
#line 556 "FormulaDerivate.cpp"
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 296 "FormulaDerivate.y"

									m_strTemp+=std::string("@init");
									m_DstrTemp+=std::string("0");
								
#line 572 "FormulaDerivate.cpp"
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
#line 300 "FormulaDerivate.y"

									m_strTemp+=std::string("#pixel");
									m_DstrTemp+=std::string("0");
								
#line 588 "FormulaDerivate.cpp"
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
#line 310 "FormulaDerivate.y"
 char   *string; (*(YYSTYPE YYFAR*)yyvalptr).fval = (double) strtod(m_plexer->yytext,&string); _TRACE_INFO(_STR("%.10f",(*(YYSTYPE YYFAR*)yyvalptr).fval)); 
#line 601 "FormulaDerivate.cpp"
			}
		}
		break;
	case 28:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 317 "FormulaDerivate.y"
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (int) yyattribute(1 - 1).fval; 
#line 614 "FormulaDerivate.cpp"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}
#line 320 "FormulaDerivate.y"


CDataDerivateParser::~CDataDerivateParser()
{
	delete m_plexer;
}

CDataDerivateLexer* CDataDerivateParser::CreateLexer()
{
	m_plexer=new CDataDerivateLexer;

	if (!yycreate(m_plexer)) {
		return 0;
	}

	m_plexer->Create(this);

	return m_plexer;	// success
}

void CDataDerivateParser::SetOutputString(std::string *pstr)
{
	m_pstr=pstr;
}

int CDataDerivateParser::GetResult()
{
	return m_Result;
}
#line 653 "FormulaDerivate.cpp"
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
		{ NULL, 0 }
	};
	yysymbol = symbol;

	static const char* const YYNEARFAR YYBASED_CODE rule[] = {
		"$accept: file",
		"file: addsub_expr",
		"file: error",
		"$$1:",
		"addsub_expr: addsub_expr $$1 MULT_TOKEN addsub_expr",
		"$$2:",
		"addsub_expr: addsub_expr $$2 DIV_TOKEN addsub_expr",
		"$$3:",
		"addsub_expr: addsub_expr $$3 PLUS_TOKEN addsub_expr",
		"$$4:",
		"addsub_expr: addsub_expr $$4 DASH_TOKEN addsub_expr",
		"addsub_expr: \'(\' addsub_expr \')\'",
		"addsub_expr: element_expr",
		"addsub_expr: addsub_expr HAT_TOKEN integer",
		"element_expr: puiss_expr",
		"element_expr: constant",
		"element_expr: double",
		"func_expr: SIN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: COS_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: EXP_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: TAN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: COTAN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: LOG_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: ASIN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: ACOS_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: ATAN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: ACOTAN_TOKEN \'(\' QUATER_TOKEN \')\'",
		"func_expr: SQRT_TOKEN \'(\' QUATER_TOKEN \')\'",
		"puiss_expr: puiss_quater",
		"puiss_expr: func_expr",
		"puiss_quater: QUATER_TOKEN",
		"puiss_quater: QUATER_TOKEN HAT_TOKEN integer",
		"constant: INIT_TOKEN",
		"constant: PIXEL_TOKEN",
		"double: fexpr",
		"fexpr: FLOAT_TOKEN",
		"integer: double"
	};
	yyrule = rule;
#endif

	static const yyreduction_t YYNEARFAR YYBASED_CODE reduction[] = {
		{ 0, 1, -1 },
		{ 1, 1, 0 },
		{ 1, 1, 1 },
		{ 3, 0, 2 },
		{ 2, 4, 3 },
		{ 4, 0, 4 },
		{ 2, 4, 5 },
		{ 5, 0, 6 },
		{ 2, 4, 7 },
		{ 6, 0, 8 },
		{ 2, 4, 9 },
		{ 2, 3, -1 },
		{ 2, 1, -1 },
		{ 2, 3, 10 },
		{ 7, 1, -1 },
		{ 7, 1, -1 },
		{ 7, 1, 11 },
		{ 8, 4, 12 },
		{ 8, 4, 13 },
		{ 8, 4, 14 },
		{ 8, 4, 15 },
		{ 8, 4, 16 },
		{ 8, 4, 17 },
		{ 8, 4, 18 },
		{ 8, 4, 19 },
		{ 8, 4, 20 },
		{ 8, 4, 21 },
		{ 8, 4, 22 },
		{ 9, 1, -1 },
		{ 9, 1, -1 },
		{ 10, 1, 23 },
		{ 10, 3, 24 },
		{ 11, 1, 25 },
		{ 11, 1, 26 },
		{ 12, 1, -1 },
		{ 13, 1, 27 },
		{ 14, 1, 28 }
	};
	yyreduction = reduction;

	static const yytokenaction_t YYNEARFAR YYBASED_CODE tokenaction[] = {
		{ 63, YYAT_SHIFT, 1 },
		{ 27, YYAT_SHIFT, 45 },
		{ 78, YYAT_REDUCE, 7 },
		{ 78, YYAT_REDUCE, 3 },
		{ 78, YYAT_SHIFT, 40 },
		{ 78, YYAT_REDUCE, 9 },
		{ 78, YYAT_REDUCE, 5 },
		{ 21, YYAT_REDUCE, 7 },
		{ 21, YYAT_REDUCE, 3 },
		{ 21, YYAT_SHIFT, 40 },
		{ 21, YYAT_REDUCE, 9 },
		{ 21, YYAT_REDUCE, 5 },
		{ 77, YYAT_REDUCE, 7 },
		{ 77, YYAT_REDUCE, 3 },
		{ 77, YYAT_SHIFT, 40 },
		{ 58, YYAT_SHIFT, 74 },
		{ 77, YYAT_REDUCE, 5 },
		{ 76, YYAT_REDUCE, 3 },
		{ 76, YYAT_SHIFT, 40 },
		{ 57, YYAT_SHIFT, 73 },
		{ 76, YYAT_REDUCE, 5 },
		{ 75, YYAT_REDUCE, 3 },
		{ 75, YYAT_SHIFT, 40 },
		{ 56, YYAT_SHIFT, 72 },
		{ 55, YYAT_SHIFT, 71 },
		{ 54, YYAT_SHIFT, 70 },
		{ 53, YYAT_SHIFT, 69 },
		{ 52, YYAT_SHIFT, 68 },
		{ 51, YYAT_SHIFT, 67 },
		{ 50, YYAT_SHIFT, 66 },
		{ 49, YYAT_SHIFT, 65 },
		{ 48, YYAT_SHIFT, 64 },
		{ 44, YYAT_SHIFT, 63 },
		{ 43, YYAT_SHIFT, 62 },
		{ 42, YYAT_SHIFT, 61 },
		{ 41, YYAT_SHIFT, 60 },
		{ 40, YYAT_SHIFT, 15 },
		{ 39, YYAT_SHIFT, 58 },
		{ 38, YYAT_SHIFT, 57 },
		{ 37, YYAT_SHIFT, 56 },
		{ 36, YYAT_SHIFT, 55 },
		{ 35, YYAT_SHIFT, 54 },
		{ 34, YYAT_SHIFT, 53 },
		{ 33, YYAT_SHIFT, 52 },
		{ 32, YYAT_SHIFT, 51 },
		{ 31, YYAT_SHIFT, 50 },
		{ 30, YYAT_SHIFT, 49 },
		{ 29, YYAT_SHIFT, 48 },
		{ 20, YYAT_ACCEPT, 0 },
		{ 14, YYAT_SHIFT, 39 },
		{ 13, YYAT_SHIFT, 38 },
		{ 12, YYAT_SHIFT, 37 },
		{ 11, YYAT_SHIFT, 36 },
		{ 10, YYAT_SHIFT, 35 },
		{ 9, YYAT_SHIFT, 34 },
		{ 8, YYAT_SHIFT, 33 },
		{ 7, YYAT_SHIFT, 32 },
		{ 6, YYAT_SHIFT, 31 },
		{ 5, YYAT_SHIFT, 30 },
		{ 4, YYAT_SHIFT, 29 },
		{ 3, YYAT_SHIFT, 28 },
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
		{ 63, YYAT_SHIFT, 3 },
		{ 63, YYAT_SHIFT, 4 },
		{ 63, YYAT_SHIFT, 5 },
		{ 63, YYAT_SHIFT, 6 },
		{ 63, YYAT_SHIFT, 7 },
		{ 63, YYAT_SHIFT, 8 },
		{ 63, YYAT_SHIFT, 9 },
		{ 63, YYAT_SHIFT, 10 },
		{ 63, YYAT_SHIFT, 11 },
		{ 63, YYAT_SHIFT, 12 },
		{ 63, YYAT_SHIFT, 13 },
		{ 63, YYAT_SHIFT, 14 },
		{ -1, YYAT_ERROR, 0 },
		{ 63, YYAT_SHIFT, 16 },
		{ 63, YYAT_SHIFT, 17 },
		{ -1, YYAT_ERROR, 0 },
		{ 27, YYAT_REDUCE, 3 },
		{ 27, YYAT_SHIFT, 40 },
		{ 27, YYAT_REDUCE, 9 },
		{ 27, YYAT_REDUCE, 5 }
	};
	yytokenaction = tokenaction;
	yytokenaction_size = 237;

	static const yystateaction_t YYNEARFAR YYBASED_CODE stateaction[] = {
		{ -195, 1, YYAT_DEFAULT, 63 },
		{ 0, 0, YYAT_DEFAULT, 63 },
		{ 0, 0, YYAT_REDUCE, 2 },
		{ -214, 1, YYAT_REDUCE, 30 },
		{ 19, 1, YYAT_DEFAULT, 14 },
		{ 18, 1, YYAT_DEFAULT, 14 },
		{ 17, 1, YYAT_DEFAULT, 14 },
		{ 16, 1, YYAT_DEFAULT, 14 },
		{ 15, 1, YYAT_DEFAULT, 14 },
		{ 14, 1, YYAT_DEFAULT, 14 },
		{ 13, 1, YYAT_DEFAULT, 14 },
		{ 12, 1, YYAT_DEFAULT, 14 },
		{ 11, 1, YYAT_DEFAULT, 14 },
		{ 10, 1, YYAT_DEFAULT, 14 },
		{ 9, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 35 },
		{ 0, 0, YYAT_REDUCE, 33 },
		{ 0, 0, YYAT_REDUCE, 32 },
		{ 0, 0, YYAT_REDUCE, 34 },
		{ 0, 0, YYAT_REDUCE, 16 },
		{ 48, 1, YYAT_ERROR, 0 },
		{ -265, 1, YYAT_REDUCE, 1 },
		{ 0, 0, YYAT_REDUCE, 12 },
		{ 0, 0, YYAT_REDUCE, 14 },
		{ 0, 0, YYAT_REDUCE, 15 },
		{ 0, 0, YYAT_REDUCE, 29 },
		{ 0, 0, YYAT_REDUCE, 28 },
		{ -40, 1, YYAT_REDUCE, 7 },
		{ 0, 0, YYAT_DEFAULT, 40 },
		{ -210, 1, YYAT_DEFAULT, 39 },
		{ -211, 1, YYAT_DEFAULT, 39 },
		{ -212, 1, YYAT_DEFAULT, 39 },
		{ -213, 1, YYAT_DEFAULT, 39 },
		{ -214, 1, YYAT_DEFAULT, 39 },
		{ -215, 1, YYAT_DEFAULT, 39 },
		{ -216, 1, YYAT_DEFAULT, 39 },
		{ -217, 1, YYAT_DEFAULT, 39 },
		{ -218, 1, YYAT_DEFAULT, 39 },
		{ -219, 1, YYAT_DEFAULT, 39 },
		{ -220, 1, YYAT_ERROR, 0 },
		{ -233, 1, YYAT_ERROR, 0 },
		{ -238, 1, YYAT_ERROR, 0 },
		{ -242, 1, YYAT_ERROR, 0 },
		{ -239, 1, YYAT_ERROR, 0 },
		{ -243, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 11 },
		{ 0, 0, YYAT_REDUCE, 36 },
		{ 0, 0, YYAT_REDUCE, 31 },
		{ -10, 1, YYAT_DEFAULT, 58 },
		{ -11, 1, YYAT_DEFAULT, 58 },
		{ -12, 1, YYAT_DEFAULT, 58 },
		{ -13, 1, YYAT_DEFAULT, 58 },
		{ -14, 1, YYAT_DEFAULT, 58 },
		{ -15, 1, YYAT_DEFAULT, 58 },
		{ -16, 1, YYAT_DEFAULT, 58 },
		{ -17, 1, YYAT_DEFAULT, 58 },
		{ -18, 1, YYAT_DEFAULT, 58 },
		{ -22, 1, YYAT_DEFAULT, 58 },
		{ -26, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 13 },
		{ 0, 0, YYAT_DEFAULT, 63 },
		{ 0, 0, YYAT_DEFAULT, 63 },
		{ 0, 0, YYAT_DEFAULT, 63 },
		{ -40, 1, YYAT_DEFAULT, 40 },
		{ 0, 0, YYAT_REDUCE, 19 },
		{ 0, 0, YYAT_REDUCE, 17 },
		{ 0, 0, YYAT_REDUCE, 18 },
		{ 0, 0, YYAT_REDUCE, 20 },
		{ 0, 0, YYAT_REDUCE, 22 },
		{ 0, 0, YYAT_REDUCE, 21 },
		{ 0, 0, YYAT_REDUCE, 23 },
		{ 0, 0, YYAT_REDUCE, 24 },
		{ 0, 0, YYAT_REDUCE, 25 },
		{ 0, 0, YYAT_REDUCE, 26 },
		{ 0, 0, YYAT_REDUCE, 27 },
		{ -252, 1, YYAT_REDUCE, 4 },
		{ -256, 1, YYAT_REDUCE, 6 },
		{ -260, 1, YYAT_REDUCE, 8 },
		{ -270, 1, YYAT_REDUCE, 10 }
	};
	yystateaction = stateaction;

	static const yynontermgoto_t YYNEARFAR YYBASED_CODE nontermgoto[] = {
		{ 63, 78 },
		{ 78, 41 },
		{ 78, 42 },
		{ 78, 43 },
		{ 78, 44 },
		{ 63, 22 },
		{ 63, 25 },
		{ 63, 23 },
		{ 63, 26 },
		{ 63, 24 },
		{ 63, 19 },
		{ 63, 18 },
		{ 40, 46 },
		{ 40, 18 },
		{ 40, 59 },
		{ 0, 20 },
		{ 0, 21 },
		{ 62, 77 },
		{ 61, 76 },
		{ 60, 75 },
		{ 28, 47 },
		{ 1, 27 }
	};
	yynontermgoto = nontermgoto;
	yynontermgoto_size = 22;

	static const yystategoto_t YYNEARFAR YYBASED_CODE stategoto[] = {
		{ 14, 63 },
		{ 19, 63 },
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
		{ 0, 78 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, 78 },
		{ 6, 40 },
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
		{ 0, -1 },
		{ 0, -1 },
		{ 17, 63 },
		{ 16, 63 },
		{ 15, 63 },
		{ -2, -1 },
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
		{ 0, 78 },
		{ 0, 78 },
		{ 0, 78 },
		{ -2, -1 }
	};
	yystategoto = stategoto;

	yydestructorptr = NULL;

	yytokendestptr = NULL;
	yytokendest_size = 0;
	yytokendestbase = 0;
}
