//////////////////////////////////////////////////////////////////////
// winstrbuf.cpp:	implementation of class winstrbuf.
// author:			g. makulik
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winstrbuf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

winstrbuf::winstrbuf	( CWnd *	pWnd_
						, int		nBufSize_ 
						)
	: streambuf()
	, m_pWnd(pWnd_)
	, m_nBufSize(nBufSize_)
{
	ASSERT_VALID(pWnd_);
	
	if (m_nBufSize)
	{
		char *	ptr = new char[m_nBufSize];
		setp(ptr, ptr + m_nBufSize);
	}
	else
		setp(0, 0);

	setg(0, 0, 0);
}

winstrbuf::~winstrbuf	()
{
	sync();
	if (m_nBufSize)
	{
		delete [] pbase();
	}
}

int	winstrbuf::overflow	( int		c_
						)
{
	put_buffer();

	if (c_ != EOF)
		if (pbase() == epptr())
			put_char(c_);
		else
			sputc(c_);

	return 0;
}

int	winstrbuf::sync		()
{
	put_buffer();
	return 0;
}

void winstrbuf::put_char( int		c_
						)
{
	// extract actual window text
	ASSERT_VALID(m_pWnd);
	CString	csBuf;
	m_pWnd->GetWindowText(csBuf);

	// append character to extracted text
	csBuf += TranslateWinChar(c_);

	// write back text to the window (render)
	m_pWnd->SetWindowText(csBuf);
	//OutputDebugString(csBuf);
}

void winstrbuf::put_buffer()
{
	if (pbase() != pptr())
	{
		int     nBufLength = (pptr() - pbase());

		// extract actual window text
		ASSERT_VALID(m_pWnd);
		CString	csBuf;
		m_pWnd->GetWindowText(csBuf);

		// append buffer to extracted text
		CString	csHelp(pbase(),nBufLength);
		csBuf += TranslateWinChar(csHelp);

		// write back text to the window (render)
		m_pWnd->SetWindowText(csBuf);
		//OutputDebugString(csBuf);

		setp(pbase(), epptr());
	}
}

CString	winstrbuf::TranslateWinChar	( int		c_
									)
{
	CString	csRes;

	csRes = "";
	switch((char)c_)
	{
	// prefix 'LF' with 'CR' 
	case '\n':
		csRes += '\r';
		break;
	// implement alert character as 'optical bell'. Just override if
	// you want to do anything other.
	case '\a':
		PutAlertChar();
		return csRes;
		break;
	}

	csRes += (char)c_;
	return csRes;
}

CString	winstrbuf::TranslateWinChar	( CString const &		cs_
									)
{
	CString	csRes;

	csRes = "";
	for(int i = 0;
	    i < cs_.GetLength();
		i++)
	{
		csRes += TranslateWinChar(cs_[i]);
	}

	return csRes;
}

void winstrbuf::PutAlertChar()
{
	ASSERT(m_pWnd);
	CWnd *	pFlashWin = m_pWnd->GetTopLevelParent();
	InstallTimer(pFlashWin,100,5);

}

void CALLBACK EXPORT
	winstrbuf::CFlashTimer::TimerProc	( HWND			hWnd_
										, UINT			nMsg_
										, UINT			nId_
										, DWORD			dwTime_
										)
{
	CFlashTimer	*	pThis;
	// Thread critical
	if((pThis = winstrbuf::GetTimer(nId_)) != NULL)
	{
		// Thread critical end
		if(++pThis->m_nCount <= pThis->m_nTimes)
		{
			pThis->m_bNextFlash = ::FlashWindow(hWnd_,pThis->m_bNextFlash);
		}
		else
		{
			winstrbuf::KillTimer(nId_);
		}
	}
}

UINT					winstrbuf::sm_nextTimerId = 0;
map<UINT,winstrbuf::CFlashTimer*>	winstrbuf::sm_mapFlshTimers;

winstrbuf::CFlashTimer *	
				winstrbuf::InstallTimer	( CWnd *			pWnd_
										, DWORD				dwFreq_
										, UINT				nTimes_
										)
{
	CFlashTimer *	pRes = NULL;
	// Thread critical from here to return
	if(pWnd_->SetTimer(++sm_nextTimerId,dwFreq_,CFlashTimer::TimerProc) != sm_nextTimerId)
	{
		return NULL;
	}
	pRes = new CFlashTimer(sm_nextTimerId,pWnd_,nTimes_);
	sm_mapFlshTimers[sm_nextTimerId] = pRes;
	return pRes;
}

winstrbuf::CFlashTimer *	winstrbuf::GetTimer	( UINT				nId_
												)
{
	CFlashTimer *	pRes = NULL;
	// Thread critical from here to return
	if(sm_mapFlshTimers.find(nId_) != sm_mapFlshTimers.end())
	{
		pRes = sm_mapFlshTimers[nId_];
	}
	return pRes;
}

BOOL	winstrbuf::KillTimer	( UINT				nId_
								)
{
	BOOL			bRes = FALSE;
	// Thread critical from here to return
	CFlashTimer *	pFlashTimer = GetTimer(nId_);
	if(pFlashTimer)
	{
		bRes = pFlashTimer->m_pWnd->KillTimer(pFlashTimer->m_nId);
		delete pFlashTimer;
		sm_mapFlshTimers.erase(nId_);
	}
	return bRes;
}

