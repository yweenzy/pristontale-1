#define PT_NPKCRYPT_CPP

#include <windows.h>
#include "PT_KeyCrypt.h"

#define IDS_ERR_DRIVERVERSION "설치된 드라이버 버전이 맞지 않습니다.\n\n최신 업데이트를 받으신 후 컴퓨터를 재 시작 해 주십시요."

#define IDS_ERR_VERIFYVERSION "프로그램에 호환성 모드가 체크되어 있습니다. 체크를 해제하신 후 다시 실행해 주십시요."

#define IDS_ERR_LOADFAIL "드라이버가 초기화 되지 않았습니다.\n\n초기화 버튼을 눌러서 드라이버를 초기화 해 주십시요."

CKeyCrypt::CKeyCrypt(void)
{
}

CKeyCrypt::~CKeyCrypt(void)
{
}

BOOL CKeyCrypt::OnLoadKeyCrypt()
{
	// TODO: Add your control notification handler code here
	char szFileName[MAX_PATH] = {0,};
	char szGameFileName[MAX_PATH] = {0,};

	BOOL	bStatus = FALSE;

	// 실 적용시 game Client 실행파일의 Full Path.
	char szSysPath[MAX_PATH];
	if( GetCurrentDirectory(sizeof(szSysPath), (char*)szSysPath) == 0 ) 
		return FALSE;

	wsprintf((char*)szGameFileName, "%s\\game.exe", szSysPath);

	//MessageBox(NULL,szGameFileName,"",MB_OK);

	if(NPKGetAppCompatFlag(szGameFileName) != apcfNone)
    {
		//OutputDebugString("--> ReStart Program\n");

		char	strErrMsg[256] = {0,};

		NPKSetAppCompatFlag(szGameFileName, apcfNone);
		
		//wsprintf(strErrMsg, "%s Program 종료후 재 실행 해주세요.!!\n", szGameFileName);
		//::MessageBox(NULL, strErrMsg, "nProtect KeyCrypt", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
		return FALSE;
    }
    else
	{
		//OutputDebugString("--> Load KeyCrypt\n");

		bStatus = NPKGetLoadStartup();

		GetModuleFileName(NULL, szFileName, sizeof szFileName);
		char *ptr = strrchr(szFileName, '\\');
		if(ptr != NULL)
			*ptr = 0;

		NPKSetDrvPath(szFileName);
		m_hKCrypt = NPKOpenDriver();

		if(m_hKCrypt <= 0)
		{
			HLOCAL	hlocal = NULL;
			DWORD	dwError = GetLastError();
			char	strErrMsg[256] = {0,};
			
			BOOL fOk = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 
				NULL, 
				dwError, 
				MAKELANGID(LANG_KOREAN, SUBLANG_ENGLISH_US), 
				(PTSTR) &hlocal, 
				0, 
				NULL);
			
			if(fOk)
			{
				//strcpy(strErrMsg,(PCTSTR) LocalLock(hlocal));
				::LocalFree(hlocal);
			}
			else
			{
				switch(dwError)
				{
				case NPK_ERROR_NOTADMIN:
					break;

				case NPK_ERROR_DRIVERVERSION:
					strcpy(strErrMsg,IDS_ERR_DRIVERVERSION);
					break;

				case NPK_ERROR_VERIFYVERSION:
					strcpy(strErrMsg,IDS_ERR_VERIFYVERSION);
					break;
				}
			}

			//::MessageBox(NULL, strErrMsg, "nProtect KeyCrypt", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
			return FALSE;
		} else {

			NPKLoadAtStartup(TRUE);
		}
	}

	return TRUE;
}

BOOL CKeyCrypt::OnExitKeyCrypt()
{
	// TODO: Add your control notification handler code here
	if(m_hKCrypt > 0)
		NPKCloseDriver(m_hKCrypt);
	else
	{
		/*char	strErrMsg[256] = {0,};
		strcpy(strErrMsg,IDS_ERR_LOADFAIL);
		::MessageBox(NULL, strErrMsg, "nProtect KeyCrypt", MB_OK | MB_ICONERROR);*/
		return FALSE;
	}
	return TRUE;
}
BOOL CKeyCrypt::OnRegisterwindow(HWND hEdit)
{
	// TODO: Add your control notification handler code here
	if(m_hKCrypt > 0)
		NPKRegCryptMsg(m_hKCrypt, hEdit, WM_USER + 1094);
	else
	{
		/*char	strErrMsg[256] = {0,};
		strcpy(strErrMsg,IDS_ERR_LOADFAIL);
		::MessageBox(NULL, strErrMsg, "nProtect KeyCrypt", MB_OK | MB_ICONERROR);*/
		return FALSE;
	}
	return TRUE;
}