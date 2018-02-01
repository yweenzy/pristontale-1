#ifndef __AUTH_H__
#define __AUTH_H__
#ifndef USE_PROSTONTALE		//=========== 프리스턴소스인경우
#include "..\\clanmenu\\cE_CViewClanInfo.h"
#endif


//DEFINE_YCY
#define CDKEYLEN 32
#define CONFIG   10

#define AUTH_ERROR_OTHER 1009
#define INET_ADDRSTRLEN 16
#define AUTH_ERROR_END  20
#define AUTH_OK 1
//END_YCY

// DB의 큐의 커맨드
enum {
	/*
	AUTH_QUE_COMMAND_NONE,
	AUTH_QUE_COMMAND_AUTH,          // 인증하다
	AUTH_QUE_COMMAND_AUTH_KTJEND,   // ktj : 새로넣은 끝내기 과금인증
	AUTH_QUE_COMMAND_ALLNUM,
	*/

	AUTH_QUE_CMD_NONE,

	AUTH_QUE_CMD_isClanMember,		//클랜멤버인지를 알아냄
	AUTH_QUE_CMD_CL_MAKE,			//클랜만듦(클랜칩이 클랜만들때 사용 : 클랜과클랜원데이타저장)
	AUTH_QUE_CMD_CL_MEMBER_MAKE,    //클랜원저장(클랜에 가입한경우 사용 : 클랜데이타추가,클랜원데이타만듦)
	AUTH_QUE_CMD_ReadClan,			//클랜데이타를 읽는다.
	AUTH_QUE_CMD_BreakUP,			//클랜을 해체한다.
	AUTH_QUE_CMD_Banishiment,		//클랜원 추방한다.
	AUTH_QUE_CMD_WarhouseR,			//권한바꿈.
	AUTH_QUE_CMD_updateFlag,		//클랜결성완료를 위한 플래그셋팅
	AUTH_QUE_CMD_Secession,		//클랜원 스스로 탈퇴한다.

	AUTH_QUE_CMD_MarkREAD,		//클랜마크를 읽는다.
	//ygy
	AUTH_QUE_CMD_isCheckClanJang,		//클랜장이 중복인지 체크
	AUTH_QUE_CMD_isCheckClanName,		//클랜이름이 중복인지 체크
	AUTH_QUE_CMD_isPFlag,
	AUTH_QUE_CMD_ReadClanInfo,
	AUTH_QUE_CMD_MarkREAD2,		//클랜마크를 읽는다.
	AUTH_QUE_CMD_Updatcldata,
	AUTH_QUE_CMD_ReadNotice,
	AUTH_QUE_CMD_LeaveClan,
	AUTH_QUE_CMD_isKPFlag,
	AUTH_QUE_CMD_AppointSubChip,
	AUTH_QUE_CMD_ReleaseSubChip,
	AUTH_QUE_CMD_GetWavFile,

	AUTH_QUE_CMD_SOD2,
	AUTH_QUE_CMD_isCheckClanMember,	//호동Clan추가 (클랜 탈퇴 후 재가입 기간(4일)이 경과되었는지 아닌지 검사
	AUTH_QUE_CMD_ALLNUM,
};

// 큐의 1개의 데이터의 존재．
// 복수 스레드로 처리를 하기 때문에 존재한다．
enum {
	AUTH_QUE_STATUS_NONE,
	AUTH_QUE_STATUS_EXIST,          // 데이터가 존재한다．
	AUTH_QUE_STATUS_BEGINAUTHPROC,        // (다른 스레드가)데이터를 읽고 처리하고 있다．
	AUTH_QUE_STATUS_ENDOFAUTHPROC,  // AUTH 처리 종료
};

