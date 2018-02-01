#define OTHER_PLAYER_MAX		1024
#define OTHER_PLAYER_MASK		1023


#define	SHADOW_PAT_MAX		4

//######################################################################################
//작 성 자 : 오 영 석
#define	ICE_FOOT_PAT_MAX		2
extern	smPAT3D *PatIceFoot[ ICE_FOOT_PAT_MAX ];
//######################################################################################

//월드시분 의 실제의 시간
#define	GAME_WORLDTIME_MIN		800
//#define	GAME_WORLDTIME_MIN		200

//게임내 에서의 밤낮 변화 시간
#define GAME_HOUR_DAY			4
#define GAME_HOUR_GLOW			22
#define GAME_HOUR_DARKNESS		23
#define GAME_HOUR_NIGHT			24


extern DWORD	dwBattleTime;				//최근 전투 시간
extern DWORD	dwBattleQuitTime;			//전투중 종료 하려 할때
extern DWORD	dwCloseBoxTime;				//창 종료 하려 할때

extern int GameMode;						//게임모드 상태

extern int	PkMode;							//PK모드
extern int	DispApp_SkillPoint ;			//설정된 시간적용 스킬 포인트

extern int		Moving_DblClick;			//마우스 이동 첵크 더블 클릭
extern POINT3D	MousePos_DblClick;

extern POINT3D	TracePos_DblClick;
extern int TraceMode_DblClick;


extern	int	ActionGameMode;				//액션게임모드

extern smPAT3D  *PatShadow[SHADOW_PAT_MAX];			//그림자
extern smPAT3D  *PatArrow;							//화살
extern smPAT3D	*PatEffectShield;					//방패 이펙트
extern smPAT3D	*PatSparkShield;					//스파크쉴드 이펙트
extern smPAT3D	*PatDivineShield;					//디바인인할레이션
extern smPAT3D	*PatGodlyShield;					//가들리쉴드
extern smPAT3D	*PatCrown;							//블레스캐슬 왕관


extern smCHAR	*lpCurPlayer;							//주인공
extern smCHAR	chrOtherPlayer[OTHER_PLAYER_MAX];
extern char PlayerName[64];

extern	int	RecordFailCount;				//저장 실피 카운터


//무대 세트 클래스
extern smSTAGE3D *smStage;
extern int PlayCounter;
extern smSTAGE3D *smGameStage[2];
extern smSTAGE3D *smGameStageWall[2];
extern DWORD	dwPlayTime;					//현재의 윈도우 시간 ( 플레이 용 )
extern DWORD	dwMemError;					//메모리 에러 확인 코드

extern char szGameStageName[2][64];			//게임 배경 이름

extern int	BackColor_R ;				//배경색 R
extern int	BackColor_G ;				//배경색 G
extern int	BackColor_B ;				//배경색 B

extern int	BackColor_mR;				//배경색 변경값 R
extern int	BackColor_mG;				//배경색 변경값 G
extern int	BackColor_mB;				//배경색 변경값 B

extern int	DarkLevel_Fix;				//어둠 값 고정

extern int DarkLevel;					//어둠 값
extern int DarkLightRange;			//어두울때 조명 범위
extern DWORD	dwGameWorldTime;	//게임의 월드시간
extern DWORD	dwGameHour;			//게임의 시
extern DWORD	dwGameMin;			//게임의 분
extern DWORD	dwGameTimeOffset;

extern DWORD	UseEtherCoreCode;	//에티르 코어 사용


extern int MatBlood[2];			//피튀기는 메트리얼

extern int MatEnergyBox[2];		//에너지 그래프

extern	int WeatherMode;		//날씨

extern int		MsTraceCount;
extern int		MsTraceMode;

extern	RECT	MsSelRect;
extern	POINT	MsSelPos;

extern	int		SelMouseButton;			//사용 선택된 마우스

extern  int		AttCancel;						//공격 취소
extern  int		AttAutoCont;					//자동 공격


extern  smCHAR	*lpCharSelPlayer;
extern	smCHAR	*lpCharMsTrace;			//이동 목표 캐릭터

extern	scITEM	*lpSelItem;
extern	scITEM	*lpMsTraceItem;

extern	int		RestartPlayCount;			//재시작 무적 시작 카운트


//관리자 캐릭터 모드시 상대방에 데이타 송출 금지
extern int AdminCharDisable;

#define DISP_ITEM_MAX	128
extern scITEM	scItems[ DISP_ITEM_MAX ];			//ITEM


//공격 받았을때 회피 카운터
extern int	Record_BlockCount;
extern int	Record_DefenceCount;
extern int	Record_RecvDamageCount;
extern int  Record_TotalRecvDamageCount;

extern DWORD SkillFalconPoint;					//팔콘 스킬 포인트 저장용


//오토 마우스 감지용
extern	DWORD	AutoMouse_LastCheckTime;
extern	DWORD	AutoMouse_StartCheckTime;
extern	int		AutoMouse_WM_Count;
extern	int 	AutoMouse_Distance;
extern	int		AutoMouse_Attack_Count;


//공격 설정
int TraceAttackPlay();
//공격 취소
int CancelAttack();
//마우스로 찍은 플레이어로의 각도를 구해준다
int GetMouseSelAngle( );
//2명의 플레이어의 각도를 구해준다
int GetCharAngle( smCHAR *lpChar1 , smCHAR *lpChar2 );
//갑옷 모양 바꾸기
int SetChrArmor( smCHAR *lpChar , int ItemNum );

