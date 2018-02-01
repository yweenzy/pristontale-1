/*----------------------------------------------------------------------------*
*	파일명 :  sinSOD2.h
*	하는일 :  현재 Test용으로 쓰이고 있다
*	작성일 :  최종업데이트 5월 
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#ifndef _SINSOD2_HEADER_

#define _SINSOD2_HEADER_
#include <vector>
#include <string>
#include <algorithm>

#define SIN_CLANSKILL_ABSORB			1
#define SIN_CLANSKILL_DAMAGE			2
#define SIN_CLANSKILL_EVASION			3

#define SIN_GURAD_CRISTAL_ICE		    1
#define SIN_GURAD_CRISTAL_LIGHTNING		2
#define SIN_GURAD_CRISTAL_FIRE			3

#define SIN_CASTLEITEMSKILL_S_INVU         1    //무적 스크롤
#define SIN_CASTLEITEMSKILL_S_CRITICAL     2    //크리티컬스크롤
#define SIN_CASTLEITEMSKILL_S_EVASION      3    //추가 회피 스크롤
#define SIN_CASTLEITEMSKILL_S_P_LIFE       4    
#define SIN_CASTLEITEMSKILL_S_RES          5    

#define SIN_CASTLEITEMSKILL_R_FIRE_C       6    //파이어 크리스탈 저항석
#define SIN_CASTLEITEMSKILL_R_ICE_C        7    //아이스 크리스탈 저황석
#define SIN_CASTLEITEMSKILL_R_LIGHTING_C   8    //라이트닝 크리스탈 저항석
#define SIN_CASTLEITEMSKILL_A_FIGHTER      9    //대파이터 공격력 강화석
#define SIN_CASTLEITEMSKILL_A_MECHANICIAN  10   //대메카니션 공격력 강화석
#define SIN_CASTLEITEMSKILL_A_PIKEMAN      11   //대파이크맨공격력 강화석
#define SIN_CASTLEITEMSKILL_A_ARCHER       12   //대아쳐 공격력 강화석
#define SIN_CASTLEITEMSKILL_A_KNIGHT       13   //대나이트 공격력 강화석
#define SIN_CASTLEITEMSKILL_A_ATALANTA     14   //대아틀란타 공격력 강화석
#define SIN_CASTLEITEMSKILL_A_MAGICIAN     15   //대메지션 공격력 강화석
#define SIN_CASTLEITEMSKILL_A_PRIESTESS    16   //대프리스티스 공격력 강화석

/*----------------------------------------------------------------------------*
*							공성전 클랜메뉴
*-----------------------------------------------------------------------------*/	
class cSINSIEGE{
//private:
public:
	int            TaxRate;				    //세율
	int            TotalTax;				//세금 총합 //해외세금
	int			   ExpectedTotalTax;		//인출로 인해 기대되는 세금 //해외
	int            Price;					//사용된 금액총합
public:
	short		   TowerType[6];			//타워 타입
	int			   ClanSkill;				//클랜 스킬
	unsigned char  MercenaryNum[4];			//용병 설정 0 -> 255
	int            TowerTypeDraw[6][2];	    //아이콘
	int            MercenaryNumDraw;		//용병숫자 


public:
	cSINSIEGE(){};
	~cSINSIEGE(){};

	int GetTaxRate();				    //현재 세율리턴
	int	SetTaxRate(int TempTaxRate);	//세율 변경

	int GetTotalTax();						//현재까지 걷어들인 세금총합
	int cSINSIEGE::GetTaxMoney(int Money );	//금액을 찾는다


}; 

/*----------------------------------------------------------------------------*
*							MessageBox
*-----------------------------------------------------------------------------*/	
struct sinMESSAGEBOX_NEW{
	int Flag;
	int PosiX;
	int PosiY;
	int SizeW;
	int SizeH;


	//////////////Button
	int ButtonIndex;
	int ButtonNum;
	int ButtonintPosiX[3]; //일단 5개만 잡아놓는다
	int ButtonintPosiY[3]; //일단 5개만 잡아놓는다
	RECT ButtonRect[3];

};

