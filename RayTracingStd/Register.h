#include "LicenceDlg.h"
#include "ComputeRegisterKey.h"

class CRegister
{
public:
	static inline bool TestRegister(CString &Name,CString &Key);
	static inline bool TestNoRegister();
	static inline bool Verify(CString &Name,CString &Key);
};



bool CRegister::TestRegister(CString &Name,CString &Key)
{
	char sKeyValue[MAX_CHAR_KEYS];
	CString CompletePath("license.txt");

#ifdef _SCREENSAVER	
	GetSystemDirectory(sKeyValue,MAX_CHAR_KEYS);

	CompletePath.Format("%s\\license.txt",sKeyValue);
#endif
	char line[255];

	FILE *pfile=fopen(CompletePath.GetBuffer(CompletePath.GetLength()),"r");
	if(pfile!=NULL)
	{
		fgets(line,255,pfile);
		fclose(pfile);

		CString str(line);

		Name=str.Left(str.Find(";"));
		Key=str.Right(str.GetLength()-str.Find(";")-1);

		return true;
	}

	return false;
}
 
bool CRegister::TestNoRegister()
{
	char sKeyValue[MAX_CHAR_KEYS];
	CString CompletePath("./RayArtTan.ini");

#ifdef _SCREENSAVER	
	GetSystemDirectory(sKeyValue,MAX_CHAR_KEYS);

	CompletePath.Format("%s\\RayArtTan.ini",sKeyValue);
#endif

	///Affichage boite de rappel + fermeture du logiciel si + 30 jours
	GetPrivateProfileString("Time","Time","",sKeyValue,MAX_CHAR_KEYS,CompletePath);
	long Time=atol(sKeyValue);
	GetPrivateProfileString("Time","KeyTime","",sKeyValue,MAX_CHAR_KEYS,CompletePath);
	long KeyTime=atol(sKeyValue);

	if(Time==DEFAULT_TIME && KeyTime==DEFAULT_KEYTIME)
	{
		//Calcul valeur
		time_t theTime;
		time(&theTime);

		Time=theTime;
		KeyTime=theTime-sqrt(theTime)*KEY_MULTVALUE;

		CString	sTime;
		sTime.Format("%d",Time);
		CString sKeyTime;
		sKeyTime.Format("%d",KeyTime);

		WritePrivateProfileString("Time","Time",sTime,CompletePath);
		WritePrivateProfileString("Time","KeyTime",sKeyTime,CompletePath);
	} else {

		long VerifyKeyTime=Time-sqrt(Time)*KEY_MULTVALUE;

		if(VerifyKeyTime==KeyTime && KeyTime>0)
		{
			//Test 30 jours
			time_t theTime;
			time(&theTime);

			if(theTime-Time>TRENTEJOURSSEC || theTime-Time<0)
			{
				CLicenceDlg dlg;
				dlg.DoModal();

				return false;
			}

			return true;
		} else {
			CString str;
			str.LoadString(IDS_ERROR_FILEINI);
			AfxMessageBox(str);

			return false;
		}

	}

	return true;
}



bool CRegister::Verify(CString &Name,CString &Key)
{
	char sKeyValue[MAX_CHAR_KEYS];
	CString CompletePath("license.txt");

#ifdef _SCREENSAVER	
	GetSystemDirectory(sKeyValue,MAX_CHAR_KEYS);

	CompletePath.Format("%s\\license.txt",sKeyValue);
#endif

	std::string name(Name.GetBuffer(Name.GetLength()));
	std::string key(Key.GetBuffer(Key.GetLength()));

	if(CComputeRegisterKey::Verify(name,key))
	{
		FILE *pfile=fopen(CompletePath.GetBuffer(CompletePath.GetLength()),"w+");
		if(pfile!=NULL)
		{
			fputs(name.c_str(),pfile);
			fputs(";",pfile);
			fputs(key.c_str(),pfile);
			fclose(pfile);
		}

		return true;
	} else {
		return false;
	}
}
