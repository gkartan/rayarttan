#ifndef _BOXGEO
#define _BOXGEO

/////Etat classe : VALIDE

#include "Coord.h"
#include "Sphere.h"

#define MAX(a,b)	(a>b)?a:b


typedef enum SIDE_ENUM
{
	SIDE_INIT=0,
	SIDE_X_0=1,
	SIDE_X_1=2,
	SIDE_Y_0=4,
	SIDE_Y_1=8,
	SIDE_Z_0=16,
	SIDE_Z_1=32,
};

typedef enum SIDE_ENUM_IND
{
	SIDE_IND=0,
	SIDE_0=1,
	SIDE_1=2
};

typedef enum SIDE_TYPE
{
	SIDE_X=1,
	SIDE_Y=4,
	SIDE_Z=16
};

class CBox : public CBaseGeometry
{
// Construction
public:
	CBox();
	CBox(const CCoord&,const CCoord&);

//Attributes
private:
	CCoord	m_BeginCoord;
	CCoord	m_EndCoord;


protected:
	virtual void	ForceEqual(CBaseGeometry&);
public:
	virtual CBaseGeometry*	Instantiate();		//instancie un nouvel objet de ce type
	virtual	bool	Intersection(CRay &ray)			{return Intersection(ray,true);};
			bool	Intersection(CRay&,bool);

	virtual CBaseGeometry* GetBoundSphere();

//operations
protected:
			bool	Intersection(double BeginCoord,
								 double EndCoord,
								 double RayBegin,
								 double RayDirect,
								 double &TNear,
								 double &TFar,
								 SIDE_ENUM_IND &SideNear,
								 SIDE_ENUM_IND &SideFar);

	virtual bool	AddIntersect(CRay&,double Distance);
			bool	AddIntersect(CRay &Ray,double Distance,SIDE_ENUM Side);

	virtual CVector	Normal(const CCoord &coord);
			CVector	Normal(const SIDE_ENUM Side);

			double  Distance(CCoord &);


public:
	CBox&	operator=(CBox&);

	inline  SIDE_ENUM Convert(SIDE_ENUM_IND val,SIDE_TYPE type) {return(SIDE_ENUM(val*type));};

// Implementation
public:
	virtual ~CBox();

//Gestion stream
public:
		virtual	void	GetOutputStream(ostream&);
};

#endif
