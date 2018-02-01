/*----------------------------------------------------------------------------*
*	파일명 :  haPremiumItemItem.h	
*	하는일 :  프리미엄 아이템 서비스관련  
*	작성일 :  최종업데이트 2005년 9월
*	적성자 :  하대용 
*-----------------------------------------------------------------------------*/
#pragma once

/*----------------------------------------------------------------------------*
* Desc: 유지형 소모성 아이템일 경우   		
*-----------------------------------------------------------------------------*/
namespace nsPremiumItem{
	enum _Item{
		THIRD_EYES     = 1,	 //아이템드랍증가 
		EXPUP_POTION   = 2,	 //경험치 업 포션
		VAMPIRIC_CUS   = 3,	 //뱀피릭 커스핏
		MANA_RECHAR_P  = 4,	 //마나 리차징 포션
		MIGHT_OF_AWELL = 5,	 // pluto 마이트 오브 아웰
		MANA_REDUCE_P  = 6,	 // pluto 마나 리듀스
		PHENIX_PET	   = 7,  // pluto 펫(해외)
		HELP_PET_TERRY = 8,  // 박재원 - 빌링 도우미 펫 추가
		HELP_PET_NEPSYS= 9,  // 박재원 - 빌링 도우미 펫 추가
		HELP_PET_IO	   = 10,  // 박재원 - 빌링 도우미 펫 추가
		HELP_PET_MUTE  = 11, // 박재원 - 빌링 도우미 펫 추가
		VAMPIRIC_CUS_EX   = 12,	 // 장별 - 뱀피릭 커스핏 EX
		STAMINA_REDUCE_P  = 13, // 박재원 - 근력 리듀스 포션
		//추후추가

	};
}
using namespace nsPremiumItem;	

										// pluto 펫(해외)
#define		SINUPKEEPITEM_MAX       13	// pluto 마나 리듀스 포션 마이트 오브 아웰 추가 // 박재원 - 빌링 도우미 펫 추가 8 -> 11 // 장별 - 뱀피릭 커스핏 EX 11 -> 12 
                                        // 박재원 - 근력 리듀스 포션 12 -> 13
/*----------------------------------------------------------------------------*
* Desc: CONST  형 시간타임 DWORD 형태를 띤다.		
*-----------------------------------------------------------------------------*/
const DWORD SINITEM_TIME_5MINUTE    = (15*60*1);	   //15분
const DWORD SINITEM_TIME_10MINUTE   = (30*60*1);	   //30분
const DWORD SINITEM_TIME_3HOURS		= (3*60*60*1); 	   //3시간
const DWORD SINITEM_TIME_ONEDAY     = (24*60*60*1);    //1일
const DWORD SINITEM_TIME_SEVENDAY   = (7*24*60*60*1);  //7일
const DWORD SINITEM_TIME_30DAY		= (30*24*60*60*1); //30일
// 장별 - 경험치증가 포션(100% 1시간)
const DWORD SINITEM_TIME_1HOURS   = (1*60*60*1);	   //1시간




/*----------------------------------------------------------------------------*
* Desc: 텔레포트 코어		
*-----------------------------------------------------------------------------*/
struct sTelePortCore{
	short   FieldIndex[2];
	bool    PageButtonFlag[2]; 
	short   PageIndex;
	short   ItemIndex;
	char    FieldName[64]; 
};

/*----------------------------------------------------------------------------*
* Desc: 사용시 유지 돼는 아이템		
*-----------------------------------------------------------------------------*/ 
struct sUpKeepItem{
	int     TGAImageNumber;
	bool    Visible;          //유지형 아이템 
	bool    Infoflag;         //유지형 아이템 정보를 보여준다. 
	char    Id[32];		
	int		PosiX;
	int		PosiY;
	DWORD	IconTime[2];
	short   Alpha;
	short   Alphakind;
	int		Per;		//아이템확률 수치를 나타내기 위해.
};

/*----------------------------------------------------------------------------*
* class cHaPremiumItem		
*-----------------------------------------------------------------------------*/
class cHaPremiumItem
{
public:
	DIRECTDRAWSURFACE  lpUpKeepItemBackImage[SINUPKEEPITEM_MAX];    //사용돼는 이미
	sTelePortCore		  TelePortCore;						           //텔레포트 코어
	sUpKeepItem           UpKeepItem[SINUPKEEPITEM_MAX];               //경험치 상승 아이템	
	bool                  UseClickPremiumItemFlag;                     //프리미엄 아이템 사용시 모션이 멈추어야하는것체크  
	int                   Using_ItemKind;
	int                   UpKeepItemTGAImage[SINUPKEEPITEM_MAX];       //사용돼는 이미지
	bool                  haItemUseDelayFlag;
	int					  Using_SelectInvenItemIndex;				  // 박재원 - 이동 상점 아이템(인벤에서 선택된 아이템 인덱스를 가진다.)

