/*==============================================================================================
================================================================================================*/
#pragma once
#ifndef __MEMMAP_H__
#define __MEMMAP_H__

//#define MEMMAPNAME   1024

//메모리 맵
//#define MEMORYMAP_MAX		512                    //메모리맵 사이즈
//ktj(채팅스트링등을 고려해 조금 늘렸다.)
#define MEMORYMAP_MAX		4096


#define MEMORYMAP_NAME		"PTE_CALL_VOICECHAT"   //메모리맵 이름
class CMemMap
{
public:
	CMemMap();
	~CMemMap();
public:
	VOID	Clear();
	VOID	SetName(char* name);
	BOOL	InitMemoryMap();             //메모리 맵 초기화 한다.
	VOID	WriteMemoryMap(char *data);  //메모리 맵에 데이타쓰기

	//ktj : 나중에 사이즈넣는 버전만 쓸것
	VOID	WriteMemoryMap(char *data, int size);  //메모리 맵에 데이타쓰기


	VOID    ReadMemoryMap(char* data);
	VOID    SetMemMapSize(int size);

public:
	
	char    m_szMemMapName[64];
	HANDLE  m_hMemMap;

	char   *m_cMemMapPtr;
	int     m_nMemMapSize;

	BOOL    m_bIsMemMap;
};
#endif