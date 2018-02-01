#include "TextMessage.h"

char *szAppName="プリストンテール";


char *mgRequestTrade = "%s様に取引を申し込みました。";
char *mgRequestTrade2 = "%s樣は距離が遠いため、取引を申し込めません。";

char *mgDiconnect  = "サ－バ－との接続が切れました。";
char *mgDiconnect1 = "サ－バ－との接続が切れました。(1)";
char *mgDiconnect2 = "サ－バ－との接続が切れました。(2)";
char *mgDiconnect3 = "サ－バ－との接続が切れました。(3)";
char *mgDiconnect4 = "サ－バ－との接続が切れました。(4)";

char *mgCloseGame = "ゲ－ムを終了します。";
char *mgCloseWindow = "使用中のウィンドウを閉じてから終了してください。";
char *mgCloseBattle = "戦闘中は終了できません。";
/*
char *mgQuestName[][4] = {
	{"転職クエスト","転職クエスト(完了)","ChangeJob1a.Msg","ChangeJob1b.Msg"},
	{"転職クエスト[ローヤルゼリー]","転職クエスト(完了)" , "ChangeJob2a.Msg" , "ChangeJob1b.Msg" },
	{"転職クエスト[発毛剤]","転職クエスト(完了)" , "ChangeJob3a.Msg" , "ChangeJob1b.Msg" },
	
	{	"転職クエスト[二回目]"	,	"転職クエスト[二回目]" , "ChangeJob3-1.msg" , "ChangeJob3-2.msg" },
	{	"転職クエスト[二回目]"	,	"転職クエスト(完了)" , "ChangeJob3-3.msg" , "ChangeJob3-4.msg" },

	//ファイター　パイクマン　メカニシャン　ナイト
	{	"転職クエスト２次[1]"	,	"転職クエスト２次[2]"	, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-W1-2.msg" },
	{	"転職クエスト２次[3]"	,	"転職クエスト２次[4]"	, "Quest3\\ChangeJob3-W2-2.msg" , "Quest3\\ChangeJob3-W3-2.msg" },
	{	"転職クエスト２次[5]"	,	"転職クエスト２次[完了]"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//アーチャー　アタランタ
	{	"転職クエスト２次[1]"	,	"転職クエスト２次[2]"	, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-R1-2.msg" },
	{	"転職クエスト２次[3]"	,	"転職クエスト２次[4]"	, "Quest3\\ChangeJob3-R2-2.msg" , "Quest3\\ChangeJob3-R3-2.msg" },
	{	"転職クエスト２次[5]"	,	"転職クエスト２次[完了]"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//プリスティス　マジシャン
	{	"転職クエスト２次[1]"	,	"転職クエスト２次[2]"	, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-M1-2.msg" },
	{	"転職クエスト２次[3]"	,	"転職クエスト２次[4]"	, "Quest3\\ChangeJob3-M2-2.msg" , "Quest3\\ChangeJob3-M3-2.msg" },
	{	"転職クエスト２次[5]"	,	"転職クエスト２次[完了]"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },
	
	//ｷｹｺｧｺｰ ﾄｺﾆｮ
	{	"彼女達のために"		,	"彼女達のために(完了)"	, "LevelQuest\\Quest30.Msg" , "LevelQuest\\Quest30a.Msg" },	//14
	{	"The Cave"		,	"The Cave(完了)" 		, "LevelQuest\\Quest55.Msg" , "LevelQuest\\Quest55a.Msg" },	//15
	{	"The Cave"		,	"The Cave(完了)"		, "LevelQuest\\Quest55_2.Msg" , "LevelQuest\\Quest55_2a.Msg" }, //16
	{	"ミケレとの友情"		,	"ミケレとの友情(完了)"	, "LevelQuest\\Quest70.Msg" , "LevelQuest\\Quest70a.Msg" },	//17
	{	"封印されたフューリー"	,	"封印されたフューリー(完了)"	, "LevelQuest\\Quest80.Msg" , "LevelQuest\\Quest80a.Msg" },	//18
	{	"カリアの涙"		,	"カリアの涙(完了)" 		, "LevelQuest\\Quest85.Msg" , "LevelQuest\\Quest85a.Msg" },	//19
	{	"ユラビレッジ"		,	"ユラビレッジ(完了)"	, "LevelQuest\\Quest90.Msg" , "LevelQuest\\Quest90a.Msg" },	//20
	
	//ｺｸｳﾊｽｺ ｽｺﾅﾝ ﾄｺﾆｮ
	{	"王国の試験"	,	"王国の試験（完了）" ,	"LevelQuest\\Quest_7State_1.msg" , "LevelQuest\\Quest_7State_end.msg" },	//21
	{	"王国の試験"	,	"王国の試験（完了）" ,	"LevelQuest\\Quest_7State_2.msg" , "LevelQuest\\Quest_7State_end.msg" },	//22
	{	"王国の試験"	,	"王国の試験（完了）" ,	"LevelQuest\\Quest_7State_3.msg" , "LevelQuest\\Quest_7State_end.msg" },	//23

	{	"難しい試練"	,	"難しい試練（完了）" ,	"LevelQuest\\Quest_10State_1.msg" , "LevelQuest\\Quest_10State_end.msg" },	//24
	{	"難しい試練"	,	"難しい試練（完了）" ,	"LevelQuest\\Quest_10State_2_1.msg" , "LevelQuest\\Quest_10State_end.msg" },//25
	{	"難しい試練"	,	"難しい試練（完了）" ,	"LevelQuest\\Quest_10State_2_2.msg" , "LevelQuest\\Quest_10State_end.msg" },//26
	{	"難しい試練"	,	"難しい試練（完了）" ,	"LevelQuest\\Quest_10State_2_3.msg" , "LevelQuest\\Quest_10State_end.msg" },//27

	//3ﾂ・ﾀ・・ﾄｺﾆｮ
	{	"転職テスト3次[1]"	,	"転職テスト3次（完了）" ,	"Quest4\\ChangeJob4_1.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//28
	{	"転職テスト3次[2]"	,	"転職テスト3次（完了）" ,	"Quest4\\ChangeJob4_2.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//29
	{	"転職テスト3次[3]"	,	"転職テスト3次（完了）" ,	"Quest4\\ChangeJob4_3_1.msg" ,	"Quest4\\ChangeJob4_3_2.msg" },	//30
	{	"転職テスト3次[3]"	,	"転職テスト3次（完了）" ,	"Quest4\\ChangeJob4_3_3.msg" ,	"Quest4\\ChangeJob4_3_4.msg" },	//31
	{	"転職テスト3次[3]"	,	"転職テスト3次（完了）" ,	"Quest4\\ChangeJob4_3_5.msg" ,	"Quest4\\ChangeJob4_3_6.msg" },	//32
	{	"転職テスト3次[4]"	,	"転職テスト3次（完了）" ,	"Quest4\\ChangeJob4_4.msg" ,	"Quest4\\ChangeJob4_5.msg" }	//33

};
*/
char *mgRefuseWhisper = "プライベートチャットが拒否されました";
char *mgWeightOver = "重量を超過しました        ";

char *mgYahoo = "ヤッホ～";
char *mgContinueChat = "%s：話し過ぎて舌が固まってしまった！うわー-_-;";
char *mgRecvItem = "   アイテム( %s ) を受け取りました  ";

char *mgItemTimeOut = "アイテム ( %s ) 使用期間が過ぎて消去されました";
char *mgSOD_Clear = " おめでとうございます。賞金 %dGを獲得しました ";

char *mgBlessCrystal_01 = "  召喚できる個数を超えました。  ";
char *mgBlessCrystal_02 = "   召喚は1回のみできます。   ";
char *mgBlessCrystal_03 = "   クリスタルを使用できません。   ";

// Bellatra
char *g_lpBellatraTeamNameText[] = 
{
	"水の試練",
	"土の試練",
	"風の試練",
	"火の試練",
	"太陽の間",
	"月の間",
};

char *g_lpBellatraResult_Text1 = "%s に";
char *g_lpBellatraResult_Text2 = "%s と %s に";
char *g_lpBellatraResult_Text3 = "参加したチームが";
char *g_lpBellatraResult_Text4 = "上位の塔へ進みました";
