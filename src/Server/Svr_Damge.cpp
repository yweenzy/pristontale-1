#include <windows.h>
#include <io.h>
#include <stdio.h>         /* for sprintf                           */
#include <string.h>        /* for strlen                            */
#include <memory.h>
#include <process.h>       /* for _beginthread                      */

#include "common.h"

#include "..\\smwsock.h"
#include "..\\smlib3d\\smd3d.h"
#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "..\\field.h"
#include "..\\sinbaram\\sinlinkheader.h"
#include "..\\effectsnd.h"

#include "..\\record.h"
#include "..\\playsub.h"
#include "Language\\language.h"

#include "onserver.h"
#include "svr_Damage.h"
#include "..\\damage.h"
#ifdef _LANGUAGE_VEITNAM
#include "..\\veitnam\\v_event.h"
#endif

#define	PK_POWER_DIVIDE	5
#define	PK_SCORE_DIVIDE	10

//°ø¼ºÀü ÇÊµå ÁÂÇ¥ Á¤º¸ ( ³ªÁß¿¡ Çì´õÆÄÀÏ·Î ÀÌÀü¿¹Á¤ )
extern int CastleBattleZone_LineZ;


//±âº» °ø°Ý µ¥¹ÌÁö
WORD	rsDefaultDamage[10][2] = {
	{	7,	14	},
	{	17,	40	},
	{	25,	50	},
	{	45,	74	},
	{	50,	80	},
	{	55,	86	},
	{	60,	90	},
	{	65,	100	},
	{	70,	110	},
	{	70,	110	}
};

int	dm_Critical_Temp;			//Å©¸®Æ¼ÄÃ °ª ÀÓ½Ã º¸°ü
int dm_SkillCode_Temp;			//½ºÅ³ÄÚµå ÀÓ½Ãº¸°ü
//½ÇÁ¦ Å©¸®Æ¼ÄÃ 
int GetCritical( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , int Critical_Hit );
int GetCritical2( rsPLAYINFO *lpPlayInfo , rsPLAYINFO *lpPlayInfo2 , int Critical_Hit );

//Ä³¸¯ÅÍ µ¥¹ÌÁö ±â·Ï
int	rsRecordCharDamage( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , int Damage );
//Ä³¸¯ÅÍ PK ±â·Ï
int	rsRecord_PKDamage( rsPLAYINFO *lpPlayInfo , rsPLAYINFO *lpPlayInfo2 , int Damage );


//´Ù¸¥ À¯Àú °ø°Ý ÆÐÅ¶ º¸³»±â ( À¯Àú °ø°Ý )
int rsSendAttackUser( rsPLAYINFO *lpPlayInfo , rsPLAYINFO *lpPlayInfo2, int Power , int AttackState , short sParam1=0 , short sParam2=0 );

//ºô¸µ¾ÆÀÌÅÛ½ºÅ³Àû¿ë
int	rsBillingItemSkill( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , int HitMonsters , int Power , int SkillCode );


#define	DISP_DAMAGE

#ifdef DISP_DAMAGE
static char szDispDamage[128];
static char szDispDamage2[128];	//ÇØ¿Ü

//µ¥¹ÌÁö Á¤º¸ Ãâ·Â
int rsDisplayDamgeToClient( rsPLAYINFO *lpPlayInfo , char *szDmgMsg )
{
	TRANS_CHATMESSAGE	TransChatMessage;

	if ( lpPlayInfo->AdminMode<=2 ) return FALSE;

	lstrcpy( TransChatMessage.szMessage , szDmgMsg );
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;
	lpPlayInfo->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );

	return TRUE;
}
#endif


//°ø°Ý ¼ö½Å ¹ÞÀ½
int rsRecvAttackData_Old( rsPLAYINFO *lpPlayInfo , TRANS_ATTACKDATA *lpTransAttackData , smCHAR *lpTargetChar , int Type )
{
#ifdef	_W_SERVER

	DWORD	dwTime;
	TRANS_CHATMESSAGE	TransChatMessage;
	smCHAR	*lpChar;
	smTRANS_COMMAND		smTransCommand;
	int		x,y,z;
	int		cnt,len;
	int		ang,ang2;
	int		regs;
	smWINSOCK	*lpsmSock;
	rsPLAYINFO	*lpPlayInfo2;

	int	Dmg1,Dmg2,Dmg3,Dmg4;

	Dmg1=0;	Dmg2=0;	Dmg3=0; Dmg4=0;

	lpsmSock = lpPlayInfo->lpsmSock;
	dwTime = dwPlayServTime;

		//°ø°Ý µ¥ÀÌÅ¸ ±â·Ï
		lpPlayInfo->Recv_AttackCount++;
		lpPlayInfo->Recv_AttackDamage +=lpTransAttackData->Power;

		if ( lpPlayInfo->BadPlayer==TRUE ) return FALSE;
		if ( lpPlayInfo->HideMode && lpPlayInfo->AdminMode<4 ) return FALSE;

		if ( lpTargetChar ) lpChar = lpTargetChar;
		else lpChar = srFindCharFromSerial( lpTransAttackData->dwTarObjectSerial );

		if ( !lpChar || lpChar->smCharInfo.State!=smCHAR_STATE_NPC ) {
			lpPlayInfo->AttackCount++;
		}

		if ( (dwPlayServTime-lpPlayInfo->dwAttackTime)>5000 ) {
			//°ø°Ý Å¸ÀÌ¹Ö °è»ê
			lpPlayInfo->dwAttackTime = dwPlayServTime;
			if ( lpPlayInfo->AttackCount>=40 ) {
				//5ÃÊµ¿¾È 10È¸ ÀÌ»ó °ø°Ý µé¾î¿È

				smTransCommand.WParam = 1823;
				smTransCommand.SParam = lpPlayInfo->AttackCount;
				smTransCommand.LParam = lpPlayInfo->AttackCount;

				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
				rsSendDataServer( lpPlayInfo->lpsmSock , &smTransCommand );

				if ( lpPlayInfo->AttackCount>=80 )
					lpPlayInfo->BadPlayer = TRUE;
					//DisconnectUser( lpsmSock );			//30È¸ ÀÌ»ó µé¾î¿Â °æ¿ì ¿¬°á Á¾·á

				return FALSE;
			}
			lpPlayInfo->AttackCount = 0;
		}

		if ( !Type && lpTransAttackData->dwChkSum!=(DWORD)(lpTransAttackData->Power*2002+(lpTransAttackData->x*lpTransAttackData->y*lpTransAttackData->z))) {
			//Ã½Å©¼¶ È®ÀÎ ¿À·ù
			smTransCommand.WParam = 1820;
			smTransCommand.SParam = lpTransAttackData->Power;
			smTransCommand.LParam = lpTransAttackData->Power;
			//RecordHackLogFile( lpPlayInfo , &smTransCommand );

			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			rsSendDataServer( lpPlayInfo->lpsmSock , &smTransCommand );

			//DisconnectUser( lpsmSock );
			lpPlayInfo->BadPlayer = TRUE;
			return FALSE;
		}

		if ( lpTransAttackData->Power>=9000 ) {
			//°ø°Ý·Â Å©±â ÅÍ¹«´Ï ¾øÀ½
			smTransCommand.WParam = 1821;
			smTransCommand.SParam = lpTransAttackData->Power;
			smTransCommand.LParam = lpTransAttackData->Power;
			//RecordHackLogFile( lpPlayInfo , &smTransCommand );

			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			rsSendDataServer( lpPlayInfo->lpsmSock , &smTransCommand );

			//DisconnectUser( lpsmSock );
			lpPlayInfo->BadPlayer = TRUE;
			return FALSE;
		}


		if ( abs(( (long)(dwTime-lpPlayInfo->dwRecvTimePlayBuff) ))>7*1000 ) {			// pluto Çüº¯È¯
			//7ÃÊ ÀÌ»ó ¸ð¼Ç µ¥ÀÌÅ¸ ¼ö½ÅÀÌ ¾ø¾ú´ø °æ¿ì ( °ø°ÝÀÎÁ¤ÇÏÁö ¾ÊÀ½ )
			return FALSE;
		}

		//ÇÏµåÄÚ¾î ÀÌº¥Æ®¿ë ( ÀÌº¥Æ® ¸ó½ºÅÍ¸¦ ¶óÀÎ ¹Û¿¡¼­ °ø°ÝÇÏ¸é ¹«È¿ )
		if ( lpChar && lpChar->PartyFlag==rsHARDCORE_EVENT_FLAG ) {
			if ( lpPlayInfo->EventMode!=rsHARDCORE_EVENT_FLAG ) {
				return FALSE;
			}
			/*
			if ( lpPlayInfo->EventScore>100000 ) {
				lpTransAttackData->Power>>=1;			//10¸¸ ÀÌ»ó Á¡¼ö È¹µæÇÑ °æ¿ì °ø°Ý·ÂÀ» ¹ÝÀ¸·Î °¨¼Ò ( ³Ê¹« ÀßÇØ¼­ ÀÇ½É )
			}
			*/
		}

		if ( lpChar ) {
			lpChar->dwLastTransTime = dwPlayServTime;		//ÃÖ±Ù È°¼ºÈ­µÈ ½Ã°£

			x = (lpPlayInfo->Position.x-lpChar->pX)>>FLOATNS;
			y = (lpPlayInfo->Position.y-lpChar->pY)>>FLOATNS;
			z = (lpPlayInfo->Position.z-lpChar->pZ)>>FLOATNS;
			if ( abs(y)>100 || (x*x+z*z)>(800*800) ) return FALSE;		//°Å¸®°¡ ¸Õ°æ¿ì ½ÇÆÐ

			x = (lpPlayInfo->Position.x-lpTransAttackData->x)>>FLOATNS;
			y = (lpPlayInfo->Position.y-lpTransAttackData->y)>>FLOATNS;
			z = (lpPlayInfo->Position.z-lpTransAttackData->z)>>FLOATNS;
			//if ( (x*x+y*y+z*z)>(64*8)*(64*8) ) break;					

			if ( lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD && lpChar->MotionInfo->State!=CHRMOTION_STATE_WARP ) {
				
				Dmg1 = lpTransAttackData->Power;

				//ÀÏ´Ü ÀûÀÏ °æ¿ì¸¸..
				if ( lpChar->smCharInfo.State ) {

#ifndef	_LANGUAGE_KOREAN
							//Ä³¸¯ÅÍ¿Í ¸ó½ºÅÍ¿ÍÀÇ ·¹º§Â÷°¡ Å«°æ¿ì °­Á¦ º¸Á¤
							cnt = lpChar->smCharInfo.Level-lpPlayInfo->smCharInfo.Level;
							if ( cnt>20 ) {
								cnt += (rand()%(cnt-20));
								if ( cnt>25 ) {
									if ( lpPlayInfo->smCharInfo.Level<10 ) cnt=20;
									else cnt = lpPlayInfo->smCharInfo.Level * 2;

									if ( cnt<lpTransAttackData->Power ) {
										lpTransAttackData->Power = GetRandomPos( cnt/2 , cnt );
									}
									if ( (lpTransAttackData->AttackState&0xFFFF)>1 ) {
										lpTransAttackData->AttackState &=0xFFFF0000;
									}
								}
							}
#endif

							if ( lpPlayInfo->BadPlayer==2 || lpPlayInfo->BadPlayer==4 ) {
								//ÇØÅ· À¯Àú °ø°Ý·Â Á¶Á¤
								cnt = lpPlayInfo->smCharInfo.Level/10;
								if ( cnt<1 || cnt>8 ) cnt = 1;

								cnt = GetRandomPos( rsDefaultDamage[cnt][0] , rsDefaultDamage[cnt][1] );
								if ( cnt<lpTransAttackData->Power ) {
									lpTransAttackData->Power = cnt;
								}
							}

							//ÃÖ±Ù ¸ñÇ¥ ¸ó½ºÅÍ ±â·Ï
							lpPlayInfo->lpChrTarget = lpChar;
							lpPlayInfo->dwTarObjSerial = lpChar->dwObjectSerial;

							lpChar->PlayStunCount = 0;			//Áß¸³¸ðµå ÇØÁ¦

							//ÀÎÃ¾Æ® ¿öÆù ½ºÅ³ Àû¿ë
							if ( lpPlayInfo->dwSkill_EnchantWeapon_Time ) {
								if ( lpPlayInfo->dwSkill_EnchantWeapon_Time>dwPlayServTime ) {
									if ( ((lpTransAttackData->AttackState>>16)&0xF)==0 ) {
										len = lpPlayInfo->dwSkill_EnchantWeapon_Param&0xFF;		//Æ÷ÀÎÆ®
										switch(lpPlayInfo->dwSkill_EnchantWeapon_Param>>8) {
											case 0:		//¾óÀ½ ( ¹üÀ§°ø°ÝÀÌ µû·Î µé¾î¿À¹Ç·Î »ý·«)
												/*
												lpTransAttackData->Power += GetRandomPos(
													Enchant_Weapon_Damage_Ice[len-1][0] , Enchant_Weapon_Damage_Ice[len-1][1] );
													*/

												// Àåº° - ½ºÅ³ ¼öÁ¤
												lpTransAttackData->Power += GetRandomPos(
													Enchant_Weapon_Damage_Ice[len-1][0] , Enchant_Weapon_Damage_Ice[len-1][1] );
												lpTransAttackData->AttackState |= (sITEMINFO_ICE+1)<<16;
												lpTransAttackData->AttackState |= (Enchant_Weapon_Damage_Ice[len-1][1])<<(16+4);
													
											//	lpTransAttackData->AttackState |= (sITEMINFO_ICE+1)<<16;
											//	lpTransAttackData->AttackState |= (1)<<(16+4);
												break;
											case 1:		//¹ø°³
												lpTransAttackData->Power += GetRandomPos(
													Enchant_Weapon_Damage_Lightning[len-1][0] , Enchant_Weapon_Damage_Lightning[len-1][1] );
												lpTransAttackData->AttackState |= (sITEMINFO_LIGHTING+1)<<16;
												lpTransAttackData->AttackState |= (Enchant_Weapon_Damage_Lightning[len-1][1])<<(16+4);
												break;

											case 2:		//ºÒ
												lpTransAttackData->Power += GetRandomPos(
													Enchant_Weapon_Damage_Fire[len-1][0] , Enchant_Weapon_Damage_Fire[len-1][1] );
												lpTransAttackData->AttackState |= (sITEMINFO_FIRE+1)<<16;
												lpTransAttackData->AttackState |= (Enchant_Weapon_Damage_Fire[len-1][1])<<(16+4);
												break;
										}
									}
								}
								else {	//Á¾·á ( ½Ã°£ÃÊ°ú )
									lpPlayInfo->dwSkill_EnchantWeapon_Time = 0;
									lpPlayInfo->dwSkill_EnchantWeapon_Param = 0;
								}
							}

							//¼Ó¼º °ø°ÝÀÏ °æ¿ì
							regs = (lpTransAttackData->AttackState>>16)&0xF;
							if ( regs && regs<sITEMINFO_NONE ) {
								cnt = lpTransAttackData->AttackState>>(16+4);		//¼Ó¼º °ª ( »óÀ§ ºñÆ®¿¡ ÀüÃ¼ µ¥¹ÌÁöÁß ¼Ó¼º µ¥¹ÌÁö¸¸ ÀúÀåµÊ )
								if ( !cnt ) 
									cnt = lpTransAttackData->Power;

								//¼Ó¼º¿¡ µû¸¥ ÀúÇ×·Â Àû¿ë
								len = lpChar->smCharInfo.Resistance[regs-1];
								if ( len ) {					//¼Ó¼º ÀúÇ×·Â °è»ê
									if ( len>=100 ) len = 100;
									if ( len<=-100 ) len = -100;
									lpTransAttackData->Power -= ((cnt*len)/100);

									if ( lpTransAttackData->Power<0 ) lpTransAttackData->Power=0;
								}

								switch(regs-1) { //(lpTransAttackData->AttackState>>16)-1) {
									case sITEMINFO_ICE:
										if ( lpPlayInfo->dwSkill_EnchantWeapon_Time>dwPlayServTime && (lpPlayInfo->dwSkill_EnchantWeapon_Param>>8)==0 ) {
											//¾óÀ½ °ø°Ý ¼Óµµ ÀúÇÏ ( ÀÎÃ¼Æ® ÀÏ¶§ Àû¿ë )
											lpChar->PlaySlowCount = 16*3;									//¼Óµµ ´À·ÁÁü ( 3ÃÊ )
											lpChar->PlaySlowCount -= (lpChar->PlaySlowCount*len)/100;
											lpChar->PlaySlowSpeed = 230-10*(lpPlayInfo->dwSkill_EnchantWeapon_Param&0xFF);	//·¹º§¿¡ µû¸¥ ¼Óµµ
											lpChar->PlayDistortion = 0;			//µð½ºÅä¼Ç ÇØÁ¦
											break;
										}
										if ( lpPlayInfo->dwSkill_DancingSword_Time>dwPlayServTime && (lpPlayInfo->dwSkill_DancingSword_Param&0xFF)==0 ) {
											//´í½Ì¼Òµå ¾óÀ½ °ø°Ý
											lpChar->PlaySlowCount = 16*5;					//¼Óµµ ´À·ÁÁü ( 5ÃÊ¿¡¼­ »ó¼â )
											lpChar->PlaySlowCount -= (lpChar->PlaySlowCount*len)/100;
											lpChar->PlaySlowSpeed = 230-10*(lpPlayInfo->dwSkill_DancingSword_Param>>16);	//·¹º§¿¡ µû¸¥ ¼Óµµ
											lpChar->PlayDistortion = 0;			//µð½ºÅä¼Ç ÇØÁ¦
											break;
										}
										if ( dm_SkillCode_Temp==SKILL_PLAY_PET_ATTACK ) {
											//Æê ¾óÀ½°ø°Ý
											lpChar->PlaySlowCount = 16*10;					//¼Óµµ ´À·ÁÁü ( 10ÃÊ¿¡¼­ »ó¼â )
											lpChar->PlaySlowCount -= (lpChar->PlaySlowCount*len)/100;
											lpChar->PlaySlowSpeed = 180;
											lpChar->PlayDistortion = 0;			//µð½ºÅä¼Ç ÇØÁ¦
											break;
										}
										if ( lpPlayInfo->dwSkill_FrostJavelin_Time>dwPlayServTime ) {
											//ÇÁ·Î½ºÆ®Àçºí¸° ¾óÀ½°ø°Ý
											//¼Óµµ ´À·ÁÁü
											lpChar->PlaySlowCount = 16*Frost_Javelin_IceTime[lpPlayInfo->dwSkill_FrostJavelin_Param];
											lpChar->PlaySlowCount -= (lpChar->PlaySlowCount*len)/100;
											lpChar->PlaySlowSpeed = 240-(240*Frost_Javelin_SpeedSubPercent[lpPlayInfo->dwSkill_FrostJavelin_Param])/100;
											lpChar->PlayDistortion = 0;			//µð½ºÅä¼Ç ÇØÁ¦
											break;
										}
										break;

								}

							}

							cnt = ( lpTransAttackData->Power * lpChar->smCharInfo.Absorption )/100;
							cnt = lpTransAttackData->Power-cnt;

							Dmg2 = lpTransAttackData->Power;
							Dmg3 = cnt;
							Dmg4 = cnt;

							//ÀÚ±âº¸´Ù ·¹º§ÀÌ Å« ¸ó½ºÅÍ¸¦ ÇÑ¹æ¿¡ Á×ÀÌ´Â °æ¿ì
							if ( (lpChar->smCharInfo.Life[1]/4)<cnt &&
								lpChar->smCharInfo.Level>lpPlayInfo->smCharInfo.Level ) {

								cnt = GetRandomPos( lpChar->smCharInfo.Life[1]/8 , lpChar->smCharInfo.Life[1]/4 );
							}

							if ( cnt>0 ) {
								//¼± °ø°ÝÀÚ ±â·Ï½ÃÄÑ °æÇèÄ¡ ¿ì¼± È¹µæ
								if ( lpChar->smCharInfo.Life[0]==lpChar->smCharInfo.Life[1] ) {
									if ( !lpChar->lpExpAttackPlayInfo ) {
										//¼±°ø°Ý µî·Ï
										lpChar->lpExpAttackPlayInfo = lpPlayInfo;
										lpChar->ExpAttackLife = 0;
										lpChar->dwExpAttackTime = dwTime;
									}
								}
								if ( lpChar->lpExpAttackPlayInfo ) {
									if ( lpChar->lpExpAttackPlayInfo==lpPlayInfo ) {
										//¼±°ø°ÝÀÚ °ø°Ý ±â·Ï
										lpChar->ExpAttackLife += cnt;
										lpChar->dwExpAttackTime = dwTime;
									}
									else {
										if ( (dwTime-lpChar->dwExpAttackTime)>15000 ) {
											//15ÃÊ ÀÌ»ó °ø°Ý¾øÀ½/ ¼±°ø°ÝÀÚ Ãë¼Ò
											lpChar->lpExpAttackPlayInfo = 0;
										}
									}
								}

								/////////////////// ½ºÅ³ Ã³¸® /////////////////////
								//HOLY_VALOR ( °ø°Ý·Â % °¡Áß )
								if ( lpPlayInfo->dwSkill_HolyValor_Time ) {
									if ( lpPlayInfo->dwSkill_HolyValor_Time>dwPlayServTime ) {
										if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD ) 
											cnt += (cnt*lpPlayInfo->dwSkill_HolyValor_Param)/100;	//¾ðµ¥µå °ø°Ý·Â °¡Áß
									}
									else {	//Á¾·á ( ½Ã°£ÃÊ°ú )
										lpPlayInfo->dwSkill_HolyValor_Time = 0;
										lpPlayInfo->dwSkill_HolyValor_Param = 0;
									}
								}

								Dmg4 = cnt;

								///////////////////////////////////////////////////
								//¸íÁß ( °ø°Ý ¼º°ø )
								lpChar->smCharInfo.Life[0] -= cnt;

								if ( lpChar->lpAttackDamageList || lpChar->lpAttackDamageList_BlessCastle ) rsRecordCharDamage( lpPlayInfo , lpChar , cnt );	//¹ÞÀº°ø°Ý ±â¾ïÇÏ´Â ¸÷

								if ( lpChar->smCharInfo.Level>14 ) {
									//·¹º§ 14ÀÌ»ó 20%ÀÌ»ó Å¸°Ý½Ã¿¡ ¸Ø©
									cnt = (cnt*5)/lpChar->smCharInfo.Life[1];
								}
								else {
									//·¹º§ 10ÀÌÇÏ 10%ÀÌ»ó Å¸°Ý½Ã¿¡ ¸Ø©
									cnt = (cnt*10)/lpChar->smCharInfo.Life[1];
								}

								if ( lpChar->smCharInfo.Life[0]>0 && ( cnt>=1 || (lpTransAttackData->AttackState&0xFFFF)>1 ) && 
									(rand()%100)<lpChar->smMonsterInfo.DamageStunPers ) {
									//°ø°ÝÆÄ¿ö°¡ ¼¼°Å³ª Å©¸®Æ¼ÄÃ ÆÇÁ¤ÀÏ °æ¿ì
									//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ
									ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
									ang = (ang2+ANGLE_180) & ANGCLIP;
									lpChar->Angle.y = ang;
									lpChar->MoveAngle( 10 );
									lpChar->Angle.y = ang2;

									if ( lpChar->smCharInfo.Life[0] && 
										lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
										lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT && 
										lpChar->MotionInfo->State!=CHRMOTION_STATE_WARP &&
										lpChar->MotionInfo->State!=CHRMOTION_STATE_SKILL ) {

										lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
									}
								}
							}
							lpPlayInfo->dwLastAttackTime = dwTime;


/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 )
{
	//ÇØ¿Ü
	wsprintf( szDispDamage , ">%s Damaged ( %d %d %d %d )" , lpChar->smCharInfo.szName , Dmg1 , Dmg2, Dmg3, Dmg4 );
	rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );

#ifdef _LANGUAGE_VEITNAM
	//¸ó½ºÅÍÀÇ ÇöÀçHP Ãâ·Â	//ÇØ¿Ü
	wsprintf( szDispDamage2 , ">%s (hp:%d, Total:%d) )" , lpChar->smCharInfo.szName , lpChar->smCharInfo.Life[0], lpChar->smCharInfo.Life[1]);
	rsDisplayDamgeToClient( lpPlayInfo , szDispDamage2 );
#endif
}
#endif*/


				}
				else {
					//ÀÏ¹Ý NPC

					if ( abs( ( long )lpPlayInfo->dwLastAttackTime - ( long )dwTime )>1500 )
					{		//1.5ÃÊ ÀÌ»ó ´ë±âÈÄ ¿­±â
						lpPlayInfo->dwLastAttackTime = dwTime;

						if ( lpChar->smMonsterInfo.QuestCode && lpChar->smMonsterInfo.QuestCode==(lpTransAttackData->AttackState>>16) ) {
							//Äù½ºÆ® ÁøÇà NPC
							if ( rsProcessQuest( lpPlayInfo , lpChar , lpTransAttackData->AttackState>>16 , lpTransAttackData->AttackState&0xFFFF )==TRUE )
								return TRUE;
						}

						if ( lpChar->szChatMessage[0] && (!lpChar->smMonsterInfo.EventNPC || lpChar->smMonsterInfo.EventNPC==5) ) {
							//ÀÀ´ä ¸Þ¼¼Áö º¸³¿
							if ( lpChar->smMonsterInfo.NpcMsgCount>1 ) {
								//¸ÖÆ¼ ¸Þ¼¼Áö
								TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
								TransChatMessage.dwIP = 0;
								TransChatMessage.dwObjectSerial = lpChar->dwObjectSerial;
								lstrcpy( TransChatMessage.szMessage , 
									lpChar->smMonsterInfo.lpNpcMessage[ rand()%lpChar->smMonsterInfo.NpcMsgCount ]   );

								TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
								lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
							}
							else {
								//´ÜÀÏ ¸Þ¼¼Áö
								TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
								TransChatMessage.size = 32+lstrlen(lpChar->szChatMessage);
								TransChatMessage.dwIP = 0;
								TransChatMessage.dwObjectSerial = lpChar->dwObjectSerial;
								lstrcpy( TransChatMessage.szMessage , lpChar->szChatMessage );
								lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
							}
						}
						if ( lpChar->smMonsterInfo.SellAttackItemCount || 
							lpChar->smMonsterInfo.SellDefenceItemCount ||
							lpChar->smMonsterInfo.SellEtcItemCount ) {

							//»óÁ¡ ¾ÆÀÌÅÛ ¸ñ·Ï Å¬¶óÀÌ¾ðÆ®¿¡ Àü¼Û
							SendShopItemList( lpsmSock , lpChar );
						}

						if ( lpChar->smMonsterInfo.SkillMaster ) {
							//½ºÅ³ ¼ö·Ã NPC
							if ( lpPlayInfo->AdminMode ) {
								SendSkillMenu( lpsmSock , lpChar , 2 );
							}
							else
								SendSkillMenu( lpsmSock , lpChar , lpChar->smMonsterInfo.SkillChangeJob );

						}
						if ( lpChar->smMonsterInfo.WareHouseMaster ) {
							//¾ÆÀÌÅÛ º¸°ü NPC
							SendOpenWareHouse( lpsmSock );
						}

						if ( lpChar->smMonsterInfo.ItemMix ) {
							//¾ÆÀÌÅÛ Á¶ÇÕ NPC
							SendOpenMixItem( lpsmSock , lpChar->smMonsterInfo.ItemMix );
						}
	
						// pluto ¾ÆÀÌÅÛ Á¦·Ã NPC
						if( lpChar->smMonsterInfo.Smelting )
						{
							SendOpenSmelting( lpsmSock );
						}
						// pluto ¾ÆÀÌÅÛ Á¦ÀÛ NPC
						if( lpChar->smMonsterInfo.Manufacture )
						{
							SendOpenManufacture( lpsmSock );
						}
						if ( lpChar->smMonsterInfo.CollectMoney ) {
							//ºÒ¿ìÀÌ¿ôµ½±â ¸ð±Ý NPC
							SendOpenCollectMoney( lpsmSock );
						}
#ifdef _LANGUAGE_VEITNAM
						if ( lpChar->smMonsterInfo.WowEvent ) 
						{
							wsprintf( TransChatMessage.szMessage , "EventGirl: %s",szBadEventGirl_Captor);
							TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
							TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
							TransChatMessage.dwIP = 0;
							TransChatMessage.dwObjectSerial = 0;
							lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );

							lpChar->Close();
							return TRUE;
						}
#endif

						if ( lpChar->smMonsterInfo.EventGift ) {
							//¼±¹° ÃßÃ· ÀÌº¥Æ®
							SendOpenEventGift( lpsmSock );
						}
						if ( lpChar->smMonsterInfo.GiftExpress ) {
							//¼±¹° ¹è´Þ
							smTransCommand.size = sizeof( smTRANS_COMMAND );
							smTransCommand.code = smTRANSCODE_ITEM_EXPRESS;
							smTransCommand.WParam = 0;
							smTransCommand.LParam = 0;
							smTransCommand.SParam = 0;
							rsSendDataServer( lpsmSock , &smTransCommand );
							//SendOpenGiftExpress( lpPlayInfo , 0 );
						}

						if ( lpChar->smMonsterInfo.WingQuestNpc ) {
							smTransCommand.size = sizeof( smTRANS_COMMAND );
							smTransCommand.code = smTRANSCODE_WING_NPC;
							smTransCommand.WParam = lpChar->smMonsterInfo.WingQuestNpc;
							smTransCommand.LParam = 0;
							smTransCommand.SParam = 0;
							lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
						}

						if ( lpChar->smMonsterInfo.TelePortNpc ) {
							int temp = 0;							
							if( lpChar->smMonsterInfo.TelePortNpc == 3) // pluto ¹ÐÅÍ°¡ ´øÀüÀ¸·Î ¿öÇÁ¸Þ¼¼Áö ³ª¿Ã¶§ À®Äù½ºÆ® ¸Þ¼¼Áö Ãâ·Â ¾ÈÇÏ°Ô ÇÏ·Á°í ¶«»§¤»¤»¤»
							{
								temp = -1;
							}
								smTransCommand.size = sizeof( smTRANS_COMMAND );
								smTransCommand.code = smTRANSCODE_WING_NPC;
								smTransCommand.WParam = temp;
								smTransCommand.LParam = lpChar->smMonsterInfo.TelePortNpc;
								smTransCommand.SParam = 0;
								lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
						}


						if ( lpChar->smMonsterInfo.StarPointNpc && lpPlayInfo->smCharInfo.Level>=lpChar->smMonsterInfo.StarPointNpc ) {
							//·¹º§ 20¸¸ ¿­¸°´Ù , º° Æ÷ÀÎÆ® NPC
							smTransCommand.size = sizeof( smTRANS_COMMAND );
							smTransCommand.code = smTRANSCODE_OPEN_STARPOINT;
							smTransCommand.WParam = 0;
							smTransCommand.LParam = 0;
							smTransCommand.SParam = 0;
							lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
						}

						if ( lpChar->smMonsterInfo.GiveMoneyNpc ) {
							//µ· ±âºÎÇÔ
							smTransCommand.size = sizeof( smTRANS_COMMAND );
							smTransCommand.code = smTRANSCODE_OPEN_GIVEMONEY;
							smTransCommand.WParam = 0;
							smTransCommand.LParam = 0;
							smTransCommand.SParam = 0;
							lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
						}



						if ( lpChar->smMonsterInfo.EventNPC ) {
							if ( lpChar->smMonsterInfo.EventNPC==5 ) {
								//SOD È¸°è»ç
								smTransCommand.size = sizeof( smTRANS_COMMAND );
								smTransCommand.code = smTRANSCODE_OPEN_COLLECT;
								smTransCommand.WParam = 5;
								smTransCommand.LParam = 0;
								smTransCommand.SParam = 0;
								lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
							}
							else {
								//SOD ÀÔÀåµµ¿ì¹Ì
								SendOpenEvent( lpChar , lpPlayInfo , lpChar->smMonsterInfo.EventNPC );
							}

							if ( lpChar->MotionInfo->State<0x100 ) {
								lpChar->SetMotionFromCode(CHRMOTION_STATE_ATTACK);
							}
						}


						if ( lpChar->smMonsterInfo.ItemAging ) {
							//¾ÆÀÌÅÛ ¿¡ÀÌÂ¡ NPC
							SendOpenAgingItem( lpsmSock );
						}	

						if ( lpChar->smMonsterInfo.ClanNPC ) {
							//Å¬·£ NPC
							SendOpenClanMenu( lpsmSock );
						}

						if ( lpChar->smMonsterInfo.BlessCastleNPC ) {
							//ºí·¡½ºÄ³½½ ¼³Á¤Á¤º¸ ¼Û½Å
							rsSendBlessCastInfo( lpPlayInfo , lpChar->smMonsterInfo.BlessCastleNPC );
						}

						if ( lpChar->smMonsterInfo.PollingNpc ) {
							//¼³¹®Á¶»ç NPC
							smTransCommand.size = sizeof( smTRANS_COMMAND );
							smTransCommand.code = smTRANSCODE_PUBLIC_POLLING;
							smTransCommand.WParam = lpChar->smMonsterInfo.PollingNpc;
							smTransCommand.LParam = 0;
							smTransCommand.SParam = 0;
							smTransCommand.EParam = 0;
							rsSendDataServer( lpsmSock , &smTransCommand );
						}
						

						if ( lpChar->smMonsterInfo.szMediaPlayNPC_Title && lpChar->smMonsterInfo.szMediaPlayNPC_Path ) {
							//µ¿¿µ»ó Àç»ý NPC

							lstrcpy( TransChatMessage.szMessage , lpChar->smMonsterInfo.szMediaPlayNPC_Path );
							len = lstrlen(TransChatMessage.szMessage);
							lstrcpy( TransChatMessage.szMessage+len+1 , lpChar->smMonsterInfo.szMediaPlayNPC_Title );

							TransChatMessage.code = smTRANSCODE_MEDIA_NPC;
							TransChatMessage.size = 34+len+lstrlen(lpChar->smMonsterInfo.szMediaPlayNPC_Title);
							TransChatMessage.dwIP = 0;
							TransChatMessage.dwObjectSerial = lpChar->dwObjectSerial;
							lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
						}

						// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â ( ¹Í½ºÃÄ ¸®¼Â npc¸¦ ¼±ÅÃÇÏ¸é Ã¢À» ¶ç¿ì¶ó´Â ¸Þ½ÃÁö¸¦ º¸³»´Â ÇÔ¼ö È£Ãâ )
						if( lpChar->smMonsterInfo.MixtureReset )
						{
							SendOpenMixtureItemReset( lpsmSock );
						}

					}
				}

				if ( lpChar->smCharInfo.Life[0]<=0 ) {
					lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );

					lpChar->lpExt2 = (void *)lpPlayInfo;


				}
			}
		}
		else {
			//ÇöÀç PK ºÒ°¡ ¸ðµå·Î ¼³Á¤
			//Ä³¸¯ÅÍ¸¦ Ã£´Â´Ù ( ³ªÁß¿¡ »¡¸® ¯À»¼ö ÀÖ°Ô ÄÚµåÈ­ ½ÃÄÑ ¹Ù²ã Áà¾ß ÇÔ )
			lpPlayInfo2 = srFindUserFromSerial( lpTransAttackData->dwTarObjectSerial );
			if ( lpPlayInfo2 ) {
				if ( rsServerConfig.Enable_PK || lpPlayInfo->smCharInfo.State!=lpPlayInfo2->smCharInfo.State ) {

					if ( lpPlayInfo->AdminMode || ( lpPlayInfo->smCharInfo.Level>LIMIT_PK_LEVEL && lpPlayInfo2->smCharInfo.Level>LIMIT_PK_LEVEL ) ) {
						//°¢°¢ ·¹º§ 10 ÀÌÇÏ´Â PK±ÝÁö
						//lpPlayInfo2->lpsmSock->Send( (char *)lpTransAttackData , lpTransAttackData->size , TRUE );

						//´Ù¸¥ À¯Àú °ø°Ý ÆÐÅ¶ º¸³»±â ( À¯Àú °ø°Ý )
						rsSendAttackUser( lpPlayInfo , lpPlayInfo2, lpTransAttackData->Power/PK_POWER_DIVIDE , 0x80 );
					}
				}
			}
		}
