/////Etat classe : VALIDE - Reste Problème si résolution d'équations par STURM

#include "Coord.h"

class CTorus : public CBaseGeometry
{
// Construction
public:
	CTorus();
	CTorus(const CCoord&,double,double);
	CTorus(double,double);

//Attributes
private:
	CCoord	m_Center;
	double	m_Major;
	double	m_Minor;



protected:
	virtual void	ForceEqual(CBaseGeometry&);
public:
	virtual CBaseGeometry*	Instantiate();		//instancie un nouvel objet de ce type

//operations
protected:
	virtual	bool	Intersection(CRay&);
	virtual bool	AddIntersect(CRay&,double Distance);
	virtual CBaseGeometry* GetBoundSphere()	{return NULL;};


	CVector	Normal(const CCoord&);
	double  Distance(double root,double Length);

public:

public:
	CTorus&	operator=(CTorus&);

// Implementation
public:
	virtual ~CTorus();

//Gestion stream
public:
		virtual	void	GetOutputStream(ostream&);
};
