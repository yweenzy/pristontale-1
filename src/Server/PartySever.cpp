#define _WIN32_WINNT    0x0403  /* Get new material from the headers */
#define _WIN32_WINDOWS  0x0403

#include <windows.h>
#include <io.h>
#include <stdio.h>         /* for sprintf                           */
#include <string.h>        /* for strlen                            */
#include <memory.h>
#include <process.h>       /* for _beginthread                      */
//#include <winsock2.h>
//#include <mswsock.h>

#include "..\\resource.h"
#include "..\\smwsock.h"

#include "..\\smlib3d\\smd3d.h"
#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "..\\field.h"
#include "..\\sinbaram\\sinlinkheader.h"
#include "Language\\language.h"
#include "partymsg.h"
#include "onserver.h"

extern DWORD	dwPlayServTime;

/*
	//ÆÄÆ¼Àå
	int	CreateParty( rsPLAYINFO *lpPlayInfo );			//ÆÄÆ¼»ý¼º - ( ÃÊ±â ÆÄÆ¼¿ø Á¤º¸ )
	int	JoinPartyPlayer( rsPLAYINFO *lpPlayInfo );		//ÆÄÆ¼¿¡ °¡ÀÔ
	int	DeletePartyPlayer( rsPLAYINFO *lpPlayInfo );	//ÆÄÆ¼¿¡¼­ Å»Åð
	int	UpdatePartyPlayer();							//ÆÄÆ¼¿ø ¾÷µ¥ÀÌÆ®
	int	LeavePartyMaster( rsPLAYINFO *lpPlayInfo );		//ÆÄÆ¼Àå ÀÌÀÓ
	int	ReleaseParty();									//ÆÄÆ¼Àå ÇØ»ê

	//ÆÄÆ¼¿ø
	int	JoinParty( rsPLAYINFO *lpPlayMaster );			//ÆÄÆ¼ °¡ÀÔ ½ÅÃ»
	int	SecedeParty ( rsPLAYINFO *lpPlayMaster );		//ÆÄÆ¼ Å»Åð
*/
/*
	////////////// ÆÄÆ¼ °ü·Ã Á¤º¸ ///////////////////
	DWORD			dwPartyInfo;						//ÆÄÆ¼ Á¤º¸
	rsPLAYINFO		*lpPartyMaster;						//ÆÄÆ¼Àå Æ÷ÀÎÆ®
	DWORD			PartyMasterObjectCode;				//ÆÄÆ¼Àå ¿ÀºêÁ§Æ® ÄÚµå
	rsPLAYINFO		*lpPartyPlayers[PARTY_PLAYER_MAX];	//ÆÄÆ¼¿ø Æ÷ÀÎÆ®
	DWORD			dwPartyObjectCode[PARTY_PLAYER_MAX];//ÆÄÆ¼¿øÀÇ ¿ÀºêÁ§Æ® ÄÚµå
*/

//Ä³¸¯ÅÍ¸¦ Ã£´Â´Ù ( ³ªÁß¿¡ »¡¸® ¯À»¼ö ÀÖ°Ô ÄÚµåÈ­ ½ÃÄÑ ¹Ù²ã Áà¾ß ÇÔ )
rsPLAYINFO *srFindUserFromSerial( DWORD dwObjectSerial );
//¾ÆÀÌÅÛ Á¤º¸¼Û¼ö½Å ±¸Á¶Ã¼¿¡ º¸¾ÈÄÚµå »ðÀÔ ( ÄÄÆÄÀÏ½Ã ¼­¹ö¿¡¼­¸¸ Á¸Àç )
int	rsRegist_ItemSecCode( rsPLAYINFO *lpPlayInfo , TRANS_ITEMINFO *lpTransItemInfo , int NewItem );


//ÆÄÆ¼¿ø¿¡°Ô µ¥ÀÌÅ¸ º¸³¿
int rsPLAYINFO::SendPartyData( rsPLAYINFO *lpPlayInfo_From , char *szData  )
{
	int size;
	int cnt;


	size = ((smTRANS_COMMAND *)szData)->size;

	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]!=lpPlayInfo_From ) {
			if ( lpPartyPlayers[cnt]->lpsmSock ) {
				lpPartyPlayers[cnt]->lpsmSock->Send2( szData , size , TRUE );
			}
		}
	}


	return TRUE;
}

//ÆÄÆ¼¿ø¿¡°Ô ¸Þ¼¼Áö º¸³¿
int rsPLAYINFO::SendPartyMessage( char *szMessage , DWORD dwCode )
{
	TRANS_CHATMESSAGE	TransChatMessage;
	int cnt;

	if ( lpPartyMaster ) {
		lstrcpy( TransChatMessage.szMessage , szMessage );
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = dwCode;
		TransChatMessage.dwObjectSerial = 0;

		for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
			if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock ) {
				lpPartyPlayers[cnt]->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
			}
		}
	}
	else {
		lstrcpy( TransChatMessage.szMessage , szMessage );
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		if ( lpsmSock ) 
			lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
	}

	return TRUE;
}


//ÆÄÆ¼»ý¼º
int rsPLAYINFO::CreateParty( rsPLAYINFO *lpPlayInfo )
{
	int cnt;

	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		lpPartyPlayers[cnt]=0;
		dwPartyObjectCode[0] = 0;
	}

	PartyUpdateFlag = 0;
	dwPartyInfo = PARTY_STATE_MASTER;
	lpPartyMaster = this;

	//ÆÄÆ¼¿ø ¼¼ÆÃ
	lpPartyPlayers[0] = this;
	dwPartyObjectCode[0] = dwObjectSerial;
	if ( this!=lpPlayInfo ) {
		lpPartyPlayers[1] = lpPlayInfo;
		dwPartyObjectCode[1] = lpPlayInfo->dwObjectSerial;
	
		lpPlayInfo->dwPartyInfo = PARTY_STATE_MEMBER;
		lpPlayInfo->lpPartyMaster = this;
	}

	UpdatePartyPlayer();

	return TRUE;
}

