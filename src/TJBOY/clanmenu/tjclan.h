#ifdef USE_PROSTONTALE		//=========== «¡∏ÆΩ∫≈œº“Ω∫¿Œ∞ÊøÏ
#else
#include <windows.h>
#endif
//¿Ø¿˙¿« ≈¨∑£ø°º≠¿« «ˆ¿Á¿ßƒ°
#define CLANUSER					100		//¿œπ›¿Ø¿˙
#define CLANCHIP					101		//ØÖ
#define CLANNO_REGESTER				102		//π´µÓ∑œ¿⁄
#define CLAN_NOCONNECT				103		//ƒ¡≥ÿ∆Æ∞° æ»µ«º≠ º≥¡§∫“∞°
#define CLAN_SUBCHIP				104		//∫Œ≈¨∑£ƒ®





#define CLAN_NPC_START 0 //≈¨∑£NPC∏¶ ¥©∏£∏È Ω√¿€«œ¥¬ ∏ﬁ¥∫

#define CLANMESSAGEBUF_MAX 1024



#define CLAN_MAKE_is	1 //≈¨∑£ µÓ∑œ ¿«ªÁ ∞·¡§ ∏ﬁ¥∫
#define CLAN_MONEY_is	2 //≈¨∑£ ∏∏µÈ µ∑¡ˆ∫“ ∞·¡§ ∏ﬁ¥∫
#define CLAN_NAME_is	3 //≈¨∑£ ¿Ã∏ß ∏∏µÈ±‚ ∏ﬁ¥∫
#define CLAN_MARK_expl  4 //≈¨∑£ ∏∂≈© º≥∏Ì ∏ﬁ¥∫
#define CLAN_INSPECTION_expl	5 //≈¨∑£ Ω…ªÁ∏¶ æÀ∑¡¡÷¥¬ º≥∏Ì ∏ﬁ¥∫
#define CLAN_NAME_BEING         6
#define CLAN_MAKE_FINISH        7
#define CLAN_CHIP_ReadDATA		8 //ƒ®øÎ∏ﬁ¥∫∏¶ ¿ß«ÿ µ•¿Ã≈∏∏¶ √£¥¬¥Ÿ.
#define CLAN_NONAME	            9
#define CLAN_GO_MAKE			10
#define CLAN_GO_NPCSTART          11
#define CLAN_NotMake			254 //≈¨∑£¿ª ∏∏µÈ¡ˆ ∏¯«œ¥œ µπæ∆∞°∂Û
#define CLAN_AllEnd				255 //≈¨∑£«‘ºˆ∏¶ ≥™∞•∂ß ≤¿ µÈ∏Æ¥¬ ∏ﬁ¥∫
#define CLAN_ERROR				1000//ø°∑ØøÎ Ω∫∆Æ∏µ¿ª ∫∏ø©¡ÿ»ƒ µ«µπæ∆∞£¥Ÿ.




#define CLAN_CHECK_CLANMARK		200
#define CLAN_READ_CLANMARK		201
#define CLAN_REAMMAKR_ERROR       202  
#define CLANMAKE_REAMMAKR_ERROR       203  

#define CLAN_USER_DATA           300 //≈¨∑£ ¿Ø¿˙∑Œ ¿Ãµø Ω√ƒ—¡‹





//===============≈¨∑£ƒ® ∞¸∑√ µ∆ƒ¿Œ
#define CLAN_CHIP				20 //ƒ®
#define CLAN_WAREHOUSE			21 //√¢∞Ì
#define CLAN_WAREHOUSE_RIGHT		22 //√¢∞Ì ±««—
#define CLAN_MARK				23 //∏∂≈©
#define CLAN_MARK1				24
#define CLAN_MARK2				25
#define CLAN_MARK3				26
#define CLAN_REMOVE				27 //√ﬂπÊ
#define CLAN_RELEASE			28 //«ÿ√º
#define CLAN_HELP				29 //µµøÚ∏ª
#define CLAN_NOMAKE				30		//≈¨∑£ø¯¿Ã 6¿Œ ¿Ã«œ¿œ ∞ÊøÏ ∏ﬁ¥∫ √π∏”∏Æø° æÀ∑¡¡ÿ¥Ÿ
#define CLAN_HELP_CONTENT		31
#define CLAN_REMOVE_RESULT		32
#define CLAN_RECONF_RELEASE       33
#define CLAN_FINISH_RELEASE       34
#define CLAN_REMOVE_SHORTCLANWON   35
#define CLAN_RELEASE_LOADING       36
#define CLAN_REMOVE_SHORTCLANWON_LOADING 37
#define CLAN_REMOVE_LOADING        38
#define CLAN_REMOVE_SHORTCLANWON_RESULT   39 
//#define CLAN_RELEAE_BEFORE		35 //YGY:≈¨∑£ «ÿ√º«œ±‚ ¿¸ø° ≈¨∑£∞¸∑√ ¡§∫∏∏¶ ¿–æÓø¬¥Ÿ.

//===============≈¨∑£¿Ø¿˙ ∞¸∑√ µ∆ƒ¿Œ
#define CLAN_USER				40 //≈¨∑£ ±∏º∫ø¯
#define CLAN_JOIN				41 //≈¨∑£ ∞°¿‘
#define CLAN_SECESSION			42 //≈¨∑£ ≈ª≈
#define CLAN_USER_WAREHOUSE		43	//¿Ø¿˙øÎ √¢∞Ì
#define CLAN_USER_HELP			44
#define CLAN_USER_NOMAKE			45
#define CLAN_USER_HELP_CONTENT	46
#define CLAN_RECONF_SECESSION    47
#define CLAN_FINISH_SECESSION     48
#define CLAN_USER_NOMAKE_FLAG      49
#define CLAN_USER_FLAG            50
#define CLAN_USER_ReadDATA        51
#define CLAN_RECONF_SECESSION_LOADING     52

#define CLANUSER_RELEASEMESSAGE	53 //«ÿ√ºµ» ≈¨∑£ø¯
#define CLANUSER_GO_RELEASEMESSAGE 54
#define CLANUSER_RELEASE_FLAG		55

//√™∏ÆΩ∫∆Æ∏ﬁ¿Œ «√∑Ø±◊==========================================================
//#define CHATLIST_START           900 
#define CHATLIST_END			901
#define CHATLIST_ERROR			902
#define CHATLIST_READDATA		903
#define CLAN_DISPLAY_OPEN		904
#define CLAN_DISPLAY_END			905
#define CLAN_DISPLAY_INFO         906
#define CLAN_DISPLAY_CLOSE			907
#define CLAN_CLOSE_END_BEFORE			908
#define CLAN_CLOSE_ENDING             909
#define CHATLIST_READ_CLANMARK       910
#define CLAN_DISPLAY_BEFORE		911

//==============cldataæ˜µ•¿Ã∆Æ==================
#define UPDATE_ISCLANMEMBER           1003
#define UPDATE_CLANWON				1004
#define ISPFLAG_USER				1005
#define ISPFLAG_CHIP				1006
#define CLAN_isCheckClanJang_LOADING   1007
#define CLANCHIP_DOWN6_CLANWON_MESSAGE 1008
#define CLANSERVER_INSPECT		    1009
#define CLANSERVER_INSPECT_BEFORE      1010
#define CLANINFO_READMARK			1011
#define CLANINFO_DOWNLOAD			1012
#define CLANINFO_END				1013
#define CLANMAKE_DOWN_INFO			1014
#define CLANMAKE_READ_CLANMARK		1015
#define CLAN_isCheckClanJang_Result	1016	
#define CLANMAKE_NOMONEY				1017
#define CLANUSER_JOIN				1018
#define CLANUSER_REMOVE				1019 //≈¨∑£ø¯¿Ã √ﬂπÊ¥Á«ﬂ¿ª∞ÊøÏ
#define CLANUSER_AUTORELEASE			1020 //¿⁄µø«ÿ√º
#define MYCLAN_UPDATE				1021
#define MYCLAN_CLANMARK_UPDATE		1022
#define CLANCHIP_GO_RELEASEMESSAGE		1023
#define CLANCHIP_RELEASEMESSAGE		1024
#define CLANCHIP_RELEASE_FLAG			1025
#define CLANUSER_CHECKPFLAG			1026
#define CLAN_CLANWONOVER				1027 //≈¨∑£ø¯ºˆ √º≈©
#define CLAN_ABILITYDOWN				1028
#define CLAN_NOLEVEL				1029
#define CLAN_NOTICE					1030
#define CLAN_DRAWNOTICE				1031
#define CLAN_DRAWNOTICE_END			1032
//¿Ã¿”∞¸∑√========================START
#define CLANCHIP_LEAVECLAN			1033
#define CLANCHIP_LEAVECLAN_NOMONEY		1034
#define CLANCHIP_LEAVECLAN_SUCESS		1035
#define CLANCHIP_LEAVECLAN_CONFIRM		1036
#define CLANCHIP_LEAVECLAN_RECONFIRM	1037
#define CLANCHIP_LEAVECLAN_NOLEVEL		1038
#define CLANCHIP_LEAVECLAN_DO			1039
#define CLANCHIP_NOLEAVECLAN			1040
#define CLANCHIP_LEAVECLAN_PFLAG		1041
#define CLANCHIP_LEAVECLAN_MESSAGE		1042
#define CLANUSER_LEAVECLAN_MESSAGE		1043
#define CLANCHIP_LEAVECLAN_MESSAGEEND	1044
#define CLANUSER_LEAVECLAN_MESSAGEEND	1045  //
#define CLANCHIP_LEAVECLANDOWNLEVEL	1046  //≈¨∑£ø¯¿Ã ∑π∫ß¿Ã µ«¡ˆ æ æ∆º≠ ≈¨∑£ø¯¿ª πﬁæ∆µÈ¿œºˆ æ¯¿Ω
//=================================END


