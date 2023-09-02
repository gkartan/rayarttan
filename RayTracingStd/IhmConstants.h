
/////////Constantes noms de fen�tres
#define RENDERVIEW_WND	"RenderView"
#define MAX_CHAR_KEYS	255
 

#ifdef _IHMMESSAGE
	int MS_MAJ_PROPERTIES=RegisterWindowMessage("MS_MAJ_PROPERTIES");		//Premier Param�tre : pointeur sur la childframe courante
	int	MS_SELECT_OTHER=RegisterWindowMessage("MS_SELECT_OTHER");			//Pas de param�tres
	int	MS_SELECT_OTHER_SECOND=RegisterWindowMessage("MS_SELECT_OTHER_SECOND");			//Pas de param�tres
	int MS_RANDOM=RegisterWindowMessage("MS_RANDOM");						//Pas de Param�tres
	int MS_RENDER=RegisterWindowMessage("MS_RENDER");						//Pas de Param�tres
	int MS_RENDER_FINISHED=RegisterWindowMessage("MS_RENDER_FINISHED");		//Pas de Param�tres
	int MS_STOP_RENDER=RegisterWindowMessage("MS_STOP_RENDER");				//Pas de Param�tres
	int MS_FILEOPEN=RegisterWindowMessage("MS_FILEOPEN");					//Premier param�tres -> le fichier
	int MS_FILEOPEN_SECOND=RegisterWindowMessage("MS_FILEOPEN_SECOND");		//Pas de Param�tres -> utilis� pour attendre l'ouverture de l'ihm
	int MS_FILENEW_SECOND=RegisterWindowMessage("MS_FILENEW_SECOND");		//Pas de Param�tres -> utilis� pour attendre l'ouverture de l'ihm
	int	MS_OPEN_TEXTURE=RegisterWindowMessage("MS_OPEN_TEXTURE");			//Premier param�tre : pointeur sur CString -> nom de la texture s�lectionn�

	int MS_REMOVE_PAGE=RegisterWindowMessage("MS_REMOVE_PAGE");				//Param�tre : type de la page --> utilis� dans les property page
	int MS_ADD_PAGE=RegisterWindowMessage("MS_ADD_PAGE");				//Param�tre : type de la page --> utilis� dans les property page
	int MS_UPDATE=RegisterWindowMessage("MS_UPDATE");
	int MS_SIZE_VIEW=RegisterWindowMessage("MS_SIZE_VIEW");

	int MS_ANTIPIRATAGE=RegisterWindowMessage("MS_ANTIPIRATAGE");			//Param�tre : 2 pointeurs sur CString -> Nom et cl� d'enregistrement
	int MS_TESTANTIPIRATAGE=RegisterWindowMessage("MS_TESTANTIPIRATAGE");		
	int MS_POSTANTIPIRATAGE=RegisterWindowMessage("MS_POSTANTIPIRATAGE");
	
	int MS_PARTIAL_RENDER=RegisterWindowMessage("MS_PARTIAL_RENDER");		//Message en mode screensaver pour indiquer � l'application qu'un rendu partiel est � sauvegarder

	int WM_DISPLAY_PIXEL=RegisterWindowMessage("WM_DISPLAY_PIXEL");
	int WM_SETSIZE=RegisterWindowMessage("WM_SETSIZE");
	int WM_INIT_OK=RegisterWindowMessage("WM_INIT_OK");
#else
	extern int MS_MAJ_PROPERTIES;
	extern int MS_SELECT_OTHER;
	extern int MS_SELECT_OTHER_SECOND;
	extern int MS_RANDOM;
	extern int MS_RENDER;
	extern int MS_RENDER_FINISHED;
	extern int MS_STOP_RENDER;
	extern int MS_REMOVE_PAGE;
	extern int MS_ADD_PAGE;
	extern int MS_FILEOPEN;
	extern int MS_FILEOPEN_SECOND;
	extern int MS_FILENEW_SECOND;
	extern int MS_OPEN_TEXTURE;
	extern int MS_SIZE_VIEW;
	extern int MS_ANTIPIRATAGE;
	extern int MS_TESTANTIPIRATAGE;
	extern int MS_POSTANTIPIRATAGE;
	extern int MS_UPDATE;
	extern int MS_PARTIAL_RENDER;

	extern int WM_DISPLAY_PIXEL;
	extern int WM_SETSIZE;
	extern int WM_INIT_OK;
#endif