//ÆÄÆ¼¿¡ °¡ÀÔ
int	rsPLAYINFO::JoinPartyPlayer( rsPLAYINFO *lpPlayInfo )
{
	int cnt;

	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]==lpPlayInfo ) {
			//ÀÌ¹Ì °¡ÀÔµÈ À¯Àú
			return FALSE;
		}
	}

	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( !lpPartyPlayers[cnt] ) {
			lpPartyPlayers[cnt] = lpPlayInfo;
			dwPartyObjectCode[cnt] = lpPlayInfo->dwObjectSerial;
			lpPlayInfo->dwPartyInfo = PARTY_STATE_MEMBER;
			lpPlayInfo->lpPartyMaster = this;
			UpdatePartyPlayer();
			return TRUE;
		}
	}

	return FALSE;
}

//ÆÄÆ¼¿¡¼­ Å»Åð
int	rsPLAYINFO::DeletePartyPlayer( rsPLAYINFO *lpPlayInfo )
{
	int cnt;
	smTRANS_COMMAND		TransCommand;

	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]==lpPlayInfo ) {
			lpPartyPlayers[cnt]->dwPartyInfo = PARTY_STATE_NONE;
			lpPartyPlayers[cnt]->lpPartyMaster = NULL;
			lpPartyPlayers[cnt] = 0;
			dwPartyObjectCode[cnt] = 0;
			UpdatePartyPlayer();


			if ( lpPlayInfo->lpsmSock ) {
				TransCommand.code = smTRANSCODE_PARTY_RELEASE;
				TransCommand.size = sizeof(smTRANS_COMMAND);
				TransCommand.WParam = dwObjectSerial;
				TransCommand.LParam = 0;
				TransCommand.SParam = 0;

				lpPlayInfo->lpsmSock->Send( (char *)&TransCommand , TransCommand.size , TRUE );
			}
			return TRUE;
		}
	}

	return FALSE;
}

//ÆÄÆ¼¿ø º¯°æ
int	rsPLAYINFO::ChangePartyPlayer( rsPLAYINFO *lpOldPlayInfo , rsPLAYINFO *lpNewPlayInfo )
{
	int cnt;

	if ( !lpPartyMaster ) {
		//ÆÄÆ¼ÀåÀÌ ¾Æ´Ñ °æ¿ì ( ÆÄÆ¼¿ø ÇØÁ¦ )
		lpNewPlayInfo->dwPartyInfo = PARTY_STATE_NONE;
		lpNewPlayInfo->lpPartyMaster = NULL;
		return FALSE;
	}

	//º¯°æµÈ ÆÄÆ¼¿øÀÌ ÆÄÆ¼ÀåÀÏ °æ¿ì
	if ( lpOldPlayInfo==lpPartyMaster ) {
		for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
			if ( lpPartyPlayers[cnt] ) {
				lpPartyPlayers[cnt]->lpPartyMaster = lpNewPlayInfo;
			}
		}
		lpNewPlayInfo->dwPartyInfo = PARTY_STATE_MASTER;
		lpNewPlayInfo->lpPartyMaster = lpNewPlayInfo;
	}

	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyMaster->lpPartyPlayers[cnt]==lpOldPlayInfo ) {
			lpPartyMaster->lpPartyPlayers[cnt] = lpNewPlayInfo;
			break;
		}
	}

	lpOldPlayInfo->dwPartyInfo = PARTY_STATE_NONE;
	lpOldPlayInfo->lpPartyMaster = NULL;

	//lpNewPlayInfo->dwPartyInfo = PARTY_STATE_NONE;
	//lpNewPlayInfo->lpPartyMaster = NULL;

	return TRUE;
}

