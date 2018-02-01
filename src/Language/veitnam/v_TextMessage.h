#include "TextMessage.h"

char *szAppName="Priston Tale";


char *mgRequestTrade = "GıÒi yêu câÌu trao ğôÒi tõìi %s";
char *mgRequestTrade2 = "%s ğaŞ ği quaì xa ğêÒ coì thêÒ trao ğôÒi";

char *mgDiconnect = "Kêìt nôìi võìi Server biò ngãìt";
char *mgDiconnect1 = "Kêìt nôìi võìi Server biò ngãìt (1)";
char *mgDiconnect2 = "Kêìt nôìi võìi Server biò ngãìt (2)";
char *mgDiconnect3 = "Kêìt nôìi võìi Server biò ngãìt (3)";
char *mgDiconnect4 = "Kêìt nôìi võìi Server biò ngãìt (4)";

char *mgCloseGame = "Ğang thoaìt khoÒi troÌ chõi";
char *mgCloseWindow = "Vui loÌng ğoìng cıÒa sôÒ naÌy laòi  trıõìc khi thoaìt.";
char *mgCloseBattle = "Không thêÒ thoaìt khoÒi troÌ chõi   khi ğang chiêìn ğâìu";
/*
char *mgQuestName[][4] = {
	{	"Rank up quest"	,	"Rank up quest(Completed)" , "ChangeJob1a.Msg" , "ChangeJob1b.Msg" },
	{	"Rank up quest"	,	"Rank-up Exam (Done)" , "ChangeJob2a.Msg" , "ChangeJob1b.Msg" },
	{	"Rank up quest"	,	"Rank up quest (Completed)" , "ChangeJob3a.Msg" , "ChangeJob1b.Msg" },

	{	"Rank up quest [Second]"		,	"Rank up quest [Second]" , "ChangeJob3-1.msg" , "ChangeJob3-2.msg" },
	{	"Rank up quest [Second]"		,	"Rank up quest (Completed)" , "ChangeJob3-3.msg" , "ChangeJob3-4.msg" },

	//Fighter Pikeman Mecanicion Knight
	{	"Rank up quest second[1]"		,	"Rank up quest second[2]"		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-W1-2.msg" },
	{	"Rank up quest second[3]"		,	"Rank up quest second[4]"		, "Quest3\\ChangeJob3-W2-2.msg" , "Quest3\\ChangeJob3-W3-2.msg" },
	{	"Rank up quest second[5]"		,	"Rank up quest second[Completed]"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//Archer Atalanta
	{	"Rank up quest second[1]"		,	"Rank up quest second[2]"		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-R1-2.msg" },
	{	"Rank up quest second[3]"		,	"Rank up quest second[4]"		, "Quest3\\ChangeJob3-R2-2.msg" , "Quest3\\ChangeJob3-R3-2.msg" },
	{	"Rank up quest second[5]"		,	"Rank up quest second[Completed]"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//Priestess Magicion
	{	"Rank up quest second[1]"		,	"Rank up quest second[2]"		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-M1-2.msg" },
	{	"Rank up quest second[3]"		,	"Rank up quest second[4]"		, "Quest3\\ChangeJob3-M2-2.msg" , "Quest3\\ChangeJob3-M3-2.msg" },
	{	"Rank up quest second[5]"		,	"Rank up quest second[Completed]"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },
	
	//·¹º§º° ÄuÌ½ºÆ®
	{	"For her"	,	"For her(completed)" ,	"LevelQuest\\Quest30.Msg" , "LevelQuest\\Quest30a.Msg" },	//14
	{	"The Cave"	,	"The Cave(completed)" ,					"LevelQuest\\Quest55.Msg" , "LevelQuest\\Quest55a.Msg" },	//15
	{	"The Cave"	,	"The Cave(completed)" ,					"LevelQuest\\Quest55_2.Msg" , "LevelQuest\\Quest55_2a.Msg" }, //16
	{	"Friendship with Michelle"	,	"Friendship with Michelle(completed)" ,	"LevelQuest\\Quest70.Msg" , "LevelQuest\\Quest70a.Msg" },	//17
	{	"Enclosed Fury",	"Enclosed Fury(completed)" ,				"LevelQuest\\Quest80.Msg" , "LevelQuest\\Quest80a.Msg" },	//18
	{	"Tears of Kaliha","Tears of Kaliha(completed)" ,				"LevelQuest\\Quest85.Msg" , "LevelQuest\\Quest85a.Msg" },	//19
	{	"Village of eura","Village of eura(completed)" ,					"LevelQuest\\Quest90.Msg" , "LevelQuest\\Quest90a.Msg" },	//20

	//º¸³Ê½º ½ºÅİ Äù½ºÆ®
	{	"Test of Kingdom",	"Test of Kingdom(Complete)" ,	"LevelQuest\\Quest_7State_1.msg" , "LevelQuest\\Quest_7State_end.msg" },	//21
	{	"Test of Kingdom",	"Test of Kingdom(Complete)",	"LevelQuest\\Quest_7State_2.msg" , "LevelQuest\\Quest_7State_end.msg" },	//22
	{	"Test of Kingdom",	"Test of Kingdom(Complete)",	"LevelQuest\\Quest_7State_3.msg" , "LevelQuest\\Quest_7State_end.msg" },	//23

	{	"Bitter ordeal"	,	"Bitter ordeal(Complete)" ,	"LevelQuest\\Quest_10State_1.msg" , "LevelQuest\\Quest_10State_end.msg" },	//24
	{	"Bitter ordeal"	,	"Bitter ordeal(Complete)" ,	"LevelQuest\\Quest_10State_2_1.msg" , "LevelQuest\\Quest_10State_end.msg" },//25
	{	"Bitter ordeal"	,	"Bitter ordeal(Complete)" ,	"LevelQuest\\Quest_10State_2_2.msg" , "LevelQuest\\Quest_10State_end.msg" },//26
	{	"Bitter ordeal"	,	"Bitter ordeal(Complete)" ,	"LevelQuest\\Quest_10State_2_3.msg" , "LevelQuest\\Quest_10State_end.msg" },//27

	//3Â÷ Àü¾÷ Äù½ºÆ®
	{	"Job Quest 3th[1]"	,	"Job Quest 3th(Complete)" ,	"Quest4\\ChangeJob4_1.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//28
	{	"Job Quest 3th[2]"	,	"Job Quest 3th(Complete)" ,	"Quest4\\ChangeJob4_2.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//29
	{	"Job Quest 3th[3]"	,	"Job Quest 3th(Complete)" ,	"Quest4\\ChangeJob4_3_1.msg" ,	"Quest4\\ChangeJob4_3_2.msg" },	//30
	{	"Job Quest 3th[3]"	,	"Job Quest 3th(Complete)" ,	"Quest4\\ChangeJob4_3_3.msg" ,	"Quest4\\ChangeJob4_3_4.msg" },	//31
	{	"Job Quest 3th[3]"	,	"Job Quest 3th(Complete)" ,	"Quest4\\ChangeJob4_3_5.msg" ,	"Quest4\\ChangeJob4_3_6.msg" },	//32
	{	"Job Quest 3th[4]"	,	"Job Quest 3th(Complete)" ,	"Quest4\\ChangeJob4_4.msg" ,	"Quest4\\ChangeJob4_5.msg" }	//33

};
*/
char *mgRefuseWhisper = "Tin nhãìn riêng ğaŞ biò tıÌ chôìi";
char *mgWeightOver = "Không thêÒ mang thêm ğıõòc nıŞa ";