#endif		
		return TRUE;

}

//°ø°Ý ¹üÀ§Çü ¼ö½Å
int rsRecvRangeAttackData_Old( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData , int Type )
{

	smTRANS_COMMAND		smTransCommand;

	//¹üÀ§Çü ½ºÅ³ °ø°Ý
	//°ø°Ý µ¥ÀÌÅ¸ ±â·Ï
	lpPlayInfo->Recv_AttackCount++;
	lpPlayInfo->Recv_AttackDamage +=lpTransSkilAttackData->Power;

	if ( lpPlayInfo->HideMode && lpPlayInfo->AdminMode<4 ) return FALSE;

	RecvRangeAttack( lpPlayInfo , lpTransSkilAttackData );

	if ( lpTransSkilAttackData->Power>=1000 ) {
		smTransCommand.WParam = 1830;
		smTransCommand.SParam = lpTransSkilAttackData->Power;
		smTransCommand.LParam = smTransCommand.SParam;
		RecordHackLogFile( lpPlayInfo , &smTransCommand );

		DisconnectUser( lpPlayInfo->lpsmSock );
	}

	//¸ÞÄ«´Ï¼Ç ½ºÅ³½Ã ATTACKDATA¿Í µ¿½Ã¿¡ ¿Ã¶ó°¡´Â °æ¿ì°¡ ¶«¿¡ ¸·À½

	return TRUE;
}

//°ø°Ý ¹üÀ§Çü À¯Àú ¼ö½Å
int rsRecvRangeAttackUserData_Old( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData )
{

	smTRANS_COMMAND		smTransCommand;

	//¹üÀ§Çü ½ºÅ³ °ø°Ý ( À¯Àú °ø°Ý )
	//°ø°Ý µ¥ÀÌÅ¸ ±â·Ï
	lpPlayInfo->Recv_AttackCount++;
	lpPlayInfo->Recv_AttackDamage +=lpTransSkilAttackData->Power;

	if ( lpPlayInfo->HideMode && lpPlayInfo->AdminMode<4 ) return FALSE;

	RecvRangeAttackUser( lpPlayInfo , lpTransSkilAttackData );

	if ( lpTransSkilAttackData->Power>=1000 ) {
		smTransCommand.WParam = 1830;
		smTransCommand.SParam = lpTransSkilAttackData->Power;
		smTransCommand.LParam = smTransCommand.SParam;
		RecordHackLogFile( lpPlayInfo , &smTransCommand );

		DisconnectUser( lpPlayInfo->lpsmSock );
	}

	return TRUE;
}

//°Å¸® °Ë»ç ( ¸ó½ºÅÍ¿Í ¸ñÇ¥ÁöÁ¡ °Å¸® )
int	rsCheckAttackRange( int dx,int dy, int dz, smCHAR *lpChar , int dAttackSize )
{
	int x,y,z;

	x = (dx-lpChar->pX)>>FLOATNS;
	y = (dy-lpChar->pY)>>FLOATNS;
	z = (dz-lpChar->pZ)>>FLOATNS;

	if ( abs(y)>100 || (x*x+z*z)>dAttackSize )
		return FALSE;		//°Å¸®°¡ ¸Õ°æ¿ì ½ÇÆÐ

	return TRUE;
}

//°Å¸® °Ë»ç ( ÇÃ·¹ÀÌ¾î¿Í ¸ñÇ¥ÁöÁ¡ °Å¸® )
int	rsCheckAttackRange( int dx,int dy,int dz ,rsPLAYINFO *lpPlayInfo )
{
	int x,y,z;

	x = (dx-lpPlayInfo->Position.x)>>FLOATNS;
	y = (dy-lpPlayInfo->Position.y)>>FLOATNS;
	z = (dz-lpPlayInfo->Position.z)>>FLOATNS;

	if ( abs(y)>100 || (x*x+z*z)>(300*300) ) 
		return FALSE;		//°Å¸®°¡ ¸Õ°æ¿ì ½ÇÆÐ

	return TRUE;
}


//´Ù¸¥ À¯Àú °ø°Ý ÆÐÅ¶ º¸³»±â ( À¯Àú °ø°Ý )
int rsSendAttackUser( rsPLAYINFO *lpPlayInfo , rsPLAYINFO *lpPlayInfo2, int Power , int AttackState , short sParam1 , short sParam2 )
{

	TRANS_ATTACKDATA	TransAttackData;
	smTRANS_COMMAND		smTransCommand;
	int	temp;

	// pluto PKÇã¿ë ÇÊµå ÀüºÎ
	if ( !lpPlayInfo->AdminMode )
	{
		if( rsServerConfig.Enable_PKField_All )
		{
			// pluto PKÇã¿ë ÇÊµå ÀüºÎ ¼öÁ¤
			if ( !rsServerConfig.Enable_PK || lpPlayInfo->Position.Area < 11 && lpPlayInfo->Position.Area > 34 )
				return FALSE;			//ÇöÀç ÀÏ¹ÝÀ¯Àú´Â PK±ÝÁö

			if ( rsServerConfig.BlessCastleMode==2 && !lpPlayInfo->AdminMode ) return FALSE;
		}
		else
		{
			if ( !rsServerConfig.Enable_PK && 
				( sField[lpPlayInfo->Position.Area].State!=FIELD_STATE_CASTLE || lpPlayInfo->Position.z>CastleBattleZone_LineZ ) &&
				lpPlayInfo->Position.Area!=rsServerConfig.Enable_PKField )
				return FALSE;			//ÇöÀç ÀÏ¹ÝÀ¯Àú´Â PK±ÝÁö

			if ( rsServerConfig.BlessCastleMode==2 && !lpPlayInfo->AdminMode && lpPlayInfo->Position.Area!=rsServerConfig.Enable_PKField ) return FALSE;
		}
	}



	TransAttackData.code = smTRANSCODE_ATTACKDATA;
	TransAttackData.size = sizeof(TRANS_ATTACKDATA);

	TransAttackData.x = lpPlayInfo2->Position.x;
	TransAttackData.y = lpPlayInfo2->Position.y;
	TransAttackData.z = lpPlayInfo2->Position.z;


	TransAttackData.AttackState = AttackState;
	TransAttackData.AttackSize  = 32*fONE;
	TransAttackData.Power		= Power;

	//Á¾¼º ¾ÆÀÌÅÛ ½Ã°£Á¾·á È®ÀÎ
	if (  lpPlayInfo->dwSiegeItem_Scroll_Time && lpPlayInfo->dwSiegeItem_Scroll_Time<dwPlayServTime ) {
		lpPlayInfo->dwSiegeItem_Scroll_Code = 0;
		lpPlayInfo->dwSiegeItem_Scroll_Time = 0;
	}
	if (  lpPlayInfo->dwSiegeItem_Stone1_Time && lpPlayInfo->dwSiegeItem_Stone1_Time<dwPlayServTime ) {
		lpPlayInfo->dwSiegeItem_Stone1_Code = 0;
		lpPlayInfo->dwSiegeItem_Stone1_Time = 0;
	}
	if (  lpPlayInfo->dwSiegeItem_Stone2_Time && lpPlayInfo->dwSiegeItem_Stone2_Time<dwPlayServTime ) {
		lpPlayInfo->dwSiegeItem_Stone2_Code = 0;
		lpPlayInfo->dwSiegeItem_Stone2_Time = 0;
	}

	//Á¾¼º ¾ÆÀÌÅÛ ½Ã°£Á¾·á È®ÀÎ
	if (  lpPlayInfo2->dwSiegeItem_Scroll_Time && lpPlayInfo2->dwSiegeItem_Scroll_Time<dwPlayServTime ) {
		lpPlayInfo2->dwSiegeItem_Scroll_Code = 0;
		lpPlayInfo2->dwSiegeItem_Scroll_Time = 0;
	}
	if (  lpPlayInfo2->dwSiegeItem_Stone1_Time && lpPlayInfo2->dwSiegeItem_Stone1_Time<dwPlayServTime ) {
		lpPlayInfo2->dwSiegeItem_Stone1_Code = 0;
		lpPlayInfo2->dwSiegeItem_Stone1_Time = 0;
	}
	if (  lpPlayInfo->dwSiegeItem_Stone2_Time && lpPlayInfo->dwSiegeItem_Stone2_Time<dwPlayServTime ) {
		lpPlayInfo->dwSiegeItem_Stone2_Code = 0;
		lpPlayInfo->dwSiegeItem_Stone2_Time = 0;
	}

	if ( lpPlayInfo2->dwSiegeItem_Scroll_Code==(sinBC1|sin01) ) {	//¹«Àû½ºÅ©·Ñ
		if ( lpPlayInfo2->Position.Area==rsCASTLE_FIELD ) return FALSE;
	}
	if ( lpPlayInfo2->dwSiegeItem_Scroll_Code==(sinBI1|sin05) )		//¹«Àû½ºÅ©·Ñ
		return FALSE;

	if ( lpPlayInfo2->dwSiegeItem_Scroll_Code==(sinBC1|sin03) ) {	//Ãß°¡ È¸ÇÇ
		if ( lpPlayInfo2->Position.Area==rsCASTLE_FIELD ) {
			if ( (rand()%100)<(int)lpPlayInfo2->dwSiegeItem_Scroll_Param ) {
/*#ifdef DISP_DAMAGE
				if ( lpPlayInfo2->AdminMode>2 ) {
					wsprintf( szDispDamage , ">%s °ø°Ý Ãß°¡È¸ÇÇ ( Evade Scrorll[%d] )" , lpPlayInfo->smCharInfo.szName , lpPlayInfo2->dwSiegeItem_Scroll_Param );
					rsDisplayDamgeToClient( lpPlayInfo2 , szDispDamage );
				}
#endif*/
				//Ãß°¡È¸ÇÇ Á¤º¸ Å¬¶ó¸®¾ðÆ®¿¡ Ãâ·Â
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof( smTRANS_COMMAND );
				smTransCommand.WParam = 0;
				smTransCommand.LParam = lpPlayInfo2->dwSiegeItem_Scroll_Code;
				smTransCommand.SParam = lpPlayInfo->dwObjectSerial;
				smTransCommand.EParam = 0;
				lpPlayInfo2->lpsmSock->Send( (char *)&smTransCommand , smTransCommand.size , TRUE );
				return FALSE;
			}
		}
	}
	if ( lpPlayInfo2->dwSiegeItem_Scroll_Code==(sinBI1|sin07) ) {	//Ãß°¡ È¸ÇÇ
		if ( (rand()%100)<(int)lpPlayInfo2->dwSiegeItem_Scroll_Param ) {
/*#ifdef DISP_DAMAGE
			if ( lpPlayInfo2->AdminMode>2 ) {
				wsprintf( szDispDamage , ">%s °ø°Ý Ãß°¡È¸ÇÇ ( Evade Scrorll[%d] )" , lpPlayInfo->smCharInfo.szName , lpPlayInfo2->dwSiegeItem_Scroll_Param );
				rsDisplayDamgeToClient( lpPlayInfo2 , szDispDamage );
			}
#endif*/
			//Ãß°¡È¸ÇÇ Á¤º¸ Å¬¶ó¸®¾ðÆ®¿¡ Ãâ·Â
			smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
			smTransCommand.size = sizeof( smTRANS_COMMAND );
			smTransCommand.WParam = 0;
			smTransCommand.LParam = lpPlayInfo2->dwSiegeItem_Scroll_Code;
			smTransCommand.SParam = lpPlayInfo->dwObjectSerial;
			smTransCommand.EParam = 0;
			lpPlayInfo2->lpsmSock->Send( (char *)&smTransCommand , smTransCommand.size , TRUE );
			return FALSE;
		}
	}

	if ( lpPlayInfo->dwSiegeItem_Stone2_Code && lpPlayInfo2->smCharInfo.JOB_CODE==lpPlayInfo->dwSiegeItem_Stone2_Code ) {
		//Á÷¾÷º° °­È­ ½ºÅ©·Ñ
		TransAttackData.Power += (TransAttackData.Power*lpPlayInfo->dwSiegeItem_Stone2_Param)/100;

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s °ø°Ý·Â °­È­¼® ( Á÷¾÷:%d )( %d )" , lpPlayInfo2->smCharInfo.szName , lpPlayInfo->dwSiegeItem_Stone2_Code , TransAttackData.Power );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/
	}


	if ( lpPlayInfo2->dwSkill_PhysicalAbsorb_Time ) {	//°ø°Ý·Â °¨¼Ò (Èí¼ö·Â ¹Ì¸®Àû¿ë)- ÇÇÁöÄÃ »ç¿ë
		if ( lpPlayInfo2->dwSkill_PhysicalAbsorb_Time>dwPlayServTime ) {
			TransAttackData.Power -= lpPlayInfo2->dwSkill_PhysicalAbsorb_Param;
			if ( TransAttackData.Power<0 ) return FALSE;
		}
		else {
			lpPlayInfo2->dwSkill_PhysicalAbsorb_Time = 0;
			lpPlayInfo2->dwSkill_PhysicalAbsorb_Param = 0;
		}
	}
	if ( lpPlayInfo2->dwSkill_ExtreamShield_Time ) {	//ºí·°À²Áõ°¡ - ÀÍ½ºÆ®¸² ½¯µå
		if ( lpPlayInfo2->dwSkill_ExtreamShield_Time>dwPlayServTime ) {
			TransAttackData.AttackState |= (lpPlayInfo2->dwSkill_ExtreamShield_Param<<16);
		}
		else {
			lpPlayInfo2->dwSkill_ExtreamShield_Time = 0;
			lpPlayInfo2->dwSkill_ExtreamShield_Param = 0;
		}
	}

	/////////////////////////////////////////////////////////////////////


	if ( lpPlayInfo2->dwSkill_MetalArmor_Time ) {	//°ø°Ý·Â °¨¼Ò (Èí¼ö·Â ¹Ì¸®Àû¿ë)- ¸ÞÅ»¾Æ¸Ó »ç¿ë
		if ( lpPlayInfo2->dwSkill_MetalArmor_Time>dwPlayServTime ) {
			TransAttackData.Power -= lpPlayInfo2->dwSkill_MetalArmor_Param;
			if ( TransAttackData.Power<0 ) return FALSE;
		}
		else {
			lpPlayInfo2->dwSkill_MetalArmor_Time = 0;
			lpPlayInfo2->dwSkill_MetalArmor_Param = 0;
		}
	}


	if ( lpPlayInfo2->dwSkill_VirtualLife_Time ) {	//°¡»ó »ý¸í·ÂÀ» ³ô¿©¼­ °ø°Ý·Â °¨¼Ò
		if ( lpPlayInfo2->dwSkill_VirtualLife_Time>dwPlayServTime ) {
			TransAttackData.Power -= (TransAttackData.Power*lpPlayInfo2->dwSkill_VirtualLife_Param)/100;
			if ( TransAttackData.Power<0 ) return FALSE;
		}
		else {
			lpPlayInfo2->dwSkill_VirtualLife_Time = 0;
			lpPlayInfo2->dwSkill_VirtualLife_Param = 0;
		}
	}

	if ( lpPlayInfo2->dwSkill_EnergyShield_Time ) {	//¿¡³ÊÁö½¯µå °ø°Ý·Â °¨¼Ò
		if ( lpPlayInfo2->dwSkill_EnergyShield_Time>dwPlayServTime ) {
			temp = (TransAttackData.Power*lpPlayInfo2->dwSkill_EnergyShield_Param)/100;
			TransAttackData.Power -= temp;
			TransAttackData.AttackState |= (temp<<16);
			if ( TransAttackData.Power<0 ) return FALSE;
		}
		else {
			lpPlayInfo2->dwSkill_EnergyShield_Time = 0;
			lpPlayInfo2->dwSkill_EnergyShield_Param = 0;
		}
	}

	if ( lpPlayInfo2->dwSkill_Compulsion_Time ) {	//Compulsion Èí¼ö·Â Ãß°¡
		if ( lpPlayInfo2->dwSkill_Compulsion_Time>dwPlayServTime ) {
			TransAttackData.Power -= lpPlayInfo2->dwSkill_Compulsion_Param;
			if ( TransAttackData.Power<0 ) return FALSE;
		}
		else {
			lpPlayInfo2->dwSkill_Compulsion_Time = 0;
			lpPlayInfo2->dwSkill_Compulsion_Param = 0;
		}
	}

	if ( lpPlayInfo2->dwSkill_Berserker_Time ) {	//¹ö¼­Ä¿ Èí¼ö·Â °¨¼Ò
		if ( lpPlayInfo2->dwSkill_Berserker_Time>dwPlayServTime ) {
			TransAttackData.Power -= Berserker_SubAbsorb[lpPlayInfo2->dwSkill_Berserker_Param];
			if ( TransAttackData.Power<0 ) return FALSE;
		}
		else {
			lpPlayInfo2->dwSkill_Berserker_Time = 0;
			lpPlayInfo2->dwSkill_Berserker_Param = 0;
		}
	}
	

	//º£ÀÌ±× Ãß°¡È¸ÇÇ
	if ( lpPlayInfo2->dwSkill_Vague_Time ) {
		if ( lpPlayInfo2->dwSkill_Vague_Time>dwPlayServTime ) {
			if ( (rand()%100)<Vague_EvasionPercent[lpPlayInfo2->dwSkill_Vague_Param] ) {

/*#ifdef DISP_DAMAGE
				if ( lpPlayInfo2->AdminMode>2 ) {
					wsprintf( szDispDamage , ">%s °ø°Ý Ãß°¡È¸ÇÇ ( Vague[%d] )" , lpPlayInfo->smCharInfo.szName , Vague_EvasionPercent[lpPlayInfo2->dwSkill_Vague_Param] );
					rsDisplayDamgeToClient( lpPlayInfo2 , szDispDamage );
				}
#endif*/

				//Ãß°¡È¸ÇÇ Á¤º¸ Å¬¶ó¸®¾ðÆ®¿¡ Ãâ·Â
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof( smTRANS_COMMAND );
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_VAGUE;
				smTransCommand.SParam = lpPlayInfo->dwObjectSerial;
				smTransCommand.EParam = 0;
				lpPlayInfo2->lpsmSock->Send( (char *)&smTransCommand , smTransCommand.size , TRUE );

				return FALSE;		//Ãß°¡ È¸ÇÇ ÆÇÁ¤
			}
		}
		else {
			lpPlayInfo2->dwSkill_Vague_Time = 0;
			lpPlayInfo2->dwSkill_Vague_Param = 0;
		}
	}

	if ( lpPlayInfo2->dwSkill_GodlyShied_Time ) {	//°ø°Ý·Â °¨¼Ò (Èí¼ö·Â ¹Ì¸®Àû¿ë)- °¡µé¸®½¯µå»ç¿ë
		if ( lpPlayInfo2->dwSkill_GodlyShied_Time>dwPlayServTime ) {
			TransAttackData.Power -= (TransAttackData.Power*Godly_Shield_AbsorbPercent[lpPlayInfo2->dwSkill_GodlyShied_Param])/100;
			if ( TransAttackData.Power<0 ) return FALSE;
		}
		else {
			lpPlayInfo2->dwSkill_GodlyShied_Time = 0;
			lpPlayInfo2->dwSkill_GodlyShied_Param = 0;
		}
	}


	//È¦¿Àºê¹ßÇÒ¶ó Ãß°¡È¸ÇÇ
	if ( lpPlayInfo2->dwSkill_HallOfValhalla_Time ) {
		if ( lpPlayInfo2->dwSkill_HallOfValhalla_Time>dwPlayServTime ) {
			if ( (rand()%100)<(int)lpPlayInfo2->wSkill_HallOfValhalla_Param[0] ) {
/*#ifdef DISP_DAMAGE
				if ( lpPlayInfo2->AdminMode>2 ) {
					wsprintf( szDispDamage , ">%s °ø°Ý Ãß°¡È¸ÇÇ ( Hall of Valhalla [%d] )" , lpPlayInfo->smCharInfo.szName , lpPlayInfo2->wSkill_HallOfValhalla_Param[0] );
					rsDisplayDamgeToClient( lpPlayInfo2 , szDispDamage );
				}
#endif*/
				//Ãß°¡È¸ÇÇ Á¤º¸ Å¬¶ó¸®¾ðÆ®¿¡ Ãâ·Â
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof( smTRANS_COMMAND );
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_HALL_OF_VALHALLA;
				smTransCommand.SParam = lpPlayInfo->dwObjectSerial;
				smTransCommand.EParam = 0;
				lpPlayInfo2->lpsmSock->Send( (char *)&smTransCommand , smTransCommand.size , TRUE );

				return FALSE;		//Ãß°¡ È¸ÇÇ ÆÇÁ¤
			}
		}
		else {
			lpPlayInfo2->dwSkill_HallOfValhalla_Time = 0;
		}
	}

	if ( lpPlayInfo2->dwSkill_SummonMuspell_Time ) {	//¼­¸ó ¹«½ºÆç
		if ( lpPlayInfo2->dwSkill_SummonMuspell_Time>dwPlayServTime ) {

			if ( (rand()%100)<Summon_Muspell_BlockPercent[ lpPlayInfo2->dwSkill_SummonMuspell_Param ] ) {
#ifdef DISP_DAMAGE
				if ( lpPlayInfo2->AdminMode>2 ) {
					wsprintf( szDispDamage , ">%s °ø°Ý Ãß°¡ È¸ÇÇ ( Summon Muspell [%d] )" , lpPlayInfo->smCharInfo.szName , Summon_Muspell_BlockPercent[ lpPlayInfo2->dwSkill_SummonMuspell_Param ] );
					rsDisplayDamgeToClient( lpPlayInfo2 , szDispDamage );
				}
#endif
				//Ãß°¡È¸ÇÇ Á¤º¸ Å¬¶ó¸®¾ðÆ®¿¡ Ãâ·Â
				smTransCommand.code = smTRANSCODE_SUCCESS_EVATION;
				smTransCommand.size = sizeof( smTRANS_COMMAND );
				smTransCommand.WParam = 0;
				smTransCommand.LParam = SKILL_PLAY_SUMMON_MUSPELL;
				smTransCommand.SParam = lpPlayInfo->dwObjectSerial;
				smTransCommand.EParam = 0;
				lpPlayInfo2->lpsmSock->Send( (char *)&smTransCommand , smTransCommand.size , TRUE );

				return FALSE;
			}
		}
		else {
			lpPlayInfo2->dwSkill_SummonMuspell_Time = 0;
			lpPlayInfo2->dwSkill_SummonMuspell_Param = 0;
		}
	}


	//////////////////////////////////////////////////////////////////////////

	//TransAttackData.sRating[0] = lpPlayInfo->smCharInfo.Level;
	//TransAttackData.sRating[1] = lpPlayInfo->smCharInfo.Attack_Rating;

	TransAttackData.sRating[0] = sParam1;
	TransAttackData.sRating[1] = sParam2;

	TransAttackData.dwDestObjectSerial = lpPlayInfo->dwObjectSerial;
	TransAttackData.dwTarObjectSerial = lpPlayInfo2->dwObjectSerial;
	TransAttackData.dwChkSum = TransAttackData.Power*2002 + 
		(TransAttackData.x * TransAttackData.y * TransAttackData.z);// Á¶ÀÛ ¹æÁö ÄÚµå



	if ( lpPlayInfo2->lpsmSock ) {

		//°ø°Ý µ¥ÀÌÅ¸ ±â·Ï
		lpPlayInfo2->Send_AttackCount++;
		lpPlayInfo2->Send_AttackDamage+=TransAttackData.Power;


		//Ä³¸¯ÅÍ PK ±â·Ï
		rsRecord_PKDamage( lpPlayInfo , lpPlayInfo2 , TransAttackData.Power );

		if ( rsServerConfig.CrazyPacketMode && lpPlayInfo2->dwDecPacketCode && 
			lpPlayInfo2->dwDecPacketTime2<dwPlayServTime ) {					//Å©·¹ÀÌÁö ÆÐÅ¶ ¸ðµå

			//S2C °ø°Ý Ã½Å©¼¶ ( Å©·¹ÀÌÁö ÆÐÅ¶ )
			TransAttackData.code = smTRANSCODE_ATTACKDATA2;
			TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V( &TransAttackData );		//S2C °ø°Ý Ã½Å©¼¶

			if ( lpPlayInfo2 ) 
				rsEncodeDamagePacket( lpPlayInfo2 , &TransAttackData );
		}
		else
			TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V( &TransAttackData );		//S2C °ø°Ý Ã½Å©¼¶

		lpPlayInfo2->lpsmSock->Send2( (char *)&TransAttackData , TransAttackData.size , TRUE );
	}

	return TRUE;
}




int RecvRangeAttack_User( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData , int AreaNum , int PlaySkillCode )
{


	//smCHAR *lpChar;
	rsPLAYINFO	*lpCharInfo;
	int cnt,cnt2,pow;
	//int ang,ang2;
	//int x,y,z,dist;
	int	rs,time;
	//int life,TotalLife;
	int	StunFlag;
	//smTRANS_COMMAND	smTransCommand;
	int	dDist;
	int	SkillCode , SkillPoint;
	int	StnPers;
	int	Dmg1, Dmg2, Dmg3, Dmg4;
	int SlowSpeed;

	//TRANS_PARTY_SKILL		TransPartySkill;

	SkillCode = PlaySkillCode&0xFF;
	SkillPoint = PlaySkillCode>>8;
	if ( SkillPoint ) {
		SkillPoint --;
		if ( SkillPoint<0 || SkillPoint>=10 ) SkillPoint = 0;
	}


	STG_AREA *lpStgArea;

	if ( AreaNum<STAGE_AREA_MAX && StageArea[AreaNum].lpStage ) lpStgArea = &StageArea[AreaNum];
	else {
		return FALSE;
	}

	if ( lpPlayInfo->HideMode && lpPlayInfo->AdminMode<4 ) return FALSE;

	//°Å¸® °Ë»ç ( ÇÃ·¹ÀÌ¾î¿Í ¸ñÇ¥ÁöÁ¡ °Å¸® )
	if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y,lpTransSkilAttackData->z ,lpPlayInfo )==FALSE )
		return FALSE;

	dDist = lpTransSkilAttackData->AttackSize+60;
	dDist *= dDist;



	switch( lpTransSkilAttackData->AttackState ) {
	case 0:		//ÀÏ¹Ý ¹üÀ§Çü
	case 100:	//·¹ÀÌÁö ¿Àºê Á¦Å©¶÷ ( ºÒ °ø°Ý )
	case 101:	//½ºÆÄÅ© ( ³ú °ø°Ý )
	case 103:	//µð¹ÙÀÎ ¶óÀÌÆÃ ( ¾ðµ¥µå 50% °¡Áß )
	case 104:	//¾óÀ½ ( °ø°Ý )
	case 105:	//ÀÎÃ¾Æ® Àü±â
	case 106:	//µ¶ °ø°Ý

		for( cnt2=0;cnt2<CONNECTMAX;cnt2++ ) {

			lpCharInfo = &rsPlayInfo[cnt2];

			if ( lpCharInfo && lpCharInfo->lpsmSock && lpCharInfo->smCharInfo.State ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpCharInfo->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						//°Å¸®°Ë»ç
						//if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar , dDist )==FALSE ) break;

						pow = lpTransSkilAttackData->Power;
						StunFlag = TRUE;

						Dmg1 = pow;

						if ( lpTransSkilAttackData->AttackState==100 ) {
							//ºÒ °ø°Ý ( ºÒ ÀúÇ×·Â Àû¿ë )
							rs = lpCharInfo->smCharInfo.Resistance[sITEMINFO_FIRE];
							if ( SkillCode==SKILL_PLAY_METEO ) {
								rs/=2;		//¹ÌÆ¼¾î ºÒ¼Ó¼º 50% Àû¿ë
							}
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}
						if ( lpTransSkilAttackData->AttackState==101 ) {
							//³ú °ø°Ý ( Àü±â ÀúÇ×·Â Àû¿ë )
							rs = lpCharInfo->smCharInfo.Resistance[sITEMINFO_LIGHTING];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}
						if ( lpTransSkilAttackData->AttackState==105 ) {
							//³ú °ø°Ý ( Àü±â ÀúÇ×·Â Àû¿ë ) - ÀÎÃ¾Æ®
							rs = lpCharInfo->smCharInfo.Resistance[sITEMINFO_LIGHTING];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
							StunFlag = FALSE;
						}
						if ( lpTransSkilAttackData->AttackState==104 ) {
							//¾óÀ½ °ø°Ý ( ¾óÀ½ ÀúÇ×·Â Àû¿ë )
							rs = lpCharInfo->smCharInfo.Resistance[sITEMINFO_ICE];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}

						if ( lpTransSkilAttackData->AttackState==106 ) {
							//µ¶ °ø°Ý ( º£³ð ½ºÇÇ¾î )
							rs = lpCharInfo->smCharInfo.Resistance[sITEMINFO_POISON];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}

						StnPers = rand()%100;

						Dmg2 = pow;

						if ( lpTransSkilAttackData->AttackState==103 ) {
							//µð¹ÙÀÎ ¶óÀÌÆÃ ( ¾ðµ¥µå 50% °¡Áß )
							if ( lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD ) {
								pow += pow/2;
							}
							//³ú °ø°Ý ( Àü±â ÀúÇ×·Â Àû¿ë )
							rs = lpCharInfo->smCharInfo.Resistance[sITEMINFO_LIGHTING]/10;
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}


						switch( SkillCode ) {
							case SKILL_PLAY_MECHANIC_BOMB:
								//¸ÞÄ«´Ð¹ü ( ¹ÂÅÏÆ® ¸ÞÄ«´Ð ¸ó½ºÅÍ¿¡°Ô 50%Ãß°¡ )
								if ( lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_MUTANT ||
									lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_MECHANIC ) {
										pow += pow/2;
									}
									break;

							case SKILL_PLAY_SPARK:
								//½ºÆÄÅ© ( ¸ÞÄ«´Ð ¸ó½ºÅÍ¿¡°Ô 50% Ãß°¡ )
								if ( lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_MECHANIC ) {
									pow += pow/2;
								}
								break;

							case SKILL_PLAY_EXPANSION:
								//ÀÍ½ºÆÒ¼Ç ( ¹ÂÅÏÆ® ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡ )
								if ( lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_MUTANT ) {
									pow += (pow*30)/100;
								}
								break;

							case SKILL_PLAY_SWORD_BLAST:
								//¼Òµå ºí·¡½ºÆ® ( ³ë¸Ö , ¹ÂÅÏÆ® ¸ó½ºÅÍ 30% Ãß°¡ )
								if ( lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_NORMAL ||
									lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_MUTANT ) {
										pow += (pow*30)/100;
									}
									break;

							case SKILL_PLAY_PIERCING:
								//ÇÇ¾î½Ì ( ¹ÂÅÏÆ® ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡ )
								if ( lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_MUTANT ) {
									pow += (pow*30)/100;
								}
								break;

							case SKILL_PLAY_VENOM_SPEAR:
								//º£³ð ½ºÇÇ¾î µ¶Àû¿ë
								//lpChar->PlayPoison[1] = VenomSpear_Time[SkillPoint]*17;
								//lpChar->PlayPoison[0] = GetRandomPos( VenomSpear_Damage[SkillPoint][0] , VenomSpear_Damage[SkillPoint][1] );
								break;

							case SKILL_PLAY_PERFORATION:			//ÆÛÆ÷·¹ÀÌ¼Ç
								if ( (rand()%100)<GetCritical2( lpPlayInfo , lpCharInfo , dm_Critical_Temp ) ) {
									pow = (pow*170)/100;						//Å©¸®Æ¼ÄÃ °ø°Ý°¡Áß
/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý¹ÞÀ½ ( Critical )" , lpCharInfo->smCharInfo.szName );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/

								}
								break;

							case SKILL_PLAY_LIGHTNING_JAVELIN:
								if ( lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD ) {
									pow += pow/2;
								}
								break;

							case SKILL_PLAY_FLAME_BRANDISH:
								//StnPers = 100;
								break;

							case SKILL_PLAY_BOMB_SHOT:
								if ( lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_DEMON ) {
									pow += (pow*BombShot_DemonDamage[SkillPoint])/100;
								}
								break;

							case SKILL_PLAY_DIASTROPHISM:
								if (  lpCharInfo->smCharInfo.wPlayClass[0]!=MONSTER_CLASS_BOSS )
									StnPers = 0;
								break;

							case SKILL_PLAY_IMPULSION:
								// ¸ÞÄ«´Ð ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡ 
								if ( lpCharInfo->smCharInfo.Brood==smCHAR_MONSTER_MECHANIC ) {
									pow += (pow*30)/100;
								}
								break;

							case SKILL_PLAY_CYCLONE_STRIKE:
								if ( (rand()%100)<GetCritical2( lpPlayInfo , lpCharInfo , dm_Critical_Temp ) ) {
									pow = (pow*170)/100;						//Å©¸®Æ¼ÄÃ °ø°Ý°¡Áß
/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý¹ÞÀ½ ( Critical )" , lpCharInfo->smCharInfo.szName );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/
								}
								break;

							case SKILL_PLAY_CHAIN_LIGHTNING:
								if (  lpCharInfo->smCharInfo.wPlayClass[0]!=MONSTER_CLASS_BOSS &&
									lpCharInfo->smCharInfo.Resistance[sITEMINFO_LIGHTING]<=20 )
									StnPers = 0;
								break;


						}



						Dmg3 = pow;

						if ( pow>0 ) {
							rsSendAttackUser( lpPlayInfo , lpCharInfo , pow/PK_POWER_DIVIDE , 0x80 );

							Dmg4 = pow;


/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý¹ÞÀ½ ( %d %d %d %d )" , lpCharInfo->smCharInfo.szName, Dmg1 , Dmg2, Dmg3, Dmg4 );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/
						}
						break;
					}
				}
			}
		}



	case 2:	//·Î¾î
	case 5:	//½¯µå½ºÆ®¶óÀÌÅ©
		for( cnt2=0;cnt2<CONNECTMAX;cnt2++ ) {

			lpCharInfo = &rsPlayInfo[cnt2];

			if ( lpCharInfo && lpCharInfo->lpsmSock && lpCharInfo->smCharInfo.State ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpCharInfo->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						//°Å¸®°Ë»ç
						//if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar , dDist )==FALSE ) break;

						//»ý¼Ó¼º ¿¡ µû¸£ Áß¸³»óÅÂ À¯Áö 
						rs = lpCharInfo->smCharInfo.Resistance[sITEMINFO_BIONIC];
						if ( rs<0 ) rs = 0;
						if ( rs>=100 ) rs=100;
						rs = 100-rs;

						if ( lpTransSkilAttackData->AttackState==2 ) {
							//·Î¾î
							//if ( (rand()%100)>rs ) {
								//lpChar->PlayStunCount = lpTransSkilAttackData->Power<<4;		//Áß¸³»óÅÂ ¼³Á¤
								//lpChar->PlayStunCount = ( lpChar->PlayStunCount * rs )/100;
							//}
							rsSendAttackUser( lpPlayInfo , lpCharInfo , 1 , 0x80 , -SKILL_PLAY_ROAR , (lpTransSkilAttackData->Power*rs)/100 );

						}
						else if ( lpTransSkilAttackData->AttackState==5 ) {
							//½¯µå ½ºÆ®¶óÀÌÅ©
							/*
							pow = ( lpTransSkilAttackData->Power * lpChar->smCharInfo.Absorption )/100;
							pow = lpTransSkilAttackData->Power-pow;
							if ( pow>0 ) {
								//¸íÁß ( °ø°Ý ¼º°ø )
								lpChar->smCharInfo.Life[0] -= pow;
								if ( lpChar->lpAttackDamageList ) rsRecordCharDamage( lpPlayInfo , lpChar , pow );	//¹ÞÀº°ø°Ý ±â¾ïÇÏ´Â ¸÷

							}
							lpChar->PlayStunCount = 16*10;			//Áß¸³»óÅÂ 10ÃÊ
							lpChar->PlayStunCount = ( lpChar->PlayStunCount * rs )/100;
							*/
							rsSendAttackUser( lpPlayInfo , lpCharInfo , lpTransSkilAttackData->Power/PK_POWER_DIVIDE , 0x80 , -SKILL_PLAY_SHIELD_STRIKE , (10*rs)/100 );


/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý¹ÞÀ½ ( %d %d )" , lpCharInfo->smCharInfo.szName, lpTransSkilAttackData->Power , pow );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/
						}
						break;
					}
				}
			}
		}
		break;

	case 3:
		if ( SkillCode==SKILL_PLAY_GLACIAL_SPIKE ) {
			//±Û·¡¼È ½ºÆÄÀÌÅ©
			time = 8;
			SlowSpeed = 200;
		}
		else {
			//±×¶ó¿îµå ÆÄÀÌÅ©
			time = 10;
			SlowSpeed = 128;
			cnt2 = lpTransSkilAttackData->AttackSize>>FLOATNS;
			for(cnt=0;cnt<10;cnt++) {
				//±×¶ó¿îµå ÆÄÀÌÅ© ½Ã°£À» Ã£´Â´Ù
				if ( G_Pike_Range[cnt]==cnt2 ) {
					time = G_Pike_Time[cnt];
					break;
				}
			}
		}

		for( cnt2=0;cnt2<CONNECTMAX;cnt2++ ) {
			lpCharInfo = &rsPlayInfo[cnt2];

			if ( lpCharInfo && lpCharInfo->lpsmSock && lpCharInfo->smCharInfo.State ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpCharInfo->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						//°Å¸®°Ë»ç
						//if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar , dDist )==FALSE ) break;

							pow = lpTransSkilAttackData->Power;
							Dmg1 = pow;
							rs = lpCharInfo->smCharInfo.Resistance[sITEMINFO_ICE];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
							Dmg2 = pow;

/*
							lpChar->PlaySlowCount = time;		//¼Óµµ ´À·ÁÁü
							lpChar->PlaySlowSpeed = SlowSpeed;

							lpChar->PlayStunCount = 0;			//Áß¸³¸ðµå ÇØÁ¦

							if ( rs ) {
								if ( rs<0 ) rs = 0;
								lpChar->PlaySlowCount -= (rs*time)/100;
								if ( lpChar->PlaySlowCount<0 ) lpChar->PlaySlowCount = 0;
							}

							//if ( (10-rs/10)
							//10-(¸ó½ºÅÍ¼Ó¼º/10) ÃÊ
*/
							if ( pow>0 ) {
								//¸íÁß ( °ø°Ý ¼º°ø )
								rsSendAttackUser( lpPlayInfo , lpCharInfo , pow/PK_POWER_DIVIDE , 0x80 , -SkillCode , time );

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý¹ÞÀ½ ( %d %d )" , lpCharInfo->smCharInfo.szName, Dmg1 , Dmg2  );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/
							}							
						//}

						break;
					}
				}
			}
		}
		break;

	case 7:
		//µð½ºÅä¼Ç