//ÆÄÆ¼¿ø Á¤º¸ ¾÷µ¥ÀÌÆ®
int	rsPLAYINFO::UpdatePartyPlayer()
{
	int cnt,cnt2;
	TRANS_PARTY_USERS	TransPartyUsers;
	int	LevelAvg;

	cnt = 0;
	cnt2 = 0;

	if ( !lpPartyMaster ) return FALSE;

	//ÆÄÆ¼Àå Á¤º¸
	TransPartyUsers.PartyUser[cnt2].dwObjectSerial = lpPartyMaster->dwObjectSerial;
	lstrcpy( TransPartyUsers.PartyUser[cnt2].szName , lpPartyMaster->smCharInfo.szName );
	lstrcpy( TransPartyUsers.PartyUser[cnt2].szModelName , lpPartyMaster->smCharInfo.szModelName );
	lstrcpy( TransPartyUsers.PartyUser[cnt2].szModelName2 , lpPartyMaster->smCharInfo.szModelName2 );
	TransPartyUsers.PartyUser[cnt2].Life[0] = lpPartyMaster->smCharInfo.Life[0];
	TransPartyUsers.PartyUser[cnt2].Life[1] = lpPartyMaster->smCharInfo.Life[1];
	TransPartyUsers.PartyUser[cnt2].Level = lpPartyMaster->smCharInfo.Level;
	TransPartyUsers.PartyUser[cnt2].x = lpPartyMaster->Position.x;
	TransPartyUsers.PartyUser[cnt2].z = lpPartyMaster->Position.z;
	LevelAvg = lpPartyMaster->smCharInfo.Level;
	cnt2++;

	//ÆÄÆ¼¿ø Á¤º¸
	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]!=lpPartyMaster ) {
			TransPartyUsers.PartyUser[cnt2].dwObjectSerial = lpPartyPlayers[cnt]->dwObjectSerial;
			lstrcpy( TransPartyUsers.PartyUser[cnt2].szName , lpPartyPlayers[cnt]->smCharInfo.szName );
			lstrcpy( TransPartyUsers.PartyUser[cnt2].szModelName , lpPartyPlayers[cnt]->smCharInfo.szModelName );
			lstrcpy( TransPartyUsers.PartyUser[cnt2].szModelName2 , lpPartyPlayers[cnt]->smCharInfo.szModelName2 );
			TransPartyUsers.PartyUser[cnt2].Life[0] = lpPartyPlayers[cnt]->smCharInfo.Life[0];
			TransPartyUsers.PartyUser[cnt2].Life[1] = lpPartyPlayers[cnt]->smCharInfo.Life[1];
			TransPartyUsers.PartyUser[cnt2].Level = lpPartyPlayers[cnt]->smCharInfo.Level;
			TransPartyUsers.PartyUser[cnt2].x = lpPartyPlayers[cnt]->Position.x;
			TransPartyUsers.PartyUser[cnt2].z = lpPartyPlayers[cnt]->Position.z;
			LevelAvg += lpPartyPlayers[cnt]->smCharInfo.Level;
			cnt2 ++;
		}
	}

	PartyUserCount = cnt2;
	PartyLevelAverage = LevelAvg/cnt2; 

	ZeroMemory( TransPartyUsers.dwTemp , sizeof(DWORD)*8 );

	TransPartyUsers.dwObjectSerial = dwObjectSerial;
	TransPartyUsers.PartyUserCount = cnt2;
	TransPartyUsers.size = sizeof(TRANS_PARTY_USERS)-((PARTY_PLAYER_MAX-cnt2)*sizeof(_PARTY_USER));
	TransPartyUsers.code = smTRANSCODE_PARTY_UPDATE;

	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock ) {
			lpPartyPlayers[cnt]->lpsmSock->Send( (char *)&TransPartyUsers , TransPartyUsers.size , TRUE );
		}
	}

	return TRUE;
}
/*
struct _PARTY_PLAYINFO {
	DWORD	dwObjectSerial;			//°´Ã¼ °íÀ¯¹øÈ£
	DWORD	Level;					//·¹º§
	short	Life[2];				//»ý¸í·Â
};

struct	TRANS_PARTY_PLAYINFO {
	int		size,code;

	DWORD	dwObjectSerial;
	DWORD	dwTemp;

	int		PartyUserCount;

	_PARTY_PLAYINFO	PlayInfo[PARTY_PLAYER_MAX];
};
*/

//ÆÄÆ¼¿ø Á¤º¸ ¾÷µ¥ÀÌÆ®
int	rsPLAYINFO::UpdatePartyPlayInfo()
{
	int cnt,cnt2;
	int	LevelAvg;
	TRANS_PARTY_PLAYINFO	TransPartyPlayInfo;

	cnt = 0;
	cnt2 = 0;

	PartyUpdateFlag = 0;

	//ÆÄÆ¼Àå Á¤º¸
	TransPartyPlayInfo.PlayInfo[cnt2].dwObjectSerial = dwObjectSerial;
	TransPartyPlayInfo.PlayInfo[cnt2].Life[0] = smCharInfo.Life[0];
	TransPartyPlayInfo.PlayInfo[cnt2].Life[1] = smCharInfo.Life[1];
	TransPartyPlayInfo.PlayInfo[cnt2].Level = smCharInfo.Level;
	TransPartyPlayInfo.PlayInfo[cnt2].x = Position.x;
	TransPartyPlayInfo.PlayInfo[cnt2].z = Position.z;
	LevelAvg = smCharInfo.Level;
	cnt2++;

	//ÆÄÆ¼¿ø Á¤º¸
	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]!=this ) {
			TransPartyPlayInfo.PlayInfo[cnt2].dwObjectSerial = lpPartyPlayers[cnt]->dwObjectSerial;
			TransPartyPlayInfo.PlayInfo[cnt2].Life[0] = lpPartyPlayers[cnt]->smCharInfo.Life[0];
			TransPartyPlayInfo.PlayInfo[cnt2].Life[1] = lpPartyPlayers[cnt]->smCharInfo.Life[1];
			TransPartyPlayInfo.PlayInfo[cnt2].Level = lpPartyPlayers[cnt]->smCharInfo.Level;
			TransPartyPlayInfo.PlayInfo[cnt2].x = lpPartyPlayers[cnt]->Position.x;
			TransPartyPlayInfo.PlayInfo[cnt2].z = lpPartyPlayers[cnt]->Position.z;
			LevelAvg += lpPartyPlayers[cnt]->smCharInfo.Level;
			cnt2 ++;
		}
	}

	PartyUserCount = cnt2;
	PartyLevelAverage = LevelAvg/cnt2; 

	TransPartyPlayInfo.dwTemp = 0;

	TransPartyPlayInfo.dwObjectSerial = dwObjectSerial;
	TransPartyPlayInfo.PartyUserCount = cnt2;
	TransPartyPlayInfo.size = sizeof(TRANS_PARTY_PLAYINFO);
	TransPartyPlayInfo.code = smTRANSCODE_PARTY_PLAYUPDATE;

	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock ) {
			lpPartyPlayers[cnt]->lpsmSock->Send( (char *)&TransPartyPlayInfo , TransPartyPlayInfo.size , TRUE );
		}
	}

	return TRUE;
}



