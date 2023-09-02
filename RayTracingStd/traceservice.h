#pragma warning(disable : 4096)

#ifndef MOD_TRACE_SERVICE
#define MOD_TRACE_SERVICE

////////////////////////////////////////////////////////////////////////////////////////////////
//      Ce fichier déclare les fonctions et macros assurant la gestion transparente           //
//      du lien entre un programme quelconque et le serveur de trace "TRACEUR.EXE"            //
////////////////////////////////////////////////////////////////////////////////////////////////
//      Versions du traceur compatibles avec cette version de TraceService :                  //
//      => à partir de V3.0.0                                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            //
//   => Traceur.exe peut être enregistré manuellement (Traceur.exe /RegServer)                //
//      dans le cas contraire, il s'enregistre automatiquement au démarrage                   //
//      S'il n'est pas enregistré, le traceur ne démarre pas mais le client                   //
//      ne plante pas pour autant.                                                            //
//   => Ne pas oublier d'inclure le fichier "TraceService.cpp" dans chaque projet client      //
//      (chaque DLL/EXE doit inclure TraceService.cpp)                                        //
//   => Si le projet utilise les "precompiled headers", il faut invalider cette option        //
//      pour le fichier TraceService.cpp                                                      //
//      (selectionner ce fichier dans la fenêtre "settings" du projet puis invalider ...)     //
//   => TOUS les projets qui désirent envoyer des traces doivent appeler une fonction         //
//      d'initialisation de trace, même si le flux destinataire est le même                   //
//      (par ex: 1 EXE + 3 DLL => 4 appels d'init)                                            //
//   => Les fonctions de trace ne désallouent pas les chaines de caractères qui leur          //
//      sont fournies en argument (bien sûr !)                                                //
//                                                                                            //
//   => POUR SUPPRIMER LES TRACES DANS LE PROGRAMME CLIENT :                                  //
//      Toutes les fonctions et macros de trace sont exclues de la compilation                //
//      lorsque TRACER_DISABLED est defini dans le projet.                                    //
//      Ainsi il n'y aucune de perte de performance due au traceur                            //
//      lorsqu'il n'est plus utilisé (en mode "RELEASE" par exemple).                         //
//                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
//                                 OPTIONS DE TRACE                                           //
////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            //
// * MODE DE COMMUNICATION *                                                                  //
//   => précisé lors de l'initialisation (enuméré TRACER_COM_MODE), sinon le mode             //
//      COM_SENDMESSAGES est utilisé par défaut :                                             //
//                                                                                            //
//      COM_MULTITHREAD : Dans ce mode les traces sont envoyées directement                   //
//                        au serveur à partir de n'importe quel thread. Ce mode est le        //
//                        plus efficace en temps d'exécution.                                 //
//                        INCONVENIENT: Ce mode ne fonctionne pas lorsque le client           //
//                        utilise des librairies incompatibles avec le mode multi-thread      //
//                        de COM/DCOM (par ex. OLE, MAPI, ActiveX)                            //
//                        Dans ce cas, il faut utiliser l'un des deux modes suivants:         //
//                                                                                            //
//      COM_SINGLETHREAD: Les traces sont envoyées directement au serveur, mais seulement     //
//                        à partir du thread dans lequel la fonction d'init a été appelée     //
//                        (_TRACE_INIT ou _TRACE_LINKINIT). Un appel à partir d'un autre      //
//                        thread échouera (trace perdue).                                     //
//                        Ce mode, compatible avec toutes les librairies, doit-être           //
//                        utilisé lorsque COM_MULTITHREAD ne fonctionne pas.                  //
//                        Cependant, si le client necessite l'envoi de traces à partir        //
//                        de plusieurs threads (et bien sûr si COM_MULTITHREAD ne             //
//                        fonctionne pas), il faut utiliser le dernier mode disponible:       //
//   => MODE PAR DEFAUT:                                                                      //
//      COM_SENDMESSAGES: Les traces sont envoyées au serveur via un thread dédié. Les        //
//                        macros & fonctions de trace font appel à ce thread par envoi de     //
//                        messages, ce mode fonctionne donc pour tout type de client et       //
//                        les traces peuvent être envoyées à partir de tous les threads.      //
//                        INCONVENIENT: C'est la méthode la plus gourmande en CPU ...         //
//                                                                                            //
// * COULEUR DE TRACE *                                                                       //
//   => Utilisé lors de chaque appel à une fonction de trace                                  //
//   => Format de l'option COULEUR   : 0x00BBVVRR                                             //
//   => Les couleurs par défaut sont :                                                        //
        #define _TRDEF_FUNC_COL        0x00000000  // noir   (fonction _FTRACE)               //
        #define _TRDEF_INFO_COL        0x00FF0000  // bleu   (fonction _TRACE_INFO)           //
        #define _TRDEF_WARNING_COL     0x000066EE  // orange (fonction _TRACE_WARNING)        //
        #define _TRDEF_ERROR_COL       0x000000FF  // rouge  (fonction _TRACE_ERROR)          //
        #define _TRDEF_RAWDATA_COL     0x0022AA00  // vert   (fonction _TRACE_RAWDATA)        //
