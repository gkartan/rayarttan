#include <stdio.h>
#include "PolyNomial.h"
#include "ListSturmSequence.h"
#include <math.h>

/////////////////////////
////A ESSAYER -------> REMPLACER TABLEAU DE COEFF PAR VECTOR
CPolynomial::CPolynomial()
{
	m_Order=0;
}

CPolynomial::CPolynomial(unsigned short Order)
{
	m_Order=Order;
}

CPolynomial::CPolynomial(const CPolynomial &Origin)
{
	m_Order=Origin.m_Order;

	for (int i = 0; i <= m_Order; i++)
	{
		m_Coeff[i]=Origin.m_Coeff[i];
	}
}

CPolynomial::~CPolynomial()
{
}


CPolynomial CPolynomial::operator =(const CPolynomial &Origin)
{
	m_Order=Origin.m_Order;

	for (int i = 0; i <= m_Order; i++)
	{
		m_Coeff[i]=Origin.m_Coeff[i];
	}

	return(*this);
}


CPolynomial CPolynomial::operator - ()
{
	CPolynomial	Res;
	Res.m_Order=m_Order;

	for (int i = 0; i <= m_Order; i++)
	{
		Res.m_Coeff[i]=-m_Coeff[i];
	}

	return Res;
}

/////Calcul la dérivée
CPolynomial	CPolynomial::Derive()
{
	CPolynomial	Res;
	Res.m_Order=m_Order-1;

	for (int i = 1; i <= m_Order; i++)
	{
		Res.m_Coeff[i-1]=m_Coeff[i]*i;
	}

	return Res;
}

/////Normalise le polynome en faisant en sorte que le plus grand coefficient
/////soit égal à 1
void	CPolynomial::Normalize()
{
	double LeadingCoeff=m_Coeff[m_Order];

	for (int i = 0; i <= m_Order; i++)
	{
		m_Coeff[i]/=LeadingCoeff;
	}
}

//Evaluation du polynome pour une valeur
double	CPolynomial::Eval(double Value)
{
	register int i;

	double Res = m_Coeff[m_Order];

	for (i = m_Order-1; i >= 0; i--)
	{
		Res = Res * Value + m_Coeff[i];
	}

	return(Res);
}


////////////A SIMPLIFIER
CPolynomial CPolynomial::operator % (const CPolynomial &Param)
{

 int k, j;

  CPolynomial PolyRes = *this;

  if (Param.m_Coeff[Param.m_Order] < 0.0)
  {
    for (k = m_Order - Param.m_Order - 1; k >= 0; k -= 2)
    {
      PolyRes.m_Coeff[k] = -PolyRes.m_Coeff[k];
    }

    for (k = m_Order - Param.m_Order; k >= 0; k--)
    {
      for (j = Param.m_Order + k - 1; j >= k; j--)
      {
        PolyRes.m_Coeff[j] = -PolyRes.m_Coeff[j] - PolyRes.m_Coeff[Param.m_Order + k] * Param.m_Coeff[j - k];
      }
    }
  }
  else
  {
    for (k = m_Order - Param.m_Order; k >= 0; k--)
    {
      for (j = Param.m_Order + k - 1; j >= k; j--)
      {
        PolyRes.m_Coeff[j] -= PolyRes.m_Coeff[Param.m_Order + k] * Param.m_Coeff[j - k];
      }
    }
  }

  k = Param.m_Order - 1;

  while (k >= 0 && fabs(PolyRes.m_Coeff[k]) < EPSILON)
  {
    PolyRes.m_Coeff[k] = 0.0;

    k--;
  }

  PolyRes.m_Order = (k < 0) ? 0 : k;

  return(PolyRes);
}