//∫Œ ≈¨∑£ƒ® ¿”∏Ì π◊ «ÿ¿”=====================START
#define CLANCHIP_SUBCHIP_LIST			1047  //≈¨∑£ø¯µÈ ∏ÆΩ∫∆Æ ∫∏ø©¡‹ ∫Œ ≈¨∑£ƒ®¿Ã ¿÷¿∏∏È µ˚∑Œ ∫∏ø©¡‹
#define CLANCHIP_RESUBCHIP_APPOINT		1048  //∫Œ ≈¨∑£ƒ® ¿”∏Ì ¿Á»Æ¿Œ
#define CLANCHIP_RESUBCHIP_APPOINT_END	1049  //∫Œ ≈¨∑£ƒ®¿”∏Ì ∏∂¡ˆ∏∑ ∏ﬁºº¡ˆ
#define CLANCHIP_RELEASESUBCHIP		1050  //∫Œ ≈¨∑£ƒ®«ÿ¿” ¿Á»Æ¿Œ
#define CLANCHIP_RELEASESUBCHIP_END	1051  //≈¨∑£∫Œƒ® «ÿ¿” ∏∂¡ˆ∏∑ ∏ﬁºº¡ˆ
#define CLANCHIP_APPOINTSUBCHIP_DO		1052  //≈¨∑£∫Œƒ® ¿”∏Ì ASP»£√‚
#define CLANCHIP_RELEASESUBCHIP_DO		1053  //≈¨∑£∫Œƒ® «ÿ¿” ASP»£√‚

#define CLANCHIP_SUBCHIP_APPOINTMSG	1054  //≈¨∑£∫Œƒß¿Ã ¿”∏Ìµ«¥Ÿ∞Ì «—π¯ ∫∏ø©¡‹
#define CLANCHIP_SUBCHIP_RELEASEMSG	1055  //≈¨∑£∫Œƒß¿Ã «ÿ¿”µ«¥Ÿ∞Ì «—π¯ ∫∏ø©¡‹
#define CLANUSER_SUBCHIP_APPOINTMSG	1056  //≈¨∑£∫Œƒß¿Ã ¿”∏Ìµ«¥Ÿ∞Ì «—π¯ ∫∏ø©¡‹
#define CLANUSER_SUBCHIP_RELEASEMSG	1057  //≈¨∑£∫Œƒß¿Ã «ÿ¿”µ«¥Ÿ∞Ì «—π¯ ∫∏ø©¡‹
#define CLANCHIP_SUBCHIP_APPOINT_FLAG	1058  //≈¨∑£∫Œƒß¿Ã ¿”∏Ìµ«æÓ¥Ÿ¥¬ «√∑°±◊ºº∆√
#define CLANCHIP_SUBCHIP_RELEASE_FLAG	1059  //≈¨∑£∫Œƒß¿Ã «ÿ¿”µ«æÓ¥Ÿ¥¬ «√∑°±◊ºº∆√

#define CLANCHIP_SUBCHIP_READMSG_FLAG	1060  //≈¨∑£¿Â¿Ã ∫Œƒ®¿Ã ¿”∏Ìµ«æÓ¥Ÿ¥¬ ∏ﬁºº¡ˆ∏¶ ¿–æ˙¿ª∂ß
#define CLANUSER_SUBCHIP_READMSG_FLAG	1061  //≈¨∑£¿Ø¿˙∞° ∫Œƒß∞¸∑√ ∏ﬁºº¡ˆ∏¶ ¿–æÓ¥Ÿ¥¬ «√∑°±◊ ºº∆√

#define CLANCHIP_SUBCHIP_LOAD			1062  //≈¨∑£øˆ∏ÆΩ∫∆Æ ∞ÆæÓø¿±‚(æ∆¡˜ ªÁøÎæ»«‘)
#define CLANCHIP_SUBCHIP_LOAD_DATA		1063
#define CLANCHIP_NOSUBCHIP			1064


//================================END
//∫Œƒ®¿Ã
#define CLANSUBCHIP_INSERTCLANWON		2000 //∫Œƒ®¿Ã ≈¨∑£ø¯√ﬂ∞°

#define CLANWON_MAX					100








#define CLAN_JOIN_before			60
//#define CLAN_JOIN				31
#define CLAN_JOIN_After			62

#define CLAN_JOIN_chip			63
#define CLAN_JOIN_chip_NO		64
#define CLAN_JOIN_chip_YES		65

//»£µøClan√ﬂ∞°
#define CLAN_IS_CHECK_MEMBER		100
#define CLAN_IS_CHECK_MEMBER_END	101


//√≥¿Ω Ω√¿€Ω√ ≈¨∑£∏‚πˆ¿Œ¡ˆ æ∆¥—¡ˆ∏¶ πÃ∏Æ æÀæ∆æﬂ«‘.
#define CLAN_isClanWon			66

#define CLAN_MAKE_examination		67		//≈¨∑£Ω…ªÁ«œ±‚
#define CLAN_isCheckClanJang      68       //∞∞¿∫ ∞Ë¡§ø° ≈¨∑£¿Â¿Ã ¿÷¥¬¡ˆ √º≈©
#define CLAN_LOADING			69
//===============≈¨∑£ ¡¢º”Ω√ ∞¸∑√ «√∑°±◊ ∏ﬁºº¡ˆ
#define CLANCHIP_MAKE_FIRSTMESSAGE     70    //√≥¿Ω ≈¨∑£¿ª ∏∏µÈæ˙¿ª∂ß ≈¨∑£¿Â¿Ã NPC∏¶ ≈¨∏Ø«ﬂ¿ª∂ß ∫∏ø©¡÷¥¬ ∏ﬁºº¡ˆ
//#define CLANUSER_MAKE_FIRSTMESSAGE     71    //√≥¿Ω ≈¨∑£¿ª ∏∏µÈæ˙¿ª∂ß ≈¨∑£±∏º∫ø¯¿Ã NPC∏¶ ≈¨∏Ø«ﬂ¿ª∂ß ∫∏ø©¡÷¥¬ ∏ﬁºº¡ˆ
#define CLANCHIP_DOWN6_CLANWON         71   //≈¨∑£ø¯¿Ã 6∏Ì ¿Ã«œ∑Œ ∂≥æÓ¡¸
#define CLANCHIP_BREAKCLAN            72

#define CLANUSER_MAKE_FIRSTMESSAGE    73
#define CLANUSER_DOWN6_CLANWON_MESSAGE  74
#define CLANUSER_DOWN6_CLANWON         75





#define BUTTONBOX_WIDTH   68
#define BUTTONBOX_HEIGHT  27
#define BUTTONTEXT_WIDTH  32
#define BUTTONTEXT_HEIGHT 16

#define BOX_MAX_WIDTH (((4 * BOXCENTER_WIDTH) + (2*BOXCORNER_WIDTH) + 5) )

#define ICON_START       55
#define ICON_ADD		 20
#define SCROLLBAR_LEFT    236
#define SCROOBAR_TOP	54
#define DISPLAY_MAX		8

//≈¨∑£ ¿Ã∏ß ¡¬«•
#define CLAN_NAME_POS_X     65
#define CLAN_NAME_POS_Y     8

//≈¨∑£ «Ô«¡ ∞¸∑√

#define CLANHELPICON_WIDTH   109
#define CLANHELPICON_HEIGHT   30
#define CLANHELPICON_CAP		 40
#define CLANHELPICON_START_Y   105
#define CLANHELPICON_DISPLAY_MAX		4
#define CLANHELPCONTENT_MARK_X   40
#define CLANHELPCONTENT_MARK_Y   40
#define CLANHELPCONTENT_X   100
#define CLANHELPCONTENT_Y   50
#define HELPWIDTH 256
#define HLEPDISPLAY_MAX		8
#define HELPCONTENT_X        19
#define HELPCONTENT_Y        56
#define HELPCONTENT_CAP      20
#define CLANCHIPHELPINF "image\\clanImage\\help\\ClanHelp.inf"
#define CLANUSERHELPINF "image\\clanImage\\help\\ClanUserHelp.inf"


#define SAVEDATA_DIR	"savedata"
#define CLANDATA_DIR   "savedata\\clanDATA"



//========================================================

#define BOXCORNER_WIDTH		64
#define BOXCORNER_HEIGHT		32
#define BOXCENTER_WIDTH		32
#define BOXCENTER_HEIGHT		32

//≈¨∑£ ∏∂≈© ¿Ã∏ß ¿ßƒ°
#define CLANNAME_X			54  
#define CLANNAME_Y			12

#define CLANNAME_WIDTH		152
#define CLANNAME_HEIGHT		28

