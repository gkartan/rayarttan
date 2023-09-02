#include <cyacc.h>

#line 1 "FormulaDerivatePreProc.y"

/* Dérivation symbolique à partir d'une chaine
 * G.CADOU mai 2002
 */
#pragma warning(disable : 4530)
#include "TraceService.h"
#include "ListExpr.h"
#include <string>
#include "FormulaDerivatePreProc.l.h"


#line 16 "FormulaDerivatePreProc.cpp"
// repeated because of possible precompiled header
#include <cyacc.h>

#include "FormulaDerivatePreProc.h"

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
#line 72 "FormulaDerivatePreProc.y"
	
									(*m_pstr)=m_strTempFinal;
									m_Result=0;
								
#line 77 "FormulaDerivatePreProc.cpp"
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
#line 76 "FormulaDerivatePreProc.y"

									(*m_pstr)=m_strTempFinal;
									m_Result=-1;
								
#line 93 "FormulaDerivatePreProc.cpp"
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
#line 85 "FormulaDerivatePreProc.y"

								Compute(m_strTemp); 
								m_strTempFinal+=m_strTemp;
								m_strTemp="";
								
#line 110 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 3:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 98 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("+");
#line 123 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 101 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("+");
#line 136 "FormulaDerivatePreProc.cpp"
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
#line 102 "FormulaDerivatePreProc.y"

									char buffer[255]; 
									sprintf(buffer,"%.9f",yyattribute(4 - 4).fval);
									m_strTempFinal+=std::string(buffer);
								
#line 153 "FormulaDerivatePreProc.cpp"
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
#line 108 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("+");
#line 166 "FormulaDerivatePreProc.cpp"
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
#line 109 "FormulaDerivatePreProc.y"
 
								  Compute(m_strTemp); 
								  m_strTempFinal+=m_strTemp;
								  m_strTemp="";	
								
#line 183 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 8:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 116 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("+");
#line 196 "FormulaDerivatePreProc.cpp"
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
#line 119 "FormulaDerivatePreProc.y"

									char buffer[255]; 
									sprintf(buffer,"%.9f",yyattribute(1 - 1).fval);
									m_strTempFinal+=std::string(buffer);
								
#line 213 "FormulaDerivatePreProc.cpp"
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
#line 124 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("+");
#line 226 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 131 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("-");
#line 239 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 12:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 135 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("-");
#line 252 "FormulaDerivatePreProc.cpp"
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
#line 136 "FormulaDerivatePreProc.y"
 
								  Compute(m_strTemp); 
								  m_strTempFinal+=m_strTemp;
								  m_strTemp="";	
								
#line 269 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 14:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 142 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("-");
#line 282 "FormulaDerivatePreProc.cpp"
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
#line 143 "FormulaDerivatePreProc.y"
m_strTempFinal+=m_strTemp;
#line 295 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 16:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 153 "FormulaDerivatePreProc.y"

									char buffer[255]; 
									sprintf(buffer,"%.9f",yyattribute(1 - 1).fval);
									m_strTempFinal+=std::string(buffer);
								
#line 312 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 17:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 158 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("-");
#line 325 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 18:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 161 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("-");
#line 338 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 19:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 171 "FormulaDerivatePreProc.y"
 m_count=m_counttemp;
#line 351 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 20:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 174 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("(");
#line 364 "FormulaDerivatePreProc.cpp"
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
#line 176 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string(")");m_bExprFuncOnly=true;
#line 377 "FormulaDerivatePreProc.cpp"
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
#line 184 "FormulaDerivatePreProc.y"

												m_strTempFinal+=std::string("*");
												m_count=m_counttemp; 
											
#line 393 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 189 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("*");
#line 406 "FormulaDerivatePreProc.cpp"
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
#line 193 "FormulaDerivatePreProc.y"

											
#line 420 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 195 "FormulaDerivatePreProc.y"

											
#line 434 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 26:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 198 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("*");
#line 447 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 27:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 201 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("*(");
#line 460 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 28:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 203 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string(")");m_strTemp="";m_bExprFuncOnly=true;
#line 473 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 29:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 211 "FormulaDerivatePreProc.y"

											
#line 487 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 30:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 213 "FormulaDerivatePreProc.y"

											
#line 501 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 31:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 215 "FormulaDerivatePreProc.y"

											
#line 515 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 32:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 217 "FormulaDerivatePreProc.y"
								  
												Compute(m_strTemp); 
												m_strTempFinal+=m_strTemp;
												m_strTemp="";	
												m_strTempFinal+=std::string("/");
											
#line 533 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 33:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
#line 225 "FormulaDerivatePreProc.y"

												char buffer[255]; 
												sprintf(buffer,"%.9f",yyattribute(1 - 2).fval);
												m_strTempFinal+=std::string(buffer)+std::string("/");
											
#line 550 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 34:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 232 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("/(");
#line 563 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 35:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
#line 233 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string(")");m_strTemp="";m_bExprFuncOnly=true;
#line 576 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 36:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 237 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("sin(z)");m_bExprFuncOnly=true;
#line 589 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 37:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 238 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("cos(z)");m_bExprFuncOnly=true;
#line 602 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 38:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 239 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("exp(z)");m_bExprFuncOnly=true;
#line 615 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 39:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 240 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("tan(z)");m_bExprFuncOnly=true;
#line 628 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 40:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 241 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("cotan(z)");m_bExprFuncOnly=true;
#line 641 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 41:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 242 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("log(z)");m_bExprFuncOnly=true;
#line 654 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 42:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 243 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("asin(z)");m_bExprFuncOnly=true;
#line 667 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 43:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 244 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("acos(z)");m_bExprFuncOnly=true;
#line 680 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 44:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 245 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("atan(z)");m_bExprFuncOnly=true;
#line 693 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 45:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 246 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("acotan(z)");m_bExprFuncOnly=true;
#line 706 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 46:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
#line 247 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("sqrt(z)");m_bExprFuncOnly=true;
#line 719 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 47:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 255 "FormulaDerivatePreProc.y"
m_counttemp=1;m_bExprFuncOnly=false;
#line 732 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 48:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
#line 256 "FormulaDerivatePreProc.y"
m_counttemp=yyattribute(3 - 3).ival;m_bExprFuncOnly=false;
#line 745 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 49:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 259 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("@init");
#line 758 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 50:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 260 "FormulaDerivatePreProc.y"
m_strTempFinal+=std::string("#pixel");
#line 771 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 51:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 264 "FormulaDerivatePreProc.y"
_TRACE_INFO(_STR("%.9f",(*(YYSTYPE YYFAR*)yyvalptr).fval));
#line 784 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 52:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 267 "FormulaDerivatePreProc.y"
 char   *string; (*(YYSTYPE YYFAR*)yyvalptr).fval = (double) strtod(m_plexer->yytext,&string);
#line 797 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	case 53:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
#line 274 "FormulaDerivatePreProc.y"
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (int) yyattribute(1 - 1).fval; 
#line 810 "FormulaDerivatePreProc.cpp"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}
#line 277 "FormulaDerivatePreProc.y"


CDataDerivatePreProcParser::~CDataDerivatePreProcParser()
{
	delete m_plexer;
}

CDataDerivatePreProcLexer* CDataDerivatePreProcParser::CreateLexer()
{
	m_plexer=new CDataDerivatePreProcLexer;

	m_bExprFuncOnly=false;
	m_Coeff=1;
	m_CoeffTemp=1;
	m_count=0;
	m_counttemp=0;

	if (!yycreate(m_plexer)) {
		return 0;
	}

	m_plexer->Create(this);

	return m_plexer;	// success
}

void CDataDerivatePreProcParser::SetOutputString(std::string *pstr)
{
	m_pstr=pstr;
}

void CDataDerivatePreProcParser::Compute(std::string &str)
{
	if(m_bExprFuncOnly) return;

	char  buffer[200];
	sprintf(buffer,"%d",m_count);

	if(m_Coeff!=1)
	{
		char CoeffBuffer[200];
		sprintf(CoeffBuffer,"%d",m_Coeff);
		str+=std::string(CoeffBuffer)+std::string("*");					
	}

	switch(m_count)
	{
		case 0:
			{
				char CoeffBuffer[200];
				sprintf(CoeffBuffer,"%d",m_Coeff);
				str+=std::string(CoeffBuffer);
			}
		break;
		case 1:
			{
				str+=std::string("Z");
			}
		break;
		default:
			{
				str+=std::string("Z^")+std::string(buffer);
			}

	}
}

