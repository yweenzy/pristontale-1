/* 10
 * auth.cpp
 * ISAO ¶ó´Â ÀÎÁõÀ» ÇÏ´Â ½º·¹µå   
 *
 */
#define __AUTH_CPP__

#include <windowsx.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "sinbaram\\sinLinkHeader.h"

#pragma comment(lib,"ws2_32.lib")



#include "../clanmenu/tjclanDEF.h"

#ifdef USE_PROSTONTALE		//=========== ÇÁ¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì

	#include "sinbaram\\SinLinkHeader.h"
	#include "HoBaram\\HoLinkHeader.h"
	#include "Language\\language.h"
	#include "HoBaram\\HoTextFile.h"
	#include "..\\clanmenu\\cE_CViewClanInfo.h"


#endif
#include "..\\clanmenu\\tjclanDEF.h"
#include "..\\clanmenu\\tjclan.h"


#include "auth.h"
#include "isaocheck.h"

extern char szConnServerName[16];

void fd( char *fmt, ...);
void fd2( char *fmt, ...);


BOOL workfound;		//ÀÏÇÒ°Ô ¾øÀ¸¸é 0ÀÓ.


int AUTH_QUE_nums=0;			//Å¥ °¹¼ö³ÖÀ½.
CRITICAL_SECTION g_cs;

AUTH_QUE *AUTH_que;
AUTHLINKTBL aAuthLinkTbl[AUTHLINKTBL_MAX];

DWORD WINAPI AUTH_MainLoop(void* pVoid);

static BOOL AUTH_proc( int mode, int quenum, int threadindex);


//ktj : Å¬·£ ¸â¹öÀÎÁö ¾Ë¾Æ³½´Ù.  : AUTH_QUE_CMD_CL_MAKE
int AUTH_proc_isClanMember( int quenum, int threadindex);
int AUTH_proc_isClanMember_Result( int quenum, int threadindex);

//ktj : Å¬·£ ¸¸µé±â : AUTH_QUE_CMD_CL_MAKE
int AUTH_proc_ClanMake( int quenum, int threadindex);
int AUTH_proc_ClanMake_Result( int quenum, int threadindex);
//ktj : Å¬·£ ¸â¹ö ¸¸µé±â : AUTH_QUE_CMD_CL_MEMBER_MAKE
int AUTH_proc_Mmake( int quenum, int threadindex);
int AUTH_proc_Mmake_Result( int quenum, int threadindex);

//ktj : Å¬·£µ¥ÀÌÅ¸¸¦ ÀÐ´Â´Ù. : AUTH_QUE_CMD_CL_MEMBER_MAKE
int AUTH_proc_ReadClan( int quenum, int threadindex);
int AUTH_proc_ReadClan_Result( int quenum, int threadindex);


//ktj : Å¬·£À» ÇØÃ¼ÇÑ´Ù.    AUTH_QUE_CMD_BreakUP
int AUTH_proc_BreakUP( int quenum, int threadindex);
int AUTH_proc_BreakUP_Result( int quenum, int threadindex);


//ktj : Æ¯Á¤¾Æµð Ãß¹æ.    AUTH_QUE_CMD_BreakUP
int AUTH_proc_Banishiment( int quenum, int threadindex);
int AUTH_proc_Banishiment_Result( int quenum, int threadindex);

//ktj : Ã¢°í±ÇÇÑ.    AUTH_QUE_CMD_WarhouseR
int AUTH_proc_WarhouseR( int quenum, int threadindex);
int AUTH_proc_WarhouseR_Result( int quenum, int threadindex);


//ktj :Å¬·£°á¼º ¿Ï·á¿ë AUTH_QUE_CMD_updateFlag
int AUTH_proc_updateFlag( int quenum, int threadindex);
int AUTH_proc_updateFlag_Result( int quenum, int threadindex);



//ktj :Å¬·£Å»Åð AUTH_QUE_CMD_Secession
int AUTH_proc_Secession( int quenum, int threadindex);
int AUTH_proc_Secession_Result( int quenum, int threadindex);



//ktj :Å¬·£¸¶Å©ÀÐ±â AUTH_QUE_CMD_MarkREAD
int AUTH_proc_MarkREAD( int quenum, int threadindex);
int AUTH_proc_MarkREAD_Result( int quenum, int threadindex);

//ygy : ´Ù¸¥ Å¬·£¸¶Å©ÀÐ±â

int AUTH_proc_MarkREAD2( int quenum, int threadindex);
int AUTH_proc_MarkREAD2_Result( int quenum, int threadindex);

//ygy : °èÁ¤ÀÌ Å¬·£ÀåÀ¸·Î µî·ÏµÇ¾î ÀÖ´ÂÁö Ã¼Å©
int AUTH_proc_isCheckClanJang( int quenum, int threadindex);
int AUTH_proc_isCheckClanJang_Result( int quenum, int threadindex);

//ygy : Å¬·£ÀÌ¸§ÀÌ Áßº¹µÇ¾ú´ÂÁö Ã¼Å©
int AUTH_proc_isCheckClanName( int quenum, int threadindex);
int AUTH_proc_isCheckClanName_Result( int quenum, int threadindex);

//ygy : ÃÊ±â È­¸é °ü·Ã ÇÃ·¡±×
int AUTH_proc_isPFlag( int quenum, int threadindex);
int AUTH_proc_isPFlag_Result( int quenum, int threadindex);

//ygy :ÀÌÀÓ°ü·Ã ÇÃ·¡±×
int AUTH_proc_isKPFlag( int quenum, int threadindex);
int AUTH_proc_isKPFlag_Result( int quenum, int threadindex);

//ygy : Å¬·£¸¶Å©¹øÈ£·Î Å¬·£ Á¤º¸ °®¾î¿À±â
int AUTH_proc_ReadClanInfo( int quenum, int threadindex);
int AUTH_proc_ReadClanInfo_Result( int quenum, int threadindex);

//ygy : cldata ¾÷µ¥ÀÌÆ®
int AUTH_proc_Updatcldata( int quenum, int threadindex);
int AUTH_proc_Updatcldata_Result( int quenum, int threadindex);
//ygy : notice
int AUTH_proc_ReadNotice( int quenum, int threadindex);
int AUTH_proc_ReadNotice_Result( int quenum, int threadindex);

//ÀÌÀÓ
int AUTH_proc_LeaveClan( int quenum, int threadindex);
int AUTH_proc_LeaveClan_Result( int quenum, int threadindex);

//ºÎÅ¬·£Àå ÀÓ¸í
int AUTH_proc_AppointSubChip( int quenum, int threadindex);
int AUTH_proc_AppointSubChip_Result( int quenum, int threadindex);

//ºÎÅ¬·£Àå ÇØÀÓ
int AUTH_proc_ReleaseSubChip( int quenum, int threadindex);
int AUTH_proc_ReleaseSubChip_Result( int quenum, int threadindex);

//WavÆÄÀÏ °¡Á®¿À±â
int AUTH_proc_GetWavFile( int quenum, int threadindex);
int AUTH_proc_GetWavFile_Result( int quenum, int threadindex);





//È£µ¿ClanÃß°¡
int AUTH_proc_sodindex( int quenum, int threadindex);
int AUTH_proc_sodindex_Result( int quenum, int threadindex);

//È£µ¿ClanÃß°¡
int AUTH_proc_isCheckClanMember(int quenum, int threadindex);
int AUTH_proc_isCheckClanMember_Result(int quenum, int threadindex);

// function jump table
typedef int (*FUNC)( int, int);
FUNC AUTH_proc_jmptbl[][AUTH_QUE_CMD_ALLNUM] = //3
{	
	{
		NULL,						// AUTH_QUE_COMMAND_NONE,
		AUTH_proc_isClanMember,
		AUTH_proc_ClanMake,			//Å¬·£ ¸¸µé±â
		AUTH_proc_Mmake,			//Å¬·£ ¸â¹ö¸¸µé±â
		AUTH_proc_ReadClan,			//Å¬·£µ¥ÀÌÅ¸¸¦ ÀÐ´Â´Ù.
		AUTH_proc_BreakUP,			//Å¬·£À» ÇØÃ¼ÇÑ´Ù.
		AUTH_proc_Banishiment,		//Å¬·£¿øÃß¹æ
		AUTH_proc_WarhouseR,
		AUTH_proc_updateFlag,		//Å¬·£ÀÌ ¿ÏÀü°á¼ºµÈ°ÍÀ¸·Î ¾÷µ¥ÀÌÆ®µÊ.

		AUTH_proc_Secession,		//Å¬·£Å»Åð
		

		AUTH_proc_MarkREAD,
		AUTH_proc_isCheckClanJang,		//Å¬·£Â¯ µî·ÏµÇ¾î ÀÖ´ÂÁö Ã¼Å©
		AUTH_proc_isCheckClanName,      //Å¬·£ÀÌ¸§ Áßº¹ÀÎÁö Ã¼Å©
		AUTH_proc_isPFlag,		     //ÃÊ±âÈ­¸é ÇÃ·¡±×
		AUTH_proc_ReadClanInfo,
		AUTH_proc_MarkREAD2,
		AUTH_proc_Updatcldata,
		AUTH_proc_ReadNotice,
		AUTH_proc_LeaveClan,
		AUTH_proc_isKPFlag, //ÀÌÀÓ°ü·Ã ÇÃ·¡±×
		AUTH_proc_AppointSubChip,//ºÎÅ¬·£Àå ÀÓ¸í
		AUTH_proc_ReleaseSubChip,//ºÎÅ¬·£Àå ÇØÀÓ
		AUTH_proc_GetWavFile,//wavÆÄÀÏ °¡Á®¿À±â
		AUTH_proc_sodindex,
		AUTH_proc_isCheckClanMember, //È£µ¿ClanÃß°¡
		
	},
	{
		NULL,
		AUTH_proc_isClanMember_Result,
		AUTH_proc_ClanMake_Result,		//½ÃÀÛ result
		AUTH_proc_Mmake_Result,		//³¡   result
		AUTH_proc_ReadClan_Result,			//Å¬·£µ¥ÀÌÅ¸¸¦ ÀÐ´Â´Ù.
		AUTH_proc_BreakUP_Result,
		AUTH_proc_Banishiment_Result,
		AUTH_proc_WarhouseR_Result,
		AUTH_proc_updateFlag_Result,

		AUTH_proc_Secession_Result,	//Å¬·£Å»Åð
		
		AUTH_proc_MarkREAD_Result,
		AUTH_proc_isCheckClanJang_Result,
		AUTH_proc_isCheckClanName_Result,      //Å¬·£ÀÌ¸§ Áßº¹ÀÎÁö Ã¼Å©
		AUTH_proc_isPFlag_Result,
		AUTH_proc_ReadClanInfo_Result,
		AUTH_proc_MarkREAD2_Result,
		AUTH_proc_Updatcldata_Result,
		AUTH_proc_ReadNotice_Result,
		AUTH_proc_LeaveClan_Result,
		AUTH_proc_isKPFlag_Result,
		AUTH_proc_AppointSubChip_Result, //ºÎÅ¬·£Àå ÀÓ¸í
		AUTH_proc_ReleaseSubChip_Result,//ºÎÅ¬·£Àå ÇØÀÓ
		AUTH_proc_GetWavFile_Result,//WavÆÄÀÏ °¡Á®¿À±â
		AUTH_proc_sodindex_Result,
        AUTH_proc_isCheckClanMember_Result, //È£µ¿ClanÃß°¡
	}
};

//ktj : AUTH_proc_jmptbl[mode][command]·Î »ç¿ëµÇ¸ç
//		¸ðµå´Â 0:ÀÎÁõ, 1Àº ÀÎÁõÈÄ ¸®ÅÏ°ª¿¡ ´ëÇÑ ÇÔ¼ö¿¡ Á¢±ÙÇØ »ç¿ëµÊ.
//		¿¹)ÀÎÁõ ½Ã		AUTH_proc_jmptbl[0][AUTH_QUE_COMMAND_AUTH]»ç¿ë
//			ÀÎÁõ¸®ÅÏÈÄ 	AUTH_proc_jmptbl[1][AUTH_QUE_COMMAND_AUTH]»ç¿ë



//AUTH_QUE °ü·Ã µ¥ÀÌÅ¸ Ã³¸®ÇÔ¼ö ======================================
int AUTH_QUE_AppendTail( AUTH_QUE *pNow, int type );
AUTH_QUE*  AUTH_QUE_getTop( int type );
int AUTH_QUE_Remove( AUTH_QUE *pNow );
int AUTH_QUE_Count( int type );
int AUTH_addQue( AUTH_QUE *que);


// AUTH DB Å¥ ¸µÅ© Å×ÀÌºíÀÇ ¸ÇµÚ¿¡ ÇÑ°³ Ãß°¡£®
int AUTH_QUE_AppendTail( AUTH_QUE *pNow, int type )
{	
	AUTH_QUE *pOldTail;
	// °¡Àå ÃÖÈÄÀÇ ÇÑ °³ Àü£®ÀÌ°Í µÚ¿¡ Ãß°¡ÇÑ´Ù£®
	pOldTail = aAuthLinkTbl[type].QueTail.pPrev;
	// ±Ý ÃÖÈÄÀÌ¿´´Ù³ª »Ô ´ÙÀ½Àº ÀÚ½Å
	pOldTail->pNext = pNow;

	// ÃÖÈÄÀÇ ÇÑ °³ÀüÀ» ÀÚ½Å¿¡°Ô ÇÑ´Ù£®
	aAuthLinkTbl[type].QueTail.pPrev = pNow;

	// ÀÚ½ÅÀÇ ÇÑ °³ÀüÀº ±Ý ÃÖÈÄÀÌ¿´´Ù³ª ³ª·çÅÍ£®
	pNow->pPrev = pOldTail;
	// ÀÚ½ÅÀÇ ´ÙÀ½Àº °¡Àå ÃÖÈÄ
	pNow->pNext = &aAuthLinkTbl[type].QueTail;

	return TRUE;
}


