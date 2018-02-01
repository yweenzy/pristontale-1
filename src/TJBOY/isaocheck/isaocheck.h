#ifndef __ISAOCHECK_H__
#define __ISAOCHECK_H__
#ifndef USE_PROSTONTALE		//=========== ÇÁ¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
#include "..\\clanmenu\\cE_CViewClanInfo.h"
#endif

#define SAVE_DIR	"savedata\\clanDATA"
#define SAVE_EXE	"cl"

// ÀÌ°ÍÀº £É£Ó£Á£ÏÀÇ ¿¡·¯ ÄÚµåÀÌ¹Ç·Î
// º¯°æÇÏ°í ³× ºñ¹æÇÏ°í£®

enum{
	ISAO_REJECT_OK = 0,			// ¿¡·¯¾øÀ½£®¼º°ø£®
	ISAO_REJECT_BADPASS = 1,	// ÆÐ½º ¿öµå ºÒ·®£®
	ISAO_REJECT_BADNAME = 2,	// À¯Àú¹Ì µî·Ï£®
	ISAO_REJECT_LOCKOUT = 3,	// ÀÏÁ¤ ±â°£³»¿¡ ¿¬¼Ó ÆÐ½º ¿öµå ¿À¹ö µîÀ¸·Î ·ÎÅ©¾Æ¿ô
	ISAO_REJECT_TEST_OVER = 4,	// º» µî·ÏÀ» ÇÏÁö ¾Ê¾Ò±â ¶§¹®¿¡ £¬ÀÓ½Ã ÆÐ½º ¿öµåÀÇ À¯È¿ ±âÇÑÀÌ ²÷¾îÁ³´Ù
	ISAO_REJECT_UNFAIR = 5,		// ºÎÁ¤ À¯Àú ¶§¹®¿¡ £¬°ÅºÎ£®
	ISAO_REJECT_STOPPING = 6,	// ÇÑ¶§ Á¤Áö
	ISAO_REJECT_EXPIRE = 7,		// ±âÇÑ ¸¶°¨
	ISAO_REJECT_NOT_BOUGHT = 8, // Á¦Ç°¹Ì ±¸ÀÔ
	ISAO_REJECT_DB_MAINTE = 9,	// £Ä£Â ¸ÞÀÎÅÍ³Í½º Áß(¼Ó)
	ISAO_REJECT_OTHER = 10,		// ±âÅ¸ÀÇ ¿¡·¯

	//ÁÖÀÇ ===============================================================================
	//ktj : 100~999¹ø »çÀÌ´Â À¥¼­¹öÀÇ php¿¡¼­ ¸®ÅÏÄÚµå·Î »ç¿ëÇÏ¹Ç·Î ¿©±â¼­ Àý´ë Á¤ÀÇÇÏÁö¸»°Í.
	//ÁÖÀÇ ===============================================================================


	// ÀÌ ¾Æ·¡´Â º¯°æÇÒ ¼ö ÀÖ´Ù£®
	ISAO_ERR_TOP = 1000,
	ISAO_ERR_WINSOCK_NOERR,		//Ã³À½¼ÂÆÃ½Ã»ç¿ë 
	ISAO_ERR_WINSOCK_START,		//À©¼Ó START½Ã ¿¡·¯¹ß»ý					//window only
	ISAO_ERR_WINSOCK_VERSION,	//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
	ISAO_ERR_TCP_CONNECT,		// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
	ISAO_ERR_SSL_READ,			// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
	ISAO_ERR_SSL_TIMEOUT,		// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
	ISAO_ERR_NONE_REEJCT,		// ÀÀ´ä ¹øÈ£°¡ ¹®ÀÚ¿­¿¡ µé¾î°¡°í ÀÖÁö ¾Ê´Ù.
	ISAO_ERR_UNKNOWN_REJECT,	// ÀÀ´ä ¹øÈ£°¡ ÀÎ½ÄÇÒ ¼ö ¾ø´Ù.
	ISAO_ERR_RECONNECT,			// ¸®ÄÁ³ØÆ®ÇÏµµ·ÏÇÑ´Ù.
	ISAO_ERR_END
};

int IsaoCheck( char *id, char *pass, int iCheckOn, int iTimeOut , char *ipaddr, long StartTime );
int IsaoCheck2( char *id, char *pass, int iCheckOn, int iTimeOut , char *ipaddr, long usertime);