int CDataDerivatePreProcParser::GetResult()
{
	return m_Result;
}
#line 891 "FormulaDerivatePreProc.cpp"
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
		"addsub_expr: func_expr",
		"addsub_expr: multdiv_expr",
		"addsub_expr: add_expr",
		"addsub_expr: sub_expr",
		"$$1:",
		"add_expr: addsub_expr PLUS_TOKEN $$1 func_expr",
		"$$2:",
		"add_expr: addsub_expr PLUS_TOKEN $$2 double",
		"$$3:",
		"add_expr: addsub_expr PLUS_TOKEN $$3 multdiv_expr",
		"$$4:",
		"add_expr: addsub_expr PLUS_TOKEN $$4 constant",
		"$$5:",
		"$$6:",
		"add_expr: double $$5 PLUS_TOKEN $$6 addsub_expr",
		"$$7:",
		"sub_expr: addsub_expr DASH_TOKEN $$7 func_expr",
		"$$8:",
		"sub_expr: addsub_expr DASH_TOKEN $$8 multdiv_expr",
		"$$9:",
		"sub_expr: addsub_expr DASH_TOKEN $$9 constant",
		"$$10:",
		"$$11:",
		"sub_expr: double $$10 DASH_TOKEN $$11 addsub_expr",
		"$$12:",
		"sub_expr: DASH_TOKEN $$12 \'(\' addsub_expr \')\'",
		"multdiv_expr: puiss_expr",
		"multdiv_expr: mult_expr",
		"multdiv_expr: div_expr",
		"$$13:",
		"multdiv_expr: \'(\' $$13 addsub_expr \')\'",
		"mult_expr: addsub_expr MULT_TOKEN puiss_expr",
		"$$14:",
		"mult_expr: addsub_expr MULT_TOKEN $$14 constant",
		"mult_expr: addsub_expr MULT_TOKEN double",
		"mult_expr: double MULT_TOKEN multdiv_expr",
		"$$15:",
		"mult_expr: addsub_expr MULT_TOKEN $$15 func_expr",
		"$$16:",
		"mult_expr: addsub_expr MULT_TOKEN \'(\' $$16 addsub_expr \')\'",
		"div_expr: multdiv_expr DIV_TOKEN puiss_expr",
		"div_expr: multdiv_expr DIV_TOKEN constant",
		"div_expr: multdiv_expr DIV_TOKEN double",
		"$$17:",
		"div_expr: multdiv_expr DIV_TOKEN $$17 func_expr",
		"$$18:",
		"div_expr: double DIV_TOKEN $$18 multdiv_expr",
		"$$19:",
		"div_expr: multdiv_expr DIV_TOKEN \'(\' $$19 addsub_expr \')\'",
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
		{ 2, 1, -1 },
		{ 2, 1, 2 },
		{ 2, 1, -1 },
		{ 2, 1, -1 },
		{ 4, 0, 3 },
		{ 3, 4, -1 },
		{ 5, 0, 4 },
		{ 3, 4, 5 },
		{ 6, 0, 6 },
		{ 3, 4, 7 },
		{ 7, 0, 8 },
		{ 3, 4, -1 },
		{ 8, 0, 9 },
		{ 9, 0, 10 },
		{ 3, 5, -1 },
		{ 11, 0, 11 },
		{ 10, 4, -1 },
		{ 12, 0, 12 },
		{ 10, 4, 13 },
		{ 13, 0, 14 },
		{ 10, 4, 15 },
		{ 14, 0, 16 },
		{ 15, 0, 17 },
		{ 10, 5, -1 },
		{ 16, 0, 18 },
		{ 10, 5, -1 },
		{ 17, 1, 19 },
		{ 17, 1, -1 },
		{ 17, 1, -1 },
		{ 18, 0, 20 },
		{ 17, 4, 21 },
		{ 19, 3, 22 },
		{ 20, 0, 23 },
		{ 19, 4, -1 },
		{ 19, 3, 24 },
		{ 19, 3, 25 },
		{ 21, 0, 26 },
		{ 19, 4, -1 },
		{ 22, 0, 27 },
		{ 19, 6, 28 },
		{ 23, 3, 29 },
		{ 23, 3, 30 },
		{ 23, 3, 31 },
		{ 24, 0, 32 },
		{ 23, 4, -1 },
		{ 25, 0, 33 },
		{ 23, 4, -1 },
		{ 26, 0, 34 },
		{ 23, 6, 35 },
		{ 27, 4, 36 },
		{ 27, 4, 37 },
		{ 27, 4, 38 },
		{ 27, 4, 39 },
		{ 27, 4, 40 },
		{ 27, 4, 41 },
		{ 27, 4, 42 },
		{ 27, 4, 43 },
		{ 27, 4, 44 },
		{ 27, 4, 45 },
		{ 27, 4, 46 },
		{ 28, 1, -1 },
		{ 29, 1, 47 },
		{ 29, 3, 48 },
		{ 30, 1, 49 },
		{ 30, 1, 50 },
		{ 31, 1, 51 },
		{ 32, 1, 52 },
		{ 33, 1, 53 }
	};
	yyreduction = reduction;

	static const yytokenaction_t YYNEARFAR YYBASED_CODE tokenaction[] = {
		{ 474, YYAT_SHIFT, 51 },
		{ 446, YYAT_SHIFT, 462 },
		{ 446, YYAT_SHIFT, 463 },
		{ 446, YYAT_SHIFT, 464 },
		{ 446, YYAT_SHIFT, 465 },
		{ 446, YYAT_SHIFT, 466 },
		{ 446, YYAT_SHIFT, 467 },
		{ 446, YYAT_SHIFT, 468 },
		{ 446, YYAT_SHIFT, 469 },
		{ 446, YYAT_SHIFT, 470 },
		{ 446, YYAT_SHIFT, 471 },
		{ 446, YYAT_SHIFT, 472 },
		{ 245, YYAT_SHIFT, 51 },
		{ 122, YYAT_SHIFT, 1 },
		{ 399, YYAT_SHIFT, 180 },
		{ 399, YYAT_SHIFT, 404 },
		{ 500, YYAT_SHIFT, 512 },
		{ 399, YYAT_SHIFT, 181 },
		{ 488, YYAT_SHIFT, 501 },
		{ 434, YYAT_SHIFT, 352 },
		{ 184, YYAT_SHIFT, 4 },
		{ 184, YYAT_SHIFT, 5 },
		{ 184, YYAT_SHIFT, 6 },
		{ 184, YYAT_SHIFT, 7 },
		{ 184, YYAT_SHIFT, 8 },
		{ 184, YYAT_SHIFT, 9 },
		{ 184, YYAT_SHIFT, 10 },
		{ 184, YYAT_SHIFT, 11 },
		{ 184, YYAT_SHIFT, 12 },
		{ 184, YYAT_SHIFT, 13 },
		{ 184, YYAT_SHIFT, 14 },
		{ 181, YYAT_REDUCE, 20 },
		{ 382, YYAT_SHIFT, 150 },
		{ 382, YYAT_SHIFT, 151 },
		{ 180, YYAT_REDUCE, 11 },
		{ 382, YYAT_SHIFT, 152 },
		{ 499, YYAT_SHIFT, 511 },
		{ 184, YYAT_SHIFT, 16 },
		{ 498, YYAT_SHIFT, 510 },
		{ 273, YYAT_ERROR, 0 },
		{ 497, YYAT_SHIFT, 509 },
		{ 405, YYAT_SHIFT, 440 },
		{ 381, YYAT_SHIFT, 150 },
		{ 381, YYAT_SHIFT, 151 },
		{ 354, YYAT_SHIFT, 402 },
		{ 381, YYAT_SHIFT, 152 },
		{ 354, YYAT_REDUCE, 24 },
		{ 354, YYAT_SHIFT, 403 },
		{ 277, YYAT_SHIFT, 47 },
		{ 277, YYAT_SHIFT, 48 },
		{ 404, YYAT_SHIFT, 435 },
		{ 277, YYAT_SHIFT, 49 },
		{ 276, YYAT_SHIFT, 47 },
		{ 276, YYAT_SHIFT, 48 },
		{ 496, YYAT_SHIFT, 508 },
		{ 276, YYAT_SHIFT, 49 },
		{ 153, YYAT_SHIFT, 247 },
		{ 20, YYAT_SHIFT, 47 },
		{ 20, YYAT_SHIFT, 48 },
		{ 50, YYAT_SHIFT, 124 },
		{ 20, YYAT_SHIFT, 49 },
		{ 229, YYAT_SHIFT, 145 },
		{ 438, YYAT_SHIFT, 441 },
		{ 438, YYAT_SHIFT, 442 },
		{ 229, YYAT_SHIFT, 146 },
		{ 244, YYAT_ERROR, 0 },
		{ 121, YYAT_ERROR, 0 },
		{ 151, YYAT_SHIFT, 239 },
		{ 103, YYAT_SHIFT, 43 },
		{ 275, YYAT_SHIFT, 361 },
		{ 275, YYAT_SHIFT, 362 },
		{ 103, YYAT_SHIFT, 44 },
		{ 246, YYAT_SHIFT, 312 },
		{ 246, YYAT_SHIFT, 313 },
		{ 48, YYAT_SHIFT, 116 },
		{ 253, YYAT_SHIFT, 317 },
		{ 253, YYAT_SHIFT, 318 },
		{ 253, YYAT_SHIFT, 319 },
		{ 253, YYAT_SHIFT, 320 },
		{ 253, YYAT_SHIFT, 321 },
		{ 253, YYAT_SHIFT, 322 },
		{ 253, YYAT_SHIFT, 323 },
		{ 253, YYAT_SHIFT, 324 },
		{ 253, YYAT_SHIFT, 325 },
		{ 253, YYAT_SHIFT, 326 },
		{ 253, YYAT_SHIFT, 327 },
		{ 130, YYAT_SHIFT, 195 },
		{ 130, YYAT_SHIFT, 196 },
		{ 130, YYAT_SHIFT, 197 },
		{ 130, YYAT_SHIFT, 198 },
		{ 130, YYAT_SHIFT, 199 },
		{ 130, YYAT_SHIFT, 200 },
		{ 130, YYAT_SHIFT, 201 },
		{ 130, YYAT_SHIFT, 202 },
		{ 130, YYAT_SHIFT, 203 },
		{ 130, YYAT_SHIFT, 204 },
		{ 130, YYAT_SHIFT, 205 },
		{ 242, YYAT_SHIFT, 248 },
		{ 242, YYAT_SHIFT, 249 },
		{ 123, YYAT_SHIFT, 190 },
		{ 123, YYAT_SHIFT, 191 },
		{ 119, YYAT_SHIFT, 125 },
		{ 119, YYAT_SHIFT, 126 },
		{ 495, YYAT_SHIFT, 507 },
		{ 494, YYAT_SHIFT, 506 },
		{ 493, YYAT_SHIFT, 505 },
		{ 492, YYAT_SHIFT, 504 },
		{ 491, YYAT_SHIFT, 503 },
		{ 490, YYAT_SHIFT, 502 },
		{ 487, YYAT_SHIFT, 500 },
		{ 486, YYAT_SHIFT, 499 },
		{ 485, YYAT_SHIFT, 498 },
		{ 484, YYAT_SHIFT, 497 },
		{ 483, YYAT_SHIFT, 496 },
		{ 482, YYAT_SHIFT, 495 },
		{ 481, YYAT_SHIFT, 494 },
		{ 480, YYAT_SHIFT, 493 },
		{ 479, YYAT_SHIFT, 492 },
		{ 478, YYAT_SHIFT, 491 },
		{ 477, YYAT_SHIFT, 490 },
		{ 476, YYAT_SHIFT, 489 },
		{ 472, YYAT_SHIFT, 487 },
		{ 471, YYAT_SHIFT, 486 },
		{ 470, YYAT_SHIFT, 485 },
		{ 469, YYAT_SHIFT, 484 },
		{ 468, YYAT_SHIFT, 483 },
		{ 467, YYAT_SHIFT, 482 },
		{ 466, YYAT_SHIFT, 481 },
		{ 465, YYAT_SHIFT, 480 },
		{ 464, YYAT_SHIFT, 479 },
		{ 463, YYAT_SHIFT, 478 },
		{ 462, YYAT_SHIFT, 477 },
		{ 459, YYAT_SHIFT, 405 },
		{ 430, YYAT_SHIFT, 458 },
		{ 428, YYAT_SHIFT, 457 },
		{ 427, YYAT_SHIFT, 456 },
		{ 426, YYAT_SHIFT, 455 },
		{ 425, YYAT_SHIFT, 454 },
		{ 424, YYAT_SHIFT, 453 },
		{ 423, YYAT_SHIFT, 452 },
		{ 422, YYAT_SHIFT, 451 },
		{ 421, YYAT_SHIFT, 450 },
		{ 420, YYAT_SHIFT, 449 },
		{ 419, YYAT_SHIFT, 448 },
		{ 418, YYAT_SHIFT, 447 },
		{ 401, YYAT_SHIFT, 15 },
		{ 395, YYAT_SHIFT, 429 },
		{ 394, YYAT_SHIFT, 428 },
		{ 393, YYAT_SHIFT, 427 },
		{ 392, YYAT_SHIFT, 426 },
		{ 391, YYAT_SHIFT, 425 },
		{ 390, YYAT_SHIFT, 424 },
		{ 389, YYAT_SHIFT, 423 },
		{ 388, YYAT_SHIFT, 422 },
		{ 387, YYAT_SHIFT, 421 },
		{ 386, YYAT_SHIFT, 420 },
		{ 385, YYAT_SHIFT, 419 },
		{ 384, YYAT_SHIFT, 418 },
		{ 383, YYAT_SHIFT, 417 },
		{ 378, YYAT_SHIFT, 416 },
		{ 377, YYAT_SHIFT, 415 },
		{ 376, YYAT_SHIFT, 414 },
		{ 375, YYAT_SHIFT, 413 },
		{ 374, YYAT_SHIFT, 412 },
		{ 373, YYAT_SHIFT, 411 },
		{ 372, YYAT_SHIFT, 410 },
		{ 371, YYAT_SHIFT, 409 },
		{ 370, YYAT_SHIFT, 408 },
		{ 369, YYAT_SHIFT, 407 },
		{ 368, YYAT_SHIFT, 406 },
		{ 353, YYAT_SHIFT, 401 },
		{ 345, YYAT_SHIFT, 396 },
		{ 330, YYAT_REDUCE, 21 },
		{ 327, YYAT_SHIFT, 394 },
		{ 326, YYAT_SHIFT, 393 },
		{ 325, YYAT_SHIFT, 392 },
		{ 324, YYAT_SHIFT, 391 },
		{ 323, YYAT_SHIFT, 390 },
		{ 322, YYAT_SHIFT, 389 },
		{ 321, YYAT_SHIFT, 388 },
		{ 320, YYAT_SHIFT, 387 },
		{ 319, YYAT_SHIFT, 386 },
		{ 318, YYAT_SHIFT, 385 },
		{ 317, YYAT_SHIFT, 384 },
		{ 311, YYAT_REDUCE, 12 },
		{ 304, YYAT_REDUCE, 49 },
		{ 303, YYAT_SHIFT, 380 },
		{ 290, YYAT_SHIFT, 379 },
		{ 289, YYAT_SHIFT, 378 },
		{ 288, YYAT_SHIFT, 377 },
		{ 287, YYAT_SHIFT, 376 },
		{ 286, YYAT_SHIFT, 375 },
		{ 285, YYAT_SHIFT, 374 },
		{ 284, YYAT_SHIFT, 373 },
		{ 283, YYAT_SHIFT, 372 },
		{ 282, YYAT_SHIFT, 371 },
		{ 281, YYAT_SHIFT, 370 },
		{ 280, YYAT_SHIFT, 369 },
		{ 279, YYAT_SHIFT, 368 },
		{ 278, YYAT_SHIFT, 367 },
		{ 270, YYAT_SHIFT, 349 },
		{ 265, YYAT_SHIFT, 344 },
		{ 264, YYAT_SHIFT, 343 },
		{ 263, YYAT_SHIFT, 342 },
		{ 262, YYAT_SHIFT, 341 },
		{ 261, YYAT_SHIFT, 340 },
		{ 260, YYAT_SHIFT, 339 },
		{ 259, YYAT_SHIFT, 338 },
		{ 258, YYAT_SHIFT, 337 },
		{ 257, YYAT_SHIFT, 336 },
		{ 256, YYAT_SHIFT, 335 },
		{ 255, YYAT_SHIFT, 334 },
		{ 236, YYAT_SHIFT, 308 },
		{ 231, YYAT_REDUCE, 38 },
		{ 230, YYAT_SHIFT, 151 },
		{ 227, YYAT_SHIFT, 302 },
		{ 226, YYAT_SHIFT, 301 },
		{ 474, YYAT_SHIFT, 52 },
		{ 474, YYAT_SHIFT, 53 },
		{ 474, YYAT_SHIFT, 54 },
		{ 474, YYAT_SHIFT, 55 },
		{ 474, YYAT_SHIFT, 56 },
		{ 474, YYAT_SHIFT, 57 },
		{ 474, YYAT_SHIFT, 58 },
		{ 474, YYAT_SHIFT, 59 },
		{ 474, YYAT_SHIFT, 60 },
		{ 474, YYAT_SHIFT, 61 },
		{ 474, YYAT_SHIFT, 62 },
		{ 474, YYAT_SHIFT, 63 },
		{ 245, YYAT_SHIFT, 52 },
		{ 122, YYAT_SHIFT, 3 },
		{ 225, YYAT_SHIFT, 300 },
		{ 224, YYAT_SHIFT, 299 },
		{ 223, YYAT_SHIFT, 298 },
		{ 222, YYAT_SHIFT, 297 },
		{ 474, YYAT_SHIFT, 64 },
		{ 434, YYAT_SHIFT, 353 },
		{ 434, YYAT_SHIFT, 91 },
		{ 434, YYAT_SHIFT, 92 },
		{ 434, YYAT_SHIFT, 93 },
		{ 434, YYAT_SHIFT, 94 },
		{ 434, YYAT_SHIFT, 95 },
		{ 434, YYAT_SHIFT, 96 },
		{ 434, YYAT_SHIFT, 97 },
		{ 434, YYAT_SHIFT, 98 },
		{ 434, YYAT_SHIFT, 99 },
		{ 434, YYAT_SHIFT, 100 },
		{ 434, YYAT_SHIFT, 101 },
		{ 181, YYAT_REDUCE, 20 },
		{ 488, YYAT_SHIFT, 150 },
		{ 221, YYAT_SHIFT, 296 },
		{ 180, YYAT_REDUCE, 11 },
		{ 488, YYAT_SHIFT, 152 },
		{ 220, YYAT_SHIFT, 295 },
		{ 434, YYAT_SHIFT, 102 },
		{ 219, YYAT_SHIFT, 294 },
		{ 273, YYAT_ERROR, 0 },
		{ 218, YYAT_SHIFT, 293 },
		{ 405, YYAT_SHIFT, 353 },
		{ 217, YYAT_SHIFT, 292 },
		{ 181, YYAT_REDUCE, 20 },
		{ 181, YYAT_REDUCE, 22 },
		{ 181, YYAT_REDUCE, 22 },
		{ 180, YYAT_REDUCE, 9 },
		{ 180, YYAT_REDUCE, 13 },
		{ 180, YYAT_REDUCE, 13 },
		{ 181, YYAT_REDUCE, 20 },
		{ 404, YYAT_SHIFT, 353 },
		{ 273, YYAT_ERROR, 0 },
		{ 180, YYAT_REDUCE, 11 },
		{ 405, YYAT_SHIFT, 15 },
		{ 405, YYAT_SHIFT, 441 },
		{ 405, YYAT_SHIFT, 442 },
		{ 153, YYAT_SHIFT, 52 },
		{ 273, YYAT_ERROR, 0 },
		{ 212, YYAT_SHIFT, 291 },
		{ 50, YYAT_SHIFT, 3 },
		{ 208, YYAT_REDUCE, 21 },
		{ 205, YYAT_SHIFT, 289 },
		{ 404, YYAT_SHIFT, 15 },
		{ 404, YYAT_REDUCE, 35 },
		{ 404, YYAT_REDUCE, 35 },
		{ 244, YYAT_ERROR, 0 },
		{ 121, YYAT_ERROR, 0 },
		{ 151, YYAT_SHIFT, 52 },
		{ 153, YYAT_SHIFT, 213 },
		{ 153, YYAT_SHIFT, 248 },
		{ 153, YYAT_SHIFT, 249 },
		{ 50, YYAT_SHIFT, 75 },
		{ 50, YYAT_SHIFT, 125 },
		{ 50, YYAT_SHIFT, 126 },
		{ 48, YYAT_SHIFT, 3 },
		{ 204, YYAT_SHIFT, 288 },
		{ 203, YYAT_SHIFT, 287 },
		{ 244, YYAT_ERROR, 0 },
		{ 121, YYAT_ERROR, 0 },
		{ 151, YYAT_SHIFT, 213 },
		{ 202, YYAT_SHIFT, 286 },
		{ 201, YYAT_SHIFT, 285 },
		{ 200, YYAT_SHIFT, 284 },
		{ 244, YYAT_ERROR, 0 },
		{ 121, YYAT_ERROR, 0 },
		{ 199, YYAT_SHIFT, 283 },
		{ 48, YYAT_SHIFT, 75 },
		{ 198, YYAT_SHIFT, 282 },
		{ 197, YYAT_SHIFT, 281 },
		{ 196, YYAT_SHIFT, 280 },
		{ 195, YYAT_SHIFT, 279 },
		{ 189, YYAT_REDUCE, 12 },
		{ 182, YYAT_REDUCE, 49 },
		{ 179, YYAT_SHIFT, 268 },
		{ 178, YYAT_SHIFT, 267 },
		{ 177, YYAT_SHIFT, 266 },
		{ 176, YYAT_SHIFT, 265 },
		{ 175, YYAT_SHIFT, 264 },
		{ 174, YYAT_SHIFT, 263 },
		{ 173, YYAT_SHIFT, 262 },
		{ 172, YYAT_SHIFT, 261 },
		{ 171, YYAT_SHIFT, 260 },
		{ 170, YYAT_SHIFT, 259 },
		{ 169, YYAT_SHIFT, 258 },
		{ 168, YYAT_SHIFT, 257 },
		{ 167, YYAT_SHIFT, 256 },
		{ 166, YYAT_SHIFT, 255 },
		{ 165, YYAT_SHIFT, 254 },
		{ 148, YYAT_SHIFT, 234 },
		{ 147, YYAT_SHIFT, 233 },
		{ 144, YYAT_SHIFT, 228 },
		{ 143, YYAT_SHIFT, 227 },
		{ 142, YYAT_SHIFT, 226 },
		{ 141, YYAT_SHIFT, 225 },
		{ 140, YYAT_SHIFT, 224 },
		{ 139, YYAT_SHIFT, 223 },
		{ 138, YYAT_SHIFT, 222 },
		{ 137, YYAT_SHIFT, 221 },
		{ 136, YYAT_SHIFT, 220 },
		{ 135, YYAT_SHIFT, 219 },
		{ 134, YYAT_SHIFT, 218 },
		{ 133, YYAT_SHIFT, 217 },
		{ 132, YYAT_SHIFT, 213 },
		{ 113, YYAT_SHIFT, 186 },
		{ 106, YYAT_REDUCE, 38 },
		{ 104, YYAT_SHIFT, 48 },
		{ 101, YYAT_SHIFT, 176 },
		{ 100, YYAT_SHIFT, 175 },
		{ 99, YYAT_SHIFT, 174 },
		{ 98, YYAT_SHIFT, 173 },
		{ 97, YYAT_SHIFT, 172 },
		{ 96, YYAT_SHIFT, 171 },
		{ 95, YYAT_SHIFT, 170 },
		{ 94, YYAT_SHIFT, 169 },
		{ 93, YYAT_SHIFT, 168 },
		{ 92, YYAT_SHIFT, 167 },
		{ 91, YYAT_SHIFT, 166 },
		{ 89, YYAT_SHIFT, 164 },
		{ 88, YYAT_SHIFT, 163 },
		{ 87, YYAT_SHIFT, 162 },
		{ 86, YYAT_SHIFT, 161 },
		{ 85, YYAT_SHIFT, 160 },
		{ 84, YYAT_SHIFT, 159 },
		{ 83, YYAT_SHIFT, 158 },
		{ 82, YYAT_SHIFT, 157 },
		{ 81, YYAT_SHIFT, 156 },
		{ 80, YYAT_SHIFT, 155 },
		{ 79, YYAT_SHIFT, 154 },
		{ 68, YYAT_SHIFT, 153 },
		{ 66, YYAT_SHIFT, 149 },
		{ 63, YYAT_SHIFT, 143 },
		{ 62, YYAT_SHIFT, 142 },
		{ 61, YYAT_SHIFT, 141 },
		{ 60, YYAT_SHIFT, 140 },
		{ 59, YYAT_SHIFT, 139 },
		{ 58, YYAT_SHIFT, 138 },
		{ 57, YYAT_SHIFT, 137 },
		{ 56, YYAT_SHIFT, 136 },
		{ 55, YYAT_SHIFT, 135 },
		{ 54, YYAT_SHIFT, 134 },
		{ 53, YYAT_SHIFT, 133 },
		{ 52, YYAT_SHIFT, 132 },
		{ 46, YYAT_SHIFT, 111 },
		{ 45, YYAT_SHIFT, 110 },
		{ 42, YYAT_SHIFT, 90 },
		{ 41, YYAT_SHIFT, 89 },
		{ 40, YYAT_SHIFT, 88 },
		{ 39, YYAT_SHIFT, 87 },
		{ 38, YYAT_SHIFT, 86 },
		{ 37, YYAT_SHIFT, 85 },
		{ 36, YYAT_SHIFT, 84 },
		{ 35, YYAT_SHIFT, 83 },
		{ 34, YYAT_SHIFT, 82 },
		{ 33, YYAT_SHIFT, 81 },
		{ 32, YYAT_SHIFT, 80 },
		{ 31, YYAT_SHIFT, 79 },
		{ 30, YYAT_SHIFT, 75 },
		{ 22, YYAT_SHIFT, 50 },
		{ 19, YYAT_ACCEPT, 0 },
		{ 14, YYAT_SHIFT, 41 },
		{ 13, YYAT_SHIFT, 40 },
		{ 12, YYAT_SHIFT, 39 },
		{ 11, YYAT_SHIFT, 38 },
		{ 10, YYAT_SHIFT, 37 },
		{ 9, YYAT_SHIFT, 36 },
		{ 8, YYAT_SHIFT, 35 },
		{ 7, YYAT_SHIFT, 34 },
		{ 6, YYAT_SHIFT, 33 },
		{ 5, YYAT_SHIFT, 32 },
		{ 4, YYAT_SHIFT, 31 },
		{ 3, YYAT_SHIFT, 30 },
		{ 0, YYAT_SHIFT, 2 }
	};
	yytokenaction = tokenaction;
	yytokenaction_size = 409;

	static const yystateaction_t YYNEARFAR YYBASED_CODE stateaction[] = {
		{ 152, 1, YYAT_DEFAULT, 184 },
		{ 0, 0, YYAT_REDUCE, 32 },
		{ 0, 0, YYAT_REDUCE, 2 },
		{ 133, 1, YYAT_DEFAULT, 353 },
		{ 366, 1, YYAT_DEFAULT, 472 },
		{ 365, 1, YYAT_DEFAULT, 472 },
		{ 364, 1, YYAT_DEFAULT, 472 },
		{ 363, 1, YYAT_DEFAULT, 472 },
		{ 362, 1, YYAT_DEFAULT, 472 },
		{ 361, 1, YYAT_DEFAULT, 472 },
		{ 360, 1, YYAT_DEFAULT, 472 },
		{ 359, 1, YYAT_DEFAULT, 472 },
		{ 358, 1, YYAT_DEFAULT, 472 },
		{ 357, 1, YYAT_DEFAULT, 472 },
		{ 356, 1, YYAT_DEFAULT, 472 },
		{ 0, 0, YYAT_REDUCE, 69 },
		{ 0, 0, YYAT_REDUCE, 27 },
		{ 0, 0, YYAT_REDUCE, 68 },
		{ 0, 0, YYAT_DEFAULT, 103 },
		{ 395, 1, YYAT_ERROR, 0 },
		{ -215, 1, YYAT_REDUCE, 1 },
		{ 0, 0, YYAT_REDUCE, 3 },
		{ 118, 1, YYAT_DEFAULT, 459 },
		{ 0, 0, YYAT_REDUCE, 5 },
		{ 0, 0, YYAT_REDUCE, 6 },
		{ 0, 0, YYAT_REDUCE, 29 },
		{ 0, 0, YYAT_REDUCE, 30 },
		{ 0, 0, YYAT_REDUCE, 31 },
		{ 0, 0, YYAT_REDUCE, 63 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 124, 1, YYAT_DEFAULT, 401 },
		{ 135, 1, YYAT_DEFAULT, 487 },
		{ 134, 1, YYAT_DEFAULT, 487 },
		{ 133, 1, YYAT_DEFAULT, 487 },
		{ 132, 1, YYAT_DEFAULT, 487 },
		{ 131, 1, YYAT_DEFAULT, 487 },
		{ 130, 1, YYAT_DEFAULT, 487 },
		{ 129, 1, YYAT_DEFAULT, 487 },
		{ 128, 1, YYAT_DEFAULT, 487 },
		{ 127, 1, YYAT_DEFAULT, 487 },
		{ 126, 1, YYAT_DEFAULT, 487 },
		{ 125, 1, YYAT_DEFAULT, 487 },
		{ 341, 1, YYAT_DEFAULT, 472 },
		{ 0, 0, YYAT_DEFAULT, 122 },
		{ 0, 0, YYAT_REDUCE, 48 },
		{ 108, 1, YYAT_DEFAULT, 178 },
		{ 104, 1, YYAT_DEFAULT, 179 },
		{ 0, 0, YYAT_DEFAULT, 180 },
		{ 34, 1, YYAT_DEFAULT, 404 },
		{ 0, 0, YYAT_DEFAULT, 181 },
		{ 19, 1, YYAT_DEFAULT, 405 },
		{ 0, 0, YYAT_REDUCE, 32 },
		{ 104, 1, YYAT_DEFAULT, 353 },
		{ 337, 1, YYAT_DEFAULT, 472 },
		{ 336, 1, YYAT_DEFAULT, 472 },
		{ 335, 1, YYAT_DEFAULT, 472 },
		{ 334, 1, YYAT_DEFAULT, 472 },
		{ 333, 1, YYAT_DEFAULT, 472 },
		{ 332, 1, YYAT_DEFAULT, 472 },
		{ 331, 1, YYAT_DEFAULT, 472 },
		{ 330, 1, YYAT_DEFAULT, 472 },
		{ 329, 1, YYAT_DEFAULT, 472 },
		{ 328, 1, YYAT_DEFAULT, 472 },
		{ 327, 1, YYAT_DEFAULT, 472 },
		{ 0, 0, YYAT_REDUCE, 27 },
		{ 0, 0, YYAT_DEFAULT, 229 },
		{ 325, 1, YYAT_DEFAULT, 488 },
		{ 0, 0, YYAT_REDUCE, 3 },
		{ 89, 1, YYAT_DEFAULT, 459 },
		{ 0, 0, YYAT_REDUCE, 5 },
		{ 0, 0, YYAT_REDUCE, 6 },
		{ 0, 0, YYAT_REDUCE, 29 },
		{ 0, 0, YYAT_REDUCE, 30 },
		{ 0, 0, YYAT_REDUCE, 31 },
		{ 0, 0, YYAT_REDUCE, 63 },
		{ 0, 0, YYAT_REDUCE, 69 },
		{ 0, 0, YYAT_REDUCE, 68 },
		{ 0, 0, YYAT_REDUCE, 70 },
		{ 0, 0, YYAT_REDUCE, 65 },
		{ 323, 1, YYAT_DEFAULT, 500 },
		{ 322, 1, YYAT_DEFAULT, 500 },
		{ 321, 1, YYAT_DEFAULT, 500 },
		{ 320, 1, YYAT_DEFAULT, 500 },
		{ 319, 1, YYAT_DEFAULT, 500 },
		{ 318, 1, YYAT_DEFAULT, 500 },
		{ 317, 1, YYAT_DEFAULT, 500 },
		{ 316, 1, YYAT_DEFAULT, 500 },
		{ 315, 1, YYAT_DEFAULT, 500 },
		{ 314, 1, YYAT_DEFAULT, 500 },
		{ 313, 1, YYAT_DEFAULT, 500 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 313, 1, YYAT_DEFAULT, 472 },
		{ 312, 1, YYAT_DEFAULT, 472 },
		{ 311, 1, YYAT_DEFAULT, 472 },
		{ 310, 1, YYAT_DEFAULT, 472 },
		{ 309, 1, YYAT_DEFAULT, 472 },
		{ 308, 1, YYAT_DEFAULT, 472 },
		{ 307, 1, YYAT_DEFAULT, 472 },
		{ 306, 1, YYAT_DEFAULT, 472 },
		{ 305, 1, YYAT_DEFAULT, 472 },
		{ 304, 1, YYAT_DEFAULT, 472 },
		{ 303, 1, YYAT_DEFAULT, 472 },
		{ 0, 0, YYAT_REDUCE, 27 },
		{ -205, 1, YYAT_DEFAULT, 354 },
		{ 69, 1, YYAT_DEFAULT, 399 },
		{ 0, 0, YYAT_REDUCE, 3 },
		{ 341, 1, YYAT_DEFAULT, 208 },
		{ 0, 0, YYAT_REDUCE, 5 },
		{ 0, 0, YYAT_REDUCE, 6 },
		{ 0, 0, YYAT_DEFAULT, 122 },
		{ 0, 0, YYAT_REDUCE, 16 },
		{ 0, 0, YYAT_REDUCE, 25 },
		{ 0, 0, YYAT_DEFAULT, 121 },
		{ 71, 1, YYAT_DEFAULT, 401 },
		{ 0, 0, YYAT_DEFAULT, 122 },
		{ 0, 0, YYAT_DEFAULT, 123 },
		{ 0, 0, YYAT_REDUCE, 41 },
		{ 0, 0, YYAT_REDUCE, 37 },
		{ 0, 0, YYAT_REDUCE, 34 },
		{ -169, 1, YYAT_DEFAULT, 438 },
		{ 0, 0, YYAT_DEFAULT, 130 },
		{ 26, 1, YYAT_DEFAULT, 184 },
		{ -27, 1, YYAT_DEFAULT, 434 },
		{ -171, 1, YYAT_DEFAULT, 438 },
		{ 0, 0, YYAT_REDUCE, 50 },
		{ 0, 0, YYAT_REDUCE, 67 },
		{ 0, 0, YYAT_REDUCE, 66 },
		{ 0, 0, YYAT_REDUCE, 45 },
		{ 0, 0, YYAT_REDUCE, 44 },
		{ 0, 0, YYAT_REDUCE, 43 },
		{ -172, 1, YYAT_DEFAULT, 446 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 70, 1, YYAT_DEFAULT, 401 },
		{ 81, 1, YYAT_DEFAULT, 487 },
		{ 80, 1, YYAT_DEFAULT, 487 },
		{ 79, 1, YYAT_DEFAULT, 487 },
		{ 78, 1, YYAT_DEFAULT, 487 },
		{ 77, 1, YYAT_DEFAULT, 487 },
		{ 76, 1, YYAT_DEFAULT, 487 },
		{ 75, 1, YYAT_DEFAULT, 487 },
		{ 74, 1, YYAT_DEFAULT, 487 },
		{ 73, 1, YYAT_DEFAULT, 487 },
		{ 72, 1, YYAT_DEFAULT, 487 },
		{ 71, 1, YYAT_DEFAULT, 487 },
		{ 287, 1, YYAT_DEFAULT, 472 },
		{ 0, 0, YYAT_DEFAULT, 245 },
		{ 0, 0, YYAT_REDUCE, 48 },
		{ 54, 1, YYAT_DEFAULT, 178 },
		{ 50, 1, YYAT_DEFAULT, 179 },
		{ 0, 0, YYAT_REDUCE, 33 },
		{ 0, 0, YYAT_DEFAULT, 180 },
		{ 27, 1, YYAT_DEFAULT, 404 },
		{ 0, 0, YYAT_DEFAULT, 181 },
		{ 16, 1, YYAT_DEFAULT, 405 },
		{ 0, 0, YYAT_REDUCE, 54 },
		{ 0, 0, YYAT_REDUCE, 52 },
		{ 0, 0, YYAT_REDUCE, 53 },
		{ 0, 0, YYAT_REDUCE, 55 },
		{ 0, 0, YYAT_REDUCE, 57 },
		{ 0, 0, YYAT_REDUCE, 56 },
		{ 0, 0, YYAT_REDUCE, 58 },
		{ 0, 0, YYAT_REDUCE, 59 },
		{ 0, 0, YYAT_REDUCE, 60 },
		{ 0, 0, YYAT_REDUCE, 61 },
		{ 0, 0, YYAT_REDUCE, 62 },
		{ 283, 1, YYAT_DEFAULT, 488 },
		{ 66, 1, YYAT_DEFAULT, 487 },
		{ 65, 1, YYAT_DEFAULT, 487 },
		{ 64, 1, YYAT_DEFAULT, 487 },
		{ 63, 1, YYAT_DEFAULT, 487 },
		{ 62, 1, YYAT_DEFAULT, 487 },
		{ 61, 1, YYAT_DEFAULT, 487 },
		{ 60, 1, YYAT_DEFAULT, 487 },
		{ 59, 1, YYAT_DEFAULT, 487 },
		{ 58, 1, YYAT_DEFAULT, 487 },
		{ 57, 1, YYAT_DEFAULT, 487 },
		{ 56, 1, YYAT_DEFAULT, 487 },
		{ 272, 1, YYAT_DEFAULT, 472 },
		{ 39, 1, YYAT_ERROR, 0 },
		{ 35, 1, YYAT_ERROR, 0 },
		{ -6, 1, YYAT_REDUCE, 7 },
		{ -9, 1, YYAT_REDUCE, 18 },
		{ 309, 1, YYAT_DEFAULT, 208 },
		{ 0, 0, YYAT_DEFAULT, 184 },
		{ -238, 1, YYAT_DEFAULT, 122 },
		{ 0, 0, YYAT_REDUCE, 8 },
		{ 0, 0, YYAT_REDUCE, 69 },
		{ 0, 0, YYAT_REDUCE, 68 },
		{ 0, 0, YYAT_REDUCE, 10 },
		{ 308, 1, YYAT_DEFAULT, 208 },
		{ 0, 0, YYAT_REDUCE, 67 },
		{ 0, 0, YYAT_REDUCE, 66 },
		{ 0, 0, YYAT_REDUCE, 14 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 0, 0, YYAT_REDUCE, 36 },
		{ 267, 1, YYAT_DEFAULT, 472 },
		{ 266, 1, YYAT_DEFAULT, 472 },
		{ 265, 1, YYAT_DEFAULT, 472 },
		{ 264, 1, YYAT_DEFAULT, 472 },
		{ 262, 1, YYAT_DEFAULT, 472 },
		{ 259, 1, YYAT_DEFAULT, 472 },
		{ 258, 1, YYAT_DEFAULT, 472 },
		{ 257, 1, YYAT_DEFAULT, 472 },
		{ 253, 1, YYAT_DEFAULT, 472 },
		{ 252, 1, YYAT_DEFAULT, 472 },
		{ 238, 1, YYAT_DEFAULT, 472 },
		{ 0, 0, YYAT_REDUCE, 40 },
		{ 0, 0, YYAT_REDUCE, 19 },
		{ 277, 1, YYAT_DEFAULT, 22 },
		{ 0, 0, YYAT_REDUCE, 23 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 0, 0, YYAT_REDUCE, 47 },
		{ 234, 1, YYAT_DEFAULT, 488 },
		{ 0, 0, YYAT_REDUCE, 69 },
		{ 0, 0, YYAT_REDUCE, 68 },
		{ 0, 0, YYAT_REDUCE, 70 },
		{ 0, 0, YYAT_REDUCE, 65 },
		{ 218, 1, YYAT_DEFAULT, 500 },
		{ 216, 1, YYAT_DEFAULT, 500 },
		{ 214, 1, YYAT_DEFAULT, 500 },
		{ 212, 1, YYAT_DEFAULT, 500 },
		{ 209, 1, YYAT_DEFAULT, 500 },
		{ 193, 1, YYAT_DEFAULT, 500 },
		{ 192, 1, YYAT_DEFAULT, 500 },
		{ 191, 1, YYAT_DEFAULT, 500 },
		{ 190, 1, YYAT_DEFAULT, 500 },
		{ 175, 1, YYAT_DEFAULT, 500 },
		{ 174, 1, YYAT_DEFAULT, 500 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ -212, 1, YYAT_DEFAULT, 354 },
		{ -59, 1, YYAT_DEFAULT, 399 },
		{ 172, 1, YYAT_DEFAULT, 330 },
		{ 0, 0, YYAT_DEFAULT, 245 },
		{ 0, 0, YYAT_REDUCE, 16 },
		{ 0, 0, YYAT_REDUCE, 25 },
		{ 0, 0, YYAT_DEFAULT, 244 },
		{ -57, 1, YYAT_DEFAULT, 401 },
		{ 0, 0, YYAT_DEFAULT, 245 },
		{ 0, 0, YYAT_DEFAULT, 246 },
		{ 0, 0, YYAT_REDUCE, 41 },
		{ 0, 0, YYAT_REDUCE, 37 },
		{ 0, 0, YYAT_REDUCE, 34 },
		{ -173, 1, YYAT_DEFAULT, 438 },
		{ 0, 0, YYAT_DEFAULT, 253 },
		{ 25, 1, YYAT_DEFAULT, 474 },
		{ -28, 1, YYAT_DEFAULT, 434 },
		{ -198, 1, YYAT_DEFAULT, 438 },
		{ 0, 0, YYAT_REDUCE, 50 },
		{ 0, 0, YYAT_REDUCE, 67 },
		{ 0, 0, YYAT_REDUCE, 66 },
		{ 0, 0, YYAT_REDUCE, 45 },
		{ 0, 0, YYAT_REDUCE, 44 },
		{ 0, 0, YYAT_REDUCE, 43 },
		{ -183, 1, YYAT_DEFAULT, 446 },
		{ 0, 0, YYAT_REDUCE, 28 },
		{ 170, 1, YYAT_DEFAULT, 500 },
		{ 169, 1, YYAT_DEFAULT, 500 },
		{ 168, 1, YYAT_DEFAULT, 500 },
		{ 167, 1, YYAT_DEFAULT, 500 },
		{ 166, 1, YYAT_DEFAULT, 500 },
		{ 165, 1, YYAT_DEFAULT, 500 },
		{ 164, 1, YYAT_DEFAULT, 500 },
		{ 163, 1, YYAT_DEFAULT, 500 },
		{ 162, 1, YYAT_DEFAULT, 500 },
		{ 161, 1, YYAT_DEFAULT, 500 },
		{ 160, 1, YYAT_DEFAULT, 500 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 0, 0, YYAT_REDUCE, 16 },
		{ 0, 0, YYAT_REDUCE, 25 },
		{ 0, 0, YYAT_DEFAULT, 273 },
		{ -69, 1, YYAT_DEFAULT, 401 },
		{ 0, 0, YYAT_DEFAULT, 434 },
		{ 0, 0, YYAT_DEFAULT, 275 },
		{ -1, 1, YYAT_DEFAULT, 434 },
		{ 0, 0, YYAT_DEFAULT, 434 },
		{ -201, 1, YYAT_DEFAULT, 438 },
		{ -220, 1, YYAT_DEFAULT, 381 },
		{ -224, 1, YYAT_DEFAULT, 382 },
		{ 158, 1, YYAT_DEFAULT, 488 },
		{ -59, 1, YYAT_DEFAULT, 487 },
		{ -60, 1, YYAT_DEFAULT, 487 },
		{ -61, 1, YYAT_DEFAULT, 487 },
		{ -62, 1, YYAT_DEFAULT, 487 },
		{ -63, 1, YYAT_DEFAULT, 487 },
		{ -64, 1, YYAT_DEFAULT, 487 },
		{ -65, 1, YYAT_DEFAULT, 487 },
		{ -66, 1, YYAT_DEFAULT, 487 },
		{ -67, 1, YYAT_DEFAULT, 487 },
		{ -68, 1, YYAT_DEFAULT, 487 },
		{ -69, 1, YYAT_DEFAULT, 487 },
		{ 146, 1, YYAT_DEFAULT, 488 },
		{ 0, 0, YYAT_REDUCE, 33 },
		{ 0, 0, YYAT_REDUCE, 54 },
		{ 0, 0, YYAT_REDUCE, 52 },
		{ 0, 0, YYAT_REDUCE, 53 },
		{ 0, 0, YYAT_REDUCE, 55 },
		{ 0, 0, YYAT_REDUCE, 57 },
		{ 0, 0, YYAT_REDUCE, 56 },
		{ 0, 0, YYAT_REDUCE, 58 },
		{ 0, 0, YYAT_REDUCE, 59 },
		{ 0, 0, YYAT_REDUCE, 60 },
		{ 0, 0, YYAT_REDUCE, 61 },
		{ 0, 0, YYAT_REDUCE, 62 },
		{ 145, 1, YYAT_DEFAULT, 488 },
		{ 144, 1, YYAT_DEFAULT, 330 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 0, 0, YYAT_REDUCE, 8 },
		{ 0, 0, YYAT_REDUCE, 69 },
		{ 0, 0, YYAT_REDUCE, 68 },
		{ 0, 0, YYAT_REDUCE, 10 },
		{ 143, 1, YYAT_DEFAULT, 330 },
		{ 0, 0, YYAT_REDUCE, 67 },
		{ 0, 0, YYAT_REDUCE, 66 },
		{ 0, 0, YYAT_REDUCE, 14 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 0, 0, YYAT_REDUCE, 36 },
		{ 143, 1, YYAT_DEFAULT, 472 },
		{ 142, 1, YYAT_DEFAULT, 472 },
		{ 141, 1, YYAT_DEFAULT, 472 },
		{ 140, 1, YYAT_DEFAULT, 472 },
		{ 139, 1, YYAT_DEFAULT, 472 },
		{ 138, 1, YYAT_DEFAULT, 472 },
		{ 137, 1, YYAT_DEFAULT, 472 },
		{ 136, 1, YYAT_DEFAULT, 472 },
		{ 135, 1, YYAT_DEFAULT, 472 },
		{ 134, 1, YYAT_DEFAULT, 472 },
		{ 133, 1, YYAT_DEFAULT, 472 },
		{ 0, 0, YYAT_REDUCE, 40 },
		{ 0, 0, YYAT_REDUCE, 19 },
		{ 131, 1, YYAT_DEFAULT, 68 },
		{ 0, 0, YYAT_REDUCE, 23 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 0, 0, YYAT_REDUCE, 47 },
		{ 0, 0, YYAT_REDUCE, 54 },
		{ 0, 0, YYAT_REDUCE, 52 },
		{ 0, 0, YYAT_REDUCE, 53 },
		{ 0, 0, YYAT_REDUCE, 55 },
		{ 0, 0, YYAT_REDUCE, 57 },
		{ 0, 0, YYAT_REDUCE, 56 },
		{ 0, 0, YYAT_REDUCE, 58 },
		{ 0, 0, YYAT_REDUCE, 59 },
		{ 0, 0, YYAT_REDUCE, 60 },
		{ 0, 0, YYAT_REDUCE, 61 },
		{ 0, 0, YYAT_REDUCE, 62 },
		{ 130, 1, YYAT_DEFAULT, 488 },
		{ 0, 0, YYAT_DEFAULT, 434 },
		{ 0, 0, YYAT_DEFAULT, 434 },
		{ 0, 0, YYAT_REDUCE, 8 },
		{ 0, 0, YYAT_REDUCE, 69 },
		{ 0, 0, YYAT_REDUCE, 68 },
		{ 0, 0, YYAT_REDUCE, 10 },
		{ 0, 0, YYAT_REDUCE, 32 },
		{ -104, 1, YYAT_REDUCE, 64 },
		{ -229, 1, YYAT_REDUCE, 15 },
		{ 0, 0, YYAT_DEFAULT, 399 },
		{ 0, 0, YYAT_DEFAULT, 459 },
		{ 0, 0, YYAT_REDUCE, 29 },
		{ 0, 0, YYAT_REDUCE, 30 },
		{ 0, 0, YYAT_REDUCE, 31 },
		{ 0, 0, YYAT_REDUCE, 63 },
		{ 0, 0, YYAT_REDUCE, 67 },
		{ 0, 0, YYAT_REDUCE, 66 },
		{ 0, 0, YYAT_REDUCE, 14 },
		{ 0, 0, YYAT_REDUCE, 19 },
		{ 0, 0, YYAT_DEFAULT, 459 },
		{ 0, 0, YYAT_REDUCE, 23 },
		{ 0, 0, YYAT_REDUCE, 42 },
		{ 128, 1, YYAT_DEFAULT, 500 },
		{ 127, 1, YYAT_DEFAULT, 500 },
		{ 126, 1, YYAT_DEFAULT, 500 },
		{ 125, 1, YYAT_DEFAULT, 500 },
		{ 124, 1, YYAT_DEFAULT, 500 },
		{ 123, 1, YYAT_DEFAULT, 500 },
		{ 122, 1, YYAT_DEFAULT, 500 },
		{ 121, 1, YYAT_DEFAULT, 500 },
		{ 120, 1, YYAT_DEFAULT, 500 },
		{ 119, 1, YYAT_DEFAULT, 500 },
		{ 118, 1, YYAT_DEFAULT, 500 },
		{ 0, 0, YYAT_REDUCE, 51 },
		{ 0, 0, YYAT_REDUCE, 28 },
		{ -230, 1, YYAT_REDUCE, 17 },
		{ -240, 1, YYAT_REDUCE, 26 },
		{ 117, 1, YYAT_DEFAULT, 488 },
		{ -100, 1, YYAT_DEFAULT, 487 },
		{ -101, 1, YYAT_DEFAULT, 487 },
		{ -102, 1, YYAT_DEFAULT, 487 },
		{ -103, 1, YYAT_DEFAULT, 487 },
		{ -104, 1, YYAT_DEFAULT, 487 },
		{ -105, 1, YYAT_DEFAULT, 487 },
		{ -106, 1, YYAT_DEFAULT, 487 },
		{ -107, 1, YYAT_DEFAULT, 487 },
		{ -108, 1, YYAT_DEFAULT, 487 },
		{ -109, 1, YYAT_DEFAULT, 487 },
		{ -110, 1, YYAT_DEFAULT, 487 },
		{ 105, 1, YYAT_DEFAULT, 488 },
		{ 0, 0, YYAT_REDUCE, 28 },
		{ 0, 0, YYAT_DEFAULT, 399 },
		{ 0, 0, YYAT_DEFAULT, 459 },
		{ -258, 1, YYAT_DEFAULT, 179 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ -124, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 434 },
		{ 0, 0, YYAT_REDUCE, 48 },
		{ 10, 1, YYAT_REDUCE, 39 },
		{ 1, 1, YYAT_REDUCE, 46 },
		{ 0, 0, YYAT_REDUCE, 54 },
		{ 0, 0, YYAT_REDUCE, 52 },
		{ 0, 0, YYAT_REDUCE, 53 },
		{ 0, 0, YYAT_REDUCE, 55 },
		{ 0, 0, YYAT_REDUCE, 57 },
		{ 0, 0, YYAT_REDUCE, 56 },
		{ 0, 0, YYAT_REDUCE, 58 },
		{ 0, 0, YYAT_REDUCE, 59 },
		{ 0, 0, YYAT_REDUCE, 60 },
		{ 0, 0, YYAT_REDUCE, 61 },
		{ 0, 0, YYAT_REDUCE, 62 },
		{ 0, 0, YYAT_REDUCE, 42 },
		{ 103, 1, YYAT_DEFAULT, 500 },
		{ 102, 1, YYAT_DEFAULT, 500 },
		{ 101, 1, YYAT_DEFAULT, 500 },
		{ 100, 1, YYAT_DEFAULT, 500 },
		{ 99, 1, YYAT_DEFAULT, 500 },
		{ 98, 1, YYAT_DEFAULT, 500 },
		{ 97, 1, YYAT_DEFAULT, 500 },
		{ 96, 1, YYAT_DEFAULT, 500 },
		{ 95, 1, YYAT_DEFAULT, 500 },
		{ 94, 1, YYAT_DEFAULT, 500 },
		{ 93, 1, YYAT_DEFAULT, 500 },
		{ 0, 0, YYAT_REDUCE, 51 },
		{ 92, 1, YYAT_DEFAULT, 488 },
		{ 0, 0, YYAT_REDUCE, 70 },
		{ 0, 0, YYAT_REDUCE, 65 },
		{ 0, 0, YYAT_DEFAULT, 459 },
		{ -21, 1, YYAT_DEFAULT, 474 },
		{ 0, 0, YYAT_REDUCE, 41 },
		{ 0, 0, YYAT_REDUCE, 37 },
		{ 0, 0, YYAT_REDUCE, 34 },
		{ -208, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 446 },
		{ 0, 0, YYAT_REDUCE, 50 },
		{ 0, 0, YYAT_REDUCE, 67 },
		{ 0, 0, YYAT_REDUCE, 66 },
		{ 0, 0, YYAT_REDUCE, 45 },
		{ 0, 0, YYAT_REDUCE, 44 },
		{ 0, 0, YYAT_REDUCE, 43 },
		{ -257, 1, YYAT_DEFAULT, 273 },
		{ 0, 0, YYAT_REDUCE, 54 },
		{ 0, 0, YYAT_REDUCE, 52 },
		{ 0, 0, YYAT_REDUCE, 53 },
		{ 0, 0, YYAT_REDUCE, 55 },
		{ 0, 0, YYAT_REDUCE, 57 },
		{ 0, 0, YYAT_REDUCE, 56 },
		{ 0, 0, YYAT_REDUCE, 58 },
		{ 0, 0, YYAT_REDUCE, 59 },
		{ 0, 0, YYAT_REDUCE, 60 },
		{ 0, 0, YYAT_REDUCE, 61 },
		{ 0, 0, YYAT_REDUCE, 62 },
		{ 0, 0, YYAT_REDUCE, 33 },
		{ -144, 1, YYAT_REDUCE, 4 },
		{ 0, 0, YYAT_DEFAULT, 474 },
		{ 0, 0, YYAT_REDUCE, 36 },
		{ 91, 1, YYAT_DEFAULT, 472 },
		{ 90, 1, YYAT_DEFAULT, 472 },
		{ 89, 1, YYAT_DEFAULT, 472 },
		{ 88, 1, YYAT_DEFAULT, 472 },
		{ 87, 1, YYAT_DEFAULT, 472 },
		{ 86, 1, YYAT_DEFAULT, 472 },
		{ 85, 1, YYAT_DEFAULT, 472 },
		{ 84, 1, YYAT_DEFAULT, 472 },
		{ 83, 1, YYAT_DEFAULT, 472 },
		{ 82, 1, YYAT_DEFAULT, 472 },
		{ 81, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 40 },
		{ -40, 1, YYAT_DEFAULT, 401 },
		{ 0, 0, YYAT_REDUCE, 47 },
		{ 79, 1, YYAT_DEFAULT, 488 },
		{ -138, 1, YYAT_DEFAULT, 487 },
		{ -139, 1, YYAT_DEFAULT, 487 },
		{ -140, 1, YYAT_DEFAULT, 487 },
		{ -141, 1, YYAT_DEFAULT, 487 },
		{ -142, 1, YYAT_DEFAULT, 487 },
		{ -143, 1, YYAT_DEFAULT, 487 },
		{ -144, 1, YYAT_DEFAULT, 487 },
		{ -145, 1, YYAT_DEFAULT, 487 },
		{ -146, 1, YYAT_DEFAULT, 487 },
		{ -147, 1, YYAT_DEFAULT, 487 },
		{ -148, 1, YYAT_ERROR, 0 },
		{ -23, 1, YYAT_DEFAULT, 230 },
		{ 0, 0, YYAT_REDUCE, 42 },
		{ 67, 1, YYAT_DEFAULT, 500 },
		{ 66, 1, YYAT_DEFAULT, 500 },
		{ 65, 1, YYAT_DEFAULT, 500 },
		{ 64, 1, YYAT_DEFAULT, 500 },
		{ 63, 1, YYAT_DEFAULT, 500 },
		{ 62, 1, YYAT_DEFAULT, 500 },
		{ 13, 1, YYAT_DEFAULT, 500 },
		{ -1, 1, YYAT_DEFAULT, 500 },
		{ -3, 1, YYAT_DEFAULT, 500 },
		{ -5, 1, YYAT_DEFAULT, 500 },
		{ -25, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 51 },
		{ 0, 0, YYAT_REDUCE, 54 },
		{ 0, 0, YYAT_REDUCE, 52 },
		{ 0, 0, YYAT_REDUCE, 53 },
		{ 0, 0, YYAT_REDUCE, 55 },
		{ 0, 0, YYAT_REDUCE, 57 },
		{ 0, 0, YYAT_REDUCE, 56 },
		{ 0, 0, YYAT_REDUCE, 58 },
		{ 0, 0, YYAT_REDUCE, 59 },
		{ 0, 0, YYAT_REDUCE, 60 },
		{ 0, 0, YYAT_REDUCE, 61 },
		{ 0, 0, YYAT_REDUCE, 62 }
	};
	yystateaction = stateaction;

	static const yynontermgoto_t YYNEARFAR YYBASED_CODE nontermgoto[] = {
		{ 474, 488 },
		{ 474, 69 },
		{ 460, 476 },
		{ 245, 230 },
		{ 245, 107 },
		{ 347, 399 },
		{ 354, 178 },
		{ 65, 147 },
		{ 474, 70 },
		{ 446, 475 },
		{ 18, 45 },
		{ 245, 108 },
		{ 354, 179 },
		{ 65, 148 },
		{ 440, 474 },
		{ 474, 68 },
		{ 18, 46 },
		{ 474, 72 },
		{ 245, 330 },
		{ 439, 473 },
		{ 347, 398 },
		{ 474, 73 },
		{ 438, 461 },
		{ 184, 277 },
		{ 184, 23 },
		{ 474, 67 },
		{ 474, 71 },
		{ 474, 74 },
		{ 245, 105 },
		{ 474, 65 },
		{ 474, 17 },
		{ 184, 24 },
		{ 245, 229 },
		{ 401, 431 },
		{ 401, 17 },
		{ 401, 432 },
		{ 434, 355 },
		{ 435, 460 },
		{ 184, 22 },
		{ 403, 434 },
		{ 184, 26 },
		{ 181, 273 },
		{ 181, 274 },
		{ 181, 275 },
		{ 184, 27 },
		{ 402, 433 },
		{ 122, 104 },
		{ 122, 107 },
		{ 184, 21 },
		{ 184, 25 },
		{ 184, 28 },
		{ 434, 459 },
		{ 184, 18 },
		{ 434, 358 },
		{ 122, 108 },
		{ 270, 351 },
		{ 270, 350 },
		{ 434, 359 },
		{ 404, 438 },
		{ 404, 439 },
		{ 400, 430 },
		{ 122, 208 },
		{ 434, 357 },
		{ 434, 360 },
		{ 352, 400 },
		{ 434, 354 },
		{ 404, 437 },
		{ 404, 360 },
		{ 346, 397 },
		{ 404, 436 },
		{ 404, 17 },
		{ 122, 105 },
		{ 151, 242 },
		{ 151, 243 },
		{ 332, 395 },
		{ 122, 103 },
		{ 315, 383 },
		{ 48, 119 },
		{ 48, 120 },
		{ 306, 382 },
		{ 151, 241 },
		{ 151, 74 },
		{ 305, 381 },
		{ 151, 240 },
		{ 151, 214 },
		{ 48, 118 },
		{ 48, 28 },
		{ 405, 446 },
		{ 48, 117 },
		{ 48, 76 },
		{ 275, 366 },
		{ 405, 445 },
		{ 405, 360 },
		{ 405, 444 },
		{ 405, 443 },
		{ 405, 17 },
		{ 153, 253 },
		{ 152, 244 },
		{ 152, 245 },
		{ 152, 246 },
		{ 153, 252 },
		{ 153, 74 },
		{ 153, 251 },
		{ 153, 250 },
		{ 153, 214 },
		{ 50, 130 },
		{ 132, 215 },
		{ 132, 214 },
		{ 132, 216 },
		{ 50, 129 },
		{ 50, 28 },
		{ 50, 128 },
		{ 50, 127 },
		{ 50, 76 },
		{ 180, 269 },
		{ 180, 270 },
		{ 180, 271 },
		{ 180, 272 },
		{ 150, 235 },
		{ 150, 236 },
		{ 150, 237 },
		{ 150, 238 },
		{ 47, 112 },
		{ 47, 113 },
		{ 47, 114 },
		{ 47, 115 },
		{ 49, 121 },
		{ 49, 122 },
		{ 49, 123 },
		{ 30, 77 },
		{ 30, 76 },
		{ 30, 78 },
		{ 236, 310 },
		{ 236, 309 },
		{ 113, 188 },
		{ 113, 187 },
		{ 0, 19 },
		{ 0, 20 },
		{ 274, 365 },
		{ 273, 364 },
		{ 272, 363 },
		{ 271, 356 },
		{ 269, 348 },
		{ 268, 347 },
		{ 267, 346 },
		{ 266, 345 },
		{ 253, 333 },
		{ 247, 332 },
		{ 246, 331 },
		{ 244, 329 },
		{ 243, 328 },
		{ 242, 316 },
		{ 239, 315 },
		{ 238, 314 },
		{ 237, 311 },
		{ 235, 307 },
		{ 234, 306 },
		{ 233, 305 },
		{ 232, 304 },
		{ 228, 303 },
		{ 210, 290 },
		{ 193, 278 },
		{ 183, 276 },
		{ 146, 232 },
		{ 145, 231 },
		{ 131, 212 },
		{ 130, 211 },
		{ 124, 210 },
		{ 123, 209 },
		{ 121, 207 },
		{ 120, 206 },
		{ 119, 194 },
		{ 116, 193 },
		{ 115, 192 },
		{ 114, 189 },
		{ 112, 185 },
		{ 111, 184 },
		{ 110, 183 },
		{ 109, 182 },
		{ 102, 177 },
		{ 90, 165 },
		{ 64, 144 },
		{ 51, 131 },
		{ 44, 109 },
		{ 43, 106 },
		{ 29, 66 },
		{ 16, 42 },
		{ 1, 29 }
	};
	yynontermgoto = nontermgoto;
	yynontermgoto_size = 188;

	static const yystategoto_t YYNEARFAR YYBASED_CODE stategoto[] = {
		{ 135, 184 },
		{ 169, -1 },
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
		{ 170, -1 },
		{ 0, -1 },
		{ 2, -1 },
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
		{ 183, 474 },
		{ 98, -1 },
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
		{ 167, 122 },
		{ 158, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 118, -1 },
		{ 57, -1 },
		{ 115, -1 },
		{ 81, -1 },
		{ 164, -1 },
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
		{ 165, -1 },
		{ -1, -1 },
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
		{ 178, 474 },
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
		{ 163, -1 },
		{ 0, 354 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 161, 122 },
		{ 168, -1 },
		{ 161, -1 },
		{ 148, -1 },
		{ 103, -1 },
		{ 157, 122 },
		{ 143, -1 },
		{ 150, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 141, -1 },
		{ 143, -1 },
		{ 142, -1 },
		{ 44, 184 },
		{ 138, -1 },
		{ 141, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 139, -1 },
		{ 163, 474 },
		{ 75, -1 },
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
		{ 147, 245 },
		{ 138, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 114, -1 },
		{ 52, -1 },
		{ 86, -1 },
		{ 72, -1 },
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
		{ 110, -1 },
		{ 30, -1 },
		{ 0, -1 },
		{ 160, 184 },
		{ 21, 474 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 159, 474 },
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
		{ 158, 474 },
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
		{ 157, 474 },
		{ 0, 354 },
		{ 0, -1 },
		{ 0, -1 },
		{ 141, 245 },
		{ 148, -1 },
		{ 141, -1 },
		{ 128, -1 },
		{ 101, -1 },
		{ 137, 245 },
		{ 123, -1 },
		{ 130, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 121, -1 },
		{ 123, -1 },
		{ 122, -1 },
		{ 1, 474 },
		{ 118, -1 },
		{ 121, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 119, -1 },
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
		{ 143, 474 },
		{ 135, -1 },
		{ 128, -1 },
		{ 115, -1 },
		{ 24, -1 },
		{ 124, 434 },
		{ 110, -1 },
		{ 112, -1 },
		{ 121, 434 },
		{ 60, -1 },
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
		{ 80, 474 },
		{ 77, 474 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 74, 474 },
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
		{ 72, 474 },
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
		{ 66, 347 },
		{ 3, 434 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 46, -1 },
		{ 0, -1 },
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
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 58, 474 },
		{ 2, -1 },
		{ 28, 434 },
		{ 14, -1 },
		{ 38, -1 },
		{ 63, -1 },
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
		{ 34, 245 },
		{ 15, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ -8, -1 },
		{ -8, -1 },
		{ -12, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ -18, -1 },
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
		{ 0, 474 },
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
