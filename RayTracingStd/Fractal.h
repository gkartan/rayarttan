/////Etat classe : EN COURS

#ifndef _FRACTAL
#define _FRACTAL

#include "BaseFractal.h"
#include "FormulaParserParser.h"
#include "ComputeDerivate.h"



template <class T> 
class CFractal : public CBaseFractal
{
// Construction
public:
	inline CFractal();
	inline CFractal(const T &InitVal,long NbIt,double,double);

//Attributes
protected:
	T							m_InitValue;
	CComputeExpr<T,double>		m_Expr;
	CComputeExpr<T,double>		m_ExprDerivate;

	///Fonctions d'accès
public:
	CBaseVector<4,double>		GetInitValue() {return m_InitValue;};
	void						SetInitValue(const CBaseVector<4,double> &Value) {m_InitValue=Value;};
	virtual std::string			GetAlgebraType() {return m_InitValue.GetAlgebraType();}; //Type de la fractale / quaternion...
	virtual bool				GetOptimisation() {return  m_InitValue.GetOptimisation();}//Permet de savoir si la classe est optimisé 3DNow
	virtual bool				Derivate();
	virtual int					Parse();

	///
public:
	inline	void	SetExpr(const CComputeExpr<T,double>& Expr) {m_Expr=Expr;};
	inline	void	SetExprDerivate(const CComputeExpr<T,double>& Expr) {m_ExprDerivate=Expr;};

public:
	virtual void	ForceEqualFractal(CBaseFractal&);
	inline virtual CFractal&	operator=(CFractal&);

protected:
	inline virtual CVector	Normal(const CCoord &coord);

protected:
	////operations spécialisés
	inline virtual	bool	Estimator(CRay&,double Dist); //un inline sur cette ligne ralentit

// Implementation
public:
	inline	virtual ~CFractal();

public:
	virtual	void	GetOutputStream(ostream&);

public:
	inline virtual CBaseGeometry*	Instantiate();		//instancie un nouvel objet de ce type
};

template<class T>
CFractal<T>::CFractal<T>()
{
	m_DistanceTolerance=1e-7;
	m_FractalTolerance=1e-8;
	m_InitValue=T(.49,.5,-.34,.1);
	m_NbIteration=5;
	m_MaxLimits=16;
	m_BoundSphere=CSphere(CCoord(0,0,0),2);
	m_Angle=0.0;
}

template<class T>
CFractal<T>::CFractal<T>(const T& InitVal,long NbIt,double precision,double Angle)
{
	m_DistanceTolerance=1e-7;
	m_FractalTolerance=1e-8;
	m_InitValue=InitVal;
	m_NbIteration=NbIt;
	m_MaxLimits=16;
	m_Increment=precision;
	m_BoundSphere=CSphere(CCoord(0,0,0),2);
	m_Angle=Angle;
}

template<class T>
CFractal<T>::~CFractal<T>()
{

}

template<class T>
void	CFractal<T>::ForceEqualFractal(CBaseFractal &Origin)
{
	CFractal<T> *pTrueOrigin=static_cast<CFractal<T>*>(&Origin);
	if(pTrueOrigin!=NULL)
	{
		m_InitValue=pTrueOrigin->m_InitValue;
		m_Expr=pTrueOrigin->m_Expr;
		m_ExprDerivate=pTrueOrigin->m_ExprDerivate;
		m_Angle=pTrueOrigin->m_Angle;
	}
}

template<class T>
CFractal<T>&	CFractal<T>::operator=(CFractal<T>	&Origin)
{
	m_InitValue=Origin.m_InitValue;
	m_Expr=Origin.m_Expr;
	m_ExprDerivate=Origin.m_ExprDerivate;
	m_Angle=Origin.m_Angle;

	CBaseFractal::operator=(Origin);

	return (*this);
}



//////////////////////////////////////////
///Normale à la fractale
///On calcule la normale itérativement car la fractale est indérivable
///Calcul du tenseur itérativement
template<class T>
CVector	CFractal<T>::Normal(const CCoord &vInit)
{
	T	QInit(vInit.GetX(),vInit.GetY(),vInit.GetZ(),0);
	T	Qn(vInit.GetX(),vInit.GetY(),vInit.GetZ(),0);
	T	Tx(1,0,0,0);
	T	Ty(0,1,0,0);
	T	Tz(0,0,1,0);


  if(m_Angle!=0.0)
  {
	  T		ei_theta(cos(m_Angle),sin(m_Angle),0,0);
	  T		ei_mtheta(cos(-m_Angle),sin(-m_Angle),0,0);

	  T		Constant=ei_theta*m_InitValue;

	  for(int i=1;i<=m_NbIteration;i++)
	  {
			T QnDerivate(m_ExprDerivate.Compute(Qn,m_InitValue,QInit,true));
			Tx*=QnDerivate;
			Ty*=QnDerivate;
			Tz*=QnDerivate;
			Qn.Mult(ei_mtheta);
			m_Expr.Compute(Qn,m_InitValue,QInit) ;//+ m_InitValue;
			Qn.Mult(ei_theta);
	  }

  } else {
	for(int i=1;i<=m_NbIteration;i++)
	{
		T QnDerivate(m_ExprDerivate.Compute(Qn,m_InitValue,QInit,true));
		Tx*=QnDerivate;
		Ty*=QnDerivate;
		Tz*=QnDerivate;
		m_Expr.Compute(Qn,m_InitValue,QInit) ;//+ m_InitValue;
	}
  }

	CVector Res(Tx.Scalar(Qn,AXE_X),
				Ty.Scalar(Qn,AXE_Y),
				Tz.Scalar(Qn,AXE_Z));
	Res.Normalize();

	return(Res);
}

