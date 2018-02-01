#pragma once
#ifndef PT_NPKCRYPT_H
#define PT_NPKCRYPT_H
//////////////////////////////////////////////////////////////////////////
//
// 키크립트 헤더 파일을 인클루드 합니다. 
//

#ifndef	_nProtect_For_Debug
#include "npkcrypt.h"
#endif

class CKeyCrypt
{

public:
	CKeyCrypt(void);
	~CKeyCrypt(void);


	BOOL OnLoadKeyCrypt();
	BOOL OnExitKeyCrypt();
	BOOL OnRegisterwindow(HWND hEdit);

//////////////////////////////////////////////////////////////////////////
//
// 키크립트 핸들을 선언 합니다. 핸들은 키크립트가 종료될때 필요하므로, 전역 변수
// 내지는 멤버 변수로 선언 하셔야 합니다.
//

public:
	HKCRYPT		m_hKCrypt;

//////////////////////////////////////////////////////////////////////////
};
#endif

#ifdef PT_NPKCRYPT_CPP

	class CKeyCrypt KeyCrypt;

#else

	extern class CKeyCrypt KeyCrypt;

#endif
