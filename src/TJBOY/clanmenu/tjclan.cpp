//ktj : ºÎÅ¬·£ÀÇ ±ÇÀ¯°ü·Ã : netplay.cpp¿¡µµ ÀÖÀ½.

//====================================================================
//ktj : runmap3d.suoÆÄÀÏ¶§¹®¿¡ ¼¼ÀÌºê°¡¾ÈµÇ´Â°æ¿ì°¡ ÀÖÀ¸¹Ç·Î ±×·²¶§´Â ±× ÆÄÀÏÀ» Áö¿ï°Í
//====================================================================
//5.7 P4.28
//sinMain.cpp, sinInterFace.cpp¿¡¼­ ¿î¿µµÊ
#define TJCLAN_CPP

#include "tjclanDEF.h"


#ifdef USE_PROSTONTALE		//=========== ÇÁ¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì




#include "sinbaram\\SinLinkHeader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "Language\\language.h"
#include "HoBaram\\HoTextFile.h"

#include "tjclan.h"
#include "tjscroll.h"
#include "cE_Cmake.h"
#include "cE_chip.h"
#include "cE_user.h"
#include "cE_isclanmember.h"
#include "cE_report.h"
#include "cE_chatlist.h"
#include "cE_deletecha.h"
#include "cE_Cjoin.h"
#include "cE_CViewClanInfo.h"
#include "cE_Updatecldata.h"
#include "cE_Notice.h"

#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "Help.h"
#include "GuideHelp.h" 

#include "..\\ygy\\ygyheader.h"


//#include "NpcWav.h" //npc ¿þÀÌºê ¹Þ¾Æ¿À±â
//#include "Zip.h"


//#define USE_YAHEL		//¾ÆÀ£¼­¹ö¸¸ »ç¿ëÇÏ´Â°æ¿ì´Â ¿­¾îµÑ°Í


extern HWND hTextWnd;
extern HWND hFocusWnd;

extern char UserAccount[256];		//id°¡ µé¾îÀÖ´Â ¹öÆÛ
extern char	szConnServerName[16];	//Á¢¼ÓÇÑ ¼­¹öÀÌ¸§ÀÌ µé¾îÀÖ´Â ¹öÆÛ




#define MOUSE0() TJmb[0]


#else						//=========== Æ÷¸®½ºÅÏ¼Ò½º°¡ ¾Æ´Ñ°æ¿ì

#include <windows.h>
#include <stdio.h>
#include "tjclan.h"
#include "tjscroll.h"

#include "clan_Enti.h"
#include "cE_Cmake.h"
#include "cE_chip.h"
#include "cE_user.h"
#include "cE_isclanmember.h"
#include "cE_report.h"
#include "cE_chatlist.h"
#include "cE_deletecha.h"
#include "cE_CJoin.h"
#include "cE_CViewClanInfo.h"
#include "cE_Updatecldata.h"
#include "cE_Notice.h"

#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"





#define MAX_PARTY_MEMBER	6

#define PARTY_NONE		500
#define PARTY_START		1000
#define PARTY_PROCESS	2000
#define PARTY_END		3000

char UserAccount[256];		//id°¡ µé¾îÀÖ´Â ¹öÆÛ
char szConnServerName[16];	//Á¢¼ÓÇÑ ¼­¹öÀÌ¸§ÀÌ µé¾îÀÖ´Â ¹öÆÛ

extern int MouseButton[3] ;	//¸¶¿ì½º¹öÆ°´­¸²Ã½Å© : winmain.cpp¿¡ Á¤ÀÇÇÔ
extern int MouseDblClick ;		//tjclan.cpp


extern HWND    g_hwnd;
extern POINT	pCursorPos;
extern HINSTANCE g_hInst;


#define MOUSE0() MouseButton[0]


#endif


int ClanCharMove=0;	//Å¬·£¸Þ´ºÆÇ¾ÈÀÇ ¸¶¿ì½ºÀÇ ¿òÁ÷ÀÓ¿¡ Ä³¸¯ÅÍ°¡ ¿µÇâ¾øµµ·Ï ÇÑ´Ù.
int ClanCLCharMove=0;//Å¬·£Ã¤ÆÃ¸®½ºÆ®¸Þ´ºÆÇ¾ÈÀÇ ¸¶¿ì½ºÀÇ ¿òÁ÷ÀÓ¿¡ Ä³¸¯ÅÍ°¡ ¿µÇâ¾øµµ·Ï ÇÑ´Ù.


int  banisF[100];

//int TJwheel=0; //ktj : ÈÙµ¥ÀÌÅ¸
void fd2( char *fmt, ...);




//À¯±¤¿­ µµ¿ò¸» ¸¶¿ì½º ÀÌº¥Æ® °®¾î¿À±â====START
int GuideHelpButton[3] = {0,0,0}; //°¡ÀÌµå µµ¿ò¸»
int LevelpUpButton[3]= {0,0,0}; //·¹º§¾÷ µµ¿ò¸»
//END

BOOL bKeyDown = FALSE;
int nKeyDown = 0;
BOOL bKeyUp = FALSE;
int nKeyUp = 0;
BOOL bLButtonDown = FALSE;
BOOL bKeyPageDown = FALSE;
BOOL bKeyPageUp = FALSE;

BOOL IsDrawGuideHelp = FALSE; //°¡ÀÌµå µµ¿ò¸»ÀÌ ¶°Á®ÀÖÀ½

/*void GuidHelpMouse(int msg,WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_KEYUP:
		switch(wParam)
		{
		case VK_DOWN:
			GuideHelpButton[0] = FALSE; //°¡ÀÌµå µµ¿ò¸»
			bKeyUp = FALSE;
			bKeyDown = FALSE;
			break;
		case VK_UP:						
			bKeyDown = FALSE;
			bKeyUp = FALSE;
			GuideHelpButton[0] = FALSE; //°¡ÀÌµå µµ¿ò¸»			
			break;
		}		
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_DOWN:
			GuideHelpButton[0] = TRUE; //°¡ÀÌµå µµ¿ò¸»
			bKeyDown = TRUE;
			bKeyUp = FALSE;
			nKeyDown++;
			break;
		case VK_UP:						
			GuideHelpButton[0] = TRUE; //°¡ÀÌµå µµ¿ò¸»
			bKeyUp = TRUE;
			bKeyDown = FALSE;
			nKeyUp++;
			break;
		}		
		break;
	case WM_LBUTTONDOWN:		
		//À¯±¤¿­==============start
		bKeyDown = FALSE;
		bKeyUp = FALSE;
		GuideHelpButton[0] = TRUE; //°¡ÀÌµå µµ¿ò¸»
		LevelpUpButton[0]=TRUE; //·¹º§¾÷ µµ¿ò¸»
		//end
		break;
	case WM_LBUTTONUP:
		bKeyDown = FALSE;
		bKeyUp = FALSE;
		GuideHelpButton[0] = FALSE; //°¡ÀÌµå µµ¿ò¸»
		LevelpUpButton[0]=FALSE; //·¹º§¾÷ µµ¿ò¸»
		break;
	}
}
*/
void clan_Mouse(int msg,WPARAM wParam)
{
	switch(msg){
	//À¯±¤¿­ WM_KEYUPÃß°¡
	case WM_KEYUP:
		switch(wParam)
		{
		case VK_DOWN:
			GuideHelpButton[0] = FALSE; //°¡ÀÌµå µµ¿ò¸»
			bKeyUp = FALSE;
			bKeyDown = FALSE;
			break;
		case VK_UP:						
			bKeyDown = FALSE;
			bKeyUp = FALSE;
			GuideHelpButton[0] = FALSE; //°¡ÀÌµå µµ¿ò¸»			
			break;
		
		}		
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_DOWN:
			GuideHelpButton[0] = TRUE; //°¡ÀÌµå µµ¿ò¸»
			bKeyDown = TRUE;
			bKeyUp = FALSE;
			nKeyDown++;
			break;
		case VK_UP:						
			GuideHelpButton[0] = TRUE; //°¡ÀÌµå µµ¿ò¸»
			bKeyUp = TRUE;
			bKeyDown = FALSE;
			nKeyUp++;
			break;
		case VK_ESCAPE://escÅ°·Î µµ¿ò¸» ²ô±â
			g_GuideHelp.GuidHelpEnd();
			g_Help.HelpEnd();
			break;
		
		}		
		break;
	//==============END
	
	case WM_LBUTTONDOWN:
		TJmb2[0] = TJmb[0] = TRUE;
		//À¯±¤¿­==============start		
		bKeyDown = FALSE;
		bKeyUp = FALSE;		
		
		GuideHelpButton[0] = TRUE; //°¡ÀÌµå µµ¿ò¸»
		LevelpUpButton[0]=TRUE; //·¹º§¾÷ µµ¿ò¸»	

		//end
		break;

	case WM_LBUTTONUP:
		TJmb2[0] = TJmb[0] = FALSE;
		//À¯±¤¿­==============start
		bKeyDown = FALSE;
		bKeyUp = FALSE;
		bLButtonDown = FALSE;
		
		GuideHelpButton[0] = FALSE; //°¡ÀÌµå µµ¿ò¸»
		LevelpUpButton[0]=FALSE; //·¹º§¾÷ µµ¿ò¸»
		//==============END
		break;

	case WM_RBUTTONDOWN:
		TJmb2[1] = TJmb[1] = TRUE; //ktj
		break;

	case WM_RBUTTONUP:
		TJmb2[1] = TJmb[1] = FALSE; //ktj
		break;

	case WM_MBUTTONDOWN:
		TJmb2[2] = TJmb[2] = TRUE; //ktj
		break;

	case WM_MBUTTONUP:
		TJmb2[2] = TJmb[2] = FALSE; //ktj
		break;
	}
}









void ktj_imsi_clanMENU_Main()
{
	static cnt=0;
	cnt++;

	int mainchk;
	
	if(cnt<10) {
		mainchk = PARTY_START;
		
	}
	else {
		mainchk = PARTY_PROCESS;
	}

	

	Interface_clanmenu.Main(mainchk );
#ifdef VOICE_CHAT
	
	g_CtrlProcess.Main();

#endif
}

void ktj_imsi_clanMENU_Draw()
{
	if( cSinHelp.sinGetHelpShowFlag() && !IsDrawGuideHelp ) return;	// ¹«ÇÑ ÅÚ·¹Æ÷Æ® ÄÚ¾î ¶§¹®¿¡ ³Ö¾úÀ½
	Interface_clanmenu.Draw();
}
		

void clanMENUinit()
{
	Interface_clanmenu.CLANmenu_INIT();
	//ktj : Å¬·£»ó¿¡¼­ÀÇ ÇöÀç À§Ä¡¸¦ ¾Ë¾Æ³½´Ù.
	Interface_clanmenu.CLANmenu_clanPOSITION();
}


//·¹º§¾÷À» ÇßÀ»¶§ ÇÔ¼ö¸¦ È£ÃâÇØÁØ´Ù.
//=========·¹º§¾÷ µµ¿ò¸»==========================
//int ng = 1;
void InitHelp()
{	
	if(!g_GuideHelp.GetIsOn()) return; //·¹º§¾÷ µµ¿ò¸»ÀÌ ²¨Á®ÀÖÀ» °æ¿ì
	//if((sinChar->Level == 20)&&(sinChar->JOB_CODE > 4)) return;
	g_Help.SetStartPos(0,0);
	if(!g_Help.CheckLevel(sinChar->Level,sinChar->JOB_CODE)) return;
	g_Help.SetHelpN(LEVELUP_HELP);
	g_Help.menuInit(LEVELUP_HELP);
	/*switch(ng)
	{
	case 1:
		g_Help.CheckLevel(1,2);
		break;
	case 2:
		g_Help.CheckLevel(1,5);
		break;
	case 3:
		g_Help.CheckLevel(2,2);
		break;
	case 4:
		g_Help.CheckLevel(3,2);
		break;
	case 5:
		g_Help.CheckLevel(4,2);
		break;
	case 6:
		g_Help.CheckLevel(5,2);
		break;
	case 7:
		g_Help.CheckLevel(6,2);
		break;
	case 8:
		g_Help.CheckLevel(8,2);
		break;
	case 9:
		g_Help.CheckLevel(10,2);
		break;
	case 10:
		g_Help.CheckLevel(10,5);
		break;
	case 11:
		g_Help.CheckLevel(12,2);
		break;
	case 12:
		g_Help.CheckLevel(15,2);
		break;
	case 13:
		g_Help.CheckLevel(17,2);
		break;
	case 14:
		g_Help.CheckLevel(20,2);
		break;
	case 15:
		g_Help.CheckLevel(22,2);
		break;
	case 16:
		g_Help.CheckLevel(25,2);
		break;
	case 17:
		g_Help.CheckLevel(30,2);
		break;
	case 18:
		g_Help.CheckLevel(40,2);
		break;
	case 19:
		g_Help.CheckLevel(50,2);
		break;
	case 20:
		g_Help.CheckLevel(60,2);
		break;
	case 21:
		g_Help.CheckLevel(65,2);
		break;
	case 22:
		g_Help.CheckLevel(70,2);
		break;
	case 23:
		g_Help.CheckLevel(80,2);
		ng = 0;
		break;
	}
	
	
	ng++;*/
}

void InitGuideHelp()
{	
	g_GuideHelp.SetDoing(TRUE);
	g_GuideHelp.SetStartPos(0,0);	
	g_GuideHelp.CheckLevel(sinChar->Level);
	//g_GuideHelp.CheckLevel(17);
	g_GuideHelp.SetHelpN(GUIDEHELP_LIST);
	g_GuideHelp.menuInit(GUIDEHELP_LIST);

	IsDrawGuideHelp = TRUE;
}



void HelpDraw()
{
	if(g_Help.GetHelpN() !=-1)
	{
		switch(g_Help.GetHelpN())
		{
		case LEVELUP_HELP:
			g_Help.Draw(0);
			break;
		case LEVELUP_HELP_CONTENT:	

			g_Help.Draw(0);			
			break;		
		}
	}
}

void CLAN_MENU::GuideHelpDraw()
{
	if(g_GuideHelp.GetHelpN() !=-1)
	{
		switch(g_GuideHelp.GetHelpN())
		{			
		case GUIDEHELP_LIST:
			DrawBox(NOTICE_X,NOTICE_Y-50,9,9);
			g_GuideHelp.Draw();
			break;
		case GUIDEHELP_CONTENT:
			DrawBox(NOTICE_X,NOTICE_Y-50,9,9);
			g_GuideHelp.Draw();
			break;

		}
	}
}
/*//========¼­¹ö¿¡¼­ ¿þÀÌºê ¹Þ±â ¼¼ÆÃ===================================================
int GoWavDown_Check = 0;

char szWavUrl[255] = {0,};
BOOL bWavError = FALSE;

//1.¼­¹ö url¸¦ °¡Áö°í ¿Â´Ù
void GetWaveUrl(char* url)
{	
	if((url == NULL)||(url[0] == 0 ))
	{
		bWavError = TRUE;
		return;
	}
	
	ZeroMemory(szWavUrl,sizeof(szWavUrl));
	strcpy(szWavUrl,url);
	GoWavDown_Check = 1;
}

//2.¸ÞÀÎ¿¡¼­ ½ÇÇàÇÏ´Â ÇÔ¼ö
int DoWavDown_check(char* FileName)
{
	if(OpenFlag == 1) return -1;  //´Ù¸¥°Ô ¿­·ÁÀÖÀ¸¸é ¾ÈÇÏ°í ³ªÁß¿¡ ÇÑ´Ù.

	GoWavDown_Check = 1;
	if(GoWavDown_Check == 1)
	{
		void DoWavDown(char* FileName);
		DoWavDown(FileName);
	}

	return 0;
}

void DoWavDown(char* FileName)
{
	C_menuN = -1;
	OpenFlag = 1;
	g_cNpcWav.SetNpcWavNum(NPCWAVE_CALL);
	g_cNpcWav.SetFileName(FileName);
}
*/
//=============°×µé¾î°¡±âÁ÷Àü¿¡ ³ª¿À´Â °æ°í ¸Þ¼¼Áö=====================
int GoNotice_chking = 0;
int m_nNoticeCount = -1;
char szNoticeUrl[255] = {0,};
//1. ¼ÂÆÃÇÔ¼ö
int GetNoticeUrl(char *url)  
{
	GoNotice_chking = 0;
	ZeroMemory(szNoticeUrl,sizeof(szNoticeUrl));
	strcpy(szNoticeUrl,url);

	GoNotice_chking = 1;
	return 1;
}
//2. ¸ÞÀÎ¿¡¼­ ½ÇÇàÀ» ±ÇÇÏ´Â ÇÔ¼ö
void GoNotice_chk()
{
	if(OpenFlag == 1) return;  //´Ù¸¥°Ô ¿­·ÁÀÖÀ¸¸é ¾ÈÇÏ°í ³ªÁß¿¡ ÇÑ´Ù.

	if( GoNotice_chking == 1) {		
		if(m_nNoticeCount <NOTICECOUNT-1)
		{
			GoNotice_chking = 0;
			++m_nNoticeCount;
			void GoNotice();
			GoNotice();
		}
		
	}
}

