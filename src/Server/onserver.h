//PK°¡´ÉÇÑ ·¹º§ 
#define	LIMIT_PK_LEVEL	20				// pluto PKÇã¿ë ÇÊµå ÀüºÎ

#define AUTOPLAYER_MAX		2048
#define AUTOPLAYER_MASK		2047


//À¯·á ¾ÆÀÌÅÛ ±âº» »ç¿ë½Ã°£ ¼³Á¤
#define	PRIME_ITEM_TIME_THIRDEYES		(60*60*24)
#define	PRIME_ITEM_TIME_EXPUP			(60*60*24)

#define	PRIME_ITEM_TIME_THIRDEYESx7		(60*60*24*7)
#define	PRIME_ITEM_TIME_EXPUPx7			(60*60*24*7)

#define	PRIME_ITEM_TIME_VAMPCUSPID		(60*60*3)	// pluto ¹ìÇÇ¸¯ Ä¿½ºÇÍ 3½Ã°£
#define	PRIME_ITEM_TIME_MANARECHARG		(60*60*3)	// pluto ¸¶³ª ¸®Â÷Â¡ Æ÷¼Ç 3½Ã°£

#define	PRIME_ITEM_TIME_VAMPCUSPIDx2	(60*60*24)	// pluto ¹ìÇÇ¸¯ Ä¿½ºÇÍ 1ÀÏ
#define	PRIME_ITEM_TIME_MANARECHARGx2	(60*60*24)	// pluto ¸¶³ª ¸®Â÷Â¡ Æ÷¼Ç 1ÀÏ

#define	PRIME_ITEM_TIME_PACKAGE1		(60*60*3)
#define	PRIME_ITEM_TIME_PACKAGE2		(60*60*24)
#define	PRIME_ITEM_TIME_PACKAGE3		(60*60*24*7)
#define	PRIME_ITEM_TIME_PACKAGE4		(60*60*24*30)
#define	PRIME_ITEM_TIME_PACKAGE5		(60*60*1) // Àåº° - °æÇèÄ¡Áõ°¡ Æ÷¼Ç(100% 1½Ã°£)


#define	PRIME_ITEM_PACKAGE_NONE			0
#define	PRIME_ITEM_PACKAGE_BRONZE		1
#define	PRIME_ITEM_PACKAGE_SILVER		2
#define	PRIME_ITEM_PACKAGE_GOLD			3
#define	PRIME_ITEM_PACKAGE_ULTRA		4

// pluto ¸¶³ª ¸®µà½º Æ÷¼Ç
#define PRIME_ITEM_MIGHTOFAWELL			5
#define PRIME_ITEM_MANAREDUCE			6


//SOD °ü·Ã
#define	rsSOD_FIELD			30
#define	rsSOD_VILLAGE		9
#define	rsBABEL_FIELD		27
#define	rsKELVEZU_FIELD		36
#define	rsMOKOVA_FIELD		38
//°ø¼º
#define	rsCASTLE_FIELD	33
#define	rsACTION_FIELD	39

//Äù½ºÆ®¿ë ´ëÀü °ÝÅõÀå
#define	QUEST_ARENA_FIELD		32
#define	QUEST_ARENA_NPC_POS_X	(22091*fONE)
#define	QUEST_ARENA_NPC_POS_Z	(9673*fONE)


#define	WHERE_TRADE				300
#define	WHERE_GIFT_EXPRESS		600
#define	WHERE_AGINGITEM			400
#define	WHERE_CRAFTITEM			420
#define	WHERE_FORECORB			440
#define	WHERE_LEARNSKILL		460
#define	WHERE_WARPGATE			470
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


#define STG_START_POINT_MAX			200

struct STG_CHAR_INFO {

	smCHAR_INFO	smCharInfo;					//±âº» Ä³¸¯ÅÍ Á¤º¸ ÀÌ¸§ ¸ðµ¨ ·¹º§ µîµî

