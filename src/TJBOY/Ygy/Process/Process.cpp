#define PROCESS_CPP
#include <windows.h>
#include <stdio.h>
#include "..\\YgyHeader.h"
//ktj : vrun.dat luncher.ini



extern void fd( char *fmt, ...);
extern void fd2( char *fmt, ...);

extern HWND hwnd; //프리스턴 핸들 



#if 0//ktj

//라이브러리를 사용하면 dll함수사용시 일반함수처럼 사용가능해서 편리하게 쓸수있다.
//lib의 경로는 항상 프로젝트의 루트에서부터 써줘야 찾을수 있으므로 주의
#pragma comment(lib, "tjboy/HookDll.lib") 
#include "../../khook.h"
UINT  g_uMsg = 0;

//훅킹dll에서 보내줄 메시지번호
#define WM_KEYBOARDHOOK_ACTIVITY (WM_USER + 11)
//////////////////////////////////////////////////////
//
// dll의 스타트 함수
//
//////////////////////////////////////////////////////
void dll_open()
{
	g_uMsg = WM_KEYBOARDHOOK_ACTIVITY;
	
	if (InstallKeyboardHook (hwnd, g_uMsg))
		fd2("Hook installed OK\n");
	else
		fd2("Hook install FAILED\n");
} 

//////////////////////////////////////////////////////
//
// dll의 end 함수(*.lib안쓸때 써야되는건데 일단남겨둠)
//
//////////////////////////////////////////////////////
void dll_close()
{
#if 0
	if(Hook != NULL) {
		UnhookWindowsHookEx(Hook);
		//DLL을 메모리에서 제거.
		FreeLibrary(hLib);
		Hook = NULL;
	}
#endif

}

#endif

extern char UserAccount[256];		//id가 들어있는 버퍼
extern char	szConnServerName[16];	//접속한 서버이름이 들어있는 버퍼

int vrunRuning = 0;					//vrun.dat의 실행여부

int gameServerPORT=0;
char gameServerIP[16]={0,};
BOOL bMic = 0;

char g_AllClanWon[_CLANWON_MAX][STRING_MAX];

CProcess::CProcess()
{
	m_cMemMap			 = NULL;	
	m_hRemoteProcess	 = NULL;
	m_hRemoteWnd		 = NULL;	
	//m_nKeyDown			 = -1;
	m_bIsMemMap			 = FALSE;
	m_IsStart			 = FALSE;

}

CProcess::~CProcess()
{
}



extern HWND hwnd; //프리스턴 핸들 
int CProcess::InitRemoteProcess()
{
	fd2("InitRemoteProcess()00");
	m_hRemoteWnd = FindWindow(REMOTEPROCESS_NAME, NULL);
	fd2("InitRemoteProcess()11 m_hRemoteWnd  %d", m_hRemoteWnd );

	if(m_hRemoteWnd)  //프리스턴 클라이언트를 보낸다.
	{
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0, (LPARAM)hwnd);
		return 1;
	}
	return 0;
	






	/*
	int static chk = 0;

	if(chk ==1)
	{


	fd2("InitRemoteProcess()00");
	m_hRemoteWnd = FindWindow(REMOTEPROCESS_NAME, NULL);
	fd2("InitRemoteProcess()11 m_hRemoteWnd  %d", m_hRemoteWnd );

	if(m_hRemoteWnd)  //프리스턴 클라이언트를 보낸다.
	{
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0, (LPARAM)hwnd);
		return 1;
	}
	return 0;
	
	}







chk = 1;


	fd2("InitRemoteProcess() 00");

	PROCESS_INFORMATION pi={0,};
	STARTUPINFO si={0,};

	//if(CreateProcess(NULL,REMOTEPROCESS_EXE,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)  == 0)
	char buf[256];
	//ktj : 원본
	//wsprintf(buf, "%s %d", REMOTEPROCESS_EXE, hwnd);
	wsprintf(buf, "%s %d", "vrun.exe", hwnd);
	

	if(CreateProcess(NULL,buf,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi)  == 0)
	{
		fd2("InitRemoteProcess() 11 error");

		return -1;
	}


	m_hRemoteProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pi.dwProcessId);


	fd2("InitRemoteProcess() 22 ");


	//실행시킨 핸들값을 알아낸다.
	DWORD dwExitCode;
	int nCount = 0;

	if(m_hRemoteProcess == NULL){
		fd2("InitRemoteProcess() 33 error");
		return -1;
	}
	GetExitCodeProcess(m_hRemoteProcess,&dwExitCode);
	if(dwExitCode == STILL_ACTIVE)
	{
getloop:	
		Sleep(100);

		m_hRemoteWnd = FindWindow(REMOTEPROCESS_NAME, NULL);
		if(m_hRemoteWnd== NULL)
		{
			DWORD dwError;
			dwError = GetLastError();
			dwError = dwError;
			if(nCount > 100)
			{
				fd2("InitRemoteProcess() 44 error ");
				return -4;
			}
			nCount++;
			   goto getloop;
		}
		else
		{
			fd2("InitRemoteProcess() 55 OK ");
			return 1;
		}
	}

	fd2("InitRemoteProcess() 66 error ");
	return -5;
	*/

}



