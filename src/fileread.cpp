#include "common.h"

#include "smlib3d\\smd3d.h"
#include "smwsock.h"
#include "character.h"
#include "fileread.h"
#include "field.h"
#include "effectsnd.h"
#include "smreg.h"
#include "playmain.h"
#include "playsub.h"
#include "Language\\language.h"

#include "Server\\gamesql.h"
#include "Server\\onserver.h"

// 석지용 - 믹스쳐 리셋 (무특화 아이템을 위해 전역을 하나 만든다 ㅠ_ㅠ)
int	NotItemSpecial = 0;

extern	int	quit;

static char decode[512];
static char line[512];

//######################################################################################
//작 성 자 : 오 영 석
void ModelKeyWordEncode( DWORD dwFileCode, smMODELINFO *lpMODELINFO );
int  ModelKeyWordDecode( DWORD dwFileCode, smMODELINFO *lpMODELINFO );
void MotionKeyWordEncode( DWORD dwCode, smMODELINFO *lpMODELINFO );
int	 MotionKeyWordDecode( DWORD dwCode, smMODELINFO *lpMODELINFO );
//######################################################################################


//서버용 NPC 메세지 카운터
#ifdef	_W_SERVER
#define	SVR_NPC_MSG_MAX		1024
char	szSvr_NpcMsgs[SVR_NPC_MSG_MAX][256];
DWORD	dwSvr_NpcMsgCode[SVR_NPC_MSG_MAX];
#else
#define	SVR_NPC_MSG_MAX		32
char	szSvr_NpcMsgs[SVR_NPC_MSG_MAX][128];
DWORD	dwSvr_NpcMsgCode[SVR_NPC_MSG_MAX];
#endif

int		NpcMsgCount = 0;

//단축 글자
char	szShotCutMessage[10][100];



//NPC 용 대사 데이타 버퍼에 저장후 포인터 반환
char	*SetNPCMsg( char *szMsg )
{
	char	*lpMsg;
	DWORD	dwCode;
	int		cnt;

	if ( NpcMsgCount>=SVR_NPC_MSG_MAX ) return NULL;

	dwCode = GetSpeedSum(szMsg);

	for(cnt=0;cnt<NpcMsgCount;cnt++) {
		if ( dwCode==dwSvr_NpcMsgCode[cnt] && lstrcmp( szSvr_NpcMsgs[cnt] , szMsg )==0 ) {
			break;
		}
	}

	if ( cnt<NpcMsgCount ) {
		return szSvr_NpcMsgs[cnt];
	}

	dwSvr_NpcMsgCode[NpcMsgCount] = dwCode;
	lpMsg = szSvr_NpcMsgs[NpcMsgCount++];
	lstrcpy( lpMsg , szMsg );

	return lpMsg;
}


static char *GetWord(char *q , char *p)
{

//	while ( *p != '\n' ) {
		while ( (*p == 32) || (*p == 9) ) // SPACE or TAB or ':'는 제외 시킴
		{
			p++;
		}
	
		while ( (*p != 32) && (*p != 9) ) // SPACE or TAB
		{
			if ( *p == '\n' || *p=='\r' ) break;
			*q++ = *p++;
		}
		*q++ = 0;	// end of one string, put Null character
//	}
//	*q = '\n';

	return p;
}


char *szIniCommand[] = {
	"*동작파일",
	"*동작모음",
	"*모양파일",
	"*모양이름",
	"*파일연결",
	"*보조동작파일",

	"*정밀모양",
	"*보통모양",
	"*저질모양",

	"*XX걷는동작",
	"*XX서있기동작",

	"*착용무기",
	"*적용직업",
	"*해당위치",
	"*적용기술",

	//######################################################################################
	//작 성 자 : 오 영 석
	"*표정파일연결",
	"*표정파일",
	"*표정모음",
	//######################################################################################

	""
};

char *szIniRepeat = "반복";
char *szMotionWord = "동작";

char *szRunWord = "뛰는";
char *szStandWord = "*서있기";
char *szStandWord2 = "*정지";
char *szWalkWord = "*걷는";

char *szAttackWord = "공격";
char *szDeadWord = "죽기";
char *szDeadWord2 = "죽는";
char *szDamageWord = "타격";
char *szDamageWord2 = "데미지";
char *szDamageWord3 = "막기";

char *szWarpWord = "울기";
char *szWarpWord2 = "워프";

char *szSometimeWord = "가끔";

char *szFallDownWord = "떨어";
char *szFallStandLargeWord = "큰착지";
char *szFallStandSmallWord = "작은착지";

char *szRestartWord = "다시시작";
char *szEatWord = "먹기";
char *szSkillWord = "기술";
char *szYahooWord = "만세";

//######################################################################################
//작 성 자 : 오 영 석
char *szMotionTalkWord = "표정";

char *szArTalkWord = "아표정";
char *szETalkWord = "이표정";
char *szOhTalkWord = "오표정";
char *szEyeTalkWord = "눈깜빡표정";

char *szBlankTalkWord = "무표정(작동않함)";
char *szSmileTalkWord = "웃는표정";
char *szGrumbleTalkWord = "화난표정";
char *szSorrowTalkWord = "슬픈표정";
char *szStartledTalkWord = "놀란표정";
char *szNatureTalkWord = "고유표정";
char *szSpecialTalkWord = "특별표정";
//######################################################################################


JOBNAME_BIT BitMaskJobNames[] = {
	{	"Fighter"		,	0x0001	},
	{	"Mechanician"	,	0x0002	},
	{	"Archer"		,	0x0004	},
	{	"Pikeman"		,	0x0008	},

	{	"Atalanta"		,	0x0010	},
	{	"Knight"		,	0x0020	},
	{	"Magician"		,	0x0040	},
	{	"Priest"		,	0x0080	},

	{	"" , 0 },

	{	"PureBody"		,	0x0040	},
	{	"PureBody"		,	0x0080	},
	{	"PureBody"		,	0x0100	},
	{	"PureBody"		,	0x0200	},
	{	"PureBody"		,	0x0400	},
	{	"PureBody"		,	0x0800	},
	{	"PureBody"		,	0x1000	}
};


//######################################################################################
//작 성 자 : 오 영 석
//모델정모 동작 설정
int SetIniMotionInfo( smMOTIONINFO *motion, char *p, int *lpRate = NULL )
//######################################################################################
{
	char strBuff[256];
	int EventCount;

	EventCount = 0;

	//*걷는동작
	p = GetWord( strBuff , p );
	motion->StartFrame = atoi( strBuff );
	p = GetWord( strBuff , p );
	motion->EndFrame   = atoi( strBuff );

	motion->EventFrame[0] = 0;
	motion->EventFrame[1] = 0;
	motion->EventFrame[2] = 0;
	motion->EventFrame[3] = 0;

	while(1) {
		p = GetWord( strBuff , p );
		if ( strBuff[0]<'0' || strBuff[0]>'9' ) break;
		if ( EventCount>=4 ) break;

		motion->EventFrame[EventCount] = (atoi( strBuff )-motion->StartFrame) * 160;
		EventCount++;
	}

	//######################################################################################
	//작 성 자 : 오 영 석
	if( lstrcmp( strBuff, szIniRepeat ) == 0 )
	{
		motion->Repeat = TRUE;
	}
	//######################################################################################

	//######################################################################################
	//작 성 자 : 오 영 석
	if( strBuff[0] != '(' && strBuff[0] >= ' ' && strBuff[0] <= 0x7F ) 
		motion->KeyCode = strBuff[0];

	if( lpRate )
	{
		p = GetWord( strBuff, p );
		
		int  len = strlen(strBuff);
		char NumBuff[10] = {0,};

		if( len > 2 && len < 6 && strBuff[0] == '(' && strBuff[len-1] == ')'  )
		{
			::CopyMemory( NumBuff, &strBuff[1], len-2 );
			*lpRate = atoi( NumBuff );
			if( *lpRate > 100 )
				*lpRate = 100;
		}
	}
	//######################################################################################

	return TRUE;
}

static char *szFileExt = "inx";