//	int	rs,time;
		time = Distortion_Time[SkillPoint];
		rs = 240-(240*Distortion_SpeedSubPercent[SkillPoint])/100;

		for( cnt2=0;cnt2<CONNECTMAX;cnt2++ ) {
			lpCharInfo = &rsPlayInfo[cnt2];

			if ( lpCharInfo && lpCharInfo->lpsmSock && lpCharInfo->smCharInfo.State ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpCharInfo->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {
/*
							lpChar->PlaySlowCount = time;		//¼Óµµ ´À·ÁÁü
							lpChar->PlaySlowSpeed = rs;
							lpChar->PlayDistortion = time;

							lpChar->PlayStunCount = 0;			//Áß¸³¸ðµå ÇØÁ¦
*/
							rsSendAttackUser( lpPlayInfo , lpCharInfo , 1 , 0x80 , -SkillCode , time );

							break;
					}
				}
			}
		}

		break;

	}

	return TRUE;
}


int RecvRangeAttack( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData , int AreaNum , int PlaySkillCode )
{

	smCHAR *lpChar;
	int cnt,cnt2,pow;
	int ang,ang2;
	int x,y,z,dist;
	int	rs,time;
	int life,TotalLife;
	int	StunFlag;
	smTRANS_COMMAND	smTransCommand;
	int	dDist;
	int	SkillCode , SkillPoint;
	int	StnPers;
	int	Dmg1, Dmg2, Dmg3, Dmg4;
	int SlowSpeed;

	TRANS_PARTY_SKILL		TransPartySkill;

	SkillCode = PlaySkillCode&0xFF;
	SkillPoint = PlaySkillCode>>8;
	if ( SkillPoint ) {
		SkillPoint --;
		if ( SkillPoint<0 || SkillPoint>=10 ) SkillPoint = 0;
	}


	STG_AREA *lpStgArea;

	if ( AreaNum<STAGE_AREA_MAX && StageArea[AreaNum].lpStage ) lpStgArea = &StageArea[AreaNum];
	else {
		return FALSE;
	}

	if ( lpPlayInfo->HideMode && lpPlayInfo->AdminMode<4 ) return FALSE;

	//°Å¸® °Ë»ç ( ÇÃ·¹ÀÌ¾î¿Í ¸ñÇ¥ÁöÁ¡ °Å¸® )
	if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y,lpTransSkilAttackData->z ,lpPlayInfo )==FALSE )
		return FALSE;

	dDist = lpTransSkilAttackData->AttackSize+60;
	dDist *= dDist;



	switch( lpTransSkilAttackData->AttackState ) {
	case 0:		//ÀÏ¹Ý ¹üÀ§Çü
	case 100:	//·¹ÀÌÁö ¿Àºê Á¦Å©¶÷ ( ºÒ °ø°Ý )
	case 101:	//½ºÆÄÅ© ( ³ú °ø°Ý )
	case 103:	//µð¹ÙÀÎ ¶óÀÌÆÃ ( ¾ðµ¥µå 50% °¡Áß )
	case 104:	//¾óÀ½ ( °ø°Ý )
	case 105:	//ÀÎÃ¾Æ® Àü±â
	case 106:	//µ¶ °ø°Ý

		for( cnt2=0;cnt2<STG_MONSTER_MAX;cnt2++ ) {
			lpChar = lpStgArea->lpCharMonster[cnt2];
			if ( lpChar && lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						if ( !lpPlayInfo->lpChrTarget ) lpPlayInfo->lpChrTarget = lpChar;		//¿ì¼± ¸ñÇ¥ Ä³¸¯À¸·Î ¼³Á¤

						if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_USER && 
							lpChar->HoSkillCode && 
							lpChar->lpMasterPlayInfo==lpPlayInfo ) {
								continue;	//º»ÀÎ ¼ÒÈ¯¸÷Àº µ¥¹ÌÁö ¾øÀ½
							}

						//°Å¸®°Ë»ç
						if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar , dDist )==FALSE ) break;

						pow = lpTransSkilAttackData->Power;
						StunFlag = TRUE;

						Dmg1 = pow;

						if ( lpTransSkilAttackData->AttackState==100 ) {
							//ºÒ °ø°Ý ( ºÒ ÀúÇ×·Â Àû¿ë )
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_FIRE];
							if ( SkillCode==SKILL_PLAY_METEO ) {
								rs/=2;		//¹ÌÆ¼¾î ºÒ¼Ó¼º 50% Àû¿ë
							}
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}
						if ( lpTransSkilAttackData->AttackState==101 ) {
							//³ú °ø°Ý ( Àü±â ÀúÇ×·Â Àû¿ë )
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_LIGHTING];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}
						if ( lpTransSkilAttackData->AttackState==105 ) {
							//³ú °ø°Ý ( Àü±â ÀúÇ×·Â Àû¿ë ) - ÀÎÃ¾Æ®
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_LIGHTING];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
							StunFlag = FALSE;
						}
						if ( lpTransSkilAttackData->AttackState==104 ) {
							//¾óÀ½ °ø°Ý ( ¾óÀ½ ÀúÇ×·Â Àû¿ë )
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_ICE];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}

						if ( lpTransSkilAttackData->AttackState==106 ) {
							//µ¶ °ø°Ý ( º£³ð ½ºÇÇ¾î )
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_POISON];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}

						StnPers = rand()%100;

						Dmg2 = pow;

						if ( lpTransSkilAttackData->AttackState==103 ) {
							//µð¹ÙÀÎ ¶óÀÌÆÃ ( ¾ðµ¥µå 50% °¡Áß )
							if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD ) {
								pow += pow/2;
							}
							//³ú °ø°Ý ( Àü±â ÀúÇ×·Â Àû¿ë )
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_LIGHTING]/10;
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}


						switch( SkillCode ) {
							case SKILL_PLAY_MECHANIC_BOMB:
								//¸ÞÄ«´Ð¹ü ( ¹ÂÅÏÆ® ¸ÞÄ«´Ð ¸ó½ºÅÍ¿¡°Ô 50%Ãß°¡ )
								if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_MUTANT ||
									lpChar->smCharInfo.Brood==smCHAR_MONSTER_MECHANIC ) {
										pow += pow/2;
									}
									break;

							case SKILL_PLAY_SPARK:
								//½ºÆÄÅ© ( ¸ÞÄ«´Ð ¸ó½ºÅÍ¿¡°Ô 50% Ãß°¡ )
								if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_MECHANIC ) {
									pow += pow/2;
								}
								break;

							case SKILL_PLAY_EXPANSION:
								//ÀÍ½ºÆÒ¼Ç ( ¹ÂÅÏÆ® ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡ )
								if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_MUTANT ) {
									pow += (pow*30)/100;
								}
								break;

							case SKILL_PLAY_SWORD_BLAST:
								//¼Òµå ºí·¡½ºÆ® ( ³ë¸Ö , ¹ÂÅÏÆ® ¸ó½ºÅÍ 30% Ãß°¡ )
								if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_NORMAL ||
									lpChar->smCharInfo.Brood==smCHAR_MONSTER_MUTANT ) {
										pow += (pow*30)/100;
									}
									break;

							case SKILL_PLAY_PIERCING:
								//ÇÇ¾î½Ì ( ¹ÂÅÏÆ® ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡ )
								if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_MUTANT ) {
									pow += (pow*30)/100;
								}
								break;

							case SKILL_PLAY_VENOM_SPEAR:
								//º£³ð ½ºÇÇ¾î µ¶Àû¿ë
								lpChar->PlayPoison[1] = VenomSpear_Time[SkillPoint]*17;
								lpChar->PlayPoison[0] = GetRandomPos( VenomSpear_Damage[SkillPoint][0] , VenomSpear_Damage[SkillPoint][1] );
								break;

							case SKILL_PLAY_PERFORATION:			//ÆÛÆ÷·¹ÀÌ¼Ç
								if ( (rand()%100)<GetCritical( lpPlayInfo , lpChar , dm_Critical_Temp ) ) {
									pow = (pow*170)/100;						//Å©¸®Æ¼ÄÃ °ø°Ý°¡Áß
/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý¹ÞÀ½ ( Critical )" , lpChar->smCharInfo.szName );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/

								}
								break;

							case SKILL_PLAY_LIGHTNING_JAVELIN:
								if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD ) {
									pow += pow/2;
								}
								break;

							case SKILL_PLAY_FLAME_BRANDISH:
								//StnPers = 100;
								break;

							case SKILL_PLAY_BOMB_SHOT:
								if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_DEMON ) {
									pow += (pow*BombShot_DemonDamage[SkillPoint])/100;
								}
								break;

							case SKILL_PLAY_DIASTROPHISM:
								//lpChar->lpTargetPlayInfo = 0;
								//lpChar->dwNextMotionCode = CHRMOTION_STATE_STAND;
								if (  lpChar->smCharInfo.wPlayClass[0]!=MONSTER_CLASS_BOSS )
									StnPers = 0;

								if ( lpChar->smCharInfo.dwCharSoundCode==snCHAR_SOUND_DEATHKNIGHT || lpChar->smCharInfo.dwCharSoundCode==snCHAR_SOUND_BABEL || lpChar->smCharInfo.dwCharSoundCode==snCHAR_SOUND_KELVEZU || lpChar->smCharInfo.dwCharSoundCode==snCHAR_SOUND_MOKOVA ) 
									StnPers = 100;
								break;

							case SKILL_PLAY_IMPULSION:
								// ¸ÞÄ«´Ð ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡ 
								if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_MECHANIC ) {
									pow += (pow*30)/100;
								}
								break;

							case SKILL_PLAY_CYCLONE_STRIKE:
								if ( (rand()%100)<GetCritical( lpPlayInfo , lpChar , dm_Critical_Temp ) ) {
									pow = (pow*170)/100;						//Å©¸®Æ¼ÄÃ °ø°Ý°¡Áß
/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý¹ÞÀ½ ( Critical )" , lpChar->smCharInfo.szName );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/
								}
								break;

							case SKILL_PLAY_CHAIN_LIGHTNING:
								//lpChar->lpTargetPlayInfo = 0;
								//lpChar->dwNextMotionCode = CHRMOTION_STATE_STAND;
								if (  lpChar->smCharInfo.wPlayClass[0]!=MONSTER_CLASS_BOSS &&
									lpChar->smCharInfo.Resistance[sITEMINFO_LIGHTING]<=20 )
									StnPers = 0;
								break;


						}

						lpChar->PlayStunCount = 0;			//Áß¸³¸ðµå ÇØÁ¦

						Dmg3 = pow;

						pow -= ( pow * lpChar->smCharInfo.Absorption )/100;
						//pow = lpTransSkilAttackData->Power-pow;

						Dmg4 = pow;

						if ( pow>0 ) {
							//¸íÁß ( °ø°Ý ¼º°ø )
							lpChar->smCharInfo.Life[0] -= pow;

							if ( lpChar->lpAttackDamageList || lpChar->lpAttackDamageList_BlessCastle ) rsRecordCharDamage( lpPlayInfo , lpChar , pow );	//¹ÞÀº°ø°Ý ±â¾ïÇÏ´Â ¸÷

							if ( StunFlag && lpChar->smCharInfo.Life[0] && StnPers<lpChar->smMonsterInfo.DamageStunPers ) {
								//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ

								if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
									lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {

										ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
										ang = (ang2+ANGLE_180) & ANGCLIP;
										lpChar->Angle.y = ang;
										lpChar->MoveAngle( 10 );
										lpChar->Angle.y = ang2;

										//4% ÀÌ»ó
										if ( ((lpChar->smCharInfo.Life[1]<<2)/100)<lpTransSkilAttackData->Power || StnPers==0 ) {
											lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
										}
								}
							}

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý¹ÞÀ½ ( %d %d %d %d )" , lpChar->smCharInfo.szName, Dmg1 , Dmg2, Dmg3, Dmg4 );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/


						}


						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;
					}
				}
			}
		}
		break;
	case 1:
		//ÆÄÀÌÅ© À©µå
		for( cnt2=0;cnt2<STG_MONSTER_MAX;cnt2++ ) {
			lpChar = lpStgArea->lpCharMonster[cnt2];
			if ( lpChar && lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						//°Å¸®°Ë»ç
						if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar , dDist )==FALSE ) break;

						x = (lpPlayInfo->Position.x-lpChar->pX)>>FLOATNS;
						y = (lpPlayInfo->Position.y-lpChar->pY)>>FLOATNS;
						z = (lpPlayInfo->Position.z-lpChar->pZ)>>FLOATNS;
						if ( abs(y)>100 || (x*x+z*z)>(800*800) ) break;		//°Å¸®°¡ ¸Õ°æ¿ì ½ÇÆÐ

						dist = (int)sqrt(x*x+z*z);
						dist = lpTransSkilAttackData->AttackSize - dist;

				

						if ( lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_DEATHKNIGHT && lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_BABEL && lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_KELVEZU && lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_MOKOVA ) 
						{
							if ( lpChar->smCharInfo.Life[0] ) {
								//µÚ·Î ¹°·¯³ª°Ô ÇÔ
								ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
								ang = (ang2+ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->OverLapPosi2 = FALSE;
								lpChar->MoveAngle( dist );
								lpChar->Angle.y = ang2;

								if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
									lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {
										//4% ÀÌ»ó
										if ( ((lpChar->smCharInfo.Life[1]<<2)/100)<lpTransSkilAttackData->Power ) {
											lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
										}
								}
								lpChar->lpTargetPlayInfo = 0;
								lpChar->dwNextMotionCode = CHRMOTION_STATE_STAND;
							}
						}

						pow = ( lpTransSkilAttackData->Power * lpChar->smCharInfo.Absorption )/100;
						pow = lpTransSkilAttackData->Power-pow;

						lpChar->PlayStunCount = 0;			//Áß¸³¸ðµå ÇØÁ¦

						if ( pow>0 ) {
							//¸íÁß ( °ø°Ý ¼º°ø )
							lpChar->smCharInfo.Life[0] -= pow;
						}

						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;

					}
				}
			}
		}
		break;
	case 2:	//·Î¾î
	case 5:	//½¯µå½ºÆ®¶óÀÌÅ©
	case 201:	//Compulsion
		for( cnt2=0;cnt2<STG_MONSTER_MAX;cnt2++ ) {
			lpChar = lpStgArea->lpCharMonster[cnt2];
			if ( lpChar && lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						//°Å¸®°Ë»ç
						if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar , dDist )==FALSE ) break;

						//»ý¼Ó¼º ¿¡ µû¸£ Áß¸³»óÅÂ À¯Áö 
						rs = lpChar->smCharInfo.Resistance[sITEMINFO_BIONIC];
						if ( rs<0 ) rs = 0;
						if ( rs>=100 ) rs=100;
						rs = 100-rs;

						if ( lpTransSkilAttackData->AttackState==2 ) {
							//·Î¾î
							//if ( (rand()%100)>rs ) {
								lpChar->PlayStunCount = lpTransSkilAttackData->Power<<4;		//Áß¸³»óÅÂ ¼³Á¤
								lpChar->PlayStunCount = ( lpChar->PlayStunCount * rs )/100;
							//}
						}
						else if ( lpTransSkilAttackData->AttackState==5 ) {
							//½¯µå ½ºÆ®¶óÀÌÅ©
							pow = ( lpTransSkilAttackData->Power * lpChar->smCharInfo.Absorption )/100;
							pow = lpTransSkilAttackData->Power-pow;
							if ( pow>0 ) {
								//¸íÁß ( °ø°Ý ¼º°ø )
								lpChar->smCharInfo.Life[0] -= pow;
								if ( lpChar->lpAttackDamageList || lpChar->lpAttackDamageList_BlessCastle ) rsRecordCharDamage( lpPlayInfo , lpChar , pow );	//¹ÞÀº°ø°Ý ±â¾ïÇÏ´Â ¸÷

							}
							lpChar->PlayStunCount = 16*10;			//Áß¸³»óÅÂ 10ÃÊ
							lpChar->PlayStunCount = ( lpChar->PlayStunCount * rs )/100;

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý¹ÞÀ½ ( %d %d )" , lpChar->smCharInfo.szName, lpTransSkilAttackData->Power , pow );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/

						}
						else if (lpTransSkilAttackData->AttackState==201 ) {	//Compulsion

							if ( lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_DEATHKNIGHT && lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_BABEL && lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_KELVEZU && lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_MOKOVA ) 
							{
								lpChar->lpTargetPlayInfo = 0;
								lpChar->lpTargetChar = 0;

								cnt = Compulsion_Time[SkillPoint]*1000;
								//cnt = 12*1000;

								lpChar->lpCompulsionPlayInfo = lpPlayInfo;
								lpChar->dwCompulsionTime = dwPlayServTime+cnt;

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ½Ã¼±²ø±â ( %d ÃÊ )" , lpChar->smCharInfo.szName, cnt/1000 );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/
							}

						}

						if ( lpChar->smCharInfo.Life[0] && 
							lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_BABEL &&
							lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_DEATHKNIGHT &&
							lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_KELVEZU &&
							lpChar->smCharInfo.dwCharSoundCode!=snCHAR_SOUND_MOKOVA ) 
						{
							//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ
							ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
							ang = (ang2+ANGLE_180) & ANGCLIP;
							lpChar->Angle.y = ang;
							lpChar->MoveAngle( 10 );
							lpChar->Angle.y = ang2;

							if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
								lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {
								lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
							}
						}

						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;
					}
				}
			}
		}
		break;
	case 3:
		if ( SkillCode==SKILL_PLAY_GLACIAL_SPIKE ) {
			//±Û·¡¼È ½ºÆÄÀÌÅ©
			time = 8*17;
			SlowSpeed = 200;
		}
		else {
			//±×¶ó¿îµå ÆÄÀÌÅ©
			time = 175;
			SlowSpeed = 0;
			cnt2 = lpTransSkilAttackData->AttackSize>>FLOATNS;
			for(cnt=0;cnt<10;cnt++) {
				//±×¶ó¿îµå ÆÄÀÌÅ© ½Ã°£À» Ã£´Â´Ù
				if ( G_Pike_Range[cnt]==cnt2 ) {
					time = G_Pike_Time[cnt]*17;
					break;
				}
			}
		}

		for( cnt2=0;cnt2<STG_MONSTER_MAX;cnt2++ ) {
			lpChar = lpStgArea->lpCharMonster[cnt2];
			if ( lpChar && lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						//°Å¸®°Ë»ç
						if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar , dDist )==FALSE ) break;

							pow = lpTransSkilAttackData->Power;
							Dmg1 = pow;
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_ICE];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
							Dmg2 = pow;
							pow -= ( pow * lpChar->smCharInfo.Absorption )/100;
							//pow = lpTransSkilAttackData->Power-pow;
							Dmg3 = pow;

							//int G_Pike_Time[10]	     = {3,4,5,6,7,8,9,10,11,12};


							lpChar->PlaySlowCount = time;		//¼Óµµ ´À·ÁÁü
							lpChar->PlaySlowSpeed = SlowSpeed;

							lpChar->PlayStunCount = 0;			//Áß¸³¸ðµå ÇØÁ¦
							lpChar->PlayDistortion = 0;			//µð½ºÅä¼Ç ÇØÁ¦

							if ( rs ) {
								if ( rs<0 ) rs = 0;
								lpChar->PlaySlowCount -= (rs*time)/100;
								if ( lpChar->PlaySlowCount<0 ) lpChar->PlaySlowCount = 0;
							}

							//if ( (10-rs/10)
							//10-(¸ó½ºÅÍ¼Ó¼º/10) ÃÊ

							if ( pow>0 ) {
								//¸íÁß ( °ø°Ý ¼º°ø )
								lpChar->smCharInfo.Life[0] -= pow;
								if ( lpChar->lpAttackDamageList || lpChar->lpAttackDamageList_BlessCastle ) rsRecordCharDamage( lpPlayInfo , lpChar , pow );	//¹ÞÀº°ø°Ý ±â¾ïÇÏ´Â ¸÷

								if ( lpChar->smCharInfo.Life[0] ) {
									//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ
									ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
									ang = (ang2+ANGLE_180) & ANGCLIP;
									lpChar->Angle.y = ang;
									lpChar->MoveAngle( 10 );
									lpChar->Angle.y = ang2;

									if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
										lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {
											//4% ÀÌ»ó
											if ( ((lpChar->smCharInfo.Life[1]<<2)/100)<lpTransSkilAttackData->Power ) {
												lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
											}
									}
								}

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý¹ÞÀ½ ( %d %d %d )" , lpChar->smCharInfo.szName, Dmg1 , Dmg2, Dmg3 );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/
							
						}

						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;
					}
				}
			}
		}
		break;
	case 4:	//¼Ò¿ï¼­Ä¿
		if ( lpTransSkilAttackData->Power<1 || lpTransSkilAttackData->Power>10 ) break;
		TotalLife = 0;

		for( cnt2=0;cnt2<STG_MONSTER_MAX;cnt2++ ) {
			lpChar = lpStgArea->lpCharMonster[cnt2];
			if ( lpChar && lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] &&
						((lpChar->smCharInfo.Life[1]*50)/100)<lpChar->smCharInfo.Life[0] &&
						lpChar->smCharInfo.Brood!=smCHAR_MONSTER_UNDEAD ) {	//¾ðµ¥µå Á¦¿Ü

						//°Å¸®°Ë»ç
						if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar , dDist )==FALSE ) break;

						pow = Soul_Sucker_Absorb[ lpTransSkilAttackData->Power-1 ];

						rs = lpChar->smCharInfo.Resistance[sITEMINFO_BIONIC];
						if ( rs ) {
							if ( rs>=100 ) rs=100;
							if ( rs<=-100 ) rs=-100;
							pow -= ((pow*rs)/100);
						}


						lpChar->PlayStunCount = 0;			//Áß¸³¸ðµå ÇØÁ¦

						if ( pow>0 ) {
							//¸íÁß ( °ø°Ý ¼º°ø )
							life = (lpChar->smCharInfo.Life[1]*pow)/100;
							lpChar->smCharInfo.Life[0] -= life;
							if ( lpChar->lpAttackDamageList || lpChar->lpAttackDamageList_BlessCastle ) rsRecordCharDamage( lpPlayInfo , lpChar , life );	//¹ÞÀº°ø°Ý ±â¾ïÇÏ´Â ¸÷
							if ( lpChar->smCharInfo.Life[0]<0 ) life+=lpChar->smCharInfo.Life[0];
							TotalLife += life;

							if ( lpChar->smCharInfo.Life[0] && (rand()%100)<lpChar->smMonsterInfo.DamageStunPers ) {
								//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ
								ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
								ang = (ang2+ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->MoveAngle( 10 );
								lpChar->Angle.y = ang2;

								if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
									lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {

										lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
								}
							}
						}

						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;
					}
				}
			}
		}
		if ( TotalLife>0 ) {
			//»©¾ÑÀº »ý¸í·ÂÀ» º¸³»ÁØ´Ù
			smTransCommand.code = smTRANSCODE_VIRTURAL_POTION;
			smTransCommand.size = sizeof( smTRANS_COMMAND );
			smTransCommand.WParam = TotalLife;
			smTransCommand.LParam = 0;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = 0;
			if ( lpPlayInfo->lpsmSock ) 
				lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
		}
		break;

	case 6:	//¿¢½ºÆ¾¼Ç
		if ( lpTransSkilAttackData->Power<1 || lpTransSkilAttackData->Power>10 ) break;
		TotalLife = 0;

		ZeroMemory( &TransPartySkill , sizeof(TRANS_PARTY_SKILL) );

		for( cnt2=0;cnt2<STG_MONSTER_MAX;cnt2++ ) {
			lpChar = lpStgArea->lpCharMonster[cnt2];
			if ( lpChar && lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] &&
						lpChar->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD ) {	//¾ðµ¥µå¸¸

						//°Å¸®°Ë»ç
						if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar , dDist )==FALSE ) break;

						pow = Extinction_Percent[ lpTransSkilAttackData->Power-1 ];
						pow += lpPlayInfo->smCharInfo.Level/5;

						rs = lpChar->smCharInfo.Resistance[sITEMINFO_BIONIC];
						if ( rs ) {
							if ( rs>=100 ) rs=100;
							if ( rs<=-100 ) rs=-100;
							pow -= ((pow*rs)/100);
						}

						lpChar->PlayStunCount = 0;			//Áß¸³¸ðµå ÇØÁ¦

						if ( (rand()%100)<pow ) {

							if( TransPartySkill.PartyCount<8 )
								TransPartySkill.dwPartyUser[TransPartySkill.PartyCount++] = lpChar->dwObjectSerial;

							//¸íÁß ( °ø°Ý ¼º°ø )
							life = (lpChar->smCharInfo.Life[0]*Extinction_Amount[ lpTransSkilAttackData->Power-1 ])/100;
							lpChar->smCharInfo.Life[0] -= life;
							if ( lpChar->lpAttackDamageList || lpChar->lpAttackDamageList_BlessCastle ) rsRecordCharDamage( lpPlayInfo , lpChar , life );	//¹ÞÀº°ø°Ý ±â¾ïÇÏ´Â ¸÷
							if ( lpChar->smCharInfo.Life[0]<0 ) life+=lpChar->smCharInfo.Life[0];
							TotalLife += life;

							if ( lpChar->smCharInfo.Life[0] && (rand()%100)<lpChar->smMonsterInfo.DamageStunPers ) {
								//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ
								ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
								ang = (ang2+ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->MoveAngle( 10 );
								lpChar->Angle.y = ang2;

								if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
									lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {

										lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
								}
							}
						}

						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;
					}
				}
			}
		}

		if( TransPartySkill.PartyCount>0 && lpPlayInfo && lpPlayInfo->lpsmSock ) {
			TransPartySkill.code = smTRANSCODE_PARTY_SKILL;
			TransPartySkill.size = sizeof(TRANS_PARTY_SKILL);
			TransPartySkill.dwSkillCode = SKILL_PLAY_EXTINCTION;
			rsSendCommandUser2( lpPlayInfo , (smTRANS_COMMAND *)&TransPartySkill );
		}

		break;
/*
int Distortion_SpeedSubPercent[10]  = {5,6,7,8,9,10,11,12,13,14};         //¼Óµµ ÀúÇÏ 
int Distortion_DamageSubPercent[10] = {5,6,7,8,9,10,11,12,13,14};         //°ø°Ý·Â ÀúÇÏ
int Distortion_Area[10]             = {120,125,130,135,140,145,150,155,160,165};     
int Distortion_Time[10]             = {4,5,6,7,8,9,10,11,12,13};
int Distortion_UseMana[10]          = {105,110,115,120,125,130,135,140,145,150};   
*/
	case 7:
		//µð½ºÅä¼Ç
//	int	rs,time;
		time = Distortion_Time[SkillPoint]*17;
		rs = 240-(240*Distortion_SpeedSubPercent[SkillPoint])/100;

		for( cnt2=0;cnt2<STG_MONSTER_MAX;cnt2++ ) {
			lpChar = lpStgArea->lpCharMonster[cnt2];
			if ( lpChar && lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						//°Å¸®°Ë»ç
						if ( rsCheckAttackRange( lpTransSkilAttackData->x,lpTransSkilAttackData->y, lpTransSkilAttackData->z, lpChar , dDist )==FALSE ) break;


							lpChar->PlaySlowCount = time;		//¼Óµµ ´À·ÁÁü
							lpChar->PlaySlowSpeed = rs;
							lpChar->PlayDistortion = time;

							lpChar->PlayStunCount = 0;			//Áß¸³¸ðµå ÇØÁ¦


							if ( lpChar->smCharInfo.Life[0] ) {
								//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ
								ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
								ang = (ang2+ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->MoveAngle( 10 );
								lpChar->Angle.y = ang2;

								if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
									lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {
										//4% ÀÌ»ó
										if ( ((lpChar->smCharInfo.Life[1]<<2)/100)<lpTransSkilAttackData->Power ) {
											lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
										}
								}
							}
							
							if ( lpChar->smCharInfo.Life[0]<=0 ) {
								lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
								lpChar->lpExt2 = (void *)lpPlayInfo;
							}

							break;
					}
				}
			}
		}
		break;


	}

	return TRUE;
}