	int		PosiState;						//¼Ó¼º Á¾·ù ( Àû/NPC )

	int		StartFixed;						//½ÃÀÛ À§Ä¡ °íÁ¤ÀÌ¸é TRUE ( FALSE¸é ¼ö½Ã·Î º¯°æ)
	POINT	StartPosi;						//½ÃÀÛ À§Ä¡ ( °íÁ¤ÀÏ °æ¿ì )

};

struct STG_START_POINT {
	int state;
	int x,z;
};

#define STG_ITEM_MAX	1024

struct psITEM	{
//	int		ItemCode;
	int		state;
	int		Serial;
//	char	szName[32];

	sITEMINFO	ItemInfo;
};

struct	STG_ITEMS {
	int		state;
	int		x,y,z;
	psITEM	Item;
	DWORD	dwCreateTime;
	DWORD	dwLoseTime;
	DWORD	Level;
	int		BeginMode;
};

// pluto Á¦ÀÛ ·é Á¶ÇÕ
struct Rune_Formula
{
	DWORD Recipe;
	DWORD Rune[3];
};



#define FIX_CHAR_MAX	100

#define	STG_MONSTER_MAX		256




class STG_AREA {
public:
	DWORD	Head;

	smSTAGE3D			*lpStage;
	sFIELD				*lpField;

	char				szStartPointFile[64];
	char				szCharFixedFile[64];
	char				szCharMonsterFile[64];

	STG_START_POINT		StartPoint[STG_START_POINT_MAX];
	int					StartPointNearPlay[STG_START_POINT_MAX];
	int					StartPointMonCount[STG_START_POINT_MAX];	//ÇØ´ç ¸ó½ºÅÍ Ä«¿îÅÍ
	int					StartPointCnt;
	int					StartPointLastOpenCount;					//ÃÖ±Ù ¿­¸° ½ÃÀÛ Æ÷ÀÎÆ® Ä«¿îÅÍ
	DWORD				dwStartPoint_OpenTime[STG_START_POINT_MAX];	//¿­¸° ÃÖ±Ù ½Ã°£ ±â·Ï

	int					StartPointOpenCount;						//ÀüÃ¼ ½ÃÀÛÁ¡ ¼ö
	int					StartPointActiveCount;						//È°¼ºÈ­µÈ ½ÃÀÛÁ¡ ¼ö

	STG_ITEMS			StgItems[STG_ITEM_MAX];					//¸Ê»ó¿¡ Á¸ÀçÇÏ´Â ¾ÆÀÌÅÛ

	STG_CHAR_INFO		*lpStageCharInfo;

	smTRNAS_PLAYERINFO	TransCharFixed[FIX_CHAR_MAX];			//°íÁ¤µÈ Ä³¸¯ÅÍ Á¤º¸ ( NPC¿Ü )

	rsSTG_MONSTER_LIST	rsMonsterList;							//ÃâÇö ¸ó½ºÅÍ Å×ÀÌºí

	int					StgCharInfoCnt;

	int					ItemSettingCount;
	int					MonsterSettingCount;

	int					Counter;

	DWORD				FieldNightDay;							//¹ã ³·ÀÇ º¯È­¸¦ °¨ÁöÇÏ±â À§ÇÑ º¯¼ö

	smCHAR				*lpCharMonster[STG_MONSTER_MAX];		//ÃâÇö ¸ó½ºÅÍ ¿¬°á Å×ÀÌºí
	int					MonsterCount;							//¸ó½ºÅÍ ÃâÇö Ä«¿îÅÍ
	int					MonsterLastPoint;						//¸ó½ºÅÍ Å×ÀÌºí ¸¶Áö¸· Æ÷ÀÎÆ®

	int					EvnMonster;								//¸ó½ºÅÍ ÀÏ½ÃÀûÀ¸·Î ÃÊ°ú ¿ÀÇÂ

