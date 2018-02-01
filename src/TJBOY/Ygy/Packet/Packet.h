/*===========================================================================================
============================================================================================*/
#pragma once
#ifndef __PACKET_H__
#define __PACKET_H__

#include "../Memmap/memmap.h"


//#define MEMORYMAP_MAX  4096

class CPacket
{
public:
	CPacket();
	~CPacket();
public:
	VOID Init();
	VOID Clear();	
	VOID Parsing();
	
	char* GetData(){return memMapReadData;}						//들어온 데이타를 저장
	VOID SetSelectCha(char *id,char *chaname, char *clanname,DWORD clannum); //캐릭터 선택

	//이건 나중에...
	VOID SetClanChat(char *msg);


public:
	

private:
	INDEX			*m_Index;
	USERINFO		m_userInfo;

	CLANCHAT            m_sClanChat;

	//메모리맵에서 읽은 데이타를 저장(메모리맵과 크기가 같아야함에 주의)
	char				memMapReadData[MEMORYMAP_MAX];	
};
#endif