// AUTH 메시지 큐 구조 체
typedef struct _STRUCT_AUTH_QUE{
	
	int status;                  // 이 데이터의 상태
	int command;                 // 어떤 요구나 ．
	int fdid;                    // 플레이어의 fdid
	int result;                  // DB 처리의 대답
	int badmsg;                  // 플레이어에게 메시지를 낼까？
	int index;					// 배열의 번호
	unsigned int query_time;              // 큐에 의뢰를 냈던 시각
	char cdkey[CDKEYLEN];
	char isaokey[128];
	char password[128];



	//------------------  ktj : 새로 넣음.	start
	char ip_address[128];
	long howmanyTime;		//게임시간첵크용:나갈때첵크시 쓰레드라서 세이브해두어야함.	
	
	char id[64];			//한글 8자,
	char charId[64];		//캐릭터id
	char expl[256];			//200바이트까지유효함
	char clanName[64];		//한글 8자,
	char ret_Buf[2048];		//web db에서 날아온 스트링
	char gserver[64]; //현재 군서버
	char ClanWon_ID[64];   //현재 캐릭터명
	char ClanWon_ChaName[64];
	char ClanZang_ID[64];  //클랜 짱아이디
	char ClanZang_ChaName[64]; //클랜짱 캐릭터 이름
	char Gubun[1]; //클랜짱인지 클랜원인지 구분
    char Mark[64];
    int  nNum;
    CLANINFO* ci;
    int ClanInfo_Count;
	int level; //레벨

	int joinlevel;
	int joinjobcode;
	char chipflag[2]; //클랜칩이지 부클랜칩이지 구분
	DWORD job_code;//캐릭터 타입
	char  szWavFileName[64];
	char  szSod2Buff[65536];


	//------------------  ktj : 새로 넣음.	end
    //====================ygy
    char PFlag[3]; //첫화면 관련 플래그
 


	struct _STRUCT_AUTH_QUE *pNext;	// 다음의 링크 포인터
	struct _STRUCT_AUTH_QUE *pPrev;	// 전(앞)의 링크 포인터
//	pthread_mutex_t mutex;       // 이 구조체의 mutex


	int sod2index;
}AUTH_QUE;


int AUTH_addQue( AUTH_QUE *que);
int AUTH_getResultLoop( void);



DWORD WINAPI AUTH_MainLoop(void* pVoid);
int end_GOLDmoney(char* cdkey, char* isaokey, char* passwd, char* ip_address);
int end_GOLDmoney2(char* cdkey, char* isaokey, char* passwd, char* ip_address);
int start_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address);
int IsaoCheck2( char *id, char *pass, int iCheckOn, int iTimeOut , char *ipaddr, long usertime);
// ＡＵＴＨ 큐의 링크 테이블
enum{
	AUTHLINKTBL_FREE,
	AUTHLINKTBL_START_WAIT,
	AUTHLINKTBL_WORKING,
	AUTHLINKTBL_FINISH,
	AUTHLINKTBL_MAX
};
typedef struct {
	AUTH_QUE QueTop, QueTail;
}AUTHLINKTBL;

//AUTHLINKTBL aAuthLinkTbl[AUTHLINKTBL_MAX];


int end_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address);

#endif





#define FLAG_DEAD  0
#define FLAG_EXEC  1
#define FLAG_WAIT  2
#define FLAG_EXIT  3

typedef struct
{
    DWORD thrHandle;
    int flag;
	int state;
    int cnt;
} THREADstruct;

class WebDB_Thread
{
public:
	

	THREADstruct ThreadS;

    WebDB_Thread();
	~WebDB_Thread();
	
	void init();							//겜 처음에서 셋팅
	void init(int iCheckON);				//웹db사용시마다 셋팅
	void init_HostName_Port(char *hostname, int port);
	void main();
	void end();

	//ktj : 클랜접속용 호스트가 설정되있는지 여부
	void CheckHostNamePort(char *hostname, int port);

	int AUTH_init(int Num);
	int AUTH_close( void);

	void Suspend();    //중지
	void Resume();      //재개

	int AUTH_getResultLoop( void);




	//웹db에 접속하는 명령처리 함수 : 각명령마다 처리함수와 결과함수를 만들어주어야함.

	//클랜멤버인지를 알아냄.
	int AUTH_proc_isClanMember( int quenum, int threadindex);
	int AUTH_proc_isClanMember_Result( int quenum, int threadindex);