	DWORD				Event_dwMonsterTime;					//ÀÌº¥Æ® ¸ó½ºÅÍ ¼³Á¤ ½Ã°£
	smCHAR_INFO			*Event_lpChrMonster;					//ÀÌº¥Æ® ¸ó½ºÅÍ Ä³¸¯ Æ÷ÀÎÅÍ
	int					Event_MonsterPercentage;				//ÀÌº¥Æ® ¸ó½ºÅÍ ¹ß»ý È®·ü

	DWORD				dwActiveMode;							//¼³Á¤ »óÅÂ ( spp , spc µîµî )

	STG_AREA();
//	~STG_AREA();

	int	Close();										//Å¬·¡½º ´Ý±â

	int LoadStage( char *szFile );						//¹è°æ ¸Þ½Ã ·Îµå 

	smCHAR *OpenMonster( STG_CHAR_INFO *lpStgCharInfo , int gGroup=1 );	//¸ó½ºÅÍ ÃâÇö
	int Main();

	int SendStartPos( rsPLAYINFO *lpPlayInfo );

	int LoadStartPoint( char *szFile );
	int SaveStartPoint( char *szFile );
	int FindStartPoint( int x, int z );					//½ÃÀÛ ÁöÁ¡ °Ë»ö
	int AddStartPoint( int x, int z, int state );		//½ÃÀÛ ÁöÁ¡ Ãß°¡
	int DeleteStartPoint( int x, int z );				//½ÃÀÛ ÁöÁ¡ Á¦°Å
	int SetStartPosChar( smCHAR *lpChar );				//»õ·Î¿î ÃâÇö ½ÃÀÛ À§Ä¡¸¦ Ã£¾Æ ¼³Á¤ 
	int SetStartPosNearChar( smCHAR *lpChar , int cx, int cy, int cz );	//Æ¯Á¤ ÁÂÇ¥ ÁÖº¯¿¡ Ä³¸¯ÅÍ À§Ä¡¸¦ ¼³Ä¡ÇÔ 
	int SetPosNearChar( smCHAR *lpChar , int cx, int cy, int cz );	//Æ¯Á¤ ÁÂÇ¥ ÁÖº¯¿¡ Ä³¸¯ÅÍ¸¦ ÀÌµ¿ÇÔ 
	int StartPosRandomize();							//ÃâÇö ½ÃÀÛ À§Ä¡ ·£´ýÈ­ ÇÑ´Ù 

	int SendStartPointFlag();							//½ÃÀÛÁöÁ¡ ±ê¹ßÀ§Ä¡ Àü¼Û

	smTRNAS_PLAYERINFO *FindCharInfoFixed( smTRNAS_PLAYERINFO *lpTransPlayerInfo );		//°íÁ¤ Ä³¸¯ÅÍ Á¤º¸ Ã£±â
	int	AddCharInfoFixed( smTRNAS_PLAYERINFO *lpTransPlayerInfo );		//°íÁ¤ Ä³¸¯ÅÍ Á¤º¸ Ãß°¡
	int	DeleteCharInfoFixed( smTRNAS_PLAYERINFO *lpTransPlayerInfo );	//°íÁ¤ Ä³¸¯ÅÍ Á¤º¸ Á¦°Å
	int OpenNpc( smTRNAS_PLAYERINFO *lpTransPlayerInfo );				//NPC Ä³¸¯ÅÍ ÃâÇö
	int LoadCharInfoFixed( char *szFile );								//°íÁ¤ Ä³¸¯ÅÍ Á¤º¸ ÀÐ¾î¿À±â
	int SaveCharInfoFixed( char *szFile );								//°íÁ¤ Ä³¸¯ÅÍ Á¤º¸ ÀúÀå

