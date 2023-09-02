//***********************************************************************************
//* CLASSE FRONTALE DE GESTION DE LA FRACTALE
//* Mots clés : automate, frontal, fractale

/////Etat classe : EN COURS
#pragma warning(disable : 4786)

#ifndef _FRONTALFRACTAL
#define _FRONTALFRACTAL
#undef min
#undef max
#include "Fractal.h"
#include "FractalZ2.h"
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

#include <map>
#include <string>


typedef enum
{
	ALGEBRA_QUATERNION=0,
	ALGEBRA_HYPERCOMPLEX,
	ALGEBRA_EXOTIQUE01,
	ALGEBRA_EXOTIQUE02,
	ALGEBRA_EXOTIQUE03,
	ALGEBRA_EXOTIQUE04,
	ALGEBRA_EXOTIQUE05,
	ALGEBRA_EXOTIQUE06,
	ALGEBRA_EXOTIQUE07,
	ALGEBRA_EXOTIQUE08,
	ALGEBRA_EXOTIQUE09,
	ALGEBRA_EXOTIQUE10,
	ALGEBRA_EXOTIQUE11,
	ALGEBRA_EXOTIQUE12,
	ALGEBRA_EXOTIQUE13,
	ALGEBRA_EXOTIQUE14,
	ALGEBRA_EXOTIQUE15,
	ALGEBRA_EXOTIQUE16,

} ENUM_ALGEBRATYPE;

typedef enum
{
	FRACTAL_GENERIC=0,
	FRACTAL_Z2
} ENUM_FRACTALTYPE;

typedef std::map<std::string, ENUM_FRACTALTYPE, std::less<std::string>, std::allocator<ENUM_FRACTALTYPE> >	FRACTALTYPE; 

typedef std::map<std::string, ENUM_ALGEBRATYPE, std::less<std::string>, std::allocator<ENUM_ALGEBRATYPE> >	ALGEBRATYPE; 

class CFrontalFractal
{
// Construction
public:
	inline CFrontalFractal();

// Attributes
protected:
	CBaseFractal		*m_pFractal; 
	ALGEBRATYPE			m_AlgebralistType;
	FRACTALTYPE			m_FractallistType;

// Operations publiques
public:
	inline  void SetFractal(CBaseFractal*pFract,bool);
	inline  CBaseFractal* GetFractal() {return m_pFractal;};
	inline	CBaseVector<4,double>		GetInitValue() {return((m_pFractal==NULL)?CBaseVector<4,double>():m_pFractal->GetInitValue());}
	inline  long						GetMaxIter() {return((m_pFractal==NULL)?0:m_pFractal->GetMaxIter());};
	inline  double						GetNbStep()	 {return((m_pFractal==NULL)?0.0:m_pFractal->GetNbStep());}
	inline  double						GetAngle()	 {return((m_pFractal==NULL)?0.0:m_pFractal->GetAngleDeg());}
	inline  std::string					GetStrExpr() {return((m_pFractal==NULL)?"":m_pFractal->GetStrExpr());}
	inline  std::string					GetStrExprDerivate() {return((m_pFractal==NULL)?"":m_pFractal->GetStrExprDerivate());}
	inline  std::string					GetAlgebraType() {return((m_pFractal==NULL)?"":m_pFractal->GetAlgebraType());}
	inline  bool						GetOptimisation() {return((m_pFractal==NULL)?false:m_pFractal->GetOptimisation());}

	inline	void						SetInitValue(CBaseVector<4,double>&value) {if(m_pFractal!=NULL) m_pFractal->SetInitValue(value);}
	inline  void						SetMaxIter(long Iter)	 {if(m_pFractal!=NULL) m_pFractal->SetMaxIter(Iter);};
	inline  void						SetNbStep(double Step)	 {if(m_pFractal!=NULL) m_pFractal->SetNbStep(Step);}
	inline  void						SetStrExpr(const std::string&);
	inline  void						SetAngle(double Angle)	 {if(m_pFractal!=NULL) m_pFractal->SetAngleDeg(Angle);}

	inline int							ChangeType(const std::string &NewAlgebra,
												   const std::string &NewExpr, 
												   bool bOpt);
	inline int							ChangeType(	const std::string &NewAlgebra,
													const std::string &NewExpr,
													const std::string &NewExprDerive, 
													bool bOpt);
	inline CBaseFractal*				SelectAlgebra(ENUM_ALGEBRATYPE,ENUM_FRACTALTYPE,bool);

// Implementation
public:
	inline virtual ~CFrontalFractal();

};


