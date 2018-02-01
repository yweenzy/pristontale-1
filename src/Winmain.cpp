#define _SINBARAM

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <ZMOUSE.H>
#include <process.h>

#include "common.h"

#include "smlib3d\\smd3d.h"
#include "smwsock.h"
#include "smreg.h"

#include "character.h"
#include "playmain.h"
#include "Sound\\dxwav.h"
#include "effectsnd.h"
#include "fileread.h"
#include "netplay.h"
#include "makeshadow.h"
#include "particle.h"
#include "field.h"
#include "hoBaram\\holinkheader.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

#ifdef _SINBARAM
#include "sinbaram\\sinlinkheader.h"
#endif

#include "playsub.h"
#include "cracker.h"
#include "SkillSub.h"

#include "resource.h"

#include "TextMessage.h"		//문자 메세지 헤더
#include "Language\\language.h"
#include "Language\\jts.h"		//일본어 코드 첵크

#include "CurseFilter.h"		//욕설필터
#include "damage.h"
#include "AreaServer.h"

#include "BellatraFontEffect.h"

//------------------------------------< _ignore_xtrap_
#ifdef _LANGUAGE_VEITNAM
#ifdef _XTRAP_GUARD_4_CLIENT
	#include ".\\XTrapSrcD5\\Launcher\\XTrap4Launcher.h"
#endif
#endif
//------------------------------------  _ignore_xtrap_ >

//XTRAP 라이브러리 적용
#ifdef _XTRAP_GUARD_4_CLIENT
#include "XTrapSrcD5\\Client\\XTrap4Client.h"	
#pragma comment( lib,"XTrapSrcD5\\Client\\XTrap4Client_mt.lib")
#endif

#ifdef _XTRAP_GUARD_4_CLIENT // HEAP MEMERY TEST
#include "XTrapSrcD5\\ClientExt\\XTrap4ClientExt1.h"	
#pragma comment( lib,"XTrapSrcD5\\ClientExt\\XTrap4ClientExt1_st.lib")
#pragma comment( lib,"XTrapSrcD5\\ClientExt\\XTrap4ClientExt1_mt.lib")
#pragma comment( lib,"XTrapSrcD5\\ClientExt\\XTrap4ClientExt1_mtdll.lib")
#endif

//박재원 - XignCode
#ifdef _XIGNCODE_CLIENT
#include "Xigncode\Client\zwave_sdk_client.h"
#endif

//중국 xTrap
#ifdef _xTrap_GUARD
#include "XtrapSrc/xtrapgameclient.h"
#endif

#include "actiongame.h"


//######################################################################################
//작 성 자 : 박철호
#define WM_CALLMEMMAP				WM_USER+3   //메모리맵에 메세지가 있다가 통보

#ifdef PARKMENU
#include "TJBOY\\\\Park\\MicVolume.h"
extern BOOL bMic;
extern int vrunRuning;
extern int micInit;
#endif

//######################################################################################

//######################################################################################
//작 성 자 : 오 영 석
#include "WinInt\\WinIntThread.h"
#include "FullZoomMap.h"
#include "FontImage.h"
//######################################################################################


//char szAppName[]="프리스톤 테일";
HWND hwnd;
HWND hTextWnd;
HWND hFocusWnd;

extern int sinChatDisplayMode; //{ 0- 아무것도 안그리기  1-보통  2-상점 }
extern int sinChatInputMode;   //{ 0- 아무것도 안그리기  1-보통  2-상점 }

HDC hdc;
int quit = 0;
int QuitSave = 0;
int WinSizeX = 640;
int WinSizeY = 480;
int	WinColBit = 16;

float g_fWinSizeRatio_X;
float g_fWinSizeRatio_Y;

int TextMode;

int BrCtrl = 0;

DWORD	dwM_BlurTime = 0;


int MouseButton[3] = { 0,0,0 };
extern int TJwheel; //ktj
extern int keydownEnt;


//IME 관리 라이브러리 추가
#pragma comment( lib, "imm32.lib" )


BOOL smSetCurrentWindows( HWND wnd );
int InitD3D(HWND hWnd);
void CloseD3d();
void smPlayD3D( int x, int y, int z, int ax, int ay, int az );
int smSetMode( HWND hWnd , DWORD Width, DWORD Height, DWORD BPP );


///////////////////////// IME 관련 //////////////////////////////
#include "ime.h"

ImeClass IMETest;
CStrClass sz;
LRESULT CALLBACK EditWndProc01(HWND,UINT,WPARAM,LPARAM);
WNDPROC		OldEditProc01;
char szIME_Buff[10][64];


//디버그 플랙 백업
DWORD	dwDebugBack;
DWORD	dwDebugXor;

///////////////////////// 게임에 필요한 선언들 ///////////////////
int MouseX , MouseY;
int MousemX, MousemY;
int angX = 0;
int angY = 0;
DWORD	dwLastMouseMoveTime;
DWORD	dwLastCharMoveTime;

int xPos,yPos;

POINT3D TraceCameraPosi;
POINT3D TraceTargetPosi;
int	PlayCameraMode = 1;
int AutoCameraFlag = FALSE;
int	CameraInvRot = 0;					//카메라 회전 방향
int	CameraSight = 0;					//카메라 시야 조절


DIRECTDRAWSURFACE lpDDSMenu;

int DisplayDebug = 0;
int DispInterface = TRUE;			//인터페이스 그리기
int	DebugPlayer = FALSE;				//디버깅 카메라 플레이어
int	LastAttackDamage = 0;			//마지막 공격 데미지

int	HoMsgBoxMode = 0;				//호동 메세지 박스 프레임 표시 비표시 토글

//sinTrade.cpp 에 디파인 되 있도다.
#define TRADEBUTTONMAIN_X		513
#define TRADEBUTTONMAIN_Y		3

POINT pHoPartyMsgBox = { TRADEBUTTONMAIN_X, TRADEBUTTONMAIN_Y };	//호동 파티신청 메세지 박스


//운영자용 IP
char *szOperationIP[5] = {
	"211.61.248.221",
	"211.108.45.",
	"211.44.231.",
	"221.148.123.",
	0
};

char szExitInfo_URL[128]={ 0, };		//게임 종료시 표시하는 URL 경로


#define ANX_NONE	-32768

int pX;
int pY;
int pZ;
int	dpX=0;
int dpY=0;
int dpZ=0;

int whAnx = 64;
int anx = 64;
int	ViewAnx = 64;
int	ViewDist = 100;
int	PlayFloor = 0;
int any = 0;
int anz = 0;
int dist = 100;
int CaTarDist = 0;
int	CaMovAngle = 0;

int tX = 0;
int tY = 0;
int tZ = 0;


int	ImeChatLen = 0;		//IME 관련 채팅 문자길이
POINT	ImePositon;		//IME 위치 저장

int SetMousePlay( int flag );

//호동동 추가(카메라 이펙트)
int WaveCameraMode = TRUE;
POINT3D WaveCameraPosi;									
int	WaveCameraFactor = 0; // 10*fONE;		    //흔드는 크기
int	WaveCameraTimeCount = 0;
int	WaveCameraDelay = 0;
BOOL WaveCameraFlag = FALSE;


//게임 초기화
int GameInit();
//게임 닫기
int GameClose();
//게임 선택
int SetGameMode( int mode );

//채팅창 문자 설정및 활성화
int	SetChatingLine( char *szMessage );

int GameMode = 0;

//그리기 크리티컬 섹션
CRITICAL_SECTION	cDrawSection;

//해외용 함수
int HoInstallFont();	//폰트 등록하기
int HoUninstallFont();	//폰트 삭제하기

HINSTANCE hinst; 
BOOL WINAPI DllMain(HINSTANCE hinstDLL,  // handle to DLL module
					DWORD fdwReason,     // reason for calling function
					LPVOID lpvReserved   // reserved
					) 
{
	hinst = hinstDLL;

	return TRUE;
}

#define IDC_TEXT	101

BYTE VRKeyBuff[256];


LONG APIENTRY WndProc(HWND,UINT,WPARAM,LPARAM);
void PlayD3D();
//코멘드 라인 분석 설정
int DecodeCmdLine( char *lpCmdLine );
//불법 소프트 웨어 단속에 대비한 레지스트리 조작
int HaejukReg();

//폰트 생성
HFONT	hFont = 0;
int SetCreateFont();

//크리티컬 섹션 선언
CRITICAL_SECTION	cSection;

//IME Context
HIMC hImc;
HIMC hImcEdit;

extern rsRECORD_DBASE	rsRecorder;					//서버에 게임데이타 기록장치
extern INT WINAPI ServerWinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine,INT nCmdShow);

char	szCmdLine[128];			//커맨드라인 문자열


//클로즈 베타 테스터 초기화
extern int	InitCloseBetaUser();
//서버에 기록된 전체 데이타를 확인하여 의심가는 유저를 찾는다
extern int	CheckServerRecordData();

//캐릭터 정보 파일에서 해독하여 설정한다
extern int RestoreBackupData( char *szListFile , char *BackupPath );

#ifdef	_LANGUAGE_JAPANESE

static char *StripArg0(LPSTR cmdline)
{
    char *ptr;

    ptr = cmdline;
    while (*ptr && *ptr == ' ' || *ptr == '\t')
        ptr++;

    if (*ptr == '"') {
        ptr++;
        while (*ptr && *ptr != '"')
            ptr++;
        if (*ptr == '"') {
            ptr++;
            while (*ptr && *ptr == ' ')
                ptr++;
            return ptr;
        }
    }
    else {
while (*ptr && *ptr != ' ')
            ptr++;
        if (*ptr == ' ')
            return ptr+1;  
    }

    return ("");
}
#endif

#ifdef _W_SERVER
#include "mini_dump.h"
Mini_Dump CMiniDump;
#endif

