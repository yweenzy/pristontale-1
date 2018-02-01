#ifndef	_FILEREAD_HEADER

#define	_FILEREAD_HEADER

//화면 및 캐릭터 및 파일등 기본 설정
extern smCONFIG	smConfig;

//정보 파일을 해독하여 돌려준다 (Info에저장)
smCONFIG *smConfigDecode( char *iniFile );

//크랙정보파일을 읽어 온다
int ReadCustomCracker( char *szCrackFile , TRANS_FIND_CRACKER *lpTransFindCrack  );


//모델 정보 파일을 해독하여 돌려준다 (Info에저장)
int smModelDecode( char *iniFile , smMODELINFO *Info );

//캐릭터 정보 파일에서 해독하여 설정한다
int smCharDecode( char *szCharFile , smCHAR_INFO *lpCharInfo , smCHAR_MONSTER_INFO	*lpMonInfo , char *lpDialogMessage=0 );

extern char	szShotCutMessage[10][100];
int	ReadShotcutMessage( char *szFileName );		//단축 메세지 읽어 오기


//몬스터 출현 구조체
struct rsSTG_MONSTER {
	char	szMonsterName[32];			//몬스터 이름
	int		OpenPercentage;				//출현빈도

	smCHAR_INFO	*lpCharInfo;			//몬스터 정보 포인터
	int		NumOpenStart;				//출현빈도 시작 값
};

#define rsSTG_MONSTER_MAX	50
#define rsBOSS_MONSTER_MAX	16

struct sBOSS_MONSTER {
	smCHAR_INFO		*MasterMonster;			//보스급 몬스터
	smCHAR_INFO		*SlaveMonster;			//수행 몬스터
	int				SlaveCount;				//수행 몬스터 숫자
	BYTE			bOpenTime[32];			//나타나는 시간
	int				OpenTimeCount;			//시간 수
};

struct	rsSTG_MONSTER_LIST {

	rsSTG_MONSTER	rsMonster[rsSTG_MONSTER_MAX];

	int		PecetageCount;
	int		Counter;
	int		LimitMax;						//출현 제한수 / 최대치
	int		OpenInterval;					//출현 주기
	int		OpenLimit;						//직역당 최대 출현수
	DWORD	dwIntervalTime;					//출현 간격 제한시간

	sBOSS_MONSTER	sBossMonsters[rsBOSS_MONSTER_MAX];		//두목급 몬스터 세트
	int	BossMonsterCount;									//두목급 몬스터 설정 갯수

};


#define SPECIAL_JOB_RANDOM_MAX			12

//기본 아이템 구조
struct	sDEF_ITEMINFO	{

	sITEMINFO Item;

	short	sDurability[2];			//내구력
	short	sResistance[8][2];		//원소 저항력
	short	sDamage[4];				//공격력
	short	sAttack_Rating[2];		//명중력
	short	sDefence[2];			//방어력
	float	fBlock_Rating[2];		//블럭율
	float	fAbsorb[2];				//흡수력
	float	fSpeed[2];				//이동속도
	int		Increase_Life[2];		//라이프 증가
	int		Increase_Mana[2];		//마나 증가
	int		Increase_Stamina[2];	//스테미나 증가

	float	fMana_Regen[2];			//마나재생
	float	fLife_Regen[2];			//라이프재생
	float	fStamina_Regen[2];		//스테미나재생


	/////////////////// 특화 적용 /////////////////////
	short	sSpecial_Defence[2];			//방어력
	float	fSpecial_Absorb[2];				//흡수력
	float	fSpecial_fSpeed[2];				//이동속도

	float	fSpecial_Magic_Mastery[2];		//마법숙련도
	float	fSpecial_Mana_Regen[2];			//기력 재생

	int     Lev_Attack_Rating[2];			//명중력 

	DWORD	dwJobBitCode_Random[SPECIAL_JOB_RANDOM_MAX];			//랜덤특화 직업 목록 
	int		JobBitCodeRandomCount;

	//////////////////// 발생량 /////////////////////////

	short	sGenDay[2];										//하루에 발생할수 있는양/하루동안 발생된수

	BYTE	*DefCompressData[ sizeof(sITEMINFO) ];	//Item 데이타의 압축 정보
	int		DefCompressDataLen;						//압축데이타의 길이
};


struct JOBNAME_BIT {
	char *szName;
	DWORD dwBitMask;
};

extern JOBNAME_BIT BitMaskJobNames[];


//몬스터 출현 정보 파일에서 해독하여 설정한다
int DecodeOpenMonster( char *szCharFile , rsSTG_MONSTER_LIST *lpStgMonList , smCHAR_INFO *lpCharInfoList, int ListCnt );
//아이템 정보 파일을 해독하여 돌려준다 
int DecodeItemInfo( char *szItemFile , sDEF_ITEMINFO *lpDefItem  );
//아이템 생성
int CreateDefItem( sITEMINFO *lpItem , sDEF_ITEMINFO *lpDefItem , int SpJobCode=0 );
//아이템 생성
int CreateDefItem( sITEMINFO *lpItem , sDEF_ITEMINFO *lpDefItem , int SpJobCode , int ItemNormam );