	//호동Clan추가
	int AUTH_proc_isCheckClanMember(int quenum, int threadindex);
	int AUTH_proc_isCheckClanMember_Result(int quenum, int threadindex);
    int isCheckClanMember(char *pszServerName, char *pszUserName);


	//클랜을 만드는 함수
	int AUTH_proc_ClanMake( int quenum, int threadindex);
	int AUTH_proc_ClanMake_Result( int quenum, int threadindex);


	//클랜멤보를 만드는 함수
	int AUTH_proc_Mmake( int quenum, int threadindex);
	int AUTH_proc_Mmake_Result( int quenum, int threadindex);
	
	//클랜을 읽는 함수
	int AUTH_proc_ReadClan( int quenum, int threadindex);
	int AUTH_proc_ReadClan_Result( int quenum, int threadindex);

	
	//클랜을 삭제하는함수.
	int AUTH_proc_BreakUP( int quenum, int threadindex);
	int AUTH_proc_BreakUP_Result( int quenum, int threadindex);

	//특정 id추방
	int AUTH_proc_Banishiment( int quenum, int threadindex);
	int AUTH_proc_Banishiment_Result( int quenum, int threadindex);

	//권한바꿈.
	int AUTH_proc_WarhouseR( int quenum, int threadindex);
	int AUTH_proc_WarhouseR_Result( int quenum, int threadindex);

	//클랜결성끝남.
	int AUTH_proc_updateFlag( int quenum, int threadindex);
	int AUTH_proc_updateFlag_Result( int quenum, int threadindex);

	
	//클랜탈퇴.
	int AUTH_proc_Secession( int quenum, int threadindex);
	int AUTH_proc_Secession_Result( int quenum, int threadindex);

	//클랜마크읽기

	int AUTH_proc_MarkREAD( int quenum, int threadindex);
	int AUTH_proc_MarkREAD_Result( int quenum, int threadindex);

	//다른 클랜마크읽기

	int AUTH_proc_MarkREAD2( int quenum, int threadindex);
	int AUTH_proc_MarkREAD2_Result( int quenum, int threadindex);

	//isCheckClanJang 관련된 계정이 클랜장으로 등록되어 있는지 체크
	int AUTH_proc_isCheckClanJang( int quenum, int threadindex);
	int AUTH_proc_isCheckClanJang_Result( int quenum, int threadindex);
	
	//ygy : 클랜이름이 중복되었는지 체크
	int AUTH_proc_isCheckClanName( int quenum, int threadindex);
	int AUTH_proc_isCheckClanName_Result( int quenum, int threadindex);

	//ygy :초기 화면 관련 플래그
	int AUTH_proc_isPFlag( int quenum, int threadindex);
	int AUTH_proc_isPFlag_Result( int quenum, int threadindex);

	//ygy :이임관련 플래그
	int AUTH_proc_isKPFlag( int quenum, int threadindex);
	int AUTH_proc_isKPFlag_Result( int quenum, int threadindex);

	//ygy : 클랜마크번호로 클랜 정보 갖어오기
	int AUTH_proc_ReadClanInfo( int quenum, int threadindex);
	int AUTH_proc_ReadClanInfo_Result( int quenum, int threadindex);

	//ygy : cldata 업데이트
	int AUTH_proc_Updatcldata( int quenum, int threadindex);
	int AUTH_proc_Updatcldata_Result( int quenum, int threadindex);

	//ygy : notice
	int AUTH_proc_ReadNotice( int quenum, int threadindex);
	int AUTH_proc_ReadNotice_Result( int quenum, int threadindex);

	//이임
	int AUTH_proc_LeaveClan( int quenum, int threadindex);
	int AUTH_proc_LeaveClan_Result( int quenum, int threadindex);

	//부클랜장 임명
	int AUTH_proc_AppointSubChip( int quenum, int threadindex);
	int AUTH_proc_AppointSubChip_Result( int quenum, int threadindex);

	//부클랜장 해임
	int AUTH_proc_ReleaseSubChip( int quenum, int threadindex);
	int AUTH_proc_ReleaseSubChip_Result( int quenum, int threadindex);