#ifdef _DEBUG
extern "C" WINBASEAPI int WINAPI AllocConsole();
#endif

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine,INT nCmdShow)
{
	Utils_DeleteLogFiles();

	#ifdef _DEBUG
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
	#endif

	//------------------------------------< _ignore_xtrap_
	#ifdef _LANGUAGE_VEITNAM
	#ifdef _XTRAP_GUARD_4_CLIENT
	{
		#pragma comment(lib,".\\XTrapSrcD5\\Launcher\\XTrap4Launcher_mt.lib")
		#pragma comment( lib, "Urlmon.lib")
		#pragma comment( lib, "Wininet.lib")
	    XTrap_L_Patch(XTRAP_CONFIG_ARG, NULL, 60);
	}
	#endif
	#endif
	//------------------------------------  _ignore_xtrap_ >


	Utils_Log(LOG_DEBUG, " ------------ WINMAIN ---------------- ");
	MSG msg;
	WNDCLASS wndclass;
	hinst = hInst;
	int	sx,sy;

	lstrcpy( szCmdLine , lpCmdLine );


	initSinCos();		//삼각함수 초기화

	#ifdef _W_SERVER
		smConfigDecode( "hotuk_server.ini"  );
	#else
		smConfigDecode("hotuk.ini");
	#endif

	ReadShotcutMessage( "ShortCut.ini" );		//단축 메세지 읽어 오기
	DecodeCmdLine( lpCmdLine );

	//크리티칼 섹션 초기화
	InitializeCriticalSection( &cSection );
	InitializeCriticalSection( &cDrawSection );
	InitializeCriticalSection( &cSection_Main );
	
	srand( GetCurrentTime() );		//랜덤 초기화

#ifdef _W_SERVER
	if ( smConfig.WinMode<0 ) 
	{
		return ServerWinMain( hInst,  hPreInst, lpCmdLine, nCmdShow);
	}
#endif
	//Because chat in Vista before Windows creates the sound generation
	InitDirectSound();

	//The name registry operations ... (illegal software Enforcement)
	HaejukReg();

	WinSizeX = smConfig.ScreenSize.x;
	WinSizeY = smConfig.ScreenSize.y;
	WinColBit = smConfig.ScreenColorBit;
	renderDevice.SetWindowMode(smConfig.WinMode);

	sx = WinSizeX;
	sx = WinSizeY;

	//XTrap
	#ifdef _XTRAP_GUARD_4_CLIENT
	{
		XTrap_C_Start(XTRAP_CONFIG_ARG,NULL);	//XTrapD5
		XTrap_CE1_Func10_Init();				//XTrap Heap 메모리변조 방지

	#endif

	//XTrap v4,0
	#ifndef _XTRAP_GUARD_4_
		#ifndef _xTrap_GUARD
			//nProtect 실행 //디버그시 동작못하게 막음 kyle
			sx = WinSizeX;
			sy = WinSizeY;
		#else
			if ( WindowMode ) 
			{
				sx = WinSizeX;
				sy = WinSizeY;
			}
			else
			{
				sx = GetSystemMetrics(SM_CXSCREEN);
				sy = GetSystemMetrics(SM_CYSCREEN);
			}
		#endif
	#endif

	if (!hPreInst)
	{
		wndclass.style			=	CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
		wndclass.lpfnWndProc	=	WndProc;
		wndclass.cbClsExtra		=	0;
		wndclass.cbWndExtra		=	0;
		wndclass.hInstance		=	hInst;
		wndclass.hIcon			=	LoadIcon (hInst, MAKEINTRESOURCE(IDI_DEFAULT_ICON) );
		wndclass.hCursor		=	LoadCursor(NULL,IDC_ARROW);
		wndclass.hbrBackground	=	(HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpszMenuName	=	NULL;
		wndclass.lpszClassName	=	szAppName;
		RegisterClass(&wndclass);
	}

#ifdef _WINMODE_DEBUG
	if (renderDevice.GetWindowMode()) 
	{
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_OVERLAPPEDWINDOW| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
	else
	{
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_VISIBLE| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
#else

#ifdef	_LANGUAGE_TAIWAN
	hwnd=CreateWindow(szAppName,szAppName,
			  WS_VISIBLE| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
			  CW_USEDEFAULT,sx,sy,NULL,NULL,
			  hInst,NULL);
#endif

//중국 창모드 지원
#ifdef	_LANGUAGE_CHINESE	//윈도우 모드
	if ( WindowMode )
	{
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_OVERLAPPEDWINDOW| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
	else
	{
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_VISIBLE| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
#endif
#ifdef	_LANGUAGE_ENGLISH	//윈도우 모드
	if ( WindowMode ) {
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_OVERLAPPEDWINDOW| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
	else {
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_VISIBLE| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
#endif
#ifdef	_LANGUAGE_THAI
	hwnd=CreateWindow(szAppName,szAppName,
			  WS_VISIBLE| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
			  CW_USEDEFAULT,sx,sy,NULL,NULL,
			  hInst,NULL);
#endif

#ifdef _LANGUAGE_BRAZIL	
	hwnd=CreateWindow(szAppName,szAppName,
				  WS_VISIBLE| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);

#endif
#ifdef _LANGUAGE_ARGENTINA
	hwnd=CreateWindow(szAppName,szAppName,
				  WS_VISIBLE| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
#endif
#ifdef	_LANGUAGE_KOREAN
	if ( WindowMode ) {
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_OVERLAPPEDWINDOW| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
	else {
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_VISIBLE| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
#endif

#ifdef	_LANGUAGE_JAPANESE
	if ( WindowMode ) {
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_OVERLAPPEDWINDOW| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
	else {
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_VISIBLE| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
#endif
#ifdef _LANGUAGE_VEITNAM	//윈도우 모드
	if ( WindowMode ) {
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_OVERLAPPEDWINDOW| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
	else {
		hwnd=CreateWindow(szAppName,szAppName,
				  WS_VISIBLE| WS_POPUP|WS_EX_TOPMOST,CW_USEDEFAULT,
				  CW_USEDEFAULT,sx,sy,NULL,NULL,
				  hInst,NULL);
	}
#endif

#endif


	#ifdef _npGAME_GUARD
		while (1) 
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))  
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				break;
		}

		MoveWindow( hwnd , 0,0, WinSizeX , WinSizeY , FALSE );
	#endif

	//Bakjaewon - XignCode // chapters - debugging code to give out autograph ZSOPT_USESYSGUARD
	#ifdef _XIGNCODE_CLIENT
		if(!ZCWAVE_SysEnter(("_97cpcxcIB3A"),_T("Xigncode"), ZSOPT_USESYSGUARD )) // 장별 - 싸인코드3
			quit = 1;	
	#endif


	#ifdef _XTRAP_GUARD_4_CLIENT
		XTrap_C_KeepAlive();	//XTrapD5
	#endif

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	ShowCursor( FALSE );

	#ifdef _LANGUAGE_WINDOW
		Utils_Log(LOG_DEBUG, "_LANGUAGE_WINDOW");
		if (renderDevice.GetWindowMode())
		{
			HWND		hImsi1=GetDesktopWindow();
			RECT		rImsi1;
			GetWindowRect(hImsi1,&rImsi1);
		}
	#endif

	if (InitD3D(hwnd) == NULL)
	{
		Utils_Log(LOG_ERROR, "Failed InitD3D()");
		return FALSE;
	}

	InitLoadingLamp( hwnd );

	hTextWnd=CreateWindow( "EDIT", "", WS_CHILD|WS_BORDER|ES_LEFT|ES_MULTILINE|ES_WANTRETURN,
							10,400,500,40, hwnd , (HMENU)IDC_TEXT, hInst,NULL);

	OldEditProc01 = (WNDPROC)SetWindowLong(hTextWnd,GWL_WNDPROC,(LONG)EditWndProc01);
	IMETest.SetHWND(hTextWnd);

	hImc = ImmGetContext( hwnd );
	hImcEdit = ImmGetContext( hTextWnd );

	SetIME_Mode(0);		//IME conversion mode

	//Create font
	SetCreateFont();

	TextMode = 0;

	InitGameSocket();

	//Insider IP check
	char *szIP;
	int cnt;
	int ChkIp;

	if ( smConfig.DebugMode )
	{
		szIP = smGetMyIp();
		if ( szIP )
		{
			cnt = 0;
			ChkIp = 0;
			while(1) 
			{
				//IP checking for operators
				if ( !szOperationIP[cnt] ) 
					break;
				if ( strstr( szIP , szOperationIP[cnt] )!=0 )
				{
					ChkIp++;
					break;
				}
				cnt++;
			}
			if ( !ChkIp && smConfig.DebugMode==TRUE ) 
			{
				smConfig.DebugMode=0;
			}
		}
		if ( smConfig.DebugMode>1 ) 
			smConfig.DebugMode=TRUE;
	}
	else 
	{
		DeleteFile( "ddd.txt" );			//Clan debug file deletion
	}

	SetGameMode(1);
	CharacterName1[0] = 0;
	CharacterName2[0] = 0;

	//Timer interrupt operation (one minute 20 seconds in the actual game)
	SetTimer( hwnd, 0, GAME_WORLDTIME_MIN / 4, NULL );

	#ifdef _LANGUAGE_WINDOW
		if (renderDevice.GetWindowMode())
		{
			HWND		hImsi=GetDesktopWindow();
			RECT		rImsi;
			GetWindowRect(hImsi,&rImsi);
			SetWindowPos(hwnd,HWND_TOP,0,0,rImsi.right,rImsi.bottom-30,SWP_SHOWWINDOW);
		}
	#endif

	//Profanity filter
	#ifdef	_LANGUAGE_KOREAN
		if ( LoadCurses("Image\\Curse.cht")!=-81004 ) return FALSE;
	#endif
	#ifdef	_LANGUAGE_THAI
		if ( LoadCurses("Image\\thaicurse.cht")!=98085 ) return FALSE;
	#endif
	#ifdef	_LANGUAGE_TAIWAN
		if ( LoadCurses("Image\\taiwan_curse.cht")!=-19406 ) return FALSE;
		if ( LoadCursesID("Image\\taiwan_BadID.cht")!=-33585 ) return FALSE;
	#endif
	#ifdef	_LANGUAGE_BRAZIL
		if ( LoadCurses("Image\\brazil_curse.cht")!=240 ) return FALSE;
		if ( LoadCursesID("Image\\brazil_curse.cht")!=240 ) return FALSE;
	#endif
	#ifdef	_LANGUAGE_ARGENTINA
	//	if ( LoadCurses("Image\\argentina_curse.cht")!=240 ) return FALSE;
	//	if ( LoadCursesID("Image\\argentina_curse.cht")!=240 ) return FALSE;
	#endif
	#ifdef	_LANGUAGE_CHINESE
		if ( LoadCurses("Image\\chinacurse.cht")!=-92461 ) return FALSE;
		if ( LoadCursesID("Image\\chinacurse.cht")!=-92461 ) return FALSE;
	#endif
	#ifdef	_LANGUAGE_JAPANESE
		if ( LoadCurses("Image\\japancurse.cht")!=232284 ) return FALSE;
		if ( LoadCursesID("Image\\japancurse.cht")!=232284 ) return FALSE;
	#endif

	#ifdef _LANGUAGE_WINDOW
		SetForegroundWindow( hwnd );
	#endif

	//Main Loop
	while (1) 
	{
	    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	    {
	      TranslateMessage(&msg);

		  if ( msg.message==WM_SYSKEYDOWN || msg.message==WM_SYSKEYUP ) 
		  {
			  if ( msg.wParam!=0xF4 && msg.wParam!=VK_F10 )		//Except Kana key
				continue;	
		  }

	      DispatchMessage(&msg);
	    }
		else
		{
			EnterCriticalSection( &cSection_Main );	

			PlayD3D();

			//Process the message in the message queue
			PlayRecvMessageQue();

			LeaveCriticalSection( &cSection_Main );	
		}

		if (quit!=0 && !dwTradeMaskTime ) 
		{
			if ( GameMode!=2 ) 
				break;
	
			if ( smWsockServer && !QuitSave )
			{
				if ( cTrade.OpenFlag )
				{
					//If the termination of the trade deal
					SendRequestTrade( cTrade.TradeCharCode , 3 );	//Cancel transactions required
					cTrade.CancelTradeItem();						//Close trade window
				}

				if ( cWareHouse.OpenFlag ) 
				{
					//Close the warehouse
					cWareHouse.RestoreInvenItem(); //Inventory recovery
				}

				cInvenTory.ResetMouseItem();	//Repair items holding

				SaveGameData();				//Game Save and Exit
				QuitSave = TRUE;
			}
			else 
			{
				if ( !smWsockServer || GetSaveResult()==TRUE ) 
					break;
				if (  (dwPlayTime - rsRecorder.dwRecordTime)>15000 ) 
					break;
			}
		}
	}

	SetGameMode( 0 );

	//Removing Fonts
	DeleteObject( hFont );

	//Remove loading Lamp
	CloseLoadingLamp();

	CloseBindSock();

	CloseD3d();

	if ( fpNetLog ) 
		fclose( fpNetLog );

	//nProtect Removal
	Remove_nProtect();

	if ( szExitInfo_URL[0] )
		ShellExecute(NULL, NULL, szExitInfo_URL, NULL, NULL, NULL);

	return msg.wParam;
}

int msX=0,msY=0;
int msXo=0,msYo=0;
int xPs;
int yPs;

POINT	pCursorPos;
POINT	pRealCursorPos;

//Windows message process in the game
DWORD GameWindowMessage( HWND hWnd,UINT messg,WPARAM wParam,LPARAM lParam );
DWORD dwTimerCount =0;

//IME 모드 전환
BOOL DisplayIME=FALSE;

int SetIME_Mode( BOOL mode )
{
	if ( mode ) {
		DisplayIME=TRUE;
		ImmSetOpenStatus(hImc,TRUE);
#ifdef	_LANGUAGE_JAPANESE
/*

		DWORD	conv , sent;
		//일본판
		ImmGetConversionStatus( hImc , &conv , &sent );
		ImmSetConversionStatus( hImc , IME_CMODE_NATIVE|IME_CMODE_FULLSHAPE,sent );

		ImmGetConversionStatus( hImcEdit , &conv , &sent );
		ImmSetConversionStatus( hImcEdit , IME_CMODE_NATIVE|IME_CMODE_FULLSHAPE,sent );
*/
		//일본판
		ImmSetConversionStatus( hImc , IME_CMODE_NATIVE|IME_CMODE_FULLSHAPE,IME_SMODE_PHRASEPREDICT );
		ImmSetConversionStatus( hImcEdit , IME_CMODE_NATIVE|IME_CMODE_FULLSHAPE,IME_SMODE_PHRASEPREDICT );


#else
		//한국판
		ImmSetConversionStatus( hImc , IME_CMODE_NATIVE,IME_CMODE_NATIVE );
		ImmSetConversionStatus( hImcEdit , IME_CMODE_NATIVE,IME_CMODE_NATIVE );
#endif

	}
	else {
		ImmSetConversionStatus( hImc , IME_CMODE_ALPHANUMERIC,IME_CMODE_ALPHANUMERIC );
		ImmSetConversionStatus( hImcEdit , IME_CMODE_ALPHANUMERIC,IME_CMODE_ALPHANUMERIC );

		ImmSetOpenStatus(hImc,FALSE);
		DisplayIME=FALSE;
	}


	return TRUE;
}

//2-byte code verification
int CheckCode_2Byte( char *Str )
{
#ifdef _LANGUAGE_ENGLISH
	//English version - unconditionally 1

	return 1;
#endif

#ifdef _LANGUAGE_THAI
	if(CheckTHAI_ptr(Str,0)==1) 
		return 1;
    else if(CheckTHAI_ptr(Str,0)==2) 
		return 2;
	return 1;
#endif

#ifdef _LANGUAGE_JAPANESE
	//일본코드 확인
	if ( CheckJTS_ptr(Str,0)==2 )
		return 2;

#else
	//한국 중국 코드
	if ( Str[0]<0 )
		return 2;	
#endif

	return 1;
}

LRESULT CALLBACK EditWndProc01(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	wmId    = LOWORD(wParam); 
	wmEvent = HIWORD(wParam); 			

	switch (message) 
	{
		case WM_KEYDOWN:
			//SetWindowText( hWnd , "" );

#ifdef	_IME_ACTIVE
			IMETest.GetInfoPerTime();
#endif

/*
			for(int cnt=0;cnt<10;cnt++) {
				lstrcpy( szIME_Buff[cnt] , IMETest.m_szCandList[cnt].GetBuffer( IMETest.m_szCandList[cnt].GetLength() ) );
			}
*/
			break;
   }
   return CallWindowProc(OldEditProc01,hWnd,message,wParam,lParam);
}

//////////////////////// [Japanese IME handling procedures; ] ///////////////////////////////
#ifdef	_LANGUAGE_JAPANESE

char g_bufEdit[256];		
char g_bufFixed[256];

int WndProc_Japanese(HWND hWnd,UINT messg,WPARAM wParam,LPARAM lParam)
{
	HIMC	imc;
	static DWORD conv = IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE | IME_CMODE_ROMAN;
	static DWORD sent = IME_SMODE_PHRASEPREDICT;
	static BOOL setFont = FALSE;

	switch (messg)
	{

		case WM_IME_COMPOSITION:

			if ((imc = ImmGetContext(hWnd))) {
				if (lParam & GCS_RESULTSTR) {
					ZeroMemory(g_bufFixed, 256);
					ImmGetCompositionString(imc, GCS_RESULTSTR, g_bufFixed, 256);
				}
				else if (lParam & GCS_COMPSTR) {
					ZeroMemory(g_bufEdit, 256);
					ImmGetCompositionString(imc, GCS_COMPSTR, g_bufEdit, 256);
				}
				ImmReleaseContext(hWnd, imc);
			}
			break;

		case WM_IME_NOTIFY:
			switch (wParam) {
			case IMN_SETCONVERSIONMODE:
			case IMN_SETSENTENCEMODE:
				if ((imc = ImmGetContext(hWnd))) {
					ImmGetConversionStatus(imc, &conv, &sent);
					ImmReleaseContext(hWnd, imc);
				}
				break;

			case IMN_SETOPENSTATUS:
				if ((imc = ImmGetContext(hWnd))) {
					if (ImmGetOpenStatus(imc)) {
						ImmSetConversionStatus(imc, conv, sent);
					}
					else {
						ImmGetConversionStatus(imc, &conv, &sent);
					}
					ImmReleaseContext(hWnd, imc);
				}

				if (!setFont && (imc = ImmGetContext(hWnd))) {
					LOGFONT lf;
					ZeroMemory(&lf, sizeof(LOGFONT));
					lf.lfHeight = 12;//-MulDiv(10, GetDeviceCaps(hDC, LOGPIXELSY), 72);
					lf.lfItalic = FALSE;
					lf.lfUnderline = FALSE;
					lf.lfStrikeOut = FALSE;
					lf.lfCharSet = OEM_CHARSET;//SHIFTJIS_CHARSET;
					lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
					lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
					lf.lfQuality = DEFAULT_QUALITY;
					lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
					strcpy(lf.lfFaceName, _T("굃굍 굊긕긘긞긏"));
					ImmSetCompositionFont(imc, &lf);
					ImmReleaseContext(hWnd, imc);
					setFont = TRUE;
				}
				break;

			case IMN_OPENCANDIDATE:
			case IMN_CHANGECANDIDATE:
				if ((imc = ImmGetContext(hWnd))) {
					CANDIDATEFORM cf;
					ZeroMemory(&cf, sizeof(CANDIDATEFORM));
					cf.dwStyle = CFS_CANDIDATEPOS;
					cf.ptCurrentPos.x = 100000;//GetSystemMetrics(SM_CXSCREEN);
					cf.ptCurrentPos.y = 100000;//GetSystemMetrics(SM_CYSCREEN);
					ImmSetCandidateWindow(imc, &cf);
					ImmReleaseContext(hWnd, imc);
				}
				break;
			}
			break;
	}

	return TRUE;
}
#endif

extern void clan_Mouse(int msg,WPARAM wParam);

LONG APIENTRY WndProc(HWND hWnd,UINT messg, WPARAM wParam, LPARAM lParam)
{

//	PAINTSTRUCT ps;
//	HDC	hdc;
	short zDelta;
	char strBuff[256];
	char strBuff2[256];
	char *lpString;
	int	len,CrCode;
/*
#ifdef	_LANGUAGE_JAPANESE
	//if ( messg==WM_IME_COMPOSITION || messg==WM_IME_NOTIFY ) {
		WndProc_Japanese( hWnd, messg, wParam, lParam);		//일본어 처리 프로시저
	//}
#endif
*/

	switch (messg)
	{
		//박철호 : voice채팅용 ==================================================
		case WM_CALLMEMMAP:    //vrun.dat 메모리맵에 메세지
		void PacketParsing();	//process.cpp
		PacketParsing();
		break;

		case WM_CREATE:
			break;

		case WM_CLOSE:
			//게임 종료
			QuitGame();
			break;

		case WSA_ACCEPT:
			WSAMessage_Accept( wParam , lParam );
			break;   

		case WSA_READ:
			WSAMessage_Read( wParam , lParam );
			break;      

		case SWM_RECVSUCCESS:
//				SendMessage( hwnd , SWM_RECVSUCCESS , (WPARAM)SockInfo , 0 );
//			SockInfo = (smTHREADSOCK *)wParam;
			RecvPlayData( (smTHREADSOCK *)wParam );
			break;

		case SWM_MCONNECT:
			//메세지 쓰레드에서 대신 연결
			ConnectOtherPlayer( wParam );
			break;

		case SWM_MDISCONNECT:
			//메세지 쓰레드에서 대신 끈음
			((smWINSOCK *)wParam)->CloseSocket();
			break;

		//case WM_IME_KEYDOWN:
		case WM_KEYDOWN :

			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn > 0 )
			{
				if( KeyFullZoomMap(wParam) )
				{
					VRKeyBuff[ wParam ] = 1;
                    break;
				}
				else
				{
					SetFullZoomMap(0);
					pCursorPos.x = g_iFzmCursorPosX;
					pCursorPos.y = g_iFzmCursorPosY;

					if( wParam == VK_ESCAPE )
						break;
				}
			}
			//######################################################################################


		
			//////////////박철호
#ifdef PARKMENU
			/////////펑션키  Key Down
			//if ( GameMode==2 )
			if( wParam == 0x47 )
			{
				if(vrunRuning==TRUE)
				{
					if(bMic==FALSE)
					{
						if(micInit==0)
						{
							micInit = cmicvol.Init();
						}
						bMic = TRUE;
						void ParkSetMicOnOFF();
						ParkSetMicOnOFF();
					}
				}
			}
			//}
#endif
			//XTRAP HEAP MEMORY TEST
//			if(wParam == 0x6c || wParam == 0x4b)
//			{
//				sinChar->Life[0] -= 100;
//				ReformCharForm();
//			}
//			if(wParam == 0x70 || wParam == 0x50)
//			{
//				sinChar->Stamina[0] -= 100;
//				ReformCharForm();
//			}


			//ktj
			if(wParam == VK_RETURN )keydownEnt=1;

			if ( wParam==VK_CONTROL ) VRKeyBuff[ wParam ] = 1;

			if ( !hFocusWnd ) {
				//######################################################################################
				//작 성 자 : 오 영 석
				//if ( VRKeyBuff[VK_CONTROL] && !sinMessageBoxShowFlag && VRKeyBuff[wParam]==0 ) {
				if ( ! VRKeyBuff[VK_SHIFT] && VRKeyBuff[VK_CONTROL] && !sinMessageBoxShowFlag && VRKeyBuff[wParam]==0 ) {
				//######################################################################################
					if ( wParam==VK_F1 || wParam==VK_F2 || wParam==VK_F3 || wParam==VK_F4 || wParam==VK_F5 || 
						wParam==VK_F6 || wParam==VK_F7 || wParam==VK_F8 || wParam==VK_F9 || wParam==VK_F10 ) {

							SetChatingLine( "" );

						}
				}
			}

			if ( hFocusWnd ) { 
				lpString = 0;
				CrCode = 0;

				//######################################################################################
				//작 성 자 : 오 영 석
				//if ( VRKeyBuff[VK_CONTROL] && !sinMessageBoxShowFlag ) {
				if ( ! VRKeyBuff[VK_SHIFT] && VRKeyBuff[VK_CONTROL] && !sinMessageBoxShowFlag ) {
				//######################################################################################
					if ( wParam==VK_F1  && szShotCutMessage[1][0] ) lpString=szShotCutMessage[1];
					if ( wParam==VK_F2  && szShotCutMessage[2][0] ) lpString=szShotCutMessage[2];
					if ( wParam==VK_F3  && szShotCutMessage[3][0] ) lpString=szShotCutMessage[3];
					if ( wParam==VK_F4  && szShotCutMessage[4][0] ) lpString=szShotCutMessage[4];
					if ( wParam==VK_F5  && szShotCutMessage[5][0] ) lpString=szShotCutMessage[5];
					if ( wParam==VK_F6  && szShotCutMessage[6][0] ) lpString=szShotCutMessage[6];
					if ( wParam==VK_F7  && szShotCutMessage[7][0] ) lpString=szShotCutMessage[7];
					if ( wParam==VK_F8  && szShotCutMessage[8][0] ) lpString=szShotCutMessage[8];
					if ( wParam==VK_F9  && szShotCutMessage[9][0] ) lpString=szShotCutMessage[9];
					if ( wParam==VK_F10 && szShotCutMessage[0][0] ) lpString=szShotCutMessage[0];

					if ( lpString ) {
#ifdef	_LANGUAGE_VEITNAM
						GetWindowText( hFocusWnd , strBuff2 , 80 );
#else
						GetWindowText( hFocusWnd , strBuff2 , 90 );
#endif
						len = lstrlen(strBuff2)+lstrlen(lpString);
						if ( len<80 ) {
							lstrcat( strBuff2 , lpString );
							if ( strBuff2[len-1]==0x0D ) {
								len--;
								strBuff2[len] = 0;
								CrCode = TRUE;
							}
							SetWindowText( hFocusWnd , strBuff2 );
							SendMessage( hFocusWnd , EM_SETSEL , len , len );
						}
					}
				}
				if ( !sinMessageBoxShowFlag &&
					((wParam == VK_RETURN && VRKeyBuff[wParam]==0 && !VRKeyBuff[VK_CONTROL]) || CrCode==TRUE ) ) {

#ifdef	_LANGUAGE_VEITNAM
					GetWindowText( hFocusWnd , strBuff2 , 80 );
#else
					GetWindowText( hFocusWnd , strBuff2 , 90 );
#endif
					cHelpPet.PetOnOff(strBuff2);   //<==== 요거추가해주세요

					if ( strBuff2[0] ) {
						if ( strBuff2[0]=='/' || (smConfig.DebugMode && strBuff2[0]=='~') || strBuff2[0]=='`' || strBuff2[0]=='@' )
							wsprintf( strBuff , "%s" , strBuff2 );
						else {
							switch( DispChatMode ) {
							case 0:		//일반
							case 4:		//귓말
#ifdef	_LANGUAGE_VEITNAM
     						    wsprintf( strBuff , "%s: %s" , PlayerName , strBuff2 );
#else
								wsprintf( strBuff , "%s: %s" , PlayerName , strBuff2 );
#endif
								break;
							case 1:		//클랜
								wsprintf( strBuff , "/CLAN> %s", strBuff2 );
								break;
							case 2:		//동료
								wsprintf( strBuff , "@%s", strBuff2 );
								break;
							case 3:		//거래
								wsprintf( strBuff , "/TRADE> %s", strBuff2 );
								break;
							}
						}
/*
						//######################################################################################
						//작 성 자 : 오 영 석
						if( smConfig.DebugMode )
						{
							int   Alpha;
							char  szBuff[64] = {0,};
							char *pos = GetWord( szBuff, strBuff );

							if( smRender.m_FogIsRend )
							{
								if( stricmp( szBuff, "/포그모드") == 0 )
								{
									pos = GetWord( szBuff, pos );
									smRender.m_FogMode = atoi( szBuff );
								}
								else if( smRender.m_FogMode )
								{
									if( stricmp( szBuff, "/포그시작") == 0 )
									{
										pos = GetWord( szBuff, pos );
										smRender.m_fFogStNum = (float)atof( szBuff );
										lpD3DDevice->SetRenderState( D3DRENDERSTATE_FOGTABLESTART, *((DWORD*)(&smRender.m_fFogStNum)) );
									}
									else if( stricmp( szBuff, "/포그끝") == 0 )
									{
										pos = GetWord( szBuff, pos );
										smRender.m_fFogEndNum = (float)atof( szBuff );
										lpD3DDevice->SetRenderState( D3DRENDERSTATE_FOGTABLEEND, *((DWORD*)(&smRender.m_fFogEndNum)) );
									}
									else if( stricmp( szBuff, "/포그칼라") == 0 )
									{
										int r,g,b,a;
										pos = GetWord( szBuff, pos );
										r = atoi( szBuff );
										pos = GetWord( szBuff, pos );
										g = atoi( szBuff );
										pos = GetWord( szBuff, pos );
										b = atoi( szBuff );
										pos = GetWord( szBuff, pos );
										a = atoi( szBuff );

										smRender.m_dwFogColor = RGBA_MAKE(r,g,b,a);
										lpD3DDevice->SetRenderState( D3DRENDERSTATE_FOGCOLOR, smRender.m_dwFogColor );
									}
								}
							}

							if( IsCreateNewRenderTarget() )
							{
								if( stricmp( szBuff, "/정상모드") == 0 )
									SetFilterEffect( FILTER_EFFECT_NULL, 0 );
								else if( stricmp( szBuff, "/모션블러") == 0 )
								{
									pos = GetWord( szBuff, pos ); 
									Alpha = atoi(szBuff);
									if( Alpha < 80 || Alpha > 200 )		Alpha = 80;
								}
								else if( stricmp( szBuff, "/뽀샤시") == 0 )
								{
									pos = GetWord( szBuff, pos );
									Alpha = atoi(szBuff);
									if( Alpha < 160 || Alpha > 200 )	Alpha = 180;
									SetFilterEffect( FILTER_EFFECT_SET_BRIGHT_CONTRAST, Alpha );
								}
							}
						}
						//######################################################################################
*/

						if ( GameMode==2 ) {
							if ( !usehFocus )
								SendChatMessageToServer( strBuff );	//int chatlistSPEAKERflag();

							if ( chatlistSPEAKERflag() && lstrlen(strBuff)>LastWhisperLen ) {
								SetClanChatting();				//클랜 채팅 모드
								if ( szLastWhisperName[0] ) {

									szLastWhisperName[0] = 0; //귓말 초기화
								}
							}
							else
								if ( szLastWhisperName[0] && lstrlen(strBuff)>LastWhisperLen ) {
									//파티원 귓말 보내기
									WhisperPartyPlayer( szLastWhisperName );
								}
								else {
									SetWindowText( hFocusWnd , "" );
									szLastWhisperName[0] = 0;
									LastWhisperLen = 0;
									InterfaceParty.chat_WhisperPartyPlayer_close();
									chatlistSPEAKERflagChg( 0 );		//클랜 채팅 종료
								}
						}
						else {
							hFocusWnd = 0;
						}
					}
					else {
						hFocusWnd = 0;
						if ( GameMode==2 ) {
							szLastWhisperName[0] = 0;
							LastWhisperLen = 0;
							InterfaceParty.chat_WhisperPartyPlayer_close();
							chatlistSPEAKERflagChg( 0 );		//클랜 채팅 종료
						}
					}
				}

				if ( GameMode==2 ) {
					if ( wParam == VK_TAB && VRKeyBuff[wParam]==0 ) {
						IsClanChatting();
						break;
					}

					if ( wParam == VK_UP && VRKeyBuff[wParam]==0 && !LastWhisperLen ) {
						//채팅 저장 코맨드 복구 
						RecallSavedChatCommand( hFocusWnd , 1 );
						//VRKeyBuff[ wParam ] = 1;
						break;
					}
					if ( wParam == VK_DOWN && VRKeyBuff[wParam]==0 && !LastWhisperLen ) {
						RecallSavedChatCommand( hFocusWnd , 0 );
						//VRKeyBuff[ wParam ] = 1;
						break;
					}
					if ( wParam==VK_ESCAPE && VRKeyBuff[wParam]==0 ) {
						if ( SendMessage( hTextWnd , EM_GETLIMITTEXT , 78 , 0 )>=78 ) {
							hFocusWnd = 0;
							cInterFace.ChatFlag = 0;
							szLastWhisperName[0]= 0;
							LastWhisperLen = 0;
							InterfaceParty.chat_WhisperPartyPlayer_close();
							chatlistSPEAKERflagChg( 0 );		//클랜 채팅 종료
						}
//							SendMessage( hTextWnd , EM_SETLIMITTEXT , 78 , 0 );
					}

					//채팅창 스크롤
					if ( wParam == VK_NEXT && VRKeyBuff[wParam]==0 ) {
						ChatScrollPoint-=DispChatMsgHeight;//6;
					}
					if ( wParam == VK_PRIOR && VRKeyBuff[wParam]==0 ) {
						ChatScrollPoint+=DispChatMsgHeight;//6;
					}

					if ( !hFocusWnd ) {
						//ImmSimulateHotKey(hwnd,IME_CHOTKEY_IME_NONIME_TOGGLE);
						//ImmSimulateHotKey(hTextWnd,IME_CHOTKEY_IME_NONIME_TOGGLE);
						SetIME_Mode( 0 );		//IME 모드 전환
						ChatScrollPoint = 0;
						//ImmSetConversionStatus( hImc , IME_CMODE_ALPHANUMERIC,IME_CMODE_ALPHANUMERIC );
						//ImmSetConversionStatus( hImcEdit , IME_CMODE_ALPHANUMERIC,IME_CMODE_ALPHANUMERIC );
					}
				}
/*
				IMETest.SetHWND(hFocusWnd);
				IMETest.GetInfoPerTime();
				for(int cnt=0;cnt<10;cnt++) {
					lstrcpy( szIME_Buff[cnt] , IMETest.m_szCandList[cnt].GetBuffer( IMETest.m_szCandList[cnt].GetLength() ) );
				}
*/
				SendMessage( hFocusWnd, messg , wParam , lParam );
				break;
			}

			if ( wParam==VK_ESCAPE && VRKeyBuff[wParam]==0 ) {
				if ( VRKeyBuff[VK_SHIFT] )  
					QuitGame();
				else {
					if ( cInterFace.ChatFlag ) 
						cInterFace.ChatFlag = 0;
					else {
						if ( cInvenTory.OpenFlag || cCharStatus.OpenFlag || cSkill.OpenFlag || ExitButtonClick ) {
							cInterFace.CheckAllBox( SIN_ALL_CLOSE );
						}
						else {
							if ( InterfaceParty.PartyPosState==PARTY_PROCESS ) {
								InterfaceParty.PartyPosState=PARTY_END;
								InterfaceParty.qN_Pressf_CLEAR();
							}
							else {
								ExitButtonClick = 1;
							}
						}
					}
				}
			}


			if ( GameMode==2 ) {
				if ( GameWindowMessage( hWnd, messg, wParam , lParam )==FALSE ) break;
			}
/*
			else {
				if ( smConfig.DebugMode && wParam == VK_F8 && VRKeyBuff[ wParam ]==0 ) {
					SetGameMode( 2 );
				}
			}
*/
			if ( GameMode==2 && lpCurPlayer->OnStageField>=0 && StageField[lpCurPlayer->OnStageField] && 
				StageField[lpCurPlayer->OnStageField]->State==FIELD_STATE_ROOM )
			{
				//알까기 대국장에서는 화면 캡쳐 금지

			}
			else
			{
#ifdef _LANGUAGE_ENGLISH	//해외
				if(lpCurPlayer->OnStageField >= 0 && StageField[lpCurPlayer->OnStageField] &&
					StageField[lpCurPlayer->OnStageField]->State == FIELD_STATE_CASTLE)
				{
					//필리핀 공성필드에서 캡쳐금지
				}
				else
				{
					if ( wParam==VK_HOME && VRKeyBuff[wParam]==0 && VRKeyBuff[VK_CONTROL] )
					{
						Capture(hwnd,CAPTURE_JPG);
					}
					//화면 캡쳐2
					if ( wParam==VK_END && VRKeyBuff[wParam]==0 && VRKeyBuff[VK_CONTROL] )
					{
						Capture(hwnd,CAPTURE_BMP);
					}
				}
#else
				//화면 캡쳐
				if ( wParam==VK_HOME && VRKeyBuff[wParam]==0 && VRKeyBuff[VK_CONTROL] )
				{
					Capture(hwnd,CAPTURE_JPG);
				}
				//화면 캡쳐2
				if ( wParam==VK_END && VRKeyBuff[wParam]==0 && VRKeyBuff[VK_CONTROL] )
				{
					Capture(hwnd,CAPTURE_BMP);
				}
#endif
			}

			VRKeyBuff[ wParam ] = 1;
			clan_Mouse(WM_KEYDOWN,wParam);

			break;

		//case WM_IME_KEYUP:
		case WM_KEYUP :
			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn > 0 )
			{
				if( KeyFullZoomMap(wParam) )
				{
					VRKeyBuff[ wParam ] = 0;
                    break;
				}
			}
			//######################################################################################


#ifdef PARKMENU

			/////////펑션키	 Key UP
			//if ( GameMode==2 )
			//{
				if( wParam == 0x47 )
				{
					if(vrunRuning==TRUE)
					{
						if(bMic==TRUE)
						{
							bMic = FALSE;
							void ParkSetMicOnOFF();
							ParkSetMicOnOFF();
						}
					}
				}
			//}
#endif

			if ( hFocusWnd ) {
				SendMessage( hFocusWnd, messg , wParam , lParam );
			}
			VRKeyBuff[ wParam ] = 0;
			clan_Mouse(WM_KEYUP,wParam);
			break;

		case WM_SYSKEYDOWN:
			if ( wParam==VK_F10 ) {
				PostMessage( hWnd , WM_KEYDOWN , wParam , lParam );
				return FALSE;
			}
			if ( hFocusWnd ) 
				SendMessage( hFocusWnd, messg , wParam , lParam );
			break;

		case WM_SYSKEYUP:
			if ( wParam==VK_F10 ) {
				PostMessage( hWnd , WM_KEYUP , wParam , lParam );
				return FALSE;
			}
			if ( hFocusWnd ) 
				SendMessage( hFocusWnd, messg , wParam , lParam );
			break;

		case WM_MOUSEMOVE:
			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn )
			{
				g_iFzmCursorPosX = LOWORD(lParam);  // horizontal position of cursor 
				g_iFzmCursorPosY = HIWORD(lParam);  // vertical position of cursor 

				if( g_iFzmCursorPosX > 30  * g_fWinSizeRatio_X && g_iFzmCursorPosX < 350 * g_fWinSizeRatio_X &&
					g_iFzmCursorPosY > 338 * g_fWinSizeRatio_Y && g_iFzmCursorPosY < 578 * g_fWinSizeRatio_Y )
				{
					if( g_iFzmCursorFocusGame == 0 )
					{
						g_iFzmCursorFocusGame = 1;
						
						xPs = pCursorPos.x = msXo = int( ((float)g_iFzmCursorPosX - g_fZoomInAdd_x) * g_fZoomInDiv_x );
						yPs = pCursorPos.y = msYo = int( ((float)g_iFzmCursorPosY - g_fZoomInAdd_y) * g_fZoomInDiv_y );
					}
					
					xPs = int( ((float)g_iFzmCursorPosX - g_fZoomInAdd_x) * g_fZoomInDiv_x );
					yPs = int( ((float)g_iFzmCursorPosY - g_fZoomInAdd_y) * g_fZoomInDiv_y );

					AutoMouse_Distance += abs(pCursorPos.x-xPs);
					AutoMouse_Distance += abs(pCursorPos.y-yPs);

					pCursorPos.x  = xPs;
					pCursorPos.y  = yPs;

					msX = msXo - xPs;
					msY = msYo - yPs;

					msXo = xPs;
					msYo = yPs;

					if( (wParam & MK_MBUTTON) )
						SetMousePlay( 3 );
					else
					{
						if( wParam == MK_LBUTTON || TraceMode_DblClick ) 
							SetMousePlay( 2 );
						else if( wParam == MK_RBUTTON )
							SetMousePlay( 4 );
					}
					dwLastMouseMoveTime = dwPlayTime;
				}
				else
					g_iFzmCursorFocusGame = 0;
			}
			else
			{
				xPs = LOWORD(lParam);  // horizontal position of cursor 
				yPs = HIWORD(lParam);  // vertical position of cursor 

				AutoMouse_Distance += abs(pCursorPos.x-xPs);
				AutoMouse_Distance += abs(pCursorPos.y-yPs);

				//pCursorPos.x  = xPs;
				//pCursorPos.y  = yPs;
				g_iFzmCursorPosX = pCursorPos.x  = xPs;
				g_iFzmCursorPosY = pCursorPos.y  = yPs;
				msX = msXo - xPs;
				msY = msYo - yPs;

				msXo = xPs;
				msYo = yPs;

				if ( (wParam&MK_MBUTTON) )
					SetMousePlay( 3 );
				else {
					if ( wParam==MK_LBUTTON || TraceMode_DblClick ) 
						SetMousePlay( 2 );
					else
						if ( wParam==MK_RBUTTON )
							SetMousePlay( 4 );
				}

	/*
				if ( wParam==MK_LBUTTON ) {
					angY += MousemX/4;
					angX -= MousemY/4;
				}
	*/
			}
			//######################################################################################

			dwLastMouseMoveTime = dwPlayTime;
			break;

		case WM_LBUTTONDBLCLK:
			MouseDblClick = TRUE;

			if ( GameMode==2 )
			{
				//안내지도 띄우기
				if ( GetFieldMapCursor()==TRUE && cInterFace.sInterFlags.MapOnFlag ) {
					sinCheck_ShowHelpMap();
				}
				sinDoubleClick();

				dsMenuCursorPos( &pCursorPos , 2 );
				if ( StopCharMotion(pCursorPos.x,pCursorPos.y)!=TRUE ) {
					Moving_DblClick = TRUE;			//마우스 이동 첵크 더블 클릭
					MousePos_DblClick.x = xPs;
					MousePos_DblClick.y = yPs;
					MousePos_DblClick.z = 0;
				}
				dsMenuCursorPos( &pCursorPos , 0 );
			}
			break;

		case WM_LBUTTONDOWN:
			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame )
			{
				SetMousePlay( 1 );
				sinLButtonDown();
				MouseButton[0] = TRUE;

				clan_Mouse(WM_LBUTTONDOWN,wParam);
			}
			else
				g_FzmMouseButton[0] = TRUE;
			//######################################################################################

			if ( GameMode==2 && DisconnectFlag ) quit = TRUE;
			break;

		case WM_LBUTTONUP:
			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame || MouseButton[0] )
			{
				SetMousePlay( 0 );
				sinLButtonUp();
				
				MouseButton[0] = FALSE;
				MouseDblClick = FALSE;
				//ktj
				clan_Mouse(WM_LBUTTONUP,wParam);
			}
			else {
				MouseDblClick = FALSE;
				g_FzmMouseButton[0] = FALSE;
			}
			//######################################################################################

			break;

		case WM_RBUTTONDOWN:
			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame )
			{
				SetMousePlay( 11 );
				MouseButton[1] = TRUE;
				//ktj
				clan_Mouse(WM_RBUTTONDOWN,wParam);
			}
			else
				g_FzmMouseButton[1] = TRUE;
			//######################################################################################

			break;

		case WM_RBUTTONUP:
			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame )
			{
				SetMousePlay( 10 );
				sinRButtonUp();
				MouseButton[1] = FALSE;
				//ktj
				clan_Mouse(WM_RBUTTONUP,wParam);
			}
			else
				g_FzmMouseButton[1] = FALSE;
			//######################################################################################

			break;

		case WM_MBUTTONDOWN:
			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame )
			{
				MouseButton[2] = TRUE;
				//ktj
				clan_Mouse(WM_MBUTTONDOWN,wParam);
			}
			else
				g_FzmMouseButton[2] = TRUE;
			//######################################################################################
			break;

		case WM_MBUTTONUP:
			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame )
			{
				MouseButton[2] = FALSE;
				//ktj
				clan_Mouse(WM_MBUTTONUP,wParam);
			}
			else
				g_FzmMouseButton[2] = FALSE;
			//######################################################################################

			break;

		case WM_MOUSEWHEEL:
			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn <= 0 || g_iFzmCursorFocusGame )
			{
				zDelta = (short) HIWORD(wParam);    // wheel rotation

				if ( cSinHelp.sinGetScrollMove(-zDelta/16)==TRUE ) break;
				if ( TJBscrollWheel( zDelta )==TRUE ) break;

				if ( whAnx==ANX_NONE ) whAnx = anx+zDelta;
				else whAnx +=zDelta;
				AutoCameraFlag = FALSE;
			}
			//######################################################################################

			break;

		case WM_CHAR:
			if ( wParam==0x0D || wParam==0x0A || ( GameMode==2 && wParam==VK_TAB ) ) return TRUE;
			if ( !smConfig.DebugMode && wParam==22 && lpCurPlayer->szChatMessage[0] ) return TRUE;		//도배 금지 CONTROL-V 막음
	
		case WM_SYSCHAR:
		case WM_IME_CHAR:
		case WM_IME_COMPOSITION:

			//######################################################################################
			//작 성 자 : 오 영 석
			if( g_IsDxProjectZoomIn > 0 ) 
				break;
			//######################################################################################
			if ( hFocusWnd ) 
				SendMessage( hFocusWnd, messg , wParam , lParam );
			break;

		case WM_KILLFOCUS:
			SetFocus( hWnd );
			return TRUE;

		case WM_COMMAND:
			break;

		case WM_DESTROY:
			PostQuitMessage (0);
			break;


		case WM_ACTIVATE: 
			break;

		case WM_NCACTIVATE: 
#ifdef _WINMODE_DEBUG
			if ( !smConfig.DebugMode )
#endif
#ifndef _LANGUAGE_WINDOW
				SetForegroundWindow( hwnd );
#endif

			//여기에 해킹 툴 삽입
			if ( GameMode==2 && lpCurPlayer->dwObjectSerial ) {
				//오프라인 크랙 검색
				CheckCracker();
				//크랙을 다시 찾는다
				CheckCracker( NULL ); //(온라인 검색)
				//캐릭터 정보 인증 확인
				CheckCharForm();
			}

			break;

		case WM_TIMER:
			if ( (dwTimerCount&3)==0 ) {
				dwGameWorldTime ++;			//게임의 월드시간

				dwGameHour = dwGameWorldTime+dwGameTimeOffset;
				dwGameHour = dwGameHour/60;
				dwGameHour = dwGameHour-(((int)(dwGameHour/24))*24);			//게임내부에서의 시
				dwGameMin = dwGameWorldTime-(((int)(dwGameWorldTime/60))*60);		//게임내부에서의 분

				//dwGameHour = 1;		//밤 만들기
			}

			if ( smWsockServer && smWsockDataServer && smWsockUserServer ) {
				smCheckWaitMessage();
			}

			dwTimerCount++;
			break;

		case WM_NPROTECT_EXIT_TWO:
			//nProtect 종료 메세지
			DisconnectServerCode = 4;
			DisconnectFlag = GetCurrentTime();
			break;

		case WM_NPROTECT_SPEEDHACK:
		case WM_NPROTECT_SH_ERROR:
		case WM_NPROTECT_SOFTICE:
			DisconnectServerCode = 4;
			DisconnectFlag = GetCurrentTime();
			quit = 1;
			break;

		default: 
			return DefWindowProc(hWnd,messg,wParam,lParam);
			break;
	}
	return 0L;

}

int MoveAngle( int step , int angY )
{
	int x,z;

	x = ((pX<<16) + GetSin[angY&ANGLE_MASK] * step)>>16;
	z = ((pZ<<16) + GetCos[angY&ANGLE_MASK] * step)>>16;

	pX=x; 
	pZ=z;

	return TRUE;
}

#define CAMERA_MOVE_STEP		(8*fONE)

int TraceCameraMain()
{
	if ( TraceCameraPosi.x<TraceTargetPosi.x )
	{
		TraceCameraPosi.x+=CAMERA_MOVE_STEP;
		if ( TraceCameraPosi.x>TraceTargetPosi.x )
			TraceCameraPosi.x = TraceTargetPosi.x;
	}
	if ( TraceCameraPosi.x>TraceTargetPosi.x )
	{
		TraceCameraPosi.x-=CAMERA_MOVE_STEP;
		if ( TraceCameraPosi.x<TraceTargetPosi.x )
			TraceCameraPosi.x = TraceTargetPosi.x;
	}

	if ( TraceCameraPosi.y<TraceTargetPosi.y ) 
	{
		TraceCameraPosi.y+=CAMERA_MOVE_STEP;
		if ( TraceCameraPosi.y>TraceTargetPosi.y )
			TraceCameraPosi.y = TraceTargetPosi.y;
	}
	if ( TraceCameraPosi.y>TraceTargetPosi.y )
	{
		TraceCameraPosi.y-=CAMERA_MOVE_STEP/2;
		if ( TraceCameraPosi.y<TraceTargetPosi.y )
			TraceCameraPosi.y = TraceTargetPosi.y;
	}


	if ( TraceCameraPosi.z<TraceTargetPosi.z ) 
	{
		TraceCameraPosi.z+=CAMERA_MOVE_STEP;
		if ( TraceCameraPosi.z>TraceTargetPosi.z )
			TraceCameraPosi.z = TraceTargetPosi.z;
	}
	if ( TraceCameraPosi.z>TraceTargetPosi.z )
	{
		TraceCameraPosi.z-=CAMERA_MOVE_STEP;
		if ( TraceCameraPosi.z<TraceTargetPosi.z )
			TraceCameraPosi.z = TraceTargetPosi.z;
	}

	return TRUE;
}

int RendSightPos = 0;
int RendSightOffset = 0;

//////////////////// Render the view distance settings ////////////////////
int SetRendSight()
{
	if( smRender.m_GameFieldView ) 
	{
		ViewPointLen = 38 * SizeMAPCELL + RendSightPos ;
		ccDistZMin   = ViewPointLen - (20*SizeMAPCELL+RendSightPos/4);

		return TRUE;
	}

	return FALSE;
}

int RendSightSub( int flag )
{
	if ( lpCurPlayer->OnStageField>=0 && StageField[ lpCurPlayer->OnStageField ]->FieldSight ) 
		RendSightOffset = StageField[ lpCurPlayer->OnStageField ]->FieldSight * SizeMAPCELL;
	else 
	{
		RendSightOffset = smRender.m_GameFieldViewStep * SizeMAPCELL;
		if ( flag ) RendSightPos = RendSightOffset;
	}

	if ( RendSightPos<RendSightOffset ) 
		RendSightPos+=4;
	else 
		if ( RendSightPos>RendSightOffset ) RendSightPos-=4;

	return TRUE;
}
/////////////////////////////////////////////////////////////////////


#define	FPS_TIME		(1000/70)

DWORD FrameSkipTimer = 0;
int fps	= 70;
int FpsTime;

#define AC_MOVE_STEP	4
#define AC_MOVE_MIN		256

int dsCameraRotation = 0;			//Dungeon Siege camera rotation

void PlayMain()
{
	int mv;

	if ( ActionGameMode ) 
	{
		//Action Key operation
		ActionGameMain();
	}
	else if ( cSinHelp.sinGetHelpShowFlag()!=TRUE )
	{
		if ( CameraInvRot )
		{
			if ( VRKeyBuff[VK_RIGHT] ) { any+=16; AutoCameraFlag=FALSE; }
			if ( VRKeyBuff[VK_LEFT] ) { any-=16; AutoCameraFlag=FALSE; }
		}
		else
		{
			if ( VRKeyBuff[VK_RIGHT] ) { any-=16; AutoCameraFlag=FALSE; }
			if ( VRKeyBuff[VK_LEFT] ) { any+=16; AutoCameraFlag=FALSE; }
		}

		if ( VRKeyBuff[VK_CONTROL] )
		{
			if ( VRKeyBuff[VK_UP] ) { anx -= 16; AutoCameraFlag=FALSE; }
			if ( VRKeyBuff[VK_DOWN] ) { anx +=16; AutoCameraFlag=FALSE; }
		}
		else 
		{
			//######################################################################################
			if ( VRKeyBuff[VK_UP] )
			{
				dist -= 8;
				if( dist < 100 )
				{
					if( anx <= 40 )
					{
						if( dist < 40 )
							dist = 40;
					}
					else
						dist = 100;

					CaTarDist = 0;
				}
			}

			if ( VRKeyBuff[VK_DOWN] ) 
			{
				dist +=8;
				if( dist > 440 ) { dist=440; CaTarDist=0; }
			}
			//######################################################################################
		}

		if ( VRKeyBuff[VK_NEXT] ) { anx -= 16; AutoCameraFlag=FALSE; }
		if ( VRKeyBuff[VK_PRIOR] ) { anx +=16; AutoCameraFlag=FALSE; }
	}

	if ( cInterFace.sInterFlags.CameraAutoFlag!=2 ) 
	{
		//Dungeon Siege camera
		if ( pCursorPos.x>=8 && pCursorPos.x<=WinSizeX-8 )
			dsCameraRotation = 0;

		if ( pCursorPos.x<8 )
		{
			if ( !dsCameraRotation ) dsCameraRotation = -512;
			mv = dsCameraRotation/16;
			if ( mv<-16 ) mv=-16;
			any+=mv;
			dsCameraRotation++;
			if ( dsCameraRotation>=0 ) 
			{
				dsCameraRotation = 0;
				pCursorPos.x = 8;
			}
			AutoCameraFlag=FALSE;
		}

		if ( pCursorPos.x>WinSizeX-8 )
		{ 
			if ( !dsCameraRotation ) dsCameraRotation = 512;
			mv=dsCameraRotation/16;
			if ( mv>16 ) mv=16;
			any+=mv;
			dsCameraRotation--;
			if ( dsCameraRotation<=0 ) 
			{
				dsCameraRotation = 0;
				pCursorPos.x = WinSizeX-8;
			}
			AutoCameraFlag=FALSE;
		}
	}

	if ( CaTarDist ) 
	{
		if ( dist<CaTarDist )
		{
			dist+=12;
			if ( dist>=CaTarDist ) { dist=CaTarDist;CaTarDist = 0; }
		}
		else
		{
			if (dist > CaTarDist)
			{
				dist -= 12;
				if (dist <= CaTarDist) { dist = CaTarDist; CaTarDist = 0; }
			}
		}
	}

	if ( CaMovAngle ) 
	{
		mv = CaMovAngle>>4;
		if ( CaMovAngle>0 )
		{
			if ( mv>32 ) mv = 32;
			any += mv; CaMovAngle-=mv;
			if ( CaMovAngle<0 ) CaMovAngle = 0;
		}
		else 
		{
			if ( mv<-32 ) mv = -32;
			any += mv; CaMovAngle-=mv;
			if ( CaMovAngle>0 ) CaMovAngle = 0;
		}

		if ( mv==0 ) 
			CaMovAngle=0;

		if ( CaMovAngle==0 )
			AutoCameraFlag=TRUE;
		else
			AutoCameraFlag=FALSE;
	}

	if ( whAnx!=ANX_NONE )
	{
		//Change the angle of the wheels
		if ( anx<whAnx )
		{
			anx+=8;
			if ( anx>=whAnx )
			{
				whAnx = ANX_NONE;
				AutoCameraFlag = TRUE;
			}
		}
		else
		{
			anx-=8;
			if ( anx<=whAnx )
			{
				whAnx = ANX_NONE;
				AutoCameraFlag = TRUE;
			}
		}
	}

	if ( PlayFloor>0 )
	{
		if ( ViewAnx<500 )
			ViewAnx += 8;

		if ( ViewDist>250 )
			ViewDist -= 8;

		PlayFloor--;
	}
	else 
	{
		if ( ViewAnx<anx )
		{
			ViewAnx += 8;
			if ( ViewAnx>anx ) ViewAnx = anx;
		}
		if ( ViewAnx>anx ) 
		{
			ViewAnx -= 8;
			if ( ViewAnx<anx ) ViewAnx = anx;
		}

		if ( CaTarDist ) 
			mv=100;
		else 
			mv=8;

		if ( ViewDist<dist )
		{
			ViewDist += mv;
			if ( ViewDist>dist ) ViewDist = dist;
		}
		if ( ViewDist>dist )
		{
			ViewDist -= mv;
			if ( ViewDist<dist ) ViewDist = dist;
		}
	}


	if ( DebugPlayer )
	{
		if ( dpX==0 && dpZ==0 ) {
			dpX = lpCurPlayer->pX;
			dpY = lpCurPlayer->pY;
			dpZ = lpCurPlayer->pZ;
		}

		if ( VRKeyBuff[ VK_SPACE ] )
		{
			GetMoveLocation( 0 , 0, fONE*2, anx, any, 0 );
			dpX += GeoResult_X;
			dpY += GeoResult_Y;
			dpZ += GeoResult_Z;
		}

		if ( VRKeyBuff[ 'Z' ]  ) 
			anz -=8;

		if ( VRKeyBuff[ 'X' ]  ) 
			anz +=8;

		lpCurPlayer->pX = dpX;
		lpCurPlayer->pZ = dpZ;

		anx &=ANGCLIP;

		if ( anx>=ANGLE_90 && anx<ANGLE_270) 
		{
			if ( anx<ANGLE_180 )
				anx = ANGLE_90-32;
			else
				anx = ANGLE_270+32;
		}
		ViewAnx = anx;
		whAnx = ANX_NONE;

	}
	else 
	{
		if ( anx>=(ANGLE_90-48) )
		{
			anx = (ANGLE_90-48);
			whAnx = ANX_NONE;
		}
		if ( anx<40 )
		{
			anx = 40;
			whAnx = ANX_NONE;
		}
	}

	if( anx > 40 && dist < 100 ) { dist=100; CaTarDist=0; }
	if( dist > 440 )			 { dist=440; CaTarDist=0; }

	int ay;
	int astep;

	if ( PlayCameraMode!=cInterFace.sInterFlags.CameraAutoFlag ) 
	{
		if ( cInterFace.sInterFlags.CameraAutoFlag==2 ) 
			any=ANGLE_45;
		PlayCameraMode = cInterFace.sInterFlags.CameraAutoFlag;

		if( !dwM_BlurTime && IsCreateNewRenderTarget() ) 
		{
			dwM_BlurTime=dwPlayTime+600;
			SetFilterEffect( FILTER_EFFECT_SET_MOTION_BLUR, 80 );
		}
	}

	if ( PlayCameraMode==1 && AutoCameraFlag && any!=lpCurPlayer->Angle.y && lpCurPlayer->MoveFlag )
	{
		ay = (any-lpCurPlayer->Angle.y) & ANGCLIP;

		if ( ay>=ANGLE_180 )
			ay=ay-ANGLE_360;

		if ( abs(ay)<(ANGLE_90+180) ) 
		{
			if ( ay<0 ) 
			{
				astep = abs( ay )>>6;
				if ( astep<AC_MOVE_STEP ) 
					astep = AC_MOVE_STEP;

				if ( ay<-AC_MOVE_MIN )
				{
					ay += astep;
					if ( ay>0 )
						any = lpCurPlayer->Angle.y;
					else
						any = ( any+astep ) & ANGCLIP;
				}
			}
			else
			{
				astep = abs( ay )>>6;
				if ( astep<AC_MOVE_STEP ) astep = AC_MOVE_STEP;
	
				if ( ay>AC_MOVE_MIN )
				{
					ay -= astep;
					if ( ay<0 ) 
						any = lpCurPlayer->Angle.y;
					else
						any = ( any-astep ) & ANGCLIP;
				}
			}
		}
	}

	NetWorkPlay();
	PlayPat3D();

	MainEffect();							//The main effect

	if( g_IsDxProjectZoomIn )
		MainFullZoomMap();

	dwMemError = dwMemError^dwPlayTime;
	dwPlayTime = GetCurrentTime();			//Time Recording
	dwMemError = dwMemError^dwPlayTime;

	TraceCameraMain();

	RendSightSub(0);				//Rendering vision changes
}

POINT3D TargetPosi = { 0,0,0 };
POINT3D GeoResult = { 0,0,0 };

int timeg = 0;
int RenderCnt=0;
int DispRender;
int	DispMainLoop;

DWORD	dwLastPlayTime =0;
DWORD	dwLastOverSpeedCount = 0;
int		PlayTimerMax = 0;
int		MainLoopCount = 0;
DWORD	dwLastRenderTime = 0;


void PlayD3D()
{
	DWORD dwTime = GetCurrentTime();
	if ( dwLastPlayTime )
	{
		//Speed nuclear warning
		if ( dwTime<dwLastPlayTime && dwLastOverSpeedCount>1000 )
		{
			//Hacking attempt automatic user notification
			SendSetHackUser2( 1200 , dwLastPlayTime-dwTime );
			dwLastOverSpeedCount = 0;
		}
	}
	dwLastPlayTime = dwTime;

	if ( FrameSkipTimer==0 ) 
	{ 
		FrameSkipTimer = dwTime;
		FpsTime = 1000/fps;
	}

	if ( ((int)(dwTime-FrameSkipTimer))>5000 ) 
		FrameSkipTimer = dwTime;

	if ( FrameSkipTimer>dwTime ) 
	{
		Sleep( FrameSkipTimer-dwTime );
		dwTime = GetCurrentTime();
		dwLastPlayTime = dwTime;
	}

	pRealCursorPos.x = pCursorPos.x;
	pRealCursorPos.y = pCursorPos.y;

	while(1) 
	{
		if ( FrameSkipTimer>=dwTime )
			break;

		FrameSkipTimer += FPS_TIME;

		switch( GameMode ) 
		{
		case 1:
			if ( MainOpening()==TRUE ) 
				SetGameMode(2);
			break;
		case 2:
			PlayMain();
			//Character information authentication
			#ifdef _SINBARAM
			//######################################################################################
			if( g_IsDxProjectZoomIn <= 0 ) 
			{
				dsMenuCursorPos( &pCursorPos , 1 );				//Menu cursor Simulation
                sinMain();
				dsMenuCursorPos( &pCursorPos , 0 );				//Simulation menu cursor recovery

				MainInterfaceParty( pHoPartyMsgBox.x , pHoPartyMsgBox.y );		//Party invitation menu
			}
			else
				MainSub();
			//######################################################################################
			#endif
			if ( BellatraEffectInitFlag )		//Bellatra Effects
				MainBellatraFontEffect();
			break;
		}

		MainLoopCount++;
		dwLastOverSpeedCount++;
	}

	if ( ParkPlayMode ) 
	{
		if ( ParkPlayMode<0 ) 
		{
			if ((renderDevice.GetFlipCount() & 1) == 0)		//Surface face extra checks
				return;
		}
		else
		{
			if ( ParkPlayMode<=1000 )
			{
				if ( (dwLastRenderTime+ParkPlayMode)>dwTime )
					return;
			}
		}

	}
	else 
	{
		if ( GetForegroundWindow()!=hwnd )
			Sleep(200);
	}

	dwLastRenderTime = dwTime;

	int i = GetCurrentTime();
	if ( timeg<i )
	{
		timeg = i+1000;
		DispRender = RenderCnt;
		RenderCnt = 0;
		DispMainLoop = MainLoopCount;
		MainLoopCount = 0;
	}
	RenderCnt++;

	switch( GameMode )
	{
	case 1:
		DrawOpening();
		if (renderDevice.Flip() == FALSE) 
			quit = 1;	

		return;
	}

	//Fixed point camera
	if ( PlayCameraMode==2 ) 
	{
		dist = 400;
		anx = ANGLE_45-128;
		ViewAnx = anx;
		ViewDist = dist;
	}

	any &=ANGCLIP;
	anx &=ANGCLIP;


	//Hong Ho-dong add (camera effect) under a partial fix.
	if( WaveCameraFlag && WaveCameraMode )
	{
		WaveCameraTimeCount++;
			
		if((WaveCameraTimeCount>WaveCameraDelay))
		{
			WaveCameraTimeCount = 0;
			if(WaveCameraDelay > 1 && WaveCameraFactor < 40)
                		WaveCameraFactor = -int((float)WaveCameraFactor/10.f*9.f);
			else
				WaveCameraFactor = -int((float)WaveCameraFactor/10.f*8.f);
			ViewDist += WaveCameraFactor;
		}

  		if(abs(WaveCameraFactor) < 1)
		{
			WaveCameraFlag = FALSE;
			WaveCameraTimeCount = 0;
		}
	}
	else
	{
		WaveCameraFlag = FALSE;
	}

	GetMoveLocation( 0 , 0, -(ViewDist<<FLOATNS), ViewAnx&ANGCLIP, any, 0 );
	//GetMoveLocation( 0 , 0, -(dist<<FLOATNS), anx, any, 0 );
	if ( GeoResult_X==GeoResult.x && GeoResult_Y==GeoResult.y && GeoResult_Z==GeoResult.z )
	{
		pX += lpCurPlayer->pX - TargetPosi.x;
		pY += lpCurPlayer->pY - TargetPosi.y;
		pZ += lpCurPlayer->pZ - TargetPosi.z;
	}
	else
	{
		pX = lpCurPlayer->pX;
		pY = lpCurPlayer->pY;
		pZ = lpCurPlayer->pZ;

		pX +=GeoResult_X;
		pZ +=GeoResult_Z;
		pY +=GeoResult_Y;

		GeoResult.x = GeoResult_X;
		GeoResult.y = GeoResult_Y;
		GeoResult.z = GeoResult_Z;
	}

	TargetPosi.x = lpCurPlayer->pX;
	TargetPosi.y = lpCurPlayer->pY;
	TargetPosi.z = lpCurPlayer->pZ;


	if ( DebugPlayer ) 
	{
		lpCurPlayer->Angle.y = any;

		pX = dpX;
		pY = dpY;
		pZ = dpZ;

		//anx = lpCurPlayer->Angle.x;
		any = lpCurPlayer->Angle.y;
	}
	else
	{
		anz = 0;
	}

	if ( smConfig.DebugMode && VRKeyBuff[VK_SHIFT] ) 
	{
		if ( VRKeyBuff[VK_HOME] )
			DarkLevel=220;
		if ( VRKeyBuff[VK_END] )
			DarkLevel=0;
	}

	//Variable Speed Lock
	LockSpeedProtect( lpCurPlayer );

	//Critical sections declaration
	EnterCriticalSection( &cDrawSection );
	smEnterTextureCriticalSection();


	//Hacks turns rendering of skill points rating
	DWORD	dwSkilChkSum=0;
	DWORD	dwChkSum;
	DWORD	dwLevelQuestSum;
	int		cnt,k;

	for(cnt=0;cnt<SIN_MAX_USE_SKILL;cnt++)
	{
		k=(cnt+5)<<2;
		dwSkilChkSum += sinSkill.UseSkill[cnt].UseSkillCount*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Point*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Mastery*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].GageLength*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[0]*k;
		dwSkilChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[1]*k;
	}

	dwLevelQuestSum = sinQuest_levelLog&0x576321cc;

	//Screen rendering function
	smPlayD3D( pX, pY, pZ, (ViewAnx&ANGCLIP), (any&ANGCLIP), (anz&ANGCLIP) );

	dwChkSum = 0;
	for(cnt=0;cnt<SIN_MAX_USE_SKILL;cnt++)
	{
		k=(cnt+5)<<2;
		dwChkSum += sinSkill.UseSkill[cnt].UseSkillCount*k;
		dwChkSum += sinSkill.UseSkill[cnt].Point*k;
		dwChkSum += sinSkill.UseSkill[cnt].Mastery*k;
		dwChkSum += sinSkill.UseSkill[cnt].GageLength*k;
		dwChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[0]*k;
		dwChkSum += sinSkill.UseSkill[cnt].Skill_Info.UseStamina[1]*k;
	}

	if ( dwSkilChkSum!=dwChkSum ) 
	{
		//Skill changes dwaeteum, winning points found
		SendSetHackUser3( 8540 , dwSkilChkSum , dwChkSum );
	}

	if ( dwLevelQuestSum!=(sinQuest_levelLog&0x576321cc) )
	{
		//Quest chord changes, found questionable points
		SendSetHackUser3( 8820 , (dwLevelQuestSum&0x576321cc) , sinQuest_levelLog );
	}

	int mapY;
	int x,z,y;

	GetMoveLocation( 0 , 0, -(dist<<FLOATNS), anx, any, 0 );

	x = lpCurPlayer->pX+GeoResult_X;
	y = lpCurPlayer->pY+GeoResult_Y;
	z = lpCurPlayer->pZ+GeoResult_Z;

	PlayFloor=0;
	y=0;

	if ( !DebugPlayer ) 
	{
		if ( smGameStage[0] ) 
		{
			mapY = (smGameStage[0]->GetHeight2( x , z  ));
			if ( mapY>CLIP_OUT ) 
				y++;
		}

		if ( smGameStage[1] )
		{
			mapY = (smGameStage[1]->GetHeight2( x , z  ));
			if ( mapY>CLIP_OUT ) 
				y++;
		}

		if ( !y )
			PlayFloor = 64;
	}


	//Critical sections releases
	smLeaveTextureCriticalSection();
	LeaveCriticalSection( &cDrawSection );

	//UnLock Variable Speed
	UnlockSpeedProtect( lpCurPlayer );

}

