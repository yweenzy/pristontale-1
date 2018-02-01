
#ifdef _xTrap_GUARD

#include "IntNetwork.h"

#include <windows.h>
// [XTrapIC #1] XTrap.h 파일 인클루드
#include "XTrap.h"
#include ".\xtrapgameclient.h"

#include "..\language.h"

//라이브러리 인클루드
#pragma comment( lib, "ws2_32.lib")
#pragma comment( lib, "XTrapSrc\\XTrapIC_mt.lib" )

class CXTrapGameClient	g_XTrap;

CXTrapGameClient::CXTrapGameClient(void)
{
}

CXTrapGameClient::~CXTrapGameClient(void)
{
	XTrapWinsockEnd();
}

BOOL CXTrapGameClient::XTrap_StartUp(char *szGameTitle, char *szXTrap_MGR_ServerIP)
{
	if( szGameTitle==NULL ) 
		return false;

#ifdef __USE_XTRAP_MANAGER_LOG

	if( szXTrap_MGR_ServerIP==NULL )
		return false;

	SetXTrapMessagerIP(szXTrap_MGR_ServerIP);
#endif

// [XTrapIC #2] XTrap 시작 부분 ( Process의 Initial Entry Point 부분 )
#ifdef __XTRAPMODULE_H
	char	sGameName[MAX_PATH]	= {'\0',};

#ifdef _LANGUAGE_CHINESE
	DWORD	ApiVersion			= 0xA5001207;		//XTrap 버전
	DWORD	VendorCode			= 0x13026020;		//WiseLogic에서 준값
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		// Enable : 0x10, Disable : 0x00
	DWORD	ModuleType			= 0x01FFFFF2;
#else
#ifdef _LANGUAGE_BRAZIL
	DWORD	ApiVersion			= 0xA5001150;		//XTrap 버전
	DWORD	VendorCode			= 0x13026220;		//WiseLogic에서 준값
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		// Enable : 0x10, Disable : 0x00
	DWORD	ModuleType			= 0x0FFFFFFF;
#else
#ifdef _LANGUAGE_JAPANESE
	DWORD	ApiVersion			= 0xA5001150;		//XTrap 버전
	DWORD	VendorCode			= 0x13026030;		//WiseLogic에서 준값
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		// Enable : 0x10, Disable : 0x00
	DWORD	ModuleType			= 0x01FFFFF2;
#else
#ifdef _LANGUAGE_THAI
	DWORD	ApiVersion			= 0xA5001150;		//XTrap 버전
	DWORD	VendorCode			= 0x13026050;		//WiseLogic에서 준값
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		// Enable : 0x10, Disable : 0x00
	DWORD	ModuleType			= 0x01FFFFF2;
#else
#ifdef _LANGUAGE_PHILIPIN
	DWORD	ApiVersion			= 0xA5001150;		//XTrap 버전
	DWORD	VendorCode			= 0x13026070;		//WiseLogic에서 준값
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		// Enable : 0x10, Disable : 0x00
	DWORD	ModuleType			= 0x01FFFFF2;
#else
#ifdef _LANGUAGE_VEITNAM
	DWORD	ApiVersion			= 0xA5001150;		//XTrap 버전
	DWORD	VendorCode			= 0x13026080;		//WiseLogic에서 준값
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		// Enable : 0x10, Disable : 0x00
	DWORD	ModuleType			= 0x01FFFFF2;
#else
	//임시값
	DWORD	ApiVersion			= 0xA5001150;		//XTrap 버전
	DWORD	VendorCode			= 0x00000010;		//WiseLogic에서 준값
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		// Enable : 0x10, Disable : 0x00
	DWORD	ModuleType			= 0x0FFFFFFF;
#endif
#endif
#endif
#endif
#endif
#endif
	strcpy( sGameName, szGameTitle );

#ifdef __USE_XTRAP_MANAGER_LOG
	SetXTrapMgrInfo( szXTrap_MGR_ServerIP );		// Option
#endif

//	SetXTrapPatchHttpUrl( "Http://patch.wiselogic.co.kr:10080/xtrap" );		// Option

#ifdef _LANGUAGE_CHINESE //X-Trap
	SetXTrapPatchHttpUrl( "Http://222.73.230.8/xtrap" );					// 중국 Xtrap 패치서버(작동)
#else
#ifdef _LANGUAGE_BRAZIL	//X-Trap
	SetXTrapPatchHttpUrl( "http://download.priston.com.br/xtrap" );			// 브라질 Xtrap 패치서버(작동)
#else
#ifdef _LANGUAGE_ARGENTINA	//X-Trap
	SetXTrapPatchHttpUrl( "" );			// 브라질 Xtrap 패치서버(작동)
#else
#ifdef _LANGUAGE_JAPANESE	//X-Trap
	SetXTrapPatchHttpUrl( "http://xtrap.pristontale.jp/xtrap" );			// 일본 Xtrap 패치서버(작동)
#else
#ifdef _LANGUAGE_PHILIPIN	//X-Trap
	SetXTrapPatchHttpUrl( "http://gupdate.netplay.ph/updates/X-trap" );		// 필리핀 Xtrap 패치서버
#else
#ifdef _LANGUAGE_VEITNAM	//X-Trap
	SetXTrapPatchHttpUrl( "http://xtrap.ptv.com.vn" );						// 베트남 Xtrap 패치서버(작동)
#else
#ifdef _LANGUAGE_THAI		//X-Trap
	SetXTrapPatchHttpUrl( "http://patch.pt.in.th/xtrap" );					// 태국 Xtrap 패치서버
#endif
#endif
#endif
#endif
#endif
#endif
#endif

	SetXTrapStartInfo(  sGameName,
						ApiVersion,
						VendorCode,
						KeyboardType,
						PatchType,
						ModuleType );

	XTrapStart();
	XTrapKeepAlive();
#endif

//	xTrapConnect(GetXTrapMessagerIP());
//	SendLoginData();

	return TRUE;
}


//######################################################################################
//작 성 일 : 2006-08-11 오후 6:18:57
//함 수 명 : xTrapConnect()
//인 자 값 : szServerIP
//리 턴 값 : 접속 성공시 TRUE, 실패시 FALSE
//설    명 : 소켓을 초기화 하며, XTRap 메신져 서버에 접속한다. (IDC나 사내에 있는 IP를 적어줘야 된다.)
//작 성 자 : 박 철 호
//######################################################################################
BOOL CXTrapGameClient::xTrapConnect(const char *szServerIP)
{ 
	if(!XTrapWinsockStart())
		return false;

	if(!ConnectXTrapMessagerServer(szServerIP))
		return false;

	return true;
}

#endif