////////////////////////////////////////////////////
//Première estimation grossière de la distance à la fractale
//Parcours le rayon par pas defini
template<class T>
bool	CFractal<T>::Estimator(CRay &Ray,
							   double Dist)
{

  CVector &Scale=Ray.GetDirect()*Dist;
  CCoord  &Init=Ray.GetOrigin()+Scale;

  T			    QInit(Init.GetX(),
				   Init.GetY(),
				   Init.GetZ(),
				   0);
  T				Qn(Init.GetX(),
				   Init.GetY(),
				   Init.GetZ(),
				   0);

  unsigned long NumIteration=0;

  if(m_Angle!=0.0)
  {
	  T		ei_theta(cos(m_Angle),sin(m_Angle),0,0);
	  T		ei_mtheta(cos(-m_Angle),sin(-m_Angle),0,0);

	  T		Constant=ei_theta*m_InitValue;

	  while(Qn.norm2()<m_MaxLimits && NumIteration<m_NbIteration)
	  {
			//Calcul Quaternion//////
			//////f(z)=eitheta*f(ei_mtheta*z) --> rotation d'un angle theta autour de l'axe i
			Qn.Mult(ei_mtheta);
			m_Expr.Compute(Qn,m_InitValue,QInit) ;//+ m_InitValue;
			Qn.Mult(ei_theta);

			NumIteration++;
	  }
  } else {
	  while(Qn.norm2()<m_MaxLimits && NumIteration<m_NbIteration)
	  {
			//Calcul Quaternion
			m_Expr.Compute(Qn,m_InitValue,QInit);

			NumIteration++;
	  }
  }

  if(NumIteration==m_NbIteration)
  {
	  return(true);
  } 

  return(false);
}

/////************************************************************************
////On dérive l'expression et on stocke
template<class T>
bool	CFractal<T>::Derivate()
{
	CFormulaParser<T,double> Parser(m_sExpr);
	CListExpr<double> ListExpr;
	Parser.Parse(ListExpr);
	m_Expr.SetExpr(ListExpr);

	if(CComputeDerivate::Derivate(m_sExpr,m_sExprDerivate))
	{

		CFormulaParser<T,double> ParserDerivate(m_sExprDerivate);
		CListExpr<double> ListExprDerivate;
		ParserDerivate.Parse(ListExprDerivate);

		m_ExprDerivate.SetExpr(ListExprDerivate);

		return true;
	} else {
		return false;
	}
}

template<class T>
int	CFractal<T>::Parse()
{
	CFormulaParser<T,double> Parser(m_sExpr);
	CListExpr<double> ListExpr;
	if(Parser.Parse(ListExpr)==0)
	{
		m_Expr.SetExpr(ListExpr);


		CFormulaParser<T,double> ParserDerivate(m_sExprDerivate);
		CListExpr<double> ListExprDerivate;
		if(ParserDerivate.Parse(ListExprDerivate)==0)
		{
			m_ExprDerivate.SetExpr(ListExprDerivate);
		} else return -1;
	} else	return -2;

	return 0;
}


template<class T>
void	CFractal<T>::GetOutputStream(ostream &o)
{
	o	<<	"\nfractal\n{\n";						//entete
	o	<< "\t"					<< m_InitValue.GetAlgebraType().c_str() << "\n";	//type
	o   <<  "\t"				<< m_InitValue							<< "\n";
	o	<< "\t\""				<< m_sExpr.c_str()						<<"\"\n";			//Expression
	if(m_bManualDerivative)
		o	<<	"\tderivative \""	<< m_sExprDerivate.c_str()				<< "\"\n";

	o   << "\tmax_iteration "	<< m_NbIteration						<< "\n";
	o	<< "\tbailout "			<< sqrt(m_MaxLimits)					<< "\n";
	o	<< "\tprecision "		<< m_Increment							<< "\n";

//	if(m_BoundSphere.GetRay()!=DEFAULT_BOUNDSIZE)
//		o	<< "\tbound_size "	<<	m_BoundSphere.GetRay();

	if(m_Angle!=0.0)
		o	<< "\tangle "			<< m_Angle								<< "\n";

	if(m_Rotate!=CVector(0,0,0))
		o	<< "\trotate "			<< m_Rotate								<< "\n";
	//o	<< "\tscale "			<<
	if(m_Translate!=CVector(0,0,0))
		o	<< "\ttranslate "		<< m_Translate							<< "\n";

	o	<< "\ttexture{ \""		<< m_pMatiere->GetName().c_str()		<< "\" }\n";
	o	<<	"\n}\n";								//fin
}

template<class T>
CBaseGeometry*	CFractal<T>::Instantiate()
{
	return new CFractal<T>;
}
#endif