extern int DispPolyCnt;			// 실재 출력된 폴리곤 카운터 (통계용)
extern int GetMouseMapPoint( int x, int y );

extern int xframe;

int GetPlayMouseAngle()
{
	int ax,az,ay;

	ax = xPs - (WinSizeX>>1);
	az = yPs - (WinSizeY>>1);
	ay = GetRadian2D( 0,0, ax, -az );

	return ay+any;
}

int GetActionGame_PlayMouseAngle()
{
	int ax,az,ay;

	ax = xPs - lpCurPlayer->RendPoint.x;
	az = yPs - lpCurPlayer->RendPoint.x;
	ay = GetRadian2D( 0,0, ax, -az );

	return ay;;
}

int SetMousePlay( int flag )
{
	int ax,az,ay;
	char szBuff[256];
	int	cnt;
	//POINT	pmCursor;

	if ( GameMode!=2 ) return TRUE;

	if ( !lpCurPlayer->MotionInfo || dwNextWarpDelay || lpCurPlayer->PlayStunCount ) return FALSE;

	if ( lpCurPlayer->MotionInfo->State == CHRMOTION_STATE_DEAD ) return FALSE;


	#ifdef _SINBARAM
	//######################################################################################
	//작 성 자 : 오 영 석
	if( g_IsDxProjectZoomIn <= 0 )
	{
		//pmCursor.x = xPs; 
		//pmCursor.y = yPs; 
		dsMenuCursorPos( &pCursorPos , 2 );
		if ( StopCharMotion(pCursorPos.x,pCursorPos.y)==TRUE ) {
			if ( lpCurPlayer->MotionInfo->State<0x100 && lpCurPlayer->MotionInfo->State!=CHRMOTION_STATE_STAND ) {
				lpCurPlayer->SetMotionFromCode( CHRMOTION_STATE_STAND );
				lpCurPlayer->MoveFlag = FALSE;
			}
			flag = 0;
			//return TRUE;
		}
		dsMenuCursorPos( &pCursorPos , 0 );
	}
	//######################################################################################
	#endif

	switch( flag ) {
	case 1:

#ifdef	_NEW_PARTRADE

		if ( EachTradeButton && chrEachMaster ) {
			cnt = GetPartyTradeButtonPos( xPs , yPs );
			if ( cnt>=0 ) {
				EachTradeButton = 0;
				switch( cnt ) {
				case 0:
					//교환 거래 거리 확인
					if ( GetTradeDistanceFromCode( chrEachMaster->dwObjectSerial )==TRUE ) {
						//아이템 교환 신청
						SendRequestTrade( chrEachMaster->dwObjectSerial , 0 );
						wsprintf( szBuff , mgRequestTrade , chrEachMaster->smCharInfo.szName );
					}
					else {
						wsprintf( szBuff , mgRequestTrade2 , chrEachMaster->smCharInfo.szName );
					}
					return TRUE;

				case 1:
					//동료 신청
					wsprintf( szBuff , "//party %s" , chrEachMaster->smCharInfo.szName );
					SendChatMessageToServer( szBuff );
					return TRUE;

				case 2:
					//친구 등록
					InterfaceParty.latest_Insert(chrEachMaster->smCharInfo.szName);	//귓속말한사람의 리스트 추가.
					InterfaceParty.friend_Insert(chrEachMaster->smCharInfo.szName);		//친구목록

					InterfaceParty.Main_menuSet(2);	//메인메뉴 퀘스트, 동료, 친구를 바꿈.
					InterfaceParty.chat_changeMENU(1);	//친구중 최근목록(0), 친구목록(1), 거부자목록을바꿈.
					if ( InterfaceParty.PartyPosState==PARTY_NONE )	ShowParty();
					return TRUE;

				case 3:
					//클랜 메세지 보내기
					//SendClanJoinService( 1 , chrEachMaster );
					g_IsCheckClanMember(chrEachMaster);
					return TRUE;

				}
			}
		}


#else
		if ( EachTradeButton==2 && chrEachMaster ) {
			EachTradeButton = 0;

			//교환 거래 거리 확인
			if ( GetTradeDistanceFromCode( chrEachMaster->dwObjectSerial )==TRUE ) {
				//아이템 교환 신청
				SendRequestTrade( chrEachMaster->dwObjectSerial , 0 );
				//wsprintf( szBuff , "%s님께 거래를 신청했습니다" , chrEachMaster->smCharInfo.szName );
				wsprintf( szBuff , mgRequestTrade , chrEachMaster->smCharInfo.szName );
			}
			else {
//				wsprintf( szBuff , "%s님은 거리가 멀어서 거래 신청을 할수 없습니다" , chrEachMaster->smCharInfo.szName );
				wsprintf( szBuff , mgRequestTrade2 , chrEachMaster->smCharInfo.szName );
			}

			AddChatBuff( szBuff );
			break;
		}
#endif
		//안내지도 띄우기
		if ( GetFieldMapCursor()==TRUE && cInterFace.sInterFlags.MapOnFlag ) {
			if ( lpCurPlayer->smCharInfo.Level<20 ) {
				sinCheck_ShowHelpMap();
			}
			break;
		}

		if ( !ActionGameMode ) {

			//마우스 버튼 누름
			if ( lpCharSelPlayer || lpSelItem ) {
				SelMouseButton = 1;				//왼쪽 버튼
				TraceAttackPlay();
				AutoCameraFlag = FALSE;
			}
			else {
				if ( MsTraceMode && !lpCharSelPlayer && !lpSelItem ) {
					if ( lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK && 
						lpCurPlayer->MotionInfo->State!=CHRMOTION_STATE_SKILL)
						lpCurPlayer->SetTargetPosi( 0,0 );
					CancelAttack();
				}
				AutoCameraFlag = TRUE;
			}
		}
		else {
			ActionMouseClick[0] = 1;
		}

		AutoMouse_WM_Count++;				//자동 마우스 감지용
		//TraceMode_DblClick = 0;

		if ( SkillMasterFlag ) {
			//스킬 배우기를 마친다 
			sinSkillMasterClose();
		}

		lpCurPlayer->MoveFlag = TRUE;
		DispEachMode = 0;

		if ( hFocusWnd ) {
			GetWindowText( hFocusWnd , szBuff , 240 );
			if ( szBuff[0]==0 ) {
				hFocusWnd = 0;
				szLastWhisperName[0]= 0;
				LastWhisperLen = 0;
				InterfaceParty.chat_WhisperPartyPlayer_close();
				chatlistSPEAKERflagChg( 0 );		//클랜 채팅 종료
				SetIME_Mode( 0 );		//IME 모드 전환
				ChatScrollPoint = 0;
				//ImmSetConversionStatus( hImc , IME_CMODE_ALPHANUMERIC,IME_CMODE_ALPHANUMERIC );
				//ImmSetConversionStatus( hImcEdit , IME_CMODE_ALPHANUMERIC,IME_CMODE_ALPHANUMERIC );
			}
		}
		break;

	case 0:
		//마우스 버튼 놓음
		//if ( !lpCharSelPlayer && !lpSelItem ) {
		if ( Moving_DblClick ) {
			TraceMode_DblClick = TRUE;
			Moving_DblClick = 0;
			lpCurPlayer->MoveFlag = TRUE;			
			ActionMouseClick[0] = 2;

		}
		else {
			if ( !lpCharMsTrace && !lpMsTraceItem ) {
				lpCurPlayer->SetAction( 0 );
			}
		}
		return TRUE;

	case 11:
		if ( hFocusWnd ) {
			GetWindowText( hFocusWnd , szBuff , 240 );
			if ( szBuff[0]==0 ) {
				hFocusWnd = 0;
				SetIME_Mode( 0 );		//IME 모드 전환
				ChatScrollPoint = 0;
				//ImmSetConversionStatus( hImc , IME_CMODE_ALPHANUMERIC,IME_CMODE_ALPHANUMERIC );
				//ImmSetConversionStatus( hImcEdit , IME_CMODE_ALPHANUMERIC,IME_CMODE_ALPHANUMERIC );
			}
		}
		//마우스 오르쪽 버튼 누름
		if ( sinSkill.pRightSkill && lpCurPlayer->MotionInfo->State != CHRMOTION_STATE_ATTACK && 
			lpCurPlayer->MotionInfo->State!=CHRMOTION_STATE_SKILL ) {

			if ( lpCurPlayer->MotionInfo->State!=CHRMOTION_STATE_EAT) {
				//스킬 사용
				if ( OpenPlaySkill( sinSkill.pRightSkill ) ) 
					break;
			}
		}

		if ( !ActionGameMode ) {
			if ( lpCharSelPlayer ) { //|| lpSelItem ) {
				SelMouseButton = 2;				//오른 버튼
				TraceAttackPlay();
				AutoCameraFlag = FALSE;
				lpCurPlayer->MoveFlag = TRUE;
				DispEachMode = 0;
			}
		}
		else {
			ActionMouseClick[1] = TRUE;
		}


		AutoMouse_WM_Count++;				//자동 마우스 감지용
		break;
	case 10:
		//마우스 오르쪽 버튼 놓음
		if ( !lpCharMsTrace && !lpMsTraceItem ) {
			lpCurPlayer->SetAction( 0 );
		}
		break;

	case 3:
		//가운데 버튼 누른 상태에서 이동
		//	msX = xPs-msXo;
		//msY = yPs-msXo;

		ay = msY*4;//>>1;
		ax = msX*8;

		if ( ay ) {
			if ( !CaTarDist ) CaTarDist=dist;
			CaTarDist -= ay;
			//######################################################################################
			//작 성 자 : 오 영 석
			if( CaTarDist < 100 )
			{
				if( anx <= 40 )
				{
					if( CaTarDist < 40 )
						CaTarDist = 40;
				}
				else
					CaTarDist = 100;
			}

			if( CaTarDist > 440 ) { CaTarDist = 440; }
			//######################################################################################
		}

		if ( ax ) {
			if ( CameraInvRot ) ax = -ax;

			az = ANGLE_45>>1;
			if ( ax<-az ) ax=-az;
			if ( ax>az ) ax=az;

			CaMovAngle += ax;
		}

		return TRUE;

	case 4:
		if ( DebugPlayer )
		{
				/*
				msXo = WinSizeX>>1;
				msYo = WinSizeY>>1;

				SetCursorPos( msXo, msYo );
				*/

				ay = msY*2;
				ax = msX*2;

				any += ax;
				anx += ay;

				any &=ANGCLIP;
				anx &=ANGCLIP;

		}
		return TRUE;
	}

	if ( lpCurPlayer->MotionInfo->State==CHRMOTION_STATE_ATTACK ||
		lpCurPlayer->MotionInfo->State==CHRMOTION_STATE_SKILL ||
		lpCurPlayer->MotionInfo->State==CHRMOTION_STATE_YAHOO 
		) return FALSE;


	if ( lpCurPlayer->MoveFlag ) {

		if ( MsTraceMode ) {
			lpCurPlayer->Angle.y = GetMouseSelAngle();
			//if ( ay>=0) lpCurPlayer->Angle.y = ay;
		}
		else {
			if ( ActionGameMode )
				lpCurPlayer->Angle.y = GetActionGame_PlayMouseAngle();
			else
				lpCurPlayer->Angle.y = GetPlayMouseAngle();
		}
	}

	return TRUE;
}

