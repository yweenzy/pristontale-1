#pragma once
#ifndef __CE_CHATTING_HPP__
#define __CE_CHATTING_HPP__

#include <windows.h>
#include "clan_Enti.h"

//=========================================================
#define BOX_X                 656
#define MOVE_X                 400
#define MOVE_Y                 0



#ifdef USE_PROSTONTALE		//=========================================================

#define CHATING_DISPLAY_MAX       8

#define CHATING_CLANWON_LIST_X    620
#define CHATING_CLANWON_LIST_Y    204 //197
#define CHATING_CLANWON_LIST_CAP  20



#define CHATICON_X               625//( 90 + MOVE_X)  //채팅아이콘 표시 top          
#define CHATCLOSE_X              740//(200 + MOVE_X)
#define CHATICON_Y               375//(230 + MOVE_Y)


#define CHATLIST_SBAR_X	         770//(225 + MOVE_X)
#define CHATLIST_SBAR_Y           193//(45 + MOVE_Y)
#define CHATLIST_MENU                     150

#else						//=========================================================

#define CHATING_DISPLAY_MAX       8
#define CHATING_CLANWON_LIST_X    620
#define CHATING_CLANWON_LIST_Y    130
#define CHATING_CLANWON_LIST_CAP   23

#define CHATICON_X               640//( 90 + MOVE_X)  //채팅아이콘 표시 top          
#define CHATCLOSE_X              730//(200 + MOVE_X)
#define CHATICON_Y               325//(230 + MOVE_Y)
#define CHATLIST_SBAR_X	         770//(225 + MOVE_X)
#define CHATLIST_SBAR_Y           140//(45 + MOVE_Y)
#define CHATLIST_MENU                     105

#endif						//=========================================================

//====================================================================
#define CHATLIST_CLANCHIP                 1
#define CHATLIST_CLANUSER				2
#define CHATLIST_CLANNO_REGESTER			3				
#define CHATLIST_BOX_Y					147







//#define CLANWON_MAX 100
typedef struct _tagCHATLIST
{ 
	int MyPositon;              //클랜장인지, 클랜원인지, 클랜미등록인지 체크
	char  clanWon[CLANWON_MAX][30];        //클랜서버에서 보내준 클랜원을 저장(클랜장 제외)
	char  szUserID[40];           //사용자 아이디
	char  szGameServer[40];        //접속한 서버군
	char  szChaName[40];           //사용자 캐릭터 이름
	char  szClanZang_Name[40];
}CHATLIST;

class CLANEntity_chatting: public CLANEntity
{
public:

	//ktj : 임시
	void chat_WhisperPartyPlayer2(int num);
	void chat_WhisperPartyPlayer(int num);
	void chat_WhisperPartyPlayer_close();

	char szFile_hMark[128];

	CLANEntity_chatting();
	~CLANEntity_chatting();

	int Init(int Life);
	void Close();


	void Main();
	void Draw();
	void InitClanWon();
	void InitClanChatList();
	void MoveClose();


	void menuInit(int num);
	void SortClanWonList();
	void Load();
	void Load2();		//2번째로드시
	
	
	//void OpenDrawBox();
	//void CloseDrawBox();
	//void CloseDraw();



	
	void DrawBox();
	void Draw_C_menuN();
	void NoScroll();

	int  chkMenu(int x, int y, RECT *r);
	int  chkeckMenuN();
	void DoubleClick(int i);


	//void DrawChatList();


	void ChatListParsigClanWon(char* data);
	void ChatListUserData(char *id, char *gserver, char *chaid);
	void ChatListParsingIsClanMember(char* data);
	void SetBoxDraw(BOOL bFlag){bIsBox = bFlag;}
	void SetOpenChatList(BOOL bFlag){bIsClose = bFlag;}
	void DisplayInfo();
public:
#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
	int	hChatListBoxLine;	//배경

	int	hChatListBoxTitle2;

	//DIRECTDRAWSURFACE	hChatListBoxLine; //확인
	DIRECTDRAWSURFACE	hChatListBoxTitle;
	DIRECTDRAWSURFACE	hChatIcon[2];
	DIRECTDRAWSURFACE	hButtonClose[2];
	DIRECTDRAWSURFACE	hClanWon[2];
	DIRECTDRAWSURFACE	hChatClanWon;
	//박철호
#ifdef PARKMENU
	DIRECTDRAWSURFACE	hMicOption[2];
	DIRECTDRAWSURFACE	hMicOptToolTip;
    int	hChatMicOpt;	// 마이크 옵션 윈도우
	DIRECTDRAWSURFACE	hMicOptTitle;	// 마이크옵션 타이틀 이미지
	DIRECTDRAWSURFACE	hMicSortLine;	// 마이크옵션 가로줄
	DIRECTDRAWSURFACE	hMicONBack;	// 마이크on,off백그라운드
	DIRECTDRAWSURFACE	hMicONChk;	// 마이크 on체크이미
	DIRECTDRAWSURFACE	hMicVolBar;	// 마이크옵션 볼륨바
	DIRECTDRAWSURFACE	hMicVOLUPDOWN[2];	// 마이크 볼륨 up,down활성화
	//int	hMicChatIcon;	// 마이크채팅표시 아이콘
#endif
	//박철호
	DIRECTDRAWSURFACE	hClanChatToolTip;
	DIRECTDRAWSURFACE	hBtnCloseToolTip;

#else
	HBITMAP  hChatListBoxLine;
	HBITMAP  hChatListBoxTitle;
	HBITMAP  hChatIcon[2];
	HBITMAP  hButtonClose[2];
	HBITMAP  hClanWon[2];
	HBITMAP hChatListParty;
	HBITMAP hChatListFriend;
	HBITMAP hChatClanWon;
	//박철호
#ifdef PARKMENU
	HBITMAP	hMicOption[2];
	HBITMAP	hMicOptTitle;	// 마이크옵션 타이틀 이미지
	HBITMAP	hMicSortLine;	// 마이크옵션 가로줄
	HBITMAP	hMicONBack;	// 마이크on,off백그라운드
	HBITMAP	hMicONChk;	// 마이크 on체크이미
	HBITMAP	hMicVolBar;	// 마이크옵션 볼륨바
	HBITMAP	hMicVOLUPDOWN[2];	// 마이크 볼륨 up,down활성화
	HBITMAP	hMicOptToolTip;
#endif
	HBITMAP	hClanChatToolTip;
	HBITMAP	hBtnCloseToolTip;
#endif
	
	int nScl_Bar;           //스크롤바
	RECT scrIconPos;		//스크롤바의 움직이는아이콘위치설정
	int nScl_Save;
	int nTotalClanWon;
	int nRest_Num;
	CHATLIST   ClanChatList;
	BOOL bIsBox;
	char szErrorMsg[255];
	int nBoxMove;
	BOOL bIsClose;
	BOOL bIsDrawBoxFinish;	
	int OCcnt;
	int ChatListBoxX;
	int ChatListBoxY;

	int cnt;
	int AddSize;
	RECT ChatList_menuPos[30];		//메뉴셋팅.
	int ChatList_menuSu;
	
	//==================================================
	//
	int Chatting_button;			//스피커 on,off
	
	//박철호
#ifdef PARKMENU
	int MicOpt_button;			// 마이크 옵션 over, down
	int nVol;			// 마이크 볼륨의 값
#endif
	//==================================================

	int nSaveClanWonPos;
	int nDoublClick;
	
};


#endif 





#ifdef CE_CHATLIST_CPP

	class CLANEntity_chatting cClanChatting;

#else

	extern class CLANEntity_chatting cClanChatting;

#endif
