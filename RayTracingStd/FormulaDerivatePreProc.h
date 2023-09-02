#ifndef _FORMULADERIVATEPREPROC_H
#define _FORMULADERIVATEPREPROC_H

#include <cyacc.h>

/////////////////////////////////////////////////////////////////////////////
// CDataDerivatePreProcParser

#ifndef YYDECLSPEC
#define YYDECLSPEC
#endif

class YYFAR YYDECLSPEC CDataDerivatePreProcParser : public yyfparser {
public:
	CDataDerivatePreProcParser();

protected:
	void yytables();
	virtual void yyaction(int action);
#ifdef YYDEBUG
	void YYFAR* yyattribute1(int index) const;
	void yyinitdebug(void YYFAR** p, int count) const;
#endif

public:
#line 15 "FormulaDerivatePreProc.y"

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

#line 60 "FormulaDerivatePreProc.h"
};

#ifndef YYPARSENAME
#define YYPARSENAME CDataDerivatePreProcParser
#endif

#ifndef YYSTYPE
union tagYYSTYPE {
#line 48 "FormulaDerivatePreProc.y"

   char *       tval;
   int          ival;
   double        fval;
   double        vval[3];
   double		 qval[4];

#line 77 "FormulaDerivatePreProc.h"
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
#define WHITE_TOKEN 277
#endif
