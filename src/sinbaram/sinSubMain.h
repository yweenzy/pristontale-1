/*----------------------------------------------------------------------------*
*	파일명 :  sinSubMain.h	
*	하는일 :  각종 함수들을 관리한다 
*	작성일 :  최종업데이트 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#ifndef	_SINSUBMAIN_HEADER_

#define _SINSUBMAIN_HEADER_

/*----------------------------------------------------------------------------*
*							    DEFINES
*-----------------------------------------------------------------------------*/	

#define SIN_OPEN		1
#define SIN_CLOSE		0


#define MAX_SIN_KIND_INTER		13  //보여질 각종 폼 // 석지용 - 믹스쳐 리셋 창 추가

#define SIN_CHARSTATUS	0
#define SIN_INVENTORY	1
#define SIN_SHOP		2
#define SIN_SKILL		3
#define SIN_TRADE		4
#define SIN_WAREHOUSE	5			//창고
#define SIN_CRAFTITEM	6			//조합창
#define SIN_AGING		7			//에이징창
#define SIN_MYSHOP		8			//개인상점
#define SIN_CHARSHOP	9			
#define SIN_SMELTING	10			// 제련창
#define SIN_MANUFACTURE 11			// 제작창
#define	SIN_MIXTURE_RESET	12		// 석지용 - 믹스쳐 리셋 창
#define SIN_SYSTEM		13


#define SIN_ALL_CLOSE	100


///////////에이징 클래스 
#define SIN_AGING_ATTACK			100
#define SIN_AGING_CRITICAL			101
#define SIN_AGING_BLOCK				102
#define SIN_AGING_DEFENSE_ORB		103		// 박재원 - 에이징 마스터(방어구 오브 비즈 숙성시킬때)
#define SIN_AGING_DEFENSE_ARMOR		104		// 박재원 - 에이징 마스터(방어구 갑옷 로브 숙성시킬때) 
#define SIN_AGING_DEFENSE_BOOTS		105		// 박재원 - 에이징 아이템 추가(부츠)
#define SIN_AGING_DEFENSE_GLOVES	106		// 박재원 - 에이징 아이템 추가(장갑)
#define SIN_AGING_DEFENSE_ARMLETS	107		// 박재원 - 에이징 아이템 추가(암릿)

/////////// IP별 특화 제도 
#define PRORATE_USER		1
#define FREE_USER			2
#define VIP_USER			4
#define BIRTHDAY_USER		8



#define SIN_WINGRESULT_CRISTAL		0x101

/*----------------------------------------------------------------------------*
*							내부함수 
*-----------------------------------------------------------------------------*/	
void InitSub();     //서브메인 초기화 

void MainSub();	    //서브메인 메인 

void DrawSub();     //서브메인 그리기 

void CloseSub();    //서브메인 종료 

void InitCursor();

void DrawCursor();

int sinRecvMessage( DWORD dwCode , void *RecvBuff ); //서버에서 Data를 받아온다 

void DrawSprite(int winX ,int winY,DIRECTDRAWSURFACE pdds,int x, int y, int width , int height,int Bltflag=1); //컬러키는 현재 무조건 빼준다

int sinGetItemInfo(DWORD CODE , char *szImagePath); //아이템의 정보(ASE)를 구해와서 포인터(*szImagePath)에 셋팅한다 

int sinUsePotion(); //모션이 끝난다음에 포션을 사용한다 

int sinSetInvenItem(sITEMINFO *sItemInfo ); //인벤토리에 아이템을 셋팅한다 

/*각종 공식을 계산후 값을 리턴한다 */

int sinGetAccuracy(int desLV , int desDefense); //내 명중률 

int sinGetMonsterAccuracy(int MonsterLV , int MonsterAttack_Rating); //몬스터 명중률  

int sinGetPVPAccuracy(int MyLevel , int MyAttack_Rating , int DesLevel , int DesDefense);//몬스터 VS 몬스터 명중률