//                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////
    
    
////////////////////////////////////////////////////////////////////////////////////////////////
//                                 MACROS/FONCTIONS                                           //
////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                            //
// Dans la suite, le type appelé "string" signifie "unsigned short*" ou "char *"              //
// (UNICODE/non UNICODE), indépendemment du mode de compilation du projet.                    //
// Il est ainsi possible de mélanger des traces UNICODE avec des traces non UNICODE à         //
// condition que toutes les chaines soient du même type au sein du même appel.                //
// (par ex lors de l'appel à TRACE_INFO, "texte" et "module" doivent être du même type)       //
//                                                                                            //
//                                                                                            //
//                                                                                            //
// ***************************                                                                //
// *  FORMATTAGE DE CHAINES  *                                                                //
// ***************************                                                                //
//                                                                                            //
// string _STR (string format [, argument, ...] )                                             //
//              => Description: - Retourne une chaine allouée et formatée par sprintf         //
//                              - Cette chaine sera automatiquement désallouée et peut donc   //
//                                être utitisée directement en tant qu'argument de type       //
//                                string dans les fonctions d'émission de traces.             //
//                              - Taille de la chaine allouée :                               //
                                  #define _STR_ALLOCSIZE 512                                  //
//                                                                                            //
//                                                                                            //
//                                                                                            //
// ******************                                                                         //
// * INITIALISATION *                                                                         //
// ******************                                                                         //
//                                                                                            //
// int _TRACE_INITOK ( )                                                                      //
//               => Paramètres :                                                              //
//               => Description: - Retourne 0 si la connexion au serveur n'est pas établie    //
//                                                                                            //
// int _TRACE_INIT (string nomprog [, TRACER_COM_MODE ModeCOM, unsigned int TimeOut])         //
//             => Paramètres : * "nomprog" est le nom de l'appli                              //
//                  (option)   * "ModeCOM" est le mode d'envoi des traces                     //
//                  (option)   * "TimeOut" est le temps d'attente de création du thread       //
//                                   (dans le cas COM_SENDMESSAGES)                           //
//             => Description: - Etablit une connexion avec le serveur vers un nouveau flux   //
//                               de traces (après avoir fermé la connexion existante avec     //
//                               un autre flux si besoin)                                     //
//                             - Retourne 0 en cas d'erreur                                   //
//                                                                                            //
// int _TRACE_LINKINIT (string nomprog, string module [, TRACER_COM_MODE ModeCOM,             //
//                                                       unsigned int TimeOut])               //
//                 => Paramètres : * "nomprog" est le nom du flux existant                    //
//                                 * "module" est le nom de l'appli                           //
//                      (option)   * "ModeCOM" est le mode d'envoi des traces                 //
//                      (option)   * "TimeOut" est le temps d'attente de création du thread   //
//                                   (dans le cas COM_SENDMESSAGES)                           //
//                 => Description: - Etablit une connexion avec le serveur vers un flux de    //
//                                   traces dèjà existant (après avoir fermé la connexion     //
//                                   existante avec un autre flux si besoin)                  //
//                                 - Si aucun flux de traces nommé "progname" n'existe dans   //
//                                   le serveur en mode "ouvert" (EN COURS), alors un         //
//                                   nouveau flux est créé.                                   //
//                                 - Permet donc de grouper les traces provenant de           //
//                                   plusieurs programmes dans le même flux/fichier.          //
//                                   (Le premier d'entre eux appelle _TRACE_INIT ou           //
//                                   _TRACE_LINKINIT, les autres appellent _TRACE_LINKINIT)   //
//                                 - Retourne 0 en cas d'erreur                               //
//                                                                                            //
// int _TRACE_CLOSE ( )                                                                       //
//              => Paramètres : -                                                             //
//              => Description: - Ferme la connexion avec le serveur                          //
//                              - Retourne 0 en cas d'erreur                                  //
//                                                                                            //
//                                                                                            //
//                                                                                            //
// ******************************************                                                 //
// * EMISSION DE TRACES VERS LE FLUX OUVERT *                                                 //
// ******************************************                                                 //
//                                                                                            //
// _FTRACE (string texte [, string module, ushort priorité, long couleur])                    //
// _FTRACE (string texte, ushort priorité [, long couleur])                                   //
//         => Paramètres : * "texte" est le texte à envoyer au serveur                        //
//              (option)   * "module" est le nom du module/catégorie                          //
//                           apparaissant dans la colonne "Module" du serveur                 //
//              (option)   * "priorité" est le niveau de priorité (1<= priorité <=255)        //
//                           1 est la priorité maximale                                       //
                             #define _TRDEF_PRIORITY 10 // valeur par défaut                  //
