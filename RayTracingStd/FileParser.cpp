#include <cyacc.h>

/* #line 1 "FileParser.y" */

/* 
 * compilateur d'expression mathematique
 */
#pragma warning(disable : 4530)
#pragma warning(disable : 4006)
#pragma warning(disable : 4005)

#define NOMINMAX 
#include "FrontalCamera.h"
#include "FrontalLight.h"
#include "FrontalMaterial.h"
#include "ListExpr.h"
#include "FileParser.l.h"
#include "Quaternion.h"
#include "HyperComplex.h"
#include "HyperComplexExot01.h"
#include "HyperComplexExot02.h"
#include "HyperComplexExot03.h"
#include "HyperComplexExot04.h"
#include "HyperComplexExot05.h"
#include "HyperComplexExot06.h"
#include "HyperComplexExot07.h"
#include "HyperComplexExot08.h"
#include "HyperComplexExot09.h"
#include "HyperComplexExot10.h"
#include "HyperComplexExot11.h"
#include "HyperComplexExot12.h"
#include "HyperComplexExot13.h"
#include "HyperComplexExot14.h"
#include "HyperComplexExot15.h"
#include "HyperComplexExot16.h"
#include "Fractal.h"
#include "BaseGeometry.h"
#include "TraceService.h"
#include "RenderStructure.h"
#include "Color.h"
#include "Sphere.h"
#include "Box.h"
#include "Torus.h"
#include "Cylinder.h"
#include "Cone.h"
#include "ParserUnDef.h"
#include "Text.h"


// repeated because of possible precompiled header
#include <cyacc.h>

#include "FileParser.h"

/////////////////////////////////////////////////////////////////////////////
// constructor

YYPARSENAME::YYPARSENAME()
{
	yytables();
}

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYSTACK_SIZE
#define YYSTACK_SIZE 100
#endif

// yyattribute
#ifdef YYDEBUG
void YYFAR* YYPARSENAME::yyattribute1(int index) const
{
	YYSTYPE YYFAR* p = &((YYSTYPE YYFAR*)yyattributestackptr)[yytop + index];
	return p;
}
#define yyattribute(index) (*(YYSTYPE YYFAR*)yyattribute1(index))
#else
#define yyattribute(index) (((YYSTYPE YYFAR*)yyattributestackptr)[yytop + (index)])
#endif

#ifdef YYDEBUG
void YYPARSENAME::yyinitdebug(void YYFAR** p, int count) const
{
	yyassert(p != NULL);
	yyassert(count >= 1);

	YYSTYPE YYFAR** p1 = (YYSTYPE YYFAR**)p;
	for (int i = 0; i < count; i++) {
		p1[i] = &((YYSTYPE YYFAR*)yyattributestackptr)[yytop + i - (count - 1)];
	}
}
#endif

void YYPARSENAME::yyaction(int action)
{
	switch (action) {
	case 0:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 174 "FileParser.y" */
m_Result=0;
			}
		}
		break;
	case 1:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 175 "FileParser.y" */
m_Result=0;
			}
		}
		break;
	case 2:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 176 "FileParser.y" */
m_Result=m_plexer->yylineno; yyexit(1);
			}
		}
		break;
	case 3:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
/* #line 201 "FileParser.y" */

			m_pRenderStructure->GetImage()->SetSize(yyattribute(4 - 7).ival,yyattribute(6 - 7).ival);
		  
			}
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 213 "FileParser.y" */
m_pRenderStructure->SetTypeAlgo(ALGO_NORMAL);
			}
		}
		break;
	case 5:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 214 "FileParser.y" */
m_pRenderStructure->SetTypeAlgo(ALGO_ANTIALIAS);
			}
		}
		break;
	case 6:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 222 "FileParser.y" */
m_pRenderStructure->GetRefStructAlgo().m_Threshold=yyattribute(2 - 2).fval;
			}
		}
		break;
	case 7:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 223 "FileParser.y" */
m_pRenderStructure->GetRefStructAlgo().m_Depth=yyattribute(2 - 2).ival;
			}
		}
		break;
	case 8:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
/* #line 230 "FileParser.y" */

				m_pRenderStructure->GetFrontalCamera()->SetCamera(m_pTmpCamera);
				m_pTmpCamera=NULL;
			
			}
		}
		break;
	case 9:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 244 "FileParser.y" */
m_pTmpCamera=new CCamParalPlane;
			}
		}
		break;
	case 10:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 245 "FileParser.y" */
m_pTmpCamera=new CCamPersPlane;
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 246 "FileParser.y" */
m_pTmpCamera=new CCamSphere;
			}
		}
		break;
	case 12:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 247 "FileParser.y" */
m_pTmpCamera=new CCamSuperEllipsoid;
			}
		}
		break;
	case 13:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 250 "FileParser.y" */
m_pTmpCamera->SetCenter(CVector(yyattribute(2 - 2).vval)); 
			}
		}
		break;
	case 14:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 252 "FileParser.y" */
m_pTmpCamera->SetTop(CVector(yyattribute(2 - 2).vval)); 
			}
		}
		break;
	case 15:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 253 "FileParser.y" */
m_pTmpCamera->SetDirect(CVector(yyattribute(2 - 2).vval)); 
			}
		}
		break;
	case 16:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 256 "FileParser.y" */
m_pTmpCamera->SetLookAt(CCoord(yyattribute(2 - 2).vval)); 
			}
		}
		break;
	case 17:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 257 "FileParser.y" */
m_pTmpCamera->SetWidth(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 18:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 258 "FileParser.y" */
m_pTmpCamera->SetHeight(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 19:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 259 "FileParser.y" */
m_pTmpCamera->SetFocal(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 20:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 260 "FileParser.y" */
((CCamSuperEllipsoid*) m_pTmpCamera)->SetAngle(yyattribute(2 - 4).fval,yyattribute(4 - 4).fval);
			}
		}
		break;
	case 21:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 261 "FileParser.y" */
((CCamSuperEllipsoid*) m_pTmpCamera)->SetScale(CVector(yyattribute(2 - 2).vval));
			}
		}
		break;
	case 22:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 262 "FileParser.y" */
((CCamSuperEllipsoid*) m_pTmpCamera)->SetEpsilon(yyattribute(2 - 4).fval,yyattribute(4 - 4).fval);
			}
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
/* #line 307 "FileParser.y" */
m_pTmpGeometry=new CSphere(CCoord(yyattribute(3 - 5).vval),yyattribute(5 - 5).fval);
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
/* #line 308 "FileParser.y" */
m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
/* #line 312 "FileParser.y" */
m_pTmpGeometry=new CBox(CCoord(yyattribute(3 - 5).vval),CCoord(yyattribute(5 - 5).vval));
			}
		}
		break;
	case 26:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
/* #line 313 "FileParser.y" */
m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);
			}
		}
		break;
	case 27:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
/* #line 317 "FileParser.y" */
m_pTmpGeometry=new CCylinder(CCoord(yyattribute(3 - 7).vval),CCoord(yyattribute(5 - 7).vval),yyattribute(7 - 7).fval);
			}
		}
		break;
	case 28:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[11];
			yyinitdebug((void YYFAR**)yya, 11);
#endif
			{
/* #line 318 "FileParser.y" */
m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);
			}
		}
		break;
	case 29:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[10];
			yyinitdebug((void YYFAR**)yya, 10);
#endif
			{
/* #line 323 "FileParser.y" */
m_pTmpGeometry=new CCone(CCoord(yyattribute(3 - 9).vval),yyattribute(5 - 9).fval,CCoord(yyattribute(7 - 9).vval),yyattribute(9 - 9).fval);
			}
		}
		break;
	case 30:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[13];
			yyinitdebug((void YYFAR**)yya, 13);
#endif
			{
/* #line 324 "FileParser.y" */
m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);
			}
		}
		break;
	case 31:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 328 "FileParser.y" */
m_pTmpGeometry=new CText;
			}
		}
		break;
	case 32:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
/* #line 329 "FileParser.y" */
((CText*) m_pTmpGeometry)->SetFont(std::string(m_tmpStr));
			}
		}
		break;
	case 33:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
/* #line 330 "FileParser.y" */

																	((CText*) m_pTmpGeometry)->SetStr(std::string(m_tmpStr));
																
			}
		}
		break;
	case 34:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[11];
			yyinitdebug((void YYFAR**)yya, 11);
#endif
			{
/* #line 333 "FileParser.y" */

		 															((CText*) m_pTmpGeometry)->Init();
																	m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);
																
			}
		}
		break;
	case 35:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
/* #line 342 "FileParser.y" */

			  m_pRenderStructure->GetFrontalFractal()->SetFractal((CBaseFractal*) m_pTmpGeometry,false);
			  ///Appel de cette méthode pour initialiser les structures manquantes
			  if(!((CBaseFractal*)m_pTmpGeometry)->GetManualDerivative())
			  {
				m_pRenderStructure->GetFrontalFractal()->ChangeType(((CBaseFractal*) m_pTmpGeometry)->GetAlgebraType(),
																	((CBaseFractal*) m_pTmpGeometry)->GetStrExpr(),
																	((CBaseFractal*) m_pTmpGeometry)->GetOptimisation());
			  } else {
			  	m_pRenderStructure->GetFrontalFractal()->ChangeType(((CBaseFractal*) m_pTmpGeometry)->GetAlgebraType(),
																	((CBaseFractal*) m_pTmpGeometry)->GetStrExpr(),
																	((CBaseFractal*) m_pTmpGeometry)->GetStrExprDerivate(),
																	((CBaseFractal*) m_pTmpGeometry)->GetOptimisation());
			  }

			  m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pRenderStructure->GetFrontalFractal()->GetFractal());
			  m_pTmpGeometry=NULL;
			  _TRACE_INFO("Fractale Ajoutée");
		  
			}
		}
		break;
	case 36:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 368 "FileParser.y" */
_TRACE_INFO("Fractal - init value");((CBaseFractal*)m_pTmpGeometry)->SetInitValue(CBaseVector<4,double>(yyattribute(1 - 1).qval));
			}
		}
		break;
	case 37:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 369 "FileParser.y" */
_TRACE_INFO("Fractal - string"); ((CBaseFractal*)m_pTmpGeometry)->SetStrExpr(std::string(m_tmpStr));
			}
		}
		break;
	case 38:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 370 "FileParser.y" */

											((CBaseFractal*)m_pTmpGeometry)->SetStrExprDerivate(std::string(m_tmpStr));
											((CBaseFractal*)m_pTmpGeometry)->SetManualDerivative(true);
									   
			}
		}
		break;
	case 39:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 377 "FileParser.y" */
 
					typedef CQuaternion<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 40:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 384 "FileParser.y" */

			   		typedef CHyperComplex<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 41:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 390 "FileParser.y" */

			   		typedef CHyperComplexExot01<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 42:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 396 "FileParser.y" */

			   		typedef CHyperComplexExot02<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 43:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 402 "FileParser.y" */

			   		typedef CHyperComplexExot03<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 44:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 408 "FileParser.y" */

			   		typedef CHyperComplexExot04<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 45:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 414 "FileParser.y" */

			   		typedef CHyperComplexExot05<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 46:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 420 "FileParser.y" */

			   		typedef CHyperComplexExot06<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 47:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 426 "FileParser.y" */

			   		typedef CHyperComplexExot07<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 48:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 432 "FileParser.y" */

			   		typedef CHyperComplexExot08<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 49:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 438 "FileParser.y" */

			   		typedef CHyperComplexExot09<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 50:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 444 "FileParser.y" */

			   		typedef CHyperComplexExot10<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 51:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 450 "FileParser.y" */

			   		typedef CHyperComplexExot11<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 52:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 456 "FileParser.y" */

			   		typedef CHyperComplexExot12<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 53:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 462 "FileParser.y" */

			   		typedef CHyperComplexExot13<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 54:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 468 "FileParser.y" */

			   		typedef CHyperComplexExot14<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 55:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 474 "FileParser.y" */

			   		typedef CHyperComplexExot15<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 56:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 480 "FileParser.y" */

			   		typedef CHyperComplexExot16<double,HYPERFONCTION_NORMAL> TypeAlgebra;
					m_pTmpGeometry=new CFractal<TypeAlgebra>;
					_TRACE_INFO("Quaternion");
			   
			}
		}
		break;
	case 57:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 488 "FileParser.y" */
_TRACE_INFO("Max iteration");	((CBaseFractal*)m_pTmpGeometry)->SetMaxIter(yyattribute(2 - 2).ival);
			}
		}
		break;
	case 58:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 489 "FileParser.y" */
_TRACE_INFO("Bailout");		((CBaseFractal*)m_pTmpGeometry)->SetBailout(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 59:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 490 "FileParser.y" */
_TRACE_INFO("Precision");		((CBaseFractal*)m_pTmpGeometry)->SetNbStep(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 60:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 491 "FileParser.y" */
_TRACE_INFO("Angle");			((CBaseFractal*)m_pTmpGeometry)->SetAngleDeg(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 61:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
/* #line 496 "FileParser.y" */
m_pTmpGeometry=new CTorus(CCoord(yyattribute(3 - 7).vval),yyattribute(5 - 7).fval,yyattribute(7 - 7).fval);
			}
		}
		break;
	case 62:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[11];
			yyinitdebug((void YYFAR**)yya, 11);
#endif
			{
/* #line 497 "FileParser.y" */
m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry);
			}
		}
		break;
	case 63:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
/* #line 503 "FileParser.y" */
m_pTmpGeometry=new CPlane(CVector(yyattribute(3 - 5).vval),yyattribute(5 - 5).fval); _TRACE_INFO("Creation Plan");
			}
		}
		break;
	case 64:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
/* #line 504 "FileParser.y" */
m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry); _TRACE_INFO("Ajout Plan OK");
			}
		}
		break;
	case 65:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
/* #line 507 "FileParser.y" */
m_pTmpGeometry=new CPlane(CVector(yyattribute(3 - 5).vval),CCoord(yyattribute(5 - 5).vval)); _TRACE_INFO("Creation Plan");
			}
		}
		break;
	case 66:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
/* #line 508 "FileParser.y" */
m_pRenderStructure->GetFrontalGeometry()->AddGeo(m_pTmpGeometry); _TRACE_INFO("Ajout Plan OK");
			}
		}
		break;
	case 67:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 530 "FileParser.y" */
m_pTmpGeometry->SetMatiere(m_pRenderStructure->GetFrontalMaterial()->GetMaterial(m_tmpStr));
			}
		}
		break;
	case 68:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 541 "FileParser.y" */
 m_pTmpLight->SetName(m_tmpStr);
			}
		}
		break;
	case 69:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[9];
			yyinitdebug((void YYFAR**)yya, 9);
#endif
			{
/* #line 542 "FileParser.y" */
 m_pTmpLight->SetColor(m_tmpColor);
			}
		}
		break;
	case 70:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[12];
			yyinitdebug((void YYFAR**)yya, 12);
#endif
			{
/* #line 544 "FileParser.y" */

					m_pRenderStructure->GetFrontalLight()->AddLight(m_pTmpLight);
					m_pTmpLight=NULL;
					_TRACE_INFO("Light Ok");
				  
			}
		}
		break;
	case 71:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 552 "FileParser.y" */
((CLightPoint*) m_pTmpLight)->SetPosition(CCoord(yyattribute(1 - 1).vval));
			}
		}
		break;
	case 72:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 562 "FileParser.y" */
m_pTmpLight=new CLightAmbient;
			}
		}
		break;
	case 73:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 563 "FileParser.y" */
m_pTmpLight=new CLightPoint;
			}
		}
		break;
	case 74:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 579 "FileParser.y" */
m_pTmpMatiere=new CBaseMatiere;
			}
		}
		break;
	case 75:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
/* #line 580 "FileParser.y" */
m_pRenderStructure->GetFrontalMaterial()->AddMatiere(m_pTmpMatiere); m_pTmpMatiere=NULL;
			}
		}
		break;
	case 76:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 594 "FileParser.y" */
m_pTmpMatiere->SetName(m_tmpStr);
			}
		}
		break;
	case 77:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 622 "FileParser.y" */
m_pTmpTexture->GetProcedural()->Clear();
			}
		}
		break;
	case 78:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 630 "FileParser.y" */
m_pTmpTexture->GetProcedural()->SetColor(yyattribute(2 - 4).fval,m_tmpColor);
			}
		}
		break;
	case 79:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 633 "FileParser.y" */
CNoise3DGranite *pNoise=new CNoise3DGranite; m_pTmpTexture->ChangeFunctionNoise(pNoise);
			}
		}
		break;
	case 80:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 634 "FileParser.y" */