int CProcess::InitRmoteProcessWnd()
{
	m_nStep	 = INSIDE_GAMELOGIN;
	return 1;
}


/*===========================================================================================
현재는 메모리 맵과 원격프로세스 핸들을 가지고 오기위해서 초기화 하는 역할
============================================================================================*/
BOOL CProcess::Init()
{	
	
	if(m_IsStart)
	{
		

		
		m_cMemMap = (CMemMap*) new CMemMap;
		if(m_cMemMap == NULL)
		{
			return FALSE;
			m_bIsMemMap = FALSE;
		}

		m_cMemMap->SetMemMapSize(MEMORYMAP_MAX);  //MEMORYMAP_MAX  256
		m_cMemMap->SetName(MEMORYMAP_NAME);
		m_cMemMap->InitMemoryMap();
		m_bIsMemMap = TRUE;

		
		


		//원격 프로세스 핸들을 가지고 옴
		InitRmoteProcessWnd();
	}
	

	return TRUE;
}


/*===========================================================================================
현재는 메모리 맵을 삭제하는 함수
============================================================================================*/
VOID CProcess::Clear()
{
	if(!m_IsStart) return;

	UserOut();	//유저가 나가도록..


	if(m_hRemoteProcess != NULL)
		TerminateProcess(m_hRemoteProcess,0);

	m_Packet.Clear();
	m_cMemMap->Clear();
	if((m_cMemMap != NULL) && m_bIsMemMap)
	{
		delete m_cMemMap;
	}
}

/*===========================================================================================
1. 메모리 맵에서 데이타를 가지고 옴 m_cMemMap->ReadMemoryMap
2. 메모리 맵에 있는 데이타를 옮겨옴 m_Packet.GetData()
3. 가지고 온 데이타를 파싱			m_Packet.Parsing()
============================================================================================*/
void PacketParsing()	//winmain.cpp
{
	g_CtrlProcess.PacketParsing();
}
VOID CProcess::PacketParsing()
{
	m_cMemMap->ReadMemoryMap((char*)m_Packet.GetData());
	m_Packet.Parsing();
}