int UserLogin(char* UserID, char* PassWord);
int InsertUser(char* UserID,char* PassWord,char* UserName);
int DeleteUser(char* UserID);
int LoginCheck(char* UserID,char* start_time);
int Login_List(char* UserID,char* end_time,char* use_time);
#endif


//ÇØ¿Ü
bool MultiByteToWideCharByCodePage(char *szMBCS,wchar_t *szUnicode,int iCodePage);
bool WideCharToMultiByteByCodePage(wchar_t *szUnicode,char *szMBCS,int iCodePage);
bool MBCSToUTF8(char *szMBCS,char *szUTF8,int iMBCSCodePage);
bool UTF8ToWeb(char *szUTF8,char *szWeb);
bool MBCSToWeb(char *szMBCS,char *szWeb,int iMBCSCodePage);





class ISAOCHECK
{
public:
	int iCheckFlag;
	int iTimeOut;
	int hostPORT;
	char hostName[64];
	//ygy
	int hostPORT1;
	char hostName1[64];
	//end ygy


	int HSsu;					//Çí»ç½ºÆ®¸µÀÇ °¹¼ö
	char *fileDATA_HS[30];		//ÃÑ 2048binaryÀÇ µ¥ÀÌÅ¸°¡ 4096 hexa stringÀ¸·Î ¹Ù²î¾îµé¾î°¨.


    ISAOCHECK();
	~ISAOCHECK();

	void init();								//°× Ã³À½¿¡¼­ ¼ÂÆÃ
	void init(int iCheckON, int iTimeOUT );		//À¥db»ç¿ë½Ã¸¶´Ù ¼ÂÆÃ
	void init_HostName_Port(char *hostname, int port);
	void init_HostName_Port1(char *hostname, int port);
	void close();
	void main();
	
	
	//ÁÖ·Î ½ºÆ®¸µÀ» ¹Þ´Â ÇÔ¼ö
	int connect_WEBdb( char *szWriteBuffer, char *szReadBuffer);
	//ygy
	int connect_WEBdb_1( char *szWriteBuffer, char *szReadBuffer);
	//ÆÄÀÏµîÀÇ ¹ÙÀÌ³ª¸®¸¦ ÀÐ´Â ÇÔ¼ö.
	int connect_WEBdb_BINARY( char *szWriteBuffer, char *szReadBuffer, int *dataSize);

	int chk_readbuffer(char *cmd, char *readbuf, int *iRejectC );			//ÀÐÀº µ¥ÀÌÅ¸¿¡¼­ ´äº¯¿ë intµ¥ÀÌÅ¸¸¦ »Ì¾Æ³½´Ù.
	int chk_readStrBuf(char *cmd, char *readbuf, char *retBuf);	//ÀÐÀº µ¥ÀÌÅ¸¿¡¼­ ´äº¯¿ë ½ºÆ®¸µµ¥ÀÌÅ¸¸¦ »Ì¾Æ³½´Ù.

	int IsaoCheck( char *id, char *pass, char *ipaddr, long StartTime);
	int IsaoCheck_GameExit(char *id, char *pass, char *ipaddr, long usertime);



	//Å¬·£¿øÀÎ°¡ÀÇ ¿©ºÎ(Å¬·£¯…ÀÌ¸é Å¬·£ÀÌ¸§ÀüÇØÁÜ.)
	//int isClanMember(char *id, char *ret_Buf);
	int isClanMember(char *ClanZang_id, char* gserver,char* ClanZang_ChaName,char* ret_Buf);

	//È£µ¿ClanÃß°¡
	int isCheckClanMember(char *pszServerName, char *pszUserName);

