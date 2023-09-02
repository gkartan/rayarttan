#pragma warning(disable : 4786)
#pragma warning(disable : 4275)

#include "Constants.h"
#include "MatrixTransform.h"
  
CMatrixTransform::CMatrixTransform()
{
	m_bExist=false;	//la matrice de transformation n'est pas valide
	m_Mat.Identity();
	m_InvMat.Identity();
}

CMatrixTransform::CMatrixTransform(const CMatrixSqr &Init)
{
	m_Mat=Init;
	m_InvMat=Init.Inv();
}

CMatrixTransform::~CMatrixTransform()
{
}

void CMatrixTransform::Initialize()
{
	m_Mat.Identity();
	m_InvMat.Identity();
}


void CMatrixTransform::Scale(const CVector &Vect)
{
	m_bExist=true;

	m_Mat.Identity();
	m_Mat.SetValue(0,0,Vect.GetX());
	m_Mat.SetValue(1,1,Vect.GetY());
	m_Mat.SetValue(2,2,Vect.GetZ());

	m_InvMat.Identity();
	m_InvMat.SetValue(0,0,1.0/Vect.GetX());
	m_InvMat.SetValue(1,1,1.0/Vect.GetY());
	m_InvMat.SetValue(2,2,1.0/Vect.GetZ());
}

void CMatrixTransform::Translate(const CVector &Vect)
{
	m_bExist=true;

	m_Mat.Identity();
	m_Mat.SetValue(3,0,Vect.GetX());
	m_Mat.SetValue(3,1,Vect.GetY());
	m_Mat.SetValue(3,2,Vect.GetZ());

	m_InvMat.Identity();
	m_InvMat.SetValue(3,0,-Vect.GetX());
	m_InvMat.SetValue(3,1,-Vect.GetY());
	m_InvMat.SetValue(3,2,-Vect.GetZ());

}

void CMatrixTransform::Rotate(const CVector &Vect)
{
	m_bExist=true;

	register double cosx, cosy, cosz, sinx, siny, sinz;

	CVector	RadVect=Vect*PI_DIV_180;

	m_Mat.Identity();

	cosx=cos(RadVect.GetX());
	sinx=sin(RadVect.GetX());
	cosy=cos(RadVect.GetY());
	siny=sin(RadVect.GetY());
	cosz=cos(RadVect.GetZ());
	sinz=sin(RadVect.GetZ());

	m_Mat.SetValue(1,1,cosx);
	m_Mat.SetValue(2,2,cosx);
	m_Mat.SetValue(1,2,sinx);
	m_Mat.SetValue(2,1,-sinx);

	m_InvMat=m_Mat;
	m_InvMat.Transpose();

	CMatrixSqr	MatrixTemp;
	MatrixTemp.Identity();

	MatrixTemp.SetValue(0,0,cosy);
	MatrixTemp.SetValue(2,2,cosy);
	MatrixTemp.SetValue(0,2,- siny);
	MatrixTemp.SetValue(2,0,siny);

	m_Mat=m_Mat*MatrixTemp;
	MatrixTemp.Transpose();

	m_InvMat=MatrixTemp*m_InvMat;

	MatrixTemp.Identity();

	MatrixTemp.SetValue(0,0,cosz);
	MatrixTemp.SetValue(1,1,cosz);
	MatrixTemp.SetValue(0,1,sinz);
	MatrixTemp.SetValue(1,0,-sinz);

	m_Mat=m_Mat*MatrixTemp;

	MatrixTemp.Transpose();

	m_InvMat=MatrixTemp*m_InvMat;
}

