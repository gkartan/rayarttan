#pragma	warning(disable : 4530)	//exceptions
#pragma	warning(disable : 4096)	//__decl

#include "Noise3D.h"
#include "Constants.h"
#include "Rand.h"
#include "TraceService.h"

CNoise3D::CNoise3D() 
{
	Init();
}

CNoise3D::~CNoise3D() 
{

}


void  CNoise3D::Init()
{
   int i, j, k;

   srand(INIT_RAND);

   for (i = 0 ; i < NOISE_B ; i++) 
   {
      m_p[i] = i;

      for (j = 0 ; j < 3 ; j++)
         m_g3[i][j] = (double)((rand() % (NOISE_B + NOISE_B)) - NOISE_B) / NOISE_B;

      normalize3(m_g3[i]);
   }

   while (--i) 
   {
      k = m_p[i];
      m_p[i] = m_p[j = rand() % NOISE_B];
      m_p[j] = k;
   }

   for (i = 0 ; i < NOISE_B + 2 ; i++) 
   {
      m_p[NOISE_B + i] = m_p[i];

      for (j = 0 ; j < 3 ; j++)
         m_g3[NOISE_B + i][j] = m_g3[i][j];
   }
}

////A REVOIR
////Normalisation d'un vecteur --> déjà fait
void  CNoise3D::normalize3(double v[3])
{
   double s;

   s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
   v[0] = v[0] / s;
   v[1] = v[1] / s;
   v[2] = v[2] / s;
}

double CNoise3D::getNoiseValue(double vec[3])
{
   int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
   double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
   int i, j;

   setup(0, bx0,bx1, rx0,rx1);
   setup(1, by0,by1, ry0,ry1);
   setup(2, bz0,bz1, rz0,rz1);

   i = m_p[ bx0 ];
   j = m_p[ bx1 ];

   b00 = m_p[ i + by0 ];
   b10 = m_p[ j + by0 ];
   b01 = m_p[ i + by1 ];
   b11 = m_p[ j + by1 ];

   t  = s_curve(rx0);
   sy = s_curve(ry0);
   sz = s_curve(rz0);

   q = m_g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
   q = m_g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
   a = lerp(t, u, v);

   q = m_g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
   q = m_g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
   b = lerp(t, u, v);

   c = lerp(sy, a, b);

   q = m_g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
   q = m_g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
   a = lerp(t, u, v);

   q = m_g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
   q = m_g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
   b = lerp(t, u, v);

   d = lerp(sy, a, b);

   return lerp(sz, c, d);
}

double CNoise3D::GetNoise(const CCoord &coord)
{
	double vector[3];
	vector[0]=coord.GetX();
	vector[1]=coord.GetY();
	vector[2]=coord.GetZ();
	return(getNoiseValue(vector));
}