CNoise3D *pNoise=new CNoise3D; m_pTmpTexture->ChangeFunctionNoise(pNoise);
			}
		}
		break;
	case 81:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 635 "FileParser.y" */
			
									CBaseProcedural *pProc=new CProcGradientMatiere;
									m_pTmpTexture->SetProcedural(pProc);
								
			}
		}
		break;
	case 82:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 655 "FileParser.y" */
m_pTmpMatiere->SetColorAmbient(m_tmpColor);
			}
		}
		break;
	case 83:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 656 "FileParser.y" */
m_pTmpMatiere->SetColorDiffuse(m_tmpColor);
			}
		}
		break;
	case 84:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 657 "FileParser.y" */
m_pTmpMatiere->SetColorSpecular(m_tmpColor);
			}
		}
		break;
	case 85:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 658 "FileParser.y" */
m_pTmpMatiere->SetColorTransparent(m_tmpColor);
			}
		}
		break;
	case 86:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 659 "FileParser.y" */
m_pTmpTexture=new CTextureElement(new CProcSimpleNoiseMatiere);
			}
		}
		break;
	case 87:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 660 "FileParser.y" */
m_pTmpMatiere->SetTexture(TYPE_AMBIENT,*m_pTmpTexture); delete m_pTmpTexture; m_pTmpTexture=NULL;
			}
		}
		break;
	case 88:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 661 "FileParser.y" */
m_pTmpTexture=new CTextureElement(new CProcSimpleNoiseMatiere);
			}
		}
		break;
	case 89:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 662 "FileParser.y" */
m_pTmpMatiere->SetTexture(TYPE_DIFFUSE,*m_pTmpTexture); delete m_pTmpTexture; m_pTmpTexture=NULL;
			}
		}
		break;
	case 90:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 663 "FileParser.y" */
m_pTmpTexture=new CTextureElement(new CProcSimpleNoiseMatiere);
			}
		}
		break;
	case 91:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 664 "FileParser.y" */
m_pTmpMatiere->SetTexture(TYPE_SPECULAR,*m_pTmpTexture); delete m_pTmpTexture; m_pTmpTexture=NULL;
			}
		}
		break;
	case 92:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 665 "FileParser.y" */
m_pTmpTexture=new CTextureElement(new CProcSimpleNoiseMatiere);
			}
		}
		break;
	case 93:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 666 "FileParser.y" */
m_pTmpMatiere->SetTexture(TYPE_TRANSPARENT,*m_pTmpTexture); delete m_pTmpTexture; m_pTmpTexture=NULL;
			}
		}
		break;
	case 94:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 667 "FileParser.y" */
m_pTmpMatiere->SetReflexion(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 95:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 668 "FileParser.y" */

											if(m_pTmpMatiere->GetModelLight()==NULL)
												m_pTmpMatiere->SetModelLight(new CBaseModelLight(yyattribute(2 - 2).fval));
											else
												m_pTmpMatiere->GetModelLight()->SetPhongExp(yyattribute(2 - 2).fval);
										
			}
		}
		break;
	case 96:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 674 "FileParser.y" */
m_pTmpMatiere->SetTransparency(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 97:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 685 "FileParser.y" */
 m_pTmpGeometry->Rotate(CVector(yyattribute(2 - 2).vval)); 
			}
		}
		break;
	case 98:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 686 "FileParser.y" */
 m_pTmpGeometry->Scale(CVector(yyattribute(2 - 2).vval)); 
			}
		}
		break;
	case 99:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 687 "FileParser.y" */
 m_pTmpGeometry->Translate(CVector(yyattribute(2 - 2).vval)); 
			}
		}
		break;
	case 100:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 701 "FileParser.y" */

											if(m_pTmpMatiere->GetRefDispersion().IsActif())
											{
												m_pTmpMatiere->GetRefDispersion().SetIor(yyattribute(2 - 2).fval);
											} else
												m_pTmpMatiere->SetMilieu2(yyattribute(2 - 2).fval);
										
			}
		}
		break;
	case 101:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 708 "FileParser.y" */
m_pTmpMatiere->GetRefDispersion().SetDispersionRatio(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 102:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 709 "FileParser.y" */
m_pTmpMatiere->GetRefDispersion().SetDispersionSamples(yyattribute(2 - 2).ival);
			}
		}
		break;
	case 103:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 723 "FileParser.y" */
m_pTmpMatiere->GetRefPhotonsParameters().SetCount(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 104:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 724 "FileParser.y" */
m_pTmpMatiere->GetRefPhotonsParameters().SetIntensity(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 105:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 725 "FileParser.y" */
m_pTmpMatiere->GetRefPhotonsParameters().SetProbReflect(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 106:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 733 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (int) yyattribute(1 - 1).fval; 
			}
		}
		break;
	case 107:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 742 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = yyattribute(2 - 3).fval; 
			}
		}
		break;
	case 108:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 744 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = yyattribute(1 - 3).fval + yyattribute(3 - 3).fval; 
			}
		}
		break;
	case 109:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 746 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = yyattribute(1 - 3).fval - yyattribute(3 - 3).fval; 
			}
		}
		break;
	case 110:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 748 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = yyattribute(1 - 3).fval * yyattribute(3 - 3).fval; 
			}
		}
		break;
	case 111:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 750 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = yyattribute(1 - 3).fval / yyattribute(3 - 3).fval; 
			}
		}
		break;
	case 112:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 752 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = - yyattribute(2 - 2).fval; 
			}
		}
		break;
	case 113:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 754 "FileParser.y" */
 char   *string; (*(YYSTYPE YYFAR*)yyvalptr).fval = (double) strtod(m_plexer->yytext,&string); 
			}
		}
		break;
	case 114:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 756 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = atof(m_plexer->yytext); 
			}
		}
		break;
	case 115:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 760 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = (double) yyattribute(2 - 3).ival; 
			}
		}
		break;
	case 116:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 765 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = 0; /* temp */ 
			}
		}
		break;
	case 117:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 767 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = 0; /* temp */ 
			}
		}
		break;
	case 118:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 769 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = 3.141592654; 
			}
		}
		break;
	case 119:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 771 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = 4.2; 
			}
		}
		break;
	case 120:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 773 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = 1; 
			}
		}
		break;
	case 121:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 775 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = 1; 
			}
		}
		break;
	case 122:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 777 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = 1; 
			}
		}
		break;
	case 123:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 779 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = 0; 
			}
		}
		break;
	case 124:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 781 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = 0; 
			}
		}
		break;
	case 125:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 783 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = 0; 
			}
		}
		break;
	case 126:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 788 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = fabs(yyattribute(3 - 4).fval); 
			}
		}
		break;
	case 127:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 790 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = acos(yyattribute(3 - 4).fval); 
			}
		}
		break;
	case 128:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 792 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = asin(yyattribute(3 - 4).fval); 
			}
		}
		break;
	case 129:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 794 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = cos(yyattribute(3 - 4).fval); 
			}
		}
		break;
	case 130:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 796 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = sin(yyattribute(3 - 4).fval); 
			}
		}
		break;
	case 131:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 798 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = tan(yyattribute(3 - 4).fval); 
			}
		}
		break;
	case 132:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 800 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).fval = yyattribute(3 - 4).fval * 0.017453293f; 
			}
		}
		break;
	case 133:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 804 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = yyattribute(1 - 1).ival; 
			}
		}
		break;
	case 134:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[6];
			yyinitdebug((void YYFAR**)yya, 6);
#endif
			{
/* #line 806 "FileParser.y" */
 if (yyattribute(1 - 5).ival) (*(YYSTYPE YYFAR*)yyvalptr).ival=yyattribute(3 - 5).ival; else (*(YYSTYPE YYFAR*)yyvalptr).ival=yyattribute(5 - 5).ival; 
			}
		}
		break;
	case 135:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 810 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = yyattribute(2 - 3).ival; 
			}
		}
		break;
	case 136:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 812 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (yyattribute(1 - 3).ival || yyattribute(3 - 3).ival); 
			}
		}
		break;
	case 137:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 814 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (yyattribute(1 - 3).ival && yyattribute(3 - 3).ival); 
			}
		}
		break;
	case 138:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 816 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (yyattribute(1 - 3).ival < yyattribute(3 - 3).ival); 
			}
		}
		break;
	case 139:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 818 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (yyattribute(1 - 3).ival > yyattribute(3 - 3).ival); 
			}
		}
		break;
	case 140:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 820 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (yyattribute(1 - 3).ival != yyattribute(3 - 3).ival); 
			}
		}
		break;
	case 141:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 822 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (yyattribute(1 - 3).ival <= yyattribute(3 - 3).ival); 
			}
		}
		break;
	case 142:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 824 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (yyattribute(1 - 3).ival >= yyattribute(3 - 3).ival); 
			}
		}
		break;
	case 143:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 826 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (yyattribute(1 - 3).ival == yyattribute(3 - 3).ival); 
			}
		}
		break;
	case 144:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 828 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).ival = (int) yyattribute(1 - 1).fval; 
			}
		}
		break;
	case 145:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 832 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(1 - 1).fval; (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(1 - 1).fval; (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(1 - 1).fval;
			}
		}
		break;
	case 146:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 837 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(2 - 3).vval[0]; (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(2 - 3).vval[1]; (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(2 - 3).vval[2];
			}
		}
		break;
	case 147:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 839 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(1 - 3).vval[0] + yyattribute(3 - 3).vval[0];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(1 - 3).vval[1] + yyattribute(3 - 3).vval[1];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(1 - 3).vval[2] + yyattribute(3 - 3).vval[2];
            
			}
		}
		break;
	case 148:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 844 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(1 - 3).fval + yyattribute(3 - 3).vval[0];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(1 - 3).fval + yyattribute(3 - 3).vval[1];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(1 - 3).fval + yyattribute(3 - 3).vval[2];
            
			}
		}
		break;
	case 149:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 849 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(1 - 3).vval[0] - yyattribute(3 - 3).vval[0];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(1 - 3).vval[1] - yyattribute(3 - 3).vval[1];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(1 - 3).vval[2] - yyattribute(3 - 3).vval[2];
            
			}
		}
		break;
	case 150:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 854 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(1 - 3).fval - yyattribute(3 - 3).vval[0];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(1 - 3).fval - yyattribute(3 - 3).vval[1];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(1 - 3).fval - yyattribute(3 - 3).vval[2];
            
			}
		}
		break;
	case 151:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 860 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(1 - 3).vval[0] * yyattribute(3 - 3).vval[0];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(1 - 3).vval[1] * yyattribute(3 - 3).vval[1];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(1 - 3).vval[2] * yyattribute(3 - 3).vval[2];
            
			}
		}
		break;
	case 152:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 865 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(1 - 3).fval * yyattribute(3 - 3).vval[0];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(1 - 3).fval * yyattribute(3 - 3).vval[1];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(1 - 3).fval * yyattribute(3 - 3).vval[2];
            
			}
		}
		break;
	case 153:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 870 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(1 - 3).vval[0] / yyattribute(3 - 3).vval[0];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(1 - 3).vval[1] / yyattribute(3 - 3).vval[1];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(1 - 3).vval[2] / yyattribute(3 - 3).vval[2];
            
			}
		}
		break;
	case 154:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[4];
			yyinitdebug((void YYFAR**)yya, 4);
#endif
			{
/* #line 875 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(1 - 3).fval / yyattribute(3 - 3).vval[0];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(1 - 3).fval / yyattribute(3 - 3).vval[1];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(1 - 3).fval / yyattribute(3 - 3).vval[2];
            
			}
		}
		break;
	case 155:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 880 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = -yyattribute(2 - 2).vval[0];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = -yyattribute(2 - 2).vval[1];
              (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = -yyattribute(2 - 2).vval[2];
            
			}
		}
		break;
	case 156:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[8];
			yyinitdebug((void YYFAR**)yya, 8);
#endif
			{
/* #line 892 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = yyattribute(2 - 7).fval; (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = yyattribute(4 - 7).fval; (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = yyattribute(6 - 7).fval; 
			}
		}
		break;
	case 157:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[7];
			yyinitdebug((void YYFAR**)yya, 7);
#endif
			{
/* #line 898 "FileParser.y" */
 /*CVector v1($3),v2($5);
              //v1 = v1 ^ v2;
              $$[0] = v1[0]; $$[1] = v1[1]; $$[2] = v1[2];     */   
            
			}
		}
		break;
	case 158:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[5];
			yyinitdebug((void YYFAR**)yya, 5);
#endif
			{
/* #line 904 "FileParser.y" */
/* Vector v($3); v.Normalize(); $$[0] = v[0]; $$[1] = v[1]; $$[2] = v[2];*/ 
			}
		}
		break;
	case 159:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 907 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = 1; (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = 0; (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = 0; 
			}
		}
		break;
	case 160:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 909 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = 0; (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = 1; (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = 0; 
			}
		}
		break;
	case 161:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 911 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = 0; (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = 0; (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = 1; 
			}
		}
		break;
	case 162:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 913 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = 0; (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = 0; (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = 0; 
			}
		}
		break;
	case 163:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 915 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = 1; (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = 0; (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = 0; 
			}
		}
		break;
	case 164:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 917 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).vval[0] = 0; (*(YYSTYPE YYFAR*)yyvalptr).vval[1] = 1; (*(YYSTYPE YYFAR*)yyvalptr).vval[2] = 0; 
			}
		}
		break;
	case 165:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[10];
			yyinitdebug((void YYFAR**)yya, 10);