////***************
////Rotation mais sans utilisé la matrice inverse
////--->Plus efficace
void CMatrixTransform::SimpleRotate(const CVector &Vect)
{
	m_bExist=true;

	register double cosx, cosy, cosz, sinx, siny, sinz;

	CVector	RadVect=Vect*PI_DIV_180;

	m_Mat.Identity();

	cosx=cos(RadVect.GetX());
	sinx=sin(RadVect.GetX());
	cosy=cos(RadVect.GetY());
	siny=sin(RadVect.GetY());
	cosz=cos(RadVect.GetZ());
	sinz=sin(RadVect.GetZ());

	m_Mat.SetValue(1,1,cosx);
	m_Mat.SetValue(2,2,cosx);
	m_Mat.SetValue(1,2,sinx);
	m_Mat.SetValue(2,1,-sinx);

	CMatrixSqr	MatrixTemp;
	MatrixTemp.Identity();

	MatrixTemp.SetValue(0,0,cosy);
	MatrixTemp.SetValue(2,2,cosy);
	MatrixTemp.SetValue(0,2,- siny);
	MatrixTemp.SetValue(2,0,siny);

	m_Mat=m_Mat*MatrixTemp;

	MatrixTemp.Identity();

	MatrixTemp.SetValue(0,0,cosz);
	MatrixTemp.SetValue(1,1,cosz);
	MatrixTemp.SetValue(0,1,sinz);
	MatrixTemp.SetValue(1,0,-sinz);

	m_Mat=m_Mat*MatrixTemp;
}

void CMatrixTransform::SimpleComposeAndRotate(const CVector &Vect)
{
	m_bExist=true;

	register double cosx, cosy, cosz, sinx, siny, sinz;

	CVector	RadVect=Vect*PI_DIV_180;

	CMatrixSqr	MatrixTemp1;
	MatrixTemp1.Identity();

	cosx=cos(RadVect.GetX());
	sinx=sin(RadVect.GetX());
	cosy=cos(RadVect.GetY());
	siny=sin(RadVect.GetY());
	cosz=cos(RadVect.GetZ());
	sinz=sin(RadVect.GetZ());

	MatrixTemp1.SetValue(1,1,cosx);
	MatrixTemp1.SetValue(2,2,cosx);
	MatrixTemp1.SetValue(1,2,sinx);
	MatrixTemp1.SetValue(2,1,-sinx);

	CMatrixSqr	MatrixTemp2;
	MatrixTemp2.Identity();

	MatrixTemp2.SetValue(0,0,cosy);
	MatrixTemp2.SetValue(2,2,cosy);
	MatrixTemp2.SetValue(0,2,- siny);
	MatrixTemp2.SetValue(2,0,siny);

	MatrixTemp1=MatrixTemp1*MatrixTemp2;

	MatrixTemp2.Identity();

	MatrixTemp2.SetValue(0,0,cosz);
	MatrixTemp2.SetValue(1,1,cosz);
	MatrixTemp2.SetValue(0,1,sinz);
	MatrixTemp2.SetValue(1,0,-sinz);

	MatrixTemp1=MatrixTemp1*MatrixTemp2;

	m_Mat=m_Mat*MatrixTemp1;	//composition --> on n'efface pas m_Mat
}

/////////////
//Déplace la coordonnée suivant la matrice de transformation
CCoord CMatrixTransform::Trans(const CCoord &Param)	const
{
	CCoord	Res(Param.GetX()*m_Mat.GetValue(0,0)+Param.GetY()*m_Mat.GetValue(1,0)+Param.GetZ()*m_Mat.GetValue(2,0)+m_Mat.GetValue(3,0),
				Param.GetX()*m_Mat.GetValue(0,1)+Param.GetY()*m_Mat.GetValue(1,1)+Param.GetZ()*m_Mat.GetValue(2,1)+m_Mat.GetValue(3,1),
				Param.GetX()*m_Mat.GetValue(0,2)+Param.GetY()*m_Mat.GetValue(1,2)+Param.GetZ()*m_Mat.GetValue(2,2)+m_Mat.GetValue(3,2));

	return Res;
}


