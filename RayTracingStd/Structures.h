//////////////////////////////////////////////////////////////////////////////////
#ifndef _STRUCTURESFILES
#define _STRUCTURESFILES

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int   dword;

struct S_RVB
{
  byte r;
  byte v;
  byte b;
};

#include "Constants.h"
class CAlgorithmModifier
{
public:
	CAlgorithmModifier()	{m_Threshold=DEFAULT_ALGORITHM_THRESHOLD; m_Depth=DEFAULT_ALGORITHM_DEPTH;}

	double	m_Threshold;
	long	m_Depth;
};


#endif

///////////////////////////////////////////////////////////////////////////////////
