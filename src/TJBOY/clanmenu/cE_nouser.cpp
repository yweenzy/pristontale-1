
#define CE_NOUSER_CPP
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>


#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우

	#include "sinbaram\\SinLinkHeader.h"
	#include "HoBaram\\HoLinkHeader.h"
	#include "Language\\language.h"
	#include "HoBaram\\HoTextFile.h"
#endif

#include "tjclan.h"
#include "cE_nouser.h"


//*****************************************************************************
CLANEntity_nouser::CLANEntity_nouser()
{

}

CLANEntity_nouser::~CLANEntity_nouser()
{

}


//*****************************************************************************
int CLANEntity_nouser::Init(int Life)
{
	life = Life;
	return 1;
}

int CLANEntity_nouser::Clear()
{
	return 1;
}


//*****************************************************************************
void CLANEntity_nouser::Main()
{
	if(life ==0) return;


}



//*****************************************************************************
void CLANEntity_nouser::RenderMain()
{
	if(life ==0) return;

}




//***************************************************************************************
void CLANEntity_nouser::menuInit(int num)
{
	int bx = 0, by =0;	
	
	switch(num){
		case CLAN_MAKE_is:
			menuSu = 2;			

			#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우
			bx = 32;
			by = 16;
			#else			
			bx = 32;
			by = 16;
			#endif
			
			menuPos[0].left = BackStartPos.x + BUTTON1_X;//174;		//yes
			menuPos[0].top = BackStartPos.y + + BUTTON1_Y;//353;
			menuPos[0].right = menuPos[0].left + bx;
			menuPos[0].bottom = menuPos[0].top + by;



			#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우
			bx = 32;
			by = 16;
			#else			
			bx = 32;
			by = 16;
			#endif

			menuPos[1].left = BackStartPos.x + BUTTON2_X;//254		//no
			menuPos[1].top = BackStartPos.y + BUTTON2_Y; //353
			menuPos[1].right = menuPos[1].left+ bx;
			menuPos[1].bottom = menuPos[1].top + by;

			//텍스트 출력 위치
			menuPos[2].left = BackStartPos.x + 55;
			menuPos[2].top = BackStartPos.y + 70;
			menuPos[2].right = menuPos[2].left+280;
			menuPos[2].bottom = menuPos[2].top+250;

			//yes, no 테두리 박스
			#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우
			bx = 68;
			by = 27;
			#else			
			bx = 68;
			by = 27;
			#endif

			menuPos[3].left = BackStartPos.x + BUTTON1_BOX_X;//166;		//yes 테두리 박스
			menuPos[3].top = BackStartPos.y + BUTTON1_BOX_Y;//348
			menuPos[3].right = menuPos[3].left + bx;
			menuPos[3].bottom = menuPos[3].top + by;

			#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우
			bx = 68;
			by = 27;
			#else			
			bx = 68;
			by = 27;
			#endif
			menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;	//246	//no 테두리 박스
			menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;//348
			menuPos[4].right = menuPos[4].left + bx;
			menuPos[4].bottom = menuPos[4].top + by;

			break;
		case CLAN_MONEY_is:
			menuSu = 2;			
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 32;
			by = 16;
			#else
			
			bx = 32;
			by = 16;
			#endif
			
			menuPos[0].left = BackStartPos.x + BUTTON1_X;		//yes
			menuPos[0].top = BackStartPos.y + BUTTON1_Y;
			menuPos[0].right = menuPos[0].left + bx;
			menuPos[0].bottom = menuPos[0].top + by;



			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 32;
			by = 16;
			#else
			
			bx = 32;
			by = 16;
			#endif

			menuPos[1].left = BackStartPos.x + BUTTON2_X;		//no
			menuPos[1].top = BackStartPos.y + BUTTON2_Y;
			menuPos[1].right = menuPos[1].left+ bx;
			menuPos[1].bottom = menuPos[1].top + by;

			//텍스트 출력 위치
			menuPos[2].left = BackStartPos.x + 65;
			menuPos[2].top =  BackStartPos.y + 80;
			menuPos[2].right = menuPos[2].left+280;
			menuPos[2].bottom = menuPos[2].top+250;

			//yes, no 테두리 박스
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 68;
			by = 27;
			#else
			bx = 68;
			by = 27;
			#endif

			menuPos[3].left = BackStartPos.x + BUTTON1_BOX_X;		//yes 테두리 박스
			menuPos[3].top = BackStartPos.y + BUTTON1_BOX_Y;
			menuPos[3].right = menuPos[3].left + bx;
			menuPos[3].bottom = menuPos[3].top + by;

			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 68;
			by = 27;
			#else
			bx = 68;
			by = 27;
			#endif

			menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;		//no 테두리 박스
			menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;
			menuPos[4].right = menuPos[4].left + bx;
			menuPos[4].bottom = menuPos[4].top + by;

			break;
		case CLAN_NAME_is: //클랜 명칭

			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			//ktj : 이름을 입력하기 위한 입력윈도, 입력버퍼 셋팅.
			if(hFocusWnd==0) {
				ZeroMemory(cldata.name, sizeof(cldata.name));
				hFocusWnd = hTextWnd;
				SetWindowText( hFocusWnd , "" );
			}
			#endif

			menuSu = 2;
			
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 32;
			by = 16;
			#else
			bx = 32;
			by = 16;
			#endif

			menuPos[0].left = BackStartPos.x +BUTTON3_X;		//확인
			menuPos[0].top = BackStartPos.y +BUTTON3_Y;
			menuPos[0].right = menuPos[0].left + bx;
			menuPos[0].bottom = menuPos[0].top + by;


		/*  #ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 32;
			by = 16;
			#else
			GetObject(hCancel_Gray,sizeof(BITMAP),&bit);
			bx = 32;
			by = 16;
			#endif

			menuPos[1].left = BackStartPos.x +BUTTON2_X;		//취소
			menuPos[1].top = BackStartPos.y +BUTTON2_Y;
			menuPos[1].right = menuPos[1].left+ bx;
			menuPos[1].bottom = menuPos[1].top + by;
			*/

			//텍스트 출력 위치
			menuPos[2].left	= BackStartPos.x + 55;
			menuPos[2].top		= BackStartPos.y + 70;
			menuPos[2].right	=menuPos[2].left + 190;
			menuPos[2].bottom	=menuPos[2].top +	180;

			//확인, 취소 테두리 박스
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 68;
			by = 27;
			#else
			bx = 68;
			by = 27;
			#endif

			menuPos[3].left = BackStartPos.x + BUTTON3_BOX_X;		//확인 테두리 박스
			menuPos[3].top = BackStartPos.y + BUTTON3_BOX_Y;
			menuPos[3].right = menuPos[3].left + bx;
			menuPos[3].bottom = menuPos[3].top + by;

		/*	#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 68;
			by = 27;
			#else
			GetObject(hButton_Box,sizeof(BITMAP),&bit);
			bx = bit.bmWidth;
			by = bit.bmHeight;
			#endif

			menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;		//취소 테두리 박스
			menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;
			menuPos[4].right = menuPos[4].left + bx;
			menuPos[4].bottom = menuPos[4].top + by;
		*/	
			
			break;
		case CLAN_NONAME:
			menuSu = 3;			
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 32;
			by = 16;
			#else

			bx = 32;
			by = 16;
			#endif
			menuPos[0].left = BackStartPos.x + BUTTON3_X;		//확인
			menuPos[0].top = BackStartPos.y + BUTTON3_Y;
			menuPos[0].right = menuPos[0].left + bx;
			menuPos[0].bottom = menuPos[0].top + by;

			//텍스트 출력 위치
			menuPos[1].left = BackStartPos.x + 55;
			menuPos[1].top = BackStartPos.y + 70;

			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 64;
			by = 16;
			#else
			bx = 64;
			by = 16;
			#endif
			menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;		//확인
			menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
			menuPos[2].right = menuPos[2].left + bx;
			menuPos[2].bottom = menuPos[2].top + by;		
			break;
		case CLAN_NAME_BEING:
			menuSu = 3;			
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 32;
			by = 16;
			#else

			bx = 32;
			by = 16;
			#endif
			menuPos[0].left = BackStartPos.x + BUTTON3_X;		//확인
			menuPos[0].top = BackStartPos.y + BUTTON3_Y;
			menuPos[0].right = menuPos[0].left + bx;
			menuPos[0].bottom = menuPos[0].top + by;

			//텍스트 출력 위치
			menuPos[1].left = BackStartPos.x + 55;
			menuPos[1].top = BackStartPos.y + 70;

			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 64;
			by = 16;
			#else
			bx = 64;
			by = 16;
			#endif
			menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;		//확인
			menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
			menuPos[2].right = menuPos[2].left + bx;
			menuPos[2].bottom = menuPos[2].top + by;		
			break;
		case CLAN_MARK_expl: //클랜 마크 확인
			menuSu = 1;
			
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 32;
			by = 16;
			#else
			bx = 32;
			by = 16;
			#endif
			menuPos[0].left = BackStartPos.x +BUTTON3_X;		//확인
			menuPos[0].top = BackStartPos.y +BUTTON3_Y;
			menuPos[0].right = menuPos[0].left + bx;
			menuPos[0].bottom = menuPos[0].top + by;

			//텍스트 출력 위치
			menuPos[1].left	= BackStartPos.x + 55;
			menuPos[1].top		= BackStartPos.y + 70;
			menuPos[1].right	=menuPos[1].left + 190;
			menuPos[1].bottom	=menuPos[1].top +180;

			//확인 테두리
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 68;
			by = 27;
			#else
			bx = 68;
			by = 27;
			#endif

			menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;		//확인 테두리 박스
			menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
			menuPos[2].right = menuPos[2].left + bx;
			menuPos[2].bottom = menuPos[2].top + by;
			break;
		case CLAN_INSPECTION_expl:		//클랜심사
			menuSu = 5;
			
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 32;
			by = 16;
			#else

			bx = 32;
			by = 16;
			#endif
			menuPos[0].left = BackStartPos.x +BUTTON1_X;		//확인
			menuPos[0].top = BackStartPos.y +BUTTON1_Y;
			menuPos[0].right = menuPos[0].left + bx;
			menuPos[0].bottom = menuPos[0].top + by;

			//텍스트 출력 위치
			menuPos[1].left	= BackStartPos.x + 55;
			menuPos[1].top		= BackStartPos.y + 70;
			menuPos[1].right	=menuPos[1].left + 260;
			menuPos[1].bottom	=menuPos[1].top + 180;

			//확인 테두리
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 68;
			by = 27;
			#else
			bx = 68;
			by = 27;
			#endif

			menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리 박스
			menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
			menuPos[2].right = menuPos[2].left + bx;
			menuPos[2].bottom = menuPos[2].top + by;

			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 32;
			by = 16;
			#else

			bx = 32;
			by = 16;
			#endif
			menuPos[3].left = BackStartPos.x +BUTTON2_X;		//취소
			menuPos[3].top = BackStartPos.y +BUTTON2_Y;
			menuPos[3].right = menuPos[3].left + bx;
			menuPos[3].bottom = menuPos[3].top + by;

			//취소 테두리
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 68;
			by = 27;
			#else
			bx = 68;
			by = 27;
			#endif

			menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;		//취소 테두리 박스
			menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;
			menuPos[4].right = menuPos[4].left + bx;
			menuPos[4].bottom = menuPos[4].top + by;
			break;
		case CLAN_NotMake:				//클랜을 만들지 못한다는 메뉴
			menuSu = 3;
			
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 64;
			by = 64;
			#else
			bx = 64;
			by = 64;
			#endif
			menuPos[0].left = BackStartPos.x +BUTTON3_X;		//확인
			menuPos[0].top = BackStartPos.y +BUTTON3_Y;
			menuPos[0].right = menuPos[0].left + bx;
			menuPos[0].bottom = menuPos[0].top + by;

			//텍스트 출력 위치
			menuPos[1].left	= BackStartPos.x + 55;
			menuPos[1].top		= BackStartPos.y + 70;
			menuPos[1].right	=menuPos[1].left + 260;
			menuPos[1].bottom	=menuPos[1].top + 180;

			//확인 테두리
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 68;
			by = 27;
			#else
			bx = 68;
			by = 27;
			#endif

			menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;		//확인 테두리 박스
			menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
			menuPos[2].right = menuPos[2].left + bx;
			menuPos[2].bottom = menuPos[2].top + by;
			break;
		case CLAN_MAKE_FINISH:
			menuSu = 3;
			
			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 32;
			by = 16;
			#else

			bx = 32;
			by = 16;
			#endif
			menuPos[0].left = BackStartPos.x + BUTTON3_X;		//확인
			menuPos[0].top = BackStartPos.y + BUTTON3_Y;
			menuPos[0].right = menuPos[0].left + bx;
			menuPos[0].bottom = menuPos[0].top + by;

			//텍스트 출력 위치
			menuPos[1].left = BackStartPos.x + 55;
			menuPos[1].top = BackStartPos.y + 70;

			#ifdef USE_PROSTONTALE		//=========== 포리스턴소스인경우
			bx = 64;
			by = 16;
			#else
			bx = 64;
			by = 16;
			#endif
			menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;		//확인
			menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
			menuPos[2].right = menuPos[2].left + bx;
			menuPos[2].bottom = menuPos[2].top + by;		
			break;
		//======================= 클랜 만들기용 메뉴 ======================end//
			
	}
}