CFrontalFractal::CFrontalFractal()
{
	//Remplissage des types
	m_AlgebralistType["quaternion"]=ALGEBRA_QUATERNION;
	m_AlgebralistType["hypercomplex"]=ALGEBRA_HYPERCOMPLEX;
	m_AlgebralistType["algebra01"]=ALGEBRA_EXOTIQUE01;
	m_AlgebralistType["algebra02"]=ALGEBRA_EXOTIQUE02;
	m_AlgebralistType["algebra03"]=ALGEBRA_EXOTIQUE03;
	m_AlgebralistType["algebra04"]=ALGEBRA_EXOTIQUE04;
	m_AlgebralistType["algebra05"]=ALGEBRA_EXOTIQUE05;
	m_AlgebralistType["algebra06"]=ALGEBRA_EXOTIQUE06;
	m_AlgebralistType["algebra07"]=ALGEBRA_EXOTIQUE07;
	m_AlgebralistType["algebra08"]=ALGEBRA_EXOTIQUE08;
	m_AlgebralistType["algebra09"]=ALGEBRA_EXOTIQUE09;
	m_AlgebralistType["algebra10"]=ALGEBRA_EXOTIQUE10;
	m_AlgebralistType["algebra11"]=ALGEBRA_EXOTIQUE11;
	m_AlgebralistType["algebra12"]=ALGEBRA_EXOTIQUE12;
	m_AlgebralistType["algebra13"]=ALGEBRA_EXOTIQUE13;
	m_AlgebralistType["algebra14"]=ALGEBRA_EXOTIQUE14;
	m_AlgebralistType["algebra15"]=ALGEBRA_EXOTIQUE15;
	m_AlgebralistType["algebra16"]=ALGEBRA_EXOTIQUE16;

	m_FractallistType["default"]=FRACTAL_GENERIC;
	m_FractallistType["Z^2+@init"]=FRACTAL_Z2;
	m_FractallistType["z^2+@init"]=FRACTAL_Z2;
	m_FractallistType["@init+Z^2"]=FRACTAL_Z2;
	m_FractallistType["@init+z^2"]=FRACTAL_Z2;
	//Camera par défaut
	m_pFractal=NULL;
}

CFrontalFractal::~CFrontalFractal()
{
}


void CFrontalFractal::SetStrExpr(const std::string &Expr)
{
	m_pFractal->SetStrExpr(Expr);
}

void CFrontalFractal::SetFractal(CBaseFractal*pFract,bool bEfface)
{
	if(m_pFractal!=NULL && bEfface)
	{
		delete m_pFractal;
	}
	m_pFractal=pFract;
}