VOID CProcess::Main()
{
	if(!m_IsStart) return;

	switch(m_nStep)
	{
	case INSIDE_GAMELOGIN:

#if 0
		m_Packet.SetLogin(UserAccount);
		m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetGameLogin());
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,(WPARAM)0,0);
#endif

		//ktj : ip, port보낸다.
		IPPORT ipport;
		ZeroMemory(&ipport, sizeof(ipport));

		ipport.sIndex.dwIndex = INSIDE_IPPORT;
		strcpy(ipport.ip,gameServerIP);
		ipport.port = gameServerPORT;
		//ipport.Chwnd;


		m_cMemMap->WriteMemoryMap((char*)&ipport, sizeof(ipport));
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0,0);

		m_nStep = -1;
		break;

	case INSIDE_USERINFO:
		m_userInfo.sIndex.dwIndex = INSIDE_USERINFO;
		m_cMemMap->WriteMemoryMap((char*)&m_userInfo, sizeof(m_userInfo));
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0,0);
		m_nStep = -1;
		break;

	case INSIDE_USERINFOCHG:
		m_userInfo.sIndex.dwIndex = INSIDE_USERINFOCHG;
		m_cMemMap->WriteMemoryMap((char*)&m_userInfo, sizeof(m_userInfo));
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0,0);
		m_nStep = -1;
		break;




	case INSIDE_MICONOFF:
		VOICEONOFF vm;
		ZeroMemory(&vm, sizeof(vm));

		vm.sIndex.dwIndex = INSIDE_MICONOFF;
		
		//bMic = !bMic;
		vm.bMicONOFF = bMic;

		m_cMemMap->WriteMemoryMap((char*)&vm, sizeof(vm));
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0,0);
		m_nStep = -1;
		break;













/*
	//ktj : 사용안함.
	case INSIDE_SELECTCHACLAN:
		m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetSelectChaClan());
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,(WPARAM)20000,0);
		m_nStep = -1;
		 break;	
	case INSIDE_GAME_OUT:
		m_Packet.SetUserOut("ycy916","헌트가나감",30043);
		m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetUserOut());
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,(WPARAM)20000,0);
		m_nStep = -1;
		break;

	case INSIDE_WAVRECORD:
		m_Packet.SetWavRecord();
		m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetWavRecord());
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,(WPARAM)20000,0);
		m_nStep = -1;		
		break;
	case INSIDE_WAVEPLAY:
		m_Packet.SetWavPlay();
		m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetWavPlay());
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,(WPARAM)20000,0);
		m_nStep = -1;
		break;
*/

	}
}




// 박철호 (마이크 온오프)
VOID	ParkSetMicOnOFF();

VOID	ParkSetMicOnOFF()
{
	g_CtrlProcess.SetMicOnOFF();
}
VOID	CProcess::SetMicOnOFF()
{
	if(!m_IsStart) return;

	m_nStep = INSIDE_MICONOFF;
}








VOID CProcess::TestInputData(HWND hWnd,WPARAM wParam,LPARAM lParam,char *temp)
{
/*

	switch(wParam)
	{
	case VK_RETURN:
		switch(m_nKeyDown)
		{
		case -1:		
			strcpy(temp,"게임시작................");
			InvalidateRect(hWnd,NULL,1);
			m_nKeyDown++;
			//m_nStep = INSIDE_GAMELOGIN;
			break;
		case 0:
			strcpy(temp,"게임로그인 화면........");
			InvalidateRect(hWnd,NULL,1);
			m_nStep = INSIDE_GAMELOGIN;
			m_nKeyDown++;
			break;
		case 1:	
			strcpy(temp,"케릭터 선택........");
			InvalidateRect(hWnd,NULL,1);
			m_nStep = INSIDE_USERINFO;
			m_nKeyDown++;
			break;	
		case 2:
			strcpy(temp,"클랜에 가입된 캐릭터 선택");
			InvalidateRect(hWnd,NULL,1);
			m_nStep = INSIDE_SELECTCHACLAN;
			m_nKeyDown++;
			break;
		}
		break;
	case VK_ESCAPE:		
		strcpy(temp,"게임종료");
		InvalidateRect(hWnd,NULL,1);
		m_nStep = INSIDE_GAME_OUT;
		m_nKeyDown = -1;
		break;
	case VK_F1:
		m_Packet.SetIDandChaName("ycy916","헌트지존");
		m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetIDandName());
		SendMessage(hWnd,WM_CALLMEMMAP,(WPARAM)20000,0);
		break;
	case VK_F2:
		m_Packet.SetClanInfo(3020203,"테스트클랜");
		m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetClanInfo());
		SendMessage(hWnd,WM_CALLMEMMAP,(WPARAM)20000,0);
		break;
	case VK_F3:
		m_Packet.SetUserOut("yoo","헌트가나감",30043);
		m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetUserOut());
		SendMessage(hWnd,WM_CALLMEMMAP,(WPARAM)20000,0);
		break;
	}
*/
}

