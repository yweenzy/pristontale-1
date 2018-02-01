char *szAppName="프리스톤 테일";


char *mgRequestTrade = "%s님께 거래를 신청했습니다";
char *mgRequestTrade2 = "%s님은 거리가 멀어서 거래 신청을 할수 없습니다";

char *mgDiconnect = "서버와의 연결이 끊어 졌습니다";
char *mgDiconnect1 = "서버와의 연결이 끊어 졌습니다 (1)";
char *mgDiconnect2 = "서버와의 연결이 끊어 졌습니다 (2)";
char *mgDiconnect3 = "서버와의 연결이 끊어 졌습니다 (3)";
char *mgDiconnect4 = "서버와의 연결이 끊어 졌습니다 (4)";

char *mgCloseGame = "게임을 종료 합니다";
char *mgCloseWindow = "사용중인 창을 닫고 종료 하십시오";
char *mgCloseBattle = "전투중에는 종료할수 없습니다";
/*
char *mgQuestName[][4] = {
	{	"전업시험"	,	"전업시험 (완료)" , "ChangeJob1a.Msg" , "ChangeJob1b.Msg" },
	{	"전업시험 [로얄제리]"	,	"전업시험 (완료)" , "ChangeJob2a.Msg" , "ChangeJob1b.Msg" },
	{	"전업시험 [발모제]"		,	"전업시험 (완료)" , "ChangeJob3a.Msg" , "ChangeJob1b.Msg" },

	{	"전업시험 [두번째]"		,	"전업시험 [두번째]" , "ChangeJob3-1.msg" , "ChangeJob3-2.msg" },
	{	"전업시험 [두번째]"		,	"전업시험 (완료)" , "ChangeJob3-3.msg" , "ChangeJob3-4.msg" },

	//파이터 파이크맨 메카니션 나이트
	{	"전업시험 2차[1]"		,	"전업시험 2차[2]"		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-W1-2.msg" },
	{	"전업시험 2차[3]"		,	"전업시험 2차[4]"		, "Quest3\\ChangeJob3-W2-2.msg" , "Quest3\\ChangeJob3-W3-2.msg" },
	{	"전업시험 2차[5]"		,	"전업시험 2차[완료]"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//아쳐 아탈란타
	{	"전업시험 2차[1]"		,	"전업시험 2차[2]"		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-R1-2.msg" },
	{	"전업시험 2차[3]"		,	"전업시험 2차[4]"		, "Quest3\\ChangeJob3-R2-2.msg" , "Quest3\\ChangeJob3-R3-2.msg" },
	{	"전업시험 2차[5]"		,	"전업시험 2차[완료]"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//프리스티스 메지션
	{	"전업시험 2차[1]"		,	"전업시험 2차[2]"		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-M1-2.msg" },
	{	"전업시험 2차[3]"		,	"전업시험 2차[4]"		, "Quest3\\ChangeJob3-M2-2.msg" , "Quest3\\ChangeJob3-M3-2.msg" },
	{	"전업시험 2차[5]"		,	"전업시험 2차[완료]"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//레벨별 퀘스트
	{	"그녀들을 위하여"	,	"그녀들을 위하여(완료)" ,	"LevelQuest\\Quest30.Msg" , "LevelQuest\\Quest30a.Msg" },	//14
	{	"The Cave"	,	"The Cave(완료)" ,					"LevelQuest\\Quest55.Msg" , "LevelQuest\\Quest55a.Msg" },	//15
	{	"The Cave"	,	"The Cave(완료)" ,					"LevelQuest\\Quest55_2.Msg" , "LevelQuest\\Quest55_2a.Msg" }, //16
	{	"미켈레와의 우정"	,	"미켈레와의 우정(완료)" ,	"LevelQuest\\Quest70.Msg" , "LevelQuest\\Quest70a.Msg" },	//17
	{	"봉인된 퓨리",	"봉인된 퓨리(완료)" ,				"LevelQuest\\Quest80.Msg" , "LevelQuest\\Quest80a.Msg" },	//18
	{	"칼리아의 눈물","칼리아의 눈물(완료)" ,				"LevelQuest\\Quest85.Msg" , "LevelQuest\\Quest85a.Msg" },	//19
	{	"유라 빌리지","유라 빌리지(완료)" ,					"LevelQuest\\Quest90.Msg" , "LevelQuest\\Quest90a.Msg" },	//20

	//보너스 스텟 퀘스트
	{	"왕국의시험"	,	"왕국의시험(완료)" ,	"LevelQuest\\Quest_7State_1.msg" , "LevelQuest\\Quest_7State_end.msg" },	//21
	{	"왕국의시험"	,	"왕국의시험(완료)" ,	"LevelQuest\\Quest_7State_2.msg" , "LevelQuest\\Quest_7State_end.msg" },	//22
	{	"왕국의시험"	,	"왕국의시험(완료)" ,	"LevelQuest\\Quest_7State_3.msg" , "LevelQuest\\Quest_7State_end.msg" },	//23

	{	"어려운시련"	,	"어려운시련(완료)" ,	"LevelQuest\\Quest_10State_1.msg" , "LevelQuest\\Quest_10State_end.msg" },	//24
	{	"어려운시련"	,	"어려운시련(완료)" ,	"LevelQuest\\Quest_10State_2_1.msg" , "LevelQuest\\Quest_10State_end.msg" },//25
	{	"어려운시련"	,	"어려운시련(완료)" ,	"LevelQuest\\Quest_10State_2_2.msg" , "LevelQuest\\Quest_10State_end.msg" },//26
	{	"어려운시련"	,	"어려운시련(완료)" ,	"LevelQuest\\Quest_10State_2_3.msg" , "LevelQuest\\Quest_10State_end.msg" },//27

	//3차 전업 퀘스트
	{	"전업시험 3차[1]"	,	"전업시험 3차(완료)" ,	"Quest4\\ChangeJob4_1.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//28
	{	"전업시험 3차[2]"	,	"전업시험 3차(완료)" ,	"Quest4\\ChangeJob4_2.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//29
	{	"전업시험 3차[3]"	,	"전업시험 3차(완료)" ,	"Quest4\\ChangeJob4_3_1.msg" ,	"Quest4\\ChangeJob4_3_2.msg" },	//30
	{	"전업시험 3차[3]"	,	"전업시험 3차(완료)" ,	"Quest4\\ChangeJob4_3_3.msg" ,	"Quest4\\ChangeJob4_3_4.msg" },	//31
	{	"전업시험 3차[3]"	,	"전업시험 3차(완료)" ,	"Quest4\\ChangeJob4_3_5.msg" ,	"Quest4\\ChangeJob4_3_6.msg" },	//32
	{	"전업시험 3차[4]"	,	"전업시험 3차(완료)" ,	"Quest4\\ChangeJob4_4.msg" ,	"Quest4\\ChangeJob4_5.msg" }	//33

};
*/
char *mgRefuseWhisper = "귓말이 거부되었습니다";
char *mgWeightOver = "무계를 초과했습니다        ";