extern int TestTraceMatrix();

int InitD3D(HWND hWnd)
{
	Utils_Log(LOG_DEBUG, "InitD3D() - WinSizeX(%d)   WinSizeY(%d)   WinColBit(%d)", WinSizeX, WinSizeY, WinColBit);
	hwnd = hWnd;

	MidX = WinSizeX	/2;
	MidY = WinSizeY	/2;
	MidY -= 59;
	viewdistZ = WinSizeX;

    // Direct3D
	if (!renderDevice.CreateD3D())
        return FALSE;

    //Set the video mode
    if ( !renderDevice.SetDisplayMode( hWnd, WinSizeX, WinSizeY, WinColBit ) )
        return FALSE;

	TestTraceMatrix();

    //Rendering initialization
	renderDevice.InitRender();

	InitTexture();

	//Texture quality mode setting (0-3)
	smSetTextureLevel( smConfig.TextureQuality );

	if (TextureSwapMode == FALSE && renderDevice.GetDeviceDesc_IsHardware())
	{
		if (renderDevice.GetDeviceDesc_TextureFilterCaps() & D3DPTFILTERCAPS_LINEARMIPLINEAR)
		{
            MipMapModeCreate = NOSQUARE_MODE;
			if (renderDevice.GetDeviceDesc_TextureCaps() & D3DPTEXTURECAPS_SQUAREONLY)
                MipMapModeCreate = SQUARE_MODE;
		}
	}
	
	if (renderDevice.GetDeviceDesc_RasterCaps() & D3DPRASTERCAPS_FOGTABLE) // && (renderDevice.GetDeviceDesc_RasterCaps() & D3DPRASTERCAPS_WFOG) 
	{
        smRender.m_FogIsRend = TRUE;

		D3DMATRIX matProj;
		D3D_SetProjectionMatrix( matProj, (g_PI/4.4f), (float(WinSizeX) / float(WinSizeY)), 20.f, 4000.f );
		renderDevice.SetTransform(D3DTRANSFORMSTATE_PROJECTION, &matProj);

		renderDevice.SetRenderState(D3DRENDERSTATE_FOGTABLEMODE, D3DFOG_LINEAR);
	}

	DIRECTDRAWSURFACE LogoImage = LoadDibSurfaceOffscreen("Image\\Logo.bmp");

	LogoImage->SetColorKey(DDCKEY_COLORSPACE, 0);

	renderDevice.ClearViewport(D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET);

	DrawSprite(WinSizeX / 2 - 250, WinSizeY / 2 - 150, LogoImage, 0, 0, 500, 300);

	renderDevice.Flip();

	Sleep(600);

	LogoImage->Release();

	Check_CodeSafe((DWORD)GameInit );

	InitSoundEffect( hwnd );	//Sound Initialization
	InitPatterns();

	//Character structure initialization
	lpCurPlayer = InitRotPlayer();

	return Code_VRamBuffOpen();			//Buffer initialization code
}

