class nP
{
public:

	nP();
	~nP();

	int rn;			// 리턴값
	int temp;
	int result;		// nProtect실행시 진단값을 알려준다
	char nperrcode[10];		// nProtect 실행시 진단값을 넣어주는 임시 버퍼
	//char *test;			// 화일명이 들어갈 임시 포인터 함수
	HINSTANCE m_hInstDll;	// DLL라이브러리의 인스턴스

	char test[6][20];

	bool (*pFunc_npchk)(char*);
	int (*pFunc_npkill)(char*);
	
	typedef BOOL(MYCHECKCRC)(char *);
	MYCHECKCRC *pCheckCRC;

public:

	int NProtectCheck(void);
	//int NProtectCheckMON(void);
	int NProtectRun(void);
	int NProtectFree(void);
	int findNPMON();
	BOOL CheckCRC(char * FilePath);
	void Init();

	

};

extern class nP nPro;