//                           L'IHM du traceur permet de choisir le niveau max de priorité     //
//                           autorisé, l'opérateur peut ainsi optimiser la quantité de        //
//                           données entre client/traceur                                     //
//              (option)   * "couleur" est la couleur optionnelle (format: 0x00BVR)           //
//         => Description: - Envoi d'un message "entrée fonction"                             //
//                         - Envoi automatique d'un message "sortie fonction"                 //
//                         - Généralement placé sur la 1ére ligne d'une fonction/méthode      //
//                         - "texte" contient le nom de la méthode + paramètres (cf _STR)     //
//                         - LE SECOND ARG. PEUT ÊTRE AU CHOIX UN "MODULE" OU UNE "PRIORITE"  //
//                                                                                            //
// _TRACE_INFO (string texte [, string module, ushort priorité, long couleur])                //
// _TRACE_INFO (string texte, ushort priorité [, long couleur])                               //
//             => Paramètres : * cf _FTRACE                                                   //
//             => Description: - Envoi d'un message d'information                             //
//                                                                                            //
// _TRACE_WARNING (string texte [, string module, ushort priorité, long couleur])             //
// _TRACE_WARNING (string texte, ushort priorité [, long couleur])                            //
//             => Paramètres : * cf _FTRACE                                                   //
//             => Description: - Envoi d'un message d'avertissement                           //
//                                                                                            //
// _TRACE_ERROR (string texte [, string module, ushort priorité, long couleur])               //
// _TRACE_ERROR (string texte, ushort priorité [, long couleur])                              //
//             => Paramètres : * cf _FTRACE                                                   //
//             => Description: - Envoi d'un message d'erreur                                  //
//                                                                                            //
// _TRACE_RAWDATA (string texte, void* pData, ulong taille                                    //
//                 [, string module, ushort priorité, long couleur])                          //
// _TRACE_RAWDATA (string texte, void* pData, ulong taille, ushort priorité [, long couleur]) //
//             => Paramètres : * cf _FTRACE                                                   //
//                             * "pData" pointe sur la zone mémoire à tracer                  //
//                             * "size"  est la taille de la zone à tracer (en octet)         //
//             => Description: - Envoi d'un message contenant des données binaires            //
//                                                                                            //
//                                                                                            //
//                                                                                            //
// *****************************************                                                  //
// * EMISSION DE TRACES VERS UN AUTRE FLUX *                                                  //
// *****************************************                                                  //
//                                                                                            //
//  fonctions utiles par ex. pour envoyer des traces vers le "journal de bord" d'une l'appli  //
//  (flux permanent dans le traceur)                                                          //
//                                                                                            //
// _FTRACE_TO (string nomprog, string texte [, string module, ushort priorité, long couleur]) //
// _FTRACE_TO (string nomprog, string texte, ushort priorité [, long couleur])                //
//         => Paramètres : * cf _FTRACE                                                       //
//                         * "nomprog" est le nom du flux destinataire                        //
//         => Description: - Envoi d'un message "entrée fonction" vers le flux "nomprog"      //
//                         - Envoi automatique d'un message "sortie fonction"                 //
//                         - Généralement placé sur la 1ére ligne d'une fonction/méthode      //
//                         - "texte" contient le nom de la méthode + paramètres (cf _STR)     //
//                                                                                            //
// _TRACE_INFO_TO (string nomprog, string texte                                               //
//                 [, string module, ushort priorité, long couleur])                          //
// _TRACE_INFO_TO (string nomprog, string texte, ushort priorité [, long couleur])            //
//             => Paramètres : * cf _FTRACE_TO                                                //
//             => Description: - Envoi d'un message d'information                             //
//                                                                                            //
// _TRACE_WARNING_TO (string nomprog, string texte                                            //
//                    [, string module, ushort priorité, long couleur])                       //
// _TRACE_WARNING_TO (string nomprog, string texte, ushort priorité [, long couleur])         //
//             => Paramètres : * cf _FTRACE_TO                                                //
//             => Description: - Envoi d'un message d'avertissement                           //
//                                                                                            //
// _TRACE_ERROR_TO (string nomprog, string texte                                              //
//                  [, string module, ushort priorité, long couleur])                         //
// _TRACE_ERROR_TO (string nomprog, string texte, ushort priorité [, long couleur])           //
//             => Paramètres : * cf _FTRACE_TO                                                //
//             => Description: - Envoi d'un message d'erreur                                  //
//                                                                                            //
// _TRACE_RAWDATA_TO (string nomprog, string texte, void* pData, ulong taille                 //
//                    [, string module, ushort priorité, long couleur])                       //
// _TRACE_RAWDATA_TO (string nomprog, string texte, void* pData, ulong taille,                //
//                    ushort priorité [, long couleur])                                       //
//             => Paramètres : * cf _FTRACE_TO                                                //
//                             * "pData" pointe sur la zone mémoire à tracer                  //
//                             * "size"  est la taille de la zone à tracer (en octet)         //
//             => Description: - Envoi d'un message contenant des données binaires            //
//                                                                                            //
//                                                                                            //
//                                                                                            //
// *********************************************************                                  //
// * FONCTIONS DE TRACE COMPILEES EN MODE DEBUG SEULEMENT  *                                  //
// *      (lorsque _DEBUG est défini dans le projet)       *                                  //
// *********************************************************                                  //
//                                                                                            //
// _DSTR(...),                                                                                //
//                                                                                            //
// _DFTRACE(...),                                                                             //
// _DTRACE_INFO(...),                                                                         //
// _DTRACE_WARNING(...),                                                                      //
// _DTRACE_ERROR(...),                                                                        //
// _DTRACE_RAWDATA(...),                                                                      //
//                                                                                            //
// _DFTRACE_TO(...),                                                                          //
// _DTRACE_INFO_TO(...),                                                                      //
// _DTRACE_WARNING_TO(...),                                                                   //
// _DTRACE_ERROR_TO(...),                                                                     //
// _DTRACE_RAWDATA_TO(...),                                                                   //
//                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
////////////////////////////////////////////////////////////////////////////////////////////////
//            DEFINITION DES FONCTIONS ET MACROS PERMETTANT L'ENVOI DE TRACES                 //
////////////////////////////////////////////////////////////////////////////////////////////////
    
    
////////////////////////////////////////////////////////////////////////////////////////////////
// Types d'événement    
enum EVENT_TYPE { TRACE_INITPROG_EVENT=1, TRACE_EXITPROG_EVENT,    
                  TRACE_ENTER_FUNC, TRACE_EXIT_FUNC,    
                  TRACE_INFO_EVENT, TRACE_WARNING_EVENT, TRACE_ERROR_EVENT,    
                  TRACE_RAWDATA_EVENT,
                  TRACE_NEW_EVENT, TRACE_DELETE_EVENT,
                  ENDOF_EVENT_TYPE
                };


