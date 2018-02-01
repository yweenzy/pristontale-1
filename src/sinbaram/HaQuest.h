/*----------------------------------------------------------------------------*
*	파일명 :  haQuest.h	
*	하는일 :  신규 초보 퀘스트 
*	작성일 :  최종업데이트 2005년 5월
*	적성자 :  하대용 
*-----------------------------------------------------------------------------*/	

//elementary

//Quest Bit Code
#define QUESTBIT_ELEMENTARY_A			1       //피곤한 창고지기
#define QUESTBIT_ELEMENTARY_B			2       //두련운 기운
#define QUESTBIT_ELEMENTARY_C			4       //사탕 배달
#define QUESTBIT_ELEMENTARY_D			8       //고블린 동산 
#define QUESTBIT_ELEMENTARY_E			16      //언데드의 위협
#define QUESTBIT_ELEMENTARY_F			32      //외눈박이 괴물
#define QUESTBIT_ELEMENTARY_G			64      //잃어버린 망치
//퓨리의 환영(Fury of phantom)
#define QUESTBIT_FURYOFPHANTOM          128      //퓨리의 환영

/////퀘스트의 종류
#define HAQUEST_CODE_ELEMENTARY_A		0x0020
#define HAQUEST_CODE_ELEMENTARY_B	    0x0021
#define HAQUEST_CODE_ELEMENTARY_C	    0x0022
#define HAQUEST_CODE_ELEMENTARY_D   	0x0023
#define HAQUEST_CODE_ELEMENTARY_E   	0x0024
#define HAQUEST_CODE_ELEMENTARY_F		0x0025
#define HAQUEST_CODE_ELEMENTARY_G		0x0026
#define HAQUEST_CODE_ELEMENTARY_X		0x0027
//퓨리의 환영(Fury of phantom)
#define HAQUEST_CODE_FURYOFPHANTOM      0x0028              
//
enum eQuestKind{
	Quest_A,
	Quest_B,
	Quest_C,
	Quest_D,
	Quest_E,
	Quest_F,
	Quest_G,
};
/*----------------------------------------------------------------------------*
*						구조체
*-----------------------------------------------------------------------------*/	
struct sQUEST_ELEMENTARY{ 
	DWORD CODE;
	DWORD BackUpCode;
	int   Kind;
	int   State;        //숙성 Count
	short Monster[2];   //몬스터 카운트
};
/*----------------------------------------------------------------------------*
*						클래스
*-----------------------------------------------------------------------------*/
class cHaQuest{
private:
	char szBuff[128];
public:
	//
	sQUEST_ELEMENTARY  sHaQuestElementary[8];	
	char szQuestMonsterName[64];
	int iJob_Index;
	int QuestKeyCode;
	int KindClanIndex;
	//
	cHaQuest();
	~cHaQuest();	
	//
	int HaCheckQuestElementary(int npcNum,int QuestKey=0,int KindClan=0);
	int HaLoadQuest(int CODE ,void *Buff );	//퀘스트 데이타를 로드한다 
	int HaSaveQuest(void *Buff );		    //퀘스트 데이타를 세이브한다 
	//
	int haSetQuestTimer(sQUEST_ELEMENTARY *pQuest);
	int haQuestCheck();  //현재 초보  퀘스트가 진행중인지	
	//초보 진행 퀘스트
	int haElementaryQuest_A(int npcNum=0);  //피곤한 창고지기
	int haElementaryQuest_B();			    //두려운 기운 
	int haElementaryQuest_C(int npcNum=0);	//사탕 배달
	int haElementaryQuest_D(int npcNum=0);	//고블린 동산
	int haElementaryQuest_E(int npcNum=0);	//언데드의 위협
	int haElementaryQuest_F();				//외눈박이 괴물
	int haElementaryQuest_G(int npcNum=0);	//잃어버린 망치
//퓨리의 환영(Fury of phantom)
public:
	//
	sQUEST_ELEMENTARY        sHaQuest100LV;	
	bool                     bFuryQuestFlag;
	int                      iFuryQuestIndex[2]; 
	char                     cItemName[32];
	bool                     FuryBattleFlag;
	//아이템 이미지
	DIRECTDRAWSURFACE     lpQuestItemImage[8];
	DIRECTDRAWSURFACE     lpQuestButtonImage[4];


	//필요한것만 테스트
	void init();
	void Main();
	void Draw();
	void KeyDown(); //키 체크
	void LButtonDown(int x , int y);
	void LButtonUp(int x,int y);
	void DrawText();
	void ImageLoad();
	//
	int  showFuryQuest();                  //100LV 퀘스트 호출
	int  showFuryQuestItem(int Kind=0);    //보상 아이템 
	int  RecvBattleNpcResult(int flag);    //퓨리와의 대전 결과 값
	int  Recv100LVItem();                  //보상아이템을 받는디.

	

};
/*----------------------------------------------------------------------------*
*						extern 
*-----------------------------------------------------------------------------*/	
extern cHaQuest chaQuest;
extern DWORD haElementaryQuestLog;
extern void HaCheckQuestNpc(int NpcCount);