	STG_ITEMS *FindItem( int x, int y, int z );							//¾ÆÀÌÅÛÀ» Ã£´Â´Ù
	STG_ITEMS *AddItem( psITEM *lpItem , int x, int y, int z , int BeginMode=0 );	//¾ÆÀÌÅÛÀ» ¼³Ä¡ÇÑ´Ù
	int	DeleteItem( int x, int y, int z );								//ÇØ´ç À§Ä¡ÀÇ ¾ÆÀÌÅÛÀ» Á¦°ÅÇÔ
	int DeleteItem( STG_ITEMS *lpStgItem );								//ÇØ´ç ¾ÆÀÌÅÛÀ» Á¦°ÅÇÔ
	int SendStgItem( rsPLAYINFO *lpPlayInfo );							//¾ÆÀÌÅÛ Á¤º¸ Àü¼Û 
	int SendStgItems();													//¾ÆÀÌÅÛ Á¤º¸¸¦ °¢ À¯Àúµé¿¡°Ô Àü¼Û
	int SendStgItem( rsPLAYINFO *lpPlayInfo , STG_ITEMS *lpStgItem );	//¾ÆÀÌÅÛ Á¤º¸ 1°³¸¸ Àü¼Û 
	int SendStgItemToNearUsers( STG_ITEMS *lpStgItem );					//¾ÆÀÌÅÛ Á¤º¸ 1°³¸¸ Àü¼Û 
	int SendStgItemToPartyUsers( rsPLAYINFO *lpPlayInfo , STG_ITEMS *lpStgItem );	//¾ÆÀÌÅÛ Á¤º¸ 1°³¸¦ ±ÙÃ³ÀÇ ÆÄÆ¼À¯Àúµé ÇÑÅ× º¸³¿ 

	int	FindEmptyMonTable();											//ºó ¸ó½ºÅÍ Å×ÀÌºí ¹øÈ£ Ã£±â
	int	AddMonTable( smCHAR *lpChar );									//¸ó½ºÅÍ Å×ÀÌºí¿¡ Æ÷ÀÎÅÍ Ãß°¡
	int	DeleteMonTable( smCHAR *lpChar );								//¸ó½ºÅÍ Å×ÀÌºí¿¡ Æ÷ÀÎÅÍ Á¦°Å


	int LoadEnemyList( char *szFile );
};

//StgArea ÃÖ´ë °¹¼ö 
#define STAGE_AREA_MAX		64

extern STG_AREA	*StageArea;				//Stg_Area ¼±¾ð

extern DWORD		dwPlayServTime;
extern rsSERVER_CONFIG		rsServerConfig;				//¼­¹ö ¼³Á¤ ±¸Á¶
extern smCHAR		*chrAutoPlayer;					//[AUTOPLAYER_MAX];
extern rsPLAYINFO	*rsPlayInfo;				//[CONNECTMAX];

extern int Server_SqlReady;
extern HWND	hDebugWnd;
extern CRITICAL_SECTION	cSerSection;
extern int Server_SqlReady;

extern time_t		tServerTime;

extern DWORD		dwBabelPlayTime;			//°Å´ë¸ó½ºÅÍ ¹Ùº§ À¯Áö½Ã°£
extern int			BabelPlayField;				//°Å´ë¸ó½ºÅÍ ¹Ùº§ ÇÊµå

extern DWORD		dwKelvezuPlayTime;			//°Å´ë¸ó½ºÅÍ ÄÌº£Áê À¯Áö½Ã°£
extern int			KelvezuPlayField;			//°Å´ë¸ó½ºÅÍ ÄÌº£Áê ÇÊµå

///////////////////////////////////////////////////////////////////////

//ºí·¹½º Ä³½½ ¿ëº´ Á¦ÇÑ¼ö·® Á¤ÀÇ
#define srCASLTE_SOLDER_CLAN_MAX	20
#define srCASLTE_SOLDER_MAX			1
#define srCASLTE_SOLDER_KIND_MAX	5

//ºí·¹½º Ä³½½ Á¤º¸ ±¸Á¶
struct	rsBLESS_CASTLE {