//¸ÞÀÎ ¼­¹ö¿¡ ÆÄÆ¼¿ø Á¤º¸ ¾÷µ¥ÀÌÆ® /smTRANSCODE_PARTY_PLAYUPDATE
int	rsPLAYINFO::UpdateServerPartyPlayer( TRANS_PARTY_PLAYINFO *lpTransPartyPlayInfo )
{
	int cnt,cnt2;
	int LevelAvg;
	rsPLAYINFO *lpPlayInfo;
	DWORD	dwPartyCode1 , dwPartyCode2;

	LevelAvg = 0;

	if ( dwPartyInfo==PARTY_STATE_MASTER ) {

		dwPartyCode1 = 0;
		dwPartyCode2 = 0;

		for( cnt=0;cnt<lpTransPartyPlayInfo->PartyUserCount;cnt++ ) {
			dwPartyCode1 += lpTransPartyPlayInfo->PlayInfo[cnt].dwObjectSerial;
		}

		cnt = 0;
		for ( cnt2=0;cnt2<PARTY_PLAYER_MAX;cnt2++ ) {
			if ( lpPartyPlayers[cnt2] ) {
				dwPartyCode2 += lpPartyPlayers[cnt2]->dwObjectSerial;
				cnt++;
			}
		}

		if ( cnt==lpTransPartyPlayInfo->PartyUserCount && dwPartyCode1==dwPartyCode2 ) {
			//ÆÄÆ¼Á¤º¸°¡ º¯ÇÑ°Ô ¾øÀ½
			return TRUE;

		}
	}

	//////////// Á¤º¸ ¾÷µ¥ÀÌÆ® ///////////////
	//ÆÄÆ¼¿ø Á¤º¸ Á¦°Å
	if ( dwPartyInfo==PARTY_STATE_MASTER ) {
		for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
			if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock ) {
				lpPartyPlayers[cnt]->dwPartyInfo = PARTY_STATE_NONE;
				lpPartyPlayers[cnt]->lpPartyMaster = NULL;
			}
		}
	}

	ZeroMemory( lpPartyPlayers , sizeof(rsPLAYINFO *)*PARTY_PLAYER_MAX );

	for( cnt=0;cnt<lpTransPartyPlayInfo->PartyUserCount;cnt++ ) {
		if ( lpTransPartyPlayInfo->PlayInfo[cnt].dwObjectSerial==dwObjectSerial ) {
			dwPartyInfo = PARTY_STATE_MASTER;
			lpPartyMaster = this;
			lpPartyPlayers[cnt] = this;
			LevelAvg += smCharInfo.Level;
		}
		else {
			lpPlayInfo = srFindUserFromSerial( lpTransPartyPlayInfo->PlayInfo[cnt].dwObjectSerial );
			if ( lpPlayInfo ) {
				lpPartyPlayers[cnt] = lpPlayInfo;
				lpPlayInfo->dwPartyInfo = PARTY_STATE_MEMBER;
				lpPlayInfo->lpPartyMaster = this;
				LevelAvg += lpPlayInfo->smCharInfo.Level;
			}
		}
	}

	//ÆÄÆ¼¿ø ¼ö¿Í Æò±Õ·¹º§ ±â·Ï
	PartyUserCount = lpTransPartyPlayInfo->PartyUserCount;
	if ( PartyUserCount ) PartyLevelAverage = LevelAvg/PartyUserCount; 

	return TRUE;
}



//·¹º§ Â÷ÀÌº° °æÇèÄ¡ È¹µæ
int srGetTotalExp( int Exp , int Level );

// ¹ÚÀç¿ø - ÆÄÆ¼ °æÇèÄ¡ È¹µæ·® ¼öÁ¤
int	PartyExpTable[8][2] = {
	{	100	,	0 },	// 100% - 1¸í
	{	70	,	70 },	// 140%	- 2¸í
	{	60	,	60 },	// 180% - 3¸í
	{	55	,	55 },	// 220% - 4¸í
	{	52	,	52 },	// 260% - 5¸í
	{	50	,	50 },	// 300% - 6¸í
	{	22	,	21 },	// 
	{	20	,	20 }	//
};

