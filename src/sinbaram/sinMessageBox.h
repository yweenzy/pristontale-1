/*----------------------------------------------------------------------------*
*	파일명 :  sinMessageBox.h
*	하는일 :  각종 메세지 박스들을 관리한다 
*	작성일 :  최종업데이트 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#define MESSAGE_OVER_SPACE				0   //인벤 공간 부족 
#define MESSAGE_OVER_WEIGHT				1   //무게 초과    
#define MESSAGE_NO_USE_ITEM				2   //사용 불가 아이템  
#define MESSAGE_NOT_ENOUGH_MONEY		3	//돈 부족 
#define MESSAGE_NOT_CRAFT_ITEM			4	//믹스쳐할 아이템이 없음 
#define MESSAGE_TRADE_OVER_NUM			5	//트레이드 거래량 초과 
#define MESSAGE_TRADE_CANCEL			6	//트레이드 취소 
#define MESSAGE_POTION_NOT_SETTING		7	//포션셋팅불가 
#define MESSAGE_FAILD_CRAFT_ITEM		8	//아이템 믹스쳐 실패
#define MESSAGE_GIVE_MONEY_TRUE			9	//돈을 기부하다 (참 착하다)
#define MESSAGE_OVER_ITEM_NUM			10	//아이템이 너무 많습니다 
#define MESSAGE_NOT_AGING_ITEM			11	//에이징을 할수없는 아이템 
#define MESSAGE_MOVE_TRADE_ITEM			12	//아이템 사기를 방지하기 위해서 메세지를 표시한다 
#define MESSAGE_OVER_MONEY				13  //소지할수있는 돈을 제한한다 
#define MESSAGE_FAILD_AGING_ITEM		14  //에이징 실패
#define MESSAGE_GYUNGFUM_OK				15  //이벤트 경품 응모
#define MESSAGE_NOTEXIT_ITEMIMAGE		16  //아이템 이미지없음
#define MESSAGE_ALREADY_INITSTATE		17  //이미 능력치를 초기화했습니다
#define MESSAGE_USE_CLAN_ONLY			18  //클랜원만 사용할수있습니다
#define MESSAGE_USE_REGULAR_CLAN_ONLY   19  //정식 클랜만이 사용할수있습니다
#define MESSAGE_NOT_ENOUGH_LEVEL		20  //레벨제한 구역
#define MESSAGE_AGING_LEVEL_DOWN1		21  //에이징 레벨다운 1
#define MESSAGE_AGING_LEVEL_DOWN2		22  //에이징 레벨다운 2
#define MESSAGE_AGING_LEVEL_PLUS		23  //에이징 레벨다운 1
#define MESSAGE_AGING_LEVEL_PLUS2		24  //에이징 레벨다운 2
#define MESSAGE_QUEST_ITEM_DOWN			25  //아이템을 집을수없다
#define MESSAGE_QUEST_ITEM_AGING		26  //퀘스트 아이템 에이징
#define MESSAGE_INCRE_LIFE15			27  //생명력 15상승
#define MESSAGE_PERPFECT_PUZZLE			28  //퍼즐 완성
#define MESSAGE_FAILD_PUZZLE			29  //잘못된 퍼즐
#define MESSAGE_NOT_SALE_ITEM			30  //판매할아이템 없음
#define MESSAGE_MYSHOP_ITEM_DOWN		31  //이미 아이템이 팔렸음
#define MESSAGE_MYSHOP_CLOSE		    32  //판매자의 개인상점이 닫혔음
#define MESSAGE_MYSHOP_NOT_SEARCH		33  //판매자의 개인상점이 닫혔음
#define MESSAGE_MYSHOP_POTION_NUM2		34  //포션 갯수가 맞지않음
#define MESSAGE_NOT_USE_MALE			35  //남자는 사용할수 없음
#define MESSAGE_NOT_USE_FEMALE		    36  //여자는 사용할수 없음
#define MESSAGE_NOT_PICKUP_MALE			37  //남자는 줏을수 없음
#define MESSAGE_NOT_PICKUP_FEMALE	    38  //여자는 줏을수 없음
#define MESSAGE_MYSHOP_CHANGE_PRICE		39  //아이템 가격이 변했음
#define MESSAGE_DONT_HAVE_CLANMONEY		40  //아이템 가격이 변했음
#define MESSAGE_NOT_USE_FORCEORB		41  //사용할수 없는오브입니다 
#define MESSAGE_NOT_USE_FORCEORB2		42  //사용할수 없는오브입니다 
#define MESSAGE_TEST_DAMAGE_FUC			43  //데미지 펑션테스트
#define MESSAGE_FORCEORB_REFINING		44  //포스오브가 제련되었습니다
#define MESSAGE_PLUS_STATE_POINT5		45  //스탯 포인트 +5 추가
#define MESSAGE_PLUS_SKILL_POINT		46  //스킬 포인트 +1 추가
#define MESSAGE_PLUS_POINT_70		    47  //스킬 포인트 +1 추가 스탯 +5
#define MESSAGE_PLUS_POINT_80			48  //스킬 포인트 +2 추가 스탯 +5 
#define MESSAGE_PLUS_POINT_85			49  //사망경험치 1%하락
#define MESSAGE_PLUS_POINT_90			50  //+HP 40
#define MESSAGE_QUEST_NOW_EXIT			51  //진행중인 퀘스트가 있을때
#define MESSAGE_PLUS_POINT_80_2			52  //
#define MESSAGE_PLUS_POINT_90_2			53  //
#define MESSAGE_PLUS_POINT_90_2_MON		54  //퀘스트 진행시 사망
#define MESSAGE_CHANGEJOB4_FAIL			55  //시간초과로 퀘스트실패
#define MESSAGE_MERCENRAY_OVER          56  //용병구입 인원 초과
#define MESSAGE_CLANSKILL_USE           57  //클랜스킬 상요중
#define MESSAGE_NOT_CASTLE_TELEPORT     58  //텔레포트 이동불가
#define MESSAGE_NOT_MYSHOP_ITEM         59  //복주머니는 개인상점에 못올림
#define MESSAGE_NOT_CASTLE_TOTALMONEY   60  //찾을 세금이 없습니다.
#define MESSAGE_NOT_RESEARCH            61  //이미 설문조사를 진행했습니다.
#define MESSAGE_THANKS_RESEARCH         62  //설문조사 감사 메세지
#define MESSAGE_NOT_RECONITEM           63  //아이템 재구성을 할수 없습니다.
#define MESSAGE_RECONITEM_OK            64  //아이템이 재구성되었습니다
#define MESSAGE_100LVBATTLEWIN          65  //퓨리와의 대결에서 승리
#define MESSAGE_100LVBATTLELOSE         66  //퓨리와의 대결에서 패배
#define MESSAGE_100LVITEM_OK            67  //퓨리의 환영 보상아이템을 받다.
#define MESSAGE_ASATTRIBUTE_USE         68  //같은속성의 아이템은 중복사용 못한다.
#define MESSAGE_NOT_DELAYTIME           69  //딜레이 시간으로 인해 사용못함.
#define MESSAGE_NOT_AGINGSHELTOM        70  //에이징 창에 쉘텀이 올라가 잇으면 취소 불가능 메세지
#define MESSAGE_NOT_AGINGPICKUP         71  //임시 픽업 불가 메세지 
#define MESSAGE_NOT_HAIRTINTPOTION      72  //헤어틴트 포션의 같은 머리 사용금지 
#define MESSAGE_FAILD_SMELTING_ITEM		73	// pluto 제련 실패
#define MESSAGE_FAILD_MANUFACTURE_ITEM	74	// pluto 제작 실패
#define MESSAGE_NOT_SMELTING			75	// pluto 픽업 불가
#define MESSAGE_NOT_MANUFACTURE			76	// pluto 픽업 불가
#define MESSAGE_NOT_SAME_SMELTINGITEM	77	// pluto 같은 아이템이 아니다
#define MESSAGE_NOT_NEED_RUNE			78	// pluto 제련에 필요한 룬 아니다
#define MESSAGE_PET_USE_LEVEL			79	// 박재원 - "펫 아이템은 10레벨부터 사용가능합니다." 빌링 도우미 펫 추가
#define MESSAGE_HAVE_NOT_AGINGITEM		80	// 박재원 - "에이징 숙성 할 아이템이 없습니다." 에이징 마스터 에이징 숙성 최대치 아이템
#define MESSAGE_HAVE_NOT_MATURESKILL	81  // 박재원 - "숙련할 스킬이 없습니다." 스킬 마스터 스킬 숙련도를 전직별로 최대치로 한다.
#define MESSAGE_AGING_MATURE_SUCCESS	82  // 박재원 - "에이징 아이템이 숙성되었습니다." 에이징 마스터 사용시
#define MESSAGE_SKILL_MATURE_SUCCESS	83  // 박재원 = "스킬 숙련이 완료되었습니다." 스킬 마스터 사용시
#define MESSAGE_GRAVITYSCROOLFAIL		84		// 장별 - 그라비티 스크롤 5개 다 썼을때 실패 메세지
#define MESSAGE_GRAVITYSCROOLOK			85		// 장별 - 그라비티 스크롤 사용 메세지
#define MESSAGE_NOT_MIXTURE_RESET_ITEM	86	// 석지용 - 믹스쳐 리셋 아이템 픽업 불가
#define MESSAGE_NOT_MIXTURE_RESET_STONE	87	// 석지용 - 믹스쳐 리셋 스톤 등록 불가 (아이템이 올려져 있지 않으면...)
#define MESSAGE_NOT_CANCEL_RESET		88	// 석지용 - 믹스쳐 리셋 창에 스톤이 있으면 취소 불가
#define MESSAGE_FAIL_MIXTURE_RESET_ITEM	89	// 석지용 - 믹스쳐 리셋 실패
#define MESSAGE_OK_MIXTURE_RESET_ITEM	90	// 석지용 - 믹스쳐 리셋 성공
#define MESSAGE_CANNOT_RECONITEM		91	// 박재원 - 리스펙 스톤



#define MESSAGE_SCORE					99  //스매쉬 TV 스코어

#define MESSAGE_BUY_ITEM				0   //아이템 사기 
#define MESSAGE_SELL_ITEM				1   //아이템 팔기 
#define MESSAGE_THROW_ITEM				2   //아이템 버리기 
#define MESSAGE_THROW_MONEY				3   //돈 버리기 
#define MESSAGE_BUY_ITEM_DEFALT			14   //아이템사기(물약이 아닌아이템) (건들지 마시오 땜빵의 결과는 비참하니)
#define MESSAGE_MOVE_MONEY_TRADE		5   //돈거래
#define MESSAGE_MOVE_MONEY_MOVE			6   //돈옮기기 
#define MESSAGE_MOVE_MONEY_RECV			7   //창고에서 돈 받기 
#define MESSAGE_BUY_STAR				8   //별아이템 사기
#define MESSAGE_GIVE_MONEY				9   //기부금
#define MESSAGE_MYSHOP_ITEM				10  //아이템 금액 등록
#define MESSAGE_MYSHOP_POTION			11  //개인상점에서 포션사기
#define MESSAGE_SOD2_GET_MONEY			12  //클랜칩 상금찾기
#define MESSAGE_SIEGE_GET_MONEY         15  //공성전 돈찾기
#define MESSAGE_SIEGE_SET_MERCENRAY     16  //공성전 용병설정



#define MESSAGE_MASTER_SKILL			0   //스킬 습득 메세지  
#define MESSAGE_CHANGE_JOB				1   //전업 메세지 
#define MESSAGE_QUEST					2	//퀘스트 수행 메세지 
#define MESSAGE_INIT_SKILL_POINT		3	//퀘스트 수행 메세지 
#define MESSAGE_EVENT_SMASHTV			4   //이벤트 돈기증 
#define MESSAGE_EVENT_GYUNGFUM			5   //이벤트 경품 
#define MESSAGE_QUEST_CHANGEJOB_MORAYOIN	6   //모라이온 전업퀘스트
#define MESSAGE_POSTBOX					7   //아이템을 받을것인가 
#define MESSAGE_LINKCORE				8   //링크코어를 등록할것인가
#define MESSAGE_RECVITEM				9   //선물받은 아이템을 받을것인가
#define MESSAGE_WARP					10  //특정지역으로 워프할것인가
#define MESSAGE_SECRET_NUM				11  //비밀번호 입력
#define MESSAGE_GIFT_TICKET				12  //상품권으로 별구매 (별아이템)
#define MESSAGE_SELL_HIGHRANK_ITEM		13  //좋은 아이템을 팔때는 한번더 물어본다
#define MESSAGE_QUEST_CHANGEJOB3		14  //3차전직 퀘스트
#define MESSAGE_GIVE_MONEY_CHECK		15  //기부금 다시한번 확인
#define MESSAGE_MYSHOP					16  //개인상점 홍보문구등록
#define MESSAGE_PUZZLE_SEND				17  //퍼즐 보내기
#define MESSAGE_MYSHOP_ITEM_BUY			18  //개인상점 아이템 구매
#define MESSAGE_MYSHOP_ITEM_CANCEL		19  //개인상정 아이템 취소
#define MESSAGE_EVENTITEM_SEND			20  //바벨 아이템을 서버로보낸다
#define MESSAGE_FOXEVENTITEM_SEND		21  //ForceOrb 사용
#define MESSAGE_QUEST_LEVEL30			22  //퀘스트 30
#define MESSAGE_QUEST_LEVEL55			23  //퀘스트 55
#define MESSAGE_QUEST_LEVEL55_2			24  //퀘스트 55 모라이온
#define MESSAGE_QUEST_LEVEL70			25  //퀘스트 70
#define MESSAGE_QUEST_LEVEL80			26  //퀘스트 80
#define MESSAGE_QUEST_LEVEL85			27  //퀘스트 85
#define MESSAGE_QUEST_LEVEL90			28  //퀘스트 90
#define MESSAGE_TELEPORT				29  //텔레포트
#define MESSAGE_QUEST_LEVEL80_2			30  //퀘스트 80_2 데론
#define MESSAGE_QUEST_LEVEL90_2			31  //퀘스트 90_2
#define MESSAGE_CHANGE_JOB4				32  //전업퀘스트 4
#define MESSAGE_CHANGE_JOB4_2			33  //퀘스트완료
#define MESSAGE_CRISTALEVENTITEM_SEND   34  //일곱가지 크리스탈
#define MESSAGE_CASTLE_TELEPORT         35  //블레스 캐슬 텔레포트
#define MESSAGE_CASTLE_BUYTOWER         36  //블레스 캐슬 타워를 세팅한다.
#define MESSAGE_QUEST_ElementaryA       37  //초보 퀘스트(피곤한 창고지기)
#define MESSAGE_QUEST_ElementaryB       38  //초보 퀘스트(두려운 기운)
#define MESSAGE_QUEST_ElementaryC       39  //초보 퀘스트(사탕배달)
#define MESSAGE_QUEST_ElementaryD       40  //초보 퀘스트(고블린 동산)
#define MESSAGE_QUEST_ElementaryE       41  //초보 퀘스트(언데드 위협)
#define MESSAGE_QUEST_ElementaryF       42  //초보 퀘스트(외눈박이 괴물)
#define MESSAGE_QUEST_ElementaryG       43  //초보 퀘스트(잃어버린 망치)
#define MESSAGE_EVENT_ITEMOK            44  //구매 아이템 사용                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
#define MESSAGE_QUEST_100LV             45  //100LV 퀘스트 수행여부
#define MESSAGE_QUEST_100LVITEMOK       46  //100LV 아이템 선물
#define MESSAGE_QUEST_100LVBATTLEOK     47  //100LV 배틀 결과
#define MESSAGE_TELEPORT_CORE           48  //텔레포트 코어 사용
#define MESSAGE_STARDUST_SEND			49  //빛나는 가루	//크리스마스
#define MESSAGE_FALLGAME				50	//횡스크롤 이동 
#define MESSAGE_MANUFACTURE				51	// pluto 제작 할수 있는 종류 메세지
#define MESSAGE_TELEPORT_DUNGEON		52	// pluto 던전 텔레포트 메세지
#define MESSAGE_WATERMELON_EVENTITEM	53	// 박재원 - 수박 모아오기
#define MESSAGE_VALENTINE_EVENTITEM		54	// 장별 - 발렌타인 초콜릿 모아오기
#define MESSAGE_PRISTON_ALPHABET_EVENTITEM	55	// 박재원 - 알파벳 조합 이벤트
#define MESSAGE_CANDYDAYS_EVENTITEM		56	// 장별 - 캔디데이즈
#define MESSAGE_MAGICALGREEN_EVENTITEM		57	// 장별 - 매지컬그린 비취
#define MESSAGE_MAGICALGREEN_EVENTITEM_EMERALD 58 // 장별 - 매지컬그린 에메랄드
#define MESSAGE_TEAROFKARA_EVENTITEM		59	// 장별 - 카라의 눈물
#define MESSAGE_FIND_EVENTITEM		60	// 장별 - 조사원을 찾아라
#define MESSAGE_FINDKAMIU_EVENTITEM		61	// 장별 - 조사원을 찾아라
#define MESSAGE_FINDETO_EVENTITEM		62	// 장별 - 조사원을 찾아라

#define MESSAGE3_MAX					63

struct sMESSAGEBOX{
	char MessageDoc[64];
	char MessageDoc2[64];
	int  Flag;
	int  len;    //메세지 길이 
	int  x,y;    //메세지 박스가 보여질 좌표 
	int  Line;
};

struct sMESSAGEBOX2{
	char MessageDoc1[32];
	char MessageDoc2[32];
	int  Flag;
	int  YesNo;  //1은 OK 2 는 취소 
	int  Count;  //갯수 
	char szCount[64];
	int  x,y;
	int  TextSetX;
	int  Line;

};

struct sMESSAGEBOX3{
	char MessageDoc1[32];
	char MessageDoc2[32];
	int  Flag;
	int  YesNo;  //1은 OK 2 는 취소 
	int  x,y;
	int  TextSetX;
	int  Line;
	char RecvMessage[64];

};

struct sMESSAGEBOX_RECVITEM{ //아이템을 택배로받는다
	int Flag;
	sITEM RecvItem;
	char  szDoc[128];
	char  szItem[64];

	int   ButtonYes;
	int   ButtonNo;
	DWORD  Param[4];
};

//별아이템
struct sSTAR_SHOP{
	int   Flag;
	int   ButtonClose;
	int   BuyOk;
	int   Count;

};

//사라진 아이템
struct sLOST_ITEM{
	int   Flag;
	sITEM LostItem[2];
	int   BuyOk;
	char  szDoc[128];

};

class cMESSAGEBOX{

public:

	int MatBoxLeft;
	int MatBoxRight;
	int MatBoxCenter;

	int MatBoxMain;
	
	DIRECTDRAWSURFACE	lpArrowUpDown[2]; // 0 Up  1 Down

	DIRECTDRAWSURFACE	lpButtonNo[2];     // 0 Yes 1 No
	DIRECTDRAWSURFACE	lpButtonYes[2];    // 0 Yes 1 No

	DIRECTDRAWSURFACE	lpButtonOk[2];     // 0 Ok 1 Cancel
	DIRECTDRAWSURFACE	lpButtonCancel[2]; // 0 Ok 1 Cancel
	DIRECTDRAWSURFACE    lpCount;		   //아이템 갯수 창 	

	DIRECTDRAWSURFACE lpButtonYes07;
	DIRECTDRAWSURFACE lpButtonYesGlay07;
	DIRECTDRAWSURFACE lpButtonNo07;
	DIRECTDRAWSURFACE lpButtonNoGlay07;
	DIRECTDRAWSURFACE lpButtonBox07;

public:
	cMESSAGEBOX();
	~cMESSAGEBOX();

	void Init(); //클래스 초기화
	void Load();
	void Release();
	void Draw();
	void Close();//클래스 종료 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown();

	int  ShowMessage(int Kind);       //메세지박스를  보여준다 
	int  ShowMessage2(int Kind);      //기능이있는 메세지 박스를 보여준다    
	int  ShowMessage3(int Kind , char *Doc);      //메세지가 첨가될 메세지 박스를 보여준다 
	int  ShowMessageEvent(char *Msg); //이벤트 메세지를 보여준다 
	void DrawMessageText();          //메세지 텍스트를 보여준다 
	
	int CheckOkMessageBox(int Kind); //확인 을 눌렀을 경우나 엔터를 입력했을 경우 
	int CheckOkMessageBox2(int Kind);	

	int CloseMessage();              //메세지 박스를 닫아준다 

};

///////////// 별아이템
int StarShopNPC(); //별아이템 판매 npc
int sinStarPoint(int Point);
int DeleteGiftItem(); //상품권아이템을 지운다

////////////

extern cMESSAGEBOX cMessageBox;

extern sITEM *pMessageItem;  //메세지 박스에서 쓰일 아이템 포인터 

extern int sinMessageBoxShowFlag; //현재 메세지박스가 있나 없나를 플랙으로 알수있다

extern sMESSAGEBOX2 sMessageBox2[20]; 

extern int isDrawClanMenu;

extern sMESSAGEBOX_RECVITEM sMessageBox_RecvItem;

extern int sinInitPointFlag7;

extern int sinInitPointPassFlag;

extern int sinSkillPontInitButtonFlag;

extern sITEM *pMessageItem2;  //메세지 박스에서 쓰일 아이템 포인터 (건들기 시러서 한개 더맹금)

//별아이템
extern sSTAR_SHOP sStarShop;

//사라진  아이템
extern sLOST_ITEM sLost_Item;

extern int MyShopItemIndex[100];

extern int MatMyShopPRBoxLine;

extern sITEM UseForceOrbBak;