//배경 로더 초기화
void InitStageLoader();

void InitStage();
void CloseStage();
int DisplayStage(int x , int y, int z, int angX, int angY, int angZ );



int InitPat3D();
int ClosePat3D();
int PlayObj3D( smOBJ3D *obj3d , int x, int y, int z, int ax, int ay, int az );
int PlayPat3D();
int DrawPat3D_Alpha();
int DrawPat3D( int x, int y, int z, int ax, int ay, int az );
int DrawPat2D( int x, int y, int z, int ax, int ay, int az );

//그림자 그리기
int DrawPatShadow(int x, int y, int z, int ax, int ay, int az );

int InitBackGround();
int CloseBackGround();
int DrawBG( int x, int y, int z, int ax, int ay, int az );

int ChangeBG( int BgNum );				//배경 변경
int BGMain();							//배경 메인

//그리기 크리티컬 섹션
extern CRITICAL_SECTION	cDrawSection;

extern int SkipNextField;				//다음 필드로 넘어감
//관리자 캐릭터 모드
extern int AdminCharMode;

extern char *NpcSelectedName;			//선택된 NPC 이름

//파티 거래 신청 버튼 위치를 얻음
int GetPartyTradeButtonPos( int x, int y );
//파티 트레이드 신청 버트 클릭
int DisplayPartyTradeButton();

//데미지에 따른 경험치 상승
int	DamageExp( smCHAR *lpChar , int AttackDamage );

//배경을 읽어 온다
smSTAGE3D *LoadStage2( char *szStageFile );
//배경을 읽어 온다
smSTAGE3D *LoadStage( char *szStageFile );


// WINMAIN 선언 함수
extern POINT3D TraceCameraPosi;
extern POINT3D TraceTargetPosi;
extern HFONT	hFont;
extern int QuitSave;
extern int	CameraInvRot;					//카메라 회전 방향
extern int	CameraSight;					//카메라 시야 조절

extern int	DebugPlayer;				//디버깅 카메라 플레이어

extern int DispEachMode;
extern int		EachTradeButton;
extern int		EachTradeButtonMode;
extern RECT		RectTradeButton;
extern smCHAR	chrEachPlayer;
extern smCHAR	*chrEachMaster;

extern char szExitInfo_URL[128];

int SetIME_Mode( BOOL mode );

int DrawEachPlayer( float fx , float fy , int SizeMode );	//확대 캐릭터 그리기
int EachPlayerMain();					//확대 캐릭터 메인
int CloseEachPlayer();					//확대 캐릭터 닫기
int OpenEachPlayer( smCHAR *lpChar );	//확대 캐릭터 오픈

int GetPlayMouseAngle();				//마우스에 따른 방향값 구하기
int SetMousePlay( int flag );			//마우스 움직임에 따른 게임 플레이 설정


void SetPlayerBodyPattern( char *szBodyFile );		//몸 파일 바꾸기
void SetPlayerPattern( char *szFile );				//모델 바꾸기

//2바이트 코드 확인
int CheckCode_2Byte( char *Str );		//코드 확인

int SetPartyPosion( smTRANS_COMMAND *lpTransCommand );	//동료 회복 설정


//퀘스트 시작
int	StartQuest_Code( DWORD wCode );
//퀘스트 완료
int EndQuest_Code( DWORD wCode );
//퀘스트상태 보드에 설정
int SetQuestBoard();

//클라이언트 로그 파일 기록
int Record_ClinetLogFile( char *szMessage );

extern int DisplayDebug;				//디버깅 정보 표시
extern int LastAttackDamage;			//최근 공격 데미지
extern int ImeChatLen;					//IME 관련 문자길이
extern	POINT	ImePositon;				//IME 위치 저장

//신바람 마스크
#define	sinITEM_WEAPON	0x01000000
#define	sinITEM_DEFENCE	0x02000000
#define	sinITEM_MASK1	0xFF000000
#define	sinITEM_MASK2	0xFFFF0000
#define	sinITEM_MASK3	0x0000FFFF

//게임 종료 ( playsub.cpp )
int QuitGame();
int SetIME_Mode( BOOL mode );

//코멘드 라인 ( winmain.cpp )
extern char szCmdLine[128];
extern int QuitSave;
extern DWORD	dwLastMouseMoveTime;
extern DWORD	dwLastCharMoveTime;

//디버그 플랙 백업
extern DWORD	dwDebugBack;
extern DWORD	dwDebugXor;

extern int	PlayTimerMax;			//한 프레임이 걸린 시간 첵크

extern DWORD dwM_BlurTime;


//윙을 사용한 워프 ( Field.cpp )
int WingWarpGate_Field( int dwFieldCode );


//////////////// 박철호 동영상 플레이어 /////////////
extern int ParkPlayMode;		//-플립금지 0-일반 +슬립시간(최대 1000)
extern int ParkPlaying;			//동영상 플레이중

int Init_ParkPlayer();			//플레이어 초기화
int Stop_ParkPlayer();			//플레이어 중지
int Play_ParkPlayer( char *szPath , int x, int y, int w, int h , int PlayMode );		//플레이어 재생

