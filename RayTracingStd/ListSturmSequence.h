/////Etat classe : Sans doute encore bogues dans r�solution

#include "BaseListPolynomial.h"

class	CListSturmSequence : public CBaseListPolynomial
{
public:
	CListSturmSequence();

public:
	void			Initialize(long);
	unsigned long	NumSignChanges(double Value);
	bool			FindRoots(double Min,double Max,TypeVectorDouble &roots);
	bool			FindRoots(double Min,double Max,TypeVectorDouble &roots,long);
	bool			ExistRoots();

// Implementation
public:
	virtual ~CListSturmSequence();

};