//3. ½ÇÇàÅä·ÏÇÏ´Â ÇÔ¼ö
void GoNotice()
{
	C_menuN2= 0;
	OpenFlag = 1;
	C_menuN = CLAN_NOTICE;
	
	//cClanNotice.SetNoticeCount(1);

}




/*==================================================================================
//
// ¿ÜºÎ¿¡¼­ »ç¿ëµÇ´Â Å¬·£ÀÇ ±¸µ¿ ¼ÂÆÃ ÇÔ¼öµé								   start
//
==================================================================================*/


/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º¸í : 
: ÇÏ ´Â ÀÏ : Å¬·£ ¸Ç Ã³À½ ¼ÂÆÃ
///////////////////////////////////////////////////////////////////////////*/

//ktj : Å¬·£¸Þ´º ÀÎÅÍÆäÀÌ½º init
//setN : 0 : ÃÖÃÊ ¼ÂÆÃ  1: µÎ¹øÂ°¼ÂÆÃ(¸ðµç 
void clanMENU_INIT(int setN)
{	
	if(bCheckHostNameandPort==0) 
	{
		//ktj : notice ¸Þ´º¶§¹®¿¡ ³ÖÀ½.
		switch(setN) {
		case 0:
			void ReadWEBDebugOption();
			ReadWEBDebugOption();

			//Interface_clanmenu.NoticeMessage_Init();
			break;

		case 1:
			Interface_clanmenu.NoticeMessage_Init2();
#ifdef USE_PROSTONTALE		//=========== ÇÁ¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
			Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, szConnServerName, 
				sinChar->Money,500000); //6ÀÎ ÀÌÇÏ
#endif
			break;
		}
	}
	


	if(!bCheckHostNameandPort) return;




	switch(setN) {
	case -1:				//½ÇÁ¦·Î´Â »ç¿ë¾ÈÇÔ¿¡ ÁÖÀÇ
		void ReadWEBDebugOption();
		ReadWEBDebugOption();


		ZeroMemory(&ClanWonList,  sizeof(CLANWONLIST ));

		Interface_clanmenu.CLANmenu_INIT();
		//ktj : Å¬·£»ó¿¡¼­ÀÇ ÇöÀç À§Ä¡¸¦ ¾Ë¾Æ³½´Ù.
		Interface_clanmenu.CLANmenu_clanPOSITION();

		
		break;


	case 0:				//¸ÇÃ³À½¼ÂÆÃ : Ä³¸¯ÅÍ ¼±ÅÃÁ÷Àü¼ÂÆÃ
		void ReadWEBDebugOption();
		ReadWEBDebugOption();

		int LoadClanMessage();
			LoadClanMessage();

		void CreateSaveData_dir();
		CreateSaveData_dir();			//savedata/clandata¸¸µê

		//void CreateNPCWav_dir(); //npcwavµð·ºÅä¸® ¸¸µé±â
		//CreateNPCWav_dir();


		ZeroMemory(&ClanWonList,  sizeof(CLANWONLIST ));
		Interface_clanmenu.CLANmenu_INIT();
#ifdef VOICE_CHAT
		//if(smConfig.DebugMode)	//ÀÏ´Ü µð¹ö±×
		//{
			//À¯±¤¿­ : À½¼ºÃ¤ÆÃ °ü·Ã Å¬¶óÀÌ¾ðÆ® ÇÁ·Î¼¼½º¸¦ ½ÇÇà½ÃÅ´.
			g_CtrlProcess.CheckIPandPort(0, 0);  
		//}
#endif

		break;

	case 1:				//°× ½ÇÁ¦ ½ÃÀÛ½Ã ¼ÂÆÃ

#ifdef VOICE_CHAT
			//À¯±¤¿­ : À½¼ºÃ¤ÆÃÇÁ·Î¼¼½ºÀÇ À©µµ¿ì ÇÚµéÀ» °¡Áö°í ¿Â´Ù.
		g_CtrlProcess.Init();
#endif
	#ifdef USE_PROSTONTALE		//=========== ÇÁ¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì

		cBaseMenu.Load2();
		cClanChatting.Load2();
		Interface_clanmenu.Init2();	


		//setNÀº 0ÀÇ °æ¿ì Ä³¸¯ÀÌ¸§À» µû·Î ÁÖ¾î¾ß ÇÔ¿¡ Å©°Ô ÁÖÀÇÇÒ°Í.
#ifdef USE_YAHEL
		//Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, "¾ÆÀ£",//szConnServerName, 
		Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, "¿©¿Õ¹ú¼­¹ö",//szConnServerName, 
#else
		Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, szConnServerName, 
#endif
			sinChar->Money,500000); //6ÀÎ ÀÌÇÏ

		//ktj: ÀÓ½Ã·Î Áö¿ò.
		//ktj : Å¬·£»ó¿¡¼­ÀÇ ÇöÀç À§Ä¡¸¦ ¾Ë¾Æ³½´Ù.
		Interface_clanmenu.CLANmenu_clanPOSITION();
		
	
	#endif
		break;
	}
}


