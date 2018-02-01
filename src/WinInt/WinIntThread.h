
//######################################################################################
//작 성 일 : 2003-10-10 오후 1:47:40
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
#pragma once


////////////////////////////////////////////////////////////////////////////////////////
//
#include <wininet.h>
#pragma comment( lib, "wininet.lib" )
#pragma comment( lib, "Library\\ohZipLib.lib" )
////////////////////////////////////////////////////////////////////////////////////////


//
extern HINTERNET g_hInternetOpen;

//
extern int  CreateWinIntThread(void);
extern void DestroyWinIntThread(void);

extern inline void ErrorWinIntThread(void);
extern inline int  IsErrorWinIntThread(void);
extern inline int  IsWinIntThreadState(void);

//extern int WinIntThreadSuspend(void);
extern int WinIntThreadResume(void);