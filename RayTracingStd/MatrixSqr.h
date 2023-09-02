/////Etat classe : EN COURS

/////Implémentation d'une classe de matrices carrés
/////Utilisables dans le contexte du projet
/////Basé sur la MTL
#ifndef	_CMATRIXSQR
#define _CMATRIXSQR

//#include <mtl/lu.h>

/*typedef mtl::matrix<double,
					mtl::rectangle<>,
					mtl::dense<>,
					mtl::column_major>::type Type_Matrix;*/

//typedef mtl::matrix<double>::type Type_Matrix;

class CMatrixSqr
{
// Construction
public:
	inline CMatrixSqr();
	inline CMatrixSqr(const CMatrixSqr&);


//attributes
public:
	//Type_Matrix		m_Mat;
	double			m_Mat[4][4];

//Operations
public:
	inline void			Zero();
	inline void			Identity();
	inline void			Scale(double);
	inline void			Transpose();

	inline CMatrixSqr		Inv() const;
//Operators
public:
	inline double	GetValue(long x,long y) const {return m_Mat[x][y];}
	inline void		SetValue(long x,long y,double val) {m_Mat[x][y]=val;}
	inline CMatrixSqr& operator = (const CMatrixSqr&);
	inline CMatrixSqr operator * (const CMatrixSqr&) const;
	inline CMatrixSqr operator + (const CMatrixSqr&) const;
	inline CMatrixSqr operator - (const CMatrixSqr&) const;

// Implementation
public:
	inline virtual ~CMatrixSqr();
};

CMatrixSqr::CMatrixSqr()
{
}

CMatrixSqr::CMatrixSqr(const CMatrixSqr& Param)
{
	//mtl::copy(Param.m_Mat,m_Mat);
	register int i, j;

	for (i = 0 ; i < 4 ; i++)
	{
		for (j = 0 ; j < 4 ; j++)
		{
		  m_Mat[i][j] = Param.m_Mat[i][j];
		}
	}
}

void CMatrixSqr::Zero()
{
	//mtl::zero_matrix(m_Mat);
	register int i, j;

	for (i = 0 ; i < 4 ; i++)
	{
		for (j = 0 ; j < 4 ; j++)
		{
		  m_Mat[i][j] = 0.0;
		}
	}
}

void CMatrixSqr::Identity()
{
	//mtl::zero_matrix(m_Mat);
	//mtl::set_diagonal(m_Mat,1.0);
	register int i, j;

	for (i = 0 ; i < 4 ; i++)
	{
		for (j = 0 ; j < 4 ; j++)
		{
			  if (i == j)
			  {
				m_Mat[i][j] = 1.0;
			  }
			  else
			  {
				m_Mat[i][j] = 0.0;
			  }
		}
	}
}

void CMatrixSqr::Scale(double value)
{
//mtl::scale(m_Mat,value);
  register int i, j;

  for (i = 0 ; i < 4 ; i++)
    for (j = 0 ; j < 4 ; j++)
      m_Mat[i][j] *= value;

}

#define SWAP(a,b) c = a; a = b; b = c

void CMatrixSqr::Transpose()
{
	double c;
	//mtl::transpose(m_Mat);
	SWAP(m_Mat[0][1], m_Mat[1][0]);
	SWAP(m_Mat[0][2], m_Mat[2][0]);
	SWAP(m_Mat[1][2], m_Mat[2][1]);
	SWAP(m_Mat[2][3], m_Mat[3][2]);
	SWAP(m_Mat[3][0], m_Mat[0][3]);
	SWAP(m_Mat[3][1], m_Mat[1][3]);
}
#undef SWAP