int sinGetCritical(int desLV);//실제 크리티컬 

int sinGetBlockRating(int desLV);//블럭율 

int sinGetAbsorb(int Type=0); //흡수율

/*사용및 리젠관련 */
void sinRegen();
void sinUseStamina(); //스테미나를 사용한다 
void sinSetRegen();   


/*키버튼 및 마우스 함수 */

void sinLButtonUp();

void sinLButtonDown();

void sinRButtonUp();

int StopCharMotion(int x ,int y); //움직임을 멈출곳을 찾는다 

void sinReload(); //그래픽 데이타들을 다시로드한다 

/*마우스 & Key 입력 */
int sinGetMouseButton(int num);//마우스 클릭을 제한 
void sinMouseMain();

int sinGetKeyClick(int num); //키입력을  제한
void sinKeyClickMain();

void ShowInterFace(); //각종 인터페이스를 보여준다 

int sinCreatFont(); //폰트생성 

extern int CheckEditSize(int x , int lx , char *String); //Text가 놓을 위치를 보정한다 


/* 아이템 관련 */

int LoadItemImage(sITEMINFO *sItemInfo , sITEM *TempItem); //아이템의 이미지를 로드한다 

int sinUsePotion(); //모션이 끝난다음에 포션을 사용한다 

int StopCharMotion(int x ,int y); //움직임을 멈출곳을 찾는다 

/* 상점 관련 */
int sinSetShopItem(sITEMINFO *pItem,int ItemCount, int ItemKind); //상점에 대한 정보와 아이템을 받는다 


/*테스트 관련 */
void sinTestDrawText();

/* TEST */
void sinTestKey(); //테스트키 설정 

/*트레이드 관련 */
int sinRequestTrade(DWORD CODE , char *CharName);


/*  스킬 */
int sinSkillMaster(int ChangeJob=0); //스킬을 배우고 전업을 한다 

int sinSkillMasterClose();//스킬 배우기를 마친다 

/* 파티 */
int ShowParty();

/*퀘스트 */
int ShowQuest();



/*라이프 마나 스테미나 코드화 */
short sinGetLife();		//라이프를 읽어온다 
short sinGetMana();		//마나를 얻어온다 
short sinGetStamina();	//스테미나를 얻어온다 

void sinSetLife(short Life);	//라이프를 셋팅한다 
void sinSetMana(short Mana);	//마나를 셋팅한다 
void sinSetStamina(short Stamina);//스테미나를 셋팅한다 

/* 에이징 */
int sinCheckAgingLevel(int Kind, bool bBillingUse);	//레벨을 체크한후 에이징한다 // 박재원 - 에이징 마스터 사용여부를 추가 bBillingUse



/* 퀘스트 */
int sinSetQuestItem(sITEMINFO *sItemInfo ); //퀘스트 아이템일경우
extern int ChangeJobButonCheck2; //버튼다운을 한번 거너뛰는 플랙(이것두 역시 땡빵이다 씨바!!)

//해킹방지를 위해서 돈을 한곳에서 관리한다 
int sinMinusMoney(int Money,int Kind=0);
int sinPlusMoney(int Money);

int sinMinusMoney2(int Money);
int sinPlusMoney2(int Money);

int sinGetElement(smCHAR *pChar); //원소속성을 구한다 


/* 에이징 */
int sinRecvAgingIncreStateItem(sITEMINFO *pItem);
int sinSetAgingItemIncreState(sITEMINFO *pItem);
int sinAgingItemInit(sITEMINFO *pItem,int Down); //아이템 성능을 다운한다

//에이징 능력 증가 
int sinSetDurabilityAging(sITEMINFO *pItem); // 내구력을 계산한다
int sinSetDamageAging(sITEMINFO *pItem);
int sinSetDefenseAging(sITEMINFO *pItem , int Percent);
int sinSetAttackRateAging(sITEMINFO *pItem , int AddNum);
int sinSetAbsorbAging(sITEMINFO *pItem , float Percent);
int sinSetCriticalAging(sITEMINFO *pItem);
int sinSetBlockRateAging(sITEMINFO *pItem);


