//*******************************************************************************************//
//* Classe de vérification de la clé d'enregistrement *//
//*****************************************************//
#ifndef _COMPUTEREGISTERKEY
#define _COMPUTEREGISTERKEY

#include <string>
#include <cmath>


class CComputeRegisterKey
{
public:
	static inline bool Verify(std::string&,std::string&);
	static inline void GiveKey(std::string&,std::string&);
};



bool CComputeRegisterKey::Verify(std::string &Name, std::string &Key)
{
	//création de la chaine
	std::string verify;

	GiveKey(Name,verify);

	if(Key.compare(verify)==0)
		return true;
	else
		return false;
}  

void CComputeRegisterKey::GiveKey(std::string &Name, std::string &Key)
{
	double theKey=0;

	for(int i=0;i<Name.size();i++)
	{
		theKey+=Name[i];
	}

	//La formule de calcul
	theKey=theKey/log(theKey);
	theKey=theKey*37+sqrt(theKey);
	theKey=theKey/100.;

	for(i=0;i<10;i++)
	{
		unsigned char Car=char(theKey);

		if(Car<48) Car+=48;
		if(Car>122) Car=cos(float(Car)/100.)*74+48;

		if((Car>57 && Car<65) || (Car>90 && Car<97)) Car-=10;

		Key+=Car;

		theKey=theKey-char(theKey);
		theKey=theKey*100.;
	}
}

#endif