CMatrixSqr CMatrixSqr::Inv() const
{
  CMatrixSqr Res;

	//mtl::dense1D<int> pivots(S,0);
	//mtl::lu_factor(m_Mat,pivots);
	//mtl::lu_inverse(m_Mat,pivots,Res.m_Mat);

  double d00, d01, d02, d03;
  double d10, d11, d12, d13;
  double d20, d21, d22, d23;
  double d30, d31, d32, d33;
  double m00, m01, m02, m03;
  double m10, m11, m12, m13;
  double m20, m21, m22, m23;
  double m30, m31, m32, m33;
  double D;

  m00 = m_Mat[0][0];  m01 = m_Mat[0][1];  m02 = m_Mat[0][2];  m03 = m_Mat[0][3];
  m10 = m_Mat[1][0];  m11 = m_Mat[1][1];  m12 = m_Mat[1][2];  m13 = m_Mat[1][3];
  m20 = m_Mat[2][0];  m21 = m_Mat[2][1];  m22 = m_Mat[2][2];  m23 = m_Mat[2][3];
  m30 = m_Mat[3][0];  m31 = m_Mat[3][1];  m32 = m_Mat[3][2];  m33 = m_Mat[3][3];

  d00 = m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m31*m22*m13 - m32*m23*m11 - m33*m21*m12;
  d01 = m10*m22*m33 + m12*m23*m30 + m13*m20*m32 - m30*m22*m13 - m32*m23*m10 - m33*m20*m12;
  d02 = m10*m21*m33 + m11*m23*m30 + m13*m20*m31 - m30*m21*m13 - m31*m23*m10 - m33*m20*m11;
  d03 = m10*m21*m32 + m11*m22*m30 + m12*m20*m31 - m30*m21*m12 - m31*m22*m10 - m32*m20*m11;

  d10 = m01*m22*m33 + m02*m23*m31 + m03*m21*m32 - m31*m22*m03 - m32*m23*m01 - m33*m21*m02;
  d11 = m00*m22*m33 + m02*m23*m30 + m03*m20*m32 - m30*m22*m03 - m32*m23*m00 - m33*m20*m02;
  d12 = m00*m21*m33 + m01*m23*m30 + m03*m20*m31 - m30*m21*m03 - m31*m23*m00 - m33*m20*m01;
  d13 = m00*m21*m32 + m01*m22*m30 + m02*m20*m31 - m30*m21*m02 - m31*m22*m00 - m32*m20*m01;

  d20 = m01*m12*m33 + m02*m13*m31 + m03*m11*m32 - m31*m12*m03 - m32*m13*m01 - m33*m11*m02;
  d21 = m00*m12*m33 + m02*m13*m30 + m03*m10*m32 - m30*m12*m03 - m32*m13*m00 - m33*m10*m02;
  d22 = m00*m11*m33 + m01*m13*m30 + m03*m10*m31 - m30*m11*m03 - m31*m13*m00 - m33*m10*m01;
  d23 = m00*m11*m32 + m01*m12*m30 + m02*m10*m31 - m30*m11*m02 - m31*m12*m00 - m32*m10*m01;

  d30 = m01*m12*m23 + m02*m13*m21 + m03*m11*m22 - m21*m12*m03 - m22*m13*m01 - m23*m11*m02;
  d31 = m00*m12*m23 + m02*m13*m20 + m03*m10*m22 - m20*m12*m03 - m22*m13*m00 - m23*m10*m02;
  d32 = m00*m11*m23 + m01*m13*m20 + m03*m10*m21 - m20*m11*m03 - m21*m13*m00 - m23*m10*m01;
  d33 = m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m20*m11*m02 - m21*m12*m00 - m22*m10*m01;

  D = m00*d00 - m01*d01 + m02*d02 - m03*d03;

  if (D == 0.0)
  {
    //Error("Singular matrix in MInvers.");
  }

  Res.m_Mat[0][0] =  d00/D; Res.m_Mat[0][1] = -d10/D;  Res.m_Mat[0][2] =  d20/D; Res.m_Mat[0][3] = -d30/D;
  Res.m_Mat[1][0] = -d01/D; Res.m_Mat[1][1] =  d11/D;  Res.m_Mat[1][2] = -d21/D; Res.m_Mat[1][3] =  d31/D;
  Res.m_Mat[2][0] =  d02/D; Res.m_Mat[2][1] = -d12/D;  Res.m_Mat[2][2] =  d22/D; Res.m_Mat[2][3] = -d32/D;
  Res.m_Mat[3][0] = -d03/D; Res.m_Mat[3][1] =  d13/D;  Res.m_Mat[3][2] = -d23/D; Res.m_Mat[3][3] =  d33/D;

  return(Res);
}

CMatrixSqr&	CMatrixSqr::operator=(const CMatrixSqr & Param)
{
	//mtl::copy(Param.m_Mat,m_Mat);
	register int i, j;

	for (i = 0 ; i < 4 ; i++)
	{
		for (j = 0 ; j < 4 ; j++)
		{
		  m_Mat[i][j] = Param.m_Mat[i][j];
		}
	}

	return (*this);
}

