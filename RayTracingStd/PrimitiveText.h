/////Etat classe : EN COURS
#ifndef _PLANE
#define _PLANE

#include "Vector.h"
#include "BaseGeometry.h"

class CPlane : public CBaseGeometry
{
// Construction
public:
	CPlane();
	CPlane(CVector &Vect,
		  double   Cste);
	CPlane(CVector &Vect,
		  CCoord  &Point);

//Attributes
private:
	CVector	m_Coeff;	//coefficient directeur du plan
	double	m_Cste;		

protected:
	virtual void	ForceEqual(CBaseGeometry&);
public:
	virtual CBaseGeometry*	Instantiate();		//instancie un nouvel objet de ce type
	virtual CBaseGeometry* GetBoundSphere()	{return NULL;};

public:
	CPlane&	operator=(CPlane&);
	void	SetPlane(CVector&,double);	//coeff + distance

//operations
public:
	virtual	bool	Intersection(CRay&);
	virtual bool	AddIntersect(CRay&,double Distance);

protected:
	virtual CVector	Normal(const CCoord &coord);
			CVector	Normal();
			double  Distance(const CCoord &);

// Implementation
public:
	virtual ~CPlane();

//Gestion stream
public:
		virtual	void	GetOutputStream(ostream&);
};


#endif