//모델 정보 파일을 (Info에저장)
//######################################################################################
//작 성 자 : 오 영 석
int AddModelDecode( char *iniFile, smMODELINFO *Info )
//######################################################################################
{
	FILE	*fp;
	char	*szDirecotry;
	char strBuff[64];
	char *p;
	char *pb;
	int CmdNum;
	int cnt;
	_MODELGROUP	*lpModelGroup;
	int JobCount;

	char *szMotionFileList[128];

	int MotionFileListCnt;
	int MotionFrameList[100];
	smPAT3D	*pat3d;

	int MotionLastPos;

	MotionLastPos = 0;


	MotionFileListCnt = 0;
	ZeroMemory( MotionFrameList , sizeof( int )*100 );

	fp = fopen( iniFile , "rb" );
	if ( fp==NULL )
		return FALSE;

	//파일 이름으로 부터 디렉토리를 찾아 설정
	szDirecotry = SetDirectoryFromFile( iniFile );

	while( !feof( fp ) )//  feof: file end까지 읽어라 
	{
		if( fgets( line, 512, fp ) == NULL)	break;

		p = GetWord( decode , line);

		CmdNum = 0;

		while(1) {

			if ( lstrcmp( decode, szIniCommand[CmdNum] ) == 0 ) {
				break;
			}

			if ( szIniCommand[CmdNum][0]==NULL ) {
				//확장 모션
				if ( decode[0]=='*' && strstr( decode , szMotionWord ) ) {

					//######################################################################################
					//작 성 자 : 오 영 석
					if( Info->MotionCount < MOTION_INFO_MAX ) 
					{
						SetIniMotionInfo( &Info->MotionInfo[Info->MotionCount], p, 
										  &Info->NpcMotionRate[Info->MotionCount] );
					}
					//######################################################################################


					Info->MotionInfo[Info->MotionCount].MotionFrame = MotionFileListCnt;
					Info->MotionInfo[Info->MotionCount].State = TRUE;
	
					//달리기 모션
					if ( strstr( decode , szRunWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_RUN;
						Info->MotionInfo[Info->MotionCount].Repeat = TRUE;
					}

					//공격 모션
					if ( strstr( decode , szAttackWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_ATTACK;
					}
					//죽는 모션
					if ( strstr( decode , szDeadWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_DEAD;
					}
					//죽는 모션
					if ( strstr( decode , szDeadWord2 ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_DEAD;
					}

					//타격 모션
					if ( strstr( decode , szDamageWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_DAMAGE;
					}
					//타격 모션
					if ( strstr( decode , szDamageWord2 ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_DAMAGE;
					}
					//타격 모션
					if ( strstr( decode , szDamageWord3 ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_DAMAGE;
					}
					//가끔하는 모션
					if ( strstr( decode , szSometimeWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_SOMETIME;
					}

					//떨어지는 모션
					if ( strstr( decode , szFallDownWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_FALLDOWN;
					}
					//착지 모션
					if ( strstr( decode , szFallStandSmallWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_FALLSTAND;
					}
					//충격적인 착지 모션
					if ( strstr( decode , szFallStandLargeWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_FALLDAMAGE;
					}

					//서있는 모션
					if ( strstr( decode , szStandWord ) || strstr( decode , szStandWord2 ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_STAND;
						Info->MotionInfo[Info->MotionCount].Repeat = TRUE;
					}
					//걷는 모션
					if ( strstr( decode , szWalkWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_WALK;
						Info->MotionInfo[Info->MotionCount].Repeat = TRUE;
					}
					//다시 시작 모션
					if ( strstr( decode , szRestartWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_RESTART;
					}
					//물약먹기
					if ( strstr( decode , szEatWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_EAT;
					}
					//기술동작
					if ( strstr( decode , szSkillWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_SKILL;
						Info->MotionInfo[Info->MotionCount].SkillCodeList[0] = 0;
					}

					//기술동작
					if ( strstr( decode , szWarpWord ) || strstr( decode , szWarpWord2 ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_WARP;
					}

					//만세동작
					if ( strstr( decode , szYahooWord ) ) {
						Info->MotionInfo[Info->MotionCount].State = CHRMOTION_STATE_YAHOO;
					}

					//죽는 모션 끝 프레임 보정 ( 권호씨가 준 프레임땜 )
					if ( Info->MotionInfo[Info->MotionCount].State==CHRMOTION_STATE_DEAD ) {
						Info->MotionInfo[Info->MotionCount].EndFrame -= 8;
					}

/*
char *szFallDownWord = "떨어";
char *szFallStandLargeWord = "큰착지";
char *szFallStandSmallWord = "작은착지";

#define CHRMOTION_STATE_FALLDOWN	0x140
#define CHRMOTION_STATE_FALLSTAND	0x150
#define CHRMOTION_STATE_FALLDAMAGE	0x160
*/

					MotionLastPos = Info->MotionCount;
					Info->MotionCount++;
				}
				//######################################################################################
				//작 성 자 : 오 영 석
				else if( decode[0]=='*' && strstr(decode, szMotionTalkWord) && MotionFileListCnt )
				{
					if ( Info->TalkMotionCount < TALK_MOTION_INFO_MAX )
					{
						SetIniMotionInfo( &Info->TalkMotionInfo[Info->TalkMotionCount], p,
										  &Info->TalkMotionRate[ Info->TalkMotionCount ] );
					}

					Info->TalkMotionInfo[ Info->TalkMotionCount ].MotionFrame = MotionFileListCnt-1;

					// 아표정
					if( strstr(decode, szArTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_AR;
					// 이표정
					else if( strstr(decode, szETalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_E;
					// 오표정
					else if( strstr(decode, szOhTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_OH;
					// 눈깜빡표정
					else if( strstr(decode, szEyeTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_EYE;
					// 무표정(작동않함)
					else if( strstr(decode, szBlankTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_BLANK;
					// 웃는표정
					else if( strstr(decode, szSmileTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_SMILE;
                    // 화난표정
					else if( strstr(decode, szGrumbleTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_GRUMBLE;
					// 슬픈표정
					else if( strstr(decode, szSorrowTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_SORROW;
					// 놀란표정
					else if( strstr(decode, szStartledTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_STARTLED;
					// 고유표정
					else if( strstr(decode, szNatureTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_NATURE;
					// 특별표정
					else if( strstr(decode, szSpecialTalkWord) )
						Info->TalkMotionInfo[Info->TalkMotionCount].State = CHRMOTION_STATE_TALK_SPECIAL;

					Info->TalkMotionCount++;
				}
				//######################################################################################
				break;
			}

			CmdNum++;
		}



		switch( CmdNum ) {
		case 0:
			//동작 파일
			pb = p;
			p = GetWord( strBuff , p );
			if ( strBuff[0]==34 ) {	//따옴표 발견
				p = GetString( strBuff , pb );
			}
			lstrcpy( Info->szMotionFile , szDirecotry );
			lstrcat( Info->szMotionFile , strBuff );
			break;

		//######################################################################################
		//작 성 자 : 오 영 석
		case 17:	// 표정모음
		//######################################################################################

		case 1:
			//동작모음
			pb = p;
			p = GetWord( strBuff , p );
			if ( strBuff[0]==34 ) {	//따옴표 발견
				p = GetString( strBuff , pb );
			}
			szMotionFileList[ MotionFileListCnt ] = new char [64];
			lstrcpy( szMotionFileList[ MotionFileListCnt ] , szDirecotry );
			lstrcat( szMotionFileList[ MotionFileListCnt ] , strBuff );
			MotionFileListCnt++;
			break;

		case 2:
			//모양 파일
			p = GetWord( strBuff , p );
			lstrcpy( Info->szModelFile , szDirecotry );
			lstrcat( Info->szModelFile , strBuff );
			break;

		case 3:
			//모양 이름
			pb = p;
			p = GetWord( strBuff , p );
			if ( strBuff[0]==34 ) {	//따옴표 발견
				p = GetString( strBuff , pb );
			}

			//lstrcpy( Info->szModelName , strBuff );
			break;

		case 4:
			//"*동작연결파일",
			p = GetWord( strBuff , p );
			//######################################################################################
			//작 성 자 : 오 영 석
			lstrcpy( Info->szLinkFile , szDirecotry );
			lstrcat( Info->szLinkFile , strBuff );
			break;
			//######################################################################################

		case 5:
			//"*보조동작파일",
			pb = p;
			p = GetWord( strBuff , p );
			if ( strBuff[0]==34 ) {	//따옴표 발견
				p = GetString( strBuff , pb );
			}
			
			//######################################################################################
			//작 성 자 : 오 영 석
			lstrcpy( Info->szSubModelFile , szDirecotry );
			lstrcat( Info->szSubModelFile , strBuff );
			//######################################################################################
			break;

		case 6:
		case 7:
		case 8:

			switch(CmdNum) {
			case 6:
				//정밀 모양
				lpModelGroup = &Info->HighModel;
				break;
			case 7:
				lpModelGroup = &Info->DefaultModel;
				break;
			case 8:
				lpModelGroup = &Info->LowModel;
				break;
			}

			for(cnt=0;cnt<4;cnt++) {
				pb = p;
				p = GetWord( strBuff , p );
				if ( !strBuff[0] ) break;

				if ( strBuff[0]==34 ) {	//따옴표 발견
					p = GetString( strBuff , pb );
				}
				if ( lpModelGroup->ModelNameCnt<4 ) {
					lstrcpy( lpModelGroup->szModelName[ lpModelGroup->ModelNameCnt++ ] , strBuff );
				}
			}
			break;

		case 9:
			//*걷는동작
			//SetIniMotionInfo( &Info->MotionInfo[CHRMOTION_WALK] , p );
			//Info->MotionInfo[CHRMOTION_WALK].MotionFrame = MotionFileListCnt;
			break;
		case 10:
			//*서있기동작
			//SetIniMotionInfo( &Info->MotionInfo[CHRMOTION_STAND] , p );
			//Info->MotionInfo[CHRMOTION_STAND].MotionFrame = MotionFileListCnt;
			break;


/*
		case 11:
			//*점프동작
			SetIniMotionInfo( &Info->MotionInfo[CHRMOTION_JUMP] , p );
			Info->MotionInfo[CHRMOTION_JUMP].MotionFrame = MotionFileListCnt;
			break;
		case 12:
			//*공격동작
			SetIniMotionInfo( &Info->MotionInfo[CHRMOTION_ATTACK] , p );
			Info->MotionInfo[CHRMOTION_ATTACK].MotionFrame = MotionFileListCnt;
			break;
*/

		case 11:
			//"*착용무기",
			while(1) 
			{
				if ( p[0]==0 ) 
					break;

				strBuff[0] = 0;
				p = GetWord( strBuff , p );
				if ( strBuff[0] ) 
				{
					if ( lstrcmp( strBuff , "모두" )==0 )
					{
						Info->MotionInfo[MotionLastPos].ItemCodeCount = 0; 
						break; 
					}

					if ( lstrcmp( strBuff , "없음" )==0 ) 
					{
						Info->MotionInfo[MotionLastPos].ItemCodeList[Info->MotionInfo[MotionLastPos].ItemCodeCount++] = 0xFF;
					}
					else 
					{
						//코드검색 하여 설정
						for(cnt=0;cnt<MAX_ITEM;cnt++) 
						{
							if ( lstrcmp( strBuff , sItem[cnt].LastCategory )==0 ) 
							{
								Info->MotionInfo[MotionLastPos].ItemCodeList[Info->MotionInfo[MotionLastPos].ItemCodeCount++] = cnt;
								break;
							}
						}
					}

				}
				else
					break;
			}

			break;
		case 12:
			//"*적용직업",
//			if ( Info->MotionInfo[MotionLastPos].State!=CHRMOTION_STATE_SKILL ) {
				Info->MotionInfo[MotionLastPos].dwJobCodeBit = 0;
				while(1) {
					p = GetWord( strBuff , p );
					if ( strBuff[0]==0 ) break;
					JobCount = 0;
					while(1) {
						if ( !BitMaskJobNames[JobCount].dwBitMask ) break;
						if ( lstrcmpi( strBuff , BitMaskJobNames[JobCount].szName )==0 ) {
							Info->MotionInfo[MotionLastPos].dwJobCodeBit |= BitMaskJobNames[JobCount].dwBitMask;
							break;
						}
						JobCount++;
					}
				}
//			}
			break;
		case 13:
			//"*해당위치",
			p = GetWord( strBuff , p );
			cnt = 0;

			if ( lstrcmp( strBuff, "마을" )==0 ) {
					cnt |= 1;
			}
			if ( lstrcmp( strBuff, "필드" )==0 ) {
					cnt |= 2;
			}

			p = GetWord( strBuff , p );
			if ( strBuff[0] ) {
				if ( lstrcmp( strBuff, "마을" )==0 ) {
						cnt |= 1;
				}
				if ( lstrcmp( strBuff, "필드" )==0 ) {
						cnt |= 2;
				}
			}

			if ( cnt==0 || Info->MotionInfo[MotionLastPos].State==CHRMOTION_STATE_SKILL ) 
				cnt=3; 

			Info->MotionInfo[MotionLastPos].MapPosition = cnt;
			break;

		case 14:
			//"*적용기술",
			if ( Info->MotionInfo[MotionLastPos].State==CHRMOTION_STATE_SKILL ) {
				JobCount = 0;
				while(1) {
					p = GetWord( strBuff , p );
					if ( strBuff[0]==0 ) break;
					cnt = 0;
					while(1) {
						if ( !SkillDataCode[cnt].szSkillName[0] ) 
							break;
						if ( JobCount>=(MOTION_SKIL_MAX-1) ) break;
						if ( lstrcmpi( SkillDataCode[cnt].szSkillName , strBuff )==0 ) {
							Info->MotionInfo[MotionLastPos].SkillCodeList[JobCount++] = cnt;
							break;
						}
						cnt++;
					}
				}
				Info->MotionInfo[MotionLastPos].SkillCodeList[JobCount] = 0;
			}
			break;

		//######################################################################################
		//작 성 자 : 오 영 석
		case 15:	//"*표정파일연결"	(파일연결)
			pb = p;
			p = GetWord( strBuff, p );
			if( strBuff[0] == 34 )	//따옴표 발견
				p = GetString( strBuff , pb );

			//######################################################################################
			//작 성 자 : 오 영 석
			lstrcpy( Info->szTalkLinkFile, szDirecotry );
			lstrcat( Info->szTalkLinkFile, strBuff );
			//######################################################################################
			break;

		case 16:	//"*표정파일"
			pb = p;
			p = GetWord( strBuff, p );
			if( strBuff[0] == 34 )	//따옴표 발견
				p = GetString( strBuff , pb );

			//######################################################################################
			//작 성 자 : 오 영 석
			lstrcpy( Info->szTalkMotionFile, szDirecotry );
			lstrcat( Info->szTalkMotionFile, strBuff );
			break;
			//######################################################################################
		//######################################################################################

		}
	}

	fclose(fp);


	//######################################################################################
	//작 성 자 : 오 영 석
	int MaxRateNum, MaxRatePos;

	// NpcMotionRate
	if( Info->NpcMotionRate[ CHRMOTION_EXT ] )
	{
		///////////////////////////////////////////////////////////////
		// 예외 처리. ( 글픽에서 제대로 셋팅 해야 함. )
		MaxRateNum = MaxRatePos = CmdNum = 0;
		for( cnt=CHRMOTION_EXT; cnt < (int)Info->MotionCount; cnt++ )
		{
			if( MaxRateNum < Info->NpcMotionRate[ cnt ] )
			{
				MaxRateNum = Info->NpcMotionRate[ cnt ];
				MaxRatePos = cnt;
			}
			
            CmdNum += Info->NpcMotionRate[ cnt ];
		}
		
		if( CmdNum > 100 )
		{
			MaxRateNum -= (CmdNum - 100);
			if( MaxRateNum <= 0 )
			{
				// 대책 없는 버그 발생인디. ㅡ_ㅡ 
				// 작동 하지 않게끔 셋팅.
                Info->NpcMotionRate[ CHRMOTION_EXT ] = 0;
			}
			else
				Info->NpcMotionRate[ MaxRatePos ] = MaxRateNum;
		}
		else if( CmdNum < 100 )
		{
			MaxRateNum += (100 - CmdNum);
            Info->NpcMotionRate[ MaxRatePos ] = MaxRateNum;
		}
		///////////////////////////////////////////////////////////////

		if( Info->NpcMotionRate[ CHRMOTION_EXT ] )
		{
			MaxRatePos = 0;
			for( cnt=CHRMOTION_EXT; cnt < (int)Info->MotionCount; cnt++ )
			{
				for( CmdNum=0; CmdNum < Info->NpcMotionRate[ cnt ]; CmdNum++ )
				{
					Info->NpcMotionRateCnt[ MaxRatePos ] = cnt;
					MaxRatePos++;
				}
			}
		}
	}

	// TalkMotionRate
	if( Info->TalkMotionRate[ CHRMOTION_EXT ] )
	{
		///////////////////////////////////////////////////////////////
		//
		int MotionCntBuff[ TALK_MOTION_FILE_MAX ][ TALK_MOTION_INFO_MAX ] = {0,};
		int RateBuff[ TALK_MOTION_FILE_MAX ][ TALK_MOTION_INFO_MAX ] = {0,};
		int RateCnt[ TALK_MOTION_FILE_MAX ] = { CHRMOTION_EXT, CHRMOTION_EXT };

		for( cnt=CHRMOTION_EXT; cnt < (int)Info->TalkMotionCount; cnt++ )
		{
			if( Info->TalkMotionInfo[cnt].MotionFrame == TALK_MOTION_FILE )
			{
				MotionCntBuff[ TALK_MOTION_FILE ][ RateCnt[TALK_MOTION_FILE] ] = cnt;
				RateBuff[ TALK_MOTION_FILE ][ RateCnt[TALK_MOTION_FILE] ] = Info->TalkMotionRate[cnt];
				RateCnt[ TALK_MOTION_FILE ]++;
			}
			else if( Info->TalkMotionInfo[cnt].MotionFrame == FACIAL_MOTION_FILE )
			{
				MotionCntBuff[ FACIAL_MOTION_FILE ][ RateCnt[FACIAL_MOTION_FILE] ] = cnt;
				RateBuff[ FACIAL_MOTION_FILE ][ RateCnt[FACIAL_MOTION_FILE] ] = Info->TalkMotionRate[cnt];
				RateCnt[FACIAL_MOTION_FILE]++;
			}
		}
		///////////////////////////////////////////////////////////////

		//
		for( int loop=0; loop < TALK_MOTION_FILE_MAX; loop++ )
		{
			///////////////////////////////////////////////////////////////
			// 예외 처리. ( 글픽에서 제대로 셋팅 해야 함. )
			MaxRateNum = MaxRatePos = CmdNum = 0;

			int *lpRateBuff = RateBuff[ loop ];
			for( cnt=CHRMOTION_EXT; cnt < RateCnt[ loop ]; cnt++ )
			{
				if( MaxRateNum < lpRateBuff[cnt] )
				{
					MaxRateNum = lpRateBuff[cnt];
					MaxRatePos = cnt;
				}
				
				CmdNum += lpRateBuff[ cnt ];
			}

			if( CmdNum > 100 )
			{
				MaxRateNum -= (CmdNum - 100);
				if( MaxRateNum <= 0 )
				{
					// 대책 없는 버그 발생인디. ㅡ_ㅡ 
					// 작동 하지 않게끔 셋팅.
					Info->TalkMotionRate[ CHRMOTION_EXT ] = 0;
				}
				else
					lpRateBuff[ MaxRatePos ] = MaxRateNum;
			}
			else if( CmdNum < 100 )
			{
				MaxRateNum += (100 - CmdNum);
				lpRateBuff[ MaxRatePos ] = MaxRateNum;
			}
			///////////////////////////////////////////////////////////////

			if( Info->TalkMotionRate[ CHRMOTION_EXT ] )
			{
				MaxRatePos = 0;
				for( cnt=CHRMOTION_EXT; cnt < RateCnt[ loop ]; cnt++ )
				{
					for( CmdNum=0; CmdNum < lpRateBuff[ cnt ]; CmdNum++ )
					{
						Info->TalkMotionRateCnt[ loop ][ MaxRatePos ] = MotionCntBuff[ loop ][ cnt ];
						MaxRatePos++;
					}
				}
			}
		}
	}
	//######################################################################################


	//모션 파일 없구 .. 동작 모음만 있으면..모션 생성
	//######################################################################################
	//작 성 자 : 오 영 석
	if( MotionFileListCnt )
	//if( MotionFileListCnt > 1 )
	{
		if( smFindPatFile( Info->szMotionFile, "smb" ) == FALSE )
		{
			pat3d = smASE_MergeBone( Info->szMotionFile, szMotionFileList, MotionFileListCnt );
			if ( pat3d ) delete pat3d;
		}
		else if( smFindPatFile( Info->szTalkMotionFile, "smb" ) == FALSE )
		{
			pat3d = smASE_MergeBone( Info->szTalkMotionFile, szMotionFileList, MotionFileListCnt, 0 );
			if ( pat3d ) delete pat3d;
		}

		for(cnt=MotionFileListCnt-1;cnt>=0;cnt--) 
			delete szMotionFileList[cnt];
	}
	//######################################################################################


#ifndef _W_SERVER
		if ( !smConfig.DebugMode ) {
			quit = TRUE;
			return TRUE;
		}
#endif

	//######################################################################################
	//작 성 자 : 오 영 석
	char  *szFile = ChangeFileExt( iniFile, szFileExt );
	DWORD  dwCode = GetSpeedSum( szFile );
	ModelKeyWordEncode( dwCode, Info );

	//
	if( Info->MotionCount > CHRMOTION_EXT && Info->TalkMotionCount <= CHRMOTION_EXT )
		MotionKeyWordEncode( dwCode, Info );

	//모션 파일 저장
	szFile = ChangeFileExt( iniFile, szFileExt );	//필히 다시 해야 함.!! 버퍼가 하나이기에.!
	fp = fopen( szFile , "wb" );
	if( fp )
	{
		fwrite( Info , sizeof( smMODELINFO ) , 1, fp);
		fclose(fp);
	}

	//
	if( Info->MotionCount > CHRMOTION_EXT && Info->TalkMotionCount <= CHRMOTION_EXT )
		MotionKeyWordDecode( dwCode, Info );
	//######################################################################################

	return TRUE;
}


//모델 정보 파일을 해독하여 돌려준다 (Info에저장)
//######################################################################################
//작 성 자 : 오 영 석
int smModelDecode( char *iniFile , smMODELINFO *Info )
{
	char  szFile[64];
	DWORD dwFileLen;
	char *lpFile;
	FILE *fp;


	smMODELINFO	smModelInfo;
	ZeroMemory( Info, sizeof( smMODELINFO ) );

	Info->TalkMotionCount = CHRMOTION_EXT;	

	Info->MotionCount = CHRMOTION_EXT;
	Info->HighModel.ModelNameCnt = 0;
	Info->DefaultModel.ModelNameCnt = 0;
	Info->LowModel.ModelNameCnt = 0;

	int	len = lstrlen(iniFile);

	//ASE If you put the file directly
	if ( iniFile[len-4]=='.' && (iniFile[len-3]=='a' || iniFile[len-3]=='A' ) && (iniFile[len-2]=='s' || iniFile[len-2]=='S' ) && (iniFile[len-1]=='e' || iniFile[len-1]=='E' ) ) 
	{
		lstrcpy( Info->szModelFile , iniFile );
		return TRUE;
	}

	//
	for( int i=0; i < 3; i++ )
	{
		switch( i )
		{
		case 0:
			lstrcpy( szFile, iniFile );
			break;

		case 1:
			lstrcpy( szFile, Info->szLinkFile );
			break;

		case 2:
			lstrcpy( szFile, Info->szTalkLinkFile );
			break;
		}

		if( szFile[0] )
		{
			lpFile = smFindFile( szFile , szFileExt , &dwFileLen );
			if( lpFile && dwFileLen == sizeof(smMODELINFO) )
			{
				fp = fopen( lpFile, "rb" );
				if( fp )
				{
					ZeroMemory( &smModelInfo, sizeof( smMODELINFO ) );
					fread( &smModelInfo, sizeof( smMODELINFO ) , 1, fp );
					fclose(fp);

					DWORD dwCode = GetSpeedSum( lpFile );
					if( ModelKeyWordDecode( dwCode, &smModelInfo ) == FALSE )
						return FALSE;

					if( Info->szModelFile[0] && i > 0 )
					{
						if( smModelInfo.MotionCount > CHRMOTION_EXT && i == 1 )
						{
							if( MotionKeyWordDecode(dwCode, &smModelInfo) == FALSE )
								return FALSE;

							//
							lstrcpy( Info->szMotionFile, smModelInfo.szMotionFile );
							CopyMemory( Info->MotionInfo, smModelInfo.MotionInfo, sizeof(smModelInfo.MotionInfo) );
							Info->MotionCount = smModelInfo.MotionCount;

							//
							CopyMemory( Info->NpcMotionRate, smModelInfo.NpcMotionRate, sizeof(smModelInfo.NpcMotionRate) );
							CopyMemory( Info->NpcMotionRateCnt, smModelInfo.NpcMotionRateCnt, sizeof(smModelInfo.NpcMotionRateCnt) );							
						}
						else if( smModelInfo.TalkMotionCount > CHRMOTION_EXT && i == 2 )
						{
							//
							lstrcpy( Info->szTalkLinkFile, smModelInfo.szTalkLinkFile );
							lstrcpy( Info->szTalkMotionFile, smModelInfo.szTalkMotionFile );
							CopyMemory( Info->TalkMotionInfo, smModelInfo.TalkMotionInfo, sizeof(smModelInfo.TalkMotionInfo) );
							Info->TalkMotionCount = smModelInfo.TalkMotionCount;

							//							
							CopyMemory( Info->TalkMotionRate, smModelInfo.TalkMotionRate, sizeof(smModelInfo.TalkMotionRate) );
							CopyMemory( Info->TalkMotionRateCnt, smModelInfo.TalkMotionRateCnt, sizeof(smModelInfo.TalkMotionRateCnt) );
						}		
					}
					else
					{
						if( smModelInfo.MotionCount > CHRMOTION_EXT )
						{
							if( MotionKeyWordDecode(dwCode, &smModelInfo) == FALSE )
								return FALSE;
						}

						memcpy( Info, &smModelInfo, sizeof(smMODELINFO) );
					}
				}
				else
				{
					if( AddModelDecode(szFile, Info) == FALSE )
						return FALSE;
				}
			}
			else
			{
				if( AddModelDecode(szFile, Info) == FALSE )
                    return FALSE;
			}
		}
	}

	return TRUE;
}
//######################################################################################


//화면 및 캐릭터 및 파일등 기본 설정
smCONFIG	smConfig;



#ifndef _LANGUAGE_KOREAN
char *szConfigIniCommand[] = {
	"*MODE",
	"*SCREENSIZE",
	"*COLORMODE",

	"*배경화면",
	"*메뉴화면",

	"*PLAYERSKIN",
	"*나쁜놈",

	"*지형모델",
	"*지형물체",

	"*배경밝기",
	"*배경선명도",
	"*조명각도",
//	"*조명위치",

	"*서버주소",
	"*서버포트",

	"*화면품질",
	"*관찰자모드",

	"*데이타서버주소",
	"*데이타서버포트",

	"*캐릭터서버주소",
	"*캐릭터서버포트",
	
//	"Copyright-2002",
	//"MFC40.DLL",
#ifdef _LANGUAGE_ENGLISH	
#ifndef _LANGUAGE_PHILIPIN
	"알렉스*Bobby&이스마엘~-ㅜㅋ",
	"파아란",
#else
	"나쁜근배Halem$&%Byeㅋㅋ",
	"이런쉣",
#endif
#else
//중국
#ifdef _LANGUAGE_CHINESE
	"피터빤쓰속아름다운파랑고양이",
	"누런색",
#else
#ifdef _LANGUAGE_THAI
	"그물똥꼬바지속깜장잠자리",
	"붉은색",
#else
#ifdef _LANGUAGE_BRAZIL
	"아몬드쪼코~원츄>_<",
	"초코색",
#else
//아르헨티나
#ifdef _LANGUAGE_ARGENTINA
	"정하지$않았다..쉣더~ㅋ",
	"아!직%",
#else
#ifdef _LANGUAGE_JAPANESE
	"미래offline$#!대쓰요",
	"XD1004%선물세트",
#else
#ifdef _LANGUAGE_VEITNAM
	"왜낵가아엠이를하냐%짜증지대로",
	"프테투도즐겨라",
#else
	"망사똥꼬팬티속깜장개미",
	"핑크색",
#endif
#endif
#endif
#endif
#endif
#endif
#endif

	"*MONSTER_KEY",

	//######################################################################################
	//작 성 자 : 오 영 석
	"*지형애니",
	//######################################################################################


	0
};

char *szWordWinMode[5] = { "FULLSCREEN" , "WINDOW" , "SERVER" };
#else
char *szConfigIniCommand[] = {
	"*화면모드",
	"*화면해상도",
	"*화면색상비트",

	"*배경화면",
	"*메뉴화면",

	"*캐릭터스킨",
	"*나쁜놈",

	"*지형모델",
	"*지형물체",

	"*배경밝기",
	"*배경선명도",
	"*조명각도",
//	"*조명위치",

	"*서버주소",
	"*서버포트",

	"*화면품질",
	"*관찰자모드",

	"*데이타서버주소",
	"*데이타서버포트",

	"*캐릭터서버주소",
	"*캐릭터서버포트",
	
	"포장단체주문환영",
	"(왕초보가이드)",

	"*몬스터지정",

	//######################################################################################
	//작 성 자 : 오 영 석
	"*지형애니",
	//######################################################################################

	0
};
char *szWordWinMode[5] = { "전체화면" , "창모드" , "서버모드" };
#endif

char *szWordTexQualty[4] = { "좋음" , "보통" , "나쁨" , "아주나쁨" };
char *InfoRegPath = "SOFTWARE\\Triglow Pictures\\PristonTale";

/////////////////////////////////////////////////////////////////////////
ODBC_CONFIG	Odbc_Config;
TRANS_SERVER_LIST	TransServerList;
rsSERVER_CONFIG	rsServerConfig;
static int	srAdminCmdCnt = 0;
DWORD GetSwapIPCode( char *szIP );			//아이피 주소를 뒤집어서 변환 ( onserver.cpp )

/*
	int		LimitVersion;			//접속 가능한 최하 버전
	char	szAdminPassword[3][64];	//관리자 권한 부여 패스워드
*/

#ifdef _W_SERVER

//서버 설정 서브 루틴
int SetServerConfig( char *decode , char *lpPoint )
{

	int flag;
	char *p = lpPoint;
	char *pb;
	char strBuff[128];
	int cnt;

	flag = 0;

	if ( lstrcmp( decode , "*서버코드번호" )==0 ||
		lstrcmpi( decode , "*SERVER_CODE" )==0 ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.ServerCode = atoi(strBuff);
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*자동캐릭터사용" )==0 ||
		lstrcmpi( decode , "*SERVER_AUTOPLAY" )==0 ) ) {
		rsServerConfig.AutoPlayer = TRUE;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*저장버퍼사용" )==0 ||
		lstrcmpi( decode , "*SERVER_RECORD_MEM" )==0 ) ) {
		rsServerConfig.UseRecorMemory = TRUE;
		flag++;
	}


	if ( !flag && lstrcmp( decode , "*동료금지" )==0 ) {
		rsServerConfig.DisableParty = TRUE;
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*접속제한인원" )==0 ||
		lstrcmpi( decode , "*MAX_USERS" )==0 )) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.ConnectUserMax = atoi(strBuff);
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*테스트서버" )==0 || 
		lstrcmpi( decode , "*TEST_SERVER" )==0 ) ) {
		rsServerConfig.TestSeverMode = TRUE;
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] ) {
			rsServerConfig.TestSeverMode = atoi(strBuff);
		}
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*접속가능코드" )==0 ||
		lstrcmpi( decode , "*CONNECT_CLIENT_CODE" )==0 ) ) {
		for( cnt=0;cnt<32;cnt++ ) {
			p=GetWord(strBuff,p);
			if ( !strBuff[0] ) break;
			//접속가능 클라이언트 첵크섬 목록
			rsServerConfig.dwClientCheckSum[rsServerConfig.ClientCheckSumCount] = atoi(strBuff);
			rsServerConfig.ClientCheckSumCount++;
		}
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*코드접속종료" )==0 || 
		lstrcmpi( decode , "*DISCONNECT_CLIENT_BADCODE" )==0 ) ) {
		rsServerConfig.ClientCheckOut = TRUE;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*내부보호코드" )==0 || 
		lstrcmpi( decode , "*CLSAFE_CODE" )==0 ) ) {

		for( cnt=0;cnt<32;cnt++ ) {
			p=GetWord(strBuff,p);
			if ( !strBuff[0] ) break;
			//내부 보호 코드 목록
			rsServerConfig.dwSafeClientCode[rsServerConfig.SafeClientCodeCount] = atoi(strBuff);
			rsServerConfig.SafeClientCodeCount++;
		}
		flag++;
//		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
//		rsServerConfig.dwSafeClientCode = atoi(strBuff);
//		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*보호코드오류종료" )==0 || 
		lstrcmpi( decode , "*DISCONNECT_CLSAFE_CODE" )==0 ) ) {
		rsServerConfig.ClientCodeCheckOut = TRUE;
		flag++;
	}


	if ( !flag && ( lstrcmp( decode , "*제한버전" )==0 || 
		lstrcmpi( decode , "*VERSION" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.LimitVersion = atoi(strBuff);

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.LimitVersionMax = atoi(strBuff);

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*관리권한부여" )==0 || 
		lstrcmpi( decode , "*ADMIN_COMMAND" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szAdminPassword[srAdminCmdCnt] , strBuff );
		srAdminCmdCnt++;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*관리자이름" )==0 || 
		lstrcmpi( decode , "*ADMIN_NAME" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szAdminName , strBuff );
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*관리자IP주소" )==0 || 
		lstrcmpi( decode , "*ADMIN_IP" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szAdminIP , strBuff );
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*관리자접속암호" )==0 || 
		lstrcmpi( decode , "*ADMIN_LOGIN" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szAdminLogPassword , strBuff );
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*서버이름" )==0 || 
		lstrcmpi( decode , "*SERVER_NAME" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szServerName , strBuff );
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*PK허가" )==0 || 
		lstrcmpi( decode , "*ENABLE_PK" )==0 ) ) {

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Enable_PK = atoi(strBuff);
		if ( rsServerConfig.Enable_PK==0 ) rsServerConfig.Enable_PK=TRUE;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*PK필드" )==0 || 
		lstrcmpi( decode , "*PK_FIELD" )==0 ) ) {

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Enable_PKField = atoi(strBuff);
		if ( rsServerConfig.Enable_PKField==0 ) rsServerConfig.Enable_PKField=34;		//기본 PK필드 34 그리디 호수

		flag++;
	}

	// pluto PK허용 필드 전부
	if( !flag && ( lstrcmp( decode, "*PK모든필드" ) == 0 || lstrcmpi( decode, "*PK_FIELD_ALL" ) == 0 ) )
	{
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Enable_PKField_All = atoi(strBuff);
		flag++;
	}


	if ( !flag && ( lstrcmp( decode , "*물약감시" )==0 || 
		lstrcmpi( decode , "*POTION_MONITOR" )==0 ) ) {

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.PotionMonitor = atoi(strBuff);
		else
			rsServerConfig.PotionMonitor = 1;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*보안검사" )==0 || 
		lstrcmpi( decode , "*CL_PROTECT" )==0 ) ) {

		rsServerConfig.CheckProtect = TRUE;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*게임가드" )==0 || 
		lstrcmpi( decode , "*GAME_GUARD" )==0 ) ) {

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.GameGuard_Auth = atoi(strBuff);
		else
			rsServerConfig.GameGuard_Auth = 2;

		flag++;
	}

	#ifdef LOG_THE_PK
		//PK 로그 남기는거 //해외
		if ( !flag && ( lstrcmpi( decode , "*PK_LOG" )==0 ) )
		{
			rsServerConfig.bPK_LOG = true;
			flag++;
		}
	#endif

	#ifdef _XTRAP_GUARD_4_
		if ( !flag && ( lstrcmp( decode , "*엑스트랩" )==0 || 
			lstrcmpi( decode , "*XTRAP_GUARD" )==0 ) ) 
		{
			rsServerConfig.XTRAP_Timer = 200;
			rsServerConfig.XTRAP_MaxDealy = 1;




			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			if ( strBuff[0] ) {
				rsServerConfig.XTRAP_Timer = atoi(strBuff);
				OutputDebugString((strBuff));
				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
				if ( strBuff[0] ) rsServerConfig.XTRAP_MaxDealy = atoi(strBuff);
			}

			flag++;
		}
	#endif

	if ( !flag && ( lstrcmp( decode , "*보안제거" )==0 || 
		lstrcmpi( decode , "*REMOVE_PROTECT_TIME" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.RemoveNProtectTime = atoi(strBuff);
		flag++;
	}


	if ( !flag && ( lstrcmp( decode , "*디버그IP" )==0 || 
		lstrcmpi( decode , "*DEBUG_IP" )==0 ) ) {

		for( cnt=0;cnt<10;cnt++ ) {
			p=GetWord(strBuff,p);
			if ( !strBuff[0] ) break;

			lstrcpy( rsServerConfig.szDebugIP[rsServerConfig.DebugIP_Count] , strBuff );
			rsServerConfig.DebugIP_Count++;
		}
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*디버그ID" )==0 || 
		lstrcmpi( decode , "*DEBUG_ID" )==0 ) ) {

		for( cnt=0;cnt<32;cnt++ ) {
			if ( rsServerConfig.DebugID_Count>=32 ) break;
			
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			if ( !strBuff[0] ) break;

			lstrcpy( rsServerConfig.szDebugID[rsServerConfig.DebugID_Count] , strBuff );
			rsServerConfig.DebugID_Count++;
		}
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*블럭단계" )==0 ||
		lstrcmpi( decode , "*BLOCK_LEVEL" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.BlockLevel = atoi(strBuff);
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*블럭아웃" )==0 ||
		lstrcmpi( decode , "*BLOCK_LOGOUT" )==0 ) ) {
		rsServerConfig.BlockLevel_LogOut = TRUE;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*아이템오류종료" )==0 ||
		lstrcmpi( decode , "*DISCONNECT_ITEM_ERROR" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.ItemCodeOut = atoi(strBuff);
		else
			rsServerConfig.ItemCodeOut = 1;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*펑션검사" )==0 ||
		lstrcmpi( decode , "*CLIENT_CHECK_FUNC" )==0 ) ) {
		rsServerConfig.ClientFuncCheckMode = 1;
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.ClientFuncCheckMode = atoi(strBuff);
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*송편이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_MANDOO" )==0 ) ) {
		rsServerConfig.Event_Mandoo = TRUE;;
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*하드코어이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_HARDCORE" )==0 ) ) {

			p=GetWord(strBuff,p);
			if ( strBuff[0] )
				rsServerConfig.Event_HardCore = atoi(strBuff);
			else
				rsServerConfig.Event_HardCore = 1;

		flag++;
	}
#ifdef	_LANGUAGE_JAPANESE // 장별 - 원래는 필리핀	// 장별 - 몬스터 공격력 할인
	if ( !flag && ( lstrcmp( decode , "*공격력활인이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_DAMAGEOFF" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_DamageOff = atoi( strBuff );
		else
			rsServerConfig.Event_DamageOff = 1;
		flag++;
	}
#else
	if ( !flag && ( lstrcmpi( decode , "*EVENT_DAMAGEOFF1" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_DamageOff1 = atoi( strBuff );
		else
			rsServerConfig.Event_DamageOff1 = 1;
		flag++;
	}
	if ( !flag && ( lstrcmpi( decode , "*EVENT_DAMAGEOFF2" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_DamageOff2 = atoi( strBuff );
		else
			rsServerConfig.Event_DamageOff2 = 1;
		flag++;
	}
#endif
	//해외
	if ( !flag && ( lstrcmp( decode , "*방어력할인이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_DEFENSEOFF" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_DefenseOff = atoi( strBuff );
		else
			rsServerConfig.Event_DefenseOff = 1;
		flag++;
	}
//해외////////////////////////////////////////////////////////////
	if ( !flag && ( lstrcmp( decode , "*어린이이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_CHILD" )==0 ) ) {

			p=GetWord(strBuff,p);
			if ( strBuff[0] )
				rsServerConfig.Event_Child = atoi(strBuff);
			else
				rsServerConfig.Event_Child = 1;

		flag++;
	}

////////////////////////////////////////////////////////////////////
	if ( !flag && ( lstrcmp( decode , "*크리스탈이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_CRISTAL" )==0 ) ) {

			p=GetWord(strBuff,p);
			if ( strBuff[0] )
				rsServerConfig.Event_Cristal = atoi(strBuff);
			else
				rsServerConfig.Event_Cristal = 1;

		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*물약이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_POTION" )==0 ) ) {

		p=GetWord(strBuff,p);
		rsServerConfig.Event_Potion = atoi( strBuff );
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*별포인트이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_STARPOINT" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_StarPointTicket = atoi( strBuff );
		else
			rsServerConfig.Event_StarPointTicket = 40;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*생일이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_BIRTHDAY" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_ComicBirthDay = atoi( strBuff );
		else
			rsServerConfig.Event_ComicBirthDay = 1;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*퍼즐이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_PUZZLE" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Puzzle = atoi( strBuff );
		else
			rsServerConfig.Event_Puzzle = 200;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*바벨뿔이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_BABELHORN" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_BabelHorn = atoi( strBuff );
		else
			rsServerConfig.Event_BabelHorn = 4;

		if ( rsServerConfig.Event_BabelHorn>10 ) rsServerConfig.Event_BabelHorn=10;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*구미호이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_NINEFOX" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_NineFox = atoi( strBuff );
		else
			rsServerConfig.Event_NineFox = 20;

		flag++;
	}
	
	//크리스마스
	if ( !flag && ( lstrcmp( decode , "*크리스마스이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_CHRISTMAS" )==0 ) ) {
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.EVENT_Christmas = atoi( strBuff );
		else
			rsServerConfig.EVENT_Christmas = 100;

		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*발렌타인데이_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_VALENTINEDAY" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_ValentineDay = atoi( strBuff );
		else
			rsServerConfig.Event_ValentineDay = 100;

		flag++;
	}

		// pluto 커플링
	if ( !flag && ( lstrcmp( decode , "*커플링_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_COUPLERING" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_CoupleRing = atoi( strBuff );
		else
			rsServerConfig.Event_CoupleRing = 100;

		flag++;
	}

	// 박재원 - 수박 이벤트
	if ( !flag && ( lstrcmp( decode , "*수박_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_WATERMELON" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Watermelon = atoi( strBuff );
		else
			rsServerConfig.Event_Watermelon = 100;

		flag++;
	}

	// 장별 - 발렌타인 이벤트
	if ( !flag && ( lstrcmp( decode , "*발렌타인_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_VALENTINE" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Valentine = atoi( strBuff );
		else
			rsServerConfig.Event_Valentine = 100;

		flag++;
	}


	// 장별 - 캔디데이즈
	if ( !flag && ( lstrcmp( decode , "*캔디데이즈_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_CANDYDAYS" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Candydays = atoi( strBuff );
		else
			rsServerConfig.Event_Candydays = 100;

		flag++;
	}

	// 박재원 - 밤하늘의 소원이벤트
	if ( !flag && ( lstrcmp( decode , "*밤하늘소원_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_STAR" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Star = atoi( strBuff );
		else
			rsServerConfig.Event_Star = 100;

		flag++;
	}

	// 박재원 - 알파벳 조합 이벤트
	if ( !flag && ( lstrcmp( decode , "*알파벳조합_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_PRISTON_ALPHABET" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_PristonAlphabet = atoi( strBuff );
		else
			rsServerConfig.Event_PristonAlphabet = 100;
		flag++;
	}


	// 장별 - 화이트콘트라스트 이벤트
	if ( !flag && ( lstrcmp( decode , "*화이트콘트라스트_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_WHITECONTRAST" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_WhiteContrast = atoi( strBuff );
		else
			rsServerConfig.Event_WhiteContrast = 100;

		flag++;
	}

	// 장별 - 대장장이의 혼
	if ( !flag && ( lstrcmp( decode , "*대장장이의혼_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_BLACKSMITH" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_BlackSmith = atoi( strBuff );
		else
			rsServerConfig.Event_BlackSmith = 100;

		flag++;
	}

	// 장별 - 매지컬그린
	if ( !flag && ( lstrcmp( decode , "*매지컬그린_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_MAGICALGREEN" )==0 ) )
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_MagicalGreen = atoi( strBuff );
		else
			rsServerConfig.Event_MagicalGreen = 100;

		flag++;
	}

	// 장별 - 카라의 눈물
	if ( !flag && ( lstrcmp( decode , "*카라의눈물_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_TEAROFKARA" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_TearOfKara = atoi( strBuff );
		else
			rsServerConfig.Event_TearOfKara = 100;

		flag++;
	}


	if ( !flag && ( lstrcmp( decode , "*화이트데이_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_WHITEDAY" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_WhiteDay = atoi( strBuff );
		else
			rsServerConfig.Event_WhiteDay = 100;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*모리프의쉘텀_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_MORIFSHELTOM" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_MorifSheltom = atoi( strBuff );
		else
			rsServerConfig.Event_MorifSheltom = 1;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*월드컵_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_WORLDCUP" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_WorldCup = atoi( strBuff );
		else
			rsServerConfig.Event_WorldCup = 5;

		flag++;
	}

	// 장별 - 수박몬스터 이벤트
	if ( !flag && ( lstrcmp( decode , "*수박몬스터_이벤트" )==0 ||
	lstrcmpi( decode , "*EVENT_WATERMELONMONSTER" )==0 ) ) {

	p=GetWord(strBuff,p);
	if ( strBuff[0] )
		rsServerConfig.Event_WarerMelonMonster = atoi( strBuff );
	else
		rsServerConfig.Event_WarerMelonMonster = 1;

	flag++;
	}



	if ( !flag && ( lstrcmp( decode , "*몰리와늑대_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_MOLLYWOLF" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_MollyWolf = atoi( strBuff );
		else
			rsServerConfig.Event_MollyWolf = 9;

		flag++;
	}

	// 박재원 - 복날 이벤트
	if ( !flag && ( lstrcmp( decode , "*복날_이벤트" )==0 || lstrcmpi( decode , "*EVENT_CHICHEN_DAY" )==0 ) ) 
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Chichen_Day = atoi( strBuff );
		else
			rsServerConfig.Event_Chichen_Day = 1;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*고스트_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_GHOST" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_Ghost = atoi( strBuff );
		else
			rsServerConfig.Event_Ghost = 2;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*산타고블린_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_SANTAGOBLIN" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_SantaGoblin = atoi( strBuff );
		else
			rsServerConfig.Event_SantaGoblin = 5;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*삼계탕_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_SUMMER_CHICKEN" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_SummerChicken = atoi( strBuff );
		else
			rsServerConfig.Event_SummerChicken = 5;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*피시방펫_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_PCBANG_PET" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_PCBangPet = atoi( strBuff );
		else
			rsServerConfig.Event_PCBangPet = 1;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*경험치업_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_EXPUP" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.Event_ExpUp = atoi( strBuff );
		else
			rsServerConfig.Event_ExpUp = 120;

// 해외

		if		( rsServerConfig.Event_ExpUp >= 100 && rsServerConfig.Event_ExpUp < 200 )	{ rsServerConfig.Event_ExpUp=100; }
		else if ( rsServerConfig.Event_ExpUp >= 200 && rsServerConfig.Event_ExpUp < 300 )	{ rsServerConfig.Event_ExpUp=200; }
		else if ( rsServerConfig.Event_ExpUp >= 300 && rsServerConfig.Event_ExpUp < 400 )	{ rsServerConfig.Event_ExpUp=300; }
		else if ( rsServerConfig.Event_ExpUp >= 400)										{ rsServerConfig.Event_ExpUp=400; }
		else																				{ rsServerConfig.Event_ExpUp=100; }

		flag++;
	}

	if (!flag && lstrcmpi(decode, "*FAST_EXPUP_1_TO_20") == 0)
	{
		p = GetWord(strBuff, p);
		if (strBuff[0])
			rsServerConfig.Event_FastExpUp1To2 = atoi(strBuff);
		else
			rsServerConfig.Event_FastExpUp1To2 = 1000;

		//if (rsServerConfig.Event_ExpUp >= 100 && rsServerConfig.Event_ExpUp < 200) { rsServerConfig.Event_ExpUp = 100; }
		//else if (rsServerConfig.Event_ExpUp >= 200 && rsServerConfig.Event_ExpUp < 300) { rsServerConfig.Event_ExpUp = 200; }
		//else if (rsServerConfig.Event_ExpUp >= 300 && rsServerConfig.Event_ExpUp < 400) { rsServerConfig.Event_ExpUp = 300; }
		//else if (rsServerConfig.Event_ExpUp >= 400) { rsServerConfig.Event_ExpUp = 400; }
		//else { rsServerConfig.Event_ExpUp = 100; }

		flag++;
	}

#ifdef _LANGUAGE_ARGENTINA

		if ( !flag && ( lstrcmp( decode , "*경험치업_이벤트_라틴" )==0 || lstrcmpi( decode , "*EVENT_EXPUP_LATIN" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
		{
			rsServerConfig.Event_ExpUp_latin = atoi( strBuff );
		}
		else
		{
			rsServerConfig.Event_ExpUp_latin = 100;
		}

		flag++;
	}

#endif



	// pluto 선물상자
	if( !flag && ( lstrcmp( decode , "*선물상자_이벤트" )==0 ||
		lstrcmpi( decode , "*EVENT_HALLOWEEN" )==0 ) )	//해외용 Kyle
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
		{
			rsServerConfig.Event_GiftBox = atoi( strBuff );
		}
		else
		{
			rsServerConfig.Event_GiftBox = 0;
		}

		flag++;
	}

//#ifdef _LANGUAGE_VEITNAM
	//베트남 경험치 시간분배
	if ( !flag && ( lstrcmp( decode , "*시간경험치" )==0 ||	lstrcmpi( decode , "*EXP_GAMETIME" )==0 ) ) 
	{
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.ExpGameTimeMode = atoi( strBuff );
		else
			rsServerConfig.ExpGameTimeMode = 1;
		
		flag++;
	}
//#endif

	if ( !flag && ( lstrcmp( decode , "*블레스캐슬" )==0 ||
		lstrcmpi( decode , "*EVENT_BLESSCASTLE" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.BlessCastleMode = atoi( strBuff );
		else
			rsServerConfig.BlessCastleMode = 1;

		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*공성시간" )==0 ||
		lstrcmpi( decode , "*EVENT_SIEGE_TIME" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.sBlessCastle_StartTime[0] = atoi( strBuff );		//요일
		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.sBlessCastle_StartTime[1] = atoi( strBuff );		//시간

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*이벤트비트설정" )==0 ||
		lstrcmpi( decode , "*EVENT_BITMASK" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.EventPlay_BitMask = atoi( strBuff );

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*신규유저선물" )==0 ||
		lstrcmpi( decode , "*DEFAULT_ITEM_USER" )==0 ) ) {

		p=GetWord(strBuff,p);
		if ( strBuff[0] )
			rsServerConfig.StartUser_PresentItem = atoi( strBuff );
		else
			rsServerConfig.StartUser_PresentItem = TRUE;

		flag++;
	}


	if ( !flag && ( lstrcmp( decode , "*전업자기록" )==0 ||
		lstrcmpi( decode , "*RECORD_JOBCHANGER" )==0 ) ) {
		rsServerConfig.Record_JobChanger = TRUE;;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*영구블럭허가" )==0 ||
		lstrcmpi( decode , "*ENABLE_BLOCK_FOREVER" )==0 ) ) {
		rsServerConfig.ForeverBlockMode = TRUE;;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*경험치오차범위" )==0 ||
		lstrcmpi( decode , "*PERMIT_EXP" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Permit_Exp = atoi(strBuff);
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*돈오차범위" )==0 ||
		lstrcmpi( decode , "*PERMIT_MONEY" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Permit_Money = atoi(strBuff);
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*프로세스시간감시" )==0 ||
		lstrcmpi( decode , "*CLIENT_CHECK_PROCESS_TIME" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.ClientProcessTimeChk = atoi(strBuff);
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*프로세스시간종료" )==0 ||
		lstrcmpi( decode , "*CLIENT_PROCESS_TIME_OUT" )==0 ) ) {
		rsServerConfig.ClientProcessTimeChkOut = TRUE;
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*물약갯수확인" )==0 ||
		lstrcmpi( decode , "*CHECK_POTION_COUNT" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Dis_PotionError = atoi(strBuff);
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*서버경험치사용" )==0 ||
		lstrcmpi( decode , "*ENABLE_SERVER_EXP" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);

		if ( strBuff[0] ) rsServerConfig.ExpFixMode = atoi(strBuff);
		else rsServerConfig.ExpFixMode = 50;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*블럭유저경로" )==0 || 
		lstrcmpi( decode , "*BLOCK_USER_PATH" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szBlockUserPath , strBuff );
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*사용시간표시" )==0 || 
		lstrcmpi( decode , "*DISP_BILLING_TIME" )==0 ) ) {

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.DispBillingTime = atoi( strBuff );
		else
			rsServerConfig.DispBillingTime = 1;

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*로그인금지" )==0 || 
		lstrcmpi( decode , "*DISABLE_LOGIN" )==0 ) ) {

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.Disable_LogIn = atoi( strBuff );
		else
			rsServerConfig.Disable_LogIn = 1;
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*로그큐금지" )==0 || 
		lstrcmpi( decode , "*DISABLE_LOGQUE" )==0 ) ) {
		rsServerConfig.Disable_LogQue = TRUE;
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*로그아웃확인금지" )==0 || 
		lstrcmpi( decode , "*DISABLE_CHECK_LOGOUT" )==0 ) ) {
		rsServerConfig.Disable_CheckLogOut = TRUE;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*로그인차단" )==0 || 
		lstrcmpi( decode , "*DISABLE_LOGINX" )==0 ) ) {
		rsServerConfig.Disable_LogIn2 = TRUE;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*피시방금지" )==0 || 
		lstrcmpi( decode , "*DISABLE_PCBANG" )==0 ) ) {
		rsServerConfig.Disable_PCBang = TRUE;
		flag++;
	}


	if ( !flag && ( lstrcmp( decode , "*무료레벨" )==0 || 
		lstrcmpi( decode , "*FREE_LEVEL" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.FreeLevel = atoi(strBuff);					//무료 레벨

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			lstrcpy( rsServerConfig.szFreeGpCode , strBuff );		//무료 GPCODE

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*선물레벨" )==0 || 
		lstrcmpi( decode , "*PRESENT_LEVEL" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.PresentLevel = atoi(strBuff);
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*동료아이템출력" )==0 || 
		lstrcmpi( decode , "*ENABLE_PARTYITEM" )==0 ) ) {

		rsServerConfig.Enable_PartyItem = TRUE;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*필드지형검사" )==0 || 
		lstrcmpi( decode , "*CHECK_PLAYFIELD" )==0 ) ) {

		rsServerConfig.CheckPlayField = TRUE;
		flag++;
	}

		//스킨핵 방지
	if ( !flag && ( lstrcmp( decode , "*모델파일검사" )==0 || 
		lstrcmpi( decode , "*CHECK_MODELFILE" )==0 ) ) {

		rsServerConfig.CheckModelFile = TRUE;
		flag++;
	}
		

	if ( !flag && ( lstrcmp( decode , "*접속제한IP" )==0 || 
		lstrcmpi( decode , "*DISABLE_IP" )==0 ) ) {

		if ( rsServerConfig.DisableIP_Count<DISABLE_IP_MAX ) {
			p=GetWord(strBuff,p);
			rsServerConfig.DisableIP[rsServerConfig.DisableIP_Count][0] = GetSwapIPCode( strBuff );
			p=GetWord(strBuff,p);
			rsServerConfig.DisableIP[rsServerConfig.DisableIP_Count][1] = GetSwapIPCode( strBuff );
			rsServerConfig.DisableIP_Count++;
		}

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*접속허가IP" )==0 || 
		lstrcmpi( decode , "*ENABLE_IP" )==0 ) ) {

		if ( rsServerConfig.EnableIP_Count<ENABLE_IP_MAX ) {
			p=GetWord(strBuff,p);
			rsServerConfig.EnableIP[rsServerConfig.EnableIP_Count][0] = GetSwapIPCode( strBuff );
			p=GetWord(strBuff,p);
			rsServerConfig.EnableIP[rsServerConfig.EnableIP_Count][1] = GetSwapIPCode( strBuff );
			rsServerConfig.EnableIP_Count++;
		}

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*관리접속IP" )==0 || 
		lstrcmpi( decode , "*ADMINISTRATOR_IP" )==0 ) ) {

		if ( rsServerConfig.AdminIP_Count<ADMIN_IP_MAX ) {
			p=GetWord(strBuff,p);
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = GetSwapIPCode( strBuff );
			p=GetWord(strBuff,p);
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][1] = GetSwapIPCode( strBuff );
			rsServerConfig.AdminIP_Count++;
		}

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*시스템IP" )==0 || 
		lstrcmpi( decode , "*SYSTEM_IP" )==0 ) ) {

		if ( rsServerConfig.SystemIP_Count<ADMIN_IP_MAX ) {
			p=GetWord(strBuff,p);
			rsServerConfig.SystemIP[rsServerConfig.SystemIP_Count][0] = GetSwapIPCode( strBuff );
			p=GetWord(strBuff,p);
			rsServerConfig.SystemIP[rsServerConfig.SystemIP_Count][1] = GetSwapIPCode( strBuff );
			rsServerConfig.SystemIP_Count++;
		}

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*로그인서버IP" )==0 || 
		lstrcmpi( decode , "*LOGIN_SERVER_IP" )==0 ) ) {

		if ( rsServerConfig.SystemIP_Count<LOGIN_IP_MAX ) {
			p=GetWord(strBuff,p);
			rsServerConfig.LoginServerIP[rsServerConfig.LoginServerIP_Count][0] = GetSwapIPCode( strBuff );
			p=GetWord(strBuff,p);
			rsServerConfig.LoginServerIP[rsServerConfig.LoginServerIP_Count][1] = GetSwapIPCode( strBuff );
			rsServerConfig.LoginServerIP_Count++;
		}

		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*서버인벤토리" )==0 || 
		lstrcmpi( decode , "*SERVER_INVENTORY" )==0 ) ) {

		rsServerConfig.ServerInventoryMode = TRUE;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*백업폴더이름" )==0 || 
		lstrcmpi( decode , "*BACKUP_PATH" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szBackupPath , strBuff );
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*스킬포인트감소불가" )==0 || 
		lstrcmpi( decode , "*DISABLE_DEC_SKILLPOINT" )==0 ) ) {

		rsServerConfig.Disable_DecSkillPoint = TRUE;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*퀘스트금지" )==0 || 
		lstrcmpi( decode , "*DISABLE_QUEST" )==0 ) ) {

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		rsServerConfig.Disable_Quest = atoi(strBuff);
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*시작필드고정" )==0 || 
		lstrcmpi( decode , "*START_FIELD" )==0 ) ) {

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.FixedStartField = atoi(strBuff);
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*아이템버림금지" )==0 || 
		lstrcmpi( decode , "*DISABLE_THROWITEM" )==0 ) ) {

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.DisableThrowItem = atoi(strBuff);
		else
			rsServerConfig.DisableThrowItem = 1;

		flag++;
	}



	if ( !flag && ( lstrcmp( decode , "*크레이지패킷" )==0 || 
		lstrcmpi( decode , "*CRAZY_PACKET" )==0 ) ) {

		rsServerConfig.CrazyPacketMode = TRUE;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*통보주소" )==0 || 
		lstrcmpi( decode , "*NOTICE_URL" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szNoticeURL , strBuff );
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*관리명령기록" )==0 || 
		lstrcmpi( decode , "*REC_ADMIN_CMD" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			rsServerConfig.RecordAdminCommand = atoi( strBuff );
		else
			rsServerConfig.RecordAdminCommand = 2;

		flag++;
	}


	if ( !flag && ( lstrcmp( decode , "*서버연결IP" )==0 || 
		lstrcmpi( decode , "*SERVER_LINK_IP" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( rsServerConfig.szLinkServerIP , strBuff );
		flag++;
	}


	if ( !flag && ( lstrcmp( decode , "*지역서버" )==0 || 
		lstrcmpi( decode , "*AREA_SERVER" )==0 ) ) {

		for( cnt=0;cnt<32;cnt++ ) {
			if ( rsServerConfig.AreaServer.IP_Count>=SERVER_MAP_MAX ) break;

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			if ( !strBuff[0] ) break;

			rsServerConfig.AreaServer.dwIP[ rsServerConfig.AreaServer.IP_Count ] = inet_addr( strBuff );

			rsServerConfig.AreaServer.IP_Count++;
			rsServerConfig.AreaServer.size = sizeof(TRANS_SEVER_MAP)-(sizeof(DWORD)*(SERVER_MAP_MAX-rsServerConfig.AreaServer.IP_Count));
			rsServerConfig.AreaServer.code = smTRANSCODE_AREA_SERVER_MAP;
		}
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*토너먼트계정서버" )==0 || 
		lstrcmpi( decode , "*TT_DATA_SERVER" )==0 ) ) {

			cnt = rsServerConfig.TT_DataServer_Count;

			if ( cnt>=TT_DATA_SERVER_MAX ) goto skip_t;

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			if ( !strBuff[0] ) goto skip_t;
			lstrcpy( rsServerConfig.TT_DataServer[cnt].szServerID , strBuff );

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			if ( !strBuff[0] ) goto skip_t;
			lstrcpy( rsServerConfig.TT_DataServer[cnt].szServerPath, strBuff );

			rsServerConfig.TT_DataServer_Count++;
skip_t:
		flag++;
	}


	return flag;
}

#else

//서버 설정 서브 루틴
int SetServerConfig( char *decode , char *lpPoint )
{

	return NULL;
}

#endif

//ODBC 설정 서브 루틴
int SetOdbcConfig( char *decode , char *lpPoint )
{
	int flag;
	char *p = lpPoint;
	char *pb;
	char strBuff[128];

	flag = 0;

	if ( lstrcmp( decode , "*인증접속서비스" )==0 ||
		lstrcmpi( decode , "*ODBC_NAME" )==0 ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( Odbc_Config.Dsn , strBuff );
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*인증접속이름" )==0 ||
		lstrcmpi( decode , "*ODBC_ACCOUNT" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( Odbc_Config.Name , strBuff );
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*인증접속암호" )==0 ||
		lstrcmpi( decode , "*ODBC_PASSWORD" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( Odbc_Config.Password , strBuff );
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*테이블이름" )==0 ||
		lstrcmpi( decode , "*ODBC_TABLE" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( Odbc_Config.Table , strBuff );
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*테이블계정" )==0 ||
		lstrcmpi( decode , "*ODBC_TABLE_IDNAME" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		lstrcpy( Odbc_Config.Table_Id , strBuff );
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*테이블암호열" )==0 ||
		lstrcmpi( decode , "*ODBC_TABLE_PASSWORD" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		Odbc_Config.Table_Password = atoi(strBuff);
		flag++;
	}
	if ( !flag && ( lstrcmp( decode , "*테이블허가열" )==0 ||
		lstrcmpi( decode , "*ODBC_TABLE_PLAY" )==0 ) ) {
		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		Odbc_Config.Table_Play = atoi(strBuff);
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*테스트전용인증" )==0 ||
		lstrcmp( decode , "*LOGIN_TESTER" )==0 ) ) {
		Odbc_Config.CloseAccount = TRUE;
		flag++;
	}
	
	return flag;
}


//SERVER 목록 설정 서브 루틴
int SetServerSelectList( char *decode , char *lpPoint )
{
	int flag;
	char *p = lpPoint;
	char *pb;
	char strBuff[128];
	int cnt;

	flag = 0;

	if ( TransServerList.ServerCount>=TRANS_SERVER_MAX ) return FALSE;

	if ( lstrcmp( decode , "*접속서버정보" )==0 || 
		lstrcmpi( decode , "*GAME_SERVER" )==0  ) {
		cnt = TransServerList.ServerCount;

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] ) {
			lstrcpy( TransServerList.ServerInfo[cnt].szServerName , strBuff );			//서버 이름
		}

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] ) {
			lstrcpy( TransServerList.ServerInfo[cnt].szServerIp1 , strBuff );			//서버 이름
			TransServerList.ServerInfo[cnt].dwServerPort1 = TCP_SERVPORT;
		}

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] ) {
			lstrcpy( TransServerList.ServerInfo[cnt].szServerIp2 , strBuff );			//서버 이름 ( 예비 )
			TransServerList.ServerInfo[cnt].dwServerPort2 = TCP_SERVPORT;
		}

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] ) {
			lstrcpy( TransServerList.ServerInfo[cnt].szServerIp3 , strBuff );			//서버 이름 ( 예비 )
			TransServerList.ServerInfo[cnt].dwServerPort3 = TCP_SERVPORT;
		}

		TransServerList.ServerCount++;
		flag++;
	}

	if ( !flag && ( lstrcmp( decode , "*클랜서버정보" )==0 || 
		lstrcmpi( decode , "*CLAN_SERVER" )==0 ) ) {

		cnt = TransServerList.ServerCount+TransServerList.ClanServerCount;

		lstrcpy( TransServerList.ServerInfo[cnt].szServerName , "Clan" );

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			lstrcpy( TransServerList.ServerInfo[cnt].szServerIp1 , strBuff );			//IP

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			TransServerList.ServerInfo[cnt].dwServerPort1 = atoi(strBuff);				//Port

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			lstrcpy( TransServerList.ServerInfo[cnt].szServerIp2 , strBuff );			//IP

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			TransServerList.ServerInfo[cnt].dwServerPort2 = atoi(strBuff);				//Port

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			lstrcpy( TransServerList.ServerInfo[cnt].szServerIp3 , strBuff );			//IP

		pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
		if ( strBuff[0] )
			TransServerList.ServerInfo[cnt].dwServerPort3 = atoi(strBuff);				//Port

		TransServerList.ClanServerCount++;
		flag++;
	}

	
	return flag;
}

/////////////// 레지스트리 설정값 읽어옴 ///////////////
smCONFIG *smConfigReg()
{
	Utils_Log(LOG_DEBUG, "now entering the smConfigReg() function");

	char *buff;
#ifdef _LANGUAGE_WINDOW
	Utils_Log(LOG_DEBUG, "#ifdef _LANGUAGE_WINDOW");
	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "FullMode" );
	if ( buff )
	{
		if ( lstrcmpi( buff , "off" )==0 )
		{
			smConfig.WinMode = 1;
			Utils_Log(LOG_DEBUG, "smConfig.WinMode = 1");
		}
		else
		{
			smConfig.WinMode = 0;
			Utils_Log(LOG_DEBUG, "smConfig.WinMode = 0");
		}
	}
	else
	{
		Utils_Log(LOG_DEBUG, "cant find the 'FullMode' registry");
	}
#endif

	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "Graphic" );
	if ( buff ) 
	{
		smConfig.TextureQuality = atoi( buff );
		Utils_Log(LOG_DEBUG, "Use GraphicMode: %d", smConfig.TextureQuality);
	}

	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "ColorBPP" );
	if ( buff ) 
	{
		if ( atoi(buff)==32 ) 
			smConfig.ScreenColorBit = 32;
		Utils_Log(LOG_DEBUG, "Use ColorBPP: %d", smConfig.ScreenColorBit);
	}


	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "Network" );
	if ( buff ) 
	{
		smConfig.NetworkQuality = atoi( buff );
		Utils_Log(LOG_DEBUG, "Use Network: %d", smConfig.NetworkQuality);
	}


	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "CameraInvert" );
	if ( buff ) 
	{
		if ( lstrcmpi( buff , "true" )==0 ) 
			CameraInvRot = 1;
		else
			CameraInvRot = 0;

		Utils_Log(LOG_DEBUG, "Use CameraInvert: %d", CameraInvRot);
	}

	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "MotionBlur" );
	if ( buff ) 
	{
		if ( lstrcmpi( buff , "true" )==0 ) 
			g_IsCreateFilterEffect = 1;
		else
			g_IsCreateFilterEffect = 0;
		Utils_Log(LOG_DEBUG, "Use MotionBlur: %d", g_IsCreateFilterEffect);
	}

	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "CameraSight" );
	if ( buff ) 
	{
		if ( lstrcmpi( buff , "ON" )==0 ) 
			CameraSight = 1;
		else
			CameraSight = 0;
		Utils_Log(LOG_DEBUG, "Use CameraSight: %d", CameraSight);
	}

	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "ScreenSize" );
	if ( buff ) 
	{
		switch( atoi(buff) )
		{
			case 0:
				smConfig.AspectRatio = 0;
				smConfig.ScreenSize.x = 800;
				smConfig.ScreenSize.y = 600;
				//Utils_Log(LOG_DEBUG, " AspectRatio = 4:3, ScreenSize.x = 800 , ScreenSize.y = 600");
				break;

			case 1:
				smConfig.AspectRatio = 0;
				smConfig.ScreenSize.x = 1024;
				smConfig.ScreenSize.y = 768;
				//Utils_Log(LOG_DEBUG, " AspectRatio = 4:3, ScreenSize.x = 1024 , ScreenSize.y = 768");
				break;

			case 2:				
				smConfig.AspectRatio = 0;
				smConfig.ScreenSize.x = 1280;
				smConfig.ScreenSize.y = 1024;
				//Utils_Log(LOG_DEBUG, " AspectRatio = 4:3, ScreenSize.x = 1280 , ScreenSize.y = 1024");
				break;
			case 3:
				smConfig.AspectRatio = 0;
				smConfig.ScreenSize.x = 1400;
				smConfig.ScreenSize.y = 1050;
				//Utils_Log(LOG_DEBUG, " AspectRatio = 4:3, ScreenSize.x = 1400 , ScreenSize.y = 1050");
				break;

			// 16:9 screens
			case 4:
				smConfig.AspectRatio = 1;
				smConfig.ScreenSize.x = 1280;
				smConfig.ScreenSize.y = 720;
				//Utils_Log(LOG_DEBUG, " AspectRatio = 4:3, ScreenSize.x = 1280 , ScreenSize.y = 720");
			case 5:
				smConfig.AspectRatio = 1;
				smConfig.ScreenSize.x = 1366;
				smConfig.ScreenSize.y = 768;
				//Utils_Log(LOG_DEBUG, " AspectRatio = 4:3, ScreenSize.x = 1366 , ScreenSize.y = 768");
			case 6:
				smConfig.AspectRatio = 1;
				smConfig.ScreenSize.x = 1600;
				smConfig.ScreenSize.y = 900;
				//Utils_Log(LOG_DEBUG, " AspectRatio = 4:3, ScreenSize.x = 1600 , ScreenSize.y = 900");
				break;
			case 7:
				smConfig.AspectRatio = 1;
				smConfig.ScreenSize.x = 1920;
				smConfig.ScreenSize.y = 1080;
				//Utils_Log(LOG_DEBUG, " AspectRatio = 4:3, ScreenSize.x = 1920 , ScreenSize.y = 1080");
				break;
		}

		Utils_Log(LOG_DEBUG, " AspectRatio = %s , ScreenSize.x = %d , ScreenSize.y = %d", smConfig.AspectRatio ? "16:9" : "4:3", smConfig.ScreenSize.x, smConfig.ScreenSize.y);
		Utils_Log(LOG_DEBUG, "Use ScreenSize: %d", atoi(buff));
	}
	else
	{
		Utils_Log(LOG_DEBUG, "cant find the 'ScreenSize' registry");
	}

	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "Sound" );
	if ( buff ) 
	{
		if ( lstrcmpi( buff , "off" )==0 ) 
			smConfig.BGM_Mode = 0;
		else
			smConfig.BGM_Mode = 1;

		Utils_Log(LOG_DEBUG, "Use Sound: %d", smConfig.BGM_Mode);
	}

	// pluto 해외 비
	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "RainMode" );
	if ( buff )
	{
		if ( lstrcmpi( buff , "Off" )==0 ) 
			smConfig.WeatherSwitch = 0;
		else
			smConfig.WeatherSwitch = 1;

		Utils_Log(LOG_DEBUG, "Use RainMode: %d", smConfig.WeatherSwitch);
	}

	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "Server1" );
	if ( buff ) 
	{
		lstrcpy( smConfig.szDataServerIP , buff );

		Utils_Log(LOG_DEBUG, " 'Server1' the value of  smConfig.szDataServerIP is ->");
		Utils_Log(LOG_DEBUG, buff);
	}
	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "Server2" );
	if ( buff ) 
	{
		lstrcpy( smConfig.szServerIP , buff );
		lstrcpy( smConfig.szExtendServerIP , buff );

		Utils_Log(LOG_DEBUG, " 'Server2' the value of  smConfig.szServerIP , szExtendServerIP is ->");
		Utils_Log(LOG_DEBUG, buff);
	}
	buff = GetRegString( HKEY_LOCAL_MACHINE , InfoRegPath , "Server3" );
	if ( buff ) 
	{
		lstrcpy( smConfig.szUserServerIP , buff );
		Utils_Log(LOG_DEBUG, " 'Server3' the value of  smConfig.szUserServerIP is ->");
		Utils_Log(LOG_DEBUG, buff);
	}

	smConfig.dwDataServerPort = TCP_SERVPORT;
	smConfig.dwServerPort = TCP_SERVPORT;
	smConfig.dwUserServerPort = TCP_SERVPORT;
	smConfig.dwExtendServerPort = TCP_SERVPORT;

	//디버그 플랙 백업 ( 해킹 방지 )
	dwDebugXor = GetCurrentTime();
	dwDebugBack = smConfig.DebugMode^dwDebugXor;

	return &smConfig;
}


//정보 파일을 해독하여 돌려준다 (Info에저장)
smCONFIG *smConfigDecode( char *iniFile  )
{
	FILE	*fp = NULL;
	char strBuff[64];
	char *p,*pb;
	int CmdNum;
	int MapLightAngX,MapLightAngY;
	int x,y,z;
	int cnt;

	smCONFIG *Config = &smConfig;

	srAdminCmdCnt = 0;

	ZeroMemory( Config , sizeof( smCONFIG ) );
	ZeroMemory( &Odbc_Config , sizeof( ODBC_CONFIG ) );
	ZeroMemory( &TransServerList , sizeof( TRANS_SERVER_LIST ) );
	ZeroMemory( &rsServerConfig , sizeof( rsSERVER_CONFIG ) );

	//기본 설정
	Config->WinMode = 0;
	Config->ScreenSize.x = 800;
	Config->ScreenSize.y = 600;
	Config->ScreenColorBit = 16;
	Config->StageObjCnt = 0;
	Config->TextureQuality = 0;		//기본 1
	Config->NetworkQuality = 2;		//기본 2
	Config->BGM_Mode = 1;
	Config->WeatherSwitch = 0;	// pluto 해외 비


	Config->MapBright = DEFAULT_BRIGHT;
	Config->MapContrast = DEFAULT_CONTRAST;
	Config->MapLightVector.x = fONE;
	Config->MapLightVector.y = -fONE;
	Config->MapLightVector.z = fONE/2;

	//return smConfigReg();					//레지스트리 설정 적용

	rsServerConfig.Enable_PKField = -1;
	rsServerConfig.Enable_PKField_All = 0;


	////////////////////////// 디버그 모드 설정 //////////////////////


	fp = fopen( iniFile , "rb" );
	
	if( fp != NULL )
	{
		Utils_Log(LOG_DEBUG, "fp = fopen( iniFile , 'rb' ) : success");
	}
	else
	{
		Utils_Log(LOG_DEBUG, "fp = fopen( iniFile , 'rb' ) : failure , so call the smConfigReg() function.");
	}

	if ( fp==NULL ) {
		return smConfigReg();					//레지스트리 설정 적용
	}

	while( !feof( fp ) )//  feof: file end까지 읽어라 
	{
		if( fgets( line, 255, fp ) == NULL)	
			break;

		p = GetWord( decode , line);

		CmdNum = 0;

		while(1) 
		{
			if ( lstrcmp( decode, szConfigIniCommand[CmdNum] ) == 0 )
				break;
			
			if ( szConfigIniCommand[CmdNum]==NULL ) 
				break;

			CmdNum++;

#ifdef _W_SERVER
			//////////// 서버용 설정 /////////////////////////////////
			if ( SetOdbcConfig( decode , p ) ) break;			// ODBC
			if ( SetServerSelectList( decode , p ) ) break;		// 접속 서버 목록
			if ( SetServerConfig( decode , p ) ) break;			//서버설정
			//////////////////////////////////////////////////////////
#endif
		}
		
		switch( CmdNum )
		{
		case 0:
			//"*화면모드",
			p = GetWord( strBuff , p );
#ifdef _W_SERVER
			if ( lstrcmpi( strBuff , szWordWinMode[2])==0 )				//서버 모드
			{
				Config->WinMode = -1;
				break;
			}
#endif

#ifdef _WINMODE_DEBUG
			if ( lstrcmpi( strBuff , szWordWinMode[1] )==0 ) 
				Config->WinMode = 1;
			else
				Config->WinMode = 0;
#else 
				Config->WinMode = 0;
#endif
			break;

		case 1:
			//"*화면해상도",
			p = GetWord( strBuff , p );
			Config->ScreenSize.x = atoi(strBuff);
			p = GetWord( strBuff , p );
			Config->ScreenSize.y = atoi(strBuff);
			break;

		case 2://
			//"*화면색상비트",
			p = GetWord( strBuff , p );
			//Config->ScreenColorBit = atoi(strBuff);
			break;

		case 3:
			//"*배경화면",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_BackGround[0] , strBuff );
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_BackGround[1] , strBuff );
			break;

		case 4:
			//"*메뉴화면",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_Menu , strBuff );
			break;

		case 5:
#ifdef _WINMODE_DEBUG
			//"*주인공",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_Player , strBuff );
			p = GetWord( strBuff , p );
			Config->Posi_Player.x = (int)(atof(strBuff) * fONE);
			p = GetWord( strBuff , p );
			Config->Posi_Player.y = (int)(atof(strBuff) * fONE);
#endif
			break;

		case 6:
#ifdef _WINMODE_DEBUG
			//"*나쁜놈",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_Enemy , strBuff );
			p = GetWord( strBuff , p );
			Config->Posi_Enemy.x = (int)(atof(strBuff) * fONE);
			p = GetWord( strBuff , p );
			Config->Posi_Enemy.y = (int)(atof(strBuff) * fONE);
#endif
			break;

		case 7:
			//"*지형모델",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szFile_Stage , strBuff );

			p = GetWord( strBuff , p );
			if ( strBuff[0] )
				Config->Posi_Stage.x = (int)(atof(strBuff) * fONE);

			p = GetWord( strBuff , p );

			if ( strBuff[0] )
				Config->Posi_Stage.y = (int)(atof(strBuff) * fONE);
			break;

		//######################################################################################
		//작 성 자 : 오 영 석
		case 8:
			//*지형물체			
			p = GetWord( strBuff, p );
			if( Config->StageObjCnt < FIELD_STAGE_OBJ_MAX )
			{
				lstrcpy( Config->szFile_StageObject[ Config->StageObjCnt ], strBuff );
				Config->IsStageAniObject[ Config->StageObjCnt ] = 0;
				Config->StageObjCnt++;
			}
			break;
		//######################################################################################

		case 9:
			//"*배경밝기",
			//p = GetWord( strBuff , p );
			//Config->MapBright = atoi(strBuff);
			break;

		case 10:
			//"*배경선명도",
			//p = GetWord( strBuff , p );
			//Config->MapContrast = atoi(strBuff);

			break;

		case 11:
			//"*조명각도",
			/*
			p = GetWord( strBuff , p );
			Config->MapLightVector.x = (int)(atof(strBuff)*fONE);
			p = GetWord( strBuff , p );
			Config->MapLightVector.z = (int)(atof(strBuff)*fONE);
			p = GetWord( strBuff , p );
			Config->MapLightVector.y = (int)(atof(strBuff)*fONE);
			*/

			/*
			p = GetWord( strBuff , p );
			MapLightAngY = atoi(strBuff) * 16;
			p = GetWord( strBuff , p );
			MapLightAngX = (128-atoi(strBuff)) * 16;
			MapLightAngX = (MapLightAngX - ANGLE_90) & ANGCLIP;

			MapLightAngY = 128 * 16;
			MapLightAngX = (128-10) * 16;
			MapLightAngX = (MapLightAngX - ANGLE_90) & ANGCLIP;

			x = 0;
			y = 0;
			z = (int)(1.5*fONE);

			smMATRIX rX , rY , mVect;
			int vx,vy,vz;

			smIdentityMatrix( rX );
			smIdentityMatrix( rY );

			smRotateYMatrix( rY , MapLightAngY );
			smRotateXMatrix( rX , MapLightAngX );
			smMatrixMult( mVect , rX , rY );

			vx = x * mVect._11 +
				 y * mVect._21 +
				 z * mVect._31 ;

			vy = x * mVect._12 +
				 y * mVect._22 +
				 z * mVect._32 ;

			vz = x * mVect._13 +
				 y * mVect._23 +
				 z * mVect._33 ;

			vx>>=FLOATNS;
			vy>>=FLOATNS;
			vz>>=FLOATNS;

			Config->MapLightVector.x = vx;
			Config->MapLightVector.y = vy;
			Config->MapLightVector.z = vz;
			*/

			break;
		case 12:
			//"*서버주소",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szServerIP , strBuff );
			break;

		case 13:
			//"*서버포트",
			p = GetWord( strBuff , p );
			Config->dwServerPort = atoi( strBuff );
			break;

		case 14:
			//"*화면품질",
			p = GetWord( strBuff , p );

			if ( lstrcmp( strBuff , szWordTexQualty[0] )==0 ) {
				//좋음
				Config->TextureQuality = 0;
				break;
			}
			if ( lstrcmp( strBuff , szWordTexQualty[1] )==0 ) {
				//보통
				Config->TextureQuality = 1;
				break;
			}
			if ( lstrcmp( strBuff , szWordTexQualty[2] )==0 ) {
				//나쁨
				Config->TextureQuality = 2;
				break;
			}
			if ( lstrcmp( strBuff , szWordTexQualty[3] )==0 ) {
				//아주나쁨
				Config->TextureQuality = 3;
				break;
			}
			break;

		case 15:
#ifdef _WINMODE_DEBUG
			//"*관찰자모드",
			DebugPlayer = TRUE;
#endif
			break;

		case 16:
			//"*데이타서버주소",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szDataServerIP , strBuff );
			break;

		case 17:
			//"*데이타서버포트",
			p = GetWord( strBuff , p );
			Config->dwDataServerPort = atoi( strBuff );
			break;

		case 18:
			//"*캐릭터서버주소",
			p = GetWord( strBuff , p );
			lstrcpy( Config->szUserServerIP , strBuff );
			break;
		case 19:
			//"*캐릭터서버포트",
			p = GetWord( strBuff , p );
			Config->dwUserServerPort = atoi( strBuff );
			break;


		case 20:
			#ifdef _WINMODE_DEBUG
				//"*디버그모드" ( 내부 IP전용 )
				p = GetWord( strBuff , p );
				if ( lstrcmp( strBuff, szConfigIniCommand[CmdNum] )!=0 ) 
					break;

				p = GetWord( strBuff , p );
				if ( lstrcmp( strBuff, szConfigIniCommand[CmdNum] )!=0 ) 
					break;

				p = GetWord( strBuff , p );
				if ( strBuff[0]=='^' && strBuff[1]=='^' ) 
				{
					Utils_Log(LOG_DEBUG, " case 20: if ( strBuff[0]=='^' && strBuff[1]=='^' ) : success");
					Config->DebugMode = TRUE;
				}
			#endif
			break;

		case 21:
		{

			#ifdef _WINMODE_DEBUG
			{
				//"*디버그모드" - 숨겨진 최고의 모드
				p = GetWord( strBuff , p );
				if ( lstrcmp( strBuff, szConfigIniCommand[CmdNum-1] )!=0 ) 
					break;

				p = GetWord( strBuff , p );
				if ( strBuff[0]=='/' && strBuff[1]=='0' ) 
				{
					Utils_Log(LOG_DEBUG, " case 21: if ( strBuff[0]=='/' && strBuff[1]=='0' ) : success");
					Config->DebugMode = 0x100;
				}
			}
			#endif

		}break;

		case 22:
			//몬스터 키보드 설정
			for(cnt=0;cnt<CONFIG_KEY_MONSTER_MAX;cnt++) {
				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
				if ( !strBuff[0] ) break;			
				if ( Config->CmdMonsterCount>=CONFIG_KEY_MONSTER_MAX ) break;
				lstrcpy( Config->szCmdOpenMonster[Config->CmdMonsterCount++] , strBuff );
			}
			break;

		//######################################################################################
		//작 성 자 : 오 영 석
		case 23:
			// *지형애니
			p = GetWord( strBuff, p );
			if( Config->StageObjCnt < FIELD_STAGE_OBJ_MAX )
			{
				lstrcpy( Config->szFile_StageObject[ Config->StageObjCnt ], strBuff );
				Config->IsStageAniObject[ Config->StageObjCnt ] = 1;
				Config->StageObjCnt++;
			}
			break;
		//######################################################################################

		}
	}

	fclose(fp);

#ifdef	_WINMODE_DEBUG
#ifndef _LANGUAGE_VEITNAM	//윈도우 모드
#ifndef _LANGUAGE_CHINESE	//윈도우 모드
#ifndef _LANGUAGE_PHILIPIN	//윈도우 모드
#ifndef _LANGUAGE_ENGLISH	//윈도우 모드

	if ( !Config->DebugMode && Config->WinMode>=0 )
	{
		//디버그모드 아니면 화면 설정 불가
		Config->WinMode = 0;
		Config->ScreenSize.x = 800;
		Config->ScreenSize.y = 600;
		Config->ScreenColorBit = 16;
	}
#endif
#endif
#endif
#endif
#endif


			//"*조명각도",

			smMATRIX rX , rY , mVect;
			int vx,vy,vz;

			MapLightAngY = 128 * 16;
			MapLightAngX = (128-10) * 16;
			MapLightAngX = (MapLightAngX - ANGLE_90) & ANGCLIP;

			x = 0;
			y = 0;
			z = (int)(1.5*fONE);

			smIdentityMatrix( rX );
			smIdentityMatrix( rY );

			smRotateYMatrix( rY , MapLightAngY );
			smRotateXMatrix( rX , MapLightAngX );
			smMatrixMult( mVect , rX , rY );

			vx = x * mVect._11 +
				 y * mVect._21 +
				 z * mVect._31 ;

			vy = x * mVect._12 +
				 y * mVect._22 +
				 z * mVect._32 ;

			vz = x * mVect._13 +
				 y * mVect._23 +
				 z * mVect._33 ;

			vx>>=FLOATNS;
			vy>>=FLOATNS;
			vz>>=FLOATNS;

			Config->MapLightVector.x = vx;
			Config->MapLightVector.y = vy;
			Config->MapLightVector.z = vz;


			//"*배경밝기",
			Config->MapBright = 130;

			//"*배경선명도",
			Config->MapContrast = 300;

#ifndef _W_SERVER
	smConfigReg();					//레지스트리 설정 적용
#endif

	return &smConfig;
};



//단축 메세지 읽어 오기
int	ReadShotcutMessage( char *szFileName )
{
	FILE	*fp;
	int cnt;
	int	Count = 1;

	for(cnt=0;cnt<10;cnt++) {
		szShotCutMessage[cnt][0] = 0;
	}


	fp = fopen( szFileName , "rb" );
	if ( fp==NULL ) return FALSE;

	while( !feof( fp ) )					//  feof: file end까지 읽어라 
	{
		if( fgets( line, 255, fp ) == NULL)	
			break;

		line[99]=0;

		for(cnt=0;cnt<100;cnt++) {

			if ( line[cnt]=='\\' && ( line[cnt+1]=='r' || line[cnt+1]=='R' ) ) {
				line[cnt] = 0x0D;
				line[cnt+1] = 0;
				break;
			}

			if ( line[cnt]==0x0A || line[cnt]==0x0D || line[cnt]==0 ) {
				line[cnt] = 0;
				break;
			}
		}

		cnt = Count;
		if ( Count==10 ) cnt = 0;
		lstrcpy( szShotCutMessage[cnt] , line );

		Count++;
		if ( Count>10 ) break;
	}

	fclose(fp);

	return TRUE;

}

//파일 이름으로 부터 디렉토리를 찾아 설정
char *GetDirectoryFromFile( char *filename , char *szDirectory )
{
	int len;
	int cnt;

	if ( !szDirectory ) return NULL;

	lstrcpy( szDirectory , filename );

	len = lstrlen( szDirectory );

	for( cnt=len; cnt>=0 ; cnt-- )
		if ( szDirectory[cnt]=='\\' ) break;

	szDirectory[cnt+1] = NULL;

	return szDirectory;
}



//아이템 정보 파일을 해독하여 돌려준다 
int DecodeItemInfo( char *szItemFile , sDEF_ITEMINFO *lpDefItem  )
{
	FILE	*fp;
	char strBuff[128];
	char *p;
	char *pb;
	int cnt;
	int NextFlag;
	sITEMINFO	*lpItem;
	
	lpItem = &lpDefItem->Item;

	ZeroMemory( lpDefItem , sizeof( sDEF_ITEMINFO ) );

	fp = fopen( szItemFile , "rb" );
	if ( fp==NULL ) return FALSE;

	while( !feof( fp ) )					//  feof: file end까지 읽어라 
	{
		if( fgets( line, 255, fp ) == NULL)	
			break;

		p = GetWord( decode , line);
		NextFlag = 0;

		///////////////// 이름 ///////////////////////
		if ( lstrcmp( decode , "*이름" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpItem->ItemName , strBuff );
			NextFlag = TRUE;
		}

#ifdef _LANGUAGE_CHINESE
		if ( lstrcmpi( decode , "*C_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpItem->ItemName , strBuff );
			NextFlag = TRUE;
		}
#endif
#ifdef _LANGUAGE_JAPANESE
		if ( lstrcmpi( decode , "*J_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpItem->ItemName , strBuff );
			NextFlag = TRUE;
		}
#endif
#ifdef _LANGUAGE_TAIWAN
		if ( lstrcmpi( decode , "*T_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpItem->ItemName , strBuff );
			NextFlag = TRUE;
		}
#endif
#ifdef _LANGUAGE_ENGLISH
		if ( lstrcmpi( decode , "*J_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpItem->ItemName , strBuff );
			NextFlag = TRUE;
		}
#endif
#ifdef _LANGUAGE_THAI
		if ( lstrcmpi( decode , "*TH_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpItem->ItemName , strBuff );
			NextFlag = TRUE;
		}
#endif
#ifdef _LANGUAGE_VEITNAM
		if ( lstrcmpi( decode , "*V_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpItem->ItemName , strBuff );
			NextFlag = TRUE;
		}
#endif
#ifdef _LANGUAGE_BRAZIL
		if ( lstrcmpi( decode , "*B_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpItem->ItemName , strBuff );
			NextFlag = TRUE;
		}
#endif
//아르헨티나
#ifdef _LANGUAGE_ARGENTINA
		if ( lstrcmpi( decode , "*A_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpItem->ItemName , strBuff );
			NextFlag = TRUE;
		}
#endif

		///////////////// 코드 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*코드" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			for(cnt=0;cnt<MAX_ITEM;cnt++) {
				if ( lstrcmpi( strBuff , sItem[cnt].LastCategory )==0 ) {
					lpItem->CODE = sItem[cnt].CODE; break; }
			}

			NextFlag = TRUE;
		}

/////////////////////	유니크 아이템	 ////////////////////////////
		///////////////// 코드 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*유니크" )==0 ) {
			p=GetWord(strBuff,p);
			if ( strBuff[0] ) 
				lpItem->UniqueItem = atoi(strBuff);
			else
				lpItem->UniqueItem = TRUE;

			NextFlag = TRUE;
		}

		if ( !NextFlag && lstrcmp( decode , "*유니크색상" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->EffectColor[0] = atoi(strBuff);			//R
			p=GetWord(strBuff,p);
			lpItem->EffectColor[1] = atoi(strBuff);			//G
			p=GetWord(strBuff,p);
			lpItem->EffectColor[2] = atoi(strBuff);			//B
			p=GetWord(strBuff,p);
			lpItem->EffectColor[3] = atoi(strBuff);			//A
			p=GetWord(strBuff,p);
			lpItem->EffectBlink[0] = atoi(strBuff);			//Blink
			p=GetWord(strBuff,p);
			if ( strBuff[0] ) 
				lpItem->ScaleBlink[0] = (int)(atof(strBuff)*fONE);	//Scale

			NextFlag = TRUE;
		}

		if ( !NextFlag && lstrcmp( decode , "*이펙트설정" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->DispEffect = atoi(strBuff);
			NextFlag = TRUE;
		}


/////////////////////	공통사항		 ////////////////////////////

		///////////////// 내구력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*내구력" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sDurability[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sDurability[1] = atoi(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *무게 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*무게" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Weight = atoi(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *가격 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*가격" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Price = atoi(strBuff);
			NextFlag = TRUE;
		}
//////////////////////      원소    ///////////////////////

		if ( !NextFlag && lstrcmp( decode , "*생체" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_BIONIC][0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_BIONIC][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if ( !NextFlag && lstrcmp( decode , "*대자연" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_EARTH][0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_EARTH][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if ( !NextFlag && lstrcmp( decode , "*불" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_FIRE][0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_FIRE][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if ( !NextFlag && lstrcmp( decode , "*냉기" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_ICE][0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_ICE][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if ( !NextFlag && lstrcmp( decode , "*번개" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_LIGHTING][0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_LIGHTING][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if ( !NextFlag && lstrcmp( decode , "*독" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_POISON][0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_POISON][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if ( !NextFlag && lstrcmp( decode , "*물" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_WATER][0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_WATER][1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		if ( !NextFlag && lstrcmp( decode , "*바람" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_WIND][0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sResistance[sITEMINFO_WIND][1] = atoi(strBuff);
			NextFlag = TRUE;
		}



///////////////	공격성능		/////////////

		///////////////// 공격력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*공격력" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sDamage[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sDamage[1] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sDamage[2] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sDamage[3] = atoi(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *사정거리 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*사정거리" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Shooting_Range = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *공격속도 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*공격속도" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Attack_Speed = atoi(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *명중력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*명중력" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sAttack_Rating[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sAttack_Rating[1] = atoi(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *크리티컬힛 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*크리티컬" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Critical_Hit = atoi(strBuff);
			NextFlag = TRUE;
		}

//////////////	방어성능		/////////////


		///////////////// *흡수력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*흡수력" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->fAbsorb[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fAbsorb[1] = (float)atof(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *방어력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*방어력" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sDefence[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sDefence[1] = atoi(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *블럭율 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*블럭율" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->fBlock_Rating[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fBlock_Rating[1] = (float)atof(strBuff);
			NextFlag = TRUE;
		}

//////////////	신발성능		////////////
		///////////////// *이동속도 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*이동속도" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->fSpeed[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fSpeed[1] = (float)atof(strBuff);
			NextFlag = TRUE;
		}
//////////////	팔찌성능		/////////////

		///////////////// *보유공간 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*보유공간" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Potion_Space = atoi(strBuff);
			NextFlag = TRUE;
		}

//////////////	특수능력		/////////////
		///////////////// *마법숙련도 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*마법숙련도" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->fMagic_Mastery = (float)atof(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *마나재생 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*마나재생" )==0 || lstrcmp( decode , "*기력재생" )==0 ) ) {
			p=GetWord(strBuff,p);
			lpDefItem->fMana_Regen[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fMana_Regen[1] = (float)atof(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *라이프재생 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*라이프재생" )==0 || lstrcmp( decode , "*생명력재생" )==0 )) {
			p=GetWord(strBuff,p);
			lpDefItem->fLife_Regen[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fLife_Regen[1] = (float)atof(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *스테미나재생 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*스테미나재생" )==0 || lstrcmp( decode , "*근력재생" )==0 )) {
			p=GetWord(strBuff,p);
			lpDefItem->fStamina_Regen[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fStamina_Regen[1] = (float)atof(strBuff);
			NextFlag = TRUE;

		}
		///////////////// *마나추가 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*마나추가" )==0 || lstrcmp( decode , "*기력추가" )==0 )) {
			p=GetWord(strBuff,p);
			lpDefItem->Increase_Mana[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->Increase_Mana[1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *라이프추가 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*라이프추가" )==0 || lstrcmp( decode , "*생명력추가" )==0 ) ) {
			p=GetWord(strBuff,p);
			lpDefItem->Increase_Life[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->Increase_Life[1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *스테미나추가 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*스테미나추가" )==0 || lstrcmp( decode , "*근력추가" )==0 ) ) {
			p=GetWord(strBuff,p);
			lpDefItem->Increase_Stamina[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->Increase_Stamina[1] = atoi(strBuff);
			NextFlag = TRUE;
		}


//////////////	요구특성		/////////////

		///////////////// *레벨 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*레벨" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Level = atoi(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *힘 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*힘" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Strength = atoi(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *정신력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*정신력" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Spirit = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *재능 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*재능" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Talent = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *민첩성 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*민첩성" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Dexterity = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *건강 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*건강" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->Health = atoi(strBuff);
			NextFlag = TRUE;
		}


/////////////	회복약		 ////////////

		///////////////// *스테미너상승 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*스테미너상승" )==0 || lstrcmp( decode , "*근력상승" )==0 ) ) {
			p=GetWord(strBuff,p);
			lpItem->Stamina[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpItem->Stamina[1] = atoi(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *마나상승 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*마나상승" )==0 || lstrcmp( decode , "*기력상승" )==0 )) {
			p=GetWord(strBuff,p);
			lpItem->Mana[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpItem->Mana[1] = atoi(strBuff);
			NextFlag = TRUE;
		}

		///////////////// *라이프상승 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*라이프상승" )==0 || lstrcmp( decode , "*생명력상승" )==0 )) {
			p=GetWord(strBuff,p);
			lpItem->Life[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpItem->Life[1] = atoi(strBuff);
			NextFlag = TRUE;
		}

//////////////////////////////////////////////////////////
/////////////////// 직업별 특화능력 //////////////////////
//////////////////////////////////////////////////////////

		///////////////// 특화 직업 설정 ///////////////////////////
		if ( !NextFlag && lstrcmp( decode , "**특화" )==0 ) {
			while(1) {
				p=GetWord(strBuff,p);
				if ( strBuff[0]==0 ) break;
				cnt = 0;
				while(1) {
					if ( !JobDataBase[cnt].szName[0] ) break;
					if ( lstrcmpi( JobDataBase[cnt].szName  , strBuff )==0 ) {
						//lpItem->JobCodeMask |= JobDataBase[cnt].JobBitCode;
						lpItem->JobCodeMask = JobDataBase[cnt].JobBitCode;
						break;
					}
					cnt++;
				}
			}

			NextFlag = TRUE;
		}

		///////////////// 랜덤특화 직업 설정 ///////////////////////////
		if ( !NextFlag && lstrcmp( decode , "**특화랜덤" )==0 ) {
			while(1) {
				p=GetWord(strBuff,p);
				if ( strBuff[0]==0 ) break;
				cnt = 0;
				while(1) {
					if ( !JobDataBase[cnt].szName[0] ) break;
					if ( lstrcmpi( JobDataBase[cnt].szName  , strBuff )==0 ) {
						if ( lpDefItem->JobBitCodeRandomCount>=SPECIAL_JOB_RANDOM_MAX ) break;
						lpDefItem->dwJobBitCode_Random[lpDefItem->JobBitCodeRandomCount++] = JobDataBase[cnt].JobBitCode;
						//lpItem->JobCodeMask |= JobDataBase[cnt].JobBitCode;
						break;
					}
					cnt++;
				}
			}

			NextFlag = TRUE;
		}


		/////////////////////////////////////////////////////
		/////////////////// 특화 추가 ///////////////////////
		/////////////////////////////////////////////////////

		///////////////// *흡수력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**흡수력" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->fSpecial_Absorb[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fSpecial_Absorb[1] = (float)atof(strBuff);			
			//lpItem->JobItem.Add_fAbsorb = (float)atof(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *방어력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**방어력" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sSpecial_Defence[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sSpecial_Defence[1] = atoi(strBuff);
//			p=GetWord(strBuff,p);
//			lpItem->JobItem.Add_Defence = atoi(strBuff);
			NextFlag = TRUE;
		}
/*
		if ( !NextFlag && lstrcmp( decode , "*방어력" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sSpecial_Defence[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sDefence[1] = atoi(strBuff);
			NextFlag = TRUE;
		}
*/
		///////////////// *이동속도 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**이동속도" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->fSpecial_fSpeed[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fSpecial_fSpeed[1] = (float)atof(strBuff);
			//lpItem->JobItem.Add_fSpeed = (float)atof(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *블럭율 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**블럭율" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->JobItem.Add_fBlock_Rating = (float)atof(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *공격속도 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**공격속도" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->JobItem.Add_Attack_Speed = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *크리티컬힛 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**크리티컬" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->JobItem.Add_Critical_Hit = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *사정거리 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**사정거리" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->JobItem.Add_Shooting_Range = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *마법숙련도 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**마법숙련도" )==0 ) {
			p=GetWord(strBuff,p);
			//lpItem->JobItem.Add_fMagic_Mastery = (float)atof(strBuff);
			lpDefItem->fSpecial_Magic_Mastery[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fSpecial_Magic_Mastery[1] = (float)atof(strBuff);

			NextFlag = TRUE;
		}


		/////////////////////////////////////////////////////
		/////////////////// 레벨별 상승 /////////////////////
		/////////////////////////////////////////////////////


		///////////////// *마나추가 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "**마나추가" )==0 || lstrcmp( decode , "**기력추가" )==0 ) ) {
			p=GetWord(strBuff,p);
			lpItem->JobItem.Lev_Mana  = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *라이프추가 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "**라이프추가" )==0 || lstrcmp( decode , "**생명력추가" )==0 ) ) {
			p=GetWord(strBuff,p);
			lpItem->JobItem.Lev_Life = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *명중력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**명중력" )==0 ) {
			//lpItem->JobItem.Lev_Attack_Rating = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->Lev_Attack_Rating[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->Lev_Attack_Rating[1] = atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// 공격력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**공격력" )==0 ) {
			p=GetWord(strBuff,p);
			lpItem->JobItem.Lev_Damage[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpItem->JobItem.Lev_Damage[1] = atoi(strBuff);
			NextFlag = TRUE;
		}

		/////////////////////////////////////////////////////
		/////////////////// %비율 상승 //////////////////////
		/////////////////////////////////////////////////////
/*
	float	Per_Mana_Regen;			//마나 재생 
	float	Per_Life_Regen;			//라이프 재생 
	float	Per_Stamina_Regen;		//스테미나 재생
*/
		///////////////// *마나재생 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "**마나재생" )==0 || lstrcmp( decode , "**기력재생" )==0 ) ) {
			p=GetWord(strBuff,p);
			//lpItem->JobItem.Per_Mana_Regen = (float)atof(strBuff);
			lpDefItem->fSpecial_Mana_Regen[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fSpecial_Mana_Regen[1] = (float)atof(strBuff);

			NextFlag = TRUE;
		}
		///////////////// *라이프재생 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "**라이프재생" )==0 || lstrcmp( decode , "**생명력재생" )==0 )) {
			p=GetWord(strBuff,p);
			lpItem->JobItem.Per_Life_Regen = (float)atof(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *스테미나재생 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "**스테미나재생" )==0 || lstrcmp( decode , "**근력재생" )==0 ) ) {
			p=GetWord(strBuff,p);
			lpItem->JobItem.Per_Stamina_Regen = (float)atof(strBuff);
			NextFlag = TRUE;
		}

		if ( !NextFlag && lstrcmp( decode , "*발생제한" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sGenDay[0] = atoi(strBuff);
			NextFlag = TRUE;
		}

		////////////////// 다른 파일에서 계속 읽어 드림 ///////////////
		if ( !NextFlag && lstrcmp( decode , "*연결파일" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			char szNextFile[128];
			GetDirectoryFromFile( szItemFile , szNextFile );
			lstrcat( szNextFile , strBuff );
			NextFlag = TRUE;
			fclose(fp);

			fp = fopen( szNextFile , "rb" );
			if ( fp==NULL ) break;
		}

	}

	if ( lpItem->EffectBlink[0] ) {
		lpItem->EffectBlink[1] = 
			( lpItem->EffectColor[0]+lpItem->EffectColor[1]+lpItem->EffectColor[2]+lpItem->EffectColor[3]+(short)lpItem->DispEffect );
	}

	if (fp) fclose(fp);
	return TRUE;
}


struct szSTATE_CODE {
	char	*szCodeName;
	DWORD	dwCode;
};

szSTATE_CODE	dwCharSoundCode[] = {
	{	"CYCLOPS"	,	snCHAR_SOUND_CYCLOPS },
	{	"HOBGOBLIN"	,	snCHAR_SOUND_HOBGOBLIN },
	{	"IMP"		,	snCHAR_SOUND_IMP },
	{	"MINIG"		,	snCHAR_SOUND_MINIG },
	{	"PLANT"		,	snCHAR_SOUND_PLANT },
	{	"SKELETON"	,	snCHAR_SOUND_SKELETON },
	{	"ZOMBI"		,	snCHAR_SOUND_ZOMBI },
	{	"OBIT"		,	snCHAR_SOUND_OBIT },

	{	"HOPT"		,	snCHAR_SOUND_HOPT },
	{	"BARGON"	,	snCHAR_SOUND_BARGON },
	{	"LEECH"		,	snCHAR_SOUND_LEECH },
	{	"MUSHROOM"	,	snCHAR_SOUND_MUSHROOM },

	{	"ARMA"		,	snCHAR_SOUND_ARMA },
	{	"ARMADIL"	,	snCHAR_SOUND_ARMA },
	{	"SCORPION"	,	snCHAR_SOUND_SCORPION },

	{	"HEADCUTTER",	snCHAR_SOUND_HEADCUTTER },
	{	"SANDLEM"	,	snCHAR_SOUND_SANDLEM },
	{	"WEB"		,	snCHAR_SOUND_WEB },
	{	"HOPYKING"	,	snCHAR_SOUND_HOPYKING },
	{	"CRIP"		,	snCHAR_SOUND_CRIP },
	{	"BUMA"		,	snCHAR_SOUND_BUMA },
	{	"DECOY"		,	snCHAR_SOUND_DECOY },
	{	"DORAL"		,	snCHAR_SOUND_DORAL },
	{	"FIGON"		,	snCHAR_SOUND_FIGON },
	{	"GOLEM"		,	snCHAR_SOUND_STONEGIANT },
	{	"GREVEN"	,	snCHAR_SOUND_GREVEN },
	{	"ILLUSIONKNIGHT" , snCHAR_SOUND_ILLUSIONKNIGHT },
	{	"SKELETONRANGE" , snCHAR_SOUND_SKELETONRANGE },
	{	"SKELETONMELEE" , snCHAR_SOUND_SKELETONMELEE },
	{	"WOLVERLIN" , snCHAR_SOUND_WOLVERLIN },

	//모라이온 신규 추가 몬스터

	{	"RABIE"			, snCHAR_SOUND_RABIE			},
	{	"MUDY"			, snCHAR_SOUND_MUDY				},
	{	"SEN"			, snCHAR_SOUND_SEN				},
	{	"EGAN"			, snCHAR_SOUND_EGAN				},
	{	"BEEDOG"		, snCHAR_SOUND_BEEDOG			},
	{	"MUTANTPLANT"	, snCHAR_SOUND_MUTANTPLANT		},
	{	"MUTANTRABIE"	, snCHAR_SOUND_MUTANTRABIE		},
	{	"MUTANTTREE"	, snCHAR_SOUND_MUTANTTREE		},
	{	"AVELISK"		, snCHAR_SOUND_AVELISK			},
	{	"NAZ"			, snCHAR_SOUND_NAZ				},
	{	"MUMMY"			, snCHAR_SOUND_MUMMY			},
	{	"HULK"			, snCHAR_SOUND_HULK				},
	{	"HUNGKY"		, snCHAR_SOUND_HUNGKY			},
	{	"SUCCUBUS"		, snCHAR_SOUND_SUCCUBUS			},
	{	"DAWLIN"		, snCHAR_SOUND_DAWLIN			},
	{	"SHADOW"		, snCHAR_SOUND_SHADOW			},
	{	"BERSERKER"		, snCHAR_SOUND_BERSERKER		},
	{	"IRONGUARD"		, snCHAR_SOUND_IRONGUARD		},
	{	"FURY"			, snCHAR_SOUND_FURY				},
	{	"SLIVER"		, snCHAR_SOUND_SLIVER			},

	{	"RATOO"			, snCHAR_SOUND_RATOO			},
	{	"STYGIANLORD"	, snCHAR_SOUND_STYGIANLORD		},
	{	"OMICRON"		, snCHAR_SOUND_OMICRON			},
	{	"D-MACHINE"		, snCHAR_SOUND_DMACHINE			},
	{	"METRON"		, snCHAR_SOUND_METRON			},
	{	"MRGHOST"		, snCHAR_SOUND_MRGHOST			},

	{	"VAMPIRICBAT"	, snCHAR_SOUND_VAMPIRICBAT		},
	{	"MIREKEEPER"	, snCHAR_SOUND_MIREKEEPER		},
	{	"MUFFIN"		, snCHAR_SOUND_MUFFIN			},
	{	"SOLIDSNAIL"	, snCHAR_SOUND_SOLIDSNAIL		},
	{	"BEEVIL"		, snCHAR_SOUND_BEEVIL			},
	{	"NIGHTMARE"		, snCHAR_SOUND_NIGHTMARE		},
	{	"STONEGOLEM"	, snCHAR_SOUND_STONEGOLEM		},
	{	"THORNCRAWLER"	, snCHAR_SOUND_THORNCRAWLER		},
	{	"HEAVYGOBLIN"	, snCHAR_SOUND_HEAVYGOBLIN		},
	{	"EVILPLANT"		, snCHAR_SOUND_EVILPLANT		},
	{	"HAUNTINGPLANT"	, snCHAR_SOUND_HAUNTINGPLANT	},
	{	"DARKKNIGHT"	, snCHAR_SOUND_DARKKNIGHT		},
	{	"GUARDIAN-SAINT", snCHAR_SOUND_GUARDIAN_SAINT	},

	/////////////// 아이언 몬스터 추가 //////////////////

	{	"CHAINGOLEM"	, snCHAR_SOUND_CHAINGOLEM		},
	{	"DEADZONE"		, snCHAR_SOUND_DEADZONE			},
	{	"GROTESQUE"		, snCHAR_SOUND_GROTESQUE		},
	{	"HYPERMACHINE"	, snCHAR_SOUND_HYPERMACHINE		},
	{	"IRONFIST"		, snCHAR_SOUND_IRONFIST			},
	{	"MORGON"		, snCHAR_SOUND_MORGON			},
	{	"MOUNTAIN"		, snCHAR_SOUND_MOUNTAIN			},
	{	"RAMPAGE"		, snCHAR_SOUND_RAMPAGE			},
	{	"RUNICGUARDIAN"	, snCHAR_SOUND_RUNICGUARDIAN	},
	{	"SADNESS"		, snCHAR_SOUND_SADNESS			},
	{	"TOWERGOLEM"	, snCHAR_SOUND_TOWERGOLEM		},
	{	"VAMPIRICBEE"	, snCHAR_SOUND_VAMPRICBEE		},
	{	"VAMPIRICMACHINE", snCHAR_SOUND_VAMPRICMACHINE	},
	{	"AVELINARCHER"	, snCHAR_SOUND_AVELIN_ARCHER	},
	{	"AVELINQUEEN"	, snCHAR_SOUND_AVELIN_QUEEN		},
	{	"BABEL"			, snCHAR_SOUND_BABEL			},

	/////////////// 아이스 몬스터 추가 //////////////////
	{	"MYSTIC"		, snCHAR_SOUND_MYSTIC			},
	{	"ICEGOBLIN"		, snCHAR_SOUND_ICEGOBLIN		},
	{	"COLDEYE"		, snCHAR_SOUND_COLDEYE			},
	{	"FROZEN"		, snCHAR_SOUND_FROZEN			},
	{	"ICEGOLEM"		, snCHAR_SOUND_ICEGOLEM			},
	{	"FROST"			, snCHAR_SOUND_FROST			},
	{	"CHAOSCARA"		, snCHAR_SOUND_CHAOSCARA		},
	{	"DEATHKNIGHT"	, snCHAR_SOUND_DEATHKNIGHT		},


	///////////// 그리디호수 몬스터 추가 ////////////////
	{	"GREATE_GREVEN"	, snCHAR_SOUND_GREATE_GREVEN	},
	{	"LIZARDFOLK"	, snCHAR_SOUND_LIZARDFOLK		},
	{	"M_LORD"		, snCHAR_SOUND_M_LORD			},
	{	"SPIDER"		, snCHAR_SOUND_SPIDER			},
	{	"STINGRAY"		, snCHAR_SOUND_STINGRAY			},
	{	"STRIDER"		, snCHAR_SOUND_STRIDER			},
	{	"OMU"			, snCHAR_SOUND_OMU				},

	///////////// 아이스2 몬스터 추가 ////////////////
	{	"TURTLECANNON"	, snCHAR_SOUND_TURTLE_CANNON	},
	{	"DEVILBIRD"		, snCHAR_SOUND_DEVIL_BIRD		},
	{	"BLIZZARDGIANT"	, snCHAR_SOUND_BLIZZARD_GIANT	},
	{	"KELVEZU"		, snCHAR_SOUND_KELVEZU			},


	///////////// 신규필 몬스터 추가 ////////////////
	{	"DARKPHALANX"	, snCHAR_SOUND_DARKPHALANX		},
	{	"BLOODYKNIGHT"	, snCHAR_SOUND_BLOODYKNIGHT		},
	{	"CHIMERA"		, snCHAR_SOUND_CHIMERA			},
	{	"FIREWORM"		, snCHAR_SOUND_FIREWORM			},
	{	"HELLHOUND"		, snCHAR_SOUND_HELLHOUND		},
	{	"DARKGUARD"		, snCHAR_SOUND_DARKGUARD		},
	{	"DARKMAGE"		, snCHAR_SOUND_DARKMAGE			},

	{	"MONMOKOVA"		, snCHAR_SOUND_MOKOVA			},
	{	"MONTEMPLEGUARD", snCHAR_SOUND_TEMPLEGUARD		},
	{	"MONSETO"		, snCHAR_SOUND_SETO				},
	{	"MONKINGSPIDER"	, snCHAR_SOUND_KINGSPIDER		},
	//////////////	pluto 신규필드 몬스터	//////////////
	{	"D_KN"			, snCHAR_SOUND_REVIVED_KNIGHT	},
	{	"D_MAGI"		, snCHAR_SOUND_REVIVED_MAGICIAN },
	{	"D_ATAL"		, snCHAR_SOUND_REVIVED_ATALANTA },
	{	"D_FI"			, snCHAR_SOUND_REVIVED_FIGTHER	},
	{	"D_AR"			, snCHAR_SOUND_REVIVED_ARCHER	},
	{	"D_MECA"		, snCHAR_SOUND_REVIVED_MECANICIAN },
	{	"D_PA"			, snCHAR_SOUND_REVIVED_PIKEMAN	},
	{	"D_PR"			, snCHAR_SOUND_REVIVED_PRIESTESS},
	{	"DEADHOPT"		, snCHAR_SOUND_DEADHOPT			},
	{	"DEADKINGHOPY"	, snCHAR_SOUND_DEADKINGHOPY		},
	{	"GORGON"		, snCHAR_SOUND_GORGON			},
	{	"HOBOGOLEM"		, snCHAR_SOUND_HOBOGOLEM		},
	
	// 박재원 - 저주받은 신전 3층(신규필드 몬스터)
	{	"NIKEN"			, snCHAR_SOUND_NIKEN			},
	{	"MIMIC"			, snCHAR_SOUND_MIMIC			},
	{	"KINGBAT"		, snCHAR_SOUND_KINGBAT			},
	{	"GOBLINSHAMAN"	, snCHAR_SOUND_GOBLINSHAMAN		}, 
	{	"HEST"			, snCHAR_SOUND_HEST				},

	// 박재원 - 끝없는 탑 3층(신규필드 몬스터)
	{	"RUCA"			, snCHAR_SOUND_RUCA				},
	{	"NAZSENIOR"		, snCHAR_SOUND_NAZSENIOR		},
	{	"IGOLATION"		, snCHAR_SOUND_IGOLATION		},
	{	"KAKOA"			, snCHAR_SOUND_KAKOA			}, 
	{	"SPRIN"			, snCHAR_SOUND_SPRIN			},
	{	"UNDEADMAPLE"	, snCHAR_SOUND_UNDEADMAPLE		},
	{	"XETAN"			, snCHAR_SOUND_XETAN			},


	// 박재원 - 복날 이벤트 몬스터 추가
	{	"BEBECHICK"		, snCHAR_SOUND_BEBECHICK		},	// 아기 꼬꼬
	{	"PAPACHICK"		, snCHAR_SOUND_PAPACHICK		},	// 아빠 꼬꼬


	/////////////// 이벤트용 NPC //////////////////
	{	"MORIF"			, snCHAR_SOUND_NPC_MORIF		},
	{	"MOLLYWOLF"		, snCHAR_SOUND_NPC_MOLLYWOLF	},
	{	"SKILLMASTER"	, snCHAR_SOUND_NPC_SKILLMASTER	},
	{	"MAGE"			, snCHAR_SOUND_NPC_MAGICMASTER	},
	{	"WORLDCUP"		, snCHAR_SOUND_WORLDCUP			},
	{	"WATERMELON"		, snCHAR_SOUND_WATERMELON			}, // 장별 - 수박몬스터

	/////////////// 스킬 소환용 //////////////////

	{	"WOLVERIN"			, snCHAR_SOUND_S_WOLVERLIN		},
	{	"METALGOLEM"		, snCHAR_SOUND_S_METALGOLEM		},
	{	"FIREELEMENTAL"		, snCHAR_SOUND_S_F_ELEMENTAL	},


	///////////////// 공성 관련 물체 /////////////////////
	{	"CASTLEDOOR"		, snCHAR_SOUND_CASTLE_DOOR		},
	{	"T_CRYSTAL_R"		, snCHAR_SOUND_CASTLE_CRYSTAL_R	},
	{	"T_CRYSTAL_G"		, snCHAR_SOUND_CASTLE_CRYSTAL_G	},
	{	"T_CRYSTAL_B"		, snCHAR_SOUND_CASTLE_CRYSTAL_B	},
	{	"T_CRYSTAL_N"		, snCHAR_SOUND_CASTLE_CRYSTAL_N	},
	{	"TOWER-B"			, snCHAR_SOUND_CASTLE_TOWER_B	},

	//용병 A,B,C
	{	"SOLDIER_A"			, snCHAR_SOUND_CASTLE_SOLDER_A	},
	{	"SOLDIER_B"			, snCHAR_SOUND_CASTLE_SOLDER_B	},
	{	"SOLDIER_C"			, snCHAR_SOUND_CASTLE_SOLDER_C	},

	// 장별 - 소울스톤
	{	"S_AVELIN"				, snCHAR_SOUND_S_AVELIN	},
	{	"S_BAGON"				, snCHAR_SOUND_S_BAGON	},
	{	"S_BEEDOG"				, snCHAR_SOUND_S_BEEDOG	},
	{	"S_BEEVIL"				, snCHAR_SOUND_S_BEEVIL	},
	{	"S_BERSERKER"			, snCHAR_SOUND_S_BERSERKER	},
	{	"S_BUMA"					, snCHAR_SOUND_S_BUMA	},
	{	"S_COKRIS"				, snCHAR_SOUND_S_COKRIS	},
	{	"S_COLDEYE"			, snCHAR_SOUND_S_COLDEYE	},
	{	"S_CRYPT"				, snCHAR_SOUND_S_CRYPT	},
	{	"S_CYCLOPS"			, snCHAR_SOUND_S_CYCLOPS	},
	{	"S_DEADZONE"			, snCHAR_SOUND_S_DEADZONE	},
	{	"S_DECOY"				, snCHAR_SOUND_S_DECOY	},
	{	"S_D-Machine"			, snCHAR_SOUND_S_DMACHINE	},
	{	"S_EVILSNAIL"			, snCHAR_SOUND_S_EVILSNAIL	},
	{	"S_GREVEN"				, snCHAR_SOUND_S_GREVEN	},
	{	"S_GROTESQUE"		, snCHAR_SOUND_S_GROTESQUE	},
	{	"S_ICEGOBLIN"			, snCHAR_SOUND_S_ICEGOBLIN	},
	{	"S_ICEGOLEM"			, snCHAR_SOUND_S_ICEGOLEM	},
	{	"S_INCUBUS"				, snCHAR_SOUND_S_INCUBUS	},
	{	"S_KINGHOPY"			, snCHAR_SOUND_S_KINGHOPY	},
	{	"S_LEECH"				, snCHAR_SOUND_S_LEECH	},
	{	"S_LIZARDFOLK"		, snCHAR_SOUND_S_LIZARDFOLK	},
	{	"S_MEPHIT"				, snCHAR_SOUND_S_MEPHIT	},
	{	"S_METRON"				, snCHAR_SOUND_S_METRON	},
	{	"S_MUFFIN"				, snCHAR_SOUND_S_MUFFIN	},
	{	"S_MUMMY"				, snCHAR_SOUND_S_MUMMY	},
	{	"S_NAZ"					, snCHAR_SOUND_S_NAZ	},
	{	"S_OMEGA"				, snCHAR_SOUND_S_OMEGA	},
	{	"S_RAMPAGE"			, snCHAR_SOUND_S_RAMPAGE	},
	{	"S_SADNESS"			, snCHAR_SOUND_S_SADNESS	},
	{	"S_SLAUGHTER"			, snCHAR_SOUND_S_SLAUGHTER	},
	{	"S_SLAYON"				, snCHAR_SOUND_S_SLAYON	},
	{	"S_SLIVER"				, snCHAR_SOUND_S_SLIVER	},
	{	"S_TITAN"					, snCHAR_SOUND_S_TITAN	},
	{	"S_TOWERGOLEM"		, snCHAR_SOUND_S_TOWERGOLEM	},
	{	"S_TYPHOON"			, snCHAR_SOUND_S_TYPHOON	},
	{	"S_VAMPIRICBAT"		, snCHAR_SOUND_S_VAMPIRICBAT	},
	{	"S_WITCH"					, snCHAR_SOUND_S_WITCH	},
	{	"S_ZOMBIE"				, snCHAR_SOUND_S_ZOMBIE	},


	{	"" , 0 }
};




char	*szCharSizeCodeName[] = {
	"소형" , "중형" , "중대형" , "대형" , ""
};


//100 분율을 256분율로 변환
int ConvPercent8( int percent100 )
{
	return (percent100*256)/100;
}
//걷는 속도를 실제 속도로 변환
int ConvMoveSpeed( float fSpeed )
{
	int sp;

	sp = (int)( (fSpeed-9)*16 )+fONE;

	return sp;
}

//캐릭터 정보 파일에서 해독하여 설정한다
int smCharDecode( char *szCharFile , smCHAR_INFO *lpCharInfo , smCHAR_MONSTER_INFO	*lpMonInfo , char *lpDialogMessage )
{

	FILE	*fp;
	//char	*szDirecotry;
	char strBuff[256];
	char szFile[128];
	char *p;
	char *pb;
	int NextFlag;
	int cnt;
	int	percent;
	int	DialogFlag;

	DWORD	dwItemCode[32];
	int		ItemCodeCnt;


	lstrcpy( szFile , szCharFile );

	fp = fopen( szFile , "rb" );
	if ( fp==NULL ) return FALSE;

	//파일 이름으로 부터 디렉토리를 찾아 설정
	//szDirecotry = SetDirectoryFromFile( szCharFile );

	lpCharInfo->szModelName2[0] = 0;
	lpCharInfo->wPlayClass[1] = 0;
	lpCharInfo->ArrowPosi[0] = 0;
	lpCharInfo->ArrowPosi[1] = 0;

	if ( lpMonInfo ) {
		ZeroMemory( lpMonInfo , sizeof(smCHAR_MONSTER_INFO) );
		lpMonInfo->MoveRange = 64*fONE;
		lpMonInfo->FallItemCount = 0;
		lpMonInfo->FallItemMax = 0;
		lpMonInfo->FallItemPerMax = 0;

		lpMonInfo->DamageStunPers = 100;			//기본 스턴률 100%
		lpMonInfo->UseEventModel = 0;
	}

	while( !feof( fp ) )//  feof: file end까지 읽어라 
	{
		if( fgets( line, 255, fp ) == NULL)	break;

		p = GetWord( decode , line);

		NextFlag = 0;

		///////////////// 이름 ///////////////////////
		if ( lstrcmp( decode , "*이름" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpCharInfo->szName , strBuff );
			NextFlag = TRUE;
		}

#ifdef	_LANGUAGE_CHINESE
		if ( lstrcmpi( decode , "*C_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			if ( lpMonInfo )
				lstrcpy( lpMonInfo->szName , strBuff );
			else
				lstrcpy( lpCharInfo->szName , strBuff );

			NextFlag = TRUE;
		}
#endif
#ifdef	_LANGUAGE_JAPANESE
		if ( lstrcmpi( decode , "*J_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			if ( lpMonInfo )
				lstrcpy( lpMonInfo->szName , strBuff );
			else
				lstrcpy( lpCharInfo->szName , strBuff );

			NextFlag = TRUE;
		}
#endif
#ifdef	_LANGUAGE_TAIWAN
		if ( lstrcmpi( decode , "*T_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			if ( lpMonInfo )
				lstrcpy( lpMonInfo->szName , strBuff );
			else
				lstrcpy( lpCharInfo->szName , strBuff );

			NextFlag = TRUE;
		}
#endif
#ifdef	_LANGUAGE_ENGLISH
		if ( lstrcmpi( decode , "*J_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			if ( lpMonInfo )
				lstrcpy( lpMonInfo->szName , strBuff );
			else
				lstrcpy( lpCharInfo->szName , strBuff );

			NextFlag = TRUE;
		}
#endif
#ifdef	_LANGUAGE_THAI
		if ( lstrcmpi( decode , "*TH_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			if ( lpMonInfo )
				lstrcpy( lpMonInfo->szName , strBuff );
			else
				lstrcpy( lpCharInfo->szName , strBuff );

			NextFlag = TRUE;
		}
#endif
#ifdef _LANGUAGE_VEITNAM
		if ( lstrcmpi( decode , "*V_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			if ( lpMonInfo )
				lstrcpy( lpMonInfo->szName , strBuff );
			else
				lstrcpy( lpCharInfo->szName , strBuff );

			NextFlag = TRUE;
		}
#endif
#ifdef _LANGUAGE_BRAZIL
		if ( lstrcmpi( decode , "*B_NAME" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			if ( lpMonInfo )
				lstrcpy( lpMonInfo->szName , strBuff );
			else
				lstrcpy( lpCharInfo->szName , strBuff );

			NextFlag = TRUE;
		}
#endif
#ifdef _LANGUAGE_ARGENTINA
		if ( lstrcmpi( decode , "*A_NAME" )==0 ) {
			pb=p;
			p=GetWord(strBuff,p);
			if(strBuff[0]==34)
			{
				p=GetString(strBuff,pb);	//단어 찾기
			}

			if ( lpMonInfo )
				lstrcpy( lpMonInfo->szName , strBuff );
			else
				lstrcpy( lpCharInfo->szName , strBuff );

			NextFlag = TRUE;
		}
#endif

		///////////////// 모양파일 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*모양파일" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			//lstrcpy( lpCharInfo->szModelName, szDirecotry );
			//lstrcat( lpCharInfo->szModelName, strBuff );
			lstrcpy( lpCharInfo->szModelName, strBuff );
			NextFlag = TRUE;
		}

		///////////////// *대화 ///////////////////////

		DialogFlag = 0;

		if ( !NextFlag && lpDialogMessage && lstrcmp( decode , "*대화" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpDialogMessage , strBuff );
			NextFlag = TRUE;
			DialogFlag++;
		}

#ifdef _LANGUAGE_CHINESE
		if ( lpDialogMessage && lstrcmpi( decode , "*C_CHAT" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpDialogMessage , strBuff );
			NextFlag = TRUE;
			DialogFlag++;
		}
#endif

#ifdef _LANGUAGE_JAPANESE
		if ( lpDialogMessage && lstrcmpi( decode , "*J_CHAT" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpDialogMessage , strBuff );
			NextFlag = TRUE;
			DialogFlag++;
		}
#endif

#ifdef _LANGUAGE_TAIWAN
		if ( lpDialogMessage && lstrcmpi( decode , "*T_CHAT" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpDialogMessage , strBuff );
			NextFlag = TRUE;
			DialogFlag++;
		}
#endif
#ifdef _LANGUAGE_ENGLISH
		if ( lpDialogMessage && lstrcmpi( decode , "*E_CHAT" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpDialogMessage , strBuff );
			NextFlag = TRUE;
			DialogFlag++;
		}
#endif
#ifdef _LANGUAGE_THAI
		if ( lpDialogMessage && lstrcmpi( decode , "*TH_CHAT" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpDialogMessage , strBuff );
			NextFlag = TRUE;
			DialogFlag++;
		}
#endif
#ifdef _LANGUAGE_VEITNAM
		if ( lpDialogMessage && lstrcmpi( decode , "*V_CHAT" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpDialogMessage , strBuff );
			NextFlag = TRUE;
			DialogFlag++;
		}
#endif
#ifdef _LANGUAGE_BRAZIL
		if ( lpDialogMessage && lstrcmpi( decode , "*B_CHAT" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpDialogMessage , strBuff );
			NextFlag = TRUE;
			DialogFlag++;
		}
#endif
#ifdef _LANGUAGE_ARGENTINA
		if ( lpDialogMessage && lstrcmpi( decode , "*A_CHAT" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			lstrcpy( lpDialogMessage , strBuff );
			NextFlag = TRUE;
			DialogFlag++;
		}
#endif
		//대사목록 저장
		if ( DialogFlag && lpMonInfo ) {
			if ( lpMonInfo->NpcMsgCount<NPC_MESSAGE_MAX ) {
/*
#ifdef _LANGUAGE_ARGENTINA		//줄바꿈 kyle
				
				char szMessage[512];
				unsigned int iCount = 0;
				unsigned int nMessageSize = 0;

				ZeroMemory(szMessage, sizeof(szMessage));

				nMessageSize = strlen(lpDialogMessage); //npc 대사내용 길이

				for(unsigned int i=0;i<=nMessageSize;i++)
				{
					int y = 0;
					if( (i!= 0) && (iCount % 35) == 0 )
					{
						// 연결된 문자열 사이의 공백 체크
						if( lpDialogMessage[i-1] != 32	&&		
							lpDialogMessage[i] != 32	&&
							lpDialogMessage[i] != 46	)     // 두번째 문자열이 스페이스거나 '.' 이 아닐경우
						{
							szMessage[iCount] = '-';
							iCount++;
							szMessage[iCount] = ' ';//테스트중
							iCount++;
							szMessage[iCount] = ' ';//테스트중
							iCount++;
							szMessage[iCount] = lpDialogMessage[i];
						}
						else
						{
							szMessage[iCount] = lpDialogMessage[i];
						}
					}
					else
					{
						szMessage[iCount] = lpDialogMessage[i];
					}

					iCount++;	
				}

				lpMonInfo->lpNpcMessage[lpMonInfo->NpcMsgCount++] = SetNPCMsg(szMessage);
#else*/
				lpMonInfo->lpNpcMessage[lpMonInfo->NpcMsgCount++] = SetNPCMsg(lpDialogMessage);
//#endif

				
			}
		}

		///////////////// *속성 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*속성" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			if ( lstrcmp( strBuff , "적" )==0 )
				lpCharInfo->State = TRUE;
			else
				lpCharInfo->State = FALSE;

			NextFlag = TRUE;
		}

		///////////////// *크기 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*크기" )==0 ) {
			p=GetWord(strBuff,p);
			cnt = 0;

			lpCharInfo->SizeLevel = -1;

			while(1) {
				if ( szCharSizeCodeName[cnt][0]==0 ) break;
				if ( lstrcmp( szCharSizeCodeName[cnt], strBuff )==0 ) {
					lpCharInfo->SizeLevel = cnt;
				}
				cnt++;
			}
			NextFlag = TRUE;
		}

		///////////////// *소리 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*소리" )==0 || lstrcmp( decode , "*효과음" )==0 ) ) {
			p=GetWord(strBuff,p);
			cnt = 0;

			while(1) {
				if ( dwCharSoundCode[cnt].dwCode==0 ) break;
				if ( lstrcmpi( dwCharSoundCode[cnt].szCodeName , strBuff )==0 ) {
					lpCharInfo->dwCharSoundCode = dwCharSoundCode[cnt].dwCode;
				}
				cnt++;
			}
			NextFlag = TRUE;
		}


		///////////////// *레벨 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*레벨" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Level = atoi( strBuff );
			NextFlag = TRUE;
		}

		///////////////// *계급 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*두목" )==0 ) {
			//p=GetWord(strBuff,p);
			lpCharInfo->wPlayClass[0] = MONSTER_CLASS_BOSS;
			NextFlag = TRUE;
		}

		if ( !NextFlag && lstrcmp( decode , "*계급" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->wPlayClass[0] = atoi(strBuff);
			NextFlag = TRUE;
		}

		/////////////// *계급 크기 /////////////////////
		if ( !NextFlag && lstrcmp( decode , "*모델크기" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->wPlayClass[1] = (short)(atof(strBuff)*fONE);
			if ( lpCharInfo->wPlayClass[1]==fONE ) lpCharInfo->wPlayClass[1]=0;
			NextFlag = TRUE;
		}


		///////////////// *이동속도 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*이동력" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Move_Speed = ConvMoveSpeed( (float)atof( strBuff ) ); 
			NextFlag = TRUE;
		}

		///////////////// *공격력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*공격력" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Attack_Damage[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpCharInfo->Attack_Damage[1] = atoi(strBuff);

			NextFlag = TRUE;
		}

		///////////////// *공격속도 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*공격속도" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Attack_Speed = (int)( atof(strBuff)*fONE );
			p=GetWord(strBuff,p);
			lpCharInfo->Attack_Speed = (int)( atof(strBuff)*fONE );

			NextFlag = TRUE;
		}

		///////////////// *공격범위 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*공격범위" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Shooting_Range = atoi(strBuff)*fONE;
			NextFlag = TRUE;
		}



		///////////////// *명중률 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*명중력" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Attack_Rating = atoi(strBuff);

			NextFlag = TRUE;
		}
	
		///////////////// *방어력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*방어력" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Defence = atoi(strBuff);

			NextFlag = TRUE;
		}
		///////////////// *흡수율 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*흡수율" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Absorption = atoi(strBuff);

			NextFlag = TRUE;
		}
		///////////////// *블럭율 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*블럭율" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Chance_Block = atoi(strBuff);

			NextFlag = TRUE;
		}
	
		///////////////// *라이프 ///////////////////////
		if ( !NextFlag && ( lstrcmp( decode , "*생명력" )==0 || lstrcmp( decode , "*라이프" )==0 ) ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Life[0] = atoi(strBuff);
			lpCharInfo->Life[1] = lpCharInfo->Life[0];

			NextFlag = TRUE;
		}
	
		///////////////// *생체 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*생체" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Resistance[sITEMINFO_BIONIC] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *물 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*물" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Resistance[sITEMINFO_WATER] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *번개 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*번개" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Resistance[sITEMINFO_LIGHTING] = (short)atoi(strBuff);

			NextFlag = TRUE;
		}
		///////////////// *얼음 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*얼음" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Resistance[sITEMINFO_ICE] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *바람 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*바람" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Resistance[sITEMINFO_WIND] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *지동력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*지동력" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Resistance[sITEMINFO_EARTH] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *불 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*불" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Resistance[sITEMINFO_FIRE] = (short)atoi(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *독 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*독" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Resistance[sITEMINFO_POISON] = (short)atof(strBuff);
			NextFlag = TRUE;
		}





//////////////////////////////// 추가분 //////////////////////////////////

		///////////////// *시야 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*시야" )==0 ) {
			p=GetWord(strBuff,p);
			lpCharInfo->Sight = atoi( strBuff );// * fONE;
			if ( lpMonInfo ) lpMonInfo->Real_Sight = lpCharInfo->Sight;

			lpCharInfo->Sight *= lpCharInfo->Sight;			//몬스터 시야 제곱값
			NextFlag = TRUE;
		}

		///////////////// *미니화면 보정 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "*화면보정" )==0 ) {
			p=GetWord(strBuff,p);
			if ( strBuff[0] )
				lpCharInfo->ArrowPosi[0] = atoi( strBuff );

			p=GetWord(strBuff,p);
			if ( strBuff[0] )
				lpCharInfo->ArrowPosi[1] = atoi( strBuff );

		}

		if ( lpMonInfo && !NextFlag ) {

			///////////////// *예비모델 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*예비모델" )==0 ) {
				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기
				lstrcpy( lpCharInfo->szModelName2+1, strBuff ); 
				lpMonInfo->UseEventModel = TRUE;
				NextFlag = TRUE;
			}

			///////////////// *기술공격력 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*기술공격력" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->SkillDamage[0] = atoi(strBuff);
				p=GetWord(strBuff,p);
				lpMonInfo->SkillDamage[1] = atoi(strBuff);

				NextFlag = TRUE;
			}

			///////////////// *기술공격거리 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*기술공격거리" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->SkillDistance = atoi(strBuff);

				NextFlag = TRUE;
			}


			///////////////// *기술공격범위 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*기술공격범위" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->SkillRange = atoi(strBuff);

				NextFlag = TRUE;
			}

			///////////////// *기술공격률 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*기술공격률" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->SkillRating = atoi(strBuff);

				NextFlag = TRUE;
			}

			///////////////// *저주기술설정 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*저주기술" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->SkillCurse = atoi(strBuff);
				NextFlag = TRUE;
			}

			///////////////// *이동타입 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*이동타입" )==0 ) {
				p=GetWord(strBuff,p);

				NextFlag = TRUE;
			}

			///////////////// *공격속도 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*이동범위" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->MoveRange = (int)( atof(strBuff)*fONE );
				NextFlag = TRUE;
			}


			///////////////// *활동시간 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*활동시간" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->ActiveHour = 0;
				if ( lstrcmpi( strBuff , "낮" )==0 )
					lpMonInfo->ActiveHour = 1;
				if ( lstrcmpi( strBuff , "밤" )==0 )
					lpMonInfo->ActiveHour = -1;
				NextFlag = TRUE;
			}

			///////////////// *조직 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*조직" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->GenerateGroup[0] = atoi( strBuff );
				p=GetWord(strBuff,p);
				lpMonInfo->GenerateGroup[1] = atoi( strBuff );
				NextFlag = TRUE;
			}

			///////////////// *지능 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*지능" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->IQ = atoi( strBuff );
				NextFlag = TRUE;
			}

			///////////////// *구별 코드 //////////////////
			if ( !NextFlag && lstrcmp( decode , "*구별코드" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->ClassCode = atoi( strBuff );
				NextFlag = TRUE;
			}

			///////////////// *스턴율 ///////////////////////
			if ( !NextFlag && ( lstrcmp( decode , "*스턴율" )==0 || lstrcmp( decode , "*스턴률" )==0 )) {
				p=GetWord(strBuff,p);
				lpMonInfo->DamageStunPers = atoi( strBuff );
				NextFlag = TRUE;
			}

			///////////////// *품성 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*품성" )==0 ) {
				lpMonInfo->Nature = smCHAR_MONSTER_NATURAL;
				//lpCharInfo->JOB_CODE = smCHAR_MONSTER_NATURAL;
				
				p=GetWord(strBuff,p);
				if ( lstrcmpi( strBuff , "good" )==0 ) {
					lpMonInfo->Nature = smCHAR_MONSTER_GOOD;
					//lpCharInfo->JOB_CODE = smCHAR_MONSTER_GOOD;
				}
				if ( lstrcmpi( strBuff , "evil" )==0 ) {
					lpMonInfo->Nature = smCHAR_MONSTER_EVIL;
					//lpCharInfo->JOB_CODE = smCHAR_MONSTER_EVIL;
				}
				NextFlag = TRUE;
			}

			///////////////// *이벤트 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*이벤트코드" )==0 ) {
				p=GetWord(strBuff,p);
	
				lpMonInfo->EventCode = atoi( strBuff );
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*이벤트정보" )==0 ) {
				p=GetWord(strBuff,p);
	
				lpMonInfo->EventInfo = atoi( strBuff );
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*이벤트아이템" )==0 ) {
				p=GetWord(strBuff,p);

				//코드검색 하여 설정
				for(cnt=0;cnt<MAX_ITEM;cnt++) {
					if ( lstrcmpi( strBuff , sItem[cnt].LastCategory )==0 ) {
						lpMonInfo->dwEvnetItem = sItem[cnt].CODE;
						break;
					}
				}
				NextFlag = TRUE;
			}


			///////////////// *특수공격률 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*특수공격률" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->SpAttackPercetage = ConvPercent8( atoi( strBuff ) );
				NextFlag = TRUE;
			}
			///////////////// *언데드 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*언데드" )==0 ) {
				p=GetWord(strBuff,p);
				if ( lstrcmp( strBuff , "유" )==0 || lstrcmp( strBuff , "있음" )==0 ) {
					lpMonInfo->Undead = TRUE;
					lpCharInfo->Brood = smCHAR_MONSTER_UNDEAD;
				}
				else {
					lpMonInfo->Undead = FALSE;
					lpCharInfo->Brood = smCHAR_MONSTER_NORMAL;
				}

				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*몬스터종족" )==0 ) {
				p=GetWord(strBuff,p);
				if ( strBuff[0] ) {

					lpCharInfo->Brood = smCHAR_MONSTER_NORMAL;

					if ( lstrcmp( strBuff , "언데드" )==0 ) {
						lpCharInfo->Brood = smCHAR_MONSTER_UNDEAD;
					}
					else if ( lstrcmp( strBuff , "뮤턴트" )==0 ) {
						lpCharInfo->Brood = smCHAR_MONSTER_MUTANT;
					}
					else if ( lstrcmp( strBuff , "디먼" )==0 ) {
						lpCharInfo->Brood = smCHAR_MONSTER_DEMON;
					}
					else if ( lstrcmp( strBuff , "메카닉" )==0 ) {
						lpCharInfo->Brood = smCHAR_MONSTER_MECHANIC;
					}
				}
			}


			///////////////// *경험치 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*경험치" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->GetExp = atoi( strBuff );
				lpCharInfo->Exp = lpMonInfo->GetExp;
				NextFlag = TRUE;
			}

			///////////////// *물약 보유 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*물약보유수" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->PotionCount = atoi( strBuff );
				NextFlag = TRUE;
			}

			///////////////// *물약 보유 ///////////////////////
			if ( !NextFlag && lstrcmp( decode , "*물약보유률" )==0 ) {
				p=GetWord(strBuff,p);
				lpMonInfo->PotionPercent = atoi( strBuff );
				NextFlag = TRUE;
			}
//	int		PotionCount;		//물약 보유수
//	int		PotionPercent;		//물약 보유률


			if ( !NextFlag && lstrcmp( decode , "*아이템모두" )==0 ) {	//땅에 떨어질때 모두에게 아이템 보임
				lpMonInfo->AllSeeItem = TRUE;
				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*아이템카운터" )==0 ) {
				p = GetWord( strBuff , p );			//확률
				lpMonInfo->FallItemMax = atoi( strBuff );
				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*추가아이템" )==0 ) {
				p = GetWord( strBuff , p );			//확률
				lpMonInfo->FallItems_Plus[ lpMonInfo->FallItemPlusCount ].Percentage = atoi(strBuff);

				p = GetWord( strBuff , p );			//아이템 코드
				if ( strBuff[0] && lpMonInfo->FallItemPlusCount<FALLITEM2_MAX ) {
					for(cnt=0;cnt<MAX_ITEM;cnt++) {
						if ( lstrcmpi( strBuff , sItem[cnt].LastCategory )==0 ) {
							lpMonInfo->FallItems_Plus[ lpMonInfo->FallItemPlusCount ].dwItemCode = sItem[cnt].CODE;
							lpMonInfo->FallItemPlusCount++;
							break;
						}
					}
				}
				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*아이템" )==0 ) {
				p = GetWord( strBuff , p );			//확률
				percent = atoi( strBuff );

				lpMonInfo->FallItemPerMax += percent;

				p = GetWord( strBuff , p );			//확률
				if ( lstrcmp( strBuff , "없음" )==0 ) {
					//테스트 서버 안나올 확률 적계
					if ( rsServerConfig.TestSeverMode ) {
						lpMonInfo->FallItemPerMax -= percent;
						percent /= 2;
						lpMonInfo->FallItemPerMax += percent;
					}

					//안떨어질 확률
					lpMonInfo->FallItems[ lpMonInfo->FallItemCount ].dwItemCode = 0;
					lpMonInfo->FallItems[ lpMonInfo->FallItemCount ].Percentage = percent;
					lpMonInfo->FallItemCount ++;
				}
				else {
					if ( lstrcmp( strBuff , "돈" )==0 ) {
						//돈 떨어질 확률
						lpMonInfo->FallItems[ lpMonInfo->FallItemCount ].dwItemCode = sinGG1|sin01;
						p=GetWord( strBuff , p );
						lpMonInfo->FallItems[ lpMonInfo->FallItemCount ].sPrice[0] = atoi(strBuff);
						p=GetWord( strBuff , p );
						lpMonInfo->FallItems[ lpMonInfo->FallItemCount ].sPrice[1] = atoi(strBuff);
						lpMonInfo->FallItems[ lpMonInfo->FallItemCount ].Percentage = percent;
						lpMonInfo->FallItemCount ++;
					}
					else {
						//아이템 떨어질 확률
						ItemCodeCnt = 0;

						while(1) {
							if ( strBuff[0] ) {
								//코드검색 하여 설정
								for(cnt=0;cnt<MAX_ITEM;cnt++) {
									if ( lstrcmpi( strBuff , sItem[cnt].LastCategory )==0 ) {
										dwItemCode[ItemCodeCnt++] = sItem[cnt].CODE;
										break;
									}
								}
							}
							else 
								{ break; }

							strBuff[0] = 0;
							if ( p[0]==0 ) break;
							p = GetWord( strBuff , p );
						}

						if ( ItemCodeCnt>0 ) {
							//아이템 테이블에 저장
							percent = percent/ItemCodeCnt;
							for( cnt=0;cnt<ItemCodeCnt;cnt++ ) {
								lpMonInfo->FallItems[ lpMonInfo->FallItemCount ].dwItemCode = dwItemCode[cnt];
								lpMonInfo->FallItems[ lpMonInfo->FallItemCount ].Percentage = percent;
								lpMonInfo->FallItemCount ++;
							}
						}
					}
				}
				NextFlag = TRUE;
			}

			///////////////// NPC 물건 판매 정보 /////////////////////
			if ( !NextFlag && lstrcmp( decode , "*무기판매" )==0 ) {
				while(1) {
					pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기
					if ( strBuff[0]==0 ) break;
					if ( lpMonInfo->SellAttackItemCount>=32 ) break;
					for( cnt=0;cnt<MAX_ITEM;cnt++) {
						if ( lstrcmpi( strBuff , sItem[cnt].LastCategory )==0 ) {
							lpMonInfo->SellAttackItem[lpMonInfo->SellAttackItemCount++] =
								(void *)sItem[cnt].CODE;
							break;
						}
					}
				}
				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*방어구판매" )==0 ) {
				while(1) {
					pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기
					if ( strBuff[0]==0 ) break;
					if ( lpMonInfo->SellDefenceItemCount>=32 ) break;
					for( cnt=0;cnt<MAX_ITEM;cnt++) {
						if ( lstrcmpi( strBuff , sItem[cnt].LastCategory )==0 ) {
							lpMonInfo->SellDefenceItem[lpMonInfo->SellDefenceItemCount++] =
								(void *)sItem[cnt].CODE;
							break;
						}
					}
				}
				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*잡화판매" )==0 ) {
				while(1) {
					pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기
					if ( strBuff[0]==0 ) break;
					if ( lpMonInfo->SellEtcItemCount>=32 ) break;
					for( cnt=0;cnt<MAX_ITEM;cnt++) {
						if ( lstrcmpi( strBuff , sItem[cnt].LastCategory )==0 ) {
							lpMonInfo->SellEtcItem[lpMonInfo->SellEtcItemCount++] =
								(void *)sItem[cnt].CODE;
							break;
						}
					}
				}
				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*스킬수련" )==0 ) {
				lpMonInfo->SkillMaster = TRUE;
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*직업전환" )==0 ) {
				lpMonInfo->SkillChangeJob = TRUE;

				p=GetWord( strBuff , p );
				if ( strBuff[0] )
					lpMonInfo->SkillChangeJob = atoi(strBuff);

				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*이벤트매표소" )==0 ) {
				p=GetWord( strBuff , p );
				if ( strBuff[0] )
					lpMonInfo->EventNPC = atoi(strBuff);
				else
					lpMonInfo->EventNPC = 1;

				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*아이템보관" )==0 ) {
				lpMonInfo->WareHouseMaster = TRUE;
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*아이템조합" )==0 ) {
				lpMonInfo->ItemMix = TRUE;
				NextFlag = TRUE;
			}
			// pluto 제련
			if( !NextFlag && lstrcmp( decode , "*아이템제련" ) == 0 )
			{
				lpMonInfo->Smelting = TRUE;
				NextFlag = TRUE;
			}
			// pluto 제작
			if( !NextFlag && lstrcmp( decode, "*아이템제작" ) == 0 )
			{
                lpMonInfo->Manufacture = TRUE;
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*아이템연금" )==0 ) {
				lpMonInfo->ItemMix = 200;
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*아이템에이징" )==0 ) {
				lpMonInfo->ItemAging = TRUE;
				NextFlag = TRUE;
			}
			// 석지용 - 믹스쳐 리셋
			if( !NextFlag && lstrcmp( decode, "*믹스처리셋" ) == 0 )
			{
				lpMonInfo->MixtureReset = TRUE;
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*모금함" )==0 ) {
				lpMonInfo->CollectMoney = TRUE;
				NextFlag = TRUE;
			}
#ifdef _LANGUAGE_VEITNAM
			if ( !NextFlag && lstrcmp( decode , "*꽝이지롱" )==0 ) {
				lpMonInfo->WowEvent = TRUE;
				NextFlag = TRUE;
			}
#endif
			if ( !NextFlag && lstrcmp( decode , "*경품추첨" )==0 ) {
				lpMonInfo->EventGift = TRUE;
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*클랜기능" )==0 ) {
				lpMonInfo->ClanNPC = TRUE;
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*경품배달" )==0 ) {
				lpMonInfo->GiftExpress = TRUE;
				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*윙퀘스트" )==0 ) {
				p=GetWord( strBuff , p );
				if ( strBuff[0] )
					lpMonInfo->WingQuestNpc = atoi(strBuff);
				else
					lpMonInfo->WingQuestNpc = 1;
				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*퀘스트이벤트" )==0 ) {

				p=GetWord( strBuff , p );
				if ( strBuff[0] )
					lpMonInfo->WingQuestNpc = atoi(strBuff);
				else
					lpMonInfo->WingQuestNpc = 2;

				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*별포인트적립" )==0 ) {
				p=GetWord( strBuff , p );
				if ( strBuff[0] )
					lpMonInfo->StarPointNpc = atoi(strBuff);
				else
					lpMonInfo->StarPointNpc = 20;

				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*기부함" )==0 ) {
				lpMonInfo->GiveMoneyNpc = TRUE;
				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*텔레포트" )==0 ) {
				p=GetWord( strBuff , p );
				if ( strBuff[0] )
					lpMonInfo->TelePortNpc = atoi(strBuff);
				else
					lpMonInfo->TelePortNpc = 1;

				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*블레스캐슬" )==0 ) {
				p=GetWord( strBuff , p );
				if ( strBuff[0] )
					lpMonInfo->BlessCastleNPC = atoi(strBuff);
				else
					lpMonInfo->BlessCastleNPC = 1;

				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*설문조사" )==0 ) {
				p=GetWord( strBuff , p );
				if ( strBuff[0] )
					lpMonInfo->PollingNpc = atoi(strBuff);
				else
					lpMonInfo->PollingNpc = 1;

				NextFlag = TRUE;
			}

			if ( !NextFlag && lstrcmp( decode , "*동영상제목" )==0 ) {
				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기
				if ( strBuff[0] ) {
					lpMonInfo->szMediaPlayNPC_Title = SetNPCMsg(strBuff);
				}
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*동영상경로" )==0 ) {
				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기
				if ( strBuff[0] ) {
					lpMonInfo->szMediaPlayNPC_Path = SetNPCMsg(strBuff);
				}
				NextFlag = TRUE;
			}
			
			if ( !NextFlag && lstrcmp( decode , "*출현간격" )==0 ) {
				p=GetWord( strBuff , p );
				lpMonInfo->OpenCount[0] = atoi(strBuff);		//출현 번호
				p=GetWord( strBuff , p );
				lpMonInfo->OpenCount[1] = atoi(strBuff);		//랜덤 카운트
				NextFlag = TRUE;
			}
			if ( !NextFlag && lstrcmp( decode , "*퀘스트코드" )==0 ) {
				p=GetWord( strBuff , p );
				lpMonInfo->QuestCode = atoi(strBuff);		//퀘스트 코드
				p=GetWord( strBuff , p );
				lpMonInfo->QuestParam = atoi(strBuff);		//퀘스트 파라메터
				NextFlag = TRUE;
			}
		}

		////////////////// 다른 파일에서 계속 읽어 드림 ///////////////
		if ( !NextFlag && lstrcmp( decode , "*연결파일" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기

			char szNextFile[128];
			GetDirectoryFromFile( szFile , szNextFile );
			lstrcat( szNextFile , strBuff );
			NextFlag = TRUE;
			fclose(fp);

			fp = fopen( szNextFile , "rb" );
			if ( fp==NULL ) break;
		}

	}

	//몬스터 구조체 연결
	if ( lpMonInfo )
		lpCharInfo->lpMonInfo = lpMonInfo;
	else
		lpCharInfo->lpMonInfo = 0;


	if (fp) fclose(fp);

	return TRUE;
}

//몬스터 출현 정보 파일에서 해독하여 설정한다
int DecodeOpenMonster( char *szCharFile , rsSTG_MONSTER_LIST *lpStgMonList , smCHAR_INFO *lpCharInfoList, int ListCnt )
{

	FILE	*fp;
	char strBuff[64];
	char *p;
	char *pb;
	int NextFlag;
	int cnt,MonCnt,PercentCnt;
	sBOSS_MONSTER *lpBossMonster;

	ZeroMemory( lpStgMonList , sizeof( rsSTG_MONSTER ) * rsSTG_MONSTER_MAX );

	//기본 값 설정
	lpStgMonList->OpenInterval = 0x7F;
	lpStgMonList->OpenLimit = 3;

	fp = fopen( szCharFile , "rb" );
	if ( fp==NULL ) return FALSE;

	MonCnt = 0;
	PercentCnt = 0;

	while( !feof( fp ) )//  feof: file end까지 읽어라 
	{
		if( fgets( line, 255, fp ) == NULL)	break;

		p = GetWord( decode , line);

		NextFlag = 0;

		///////////////// 이름 ///////////////////////
		if ( lstrcmp( decode , "*출연자" )==0 || lstrcmpi( decode , "*ACTOR" )==0 ) {
			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//단어 찾기
			lstrcpy( lpStgMonList->rsMonster[MonCnt].szMonsterName , strBuff );
			for(cnt=0;cnt<ListCnt;cnt++) {
				if ( lstrcmp( strBuff , lpCharInfoList[cnt].szName )==0 ) {
					lpStgMonList->rsMonster[MonCnt].lpCharInfo = &lpCharInfoList[cnt];
					//출현빈도
					p=GetWord(strBuff,p);
					cnt = atoi( strBuff );
					lpStgMonList->rsMonster[MonCnt].NumOpenStart = PercentCnt;
					lpStgMonList->rsMonster[MonCnt].OpenPercentage = cnt;
					PercentCnt += cnt;
					MonCnt ++;
					break;
				}
			}

			NextFlag = TRUE;
		}

		if ( lstrcmp( decode , "*출연자두목" )==0 || lstrcmpi( decode , "*BOSS_ACTOR" )==0 ) {

			lpBossMonster = &lpStgMonList->sBossMonsters[lpStgMonList->BossMonsterCount];

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//보스 몬스터 이름
			for(cnt=0;cnt<ListCnt;cnt++) {
				if ( lstrcmp( strBuff , lpCharInfoList[cnt].szName )==0 ) {
					lpBossMonster->MasterMonster = &lpCharInfoList[cnt];
					break;
				}
			}

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	//보조 몬스터 이름
			for(cnt=0;cnt<ListCnt;cnt++) {
				if ( lstrcmp( strBuff , lpCharInfoList[cnt].szName )==0 ) {
					lpBossMonster->SlaveMonster = &lpCharInfoList[cnt];
					break;
				}
			}

			p=GetWord(strBuff,p);		// 보조 출연 최대인원
			lpBossMonster->SlaveCount = atoi( strBuff );


			for( cnt=0;cnt<32;cnt++) {
				p=GetWord(strBuff,p);		// 출연 시간
				if ( !strBuff[0] ) break;
				lpBossMonster->bOpenTime[ lpBossMonster->OpenTimeCount++ ] = atoi( strBuff );
			}

			lpStgMonList->BossMonsterCount++;
			NextFlag = TRUE;
		}


		if ( !NextFlag && ( lstrcmp( decode , "*최대동시출현수" )==0 || lstrcmp( decode , "*MAX_ACTOR_POS" )==0 )) {
			p=GetWord(strBuff,p);
			lpStgMonList->LimitMax = atoi( strBuff );		
			NextFlag = TRUE;
		}

		if ( !NextFlag && ( lstrcmp( decode , "*출현간격" )==0 || lstrcmp( decode , "*DELAY" )==0 ) ) {
			p=GetWord(strBuff,p);
			lpStgMonList->OpenInterval = (1<<atoi( strBuff ));
			if (lpStgMonList->OpenInterval>1) lpStgMonList->OpenInterval--;

			p=GetWord(strBuff,p);
			if ( strBuff[0] )
				lpStgMonList->dwIntervalTime = atoi( strBuff )*1000;

			NextFlag = TRUE;
		}

		if ( !NextFlag && ( lstrcmp( decode , "*출현수" )==0 || lstrcmp( decode , "*MAX_ACTOR" )==0 ) ) {
			p=GetWord(strBuff,p);
			lpStgMonList->OpenLimit = atoi( strBuff );
			NextFlag = TRUE;
		}


	}
	lpStgMonList->Counter		= MonCnt;
	lpStgMonList->PecetageCount = PercentCnt;


	fclose(fp);

	return TRUE;
}


//최소 최대치에서 랜덤값 산출
int GetRandomPos( int Min , int Max )
{
	int sb;
	int rnd;

	sb = (Max+1)-Min;

	if ( sb==0 ) return Max;

	rnd = rand()%sb;
	return Min+rnd;
}

//최소 최대치에서 랜덤값 산출
float GetRandomFloatPos( float Min , float Max )
{
	int sb;
	int rnd;

	sb = (int)(( Max - Min)*100.0f);

	if ( sb==0 ) return Max;

	rnd = rand()%(sb+1);
	return Min+((float)((float)rnd/100.0f));
}

//최소 최대치에서 랜덤값 산출 ( 소수점 1자리 )
float GetRandomFloatPos2( float Min , float Max )
{
	int sb;
	int rnd;

	sb = (int)(( Max - Min)*10.0f);

	if ( sb==0 ) return Max;

	rnd = rand()%(sb+1);
	return Min+((float)((float)rnd/10.0f));
}


//최소 최대치에서 랜덤값 산출
int GetMiddlePos( int Min , int Max )
{
	int sb;

	sb = (Max-Min)/2;

	return Min+sb;
}


///////////////////////////////////////
static int	Random_NormalMode = 0;

//최소 최대치에서 랜덤값 산출
int GetRandomPos_Normal( int inMin , int inMax )
{
	int sb,sc;
	int rnd;
	int	Min,Max;

	if ( !Random_NormalMode ) 
		return GetRandomPos( inMin , inMax );

	sc = inMax-inMin;
	sb = sc/4;

	if ( sb==0 && sc>=2 ) sb=1;

	Min = inMin+sb;
	Max = inMax-sb;

	sb = (Max+1)-Min;

	if ( sb==0 ) return Max;

	rnd = rand()%sb;
	return Min+rnd;
}

struct sSPECIAL_REVISION
{
	DWORD	dwJobCode;
	short	sLevel[2];
	short	sStrength[2];
	short	sSpirit[2];
	short	sTalent[2];
	short	sDexterity[2];
	short	sHealth[2];
};

#define	sSPECIAL_REVISION_MAX		8

// 특화 지업별  요구 능력치 보정표
sSPECIAL_REVISION	sSpecialRevision[sSPECIAL_REVISION_MAX] = {
	//      직업                레벨     힘			정신       재능			민첩        건강
	{ JOB_CODE_MECHANICIAN,		0,0,	5,15,		-20,-10,	0,0,		-25,-15,	0,0		},
	{ JOB_CODE_FIGHTER,			0,0,	10,15,		-20,-15,	0,0,		-20,-15,	0,0		},
	{ JOB_CODE_PIKEMAN,			0,0,	10,15,		-20,-15,	0,0,		-25,-15,	0,0		},
	{ JOB_CODE_ARCHER,			0,0,	-25,-15,	-20,-10,	0,0,		15,25,		0,0		},
	{ JOB_CODE_KNIGHT,			0,0,	5,15,		-15,-10,	5,10,		-25,-15,	0,0		},
	{ JOB_CODE_ATALANTA,		0,0,	-20,-15,	-20,-10,	0,0,		15,25,		0,0		},
	{ JOB_CODE_PRIEST,			0,0,	-25,-20,	15,20,		-15,-10,	-20,-15,	0,0		},
	{ JOB_CODE_MAGICIAN,		0,0,	-25,-20,	15,25,		-15,-10,	-20,-15,	0,0		}
};

//아이템 생성
int CreateDefItem( sITEMINFO *lpItem , sDEF_ITEMINFO *lpDefItem , int SpJobCode , int ItemNormam )
{
	int is,ie;
	int cnt;
	JOB_DATA_CODE	*lpJobDataCode = 0;

	Random_NormalMode = ItemNormam;

	//--------------------------------------------------------------< _ignore_bug_fix_0x00000000_	//해외
	//ZeroMemory(lpItem,sizeof(sITEMINFO));
	//--------------------------------------------------------------  _ignore_bug_fix_0x00000000_ >
	memcpy( lpItem , &lpDefItem->Item , sizeof(sITEMINFO) );

	//내구력 설정
	if ( lpDefItem->sDurability[0] ) {

		if ( lpDefItem->sDurability[1] )
			lpItem->Durability[1] = GetRandomPos_Normal(lpDefItem->sDurability[0],lpDefItem->sDurability[1]);
		else
			lpItem->Durability[1] = lpDefItem->sDurability[0];

		ie = lpItem->Durability[1];
		is = ie/2;
		lpItem->Durability[0] = GetRandomPos_Normal( is, ie );
	}

	//8개의 원소값 설정
	for( cnt=0;cnt<8;cnt++ ) {
		if ( lpDefItem->sResistance[cnt][1] ) {
			lpItem->Resistance[cnt] = 
				GetRandomPos_Normal( lpDefItem->sResistance[cnt][0] , lpDefItem->sResistance[cnt][1] );
		}
		else
			lpItem->Resistance[cnt] = lpDefItem->sResistance[cnt][0];
	}

	//공격력 설정
	if ( lpDefItem->sDamage[1] || lpDefItem->sDamage[3] ) {
		lpItem->Damage[0] = GetRandomPos_Normal(lpDefItem->sDamage[0],lpDefItem->sDamage[1]);
		lpItem->Damage[1] = GetRandomPos_Normal(lpDefItem->sDamage[2],lpDefItem->sDamage[3]);
	}

	//명중력 설정
	if ( lpDefItem->sAttack_Rating[1] ) 
		lpItem->Attack_Rating = GetRandomPos_Normal(lpDefItem->sAttack_Rating[0],lpDefItem->sAttack_Rating[1]);
	else
		lpItem->Attack_Rating = lpDefItem->sAttack_Rating[0];

	//흡수력 설정
	if ( lpDefItem->fAbsorb[1]!=0 ) 
		lpItem->fAbsorb = GetRandomFloatPos2(lpDefItem->fAbsorb[0],lpDefItem->fAbsorb[1]);
	else
		lpItem->fAbsorb = lpDefItem->fAbsorb[0];

	//방어력 설정
	if ( lpDefItem->sDefence[1] )
		lpItem->Defence = GetRandomPos_Normal(lpDefItem->sDefence[0],lpDefItem->sDefence[1]);
	else
		lpItem->Defence = lpDefItem->sDefence[0];

	//블럭율 설정
	if ( lpDefItem->fBlock_Rating[1]!=0 )
		lpItem->fBlock_Rating = GetRandomFloatPos(lpDefItem->fBlock_Rating[0],lpDefItem->fBlock_Rating[1]);
	else
		lpItem->fBlock_Rating = lpDefItem->fBlock_Rating[0];


	//이동속도 설정
	if ( lpDefItem->fSpeed[1]!=0 )
		lpItem->fSpeed = GetRandomFloatPos2(lpDefItem->fSpeed[0],lpDefItem->fSpeed[1]);
	else
		lpItem->fSpeed = lpDefItem->fSpeed[0];


	//마나재생
	if ( lpDefItem->fMana_Regen[1]!=0 )
		lpItem->fMana_Regen = GetRandomFloatPos2(lpDefItem->fMana_Regen[0],lpDefItem->fMana_Regen[1]);
	else
		lpItem->fMana_Regen = lpDefItem->fMana_Regen[0];

	//라이프재생
	if ( lpDefItem->fLife_Regen[1]!=0 )
		lpItem->fLife_Regen = GetRandomFloatPos2(lpDefItem->fLife_Regen[0],lpDefItem->fLife_Regen[1]);
	else
		lpItem->fLife_Regen = lpDefItem->fLife_Regen[0];

	//스테미나재생
	if ( lpDefItem->fStamina_Regen[1]!=0 )
		lpItem->fStamina_Regen = GetRandomFloatPos2(lpDefItem->fStamina_Regen[0],lpDefItem->fStamina_Regen[1]);
	else
		lpItem->fStamina_Regen = lpDefItem->fStamina_Regen[0];


	//라이프 증가
	if ( lpDefItem->Increase_Life[1] )
		lpItem->fIncrease_Life = (float)GetRandomPos_Normal(lpDefItem->Increase_Life[0],lpDefItem->Increase_Life[1]);
	else
		lpItem->fIncrease_Life = (float)lpDefItem->Increase_Life[0];

	//마나 증가
	if ( lpDefItem->Increase_Mana[1] )
		lpItem->fIncrease_Mana = (float)GetRandomPos_Normal(lpDefItem->Increase_Mana[0],lpDefItem->Increase_Mana[1]);
	else
		lpItem->fIncrease_Mana = (float)lpDefItem->Increase_Mana[0];

	//스테미나 증가
	if ( lpDefItem->Increase_Stamina[1] )
		lpItem->fIncrease_Stamina = (float)GetRandomPos_Normal(lpDefItem->Increase_Stamina[0],lpDefItem->Increase_Stamina[1]);
	else
		lpItem->fIncrease_Stamina = (float)lpDefItem->Increase_Stamina[0];




	DWORD	dwSpecialJob;
	int		RndPos;
	int		Revision;
	int		tempJobCode = 0; // 박재원 - 리스펙 스톤
	
	// 박재원 - 리스펙 스톤
	if(SpJobCode>=100)
	{
		tempJobCode = SpJobCode - 100; // 자신의 직업코드를 얻는다. tempJobCode
		SpJobCode = 0;
	}

	if ( SpJobCode>0 ) {
		lpJobDataCode = GetJobDataCode(	SpJobCode, 0 );

		if ( lpJobDataCode ) {
			dwSpecialJob = lpJobDataCode->JobBitCode;

			for(cnt=0;cnt<lpDefItem->JobBitCodeRandomCount;cnt++) {
				if ( lpDefItem->dwJobBitCode_Random[cnt]==dwSpecialJob ) break;
			}
			if ( cnt>=lpDefItem->JobBitCodeRandomCount ) {
				if ( dwSpecialJob!=lpItem->JobCodeMask ) SpJobCode = 0;		//특화 발생 불가 아이템
			}
		}
	}


	if ( lpItem->JobCodeMask || lpDefItem->JobBitCodeRandomCount || SpJobCode ) {
		//특화 아이템 설정

		//랜덤 특화직업 추가
		cnt = rand()%10;			//특화 추가될 확률 20%

		// 석지용 - 믹스쳐 리셋 (무특화를 위해 완죤 날치기를....;;;)
		if( NotItemSpecial )
		{
			cnt = 100;
			NotItemSpecial = 0;
		}

		if ( cnt<=3 || SpJobCode ) {
			//&& lpDefItem->JobBitCodeRandomCount ) {

			cnt = rand()%10;			//기본 특화 확률 70%

			dwSpecialJob = lpItem->JobCodeMask;

			if ( cnt<3 && lpDefItem->JobBitCodeRandomCount ) {
				lpItem->JobCodeMask = 0;
			}

			if ( !lpItem->JobCodeMask && lpDefItem->JobBitCodeRandomCount ) 
			{
				if(tempJobCode>0) // 박재원 - 리스펙 스톤
				{
					lpJobDataCode = GetJobDataCode(	tempJobCode, 0 );
					if(lpJobDataCode)
					{
						cnt = rand()%lpDefItem->JobBitCodeRandomCount;
						while(lpDefItem->dwJobBitCode_Random[cnt] == lpJobDataCode->JobBitCode) // 박재원 - 내 직업코드와 아이템 직업코드가 같을 경우 다른 직업코드가 나올때까지 반복한다.
						{
							cnt = rand()%lpDefItem->JobBitCodeRandomCount;
							if(lpDefItem->dwJobBitCode_Random[cnt] != lpJobDataCode->JobBitCode) 
							{
								dwSpecialJob = lpDefItem->dwJobBitCode_Random[cnt];
								lpItem->JobCodeMask = dwSpecialJob;			
								break;						
							}	
						}
					}
				}
				else //추가 특화 직업
				{
					cnt = rand()%lpDefItem->JobBitCodeRandomCount;
					dwSpecialJob = lpDefItem->dwJobBitCode_Random[cnt];
					lpItem->JobCodeMask = dwSpecialJob;
				}
			}

			if ( SpJobCode>0 ) {
				//강제 특화 발생
				lpJobDataCode = GetJobDataCode(	SpJobCode, 0 );
				if ( lpJobDataCode ) {
					dwSpecialJob = lpJobDataCode->JobBitCode;
					lpItem->JobCodeMask = dwSpecialJob;
				}
			}

			// 장별 - 리스펙스톤 사용시 가격 버그 수정
			if( lpItem->JobCodeMask) lpItem->Price += (lpItem->Price*2)/10;		//특화 가격 상승 20%
				


			// 특화 지업별  요구능력치 보정
			for( cnt=0;cnt<sSPECIAL_REVISION_MAX;cnt++ ) {
				if ( sSpecialRevision[cnt].dwJobCode==dwSpecialJob ) {
					//레벨
					if ( lpItem->Level && sSpecialRevision[cnt].sLevel[0] ) {
						RndPos = GetRandomPos_Normal( sSpecialRevision[cnt].sLevel[0] , sSpecialRevision[cnt].sLevel[1] );
						Revision = (lpItem->Level*RndPos)/100;
						lpItem->Level += Revision;
					}
					//힘
					if ( lpItem->Strength && sSpecialRevision[cnt].sStrength[0] ) {
						RndPos = GetRandomPos_Normal( sSpecialRevision[cnt].sStrength[0] , sSpecialRevision[cnt].sStrength[1] );
						Revision = (lpItem->Strength*RndPos)/100;
						lpItem->Strength += Revision;
					}
					//정신
					if ( lpItem->Spirit && sSpecialRevision[cnt].sSpirit[0] ) {
						RndPos = GetRandomPos_Normal( sSpecialRevision[cnt].sSpirit[0] , sSpecialRevision[cnt].sSpirit[1] );
						Revision = (lpItem->Spirit*RndPos)/100;
						lpItem->Spirit += Revision;
					}
					//재능
					if ( lpItem->Talent && sSpecialRevision[cnt].sTalent[0] ) {
						RndPos = GetRandomPos_Normal( sSpecialRevision[cnt].sTalent[0] , sSpecialRevision[cnt].sTalent[1] );
						Revision = (lpItem->Talent*RndPos)/100;
						lpItem->Talent += Revision;
					}
					//민첩
					if ( lpItem->Dexterity && sSpecialRevision[cnt].sDexterity[0] ) {
						RndPos = GetRandomPos_Normal( sSpecialRevision[cnt].sDexterity[0] , sSpecialRevision[cnt].sDexterity[1] );
						Revision = (lpItem->Dexterity*RndPos)/100;
						lpItem->Dexterity += Revision;
					}
					//건강
					if ( lpItem->Health && sSpecialRevision[cnt].sHealth[0] ) {
						RndPos = GetRandomPos_Normal( sSpecialRevision[cnt].sHealth[0] , sSpecialRevision[cnt].sHealth[1] );
						Revision = (lpItem->Health*RndPos)/100;
						lpItem->Health += Revision;
					}
				}
			}
/*
			if ( dwSpecialJob==JOB_CODE_ARCHER || dwSpecialJob==JOB_CODE_ATALANTA ) {
				//아쳐 아탈 특화
				if ( (lpItem->CODE&sinITEM_MASK2)==sinDA1 ) {		//갑옷
					lpItem->Dexterity = lpItem->Level + 20;			//민첩추가
				}
			}
*/
			//흡수력
			if ( lpDefItem->fSpecial_Absorb[1]!=0 ) {
				lpItem->JobItem.Add_fAbsorb = GetRandomFloatPos(lpDefItem->fSpecial_Absorb[0],lpDefItem->fSpecial_Absorb[1]);
			}
			else {
				lpItem->JobItem.Add_fAbsorb = lpDefItem->fSpecial_Absorb[0];
			}
		
			//방어력
			if ( lpDefItem->sSpecial_Defence[1] ) {
				lpItem->JobItem.Add_Defence = GetRandomPos_Normal(lpDefItem->sSpecial_Defence[0],lpDefItem->sSpecial_Defence[1]);
			}
			else {
				lpItem->JobItem.Add_Defence = lpDefItem->sSpecial_Defence[0];
			}

			//이동속도
			if ( lpDefItem->fSpecial_fSpeed[1]!=0 ) {
				lpItem->JobItem.Add_fSpeed = GetRandomFloatPos(lpDefItem->fSpecial_fSpeed[0],lpDefItem->fSpecial_fSpeed[1]);
			}
			else {
				lpItem->JobItem.Add_fSpeed = lpDefItem->fSpecial_fSpeed[0];
			}

			//마법숙련도
			if ( lpDefItem->fSpecial_Magic_Mastery[1]!=0 ) {
				lpItem->JobItem.Add_fMagic_Mastery = GetRandomFloatPos(lpDefItem->fSpecial_Magic_Mastery[0],lpDefItem->fSpecial_Magic_Mastery[1]);
			}
			else {
				lpItem->JobItem.Add_fMagic_Mastery = lpDefItem->fSpecial_Magic_Mastery[0];
			}

			//기력 재생
			if ( lpDefItem->fSpecial_Mana_Regen[1]!=0 ) {
				lpItem->JobItem.Per_Mana_Regen = GetRandomFloatPos(lpDefItem->fSpecial_Mana_Regen[0],lpDefItem->fSpecial_Mana_Regen[1]);
			}
			else {
				lpItem->JobItem.Per_Mana_Regen = lpDefItem->fSpecial_Mana_Regen[0];
			}


			//특화 명중력
			if ( lpDefItem->Lev_Attack_Rating[1] ) {
				lpItem->JobItem.Lev_Attack_Rating = GetRandomPos_Normal(lpDefItem->Lev_Attack_Rating[0],lpDefItem->Lev_Attack_Rating[1]);
			}
			else {
				lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[0];
			}


		}
		else {
			//특화 없음
			lpItem->JobCodeMask = 0;
		}
	}

	if ( !lpItem->JobCodeMask ) {
		ZeroMemory( &lpItem->JobItem , sizeof(sITEM_SPECIAL) );
	}


/*
		///////////////// *흡수력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**흡수력" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->fSpecial_Absorb[0] = (float)atof(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->fSpecial_Absorb[1] = (float)atof(strBuff);			
			//lpItem->JobItem.Add_fAbsorb = (float)atof(strBuff);
			NextFlag = TRUE;
		}
		///////////////// *방어력 ///////////////////////
		if ( !NextFlag && lstrcmp( decode , "**방어력" )==0 ) {
			p=GetWord(strBuff,p);
			lpDefItem->sSpecial_Defence[0] = atoi(strBuff);
			p=GetWord(strBuff,p);
			lpDefItem->sSpecial_Defence[1] = atoi(strBuff);
//			lpItem->JobItem.Add_Defence = atoi(strBuff);
			NextFlag = TRUE;
		}
*/

	//아이템 인증 받기
	ReformItem( lpItem );

	return	TRUE;
}

//아이템 생성
int CreateDefItem( sITEMINFO *lpItem , sDEF_ITEMINFO *lpDefItem , int SpJobCode )
{
	return CreateDefItem( lpItem , lpDefItem , SpJobCode , 0 );
}

//후진 아이템 설정
int SetLowerItem( sDEF_ITEMINFO *lpDefItem  )
{
	int ie;
	int cnt;

	sITEMINFO *lpItem;
	lpItem = &lpDefItem->Item;

	//내구력 설정
	if ( lpDefItem->sDurability[0] ) {
		ie = lpDefItem->sDurability[0];
		lpItem->Durability[0] = ie;
		lpItem->Durability[1] = ie;
	}

	//8개의 원소값 설정
	for( cnt=0;cnt<8;cnt++ ) {
		lpItem->Resistance[cnt] = lpDefItem->sResistance[cnt][0];
	}

	//공격력 설정
	if ( lpDefItem->sDamage[1] || lpDefItem->sDamage[3] ) {
		lpItem->Damage[0] = lpDefItem->sDamage[0];
		lpItem->Damage[1] = lpDefItem->sDamage[2];
	}

	lpItem->Attack_Rating = lpDefItem->sAttack_Rating[0];
	lpItem->fAbsorb = lpDefItem->fAbsorb[0];
	lpItem->Defence = lpDefItem->sDefence[0];
	lpItem->fBlock_Rating = lpDefItem->fBlock_Rating[0];
	lpItem->fSpeed = lpDefItem->fSpeed[0];

	lpItem->fMana_Regen = lpDefItem->fMana_Regen[0];		//마나재생
	lpItem->fLife_Regen = lpDefItem->fLife_Regen[0];		//라이프재생
	lpItem->fStamina_Regen = lpDefItem->fStamina_Regen[0];	//스테미나재생

	lpItem->fIncrease_Life = (float)lpDefItem->Increase_Life[0];
	lpItem->fIncrease_Mana = (float)lpDefItem->Increase_Mana[0];
	lpItem->fIncrease_Stamina = (float)lpDefItem->Increase_Stamina[0];

/*
	if ( lpItem->JobCodeMask ) {
		//특화 아이템 설정
		lpItem->JobItem.Add_fAbsorb = lpDefItem->fSpecial_Absorb[0];
		lpItem->JobItem.Add_Defence = lpDefItem->sSpecial_Defence[0];
		lpItem->JobItem.Add_fSpeed = lpDefItem->fSpecial_fSpeed[0];
	}
*/

	DWORD	dwSpecialJob;
	int		RndPos;
	int		Revision;


	if ( lpItem->JobCodeMask ) 
	{
		//특화 아이템 설정

			dwSpecialJob = lpItem->JobCodeMask;

			// 특화 지업별  요구능력치 보정 ( 능력치는 중간으로 고정 )
			for( cnt=0;cnt<sSPECIAL_REVISION_MAX;cnt++ ) {
				if ( sSpecialRevision[cnt].dwJobCode==dwSpecialJob ) {
					//레벨
					if ( lpItem->Level && sSpecialRevision[cnt].sLevel[0] ) {
						RndPos = GetMiddlePos( sSpecialRevision[cnt].sLevel[0] , sSpecialRevision[cnt].sLevel[1] );
						Revision = (lpItem->Level*RndPos)/100;
						lpItem->Level += Revision;
					}
					//힘
					if ( lpItem->Strength && sSpecialRevision[cnt].sStrength[0] ) {
						RndPos = GetMiddlePos( sSpecialRevision[cnt].sStrength[0] , sSpecialRevision[cnt].sStrength[1] );
						Revision = (lpItem->Strength*RndPos)/100;
						lpItem->Strength += Revision;
					}
					//정신
					if ( lpItem->Spirit && sSpecialRevision[cnt].sSpirit[0] ) {
						RndPos = GetMiddlePos( sSpecialRevision[cnt].sSpirit[0] , sSpecialRevision[cnt].sSpirit[1] );
						Revision = (lpItem->Spirit*RndPos)/100;
						lpItem->Spirit += Revision;
					}
					//재능
					if ( lpItem->Talent && sSpecialRevision[cnt].sTalent[0] ) {
						RndPos = GetMiddlePos( sSpecialRevision[cnt].sTalent[0] , sSpecialRevision[cnt].sTalent[1] );
						Revision = (lpItem->Talent*RndPos)/100;
						lpItem->Talent += Revision;
					}
					//민첩
					if ( lpItem->Dexterity && sSpecialRevision[cnt].sDexterity[0] ) {
						RndPos = GetMiddlePos( sSpecialRevision[cnt].sDexterity[0] , sSpecialRevision[cnt].sDexterity[1] );
						Revision = (lpItem->Dexterity*RndPos)/100;
						lpItem->Dexterity += Revision;
					}
					//건강
					if ( lpItem->Health && sSpecialRevision[cnt].sHealth[0] ) {
						RndPos = GetMiddlePos( sSpecialRevision[cnt].sHealth[0] , sSpecialRevision[cnt].sHealth[1] );
						Revision = (lpItem->Health*RndPos)/100;
						lpItem->Health += Revision;
					}
				}
			}

			//흡수력
			lpItem->JobItem.Add_fAbsorb = lpDefItem->fSpecial_Absorb[0];
		
			//방어력
			lpItem->JobItem.Add_Defence = lpDefItem->sSpecial_Defence[0];

			//이동속도
			lpItem->JobItem.Add_fSpeed = lpDefItem->fSpecial_fSpeed[0];

			//마법숙련도
			lpItem->JobItem.Add_fMagic_Mastery = lpDefItem->fSpecial_Magic_Mastery[0];

			//기력 재생
			lpItem->JobItem.Per_Mana_Regen = lpDefItem->fSpecial_Mana_Regen[0];

			//특화 명중력
			if ( lpDefItem->Lev_Attack_Rating[1] ) 
				lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[0]+(lpDefItem->Lev_Attack_Rating[1]-lpDefItem->Lev_Attack_Rating[0])/2;
			else
				lpItem->JobItem.Lev_Attack_Rating = lpDefItem->Lev_Attack_Rating[0];

	}
	else {
		ZeroMemory( &lpItem->JobItem , sizeof(sITEM_SPECIAL) );
	}

	//아이템 인증 받기
	ReformItem( lpItem );

	return	TRUE;
}

//직업 정보 구하기 ( 기본 직업 [0~3] , 전업 횟수 [0~3] )
JOB_DATA_CODE *GetJobDataCode(DWORD BaseJob	, int JobCnt )
{
	int	JobCount = 0;
	int	JobCount2 = JobCnt & 3;
	int	bJob = BaseJob & 0xFFFF;

	if ( !JobCnt ) 
	{
		JobCount2 = BaseJob>>24;
	}

	int cnt = 0;
	while(1) 
	{
		if ( !JobDataBase[cnt].szName[0] )
			break;
		if ( bJob==JobDataBase[cnt].JobCode ) 
		{
			if ( JobCount2==JobCount ) 
				return &JobDataBase[cnt];
			JobCount++;
		}
		cnt++;
	}

	Utils_Log(LOG_DEBUG, "error.....");
	return NULL;
}


#ifdef	_LANGUAGE_KOREAN
//한국어
#include "Language\\Korean\\k_JobCode.h"
#endif

#ifdef	_LANGUAGE_CHINESE
//중국어
#include "Language\\Chinese\\C_JobCode.h"
#endif

#ifdef	_LANGUAGE_JAPANESE
//일본어
#include "Language\\Japanese\\J_JobCode.h"
#endif

#ifdef	_LANGUAGE_TAIWAN
//자유중국
#include "Language\\Taiwan\\T_JobCode.h"
#endif

#ifdef	_LANGUAGE_ENGLISH
//영국어
#include "Language\\English\\E_JobCode.h"
#endif

#ifdef	_LANGUAGE_THAI
//태국어
#include "Language\\THAI\\TH_JobCode.h"
#endif

#ifdef _LANGUAGE_VEITNAM
#include "Language\\VEITNAM\\V_JobCode.h"
#endif

#ifdef _LANGUAGE_BRAZIL
#include "Language\\BRAZIL\\B_JobCode.h"
#endif

#ifdef _LANGUAGE_ARGENTINA
#include "Language\\ARGENTINA\\A_JobCode.h"
#endif


SKILL_DATA_CODE	SkillDataCode[] = {
	{	"xxxxxxxxxxxxx"			,	0								},		//NULL Code
	//1단계 메카니션
	{	"ExtremeShield"			,	SKILL_PLAY_EXTREME_SHIELD		},
	{	"MechanicBomb"			,	SKILL_PLAY_MECHANIC_BOMB		},
	{	"PhysicalAbsorption"	,	SKILL_PLAY_PHYSICAL_ABSORB		},
	{	"PoisonAttribute"		,	0								},
	//2단계 메카닉마스터
	{	"roundimpact"			,	SKILL_PLAY_GREAT_SMASH			},
	{	"Maximize"				,	SKILL_PLAY_MAXIMIZE				},
	{	"Automation"			,	SKILL_PLAY_AUTOMATION			},
	{	"Spark"					,	SKILL_PLAY_SPARK				},
	//3단계 메탈리더
	{	"MetalArmor"			,	SKILL_PLAY_METAL_ARMOR			},
	{	"GrandSmash"			,	SKILL_PLAY_GRAND_SMASH			},	//10
	{	"SparkShield"			,	SKILL_PLAY_SPARK_SHIELD			},
	//4단계 메탈리온
	{	"IMPULSION"				,	SKILL_PLAY_IMPULSION			},
	{	"COMPULSION"			,	SKILL_PLAY_COMPULSION			},
	{	"MAGNETICSPHERE"		,	SKILL_PLAY_MAGNETIC_SPHERE		},
	{	"METALGOLEM"			,	SKILL_PLAY_METAL_GOLEM			},


	//1단계 파이터
	{	"MeleeMastery"			,	0								},
	{	"FireAttribute"			,	0								},
	{	"Raving"				,	SKILL_PLAY_RAVING				},
	{	"Impact"				,	SKILL_PLAY_IMPACT				},
	//2단계 워리어
	{	"TripleImpact"			,	SKILL_PLAY_TRIPLE_IMPACT		},	//20
	{	"BrutalSwing"			,	SKILL_PLAY_BRUTAL_SWING			},
	{	"Roar"					,	SKILL_PLAY_ROAR					},
	{	"RageofZecram"			,	SKILL_PLAY_RAGEOF_ZECRAM		},
	//3단계 챔피언
	{	"Concentration"			,	SKILL_PLAY_CONCENTRATION		},
	{	"AvangingCrash"			,	SKILL_PLAY_AVANGING_CRASH		},
	{	"SwiftAxe"				,	SKILL_PLAY_SWIFT_AXE			},
	{	"BoneSmash"				,	SKILL_PLAY_BONE_SMASH			},
	//4단계 이모탈워리어
	{	"DESTROYER"				,	SKILL_PLAY_DESTROYER			},
	{	"BERSERKER"				,	SKILL_PLAY_BERSERKER			},
	{	"CYCLONESTRIKE"			,	SKILL_PLAY_CYCLONE_STRIKE		},	//30


	//1단계 파이크맨
	{	"PikeWind"				,	SKILL_PLAY_PIKEWIND				},
	{	"IceAttribute"			,	0								},
	{	"CriticalHit"			,	SKILL_PLAY_CRITICAL_HIT			},
	{	"JumpingCrash"			,	SKILL_PLAY_JUMPING_CRASH		},
	//2단계 컴배턴트
	{	"GroundPike"			,	SKILL_PLAY_GROUND_PIKE			},
	{	"Tornado"				,	SKILL_PLAY_TORNADO				},
	{	"WeaponDefenceMastery"	,	0								},
	{	"Expansion"				,	SKILL_PLAY_EXPANSION			},
	//3단계 랜서
	{	"VenomSpear"			,	SKILL_PLAY_VENOM_SPEAR			},
	//{	"Vanish"				,	SKILL_PLAY_VANISH				},	//BladeOfBlaze 가 변경됬음
	{	"BladeOfBlaze"			,	SKILL_PLAY_BLADE_OF_BLAZE		},	//사용 금지 예정	//40
	{	"ChainLance"			,	SKILL_PLAY_CHAIN_LANCE			},
	//4단계 랜슬롯
	{	"ASSASSINEYE"			,	SKILL_PLAY_ASSASSIN_EYE			},
	{	"CHARGINGSTRIKE"		,	SKILL_PLAY_CHARGING_STRIKE		},
	{	"VAGUE"					,	SKILL_PLAY_VAGUE				},
	{	"SHADOWMASTER"			,	SKILL_PLAY_SHADOW_MASTER		},



	//1단계 아쳐
	{	"ScoutHawk"				,	SKILL_PLAY_SCOUT_HAWK			},
	{	"ShootingMastery"		,	0								},
	{	"WindArrow"				,	SKILL_PLAY_WIND_ARROW			},
	{	"PerfectAim"			,	SKILL_PLAY_PERFECT_AIM			},
	//2단계 헌트리스마스터
	{	"DionsEye"				,	0								},
	{	"Falcon"				,	SKILL_PLAY_FALCON				},
	{	"ArrowofRage"			,	SKILL_PLAY_ARROWOF_RAGE			},
	{	"Avalanche"				,	SKILL_PLAY_AVALANCHE			},
	//3단계 디온의수제자
	{	"ElementalShot"			,	SKILL_PLAY_ELEMENTAL_SHOT		},
	{	"GoldenFalcon"			,	SKILL_PLAY_GOLDEN_FALCON		},
	{	"BombShot"				,	SKILL_PLAY_BOMB_SHOT			},
	{	"Perforation"			,	SKILL_PLAY_PERFORATION			},
	//4단계 새지테리온
	{	"RECALLWOLVERIN"		,	SKILL_PLAY_RECALL_WOLVERIN		},
	{	"PHOENIXSHOT"			,	SKILL_PLAY_PHOENIX_SHOT			},
	{	"FORCEOFNATURE"			,	SKILL_PLAY_FORCE_OF_NATURE		},


	/////////////////////////// 모라이온 //////////////////////////////

	//1단계 나이트
	{	"SwordBlast"			,	SKILL_PLAY_SWORD_BLAST			},
	{	"HolyBody"				,	SKILL_PLAY_HOLY_BODY			},
	{	"PhysicalTraning"		,	0								},
	{	"DoubleCrash"			,	SKILL_PLAY_DOUBLE_CRASH			},
	//2단계	팔라딘
	{	"holyteam"				,	SKILL_PLAY_HOLY_VALOR			},
	{	"Brandish"				,	SKILL_PLAY_BRANDISH				},
	{	"Piercing"				,	SKILL_PLAY_PIERCING				},
	{	"DrasticSpirit"			,	SKILL_PLAY_DRASTIC_SPIRIT		},
	//3단계	홀리나이트
	{	"FlameBrandish"			,	SKILL_PLAY_FLAME_BRANDISH		},
	{	"Divineinhalation"		,	SKILL_PLAY_DIVINE_INHALATION	},
	{	"HolyIncantation"		,	SKILL_PLAY_HOLY_INCANTATION		},
	{	"GrandCross"			,	SKILL_PLAY_GRAND_CROSS			},
	//4단계	세인트나이트
	{	"DIVINEPIERCING"		,	SKILL_PLAY_DIVINE_PIERCING		},
	{	"DIVINEPIERCING2"		,	SKILL_PLAY_DIVINE_PIERCING2		},
	{	"DIVINEPIERCING3"		,	SKILL_PLAY_DIVINE_PIERCING3		},
	{	"GODLYSHIELD"			,	SKILL_PLAY_GODLY_SHIELD			},
	{	"GODSBLESS"				,	SKILL_PLAY_GODS_BLESS			},
	{	"SWORDOFJUSTICE"		,	SKILL_PLAY_SWORD_OF_JUSTICE		},


	//1단계 아탈란타
	{	"ShieldStrike"			,	SKILL_PLAY_SHIELD_STRIKE		},
	{	"Farina"				,	SKILL_PLAY_FARINA				},
	{	"ThrowingMastery"		,	0								},
	{	"VigorSpear"			,	SKILL_PLAY_VIGOR_SPEAR			},
	//2단계 발키리
	{	"Windy"					,	SKILL_PLAY_WINDY				},
	{	"TwistJavelin"			,	SKILL_PLAY_TWIST_JAVELIN		},
	{	"SoulSucker"			,	SKILL_PLAY_SOUL_SUCKER			},
	{	"FireJavelin"			,	SKILL_PLAY_FIRE_JAVELIN			},
	//3단계 Brunhild
	{	"SplitJavelin"			,	SKILL_PLAY_SPLIT_JAVELIN		},
	{	"TriumphOfValhalla"		,	SKILL_PLAY_TRIUMPH_OF_VALHALLA	},
	{	"LightningJavelin"		,	SKILL_PLAY_LIGHTNING_JAVELIN	},
	{	"StormJavelin"			,	SKILL_PLAY_STORM_JAVELIN		},
	//4단계 발할라
	{	"HALLOFVALHALLA"		,	SKILL_PLAY_HALL_OF_VALHALLA		},
	{	"XRAGE"					,	SKILL_PLAY_X_RAGE				},
	{	"FROSTJAVELIN"			,	SKILL_PLAY_FROST_JAVELIN		},
	{	"VENGEANCE"				,	SKILL_PLAY_VENGEANCE			},


	//1단계 프리스티스
	{	"Healing"				,	SKILL_PLAY_HEALING				},
	{	"HolyBolt"				,	SKILL_PLAY_HOLY_BOLT			},
	{	"MultiSpark"			,	SKILL_PLAY_MULTI_SPARK			},
	{	"HolyMind"				,	SKILL_PLAY_HOLY_MIND			},
	//2단계 세인티스
	{	"Meditation"			,	0								},
	{	"DivineLightning"		,	SKILL_PLAY_DIVINE_LIGHTNING		},
	{	"HolyReflection"		,	SKILL_PLAY_HOLY_REFLECTION		},
	{	"GrandHealing"			,	SKILL_PLAY_GREAT_HEALING		},
	//3단계 비숍
	{	"VigorBall"				,	SKILL_PLAY_VIGOR_BALL			},
	{	"Resurrection"			,	SKILL_PLAY_RESURRECTION			},
	{	"Extinction"			,	SKILL_PLAY_EXTINCTION			},
	{	"VirtualLife"			,	SKILL_PLAY_VIRTUAL_LIFE			},
	//4단계 CELESTIAL
	{	"GLACIALSPIKE"			,	SKILL_PLAY_GLACIAL_SPIKE		},
	{	"REGENERATIONFIELD"		,	SKILL_PLAY_REGENERATION_FIELD	},
	{	"CHAINLIGHTNING"		,	SKILL_PLAY_CHAIN_LIGHTNING		},
	{	"SUMMONMUSPELL"			,	SKILL_PLAY_SUMMON_MUSPELL		},


	//1단계 매지션
	{	"Agony"					,	SKILL_PLAY_AGONY				},
	{	"FireBolt"				,	SKILL_PLAY_FIRE_BOLT			},
	{	"Zenith"				,	SKILL_PLAY_ZENITH				},
	{	"FireBall"				,	SKILL_PLAY_FIRE_BALL			},
	//2단계 위자드
	{	"MentalMastery"			,	0								},
	{	"ColumnOfWater"			,	SKILL_PLAY_COLUMN_OF_WATER		},
	{	"EnchantWeapon"			,	SKILL_PLAY_ENCHANT_WEAPON		},
	{	"DeadRay"				,	SKILL_PLAY_DEAD_RAY				},
	//3단계 로얄위저드
	{	"EnergyShield"			,	SKILL_PLAY_ENERGY_SHIELD		},
	{	"Diastrophism"			,	SKILL_PLAY_DIASTROPHISM			},
	{	"SpiritElemental"		,	SKILL_PLAY_SPIRIT_ELEMENTAL		},
	{	"DancingSword"			,	SKILL_PLAY_DANCING_SWORD		},
	//4단계 아크메이지
	{	"FIREELEMENTAL"			,	SKILL_PLAY_FIRE_ELEMENTAL		},
	{	"FLAMEWAVE"				,	SKILL_PLAY_FLAME_WAVE			},
	{	"DISTORTION"			,	SKILL_PLAY_DISTORTION			},
	{	"METEO"					,	SKILL_PLAY_METEO				},

	{	"",0 }
};



//######################################################################################
//작 성 자 : 오 영 석

// 꼬아서리.!!! 
void ModelKeyWordEncode( DWORD dwFileCode, smMODELINFO *lpMODELINFO )
{
	char *szFile;
	int   dwCode_1, dwCode_2, dwCode_3, dwCode_4;

	if( lpMODELINFO->szLinkFile[0] )
	{
		szFile = ChangeFileExt( lpMODELINFO->szLinkFile, szFileExt );
		DWORD dwLinkCode = GetSpeedSum( szFile );

		dwCode_1 = ( (dwFileCode & 0x00ff0000) << 8 );
		dwCode_2 = ( (dwLinkCode & 0x000000ff) << 16 );
		dwCode_3 = ( (dwFileCode & 0x000000ff) << 8 );
		dwCode_4 = ( (dwLinkCode & 0xff000000) >> 24 );
		lpMODELINFO->FileTypeKeyWord = ( dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4 ); 

		dwCode_1 = ( (dwFileCode & 0xff000000) );
		dwCode_2 = ( (dwLinkCode & 0x0000ff00) << 8 );
		dwCode_3 = ( (dwFileCode & 0x0000ff00) );
		dwCode_4 = ( (dwLinkCode & 0x00ff0000) >> 16 );
		lpMODELINFO->LinkFileKeyWord = ( dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4 ); 
	}
	else
	{
		dwCode_1 = ( (dwFileCode & 0x0000ff00) << 16 );
		dwCode_2 = ( (dwFileCode & 0xff000000) >> 8 );
		dwCode_3 = ( (dwFileCode & 0x000000ff) << 8 );
		dwCode_4 = ( (dwFileCode & 0x00ff0000) >> 16 );
		lpMODELINFO->FileTypeKeyWord = ( dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4 ); 
	}
}

// 풀어서.!!! 
int ModelKeyWordDecode( DWORD dwFileCode, smMODELINFO *lpMODELINFO )
{
	char *szFile;
	int   dwCode_1, dwCode_2, dwCode_3, dwCode_4;

	if( lpMODELINFO->szLinkFile[0] )
	{
		szFile = ChangeFileExt( lpMODELINFO->szLinkFile, szFileExt );
		DWORD dwLinkCode = GetSpeedSum( szFile );

		dwCode_1 = ( (lpMODELINFO->LinkFileKeyWord & 0xff000000) );
		dwCode_2 = ( (lpMODELINFO->FileTypeKeyWord & 0xff000000) >> 8 );
		dwCode_3 = ( (lpMODELINFO->LinkFileKeyWord & 0x0000ff00) );
		dwCode_4 = ( (lpMODELINFO->FileTypeKeyWord & 0x0000ff00) >> 8 );
		if( dwFileCode != (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4) )
			return FALSE;

		dwCode_1 = ( (lpMODELINFO->FileTypeKeyWord & 0x000000ff) << 24 );
		dwCode_2 = ( (lpMODELINFO->LinkFileKeyWord & 0x000000ff) << 16 );
		dwCode_3 = ( (lpMODELINFO->LinkFileKeyWord & 0x00ff0000) >> 8  );
		dwCode_4 = ( (lpMODELINFO->FileTypeKeyWord & 0x00ff0000) >> 16 );
		if( dwLinkCode != (dwCode_1 | dwCode_2 | dwCode_3 | dwCode_4) )
			return FALSE;
	}
	else
	{
		dwCode_1 = ( (lpMODELINFO->FileTypeKeyWord & 0xff000000) >> 16 );
		dwCode_2 = ( (lpMODELINFO->FileTypeKeyWord & 0x00ff0000) << 8 );
		dwCode_3 = ( (lpMODELINFO->FileTypeKeyWord & 0x0000ff00) >> 8 );
		dwCode_4 = ( (lpMODELINFO->FileTypeKeyWord & 0x000000ff) << 16 );
		if( dwFileCode != (dwCode_2 | dwCode_4 | dwCode_1 | dwCode_3) )
			return FALSE;
	}

	return TRUE;
}

// 꼬아서리.!!! 
void MotionKeyWordEncode( DWORD dwCode, smMODELINFO *lpMODELINFO )
{
	int cnt, i, stFrm, endFrm;
	smMOTIONINFO *lpMotionInfo;

	//
	cnt = lpMODELINFO->MotionCount;
	for( i=CHRMOTION_EXT; i < cnt; i++ )
	{
		lpMotionInfo = &lpMODELINFO->MotionInfo[i];
		if( lpMotionInfo )
		{
			stFrm  = lpMotionInfo->StartFrame;
			endFrm = lpMotionInfo->EndFrame;
			
			//
			if( stFrm )
			{
				lpMotionInfo->MotionKeyWord_1 = (dwCode & 0xff000000) | ( (stFrm & 0x0000ff00)  << 8 ) |
												( (dwCode & 0x00ff0000) >> 8 ) | (stFrm & 0x000000ff);

				lpMotionInfo->StartFrame	  = ( (dwCode & 0x000000ff) << 24 )  | (stFrm & 0x00ff0000) | 
												(dwCode & 0x0000ff00) | ( (stFrm & 0xff000000) >> 24 );
			}

			//
			if( endFrm )
			{
				lpMotionInfo->MotionKeyWord_2 = ( (dwCode & 0x000000ff) << 24 ) | ( (endFrm & 0xff000000) >> 8 ) | 
												(dwCode & 0x0000ff00) | ( (endFrm & 0x00ff0000) >> 16 );

				lpMotionInfo->EndFrame		  = ( (dwCode & 0x00ff0000) << 8 ) | ( (endFrm & 0x0000ff00) << 8 ) | 
												( (dwCode & 0xff000000) >> 16 ) | (endFrm & 0x000000ff);
			}
		}
	}
}

// 풀어서.!!! 
int MotionKeyWordDecode( DWORD dwCode, smMODELINFO *lpMODELINFO )
{
	int cnt, i, KeyWord, Frame;
	smMOTIONINFO *lpMotionInfo;

	//
	cnt = lpMODELINFO->MotionCount;
	for( i=CHRMOTION_EXT; i < cnt; i++ )
	{
		lpMotionInfo = &lpMODELINFO->MotionInfo[i];
		if( lpMotionInfo )
		{
			//
			if( lpMotionInfo->MotionKeyWord_1 || lpMotionInfo->StartFrame )
			{
				KeyWord = (lpMotionInfo->MotionKeyWord_1 & 0xff000000) | ( (lpMotionInfo->MotionKeyWord_1 & 0x0000ff00) << 8 ) |
						  (lpMotionInfo->StartFrame & 0x0000ff00) | ( (lpMotionInfo->StartFrame & 0xff000000) >> 24 );

				Frame   = ( (lpMotionInfo->StartFrame & 0x000000ff) << 24 ) | (lpMotionInfo->StartFrame & 0x00ff0000) |
						  ( (lpMotionInfo->MotionKeyWord_1 & 0x00ff0000) >> 8 ) | (lpMotionInfo->MotionKeyWord_1 & 0x000000ff);

				if( dwCode != KeyWord )
					return FALSE;

				lpMotionInfo->MotionKeyWord_1 = 0;
				lpMotionInfo->StartFrame      = Frame;
			}

			//
			if( lpMotionInfo->MotionKeyWord_2 || lpMotionInfo->EndFrame )
			{
				KeyWord = ( (lpMotionInfo->EndFrame & 0x0000ff00) << 16 ) | ( (lpMotionInfo->EndFrame & 0xff000000) >> 8 ) |
						  (lpMotionInfo->MotionKeyWord_2 & 0x0000ff00) | ( (lpMotionInfo->MotionKeyWord_2 & 0xff000000) >> 24 );

				Frame   = ( (lpMotionInfo->MotionKeyWord_2 & 0x00ff0000) << 8 ) | ( (lpMotionInfo->MotionKeyWord_2 & 0x000000ff) << 16 )|
						  ( (lpMotionInfo->EndFrame & 0x00ff0000) >> 8 ) | (lpMotionInfo->EndFrame & 0x000000ff);

				if( dwCode != KeyWord )
					return FALSE;

				lpMotionInfo->MotionKeyWord_2 = 0;
				lpMotionInfo->EndFrame        = Frame;
			}
		}
	}

	return TRUE;
}

//######################################################################################
//SOD벨라트라 몬스터 설정 불러오기
int	Open_SODConfig( char *szFileName , void *lphCoreMonster , int *SodTax , char *szSodText , int *SodScoreDiv )
{

	FILE	*fp;
	char strBuff[256];
	char *p;
	char *pb;
	int NextFlag;
	int cnt;
	int hcRoundCount = 0;

	int	m_SodTax = 0;
	int m_SodScoreDiv = 0;
	char m_szSodText[256];
	sHCORE_MONSTER	hcMonster[hCORE_ROUND_MAX];
	sHCORE_MONSTER	*lpSod_Monster = (sHCORE_MONSTER *)lphCoreMonster;

	m_szSodText[0] = 0;
	memcpy( hcMonster , lpSod_Monster , sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX );

	for(cnt=0;cnt<rsHARDCORE_COUNT_END;cnt++) {

		hcMonster[cnt].hCoreMonster1.szName[0] = 0;
		hcMonster[cnt].hCoreMonster1.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster1.perCount = 0;

		hcMonster[cnt].hCoreMonster2.szName[0] = 0;
		hcMonster[cnt].hCoreMonster2.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster2.perCount = 0;

		hcMonster[cnt].hCoreMonster3.szName[0] = 0;
		hcMonster[cnt].hCoreMonster3.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster3.perCount = 0;

		hcMonster[cnt].hCoreMonster4.szName[0] = 0;
		hcMonster[cnt].hCoreMonster4.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonster4.perCount = 0;

		hcMonster[cnt].hCoreMonsterBoss.szName[0] = 0;
		hcMonster[cnt].hCoreMonsterBoss.lpCharInfo = 0;
		hcMonster[cnt].hCoreMonsterBoss.perCount = 0;

		hcMonster[cnt].MaxMonster = 0;
	}


	fp = fopen( szFileName , "rb" );
	if ( fp==NULL ) return FALSE;


	while( !feof( fp ) )//  feof: file end까지 읽어라 
	{
		if( fgets( line, 255, fp ) == NULL)	break;

		p = GetWord( decode , line);

		NextFlag = 0;

		///////////////// 세율 ///////////////////////
		if ( lstrcmpi( decode , "*BELATRA_TAX" )==0 ) {

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			if ( strBuff[0] ) m_SodTax = atoi( strBuff );

			NextFlag = TRUE;
		}


		///////////////// 설명 ///////////////////////
		if ( !NextFlag && lstrcmpi( decode , "*BELATRA_TEXT" )==0 ) {

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			lstrcpy( m_szSodText , strBuff );

			NextFlag = TRUE;
		}

		///////////////// 설명 ///////////////////////
		if ( !NextFlag && lstrcmpi( decode , "*BELATRA_DIVSCORE" )==0 ) {

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			if ( strBuff[0] ) m_SodScoreDiv = atoi( strBuff );

			NextFlag = TRUE;
		}


		///////////////// 몬스터 ///////////////////////
		if ( !NextFlag && lstrcmpi( decode , "*BELATRA_MONSTER" )==0 ) {
			if ( hcRoundCount<rsHARDCORE_COUNT_END ) {
				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);		//1st 몬스터
				lstrcpy( hcMonster[hcRoundCount].hCoreMonster1.szName , strBuff );
				p=GetWord(strBuff,p);
				hcMonster[hcRoundCount].hCoreMonster1.perCount = atoi(strBuff);

				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);		//2nd 몬스터
				lstrcpy( hcMonster[hcRoundCount].hCoreMonster2.szName , strBuff );
				p=GetWord(strBuff,p);
				hcMonster[hcRoundCount].hCoreMonster2.perCount = atoi(strBuff);

				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);		//3rd 몬스터
				lstrcpy( hcMonster[hcRoundCount].hCoreMonster3.szName , strBuff );
				p=GetWord(strBuff,p);
				hcMonster[hcRoundCount].hCoreMonster3.perCount = atoi(strBuff);

				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);		//4th 몬스터
				lstrcpy( hcMonster[hcRoundCount].hCoreMonster4.szName , strBuff );
				p=GetWord(strBuff,p);
				hcMonster[hcRoundCount].hCoreMonster4.perCount = atoi(strBuff);

				pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);		//보스 몬스터
				lstrcpy( hcMonster[hcRoundCount].hCoreMonsterBoss.szName , strBuff );
				hcMonster[hcRoundCount].hCoreMonsterBoss.perCount = 0;

				p=GetWord(strBuff,p);														//출현제한수
				hcMonster[hcRoundCount].MaxMonster = atoi(strBuff);

				hcRoundCount ++;
			}
			NextFlag = TRUE;
		}
	}
	fclose(fp);

	if ( hcRoundCount<rsHARDCORE_COUNT_END ) return 0;

	if ( m_SodTax>=0 && m_SodTax<100 ) 	*SodTax = m_SodTax;
	if ( m_szSodText[0] ) lstrcpy( szSodText , m_szSodText );
	if ( m_SodScoreDiv>0 ) 	*SodScoreDiv = m_SodScoreDiv;

	memcpy( lpSod_Monster , hcMonster , sizeof(sHCORE_MONSTER)*hCORE_ROUND_MAX );

	return 1;		//나중에 갯수 추가된다면 숫자가 그룹만큼 리턴
}




//크랙정보파일을 읽어 온다
int ReadCustomCracker( char *szCrackFile , TRANS_FIND_CRACKER *lpTransFindCrack  )
{
	FILE	*fp;
	char strBuff[64];
	char *p,*pb;
	int cnt;

	//fp = fopen( "FindCrack.ini" , "rb" );
	fp = fopen( szCrackFile , "rb" );
	if ( fp==NULL ) {
		return FALSE;					//레지스트리 설정 적용
	}

	cnt = 0;

	while( !feof( fp ) )//  feof: file end까지 읽어라 
	{

		if( fgets( line, 255, fp ) == NULL)	break;

		p = GetWord( decode , line);


		if ( lstrcmpi( decode , "*CRACK" )==0 ) {


			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			lstrcpy( lpTransFindCrack->CrackName[cnt].szName1 , strBuff );

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			lstrcpy( lpTransFindCrack->CrackName[cnt].szName2 , strBuff );

			pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);
			lstrcpy( lpTransFindCrack->CrackName[cnt].szClass , strBuff );

			cnt++;
		}
		if ( cnt>=FIND_CRACK_LIST_MAX ) break;

	}

	lpTransFindCrack->code = smTRANSCODE_FINDCRACK;
	lpTransFindCrack->size = sizeof(_CRACK_NAME)*cnt+16;
	lpTransFindCrack->FindCounter = cnt;

	fclose(fp);

	return cnt;
}