/*----------------------------------------------------------------------------*
*							cHELPPET 	class		
*-----------------------------------------------------------------------------*/	
class cSINSOD2{

public:
	int UserType; //1 일반유저 , 2 클랜원 ,3 클랜마스터
	int BoxIndex; //현재 보고있는 페이지
	char sinSod2Buff[65536];
	DIRECTDRAWSURFACE ClanMark[10];
	DIRECTDRAWSURFACE ClanMark_32;
	int  ClanMark_32Time;
	int  ClanMark_32Index;
	int  ClanMarkNum[10];
	int  ClanMarkIndex[10];
	int  ClanMarkLoadTime[10];
	int  TotalEMoney;
	int  Tax;
	int  TotalMoney;
	int  ClanImageNum;
	vector<string> sinClanRank;
	char szClanName[32];
	vector<string> sinClanMessage;

	int SendClanMoneyFlag; //중복으로 메세지를 보내지않게 플랙을 준다
	int RecvRemainMoney;
	char szClanMaster[24];
	int ClanMasterMessageBoxFlag; //창이 중복으로떠서 플랙을준다
	int ClanRankFlag; //클랜랭크 메세지를 한번만 보낸다

	//복잡하다 하나더
	DWORD ClanMoney;
	
public:
	cSINSOD2(){};
	~cSINSOD2(){};

	void Init(); //클래스 초기화
	void Load();
	void Release();
	void Draw();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);
	void DrawText();
	void Close();//클래스 종료 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); //키 체크 

	///////
	void ShowSod2MessageBox(); //메세지 박스 보여주기

	void CloseSod2MessageBox(); //메세지 박스 닫기

	void RecvWebDaTa();

	void RecvClanRank(char *szBuff);

	//Space기준으로 String을 분할
	vector<string> Split_ClanRankDaTa(const string& s);

	//String의 길이를 기준으로 String을 분할
	vector<string> Split_ClanMessage(const string& s , const int Len[]);

	//웹 DB에서 메세지를 받는다
	int RecvWebData(int Index ,const string& s); //1정보 2 클랜리스트

	//웹 DB에서 받은 데이타를 구분한다
	vector<string> cSINSOD2::Split_Sod2DaTa(const string& s);

};

//메세지 박스
int ShowSinMessageBox_New(int PosiX , int PosiY , int SizeW , int SizeH , RECT *rect ,int ButtonNum=3);

//서버에서 돈을 받는다
int sinRecvClanMoney(int RemainMoney , int GetMoney);



//////////////////// 공성전 //////////////////////////////
int sinShowSeigeMessageBox();
int RecvSeigeWebData(int Index , char *string);

/*----------------------------------------------------------------------------*
*						  공성전 
*-----------------------------------------------------------------------------*/	
//임시 선언
#define HASIEGE_MODE   //공성전 세율변경  

//공성전 종류 선언
#define HASIEGE_TAXRATES    1  //세율 조정
#define HASIEGE_DEFENSE     2  //방어 설정


//클랜 개수
#define HACLAN_MAX    10   //클랜개수

//클랜 정보를 받을 구조체
struct sHACLANDATA{
	int		Flag;         //클랜 플랙
	int		Score;        //클랜 점수
	int     ClanInfoNum;  //보드에 표시될 좌표   
	char    ClanName[40]; //클랜이름

	DWORD   CLANCODE;     //클랜 코드

	DIRECTDRAWSURFACE lpClanMark;  //클랜 마크	   
};

class cHASIEGE{

public:
    /*---서버에서 호출돼는 함수들----*/
	int   ShowSiegeMenu(smTRANS_BLESSCASTLE *);    //공성메뉴를 연다.
	int   ShowSiegeScore(rsUSER_LIST_TOP10 *);     //현재 클랜들의 점수를 표시한다
	int   ShowExitMessage();         //종료 메세지
	int   ShowPlayTime(int);        //시작 메세지