int RecvRangeAttack( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData )
{
/*
	smCHAR *lpChar;
	int cnt,cnt2,pow;
	int ang,ang2;
	int x,y,z,dist;
	int	rs,time;
	int life,TotalLife;
	int	StunFlag;
	smTRANS_COMMAND	smTransCommand;

	switch( lpTransSkilAttackData->AttackState ) {
	case 0:		//ÀÏ¹Ý ¹üÀ§Çü
	case 100:	//·¹ÀÌÁö ¿Àºê Á¦Å©¶÷ ( ºÒ °ø°Ý )
	case 101:	//½ºÆÄÅ© ( ³ú °ø°Ý )
	case 103:	//µð¹ÙÀÎ ¶óÀÌÆÃ ( ¾ðµ¥µå 50% °¡Áß )
	case 104:	//¾óÀ½ ( °ø°Ý )
	case 105:	//ÀÎÃ¾Æ® Àü±â
		for(cnt2=0;cnt2<AUTOPLAYER_MAX;cnt2++) {
			lpChar = &chrAutoPlayer[cnt2];
			if ( lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

					x = (lpPlayInfo->Position.x-lpChar->pX)>>FLOATNS;
					y = (lpPlayInfo->Position.y-lpChar->pY)>>FLOATNS;
					z = (lpPlayInfo->Position.z-lpChar->pZ)>>FLOATNS;
					if ( abs(y)>100 || (x*x+z*z)>(800*800) ) break;		//°Å¸®°¡ ¸Õ°æ¿ì ½ÇÆÐ

						pow = lpTransSkilAttackData->Power;
						StunFlag = TRUE;

						if ( lpTransSkilAttackData->AttackState==100 ) {
							//ºÒ °ø°Ý ( ºÒ ÀúÇ×·Â Àû¿ë )
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_FIRE];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}
						if ( lpTransSkilAttackData->AttackState==101 ) {
							//³ú °ø°Ý ( Àü±â ÀúÇ×·Â Àû¿ë )
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_LIGHTING];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}
						if ( lpTransSkilAttackData->AttackState==105 ) {
							//³ú °ø°Ý ( Àü±â ÀúÇ×·Â Àû¿ë ) - ÀÎÃ¾Æ®
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_LIGHTING];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
							StunFlag = FALSE;
						}

						if ( lpTransSkilAttackData->AttackState==104 ) {
							//¾óÀ½ °ø°Ý ( ¾óÀ½ ÀúÇ×·Â Àû¿ë )
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_ICE];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}
						if ( lpTransSkilAttackData->AttackState==103 ) {
							//µð¹ÙÀÎ ¶óÀÌÆÃ ( ¾ðµ¥µå 50% °¡Áß )
							if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD ) {
								pow += pow/2;
							}
							//³ú °ø°Ý ( Àü±â ÀúÇ×·Â Àû¿ë )
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_LIGHTING]/10;
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
						}


						pow -= ( pow * lpChar->smCharInfo.Absorption )/100;
						//pow = lpTransSkilAttackData->Power-pow;

						if ( pow>0 ) {
							//¸íÁß ( °ø°Ý ¼º°ø )
							lpChar->smCharInfo.Life[0] -= pow;

							if ( StunFlag && lpChar->smCharInfo.Life[0] && (rand()%100)<lpChar->smMonsterInfo.DamageStunPers ) {
								//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ
								//ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpTransSkilAttackData->x, lpTransSkilAttackData->z );
								ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
								ang = (ang2+ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->MoveAngle( 10 );
								lpChar->Angle.y = ang2;

								if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
									lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {
										//4% ÀÌ»ó
										if ( ((lpChar->smCharInfo.Life[1]<<2)/100)<lpTransSkilAttackData->Power ) {
											lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
										}
								}
							}
						}


						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;
					}
				}
			}
		}
		break;
	case 1:
		//ÆÄÀÌÅ© À©µå
		for(cnt2=0;cnt2<AUTOPLAYER_MAX;cnt2++) {
			lpChar = &chrAutoPlayer[cnt2];
			if ( lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						x = (lpPlayInfo->Position.x-lpChar->pX)>>FLOATNS;
						y = (lpPlayInfo->Position.y-lpChar->pY)>>FLOATNS;
						z = (lpPlayInfo->Position.z-lpChar->pZ)>>FLOATNS;
						if ( abs(y)>100 || (x*x+z*z)>(800*800) ) break;		//°Å¸®°¡ ¸Õ°æ¿ì ½ÇÆÐ

						//x = ( lpChar->pX-lpPlayInfo->Position.x )>>FLOATNS;
						//z = ( lpChar->pZ-lpPlayInfo->Position.z )>>FLOATNS;

						dist = (int)sqrt(x*x+z*z);
						dist = (lpTransSkilAttackData->AttackSize>>FLOATNS) - dist;

				
							if ( lpChar->smCharInfo.Life[0] ) {
								//µÚ·Î ¹°·¯³ª°Ô ÇÔ
								ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
								ang = (ang2+ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->OverLapPosi2 = FALSE;
								lpChar->MoveAngle( dist );
								lpChar->Angle.y = ang2;

								if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
									lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {
										//4% ÀÌ»ó
										if ( ((lpChar->smCharInfo.Life[1]<<2)/100)<lpTransSkilAttackData->Power ) {
											lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
										}
								}
								lpChar->lpTargetPlayInfo = 0;
								lpChar->dwNextMotionCode = CHRMOTION_STATE_STAND;
							}

						pow = ( lpTransSkilAttackData->Power * lpChar->smCharInfo.Absorption )/100;
						pow = lpTransSkilAttackData->Power-pow;

						if ( pow>0 ) {
							//¸íÁß ( °ø°Ý ¼º°ø )
							lpChar->smCharInfo.Life[0] -= pow;
						}

						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;

					}
				}
			}
		}
		break;
	case 2:	//·Î¾î
	case 5:	//½¯µå½ºÆ®¶óÀÌÅ©
		for(cnt2=0;cnt2<AUTOPLAYER_MAX;cnt2++) {
			lpChar = &chrAutoPlayer[cnt2];
			if ( lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						x = (lpPlayInfo->Position.x-lpChar->pX)>>FLOATNS;
						y = (lpPlayInfo->Position.y-lpChar->pY)>>FLOATNS;
						z = (lpPlayInfo->Position.z-lpChar->pZ)>>FLOATNS;
						if ( abs(y)>100 || (x*x+z*z)>(800*800) ) break;		//°Å¸®°¡ ¸Õ°æ¿ì ½ÇÆÐ

						//»ý¼Ó¼º ¿¡ µû¸£ Áß¸³»óÅÂ À¯Áö 
						rs = lpChar->smCharInfo.Resistance[sITEMINFO_BIONIC];
						if ( rs<0 ) rs = 0;
						if ( rs>=100 ) rs=100;
						rs = 100-rs;

						if ( lpTransSkilAttackData->AttackState==2 ) {
							//·Î¾î
							//if ( (rand()%100)>rs ) {
								lpChar->PlayStunCount = lpTransSkilAttackData->Power<<4;		//Áß¸³»óÅÂ ¼³Á¤
								lpChar->PlayStunCount = ( lpChar->PlayStunCount * rs )/100;
							//}
						}
						else if ( lpTransSkilAttackData->AttackState==5 ) {
							//½¯µå ½ºÆ®¶óÀÌÅ©
							pow = ( lpTransSkilAttackData->Power * lpChar->smCharInfo.Absorption )/100;
							pow = lpTransSkilAttackData->Power-pow;
							if ( pow>0 ) {
								//¸íÁß ( °ø°Ý ¼º°ø )
								lpChar->smCharInfo.Life[0] -= pow;
							}
							lpChar->PlayStunCount = 16*10;			//Áß¸³»óÅÂ 10ÃÊ
							lpChar->PlayStunCount = ( lpChar->PlayStunCount * rs )/100;
						}


						if ( lpChar->smCharInfo.Life[0] ) {
							//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ
							ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
							ang = (ang2+ANGLE_180) & ANGCLIP;
							lpChar->Angle.y = ang;
							lpChar->MoveAngle( 10 );
							lpChar->Angle.y = ang2;

							if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
								lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {
								lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
							}
						}

						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;
					}
				}
			}
		}
		break;
	case 3:
		//±×¶ó¿îµå ÆÄÀÌÅ©
		time = 175;
		cnt2 = lpTransSkilAttackData->AttackSize>>FLOATNS;
		for(cnt=0;cnt<10;cnt++) {
			//±×¶ó¿îµå ÆÄÀÌÅ© ½Ã°£À» Ã£´Â´Ù
			if ( G_Pike_Range[cnt]==cnt2 ) {
				time = G_Pike_Time[cnt]*17;
				break;
			}
		}

		for(cnt2=0;cnt2<AUTOPLAYER_MAX;cnt2++) {
			lpChar = &chrAutoPlayer[cnt2];
			if ( lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] ) {

						x = (lpPlayInfo->Position.x-lpChar->pX)>>FLOATNS;
						y = (lpPlayInfo->Position.y-lpChar->pY)>>FLOATNS;
						z = (lpPlayInfo->Position.z-lpChar->pZ)>>FLOATNS;
						if ( abs(y)>100 || (x*x+z*z)>(800*800) ) break;		//°Å¸®°¡ ¸Õ°æ¿ì ½ÇÆÐ

							pow = lpTransSkilAttackData->Power;
							rs = lpChar->smCharInfo.Resistance[sITEMINFO_ICE];
							if ( rs ) {
								if ( rs>=100 ) rs=100;
								if ( rs<=-100 ) rs=-100;
								pow -= ((pow*rs)/100);
							}
							pow -= ( pow * lpChar->smCharInfo.Absorption )/100;
							//pow = lpTransSkilAttackData->Power-pow;



							//int G_Pike_Time[10]	     = {3,4,5,6,7,8,9,10,11,12};


							lpChar->PlaySlowCount = time;		//¼Óµµ ´À·ÁÁü
							lpChar->PlaySlowSpeed = 0;

							if ( rs ) {
								if ( rs<0 ) rs = 0;
								lpChar->PlaySlowCount -= (rs*time)/100;
								if ( lpChar->PlaySlowCount<0 ) lpChar->PlaySlowCount = 0;
							}

							//if ( (10-rs/10)
							//10-(¸ó½ºÅÍ¼Ó¼º/10) ÃÊ

							if ( pow>0 ) {
								//¸íÁß ( °ø°Ý ¼º°ø )
								lpChar->smCharInfo.Life[0] -= pow;

								if ( lpChar->smCharInfo.Life[0] ) {
									//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ
									ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
									ang = (ang2+ANGLE_180) & ANGCLIP;
									lpChar->Angle.y = ang;
									lpChar->MoveAngle( 10 );
									lpChar->Angle.y = ang2;

									if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
										lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {
											//4% ÀÌ»ó
											if ( ((lpChar->smCharInfo.Life[1]<<2)/100)<lpTransSkilAttackData->Power ) {
												lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
											}
									}
								}
							
						}

						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;
					}
				}
			}
		}
		break;
	case 4:	//¼Ò¿ï¼­Ä¿
		if ( lpTransSkilAttackData->Power<1 || lpTransSkilAttackData->Power>10 ) break;
		TotalLife = 0;

		for(cnt2=0;cnt2<AUTOPLAYER_MAX;cnt2++) {
			lpChar = &chrAutoPlayer[cnt2];
			if ( lpChar->Flag && lpChar->smCharInfo.State && lpChar->MotionInfo->State!=CHRMOTION_STATE_DEAD ) {
				for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
			
					if ( lpChar->dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] &&
						((lpChar->smCharInfo.Life[1]*60)/100)<lpChar->smCharInfo.Life[0] ) {

						x = (lpPlayInfo->Position.x-lpChar->pX)>>FLOATNS;
						y = (lpPlayInfo->Position.y-lpChar->pY)>>FLOATNS;
						z = (lpPlayInfo->Position.z-lpChar->pZ)>>FLOATNS;
						if ( abs(y)>100 || (x*x+z*z)>(800*800) ) break;		//°Å¸®°¡ ¸Õ°æ¿ì ½ÇÆÐ

						pow = Soul_Sucker_Absorb[ lpTransSkilAttackData->Power-1 ];

						rs = lpChar->smCharInfo.Resistance[sITEMINFO_BIONIC];
						if ( rs ) {
							if ( rs>=100 ) rs=100;
							if ( rs<=-100 ) rs=-100;
							pow -= ((pow*rs)/100);
						}

						if ( pow>0 ) {
							//¸íÁß ( °ø°Ý ¼º°ø )
							life = (lpChar->smCharInfo.Life[1]*pow)/100;
							lpChar->smCharInfo.Life[0] -= life;
							if ( lpChar->smCharInfo.Life[0]<0 ) life+=lpChar->smCharInfo.Life[0];
							TotalLife += life;

							if ( lpChar->smCharInfo.Life[0] && (rand()%100)<lpChar->smMonsterInfo.DamageStunPers ) {
								//¸ÂÀ¸¸é µÚ·Î ¹°·¯³ª°Ô ÇÔ
								ang2 = GetRadian2D( lpChar->pX , lpChar->pZ ,lpPlayInfo->Position.x, lpPlayInfo->Position.z );
								ang = (ang2+ANGLE_180) & ANGCLIP;
								lpChar->Angle.y = ang;
								lpChar->MoveAngle( 10 );
								lpChar->Angle.y = ang2;

								if ( lpChar->smCharInfo.Life[0] && lpChar->MotionInfo->State != CHRMOTION_STATE_DAMAGE && 
									lpChar->MotionInfo->State!=CHRMOTION_STATE_EAT) {

										lpChar->SetMotionFromCode( CHRMOTION_STATE_DAMAGE );
								}
							}
						}

						if ( lpChar->smCharInfo.Life[0]<=0 ) {
							lpChar->SetMotionFromCode( CHRMOTION_STATE_DEAD );
							lpChar->lpExt2 = (void *)lpPlayInfo;
						}

						break;
					}
				}
			}
		}
		if ( TotalLife>0 ) {
			//»©¾ÑÀº »ý¸í·ÂÀ» º¸³»ÁØ´Ù
			smTransCommand.code = smTRANSCODE_VIRTURAL_POTION;
			smTransCommand.size = sizeof( smTRANS_COMMAND );
			smTransCommand.WParam = TotalLife;
			smTransCommand.LParam = 0;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = 0;
			if ( lpPlayInfo->lpsmSock ) 
				lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
		}
		break;


	}
*/
	return TRUE;
}


//¹üÀ§Çü °ø°Ý ¹ÞÀ½ ( À¯Àú °ø°Ý )
int RecvRangeAttackUser( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData )
{

	int cnt,cnt2;
	TRANS_ATTACKDATA	TransAttackData;

	if ( !lpPlayInfo->AdminMode ) {
		if ( !rsServerConfig.Enable_PK ) return FALSE;			//ÇöÀç ÀÏ¹ÝÀ¯Àú´Â PK±ÝÁö
		if ( lpPlayInfo->smCharInfo.Level<=LIMIT_PK_LEVEL ) return FALSE;	//·¹º§ 10ÀÌÇÏ PK±ÝÁö
	}

	if ( (lpTransSkilAttackData->AttackState&0xFFFF)==2 ) //·Î¾î PK°ø°Ý ÇØ´ç ¾øÀ½
		return FALSE;


	for( cnt2=0;cnt2<CONNECTMAX;cnt2++ ) {
		if ( rsPlayInfo[cnt2].lpsmSock && rsPlayInfo[cnt2].dwObjectSerial ) {
			for( cnt=0;cnt<lpTransSkilAttackData->TargetCount;cnt++) {
				if ( rsPlayInfo[cnt2].dwObjectSerial==lpTransSkilAttackData->dwTarObjectSerial[cnt] &&
					rsPlayInfo[cnt2].smCharInfo.Level>LIMIT_PK_LEVEL ) {


					TransAttackData.code = smTRANSCODE_ATTACKDATA;
					TransAttackData.size = sizeof(TRANS_ATTACKDATA);

					TransAttackData.x = rsPlayInfo[cnt2].Position.x;
					TransAttackData.y = rsPlayInfo[cnt2].Position.y;
					TransAttackData.z = rsPlayInfo[cnt2].Position.z;


					TransAttackData.AttackState = 1;
					TransAttackData.AttackSize  = 32*fONE;
					TransAttackData.Power		= lpTransSkilAttackData->Power;

					TransAttackData.dwDestObjectSerial = lpPlayInfo->dwObjectSerial;
					TransAttackData.dwTarObjectSerial = rsPlayInfo[cnt2].dwObjectSerial;
					TransAttackData.dwChkSum = TransAttackData.Power*2002 + 
						(TransAttackData.x * TransAttackData.y * TransAttackData.z);// Á¶ÀÛ ¹æÁö ÄÚµå

					//°ø°Ý ±â·Ï
					rsPlayInfo[cnt2].Send_AttackCount++;
					rsPlayInfo[cnt2].Send_AttackDamage += lpTransSkilAttackData->Power;

					rsPlayInfo[cnt2].lpsmSock->Send2( (char *)&TransAttackData , TransAttackData.size , TRUE );

					break;
				}
			}
		}
	}

	return TRUE;
}


///////////////////////////// »õ·Î¿î °ø°Ý ÆÐÅ¶ //////////////////////////////////


//·¹º§·Î Á¤»óÀûÀÎ ½ºÅ³ ÄÚµåÀÎÁö °Ë»ç
int rsCheckSkillLevel( rsPLAYINFO *lpPlayInfo , DWORD dwSkillCode )
{
	DWORD	dwCode = dwSkillCode&0xFF;
	DWORD	dwCodeByte = dwSkillCode&0xF;
	int		lv = lpPlayInfo->smCharInfo.Level;

	if ( dwCode>=0xC0 ) return TRUE;

	if ( dwSkillCode==SKILL_PLAY_PIKEWIND || dwSkillCode==SKILL_PLAY_ENCHANT_WEAPON ) return TRUE;

	if ( dwCodeByte==0 || dwCodeByte>=0xD ) {
		//4Â÷½ºÅ³
		if ( lv<59 ) return FALSE;
	}
	else if ( dwCodeByte>=9 ) {
		//3Â÷ ½ºÅ³
		if ( lv<39 ) return FALSE;
	}
	else if ( dwCodeByte>=5 ) {
		//2Â÷ ½ºÅ³
		if ( lv<19 ) return FALSE;
	}
	else if ( dwCodeByte>=1 ) {
		//1Â÷ ½ºÅ³
		if ( lv<9 ) return FALSE;
	}

	return TRUE;
}



//½ºÅ³ °ø°Ý º¯È¯
int rsSetSkillAttack( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , TRANS_ATTACKDATA *lpTransAttackData , TRANS_ATTACKDATA2 *lpTransAttackData2 ) 
{
	DWORD	dwSkillCode;
	int		Point;
	int		Param;
	int		pow,pow1,pow2;
	int		power[2];
	int		cnt;
	smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	TransCommandEx;


	dwSkillCode = lpTransAttackData2->SkillCode&0xFF;
	Point = ((lpTransAttackData2->SkillCode>>8)&0xF)-1;
	Param = (lpTransAttackData2->SkillCode>>12)&0xF;

	if ( Point<0 || Point>=10 ) return FALSE;

	dm_SkillCode_Temp = dwSkillCode;

	//·¹º§·Î Á¤»óÀûÀÎ ½ºÅ³ ÄÚµåÀÎÁö °Ë»ç
	if ( rsCheckSkillLevel( lpPlayInfo , dwSkillCode )==FALSE ) {
		if ( lpPlayInfo->WarningCount<5 ) {
			//¿À·ù ·Î±× ³²±â±â
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.WParam = 8850;
			smTransCommand.LParam = lpPlayInfo->smCharInfo.Level;
			smTransCommand.SParam = dwSkillCode;
			smTransCommand.EParam = Point;
			rsSendDataServer( lpPlayInfo->lpsmSock , &smTransCommand );
			lpPlayInfo->WarningCount++;
		}
		return FALSE;
	}

	switch( dwSkillCode ) {
		case SKILL_PLAY_RAVING:					//·¹ÀÌºù
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;	//ÆÄÀÌÅÍ Àü¿ë

			lpTransAttackData->Power += (lpTransAttackData->Power*Raving_Damage[Point])/100;
			lpTransAttackData->AttackState = (lpTransAttackData->AttackState&0xFFFF0000)+2;		//Å©¸®Æ¼ÄÃ Ã³¸®
			break;

		case SKILL_PLAY_IMPACT:					//ÀÓÆÑÆ®
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;	//ÆÄÀÌÅÍ Àü¿ë

			lpTransAttackData->Power += (lpTransAttackData->Power*Impact_Damage[Point])/100;
			lpTransAttackData->AttackState = (lpTransAttackData->AttackState&0xFFFF0000)+2;		//Å©¸®Æ¼ÄÃ Ã³¸®
			//lpTransAttackData2->Critical[0] = 0;
			break;

		case SKILL_PLAY_CRITICAL_HIT:			//Å©¸®Æ¼ÄÃ Èý
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;	//ÆÄÀÌÅ©¸Ç Àü¿ë

			lpTransAttackData2->Critical[0] += Critical_Hit_Critical[Point];
			break;

		case SKILL_PLAY_JUMPING_CRASH:			//Á¡ÇÎ Å¬·¡½Ã
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;	//ÆÄÀÌÅ©¸Ç Àü¿ë

			lpTransAttackData->AttackState = (lpTransAttackData->AttackState&0xFFFF0000)+2;		//Å©¸®Æ¼ÄÃ Ã³¸®
			lpTransAttackData->Power += (lpTransAttackData->Power*Jumping_Crash_Damage[Point])/100;

			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_DEMON ) {
				// µð¸Õ ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡
				lpTransAttackData->Power += (lpTransAttackData->Power*30)/100;
			}
			break;

		case SKILL_PLAY_WIND_ARROW:				//À©µå ¾Ö·Î¿ì
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ARCHER ) return FALSE;	//¾ÆÃÄ Àü¿ë

			lpTransAttackData->Power += (lpTransAttackData->Power*Wind_Arrow_Damage[Point])/100;

			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_NORMAL ) {
				// ³ë¸» ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡
				lpTransAttackData->Power += (lpTransAttackData->Power*30)/100;
			}
			break;

		case SKILL_PLAY_PERFECT_AIM:			//ÆäÆåÆ® ¿¡ÀÓ
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ARCHER ) return FALSE;	//¾ÆÃÄ Àü¿ë

			lpTransAttackData->Power += Perfect_Aim_Damage[Point];
			lpTransAttackData->Power += lpPlayInfo->smCharInfo.Level/Perfect_Aim_Damage_LV[Point];

			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_DEMON ) {
				// µð¸Õ ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡
				lpTransAttackData->Power += (lpTransAttackData->Power*30)/100;
			}
			break;

		case SKILL_PLAY_AVALANCHE:				//¿¡¹ú·±Ã÷
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ARCHER ) return FALSE;	//¾ÆÃÄ Àü¿ë

			lpTransAttackData->Power += (lpTransAttackData->Power*Avalanche_Damage[Point])/100;
			lpTransAttackData2->Critical[0] >>=1;		//¿¡¹ú·±Ã÷ ÀÏ¶§ Å©¸®Æ¼ÄÃ Àý¹ÝÈ®·ü
			break;

		case SKILL_PLAY_TRIPLE_IMPACT:			//Æ®¸®ÇÃ ÀÓÆÑÆ®
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;	//ÆÄÀÌÅÍ Àü¿ë

			lpTransAttackData->Power += (lpTransAttackData->Power*T_Impact_Damage[Point])/100;
			if ( lpTransAttackData2->MotionCount[0]==2 ) {
				lpTransAttackData->AttackState = (lpTransAttackData->AttackState&0xFFFF0000)+2;		//Å©¸®Æ¼ÄÃ Ã³¸®
				lpTransAttackData2->Critical[0] = 0;
			}
			break;

		case SKILL_PLAY_BRUTAL_SWING:			//ºÎ¸£Å» ½ºÀ®
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;	//ÆÄÀÌÅÍ Àü¿ë

			lpTransAttackData->Power += (lpTransAttackData->Power*B_Swing_Damage[Point])/100;
			lpTransAttackData2->Critical[0] += (lpTransAttackData2->Critical[0]*B_Swing_Critical[Point])/100;

			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_DEMON ) {
				//ºÎ·çÅ» ½ºÀ® ( µð¸Õ ¸ó½ºÅÍ¿¡°Ô 40% Ãß°¡ )
				lpTransAttackData->Power += (lpTransAttackData->Power*40)/100;
			}
			break;

		case SKILL_PLAY_RAGEOF_ZECRAM:			//Á¦Å©¶÷
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;	//ÆÄÀÌÅÍ Àü¿ë

			lpTransAttackData->Power += (lpTransAttackData->Power*R_Zecram_Damage[Point])/100;
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE+1)<<16;		//ºÒ ¼Ó¼º
			break;

		case SKILL_PLAY_DOUBLE_CRASH:			//´õºí Å©·¡½Ã
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_KNIGHT ) return FALSE;	//³ªÀÌÆ® Àü¿ë

			lpTransAttackData->Power += (lpTransAttackData->Power*D_Crash_Damage[Point])/100;
			lpTransAttackData2->Critical[0] += D_Crash_Critical[Point];		//¿ø·¡²¨¶û Á» Æ²¸² ( ¿ø·¡²¨´Â Å©¸®Æ¼ÄÃ ¼öÄ¡»êÃâÈÄ Ãß°¡ )
			break;

		case SKILL_PLAY_FARINA:					//ÆÐ¸®³ª
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;	//¾ÆÅ»¶õÅ¸ Àü¿ë

			 break;

		case SKILL_PLAY_VIGOR_SPEAR:			//ºñ°Å½ºÇÇ¾î
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;	//¾ÆÅ»¶õÅ¸ Àü¿ë

			lpTransAttackData->Power += GetRandomPos( V_Spear_Damage[Point][0] , V_Spear_Damage[Point][1] );
			lpTransAttackData->Power += lpPlayInfo->smCharInfo.Level/2;
			break;

		case SKILL_PLAY_TWIST_JAVELIN:			//Æ®À§½ºÆ® Àçºí¸°
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;	//¾ÆÅ»¶õÅ¸ Àü¿ë

			lpTransAttackData->Power += (lpTransAttackData->Power*Twist_Javelin_Damage[Point])/100;

			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_DEMON ) {
				//µð¸Õ ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡
				lpTransAttackData->Power += (lpTransAttackData->Power*30)/100;
			}
			break;

		case SKILL_PLAY_FIRE_JAVELIN:			//ÆÄÀÌ¾î Àçºí¸°
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;	//¾ÆÅ»¶õÅ¸ Àü¿ë

			pow = GetRandomPos( Fire_Javelin_Damage[Point][0],Fire_Javelin_Damage[Point][1] );
			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_MUTANT ) {
				//¹ÂÅÏÆ® ¸ó½ºÅÍ¿¡°Ô ºÒ¼Ó¼º 50% Ãß°¡
				pow += (pow*50)/100;
			}

			lpTransAttackData->AttackState |= (sITEMINFO_FIRE+1)<<16;		//ºÒ ¼Ó¼º
			lpTransAttackData->AttackState |= pow<<(16+4);					//ÀüÃ¼Áß ºÒ¼Ó¼º µ¥¹ÌÁö
			lpTransAttackData->Power += pow;								//ÀüÃ¼ µ¥¹ÌÁö
			lpTransAttackData->Power += lpPlayInfo->smCharInfo.Level/3;
			break;

		case SKILL_PLAY_HOLY_BOLT:				//È¦¸® º¼Æ®
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PRIESTESS || !lpChar ) return FALSE;	//ÇÁ¸®½ºÆ¼½º Àü¿ë

			power[0] = HolyBolt_Damage[Point][0];// + lpTransAttackData2->Critical[1]/8;
			power[1] = HolyBolt_Damage[Point][1];// + lpTransAttackData2->Critical[1]/4;

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			power[0]+=lpTransAttackData2->Power2[0]/3; // ¹«¹Î/3
			power[1]+=lpTransAttackData2->Power2[1]/3; // ¹«¸Æ/3
			power[0]+=lpTransAttackData2->Critical[1]/8; // Á¤½Å/8
			power[1]+=lpTransAttackData2->Critical[1]/6; // Á¤½Å/6

			pow = GetRandomPos( power[0] , power[1] );

			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD )	pow <<=1;  //¾ðµ¥µå µ¥¹ÌÁö °¡Áß
			lpTransAttackData->Power = pow;
			lpTransAttackData2->Critical[0] = 0;
			break;

		case SKILL_PLAY_MULTI_SPARK:			//¸ÖÆ¼ ½ºÆÄÅ©
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PRIESTESS ) return FALSE;	//ÇÁ¸®½ºÆ¼½º Àü¿ë

		//	pow1 = M_Spark_Damage[Point][0]+lpTransAttackData2->Power2[0];//+(lpTransAttackData2->Critical[1]/8);
		//	pow2 = M_Spark_Damage[Point][1]+lpTransAttackData2->Power2[1];//+(lpTransAttackData2->Critical[1]/4);

			 // Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			pow1 = M_Spark_Damage[Point][0] + (lpTransAttackData2->Critical[1]/8) + (lpTransAttackData2->Power2[0]/3);
			pow2 = M_Spark_Damage[Point][1] + (lpTransAttackData2->Critical[1]/6) + (lpTransAttackData2->Power2[1]/3);

			pow = GetRandomPos( pow1 , pow2 );
			pow *= Param;
			lpTransAttackData->Power = pow;
			lpTransAttackData2->Critical[0] = 0;
			break;

		case SKILL_PLAY_FIRE_BOLT:					//ÆÄÀÌ¾î º¼Æ®
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MAGICIAN ) return FALSE;	//¸ÅÁö¼Ç Àü¿ë

			power[0] = FireBolt_Damage[Point][0];//+lpTransAttackData2->Critical[1]/8;
			power[1] = FireBolt_Damage[Point][1];//+lpTransAttackData2->Critical[1]/4;

			if ( lpPlayInfo->dwSkill_SpiritElemental_Time ) {		//½ºÇÇ¸´¿¤¸®¸àÅ» µ¥¹ÌÁö °¡Áß
				if ( lpPlayInfo->dwSkill_SpiritElemental_Time>dwPlayServTime ) {
					power[0]+=(power[0]*lpPlayInfo->dwSkill_SpiritElemental_Param)/100;
					power[1]+=(power[1]*lpPlayInfo->dwSkill_SpiritElemental_Param)/100;
				}
				else {
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			power[0]+= lpTransAttackData2->Power2[0]/3; // ¹«¹Î/3
			power[1]+= lpTransAttackData2->Power2[1]/3; // ¹«¸Æ/3
			
			power[0] += lpTransAttackData2->Critical[1]/8; // Á¤½Å/8
			power[1] += lpTransAttackData2->Critical[1]/6; // Á¤½Å/6

			pow = GetRandomPos( power[0] , power[1] );
			lpTransAttackData->Power = pow;


			lpTransAttackData->AttackState |= (sITEMINFO_FIRE+1)<<16;		//ºÒ ¼Ó¼º
			lpTransAttackData2->Critical[0] = 0;
			break;

		case SKILL_PLAY_DEAD_RAY:				//µ¥¾²·¹ÀÌ
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MAGICIAN ) return FALSE;	//¸ÅÁö¼Ç Àü¿ë

			pow1 = Dead_Ray_Damage[Point][0];
			pow2 = Dead_Ray_Damage[Point][1];

			if ( lpPlayInfo->dwSkill_SpiritElemental_Time ) {		//½ºÇÇ¸´¿¤¸®¸àÅ» µ¥¹ÌÁö °¡Áß
				if ( lpPlayInfo->dwSkill_SpiritElemental_Time>dwPlayServTime ) {
					pow1+=(pow1*lpPlayInfo->dwSkill_SpiritElemental_Param)/100;
					pow2+=(pow2*lpPlayInfo->dwSkill_SpiritElemental_Param)/100;
				}
				else {
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}

			/*

			pow1 += lpTransAttackData2->Critical[1]/8;
			pow2 += lpTransAttackData2->Critical[1]/4;

			pow1 += lpTransAttackData2->Power2[0];
			pow2 += lpTransAttackData2->Power2[1];
			*/

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			pow1 += lpTransAttackData2->Power2[0];  // ¹«¹Î
			pow2 += lpTransAttackData2->Power2[1];  // ¹«¸Æ
			
			pow1 += lpPlayInfo->smCharInfo.Level/2;   // Lv/2
			pow2 += lpPlayInfo->smCharInfo.Level/2;   // Lv/2

			pow1 +=lpTransAttackData2->Critical[1]/4;  // Á¤½Å/4
			pow2 +=lpTransAttackData2->Critical[1]/2;  // Á¤½Å/2



			lpTransAttackData->Power = GetRandomPos( pow1, pow2 );

			lpTransAttackData->AttackState |= (sITEMINFO_NONE)<<16;			//¹«¼Ó¼º
			lpTransAttackData2->Critical[0] = 0;
			break;

		case SKILL_PLAY_FALCON:					//ÆÈÄÜ
			if ( lpPlayInfo->smCharInfo.JOB_CODE==JOBCODE_ARCHER ) {
				//¾ÆÃÄ Àü¿ë
				if ( !lpPlayInfo->dwSKill_Falcon_Time || lpPlayInfo->dwSKill_Falcon_Time<dwPlayServTime ) {
					lpPlayInfo->dwSKill_Falcon_Time = 0;
					return FALSE;
				}

				lpTransAttackData->Power = GetRandomPos( lpPlayInfo->dwSKill_Falcon_Damage[0] , lpPlayInfo->dwSKill_Falcon_Damage[1] );
				lpTransAttackData2->Critical[0] = 0;

				//Æ÷½º¿Àºê ³×ÀÌÃÄ
				if ( lpPlayInfo->dwSkill_ForceOfNature_Time ) {
					if ( lpPlayInfo->dwSkill_ForceOfNature_Time<dwPlayServTime ) {
						lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
					}
					else {
						lpTransAttackData->Power += lpPlayInfo->wSkill_ForceOfNature_Param[1];
					}
				}
				break;
			}
			return FALSE;

		case SKILL_PLAY_DANCING_SWORD:				//´í½Ì¼Òµå
			if ( lpPlayInfo->smCharInfo.JOB_CODE==JOBCODE_MAGICIAN ) {
				//¸ÞÁö¼Ç ´í½Ì¼Òµå
				if ( !lpPlayInfo->dwSkill_DancingSword_Time || lpPlayInfo->dwSkill_DancingSword_Time<dwPlayServTime ) {
					lpPlayInfo->dwSkill_DancingSword_Time = 0;
					lpPlayInfo->dwSkill_DancingSword_Param = 0;
					return FALSE;
				}

				pow1 = lpPlayInfo->dwSkill_DancingSword_Param>>16;		//½ºÅ³Æ÷ÀÎÆ®

				if ( lpPlayInfo->dwSkill_DancingSword_DelayTime ) {
					if ( lpPlayInfo->dwSkill_DancingSword_DelayTime>(lpTransAttackData2->dwTime+1000) ) {
						//µô·¹ÀÌ ½Ã°£ ¿À·ù
						return FALSE;
					}
				}
				//´ÙÀ½ ÃÖ¼Ò °ø°Ý¿¹Á¤ ½Ã°£ µî·Ï 
				lpPlayInfo->dwSkill_DancingSword_DelayTime = lpTransAttackData2->dwTime+Dancing_Sword_AttackDelay[pow1]*900;

				if ( lpTransAttackData2->Power[0]<lpTransAttackData2->Power2[0] || lpTransAttackData2->Power[1]<lpTransAttackData2->Power2[1] ) {
					//¹«±âµ¥¹ÌÁö ¿À·ù
					return FALSE;
				}

				if ( (lpPlayInfo->dwSkill_DancingSword_Param&0xFF)==0 ) //¾óÀ½
				{ 
					// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
					lpTransAttackData->Power = GetRandomPos(
						Dancing_Sword_IceDamage[pow1][0] + (lpTransAttackData2->Power2[0]/3) + (lpTransAttackData2->Critical[1]/8),
						Dancing_Sword_IceDamage[pow1][1] + (lpTransAttackData2->Power2[1]/3) + (lpTransAttackData2->Critical[1]/6) );

					lpTransAttackData2->Critical[0] = 0;
					lpTransAttackData->AttackState |= (sITEMINFO_ICE+1)<<16;
				}
				else 	//ºÒ
				{
					// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
					lpTransAttackData->Power = GetRandomPos(
						Dancing_Sword_FireDamage[pow1][0] + (lpTransAttackData2->Power2[0]/3) + (lpTransAttackData2->Critical[1]/8),
						Dancing_Sword_FireDamage[pow1][1] + (lpTransAttackData2->Power2[1]/3) + (lpTransAttackData2->Critical[1]/6) );

					lpTransAttackData2->Critical[0] = 0;
					lpTransAttackData->AttackState |= (sITEMINFO_FIRE+1)<<16;
				}
				break;
			}
			return FALSE;


		case SKILL_PLAY_HEALING:				//Èú¸µ
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PRIESTESS ) return FALSE;	//ÇÁ¸®½ºÆ¼½º Àü¿ë

			if ( lpPlayInfo->sLimitDamage[0]<lpTransAttackData2->Power2[0] || lpPlayInfo->sLimitDamage[1]<lpTransAttackData2->Power2[1] ) {
				//¹«±âµ¥¹ÌÁö ¿À·ù
				return FALSE;
			}

			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_HEALING;
			/*
			smTransCommand.WParam =	GetRandomPos( 
				Healing_Heal[Point][0]+lpTransAttackData2->Power2[0]+(lpTransAttackData2->Critical[1]/8),
				Healing_Heal[Point][1]+lpTransAttackData2->Power2[1]+(lpTransAttackData2->Critical[1]/4) );	//»ý¸í·Â
				*/

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			smTransCommand.WParam =	GetRandomPos( 
				Healing_Heal[Point][0]+(lpTransAttackData2->Power2[0]/3)+(lpTransAttackData2->Critical[1]/8),
				Healing_Heal[Point][1]+(lpTransAttackData2->Power2[1]/3)+(lpTransAttackData2->Critical[1]/6) );	//»ý¸í·Â

			smTransCommand.LParam =	0;								//
			smTransCommand.SParam =	lpTransAttackData2->dwTarObjectSerial;			//Ä¡·á ´ë»ó
			smTransCommand.EParam = lpPlayInfo->dwObjectSerial;	//
			rsPlayHealing( &smTransCommand );									//Èú¸µ½ÇÇàÇÔ¼ö
			return FALSE;



		case SKILL_PLAY_GREAT_HEALING:			//±×·£µå Èú¸µ
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PRIESTESS ) return FALSE;	//ÇÁ¸®½ºÆ¼½º Àü¿ë

			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_GRAND_HEALING;
			smTransCommand.WParam =	Point+1;					//½ºÅ³Æ÷ÀÎÆ®

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			smTransCommand.LParam =	GetRandomPos( 
				Grand_Healing[Point][0] + (lpTransAttackData2->Critical[1]/8) + (lpTransAttackData2->Power2[0]/3) , 
				Grand_Healing[Point][1] + (lpTransAttackData2->Critical[1]/6) + (lpTransAttackData2->Power2[1]/3) );

			/*
			smTransCommand.LParam =	GetRandomPos( 
				Grand_Healing[Point][0]+lpTransAttackData2->Power2[0]+(lpTransAttackData2->Critical[1]/8) , 
				Grand_Healing[Point][1]+lpTransAttackData2->Power2[1]+(lpTransAttackData2->Critical[1]/4) );
				*/

			smTransCommand.SParam =	Grand_Healing_Range[Point];
			smTransCommand.EParam = lpPlayInfo->dwObjectSerial;
			rsPlayGrandHealing( lpPlayInfo , &smTransCommand );
			return FALSE;


		case SKILL_PLAY_SPARK_SHIELD:		//½ºÆÄÅ©½¯µå
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MECHANICIAN ) return FALSE;	//¸ÞÄ«´Ï¼Ç
			if ( !lpChar || !lpPlayInfo->dwSkill_SparkShield_Time || lpPlayInfo->dwSkill_SparkShield_Time<dwPlayServTime ) {
				//½ºÆÄÅ© ½¯µå ½ÃÀü Á¾·á
				lpPlayInfo->dwSkill_SparkShield_Time = 0;
				return FALSE;
			}

			pow1 = lpPlayInfo->dwSkill_SparkShield_Param>>16;
			pow2 = lpPlayInfo->dwSkill_SparkShield_Param&0xFFFF;
			pow = GetRandomPos(pow1,pow2);
			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_MECHANIC ) {
				//¸ÞÄ«´Ð ¸ó½ºÅÍ¿¡°Ô ·Ú¼Ó¼º 50% Ãß°¡
				pow += (pow*50)/100;
			}

			lpTransAttackData->AttackState |= (sITEMINFO_LIGHTING+1)<<16;		//·Ú ¼Ó¼º
			lpTransAttackData->Power = pow;										//ÀüÃ¼ µ¥¹ÌÁö
			lpTransAttackData2->Critical[0] = 0;

			smTransCommand.code = smTRANSCODE_PROCESS_SKILL;;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = SKILL_PLAY_SPARK_SHIELD;
			smTransCommand.LParam = lpPlayInfo->dwObjectSerial;
			smTransCommand.SParam = lpChar->dwObjectSerial;
			rsSendCommandUser2( lpPlayInfo , &smTransCommand );
			break;

		case SKILL_PLAY_GRAND_SMASH:		//±×·£µå ½º¸Å½¬
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MECHANICIAN ) return FALSE;	//¸ÞÄ«´Ï¼Ç
			lpTransAttackData->Power += (lpTransAttackData->Power*Grand_Smash_Damage[Point])/100;
			break;

		case SKILL_PLAY_AVANGING_CRASH:		//¾î¹êÂ¡ Å©·¡½¬
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;		//ÆÄÀÌÅÍ
			lpTransAttackData->Power += (lpTransAttackData->Power*A_Crash_Damage[Point])/100;
			if ( lpTransAttackData2->Power2[0]>0 && lpTransAttackData2->Power2[0]<=10 ) {
				lpTransAttackData2->Critical[0] += B_Swing_Critical[ lpTransAttackData2->Power2[0] ]/2;
			}
			break;

		case SKILL_PLAY_BONE_SMASH:			//º» ½º¸Å½¬
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;		//ÆÄÀÌÅÍ

			lpTransAttackData->Power += (lpTransAttackData->Power*B_Crash_Damage[Point])/100;

			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_DEMON ) {
				//µð¸Õ
				lpTransAttackData->Power += (lpTransAttackData->Power*B_Crash_DemonDamage[Point])/100;
			}
			break;

		case SKILL_PLAY_CHAIN_LANCE:		//Ã¼ÀÎ·»½º
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;	//ÆÄÀÌÅ©¸Ç Àü¿ë
			lpTransAttackData->Power += (lpTransAttackData->Power*Chain_Lance_Damage[Point])/100;
			break;


		case SKILL_PLAY_ELEMENTAL_SHOT:		//¿¤¸®¸àÅ»¼¦ 
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ARCHER ) return FALSE;	//¾ÆÃÄ Àü¿ë
			if ( Param==0 ) {	//ºÒ
				lpTransAttackData2->Critical[0] = 0;
				pow = GetRandomPos( Elemental_Shot_Fire[Point][0], Elemental_Shot_Fire[Point][1] );
				lpTransAttackData->Power += pow;
				lpTransAttackData->AttackState |= (sITEMINFO_FIRE+1)<<16;		//ºÒ ¼Ó¼º
				lpTransAttackData->AttackState |= pow<<(16+4);					//ÀüÃ¼Áß ºÒ¼Ó¼º µ¥¹ÌÁö
			}
			break;


		case SKILL_PLAY_HOLY_INCANTATION:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_KNIGHT ) return FALSE;	//³ªÀÌÆ® Àü¿ë
			//¸î°¡Áö Ãß°¡¿¹Á¤
			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD ) {

				pow = lpChar->smCharInfo.Resistance[sITEMINFO_BIONIC];		//»ý ¼Ó¼º Àû¿ë
				if ( pow<0 ) pow=0;
				if ( pow>100 ) pow=100;
				pow = 100-pow;

				pow = (H_Incantation_Success[Point]*pow)/100;
				if ( (rand()%100)<pow ) {
					lpChar->lpMasterPlayInfo = lpPlayInfo;
					lpChar->smMonsterInfo.dwAutoCharCode = 0;
					lpChar->smCharInfo.bUpdateInfo[0]++;
					lpChar->PlayHolyIncantation[0] = (short)lpChar->smCharInfo.Brood;
					lpChar->PlayHolyIncantation[1] = H_Incantation_Time[Point]*17;

					//lpChar->smCharInfo.Life[0] = (lpChar->smCharInfo.Life[0]*H_Incantation_AddLife[Point])/100;
					//if ( lpChar->smCharInfo.Life[0]>lpChar->smCharInfo.Life[1] ) lpChar->smCharInfo.Life[0]=lpChar->smCharInfo.Life[1];
			//		lpChar->smCharInfo.Life[0]=lpChar->smCharInfo.Life[1]; // Àåº° - ±âÁ¸ ¼Ò½º

					// Àåº° - È¦¸® ÀÎÄËÅ×ÀÌ¼Ç ¼öÁ¤
					lpChar->smCharInfo.Life[0] = lpChar->smCharInfo.Life[1] = (lpChar->smCharInfo.Life[0]*H_Incantation_AddLife[Point])/100;



					lpChar->smCharInfo.Next_Exp = lpPlayInfo->dwObjectSerial;		//ÁÖÀÎ ½Ã¸®¾ó ÄÚµå ÀúÀå
					lpChar->smCharInfo.Brood = smCHAR_MONSTER_USER;
					lstrcpy( lpChar->smCharInfo.szModelName2+1 , lpPlayInfo->smCharInfo.szName );	//ÁÖÀÎ ÀÌ¸§
					lpChar->lpTargetChar = 0;
					lpChar->lpTargetPlayInfo = 0;

					//¸ó½ºÅÍ ÇöÈ¤µÈ ÀÌÆåÆ® È£Ãâ
					ZeroMemory( &TransCommandEx , sizeof(smTRANS_COMMAND_EX) );
					TransCommandEx.WParam = smCOMMNAD_USER_HOLY_INCANTATION;
					TransCommandEx.LParam = lpChar->dwObjectSerial;
					TransCommandEx.SParam = H_Incantation_Time[Point];
					TransCommandEx.EParam = 0;
					rsSendCommandUser( lpPlayInfo , &TransCommandEx );			//ÀÌÆåÆ® È£Ãâ
				}
			}
			return FALSE;

		case SKILL_PLAY_GRAND_CROSS:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_KNIGHT ) return FALSE;		//³ªÀÌÆ® Àü¿ë

			lpTransAttackData->Power += (lpTransAttackData->Power*Grand_Cross_Damage[Point])/100;

			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD ) {
				//¾ðµ¥µå
				lpTransAttackData->Power += (lpTransAttackData->Power*Grand_Cross_UndeadDamage[Point])/100;
			}
			break;

		case SKILL_PLAY_SPLIT_JAVELIN:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;		//¾ÆÅ»¶õÅ¸ Àü¿ë
			if ( lpTransAttackData2->Power2[0]>Split_Javelin_AttackNum[Point] ) return FALSE;

			lpTransAttackData->Power = 0;

			//¹ß»çÇÑ °¹¼ö¸¸Å­ °ø°Ý·Â °è»ê
			for(cnt=0;cnt<lpTransAttackData2->Power2[0];cnt++) {
				pow = GetRandomPos( lpTransAttackData2->Power[0] , lpTransAttackData2->Power[1] );
				pow += (pow*Split_Javelin_Damage[Point])/100;
				lpTransAttackData->Power += pow;
			}
			lpTransAttackData2->Critical[0] = 0;		//Å©¸®Æ¼ÄÃ ÆÇÁ¤ ¾øÀ½
			break;

		case SKILL_PLAY_VIGOR_BALL:		//ºñ°Åº¼
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PRIESTESS || !lpChar ) return FALSE;	//ÇÁ¸®½ºÆ¼½º Àü¿ë

			if ( lpTransAttackData2->Power[0]>lpTransAttackData2->Power2[0] && lpTransAttackData2->Power[1]>lpTransAttackData2->Power2[1] ) {

				/*
				pow1 = lpTransAttackData2->Power2[0]+Vigor_Ball_Damage[Point][0]+(lpTransAttackData2->Critical[1]/8);
				pow2 = lpTransAttackData2->Power2[1]+Vigor_Ball_Damage[Point][1]+(lpTransAttackData2->Critical[1]/8);
				*/

				// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
				pow1 = Vigor_Ball_Damage[Point][0] + (lpPlayInfo->smCharInfo.Level/2) + (lpTransAttackData2->Critical[1]/6);
				pow2 = Vigor_Ball_Damage[Point][1] + (lpPlayInfo->smCharInfo.Level/2) + (lpTransAttackData2->Critical[1]/3);


				lpTransAttackData->Power = GetRandomPos( pow1, pow2 );
				lpTransAttackData2->Critical[0] = 0;		//Å©¸®Æ¼ÄÃ ÆÇÁ¤ ¾øÀ½
				break;
			}
			return FALSE;

		case SKILL_PLAY_PET_ATTACK:
			//Æê¿¡ ÀÇÇÑ °ø°Ý

			//¹ÚÀç¿ø - ºô¸µ µµ¿ì¹Ì Æê
			//	if ( lpPlayInfo->smCharInfo.Level>10 ) return FALSE;		//·¹º§ 10±îÁö¸¸

			pow1 =0;
			pow2 =0;

			switch( Point ) 
			{
			case PET_TERRY:
				//	pow1 = 2 + lpPlayInfo->smCharInfo.Level/3;
				//	pow2 = 5 + lpPlayInfo->smCharInfo.Level/3;
				// Àåº° - ºô¸µ µµ¿ì¹Ì Æê µ¥¹ÌÁö ¼öÁ¤
				pow1 = lpPlayInfo->smCharInfo.Level / 2;
				pow2 = (lpPlayInfo->smCharInfo.Level * 95)/100;
				lpTransAttackData->AttackState |= (sITEMINFO_FIRE+1)<<16;
				break;

			case PET_NEPSYS:
				//	pow1 = 1;
				//	pow2 = 2;
				// Àåº° - ºô¸µ µµ¿ì¹Ì Æê µ¥¹ÌÁö ¼öÁ¤
				pow1 = lpPlayInfo->smCharInfo.Level / 2;
				pow2 = (lpPlayInfo->smCharInfo.Level * 95)/100;
				lpTransAttackData->AttackState |= (sITEMINFO_ICE+1)<<16;
				break;

			case PET_IO:
				//	pow1 = 1;
				//	pow2 = 6 + lpPlayInfo->smCharInfo.Level/2;
				// Àåº° - ºô¸µ µµ¿ì¹Ì Æê µ¥¹ÌÁö ¼öÁ¤
				pow1 = (lpPlayInfo->smCharInfo.Level * 80)/100 + 1;
				pow2 = lpPlayInfo->smCharInfo.Level + (lpPlayInfo->smCharInfo.Level * 80)/100 + 2;
				break;

			// Àåº° - ¿»·Î¿ì µå·¡°ï
			case PET_MUTE:
				//	pow1 = 1;
				//	pow2 = 6 + lpPlayInfo->smCharInfo.Level/2;
				// Àåº° - ºô¸µ µµ¿ì¹Ì Æê µ¥¹ÌÁö ¼öÁ¤
				pow1 = (lpPlayInfo->smCharInfo.Level)/2;
				pow2 = lpPlayInfo->smCharInfo.Level + (lpPlayInfo->smCharInfo.Level * 95)/100 ;
			break;
			}
			
			// ¹ÚÀç¿ø - ºô¸µ µµ¿ì¹Ì Æê °ø°Ý µ¥¹ÌÁö 2¹è·Î ¼³Á¤
		//	pow1 = 1 + (lpPlayInfo->smCharInfo.Level*80)/100;
		//	pow2 = 2 + (lpPlayInfo->smCharInfo.Level) + (lpPlayInfo->smCharInfo.Level*80)/100;

			lpTransAttackData->Power = GetRandomPos( pow1, pow2 );
			lpTransAttackData2->Critical[0] = 0;		//Å©¸®Æ¼ÄÃ ÆÇÁ¤ ¾øÀ½
			break;

		case SKILL_PLAY_PET_ATTACK2:
			//PC¹æ ÆÖ °ø°Ý

			//if ( !lpPlayInfo->Bl_RNo || (dwPlayServTime-lpPlayInfo->dwPCBang_Pet_AttackTime)<1000 ) return FALSE;		//1ÃÊ °£°Ý µô·¹ÀÌ À¯Áö
			
			// pluto Æê(ÇØ¿Ü) ¼öÁ¤
			if ( !lpPlayInfo->dwTime_PrimeItem_PhenixPet || (dwPlayServTime-lpPlayInfo->dwPCBang_Pet_AttackTime)<1000 ) return FALSE;		//1ÃÊ °£°Ý µô·¹ÀÌ À¯Áö

			lpPlayInfo->dwPCBang_Pet_AttackTime = dwPlayServTime;

			pow1 =0;
			pow2 =0;

			switch( Point ) {
				case PCBANG_PET_BURSTP:
				case PCBANG_PET_BURSTS:
				case PCBANG_PET_BURSTL:
				case PCBANG_PET_BURSTD:
					pow1 = lpPlayInfo->smCharInfo.Level/2+1;
					pow2 = lpPlayInfo->smCharInfo.Level+lpPlayInfo->smCharInfo.Level/2+1;
					break;
			}

			lpTransAttackData->Power = GetRandomPos( pow1, pow2 );
			lpTransAttackData2->Critical[0] = 0;		//Å©¸®Æ¼ÄÃ ÆÇÁ¤ ¾øÀ½
			break;


		/////////////////// 4Â÷½ºÅ³ ////////////////

		case SKILL_PLAY_IMPULSION:
			if ( lpPlayInfo->smCharInfo.JOB_CODE==JOBCODE_MECHANICIAN ) {
				pow1 = Impulsion_LightingDamage[Point][0];
				pow2 = Impulsion_LightingDamage[Point][1];

				lpTransAttackData->Power = GetRandomPos( pow1, pow2 );

				//¸ÞÄ«´Ð ¸÷ 30% Ãß°¡
				if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_MECHANIC ) {
					lpTransAttackData->Power+=(lpTransAttackData->Power*30)/100;
				}

				lpTransAttackData2->Critical[0] = 0;
				break;
			}
			return FALSE;


		case SKILL_PLAY_MAGNETIC_SPHERE:
			if ( lpPlayInfo->smCharInfo.JOB_CODE==JOBCODE_MECHANICIAN ) {
				if ( !lpPlayInfo->dwSkill_MagneticSphere_Time || lpPlayInfo->dwSkill_MagneticSphere_Time<dwPlayServTime ) {
					lpPlayInfo->dwSkill_MagneticSphere_Time = 0;
					return FALSE;
				}

				pow1 = Magnetic_Sphere_AddDamage[lpPlayInfo->dwSkill_MagneticSphere_Param][0];
				pow2 = Magnetic_Sphere_AddDamage[lpPlayInfo->dwSkill_MagneticSphere_Param][1];

				lpTransAttackData->Power = GetRandomPos( pow1, pow2 );
				lpTransAttackData2->Critical[0] = 0;
				lpTransAttackData->AttackState |= (sITEMINFO_LIGHTING+1)<<16;		//·Ú ¼Ó¼º

				//¸ÞÄ«´Ð ¸÷ 30% Ãß°¡
				if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_MECHANIC ) {
					lpTransAttackData->Power+=(lpTransAttackData->Power*30)/100;
				}
				break;
			}
			return FALSE;


		case SKILL_PLAY_DESTROYER:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;

			lpTransAttackData->AttackState = (lpTransAttackData->AttackState&0xFFFF0000)+2;		//Å©¸®Æ¼ÄÃ Ã³¸®
			lpTransAttackData->Power += (lpTransAttackData->Power*Destoryer_DamagePercent[Point])/100;

			lpTransAttackData2->Critical[0] += Destoryer_AddCritical[Point];

			if ( lpChar && lpChar->smCharInfo.Brood==smCHAR_MONSTER_DEMON ) {
				// µð¸Õ ¸ó½ºÅÍ¿¡°Ô 30% Ãß°¡
				lpTransAttackData->Power += (lpTransAttackData->Power*30)/100;
			}
			break;