CBaseFractal*	CFrontalFractal::SelectAlgebra(ENUM_ALGEBRATYPE AlgebraType,
											   ENUM_FRACTALTYPE ExprType,
											   bool bOpt)
{
	typedef	double	TypeElem;

	CBaseFractal *pNewFractal=NULL;
	CBaseFractal *pNewFractal1=NULL;
	CBaseFractal *pNewFractal2=NULL;
	CBaseFractal *pNewFractal3=NULL;
	CBaseFractal *pNewFractal4=NULL;


	////Le pb des templates c'est que les types doivent être connus
	////à la compilation donc on construit tout et on regarde après
	////Cette méthode permet de générer moins de code lors d'ajouts d'algèbres
	switch(AlgebraType)
	{
		case ALGEBRA_QUATERNION:
			{
				//typedef CQuaternion<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CQuaternion<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CQuaternion<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CQuaternion<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;

			}
			break;
		case ALGEBRA_HYPERCOMPLEX:
			{
				//typedef CHyperComplex<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplex<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplex<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplex<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE01:
			{
				//typedef CHyperComplexExot01<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot01<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot01<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot01<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE02:
			{
				//typedef CHyperComplexExot02<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot02<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot02<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot02<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE03:
			{
				//typedef CHyperComplexExot03<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot03<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot03<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot03<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE04:
			{
				//typedef CHyperComplexExot04<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot04<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot04<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot04<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE05:
			{
				//typedef CHyperComplexExot05<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot05<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot05<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot05<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE06:
			{
				//typedef CHyperComplexExot06<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot06<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot06<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot06<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE07:
			{
				//typedef CHyperComplexExot07<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot07<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot07<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot07<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;

		case ALGEBRA_EXOTIQUE08:
			{
				//typedef CHyperComplexExot08<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot08<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot08<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot08<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE09:
			{
				//typedef CHyperComplexExot09<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot09<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot09<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot09<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;

		case ALGEBRA_EXOTIQUE10:
			{
				//typedef CHyperComplexExot10<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot10<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot10<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot10<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE11:
			{
				//typedef CHyperComplexExot11<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot11<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot11<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot11<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE12:
			{
				//typedef CHyperComplexExot12<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot12<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot12<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot12<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE13:
			{
				//typedef CHyperComplexExot13<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot13<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot13<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot13<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE14:
			{
				//typedef CHyperComplexExot14<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot14<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot14<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot14<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE15:
			{
				//typedef CHyperComplexExot15<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot15<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot15<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot15<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;
		case ALGEBRA_EXOTIQUE16:
			{
				//typedef CHyperComplexExot16<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CHyperComplexExot16<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CHyperComplexExot16<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CHyperComplexExot16<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;
			}
			break;


		default:
			{
				//typedef CQuaternion<TypeElem,HYPERFONCTION_AMD>		TypeFract1;
				//pNewFractal1=new CFractal<TypeFract1>;
				typedef CQuaternion<TypeElem,HYPERFONCTION_NORMAL>	TypeFract2;
				pNewFractal2=new CFractal<TypeFract2>;
				//typedef CQuaternion<TypeElem,HYPERFONCTION_AMD>		TypeFract3;
				//pNewFractal3=new CFractalZ2<TypeFract3>;
				typedef CQuaternion<TypeElem,HYPERFONCTION_NORMAL>	TypeFract4;
				pNewFractal4=new CFractalZ2<TypeFract4>;

			}

	}

	switch(ExprType)
	{
		case FRACTAL_Z2:
			{
				//delete pNewFractal1;
				//pNewFractal1=NULL;
				delete pNewFractal2;
				pNewFractal2=NULL;
			}
			break;
		default:
			{
				//delete pNewFractal3;
				//pNewFractal3=NULL;
				delete pNewFractal4;
				pNewFractal4=NULL;
			}
	}

	switch(bOpt)
	{
		case true:
			{
				/*if(pNewFractal2!=NULL)
					delete pNewFractal2;
				pNewFractal2=NULL;
			    if(pNewFractal4!=NULL)
					delete pNewFractal4;
				pNewFractal4=NULL;

				if(pNewFractal1!=NULL)
					pNewFractal=pNewFractal1;
				else
					pNewFractal=pNewFractal3;*/
			}

			break;
		case false:
			{
				if(pNewFractal1!=NULL)
					delete pNewFractal1;
				pNewFractal1=NULL;
			    if(pNewFractal3!=NULL)
					delete pNewFractal3;
				pNewFractal3=NULL;

				if(pNewFractal2!=NULL)
					pNewFractal=pNewFractal2;
				else
					pNewFractal=pNewFractal4;
			}

	}

	return pNewFractal;
}
///**********************************************************
///*Gestion automate
int	CFrontalFractal::ChangeType(const std::string &NewAlgebra,
									const std::string &NewExpr,
									bool bOpt)
{
	ALGEBRATYPE::iterator ItAlgebra=m_AlgebralistType.find(NewAlgebra);
	ENUM_ALGEBRATYPE AlgebraType=(*ItAlgebra).second;

	FRACTALTYPE::iterator ItExpr=m_FractallistType.find(NewExpr);
	ENUM_FRACTALTYPE ExprType=(*ItExpr).second;

	CBaseFractal *pNewFractal=SelectAlgebra(AlgebraType,ExprType,bOpt);

	*pNewFractal=*m_pFractal;	//Recopie des paramètres de l'ancienne fractale

	pNewFractal->SetStrExpr(NewExpr);

	bool IsDerivateOK=pNewFractal->Derivate();

	int iError=pNewFractal->Parse();
	if(iError==0)
	{
		//Effacement de l'ancienne fractale
		if(m_pFractal!=NULL) delete m_pFractal;
		m_pFractal=pNewFractal;
	}

	return iError;
}

//////////////////////////////////////////////////////////
///Retourne		0   si OK
//				-1  si erreur dans dérivée
//				-2  si erreur dans expression
int	CFrontalFractal::ChangeType(const std::string &NewAlgebra,
									const std::string &NewExpr,
									const std::string &NewExprDerivate,
									bool bOpt)
{
	ALGEBRATYPE::iterator ItAlgebra=m_AlgebralistType.find(NewAlgebra);
	ENUM_ALGEBRATYPE AlgebraType=(*ItAlgebra).second;

	//si la dérivée a changé on prend le moteur générique
	//FRACTALTYPE::iterator ItExpr=m_FractallistType.find(NewExpr);
	ENUM_FRACTALTYPE ExprType=FRACTAL_GENERIC;

	CBaseFractal *pNewFractal=SelectAlgebra(AlgebraType,ExprType,bOpt);

	*pNewFractal=*m_pFractal;	//Recopie des paramètres de l'ancienne fractale

	pNewFractal->SetStrExpr(NewExpr);
	pNewFractal->SetStrExprDerivate(NewExprDerivate);

	int iError=pNewFractal->Parse();
	if(iError==0)
	{
		//Effacement de l'ancienne fractale
		if(m_pFractal!=NULL) delete m_pFractal;
		m_pFractal=pNewFractal;
	} else return iError;

	return 0;
}


#endif

