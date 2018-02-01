#ifdef _xTrap_GUARD

#include "IntNetwork.h"
#include <windows.h>
#include "XTrap.h"
#include "XTrapGameClient.h"
#include <math.h>

#include <stdio.h>

SOCKET m_gSocket;
HANDLE m_hThread;

MYINFO	myInfo;

BOOL XTrapWinsockStart()
{
#ifdef __USE_XTRAP_MANAGER_LOG
	WSADATA wsaData;
	
	if( ::WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) != 0 )
		return FALSE;
	
	if( wsaData.wVersion != MAKEWORD( 2, 2 ) )
	{
		::WSACleanup();
		return FALSE;
	}
#endif
	return TRUE;
}

void XTrapWinsockEnd()
{
	TerminateThread( m_hThread, 0 );

#ifdef __USE_XTRAP_MANAGER_LOG
	closesocket( m_gSocket );
	::WSACleanup();
#endif
}


BOOL ConnectXTrapMessagerServer(const char *szMessagerServerIP)
{
#ifdef __USE_XTRAP_MANAGER_LOG
	m_gSocket = ::socket( AF_INET, SOCK_STREAM, 0 );
	if( m_gSocket == INVALID_SOCKET ) return INVALID_SOCKET;
	
	struct sockaddr_in ServAddr;
	ZeroMemory( &ServAddr, sizeof(ServAddr) );
	ServAddr.sin_family			= PF_INET;
	ServAddr.sin_addr.s_addr	= ::inet_addr( szMessagerServerIP );
	ServAddr.sin_port			= ::htons( 3271 );

	struct linger ling;
	ling.l_onoff  = 1;
	ling.l_linger = 0;
	setsockopt(m_gSocket, SOL_SOCKET, SO_LINGER, (char *)&ling, sizeof(ling));

	if( connect( m_gSocket, (struct sockaddr*)&ServAddr, sizeof(ServAddr)) != 0 )
	{
		return FALSE;
	}
#endif

	m_hThread = CreateThread( NULL, 0, RecvThread, NULL, 0,NULL );

	return TRUE;
}

void RecvLogin( char* buff, int buffsize )
{
	CHARACTERINFO info;
	memset( &info, 0, sizeof(info));

#ifdef __USE_XTRAP_MANAGER_LOG

	memcpy( &info, buff, buffsize );

	strcpy( myInfo.charName, info.characterNAME );
	myInfo.level = info.characterLevel;

#endif
// [XTrapIC #3] Manager 사용을 위한 유저정보 셋팅 부분
	SetOptGameInfo("TestID", "TestServer", myInfo.charName, "TestClass", myInfo.level);

// [XTrapCC #4] 받은 주소맵으로 CreateKF 함수 호출 후 코드맵 전달
	SECURITY_DATA securityd;
	memset( &securityd, 0, sizeof(securityd));
	securityd.cmd = CS_SECUREPACKET;
	securityd.size = sizeof(securityd);

	UCHAR KFBuf[CREATEKF_OUT_SIZE*2] = {0,};
	CreateKFEx(NULL, (PUCHAR)info.Addr, 2, KFBuf);

	memcpy( &securityd.serialkey, KFBuf, CREATEKF_OUT_SIZE*2);
	SendData( (char*)&securityd, securityd.size );
}

DWORD WINAPI RecvThread( LPVOID pParam )
{
	char cBuff[BUFFSIZE];
	int recvret;

	PACKETHEAD packhead;
	
	while( TRUE )
	{
#ifdef __USE_XTRAP_MANAGER_LOG
		recvret = recv( m_gSocket, cBuff, BUFFSIZE, 0 );
#else
		recvret = recv( m_gSocket, cBuff, BUFFSIZE, 0 );
#endif

		if( recvret = 0 ) 
			break;

		memcpy( &packhead, cBuff, sizeof(packhead));

		switch( packhead.cmd ) {
		case SC_LOGIN:
			RecvLogin( cBuff, packhead.size  );
			
			break;
		case SC_GAMEDATA:
			break;
		case SC_LOGOUT:
			break;
		case SC_SECUREPACKET:
			break;
		case SC_NONE_CLIENT:
// [XTrapCC #6] XCrackCheck 함수의 반환값이 0일경우 클라이언트에서 SendLogToMgr() 함수 호출
			SendLogToMgr();
			return 0;
			break;
		case XTRAP_ERROR:
			break;
		default:
			break;
		}
	}
	return 0;
}


bool SendLoginData()
{
#ifdef __USE_XTRAP_MANAGER_LOG
	LOG_DATA loginData;
	memset( &loginData, 0, sizeof(LOG_DATA ));

	loginData.cmd = CS_LOGIN;
	loginData.size = sizeof(loginData);
	wsprintf( loginData.userID, "XTRAP_USER" );
	wsprintf( loginData.userPW, "PASSWORD" );

	return SendMGRData( (char*)&loginData, sizeof(loginData));
#else
	return true;
#endif
}

bool sendGameData( int param1, int param2 )
{
	GAME_DATA gameData;
	memset( &gameData, 0, sizeof(gameData));

	
	gameData.cmd = CS_GAMEDATA;
	gameData.size = sizeof(gameData);
	gameData.g_nShipsLeft = param1;
	gameData.g_nPowerLevel = param2;


	return SendData( (char*)&gameData, sizeof(gameData));
}

bool SendLogoutData()
{
#ifdef __USE_XTRAP_MANAGER_LOG
	PACKETHEAD packhead;
	memset( &packhead, 0, sizeof(packhead));

	packhead.cmd = CS_LOGOUT;
	packhead.size = sizeof( packhead );
	return SendMGRData( (char*)&packhead, sizeof(packhead));
#else
	return true;
#endif
}

#ifdef __USE_XTRAP_MANAGER_LOG
bool SendMGRData( char* buff, int size )
{
	int sendret;
	sendret = send( m_gSocket, buff, size, 0 );
	if( sendret <= 0 ) return false;
	return true;
}
#endif

bool SendData( char* buff, int size )
{
	int sendret;
	sendret = send( m_gSocket, buff, size, 0 );
	if( sendret <= 0 ) return false;
	return true;
}

#endif