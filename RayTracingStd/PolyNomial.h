/////Etat classe : VALIDE sauf Solve -> reste probl�mes sur algo de sturm

#ifndef	_POLYNOMIAL
#define _POLYNOMIAL
#pragma warning(disable : 4786)
#pragma warning(disable : 4275)
#pragma warning(disable : 4530)

#include "Constants.h"
#include "TypeDefinitions.h"

class CListSturmSequence;

class	CPolynomial
{
public:
	CPolynomial();
	CPolynomial(unsigned short);
	CPolynomial(const CPolynomial&);

protected:
	unsigned short	m_Order;
	double			m_Coeff[MAX_ORDER+1]; //Coeff � l'ordre n

	///Private Operations
protected:
	void ComputeSturmSeq(CListSturmSequence *SturmSeq);

	///Public operations
public:
	CPolynomial operator =(const CPolynomial&);
	CPolynomial operator - ();	
	CPolynomial operator % (const CPolynomial&); 

	inline		unsigned short	GetOrder() const	{return m_Order;}
	inline		void			SetCoeff(unsigned long Order,double Coeff) {m_Coeff[Order]=Coeff;}
	inline		double			GetCoeff(unsigned long Order) const	{return(m_Coeff[Order]);}

protected:
	CPolynomial	Derive();			//Calcul la derivee du polynome
	void		Normalize();
	void		InverseSign();		//Inverse le signe


public:
	double	Eval(double Value);		//Evaluation du polynome pour une valeur

	///R�solution du polynome par les suites de STURM
	virtual bool	Solve(TypeVectorDouble& roots,double RootsTolerance);

	///R�solution de la racine par interpolation lin�aire
	///Methode Regular Falsi
	bool	Solve(double Min,double Max,TypeVectorDouble& roots);

// Implementation
public:
	virtual ~CPolynomial();

};

#endif