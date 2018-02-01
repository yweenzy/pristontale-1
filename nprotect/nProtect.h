class nP
{
public:

	nP();
	~nP();

	int rn;			// 리턴값
	int temp;
	int result;		// nProtect실행시 진단값을 알려준다
	char nperrcode[10];		// nProtect 실행시 진단값을 넣어주는 임시 버퍼
	HINSTANCE m_hInstDll;	// DLL라이브러리의 인스턴스

	char test[6][20];

	bool (*pFunc_npchk)(char*);
	int (*pFunc_npkill)(char*);
	
	typedef BOOL(MYCHECKCRC)(char *);
	MYCHECKCRC *pCheckCRC;

public:

	int NProtectCheck(void);
	int NProtectRun(void);
	int NProtectFree(void);
	int findNPMON();
	BOOL CheckCRC(char * FilePath);
	void Init();

// nProtect GameHack SDK //
	bool m_bStart;
	bool IsNT;
	
	HINSTANCE hInstanceNPFSICE; // 소프트 아이스 검색시 사용되는 DLL Handle
	HINSTANCE hInstanceNPFGM; // GameHack시 사용되는 DLL Handle

	BOOL NPGetWindowsVersion();
	BOOL NPMyLoadLibraryNPFGM();
	BOOL NPEnterProtect();
	BOOL NPReleaseProtect();
	BOOL NPFindSICEProtect();
	void NPFreeLib();
};

extern class nP nPro;
