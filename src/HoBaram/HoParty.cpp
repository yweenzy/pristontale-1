
#include "sinbaram\\SinLinkHeader.h"
#include "..\\HoBaram\\HoLinkHeader.h"
//#include "HoParty.h"

#include "Language\\language.h"
#include "..\\HoBaram\\HoTextFile.h"

//ktj : Å¬·£¸Þ´º¶§¹®¿¡ »ðÀÔ
#include "tjboy/clanmenu/tjclanDEF.h"
#include "tjboy/clanmenu/tjclan.h"


extern char UserAccount[256];		//id°¡ µé¾îÀÖ´Â ¹öÆÛ
extern char	szConnServerName[16];	//Á¢¼ÓÇÑ ¼­¹öÀÌ¸§ÀÌ µé¾îÀÖ´Â ¹öÆÛ



/*///////////////////////////////////////////////////////////////////////////
: ÇÔ¼ö  ¸í :  fd( char *fmt, ...)
: ÇÏ´Â  ÀÏ :  ÆÄÀÏÀ» ÀÌ¿ëÇÑ µð¹ö±ë¿ë
///////////////////////////////////////////////////////////////////////////*/
void fd222(char *buff)
{
    HANDLE hFile;
    DWORD dwAcess =0;
    hFile = CreateFile( "abc.txt", GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

    if( hFile != INVALID_HANDLE_VALUE ) {
        SetFilePointer( hFile , 0 , NULL , FILE_END );
        //µ¥ÀÌÅ¸ ¾²±â     ¹öÆÛ    ¾µÅ©±â    ½ÇÁ¦·Î ¾²¿©Áø ¹ÙÀÌÆ®¼ö
        int chk = WriteFile( hFile , buff , lstrlen(buff) , &dwAcess , NULL );
        //ÆÄÀÏ ´Ý±â
        CloseHandle( hFile );
    }
}


void fd( char *fmt, ...)
{
	return;

    char buff[4096] = "abc";
	
    va_list args;

    va_start( args, fmt );
    vsprintf( buff, fmt, args );
    va_end( args );

    strcat( buff, "\r\n" );
	

	if(strlen(buff)>1024 ) {
		int abc = 1;
		abc=2;
	}

    fd222(buff);
}


void fd2( char *fmt, ...)
{
	return;

	char buff[4096];
	
    va_list args;

    va_start( args, fmt );
    vsprintf( buff, fmt, args );
    va_end( args );

    strcat( buff, "\r\n" );

	if(strlen(buff)>1024 ) {
		int abc = 1;
		abc=2;
	}

    fd222(buff);
}




/*///////////////////////////////////////////////////////////////////////////
: ÇÔ¼ö  ¸í :                 INIÀÐ±â
: ÇÏ´Â  ÀÏ :
///////////////////////////////////////////////////////////////////////////*/
//µ¥ÀÌÅ¸¼ÂÆÃÀ§ÇÑ ini¸¦ ¿­¾î °¢Á¾ ¿É¼ÇÀ» ÀÐ´Â´Ù.([optStr1]ÀÇ optStr°ÍÀ» ÀÐÀ½¿¡ ÁÖÀÇ)
int read_INI(char *iniF, char *optStr1, char *optStr, char *rStr)
{
    char folder[] = ".\\";
    char strFilename[128];
    strcpy ( strFilename , folder);
    strcat ( strFilename , iniF );

    if(rStr==NULL) { //intÇü
        return GetPrivateProfileInt(optStr1, optStr, 0, strFilename );
    }
    //stringÇü
    return GetPrivateProfileString(optStr1, optStr, NULL, rStr, 128, strFilename);
    //return 0;
}

int save_INI(char *iniF, char *optStr1, char *optStr, char *rStr, int value)
{
    char folder[] = ".\\";
    char strFilename[128];
    strcpy ( strFilename , folder);
    strcat ( strFilename , iniF );
	char buf[64];


    if(rStr==NULL) { //intÇü

		wsprintf(buf, "%d", value);
        //return GetPrivateProfileInt(optStr1, optStr, 0, strFilename );
		return WritePrivateProfileString(
			optStr1, optStr,
			buf,
			strFilename);  
    }
    //stringÇü
    //return GetPrivateProfileString(optStr1, optStr, NULL, rStr, 128, strFilename);
	return WritePrivateProfileString(
			optStr1, optStr,
			rStr,
			strFilename);  

		
    //return 0;
}






/*==================================================================================
//
// ktj  : »õ·Î ¸¸µç°Í.													start
//
==================================================================================*/
class HoParty_KTJ
{
public:
	HoParty_KTJ();
	~HoParty_KTJ();



	//PartyInterface ¸®¼Ò½º..
	int									MatPartyBackGround;	//¹è°æ
	int									MatTitle[4+2] ;		//Å¸ÀÌÆ².(Äù½ºÆ®,Ã¤ÆÃ,µ¿·á
	POINT								BackStartPos;		//ÀÎÅÍÆäÀÌ½º ±âº»À§Ä¡
	int xLeft, xRight;

	RECT menuPos[30];		//¸Þ´º¼ÂÆÃ.
	int menuSu;
	int PmenuN, savePmenuN;
	void InitMenuSet(int menuN);


	


	int  questSelN;
	void quest_Progress_Clear();
	void quest_End_Clear();
	void quest_Progress_Set(char *q_name, char *f_name);
	int  qNameProgress_SU;
	void quest_End_Set(char *q_name, char *f_name);
	int  qNameEnd_SU;
	int  qNameS_ENDs , qNameE_ENDs ;		//Äù½ºÆ®ÀÌ¸§ÀÇ È­¸é»ó¿¡ ³ª¿Ã ¸ÇÀ§ÂÊ°ú ¸Ç¾Æ·¡ÂÊ 
	void qN_Pressf_CLEAR();				//Äù½ºÆ®ÀÇ ÇïÇÁÃ¢¾ø¾Ö±â

	void quest_Sel_Progress();	//Äù½ºÆ®ÁøÇà¹öÆ°´©¸¥°É·Î ¼ÂÆÃÇÔ.

	int  qNameS, qNameE;		//Äù½ºÆ®ÀÌ¸§ÀÇ È­¸é»ó¿¡ ³ª¿Ã ¸ÇÀ§ÂÊ°ú ¸Ç¾Æ·¡ÂÊ 
	int  qNameSelN;			//Äù½ºÆ®ÀÌ¸§ÀÇ ¼±ÅÃ¹øÈ£
	char qNameb[64][128];	//Äù½ºÆ®ÀÌ¸§À» ³ÖÀº ¹öÆÛ(Äù½ºÆ®Ã¢¿¡¼­ ¼±ÅÃ°¡´ÉÇÔ)
	char qFnameb[64][128];	//Äù½ºÆ®ÀÌ¸§¿¡ µû¸¥ ÇØ¼³ÆÄÀÏÀÇ ÀÌ¸§µé

	char qNameb_E[64][128];	//³¡³­ Äù½ºÆ®ÀÌ¸§À» ³ÖÀº ¹öÆÛ(Äù½ºÆ®Ã¢¿¡¼­ ¼±ÅÃ°¡´ÉÇÔ)
	char qFnameb_E[64][128];//³¡³­ Äù½ºÆ®ÀÌ¸§¿¡ µû¸¥ ÇØ¼³ÆÄÀÏÀÇ ÀÌ¸§µé


	char q_explation[64][128];	//Äù½ºÆ®ÀÇ ¼³¸í(ÃÖ´ë64ÁÙÀÌ¸ç ÇÑÆäÀÌÁö´ç 6ÁÙÀÓ)
	int  q_explationS;
	char q_explationTitle[128];	//Äù½ºÆ®ÀÇ ¼³¸í¿¡ »ç¿ëµÇ´Â Å¸ÀÌÆ²


	



	//Ã¤ÆÃ¿ë µ¥ÀÌÅ¸ÀúÀå¿ë
	//int chatButN;			//Ã¤ÆÃÀÇ ´­¸° ¹öÆ°ÀÇ ¹øÈ£
	//ÃÖ±Ù ±Ó¸»ÇÑ»ç¶÷ÀÇ ¸ñ·Ï
	char latestb[9][128];	//0~7±îÁö»ç¿ë
	int  latestb_LOG[9+1];	//·Î±×°¡µÇÀÖ´ÂÁö¿©ºÎ(¼­¹öÂÊ¿¡¼­ »ç¿ë°¡´É)

	//friend¿ë
	int fNameS, fNameE, fNameSu;		//Ä£±¸ idÀÇ È­¸é»ó¿¡ ³ª¿Ã ¸ÇÀ§ÂÊ°ú ¸Ç¾Æ·¡ÂÊ, ÃÑ°¹¼ö
	char fNameb[100+1][32];	//friend idÀ» ³ÖÀº ¹öÆÛ(Ã¤ÆÃÃ¢¿¡¼­ ¼±ÅÃ°¡´ÉÇÔ)
	int  fName_LOG[100+1];	//·Î±×°¡µÇÀÖ´ÂÁö¿©ºÎ(¼­¹öÂÊ¿¡¼­ »ç¿ë°¡´É)
	//deny¿ë
	int dNameS, dNameE, dNameSu;		//°ÅºÎ¿ë id
	int dNameSelN;			
	char dNameb[100+1][32];
	int  dName_LOG[100+1];	//·Î±×°¡µÇÀÖ´ÂÁö¿©ºÎ

	int cN_MenuN ;	//0:Ä£±¸¸Þ´ºÁß ÃÖ±Ù¸ñ·Ï 1: Ä£±¸µé¸ñ·Ï 2:°ÅºÎÀÚ¸ñ·Ï
	int cN_Pressf;	//¸®½ºÆ®Áß ´©¸¥°Å Ã½Å©
	int cN_PressfDBL;	//´õºíÅ¬¸¯´©¸¥°Å
	int cN_PressfDBL_Where;	//´õºíÅ¬¸¯ ¸Þ´º¹øÈ£.

	
	//µ¿·á->Ä£±¸    ================================== start
	void chat_PageChange(int sw);		//µ¿·á->Ä£±¸    idÀÇ ÀÌÀü,´ÙÀ½ ¸®½ºÆ®¸¦ º¸¿©ÁÜ.
	void chat_IDdelete();				//µ¿·á->Ä£±¸    id »èÁ¦½Ã ÇÊ¿äÇÔ.
	void chat_isLOG(char *name, int flag);
	//cN_Pressf ´­¸°¹øÈ£ ¼ÂÆÃ(ºó ºÎºÐÀº ¼ÂÆÃÀÌ ¾ÈµÇ±â ¶§¹®ÀÓ
	void chat_cN_Pressf(int press);
	void chat_IDinsert(int sw, char *id);

	void chatINI_read();	//°×Ã³À½µé¾î°¥¶§ ¼ÂÆÃÇÔ.
	void chatINI_save(int menuN);
	void chatDATA_Insert(int menuN, char *str);
	void chatDATA_delete(int menuN, int num);
	void latest_Insert(char *namestr);
	int chat_IDs(int dataN, int cnt, char *id);
	void chat_WhisperPartyPlayer(int num);
	void chat_WhisperPartyPlayer_close();


	int chatbuild_INIfiles();	//µ¿·á->Ä£±¸
	

	void chat_changeMENU(int sw);	//0:Ä£±¸->ÃÖ±Ù¸ñ·Ï, 1:Ä£±¸->Ä£±¸¸ñ·Ï, 2:Ä£±¸->°ÅºÎÀÚ¸ñ·ÏÀÇ ¸Þ´º¸¦ ¹Ù²Þ.


	//µ¿·á->Ä£±¸    ================================== end



	





	//ktj : ¤¾¤¾¤§ÀÌ ¸¸µç°Å ±×´ë·Î¾¸
	hoPartyMember	PartyMember[MAX_PARTY_MEMBER];	//ÆÄÆ¼¸É¹ö Á¤º¸ ±¸Á¶Ã¼..
	int				PartyMemberCount;				//ÇöÀç ÀÎ¿ø¼ö...

	//ktj : ÀÏ´Ü »èÁ¦
	int									PartyPosState;
	int									MouseDownPartyMember;

	int									MouseDownButton;
	
	//PartyInterface ¸®¼Ò½º..
	//int									MatPartyBackGround;
	DIRECTDRAWSURFACE				BmpMan[3];

	DIRECTDRAWSURFACE				BmpLifeBlue;
	DIRECTDRAWSURFACE				BmpLifeRed;

	DIRECTDRAWSURFACE				ToolTip[5];
	DIRECTDRAWSURFACE				Button[5];

	
	//POINT								BackStartPos;
	POINT								TextStartPos;
	
	//PartyMessageBox ¸®¼Ò½º..
	int									MatMessageBoxBackGround;
	POINT								MessageBoxStartPos;
	
	char								PartyMessageBoxChrName[128];
	DWORD								PartyMessageBoxChrCode;

	DIRECTDRAWSURFACE				BmpMessageOk[2];
	DIRECTDRAWSURFACE				BmpMessageCancel[2];

	int				MessageBoxDrawCount;
	BOOL			MessageBoxOpenFlag;			//MessageÃ¢ ¿ÀÇÂ ÇÃ·¡±×ÀÌ´Ù.




	void Init();
	void Load();
	void Close();


	
	int	 Draw();

	//sw=0, 1 //½ºÅ©·Ñ ¾ÈÇÏ°í »ç¿ë½ÃºÎ¸¥´Ù.
	int Main_menuSet(int sw);
	int	 Main(int sw);
	

	//ktj : ÁÖÀÇ : ÀÌÇÔ¼ö´Â »ç¿ë¾ÈÇÔ.
	int  AddMember(char *memberName,DWORD chrCode, int life, int level);


	//ktj : »õ·Î ¸¸µê. ============== start
	int AddMember(hoPartyMember *member,int cnt);
	void AddMember_memberSu(int memberSu);
	int PARTY_PLAYUPDATE(hoPartyMember *member,int cnt);
	int PARTY_RELEASE();
	//ktj : »õ·Î ¸¸µê. ============== end

	






	
	//ºÎ¼öÀû ÇÔ¼öµé ( ¸¶¿ì½º·Î ´©¸¥ ¸Þ´º ¹øÈ£ Ã½Å©)
	int chkeckMenuN();
	void menuSet(int sw);
	
	


	void Draw_questExplane(int x, int y);	//Äù½ºÆ®ÀÇ ¼³¸í±Û ±×¸®±â
	void Init_questExplane(char *string, int sw);	//Äù½ºÆ®ÀÇ ¼³¸í±Û ±×¸®±â




	//ÆÄÀÏÀÇ µ¥ÀÌÅ¸¼ÂÆÃÇÔ¼öµé			================= start
	int ReadFileData(char *fname);							//ÆÄÀÏÀ» ¸ù¶¥ÀÐ´Â´Ù.
	void ReadFileData_moveBuf(char *savebuf, int lineLen);	//ÀÐÀºµ¥ÀÌÅ¸¸¦ ¿øÇÏ´Â¹öÆÛ·Î ÇÑÁÙ¾¿ Â©¶ó¿Å±ä´Ù.
	//ÆÄÀÏÀÇ ¼³¸í±ÛÀÇ µ¥ÀÌÅ¸¼ÂÆÃÇÔ¼öµé	================= end

};

HoParty_KTJ	InterfaceParty_KTJ;



/*==================================================================================
//
// ktj  : »õ·Î ¸¸µç°Í.															end
//
==================================================================================*/
















HoParty	InterfaceParty;

//HFONT	hoFont11;

HoParty::HoParty()
{
	MessageBoxDrawCount = 0;
	BackStartPos.x = 800;
	BackStartPos.y = 155;
	
	TextStartPos.x = BackStartPos.x+102;
	TextStartPos.y = BackStartPos.y+38;
	
	BmpLifeBlue = NULL;
	BmpLifeRed  = NULL;

	for(int index = 0; index < 5; index++)
	{
		ToolTip[index] = NULL;
		Button[index] = NULL;
	}

	for ( int index = 0; index < 3; index++ )
		BmpMan[index] = NULL;
	
	//MessageBox¿ë..
	MessageBoxStartPos.x = 513;
	MessageBoxStartPos.y = 3;
	MatMessageBoxBackGround = -1;
	
	for ( int index = 0; index < 2; index++ )
	{
		BmpMessageOk[index] = NULL;
		BmpMessageCancel[index] = NULL;
	}

	MouseDownPartyMember = -1;
	MouseDownButton = -1;
	memset(PartyMember, 0, sizeof(PartyMember));
	PartyMemberCount = 0;
	MatMessageBoxBackGround = -1;

	MessageBoxOpenFlag = FALSE;
	PartyPosState = PARTY_NONE;

/*
#ifdef _LANGUAGE_JAPANESE

#include "..\\Japanese\\j_font.h"

	hoFont11 = 	CreateFont( 8,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
						SHIFTJIS_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        FIXED_PITCH | FF_MODERN,
						j_font );
#endif

	
#ifdef _LANGUAGE_CHINESE

	hoFont11 = 	CreateFont( 8,
                        0,
                        0,
                        0,
			FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
						GB2312_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
						"SimSun" );

#endif

#ifdef _LANGUAGE_KOREAN
	hoFont11 = 	CreateFont( 4,
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

#endif
*/

}


HoParty::~HoParty()
{
	Close();
}






//========================= Äù½ºÆ® ¸Þ´º °ü·Ã µ¥ÀÌÅ¸ ¼ÂÆÃ ============================= start
void HoParty::quest_Progress_Clear()
{
	InterfaceParty_KTJ.quest_Progress_Clear();
}

void HoParty::quest_End_Clear()
{
	InterfaceParty_KTJ.quest_End_Clear();
}

void HoParty::quest_Progress_Set(char *q_name, char *f_name)
{
	InterfaceParty_KTJ.quest_Progress_Set(q_name, f_name);
}

void HoParty::quest_End_Set(char *q_name, char *f_name)
{
	InterfaceParty_KTJ.quest_End_Set(q_name, f_name);
}

void HoParty::qN_Pressf_CLEAR()
{
	InterfaceParty_KTJ.qN_Pressf_CLEAR();
}
void HoParty::quest_Sel_Progress()	//Äù½ºÆ®ÁøÇà¹öÆ°´©¸¥°É·Î ¼ÂÆÃÇÔ.
{
	InterfaceParty_KTJ.quest_Sel_Progress();
}

//========================= Äù½ºÆ® ¸Þ´º °ü·Ã µ¥ÀÌÅ¸ ¼ÂÆÃ ============================= end


//========================= µ¿·á->Ä£±¸ ¸Þ´º °ü·Ã µ¥ÀÌÅ¸ ¼ÂÆÃ ============================= start
void HoParty::latest_Insert(char *namestr)	//ÃÖ±Ù¸ñ·ÏÀÇ ±Ó¼Ó¸»ÇÑ»ç¶÷ÀÇ ¸®½ºÆ® Ãß°¡.
{
	InterfaceParty_KTJ.latest_Insert(namestr);
}

//Ä£±¸¸ñ·Ï¿¡ id³ÖÀ»¶§
void HoParty::friend_Insert(char *id)
{
	InterfaceParty_KTJ.chat_IDinsert(3, id);
}


void HoParty::chat_isLOG(char *name, int flag)
{
	InterfaceParty_KTJ.chat_isLOG(name, flag);
}


//log¿©ºÎ¸¦ ¾Ë¾Æ³»±â À§ÇØ ÀÌ¸§À» ¹Þ¾Æ³»´Â°Í(
//dataN : µ¿·á->Ä£±¸ÀÇ ÃÖ±Ù¸ñ·Ï==0, Ä£±¸µé==1, °ÅºÎÀÚ==2
//cnt 0~15±îÁö
//id
int HoParty::chat_IDs(int dataN, int cnt, char *id)
{
	return InterfaceParty_KTJ.chat_IDs(dataN, cnt, id);
}


//0:Ä£±¸->ÃÖ±Ù¸ñ·Ï, 1:Ä£±¸->Ä£±¸¸ñ·Ï, 2:Ä£±¸->°ÅºÎÀÚ¸ñ·ÏÀÇ ¸Þ´º¸¦ ¹Ù²Þ.
void HoParty::chat_changeMENU(int sw)
{
	
	InterfaceParty_KTJ.chat_changeMENU(sw);
}

//id, ÆÐ½º¿öµåÀÔ·ÂµÈÈÄ ºÎ¸¦°Í.
int HoParty::chatbuild_INIfiles()	//µ¿·á->Ä£±¸
{
	return InterfaceParty_KTJ.chatbuild_INIfiles();
}


void HoParty::chat_WhisperPartyPlayer_close()
{
	InterfaceParty_KTJ.chat_WhisperPartyPlayer_close();
	
	
	//ktj : clan Ãª¸®šÀ ¸Þ´º¶«¿¡ ³ÖÀ½.
	//void clan_chat_WhisperPartyPlayer_close();	//cE_chatlist.cpp¿¡ Á¤ÀÇ
	//clan_chat_WhisperPartyPlayer_close();
	void chatlistSPEAKERflagChg(int flag);		//cE_chatlist.cpp¿¡ Á¤ÀÇ
	chatlistSPEAKERflagChg(0);
}






//========================= µ¿·á->Ä£±¸ ¸Þ´º °ü·Ã µ¥ÀÌÅ¸ ¼ÂÆÃ ============================= end


//½ºÅ©·Ñ¾Ê°í ¼ÂÆÃ½Ã¿¡ ÀÌ°ÉºÎ¸¥´Ù.
void HoParty::Main_menuSet(int menuN)
{
	InterfaceParty_KTJ.Main_menuSet(menuN);
}



//Äù½ºÆ®, µ¿·á¸Þ´º°¡ °°ÀÌºÙ¾îÀÖ¾î¼­³ÖÀ½(Äù½ºÆ®0, ¸Þ´º, µ¿·á 1)
void HoParty::InitMenuSet(int menuN)
{
	InterfaceParty_KTJ.InitMenuSet(menuN);
}


void HoParty::Init()
{
	memset(PartyMember, 0, sizeof(PartyMember));
	PartyMemberCount = 0;
	MessageBoxDrawCount = 0;
	Close();
	Load();


	//ktj 
	InterfaceParty_KTJ.Init();
}

void HoParty::Close()
{
	if(BmpLifeBlue)
	{
		BmpLifeBlue->Release();
		BmpLifeBlue = NULL;
	}

	if(BmpLifeRed)
	{
		BmpLifeRed->Release();
		BmpLifeRed = NULL;
	}

	for(int index = 0; index < 5; index++)
	{
		if(ToolTip[index] != NULL)
		{
			ToolTip[index]->Release();
			ToolTip[index] = NULL;
		}
	}

	for ( int index = 0; index < 4; index++ )
	{
		if(Button[index] != NULL)
		{
			Button[index]->Release();
			Button[index] = NULL;
		}
	}

	for ( int index = 0; index < 2; index++ )
	{
		if(BmpMessageOk[index] != NULL)
		{
			BmpMessageOk[index]->Release();
			BmpMessageOk[index] = NULL;
		}

		if(BmpMessageCancel[index] != NULL)
		{
			BmpMessageCancel[index]->Release();
			BmpMessageCancel[index] = NULL;
		}
	}

	for ( int index = 0; index < 3; index++ )
	{
		if(BmpMan[index] != NULL)
		{
			BmpMan[index]->Release();
			BmpMan[index] = NULL;
		}
	}

	//ÆùÆ® Á¦°Å
//	DeleteObject( hoFont11);
}

void HoParty::Load()
{
	MatPartyBackGround = CreateTextureMaterial( "Effect\\Party\\PartyBackGround.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	BmpLifeBlue = LoadDibSurfaceOffscreen( "Effect\\Party\\LifeBlue.bmp");
	BmpLifeRed  = LoadDibSurfaceOffscreen( "Effect\\Party\\LifeRed.bmp");
	
	char buffer[256];
	for(int index = 0; index < 5; index++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\ToolTip", index+1, ".bmp");
		ToolTip[index] = LoadDibSurfaceOffscreen(buffer);
	}
	
	for ( int index = 0; index < 5; index++ )
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\icon-", index+1, ".bmp");
		Button[index] = LoadDibSurfaceOffscreen(buffer);
	}
	
	for ( int index = 0; index < 3; index++ )
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\Man", index+1, ".bmp");
		BmpMan[index] = LoadDibSurfaceOffscreen(buffer);
	}
	

	//¸Þ½ÃÁö Ã¢°ü·Ã..			
	//////////////////////////////////////////////////////////////////////////
	MatMessageBoxBackGround = CreateTextureMaterial( "Effect\\Party\\MessageBackGround.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	for ( int index = 0; index < 2; index++ )
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\Ok", index+1, ".bmp");
		BmpMessageOk[index] = LoadDibSurfaceOffscreen(buffer);

		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\Cancel", index+1, ".bmp");
		BmpMessageCancel[index] = LoadDibSurfaceOffscreen(buffer);
	}
	
	ReadTextures();
}

