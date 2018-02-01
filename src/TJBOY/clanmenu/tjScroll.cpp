//====================================================================
//ktj : runmap3d.suo파일때문에 세이브가안되는경우가 있으므로 그럴때는 그 파일을 지울것
//====================================================================
//sinMain.cpp, sinInterFace.cpp에서 운영됨
#define TJSCROLL_CPP

#include "tjScroll.h"

void fd2( char *fmt, ...);



/*==================================================================================
//
// 클랜메뉴																	   start
//
==================================================================================*/

extern int TJwheel; //ktj : 휠데이타(tjclan.cpp)

//인자값 : 휠값
//사용했으면 1 사용안했으면 0
int TJBscrollWheel(int wheel)		//사용중:1  미사용중 0
{
	void fd2( char *fmt, ...);
	//fd2( "TJBscrollWheel 00 " );


	if(wheel != 0) {			//ktj : wheel>0 휠 앞으로 굴리기  wheel<0 휠 뒤로 굴리기
		if(tscr.lifef || tscr_CL.lifef ||tscr_Guide.lifef) {
			TJwheel = wheel;


			//fd2( "TJBscrollWheel 11  " );

			return 1;
		}
	}

	//fd2( "TJBscrollWheel 22  " );
	return 0;
}

void TJBscrollWheelClear()		//hoparty.cpp 제외한 기타함수에 사용하기
{
	TJwheel = 0;
	tscr.lifef = 0;

}

void TJBscrollWheelClear_ChatL()		//hoparty.cpp에 사용키위한함수
{
	TJwheel = 0;
	tscr_CL.lifef = 0;
	void chatList_Main_CHATLIST_END();
	chatList_Main_CHATLIST_END();
}

void TJBscrollWheelClear_Guide()
{
	TJwheel = 0;
	tscr_Guide.lifef = 0;
}

tSCROLL::tSCROLL()
{
}

tSCROLL::~tSCROLL()
{
}

//스크롤의 life판정
void tSCROLL::Init(int flag)
{
	lifef= flag;
}


//t, b:스크롤의 top, bottom,    scrLineSu:스크롤할 라인의 총길이    viewLineSu: 한화면에 보이는라인의 갯수
void tSCROLL::Init(int t, int b, int scrLineSu, int ViewLineSu)
{
	top = t; 
	bot = b;
	allLineSu = scrLineSu;
	viewLineSu = ViewLineSu;
	
	int scrLen = bot-top;					//라인 총길이
	step   = scrLen / (scrLineSu+1);		//한개의 라인이 필요한 스텝

	lifef = 1;
}

int tSCROLL::topScrollLineNum(int point)
{
	if(lifef == 0) return -1;

	int curP = point - top;					//현재 스크롤라인안의 위치
	int currentScrllLineNum = curP/step;	//스크롤라인한개당의 위치로 나눠준다.
	if(currentScrllLineNum > allLineSu )
		currentScrllLineNum = allLineSu;


	//맨아래스크롤 부분이 위로 올라가지 않게 막는다.
	int i = currentScrllLineNum + viewLineSu;
	if(i>allLineSu) {
		currentScrllLineNum  = allLineSu-viewLineSu;
	}
	
	return currentScrllLineNum;			//현재 화면에 나올 맨위의 라인번호리턴(좀더 수정해야함)
}



int tSCROLL::ret_WHEELpoint(int wheelN, int point)
{
	if(lifef == 0) return point;

	if(wheelN<0) {				//아래로 돌리기
		point += step;
		if( (bot-9)<point )
			point = bot-9;
	}

	if(wheelN>0) {				//앞으로 돌리기
		point -= step;

		if(top>point )
			point = top;
	}

	return point;			//휠움직인만큼의 포인트리턴해줌
}



//void aa333()
//{
	/*
	tscr.Init(0, 100, 10, 10);
	int n =  tscr.topScrollLineNum(205);
	n =  tscr.topScrollLineNum(6);
	n =  tscr.topScrollLineNum(7);
	n =  tscr.topScrollLineNum(8);
	n =  tscr.topScrollLineNum(9);
	n =  tscr.topScrollLineNum(10);
	n =  tscr.topScrollLineNum(11);
	n =  tscr.topScrollLineNum(12);

	n =  tscr.topScrollLineNum(50);
	n =  tscr.topScrollLineNum(61);
	n =  tscr.topScrollLineNum(70);
	*/
//}

