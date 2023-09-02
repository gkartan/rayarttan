//////////////////////////////////////////////////////////////////////
// winstrbuf.h:	interface of class winstrbuf.
// author:		g. makulik
// purpose:		see winostream.h
//////////////////////////////////////////////////////////////////////

#if !defined(WINSTRBUF_H)
#define WINSTRBUF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <map>

class winstrbuf : public streambuf  
{
public:
						winstrbuf	( CWnd *			pWnd_
									, int				nBufSize_ = 0
									);
	virtual				~winstrbuf	();

	CWnd *				getwnd		()
							{ return m_pWnd; };

protected:
	virtual int			overflow	( int				c_
									);
	virtual int			sync		();
	virtual	CString		TranslateWinChar	
									( int				c_
									);
	virtual	CString		TranslateWinChar	
									( CString const &	cs_
									);
	virtual	void		PutAlertChar();
private:
	CWnd *				m_pWnd;
	int					m_nBufSize;

	struct CFlashTimer	{
				CFlashTimer	( UINT			nId_
							, CWnd *		pWnd_
							, UINT			nTimes_
							)
					: m_nId(nId_)
					, m_pWnd(pWnd_)
					// Assure to have an odd value for m_nTimes, to
					// get the same window state as before, when the
					// flashing is over
					, m_nTimes((nTimes_%2)?nTimes_+1:nTimes_)
					, m_nCount(0)
				{};
		UINT	m_nId;
		CWnd *	m_pWnd;
		UINT	m_nTimes;
		UINT	m_nCount;
		BOOL	m_bNextFlash;

		static void CALLBACK EXPORT
				TimerProc	( HWND			hWnd_
							, UINT			nMsg_
							, UINT			nId_
							, DWORD			dwTime_
							);
	};
	friend struct CFlashTimer;

	CFlashTimer *		InstallTimer( CWnd *			pWnd_
									, DWORD				dwFreq_
									, UINT				nTimes_
									);
	static CFlashTimer *GetTimer	( UINT				nId_
									);
	static BOOL			KillTimer	( UINT				nId_
									);

	static UINT						sm_nextTimerId;
	static map<UINT,CFlashTimer*>	sm_mapFlshTimers;

			void		put_buffer	();
			void		put_char	( int				c_
									);

};


#endif // !defined(WINSTRBUF_H)