// si le fichier n'est pas inclu par le serveur
#if !defined(MOD_TRACER_DEFINES)


////////////////////////////////////////////////////////////////////////////////////////////////
// Modes de communication
enum TRACER_COM_MODE { COM_MULTITHREAD, COM_SINGLETHREAD, COM_SENDMESSAGES };


#ifndef TRACER_DISABLED // si les traces sont activées



////////////////////////////////////////////////////////////////////////////////////////////////
// Fonctions d'initialisation et de trace utilisées par les macros
int _TRACE_INIT(const char * ProgramName, TRACER_COM_MODE ComMode = COM_SENDMESSAGES, unsigned int timeout = 5000);
int _TRACE_INIT(const unsigned short * ProgramName, TRACER_COM_MODE ComMode = COM_SENDMESSAGES, unsigned int timeout = 5000);
int _TRACE_LINKINIT(const char * ProgramName, const char * ModuleName, TRACER_COM_MODE ComMode = COM_SENDMESSAGES, unsigned int timeout = 5000);
int _TRACE_LINKINIT(const unsigned short * ProgramName, const unsigned short * ModuleName, TRACER_COM_MODE ComMode = COM_SENDMESSAGES, unsigned int timeout = 5000);
int TraceService_Close();
void TraceService_SendTrace(EVENT_TYPE Type, const char * text, unsigned char priority, long color,
                            const char * ModuleName, const char * TargetStream = 0);
void TraceService_SendTrace(EVENT_TYPE Type, const unsigned short* text, unsigned char priority,
                            long color, const unsigned short * ModuleName, const unsigned short * TargetStream = 0);