CCoord CMatrixTransform::InvTrans(const CCoord &Param)	const
{
	CCoord	ParamNormalize=Param;
	ParamNormalize.Normalize();

	CCoord	Res(Param.GetX()*m_InvMat.GetValue(0,0)+Param.GetY()*m_InvMat.GetValue(1,0)+Param.GetZ()*m_InvMat.GetValue(2,0)+m_InvMat.GetValue(3,0),
				Param.GetX()*m_InvMat.GetValue(0,1)+Param.GetY()*m_InvMat.GetValue(1,1)+Param.GetZ()*m_InvMat.GetValue(2,1)+m_InvMat.GetValue(3,1),
				Param.GetX()*m_InvMat.GetValue(0,2)+Param.GetY()*m_InvMat.GetValue(1,2)+Param.GetZ()*m_InvMat.GetValue(2,2)+m_InvMat.GetValue(3,2));

	return Res;
}


CVector CMatrixTransform::Trans(const CVector &Param)	const
{
	CVector	Res(Param.GetX()*m_Mat.GetValue(0,0)+Param.GetY()*m_Mat.GetValue(1,0)+Param.GetZ()*m_Mat.GetValue(2,0),
				Param.GetX()*m_Mat.GetValue(0,1)+Param.GetY()*m_Mat.GetValue(1,1)+Param.GetZ()*m_Mat.GetValue(2,1),
				Param.GetX()*m_Mat.GetValue(0,2)+Param.GetY()*m_Mat.GetValue(1,2)+Param.GetZ()*m_Mat.GetValue(2,2));

	return Res;
}

CVector CMatrixTransform::InvTrans(const CVector &Param)	const
{
	CVector	Res(Param.GetX()*m_InvMat.GetValue(0,0)+Param.GetY()*m_InvMat.GetValue(1,0)+Param.GetZ()*m_InvMat.GetValue(2,0),
				Param.GetX()*m_InvMat.GetValue(0,1)+Param.GetY()*m_InvMat.GetValue(1,1)+Param.GetZ()*m_InvMat.GetValue(2,1),
				Param.GetX()*m_InvMat.GetValue(0,2)+Param.GetY()*m_InvMat.GetValue(1,2)+Param.GetZ()*m_InvMat.GetValue(2,2));

	return Res;
}

CVector	CMatrixTransform::TransNormal(const CVector &Param)	const
{
	CVector	Res(Param.GetX()*m_InvMat.GetValue(0,0)+Param.GetY()*m_InvMat.GetValue(0,1)+Param.GetZ()*m_InvMat.GetValue(0,2),
				Param.GetX()*m_InvMat.GetValue(1,0)+Param.GetY()*m_InvMat.GetValue(1,1)+Param.GetZ()*m_InvMat.GetValue(1,2),
				Param.GetX()*m_InvMat.GetValue(2,0)+Param.GetY()*m_InvMat.GetValue(2,1)+Param.GetZ()*m_InvMat.GetValue(2,2));

	return Res;
}

void CMatrixTransform::Compose(const CMatrixTransform &Param)
{
	m_bExist=true;

	//m_Mat=m_Mat*Param.m_Mat;
	//m_InvMat=m_InvMat*Param.m_InvMat;
	m_Mat=Param.m_Mat*m_Mat;
	m_InvMat=Param.m_InvMat*m_InvMat;
}


CMatrixTransform& CMatrixTransform::operator = (const CMatrixTransform &Param)
{
	m_Mat=Param.m_Mat;
	m_InvMat=Param.m_InvMat;
	m_bExist=Param.m_bExist;

	return(*this);
}

