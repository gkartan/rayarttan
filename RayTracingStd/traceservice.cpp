////////////////////////////////////////////////////////////////////////////////////////
// * FICHIER D'IMPLEMENTATION   : TraceService.cpp                                    //
////////////////////////////////////////////////////////////////////////////////////////
// * AUTEUR                     : Jérôme CUQ                                          //
////////////////////////////////////////////////////////////////////////////////////////
// * DATE DE CREATION           : 22/03/00                                            //
////////////////////////////////////////////////////////////////////////////////////////
// * DESCRIPTION :                                                                    //
//     Implémentation d'un service d'accès au serveur COM "TRACEUR.EXE".              //
//     Cela inclut la prise en charge de l'ensemble des types de traces et le point   //
//     de connexion COM permettant d'être informé sur les filtres demandés par le     //
//     serveur.                                                                       //
////////////////////////////////////////////////////////////////////////////////////////

#include "TraceService.h"

///// SI TRACES ACTIVEES
#ifndef TRACER_DISABLED

#define _WIN32_WINNT 0x0400
#include <objbase.h>

#include <stdio.h>
#import "traceur.exe" named_guids

#define TRACE_MSG       (WM_USER+520)


#define EXCEPTION_MSG L"Exception lors de l'envoi d'une trace"



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                 VARIABLES & FONCTIONS GLOBALES                    ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

int CloseFunction();
class CTrace
{
public:
	// Objet de trace
	TRACERLib::ITraceCOMObject2Ptr TracePtr;

	void FatalError(unsigned short *ErrorText) { try{TracePtr->Trace(TRACE_ERROR_EVENT, ErrorText, 1, _TRDEF_ERROR_COL, BSTR(NULL));}catch(...){};};
	void OnServerLost() { CloseFunction(); };
	~CTrace() { TraceService_Close(); };
};
CTrace g_Trace;

// Structure dans laquelle transite les données d'une trace vers le thread
struct STraceThread
{
	char             m_Status;
	unsigned char    m_Priority;
	long             m_Color;
	unsigned short * m_Text;
	unsigned short * m_Module;
	unsigned short * m_TargetProg;
	const void *     m_pData;
	long             m_Size;
};

// var globale indiquant le précédent resultat de CoInitializeEx()
// (permet d'appeler CoUninitialize)
int g_InitRes = 0;

// Point de connexion
IConnectionPoint *g_pConnectionPoint = NULL;
DWORD g_dwCookie = 0;

// Booléens filtrant les traces avant l'emission vers le serveur
// (Tableau indexé sur l'énuméré EVENT_TYPE
BOOL g_bSendTraces[ENDOF_EVENT_TYPE];
inline void InitBooleans()
{memset(g_bSendTraces,TRUE,sizeof(BOOL)*ENDOF_EVENT_TYPE);}
unsigned char g_SendMaxPriority = 255;

// Objets identifiant le thread de trace
HANDLE g_TraceThreadHandle = 0;
DWORD  g_TraceThreadID     = 0;

// Objets utilisés par le thread de trace
class CThreadInitData
{
public:
	CThreadInitData()  {ProgramName=NULL; ModuleName=NULL;}
	~CThreadInitData() {if (ProgramName) delete[] ProgramName; if (ModuleName) delete[] ModuleName;}
	unsigned short *ProgramName;
	unsigned short *ModuleName;
};
BOOL g_ThreadStarted = FALSE;
BOOL g_bLinkInit;

size_t len;

// Mode de communication avec le serveur
TRACER_COM_MODE g_TraceComMode;

char g_STR_Mark[] = "TRAC";

////////////////////////////////////
//     Conversion CHAR =>UNICODE
////////////////////////////////////
#ifndef _DEBUG
	#define USES_TRACE_CONVERSION int _trace_convert; _trace_convert
#else
	#define USES_TRACE_CONVERSION int _trace_convert = 0
#endif

#define C2U(lpa) (\
	((LPCWSTR)lpa == NULL) ? NULL : (\
		_trace_convert = (strlen(lpa)+1)*2,\
		C2UHelper((LPWSTR) alloca(_trace_convert), lpa, _trace_convert)))

LPWSTR WINAPI C2UHelper(LPWSTR lpw, LPCSTR lpa, int nChars)
{
	lpw[0] = '\0';
	MultiByteToWideChar(CP_ACP, 0, lpa, -1, lpw, nChars);
	return lpw;
}
////////////////////////////////////






///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////       IMPLEMENTATION DU POINT DE CONNEXION VERS LE TRACEUR        ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
class  CTraceConnectionPoint : public TRACERLib::ITraceConnectionPoint2
{
	public:
		// IUnknown
		ULONG __stdcall AddRef();
		ULONG __stdcall Release();
		HRESULT __stdcall QueryInterface(REFIID iid, void** ppv);
		