#define CLANNAMETEXT_X       128
#define CLANNAMETEXT_Y		20

//≈¨∑£ ∏∂≈© π⁄ ¿ßƒ°
#define CLANMARKBOX_X		93 
#define CLANMARKBOX_Y		47

//≈¨∑£ ∏∂≈© ¿ßƒ°
#define CLANMARK_X		111
#define CLANMARK_Y		60

//BUTTONπ⁄Ω∫∞° «—∞≥ ¿œ∂ß ¡¬«•
#define BUTTON1_BOX_X			104
#define BUTTON1_BOX_Y			222

#define BUTTON1_X				BUTTON1_BOX_X + 9
#define BUTTON1_Y				BUTTON1_BOX_Y + 4

//BUTTONπ⁄Ω∫∞° µŒ∞≥ ¿œ∂ß ¡¬«•
#define BUTTON2_BOX_X			69
#define BUTTON2_BOX_Y			221

#define BUTTON2_X				BUTTON2_BOX_X + 9
#define BUTTON2_Y				BUTTON2_BOX_Y + 4

#define BUTTON3_BOX_X			139
#define BUTTON3_BOX_Y			221

#define BUTTON3_X				BUTTON3_BOX_X + 9
#define BUTTON3_Y				BUTTON3_BOX_Y + 4

//≈¨∑£ƒ® ∏ﬁ¿Œ ∏ﬁ¥∫
#define CLANCHIPMENU_RELEASE_X	104
#define CLANCHIPMENU_RELEASE_y	62

#define CLANCHIPMENU_REMOVE_X		104
#define CLANCHIPMENU_REMOVE_Y		92

//¿Ã¿”
#define CLANCHIPMENU_LC_X		104
#define CLANCHIPMENU_LC_Y		122
//µµøÚ∏ª
#define CLANCHIPMENU_HELP_X		104
#define CLANCHIPMENU_HELP_Y		182
//∫Œ≈¨∑£ƒ®
#define CLANCHIPMENU_SUBCHIP_X	104
#define CLANCHIPMENU_SUBCHIP_Y	152

//≈¨∑£ ∏ﬁ¥∫ ≈∏¿Ã∆≤
#define CLANTITLE_X				68
#define CLANTITLE_Y				12

//µµøÚ∏ª ∏Ò∑œ
#define CLANHELPLIST_X			68
#define CLANHELPLIST_Y			76

//√ﬂπÊ ≈¨∑£ø¯ ∏ÆΩ∫∆Æ ¿ßƒ°
#define CLANWONLIST_X			50
#define CLANWONLIST_Y			60

//≈¨∑£¿Ø¿˙ ≈ª≈
#define CLANUSER_SECESSION_X	64
#define CLANUSER_SECESSION_Y	127

#define CLANUSER_HELP_X			64
#define CLANUSER_HELP_Y			167

//≈¨∑£ ∞·º∫ ∞¸∑√ ≈ÿΩ∫∆Æ ¡¬«•
#define CLANMAKETEXT_X			25
#define CLANMAKETEXT_Y			40

#define LOADTEXT_X				70
#define LOADTEXT_Y				50

//≈¨∑£¿Â ∏ﬁ¥∫≈ÿΩ∫∆Æ ∞¸∑√
#define CLAN_RELEASE_X			60
#define CLAN_RELEASE_Y			80

#define CLAN_RECONF_RELEASE_X			30
#define CLAN_RECONF_RELEASE_Y			70

#define CLANNOMAKE_X		    30
#define CLANNOMAKE_Y		    60

#define CLANRELEASE_FINISH_X		50
#define CLANRELEASE_FINISH_Y		60

#define CLANUSERTEXT_X           45
#define CLANUSERTEXT_Y			60

#define CLANINPUTNAME_X			78
#define CLANINPUTNAME_Y			70


//========================================================




#define XCAP					20 // ≈ÿΩ∫∆Æ √‚∑¬Ω√ Ω√¿€«œ¥¬ x¿ßƒ°∞™ ∫∏¡§
#define YDOWN					-2  //≈ÿΩ∫∆Æ √‚∑¬Ω√ Ω√¿€«œ¥¬ y¿ßƒ°∞™ ∫∏¡§
#define REMOVE_ICON				20 //√ﬂπÊ æ∆¿Ãƒ‹ ¿ßƒ° ¿Ãµø
#define WHR_ICON				30
#define HELP1					"image\\Sinimage\\chipbutton\\help1.txt"
#define HELPMSG_MAX				256
#define CLANMARK_TXT_X           34
#define CLANMARK_TXT_Y           10
//≈©∑£ «Ô«¡πˆ≈œ¿« ≈ÿΩ∫∆Æ ¿ßƒ°
#define CLANHELPTEXT_Y               25
//≈¨∑£≈ÿΩ∫∆Æ ¿ÃπÃ¡ˆ √‚∑¬
#define CLANTEXT_IMAGE_X         68
#define CLANTEXT_IMAGE_Y          12
#define CLANTEXT_IMAGE_WIDTH         120
#define CLANTEXT_IMAGE_HEIGHT         30





#define CLANHELPICON_NUM		100




#define CHIP_BUTTON_X_MOVE		30
#define CHIP_BUTTON_Y_MOVE		20

#define MAKEMONEY 500000			//≈¨∑£∞·º∫¿ª ¿ß«ÿ 50∏∏ø¯« ø‰
#define CLANCHIP_LEAVECLAN_MONEY	300000
//#define MAKEMONEY 3000			//≈¨∑£∞·º∫¿ª ¿ß«ÿ 4∏∏ø¯« ø‰
#define ABILITY   10000 	        //≈¨∑£∞·º∫¿ª ¿ß«ÿ 10000 ¥…∑¬ƒ°∞° « ø‰
#define CLAN_MAKELEVEL  40		//≈¨∑£¿ª ∏∏µÈºˆ ¿÷¥¬ ∑π∫ß

//web db∑Œ ∫Œ≈Õ ¥‰∫Ø¿ª πﬁæ∆ ¿˙¿Â«œ¥¬∞˜.
typedef struct {
	int  ret_val;					//web dbø°º≠ ¿Ø¿˙¿« ≈¨∑£ø°º≠¿«¿ßƒ°(≈¨∑£¿Â,≈¨∑£ø¯,∞°¿‘æ»«‘)∞°¡Æø».
	char ret_Buf[2048];				//web db∏¶ ≈Î«ÿ µÈæÓø¬ Ω∫∆Æ∏µ¿ª ºº¿Ã∫Í«ÿµŒæ˙¥Ÿ∞° « ø‰«“∂ß ≤®≥ªæ≤±‚¿ß«—πˆ∆€


} ANSWERDATA;

typedef struct _tagMyClanInfoHeader
{
	char		ClanMark_Num[40];   //≈¨∑£ ∏∂≈© π¯»£
	int		nClanMark;
	char		ClanName[40];   //≈¨∑£ ¿Ã∏ß		
	char		ClanReport[90];
	char		Gserver[4];
	char		UniqueClaClanInfo_nNum[64];

	
}MYCLANINFOHEADER;

//=============================================º¯ºˆ ¿©µµøÎ
typedef struct {
	HBITMAP hb;
	void *pixBuf;
	char fname[64];
} DIBSectionBUF;