//ÆÄÆ¼¿ø °æÇèÄ¡ È¹µæ
int rsPLAYINFO::GetPartyExp( smCHAR *lpChar , rsPLAYINFO *lpPlayInfo )
{
	smTRANS_COMMAND	smTransCommand;
	int	Exp;
	int	PartyExp[2];
	int	cnt;
	int x,z,dist;
	int Sucess = 0;
	int	ExpUp;

	if ( dwPartyInfo!=PARTY_STATE_MASTER || !lpsmSock ) return FALSE;

	//°æÇèÄ¡ È¹µæ
	smTransCommand.size = sizeof( smTRANS_COMMAND );
	smTransCommand.WParam = 0;										//È¹µæ °æÇèÄ¡
	smTransCommand.LParam = lpChar->dwObjectSerial;					//¸ó½ºÅÍ °íÀ¯¹øÈ£
	Exp = srGetTotalExp( lpChar->smMonsterInfo.GetExp , lpChar->smCharInfo.Level-PartyLevelAverage );

	PartyExp[0] = (Exp*PartyExpTable[PartyUserCount-1][0])/100;			//º»ÀÎ È¹µæ
	PartyExp[1] = (Exp*PartyExpTable[PartyUserCount-1][1])/100;			//ÆÄÆ¼¿ø È¹µæ


	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock ) {

			if ( lpPartyPlayers[cnt]==lpPlayInfo ) {
				smTransCommand.code = smTRANSCODE_ADDEXP;
				smTransCommand.WParam = PartyExp[0];										//º»ÀÎ È¹µæ
				Sucess++;
			}
			else {
				smTransCommand.code = smTRANSCODE_ADDEXP_PARTY;
				x = (lpPlayInfo->Position.x - lpPartyPlayers[cnt]->Position.x)>>FLOATNS;
				z = (lpPlayInfo->Position.z - lpPartyPlayers[cnt]->Position.z)>>FLOATNS;
				dist = x*x+z*z;
				if ( dist<PARTY_GETTING_DIST )
					smTransCommand.WParam = PartyExp[1];										//ÆÄÆ¼¿ø È¹µæ
				else
					smTransCommand.WParam = 0;
			}

			if ( smTransCommand.WParam ) {
				ExpUp = 0;

				if ( lpPartyPlayers[cnt]->dwTime_PrimeItem_ExpUp>(DWORD)tServerTime ) {
					switch( lpPartyPlayers[cnt]->dwPrimeItem_PackageCode ) 
					{
					case PRIME_ITEM_PACKAGE_NONE:
						ExpUp += 30;
						break;
					case PRIME_ITEM_PACKAGE_BRONZE:
						ExpUp += 10;
						break;
					case PRIME_ITEM_PACKAGE_SILVER:
						ExpUp += 20;
						break;
					case PRIME_ITEM_PACKAGE_GOLD:
						ExpUp += 30;
						break;
					case PRIME_ITEM_PACKAGE_ULTRA:		//º£Æ®³²¿äÃ»	50%
						ExpUp += 50;
						break;
					case PRIME_ITEM_PACKAGE_NONE_50_EXPUP: // ¹ÚÀç¿ø - °æÇèÄ¡Áõ°¡ Æ÷¼Ç(50%) ¾ÆÀÌÅÛ Àü¿ë
						ExpUp += 50; // ¹ÚÀç¿ø - °æÇèÄ¡ 50% ¾÷
						break; 
					case PRIME_ITEM_PACKAGE_NONE_100_EXPUP: // ¹ÚÀç¿ø - °æÇèÄ¡Áõ°¡ Æ÷¼Ç(100%) ¾ÆÀÌÅÛ Àü¿ë
						ExpUp += 100; // ¹ÚÀç¿ø - °æÇèÄ¡ 100% ¾÷
						break; 
					}
				}
				if ( lpPartyPlayers[cnt]->Bl_RNo>0 )
					ExpUp += 20;

				if( lpPartyPlayers[cnt]->dwTime_PrimeItem_PhenixPet > 0 )	// pluto Æê(ÇØ¿Ü) ¼öÁ¤
				{
					ExpUp += 20;
				}

				//½Ã°£º° °æÇèÄ¡ ºÐ¹è ( º£Æ®³² )
				if ( rsServerConfig.ExpGameTimeMode ) {
					smTransCommand.WParam = (smTransCommand.WParam*rsGetExp_GameTime( lpPartyPlayers[cnt] ))/100;
				}

				if ( ExpUp ) {
					//À¯·á ¾ÆÀÌÅÛ »ç¿ëÁß ¶Ç´Â PC¹æ ( °æÇèÄ¡ 30% + 20% Ãß°¡ )
					smTransCommand.WParam += (smTransCommand.WParam*ExpUp)/100;
				}

				lpPartyPlayers[cnt]->spEXP_Out += smTransCommand.WParam;		//³ª°£ °æÇèÄ¡ ±â·Ï
				smTransCommand.SParam = (smTransCommand.WParam*3 + smTransCommand.LParam*13)*2002;	//Á¶ÀÛ ¹æÁö ÇÁ·ÎÅØÅÍ ÄÚµå
				smTransCommand.EParam = smTransCommand.SParam^lpPartyPlayers[cnt]->spEXP_Out;

				lpPartyPlayers[cnt]->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
			}
		}
	}

	if ( !Sucess )	return FALSE;

	return TRUE;
}

//ÆÄÆ¼¿ø µ· È¹µæ
int rsPLAYINFO::GetPartyMoney( sITEMINFO *lpDefItemInfo , rsPLAYINFO *lpPlayInfo )
{
	TRANS_ITEMINFO	TransItemInfo;
	int	PartyMoney[2];
	int	cnt;
	int x,z,dist;
	int Sucess = 0;

	if ( dwPartyInfo!=PARTY_STATE_MASTER || !lpsmSock ) return FALSE;

	PartyMoney[1] = lpDefItemInfo->Money/PartyUserCount;					//ÆÄÆ¼¿ø È¹µæ
	PartyMoney[0] = PartyMoney[1]+(lpDefItemInfo->Money%PartyUserCount);	//º»ÀÎ È¹µæ


	TransItemInfo.code = smTRANSCODE_PUTITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	memcpy( &TransItemInfo.Item , lpDefItemInfo , sizeof( sITEMINFO ) );
	//lpsmSock->Send( (char *)&TransItemInfo , TransItemInfo.size , TRUE );


	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock ) {

			if ( lpPartyPlayers[cnt]==lpPlayInfo ) {
				wsprintf( TransItemInfo.Item.ItemName , sinGold , PartyMoney[0] );
				TransItemInfo.Item.Money = PartyMoney[0];
				ReformItem( &TransItemInfo.Item );						//¾ÆÀÌÅÛ ÀÎÁõ
				Sucess++;
			}
			else {
				x = (lpPlayInfo->Position.x - lpPartyPlayers[cnt]->Position.x)>>FLOATNS;
				z = (lpPlayInfo->Position.z - lpPartyPlayers[cnt]->Position.z)>>FLOATNS;
				dist = x*x+z*z;
				if ( dist<PARTY_GETTING_DIST ) {			//ÆÄÆ¼ °øÀ¯ Á¦ÇÑ °Å¸®
					wsprintf( TransItemInfo.Item.ItemName , sinGold , PartyMoney[1] );
					TransItemInfo.Item.Money = PartyMoney[1];
					ReformItem( &TransItemInfo.Item );						//¾ÆÀÌÅÛ ÀÎÁõ
				}
				else {
					TransItemInfo.Item.Money = 0;
				}
			}

			if ( TransItemInfo.Item.Money ) {
				lpPartyPlayers[cnt]->spMoney_Out += TransItemInfo.Item.Money;

				TransItemInfo.x = dwPlayServTime;											//ÇØµ¶ Å°
				TransItemInfo.y = TransItemInfo.Item.ItemHeader.dwChkSum;					//ÇØµ¶ Å°2
				TransItemInfo.z = lpPartyPlayers[cnt]->spMoney_Out^(TransItemInfo.x+TransItemInfo.y);	//ÅäÅ» ±â·Ï Àü¼Û

				rsRegist_ItemSecCode( lpPartyPlayers[cnt] , &TransItemInfo , 0 );	//¾ÆÀÌÅÛ Á¤º¸¼Û¼ö½Å ±¸Á¶Ã¼¿¡ º¸¾ÈÄÚµå »ðÀÔ ( ÄÄÆÄÀÏ½Ã ¼­¹ö¿¡¼­¸¸ Á¸Àç )

				lpPartyPlayers[cnt]->lpsmSock->Send2( (char *)&TransItemInfo , TransItemInfo.size , TRUE );
			}

		}
	}
	if ( !Sucess )	return FALSE;

	return TRUE;
}

