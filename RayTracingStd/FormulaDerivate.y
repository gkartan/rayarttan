%{
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

%}

%name CDataDerivateParser
// class definition
{
public:
	~CDataDerivateParser();
// Attributes
private:
	std::stack<std::string>	 m_strTempLeft;	
	std::stack<std::string>	 m_DstrTempLeft;
	std::string				 m_strTempRight;
	std::string				 m_DstrTempRight;
	std::string				 m_strTemp;
	std::string				 m_DstrTemp;
	std::string				 m_strValue;
	std::string				 m_DstrValue;
	std::string*			 m_pstr;
	std::string				 m_errorMsg;

	CDataDerivateLexer*  m_plexer;
	long				 m_value;
	int					 m_Result;

public:
	void		SetOutputString(std::string *pstr);
	void		SetValue(long val) {m_value=val;};
	int			GetResult();
	CDataDerivateLexer*	CreateLexer();
}

%union {
   char *       tval;
   int          ival;
   double        fval;
   double        vval[3];
   double		 qval[4];
}

%token QUATER_TOKEN EXP_TOKEN SIN_TOKEN COS_TOKEN TAN_TOKEN LOG_TOKEN COTAN_TOKEN
	   ASIN_TOKEN ACOS_TOKEN ATAN_TOKEN ACOTAN_TOKEN SQRT_TOKEN FLOAT_TOKEN PIXEL_TOKEN
	   INIT_TOKEN PLUS_TOKEN MULT_TOKEN HAT_TOKEN DASH_TOKEN DIV_TOKEN

%left PLUS_TOKEN, DASH_TOKEN 
%left DIV_TOKEN 
%left MULT_TOKEN
%right PSEUDO_MINUS

%type  <fval> fexpr
%type  <fval> double

%type  <ival> integer


%start file

%%

file
	: addsub_expr				{
									(*m_pstr)=m_DstrTemp;
									m_Result=0;
								}
	| error						{
									_TRACE_ERROR("Error Parsing Derivate");
									m_Result=-1;
								}
	;			
	
addsub_expr :
				addsub_expr						{
													m_strTempLeft.push(m_strTemp);
													m_DstrTempLeft.push(m_DstrTemp);
													m_strTemp="";
													m_DstrTemp="";
												}
				MULT_TOKEN
				addsub_expr						{
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
												}
			|	addsub_expr						{
													m_strTempLeft.push(m_strTemp);
													m_DstrTempLeft.push(m_DstrTemp);
													m_strTemp="";
													m_DstrTemp="";
												}
				DIV_TOKEN	
				addsub_expr						{
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
												}

			|			addsub_expr		{
											m_strTempLeft.push(m_strTemp);
											m_DstrTempLeft.push(m_DstrTemp);
											m_strTemp="";
											m_DstrTemp="";
										}
						PLUS_TOKEN
						addsub_expr		{
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
										}
			|  			addsub_expr 	{
											m_strTempLeft.push(m_strTemp);
											m_DstrTempLeft.push(m_DstrTemp);
											m_strTemp="";
											m_DstrTemp="";
										}
						DASH_TOKEN
						addsub_expr		{
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
										}
			|			'('	addsub_expr ')'			
			|	element_expr						
			|	addsub_expr HAT_TOKEN integer	{
													char buffer[255],Dbuffer[255];
													sprintf(buffer,"%d",$3);
													sprintf(Dbuffer,"%d",$3-1);
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
												}
			;

element_expr :
				puiss_expr				
			 |	constant				
			 |	double						{
			 									char buffer[255];
												sprintf(buffer,"%.10f",$1);
												m_strTemp+=std::string(buffer);
												m_DstrTemp+=std::string("0");
											}				
			 ;		


func_expr
	: 
	  SIN_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("cos(z)");					m_strTemp+=std::string("sin(z)");}
	| COS_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("(-sin(z))");					m_strTemp+=std::string("cos(z)");}
	| EXP_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("exp(z)");					m_strTemp+=std::string("exp(z)");}
	| TAN_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("(1+tan(z)*tan(z))");			m_strTemp+=std::string("tan(z)");}
	| COTAN_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("(-(1+cotan(z)*cotan(z)))");	m_strTemp+=std::string("cotan(z)");}
	| LOG_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("(1/z)");						m_strTemp+=std::string("log(z)");}
	| ASIN_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("(1/sqrt(1-z^2))");			m_strTemp+=std::string("asin(z)");}
	| ACOS_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("(-(1/sqrt(1-z^2)))");		m_strTemp+=std::string("acos(z)");}
	| ATAN_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("(1/(1+z^2))");			m_strTemp+=std::string("atan(z)");}
	| ACOTAN_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("(-(1/(1+z^2)))");			m_strTemp+=std::string("acotan(z)");}
	| SQRT_TOKEN '(' QUATER_TOKEN ')'		{m_DstrTemp+=std::string("(1/(2*sqrt(z)))");		m_strTemp+=std::string("sqrt(z)");}

	;


puiss_expr : puiss_quater
		   | func_expr
		   ;

puiss_quater
	: QUATER_TOKEN	{
						m_strTemp+=std::string("Z");
						m_DstrTemp+=std::string("1");
					}
	| QUATER_TOKEN HAT_TOKEN integer	{
											char buffer[255],buffer1[255];
											sprintf(buffer,"%d",$3);
											sprintf(buffer1,"%d",$3-1);
											m_strTemp+=std::string("Z^")+std::string(buffer);
											m_DstrTemp+=std::string(buffer)+std::string("*Z^")+std::string(buffer1);
										}
	;

constant : INIT_TOKEN			{
									m_strTemp+=std::string("@init");
									m_DstrTemp+=std::string("0");
								}			
		 | PIXEL_TOKEN			{
									m_strTemp+=std::string("#pixel");
									m_DstrTemp+=std::string("0");
								}		
		 ;

/****************expression d'un nombre*****************/
double : fexpr;

fexpr : FLOAT_TOKEN
            { char   *string; $$ = (double) strtod(m_plexer->yytext,&string); _TRACE_INFO(_STR("%.10f",$$)); }
	  ;

/*================================*/
/* Integer stuff */

integer : double 
		  { $$ = (int) $1; }
		;

%%

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