extern int	WhisperPartyPlayer( char *szName );
extern int	PartyButton( int Num , int Button );

BOOL faceFlag = FALSE;
BOOL whisperFlag = FALSE;
BOOL buttonMessageFlag = FALSE;
int HoParty::Draw()
{
	/*
	if(lpD3DDevice == NULL)
		return FALSE;
	
	if(MouseButton[0] == FALSE)
	{
		faceFlag = FALSE;
		buttonMessageFlag = FALSE;
	}
	
	if(MouseDblClick == FALSE)
		whisperFlag = FALSE;
	*/
    /*
	if(PartyPosState == PARTY_START || PartyPosState == PARTY_PROCESS
		|| PartyPosState == PARTY_END)
	{
    */
		//ktj ; Áö¿ò.
		/*
		lpD3DDevice->BeginScene();
		//PartyÃ¢ Ãâ·Â.
		if(MatPartyBackGround != -1)
			dsDrawTexImage( MatPartyBackGround, BackStartPos.x, BackStartPos.y, 256, 256, 255);
		lpD3DDevice->EndScene();








		for(int index = 0; index < PartyMemberCount; index++)
		{
			//Life¸¦ Ç¥½Ã.
			if(BmpLifeBlue != NULL && BmpLifeRed != NULL)
			{
				DrawSprite(TextStartPos.x-3+14, TextStartPos.y+30*index-2+15, BmpLifeRed,  0, 0, 94, 4, 1);
				DrawSprite(TextStartPos.x-3+14, TextStartPos.y+30*index-2+15, BmpLifeBlue, 0, 0, int((94.f/100.f)*(float)PartyMember[index].Life), 4, 1);
			}
			
			if(pCursorPos.x > TextStartPos.x && pCursorPos.y > TextStartPos.y+30*index-10 &&
			   pCursorPos.x < TextStartPos.x +110 && pCursorPos.y < TextStartPos.y+30*index+18)
			{
				if(BmpMan[1] != NULL && PartyMember[index].JangFlag == FALSE)
					DrawSprite(TextStartPos.x-4, TextStartPos.y+30*index-2, BmpMan[1],  0, 0, 13, 17,1);
				
				if(BmpMan[3] != NULL && PartyMember[index].JangFlag)
					DrawSprite(TextStartPos.x-4, TextStartPos.y+30*index-2, BmpMan[2],  0, 0, 13, 17,1);
			
				//Ä³¸¯ÅÍ ¼±ÅÃ.
				if(MouseButton[0] && PartyPosState == PARTY_PROCESS)
				{
					MouseDownPartyMember = index;
					
					//¾ó±¼ Ãâ·Â ÇÔ¼ö..
					if(strlen(PartyMember[MouseDownPartyMember].Name) != 0 &&
					   strlen(PartyMember[MouseDownPartyMember].ModelName1) != 0 &&
					   strlen(PartyMember[MouseDownPartyMember].ModelName2) != 0 && faceFlag == FALSE)
					{
						if(faceFlag == FALSE)
						{
							faceFlag = TRUE;
							OpenPartyPlayer(PartyMember[MouseDownPartyMember].Name, PartyMember[MouseDownPartyMember].ModelName1, PartyMember[MouseDownPartyMember].ModelName2);
						}
					}
				}
				
				//±Í¸» º¸³»±â...
				if(MouseDblClick && whisperFlag == FALSE)
				{
					//ktj : È«¾¾°¡ ¸¸µå°Ô ÀÌ»óÇØ¼­ MouseDownPartyMember->index·Î ¹Ù²Þ.(Á¦´ë·ÎµÊ)
					
					//if(lpCurPlayer->dwObjectSerial != PartyMember[MouseDownPartyMember].ChrCode )
					//{
					//	whisperFlag = TRUE;
					//	WhisperPartyPlayer(PartyMember[MouseDownPartyMember].Name);
					//}
					if(lpCurPlayer->dwObjectSerial != PartyMember[index].ChrCode )
					{
						whisperFlag = TRUE;
						WhisperPartyPlayer(PartyMember[index].Name);
					}
				}
			}
			else
			{
				if(BmpMan[0] != NULL && PartyMember[index].JangFlag == FALSE)
					DrawSprite(TextStartPos.x-4, TextStartPos.y+30*index-2, BmpMan[0],  0, 0, 13, 17,1);
				
				if(BmpMan[3] != NULL && PartyMember[index].JangFlag)
					DrawSprite(TextStartPos.x-4, TextStartPos.y+30*index-2, BmpMan[2],  0, 0, 13, 17,1);
			}
		}
		
		if(PartyPosState == PARTY_PROCESS)
		{
			//´­¸° ¸â¹ö Ç¥½ÃÇÏ±â.
			if(MouseDownPartyMember != -1 && PartyMember[MouseDownPartyMember].JangFlag == FALSE)
				DrawSprite(TextStartPos.x-4, TextStartPos.y+30*MouseDownPartyMember-2, BmpMan[1],  0, 0, 13, 17,1);
			if(MouseDownPartyMember != -1 && PartyMember[MouseDownPartyMember].JangFlag == TRUE)
				DrawSprite(TextStartPos.x-4, TextStartPos.y+30*MouseDownPartyMember-2, BmpMan[2],  0, 0, 13, 17,1);
		}
		
		HDC hdc;
		HFONT oldFont;
		lpDDSBack->GetDC(&hdc);
		if(hFont != NULL)
			oldFont = (HFONT)SelectObject( hdc , hFont );
		
		//µÚ¿¡ ±×¸²ÀÚ..
		SetBkMode( hdc, TRANSPARENT );
		
		//LevelÀ» Âï±â..
		char levelBuffer[256];
		for(index = 0; index < PartyMemberCount; index++)
		{
			SetTextColor( hdc, RGB(0, 0, 0));
			dsTextLineOut(hdc, TextStartPos.x+11, TextStartPos.y+30*index+1, PartyMember[index].Name, lstrlen(PartyMember[index].Name));
			memset(levelBuffer, 0, sizeof(levelBuffer));

			if(PartyMember[index].Level > 10)
				wsprintf(levelBuffer, "%s%d%s", "L",PartyMember[index].Level/10,"x");
			else
				wsprintf(levelBuffer, "%s%d", "L", PartyMember[index].Level);
			dsTextLineOut(hdc, TextStartPos.x+110, TextStartPos.y+5+30*index+1, levelBuffer, lstrlen(levelBuffer));
		}
		
		
		//ÁøÂ¥ ±Û¾¾..
		SetBkMode( hdc, TRANSPARENT );
		for(index = 0; index < PartyMemberCount; index++)
		{
			if( MouseDownPartyMember != index)
				SetTextColor( hdc, RGB(209, 190, 154));		
			else
				SetTextColor( hdc, RGB(255, 150, 0));
			
			if(pCursorPos.x > TextStartPos.x && pCursorPos.y > TextStartPos.y+30*index-10 &&
			   pCursorPos.x < TextStartPos.x +110 && pCursorPos.y < TextStartPos.y+30*index+18)
				SetTextColor( hdc, RGB(255, 150, 0));
			dsTextLineOut(hdc,TextStartPos.x+10, TextStartPos.y+30*index, PartyMember[index].Name, lstrlen(PartyMember[index].Name));

			memset(levelBuffer, 0, sizeof(levelBuffer));
			
			if(PartyMember[index].Level > 10)
				wsprintf(levelBuffer, "%s%d%s", "L",PartyMember[index].Level/10,"x");
			else
				wsprintf(levelBuffer, "%s%d", "L", PartyMember[index].Level);

			SetTextColor( hdc, RGB(255, 190, 107));
			dsTextLineOut(hdc, TextStartPos.x+110, TextStartPos.y+5+30*index, levelBuffer, lstrlen(levelBuffer));
		}
		
		if(oldFont)
			SelectObject( hdc, oldFont);
		lpDDSBack->ReleaseDC(hdc);
		
		
		//ButtonÂï±â.
		for(index = 0; index < 5; index++)
		{
			if(pCursorPos.x > BackStartPos.x+114+index*22     && pCursorPos.y > BackStartPos.y+220 &&
			   pCursorPos.x < BackStartPos.x+114+20+index*22  && pCursorPos.y < BackStartPos.y+220+20)
			{
				if(lpCurPlayer->dwObjectSerial != PartyMember[0].ChrCode)
				{
					if(index == 0 || index == 1 || index == 2)
						continue;
				}
				
				if(PartyMemberCount == 0 && index != 4)
					continue;
				//Button Ç¥½Ã
				DrawSprite(BackStartPos.x+114+index*22, BackStartPos.y+222, Button[index],  0, 0, 20, 20,1);
				
				if(MouseButton[0] && PartyPosState == PARTY_PROCESS)
				{
					
					if(buttonMessageFlag == FALSE)
					{
						MouseDownButton = index;
						buttonMessageFlag = TRUE;
						//ÆÄÆ¼ ¹öÆ° º¸³»±â...
						PartyButton(MouseDownPartyMember, index);
						MouseDownPartyMember = -1;
					}
					
					//³ª°¡±â ¹öÆ°..
					if(MouseDownButton == 4)
						PartyPosState = PARTY_END;
				}
			}
		}

		//´­¸° ¹öÆ° Ç¥½ÃÇÏ±â..
		if(MouseDownButton != -1)
		{
			DrawSprite(BackStartPos.x+114+MouseDownButton*22+1, BackStartPos.y+222+1, Button[MouseDownButton],  0, 0, 20, 20,1);
			MouseDownButton = -1;
		}
		//ToolTip Ç¥½Ã.
		for(index = 0; index < 5; index++)
		{
			if(lpCurPlayer->dwObjectSerial != PartyMember[0].ChrCode )
			{
				if(index == 0 || index == 1 || index == 2)
					continue;
			}

			if(PartyMemberCount == 0)
			{
				if(index == 0 || index == 1 || index == 2 || index == 3)
					continue;
			}

			if(pCursorPos.x > BackStartPos.x+114+index*22     && pCursorPos.y > BackStartPos.y+220 &&
			   pCursorPos.x < BackStartPos.x+114+20+index*22  && pCursorPos.y < BackStartPos.y+220+20
			   && PartyPosState == PARTY_PROCESS)
			{
				//ToolTip Ç¥½Ã
				DrawSprite(BackStartPos.x+114+index*22-15, BackStartPos.y+226-28, ToolTip[index],  0, 0, 47, 27,1);
			}
		}

		*/





		//ktj ; ³ÖÀ½.
		//InterfaceParty_KTJ.Draw();
	//}
	/*
	//MessageBox Ãâ·Â½Ã..
	if(MessageBoxOpenFlag == TRUE)
	{
		static PartySpotTimer = 0;
		lpD3DDevice->BeginScene();
		//MessageÃ¢ Ãâ·Â.
		if(MatMessageBoxBackGround != -1)
			dsDrawTexImage( MatMessageBoxBackGround, MessageBoxStartPos.x, MessageBoxStartPos.y, 256, 64, 255);
			PartySpotTimer++;
		
		if(PartySpotTimer > 15)
		{
			dsDrawColorBox( RGBA_MAKE( 0,200,255,80 ), MessageBoxStartPos.x+5, MessageBoxStartPos.y+5, 160, 53 ); //±ôºýÀÎ´Ù 
			if(PartySpotTimer >30)
				PartySpotTimer = 0;
		}
		lpD3DDevice->EndScene();
		
		//Message ¹Ú½º °ü·Ã..
		////////////////////////////////////////////////////////////////////////////////////////////////
		//ok
		if(pCursorPos.x > MessageBoxStartPos.x+140     && pCursorPos.y > MessageBoxStartPos.y+11 &&
		   pCursorPos.x < MessageBoxStartPos.x+140+23  && pCursorPos.y < MessageBoxStartPos.y+11+23)
		{
			if(BmpMessageOk[1] != NULL)
				DrawSprite(MessageBoxStartPos.x+140, MessageBoxStartPos.y+11, BmpMessageOk[1],  0, 0, 23, 23,1);
			if(MouseButton[0])
			{
				SendJoinPartyUser(PartyMessageBoxChrCode);
				PartyPosState = PARTY_START;
				MessageBoxOpenFlag = FALSE;



				//ktj:...
				InitMenuSet(1);
				//PmenuN=1;


			}
		}
		else
		{
			if(BmpMessageOk[0] != NULL)
				DrawSprite(MessageBoxStartPos.x+140, MessageBoxStartPos.y+11, BmpMessageOk[0],  0, 0, 23, 23,1);
		}
		
		//Cancel
		if(pCursorPos.x > MessageBoxStartPos.x+144     && pCursorPos.y > MessageBoxStartPos.y+37 &&
		   pCursorPos.x < MessageBoxStartPos.x+144+15  && pCursorPos.y < MessageBoxStartPos.y+37+15)
		{
			if(BmpMessageCancel[0] != NULL)
				DrawSprite(MessageBoxStartPos.x+144, MessageBoxStartPos.y+37, BmpMessageCancel[1],  0, 0, 15, 15,1);
			
			if(MouseButton[0])
				MessageBoxOpenFlag = FALSE;
			
		}
		else
		{
			if(BmpMessageCancel[0] != NULL)
				DrawSprite(MessageBoxStartPos.x+144, MessageBoxStartPos.y+37, BmpMessageCancel[0],  0, 0, 15, 15,1);
		}
		
		HDC hdc;
		HFONT oldFont;
		lpDDSBack->GetDC(&hdc);
		oldFont = (HFONT)SelectObject( hdc , hFont);
		
		SetBkMode( hdc, TRANSPARENT );

		SetTextColor( hdc, RGB(255, 255, 255));
		
		dsTextLineOut(hdc, MessageBoxStartPos.x+36, MessageBoxStartPos.y+16, PartyMessageBoxChrName, lstrlen(PartyMessageBoxChrName));
		dsTextLineOut(hdc, MessageBoxStartPos.x+28, MessageBoxStartPos.y+38, HoText_PartyMessage, lstrlen(HoText_PartyMessage));
		
		
		
		if(oldFont)
			SelectObject( hdc, oldFont);
		lpDDSBack->ReleaseDC(hdc);
	}
	*/
    //DrawPartyMessage(MessageBoxStartPos.x, MessageBoxStartPos.y);
	
	if (renderDevice.IsDevice() == NULL)
		return FALSE;
	
	if(MouseButton[0] == FALSE)
	{
		faceFlag = FALSE;
		buttonMessageFlag = FALSE;
	}
	
	if(MouseDblClick == FALSE)
		whisperFlag = FALSE;

	if(PartyPosState == PARTY_START || PartyPosState == PARTY_PROCESS
		|| PartyPosState == PARTY_END)
		InterfaceParty_KTJ.Draw();

 	return TRUE;
}

void HoParty::DrawPartyMessage(int x, int y)
{
	
	//MessageBox Ãâ·Â½Ã..
	if(MessageBoxOpenFlag == TRUE)
	{
		static PartySpotTimer = 0;
		renderDevice.BeginScene();
		//MessageÃ¢ Ãâ·Â.
		if(MatMessageBoxBackGround != -1)
			dsDrawTexImage( MatMessageBoxBackGround, x, y, 256, 64, 255);
			PartySpotTimer++;
		
		if(PartySpotTimer > 15)
		{
			dsDrawColorBox( RGBA_MAKE( 0,200,255,80 ), x+5, y+5, 160, 53 ); //±ôºýÀÎ´Ù 
			if(PartySpotTimer >30)
				PartySpotTimer = 0;
		}
		renderDevice.EndScene();
		
		
		HDC hdc;
		HFONT oldFont;
		renderDevice.lpDDSBack->GetDC(&hdc);
		oldFont = (HFONT)SelectObject( hdc , hFont);
		
		SetBkMode( hdc, TRANSPARENT );

		SetTextColor( hdc, RGB(255, 255, 255));
		
		dsTextLineOut(hdc, x+36, y+16, PartyMessageBoxChrName, lstrlen(PartyMessageBoxChrName));
		dsTextLineOut(hdc, x+28, y+38, HoText_PartyMessage, lstrlen(HoText_PartyMessage));
		
		if(oldFont)
			SelectObject( hdc, oldFont);
		renderDevice.lpDDSBack->ReleaseDC(hdc);

		//Message ¹Ú½º °ü·Ã..
		////////////////////////////////////////////////////////////////////////////////////////////////
		//ok
		if(pCursorPos.x > x+140     && pCursorPos.y > y+11 &&
			pCursorPos.x < x+140+23  && pCursorPos.y < y+11+23)
		{
			if(BmpMessageOk[1] != NULL)
				DrawSprite(x+140, y+11, BmpMessageOk[1],  0, 0, 23, 23,1);
			if(MouseButton[0])
			{
				SendJoinPartyUser(PartyMessageBoxChrCode);
				PartyPosState = PARTY_START;
				MessageBoxOpenFlag = FALSE;



				//ktj:...
				InitMenuSet(1);
				//PmenuN=1;


			}
		}
		else
		{
			if(BmpMessageOk[0] != NULL)
				DrawSprite(x+140, y+11, BmpMessageOk[0],  0, 0, 23, 23,1);
		}
		
		//Cancel
		if(pCursorPos.x > x+144     && pCursorPos.y > y+37 &&
			pCursorPos.x < x+144+15  && pCursorPos.y < y+37+15)
		{
			if(BmpMessageCancel[0] != NULL)
				DrawSprite(x+144, y+37, BmpMessageCancel[1],  0, 0, 15, 15,1);
			
			if(MouseButton[0])
				MessageBoxOpenFlag = FALSE;
			
		}
		else
		{
			if(BmpMessageCancel[0] != NULL)
				DrawSprite(x+144, y+37, BmpMessageCancel[0],  0, 0, 15, 15,1);
		}
	}
}

void HoParty::MainPartyMessage(int x, int y)
{
	
}

int HoParty::Main()
{
	if(PartyPosState == PARTY_START)
	{
		BackStartPos.x-= 15;
		if(BackStartPos.x <= 549)
		{
			BackStartPos.x = 549;
			PartyPosState = PARTY_PROCESS;
		}
		TextStartPos.x = BackStartPos.x+102;
	}
	else if(PartyPosState == PARTY_END)
	{
		BackStartPos.x += 15;
		if(BackStartPos.x >= 800)
		{
			//ktj : Å¬·£ÀÇ ÈÙºÎºÐÅ¬¸®¾î
			void TJBscrollWheelClear_ChatL();
			TJBscrollWheelClear_ChatL();


			void but_exit_chk();
			but_exit_chk();

			//ret_menuN  = 0;
			//PmenuN=2;



			MouseDownPartyMember = -1;
			MouseDownButton = -1;
			BackStartPos.x = 800;
			PartyPosState = PARTY_NONE;
		}
		TextStartPos.x = BackStartPos.x+102;
	}
	

	
	if(MessageBoxOpenFlag)
	{
		MessageBoxDrawCount++;
		if(MessageBoxDrawCount > 1400)
		{
			MessageBoxOpenFlag = FALSE;
			MessageBoxDrawCount = 0;
		}
	}
	

	//ktj : »õ·Î ³ÖÀ½.
	int chk = InterfaceParty_KTJ.Main(PartyPosState );
	if(chk == PARTY_END) {

		//ktj : Å¬·£ÀÇ ÈÙºÎºÐÅ¬¸®¾î
		void TJBscrollWheelClear_ChatL();
		TJBscrollWheelClear_ChatL();

		PartyPosState = PARTY_END;		//³»°¡¸¸µçÀÎÅÍÆäÀÌ½º¿¡¼­ ³¡³»´Â°Å¸é ³ª°¡µµ·ÏÇÑ´Ù.
	}



	return TRUE;
}

//ktj : ÁÖÀÇ : ÀÌÇÔ¼ö´Â »ç¿ë¾ÈÇÔ.
int HoParty::AddMember(char *memberName,DWORD chrCode, int life, int level)
{

	//ktj: »õ·Î³Ö¾úÀ½(ÀÌÇÔ¼ö¸¦ ¾îµð¼­ºÎ¸£´ÂÁö ¸ô¶ó¼­ ±×³É ¿©±â´Ù ³Ö¾ú´Ù)
	InterfaceParty_KTJ.AddMember(memberName, chrCode,  life,  level);


	if(memberName == NULL) 
		return FALSE;
	
	if(PartyMemberCount >= MAX_PARTY_MEMBER)
		return FALSE;
	memcpy(PartyMember[PartyMemberCount].Name, memberName, strlen(memberName));
	PartyMember[PartyMemberCount].ChrCode = chrCode;
	PartyMember[PartyMemberCount].Life = life;
	PartyMember[PartyMemberCount].Level = 100;
	PartyMemberCount++;
	return TRUE;
}