/*
		case SKILL_PLAY_CYCLONE_STRIKE:
			if ( lpPlayInfo->smCharInfo.JOB_CODE==JOBCODE_FIGHTER ) {
				lpTransAttackData->Power+= (lpTransAttackData->Power*Cyclone_Strike_DamagePercent[Point])/100;
				//lpTransAttackData2->Critical[0] = 0;
				break;
			}
			return FALSE;
*/
		case SKILL_PLAY_ASSASSIN_EYE:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;

			lpPlayInfo->dwSkill_AssassinEye_Time = dwPlayServTime+Assassin_Eye_Time[Point]*1000;
			lpPlayInfo->dwSkill_AssassinEye_Param = Point;

			if ( lpChar ) {
				lpChar->dwAssassinEyeTime = lpPlayInfo->dwSkill_AssassinEye_Time;
				lpChar->AssassinEyeParam = Assassin_Eye_M_SubCritical[Point];
			}
			return FALSE;

		case SKILL_PLAY_CHARGING_STRIKE:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;

			if ( !lpTransAttackData2->Power2[0] ) 
				lpTransAttackData->Power += (lpTransAttackData->Power*Charging_Strike_CharingDamagePercent[Point])/100;
			else
				lpTransAttackData->Power += (lpTransAttackData->Power*Charging_Strike_DamagePercent[Point])/100;
			break;

		case SKILL_PLAY_SHADOW_MASTER:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;

			lpTransAttackData->Power += (lpTransAttackData->Power*Shadow_Master_DamagePercent[Point])/100;
			break;

		case SKILL_PLAY_PHOENIX_SHOT:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ARCHER ) return FALSE;
				lpTransAttackData->Power += (lpTransAttackData->Power*Phoenix_Shot_DamagePercent[Point])/100;
			break;

		case SKILL_PLAY_DIVINE_PIERCING:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_KNIGHT ) return FALSE;

			lpTransAttackData->Power += (lpTransAttackData->Power*Divine_Piercing_DamagePercent[Point])/100;
			break;

		case SKILL_PLAY_VENGEANCE: // Àåº° - º¥Á¯½º ¼öÁ¤
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;

			lpTransAttackData->Power += (lpTransAttackData->Power*Vengeance_DamagePercent[Point])/100;
			break;

		case SKILL_PLAY_SUMMON_MUSPELL:
			if ( lpPlayInfo->smCharInfo.JOB_CODE==JOBCODE_PRIESTESS ) {
				if ( !lpPlayInfo->dwSkill_SummonMuspell_Time || lpPlayInfo->dwSkill_SummonMuspell_Time<dwPlayServTime ) {
					lpPlayInfo->dwSkill_SummonMuspell_Time = 0;
					return FALSE;
				}

				pow1 = Summon_Muspell_Damage[lpPlayInfo->dwSkill_SummonMuspell_Param][0];
				pow2 = Summon_Muspell_Damage[lpPlayInfo->dwSkill_SummonMuspell_Param][1];

				lpTransAttackData->Power = GetRandomPos( pow1, pow2 );
				lpTransAttackData2->Critical[0] = 0;
				break;
			}

	}


	return TRUE;
}

//½ºÅ³ °ø°Ý º¯È¯
int rsSetSkillPlus( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , TRANS_ATTACKDATA *lpTransAttackData , TRANS_ATTACKDATA2 *lpTransAttackData2 )
{
	int pow;
	DWORD dwWeaponCode;
	smTRANS_COMMAND	smTransCommand;
	DWORD 	dwSkillCode = lpTransAttackData2->SkillCode&0xFF;

	DWORD	dwAttSkillCode = 0;
	
	if ( !lpPlayInfo->AdminMode )
		dwAttSkillCode = lpTransAttackData2->SkillCode;


	if ( lpPlayInfo->dwSkill_Maximize_Time && !dwAttSkillCode ) {
		//¸Æ½Ã¸¶ÀÌÁî Àû¿ë ( ÃÖ´ë °ø°Ý·Â ¹«±â ÃÖ´ëÄ¡ ¸¸Å­ Ãß°¡ )
		if ( lpPlayInfo->dwSkill_Maximize_Time<dwPlayServTime ) {
			lpPlayInfo->dwSkill_Maximize_Time = 0;
			lpPlayInfo->dwSkill_Maximize_Param = 0;
			return TRUE;
		}

		pow = lpTransAttackData2->Power[1]-lpTransAttackData2->Power2[1];
		if ( pow>=0 && pow<lpTransAttackData2->Power[1] ) {
			lpTransAttackData2->Power[1] += (pow * lpPlayInfo->dwSkill_Maximize_Param)/100;
			lpTransAttackData->Power = GetRandomPos( lpTransAttackData2->Power[0] , lpTransAttackData2->Power[1] );
		}
	}

	if ( lpPlayInfo->dwSkill_AutoMation_Time && !dwAttSkillCode ) {
		//¿ÀÅä¸ÅÀÌ¼Ç Àû¿ë ( °ø°Ý·ÂÀ» ¹«±â µ¥¹ÌÁö ÀÇ ºñÀ²·Î Ãß°¡ )
		if ( lpPlayInfo->dwSkill_AutoMation_Time<dwPlayServTime ) {
			lpPlayInfo->dwSkill_AutoMation_Time = 0;
			lpPlayInfo->dwSkill_AutoMation_Param = 0;
			return TRUE;
		}

		dwWeaponCode = lpTransAttackData2->dwWeaponCode&sinITEM_MASK2;
		if ( dwWeaponCode==sinWS1 || dwWeaponCode==sinWT1 ) {		//¹«±â È° , Àçºí¸° °è¿­¸¸ Àû¿ë
			pow = lpTransAttackData2->Power[1]-lpTransAttackData2->Power2[1];
			if ( pow>=0 && pow<lpTransAttackData2->Power[1] ) 
				lpTransAttackData2->Power[1] += (pow * lpPlayInfo->dwSkill_AutoMation_Param)/100;

			pow = lpTransAttackData2->Power[0]-lpTransAttackData2->Power2[0];
			if ( pow>=0 && pow<lpTransAttackData2->Power[0] ) 
				lpTransAttackData2->Power[0] += (pow * lpPlayInfo->dwSkill_AutoMation_Param)/100;

			lpTransAttackData->Power = GetRandomPos( lpTransAttackData2->Power[0] , lpTransAttackData2->Power[1] );
		}
	}

	if ( lpPlayInfo->dwSkill_TriumphOfValhalla_Time && !dwAttSkillCode ) {
		//Æ®¶óÀÌ¾öÇÁ ¹ßÇÒ¶ó
		if ( lpPlayInfo->dwSkill_TriumphOfValhalla_Time<dwPlayServTime ) {
			lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
			lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;
			return TRUE;
		}

		pow = GetRandomPos( lpTransAttackData2->Power[0] , lpTransAttackData2->Power[1]+(short)lpPlayInfo->dwSkill_TriumphOfValhalla_Param );
		lpTransAttackData->Power = pow;
	}

	if ( lpPlayInfo->dwSkill_HallOfValhalla_Time && !dwAttSkillCode ) {
		//È¦¿Àºê ¹ßÇÒ¶ó
		if ( lpPlayInfo->dwSkill_HallOfValhalla_Time<dwPlayServTime ) {
			lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
			return TRUE;
		}

		pow = GetRandomPos( lpTransAttackData2->Power[0] , lpTransAttackData2->Power[1]+(short)lpPlayInfo->wSkill_HallOfValhalla_Param[1] );
		lpTransAttackData->Power = pow;
	}

	if ( lpPlayInfo->dwSkill_Vanish_Time ) {
		//¹è´Ï½¬
		if ( lpPlayInfo->dwSkill_Vanish_Time<dwPlayServTime ) {
			lpPlayInfo->dwSkill_Vanish_Time = 0;
			lpPlayInfo->dwSkill_Vanish_Param = 0;
			return TRUE;
		}

		lpTransAttackData->Power += (lpTransAttackData->Power*Vanish_Damage[lpPlayInfo->dwSkill_Vanish_Param])/100;

		lpPlayInfo->dwSkill_Vanish_Time = 0;
		lpPlayInfo->dwSkill_Vanish_Param = 0;

		//¹è´Ï½¬ ÇØÁ¦ÇÏ±â
		smTransCommand.code = smTRANSCODE_PROCESS_SKILL;
		smTransCommand.size = sizeof( smTRANS_COMMAND );
		smTransCommand.WParam  = SKILL_PLAY_VANISH;
		smTransCommand.LParam  = 0;
		smTransCommand.SParam  = 0;
		smTransCommand.EParam  = 0;
		lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
	}

	if ( lpPlayInfo->dwSkill_Berserker_Time ) {
		//¹ö¼­Ä¿
		if ( lpPlayInfo->dwSkill_Berserker_Time<dwPlayServTime ) {
			lpPlayInfo->dwSkill_Berserker_Time = 0;
			lpPlayInfo->dwSkill_Berserker_Param = 0;
			return TRUE;
		}

		lpTransAttackData->Power += Berserker_AddAttack[lpPlayInfo->dwSkill_Berserker_Param];
	}

	if ( lpPlayInfo->dwSkill_ForceOfNature_Time ) {
		//Æ÷½º¿Àºê ³×ÀÌÃÄ
		if ( lpPlayInfo->dwSkill_ForceOfNature_Time<dwPlayServTime ) {
			lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
			return TRUE;
		}

		if ( dwSkillCode!=SKILL_PLAY_FALCON )
			lpTransAttackData->Power += lpPlayInfo->wSkill_ForceOfNature_Param[0];
	}


	if ( lpPlayInfo->dwSkill_GodsBless_Time ) {
		//°«ºí·¹½º
		if ( lpPlayInfo->dwSkill_GodsBless_Time<dwPlayServTime ) {
			lpPlayInfo->dwSkill_GodsBless_Time = 0;
			lpPlayInfo->dwSkill_GodsBless_Param = 0;
			return TRUE;
		}

		lpTransAttackData->Power += lpPlayInfo->dwSkill_GodsBless_Param;
	}

	if ( lpPlayInfo->dwSkill_FrostJavelin_Time && !dwAttSkillCode ) {
		//ÇÁ·Î½ºÆ®Àçºí¸°
		if ( lpPlayInfo->dwSkill_FrostJavelin_Time<dwPlayServTime ) {
			lpPlayInfo->dwSkill_FrostJavelin_Time = 0;
			lpPlayInfo->dwSkill_FrostJavelin_Param = 0;
			return TRUE;
		}

		dwWeaponCode = lpTransAttackData2->dwWeaponCode&sinITEM_MASK2;
		if ( dwWeaponCode==sinWT1 ) {		//¹«±â Àçºí¸° °è¿­¸¸ Àû¿ë
			pow = GetRandomPos( Frost_Javelin_IceAddDamage[lpPlayInfo->dwSkill_FrostJavelin_Param][0],
								Frost_Javelin_IceAddDamage[lpPlayInfo->dwSkill_FrostJavelin_Param][1] );

			lpTransAttackData->AttackState |= (sITEMINFO_ICE+1)<<16;
			lpTransAttackData->AttackState |= pow<<(16+4);		//ÀüÃ¼Áß ¾óÀ½¼Ó¼º µ¥¹ÌÁö
			lpTransAttackData->Power += pow;
		}
	}

	if ( lpPlayInfo->dwBlessSkill_Code==SKILL_PLAY_BLESS_DAMAGE ) {	//Å¬·£½ºÅ³ (µ¥¹ÌÁöÃß°¡)
		if ( lpPlayInfo->dwBlessSkill_Time>dwPlayServTime ) {
			lpTransAttackData->Power += (lpTransAttackData->Power*lpPlayInfo->dwBlessSkill_Param)/100;
		}
		else {
			lpPlayInfo->dwBlessSkill_Code = 0;
			lpPlayInfo->dwBlessSkill_Time = 0;
			return TRUE;
		}
	}

	//°ø¼º ½ºÅ©·Ñ
	if (  lpPlayInfo->dwSiegeItem_Scroll_Time ) {
		if ( lpPlayInfo->dwSiegeItem_Scroll_Time<dwPlayServTime ) {
			lpPlayInfo->dwSiegeItem_Scroll_Code = 0;
			lpPlayInfo->dwSiegeItem_Scroll_Time = 0;
		}
		else {
			switch( lpPlayInfo->dwSiegeItem_Scroll_Code ) {
				case (sinBI1|sin05):					//¹«Àû ½ºÅ©·Ñ
					lpTransAttackData->Power /= lpPlayInfo->dwSiegeItem_Scroll_Param;			//°ø°Ý·Â °¨¼Ò
					break;
				case (sinBI1|sin06):					//Å©¸®Æ¼ÄÃ ½ºÅ©·Ñ
					lpTransAttackData2->Critical[0] += (short)lpPlayInfo->dwSiegeItem_Scroll_Param;		//Å©¸®Æ¼ÄÃ 2¹è Áõ°¡
					break;
			}

			if ( lpPlayInfo->Position.Area==rsCASTLE_FIELD ) {
				switch( lpPlayInfo->dwSiegeItem_Scroll_Code ) {
					case (sinBC1|sin01):					//¹«Àû ½ºÅ©·Ñ
						lpTransAttackData->Power /= lpPlayInfo->dwSiegeItem_Scroll_Param;			//°ø°Ý·Â °¨¼Ò
						break;
					case (sinBC1|sin02):					//Å©¸®Æ¼ÄÃ ½ºÅ©·Ñ
						lpTransAttackData2->Critical[0] += (short)lpPlayInfo->dwSiegeItem_Scroll_Param;		//Å©¸®Æ¼ÄÃ 2¹è Áõ°¡
						break;
				}
			}
		}
	}


	return TRUE;
}


//½ÇÁ¦ Å©¸®Æ¼ÄÃ 
int GetCritical( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , int Critical_Hit )
{
	int Result;

	Result = Critical_Hit + (((lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level)*25)/100);

	//¾î¼¼½Å¾ÆÀÌ ½ºÅ³ Å©¸®Æ¼ÄÃ °­È­
	/*
	if ( lpPlayInfo->dwSkill_AssassinEye_Time && Critical_Hit>0 ) {

		if ( lpPlayInfo->dwSkill_AssassinEye_Time>dwPlayServTime ) {	
			Result += Assassin_Eye_AddCritical[ lpPlayInfo->dwSkill_AssassinEye_Param ];
		}
		else {
			lpPlayInfo->dwSkill_AssassinEye_Time = 0;
			lpPlayInfo->dwSkill_AssassinEye_Param = 0;
		}
	}
	*/
	if ( lpChar->dwAssassinEyeTime && Critical_Hit>0 ) {
		if ( lpChar->dwAssassinEyeTime>dwPlayServTime ) {	
			Result -= lpChar->AssassinEyeParam;
		}
		else {
			lpChar->dwAssassinEyeTime = 0;
			lpChar->AssassinEyeParam = 0;
		}
	}



	if(Result > 70)
		Result = 70;
	
	return Result;
}

//½ÇÁ¦ Å©¸®Æ¼ÄÃ 
int GetCritical2( rsPLAYINFO *lpPlayInfo , rsPLAYINFO *lpPlayInfo2 , int Critical_Hit )
{
	int Result;

	Result = Critical_Hit + (((lpPlayInfo->smCharInfo.Level - lpPlayInfo2->smCharInfo.Level)*25)/100);
	if(Result > 70)
		Result = 70;
	
	return Result;
}

//Æ÷½º¿Àºê ÆÄ¿ö¾÷
int AddForceOrbPower( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , TRANS_ATTACKDATA	*lpTransAttackData , DWORD dwSkillCode , int MinDamage , int MaxDamage )
{
	int damage = 0;
	int	sJobLevel;
	int	damage2;
	
	// ¹ÚÀç¿ø - ¸ÅÁ÷ Æ÷½º, ºô¸µ ¸ÅÁ÷ Æ÷½º´Â ÀÏ¹Ý½ºÅ³°ú ´ÜÅ¸¿¡´Â Àû¿ëÀÌ µÇÁö ¾ÊÀ¸¹Ç·Î return FALSE
	if ( (lpPlayInfo->dwForceOrb_Code&sinITEM_MASK3) > sin14 ) return FALSE;
	if ( !lpPlayInfo->dwForceOrb_Time ) return FALSE;
	if ( lpPlayInfo->dwForceOrb_Time<dwPlayServTime ) {
		lpPlayInfo->dwForceOrb_Time = 0;
		lpPlayInfo->dwForceOrb_Code = 0;
		lpPlayInfo->dwForceOrb_Damage = 0;
		return FALSE;
	}

	//ÀÏºÎ ½ºÅ³ Àû¿ë ±ÝÁö
	switch ( dwSkillCode&0xFF )
	{
	case SKILL_PLAY_RAGEOF_ZECRAM:
	case SKILL_PLAY_SPARK_SHIELD:
	case SKILL_PLAY_FALCON:
	case SKILL_PLAY_DANCING_SWORD:
	case SKILL_PLAY_SUMMON_MUSPELL:	//¼­¸Õ¹«½ºÆç ¿¡ Æ÷½º °ø°Ý·Â Ãß°¡ ¹ö±×¸¦ ÀÏº»Ãø ¿ä±¸·Î ¼öÁ¤ (2005³â7¿ù14ÀÏ)
	case SKILL_PLAY_PET_ATTACK:
	case SKILL_PLAY_PET_ATTACK2:


		return FALSE;
	}

	damage = lpPlayInfo->dwForceOrb_Damage;

	// ¹ÚÀç¿ø : ºô¸µ Æ÷½º Ãß°¡
	if ( lpPlayInfo->dwForceOrb_Code==(sinFO1|sin07) || lpPlayInfo->dwForceOrb_Code==(sinFO1|sin08) || lpPlayInfo->dwForceOrb_Code==(sinFO1|sin09) || lpPlayInfo->dwForceOrb_Code==(sinFO1|sin10) ) 
	{
		//¸ÓÅ° Æ÷½º, µ¥ºñ³× Æ÷½º, ½ì·¹½ºÅä Æ÷½º, ¹Ì¶óÁö Æ÷½º °ø°Ý·Â 10%°¡Áß
		damage2 = (MaxDamage+MinDamage)/2;
		if ( damage2>0 && damage2<1000 )
			damage += (damage2*10)/100;
	}
	else if( lpPlayInfo->dwForceOrb_Code==(sinFO1|sin11) )
	{
		//ÀÎÆä¸£³ª Æ÷½º 15%°¡Áß
		damage2 = (MaxDamage+MinDamage)/2;
		if ( damage2>0 && damage2<1000 )
			damage += (damage2*15)/100; // °ø°Ý·Â 15%°¡Áß
	}
	else if( lpPlayInfo->dwForceOrb_Code==(sinFO1|sin12) )
	{
		//ÀÌ´Ï±×¸¶ Æ÷½º 20%°¡Áß
		damage2 = (MaxDamage+MinDamage)/2;
		if ( damage2>0 && damage2<1000 )
			damage += (damage2*20)/100; //°ø°Ý·Â 20%°¡Áß
	}

	if ( dwSkillCode ) {
		sJobLevel = dwSkillCode&0xF;
		sJobLevel --;
		if ( sJobLevel>=0 && sJobLevel<0x10 ) {
			sJobLevel>>=2;
			switch( sJobLevel ) {
				case 0:		//1Â÷½ºÅ³
					if ( (dwSkillCode&0xFF)==SKILL_PLAY_MULTI_SPARK )
						damage = (damage*50)/100;
					else
						damage = (damage*80)/100;

					break;
				case 1:		//2Â÷½ºÅ³
					damage = (damage*90)/100;
					break;
				case 2:		//3Â÷½ºÅ³

					break;
				case 3:		//4Â÷½ºÅ³
					damage = (damage*150)/100;
					break;
			}

		}
	}

	lpTransAttackData->Power += damage;

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
	if ( lpChar ) {					//ÇØ¿Ü
		wsprintf( szDispDamage , ">%s Attack ( ForceOrb + %d ) (%d)" , lpChar->smCharInfo.szName , damage , lpTransAttackData->Power );
		rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
	}
	else {							//ÇØ¿Ü
		wsprintf( szDispDamage , "> Attack ( ForceOrb + %d ) (%d)" , damage , lpTransAttackData->Power );
		rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
	}
}
#endif*/
	return TRUE;
}