typedef struct {
	//===========================================================================================
	int  myPosition;			//100:¿œπ› ≈¨∑£ø¯ 101:≈¨∑£ØÖ  102:∞°¿‘æ»µ«æÓ¿÷¿Ω. 103: ≈¨∑£º≠πˆªÛ¿« ø°∑Ø
	
	int	 money;					//«ˆ¿Á ¿Ø¿˙∞° ∞°¡¯ µ∑
	int  ability;





	//≈¨∑£¿Â¿Ã ±«¿Ø«ÿº≠ ≈¨∑£ø¯¿∏∑Œ ∞°¿‘«“ ªÁ∂˜¿« id
	char clanJoinID[64];		
	char clanJoinCharID[64];
	int  clanJoinJob, clanJoinLevel;

	char chipCharID[64];		//≈¨∑£ø° ∞°¿‘¿ª ±«¿Ø«— ≈¨∑£ØÖ¿« id∏¶ ¿˙¿Â«ÿµ–¥Ÿ.

    //ygy:∞°¿‘¿ª ±«¿Ø«œ¥¬ ≈¨∑£∞˙ ≈¨∑£¿Â¿« ¡§∫∏∏¶ ¿œπ›¿Œ¿Ã ¿˙¿Â«‘
	char  szJoinClanName[64];		//¡∂¿Œ ≈¨∑£ ¿Ã∏ß
	char  szJoinClanChipName[64];   //¡∂¿Œ«œ¥¬ ≈¨∑£¿Â ¿Ã∏ß
			
	
	//===========================================================================================
	char name[20];				//≈¨∑£¿« ¿Ã∏ß
	char explanation[128];		//≈¨∑£¿« º≥∏Ì±€(«ˆ¿Á ≈¨∑£∏∏µÈ∂ß º¬∆√æ»«œ∞Ì ¿÷¿Ω.)
	
	//ygy
	char stats[2];
	char sec[30];
	char szRegiD[50];
	char  limitD[30];
	char  DelActive[10];
	char  gserver[30];
	char  szID[64];       //¿œπ› ∞Ë¡§	//¥Á ¿Ø¿˙¿« id : ∞‘¿”∏ﬁ¿Œø°º≠ πﬁæ∆ø».
	char  ChaName[64];    //ƒ≥∏Ø≈Õ ¿Ã∏ß //¥Á ¿Ø¿˙¿« ƒ≥∏Ø≈Õid : ∞‘¿”∏ﬁ¿Œø°º≠ πﬁæ∆ø».
	char  ClanZang_ID[64];
	char  ClanZang_Name[64];	
	char  ClanMark[64];	//100188

	int intClanMark;
	int nLastDay;  //≈¨∑£¿Ã µÓ∑œµ«±‚±Ó¡ˆ ≥≤¿∫ ≥Ø
	BOOL bIsOneDay;
	int	nMinute;
	int	nHour;
	
	int nCurrentClanWon_Num;  //«ˆ¿Á ≈¨∑£ø¯ºˆ [≈¨∑£¿Â ∆˜«‘]
	int nClanWon_Max;        //≈¨∑£ø¯ √÷¥Îºˆ
	
	

	//bmp¿Ã∏ß ≥÷¿ª∞Õ.


	//===========================================================================================
	char  clanWon[CLANWON_MAX][30];        //≈¨∑£º≠πˆø°º≠ ∫∏≥ª¡ÿ ≈¨∑£ø¯¿ª ¿˙¿Â(≈¨∑£¿Â ¡¶ø‹)
	int	 clanWonStrLen[41];      //∞¢ ≈¨∑£ø¯ πÆ¿⁄ø≠ ±Ê¿Ã
	char  szClanMarkName[50];     //≈¨∑£∏∂≈© ∫Ò∆Æ∏ ¿Ã∏ß
	int   nTotalClanWonCount;     //«ˆ¿Á ≈¨∑£ø¯ºˆ
	char  PFlag[5];             //≈¨∑£ √π »≠∏È «√∑°±◊
	char  LeaveClanFlag[5];       //kflag
	int	 nKFlag;				//kflag
	int   nKFlag_Count;
	char  OldChipChaName[64];
	char  SubChip[64];			//∫Œ ≈¨∑£ƒ®
	char	 OldSubChip[64];
	char	 isSubChip[2];

	//»£µøClan√ﬂ∞°
	smCHAR *TargetChar;        //Target Character


#ifdef USE_PROSTONTALE		//=========== ∆˜∏ÆΩ∫≈œº“Ω∫¿Œ∞ÊøÏ
	DIRECTDRAWSURFACE	hClanMark;
	DIRECTDRAWSURFACE	hClanMark16;

#else
	HBITMAP				hClanMark;
	HBITMAP				hClanMark16;
#endif


	//(status,StartMessageFlag) : 
	//(0,1) ≈¨∑£ ∞·º∫ √π ∏ﬁºº¡ˆ ∂ÁøÚ (0,2)≈¨∑£ ∞·º∫ √π∏ﬁºº¡ˆ ¿–¿Ω
	char  StartMessageFlag[1];      
	//end-ygy

 
	DWORD CNFlag; //sod¡÷∞¸ ≈¨∑£¿« ∏‚πˆ¿Œ¡ˆ¿« ø©∫Œ	//cE_isclanmember.cppø°º≠ º¬∆√µ 
} CLANDATA;

typedef struct _tagClanWonList
{
	char  clanWon[CLANWON_MAX][30];

}CLANWONLIST;


typedef struct _tagHelpContent
{
	char szHelpContent[HELPWIDTH];
	BOOL bFlag;
}HELPCONTENTS;


typedef struct _tagClanHelpIcon
{	
	char ImagePath[255];
	char ImagePath2[255];	
	char ImagePath3[255];	
	char TextFilePath[255];
}CLANHELPICON;
//end-ygy
typedef struct _tagMenuBMP
{
	HBITMAP membmp;
}MENUBMP;

class CLAN_MENU
{
public:
	CLAN_MENU();
	~CLAN_MENU();


	
	
	int menu_joinOpen(char *chipCharID);	//ØÖ¿« ƒ≥∏Ø≈Õ id
	int menu_joinOpen_Chip(int joinOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel);		//ØÖ¿« ƒ≥∏Ø≈Õ id
		
	//»£µøClan√ﬂ∞°
	int IsCheckClanMember(smCHAR *pChar);


	//PartyInterface ∏Æº“Ω∫..
	#ifdef USE_PROSTONTALE		//=========== ∆˜∏ÆΩ∫≈œº“Ω∫¿Œ∞ÊøÏ
	int	MatPartyBackGround;	//πË∞Ê
	//int	hBoxCorner,hBoxLine;	//π⁄Ω∫±◊∏Æ±‚
	int	hBox1,hBox2,hBox3,hBox4,hBox5,hBox6,hBox7,hBox8,hBox9; //π⁄Ω∫±◊∏Æ±‚



	int	hScl_Bar_tj;
	int	hScl_icon_tj;


	/*
	DIRECTDRAWSURFACE				hBox1_ktj; //»Æ¿Œ

	DIRECTDRAWSURFACE				hOk_Gray,hOk_Yellow; //»Æ¿Œ
	DIRECTDRAWSURFACE				hCancel_Gray,hCancel_Yellow; //√Îº“
	DIRECTDRAWSURFACE				hYes_Gray,hYes_Yellow; // øπ
	DIRECTDRAWSURFACE				hNo_Gray,hNo_Yellow; //æ∆¥œø¿

	DIRECTDRAWSURFACE	hMark,hClanName;
	DIRECTDRAWSURFACE	hSecession[2];
	DIRECTDRAWSURFACE	hClose[2];
	DIRECTDRAWSURFACE	hIcon;
	DIRECTDRAWSURFACE	hIcon_Click;
	DIRECTDRAWSURFACE	hHelp1;
	DIRECTDRAWSURFACE	hClinetMark;
	DIRECTDRAWSURFACE	hServerMark;
	DIRECTDRAWSURFACE	hWareHouse[2]; //∏∂øÏΩ∫∞° ¿ß∑Œ ø√∂Ûø‘¿ª∂ß
	DIRECTDRAWSURFACE	hWHRight[2];
	DIRECTDRAWSURFACE	hClanMark[2];
	DIRECTDRAWSURFACE	hRemove[2];
	DIRECTDRAWSURFACE	hClanRelease[2];
	DIRECTDRAWSURFACE	hHelp[2];
	DIRECTDRAWSURFACE	hOut[2];

	DIRECTDRAWSURFACE	hButton_Box;
	DIRECTDRAWSURFACE	hClanTitle;
	DIRECTDRAWSURFACE	hRemoveToMenu[2];
	DIRECTDRAWSURFACE	hScl_Bar;
	DIRECTDRAWSURFACE	hScl_icon;
	DIRECTDRAWSURFACE	hClanHelpIcon[CLANHELPICON_NUM][4];
	DIRECTDRAWSURFACE    hClanNameInput;

	DIRECTDRAWSURFACE   hTxt_Remove[2]; //√ﬂπÊ
	DIRECTDRAWSURFACE   hTxt_Release[2]; //«ÿ√º
	DIRECTDRAWSURFACE   hTxt_Mark[2]; //∏∂≈©
	DIRECTDRAWSURFACE   hTxt_Help[2]; //µµøÚ∏ª
	DIRECTDRAWSURFACE   hTxt_Secession[2];//≈ª≈
	*/

	
	char		szHelpMsg1[HELPMSG_MAX];
	char		szErrorMsg[256];

	#else
	HBITMAP	hBox1,hBox2,hBox3,hBox4,hBox6,hBox7,hBox8,hBox9;

	HBITMAP	MatPartyBackGround;
	//HBITMAP	hBoxCorner,hBoxLine,hBoxLine1,OldBmp;
	HBITMAP	hOk_Gray,hOk_Yellow; //»Æ¿Œ
	HBITMAP	hCancel_Gray,hCancel_Yellow; //√Îº“
	HBITMAP	hYes_Gray,hYes_Yellow; // øπ
	HBITMAP	hNo_Gray,hNo_Yellow; //æ∆¥œø¿

	HBITMAP	hMark,hClanName;
	HBITMAP	hSecession[2];
	HBITMAP	hClose[2];
	HBITMAP	hIcon;
	HBITMAP   hIcon_Click;
	HBITMAP	hHelp1;
	HBITMAP	hClinetMark;
	HBITMAP	hServerMark;
	HBITMAP	hWareHouse[2]; //∏∂øÏΩ∫∞° ¿ß∑Œ ø√∂Ûø‘¿ª∂ß
	HBITMAP	hWHRight[2];
	HBITMAP	hClanMark[2];
	HBITMAP	hRemove[2];
	HBITMAP	hClanRelease[2];
	HBITMAP	hHelp[2];
	HBITMAP	hOut[2];
	HBITMAP	hButton_Box;
	HBITMAP	hClanTitle;
	HBITMAP	hRemoveToMenu[2];
	HBITMAP	hScl_Bar;
	HBITMAP	hScl_icon;
	HBITMAP   hClanHelpIcon[CLANHELPICON_NUM][4]; //¿Ã¬˜ø¯ πËø≠∑Œ √≥∏Æ

#ifndef _LANGUAGE_BRAZIL //∫Í∂Û¡˙ ≈¨∑£ //«ÿø‹
	HBITMAP   hTxt_Remove[2]; //√ﬂπÊ
	HBITMAP   hTxt_Release[2]; //«ÿ√º
#endif
	HBITMAP   hTxt_Mark[2]; //∏∂≈©
	HBITMAP   hTxt_Help[2]; //µµøÚ∏ª
	HBITMAP   hTxt_Secession[2]; //≈ª≈