//ktj : »õ·Î ¸¸µê. ============== start
//ÆÄÆ¼¿ë
int HoParty::AddMember(hoPartyMember *member,int cnt)
{
	//ktj : ÀÓ½Ã
	InterfaceParty_KTJ.AddMember(member,cnt);
	
	//ktj : Áö¿ò.
	
	PartyMember[cnt].ChrCode = member->ChrCode;
	PartyMember[cnt].Life  = member->Life;
	PartyMember[cnt].Level = member->Level;
	PartyMember[cnt].CharacterPos.x = member->CharacterPos.x;
	PartyMember[cnt].CharacterPos.z = member->CharacterPos.z;
	PartyMember[cnt].CharacterPos.y = member->CharacterPos.y;
	lstrcpy( PartyMember[cnt].Name , member->Name );
	lstrcpy( PartyMember[cnt].ModelName1 , member->ModelName1 );
	lstrcpy( PartyMember[cnt].ModelName2 , member->ModelName2 );
	PartyMember[cnt].JangFlag = member->JangFlag ;
	
				
	return TRUE;
}
//ÆÄÆ¼¿ë
void HoParty::AddMember_memberSu(int memberSu)
{
	//ktj : ÀÓ½Ã
	InterfaceParty_KTJ.AddMember_memberSu(memberSu);


	//ktj : Áö¿ò.
	
    PartyMemberCount = memberSu;
	
}
//ÆÄÆ¼¿ë
int HoParty::PARTY_PLAYUPDATE(hoPartyMember *member,int cnt)
{
	//ktj : ÀÓ½Ã
	InterfaceParty_KTJ.PARTY_PLAYUPDATE(member,cnt);


	//ktj : Áö¿ò.
	
	if ( PartyMember[cnt].ChrCode==member->ChrCode) {
		PartyMember[cnt].Life  = member->Life;
		PartyMember[cnt].Level = member->Level;
		PartyMember[cnt].CharacterPos.x = member->CharacterPos.x;
		PartyMember[cnt].CharacterPos.z = member->CharacterPos.z;
		return 1;
	}
	
	return 0;
}


void HoParty::PARTY_RELEASE()
{
	//ktj : ÀÓ½Ã
	int chk = 
		InterfaceParty_KTJ.PARTY_RELEASE();


	
	PartyMemberCount = 0;
	MouseDownPartyMember = -1;


	if(chk == 0) return;

	PartyPosState = PARTY_END;
	
}
//ktj : »õ·Î ¸¸µê. ============== end



































/*==================================================================================
//
// ktj  : »õ·Î ¸¸µç°Í.													start
//
==================================================================================*/
int chkMenu(int x, int y, RECT *r) 
{
	if(r->left <= x   &&   x<= r->right ) 
	{
		if(r->top <= y   &&   y<= r->bottom ) 
			return 1;
	}
	return 0;
}




#define PARTY_BINFOsu 22
DIRECTDRAWSURFACE				binfo_Bmp[PARTY_BINFOsu];
#define PARTY_BUTTONsu 54
DIRECTDRAWSURFACE				butt_Bmp[PARTY_BUTTONsu];


//¸Þ´ºÀÇ l, t, r, bÀÓ.
HoParty_KTJ::HoParty_KTJ()
{
	//ktj :
	BackStartPos.x = 800;
	BackStartPos.y = 155;


	xLeft = BackStartPos.x-100;		//ktj : left,right½ºÅ©·Ñ¾Ö´Ï¸¦ À§ÇØ ¼³Á¤.
	xRight= BackStartPos.x;


	questSelN = 5;					//Äù½ºÆ® ¸Þ´º¹øÈ£(5:ÁøÇà 6:³¡)


	PmenuN=0;	//ÆÄÆ¼¸Þ´º¹øÈ£(0:Äù½ºÆ®, 1:µ¿·á, 2:Ä£±¸)
	savePmenuN = 0;
	//PmenuN=1;	//ÆÄÆ¼¸Þ´º¹øÈ£(0:Äù½ºÆ®, 1:µ¿·á, 2:Ä£±¸)

	cN_MenuN = 0;	//Ä£±¸¸Þ´ºÁß 0: ÃÖ±Ù¸ñ·Ï 1: Ä£±¸µé¸ñ·Ï 2:°ÅºÎÀÚ¸ñ·Ï
	cN_Pressf = 0;
	cN_PressfDBL = 0;	//´õºíÅ¬¸¯´©¸¥°Å
	cN_PressfDBL_Where = 0;



	
	MessageBoxDrawCount = 0;
	//BackStartPos.x = 800;
	//BackStartPos.y = 155;
	
	//TextStartPos.x = BackStartPos.x+102;
	//TextStartPos.y = BackStartPos.y+38;
	
	BmpLifeBlue = NULL;
	BmpLifeRed  = NULL;

	for(int index = 0; index < 5; index++)
	{
		ToolTip[index] = NULL;
		Button[index] = NULL;
	}

	for ( int index = 0; index < 3; index++ )
		BmpMan[index] = NULL;
	
	//MessageBox¿ë..
	MessageBoxStartPos.x = 513;
	MessageBoxStartPos.y = 3;
	MatMessageBoxBackGround = -1;
	
	for ( int index = 0; index < 2; index++ )
	{
		BmpMessageOk[index] = NULL;
		BmpMessageCancel[index] = NULL;
	}

	MouseDownPartyMember = -1;
	MouseDownButton = -1;
	memset(PartyMember, 0, sizeof(PartyMember));
	PartyMemberCount = 0;
	MatMessageBoxBackGround = -1;

	MessageBoxOpenFlag = FALSE;
	PartyPosState = PARTY_NONE;



	ZeroMemory(binfo_Bmp, sizeof(binfo_Bmp) );
	ZeroMemory(butt_Bmp, sizeof(butt_Bmp) );

	/*
	//ktj : »èÁ¦
#ifdef _LANGUAGE_JAPANESE
	hoFont11 = 	CreateFont( 8,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
						SHIFTJIS_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
						"MS GOTHIC" );
#endif

	
#ifdef _LANGUAGE_CHINESE

	hoFont11 = 	CreateFont( 8,
                        0,
                        0,
                        0,
			FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
						GB2312_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
						"SimSun" );

#endif

#ifdef _LANGUAGE_KOREAN
	hoFont11 = 	CreateFont( 4,
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

#endif
	*/
}


HoParty_KTJ::~HoParty_KTJ()
{
	Close();
}

void HoParty_KTJ::InitMenuSet(int menuN)
{
	if(menuN==1) {
		if(savePmenuN ==0) {
			PmenuN = menuN;
			savePmenuN = PmenuN ;
		}
		else {
			PmenuN = savePmenuN ;
		}
	}
	else {
		PmenuN = menuN;
	}
}


	











//========================= Äù½ºÆ® ¸Þ´º °ü·Ã µ¥ÀÌÅ¸ ¼ÂÆÃ ============================= start

void HoParty_KTJ::quest_Progress_Clear()
{
	ZeroMemory(qNameb, sizeof(qNameb));
	ZeroMemory(qFnameb, sizeof(qFnameb));
	qNameProgress_SU = 0;
}

void HoParty_KTJ::quest_End_Clear()
{
	
	ZeroMemory(qNameb_E, sizeof(qNameb_E));
	ZeroMemory(qFnameb_E, sizeof(qFnameb_E));
	qNameEnd_SU = 0;
}


void HoParty_KTJ::quest_Progress_Set(char *q_name, char *f_name)
{
	strcpy(qNameb[  qNameProgress_SU  ], q_name);
	strcpy(qFnameb[  qNameProgress_SU  ], f_name);

	qNameProgress_SU++;
}

void HoParty_KTJ::quest_End_Set(char *q_name, char *f_name)
{
	strcpy(qNameb_E[  qNameEnd_SU  ], q_name);
	strcpy(qFnameb_E[  qNameEnd_SU  ], f_name);
	qNameEnd_SU++;
}


//Äù½ºÆ®ÀÇ ÇÛÇÁÃ¢ ´Ý±â
void HoParty_KTJ::qN_Pressf_CLEAR()
{
	extern int qN_Pressf;	//Äù½ºÆ®ÀÌ¸§ÀÇ ´©¸§Ç¥½Ã(8~12±îÁö·Î Á¤ÇØÁü)
	extern int QuestnotCharMove, QuestnotCharMove2;	//¸Þ´ºÆÇ¾ÈÀÇ ¸¶¿ì½ºÀÇ ¿òÁ÷ÀÓ¿¡ Ä³¸¯ÅÍ°¡ ¿µÇâ¾øµµ·Ï ÇÑ´Ù.
	qN_Pressf = 0;
	QuestnotCharMove = 0;
	QuestnotCharMove2 = 0;
	
}


//Äù½ºÆ®ÀÇ ÁøÇà ¹öÆ° ´©¸¥°ÍÃ³·³ÇÏ±â
void HoParty_KTJ::quest_Sel_Progress()
{
	questSelN = 5;
}

//========================= Äù½ºÆ® ¸Þ´º °ü·Ã µ¥ÀÌÅ¸ ¼ÂÆÃ ============================= end







//========================= µ¿·á->Ä£±¸ ¸Þ´º °ü·Ã µ¥ÀÌÅ¸ ¼ÂÆÃ ============================= start
int HoParty_KTJ::chatbuild_INIfiles()	//µ¿·á->Ä£±¸
{
	HANDLE hFile;
    DWORD dwAcess =0;

	char fname[64];
	//wsprintf(fname, ".\\savedata\\%s.ini", UserAccount );//
	//¼­¹öÀÌ¸§°ú, id°¡ Á¶ÇÕµÇ³ª¿Â´Ù.

	if(szConnServerName[0] == 0)
		wsprintf(fname, ".\\savedata\\%s.ini", UserAccount );
	else 
		wsprintf(fname, ".\\savedata\\%s\\%s.ini", szConnServerName, UserAccount );


	hFile = CreateFile( fname,
				GENERIC_READ , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );

	if( hFile != INVALID_HANDLE_VALUE ) {		//ÆÄÀÏÀÌ Á¸ÀçÇÏ¹Ç·Î ³»¹ö·Á µÐ´Ù.
        CloseHandle( hFile );
		return 1;
	}



	CreateDirectory(".\\savedata", 0);
	char buf[128];

	if(szConnServerName[0] != 0) {		//¼­¹öÀÌ¸§ÀÇ savedataµð·ºÅä¸®¾È¿¡  ¸¸µç´Ù.
		wsprintf(buf,".\\savedata\\%s", szConnServerName);
		CreateDirectory(buf, 0);
	}


	char inidata0[] = "[FRIEND]\r\n";//ID00=\r\nID01=\r\nID02=\r\nID03=\r\nID04=\r\nID05=\r\nID06=\r\nID07=\r\nID08=\r\nID09=\r\nID10=\r\nID11=\r\nID12=\r\nID13=\r\nID14=\r\nID15=\r\nID16=\r\n\r\n";
	char inidata1[] = "[DENY]\r\n";//ID00=\r\nID01=\r\nID02=\r\nID03=\r\nID04=\r\nID05=\r\nID06=\r\nID07=\r\nID08=\r\nID09=\r\nID10=\r\nID11=\r\nID12=\r\nID13=\r\nID14=\r\nID15=\r\nID16=\r\n\r\n";
	char inidata2[10];


	hFile = CreateFile( fname,
				GENERIC_WRITE , FILE_SHARE_READ|FILE_SHARE_WRITE, 
				NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL , NULL );

	int chk = WriteFile( hFile , inidata0, lstrlen(inidata0) , &dwAcess , NULL );
	for(int i=0; i<(100+1); i++) {
		wsprintf( inidata2, "ID%0.2d=\r\n", i);
		WriteFile( hFile , inidata2, lstrlen(inidata2) , &dwAcess , NULL );
	}

	chk = WriteFile( hFile , inidata1, lstrlen(inidata1) , &dwAcess , NULL );	
	for(int i=0; i<(100+1); i++) {
		wsprintf( inidata2, "ID%0.2d=\r\n", i);
		WriteFile( hFile , inidata2, lstrlen(inidata2) , &dwAcess , NULL );
	}

	CloseHandle( hFile );
	return chk ;		//ÆÄÀÏ¾øÀ½.
}




void HoParty_KTJ::chatINI_read()
{
	//ktj : ÀÓ½ÃÀÓ Áö¿ï°Í.
	//chatbuild_INIfiles();

	char fname[64];
	//wsprintf(fname, ".\\savedata\\%s\\%s.ini", szConnServerName, UserAccount );
	if(szConnServerName[0] == 0)
		wsprintf(fname, ".\\savedata\\%s.ini", UserAccount );
	else 
		wsprintf(fname, ".\\savedata\\%s\\%s.ini", szConnServerName, UserAccount );



	int i, chk;
	char buf[64];
	//ktj :  µ¿·á->Ä£±¸ ¸Þ´ºÀÇ ini¼ÂÆÃÀÐÀ½.  
	ZeroMemory((void*)fNameb, sizeof(fNameb));
	i=0;
	fNameSu = i;
	while(1) {
		wsprintf(buf,"ID%0.2d", i);
		chk = read_INI(		//chating.ini µ¥ÀÌÅ¸¸¦ °¡Á®¿Â´Ù.
			//".\\image\\party\\party_DATA\\chating.ini", 
			fname,
			"FRIEND", buf, fNameb[i]);
		if(chk==0) break;
		i++;
	}

	//ÀÓ½Ã·Î ÇÑ´Ù.
	fNameS = 0;
	fNameE = 7;		//Ã¤ÆÃidÀÇ È­¸é»ó¿¡ ³ª¿Ã ¸ÇÀ§ÂÊ°ú ¸Ç¾Æ·¡ÂÊ 
	fNameSu = i;

	ZeroMemory((void*)dNameb, sizeof(dNameb));
	i=0;
	while(1) {
		wsprintf(buf,"ID%0.2d", i); 
		chk = read_INI(		//chating.ini µ¥ÀÌÅ¸¸¦ °¡Á®¿Â´Ù.
			//".\\image\\party\\party_DATA\\chating.ini", 
			fname,
			"DENY", buf, dNameb[i]);
		if(chk==0) break;
		i++;
	}

	//ÀÓ½Ã·Î ÇÑ´Ù.
	dNameS= 0;
	dNameE = 7;		//Ã¤ÆÃidÀÇ È­¸é»ó¿¡ ³ª¿Ã ¸ÇÀ§ÂÊ°ú ¸Ç¾Æ·¡ÂÊ 
	dNameSu = i;
}




//chatSave : 12, 13, 14, 15
int save_INI(char *iniF, char *optStr1, char *optStr, char *rStr, int value);

void HoParty_KTJ::chatINI_save(int menuN)
{

	char fname[64];
	//wsprintf(fname, ".\\savedata\\%s.ini", UserAccount );
	//wsprintf(fname, ".\\savedata\\%s\\%s.ini", szConnServerName, UserAccount );
	if(szConnServerName[0] == 0)
		wsprintf(fname, ".\\savedata\\%s.ini", UserAccount );
	else 
		wsprintf(fname, ".\\savedata\\%s\\%s.ini", szConnServerName, UserAccount );



	int i;
	char buf[64];

	switch(menuN) {
	case 0:				//ÃÖ±Ù¸ñ·ÏÀº ±³Ã¼ ¾ÈÇÔ.
		return;
	case 1:				//1: Ä£±¸µé¸ñ·Ï 
		for(i=0; i<100; i++) {
			wsprintf(buf,"ID%0.2d", i);
			save_INI(	//".\\image\\party\\party_DATA\\chating.ini", 
						fname,
						"FRIEND", buf, fNameb[i], 0);
		}
		return;

	case 2:				//°ÅºÎ¸ñ·Ï
		for(i=0; i<100; i++) {
			wsprintf(buf,"ID%0.2d", i); 
			save_INI(	//".\\image\\party\\party_DATA\\chating.ini", 
						fname,
						"DENY", buf, dNameb[i], 0);
		}
		return;
	}
}

void HoParty_KTJ::chatDATA_Insert(int menuN, char *str)
{
	int i, cnt;
	int l;
	
	switch(menuN) {
	case 0:				//ÃÖ±Ù¸ñ·ÏÀº ±³Ã¼ ¾ÈÇÔ.
		return;
	case 1:				//1: Ä£±¸µé¸ñ·Ï 
		l = strlen(str);
		for(i=0; i<100; i++) {
			if( l == strlen(fNameb[i])  &&   (   strcmp(str, fNameb[i]) == 0   )) 
			{
				return;		//°°Àº°Ô ÀÖ½¿.
			}
		}

		cnt=0;
		for(i=0; i<100; i++) {
			if(fNameb[i][0] == 0) {
				wsprintf(fNameb[i],"%s", str);	//ºó°÷¿¡ ¶§·Á³Ö´Â´Ù.
				cnt++;
				break;
			}
			cnt++;
		}
		fNameSu = cnt;
		return;
	case 2:			//°ÅºÎ¸ñ·Ï

		l = strlen(str);
		for(i=0; i<100; i++) {
			if( l == strlen(dNameb[i])  &&   (   strcmp(str, dNameb[i]) == 0   )) 
			{
				return;		//°°Àº°Ô ÀÖ½¿.
			}
		}



		cnt=0;
		for(i=0; i<100; i++) {
			if(dNameb[i][0] == 0) {
				wsprintf(dNameb[i],"%s", str);	//ºó°÷¿¡ ¶§·Á³Ö´Â´Ù.
				cnt++;
				break;
			}
			cnt++;
		}
		dNameSu = cnt;
		return;
	}
}


//iniÀÇ µ¥ÀÌÅ¸ Áö¿ï¶§ »ç¿ë
void HoParty_KTJ::chatDATA_delete(int menuN, int num)
{
	int i, cnt;
	switch(menuN) {
	case 0:
		for(i=num; i<7; i++) {
			strncpy(latestb[i], latestb[i+1], sizeof(latestb[i]));
			latestb_LOG[i] = latestb_LOG[i+1];
		}
		break;
	case 1:
		for(i=num; i<100; i++) {
			strncpy(fNameb[i], fNameb[i+1], sizeof(fNameb[i]));
			fName_LOG[i] = fName_LOG[i+1];
		}

		cnt=0;
		for(i=0; i<100; i++) {						//°¹¼ö´Ù½Ã¾Ë¾Æ³¿
			if(fNameb[i][0] == 0) {
				//cnt++;
				break;
			}
			cnt++;
		}
		fNameSu = cnt;


		if(fNameS &&  fNameb[fNameS][0]==0) {	//½ÃÀÛ¹øÈ£³¡¹øÈ£¸¦ ´Ù½Ã ¾Ë¾Æ³¿
			fNameS-=7;
			fNameE=fNameS+7;
		}
		break;



	case 2:
		for(i=num; i<100; i++) {
			strncpy(dNameb[i], dNameb[i+1], sizeof(dNameb[i]));
			dName_LOG[i] = dName_LOG[i+1];
		}

		cnt=0;										//°¹¼ö´Ù½Ã¾Ë¾Æ³¿
		for(i=0; i<100; i++) {
			if(dNameb[i][0] == 0) {
				//cnt++;
				break;
			}
			cnt++;
		}
		dNameSu = cnt;

		if(dNameS &&  dNameb[dNameS][0]==0) {		//½ÃÀÛ¹øÈ£³¡¹øÈ£¸¦ ´Ù½Ã ¾Ë¾Æ³¿
			dNameS-=7;
			dNameE=dNameS+7;
		}
		break;
	}

}




//Ä£±¸ ¸Þ´ºÀÇ ÃÖ±Ù¸ñ·Ï insertÇÑ´Ù.
void HoParty_KTJ::latest_Insert(char *namestr)
{
	int i;


	//°°Àº°Ô ÀÖÀ¸¸é ±×°ÍÀ» »èÁ¦ÇÑ´Ù.
	for(i=0; i<7; i++) {
		if(latestb[i][0] != 0) {
			if( strcmp(latestb[i], namestr ) == 0 ) {
				if( strlen(latestb[i]) ==  strlen(namestr)) {
					chatDATA_delete(0, i);				//ÃÖ±Ù¸ñ·ÏÁß¿¡¼­ ÀÌµ¿µÈ ¸ñ·ÏÀº »èÁ¦ÇÔ.
					break;
				}
			}
		}
	}



	for(i=6; i>=1;i--) {
		ZeroMemory( latestb[i], sizeof(latestb[i]) );
		strcpy(latestb[i], latestb[i-1] );
	}
	strcpy(latestb[0], namestr);	//¸ÇÀ§¿¡´Ù¼³Á¤

}





//µ¿·á->Ä£±¸    idÀÇ ÀÌÀü,´ÙÀ½ ¸®½ºÆ®¸¦ º¸¿©ÁÜ.
void HoParty_KTJ::chat_PageChange(int sw)
{
	switch(cN_MenuN) {
	case 0:				//ÃÖ±Ù¸ñ·ÏÀº ±³Ã¼ ¾ÈÇÔ.
		break;
	case 1:				//1: Ä£±¸µé¸ñ·Ï 
		if(sw==0) {
			fNameS -= 7;
			if(fNameS <0)fNameS =0;
			fNameE = fNameS +7;
			if(fNameE  > 100) fNameE  = 100;
			return;
		}
		fNameS += 7;
		if(fNameb[ fNameS ][0]==0) fNameS -= 7;
		fNameE = fNameS + 7;
		if(fNameE  > 100) fNameE  = 100;
		break;
	case 2:				//2:°ÅºÎÀÚ¸ñ·Ï
		if(sw==0) {
			dNameS -= 7;
			if(dNameS <0)dNameS =0;
			dNameE = dNameS +7;

			if(dNameE > 100) dNameE = 100;
			return;
		}
		dNameS += 7;
		if(dNameb[ dNameS ][0]==0) dNameS -= 7;
		dNameE = dNameS + 7;
		if(dNameE > 100) dNameE = 100;

		break;
	}
}

//µ¿·á->Ä£±¸    id »èÁ¦½Ã ÇÊ¿äÇÔ.
void HoParty_KTJ::chat_IDdelete()
{
	int i;
	switch(cN_MenuN) {
	case 0:				//ÃÖ±Ù¸ñ·ÏÀº ±³Ã¼ ¾ÈÇÔ.
		break;
	case 1:				//1: Ä£±¸µé¸ñ·Ï 
		if(cN_Pressf==0) return;		//¼±ÅÃ¾ÈµÆÀ½.
		i = cN_Pressf-3;
		i += fNameS;

		chatDATA_delete(cN_MenuN, i);
		chatINI_save(cN_MenuN);
		break;
	case 2:				//2:°ÅºÎÀÚ¸ñ·Ï
		if(cN_Pressf==0) return;
		i = cN_Pressf-3;
		i += dNameS;

		chatDATA_delete(cN_MenuN, i);
		chatINI_save(cN_MenuN);

		break;
	}
}


