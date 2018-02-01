
//######################################################################################
//작 성 일 : 2003-10-10 오후 1:47:46
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
#include <windows.h>
#include <wininet.h>
#include "WavIntHttp.h"
#include "WinIntThread.h"

////////////////////////////////////////////////////////////////////////////////////////
//
HINTERNET					g_hInternetOpen;
int							g_ErrorWinInt;

//
static HANDLE				s_hWinIntThread;
static int					s_WinIntThreadState;
static int					s_WinIntThreadExit;
static CRITICAL_SECTION		s_WinIntThrCS;

//
static DWORD WINAPI WinIntThreadProc( LPVOID lpParameter );


//######################################################################################
//작 성 일 : 2003-10-10 오후 1:51:25
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
int CreateWinIntThread(void)
{
	if( IsErrorWinIntThread() )
		return FALSE;

	if( g_hInternetOpen == NULL )
	{
		g_hInternetOpen = ::InternetOpen( "WinThrHttp", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
		if( g_hInternetOpen == NULL )
		{
			ErrorWinIntThread();
			return FALSE;
		}
	}

	if( s_hWinIntThread == NULL )
	{
		DWORD dwThreadID;
		s_hWinIntThread = ::CreateThread( NULL, 0, WinIntThreadProc, NULL, CREATE_SUSPENDED, &dwThreadID );
		if( s_hWinIntThread == NULL )
		{
			ErrorWinIntThread();
			return FALSE;
		}

		::InitializeCriticalSection( &s_WinIntThrCS );
	}

	if( CreateWavIntHttp( "http://211.39.144.158/NPCSound/" ) == FALSE )
	{
		ErrorWinIntThread();
		return FALSE;
	}


	CreateDirectory( "SaveData" , NULL );
	CreateDirectory( "SaveData\\TalkWav" , NULL );


	return TRUE;
}


//######################################################################################
//작 성 일 : 2003-10-10 오후 1:55:54
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
void DestroyWinIntThread(void)
{
	DestroyWavIntHttp();

	if( s_hWinIntThread )
	{
		if( s_WinIntThreadState )
		{
			s_WinIntThreadExit = 1;
			Sleep(0);

			if( ::WaitForSingleObject(s_hWinIntThread, 1000) == WAIT_TIMEOUT )
                ::TerminateThread( s_hWinIntThread, 0 );
		}
		else
			::TerminateThread( s_hWinIntThread, 1 );

		::CloseHandle( s_hWinIntThread );
        s_hWinIntThread = NULL;

		::DeleteCriticalSection( &s_WinIntThrCS );
	}

	if( g_hInternetOpen )
	{
		::InternetCloseHandle( g_hInternetOpen );
		g_hInternetOpen = NULL;
	}

	//
	ErrorWinIntThread();
}


//######################################################################################
//작 성 일 : 2003-10-16 오후 1:26:48
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
inline void ErrorWinIntThread(void)
{
	g_ErrorWinInt = 1;
}


//######################################################################################
//작 성 일 : 2003-10-16 오후 1:34:31
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
inline int IsErrorWinIntThread(void)
{
	return g_ErrorWinInt;
}


//######################################################################################
//작 성 일 : 2003-10-10 오후 3:42:45
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
inline int IsWinIntThreadState(void)
{
	return s_WinIntThreadState;
}


//######################################################################################
//작 성 일 : 2003-10-10 오후 3:07:04
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
/*
int WinIntThreadSuspend(void)
{
	if( IsErrorWinIntThread() )
		return 0;

	if( s_WinIntThreadState == 0 )
		return 1;

	::EnterCriticalSection( &s_WinIntThrCS );	
	::SuspendThread( s_hWinIntThread );
	s_WinIntThreadState = 0;
	::LeaveCriticalSection( &s_WinIntThrCS );
	return 1;
}
*/


//######################################################################################
//작 성 일 : 2003-10-10 오후 3:30:47
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
int WinIntThreadResume(void)
{
	if( IsErrorWinIntThread() )
		return 0;

	if( s_WinIntThreadState == 1 )
		return 1;

	::EnterCriticalSection( &s_WinIntThrCS );	
	::ResumeThread( s_hWinIntThread );
	s_WinIntThreadState = 1;
	::LeaveCriticalSection( &s_WinIntThrCS );
	return 1;
}


//######################################################################################
//작 성 일 : 2003-10-10 오후 1:56:32
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
static DWORD WINAPI WinIntThreadProc( LPVOID lpParameter )
{
	while( s_WinIntThreadExit == 0 )
	{
		//
		MainWavIntHttp();

		//
		s_WinIntThreadState = 0;
		::SuspendThread( s_hWinIntThread );
	}
	return 1;
}



