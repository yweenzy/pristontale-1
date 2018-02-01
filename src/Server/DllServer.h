int InitLogSql();
int CloseLogSql();
int RecordLogSql( DWORD	dwRecCode , char *szIP , char *lpUserID , char *lpCharName  , char *szGPCode, int Race , int JobCode , INT64 Exp64 , DWORD dwLevel , DWORD dwMoney );
int RecordGameLogSql( DWORD	dwRecCode , char *szIP , char *lpUserID , char *lpCharName  , char *szGPCode, int JobCode , char *szGuid , int BlockTime );

#define		LOG_SQL_LOGIN			0
#define		LOG_SQL_NEWCHAR			1
#define		LOG_SQL_DELCHAR			2
#define		LOG_SQL_LOGOUT			3


#define		GAMELOG_SQL_LOGIN		0x100
#define		GAMELOG_SQL_LOGOUT		0x101

#define		GAMELOG_SQL_SOD			0x102
#define		GAMELOG_SQL_STARPOINT	0x104
#define		GAMELOG_SQL_GIVEMONEY	0x106
#define		GAMELOG_SQL_CLANMONEY	0x107
#define		GAMELOG_SQL_SIEGETAX	0x108
#define		GAMELOG_SQL_POLLRECORD	0x109

#define		GAMELOG_SQL_EVENTJOIN	0x110

#define		BILLING_SQL_LOGOUT		0x201
#define		BILLING_SQL_PCUSE		0x202
#define		BILLING_SQL_PC_SRESERV	0x203
#define		BILLING_SQL_PC_TIME		0x204
#define		BILLING_SQL_BILL_CHANGE	0x205
#define		BILLING_SQL_EVENT_LOGIN		0x206
#define		BILLING_SQL_EVENT_LOGOUT	0x207

#define		BILLING_DISPLAY			0x210


#define		BILLING_URS_EXPINED		0x400

#define		CLAN_USER_TICKET		0x801
#define		CLAN_INSERT_POINT		0x802
#define		CLAN_GET_MARKCODE		0x803

#define		EGT_GET_EXPGAMETIME		0x901

#define		LOAD_DLL_NONE			0
#define		LOAD_DLL_SQL			1
#define		LOAD_DLL_URS			2

extern		int UseDLL_Code;			//사용 DLL 코드
extern		int	UseDLL_Expined;			//빌링 Expined 사용

//extern HINSTANCE hLogSqlDLL;					// Handle to DLL
int	bSql_LogOn(char *lpszPID, char *lpszPWD, char *lpszIP, char *lpszGPCode, char *lpszDisuseDay, char *lpszUsePeriod, char *szGuid , char *lpszPCRNo , char *lpszGubunCode );
int	bSql_Logout(char *lpszPID, char *lpszCID, char *lpszIP, char *lpszGPCode, time_t DisuseDay, int UsePeriod, char *szGuid , int PCRNo);
int	bSql_EventLogon( rsPLAYINFO *lpPlayInfo );	//이벤트 과금
int	bSql_EventLogOut( rsPLAYINFO *lpPlayInfo );	//이벤트 로그아웃

//#ifdef _LANGUAGE_VEITNAM
int	bSql_GetExpGameTime( rsPLAYINFO *lpPlayInfo , int GamePlayTime );		//ExpGameTime 기록및 보기 (베트남)
//#endif

int	bSql_GetGPCode(char *GPCode, char *PG);
int	bSql_PCUse( rsPLAYINFO *lpPlayInfo );
int	bSql_PCSearchReserv( rsPLAYINFO *lpPlayInfo );		//과금 연장 확인
int	bSql_ChangeUserIdGpCodeGame( int PCRNo );	//과금 변경

int	bSql_PCRNoReservProduct( rsPLAYINFO *lpPlayInfo );	//PC방 추가 시간 표시
int	bSql_GetQueLogOut( char *szID );				//대기중인 큐에 해당 계정의 로그 아웃이 있는지 확인
int	bSql_SODRecord( rsPLAYINFO *lpPlayInfo , int Level , int SodScore , int SodKillCount , int SodTotalScore , int SodTotalSucessUser , int SodTotalUser , int SodCode );
int	bSql_StarPoint( rsPLAYINFO *lpPlayInfo , int StarPoint , int CashFlag );	//Star Point 기록및 보기
int	bSql_GiveMoney( rsPLAYINFO *lpPlayInfo , int Money );		//GiveMoney 기록
int	bSql_PollRecord( rsPLAYINFO *lpPlayInfo , int PollKind , int PollCount , BYTE *PollData );//Polling 기록및 보기
int	bSql_ClanMoney( rsPLAYINFO *lpPlayInfo , int Cash , int CashFlag , int Kind );	//SOD 공성 클랜 돈창고 
int	bClan_GetClanMarkCode( rsPLAYINFO *lpPlayInfo );								//클랜 마크 코드 구하기

int	bSql_EventJoin( rsPLAYINFO *lpPlayInfo );	//이벤트 참여
int	bSql_RecordCurrency();						//통화량과 세금 DB에 기록

int b_SqlGetLossCount();
int b_SqlGetQueSize();
int b_SqlGetQueProcessTime( DWORD *pTimeMax , DWORD *pAvgTime );

int	bUrs_LoginIP(char *lpszPID, char *lpszPWD, char *lpszIP );
int	bUrs_Expined( rsPLAYINFO *lpPlayInfo );

int	bSql_ServerDown();
int	bSql_ServerExit();



struct	_LogITEM {
	DWORD	dwCode;
	DWORD	dwINo[2];
};


