#ifndef _LISTEXPR
#define _LISTEXPR


/////////////////////////////////////////////////
///classe permettant le calcul d'une expression
///d'un type donnée en faisant appel à ses opérateurs
#include <list>

///Liste des types d'opérateurs qui doivent être définies
typedef enum 
{
	TYPE_OP_ADD=0,
	TYPE_OP_MINUS,
	TYPE_OP_MINUS_ALONE,
	TYPE_OP_MULT,
	TYPE_OP_DIV,
	TYPE_OP_ADD_CST,
	TYPE_OP_MINUS_CST,
	TYPE_OP_MINUS_CST_INV,
	TYPE_OP_MULT_CST,
	TYPE_OP_DIV_CST,
	TYPE_OP_EXP,
	TYPE_OP_SIN,
	TYPE_OP_COS,
	TYPE_OP_TAN,
	TYPE_OP_COTAN,
	TYPE_OP_LOG,
	TYPE_OP_ASIN,
	TYPE_OP_ACOS,
	TYPE_OP_ATAN,
	TYPE_OP_ACOTAN,
	TYPE_OP_STOCK,
	TYPE_OP_STOCK_CST,
	TYPE_OP_STOCK_INIT,
	TYPE_OP_STOCK_PIXEL,
	TYPE_OP_LOAD,
	TYPE_OP_POWER,
	TYPE_OP_INIT,
	TYPE_OP_PIXEL,
	TYPE_OP_DIV_CST_INV,
	TYPE_OP_SQRT,
} Type_Op;

template <class Type_Elem>
class CListExpr
{

	///construction
public:
	CListExpr() {}
	~CListExpr() {m_listop.clear();m_listdouble.clear();};


public:
	///operator
	CListExpr &operator=(const CListExpr &Param)
	{
		m_listop=Param.m_listop;
		m_listdouble=Param.m_listdouble;

		return(*this);
	}
	///operations
public:
	inline void	AddOp(Type_Op Op) {m_listop.push_back(Op); m_listdouble.push_back(0);};
	inline void	AddOp(Type_Op Op,Type_Elem Val) {m_listop.push_back(Op); m_listdouble.push_back(Val);};

public:
	std::list<Type_Op>		m_listop;
	std::list<Type_Elem>	m_listdouble;
};

#endif
