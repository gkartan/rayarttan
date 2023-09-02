/////Etat classe : VALIDE
#ifndef _CDISPERSION
#define _CDISPERSION

#include "Color.h"
#include <vector>
//********************Definit une structure de donnée***************************/
//** contenant une table des différentes indice de réfraction en fonction de la couleur*/
//** permet de gérer le phénomène de dispersion
class	CDispersion
{
public:
	CDispersion();

	void			SetDispersionSamples(long Param);
	inline void		SetDispersionRatio(float Param)	{m_DispersionRatio=Param; m_IsActif=true;}
	void			SetIor(float);

	inline bool		IsActif()			const		{return m_IsActif;};
	inline CColor	GetColor(long Param) const		{return m_WaveLength_table[Param];}
	inline float	GetIor(long Param)  const		{return m_Ior_table[Param];}
	inline long		GetCountSamples()	const		{return m_WaveLength_table.size();}

private:
	float				m_DispersionRatio;
	bool				m_IsActif;
	std::vector<float>	m_Ior_table;
	std::vector<CColor>	m_WaveLength_table;	
};

#endif
