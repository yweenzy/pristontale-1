#ifndef __XTrapGameClient_H
#define __XTrapGameClient_H
#pragma once

//////////////////////////////////////////////////////////////////////////
typedef struct _tagXTrapConnectInfo {
	char	szConncetID[32];		// 접속 아이디
	char	szConncetServer[32];	// 접속한 서버
	char	szCharName[32];			// 선택한 캐릭터
	char	szCharJob[32];			// 캐릭터 직업
	int		nCharLevel;				// 캐릭터 레벨
}XTRAPCONNECTINFO, *PXTRAPCONNECTINFO;
//////////////////////////////////////////////////////////////////////////

class CXTrapGameClient
{
public:
	CXTrapGameClient(void);
	~CXTrapGameClient(void);

public:
#ifndef __USE_XTRAP_MANAGER_LOG
	BOOL XTrap_StartUp(char *szGameTitle, char *szXTrap_MGR_ServerIP = "127.0.0.1");
#else
	BOOL XTrap_StartUp(char *szGameTitle, char *szXTrap_MGR_ServerIP);
#endif

	inline char* GetXTrapMessagerIP() { return szXTrapMessagerIP; }

	BOOL xTrapConnect(const char *szServerIP);

public:
	XTRAPCONNECTINFO	xTrapConncetInfo;

	//void SetXTrapMessagerConnectInfo(

private:
	inline void SetXTrapMessagerIP(char *szXTrap_MGR_ServerIP) 
								{ ZeroMemory(&szXTrapMessagerIP, sizeof(char)*20); 
								  strcpy(szXTrapMessagerIP, szXTrap_MGR_ServerIP); }
private:
	char szXTrapMessagerIP[20];

};


#endif

extern class CXTrapGameClient	g_XTrap;