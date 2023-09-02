%{
/* Dérivation symbolique à partir d'une chaine
 * G.CADOU mai 2002
 */
#pragma warning(disable : 4530)
#include "TraceService.h"
#include "ListExpr.h"
#include <string>
#include "FormulaDerivatePreProc.l.h"

%}

%name CDataDerivatePreProcParser
// class definition
{
public:
	~CDataDerivatePreProcParser();
// Attributes
private:
	//intern variables
	std::string					m_strTemp;
	std::string					m_strTempFinal;
	long						m_count;
	long						m_counttemp;
	long						m_Coeff;
	long						m_CoeffTemp;

	std::string*				m_pstr;			//Output string

	//attributes from lexer
	CDataDerivatePreProcLexer*  m_plexer;
	long						m_value;

	std::string					m_errorMsg;

	bool						m_bExprFuncOnly;

	int							m_Result;

public:
	void		SetOutputString(std::string *pstr);
	void		SetValue(long val) {m_value=val;};
	CDataDerivatePreProcLexer*	CreateLexer();
	void		Compute(std::string &str);
	int			GetResult();
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
	   INIT_TOKEN PLUS_TOKEN MULT_TOKEN HAT_TOKEN DASH_TOKEN DIV_TOKEN WHITE_TOKEN

%type  <fval> fexpr
%type  <fval> double

%type  <ival> integer


%start file

%%

file
	: addsub_expr				{	
									(*m_pstr)=m_strTempFinal;
									m_Result=0;
								}
	| error						{
									(*m_pstr)=m_strTempFinal;
									m_Result=-1;
								}
	;					

addsub_expr : 
		   func_expr

		 | multdiv_expr			{
								Compute(m_strTemp); 
								m_strTempFinal+=m_strTemp;
								m_strTemp="";
								}

		 | add_expr		
		 | sub_expr
		 ;


add_expr:
		 	addsub_expr 
			PLUS_TOKEN			{m_strTempFinal+=std::string("+");}
		 	func_expr		
		 | addsub_expr 
		   PLUS_TOKEN			{m_strTempFinal+=std::string("+");}
		   double				{
									char buffer[255]; 
									sprintf(buffer,"%.9f",$4);
									m_strTempFinal+=std::string(buffer);
								}
		 |	addsub_expr 
			PLUS_TOKEN			{m_strTempFinal+=std::string("+");}
		 	multdiv_expr		{ 
								  Compute(m_strTemp); 
								  m_strTempFinal+=m_strTemp;
								  m_strTemp="";	
								}

		 | addsub_expr 
		   PLUS_TOKEN			{m_strTempFinal+=std::string("+");}
		   constant	
		 
		 | double				{
									char buffer[255]; 
									sprintf(buffer,"%.9f",$1);
									m_strTempFinal+=std::string(buffer);
								}
		   PLUS_TOKEN			{m_strTempFinal+=std::string("+");}
		   addsub_expr		
		 ;


sub_expr:
		 addsub_expr 
		 DASH_TOKEN			{m_strTempFinal+=std::string("-");}
		 func_expr	
		 	
		 | addsub_expr 
		   DASH_TOKEN			{m_strTempFinal+=std::string("-");}
		   multdiv_expr			{ 
								  Compute(m_strTemp); 
								  m_strTempFinal+=m_strTemp;
								  m_strTemp="";	
								}
		 | addsub_expr 
		   DASH_TOKEN			{m_strTempFinal+=std::string("-");}
		   constant				{m_strTempFinal+=m_strTemp;}

		 /*| addsub_expr 
		   DASH_TOKEN			{m_strTempFinal+=std::string("-");}
		   double				{
									char buffer[255]; 
									sprintf(buffer,"%.9f",$4);
									m_strTempFinal+=std::string(buffer);
								}*/

		 | double				{
									char buffer[255]; 
									sprintf(buffer,"%.9f",$1);
									m_strTempFinal+=std::string(buffer);
								}
		   DASH_TOKEN			{m_strTempFinal+=std::string("-");}
		   addsub_expr	

		 |  DASH_TOKEN			{m_strTempFinal+=std::string("-");}
		    '(' addsub_expr ')'		


	     ;


multdiv_expr
	: 
/*	  func_expr 
	|*/ puiss_expr { m_count=m_counttemp;}
	| mult_expr		
	| div_expr
	| '('		{m_strTempFinal+=std::string("(");}
	  addsub_expr 
	  ')'		{m_strTempFinal+=std::string(")");m_bExprFuncOnly=true;}
	;

/**********************************************/
/*Definitions des multiplications
/**********************************************/
mult_expr :
	  addsub_expr  
	  MULT_TOKEN	puiss_expr				{
												m_strTempFinal+=std::string("*");
												m_count=m_counttemp; 
											}
	| addsub_expr
	  MULT_TOKEN							{m_strTempFinal+=std::string("*");}
	  constant	
	| addsub_expr 
	  MULT_TOKEN
	  double								{
											}
	| double	MULT_TOKEN multdiv_expr		{
											}
	| addsub_expr
	  MULT_TOKEN							{m_strTempFinal+=std::string("*");}
	  func_expr				
	| addsub_expr
	  MULT_TOKEN '('						{m_strTempFinal+=std::string("*(");}
	  addsub_expr 
	  ')'									{m_strTempFinal+=std::string(")");m_strTemp="";m_bExprFuncOnly=true;}

	;

/**********************************************/
/*Definitions des divisions
/**********************************************/
div_expr :
	  multdiv_expr DIV_TOKEN	puiss_expr	{
											}
	| multdiv_expr DIV_TOKEN	constant	{
											}
	| multdiv_expr DIV_TOKEN	double		{
											}
	| multdiv_expr DIV_TOKEN				{								  
												Compute(m_strTemp); 
												m_strTempFinal+=m_strTemp;
												m_strTemp="";	
												m_strTempFinal+=std::string("/");
											}
	  func_expr	

	| double	DIV_TOKEN					{
												char buffer[255]; 
												sprintf(buffer,"%.9f",$1);
												m_strTempFinal+=std::string(buffer)+std::string("/");
											}
	  multdiv_expr

	| multdiv_expr	DIV_TOKEN '('			{m_strTempFinal+=std::string("/(");}
	  addsub_expr ')'						{m_strTempFinal+=std::string(")");m_strTemp="";m_bExprFuncOnly=true;}
	;

func_expr
	: SIN_TOKEN	'(' QUATER_TOKEN ')'		{m_strTempFinal+=std::string("sin(z)");m_bExprFuncOnly=true;}			
	| COS_TOKEN	'(' QUATER_TOKEN ')'		{m_strTempFinal+=std::string("cos(z)");m_bExprFuncOnly=true;}						
	| EXP_TOKEN	'(' QUATER_TOKEN ')'		{m_strTempFinal+=std::string("exp(z)");m_bExprFuncOnly=true;}					
	| TAN_TOKEN	'(' QUATER_TOKEN ')'		{m_strTempFinal+=std::string("tan(z)");m_bExprFuncOnly=true;}						
	| COTAN_TOKEN '(' QUATER_TOKEN ')'		{m_strTempFinal+=std::string("cotan(z)");m_bExprFuncOnly=true;}				
	| LOG_TOKEN	'(' QUATER_TOKEN ')'		{m_strTempFinal+=std::string("log(z)");m_bExprFuncOnly=true;}					
	| ASIN_TOKEN '(' QUATER_TOKEN ')'		{m_strTempFinal+=std::string("asin(z)");m_bExprFuncOnly=true;}				 			
	| ACOS_TOKEN '(' QUATER_TOKEN ')'		{m_strTempFinal+=std::string("acos(z)");m_bExprFuncOnly=true;} 						
	| ATAN_TOKEN '(' QUATER_TOKEN ')'		{m_strTempFinal+=std::string("atan(z)");m_bExprFuncOnly=true;}						
	| ACOTAN_TOKEN	'(' QUATER_TOKEN ')'	{m_strTempFinal+=std::string("acotan(z)");m_bExprFuncOnly=true;}					
	| SQRT_TOKEN '(' QUATER_TOKEN ')'		{m_strTempFinal+=std::string("sqrt(z)");m_bExprFuncOnly=true;}

	;

puiss_expr : 
			puiss_quater
		   ;

puiss_quater : QUATER_TOKEN						{m_counttemp=1;m_bExprFuncOnly=false;}	
			 | QUATER_TOKEN HAT_TOKEN integer	{m_counttemp=$3;m_bExprFuncOnly=false;}
			 ;

constant	: INIT_TOKEN	{m_strTempFinal+=std::string("@init");}
			| PIXEL_TOKEN	{m_strTempFinal+=std::string("#pixel");}
			;

/****************expression d'un nombre*****************/
double : fexpr {_TRACE_INFO(_STR("%.9f",$$));};

fexpr : FLOAT_TOKEN
            { char   *string; $$ = (double) strtod(m_plexer->yytext,&string);}
	  ;

/*================================*/
/* Integer stuff */

integer : double 
		  { $$ = (int) $1; }
		;

%%

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