//hoLogin.cpp¿¡¼­ »ç¿ëÇÔ.
int isDELETE_character(char *charName) 
{
	if(!bCheckHostNameandPort) return 1;		//1Àº Ä³¸¯ÅÍ¸¦ Áö¿öµµµÈ´Ù´Â¶æ


	int web_DB_state_FLAG_WAIT();
	while(1) {
		if(web_DB_state_FLAG_WAIT() == 1) 
			break;
	}



	//ktj : ÀÌ°Å ÀÌ»óÇÔ µð¹ö±ë=====================================================
#ifdef USE_YAHEL
	//Interface_clanmenu.SetUserData(UserAccount, charName, "¾ÆÀ£", //szConnServerName, 
	Interface_clanmenu.SetUserData(UserAccount, charName, "¿©¿Õ¹ú¼­¹ö", //szConnServerName, 
#else
	Interface_clanmenu.SetUserData(UserAccount, charName, szConnServerName, 
#endif

		500000   ,500000); //6ÀÎ ÀÌÇÏ //ktj : ÀÌ°Å ÀÌ»óÇÔ µð¹ö±ë=======================================

	//ktj : Å¬·£»ó¿¡¼­ÀÇ ÇöÀç À§Ä¡¸¦ ¾Ë¾Æ³½´Ù.
	Interface_clanmenu.CLANmenu_clanPOSITION();
	cldata.myPosition = 0;//CLANNO_REGESTER;
	while(1) {
		web_DB_main();					//web db¸¦ »ç¿ëÇÏ´Â Å¬·£ ¸Þ´º¿¡¼­¸¸ ºÒ¸®¿öÁü.	
		cIsClanMember.Main();			//ktj : Å¬·£¿øÀÇ Æ÷Áö¼Ç Ã¼Å© ¸ÞÀÎ

		if(cldata.myPosition != 0) 
			break;
	}

	while(1) {
		if(web_DB_state_FLAG_WAIT() == 1) 
			break;
	}

	/*
	#define CLANUSER					100		//ÀÏ¹ÝÀ¯Àú
	#define CLANCHIP					101		//¯…
	#define CLANNO_REGESTER				102		//¹«µî·ÏÀÚ
	#define CLAN_NOCONNECT				103		//ÄÁ³ØÆ®°¡ ¾ÈµÇ¼­ ¼³Á¤ºÒ°¡
	*/
	return cldata.myPosition;
}



void CLAN_MENU::Init2()
{
	#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì

	MatPartyBackGround =
		CreateTextureMaterial( "image\\Sinimage\\Help\\party_win.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );

	//box===========================================================================start

	hBox1 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxCorner.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox2 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxLine.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox3 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box3.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox4 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box4.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );
	hBox5 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box5.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox6 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box6.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox7 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box7.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox8 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box8.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox9 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box9.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	//box===========================================================================end
	hScl_icon_tj = CreateTextureMaterial( "image\\Sinimage\\Help\\scl_icon.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	g_Help.Load();
	g_GuideHelp.Load();


	cBaseMenu.copy_LoadResource2(&cIsClanMember);		//¸®¼Ò½º Ä«ÇÇ
	cBaseMenu.copy_LoadResource2(&cClanChip);		//¸®¼Ò½º Ä«ÇÇ
	cBaseMenu.copy_LoadResource2(&cClanUser);		//¸®¼Ò½º Ä«ÇÇ
	cBaseMenu.copy_LoadResource2(&cClanMake);		//¸®¼Ò½º Ä«ÇÇ
	cBaseMenu.copy_LoadResource2(&cClanReport);		//¸®¼Ò½º Ä«ÇÇ
	cBaseMenu.copy_LoadResource2(&cClanChatting);		//¸®¼Ò½º Ä«ÇÇ
	cBaseMenu.copy_LoadResource2(&cClanDeleteCha);		//¸®¼Ò½º Ä«ÇÇ
	cBaseMenu.copy_LoadResource2(&cClanJoin);		//¸®¼Ò½º Ä«ÇÇ	
	
	cBaseMenu.copy_LoadResource2(&cClanNotice);		//¸®¼Ò½º Ä«ÇÇ	

#endif
}

//notice¸Þ½ÃÁö·Îµå¿ëÀÇ Init2()¿¡ »óÀÀÇÏ´Â ÇÔ¼ö
void CLAN_MENU::NoticeMessage_Init2()
{
	#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì

	MatPartyBackGround =
		CreateTextureMaterial( "image\\Sinimage\\Help\\party_win.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );

	//box===========================================================================start

	hBox1 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxCorner.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox2 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxLine.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox3 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box3.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox4 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box4.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );
	hBox5 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box5.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox6 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box6.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox7 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box7.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox8 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box8.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox9 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box9.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	//box===========================================================================end
	hScl_icon_tj = CreateTextureMaterial( "image\\Sinimage\\Help\\scl_icon.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	cBaseMenu.copy_LoadResource2(&cClanNotice);		//¸®¼Ò½º Ä«ÇÇ	

#endif
}




void CLAN_MENU::CLANmenu_INIT()
{
	if(!bCheckHostNameandPort) return;
	//g_ViewClanInfo.LoadData();

	Init();


#ifdef  USE_PROSTONTALE

	//SetUserData(UserAccount, sinChar->szName, szConnServerName); //6ÀÎ ÀÌÇÏ
	//ktj : ÀÌ°Ô ¸ÂÀ½.
	//SetUserData(UserAccount, sinChar->szName, szConnServerName, sinChar->Money,1000); //6ÀÎ ÀÌÇÏ

	//ktj : ¿øº»
#ifdef USE_YAHEL
	//SetUserData(UserAccount, sinChar->szName, "¾ÆÀ£",//szConnServerName, 
	SetUserData(UserAccount, sinChar->szName, "¿©¿Õ¹ú¼­¹ö",//szConnServerName, 
#else
	SetUserData(UserAccount, sinChar->szName, szConnServerName, 
#endif
		sinChar->Money,500000); //6ÀÎ ÀÌÇÏ
	//SetUserData(UserAccount, "Çã°Æ´ö", "¾ÆÀ£", 500000 ,500000); //6ÀÎ ÀÌÇÏ

	//SetJoinData("ÇÏÇÏÇÏ","¿ïÆ®¶ó","ÇåÆ®");

#else



	//SetJoinData("ÇÏÇÏÇÏ","¿ïÆ®¶ó","ÇåÆ®");
	//Å¬·£ÀåÀ¸·Î µî·ÏµÈ idÀÓ			
	strcpy(szConnServerName,"Æë±Ï¼­¹ö");
	SetUserData("Red","»¡°­",szConnServerName,500000,100000); //6ÀÎ ÀÌÇÏ
	SetUserData("ccc","»¡°­4",szConnServerName,500000,100000); //6ÀÎ ÀÌÇÏ
	//SetUserData("ccc","º¸¶ó2",szConnServerName,500000,100000); //6ÀÎ ÀÌÇÏ

	

	//SetUserData("test2000","Å¬·£¹«»ç","¾ÆÀ£",500000,100000); //6ÀÎ ÀÌÇÏ
	//SetUserData("ccc","¼º³²70","¾ÆÀ£",500000,100000);
	//Å¬·£¿øÀ¸·Î µî·ÏµÈ idÀÓ	

#endif
}


/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º¸í :
: ÇÏ ´Â ÀÏ : °èÁ¤¿¡ ¸¸µé¾îÁø Ä³¸¯ÅÍµéÀÇ Å¬·£Á¤º¸ ¾Ë¾Æ¿À±â
///////////////////////////////////////////////////////////////////////////*/
BOOL bGetChaClan = FALSE; //°èÁ¤¿¡ °ü·ÃµÈ Ä³¸¯ÅÍµéÀÇ Å¬·£Á¤º¸¸¦ ÀÐ¾î¿À´ÂÁö Ã¼Å©
int  nGetChaClan = 0;   //0: ÁøÇà¾ÈµÊ 1: ÁøÇàµÇ°íÀÖÀ½ 2: ÁøÇà¿Ï·á  3: ¿¡·¯
int nStatusCount=0;	


int cntsu = 0;
char *szSelectCha[5][2];


void InitSelectCha()
{
	if(!bCheckHostNameandPort) return;

	nStatusCount=0;	
	ZeroMemory(chacldata,sizeof(chacldata));
	ZeroMemory(szSelectCha,sizeof(szSelectCha));
	cntsu = 0;
}

void ClearSelectCha()
{
	if(!bCheckHostNameandPort) return;


	int i;
#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
	for(i =0; i< 5; i++)
	{
		if(chacldata[i].hClanMark) {

			chacldata[i].hClanMark->Release();
			chacldata[i].hClanMark = NULL;

		}
		if(chacldata[i].hClanMark16) {

			chacldata[i].hClanMark16->Release();
			chacldata[i].hClanMark16 = NULL;

		}
	}

	
#else
	for(i =0; i< 5; i++)
	{
		if(chacldata[i].hClanMark) {

			
			DeleteObject(chacldata[i].hClanMark);

		}
		if(chacldata[i].hClanMark16) {

			DeleteObject(chacldata[i].hClanMark16);

		}
	}
#endif
	bGetChaClan = FALSE;
	ZeroMemory(szSelectCha,sizeof(szSelectCha));
	ZeroMemory(chacldata,sizeof(chacldata));
	ZeroMemory(&cldata,sizeof(CLANDATA));
	nStatusCount = 0;

}

//Ä³¸¯ÅÍµéÀÇ ÀÌ¸§À» ÀÔ·Â
int HONG_GetChaClanName(char* id, char* chaname)
{
	if(!bCheckHostNameandPort) return 0;


	int i;
	int nReturn = 0;;
	for(i = 0; i < 5; i++)
	{
		if(szSelectCha[i][0] == NULL)
		{
			szSelectCha[i][0] = id;
			szSelectCha[i][1] = chaname;			
			nReturn =1;

			break;
		}
	}

	cntsu = i+1;
	
	if( i == 5) return -1;

	return nReturn;
}


	

int  main_chaC()
{
	if(!bCheckHostNameandPort) return 0;

	//while(1) {

	Interface_clanmenu.Main(PARTY_PROCESS );

	if(nStatusCount>=cntsu){
		return 1;
	}
	else	
	{
		if(OpenFlag==0) {
			bGetChaClan = TRUE;
			int GetChaClanName(char* id, char* chaname, char* gserver);
			GetChaClanName(szSelectCha[nStatusCount][0], szSelectCha[nStatusCount][1], szConnServerName);
		}
	}
	return 0;
}


int GetChaClanName(char* id, char* chaname, char* gserver)
{
	if(!bCheckHostNameandPort) return 0;


	//ÀÓ½Ã
	Interface_clanmenu.Main(PARTY_PROCESS );


	bGetChaClan = FALSE;
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;
	nGetChaClan = 0;
	void SetUserData2(char* id, char* chaname, char* gserver);
	SetUserData2(id, chaname, gserver);
	C_menuN = CLAN_isClanWon;
	bGetChaClan = TRUE;

	return 1;	
}









/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º¸í :
: ÇÏ ´Â ÀÏ : Å¬·£¿øÀ¸·Î¼­ÀÇ À§Ä¡¸¦ ¾Ë¾Æ³¿.
///////////////////////////////////////////////////////////////////////////*/

#ifdef VOICE_CHAT
BOOL bCheckClan = FALSE;
#endif
int CLAN_MENU::CLANmenu_clanPOSITION()
{

	if(!bCheckHostNameandPort) {
		cldata.myPosition = CLAN_NOCONNECT;
		return 0;
	}

	if(OpenFlag==1) return 0;		//ÀÌ ¸Þ´º°¡ ´ÝÇôÀÖÀ»¶§¸¸ °¡´ÉÇÔ.
	
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;
	C_menuN = CLAN_isClanWon;
	menuInit(C_menuN );
	ClanCharMove = 1;			//ktj : ¸¶¿ì½º°¡ Ã½Å©ÇÏ´Â ¹Ú½ºÃ½Å© 

#ifdef VOICE_CHAT	
		bCheckClan = TRUE;
#endif
	return 1;
}


/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º¸í :
: ÇÏ ´Â ÀÏ : NPC¿Í ¸¸³µÀ»¶§
///////////////////////////////////////////////////////////////////////////*/
void CLANmenu_meetNPC()	//newplay.cpp¿¡¼­ »ç¿ëÇÔ.
{
	Interface_clanmenu.CLANmenu_meetNPC();	
}
int CLAN_MENU::CLANmenu_meetNPC()
{	
	if(OpenFlag==1) {
		if(C_menuN == CLAN_DISPLAY_INFO)
		{
			C_menuN = CLAN_CLOSE_END_BEFORE;									
			
		}
		return 0;		//ÀÌ ¸Þ´º°¡ ´ÝÇôÀÖÀ»¶§¸¸ °¡´ÉÇÔ.
	}

	
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;	
	if(!bCheckHostNameandPort)
	{
		C_menuN = CLANSERVER_INSPECT_BEFORE;
		
	}
	else
	{
		C_menuN = CLAN_GO_NPCSTART;
	}
	

	//menuInit(C_menuN );

	ClanCharMove = 1;			//ktj : ¸¶¿ì½º°¡ Ã½Å©ÇÏ´Â ¹Ú½ºÃ½Å© 
	return 1;
}






/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º¸í :
: ÇÏ ´Â ÀÏ : Å¬·£¿øµéÀÇ Ã¤ÆÃ¸®½ºÆ®¸¦ º¼¶§
///////////////////////////////////////////////////////////////////////////*/
void CLANmenu_ChatList(int sw)	//newplay.cpp¿¡¼­ »ç¿ëÇÔ.l
{
	Interface_clanmenu.CLANmenu_ChatList(sw);	
}
void CLAN_MENU::CLANmenu_ChatList(int sw)
{

	if(!bCheckHostNameandPort) return;
	if(OpenFlag==1) return;
	if(bOpenChatList) return;

	ChatList_CmenuN2 = 0;

	switch(sw)
	{
	case 0: //½ºÅ©·Ñ µÇ°Ô
		
		cClanChatting.InitClanChatList();
		if(bIsReadData) ChatList_CmenuN = CLAN_DISPLAY_OPEN;
		else	ChatList_CmenuN = CHATLIST_READDATA;

		cClanChatting.menuInit(ChatList_CmenuN);

		break;
	case 1: //½ºÅ©·Ñ ¾ÈµÇ°Ô
		cClanChatting.NoScroll();
		//if(bIsReadData) ChatList_CmenuN = CLAN_DISPLAY_OPEN;
		//else	ChatList_CmenuN = CHATLIST_READDATA;		

		ChatList_CmenuN = CLAN_DISPLAY_INFO;				
		cClanChatting.menuInit(ChatList_CmenuN);

#ifdef USE_PROSTONTALE		//=========== ÇÁ¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
		
#else
		OpenFlag = 1;
		C_menuN = ChatList_CmenuN;
	
#endif


		break;
	}
}




void CLANmenu_ChatList_Main()	//newplay.cpp¿¡¼­ »ç¿ëÇÔ.l
{
	cClanChatting.Main();			//Å¬·£ Ã¤ÆÃ¸®½ºÆ®
}
void CLANmenu_ChatList_Draw()	//newplay.cpp¿¡¼­ »ç¿ëÇÔ.l
{
	cClanChatting.Draw();			//Å¬·£ Ã¤ÆÃ¸®½ºÆ®
}


/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º¸í :
: ÇÏ ´Â ÀÏ : cldata¾÷µ¥ÀÌÆ® ÇÒ¶§
///////////////////////////////////////////////////////////////////////////*/
void Updatecldata()
{
	//Interface_clanmenu.Updatecldata();
	g_UpdateCldata.Updatecldata();
}


/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º¸í : ±ÇÀ¯ÇÏ´Â ¸Þ´ºµé.
: ÇÏ ´Â ÀÏ : ÀÏ¹ÝÀÎ¿¡°Ô Å¬·£ÀÇ °¡ÀÔÀ» ±ÇÀ¯ÇÏ¸é ±ÇÀ¯ÇÑ´Ù´Â ¸Þ´º°¡ ¶á´Ù.
///////////////////////////////////////////////////////////////////////////*/

//±ÇÀ¯¹Þ´Â »ç¶÷ÀÌ »ç¿ëÇÏ´Â ÇÔ¼ö
void ClanJoin(char *oneClanName, char *oneChipCharid)
{
	//Interface_clanmenu.SetJoinData("¿ïÆ®¶ó","ÇåÆ®");
	Interface_clanmenu.SetJoinData(oneClanName,oneChipCharid);
	Interface_clanmenu.ClanJoin();
}

//ktj : ±ÇÀ¯¹ÞÀºÀÚ°¡ ¸®ÅÏÇØÁÖ´Â °ª(ÀÌÇÔ¼ö¸¦ »ç¿ëÇØ ¸®ÅÏÇØÁØ´Ù.)
//0:Ãë¼Ò 1:OK
int JoinAnswer()
{
	return cClanJoin.nJoinAnswer;
}

void CLAN_MENU::ClanJoin()
{
	if(OpenFlag==1) return;
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			//ktj : ¸¶¿ì½º°¡ Ã½Å©ÇÏ´Â ¹Ú½ºÃ½Å© 	
	C_menuN = CLAN_JOIN_before;
	
}

/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º¸í :±ÇÀ¯ÇÏ´Â»ç¶÷ÀÌ »ç¿ë
: ÇÏ ´Â ÀÏ : Å¬·£ÀåÀÌ Å¬·£¿øÀ» µî·Ï½ÃÅ³¶§
///////////////////////////////////////////////////////////////////////////*/

//===================================
//ktj:»ç¿ë¾ÈÇÔ.
//====================================
void joinClanMember()
{
	Interface_clanmenu.joinClanMember();
}

void CLAN_MENU::joinClanMember()
{
	if(OpenFlag==1) return;

	
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			//ktj : ¸¶¿ì½º°¡ Ã½Å©ÇÏ´Â ¹Ú½ºÃ½Å© 	
	C_menuN = CLAN_JOIN_chip;
}

//ygy: Ä³¸¯ÅÍ »èÁ¦ ÀÓ½Ã
void CLANmenu_DeleteCha(char *id, char *gserver, char *chaname)
{
	cClanDeleteCha.SetDeleteChaInfo(id, gserver, chaname);
	Interface_clanmenu.CLANmenu_DeleteCha();

	cClanDeleteCha.bFlag = FALSE;
}


/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º¸í :
: ÇÏ ´Â ÀÏ : Ä³¸¯ÅÍ »èÁ¦½Ã
///////////////////////////////////////////////////////////////////////////*/
void ktj_IMSI_DELETE()
{
	//extern char UserAccount[256];		//id°¡ µé¾îÀÖ´Â ¹öÆÛ
	//extern char szConnServerName[16];	//Á¢¼ÓÇÑ ¼­¹öÀÌ¸§ÀÌ µé¾îÀÖ´Â ¹öÆÛ
	//CLANmenu_DeleteCha_SetCharacter(UserAccount, szConnServerName, "Çã°Æ´ö");
}



//ktj :  1. Ä³¸¯ Áö¿ì±âÀü¿¡ ¼ÂÆÃÇÏ´Â ÇÔ¼ö
void CLANmenu_DeleteCha_SetCharacter(char *id, char *gserver, char *chaname)
{
	cClanDeleteCha.SetDeleteChaInfo(id, gserver, chaname);

	//ktj : 2. Áö¿ì´Â ¸Þ´º¸¦ ¼ÂÆÃÇÑ´Ù.
	Interface_clanmenu.CLANmenu_DeleteCha();
}

//ktj : Ä³¸¯ Áö¿ì±âÀü¿¡ ºÒ¸®¿ì´Â ÇÔ¼ö
void CLAN_MENU::CLANmenu_DeleteCha()
{
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			//ktj : ¸¶¿ì½º°¡ Ã½Å©ÇÏ´Â ¹Ú½ºÃ½Å© 	
	C_menuN = CLAN_DELETECHA_START;

	cClanDeleteCha.SetHowDeleteChaFlag();
}

//ktj : 3. »óÅÂ ÇÃ·¡±×¸¦ º¸°í 2ÀÌ¸é Ä³¸¯À» »èÁ¦ÇÏ°í 3ÀÌ¸é »èÁ¦ ¸øÇÔ.(0,1ÀÌ¸é 2,3µÉ¶§±îÁö ±â´Ù¸°´Ù)
int CLANmenu_DeleteCha_flag()
{
	//»èÁ¦Àü : 0
	//»èÁ¦Áß : 1
	//»èÁ¦ ok : 2
	//»èÁ¦ ¾ÈµÊ : 3
	return cClanDeleteCha.GetHowDeleteChaFlag();
}



//////////////////////////////////////////////////////////////////////////////////
//Å¬·£ Á¤º¸ °®¾î¿À±â
//
/////////////////////////////////////////////////////////////////////////////////


int g_ClanCount=-1;
int ClanMark[10] = {0,0,0,0,0,0,0,0,0,0};

//============= µð¹ö±ë¿ë Å¬·£ÀÎÆ÷ µ¥ÀÌÅ¸¼¼ÀÌºê
int ReadClanInfo(DWORD dwClanNum)
{
	//µð¹ö±ë¿ëÀ¸·Î ±×¸®±â À§ÇÑ°Í
	g_ClanCount++;
	if(g_ClanCount > 9) g_ClanCount = 0;
	ClanMark[g_ClanCount] = dwClanNum; 
	//============================

	/*
	if(OpenFlag==1) {
		return -1;		//ÀÌ ¸Þ´º°¡ ´ÝÇôÀÖÀ»¶§¸¸ °¡´ÉÇÔ.
	}
	*/

	g_ViewClanInfo.SearchClan(dwClanNum);
	return ClanInfo_nNum;		//0~99;
}


// ÇöÀç 16*16 À¸·Î µÈ ±×¸²¸¸ ·ÎµåµÇÀÖÀ¸³ª 32*32°¡ ÇÊ¿äÇÑ °æ¿ì ºÎ¸¥´Ù.
// 32*32°¡ ¸Þ¸ð¸®¸¦ ¸¹ÀÌ Â÷ÁöÇØ¼­ ÀÌ·¸°Ô µû·Î ÇÊ¿äÇÑ ±Ø¼Ò¼öÀÇ °æ¿ì¿¡¸¸ ºÎ¸¥´Ù.
int ReadClanInfo_32X32(DWORD dwClanNum)
{
	int claninfo_n = ReadClanInfo(dwClanNum);
	if(claninfo_n >= 0) {
		int clanINFO_Load32X32(int claninfo_n );
		clanINFO_Load32X32(claninfo_n );
	}
	return claninfo_n;
}







//==================================================================================
// ¿ÜºÎ¿¡¼­ »ç¿ëµÇ´Â Å¬·£ÀÇ ±¸µ¿ ¼ÂÆÃ ÇÔ¼öµé								    end
//=================================================================================







/*==================================================================================
//
// Å¬·£¸Þ´º																	   start
//
==================================================================================*/
CLAN_MENU::CLAN_MENU()
{
	nClanWon_Num = 0;
	nScl_Bar = 0;           //½ºÅ©·Ñ¹Ù
	g_nClanIconNum;			//ÇïÇÁ¾ÆÀÌÄÜ ÃÑ¼ö
	g_HelpIconNumber = 0;    
	g_HelpDisPlay = 0;

}

CLAN_MENU::~CLAN_MENU()
{
}


//¸¶¿ì½ºÀ§Ä¡¸¦ Ã½Å©¾ÈÅä·ÏÇÏ´Â°Í hoLinkHeader.cpp¿¡¼­ »ç¿ë
POINT clanBoxPos;
POINT clanCLBoxPos;
void CLAN_MENU::Init()
{
	OpenFlag = 0;

	C_menuN = 0;
	C_menuN2 =0;

	

	//BackStartPos.x = 70;
	//BackStartPos.y = 94;

	//BackStartPos.x = 100;
	//BackStartPos.y = 94;

	BackStartPos.x = 101;
	BackStartPos.y = 114;


	//Å¬·£¸Þ´º¿¡¼­ ¿ùµåÂÊ¿¡ ¸¶¿ì½º°¡ ¿òÁ÷ÀÓÀÌ Àü´Þ¾ÈµÇµµ·ÏÇÑ´Ù.
	clanBoxPos.x = BackStartPos.x;
	clanBoxPos.y = BackStartPos.y;

	//Å¬·£Ã¤ÆÃ ¸®½ºÆ®¸Þ´º¿¡¼­ ¿ùµåÂÊ¿¡ ¸¶¿ì½º°¡ ¿òÁ÷ÀÓÀÌ Àü´Þ¾ÈµÇµµ·ÏÇÑ´Ù.
	clanCLBoxPos.x = 540+60;		//60Àº ±×¸²ÀÌ ¿À¸¥Æí¿¡ ºÙ¾îÀÖ±â ¶§¹®ÀÓ
	clanCLBoxPos.y = CHATLIST_BOX_Y;


	

	ZeroMemory(szRemoveClanWon,sizeof(char)*500);	
	ZeroMemory(ClanHelpIcon,sizeof(CLANHELPICON)*CLANHELPICON_NUM);		
	ZeroMemory(cldata.szJoinClanName,sizeof(char)*64);   //Á¶ÀÎ Å¬·£ ÀÌ¸§
	ZeroMemory(cldata.ChaName,sizeof(char)*64);  //Á¶ÀÎÇÏ´Â À¯Àú Ä³¸¯ÅÍ ÀÌ¸§
	ZeroMemory(cldata.szJoinClanChipName,sizeof(char)*64);   //Á¶ÀÎÇÏ´Â Å¬·£Àå ÀÌ¸§
	ZeroMemory(szReconfReleaseMsg,sizeof(char)*2048);

	
	nClanWon_Num = 0;			//Å¬·£¿øÆÄ½ÌÈÄ Å¬·£¿øÀÇ ¸í¼ö(Å¬·£ÀåÁ¦¿Ü)
	nReleaseClanWon = 0;		//»èÁ¦ Å¬·£¿ø
	//membmp = new MENUBMP;
	
	//hMark = NULL;
#ifndef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
	int LoadClanMessage();
	LoadClanMessage();
#endif

	Load();	
	cClanChatting.Load();

	//ktj : ¸Þ´º °ü·Ã Å¬¶ó½º ¼ÂÆÃ ===================
	
	cBaseMenu.Load();

	
	cIsClanMember.Init(1);
	cIsClanMember.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cIsClanMember);		//¸®¼Ò½º Ä«ÇÇ

	cClanChip.Init(1);
	cClanChip.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanChip);		//¸®¼Ò½º Ä«ÇÇ
	cBaseMenu.SetBase(&cClanChip);

	cClanUser.Init(1);
	cClanUser.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanUser);		//¸®¼Ò½º Ä«ÇÇ
	cBaseMenu.SetBase(&cClanUser);

	cClanMake.Init(1);
	cClanMake.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanMake);		//¸®¼Ò½º Ä«ÇÇ

	cClanReport.Init(1);
	cClanReport.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanReport);		//¸®¼Ò½º Ä«ÇÇ


	cClanChatting.Init(1);
	cClanChatting.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanChatting);		//¸®¼Ò½º Ä«ÇÇ
	cBaseMenu.SetBase(&cClanChatting);


	cClanDeleteCha.Init(1);
	cClanDeleteCha.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanDeleteCha);		//¸®¼Ò½º Ä«ÇÇ

	cClanJoin.Init(1);
	cClanJoin.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanJoin);		//¸®¼Ò½º Ä«ÇÇ	


	cClanNotice.Init(1);
	cClanNotice.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanNotice);		//¸®¼Ò½º Ä«ÇÇ	

	//µµ¿ò¸» ÃÊ±âÈ­
	//g_Help.Init(1);
	//g_Help.setParent(&cBaseMenu);
	//cBaseMenu.copy_LoadResource(&g_Help);		//¸®¼Ò½º Ä«ÇÇ	

	//guie ÃÊ±âÈ­
	g_GuideHelp.Init(1);
	g_GuideHelp.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&g_GuideHelp);		//¸®¼Ò½º Ä«ÇÇ	
	g_GuideHelp.InitLevelHelpLabel();

}