// DB Å¥ ¸µÅ© Å×ÀÌºíÀÇ ¼±µÎ¸¦ µ¹·Á ÁØ´Ù£®
AUTH_QUE*  AUTH_QUE_getTop( int type )
{
	// MUTEX LOCK

	// Åé¿¡ ¿¬°áµÇ°íªë ³²ÀÚ ÇÏÀÎÀ» Á¶»çÇÑ´Ù£®
	// ±×°ÍÀº ÃÖÈÄ ²¿¸®ÀÌ¿´´Ù£®ªÀªÃ ´ë±¸ ¾Æ¹«°Íµµ ¾ø´Ù£®
	if( aAuthLinkTbl[type].QueTop.pNext == &aAuthLinkTbl[type].QueTail ){
		return NULL;
	}

	// ÀÌ°ÍÀÌ´Ù£®
	return aAuthLinkTbl[type].QueTop.pNext;
}

// ¸µÅ©¿¡¼­´Â µÎ µ¿¹°ÀÌ ½¬´Â Àå¼Ò£®
int AUTH_QUE_Remove( AUTH_QUE *pNow )
{
	AUTH_QUE *pOldNext, *pOldPrev;

	// ÀÚ½ÅÀÇ ÀüÈÄ¸¦ ±â¾ïÇÑ´Ù£®
	pOldNext = pNow->pNext;
	pOldPrev = pNow->pPrev;
	// ÀüÈÄ¸¦ Áö¿ö ¾ø¾Ø´Ù£®
	pNow->pNext = NULL;
	pNow->pPrev = NULL;
	// ¿¬°áÇÒÁö ¾ò´Â´Ù£®
	pOldNext->pPrev = pOldPrev;
	pOldPrev->pNext = pOldNext;

	return TRUE;
}

// ¸µÅ©¸¦ ¼¾´Ù.
int AUTH_QUE_Count( int type )
{
	int iCount = 0;
	AUTH_QUE *pNow;
	// ¼±µÎÀÇ À§Ä¡
	pNow = aAuthLinkTbl[type].QueTop.pNext;
	// ÀÖÀ» ¶§±îÁö ¼¾´Ù£®
	for( ; pNow->pNext; pNow=pNow->pNext ){
		iCount ++;
	}

	return iCount;
}


//-------------------------------------------------------------------------
// Å¥¿¡ Ã³¸®¸¦ Ãß°¡ÇÑ´Ù.
// ÀÎ¼ö
// AUTH_QUE *que   µî·ÏÇÏ´Â Å¥
// µ¹¾Æ¿À°í °ª:
// ¼º°ø :0 ÀÌ»ó£®¼¼Æ®ÇÑ queÀÇ ¹øÈ£
// ½ÇÆÐ :-1
//-------------------------------------------------------------------------

int AUTH_addQue( AUTH_QUE *que)
{    
	AUTH_QUE *pNew;
	EnterCriticalSection(&g_cs);			//ktj : window
	//pthread_mutex_lock( &AUTH_que_mutex);	//ktj : linux

	// freeListÀÇ ¼±µÎ
	pNew = AUTH_QUE_getTop( AUTHLINKTBL_FREE );  //0
	if( pNew == NULL ){
		//eprint( "err:cannot add auth que\n");
		LeaveCriticalSection(&g_cs);				//ktj : window
		//pthread_mutex_unlock( &AUTH_que_mutex);	//ktj : linux
		return -1;
	}

	// µ¥ÀÌÅÍ Ä«ÇÇ
	pNew->command = que->command;
	pNew->fdid = que->fdid;
	pNew->result = AUTH_ERROR_OTHER;
	//ktj : ÀÏ´Ü »èÁ¦
	//pNew->query_time = NowTime.tv_sec;
	pNew->query_time = 10;
	strcpy( pNew->cdkey, que->cdkey);
	strcpy( pNew->isaokey, que->isaokey);
	strcpy( pNew->password, que->password);

	//ktj : »õ·Î ³ÖÀ½. --s
	strcpy( pNew->ip_address, que->ip_address);
	strcpy( pNew->id, que->id);
	strcpy( pNew->expl, que->expl);
	strcpy( pNew->clanName, que->clanName);
	strcpy( pNew->charId, que->charId);
	//ygy
	strcpy( pNew->ClanZang_ID,que->ClanZang_ID);
	strcpy( pNew->ClanZang_ChaName, que->ClanZang_ChaName);
	strcpy(pNew->gserver, que->gserver);
	strcpy(pNew->ClanWon_ID,que->ClanWon_ID);
	strcpy(pNew->ClanWon_ChaName,que->ClanWon_ChaName);
	strcpy(pNew->Mark,que->Mark);
	strcpy(pNew->Gubun,que->Gubun);
	strcpy(pNew->PFlag,que->PFlag);
	
	pNew->howmanyTime = que->howmanyTime;
	pNew->nNum = que->nNum;
	pNew->ci = que->ci;
	pNew->job_code = que->job_code;
	pNew->level = que->level;
	pNew->joinlevel = que->joinlevel;
	pNew->joinjobcode = que->joinjobcode;
	strcpy(pNew->chipflag , que->chipflag);
	strcpy(pNew->szWavFileName,que->szWavFileName);


	/*char gserver[64]; //ÇöÀç ±º¼­¹ö
	char ClanWon[64];   //ÇöÀç Ä³¸¯ÅÍ¸í
	char ClanZang[64];  //Å¬·£ Â¯
*/

	//ktj : »õ·Î ³ÖÀ½. --e

	pNew->status = AUTH_QUE_STATUS_EXIST;  //1
	pNew->sod2index = que->sod2index;



	// ¸µÅ©¿¡¼­´Â µÎ µ¿¹°ÀÌ ½¬´Â Àå¼Ò£®
	AUTH_QUE_Remove( pNew );
	// °³½Ã ±â´Ù¸®°í Áß(¼Ó)ÀÇ µÚ¿¡ Ãß°¡ÇÑ´Ù£®
	AUTH_QUE_AppendTail( pNew, AUTHLINKTBL_START_WAIT );

	LeaveCriticalSection(&g_cs);				//ktj : window

	// ¹è¿­ÀÇ ¹øÈ£
	return pNew->index;
}















/**************************************************************************
 *
 * DWORD WINAPI AUTH_MainLoop(void* pVoid)
 * AUTH ½º·¹µå ¸ÞÀÎ·çÇÁ(¾²·¹µå¿¡ ÀÇÇØ ºÒ¸®¿öÁü)
 *
 *
 **************************************************************************/
DWORD WINAPI AUTH_MainLoop(void* pVoid)
{
	THREADstruct *thr = (THREADstruct *)pVoid;

	int cnt = 0;
	//BOOL found;
	static struct timeval prev = {0,0};	
	unsigned long thread_index = -1;
	int ret = 0;
	
	//fd2("¾²·¹µå¸ÞÀÎ·çÇÁwhile µé¾î°¡±â Á÷Àü ");


	while(1){
		Sleep(10);

		time_t myTime;
		time( (time_t*)&myTime );
		//fd2("¾²·¹µå¸ÞÀÎ·çÇÁcnt %d  myTime : %d ", cnt++, myTime);

		switch(thr->flag) {
        case FLAG_WAIT:
			time( ( time_t* )&myTime );
			//fd2("¾²·¹µå¸ÞÀÎ·çÇÁ FLAG_WAIT ½ÃÀÛ. %d  ", myTime );


			thr->state=FLAG_WAIT;
			//EnterCriticalSection(&g_cs);
            SuspendThread( (void *)thr->thrHandle );    //WAIT°ªÀÌ µé¾î¿À¸é ÀÚµ¿ÁßÁö½ÃÅ´.
														//Àç°³´Â ¾²·¹µå ¹Û¿¡¼­ ÇØÁÜ.
			//LeaveCriticalSection(&g_cs);

			time( ( time_t* )&myTime );
			fd2("¾²·¹µå¸ÞÀÎ·çÇÁ FLAG_WAIT ³¡. %d ", myTime);
            break;

        case FLAG_EXIT:
            goto _EXIT;

		case FLAG_EXEC:
			thr->state=FLAG_EXEC;
			//fd2("¾²·¹µå¸ÞÀÎ·çÇÁ FLAG_EXEC µé¾î°¨. ");

			/*
			EnterCriticalSection(&g_cs);
			
			LeaveCriticalSection(&g_cs);
			*/



			workfound = FALSE;
			EnterCriticalSection(&g_cs);			//ktj : windows //ktj:432ÁÙ¿¡¼­ ÇØÃ¼ÇÔ¿¡ÁÖÀÇ

			// ´ë±âÁßÀÎ ½ºÆ®·°Ã³ÀÇ ¸Ç¾ÕÀ» °¡Á®¿È(AUTHLINKTBL_START_WAIT : 1)
			AUTH_QUE *que;
			que = AUTH_QUE_getTop(AUTHLINKTBL_START_WAIT );
			
			if( que != NULL ){			// ´ë±âÁßÀÎ µ¥ÀÌÅ¸°¡ ÀÖ¾î index¸¦ °¡Á®¿È.
				workfound = TRUE;			
				cnt = que->index;		
			}else{
				workfound = FALSE;			
			}
  
			// ¹ß°ßµÈ µ¥ÀÌÅ¸°¡ ¾øÀ¸¸é ¾à°£ ÈÞ½ÄÈÄ continueÇÑ´Ù.
			if( !workfound ) {
				LeaveCriticalSection(&g_cs);				//window only
				continue;
			}

			// ¸¸³µ´ø ¶§
			// Å¥ »óÅÂ º¯°æ£®´Ù¸¥ ½º·¹µå¿¡ ºí·ÏÇÏ´Ù£®
			AUTH_que[cnt].status = AUTH_QUE_STATUS_BEGINAUTHPROC; //2
			//ÀÛ¾÷¿¡ Ãß°¡ÇÑ´Ù£®
			AUTH_QUE_Remove( &AUTH_que[cnt] );
			AUTH_QUE_AppendTail( &AUTH_que[cnt], AUTHLINKTBL_WORKING );  //2

			LeaveCriticalSection(&g_cs);				//window only

			// AUTH Ã³¸®
			//ktj : FAUTH_proc_jmptbl[][AUTH_QUE_COMMAND_ALLNUM] ¿¡ ¼ÂÆÃµÈ ÇÔ¼ö¸¦ ½ÇÇà½ÃÄÑÁØ´Ù
			//      À¥»çÀÌÆ®ÅëÇÑ asp,phpÆÄÀÏÀ» ±¸µ¿ÇÏ´Â ÇÔ¼ö°¡ ½ÇÇàµÊ.
			if( !AUTH_proc( 0, cnt, thread_index)) {		
				fd2( "auth_proc error [que:%d command:%d]\n", cnt, AUTH_que[cnt].command);
				break;
			}

			// Å¥ »óÅÂ º¯°æ
			EnterCriticalSection(&g_cs);			//window only
		
			// ÀÏÀÌ ³¡³ª¼­ Å¥¸¦ »èÁ¦ÇÔ.
			AUTH_QUE_Remove( &AUTH_que[cnt] );
			AUTH_QUE_AppendTail( &AUTH_que[cnt], AUTHLINKTBL_FINISH ); //3

			AUTH_que[cnt].status = AUTH_QUE_STATUS_ENDOFAUTHPROC; //3
			LeaveCriticalSection(&g_cs);


			break;
        }
	}
_EXIT:
    thr->flag = FLAG_DEAD;

    ExitThread( TRUE );
    return TRUE;

	

	/*

	//½ÇÁ¦ ½º·¹µå ¸ÞÀÎ ·çÇÁ
	//ktj : Á¾·áºÎºÐÀº ¿ÜºÎÇÔ¼ö¿¡¼­ Á¾·áÇÏµµ·Ï µÇ¾îÀÖÀ½
    while(1){
		
		found = FALSE;
		EnterCriticalSection(&g_cs);			//ktj : windows //ktj:432ÁÙ¿¡¼­ ÇØÃ¼ÇÔ¿¡ÁÖÀÇ

		// ´ë±âÁßÀÎ ½ºÆ®·°Ã³ÀÇ ¸Ç¾ÕÀ» °¡Á®¿È(AUTHLINKTBL_START_WAIT : 1)
		AUTH_QUE *que;
	    que = AUTH_QUE_getTop(AUTHLINKTBL_START_WAIT );
			
		if( que != NULL ){			// ´ë±âÁßÀÎ µ¥ÀÌÅ¸°¡ ÀÖ¾î index¸¦ °¡Á®¿È.
			found = TRUE;			
			cnt = que->index;		
		}else{
			found = FALSE;			
		}
  
		// ¹ß°ßµÈ µ¥ÀÌÅ¸°¡ ¾øÀ¸¸é ¾à°£ ÈÞ½ÄÈÄ continueÇÑ´Ù.
		if( !found) {
			LeaveCriticalSection(&g_cs);				//window only
			continue;
		}

		// ¸¸³µ´ø ¶§
		// Å¥ »óÅÂ º¯°æ£®´Ù¸¥ ½º·¹µå¿¡ ºí·ÏÇÏ´Ù£®
		AUTH_que[cnt].status = AUTH_QUE_STATUS_BEGINAUTHPROC; //2
		//ÀÛ¾÷¿¡ Ãß°¡ÇÑ´Ù£®
		AUTH_QUE_Remove( &AUTH_que[cnt] );
		AUTH_QUE_AppendTail( &AUTH_que[cnt], AUTHLINKTBL_WORKING );  //2

        LeaveCriticalSection(&g_cs);				//window only

		// AUTH Ã³¸®
		//ktj : FAUTH_proc_jmptbl[][AUTH_QUE_COMMAND_ALLNUM] ¿¡ ¼ÂÆÃµÈ ÇÔ¼ö¸¦ ½ÇÇà½ÃÄÑÁØ´Ù
		//      À¥»çÀÌÆ®ÅëÇÑ asp,phpÆÄÀÏÀ» ±¸µ¿ÇÏ´Â ÇÔ¼ö°¡ ½ÇÇàµÊ.
		if( !AUTH_proc( 0, cnt, thread_index)) {		
			fd2( "auth_proc error [que:%d command:%d]\n", cnt, AUTH_que[cnt].command);
			break;
		}

		
		// Å¥ »óÅÂ º¯°æ
		EnterCriticalSection(&g_cs);			//window only
		
		// ÀÏÀÌ ³¡³ª¼­ Å¥¸¦ »èÁ¦ÇÔ.
		AUTH_QUE_Remove( &AUTH_que[cnt] );
		AUTH_QUE_AppendTail( &AUTH_que[cnt], AUTHLINKTBL_FINISH ); //3

		AUTH_que[cnt].status = AUTH_QUE_STATUS_ENDOFAUTHPROC; //3
		LeaveCriticalSection(&g_cs);

	}
	
	fd2("¾²·¹µå¸ÞÀÎ·çÇÁ ExitThread  ");
	ExitThread( TRUE );

	return 0;
	*/
}
	

