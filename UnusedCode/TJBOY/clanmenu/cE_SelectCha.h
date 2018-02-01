/***************************************************************************************************************
*
*
*
*설명 : 캐릭터 선택했을때 계정에 만들어진 각 캐릭터들이 가입한 클랜 이름과 클랜마크 디스플레이 관련 클래스
***************************************************************************************************************/
#pragma once
#ifndef __CE_SELECTCHA_H__
#define __CE_SELECTCHA_H__


typedef struct _tagChaClan
{
	char ClanName[64];
	char szMarkNum[16];
	int  nStatus;
#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
	LPDIRECTDRAWSURFACE4  hClanMark;
#else
	HBITMAP		hClanMark;
#endif
}CHACLAN;


class CSelectCha
{
public:
	CSelectCha();
	virtual ~CSelectCha();
public:
	void Main();
private:
protected:
	int nHowDownClanName;
};
#endif

#ifdef CE_SELECTCHA_CPP
class CSelectCha   g_SelectCha;
CHACLAN           g_ChaClan[5];
#else
extern class CSelectCha   g_SelectCha;
extern CHACLAN           g_ChaClan[5];
#endif