	//wav파일 가져오기
	int AUTH_proc_GetWavFile( int quenum, int threadindex);
	int AUTH_proc_GetWavFile_Result( int quenum, int threadindex);



	//WebDB에 접속해서 할일을 지시하는 지시함수들.(유저들에의해 설정되어짐)
	int isClanMember(char *ClanZang_id, char* gserver,char* ClanZang_ChaName);
	//클랜멤버로 가입시킨다.
	//int joinClanMember(char *clanName, char *memid, char *memCharid);
	//int joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName,char* ClanName,char* ClanWon,char* ClanWon_ID);
	int joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName,char* ClanName,char* ClanWon,char* ClanWon_ID,int level,DWORD chtype,int joinlevel,char *chipflag);

	int make_Clan(char *ClanZang_ID, char* gserver,char* ClanZang_ChaName,char* ClanName,char *explanation,DWORD chtype,int level);
	int ReadClan(char *ClanZang_ID,char* gserver,char* ClanZang_ChaName);			//클렌데이타를 읽는다.
	//int BreakUP_Clan(char *clanName);		//클랜을 해체한다.
	int BreakUP_Clan(char *ClanZang_ID,char *gserver,char *ClanZang_ChaName, char *ClanName);		//클랜을 해체한다.
	int Banishiment(char *ClanZang_ID,char *gserver,char *ClanZang_ChaName,char *ClanName, char *ClanWon);
	int Warhouse_right(char *clanName, char *right_str);
	int updateFlag(char *clanName);

	//클랜마크읽기
	int MarkREAD(char *clanname,char *mark);
	//다른 클랜 마크 읽어오기
	int MarkREAD2(char *clanname,char *mark);


	int Secession(char* clanzang,char* gserver,char* SecessionID,char* clname);
	//ygy :초기 화면 관련 플래그
	int isPFlag(char *userid, char *clName, char *chName,char *gserver, char *PFlag, char *Gubun);

	//ygy :이임 관련 플래그
	int isKPFlag(char *userid, char *clName, char *chName,char *gserver, char *PFlag, char *Gubun);

	//ygy
	//isCheckClanJang 관련된 계정이 클랜장으로 등록되어 있는지 체크
	int isCheckClanJang(char *ClanZang_ID, char *gserver);

	//ygy : 클랜이름이 중복이 되었는지 체크
	int isCheckClanName(char *ClanName,char *gserver);
	//ygy : 클랜마크번호로 클랜 정보 갖어오기
	int ReadClanInfo(char *clanNum,CLANINFO *ci);

	//ygy : 업데이트 cldata
	int Updatcldata(char *id, char *gserver, char *chaname);
	//특정 캐릭터에 대한 경고문
	int ReadNotice(char *userid,char *chaname,char *gserver);

	//이임
	int LeaveClan(char *clanname,char *chaname,char *gserver);

	//서버에서 웨이브파일 가져오기
	int	GetWavFile(char* FileName);

	int AppointSubChip(char* userid,char* chaname,char* clanname,char *gserver,char* clanwon);//부클랜장 임명
	int ReleaseSubChip(char* userid,char* chaname,char* clanname,char *gserver,char* clanwon); //부 클랜장 해임



//sod 셋팅
int sod2INFOindex(char *UserId, char* CharName,char* GServer, int Index);

int AUTH_proc_sodindex( int quenum, int threadindex);
int AUTH_proc_sodindex_Result( int quenum, int threadindex);







	int start_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address);
	int end_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address);
};



extern int sod2INFOindex(char *UserId, char* CharName,char* GServer , int Index);
extern BOOL bip_port_error;

#undef EXTERN
#ifdef __AUTH_CPP__
	#define EXTERN
#else
	#define EXTERN extern
#endif

EXTERN WebDB_Thread WebDB;






void web_DB_start();		//게임 시작에서 셋팅
void web_DB_main();			//web db를 사용하는 클랜 메뉴에서만 불리워짐.
void web_DB_end();			//게임 끝에서 셋팅