//notice¸Þ½ÃÁö´Â µû·Î ¼ÂÆÃµÇ¸ç Init()°ú µ¿½Ã¿¡ ›¾ÆÃÇÒ¼ö¾øÀ½.
//Å¬·£ ¼­¹ö°¡ Á×¾î ÀÖÀ» °æ¿ì ¼¼ÆÃ
void CLAN_MENU::NoticeMessage_Init()
{
	BackStartPos.x = 101;
	BackStartPos.y = 114;

	cBaseMenu.Load();

	cClanNotice.Init(1);
	cClanNotice.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanNotice);		//¸®¼Ò½º Ä«ÇÇ	

	g_Help.Load();
	g_GuideHelp.Load();

	g_GuideHelp.Init(1);
	g_GuideHelp.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&g_GuideHelp);		//¸®¼Ò½º Ä«ÇÇ	
	g_GuideHelp.InitLevelHelpLabel();
	
}


/*///////////////////////////////////////////////////////////////////////////
: ÇÔ¼ö¸í   : menuInit
: ÇÏ ´Â ÀÏ : ¸Þ´º ÃÑ°ý Init
: ¹Ý È¯ °ª :
: ÆÄ¶ó¹ÌÅÍ :
///////////////////////////////////////////////////////////////////////////*/
void CLAN_MENU::menuInit(int num)
{
	
	cIsClanMember.menuInit(num);		//Å¬·£¸¸µé±â ¸Þ´º initialize
	cClanMake.menuInit(num);		//Å¬·£¸¸µé±â ¸Þ´º initialize
	cClanChip.menuInit(num);		//Å¬·»¯… ¸Þ´º initialize
	cClanUser.menuInit(num);		//Å¬·£À¯Àú ¸Þ´º initialize
	cClanChatting.menuInit(num);
	cClanDeleteCha.menuInit(num);
	cClanJoin.menuInit(num);
}







/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º ¸í: 
: ÇÏ ´Â ÀÏ : ¸¶¿ì½º·Î ´©¸¥ ¸Þ´º ¹øÈ£ Ã½Å©ÇÔ¼ö.
: ¹Ý È¯ °ª :
:ÆÄ¶ó¹ÌÅÍ  :
///////////////////////////////////////////////////////////////////////////*/
int CLAN_MENU::chkMenu(int x, int y, RECT *r) 
{
	if(r->left <= x   &&   x<= r->right ) 
		if(r->top <= y   &&   y<= r->bottom ) 
			return 1;
	return 0;			//¾Æ¹«°Íµµ ¼±ÅÃ¾ÈÇÔ.
}
int CLAN_MENU::chkeckMenuN()
{
	int i;
	
	for(i=0; i<menuSu; i++) {
		if(  chkMenu(pCursorPos.x, pCursorPos.y, &menuPos[i])  ) {
			return i;
		}
	}
	return -1;
}





//¯…ÀÌ ±ÇÀ¯ÇÏ¸é ±ÇÀ¯¹ÞÀº »ç¶÷ÇÑÅ× ¶ß´Â ¸Þ´ºÀÓ.(ÇöÀç netplay.cpp¿¡¼­ »ç¿ëÁß)
void menu_joinOpen(char *chipCharID)
{
	//Interface_clanmenu.menu_joinOpen(chipCharID);
}


//Á¶ÀÎ¸Þ´º´Â Å¬·£¯…ÀÌ ±ÇÀ¯ÇÏ¸é ±ÇÀ¯¹ÞÀº »ç¶÷ÇÑÅ× ¸Þ´º°¡ ¶á´Ù.
int CLAN_MENU::menu_joinOpen(char *chipCharID)		//¯…ÀÇ Ä³¸¯ÅÍ id
{
	/*
	if(OpenFlag==1) return 0;					//ÀÌ ¸Þ´º°¡ ´ÝÇôÀÖÀ»¶§¸¸ °¡´ÉÇÔ.
	if( cldata.myPosition == 100 ||				//100(Å¬·£¿ø), 101:Å¬·£¯…¿¡°Ô ±ÇÀ¯ÇÒ¼ö ¾ø´Ù.
		cldata.myPosition == 101)				return 0;

	strcpy(cldata.chipCharID, chipCharID);
	C_menuN   = CLAN_JOIN_before;		//Á¶ÀÎ¿¡ ÀûÇÕÇÑÁö ¿©ºÎ.
	C_menuN2  = 0;
	OpenFlag  = 1;
	joinAnswer= 0;

	//ktj
	ClanCharMove = 1;
	*/

	return 1;
	
}





void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID)
{
	Interface_clanmenu.menu_joinOpen_Chip(isOK, clanWonID, clanWonCharID,0,0);		//¯…ÀÇ Ä³¸¯ÅÍ id;
}
void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel)
{
	Interface_clanmenu.menu_joinOpen_Chip(isOK, clanWonID, clanWonCharID,clanWonJob, clanWonLevel);		//¯…ÀÇ Ä³¸¯ÅÍ id;
}

//È£µ¿ClanÃß°¡
void g_IsCheckClanMember(smCHAR *pChar)
{
	Interface_clanmenu.IsCheckClanMember(pChar);
}

int CLAN_MENU::IsCheckClanMember(smCHAR *pChar)
{
	if(OpenFlag == 1)
		return 0;
	
	C_menuN = CLAN_IS_CHECK_MEMBER;	//Å¬·£¿¡ °¡ÀÔÇÑÁö 4ÀÏÀÌ Áö³µ´ÂÁö °Ë»ç¸¦ ÇÑ´Ù.
	cldata.TargetChar = NULL;
	if(pChar)
		cldata.TargetChar = pChar;
	
	//strcpy(cldata.ChaName, pChar->smCharInfo.szName);
	
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;
	ClanCharMove = 1;
	
	return 0;
}



//======================================================================
//±ÇÀ¯ÇÏ´Â ¸Þ´º¸¦ ´©¸£¸é ÀÌÇÔ¼ö¸¦ ºÒ·¯ ¸®ÅÏÀÌ 1ÀÌ¸é ±ÇÀ¯ÇÏ´Â µ¥ÀÌÅ¸¸¦ º¸³»°í ¾Æ´Ï¸é ¸»°Í.
// 0 ÀÌ¸é ´õÀÌ»ó Å¬·£¿øÀ» Ãß°¡ ÇÒ¼ö ¾øÀ½(ÀÚÃ¼¸Þ´º¿¡¼­ µî·Ï½ÃÅ³¼ö¾ø´Ù°í ³ª¿Â´Ù)
BOOL CheckClanWon(int level);		//

//======================================================================


//±ÇÀ¯¹ÞÀº »ç¶÷ÀÌ OKÇÏ¸é ±×¸í·ÉÀÌ Å¬·£¯…¿¡°Ô µÇµ¹¾Æ¿Í Å¬·£¯…ÀÌ °¡ÀÔ½ÃÅ°´Â ¸Þ´ºÀÓ.
//ÁÖÀÇ : È­¸é»ó¿¡´Â ¸Þ´º°¡ ¶ßÁö¾ÊÀ½.
int CLAN_MENU::menu_joinOpen_Chip(int joinOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel)		//¯…ÀÇ Ä³¸¯ÅÍ id
{
	if(OpenFlag==1) return 0;		//ÀÌ ¸Þ´º°¡ ´ÝÇôÀÖÀ»¶§¸¸ °¡´ÉÇÔ.


#ifdef __CLANSUBCHIP__
	//if(cldata.myPosition != 101 && cldata.myPosition != 104 ) return 0;	//101:Å¬·£¯…,ºÎÅ¬·£¯…¸¸ »ç¿ë°¡´ÉÇÑ ¸Þ´ºÀÓ.
	if(cldata.myPosition == 101 || cldata.myPosition == 104 ) goto jmp1;	//101:Å¬·£¯…,ºÎÅ¬·£¯…¸¸ »ç¿ë°¡´ÉÇÑ ¸Þ´ºÀÓ.
	return 0;
jmp1:
#else
	if(cldata.myPosition != 101 ) return 0;	//101:Å¬·£¯…¸¸ »ç¿ë°¡´ÉÇÑ ¸Þ´ºÀÓ.
#endif
	



#ifdef USE_PROSTONTALE		//=========== ÇÁ¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
	int chk = CheckClanWon(sinChar->Level);
	if(chk==0) {			//Å¬·£¿øÀ» Ãß°¡ÇÒ¼ö ¾ø½À´Ï´Ù.
		return 0;
	}
#endif

	/*
	if(joinOK==0) {
		C_menuN= CLAN_JOIN_chip_NO	;		//Å¬·£¿¡ °¡ÀÔÇÏ±â¸¦ °ÅºÎÇÔ.
		C_menuN2= -1;
	}
	else {
		*/
		C_menuN = CLAN_JOIN_chip		;	//Å¬·£¿¡ µî·Ï½ÃÅ²´Ù.
		strcpy(cldata.clanJoinID, clanWonID);
		strcpy(cldata.clanJoinCharID, clanWonCharID);
		cldata.clanJoinJob   = clanWonJob;
		cldata.clanJoinLevel = clanWonLevel;
	

		C_menuN2= 0;
	//}
	OpenFlag = 1;
	joinAnswer = 0;

	//ktj
	ClanCharMove = 1;


	return 1;
}








//int chkN11 = -1;
//int chkN22 = -1;

extern BOOL bip_port_error;
int CLAN_MENU::Main(int sw)
{
	web_DB_main();					//web db¸¦ »ç¿ëÇÏ´Â Å¬·£ ¸Þ´º¿¡¼­¸¸ ºÒ¸®¿öÁü.	

	GoNotice_chk();		//°æ°í¸Þ½ÃÁöÀÇ »ç¿ë¿©ºÎ
	if((bip_port_error==1)||GoNotice_chking||(m_nNoticeCount > -1))  {
		//if(m_nNoticeCount > -1)
				cClanNotice.Main();	//±×¸ÞÀÎ
	}
/*	if(!bWavError)
	{
		g_cNpcWav.Main(); //npc ¿þÀÌºê¹Þ±â ¸ÞÀÎÇÔ¼ö
	}*/
	g_Help.Main();
	g_GuideHelp.Main();




	if(bip_port_error) return 0;

	//char		szErrorMsg[256];
	if(OpenFlag==0) return 0;		//ÀÌ ¸Þ´º´Â´ÝÇûÀ½


	switch(sw) {
	case PARTY_START:				//Ã³À½ ºÒ¸®¿öÁú¶§ÀÇ Ã³¸®
		return 1;
	case PARTY_END:					//³¡³¯Áò¿¡ ºÒ¸®¿öÁú¶§ÀÇ Ã³¸®
		return 1;
	}

	//ClanCharMove = 1;
									//ktj : auth.cppÀÇ web_DBÃ½Å©¿ëÀÓ.
	cBaseMenu.Main();				//ktj : °ø¿ë ¸Þ´º ÀÇ ¸ÞÀÎ
	cIsClanMember.Main();			//ktj : Å¬·£¿øÀÇ Æ÷Áö¼Ç Ã¼Å© ¸ÞÀÎ
	cClanReport.Main();				//ktj : ¸Þ½ÃÁö Ã³¸®¿ë ¸ÞÀÎ
	cClanMake.Main();				//ktj : Å¬·£À» ¸¸µé°æ¿ìÀÇ ¸ÞÀÎ
	cClanChip.Main();				//Å¬·£ Ä¨ ¸Þ¼¼Áö Ã³¸®
	cClanUser.Main();				//Å¬·£ À¯Àú ¸Þ¼¼ÁöÃ³¸®
	cClanJoin.Main();
#ifdef USE_PROSTONTALE		//=========== ÇÁ¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì

	//cClanChatting.Main();			//Å¬·£ Ã¤ÆÃ¸®½ºÆ®
#else
	cClanChatting.Main();			//Å¬·£ Ã¤ÆÃ¸®½ºÆ®
#endif

	cClanDeleteCha.Main();            //Ä³¸¯ÅÍ »èÁ¦½Ã
	cClanNotice.Main();	//±×¸ÞÀÎ
	
	return TRUE;
}




char loadis[256] = {0,};
char loadis2[256] = {0,};
char updateis[256] = {0,};





//ÀÌ°Ô 1ÀÌ¸é ÀÎÆ÷¸¦ µå·ÎÀÎÇÑ´Ù.
int ktj_imsiDRAWinfo = 0;
//========================================================================³ªÁß¿¡ Áö¿ö¾ßÇÔ¿¡ ÁÖÀÇ