//ÆÄÆ¼¿ø Ã¤ÆÃ¸Þ¼¼Áö º¸³¿
int rsPLAYINFO::PartyChatting( rsPLAYINFO *lpPlayInfo )
{
	int sLen,cnt;
	TRANS_CHATMESSAGE	TransChatMessage;
	

	sLen = lstrlen(lpPlayInfo->szChatMessage)+1;
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32+lstrlen(lpPlayInfo->szChatMessage);
	TransChatMessage.dwIP = 4;			//ÆÄ¶û±Û¾¾ (±Ó¸»°ú °°´Ù )
	TransChatMessage.dwObjectSerial = lpPlayInfo->dwObjectSerial;
	memcpy( TransChatMessage.szMessage , lpPlayInfo->szChatMessage , sLen );

	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] && lpPartyPlayers[cnt]->lpsmSock && lpPartyPlayers[cnt]!=lpPlayInfo) {

			lpPartyPlayers[cnt]->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
		}
	}


	return TRUE;
}


//ÆÄÆ¼Àå ÀÌÀÓ
int	rsPLAYINFO::LeavePartyMaster( rsPLAYINFO *lpPlayInfo )
{
	int cnt;
	char szBuff[128];

	if ( dwPartyInfo!=PARTY_STATE_MASTER ) return FALSE;
	if ( lpPlayInfo==this ) return FALSE;

	dwPartyInfo = PARTY_STATE_MEMBER;

	if ( !lpPlayInfo ) {
		//ÀÚµ¿ ÀÌÀÓ 
		for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
			if ( lpPartyPlayers[cnt] && lpPartyMaster!=lpPartyPlayers[cnt] ) {
				lpPlayInfo = lpPartyPlayers[cnt];
				break;
			}
		}
	}

	if ( !lpPlayInfo ) return FALSE;
	if ( !lpPlayInfo->lpsmSock ) return FALSE;

	//ÆÄÆ¼¿ø Á¤º¸
	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] ) {

			lpPartyPlayers[cnt]->lpPartyMaster = lpPlayInfo;		//ÆÄÆ¼Àå Æ÷ÀÎÅÍ º¯°æ
			lpPartyPlayers[cnt]->PartyMasterObjectCode = lpPlayInfo->dwObjectSerial;
			if ( lpPartyPlayers[cnt]==lpPlayInfo ) {
				lpPartyPlayers[cnt]->dwPartyInfo = PARTY_STATE_MASTER;
			}
		}
	}

	memcpy( lpPlayInfo->lpPartyPlayers , lpPartyPlayers , sizeof( rsPLAYINFO *) *PARTY_PLAYER_MAX );
	memcpy( lpPlayInfo->dwPartyObjectCode , dwPartyObjectCode , sizeof( DWORD ) *PARTY_PLAYER_MAX );

	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		lpPartyPlayers[cnt]=0;
		dwPartyObjectCode[0] = 0;
	}

	lpPlayInfo->UpdatePartyPlayer();


	//wsprintf( szBuff , "µ¿·áÀåÀÌ %s´ÔÀ¸·Î º¯°æµÇ¾ú½À´Ï´Ù" , lpPlayInfo->smCharInfo.szName );
	wsprintf( szBuff , srPartyMsg1 , lpPlayInfo->smCharInfo.szName );
	lpPlayInfo->SendPartyMessage( szBuff , 2 );

	return TRUE;
}

//ÆÄÆ¼ ÇØ»ê
int	rsPLAYINFO::ReleaseParty()
{
	int cnt;
	smTRANS_COMMAND		TransCommand;

	if ( lpPartyMaster!=this ) return FALSE;

	//SendPartyMessage( "µ¿·á°¡ ÇØ»êµÇ¾ú½À´Ï´Ù" , 2 );
	SendPartyMessage( srPartyMsg2 , 2 );

	dwPartyInfo = PARTY_STATE_NONE;

	TransCommand.code = smTRANSCODE_PARTY_RELEASE;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = dwObjectSerial;
	TransCommand.LParam = 0;
	TransCommand.SParam = 0;

	//ÆÄÆ¼¿ø Á¤º¸
	for(cnt=0;cnt<PARTY_PLAYER_MAX;cnt++) {
		if ( lpPartyPlayers[cnt] ) {

			lpPartyPlayers[cnt]->dwPartyInfo = PARTY_STATE_NONE;
			lpPartyPlayers[cnt]->lpPartyMaster = NULL;

			if ( lpPartyPlayers[cnt]->lpsmSock )
				lpPartyPlayers[cnt]->lpsmSock->Send( (char *)&TransCommand , TransCommand.size , TRUE );

			lpPartyPlayers[cnt] = 0;
		}
	}


	return TRUE;
}


