#pragma warning(disable : 4530)

#include "BaseCamera.h"

CBaseCamera::CBaseCamera()
{
	m_Center=CCoord(0,0,0);  
	m_Focal=1;    
	m_Direct=CVector(0,0,1); 
	m_Top=CVector(0,0,1); 
	m_WidthScreen=1;	
	m_HeightScreen=1;	
}

CBaseCamera::~CBaseCamera()
{
}
