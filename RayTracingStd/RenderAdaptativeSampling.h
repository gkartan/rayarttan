/////Etat classe : VALIDE
#ifndef _RENDERADAPTATIVESAMPLING
#define _RENDERADAPTATIVESAMPLING

#include "RenderStdRayTracing.h"
#include "Structures.h"

class wxImage;

class CRenderAdaptativeSampling : public CRenderStdRaytracing
{
// Construction
public:
	CRenderAdaptativeSampling();
	CRenderAdaptativeSampling(CBaseCamera*,
						 CBaseImage*,
						 TypeVectorGeometry&,
						 TypeVectorLight&,
						 CPhotonTracer*);

//attributes
protected:
	std::vector<CColor>	m_TabLine[2];
	double				m_AntialiasThreshold;	//tolérance de couleur
	long				m_AntialiasDepth;		//Nombre de récursivité

//operations
public:
	CRenderAdaptativeSampling&	operator=(CRenderAdaptativeSampling&);

	/////////////Evolution du Moteur de rendu pour prendre 
	//une ligne et une colonne supplémentaire
	virtual void	Render(long,long);

	////////////Evolution calcul de rendu d'un pixel
	virtual void	RenderPixel(float,float,std::list<BaseColorChar>&);
	void	RenderPixel(float,float,float,std::vector<CColor>&);
	void	RenderPixel(float,float,CColor&);
	void	AfterRenderPixelLocal(float CurX,
							 CColor &ColorRes,
							 std::vector<BaseColorChar> &Line);

	////Traitement de fin d'une ligne
	virtual void DoEndLine(long,std::list<BaseColorChar> &);

	////Sur échantillonnage
	void	SuperSample(double,double,double,double,
						CColor&,CColor&,CColor&,CColor&,CColor&,long);

	void	SetAlgo(const CAlgorithmModifier&);

// Implementation
public:
	virtual ~CRenderAdaptativeSampling();
};

#endif