//ÆÄÆ¼ °¡ÀÔ
int	rsPLAYINFO::JoinParty( rsPLAYINFO *lpPlayMaster )
{
	char	szBuff[128];

	if ( dwPartyInfo ) return FALSE;

	if ( lpPlayMaster && lpPlayMaster->lpsmSock && lpPlayMaster->dwPartyInfo==PARTY_STATE_MASTER ) {

		//ÆÄÆ¼¿¡ °¡ÀÔ
		if ( lpPlayMaster->JoinPartyPlayer( this )==TRUE ) {
			//¼º°ø
			//wsprintf( szBuff , "%s´ÔÀÌ µ¿·á¿¡ °¡ÀÔ Çß½À´Ï´Ù" , smCharInfo.szName );
			wsprintf( szBuff , srPartyMsg3 , smCharInfo.szName );
			SendPartyMessage( szBuff , 2 );
		}
		else {
			//½ÇÆÐ
			//wsprintf( szBuff , "µ¿·á¿¡ °¡ÀÔ ÇÒ¼ö ¾ø½À´Ï´Ù" );
			wsprintf( szBuff , srPartyMsg4 );
			SendPartyMessage( szBuff , 2 );
		}
	}

	return TRUE;
}


//ÆÄÆ¼ Å»Åð
int	rsPLAYINFO::SecedeParty()
{
	char	szBuff[128];

	rsPLAYINFO	*lpPlayInfo;


	if ( dwPartyInfo && lpPartyMaster && lpPartyMaster->lpsmSock && lpPartyMaster->dwPartyInfo==PARTY_STATE_MASTER ) {
		//ÆÄÆ¼¿¡¼­ Å»Åð

		if ( this==lpPartyMaster ) {
			LeavePartyMaster(0);		//ÆÄÆ¼Àå ÀÌÀÓ
		}

		lpPlayInfo = lpPartyMaster;

		if ( lpPlayInfo->PartyUserCount<=2 ) {
			//wsprintf( szBuff , "%s´Ô µ¿·á¿¡¼­ Å»ÅðÇß½À´Ï´Ù" , smCharInfo.szName );
			wsprintf( szBuff , srPartyMsg5 , smCharInfo.szName );
			lpPlayInfo->SendPartyMessage( szBuff , 2 );

			//ÆÄÆ¼¿ø ¾øÀ½ ÆÄÆ¼ ÇØ»ê
			lpPlayInfo->ReleaseParty();
			return TRUE;
		}

		if ( lpPlayInfo->DeletePartyPlayer( this ) ) {
			//wsprintf( szBuff , "%s´Ô µ¿·á¿¡¼­ Å»ÅðÇß½À´Ï´Ù" , smCharInfo.szName );
			wsprintf( szBuff , srPartyMsg5 , smCharInfo.szName );
			lpPlayInfo->SendPartyMessage( szBuff , 2 );

			return TRUE;
		}
	}


	return FALSE;
}

rsPLAYINFO *LastDisPlayer;
rsPLAYINFO *LastDisPartyMaster;
DWORD		LastDisPartyInfo;

//ÆÄÆ¼¿ø ¿¬°á ²ö¾îÁü
int	rsPLAYINFO::DisconnectPartyUser()
{
	char szBuff[128];
	rsPLAYINFO *pMaster;

	if ( !lpPartyMaster || !dwPartyInfo ) return NULL;

	LastDisPlayer = this;
	LastDisPartyMaster = lpPartyMaster;
	LastDisPartyInfo = dwPartyInfo;



	pMaster = lpPartyMaster;

	if ( this==lpPartyMaster ) {
		LeavePartyMaster(0);		//ÆÄÆ¼Àå ÀÌÀÓ
	}


	//wsprintf( szBuff , "%s´Ô µ¿·á¿¡¼­ Å»ÅðÇß½À´Ï´Ù" , smCharInfo.szName );
	wsprintf( szBuff , srPartyMsg5 , smCharInfo.szName );
	lpPartyMaster->SendPartyMessage( szBuff , 2 );

	if ( lpPartyMaster->PartyUserCount<=2 ) {
		lpPartyMaster->ReleaseParty();		//ÆÄÆ¼¿ø ¾øÀ½ ÆÄÆ¼ ÇØ»ê
		return TRUE;
	}

	//ÆÄÆ¼¿¡¼­ Å»Åð
	lpPartyMaster->DeletePartyPlayer( this );


	lpPartyMaster = pMaster;

	return TRUE;
}


//////////////////////// ¼­¹ö ¸Ó´Ï °ü¸® ///////////////////////
/*
	int	AddServerMoney( int Money , int WhereParam=0 );		//¼­¹ö ¸Ó´Ï Ãß°¡
	int	SubServerMoney( int Money , int WhereParam=0 );		//¼­¹ö ¸Ó´Ï °¨¼Ò
	int	SetServerMoney( int Money , int WhereParam=0 );		//¼­¹ö ¸Ó´Ï ¼³Á¤
*/

/*
#define	WHERE_TRADE				300
#define	WHERE_GIFT_EXPRESS		600
#define	WHERE_AGINGITEM			400
#define	WHERE_CRAFTITEM			420
#define	WHERE_FORECORB			440
#define	WHERE_BUY_ITEM			200
#define	WHERE_BUY_POTION		210
#define	WHERE_SELL_ITEM			220
#define	WHERE_LOAD_PLAYER		100
#define	WHERE_THROW_ITEM		120
#define	WHERE_GET_ITEM			130
#define	WHERE_STAR_POINT		620
#define	WHERE_CLAN_MONEY		630
#define	WHERE_GIVE_MONEY		640
#define	WHERE_PERSONAL_SHOP		320
#define	WHERE_OPEN_WAREHOUES	500
*/

