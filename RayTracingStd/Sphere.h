/////Etat classe : EN COURS --> Traitement Ellipsoide
#ifndef _SPHERE
#define _SPHERE

#include "BaseGeometry.h"

class CSphere : public CBaseGeometry
{
// Construction
public:
	CSphere();
	CSphere(const CCoord&,double);

//Attributes
private:
	CCoord	m_Center;
	double	m_Ray;


protected:
	virtual void	ForceEqual(CBaseGeometry&);
public:
	virtual CBaseGeometry*	Instantiate();		//instancie un nouvel objet de ce type

//operations
protected:
	virtual	bool	Intersection(CRay&);
	virtual bool	AddIntersect(CRay&,double Distance);
	virtual CBaseGeometry* GetBoundSphere()	{return (this);};

	double  Distance(double b,double delta,bool IsFirst);

public:
	CVector	Normal(const CCoord&);
	bool	Intersection(CRay&,double &DistMin,double &DistMax,CCoord&);
	inline	const CCoord&	GetCenter() {return m_Center;}

	virtual	void	Scale(const CVector&);
	virtual	void	Translate(const CVector&);

public:
	CSphere&	operator=(CSphere&);

	inline	double	GetRay() const {return m_Ray;}
	inline	void	SetRay(double Param) {m_Ray=Param;}

// Implementation
public:
	virtual ~CSphere();

//Gestion stream
public:
		virtual	void	GetOutputStream(ostream&);
};


#endif