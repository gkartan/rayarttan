/////Etat classe : VALIDE

#include "RenderStdRaytracing.h"

class CRenderParallel : public CRenderStdRaytracing
{
// Construction
public:
	CRenderParallel();
	CRenderParallel(CBaseCamera*,
						 CBaseImage*,
						 TypeVectorGeometry&,
						 TypeVectorLight&);


//operations
public:
	virtual void	Render();

// Implementation
public:
	virtual ~CRenderParallel();
};
 