void TraceService_SendBinTrace(const void* pData, unsigned long size, const char * title, unsigned char priority,
                               long color, const char * ModuleName, const char * TargetStream = 0);
void TraceService_SendBinTrace(const void* pData, unsigned long size, const unsigned short * title, unsigned char priority,
                               long color, const unsigned short * ModuleName, const unsigned short * TargetStream = 0);


//////////////////////////////////////////////////////////////////////////////////////////
// Classe CTraceService : Utilisée par les macros
//     Permet l'envoi d'une trace d'entrée de méthode (constructeur)
//     puis l'envoi automatique d'une trace de sortie de méthode (destructeur)
//////////////////////////////////////////////////////////////////////////////////////////
class CTraceService
{
public:
	CTraceService(const char*           FuncName, const char           *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_FUNC_COL);
	CTraceService(const unsigned short* FuncName, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_FUNC_COL);
	CTraceService(const char*           FuncName, unsigned char priority, long color = _TRDEF_INFO_COL);
	CTraceService(const unsigned short* FuncName, unsigned char priority, long color = _TRDEF_INFO_COL);
	~CTraceService();
protected:
	inline void Constructor(const unsigned short* FuncName, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_FUNC_COL);
	unsigned short * m_FuncName;
	unsigned short * m_Module;
	unsigned char    m_Priority;
	long             m_Color;
};
class CTraceService_TO
{
public:
	CTraceService_TO(const char*           nomprog, const char*           FuncName, const char           *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_FUNC_COL);
	CTraceService_TO(const unsigned short* nomprog, const unsigned short* FuncName, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_FUNC_COL);
	CTraceService_TO(const char*           nomprog, const char*           FuncName, unsigned char priority, long color = _TRDEF_INFO_COL);
	CTraceService_TO(const unsigned short* nomprog, const unsigned short* FuncName, unsigned char priority, long color = _TRDEF_INFO_COL);
	~CTraceService_TO();
protected:
	inline void Constructor(const unsigned short* nomprog, const unsigned short* FuncName, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_FUNC_COL);
	unsigned short * m_FuncName;
	unsigned short * m_Module;
	unsigned short * m_NomProg;
	unsigned char    m_Priority;
	long             m_Color;
};


//////////////////////////////////////////////////////////////////////////////////////////
// MACROS  de trace utilisées par le client
//////////////////////////////////////////////////////////////////////////////////////////

int     _TRACE_INITOK();
#define _TRACE_CLOSE()   TraceService_Close();