	//HWND		m_hClanName;	
	char		szErrorMsg[256];

	#endif

	
	int  nReleaseClanWon;		//ªË¡¶ ≈¨∑£ø¯
	
	
	int nScl_Bar;           //Ω∫≈©∑—πŸ
	//int g_nClanIconNum;			//«Ô«¡æ∆¿Ãƒ‹ √—ºˆ
	int g_HelpIconNumber;    //«ˆ¿Á Ω∫ƒ⁄∑— ¿ßƒ°∏¶ ¿˙¿Â
	//int g_HelpDisPlay;       //«Ô«¡ √—∞πºˆ
	char szHelpContent[1024]; //«Ô«¡ ≥ªøÎ ¿˙¿Â
	


	
	char     szRemoveClanWonResultMsg[1024];
	char     szReconfReleaseMsg[2048];
	
	

	//√¢∞Ì ±««—, √ﬂπÊ æ∆¿Ãƒ‹ ∞¸∑√ ±∏¡∂√º
	typedef struct _tagButtonClick
	{
		char szClanWon[20];
		BOOL bIsClick;
	}BUTTONCLICK;
	BUTTONCLICK buttonclick[30];
	BUTTONCLICK removeclick[30];
	int	nClanWon[40];
	//√ﬂπÊ«“ ≈¨∑£ø¯ ¿˙¿Â
	char szRemoveClanWon[500];
	//≈¨∑£ «Ô«¡ æ∆¿Ãƒ‹ ±∏¡∂√º
	CLANHELPICON ClanHelpIcon[CLANHELPICON_NUM];

	MENUBMP *membmp;

	

	int MatTitle[4];		//≈∏¿Ã∆≤.(ƒ˘Ω∫∆Æ,√§∆√,µø∑·
	
	int xLeft, xRight;

	
	RECT scrIconPos;		//Ω∫≈©∑—πŸ¿« øÚ¡˜¿Ã¥¬æ∆¿Ãƒ‹¿ßƒ°º≥¡§
	//int menuSu;
	void InitMenuSet(int menuN);
	int chk_readStrBuf(char *cmd, char *readbuf, char *retBuf);		//¿• dbø°º≠ ø¬ Ω∫∆Æ∏µø°º≠ ø¯«œ¥¬ Ω∫∆Æ∏µ¿ª ªÃæ∆≥ø.


	void Init();
	void NoticeMessage_Init();
	void Init2();
	void NoticeMessage_Init2();

	void Load();
	void Close();
	
	int	 Main(int sw);
	int	 Draw();
	int	 DrawBox(int x,int y,int x_width,int y_height);
	void menuInit(int num);
	void Draw_C_menuN();
	void Draw_C_Text(char *str, int x, int y, int sw);


	
	void RenderMenu();
	//∫Œºˆ¿˚ «‘ºˆµÈ ( ∏∂øÏΩ∫∑Œ ¥©∏• ∏ﬁ¥∫ π¯»£ √Ω≈©)
	int chkMenu(int x, int y, RECT *r) ;
	int chkeckMenuN();
	void menuSet(int sw);



	int		nChkMark;


	//ygy
	int chkMark(char *clanName);
	
	void SetUserData(char* id, char* chaname, char* gserver,int money, int ability);
	//≈¨∑£ø° ∞°¿‘«“∞Õ¿ª ±«¿Øπﬁ¥¬ ∏ﬁ¥∫¿« ±‚√  «‘ºˆ
	void SetJoinData(char *joinclanname, char *joinclanchip);
	
	//≈¨∑£ ∞°¿‘
	void clanCheckMark_main();
	
	void clanJoin_main(); //≈¨∑£¡∂¿Œ ∏ﬁºº¡ˆ√≥∏Æ
	//º≠πˆ ¡¢±Ÿ ¡ﬂ¿œ∂ß ∫∏≥ª¥¬ «‘ºˆ
	void Loading();
	//join∞¸∑√ «‘ºˆ
	void ClanJoin();
	//≈¨∑£¿Â¿Ã ≈¨∑£ø¯¿ª ∞°¿‘Ω√≈∞¥¬ «‘ºˆ
	void joinClanMember();




	// ø‹∫Œø°º≠ ªÁøÎµ«¥¬ ≈¨∑£¿« ±∏µø º¬∆√ «‘ºˆµÈ===================================start
	void CLANmenu_INIT();					//√≥¿Ω init
	int  CLANmenu_clanPOSITION();			//√≥¿Ω±∏µøΩ√ ≥™¿« ∆˜¡ˆº«
	int  CLANmenu_meetNPC();				//npcøÕ ∏∏≥≤.

	void CLANmenu_ChatList(int sw);				//≈¨∑£ø¯µÈ∞˙¿« √™∏ÆΩ∫∆Æ ∏ﬁ¥∫ ±∏µø«‘ºˆµÈ
	void CLANmenu_DeleteCha();				//ƒ≥∏Ø≈Õ∏¶ ¡ˆøÔ∂ß ≈¨∑£ø¯¿Œ¡ˆæÀæ∆≥ªªÁøÎ«‘.
	// ø‹∫Œø°º≠ ªÁøÎµ«¥¬ ≈¨∑£¿« ±∏µø º¬∆√ «‘ºˆµÈ===================================end

	void GuideHelpDraw(); /////////////////////// µµøÚ∏ª ±◊∏Æ±‚////////////////////////
};

typedef struct _tagClanMsg
{
	POINT pos;
	char szMsg[1024];
}CLANMSG;

void Draw_Text(int x, int y,char *str);
void Text_Out(HDC hdc,int x, int y,char *str);





#ifdef TJCLAN_CPP

CLAN_MENU	Interface_clanmenu;




//auth.cppø°º≠ ¥‰∫Ø¿ª πﬁæ∆ø¿¥¬ ∫Øºˆ ( classø° ≥÷¿∏∏È ¥‰¿Ã ¿ÃªÛ«œ∞‘ ≥™ø»)
ANSWERDATA ANSdata;

CLANDATA cldata;		//web µ∫Òø°º≠ πﬁ¿∫ Ω∫∆Æ∏µ¿ª ∆ƒΩÃ«ÿº≠ ≥÷æÓµ–∞˜
CLANDATA chacldata[5];	//∞Ë¡§ø° ∏∏µÈæÓ¡¯ ƒ≥∏Ø≈ÕµÈ¿Ã ∞°¿‘«— ≈¨∑£¡§∫∏ ¿˙¿Â




//=======================================√‚∑¬ ∏ﬁºº¡ˆ======================start

//≈¨∑£ ∏∏µÈ±‚ ∞¸∑√ ∏ﬁºº¡ˆ
CLANMSG clanMake1;
CLANMSG clanMake2;
CLANMSG clanMake3;
CLANMSG clanMake4;
CLANMSG clanMake5;
CLANMSG clanMake6;
CLANMSG clanMsg21;
CLANMSG clanMsg254;
CLANMSG clanMsg15;
CLANMSG clanJoin;
CLANMSG clanSecession;
CLANMSG clanServerConnectErrorMsg;
CLANMSG clanszError_Msg;
CLANMSG clanDeleteChaError;
CLANMSG clanCancelMakeClan;
CLANMSG clanClanNameError;
CLANMSG clanSecession6DownMsg;
CLANMSG clanClanJoinMsg;
CLANMSG clanClanJoinCancelMsg;
CLANMSG clanClanJoinsucesssMsg;
CLANMSG clanszReMoveClanWonMsg;
CLANMSG clanReMoveHeaderMsg;
CLANMSG clanszReConfReleaseMsg;
CLANMSG clanNoRecordReleaseMsg;
CLANMSG clanFinishReleaseMsg;
CLANMSG clanSecessionMsg;
CLANMSG clanFinishSecessionMsg;
CLANMSG clanisCheckClanJangErrorMsg;
CLANMSG clanMoneyErrorMsg;
CLANMSG clanAbilityErrorMsg;
CLANMSG clanszRemoveShortClanWonMsg;
CLANMSG clanNoName;
CLANMSG clanLoading;
CLANMSG clanMsg6;
CLANMSG clanMsg7;
CLANMSG clanClanWon6Down;
CLANMSG clanClanUserNoMakeMsg;
CLANMSG clanMakeFinishClanWon;
CLANMSG clanClanServerInspect;
CLANMSG clanClanUserRelease;
CLANMSG clanClanUserReleaseMsg;
CLANMSG clanClanMakedowninfo;
CLANMSG clanClanUserRemove;
CLANMSG clanClanWonOver;
CLANMSG clanNoLevel;
CLANMSG clanMakeFinishClan;
CLANMSG clanRemoveShowrtClanWonResultMsg;
CLANMSG clanRemoveSecond;
CLANMSG clanRemoveSecondResult;
CLANMSG LeaveClanConfirm;
CLANMSG LeaveClanNoMoney;
CLANMSG LeaveClanSuccess;
CLANMSG LeaveClanNoLevel;
CLANMSG LeaveClanReConfirm;
CLANMSG NoLeaveClan;
CLANMSG LeaveClanMessage;
CLANMSG LeaveClanDownLevel;
CLANMSG SubChipAppoint;
CLANMSG SubChipAppointEnd;
CLANMSG SubChipRelease;
CLANMSG SubChipReleaseEnd;
CLANMSG NoSubChip;

