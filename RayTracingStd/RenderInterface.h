#ifndef _RENDERINTERFACE
#define _RENDERINTERFACE

#include "stdio.h"
#include "Quaternion.h"
#include "HyperComplex.h"
#include "FractalZ2.h"
#include "FormulaParserParser.h"
#include "TypeDefinitions.h"
#include "Color.h"
#include "BaseMatiere.h"
#include "Plan.h"  
#include "BaseCamera.h"
#include "RenderStdRayTracing.h"
#include "LightAmbient.h"
#include "LightPoint.h"
#include "Sphere.h"
#include "Torus.h"
#include "Box.h"
#include "ComputeDerivate.h"
#include "CamParalPlane.h"
#include "CamSphere.h"
#include "TraceService.h"
#include "RenderAdaptativeSampling.h"
#include "BaseListGeometry.h"
#include "RenderStructure.h"
#include "PhotonTracer.h"

class CRenderInterface
{
public:
	CRenderInterface();

	static		int		FindLastNumber();
	static		void	AfterRender(bool);
	static		unsigned long __stdcall LancementRayTracing(void* lpParameter);
	static		void	Initialize(int Number);
	static		void	Destroy(int Number);
	static		void	CommonComputation();
	static		void	ComputePhotonMap();
	static		bool	TestContinue();

	virtual ~CRenderInterface();

private:
  static long	Number;

public:
  static CBaseImage				*pImage;
  static CBaseCamera			*pCamera;
  static CBaseListGeometry		*pListGeometry;
  static TypeVectorLight		*pListLight;
  static std::string			m_InitPath;
  static std::string			m_FileName;
  static std::string			m_ScreenSaverLoadPath;
  static bool					m_bContinue;
  static bool					m_FileSave;
  static bool					m_bIhm;
  static long					m_NbLine;
  static CRenderStructure		*pRenderStructure;

  static CBaseListGeometry		**pListOfListGeometry;

  static CPhotonTracer			*pPhotonTracer;		//la photon map
};

#endif