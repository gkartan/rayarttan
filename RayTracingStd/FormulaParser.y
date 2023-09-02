%{
/* 
 * compilateur d'expression mathematique
 */
#pragma warning(disable : 4530)
#include "TraceService.h"
#include "ListExpr.h"
#include <string>
#include "FormulaParser.l.h"

%}

%name CDataFormulaParser
// class definition
{
public:
	~CDataFormulaParser();
// Attributes
private:
	CListExpr<double>*	m_pExpr;
	CDataFormulaLexer*  m_plexer;
	long				m_value;
	bool				m_bvaluecste;
	bool				m_bvaluecsteLeft;
	double				m_valuetemp;
	double				m_valuetempLeft;
	double				m_valuesauv;

	int					m_Result;

public:
	void		SetExpr(CListExpr<double>*);
	CDataFormulaLexer*	CreateLexer();
	void		SetValue(long val) {m_value=val;};
	int			GetResult()	{return m_Result;}
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
	: addsub_expr					{	
											_TRACE_INFO("End Parsing");
											m_Result=0;
									}
	| error							{ _TRACE_ERROR("Error Parsing Formula");m_Result=-1;}
	;					




addsub_expr :
				addsub_expr	MULT_TOKEN	addsub_expr			{ 
																m_pExpr->AddOp(TYPE_OP_MULT);
																_TRACE_INFO("TYPE_OP_MULT");
																_TRACE_INFO("TYPE_OP_STOCK");
															}
			|	addsub_expr DIV_TOKEN addsub_expr			{ 
																m_pExpr->AddOp(TYPE_OP_DIV);
																_TRACE_INFO("TYPE_OP_DIV");
																_TRACE_INFO("TYPE_OP_STOCK");
															}

			|			addsub_expr PLUS_TOKEN	addsub_expr	{ 
																m_pExpr->AddOp(TYPE_OP_ADD); 
																_TRACE_INFO("TYPE_OP_ADD");
																_TRACE_INFO("TYPE_OP_STOCK");
															}	
			|  			addsub_expr DASH_TOKEN	addsub_expr	{ 
																m_pExpr->AddOp(TYPE_OP_MINUS); 
																_TRACE_INFO("TYPE_OP_MINUS");
																_TRACE_INFO("TYPE_OP_STOCK");
															}
			|			DASH_TOKEN addsub_expr 	%prec PSEUDO_MINUS
															{
																_TRACE_INFO("TYPE_OP_MINUS_ALONE");
																m_pExpr->AddOp(TYPE_OP_MINUS_ALONE);
																_TRACE_INFO("TYPE_OP_STOCK");
															}	

			|			'('	addsub_expr ')'					
			|	element_expr						
			|	addsub_expr HAT_TOKEN integer				{
																m_pExpr->AddOp(TYPE_OP_LOAD); 
																_TRACE_INFO("TYPE_OP_LOAD");
																m_pExpr->AddOp(TYPE_OP_POWER,$3);
																_TRACE_INFO("TYPE_OP_POWER");
																_TRACE_INFO("TYPE_OP_STOCK");
															}
					;

element_expr :
				puiss_expr
			 |	constant					{	
												_TRACE_INFO("TYPE_OP_STOCK");
												m_pExpr->AddOp(TYPE_OP_STOCK);
											}
			 |	double						{
												_TRACE_INFO("TYPE_OP_STOCK_CST");
												m_pExpr->AddOp(TYPE_OP_STOCK_CST,$1);
											}
			 ;





func_expr :
	  EXP_TOKEN '(' QUATER_TOKEN ')'		{
												_TRACE_INFO("TYPE_OP_EXP");
												m_pExpr->AddOp(TYPE_OP_EXP);
												_TRACE_INFO("TYPE_OP_STOCK");
											}
	| SIN_TOKEN '(' QUATER_TOKEN ')'		{
												_TRACE_INFO("TYPE_OP_SIN");
												m_pExpr->AddOp(TYPE_OP_SIN);
												_TRACE_INFO("TYPE_OP_STOCK");
											}
	| COS_TOKEN '(' QUATER_TOKEN ')'		{
												_TRACE_INFO("TYPE_OP_COS");
												m_pExpr->AddOp(TYPE_OP_COS);
												_TRACE_INFO("TYPE_OP_STOCK");
											}
	| TAN_TOKEN '(' QUATER_TOKEN ')'		{
												_TRACE_INFO("TYPE_OP_TAN");
												m_pExpr->AddOp(TYPE_OP_TAN);
												_TRACE_INFO("TYPE_OP_STOCK");
											}
	| COTAN_TOKEN '(' QUATER_TOKEN ')'		{
												_TRACE_INFO("TYPE_OP_COTAN");
												m_pExpr->AddOp(TYPE_OP_COTAN);
												_TRACE_INFO("TYPE_OP_STOCK");
											}
	| LOG_TOKEN '(' QUATER_TOKEN ')'		{
												_TRACE_INFO("TYPE_OP_LOG");
												m_pExpr->AddOp(TYPE_OP_LOG);
												_TRACE_INFO("TYPE_OP_STOCK");
											}
	| ASIN_TOKEN '(' QUATER_TOKEN ')'		{
												_TRACE_INFO("TYPE_OP_ASIN");
												m_pExpr->AddOp(TYPE_OP_ASIN);
												_TRACE_INFO("TYPE_OP_STOCK");
											}
	| ACOS_TOKEN '(' QUATER_TOKEN ')'		{
												_TRACE_INFO("TYPE_OP_ACOS");
												m_pExpr->AddOp(TYPE_OP_ACOS);
												_TRACE_INFO("TYPE_OP_STOCK");
											}
	| ATAN_TOKEN '(' QUATER_TOKEN ')'		{
												_TRACE_INFO("TYPE_OP_ATAN");
												m_pExpr->AddOp(TYPE_OP_ATAN);
												_TRACE_INFO("TYPE_OP_STOCK");
											}
	| ACOTAN_TOKEN '(' QUATER_TOKEN ')'		{
												_TRACE_INFO("TYPE_OP_ACOTAN");
												m_pExpr->AddOp(TYPE_OP_ACOTAN);
												_TRACE_INFO("TYPE_OP_STOCK");
											}

	| SQRT_TOKEN '(' addsub_expr ')'		{
												m_pExpr->AddOp(TYPE_OP_SQRT);
												_TRACE_INFO("TYPE_OP_SQRT");
											}
	;


puiss_expr : puiss_quater
		   | func_expr
		   ;

puiss_quater : QUATER_TOKEN						{
													_TRACE_INFO("TYPE_OP_STOCK");
													m_pExpr->AddOp(TYPE_OP_STOCK);
												}
			 | QUATER_TOKEN HAT_TOKEN integer	{
													m_pExpr->AddOp(TYPE_OP_POWER,$3); 
													_TRACE_INFO("TYPE_OP_POWER");
													_TRACE_INFO("TYPE_OP_STOCK");
												}
			 ;

constant	: INIT_TOKEN	{
								m_pExpr->AddOp(TYPE_OP_INIT); 
								_TRACE_INFO("TYPE_OP_INIT");
							}
			| PIXEL_TOKEN	{
								m_pExpr->AddOp(TYPE_OP_PIXEL); 
								_TRACE_INFO("TYPE_OP_PIXEL");
							}		
			;


/****************expression d'un nombre*****************/
double : fexpr;

fexpr : 
		DASH_TOKEN  fexpr      
            { $$ = - $2; }
	  | FLOAT_TOKEN
            { char   *string; $$ = (double) strtod(m_plexer->yytext,&string);}
	  ;

/*================================*/
/* Integer stuff */

integer : double 
		  { $$ = (int) $1; }
		;

%%

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