char *mgYahoo = "Yes!";
char *mgContinueChat = "%s : Tôi noìi nhiêÌu ğêìn mıìc cıìng caÒ lıõŞi laòi rôÌi! WOW q^_^p";
char *mgRecvItem = "  Baòn ğaŞ nhâòn ğıõòc moìn ğôÌ ( %s )  ";

char *mgItemTimeOut = "Moìn ğôÌ ğaŞ biò xoaì ( %s ) vıõòt quaì thõÌi haòn sıÒ duòng cho pheìp ";
char *mgSOD_Clear = " Chuìc mıÌng! Baòn ğaŞ nhâòn ğıõòc giaÒi thıõÒng( %d VaÌng) ";

char *mgBlessCrystal_01 = "  Giõìi haòn cho viêòc triêòu tâòp cuÒa baòn ğaŞ hêìt  ";
char *mgBlessCrystal_02 = "   Baòn chiÒ coì thêÒ triêòu tâòp môŞi lâÌn môòt quaìi vâòt   ";
char *mgBlessCrystal_03 = "   Baòn không thêÒ sıÒ duòng viên ngoòc naÌy  ";


// Bellatra
char *g_lpBellatraTeamNameText[] = 
{
	"ThıÒ thaìch cuÒa Nıõìc",
	"ThıÒ thaìch cuÒa Ğâìt",
	"ThıÒ thaìch cuÒa Gioì ",
	"ThıÒ thaìch cuÒa LıÒa",
	"TâÌng Nhâòt Quan",
	"TâÌng Nguyêòt Quang",
};

char *g_lpBellatraResult_Text1 = "%s of";
char *g_lpBellatraResult_Text2 = "%s and %s of";
char *g_lpBellatraResult_Text3 = "Join team";
char *g_lpBellatraResult_Text4 = "ChuyêÒn lên tâÌng cao hõn.";