//후진 아이템 설정
int SetLowerItem( sDEF_ITEMINFO *lpDefItem  );

//최소 최대치에서 랜덤값 산출
float GetRandomFloatPos( float Min , float Max );
int GetRandomPos( int Min , int Max );

//SOD벨라트라 몬스터 설정 불러오기
int	Open_SODConfig( char *szFileName , void *lphCoreMonster , int *SodTax , char *szSodText , int *SodScoreDiv );

//Mechanican
#define		JOB_CODE_MECHANICIAN		0x00000001		//T1
#define		JOB_CODE_MECHANICMASTER		0x00000010		//T2
#define		JOB_CODE_METALLEADER		0x00000100		//T3
#define		JOB_CODE_HEAVYMETAL			0x00001000		//T4

//Fighter
#define		JOB_CODE_FIGHTER			0x00000002		//T1
#define		JOB_CODE_WARRIOR			0x00000020		//T2
#define		JOB_CODE_CHAMPION			0x00000200		//T3
#define		JOB_CODE_IMMORTALWARRIOR	0x00002000		//T4

//Pikeman
#define		JOB_CODE_PIKEMAN			0x00000004		//T1
#define		JOB_CODE_COMBATANT			0x00000040		//T2
#define		JOB_CODE_LANCER				0x00000400		//T3
#define		JOB_CODE_LANCELOT			0x00004000		//T4

//Archer
#define		JOB_CODE_ARCHER				0x00000008		//T1
#define		JOB_CODE_HUNTERMASTER		0x00000080		//T2
#define		JOB_CODE_DIONS_DISCIPLE		0x00000800		//T3
#define		JOB_CODE_SAGITTARION		0x00008000		//T4

//Knight
#define		JOB_CODE_KNIGHT				0x00010000		//T1
#define		JOB_CODE_PALADIN			0x00100000		//T2
#define		JOB_CODE_HOLYKNIGHT			0x01000000		//T3
#define		JOB_CODE_SAINTKNIGHT		0x10000000		//T4

//Atalanta
#define		JOB_CODE_ATALANTA			0x00020000		//T1
#define		JOB_CODE_VALKYRIE			0x00200000		//T2
#define		JOB_CODE_BRUNHILD			0x02000000		//T3
#define		JOB_CODE_VALHALLA			0x20000000		//T4

//Priest
#define		JOB_CODE_PRIEST				0x00040000		//T1
#define		JOB_CODE_SAINTESS			0x00400000		//T2
#define		JOB_CODE_BISHOP				0x04000000		//T3
#define		JOB_CODE_CELESTIAL			0x40000000		//T4

//Magican
#define		JOB_CODE_MAGICIAN			0x00080000		//T1
#define		JOB_CODE_WIZARD				0x00800000		//T2
#define		JOB_CODE_ROYALKNIGHT		0x08000000		//T3
#define		JOB_CODE_ARCHMAGE			0x80000000		//T4

//Fighter
#define		JOB_CODE_WARLORD			0x00008000		//T5

//Mechanican
#define		JOB_CODE_METALRAGE			0x00008000		//T5

//Pikeman
#define		JOB_CODE_BAYLOLUNT			0x00008000		//T5

//Archer
#define		JOB_CODE_ISKAR				0x00008000		//T5

//Knight
#define		JOB_CODE_VALIANT			0x00008000		//T5

//Atalanta
#define		JOB_CODE_QUEENOFVALHALA		0x00008000		//T5

//Priestess
#define		JOB_CODE_ARCANGLE			0x00008000		//T5

//Magican
#define		JOB_CODE_ELEMENTALMASTER	0x00008000		//T5



#define		BROOD_CODE_TEMPSKRON			1
#define		BROOD_CODE_MORAYION				2
#define		BROOD_CODE_SOPPHETIO			4


struct	JOB_DATA_CODE {
	char	*szName;			//이름 영문
	char	*szName2;			//이름 한글
	DWORD	JobBitCode;			//직업 비트 코드
	DWORD	JobCode;			//직업 일반 코드
	DWORD	Brood;				//해당 종족

	int     Sight;				//시야  ****전업시 시야 +5 고정 ****
	int     LifeFunction;		//생명력 함수 
	int     ManaFunction;		//기력 함수 
	int     StaminaFunction;	//근력 함수 
	short   DamageFunction[3];  //0 근접 1 원거리 2마법  
};


struct	SKILL_DATA_CODE {
	char	*szSkillName;				//스킬 이름
	int		dwPlaySkillCode;			//스킬 코드
};

extern	JOB_DATA_CODE	JobDataBase[];
extern	SKILL_DATA_CODE	SkillDataCode[];

//직업 정보 구하기 ( 기본 직업 [0~3] , 전업 횟수 [0~3] )
JOB_DATA_CODE	*GetJobDataCode(	DWORD BaseJob	, int	JobCnt );

extern int NotItemSpecial; // 석지용 - 믹스쳐 리셋

#endif