int CLAN_MENU::Draw()
{	

	
#ifndef USE_PROSTONTALE
	window_renderINIT();
#endif

	/////////////////////// µµ¿ò¸» ±×¸®±â////////////////////////
	HelpDraw();
	GuideHelpDraw();
	//////////////////////////////////////////////////////////
	
 	if((bip_port_error==1)||(m_nNoticeCount > -1)) {
		if(C_menuN==CLAN_DRAWNOTICE) {
    		DrawBox(NOTICE_X,NOTICE_Y-50,9,10);
  			Draw_C_menuN();
		}
		if(m_nNoticeCount > -1)
			cClanNotice.Draw();
	}



	if(bip_port_error) return 0;
	
#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì


#ifdef VOICE_CHAT

	/*
	extern int vrunRuning;					//vrun.datÀÇ ½ÇÇà¿©ºÎ
	if(vrunRuning == 1) 
	{
		
		extern BOOL bMic; //¸¶ÀÌÅ© on,off
		char buf[256];

		if(bMic == 0) {
			wsprintf(buf, "[ voice Chat Å×½ºÆ®Áß À½¼ºOFF ] ½ºÀ§Ä¡ shift+tab");
		}
		else {
			wsprintf(buf, "[ voice Chat Å×½ºÆ®Áß À½¼ºON ] ½ºÀ§Ä¡ shift+tab");
		}
		Draw_C_Text(buf, 10, 5,   0);



		int cnt=0;

		extern char voiceInfoStr[256];			//º¸ÀÌ½º Å¬¶óÀÌ¾ðÆ® Á¤º¸
		if(voiceInfoStr[0]!=0) {
			Draw_C_Text(voiceInfoStr, 10, (cnt*16) + 20,   0);
		}


		cnt = 1;
		extern VOICTALKUSERDATA voiceUser;			//¸»ÇÑÀ¯ÀúÀÇ ¸®½ºÆ®
		while(cnt<8) {
			if(voiceUser.uID[cnt][0] == 0) 
				break;

			wsprintf(buf, "¸»ÇÑÀ¯Àú %s",voiceUser.uID[cnt]);
			Draw_C_Text(buf, 10, (cnt*16) + 20,   0);

			cnt++;

			//À¯ÀúµéÀÌ ¸»À» ¾ÈÇÏ°í ÀÖ´Ù¸é µ¥ÀÌÅ¸¸¦ Áö¿î´Ù.
			if( (timeGetTime() - voiceUser.time ) >= 1000*2) {
				voiceUser.uID[0][0] = 0;
			}
		}
	
	}
	*/
	
#endif

	





	if(smConfig.DebugMode && ktj_imsiDRAWinfo ==1 ) 
	{

	//ktj : ÀÓ½Ã·Î ¹ö±×Ã½Å©
	char buf[256];

	wsprintf(buf, "bug :  %d ================ : (myPos:%d ) (Å¬·£¸¶Å©¹øÈ£%s,%d)  cldata.money %d, cldata.nCurrentClanWon_Num %d ", C_menuN, cldata.myPosition, cldata.ClanMark, cldata.intClanMark, cldata.money, cldata.nCurrentClanWon_Num);
	Draw_C_Text(buf, 0,0,   0);
	

	wsprintf(buf, "cldata.szID %s  cldata.ChaName %s cldata.name %s (C_menuN %d C_menuN2 %d) ================ ", cldata.szID,cldata.ChaName, cldata.name, C_menuN, C_menuN2);
	Draw_C_Text(buf, 0,16,   0);
	

	//Å¬·£ÀÎÆ÷ µð¹ö±ë
	int cinfoX = 0;
	int cinfoY = 32;
	int i2;
	for(i2=0; i2<100; i2++) {
		if(ClanInfo[i2].nStatus==0) continue;

		char buf[256];
		wsprintf(buf, "ClanInfo[%d] %s %s %s ", i2, 
				ClanInfo[i2].ClanInfoHeader.ClanMark_Num,
				ClanInfo[i2].ClanInfoHeader.ClanName,
				ClanInfo[i2].ClanInfoHeader.ClanReport);
		//debug_fd2( buf);
		Draw_C_Text(buf, cinfoX ,cinfoY,   0);
		cinfoY+=16;
	}


	int cinfoX2 = 16*25;
	int cinfoY2 = 32;

	for(i2=0; i2<10; i2++) {
		char buf[256];
		wsprintf(buf, "up ¸¶Å©¹øÈ£ [%d]:%d (ÃÖÁ¾ %d)", i2, ClanMark[i2], g_ClanCount);
		Draw_C_Text(buf, cinfoX2 ,cinfoY2,   0);
		cinfoY2+=16;
	}


	cinfoX2 = 20*35;
	cinfoY2 = 32;

	for(i2=0; i2<41; i2++) {
		//char buf[256];
		//wsprintf(buf, "up ¸¶Å©¹øÈ£ ¹ÞÀº°Í d_buf[%d] = %d ",i2, d_buf[i2] );

		//memcpy(ClanWonList.clanWon,cldata.clanWon,sizeof(cldata.clanWon));
		Draw_C_Text(cldata.clanWon[i2], cinfoX2 ,cinfoY2,   0);
		cinfoY2+=16;
	}

#ifdef VOICE_CHAT
	//Å¬·£¿ø ¸®½ºÆ® º¸¿©ÁÖ±â
	char Msg3[1024] = {0,};
	int nPos= 0;
	{
		extern char g_AllClanWon[_CLANWON_MAX][STRING_MAX];
		for(int i = 0; i< 90; i+=5)
		{
			wsprintf(Msg3,"%s, %s,  %s , %s, %s\n",
				g_AllClanWon[i],g_AllClanWon[i+1],g_AllClanWon[i+2],g_AllClanWon[i+3]
				,g_AllClanWon[i+4]);
				Draw_C_Text(Msg3, 300,230+nPos,   0);
				nPos+=20;
		}

		
	}
#endif







	}
	



#endif
	/*
	wsprintf(buf, "Å¬·£Ã¤ÆÃ¸®½ºÆ®·Îµå´Â  %s ================ ", loadis);
	Draw_C_Text(buf, 0,32,   0);
	wsprintf(buf, "Å¬·£Ã¤ÆÃ¸®½ºÆ®·Îµå2   %s ================ ", loadis2);
	Draw_C_Text(buf, 0,32+16,   0);

	wsprintf(buf, "¾øµ¥ÀÌÆ®Ä«¿îÆ® %s ================ ", updateis);
	Draw_C_Text(buf, 0,64,   0);
	*/
	
	
	


	

	//InvalidateRect(g_hwnd,NULL,1);
	if(OpenFlag==0) return 0;	


#ifndef USE_PROSTONTALE		//=========== À©µµÇÔ¼ö

	//window_renderINIT();			//Ã³À½ ÇÑ¹ø¼ÂÆÃÇÔ.
	HDC hdc = GetDC(g_hwnd);	
	HDC sorDC;
	sorDC  = CreateCompatibleDC(hdc);
	HDC destdc=CreateCompatibleDC(hdc);
	SelectObject(destdc, Dback.hb );
	PatBlt(destdc,0,0,800,600,PATCOPY);
	char szBuf[100];
	extern POINT	pCursorPos;
	
	// 0 : ÀÛ¾÷¼öÇàÇÏ±âÀü 1: ´Ù¿î·Îµå ¼öÇàÁß 2 : ÀÛ¾÷¿Ï·á 3: ¿¡·¯
	wsprintf(szBuf,"C_menuN : %d  ,x = %d, y = %d , ÁøÇà °úÁ¤ : %d Å¬·£ ÀÌ¸§ : %s,myposition=%d",
		C_menuN,pCursorPos.x,pCursorPos.y,nCheckDownLoad,cldata.name,cldata.myPosition);
	dsTextLineOut(destdc,100,0,szBuf,lstrlen(szBuf));

	SelectObject(hdc,ClanInfo[ClanInfo_nNum].hClanMark );
	BitBlt(destdc,0,0,32,32,sorDC,0,0,SRCCOPY);
	dsTextLineOut(destdc,0,50,ClanInfo[ClanInfo_nNum].ClanInfoHeader.ClanReport,lstrlen(ClanInfo[ClanInfo_nNum].ClanInfoHeader.ClanReport));
	DeleteDC(destdc);
	DeleteDC(sorDC);
	ReleaseDC(g_hwnd,hdc);

#endif
	
	/*
	if(OpenFlag){
	if(ANSdata.ret_val == -1){
		DrawBox(BackStartPos.x,BackStartPos.y,3,3);		
		//Loading();
		}
	}
	*/

	switch(C_menuN) {
	case CLAN_DRAWNOTICE:
	//case CLAN_NOTICE:
		DrawBox(NOTICE_X,NOTICE_Y,9,10);		
		//Draw_C_menuN();	
		cClanNotice.Draw();
		break;
	case CLAN_NOLEVEL: //·¹º§ÀÌ ¾ÈµÇ¼­ Å¬·£À» ¸ø¸¸µë
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();						
		break;
	case CLAN_ABILITYDOWN:
	case CLANSERVER_INSPECT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();						
		break;
	case CLAN_READ_CLANMARK:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();				
		break;	
	case CLAN_isCheckClanJang_Result:
	case CLAN_isCheckClanJang:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();				
		break;	
	case CLAN_MAKE_is:		//Å¬·£°á¼ºÀÇ»ç È®ÀÎ Y/N

		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();				
		break;
	case CLANMAKE_NOMONEY:
	case CLAN_MONEY_is:		// ´ë±ÝÁöºÒÀÇ»ç¹¯±â

		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();

		break;
	case CLAN_NAME_is:		//Å¬·£ÀÌ¸§ ¼³Á¤.
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_NONAME:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_NAME_BEING:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK_expl:		//Å¬·£¸¶Å©¼³¸í
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		
		break;
	case CLAN_INSPECTION_expl:		//½É»ç±â°£¼³¸í
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		
		break;

	case CLANMAKE_REAMMAKR_ERROR:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_NotMake:	//Å¬·£°á¼º¸øÇÏ´Ï µ¹¾Æ°¡¶ó
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLANMAKE_DOWN_INFO:
	case CLANMAKE_READ_CLANMARK:
	case CLAN_MAKE_FINISH:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_AllEnd:	//Å¬·£ ³¡³ª°í Å¬¸®¾îÇÏ´Â¼ÂÆÃºÎºÐ.
		break;


	case CLAN_ERROR:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;


	//============¯…¿ë¸Þ´º
	//case CLAN_CHIP_ReadDATA:		
	//	Draw_C_menuN();
	//	break;

	//===================ºÎ Å¬·£Ä¨ ÀÓ¸í¹× ÇØÀÓ
#ifdef __CLANSUBCHIP__
	case CLANCHIP_SUBCHIP_LOAD_DATA:
	case	CLANCHIP_APPOINTSUBCHIP_DO:	    //Å¬·£ºÎÄ¨ ÀÓ¸í ASPÈ£Ãâ
	case CLANCHIP_RELEASESUBCHIP_DO:	    //Å¬·£ºÎÄ¨ ÇØÀÓ ASPÈ£Ãâ
	case CLANCHIP_SUBCHIP_APPOINT_FLAG:		//Å¬·£ºÎÄ§ÀÌ ÀÓ¸íµÇ¾î´Ù´Â ÇÃ·¡±×¼¼ÆÃ
	case CLANCHIP_SUBCHIP_RELEASE_FLAG:		//Å¬·£ºÎÄ§ÀÌ ÇØÀÓµÇ¾î´Ù´Â ÇÃ·¡±×¼¼ÆÃ
	case CLANCHIP_SUBCHIP_READMSG_FLAG:		//Å¬·£ÀåÀÌ ºÎÄ§°ü·Ã¸Þ¼¼Áö¸¦ ÀÐ¾î´Ù´Â ÇÃ·¡±×¼¼ÆÃ
	case CLANUSER_SUBCHIP_READMSG_FLAG:		//Å¬·£À¯Àú°¡ ºÎÄ§°ü·Ã ¸Þ¼¼Áö¸¦ ÀÐ¾î´Ù´Â ÇÃ·¡±× ¼¼ÆÃ
	case CLANCHIP_SUBCHIP_LIST:			//Å¬·£¿øµé ¸®½ºÆ® º¸¿©ÁÜ ºÎ Å¬·£Ä¨ÀÌ ÀÖÀ¸¸é µû·Î º¸¿©ÁÜ
	case CLANCHIP_RESUBCHIP_APPOINT:		//ºÎ Å¬·£Ä¨ ÀÓ¸í ÀçÈ®ÀÎ
	case CLANCHIP_RESUBCHIP_APPOINT_END:	//ºÎ Å¬·£Ä¨ÀÓ¸í ¸¶Áö¸· ¸Þ¼¼Áö
	case CLANCHIP_RELEASESUBCHIP:			//ºÎ Å¬·£Ä¨ÇØÀÓ ÀçÈ®ÀÎ
	case CLANCHIP_RELEASESUBCHIP_END:		//Å¬·£Ä¨ ÇØÀÓ ¸¶Áö¸· ¸Þ¼¼Áö
	case CLANCHIP_SUBCHIP_APPOINTMSG:
	case CLANCHIP_SUBCHIP_RELEASEMSG:
	case CLANUSER_SUBCHIP_APPOINTMSG:
	case CLANUSER_SUBCHIP_RELEASEMSG:
	case CLANCHIP_NOSUBCHIP:
	
#endif

	//ÀÌÀÓ °ü·Ã µå·Î¿ì
	case CLANCHIP_LEAVECLAN_NOLEVEL:
	case CLANCHIP_LEAVECLANDOWNLEVEL:
	case	CLANCHIP_LEAVECLAN_PFLAG:		
	case CLANCHIP_LEAVECLAN_MESSAGE:		
	case CLANUSER_LEAVECLAN_MESSAGE:		
	case CLANCHIP_LEAVECLAN_MESSAGEEND:	
	case CLANUSER_LEAVECLAN_MESSAGEEND:	
	case CLANCHIP_NOLEAVECLAN:
	case CLANCHIP_LEAVECLAN_RECONFIRM:
	case CLANCHIP_LEAVECLAN_CONFIRM:
	case CLANCHIP_LEAVECLAN_NOMONEY:
	case CLANCHIP_LEAVECLAN_SUCESS:
	case CLANCHIP_LEAVECLAN://ÀÌÀÓ
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_CHIP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
		//ycy
		//========= Ãß¹æ
	case CLAN_REMOVE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_REMOVE_SHORTCLANWON_RESULT:		
	case CLAN_REMOVE_RESULT:
	DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_REMOVE_SHORTCLANWON:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RELEASE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RECONF_RELEASE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_FINISH_RELEASE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLANCHIP_RELEASEMESSAGE:
	case CLAN_WAREHOUSE_RIGHT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK1:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK2:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK3:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_HELP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_HELP_CONTENT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;	
	

	case CLANCHIP_LEAVECLAN_DO:		//ÀÌÀÓ aspÈ£Ãâ
	case ISPFLAG_CHIP:
	case CLANCHIP_MAKE_FIRSTMESSAGE: 
	case CLANCHIP_DOWN6_CLANWON:    
	case CLANCHIP_DOWN6_CLANWON_MESSAGE:
	case CLAN_NOMAKE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	//=========Ä¨ À¯Àú¸Þ´º
	case CLANUSER_REMOVE ://Å¬·£¿øÀÌ Ãß¹æ´çÇßÀ»°æ¿ì
	case	CLANUSER_AUTORELEASE://ÀÚµ¿ÇØÃ¼
	case CLAN_USER:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	//Å¬·£À» ¾ÆÁ÷ °á¼º ¸øÇÔ
	case CLAN_USER_NOMAKE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RECONF_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_FINISH_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLANUSER_MAKE_FIRSTMESSAGE:			
	case CLANUSER_DOWN6_CLANWON_MESSAGE:
	case CLANUSER_DOWN6_CLANWON:			
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;

	//Å¬·£¯…ÀÌ °¡ÀÔ±ÇÀ¯ÇÒ¶§ ¶ß´Â ¸Þ´º
	case CLANUSER_JOIN:
	case CLAN_CLANWONOVER:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;

	case CLAN_JOIN:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;

	case CLAN_USER_WAREHOUSE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_USER_HELP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_USER_HELP_CONTENT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;	

	case CLAN_DISPLAY_END:
	case CLAN_DISPLAY_OPEN:		
	case CLAN_DISPLAY_CLOSE:
	case CLAN_CLOSE_ENDING:
	case CLAN_DISPLAY_INFO:
	case CHATLIST_READDATA:	
#ifdef USE_PROSTONTALE		//=========== ÇÁ¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
		//cClanChatting.Draw();
#else
		cClanChatting.Draw();
#endif
		break;	


	case CLAN_DELETECHA_RELEASECLAN_BEFORE: 
	case CLAN_DELETECHA_RELEASECLAN:      
	case	CLAN_DELETECHA_SECESSION_BEFORE:	
	case	CLAN_DELETECHA_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		cClanDeleteCha.Draw();
		break;
	case CLAN_REAMMAKR_ERROR:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RELEASE_LOADING:
	case CLAN_REMOVE_SHORTCLANWON_LOADING:
	case CLAN_REMOVE_LOADING:
	case CLAN_CHIP_ReadDATA:
	case CLAN_NPC_START:
	case CLAN_USER_ReadDATA:
	case ISPFLAG_USER:
	case CLANUSER_RELEASEMESSAGE:
	case CLANUSER_RELEASE_FLAG:
	case CLAN_RECONF_SECESSION_LOADING:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;	
	
	}	

#ifndef USE_PROSTONTALE		//=========== À©µµÇÔ¼ö
	window_renderFLIP();
#endif

	return TRUE;
}