	int		CastleMode;
	DWORD	dwMasterClan;
	int		DefenceLevel;
	DWORD	dwLimitTime;
	int		Counter;

	int		Tax;				//ÇöÀç ¼¼À²
	int		NextTax;			//´ÙÀ½ ¼¼À²

	DWORD	dwBattleOverTime;	//ÀüÅõ Á¾·á ½Ã°£
	int		SoulFountain_PotionCount;		//¿µÈ¥ÀÇ »ùÅÍ ¹°¾à ´©Àû
	DWORD	dwSoulFountainTime;				//¿µÈ¥ÀÇ »ùÅÍ ¹°¾à ¹ß»ý½Ã°£
	DWORD	dwSoulFountainTime2;			//¿µÈ¥ÀÇ »ùÅÍ ¹°¾à º¸³¾½Ã°£
	int		SoulFountain_LastUserCount;

	DWORD	dwStartTime;
	short	TimeSec[2];						//ÁøÇà½Ã°£ÃÊ[0] Á¾·á½Ã°£ÃÊ[1]	
	int		SelectedSkill;					//¼±ÅÃµÈ ½ºÅ³

	int		Temp[10];

	smTRANS_BLESSCASTLE	BlessCastleSetup;
	rsUSER_LIST_TOP10	ClanTop10;
	ATTACK_DAMAGE_LIST	*lpAttackDamageList;
	char	bCrystalSolderCount[4];
	char	bCrystalTowerCount[4];
	smCHAR	*lpChar_ValhallaTower;
	DWORD	dwScoreLogTime;				//°ø¼ºÁ¡¼ö ÀúÀå½Ã°£

};

extern rsBLESS_CASTLE	rsBlessCastle;				//ºí·¡½º Ä³½½ °ø¼º Á¤º¸


struct	rsCURRENCY_LOG {	
	//»ç¿ëµÈ µ· ÅëÈ­·® ±â·Ï
	INT64	int64_CraftMoney;
	INT64	int64_AgingMoney;
	INT64	int64_ShopMoney;
	INT64	int64_ShopPotionMoney[3];

	INT64	int64_ForceOrbMoney;
	INT64	int64_WarpgateMoney;
	INT64	int64_LearnSkillMoney;
};

extern	rsCURRENCY_LOG	CurrencyLog;

//////////////////////////////////////////////////////////////////////////

#define	srMONSTER_KILL_QUE_MAX		1024
#define	srMONSTER_KILL_QUE_MASK		1023

struct	rsKILL_MONSTER_INFO {
	DWORD	dwAutoCharCode;
	DWORD	dwCharSoundCode;
	DWORD	dwMonObjectSerial;
	DWORD	dwUserObjectSerial;
	int		x,y,z,Area;
	int		PartyFlag;
	DWORD	dwParam[4];
};

struct	TRANS_KILL_MONSTER_INFO {
	int		size,code;
	DWORD	tCode;
	int		KillInfo_Count;
	int		Temp[4];
};

//////////////////////////////////////////////////////////////////////////

/////////////// º§¶óÆ®¶ó ¸ó½ºÅÍ ¹èÄ¡ ±¸Á¶Ã¼ //////////////////////////////
//¸¶Áö¸· Ä«¿îÅÍ
#define	rsHARDCORE_COUNT_END	8	
#define	hCORE_ROUND_MAX		9

struct	_sHCORE_MONSTER {
	char	szName[32];
	smCHAR_INFO	*lpCharInfo;
	int		perCount;
};

struct	sHCORE_MONSTER {

	_sHCORE_MONSTER	hCoreMonster1;
	_sHCORE_MONSTER	hCoreMonster2;
	_sHCORE_MONSTER	hCoreMonster3;
	_sHCORE_MONSTER	hCoreMonster4;
	_sHCORE_MONSTER	hCoreMonsterBoss;