// ¹ÚÀç¿ø - ¸ÅÁ÷ Æ÷½º Ãß°¡, ºô¸µ ¸ÅÁ÷ Æ÷½º Ãß°¡(¹üÀ§°ø°Ý¿ë Æ÷½º¿Àºê ÆÄ¿ö¾÷)
int AddRangeForceOrbPower( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , TRANS_SKIL_ATTACKDATA	*lpTransSkillAttackData , DWORD dwSkillCode , int MinDamage , int MaxDamage )
{
	int damage = 0;
	int	sJobLevel;
	int	damage2;

	if( (lpPlayInfo->dwForceOrb_Code&sinITEM_MASK2) == sinFO1 ) // ¹ÚÀç¿ø - ÀÏ¹Ý Æ÷½º Àû¿ëÁß¿¡ ¹üÀ§Çü ½ºÅ³À» »ç¿ëÇÏ¸é ¸®ÅÏ½ÃÅ²´Ù.
	{
		if( (lpPlayInfo->dwForceOrb_Code&sinITEM_MASK3) < sin21 )
			return FALSE;
	}
	if ( !lpPlayInfo->dwForceOrb_Time ) return FALSE;
	if ( lpPlayInfo->dwForceOrb_Time<dwPlayServTime ) {
		lpPlayInfo->dwForceOrb_Time = 0;
		lpPlayInfo->dwForceOrb_Code = 0;
		lpPlayInfo->dwForceOrb_Damage = 0;
		return FALSE;
	}

	//ÀÏºÎ ½ºÅ³ Àû¿ë ±ÝÁö
	switch ( dwSkillCode&0xFF )
	{
		//	case SKILL_PLAY_RAGEOF_ZECRAM: // ¹ÚÀç¿ø - ·¹ÀÌÁö ¿Àºê Á¦Å©¶÷ ½ºÅ³Àº ¸ÅÁ÷ Æ÷½º ¶§ Àû¿ë½ÃÅ²´Ù.
	case SKILL_PLAY_SPARK_SHIELD:
	case SKILL_PLAY_FALCON:
	case SKILL_PLAY_DANCING_SWORD:
	case SKILL_PLAY_SUMMON_MUSPELL:	//¼­¸Õ¹«½ºÆç ¿¡ Æ÷½º °ø°Ý·Â Ãß°¡ ¹ö±×¸¦ ÀÏº»Ãø ¿ä±¸·Î ¼öÁ¤ (2005³â7¿ù14ÀÏ)
	case SKILL_PLAY_PET_ATTACK:
	case SKILL_PLAY_PET_ATTACK2:
	case SKILL_PLAY_ELEMENTAL_SHOT: // ¹ÚÀç¿ø - ¸ÅÁ÷ Æ÷½º »ç¿ë½Ã ÀÌ ½ºÅ³ÀÇ ³ú ¼Ó¼ºÀº Á¦¿Ü½ÃÅ²´Ù.
	case SKILL_PLAY_SOUL_SUCKER: // ¹ÚÀç¿ø - ½î¿ï½âÄ¿µµ ¸ÅÁ÷ Æ÷½º Àû¿ë½Ã Á¦¿Ü½ÃÅ²´Ù.
	case SKILL_PLAY_X_RAGE: // ¹ÚÀç¿ø - ÀÍ½ºÆ¼¸² ·¹ÀÌÁöµµ ¸ÅÁ÷ Æ÷½º Àû¿ë½Ã Á¦¿Ü½ÃÅ²´Ù.
	case SKILL_PLAY_EXPANSION: // ¹ÚÀç¿ø - ÀÍ½ºÆÒ¼Çµµ ¸ÅÁ÷ Æ÷½º Àû¿ë½Ã Á¦¿Ü½ÃÅ²´Ù.

		return FALSE;
	}

	damage = lpPlayInfo->dwForceOrb_Damage;


	// ¹ÚÀç¿ø : ºô¸µ Æ÷½º Ãß°¡
	if ( lpPlayInfo->dwForceOrb_Code==(sinFO1|sin27) || lpPlayInfo->dwForceOrb_Code==(sinFO1|sin28) || lpPlayInfo->dwForceOrb_Code==(sinFO1|sin29) || lpPlayInfo->dwForceOrb_Code==(sinFO1|sin30) ) 
	{
		//¸ÓÅ° ¸ÅÁ÷Æ÷½º, µ¥ºñ³× ¸ÅÁ÷Æ÷½º, ½ì·¹½ºÅä ¸ÅÁ÷Æ÷½º, ¹Ì¶óÁö ¸ÅÁ÷Æ÷½º °ø°Ý·Â 10%°¡Áß
		damage2 = (MaxDamage+MinDamage)/2;
		if ( damage2>0 && damage2<1000 )
			damage += (damage2*10)/100;
	}
	else if( lpPlayInfo->dwForceOrb_Code==(sinFO1|sin31) || lpPlayInfo->dwForceOrb_Code==(sinFO1|sin35) || 
		lpPlayInfo->dwForceOrb_Code==(sinFO1|sin36) || lpPlayInfo->dwForceOrb_Code==(sinFO1|sin37) )
	{
		//ÀÎÆä¸£³ª ¸ÅÁ÷Æ÷½º, ºô¸µ ¸ÅÁ÷Æ÷½º(3Á¾)µµ 15%°¡Áß
		damage2 = (MaxDamage+MinDamage)/2;
		if ( damage2>0 && damage2<1000 )
			damage += (damage2*15)/100; // °ø°Ý·Â 15%°¡Áß
	}
	else if( lpPlayInfo->dwForceOrb_Code==(sinFO1|sin32) )
	{
		//ÀÌ´Ï±×¸¶ ¸ÅÁ÷Æ÷½º 20%°¡Áß
		damage2 = (MaxDamage+MinDamage)/2;
		if ( damage2>0 && damage2<1000 )
			damage += (damage2*20)/100; //°ø°Ý·Â 20%°¡Áß
	}

	if ( dwSkillCode ) 
	{
		// ¹ÚÀç¿ø - ³ªÀÌÆ® SKILL_PLAY_SWORD_OF_JUSTICE / ¸ÅÁö¼Ç SKILL_PLAY_METEO »ç¿ë½Ã 4Â÷ ½ºÅ³ ÀÎ½Ä ¿À·ù·Î º¸¿ÏÇÔ.
		if(dwSkillCode == 336 || dwSkillCode == 384)
		{
			dwSkillCode += 15;
		}
		sJobLevel = dwSkillCode&0xF;
		sJobLevel --;
		if ( sJobLevel>=0 && sJobLevel<0x10 ) {
			sJobLevel>>=2;
			switch( sJobLevel ) {
	case 0:		//1Â÷½ºÅ³
		if ( (dwSkillCode&0xFF)==SKILL_PLAY_MULTI_SPARK )
			damage = (damage*50)/100;
		else
			damage = (damage*80)/100;

		break;
	case 1:		//2Â÷½ºÅ³
		damage = (damage*90)/100;
		break;
	case 2:		//3Â÷½ºÅ³

		break;
	case 3:		//4Â÷½ºÅ³
		damage = (damage*150)/100;
		break;
			}

		}
	}

	lpTransSkillAttackData->Power += damage;

/*#ifdef DISP_DAMAGE
	///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
	if ( lpPlayInfo->AdminMode>2 ) {
		if ( lpChar ) {
			wsprintf( szDispDamage , ">%s ¹üÀ§°ø°Ý ( ¸ÅÁ÷Æ÷½º¿Àºê + %d ) (%d)" , lpChar->smCharInfo.szName , damage , lpTransSkillAttackData->Power );
			rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
		}
		else {
			wsprintf( szDispDamage , "> ¹üÀ§°ø°Ý ( ¸ÅÁ÷Æ÷½º¿Àºê + %d ) (%d)" , damage , lpTransSkillAttackData->Power );
			rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
		}
	}
#endif*/
	return TRUE;
}

//°ø°ÝÀ» À¯ÀúÇÑÅ× º¸³¿ ( PK-PVP )
int rsSendAttackDataToUser(  rsPLAYINFO *lpPlayInfo , rsPLAYINFO *lpPlayInfo2 , TRANS_ATTACKDATA *lpTransAttackData )
{
	int regs,cnt,len;
	int  Param1,Param2;

	if ( !lpPlayInfo->AdminMode ) {
		if( rsServerConfig.Enable_PKField_All )
		{
			// pluto PKÇã¿ë ÇÊµå ÀüºÎ ¼öÁ¤
			if ( !rsServerConfig.Enable_PK || lpPlayInfo->Position.Area < 11 && lpPlayInfo->Position.Area > 34 ) 
				return FALSE;			//ÇöÀç ÀÏ¹ÝÀ¯Àú´Â PK±ÝÁö
		}
		else
		{
			if ( !rsServerConfig.Enable_PK && 
				sField[lpPlayInfo->Position.Area].State!=FIELD_STATE_CASTLE && 
				lpPlayInfo->Position.Area!=rsServerConfig.Enable_PKField ) 
				return FALSE;			//ÇöÀç ÀÏ¹ÝÀ¯Àú´Â PK±ÝÁö
		}
	}

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 )
{
	//ÇØ¿Ü
	wsprintf( szDispDamage , ">%s Damaged ( %d -> %d )" , lpPlayInfo2->smCharInfo.szName, lpTransAttackData->Power , lpTransAttackData->Power/PK_POWER_DIVIDE );
	rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/

	Param1 = 0;
	Param2 = 0;

	//¼Ó¼º °ø°ÝÀÏ °æ¿ì
	regs = (lpTransAttackData->AttackState>>16)&0xF;
	if ( regs && regs<sITEMINFO_NONE ) {
		cnt = lpTransAttackData->AttackState>>(16+4);		//¼Ó¼º °ª ( »óÀ§ ºñÆ®¿¡ ÀüÃ¼ µ¥¹ÌÁöÁß ¼Ó¼º µ¥¹ÌÁö¸¸ ÀúÀåµÊ )
		if ( !cnt ) 
			cnt = lpTransAttackData->Power;

		//¼Ó¼º¿¡ µû¸¥ ÀúÇ×·Â Àû¿ë
		len = lpPlayInfo2->smCharInfo.Resistance[regs-1];
		if ( len ) {					//¼Ó¼º ÀúÇ×·Â °è»ê
			if ( len>=100 ) len = 100;
			if ( len<=-100 ) len = -100;
			lpTransAttackData->Power -= ((cnt*len)/100);

			if ( lpTransAttackData->Power<0 ) lpTransAttackData->Power=0;
		}

		switch(regs-1) { //(lpTransAttackData->AttackState>>16)-1) {
			case sITEMINFO_ICE:
				if ( lpPlayInfo->dwSkill_EnchantWeapon_Time>dwPlayServTime && (lpPlayInfo->dwSkill_EnchantWeapon_Param>>8)==0 ) {
					//¾óÀ½ °ø°Ý ¼Óµµ ÀúÇÏ ( ÀÎÃ¼Æ® ÀÏ¶§ Àû¿ë )
					Param1 = -SKILL_PLAY_ENCHANT_WEAPON;
					Param2 = 230-10*(lpPlayInfo->dwSkill_EnchantWeapon_Param&0xFF);	//·¹º§¿¡ µû¸¥ ¼Óµµ
					break;
				}
				if ( lpPlayInfo->dwSkill_DancingSword_Time>dwPlayServTime && (lpPlayInfo->dwSkill_DancingSword_Param&0xFF)==0 ) {
					//´í½Ì¼Òµå ¾óÀ½ °ø°Ý
					Param1 = -SKILL_PLAY_DANCING_SWORD;
					Param2 = 230-10*(lpPlayInfo->dwSkill_DancingSword_Param>>16);
					break;
				}
				if ( lpPlayInfo->dwSkill_FrostJavelin_Time>dwPlayServTime ) {
					//ÇÁ·Î½ºÆ®Àçºí¸° ¾óÀ½°ø°Ý
					//¼Óµµ ´À·ÁÁü
					Param1 = -SKILL_PLAY_FROST_JAVELIN;
					Param2 = 240-(240*Frost_Javelin_SpeedSubPercent[lpPlayInfo->dwSkill_FrostJavelin_Param])/100;
					break;
				}
				break;

		}
	}


	return rsSendAttackUser( lpPlayInfo , lpPlayInfo2, lpTransAttackData->Power/PK_POWER_DIVIDE  , 0x80 , Param1, Param2 );
}

//°ø°Ý ¼ö½Å ¹ÞÀ½
int rsRecvAttackData( rsPLAYINFO *lpPlayInfo , TRANS_ATTACKDATA2 *lpTransAttackData )
{
	TRANS_ATTACKDATA	TransAttackData;
	smCHAR				*lpChar;
	smTRANS_COMMAND_EX	smTransCommand;
	rsPLAYINFO *lpPlayInfo2;
	char				szDispDamage[64];
	short				sDefAttack[2];
	int					pow;
	DWORD				dwCode;

/*
#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , "> °ø°ÝÆÐÅ¶ ÀÔ¼ö" );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif
*/
#ifdef _USE_DYNAMIC_ENCODE
	rsDecodeDamagePacket(lpPlayInfo, lpTransAttackData);						//Decryption
#else
	dm_DecodePacket(lpPlayInfo->dwObjectSerial, lpTransAttackData);			//Decryption
#endif

	if ( lpTransAttackData->dwChkSum!=dm_GetDamgeChkSum(lpTransAttackData) )	//ÆÐÅ¶ °Ë»ç
	{
		//µ¥¹ÌÁö µ¥ÀÌÅ¸ ¿À·ù¸¦ ±º¼­¹ö ·Î±×¿¡ ±â·Ï
		smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
		smTransCommand.size = sizeof( smTRANS_COMMAND );
		smTransCommand.WParam = 8500;
		smTransCommand.LParam = 1;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		rsRecordDamageError( lpPlayInfo , (smTRANS_COMMAND *)&smTransCommand );
		return FALSE;
	}

	dwCode = lpTransAttackData->SkillCode&0xFF;
	if ( dwCode!=SKILL_PLAY_FALCON && dwCode!=SKILL_PLAY_MAGNETIC_SPHERE && dwCode!=SKILL_PLAY_CHARGING_STRIKE &&
		dwCode!=SKILL_PLAY_SHADOW_MASTER && dwCode!=SKILL_PLAY_DIVINE_PIERCING ) {
		//ÆÓÄÁ, ¼ø¼­°¡ ¹Ù²ð °¡´É¼º ¶«¿¡ Á¦¿Ü
		if ( lpTransAttackData->AttackCount<=lpPlayInfo->DamagePacketCount || 
			lpTransAttackData->dwTime<=lpPlayInfo->dwDamagePacketTime ) {


/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , "> µ¥¹ÌÁö Å¬¶óÀÌ¾ðÆ® Ä«¿îÆÃ ½Ã°£ ¿À·ù" );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/

				//µ¥¹ÌÁö Å¬¶óÀÌ¾ðÆ® Ãø Ä«¿îÆÃ,½Ã°£ ¿À·ù
				return FALSE;
		}

		lpPlayInfo->DamagePacketCount = lpTransAttackData->AttackCount;
		lpPlayInfo->dwDamagePacketTime = lpTransAttackData->dwTime;
	}

	if ( lpTransAttackData->Power[0]>lpPlayInfo->sLimitDamage[0] || 
		lpTransAttackData->Power[1]>lpPlayInfo->sLimitDamage[1] ||
		lpTransAttackData->Critical[0]>lpPlayInfo->sLimitCritical[0] ) {

			//µ¥¹ÌÁö µ¥ÀÌÅ¸ ¿À·ù¸¦ ±º¼­¹ö ·Î±×¿¡ ±â·Ï
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof( smTRANS_COMMAND_EX );
			smTransCommand.WParam = 8510;
			smTransCommand.WxParam = 1;

			smTransCommand.LParam = lpTransAttackData->Power[0];
			smTransCommand.SParam = lpTransAttackData->Power[1];
			smTransCommand.EParam = lpTransAttackData->Critical[0];

			smTransCommand.LxParam = lpPlayInfo->sLimitDamage[0];
			smTransCommand.SxParam = lpPlayInfo->sLimitDamage[1];
			smTransCommand.ExParam = lpPlayInfo->sLimitCritical[0];

			rsRecordDamageError( lpPlayInfo , (smTRANS_COMMAND *)&smTransCommand );

#ifdef _LANGUAGE_KOREAN
			if ( lpPlayInfo->AdminMode ) {
				TRANS_CHATMESSAGE	TransChatMessage;

				wsprintf( TransChatMessage.szMessage , "°ø°Ý ¼öÄ¡¿À·ù ( %d %d %d ) ( %d %d %d )" ,
					lpTransAttackData->Power[0] , lpTransAttackData->Power[1] , lpTransAttackData->Critical[0],
					lpPlayInfo->sLimitDamage[0] , lpPlayInfo->sLimitDamage[1] , lpPlayInfo->sLimitCritical[0] );

				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				lpPlayInfo->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
			}
#endif

			//Á¦ÇÑ °ø°Ý ¼öÄ¡ ÃÊ°ú º¸Á¤
			lpTransAttackData->Power[0] = lpPlayInfo->sLimitDamage[0];
			lpTransAttackData->Power[1] = lpPlayInfo->sLimitDamage[1];
			lpTransAttackData->Critical[0] = lpPlayInfo->sLimitCritical[0];

	}


	TransAttackData.x = lpTransAttackData->x;
	TransAttackData.y = lpTransAttackData->y;
	TransAttackData.z = lpTransAttackData->z;

	TransAttackData.AttackSize = lpTransAttackData->AttackSize;
	TransAttackData.dwTarObjectSerial = lpTransAttackData->dwTarObjectSerial;
	TransAttackData.dwDestObjectSerial = lpTransAttackData->dwDestObjectSerial;

	sDefAttack[0] = lpTransAttackData->Power[0];
	sDefAttack[1] = lpTransAttackData->Power[1];

	TransAttackData.Power = GetRandomPos( sDefAttack[0] , sDefAttack[1] );
	TransAttackData.AttackState = lpTransAttackData->AttackState;

	dm_SkillCode_Temp = 0;

	if ( lpTransAttackData->Area[0]>=0 )
		lpChar = srFindCharFromSerial( lpTransAttackData->dwTarObjectSerial , lpTransAttackData->Area[0] );
	else
		lpChar = srFindCharFromSerial( lpTransAttackData->dwTarObjectSerial );

	if ( lpTransAttackData->SkillCode ) {
		if ( rsSetSkillAttack( lpPlayInfo , lpChar , &TransAttackData , lpTransAttackData )==FALSE ) 
			return FALSE;
	}

	if ( rsSetSkillPlus( lpPlayInfo , lpChar , &TransAttackData , lpTransAttackData )==FALSE ) return FALSE;

	if ( !lpTransAttackData->SkillCode ) {
		//ÀÏ¹Ý °ø°Ý
		if ( rsServerConfig.Event_Child ) {
			//¾î¸°ÀÌ ÀÌº¥Æ® ( ¾óÅ«ÀÌ Ä³¸¯ÀÏ¶§ °ø°Ý°¡Áß )
			if ( lpPlayInfo->smCharInfo.SizeLevel>0x1000 && lpPlayInfo->smCharInfo.SizeLevel<=0x1002 ) {
				TransAttackData.Power += (TransAttackData.Power*15)/100;	//°ø°Ý·Â 15% °¡Áß
			}
		}
	}

	//°ø°Ý¿¡ ÀúÁÖ°¡ °É·È´Ù
	if ( lpPlayInfo->dwCurse_Attack_Time ) {
		if( lpPlayInfo->dwCurse_Attack_Time>dwPlayServTime)
			TransAttackData.Power -= (TransAttackData.Power*lpPlayInfo->dwCurse_Attack_Param)/100;
		else
			lpPlayInfo->dwCurse_Attack_Time = 0;
	}


	// Àåº° - ¿»·Î¿ì µå·¡°ï
	if( lpPlayInfo->dwTime_PrimeItem_HelpPet > (DWORD)tServerTime && lpPlayInfo->smCharInfo.GravityScroolCheck[1] == 2)
	{
		TransAttackData.Power += (TransAttackData.Power * 10) / 100; 
	}





//	if ( !lpChar ) return FALSE;

	if ( lpChar ) {

		//Æ÷½º¿Àºê °ø°Ý·Â Ãß°¡ 
		AddForceOrbPower(lpPlayInfo , lpChar ,  &TransAttackData , lpTransAttackData->SkillCode , sDefAttack[0] , sDefAttack[1]);

		if ( lpTransAttackData->Critical[0] ) {
			if ( (rand()%100)<GetCritical( lpPlayInfo , lpChar , lpTransAttackData->Critical[0] ) ) {
				TransAttackData.AttackState = (TransAttackData.AttackState&0xFFFF0000)+2;		//Å©¸®Æ¼ÄÃ Ã³¸®
				pow = TransAttackData.Power;
				TransAttackData.Power = (pow*170)/100;						//Å©¸®Æ¼ÄÃ °ø°Ý°¡Áß

				//¾î¼¼½Å ¾ÆÀÌ
				if ( lpPlayInfo->dwSkill_AssassinEye_Time ) {
					if ( lpPlayInfo->dwSkill_AssassinEye_Time>dwPlayServTime ) {	
						TransAttackData.Power = (pow*(170+Assassin_Eye_AddCritical[ lpPlayInfo->dwSkill_AssassinEye_Param ]))/100;						//Å©¸®Æ¼ÄÃ °ø°Ý°¡Áß
					}
					else {
						lpPlayInfo->dwSkill_AssassinEye_Time = 0;
						lpPlayInfo->dwSkill_AssassinEye_Param = 0;
					}
				}

				smTransCommand.code = smTRANSCODE_ATTACK_RESULT;
				smTransCommand.size = sizeof(smTRANS_COMMAND);
				smTransCommand.WParam = 1;
				smTransCommand.LParam = 0;
				smTransCommand.SParam = 0;
				smTransCommand.EParam = 0;
				lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s °ø°Ý½Ãµµ ( Å©¸®Æ¼ÄÃ )" , lpChar->smCharInfo.szName );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/

			}
		}

		//ºô¸µ¾ÆÀÌÅÛ½ºÅ³Àû¿ë
		rsBillingItemSkill( lpPlayInfo , lpChar , 1 , TransAttackData.Power , lpTransAttackData->SkillCode&0xFF );


		rsRecvAttackData_Old( lpPlayInfo , &TransAttackData , lpChar , TRUE );

		if ( lpChar->dwTargetLockTime==0 && (
			lpChar->smCharInfo.dwCharSoundCode==snCHAR_SOUND_DEATHKNIGHT ||  
			lpChar->smCharInfo.dwCharSoundCode==snCHAR_SOUND_BABEL ||  
			lpChar->smCharInfo.dwCharSoundCode==snCHAR_SOUND_CASTLE_CRYSTAL_R ||  
			lpChar->smCharInfo.dwCharSoundCode==snCHAR_SOUND_CASTLE_CRYSTAL_G ||  
			lpChar->smCharInfo.dwCharSoundCode==snCHAR_SOUND_CASTLE_CRYSTAL_B ) )
		{
			//¹Ùº§ ¶Ç´Â Å©¸®½ºÅ» ¿ø°Å¸® °ø°ÝÇÑ À¯Àú·Î Å¸°Ù º¯°æ
			int dist,x,y,z;

			x = (lpPlayInfo->Position.x - lpChar->pX)>>FLOATNS;
			y = (lpPlayInfo->Position.y - lpChar->pY)>>FLOATNS;
			z = (lpPlayInfo->Position.z - lpChar->pZ)>>FLOATNS;
			dist = x*x+y*y+z*z;

			if ( dist<=(lpChar->smCharInfo.Shooting_Range*lpChar->smCharInfo.Shooting_Range) ) {
				lpChar->lpTargetPlayInfo = lpPlayInfo;
				lpChar->dwTargetLockTime = dwPlayServTime+4000;
			}
		}
	}
	else {
		//PK - PVP ¸ðµå¿ë

		lpPlayInfo2 = srFindUserFromSerial( lpTransAttackData->dwTarObjectSerial );
		if ( lpPlayInfo2 ) {
			//Æ÷½º¿Àºê °ø°Ý·Â Ãß°¡ 
			AddForceOrbPower(lpPlayInfo , 0 ,  &TransAttackData , lpTransAttackData->SkillCode , sDefAttack[0] , sDefAttack[1]);

			if ( lpTransAttackData->Critical[0] ) {
				if ( (rand()%100)<GetCritical2( lpPlayInfo , lpPlayInfo2 , lpTransAttackData->Critical[0] ) ) {
					TransAttackData.AttackState = (TransAttackData.AttackState&0xFFFF0000)+2;		//Å©¸®Æ¼ÄÃ Ã³¸®
					pow = TransAttackData.Power;
					TransAttackData.Power = (pow*170)/100;						//Å©¸®Æ¼ÄÃ °ø°Ý°¡Áß

					//¾î¼¼½Å ¾ÆÀÌ
					if ( lpPlayInfo->dwSkill_AssassinEye_Time ) {
						if ( lpPlayInfo->dwSkill_AssassinEye_Time>dwPlayServTime ) {	
							TransAttackData.Power = (pow*(170+Assassin_Eye_AddCritical[ lpPlayInfo->dwSkill_AssassinEye_Param ]))/100;						//Å©¸®Æ¼ÄÃ °ø°Ý°¡Áß
						}
						else {
							lpPlayInfo->dwSkill_AssassinEye_Time = 0;
							lpPlayInfo->dwSkill_AssassinEye_Param = 0;
						}
					}

					smTransCommand.code = smTRANSCODE_ATTACK_RESULT;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 1;
					smTransCommand.LParam = 0;
					smTransCommand.SParam = 0;
					smTransCommand.EParam = 0;
					lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s °ø°Ý½Ãµµ ( Å©¸®Æ¼ÄÃ )" , lpPlayInfo2->smCharInfo.szName );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/
				}
			}
			rsSendAttackDataToUser( lpPlayInfo , lpPlayInfo2 , &TransAttackData );
		}
	}


	if ( lpPlayInfo->AdminMode ) {
		smTransCommand.code = smTRANSCODE_DISP_DAMAGE;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = TransAttackData.Power;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
	}

	return TRUE;
}


int rsSetSkillRangeAttack( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , TRANS_ATTACKDATA *lpTransAttackData , TRANS_SKIL_ATTACKDATA *lpTransSkillAttackData , TRANS_SKIL_ATTACKDATA2 *lpTransRangeAttack )
{
	DWORD	dwSkillCode;
	int		Point;
	int		Param;
	int		pow,pow1,pow2;
	int		cnt;
	smTRANS_COMMAND	smTransCommand;

	dwSkillCode = lpTransRangeAttack->SkillCode&0xFF;
	Point = ((lpTransRangeAttack->SkillCode>>8)&0xF)-1;
	Param = (lpTransRangeAttack->SkillCode>>12)&0xF;

	if ( Point<0 || Point>=10 ) return FALSE;

	dm_SkillCode_Temp = dwSkillCode;

	if ( lpPlayInfo->dwSkill_Vanish_Time ) {
		//¹è´Ï½¬
		if ( lpPlayInfo->dwSkill_Vanish_Time<dwPlayServTime ) {
			lpPlayInfo->dwSkill_Vanish_Time = 0;
			lpPlayInfo->dwSkill_Vanish_Param = 0;
			return TRUE;
		}

		lpPlayInfo->dwSkill_Vanish_Time = 0;
		lpPlayInfo->dwSkill_Vanish_Param = 0;

		//¹è´Ï½¬ ÇØÁ¦ÇÏ±â
		smTransCommand.code = smTRANSCODE_PROCESS_SKILL;
		smTransCommand.size = sizeof( smTRANS_COMMAND );
		smTransCommand.WParam  = SKILL_PLAY_VANISH;
		smTransCommand.LParam  = 0;
		smTransCommand.SParam  = 0;
		smTransCommand.EParam  = 0;
		lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
	}

	//·¹º§·Î Á¤»óÀûÀÎ ½ºÅ³ ÄÚµåÀÎÁö °Ë»ç
	if ( rsCheckSkillLevel( lpPlayInfo , dwSkillCode )==FALSE ) {
		if ( lpPlayInfo->WarningCount<5 ) {
			//¿À·ù ·Î±× ³²±â±â
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.WParam = 8850;
			smTransCommand.LParam = lpPlayInfo->smCharInfo.Level;
			smTransCommand.SParam = dwSkillCode;
			smTransCommand.EParam = Point;
			rsSendDataServer( lpPlayInfo->lpsmSock , &smTransCommand );
			lpPlayInfo->WarningCount++;
		}
		return FALSE;
	}

	switch( dwSkillCode ) {
		case SKILL_PLAY_PIKEWIND:			//ÆÄÀÌÅ© À©µå
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;	//ÆÄÀÌÅ©¸Ç Àü¿ë

			lpTransSkillAttackData->AttackSize = Pike_Wind_Push_Lenght[Point];
			lpTransSkillAttackData->Power = GetRandomPos( Pike_Wind_Damage[Point][0] ,  Pike_Wind_Damage[Point][1] );
			lpTransSkillAttackData->AttackState = 1;
			return TRUE;

		case SKILL_PLAY_GROUND_PIKE:		//±×¶ó¿îµå ÆÄÀÌÅ©
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;	//ÆÄÀÌÅ©¸Ç Àü¿ë

			lpTransSkillAttackData->AttackSize = G_Pike_Range[Point];
			lpTransSkillAttackData->Power = GetRandomPos( G_Pike_Damage[Point][0] ,  G_Pike_Damage[Point][1] );
			lpTransSkillAttackData->AttackState = 3;
			return TRUE;

		case SKILL_PLAY_ROAR:				//·Î¾î
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;	//ÆÄÀÌÅÍ Àü¿ë

			lpTransSkillAttackData->AttackSize = Roar_Range[Point];
			lpTransSkillAttackData->Power = Roar_Time[Point];
			lpTransSkillAttackData->AttackState = 2;
			return TRUE;

		case SKILL_PLAY_DIVINE_LIGHTNING:	//µð¹ÙÀÎ ¶óÀÌÆ®´×
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PRIESTESS ) return FALSE;	//ÇÁ¸®½ºÆ¼½º Àü¿ë
			if ( lpTransSkillAttackData->TargetCount>Divine_Lightning_Num[Point] ) return FALSE;	//¹ø°³ Å¸°Ù ¼öº¸´Ù ¸¹À½

			/*
			pow1 = Divine_Lightning_Damage[Point][0]+lpTransRangeAttack->Critical[1]/8;
			pow2 = Divine_Lightning_Damage[Point][1]+lpTransRangeAttack->Critical[1]/4;

			pow1 += lpTransRangeAttack->Power2[0];
			pow2 += lpTransRangeAttack->Power2[1];
			*/

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			pow1 = Divine_Lightning_Damage[Point][0] + (lpTransRangeAttack->Critical[1]/6);
			pow2 = Divine_Lightning_Damage[Point][1] + (lpTransRangeAttack->Critical[1]/3);

			pow1 += (lpPlayInfo->smCharInfo.Level/2);
			pow2 += (lpPlayInfo->smCharInfo.Level/2);


			lpTransSkillAttackData->Power = GetRandomPos( pow1 , pow2 );
			lpTransSkillAttackData->AttackState = 103;

			return TRUE;

		case SKILL_PLAY_MECHANIC_BOMB:		//¸ÞÄ«´Ð¹ü
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MECHANICIAN ) return FALSE;	//¸ÞÄ«´Ï¼Ç Àü¿ë

			lpTransSkillAttackData->AttackSize = Mechanic_Bomb_Attack_Range[Point];
			lpTransSkillAttackData->Power = GetRandomPos( Mechanic_Bomb_Damage[Point][0] , Mechanic_Bomb_Damage[Point][1] );
			lpTransAttackData->Power = lpTransSkillAttackData->Power>>1;
			lpTransSkillAttackData->Power>>=1;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;

		case SKILL_PLAY_GREAT_SMASH:		//±×·¹ÀÌÆ® ½º¸Å½¬
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MECHANICIAN ) return FALSE;	//¸ÞÄ«´Ï¼Ç Àü¿ë

			lpTransSkillAttackData->AttackSize = 70;
/*
			pow = lpPlayInfo->smCharInfo.Level/G_Smash_Attack_Rage[Point];
			pow += GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			pow >>=1;
*/
			pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1]+(lpTransRangeAttack->Critical[1]/5) );
			pow += G_Smash_Attack_Rage[Point];
			pow >>=1;

			lpTransSkillAttackData->Power = pow;
			lpTransAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;

		case SKILL_PLAY_SPARK:				//½ºÆÄÅ©
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MECHANICIAN ) return FALSE;	//¸ÞÄ«´Ï¼Ç Àü¿ë

			lpTransSkillAttackData->AttackSize = Spark_Area[Point];
			lpTransSkillAttackData->Power = GetRandomPos( Spark_Damage[Point][0] , Spark_Damage[Point][1] );
			lpTransSkillAttackData->Power += lpPlayInfo->smCharInfo.Level/5;
			lpTransSkillAttackData->AttackState = 101;		//Àü±â