//»£µøClan√ﬂ∞°
CLANMSG ClanIs4DayCheckMsg;


char szMsg1[CLANMESSAGEBUF_MAX];
char szMsg2[CLANMESSAGEBUF_MAX];
char szMsg21[CLANMESSAGEBUF_MAX];
char szMsg3[CLANMESSAGEBUF_MAX];
char szMsg4[CLANMESSAGEBUF_MAX];
char szMsg5[CLANMESSAGEBUF_MAX];
char szClanMakeFinishMsg[CLANMESSAGEBUF_MAX];
char szMsg254[CLANMESSAGEBUF_MAX];
char szMsg15[CLANMESSAGEBUF_MAX];
char szMark1[CLANMESSAGEBUF_MAX];
char szMark2[CLANMESSAGEBUF_MAX];
char szMark3[CLANMESSAGEBUF_MAX];
char szJoin[CLANMESSAGEBUF_MAX];
char szSecession[CLANMESSAGEBUF_MAX];
char szMsg6[CLANMESSAGEBUF_MAX];
char szServerConnectErrorMsg[CLANMESSAGEBUF_MAX];
char szReadClanMarkErrorMsg[CLANMESSAGEBUF_MAX];
char szCancelMakeClan[CLANMESSAGEBUF_MAX];
char szTranzationError[CLANMESSAGEBUF_MAX];
char szInsertClanWonError1[CLANMESSAGEBUF_MAX];
char szClanNameError[CLANMESSAGEBUF_MAX];
char sz100Error[CLANMESSAGEBUF_MAX];
char szDefaultError[CLANMESSAGEBUF_MAX];
char szReleseError[CLANMESSAGEBUF_MAX];
char szSecessionSuccess[CLANMESSAGEBUF_MAX];
char szSecession6DownMsg[CLANMESSAGEBUF_MAX];
char szSecessionChipMsg[CLANMESSAGEBUF_MAX];
char szSecession2ErrorMsg[CLANMESSAGEBUF_MAX];
char szClanJoinMsg[CLANMESSAGEBUF_MAX];
char szClanJoinError2Msg[CLANMESSAGEBUF_MAX];
char szClanJoinError3Msg[CLANMESSAGEBUF_MAX];
char szClanJoinError4Msg[CLANMESSAGEBUF_MAX];
char szClanJoinCancelMsg[CLANMESSAGEBUF_MAX];
char szClanJoinsucesssMsg[CLANMESSAGEBUF_MAX];
char szReMoveClanWonMsg[CLANMESSAGEBUF_MAX];
char szReMoveHeaderMsg[CLANMESSAGEBUF_MAX];
char szReConfReleaseMsg[CLANMESSAGEBUF_MAX];

char szNoRecordReleaseMsg[CLANMESSAGEBUF_MAX];
char szFinishReleaseMsg[CLANMESSAGEBUF_MAX];
char szSecessionMsg[CLANMESSAGEBUF_MAX];
char szFinishSecessionMsg[CLANMESSAGEBUF_MAX];
char szisCheckClanJangErrorMsg[CLANMESSAGEBUF_MAX];
char szMoneyErrorMsg[CLANMESSAGEBUF_MAX];
char szAbilityErrorMsg[CLANMESSAGEBUF_MAX];
char szRemoveShortClanWonMsg[CLANMESSAGEBUF_MAX];
char szRemoveShowrtClanWonResultMsg[CLANMESSAGEBUF_MAX];
char szNoName[CLANMESSAGEBUF_MAX];
char szLoading[CLANMESSAGEBUF_MAX];
/////////ƒ≥∏Ø≈Õ ªË¡¶ ∏ﬁºº¡ˆ
char szDeleteChaReleaseBefore[CLANMESSAGEBUF_MAX];
char szDeleteChaReleaseFinish[CLANMESSAGEBUF_MAX];
char szDeleteChaSecessionBefore[CLANMESSAGEBUF_MAX];
char szDeleteChaSecessionFinish[CLANMESSAGEBUF_MAX];

char szDeleteChaError[CLANMESSAGEBUF_MAX];
char szMakeFinishClan[CLANMESSAGEBUF_MAX];
char szClanWon6Down[CLANMESSAGEBUF_MAX];
char szClanUserNoMakeMsg[CLANMESSAGEBUF_MAX];
char szMakeFinishClanWon[CLANMESSAGEBUF_MAX];
char ClanServerInspect[CLANMESSAGEBUF_MAX];
char szClanUserRelease[CLANMESSAGEBUF_MAX];
char Replay[CLANMESSAGEBUF_MAX];
char szClanMakedowninfo[CLANMESSAGEBUF_MAX];
char szClanUserReleaseMsg[CLANMESSAGEBUF_MAX];
char szClanUserRemove[CLANMESSAGEBUF_MAX];
char szClanWonOver[CLANMESSAGEBUF_MAX];
char szError_Msg[CLANMESSAGEBUF_MAX];
char szMsg7[CLANMESSAGEBUF_MAX];
char szNoLevel[CLANMESSAGEBUF_MAX];
//=======================================√‚∑¬ ∏ﬁºº¡ˆ======================end



	int C_menuN;			//≈¨∑£¿« ∏ﬁ¥∫¥¬ ø©∑Ø∞°¡ˆ∞° ¿÷±‚∂ßπÆø° π¯»£∏¶ º¬∆√«ÿº≠ ≥™¥≤¡ÿ¥Ÿ.
	int C_menuN2;			//¿•º≠πˆøÕø¨∞·Ω√ æ≤∑πµÂ¿« µ•¿Ã≈∏∏¶ ±‚¥Ÿ∏Æ±‚¿ß«ÿ º¬∆√µ«¥¬ √Ω≈©øÎπ¯»£¿”.
	int CLAN_ERROR_ret;		//ø°∑Ø∏ﬁ¥∫∫∏ø©¡ÿ»ƒ √£æ∆∞•∞˜ ¡§«—¥Ÿ.



	int  nClanWon_Num;			//≈¨∑£ø¯∆ƒΩÃ»ƒ ≈¨∑£ø¯¿« ∏Ìºˆ(≈¨∑£¿Â¡¶ø‹)
	POINT BackStartPos;		//¿Œ≈Õ∆‰¿ÃΩ∫ ±‚∫ª¿ßƒ°
	int g_HelpIconNumber;    //«ˆ¿Á Ω∫ƒ⁄∑— ¿ßƒ°∏¶ ¿˙¿Â
	HELPCONTENTS HelpContents[100];
	int g_nClanIconNum;
	int g_HelpDisPlay;
	int g_HelpIConNumber;
	RECT menuPos[30];		//∏ﬁ¥∫º¬∆√.
	int		menuMouseOver[30];
	int menuSu;
	CLANHELPICON ClanHelpIcon[CLANHELPICON_NUM];
	char szRemoveClanWonResult[5][64];
	int keydownEnt =0;
	int TJwheel =0;// »Ÿµ•¿Ã≈∏
	int OpenFlag =0;
	char banisBuf1[64];
	char banisBuf2[512];
	int  banisCnt;

	DIBSectionBUF Dback;		//πÈπˆ∆€øÎ.
	int joinAnswer;
	BOOL bIsLoading = FALSE; 
	BOOL bOpenChatList = FALSE;
	BOOL bIsReadData = FALSE;
	int  ChatList_CmenuN = 0;
	int	ChatList_CmenuN2 = 0;

	int TJmb[3] = { 0,0,0 };
	int TJmb2[3] = { 0,0,0 };

	BOOL bCheckHostNameandPort = FALSE;
	MYCLANINFOHEADER MyClanInfo;

	CLANWONLIST ClanWonList;
	BOOL		bcldataclanmark = FALSE;






	int isDrawClanMenu=0;	//∏ﬁ¥∫∞° ∂∞¿÷¿∏∏È 1

	char  szChatClanWon[CLANWON_MAX][30];        //≈¨∑£º≠πˆø°º≠ ∫∏≥ª¡ÿ ≈¨∑£ø¯¿ª ¿˙¿Â(≈¨∑£¿Â ¡¶ø‹)

#else	//=================================================================//




extern BOOL		bcldataclanmark;
extern CLANWONLIST ClanWonList;
extern MYCLANINFOHEADER MyClanInfo;

extern BOOL bCheckHostNameandPort;  //≈¨∑£ º≠πˆ æ∆¿Ã««¡÷º“∞˙ ∆˜∆Æ ªÛ≈¬∏¶ √º≈©
extern int TJmb[3] ;
extern int TJmb2[3];

extern int  ChatList_CmenuN;
extern int  ChatList_CmenuN2;
extern BOOL bIsReadData;
extern BOOL bOpenChatList;
extern BOOL bIsLoading; 
extern int joinAnswer;
extern DIBSectionBUF Dback;		//πÈπˆ∆€øÎ.


