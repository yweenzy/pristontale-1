
#ifndef _ignore_messageprotocol_h_20070126_
#define _ignore_messageprotocol_h_20070126_

#include "stdio.h"
#include <windows.h>
#include "XTrap.h"


#define		szMAP1_FILE_NAME  "map1.cs3"
#define		szMAP2_FILE_NAME  "map2.cs3"

#define CC4FILE_NUM	2											// 사용될 MapFile 의 개수 설정
//--------------------------------------------------------< Debug 파일 출력 >
#define	_XTRAP_DEBUG		// define 되어있으면 아래와 같은 로그 파일을 남긴다.
							// 유니크 키값의 로그파일을 남기기 원하면 XApi_Client.cpp 에 주석을 풀어라
							// 이것은 디버깅 할때만 풀어라. 

#define SERVER_XTRAP_DEBUG_FILE	"_ignore_xtrap_server_debug.dat"
#define	CLIENT_XTRAP_DEBUG_FILE	"_ignore_xtrap_client_debug.dat"



typedef struct _xtrap_session_buf
{
	char	m_PacketBuf[XTRAP_CC4_BUFFERSIZE_COMMUNICATION_BASE];
	char	m_SessionBuf[XTRAP_CC4_BUFFERSIZE_SESSION];
	
	DWORD	dwTime;
	bool	bFirst;
	bool	bGetTRANSPLAYDATA;
	int		KeyGenWaitCount;
	
	FILE	*m_fp;
	
	_xtrap_session_buf()
	{
		Clear();
	};

	~_xtrap_session_buf()
	{

	};

	void Clear(void)
	{
		memset(this->m_PacketBuf,0,sizeof(this->m_PacketBuf));
		memset(this->m_SessionBuf,0,sizeof(this->m_SessionBuf));
		dwTime = 0; 
		bFirst = true;	
		m_fp = 0;
		bGetTRANSPLAYDATA = false;
		KeyGenWaitCount = 0;
	};

} XTRAPCS_SESSION_BUF;				// 세션별로 사용될 로컬 변수. 예제에서는 편의상 구조체로 정의


//--------------------------------------------------------<	Packet struct for XTrap Packet >
typedef struct _xtrap_packet
{
	int		m_iSize;
	int		m_iCmd;			
	char	aData[512];	// array for Data

	_xtrap_packet()
	{
		m_iCmd = 0;
		m_iSize = 0;
		ZeroMemory(aData,sizeof(aData));
	};

} XTrapPacket;

//--------------------------------------------------------< Message protocol for XTrap Packet >
#define		XTRAP_CMD_UNIQKEY		0x44444444
#define		XTRAP_CMD_SEEDKEY		0x44446666
#define		XTRAP_CMD_DISCONNECT	0x44447777

#endif