void CloseD3d()
{
	//TermDX_Wav2();			   //말기화
	CloseRotPlayer();			//주인공 구조체 포인터 종료

	CloseSoundEffect();

	//CloseMaterial();
	CloseTexture();

//	delete pat3d;
	
//	if ( hOBJ3DTexture )
//		hOBJ3DTexture->Release();

//	CloseMap();
	renderDevice.ReleaseD3D();
}

//게임 초기화
int GameInit()
{
	//######################################################################################
	//작 성 자 : 오 영 석
	g_IsReadTextures = 1;
	//######################################################################################

	//서버에 권한 설정
	if ( smConfig.DebugMode ) 
		SendAdminMode( TRUE );

	npSetUserID( UserAccount );		//게임가드에 ID 통보

	dwPlayTime = GetCurrentTime();
	dwMemError = dwMemError^dwPlayTime;
	Check_nProtect();					//nProtect 확인

	// 메트리얼 초기화
	InitMaterial();
	smRender.SetMaterialGroup( smMaterialGroup );			//기본 메트리얼 그룹

	//ZeroMemory( &lpCurPlayer->smCharInfo , sizeof( smCHAR_INFO ) );
	ReformCharForm();

	InitEffect();			//호 이펙트 초기화

	InitMotionBlur();		//모션 부려 초기화
	InitBackGround();		//배경 초기화

	Check_CodeSafe( (DWORD)CloseD3d );	//코드 보호 실행

	InitStage();
	InitPat3D();

#ifdef _XTRAP_GUARD_4_CLIENT
	XTrap_C_SetUserInfo(UserAccount,szConnServerName,lpCurPlayer->smCharInfo.szName , "class name" ,1);	//XTrapD5
#endif

	//######################################################################################
	//작 성 자 : 오 영 석
	CreateItem2PassTexture();
	//######################################################################################

	CheckCharForm();

	//메모리 첵크 초기화
	//InitKeepMemFunc();

	//메모리 전체 첵크
	//CheckKeepMemFull();


#ifdef _SINBARAM
	lpDDSMenu = 0;
	sinInit();
#else
	lpDDSMenu =  LoadDibSurfaceOffscreen( smConfig.szFile_Menu );
#endif

	//######################################################################################
	//작 성 자 : 오 영 석
	g_fWinSizeRatio_X = float(WinSizeX) / 800.f;
	g_fWinSizeRatio_Y = float(WinSizeY) / 600.f;

	CreateBeforeFullZoomMap();
	CreateFontImage();
	//######################################################################################

	TraceCameraPosi.x = lpCurPlayer->pX;
	TraceCameraPosi.y = lpCurPlayer->pY;
	TraceCameraPosi.z = lpCurPlayer->pZ;

	TraceTargetPosi.x = lpCurPlayer->pX;
	TraceTargetPosi.y = lpCurPlayer->pY;
	TraceTargetPosi.z = lpCurPlayer->pZ;

	InitMessageBox();

	//렌더링 기본 값
	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;
	MidX = WinSizeX	/2;
	MidY = WinSizeY	/2;
	viewdistZ = WinSizeX;

	//######################################################################################
	//작 성 자 : 오 영 석
	g_IsReadTextures = 1;
	//######################################################################################

	ReadTextures();

	CheckOftenMeshTextureSwap();	//자주쓸 메시 텍스쳐 스왑첵크

	//음악 연주
	if ( smConfig.BGM_Mode ) {
		if ( StageField[0] )
			PlayBGM_Direct( StageField[0]->BackMusicCode  );
		else {
			OpenBGM("wav\\bgm\\Field - Desert - Pilgrim.bgm");
			PlayBGM();
		}
	}
	CharPlaySound( lpCurPlayer );
	StartEffect( lpCurPlayer->pX,lpCurPlayer->pY,lpCurPlayer->pZ, EFFECT_GAME_START1 );
	RestartPlayCount = 700;		//10초 동안 무적


	hFocusWnd = 0;
	szLastWhisperName[0]= 0;
	LastWhisperLen = 0;
	InterfaceParty.chat_WhisperPartyPlayer_close();
	chatlistSPEAKERflagChg( 0 );		//클랜 채팅 종료
	SendMessage( hTextWnd , EM_SETLIMITTEXT , 78 , 0 );			//채팅 80글자 제한

	MouseButton[0] = 0;
	MouseButton[1] = 0;
	MouseButton[2] = 0;

	//주인공 캐릭터 포인터 변경		//kyle xtrapHeap

#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func11_Protect( &sinChar, sizeof(sinChar) );	//보호영역 무결성 체크
#endif

#ifdef _XIGNCODE_CLIENT
	// 박재원 - XignCode
	Xigncode_Client_Start();
#endif

	smCHAR	*lpTempChar;
	lpTempChar =  SelectRotPlayer( lpCurPlayer );
	if ( lpTempChar ) {
		lpCurPlayer = lpTempChar;
		sinChar = &lpCurPlayer->smCharInfo;
	}
	lpTempChar =  SelectRotPlayer( lpCurPlayer );
	if ( lpTempChar ) {
		lpCurPlayer = lpTempChar;
		sinChar = &lpCurPlayer->smCharInfo;
	}

#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
	XTrap_CE1_Func12_Protect( &sinChar, sizeof(sinChar) );	//보호영역 보호
	XTrap_CE1_Func13_Free( &sinChar, sizeof(sinChar) );		//보호영역 해제
#endif

	SetIME_Mode( 0 );		//IME 모드 전환

	//스킬보호값 전부 초기화
	ReformSkillInfo();


	HoMsgBoxMode = 1;
	SetMessageFrameSelect( HoMsgBoxMode );		//호메세지창 프레임 모드

	//######################################################################################
	//작 성 자 : 오 영 석
	CreateWinIntThread();
	//######################################################################################

	return TRUE;
}

//게임 닫기
int GameClose()
{

	#ifdef _XIGNCODE_CLIENT
	//박재원 - XignCode
	ZCWAVE_Cleanup();
	ZCWAVE_SysExit();
	#endif

	if ( lpDDSMenu ) lpDDSMenu->Release();

	//메모리 첵크 종료
	//CloseKeepMem();

	ClosePat3D();
	CloseBackGround();
	CloseStage();

#ifdef _SINBARAM
	sinClose();
#endif
	CloseMaterial();

	//######################################################################################
	//작 성 자 : 오 영 석
	DestroyWinIntThread();
	//######################################################################################

	if ( BellatraEffectInitFlag )
		DestroyBellatraFontEffect();

	return TRUE;
}


int SetGameMode( int mode )
{
	int OldMode = GameMode;
	GameMode = mode;
	//Pointer to the character set sinbaram

	#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
		XTrap_CE1_Func11_Protect( &sinChar, sizeof(sinChar) );	//보호영역 무결성 체크
	#endif

	sinChar = &lpCurPlayer->smCharInfo;

	#ifdef _XTRAP_GUARD_4_CLIENT //HEAP MEMORY TEST
		XTrap_CE1_Func12_Protect( &sinChar, sizeof(sinChar) );	//보호영역 보호
		XTrap_CE1_Func13_Free( &sinChar, sizeof(sinChar) );		//보호영역 해제
	#endif

	//Clean up old mode
	switch( OldMode )
	{
	case 1:

		CloseOpening();
		CloseMaterial();
		break;

	case 2:
		GameClose();
		break;
	}

	//Set new Mode
	switch( GameMode )
	{
	case 1:
		SetDxProjection( (g_PI/4.4f), WinSizeX, WinSizeY, 20.f, 4000.f );

		smRender.CreateRenderBuff(CameraSight);

		//Material Initalize
		InitMaterial();
		smRender.SetMaterialGroup(smMaterialGroup);			//Initialize Material
		InitEffect();			//Effect Initailize

		InitOpening();

		//Ward render clipping mode
		smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_WIDE_MULT_PERSPECTIVE_HEIGHT;
		MidX = WinSizeX	/ 2;
		MidY = WinSizeY	/ 2;

		// Check running processes.
		if ( CheckCrackProcess(TRUE) ) 
			quit = 1;

		if (IsCreateNewRenderTarget())
			SetFilterEffect(FILTER_EFFECT_SET_BRIGHT_CONTRAST, 180);

		dwM_BlurTime = 0;

		break;

	case 2:
		if( IsCreateNewRenderTarget() )
			SetFilterEffect( FILTER_EFFECT_SET_BRIGHT_CONTRAST, 160 );


		if( smRender.m_GameFieldView )
		{
			smRender.m_GameFieldViewStep = 22;
			smRender.SetGameFieldViewStep();
		}

		GameInit();

		// Check running processes.
		if ( CheckCrackProcess() ) 
			quit = 1;
		break;
	}

	WaveCameraFlag = FALSE;

	return TRUE;
}

float xr=0;

int jcnt = 0;

float brt = 1;
float bs = 0;


int ox=0,oy=0,oz=0;

int GoText = 0;

char strBuff[240];
char strBuff2[256];

int RestoreFlag = 0;

char *szRestore = "Now load the estuary very hard to picture data. Jjogeum only wait!";