CMatrixSqr	CMatrixSqr::operator*(const CMatrixSqr &Param) const
{
  CMatrixSqr res;

	//mtl::mult(m_Mat,Param.m_Mat,res.m_Mat);
  res.m_Mat[0][0] = m_Mat[0][0] * Param.m_Mat[0][0] + m_Mat[0][1] * Param.m_Mat[1][0] + m_Mat[0][2] * Param.m_Mat[2][0] + m_Mat[0][3] * Param.m_Mat[3][0];
  res.m_Mat[0][1] = m_Mat[0][0] * Param.m_Mat[0][1] + m_Mat[0][1] * Param.m_Mat[1][1] + m_Mat[0][2] * Param.m_Mat[2][1] + m_Mat[0][3] * Param.m_Mat[3][1];
  res.m_Mat[0][2] = m_Mat[0][0] * Param.m_Mat[0][2] + m_Mat[0][1] * Param.m_Mat[1][2] + m_Mat[0][2] * Param.m_Mat[2][2] + m_Mat[0][3] * Param.m_Mat[3][2];
  res.m_Mat[0][3] = m_Mat[0][0] * Param.m_Mat[0][3] + m_Mat[0][1] * Param.m_Mat[1][3] + m_Mat[0][2] * Param.m_Mat[2][3] + m_Mat[0][3] * Param.m_Mat[3][3];

  res.m_Mat[1][0] = m_Mat[1][0] * Param.m_Mat[0][0] + m_Mat[1][1] * Param.m_Mat[1][0] + m_Mat[1][2] * Param.m_Mat[2][0] + m_Mat[1][3] * Param.m_Mat[3][0];
  res.m_Mat[1][1] = m_Mat[1][0] * Param.m_Mat[0][1] + m_Mat[1][1] * Param.m_Mat[1][1] + m_Mat[1][2] * Param.m_Mat[2][1] + m_Mat[1][3] * Param.m_Mat[3][1];
  res.m_Mat[1][2] = m_Mat[1][0] * Param.m_Mat[0][2] + m_Mat[1][1] * Param.m_Mat[1][2] + m_Mat[1][2] * Param.m_Mat[2][2] + m_Mat[1][3] * Param.m_Mat[3][2];
  res.m_Mat[1][3] = m_Mat[1][0] * Param.m_Mat[0][3] + m_Mat[1][1] * Param.m_Mat[1][3] + m_Mat[1][2] * Param.m_Mat[2][3] + m_Mat[1][3] * Param.m_Mat[3][3];

  res.m_Mat[2][0] = m_Mat[2][0] * Param.m_Mat[0][0] + m_Mat[2][1] * Param.m_Mat[1][0] + m_Mat[2][2] * Param.m_Mat[2][0] + m_Mat[2][3] * Param.m_Mat[3][0];
  res.m_Mat[2][1] = m_Mat[2][0] * Param.m_Mat[0][1] + m_Mat[2][1] * Param.m_Mat[1][1] + m_Mat[2][2] * Param.m_Mat[2][1] + m_Mat[2][3] * Param.m_Mat[3][1];
  res.m_Mat[2][2] = m_Mat[2][0] * Param.m_Mat[0][2] + m_Mat[2][1] * Param.m_Mat[1][2] + m_Mat[2][2] * Param.m_Mat[2][2] + m_Mat[2][3] * Param.m_Mat[3][2];
  res.m_Mat[2][3] = m_Mat[2][0] * Param.m_Mat[0][3] + m_Mat[2][1] * Param.m_Mat[1][3] + m_Mat[2][2] * Param.m_Mat[2][3] + m_Mat[2][3] * Param.m_Mat[3][3];

  res.m_Mat[3][0] = m_Mat[3][0] * Param.m_Mat[0][0] + m_Mat[3][1] * Param.m_Mat[1][0] + m_Mat[3][2] * Param.m_Mat[2][0] + m_Mat[3][3] * Param.m_Mat[3][0];
  res.m_Mat[3][1] = m_Mat[3][0] * Param.m_Mat[0][1] + m_Mat[3][1] * Param.m_Mat[1][1] + m_Mat[3][2] * Param.m_Mat[2][1] + m_Mat[3][3] * Param.m_Mat[3][1];
  res.m_Mat[3][2] = m_Mat[3][0] * Param.m_Mat[0][2] + m_Mat[3][1] * Param.m_Mat[1][2] + m_Mat[3][2] * Param.m_Mat[2][2] + m_Mat[3][3] * Param.m_Mat[3][2];
  res.m_Mat[3][3] = m_Mat[3][0] * Param.m_Mat[0][3] + m_Mat[3][1] * Param.m_Mat[1][3] + m_Mat[3][2] * Param.m_Mat[2][3] + m_Mat[3][3] * Param.m_Mat[3][3];

  return(res);
}

CMatrixSqr	CMatrixSqr::operator+(const CMatrixSqr &Param) const
{
	CMatrixSqr res(Param);

	//mtl::add(m_Mat,res.m_Mat);
	register int i, j;

	for (i = 0 ; i < 4 ; i++)
		for (j = 0 ; j < 4 ; j++)
			res.m_Mat[i][j] = m_Mat[i][j] + Param.m_Mat[i][j];

	return(res);
}

CMatrixSqr	CMatrixSqr::operator-(const CMatrixSqr & Param) const
{
	CMatrixSqr res(Param);

	//mtl::sub(m_Mat,res.m_Mat);
	register int i, j;

	for (i = 0 ; i < 4 ; i++)
		for (j = 0 ; j < 4 ; j++)
			res.m_Mat[i][j] = m_Mat[i][j] - Param.m_Mat[i][j];


	return(res);
}

CMatrixSqr::~CMatrixSqr()
{
}

#endif
