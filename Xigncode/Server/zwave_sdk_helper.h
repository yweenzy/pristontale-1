/*--
	Copyright (C) 2007-2010 Wellbia.com Co., Ltd.

	Module Name:
		zwave_sdk_helper.h

	Abstract:
		XIGNCODE Helper for Server

	Author:
		2010-10-18 HyunOh Kim <zextor@wellbia.com>

	Environment:
		any

	Library:
		none

--*/

#pragma once

#ifdef ZWAVE_SDK_HELPER_EXPORTS
#define ZWAVE_SDK_HELPER_API __declspec(dllexport)
#else
#define ZWAVE_SDK_HELPER_API __declspec(dllimport)
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#ifndef SOCKET
typedef UINT_PTR SOCKET;
#endif

#ifndef Z_RETURN
#define Z_RETURN
enum Z_RETURN
{
	Z_RTN_ERROR = -1,			// 잘못된 패킷
	Z_RTN_NONE,				// 정상적인 클라이언트
	Z_RTN_NONCLIENT,			// 논클라이언트 봇 클라이언트
	Z_RTN_BLACK_CODE,			// 치트엔진 탐지
	Z_RTN_SUSPICIOUS,			// 치트엔진 추정 탐지
	Z_RTN_USERDEFINED,		// 사용자 정의
	Z_RTN_RESEND				// 패킷 재전송
};
#endif

enum
{
	XIGNCODE_CLEAN			= Z_RTN_NONE
	, XIGNCODE_NONCLIENT		= Z_RTN_NONCLIENT
	, XIGNCODE_BLACKCODE		= Z_RTN_BLACK_CODE
	, XIGNCODE_SUSPICIOUS		= Z_RTN_SUSPICIOUS
	, XIGNCODE_USERDEFINED	= Z_RTN_USERDEFINED
	, XIGNCODE_RESEND			= Z_RTN_RESEND
	, XIGNCODE_TIMEOUT
};



typedef BOOL (WINAPI *FnSend)(SOCKET s, PVOID meta, LPCSTR buf, SIZE_T size);
typedef void (WINAPI *FnCallback)(SOCKET s, PVOID meta, int code, LPCTSTR report);

class IXigncodeServer
{
public:
	virtual BOOL OnBegin(LPCTSTR lic, SIZE_T blocksize = 512, LPCTSTR path=NULL) = 0;
	virtual BOOL OnEnd() = 0;
	virtual BOOL OnAccept(SOCKET s, PVOID meta) = 0;
	virtual BOOL OnDisconnect(SOCKET s) = 0;
	virtual BOOL OnRecieve(SOCKET s, LPCSTR buf, SIZE_T size) = 0;
	virtual DWORD GetRefCnt() = 0;
	virtual BOOL Release() = 0;
};

ZWAVE_SDK_HELPER_API BOOL WINAPI CreateXigncodeServer(IXigncodeServer** _interface, FnSend _pFnSend, FnCallback _pFnCallback);

///===========================================================
///
/// 아래의 정의와 함수로 zwave_sdk_helper.dll 을 로드함
///

typedef BOOL (WINAPI* PCREATE_XIGNCODE_SERVER)(
	IXigncodeServer** _interface
	, FnSend _pFnSend
	, FnCallback _pFnCallback
	);

inline PCREATE_XIGNCODE_SERVER LoadHelperDllW(wchar_t* pszPath)
{
	wchar_t szT[MAX_PATH];

	if ( pszPath == NULL )
	{
		GetModuleFileNameW(NULL, szT, MAX_PATH);
		wchar_t* _p = wcsrchr(szT, '\\');
		if ( _p++ )
			*_p = 0x00;
	}
	else
		wcscpy(szT, pszPath);

	if ( szT[wcslen(szT)-1] != '\\' ) wcscat(szT, L"\\");
#ifdef _M_X64
	wcscat(szT, L"zwave_sdk_helper_x64.dll");
#else
	wcscat(szT, L"zwave_sdk_helper.dll");
#endif
	HMODULE h = LoadLibraryW(szT);
	if ( h )
	{
		PCREATE_XIGNCODE_SERVER f = (PCREATE_XIGNCODE_SERVER)GetProcAddress(h, "CreateXigncodeServer");			
		if ( f ) return f;
	}
	return NULL;
}


inline PCREATE_XIGNCODE_SERVER LoadHelperDllA(char* pszPath)
{
	if ( pszPath == NULL ) return NULL;
	size_t t = strlen(pszPath) + 1;
	wchar_t* _temp = new wchar_t[t*2];
	MultiByteToWideChar(CP_ACP, 0, pszPath, -1, _temp, t*2);
	PCREATE_XIGNCODE_SERVER f = LoadHelperDllW(_temp);
	delete[] _temp;
	return f;
}

#ifdef _UNICODE
#define LoadHelperDll LoadHelperDllW
#else
#define LoadHelperDll LoadHelperDllW
#endif