//µ¿·á->Ä£±¸->ÃÖ±Ù¸ñ·Ï->Ä£±¸µî·Ï¹öÆ°, °ÅºÎµî·Ï¹öÆ°´­·ÈÀ»½Ã¿¡ »ç¿ë
void HoParty_KTJ::chat_IDinsert(int sw, char *id)
{
	int i;
	//

	if(sw==1)	{							//1: Ä£±¸µé¸ñ·Ï¿¡ µî·ÏÇÏ±â
		if(cN_MenuN != 0) return;			//¸Þ´º°¡ ÃÖ±Ù¸ñ·ÏÀÏ¶§¸¸ »ç¿ëµÊ

		if(cN_Pressf==0) return;			//¼±ÅÃ¾ÈµÆÀ½.
		i = cN_Pressf-3;
		
		chatDATA_Insert(1, latestb[i]);		//ÃÖ±Ù¸ñ·Ï¿¡¼­ °ÅºÎÀÚ¸ñ·ÏÀ¸·Î ¿Å±ä´Ù.
		chatINI_save(1);					//°ÅºÎÀÚ¸ñ·Ï ¼¼ÀÌºê

		chatDATA_delete(0, i);				//ÃÖ±Ù¸ñ·ÏÁß¿¡¼­ ÀÌµ¿µÈ ¸ñ·ÏÀº »èÁ¦ÇÔ.
		return;
	}

	if(sw==2)	{							//2: Ä£±¸µé¸ñ·Ï¿¡ µî·ÏÇÏ±â
		if(cN_MenuN != 0) return;			//¸Þ´º°¡ ÃÖ±Ù¸ñ·ÏÀÏ¶§¸¸ »ç¿ëµÊ

		if(cN_Pressf==0) return;
		i = cN_Pressf-3;

		chatDATA_Insert(2, latestb[i]);		//ÃÖ±Ù¸ñ·Ï¿¡¼­ °ÅºÎÀÚ¸ñ·ÏÀ¸·Î ¿Å±ä´Ù.
		chatINI_save(2);					//°ÅºÎÀÚ¸ñ·Ï ¼¼ÀÌºê

		chatDATA_delete(0, i);				//ÃÖ±Ù¸ñ·ÏÁß¿¡¼­ ÀÌµ¿µÈ ¸ñ·ÏÀº »èÁ¦ÇÔ.
	}



	//ÀÌºÎºÐÀº ¼­¹ö¿¡¼­ Á÷Á¢ Ä£±¸¸ñ·ÏÀ¸·Î id¸¦ ³ÖÀ»¶§ »ç¿ëÇÔ.
	if(sw==3) {
		chatDATA_Insert(1, id);		//ÃÖ±Ù¸ñ·Ï¿¡¼­ °ÅºÎÀÚ¸ñ·ÏÀ¸·Î ¿Å±ä´Ù.
		chatINI_save(1);					//°ÅºÎÀÚ¸ñ·Ï ¼¼ÀÌºê
		return;
	}

}







//·Î±äµÇÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ ¾Ë¾Æ³¿.
void HoParty_KTJ::chat_isLOG(char *name, int flag)
{
	int i;
	int len = strlen(name);
	for(i=0; i<100; i++) {
		if( ( len == strlen(fNameb[i]) ) || 
			( strcmp(name, fNameb[i])==0 ) 
			 ) 
		{
			fName_LOG[i] = flag;		//on offµÉ¼öÀÖÀ½.
			return;
		}
	}


	for(i=0; i<100; i++) {
		if( ( len == strlen(dNameb[i]) ) || 
			( strcmp(name, dNameb[i])==0 ) 
			 ) 
		{
			dName_LOG[i] = flag;
			return;
		}
	}
}



//cN_Pressf ´­¸°¹øÈ£ ¼ÂÆÃ(ºó ºÎºÐÀº ¼ÂÆÃÀÌ ¾ÈµÇ±â ¶§¹®ÀÓ
void HoParty_KTJ::chat_cN_Pressf(int press)	
{
	switch(cN_MenuN) {
	case 0:				//ÃÖ±Ù¸ñ·ÏÀº ±³Ã¼ ¾ÈÇÔ.
		press -= 3;
		if(latestb[ press ][0] == 0) {
			cN_Pressf = 0;
			return;
		}

		cN_Pressf = press + 3;
		break;

	case 1:				//1: Ä£±¸µé¸ñ·Ï 
		press = press-3;
		press += fNameS;

		if(fNameb[ press ][0] == 0) {
			cN_Pressf = 0;
			return;
		}
		cN_Pressf = (press-fNameS) + 3;
		break;
	case 2:				//2:°ÅºÎÀÚ¸ñ·Ï
		press = press-3;
		press += dNameS;

		if(dNameb[ press ][0] == 0) {
			cN_Pressf = 0;
			return;
		}

		cN_Pressf = (press-dNameS) + 3;
		break;
	}
}



//id¸¦ Ã£¾Æ³» º¸³»ÁØ´Ù.
int HoParty_KTJ::chat_IDs(int dataN, int cnt, char *id)
{
	switch(dataN) {
	case 0:				//ÃÖ±Ù¸ñ·Ï¿¡¼­ id¸¦ ³Ñ±ä´Ù.
		if(cnt>6) return 0;
		
		if(latestb[ cnt ][0] == 0) {
			return 0;
		}
		strcpy(id, latestb[ cnt ]);
		break;

	case 1:				//1: Ä£±¸µé¸ñ·Ï 
		if(cnt>(100-1)) return 0;
		
		if(fNameb[ cnt ][0] == 0) {
			return 0;
		}
		strcpy(id, fNameb[ cnt ]);
		
		break;
	case 2:				//2:°ÅºÎÀÚ¸ñ·Ï
		if(cnt>(100-1)) return 0;
		
		if(dNameb[ cnt ][0] == 0) {
			return 0;
		}
		strcpy(id, dNameb[ cnt ]);

		break;
	}

	return 1;
}




//µ¿·á->Ä£±¸->ÃÖ±Ù¸ñ·Ï,Ä£±¸¸ñ·Ï¿¡¼­ ´õºíÅ¬¸¯½Ã ±Ó¸»ÇÑ´Ù.
void HoParty_KTJ::chat_WhisperPartyPlayer(int num)
{
	int i;
	switch(cN_MenuN) {
	case 0:				//ÃÖ±Ù¸ñ·Ï¿¡¼­ id¸¦ ³Ñ±ä´Ù.
		cN_PressfDBL_Where = 0;


		if(num==-1) {
			if(cN_PressfDBL == cN_Pressf) {
				cN_PressfDBL = 0;	//ÀÌ¹ÌµÇÀÖÀ¸¸é Å¬¸®¾î½ÃÅ´.
				break;
			}
			cN_PressfDBL = cN_Pressf;
			cN_Pressf = 0;

			i = cN_PressfDBL - 3;
		}
		else {
			if(cN_Pressf != num){	//ÀÌ¹Ì ¼±ÅÃµÈ°Í¸¸ ±Ó¸»ÀÌ µÇ¾îÁ®¾ßÇÔ.
				cN_Pressf = num;
				return;
			}
			cN_PressfDBL = num;
			i = cN_PressfDBL - 3;
		}

		
		
		WhisperPartyPlayer( latestb[ i ] );
		break;

	case 1:				//1: Ä£±¸µé¸ñ·Ï 

		if(num==-1) {

			if(cN_PressfDBL == ( cN_Pressf+fNameS)  ) {
				cN_PressfDBL = 0;	//ÀÌ¹ÌµÇÀÖÀ¸¸é Å¬¸®¾î½ÃÅ´.
				cN_PressfDBL_Where = 0;
				break;
			}
			i = cN_Pressf - 3;
			i += fNameS;
			cN_Pressf = 0;
		}
		else {
			if(cN_Pressf != num){	//ÀÌ¹Ì ¼±ÅÃµÈ°Í¸¸ ±Ó¸»ÀÌ µÇ¾îÁ®¾ßÇÔ.

				cN_Pressf = num;
				return;
			}
			i = num - 3;
			i += fNameS;
		}

		
		WhisperPartyPlayer( fNameb[ i ] );
		cN_PressfDBL_Where = 1;
		cN_PressfDBL = i+3;			//ÁÖÀÇ cN_PressfDBL ´ÂfNameS°¡ Æ÷ÇÔµÊ
		break;

	case 2:				//2:°ÅºÎÀÚ¸ñ·Ï Àº ±Ó¸»¾ÈÇÑ´Ù.
		break;
	}
}

//±Ó¸»º¸³»±â ¿£ÅÍÄ£ÈÄ ºÎ¸¥´Ù.
void HoParty_KTJ::chat_WhisperPartyPlayer_close()
{
	cN_PressfDBL =0;
}




//0:Ä£±¸->ÃÖ±Ù¸ñ·Ï, 1:Ä£±¸->Ä£±¸¸ñ·Ï, 2:Ä£±¸->°ÅºÎÀÚ¸ñ·ÏÀÇ ¸Þ´º¸¦ ¹Ù²Þ.
void HoParty_KTJ::chat_changeMENU(int sw)
{
	cN_MenuN = sw;		//0:Ä£±¸->ÃÖ±Ù¸ñ·Ï, 1:Ä£±¸->Ä£±¸¸ñ·Ï, 2:Ä£±¸->°ÅºÎÀÚ¸ñ·Ï
}

//========================= µ¿·á->Ä£±¸ ¸Þ´º °ü·Ã µ¥ÀÌÅ¸ ¼ÂÆÃ ============================= end






















