
extern DWORD	dwExeCheckSum;		//실행파일 체크섬
extern char		szProcessPath[256];	//실행파일 경로

//크랙을 찾아서 이름을 반환한다 (오프라인 )
char *FindCracker();
//크랙을 찾아 이름 반환 ( 온라인 )
char *FindCracker( TRANS_FIND_CRACKER *lpTransFindCrack );
//크랙을 다시 찾는다 ( 온라인 )
char *FindCrackCont();
//윈도우 포커스를 감시
HWND WinFocusCrack();
// 실행중인 프로세스의 목록을 구한다.
int CheckCrackProcess( int Flag=0 );

//해당 모듈을 검사하여 첵크섬 반환
DWORD	GetModuleCheckSum( char *szModule );

int	CheckDLL_Module();		//프로세스 모듈 검사


//nProtect 실행
int Start_nProtect( int deMode );
//nProtect HWND
int SetHwnd_nProtect( HWND hWnd );
//nProtect 제거
int Remove_nProtect();
//nProtect 확인
int	Check_nProtect();
//nProtect 확인
int Check_nProtectDLL();

//사용자 ID 정보 게임가드 통보
int	npSetUserID( char *szID );

//게임가드 서버측 첵크
int npAuth( DWORD dwAuthValue );

// 게임에서 NPMON.EXE로 보내주는 자동종료 메시지 (게임종료시 적용)
#define WM_NPROTECT_FORCEEXIT		(WM_USER + 10010)

//////////////////////Npmon.exe가 게임으로 보내는 메시지/////////////////////////////////
#define WM_NPROTECT_EXIT_TWO		(WM_USER + 10001)

//- 게임중 스피드핵을 사용할 경우 (구버젼(SPEEDER)의 버그 진단가능)
//게임의 캡션명을 참조하여 윈도우 메시지 전송. (npmon 4.10.0.35 부터 적용됨)
#define WM_NPROTECT_SPEEDHACK		(WM_USER + 10011) //사용자에게 보여지는 메시지 : 스피드핵이 발견되었습니다.
#define WM_NPROTECT_SH_ERROR		(WM_USER + 10012) //관리자 계정으로 로그인하여 게임을 실행하시기 바랍니다.

//- 게임중 소프트 아이스를 사용할 경우
//게임의 캡션명을 참조하여 윈도우 메시지 전송. (npmon 4.10.0.35 부터 적용됨)
#define WM_NPROTECT_SOFTICE			(WM_USER + 10111) //소프트 아이스가 발견 되었습니다.
///////////////////////////////////////////////////////////////////////////////////////////////






