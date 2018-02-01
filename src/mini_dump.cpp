//#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#include "mini_dump.h"
#include "assert.h"

Mini_Dump	*Mini_Dump::gpDumper = NULL;

Mini_Dump::Mini_Dump(void)
{
	assert(!gpDumper);
	if(!gpDumper)
	{
		::SetUnhandledExceptionFilter(Handler);
		gpDumper = this;
	}
}

LONG Mini_Dump::Handler(_EXCEPTION_POINTERS *pExceptionInfo)
{
	LONG retvel = EXCEPTION_CONTINUE_SEARCH;

	if(!gpDumper)
	{
		return retvel;
	}
	return gpDumper->WriteMiniDump(pExceptionInfo);
}

LONG Mini_Dump::WriteMiniDump(_EXCEPTION_POINTERS *pExceptionInfo)
{
	LONG retvel = EXCEPTION_CONTINUE_SEARCH;

	m_pExceptionInfo = pExceptionInfo;
	HMODULE	hDll	 = NULL;
	
	TCHAR	szDbgHelpPath[_MAX_PATH];

	if(GetModuleFileName(NULL,m_szAppPath,_MAX_PATH))
	{
		TCHAR *pSlash = _tcsrchr(m_szAppPath, '\\');
		if(pSlash)
		{
			_tcscpy(m_szAppBaseName,pSlash +1);
			*(pSlash+1) = 0;
		}
		_tcscpy(szDbgHelpPath,m_szAppPath);
		_tcscat(szDbgHelpPath,_T("DBGHELP.DLL"));	
		hDll = ::LoadLibrary(szDbgHelpPath);
	}
	
	if(hDll == NULL)
	{
		hDll = ::LoadLibrary(_T("DBGHELP.DLL"));
	}
	
	LPCTSTR	szResult = NULL;
	
	if(hDll)
	{
		MINIDUMPWRITEDUMP	pMiniDumpWriteDump = (MINIDUMPWRITEDUMP)::GetProcAddress(hDll,"MiniDumpWriteDump");
		if(pMiniDumpWriteDump)
		{
			TCHAR szScratch[_MAX_PATH];

			VSetDumpFileName();
			HANDLE	hFile = ::CreateFile(m_szDumpPath,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			
			if(hFile != INVALID_HANDLE_VALUE)
			{
				_MINIDUMP_EXCEPTION_INFORMATION	ExInfo;

				ExInfo.ThreadId = ::GetCurrentThreadId();
				ExInfo.ExceptionPointers = pExceptionInfo;
				ExInfo.ClientPointers = NULL;
		
				BOOL bOK = pMiniDumpWriteDump(GetCurrentProcess(),GetCurrentProcessId(), hFile,MiniDumpNormal,&ExInfo,VGetUserStreamArray(),NULL);
				
				if(bOK)
				{
					szResult = NULL;
					retvel = EXCEPTION_EXECUTE_HANDLER;
				}
				else
				{
//					_stprintf((wchar_t*)szResult, _T("에러 파일 저장 오류"));
					szResult = szScratch;
				}
				::CloseHandle(hFile);
			}
			else
			{
//				_stprintf((wchar_t*)szResult, _T("에러 파일 생성 오류"));
				szResult = szScratch;
			}
		}
		else
		{
			szResult = _T("DGBHELP.DLL too Old");
		}
	}
	else
	{
		szResult = _T("DGBHELP.DLL not found");		
	}
	
	if(szResult)
		::MessageBox(NULL,szResult,NULL,MB_OK);
	TerminateProcess(GetCurrentProcess(),0);
	return retvel;
}

void Mini_Dump::VSetDumpFileName()
{
	_stprintf(m_szDumpPath, _T("%s%s.dmp"), m_szAppPath, m_szAppBaseName);
}