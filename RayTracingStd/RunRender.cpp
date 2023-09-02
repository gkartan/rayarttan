#pragma warning(disable : 4530)
#pragma warning(disable : 4096)
#pragma warning(disable : 4005)

#include "RenderInterface.h"

#include "stdafx.h"
#include "RayTracingStd.h"
#include "IhmInterface.h"
#include "RunRender.h"
#include "resource.h"
#include "MainFrm.h"
#include "IhmConstants.h"
#include "TraceService.h"
#include "RenderType.h"
#include "RenderingView.h"

extern ENUM_APP_MODE	GetMode();			  


CRunRender::CRunRender()
{
}


CRunRender::~CRunRender()
{
}

HANDLE StartEvent;
HANDLE ThreadHandle[32];
StructRenderType* RenderType[32];
ULONG TotalIterations = 1;
DWORD CurrentRun=0;

void CRunRender::TerminateAll()
{
	//On force la terminaison
	for (int i=0; i<CurrentRun; i++) 
	{
		if(RenderType[i]!=NULL)
			RenderType[i]->bTerminated=true;
	}

	for (i=0; i<CurrentRun; i++) 
	{
		if(ThreadHandle[i]!=NULL)
			CloseHandle(ThreadHandle[i]);
	}
}

unsigned long CRunRender::Run(void* pParam)
{
	CRenderStructure	*pRenderStructure=static_cast<CRenderStructure*>(pParam);
/*	CMainFrame *pFrame=NULL;

	if(pParam!=NULL)
	{
		pFrame=static_cast<CMainFrame *>(pParam);

		if(pFrame->m_pRenderView==NULL)
		{
			
			CString str;
			str.LoadString(IDS_ERREUR_MSG_1);
			AfxMessageBox(str);

			pFrame->PostMessage(MS_RENDER_FINISHED);

			return -1;
		}
	}*/


    DWORD i;
    SYSTEM_INFO SystemInfo;
    DWORD ThreadId;
    DWORD StartTime, EndTime;
    DWORD ThisTime;

    //
    // Determine how many processors are in the system.
    //
    GetSystemInfo(&SystemInfo);

    //
    // Create the start event.
    //
    StartEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (StartEvent == NULL) {
        fprintf(stderr, "CreateEvent failed, error %d\n",GetLastError());
        exit(1);
    }

		//
		// Start the threads, and let them party on the
		// memory buffer.
		//
		ResetEvent(StartEvent);

		int	NumberOfProcessors=SystemInfo.dwNumberOfProcessors;
		CurrentRun=NumberOfProcessors;

		for (i=0; i<NumberOfProcessors; i++) 
		{
			RenderType[i]=NULL;
			ThreadHandle[i]=NULL;
		}

		/////**Preprocessing
		DWORD StartTimePreproc, EndTimePreproc,TimePreproc;

		StartTimePreproc=GetTickCount();
		///Initialise les structure pour les processeurs
		CRenderInterface::Initialize(NumberOfProcessors);

		CRenderInterface::CommonComputation();

		EndTimePreproc=GetTickCount();

		TimePreproc=EndTimePreproc-StartTimePreproc;
		/////**Fin Preprocessing

		for (i=0; i<NumberOfProcessors; i++) 
		{
			_TRACE_INFO(_STR("  %d thread run: ", i+1));

			RenderType[i]=new StructRenderType;
			RenderType[i]->NumThread=i;
			RenderType[i]->TotalThread=NumberOfProcessors;
			RenderType[i]->NbLines=pRenderStructure->GetImage()->GetHeight();
			RenderType[i]->TypeAlgo=pRenderStructure->GetTypeAlgo();
		
			ThreadHandle[i] = CreateThread(NULL,
										   0,
										   CRenderInterface::LancementRayTracing,
										   RenderType[i],
										   0,
										   &ThreadId);
			if (ThreadHandle[i] == NULL) {
				exit(1);
			}
		}

		//
		// Start the threads and wait for them to exit.
		//
		StartTime = GetTickCount();
		SetEvent(StartEvent);

		WaitForMultipleObjects(NumberOfProcessors, ThreadHandle, TRUE, INFINITE);


		CRenderInterface::AfterRender(false);
		CRenderInterface::Destroy(NumberOfProcessors);

		EndTime = GetTickCount();

		ThisTime = EndTime-StartTime;

		//////////////////////////////////////////////////
		////Affichage résultat
		if(((CRayTracingStdApp*) AfxGetApp())->GetMode()!=MODE_SCREENSAVER)
		{
			CString str;
			str.Format("%7d ms",ThisTime);
			_TRACE_WARNING(str);

			
			str.LoadString(IDS_COMPUTING_FINISHED);
			CString sDisplay(str);

			CTime DureeTimePreproc(TimePreproc/1000);
			CString sPreProcDisplay;
			sPreProcDisplay.Format("\nPreprocessing : %d = %d h : %d m : %d s",
									  DureeTimePreproc.GetHour()-1,DureeTimePreproc.GetMinute(),DureeTimePreproc.GetSecond());

			sDisplay+=sPreProcDisplay;


			double DureeCumulee=0;
			for (i=0; i<NumberOfProcessors; i++) 
			{
				CTime Time(long(RenderType[i]->Duree)/1000);
				CString sInternDisplay;
				sInternDisplay.Format("\nThread %d = %d h : %d m : %d s",i,
									  Time.GetHour()-1,Time.GetMinute(),Time.GetSecond());
				sDisplay+=sInternDisplay;
				DureeCumulee+=float(RenderType[i]->Duree)/1000.;
			}

			CTime DureeTime(DureeCumulee);
			CString sInternDisplay;
			sInternDisplay.Format("\nTotal = %d h : %d m : %d s\n",
								  DureeTime.GetHour()-1,DureeTime.GetMinute(),DureeTime.GetSecond());
			sDisplay+=sInternDisplay;

			CTime MeanTime(long(DureeCumulee/NumberOfProcessors));
			str.LoadString(IDS_MOYENNE);
			sInternDisplay.Format(" %d h : %d m : %d s",
								  MeanTime.GetHour()-1,MeanTime.GetMinute(),MeanTime.GetSecond());
			sInternDisplay=str+sInternDisplay;
			sDisplay+=sInternDisplay;

			if(CRenderInterface::m_bIhm)
				AfxMessageBox(sDisplay);
		}

		////Fin Affichage résultat
		//////////////////////////////////////////////////

		for (i=0; i<NumberOfProcessors; i++) 
		{
			delete RenderType[i];
			CloseHandle(ThreadHandle[i]);
		}


	switch(GetMode())
	{
		case MODE_NORMAL:
			AfxGetMainWnd()->PostMessage(MS_RENDER_FINISHED);
			break;
		case MODE_CONSOLE:
			AfxGetApp()->PostThreadMessage(WM_QUIT,NULL,NULL);
			break;
		case MODE_SCREENSAVER:
			AfxGetApp()->PostThreadMessage(MS_RENDER_FINISHED,NULL,NULL);
			break;
	}

	return 0;
}