	int		PerCount;
	int		StartHour;
	int		State;
	int		MaxMonster;
	int		DelayTime;			//½ÃÀÛ½Ã µô·¹ÀÌ ½Ã°£
};

///////////////////////////////////////////////////////////////////////////////

//µ¥ÀÌÅ¸¼­¹ö·Î °æÀ¯Àü¼Û
int rsSendDataServer( smWINSOCK *lpsmSock , void *szData );
//Äù½ºÆ® ÁøÇà Ã³¸®
int rsProcessQuest( rsPLAYINFO *lpPlayInfo , smCHAR *lpChar , int QuestCode , int QuestParam );
//»óÁ¡ ¾ÆÀÌÅÛ ¸ñ·Ï Å¬¶óÀÌ¾ðÆ®¿¡ Àü¼Û
int SendShopItemList( smWINSOCK *lpsmSock , smCHAR *lpChar );
//½ºÅ³ ¼ö·Ã NPC
int SendSkillMenu( smWINSOCK *lpsmSock , smCHAR *lpChar , int Mode );
//Ã¢°í ¿­±â
int SendOpenWareHouse( smWINSOCK *lpsmSock );
//¾ÆÀÌÅÛ Á¶ÇÕÃ¢ ¿­±â
int SendOpenMixItem( smWINSOCK *lpsmSock , int MixFlag );
//¸ð±ÝÇÔ ¿­±â
int SendOpenCollectMoney( smWINSOCK *lpsmSock );
//°æÇ°ÀÌº¥Æ®
int SendOpenEventGift( smWINSOCK *lpsmSock );
//¿¡ÀÌÂ¡ Ã¢ ¿­±â
int SendOpenAgingItem( smWINSOCK *lpsmSock );
//Å¬·£ ¸Þ´º ¿­±â
int SendOpenClanMenu( smWINSOCK *lpsmSock );
//ÀÌº¥Æ® NPC
int SendOpenEvent( smCHAR *lpChar , rsPLAYINFO *lpPlayInfo , int EventFlag );
//¼±¹° ¹è´Þ
int SendOpenGiftExpress( rsPLAYINFO *lpPlayInfo , DWORD	dwItemCode , DWORD dwPassCode_Param );
// pluto ¾ÆÀÌÅÛ Á¦·ÃÃ¢ ¿­±â
int SendOpenSmelting( smWINSOCK *lpsmSock );
// pluto ¾ÆÀÌÅÛ Á¦ÀÛÃ¢ ¿­±â
int SendOpenManufacture( smWINSOCK *lpsmSock );
//SoD ÁøÇà »óÈ² Ãâ·Â
TRANS_SOD_RESULT *rsSod_GetRealTimeScore( rsPLAYINFO *lpPlayInfo );
// ¼®Áö¿ë - ¹Í½ºÃÄ ¸®¼Â Ã¢ ¿­±â
int SendOpenMixtureItemReset( smWINSOCK *lpsmSock );

//Å¬¶óÀÌ¾ðÆ® ²ö±è ( Å©¸®Æ¼Ä® »ç¿ë ¾ÈÇÔ )
int DisconnectUser( smWINSOCK *lpsmSock );
//ÇØÅ· ½Ãµµ ±â·Ï ÆÄÀÏ·Î ³²±è
int RecordHackLogFile( rsPLAYINFO *lpPlayInfo , void *lpTransCommand );

//¹üÀ§Çü °ø°Ý ÆÇÁ¤
int RecvRangeAttack( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData );
//¹üÀ§Çü °ø°Ý ¹ÞÀ½ ( À¯Àú °ø°Ý )
int RecvRangeAttackUser( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData );


//ÇØ´ç ÇÊµå¿¡¼­ Ä³¸¯ÅÍ¸¦ Ã£´Â´Ù
smCHAR *srFindCharFromSerial( DWORD dwObjectSerial , int AreaNum );
//Ä³¸¯ÅÍ¸¦ Ã£´Â´Ù ( ³ªÁß¿¡ »¡¸® ¯À»¼ö ÀÖ°Ô ÄÚµåÈ­ ½ÃÄÑ ¹Ù²ã Áà¾ß ÇÔ )
smCHAR *srFindCharFromSerial( DWORD dwObjectSerial );
//Ä³¸¯ÅÍ¸¦ Ã£´Â´Ù ( ³ªÁß¿¡ »¡¸® ¯À»¼ö ÀÖ°Ô ÄÚµåÈ­ ½ÃÄÑ ¹Ù²ã Áà¾ß ÇÔ )
rsPLAYINFO *srFindUserFromSerial( DWORD dwObjectSerial );
//±×·£µåÈú¸µ
int rsPlayGrandHealing( rsPLAYINFO *lpPlayInfo , smTRANS_COMMAND *lpTransCommand );
//Èú¸µ
int	rsPlayHealing( smTRANS_COMMAND *lpTransCommand );

//ºô¸µ ³²Àº ½Ã°£ Ç¥½Ã
int srDisplayBillingTime( rsPLAYINFO *lpPlayInfo , int Add_BillingTime );

//ÁÖº¯ À¯Àú¿¡°Ô ¸í·É º¸³¿
int	rsSendCommandUser( rsPLAYINFO *lpPlayInfo , smTRANS_COMMAND_EX	*lpTransCommandEx );
//ÁÖº¯ À¯Àú¿¡°Ô ¸í·É º¸³¿
int	rsSendCommandUser2( rsPLAYINFO *lpPlayInfo , smTRANS_COMMAND *lpTransCommand );


//¼­¹ö¸¦ Á¾·á½ÃÅ²´Ù ( Á¾·á½ÃÅ°´Âµ¥ °É¸®´Â ½Ã°£Àº ¾à 6~10ºÐ Á¤µµ ¼Ò¿ä )
int	rsShutDown();
//¾ÆÀÌÇÇ ÁÖ¼Ò¸¦ µÚÁý¾î¼­ º¯È¯
DWORD GetSwapIPCode( char *szIP );

//ÀÌº¥Æ® ·Î±×¿Â ¼º°øÃ³¸®
int rsEventLogOn_Sucess( rsPLAYINFO *lpPlayInfo );



//SOD Áö¿ª¹øÈ£ ±¸ÇÏ±â
int rsGetSoD_AreaCode( int x, int y, int z ) ;
//·ç½ÃÆÛ ÀÏ¹Ý°ø°Ý½Ã ½ºÅ³µµ °°ÀÌ Àû¿ë (¹üÀ§ÁöÁ¤)
int rsSendRangeDamage( smCHAR *lpChar , rsPLAYINFO *lpMainPlayInfo , int Range , int SubDamgePers );
//¸ó½ºÅÍ »ý¸í·Â Àç»ýÄ¡ ±¸ÇÏ´Â ÇÔ¼ö
int rsGetMonsterLifeRegen( smCHAR *lpChar );

//Å¬·£ ¸Ó´Ï ±â·Ï
int	rsClanMoneyLog( rsPLAYINFO *lpPlayInfo , int Money , int RestMoney );


//¼­¹ö Æ÷¼Ç¿¡ ¹°¾à Ãß°¡
int rsAddServerPotion( rsPLAYINFO *lpPlayInfo , DWORD dwPotionCode , int PotionCount );
//¼­¹ö Æ÷¼Ç¿¡¼­ ¹°¾à ±¸ÇÏ±â
int rsGetServerPotion( rsPLAYINFO *lpPlayInfo , DWORD dwPotionCode );

//ÇØÅ· ½Ãµµ ±â·Ï ÆÄÀÏ·Î ³²±è
int RecordHackLogFile( rsPLAYINFO *lpPlayInfo , void *lpBuff );