VOID CProcess::SetStep(int step)
{
	m_nStep = step;
}





//===========================================================================//
#if 0
VOID CProcess::SetSelectCha(char *id,char *chaname, char *clanname,DWORD clannum)
{
	if(!m_IsStart) return;
	
	//ktj : 여기서 데이타만 저장한후 보내야 될경우에만 보내는 처리를 해야할듯.
	ZeroMemory(&m_userInfo,sizeof(m_userInfo));
	m_userInfo.sIndex.dwIndex = INSIDE_USERINFO;
	if(id != NULL)
		strncpy(m_userInfo.szID,id,strlen(id));
	if(chaname != NULL)
		strncpy(m_userInfo.szCharName, chaname,strlen(chaname));
	if(clanname !=NULL)
		strncpy(m_userInfo.szClanName,clanname,strlen(clanname));
	m_userInfo.dwClanNum = clannum;


	//보낼경우에는 이렇게
	m_nStep = INSIDE_USERINFO;
}
#endif

int firstFlag = 0;
VOID CProcess::SetSelectCha(char *id,char *chaname, char *clanname,DWORD clannum, int utype)
{
	if(!m_IsStart) return;

	//데이타가 맨 처음 셋팅될때 =========================
	if(firstFlag==0) {
		firstFlag = 1;	
	
		//ktj : 여기서 데이타만 저장한후 보내야 될경우에만 보내는 처리를 해야할듯.
		ZeroMemory(&m_userInfo,sizeof(m_userInfo));
		m_userInfo.sIndex.dwIndex = INSIDE_USERINFO;
		//if(id != NULL)
		//	strncpy(m_userInfo.szID,id,strlen(id));

		extern char UserAccount[256];		//id가 들어있는 버퍼
		strncpy(m_userInfo.szID,UserAccount,strlen(UserAccount));


		if(chaname != NULL)
			strncpy(m_userInfo.szCharName, chaname,strlen(chaname));
		if(clanname !=NULL)
			strncpy(m_userInfo.szClanName,clanname,strlen(clanname));
		m_userInfo.dwClanNum = clannum;
		m_userInfo.utype = utype;

		//서버이름셋팅

		

		if(strlen(szConnServerName)<15) {
			strncpy(m_userInfo.szConnServerName,szConnServerName,strlen(szConnServerName));
		
		
			fd2("프리스턴클라: 서버이름  %s ",szConnServerName);
		}
		else {
			//짤라야될듯
			szConnServerName[15] = 0;
			fd2("프리스턴클라: 서버이름 이상????????????????????? %s ",szConnServerName);
		}
		//보낼경우에는 이렇게
		m_nStep = INSIDE_USERINFO;
		return;
	}


	//이전에 설정되 있던 클랜 번호와 방금새로 들어온 클랜번호가 같으면
	//새로운 데이타를 보낼 필요가 없다.
	if(m_userInfo.dwClanNum == clannum) {
		return;
	}



	//ktj : 여기서 데이타만 저장한후 보내야 될경우에만 보내는 처리를 해야할듯.
	m_userInfo.sIndex.dwIndex = INSIDE_USERINFOCHG;
	if(clanname !=NULL)
		strncpy(m_userInfo.szClanName,clanname,strlen(clanname));
	else {
		memset(&m_userInfo.szClanName, 0, sizeof(m_userInfo.szClanName));
	}
	m_userInfo.dwClanNum = clannum;
	m_userInfo.utype = utype;

	//클랜이없어지거나 바뀐경우 db를 바꾸기위함.
	m_nStep = INSIDE_USERINFOCHG;	
}



VOID CProcess::UserOut()
{
	if(!m_IsStart) return;
	/*
	m_Packet.SetUserOut(NULL,NULL,0);
	m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetUserOut());
	SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,(WPARAM)20000,0);
	*/
	P_Out pout;
	pout.sIndex.dwIndex = INSIDE_GAME_OUT;

	m_cMemMap->WriteMemoryMap((char*)&pout, sizeof(pout));
	SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,(WPARAM)0,0);
	Sleep(1000*2);	//프로세스삭제전에 시간을 주기위함.
}

