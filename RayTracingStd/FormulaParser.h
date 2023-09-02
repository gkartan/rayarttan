#ifndef _FORMULAPARSER_H
#define _FORMULAPARSER_H

#include <cyacc.h>

/////////////////////////////////////////////////////////////////////////////
// CDataFormulaParser

#ifndef YYDECLSPEC
#define YYDECLSPEC
#endif

class YYFAR YYDECLSPEC CDataFormulaParser : public yyfparser {
public:
	CDataFormulaParser();

protected:
	void yytables();
	virtual void yyaction(int action);
#ifdef YYDEBUG
	void YYFAR* yyattribute1(int index) const;
	void yyinitdebug(void YYFAR** p, int count) const;
#endif

public:
#line 15 "FormulaParser.y"

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

#line 50 "FormulaParser.h"
};

#ifndef YYPARSENAME
#define YYPARSENAME CDataFormulaParser
#endif

#ifndef YYSTYPE
union tagYYSTYPE {
#line 39 "FormulaParser.y"

   char *       tval;
   int          ival;
   double        fval;
   double        vval[3];
   double		 qval[4];

#line 67 "FormulaParser.h"
};

#define YYSTYPE union tagYYSTYPE
#endif

#define QUATER_TOKEN 257
#define EXP_TOKEN 258
#define SIN_TOKEN 259
#define COS_TOKEN 260
#define TAN_TOKEN 261
#define LOG_TOKEN 262
#define COTAN_TOKEN 263
#define ASIN_TOKEN 264
#define ACOS_TOKEN 265
#define ATAN_TOKEN 266
#define ACOTAN_TOKEN 267
#define SQRT_TOKEN 268
#define FLOAT_TOKEN 269
#define PIXEL_TOKEN 270
#define INIT_TOKEN 271
#define PLUS_TOKEN 272
#define MULT_TOKEN 273
#define HAT_TOKEN 274
#define DASH_TOKEN 275
#define DIV_TOKEN 276
#define PSEUDO_MINUS 277
#endif