//½ºÅ³ ¼ÒÈ¯¸ó½ºÅÍ ÃâÇö ½ÃÅ´
smCHAR *OpenMonsterFromSkill( DWORD SkillCode , int x, int y, int z , rsPLAYINFO *lpPlayInfo , smCHAR *lpEnemyChar );
//¼ÒÈ¯¿¬°á¸÷ Ã£±â
smCHAR *rsGetLinkChar( smCHAR *lpMasterChar );


//ºí·¡½ºÄ³½½ ¼³Á¤Á¤º¸ ¼ö½Å
int rsRecvBlessCastInfo( rsPLAYINFO *lpPlayInfo , void *lpPacket );
//ºí·¡½ºÄ³½½ ¼³Á¤Á¤º¸ ¼Û½Å
int rsSendBlessCastInfo( rsPLAYINFO *lpPlayInfo , int Mode );

//Å¬·£ ÄÚµå ±¸ÇÏ±â
DWORD GetClanCode( int ClassClanCode );


//´Ù¸¥¼­¹ö¿¡ ¾÷µ¥ÀÌÆ® Á¤º¸ º¸³¿
int	rsUpdateServerParam( rsPLAYINFO *lpPlayInfo , DWORD dwUpdateCode , int Param1 , int Param2 , int TargetMode );


///////////////////////// µð¹ö±×¿ë Ãâ·Â //////////////////////
int rsDebugMessageToClient( rsPLAYINFO *lpPlayInfo , char *szDmgMsg );	//µð¹ö±× ¸Þ¼¼Áö Ãâ·Â


////////////////////////// º£Æ®³² °æÇèÄ¡ ½Ã°£ºÐ¹è /////////////////////////////
int rsGetExp_GameTime( rsPLAYINFO *lpPlayInfo );
// pluto Á¦ÀÛ ·é °Ë»ç // Àåº° - ´ëÀåÀåÀÌÀÇ È¥
DWORD ManufactureCheckRune( rsPLAYINFO *lpPlayInfo, DWORD RecipeCode, DWORD *pRuneCode );

////////////////////////// Áß±¹ ½Ã°£Á¦ÇÑ ´©Àû½Ã°£¿¡ µû¸¥ ¸Þ¼¼Áö Ãâ·Â ///////////////////
int rsDispay_GameTime( rsPLAYINFO *lpPlayInfo , DWORD dwTimeOld );

// ¹ÚÀç¿ø - 2010 ¿ùµåÄÅ ÀÌº¥Æ® - Ãà±¸°ø Æ÷¼Ç »ç¿ë
int	rsUseSoccerBallPotionItem( DWORD dwItemCode , rsPLAYINFO *lpPlayInfo );

// ¹ÚÀç¿ø - ¿¡ÀÌÂ¡³»¸¾´ë·Î(¿¡ÀÌÂ¡ ¾ÆÀÌÅÛ ¸¸µé±â)
int SetAgingItem(sITEMINFO *pItem, int AgingNum);

int rsSendGameServer_PrimeItem2( rsPLAYINFO *lpPlayInfo );

// ¹ÚÀç¿ø - ºô¸µ µµ¿ì¹Ì Æê Ãß°¡  // ¹ÚÀç¿ø - ±Ù·Â ¸®µà½º Æ÷¼Ç Ãß°¡
// ¹ÚÀç¿ø - ¸ÞÀÎ ¼­¹ö·Î ½Ã°£Á¦ ºô¸µ ¾ÆÀÌÅÛ Á¤º¸ º¸³¿
// rsSendGameServer_PrimeItem3 -> (ºô¸µ µµ¿ì¹Ì Æê, ¹ìÇÇ¸¯ Ä¿½ºÇÍ EX, ±Ù·Â ¸®µà½º Æ÷¼Ç)
int rsSendGameServer_PrimeItem3( rsPLAYINFO *lpPlayInfo );