//sw==0 : ÀÏ¹Ý sw==1: Å°ÀÔ·ÂÀ» ¹Þ´Â°æ¿ì sw==2: Å¬·£ÀÌ¸§À» Å¸ÀÌÆ²¿¡ ¾µ°æ¿ì»ç¿ë(±×¸²ÀÚÃ³¸®)
void CLAN_MENU::Draw_C_Text(char *str, int x, int y, int sw=0)
{
#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
	char strbuf[1024];

	HDC hdc;
	HFONT oldFont;
	renderDevice.lpDDSBack->GetDC(&hdc);
	SetBkMode( hdc, TRANSPARENT );

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject( hdc , hFont );


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;

	while(1) {
		

		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:


			
			if(sw==2){
				SetTextColor( hdc, RGB(100, 100, 100));	//±×¸²ÀÚ¿ë ±ÛÀÚ»ö
				//SetTextColor( hdc, RGB(255, 255,255));	//±×¸²ÀÚ¿ë ±ÛÀÚ»ö
				dsTextLineOut(hdc, x+1, y+1, strbuf, lstrlen(strbuf));

				SetTextColor( hdc, RGB(230, 255, 240));	//ÀÏ¹Ý±ÛÀÚ»ö
				dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			else     {
				SetTextColor( hdc, RGB(230, 255, 240));	//ÀÏ¹Ý±ÛÀÚ»ö
				dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			
			/*
			if(sw==2){
				SetTextColor( hdc, RGB(255, 255, 255));	//Å¬·£ÀÌ¸§ÀÔ·Â½Ã Èò»ö				
			}
			else {
				SetTextColor( hdc, RGB(230, 255, 240));	//ÀÏ¹Ý±ÛÀÚ»ö
			}
			dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			*/
			

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	

	if(sw==1) 
	{
		static cnt=0;
		cnt++;
		if(cnt<20) {
			SetTextColor( hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, x + (lstrlen(str)*6) , y-16, "|", 1);
		}
		if(cnt>=40) cnt=0;
	}

	if(oldFont)
		SelectObject( hdc, oldFont);
	renderDevice.lpDDSBack->ReleaseDC(hdc);
#else

#endif
}






//ycy : ¹Ú½º ±×¸®±â
int g_nTotalWidth = 0;
int CLAN_MENU::DrawBox(int x,int y,int x_width,int y_height)
{
	//pluto
	if( cSinHelp.sinGetHelpShowFlag() && !IsDrawGuideHelp ) return FALSE;	// ¹«ÇÑ ÅÚ·¹Æ÷Æ® ÄÚ¾î ¶§¹®¿¡ ³Ö¾úÀ½
	isDrawClanMenu = 1;
	g_nTotalWidth = x_width;



#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì

	#define BOXFONTSIZE 64

	if (renderDevice.IsDevice() == NULL)
		return FALSE;

	renderDevice.BeginScene();


	//µÞ¹è°æÂï±â
	//dsDrawColorBox( RGBA_MAKE(0,15,128,125), x+32, y+32, 	(x_width+1)*64, 	(y_height+1)*64);
	//dsDrawColorBox( RGBA_MAKE(0,20,10,125), x+32, y+32, 	((x_width+1)*64)+1, 	((y_height+1)*64)+1);
	
	sinDrawTexImage( hBox5, (float)x+64, (float)y+32, (float)( 64+(  ( x_width-2) *32) ), (float)(   32+(  (y_height-1) *32) ),
				0,0,
				0, 0, 32, 32, 
				255);
	//DrawSprite(x  ,y , hBox1_ktj ,  0, 0, 32, 32, 1);
	//int sinDrawTexImage( int Mat, float x, float y, float w, float h, 
	//						float surW, float surH, 
	//						float tLeft, float tTop, float tRight, float tBottom, 
	//						int Transp);
	//left, top
	sinDrawTexImage( hBox1,(float) x,(float) y, (float)64, (float)32,    
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);
	//right, top
	sinDrawTexImage( hBox3,(float)(   x+(32*x_width) +64 ), (float)y, 64, 32,    
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);	
	//left, bottom
	sinDrawTexImage( hBox7, (float)x, (float)(  y+(32*y_height) + 32 ), 64, 64 ,
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);
	//right, top
	sinDrawTexImage( hBox9,(float)(   x+(32*x_width) +64 ), (float)(  y+(32*y_height) + 32  ), 64, 64,    
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);
				
	int line;
	int sx = x+64;
	int ey=  y+(32*y_height) + 32 ;
	for(line=0; line<x_width; line++) {
		//À§ÂÊ ¶óÀÎ
		sinDrawTexImage( hBox2, (float) sx, (float)y, 32, 32,
				(float)0,(float)0,  
				(float)0, (float)0, (float)32, (float)32,
				255);
		
		//¾Æ·¡ÂÊ ¶óÀÎ
		sinDrawTexImage( hBox8, (float)sx, (float)( ey ), 32, 64,
				0,0,
				0, 0, 32, 64,
				255);
				
		sx+=32;
	}

	int sy = y+32;
	int ex = x+(32*x_width) + 64 ;
	for(line=0; line<y_height; line++) {
		//¿À¸¥ÂÊ¶óÀÎ
		sinDrawTexImage( hBox4, (float)x, (float)sy, 64, 32,
				0,0,
				0, 0, 64, 32,
				255);
		//¿ÞÂÊ ¶óÀÎ
		sinDrawTexImage( hBox6,(float)ex, (float)sy, 64, 32,
				0,0,
				0, 0, 64, 32,
				255);
		sy+=32;
	}
	
	renderDevice.EndScene();

	//DrawSprite(x+128,y+6, hClanTitle ,  0, 0, 139, 32, 0);
	//DrawSprite(x+ ( ((x_width*64)/2))-2 , y-2, hClanTitle ,  0, 0, 139, 32, 1);
	//DrawSprite(x + 90 ,y -10, hClanTitle ,  0, 0, 139, 32, 1);


#else



	//HBITMAP backu_BMP;
	//HDC backu_dc;



	
	BITMAP bit;
	int bx,by;
	int i;
	int nTotal_Width = 0;
	int nTotal_Height = 0;
	//int nStart_x;
	





	HDC hdc=GetDC(g_hwnd);

	HDC sorDC =CreateCompatibleDC(hdc);
	HDC destdc=CreateCompatibleDC(hdc);

	SelectObject(destdc, Dback.hb );		//off½ºÅ©¸°¼³Á¤.
	//SelectObject(sorDC, backBMP );

	/*
	for(int i=0; i<coordNum; i++) {

		BitBlt(
			destDC,
			coordB[i].left,coordB[i].top,
			//ÁÖÀÇ : ±æÀÌÀÓ.
			coordB[i].right, coordB[i].bottom,	//offscrÀ» À©µµÃ¢À¸·Î Ä«ÇÇ
			sorDC,
			coordB[i].left,coordB[i].top,
			SRCCOPY);

	}

	
	*/


	//¿ÞÂÊ top
	SelectObject(sorDC, hBox1);
	GetObject(hBox1,sizeof(BITMAP),&bit);
	bx = bit.bmWidth;
	nTotal_Width+=bx;
	by = bit.bmHeight;	
	BitBlt(destdc,x,y,bx,by,sorDC,0,0,SRCCOPY);

	for(i=0; i< x_width; i++)
	{
		SelectObject(sorDC,hBox2);
		GetObject(hBox2,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;
		nTotal_Width +=bx;
		by = bit.bmHeight;
		StretchBlt(destdc,x+BOXCORNER_WIDTH+(bx*i),y,bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}

	//¿À¸¥ÂÊ top

	SelectObject(sorDC, hBox3 );
	GetObject(hBox3,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;	
	StretchBlt(destdc,x+nTotal_Width,y,bx,by,sorDC,0,0,bx,by,SRCCOPY);


    //¿ÞÂÊ Å×µÎ¸®

	for(i=0; i< y_height; i++)
	{
		SelectObject(sorDC, hBox4 );
		GetObject(hBox4,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;
		by = bit.bmHeight;
		nTotal_Height +=by ;
		StretchBlt(destdc,x,y+BOXCORNER_HEIGHT+(by*i),bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}



	
	
	//¿ÞÂÊ BOTTOM 	
	SelectObject(sorDC,hBox7);
	GetObject(hBox7,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;
		
	StretchBlt(destdc,x,y +BOXCORNER_HEIGHT+nTotal_Height,bx,by,sorDC,0,0,bx,by,SRCCOPY);

	for(i=0; i< x_width; i++)
	{
		SelectObject(sorDC,hBox8);
		GetObject(hBox8,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;		
		by = bit.bmHeight;
		StretchBlt(destdc,x+BOXCORNER_WIDTH+(bx*i),y +BOXCORNER_HEIGHT+nTotal_Height,bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}	

	//¿À¸¥ÂÊ BOTTOM
	SelectObject(sorDC,hBox9);
	GetObject(hBox9,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;	
	StretchBlt(destdc,x+nTotal_Width,y +BOXCORNER_HEIGHT+nTotal_Height,bx,by,sorDC,0,0,bx,by,SRCCOPY);	

 
	//¿À¸¥ÂÊ Å×µÎ¸®
	for(i=0; i< y_height; i++)
	{
		SelectObject(sorDC, hBox6 );
		GetObject(hBox6,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;
		by = bit.bmHeight;		
		StretchBlt(destdc,x+nTotal_Width,y+BOXCORNER_HEIGHT+(by*i),bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}


	DeleteDC(sorDC);
	DeleteDC(destdc);

	ReleaseDC(g_hwnd, hdc);


#endif

	return TRUE;
}

void CLAN_MENU::RenderMenu()
{
	/*
	HDC hdc,sorDC;
	HBITMAP oldbmp;

	hdc = GetDC(g_hwnd);
	sorDC  = CreateCompatibleDC(hdc );
	oldbmp = (HBITMAP)SelectObject(sorDC,membmp->membmp);
	BitBlt(hdc,0,0,800,600,sorDC,0,0,SRCCOPY);
	SelectObject(sorDC,oldbmp);	
	DeleteDC(sorDC);
	ReleaseDC(g_hwnd,hdc);
	*/
}
/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º ¸í: class CLAN_MENU
: ÇÏ ´Â ÀÏ : 
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò : À¥db¸¦ »ç¿ëÇØ µ¥ÀÌÅ¸¸¦ »Ì¾Æ³»¾ß ÇÒ°æ¿ì º» Å¬¶ó½º¸¦ ÀÌ¿ëÇÑ´Ù.
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
void CLAN_MENU::Draw_C_menuN()
{		
	cBaseMenu.Draw();
	cClanChip.Draw();	
	cClanUser.Draw();	
	cClanMake.Draw();	
	cClanReport.Draw();
#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
#else
	cClanChatting.Draw();
#endif
	cClanJoin.Draw();
	
}


//=============µå·Î¿ì °ü·Ã ÇÔ¼ö ==================================================================end







/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º ¸í: °èÁ¤¿¡ ¸¸µé¾îÁø Ä³¸¯ÅÍµéÀÌ °¡ÀÔÇÑ Å¬·£À» ¾Ë±â À§ÇØ¼­
: ÇÏ ´Â ÀÏ : 
: ¹Ý È¯ °ª :
///////////////////////////////////////////////////////////////////////////*/
//À¯Àú id, Ä³¸¯ÅÍ id, ±º¼­¹ö ÀÌ¸§.
void SetUserData2(char* id, char* chaname, char* gserver)
{
	strcpy(cldata.szID,  id);
	strcpy(cldata.ChaName, chaname);
	strcpy(cldata.gserver, gserver);
	
}

/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º ¸í: Å¬·£ ½ºÆ®·°Ã³ µ¥ÀÌÅ¸ ¼ÂÆÃ ÇÔ¼öµé
: ÇÏ ´Â ÀÏ : 
: ¹Ý È¯ °ª :
///////////////////////////////////////////////////////////////////////////*/
//À¯Àú id, Ä³¸¯ÅÍ id, ±º¼­¹ö ÀÌ¸§.
void CLAN_MENU::SetUserData(char* id, char* chaname, char* gserver,int money, int ability)
{
	strcpy(cldata.szID,  id);
	strcpy(cldata.ChaName, chaname);
	strcpy(cldata.gserver, gserver);

	cldata.money = money;
	//ktj : ÀÓ½Ã
	//if(cldata.money ==0) cldata.money = 100000;
	cldata.ability = ability;
}



//±ÇÀ¯¸¦ ¹Þ´Â »ç¶÷ÇÑÅ×¿À´Â µ¥ÀÌÅ¸
void CLAN_MENU::SetJoinData(char *joinclanname, char *joinclanchip)
{
	strcpy(cldata.szJoinClanName,    joinclanname);			//°¡ÀÔµÉ Å¬·£ ÀÌ¸§
	strcpy(cldata.szJoinClanChipName,joinclanchip);		//°¡ÀÔµÉ Å¬·£ÀÇ Å¬·£Àå id
}











#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì

void DrawSprite_TJB(int winX ,int winY, int winxlen, int winylen, DIRECTDRAWSURFACE pdds,int x, int y, int width, int height,int Bltflag)
{
	if(!pdds) 
		return;

	//int dx,dy,sx,sy,px,py;
    RECT rcRect;
	RECT dRect;

	dRect.left = winX;
	dRect.right = winX+winxlen;
	dRect.top = winY;
	dRect.bottom = winY+winylen;

	rcRect.top		= 0;
	rcRect.left		= 0;
	rcRect.bottom   = 32;
	rcRect.right    = 32;

	//renderDevice.lpDDSBack->Blt(&dRect, pdds, &rcRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY, NULL);
	renderDevice.Blt(renderDevice.lpDDSBack, &dRect, pdds, &rcRect, DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY, NULL);
}
#endif




#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
#else

void Draw_Text(int x, int y,char *str)
{
	HANDLE hFont,hOldFont;
	HDC hdc;	
	hdc = GetDC(g_hwnd);
    	hFont = CreateFont( 12,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
                        HANGEUL_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
                        "±¼¸²Ã¼" );

	hOldFont = SelectObject(hdc,hFont);
	char strbuf[1024];


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;
	
	while(1)
	{
		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:		
			
			dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	
	//DrawText(GetDC(g_hwnd),string,-1,&rect,DT_LEFT | DT_WORDBREAK);

	SelectObject(hdc,hOldFont);
	DeleteObject(hFont);

	ReleaseDC(g_hwnd,hdc);
	
}
#endif



void Text_Out1(HDC hdc,int x, int y,char *str)
{
}

void Text_Out2(HDC hdc,int x, int y,char *str)
{
}

void Text_Out3(HDC hdc,int x, int y,char *str)
{
}
void Text_Out(HDC hdc,int x, int y,char *str)
{
	HANDLE hFont,hOldFont;

	
    	hFont = CreateFont( 12,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
                        HANGEUL_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
                        "±¼¸²Ã¼" );

	hOldFont = SelectObject(hdc,hFont);
	char strbuf[1024];


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;
	
	while(1)
	{
		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:		
			
			dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	
	//DrawText(GetDC(g_hwnd),string,-1,&rect,DT_LEFT | DT_WORDBREAK);

	SelectObject(hdc,hOldFont);
	DeleteObject(hFont);
	
	
}



void CLAN_MENU::Load()
{
#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì

	MatPartyBackGround =
		CreateTextureMaterial( "image\\Sinimage\\Help\\party_win.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	

	//box===========================================================================start

	hBox1 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxCorner.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox2 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxLine.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox3 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box3.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox4 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box4.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );
	hBox5 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box5.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox6 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box6.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox7 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box7.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox8 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box8.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox9 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box9.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	//box===========================================================================end


	/*
	//ktj : scroll
	hScl_Bar_tj= CreateTextureMaterial( "image\\Sinimage\\Help\\scl_bar.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	hScl_icon_tj = CreateTextureMaterial( "image\\Sinimage\\Help\\scl_icon.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hOk_Gray  = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Ok_Glay.bmp");
	hOk_Yellow= LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Ok_Yellow.bmp");
	//hCancel_Gray = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Cancel_Glay.bmp");
	//hCancel_Yellow = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Cancel_Yellow.bmp");
	hYes_Gray = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Yes_Glay.bmp");
	hYes_Yellow = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_Yes_Yellow.bmp");
	//hNo_Gray = LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_No_Glay.bmp");
	//hNo_Yellow =  LoadDibSurfaceOffscreen("image\\Sinimage\\MessageBox\\Button_No_Yellow.bmp");

	//CLAN CHIP
	//hMark = LoadDibSurfaceOffscreen("image\\Sinimage\\chipbutton\\Mark.bmp");
	hClanName = LoadDibSurfaceOffscreen("image\\Sinimage\\Help\\box-test-title.bmp");
	hWareHouse[0]= LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\whc.bmp");
	hWareHouse[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\whc1.bmp");
	hWHRight[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\whr.bmp");
	hWHRight[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\whr1.bmp");
	//hClanMark[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\m.bmp");
	hClanMark[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\m1.bmp");
	hRemove[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\r.bmp");
	hRemove[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\r1.bmp");
	hClanRelease[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\cr.bmp");
	hClanRelease[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\cr1.bmp");
	hHelp[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\h.bmp");
	hHelp[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\h1.bmp");
	hOut[0] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\o.bmp");
	hOut[1] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\o1.bmp");
	//Å¬·£ ±¸¼º¿ø
	hSecession[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\s.bmp");
	hSecession[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\s1.bmp");
	//Ãß¹æ,Ã¢°í ±ÇÇÑ
	hIcon = LoadDibSurfaceOffscreen("image\\party\\party_man_0.bmp");
	hIcon_Click = LoadDibSurfaceOffscreen("image\\party\\party_man_1.bmp");

										
	hClose[0] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c.bmp");
	hClose[1] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c1.bmp");
	//ÇïÇÁ
	hHelp1 = LoadDibSurfaceOffscreen("image\\Sinimage\\chipbutton\\help1.bmp");


	//hButton_Box = LoadDibSurfaceOffscreen("image\\Sinimage\\Help\\box-test-title2.bmp");
	hClanTitle = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\title.bmp");



	//Ãß¹æ¸Þ´º¾È¿¡¼­ Ãß¹æ ¹öÆ°
	hRemoveToMenu[0]= LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\Button_deport_Glay.bmp");
	hRemoveToMenu[1] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\Button_deport_Yellow.bmp");

	//½ºÅ©·Ñ¹Ù
	hScl_Bar= LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\scl_bar.bmp");
	hScl_icon = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\msBox.bmp");
	
	hClanNameInput = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\clan_name.bmp");

	//====Å¬·£ ¹öÅÏ¼³¸í ºÎºÐ
	hTxt_Remove[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_r_.bmp");

	hTxt_Remove[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_r.bmp");

	hTxt_Release[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_cr_.bmp");

	hTxt_Release[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_cr.bmp");

	hTxt_Mark[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_m_.bmp");

	hTxt_Mark[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_m.bmp");

	hTxt_Help[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_h_.bmp");

	hTxt_Help[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_h.bmp");

	hTxt_Secession[0] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_out_.bmp");

	hTxt_Secession[1] = LoadDibSurfaceOffscreen("image\\clanImage\\chipbutton\\txt_out.bmp");

	*/

#else
	

	MatPartyBackGround = (HBITMAP)LoadImage(
					NULL, 
					"image\\Sinimage\\Help\\box-test-title2.bmp",
					IMAGE_BITMAP,
					0,0,
					LR_LOADFROMFILE);

//box===========================================================================start

	hBox1= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hBox2= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box2.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox3= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box3.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox4= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box4.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hBox6= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box6.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox7= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box7.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hBox8= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box8.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox9= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box9.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	
	
	//box===========================================================================end



	hOk_Gray= (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Ok_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);	

	hOk_Yellow = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Ok_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);


	if(hOk_Yellow == NULL)
	{
		char temp[50];
		wsprintf(temp,"Num : %d",GetLastError());
	}

	hCancel_Gray = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Cancel_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hCancel_Yellow = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Cancel_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hYes_Gray = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Yes_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hYes_Yellow = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Yes_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hNo_Gray = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_No_Glay.bmp",
						IMAGE_BITMAP,	
						0,0,
						LR_LOADFROMFILE);

	hNo_Yellow =  (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_No_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);




	//CLAN CHIP
	//hMark = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\chipbutton\\Mark.bmp",
	//					IMAGE_BITMAP,
	//					0,0,
	//					LR_LOADFROMFILE);
	hClanName = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\Help\\box-test-title.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWareHouse[0]= (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whc.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWareHouse[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whc1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWHRight[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whr.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWHRight[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whr1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanMark[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\m.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanMark[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\m1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hRemove[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\r.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hRemove[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\r1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanRelease[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\cr.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanRelease[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\cr1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hHelp[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\h.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hHelp[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\h1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hOut[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\o.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hOut[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\o1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	//Å¬·£ ±¸¼º¿ø
	hSecession[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\s.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hSecession[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\s1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
//Ãß¹æ,Ã¢°í ±ÇÇÑ
	hIcon = (HBITMAP)LoadImage(NULL,"image\\party\\party_man_0.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hIcon_Click = (HBITMAP)LoadImage(NULL,"image\\party\\party_man_1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
//Ãß¹æ¸Þ´º¾È¿¡¼­ Ãß¹æ ¹öÆ°
	hRemoveToMenu[0]= (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\Button_deport_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hRemoveToMenu[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\Button_deport_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hClose[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\c.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hClose[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\c1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	//ÇïÇÁ
	hHelp1 = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\chipbutton\\help1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hButton_Box = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\msBox.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanTitle = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\title.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hScl_Bar = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\scl_bar.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hScl_icon = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\help\\scl_icon.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	//====Å¬·£ ¹öÅÏ¼³¸í ºÎºÐ
#ifndef _LANGUAGE_BRAZIL //ºê¶óÁú Å¬·£ //ÇØ¿Ü
	hTxt_Remove[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_r_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Remove[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_r.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Release[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_cr_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Release[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_cr.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
#endif

	hTxt_Mark[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_m_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Mark[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_m.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Help[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_h_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Help[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_h.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Secession[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_out_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Secession[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_out.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	


	
	

#endif
}



//simMain.cpp¿¡¼­ ºÒ·¯¼­ Å¬·ÎÁî ÇÑ´Ù.
void clanMENU_close()
{
	Interface_clanmenu.Close();
}

void CLAN_MENU::Close()
{
	#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì

	/*if(	hOk_Gray ) {   hOk_Gray->Release();  hOk_Gray = NULL;}
	if(	hOk_Yellow ) {   hOk_Yellow->Release();  hOk_Yellow= NULL;}
	if(	hCancel_Gray ) {   hCancel_Gray->Release();  hCancel_Gray= NULL;}
	if(	hCancel_Yellow) {   hCancel_Yellow->Release();  hCancel_Yellow= NULL;}
	if(	hYes_Gray ) {   hYes_Gray->Release();  hYes_Gray = NULL;}
	if(	hYes_Yellow ) {   hYes_Yellow->Release();  hYes_Yellow = NULL;}
	if(	hNo_Gray ) {   hNo_Gray->Release();  hNo_Gray = NULL;}
	if(	hNo_Yellow ) {   hNo_Yellow ->Release();  hNo_Yellow = NULL;}

	//CLAN CHIP
	if(	hMark ) {   hMark->Release();  hMark = NULL;}
	if(	hClanName ) {   hClanName->Release();  hClanName = NULL;}
	


	for(int i=0 ; i <2; i++)
	{
		if(hWHRight[i]) { hWHRight[i]->Release(); hWHRight[i]= NULL; } 
		if(hWareHouse[i]) { hWareHouse[i]->Release(); hWareHouse[i] = NULL;}
		if(hClanMark[i]) { hClanMark[i]->Release(); hClanMark[i] = NULL;}
		if(hRemove[i]) { hRemove[i]->Release(); hRemove[i] = NULL;}
		if(hClanRelease[i]) { hClanRelease[i]->Release(); hClanRelease[i] = NULL;}
		if(hHelp[i]) { hHelp[i]->Release(); hHelp[i] = NULL;}	
		if(hOut[i]) { hOut[i]->Release(); hOut[i] = NULL;}	
		if(hClose[i]) { hClose[i]->Release(); hClose[i] = NULL;}	
		if(hSecession[i]) { hSecession[i]->Release(); hSecession[i] = NULL;}	
		if(hTxt_Remove[i]) { hTxt_Remove[i]->Release(); hTxt_Remove[i] = NULL;}	
		if(hTxt_Release[i]) { hTxt_Release[i]->Release(); hTxt_Release[i] = NULL;}	
		if(hTxt_Mark[i]) { hTxt_Mark[i]->Release(); hTxt_Mark[i] = NULL;}	
		if(hTxt_Help[i]) { hTxt_Help[i]->Release(); hTxt_Help[i] = NULL;}	
		if(hTxt_Secession[i]) { hTxt_Secession[i]->Release(); hTxt_Secession[i] = NULL;}
		
		
	}

	//Ãß¹æ
	if(	hIcon ) {   hIcon->Release();  hIcon = NULL;}
	//ÇïÇÁ
	if(	hHelp1 ) {   hHelp1->Release();  hHelp1 = NULL;}

	if(	hButton_Box) {   hClanTitle ->Release();  hClanTitle = NULL;}
	if(	hClanTitle ) {   hClanTitle ->Release();  hClanTitle = NULL;}


	//ygy ½ºÅ©·Ñ
	if(	hScl_Bar) {   hScl_Bar->Release();  hScl_Bar = NULL;}
	if(	hScl_icon ) {   hScl_icon->Release();  hScl_icon = NULL;}

	//ygyÅ¬·£ÀÌ¸§ ÀÔ·Â ÀÌ¹ÌÁö
	if(	hClanNameInput ) {   hClanNameInput->Release();  hClanNameInput = NULL;}*/
	


	if(cldata.hClanMark) { cldata.hClanMark->Release(); cldata.hClanMark = NULL;}
	if(cldata.hClanMark16) {cldata.hClanMark16->Release(); cldata.hClanMark16 = NULL;}

	cClanChatting.Close();
	cBaseMenu.Close();


	#else

	//bitmap¾ø¾Ù°Í.
	DeleteObject( MatPartyBackGround );
//	DeleteObject(hBoxCorner);
//	DeleteObject(hBoxLine);
	//DeleteObject(hBoxLine1);
	DeleteObject(hOk_Gray);
	DeleteObject(hOk_Yellow);
	DeleteObject(hCancel_Gray);
	DeleteObject(hCancel_Yellow);
	DeleteObject(hYes_Yellow);
	DeleteObject(hYes_Gray);
	DeleteObject(hNo_Gray);
	DeleteObject(hNo_Yellow);
	DeleteObject(hMark);
	DeleteObject(hClanName);
	DeleteObject(hScl_Bar);
	DeleteObject(hScl_icon);


	for(int i=0 ; i <2; i++)
	{
		DeleteObject(hWHRight[i]);
		DeleteObject(hWareHouse[i]);
		DeleteObject(hClanMark[i]);
		DeleteObject(hRemove[i]);
		DeleteObject(hClanRelease[i]);
		DeleteObject(hHelp[i]);
		DeleteObject(hOut[i]);
		DeleteObject(hClose[i]);
		DeleteObject(hSecession[i]);
#ifndef _LANGUAGE_BRAZIL //ºê¶óÁú Å¬·£ //ÇØ¿Ü
		DeleteObject(hTxt_Remove[i]);
		DeleteObject(hTxt_Release[i]);
#endif
		DeleteObject(hTxt_Mark[i]);
		DeleteObject(hTxt_Help[i]);
		DeleteObject(hTxt_Secession[i]);
	}
	


	DeleteObject(hIcon);
	DeleteObject(hHelp1);



	#endif
#ifdef VOICE_CHAT
	g_CtrlProcess.Clear();
#endif
}

void CLAN_MENU::Loading()
{
#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
	Draw_C_Text(clanLoading.szMsg, BackStartPos.x + 80,BackStartPos.y + 90);
#else

	HDC hdc, sorDC,destdc;

	hdc = GetDC(g_hwnd);
	sorDC  = CreateCompatibleDC(hdc);
	destdc = CreateCompatibleDC(hdc);
	SelectObject(destdc, Dback.hb );		//off½ºÅ©¸°¼³Á¤.	
//	Text_Out(destdc,BackStartPos.x + 80,BackStartPos.y + 90 ,szLoading);

	DeleteDC(sorDC);
	DeleteDC(destdc);
	ReleaseDC(g_hwnd, hdc );
#endif

}


#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
//Å¬·£¿ø Á¤º¸ Àü¼Û¿ë ÇÔ¼ö
int SendClanCommandUser( smWINSOCK *lpsmSock , DWORD	dwCode , int Param1, int Param2 , CLANWONLIST *lpClanUserList , int ClanUserCount );
#endif


void SetClanWon()
{

	if(cldata.nTotalClanWonCount==0) return;

	memcpy(ClanWonList.clanWon,cldata.clanWon,sizeof(cldata.clanWon));

	

	//========================================================

#ifdef USE_PROSTONTALE		//=========== Æ÷¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì

	//Å¬·£ ¾÷µ¥ÀÌÆ® ¿ä±¸¸¦ ¼­¹ö¿¡ ¾Ë·ÁÁÖ±âÀ§ÇÑ ÇÔ¼ö(Àå¼ø¸ñ½ÇÀå)
	//Å¬·£¿ø Á¤º¸ Àü¼Û¿ë ÇÔ¼ö
	SendClanCommandUser( smWsockDataServer , smTRANSCODE_CLAN_UPDATE  , 0,0, &ClanWonList , cldata.nTotalClanWonCount );

	//========================================================
#endif

}





//savedata\\clanDATA ¸¸µé±â==============================================start
BOOL SearchDirectory(char *dir)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;	
	char t[50];
	wsprintf(t,"%s\\*.*",dir);
	hFind = FindFirstFile(t,&wfd);
	if(hFind == INVALID_HANDLE_VALUE)
	{		
		return FALSE;
	}	

	return TRUE;	
}

void MakeDirectory(char *dir)
{
	CreateDirectory(dir,NULL);
}


void CreateSaveData_dir()
{	
	char szTemp[100];
	if(!SearchDirectory(SAVEDATA_DIR)) MakeDirectory(SAVEDATA_DIR);
	if(!SearchDirectory(CLANDATA_DIR)) MakeDirectory(CLANDATA_DIR);

	ZeroMemory(szTemp,sizeof(szTemp));
	wsprintf(szTemp,"%s",CLANDATA_DIR);
	wsprintf(szTemp,"%s\\%s",szTemp,szConnServerName);

	if(!SearchDirectory(szTemp)) MakeDirectory(szTemp);

}



//savedata\\clanDATA ¸¸µé±â==============================================end

//npcwav µð·ºÅä¸® ¸¸µé±â=========================start

/*void CreateNPCWav_dir()
{
	if(!SearchDirectory(NPCWAV_DIR))
	{
		MakeDirectory(NPCWAV_DIR);
	}
}
*/


//Å¬·£ ¸Þ¼¼Áö Ãâ·ÂÇÏ±â ==========================================================================start
#define CLANMESSAGE_DIR "image/clanImage/Help/clanText.msg"//msg"

int LoadClanMessage()
{
	char *g_ClanMessage;


	HANDLE hFile = NULL;
	DWORD dwFileSize;	
	DWORD dwRead = 0;
	char c;
	c = '\n';
	hFile = CreateFile( CLANMESSAGE_DIR, GENERIC_READ, FILE_SHARE_READ,
                        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL , NULL );

	if(hFile == NULL) return -1;

	dwFileSize = GetFileSize(hFile,NULL);

	g_ClanMessage = new char[dwFileSize];

	ReadFile(hFile,g_ClanMessage,dwFileSize,&dwRead,NULL);
	CloseHandle(hFile);

	int ReadMessage(char *save,char *savename,char *readbuf);
	//void CheckMsgPos(CLANMSG* clanmsg,int width, int height);
	ReadMessage(clanMake1.szMsg,"szMsg1",g_ClanMessage);
	CheckMsgPos(&clanMake1,BOX_MAX_WIDTH,0);
	ReadMessage(clanMake2.szMsg,"szMsg2",g_ClanMessage);
	CheckMsgPos(&clanMake2,BOX_MAX_WIDTH,0);
	ReadMessage(clanMake4.szMsg,"szMsg4",g_ClanMessage);
	CheckMsgPos(&clanMake4,BOX_MAX_WIDTH,0);
	ReadMessage(clanMake5.szMsg,"szMsg5",g_ClanMessage);
	CheckMsgPos(&clanMake5,BOX_MAX_WIDTH,0);
	ReadMessage(clanMake6.szMsg,"szClanMakeFinishMsg",g_ClanMessage);
	CheckMsgPos(&clanMake6,BOX_MAX_WIDTH,0);


	ReadMessage(szMsg3,"szMsg3",g_ClanMessage);
	
	ReadMessage(clanMsg21.szMsg,"szMsg21",g_ClanMessage);
	CheckMsgPos(&clanMsg21,BOX_MAX_WIDTH,0);	
	
	ReadMessage(clanMsg254.szMsg,"szMsg254",g_ClanMessage);  //CLAN_NotMake
	CheckMsgPos(&clanMsg254,BOX_MAX_WIDTH,0);	
	ReadMessage(clanMsg15.szMsg,"szMsg15",g_ClanMessage);
	CheckMsgPos(&clanMsg15,BOX_MAX_WIDTH,0);	  //CLAN_RELEASE
	ReadMessage(clanJoin.szMsg,"szJoin",g_ClanMessage); //CLAN_JOIN
	CheckMsgPos(&clanJoin,BOX_MAX_WIDTH,0);	
	ReadMessage(clanSecession.szMsg,"szSecession",g_ClanMessage); //CLAN_SECESSION
	CheckMsgPos(&clanSecession,BOX_MAX_WIDTH,0);
	ReadMessage(clanServerConnectErrorMsg.szMsg,"szServerConnectErrorMsg",g_ClanMessage);
	CheckMsgPos(&clanServerConnectErrorMsg,BOX_MAX_WIDTH,0);            //ISAO_ERR_TCP_CONNECT
	ReadMessage(clanszError_Msg.szMsg,"szError_Msg",g_ClanMessage); //ISAO_ERR_TCP_CONNECT
	CheckMsgPos(&clanszError_Msg,BOX_MAX_WIDTH,0);
	ReadMessage(clanCancelMakeClan.szMsg,"szCancelMakeClan",g_ClanMessage);
	CheckMsgPos(&clanCancelMakeClan,BOX_MAX_WIDTH,0);
	ReadMessage(clanClanNameError.szMsg,"szClanNameError",g_ClanMessage);
	CheckMsgPos(&clanClanNameError,BOX_MAX_WIDTH,0);

	
	//ReadMessage(szClanMakeFinishMsg,"szClanMakeFinishMsg",g_ClanMessage);
	//ReadMessage(szMsg254,"szMsg254",g_ClanMessage);
	//ReadMessage(szMsg15,"szMsg15",g_ClanMessage);
	//ReadMessage(szMark1,"szMark1",g_ClanMessage);
	//ReadMessage(szMark2,"szMark2",g_ClanMessage);
	//ReadMessage(szMark3,"szMark3",g_ClanMessage);
	//ReadMessage(szJoin,"szJoin",g_ClanMessage);
	//ReadMessage(szSecession,"szSecession",g_ClanMessage);

	//ReadMessage(szMsg6,"szMsg6",g_ClanMessage);
	//ReadMessage(szServerConnectErrorMsg,"szServerConnectErrorMsg",g_ClanMessage);
	//ReadMessage(szReadClanMarkErrorMsg,"szReadClanMarkErrorMsg",g_ClanMessage);
	//ReadMessage(szCancelMakeClan,"szCancelMakeClan",g_ClanMessage);
	//ReadMessage(szTranzationError,"szTranzationError",g_ClanMessage);
	//ReadMessage(szInsertClanWonError1,"szInsertClanWonError1",g_ClanMessage);
	//ReadMessage(szClanNameError,"szClanNameError",g_ClanMessage);
	//ReadMessage(sz100Error,"sz100Error",g_ClanMessage);
	//ReadMessage(szDefaultError,"szDefaultError",g_ClanMessage);
	//ReadMessage(szReleseError,"szReleseError",g_ClanMessage);
	//ReadMessage(szSecessionSuccess,"szSecessionSuccess",g_ClanMessage);
	//ReadMessage(szSecession6DownMsg,"szSecession6DownMsg",g_ClanMessage);clanSecession6DownMsg
	ReadMessage(clanSecession6DownMsg.szMsg,"szSecession6DownMsg",g_ClanMessage);  //CLAN_DELETECHA_SECESSION
	CheckMsgPos(&clanSecession6DownMsg,BOX_MAX_WIDTH,0);
	//ReadMessage(szSecessionChipMsg,"szSecessionChipMsg",g_ClanMessage);
	//ReadMessage(szSecession2ErrorMsg,"szSecession2ErrorMsg",g_ClanMessage);
	//ReadMessage(szClanJoinMsg,"szClanJoinMsg",g_ClanMessage);
	ReadMessage(clanClanJoinMsg.szMsg,"szClanJoinMsg",g_ClanMessage);
	CheckMsgPos(&clanClanJoinMsg,BOX_MAX_WIDTH,0);

	//ReadMessage(szClanJoinError2Msg,"szClanJoinError2Msg",g_ClanMessage);
	//ReadMessage(szClanJoinError3Msg,"szClanJoinError3Msg",g_ClanMessage);
	//ReadMessage(szClanJoinError4Msg,"szClanJoinError4Msg",g_ClanMessage);
	//ReadMessage(szClanJoinCancelMsg,"szClanJoinCancelMsg",g_ClanMessage);CLANMSG clanClanJoinCancelMsg;
	ReadMessage(clanClanJoinCancelMsg.szMsg,"szClanJoinCancelMsg",g_ClanMessage);
	CheckMsgPos(&clanClanJoinCancelMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanJoinsucesssMsg.szMsg,"szClanJoinsucesssMsg",g_ClanMessage);
	CheckMsgPos(&clanClanJoinsucesssMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanszReMoveClanWonMsg.szMsg,"szReMoveClanWonMsg",g_ClanMessage);
	CheckMsgPos(&clanszReMoveClanWonMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanReMoveHeaderMsg.szMsg,"szReMoveHeaderMsg",g_ClanMessage);
	CheckMsgPos(&clanReMoveHeaderMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanszReConfReleaseMsg.szMsg,"szReConfReleaseMsg",g_ClanMessage);
	CheckMsgPos(&clanszReConfReleaseMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanNoRecordReleaseMsg.szMsg,"szNoRecordReleaseMsg",g_ClanMessage);
	CheckMsgPos(&clanNoRecordReleaseMsg,BOX_MAX_WIDTH,0);

	//ReadMessage(szFinishReleaseMsg,"szFinishReleaseMsg",g_ClanMessage);clanFinishReleaseMsg
	ReadMessage(clanFinishReleaseMsg.szMsg,"szFinishReleaseMsg",g_ClanMessage);
	CheckMsgPos(&clanFinishReleaseMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanSecessionMsg.szMsg,"szSecessionMsg",g_ClanMessage);
	CheckMsgPos(&clanSecessionMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanFinishSecessionMsg.szMsg,"szFinishSecessionMsg",g_ClanMessage);
	CheckMsgPos(&clanFinishSecessionMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanisCheckClanJangErrorMsg.szMsg,"szisCheckClanJangErrorMsg",g_ClanMessage);
	CheckMsgPos(&clanisCheckClanJangErrorMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanMoneyErrorMsg.szMsg,"szMoneyErrorMsg",g_ClanMessage);
	CheckMsgPos(&clanMoneyErrorMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanAbilityErrorMsg.szMsg,"szAbilityErrorMsg",g_ClanMessage);
	CheckMsgPos(&clanAbilityErrorMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanszRemoveShortClanWonMsg.szMsg,"szRemoveShortClanWonMsg",g_ClanMessage);
	CheckMsgPos(&clanszRemoveShortClanWonMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanRemoveShowrtClanWonResultMsg.szMsg,"szRemoveShowrtClanWonResultMsg",g_ClanMessage);
	CheckMsgPos(&clanRemoveShowrtClanWonResultMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanNoName.szMsg,"szNoName",g_ClanMessage);
	CheckMsgPos(&clanNoName,BOX_MAX_WIDTH,0);

	ReadMessage(clanLoading.szMsg,"szLoading",g_ClanMessage);
	CheckMsgPos(&clanLoading,BOX_MAX_WIDTH,0);

	ReadMessage(clanMsg6.szMsg,"szMsg6",g_ClanMessage);
	CheckMsgPos(&clanMsg6,BOX_MAX_WIDTH,0);

	
	
	/////////Ä³¸¯ÅÍ »èÁ¦ ¸Þ¼¼Áö
	ReadMessage(szDeleteChaReleaseBefore,"szDeleteChaReleaseBefore",g_ClanMessage);
	ReadMessage(szDeleteChaReleaseFinish,"szDeleteChaReleaseFinish",g_ClanMessage);
	ReadMessage(szDeleteChaSecessionBefore,"szDeleteChaSecessionBefore",g_ClanMessage);
	ReadMessage(szDeleteChaSecessionFinish,"szDeleteChaSecessionFinish",g_ClanMessage);
	//ReadMessage(szDeleteChaError,"szDeleteChaError",g_ClanMessage);
	
	ReadMessage(clanDeleteChaError.szMsg,"szDeleteChaError",g_ClanMessage);
	CheckMsgPos(&clanDeleteChaError,BOX_MAX_WIDTH,0);
	
	ReadMessage(clanMakeFinishClan.szMsg,"szMakeFinishClan",g_ClanMessage);
	CheckMsgPos(&clanMakeFinishClan,BOX_MAX_WIDTH,0);


	ReadMessage(szClanWon6Down,"szClanWon6Down",g_ClanMessage);

	ReadMessage(clanClanUserNoMakeMsg.szMsg,"szClanUserNoMakeMsg",g_ClanMessage);
	CheckMsgPos(&clanClanUserNoMakeMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanMakeFinishClanWon.szMsg,"szMakeFinishClanWon",g_ClanMessage);
	CheckMsgPos(&clanMakeFinishClanWon,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanServerInspect.szMsg,"ClanServerInspect",g_ClanMessage);
	CheckMsgPos(&clanClanServerInspect,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanUserRelease.szMsg,"szClanUserRelease",g_ClanMessage);
	CheckMsgPos(&clanClanUserRelease,BOX_MAX_WIDTH,0);


	//ReadMessage(Replay,"Replay",g_ClanMessage);

	ReadMessage(clanClanMakedowninfo.szMsg,"szClanMakedowninfo",g_ClanMessage);
	CheckMsgPos(&clanClanMakedowninfo,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanUserReleaseMsg.szMsg,"szClanUserReleaseMsg",g_ClanMessage);
	CheckMsgPos(&clanClanUserReleaseMsg,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanUserRemove.szMsg,"szClanUserRemove",g_ClanMessage);
	CheckMsgPos(&clanClanUserRemove,BOX_MAX_WIDTH,0);

	ReadMessage(clanClanWonOver.szMsg,"szClanWonOver",g_ClanMessage);
	CheckMsgPos(&clanClanWonOver,BOX_MAX_WIDTH,0);

	//ReadMessage(szError_Msg,"szError_Msg",g_ClanMessage);
	ReadMessage(clanMsg7.szMsg,"szMsg7",g_ClanMessage);
	CheckMsgPos(&clanMsg7,BOX_MAX_WIDTH,0);

	ReadMessage(clanNoLevel.szMsg,"szNoLevel",g_ClanMessage);
	CheckMsgPos(&clanNoLevel,BOX_MAX_WIDTH,0);

	ReadMessage(clanRemoveSecond.szMsg,"szRemoveSecond",g_ClanMessage);
	CheckMsgPos(&clanRemoveSecond,BOX_MAX_WIDTH,0);

	ReadMessage(clanRemoveSecondResult.szMsg,"szRemoveSecondResult",g_ClanMessage);
	CheckMsgPos(&clanRemoveSecondResult,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanConfirm.szMsg,"szLeaveClanConfirm",g_ClanMessage);
	CheckMsgPos(&LeaveClanConfirm,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanNoMoney.szMsg,"szLeaveClanNoMoney",g_ClanMessage);
	CheckMsgPos(&LeaveClanNoMoney,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanSuccess.szMsg,"szLeaveClanSuccess",g_ClanMessage);
	CheckMsgPos(&LeaveClanSuccess,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanNoLevel.szMsg,"szLeaveClanNoLevel",g_ClanMessage);
	CheckMsgPos(&LeaveClanNoLevel,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanReConfirm.szMsg,"szLeaveClanReConfirm",g_ClanMessage);
	CheckMsgPos(&LeaveClanReConfirm,BOX_MAX_WIDTH,0);

	ReadMessage(NoLeaveClan.szMsg,"szNoLeaveClan",g_ClanMessage);
	CheckMsgPos(&NoLeaveClan,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanMessage.szMsg,"szLeaveClanMessage",g_ClanMessage);
	CheckMsgPos(&LeaveClanMessage,BOX_MAX_WIDTH,0);

	ReadMessage(LeaveClanDownLevel.szMsg,"szLeaveClanDownLevel",g_ClanMessage);
	CheckMsgPos(&LeaveClanDownLevel,BOX_MAX_WIDTH,0);

	ReadMessage(SubChipAppoint.szMsg,"szSubChipAppoint",g_ClanMessage);
	CheckMsgPos(&SubChipAppoint,BOX_MAX_WIDTH,0);

	ReadMessage(SubChipAppointEnd.szMsg,"szSubChipAppointEnd",g_ClanMessage);
	CheckMsgPos(&SubChipAppointEnd,BOX_MAX_WIDTH,0);

	ReadMessage(SubChipRelease.szMsg,"szSubChipRelease",g_ClanMessage);
	CheckMsgPos(&SubChipRelease,BOX_MAX_WIDTH,0);

	ReadMessage(SubChipReleaseEnd.szMsg,"szSubChipReleseEnd",g_ClanMessage);
	CheckMsgPos(&SubChipReleaseEnd,BOX_MAX_WIDTH,0);

	ReadMessage(NoSubChip.szMsg,"szNoSubChip",g_ClanMessage);
	CheckMsgPos(&NoSubChip,BOX_MAX_WIDTH,0);
	

	//È£µ¿ClanÃß°¡
	ReadMessage(ClanIs4DayCheckMsg.szMsg,"szClanIs4DayCheckMsg",g_ClanMessage);
	CheckMsgPos(&ClanIs4DayCheckMsg,BOX_MAX_WIDTH,0);






	delete[] g_ClanMessage;
	g_ClanMessage = NULL;
	return 1;
}

int ReadMessage(char *save,char *savename,char *readbuf)
{
	char szTemp[256];
	char *pBuf;
	char szReadData[1024];
	int nCount =0;
	int nCount1 =0;
	BOOL bFlag = FALSE;

	ZeroMemory(szReadData,sizeof(szReadData));
	wsprintf(szTemp,"*%s",savename);

	pBuf = strstr(readbuf,szTemp);
    if( pBuf == NULL)	//¹ß°ßÇÒ ¼ö ¾ø¾ú´Ù.
	{
		return -1;
	}	

	pBuf = pBuf + strlen(szTemp) + 2;
	nCount = (int)(pBuf - readbuf);

	if(readbuf[nCount] == 0x0a){
		nCount++;
	}

	//DRZ_EDIT (prevent buffer overrun)
	while (nCount < (int)strlen(szReadData))
	{		
		if((readbuf[nCount] == 0x5c)) 
		{				
			szReadData[nCount1] = '\n';		
			nCount1++;				
			nCount +=3;			
			if(readbuf[nCount] == 0x0a)
			{	
				nCount++;
				continue;
			}			
			
		}
		if((readbuf[nCount] == 0x0d) ||(readbuf[nCount] == 0x0a)) break;
		szReadData[nCount1] = readbuf[nCount];		
		nCount++;
		nCount1++;
		
	}

	strcpy(save,szReadData);
	return 1;
}



//xsu´Â ¿©·¯°³ÀÇ xÃàÁß ÃÖ´ë±æÀÌÀÓ.
void MsgXsu_Ysu(CLANMSG* clanmsg, int *xsu, int *ysu)
{
	char strbuf[256], strbuf2[256];
	ZeroMemory(strbuf, sizeof(strbuf));

	int nCount = 0;
	int maxXsu = 0;
	int cntX= 0, cntY = 0;

	while(1)
	{
		strbuf[cntX] = clanmsg->szMsg[nCount];

		if(clanmsg->szMsg[nCount] =='\n')			//ÇÑÁÙÀÇ ³¡
		{
			strbuf[cntX] = 0;
			if(cntX>maxXsu) {
				maxXsu = cntX;
				strcpy(strbuf2, strbuf);
			}

			cntY++;
			cntX = -1;
		}

		if(clanmsg->szMsg[nCount] ==0x00)//0x0d)			//³¡
		{
			strbuf[cntX] = 0;
			if(cntX>maxXsu) {
				maxXsu = cntX;
				strcpy(strbuf2, strbuf);
			}
			cntY++;
			break;
		}

		
		cntX++;
		nCount+=1;
	}

	*xsu = maxXsu;
	*ysu = cntY ;
}



void CheckMsgPos(CLANMSG* clanmsg,int width, int height)
{
	int nCount = 0;
	int nXMax = 0,nYMax;	
	int nX = 0;
	//nX = (((4 * BOXCENTER_WIDTH) + (2*BOXCORNER_WIDTH) + 5) ); //261ÀÌ ¹Ú½ºÀÇ x±æÀÌ
	nX = width; //261ÀÌ ¹Ú½ºÀÇ x±æÀÌ
	nX = nX/2;
	int nY = 40;

	MsgXsu_Ysu(clanmsg, &nXMax, &nYMax);
	int strDotlen = nXMax*6;     //½ºÆ®¸µ ÇÑ¹ÙÀÌÆ®ÀÇ µµÆ®¼ö´Â 6dot
	strDotlen /= 2;

	if(nYMax == 1) nY = 80;
	if(nYMax == 2 ) nY = 60;

	clanmsg->pos.x = (nX - strDotlen);
	clanmsg->pos.y = nY;
}



int g_nCount = 0;
void DebugMessage(char* msg,...)
{
#define DEBUG_MSG_MAX 4096
	HANDLE hFile;
	char buff[DEBUG_MSG_MAX];
	char szDebugMsg[5120];
	DWORD dwWrite =0;
	int nMsgStrOver = 0;
	SYSTEMTIME	SystemTime;	

	
    va_list args;

    va_start( args, msg );
    vsprintf( buff, msg, args );
    va_end( args );

	

    //strcat( buff, "\r\n" );

	GetLocalTime(&SystemTime);	

	hFile = CreateFile( "ClanDebug.txt", GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
							NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	
	wsprintf(szDebugMsg,"%d.%d³â%d¿ù%dÀÏ : %s\r\n",g_nCount++,
		SystemTime.wYear,SystemTime.wMonth,SystemTime.wDay,buff);
	

	if( hFile != INVALID_HANDLE_VALUE ) {
		SetFilePointer( hFile , 0 , NULL , FILE_END );
		
		WriteFile( hFile , szDebugMsg , lstrlen(szDebugMsg) , &dwWrite , NULL );		
		if(lstrlen(buff) > DEBUG_MSG_MAX -2)
		{
			SetFilePointer( hFile , 0 , NULL , FILE_END );
			char szMsg[256] = "..\n¸Þ½ÃÁö°¡ ³Ê¹«±æ¾î¼­ Àß¶úÀ½";
			WriteFile( hFile , szMsg, lstrlen(szMsg) , &dwWrite , NULL );
		}
		
		
		
	}
			

	if(hFile) CloseHandle(hFile);
}

//#define DEBUGOPTION  "image\\clanimage\\help\\clan.inf"
#define DEBUGOPTION  "DDD2.txt"
BOOL	g_bDebugOption  = FALSE;
void ReadWEBDebugOption()
{
	HANDLE hFile = NULL;
	DWORD dwRead;
	char DebugOption;
	hFile = CreateFile( DEBUGOPTION, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
							
	if( hFile != INVALID_HANDLE_VALUE ) {
		ReadFile(hFile,&DebugOption,1,&dwRead,NULL);
		CloseHandle(hFile);

		DebugOption = '1';
	}
	else {
		//ÆÄÀÏÀÌ ¾øÀ¸¸é µð¹ö±ë ¾ÈÇÑ´Ù.
		//hFile = CreateFile( DEBUGOPTION, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
		//					NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
		//WriteFile(hFile,&DebugOption,1,&dwRead,NULL);
		//CloseHandle(hFile);
		DebugOption = '0';
	}
	if (DebugOption == '1') {
		g_bDebugOption = TRUE;
	}
	else {
		g_bDebugOption = FALSE;
	}
}