//extern HBITMAP membmp;




extern int TJwheel; //ktj : »Ÿµ•¿Ã≈∏
extern int menuSu;
extern HWND			g_hwnd;
extern POINT		pCursorPos;
extern HINSTANCE	g_hInst;

extern CLAN_MENU	Interface_clanmenu;
extern ANSWERDATA	ANSdata;
extern int OpenFlag;



extern    int C_menuN;			//≈¨∑£¿« ∏ﬁ¥∫¥¬ ø©∑Ø∞°¡ˆ∞° ¿÷±‚∂ßπÆø° π¯»£∏¶ º¬∆√«ÿº≠ ≥™¥≤¡ÿ¥Ÿ.
extern 	int C_menuN2;			//¿•º≠πˆøÕø¨∞·Ω√ æ≤∑πµÂ¿« µ•¿Ã≈∏∏¶ ±‚¥Ÿ∏Æ±‚¿ß«ÿ º¬∆√µ«¥¬ √Ω≈©øÎπ¯»£¿”.
extern 	int CLAN_ERROR_ret;		//ø°∑Ø∏ﬁ¥∫∫∏ø©¡ÿ»ƒ √£æ∆∞•∞˜ ¡§«—¥Ÿ.
extern int  banisF[100];
extern char banisBuf1[64];
extern char banisBuf2[512];
extern int  banisCnt;
extern CLANDATA cldata;		//web µ∫Òø°º≠ πﬁ¿∫ Ω∫∆Æ∏µ¿ª ∆ƒΩÃ«ÿº≠ ≥÷æÓµ–∞˜
extern CLANDATA chacldata[5];	//∞Ë¡§ø° ∏∏µÈæÓ¡¯ ƒ≥∏Ø≈ÕµÈ¿Ã ∞°¿‘«— ≈¨∑£¡§∫∏ ¿˙¿Â


extern int  nClanWon_Num;			//≈¨∑£ø¯∆ƒΩÃ»ƒ ≈¨∑£ø¯¿« ∏Ìºˆ(≈¨∑£¿Â¡¶ø‹)
extern POINT BackStartPos;		//¿Œ≈Õ∆‰¿ÃΩ∫ ±‚∫ª¿ßƒ°
extern int g_HelpIconNumber;    //«ˆ¿Á Ω∫ƒ⁄∑— ¿ßƒ°∏¶ ¿˙¿Â
extern HELPCONTENTS HelpContents[100];
extern int g_nClanIconNum;
extern int g_HelpDisPlay;
extern int g_HelpIConNumber;
extern RECT menuPos[30];		//∏ﬁ¥∫º¬∆√.
extern int		menuMouseOver[30];
extern int MouseButton[3] ;	//∏∂øÏΩ∫πˆ∆∞¥≠∏≤√Ω≈© : winmain.cppø° ¡§¿««‘
extern CLANHELPICON ClanHelpIcon[CLANHELPICON_NUM];
extern char szRemoveClanWonResult[5][64];
#define MOUSE0() MouseButton[0]
extern int keydownEnt;



extern CLANMSG clanMake1;
extern CLANMSG clanMake2;
extern CLANMSG clanMake3;
extern CLANMSG clanMake4;
extern CLANMSG clanMake5;
extern CLANMSG clanMake6;


extern CLANMSG clanMsg21;
extern CLANMSG clanMsg254;
extern CLANMSG clanMsg15;
extern CLANMSG clanJoin;
extern CLANMSG clanSecession;
extern CLANMSG clanServerConnectErrorMsg;
extern CLANMSG clanszError_Msg;
extern CLANMSG clanDeleteChaError;
extern CLANMSG clanCancelMakeClan;
extern CLANMSG clanClanNameError;
extern CLANMSG clanSecession6DownMsg;
extern CLANMSG clanClanJoinMsg;
extern CLANMSG clanClanJoinCancelMsg;
extern CLANMSG clanClanJoinsucesssMsg;
extern CLANMSG clanszReMoveClanWonMsg;
extern CLANMSG clanReMoveHeaderMsg;
extern CLANMSG clanszReConfReleaseMsg;
extern CLANMSG clanNoRecordReleaseMsg;
extern CLANMSG clanFinishReleaseMsg;
extern CLANMSG clanSecessionMsg;
extern CLANMSG clanFinishSecessionMsg;
extern CLANMSG clanisCheckClanJangErrorMsg;
extern CLANMSG clanMoneyErrorMsg;
extern CLANMSG clanAbilityErrorMsg;
extern CLANMSG clanszRemoveShortClanWonMsg;
extern CLANMSG clanNoName;
extern CLANMSG clanLoading;
extern CLANMSG clanMsg6;
extern CLANMSG clanMsg7;
extern CLANMSG clanClanWon6Down;
extern CLANMSG clanClanUserNoMakeMsg;
extern CLANMSG clanMakeFinishClanWon;
extern CLANMSG clanClanServerInspect;
extern CLANMSG clanClanUserRelease;
extern CLANMSG clanClanUserReleaseMsg;
extern CLANMSG clanClanMakedowninfo;
extern CLANMSG clanClanUserRemove;
extern CLANMSG clanClanWonOver;
extern CLANMSG clanNoLevel;
extern CLANMSG clanMakeFinishClan;
extern CLANMSG clanRemoveShowrtClanWonResultMsg;
extern CLANMSG clanRemoveSecond;
extern CLANMSG clanRemoveSecondResult;
extern CLANMSG LeaveClanConfirm;
extern CLANMSG LeaveClanNoMoney;
extern CLANMSG LeaveClanSuccess;
extern CLANMSG LeaveClanNoLevel;
extern CLANMSG LeaveClanReConfirm;
extern CLANMSG NoLeaveClan;
extern CLANMSG LeaveClanMessage;
extern CLANMSG LeaveClanDownLevel;
extern CLANMSG SubChipAppoint;
extern CLANMSG SubChipAppointEnd;
extern CLANMSG SubChipRelease;
extern CLANMSG SubChipReleaseEnd;
extern CLANMSG NoSubChip;

////»£µøClan√ﬂ∞°
extern CLANMSG ClanIs4DayCheckMsg;


extern char szMsg1[CLANMESSAGEBUF_MAX];
extern char szMsg2[CLANMESSAGEBUF_MAX];
extern char szMsg21[CLANMESSAGEBUF_MAX];
extern char szMsg3[CLANMESSAGEBUF_MAX];
extern char szMsg4[CLANMESSAGEBUF_MAX];
extern char szMsg5[CLANMESSAGEBUF_MAX]; 
extern char szMsg6[CLANMESSAGEBUF_MAX];
extern char sz100Error[CLANMESSAGEBUF_MAX];
extern char szAbilityErrorMsg[CLANMESSAGEBUF_MAX];
extern char szCancelMakeClan[CLANMESSAGEBUF_MAX];
extern char szMsg254[CLANMESSAGEBUF_MAX];
extern char szClanMakeFinishMsg[CLANMESSAGEBUF_MAX];
extern char szMsg15[CLANMESSAGEBUF_MAX]; 
extern char szMark1[CLANMESSAGEBUF_MAX]; 
extern char szMark2[CLANMESSAGEBUF_MAX]; 
extern char szMark3[CLANMESSAGEBUF_MAX]; 
extern char szJoin[CLANMESSAGEBUF_MAX];
extern char szSecession[CLANMESSAGEBUF_MAX]; 
extern char szServerConnectErrorMsg[CLANMESSAGEBUF_MAX]; 
extern char szReadClanMarkErrorMsg[CLANMESSAGEBUF_MAX];
extern char szTranzationError[CLANMESSAGEBUF_MAX];
extern char szInsertClanWonError1[CLANMESSAGEBUF_MAX];
extern char szClanNameError[CLANMESSAGEBUF_MAX];
extern char szDefaultError[CLANMESSAGEBUF_MAX];
extern char szReleseError[CLANMESSAGEBUF_MAX];
extern char szSecessionSuccess[CLANMESSAGEBUF_MAX];
extern char szSecession6DownMsg[CLANMESSAGEBUF_MAX];
extern char szSecessionChipMsg[CLANMESSAGEBUF_MAX];
extern char szSecession2ErrorMsg[CLANMESSAGEBUF_MAX];
extern char szClanJoinMsg[CLANMESSAGEBUF_MAX];
extern char szClanJoinError2Msg[CLANMESSAGEBUF_MAX]; 
extern char szClanJoinError3Msg[CLANMESSAGEBUF_MAX];
extern char szClanJoinError4Msg[CLANMESSAGEBUF_MAX];
extern char szClanJoinCancelMsg[CLANMESSAGEBUF_MAX];
extern char szClanJoinsucesssMsg[CLANMESSAGEBUF_MAX];
extern char szReMoveClanWonMsg[CLANMESSAGEBUF_MAX];
extern char szReMoveHeaderMsg[CLANMESSAGEBUF_MAX];
extern char szReConfReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szNoRecordReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szFinishReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szSecessionMsg[CLANMESSAGEBUF_MAX];
extern char szFinishSecessionMsg[CLANMESSAGEBUF_MAX];
extern char szisCheckClanJangErrorMsg[CLANMESSAGEBUF_MAX];
extern char szMoneyErrorMsg[CLANMESSAGEBUF_MAX];
extern char szRemoveShortClanWonMsg[CLANMESSAGEBUF_MAX];
extern char szRemoveShowrtClanWonResultMsg[CLANMESSAGEBUF_MAX];
extern char szClanUserNoMakeMsg[CLANMESSAGEBUF_MAX];
extern char szNoName[CLANMESSAGEBUF_MAX];
extern char szLoading[CLANMESSAGEBUF_MAX];