//-------------------------------------------------------------------------
// AUTH ÇÔ¼ö ½ÇÇà ½ÃÅ´
//AUTH_MainLoop(void* pVoid),AUTH_getResultLoop( void) ÀÇ µÎ°³ ÇÔ¼ö¿¡¼­ ºÒ¸®¿öÁ®
//ÇÔ¼öÆ÷ÀÎÅÍ¸¦ ºÒ·¯ ½ÇÇà½ÃÄÑÁÜ.
//-------------------------------------------------------------------------
BOOL AUTH_proc( int mode, int quenum, int threadindex)
{	

	if(mode==0)
		mode = 0;

	if(mode==1)
		mode = 1;

    FUNC	func;
	BOOL	ret = FALSE;

	// ¿¡·¯ Ã¼Å©
	if( quenum < 0 || quenum > AUTH_QUE_nums ) {
		//eprint( "err: quenum \n");
		fd2( "err: quenum \n");
		return FALSE;
	} 

	if( AUTH_que[quenum].command <= AUTH_QUE_CMD_NONE || AUTH_que[quenum].command >= AUTH_QUE_CMD_ALLNUM )
	{
		fd2( "err: command \n");
		return FALSE;
	}
	
	func = AUTH_proc_jmptbl[mode][AUTH_que[quenum].command];
	if( func) {
		//isaocheckµîÀÇ À¥¿¡ Á¢±ÙÇÏ´Â ÇÔ¼öµéÀÌ ÇÔ¼öÆ÷ÀÎÅÍ¿¡ ÀÇÇØ ½ÇÇàµÇ¾îÁü.
		//===============================================================
		ret = func( quenum, threadindex);	
		//===============================================================
	}
	else {
		fd2( "err: no such function\n");
	}
	if( !ret)
		fd2("err func:\n");
	return ret;
	
}










































WebDB_Thread::WebDB_Thread()
{
	
}
WebDB_Thread::~WebDB_Thread()
{

	//######################################################################################
	//ÀÛ ¼º ÀÚ : ¿À ¿µ ¼®
	AUTH_close();
	//######################################################################################
}
void WebDB_Thread::init()
{
}

void WebDB_Thread::main()
{
	AUTH_getResultLoop();
}


void WebDB_Thread::end()
{
	
}





/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º ¸í: AUTH_init
: ÇÏ ´Â ÀÏ : ¾²·¹µå¿Í µ¥ÀÌÅ¸ ¼ÂÆÃ
: ¹Ý È¯ °ª :
///////////////////////////////////////////////////////////////////////////*/
int WebDB_Thread::AUTH_init(int Num)
{
	fd2( "AUTH_init()ÇÔ¼ö start" );
	
	//ktj ±³Ã¼
	AUTH_QUE_nums = Num;//config.authquenum;

	int i;

	// ¸Þ½ÃÁö Å¥ÀÇ È®º¸
	//AUTH_que = allocateMemory( sizeof( AUTH_QUE) * config.authquenum);	//¿øº»
	AUTH_que = new AUTH_QUE[AUTH_QUE_nums ];								//ktj : setup.cf¿¡¼­ ÀÐ¾îÈ®º¸ÇÔ.
	
	if( AUTH_que == NULL ) {
		//eprint( "can not allocate memory %d\n", sizeof( AUTH_QUE)*config.authquenum);
		fd2("can not allocatte memory %d\n","new memory");
		return FALSE;
	}


	// ¸Þ½ÃÁö Å¥ÀÇ ÃÊ±âÈ­
	//for( i = 0; i < (int)config.authquenum; i ++ ) {
	for( i = 0; i < (int)AUTH_QUE_nums; i ++ ) {
		AUTH_que[i].status = AUTH_QUE_STATUS_NONE;
		AUTH_que[i].command = AUTH_QUE_CMD_NONE;
		AUTH_que[i].index = i;							//¹öÆÛ¹øÈ£
		AUTH_que[i].fdid = -1;
		AUTH_que[i].cdkey[0] = '\0';
		AUTH_que[i].isaokey[0] = '\0';
		AUTH_que[i].password[0] = '\0';
		
		AUTH_que[i].result = AUTH_ERROR_OTHER;
	}


	//ktj: Å©¸®Æ¼ÄÃ ¼½¼ÇÀÇ ÃÊ±âÈ­
	InitializeCriticalSection(&g_cs);
//	pthread_mutex_init( &AUTH_que_mutex, NULL);
//	pthread_mutex_init( &AUTH_que_wait_mutex, NULL);
    
	// AUTH Å¥ ¸µÅ© Å×ÀÌºíÀ» ÃÊ±âÈ­	(AUTHLINKTBL_MAX==ÇöÀç 4ÀÓ)
	for( i = 0; i < AUTHLINKTBL_MAX; i ++ ){
		aAuthLinkTbl[i].QueTop.pNext = &aAuthLinkTbl[i].QueTail;	// ¼±µÎÀÇ ´ÙÀ½Àº ÃÖÈÄ
		aAuthLinkTbl[i].QueTop.pPrev = NULL;						// ¼±µÎÀÇ Àü(¾Õ)Àº ÀÌ·ç°í

		aAuthLinkTbl[i].QueTail.pPrev = &aAuthLinkTbl[i].QueTop;	// ÃÖÈÄÀÇ Àü(¾Õ)Àº ¼±µÎ
		aAuthLinkTbl[i].QueTail.pNext = NULL;						// ÃÖÈÄÀÇ ´ÙÀ½Àº ÀÌ·ç°í
	}

	// ÀüºÎ¸¦ ÇÏ´Ã ¸µÅ© ¸®½ºÆ®¿¡ ¿¬°áÇÑ´Ù£®
	for( i = 0; i < (int)AUTH_QUE_nums; i ++ ) {
		AUTH_QUE_AppendTail( &AUTH_que[i], AUTHLINKTBL_FREE );
	}
	
	
	//ktj : À©µµ¿ì¿ë ¾²·¹µå·Î »õ·Î Á¦ÀÛ
	//AUTH ¾²·¹µå¸¦ ½ÃÀÛ.(AUTH_MainLoop()ÇÔ¼ö°¡ °è¼Ó µ¹¾Æ°¨)
	DWORD dwSendMsgId;
	ThreadS.thrHandle  = 0;
    ThreadS.flag =0;
	
    ThreadS.cnt = 0;
	DWORD thrHandle = (unsigned long)CreateThread(NULL,0,AUTH_MainLoop, (void*)&ThreadS,
													0,&dwSendMsgId);
	ThreadS.thrHandle = thrHandle;

	if(ThreadS.thrHandle ==0) 
		return 0;


	fd2( "AUTH_init()ÇÔ¼ö end" );

	return TRUE;
}
/*///////////////////////////////////////////////////////////////////////////
: ÇÔ¼ö  ¸í : AUTH_close()
: ÇÏ´Â  ÀÏ : Á¾·á Ã³¸®
: ÀÎ    ÀÚ :
: ¹ÝÈ¯  °ª :
///////////////////////////////////////////////////////////////////////////*/
int WebDB_Thread::AUTH_close( void)
{
	//AUTH ¾²·¹µå¸¦ ³¡³½´Ù.(TerminateThread():¿ÜºÎ¿¡¼­ ¾²·¹µå¸¦ ³¡³»´ÂÇÔ¼ö)
    TerminateThread( (void*)ThreadS.thrHandle , 0 );

	delete AUTH_que;
	AUTH_que = NULL;

	DeleteCriticalSection(&g_cs);

	fd2( "AUTH_close()ÇÔ¼ö " );
	return TRUE;
}


/*///////////////////////////////////////////////////////////////////////////
: ÇÔ¼ö  ¸í :
: ÇÏ´Â  ÀÏ : ¾²·¹µåÀÇ ¼öÇàÁßÁö, Àç°³ÇÔ¼ö
: ÀÎ    ÀÚ :
: ¹ÝÈ¯  °ª :
///////////////////////////////////////////////////////////////////////////*/
void WebDB_Thread::Suspend()     //ÁßÁö : ktj : Ã³¸®ÇÒ µ¥ÀÌÅ¸°¡ ¾ø´Â°ÍÀ» È®ÀÎÇÑÈÄ ÁßÁöÇÒ°Í
{
	//¸Õ°¡ ÀÖÀ¸¸é ±×³É °£´Ù.
	//if(	workfound != FALSE ||   AUTH_QUE_getTop( AUTHLINKTBL_FINISH ) != NULL)
	//	return;

	fd2("ÁßÁöÇÔ¼ö Suspend() 00 ");
	ThreadS.flag = FLAG_WAIT;

	fd2("ÁßÁöÇÔ¼ö Suspend() 11 ");
}

void WebDB_Thread::Resume()      //Àç°³
{
	fd2("Àç°³ÇÔ¼ö Resume() µé¾î°¨ ");

	if(ThreadS.flag == FLAG_EXEC) return; //flag°¡ ½ÇÇà»óÅÂÀÌ¸é ±×³É °£´Ù.

		
	fd2("Àç°³ÇÔ¼ö Resume() while ½ÃÀÛ ");
    while(1) {
		fd2("Àç°³ÇÔ¼ö Resume() while Áß ");
		
		if(ThreadS.flag == FLAG_WAIT) {

			fd2("Àç°³ÇÔ¼ö Resume() while Áß break; ");


			break;  //flag°¡ ´ë±â»óÅÂÀÏ¶§¸¸ ¼öÇàÇÔ.
		}
    }

	ThreadS.flag = FLAG_EXEC;				//È°µ¿Àç°³(ÁÖÀÇ:ÇÃ·¡±×¸¦ ResumeThread()¾Õ¿¡¾µ°Í ÄÄÀÌ ³Ê¹«ºü¸£¸é ¾²·¹µå°¡ ¾ûÅ³À§ÇèÀÖÀ½.)
    ResumeThread( (void *)ThreadS.thrHandle  );

	fd2("Àç°³ÇÔ¼ö Resume()  ³¡");
}




/**************************************************************************
 * ¿©±â¿¡¼­´Â °ÔÀÓ ½º·¹µå°¡ Ã³¸®ÇÏ´Â ºÎºÐ.
 * AUTH_MainLoop¿¡ ÀÇÇØ Ã³¸®µÈ °¢ °á°ú¸¦ Ã³¸®ÇÏ´Â ÇÔ¼ö
 * °øÀ¯ ¸Þ¸ð¸®¸¦ ¸¸Áö´Â °ÍÀº °ÔÀÓ ½º·¹µå
 *  severNT.cppÀÇ ¸ÞÀÎ¿¡¼­ °è¼ÓºÒ¸®¿öÁ® Ã³¸®µÊ¿¡ ÁÖÀÇ
 **************************************************************************/
int WebDB_Thread::AUTH_getResultLoop( void)
{
	int i;
	static	int cnt = 0;

	AUTH_QUE *que;
	cnt = -1;

	EnterCriticalSection(&g_cs);				//window only
	
	for( i = 0; i < AUTH_QUE_nums; i ++ )
	{
		que = AUTH_QUE_getTop( AUTHLINKTBL_FINISH ); //Ã³¸®°¡ ³¡³­ Å¥¸¦ °¡Á®¿Â´Ù.
		if( que != NULL ){
			cnt = que->index;	// ¹è¿­ ¹øÈ£

			AUTH_QUE_Remove( que );
			// Result Ã³¸®ÇÑ´Ù£®
			if( !AUTH_proc( 1,cnt, -1)) {
				//eprint( "auth_proc error [%d]\n", cnt);
			}
			AUTH_que[cnt].status = AUTH_QUE_STATUS_NONE;
			// ÇÏ´Ã ¸µÅ©¿¡
			AUTH_QUE_AppendTail( &AUTH_que[cnt], AUTHLINKTBL_FREE );
		}else{
			break;
		}
	}
	LeaveCriticalSection(&g_cs);					//window only
	return  TRUE;
}











/*/////////////////////////////////////////////////////////////////////////// START
: ÇÏ ´Â ÀÏ :  À¥db¿¡ Á¢¼ÓÇÏ´Â ¸í·ÉÃ³¸® ÇÔ¼ö 
			  ÇÔ¼öÆ÷ÀÎÅÍ¶§¹®¿¡ CÇüÇÔ¼ö¸¦ ¼±¾ðÇØ¼ö ºÒ¸®¿öÁü¿¡ ÁÖÀÇ
///////////////////////////////////////////////////////////////////////////*/


/*///////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  °æ°í¹® ÀÐ¾î¿À±â
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
/////////////////////////////////////////*/

int WebDB_Thread::ReadNotice(char *userid,char *chaname,char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AuthQueTmp));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReadNotice;          // Å¬·£¸â¹ö·Î °¡ÀÔ

	//ygy	
	strncpy( AuthQueTmp.ClanZang_ID, userid, sizeof( AuthQueTmp.ClanZang_ID ) );
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );
	strncpy( AuthQueTmp.ClanZang_ChaName, chaname, sizeof( AuthQueTmp.ClanZang_ChaName ) );	


	//Å¥¿¡ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}
