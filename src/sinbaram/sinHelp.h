/*----------------------------------------------------------------------------*
*	파일명 :  sinHelp.h	
*	하는일 :  신바람 도우미
*	작성일 :  최종업데이트 2002년 7월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
 
#define SIN_MAX_HELP_NUMBER		10		//도움말인터 페이스 최대 갯수 

#define SIN_HELP_KIND_NORMAL		1		//기본 도움말
#define SIN_HELP_KIND_QUEST			2		//퀘스트 수행 도움말
#define SIN_HELP_KIND_SMASHTV		3		//스매쉬 TV이벤트 
#define SIN_HELP_KIND_POSTBOX		4		//PostBox
#define SIN_HELP_KIND_SOD			5		//PostBox
#define SIN_HELP_KIND_QUEST_WING	6		//윙 퀘스트는 따로한다
#define SIN_HELP_KIND_WARPGATE		7		//워프게이트 설명을 보여준다
#define SIN_HELP_KIND_INITPOINT		8		//먼가 초기화하는거 같다
#define SIN_HELP_KIND_BABEL			9		//바벨 이벤트
#define SIN_HELP_KIND_Q_LEVEL30		10		//레벨퀘스트30
#define SIN_HELP_KIND_Q_LEVEL55		11		//레벨퀘스트55
#define SIN_HELP_KIND_Q_LEVEL55_2	12		//레벨퀘스트55 모라이온
#define SIN_HELP_KIND_Q_LEVEL70		13		//레벨퀘스트70
#define SIN_HELP_KIND_Q_LEVEL80		14		//레벨퀘스트80
#define SIN_HELP_KIND_Q_LEVEL85		15		//레벨퀘스트85
#define SIN_HELP_KIND_Q_LEVEL90		16		//레벨퀘스트90
#define SIN_HELP_KIND_TELEPORT		17		//텔레포트 
#define SIN_HELP_KIND_Q_LEVEL80_2	18		//레벨퀘스트80_2
#define SIN_HELP_KIND_Q_LEVEL90_2	19		//레벨퀘스트80_2
#define SIN_HELP_KIND_C_TELEPORT    20      //블레스 캐슬 텔레포트 
#define SIN_HELP_KIND_RESEARCH      21      //설문조사
#define SIN_HELP_KIND_TELEPORT_SCROLL   22      //텔레포트 코어
#define SIN_HELP_KIND_TELEPORT_MILTER	23	// pluto 밀터 워프





#define SIN_HELP_COLOR_RED		1		//바탕화면 색
#define SIN_HELP_COLOR_YELLOW	2
#define SIN_HELP_COLOR_GREEN	3
#define SIN_HELP_COLOR_BLUE		4

///////TONY 그림테스트 관련 
#define TONY_TGA				1
#define TONY_BMP				2


/////// 각종 메세지 
#define SIN_MESSAGE_DEFAULT		98
#define SIN_HELP				99	
#define SIN_CHANGEJOB_MESSAGE	100
#define SIN_EVENT_SMASHTV		101
#define SIN_POST_BOX			102
#define SIN_SOD					103



/*----------------------------------------------------------------------------*
*						신바람 도우미 struct
*-----------------------------------------------------------------------------*/	
struct sSINHELP_BOX{
	int Mat;
	float x,  y,  w , h;
	float surW,  surH;
	float tLeft,  tTop,  tRight,  tBottom;
	int Transp;

};

struct sSINHELP{
	int KindFlag;
	int PosiX , PosiY;
	int SizeW , SizeH;
	DWORD BackColor;
	sSINHELP_BOX *sHelp_Box[20][20];
	int MatFlag[20][20];

	///////// Doc 관련 
	int LineCnt;
	char *szDocBuff[100];

	///////// 스크롤 
	int		ScrollFlag;
	POINT	ScrollButton;
	POINT	ScrollMousePosi;
	int		ScrollMAXPosiY_UP;
	int		ScrollMAXPosiY_DOWN;
	int		ScrollMouseDownFlag;

	///////// 버튼 
	POINT	TitlePosi;
	int		ButtonOkFlag;
	POINT	ButtonPosi;
	int		ButtonShowFlag;