		HRESULT STDMETHODCALLTYPE raw_IsAlive();
		HRESULT STDMETHODCALLTYPE raw_InfoTraces(short bSend);
		HRESULT STDMETHODCALLTYPE raw_WarningTraces(short bSend);
		HRESULT STDMETHODCALLTYPE raw_ErrorTraces(short bSend);
		HRESULT STDMETHODCALLTYPE raw_EnterExitTraces(short bSend);
		HRESULT STDMETHODCALLTYPE raw_BinaryTraces(short bSend);
		HRESULT STDMETHODCALLTYPE raw_MaxTracePriority(short Priority);

		//HRESULT STDMETHODCALLTYPE raw_GetRef(long * a_plRef);
		
		CTraceConnectionPoint() : m_cRef(0) { }
		~CTraceConnectionPoint() { }

	private:
		long m_cRef;
};

ULONG CTraceConnectionPoint::AddRef()
{
	return ++m_cRef;
}

ULONG CTraceConnectionPoint::Release()
{
	if(--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT CTraceConnectionPoint::QueryInterface(REFIID riid, void** ppv)
{
	if(riid == IID_IUnknown)
		*ppv = (IUnknown*)this;
	else if(riid == TRACERLib::IID_ITraceConnectionPoint)
		*ppv = (TRACERLib::ITraceConnectionPoint*)this;
	else if(riid == TRACERLib::IID_ITraceConnectionPoint2)
		*ppv = (TRACERLib::ITraceConnectionPoint2*)this;
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

STDMETHODIMP CTraceConnectionPoint::raw_IsAlive()
{
	return S_OK;
}

STDMETHODIMP CTraceConnectionPoint::raw_InfoTraces(short bSend)
{
	g_bSendTraces[TRACE_INFO_EVENT] = bSend;
	return S_OK;
}

STDMETHODIMP CTraceConnectionPoint::raw_WarningTraces(short bSend)
{
	g_bSendTraces[TRACE_WARNING_EVENT] = bSend;
	return S_OK;
}

STDMETHODIMP CTraceConnectionPoint::raw_ErrorTraces(short bSend)
{
	g_bSendTraces[TRACE_ERROR_EVENT] = bSend;
	return S_OK;
}

STDMETHODIMP CTraceConnectionPoint::raw_EnterExitTraces(short bSend)
{
	g_bSendTraces[TRACE_ENTER_FUNC] = bSend;
	g_bSendTraces[TRACE_EXIT_FUNC]  = bSend;
	return S_OK;
}

STDMETHODIMP CTraceConnectionPoint::raw_BinaryTraces(short bSend)
{
	g_bSendTraces[TRACE_RAWDATA_EVENT] = bSend;
	return S_OK;
}

STDMETHODIMP CTraceConnectionPoint::raw_MaxTracePriority(short Priority)
{
	g_SendMaxPriority = (unsigned char)Priority;
	return S_OK;
}







///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////    FONCTIONS DE GESTION DES CHAINES (fonctions _STR & _DSTR)      ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// Cette macro désalloue le buffer g_STR_Buffer
#define Delete_if_STRBuffer(pStr)\
	if ( pStr && (*(long*)(g_STR_Mark) == *(((long*)pStr)-1)) )\
		delete[] (((char *)pStr)-4);

////////////////////////////////////////
const char* _STR(const char* format,...)
{
	char *l_STR_Buffer = new char[_STR_ALLOCSIZE];
	memcpy(l_STR_Buffer,"TRAC",4);
	l_STR_Buffer+=4;
	va_list var_args;
	va_start( var_args, format );     // Initialise le pointeur de liste d'arguments
	_vsnprintf(l_STR_Buffer,_STR_ALLOCSIZE-4,format, var_args);
	return(l_STR_Buffer);
}
const unsigned short* _STR(const unsigned short* format,...)
{
	unsigned short *l_STR_UBuffer = new unsigned short[_STR_ALLOCSIZE];
	memcpy(l_STR_UBuffer,"TRAC",4);
	l_STR_UBuffer+=2;
	va_list var_args;
	va_start( var_args, format );
	_vsnwprintf(l_STR_UBuffer,_STR_ALLOCSIZE,format, var_args);
	return(l_STR_UBuffer);
}








///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////            FONCTIONS INIT/CLOSE UTILISEES PLUS LOIN               ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////////////////////////////////////
//     fonction d'init
////////////////////////////////////
int InitFunction(DWORD Mode, const unsigned short *ProgName, const unsigned short *ModuleName, BOOL bLinkInit)
{
	IConnectionPointContainer *l_pConnectionPointContainer = NULL;
	CTraceConnectionPoint * l_pTraceConnectionPoint = NULL;

	try
	{
		InitBooleans();
		if (!FAILED(CoInitializeEx(NULL, Mode)))
			g_InitRes++;
		// else return 0; c'est pas grave !

		g_Trace.TracePtr.CreateInstance(__uuidof(TRACERLib::TraceCOMObject));
		if (g_Trace.TracePtr==NULL)
			return 0;

		//Sleep(100);

		// Récupération de l'instance du ConnectionPointContainer contenant les points de connection
		if (!FAILED(g_Trace.TracePtr->QueryInterface(IID_IConnectionPointContainer, (void**)&l_pConnectionPointContainer)))
		{
			// Création d'un nouveau ConnectionPoint
			if (!FAILED(l_pConnectionPointContainer->FindConnectionPoint(TRACERLib::IID_ITraceConnectionPoint, &g_pConnectionPoint)))
			{
				l_pTraceConnectionPoint = new CTraceConnectionPoint;
				if (g_pConnectionPoint->Advise(l_pTraceConnectionPoint, &g_dwCookie)!=S_OK)
				{
					//delete l_pTraceConnectionPoint;
					l_pTraceConnectionPoint = NULL;
				}
			}
		}

		if (bLinkInit)
			g_Trace.TracePtr->Link(ProgName,ModuleName);
		else
			g_Trace.TracePtr->Init(ProgName);
	}
	catch(...)
	{
		g_Trace.FatalError(L"Exception à l'INIT");
		g_Trace.OnServerLost();
	}

	if (l_pConnectionPointContainer)
		l_pConnectionPointContainer->Release();
	l_pConnectionPointContainer = NULL;

	if ((g_Trace.TracePtr!=NULL) && !l_pTraceConnectionPoint)
		_TRACE_ERROR(_STR(L"La création d'une notification vers %s/%s a echoué",ProgName,ModuleName));

	if (g_Trace.TracePtr==NULL)
	{
		if (g_pConnectionPoint)
		{
			g_pConnectionPoint->Unadvise(g_dwCookie);
			g_pConnectionPoint->Release();
			g_pConnectionPoint = NULL;
		}
		while (g_InitRes)
		{
			CoUninitialize();
			g_InitRes--;
		}
		return 0;
	}

	return 1;
}

////////////////////////////////////
//     fonction d'uninit
////////////////////////////////////
int CloseFunction()
{
	try
	{
		try
		{
			if (g_pConnectionPoint)
			{
				g_pConnectionPoint->Unadvise(g_dwCookie);
				g_pConnectionPoint->Release();
				g_pConnectionPoint = NULL;
			}
		}
		catch(...)
		{
			g_pConnectionPoint = NULL;
		}

		if (g_Trace.TracePtr!=NULL)
		{
			try
			{
				g_Trace.TracePtr = NULL;
			}
			catch(...)
			{
				g_Trace.TracePtr.Detach();
			}
			Sleep(20);
			while (g_InitRes)
			{
				CoUninitialize();
				g_InitRes--;
			}
		}
	}
	catch(...)
	{
		return 0;
	}
	return 1;
}







///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////           FONCTION DE CREATION D'UNE TRACE BINAIRE                ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
VARIANT CreateRawData(const void * pData, long size)
{
	VARIANT l_variant;
	l_variant.vt = VT_ARRAY;
	l_variant.parray = NULL;

	SAFEARRAY FAR* l_pArray;
	SAFEARRAYBOUND rgsabound[1];
	void * l_pArrayData;
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = size;
	l_pArray = SafeArrayCreate(VT_UI1, 1, rgsabound);

	if (!FAILED(SafeArrayAccessData(l_pArray,(void**)&l_pArrayData)))
	{
		memcpy(l_pArrayData,pData,size);
		
		if (!FAILED(SafeArrayUnaccessData(l_pArray)))
			l_variant.parray = l_pArray;
		else
			SafeArrayDestroy(l_pArray);
	}
	else
		SafeArrayDestroy(l_pArray);

	return l_variant;
}









///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////   FONCTIONS DE GESTION DES TRACES PAR ENVOI DE MESSAGE (Thread)   ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

DWORD WINAPI TraceThreadFunction (LPVOID lpParam)
{
	STraceThread *l_pData = NULL;
	EVENT_TYPE    l_Type;
	VARIANT       l_var;
	CThreadInitData* l_pInitData = (CThreadInitData*)lpParam;


	/////////// INIT ///////////
	InitFunction(COINIT_MULTITHREADED, l_pInitData->ProgramName, l_pInitData->ModuleName, g_bLinkInit);
	g_ThreadStarted = TRUE;
	try
	{
		delete l_pInitData;
	}
	catch(...)
	{}
	///////// FIN INIT /////////


	// Boucle de traitement des messages
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		l_pData = (STraceThread*)msg.lParam;

		if (g_Trace.TracePtr!=NULL)
			switch (msg.message)
			{
			case TRACE_MSG:
				l_Type = (EVENT_TYPE)msg.wParam;
				if (l_Type!=TRACE_EXITPROG_EVENT)
				{
					try
					{
						if (l_Type==TRACE_RAWDATA_EVENT)
						{
							try
							{
								l_var = CreateRawData(l_pData->m_pData,l_pData->m_Size);
								if (l_pData->m_TargetProg)
									g_Trace.TracePtr->TraceRawDataToStream(l_pData->m_TargetProg,&l_var, l_pData->m_Text, l_pData->m_Priority, l_pData->m_Color, l_pData->m_Module);
								else
									g_Trace.TracePtr->TraceRawData(&l_var, l_pData->m_Text, l_pData->m_Priority, l_pData->m_Color, l_pData->m_Module);
								SafeArrayDestroy(l_var.parray);
							}
							catch(...)
							{
								try{SafeArrayDestroy(l_var.parray);}catch(...){}
							}
						}
						else
						{
							if (l_pData->m_TargetProg)
								g_Trace.TracePtr->TraceToStream(l_pData->m_TargetProg,l_Type, l_pData->m_Text, l_pData->m_Priority, l_pData->m_Color, l_pData->m_Module);
							else
								g_Trace.TracePtr->Trace(l_Type, l_pData->m_Text, l_pData->m_Priority, l_pData->m_Color, l_pData->m_Module);
						}
					}
					catch(...)
					{
						g_Trace.FatalError(EXCEPTION_MSG);
						g_Trace.OnServerLost();
					}
				}
				break;

			/*case SETMAXITEMS_MSG:
				try
				{
					g_Trace.TracePtr->SetMaxItems(msg.wParam);
				}
				catch(...)
				{
					g_Trace.OnServerLost();
				}
				break;*/
			}

		// Libération des données de trace
		if ( (l_pData) && ((msg.message==TRACE_MSG) /*|| (msg.message==SETMAXITEMS_MSG)*/) )
		{
			if (l_pData->m_Status==2) // l'attente du thread appelant a échoué
				try
				{
					if (l_pData->m_Text)
						delete[] l_pData->m_Text;
					if (l_pData->m_Module)
						delete[] l_pData->m_Module;
					if (l_pData->m_TargetProg)
						delete[] l_pData->m_TargetProg;
					delete l_pData;
				}
				catch(...)
				{
				}
			else
				l_pData->m_Status = 0; // traité
		}

		// On arrête le thread
		if ( (msg.message==TRACE_MSG) && (msg.wParam==TRACE_EXITPROG_EVENT) )
			break;
	} // While GetMessage()


	/////////  ARRET  /////////
	CloseFunction();
	g_ThreadStarted = FALSE;
	//////// FIN ARRET ////////
	
	return 0;
}

// Fonction permettant l'envoi d'une trace vers le thread
inline void TraceService_SendTraceToThread(EVENT_TYPE Type, const unsigned short * text, unsigned char priority, long color, const unsigned short * module, const unsigned short * targetprog = NULL, const void *pData = NULL, long size = 0)
{
	unsigned short *l_pTexte = NULL;
	unsigned short *l_pModule = NULL;
	unsigned short *l_pTargetProg = NULL;

	if (text)
	{
		l_pTexte = new unsigned short[wcslen(text)+1];
		wcscpy(l_pTexte, text);
	}
	if (module)
	{
		l_pModule = new unsigned short[wcslen(module)+1];
		wcscpy(l_pModule, module);
	}
	if (targetprog)
	{
		l_pTargetProg = new unsigned short[wcslen(targetprog)+1];
		wcscpy(l_pTargetProg, targetprog);
	}

	STraceThread *l_pTrace = new STraceThread;
	l_pTrace->m_Status     = 1;
	l_pTrace->m_Priority   = priority;
	l_pTrace->m_Color      = color;
	l_pTrace->m_Text       = l_pTexte;
	l_pTrace->m_Module     = l_pModule;
	l_pTrace->m_TargetProg = l_pTargetProg;
	l_pTrace->m_pData      = pData;
	l_pTrace->m_Size       = size;

	if (!PostThreadMessage(g_TraceThreadID,TRACE_MSG,Type,(long)l_pTrace))
	{
		// Impossible d'émettre le message
		// => On essaie en appel direct
		l_pTrace->m_Status = 0;
		try
		{
			if (Type==TRACE_EXITPROG_EVENT)
			{
				// Pour éviter un DeadLock (si le thread n'existe plus c'est que le process est déjà arrêté)
				g_pConnectionPoint = NULL;
				CloseFunction();
				g_ThreadStarted = FALSE;
			}
			else if (g_Trace.TracePtr!=NULL)
			{
				if (targetprog)
					g_Trace.TracePtr->TraceToStream(targetprog, Type, text, priority, color, module);
				else
					g_Trace.TracePtr->Trace(Type, text, priority, color, module);
			}
		}
		catch(...)
		{
			g_Trace.FatalError(EXCEPTION_MSG);
			g_Trace.OnServerLost();
		}
	}
	else
	{ // On attend que le message soit traité
		int counter = 0;
		while ( (l_pTrace->m_Status) && (counter!=10) )
		{
			Sleep(0);
			counter++;
		}
		// Cette méthode a échoué
		if (counter==10)
		{
			counter=3;
			while ( (l_pTrace->m_Status) && (counter!=10) )
			{
				Sleep(counter);
				counter++;
			}
		}
	}

	if (l_pTrace->m_Status)
		l_pTrace->m_Status=2; // On demande au thread de détruire les données
	else
		try
		{
			delete l_pTrace;
			if (l_pTexte)
				delete[] l_pTexte;
			if (l_pModule)
				delete[] l_pModule;
			if (l_pTargetProg)
				delete[] l_pTargetProg;
		}
		catch(...)
		{
		}
}
inline void TraceService_SendTraceToThread(EVENT_TYPE Type, const char * text, unsigned char priority, long color, const char * module, const char * targetprog = NULL, const void *pData = NULL, long size = 0)
{
	USES_TRACE_CONVERSION;
	TraceService_SendTraceToThread(Type, C2U(text), priority, color, C2U(module), C2U(targetprog), pData, size);
}

// Démarre le thread et attend que l'init du serveur soit terminée
BOOL StartThread(const unsigned short *ProgramName, const unsigned short *ModuleName, unsigned int timeout)
{
	try
	{
		if (!g_TraceThreadHandle)
		{
			CThreadInitData * l_pThreadInitData = new CThreadInitData;
			g_ThreadStarted = FALSE;
			SECURITY_ATTRIBUTES secu;
			secu.nLength = sizeof(SECURITY_ATTRIBUTES);
			secu.lpSecurityDescriptor = NULL;
			secu.bInheritHandle = TRUE;
			if (ProgramName)
			{
				l_pThreadInitData->ProgramName = new unsigned short [wcslen(ProgramName)+1];
				wcscpy(l_pThreadInitData->ProgramName, ProgramName);
			}
			if (ModuleName)
			{
				l_pThreadInitData->ModuleName = new unsigned short [wcslen(ModuleName)+1];
				wcscpy(l_pThreadInitData->ModuleName, ModuleName);
			}
			g_TraceThreadHandle = ::CreateThread(&secu,0,&TraceThreadFunction,l_pThreadInitData,0,&g_TraceThreadID);
			if (!g_TraceThreadHandle)
			{
				g_TraceThreadID = 0;
				return FALSE;
			}

			int max = timeout / 50;
			int count=0;
			while ( (g_ThreadStarted==FALSE) && (count<max) )
			{
				count++;
				Sleep(50);
			}
			if (count && (count==max))
				return FALSE;

			if (!SetThreadPriority(g_TraceThreadHandle,THREAD_PRIORITY_TIME_CRITICAL))
			{
				// impossible de fixer la priorité
			}
		}
	}
	catch(...)
	{
		return FALSE;
	}
	return TRUE;
}

// Arrête le thread et attend la fin effective
BOOL EndThread()
{
	if (g_ThreadStarted)
		TraceService_SendTraceToThread(TRACE_EXITPROG_EVENT, L"", 1, 0, NULL);

	int count=0;
	while ( (g_ThreadStarted==TRUE) && (count<50) )
	{
		count++;
		Sleep(30);
	}
	g_TraceThreadHandle = NULL;
	g_TraceThreadID = 0;
	if (count==50)
		return FALSE;

	return TRUE;
}






///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
//// FONCTIONS DE GESTION DES TRACES DECLAREES DANS LE FICHIER EN-TETE ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////
int _TRACE_INITOK()
{
	if (g_Trace.TracePtr==NULL)
		return(0);
	else
		return(1);
}

///////////////////////////////////////////////
int _TRACE_INIT(const char * ProgramName, TRACER_COM_MODE ComMode, unsigned int timeout)
{
	USES_TRACE_CONVERSION;
	return(_TRACE_INIT(C2U(ProgramName),ComMode,timeout));
}
int _TRACE_INIT(const unsigned short* ProgramName, TRACER_COM_MODE ComMode, unsigned int timeout)
{
	int l_Res = 0;

	// Libération de l'ancienne connexion
	if (TraceService_Close())
	{
		g_TraceComMode = ComMode;

		// Dans le cas d'une communication par envoi de messages, init d'un thread dédié
		if (ComMode==COM_SENDMESSAGES)
		{
			g_bLinkInit      = FALSE;
			if (StartThread(ProgramName, NULL, timeout))
				l_Res = 1;
		}
		else
			if (InitFunction((ComMode==COM_MULTITHREAD)?COINIT_MULTITHREADED:COINIT_APARTMENTTHREADED, ProgramName, NULL, FALSE))
				l_Res = 1;
	}

	Delete_if_STRBuffer(ProgramName);
	return l_Res;
}


////////////////////////////////////////////////////////////////////////////
int _TRACE_LINKINIT(const char * ProgramName, const char * ModuleName, TRACER_COM_MODE ComMode, unsigned int timeout)
{
	USES_TRACE_CONVERSION;
	int l_Res = _TRACE_LINKINIT(C2U(ProgramName),C2U(ModuleName),ComMode,timeout);
	Delete_if_STRBuffer(ProgramName);
	Delete_if_STRBuffer(ModuleName);
	return(l_Res);
}
int _TRACE_LINKINIT(const unsigned short * ProgramName, const unsigned short* ModuleName, TRACER_COM_MODE ComMode, unsigned int timeout)
{
	int l_Res = 0;

	// Libération de l'ancienne connexion
	if (TraceService_Close())
	{
		g_TraceComMode = ComMode;

		// Dans le cas d'une communication par envoi de messages, init d'un thread dédié
		if (ComMode==COM_SENDMESSAGES)
		{
			g_bLinkInit      = TRUE;
			if (StartThread(ProgramName, ModuleName, timeout))
				l_Res = 1;
		}
		else
			if (InitFunction((ComMode==COM_MULTITHREAD)?COINIT_MULTITHREADED:COINIT_APARTMENTTHREADED, ProgramName, ModuleName, TRUE))
				l_Res = 1;
	}

	Delete_if_STRBuffer(ProgramName);
	Delete_if_STRBuffer(ModuleName);

	return l_Res;
}


///////////////////////////////////////////////////////////////////////////
int TraceService_Close()
{
	if (g_TraceComMode==COM_SENDMESSAGES)
	{
		if (!EndThread())
			return 0;
	}
	else
		return CloseFunction();

	return(1);
}


///////////////////////////////////////////////////////////////////////////
void TraceService_SendTrace(EVENT_TYPE Type, const char * text, unsigned char priority, long color,
                            const char * ModuleName, const char * TargetStream)
{
	if (g_bSendTraces[Type] && (priority<=g_SendMaxPriority))
	{
		if (g_TraceComMode==COM_SENDMESSAGES)
		{
			TraceService_SendTraceToThread(Type,text,priority,color,ModuleName,TargetStream);
		}
		else
		{
			try
			{
				if ( (g_Trace.TracePtr!=NULL)/* &&
						 (Type!=TRACE_ENTER_FUNC) && (Type!=TRACE_EXIT_FUNC) &&
						 (Type!=TRACE_INITPROG_EVENT) && (Type!=TRACE_EXITPROG_EVENT) */)
				{
					USES_TRACE_CONVERSION;
					if (TargetStream)
						g_Trace.TracePtr->TraceToStream(C2U(TargetStream), Type, C2U(text), priority, color, C2U(ModuleName));
					else
						g_Trace.TracePtr->Trace(Type, C2U(text), priority, color, C2U(ModuleName));
				}
			}
			catch(...)
			{
				g_Trace.FatalError(EXCEPTION_MSG);
				g_Trace.OnServerLost();
			}
		}
	}

	Delete_if_STRBuffer(text);
	Delete_if_STRBuffer(ModuleName);
	Delete_if_STRBuffer(TargetStream);
}
void TraceService_SendTrace(EVENT_TYPE Type, const unsigned short* text, unsigned char priority,
                            long color, const unsigned short * ModuleName, const unsigned short * TargetStream)
{
	if (g_bSendTraces[Type] && (priority<=g_SendMaxPriority))
	{
		if (g_TraceComMode==COM_SENDMESSAGES)
		{
			TraceService_SendTraceToThread(Type,text,priority,color,ModuleName,TargetStream);
		}
		else
		{
			try
			{
				if ( (g_Trace.TracePtr!=NULL)/* &&
						 (Type!=TRACE_ENTER_FUNC) && (Type!=TRACE_EXIT_FUNC) &&
						 (Type!=TRACE_INITPROG_EVENT) && (Type!=TRACE_EXITPROG_EVENT) */)
				{
					if (TargetStream)
						g_Trace.TracePtr->TraceToStream(TargetStream, Type, text, priority, color, ModuleName);
					else
						g_Trace.TracePtr->Trace(Type, text, priority, color, ModuleName);
				}
			}
			catch(...)
			{
				g_Trace.FatalError(EXCEPTION_MSG);
				g_Trace.OnServerLost();
			}
		}
	}

	Delete_if_STRBuffer(text);
	Delete_if_STRBuffer(ModuleName);
	Delete_if_STRBuffer(TargetStream);
}

///////////////////////////////////////////////////////////////////////////
void TraceService_SendBinTrace(const void* pData, unsigned long size, const char * title, unsigned char priority,
                               long color, const char * ModuleName, const char * TargetStream)
{
	if (g_bSendTraces[TRACE_RAWDATA_EVENT] && (priority<=g_SendMaxPriority))
	{
		if (g_TraceComMode==COM_SENDMESSAGES)
		{
			TraceService_SendTraceToThread(TRACE_RAWDATA_EVENT,title,priority,color,ModuleName,TargetStream,pData,size);
		}
		else
		{
			try
			{
				if ( (g_Trace.TracePtr!=NULL)/* &&
						 (Type!=TRACE_ENTER_FUNC) && (Type!=TRACE_EXIT_FUNC) &&
						 (Type!=TRACE_INITPROG_EVENT) && (Type!=TRACE_EXITPROG_EVENT) */)
				{
					VARIANT l_var = CreateRawData(pData,size);
					try
					{
						USES_TRACE_CONVERSION;
						if (TargetStream)
							g_Trace.TracePtr->TraceRawDataToStream(C2U(TargetStream), &l_var, C2U(title), priority, color, C2U(ModuleName));
						else
							g_Trace.TracePtr->TraceRawData(&l_var, C2U(title), priority, color, C2U(ModuleName));
						SafeArrayDestroy(l_var.parray);
					}
					catch(...)
					{
						try{SafeArrayDestroy(l_var.parray);}catch(...){}
						g_Trace.FatalError(EXCEPTION_MSG);
						g_Trace.OnServerLost();
					}
				}
			}
			catch(...)
			{
			}
		}
	}

	Delete_if_STRBuffer(title);
	Delete_if_STRBuffer(ModuleName);
	Delete_if_STRBuffer(TargetStream);
}

///////////////////////////////////////////////////////////////////////////
void TraceService_SendBinTrace(const void* pData, unsigned long size, const unsigned short * title, unsigned char priority,
                               long color, const unsigned short * ModuleName, const unsigned short * TargetStream)
{
	if (g_bSendTraces[TRACE_RAWDATA_EVENT] && (priority<=g_SendMaxPriority))
	{
		if (g_TraceComMode==COM_SENDMESSAGES)
		{
			TraceService_SendTraceToThread(TRACE_RAWDATA_EVENT,title,priority,color,ModuleName,TargetStream,pData,size);
		}
		else
		{
			try
			{
				if ( (g_Trace.TracePtr!=NULL)/* &&
						 (Type!=TRACE_ENTER_FUNC) && (Type!=TRACE_EXIT_FUNC) &&
						 (Type!=TRACE_INITPROG_EVENT) && (Type!=TRACE_EXITPROG_EVENT) */)
				{
					VARIANT l_var = CreateRawData(pData,size);
					try
					{
						if (TargetStream)
							g_Trace.TracePtr->TraceRawDataToStream(TargetStream, &l_var, title, priority, color, ModuleName);
						else
							g_Trace.TracePtr->TraceRawData(&l_var, title, priority, color, ModuleName);
						SafeArrayDestroy(l_var.parray);
					}
					catch(...)
					{
						try{SafeArrayDestroy(l_var.parray);}catch(...){}
						g_Trace.FatalError(EXCEPTION_MSG);
						g_Trace.OnServerLost();
					}
				}
			}
			catch(...)
			{
			}
		}
	}

	Delete_if_STRBuffer(title);
	Delete_if_STRBuffer(ModuleName);
	Delete_if_STRBuffer(TargetStream);
}














///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////   CLASSE PERMETTANT DE TRACER LES ENTREES & SORTIES DE FONCTION   ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void CTraceService::Constructor(const unsigned short* FuncName, const unsigned short *module, unsigned char priority, long color)
{
	m_FuncName = NULL;
	m_Module = NULL;

	if ( g_bSendTraces[TRACE_ENTER_FUNC]  && (priority<=g_SendMaxPriority) && (g_Trace.TracePtr!=NULL) )
	{
		m_Priority = priority;
		m_Color    = color;
		m_FuncName = new unsigned short[wcslen(FuncName)+1];
		wcscpy(m_FuncName,FuncName);
		if (module)
		{
			m_Module = new unsigned short[wcslen(module)+1];
			wcscpy(m_Module,module);
		}
		if (g_TraceComMode==COM_SENDMESSAGES)
		{
			TraceService_SendTraceToThread(TRACE_ENTER_FUNC,FuncName,priority,color,module);
		}
		else
		{
			try
			{
				g_Trace.TracePtr->Trace(TRACE_ENTER_FUNC, FuncName, priority, color, module);
			}
			catch(...)
			{
				g_Trace.FatalError(EXCEPTION_MSG);
				g_Trace.OnServerLost();
			}
		}
	}
}

///////////////////////////////////////////////////
CTraceService::CTraceService(const char* FuncName, const char *module, unsigned char priority, long color)
{
	USES_TRACE_CONVERSION;
	Constructor(C2U(FuncName),C2U(module),priority,color);
	Delete_if_STRBuffer(FuncName);
	Delete_if_STRBuffer(module);
}
CTraceService::CTraceService(const unsigned short* FuncName, const unsigned short *module, unsigned char priority, long color)
{
	Constructor(FuncName,module,priority,color);
	Delete_if_STRBuffer(FuncName);
	Delete_if_STRBuffer(module);
}
CTraceService::CTraceService(const char* FuncName, unsigned char priority, long color)
{
	USES_TRACE_CONVERSION;
	Constructor(C2U(FuncName),0,priority,color);
	Delete_if_STRBuffer(FuncName);
}
CTraceService::CTraceService(const unsigned short* FuncName, unsigned char priority, long color)
{
	Constructor(FuncName,0,priority,color);
	Delete_if_STRBuffer(FuncName);
}

///////////////////////////////
CTraceService::~CTraceService()
{
	if ( m_FuncName && (g_Trace.TracePtr!=NULL) )
	{
		if (g_TraceComMode==COM_SENDMESSAGES)
		{
			TraceService_SendTraceToThread(TRACE_EXIT_FUNC,m_FuncName,m_Priority,m_Color,m_Module);
		}
		else
		{
			try
			{
				g_Trace.TracePtr->Trace(TRACE_EXIT_FUNC, m_FuncName, m_Priority, m_Color, m_Module);
			}
			catch(...)
			{
				g_Trace.FatalError(EXCEPTION_MSG);
				g_Trace.OnServerLost();
			}
		}
	}

	if (m_FuncName)
		delete[] m_FuncName;
	if (m_Module)
		delete[] m_Module;
}

void CTraceService_TO::Constructor(const unsigned short* nomprog, const unsigned short* FuncName, const unsigned short *module, unsigned char priority, long color)
{
	m_FuncName = NULL;
	m_Module = NULL;
	m_NomProg = NULL;

	if ( g_bSendTraces[TRACE_ENTER_FUNC]  && (priority<=g_SendMaxPriority) && (g_Trace.TracePtr!=NULL) )
	{
		m_Priority = priority;
		m_Color    = color;
		m_FuncName = new unsigned short[wcslen(FuncName)+1];
		wcscpy(m_FuncName,FuncName);
		if (module)
		{
			m_Module = new unsigned short[wcslen(module)+1];
			wcscpy(m_Module,module);
		}
		m_NomProg = new unsigned short[wcslen(nomprog)+1];
		wcscpy(m_NomProg,nomprog);
		if (g_TraceComMode==COM_SENDMESSAGES)
		{
			TraceService_SendTraceToThread(TRACE_ENTER_FUNC,FuncName,priority,color,module,m_NomProg);
		}
		else
		{
			try
			{
				g_Trace.TracePtr->TraceToStream(m_NomProg,TRACE_ENTER_FUNC, FuncName, priority, color, module);
			}
			catch(...)
			{
				g_Trace.FatalError(EXCEPTION_MSG);
				g_Trace.OnServerLost();
			}
		}
	}
}

///////////////////////////////////////////////////
CTraceService_TO::CTraceService_TO(const char* nomprog, const char* FuncName, const char *module, unsigned char priority, long color)
{
	USES_TRACE_CONVERSION;
	Constructor(C2U(nomprog),C2U(FuncName),C2U(module),priority,color);
	Delete_if_STRBuffer(nomprog);
	Delete_if_STRBuffer(FuncName);
	Delete_if_STRBuffer(module);
}
CTraceService_TO::CTraceService_TO(const unsigned short* nomprog, const unsigned short* FuncName, const unsigned short *module, unsigned char priority, long color)
{
	Constructor(nomprog,FuncName,module,priority,color);
	Delete_if_STRBuffer(nomprog);
	Delete_if_STRBuffer(FuncName);
	Delete_if_STRBuffer(module);
}
CTraceService_TO::CTraceService_TO(const char* nomprog, const char* FuncName, unsigned char priority, long color)
{
	USES_TRACE_CONVERSION;
	Constructor(C2U(nomprog),C2U(FuncName),0,priority,color);
	Delete_if_STRBuffer(nomprog);
	Delete_if_STRBuffer(FuncName);
}
CTraceService_TO::CTraceService_TO(const unsigned short* nomprog, const unsigned short* FuncName, unsigned char priority, long color)
{
	Constructor(nomprog,FuncName,0,priority,color);
	Delete_if_STRBuffer(nomprog);
	Delete_if_STRBuffer(FuncName);
}

///////////////////////////////
CTraceService_TO::~CTraceService_TO()
{
	if ( m_FuncName && (g_Trace.TracePtr!=NULL) )
	{
		if (g_TraceComMode==COM_SENDMESSAGES)
		{
			TraceService_SendTraceToThread(TRACE_EXIT_FUNC,m_FuncName,m_Priority,m_Color,m_Module,m_NomProg);
		}
		else
		{
			try
			{
				g_Trace.TracePtr->TraceToStream(m_NomProg,TRACE_EXIT_FUNC, m_FuncName, m_Priority, m_Color, m_Module);
			}
			catch(...)
			{
				g_Trace.FatalError(EXCEPTION_MSG);
				g_Trace.OnServerLost();
			}
		}
	}

	if (m_FuncName)
		delete[] m_FuncName;
	if (m_Module)
		delete[] m_Module;
	if (m_NomProg)
		delete[] m_NomProg;
}

#endif