//"mapedit.INI" 파일안의 "INITGAME"의 각종 옵션을 읽는다.
int read_GameOption(char *optStr, char *rStr)
{
    char fname[] = "luncher.INI";
    char folder[] = ".\\";
    char strFilename[128];
    strcpy ( strFilename , folder);
    strcat ( strFilename , fname );

    if(rStr==NULL) { //int형
        return GetPrivateProfileInt("INITGAME", optStr, 0, strFilename );
    }
    //string형
    GetPrivateProfileString("INITGAME", optStr, NULL, rStr, 128, strFilename);
    return 0;
}


int InitGAMEopt()
{
    FILE *fp;
    fp = fopen("luncher.ini", "rb");
    if(fp==NULL) {
        return 0;
    }
    else {                      //디버깅버전의 첵크(mapedit.ini사용시)
        fclose(fp);             //일단 닫고 셋팅 데이타를 mapedit.ini에서 꺼낸다.

		//게임 서버 ip,port
		read_GameOption("gameServerIP", gameServerIP );
		gameServerPORT = read_GameOption("gameServerPORT", NULL );
    }
	return TRUE;
}

/*
void abc()
{
g_CtrlProcess.CheckIPandPort(0, 0); 
}
*/


VOID CProcess::CheckIPandPort(char *ip, int port)
{
	
	//ktj : auth.cpp : 클랜서버가 없다면 작동안한다.
	extern BOOL bip_port_error;
	if(bip_port_error==TRUE) {
		m_IsStart = FALSE;
		return;

	}
	


	fd2("CheckIPandPort() 00 ");


	if(InitGAMEopt() == 0)	//luncher.ini가 없으면 겜클라이언트로부터 ip,port를 받아온다.
	{
		if((ip != NULL ) &&(port != 0))
		{
			fd2("CheckIPandPort() 11 ");

			gameServerPORT = port;
			strncpy(gameServerIP,ip,strlen(ip));

			if(InitRemoteProcess() == 1) {
				vrunRuning = 1;					//vrun.dat의 실행여부
				m_IsStart = TRUE;
				fd2("CheckIPandPort() 22 OK ");
			}
		}
		else	//ini파일이 없고 서버에서도 ip,port셋팅이 없으면 그냥이걸로 한다.
		{


			fd2("CheckIPandPort() 33 ");
			//m_IsStart = FALSE;
			gameServerPORT = 7000;
			strcpy(gameServerIP,"211.44.231.13");

			if(InitRemoteProcess() == 1) {
				vrunRuning = 1;					//vrun.dat의 실행여부
				m_IsStart = TRUE;

				fd2("CheckIPandPort() 44 OK ");
			}

		}
	}
	else //luncher.ini가 있으면 거기서 받아온다.
	{
		if(gameServerPORT != 0 && gameServerIP[0] != 0)
		{

			fd2("CheckIPandPort() 55 ");
			if(InitRemoteProcess() == 1) {
				vrunRuning = 1;					//vrun.dat의 실행여부
				m_IsStart = TRUE;
				fd2("CheckIPandPort() 66 ok ");
			}
		}
		else
		{
			m_IsStart = FALSE;

			fd2("CheckIPandPort() 77 false ");
		}
	}
}

VOID CProcess::SetClanChat(char *msg)
{
/*
	if(!m_IsStart) return;
	m_Packet.SetClanChat(msg);
#ifdef __YOUDEBUG
	MiLae_Debug_txt("클랜메세지 : %s",msg);
#endif
	m_cMemMap->WriteMemoryMap((char*)&m_Packet.GetClanChat());
	SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,(WPARAM)20000,0);

#ifdef __YOUDEBUG
	MiLae_Debug_txt("클랜메세지 : WM_CALLMEMMAP 호출");
#endif
*/

}