	//¸â¹ö Ãß°¡
	//int joinClanMember(char *clanName, char *memId, char *memCharId);
	//int joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName,char* ClanName,char* ClanWon,char* ClanWon_ID);
	int joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName,char* ClanName,char* ClanWon,char* ClanWon_ID,int level,DWORD chtype,int joinlevel,char *chipflag);
	
	

	//YGY:isCheckClanJang //°ü·ÃµÈ °èÁ¤ÀÌ Å¬·£ÀåÀ¸·Î µî·ÏµÇ¾î ÀÖ´ÂÁö Ã¼Å©
	int isCheckClanJang(char *ClanZang_ID, char *gserver);
	//YGY: Å¬·£ÀÌ¸§ Áßº¹Ã¼Å©
	int isCheckClanName(char *ClanName,char *gserver);
	//makeClan
	int makeClan(char *ClanZang_ID, char* gserver,char* ClanZang_ChaName,char* ClanName,char *explanation,DWORD chtype,int level,char* data);
	//clanName¹öÆÛ¿¡¼­ ¿øÇÏ´Â Ä®·³ µ¥ÀÌÅ¸¸¦ ÀÐ¾î¿È.
	int read_ClanName(int readClumns);
	//int read_ClanData(char *clname, char *ret_Buf);		//clanNameÀÇ µ¥ÀÌÅ¸¸¦ °¡Á®¿È.
	int read_ClanData(char *ClanZang_ID,char* gserver,char* ClanZang_ChaName,char* ret_Buf);		//clanNameÀÇ µ¥ÀÌÅ¸¸¦ °¡Á®¿È.
	//int BreakUPClan(char *clname);			//Å¬·£À» »èÁ¦ÇÔ.
	int BreakUPClan(char *ClanZang_ID,char *gserver,char *ClanZang_ChaName, char *ClanName);			//Å¬·£À» »èÁ¦ÇÔ.
	//int Banishiment(char *clname, char *banisID);	//Æ¯Á¤idÀ» Ãß¹æÇÔ.
	int Banishiment(char *ClanZang_ID,char *gserver,char *ClanZang_ChaName,char *ClanName, char *ClanWon);
	int WarhouseRight(char *clname, char *right_str);	//Ã¢°í±ÇÇÑ ¹Ù²Þ.
	int updateFlag(char *clname);
	
	int Secession(char* clanzang,char* gserver,char* SecessionID,char* clanname);	//Å»Åð
	//ygy : ÃÊ±â Ã¢ °ü·Ã ÇÃ·¡±×
	int isPFlag(char *userid,char *clanname, char *chaname,char *gserver,char *pflag, char *gunbun);
	//ygy : Å¬·£¸¶Å©¹øÈ£·Î Å¬·£ Á¤º¸ °®¾î¿À±â
	int ReadClanInfo(char *clanNum,char* ret_Buf);


	//¼­¹öÀÇ Æ¯Á¤ µð·ºÅä¸®¾ÈÀÇ Å¬·£ÀÇ ±×¸²À» ÀÐ¾îµéÀÎ´Ù.
	int read_ClanImage(char *clanname,char *filename);
	//´Ù¸¥ Å¬·£¸¶Å© ÀÌ¹ÌÁö ÀÐ¾î µéÀÓ
	int read_ClanImage2(char *clanname,char *filename,CLANINFO *ci);	
	//Æ¯Á¤µð·ºÅä¸®¾ÈÀÇ Å¬·£±×¸²À» ¼¼ÀÌºêÇÔ : ¸ðµÎ hexa ½ºÆ®¸µÀ¸·Î ¼­¹ö¿¡ ÀúÀåµÊ.
	int write_ClanImageFile(char *filename);		

	//Æ¯Á¤ Ä³¸¯ÅÍ¿¡ ´ëÇÑ °æ°í¹®
	//int connect_WEBdb_NOTICE1(char *severIP, int port, char *szWriteBuffer, char *szReadBuffer);
	int connect_WEBdb_NOTICE(char *szWriteBuffer, char *szReadBuffer);
	int ReadNotice(char *userid,char *chaname,char *gserver,char *buf);	
	//ÀÌÀÓ
	int LeaveClan(char *clanname,char *chaname,char *gserver);

	//ÀÌÀÓ°ü·Ã ÇÃ·¡
	int isKPFlag(char *userid,char *clanname, char *chaname,char *gserver,char *pflag, char *gunbun);

	int AppointSubChip(char *gserver,char* clanwon);//ºÎÅ¬·£Àå ÀÓ¸í
	int ReleaseSubChip(char *gserver,char* clanwon); //ºÎ Å¬·£Àå ÇØÀÓ

	//¼­¹ö¿¡¼­ ¿þÀÌºêÆÄÀÏ °¡Á®¿À±â
	int	GetWavFile(char* FileName);


	void Convert_bin2HS(char *sorce, int len);
	int WEBdb_Exam();
	






	int read_sod2(char *usid, char *charname,char *gserver, int index , char *szSod2Buff);

};




#undef EXTERN
#ifdef __ISAOCHECK_CPP__
	#define EXTERN
#else
	#define EXTERN extern
#endif

EXTERN ISAOCHECK iCheck;




