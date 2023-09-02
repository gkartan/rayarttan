#pragma	warning(disable : 4530) 
#pragma	warning(disable : 4096) 

#include "Noise3DGranite.h"
#include "Constants.h"
#include "Rand.h"
#include "TraceService.h"

CNoise3DGranite::CNoise3DGranite() 
:CNoise3D()
{
	m_alpha=2;
	m_beta=2;
	m_expn=20;
	m_Scale=4.0;
}

CNoise3DGranite::~CNoise3DGranite() 
{

}



double CNoise3DGranite::GetNoise(const CCoord &coord)
{
   CCoord	intern=coord*m_Scale;

   int i;
   double val,sum = 0;
   double p[3],scale = 1;

   p[0] = intern.GetX();
   p[1] = intern.GetY();
   p[2] = intern.GetZ();
   for (i=0;i<m_expn;i++) {
      val = getNoiseValue(p);
      sum += val / scale;
      scale *= m_alpha;
      p[0] *= m_beta;
      p[1] *= m_beta;
      p[2] *= m_beta;
   }
   return(sum);
}
