////Pour le compilateur Borland

#include "BaseColor.h"

template <class T>
CBaseColor<T>::CBaseColor<T>()
{

}

template <class T>
CBaseColor<T>::CBaseColor<T>(const CBaseColor<T> &color)
{
	m_R=color.m_R;
	m_G=color.m_G;
	m_B=color.m_B;
	m_A=color.m_A;
}

template <class T>
CBaseColor<T>::CBaseColor<T>(T Red,T Green,T Blue)
{
	m_R=Red;
	m_G=Green;
	m_B=Blue;
}

template <class T>
CBaseColor<T>::~CBaseColor<T>()
{
}

template <class T>
CBaseColor<T>&	CBaseColor<T>::operator=(const CBaseColor<T>	&Origin)
{
	m_R=Origin.m_R;
	m_G=Origin.m_G;
	m_B=Origin.m_B;
	m_A=Origin.m_A;

	return (*this);
}


template <class T>
CBaseColor<T>&	CBaseColor<T>::operator*=(T cste)
{
	m_R=m_R*cste;
	m_G=m_G*cste;
	m_B=m_B*cste;

	return (*this);
}

template <class T>
CBaseColor<T>	CBaseColor<T>::operator+(const CBaseColor<T>	&Origin)
{
	CBaseColor<T> res;

	res.m_R=m_R+Origin.m_R;
	res.m_G=m_G+Origin.m_G;
	res.m_B=m_B+Origin.m_B;

	return (res);
}

template <class T>
CBaseColor<T>	CBaseColor<T>::operator*(const CBaseColor<T>	&Origin)
{
	CBaseColor<T> res;

	res.m_R=m_R*Origin.m_R;
	res.m_G=m_G*Origin.m_G;
	res.m_B=m_B*Origin.m_B;

	return (res);
}

template <class T>
CBaseColor<T>	CBaseColor<T>::operator*(T Coeff)
{
	CBaseColor<T> res;

	res.m_R=m_R*Coeff;
	res.m_G=m_G*Coeff;
	res.m_B=m_B*Coeff;

	return (res);
}

template <class T>
CBaseColor<T>	CBaseColor<T>::operator+(T Coeff)
{
	CBaseColor<T> res;

	res.m_R=m_R+Coeff;
	res.m_G=m_G+Coeff;
	res.m_B=m_B+Coeff;

	return (res);
}

template <class T>
void	CBaseColor<T>::SetMax(T &max)
{
    if (max<m_R)
      max=m_R;
    if (max<m_G)
      max=m_G;
    if (max<m_B)
      max=m_B;
}


template <class T>
void	CBaseColor<T>::SetLimits(T min,T max)
{
	if (min>m_R)
      m_R=min;
    if (min>m_G)
      m_G=min;
    if (min>m_B)
      m_B=min;

	if (max<m_R)
      m_R=max;
    if (max<m_G)
      m_G=max;
    if (max<m_B)
      m_B=max;
}


template <class T>
void	CBaseColor<T>::Print()
{
	CString str;
	str.Format("Color :: R : %.4f - G : %.4f - B : %.4f \n",m_R,m_G,m_B);
	OutputDebugString(str);
}


template <class T>
CBaseColor<T> CBaseColor<T>::Merge(const CBaseColor<T> & c,T m) const
{
  CBaseColor<T> res;

  // On borne le coefficient de melange par l'intervalle [0,1]
  if (m>1)
    m=1;
  if (m<0)
    m=0;

  res.m_R=(m_R*(1-m))+(c.m_R*m);
  res.m_G=(m_G*(1-m))+(c.m_G*m);
  res.m_B=(m_B*(1-m))+(c.m_B*m);

  return res;
}

template <class T>
float	CBaseColor<T>::Distance(const CBaseColor<T> &Origin)
{
	  return (float(fabs(m_R - Origin.m_R) +
			  fabs(m_G - Origin.m_G) +
			  fabs(m_B - Origin.m_B)));
}


#endif