//**********************************************************************
//Fonctions de conversions Matrice<->Quaternion
void	CMatrixTransform::QuatToMat(const CBaseVector<4,double> &Quat)
{
	m_bExist=true;

	double  DEUX_X2=2*Quat.m_Value[0]*Quat.m_Value[0];
	double	DEUX_Y2=2*Quat.m_Value[1]*Quat.m_Value[1];
	double	DEUX_Z2=2*Quat.m_Value[2]*Quat.m_Value[2];
	double	DEUX_XY=2*Quat.m_Value[0]*Quat.m_Value[1];
	double	DEUX_XZ=2*Quat.m_Value[0]*Quat.m_Value[2];
	double	DEUX_XW=2*Quat.m_Value[0]*Quat.m_Value[3];
	double	DEUX_YZ=2*Quat.m_Value[1]*Quat.m_Value[2];
	double	DEUX_YW=2*Quat.m_Value[1]*Quat.m_Value[3];
	double	DEUX_ZW=2*Quat.m_Value[2]*Quat.m_Value[3];

	m_Mat.SetValue(0,0,1-DEUX_Y2-DEUX_Z2);
	m_Mat.SetValue(0,1,DEUX_XY+DEUX_ZW);
	m_Mat.SetValue(0,2,DEUX_XZ+DEUX_YW);
	m_Mat.SetValue(0,3,0);
	m_Mat.SetValue(1,0,DEUX_XY-DEUX_ZW);
	m_Mat.SetValue(1,1,1-DEUX_X2-DEUX_Z2);
	m_Mat.SetValue(1,2,DEUX_YZ+DEUX_XW);
	m_Mat.SetValue(1,3,0);
	m_Mat.SetValue(2,0,DEUX_XZ+DEUX_YW);
	m_Mat.SetValue(2,1,DEUX_YZ-DEUX_XW);
	m_Mat.SetValue(2,2,1-DEUX_X2-DEUX_Y2);
	m_Mat.SetValue(2,3,0);
	m_Mat.SetValue(3,0,0);
	m_Mat.SetValue(3,1,0);
	m_Mat.SetValue(3,2,0);
	m_Mat.SetValue(3,3,1);
}

void	CMatrixTransform::MatToQuat(CBaseVector<4,double> &Quat) const
{
	double	T=m_Mat.GetValue(0,0)+m_Mat.GetValue(1,1)+m_Mat.GetValue(2,2)+1;

	if(T>0)
	{
		double S=sqrt(T)*0.5;

		Quat.m_Value[3]=0.25*S;
		Quat.m_Value[0]=(m_Mat.GetValue(2,1)-m_Mat.GetValue(1,2))*S;
		Quat.m_Value[1]=(m_Mat.GetValue(0,2)-m_Mat.GetValue(2,0))*S;
		Quat.m_Value[2]=(m_Mat.GetValue(1,0)-m_Mat.GetValue(0,1))*S;
	} else {

		int NumColonne=-1;
		if(m_Mat.GetValue(0,0) > m_Mat.GetValue(1,1) &&
		   m_Mat.GetValue(1,1) > m_Mat.GetValue(2,2))
		{
			NumColonne=0;
		} else
		if(m_Mat.GetValue(0,0) <= m_Mat.GetValue(1,1))
		{
			NumColonne=1;
		} else
		if(m_Mat.GetValue(0,0) > m_Mat.GetValue(2,2))
		{
			NumColonne=0;
		} else 
			NumColonne=2;

		switch(NumColonne)
		{
			case 1:
				{
					double S=sqrt(1+m_Mat.GetValue(0,0)-m_Mat.GetValue(1,1)-m_Mat.GetValue(2,2))*2.0;
					Quat.m_Value[0]=0.5/S;
					Quat.m_Value[1]=(m_Mat.GetValue(0,1)+m_Mat.GetValue(1,0))/S;
					Quat.m_Value[2]=(m_Mat.GetValue(0,2)+m_Mat.GetValue(2,0))/S;
					Quat.m_Value[3]=(m_Mat.GetValue(1,2)+m_Mat.GetValue(2,1))/S;
				}
				break;
			case 2:
				{
					double S=sqrt(1+m_Mat.GetValue(1,1)-m_Mat.GetValue(0,0)-m_Mat.GetValue(2,2))*2.0;
					Quat.m_Value[0]=(m_Mat.GetValue(0,1)+m_Mat.GetValue(1,0))/S;
					Quat.m_Value[1]=0.5/S;
					Quat.m_Value[2]=(m_Mat.GetValue(1,2)+m_Mat.GetValue(2,1))/S;
					Quat.m_Value[3]=(m_Mat.GetValue(0,2)+m_Mat.GetValue(2,0))/S;
				}
				break;
			case 3:
				{
					double S=sqrt(1+m_Mat.GetValue(2,2)-m_Mat.GetValue(0,0)-m_Mat.GetValue(1,1))*2.0;
					Quat.m_Value[0]=(m_Mat.GetValue(0,2)+m_Mat.GetValue(2,0))/S;
					Quat.m_Value[1]=(m_Mat.GetValue(1,2)+m_Mat.GetValue(2,1))/S;
					Quat.m_Value[2]=0.5/S;
					Quat.m_Value[3]=(m_Mat.GetValue(0,1)+m_Mat.GetValue(1,0))/S;
				}
				break;
			default:
				/////Error
				break;

		}

	}
}
// Fin Conversion Matrice<->Quaternion
//***********************************************************************

