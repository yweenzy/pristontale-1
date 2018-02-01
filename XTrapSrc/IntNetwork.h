#ifndef __IntNetwork_H
#define __IntNetwork_H

// xtrap 로그 메신져를 사용할건지 안할건지..
//#define	__USE_XTRAP_MANAGER_LOG

#include <WINSOCK2.h>
#pragma comment( lib, "ws2_32.lib")

#define BUFFSIZE 1500

enum{
	CS_LOGIN = 1,
	SC_LOGIN,
	CS_GAMEDATA,
	SC_GAMEDATA,
	CS_LOGOUT,
	SC_LOGOUT,
	CS_SECUREPACKET,
	SC_SECUREPACKET,
	SC_NONE_CLIENT,
	XTRAP_ERROR
};

typedef struct _packet_head{
	unsigned char	cmd;
	unsigned short	size;
}PACKETHEAD, *PPACKETHEAD;

typedef struct _security_data : PACKETHEAD
{
	char serialkey[1088];		/* Client CREATEKF_OUT_SIZE == Server XC_CLIENTBUF_SIZE */
}SECURITY_DATA, *PSECURITY_DATA;

typedef struct _log_data : PACKETHEAD
{
	char	userID[32];
	char	userPW[32];
}LOG_DATA, *PLOG_DATA;

typedef struct _character_info : PACKETHEAD
{
	char	characterNAME[32];
	int		characterLevel;
	char	RandomValue[32];
	char	Addr[528];			/* Client CREATEKF_IN_SIZE == Server XC_ADDR_SIZE */
}CHARACTERINFO, *PCHARACTERINFO;

typedef struct _game_data : PACKETHEAD
{
	int g_nShipsLeft;
	int g_nPowerLevel;
}GAME_DATA, *PGAME_DATA;

BOOL XTrapWinsockStart();
void XTrapWinsockEnd();

BOOL ConnectXTrapMessagerServer(const char *szMessagerServerIP);

DWORD WINAPI RecvThread( LPVOID pParam );

bool SendLoginData();
bool sendGameData( int , int );
bool SendLogoutData();

bool SendData( char* buff, int size );

#ifdef __USE_XTRAP_MANAGER_LOG
bool SendMGRData( char* buff, int size );
#endif
//////////////////////////////////////////////////////////////////////////
typedef struct _myinfo {
	char	myID[32];
	char	myPW[32];
	char	charName[32];
	int		level;
}MYINFO, *PMYINFO;
//////////////////////////////////////////////////////////////////////////


#endif