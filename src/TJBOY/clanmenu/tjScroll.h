


//스크롤 전용함수

class tSCROLL
{
public:
	tSCROLL();
	~tSCROLL();

	int lifef;
	int step;		//한개의 라인이 필요한 스텝
	int top, bot;
	int allLineSu;
	int viewLineSu;

	void Init(int flag);
	void Init(int t, int b, int menuSu, int ViewLineSu);
	int topScrollLineNum(int point);


	int ret_WHEELpoint(int wheelN, int point);
};

void TJBscrollWheelClear();

#ifdef TJSCROLL_CPP

	class tSCROLL tscr;
	class tSCROLL tscr_CL;		//채팅리스트용임에 주의할것
	class tSCROLL tscr_Guide;	//가이드 도움말용
	//class tSCROLL tscr_GuideContent; //가이드 내용

#else 

	extern class tSCROLL tscr;
	extern class tSCROLL tscr_CL;		//채팅리스트용임에 주의할것
	extern class tSCROLL tscr_Guide;	//가이드 도움말용
	//extern class tSCROLL tscr_GuideContent; //가이드 내용 

#endif

void TJBscrollWheelClear_Guide();
