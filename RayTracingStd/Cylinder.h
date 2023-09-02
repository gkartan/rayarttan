/////Etat classe : EN COURS 
#ifndef _CYLINDER
#define _CYLINDER

#include "BaseGeometry.h"

typedef enum INTERSECT_ENUM
{
	NO_INTERSECT=0,
	SIDE_INTERSECT=1,
	BASE_INTERSECT=2,
	CAP_INTERSECT=3,
};

class CCylinder : public CBaseGeometry
{
// Construction
public:
	CCylinder();
	CCylinder(const CCoord&,const CCoord&,double);

//Attributes
protected:
	CCoord	m_Base;
	CCoord	m_Cap;
	double	m_Radius;


protected:
	virtual void	ForceEqual(CBaseGeometry&);
public:
	virtual CBaseGeometry*	Instantiate();		//instancie un nouvel objet de ce type

//operations
protected:
	virtual	bool	Intersection(CRay&);
	virtual bool	AddIntersect(CRay&,double Distance);
	virtual bool	AddIntersect(CRay&,double Distance,INTERSECT_ENUM);
	virtual CBaseGeometry* GetBoundSphere();

public:
	CVector	Normal(const CCoord&);	//non implémenté
	virtual CVector	Normal(const CCoord&,INTERSECT_ENUM);
	bool	Intersection(const CRay&,double *Distance,INTERSECT_ENUM*);

public:
	CCylinder&	operator=(CCylinder&);

// Implementation
public:
	virtual ~CCylinder();

//**********Operations speciales
protected:
	void	InitTrans();

//Gestion stream
public:
		virtual	void	GetOutputStream(ostream&);
};


#endif