char *GetWhereParamString( int WareParam )
{
	char *lpString;

	lpString = "Unknow";

#ifdef _W_SERVER

	switch(WareParam) {

	case	WHERE_TRADE:
			lpString = "Trade";	break;
	case	WHERE_GIFT_EXPRESS:
			lpString = "GiftExpress";	break;
	case	WHERE_AGINGITEM:	
			lpString = "AgingItem";	break;
	case	WHERE_CRAFTITEM:	
			lpString = "CraftItem";	break;
	case	WHERE_FORECORB:	
			lpString = "ForceOrb";	break;
	case	WHERE_BUY_ITEM:		
			lpString = "BuyItem";	break;
	case	WHERE_BUY_POTION:
			lpString = "BuyPotion";	break;
	case	WHERE_SELL_ITEM:
			lpString = "SellItem";	break;
	case	WHERE_LOAD_PLAYER:
			lpString = "LoadPlayer";	break;
	case	WHERE_THROW_ITEM:
			lpString = "ThrowItem";	break;
	case	WHERE_GET_ITEM:
			lpString = "GetItem";	break;
	case	WHERE_STAR_POINT:
			lpString = "StarPoint";	break;
	case	WHERE_CLAN_MONEY:
			lpString = "ClanMoney";	break;
	case	WHERE_GIVE_MONEY:
			lpString = "GiveMoney";	break;
	case	WHERE_PERSONAL_SHOP:
			lpString = "PersonalShop";	break;
	case	WHERE_OPEN_WAREHOUES:
			lpString = "WareHouse";	break;
	}
#endif

	return lpString;
}


#define	CHK_SERVER_MONEY_MAX	100000000
#define	CHK_SERVER_MONEY_MAX2	150000000
#define	CHK_SERVER_MONEY_MIN	-150000000

int	rsPLAYINFO::AddServerMoney( int Money , int WhereParam )	//¼­¹ö ¸Ó´Ï Ãß°¡
{
	int money = ServerMoney;

	ServerMoney += Money;

	if ( (money>=0 && ServerMoney<0) || Money<0 || Money>CHK_SERVER_MONEY_MAX ) {
		//µ· ¿À¹ö ÇÃ·Î¿ì ( ·Î±× ³²±â±â )

		smTRANS_COMMAND_EX	smTransCommandEx;

		char szStrBuff[128];
		wsprintf( szStrBuff , "*ADD_MONEY [%s]*" , GetWhereParamString(WhereParam) );

		smTransCommandEx.WParam = 8840;
		smTransCommandEx.WxParam = WhereParam;
		smTransCommandEx.LxParam = (int)szStrBuff;
		smTransCommandEx.LParam = money;
		smTransCommandEx.SParam = Money;
		smTransCommandEx.EParam = ServerMoney;
		RecordHackLogFile( this , &smTransCommandEx );

		if ( ServerMoney<CHK_SERVER_MONEY_MIN )
			ServerMoney = CHK_SERVER_MONEY_MIN;

		return FALSE;
	}

	return TRUE;
}

int	rsPLAYINFO::SubServerMoney( int Money , int WhereParam )	//¼­¹ö ¸Ó´Ï °¨¼Ò
{
	int money = ServerMoney;

	ServerMoney -= Money;

	if ( (money>=0 && ServerMoney<0) || Money<0 || Money>CHK_SERVER_MONEY_MAX ) {
		//µ· ¿À¹ö ÇÃ·Î¿ì ( ·Î±× ³²±â±â )

		smTRANS_COMMAND_EX	smTransCommandEx;

		char szStrBuff[128];
		wsprintf( szStrBuff , "*SUB_MONEY [%s]*" , GetWhereParamString(WhereParam) );

		smTransCommandEx.WParam = 8840;
		smTransCommandEx.WxParam = WhereParam;
		smTransCommandEx.LxParam = (int)szStrBuff;
		smTransCommandEx.LParam = money;
		smTransCommandEx.SParam = Money;
		smTransCommandEx.EParam = ServerMoney;
		RecordHackLogFile( this , &smTransCommandEx );

		if ( ServerMoney<CHK_SERVER_MONEY_MIN )
			ServerMoney = CHK_SERVER_MONEY_MIN;


		return FALSE;
	}

	return TRUE;
}

int	rsPLAYINFO::SetServerMoney( int Money , int WhereParam )	//¼­¹ö ¸Ó´Ï ¼³Á¤
{
	ServerMoney = Money;

	if ( Money>CHK_SERVER_MONEY_MAX || Money<0 ) {
		//µ· ¿À¹ö ÇÃ·Î¿ì ( ·Î±× ³²±â±â )

		smTRANS_COMMAND_EX	smTransCommandEx;

		char szStrBuff[128];
		wsprintf( szStrBuff , "*SET_MONEY [%s]*" , GetWhereParamString(WhereParam) );

		smTransCommandEx.WParam = 8840;
		smTransCommandEx.WxParam = WhereParam;
		smTransCommandEx.LxParam = (int)szStrBuff;
		smTransCommandEx.LParam = 0;
		smTransCommandEx.SParam = Money;
		smTransCommandEx.EParam = ServerMoney;
		RecordHackLogFile( this , &smTransCommandEx );

		if ( ServerMoney<CHK_SERVER_MONEY_MIN )
			ServerMoney = CHK_SERVER_MONEY_MIN;

		if ( ServerMoney>CHK_SERVER_MONEY_MAX2 )
			ServerMoney = 0;

		return FALSE;
	}

	return TRUE;
}


int	rsPLAYINFO::CallBack_ClanMarkNum( int ClanMarkNum )			//Å¬·£¸¶Å© ¹øÈ£ ¾Ë·ÁÁÜ
{
	DWORD dwCode;
	smTRANS_COMMAND	smTransCommand;

	if ( ClanMarkNum==-1 ) return TRUE;

	dwCode = GetClanCode( ClanMarkNum );
	if ( dwClanCode!=dwCode ) {

		smTransCommand.WParam = 8870;
		smTransCommand.LParam = dwClanCode;
		smTransCommand.SParam = dwCode;
		smTransCommand.EParam = rsBlessCastle.dwMasterClan;
		RecordHackLogFile( this , &smTransCommand );

		SucessCheck_ClanCode = -1;
		//Å¬·£ ¸¶Å© ÄÚµå°¡ Æ²¸®´Ù
		return FALSE;
	}

	dwClanCode = dwCode;
	SucessCheck_ClanCode = TRUE;

	return TRUE;
}