const char*           _STR(const char* format, ...);
const unsigned short* _STR(const unsigned short* format, ...);
#define     _FTRACE  CTraceService lTraceObject
inline void _TRACE_INFO   (const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL)           {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority,color,module);}
inline void _TRACE_INFO   (const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL) {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority,color,module);}
inline void _TRACE_INFO   (const char*           str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority,color,0);}
inline void _TRACE_INFO   (const unsigned short* str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority,color,0);}
inline void _TRACE_WARNING(const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL)          {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority, color,module);}
inline void _TRACE_WARNING(const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL){TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority, color,module);}
inline void _TRACE_WARNING(const char*           str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority,color,0);}
inline void _TRACE_WARNING(const unsigned short* str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority,color,0);}
inline void _TRACE_ERROR  (const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL)          {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority, color,module);}
inline void _TRACE_ERROR  (const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL){TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority, color,module);}
inline void _TRACE_ERROR  (const char*           str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority,color,0);}
inline void _TRACE_ERROR  (const unsigned short* str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority,color,0);}
inline void _TRACE_RAWDATA(const char*           title, const void* pData, long size, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL)          {TraceService_SendBinTrace(pData, size, title, priority, color,module);}
inline void _TRACE_RAWDATA(const unsigned short* title, const void* pData, long size, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL){TraceService_SendBinTrace(pData, size, title, priority, color,module);}
inline void _TRACE_RAWDATA(const char*           title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {TraceService_SendBinTrace(pData, size, title, priority, color,0);}
inline void _TRACE_RAWDATA(const unsigned short* title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {TraceService_SendBinTrace(pData, size, title, priority, color,0);}
#define     _FTRACE_TO  CTraceService_TO lTraceObject
inline void _TRACE_INFO_TO   (const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL)           {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority, color,module,nomprog);}
inline void _TRACE_INFO_TO   (const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL) {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority, color,module,nomprog);}
inline void _TRACE_INFO_TO   (const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority,color,0,nomprog);}
inline void _TRACE_INFO_TO   (const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority,color,0,nomprog);}
inline void _TRACE_WARNING_TO(const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL)          {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority, color,module,nomprog);}
inline void _TRACE_WARNING_TO(const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL){TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority, color,module,nomprog);}
inline void _TRACE_WARNING_TO(const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority,color,0,nomprog);}
inline void _TRACE_WARNING_TO(const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority,color,0,nomprog);}
inline void _TRACE_ERROR_TO  (const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL)          {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority, color,module,nomprog);}
inline void _TRACE_ERROR_TO  (const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL){TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority, color,module,nomprog);}
inline void _TRACE_ERROR_TO  (const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority,color,0,nomprog);}
inline void _TRACE_ERROR_TO  (const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority,color,0,nomprog);}
inline void _TRACE_RAWDATA_TO(const char*           nomprog, const char*           title, const void* pData, long size, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL)          {TraceService_SendBinTrace(pData, size, title, priority, color,module,nomprog);}
inline void _TRACE_RAWDATA_TO(const unsigned short* nomprog, const unsigned short* title, const void* pData, long size, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL){TraceService_SendBinTrace(pData, size, title, priority, color,module,nomprog);}
inline void _TRACE_RAWDATA_TO(const char*           nomprog, const char*           title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {TraceService_SendBinTrace(pData, size, title, priority, color,0,nomprog);}
inline void _TRACE_RAWDATA_TO(const unsigned short* nomprog, const unsigned short* title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {TraceService_SendBinTrace(pData, size, title, priority, color,0,nomprog);}

#ifdef _DEBUG // Traces en mode DEBUG seulement

#define     _DSTR _STR
#define     _DFTRACE  CTraceService lTraceObject
inline void _DTRACE_INFO   (const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL)           {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority, color,module);}
inline void _DTRACE_INFO   (const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL) {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority, color,module);}
inline void _DTRACE_INFO   (const char*           str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority,color,0);}
inline void _DTRACE_INFO   (const unsigned short* str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority,color,0);}
inline void _DTRACE_WARNING(const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL)          {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority, color,module);}
inline void _DTRACE_WARNING(const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL){TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority, color,module);}
inline void _DTRACE_WARNING(const char*           str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority,color,0);}
inline void _DTRACE_WARNING(const unsigned short* str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority,color,0);}
inline void _DTRACE_ERROR  (const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL)          {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority, color,module);}
inline void _DTRACE_ERROR  (const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL){TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority, color,module);}
inline void _DTRACE_ERROR  (const char*           str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority,color,0);}
inline void _DTRACE_ERROR  (const unsigned short* str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority,color,0);}
inline void _DTRACE_RAWDATA(const char*           title, const void* pData, long size, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL)          {TraceService_SendBinTrace(pData, size, title, priority, color,module);}
inline void _DTRACE_RAWDATA(const unsigned short* title, const void* pData, long size, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL){TraceService_SendBinTrace(pData, size, title, priority, color,module);}
inline void _DTRACE_RAWDATA(const char*           title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {TraceService_SendBinTrace(pData, size, title, priority, color,0);}
inline void _DTRACE_RAWDATA(const unsigned short* title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {TraceService_SendBinTrace(pData, size, title, priority, color,0);}
#define     _DFTRACE_TO  CTraceService_TO lTraceObject
inline void _DTRACE_INFO_TO   (const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL)           {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority, color,module,nomprog);}
inline void _DTRACE_INFO_TO   (const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL) {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority, color,module,nomprog);}
inline void _DTRACE_INFO_TO   (const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority,color,0,nomprog);}
inline void _DTRACE_INFO_TO   (const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {TraceService_SendTrace(TRACE_INFO_EVENT, str, priority,color,0,nomprog);}
inline void _DTRACE_WARNING_TO(const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL)          {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority, color,module,nomprog);}
inline void _DTRACE_WARNING_TO(const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL){TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority, color,module,nomprog);}
inline void _DTRACE_WARNING_TO(const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority,color,0,nomprog);}
inline void _DTRACE_WARNING_TO(const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {TraceService_SendTrace(TRACE_WARNING_EVENT, str, priority,color,0,nomprog);}
inline void _DTRACE_ERROR_TO  (const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL)          {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority, color,module,nomprog);}
inline void _DTRACE_ERROR_TO  (const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL){TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority, color,module,nomprog);}
inline void _DTRACE_ERROR_TO  (const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority,color,0,nomprog);}
inline void _DTRACE_ERROR_TO  (const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {TraceService_SendTrace(TRACE_ERROR_EVENT, str, priority,color,0,nomprog);}
inline void _DTRACE_RAWDATA_TO(const char*           nomprog, const char*           title, const void* pData, long size, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL)          {TraceService_SendBinTrace(pData, size, title, priority, color,module,nomprog);}
inline void _DTRACE_RAWDATA_TO(const unsigned short* nomprog, const unsigned short* title, const void* pData, long size, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL){TraceService_SendBinTrace(pData, size, title, priority, color,module,nomprog);}
inline void _DTRACE_RAWDATA_TO(const char*           nomprog, const char*           title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {TraceService_SendBinTrace(pData, size, title, priority, color,0,nomprog);}
inline void _DTRACE_RAWDATA_TO(const unsigned short* nomprog, const unsigned short* title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {TraceService_SendBinTrace(pData, size, title, priority, color,0,nomprog);}


#else // mode release

inline const char*           _DSTR(const char* format,...)           {return(0);}
inline const unsigned short* _DSTR(const unsigned short* format,...) {return(0);}
#define     _DFTRACE //
inline void _DTRACE_INFO   (const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL)           {}
inline void _DTRACE_INFO   (const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL) {}
inline void _DTRACE_INFO   (const char*           str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _DTRACE_INFO   (const unsigned short* str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _DTRACE_WARNING(const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL)          {}
inline void _DTRACE_WARNING(const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL){}
inline void _DTRACE_WARNING(const char*           str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _DTRACE_WARNING(const unsigned short* str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _DTRACE_ERROR  (const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL)          {}
inline void _DTRACE_ERROR  (const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL){}
inline void _DTRACE_ERROR  (const char*           str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _DTRACE_ERROR  (const unsigned short* str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _DTRACE_RAWDATA(const char*           title, const void* pData, long size, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL)          {}
inline void _DTRACE_RAWDATA(const unsigned short* title, const void* pData, long size, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL){}
inline void _DTRACE_RAWDATA(const char*           title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}
inline void _DTRACE_RAWDATA(const unsigned short* title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}
#define     _DFTRACE_TO //
inline void _DTRACE_INFO_TO   (const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL)           {}
inline void _DTRACE_INFO_TO   (const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL) {}
inline void _DTRACE_INFO_TO   (const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _DTRACE_INFO_TO   (const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _DTRACE_WARNING_TO(const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL)          {}
inline void _DTRACE_WARNING_TO(const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL){}
inline void _DTRACE_WARNING_TO(const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _DTRACE_WARNING_TO(const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _DTRACE_ERROR_TO  (const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL)          {}
inline void _DTRACE_ERROR_TO  (const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL){}
inline void _DTRACE_ERROR_TO  (const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _DTRACE_ERROR_TO  (const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _DTRACE_RAWDATA_TO(const char*           nomprog, const char*           title, const void* pData, long size, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL)          {}
inline void _DTRACE_RAWDATA_TO(const unsigned short* nomprog, const unsigned short* title, const void* pData, long size, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL){}
inline void _DTRACE_RAWDATA_TO(const char*           nomprog, const char*           title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}
inline void _DTRACE_RAWDATA_TO(const unsigned short* nomprog, const unsigned short* title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}

#endif // _DEBUG


////////////////////////////////////////////////////////////////////////////////////////////////////
// Si les traces sont désactivées
#else


inline int  _TRACE_INITOK() {return(1);}
inline int _TRACE_INIT(const char * ProgramName, TRACER_COM_MODE ComMode = COM_MULTITHREAD, unsigned int timeout = 5000) {return 1;}
inline int _TRACE_INIT(const unsigned short * ProgramName, TRACER_COM_MODE ComMode = COM_MULTITHREAD, unsigned int timeout = 5000) {return 1;}
inline int _TRACE_LINKINIT(const char * ProgramName, const char * ModuleName, TRACER_COM_MODE ComMode = COM_MULTITHREAD, unsigned int timeout = 5000) {return 1;}
inline int _TRACE_LINKINIT(const unsigned short * ProgramName, const unsigned short * ModuleName, TRACER_COM_MODE ComMode = COM_MULTITHREAD, unsigned int timeout = 5000) {return 1;}
#define _TRACE_CLOSE()   1

inline const char*           _STR(const char* format,...)           {return(0);}
inline const unsigned short* _STR(const unsigned short* format,...) {return(0);}
#define     _FTRACE 
inline void _TRACE_INFO   (const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL)           {}
inline void _TRACE_INFO   (const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL) {}
inline void _TRACE_INFO   (const char*           str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _TRACE_INFO   (const unsigned short* str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _TRACE_WARNING(const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL)          {}
inline void _TRACE_WARNING(const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL){}
inline void _TRACE_WARNING(const char*           str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _TRACE_WARNING(const unsigned short* str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _TRACE_ERROR  (const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL)          {}
inline void _TRACE_ERROR  (const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL){}
inline void _TRACE_ERROR  (const char*           str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _TRACE_ERROR  (const unsigned short* str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _TRACE_RAWDATA(const char*           title, const void* pData, long size, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL)          {}
inline void _TRACE_RAWDATA(const unsigned short* title, const void* pData, long size, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL){}
inline void _TRACE_RAWDATA(const char*           title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}
inline void _TRACE_RAWDATA(const unsigned short* title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}
#define     _FTRACE_TO 
inline void _TRACE_INFO_TO   (const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL)           {}
inline void _TRACE_INFO_TO   (const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL) {}
inline void _TRACE_INFO_TO   (const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _TRACE_INFO_TO   (const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _TRACE_WARNING_TO(const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL)          {}
inline void _TRACE_WARNING_TO(const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL){}
inline void _TRACE_WARNING_TO(const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _TRACE_WARNING_TO(const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _TRACE_ERROR_TO  (const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL)          {}
inline void _TRACE_ERROR_TO  (const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL){}
inline void _TRACE_ERROR_TO  (const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _TRACE_ERROR_TO  (const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _TRACE_RAWDATA_TO(const char*           nomprog, const char*           title, const void* pData, long size, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL)          {}
inline void _TRACE_RAWDATA_TO(const unsigned short* nomprog, const unsigned short* title, const void* pData, long size, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL){}
inline void _TRACE_RAWDATA_TO(const char*           nomprog, const char*           title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}
inline void _TRACE_RAWDATA_TO(const unsigned short* nomprog, const unsigned short* title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}


#define     _DSTR          _STR
#define     _DFTRACE 
inline void _DTRACE_INFO   (const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL)           {}
inline void _DTRACE_INFO   (const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL) {}
inline void _DTRACE_INFO   (const char*           str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _DTRACE_INFO   (const unsigned short* str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _DTRACE_WARNING(const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL)          {}
inline void _DTRACE_WARNING(const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL){}
inline void _DTRACE_WARNING(const char*           str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _DTRACE_WARNING(const unsigned short* str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _DTRACE_ERROR  (const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL)          {}
inline void _DTRACE_ERROR  (const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL){}
inline void _DTRACE_ERROR  (const char*           str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _DTRACE_ERROR  (const unsigned short* str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _DTRACE_RAWDATA(const char*           title, const void* pData, long size, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL)          {}
inline void _DTRACE_RAWDATA(const unsigned short* title, const void* pData, long size, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL){}
inline void _DTRACE_RAWDATA(const char*           title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}
inline void _DTRACE_RAWDATA(const unsigned short* title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}
#define     _DFTRACE_TO 
inline void _DTRACE_INFO_TO   (const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL)           {}
inline void _DTRACE_INFO_TO   (const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_INFO_COL) {}
inline void _DTRACE_INFO_TO   (const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _DTRACE_INFO_TO   (const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_INFO_COL)                                                     {}
inline void _DTRACE_WARNING_TO(const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL)          {}
inline void _DTRACE_WARNING_TO(const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_WARNING_COL){}
inline void _DTRACE_WARNING_TO(const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _DTRACE_WARNING_TO(const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_WARNING_COL)                                                  {}
inline void _DTRACE_ERROR_TO  (const char*           nomprog, const char*           str, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL)          {}
inline void _DTRACE_ERROR_TO  (const unsigned short* nomprog, const unsigned short* str, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_ERROR_COL){}
inline void _DTRACE_ERROR_TO  (const char*           nomprog, const char*           str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _DTRACE_ERROR_TO  (const unsigned short* nomprog, const unsigned short* str, unsigned char priority, long color = _TRDEF_ERROR_COL)                                                    {}
inline void _DTRACE_RAWDATA_TO(const char*           nomprog, const char*           title, const void* pData, long size, const char *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL)          {}
inline void _DTRACE_RAWDATA_TO(const unsigned short* nomprog, const unsigned short* title, const void* pData, long size, const unsigned short *module = 0, unsigned char priority = _TRDEF_PRIORITY, long color = _TRDEF_RAWDATA_COL){}
inline void _DTRACE_RAWDATA_TO(const char*           nomprog, const char*           title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}
inline void _DTRACE_RAWDATA_TO(const unsigned short* nomprog, const unsigned short* title, const void* pData, long size, unsigned char priority, long color = _TRDEF_RAWDATA_COL)                                                    {}


#endif // TRACER_DISABLED


#endif

#endif
