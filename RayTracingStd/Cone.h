/////Etat classe : EN COURS 
#ifndef _CONE
#define _CONE

#include "Cylinder.h"

class CCone : public CCylinder
{
// Construction
public:
	CCone();
	CCone(const CCoord&,double,const CCoord&,double);

//Attributes
private:
	double	m_CapRadius;
	double	m_Dist;
	bool	m_IsCylinder;//si c'est un cylindre dégénéré


protected:
	virtual void	ForceEqual(CBaseGeometry&);
public:
	virtual CBaseGeometry*	Instantiate();		//instancie un nouvel objet de ce type

//operations
protected:
	virtual	bool	Intersection(CRay&);
	virtual CBaseGeometry* GetBoundSphere();

public:
	virtual CVector	Normal(const CCoord&,INTERSECT_ENUM);
	bool	Intersection(const CRay&,double *Distance,INTERSECT_ENUM*);

public:
	CCone&	operator=(CCone&);

// Implementation
public:
	virtual ~CCone();

//**********Operations speciales
protected:
	void	InitTrans();

//Gestion stream
public:
		virtual	void	GetOutputStream(ostream&);
};


#endif