/*
			lpTransSkillAttackData->AttackSize = Spark_Area[Point];
			lpTransSkillAttackData->Power = GetRandomPos( Spark_Damage[Point][0] , Spark_Damage[Point][1] );
			lpTransAttackData->Power = lpTransSkillAttackData->Power>>1;
			lpTransSkillAttackData->Power>>=1;
			lpTransSkillAttackData->AttackState = 0;
*/
			return TRUE;

		case SKILL_PLAY_TORNADO:			//Åä³×ÀÌµµ
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;	//ÆÄÀÌÅ©¸Ç Àü¿ë

			pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			pow += ( pow*Tornado_Damage[Point] )/100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;

		case SKILL_PLAY_ARROWOF_RAGE:		//¿¤·Î¿ì ¿ÀÇÁ ·¹ÀÌÁö
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ARCHER ) return FALSE;	//¾ÆÃÄ Àü¿ë

			lpTransSkillAttackData->AttackSize = A_Rage_Area[Point];
			pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			pow += ( lpPlayInfo->smCharInfo.Level / A_Rage_Damage[Point] );
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;

		case SKILL_PLAY_RAGEOF_ZECRAM:		//·¹ÀÌÁö ¿Àºê Á¦Å©¶÷
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;	//ÆÄÀÌÅÍ Àü¿ë

			lpTransSkillAttackData->AttackSize = 70;
			pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			pow += ( pow*R_Zecram_Damage[Point] )/100;
			pow >>=1;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 100;		//ºÒ¼Ó¼º
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE+1)<<16;		//ºÒ ¼Ó¼º
			return TRUE;

		case SKILL_PLAY_EXPANSION:			//ÀÍ½ºÆÒ¼Ç
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;	//ÆÄÀÌÅ©¸Ç Àü¿ë

			lpTransSkillAttackData->AttackSize = 180;
			pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			pow += ( pow*Expansion_Damage[Point] )/100;

			//½ºÅ³ ·¹º§´ç 5% °ø°Ý·Â »ó½Â
			pow += (pow*(5*(Point+1)))/100;

			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;


			if ( lpChar ) {
				for( cnt=0;cnt<lpTransRangeAttack->TargetCount;cnt++) {
					if ( lpTransRangeAttack->dwTarObjectSerial[cnt]==lpChar->dwObjectSerial ) {
						lpTransAttackData->Power = 0;
						break;
					}
				}
			}
			return TRUE;

		case SKILL_PLAY_SWORD_BLAST:		//¼Òµå ºí·¡½ºÆ®
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_KNIGHT ) return FALSE;	//³ªÀÌÆ® Àü¿ë

			pow = GetRandomPos( Sword_Blast_Damage[Point][0] , Sword_Blast_Damage[Point][1]+(lpPlayInfo->smCharInfo.Level/2) );
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;

		case SKILL_PLAY_BRANDISH:			//ºê·£µð½¬
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_KNIGHT ) return FALSE;	//³ªÀÌÆ® Àü¿ë

			lpTransSkillAttackData->AttackSize = Brandish_Range[Point];
			pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			pow += ( pow*Brandish_Damage[Point] ) /100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;

		case SKILL_PLAY_PIERCING:			//ÇÇ¾î½Ì
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_KNIGHT ) return FALSE;	//³ªÀÌÆ® Àü¿ë

			pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			pow += ( pow*Piercing_Damage[Point] ) /100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;

		case SKILL_PLAY_SHIELD_STRIKE:		//½¯µå ½ºÆ®¶óÀÌÅ©
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;	//¾ÆÅ»¶õÅ¸ Àü¿ë

			lpTransSkillAttackData->Power = GetRandomPos( S_Strike_Damage[Point][0] , S_Strike_Damage[Point][1]+(lpPlayInfo->smCharInfo.Level/5) );
			lpTransSkillAttackData->AttackState = 5;
			return TRUE;

		case SKILL_PLAY_SOUL_SUCKER:		//¼Ò¿ï ¼®Ä¿
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;	//¾ÆÅ»¶õÅ¸ Àü¿ë

			lpTransSkillAttackData->Power = Point;
			lpTransSkillAttackData->AttackState = 4;
			return TRUE;

		case SKILL_PLAY_FIRE_BALL:			//ÆÄÀÌ¾îº¼
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MAGICIAN ) return FALSE;	//¸ÅÁö¼Ç Àü¿ë

			lpTransSkillAttackData->AttackSize = FireBall_Area[Point];

			pow1 = FireBall_Damage[Point][0];
			pow2 = FireBall_Damage[Point][1];

			if ( lpPlayInfo->dwSkill_SpiritElemental_Time ) {		//½ºÇÇ¸´¿¤¸®¸àÅ» µ¥¹ÌÁö °¡Áß
				if ( lpPlayInfo->dwSkill_SpiritElemental_Time>dwPlayServTime ) {
					pow1 += ( pow1 * lpPlayInfo->dwSkill_SpiritElemental_Param )/100;
					pow2 += ( pow2 * lpPlayInfo->dwSkill_SpiritElemental_Param )/100;
				}
				else {
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}

			/*
			pow1 +=lpTransRangeAttack->Critical[1]/8;
			pow2 +=lpTransRangeAttack->Critical[1]/4;

			pow1 += lpTransRangeAttack->Power2[0];
			pow2 += lpTransRangeAttack->Power2[1];
			*/

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			pow1 += lpPlayInfo->smCharInfo.Level/2;
			pow2 += lpPlayInfo->smCharInfo.Level/2;

			pow1 +=lpTransRangeAttack->Critical[1]/6;
			pow2 +=lpTransRangeAttack->Critical[1]/4;

			pow = GetRandomPos( pow1 , pow2 );
	//		lpTransSkillAttackData->Power = (pow*70)/100;
	//		lpTransAttackData->Power = (pow*30)/100;

			lpTransSkillAttackData->Power = (pow*70)/100;
			lpTransAttackData->Power = pow;

			lpTransSkillAttackData->AttackState = 100;
			lpTransAttackData->AttackState |= (sITEMINFO_FIRE+1)<<16;		//ºÒ ¼Ó¼º
			return TRUE;

		case SKILL_PLAY_COLUMN_OF_WATER:	//¿öÅä³×ÀÌµµ
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MAGICIAN ) return FALSE;	//¸ÅÁö¼Ç Àü¿ë

			lpTransSkillAttackData->AttackSize = Watornado_Area[Point];

			pow1 = Watornado_Damage[Point][0];
			pow2 = Watornado_Damage[Point][1];

			if ( lpPlayInfo->dwSkill_SpiritElemental_Time ) {		//½ºÇÇ¸´¿¤¸®¸àÅ» µ¥¹ÌÁö °¡Áß
				if ( lpPlayInfo->dwSkill_SpiritElemental_Time>dwPlayServTime ) {
					pow1 += (pow1*lpPlayInfo->dwSkill_SpiritElemental_Param)/100;
					pow2 += (pow2*lpPlayInfo->dwSkill_SpiritElemental_Param)/100;
				}
				else {
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}

			/*
			pow1 += lpTransRangeAttack->Critical[1]/8;
			pow2 += lpTransRangeAttack->Critical[1]/4;

			pow1 += lpTransRangeAttack->Power2[0];
			pow2 += lpTransRangeAttack->Power2[1];
			*/

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			pow1 += lpPlayInfo->smCharInfo.Level/2;
			pow2 += lpPlayInfo->smCharInfo.Level/2;

			pow1 +=lpTransRangeAttack->Critical[1]/6;
			pow2 +=lpTransRangeAttack->Critical[1]/3;

			pow = GetRandomPos( pow1 , pow2 );
		//	lpTransSkillAttackData->Power = (pow*70)/100;
		//	lpTransAttackData->Power = (pow*30)/100;

			lpTransSkillAttackData->Power = (pow*70)/100;
			lpTransAttackData->Power = pow;


			lpTransSkillAttackData->AttackState = 104;
			lpTransAttackData->AttackState |= (sITEMINFO_NONE)<<16;		//¹« ¼Ó¼º
			return TRUE;

		case SKILL_PLAY_ENCHANT_WEAPON:		//ÀÎÃ¾Æ® ¿þÆù Àü±â½ºÇÃ·¹½¬¿ë
			if ( !lpPlayInfo->dwSkill_EnchantWeapon_Time ) return FALSE;			//ÀÎÃ¾Æ® »óÅÂ È®ÀÎ

			lpTransSkillAttackData->AttackSize = 50;
			lpTransSkillAttackData->Power = GetRandomPos( Enchant_Weapon_Damage_Lightning[Point][0] , Enchant_Weapon_Damage_Lightning[Point][1] );
			lpTransSkillAttackData->AttackState = 105;
			return TRUE;

		case SKILL_PLAY_VENOM_SPEAR:		//º£³ð½ºÇÇ¾î
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;	//ÆÄÀÌÅ©¸Ç Àü¿ë
			if ( lpTransSkillAttackData->TargetCount>VenomSpear_Num[Point] ) return FALSE;	//µ¶Ã¢ Å¸°Ù ¼öº¸´Ù ¸¹À½

			//µ¥¹ÌÁö ÃÖ´ëÁö ÃÊ°ú
			if ( lpTransRangeAttack->Power2[0]>lpPlayInfo->sLimitDamage[0] )
				lpTransRangeAttack->Power2[0] = lpPlayInfo->sLimitDamage[0];
			if ( lpTransRangeAttack->Power2[1]>lpPlayInfo->sLimitDamage[1] )
				lpTransRangeAttack->Power2[1] = lpPlayInfo->sLimitDamage[1];

			pow1 = lpTransRangeAttack->Power2[0]>>1;
			pow2 = lpTransRangeAttack->Power2[1]>>1;

			lpTransSkillAttackData->Power = GetRandomPos( pow1 , pow2 );
			lpTransSkillAttackData->AttackState = 106;
			lpTransAttackData->AttackState |= (sITEMINFO_POISON+1)<<16;		//µ¶ ¼Ó¼º

			return TRUE;
/*
		case SKILL_PLAY_BLADE_OF_BLAZE:		//ºÒ·¹ÀÌµð ¿Àºê ºí·¹ÀÌÁî
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PIKEMAN ) return FALSE;	//ÆÄÀÌÅ©¸Ç Àü¿ë

			if ( lpTransRangeAttack->Power[0]<lpTransRangeAttack->Power2[0] || lpTransRangeAttack->Power[1]<lpTransRangeAttack->Power2[1] ) {
				//¹«±âµ¥¹ÌÁö ¿À·ù
				return FALSE;
			}
			pow1 = B_Of_Blaze_Damage[Point][0] + lpTransRangeAttack->Power2[0];
			pow2 = B_Of_Blaze_Damage[Point][1] + lpTransRangeAttack->Power2[1];

			lpTransSkillAttackData->Power = GetRandomPos( pow1 , pow2 );
			lpTransSkillAttackData->AttackState = 100;
			return TRUE;
*/

		case SKILL_PLAY_ELEMENTAL_SHOT:		//¿¤¸®¸àÅ»¼¦ (Àü±â)
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ARCHER ) return FALSE;	//¾ÆÃÄ Àü¿ë
			if ( Param!=1 ) return FALSE;
			lpTransSkillAttackData->AttackSize = 75;
			pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			lpTransAttackData->Power = pow;
			lpTransSkillAttackData->Power = GetRandomPos( Elemental_Shot_Lightning[Point][0] , Elemental_Shot_Lightning[Point][1] );
			lpTransSkillAttackData->AttackState = 105;
			lpTransAttackData->AttackState |= (sITEMINFO_LIGHTING+1)<<16;		//Àü±â ¼Ó¼º
			return TRUE;

		case SKILL_PLAY_BOMB_SHOT:			//¹ü¼¦
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ARCHER ) return FALSE;	//¾ÆÃÄ Àü¿ë

			if ( lpChar ) {
				pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
				pow += (pow*BombShot_Damage[Point])/100;

				if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_DEMON ) 
					pow += (pow*BombShot_DemonDamage[Point])/100;

				lpTransAttackData->Power = pow;
			}
			lpTransSkillAttackData->Power = GetRandomPos( BombShot_AddDamage[Point][0],BombShot_AddDamage[Point][1] );
			lpTransSkillAttackData->AttackState = 100;
			lpTransAttackData->AttackState = 0;
			//lpTransAttackData->AttackState |= (sITEMINFO_FIRE+1)<<16;		//ºÒ ¼Ó¼º
			return TRUE;

		case SKILL_PLAY_PERFORATION:			//ÆÛÆ÷·¹ÀÌ¼Ç
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ARCHER ) return FALSE;	//¾ÆÃÄ Àü¿ë

			lpTransSkillAttackData->AttackSize = 340+Perforation_Attack_Range[Point];

			pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			pow += (pow*Perforation_Damage[Point])/100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			dm_Critical_Temp = lpTransRangeAttack->Critical[0];
			return TRUE;
/*
		case SKILL_PLAY_FLAME_BRANDISH:			//ÇÁ·¹ÀÓ ºê·£µð½¬
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_KNIGHT ) return FALSE;	//³ªÀÌÆ® Àü¿ë

			lpTransSkillAttackData->AttackSize = 80;

			if ( lpChar && lpTransRangeAttack->Power2[0]>0 && lpTransRangeAttack->Power2[0]<=10 ) {

				pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
				pow += pow*(Brandish_Damage[lpTransRangeAttack->Power2[0]-1])/100;//*130)/100;
				pow += (pow*30)/100;

				if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_MUTANT )			//¹ÂÅÏÆ® °ø°Ý·Â 30%Ãß°¡
					pow += (pow*30)/100;

				lpTransAttackData->Power = pow;
				lpTransSkillAttackData->AttackState = 0;

				pow = GetRandomPos( Flame_Brandish_Damage[Point][0] , Flame_Brandish_Damage[Point][1] );
				lpTransSkillAttackData->Power = pow;
				lpTransSkillAttackData->AttackState = 100;
				return TRUE;
			}
			break;
*/
		case SKILL_PLAY_LIGHTNING_JAVELIN:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;	//¾ÆÅ» Àü¿ë

			lpTransSkillAttackData->AttackSize = 100;
			pow = GetRandomPos( Lightning_Javelin_Damage[Point][0] , Lightning_Javelin_Damage[Point][1]+(lpPlayInfo->smCharInfo.Level/3) );
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 101;		//Àü±â

			lpTransAttackData->Power = GetRandomPos(lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1]+(lpPlayInfo->smCharInfo.Level/3) );
			lpTransAttackData->AttackState = 0;

			if ( lpChar ) {
				if ( lpChar->smCharInfo.Brood==smCHAR_MONSTER_UNDEAD ) {
					lpTransAttackData->Power += lpTransAttackData->Power/2;		//¾ðµ¥µå 50%
				}

				//Å©¸®Æ¼ÄÃ Ã³¸®
				if ( lpTransRangeAttack->Critical[0] ) {
					if ( (rand()%100)<GetCritical( lpPlayInfo , lpChar , lpTransRangeAttack->Critical[0] ) ) {
						lpTransAttackData->Power = (lpTransAttackData->Power*170)/100;

/*#ifdef DISP_DAMAGE
///////////////////////// µð¹ö±×¿ë µ¥¹ÌÁö Àû¿ë Ãâ·Â //////////////////////
if ( lpPlayInfo->AdminMode>2 ) {
wsprintf( szDispDamage , ">%s °ø°Ý½Ãµµ ( Å©¸®Æ¼ÄÃ )" , lpChar->smCharInfo.szName );
rsDisplayDamgeToClient( lpPlayInfo , szDispDamage );
}
#endif*/

					}
				}
			}
			return TRUE;

		case SKILL_PLAY_STORM_JAVELIN:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;	//¾ÆÅ» Àü¿ë
			lpTransSkillAttackData->AttackSize = 340; // Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10) 300 -> 340
			pow = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			pow += (pow*Storm_Javelin_Damage[Point])/100;
			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;


		case SKILL_PLAY_EXTINCTION:		//ÀÍ½ºÆ¾¼Ç
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PRIESTESS ) return FALSE;	//ÇÁÆ¼ Àü¿ë
			lpTransSkillAttackData->Power = Point+1;
			lpTransSkillAttackData->AttackState = 6;
			return TRUE;

		case SKILL_PLAY_DIASTROPHISM:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MAGICIAN ) return FALSE;	//¸ÞÁö¼Ç Àü¿ë
			if ( lpTransRangeAttack->Power[0]<lpTransRangeAttack->Power2[0] || lpTransRangeAttack->Power[1]<lpTransRangeAttack->Power2[1] ) {
				//¹«±âµ¥¹ÌÁö ¿À·ù
				return FALSE;
			}

			lpTransSkillAttackData->AttackSize = Diastrophism_Area[Point];

			pow1 = Diastrophism_Damage[Point][0];
			pow2 = Diastrophism_Damage[Point][1];

			if ( lpPlayInfo->dwSkill_SpiritElemental_Time ) {		//½ºÇÇ¸´¿¤¸®¸àÅ» µ¥¹ÌÁö °¡Áß
				if ( lpPlayInfo->dwSkill_SpiritElemental_Time>dwPlayServTime ) {
					pow1 += (pow1*lpPlayInfo->dwSkill_SpiritElemental_Param)/100;
					pow2 += (pow2*lpPlayInfo->dwSkill_SpiritElemental_Param)/100;
				}
				else {
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}

			/*
			pow = GetRandomPos( 
				pow1+lpTransRangeAttack->Power2[0]+(lpTransRangeAttack->Critical[1]/8),
				pow2+lpTransRangeAttack->Power2[1]+(lpTransRangeAttack->Critical[1]/4) );
				*/
			

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			pow = GetRandomPos( 
				pow1 + (lpPlayInfo->smCharInfo.Level/2) + (lpTransRangeAttack->Critical[1]/6),
				pow2 + (lpPlayInfo->smCharInfo.Level/2) + (lpTransRangeAttack->Critical[1]/3) );



			lpTransSkillAttackData->Power = pow;
			lpTransSkillAttackData->AttackState = 0;

			return TRUE;


		///////////////////// 4Â÷½ºÅ³ /////////////////////

		case SKILL_PLAY_IMPULSION:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MECHANICIAN ) return FALSE;	//¸ÞÄ«´Ï¼Ç Àü¿ë

			//lpTransAttackData->Power = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			lpTransSkillAttackData->AttackSize = Impulsion_Range[Point];
			lpTransSkillAttackData->Power = GetRandomPos( Impulsion_LightingDamage[Point][0] , Impulsion_LightingDamage[Point][1] );
			lpTransSkillAttackData->AttackState = 101;
			return TRUE;

		case SKILL_PLAY_COMPULSION:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MECHANICIAN ) return FALSE;	//¸ÞÄ«´Ï¼Ç Àü¿ë
			lpTransSkillAttackData->AttackState = 201;
			lpTransSkillAttackData->AttackSize = Compulsion_Area[Point];

			lpPlayInfo->dwSkill_Compulsion_Time = dwPlayServTime+Compulsion_Time[Point]*1000;
			lpPlayInfo->dwSkill_Compulsion_Param = Compulsion_AddAbsorb[Point];

			return TRUE;

		case SKILL_PLAY_CYCLONE_STRIKE:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_FIGHTER ) return FALSE;
			if ( lpTransSkillAttackData->TargetCount>Cyclone_Strike_AttackNum[Point]+1 ) return FALSE;	//Å¸°Ù ¼öº¸´Ù ¸¹À½

			lpTransAttackData->Power = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			lpTransAttackData->Power+= (lpTransAttackData->Power*Cyclone_Strike_DamagePercent[Point])/100;
			lpTransSkillAttackData->AttackSize = Cyclone_Strike_Area[Point];
			lpTransSkillAttackData->Power = GetRandomPos( Cyclone_Strike_AreaDamage[Point][0] , Cyclone_Strike_AreaDamage[Point][1] );
			lpTransSkillAttackData->AttackState = 0;
			dm_Critical_Temp = lpTransRangeAttack->Critical[0];
			return TRUE;

		case SKILL_PLAY_PHOENIX_SHOT:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ARCHER ) return FALSE;

			lpTransSkillAttackData->Power = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			lpTransSkillAttackData->Power+= (lpTransSkillAttackData->Power*Phoenix_Shot_DamagePercent[Point])/100;
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;


		case SKILL_PLAY_SWORD_OF_JUSTICE:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_KNIGHT ) return FALSE;

			lpTransSkillAttackData->Power = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			lpTransSkillAttackData->Power+= (lpTransSkillAttackData->Power*Sword_Of_Justice_DamagePercent[Point])/100;
			lpTransSkillAttackData->AttackSize = Sword_Of_Justice_Area[Point];
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;

		case SKILL_PLAY_X_RAGE:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_ATALANTA ) return FALSE;

			lpTransSkillAttackData->Power = GetRandomPos( lpTransRangeAttack->Power[0] , lpTransRangeAttack->Power[1] );
			lpTransSkillAttackData->Power+= (lpTransSkillAttackData->Power*X_Rage_DamagePercent[Point])/100;
			lpTransSkillAttackData->AttackSize = X_Rage_Area[Point];
			lpTransSkillAttackData->AttackState = 0;
			return TRUE;

		case SKILL_PLAY_GLACIAL_SPIKE:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PRIESTESS ) return FALSE;

			/*
			pow1 = Glacial_Spike_Damage[Point][0]+lpTransRangeAttack->Critical[1]/8;
			pow2 = Glacial_Spike_Damage[Point][1]+lpTransRangeAttack->Critical[1]/4;

			pow1 += lpTransRangeAttack->Power2[0];
			pow2 += lpTransRangeAttack->Power2[1];
			*/

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			pow1 = Glacial_Spike_Damage[Point][0] + (lpTransRangeAttack->Critical[1]/6);
			pow2 = Glacial_Spike_Damage[Point][1] + (lpTransRangeAttack->Critical[1]/3);

			pow1 += (lpPlayInfo->smCharInfo.Level/2);
			pow2 += (lpPlayInfo->smCharInfo.Level/2);

			lpTransSkillAttackData->Power = GetRandomPos( pow1 , pow2 );
			lpTransSkillAttackData->AttackState = 3;
			return TRUE;;

		case SKILL_PLAY_CHAIN_LIGHTNING:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_PRIESTESS ) return FALSE;
			if ( lpTransSkillAttackData->TargetCount>Chain_Lightning_Num[Point] ) return FALSE;	//Å¸°Ù ¼öº¸´Ù ¸¹À½
			lpTransSkillAttackData->AttackSize = Chain_Lightning_Range[Point]*Chain_Lightning_Num[Point];

			/*
			pow1 = Chain_Lightning_Damage[Point][0]+lpTransRangeAttack->Critical[1]/8;
			pow2 = Chain_Lightning_Damage[Point][1]+lpTransRangeAttack->Critical[1]/4;

			pow1 += lpTransRangeAttack->Power2[0];
			pow2 += lpTransRangeAttack->Power2[1];
			*/

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			pow1 = Chain_Lightning_Damage[Point][0] + (lpTransRangeAttack->Critical[1]/6);
			pow2 = Chain_Lightning_Damage[Point][1] + (lpTransRangeAttack->Critical[1]/3);

			pow1 += (lpPlayInfo->smCharInfo.Level/3);
			pow2 += (lpPlayInfo->smCharInfo.Level/3);

			pow1 += (lpTransRangeAttack->Power2[0]/3);
			pow2 += (lpTransRangeAttack->Power2[1]/3);



			lpTransSkillAttackData->Power = GetRandomPos( pow1 , pow2 );

			lpTransSkillAttackData->AttackState = 101;		//Àü±â
			return TRUE;;

		case SKILL_PLAY_FLAME_WAVE:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MAGICIAN ) return FALSE;	//¸ÅÁö¼Ç Àü¿ë

			//lpTransSkillAttackData->AttackSize = FireBall_Area[Point];

			pow1 = Flame_Wave_FireDamage[Point][0];
			pow2 = Flame_Wave_FireDamage[Point][1];

			if ( lpPlayInfo->dwSkill_SpiritElemental_Time ) {		//½ºÇÇ¸´¿¤¸®¸àÅ» µ¥¹ÌÁö °¡Áß
				if ( lpPlayInfo->dwSkill_SpiritElemental_Time>dwPlayServTime ) {
					pow1 += ( pow1 * lpPlayInfo->dwSkill_SpiritElemental_Param )/100;
					pow2 += ( pow2 * lpPlayInfo->dwSkill_SpiritElemental_Param )/100;
				}
				else {
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}

			/*
			pow1 +=lpTransRangeAttack->Critical[1]/8;
			pow2 +=lpTransRangeAttack->Critical[1]/4;

			pow1 += lpTransRangeAttack->Power2[0];
			pow2 += lpTransRangeAttack->Power2[1];
			*/

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			pow1 += lpPlayInfo->smCharInfo.Level/2;
			pow2 += lpPlayInfo->smCharInfo.Level/2;

			pow1 +=lpTransRangeAttack->Critical[1]/6;
			pow2 +=lpTransRangeAttack->Critical[1]/3;

			pow = GetRandomPos( pow1 , pow2 );
			lpTransSkillAttackData->Power = pow;

			lpTransSkillAttackData->AttackState = 100;
			return TRUE;

		case SKILL_PLAY_DISTORTION:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MAGICIAN ) return FALSE;	//¸ÅÁö¼Ç Àü¿ë
			//¿Ö°î ±â´É

			lpTransSkillAttackData->AttackState = 7;		//¿Ö°î
			return TRUE;

		case SKILL_PLAY_METEO:
			if ( lpPlayInfo->smCharInfo.JOB_CODE!=JOBCODE_MAGICIAN ) return FALSE;	//¸ÅÁö¼Ç Àü¿ë

			lpTransSkillAttackData->AttackSize = Meteo_Area[Point];

			pow1 = Meteo_Damage[Point][0];
			pow2 = Meteo_Damage[Point][1];

			if ( lpPlayInfo->dwSkill_SpiritElemental_Time ) {		//½ºÇÇ¸´¿¤¸®¸àÅ» µ¥¹ÌÁö °¡Áß
				if ( lpPlayInfo->dwSkill_SpiritElemental_Time>dwPlayServTime ) {
					pow1 += ( pow1 * lpPlayInfo->dwSkill_SpiritElemental_Param )/100;
					pow2 += ( pow2 * lpPlayInfo->dwSkill_SpiritElemental_Param )/100;
				}
				else {
					lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
					lpPlayInfo->dwSkill_SpiritElemental_Param = 0;
				}
			}

			/*
			pow1 +=lpTransRangeAttack->Critical[1]/8;
			pow2 +=lpTransRangeAttack->Critical[1]/4;

			pow1 += lpTransRangeAttack->Power2[0];
			pow2 += lpTransRangeAttack->Power2[1];
			*/

			// Àåº° - ½ºÅ³¹ë·±½º Á¶Á¤(10.08.10)
			pow1 += lpPlayInfo->smCharInfo.Level/3; // Lv/3
			pow2 += lpPlayInfo->smCharInfo.Level/3; // Lv/3

			pow1 += lpTransRangeAttack->Power2[0]/3; // ¹«¹Î/3
			pow2 += lpTransRangeAttack->Power2[1]/3; // ¹«¸Æ/3

			pow1 +=lpTransRangeAttack->Critical[1]/6; //Á¤½Å/6
			pow2 +=lpTransRangeAttack->Critical[1]/3; //Á¤½Å/3

			pow = GetRandomPos( pow1 , pow2 );
			lpTransSkillAttackData->Power = pow;

			lpTransSkillAttackData->AttackState = 100;
			return TRUE;

	}

	return FALSE;
}

//¹üÀ§°ø°Ý ¼ö½Å ¹ÞÀ½
int rsRecvRangeAttackData( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA2 *lpTransRangeAttackData )
{

	TRANS_ATTACKDATA		TransAttackData;
	TRANS_SKIL_ATTACKDATA	TransSkillAttackData;
	smCHAR					*lpChar;
	smTRANS_COMMAND_EX	smTransCommand;

#ifdef _USE_DYNAMIC_ENCODE
	rsDecodeDamagePacket(lpPlayInfo, lpTransAttackData);						//Decryption
#else
	dm_DecodePacket(lpPlayInfo->dwObjectSerial, lpTransRangeAttackData);			//Decryption
#endif

	if ( lpTransRangeAttackData->dwChkSum!=dm_GetRangeDamgeChkSum(lpTransRangeAttackData) )	{	//ÆÐÅ¶°Ë»ç

		//µ¥¹ÌÁö µ¥ÀÌÅ¸ ¿À·ù¸¦ ±º¼­¹ö ·Î±×¿¡ ±â·Ï
		smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
		smTransCommand.size = sizeof( smTRANS_COMMAND );
		smTransCommand.WParam = 8500;
		smTransCommand.LParam = 2;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;

		rsRecordDamageError( lpPlayInfo , (smTRANS_COMMAND *)&smTransCommand );
		return FALSE;
	}


	if ( (lpTransRangeAttackData->SkillCode&0xFF)!=SKILL_PLAY_ENCHANT_WEAPON ) {		//ÀÎÃ¾Æ® ¿þÆù, ¼ø¼­°¡ ¹Ù²ð °¡´É¼º ¶«¿¡ Á¦¿Ü
		if ( lpTransRangeAttackData->AttackCount<=lpPlayInfo->DamagePacketCount || 
			lpTransRangeAttackData->dwTime<=lpPlayInfo->dwDamagePacketTime ) {
				//µ¥¹ÌÁö Å¬¶óÀÌ¾ðÆ® Ãø Ä«¿îÆÃ,½Ã°£ ¿À·ù
				return FALSE;
		}

		lpPlayInfo->DamagePacketCount = lpTransRangeAttackData->AttackCount;
		lpPlayInfo->dwDamagePacketTime = lpTransRangeAttackData->dwTime;
	}

	if ( lpTransRangeAttackData->Power[0]>lpPlayInfo->sLimitDamage[0] || 
		lpTransRangeAttackData->Power[1]>lpPlayInfo->sLimitDamage[1] ||
		lpTransRangeAttackData->Critical[0]>lpPlayInfo->sLimitCritical[0] ) {

			//µ¥¹ÌÁö µ¥ÀÌÅ¸ ¿À·ù¸¦ ±º¼­¹ö ·Î±×¿¡ ±â·Ï
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof( smTRANS_COMMAND_EX );
			smTransCommand.WParam = 8510;
			smTransCommand.WxParam = 1;

			smTransCommand.LParam = lpTransRangeAttackData->Power[0];
			smTransCommand.SParam = lpTransRangeAttackData->Power[1];
			smTransCommand.EParam = lpTransRangeAttackData->Critical[0];

			smTransCommand.LxParam = lpPlayInfo->sLimitDamage[0];
			smTransCommand.SxParam = lpPlayInfo->sLimitDamage[1];
			smTransCommand.ExParam = lpPlayInfo->sLimitCritical[0];

			rsRecordDamageError( lpPlayInfo , (smTRANS_COMMAND *)&smTransCommand );

#ifdef _LANGUAGE_KOREAN
			if ( lpPlayInfo->AdminMode ) {
				TRANS_CHATMESSAGE	TransChatMessage;

				wsprintf( TransChatMessage.szMessage , "°ø°Ý ¼öÄ¡¿À·ù ( %d %d %d ) ( %d %d %d )" ,
					lpTransRangeAttackData->Power[0] , lpTransRangeAttackData->Power[1] , lpTransRangeAttackData->Critical[0],
					lpPlayInfo->sLimitDamage[0] , lpPlayInfo->sLimitDamage[1] , lpPlayInfo->sLimitCritical[0] );

				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				lpPlayInfo->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
			}
#endif
			//Á¦ÇÑ °ø°Ý ¼öÄ¡ ÃÊ°ú º¸Á¤
			lpTransRangeAttackData->Power[0] = lpPlayInfo->sLimitDamage[0];
			lpTransRangeAttackData->Power[1] = lpPlayInfo->sLimitDamage[1];
			lpTransRangeAttackData->Critical[0] = lpPlayInfo->sLimitCritical[0];
	}


	TransAttackData.Power = 0;
	TransSkillAttackData.Power = 0;
	dm_SkillCode_Temp = 0;

	if ( lpTransRangeAttackData->dwMainTargetObject )
		lpChar = srFindCharFromSerial( lpTransRangeAttackData->dwMainTargetObject , lpTransRangeAttackData->Area[0] );
	else 
		lpChar = 0;


	if ( lpTransRangeAttackData->dwMainTargetObject ) {
		TransAttackData.AttackState = 0;
		TransAttackData.AttackSize = 64*64;
		TransAttackData.dwDestObjectSerial = lpTransRangeAttackData->dwDestObjectSerial;
		TransAttackData.x = lpTransRangeAttackData->x;
		TransAttackData.y = lpTransRangeAttackData->y;
		TransAttackData.z = lpTransRangeAttackData->z;
	}

	TransSkillAttackData.AttackSize = lpTransRangeAttackData->AttackSize;
	TransSkillAttackData.dwDestObjectSerial = lpTransRangeAttackData->dwDestObjectSerial;
	TransSkillAttackData.x = lpTransRangeAttackData->x;
	TransSkillAttackData.y = lpTransRangeAttackData->y;
	TransSkillAttackData.z = lpTransRangeAttackData->z;
	TransSkillAttackData.AttackSize = 200;

	if ( lpTransRangeAttackData->TargetCount>0 && lpTransRangeAttackData->TargetCount<SKIL_ATTACK_CHAR_MAX ) {
		memcpy( TransSkillAttackData.dwTarObjectSerial , lpTransRangeAttackData->dwTarObjectSerial , sizeof(DWORD)*lpTransRangeAttackData->TargetCount );
		TransSkillAttackData.TargetCount = lpTransRangeAttackData->TargetCount;
	}
	else
		TransSkillAttackData.TargetCount = 0;


	if ( rsSetSkillRangeAttack( lpPlayInfo , lpChar , &TransAttackData , &TransSkillAttackData , lpTransRangeAttackData )==FALSE ) 
		return FALSE;
	
	// ¹ÚÀç¿ø - ¸ÅÁ÷ Æ÷½º Ãß°¡, ºô¸µ ¸ÅÁ÷ Æ÷½º Ãß°¡(¹üÀ§°ø°Ý¿ë Æ÷½º¿Àºê ÆÄ¿ö¾÷)
	AddRangeForceOrbPower(lpPlayInfo, lpChar, &TransSkillAttackData, lpTransRangeAttackData->SkillCode, lpTransRangeAttackData->Power[0], lpTransRangeAttackData->Power[1]);

	//ºô¸µ¾ÆÀÌÅÛ½ºÅ³Àû¿ë
	int Total = TransSkillAttackData.TargetCount;
	int AvgPow;

	if ( lpChar ) Total+=1;
	if ( Total ) AvgPow = (TransAttackData.Power+TransSkillAttackData.Power*TransSkillAttackData.TargetCount)/Total;
	else AvgPow = 0;

	rsBillingItemSkill( lpPlayInfo , lpChar , Total , AvgPow , lpTransRangeAttackData->SkillCode&0xFF );

	if ( lpChar && TransAttackData.Power ) {
		//AddForceOrbPower(lpPlayInfo , lpChar ,  &TransAttackData , lpTransRangeAttackData->SkillCode );	//Æ÷½º¿Àºê °ø°Ý·Â Ãß°¡ 
		rsRecvAttackData_Old( lpPlayInfo , &TransAttackData , lpChar , TRUE );
	}

	if ( TransSkillAttackData.TargetCount>0 ) {
		RecvRangeAttack( lpPlayInfo , &TransSkillAttackData , lpTransRangeAttackData->Area[0] , lpTransRangeAttackData->SkillCode );


		// pluto PKÇã¿ë ÇÊµå ÀüºÎ
		if( rsServerConfig.Enable_PKField_All )
		{
			// pluto PKÇã¿ë ÇÊµå ÀüºÎ ¼öÁ¤
			if ( rsServerConfig.Enable_PK || lpPlayInfo->Position.Area < 11 && lpPlayInfo->Position.Area > 34 )
			{
				//ÇöÀç  PK Å×½ºÆ®Áß
				RecvRangeAttack_User( lpPlayInfo , &TransSkillAttackData , lpTransRangeAttackData->Area[0] , lpTransRangeAttackData->SkillCode );
			}
		}
		else
		{
			if ( rsServerConfig.Enable_PK || lpPlayInfo->Position.Area==rsCASTLE_FIELD || lpPlayInfo->Position.Area==rsServerConfig.Enable_PKField ) {
				//ÇöÀç  PK Å×½ºÆ®Áß
				RecvRangeAttack_User( lpPlayInfo , &TransSkillAttackData , lpTransRangeAttackData->Area[0] , lpTransRangeAttackData->SkillCode );
			}
		}
	}

	if ( lpPlayInfo->AdminMode ) {
		smTRANS_COMMAND	smTransCommand;

		smTransCommand.code = smTRANSCODE_DISP_DAMAGE;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = TransSkillAttackData.Power+TransAttackData.Power;
		smTransCommand.LParam = 0;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );
	}


	return TRUE;
}


