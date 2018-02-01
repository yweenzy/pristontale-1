
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