///////////////////////////////////////////////////////////////
///Calcul de la suite de Sturm à partir du polynome
void CPolynomial::ComputeSturmSeq(CListSturmSequence *pSturmSeq)
{
	CListSturmSequence &SturmSeq=(*pSturmSeq);

	SturmSeq.Initialize(m_Order);

	//Calcul des premières suites
	*(SturmSeq[0])=*this;
	SturmSeq[0]->Normalize();
	*(SturmSeq[1])=SturmSeq[0]->Derive();
	SturmSeq[1]->Normalize();

	int i=1;

	while(i<m_Order-1)
	{
		*(SturmSeq[i+1]) = *(SturmSeq[i-1]) % *(SturmSeq[i]);
		SturmSeq[i+1]->Normalize();
		*(SturmSeq[i+1])=-*(SturmSeq[i+1]);
		i++;
	}

	*(SturmSeq[m_Order]) = *(SturmSeq[m_Order-2]) % *(SturmSeq[m_Order-1]);
	*(SturmSeq[m_Order]) = -*(SturmSeq[m_Order]);

	for(i=0;i<=m_Order;i++)
	{
		CPolynomial poly=*(SturmSeq[i]);
	}
}

//////////////////////////////////////////////
///Résolution de l'équation par les suites de Sturm
///retourne vrai s'il ya des solutions
bool CPolynomial::Solve(TypeVectorDouble& roots,double RootsTolerance)
{
	  if (RootsTolerance > 0.0)
      {
        if ((m_Coeff[m_Order-1] != 0.0) && (fabs(m_Coeff[m_Order]/m_Coeff[m_Order-1]) < RootsTolerance))
        {
			CPolynomial	poly(m_Order-1);
			for(int i=0;i<m_Order;i++)
			{
				poly.SetCoeff(i,GetCoeff(i));
			}

			return(poly.Solve(roots,RootsTolerance));
        }
      }

	CListSturmSequence	SturmSeq;
	double			NbRoots=0;

	ComputeSturmSeq(&SturmSeq);

	double MinValue=0;
	double MaxValue=MAX_DISTANCE;

	bool Res=SturmSeq.FindRoots(MinValue,MaxValue,roots);

	if(Res)
	{
	}

	return(Res);
}

///////////////////////////////////////////////////
///Résolution de l'équation sur un intervalle
///par la méthode d'interpolation linéaire Regular Falsi
///METHODE A REVOIR ET A SIMPLIFIER
#define MAX_ITERATIONS 50
bool CPolynomial::Solve(double Min,double Max,TypeVectorDouble& roots)
{
  int its;
  double fa, fb, x, fx, lfx;

  fa = Eval(Min);
  fb = Eval(Max);

  if (fa * fb > 0.0)
  {
    return false;
  }

  if (fabs(fa) < EPSILON)
  {
    roots.push_back(Min);

    return true;
  }

  if (fabs(fb) < EPSILON)
  {
    roots.push_back(Max);

    return true;
  }

  lfx = fa;

  for (its = 0; its < MAX_ITERATIONS; its++)
  {
    x = (fb * Min - fa * Max) / (fb - fa);

    fx = Eval(x);

    if (fabs(x) > RELERROR)
    {
      if (fabs(fx / x) < RELERROR)
      {
		roots.push_back(x);

        return true;
      }
    }
    else
    {
      if (fabs(fx) < RELERROR)
      {
		roots.push_back(x);
        return true;
      }
    }

    if (fa < 0)
    {
      if (fx < 0)
      {
        Min = x;

        fa = fx;

        if ((lfx * fx) > 0)
        {
          fb /= 2;
        }
      }
      else
      {
        Max = x;

        fb = fx;

        if ((lfx * fx) > 0)
        {
          fa /= 2;
        }
      }
    }
    else
    {
      if (fx < 0)
      {
        Max = x;

        fb = fx;

        if ((lfx * fx) > 0)
        {
          fa /= 2;
        }
      }
      else
      {
        Min = x;

        fa = fx;

        if ((lfx * fx) > 0)
        {
          fb /= 2;
        }
      }
    }

    if (fabs(Max-Min) < RELERROR)
    {
	  roots.push_back(x);
      return true;
    }

    lfx = fx;
  }

  return false;
}