int RestoreAll()
{
	HDC hdc;

    // Back Surface Clear
    DDBLTFX bltFx;
    ZeroMemory( &bltFx, sizeof(DDBLTFX) );
    bltFx.dwSize        = sizeof(DDBLTFX);
    bltFx.dwFillColor   = 0;

	//renderDevice.lpDDSPrimary->Blt(NULL, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &bltFx);
	renderDevice.Blt(renderDevice.lpDDSPrimary, NULL, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &bltFx);

	VramTotal = 0;
	
	renderDevice.lpDDSPrimary->GetDC(&hdc);
	SetTextColor( hdc, RGB(255, 255, 255) );
	SetBkMode( hdc, TRANSPARENT );
	dsTextLineOut( hdc , 16,WinSizeY-32, szRestore , lstrlen( szRestore ) );
	renderDevice.lpDDSPrimary->ReleaseDC(hdc);

	RestoreTextures();
	if ( lpDDSMenu ) 
	{
		lpDDSMenu->Release();
		lpDDSMenu =  LoadDibSurfaceOffscreen( smConfig.szFile_Menu );
	}

	sinReload();

	return TRUE;

}

int NumPoly;
int Disp_tx,Disp_ty;
int Disp_rx,Disp_ry;

//Boxes for sorting chat window
smCHAR	*lpCharMsgSort[OTHER_PLAYER_MAX];
int ChatMsgSortCnt;

extern int Debug_RecvCount1;
extern int Debug_RecvCount2;
extern int Debug_SendCount;