/////////////////////////////////// ¾ÏÈ£È­ ¸ðµâ ///////////////////////////////////////////
//////////// º¸¾È Ã¶Àú ¿ä±¸ /////////////

/*
//¸ðµâ ³»¿ë - ¿ø·¡ ¼Ò½º
#define	DAMAGE_PACKET_KEY	0xBBAA3840
#define	DAMAGE_PACKET_MUL	0x11223344

int	dm_EncodePacket2( void *lpPacket )
{
	DWORD size,code;
	DWORD cnt,cnt2,cnt3;
	DWORD dwCode;
	DWORD *lpDword = (DWORD *)lpPacket;

	size = lpDword[0];
	code = lpDword[1];
	size /=4;


	dwCode = (code^(code<<7)) + size*DAMAGE_PACKET_MUL;
	cnt2 = (code+DAMAGE_PACKET_KEY)&0xF5ABCF;
	cnt3 = cnt2&0x3C;

	for( cnt=2;cnt<size;cnt++ ) {
		dwCode = dwCode^(cnt2<<6)^lpDword[cnt];
		lpDword[cnt] = dwCode;
		cnt2+=cnt2+cnt3;
	}

	return TRUE;
}

//µ¥¹ÌÁö ¾ÏÈ£ Ç®±â ÇÔ¼ö
int	dm_DecodeDamagePacket( rsPLAYINFO *lpPlayInfo , void *lpPacket )
{
	DWORD size,code;
	DWORD cnt,cnt2,cnt3;
	DWORD dwCode;
	DWORD dwCode2;
	DWORD *lpDword = (DWORD *)lpPacket;

	size = lpDword[0];
	code = lpDword[1];
	size /=4;

	dwCode = (code^(code<<5)) + size*0x00003434;
	cnt2 = (code+0x00008989)&0xBCAFF5;
	cnt3 = cnt2&0x5E;

	for( cnt=2;cnt<size;cnt++ ) {
		dwCode2 = lpDword[cnt];
		lpDword[cnt] = dwCode2^(cnt2<<7)^dwCode;
		dwCode = dwCode2;
		cnt2+=cnt2+cnt3;
	}

	return TRUE;
}
*/

#ifdef _W_SERVER

#define	DM_ENCODE_PACKET_SIZE	0x60
#define	DM_ENCODE_PACKET_KEY1	0x13
#define	DM_ENCODE_PACKET_KEY2	0x1F

BYTE dm_EncodePacket_AsmCode[DM_ENCODE_PACKET_SIZE] = {
	0x53, 0x56, 0x57, 0x8b, 0x7c, 0x24, 0x10, 0x8b, 0x37, 0x8b, 0x47, 0x04, 0xc1, 0xee, 0x02, 0x8b,
	0xd6, 0x69, 0xd2, 0x44, 0x33, 0x22, 0x11, 0x8b, 0xc8, 0xc1, 0xe1, 0x07, 0x33, 0xc8, 0x05, 0x40,
	0x38, 0xaa, 0xff, 0x25, 0xcf, 0xab, 0xf5, 0x00, 0x03, 0xca, 0x8b, 0xd8, 0xba, 0x02, 0x00, 0x00,
	0x00, 0x83, 0xe3, 0x3c, 0x3b, 0xf2, 0x76, 0x1e, 0x55, 0x8d, 0xa4, 0x24, 0x00, 0x00, 0x00, 0x00,
	0x8b, 0xe8, 0xc1, 0xe5, 0x06, 0x33, 0x2c, 0x97, 0x8d, 0x04, 0x43, 0x33, 0xcd, 0x89, 0x0c, 0x97,
	0x42, 0x3b, 0xd6, 0x72, 0xeb, 0x5d, 0x5f, 0x5e, 0xb8, 0x01, 0x00, 0x00, 0x00, 0x5b, 0xc3, 0x90
};

#define	DM_DECODE_PACKET_SIZE	0x70
#define	DM_DECODE_PACKET_KEY1	0x13
#define	DM_DECODE_PACKET_KEY2	0x1F

BYTE dm_DecodePacket_AsmCode[DM_DECODE_PACKET_SIZE] = {
	0x53,0x56,0x57,0x8b,0x7c,0x24,0x14,0x8b,0x37,0x8b,0x47,0x04,0xc1,0xee,0x02,0x8b,
	0xd6,0x69,0xd2,0x34,0x34,0x00,0x00,0x8b,0xc8,0xc1,0xe1,0x05,0x33,0xc8,0x05,0x89,
	0x89,0x00,0x00,0x25,0xf5,0xaf,0xbc,0x00,0x03,0xca,0x8b,0xd8,0xba,0x02,0x00,0x00,
	0x00,0x83,0xe3,0x5e,0x3b,0xf2,0x76,0x2a,0x55,0x8d,0xa4,0x24,0x00,0x00,0x00,0x00,
	0x8b,0x2c,0x97,0x89,0x6c,0x24,0x18,0x8b,0xe8,0xc1,0xe5,0x07,0x33,0x6c,0x24,0x18,
	0x8d,0x04,0x43,0x33,0xe9,0x8b,0x4c,0x24,0x18,0x89,0x2c,0x97,0x42,0x3b,0xd6,0x72,
	0xdf,0x5d,0x5f,0x5e,0xb8,0x01,0x00,0x00,0x00,0x5b,0xc3,0x90,0x90,0x90,0x90,0x90
};

//µ¥¹ÌÁö ¾ÏÈ£È­ Å°¼³Á¤
int rsSetDamagePacketKey( rsPLAYINFO *lpPlayInfo )
{
	DWORD	dwChkSum;
	DWORD	dwObjSum;

	if ( lpPlayInfo->szName[0] )
		dwChkSum = GetSpeedSum( lpPlayInfo->szName );
	else
		dwChkSum = GetSpeedSum( lpPlayInfo->smCharInfo.szName );

	dwObjSum = lpPlayInfo->dwObjectSerial;

	lpPlayInfo->dwDamagePacketKey[0] = (dwChkSum*dwObjSum/7)+0x13;
	lpPlayInfo->dwDamagePacketKey[1] = lpPlayInfo->dwDamagePacketKey[0]^((dwObjSum>>8)+(dwObjSum<<15))+0x1F;

	dwObjSum *= (lpPlayInfo->smCharInfo.JOB_CODE+2);
	lpPlayInfo->dwDamagePacketKey2[0] = (dwChkSum*dwObjSum/11)+0x34;
	lpPlayInfo->dwDamagePacketKey2[1] = lpPlayInfo->dwDamagePacketKey2[0]^((dwObjSum>>7)+(dwObjSum<<16))+0x37;

	return TRUE;
}

//µ¥¹ÌÁö ¾ÏÈ£È­ Æã¼ÇÀ» ÅëÃ¤·Î Å¬¶óÀÌ¾ðÆ®¿¡ º¸³½´Ù
int rsSendDamageFuncToClient( rsPLAYINFO *lpPlayInfo )
{
	TRANS_FUNC_MEMORY	TransFuncMemory;

	ZeroMemory( &TransFuncMemory, sizeof(TRANS_FUNC_MEMORY) );

	TransFuncMemory.size = DM_ENCODE_PACKET_SIZE+64+(rand()%3)*4;
	TransFuncMemory.code = smTRANSCODE_DAMAGE_ENCODE_MEM;

	TransFuncMemory.Param[0] = DM_ENCODE_PACKET_SIZE;

	memcpy( TransFuncMemory.szData , dm_EncodePacket_AsmCode , DM_ENCODE_PACKET_SIZE );

	rsSetDamagePacketKey( lpPlayInfo );			//ÆÐÅ¶ ¾ÏÈ£È­¿ë Å° ¼³Á¤

	((DWORD *)(TransFuncMemory.szData+DM_ENCODE_PACKET_KEY1))[0] = lpPlayInfo->dwDamagePacketKey[1];
	((DWORD *)(TransFuncMemory.szData+DM_ENCODE_PACKET_KEY2))[0] = lpPlayInfo->dwDamagePacketKey[0];

	if ( lpPlayInfo && lpPlayInfo->lpsmSock )
	{
		return lpPlayInfo->lpsmSock->Send2( (char *)&TransFuncMemory , TransFuncMemory.size , TRUE );
	}

	return FALSE;
}

//µ¥¹ÌÁö ¾ÏÈ£È­ Æã¼ÇÀ» ÅëÃ¤·Î Å¬¶óÀÌ¾ðÆ®¿¡ º¸³½´Ù
int rsSendDamageFuncToClient2( rsPLAYINFO *lpPlayInfo )
{
	TRANS_FUNC_MEMORY	TransFuncMemory;

	ZeroMemory( &TransFuncMemory, sizeof(TRANS_FUNC_MEMORY) );

	TransFuncMemory.size = DM_DECODE_PACKET_SIZE+64+(rand()%3)*4;
	TransFuncMemory.code = smTRANSCODE_DAMAGE_ENCODE_MEM2;

	TransFuncMemory.Param[0] = DM_DECODE_PACKET_SIZE;

	memcpy( TransFuncMemory.szData , dm_DecodePacket_AsmCode , DM_DECODE_PACKET_SIZE );

	rsSetDamagePacketKey( lpPlayInfo );			//ÆÐÅ¶ ¾ÏÈ£È­¿ë Å° ¼³Á¤

	((DWORD *)(TransFuncMemory.szData+DM_DECODE_PACKET_KEY1))[0] = lpPlayInfo->dwDamagePacketKey2[1];
	((DWORD *)(TransFuncMemory.szData+DM_DECODE_PACKET_KEY2))[0] = lpPlayInfo->dwDamagePacketKey2[0];

	if ( lpPlayInfo && lpPlayInfo->lpsmSock ) {
		return lpPlayInfo->lpsmSock->Send2( (char *)&TransFuncMemory , TransFuncMemory.size , TRUE );
	}

	return FALSE;
}

//¼ÒÄÏ ¾ÏÈ£È­ Æã¼ÇÀ» ÅëÃ¤·Î Å¬¶óÀÌ¾ðÆ®¿¡ º¸³½´Ù
int rsSendPacketFuncToClient( rsPLAYINFO *lpPlayInfo , DWORD dwEncPacketCode , BYTE bEncXor , BYTE bDecXor )
{

	TRANS_FUNC_MEMORY	TransFuncMemory;

	ZeroMemory( &TransFuncMemory, sizeof(TRANS_FUNC_MEMORY) );

	TransFuncMemory.size = ENC_PACKET_ASM_SIZE+64+(rand()%3)*4;
	TransFuncMemory.code = smTRANSCODE_PACKET_DYNFUNC;

	TransFuncMemory.Param[0] = ENC_PACKET_ASM_SIZE;
	TransFuncMemory.Param[1] = POS_ENC_START;
	TransFuncMemory.Param[2] = POS_DEC_START;

	memcpy( TransFuncMemory.szData , smwsock_EncodePacket_AsmCode , ENC_PACKET_ASM_SIZE );

	((DWORD *)(TransFuncMemory.szData+POS_ENC_PACCODE))[0]	= dwEncPacketCode;
	((BYTE *)(TransFuncMemory.szData+POS_ENC_XOR))[0]		= bEncXor;
	((BYTE *)(TransFuncMemory.szData+POS_DEC_XOR))[0]		= bDecXor;

	if ( lpPlayInfo && lpPlayInfo->lpsmSock ) {
		return lpPlayInfo->lpsmSock->Send2( (char *)&TransFuncMemory , TransFuncMemory.size , TRUE );
	}

	return FALSE;
}

#define	PACKET_SAFE_CODE		704
#define	PACKET_SAFE_SHIFT1		2
#define	PACKET_SAFE_SHIFT2		3


//¾ÏÈ£ ¸ðµâ ½ÃÇà
int	rsProcessSafePacket( rsPLAYINFO *lpPlayInfo )
{

	DWORD	dwChkSum;
	DWORD	dwObjSum;
	BYTE	bEncXor,bDecXor;
	DWORD	dwEncPacketCode;

	if ( !rsServerConfig.CrazyPacketMode ) return FALSE;

	if ( lpPlayInfo->szName[0] )
		dwChkSum = GetSpeedSum( lpPlayInfo->szName );
	else
		dwChkSum = GetSpeedSum( lpPlayInfo->smCharInfo.szName );

	dwObjSum = (lpPlayInfo->dwObjectSerial+PACKET_SAFE_CODE)*dwChkSum;

	dwEncPacketCode = (dwObjSum^dwChkSum)&0x0FFF0000;
	dwEncPacketCode |= smTRANSCODE_ENCODE_PACKET2;
	bEncXor = (BYTE)(dwObjSum^(dwChkSum>>PACKET_SAFE_SHIFT1))&0x7F;
	bDecXor = (BYTE)((dwObjSum>>PACKET_SAFE_SHIFT2)^dwChkSum)&0x7F;

	rsSendPacketFuncToClient( lpPlayInfo , dwEncPacketCode , bDecXor ,bEncXor );

	lpPlayInfo->dwDecPacketCode = dwEncPacketCode;
	lpPlayInfo->bPacketXor[0] = bEncXor;
	lpPlayInfo->bPacketXor[1] = bDecXor;

	lpPlayInfo->lpsmSock->dwEncPacketCode = smTRANSCODE_ENCODE_PACKET2;
	lpPlayInfo->lpsmSock->bEncXor = bEncXor;
	lpPlayInfo->lpsmSock->bDecXor = bDecXor;

	lpPlayInfo->dwDecPacketTime = dwPlayServTime;
	lpPlayInfo->dwDecPacketTime2 = dwPlayServTime+60000;		//1ºÐ µ¿¾È ¾ÏÈ£È­ »ç¿ë º¸·ù - °ø°Ý ÆÐÅ¶ÀÇ °æ¿ì

	return TRUE;
}

//¾ÏÈ£ ¸ðµâÀÎÁö È®ÀÎÇÏ¿© Àû¿ë
int	rsCompareSafePacket( rsPLAYINFO *lpPlayInfo , DWORD dwRcvPacketCode )
{
	DWORD	dwChkSum;
	DWORD	dwObjSum;
	BYTE	bEncXor,bDecXor;
	DWORD	dwEncPacketCode;

	if ( (dwRcvPacketCode>>28)!=9 ) return FALSE;

	if ( lpPlayInfo->szName[0] )
		dwChkSum = GetSpeedSum( lpPlayInfo->szName );
	else
		dwChkSum = GetSpeedSum( lpPlayInfo->smCharInfo.szName );

	dwObjSum = (lpPlayInfo->dwObjectSerial+PACKET_SAFE_CODE)*dwChkSum;

	dwEncPacketCode = (dwObjSum^dwChkSum)&0x0FFF0000;
	dwEncPacketCode |= smTRANSCODE_ENCODE_PACKET2;
	bEncXor = (BYTE)(dwObjSum^(dwChkSum>>PACKET_SAFE_SHIFT1))&0x7F;
	bDecXor = (BYTE)((dwObjSum>>PACKET_SAFE_SHIFT2)^dwChkSum)&0x7F;

	if ( dwRcvPacketCode==dwEncPacketCode ) {
		lpPlayInfo->dwDecPacketCode = dwEncPacketCode;
		lpPlayInfo->bPacketXor[0] = bEncXor;
		lpPlayInfo->bPacketXor[1] = bDecXor;

		lpPlayInfo->lpsmSock->dwEncPacketCode = smTRANSCODE_ENCODE_PACKET2;
		lpPlayInfo->lpsmSock->bEncXor = bEncXor;
		lpPlayInfo->lpsmSock->bDecXor = bDecXor;

		return TRUE;
	}

	return FALSE;
}

//µ¥¹ÌÁö ¾ÏÈ£ Ç®±â ÇÔ¼ö
int	rsDecodeDamagePacket( rsPLAYINFO *lpPlayInfo , void *lpPacket )
{
	DWORD size,code;
	DWORD cnt,cnt2,cnt3;
	DWORD dwCode;
	DWORD dwCode2;
	DWORD *lpDword = (DWORD *)lpPacket;

	size = lpDword[0];
	code = lpDword[1];
	size /=4;

	dwCode = (code^(code<<7)) + size*lpPlayInfo->dwDamagePacketKey[1];
	cnt2 = (code+lpPlayInfo->dwDamagePacketKey[0])&0xF5ABCF;
	cnt3 = cnt2&0x3C;

	for( cnt=2;cnt<size;cnt++ )
	{
		dwCode2 = lpDword[cnt];
		lpDword[cnt] = dwCode2^(cnt2<<6)^dwCode;
		dwCode = dwCode2;
		cnt2+=cnt2+cnt3;
	}

	return TRUE;
}

int	rsEncodeDamagePacket( rsPLAYINFO *lpPlayInfo , void *lpPacket )
{
	DWORD size,code;
	DWORD cnt,cnt2,cnt3;
	DWORD dwCode;
	DWORD *lpDword = (DWORD *)lpPacket;

	size = lpDword[0];
	code = lpDword[1];
	size /=4;


	dwCode = (code^(code<<5)) + size*lpPlayInfo->dwDamagePacketKey2[1];
	cnt2 = (code+lpPlayInfo->dwDamagePacketKey2[0])&0xBCAFF5;
	cnt3 = cnt2&0x5E;

	for( cnt=2;cnt<size;cnt++ ) 
	{
		dwCode = dwCode^(cnt2<<7)^lpDword[cnt];
		lpDword[cnt] = dwCode;
		cnt2+=cnt2+cnt3;
	}

	return TRUE;
}


#else

//µ¥¹ÌÁö ¾ÏÈ£È­ Å°¼³Á¤
int rsSetDamagePacketKey( rsPLAYINFO *lpPlayInfo )
{
	return TRUE;
}

//µ¥¹ÌÁö ¾ÏÈ£È­ Æã¼ÇÀ» ÅëÃ¤·Î Å¬¶óÀÌ¾ðÆ®¿¡ º¸³½´Ù
int rsSendDamageFuncToClient( rsPLAYINFO *lpPlayInfo )
{
	return TRUE;
}
//µ¥¹ÌÁö ¾ÏÈ£ Ç®±â ÇÔ¼ö
int	rsDecodeDamagePacket( rsPLAYINFO *lpPlayInfo , void *lpPacket )
{
	return TRUE;
}
int	rsEncodeDamagePacket( rsPLAYINFO *lpPlayInfo , void *lpPacket )
{
	return TRUE;
}

#endif



//µ¥¹ÌÁö µ¥ÀÌÅ¸ ¿À·ù¸¦ ±º¼­¹ö ·Î±×¿¡ ±â·Ï
int rsRecordDamageError( rsPLAYINFO *lpPlayInfo , smTRANS_COMMAND *lpTransCommand )
{

	if ( lpPlayInfo->WarningCount<20 ) {
		rsSendDataServer( lpPlayInfo->lpsmSock , lpTransCommand );
		lpPlayInfo->WarningCount++;
	}

	return TRUE;
}


//ATTACK_DAMAGE_LIST_MAX
/*
//µ¥¹ÌÁö¸¦ ÁØ À¯Àú¸¦ ±â¾ï½ÃÅ´
struct	ATTACK_DAMAGE_LIST	{
	DWORD	dwUserCode;
	int		DamageCount;
};
*/

//Ä³¸¯ÅÍ µ¥¹ÌÁö ±â·Ï
int	rsRecordCharDamage( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , int Damage )
{
	int cnt;
	int EmptyNum = -1;
	DWORD	dwClanCode;

	if ( lpChar->lpAttackDamageList_BlessCastle ) {
		//ºí·¹½º Ä³½½ Å©¸®½ºÅ» Å¸¿ö ( Å¬·£¼øÀ§ )
		if ( lpPlayInfo->dwClanCode && lpPlayInfo->Position.Area==rsCASTLE_FIELD ) {

			lpPlayInfo->sBlessCastle_Damage[0] += Damage;	//µ¥¹ÌÁö Á¤º¸ Ãß°¡

			for(cnt=0;cnt<ATTACK_DAMAGE_LIST_MAX;cnt++) {
				if ( lpChar->lpAttackDamageList_BlessCastle[cnt].dwUserCode ) {
					dwClanCode = GetClanCode(lpChar->lpAttackDamageList_BlessCastle[cnt].dwUserCode);
					if ( dwClanCode==lpPlayInfo->dwClanCode ) {
						lpChar->lpAttackDamageList_BlessCastle[cnt].DamageCount += Damage;
						lpChar->lpAttackDamageList_BlessCastle[cnt].Count ++;
						return TRUE;
					}
				}
				if ( EmptyNum<0 && lpChar->lpAttackDamageList_BlessCastle[cnt].dwUserCode==0 ) {
					EmptyNum = cnt;
				}

			}

			if ( EmptyNum>=0 ) {
				lpChar->lpAttackDamageList_BlessCastle[EmptyNum].dwUserCode = lpPlayInfo->smCharInfo.ClassClan;
				lpChar->lpAttackDamageList_BlessCastle[EmptyNum].DamageCount = Damage;
				lpChar->lpAttackDamageList_BlessCastle[EmptyNum].Count++;

				return TRUE;
			}
		}
		return TRUE;
	}

	if ( !lpChar->lpAttackDamageList ) return FALSE;

	if ( lpChar->smCharInfo.dwCharSoundCode==snCHAR_SOUND_CASTLE_TOWER_B ) {
		//¹ßÇÒ¶ó Å¾ ( Å¬·£¼øÀ§ )
		if ( lpPlayInfo->dwClanCode && lpPlayInfo->Position.Area==rsCASTLE_FIELD ) {

			lpPlayInfo->sBlessCastle_Damage[0] += Damage;	//µ¥¹ÌÁö Á¤º¸ Ãß°¡

			for(cnt=0;cnt<ATTACK_DAMAGE_LIST_MAX;cnt++) {
				if ( lpChar->lpAttackDamageList[cnt].dwUserCode ) {
					dwClanCode = GetClanCode(lpChar->lpAttackDamageList[cnt].dwUserCode);
					if ( dwClanCode==lpPlayInfo->dwClanCode ) {
						lpChar->lpAttackDamageList[cnt].DamageCount += Damage;
						lpChar->lpAttackDamageList[cnt].Count ++;
						return TRUE;
					}
				}
				if ( EmptyNum<0 && lpChar->lpAttackDamageList[cnt].dwUserCode==0 ) {
					EmptyNum = cnt;
				}

			}

			if ( EmptyNum>=0 ) {
				lpChar->lpAttackDamageList[EmptyNum].dwUserCode = lpPlayInfo->smCharInfo.ClassClan;
				lpChar->lpAttackDamageList[EmptyNum].DamageCount = Damage;
				lpChar->lpAttackDamageList[EmptyNum].Count++;

				return TRUE;
			}
		}
	}
	else {
		//ÀÏ¹Ý ¼øÀ§ (°³ÀÎ)
		for(cnt=0;cnt<ATTACK_DAMAGE_LIST_MAX;cnt++) {
			if ( lpChar->lpAttackDamageList[cnt].dwUserCode==lpPlayInfo->dwObjectSerial ) {
				lpChar->lpAttackDamageList[cnt].DamageCount += Damage;
				lpChar->lpAttackDamageList[cnt].Count ++;
				return TRUE;
			}
			if ( EmptyNum<0 && lpChar->lpAttackDamageList[cnt].dwUserCode==0 ) {
				EmptyNum = cnt;
			}
		}

		if ( EmptyNum>=0 ) {
			lpChar->lpAttackDamageList[EmptyNum].dwUserCode = lpPlayInfo->dwObjectSerial;
			lpChar->lpAttackDamageList[EmptyNum].DamageCount = Damage;
			lpChar->lpAttackDamageList[EmptyNum].Count++;

			return TRUE;
		}
	}

	return FALSE;
}

//Ä³¸¯ÅÍ PK ±â·Ï
int	rsRecord_PKDamage( rsPLAYINFO *lpPlayInfo , rsPLAYINFO *lpPlayInfo2 , int Damage )
{
	int cnt;
	ATTACK_DAMAGE_LIST *lpAttackDamageList = 0;
	DWORD dwClanCode;
	int EmptyNum = -1;


	if ( !lpPlayInfo2->dwClanCode || lpPlayInfo2->dwClanCode==lpPlayInfo->dwClanCode ) {
		if ( lpPlayInfo2->dwClanCode!=rsBlessCastle.dwMasterClan && lpPlayInfo->dwClanCode!=rsBlessCastle.dwMasterClan ) 
		{ 
			//°ø°Ý/Å¸°Ý ÀÚÀÇ Å¬·£ È®ÀÎÇÏ¿© °ø¼º³¢¸® ¼ö¼º³¢¸®´Â °ø°Ý ºÒ°¡
			return FALSE;
		}
	}

	if ( rsBlessCastle.lpAttackDamageList ) {
		lpAttackDamageList = rsBlessCastle.lpAttackDamageList;		//Å©¸®½ºÅ» Å¸¿ö °ø°ÝÁß
	}
	else if ( rsBlessCastle.lpChar_ValhallaTower ) {
		//¹ßÇÒ¶ó Å¸¿ö °ø°ÝÁß		
		if ( rsBlessCastle.lpChar_ValhallaTower->Flag && 
			rsBlessCastle.lpChar_ValhallaTower->smCharInfo.dwCharSoundCode==snCHAR_SOUND_CASTLE_TOWER_B &&
			rsBlessCastle.lpChar_ValhallaTower->smCharInfo.Life[0]>0 ) 
		{
			lpAttackDamageList = rsBlessCastle.lpChar_ValhallaTower->lpAttackDamageList;
		}
	}

	if ( !lpAttackDamageList ) return FALSE;

	Damage -= lpPlayInfo->smCharInfo.Absorption;			//Èí¼ö·Â Àû¿ë
	Damage /= PK_SCORE_DIVIDE;								//PK Á¡¼ö 1/10 °¨¼â
	if ( Damage<=0 ) {
		Damage = 1;
	}

	lpPlayInfo->sBlessCastle_Damage[0] += Damage;	//µ¥¹ÌÁö Á¤º¸ Ãß°¡

	// ( Å¬·£¼øÀ§ )
	if ( lpPlayInfo->dwClanCode && lpPlayInfo->Position.Area==rsCASTLE_FIELD ) {

		for(cnt=0;cnt<ATTACK_DAMAGE_LIST_MAX;cnt++) {
			if ( lpAttackDamageList[cnt].dwUserCode ) {
				dwClanCode = GetClanCode( lpAttackDamageList[cnt].dwUserCode);
				if ( dwClanCode==lpPlayInfo->dwClanCode ) {
					lpAttackDamageList[cnt].DamageCount += Damage;
					lpAttackDamageList[cnt].Count ++;
					return TRUE;
				}
			}
			if ( EmptyNum<0 && lpAttackDamageList[cnt].dwUserCode==0 ) {
				EmptyNum = cnt;
			}
		}
		if ( EmptyNum>=0 ) {
			lpAttackDamageList[EmptyNum].dwUserCode = lpPlayInfo->smCharInfo.ClassClan;
			lpAttackDamageList[EmptyNum].DamageCount = Damage;
			lpAttackDamageList[EmptyNum].Count++;

			return TRUE;
		}
	}

	return TRUE;
}


/*
#ifdef _LANGUAGE_KOREAN
			if ( lpPlayInfo->AdminMode ) {
				TRANS_CHATMESSAGE	TransChatMessage;

				wsprintf( TransChatMessage.szMessage , "°ø°Ý ¼öÄ¡¿À·ù ( %d %d %d ) ( %d %d %d )" ,
					lpTransAttackData->Power[0] , lpTransAttackData->Power[1] , lpTransAttackData->Critical[0],
					lpPlayInfo->sLimitDamage[0] , lpPlayInfo->sLimitDamage[1] , lpPlayInfo->sLimitCritical[0] );

				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				lpPlayInfo->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
			}
#endif
*/

//ºô¸µ ¾ÆÀÌÅÛ ½ºÅ³ Àû¿ë
int	rsBillingItemSkill( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , int HitMonsters , int Power , int SkillCode  )
{
	//int cnt,cps;
	float fps,fp1,fp2;
	smTRANS_COMMAND	smTransCommand;
//	TRANS_CHATMESSAGE	TransChatMessage;
	DWORD	dwServTime_T = (DWORD)tServerTime;

	if ( SkillCode==SKILL_PLAY_ROAR || SkillCode==SKILL_PLAY_METAL_GOLEM || SkillCode==SKILL_PLAY_COMPULSION || SkillCode==SKILL_PLAY_EXTINCTION ||
		SkillCode==SKILL_PLAY_RECALL_WOLVERIN || SkillCode==SKILL_PLAY_FIRE_ELEMENTAL || SkillCode==SKILL_PLAY_DISTORTION ||
		SkillCode==SKILL_PLAY_PET_ATTACK || SkillCode==SKILL_PLAY_PET_ATTACK2 || lpPlayInfo->Position.Area==rsCASTLE_FIELD )
	{
		return FALSE;
	}

	//ÇØ¿Ü ÀÓ½Ã
	if(!lpChar) return FALSE;

	if ( lpChar ) {
		if ( lpChar->smCharInfo.State==smCHAR_STATE_NPC || lpChar->smCharInfo.Brood==smCHAR_MONSTER_USER )
			return FALSE;
	}

	if ( lpPlayInfo->dwTime_PrimeItem_VampCuspid ) {
		if ( lpPlayInfo->dwTime_PrimeItem_VampCuspid>dwServTime_T ) {
			// pluto ¹ìÇÇ¸¯ Ä¿½ºÇÍ ¼öÄ¡ º¯°æ
			fp1 = float(lpPlayInfo->smCharInfo.Strength+(((float)Power)/10.0f))/20.0f;
			fp2 = (1.0f+(((float)HitMonsters)/10.0f));
			fps = fp1*fp2*HitMonsters+1.0f;

			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_VAMPRIC_CUSPID;
			smTransCommand.WParam =	(int)fps;
			smTransCommand.LParam =	0;								//
			smTransCommand.SParam =	0;
			smTransCommand.EParam = lpPlayInfo->dwObjectSerial;	//

			if ( smTransCommand.WParam )
				lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );


#ifdef _LANGUAGE_KOREAN
			TRANS_CHATMESSAGE	TransChatMessage;
			if ( lpPlayInfo->AdminMode>1 ) {
				wsprintf( TransChatMessage.szMessage , "¹ìÇÇ¸¯ Ä¿½ºÇÍ [%d] Stength(%d) HitMonsters(%d) Power(%d) <%d^%d> Time(%d)" ,
					smTransCommand.WParam,lpPlayInfo->smCharInfo.Strength,HitMonsters,Power , (int)fp1 , (int)fp2 , (lpPlayInfo->dwTime_PrimeItem_VampCuspid-dwServTime_T)/60 );

				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				lpPlayInfo->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
			}
#endif


		}
		else 
			lpPlayInfo->dwTime_PrimeItem_VampCuspid = 0;
	}


	// Àåº° - ¹ìÇÇ¸¯ Ä¿½ºÇÍ EX
	if ( lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX ) 
	{
		if ( lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX>dwServTime_T ) 
		{
			// ¹ìÇÇ¸¯ Ä¿½ºÇÍ EX ¼öÄ¡
			fp1 = float(lpPlayInfo->smCharInfo.Strength+(((float)Power)/10.0f))/15.0f;
			fp2 = (1.0f+(((float)HitMonsters)/7.0f));
			fps = fp1*fp2*HitMonsters+1.0f;

			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_VAMPRIC_CUSPID_EX;
			smTransCommand.WParam =	(int)fps;
			smTransCommand.LParam =	0;								//
			smTransCommand.SParam =	0;
			smTransCommand.EParam = lpPlayInfo->dwObjectSerial;	//

			if ( smTransCommand.WParam )
				lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );


#ifdef _LANGUAGE_JAPANESE 
			TRANS_CHATMESSAGE	TransChatMessage;
			if ( lpPlayInfo->AdminMode>1 ) 
			{
				wsprintf( TransChatMessage.szMessage , "VAMPRIC_CUSPID EX [%d] Stength(%d) HitMonsters(%d) Power(%d) <%d^%d> Time(%d)" ,
					smTransCommand.WParam,lpPlayInfo->smCharInfo.Strength,HitMonsters,Power , (int)fp1 , (int)fp2 , (lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX-dwServTime_T)/60 );

				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				lpPlayInfo->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
			}
#endif


		}
		else 
			lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX = 0;
	}


	if ( lpPlayInfo->dwTime_PrimeItem_ManaRecharg ) {
		if ( lpPlayInfo->dwTime_PrimeItem_ManaRecharg>dwServTime_T ) {
/*
			fps = float(lpPlayInfo->smCharInfo.Spirit+Power)/50+1;
			fp2 = (1.0f-((float)HitMonsters)/20.0f);
			cps = (int)fp2;
			for(cnt=0;cnt<cps;cnt++) {
				fps *= fps;
			}
*/
			// pluto ¸¶³ª ¸®Â÷Â¡ Æ÷¼Ç ¼öÄ¡ º¯°æ
			fp1 = float(lpPlayInfo->smCharInfo.Spirit+(((float)Power)/10.0f))/13.0f;
			fp2 = (1.0f+(((float)HitMonsters)/10.0f));
			fps = fp1*fp2*HitMonsters+1.0f;

			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_MANA_RECHARGING;
			smTransCommand.WParam =	(int)fps;
			smTransCommand.LParam =	0;								//
			smTransCommand.SParam =	0;
			smTransCommand.EParam = lpPlayInfo->dwObjectSerial;	//
			if ( smTransCommand.WParam )
				lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );

#ifdef _LANGUAGE_KOREAN
			TRANS_CHATMESSAGE	TransChatMessage;
			if ( lpPlayInfo->AdminMode>1 ) {
				wsprintf( TransChatMessage.szMessage , "¸¶³ª ¸®Â÷Â¡ [%d] Spirit(%d) HitMonsters(%d) Power(%d) <%d^%d> Time(%d)" ,
					smTransCommand.WParam,lpPlayInfo->smCharInfo.Spirit,HitMonsters,Power , (int)fp1 , (int)fp2 , (lpPlayInfo->dwTime_PrimeItem_ManaRecharg-dwServTime_T)/60 );

				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				lpPlayInfo->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
			}
#endif


		}
		else
			lpPlayInfo->dwTime_PrimeItem_ManaRecharg = 0;
	}


	return TRUE;
}