	//유지돼는 시간
	DWORD                 m_ThirdEyesTime;
	DWORD                 m_ExpUpPotionTime;
	DWORD                 m_VampiricCuspidTime;
	DWORD                 m_ManaRechargingPTime;
	DWORD				  m_ManaReducePotiontime;		// pluto 마나 리듀스 포션
	int					  m_ManaReducePotionValue;		// pluto 마나 리듀스 포션 감소 %값
	DWORD				  m_MightofAwellTime;			// pluto 마이트 오브 아웰
	int					  m_MightofAwellWeight;			// pluto 마이트 오브 아웰 소지량
	DWORD				  m_PhenixPetTime;				// pluto 펫(해외)
	DWORD				  m_HelpPetTime;				// 박재원 - 빌링 도우미 펫 추가
	DWORD				  m_VampiricCuspidEXTime;		// 장별 - 뱀피릭 커스핏 EX
	DWORD				  m_StaminaReducePotiontime;    // 박재원 - 근력 리듀스 포션
	int					  m_StaminaReducePotionValue;   // 박재원 - 근력 리듀스 포션 감소 %값

	// 장별 - 테리 속성
	DWORD				  m_TerryTime;
  
public:
	cHaPremiumItem();
	~cHaPremiumItem();

	//msg
	void init();
	void Main();
	void Draw();
	void DrawUp();
	void KeyDown(); //키 체크
	void LButtonDown(int x , int y);
	void LButtonUp(int x,int y);
	int  DrawText();
	//프리미엄 부분 유료화 아이템 vvvvv
	int  UsePremiumItem(int kind=0);					     //사용
	int  SetPremiumItemSkill(int kind=0);					 //기능성 아이템 사용
	int  UseTeleportScrollItem(short ItemIndex);             //텔레포트코어 아이템 사용
	int  CheckWindowOpen();									 //마을에서 사용돼는 아이템 창이 열려져 잇을경우는 사용불가
	int  CheckUpKeepItem();					                 //사용시 유지돼는 아이템 체크 
	void InfoBox(int PoisX,int PosiY,int Width,int Height);  //가로 세로 값을 받아 박스를 만든다. 
	int  SetUpKeepItem(int kind,DWORD dwTime,bool visible,char* id,int Percent = 0,short ItemType=0);
	int  cHaPremiumItem::CheckTime(DWORD CurrentTime);		

	//서버에서 현재 남은  시간을 받아 온다.
	void SetThirdEyesTime(DWORD Time){ 	m_ThirdEyesTime   = Time;};
	void SetExpUpPotionTime(DWORD Time){ m_ExpUpPotionTime = Time;};
	void SetVampiricCuspidTime(DWORD Time){ m_VampiricCuspidTime = Time;};
	void SetVampiricCuspidEXTime(DWORD Time){ m_VampiricCuspidEXTime = Time;}; // 장별 - 뱀피릭 커스핏 EX
	void SetManaRechargingPTime(DWORD Time){ m_ManaRechargingPTime = Time;};
	void SetManaReducePotionTime(DWORD Time){ m_ManaReducePotiontime = Time; };		// pluto 마나 리듀스 포션
	void SetManaReducePotionValue(int Value){ m_ManaReducePotionValue = Value; };	// pluto 마나 리듀스 포션 감소 %값
	void SetMightOfAwellTime(DWORD Time){ m_MightofAwellTime = Time; };				// pluto 마이트 오브 아웰
	void SetMightOfAwellWeight(int Weight){ m_MightofAwellWeight = Weight; };		// pluto 마이트 오브 아웰 소지량
	void SetPhenixPetTime(DWORD Time){ m_PhenixPetTime = Time; };					// pluto 펫(해외)
	void SetStaminaReducePotionTime(DWORD Time){ m_StaminaReducePotiontime = Time; };		// 박재원 - 근력 리듀스 포션
	void SetStaminaReducePotionValue(int Value){ m_StaminaReducePotionValue = Value; };		// 박재원 - 근력 리듀스 포션 감소 %값

	// 장별 - 테리 속성
	void SetHelpPetTimeTime(DWORD Time){ m_TerryTime = m_HelpPetTime = Time; };
  	
	//헤어틴트포션
	int  UseHairtintPotion(int ItemKind);//ItemKind 1-A형 2-B형 3-C형 4-D형 5-E , 6-F, 7-G, 8-H, 

	// 박재원 - 에이징 마스터 아이템
	int UseAgingMaster(int ItemKind);

	// 박재원 - 스킬 마스터 아이템
	int UseSkillMaster(int ItemKind);

	// 박재원 - 이동 상점 아이템
	int UseMoveShop();


};
extern cHaPremiumItem  chaPremiumitem;