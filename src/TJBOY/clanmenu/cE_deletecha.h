///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//설명 : 캐릭터 삭제시 클랜해체및 탈퇴로 처리
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef __CE_DELETECHA_HPP__
#define __CE_DELETECHA_HPP__

#include "clan_Enti.h"

//캐릭터 삭제 관련 클랜 처리=======================================================start

#define CLAN_DELETECHA_START					800  //캐릭터 삭제시 isClanmember호출
#define CLAN_DELETECHA_RELEASECLAN_BEFORE        801  //클랜장일 경우 클랜 해체 처리
#define CLAN_DELETECHA_RELEASECLAN              802
#define CLAN_DELETECHA_SECESSION_BEFORE			803  //클랜원일 경우 클랜 탈퇴 처리
#define CLAN_DELETECHA_SECESSION				804
#define CLAN_DIRECT_DELETE					805

//캐릭터 삭제 관련 클랜 처리=======================================================end

class CLANEntity_deletecha: public CLANEntity
{
public:
	CLANEntity_deletecha();
	~CLANEntity_deletecha();

	int Init(int Life);
	int Clear();

	void Main();	
	void Draw();
	void menuInit(int num);
	void SetDeleteChaInfo(char *id, char *gserver, char *chaname);

	BOOL bFlag;
public:
	inline int GetHowDeleteChaFlag(){return nHowDeleteChaFlag;}
	inline void SetHowDeleteChaFlag() {nHowDeleteChaFlag=0;}
public:
	int nHowDeleteChaFlag;
	
	
	
};


#endif 



#ifdef CE_DELETECHA_CPP

class CLANEntity_deletecha cClanDeleteCha;



#else

extern class CLANEntity_deletecha cClanDeleteCha;



#endif
