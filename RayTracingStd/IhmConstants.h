
/////////Constantes noms de fenêtres
#define RENDERVIEW_WND	"RenderView"
#define MAX_CHAR_KEYS	255
 

#ifdef _IHMMESSAGE
	int MS_MAJ_PROPERTIES=RegisterWindowMessage("MS_MAJ_PROPERTIES");		//Premier Paramètre : pointeur sur la childframe courante
	int	MS_SELECT_OTHER=RegisterWindowMessage("MS_SELECT_OTHER");			//Pas de paramètres
	int	MS_SELECT_OTHER_SECOND=RegisterWindowMessage("MS_SELECT_OTHER_SECOND");			//Pas de paramètres
	int MS_RANDOM=RegisterWindowMessage("MS_RANDOM");						//Pas de Paramètres
	int MS_RENDER=RegisterWindowMessage("MS_RENDER");						//Pas de Paramètres
	int MS_RENDER_FINISHED=RegisterWindowMessage("MS_RENDER_FINISHED");		//Pas de Paramètres
	int MS_STOP_RENDER=RegisterWindowMessage("MS_STOP_RENDER");				//Pas de Paramètres
	int MS_FILEOPEN=RegisterWindowMessage("MS_FILEOPEN");					//Premier paramètres -> le fichier
	int MS_FILEOPEN_SECOND=RegisterWindowMessage("MS_FILEOPEN_SECOND");		//Pas de Paramètres -> utilisé pour attendre l'ouverture de l'ihm
	int MS_FILENEW_SECOND=RegisterWindowMessage("MS_FILENEW_SECOND");		//Pas de Paramètres -> utilisé pour attendre l'ouverture de l'ihm
	int	MS_OPEN_TEXTURE=RegisterWindowMessage("MS_OPEN_TEXTURE");			//Premier paramètre : pointeur sur CString -> nom de la texture sélectionné

	int MS_REMOVE_PAGE=RegisterWindowMessage("MS_REMOVE_PAGE");				//Paramètre : type de la page --> utilisé dans les property page
	int MS_ADD_PAGE=RegisterWindowMessage("MS_ADD_PAGE");				//Paramètre : type de la page --> utilisé dans les property page
	int MS_UPDATE=RegisterWindowMessage("MS_UPDATE");
	int MS_SIZE_VIEW=RegisterWindowMessage("MS_SIZE_VIEW");

	int MS_ANTIPIRATAGE=RegisterWindowMessage("MS_ANTIPIRATAGE");			//Paramètre : 2 pointeurs sur CString -> Nom et clé d'enregistrement
	int MS_TESTANTIPIRATAGE=RegisterWindowMessage("MS_TESTANTIPIRATAGE");		
	int MS_POSTANTIPIRATAGE=RegisterWindowMessage("MS_POSTANTIPIRATAGE");
	
	int MS_PARTIAL_RENDER=RegisterWindowMessage("MS_PARTIAL_RENDER");		//Message en mode screensaver pour indiquer à l'application qu'un rendu partiel est à sauvegarder

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
