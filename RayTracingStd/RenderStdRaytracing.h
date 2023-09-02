/////Etat classe : VALIDE
#ifndef _RENDERSTDRAYTRACING
#define _RENDERSTDRAYTRACING

#include "BaseRender.h"

typedef CBaseColor<unsigned char> BaseColorChar;

class CRenderStdRaytracing : public CBaseRender
{
// Construction
public:
	CRenderStdRaytracing();
	CRenderStdRaytracing(CBaseCamera*,
						 CBaseImage*,
						 TypeVectorGeometry&,
						 TypeVectorLight&,
						 CPhotonTracer*);


//Attributes
private:
	int		m_NbRecursivity;

//operations
public:
	CRenderStdRaytracing&	operator=(CRenderStdRaytracing&);

	/////////////Moteur de rendu
	virtual void	Render(long,long);

	////////////Lancement d'un rayon
	virtual CColor	RayTrace(CRayEye*,TypeVectorGeometry&,TypeVectorLight&);
	virtual CColor	RayTrace(CRayEye *pRayEye,
									   TypeVectorGeometry &ListGeometry,
									   TypeVectorLight &ListLight,
									   int NbRecursivity);

	///////////////////////////////////////////////
	////Fonctions de rendu d'un pixel
	virtual void	RenderPixel(float,float,std::list<BaseColorChar>&);
	void	BeforeRenderPixel(float CurX,float CurY,CCoord&,CVector&); 
	void	RunRenderPixel(CCoord& PtIntersect,
						   CVector& RayVect,
						   CColor& color);
	void	AfterRenderPixel(CColor &ColorRes,
							 std::list<BaseColorChar> &CurLine);
	//////////////////////////////////////////////////

	///////Operations de fin de calcul d'une ligne
	virtual void DoEndLine(long,std::list<BaseColorChar> &);
// Implementation
public:
	virtual ~CRenderStdRaytracing();
};

#endif