	/*---클랜 스킬-----*/
	int   SetClanSkill(int);			  //클랜스킬이 있으면 세팅한다.
	int   SetCastleItemSkill(int);	      //공성전 아이템 사용스킬

	int   SendServerSiegeData();          //서버로 데이타를 보낸다.
	int   SetCastleInit();				  //초기화 한다.   
	int   SetCastleMenuInit();            //초기화 할것은 여기에서 다 처리해준다.  

	int	  ShowPickUserKillPoint(int x,int y,int KillCount);

	//동영상을 재생시키다.
	int   ShowCastlePlayMovie(char *szPath,char *TitleName,int Option);


public:
	
	cHASIEGE();
	~cHASIEGE();
	//필요한것만 테스트
	void init();
	void Main();
	void Draw();
	void KeyDown(); //키 체크
	void Release();
	void LButtonDown(int x , int y);
	void LButtonUp(int x,int y);
	void DrawText();
	void ImageLoad();
	
public:
	DIRECTDRAWSURFACE  lpSiegeTax;             //재정메인
	DIRECTDRAWSURFACE  lpSiegeDefense;         //방어메인
	DIRECTDRAWSURFACE  lpCastleButton;         //성메인
	DIRECTDRAWSURFACE  lpMercenary;            //용병메인


	DIRECTDRAWSURFACE  lpDefenseButton[2];     //성/용병설정 버튼
	DIRECTDRAWSURFACE  lpTax_Ok[2];            //돈찾기 확인버튼
	
	DIRECTDRAWSURFACE  lpSiegeDefeseIcon_[3];     //성의 방어설정 아이콘 그레이
	DIRECTDRAWSURFACE  lpSiegeMercenaryIcon_[3];  //용병 아이콘 그레이


	DIRECTDRAWSURFACE  lpSiegeDefeseIcon[3];    //성의 방어설정 아이콘
	DIRECTDRAWSURFACE  lpSiegeClanskillIcon[3]; //클랜 스킬 아이콘
	DIRECTDRAWSURFACE  lpSiegeMercenaryIcon[3]; //용병아이콘

	DIRECTDRAWSURFACE  lpSiegeTaxButton;        //재정설정 메인버튼
	DIRECTDRAWSURFACE  lpSiegeDefenseButton;    //방어설정 메인버튼
	DIRECTDRAWSURFACE  lpSiegeOkButton;         //확인 버튼 
	DIRECTDRAWSURFACE  lpSiegeCancelButton;     //취소버튼

	DIRECTDRAWSURFACE  lpCastleIcon[6];         //성의 종류 활성화 버튼
	DIRECTDRAWSURFACE  lpTaxScroll[2];          //스크롤 버튼
	DIRECTDRAWSURFACE  lpTaxGraph;              //스크롤
	DIRECTDRAWSURFACE  lpDefenseRect[6];        //방어설정 활성화

	DIRECTDRAWSURFACE  lpTwoerImage;

	//
	DIRECTDRAWSURFACE haPlayerButton_G[3];
	DIRECTDRAWSURFACE haPlayerButton[3];
	DIRECTDRAWSURFACE haPlayerButtonBox[3];
	DIRECTDRAWSURFACE haPlayerButtonDown[3];
};



//extern 변수 선언
extern cHASIEGE chaSiege;
extern int haSiegeMenuFlag;        //메뉴 플랙
extern int haMercenrayIndex;       //용병 아이콘 인덱스
extern int HaTestMoney;            //임시 세금총액
extern int haMercenrayMoney[3];    //용병설정 머니
extern int haSiegeBoardFlag;    
extern int haSendTowerIndex;      
extern int haTowerMoney; 
extern int haMovieFlag;

//////////////////// 공성전  end //////////////////////////////
extern cSINSOD2 cSinSod2;
extern sinMESSAGEBOX_NEW sinMessageBox_New;
extern DIRECTDRAWSURFACE	lpbltr_Button_OK;
extern DIRECTDRAWSURFACE	lpbltr_Button_OK_G;
extern int haCastleSkillUseFlag;
extern cSINSIEGE cSinSiege;

#endif