///Création d'une matrice de rotation autour d'un axe passé en paramètre
///L'angle est en degrées
void CMatrixTransform::AxisRotate(const CVector &Vect, double angle)
{
  m_bExist=true;

  double Angle_Rad=angle*PI_DIV_180;

  double cosx, sinx;

  CVector vTemp(Vect);
  vTemp.Normalize();

  m_Mat.Identity();

  cosx = cos(Angle_Rad);
  sinx = sin(Angle_Rad);

  m_Mat.SetValue(0,0,vTemp.GetX() * vTemp.GetX() + cosx * (1.0 - vTemp.GetX() * vTemp.GetX()));
  m_Mat.SetValue(0,1,vTemp.GetX() * vTemp.GetY() * (1.0 - cosx) + vTemp.GetZ() * sinx);
  m_Mat.SetValue(0,2,vTemp.GetX() * vTemp.GetZ() * (1.0 - cosx) - vTemp.GetY() * sinx);

  m_Mat.SetValue(1,0, vTemp.GetX() * vTemp.GetY() * (1.0 - cosx) - vTemp.GetZ() * sinx);
  m_Mat.SetValue(1,1, vTemp.GetY() * vTemp.GetY() + cosx * (1.0 - vTemp.GetY() * vTemp.GetY()));
  m_Mat.SetValue(1,2, vTemp.GetY() * vTemp.GetZ() * (1.0 - cosx) + vTemp.GetX() * sinx);

  m_Mat.SetValue(2,0, vTemp.GetX() * vTemp.GetZ() * (1.0 - cosx) + vTemp.GetY() * sinx);
  m_Mat.SetValue(2,1, vTemp.GetY() * vTemp.GetZ() * (1.0 - cosx) - vTemp.GetX() * sinx);
  m_Mat.SetValue(2,2, vTemp.GetZ() * vTemp.GetZ() + cosx * (1.0 - vTemp.GetZ() * vTemp.GetZ()));

  m_InvMat=m_Mat;
  m_InvMat.Transpose();

}

//Calcul de la tranformation pour aboutir à un système canonique
//Origin : origine du système de coordonnée
//Up	 : Direction de l'axe Z du système de coordonnée
//Radius : Longueur des axes X et Y
//Length : Longueur de l'axe Z
void CMatrixTransform::ChangeCoordinateSystem(const CCoord &Origin,const CVector &Up,double Radius, double Length )
{
  CVector TmpUp(Up);
  CVector ScaleVect(Radius,Radius,Length);//definition du vecteur de transformation d'échelle

  Scale(ScaleVect);

  CVector TmpVect;

  if (fabs(Up.GetZ()) > 1.0 - EPSILON)
  {
	TmpVect.Set(1,0,0);
    TmpUp.m_Value[2] = TmpUp.m_Value[2] < 0.0 ? -1.0 : 1.0;
  }
  else
  {
	//On calcule l'axe de rotation (il passe par le centre d'inertie de l'objet)
	TmpVect.Set(-Up.GetY(),Up.GetX(),0);
  }


  //On le fait tourner autour de l'axe de rotation
  //d'un angle correspodant à Z.
  CMatrixTransform	Trans;
  double angle=acos(TmpUp.GetZ())*INV_PI_180;//angle en degrés
  if(angle!=0.0)
  {
	Trans.AxisRotate(TmpVect,angle);
	Compose(Trans);
  }

  Trans.Translate(Origin);
  Compose(Trans);
}
