//****Etat Classe : EN COURS
#ifndef _COMPUTEEXPR
#define _COMPUTEEXPR


/////////////////////////////////////////////////
///classe permettant le calcul d'une expression
///d'un type donnée en faisant appel à ses opérateurs
#include "ListExpr.h"
#include <stack>
#include "TraceService.h"

template <class T,class Type_Elem>
class CComputeExpr
{

	///construction
public:
	CComputeExpr();
	CComputeExpr(CListExpr<Type_Elem> &ListExpr);


public:
	///operator
	CComputeExpr<T,Type_Elem> &operator=(const CComputeExpr<T,Type_Elem> &Param)
	{
		m_ListExpr=Param.m_ListExpr;

		return(*this);
	}
	///operations
public:
	inline void	SetExpr(CListExpr<Type_Elem> &ListExpr) {m_ListExpr=ListExpr;}
	inline T	Compute(const T& Value,const T& Init,const T& Pixel,bool);
	inline void	Compute(T& Value,const T& Init,const T& Pixel);

private:
	CListExpr<Type_Elem>	m_ListExpr;
	std::stack<T>			m_Stockage;	//pile de stockage
};

template <class T,class Type_Elem>
CComputeExpr<T,Type_Elem>::CComputeExpr<T,Type_Elem>()
{
}

template <class T,class Type_Elem>
CComputeExpr<T,Type_Elem>::CComputeExpr<T,Type_Elem>(CListExpr<Type_Elem> &ListExpr)
{
	m_ListExpr=ListExpr;
}

/////////////////////////////////////////
///Calcul de l'expression
//template <class T,class Type_Elem>
//T	CComputeExpr<T,Type_Elem>::Compute(const T& Value,const T& Init,const T&pixel)
template <class T,class Type_Elem>
void	CComputeExpr<T,Type_Elem>::Compute(T& Value,const T& Init,const T&pixel)
{
	T	Res(Value);
	//boucle sur la liste des opérations
	std::list<Type_Op>::iterator	theIterator;
	std::list<Type_Elem>::iterator	theIteratorDouble=m_ListExpr.m_listdouble.begin();

	for(theIterator=m_ListExpr.m_listop.begin();
		theIterator!=m_ListExpr.m_listop.end();theIterator++)
	{
		switch((*theIterator))
		{
			case TYPE_OP_ADD: //fait le stockage aussi
				{
					T	&ValueStack1=m_Stockage.top();
					m_Stockage.pop();
					T	&ValueStack2=m_Stockage.top();
					ValueStack2.Add(ValueStack1);
					m_Stockage.push(ValueStack2);
					m_Stockage.pop();
					Res=Value;
				}
				break;
			case TYPE_OP_MINUS://fait le stockage aussi
				{
					T	&ValueStack1=m_Stockage.top();
					m_Stockage.pop();
					T	&ValueStack2=m_Stockage.top();
					ValueStack2.Sub(ValueStack1);
					m_Stockage.push(ValueStack2);
					m_Stockage.pop();
					Res=Value;
				}
				break;
			case TYPE_OP_MULT://fait le stockage aussi
				{
					T	&ValueStack1=m_Stockage.top();
					m_Stockage.pop();
					T	&ValueStack2=m_Stockage.top();
					ValueStack2.Mult(ValueStack1);
					m_Stockage.push(ValueStack2);
					m_Stockage.pop();
					Res=Value;
				}
				break;
			case TYPE_OP_DIV://fait le stockage aussi
				{
					T	&ValueStack1=m_Stockage.top();
					m_Stockage.pop();
					T	&ValueStack2=m_Stockage.top();
					ValueStack2.Div(ValueStack1);
					m_Stockage.push(ValueStack2);
					m_Stockage.pop();
					Res=Value;
				}
				break;
			case TYPE_OP_EXP:
				m_Stockage.push(Value.exp());
				Res=Value;
				break;
			case TYPE_OP_SIN:
				m_Stockage.push(Value.sin());
				Res=Value;
				break;
			case TYPE_OP_COS:
				m_Stockage.push(Value.cos());
				Res=Value;
				break;
			case TYPE_OP_STOCK:
				{
					m_Stockage.push(Res); //empilement de la variable
					Res=Value;
				}
				break;
			case TYPE_OP_STOCK_CST:
				{
					m_Stockage.push(T(*theIteratorDouble,0,0,0));
					Res=Value;
				}
				break;
			case TYPE_OP_MINUS_ALONE: //fait le stockage aussi
				{
					T	&ValueStack=m_Stockage.top();
					Res=-ValueStack;
					m_Stockage.pop();
					m_Stockage.push(Res);
					Res=Value;
				}
				break;
			case TYPE_OP_TAN:
				m_Stockage.push(Value.tan());
				Res=Value;
				break;
			case TYPE_OP_COTAN:
				m_Stockage.push(Value.cotan());
				Res=Value;
				break;
			case TYPE_OP_LOG:
				m_Stockage.push(Value.log());
				Res=Value;
				break;
			case TYPE_OP_ASIN:
				m_Stockage.push(Value.asin());
				Res=Value;
				break;
			case TYPE_OP_ACOS:
				m_Stockage.push(Value.acos());
				Res=Value;
				break;
			case TYPE_OP_ATAN:
				m_Stockage.push(Value.atan());
				Res=Value;
				break;
			case TYPE_OP_ACOTAN:
				m_Stockage.push(Value.acotan());
				Res=Value;
				break;
			case TYPE_OP_INIT:
				Res=Init;
				break;
			case TYPE_OP_PIXEL:
				Res=pixel;
				break;
			case TYPE_OP_POWER:
				Res.Pow((*theIteratorDouble));
				m_Stockage.push(Res);
				Res=Value;
				break;
			case TYPE_OP_SQRT:
				{
					T	&ValueStack=m_Stockage.top();
					m_Stockage.push(ValueStack.sqrt());
					m_Stockage.pop();
					Res=Value;
				}
				break;
			case TYPE_OP_LOAD:
				{
					Res=m_Stockage.top();
					m_Stockage.pop();
				}
		}

		theIteratorDouble++;
	}

	Value=m_Stockage.top();
	m_Stockage.pop();

	if(!m_Stockage.empty())
		_TRACE_ERROR("Pb Stack-> fuite mémoire");
}


template <class T,class Type_Elem>
T	CComputeExpr<T,Type_Elem>::Compute(const T& Value,const T& Init,const T&pixel,bool)
{
	T	Res(Value);
	//boucle sur la liste des opérations
	Compute(Res,Init,pixel);

	return(Res);
}
#endif