//ÆÄÆ¼¸Þ´º¹øÈ£(0:Äù½ºÆ®, 1:µ¿·á, 2:Ã¤ÆÃ)¿¡ µû¶ó ´Ù¸¥¼ÂÆÃÀÌ µÇ¾ßÇÔ.
void HoParty_KTJ::menuSet(int sw)
{
	int i;
	int menuButPosx;
	int menuButPosy;
	int qNamePosx;
	int qNamePosy;

	if(sw==3) {
		//fd2("¸Þ´º¼Â3¹øÀÌ¿ë");
		void CLANmenu_ChatList(int sw);	//netplay.cpp¿¡¼­ »ç¿ëÇÔ.l
		CLANmenu_ChatList(1);
		return ;
	}

	//ktj : Å¬·£¿øÀÇ À§Ä¡ ÆÄ¾ÇÇØ¾ßÇÔ¿¡ ÁÖÀÇ
	int isClanWon = 0;
	
	//Å¬·£¿øÀÌ°Å³ª ¯…ÀÌ°Å³ª ºÎÅ¬·£¯…ÀÇ °æ¿ì

#ifdef  __CLANSUBCHIP__
	if(cldata.myPosition==100 || cldata.myPosition==101 || cldata.myPosition==104) {
#else
	if(cldata.myPosition==100 || cldata.myPosition==101 ) {
#endif
		isClanWon = 1;
	}

	if(sw==0) {		//Äù½ºÆ®Ã¢Àº µû·Î ¿­¸².

		//ktj : ÀÓ½Ã
		chat_WhisperPartyPlayer_close();

		void chatlistSPEAKERflagChg(int flag);		//cE_chatlist.cpp¿¡ Á¤ÀÇ
		chatlistSPEAKERflagChg(0);


		menuPos[0].left  = BackStartPos.x+140;
		menuPos[0].top   = (BackStartPos.y-8)+10;
		menuPos[0].right = BackStartPos.x+(140+105);	
		menuPos[0].bottom= (BackStartPos.y-8)+30;

		menuPos[1].left  = -1;		//µ¿·á, Ã¤ÆÃÃ¢ »ç¿ë¾ÈÇÔ.
		menuPos[1].top   = -1;
		menuPos[1].right = -1;
		menuPos[1].bottom= -1;	
		menuPos[2].left  = -1;
		menuPos[2].top   = -1;
		menuPos[2].right = -1;
		menuPos[2].bottom= -1;
	}
	else {			//µ¿·á, Ã¤ÆÃÃ¢ÀÌ ÇÔ²² ¿­¸²

		//ktj : ÀÓ½Ã
		chat_WhisperPartyPlayer_close();

		void chatlistSPEAKERflagChg(int flag);		//cE_chatlist.cpp¿¡ Á¤ÀÇ
		chatlistSPEAKERflagChg(0);


		menuPos[0].left  = -1;	//left		//Äù½ºÆ®Ã¢ »ç¿ë¾ÈÇÔ.
		menuPos[0].top   = -1;	//top
		menuPos[0].right = -1;	//right
		menuPos[0].bottom= -1;	//bottom

		/*
		menuPos[1].left  = BackStartPos.x+90;
		menuPos[1].top   = (BackStartPos.y-8)+10;
		menuPos[1].right = BackStartPos.x+160;	
		menuPos[1].bottom= (BackStartPos.y-8)+30;	
		menuPos[2].left  = BackStartPos.x+170;
		menuPos[2].top   = (BackStartPos.y-8)+10;
		menuPos[2].right = BackStartPos.x+240;
		menuPos[2].bottom= (BackStartPos.y-8)+30;
		*/

		savePmenuN = sw;

		//ktj : ¹Ù²Þ.
		menuPos[1].left  = BackStartPos.x+60;
		menuPos[1].top   = (BackStartPos.y-8)+10;
		menuPos[1].right = BackStartPos.x+120;	
		menuPos[1].bottom= (BackStartPos.y-8)+30;	


		menuPos[2].left  = BackStartPos.x+120;
		menuPos[2].top   = (BackStartPos.y-8)+10;
		menuPos[2].right = BackStartPos.x+180;
		menuPos[2].bottom= (BackStartPos.y-8)+30;
	}


	switch(sw) {
	case 0:			//Äù½ºÆ® ¸Þ´º ¼ÂÆÃ

		menuSu = 3;	//Çìµå¸Þ´º´Â ÀÌ¹Ì ¼ÂÆÃµÇÀÖÀ¸¹Ç·Î ÀÌ·¸°Ô ÇØ¾ßÇÔ¿¡ ÁÖÀÇ

		//Äù½ºÆ®ÀÇ ÇÏºÎ¸Þ´ºÆùÆ®¼ÂÆÃ.=========================================start
		menuButPosx =BackStartPos.x+100;
		menuButPosy =BackStartPos.y+220;
		for(i=0+3; i<5+3; i++) {		//¾Æ·¡ ¸Þ´º 
			menuPos[i].left  = menuButPosx+( (i-3)*23);		//left(-3´Â i°¡ 0ºÎÅÍ½ÃÀÛÇÏ°ÔÇÏ±âÀ§ÇÑ°ÍÀÓ¿¡ ÁÖÀÇ)
			menuPos[i].top   = menuButPosy ;			//top
			menuPos[i].right = menuPos[i].left+20;		//right
			menuPos[i].bottom= menuPos[i].top +20;		//bottom
		}
		menuSu = 3+5;	//¸Þ´º°¹¼ö¼ÂÆÃ
		//Äù½ºÆ®ÀÇ ÇÏºÎ¸Þ´ºÆùÆ®¼ÂÆÃ.=========================================end
		

		//Äù½ºÆ®ÀÌ¸§¼±ÅÃºÎ ¼ÂÆÃ =================================================start
		qNameS=0, qNameE=5;		//Äù½ºÆ®ÀÌ¸§ÀÇ È­¸é»ó¿¡ ³ª¿Ã ¸ÇÀ§ÂÊ°ú ¸Ç¾Æ·¡ÂÊ 
		qNameSelN=0;			//Äù½ºÆ®ÀÌ¸§ÀÇ ¼±ÅÃ¹øÈ£
		
		qNameS_ENDs=0, qNameE_ENDs=5;		//Äù½ºÆ®ÀÌ¸§ÀÇ È­¸é»ó¿¡ ³ª¿Ã ¸ÇÀ§ÂÊ°ú ¸Ç¾Æ·¡ÂÊ 
		

		qNamePosx =BackStartPos.x+110;
		qNamePosy =BackStartPos.y+40;

		for(i=0; i<5; i++) {
			menuPos[menuSu ].left  = qNamePosx;
			menuPos[menuSu ].top   = qNamePosy;
			menuPos[menuSu ].right = menuPos[menuSu ].left+(12*10);	//(ÇÑ±ÛÇÑ±ÛÀÚ 12µµÆ®*10ÀÚ)
			menuPos[menuSu ].bottom= menuPos[menuSu ].top +20;
			menuSu ++;
			qNamePosy += 30;
		}
		//menuSu =3+5+5;
		//Äù½ºÆ®ÀÌ¸§¼±ÅÃºÎ ¼ÂÆÃ =================================================end


		//Äù½ºÆ®¿ÞÂÊ¸Þ´ºÀÇ ÇÏºÎ¸Þ´ºÆùÆ®¼ÂÆÃ======================================start
		menuButPosx =BackStartPos.x-80;
		menuButPosy =BackStartPos.y+220;
		i=0;
		menuPos[menuSu ].left  = menuButPosx+( i*23);		
		menuPos[menuSu ].top   = menuButPosy ;
		menuPos[menuSu ].right = menuPos[menuSu ].left+34;
		menuPos[menuSu ].bottom= menuPos[menuSu ].top +20;
		menuSu ++;

		i=2;
		menuPos[menuSu ].left  = menuButPosx+( i*23);		
		menuPos[menuSu ].top   = menuButPosy ;
		menuPos[menuSu ].right = menuPos[menuSu ].left+20;
		menuPos[menuSu ].bottom= menuPos[menuSu ].top +20;
		menuSu ++;

		i=3;
		menuPos[menuSu ].left  = menuButPosx+( i*23);		
		menuPos[menuSu ].top   = menuButPosy ;
		menuPos[menuSu ].right = menuPos[menuSu ].left+20;
		menuPos[menuSu ].bottom= menuPos[menuSu ].top +20;
		menuSu ++;

		i=5;
		menuPos[menuSu ].left  = menuButPosx+( i*23) - 14;	
		menuPos[menuSu ].top   = menuButPosy ;			
		menuPos[menuSu ].right = menuPos[menuSu ].left+20;
		menuPos[menuSu ].bottom= menuPos[menuSu ].top +20;		//bottom
		menuSu ++;
		//Äù½ºÆ®¿ÞÂÊ¸Þ´ºÀÇ ÇÏºÎ¸Þ´ºÆùÆ®¼ÂÆÃ======================================end

		break;

	case 1:		//µ¿·á¸Þ´ºÀÇ ¼ÂÆÃ.
		menuSu = 3;	//Çìµå¸Þ´º´Â ÀÌ¹Ì ¼ÂÆÃµÇÀÖÀ¸¹Ç·Î ÀÌ·¸°Ô ÇØ¾ßÇÔ¿¡ ÁÖÀÇ

		//µ¿·áÀÇ ÇÏºÎ¸Þ´ºÆùÆ®¼ÂÆÃ.=========================================start
		menuButPosx =BackStartPos.x+100;
		menuButPosy =BackStartPos.y+220;
		for(i=0+3; i<5+3; i++) {		//¾Æ·¡ ¸Þ´º 
			menuPos[i].left  = menuButPosx+( (i-3)*23);		//left(-3´Â i°¡ 0ºÎÅÍ½ÃÀÛÇÏ°ÔÇÏ±âÀ§ÇÑ°ÍÀÓ¿¡ ÁÖÀÇ)
			menuPos[i].top   = menuButPosy ;			//top
			menuPos[i].right = menuPos[i].left+20;		//right
			menuPos[i].bottom= menuPos[i].top +20;		//bottom
		}
		menuSu = 3+5;	//¸Þ´º°¹¼ö¼ÂÆÃ


		if(isClanWon==1) {	//ktj Å¬·£¿ø ¸®½ºÆ®Ã¢ÀÌ ³Ö¾î¾ßÇÔ.
			//8¹øÀÓ.
			menuPos[menuSu ].left  = BackStartPos.x+180;
			menuPos[menuSu ].top   = (BackStartPos.y-8)+10;
			menuPos[menuSu ].right = BackStartPos.x+240;
			menuPos[menuSu ].bottom= (BackStartPos.y-8)+30;
			menuSu = 3+5+1;
		}
		

		//µ¿·áÀÇ ÇÏºÎ¸Þ´ºÆùÆ®¼ÂÆÃ.=========================================end
		break;


	case 2:		//Ä£±¸¸Þ´ºÀÇ ¼ÂÆÃ
		menuSu = 3;	//Çìµå¸Þ´º´Â ÀÌ¹Ì ¼ÂÆÃµÇÀÖÀ¸¹Ç·Î ÀÌ·¸°Ô ÇØ¾ßÇÔ¿¡ ÁÖÀÇ

		//Ã¤ÆÃÀÇ id¼±ÅÃºÎºÐ(3~9¹ø±îÁöÀÓ)=========================================start
		//menuButPosx =BackStartPos.x+120;
		menuButPosx =BackStartPos.x+100;
		menuButPosy =BackStartPos.y+55;
		for(i= 0; i < 7; i++) {
			menuPos[menuSu ].left  = menuButPosx;				//left
			menuPos[menuSu ].top   = menuButPosy;				//top
			menuPos[menuSu ].right = menuPos[menuSu ].left+(12*10);		//right
			menuPos[menuSu ].bottom= menuPos[menuSu ].top +18;		//bottom

			menuButPosy += 20;
			menuSu ++;
		}



		menuSu = 3+7;	//ID ¾Õ¿¡ ºÙÀº Ç¥½ÄÀÓ.
		//menuButPosx =BackStartPos.x+100;
		menuButPosx =BackStartPos.x+80;
		menuButPosy =BackStartPos.y+55;
		for(i= 0; i < 7; i++) {
			menuPos[menuSu ].left  = menuButPosx;				//left
			menuPos[menuSu ].top   = menuButPosy;				//top
			menuPos[menuSu ].right = menuPos[menuSu ].left+20;	//right
			menuPos[menuSu ].bottom= menuPos[menuSu ].top +18;		//bottom

			menuButPosy += 20;
			menuSu ++;
		}
		//Ã¤ÆÃÀÇ id¼±ÅÃºÎºÐ=========================================end


		//Ã¤ÆÃÀÇ ÇÏºÎ¸Þ´ºÆùÆ®¼ÂÆÃ.=========================================start

		
		menuSu = 3+7+7;	
		menuButPosx =BackStartPos.x+85;
		menuButPosy =BackStartPos.y+220;

		for(i=0; i<3+ 4; i++) {		//¾Æ·¡ ¸Þ´ºÁß ÃÖÇÏ´Ü ¹öÆ° 7°³
			
			menuPos[menuSu ].left  = menuButPosx+( i*20);		//left(-3´Â i°¡ 0ºÎÅÍ½ÃÀÛÇÏ°ÔÇÏ±âÀ§ÇÑ°ÍÀÓ¿¡ ÁÖÀÇ)

			if(i>=3) menuPos[menuSu ].left +=5;				//Áß°£¿¡ ¶è´Ù.

			menuPos[menuSu ].top   = menuButPosy ;				//top
			menuPos[menuSu ].right = menuPos[menuSu ].left+20;	//right
			menuPos[menuSu ].bottom= menuPos[menuSu ].top +20;	//bottom

			menuSu ++;
		}







		//ktj : Å¬·£¸®½ºÆ®¶§¹®¿¡ »õ·Î³ÖÀ½.
		menuSu = 3+7+7 + 7;	

		if(isClanWon==1) {	//Å¬·£¿ø ¸®½ºÆ®Ã¢ÀÌ ³Ö¾î¾ßÇÔ.
			//24¹øÀÓ.
			menuPos[menuSu ].left  = BackStartPos.x+180;
			menuPos[menuSu ].top   = (BackStartPos.y-8)+10;
			menuPos[menuSu ].right = BackStartPos.x+240;
			menuPos[menuSu ].bottom= (BackStartPos.y-8)+30;
			menuSu = 3+7+7 + 7 + 1;	
		}


		//Ã¤ÆÃÀÇ ÇÏºÎ¸Þ´ºÆùÆ®¼ÂÆÃ.=========================================end

		break;
	}
}





void HoParty_KTJ::Init()
{
	Load();
	
	memset(PartyMember, 0, sizeof(PartyMember));
	PartyMemberCount = 0;
	//ktj : »èÁ¦
	/*
	MessageBoxDrawCount = 0;
	Close();
	*/

	//chatButN = 12;	//Ã¤ÆÃ->Ä£±¸¸ñ·ÏÀ» ·ÎµåÇÏ°ÔÇÔ.(Çö¹öÀü¿¡¼­´Â °ÅºÎ¸¸µÇ±â¶«¿¡ 13À¸·ÎÇÔ.
	q_explationS = 0;


	/*
	//ktj : ÀÓ½Ã ³ªÁß¿¡ Áö¿ï°Í
	quest_Progress_Clear();
	quest_End_Clear();
	quest_Progress_Set("¿ö¸ÞÁøÇàÇÑ´Ù", "ChangeJob1a.Msg");
	quest_End_Set("¿ö¸Þ³¡ÇÑ´Ù", "ÆÄÀÏ³×ÀÓÀÌ´Ù");
	*/
}



void HoParty_KTJ::Close()
{
	int i, index;
	for(i= 0; i < PARTY_BINFOsu; i++)
	{
		if(binfo_Bmp[i]) {
			binfo_Bmp[i]->Release();
			binfo_Bmp[i] = NULL;
		}
	}

	for(i= 0; i < PARTY_BUTTONsu; i++)
	{
		if(butt_Bmp[i]) {
			butt_Bmp[i]->Release();
			butt_Bmp[i] = NULL;
		}
	}







	
	if(BmpLifeBlue)
	{
		BmpLifeBlue->Release();
		BmpLifeBlue = NULL;
	}

	if(BmpLifeRed)
	{
		BmpLifeRed->Release();
		BmpLifeRed = NULL;
	}

	
	//ktj : »èÁ¦
	for(index = 0; index < 5; index++)
	{
		if(ToolTip[index] != NULL)
		{
			ToolTip[index]->Release();
			ToolTip[index] = NULL;
		}
	}

	for(index = 0; index < 4; index++)
	{
		if(Button[index] != NULL)
		{
			Button[index]->Release();
			Button[index] = NULL;
		}
	}

	for(index = 0; index < 2; index++)
	{
		if(BmpMessageOk[index] != NULL)
		{
			BmpMessageOk[index]->Release();
			BmpMessageOk[index] = NULL;
		}

		if(BmpMessageCancel[index] != NULL)
		{
			BmpMessageCancel[index]->Release();
			BmpMessageCancel[index] = NULL;
		}
	}
	

	for(index = 0; index < 3; index++)
	{
		if(BmpMan[index] != NULL)
		{
			BmpMan[index]->Release();
			BmpMan[index] = NULL;
		}
	}


	/*
	//ÆùÆ® Á¦°Å
	DeleteObject( hoFont11);
	*/
}




void HoParty_KTJ::Load()
{
	int i, index;
	MatPartyBackGround = //CreateTextureMaterial( "Effect\\Party\\PartyBackGround.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
		CreateTextureMaterial( "image\\party\\party_win.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );



	MatTitle[0] =	//Å¸ÀÌÆ²ÀÌ¸§-Äù½ºÆ®
		CreateTextureMaterial( "image\\party\\title-quest.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	MatTitle[1] =	//Å¸ÀÌÆ²ÀÌ¸§-µ¿·á
		CreateTextureMaterial( "image\\party\\title-Party.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	MatTitle[2] =	//Å¸ÀÌÆ²ÀÌ¸§-Ã¤ÆÃ
		CreateTextureMaterial( "image\\party\\title-chatting.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	MatTitle[3] =	//Äù½ºÆ®¿ë À©µµ¿ì
		CreateTextureMaterial( "image\\party\\quest_win.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	

	MatTitle[4] =	//Å¸ÀÌÆ²ÀÌ¸§-µ¿·á(Å¬·£Àº ¾øÀ½)
		CreateTextureMaterial( "image\\party\\title-NoClan_Party.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	MatTitle[5] =	//Å¸ÀÌÆ²ÀÌ¸§-Ã¤ÆÃ(Å¬·£Àº ¾øÀ½)
		CreateTextureMaterial( "image\\party\\title-NoClan_chatting.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );






	char *binfoName[] = {	
	"ButtonInfo-1.bmp",	//0 ÀÌÀÓ
	"ButtonInfo-2.bmp",	//1 ÇØ»ê
	"ButtonInfo-3.bmp",	//2	Ãß¹æ
	"ButtonInfo-4.bmp",	//3	Å»Åð
	"ButtonInfo-5.bmp",	//4	´Ý±â

	"ButtonInfo-c0.bmp",	//5	Ã¤ÆÃ
	"ButtonInfo-c1.bmp",	//6	µ¿·á
	"ButtonInfo-c2.bmp",	//7 Ä£±¸¸ñ·Ï
	"ButtonInfo-c3.bmp",	//8	°ÅºÎÀÚ
	"ButtonInfo-c4.bmp",	//9	ÃÖ±Ù¸ñ·Ï
	"ButtonInfo-c5.bmp",	//10	±æµå	

	"ButtonInfo-q0.bmp",	//11	Äù½ºÆ®
	"ButtonInfo-q1.bmp",	//12	¾Æ·¡
	"ButtonInfo-q2.bmp",	//13	À§
	"ButtonInfo-q3.bmp",	//14	ÁøÇà
	"ButtonInfo-q4.bmp",	//15	¿Ï¼ö

	"ButtonInfo-qc.bmp",	//16	Äù½ºÆ®Ãë¼Ò
	"ButtonInfo-qc-nxt.bmp",//17	ÀÌÀüÆäÀÌÁö
	"ButtonInfo-qc-pre.bmp",//18	´ÙÀ½ÆäÀÌÁö


	"ButtonInfo-c6.bmp",	//19	»èÁ¦(Ã¤ÆÃ¿¡ °ü·ÃµÈ°Ô Ãß°¡µÊ)
	"ButtonInfo-c7.bmp",	//20	°ÅºÎ(°ÅºÎÀÚµî·Ï)
	"ButtonInfo-c8.bmp",	//21	Ä£±¸(Ä£±¸µî·Ï)
	};	

	char buffer[256];		
	for(i= 0; i < PARTY_BINFOsu; i++)		//¹öÆ°ÀÌ¸§½áÁø ±×¸²ÀÓ.
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "image\\party\\%s", binfoName[i]);
		binfo_Bmp[i] = LoadDibSurfaceOffscreen(buffer);
	}

	char *iconName[] = {
	"ButtonCancel.bmp",			//0
	"ButtonCancel_0.bmp",		//1

	"chatting-icon_b.bmp",		//2
	"chattng-icon_off.bmp",		//3
	"chattng-icon_on.bmp",		//4
	"ButtonExit.bmp",			//5		//ºêÀÌÀÚ Ç¥½Ã(»õ·Î ³ÖÀ½:image\Sinimage\shopall¿¡ ÀÖ´Â°ÍÀ» Ä«ÇÇÇØ¿è)
	"close_.bmp",				//6

	"icon-1.bmp",				//7
	"icon-1_.bmp",				//8
	"icon-2.bmp",				//9
	"icon-2_.bmp",				//10
	"icon-3.bmp",				//11
	"icon-3_.bmp",				//12
	"icon-4.bmp",				//13
	"icon-4_.bmp",				//14

	"icon-c1.bmp",				//15
	"icon-c1_.bmp",				//16
	"icon-c2.bmp",				//17 Ä£±¸¸ñ·Ï
	"icon-c2_.bmp",				//18
	"icon-c3.bmp",				//19 »èÁ¦¹öÆ°
	"icon-c3_.bmp",				//20
	"icon-c4.bmp",				//21 ÃÖ±Ù¸ñ·Ï
	"icon-c4_.bmp",				//22
	"icon-c5.bmp",				//23
	"icon-c5_.bmp",				//24

	"icon-q1.bmp",				//25
	"icon-q1_.bmp",				//26
	"icon-q2.bmp",				//27
	"icon-q2_.bmp",				//28
	"icon-q3.bmp",				//29
	"icon-q3_.bmp",				//30
	"icon-q4.bmp",				//31
	"icon-q4_.bmp",				//32

	"icon-qc.bmp",				//33
	"icon-qc_.bmp",				//34

	"party_icon.bmp",			//35
	"party_icon_0.bmp",			//36
	"party_man_0.bmp",			//37
	"party_man_1.bmp",			//38
	"party_man_jang.bmp",		//39

	"quest_icon-end.bmp",		//40
	"quest_icon-ing.bmp",		//41


	"LeftArrow.bmp",		//42
	"LeftArrow_.bmp",		//43
	"RightArrow.bmp",		//44
	"RightArrow_.bmp",		//45



	"icon-c6.bmp",				//46 °ÅºÎÀÚ¸ñ·Ï
	"icon-c6_.bmp",				//47

	"icon-7.bmp",				//48 °ÅºÎÀÚµî·ÏÇÏ±â
	"icon-7_.bmp",				//49
	"icon-8.bmp",				//50 Ä£±¸µî·ÏÇÏ±â
	"icon-8_.bmp",				//51
	"last_man.bmp",				//52 ±Í¿¡ ÇìµåÆù(ÃÖ±Ù¸ñ·Ï)

	"chattng-icon-c.bmp",		//53 ±Ó¼Ó¸»·ÎÁöÁ¤µÈ»ç¶÷ÀÌ ´õºíÅ¬¸¯µÈ°æ¿ì»ç¿ë


	};
	for(i= 0; i < PARTY_BUTTONsu; i++)		//°¢Á¾ ¹öÆ° ±×¸²ÀÓ.
	{
		if(i==48)
			i=48;
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "image\\party\\%s", iconName[i]);
		butt_Bmp[i] = LoadDibSurfaceOffscreen(buffer);
	}



	

	//ktj : ÀÏ´Ü »èÁ¦
	//MatPartyBackGround = CreateTextureMaterial( "Effect\\Party\\PartyBackGround.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	BmpLifeBlue = LoadDibSurfaceOffscreen( "Effect\\Party\\LifeBlue.bmp");
	BmpLifeRed  = LoadDibSurfaceOffscreen( "Effect\\Party\\LifeRed.bmp");
	
	
	//ktj : ÀÏ´Ü »èÁ¦
	/*
	char buffer[256];
	for(int index = 0; index < 5; index++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\ToolTip", index+1, ".bmp");
		ToolTip[index] = LoadDibSurfaceOffscreen(buffer);
	}
	
	
	for(index = 0; index < 5; index++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\icon-", index+1, ".bmp");
		Button[index] = LoadDibSurfaceOffscreen(buffer);
	}
	*/
	
	for(index = 0; index < 3; index++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\Man", index+1, ".bmp");
		BmpMan[index] = LoadDibSurfaceOffscreen(buffer);
	}
	

	//ktj : ÀÏ´Ü »èÁ¦
	/*
	//¸Þ½ÃÁö Ã¢°ü·Ã..			
	//////////////////////////////////////////////////////////////////////////
	MatMessageBoxBackGround = CreateTextureMaterial( "Effect\\Party\\MessageBackGround.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	for(index = 0; index < 2; index++)
	{
		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\Ok", index+1, ".bmp");
		BmpMessageOk[index] = LoadDibSurfaceOffscreen(buffer);

		memset(buffer, 0, sizeof(buffer));
		wsprintf(buffer, "%s%d%s", "Effect\\Party\\Cancel", index+1, ".bmp");
		BmpMessageCancel[index] = LoadDibSurfaceOffscreen(buffer);
	}
	
	ReadTextures();
	*/



	chatINI_read();
}

















extern int	WhisperPartyPlayer( char *szName );
extern int	PartyButton( int Num , int Button );

/*
//ktj : »èÁ¦
BOOL faceFlag = FALSE;
BOOL whisperFlag = FALSE;
BOOL buttonMessageFlag = FALSE;
*/


//ÀÌ°Ç Äù½ºÆ®¿ë
int b_Nis[] = {25, 27, 29, 31, 5};	//ÆÄÆ¼¸Þ´ºÀÇ ¾Æ·¡ÂÊ¿¡ ÀÖ´Â ¹öÆ° 5°³
int bi_Nis[] = {18, 17, 14, 15, 4};//16};		//¸»Ç³¼±³ª¿À±âÀ§ÇÑ ¹øÈ£
int b_Nflag[] = {0, 0, 0, 0, 0, 0, 0,0,0,0, 0,0,0,0,0,0,0,0,0};		//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ(À§:1 ±âÅ¸ 0):ÀÓ½Ã·Î 10°³³ÖÀ½
int b2_Nflag[] = {0, 0, 0, 0, 0, 0, 0,0,0,0, 0,0,0,0,0,0,0,0,0};	//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ(À§:1 ±âÅ¸ 0):ÀÓ½Ã·Î 10°³³ÖÀ½
int qN_flag[] = {0, 0, 0, 0, 0, 0, 0,0,0,0, 0,0,0,0,0,0,0,0,0};		//Äù½ºÆ®ÀÇ ÀÌ¸§À§¿¡ ¸¶¿ì½º¼ÂÆÃ
int qN_Pressf=0;	//Äù½ºÆ®ÀÌ¸§ÀÇ ´©¸§Ç¥½Ã(8~12±îÁö·Î Á¤ÇØÁü)




//ÀÌ°Ç µ¿·á¿ë
int db_Nis[] = {7, 9, 11, 13, 5};
int dbi_Nis[] = {0, 1, 2, 3, 4};		//¸»Ç³¼±³ª¿À±âÀ§ÇÑ ¹øÈ£






              //ÃÖ±Ù¸ñ·Ï,Ä£±¸¸ñ·Ï,°ÅºÎÀÚ¸ñ·Ï,      <-, Ä£±¸µî·Ï, °ÅºÎµî·Ï, ³ª°¡±â (ÃÖ±Ù¸ñ·Ï¿¡¼­ »ç¿ë)
int cb_Nis[] = {21, 17, 46,                    42, 50, 48, 5};		
int cbi_Nis[] = {9, 7,  8,                    17, 21, 20, 4};		//¸»Ç³¼±³ª¿À±âÀ§ÇÑ ¹øÈ£
int cb_Nis1[] = {21, 17, 46,                    42, 44, 19, 5};		
int cbi_Nis1[] = {9, 7,  8,                    17, 18, 19, 4};		//¸»Ç³¼±³ª¿À±âÀ§ÇÑ ¹øÈ£
int cb_Nis2[] = {21, 17, 46,                    42, 44, 19, 5};
int cbi_Nis2[] = {9, 7,  8,                    17, 18, 19, 4};		//¸»Ç³¼±³ª¿À±âÀ§ÇÑ ¹øÈ£





int QuestnotCharMove = 0;				//¸Þ´ºÆÇ¾ÈÀÇ ¸¶¿ì½ºÀÇ ¿òÁ÷ÀÓ¿¡ Ä³¸¯ÅÍ°¡ ¿µÇâ¾øµµ·Ï ÇÑ´Ù.
int QuestnotCharMove2 = 0;				//QuestnotCharMove2 ´Â Äù½ºÆ®ÀÇ ¿ÞÂÊ¿¡ Æ¢¾î³ª¿À´Â ¸Þ´ºÀÓ.


int HoParty_KTJ::Draw()
{
	int i, j, j2;
	if (renderDevice.IsDevice() == NULL)
		return FALSE;

	//int menuButPosx;
	//int menuButPosy;
	int qNamePosx ;
	int qNamePosy ;
	int mSu ;



	/*
	static cnt=0;
	if(cnt==0)
		Init();
	cnt=1;

	PmenuN = 2;
	//ktj: ÀÓ½Ã
	BackStartPos.x = 539;
	PartyPosState = PARTY_PROCESS;
	menuSet(PmenuN);
	*/


	if( PmenuN==1) goto menu_dongru;
	if( PmenuN==2) goto menu_frList;
	if( PmenuN==3) goto menu_clanList;


	renderDevice.BeginScene();


	
	if(qN_Pressf &&  MatTitle[3]!= -1)				//Äù½ºÆ®Ã¢ÀÇ ¿·¿¡ ºÙ´Â Ã¢(Äù½ºÆ®Á¦¸ñ´­·¶À»¶§¸¸³ª¿È)
		dsDrawTexImage( MatTitle[3], 
			BackStartPos.x-195, BackStartPos.y +15, 256, 256, 255);

	if(MatPartyBackGround != -1)		//Äù½ºÆ®µ¿·áÃ¤ÆÃÀÇ ¹è°æÃ¢ Ãâ·Â.
		dsDrawTexImage( MatPartyBackGround, 
			BackStartPos.x, BackStartPos.y, 256, 256, 255);
	
	if(MatTitle[PmenuN]!= -1)			//Äù½ºÆ®µ¿·áÃ¤ÆÃÀÇ Å¸ÀÌÆ²Ã¢
		dsDrawTexImage( MatTitle[PmenuN], 
			BackStartPos.x, BackStartPos.y - 8,256, 32, 255);

	renderDevice.EndScene();

	if(PartyPosState != PARTY_PROCESS) return 1;

	//Äù½ºÆ®¿ë ¸Þ´ºÆùÆ® ======================================start
	
	mSu = 3;
	for(i= 0; i < 5; i++)
	{
		if(b_Nflag[i])	{//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.

			//¸»Ç³¼±
			DrawSprite(menuPos[mSu  ].left-30,  menuPos[mSu  ].top-30, binfo_Bmp[ bi_Nis[i] ],  0, 0, 76, 27,1);

			//ÆùÆ®
			
			DrawSprite(menuPos[mSu  ].left, menuPos[mSu  ].top, butt_Bmp[  b_Nis[i]  ],  0, 0, 20, 20,1);
	

		}
		else
		{
			///if(i != 2 )
//			DrawSprite(menuPos[mSu  ].left,  menuPos[mSu  ].top, butt_Bmp[  28  ],  0, 0, 20, 20,1);
			DrawSprite(menuPos[mSu  ].left,  menuPos[mSu  ].top, butt_Bmp[  b_Nis[i]+1  ],  0, 0, 20, 20,1);
		}

		if((questSelN-3) == i)
		{
			//ÆùÆ®
			DrawSprite(menuPos[mSu  ].left/*-30*/, menuPos[mSu  ].top, butt_Bmp[  b_Nis[i]  ],  0, 0, 20, 20,1);
		}
		mSu++;
	}
	

	//Äù½ºÆ®¿ë ¸Þ´ºÆùÆ® ======================================end


	//Äù½ºÆ®¿ë Äù½ºÆ®ÀÌ¸§ ======================================start
	qNamePosx =BackStartPos.x+116;
	qNamePosy =BackStartPos.y+40;
	HDC hdc;
	HFONT oldFont;
	renderDevice.lpDDSBack->GetDC(&hdc);
	SetBkMode( hdc, TRANSPARENT );

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject( hdc , hFont );
	for(i= qNameS; i < qNameE; i++) {

		if(qN_flag[i]) {//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.
			SetTextColor( hdc, RGB(255, 255, 255));
		}
		else {
			SetTextColor( hdc, RGB(255, 190, 107));
			SetTextColor( hdc, RGB(255, 255, 255));
		}

		if(qN_Pressf &&  (((qN_Pressf-8)+qNameS)== i) )		//¸¶¿ì½º¹öÆ°À¸·Î ´­¸®¾îÁø Äù½ºÆ®ÀÌ¸§ÀÎ°æ¿ì
			SetTextColor( hdc, RGB(255, 0, 0));
			



		if(questSelN == 5) {	//ÁøÇàÁßÀÎ°æ¿ì
#ifdef _LANGUAGE_ARGENTINA
			dsTextLineOut(hdc, qNamePosx-30, qNamePosy, qNameb[i], lstrlen(qNameb[i])); // Äù½ºÆ®¸í(ÆùÆ®) ¼öÁ¤
#else
			dsTextLineOut(hdc, qNamePosx, qNamePosy, qNameb[i], lstrlen(qNameb[i]));
#endif
		}
		else {					//case 6:		//¿Ï¼ö
#ifdef _LANGUAGE_ARGENTINA
			dsTextLineOut(hdc, qNamePosx-30, qNamePosy, qNameb_E[i], lstrlen(qNameb_E[i])); // Äù½ºÆ®¸í(ÆùÆ®) ¼öÁ¤
#else
			dsTextLineOut(hdc, qNamePosx, qNamePosy, qNameb_E[i], lstrlen(qNameb_E[i]));
#endif
		}

		qNamePosy += 30;
	}
	if(oldFont)
		SelectObject( hdc, oldFont);
	renderDevice.lpDDSBack->ReleaseDC(hdc);


	qNamePosx =BackStartPos.x+110;			//Äù½ºÆ®ÀÌ¸§¾ÕÀÇ ÆùÆ®Ç¥½Ã ==start(±ÛÀÚÇÏ°í °°ÀÌ ¸ø¾´´Ù :¾È±×·ÁÁü)
	qNamePosy =BackStartPos.y+40;
	for(i= qNameS; i < qNameE; i++) {


		if(questSelN == 5) {	//ÁøÇàÁßÀÎ°æ¿ì
			if(qNameb[i][0]==0) break;
		}
		else {					//case 6:		//¿Ï¼ö
			if(qNameb_E[i][0]==0) break;
		}


		if(qN_flag[i]) {//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.
			//Äù½ºÆ® endÇ¥½Ã¿ë ÆùÆ®
#ifdef _LANGUAGE_ARGENTINA
			DrawSprite(qNamePosx-40, qNamePosy, butt_Bmp[ 40 ],  0, 0, 14, 15,1); // Äù½ºÆ®±×¸² ¼öÁ¤
#else
			DrawSprite(qNamePosx-15, qNamePosy, butt_Bmp[ 40 ],  0, 0, 14, 15,1);
#endif
		}
		else {
			//Äù½ºÆ® ingÇ¥½Ã¿ë ÆùÆ®]
#ifdef _LANGUAGE_ARGENTINA
			DrawSprite(qNamePosx-40, qNamePosy, butt_Bmp[ 41 ],  0, 0, 14, 15,1); // Äù½ºÆ®±×¸² ¼öÁ¤
#else
			DrawSprite(qNamePosx-15, qNamePosy, butt_Bmp[ 41 ],  0, 0, 14, 15,1);
#endif
		}
		qNamePosy += 30;
	}									//Äù½ºÆ®ÀÌ¸§¾ÕÀÇ ÆùÆ®Ç¥½Ã ==end

	qNamePosx =BackStartPos.x-80;
	qNamePosy =BackStartPos.y+50;

	
	
	//Äù½ºÆ®¿ë¿ÞÂÊ ¸Þ´ºÆùÆ® ======================================start
	if(qN_Pressf==0) {
		QuestnotCharMove = 0;
		QuestnotCharMove2= 0;
		return 1;	//Äù½ºÆ®¿ÞÂÊÃ¢ÇÊ¿ä¾øÀ»°æ¿ì
	}

	//Äù½ºÆ® ¼³¸í±Û ±×¸°´Ù.//80
#ifdef _LANGUAGE_ARGENTINA
	Draw_questExplane(BackStartPos.x-120, BackStartPos.y+55);
#else
	Draw_questExplane(BackStartPos.x-105, BackStartPos.y+55);
#endif

	QuestnotCharMove = 1;
	QuestnotCharMove2= 1;

	static int bN[] ={33, 42, 44, 5};
	static int bSize[] ={34, 20, 20, 20};		//ÆùÆ®ÀÇ x size°¡ Æ²·Á¼­..

	static int bi_Nis2[] = {0, 18, 17, 4};		//¸»Ç³¼± ¹øÈ£


    mSu = 3+5+5;
	
	for(i= 0; i < 4; i++)
	{
		if(i==0) {
			goto jmp111;		//±×³É »¯´Ù.
		}

		if(b2_Nflag[i]) {//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.

			//¸»Ç³¼±
			DrawSprite(menuPos[mSu  ].left-30,  menuPos[mSu  ].top-30,
				binfo_Bmp[ bi_Nis2[i] ],  0, 0, 76, 27,1);

			DrawSprite(menuPos[mSu ].left, menuPos[mSu ].top, 
				butt_Bmp[  bN[i]  ],  0, 0, bSize[i], 20,1);

		}
		else {
				DrawSprite(menuPos[mSu ].left, menuPos[mSu ].top, 
					butt_Bmp[  bN[i]+1  ],  0, 0, bSize[i], 20,1);
		}

jmp111:
		mSu ++;
	}
	
	//Äù½ºÆ®¿ë ¸Þ´ºÆùÆ® ======================================end

	return 1;

menu_dongru:

	renderDevice.BeginScene();

	//Party ¹è°æÃ¢ Ãâ·Â.
	if(MatPartyBackGround != -1)
		dsDrawTexImage( MatPartyBackGround, 
			BackStartPos.x, BackStartPos.y, 
			256, 256, 255);

	//Å¸ÀÌÆ²Ã¢	: PartyÃ¢ À§¿¡ ºÙ´Â°ÍÀÓ
	/*
	if(MatTitle[PmenuN]!= -1)
		dsDrawTexImage( MatTitle[PmenuN], 
			BackStartPos.x, BackStartPos.y - 8,
			256, 32, 255);
			*/
#ifdef  __CLANSUBCHIP__
	if(cldata.myPosition==100 || cldata.myPosition==101 || cldata.myPosition==104) 
#else
	if(cldata.myPosition==100 || cldata.myPosition==101) 
#endif

	{
		//Å¸ÀÌÆ²Ã¢	: Å¬·£ÀÌ ÀÖ´Â °æ¿ìÀÓ.
		if(MatTitle[PmenuN]!= -1)
			dsDrawTexImage( MatTitle[PmenuN],    BackStartPos.x, BackStartPos.y - 8,   256, 32, 255);
		
	}
	else {
		//Å¸ÀÌÆ²Ã¢	: Å¬·£ÀÌ ¾ø´Â °æ¿ìÀÓ.
		if(MatTitle[4]!= -1)
			dsDrawTexImage( MatTitle[4],   BackStartPos.x, BackStartPos.y - 8,    256, 32, 255);
	}
	



	renderDevice.EndScene();


	if(PartyPosState != PARTY_PROCESS) return 1;
	
	//µ¿·á¿ë ¸Þ´ºÆùÆ® ======================================start
	//menuButPosx =BackStartPos.x+110;
	//menuButPosy =BackStartPos.y+220;
	/*
	//ktj : ¿øº»
	mSu = 3;
	for(i= 0; i < 5; i++)
	{
		if(b_Nflag[i])	{//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.


			//ktj : È«¾¾°Å¿¡¼­ µû¿Â°Å == //okÀÓ.
			if(lpCurPlayer->dwObjectSerial != PartyMember[0].ChrCode )
			{
				if(i == 0 || i == 1 || i == 2)
					goto jump0;
			}

			if(PartyMemberCount == 0)
			{
				if(i == 0 || i == 1 || i == 2 || i == 3)
					goto jump0;
			}
			//==


			//¸»Ç³¼±
			DrawSprite(menuPos[mSu  ].left-30, menuPos[mSu  ].top-30, 
				binfo_Bmp[ dbi_Nis[i] ],  0, 0, 76, 27,1);

			//ÆùÆ®
			DrawSprite(menuPos[mSu  ].left, menuPos[mSu  ].top, butt_Bmp[  db_Nis[i]  ],  0, 0, 20, 20,1);
		}
		else {
jump0:
			DrawSprite(menuPos[mSu  ].left, menuPos[mSu  ].top, butt_Bmp[  db_Nis[i]+1  ],  0, 0, 20, 20,1);
		}


		mSu++;
	}
	*/

	//µ¿·á¿ë ¸Þ´ºÆùÆ® ======================================end










	//ktj : µ¿ ¸¸µç°Å ÀÏ´Ü ÆÛ¿È
	TextStartPos.x = BackStartPos.x+80;//102;
	TextStartPos.y = BackStartPos.y+38;

	for(int index = 0; index < PartyMemberCount; index++)
	{
		
		//Life¸¦ Ç¥½Ã.
		if(BmpLifeBlue != NULL && BmpLifeRed != NULL)
		{
			//¿øº»ÀÌ¿©
			DrawSprite(TextStartPos.x-3+14, TextStartPos.y+30*index-2+15, BmpLifeRed,  0, 0, 94, 4, 1);
			DrawSprite(TextStartPos.x-3+14, TextStartPos.y+30*index-2+15, BmpLifeBlue, 0, 0, int((94.f/100.f)*(float)PartyMember[index].Life), 4, 1);
		}
			
			
		if(pCursorPos.x > TextStartPos.x && pCursorPos.y > TextStartPos.y+30*index-10 &&
		   pCursorPos.x < TextStartPos.x +110 && pCursorPos.y < TextStartPos.y+30*index+18)
		{
			
			if(BmpMan[1] != NULL && PartyMember[index].JangFlag == FALSE)
				DrawSprite(TextStartPos.x-4, TextStartPos.y+30*index-2, BmpMan[1],  0, 0, 13, 17,1);
				
			if(BmpMan[3] != NULL && PartyMember[index].JangFlag)
				DrawSprite(TextStartPos.x-4, TextStartPos.y+30*index-2, BmpMan[2],  0, 0, 13, 17,1);
			
			//Ä³¸¯ÅÍ ¼±ÅÃ.
			if(MouseButton[0] && PartyPosState == PARTY_PROCESS)
			{
				MouseDownPartyMember = index;
				
				//¾ó±¼ Ãâ·Â ÇÔ¼ö..
				if(strlen(PartyMember[MouseDownPartyMember].Name) != 0 &&
				   strlen(PartyMember[MouseDownPartyMember].ModelName1) != 0 &&
				   strlen(PartyMember[MouseDownPartyMember].ModelName2) != 0 && faceFlag == FALSE)
				{
					if(faceFlag == FALSE)
					{
						faceFlag = TRUE;
						OpenPartyPlayer(PartyMember[MouseDownPartyMember].Name, PartyMember[MouseDownPartyMember].ModelName1, PartyMember[MouseDownPartyMember].ModelName2);
					}
				}
			}
				
			//±Í¸» º¸³»±â...
			if(MouseDblClick && whisperFlag == FALSE)
			{
				//if(lpCurPlayer->dwObjectSerial != PartyMember[MouseDownPartyMember].ChrCode )
				if(lpCurPlayer->dwObjectSerial != PartyMember[index].ChrCode )
				{
					whisperFlag = TRUE;
					//WhisperPartyPlayer(PartyMember[MouseDownPartyMember].Name);
					WhisperPartyPlayer(PartyMember[index].Name);
				}
			}
			
		}
		else	//¸¶¿ì½º°¡ Á¢±ÙÇÏÁö¾ÊÀº°æ¿ìÀÓ(ktj : ÀÏ´Ü »èÁ¦)
		{
			
			if(BmpMan[0] != NULL && PartyMember[index].JangFlag == FALSE)
				DrawSprite(TextStartPos.x-4, TextStartPos.y+30*index-2, BmpMan[0],  0, 0, 13, 17,1);
			
			if(BmpMan[3] != NULL && PartyMember[index].JangFlag)
				DrawSprite(TextStartPos.x-4, TextStartPos.y+30*index-2, BmpMan[2],  0, 0, 13, 17,1);
		}
	}




		if(PartyPosState == PARTY_PROCESS)
		{
			//´­¸° ¸â¹ö Ç¥½ÃÇÏ±â.
			if(MouseDownPartyMember != -1 && PartyMember[MouseDownPartyMember].JangFlag == FALSE)
				DrawSprite(TextStartPos.x-4, TextStartPos.y+30*MouseDownPartyMember-2, BmpMan[1],  0, 0, 13, 17,1);
			if(MouseDownPartyMember != -1 && PartyMember[MouseDownPartyMember].JangFlag == TRUE)
				DrawSprite(TextStartPos.x-4, TextStartPos.y+30*MouseDownPartyMember-2, BmpMan[2],  0, 0, 13, 17,1);
		}

		
		//HDC hdc;
		//HFONT oldFont;
		renderDevice.lpDDSBack->GetDC(&hdc);
		if(hFont != NULL)
			oldFont = (HFONT)SelectObject( hdc , hFont );
		
		//µÚ¿¡ ±×¸²ÀÚ..
		SetBkMode( hdc, TRANSPARENT );
		
		//LevelÀ» Âï±â..
		char levelBuffer[256];
		for ( int index = 0; index < PartyMemberCount; index++ )
		{
			SetTextColor( hdc, RGB(0, 0, 0));
			dsTextLineOut(hdc, TextStartPos.x+11, TextStartPos.y+30*index+1, PartyMember[index].Name, lstrlen(PartyMember[index].Name));
			memset(levelBuffer, 0, sizeof(levelBuffer));

			if(PartyMember[index].Level > 10)
				wsprintf(levelBuffer, "%s%d%s", "L",PartyMember[index].Level/10,"x");
			else
				wsprintf(levelBuffer, "%s%d", "L", PartyMember[index].Level);
			dsTextLineOut(hdc, TextStartPos.x+110, TextStartPos.y+5+30*index+1, levelBuffer, lstrlen(levelBuffer));
		}
		
		
		//ÁøÂ¥ ±Û¾¾.. Ä³¸¯ÅÍÀÌ¸§±×¸°´Ù.
		SetBkMode( hdc, TRANSPARENT );
		for ( int index = 0; index < PartyMemberCount; index++ )
		{
			if( MouseDownPartyMember != index)
				SetTextColor( hdc, RGB(209, 190, 154));		
			else
				SetTextColor( hdc, RGB(255, 150, 0));
			
			if(pCursorPos.x > TextStartPos.x && pCursorPos.y > TextStartPos.y+30*index-10 &&
			   pCursorPos.x < TextStartPos.x +110 && pCursorPos.y < TextStartPos.y+30*index+18)
				SetTextColor( hdc, RGB(255, 150, 0));
			dsTextLineOut(hdc,TextStartPos.x+10, TextStartPos.y+30*index, PartyMember[index].Name, lstrlen(PartyMember[index].Name));

			memset(levelBuffer, 0, sizeof(levelBuffer));
			
			if(PartyMember[index].Level > 10)
				wsprintf(levelBuffer, "%s%d%s", "L",PartyMember[index].Level/10,"x");
			else
				wsprintf(levelBuffer, "%s%d", "L", PartyMember[index].Level);

			SetTextColor( hdc, RGB(255, 190, 107));
			dsTextLineOut(hdc, TextStartPos.x+110, TextStartPos.y+5+30*index, levelBuffer, lstrlen(levelBuffer));
		}
		if(oldFont)
			SelectObject( hdc, oldFont);
		renderDevice.lpDDSBack->ReleaseDC(hdc);
		








		//================ ¸¶¿ì½º°¡ ¿Ã¶ó°£°÷ÀÇ ¸»Ç³¼±¶á´Ù.
		mSu = 3;
		for(i= 0; i < 5; i++)
		{
			if(b_Nflag[i])	{//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.


				//ktj : È«¾¾°Å¿¡¼­ µû¿Â°Å == //okÀÓ.
				if(lpCurPlayer->dwObjectSerial != PartyMember[0].ChrCode )
				{
					if(i == 0 || i == 1 || i == 2)
						goto jump0;
				}

				if(PartyMemberCount == 0)
				{
					if(i == 0 || i == 1 || i == 2 || i == 3)
						goto jump0;
				}
				//==


				//¸»Ç³¼±
				DrawSprite(menuPos[mSu  ].left-30, menuPos[mSu  ].top-30, 
					binfo_Bmp[ dbi_Nis[i] ],  0, 0, 76, 27,1);

				//ÆùÆ®
				DrawSprite(menuPos[mSu  ].left, menuPos[mSu  ].top, butt_Bmp[  db_Nis[i]  ],  0, 0, 20, 20,1);
			}
			else {
	jump0:
				DrawSprite(menuPos[mSu  ].left, menuPos[mSu  ].top, butt_Bmp[  db_Nis[i]+1  ],  0, 0, 20, 20,1);
			}


			mSu++;
		}




















		
		//ButtonÂï±â. : È«È£µ¿¾¾²«µ¥ ¹öÆ°ÂïÁö¾Ê°í ´­¸°°Í¸¸ Ã³¸²ÇÔ¿¡ ÁÖÀÇ
		for ( int index = 0; index < 5; index++ )
		{
			/*
			//ktj : ¿øº» : ÁÂÇ¥¹Ù²¸¼­¸ø¾¸
			if(pCursorPos.x > BackStartPos.x+114+index*22     && pCursorPos.y > BackStartPos.y+220 &&
			   pCursorPos.x < BackStartPos.x+114+20+index*22  && pCursorPos.y < BackStartPos.y+220+20)
			{
			*/
			//À§Ä¡°¡ ¹Ù²¸¼­ ¤¾¤¾¤§¼Ò½º¸¦ ¹Ù²Þ.
			if(menuPos[3+index].left <= pCursorPos.x  && pCursorPos.x <=  menuPos[3+index].right &&
				menuPos[3+index].top <= pCursorPos.y  && pCursorPos.y <=  menuPos[3+index].bottom)
			{
				if(lpCurPlayer->dwObjectSerial != PartyMember[0].ChrCode)
				{
					if(index == 0 || index == 1 || index == 2)
						continue;
				}
				
				if(PartyMemberCount == 0 && index != 4)
					continue;
				//Button Ç¥½Ã
				//DrawSprite(BackStartPos.x+114+index*22, BackStartPos.y+222, Button[index],  0, 0, 20, 20,1);
				DrawSprite(BackStartPos.x+110+index*23, BackStartPos.y+220, Button[index],  0, 0, 20, 20,1);
				
				if(MouseButton[0] && PartyPosState == PARTY_PROCESS)
				{
					
					if(buttonMessageFlag == FALSE)
					{
						MouseDownButton = index;
						buttonMessageFlag = TRUE;
						//ÆÄÆ¼ ¹öÆ° º¸³»±â...
						PartyButton(MouseDownPartyMember, index);
						MouseDownPartyMember = -1;
					}
					
					//³ª°¡±â ¹öÆ°..
					if(MouseDownButton == 4)
						PartyPosState = PARTY_END;
				}
			}
		}

		
		
	return 1;


menu_frList:

	renderDevice.BeginScene();

	//Party ¹è°æÃ¢ Ãâ·Â.
	if(MatPartyBackGround != -1)
		dsDrawTexImage( MatPartyBackGround, 
			BackStartPos.x, BackStartPos.y, 
			256, 256, 255);

	//Å¸ÀÌÆ²Ã¢	: PartyÃ¢ À§¿¡ ºÙ´Â°ÍÀÓ
	/*
	if(MatTitle[PmenuN]!= -1)
		dsDrawTexImage( MatTitle[PmenuN], 
			BackStartPos.x, BackStartPos.y - 8,
			256, 32, 255);
			*/
#ifdef  __CLANSUBCHIP__
	if(cldata.myPosition==100 || cldata.myPosition==101 || cldata.myPosition==104) 
#else
	if(cldata.myPosition==100 || cldata.myPosition==101 ) 
#endif

	{
		//Å¸ÀÌÆ²Ã¢	: Å¬·£ÀÌ ÀÖ´Â °æ¿ìÀÓ.
		if(MatTitle[PmenuN]!= -1)
			dsDrawTexImage( MatTitle[PmenuN],   BackStartPos.x, BackStartPos.y - 8,   256, 32, 255);
		
	}
	else {
		//Å¸ÀÌÆ²Ã¢	: PartyÃ¢ À§¿¡ ºÙ´Â°ÍÀÓ
		if(MatTitle[5]!= -1)
			dsDrawTexImage( MatTitle[5],    BackStartPos.x, BackStartPos.y - 8,   256, 32, 255);
	}

	renderDevice.EndScene();


	
	//Ã¤ÆÃ¿ë id ±×¸°´Ù. ======================================start
	mSu = 3;
	if(PartyPosState != PARTY_PROCESS) return 1;

	//Ã¤ÆÃ¿ë ¸Þ´ºÆùÆ® ======================================start
	//mSu = 7+3;

	int *intp_N, *intp_Ni;//0:Ä£±¸¸Þ´ºÁß ÃÖ±Ù¸ñ·Ï 1: Ä£±¸µé¸ñ·Ï 2:°ÅºÎÀÚ¸ñ·Ï
	if(cN_MenuN == 0) {
		intp_N = cb_Nis;
		intp_Ni = cbi_Nis;
	}
	else if(cN_MenuN == 1) {
		intp_N = cb_Nis1;
		intp_Ni = cbi_Nis1;
	}
	else {
		intp_N = cb_Nis2;
		intp_Ni = cbi_Nis2;
	}

	mSu = 3+7+7;
	for(i= 0; i < 3+4; i++)	//¸Þ´º6°³ÀÓ.
	{
		if(cN_MenuN == 0 && i==3)
				goto jmp1;			//ÃÖ±Ù¸ñ·ÏÀº È­»ìÇ¥¹öÆ°, »èÁ¦¹öÆ° ¾øÀ½.



		if(cN_MenuN == 0 && i==0) goto jmp1_1;		//ÃÖ±Ù, Ä£±¸, °ÅºÎÀÚ ¸ñ·ÏÁß ´­¸°°Í Ç¥½ÃÇÔ.
		if(cN_MenuN == 1 && i==1) goto jmp1_1;
		if(cN_MenuN == 2 && i==2) goto jmp1_1;


		if(b_Nflag[i])	{//¸¶¿ì½º°¡ À§¿¡ ÀÖ´Â°æ¿ì


			//¸»Ç³¼±
			DrawSprite(menuPos[mSu  ].left-30, menuPos[mSu  ].top-26,
				binfo_Bmp[ intp_Ni[i] ],  0, 0, 76, 27,1);
jmp1_1:
			//ÆùÆ®
			DrawSprite(menuPos[mSu  ].left, menuPos[mSu  ].top,
				butt_Bmp[  intp_N[i]  ],  0, 0, 20, 20,1);
		}
		else {
			DrawSprite(menuPos[mSu  ].left, menuPos[mSu  ].top,
				butt_Bmp[  intp_N[i]+1  ],  0, 0, 20, 20,1);
		}

jmp1:
		mSu++;
	}
	

	//Ã¤ÆÃ¿ë ¸Þ´ºÆùÆ® ======================================end




	//µ¿·á->Ä£±¸ id ±×¸°´Ù. ======================================start
	mSu = 3;
	renderDevice.lpDDSBack->GetDC(&hdc);
	SetBkMode( hdc, TRANSPARENT );
	if(hFont != NULL)
		oldFont = (HFONT)SelectObject( hdc , hFont );


	SetTextColor( hdc, RGB(255, 255, 255));
	if(cN_MenuN == 0) {	



		/*
	
		//ktj : ÀÓ½Ã·Î µ¿·áÀÇ ÃÖ±Ù¸ñ·Ï¿¡ ³Ö´Â°ÍÀÓ
		static cc=0;
		char buf[32];
		wsprintf(buf, "ktjÀÔ%d", cc);
		//wsprintf(buf, "ktjÀÔ");
		//if(cc<10) latest_Insert(buf);
		//if(cc<10) friend_Insert(buf);
		cc++;
		if(cc>=10) cc=0;
		*/
		

		SetTextColor( hdc, RGB(255, 220, 0));
		//dsTextLineOut(hdc, menuPos[mSu  ].left+20, menuPos[mSu  ].top-24, "[ÃÖ±Ù¸ñ·Ï]", 2*4+2);
		dsTextLineOut(hdc, menuPos[mSu  ].left+20, menuPos[mSu  ].top-24, HoTextFriendNear, lstrlen(HoTextFriendNear) );

		j2=-1;
		for(i= 0; i < 7; i++) {

			if(cN_Pressf==0)
				j=-1;
			else
				j = cN_Pressf-3;

			if(cN_PressfDBL && cN_PressfDBL_Where== 0)
				j2 = cN_PressfDBL-3;




			
			if(j2 == i){		//´­¸°°Å
				SetTextColor( hdc, RGB(255, 0, 0));
			}
			else if(j == i){		//´­¸°°Å
				SetTextColor( hdc, RGB(255, 200, 100));
			}
			else {
				SetTextColor( hdc, RGB(255, 255, 255));
			}

			dsTextLineOut(hdc, menuPos[mSu  ].left, menuPos[mSu  ].top, latestb[i], lstrlen(latestb[i]));


			mSu++;
		}



	}
	else if(cN_MenuN == 1) {

		int max = (fNameSu/7);
		if(fNameSu%7) max++;

		int min = (fNameS/7);
		if(fNameSu) min++;


		char buf[128];
		//wsprintf(buf, "[Ä£±¸¸ñ·Ï] %d/%d", min, max  );
		wsprintf(buf, HoTextFriendList , min, max  );

		SetTextColor( hdc, RGB(255, 220, 0));
		dsTextLineOut(hdc, menuPos[mSu  ].left+15, menuPos[mSu  ].top-24, buf, strlen(buf) );

		
		for(i= fNameS; i < fNameE; i++) {
			j=-1;
			if(cN_Pressf) {
				j = cN_Pressf-3;
				j += fNameS;
			}
			j2=-1;
			if(cN_PressfDBL && cN_PressfDBL_Where== 1) {
				j2 = cN_PressfDBL-3;
			}

			if(j2 == i){		//´­¸°°Å
				SetTextColor( hdc, RGB(255, 0, 0));
			}
			else if(j == i){		//´­¸°°Å
				SetTextColor( hdc, RGB(255, 200, 100));
			}
			else 
				SetTextColor( hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, menuPos[mSu  ].left, menuPos[mSu  ].top, fNameb[i], lstrlen(fNameb[i]));

			mSu++;
		}


	}
	else {
		char buf[128];
		int max = (dNameSu/7);
		if(dNameSu%7) max++;

		int min = (dNameS/7);
		if(dNameSu) min++;

		//wsprintf(buf, "[°ÅºÎÀÚ¸ñ·Ï] %d/%d", min, max  );
		wsprintf(buf, HoTextFriendRefuse , min, max  );

		SetTextColor( hdc, RGB(255, 220, 0));
		dsTextLineOut(hdc, menuPos[mSu  ].left+10, menuPos[mSu  ].top-24, buf, strlen(buf) );

		if(dNameS>13){
			dNameS = dNameS;
		}

		for(i= dNameS; i < dNameE; i++) {

			j = -1;
			if(cN_Pressf) {
				j = cN_Pressf-3;
			}

			if(j == i){		//´­¸°°Å
				SetTextColor( hdc, RGB(255, 200, 100));
			}
			else 
				SetTextColor( hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, menuPos[mSu  ].left, menuPos[mSu  ].top, dNameb[i], lstrlen(dNameb[i]));

			mSu++;
		}

	}


	if(oldFont)
		SelectObject( hdc, oldFont);
	renderDevice.lpDDSBack->ReleaseDC(hdc);
	//µ¿·á->Ä£±¸ id ±×¸°´Ù. ======================================end



	//µ¿·á->Ä£±¸id¿·ÀÇ LOG on offÇ¥½Ã ===========================start
	mSu = 3;

	if(cN_MenuN == 0) {	
		
		j = cN_PressfDBL-3;
		for(i= 0; i < 7; i++) {
	
			if( latestb[ i ][0]==0) goto jmp10;	//ÀÌ¸§ÀÌ ¾ø´Ù¸é..


			if(cN_PressfDBL && cN_PressfDBL_Where== 0) {
				if(j==i) {
					DrawSprite(	menuPos[mSu  ].left - 23, menuPos[mSu  ].top-3, 
						butt_Bmp[ 53 ],  0, 0, 16, 16,1);
					goto jmp10;
				}
			}



			/*
			if(latestb_LOG[i] ) 
				DrawSprite(	menuPos[mSu  ].left - 18, menuPos[mSu  ].top-2, 
							butt_Bmp[ 4 ],  0, 0, 16, 16,1);
			else 
				DrawSprite(	menuPos[mSu  ].left - 18, menuPos[mSu  ].top-2, 
							butt_Bmp[ 3 ],  0, 0, 16, 16,1);
			*/

			//ÀÌ°Ç ±×³É ÇìµåÆù¾´ ¸ð¾ç¸¸ ³ª¿Â´Ù.
			DrawSprite(	menuPos[mSu  ].left - 23, menuPos[mSu  ].top-5, 
					butt_Bmp[ 52 ],  0, 0, 20, 20,1);
	jmp10:

			mSu++;
		}
	}



	if(cN_MenuN == 1) {	
		
		for(i= fNameS; i < fNameE; i++) {
	
			if( fNameb[ i ][0]==0) goto jmp11;


			if(cN_PressfDBL && cN_PressfDBL_Where== 1) {
				j = cN_PressfDBL-3;
				if(j==i) {
					DrawSprite(	menuPos[mSu  ].left - 23, menuPos[mSu  ].top-3, 
						butt_Bmp[ 53 ],  0, 0, 16, 16,1);
					goto jmp11;
				}
			}


			//if(fName_LOG[i] )		//ktj : ÀÏ´Ü Áö¿ø¾ÈÇÏ°í ÄÑÀÖ°ÔÇÔ.
				DrawSprite(	menuPos[mSu  ].left - 23, menuPos[mSu  ].top-2, 
							butt_Bmp[ 4 ],  0, 0, 16, 16,1);
			//else 
			//	DrawSprite(	menuPos[mSu  ].left - 23, menuPos[mSu  ].top-2, 
			//				butt_Bmp[ 3 ],  0, 0, 16, 16,1);

	jmp11:		

			mSu++;
		}
	}

	if(cN_MenuN == 2) {	

		for(i= dNameS; i < dNameE; i++) {
			if( dNameb[ i ][0]==0) goto jmp12;

			//if(dName_LOG[i]) //ktj : ÀÏ´Ü Áö¿ø¾ÈÇÏ°í ÄÑÀÖ°ÔÇÔ.
				DrawSprite(	menuPos[mSu  ].left - 23, menuPos[mSu  ].top-2, 
							butt_Bmp[ 2 ],  0, 0, 16, 16,1);
			//else 
			//	DrawSprite(	menuPos[mSu  ].left - 23, menuPos[mSu  ].top-2, 
			//				butt_Bmp[ 3 ],  0, 0, 16, 16,1);

	jmp12:
			mSu++;
		}
	}
	//µ¿·á->Ä£±¸id¿·ÀÇ LOG on offÇ¥½Ã ===========================end

	return TRUE;


	//ktj : Ãß°¡
menu_clanList:

	void CLANmenu_ChatList_Draw();
	CLANmenu_ChatList_Draw();

	return TRUE;

}









//sw=0, 1 //½ºÅ©·Ñ ¾ÈÇÏ°í »ç¿ë½ÃºÎ¸¥´Ù.
int HoParty_KTJ::Main_menuSet(int sw)
{
	PmenuN = sw;
	BackStartPos.x = 539;
	PartyPosState = PARTY_PROCESS;
	menuSet(PmenuN);
	return 1;
}





void but_exit_chk()
{
	extern int ret_menuN;
	ret_menuN  = 0;
	InterfaceParty_KTJ.PmenuN=2;
}




int HoParty_KTJ::Main(int sw)
{
	int i;
	char namebuf[256];



	PartyPosState = sw;


	if(PartyPosState == PARTY_START)
	{
		

		//µ¿·á ¸Þ´º¿­°æ¿ì ÆÄÆ¼¿¡ »ç¶÷ÀÌ ¾øÀ¸¸é Ä£±¸¸Þ´º·Î ¹Ù²Û´Ù.
		if(PmenuN==1 && PartyMember[0].Name[0]==0)
			PmenuN  = 2;


		//BackStartPos.x-= 15;
		BackStartPos.x-= 20;
		//if(BackStartPos.x <= 549)
		if(BackStartPos.x <= 539)
		//if(BackStartPos.x <= xLeft)
		{
			//BackStartPos.x = 549;
			BackStartPos.x = 539;
			//BackStartPos.x = xLeft;
			PartyPosState = PARTY_PROCESS;
		}
		menuSet(PmenuN);




		for(i=0; i<8; i++) {
			b_Nflag[i] = 0;	//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.
			b2_Nflag[i] = 0;	//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.

			if(i<5)
				qN_flag[i] = 0;
		}



		//TextStartPos.x = BackStartPos.x+102;		
	}
	else if(PartyPosState == PARTY_END)
	{
		
		//BackStartPos.x += 15;
		BackStartPos.x += 20;
		if(BackStartPos.x >= 800)
		//if(BackStartPos.x >= xRight)
		{
			MouseDownPartyMember = -1;
			MouseDownButton = -1;
			BackStartPos.x = 800;
			//BackStartPos.x = xRight;
			PartyPosState = PARTY_NONE;


			qN_Pressf_CLEAR();
		}
		//TextStartPos.x = BackStartPos.x+102;
		//menuSet(PmenuN);
		
	}
	


	switch(sw) {
	case PARTY_START:
		break;

	case PARTY_PROCESS:

		for(i=0; i<8; i++) {
			b_Nflag[i] = 0;	//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.
			b2_Nflag[i] = 0;	//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.

			if(i<5)
				qN_flag[i] = 0;
		}


		i = chkeckMenuN();

		//ÆÄÆ¼¸Þ´º¹øÈ£
		if(PmenuN==0) {			//0:Äù½ºÆ®¸Þ´º
			switch(i) {
			case 3:				//Äù½ºÆ®¸Þ´ºÀÇ ¾Æ·¡¹öÆ°µé
			case 4:
			case 5:
			case 6:
			case 7:
				b_Nflag[i-3] = 1;	//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.
				break;

			case 8:				//Äù½ºÆ®ÀÇ ÀÌ¸§µé(1Â÷Àü¾÷½ÃÇè, ½ºÅ³¸¶½ºÅÍÇÏ±âµîÀÇ Äù½ºÆ®ÀÌ¸§ÀÓ)
			case 9:
			case 10:
			case 11:
			case 12:
				qN_flag[i-8] = 0;	//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.
				break;

			//============================================= Äù½ºÆ®ÀÇ ¿ÞÂÊ¸Þ´ºÀÇ ¹öÆ°µé === start
			case 13:
				//b2_Nflag[ (i-13) ] = 1;	//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.
				break;
			case 14:	//left ¹öÆ°ÀÓ.
				b2_Nflag[ (i-13) ] = 1;	
				break;
			case 15:	//right ¹öÆ°ÀÓ.
				b2_Nflag[ (i-13) ] = 1;	
				break;
			case 16:
				b2_Nflag[ (i-13) ] = 1;	
				break;
			//============================================= Äù½ºÆ®ÀÇ ¿ÞÂÊ¸Þ´ºÀÇ ¹öÆ°µé === end
			}

			if(MouseButton[0])			//´­·¶À»°æ¿ì
			{		
				if(i!= -1)
            		MouseButton[0]=0;
				switch(i) {
				case -1: break;			//Á¦´ë·Î ¾È´­¸¥°ÍÀÓ.
				case 0:	break;			//ÇìµåºÎºÐÀÇ Äù½ºÆ®, µ¿·á, Ã¤ÆÃ ´©¸§
				case 1:
				case 2:
					PmenuN=i;
					menuSet(PmenuN);		//¸Þ´º°¡ Æ²·Á¼­ ´Ù½Ã ¼ÂÆÃÇÔ.
					break;


				case 3:					//Äù½ºÆ®¸Þ´ºÀÇ ¾Æ·¡¹öÆ°µé

					if(questSelN == 5) {
						qNameS -= 8;
						if(qNameS<0)qNameS=0;
						qNameE = qNameS+5;
					}
					else {
						qNameS_ENDs -= 8;
						if(qNameS_ENDs<0)qNameS_ENDs=0;
						qNameE_ENDs = qNameS_ENDs+5;
					}

					break;
				case 4:		//right ¹öÆ°ÀÓ.
					if(questSelN == 5) {
						qNameS += 8;
						if(qNameb[qNameS ][0] == 0){		//°ø¹éÀÌ¸é ¿ø·¡´ë·Î µ¹¸°´Ù.
							qNameS-=8;
						}
						qNameE = qNameS+5;
					}
					else {

						qNameS_ENDs += 8;
						if(qNameb_E[qNameS ][0] == 0){		//°ø¹éÀÌ¸é ¿ø·¡´ë·Î µ¹¸°´Ù.
							qNameS_ENDs-=8;
						}
						qNameE_ENDs = qNameS_ENDs+5;

					}

					break;





					//=======ÁøÇàÇÏ´Â°÷
				case 5:		//ÁøÇà
					if(questSelN == 5) break;		//¿ø·¡ ´­·ÁÀÖÀ¸¸é ¾ÈÇÔ.
					questSelN = 5;
					qN_Pressf = 0;

					break;


				case 6:		//¿Ï¼ö
					if(questSelN == 6) break;		//¿ø·¡ ´­·ÁÀÖÀ¸¸é ¾ÈÇÔ.
					//if(qN_Pressf==0) 
						questSelN = 6;
						qN_Pressf = 0;
					break;

				case 7:
					//³ª°¡±â¹öÆ°´©¸¥°æ¿ìÀÓ.
					qN_Pressf=0;				//¿·¿¡ ³ª¿ÂÃ¢ ¾ø¾Ø´Ù.
					return PARTY_END;
					
				//==== Äù½ºÆ®ÀÇ ÀÌ¸§µé(1Â÷Àü¾÷½ÃÇè, ½ºÅ³¸¶½ºÅÍÇÏ±âµîÀÇ Äù½ºÆ®ÀÌ¸§ÀÓ) start
				case 8:					
				case 9:
				case 10:
				case 11:
				case 12:
					if(questSelN == 5) 
					{				
						if(qNameb[ qNameS + (i-8) ][0]==0)	break;	//ÀÌ¸§ÀÌ ¾øÀ¸¸é ¾ÈÇÑ´Ù
						if(qN_Pressf==i) {
							qN_Pressf=0;	break;
						}
						qN_Pressf = i;

						//Äù½ºÆ®ÀÇ ÀÌ¸§À» ¼¼ÀÌºêÇØ ¿ÞÂÊÇØ¼³¸Þ´º¿¡ ³Ö´Â´Ù.
						strcpy( q_explationTitle, qNameb[ qNameS + (i-8) ]);
						
						//Äù½ºÆ® ÇØ¼³ÆÄÀÏÀ» ¸Þ¸ð¸®¿¡ ³Ö´Â´Ù.
						wsprintf(namebuf, ".\\image\\party\\party_DATA\\%s", qFnameb[   qNameS + (i-8)  ]);
						if(ReadFileData(namebuf) == 0) {
							ReadFileData(".\\image\\party\\party_DATA\\quest_imsi.txt");	//ÆÄÀÏÀÌ ¾øÀ»¶§..
						}
						ZeroMemory((void *)q_explation, sizeof(q_explation));
						ReadFileData_moveBuf( (char *)q_explation, 128 );


					}
					else {

						if(qNameb_E[ qNameS_ENDs  + (i-8) ][0]==0)	break;	//ÀÌ¸§ÀÌ ¾øÀ¸¸é ¾ÈÇÑ´Ù
						if(qN_Pressf==i) {
							qN_Pressf=0;	break;
						}
						qN_Pressf = i;

						//Äù½ºÆ®ÀÇ ÀÌ¸§À» ¼¼ÀÌºêÇØ ¿ÞÂÊÇØ¼³¸Þ´º¿¡ ³Ö´Â´Ù.
						strcpy( q_explationTitle, qNameb_E[ qNameS_ENDs  + (i-8) ]);
						
						//Äù½ºÆ® ÇØ¼³ÆÄÀÏÀ» ¸Þ¸ð¸®¿¡ ³Ö´Â´Ù.
						wsprintf(namebuf, ".\\image\\party\\party_DATA\\%s", qFnameb_E[   qNameS_ENDs  + (i-8)  ]);
						if(ReadFileData(namebuf) == 0) {
							ReadFileData(".\\image\\party\\party_DATA\\quest_imsi.txt");	//ÆÄÀÏÀÌ ¾øÀ»¶§..
						}
						ZeroMemory((void *)q_explation, sizeof(q_explation));
						ReadFileData_moveBuf( (char *)q_explation, 128 );
					}



					break;
				//==== Äù½ºÆ®ÀÇ ÀÌ¸§µé(1Â÷Àü¾÷½ÃÇè, ½ºÅ³¸¶½ºÅÍÇÏ±âµîÀÇ Äù½ºÆ®ÀÌ¸§ÀÓ) end


				//============================================= Äù½ºÆ®ÀÇ ¿ÞÂÊ¸Þ´ºÀÇ ¹öÆ°µé === start
				case 13:
					break;

				case 14:	//left ¹öÆ°ÀÓ.
					if(qN_Pressf==0) break;
					q_explationS -= 8;
					if(q_explationS<0)q_explationS=0;
					break;
				case 15:	//right ¹öÆ°ÀÓ.
					if(qN_Pressf==0) break;

					q_explationS += 8;
					if(q_explation[ q_explationS ][0] == 0){		//°ø¹éÀÌ¸é ¿ø·¡´ë·Î µ¹¸°´Ù.
						q_explationS-=8;
					}
					break;
				case 16:
					b2_Nflag[ (i-13) ] = 1;

					qN_Pressf=0;//¿ÞÂÊÃ¢¿¡¼­ ºüÁ®³ª°£´Ù.
					break;
				//============================================= Äù½ºÆ®ÀÇ ¿ÞÂÊ¸Þ´ºÀÇ ¹öÆ°µé === end
				}
			}

		}
		else if(PmenuN==1)		//1:µ¿·á
		{
			switch(i) {
			case 3:				//ÆÄÆ¼¸Þ´ºÀÇ ¾Æ·¡¹öÆ°µé
			case 4:
			case 5:
			case 6:
			case 7:
				b_Nflag[i-3] = 1;	//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.
				break;
			}

			if(MouseButton[0]) {		//´­·¶À»°æ¿ì
				//if(i!= -1)
            	//	MouseButton[0]=0;
				
				switch(i) {
				case -1: break;		//Á¦´ë·Î ¾È´­¸¥°ÍÀÓ.
				case 1:	break;
				case 0:				//ÇìµåºÎºÐÀÇ Äù½ºÆ®, µ¿·á, Ã¤ÆÃ ´©¸§
				case 2:
				case 8:
					if(i==8) i=3;	//ktj : ¸¶Áö¸·¿¡ ³ÖÀº°Å¶ó 3À¸·Î °íÄ§
					PmenuN=i;
					menuSet(PmenuN);	//¸Þ´º°¡ Æ²·Á¼­ ´Ù½Ã ¼ÂÆÃÇÔ.

					
					break;


				case 3:				//ÆÄÆ¼¸Þ´ºÀÇ ¾Æ·¡¹öÆ°µé
				case 4:
				case 5:
				case 6:	//Å»Åð¹öÆ°
					//MouseButton[0]=0;
					break;
				case 7:	//³ª°¡±â¹öÆ°´©¸¥°æ¿ìÀÓ.
					MouseButton[0]=0;
					return PARTY_END;
				}
			}


		}
		else if(PmenuN==2)		//2:Ä£±¸
		{
			//Ä£±¸ ¸Þ´º ºÎºÐ ================ start
			switch(i) {
			case 3:				//Ä£±¸ÀÇ idµé
			case 4:

			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				break;




			case 17:
			case 18:				//Ã¤ÆÃ¸Þ´ºÀÇ ¾Æ·¡¹öÆ°µé
			case 19:

			case 20:
			case 21:
			case 22:
			case 23:
				b_Nflag[i-17] = 1;	//¸¶¿ì½º°¡ À§¿¡ ÀÖ´ÂÁöÀÇ ¿©ºÎ¸¦ 0À¸·Î ÇÑ´Ù.
				break;
			}









			if(MouseButton[0]) {		//´­·¶À»°æ¿ì
				if(i!= -1)
            		MouseButton[0]=0;
				switch(i) {
				case -1: break;		//Á¦´ë·Î ¾È´­¸¥°ÍÀÓ.
				case 2:  break;
				case 0:				//ÇìµåºÎºÐÀÇ Äù½ºÆ®, µ¿·á, Ã¤ÆÃ ´©¸§
				case 1:
				case 24:
					if(i==24) i=3;	//ktj : ¸¶Áö¸·¿¡ ³ÖÀº°Å¶ó 3À¸·Î °íÄ§
					if(cN_PressfDBL != 0) break;

					PmenuN=i;
					menuSet(PmenuN);	//¸Þ´º°¡ Æ²·Á¼­ ´Ù½Ã ¼ÂÆÃÇÔ.
					break;


				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:	//Ã¤ÆÃ..´­¸°°Å idºÎºÐÀÓ.
					//cN_Pressf = i;
					chat_cN_Pressf(i);	//cN_Pressf ´­¸°¹øÈ£ ¼ÂÆÃ(ºó ºÎºÐÀº ¼ÂÆÃÀÌ ¾ÈµÇ±â ¶§¹®ÀÓ
					break;

				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16:	//id¾ÕÀÇ Ç¥½Ã
					chat_WhisperPartyPlayer( (i-10)+3);
					break;




				case 17:			//ÃÖ±Ù¸ñ·Ï
					cN_MenuN = 0;
					cN_Pressf = 0;
					break;
				case 18:			//Ä£±¸ ¸ñ·Ï
					cN_MenuN = 1;
					cN_Pressf = 0;
					
					break;
				case 19:
					cN_MenuN = 2;	//°ÅºÎÀÚ¸ñ·Ï
					cN_Pressf = 0;
					break;
			
				case 20:			//Ã¤ÆÃÀÇ ÆäÀÌÁö¹Ù²Þ¹öÆ° left
					//if(cN_PressfDBL != 0) break;
					chat_PageChange(0);
					cN_Pressf = 0;
					break;
				case 21:			//Ã¤ÆÃÀÇ ÆäÀÌÁö¹Ù²Þ¹öÆ° right     , Ä£±¸¸ñ·Ïµî·Ï¿ëÀÇ 2°¡Áö¿ëµµ
					//if(cN_PressfDBL != 0) break;
					chat_PageChange(1);

					chat_IDinsert(1, NULL);	//cN_MenuN==0 ÀÏ¶§¸¸ Ä£±¸µé¸ñ·Ï¿¡ µî·Ï¿ëÀ¸·Î »ç¿ëµÊ
					cN_Pressf = 0;
					break;

				case 22:	//»èÁ¦			, °ÅºÎÀÚ¸ñ·Ïµî·Ï¿ëÀÇ 2°¡Áö¿ëµµ
					chat_IDdelete();

					chat_IDinsert(2, NULL);	//cN_MenuN==0 ÀÏ¶§¸¸ Ä£±¸µé¸ñ·Ï¿¡ µî·Ï¿ëÀ¸·Î »ç¿ëµÊ
					//chat_IDinsert(3, "¿È¸¶³Ä3");	//cN_MenuN==0 ÀÏ¶§¸¸ Ä£±¸µé¸ñ·Ï¿¡ µî·Ï¿ëÀ¸·Î »ç¿ëµÊ
					cN_Pressf = 0;
					cN_PressfDBL = 0;
					break;
				case 23:	//´Ý±â
					cN_Pressf = 
					cN_PressfDBL = 0;
					return PARTY_END;
				}
			}


			
			
			//±Í¸» º¸³»±â...
			if(MouseDblClick)
			{
				switch(i) {
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:	//Ã¤ÆÃ..´­¸°°Å
					//cN_Pressf = i;
					//chat_cN_Pressf(i);	//cN_Pressf ´­¸°¹øÈ£ ¼ÂÆÃ(ºó ºÎºÐÀº ¼ÂÆÃÀÌ ¾ÈµÇ±â ¶§¹®ÀÓ
					//WhisperPartyPlayer("¿È¸¶´Ï¾Æ");
					chat_WhisperPartyPlayer(-1);
					MouseDblClick=0;					
					break;



				}
			}
			//Ä£±¸ ¸Þ´º ºÎºÐ ================ end
		}
		else {	//if(PmenuN==3)		//Å¬·£¿ø¸®½ºÆ®

			void CLANmenu_ChatList_Main();
			CLANmenu_ChatList_Main();
			extern int ret_menuN;
			switch(ret_menuN ) 
			{
			case 1:		//Ä£±¸
			case 2:		//µ¿·á
				PmenuN=ret_menuN ;
				menuSet(PmenuN);		//¸Þ´º°¡ Æ²·Á¼­ ´Ù½Ã ¼ÂÆÃÇÔ.
				break;
			case 3:						//º» ¸Þ´º¸¦ ´Ý´Â´Ù.

				ret_menuN  = 0;
				PmenuN=2;
				//³ª°¡±â¹öÆ°´©¸¥°æ¿ìÀÓ.
				MouseButton[0]=0;

				void cN_PressfDBL_clear();	//ce_chatlist.cppÀÇ º¯¼öÅ¬¸®¾î
				cN_PressfDBL_clear();
				return PARTY_END;
			}
		}

		//¿©±â´Â ¸¶¿ì½º°¡ ¸Þ´ºÀÇ Çìµå¸¦ ´­·¯ Äù, µ¿, Ã¤ ¼±ÅÃÇÏ´Â ºÎºÐ ========== end
		
		break;

	case PARTY_END:
		break;
	}

	return TRUE;
}



//ktj : ÁÖÀÇ : ÀÌÇÔ¼ö´Â »ç¿ë¾ÈÇÔ.
int HoParty_KTJ::AddMember(char *memberName,DWORD chrCode, int life, int level)
{
	if(memberName == NULL)
		return FALSE;
	
	if(PartyMemberCount >= MAX_PARTY_MEMBER)
		return FALSE;
	memcpy(PartyMember[PartyMemberCount].Name, memberName, strlen(memberName));
	PartyMember[PartyMemberCount].ChrCode = chrCode;
	PartyMember[PartyMemberCount].Life = life;
	PartyMember[PartyMemberCount].Level = 100;
	PartyMemberCount++;
	return TRUE;
}


//ktj : »õ·Î ¸¸µê. ============== start
int HoParty_KTJ::AddMember(hoPartyMember *member,int cnt)
{
	PartyMember[cnt].ChrCode = member->ChrCode;
	PartyMember[cnt].Life  = member->Life;
	PartyMember[cnt].Level = member->Level;
	PartyMember[cnt].CharacterPos.x = member->CharacterPos.x;
	PartyMember[cnt].CharacterPos.z = member->CharacterPos.z;
	PartyMember[cnt].CharacterPos.y = member->CharacterPos.y;
	lstrcpy( PartyMember[cnt].Name , member->Name );
	lstrcpy( PartyMember[cnt].ModelName1 , member->ModelName1 );
	lstrcpy( PartyMember[cnt].ModelName2 , member->ModelName2 );
	PartyMember[cnt].JangFlag = member->JangFlag ;
				
	return TRUE;
}

void HoParty_KTJ::AddMember_memberSu(int memberSu)
{
    PartyMemberCount = memberSu;
}

int HoParty_KTJ::PARTY_PLAYUPDATE(hoPartyMember *member,int cnt)
{
	if ( PartyMember[cnt].ChrCode==member->ChrCode) {
		PartyMember[cnt].Life  = member->Life;
		PartyMember[cnt].Level = member->Level;
		PartyMember[cnt].CharacterPos.x = member->CharacterPos.x;
		PartyMember[cnt].CharacterPos.z = member->CharacterPos.z;
		return 1;
	}
	return 0;
}


int HoParty_KTJ::PARTY_RELEASE()
{
	PartyMemberCount = 0;
	MouseDownPartyMember = -1;

	if(PmenuN==0) return PmenuN;


	//ktj : Å¬·£ÀÇ ÈÙºÎºÐÅ¬¸®¾î
	void TJBscrollWheelClear_ChatL();
	TJBscrollWheelClear_ChatL();


	PartyPosState = PARTY_END;

	return PmenuN;
}
//ktj : »õ·Î ¸¸µê. ============== end




//ºÎ¼öÀû ÇÔ¼öµé ( ¸¶¿ì½º·Î ´©¸¥ ¸Þ´º ¹øÈ£ Ã½Å©)
int HoParty_KTJ::chkeckMenuN()
{
	int i;

	for(i=0; i<menuSu; i++) {
		if(  chkMenu(pCursorPos.x, pCursorPos.y, &menuPos[i])  ) {
			return i;
		}
	}
	return -1;
}









//Äù½ºÆ®ÀÇ ¼³¸í±ÛÀ» ³Ö´Â´Ù.
void HoParty_KTJ::Draw_questExplane(int x, int y)	//Äù½ºÆ®ÀÇ ¼³¸í±Û ±×¸®±â
{
	int i;
	HDC hdc;
	HFONT oldFont;

	//wsprintf(q_explationTitle, "Å¸ÀÌÆ²ÀÌ¾ß¿ä");
	renderDevice.lpDDSBack->GetDC(&hdc);
	SetBkMode( hdc, TRANSPARENT );

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject( hdc , hFont );

	
	SetTextColor( hdc, RGB(255, 190, 107));		//Çì´õÀÌ¸§
	dsTextLineOut(hdc, x+30, y-20, q_explationTitle, lstrlen(q_explationTitle));

	for(i= q_explationS; i < q_explationS +8; i++) {
		SetTextColor( hdc, RGB(255, 190, 107));
		dsTextLineOut(hdc, x, y, q_explation[i], lstrlen(q_explation[i]));
		y += 20;
	}
	if(oldFont)
		SelectObject( hdc, oldFont);
	renderDevice.lpDDSBack->ReleaseDC(hdc);
}


void HoParty_KTJ::Init_questExplane(char *string, int sw)	//Äù½ºÆ®ÀÇ ¼³¸í±Û ±×¸®±â
{
	if(sw==-1) {	//title¼ÂÆÃ
		wsprintf(q_explationTitle, string);
		return;
	}
	wsprintf(q_explation[sw], string);
}















/*///////////////////////////////////////////////////////////////////////////
: ÇÔ¼ö  ¸í :
: ÇÏ´Â  ÀÏ :  ÆÄÀÏÀ» ÀÌ¿ëÇÑ µð¹ö±ë¿ë
///////////////////////////////////////////////////////////////////////////*/

char QuestReadBuf[64*50];
//Äù½ºÆ®ÀÇ ¼³¸í±ÛÀÌ ÀÖ´Â ¹öÆÛ¿¡¼­ µ¥ÀÌÅ¸¸¦ ÀÐ¾î¼­ °¢ ÁÙ¿ë µ¥ÀÌÅ¸·Î ´Ù½Ã ¿Å±ä´Ù.
void HoParty_KTJ::ReadFileData_moveBuf(char *savebuf, int lineLen)	
{
	int i, bufC=0,cnt=0;
	char c;
	for(i=0; ; i++) {

		while(1) {
			c = QuestReadBuf[cnt++];
			
			if(c==0) break;	
			if(c==13) {
				cnt++;		//13, 10ÀÌ Ä³¸®Áö¸®ÅÏÀ¸·Î °°ÀÌ ÀÖÀ½.
				break;
			}
			savebuf[i*lineLen + bufC] = c;
			bufC++;
		}
		//fd2(&savebuf[i*lineLen]);

		bufC = 0;
		if(c==0) break;					//³¡ÀÌ¸é ³¡
	}
}



//Äù½ºÆ®ÀÇ ¼³¸í±ÛÀÇ µ¥ÀÌÅ¸¼ÂÆÃÇÔ¼öµé ================= start
int HoParty_KTJ::ReadFileData(char *fname)	//Äù½ºÆ®ÀÇ ¼³¸í±Û ±×¸®±â
{

	HANDLE hFile;
    DWORD dwAcess =0;
	hFile = CreateFile( fname, //"D:\\ÇÁ¼Ò½º2\\image\\party\\quest_imsi.txt", 
				GENERIC_READ , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );


	ZeroMemory((void*)QuestReadBuf, sizeof(QuestReadBuf));

    if( hFile != INVALID_HANDLE_VALUE ) {
		DWORD rbyte;
		int chk = ReadFile(hFile, (LPVOID)QuestReadBuf, sizeof(QuestReadBuf ), &rbyte, NULL);

        //ÆÄÀÏ ´Ý±â
        CloseHandle( hFile );
		return 1;
    }

	return 0;		//ÆÄÀÏ¾øÀ½.
}
//Äù½ºÆ®ÀÇ ¼³¸í±ÛÀÇ µ¥ÀÌÅ¸¼ÂÆÃÇÔ¼öµé ================= end




/*
//µ¿·áÀÇ µ¥ÀÌÅ¸¸¦ °ü·Ã ÇÔ¼ö ================= start
int HoParty_KTJ::Read_FriendData(char *fname)
{
	int i;
	HANDLE hFile;
    DWORD dwAcess =0;

	hFile = CreateFile( fname, 
				GENERIC_READ , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL );

	ZeroMemory((void*)QuestReadBuf, sizeof(QuestReadBuf));

    if( hFile != INVALID_HANDLE_VALUE ) {
		DWORD rbyte;
		//int chk = ReadFile(hFile, (LPVOID)QuestReadBuf, sizeof(QuestReadBuf ), &rbyte, NULL);

		DWORD fileH;
		DWORD fsize = GetFileSize(hFile, &fileH);
		if(fsize==0) {
			CloseHandle( hFile );
			return 0;
		}


		PartyMemberCount = fsize/sizeof(hoPartyMember);
		for(i=0; i<PartyMemberCount ; i++) {
			ReadFile(hFile, (LPVOID)&PartyMember[i], sizeof(hoPartyMember), &rbyte, NULL);
		}
		//hoPartyMember	PartyMember[MAX_PARTY_MEMBER];	//ÆÄÆ¼¸É¹ö Á¤º¸ ±¸Á¶Ã¼..
		//int				PartyMemberCount;				//ÇöÀç ÀÎ¿ø¼ö...

		//ÆÄÀÏ ´Ý±â
        CloseHandle( hFile );
		return 1;
    }

	return 0;		//ÆÄÀÏ¾øÀ½.
}

int HoParty_KTJ::Write_FriendData(char *fname)
{
	int i;
	HANDLE hFile;
    DWORD dwAcess =0;


	if(PartyMemberCount ==0){	
		CreateFile( fname, 
				GENERIC_WRITE , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, 
				TRUNCATE_EXISTING, //³ÖÀ» µ¥ÀÌÅ¸°¡ ¾øÀ¸¹Ç·Î ÆÄÀÏÀÌ ÀÖÀ¸¸é ¹«Á¶°Ç 0¹ÙÀÌÆ®·Î ¸¸µç´Ù.
				FILE_ATTRIBUTE_NORMAL , NULL );
		return 0;
	}



	hFile = CreateFile( fname, 
				GENERIC_WRITE , FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, 
				CREATE_ALWAYS, //ÆÄÀÏÀÌ ÀÖ¾îµµ ¹«Á¶°Ç µ¤¾î¾²±â
				FILE_ATTRIBUTE_NORMAL , NULL );

	ZeroMemory((void*)QuestReadBuf, sizeof(QuestReadBuf));

    if( hFile != INVALID_HANDLE_VALUE ) {
		DWORD rbyte;
		//int chk = ReadFile(hFile, (LPVOID)QuestReadBuf, sizeof(QuestReadBuf ), &rbyte, NULL);

		for(i=0; i<PartyMemberCount ; i++) {
			WriteFile(hFile, (LPVOID)&PartyMember[i], sizeof(hoPartyMember), &rbyte, NULL);
		}


		//ÆÄÀÏ ´Ý±â
        CloseHandle( hFile );
		return 1;
    }

	return 0;		//ÆÄÀÏ¾øÀ½.
}
//µ¿·áÀÇ µ¥ÀÌÅ¸¸¦ °ü·Ã ÇÔ¼ö ================= end
*/


/*==================================================================================
//
// ktj  : »õ·Î ¸¸µç°Í.													end
//
==================================================================================*/
































//ktj : ¾Æ·¡ ÀÌ°Ç ¸Ó´Ù³Ä????? ¸ô¸£°Í´Ù. ========================================

HoEffectHitBoard EffectHitBoard;

HoEffectHitBoard::HoEffectHitBoard()
{
	MatHitBackBoard = -1;
	MatHitCount = -1;
	
	memset(BufferNum, 0, sizeof(BufferNum));
}

HoEffectHitBoard::~HoEffectHitBoard()
{
	
}

void HoEffectHitBoard::Load()
{
	MatHitBackBoard  = CreateTextureMaterial( "Effect\\Etc\\HitBackBoard.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	MatHitCount		 = CreateTextureMaterial( "Effect\\Etc\\HitCount.tga"     , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	ReadTextures();
}


POINT BackSize[4]  = { {32, 32}, {32, 32}, {50, 50}, {80, 80}};
float BackSizeStepX = 0.f;
float BackSizeStepY = 0.f;
float BackAlphaStep = 0.f;
int   BackAlpha[4] = { 200, 200, 80, 0};
int	  Delay[4]     = { 5, 5, 5, 10};
int	  BackFrameCount = 0;
int   BackTimeCount;

POINT TextSize[4]  = { {10, 10}, {10, 10}, {20, 20}, {30, 30}};   
float TextSizeStepX = 0.f;
float TextSizeStepY = 0.f;
float TextAlphaStep = 0.f;
int   TextAlpha[4] = { 255, 255, 100, 0};
int	  TextDelay[4]     = { 5, 5, 5, 10};
int	  TextFrameCount = 0;
int   TextTimeCount;


POINT CriticalSize[4]  = { {70, 20}, {70, 20}, {70+70, 20+20}, {70+70*2, 20+20*2}};   
float CriticalSizeStepX = 0.f;
float CriticalSizeStepY = 0.f;
float CriticalAlphaStep = 0.f;
int   CriticalAlpha[4] = { 255, 255, 200, 0};
int	  CriticalDelay[4]     = { 30, 30, 8, 20};
int	  CriticalFrameCount = 0;
int   CriticalTimeCount;

int HoEffectHitBoard::Main()
{
	if(StartFlag)
	{
		if(CriticalFlag)
		{
			CriticalPutSizeX += CriticalSizeStepX;
			CriticalPutSizeY += CriticalSizeStepY;
			CriticalPutAlpha += CriticalAlphaStep;
			CriticalTimeCount++;

			if(CriticalTimeCount > CriticalDelay[BackFrameCount])
			{
				if(CriticalFrameCount == 3)
					CriticalFlag = FALSE;
				
				if(CriticalFrameCount != 3)
				{
					CriticalSizeStepX = (float(CriticalSize[CriticalFrameCount+1].x)-float(CriticalSize[CriticalFrameCount].x))/(float)CriticalDelay[CriticalFrameCount];
					CriticalSizeStepY = (float(CriticalSize[CriticalFrameCount+1].y)-float(CriticalSize[CriticalFrameCount].y))/(float)CriticalDelay[CriticalFrameCount];
					CriticalAlphaStep = (float(CriticalAlpha[CriticalFrameCount+1]-CriticalPutAlpha))/(float)CriticalDelay[CriticalFrameCount];
					CriticalFrameCount++;
				}
				CriticalTimeCount = 0;
			}
		}
		else
		{
			BackPutSizeX  += BackSizeStepX;
			BackPutSizeY  += BackSizeStepY;
			BackPutAlpha  += BackAlphaStep;
			BackTimeCount++;
			if(BackTimeCount >= Delay[BackFrameCount])
			{
				if(BackFrameCount != 3)
				{
					BackSizeStepX = (float(BackSize[BackFrameCount+1].x)-float(BackSize[BackFrameCount].x))/(float)Delay[BackFrameCount];
					BackSizeStepY = (float(BackSize[BackFrameCount+1].y)-float(BackSize[BackFrameCount].y))/(float)Delay[BackFrameCount];
					BackAlphaStep = (float(BackAlpha[BackFrameCount+1]-(float)BackAlpha[BackFrameCount]))/(float)Delay[BackFrameCount];
					BackFrameCount++;
				}
				BackTimeCount = 0;
			}

			TextPutSizeX  += TextSizeStepX;
			TextPutSizeY  += TextSizeStepY;
			TextPutAlpha  += TextAlphaStep;
			TextTimeCount++;
			if(TextTimeCount > TextDelay[TextFrameCount])
			{
				if(TextFrameCount == 3)
				{
					StartFlag = FALSE;
				}					
				
				if(TextFrameCount != 3)
				{
					TextSizeStepX = (float(TextSize[TextFrameCount+1].x)-float(TextSize[TextFrameCount].x))/(float)TextDelay[TextFrameCount];
					TextSizeStepY = (float(TextSize[TextFrameCount+1].y)-float(TextSize[TextFrameCount].y))/(float)TextDelay[TextFrameCount];
					TextAlphaStep = (float(TextAlpha[TextFrameCount+1]-(float)TextAlpha[TextFrameCount]))/(float)TextDelay[TextFrameCount];

					TextFrameCount++;
				}
				TextTimeCount = 0;
			}
		}
	}
	return TRUE;
}

int HoEffectHitBoard::Start(char *num, BOOL criticalFlag)
{
	BackFrameCount = 0;
	BackTimeCount  = 0;

	CriticalFrameCount = 0;
	CriticalTimeCount = 0;
	
	TextFrameCount = 0;
	TextTimeCount = 0;
	StartFlag = TRUE;
	
	BackPutSizeX = 64;
	BackPutSizeY = 64;
	BackPutAlpha = 255;

	TextPutSizeX = 10;
	TextPutSizeY = 10;
	TextPutAlpha = 255;
	
	CriticalPutSizeX = 70;
	CriticalPutSizeY = 20;
	CriticalPutAlpha = 255;

	BackSizeStepX = float((BackSize[BackFrameCount+1].x-BackSize[BackFrameCount].x)/Delay[BackFrameCount]);
	BackSizeStepY = float((BackSize[BackFrameCount+1].y-BackSize[BackFrameCount].y)/Delay[BackFrameCount]);
	BackAlphaStep = float((BackAlpha[BackFrameCount+1]-BackAlpha[BackFrameCount])/Delay[BackFrameCount]);
	
	TextSizeStepX = float((TextSize[BackFrameCount+1].x-TextSize[BackFrameCount].x)/TextDelay[TextFrameCount]);
	TextSizeStepY = float((TextSize[BackFrameCount+1].y-TextSize[BackFrameCount].y)/TextDelay[TextFrameCount]);
	TextAlphaStep = float((TextAlpha[BackFrameCount+1] -TextAlpha[BackFrameCount])/TextDelay[TextFrameCount]);
	
	if(criticalFlag)
	{
		CriticalSizeStepX = float((CriticalSize[CriticalFrameCount+1].x-CriticalSize[BackFrameCount].x)/CriticalDelay[CriticalFrameCount]);
		CriticalSizeStepY = float((CriticalSize[CriticalFrameCount+1].y-CriticalSize[BackFrameCount].y)/CriticalDelay[CriticalFrameCount]);
		CriticalAlphaStep = float((CriticalAlpha[CriticalFrameCount+1] -CriticalAlpha[BackFrameCount])/CriticalDelay[CriticalFrameCount]);
	}
	memset(BufferNum, 0, sizeof(BufferNum));
	wsprintf(BufferNum, "%s", num);

	CriticalFlag = criticalFlag;
	return TRUE;
}

int HoEffectHitBoard::Draw()
{
	int x = 725;
	int y = 50;
	

	if(StartFlag)
	{
		renderDevice.BeginScene();

		if(CriticalFlag == FALSE)
		{
			hoDrawTexImageFloat(MatHitBackBoard, x-BackPutSizeX/2+10, y-BackPutSizeY/2, BackPutSizeX, BackPutSizeY, 0, 0, 32.f, 32.f, 32.f, 32.f, (int)BackPutAlpha);
			
			int count;
			for(int index = 0; index < (int)strlen(BufferNum); index++)
			{
				count = 0;
				if(BufferNum[index] == '0')
					count = 9;
				if(BufferNum[index] == '1')
					count = 0;
				if(BufferNum[index] == '2')
					count = 1;
				if(BufferNum[index] == '3')
					count = 2;
				if(BufferNum[index] == '4')
					count = 3;
				if(BufferNum[index] == '5')
					count = 4;
				if(BufferNum[index] == '6')
					count = 5;
				if(BufferNum[index] == '7')
					count = 6;
				if(BufferNum[index] == '8')
					count = 7;
				if(BufferNum[index] == '9')
					count = 8;
				
				int size = (int)strlen(BufferNum);
				//Á¡¼ö Ãâ·ÂÇÏ´Â°÷..
				hoDrawTexImageFloat(MatHitCount, float(float(x+index*TextPutSizeX)-((float)size/2.f)*TextPutSizeX+10.f),
					-TextPutSizeY/2+y,
					TextPutSizeX, TextPutSizeY, 
					float(count*10), 0.f, 11.f, 14.f, 128.f, 64.f, (int)TextPutAlpha);
			}
		}
		else
		{
			//hoDrawTexImageFloat(MatHitCount, float(x-16), float(y-16), 70.f, 20.f, 0.f, 14.f, 128.f, 17.f, 128.f, 32.f, (int)BackPutAlpha);
			hoDrawTexImageFloat(MatHitCount, x-CriticalPutSizeX/2+20, float(y-16), CriticalPutSizeX, CriticalPutSizeY, 0.f, 14.f, 128.f, 17.f, 128.f, 64.f, (int)CriticalPutAlpha);
		}

		renderDevice.EndScene();
	}
	return TRUE;
}