int AUTH_proc_ReadNotice( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadNotice( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadNotice( int quenum, int threadindex)
{
	char *chaname,*gserver,*userid;
	int knret = 1, iBadMsg = 0;	

	userid = AUTH_que[quenum].ClanZang_ID;
	chaname = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;


	fd2("AUTH_proc_ReadClanInfo %s ", AUTH_que[quenum].Mark);

	//int nMarkNum;
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.ReadNotice(userid,chaname,gserver,AUTH_que[quenum].ret_Buf);
	
	
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
int AUTH_proc_ReadNotice_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadNotice_Result( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReadNotice_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå

	//iResultCode = 1;
	//strcpy(AUTH_que[quenum].ret_Buf,"¾È³çÇÏ¼¼¿ä. ´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù. ´Ù½Ã Á¢¼ÓÇÏ¿©ÁÖ½Ê½Ã¿À´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù.´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù.´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù.´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù.´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù.´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù.´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù.´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù.´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù.´ç½ÅÀº Å¬·£ÀÇ ¹üÁËÀÚ·Î½á ÀÌ¹ø °ÔÀÓÀ» ½ÇÇàÇÒ ¼ö ¾ø½À´Ï´Ù.");
	//AUTH_que[quenum].ret_Buf[0] = 0;

	switch( iResultCode ){
	case 0:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		break;
	case 1:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		strcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);		
		break;	
	case 100:				//ÀÏ¹Ý ¸â¹ö,
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	//ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


/*///////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Å¬·£ ¸¶Å© ¹øÈ£·Î Å¬·£ Á¤º¸ °®¾î¿À±â
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
/////////////////////////////////////////*/
//ygy : Å¬·£¸¶Å©¹øÈ£·Î Å¬·£ Á¤º¸ °®¾î¿À±â
int AUTH_proc_ReadClanInfo( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClanInfo( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReadClanInfo( int quenum, int threadindex)
{
	char *szMarkNum;
	CLANINFO* claninfo;
	//int SaveNum;
	int knret = 1, iBadMsg = 0;
	char* clnaName;

	//id = AUTH_que[quenum].id;
	szMarkNum = AUTH_que[quenum].Mark;
	claninfo = AUTH_que[quenum].ci;
	//SaveNum = AUTH_que[quenum].nNum;



	fd2("AUTH_proc_ReadClanInfo %s ", AUTH_que[quenum].Mark);

	//int nMarkNum;
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.ReadClanInfo(szMarkNum,AUTH_que[quenum].ret_Buf);
	if(knret == 1){
		char* clanINFO_result(char *marknum,char *szInfo,CLANINFO* ci);
		clnaName = clanINFO_result(AUTH_que[quenum].Mark,AUTH_que[quenum].ret_Buf,claninfo);
		knret = iCheck.read_ClanImage2(clnaName,AUTH_que[quenum].Mark,claninfo);
		if(knret ==1)
		{
			claninfo->nStatus = 2;
		}
		else
		{
			claninfo->nStatus = 3;
		}
		//??????????????????????????????????????????????????????????????????????????
		//nCheckDownLoad = 2;
		//??????????????????????????????????????????????????????????????????????????
	}
	else		//´Ù¿î·Îµå ½ÇÆÐÇÔ.
	{
		claninfo->nStatus = 3;
	}
	
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
int AUTH_proc_ReadClanInfo_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClanInfo_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadClanInfo_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	int clanINFO_result2(int ret_code, char *marknum,CLANINFO *ci);
	//clanINFO_result2(ANSdata.ret_val, AUTH_que[quenum].Mark);


	clanINFO_result2(iResultCode, AUTH_que[quenum].Mark,AUTH_que[quenum].ci);


	//ktj : ÀÓ½Ã
	//fd2("AUTH_proc_ReadClanInfo_Result :  ret_val %d  AUTH_que[quenum].Mark : %s ",   ANSdata.ret_val, AUTH_que[quenum].Mark);
	
	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


int WebDB_Thread::ReadClanInfo(char *clanNum,CLANINFO *ci)
{
	//ktj : ÀÓ½Ã
	static int cnt=0;
	fd2("ReadClanInfo:  Å¬·£¸¶Å©¹øÈ£ %s  (cnt %d )",   clanNum,  cnt);
	cnt++;


	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReadClanInfo;          // ÀÎÁõÇÏ´Ù
	
	
	strncpy( AuthQueTmp.Mark, clanNum, sizeof( AuthQueTmp.Mark) );
	//AuthQueTmp.nNum =  num;
	AuthQueTmp.ci = ci;

		

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}

//È£µ¿ClanÃß°¡
//ÇØ´ç ¾ÆÀÌµð°¡ Å¬·£ Å»Åð ÈÄ Àç°¡ÀÔ ±â°£(4ÀÏ)ÀÌ °æ°úµÇÁö ¾Ê¾ÒÀ» ¶§ÀÇ Å¬·£ °¡ÀÔ½ÃÀÇ ¸Þ¼¼Áö
//1ÀÌ¸é 4ÀÏÀÌ ¾ÈÁö³­ »ç¶÷ÀÌ°í 0ÀÌ¸é 4ÀÏÀÌ Áö³­ »ç¶÷
int WebDB_Thread::isCheckClanMember(char *pszServerName, char *pszUserName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isCheckClanMember;          

	//strncpy( AuthQueTmp.ClanZang_ID,      pszUserID, sizeof( AuthQueTmp.ClanZang_ID ) );
	strncpy( AuthQueTmp.ClanZang_ChaName, pszUserName, sizeof( AuthQueTmp.ClanZang_ChaName ) );
	strncpy( AuthQueTmp.gserver,          pszServerName, sizeof( AuthQueTmp.gserver) );

	//Å¥¿¡ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;

}

int AUTH_proc_isCheckClanMember_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanMember_Result(quenum, threadindex);	
}

int AUTH_proc_isCheckClanMember(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanMember(quenum, threadindex);
}



int WebDB_Thread::AUTH_proc_isCheckClanMember(int quenum, int threadindex)
{
	char *ClanZang_ID,*ClanZang_ChaName,*gserver;
	int knret = 1, iBadMsg = 0;

	//id = AUTH_que[quenum].id;
	ClanZang_ID      = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver          = AUTH_que[quenum].gserver;
	
 	knret = iCheck.isCheckClanMember(gserver,ClanZang_ChaName);
	 //knret = iCheck.isCheckClanMember(ClanZang_ID,gserver,ClanZang_ChaName);
	
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	
	return TRUE;
}

int WebDB_Thread::AUTH_proc_isCheckClanMember_Result(int quenum, int threadindex)
{
	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯


	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 0:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		break;
	case 1:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.		
		break;	
	
	default :
		ANSdata.ret_val = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}
	return TRUE;
}


/*///////////////////////////////////////
: ÇÔ ¼ö ¸í :  

: ÇÏ ´Â ÀÏ :  Å¬·£¸â¹öÀÎÁö¸¦ ¾Ë¾Æ³»´ÂÇÔ¼ö
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
/////////////////////////////////////////*/
int AUTH_proc_isClanMember( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isClanMember( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isClanMember( int quenum, int threadindex)
{
	char *ClanZang_ID,*ClanZang_ChaName,*gserver;
	int knret = 1, iBadMsg = 0;

	//id = AUTH_que[quenum].id;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.isClanMember(ClanZang_ID,gserver,ClanZang_ChaName, AUTH_que[quenum].ret_Buf);


	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
   

int AUTH_proc_isClanMember_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isClanMember_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isClanMember_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 0:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		strcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 1:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		strcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 5:
	case 4:
	case 3:
	case 2:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		strcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 100:				//ÀÏ¹Ý ¸â¹ö,
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	//ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}


/*///////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  ÃÊ±â È­¸é °ü·Ã ÇÃ·¡±×
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
/////////////////////////////////////////*/

/*///////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Å¬·£¸â¹öÀÎÁö¸¦ ¾Ë¾Æ³»´ÂÇÔ¼ö
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
/////////////////////////////////////////*/
int AUTH_proc_isPFlag( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isPFlag( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isPFlag( int quenum, int threadindex)
{
	char *ClanZang_ID,*ClanZang_ChaName,*gserver,*PFlag,*Gubun,*ClanName;
	int knret = 1, iBadMsg = 0;

	//id = AUTH_que[quenum].id;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	PFlag = AUTH_que[quenum].PFlag;
	Gubun = AUTH_que[quenum].Gubun;
	ClanName = AUTH_que[quenum].clanName;
	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.isPFlag(ClanZang_ID,ClanName,ClanZang_ChaName,gserver, PFlag,Gubun);


	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_isPFlag_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isPFlag_Result( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isPFlag_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 0:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		break;
	case 1:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.		
		break;	
	case 100:				//ÀÏ¹Ý ¸â¹ö,
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;		
	default :
		ANSdata.ret_val = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	//ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}

int WebDB_Thread::isPFlag(char *userid, char *clName, char *chName,char *gserver, char *PFlag, char *Gubun)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isPFlag;          // ÀÎÁõÇÏ´Ù
	
	strncpy( AuthQueTmp.Gubun, Gubun, sizeof( AuthQueTmp.Gubun ) );
	strncpy(AuthQueTmp.ClanZang_ID, userid, sizeof( AuthQueTmp.ClanZang_ID ));
	strncpy( AuthQueTmp.clanName, clName, sizeof( AuthQueTmp.clanName ) );	
	strncpy( AuthQueTmp.ClanZang_ChaName, chName, sizeof( AuthQueTmp.ClanZang_ChaName ) );	
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );
	strncpy( AuthQueTmp.PFlag, PFlag, sizeof( AuthQueTmp.PFlag ) );
	

	

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}

/*///////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  °ü·ÃµÈ °èÁ¤ÀÌ Å¬·£ÀåÀ¸·Î µî·ÏµÇ¾î ÀÖ´ÂÁö Ã¼Å©
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
/////////////////////////////////////////*/
int WebDB_Thread::isCheckClanJang(char *ClanZang_ID, char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isCheckClanJang;          // ÀÎÁõÇÏ´Ù
		
	strncpy( AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof( AuthQueTmp.ClanZang_ID ) );	
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}
int AUTH_proc_isCheckClanJang( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanJang( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanJang( int quenum, int threadindex)
{
	char* ClanZang_ID,*gserver;
	int knret = 1, iBadMsg = 0;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;	
	gserver= AUTH_que[quenum].gserver;
	
	
	knret = iCheck.isCheckClanJang(ClanZang_ID,gserver);


	//ktj : ¿¹Á¦ÀÌ¹Ç·Î ³ªÁß¿¡ Áö¿ì½Ã¿À.
	//Ä®·³¿¡ µû¸¥ µ¥ÀÌÅ¸ÀÐ±â
	//knret = iCheck.read_ClanName(0);
	//ÀÌ¹ÌÁöÀÐ±â : OK
	//knret = iCheck.write_ClanImageFile("a.bmp");
	///knret = iCheck.read_ClanImage("a.bmp");


	
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_isCheckClanJang_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanJang_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanJang_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	
	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}
	
	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
		case 0://Æ®·£Àè¼Ç ¿À·ù
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 1://»ðÀÔ ¼º°ø
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		/*case 2://Ä³¸¯ÅÍ°¡ ÀÌ¹Ì ´Ù¸¥ Å¬·£¿¡ ¼Ò¼Ó
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 3://Å¬·£ÀÌ¸§ Áßº¹
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;*/
		case 100:				//ÀÎÀÚ°ª ¿¡¶ó
		iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 1004:
		iResultCode = ANSdata.ret_val;
			break;
	case 101:				//Å¬·£µî·ÏÀÌ ¾ÈµÊ.
	case 102:				//Å¬·£ÀåÀ¸·Î µî·ÏÀÌ ¾ÈµÊ.
	case 103:				//Å¬·£ÀåÀ¸·Î µî·ÏÀÌ ¾ÈµÊ.
		break;
//ygy
	//case AUTH_OK:
	//	break;
	default :
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val );

	


	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}





/*///////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Å¬·£ÀÌ¸§ÀÌ Áßº¹ÀÎÁö Ã¼Å©
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
/////////////////////////////////////////*/
int WebDB_Thread::isCheckClanName(char *ClanName,char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isCheckClanName;          // ÀÎÁõÇÏ´Ù
		
	strncpy( AuthQueTmp.clanName, ClanName, sizeof( AuthQueTmp.clanName ) );	
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}
int AUTH_proc_isCheckClanName( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanName( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanName( int quenum, int threadindex)
{
	char* ClanName,*gserver;
	int knret = 1, iBadMsg = 0;

	ClanName = AUTH_que[quenum].clanName;	
	gserver= AUTH_que[quenum].gserver;
	
	
	knret = iCheck.isCheckClanName(ClanName,gserver);


	//ktj : ¿¹Á¦ÀÌ¹Ç·Î ³ªÁß¿¡ Áö¿ì½Ã¿À.
	//Ä®·³¿¡ µû¸¥ µ¥ÀÌÅ¸ÀÐ±â
	//knret = iCheck.read_ClanName(0);
	//ÀÌ¹ÌÁöÀÐ±â : OK
	//knret = iCheck.write_ClanImageFile("a.bmp");
	///knret = iCheck.read_ClanImage("a.bmp");


	
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_isCheckClanName_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanName_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanName_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	
	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}
	
	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
		case 0://Å¬·£ÀÌ¸§ÀÌ Áßº¹µÇÁö ¾ÊÀ½
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 1://Å¬·£ÀÌ¸§ÀÌ Áßº¹
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		/*case 2://Ä³¸¯ÅÍ°¡ ÀÌ¹Ì ´Ù¸¥ Å¬·£¿¡ ¼Ò¼Ó
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 3://Å¬·£ÀÌ¸§ Áßº¹
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;*/
		case 100:				//ÀÎÀÚ°ª ¿¡¶ó
		iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 1004:
		iResultCode = ANSdata.ret_val;
			break;
	case 101:				//Å¬·£µî·ÏÀÌ ¾ÈµÊ.
	case 102:				//Å¬·£ÀåÀ¸·Î µî·ÏÀÌ ¾ÈµÊ.
	case 103:				//Å¬·£ÀåÀ¸·Î µî·ÏÀÌ ¾ÈµÊ.
		break;
//ygy
	//case AUTH_OK:
	//	break;
	default :
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val );

	


	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}



/*///////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Å¬·£À» ¸¸µå´ÂÇÔ¼ö
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
/////////////////////////////////////////*/
int AUTH_proc_ClanMake( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ClanMake( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ClanMake( int quenum, int threadindex)
{
	//char *userId, *clanName, *expl, *userCid;
	char* ClanZang_ID,*ClanZang_ChaName,*gserver,*ClanName,*expl;
	int knret = 1, iBadMsg = 0;
	DWORD chtype;
	int level;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName= AUTH_que[quenum].ClanZang_ChaName;
	ClanName = AUTH_que[quenum].clanName;
	expl = AUTH_que[quenum].expl;
	gserver= AUTH_que[quenum].gserver;
	chtype = AUTH_que[quenum].job_code;
	level = AUTH_que[quenum].level;
	
	
	knret = iCheck.makeClan(ClanZang_ID,gserver,ClanZang_ChaName,ClanName,expl,chtype,level,AUTH_que[quenum].ret_Buf);


	//ktj : ¿¹Á¦ÀÌ¹Ç·Î ³ªÁß¿¡ Áö¿ì½Ã¿À.
	//Ä®·³¿¡ µû¸¥ µ¥ÀÌÅ¸ÀÐ±â
	//knret = iCheck.read_ClanName(0);
	//ÀÌ¹ÌÁöÀÐ±â : OK
	//knret = iCheck.write_ClanImageFile("a.bmp");
	///knret = iCheck.read_ClanImage("a.bmp");


	
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
   

int AUTH_proc_ClanMake_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ClanMake_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ClanMake_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	
	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}
	
	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
		case 0://Æ®·£Àè¼Ç ¿À·ù
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 1://»ðÀÔ ¼º°ø
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			strcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf); //Å¬·£ ºñ¿ëÀ» °¡Áö°í ¿Â´Ù.
			break;
		case 2://Ä³¸¯ÅÍ°¡ ÀÌ¹Ì ´Ù¸¥ Å¬·£¿¡ ¼Ò¼Ó
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 3://Å¬·£ÀÌ¸§ Áßº¹
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 100:				//ÀÎÀÚ°ª ¿¡¶ó
		iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 1004:
		iResultCode = ANSdata.ret_val;
			break;
	case 101:				//Å¬·£µî·ÏÀÌ ¾ÈµÊ.
	case 102:				//Å¬·£ÀåÀ¸·Î µî·ÏÀÌ ¾ÈµÊ.
	case 103:				//Å¬·£ÀåÀ¸·Î µî·ÏÀÌ ¾ÈµÊ.
		break;
//ygy
	//case AUTH_OK:
	//	break;
	default :
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val );

	


	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}









/*/////////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Å¬·£°¡ÀÔ½Ã ¸â¹ö¸¦ ¸¸µå´ÂÇÔ¼ö
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
//////////////////////////////////////////*/
int AUTH_proc_Mmake( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Mmake(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Mmake( int quenum, int threadindex)
{
	char *clanName, *memId, *memCharId;
	char *ClanZang_ID,*ClanZang_ChaName,*gserver,*ClanWon_ID,*ClanWon_ChaName,*chipflag;
	int knret = 1, iBadMsg = 0;
	int level =0;
	int joinlevel;
	DWORD job_code;


	clanName = AUTH_que[quenum].clanName;
	memId     = AUTH_que[quenum].id;				//ÀÓ½Ã·Î ¾Æ¹«¹öÆÛ¿¡³ª ³Ö¾îµÒ.
	memCharId = AUTH_que[quenum].charId;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	ClanWon_ID = AUTH_que[quenum].ClanWon_ID;
	ClanWon_ChaName = AUTH_que[quenum].ClanWon_ChaName;
	level = AUTH_que[quenum].level;
	job_code = AUTH_que[quenum].joinjobcode;
	joinlevel = AUTH_que[quenum].joinlevel;
	chipflag = AUTH_que[quenum].chipflag;
	

	//ygy
	//knret = iCheck.joinClanMember(clanName, memId, memCharId);
	//char *ClanZang_ID, char *gserver, char *ClanZang_ChaName,char* ClanName,char* ClanWon,char* ClanWon_ID
	knret = iCheck.joinClanMember(ClanZang_ID,gserver,ClanZang_ChaName,clanName,ClanWon_ChaName,ClanWon_ID,level,job_code,joinlevel,chipflag);
    
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;

	return TRUE;
}


int AUTH_proc_Mmake_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Mmake_Result( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Mmake_Result( int quenum, int threadindex)
{
	char szData[128];

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
		case 0://Æ®·£Àè¼Ç ¿À·ù
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 1://Å¬·£¿ø °¡ÀÔ ¼º°ø
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 2://ÇöÀç °¡ÀÔ½ÃÅ°·Á´Â Å¬·£¿øÀÌ ÀÌ¹Ì ´Ù¸¥ Å¬·£¿¡ °¡ÀÔÇØÀÖÀ» °æ¿ì(ÀÚ±â Å¬·£Æ÷ÇÔ)
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 3://Å¬·£ÀÌ Á¸ÀçÇÏÁö ¾Ê°Å³ª Å¬·£ ÀåÀÌ ¾Æ´Ñ°æ¿ì
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 4://Å¬·£ ¸â¹ö°¡ 32 ÀÌ»óÀÏ °æ¿ì(Max : 32)
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 100:
			iResultCode = AUTH_que[quenum].result;
			break;
		case 1004:
			iResultCode = AUTH_que[quenum].result;
			break;
	case 101:
	case 102:
	case 103:
		break;
//ygy
	//case AUTH_OK:
	//	break;
	default :
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}

	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return 1;
}





/*/////////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  ¸¸µé¾îÁø Å¬·£ µ¥ÀÌÅ¸¸¦ ÀÐ´Â´Ù.
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
//////////////////////////////////////////*/

int AUTH_proc_ReadClan( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClan(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadClan( int quenum, int threadindex)
{
	char *ClanZang_ID,*ClanZang_ChaName,*gserver;
	int knret = 1, iBadMsg = 0;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.read_ClanData(ClanZang_ID,gserver,ClanZang_ChaName, AUTH_que[quenum].ret_Buf);


	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_ReadClan_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClan_Result( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadClan_Result( int quenum, int threadindex)
{
	char szData[128];

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
		//ygy
		case 0: //°¡ÀÔÇÑ Å¬·£ÀÌ ¾øÀ½
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 1://Á¤»ó Ãâ·Â
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			strcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
			break;
		case 100:				//ÀÏ¹Ý ¸â¹ö,
			ANSdata.ret_val = iResultCode;
			break;
		case	1004:
			ANSdata.ret_val = iResultCode;
			break;
		case 101:				//Å¬·£ÀåÀÏ°æ¿ì ¼ÓÇÑ Å¬·£ÀÌ¸§µµ ¾Ë¾Æ³¿.
		case 102:				//¸â¹ö¾Æ´Ô.
			strcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
			break;

			//ygy
		//case AUTH_OK:
		//	break;
		default :
			iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
			break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}



/*/////////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Å¬·£À» ÇØÃ¼ÇÑ´Ù.
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
//////////////////////////////////////////*/

int AUTH_proc_BreakUP( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_BreakUP(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_BreakUP( int quenum, int threadindex)
{
	char *ClanZang_ID,*ClanZang_ChaName,*gserver,*ClanName;
	int knret = 1, iBadMsg = 0;

	ClanName = AUTH_que[quenum].clanName;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver= AUTH_que[quenum].gserver;
	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.BreakUPClan(ClanZang_ID,gserver,ClanZang_ChaName,ClanName);

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_BreakUP_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_BreakUP_Result( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_BreakUP_Result( int quenum, int threadindex)
{
	char szData[128];

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
		//ygy
		//case AUTH_OK:
		//break;
		case 0:
			iResultCode = AUTH_que[quenum].result;
			break;
		case 1: //»èÁ¦ ¼º°ø
			iResultCode = AUTH_que[quenum].result;
			break;
		case 2: //ÇöÀç Ä³¸¯¸íÀÌ ÇöÀç Å¬·£ÀÇ ÀåÀÌ ¾Æ´Ï°Å³ª ÇØ´çÅ¬·£ÀÌ ¾øÀ½
			iResultCode = AUTH_que[quenum].result;
			break;
			//end ygy
	case 100:				//Áö¿ì±â¼º°ø
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 101:				//clanWonÅ×ÀÌºí¿¡ Å¬·£¿øÀÖ´Âµ¥ clanWonÅ×ÀÌºí¿¡ ¾ø´Â°æ¿ì(Ä¡¸í¿¡·¯)
	case 102:				//clanWonÅ×ÀÌºí¿¡¼­ Å¬·£¿ø»èÁ¦½ÇÆÐ>
	case 103:				//clanName¾È¿¡ Å¬·£ ³×ÀÓÀÌ Á¸ÀçÇÏÁö¾ÊÀ»°æ¿ì
	case 104:				//clanNameÅ×ÀÌºí¿¡¼­ Å¬·£»èÁ¦ ½ÇÆÐ
		break;

	
	default :
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	//ygy
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}






/*/////////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Æ¯Á¤id°¡ Å¬·£¿¡¼­ Å»Åð
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
//////////////////////////////////////////*/

int AUTH_proc_Secession( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Secession(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Secession( int quenum, int threadindex)
{
	char *clanName, *secession_id,*gserver,*clanzang;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	//ygy
	//banish_id = AUTH_que[quenum].expl;
	clanzang = AUTH_que[quenum].ClanWon_ChaName;
	gserver = AUTH_que[quenum].gserver;
	secession_id = AUTH_que[quenum].ClanWon_ID;

	/*
	strncpy( AuthQueTmp.clanName, claname, sizeof( AuthQueTmp.clanName ) );
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );
	strncpy( AuthQueTmp.ClanWon, SecessionID, sizeof( AuthQueTmp.ClanWon ) );
	strncpy( AuthQueTmp.ClanZang, clanzang, sizeof( AuthQueTmp.ClanZang ) );
	*/

	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.Secession(secession_id,gserver,clanzang ,clanName);
	//int ISAOCHECK::Secession(char* clanzang,char* gserver,char* SecessionID,char* claname)

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_Secession_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Secession_Result( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Secession_Result( int quenum, int threadindex)
{
	char szData[128];

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	//ygy
	case 0: //Æ®·£Àè¼Ç ¿À·ù
			iResultCode = AUTH_que[quenum].result;
			break;
	case 1: //Å¬·£¿ø Å»Åð ¼º°ø
			iResultCode = AUTH_que[quenum].result;
			break;
	case 2://Å¬·£ÀÌ Á¸ÀçÇÏÁö ¾Ê°Å³ª Å¬·£ ÀåÀÌ ¾Æ´Ñ°æ¿ì ¶Ç´Â Å¬·£¿øÀÌ ¾Æ´Ñ°æ¿ì
			iResultCode = AUTH_que[quenum].result;
			break;
	case 3://Å»Åð´Â ¼º°øÇßÀ¸³ª Å¬·£È¸¿ø¼ö°¡ 6¸íÀÌÇÏ·Î ¶³¾îÁ³À» °æ¿ì(LimitDate ¼³Á¤)
			iResultCode = AUTH_que[quenum].result;
			break;
	case 100:	
			iResultCode = AUTH_que[quenum].result;
			break;			//Ãß¹æ ¿¡·¯
	case ISAO_ERR_TCP_CONNECT: //¼­¹ö Á¢¼Ó¿¡·¯
			iResultCode = AUTH_que[quenum].result;
			break;
	case 101:				//Ãß¹æºÒ°¡
		break;
     //ygy
	//case AUTH_OK:
	//	break;
	default :
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);
	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}





/*/////////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Æ¯Á¤id¸¦ Å¬·£¿¡¼­ Ãß¹æÇÑ´Ù.
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
//////////////////////////////////////////*/

int AUTH_proc_Banishiment( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Banishiment(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Banishiment( int quenum, int threadindex)
{
	char *clanName, *ClanWon,*gserver,*ClanZang_ID,*ClanZang_ChaName;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	ClanWon = AUTH_que[quenum].ClanWon_ChaName;

	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.Banishiment(ClanZang_ID,gserver,ClanZang_ChaName,clanName,ClanWon);

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_Banishiment_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Banishiment_Result( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Banishiment_Result( int quenum, int threadindex)
{
	char szData[128];

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
		//ygy
		case 0: //Æ®·£Àè¼Ç ¿À·ù
			iResultCode = AUTH_que[quenum].result;
			break;
		case 1: //Å¬·£¿ø Å»Åð ¼º°ø
			iResultCode = AUTH_que[quenum].result;
			break;
		case 2://Å¬·£ÀÌ Á¸ÀçÇÏÁö ¾Ê°Å³ª Å¬·£ ÀåÀÌ ¾Æ´Ñ°æ¿ì ¶Ç´Â Å¬·£¿øÀÌ ¾Æ´Ñ°æ¿ì
			iResultCode = AUTH_que[quenum].result;
			break;
		case 3://Å»Åð´Â ¼º°øÇßÀ¸³ª Å¬·£È¸¿ø¼ö°¡ 6¸íÀÌÇÏ·Î ¶³¾îÁ³À» °æ¿ì(LimitDate ¼³Á¤)
			iResultCode = AUTH_que[quenum].result;
			break;
	case 100:				//Ãß¹æ¿Ï·á
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 101:				//Ãß¹æºÒ°¡
		break;
     //ygy
	//case AUTH_OK:
	//	break;
	default :
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);
	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}





/*/////////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Æ¯Á¤id¸¦ Å¬·£¿¡¼­ Ãß¹æÇÑ´Ù.
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
//////////////////////////////////////////*/

int AUTH_proc_WarhouseR( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_WarhouseR(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_WarhouseR( int quenum, int threadindex)
{
	char *clanName, *banish_id;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	banish_id = AUTH_que[quenum].expl;
	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.WarhouseRight(clanName, banish_id);

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_WarhouseR_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_WarhouseR_Result( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_WarhouseR_Result( int quenum, int threadindex)
{
	char szData[128];

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 100:				//¿Ï·á
	case 101:				//
	case 102:				//
		break;

	case AUTH_OK:
		break;
	default :
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Ã¢°í±ÇÇÑ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);
	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}




/*/////////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Å¬·£°á¼º³¡ ÇÃ·¡±× ¼ÂÆÃ
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
//////////////////////////////////////////*/

int AUTH_proc_updateFlag( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_updateFlag(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_updateFlag( int quenum, int threadindex)
{
	char *clanName, *banish_id;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	banish_id = AUTH_que[quenum].expl;
	
	knret = iCheck.updateFlag(clanName);

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_updateFlag_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_updateFlag_Result( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_updateFlag_Result( int quenum, int threadindex)
{
	char szData[128];

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 100:				//¿Ï·á
	case 101:				//Å¬·£¾øÀ½.
	case 102:				//
		break;

	case AUTH_OK:
		iResultCode = AUTH_que[quenum].result;
		break;
	default :
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Ã¢°í±ÇÇÑ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);
	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}








/*/////////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  Å¬·£¸¶Å©ÀÐ±â
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
//////////////////////////////////////////*/

int AUTH_proc_MarkREAD( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD( int quenum, int threadindex)
{
	//char *clanName, *banish_id;
	char *Mark,*clanname;
	int knret = 1, iBadMsg = 0;

	Mark = AUTH_que[quenum].Mark;
	clanname = AUTH_que[quenum].clanName;
	//banish_id = AUTH_que[quenum].expl;
	
	knret = iCheck.read_ClanImage(clanname,Mark);

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_MarkREAD_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD_Result( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD_Result( int quenum, int threadindex)
{
	char szData[128];

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;	

	//ktj : ÀÓ½Ã ½ÇÆÐ
	//AUTH_que[quenum].result = 2;

	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 1: //Å¬·£ ¸¶Å© ÀÐ±â ¼º°ø
			
		iResultCode =AUTH_que[quenum].result ;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
		break;
	case 2://Å¬·£ ¸¶Å© ÀÐ±â ½ÇÆÐ
		iResultCode = AUTH_que[quenum].result ;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
		break;

	case 100:				//¿Ï·á
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 101:				//Å¬·£¾øÀ½.
	case 102:				//
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;

//	case AUTH_OK:
//		break;
	//default :
	//	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	//	AUTH_que[quenum].result = iResultCode;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Ã¢°í±ÇÇÑ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);
	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}

/*/////////////////////////////////////////
: ÇÔ ¼ö ¸í :  
: ÇÏ ´Â ÀÏ :  ´Ù¸¥ Å¬·£¸¶Å©ÀÐ±â
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
//////////////////////////////////////////*/

int AUTH_proc_MarkREAD2( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD2(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD2( int quenum, int threadindex)
{
	//char *clanName, *banish_id;
	char *Mark,*clanname;
	int knret = 1, iBadMsg = 0;

	Mark = AUTH_que[quenum].Mark;
	clanname = AUTH_que[quenum].clanName;
	//banish_id = AUTH_que[quenum].expl;
	
	//knret = iCheck.read_ClanImage2(clanname,Mark);





	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_MarkREAD2_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD2_Result( quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD2_Result( int quenum, int threadindex)
{
	char szData[128];

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;	
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
		case 1: //Å¬·£ ¸¶Å© ÀÐ±â ¼º°ø
			
			iResultCode =AUTH_que[quenum].result ;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 2://Å¬·£ ¸¶Å© ÀÐ±â ½ÇÆÐ
			iResultCode = AUTH_que[quenum].result ;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
	case 100:				//¿Ï·á
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 101:				//Å¬·£¾øÀ½.
	case 102:				//
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;

//	case AUTH_OK:
//		break;
	//default :
	//	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	//	AUTH_que[quenum].result = iResultCode;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	//	break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Ã¢°í±ÇÇÑ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);
	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}



int AUTH_proc_Updatcldata( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Updatcldata(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_Updatcldata(int quenum, int threadindex)
{
	char *id,*chaname,*gserver;
	int knret = 1, iBadMsg = 0;

	//id = AUTH_que[quenum].id;
	id = AUTH_que[quenum].ClanZang_ID;
	chaname = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.isClanMember(id,gserver,chaname, AUTH_que[quenum].ret_Buf);
	if((knret == 0)||(knret == 2)||(knret == 1)||(knret == 3)||(knret == 4)||(knret == 5)){
		void ParsingIsClanMember(char* data,int myposition);
		ParsingIsClanMember(AUTH_que[quenum].ret_Buf,knret);
		if((knret == 2)||(knret == 1)||(knret == 5)){
			knret=iCheck.read_ClanData(id,gserver,chaname, AUTH_que[quenum].ret_Buf);
			if(knret == 1){
				void ParsigClanWon(char* data);
				ParsigClanWon(AUTH_que[quenum].ret_Buf);
				knret = iCheck.read_ClanImage(chaname,cldata.ClanMark);
			}
		}
	}


	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;

	return 1;
}

int AUTH_proc_Updatcldata_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Updatcldata_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_Updatcldata_Result( int quenum, int threadindex)
{
	char szData[128];
	char GServer;
	char szNum[64];
	char szFile[256];
	char szFile2[256];
	ZeroMemory(szNum,sizeof(szNum));
	ZeroMemory(szFile,sizeof(szFile));
	ZeroMemory(szFile2,sizeof(szFile2));

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
		//ygy
		case 0: //°¡ÀÔÇÑ Å¬·£ÀÌ ¾øÀ½
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
			break;
		case 1://Á¤»ó Ãâ·Â
			iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯			
			GServer = cldata.ClanMark[0];
			strcpy(szNum , &cldata.ClanMark[3]);
			wsprintf(szFile,"%s\\%s\\%c_%s.%s",SAVE_DIR,szConnServerName,GServer,szNum,SAVE_EXE );
			wsprintf(szFile2,"%s\\%s\\%c_%s_16.%s",SAVE_DIR,szConnServerName,GServer,szNum,SAVE_EXE);
#ifdef  USE_PROSTONTALE						
			if(cldata.hClanMark16) {
				cldata.hClanMark16->Release();
				cldata.hClanMark16 = NULL;
			}

			if(cldata.hClanMark){
				cldata.hClanMark->Release();
				cldata.hClanMark = NULL;
			}

			cldata.hClanMark16= LoadDibSurfaceOffscreen(szFile2);
			cldata.hClanMark= LoadDibSurfaceOffscreen(szFile);
#endif

			break;
		case 100:				//ÀÏ¹Ý ¸â¹ö,
			ANSdata.ret_val = iResultCode;
			break;
		case	1004:
			ANSdata.ret_val = iResultCode;
			break;
		case 101:				//Å¬·£ÀåÀÏ°æ¿ì ¼ÓÇÑ Å¬·£ÀÌ¸§µµ ¾Ë¾Æ³¿.
		case 102:				//¸â¹ö¾Æ´Ô.			
			break;

			//ygy
		//case AUTH_OK:
		//	break;
		default :
			iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
			break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	


	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}


	//cE_Updatecldata.cpp¿Í °ü·Ã
	void g_UpdateCldata_Close(); //¾²·¹µå Á×ÀÓ
	g_UpdateCldata_Close(); //¾²·¹µå Á×ÀÓ

	return TRUE;
}

int WebDB_Thread::Updatcldata(char *id, char *gserver, char *chaname)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));


	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_Updatcldata;          // Å¬·£¸â¹öÀÎÁö¸¦ ¾Ë·Á´Þ¶ó..	
	
	//ygy
	//strncpy( AuthQueTmp.id, id, sizeof( AuthQueTmp.id ) );
	strncpy( AuthQueTmp.ClanZang_ID, id, sizeof( AuthQueTmp.ClanZang_ID ) );
	strncpy( AuthQueTmp.ClanZang_ChaName, chaname, sizeof( AuthQueTmp.ClanZang_ChaName ) );
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver) );
		
	

	//Å¥¿¡ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}

/*/////////////////////////////////////////////////////////////////////////// END
: ÇÏ ´Â ÀÏ :  À¥db¿¡ Á¢¼ÓÇÏ´Â ¸í·ÉÃ³¸® ÇÔ¼ö 
///////////////////////////////////////////////////////////////////////////*/















/*/////////////////////////////////////////////////////////////////////////// START
: ÇÏ ´Â ÀÏ :  WebDB¿¡ Á¢¼ÓÇØ¼­ ÇÒÀÏÀ» Áö½ÃÇÏ´Â Áö½ÃÇÔ¼öµé.
///////////////////////////////////////////////////////////////////////////*/

//ÇØ´ç id°¡ Å¬·£¿øÀÎÁöÀÇ ¿©ºÎ¸¦ ¾Ë¾Æ³¿.
int WebDB_Thread::isClanMember(char *ClanZang_id, char* gserver,char* ClanZang_ChaName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isClanMember;          // Å¬·£¸â¹öÀÎÁö¸¦ ¾Ë·Á´Þ¶ó..	
	
	//ygy
	//strncpy( AuthQueTmp.id, id, sizeof( AuthQueTmp.id ) );
	strncpy( AuthQueTmp.ClanZang_ID, ClanZang_id, sizeof( AuthQueTmp.ClanZang_ID ) );
	strncpy( AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof( AuthQueTmp.ClanZang_ChaName ) );
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver) );

	//Å¥¿¡ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}




//Å¬·£¸â¹ö·Î °¡ÀÔ½ÃÅ²´Ù.
int WebDB_Thread::joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName,char* ClanName,char* ClanWon,char* ClanWon_ID,int level,DWORD chtype,int joinlevel,char *chipflag)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AuthQueTmp));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_CL_MEMBER_MAKE;          // Å¬·£¸â¹ö·Î °¡ÀÔ

	//ygy	
	strncpy( AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof( AuthQueTmp.ClanZang_ID ) );
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );
	strncpy( AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof( AuthQueTmp.ClanZang_ChaName ) );
	strncpy( AuthQueTmp.clanName, ClanName, sizeof( AuthQueTmp.clanName ) );
	strncpy( AuthQueTmp.ClanWon_ChaName, ClanWon, sizeof( AuthQueTmp.ClanWon_ChaName ) );
	strncpy( AuthQueTmp.ClanWon_ID, ClanWon_ID, sizeof( AuthQueTmp.ClanWon_ID ) );
	strncpy( AuthQueTmp.chipflag, chipflag, sizeof( AuthQueTmp.chipflag ) );
	
	AuthQueTmp.level = level;
	AuthQueTmp.joinlevel = joinlevel;
	AuthQueTmp.joinjobcode = (int)chtype;



	//Å¥¿¡ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}





//Å¬·£À» ¸¸µé°í½Í´Ù¸é ¸¸µç´Ù.
int WebDB_Thread::make_Clan(char *ClanZang_ID, char* gserver,char* ClanZang_ChaName,char* ClanName,char *explanation,DWORD chtype,int level)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_CL_MAKE;          // ÀÎÁõÇÏ´Ù
		
	strncpy( AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof( AuthQueTmp.ClanZang_ID ) );
	strncpy( AuthQueTmp.expl, explanation, sizeof( AuthQueTmp.expl ) );
	strncpy( AuthQueTmp.clanName, ClanName, sizeof( AuthQueTmp.clanName ) );
	strncpy( AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof( AuthQueTmp.ClanZang_ChaName ) );
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );

	AuthQueTmp.level = level;
	AuthQueTmp.job_code = chtype;

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}





//Å¬·£À» ÀÐ´Â´Ù.
int WebDB_Thread::ReadClan(char *ClanZang_ID,char* gserver,char* ClanZang_ChaName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReadClan;          // ÀÎÁõÇÏ´Ù
	
	//ygy	
	strncpy(AuthQueTmp.ClanZang_ID,ClanZang_ID,sizeof(AuthQueTmp.ClanZang_ID));
	strncpy(AuthQueTmp.gserver,gserver,sizeof(AuthQueTmp.gserver));
	strncpy(AuthQueTmp.ClanZang_ChaName,ClanZang_ChaName,sizeof(AuthQueTmp.ClanZang_ChaName));


	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}


//Å¬·£À» ÇìÃ¼ÇÑ´Ù.
int WebDB_Thread::BreakUP_Clan(char *ClanZang_ID,char *gserver,char *ClanZang_ChaName, char *ClanName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_BreakUP;          // ÀÎÁõÇÏ´Ù
	
	//ygy	
	strncpy( AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof( AuthQueTmp.ClanZang_ID ) );
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );
	strncpy( AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof( AuthQueTmp.ClanZang_ChaName) );
	strncpy( AuthQueTmp.clanName, ClanName, sizeof( AuthQueTmp.clanName ) );

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("BreakUP_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}



//Æ¯Á¤ ¾Æµð¸¦ Ãß¹æÇÑ´Ù.
int WebDB_Thread::Banishiment(char *ClanZang_ID,char *gserver,char *ClanZang_ChaName,char *ClanName, char *ClanWon)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_Banishiment;          // ÀÎÁõÇÏ´Ù	

	//ygy
	strncpy( AuthQueTmp.clanName, ClanName, sizeof( AuthQueTmp.clanName ) );
	strncpy( AuthQueTmp.ClanZang_ID, ClanZang_ID, sizeof( AuthQueTmp.ClanZang_ID ) );
	strncpy( AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName, sizeof( AuthQueTmp.ClanZang_ChaName ) );
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver) );
	strncpy( AuthQueTmp.ClanWon_ChaName, ClanWon, sizeof( AuthQueTmp.ClanWon_ChaName) );
	//strncpy( AuthQueTmp.expl, id_str, strlen( id_str ) );			//ÀÓ½Ã·Î .expl¿¡´Ù ³ÖÀ½.

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("BreakUP_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}



//ÃÊ±âÈ­¸é ÇÃ·¡±×

//Å»ÅðÇÑ´Ù.
int WebDB_Thread::Secession(char* clanzang,char* gserver,char* SecessionID,char* claname)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof( AUTH_QUE  ) );

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_Secession;          // ÀÎÁõÇÏ´Ù

	strncpy( AuthQueTmp.clanName, claname, sizeof( AuthQueTmp.clanName ) );
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );
	strncpy( AuthQueTmp.ClanWon_ChaName, SecessionID, sizeof( AuthQueTmp.ClanWon_ChaName ) );
	strncpy( AuthQueTmp.ClanWon_ID, clanzang, sizeof( AuthQueTmp.ClanZang_ID ) );

	//ygy
	//strncpy( AuthQueTmp.expl, id_str, strlen( id_str ) );			//ÀÓ½Ã·Î .expl¿¡´Ù ³ÖÀ½.

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("BreakUP_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}




//Ã¢°í±ÇÇÑ ¹Ù²ñ
int WebDB_Thread::Warhouse_right(char *clanName, char *right_str)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_WarhouseR			;          // ÀÎÁõÇÏ´Ù
	

	strncpy( AuthQueTmp.clanName, clanName, sizeof( AuthQueTmp.clanName ) );
	strncpy( AuthQueTmp.expl, right_str, strlen( right_str ) );			//ÀÓ½Ã·Î .expl¿¡´Ù ³ÖÀ½.

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("Warhouse_right() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}


//ÀÌÀÓ================================================================
int AUTH_proc_LeaveClan( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_LeaveClan( quenum, threadindex);
}
int AUTH_proc_LeaveClan_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_LeaveClan_Result( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_LeaveClan( int quenum, int threadindex)
{
	
	char *clanname, *chaname,*gserver;
	int knret = 1, iBadMsg = 0;

	chaname = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	clanname = AUTH_que[quenum].clanName;
	
	knret = iCheck.LeaveClan(clanname,chaname,gserver);

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return 1;
}
int WebDB_Thread::AUTH_proc_LeaveClan_Result( int quenum, int threadindex)
{
	char szData[128];

	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯
	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 1:				//¿Ï·á
	case 2:				//Å¬·£¿øÀÌ ¾Æ´Ô
	case 3:				//Á¸ÀçÇÏÁö ¾Ê´Â Å¬·£
	case 4:				//·¹º§ 50¹Ì¸¸
	case 5:				//±ÇÇÑ ÀÚ°Ý¸¸ ¼º°ø ???????????????????????
	case 6:				//ÁöÁ¤Ä³¸¯ÅÍÀÇ Æ÷¿ëÃÖ´ëÀÎ¿ø¼ö º¸´Ù ÇöÀç ÀÎ¿ø¼ö°¡ Å­
	case 100:			//ÀÎÀÚ°ª ºüÁø¿¡·¯¸®ÅÏ°ª
		break;
	case 1004:				//¼­¹öÁ¢±Ù¾ÈµÈ°æ¿ì
		break;
	default :
		iResultCode = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Ã¢°í±ÇÇÑ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);
	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
	
}
int WebDB_Thread::LeaveClan(char *clanname,char *chaname,char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AuthQueTmp));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_LeaveClan;          // Å¬·£¸â¹ö·Î °¡ÀÔ

	//ygy	
	strncpy( AuthQueTmp.clanName, clanname, sizeof( AuthQueTmp.ClanZang_ID ) );
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );
	strncpy( AuthQueTmp.ClanZang_ChaName, chaname, sizeof( AuthQueTmp.ClanZang_ChaName ) );	


	//Å¥¿¡ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;	
}


//Å¬·£°á¼º¿Ï·á¸¦ À§ÇÑ ÇÃ·¡±×¼ÂÆÃ
int WebDB_Thread::updateFlag(char *clanName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_updateFlag;		//Å¬·£°á¼º¿Ï·á¸¦ À§ÇÑ ÇÃ·¡±×¼ÂÆÃ	
	
	strncpy( AuthQueTmp.clanName, clanName, sizeof( AuthQueTmp.clanName ) );

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("Warhouse_right() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}



//Å¬·£¸¶Å©ÀÐ±â
int WebDB_Thread::MarkREAD(char *clanname,char *mark)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_MarkREAD;		//Å¬·£°á¼º¿Ï·á¸¦ À§ÇÑ ÇÃ·¡±×¼ÂÆÃ	
	
	strncpy( AuthQueTmp.Mark, mark, sizeof( AuthQueTmp.Mark ) );
	strncpy(AuthQueTmp.clanName,clanname,sizeof(AuthQueTmp.clanName));

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("Warhouse_right() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}

//´Ù¸¥ Å¬·£¸¶Å©ÀÐ±â
int WebDB_Thread::MarkREAD2(char *clanname,char *mark)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_MarkREAD2;		//Å¬·£°á¼º¿Ï·á¸¦ À§ÇÑ ÇÃ·¡±×¼ÂÆÃ	
	
	strncpy( AuthQueTmp.Mark, mark, sizeof( AuthQueTmp.Mark ) );
	strncpy(AuthQueTmp.clanName,clanname,sizeof(AuthQueTmp.clanName));

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("Warhouse_right() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}




//ktj : ¼ÂÆÃµÈ È£½ºÆ®ÀÌ¸§ÀÌ NULLÀÌ¸é Å¬·£¸Þ´º¸¦ 'Á¡°ËÁß'À¸·Î ¶Ù¾îÁØ´Ù.
extern BOOL bCheckHostNameandPort ;			//tjclan.cpp
void WebDB_Thread::CheckHostNamePort(char *hostname, int port)
{
	if(hostname == NULL) {
		bCheckHostNameandPort = FALSE;
		return;
	}
	if(port == 0){
		bCheckHostNameandPort = FALSE;
		return;
	}

	bCheckHostNameandPort = TRUE;
}
















int WebDB_Thread::start_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address)
{
	return 0;
		//ktj : ³¡³»±â °ú±ÝÃ³¸®¿ëÀ» »õ·Î ¸¸µé¾î ³ÖÀ½.
		AUTH_QUE AuthQueTmp;
		ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

		/*
		//ktj : ¿øÆÇÀÓ.
		if(Connect[fd].howmanyTime==0) return 0;		//Á¦´ë·Î ·Î±äÀÌ ¾ÈµÇ¼­ ³¡³»±â °ú±ÝÃ³¸® ¾ÈÇÔ.

		// Å¥¿¡ Á¤º¸¸¦ ³Ö´Â´Ù£®
		AuthQueTmp.fdid = Connect[fd].fdid;
		//AuthQueTmp.command = AUTH_QUE_COMMAND_AUTH;
		//ktj : »õ·Î³ÖÀ½.
		AuthQueTmp.command = AUTH_QUE_COMMAND_AUTH_KTJEND;
		
		strncpy( AuthQueTmp.cdkey, Connect[fd].cdkey, sizeof( AuthQueTmp.cdkey ) );
		strncpy( AuthQueTmp.isaokey, Connect[fd].accountid, sizeof( AuthQueTmp.isaokey ) );
		strncpy( AuthQueTmp.password, Connect[fd].passwd, sizeof( AuthQueTmp.password ) );
		strncpy( AuthQueTmp.ip_address, Connect[fd].ip_address, sizeof( AuthQueTmp.ip_address ) );
		AuthQueTmp.howmanyTime = Connect[fd].howmanyTime;
		*/

		AuthQueTmp.fdid = 100;
		//AuthQueTmp.command = AUTH_QUE_COMMAND_AUTH;
		//ktj : »õ·Î³ÖÀ½.
		//AuthQueTmp.command = AUTH_QUE_COMMAND_AUTH_KTJEND;
		AuthQueTmp.command = AUTH_QUE_CMD_CL_MAKE;          // ÀÎÁõÇÏ´Ù
		
		strncpy( AuthQueTmp.cdkey, cdkey, sizeof( AuthQueTmp.cdkey ) );
		strncpy( AuthQueTmp.isaokey, accountid, sizeof( AuthQueTmp.isaokey ) );
		strncpy( AuthQueTmp.password, passwd, sizeof( AuthQueTmp.password ) );
		strncpy( AuthQueTmp.ip_address, ip_address, sizeof( AuthQueTmp.ip_address ) );

		time_t myTime;
		time( ( time_t* )&myTime );
		AuthQueTmp.howmanyTime = myTime;//Connect[fd].howmanyTime = myTime;
	
		// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "start_GOLDmoney¿¡·¯\n" );
		fd2("³¡³»±â °ú±Ý ¿¡·¯ Å¥¿¡ µî·Ï¾ÈµÊ. %s \n", accountid );
		return 0;
	}
	return 1;
}

//ktj »õ·Î ¸¸µê.: ³¡ °ú±ÝÃ³¸® 
int WebDB_Thread::end_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address)
{
		//ktj : ³¡³»±â °ú±ÝÃ³¸®¿ëÀ» »õ·Î ¸¸µé¾î ³ÖÀ½.
		AUTH_QUE AuthQueTmp;


		/*
		//ktj : ¿øÆÇÀÓ.
		if(Connect[fd].howmanyTime==0) return 0;		//Á¦´ë·Î ·Î±äÀÌ ¾ÈµÇ¼­ ³¡³»±â °ú±ÝÃ³¸® ¾ÈÇÔ.

		// Å¥¿¡ Á¤º¸¸¦ ³Ö´Â´Ù£®
		AuthQueTmp.fdid = Connect[fd].fdid;
		//AuthQueTmp.command = AUTH_QUE_COMMAND_AUTH;
		//ktj : »õ·Î³ÖÀ½.
		AuthQueTmp.command = AUTH_QUE_COMMAND_AUTH_KTJEND;
		
		strncpy( AuthQueTmp.cdkey, Connect[fd].cdkey, sizeof( AuthQueTmp.cdkey ) );
		strncpy( AuthQueTmp.isaokey, Connect[fd].accountid, sizeof( AuthQueTmp.isaokey ) );
		strncpy( AuthQueTmp.password, Connect[fd].passwd, sizeof( AuthQueTmp.password ) );
		strncpy( AuthQueTmp.ip_address, Connect[fd].ip_address, sizeof( AuthQueTmp.ip_address ) );
		AuthQueTmp.howmanyTime = Connect[fd].howmanyTime;
		*/

		AuthQueTmp.fdid = 100;
		//AuthQueTmp.command = AUTH_QUE_COMMAND_AUTH;
		//ktj : »õ·Î³ÖÀ½.
		AuthQueTmp.command = AUTH_QUE_CMD_CL_MEMBER_MAKE;
		
		strncpy( AuthQueTmp.cdkey, cdkey, sizeof( AuthQueTmp.cdkey ) );
		strncpy( AuthQueTmp.isaokey, accountid, sizeof( AuthQueTmp.isaokey ) );
		strncpy( AuthQueTmp.password, passwd, sizeof( AuthQueTmp.password ) );
		strncpy( AuthQueTmp.ip_address, ip_address, sizeof( AuthQueTmp.ip_address ) );
		AuthQueTmp.howmanyTime = 100;//Connect[fd].howmanyTime;
	
		// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );


		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦ÇÔ.
		//nrproto_ClientLogin_send( fd, 0, "end_GOLDmoney ¿¡·¯\n" );

		fd2("³¡³»±â °ú±Ý ¿¡·¯ Å¥¿¡ µî·Ï¾ÈµÊ. %s \n", accountid );
		return 0;
	}
	return 1;
}
/*/////////////////////////////////////////////////////////////////////////// END
: ÇÏ ´Â ÀÏ :  WebDB¿¡ Á¢¼ÓÇØ¼­ ÇÒÀÏÀ» Áö½ÃÇÏ´Â Áö½ÃÇÔ¼öµé.
///////////////////////////////////////////////////////////////////////////*/

char web_DBip0[64] = {0,};
int  web_DBport0 = 0;
char web_DBip1[64] = {0,};
int  web_DBport1 = 0;
int  nClanTicket = 0; //ticket¹øÈ£



void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1)
{
	strcpy(web_DBip0, ip0);
	strcpy(web_DBip1, ip1);

	web_DBport0 = port0;
	web_DBport1 = port1;

}

void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1,int ticket)
{
	strcpy(web_DBip0, ip0);
	strcpy(web_DBip1, ip1);

	web_DBport0 = port0;
	web_DBport1 = port1;
#ifdef __CLANSERVER__
	nClanTicket = 9999;
#else
	nClanTicket = ticket;
#endif
}

//winmain.cpp¿¡¼­ ¼ÂÆÃµÊ.
void web_DB_start(char *hostN0, int port0, char *hostN1, int port1);
void web_DB_start()
{
	//dns
	//char hostN0[] ="clanserver.pristontale.com" ; //"211.39.144.157"
	//char hostN1[] = "image.pristontale.com";//"211.39.144.158";

	//ip
	char hostN0[] ="211.39.144.157";
	char hostN1[] ="211.39.144.158";



	//char hostN0[] = "211.39.144.155";
	//char hostN1[] = "211.39.144.154";

	int port0 = 80;
	int port1 = 80;

	//ktj : ¿øº» : ¹«Á¶°Ç web_DBip0¸¦ »ç¿ëÅä·Ï ¹Ù…fÀ½(¼³Á¤À» ¾ÈÇØµµ µÇµµ·Ï)
	//if(web_DBip0[0]==0) {		//À¥µðºñ¼³Á¤¾ÈµÇÀÖÀ¸¸é ±×³É ·ÎÄ® º¯¼ö»ç¿ëÇÔ.
	//	 web_DB_start(hostN0, port0, hostN1, port1 );
	//}
	//else {
		web_DB_start(web_DBip0, web_DBport0 , web_DBip1, web_DBport1 );
	//}
	
	//ktj : ÀÓ½Ã
	//web_DB_start(hostN0, port0, hostN1, port1 );

	//web_DB_start(NULL, port0, NULL, port1  );
}


BOOL bip_port_error = FALSE;
//KTJ : ÀÓ½Ã ÇÔ¼öµé
////ktj : winmain.cppÀÇ int SetGameMode( int mode ) ¿¡ ¼ÂÆÃµÇ¾îÁ® ÀÖ´Â°ÍÀÓ
void web_DB_start(char *hostN0, int port0, char *hostN1, int port1)
{		
	if((hostN0 == NULL)||(port0 == 0) || (hostN1 == NULL)|| (port1 == 0)) {
		bip_port_error = TRUE;


		//¸Þ½ÃÁö °æ°í¹®¶§¹®¿¡ À¥µðºñ´Â ¼³Á¤µÇ¾î¾ßÇÔ.
		WebDB.AUTH_init(10);
		WebDB.ThreadS.flag = FLAG_WAIT;
		WebDB.Suspend();     //ÀÏ´Ü ÁßÁö

		while(1) {
			if(WebDB.ThreadS.flag == FLAG_WAIT)
				break;
		}

		return;
	}
	static int cnt=0;
	if(cnt==1) return;
	cnt=1;
	/*
	char hostN[] =  "211.39.144.157";
	char hostN1[] = "211.39.144.158";
	int port = 80;
	int port1 = 80;
	*/



	//===================================================================================
	//ÁÖÀÇ : ¼ÂÆÃ ÇØ¾ßÇÔ.================================================================
	//===================================================================================

	//iCheck.init(1, 30);		//À¥db»ç¿ë½Ã¸¶´Ù ¼ÂÆÃ
	iCheck.init(1, 5);		//À¥db»ç¿ë½Ã¸¶´Ù ¼ÂÆÃ

	//Å¬·£¼­¹ö È£½ºÆ® ¾ÆÀÌÇÇ°¡ 0, ±×¸®°í Æ÷Æ®°¡ 0 ÀÏ °æ¿ì È®ÀÎÇÏ´Â ÇÔ¼ö
	WebDB.CheckHostNamePort(hostN0,port0); 

	iCheck.init_HostName_Port (hostN0, port0);
	iCheck.init_HostName_Port1(hostN1 ,port1);		//¼ÂÆÃÇÒ°Í.

	//===================================================================================
	//ÁÖÀÇ : ¼ÂÆÃ ÇØ¾ßÇÔ.================================================================
	//===================================================================================

	WebDB.AUTH_init(10);
	WebDB.ThreadS.flag = FLAG_WAIT;
	WebDB.Suspend();     //ÀÏ´Ü ÁßÁö

	while(1) {
		if(WebDB.ThreadS.flag == FLAG_WAIT)
			break;
	}
}


int web_DB_state_FLAG_WAIT()
{
	if(WebDB.ThreadS.flag == FLAG_WAIT)
		return 1;

	return 0;
}


void web_DB_main()
{
	WebDB.main();
}

void web_DB_end()
{
	WebDB.end();
}



//ÀÌÀÓ°ü·Ã ÇÃ·¡±×================================================================




int AUTH_proc_isKPFlag( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isKPFlag( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isKPFlag( int quenum, int threadindex)
{
	char *ClanZang_ID,*ClanZang_ChaName,*gserver,*PFlag,*Gubun,*ClanName;
	int knret = 1, iBadMsg = 0;

	//id = AUTH_que[quenum].id;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	PFlag = AUTH_que[quenum].PFlag;
	Gubun = AUTH_que[quenum].Gubun;
	ClanName = AUTH_que[quenum].clanName;
	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.isKPFlag(ClanZang_ID,ClanName,ClanZang_ChaName,gserver, PFlag,Gubun);


	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_isKPFlag_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isKPFlag_Result( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isKPFlag_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 0:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		break;
	case 1:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.		
		break;	
	case 100:				//ÀÏ¹Ý ¸â¹ö,
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;		
	default :
		ANSdata.ret_val = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	//ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}

int WebDB_Thread::isKPFlag(char *userid, char *clName, char *chName,char *gserver, char *PFlag, char *Gubun)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isKPFlag;          // ÀÎÁõÇÏ´Ù
	
	strncpy( AuthQueTmp.Gubun, Gubun, sizeof( AuthQueTmp.Gubun ) );
	strncpy(AuthQueTmp.ClanZang_ID, userid, sizeof( AuthQueTmp.ClanZang_ID ));
	strncpy( AuthQueTmp.clanName, clName, sizeof( AuthQueTmp.clanName ) );	
	strncpy( AuthQueTmp.ClanZang_ChaName, chName, sizeof( AuthQueTmp.ClanZang_ChaName ) );	
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );
	strncpy( AuthQueTmp.PFlag, PFlag, sizeof( AuthQueTmp.PFlag ) );
	

	

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}

int WebDB_Thread::AppointSubChip(char* userid,char* chaname,char* clanname,char *gserver,char* clanwon)//ºÎÅ¬·£Àå ÀÓ¸í
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_AppointSubChip;          // ÀÎÁõÇÏ´Ù
		
	strncpy(AuthQueTmp.ClanZang_ID, userid, sizeof( AuthQueTmp.ClanZang_ID ));
	strncpy( AuthQueTmp.clanName, clanname, sizeof( AuthQueTmp.clanName ) );	
	strncpy( AuthQueTmp.ClanZang_ChaName, chaname, sizeof( AuthQueTmp.ClanZang_ChaName ) );	
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );
	strncpy(AuthQueTmp.ClanWon_ChaName,clanwon,sizeof(AuthQueTmp.ClanWon_ChaName));;
	
	

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}



int AUTH_proc_AppointSubChip( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_AppointSubChip( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_AppointSubChip( int quenum, int threadindex)
{
	char *ClanZang_ID,*ClanZang_ChaName,*gserver,*ClanName;
	int knret = 1, iBadMsg = 0;
	//char *gserver;
	char *clanwon;

	//id = AUTH_que[quenum].id;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;	
	clanwon = AUTH_que[quenum].ClanWon_ChaName;
	ClanName = AUTH_que[quenum].clanName;
	
	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.AppointSubChip(gserver,clanwon);

	//ºÎÅ¬·£Ä¨ ÀÓ¸íÀÌ ¼º°øµÇ¸é ÇÃ·¡±×°ª ¼¼ÆÃ(ÇÃ·¡±×°ª : 300)
	//if(knret == 1)
	//{
	//	knret = iCheck.isKPFlag(ClanZang_ID,ClanZang_ChaName,ClanName,gserver,"300","0");
	//}

	

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_AppointSubChip_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_AppointSubChip_Result( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_AppointSubChip_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 0://Å¬·£¿øÀÌ ¾Æ´Ô
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		break;
	case 3://ºÎÅ¬·£Ä¨ÀÌ Á¸ÀçÇÔ
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.		
		break;
	case 2: //Å¬·£Ä¨ÀÌ°Å³ª 
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.		
		break;	
	case 1: //º¯°æ¼º°ø
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.		
		break;

	case 100:				//ÀÏ¹Ý ¸â¹ö,
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;		
	default :
		ANSdata.ret_val = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	//ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}

	
int WebDB_Thread::ReleaseSubChip(char* userid,char* chaname,char* clanname,char *gserver,char* clanwon) //ºÎ Å¬·£Àå ÇØÀÓ
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReleaseSubChip;          // ÀÎÁõÇÏ´Ù
		
	strncpy(AuthQueTmp.ClanZang_ID, userid, sizeof( AuthQueTmp.ClanZang_ID ));
	strncpy( AuthQueTmp.clanName, clanname, sizeof( AuthQueTmp.clanName ) );	
	strncpy( AuthQueTmp.ClanZang_ChaName, chaname, sizeof( AuthQueTmp.ClanZang_ChaName ) );	
	strncpy( AuthQueTmp.gserver, gserver, sizeof( AuthQueTmp.gserver ) );
	strncpy(AuthQueTmp.ClanWon_ChaName,clanwon,sizeof(AuthQueTmp.ClanWon_ChaName));;
	
	

	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}

//ºÎÅ¬·£Àå ÇØÀÓ
int AUTH_proc_ReleaseSubChip( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReleaseSubChip(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReleaseSubChip( int quenum, int threadindex)
{
	int knret = 1, iBadMsg = 0;
	char *gserver;
	char *clanwon;
	char *ClanZang_ID,*ClanZang_ChaName,*ClanName;

	//id = AUTH_que[quenum].id;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;	
	clanwon = AUTH_que[quenum].ClanWon_ChaName;
	ClanName = AUTH_que[quenum].clanName;
	
	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.ReleaseSubChip(gserver,clanwon);
	//if(knret == 1) //ºÎÅ¬·£Ä¨ ÇØÀÓ°ü·Ã ÇÃ·¡±× ¼¼ÆÃ(301)
	//{
	//	knret = iCheck.isKPFlag(ClanZang_ID,ClanZang_ChaName,ClanName,gserver,"301","0");
	//}

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_ReleaseSubChip_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReleaseSubChip_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReleaseSubChip_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 0: //Å¬·£¿øÀÌ ¾Æ´Ò°æ¿ì
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		break;
	case 1://ÇØÀÓ ¼º°ø
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		break;
	case 2: //Å¬·£ÀåÀÌ°Å³ª ºÎÅ¬·£ÀÏ °æ¿ì
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.		
		break;	
	case 100:				//ÀÏ¹Ý ¸â¹ö,
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;		
	default :
		ANSdata.ret_val = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	//ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	return TRUE;
}

/*////////////////////////////////////////////////////////////////////////////////
WAV ÆÄÀÏ °¡Á®¿À±â
////////////////////////////////////////////////////////////////////////////////*/
int	WebDB_Thread::GetWavFile(char* FileName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_GetWavFile;          // ÀÎÁõÇÏ´Ù
		
	strncpy(AuthQueTmp.szWavFileName, FileName, sizeof( AuthQueTmp.szWavFileName ));
	
	time_t myTime;
	time( ( time_t* )&myTime );
	AuthQueTmp.howmanyTime = myTime;
	
	// Å¥¸¦ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}
int AUTH_proc_GetWavFile( int quenum, int threadindex)
{
	return  WebDB.AUTH_proc_GetWavFile(quenum,threadindex);
}

int WebDB_Thread::AUTH_proc_GetWavFile( int quenum, int threadindex)
{
	int knret = 1, iBadMsg = 0;
	char *szFileName;	

	szFileName = AUTH_que[quenum].szWavFileName;
	
	
	//id¿¡ ÇØ´çÇÏ´Â ÀÚ°¡ Å¬·£¸â¹ö¶ó¸é, 100(Å¬·£¸â¹ö), 101(Å¬·£¯…:Å¬·£¸íÀ»°¡Á®¿È), ¾Æ´Ï¸é 102(Å¬·£¿¡ µé¾îÀÖÁö¾ÊÀ½)
	knret = iCheck.GetWavFile(szFileName);
	//if(knret == 1) //ºÎÅ¬·£Ä¨ ÇØÀÓ°ü·Ã ÇÃ·¡±× ¼¼ÆÃ(301)
	//{
	//	knret = iCheck.isKPFlag(ClanZang_ID,ClanZang_ChaName,ClanName,gserver,"301","0");
	//}

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
int AUTH_proc_GetWavFile_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_GetWavFile_Result(quenum,threadindex);
}

int WebDB_Thread::AUTH_proc_GetWavFile_Result( int quenum, int threadindex)
{
	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 0: //Å¬·£¿øÀÌ ¾Æ´Ò°æ¿ì
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		break;
	case 1://ÇØÀÓ ¼º°ø
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		break;
	case 2: //Å¬·£ÀåÀÌ°Å³ª ºÎÅ¬·£ÀÏ °æ¿ì
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.		
		break;	
	case 100:				//ÀÏ¹Ý ¸â¹ö,
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;		
	default :
		ANSdata.ret_val = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	//ktj : ÀÏ´Ü »èÁ¦
	// °á°ú¸¦ Á¶»çÇÏ°í µ¹·Á ÁØ´Ù£®
	//ktj : µ¹·ÁÁÖ´ÂºÎºÐÀ» ³Ö¾î¾ßÇÔ.
	/*
	nrproto_ClientLogin_send( 
			fd, 
			iResultCode,
			szData);
	//nrproto_ClientLogin_send( fd, 1, "OK" );
	*/
	//ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}

	return TRUE;
}




//=================================================================



//sod ¼ÂÆÃ
int sod2INFOindex(char *UserId, char* CharName,char* GServer , int Index)
{
	WebDB.sod2INFOindex(UserId, CharName,GServer , Index);
	return TRUE;
}


//sod ¼ÂÆÃ
int WebDB_Thread::sod2INFOindex(char *UserId, char* CharName,char* GServer , int Index)
{
	Resume();      //Àç°³


	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp,sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_SOD2;          // Å¬·£¸â¹öÀÎÁö¸¦ ¾Ë·Á´Þ¶ó..	
	

	strncpy( AuthQueTmp.id, UserId, sizeof( AuthQueTmp.id ) );
	strncpy( AuthQueTmp.charId, CharName, sizeof( AuthQueTmp.charId ) );
	strncpy( AuthQueTmp.gserver, GServer, sizeof( AuthQueTmp.gserver) );
	AuthQueTmp.sod2index = Index;
	
	//Å¥¿¡ µî·Ï
	if( AUTH_addQue( &AuthQueTmp ) < 0 ){
		// ½ÇÆÐÇÏ¸é ¿¡·¯¸¦ µ¹·Á ÁØ´Ù£®±âÅ¸ÀÇ ¿¡·¯£®
		//nrproto_CharLogin_send( fd, AUTH_ERROR_OTHER, "authorization required\n" );

		//ktj : ÇÁÅ×¶§¹®¿¡ ÀÏ´Ü »èÁ¦
		//nrproto_ClientLogin_send( fd, 0, "make_Clan() ¿¡·¯\n" );
		fd2("make_Clan() ¿¡·¯   : Å¥¿¡ µî·Ï¾ÈµÊ");
		return 0;
	}
	return 1;
}





/*///////////////////////////////////////
: ÇÔ ¼ö ¸í :  

: ÇÏ ´Â ÀÏ :  Å¬·£¸â¹öÀÎÁö¸¦ ¾Ë¾Æ³»´ÂÇÔ¼ö
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
/////////////////////////////////////////*/
int AUTH_proc_sodindex( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_sodindex( quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_sodindex( int quenum, int threadindex)
{

	int knret = 1, iBadMsg = 0;
	knret = iCheck.read_sod2(AUTH_que[quenum].id, AUTH_que[quenum].charId,AUTH_que[quenum].gserver, AUTH_que[quenum].sod2index  , AUTH_que[quenum].szSod2Buff);

	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].result = knret;
	// °á°ú¸¦ °Ý³³
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
   

int AUTH_proc_sodindex_Result( int quenum, int threadindex)
{
	return WebDB.AUTH_proc_sodindex_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_sodindex_Result( int quenum, int threadindex)
{

	cSinSod2.RecvWebData(AUTH_que[quenum].sod2index , AUTH_que[quenum].szSod2Buff);

	/*

	char *aszAuthErrStr[] = {
	"OK",
	"Err CDKEY", 
	"Err ISAO_ID", 
	"Err PASSWORD", 
	"Err EXPIRE", 
	"Err LOCOUT", 
	"Err ISAO_DB", 
	"Err OTHER", 
	""
	};

	char szData[128];
	
	if( AUTH_que[quenum].result == 0 ){
		szData[0] = '\0';
	}else{
		sprintf( szData, "faild" );
	}

	char szBuffer[256];

	// ¿¡·¯ ¸Þ½ÃÁö Å×ÀÌºíÀÇ ¹üÀ§³»¶ó¸é ¹®ÀÚ·Î Ç¥½Ã
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
		sprintf( szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result] );
	}else{
		sprintf( szBuffer, "ExtraCode=%d", AUTH_que[quenum].result );
	}

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// µðÆúÆ®´Â ±âÅ¸ÀÇ ¿¡·¯

	
	// ÃÖÁ¾ÀûÀ¸·Î Å¬¶óÀÌ¾ðÆ®¿¡°Ô µ¹·Á ÁÖ´Â ÄÚµå
	switch( iResultCode ){
	case 0:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		strcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 1:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		strcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 5:
	case 4:
	case 3:
	case 2:
		ANSdata.ret_val = iResultCode;				//tjclan.cpp¿¡ Á¤ÀÇµÈ º¯¼ö¿¡ ´äº¯À» ³Ö´Â´Ù.
		strcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 100:				//ÀÏ¹Ý ¸â¹ö,
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;	// ±âÅ¸ÀÇ ¿¡·¯
		break;
	}


	fd2("Å¬·£¸â¹ö¿©ºÎÀÇ ´äº¯À» ¹ÞÀ½. :  ret_val %d  ", ANSdata.ret_val);

	

	// ¹üÀ§³»¿¡ µé¾î°¡°í ÀÌ¸£´Ù OK.
	if( 0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END ){
	}else{
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	}
	*/

	return TRUE;
}