#endif
			{
/* #line 921 "FileParser.y" */
 (*(YYSTYPE YYFAR*)yyvalptr).qval[0] = yyattribute(2 - 9).fval; (*(YYSTYPE YYFAR*)yyvalptr).qval[1] = yyattribute(4 - 9).fval; (*(YYSTYPE YYFAR*)yyvalptr).qval[2] = yyattribute(6 - 9).fval; (*(YYSTYPE YYFAR*)yyvalptr).qval[3] = yyattribute(8 - 9).fval;
			}
		}
		break;
	case 166:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 940 "FileParser.y" */
 m_tmpColor.SetRGB(yyattribute(2 - 2).vval);
			}
		}
		break;
	case 167:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 944 "FileParser.y" */
 m_tmpColor.SetRGB(yyattribute(1 - 1).vval);
			}
		}
		break;
	case 168:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 955 "FileParser.y" */
 m_tmpColor.SetRed(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 169:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 957 "FileParser.y" */
 m_tmpColor.SetBlue(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 170:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[3];
			yyinitdebug((void YYFAR**)yya, 3);
#endif
			{
/* #line 959 "FileParser.y" */
 m_tmpColor.SetGreen(yyattribute(2 - 2).fval);
			}
		}
		break;
	case 171:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR* yya[2];
			yyinitdebug((void YYFAR**)yya, 2);
#endif
			{
/* #line 970 "FileParser.y" */

			memset(m_tmpStr,'\0',255);
			strncpy(m_tmpStr, m_plexer->yytext+1,
					  strlen(m_plexer->yytext) -2);
		 
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}
/* #line 977 "FileParser.y" */


CFileParser::~CFileParser()
{
}

CFileLexer* CFileParser::CreateLexer()
{
	m_plexer=new CFileLexer;

	if (!yycreate(m_plexer)) {
		return 0;
	}

	m_plexer->Create(this);

	return m_plexer;	// success
}

void		CFileParser::SetRenderStructure(CRenderStructure* pRender)
{
	m_pRenderStructure=pRender;
}



void YYPARSENAME::yytables()
{
	yyattribute_size = sizeof(YYSTYPE);
	yysstack_size = YYSTACK_SIZE;

#ifdef YYDEBUG
	static const yysymbol_t YYNEARFAR YYBASED_CODE symbol[] = {
		{ "$end", 0 },
		{ "error", 256 },
		{ "ABS_TOKEN", 257 },
		{ "CLOCK_TOKEN", 260 },
		{ "COS_TOKEN", 261 },
		{ "FLOAT_TOKEN", 266 },
		{ "PI_TOKEN", 273 },
		{ "RADIANS_TOKEN", 275 },
		{ "SIN_TOKEN", 276 },
		{ "VERSION_TOKEN", 280 },
		{ "ON_TOKEN", 281 },
		{ "OFF_TOKEN", 282 },
		{ "TRUE_TOKEN", 283 },
		{ "FALSE_TOKEN", 284 },
		{ "YES_TOKEN", 285 },
		{ "NO_TOKEN", 286 },
		{ "ACOS_TOKEN", 287 },
		{ "ASIN_TOKEN", 288 },
		{ "TAN_TOKEN", 289 },
		{ "CLOCK_DELTA_TOKEN", 297 },
		{ "VAXIS_ROTATE_TOKEN", 302 },
		{ "VCROSS_TOKEN", 303 },
		{ "VNORMALIZE_TOKEN", 305 },
		{ "VROTATE_TOKEN", 306 },
		{ "X_TOKEN", 307 },
		{ "Y_TOKEN", 308 },
		{ "Z_TOKEN", 309 },
		{ "BLUE_TOKEN", 312 },
		{ "FILTER_TOKEN", 313 },
		{ "TRANSMIT_TOKEN", 314 },
		{ "GREEN_TOKEN", 315 },
		{ "RED_TOKEN", 316 },
		{ "RGB_TOKEN", 320 },
		{ "COLOR_TOKEN", 322 },
		{ "COLOUR_TOKEN", 323 },
		{ "AMBIENT_TOKEN", 328 },
		{ "AMPERSAND_TOKEN", 329 },
		{ "BAR_TOKEN", 334 },
		{ "BOX_TOKEN", 338 },
		{ "CAMERA_TOKEN", 346 },
		{ "COLON_TOKEN", 349 },
		{ "COLOR_MAP_TOKEN", 350 },
		{ "COMMA_TOKEN", 353 },
		{ "CONE_TOKEN", 356 },
		{ "CYLINDER_TOKEN", 359 },
		{ "DASH_TOKEN", 360 },
		{ "DEFAULT_TOKEN", 362 },
		{ "DIFFUSE_TOKEN", 365 },
		{ "DIRECTION_TOKEN", 366 },
		{ "EQUALS_TOKEN", 371 },
		{ "FINISH_TOKEN", 375 },
		{ "GRADIENT_TOKEN", 380 },
		{ "GRANITE_TOKEN", 381 },
		{ "IOR_TOKEN", 393 },
		{ "LEFT_ANGLE_TOKEN", 396 },
		{ "LEFT_CURLY_TOKEN", 397 },
		{ "LEFT_PAREN_TOKEN", 398 },
		{ "LEFT_SQUARE_TOKEN", 399 },
		{ "LIGHT_SOURCE_TOKEN", 401 },
		{ "LOCATION_TOKEN", 402 },
		{ "LOOK_AT_TOKEN", 404 },
		{ "NO_SHADOW_TOKEN", 415 },
		{ "OBJECT_TOKEN", 417 },
		{ "PHONG_SIZE_TOKEN", 424 },
		{ "PIGMENT_TOKEN", 427 },
		{ "PLANE_TOKEN", 428 },
		{ "PLUS_TOKEN", 429 },
		{ "QUESTION_TOKEN", 435 },
		{ "REFLECTION_TOKEN", 441 },
		{ "RIGHT_ANGLE_TOKEN", 443 },
		{ "RIGHT_CURLY_TOKEN", 444 },
		{ "RIGHT_PAREN_TOKEN", 445 },
		{ "RIGHT_SQUARE_TOKEN", 446 },
		{ "RIGHT_TOKEN", 447 },
		{ "ROTATE_TOKEN", 449 },
		{ "SCALE_TOKEN", 451 },
		{ "SLASH_TOKEN", 455 },
		{ "SPECULAR_TOKEN", 458 },
		{ "SPHERE_TOKEN", 459 },
		{ "SPOTLIGHT_TOKEN", 460 },
		{ "SPOTTED_TOKEN", 461 },
		{ "STAR_TOKEN", 462 },
		{ "STRING_LITERAL_TOKEN", 463 },
		{ "TEXTURE_TOKEN", 466 },
		{ "THRESHOLD_TOKEN", 468 },
		{ "TORUS_TOKEN", 475 },
		{ "TRANSLATE_TOKEN", 479 },
		{ "UP_TOKEN", 484 },
		{ "TEXT_TOKEN", 507 },
		{ "TTF_TOKEN", 508 },
		{ "REL_GE_TOKEN", 509 },
		{ "REL_LE_TOKEN", 510 },
		{ "REL_NE_TOKEN", 511 },
		{ "ANGLE_TOKEN", 520 },
		{ "WIDTH_TOKEN", 521 },
		{ "PERSPECTIVE_TOKEN", 523 },
		{ "ORTHOGRAPHIC_TOKEN", 524 },
		{ "SUPERELLIPSOID_TOKEN", 555 },
		{ "QUATERNION_TOKEN", 556 },
		{ "MAX_ITERATION_TOKEN", 558 },
		{ "HYPERCOMPLEX_TOKEN", 559 },
		{ "COUNT_TOKEN", 603 },
		{ "U_TOKEN", 622 },
		{ "V_TOKEN", 623 },
		{ "PRECISION_TOKEN", 626 },
		{ "T_TOKEN", 637 },
		{ "INTERIOR_TOKEN", 650 },
		{ "FRACTAL_TOKEN", 683 },
		{ "BAILOUT_TOKEN", 684 },
		{ "POINTLIGHT_TOKEN", 685 },
		{ "TRANSPARENT_TOKEN", 686 },
		{ "HEIGHT_TOKEN", 687 },
		{ "CONSTANT_TOKEN", 688 },
		{ "FOCUS_TOKEN", 689 },
		{ "ALGORITHM_TOKEN", 691 },
		{ "ANTIALIAS_TOKEN", 692 },
		{ "HYPERCOMPLEXEXOT01_TOKEN", 693 },
		{ "HYPERCOMPLEXEXOT02_TOKEN", 694 },
		{ "HYPERCOMPLEXEXOT03_TOKEN", 695 },
		{ "HYPERCOMPLEXEXOT04_TOKEN", 696 },
		{ "HYPERCOMPLEXEXOT05_TOKEN", 697 },
		{ "HYPERCOMPLEXEXOT06_TOKEN", 698 },
		{ "HYPERCOMPLEXEXOT07_TOKEN", 699 },
		{ "HYPERCOMPLEXEXOT08_TOKEN", 700 },
		{ "HYPERCOMPLEXEXOT09_TOKEN", 701 },
		{ "HYPERCOMPLEXEXOT10_TOKEN", 702 },
		{ "HYPERCOMPLEXEXOT11_TOKEN", 703 },
		{ "HYPERCOMPLEXEXOT12_TOKEN", 704 },
		{ "HYPERCOMPLEXEXOT13_TOKEN", 705 },
		{ "HYPERCOMPLEXEXOT14_TOKEN", 706 },
		{ "HYPERCOMPLEXEXOT15_TOKEN", 707 },
		{ "HYPERCOMPLEXEXOT16_TOKEN", 708 },
		{ "SPHERIC_TOKEN", 709 },
		{ "EPSILON_TOKEN", 710 },
		{ "IMAGE_TOKEN", 711 },
		{ "DEPTH_TOKEN", 712 },
		{ "DERIVATIVE_TOKEN", 713 },
		{ "DISPERSION_TOKEN", 714 },
		{ "DISPERSION_SAMPLES_TOKEN", 715 },
		{ "PHOTONS_TOKEN", 716 },
		{ "INTENSITY_TOKEN", 717 },
		{ "PROBABILITY_REFLECTION_TOKEN", 718 },
		{ "UMINUS", 719 },
		{ NULL, 0 }
	};
	yysymbol = symbol;

	static const char* const YYNEARFAR YYBASED_CODE rule[] = {
		"$accept: scene",
		"scene: scene_item",
		"scene: scene scene_item",
		"scene: error",
		"scene_item: language_directives",
		"scene_item: camera",
		"scene_item: object",
		"scene_item: texture",
		"scene_item: display",
		"scene_item: algorithm",
		"language_directives:",
		"display: IMAGE_TOKEN LEFT_CURLY_TOKEN WIDTH_TOKEN integer HEIGHT_TOKEN integer RIGHT_CURLY_TOKEN",
		"algorithm: ALGORITHM_TOKEN LEFT_CURLY_TOKEN algorithm_item RIGHT_CURLY_TOKEN",
		"algorithm_item: DEFAULT_TOKEN",
		"algorithm_item: ANTIALIAS_TOKEN algorithm_modifier_list",
		"algorithm_modifier_list:",
		"algorithm_modifier_list: algorithm_modifier",
		"algorithm_modifier_list: algorithm_modifier_list algorithm_modifier",
		"algorithm_modifier: THRESHOLD_TOKEN double",
		"algorithm_modifier: DEPTH_TOKEN integer",
		"camera: CAMERA_TOKEN LEFT_CURLY_TOKEN cam_type cam_item_list RIGHT_CURLY_TOKEN",
		"cam_item_list: cam_item",
		"cam_item_list: cam_item_list cam_item",
		"cam_item: cam_vector",
		"cam_item: cam_modifier",
		"cam_type: ORTHOGRAPHIC_TOKEN",
		"cam_type: PERSPECTIVE_TOKEN",
		"cam_type: SPHERIC_TOKEN",
		"cam_type: SUPERELLIPSOID_TOKEN",
		"cam_vector: LOCATION_TOKEN vector",
		"cam_vector: RIGHT_TOKEN vector",
		"cam_vector: UP_TOKEN vector",
		"cam_vector: DIRECTION_TOKEN vector",
		"cam_modifier: LOOK_AT_TOKEN vector",
		"cam_modifier: WIDTH_TOKEN double",
		"cam_modifier: HEIGHT_TOKEN double",
		"cam_modifier: FOCUS_TOKEN double",
		"cam_modifier: ANGLE_TOKEN double COMMA_TOKEN double",
		"cam_modifier: SCALE_TOKEN vector",
		"cam_modifier: EPSILON_TOKEN double COMMA_TOKEN double",
		"object: finite_solid_object",
		"object: infinite_solid_object",
		"object: finite_patch_object",
		"object: csg_object",
		"object: light_source",
		"object: OBJECT_TOKEN LEFT_CURLY_TOKEN object RIGHT_CURLY_TOKEN",
		"csg_object:",
		"finite_patch_object:",
		"finite_solid_object: box",
		"finite_solid_object: fractal",
		"finite_solid_object: sphere",
		"finite_solid_object: torus",
		"finite_solid_object: cylinder",
		"finite_solid_object: cone",
		"finite_solid_object: text",
		"infinite_solid_object: plane",
		"$$1:",
		"sphere: SPHERE_TOKEN LEFT_CURLY_TOKEN vector COMMA_TOKEN double $$1 objmods RIGHT_CURLY_TOKEN",
		"$$2:",
		"box: BOX_TOKEN LEFT_CURLY_TOKEN vector COMMA_TOKEN vector $$2 objmods RIGHT_CURLY_TOKEN",
		"$$3:",
		"cylinder: CYLINDER_TOKEN LEFT_CURLY_TOKEN vector COMMA_TOKEN vector COMMA_TOKEN double $$3 objmods RIGHT_CURLY_TOKEN",
		"$$4:",
		"cone: CONE_TOKEN LEFT_CURLY_TOKEN vector COMMA_TOKEN double COMMA_TOKEN vector COMMA_TOKEN double $$4 objmods RIGHT_CURLY_TOKEN",
		"$$5:",
		"$$6:",
		"$$7:",
		"text: TEXT_TOKEN LEFT_CURLY_TOKEN $$5 TTF_TOKEN string $$6 string $$7 objmods RIGHT_CURLY_TOKEN",
		"fractal: FRACTAL_TOKEN LEFT_CURLY_TOKEN fractal_type fractal_item_list objmods RIGHT_CURLY_TOKEN",
		"fractal_item_list: fractal_item",
		"fractal_item_list: fractal_item_list fractal_item",
		"fractal_item: fractal_mod",
		"fractal_item: quaternion_literal",
		"fractal_item: string",
		"fractal_item: DERIVATIVE_TOKEN string",
		"fractal_type: QUATERNION_TOKEN",
		"fractal_type: HYPERCOMPLEX_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT01_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT02_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT03_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT04_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT05_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT06_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT07_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT08_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT09_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT10_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT11_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT12_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT13_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT14_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT15_TOKEN",
		"fractal_type: HYPERCOMPLEXEXOT16_TOKEN",
		"fractal_mod: MAX_ITERATION_TOKEN integer",
		"fractal_mod: BAILOUT_TOKEN double",
		"fractal_mod: PRECISION_TOKEN double",
		"fractal_mod: ANGLE_TOKEN double",
		"$$8:",
		"torus: TORUS_TOKEN LEFT_CURLY_TOKEN vector COMMA_TOKEN double COMMA_TOKEN double $$8 objmods RIGHT_CURLY_TOKEN",
		"$$9:",
		"plane: PLANE_TOKEN LEFT_CURLY_TOKEN vector CONSTANT_TOKEN double $$9 objmods RIGHT_CURLY_TOKEN",
		"$$10:",
		"plane: PLANE_TOKEN LEFT_CURLY_TOKEN vector COMMA_TOKEN vector $$10 objmods RIGHT_CURLY_TOKEN",
		"objmods:",
		"objmods: objmod",
		"objmods: objmods objmod",
		"objmod:",
		"objmod: interior",
		"objmod: photons",
		"objmod: TEXTURE_TOKEN LEFT_CURLY_TOKEN string RIGHT_CURLY_TOKEN",
		"objmod: transformation",
		"$$11:",
		"$$12:",
		"light_source: LIGHT_SOURCE_TOKEN LEFT_CURLY_TOKEN light_type string $$11 light_position COLOR_TOKEN color $$12 light_mod_list RIGHT_CURLY_TOKEN",
		"light_position:",
		"light_position: vector",
		"light_mod_list: light_mod",
		"light_mod_list: light_mod_list light_mod",
		"light_mod:",
		"light_type: AMBIENT_TOKEN",
		"light_type: POINTLIGHT_TOKEN",
		"light_type: SPOTLIGHT_TOKEN",
		"light_type: NO_SHADOW_TOKEN",
		"light_type: CYLINDER_TOKEN",
		"texture: plain_texture",
		"texture: patterned_texture",
		"texture: layered_texture",
		"$$13:",
		"plain_texture: TEXTURE_TOKEN $$13 LEFT_CURLY_TOKEN pnf_items RIGHT_CURLY_TOKEN",
		"pnf_items:",
		"pnf_items: pnf_item",
		"pnf_items: pnf_items pnf_item",
		"pnf_item: pigment",
		"pnf_item: finish",
		"pnf_item: string",
		"pnf_item: interior",
		"pnf_item: photons",
		"patterned_texture:",
		"layered_texture:",
		"pigment: PIGMENT_TOKEN LEFT_CURLY_TOKEN pigment RIGHT_CURLY_TOKEN",
		"pigment: PIGMENT_TOKEN LEFT_CURLY_TOKEN pig_type pig_mods RIGHT_CURLY_TOKEN",
		"pig_type:",
		"pig_type: color",
		"pig_type: pattern_type",
		"pig_mods:",
		"pig_mods: pig_mod",
		"pig_mods: pig_mods pig_mod",
		"pig_mod: color_map",
		"$$14:",
		"color_map: COLOR_MAP_TOKEN $$14 LEFT_CURLY_TOKEN color_map_entries RIGHT_CURLY_TOKEN",
		"color_map_entries: color_map_entry",
		"color_map_entries: color_map_entries color_map_entry",
		"color_map_entry: LEFT_SQUARE_TOKEN double color RIGHT_SQUARE_TOKEN",
		"pattern_type: GRANITE_TOKEN",
		"pattern_type: SPOTTED_TOKEN",
		"pattern_type: GRADIENT_TOKEN",
		"finish: FINISH_TOKEN LEFT_CURLY_TOKEN finish RIGHT_CURLY_TOKEN",
		"finish: FINISH_TOKEN LEFT_CURLY_TOKEN fin_items RIGHT_CURLY_TOKEN",
		"fin_items:",
		"fin_items: fin_item",
		"fin_items: fin_items fin_item",
		"fin_item: AMBIENT_TOKEN color",
		"fin_item: DIFFUSE_TOKEN color",
		"fin_item: SPECULAR_TOKEN color",
		"fin_item: TRANSPARENT_TOKEN color",
		"$$15:",
		"fin_item: AMBIENT_TOKEN $$15 pigment",
		"$$16:",
		"fin_item: DIFFUSE_TOKEN $$16 pigment",
		"$$17:",
		"fin_item: SPECULAR_TOKEN $$17 pigment",
		"$$18:",
		"fin_item: TRANSPARENT_TOKEN $$18 pigment",
		"fin_item: REFLECTION_TOKEN double",
		"fin_item: PHONG_SIZE_TOKEN double",
		"fin_item: TRANSPARENT_TOKEN double",
		"transformation: tran",
		"transformation: transformation tran",
		"tran: ROTATE_TOKEN vector",
		"tran: SCALE_TOKEN vector",
		"tran: TRANSLATE_TOKEN vector",
		"interior: INTERIOR_TOKEN LEFT_CURLY_TOKEN interior_items RIGHT_CURLY_TOKEN",
		"interior_items: interior_item",
		"interior_items: interior_items interior_item",
		"interior_item: IOR_TOKEN double",
		"interior_item: DISPERSION_TOKEN double",
		"interior_item: DISPERSION_SAMPLES_TOKEN integer",
		"photons: PHOTONS_TOKEN LEFT_CURLY_TOKEN photons_items RIGHT_CURLY_TOKEN",
		"photons_items: photons_item",
		"photons_items: photons_items photons_item",
		"photons_item: COUNT_TOKEN double",
		"photons_item: INTENSITY_TOKEN double",
		"photons_item: PROBABILITY_REFLECTION_TOKEN double",
		"integer: double",
		"double: fexpr",
		"fexpr: LEFT_PAREN_TOKEN fexpr RIGHT_PAREN_TOKEN",
		"fexpr: fexpr PLUS_TOKEN fexpr",
		"fexpr: fexpr DASH_TOKEN fexpr",
		"fexpr: fexpr STAR_TOKEN fexpr",
		"fexpr: fexpr SLASH_TOKEN fexpr",
		"fexpr: DASH_TOKEN fexpr",
		"fexpr: FLOAT_TOKEN",
		"fexpr: PLUS_TOKEN FLOAT_TOKEN",
		"fexpr: double_function",
		"fexpr: double_builtin_ident",
		"fexpr: LEFT_PAREN_TOKEN full_expression RIGHT_PAREN_TOKEN",
		"double_builtin_ident: CLOCK_TOKEN",
		"double_builtin_ident: CLOCK_DELTA_TOKEN",
		"double_builtin_ident: PI_TOKEN",
		"double_builtin_ident: VERSION_TOKEN",
		"double_builtin_ident: TRUE_TOKEN",
		"double_builtin_ident: YES_TOKEN",
		"double_builtin_ident: ON_TOKEN",
		"double_builtin_ident: FALSE_TOKEN",
		"double_builtin_ident: NO_TOKEN",
		"double_builtin_ident: OFF_TOKEN",
		"double_function: ABS_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN",
		"double_function: ACOS_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN",
		"double_function: ASIN_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN",
		"double_function: COS_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN",
		"double_function: SIN_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN",
		"double_function: TAN_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN",
		"double_function: RADIANS_TOKEN LEFT_PAREN_TOKEN double RIGHT_PAREN_TOKEN",
		"full_expression: lexpr",
		"full_expression: lexpr QUESTION_TOKEN full_expression COLON_TOKEN full_expression",
		"lexpr: LEFT_PAREN_TOKEN lexpr RIGHT_PAREN_TOKEN",
		"lexpr: lexpr BAR_TOKEN lexpr",
		"lexpr: lexpr AMPERSAND_TOKEN lexpr",
		"lexpr: lexpr LEFT_ANGLE_TOKEN lexpr",
		"lexpr: lexpr RIGHT_ANGLE_TOKEN lexpr",
		"lexpr: lexpr REL_NE_TOKEN lexpr",
		"lexpr: lexpr REL_LE_TOKEN lexpr",
		"lexpr: lexpr REL_GE_TOKEN lexpr",
		"lexpr: lexpr EQUALS_TOKEN lexpr",
		"lexpr: double",
		"vector: double",
		"vector: vexpr",
		"vexpr: LEFT_PAREN_TOKEN vexpr RIGHT_PAREN_TOKEN",
		"vexpr: vexpr PLUS_TOKEN vexpr",
		"vexpr: fexpr PLUS_TOKEN vexpr",
		"vexpr: vexpr DASH_TOKEN vexpr",
		"vexpr: fexpr DASH_TOKEN vexpr",
		"vexpr: vexpr STAR_TOKEN vexpr",
		"vexpr: fexpr STAR_TOKEN vexpr",
		"vexpr: vexpr SLASH_TOKEN vexpr",
		"vexpr: fexpr SLASH_TOKEN vexpr",
		"vexpr: DASH_TOKEN vexpr",
		"vexpr: vector_literal",
		"vexpr: vector_function",
		"vexpr: vector_builtin_ident",
		"vexpr: quaternion_literal",
		"vector_literal: LEFT_ANGLE_TOKEN double COMMA_TOKEN double COMMA_TOKEN double RIGHT_ANGLE_TOKEN",
		"vector_function: VAXIS_ROTATE_TOKEN LEFT_PAREN_TOKEN vector COMMA_TOKEN vector COMMA_TOKEN double RIGHT_PAREN_TOKEN",
		"vector_function: VCROSS_TOKEN LEFT_PAREN_TOKEN vector COMMA_TOKEN vector RIGHT_PAREN_TOKEN",
		"vector_function: VROTATE_TOKEN LEFT_PAREN_TOKEN vector COMMA_TOKEN vector RIGHT_PAREN_TOKEN",
		"vector_function: VNORMALIZE_TOKEN LEFT_PAREN_TOKEN vector RIGHT_PAREN_TOKEN",
		"vector_builtin_ident: X_TOKEN",
		"vector_builtin_ident: Y_TOKEN",
		"vector_builtin_ident: Z_TOKEN",
		"vector_builtin_ident: T_TOKEN",
		"vector_builtin_ident: U_TOKEN",
		"vector_builtin_ident: V_TOKEN",
		"quaternion_literal: LEFT_ANGLE_TOKEN double COMMA_TOKEN double COMMA_TOKEN double COMMA_TOKEN double RIGHT_ANGLE_TOKEN",
		"color: color_body",
		"color: COLOR_TOKEN color_body",
		"color: COLOUR_TOKEN color_body",
		"color: COLOR_TOKEN COLOR_TOKEN color_body",
		"color_body: color_vector color_keyword_group",
		"color_body: color_keyword_group",
		"color_vector: RGB_TOKEN vector",
		"color_vector: vector",
		"color_keyword_group:",
		"color_keyword_group: color_keyword",
		"color_keyword_group: color_keyword_group color_keyword",
		"color_keyword: RED_TOKEN double",
		"color_keyword: BLUE_TOKEN double",
		"color_keyword: GREEN_TOKEN double",
		"color_keyword: FILTER_TOKEN double",
		"color_keyword: TRANSMIT_TOKEN double",
		"string: STRING_LITERAL_TOKEN"
	};
	yyrule = rule;
#endif

	static const yyreduction_t YYNEARFAR YYBASED_CODE reduction[] = {
		{ 0, 1, -1 },
		{ 1, 1, 0 },
		{ 1, 2, 1 },
		{ 1, 1, 2 },
		{ 2, 1, -1 },
		{ 2, 1, -1 },
		{ 2, 1, -1 },
		{ 2, 1, -1 },
		{ 2, 1, -1 },
		{ 2, 1, -1 },
		{ 3, 0, -1 },
		{ 4, 7, 3 },
		{ 5, 4, -1 },
		{ 6, 1, 4 },
		{ 6, 2, 5 },
		{ 7, 0, -1 },
		{ 7, 1, -1 },
		{ 7, 2, -1 },
		{ 8, 2, 6 },
		{ 8, 2, 7 },
		{ 9, 5, 8 },
		{ 10, 1, -1 },
		{ 10, 2, -1 },
		{ 11, 1, -1 },
		{ 11, 1, -1 },
		{ 12, 1, 9 },
		{ 12, 1, 10 },
		{ 12, 1, 11 },
		{ 12, 1, 12 },
		{ 13, 2, 13 },
		{ 13, 2, -1 },
		{ 13, 2, 14 },
		{ 13, 2, 15 },
		{ 14, 2, 16 },
		{ 14, 2, 17 },
		{ 14, 2, 18 },
		{ 14, 2, 19 },
		{ 14, 4, 20 },
		{ 14, 2, 21 },
		{ 14, 4, 22 },
		{ 15, 1, -1 },
		{ 15, 1, -1 },
		{ 15, 1, -1 },
		{ 15, 1, -1 },
		{ 15, 1, -1 },
		{ 15, 4, -1 },
		{ 16, 0, -1 },
		{ 17, 0, -1 },
		{ 18, 1, -1 },
		{ 18, 1, -1 },
		{ 18, 1, -1 },
		{ 18, 1, -1 },
		{ 18, 1, -1 },
		{ 18, 1, -1 },
		{ 18, 1, -1 },
		{ 19, 1, -1 },
		{ 21, 0, 23 },
		{ 20, 8, 24 },
		{ 23, 0, 25 },
		{ 22, 8, 26 },
		{ 25, 0, 27 },
		{ 24, 10, 28 },
		{ 27, 0, 29 },
		{ 26, 12, 30 },
		{ 29, 0, 31 },
		{ 30, 0, 32 },
		{ 31, 0, 33 },
		{ 28, 10, 34 },
		{ 32, 6, 35 },
		{ 33, 1, -1 },
		{ 33, 2, -1 },
		{ 34, 1, -1 },
		{ 34, 1, 36 },
		{ 34, 1, 37 },
		{ 34, 2, 38 },
		{ 35, 1, 39 },
		{ 35, 1, 40 },
		{ 35, 1, 41 },
		{ 35, 1, 42 },
		{ 35, 1, 43 },
		{ 35, 1, 44 },
		{ 35, 1, 45 },
		{ 35, 1, 46 },
		{ 35, 1, 47 },
		{ 35, 1, 48 },
		{ 35, 1, 49 },
		{ 35, 1, 50 },
		{ 35, 1, 51 },
		{ 35, 1, 52 },
		{ 35, 1, 53 },
		{ 35, 1, 54 },
		{ 35, 1, 55 },
		{ 35, 1, 56 },
		{ 36, 2, 57 },
		{ 36, 2, 58 },
		{ 36, 2, 59 },
		{ 36, 2, 60 },
		{ 38, 0, 61 },
		{ 37, 10, 62 },
		{ 40, 0, 63 },
		{ 39, 8, 64 },
		{ 41, 0, 65 },
		{ 39, 8, 66 },
		{ 42, 0, -1 },
		{ 42, 1, -1 },
		{ 42, 2, -1 },
		{ 43, 0, -1 },
		{ 43, 1, -1 },
		{ 43, 1, -1 },
		{ 43, 4, 67 },
		{ 43, 1, -1 },
		{ 45, 0, 68 },
		{ 46, 0, 69 },
		{ 44, 11, 70 },
		{ 47, 0, -1 },
		{ 47, 1, 71 },
		{ 48, 1, -1 },
		{ 48, 2, -1 },
		{ 49, 0, -1 },
		{ 50, 1, 72 },
		{ 50, 1, 73 },
		{ 50, 1, -1 },
		{ 50, 1, -1 },
		{ 50, 1, -1 },
		{ 51, 1, -1 },
		{ 51, 1, -1 },
		{ 51, 1, -1 },
		{ 53, 0, 74 },
		{ 52, 5, 75 },
		{ 54, 0, -1 },
		{ 54, 1, -1 },
		{ 54, 2, -1 },
		{ 55, 1, -1 },
		{ 55, 1, -1 },
		{ 55, 1, 76 },
		{ 55, 1, -1 },
		{ 55, 1, -1 },
		{ 56, 0, -1 },
		{ 57, 0, -1 },
		{ 58, 4, -1 },
		{ 58, 5, -1 },
		{ 59, 0, -1 },
		{ 59, 1, -1 },
		{ 59, 1, -1 },
		{ 60, 0, -1 },
		{ 60, 1, -1 },
		{ 60, 2, -1 },
		{ 61, 1, -1 },
		{ 63, 0, 77 },
		{ 62, 5, -1 },
		{ 64, 1, -1 },
		{ 64, 2, -1 },
		{ 65, 4, 78 },
		{ 66, 1, 79 },
		{ 66, 1, 80 },
		{ 66, 1, 81 },
		{ 67, 4, -1 },
		{ 67, 4, -1 },
		{ 68, 0, -1 },
		{ 68, 1, -1 },
		{ 68, 2, -1 },
		{ 69, 2, 82 },
		{ 69, 2, 83 },
		{ 69, 2, 84 },
		{ 69, 2, 85 },
		{ 70, 0, 86 },
		{ 69, 3, 87 },
		{ 71, 0, 88 },
		{ 69, 3, 89 },
		{ 72, 0, 90 },
		{ 69, 3, 91 },
		{ 73, 0, 92 },
		{ 69, 3, 93 },
		{ 69, 2, 94 },
		{ 69, 2, 95 },
		{ 69, 2, 96 },
		{ 74, 1, -1 },
		{ 74, 2, -1 },
		{ 75, 2, 97 },
		{ 75, 2, 98 },
		{ 75, 2, 99 },
		{ 76, 4, -1 },
		{ 77, 1, -1 },
		{ 77, 2, -1 },
		{ 78, 2, 100 },
		{ 78, 2, 101 },
		{ 78, 2, 102 },
		{ 79, 4, -1 },
		{ 80, 1, -1 },
		{ 80, 2, -1 },
		{ 81, 2, 103 },
		{ 81, 2, 104 },
		{ 81, 2, 105 },
		{ 82, 1, 106 },
		{ 83, 1, -1 },
		{ 84, 3, 107 },
		{ 84, 3, 108 },
		{ 84, 3, 109 },
		{ 84, 3, 110 },
		{ 84, 3, 111 },
		{ 84, 2, 112 },
		{ 84, 1, 113 },
		{ 84, 2, 114 },
		{ 84, 1, -1 },
		{ 84, 1, -1 },
		{ 84, 3, 115 },
		{ 85, 1, 116 },
		{ 85, 1, 117 },
		{ 85, 1, 118 },
		{ 85, 1, 119 },
		{ 85, 1, 120 },
		{ 85, 1, 121 },
		{ 85, 1, 122 },
		{ 85, 1, 123 },
		{ 85, 1, 124 },
		{ 85, 1, 125 },
		{ 86, 4, 126 },
		{ 86, 4, 127 },
		{ 86, 4, 128 },
		{ 86, 4, 129 },
		{ 86, 4, 130 },
		{ 86, 4, 131 },
		{ 86, 4, 132 },
		{ 87, 1, 133 },
		{ 87, 5, 134 },
		{ 88, 3, 135 },
		{ 88, 3, 136 },
		{ 88, 3, 137 },
		{ 88, 3, 138 },
		{ 88, 3, 139 },
		{ 88, 3, 140 },
		{ 88, 3, 141 },
		{ 88, 3, 142 },
		{ 88, 3, 143 },
		{ 88, 1, 144 },
		{ 89, 1, 145 },
		{ 89, 1, -1 },
		{ 90, 3, 146 },
		{ 90, 3, 147 },
		{ 90, 3, 148 },
		{ 90, 3, 149 },
		{ 90, 3, 150 },
		{ 90, 3, 151 },
		{ 90, 3, 152 },
		{ 90, 3, 153 },
		{ 90, 3, 154 },
		{ 90, 2, 155 },
		{ 90, 1, -1 },
		{ 90, 1, -1 },
		{ 90, 1, -1 },
		{ 90, 1, -1 },
		{ 91, 7, 156 },
		{ 92, 8, -1 },
		{ 92, 6, 157 },
		{ 92, 6, -1 },
		{ 92, 4, 158 },
		{ 93, 1, 159 },
		{ 93, 1, 160 },
		{ 93, 1, 161 },
		{ 93, 1, 162 },
		{ 93, 1, 163 },
		{ 93, 1, 164 },
		{ 94, 9, 165 },
		{ 95, 1, -1 },
		{ 95, 2, -1 },
		{ 95, 2, -1 },
		{ 95, 3, -1 },
		{ 96, 2, -1 },
		{ 96, 1, -1 },
		{ 97, 2, 166 },
		{ 97, 1, 167 },
		{ 98, 0, -1 },
		{ 98, 1, -1 },
		{ 98, 2, -1 },
		{ 99, 2, 168 },
		{ 99, 2, 169 },
		{ 99, 2, 170 },
		{ 99, 2, -1 },
		{ 99, 2, -1 },
		{ 100, 1, 171 }
	};
	yyreduction = reduction;

	static const yytokenaction_t YYNEARFAR YYBASED_CODE tokenaction[] = {
		{ 292, YYAT_SHIFT, 55 },
		{ 111, YYAT_SHIFT, 192 },
		{ 221, YYAT_SHIFT, 219 },
		{ 292, YYAT_SHIFT, 56 },
		{ 292, YYAT_SHIFT, 57 },
		{ 16, YYAT_ACCEPT, 0 },
		{ 393, YYAT_SHIFT, 458 },
		{ 52, YYAT_SHIFT, 135 },
		{ 136, YYAT_SHIFT, 219 },
		{ 292, YYAT_SHIFT, 58 },
		{ 44, YYAT_SHIFT, 104 },
		{ 518, YYAT_SHIFT, 519 },
		{ 41, YYAT_SHIFT, 97 },
		{ 41, YYAT_SHIFT, 98 },
		{ 332, YYAT_SHIFT, 242 },
		{ 331, YYAT_SHIFT, 242 },
		{ 292, YYAT_SHIFT, 59 },
		{ 202, YYAT_SHIFT, 195 },
		{ 292, YYAT_SHIFT, 60 },
		{ 292, YYAT_SHIFT, 61 },
		{ 503, YYAT_SHIFT, 512 },
		{ 332, YYAT_SHIFT, 243 },
		{ 331, YYAT_SHIFT, 243 },
		{ 292, YYAT_SHIFT, 62 },
		{ 292, YYAT_SHIFT, 63 },
		{ 292, YYAT_SHIFT, 64 },
		{ 292, YYAT_SHIFT, 65 },
		{ 292, YYAT_SHIFT, 66 },
		{ 292, YYAT_SHIFT, 67 },
		{ 292, YYAT_SHIFT, 68 },
		{ 292, YYAT_SHIFT, 69 },
		{ 292, YYAT_SHIFT, 70 },
		{ 292, YYAT_SHIFT, 71 },
		{ 113, YYAT_SHIFT, 195 },
		{ 506, YYAT_SHIFT, 505 },
		{ 338, YYAT_SHIFT, 247 },
		{ 269, YYAT_SHIFT, 170 },
		{ 440, YYAT_REDUCE, 271 },
		{ 440, YYAT_REDUCE, 271 },
		{ 500, YYAT_SHIFT, 510 },
		{ 292, YYAT_SHIFT, 72 },
		{ 44, YYAT_SHIFT, 105 },
		{ 445, YYAT_SHIFT, 444 },
		{ 269, YYAT_SHIFT, 171 },
		{ 41, YYAT_SHIFT, 99 },
		{ 292, YYAT_SHIFT, 73 },
		{ 292, YYAT_SHIFT, 74 },
		{ 388, YYAT_SHIFT, 385 },
		{ 292, YYAT_SHIFT, 75 },
		{ 292, YYAT_SHIFT, 76 },
		{ 292, YYAT_SHIFT, 77 },
		{ 292, YYAT_SHIFT, 78 },
		{ 292, YYAT_SHIFT, 79 },
		{ 498, YYAT_SHIFT, 490 },
		{ 268, YYAT_SHIFT, 170 },
		{ 292, YYAT_SHIFT, 365 },
		{ 292, YYAT_SHIFT, 366 },
		{ 292, YYAT_SHIFT, 367 },
		{ 292, YYAT_SHIFT, 368 },
		{ 292, YYAT_SHIFT, 369 },
		{ 134, YYAT_SHIFT, 208 },
		{ 268, YYAT_SHIFT, 171 },
		{ 261, YYAT_SHIFT, 170 },
		{ 292, YYAT_SHIFT, 370 },
		{ 514, YYAT_SHIFT, 55 },
		{ 292, YYAT_SHIFT, 371 },
		{ 292, YYAT_SHIFT, 372 },
		{ 514, YYAT_SHIFT, 56 },
		{ 514, YYAT_SHIFT, 57 },
		{ 261, YYAT_SHIFT, 171 },
		{ 363, YYAT_SHIFT, 356 },
		{ 497, YYAT_SHIFT, 509 },
		{ 496, YYAT_SHIFT, 508 },
		{ 514, YYAT_SHIFT, 58 },
		{ 260, YYAT_SHIFT, 165 },
		{ 495, YYAT_ERROR, 0 },
		{ 314, YYAT_SHIFT, 305 },
		{ 338, YYAT_SHIFT, 249 },
		{ 314, YYAT_SHIFT, 306 },
		{ 506, YYAT_SHIFT, 515 },
		{ 514, YYAT_SHIFT, 59 },
		{ 260, YYAT_SHIFT, 166 },
		{ 514, YYAT_SHIFT, 60 },
		{ 514, YYAT_SHIFT, 61 },
		{ 493, YYAT_SHIFT, 502 },
		{ 113, YYAT_SHIFT, 196 },
		{ 202, YYAT_SHIFT, 295 },
		{ 514, YYAT_SHIFT, 62 },
		{ 514, YYAT_SHIFT, 63 },
		{ 514, YYAT_SHIFT, 64 },
		{ 514, YYAT_SHIFT, 65 },
		{ 514, YYAT_SHIFT, 66 },
		{ 514, YYAT_SHIFT, 67 },
		{ 514, YYAT_SHIFT, 68 },
		{ 514, YYAT_SHIFT, 69 },
		{ 514, YYAT_SHIFT, 70 },
		{ 514, YYAT_SHIFT, 71 },
		{ 44, YYAT_SHIFT, 106 },
		{ 388, YYAT_SHIFT, 453 },
		{ 0, YYAT_SHIFT, 1 },
		{ 489, YYAT_SHIFT, 499 },
		{ 482, YYAT_SHIFT, 495 },
		{ 338, YYAT_SHIFT, 250 },
		{ 292, YYAT_SHIFT, 80 },
		{ 514, YYAT_SHIFT, 72 },
		{ 202, YYAT_SHIFT, 189 },
		{ 314, YYAT_SHIFT, 308 },
		{ 363, YYAT_SHIFT, 357 },
		{ 216, YYAT_SHIFT, 208 },
		{ 514, YYAT_SHIFT, 73 },
		{ 514, YYAT_SHIFT, 74 },
		{ 259, YYAT_SHIFT, 170 },
		{ 514, YYAT_SHIFT, 75 },
		{ 514, YYAT_SHIFT, 76 },
		{ 514, YYAT_SHIFT, 77 },
		{ 514, YYAT_SHIFT, 78 },
		{ 514, YYAT_SHIFT, 79 },
		{ 468, YYAT_SHIFT, 491 },
		{ 259, YYAT_SHIFT, 171 },
		{ 258, YYAT_SHIFT, 165 },
		{ 463, YYAT_SHIFT, 488 },
		{ 113, YYAT_SHIFT, 189 },
		{ 45, YYAT_SHIFT, 2 },
		{ 292, YYAT_SHIFT, 373 },
		{ 292, YYAT_SHIFT, 374 },
		{ 462, YYAT_SHIFT, 487 },
		{ 258, YYAT_SHIFT, 166 },
		{ 514, YYAT_SHIFT, 370 },
		{ 287, YYAT_SHIFT, 55 },
		{ 514, YYAT_SHIFT, 371 },
		{ 514, YYAT_SHIFT, 372 },
		{ 287, YYAT_SHIFT, 56 },
		{ 287, YYAT_SHIFT, 57 },
		{ 183, YYAT_SHIFT, 172 },
		{ 430, YYAT_SHIFT, 196 },
		{ 419, YYAT_SHIFT, 476 },
		{ 445, YYAT_SHIFT, 483 },
		{ 287, YYAT_SHIFT, 58 },
		{ 337, YYAT_SHIFT, 249 },
		{ 292, YYAT_SHIFT, 81 },
		{ 45, YYAT_SHIFT, 4 },
		{ 292, YYAT_SHIFT, 82 },
		{ 44, YYAT_SHIFT, 107 },
		{ 45, YYAT_SHIFT, 5 },
		{ 287, YYAT_SHIFT, 59 },
		{ 291, YYAT_SHIFT, 356 },
		{ 287, YYAT_SHIFT, 60 },
		{ 287, YYAT_SHIFT, 61 },
		{ 418, YYAT_SHIFT, 475 },
		{ 338, YYAT_SHIFT, 252 },
		{ 417, YYAT_SHIFT, 474 },
		{ 287, YYAT_SHIFT, 62 },
		{ 287, YYAT_SHIFT, 63 },
		{ 287, YYAT_SHIFT, 64 },
		{ 287, YYAT_SHIFT, 65 },
		{ 287, YYAT_SHIFT, 66 },
		{ 287, YYAT_SHIFT, 67 },
		{ 287, YYAT_SHIFT, 68 },
		{ 287, YYAT_SHIFT, 69 },
		{ 287, YYAT_SHIFT, 70 },
		{ 287, YYAT_SHIFT, 71 },
		{ 414, YYAT_SHIFT, 471 },
		{ 411, YYAT_SHIFT, 470 },
		{ 337, YYAT_SHIFT, 250 },
		{ 410, YYAT_SHIFT, 238 },
		{ 393, YYAT_SHIFT, 390 },
		{ 363, YYAT_SHIFT, 358 },
		{ 514, YYAT_SHIFT, 80 },
		{ 287, YYAT_SHIFT, 72 },
		{ 183, YYAT_SHIFT, 173 },
		{ 292, YYAT_SHIFT, 196 },
		{ 183, YYAT_SHIFT, 174 },
		{ 292, YYAT_SHIFT, 83 },
		{ 287, YYAT_SHIFT, 73 },
		{ 287, YYAT_SHIFT, 74 },
		{ 216, YYAT_SHIFT, 189 },
		{ 287, YYAT_SHIFT, 75 },
		{ 287, YYAT_SHIFT, 76 },
		{ 287, YYAT_SHIFT, 77 },
		{ 287, YYAT_SHIFT, 78 },
		{ 287, YYAT_SHIFT, 79 },
		{ 0, YYAT_SHIFT, 2 },
		{ 291, YYAT_SHIFT, 357 },
		{ 363, YYAT_SHIFT, 359 },
		{ 134, YYAT_SHIFT, 209 },
		{ 45, YYAT_SHIFT, 6 },
		{ 363, YYAT_SHIFT, 432 },
		{ 408, YYAT_SHIFT, 467 },
		{ 407, YYAT_SHIFT, 466 },
		{ 0, YYAT_SHIFT, 3 },
		{ 370, YYAT_SHIFT, 73 },
		{ 370, YYAT_SHIFT, 74 },
		{ 291, YYAT_SHIFT, 195 },
		{ 370, YYAT_SHIFT, 75 },
		{ 370, YYAT_SHIFT, 76 },
		{ 370, YYAT_SHIFT, 77 },
		{ 370, YYAT_SHIFT, 78 },
		{ 370, YYAT_SHIFT, 79 },
		{ 41, YYAT_SHIFT, 100 },
		{ 0, YYAT_SHIFT, 4 },
		{ 363, YYAT_SHIFT, 360 },
		{ 45, YYAT_SHIFT, 7 },
		{ 0, YYAT_SHIFT, 5 },
		{ 514, YYAT_SHIFT, 81 },
		{ 292, YYAT_SHIFT, 375 },
		{ 514, YYAT_SHIFT, 82 },
		{ 237, YYAT_SHIFT, 242 },
		{ 501, YYAT_SHIFT, 305 },
		{ 406, YYAT_SHIFT, 465 },
		{ 501, YYAT_SHIFT, 306 },
		{ 337, YYAT_SHIFT, 252 },
		{ 183, YYAT_SHIFT, 283 },
		{ 45, YYAT_SHIFT, 8 },
		{ 237, YYAT_SHIFT, 243 },
		{ 183, YYAT_SHIFT, 175 },
		{ 338, YYAT_SHIFT, 253 },
		{ 338, YYAT_SHIFT, 254 },
		{ 338, YYAT_SHIFT, 255 },
		{ 183, YYAT_SHIFT, 176 },
		{ 150, YYAT_SHIFT, 165 },
		{ 511, YYAT_SHIFT, 517 },
		{ 405, YYAT_SHIFT, 464 },
		{ 134, YYAT_SHIFT, 210 },
		{ 400, YYAT_SHIFT, 189 },
		{ 501, YYAT_SHIFT, 307 },
		{ 511, YYAT_SHIFT, 305 },
		{ 150, YYAT_SHIFT, 166 },
		{ 511, YYAT_SHIFT, 306 },
		{ 379, YYAT_SHIFT, 444 },
		{ 378, YYAT_SHIFT, 443 },
		{ 345, YYAT_SHIFT, 247 },
		{ 287, YYAT_SHIFT, 80 },
		{ 216, YYAT_SHIFT, 209 },
		{ 371, YYAT_SHIFT, 440 },
		{ 362, YYAT_SHIFT, 431 },
		{ 345, YYAT_SHIFT, 248 },
		{ 514, YYAT_SHIFT, 83 },
		{ 501, YYAT_SHIFT, 308 },
		{ 361, YYAT_REDUCE, 171 },
		{ 360, YYAT_REDUCE, 169 },
		{ 357, YYAT_REDUCE, 167 },
		{ 291, YYAT_SHIFT, 358 },
		{ 511, YYAT_SHIFT, 307 },
		{ 45, YYAT_SHIFT, 9 },
		{ 0, YYAT_SHIFT, 6 },
		{ 356, YYAT_REDUCE, 165 },
		{ 221, YYAT_SHIFT, 220 },
		{ 267, YYAT_SHIFT, 163 },
		{ 370, YYAT_SHIFT, 80 },
		{ 352, YYAT_SHIFT, 416 },
		{ 341, YYAT_SHIFT, 410 },
		{ 183, YYAT_SHIFT, 177 },
		{ 136, YYAT_SHIFT, 220 },
		{ 335, YYAT_SHIFT, 409 },
		{ 309, YYAT_SHIFT, 402 },
		{ 511, YYAT_SHIFT, 308 },
		{ 245, YYAT_SHIFT, 247 },
		{ 307, YYAT_SHIFT, 400 },
		{ 291, YYAT_SHIFT, 359 },
		{ 45, YYAT_SHIFT, 11 },
		{ 0, YYAT_SHIFT, 7 },
		{ 245, YYAT_SHIFT, 248 },
		{ 448, YYAT_SHIFT, 365 },
		{ 448, YYAT_SHIFT, 366 },
		{ 448, YYAT_SHIFT, 367 },
		{ 448, YYAT_SHIFT, 368 },
		{ 448, YYAT_SHIFT, 369 },
		{ 287, YYAT_SHIFT, 81 },
		{ 299, YYAT_SHIFT, 397 },
		{ 287, YYAT_SHIFT, 82 },
		{ 216, YYAT_SHIFT, 210 },
		{ 0, YYAT_SHIFT, 8 },
		{ 345, YYAT_SHIFT, 249 },
		{ 297, YYAT_SHIFT, 395 },
		{ 294, YYAT_ERROR, 0 },
		{ 291, YYAT_SHIFT, 360 },
		{ 337, YYAT_SHIFT, 253 },
		{ 337, YYAT_SHIFT, 254 },
		{ 337, YYAT_SHIFT, 255 },
		{ 393, YYAT_SHIFT, 391 },
		{ 393, YYAT_SHIFT, 392 },
		{ 293, YYAT_ERROR, 0 },
		{ 286, YYAT_SHIFT, 350 },
		{ 285, YYAT_SHIFT, 349 },
		{ 370, YYAT_SHIFT, 81 },
		{ 282, YYAT_SHIFT, 348 },
		{ 370, YYAT_SHIFT, 82 },
		{ 183, YYAT_SHIFT, 178 },
		{ 183, YYAT_SHIFT, 179 },
		{ 278, YYAT_SHIFT, 347 },
		{ 134, YYAT_SHIFT, 211 },
		{ 45, YYAT_SHIFT, 12 },
		{ 202, YYAT_SHIFT, 197 },
		{ 236, YYAT_SHIFT, 330 },
		{ 235, YYAT_SHIFT, 329 },
		{ 234, YYAT_SHIFT, 328 },
		{ 233, YYAT_SHIFT, 327 },
		{ 345, YYAT_SHIFT, 250 },
		{ 245, YYAT_SHIFT, 249 },
		{ 232, YYAT_SHIFT, 326 },
		{ 287, YYAT_SHIFT, 83 },
		{ 505, YYAT_SHIFT, 55 },
		{ 0, YYAT_SHIFT, 9 },
		{ 231, YYAT_SHIFT, 325 },
		{ 505, YYAT_SHIFT, 56 },
		{ 505, YYAT_SHIFT, 57 },
		{ 230, YYAT_SHIFT, 324 },
		{ 229, YYAT_SHIFT, 323 },
		{ 113, YYAT_SHIFT, 197 },
		{ 0, YYAT_SHIFT, 10 },
		{ 505, YYAT_SHIFT, 58 },
		{ 428, YYAT_REDUCE, 235 },
		{ 428, YYAT_REDUCE, 235 },
		{ 428, YYAT_REDUCE, 235 },
		{ 428, YYAT_REDUCE, 235 },
		{ 428, YYAT_REDUCE, 235 },
		{ 267, YYAT_SHIFT, 164 },
		{ 505, YYAT_SHIFT, 59 },
		{ 0, YYAT_SHIFT, 11 },
		{ 505, YYAT_SHIFT, 60 },
		{ 505, YYAT_SHIFT, 61 },
		{ 228, YYAT_SHIFT, 322 },
		{ 227, YYAT_SHIFT, 321 },
		{ 245, YYAT_SHIFT, 250 },
		{ 505, YYAT_SHIFT, 62 },
		{ 505, YYAT_SHIFT, 63 },
		{ 505, YYAT_SHIFT, 64 },
		{ 505, YYAT_SHIFT, 65 },
		{ 505, YYAT_SHIFT, 66 },
		{ 505, YYAT_SHIFT, 67 },
		{ 505, YYAT_SHIFT, 68 },
		{ 505, YYAT_SHIFT, 69 },
		{ 505, YYAT_SHIFT, 70 },
		{ 505, YYAT_SHIFT, 71 },
		{ 226, YYAT_SHIFT, 320 },
		{ 225, YYAT_SHIFT, 319 },
		{ 111, YYAT_SHIFT, 193 },
		{ 52, YYAT_SHIFT, 136 },
		{ 216, YYAT_SHIFT, 211 },
		{ 198, YYAT_SHIFT, 294 },
		{ 197, YYAT_SHIFT, 293 },
		{ 505, YYAT_SHIFT, 72 },
		{ 267, YYAT_SHIFT, 165 },
		{ 16, YYAT_SHIFT, 2 },
		{ 345, YYAT_SHIFT, 252 },
		{ 196, YYAT_SHIFT, 292 },
		{ 239, YYAT_SHIFT, 240 },
		{ 159, YYAT_SHIFT, 247 },
		{ 134, YYAT_SHIFT, 212 },
		{ 267, YYAT_SHIFT, 166 },
		{ 0, YYAT_SHIFT, 12 },
		{ 16, YYAT_SHIFT, 3 },
		{ 159, YYAT_SHIFT, 248 },
		{ 383, YYAT_SHIFT, 365 },
		{ 383, YYAT_SHIFT, 366 },
		{ 383, YYAT_SHIFT, 367 },
		{ 383, YYAT_SHIFT, 368 },
		{ 383, YYAT_SHIFT, 369 },
		{ 202, YYAT_SHIFT, 198 },
		{ 195, YYAT_SHIFT, 291 },
		{ 160, YYAT_SHIFT, 256 },
		{ 16, YYAT_SHIFT, 4 },
		{ 245, YYAT_SHIFT, 251 },
		{ 156, YYAT_SHIFT, 156 },
		{ 16, YYAT_SHIFT, 5 },
		{ 292, YYAT_SHIFT, 84 },
		{ 292, YYAT_SHIFT, 85 },
		{ 44, YYAT_SHIFT, 108 },
		{ 388, YYAT_SHIFT, 386 },
		{ 388, YYAT_SHIFT, 387 },
		{ 245, YYAT_SHIFT, 252 },
		{ 155, YYAT_SHIFT, 244 },
		{ 245, YYAT_SHIFT, 336 },
		{ 154, YYAT_REDUCE, 194 },
		{ 113, YYAT_SHIFT, 198 },
		{ 137, YYAT_SHIFT, 223 },
		{ 344, YYAT_SHIFT, 247 },
		{ 134, YYAT_SHIFT, 213 },
		{ 115, YYAT_SHIFT, 207 },
		{ 114, YYAT_SHIFT, 206 },
		{ 292, YYAT_SHIFT, 86 },
		{ 344, YYAT_SHIFT, 248 },
		{ 343, YYAT_SHIFT, 247 },
		{ 112, YYAT_SHIFT, 194 },
		{ 110, YYAT_SHIFT, 191 },
		{ 342, YYAT_SHIFT, 247 },
		{ 103, YYAT_SHIFT, 188 },
		{ 343, YYAT_SHIFT, 248 },
		{ 102, YYAT_SHIFT, 187 },
		{ 159, YYAT_SHIFT, 249 },
		{ 342, YYAT_SHIFT, 248 },
		{ 101, YYAT_ERROR, 0 },
		{ 340, YYAT_SHIFT, 247 },
		{ 161, YYAT_SHIFT, 168 },
		{ 91, YYAT_SHIFT, 167 },
		{ 87, YYAT_REDUCE, 194 },
		{ 216, YYAT_SHIFT, 212 },
		{ 340, YYAT_SHIFT, 248 },
		{ 51, YYAT_SHIFT, 116 },
		{ 83, YYAT_SHIFT, 162 },
		{ 76, YYAT_SHIFT, 149 },
		{ 51, YYAT_SHIFT, 117 },
		{ 75, YYAT_SHIFT, 148 },
		{ 157, YYAT_SHIFT, 163 },
		{ 505, YYAT_SHIFT, 152 },
		{ 74, YYAT_SHIFT, 147 },
		{ 16, YYAT_SHIFT, 6 },
		{ 95, YYAT_SHIFT, 168 },
		{ 501, YYAT_SHIFT, 197 },
		{ 73, YYAT_SHIFT, 146 },
		{ 345, YYAT_SHIFT, 253 },
		{ 345, YYAT_SHIFT, 254 },
		{ 345, YYAT_SHIFT, 255 },
		{ 71, YYAT_SHIFT, 145 },
		{ 159, YYAT_SHIFT, 250 },
		{ 239, YYAT_SHIFT, 241 },
		{ 339, YYAT_SHIFT, 247 },
		{ 70, YYAT_SHIFT, 144 },
		{ 344, YYAT_SHIFT, 249 },
		{ 69, YYAT_SHIFT, 143 },
		{ 61, YYAT_SHIFT, 142 },
		{ 339, YYAT_SHIFT, 248 },
		{ 16, YYAT_SHIFT, 7 },
		{ 60, YYAT_SHIFT, 141 },
		{ 343, YYAT_SHIFT, 249 },
		{ 216, YYAT_SHIFT, 213 },
		{ 511, YYAT_SHIFT, 197 },
		{ 342, YYAT_SHIFT, 249 },
		{ 363, YYAT_SHIFT, 361 },
		{ 514, YYAT_SHIFT, 84 },
		{ 514, YYAT_SHIFT, 85 },
		{ 239, YYAT_SHIFT, 246 },
		{ 57, YYAT_SHIFT, 140 },
		{ 16, YYAT_SHIFT, 8 },
		{ 340, YYAT_SHIFT, 249 },
		{ 55, YYAT_SHIFT, 139 },
		{ 245, YYAT_SHIFT, 253 },
		{ 245, YYAT_SHIFT, 254 },
		{ 245, YYAT_SHIFT, 255 },
		{ 53, YYAT_SHIFT, 138 },
		{ 48, YYAT_SHIFT, 113 },
		{ 239, YYAT_SHIFT, 242 },
		{ 505, YYAT_SHIFT, 153 },
		{ 344, YYAT_SHIFT, 250 },
		{ 514, YYAT_SHIFT, 86 },
		{ 15, YYAT_SHIFT, 53 },
		{ 14, YYAT_SHIFT, 52 },
		{ 13, YYAT_SHIFT, 51 },
		{ 239, YYAT_SHIFT, 243 },
		{ 343, YYAT_SHIFT, 250 },
		{ 12, YYAT_SHIFT, 50 },
		{ 11, YYAT_SHIFT, 49 },
		{ 342, YYAT_SHIFT, 250 },
		{ 159, YYAT_SHIFT, 251 },
		{ 183, YYAT_SHIFT, 180 },
		{ 9, YYAT_SHIFT, 47 },
		{ 183, YYAT_SHIFT, 181 },
		{ 8, YYAT_SHIFT, 46 },
		{ 339, YYAT_SHIFT, 249 },
		{ 340, YYAT_SHIFT, 250 },
		{ 7, YYAT_SHIFT, 45 },
		{ 159, YYAT_SHIFT, 252 },
		{ 161, YYAT_SHIFT, 169 },
		{ 6, YYAT_SHIFT, 44 },
		{ 16, YYAT_SHIFT, 9 },
		{ 5, YYAT_SHIFT, 43 },
		{ 4, YYAT_SHIFT, 42 },
		{ 45, YYAT_SHIFT, 13 },
		{ 3, YYAT_SHIFT, 41 },
		{ 2, YYAT_SHIFT, 40 },
		{ -1, YYAT_ERROR, 0 },
		{ 16, YYAT_SHIFT, 10 },
		{ 157, YYAT_SHIFT, 164 },
		{ 505, YYAT_SHIFT, 83 },
		{ 501, YYAT_SHIFT, 198 },
		{ -1, YYAT_ERROR, 0 },
		{ 95, YYAT_SHIFT, 169 },
		{ 183, YYAT_SHIFT, 182 },
		{ 161, YYAT_SHIFT, 257 },
		{ -1, YYAT_ERROR, 0 },
		{ 16, YYAT_SHIFT, 11 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 339, YYAT_SHIFT, 250 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 161, YYAT_SHIFT, 170 },
		{ -1, YYAT_ERROR, 0 },
		{ 344, YYAT_SHIFT, 252 },
		{ -1, YYAT_ERROR, 0 },
		{ 511, YYAT_SHIFT, 198 },
		{ 287, YYAT_SHIFT, 84 },
		{ 287, YYAT_SHIFT, 85 },
		{ 161, YYAT_SHIFT, 171 },
		{ 343, YYAT_SHIFT, 252 },
		{ -1, YYAT_ERROR, 0 },
		{ 157, YYAT_SHIFT, 165 },
		{ 342, YYAT_SHIFT, 252 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 95, YYAT_SHIFT, 170 },
		{ 291, YYAT_SHIFT, 361 },
		{ -1, YYAT_ERROR, 0 },
		{ 157, YYAT_SHIFT, 166 },
		{ 340, YYAT_SHIFT, 252 },
		{ -1, YYAT_ERROR, 0 },
		{ 287, YYAT_SHIFT, 86 },
		{ 95, YYAT_SHIFT, 171 },
		{ 370, YYAT_SHIFT, 84 },
		{ 370, YYAT_SHIFT, 85 },
		{ 16, YYAT_SHIFT, 12 },
		{ 382, YYAT_SHIFT, 365 },
		{ 382, YYAT_SHIFT, 366 },
		{ 382, YYAT_SHIFT, 367 },
		{ 382, YYAT_SHIFT, 368 },
		{ 382, YYAT_SHIFT, 369 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 370, YYAT_SHIFT, 86 },
		{ 0, YYAT_SHIFT, 13 },
		{ 159, YYAT_SHIFT, 253 },
		{ 159, YYAT_SHIFT, 254 },
		{ 159, YYAT_SHIFT, 255 },
		{ 339, YYAT_SHIFT, 252 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 0, YYAT_SHIFT, 14 },
		{ 51, YYAT_SHIFT, 118 },
		{ 51, YYAT_SHIFT, 119 },
		{ 51, YYAT_SHIFT, 120 },
		{ 51, YYAT_SHIFT, 121 },
		{ 51, YYAT_SHIFT, 122 },
		{ 51, YYAT_SHIFT, 123 },
		{ 51, YYAT_SHIFT, 124 },
		{ 51, YYAT_SHIFT, 125 },
		{ 51, YYAT_SHIFT, 126 },
		{ 51, YYAT_SHIFT, 127 },
		{ 51, YYAT_SHIFT, 128 },
		{ 51, YYAT_SHIFT, 129 },
		{ 51, YYAT_SHIFT, 130 },
		{ 51, YYAT_SHIFT, 131 },
		{ 51, YYAT_SHIFT, 132 },
		{ 51, YYAT_SHIFT, 133 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 0, YYAT_SHIFT, 15 },
		{ -1, YYAT_ERROR, 0 },
		{ 344, YYAT_SHIFT, 253 },
		{ 344, YYAT_SHIFT, 254 },
		{ 344, YYAT_SHIFT, 255 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 343, YYAT_SHIFT, 253 },
		{ 343, YYAT_SHIFT, 254 },
		{ 343, YYAT_SHIFT, 255 },
		{ 342, YYAT_SHIFT, 253 },
		{ 342, YYAT_SHIFT, 254 },
		{ 342, YYAT_SHIFT, 255 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 340, YYAT_SHIFT, 253 },
		{ 340, YYAT_SHIFT, 254 },
		{ 340, YYAT_SHIFT, 255 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 339, YYAT_SHIFT, 253 },
		{ 339, YYAT_SHIFT, 254 },
		{ 339, YYAT_SHIFT, 255 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 16, YYAT_SHIFT, 13 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 16, YYAT_SHIFT, 14 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ -1, YYAT_ERROR, 0 },
		{ 16, YYAT_SHIFT, 15 }
	};
	yytokenaction = tokenaction;
	yytokenaction_size = 717;

	static const yystateaction_t YYNEARFAR YYBASED_CODE stateaction[] = {
		{ -157, 1, YYAT_REDUCE, 10 },
		{ 0, 0, YYAT_REDUCE, 3 },
		{ 72, 1, YYAT_DEFAULT, 482 },
		{ 71, 1, YYAT_DEFAULT, 482 },
		{ 69, 1, YYAT_DEFAULT, 482 },
		{ 68, 1, YYAT_DEFAULT, 482 },
		{ 66, 1, YYAT_DEFAULT, 482 },
		{ 63, 1, YYAT_DEFAULT, 482 },
		{ 60, 1, YYAT_DEFAULT, 482 },
		{ 58, 1, YYAT_DEFAULT, 482 },
		{ 0, 0, YYAT_REDUCE, 127 },
		{ 54, 1, YYAT_DEFAULT, 482 },
		{ 53, 1, YYAT_DEFAULT, 482 },
		{ 50, 1, YYAT_DEFAULT, 482 },
		{ 49, 1, YYAT_DEFAULT, 482 },
		{ 48, 1, YYAT_DEFAULT, 482 },
		{ 5, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 1 },
		{ 0, 0, YYAT_REDUCE, 4 },
		{ 0, 0, YYAT_REDUCE, 5 },
		{ 0, 0, YYAT_REDUCE, 6 },
		{ 0, 0, YYAT_REDUCE, 7 },
		{ 0, 0, YYAT_REDUCE, 8 },
		{ 0, 0, YYAT_REDUCE, 9 },
		{ 0, 0, YYAT_REDUCE, 40 },
		{ 0, 0, YYAT_REDUCE, 41 },
		{ 0, 0, YYAT_REDUCE, 42 },
		{ 0, 0, YYAT_REDUCE, 43 },
		{ 0, 0, YYAT_REDUCE, 44 },
		{ 0, 0, YYAT_REDUCE, 48 },
		{ 0, 0, YYAT_REDUCE, 49 },
		{ 0, 0, YYAT_REDUCE, 50 },
		{ 0, 0, YYAT_REDUCE, 51 },
		{ 0, 0, YYAT_REDUCE, 52 },
		{ 0, 0, YYAT_REDUCE, 53 },
		{ 0, 0, YYAT_REDUCE, 54 },
		{ 0, 0, YYAT_REDUCE, 55 },
		{ 0, 0, YYAT_REDUCE, 124 },
		{ 0, 0, YYAT_REDUCE, 125 },
		{ 0, 0, YYAT_REDUCE, 126 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ -511, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ -318, 1, YYAT_ERROR, 0 },
		{ -216, 1, YYAT_REDUCE, 46 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 43, 1, YYAT_DEFAULT, 482 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_REDUCE, 64 },
		{ -158, 1, YYAT_ERROR, 0 },
		{ -355, 1, YYAT_ERROR, 0 },
		{ -82, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 2 },
		{ 37, 1, YYAT_DEFAULT, 76 },
		{ 0, 0, YYAT_REDUCE, 206 },
		{ 34, 1, YYAT_DEFAULT, 76 },
		{ 0, 0, YYAT_REDUCE, 201 },
		{ 0, 0, YYAT_REDUCE, 208 },
		{ 25, 1, YYAT_DEFAULT, 76 },
		{ 22, 1, YYAT_DEFAULT, 76 },
		{ 0, 0, YYAT_REDUCE, 209 },
		{ 0, 0, YYAT_REDUCE, 212 },
		{ 0, 0, YYAT_REDUCE, 215 },
		{ 0, 0, YYAT_REDUCE, 210 },
		{ 0, 0, YYAT_REDUCE, 213 },
		{ 0, 0, YYAT_REDUCE, 211 },
		{ 0, 0, YYAT_REDUCE, 214 },
		{ 21, 1, YYAT_DEFAULT, 76 },
		{ 19, 1, YYAT_DEFAULT, 76 },
		{ 15, 1, YYAT_DEFAULT, 76 },
		{ 0, 0, YYAT_REDUCE, 207 },
		{ 11, 1, YYAT_DEFAULT, 76 },
		{ 7, 1, YYAT_DEFAULT, 76 },
		{ 4, 1, YYAT_DEFAULT, 76 },
		{ 2, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 256 },
		{ 0, 0, YYAT_REDUCE, 257 },
		{ 0, 0, YYAT_REDUCE, 258 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 156 },
		{ 133, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 260 },
		{ 0, 0, YYAT_REDUCE, 261 },
		{ 0, 0, YYAT_REDUCE, 259 },
		{ -50, 1, YYAT_DEFAULT, 157 },
		{ 0, 0, YYAT_REDUCE, 235 },
		{ 0, 0, YYAT_REDUCE, 203 },
		{ 0, 0, YYAT_REDUCE, 204 },
		{ 41, 1, YYAT_DEFAULT, 498 },
		{ 0, 0, YYAT_REDUCE, 247 },
		{ 0, 0, YYAT_REDUCE, 249 },
		{ 0, 0, YYAT_REDUCE, 248 },
		{ 47, 1, YYAT_REDUCE, 236 },
		{ 0, 0, YYAT_REDUCE, 250 },
		{ 0, 0, YYAT_REDUCE, 26 },
		{ 0, 0, YYAT_REDUCE, 25 },
		{ 0, 0, YYAT_REDUCE, 28 },
		{ 0, 0, YYAT_REDUCE, 27 },
		{ -53, 1, YYAT_DEFAULT, 183 },
		{ 35, 1, YYAT_DEFAULT, 498 },
		{ 33, 1, YYAT_DEFAULT, 498 },
		{ 0, 0, YYAT_REDUCE, 119 },
		{ 0, 0, YYAT_REDUCE, 123 },
		{ 0, 0, YYAT_REDUCE, 122 },
		{ 0, 0, YYAT_REDUCE, 121 },
		{ 0, 0, YYAT_REDUCE, 120 },
		{ 0, 0, YYAT_DEFAULT, 400 },
		{ -60, 1, YYAT_DEFAULT, 503 },
		{ -352, 1, YYAT_DEFAULT, 498 },
		{ 30, 1, YYAT_DEFAULT, 498 },
		{ -342, 1, YYAT_REDUCE, 129 },
		{ 26, 1, YYAT_DEFAULT, 498 },
		{ -130, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 75 },
		{ 0, 0, YYAT_REDUCE, 76 },
		{ 0, 0, YYAT_REDUCE, 77 },
		{ 0, 0, YYAT_REDUCE, 78 },
		{ 0, 0, YYAT_REDUCE, 79 },
		{ 0, 0, YYAT_REDUCE, 80 },
		{ 0, 0, YYAT_REDUCE, 81 },
		{ 0, 0, YYAT_REDUCE, 82 },
		{ 0, 0, YYAT_REDUCE, 83 },
		{ 0, 0, YYAT_REDUCE, 84 },
		{ 0, 0, YYAT_REDUCE, 85 },
		{ 0, 0, YYAT_REDUCE, 86 },
		{ 0, 0, YYAT_REDUCE, 87 },
		{ 0, 0, YYAT_REDUCE, 88 },
		{ 0, 0, YYAT_REDUCE, 89 },
		{ 0, 0, YYAT_REDUCE, 90 },
		{ 0, 0, YYAT_REDUCE, 91 },
		{ 0, 0, YYAT_REDUCE, 92 },
		{ -336, 1, YYAT_DEFAULT, 400 },
		{ 0, 0, YYAT_REDUCE, 13 },
		{ -460, 1, YYAT_REDUCE, 15 },
		{ -69, 1, YYAT_DEFAULT, 503 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ -236, 1, YYAT_DEFAULT, 237 },
		{ 0, 0, YYAT_REDUCE, 246 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ -72, 1, YYAT_DEFAULT, 239 },
		{ 18, 1, YYAT_DEFAULT, 498 },
		{ -35, 1, YYAT_DEFAULT, 370 },
		{ 43, 1, YYAT_DEFAULT, 239 },
		{ 0, 0, YYAT_REDUCE, 234 },
		{ 18, 1, YYAT_REDUCE, 223 },
		{ -85, 1, YYAT_DEFAULT, 489 },
		{ 33, 1, YYAT_DEFAULT, 489 },
		{ 0, 0, YYAT_REDUCE, 202 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ -233, 1, YYAT_DEFAULT, 503 },
		{ 0, 0, YYAT_REDUCE, 21 },
		{ 0, 0, YYAT_REDUCE, 23 },
		{ 0, 0, YYAT_REDUCE, 24 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_REDUCE, 279 },
		{ 0, 0, YYAT_REDUCE, 111 },
		{ 0, 0, YYAT_REDUCE, 45 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ -38, 1, YYAT_DEFAULT, 482 },
		{ -52, 1, YYAT_DEFAULT, 482 },
		{ -57, 1, YYAT_DEFAULT, 482 },
		{ -58, 1, YYAT_DEFAULT, 482 },
		{ 0, 0, YYAT_REDUCE, 134 },
		{ 0, 0, YYAT_REDUCE, 135 },
		{ 0, 0, YYAT_REDUCE, 136 },
		{ -358, 1, YYAT_DEFAULT, 430 },
		{ 0, 0, YYAT_REDUCE, 130 },
		{ 0, 0, YYAT_REDUCE, 132 },
		{ 0, 0, YYAT_REDUCE, 133 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 400 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 400 },
		{ 0, 0, YYAT_REDUCE, 72 },
		{ 0, 0, YYAT_REDUCE, 73 },
		{ -288, 1, YYAT_DEFAULT, 501 },
		{ 0, 0, YYAT_REDUCE, 69 },
		{ 0, 0, YYAT_REDUCE, 71 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ -466, 1, YYAT_REDUCE, 14 },
		{ 0, 0, YYAT_REDUCE, 16 },
		{ 0, 0, YYAT_REDUCE, 12 },
		{ 0, 0, YYAT_REDUCE, 193 },
		{ -352, 1, YYAT_ERROR, 0 },
		{ -111, 1, YYAT_DEFAULT, 489 },
		{ -123, 1, YYAT_DEFAULT, 489 },
		{ -124, 1, YYAT_DEFAULT, 489 },
		{ -138, 1, YYAT_DEFAULT, 489 },
		{ -139, 1, YYAT_DEFAULT, 489 },
		{ -142, 1, YYAT_DEFAULT, 489 },
		{ -146, 1, YYAT_DEFAULT, 489 },
		{ -57, 1, YYAT_DEFAULT, 498 },
		{ -58, 1, YYAT_DEFAULT, 498 },
		{ -151, 1, YYAT_DEFAULT, 489 },
		{ -60, 1, YYAT_DEFAULT, 498 },
		{ -249, 1, YYAT_REDUCE, 200 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ -14, 1, YYAT_REDUCE, 194 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ -73, 1, YYAT_DEFAULT, 500 },
		{ 0, 0, YYAT_REDUCE, 195 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ 0, 0, YYAT_DEFAULT, 410 },
		{ 0, 0, YYAT_REDUCE, 205 },
		{ 0, 0, YYAT_REDUCE, 237 },
		{ -336, 1, YYAT_DEFAULT, 331 },
		{ -344, 1, YYAT_REDUCE, 241 },
		{ -381, 1, YYAT_DEFAULT, 332 },
		{ -393, 1, YYAT_REDUCE, 239 },
		{ 0, 0, YYAT_REDUCE, 199 },
		{ 0, 0, YYAT_REDUCE, 245 },
		{ 0, 0, YYAT_REDUCE, 198 },
		{ 0, 0, YYAT_REDUCE, 243 },
		{ 0, 0, YYAT_REDUCE, 58 },
		{ -113, 1, YYAT_ERROR, 0 },
		{ -401, 1, YYAT_REDUCE, 240 },
		{ -419, 1, YYAT_REDUCE, 238 },
		{ 0, 0, YYAT_REDUCE, 244 },
		{ 0, 0, YYAT_REDUCE, 242 },
		{ 0, 0, YYAT_REDUCE, 32 },
		{ 0, 0, YYAT_REDUCE, 29 },
		{ 0, 0, YYAT_REDUCE, 33 },
		{ 0, 0, YYAT_REDUCE, 30 },
		{ 0, 0, YYAT_REDUCE, 38 },
		{ 0, 0, YYAT_REDUCE, 31 },
		{ -64, 1, YYAT_DEFAULT, 498 },
		{ 0, 0, YYAT_REDUCE, 34 },
		{ 0, 0, YYAT_REDUCE, 35 },
		{ 0, 0, YYAT_REDUCE, 36 },
		{ -68, 1, YYAT_DEFAULT, 498 },
		{ 0, 0, YYAT_REDUCE, 20 },
		{ 0, 0, YYAT_REDUCE, 22 },
		{ -70, 1, YYAT_DEFAULT, 498 },
		{ -71, 1, YYAT_DEFAULT, 498 },
		{ -129, 1, YYAT_REDUCE, 114 },
		{ 0, 0, YYAT_REDUCE, 101 },
		{ 0, 0, YYAT_REDUCE, 99 },
		{ 0, 0, YYAT_REDUCE, 56 },
		{ -183, 1, YYAT_REDUCE, 158 },
		{ -257, 1, YYAT_REDUCE, 141 },
		{ -163, 1, YYAT_DEFAULT, 388 },
		{ -170, 1, YYAT_DEFAULT, 393 },
		{ 0, 0, YYAT_REDUCE, 128 },
		{ 0, 0, YYAT_REDUCE, 131 },
		{ -80, 1, YYAT_DEFAULT, 498 },
		{ 0, 0, YYAT_REDUCE, 65 },
		{ -85, 1, YYAT_DEFAULT, 498 },
		{ 0, 0, YYAT_REDUCE, 96 },
		{ 0, 0, YYAT_REDUCE, 93 },
		{ 0, 0, YYAT_REDUCE, 95 },
		{ 0, 0, YYAT_REDUCE, 94 },
		{ 0, 0, YYAT_REDUCE, 74 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ -140, 1, YYAT_DEFAULT, 482 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ -190, 1, YYAT_DEFAULT, 511 },
		{ 0, 0, YYAT_REDUCE, 70 },
		{ 0, 0, YYAT_REDUCE, 104 },
		{ 0, 0, YYAT_REDUCE, 107 },
		{ 0, 0, YYAT_REDUCE, 108 },
		{ -373, 1, YYAT_REDUCE, 110 },
		{ 0, 0, YYAT_REDUCE, 176 },
		{ 0, 0, YYAT_REDUCE, 18 },
		{ 0, 0, YYAT_REDUCE, 19 },
		{ 0, 0, YYAT_REDUCE, 17 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_REDUCE, 216 },
		{ 0, 0, YYAT_REDUCE, 219 },
		{ 0, 0, YYAT_REDUCE, 222 },
		{ 0, 0, YYAT_REDUCE, 220 },
		{ 0, 0, YYAT_REDUCE, 217 },
		{ 0, 0, YYAT_REDUCE, 218 },
		{ 0, 0, YYAT_REDUCE, 221 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_REDUCE, 255 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ -440, 1, YYAT_REDUCE, 197 },
		{ -441, 1, YYAT_REDUCE, 196 },
		{ 0, 0, YYAT_REDUCE, 199 },
		{ 0, 0, YYAT_REDUCE, 198 },
		{ -100, 1, YYAT_DEFAULT, 498 },
		{ 0, 0, YYAT_REDUCE, 225 },
		{ -233, 1, YYAT_REDUCE, 227 },
		{ -294, 1, YYAT_REDUCE, 226 },
		{ 87, 1, YYAT_REDUCE, 233 },
		{ 63, 1, YYAT_REDUCE, 228 },
		{ -99, 1, YYAT_ERROR, 0 },
		{ 56, 1, YYAT_REDUCE, 229 },
		{ 53, 1, YYAT_REDUCE, 232 },
		{ 47, 1, YYAT_REDUCE, 231 },
		{ -99, 1, YYAT_REDUCE, 230 },
		{ 0, 0, YYAT_DEFAULT, 501 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 370 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_REDUCE, 115 },
		{ -73, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 501 },
		{ 0, 0, YYAT_DEFAULT, 501 },
		{ 0, 0, YYAT_DEFAULT, 501 },
		{ -182, 1, YYAT_DEFAULT, 514 },
		{ -187, 1, YYAT_DEFAULT, 514 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ -188, 1, YYAT_DEFAULT, 514 },
		{ -189, 1, YYAT_DEFAULT, 514 },
		{ -210, 1, YYAT_DEFAULT, 503 },
		{ -258, 1, YYAT_DEFAULT, 503 },
		{ 0, 0, YYAT_REDUCE, 159 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ -112, 1, YYAT_DEFAULT, 505 },
		{ -89, 1, YYAT_DEFAULT, 440 },
		{ 0, 0, YYAT_DEFAULT, 440 },
		{ 0, 0, YYAT_REDUCE, 155 },
		{ 0, 0, YYAT_REDUCE, 153 },
		{ 0, 0, YYAT_REDUCE, 154 },
		{ 0, 0, YYAT_REDUCE, 270 },
		{ 0, 0, YYAT_REDUCE, 142 },
		{ -215, 1, YYAT_DEFAULT, 503 },
		{ -122, 1, YYAT_REDUCE, 144 },
		{ 0, 0, YYAT_REDUCE, 143 },
		{ 0, 0, YYAT_REDUCE, 263 },
		{ 201, 1, YYAT_REDUCE, 271 },
		{ 41, 1, YYAT_REDUCE, 268 },
		{ 0, 0, YYAT_REDUCE, 272 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ -346, 1, YYAT_DEFAULT, 503 },
		{ 0, 0, YYAT_REDUCE, 182 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ -438, 1, YYAT_DEFAULT, 503 },
		{ 0, 0, YYAT_REDUCE, 188 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 400 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_REDUCE, 178 },
		{ 0, 0, YYAT_REDUCE, 179 },
		{ -240, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 180 },
		{ 0, 0, YYAT_REDUCE, 68 },
		{ 0, 0, YYAT_REDUCE, 105 },
		{ 0, 0, YYAT_REDUCE, 177 },
		{ -223, 1, YYAT_DEFAULT, 503 },
		{ -145, 1, YYAT_DEFAULT, 498 },
		{ -257, 1, YYAT_DEFAULT, 489 },
		{ -258, 1, YYAT_DEFAULT, 489 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ -234, 1, YYAT_DEFAULT, 505 },
		{ -282, 1, YYAT_DEFAULT, 511 },
		{ 0, 0, YYAT_REDUCE, 37 },
		{ 0, 0, YYAT_REDUCE, 39 },
		{ -192, 1, YYAT_DEFAULT, 498 },
		{ 0, 0, YYAT_REDUCE, 60 },
		{ 0, 0, YYAT_DEFAULT, 514 },
		{ -294, 1, YYAT_DEFAULT, 511 },
		{ -296, 1, YYAT_DEFAULT, 511 },
		{ -309, 1, YYAT_DEFAULT, 511 },
		{ 0, 0, YYAT_REDUCE, 161 },
		{ 0, 0, YYAT_DEFAULT, 430 },
		{ 0, 0, YYAT_REDUCE, 162 },
		{ 0, 0, YYAT_DEFAULT, 430 },
		{ 0, 0, YYAT_REDUCE, 174 },
		{ 0, 0, YYAT_REDUCE, 173 },
		{ 0, 0, YYAT_REDUCE, 163 },
		{ 0, 0, YYAT_DEFAULT, 430 },
		{ -1, 1, YYAT_REDUCE, 175 },
		{ 0, 0, YYAT_REDUCE, 164 },
		{ -293, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 156 },
		{ 0, 0, YYAT_REDUCE, 157 },
		{ 0, 0, YYAT_REDUCE, 160 },
		{ 0, 0, YYAT_REDUCE, 275 },
		{ 0, 0, YYAT_REDUCE, 277 },
		{ 0, 0, YYAT_REDUCE, 278 },
		{ 0, 0, YYAT_REDUCE, 276 },
		{ 0, 0, YYAT_REDUCE, 274 },
		{ 0, 0, YYAT_REDUCE, 269 },
		{ -285, 1, YYAT_DEFAULT, 514 },
		{ 0, 0, YYAT_REDUCE, 264 },
		{ 0, 0, YYAT_REDUCE, 265 },
		{ 0, 0, YYAT_REDUCE, 139 },
		{ 0, 0, YYAT_REDUCE, 148 },
		{ -308, 1, YYAT_DEFAULT, 503 },
		{ 0, 0, YYAT_REDUCE, 145 },
		{ 0, 0, YYAT_REDUCE, 147 },
		{ -50, 1, YYAT_REDUCE, 267 },
		{ 0, 0, YYAT_REDUCE, 273 },
		{ 0, 0, YYAT_REDUCE, 184 },
		{ 0, 0, YYAT_REDUCE, 185 },
		{ 0, 0, YYAT_REDUCE, 186 },
		{ 0, 0, YYAT_REDUCE, 181 },
		{ 0, 0, YYAT_REDUCE, 183 },
		{ 0, 0, YYAT_REDUCE, 190 },
		{ 0, 0, YYAT_REDUCE, 191 },
		{ 0, 0, YYAT_REDUCE, 192 },
		{ 0, 0, YYAT_REDUCE, 187 },
		{ 0, 0, YYAT_REDUCE, 189 },
		{ 0, 0, YYAT_REDUCE, 97 },
		{ 0, 0, YYAT_REDUCE, 66 },
		{ -228, 1, YYAT_DEFAULT, 498 },
		{ -324, 1, YYAT_DEFAULT, 503 },
		{ 0, 0, YYAT_REDUCE, 11 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_REDUCE, 253 },
		{ 0, 0, YYAT_REDUCE, 254 },
		{ -326, 1, YYAT_DEFAULT, 498 },
		{ 0, 0, YYAT_REDUCE, 224 },
		{ 0, 0, YYAT_REDUCE, 59 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_DEFAULT, 501 },
		{ 0, 0, YYAT_REDUCE, 112 },
		{ 0, 0, YYAT_REDUCE, 102 },
		{ 0, 0, YYAT_REDUCE, 100 },
		{ 0, 0, YYAT_REDUCE, 57 },
		{ 0, 0, YYAT_REDUCE, 166 },
		{ 0, 0, YYAT_REDUCE, 168 },
		{ 0, 0, YYAT_REDUCE, 170 },
		{ 0, 0, YYAT_REDUCE, 172 },
		{ 0, 0, YYAT_REDUCE, 266 },
		{ -296, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 140 },
		{ 0, 0, YYAT_REDUCE, 146 },
		{ 0, 0, YYAT_DEFAULT, 501 },
		{ 0, 0, YYAT_DEFAULT, 501 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_REDUCE, 109 },
		{ -345, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_DEFAULT, 505 },
		{ 0, 0, YYAT_REDUCE, 251 },
		{ 0, 0, YYAT_REDUCE, 62 },
		{ -360, 1, YYAT_DEFAULT, 511 },
		{ 0, 0, YYAT_REDUCE, 118 },
		{ -369, 1, YYAT_DEFAULT, 506 },
		{ -372, 1, YYAT_DEFAULT, 511 },
		{ -373, 1, YYAT_DEFAULT, 511 },
		{ -300, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 252 },
		{ -404, 1, YYAT_ERROR, 0 },
		{ -242, 1, YYAT_REDUCE, 103 },
		{ 0, 0, YYAT_REDUCE, 61 },
		{ -424, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 116 },
		{ 44, 1, YYAT_DEFAULT, 83 },
		{ -365, 1, YYAT_DEFAULT, 503 },
		{ 0, 0, YYAT_REDUCE, 150 },
		{ 0, 0, YYAT_REDUCE, 98 },
		{ 0, 0, YYAT_REDUCE, 67 },
		{ 0, 0, YYAT_REDUCE, 262 },
		{ -224, 1, YYAT_DEFAULT, 503 },
		{ 0, 0, YYAT_REDUCE, 113 },
		{ 0, 0, YYAT_REDUCE, 117 },
		{ -193, 1, YYAT_DEFAULT, 382 },
		{ 0, 0, YYAT_REDUCE, 149 },
		{ 0, 0, YYAT_REDUCE, 151 },
		{ 0, 0, YYAT_REDUCE, 63 },
		{ -435, 1, YYAT_ERROR, 0 },
		{ 0, 0, YYAT_REDUCE, 152 }
	};
	yystateaction = stateaction;

	static const yynontermgoto_t YYNEARFAR YYBASED_CODE nontermgoto[] = {
		{ 45, 110 },
		{ 45, 27 },
		{ 45, 26 },
		{ 45, 24 },
		{ 45, 25 },
		{ 45, 31 },
		{ 287, 352 },
		{ 45, 29 },
		{ 166, 264 },
		{ 45, 33 },
		{ 506, 516 },
		{ 45, 34 },
		{ 503, 513 },
		{ 45, 35 },
		{ 166, 265 },
		{ 292, 378 },
		{ 292, 379 },
		{ 45, 30 },
		{ 16, 54 },
		{ 16, 18 },
		{ 16, 22 },
		{ 16, 23 },
		{ 45, 32 },
		{ 292, 380 },
		{ 45, 36 },
		{ 16, 19 },
		{ 514, 88 },
		{ 514, 87 },
		{ 511, 403 },
		{ 45, 28 },
		{ 356, 421 },
		{ 16, 20 },
		{ 514, 376 },
		{ 514, 95 },
		{ 514, 92 },
		{ 514, 94 },
		{ 514, 93 },
		{ 514, 96 },
		{ 514, 518 },
		{ 514, 381 },
		{ 514, 382 },
		{ 514, 383 },
		{ 514, 384 },
		{ 134, 216 },
		{ 134, 217 },
		{ 216, 310 },
		{ 134, 218 },
		{ 216, 218 },
		{ 287, 351 },
		{ 492, 501 },
		{ 357, 423 },
		{ 490, 500 },
		{ 292, 377 },
		{ 216, 309 },
		{ 202, 296 },
		{ 356, 420 },
		{ 165, 262 },
		{ 202, 204 },
		{ 360, 427 },
		{ 511, 314 },
		{ 511, 315 },
		{ 511, 312 },
		{ 165, 263 },
		{ 487, 498 },
		{ 511, 313 },
		{ 164, 260 },
		{ 202, 205 },
		{ 16, 21 },
		{ 16, 37 },
		{ 361, 430 },
		{ 486, 497 },
		{ 164, 261 },
		{ 16, 38 },
		{ 16, 39 },
		{ 357, 422 },
		{ 202, 200 },
		{ 370, 439 },
		{ 255, 158 },
		{ 202, 201 },
		{ 361, 428 },
		{ 485, 496 },
		{ 360, 426 },
		{ 255, 345 },
		{ 370, -1 },
		{ 370, -1 },
		{ 370, -1 },
		{ 370, -1 },
		{ 473, 494 },
		{ 156, 158 },
		{ 156, 157 },
		{ 472, 493 },
		{ 361, 429 },
		{ 156, 160 },
		{ 156, 245 },
		{ 163, 258 },
		{ 156, 161 },
		{ 171, -1 },
		{ 171, 267 },
		{ 471, 492 },
		{ 202, 199 },
		{ 163, 259 },
		{ 465, 489 },
		{ 171, -1 },
		{ 171, 271 },
		{ 134, 214 },
		{ 216, 214 },
		{ 505, 514 },
		{ 505, 154 },
		{ 505, 90 },
		{ 505, 89 },
		{ 134, 215 },
		{ 216, 215 },
		{ 238, 239 },
		{ 80, 150 },
		{ 461, 486 },
		{ 238, 160 },
		{ 238, 245 },
		{ 460, 485 },
		{ 183, 284 },
		{ 80, 151 },
		{ 183, 185 },
		{ 183, 186 },
		{ 291, 362 },
		{ 291, 363 },
		{ 291, 364 },
		{ 501, 511 },
		{ 501, 311 },
		{ 495, 506 },
		{ 495, 507 },
		{ 494, 503 },
		{ 494, 504 },
		{ 445, 484 },
		{ 445, 447 },
		{ 440, -1 },
		{ 440, 481 },
		{ 410, 469 },
		{ 410, 159 },
		{ 387, 452 },
		{ 387, 224 },
		{ 382, 448 },
		{ 382, 384 },
		{ 379, 445 },
		{ 379, 446 },
		{ 294, 393 },
		{ 294, 394 },
		{ 293, 388 },
		{ 293, 389 },
		{ 243, -1 },
		{ 243, 334 },
		{ 136, 221 },
		{ 136, 222 },
		{ 113, 202 },
		{ 113, 203 },
		{ 101, 183 },
		{ 101, 184 },
		{ 0, 16 },
		{ 0, 17 },
		{ 448, 449 },
		{ 444, 482 },
		{ 430, 480 },
		{ 427, 479 },
		{ 423, 478 },
		{ 421, 477 },
		{ 416, 473 },
		{ 415, 472 },
		{ 409, 468 },
		{ 400, 463 },
		{ 397, 462 },
		{ 396, 461 },
		{ 395, 460 },
		{ 393, 459 },
		{ 392, 457 },
		{ 391, 456 },
		{ 390, 455 },
		{ 388, 454 },
		{ 386, 451 },
		{ 385, 450 },
		{ 372, 442 },
		{ 371, 441 },
		{ 369, 438 },
		{ 368, 437 },
		{ 367, 436 },
		{ 366, 435 },
		{ 365, 434 },
		{ 363, 433 },
		{ 359, 425 },
		{ 358, 424 },
		{ 355, 419 },
		{ 354, 418 },
		{ 353, 417 },
		{ 350, 415 },
		{ 349, 414 },
		{ 348, 413 },
		{ 347, 412 },
		{ 346, 411 },
		{ 330, 408 },
		{ 328, 407 },
		{ 327, 406 },
		{ 319, 405 },
		{ 314, 404 },
		{ 308, 401 },
		{ 306, 399 },
		{ 305, 398 },
		{ 298, 396 },
		{ 290, 355 },
		{ 289, 354 },
		{ 288, 353 },
		{ 266, 346 },
		{ 254, 344 },
		{ 253, 343 },
		{ 252, 342 },
		{ 251, 341 },
		{ 250, 340 },
		{ 249, 339 },
		{ 248, 338 },
		{ 247, 337 },
		{ 244, 335 },
		{ 242, 333 },
		{ 241, 332 },
		{ 240, 331 },
		{ 221, 318 },
		{ 220, 317 },
		{ 219, 316 },
		{ 213, 304 },
		{ 212, 303 },
		{ 211, 302 },
		{ 210, 301 },
		{ 209, 300 },
		{ 208, 299 },
		{ 207, 298 },
		{ 206, 297 },
		{ 194, 290 },
		{ 193, 289 },
		{ 192, 288 },
		{ 190, 287 },
		{ 188, 286 },
		{ 187, 285 },
		{ 182, 282 },
		{ 181, 281 },
		{ 180, 280 },
		{ 179, 279 },
		{ 178, 278 },
		{ 177, 277 },
		{ 176, 276 },
		{ 175, 275 },
		{ 174, 274 },
		{ 173, 273 },
		{ 172, 272 },
		{ 170, 270 },
		{ 169, 269 },
		{ 168, 268 },
		{ 167, 266 },
		{ 153, 159 },
		{ 152, 237 },
		{ 149, 236 },
		{ 148, 235 },
		{ 147, 234 },
		{ 146, 233 },
		{ 145, 232 },
		{ 144, 231 },
		{ 143, 230 },
		{ 142, 229 },
		{ 141, 228 },
		{ 140, 227 },
		{ 139, 226 },
		{ 138, 225 },
		{ 109, 190 },
		{ 82, 159 },
		{ 81, 155 },
		{ 52, 137 },
		{ 51, 134 },
		{ 50, 115 },
		{ 49, 114 },
		{ 47, 112 },
		{ 46, 111 },
		{ 44, 109 },
		{ 43, 103 },
		{ 42, 102 },
		{ 41, 101 },
		{ 40, 91 },
		{ 10, 48 }
	};
	yynontermgoto = nontermgoto;
	yynontermgoto_size = 281;

	static const yystategoto_t YYNEARFAR YYBASED_CODE stategoto[] = {
		{ 154, 16 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 227, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 16, 45 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 190, 370 },
		{ 266, -1 },
		{ 188, 370 },
		{ 187, 370 },
		{ 225, -1 },
		{ -15, -1 },
		{ 185, 370 },
		{ 184, 370 },
		{ 0, -1 },
		{ 183, 370 },
		{ 242, -1 },
		{ 235, -1 },
		{ 263, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 29, 171 },
		{ 185, 505 },
		{ 179, 156 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 143, 183 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 166, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 97, 202 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 10, -1 },
		{ 0, -1 },
		{ 142, -1 },
		{ 0, -1 },
		{ 183, 387 },
		{ 181, 505 },
		{ 180, 505 },
		{ 179, 505 },
		{ 178, 505 },
		{ 177, 505 },
		{ 176, 505 },
		{ 175, 505 },
		{ 168, 370 },
		{ 167, 370 },
		{ 166, 370 },
		{ 165, 370 },
		{ 0, -1 },
		{ 0, -1 },
		{ 169, 243 },
		{ 164, 238 },
		{ 0, -1 },
		{ 0, -1 },
		{ 5, 171 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 10, 171 },
		{ -19, 171 },
		{ -28, 171 },
		{ -76, 171 },
		{ 162, 370 },
		{ 160, 171 },
		{ 159, 171 },
		{ 158, 171 },
		{ 13, 370 },
		{ 158, 370 },
		{ 157, 370 },
		{ 156, 370 },
		{ 155, 370 },
		{ 154, 370 },
		{ 153, 370 },
		{ 158, 505 },
		{ 157, 505 },
		{ 156, 505 },
		{ 155, 505 },
		{ 154, 505 },
		{ 107, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 153, 505 },
		{ 146, 370 },
		{ 0, -1 },
		{ 189, -1 },
		{ 0, -1 },
		{ 144, 370 },
		{ 149, 505 },
		{ 148, 505 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ -1, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 147, 505 },
		{ 129, -1 },
		{ 145, 505 },
		{ 144, 505 },
		{ 144, 387 },
		{ 142, 505 },
		{ 141, 505 },
		{ 123, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 11, 501 },
		{ 0, -1 },
		{ 0, -1 },
		{ 139, 505 },
		{ 139, 387 },
		{ 212, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 28, 410 },
		{ 0, -1 },
		{ 135, 243 },
		{ 134, 243 },
		{ 133, 243 },
		{ 64, 505 },
		{ 133, 505 },
		{ 0, -1 },
		{ 0, -1 },
		{ 127, 255 },
		{ 126, 255 },
		{ 125, 255 },
		{ 124, 255 },
		{ 124, 410 },
		{ 122, 255 },
		{ 121, 255 },
		{ 120, 255 },
		{ -6, 505 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 184, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ -41, 370 },
		{ 165, -1 },
		{ 165, -1 },
		{ 183, -1 },
		{ 55, -1 },
		{ -43, 514 },
		{ 68, -1 },
		{ 63, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 173, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 113, 370 },
		{ 112, 370 },
		{ 0, -1 },
		{ 111, 370 },
		{ 0, 511 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 124, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 116, 387 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 108, 370 },
		{ 107, 370 },
		{ 0, -1 },
		{ 106, 370 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 152, 501 },
		{ 110, 505 },
		{ 109, 505 },
		{ 102, 370 },
		{ 107, 505 },
		{ 0, -1 },
		{ 0, -1 },
		{ 147, 501 },
		{ 146, 501 },
		{ 145, 501 },
		{ -40, 514 },
		{ -21, 514 },
		{ 103, 505 },
		{ 102, 505 },
		{ -14, 514 },
		{ -4, 514 },
		{ 0, -1 },
		{ 115, -1 },
		{ 0, -1 },
		{ 100, 505 },
		{ 99, 505 },
		{ 98, 505 },
		{ 97, 505 },
		{ 96, 505 },
		{ -13, 440 },
		{ 82, 440 },
		{ 81, 440 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 81, 445 },
		{ 0, -1 },
		{ 0, -1 },
		{ 41, -1 },
		{ 0, 448 },
		{ 0, -1 },
		{ 93, 505 },
		{ 92, 505 },
		{ 55, 505 },
		{ 96, -1 },
		{ 0, -1 },
		{ 90, 505 },
		{ 89, 505 },
		{ 88, 505 },
		{ 89, -1 },
		{ 0, -1 },
		{ 86, 505 },
		{ 68, -1 },
		{ 84, 505 },
		{ 0, -1 },
		{ 0, -1 },
		{ 66, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 82, 505 },
		{ 48, 255 },
		{ 0, 511 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 139, -1 },
		{ 68, 514 },
		{ 0, 511 },
		{ 0, 511 },
		{ 0, 511 },
		{ 0, -1 },
		{ 104, -1 },
		{ 0, -1 },
		{ 103, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 102, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 101, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 38, 514 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 95, -1 },
		{ 70, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 58, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 79, -1 },
		{ 83, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 18, 505 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 15, 505 },
		{ 48, 501 },
		{ 41, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 38, 501 },
		{ 28, 501 },
		{ -20, 505 },
		{ 0, -1 },
		{ 0, -1 },
		{ -32, 505 },
		{ 0, -1 },
		{ 22, -1 },
		{ 0, 511 },
		{ 81, -1 },
		{ 63, -1 },
		{ 0, 511 },
		{ 0, 511 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 83, 511 },
		{ 0, -1 },
		{ -37, -1 },
		{ 0, -1 },
		{ 23, -1 },
		{ -55, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ -15, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ -57, 505 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 },
		{ 0, -1 }
	};
	yystategoto = stategoto;

	yydestructorptr = NULL;

	yytokendestptr = NULL;
	yytokendest_size = 0;
	yytokendestbase = 0;
}