//아이템 구조체
struct LogITEM {
	int 		size;			// 사용한 구조체의 크기
	char 		UserID[32];  		// 사용자 ID
	char 		CharName[24]; 		// 사용자 캐랙터 이름
	long 		IP; 			// 사용자 IP            <===== 추가
	int 		Flag;			// 아이템 정보
	int		ItemCount;		// 처리할 아이템 갯수
	_LogITEM	Item[32];		// 아이템 정보
};

//거래 아이템 처리 구조체
struct LogITEM_TRADE {
	int 		size;			// 사용한 구조체의 크기
	char 		UserID[32];  		// 사용자 ID
	char 		CharName[24]; 		// 사용자 캐랙터 이름
	long		IP;			// 사용자 IP         <========= 추가 
	int 		Flag;			// 아이템 정보

	char 		TUserID[32];		// 거래 아이디
	char 		TCharName[24];		// 거래 캐랙터 이름
	long 		TIP;			// 거래 IP           <========= 추가 
	int		Money;			// 거래한 금액
	int		ItemCount;		// 거래한 아이템 갯수
	_LogITEM 	Item[32];		// 아이템 정보
};


//아이템 구조체
struct LogGiftITEM {
	int 		size;		// 사용한 구조체의 크기
	char 		UserID[32];  	// 사용자 ID
	char 		CharName[24]; 	// 사용자 캐랙터 이름
	long 		IP; 		// 사용자 IP
	int 		Flag;		// 아이템 정보    (아이템교부13)
	long		GNo;		// 인증번호
	char 		TEL[16]; 	// 사용자 전화번호
	_LogITEM 	Gitem;		// 아이템 정보
};

/*
//아이템 구조체
struct LogITEM {
	int 		size;		// 사용한 구조체의 크기
	char 		UserID[32];  	// 사용자 ID
	char 		CharName[24]; 	// 사용자 캐랙터 이름
	int 		Flag;		// 아이템 정보
	int		ItemCount;	// 처리할 아이템 갯수
	_LogITEM	Item[32];	// 아이템 정보
};

//거래 아이템 처리 구조체
struct LogITEM_TRADE {
	int 		size;		// 사용한 구조체의 크기
	char 		UserID[32];  	// 사용자 ID
	char 		CharName[24]; 	// 사용자 캐랙터 이름
	int 		Flag;		// 아이템 정보

	char 		TUserID[32];  	// 사용자 ID
	char 		TCharName[24];	// 거래 캐랙터 이름
	int		Money;		// 거래한 금액
	int		ItemCount;	// 거래한 아이템 갯수
	_LogITEM 	Item[32];	// 아이템 정보
};
*/

struct	LogITEM_QUE {
	int		LogType;
	char	szBuff[sizeof(LogITEM_TRADE)];			//제일 큰 구조체 LogITEM_TRADE 크기
};

#define		LOG_ITEM_QUE_MAX		1024
#define		LOG_ITEM_QUE_MASK		1023


struct	LogEVENT_QUE {
	int		LogType;
	char	szBuff[512];
};
#define		LOG_EVENT_QUE_MAX		256
#define		LOG_EVENT_QUE_MASK		255

//아이템 로그 큐에 데이타 받음
int b_PopLogItemQue(LogITEM_QUE *lpLogItemQue);
//아이템 로그 큐에 데이타 넣음
int	b_PushLogItemQue( int type , int size,  void *lpLogItemData );

int b_SqlGetItemQueSize();			//아이템 로그 큐 크기
int b_SqlGetItemLossCount();		//아이템 로그 샐패 카운터


//이벤트 로그 큐에 데이타 넣음
int	b_PushLogEventQue( int type , int size, void *lpLogEventData );
//이벤트 로그 큐에 데이타 받음
int b_PopLogEventQue( LogEVENT_QUE *lpLogEventQue);
int b_SqlGetEventQueSize();
int b_SqlGetEventLossCount();


//(빌링) PC방 정액 IP송출
int	b_IPRecord(char *lpszServerName, struct JUNGIP *JungIP);
//(빌링) PC방 정량 IP송출
int	b_IPRecordTime(char *lpszServerName, struct JUNGIP *JungIP);

#define	JUNGIP_MAX	1024

struct JUNGIP {
    int	  IPCount;	// 처리할 IP 갯수
    DWORD IP[JUNGIP_MAX];	// IP 정보
};  


//클랜 티켓 발행
int bClan_GetTicket();
//클랜 티켓 처리
int	bClan_UserTicket( rsPLAYINFO *lpPlayInfo , int gubun );
//클랜 포인트 등록
int	bClan_InsertPoint( rsPLAYINFO *lpPlayInfo , int point );


/////////////////////////////// 중국판 인증 DLL ////////////////////////////////
/*
extern HINSTANCE hUsrLogInDLL;					// Handle to DLL
typedef int (*LPFNUSRLOGIN)(const char *ID,const char *PW, const char *IP );
typedef int (*LPFNUSRLOGOUT)(const char *ID, const char *IP );
typedef int (*LPFNUSRLOGOUT_IP_BLOCK)(const char *ID, const char *IP , const int min );
extern LPFNUSRLOGIN URSLoginIP;				// Function pointer
extern LPFNUSRLOGOUT URSLogoutIP;				// Function pointer
extern LPFNUSRLOGOUT_IP_BLOCK URSLogoutIPBlock;				// Function pointer
*/

//nSprite 중국 보안코드
DWORD nSprite_GetResult( DWORD nRecvNum );
int	nSprite_Init();			//nSprite 초기화

//////////////////////////////////////////////////////////////////////////////
