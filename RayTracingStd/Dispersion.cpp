#include "Dispersion.h"

CDispersion::CDispersion()
{
	m_Ior_table.push_back(1.325); 
	m_Ior_table.push_back(1.333); 
	m_Ior_table.push_back(1.340); 

	m_WaveLength_table.push_back(CColor(1,0,0));
	m_WaveLength_table.push_back(CColor(0,1,0));
	m_WaveLength_table.push_back(CColor(0,0,1));
}//default value


///Initialise le tableau des couleurs
///en fonction de nombre d'échantillon
///permet d'aller plus vite lors des calculs --> évite l'interpolation en temps réel
void CDispersion::SetDispersionSamples(long Param)
{
	m_IsActif=true;
	m_WaveLength_table.clear();


	float Middle=Param/2;
	for(int i=0;i<Middle;i++)
	{
		float fi=float(i);
		m_WaveLength_table.push_back(CColor(1.0-fi/Middle,fi/Middle,0));
	}

	for(i=0;i<=Middle;i++)
	{
		float fi=float(i);
		m_WaveLength_table.push_back(CColor(0,1.0-fi/Middle,fi/Middle));
	}
}

/////On doit connaitre d'abord le nombre d'échantillon et le ratio de dispersion
/////Cet ior est l'ior du rouge
void		CDispersion::SetIor(float ior)
{
	m_IsActif=true;
	m_Ior_table.clear();

	int NumberSamples=m_WaveLength_table.size();
	for(int i=0;i<NumberSamples;i++)
	{
		m_Ior_table.push_back(ior*(1+(m_DispersionRatio-1)/(NumberSamples-i)));
	}
}