char *mgYahoo = "야호";
char *mgContinueChat = "%s : 너무 말을 많이 했더니 혀가 굳어 버렸다! 우와 -_-;";
char *mgRecvItem = "   아이템 ( %s ) 을 받았습니다   ";

char *mgItemTimeOut = "아이템 ( %s ) 사용기간이 종료 되어 제거되었습니다";
char *mgSOD_Clear = " 축하합니다. 상금 %d원을 획득했습니다 ";


char *mgBlessCrystal_01 = "  소환할수 있는 갯수를 초과했습니다  ";
char *mgBlessCrystal_02 = "   소환은 한 번씩만 할수 있습니다   ";
char *mgBlessCrystal_03 = "   크리스탈을 사용할수 없습니다   ";

char *mgGetQuestItem = "> (%s) 아이템을 획득했습니다";

// Bellatra
char *g_lpBellatraTeamNameText[] = 
{
	"물의 시련",
	"땅의 시련",
	"바람의 시련",
	"불의 시련",
	"태양의 장",
	"달의 장",
};

char *g_lpBellatraResult_Text1 = "%s 에";
char *g_lpBellatraResult_Text2 = "%s 과 %s 에";
char *g_lpBellatraResult_Text3 = "참가한 팀이";
char *g_lpBellatraResult_Text4 = "상위 탑으로 진출하였습니다.";