	//////// CODE
	int    Code; //중복으로 들어오는건 리턴한다

};
/*----------------------------------------------------------------------------*
*						Tony의 Test 이미지
*-----------------------------------------------------------------------------*/	
struct sTONY_TEST_IMAGE{
	int Flag;
	char ImageFileName[64];
	POINT	Posi;
	POINT	Size;
	DWORD   BackColor;
	POINT	BackPosi;
	POINT	BackSize;
	int		FileFormat;

	int		Mat;
	DIRECTDRAWSURFACE lpTony;

};

struct sSOD_RANK{
	int		Flag;
	int		Job;
	char	Name[64];
	int		Score;
	int		KillNum;

};
/*----------------------------------------------------------------------------*
*						설문 조사 구조체
*-----------------------------------------------------------------------------*/	
struct shaResearch{
	int   Result[10];
	int   Index;
	int   Value[10];
	int   Number;
	BYTE  bSendPollingData[10];
	POINT ButtonPosi;
	int   ButtonShowFlag;
};
/*----------------------------------------------------------------------------*
*						신바람 도우미 class
*-----------------------------------------------------------------------------*/	
class cSINHELP{

public:
	int MatHelpCorner;
	int MatHelpLine;

	int MatScrollBar;
	int MatScrollButton;

	DIRECTDRAWSURFACE	lpHelpTitle;
	DIRECTDRAWSURFACE	lpChangeJobTitle;
	DIRECTDRAWSURFACE	lpHelpOk;
	DIRECTDRAWSURFACE	lpSodMenu;
	DIRECTDRAWSURFACE	lpSodLine;
	DIRECTDRAWSURFACE	lpSodJobFace[8];

	

public:
	int                     ScrollLineCount;  //도움창의 스크롤이 존재할시에 라인수
	int                     NPCTeleportFlag;
	
public:

	cSINHELP();
	~cSINHELP();

	void Init(); //클래스 초기화
	void Load();
	void Release();
	void Draw();	
	void DrawText();
	void Close();//클래스 종료 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); 

	//도움말을 보여준다 
	int sinShowHelp(int Kind , int PosiX , int PosiY , int SizeW , int SizeH , DWORD BackColor,char *File);
	//파일을 읽는다 
	int sinReadFileData(char *name);

	//읽은 파일의 데이타를 버퍼에 분할한다 
	int sinReadFileDataDivide(char *SaveBuf , int Linelen ,int Size);

	////////TONY의 테스트 파일 
	int TonyGetFileData();
	
	////////휠과 키입력으로 스크롤을한다
	int sinGetScrollMove(int Num);
	int sinGetKeyScrollDown();

	//도움말이 떠있는지를 알아온다 
	int sinGetHelpShowFlag();

	//SOD 랭킹을 본다 
	int ShowSodRanking(TRANS_SOD_RESULT *SodResult ,int MyGame=0);

	//Sod 랭킹창이 떠있는지 찾는다
	int GetSodRankBoxState();

	//*haGoon
	//설문 조사
	int ShowResearchMenu(int Kind,int Flag);

	//서버로 보내다
	int SendResearch();

	// pluto 무한 텔레포트 코어 막음
	int sinGetHelpShowFlagNum();
};
int TeleportDungeon();	// pluto 추가던전으로 워프
int haShowCastleTeleportMap();
int sinShowTeleportMap();
int sinShowHelp();
int sinDrawTexImage( int Mat, float x, float y, float w, float h, float surW=0.0f, float surH=0.0f, float tLeft=0.0f, float tTop=0.0f, float tRight=0.0f, float tBottom=0.0f, int Transp=255);
extern sSINHELP sSinHelp[SIN_MAX_HELP_NUMBER];
extern cSINHELP cSinHelp;
extern int HelpBoxKindIndex;
extern int WingItemQuestIndex;
extern int MatHelpBoxImage[10];
extern int sinTeleportIndex;
extern int sinTeleportMoneyIndex;
extern int TeleportUseCose[];
extern int haC_TeleportMoney;
extern char *haC_Not_TeleportFilePath;
extern int haTeleport_PageIndex;


