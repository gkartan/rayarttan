#ifndef _FORMULADERIVATE_H
#define _FORMULADERIVATE_H

#include <cyacc.h>

/////////////////////////////////////////////////////////////////////////////
// CDataDerivateParser

#ifndef YYDECLSPEC
#define YYDECLSPEC
#endif

class YYFAR YYDECLSPEC CDataDerivateParser : public yyfparser {
public:
	CDataDerivateParser();

protected:
	void yytables();
	virtual void yyaction(int action);
#ifdef YYDEBUG
	void YYFAR* yyattribute1(int index) const;
	void yyinitdebug(void YYFAR** p, int count) const;
#endif

public:
#line 17 "FormulaDerivate.y"

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

#line 54 "FormulaDerivate.h"
};

#ifndef YYPARSENAME
#define YYPARSENAME CDataDerivateParser
#endif

#ifndef YYSTYPE
union tagYYSTYPE {
#line 44 "FormulaDerivate.y"

   char *       tval;
   int          ival;
   double        fval;
   double        vval[3];
   double		 qval[4];

#line 71 "FormulaDerivate.h"
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
