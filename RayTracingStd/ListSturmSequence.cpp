#include <stdio.h>
#include <cmath>
#include "ListSturmSequence.h"

CListSturmSequence::CListSturmSequence()
{
}

CListSturmSequence::~CListSturmSequence()
{
	for(TypeVectorPolynomial::iterator i=m_ListPolynomial.begin();
		i!=m_ListPolynomial.end();i++)
		{
			delete (*i);
		}
}

/////Initialise la liste avec le bon nombre d'éléments
void CListSturmSequence::Initialize(long Order)
{
	for(int i=0;i<=Order;i++)
	{
		CPolynomial *pPoly=new CPolynomial;
		m_ListPolynomial.push_back(pPoly);
	}
}


unsigned long	CListSturmSequence::NumSignChanges(double Value)
{
	unsigned long res=0;

	if(m_ListPolynomial.size()<2) return res;

	TypeVectorPolynomial::iterator theIterator=m_ListPolynomial.begin();

	for(int i=0;i<m_ListPolynomial.size()-1;i++)
		{
			double FirstEval=(*theIterator)->Eval(Value);
			double SecondEval=(*(theIterator+1))->Eval(Value);

			if(FirstEval==0 || FirstEval*SecondEval<0)
			{
				res++;
			}

			theIterator++;
		}

	return res;

}

#define MAX_RECURSIVITY 50
bool CListSturmSequence::FindRoots(double Min,double Max,TypeVectorDouble &roots)
{
	///S'il y a des racines on les cherche par la méthode de STURM
	if(ExistRoots())
	{
		return(FindRoots(Min,Max,roots,MAX_RECURSIVITY));
	} else {
		return false;
	}
}

bool CListSturmSequence::FindRoots(double Min,double Max,TypeVectorDouble &roots,long NbRecur)
{
		
	unsigned long NbChangeMin=NumSignChanges(Min);
	unsigned long NbChangeMax=NumSignChanges(Max);

	unsigned long NbRoots=fabs(NbChangeMin-NbChangeMax);

	if(NbRoots==0) return false;

	double Middle=(Max+Min)/2.;
	unsigned long NbChangeMiddle=NumSignChanges(Middle);

	if(NbRecur<0) 
	{
		//roots.push_back(Middle);
		return roots.size()>0;
	}

	if( NbRoots == 1)
	{
		///Trouve la racine par interpolation linéaire
		if(m_ListPolynomial[0]->Solve(Min,Max,roots))
		{
			return true;
		}

		//On a trouvé la racine
		if(fabs((Max-Min)/Middle)<RELERROR)
		{
			roots.push_back(Middle);
			return true;
		} else

		if (fabs(Max - Min) < RELERROR)
        {
			roots.push_back(Middle);
			return true;
        }

		//On cherche la racine dans l'intervalle
		if((NbChangeMin - NbChangeMiddle )==0)
		{
			FindRoots(Middle,Max,roots,NbRecur-1);
		} else {
			FindRoots(Min,Middle,roots,NbRecur-1);
		}

		return true;
	}

	///Appels récursif pour trouver les racines
	if(NbChangeMin-NbChangeMiddle>0)
	{
		FindRoots(Min,Middle,roots,NbRecur-1);
	}

	if(NbChangeMiddle-NbChangeMax>0)
	{
		FindRoots(Middle,Max,roots,NbRecur-1);
	}

	return true;
}

/////////////A REVOIR - A SIMPLIFIER
bool CListSturmSequence::ExistRoots()
{
	int atposinf, atzero;
	double f, lf;

	atposinf = atzero = 0;

	CPolynomial	poly=*(m_ListPolynomial[0]);
	/* Nombre de changement à l'infini */
	lf =m_ListPolynomial[0]->GetCoeff(m_ListPolynomial[0]->GetOrder());

	TypeVectorPolynomial::iterator theIterator=m_ListPolynomial.begin();
	theIterator++;

	for(int i=0;i<m_ListPolynomial.size()-1;i++)
	{

		f=(*theIterator)->GetCoeff((*theIterator)->GetOrder());

		if(lf==0 || lf*f<0)
		{
			atposinf++;
		}

		theIterator++;

		lf=f;
	}

	/* Nombre de changement à zéro */

	lf =m_ListPolynomial[0]->GetCoeff(0);

	theIterator=m_ListPolynomial.begin();
	theIterator++;

	for(i=0;i<m_ListPolynomial.size()-1;i++)
	{

		f=(*theIterator)->GetCoeff(0);

		if(lf==0 || lf*f<0)
		{
			atzero++;
		}

		theIterator++;

		lf=f;
	}

  return((atzero - atposinf)!=0);
}
