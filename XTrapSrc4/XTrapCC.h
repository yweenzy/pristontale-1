
// ***************************************************************
//  XTrapCC   version:  4.0    date: 04/11/2007
//  -------------------------------------------------------------
//  Copyright (C)WiseLogic 2005 - All Rights Reserved
// ***************************************************************

#ifndef	__XAPI_SERVER_CRACK_H_
#define __XAPI_SERVER_CRACK_H_

#include <windows.h>

// Buffer Size
#define XTRAP_CC4_BUFFERSIZE_COMMUNICATION_BASE		128

#define XTRAP_CC4_BUFFERSIZE_SESSION_BASE			320
#define XTRAP_CC4_BUFFERSIZE_SESSION_ADDON			80

// XTRAP_CC4_BUFFERSIZE_SESSION_BASE + XTRAP_CC4_BUFFERSIZE_SESSION_ADDON * MAP파일 갯수 = 320 + 80 * 2
#define XTRAP_CC4_BUFFERSIZE_SESSION				480

#define	XTRAP_CC4_FILESIZE_MAP						45000


// Return Value
#define XTRAP_CC_RETURN_OK					0x00000000
#define XTRAP_CC_RETURN_ERROR				0x00000001
#define XTRAP_CC_RETURN_UNKNOWN				0x00000002
#define XTRAP_CC_RETURN_INVALID_PARAMETER	0x00000003
#define XTRAP_CC_RETURN_INVALID_CRC			0x00000004
#define XTRAP_CC_RETURN_TIMEOUT				0x00000005

#define XTRAP_CC_RETURN_DETECTHACK			0x0000000F


// Protect Option
#define	XTRAP_PROTECT_PE					0x00000001
#define	XTRAP_PROTECT_TEXT					0x00000010
#define	XTRAP_PROTECT_RDATA					0x00000100
#define	XTRAP_PROTECT_EDATA					0x00001000
#define	XTRAP_PROTECT_RSRC					0x00010000
#define	XTRAP_PROTECT_RELOC					0x00100000

#define XTRAP_PROTECT_EXCEPT_VIRUS			0x00000002


// Timeout Limit
#define XTRAP_CC_MAXTIMEOUT					(int)600
#define XTRAP_CC_MINTIMEOUT					(int)100



#if		defined(XTRAPCC_EXPORTS)
#define XTRAPCC_API __declspec(dllexport)
#else
#define XTRAPCC_API
#endif

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef INOUT
#define INOUT
#endif

#ifndef _WIN32
#ifndef __stdcall
#define __stdcall
#endif
#ifndef __cdecl
#define __cdecl
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if	( defined(_WIN32) && !defined(XTRAPCC_EXPORTS) )


typedef unsigned long	(__cdecl *PFN_XTrapCC_ServerInit)	( unsigned long ulPacketTimeOut,	unsigned long ulMapNumber,	unsigned char* pGlobalBuf_Map	);
typedef unsigned long	(__cdecl *PFN_XTrapCC_SessionInit)	( unsigned long ulPacketTimeOut,	unsigned long ulMapNumber,	unsigned char* pGlobalBuf_Map,	unsigned char* pSessionBuf	);
typedef unsigned long	(__cdecl *PFN_XTrapCC_STEP1)		( unsigned char* pSessionBuf, unsigned char* pPacketBuf	);
typedef unsigned long	(__cdecl *PFN_XTrapCC_STEP3)		( unsigned char* pSessionBuf, unsigned char* pPacketBuf	);

extern PFN_XTrapCC_ServerInit	XTrapCC_ServerInit;
extern PFN_XTrapCC_SessionInit	XTrapCC_SessionInit;
extern PFN_XTrapCC_STEP1		XTrapCC_STEP1;
extern PFN_XTrapCC_STEP3		XTrapCC_STEP3;

extern unsigned long	XTrapCCLoadDll				();		// "XTrapCC.Dll" 기본 로딩함수 예제

#else


XTRAPCC_API unsigned long __cdecl	XTrapCC_ServerInit(
	IN		unsigned long	ulPacketTimeOut,
	IN		unsigned long	ulMapNumber, 
	IN		unsigned char*	pGlobalBuf_Map
	);

XTRAPCC_API unsigned long __cdecl	XTrapCC_SessionInit(
	IN		unsigned long	ulPacketTimeOut,
	IN		unsigned long	ulMapNumber, 
	IN		unsigned char*	pGlobalBuf_Map, 
	INOUT	unsigned char*	pSessionBuf
	);

XTRAPCC_API unsigned long __cdecl	XTrapCC_STEP1(
	INOUT	unsigned char*	pSessionBuf, 
	OUT		unsigned char*	pPacketBuf 
	);

XTRAPCC_API unsigned long __cdecl	XTrapCC_STEP3(
	INOUT	unsigned char*	pSessionBuf, 
	IN		unsigned char*	pPacketBuf 
	);


#endif

#ifndef XTRAPCC_EXPORTS


#endif


#ifdef __cplusplus
}
#endif

#endif