//Texture options to their default values
int RestoreInterfaceTexture()
{
	int cnt;

	smRender.Color_R  = 0;
	smRender.Color_G  = 0;
	smRender.Color_B  = 0;
	smRender.Color_A  = 0;

	cnt = 0;

	renderDevice.SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_MODULATE);
	renderDevice.SetTextureStageState(cnt, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	renderDevice.SetTextureStageState(cnt, D3DTSS_COLORARG2, D3DTA_CURRENT);

	renderDevice.SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	renderDevice.SetTextureStageState(cnt, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	renderDevice.SetTextureStageState(cnt, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	renderDevice.SetTexture(cnt, 0);

	for( cnt=1; cnt < 8; cnt++ ) 
	{
		renderDevice.SetTextureStageState(cnt, D3DTSS_COLOROP, D3DTOP_DISABLE);
		renderDevice.SetTextureStageState(cnt, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		renderDevice.SetTexture(cnt, 0);
	}

	return TRUE;
}

void VirtualDrawGameState(void)
{
	smRender.ClearLight();

	int BackDarkLevel;

	BackDarkLevel = DarkLevel;
	DarkLevel = 0;

	///////////////////////////////////////////////////////////////////////
	//Texture options to their default values
	RestoreInterfaceTexture();
	///////////////////////////////////////////////////////////////////////

	if( DisconnectFlag )
	{
		//Connection to the server broken
		if ( DisconnectServerCode==0 )
			DrawMessage( MidX-64 ,  MidY, mgDiconnect ,36, BOX_ONE );
		
		if ( DisconnectServerCode==1 )
			DrawMessage( MidX-64 ,  MidY, mgDiconnect1 ,36, BOX_ONE );
		
		if ( DisconnectServerCode==2 )
			DrawMessage( MidX-64 ,  MidY, mgDiconnect2 ,36, BOX_ONE );
		
		if ( DisconnectServerCode==3 )
			DrawMessage( MidX-64 ,  MidY, mgDiconnect3 ,36, BOX_ONE );
		
		if ( DisconnectServerCode==4 )
			DrawMessage( MidX-64 ,  MidY, mgDiconnect4 ,36, BOX_ONE );
		

		#ifdef	_WINMODE_DEBUG
			if ( !smConfig.DebugMode && !quit && ((DWORD)DisconnectFlag+5000)<dwPlayTime ) 
				quit=TRUE;
		#else
			if ( !quit && ((DWORD)DisconnectFlag+5000)<dwPlayTime ) 
				quit=TRUE;
		#endif
	}
	else
	{
		if ( quit )
			DrawMessage( MidX-40 ,  MidY, mgCloseGame ,36, BOX_ONE );
		else 
		{
			if ( dwCloseBoxTime && dwCloseBoxTime>dwPlayTime ) 
			{
				DrawMessage( MidX-100 ,  MidY, mgCloseWindow ,36, BOX_ONE );
			}
			else
			{
				if ( dwBattleQuitTime )
				{
					if ( (dwBattleQuitTime+5000)>dwPlayTime )
						DrawMessage( MidX-40 ,  MidY, mgCloseBattle ,36, BOX_ONE );
					else
						dwBattleQuitTime = 0;
				}
			}
		}
	}

	if (renderDevice.IsDevice())
	{ 
		renderDevice.BeginScene();
		DrawCursor();
		renderDevice.EndScene();
	}

	DarkLevel = BackDarkLevel;
	if (renderDevice.Flip() == FALSE) 
	{
		DisconnectFlag = dwPlayTime;
		quit = 1;
	}
}

int DrawGameState()
{
	int i;
	HDC	hdc;
	int cnt,cnt2;
	int	y,DispBar,DispMaster;
	smCHAR	*lpChar;
	scITEM	*lpItem;
	RECT	ddRect;
	int BackDarkLevel;
	DWORD	dwColor;

	ddRect.left   = 0;
	ddRect.right  = 800;
	ddRect.top    = 0;
	ddRect.bottom = 150;

	if (lpDDSMenu)
	{
		i = renderDevice.BltFast(renderDevice.lpDDSBack, 0, WinSizeY - 150, lpDDSMenu, &ddRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		//i = renderDevice.lpDDSBack->BltFast(0, WinSizeY - 150, lpDDSMenu, &ddRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}

	smRender.ClearLight();

	BackDarkLevel =DarkLevel;
	DarkLevel = 0;

	//Texture options to their default values
	RestoreInterfaceTexture();

	if ( lpCharMsTrace && lpCharMsTrace->RendSucess )
	{
		Disp_tx = lpCharMsTrace->RendPoint.x - 32;
		Disp_ty = lpCharMsTrace->RendPoint.y - 12;
	}

	if ( lpCharSelPlayer && lpCharMsTrace!=lpCharSelPlayer )
	{
		if ( lpCharSelPlayer->RendSucess ) 
		{
			Disp_rx = lpCharSelPlayer->RendPoint.x - 32;
			Disp_ry = lpCharSelPlayer->RendPoint.y - 12;
		}
	}

	lpChar = 0;
	lpItem =0;

	if ( lpMsTraceItem ) 
		lpItem = lpMsTraceItem;
	else
		lpItem = lpSelItem;

	if ( VRKeyBuff[ 'A' ] ) 
	{
		for(cnt=0;cnt<DISP_ITEM_MAX;cnt++) 
		{
			if ( scItems[cnt].Flag && scItems[cnt].ItemCode!=0 && lpSelItem!=&scItems[cnt] ) 
			{
				if ( scItems[cnt].RendPoint.z>=32*fONE && scItems[cnt].RendPoint.z<64*12*fONE ) 
				{
					DrawCharacterMessage( scItems[cnt].RendPoint.x, scItems[cnt].RendPoint.y,
						scItems[cnt].szName , 0 , 0, 0 , RGB(110, 110, 110)  );
				}
			}
		}
	}

	if ( lpSelItem && !lpCharSelPlayer && !lpCharMsTrace ) 
	{
		//Item Name Display
		Disp_tx = MsSelPos.x;
		Disp_ty = MsSelPos.y;

		DrawCharacterMessage( Disp_tx, Disp_ty,
			lpSelItem->szName , 0 , 0, 0 , RGB(180, 180, 180)  );

	}


	int	SelFlag;

	ChatMsgSortCnt = 0;

	for( cnt=0;cnt<OTHER_PLAYER_MAX;cnt++) 
	{
		if ( chrOtherPlayer[cnt].Flag && chrOtherPlayer[cnt].RendSucess && chrOtherPlayer[cnt].smCharInfo.szName[0] ) 
		{
			SelFlag = 0;
			if ( chrOtherPlayer[cnt].RendPoint.z<12*64*fONE ) 
			{
				if ( chrOtherPlayer[cnt].szChatMessage[0] ) 
				{
					//Chat Window Inspection
					if ( chrOtherPlayer[cnt].dwChatMessageTimer<dwPlayTime ) 
						chrOtherPlayer[cnt].szChatMessage[0] = 0;
					else 
					{
						if ( chrOtherPlayer[cnt].smCharInfo.State ) 
						{
							lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
							SelFlag++;
						}
					}
				}

				if ( chrOtherPlayer[cnt].dwTradeMsgCode && !SelFlag )	//Individual shops open
				{
					lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
					SelFlag++;
				}
			}

			if ( !SelFlag )
			{
				if ( lpCharMsTrace==&chrOtherPlayer[cnt] || lpCharSelPlayer==&chrOtherPlayer[cnt] || 
					( chrOtherPlayer[cnt].smCharInfo.State==smCHAR_STATE_NPC && chrOtherPlayer[cnt].RendPoint.z<12*64*fONE ) || 
					( chrOtherPlayer[cnt].smCharInfo.Life[0]>0 && chrOtherPlayer[cnt].smCharInfo.State==smCHAR_STATE_ENEMY && chrOtherPlayer[cnt].smCharInfo.Brood==smCHAR_MONSTER_USER ) ||
					( chrOtherPlayer[cnt].smCharInfo.ClassClan && chrOtherPlayer[cnt].smCharInfo.ClassClan==lpCurPlayer->smCharInfo.ClassClan )  ||
					( HoMsgBoxMode && chrOtherPlayer[cnt].dwClanManageBit ) ||
					chrOtherPlayer[cnt].PartyFlag )
				{
					lpCharMsgSort[ChatMsgSortCnt++] = &chrOtherPlayer[cnt];
				}
			}
		}
	}

	if ( lpCurPlayer->szChatMessage[0] ) 
	{
		if ( lpCurPlayer->dwChatMessageTimer<dwPlayTime ) 
			lpCurPlayer->szChatMessage[0] = 0;
		else 
			lpCharMsgSort[ChatMsgSortCnt++] = lpCurPlayer ;
	}
	else
	{
		if ( lpCurPlayer->dwTradeMsgCode )
			lpCharMsgSort[ChatMsgSortCnt++] = lpCurPlayer ;
	}


	//Sorting the message box
	if ( ChatMsgSortCnt )
	{
		for( cnt=0;cnt<ChatMsgSortCnt;cnt++)
		{
			for( cnt2=cnt+1;cnt2<ChatMsgSortCnt;cnt2++) 
			{
				if ( lpCharMsgSort[cnt]->RendPoint.z<lpCharMsgSort[cnt2]->RendPoint.z || lpCharMsgSort[cnt]==lpCharMsTrace || lpCharMsgSort[cnt]==lpCharSelPlayer ) 
				{
					lpChar = lpCharMsgSort[cnt];
					lpCharMsgSort[cnt] = lpCharMsgSort[cnt2];
					lpCharMsgSort[cnt2] = lpChar;
				}
			}
		}
	}

	DIRECTDRAWSURFACE lpDDS_clanMark;
	char *szClanName;
	char *szBoxMsg;
	BOOL  selectedBox;

	y = 8+(ViewAnx>>6);

	//순차 정렬된 채팅 박스 그리기
	for( cnt=0;cnt<ChatMsgSortCnt;cnt++) 
	{
		dwColor = RGB(255, 255, 200);

		DispBar = FALSE;
		DispMaster = FALSE;
		selectedBox = FALSE;

		if ( lpCharMsgSort[cnt]->PartyFlag ) 
		{
			dwColor = RGB(220, 255, 160);
			DispBar = TRUE;
		}
		else if ( lpCharMsgSort[cnt]->smCharInfo.State==smCHAR_STATE_ENEMY ) 
		{
			if (  lpCharMsgSort[cnt]->smCharInfo.Brood==smCHAR_MONSTER_USER ) 
			{
				dwColor = RGB(220, 255, 160);

				if ( lpCharMsgSort[cnt]->smCharInfo.Next_Exp==lpCurPlayer->dwObjectSerial || lpCharMsgSort[cnt]->smCharInfo.ClassClan )
					DispBar = TRUE;
				else
					DispMaster = TRUE;
			}
			else
				dwColor = RGB(255, 210, 210);
		}
		else if ( lpCharMsgSort[cnt]->smCharInfo.State==smCHAR_STATE_NPC ) 
		{
			dwColor = RGB(180, 180, 255);
		}

		if ( lpCharMsgSort[cnt]==lpCharMsTrace )
		{
			if ( lpCharMsgSort[cnt]->smCharInfo.State==smCHAR_STATE_ENEMY && lpCharMsgSort[cnt]->smCharInfo.Brood!=smCHAR_MONSTER_USER )
				dwColor = RGB(255, 230, 200);
			else
				dwColor = RGB(255, 255, 255);

			selectedBox = TRUE;
		}
		else
		{
			if ( lpCharMsgSort[cnt]==lpCharSelPlayer && lpCharMsgSort[cnt]->szChatMessage[0] ) selectedBox = TRUE;
		}

		lpDDS_clanMark = 0;
		szClanName = 0;
		DWORD	dwClanMgrBit;

		if ( lpCharMsgSort[cnt]->smCharInfo.ClassClan ) 
		{
			if ( lpCharMsgSort[cnt]==lpCurPlayer  )
			{
				lpDDS_clanMark =  cldata.hClanMark16;
				szClanName	   =  cldata.name;
			}
			else if ( lpCharMsgSort[cnt]->ClanInfoNum>=0 )
			{
				lpDDS_clanMark = ClanInfo[lpCharMsgSort[cnt]->ClanInfoNum].hClanMark;
				szClanName = ClanInfo[lpCharMsgSort[cnt]->ClanInfoNum].ClanInfoHeader.ClanName;
			}
		}


		if ( ( ( lpCharMsgSort[cnt]->szChatMessage[0] || lpCharMsgSort[cnt]->dwTradeMsgCode ) && lpCharMsgSort[cnt]->smCharInfo.State && lpCharMsgSort[cnt]->RendPoint.z<12*64*fONE ) || 
			lpCharMsgSort[cnt]==lpCurPlayer ) 
		{
			if ( szClanName && lpCharMsgSort[cnt]!=lpCharMsTrace && lpCharMsgSort[cnt]!=lpCharSelPlayer )
			{
				if ( !lpCurPlayer->smCharInfo.ClassClan || lpCharMsgSort[cnt]->smCharInfo.ClassClan!=lpCurPlayer->smCharInfo.ClassClan )
					szClanName = 0;
			}

			if ( lpCharMsgSort[cnt]->szChatMessage[0] )
			{
				DrawCharacterMessage( lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top+y,
					lpCharMsgSort[cnt]->szChatMessage ,30 , lpDDS_clanMark, szClanName ,dwColor , selectedBox );
			}
			else
			{
				if ( lpCharMsgSort[cnt]->szTradeMessage[0] ) 
				{
					DrawCharacterShopByeMessage( lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top+y,
						lpCharMsgSort[cnt]->szTradeMessage ,30 , lpDDS_clanMark, dwColor , selectedBox );
				}
			}
		}
		else 
		{
			if ( DispMaster && !lpCharMsgSort[cnt]->smCharInfo.ClassClan )
			{

				wsprintf( strBuff , "(%s)" , lpCharMsgSort[cnt]->smCharInfo.szModelName2+1 );
				DrawTwoLineMessage( lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top+y,
					lpCharMsgSort[cnt]->smCharInfo.szName , strBuff , dwColor , RGB(255, 255, 200) ,0 , selectedBox );

			}
			else 
			{
				if ( HoMsgBoxMode )
					dwClanMgrBit = lpCharMsgSort[cnt]->dwClanManageBit;
				else
					dwClanMgrBit = 0;

				if ( szClanName )
				{
					if ( smConfig.DebugMode && VRKeyBuff[VK_CONTROL] )
						wsprintf( strBuff , "%d/%d" , lpCharMsgSort[cnt]->smCharInfo.ClassClan , lpCharMsgSort[cnt]->ClanInfoNum );
					else
						wsprintf( strBuff , "[%s]" , szClanName );

					DrawTwoLineMessage( lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top+y,
						strBuff , lpCharMsgSort[cnt]->smCharInfo.szName , RGB(150, 255, 200) ,dwColor ,lpDDS_clanMark , selectedBox , dwClanMgrBit );
				}
				else
				{
					szBoxMsg = lpCharMsgSort[cnt]->smCharInfo.szName;
					DrawCharacterMessage( lpCharMsgSort[cnt]->RendPoint.x, lpCharMsgSort[cnt]->RendRect2D.top+y,
						szBoxMsg ,30 , lpDDS_clanMark, szClanName ,dwColor , selectedBox , dwClanMgrBit );
				}
			}
		}

		if ( DispBar )
		{
			renderDevice.EndScene();
			lpCharMsgSort[cnt]->DrawStateBar2( lpCharMsgSort[cnt]->RendPoint.x-30, lpCharMsgSort[cnt]->RendRect2D.top+y-14 );
			renderDevice.BeginScene();
		}
	}

	//Skill charging gauge
	if ( lpCurPlayer->AttackSkil ) 
	{
		DWORD checkFrame = 0;
		switch( lpCurPlayer->AttackSkil&0xFF )
		{
			case SKILL_PLAY_CHARGING_STRIKE:
				checkFrame = lpCurPlayer->frame - (lpCurPlayer->MotionInfo->StartFrame * 160);
				if ( lpCurPlayer->MotionInfo->EventFrame[0]<checkFrame && lpCurPlayer->MotionInfo->EventFrame[1]>checkFrame)
				{
					checkFrame -= (int)lpCurPlayer->MotionInfo->EventFrame[0];
					cnt2 = (int)(lpCurPlayer->MotionInfo->EventFrame[1]-lpCurPlayer->MotionInfo->EventFrame[0]);

					renderDevice.EndScene();
					lpCurPlayer->DrawChargingBar( lpCurPlayer->RendPoint.x-30,lpCurPlayer->RendRect2D.bottom, checkFrame,cnt2 );
					renderDevice.BeginScene();
				}
				break;
			case SKILL_PLAY_PHOENIX_SHOT:
				checkFrame = lpCurPlayer->frame - (lpCurPlayer->MotionInfo->StartFrame * 160);
				if ( lpCurPlayer->MotionInfo->EventFrame[0]<checkFrame && lpCurPlayer->MotionInfo->EventFrame[1]>checkFrame)
				{
					checkFrame -= (int)lpCurPlayer->MotionInfo->EventFrame[0];
					cnt2 = (int)(lpCurPlayer->MotionInfo->EventFrame[1]-lpCurPlayer->MotionInfo->EventFrame[0]);

					renderDevice.EndScene();
					lpCurPlayer->DrawChargingBar( lpCurPlayer->RendPoint.x-30,lpCurPlayer->RendRect2D.bottom, checkFrame,cnt2 );
					renderDevice.BeginScene();
				}
				break;
		}
	}

	if ( DispInterface )
	{
		if ( DispEachMode )
			DrawEachPlayer( 0.74f , 0.32f , 1 );				//Enlarge the character drawing
		
		else 
		{
			DrawEachPlayer( 0.92f , 0.1f , 0 );					//Enlarge the character drawing

			dsDrawOffset_X = WinSizeX-800;
			dsDrawOffset_Y = WinSizeY-600;
			dsDrawOffsetArray = dsARRAY_RIGHT|dsARRAY_BOTTOM;
			dsMenuCursorPos( &pCursorPos , 3 );				//Menu cursor Simulation
			
			DrawInterfaceParty();							//Drawing party menu
			dsMenuCursorPos( &pCursorPos , 0 );				//Menu cursor Simulation
			dsDrawOffsetArray = dsARRAY_TOP;
			dsDrawOffset_X = 0;
			dsDrawOffset_Y = 0;

			DrawInterfaceParty( pHoPartyMsgBox.x , pHoPartyMsgBox.y );		//Party invitation menu
		}

		if( smConfig.DebugMode )
		{
			extern int Debug_TalkZoomMode;
			if( Debug_TalkZoomMode && lpCurPlayer->TalkPattern )
			{
				extern void DrawTalkZoom( smCHAR *lpChar, smPAT3D *lpPattern, float fx, float fy );
				DrawTalkZoom( lpCurPlayer, lpCurPlayer->TalkPattern, 0.2f, 0.32f );
			}
		}
	}

	//////////////////////////////
	#ifdef	_NEW_PARTRADE
		if ( EachTradeButton && chrEachMaster ) 
		{
			//Click Butte trade party application
			DisplayPartyTradeButton();
		}
	#endif


	//Sod score display function
	DisplaySodScore();

	#ifdef _SINBARAM
		//Texture options to their default values
		RestoreInterfaceTexture();

		dsDrawOffset_X = WinSizeX-800;
		dsDrawOffset_Y = WinSizeY-600;

		if ( DispInterface ) sinDraw();

		dsDrawOffset_X = 0;
		dsDrawOffset_Y = 0;
	#endif

	if ( BellatraEffectInitFlag )		//Bellatra Effect
		DrawBellatraFontEffect();

	renderDevice.lpDDSBack->GetDC(&hdc);

	SelectObject( hdc , hFont );

	#ifdef	_IME_ACTIVE
		////////////////////////// IME 표시 //////////////////////////
		char *ImeStr;
		//int Num,ImeY;
		int ImeY;
		//if ( hFocusWnd ) {
		if ( DisplayIME ) {

			SetBkColor( hdc , RGB( 255,255,200 ) );
			SetTextColor( hdc, RGB(0, 0, 0) );

			if (sinChatDisplayMode==1) 
				ImeY = 442;
			else 
				ImeY = 340;

			//ImeStr = IMETest.m_szCOMPOSTR.GetBuffer( IMETest.m_szCOMPOSTR.GetLength() );
			//if ( ImeStr[0] ) 
			//	dsTextLineOut( hdc , 8,ImeY-12, ImeStr , lstrlen( ImeStr ) );
			IMETest.GetImeInfo();
			ImeStr = IMETest.m_szTitle.GetBuffer( IMETest.m_szTitle.GetLength() );
			if ( ImeStr[0] )
				//dsTextLineOut( hdc , 100,ImeY-12, ImeStr , lstrlen( ImeStr ) );
				dsTextLineOut( hdc , 8,ImeY-12, ImeStr , lstrlen( ImeStr ) );

			//wsprintf( strBuff , "%s %s", 
			//	IMETest.m_szConvMode.GetBuffer( IMETest.m_szConvMode.GetLength() ) ,
			//	IMETest.m_szHalfMode.GetBuffer( IMETest.m_szHalfMode.GetLength() ) );

			//dsTextLineOut( hdc , 300,ImeY-12, strBuff , lstrlen( strBuff ) );

			SetBkColor( hdc , RGB( 255,255,255 ) );
			/*
			for( cnt=0;cnt<IMETest.nCandListCount;cnt++ ) {
	
				ImeStr = IMETest.m_szCandList[cnt].GetBuffer( IMETest.m_szCandList[cnt].GetLength() );

				if ( cnt>=9 ) Num=0;
				else Num = cnt+1;

				wsprintf( strBuff , " %d: %s ", Num , ImeStr );

				dsTextLineOut( hdc , 344,ImeY+cnt*12, strBuff , lstrlen( strBuff ) );
			}
			*/
		}

	#endif

    SetBkMode( hdc, TRANSPARENT );

#ifdef _WINMODE_DEBUG

	int	rcv1,rcv2,snd1,snd2,arcv1,brcv1,arcv2,brcv2;
	int LineY;

	if (DisplayDebug)
	{
		rcv1=0;
		rcv2=0;
		snd1=0;
		snd2=0;
		arcv1=0;
		brcv1=0;
		arcv2=0;
		brcv2=0;

		if ( smWsockServer )
		{
			rcv1= smWsockServer->RecvPacketCount;
			snd1= smWsockServer->SendPacketCount;
			arcv1 = smWsockServer->RecvPopCount;
			brcv1 = smWsockServer->RecvPopErrorCount;
		}
		else { rcv1=0;snd1=0; }

		if ( smWsockUserServer )
		{
			rcv2= smWsockUserServer->RecvPacketCount;
			snd2= smWsockUserServer->SendPacketCount;
			arcv2 = smWsockUserServer->RecvPopCount;
			brcv2 = smWsockUserServer->RecvPopErrorCount;
		}
		else 
		{ 
			rcv2=0;snd2=0; 
		}

		wsprintf( strBuff , "%d(%d) %d x=%d z=%d y=%d VRAM=%d R1=%d(%d) R2=%d(%d) S1=%d S2=%d (%d/%d) (%d/%d) RcvTurb( %d )", DispRender ,DispMainLoop , DispPolyCnt , lpCurPlayer->pX>>(FLOATNS) , lpCurPlayer->pZ>>(FLOATNS) , lpCurPlayer->pY>>(FLOATNS), (VramTotal/(1024*1024)) , 
			rcv1,Debug_RecvCount1,rcv2,Debug_RecvCount2,snd1,snd2 , brcv1,arcv1, brcv2,arcv2 , smTransTurbRcvMode );	//ReconnServer ,ReconnDataServer );

		SetTextColor( hdc, RGB(0, 0, 0) );
		dsTextLineOut( hdc , 11,11, strBuff , lstrlen( strBuff ) );
		SetTextColor( hdc, RGB(255, 255, 255) );
		dsTextLineOut( hdc , 10,10, strBuff , lstrlen( strBuff ) );

		wsprintf( strBuff , "Stage : %s , %s", szGameStageName[0] ,szGameStageName[1] );
		SetTextColor( hdc, RGB(0, 0, 0) );
		dsTextLineOut( hdc , 11,31, strBuff , lstrlen( strBuff ) );
		SetTextColor( hdc, RGB(255, 255, 255) );
		dsTextLineOut( hdc , 10,30, strBuff , lstrlen( strBuff ) );

		wsprintf( strBuff , "World Time (%d:%d)", dwGameHour ,dwGameMin );
		SetTextColor( hdc, RGB(0, 0, 0) );
		dsTextLineOut( hdc , (WinSizeX>>1)+1,31, strBuff , lstrlen( strBuff ) );
		SetTextColor( hdc, RGB(255, 255, 255) );
		dsTextLineOut( hdc , (WinSizeX>>1),30, strBuff , lstrlen( strBuff ) );


		if ( lpCurPlayer->PatLoading==FALSE ) 
		{
			if ( AdminCharMode ) 
				wsprintf( strBuff , "%s" , lpCurPlayer->smCharInfo.szName );
			else
				wsprintf( strBuff , "%s" , lpCurPlayer->lpDinaPattern->szPatName );

			SetTextColor( hdc, RGB(0, 0, 0) );
			dsTextLineOut( hdc , (WinSizeX>>1)+1+120 , 31 , strBuff , lstrlen( strBuff ) );
			SetTextColor( hdc, RGB(255, 255, 255) );
			dsTextLineOut( hdc , (WinSizeX>>1)+120 , 30 , strBuff , lstrlen( strBuff ) );

			wsprintf( strBuff , "Damage : %d" , LastAttackDamage );
			SetTextColor( hdc, RGB(0, 0, 0) );
			dsTextLineOut( hdc , 9 , 48 , strBuff , lstrlen( strBuff ) );
			SetTextColor( hdc, RGB(255, 255, 255) );
			dsTextLineOut( hdc , 8 , 47 , strBuff , lstrlen( strBuff ) );

			wsprintf( strBuff , "RcvDamage:(%d) [%d] %d %d", Record_TotalRecvDamageCount , Record_RecvDamageCount,Record_DefenceCount,Record_BlockCount );
			SetTextColor( hdc, RGB(0, 0, 0) );
			dsTextLineOut( hdc , 9 , 62 , strBuff , lstrlen( strBuff ) );
			SetTextColor( hdc, RGB(255, 255, 255) );
			dsTextLineOut( hdc , 8 , 61 , strBuff , lstrlen( strBuff ) );

			if ( AreaServerMode )
			{
				if ( lpWSockServer_Area[0] )
				{
					wsprintf( strBuff , "Area Server[0]: (%s)",lpWSockServer_Area[0]->szIPAddr );
					SetTextColor( hdc, RGB(0, 0, 0) );
					dsTextLineOut( hdc , 9 , 82 , strBuff , lstrlen( strBuff ) );
					SetTextColor( hdc, RGB(255, 255, 255) );
					dsTextLineOut( hdc , 8 , 81 , strBuff , lstrlen( strBuff ) );
				}
				if ( lpWSockServer_Area[1] )
				{
					wsprintf( strBuff , "Area Server[1]: (%s)",lpWSockServer_Area[1]->szIPAddr );
					SetTextColor( hdc, RGB(0, 0, 0) );
					dsTextLineOut( hdc , 9 , 96 , strBuff , lstrlen( strBuff ) );
					SetTextColor( hdc, RGB(255, 255, 255) );
					dsTextLineOut( hdc , 8 , 95 , strBuff , lstrlen( strBuff ) );
				}

				if ( lpWSockServer_DispArea[0] )
				{
					wsprintf( strBuff , "Area Server[0]: (%s)",lpWSockServer_DispArea[0]->szIPAddr );
					SetTextColor( hdc, RGB(0, 0, 0) );
					dsTextLineOut( hdc , 209 , 82 , strBuff , lstrlen( strBuff ) );
					SetTextColor( hdc, RGB(255, 255, 255) );
					dsTextLineOut( hdc , 208 , 81 , strBuff , lstrlen( strBuff ) );
				}

				if ( lpWSockServer_DispArea[1] )
				{
					wsprintf( strBuff , "Area Server[1]: (%s)",lpWSockServer_DispArea[1]->szIPAddr );
					SetTextColor( hdc, RGB(0, 0, 0) );
					dsTextLineOut( hdc , 209 , 96 , strBuff , lstrlen( strBuff ) );
					SetTextColor( hdc, RGB(255, 255, 255) );
					dsTextLineOut( hdc , 208 , 95 , strBuff , lstrlen( strBuff ) );
				}

				wsprintf( strBuff , "AreaCount(%d) AreaConn(%d) AreaIP( [%d] %d %d ) Step(%d)" , 
					dwDebugAreaCount , dwDebugAreaConnCount ,
					dwDebugAreaIP[0],dwDebugAreaIP[1],dwDebugAreaIP[2] , dwDebugAreaStep );

				SetTextColor( hdc, RGB(0, 0, 0) );
				dsTextLineOut( hdc , 9 , 108 , strBuff , lstrlen( strBuff ) );
				SetTextColor( hdc, RGB(255, 255, 255) );
				dsTextLineOut( hdc , 8 , 108 , strBuff , lstrlen( strBuff ) );
			}
		}

		SetTextColor( hdc, RGB(255, 255, 255) );

		LineY=48;
		for( i=0;i<OTHER_PLAYER_MAX;i++) 
		{
			if ( chrOtherPlayer[i].Flag && chrOtherPlayer[i].Pattern && chrOtherPlayer[i].smCharInfo.State==smCHAR_STATE_USER )
			{
				wsprintf( strBuff , "%s", chrOtherPlayer[i].smCharInfo.szName );
				SetTextColor( hdc, RGB(0, 0, 0) );
				dsTextLineOut( hdc , WinSizeX-220,LineY+1, strBuff , lstrlen( strBuff ) );
				SetTextColor( hdc, RGB(255, 255, 255) );
				dsTextLineOut( hdc , WinSizeX-221,LineY, strBuff , lstrlen( strBuff ) );
				LineY += 16;
				if ( LineY>460 ) 
					break;
			}
		}

		int	MonCharBuff[OTHER_PLAYER_MAX];
		int MonCharCnt = 0;
		int	MonCnt;

		for( i=0;i<OTHER_PLAYER_MAX;i++) 
		{
			if ( chrOtherPlayer[i].Flag && chrOtherPlayer[i].Pattern && chrOtherPlayer[i].smCharInfo.State!=smCHAR_STATE_USER )
				MonCharBuff[MonCharCnt++] = i;
		}

		LineY=48;
		for( i=0;i<MonCharCnt;i++) 
		{
			if ( MonCharBuff[i]>=0 ) 
			{
				MonCnt = 1;
				for( cnt=i+1;cnt<MonCharCnt;cnt++ ) 
				{
					if ( MonCharBuff[cnt]>=0 && lstrcmp( chrOtherPlayer[MonCharBuff[cnt]].smCharInfo.szName , 
						chrOtherPlayer[MonCharBuff[i]].smCharInfo.szName )==0 )
					{
						MonCharBuff[cnt] = -1;
						MonCnt++;
					}
				}

				wsprintf( strBuff , "%s x %d", chrOtherPlayer[MonCharBuff[i]].smCharInfo.szName , MonCnt );
				SetTextColor( hdc, RGB(0, 0, 0) );
				dsTextLineOut( hdc , WinSizeX-380,LineY+1, strBuff , lstrlen( strBuff ) );

				if ( chrOtherPlayer[MonCharBuff[i]].smCharInfo.State==smCHAR_STATE_NPC )
					SetTextColor( hdc, RGB(192, 192, 255) );
				else
					SetTextColor( hdc, RGB(255, 192, 192) );
				dsTextLineOut( hdc , WinSizeX-381,LineY, strBuff , lstrlen( strBuff ) );
				LineY += 16;
				if ( LineY>460 ) break;
			}
		}
	}
#endif

	renderDevice.lpDDSBack->ReleaseDC(hdc);

	if ( DisconnectFlag )
	{
		//서버와의 연결 끊어짐
		if ( DisconnectServerCode==0 )
			DrawMessage( MidX-64 ,  MidY, mgDiconnect ,36, BOX_ONE );

		if ( DisconnectServerCode==1 )
			DrawMessage( MidX-64 ,  MidY, mgDiconnect1 ,36, BOX_ONE );

		if ( DisconnectServerCode==2 )
			DrawMessage( MidX-64 ,  MidY, mgDiconnect2 ,36, BOX_ONE );

		if ( DisconnectServerCode==3 )
			DrawMessage( MidX-64 ,  MidY, mgDiconnect3 ,36, BOX_ONE );

		if ( DisconnectServerCode==4 )
			DrawMessage( MidX-64 ,  MidY, mgDiconnect4 ,36, BOX_ONE );


		#ifdef	_WINMODE_DEBUG
			if ( !smConfig.DebugMode && !quit && ((DWORD)DisconnectFlag+5000)<dwPlayTime ) 
				quit=TRUE;
		#else
			if ( !quit && ((DWORD)DisconnectFlag+5000)<dwPlayTime ) 
				quit=TRUE;
		#endif
	}
	else 
	{
		if ( quit )
			DrawMessage( MidX-40 ,  MidY, mgCloseGame ,36, BOX_ONE );
		else 
		{
			if ( dwCloseBoxTime && dwCloseBoxTime>dwPlayTime ) 
			{
				DrawMessage( MidX-100 ,  MidY, mgCloseWindow ,36, BOX_ONE );
			}
			else 
			{
				if ( dwBattleQuitTime )
				{
					if ( (dwBattleQuitTime+5000)>dwPlayTime )
						DrawMessage( MidX-40 ,  MidY, mgCloseBattle ,36, BOX_ONE );
					else
						dwBattleQuitTime = 0;
				}
			}
		}
	}

	DarkLevel = BackDarkLevel;

	if (renderDevice.Flip() == FALSE)
	{
		DisconnectFlag = dwPlayTime;
		quit = 1;
	}

	return TRUE;
}

void smPlayD3D( int x, int y, int z, int ax, int ay, int az )
{
	eCAMERA_TRACE	eTrace;
	int	ap;

	DispPolyCnt = 0;

	if (renderDevice.lpDDSBack->IsLost() == DDERR_SURFACELOST || renderDevice.lpDDSPrimary->IsLost() == DDERR_SURFACELOST)
	{
		//Lost connection termination surfaces
		DisconnectFlag = dwPlayTime;
		quit = TRUE;

		renderDevice.lpDDSPrimary->Restore();
		renderDevice.lpDDSBack->Restore();
		RestoreFlag = TRUE;
		return;
	}
	else
	{
		if ( RestoreFlag )
		{
			RestoreAll();
			RestoreFlag = FALSE;
		}
	}

	SetRendSight();		//Rendering vision set

	if( g_IsDxProjectZoomIn <= 0 )
        DrawGameState();
	else
		VirtualDrawGameState();

	if ( (dwDebugBack^dwDebugXor)==0 )
	{
		if ( smConfig.DebugMode ) 
		{
			//Hacking attempt automatic user notification
			SendSetHackUser( TRUE );
			smConfig.DebugMode = 0;
		}
	}

	int Mapfl;
	int cy;
	int mapY;

	Mapfl = 0;
	cy = y+16*fONE;

	if ( !DebugPlayer )
	{
		if ( smGameStage[0] )
		{
			mapY = (smGameStage[0]->GetHeight( x , z ));
			if ( y<mapY )
			{
				y = mapY;
				y +=8<<FLOATNS;
			}
			if ( mapY>CLIP_OUT ) Mapfl++;
		}
		if ( smGameStage[1] )
		{
			mapY = (smGameStage[1]->GetHeight( x , z ));
			if ( y<mapY )
			{
				y = mapY;
				y +=8<<FLOATNS;
			}
			if ( mapY>CLIP_OUT ) 
				Mapfl++;
		}
	}

	Mix_CodeVram();		//Code buffer mixer

	smRender.Color_R = BrCtrl;
	smRender.Color_G = BrCtrl;
	smRender.Color_B = BrCtrl;
	smRender.Color_A = BrCtrl;

	smRender.Color_R = -DarkLevel+BackColor_R;
	smRender.Color_G = -DarkLevel+BackColor_G;
	smRender.Color_B = -DarkLevel+BackColor_B;


	if( dwM_BlurTime && IsCreateNewRenderTarget() ) 
	{
		if ( dwM_BlurTime<dwPlayTime ) 
		{
			dwM_BlurTime = 0;
			SetFilterEffect( FILTER_EFFECT_SET_BRIGHT_CONTRAST, 160 );
			SetFilterEffect( FILTER_EFFECT_DEL_MOTION_BLUR, 0 );
		}
	}

	if( GetFilterEffect() )
	{
		renderDevice.ClearViewport(D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET);
        ChangeRenderTarget( NEW_TARGET_BACK );
	}

	renderDevice.ClearViewport(D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET);

	y += (32<<FLOATNS);

	if( anx <= 40 && dist <= 100 )
		y -= ((110-dist) << FLOATNS);

	TraceTargetPosi.x = x;
	TraceTargetPosi.y = y;
	TraceTargetPosi.z = z;

	if ( AutoCameraFlag )
	{

		TraceCameraMain();

		x = TraceCameraPosi.x;
		y = TraceCameraPosi.y;
		z = TraceCameraPosi.z;
	}


	int ey = lpCurPlayer->pY + (32*fONE);
	if( anx <= 40 && dist <= 100 ) 
		ey += ((100-dist) * fONE);

	ActionGameMode = FALSE;


	if ( lpCurPlayer && lpCurPlayer->OnStageField>=0 && StageField[ lpCurPlayer->OnStageField ]->State==FIELD_STATE_ACTION ) 
	{
		//Side-scrolling action mode
		x = lpCurPlayer->pX;
		y = StageField[ lpCurPlayer->OnStageField ]->ActionCamera.FixPos.y+80*fONE;
		z = StageField[ lpCurPlayer->OnStageField ]->ActionCamera.FixPos.z*fONE;

		if ( x<StageField[ lpCurPlayer->OnStageField ]->ActionCamera.LeftX*fONE ) x= StageField[ lpCurPlayer->OnStageField ]->ActionCamera.LeftX*fONE;
		else if ( x>StageField[ lpCurPlayer->OnStageField ]->ActionCamera.RightX*fONE ) x=StageField[ lpCurPlayer->OnStageField ]->ActionCamera.RightX*fONE;

		MakeTraceMatrix( &eTrace, x,y,z, x, lpCurPlayer->pY , 326711*fONE );

		ax = eTrace.AngX;
		ay = eTrace.AngY;
		smRender.OpenCameraPosi( x,y,z, &eTrace.eRotMatrix );

		ActionGameMode = TRUE;
	}
	else if ( !DebugPlayer )
	{
		MakeTraceMatrix( &eTrace, x,y,z, lpCurPlayer->pX, ey, lpCurPlayer->pZ );

		ax = eTrace.AngX;
		ay = eTrace.AngY;
		smRender.OpenCameraPosi( x,y,z, &eTrace.eRotMatrix );
	}

	smRender.ClearLight();

	if ( DarkLevel>0 )
	{
		ap = DarkLevel+(DarkLevel>>2);

		if ( StageField[lpCurPlayer->OnStageField]->State==FIELD_STATE_DUNGEON ) 
		{
			DarkLightRange = 400*fONE;		//320
			ap = DarkLevel;
		}
		else
			DarkLightRange = 260*fONE;		//220


		if ( lpCurPlayer->OnStageField>=0 && StageField[lpCurPlayer->OnStageField]->State==FIELD_STATE_VILLAGE ) 
		{
			//ap = (ap*190)>>8;
			//smRender.AddDynamicLight( lpCurPlayer->pX,lpCurPlayer->pY+32*fONE,lpCurPlayer->pZ, ap,ap,ap,0, DarkLightRange );
		}
		else
			smRender.AddDynamicLight( lpCurPlayer->pX,lpCurPlayer->pY+32*fONE,lpCurPlayer->pZ, ap,ap,ap,0, DarkLightRange );
	}

	DynLightApply();	//Renderer applied to dynamic light

	DrawSky( x,  y,  z,  ax, ay, az );	

	smRender.DeviceRendMode = FALSE;
	renderDevice.BeginScene();

	if( smRender.m_FogIsRend && smRender.m_FogMode )
		renderDevice.SetRenderState(D3DRENDERSTATE_FOGENABLE, TRUE);

	smRender.bApplyRendObjLight = TRUE;	
	DrawPat3D( x, y, z, ax, ay, az );

	smRender.bApplyRendObjLight = FALSE;
	NumPoly = DisplayStage( x ,  y,  z, ax, ay, az );

	smRender.bApplyRendObjLight = TRUE;
	DrawPat3D_Alpha();

	smRender.ClearObjLight();

	if( smRender.m_FogIsRend && smRender.m_FogMode )
		renderDevice.SetRenderState(D3DRENDERSTATE_FOGENABLE, FALSE);

	smRender.ClearLight();
	smRender.Color_A = 0;
	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;

	//Draw Shadows
	DrawPatShadow( x, y, z, ax, ay, az );

	renderDevice.EndScene();
	smRender.DeviceRendMode = TRUE;

	//Texture options to their default values
	RestoreInterfaceTexture();

	DrawEffect(x, y, z, ax,ay,az);					//Drawing No. effects
	cSin3D.Draw( x,y,z,ax,ay,az );
	DrawPat2D( x, y, z, ax, ay, az );


	if( GetFilterEffect() && GetRenderTarget() == NEW_TARGET_BACK )
	{
		SetNewTargetTextureState();
		renderDevice.BeginScene();
		RenderFilterEffect();
		renderDevice.EndScene();
		DefaultsNewTargetTextureState();
	}


	if( g_IsDxProjectZoomIn )
	{
		DrawFullZoomMap();
	}
	else
	{
		if ( cInterFace.sInterFlags.MapOnFlag )
		{
			//Field Map Draw
			if ( DispInterface ) 
				DrawFieldMap();
		}
	}

	if ( (!MsTraceMode && MouseButton[0]==0) || lpCurPlayer->smCharInfo.Stamina[0]>(lpCurPlayer->smCharInfo.Stamina[1]>>2) )
	{
		//Walk Run mode
		lpCurPlayer->MoveMode = cInterFace.sInterFlags.RunFlag;

		if ( ActionGameMode )
			lpCurPlayer->MoveMode = ActionDashMode;
	}
	else 
	{
		if ( lpCurPlayer->smCharInfo.Stamina[0]==0 )
			lpCurPlayer->MoveMode = FALSE;
	}

	smRender.CloseCameraPosi();

	Disp_tx = MsSelPos.x-32;
	Disp_ty = MsSelPos.y;

	//Increased texture frame
	IncTextureFrame();
}

char *CompCmdStr( char *strCmdLine , char *strword )
{
	int len,len2;
	int cnt,cnt2;

	len = lstrlen( strCmdLine );
	len2 = lstrlen( strword );

	for(cnt=0;cnt<len-len2;cnt++) {
		for(cnt2=0;cnt2<len2;cnt2++) {
			if ( strword[cnt2]!=strCmdLine[cnt+cnt2] ) break;
		}
		if ( cnt2==len2 ) 
			return &strCmdLine[cnt+cnt2];
	}

	return NULL;
};

//Command line analysis settings
int DecodeCmdLine( char *lpCmdLine )
{
	char *lpChar;
	int	cnt;

	lpChar = CompCmdStr( lpCmdLine , "/reload=" );
	if ( lpChar ) 
	{
		for(cnt=0;cnt<16;cnt++) 
		{
			if ( lpChar[cnt]==' ' || lpChar[cnt]=='&' || lpChar[cnt]==0 ) 
				break;
		}

		if ( atoi( lpChar )==0 )
		{
			smSetMeshReload( 0 , 1 );
		}
	}

	return TRUE;
}

char *RegPath_3DMax = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\3D Studio MAX R3.1L";
char *RegPath_3DMax2 = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\3D Studio MAX R3.1";
char *RegPath_Photoshop = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Adobe Photoshop 6.0";
char *RegPath_ACDSee = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\ACDSee";

//Registry enforcement operations against illegal software
int HaejukReg()
{
/*
	char *RegStr;
	RegStr = GetRegString( HKEY_LOCAL_MACHINE , RegPath_3DMax , "DisplayName" );
	if ( RegStr ) {
		SetRegString( HKEY_LOCAL_MACHINE , RegPath_3DMax , "DisplayName" , "DeluxPaint 2000" );
		
	}

	RegStr = GetRegString( HKEY_LOCAL_MACHINE , RegPath_3DMax2 , "DisplayName" );
	if ( RegStr ) {
		SetRegString( HKEY_LOCAL_MACHINE , RegPath_3DMax2 , "DisplayName" , "DeluxPaint 2000" );		
	}

	RegStr = GetRegString( HKEY_LOCAL_MACHINE , RegPath_Photoshop , "DisplayName" );
	if ( RegStr ) {
		SetRegString( HKEY_LOCAL_MACHINE , RegPath_Photoshop , "DisplayName" , "Paint School 1.0" );		
	}

	RegStr = GetRegString( HKEY_LOCAL_MACHINE , RegPath_ACDSee , "DisplayName" );
	if ( RegStr ) {
		SetRegString( HKEY_LOCAL_MACHINE , RegPath_ACDSee , "DisplayName" , "ABC 메신저" );		
	}
	
*/	


	return TRUE;
}

//Create font
int SetCreateFont()
{

#ifdef _LANGUAGE_ENGLISH
#ifdef	_CUSTOM_FONT
	hFont = CreateFont( 16,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
                        DEFAULT_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
                        "Comic Sans MS" );
#else
	hFont = CreateFont( 16,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
						DEFAULT_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
						"Comic Sans MS" );

#endif
#endif

#ifdef _LANGUAGE_TAIWAN
	hFont = CreateFont( 12,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
						CHINESEBIG5_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
						"MingLiu" );
#endif


#ifdef _LANGUAGE_JAPANESE

#include "Japanese\\j_font.h"

	hFont = CreateFont( 12,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
						SHIFTJIS_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        FIXED_PITCH | FF_MODERN,
						j_font );
#endif

#ifdef _LANGUAGE_CHINESE

	hFont = CreateFont( 12,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
						GB2312_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
						"SimSun" );
#endif

#ifdef _LANGUAGE_THAI
#ifdef _CUSTOM_FONT
/*#ifdef	_ZHOON_TEST
	hFont = CreateFont(z_fonttest.setdata[0].z_nHeight,
						z_fonttest.setdata[0].z_nWidth,
						z_fonttest.setdata[0].z_nEscapement,
						z_fonttest.setdata[0].z_nOrientation,
						z_fonttest.setdata[0].z_nWeight,
						z_fonttest.setdata[0].z_bItalic,
						z_fonttest.setdata[0].z_bUnderline,
						z_fonttest.setdata[0].z_cStrikeOut,
						z_fonttest.setdata[0].z_nCharSet,
						z_fonttest.setdata[0].z_nOutPrecision,
						z_fonttest.setdata[0].z_nClipPrecision,
						z_fonttest.setdata[0].z_nQuality,
                      z_fonttest.setdata[0].z_nPitchAndFamily,
						z_fonttest.setdata[0].z_lpszFacename);
#else*/
	hFont = CreateFont(13,
						0,
						0,
						0,
						FW_THIN,
						FALSE,
						FALSE,
						FALSE,
						THAI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
                      DEFAULT_PITCH | FF_DONTCARE,
						"MS Sans Serif");
//#endif

#else
	hFont = CreateFont(13,
						0,
						0,
						0,
						FW_THIN,
						FALSE,
						FALSE,
						FALSE,
						THAI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
                      FIXED_PITCH|FF_MODERN,
						"FreesiaUPC");
#endif					
#endif
#ifdef _LANGUAGE_BRAZIL	
	hFont = CreateFont(16,
						0,
						0,
						0,
						FW_THIN,
						FALSE,
						FALSE,
						FALSE,
						ANSI_CHARSET|FS_LATIN1,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FIXED_PITCH|FF_MODERN,
						"Comic Sans MS");
#endif					

#ifdef _LANGUAGE_ARGENTINA
	hFont = CreateFont(16,
						0,
						0,
						0,
						FW_THIN,
						FALSE,
						FALSE,
						FALSE,
						EASTEUROPE_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FIXED_PITCH|FF_MODERN,
						"Tahoma");
#endif

#ifdef _LANGUAGE_KOREAN

	hFont = CreateFont( 12,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
                        HANGEUL_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
                        "굴림체" );
#endif
#ifdef _LANGUAGE_VEITNAM

	hFont = CreateFont( 14,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
						VIETNAMESE_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
						"Tahoma" );
#endif

	return TRUE;

}

//Character set and activate the chat window
int	SetChatingLine( char *szMessage )
{

	cInterFace.ChatFlag = TRUE;
	hFocusWnd = hTextWnd;
	SetWindowText( hFocusWnd, szMessage );
	SetIME_Mode( 1 );		//IME 모드 전환

	//ImmSetConversionStatus( hImc , IME_CMODE_NATIVE,IME_CMODE_NATIVE );
	//ImmSetConversionStatus( hImcEdit , IME_CMODE_NATIVE,IME_CMODE_NATIVE );

	return TRUE;
}

//Windows message process in the game
DWORD GameWindowMessage( HWND hWnd,UINT messg,WPARAM wParam,LPARAM lParam )
{
	int stm,cnt;

	switch( messg ) {

	//case WM_IME_KEYDOWN:
	case WM_KEYDOWN:

			if ( GameMode==2 ) {

				if ( wParam==VK_RETURN && VRKeyBuff[wParam]==0 && !sinMessageBoxShowFlag &&
					!VRKeyBuff[VK_CONTROL] ) {

					SetChatingLine( "" );
				}

				if ( wParam==VK_BACK && VRKeyBuff[wParam]==0 ) {
					if ( HoMsgBoxMode ) 
						HoMsgBoxMode = 0;
					else 
						HoMsgBoxMode = 1;

					SetMessageFrameSelect( HoMsgBoxMode );
				}

				if ( wParam=='M' && VRKeyBuff[wParam]==0 ) {
					//안내지도 띄우기
					sinCheck_ShowHelpMap();
				}

				if ( dwYahooTime>dwPlayTime && dwYahooTime<(dwPlayTime+60*1000) ) {
					if ( wParam==VK_SPACE && VRKeyBuff[wParam]==0 ) {
						if ( lpCurPlayer && lpCurPlayer->MotionInfo ) {
							stm = sinGetStamina();
							cnt = (lpCurPlayer->smCharInfo.Stamina[1]*3)/100;
							if ( lpCurPlayer->MotionInfo->State<0x100 && stm>cnt ) {
								if ( lpCurPlayer->SetMotionFromCode( CHRMOTION_STATE_YAHOO ) ) {
									//lpCurPlayer->HideWeapon = TRUE;
									if ( cnt>0 ) sinSetStamina( stm-cnt );
								}
							}
						}
						VRKeyBuff[wParam] = 1;
						return FALSE;
					}
				}

				//######################################################################################
				//작 성 자 : 오 영 석
				if( smRender.m_GameFieldView && !VRKeyBuff[wParam] )
				{
					if( wParam == VK_ADD )
					{
						if( smRender.m_GameFieldViewStep < 22 )
						{
							smRender.m_GameFieldViewStep++;
							//smRender.SetGameFieldViewStep();
							RendSightSub( 1 );
						}
					}
					else if( wParam == VK_SUBTRACT )
					{
						if( smRender.m_GameFieldViewStep > 1 )
						{
							smRender.m_GameFieldViewStep--;
							//smRender.SetGameFieldViewStep();
							RendSightSub( 1 );
						}
					}
				}
				//######################################################################################



#ifdef _WINMODE_DEBUG

				if (smConfig.DebugMode ) {
					//디버깅용 기능
					if ( wParam == VK_F9 && VRKeyBuff[VK_F9]==0 ) {
						if ( DisplayDebug ) DisplayDebug = FALSE;
						else DisplayDebug = TRUE;
					}
/*
	E_BL_LODING		   = 0,
	E_BL_CHANGE_TRUE   = 1,
	E_BL_CHANGE_FALSE  = 2,
	E_BL_FONT_ROUND    = 3,
	E_BL_FONT_COUNT_1  = 4,
	E_BL_FONT_COUNT_2  = 5,
	E_BL_FONT_COUNT_3  = 6,
	E_BL_FONT_COUNT_4  = 7,
	E_BL_FONT_COUNT_5  = 8,
	E_BL_FONT_COUNT_6  = 9,
	E_BL_FONT_COUNT_7  = 10,
	E_BL_FONT_START    = 11,	
	E_BL_FONT_STAGE    = 12,
	E_BL_FONT_COMPLETE = 13,
	E_BL_FONT_FAIL	   = 14,
*/
					if ( VRKeyBuff[VK_CONTROL] && wParam == 'E' && VRKeyBuff['E']==0 ) {
						//연결 효과음 삽입
						//PlayBGM_Direct( BGM_CODE_SOD1 );
/*
						if ( !BellatraEffectInitFlag ) {
							CreateBellatraFontEffect();
							BellatraEffectInitFlag = TRUE;
						}

						SetBellatraFontEffect(E_BL_CHANGE_TRUE);
*/
/*
extern char	szSOD_String[64];
extern BYTE	bSOD_StringColor[4];
extern int	SOD_StringCount;
*/
						lstrcpy( szSOD_String , "Score up 5000 pts" );
						bSOD_StringColor[0] = 128;
						bSOD_StringColor[1] = 255;
						bSOD_StringColor[2] = 128;
						SOD_StringCount = 256;
					}


					//몬스터 생성
					//int SendOpenMonster( int State )
					//if ( lpCurPlayer->smCharInfo.State!=smCHAR_STATE_USER && VRKeyBuff[wParam]==0 ) {
/*
					if ( VRKeyBuff[VK_CONTROL] && VRKeyBuff[wParam]==0 ) {
						//몬스터 생성
						if ( wParam == '6' ){
								SendOpenMonster( -1 );				//랜덤
						}
						//몬스터 생성
						if ( wParam == '7' ){
								SendOpenMonster( 0 );
						}
						//몬스터 생성
						if ( wParam == '8' ) {
								SendOpenMonster( 1 );
						}
						//몬스터 생성
						if ( wParam == '9' ) {
								SendOpenMonster( 2 );
						}
						//몬스터 생성
						if ( wParam == '0' ) {
								SendOpenMonster( 3 );
						}
						//몬스터 생성
						if ( wParam == 189 ) {//'-' ) {
								SendOpenMonster( 4 );
						}
					}
*/
					//######################################################################################
					//작 성 자 : 오 영 석
					//if ( VRKeyBuff[VK_SHIFT] ) {
					if ( VRKeyBuff[VK_SHIFT] && ! VRKeyBuff[VK_CONTROL] ) {
					//######################################################################################					
						if ( wParam == VK_F5 && VRKeyBuff[VK_F5]==0 ) {
							SkipNextField = 1;
						}
						if ( wParam == VK_F6 && VRKeyBuff[VK_F6]==0 ) {
							SkipNextField = 2;
						}

						//안보이는 벽 표시 비표시
						if ( wParam == VK_F7 && VRKeyBuff[VK_F7]==0 ) {
							if ( smRender.dwMatDispMask ) 
								smRender.dwMatDispMask = 0;
							else
								smRender.dwMatDispMask = sMATS_SCRIPT_NOTVIEW;
						}
/*
						if ( wParam==VK_F11 && VRKeyBuff[wParam]==0 ) {
							if ( DispInterface==0 ) DispInterface=TRUE;
							else DispInterface=FALSE;
						}
*/

						if ( wParam == VK_F8 && VRKeyBuff[wParam]==0 ) {
							//클랜 정보 표시
							if ( ktj_imsiDRAWinfo ) ktj_imsiDRAWinfo=0;
							else ktj_imsiDRAWinfo=1;
						}
					}

						if ( wParam==VK_F11 && VRKeyBuff[wParam]==0 ) {
							if ( DispInterface==0 ) DispInterface=TRUE;
							else DispInterface=FALSE;
						}



					if ( AdminCharMode ) {
						if ( wParam==VK_INSERT && VRKeyBuff[wParam]==0 && VRKeyBuff[VK_CONTROL] ) {
							//시작 지점 추가
							SendAdd_Npc( lpCurPlayer , 0 );
						}
						if ( wParam==VK_DELETE && VRKeyBuff[wParam]==0 && VRKeyBuff[VK_CONTROL] ) {
							//시작 지점 추가
							if ( lpCharSelPlayer ) {
								//NPC 캐릭터 제거
								SendDelete_Npc( lpCharSelPlayer );
							}
						}
					}
					else {
						if ( wParam==VK_INSERT && VRKeyBuff[wParam]==0 && VRKeyBuff[VK_CONTROL] ) {
							//시작 지점 추가
							SendAddStartPoint( lpCurPlayer->pX , lpCurPlayer->pZ );
						}

						if ( wParam==VK_DELETE && VRKeyBuff[wParam]==0 && VRKeyBuff[VK_CONTROL] ) {
							//시작 지점 추가
							if ( lpSelItem ) {
								SendDeleteStartPoint( lpSelItem->pX , lpSelItem->pZ );
							}
						}
					}
				}
#endif

			}
			break;
	}

	return TRUE;
}

//Quest message board where you set
#include "sinbaram\\HaQuestBoard.h"

//Start Quest
int	StartQuest_Code( DWORD wCode )
{
	SetQuestBoard();


	if (InterfaceParty.PartyPosState==PARTY_NONE) {
		//퀘스트 창을 보여준다 
		ShowQuest();
		InterfaceParty.quest_Sel_Progress();	//퀘스트진행버튼누른걸로 셋팅함.
	}

	return TRUE;
}

//End Quests
int EndQuest_Code( DWORD wCode )
{
	//종료된 퀘스트 기록 추가
	Record_LastQuest( (WORD)wCode );
	SetQuestBoard();

	return TRUE;
}

int HoInstallFont()
{
	//폰트를 등록한다
#ifdef	_LANGUAGE_ENGLISH		//C7
	AddFontResource("ptz.ttf");
#endif

#ifdef	_LANGUAGE_THAI		//C7
/*#ifdef	_ZHOON_TEST
	AddFontResource(z_fonttest.z_FontFileName);
#else*/
	AddFontResource("ssee874.fon");
//#endif	
#endif
	
	

	//레지스트리에 등록한다.
	OSVERSIONINFO vi;
	vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	char szKey[255];
	GetVersionEx(&vi);
	if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		strcpy(szKey, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");
	else
		strcpy(szKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Fonts");

#ifdef	_LANGUAGE_ENGLISH		//C7
	SetRegString(HKEY_LOCAL_MACHINE, szKey, "ptz", "ptz.ttf");
#endif
#ifdef	_LANGUAGE_THAI	
/*#ifdef	_ZHOON_TEST
	SetRegString(HKEY_LOCAL_MACHINE, szKey, z_fonttest.z_FontName,z_fonttest.z_FontFileName);
#else*/
	SetRegString(HKEY_LOCAL_MACHINE, szKey, "MS Sans Serif", "ssee874.fon");
//#endif	
#endif

	
	return TRUE;
}

int HoUninstallFont()
{
	//폰트를 제거한다.
#ifdef	_LANGUAGE_ENGLISH		//C7
	RemoveFontResource("ptz.ttf");
#endif
#ifdef	_LANGUAGE_THAI		//C7
/*#ifdef	_ZHOON_TEST
	RemoveFontResource(z_fonttest.z_FontFileName);	
#else*/
	RemoveFontResource("ssee874.fon");
//#endif
#endif	

	//레지스트리 값을 지운다.
	OSVERSIONINFO vi;
	vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	char szKey[255];
	GetVersionEx(&vi);
	if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
		strcpy(szKey, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");
	else
		strcpy(szKey, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Fonts");
	HKEY key;
	DWORD dwDisp;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisp);

#ifdef	_LANGUAGE_ENGLISH		//C7
	RegDeleteValue(key,"ptz");
#endif
#ifdef	_LANGUAGE_THAI		//C7
/*#ifdef	_ZHOON_TEST	
	RegDeleteValue(key,z_fonttest.z_FontName);
#else*/
	RegDeleteValue(key,"MS Sans Serif");
//#endif	
#endif		

	RegCloseKey(key);

	return TRUE;
}
