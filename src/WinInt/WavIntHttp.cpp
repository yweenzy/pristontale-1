//######################################################################################
//작 성 일 : 2003-10-10 오후 4:45:57
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
#include <windows.h>
#include <wininet.h>
#include "ZipLib.h"
#include "RingBuff.h"
#include "WinIntThread.h"
#include "WavIntHttp.h"


////////////////////////////////////////////////////////////////////////////////////////
//
#define MAX_WAV_CONNECT_COUNT		2
#define MAX_WAV_DOWN_COUNT			300

#define MAX_WAV_DOWN_URL			10
static CRingBuff<SWavDownUrl, MAX_WAV_DOWN_URL>		s_WavDownUrlRingBuff;
static SWavDownUrl									s_WavDownUrlBuff[ MAX_WAV_DOWN_URL ];
static BYTE											s_ZipWavDownBuff[ MAX_ZIP_BUFF_SIZE ];

static CRITICAL_SECTION								s_WavDownCS;
static char											s_szWavUrlBasis[128];
static int											s_bCreateWavIntHttp;

//
static int DownWavIntHttp( SWavDownUrl *lpWavDownInfo );


//######################################################################################
//작 성 일 : 2003-10-10 오후 4:49:14
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
int CreateWavIntHttp( char *lpWavUrlBasis )
{
	if( g_hInternetOpen && lpWavUrlBasis[0] )
		strcpy( s_szWavUrlBasis, lpWavUrlBasis );
	else
		return FALSE;

	if( s_bCreateWavIntHttp == FALSE )
		::InitializeCriticalSection( &s_WavDownCS );

	s_bCreateWavIntHttp = TRUE;
	return TRUE;
}


//######################################################################################
//작 성 일 : 2003-10-11 오전 11:18:44
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
void DestroyWavIntHttp(void)
{
	if( s_bCreateWavIntHttp == TRUE )
		::DeleteCriticalSection( &s_WavDownCS );

	s_bCreateWavIntHttp = FALSE;
}


//######################################################################################
//작 성 일 : 2003-10-14 오후 1:07:20
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
int WavIntHttpPush( char *lpRemainderUrl )
{
	if( IsErrorWinIntThread() || s_bCreateWavIntHttp == FALSE )
		return 0;

	SWavDownUrl WavDownInfo;
	::ZeroMemory( &WavDownInfo, sizeof(WavDownInfo) );
	::strcpy( WavDownInfo.szRemainderUrl, lpRemainderUrl );

	::EnterCriticalSection( &s_WavDownCS );
	int ret = s_WavDownUrlRingBuff.Push( WavDownInfo );
	::LeaveCriticalSection( &s_WavDownCS );
	return ret;
}


//######################################################################################
//작 성 일 : 2003-10-14 오후 1:17:41
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
/*
int WavIntHttpPop( SWavDownUrl *lpWavDownInfo )
{
	if( s_bCreateWavIntHttp == FALSE )
		return 0;

	::EnterCriticalSection( &s_WavDownCS );
	int ret = s_WavDownUrlRingBuff.Pop( *lpWavDownInfo );
	::LeaveCriticalSection( &s_WavDownCS );
	return ret;
}
*/



//######################################################################################
//작 성 일 : 2003-10-10 오후 5:29:33
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
static int DownWavIntHttp( SWavDownUrl *lpWavDownInfo )
{
	if( IsErrorWinIntThread() || s_bCreateWavIntHttp == FALSE || lpWavDownInfo->szRemainderUrl[0] == NULL )
		return 0;

	int  i;
	char szUrl[256] = {0,};
	strcpy( szUrl, s_szWavUrlBasis );
	strcat( szUrl, lpWavDownInfo->szRemainderUrl );	

	//
	HINTERNET hOpenUrl;
	for( i=0; i < MAX_WAV_CONNECT_COUNT; i++ )
	{
		hOpenUrl = ::InternetOpenUrl( g_hInternetOpen, szUrl, NULL, 0, 0, 0 );
		if( hOpenUrl )
			break;
	}

	if( hOpenUrl == NULL )
		return 0;

	//
	DWORD dwTotalReadSize = 0, dwWaitSize, dwReadSize;
	for( i=0; i < MAX_WAV_DOWN_COUNT; i++ )
	{
		dwWaitSize = dwReadSize = 0;
		::InternetQueryDataAvailable( hOpenUrl, &dwWaitSize, 0, 0 );
		if( dwWaitSize == 0 )
			break;

		::InternetReadFile( hOpenUrl, s_ZipWavDownBuff+dwTotalReadSize, dwWaitSize, &dwReadSize );
		dwTotalReadSize += dwReadSize;
	}

	::InternetCloseHandle( hOpenUrl );

	//
	SZIP_HEADER *lpZipHeader = (SZIP_HEADER*)s_ZipWavDownBuff;
	if( lpZipHeader->TotalFileSize != dwTotalReadSize )
		return 0;

	i = UnZipDataToDirectory( "SaveData\\TalkWav\\", s_ZipWavDownBuff );
	if( i != ZIP_OK )
		return 0;

	return 1;
}


//######################################################################################
//작 성 일 : 2003-10-11 오전 11:15:25
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
void MainWavIntHttp(void)
{
	if( IsErrorWinIntThread() || s_bCreateWavIntHttp == FALSE )
		return;

    DWORD WavDownUrlCount = 0;
	::EnterCriticalSection( &s_WavDownCS );
	s_WavDownUrlRingBuff.TotalPop( s_WavDownUrlBuff, WavDownUrlCount );
	::LeaveCriticalSection( &s_WavDownCS );

	for( DWORD i=0; i < WavDownUrlCount; i++ )
	{
		if( DownWavIntHttp(&s_WavDownUrlBuff[i]) == FALSE )
		{
            ErrorWinIntThread();
			return;
		}
	}
}