extern char szDeleteChaReleaseBefore[CLANMESSAGEBUF_MAX];
extern char szDeleteChaReleaseFinish[CLANMESSAGEBUF_MAX];
extern char szDeleteChaSecessionBefore[CLANMESSAGEBUF_MAX];
extern char szDeleteChaSecessionFinish[CLANMESSAGEBUF_MAX];

extern char szDeleteChaError[CLANMESSAGEBUF_MAX];
extern char szMakeFinishClan[CLANMESSAGEBUF_MAX];
extern char szClanWon6Down[CLANMESSAGEBUF_MAX];
extern char szMakeFinishClanWon[CLANMESSAGEBUF_MAX];
extern char ClanServerInspect[CLANMESSAGEBUF_MAX];
extern char szClanUserRelease[CLANMESSAGEBUF_MAX]; 
extern char Replay[CLANMESSAGEBUF_MAX];
extern char szClanMakedowninfo[CLANMESSAGEBUF_MAX]; 
extern char szClanUserReleaseMsg[CLANMESSAGEBUF_MAX];
extern char szClanUserRemove[CLANMESSAGEBUF_MAX];
extern char szClanWonOver[CLANMESSAGEBUF_MAX];
extern char szError_Msg[CLANMESSAGEBUF_MAX];

extern char szMsg7[CLANMESSAGEBUF_MAX];
extern char szNoLevel[CLANMESSAGEBUF_MAX];

extern int ClanCharMove;	//∏ﬁ¥∫∆«æ»¿« ∏∂øÏΩ∫¿« øÚ¡˜¿”ø° ƒ≥∏Ø≈Õ∞° øµ«‚æ¯µµ∑œ «—¥Ÿ.
extern int ClanCLCharMove;//




extern int isDrawClanMenu;	//∏ﬁ¥∫∞° ∂∞¿÷¿∏∏È 1



extern int ktj_imsiDRAWinfo ;



extern char  szChatClanWon[CLANWON_MAX][30];        //≈¨∑£º≠πˆø°º≠ ∫∏≥ª¡ÿ ≈¨∑£ø¯¿ª ¿˙¿Â(≈¨∑£¿Â ¡¶ø‹)


#endif


void ClanJoin(char *oneClanName, char *oneChipCharid);
void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID);
void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID, int clanWonJob, int clanWonLevel);

//»£µøClan√ﬂ∞°
void g_IsCheckClanMember(smCHAR *pChar);

//cldata æ¯µ•¿Ã∆ÆøÎ
void Updatecldata();



//≈¨∑£∏∂≈© ¿ßƒ° πﬁ±‚
int ReadClanInfo(DWORD dwClanNum);
int ReadClanInfo_32X32(DWORD dwClanNum);
//≈¨∑£∏∂≈©¿« ªÁøÎπ˝ 
//πﬁ¿∫π¯»£ = ReadClanInfo(100189);
//if(πﬁ¿∫π¯»£ == -1) «ˆ¿Á ¥ŸøÓπﬁ¿ªºˆæ¯¿Ω.
//if(ClanInfo[ πﬁ¿∫π¯»£ ].nStatus == 2) {
//			ªÁøÎ∞°¥…«‘
//}


//web DB¿« ∆˜∆ÆøÕ ipº¬∆√Ω√ ªÁøÎ«‘(ƒ≥∏Ø≈Õ º±≈√»≠∏È ¿¸ø° ≥÷¿ª∞Õ)
void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1);
void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1,int ticket);



//ktj :  1. ƒ≥∏Ø ¡ˆøÏ±‚¿¸ø° º¬∆√«œ¥¬ «‘ºˆ
void CLANmenu_DeleteCha_SetCharacter(char *id, char *gserver, char *chaname);


//HWND hFocusWnd∏¶ ªÁøÎ«œ∞Ì ¿÷¥¬¡ˆ¿« ø©∫Œ∏¶ æÀæ∆≥ø. 0:æ»ªÁøÎ 1:ªÁøÎ
extern int usehFocus;



//Ω∫≈©∑—ø° »Ÿ≈∞ªÁøÎø©∫Œ
int TJBscrollWheel(int wheel);		//ªÁøÎ¡ﬂ:1  πÃªÁøÎ¡ﬂ 0


//√§∆√∏ÆΩ∫∆ÆΩ∫««ƒø¿« «√∑°±◊∏¶ æÀæ∆≥Ω¥Ÿ.
int chatlistSPEAKERflag();
void chatlistSPEAKERflagChg(int flag);//0,1¿ª ≥÷¿ªºˆ¿÷¿Ω.







//=============∞◊µÈæÓ∞°±‚¡˜¿¸ø° ∞Ê∞Ì ∏ﬁºº¡ˆ=====================
//1. º¬∆√«‘ºˆ
int GetNoticeUrl(char *url);








#ifdef TJCLAN_CPP


#ifndef USE_PROSTONTALE		//=============¿©µµø°º≠∏∏ ªÁøÎ«‘


extern HWND    g_hwnd;
/*///////////////////////////////////////////////////////////////////////////
: «‘ºˆ  ∏Ì :  HBITMAP MakeDIBSection(char *Path)
: «œ¥¬  ¿œ :  
: ¿Œ    ¿⁄ : bmp∆ƒ¿œ¿ª¿–æÓº≠  DIB ºΩº«¿ª ∏∏µÈæÓ «⁄µÈ¿ª ∏Æ≈œ«—¥Ÿ.
: π›»Ø  ∞™ :  
///////////////////////////////////////////////////////////////////////////*/
HBITMAP MakeDIBSection(DIBSectionBUF *Dibbuf)
{
	HANDLE hFile;
	DWORD FileSize, dwRead;
	BITMAPFILEHEADER fh;
	HBITMAP hBit;
	BITMAPINFO *ih;
	PVOID pRaster;

	// ∆ƒ¿œ¿ª ø¨¥Ÿ
	hFile=CreateFile(Dibbuf->fname,GENERIC_READ,0,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile==INVALID_HANDLE_VALUE) {
		return NULL;
	}

	// ∆ƒ¿œ «Ï¥ıøÕ ¡§∫∏ ±∏¡∂√º(ªˆªÛ ≈◊¿Ã∫Ì ∆˜«‘)∏¶ ¿–æÓµÈ¿Œ¥Ÿ.
	ReadFile(hFile,&fh,sizeof(BITMAPFILEHEADER),&dwRead,NULL);
	FileSize=fh.bfOffBits-sizeof(BITMAPFILEHEADER);
	ih=(BITMAPINFO *)malloc(FileSize);
	ReadFile(hFile,ih,FileSize,&dwRead,NULL);

	//ih->bmiHeader.biHeight =  -ih->bmiHeader.biHeight;
	// DIB ºΩº«¿ª ∏∏µÈ∞Ì πˆ∆€ ∏ﬁ∏∏Æ∏¶ «“¥Á«—¥Ÿ.
	hBit = CreateDIBSection(NULL,ih,DIB_RGB_COLORS,&pRaster,NULL,0);

	if(Dibbuf != NULL) {				//¡§∫∏∏¶ ≥—∞‹¡ÿ¥Ÿ.
		Dibbuf->hb = hBit;
		Dibbuf->pixBuf = (void *)pRaster;
	}


	// ∑°Ω∫≈Õ µ•¿Ã≈Õ∏¶ ¿–æÓµÈ¿Œ¥Ÿ.
	ReadFile(hFile,pRaster,fh.bfSize-fh.bfOffBits,&dwRead,NULL);
	free(ih);
	CloseHandle(hFile);
	
	return hBit;
}

void window_renderINIT()				//«—π¯
{
	static cnt=0;
	if(cnt != 0) return;
	cnt = 1;

	Dback.hb = 0;
	Dback.pixBuf = 0;
	wsprintf(Dback.fname, "stg0.bmp" );		//¿”Ω√
	MakeDIBSection(&Dback);			//dib Section
}

void window_renderFLIP()					//«—π¯
{
	HDC hdc, sorDC;
	hdc = GetDC(g_hwnd);
	sorDC =CreateCompatibleDC(hdc );
	SelectObject(sorDC , Dback.hb );

	//«√∏Æ«Œ.
	BitBlt(hdc, 0,0,
			800, 600,
			sorDC,0,0,SRCCOPY);

	DeleteDC(sorDC);

	ReleaseDC( g_hwnd, hdc);


	//if(Dback.hb) {
	//	DeleteObject( Dback.hb );
	//}
}
#endif


#endif


void CheckMsgPos(CLANMSG* clanmsg,int width, int height);
void DebugMessage(char* msg,...);
void InitHelp();
void GoNotice();
int GetNoticeUrl(char *url);

extern int GoNotice_chking;