//에이징 능력 다운
int sinDownDurabilityAging(sITEMINFO *pItem);
int sinDownDamageAging(sITEMINFO *pItem , int Level=0);
int sinDownDefenseAging(sITEMINFO *pItem , int Percent);
int sinDownAttackRateAging(sITEMINFO *pItem , int AddNum);
int sinDownAbsorbAging(sITEMINFO *pItem , float Percent, int Level=0);
int sinDownCriticalAging(sITEMINFO *pItem);
int sinDownBlockRateAging(sITEMINFO *pItem);


//에이징 아이템에 대한 해킹을 막는다 
int sinCheckAgingItemHack(sITEM *pItem);


//WingItem 퀘스트
DWORD sinWingItemQuestServer(sCRAFTITEM_SERVER *pWingItem , smCHAR_INFO *pChar_Info);
int SendWingQuestItem(); //윙아이템 퀘스트 
int RecvWingItem(sCRAFTITEM_SERVER *pWingItem);
int AgingRing();//링을 에이징 한다

//인벤토리에 따로처리해야될 스페셜아이템을 등록한다
int sinSetSpecialItemCode(sITEMINFO *pItemInfo);

//숫자게 콤마를찍어서 리턴한다
int NumLineComa(int Num , char *pBuff);

//물약을 버릴때 저장한다
int sinSaveGame(DWORD CODE , int Count);

//날짜가지난 아이템을 지워준다
int OverDay_Item_Delete(sITEM *pItem);

//모든 인터페이스를 닫는다
int sinCloseInterFace();

//헬프맵이 사용될수있는지 체크해준다
int sinCheck_ShowHelpMap();

//ForceOrb 아이템을 받는다
int sinRecvForceOrb(sITEMINFO *pItemInfo , int Count);

//더블클릭이벤트를 받는다
int sinDoubleClick();
/*----------------------------------------------------------------------------*
*							외부 extern 함수 
*-----------------------------------------------------------------------------*/	

extern int ReformItem( sITEMINFO *lpItemInfo ); //아이템 인증받기 
extern int CheckItemForm( sITEMINFO *lpItemInfo ); //아이템 인증확인 

extern int ReformCharForm(); //재인증 
extern int CheckCharForm(); //인증 

extern int sinSetCharItem(DWORD CODE , DWORD Posi , BOOL SetFlag ); //캐릭터에 아이템을 셋팅한다 

extern int sinThrowItemToFeild(sITEM *pItem); //아이템을 필드에 버린다 

extern int sinActionPotion(); //포션 사용모션 

extern int CompareItems( sITEMINFO *lpItemInfo1 , sITEMINFO *lpItemInfo2 );//아이템 2개를 비교한다



/*----------------------------------------------------------------------------*
*							  extern 변수  
*-----------------------------------------------------------------------------*/	
extern HFONT sinFont; //신바람 폰트 
extern HFONT sinMessageFont;  //메세지 폰트 
extern HFONT sinBoldFont;     //두꺼운 폰트 

extern int sinTestFlag;      //테스트시 사용될 플랙 
extern int MouseButtonUpEvent;

extern int CursorClass; //커서종류 (default로 1을 준다  아이템을 집을 때 CursorClass = 0으로준다 )

extern int Accuracy_Table[][2]; //명중률 테이블을 익스턴한다 

extern int sinSecretFlag;  //암호 플랙 


extern int ItemIndex1[3];
extern int ItemIndex2[3];

extern int ItemImageNotExitFlag;

extern int OverDay_Item_Flag;

extern int SummonSkillCodeIndex[10];

extern int haSiegeBoardTempFlag;

#endif
