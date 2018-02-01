#include <windows.h>
#include "memmap.h"
#define __MEMDEBUG



extern void fd( char *fmt, ...);
extern void fd2( char *fmt, ...);


CMemMap::CMemMap()
{
	m_cMemMapPtr = NULL;
	m_hMemMap = NULL;
	m_nMemMapSize = 0;
	m_bIsMemMap = FALSE;
	
}

CMemMap::~CMemMap()
{
}

VOID CMemMap::Clear()
{



	if((m_cMemMapPtr != NULL) &&m_bIsMemMap)
	{
		UnmapViewOfFile(m_cMemMapPtr);
	}
	if(m_hMemMap != NULL)
	{
		CloseHandle(m_hMemMap);
	}
}

VOID CMemMap::SetName(char* name)
{
	ZeroMemory(m_szMemMapName, sizeof(m_szMemMapName) );
	strncpy(m_szMemMapName,name,lstrlen(name));
}

VOID CMemMap::SetMemMapSize(int size)
{
	m_nMemMapSize = size;
}

/*=========================================================================================
*메모리 맵 초기화 한다.
==========================================================================================*/
BOOL CMemMap::InitMemoryMap()
{
	fd2( "메모리 맵 InitMemoryMap() 00");

	if((m_nMemMapSize > 0) &&(m_szMemMapName[0] != 0))
	{
		m_hMemMap = CreateFileMapping(
			INVALID_HANDLE_VALUE,		//0xffffffff으로 설정
			NULL,						//보안속성 : 보통 NULL
			PAGE_READWRITE,				//읽기, 쓰기, 읽기+쓰기
			0,							//할당메모리의 최대크기중 상위 32비트값(64비트값으로 설정가능하기때문)
			m_nMemMapSize,				//할당메모리의 하위 32비트
			m_szMemMapName);		//공유 이름

		//생성 실패
		if(m_hMemMap == NULL)
		{
			fd2( "메모리 맵 InitMemoryMap() 11 실패");
			return FALSE;
		}	

		m_cMemMapPtr =(char *)MapViewOfFile(m_hMemMap, FILE_MAP_ALL_ACCESS,0,0, m_nMemMapSize);

		//메모리 맵 주소를 가지고 오는데 실패
		if(m_cMemMapPtr == NULL)
		{
			
			fd2( "메모리 맵 InitMemoryMap() 44 FALSE");

			return FALSE;
		}
	}
	else
		return FALSE;


	fd2( "메모리 맵 InitMemoryMap() 55 TRUE");
	m_bIsMemMap = TRUE;

	return TRUE;
}

/*=========================================================================================
메모리 맵에 데이타 쓰기..
==========================================================================================*/
VOID CMemMap::WriteMemoryMap(char *data)
{
	if(m_nMemMapSize <=0) 
		return;
	ZeroMemory(m_cMemMapPtr, m_nMemMapSize);

#ifdef __MEMDEBUG
	char szTemp[1024];
	memcpy(szTemp,data,1024);

#endif
	memcpy(m_cMemMapPtr, data, m_nMemMapSize);
}

//ktj : size있어야함
VOID CMemMap::WriteMemoryMap(char *data, int size)
{
	if(m_nMemMapSize <=0) 
		return;
	ZeroMemory(m_cMemMapPtr, m_nMemMapSize);

	memcpy(m_cMemMapPtr, data, size);
}





VOID CMemMap::ReadMemoryMap(char* data)
{
	ZeroMemory(data, m_nMemMapSize);
	memcpy(data,m_cMemMapPtr, m_nMemMapSize);
}