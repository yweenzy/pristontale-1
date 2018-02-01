#include  "TextMessage.h" 
char *szAppName= "Priston Tale " ;
char *mgRequestTrade =  "เสนอการซื้อขายไปยัง %s " ;
char *mgRequestTrade2 =  "%s อยู่ไกลเกินไปไม่สามารถแลกเปลี่ยนได้ ";

char *mgDiconnect =  "สัญญาณขัดข้อง ไม่สามารถติดต่อกับเซิร์ฟเวอร์ได้" ;
char *mgDiconnect1 =  "สัญญาณขัดข้อง ไม่สามารถติดต่อกับเซิร์ฟเวอร์(1) ได้ ";
char *mgDiconnect2 =  "สัญญาณขัดข้อง ไม่สามารถติดต่อกับเซิร์ฟเวอร์(2) ได้ ";
char *mgDiconnect3 =  "สัญญาณขัดข้อง ไม่สามารถติดต่อกับเซิร์ฟเวอร์(3) ได้ ";
char *mgDiconnect4 =  "สัญญาณขัดข้อง ไม่สามารถติดต่อกับเซิร์ฟเวอร์(4) ได้ ";

char *mgCloseGame =  "ขอบคุณที่เล่น PT ค่ะ " ;
char *mgCloseWindow =  "กรุณาปิด Window ที่เปิดอยู่ก่อน " ;
char *mgCloseBattle =  "ไม่สามารถออกจากเกมได้ ขณะต่อสู้ " ;
/*
char *mgQuestName[][4] = {
	{	 "Rank-up Exam " 	,	 "การเปลี่ยนคลาส (สมบูรณ์)"  ,  "ChangeJob1a.Msg"  ,  "ChangeJob1b.Msg"  },
	{	 "Rank-up Exam [Royal Jelly] " 	,	 "การเปลี่ยนคลาส (สมบูรณ์)"  ,  "ChangeJob2a.Msg"  ,  "ChangeJob1b.Msg"  },
	{	 "Rank-up Exam [Hair growth spray] " 	,	 "Rank-up Exam (Done)"  ,  "ChangeJob3a.Msg"  ,  "ChangeJob1b.Msg"  },
	{	"การเปลี่ยนคลาส  [ครั้งที่ 2] "		,	"การเปลี่ยนคลาส  [ครั้งที่ 2] " , "ChangeJob3-1.msg" , "ChangeJob3-2.msg" },
	{	"การเปลี่ยนคลาส  [ครั้งที่ 2] "		,	"การเปลี่ยนคลาส  (สมบูรณ์) " , "ChangeJob3-3.msg" , "ChangeJob3-4.msg" },

	//Fighter Pikeman Mechanic Knight
	{	"การเปลี่ยนคลาสที่ 2 [1] "		,	"การเปลี่ยนคลาสที่ 2 [2] "		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-W1-2.msg" },
	{	"การเปลี่ยนคลาสที่ 2 [3]  "		,	"การเปลี่ยนคลาสที่ 2 [4] "		, "Quest3\\ChangeJob3-W2-2.msg" , "Quest3\\ChangeJob3-W3-2.msg" },
	{	"การเปลี่ยนคลาสที่ 2 [5] "		,	"การเปลี่ยนคลาสที่ 2 [สมบูรณ์] "	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//Archer Atlanta
	{	"การเปลี่ยนคลาสที่ 2 [1] "		,	"การเปลี่ยนคลาสที่ 2 [2] "		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-R1-2.msg" },
	{	"การเปลี่ยนคลาสครั้งที่ 2 [3] "		,	"การเปลี่ยนคลาสที่ 2 [4] "		, "Quest3\\ChangeJob3-R2-2.msg" , "Quest3\\ChangeJob3-R3-2.msg" },
	{	"การเปลี่ยนคลาสที่ 2 [5] "		,	"การเปลี่ยนคลาสที่ 2 [สมบูรณ์]"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//Pristess Magician
	{	"การเปลี่ยนคลาสที่ 2 [1] "		,	"การเปลี่ยนคลาสที่ 2 [2] "		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-M1-2.msg" },
	{	"การเปลี่ยนคลาสที่ 2 [3] "		,	"การเปลี่ยนคลาสที่ 2 [4] "		, "Quest3\\ChangeJob3-M2-2.msg" , "Quest3\\ChangeJob3-M3-2.msg" },
	{	"การเปลี่ยนคลาสที่ 2 [5] "		,	"การเปลี่ยนคลาสที่ 2 [สมบูรณ์] "	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },
		
	// Level Quest
	{	"แด่เธอ"		,	"แด่เธอ (สําเร็จ)" 	,	"LevelQuest\\Quest30.Msg" , "LevelQuest\\Quest30a.Msg" },	//14
	{	"เดอะเคฟ "		,	"เดอะเคฟ(สําเร็จ)"	,	"LevelQuest\\Quest55.Msg" , "LevelQuest\\Quest55a.Msg" },	//15
	{	"เดอะเคฟ "		,	"เดอะเคฟ(สําเร็จ)"	,	"LevelQuest\\Quest55_2.Msg" , "LevelQuest\\Quest55_2a.Msg" }, //16
	{	"มิตรภาพแด่มิเชล "	,	"มิตรภาพแด่มิเชล(สําเร็จ) "	,	"LevelQuest\\Quest70.Msg" , "LevelQuest\\Quest70a.Msg" },	//17
	{	"ผนึก Fury"		,	"ผนึก Fury(สําเร็จ)"	,	"LevelQuest\\Quest80.Msg" , "LevelQuest\\Quest80a.Msg" },	//18
	{	"หยาดนํ้าตาคาร์เลีย"	,	"หยาดนํ้าตาคาร์เลีย(สําเร็จ)",	"LevelQuest\\Quest85.Msg" , "LevelQuest\\Quest85a.Msg" },	//19
	{	"หมู่บ้านยูร่า "	,	"หมู่บ้านยูร่า(สําเร็จ)"	,	"LevelQuest\\Quest90.Msg" , "LevelQuest\\Quest90a.Msg" },	//20
	
	//เควสโบนัสแสตท
	{	"บททดสอบแห่งราชอาณาจักร"	,	"บททดสอบแห่งราชอาณาจักร(เรียบร้อย)" ,	"LevelQuest\\Quest_7State_1.msg" , "LevelQuest\\Quest_7State_end.msg" },	//21
	{	"บททดสอบแห่งราชอาณาจักร"	,	"บททดสอบแห่งราชอาณาจักร(เรียบร้อย)" ,	"LevelQuest\\Quest_7State_2.msg" , "LevelQuest\\Quest_7State_end.msg" },	//22
	{	"บททดสอบแห่งราชอาณาจักร"	,	"บททดสอบแห่งราชอาณาจักร(เรียบร้อย)" ,	"LevelQuest\\Quest_7State_3.msg" , "LevelQuest\\Quest_7State_end.msg" },	//23

	{	"หนทางแห่งความยากลําบาก"	,	"หนทางแห่งความยากลําบาก(สําเร็จ)" ,	"LevelQuest\\Quest_10State_1.msg" , "LevelQuest\\Quest_10State_end.msg" },	//24
	{	"หนทางแห่งความยากลําบาก"	,	"หนทางแห่งความยากลําบาก(สําเร็จ)",	"LevelQuest\\Quest_10State_2_1.msg" , "LevelQuest\\Quest_10State_end.msg" },//25
	{	"หนทางแห่งความยากลําบาก"	,	"หนทางแห่งความยากลําบาก(สําเร็จ)"	"LevelQuest\\Quest_10State_2_2.msg" , "LevelQuest\\Quest_10State_end.msg" },//26
	{	"หนทางแห่งความยากลําบาก"	,	"หนทางแห่งความยากลําบาก(สําเร็จ)",	"LevelQuest\\Quest_10State_2_3.msg" , "LevelQuest\\Quest_10State_end.msg" },//27

	//3เควสเปลี่ยนอาชีพรอบ3
	{	"เควสเปลี่ยนอาชีพรอบที่3[1]"	,	"เควสเปลี่ยนอาชีพรอบที่3(สําเร็จ)" ,	"Quest4\\ChangeJob4_1.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//28
	{	"เควสเปลี่ยนอาชีพรอบที่3[2]"	,	"เควสเปลี่ยนอาชีพรอบที่3(สําเร็จ)",	"Quest4\\ChangeJob4_2.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//29
	{	"เควสเปลี่ยนอาชีพรอบที่3[3]"	,	"เควสเปลี่ยนอาชีพรอบที่3(สําเร็จ)",	"Quest4\\ChangeJob4_3_1.msg" ,	"Quest4\\ChangeJob4_3_2.msg" },	//30
	{	"เควสเปลี่ยนอาชีพรอบที่3[3]"	,	"เควสเปลี่ยนอาชีพรอบที่3(สําเร็จ)",	"Quest4\\ChangeJob4_3_3.msg" ,	"Quest4\\ChangeJob4_3_4.msg" },	//31
	{	"เควสเปลี่ยนอาชีพรอบที่3[3]"	,	"เควสเปลี่ยนอาชีพรอบที่3(สําเร็จ)" ,	"Quest4\\ChangeJob4_3_5.msg" ,	"Quest4\\ChangeJob4_3_6.msg" },	//32
	{	"เควสเปลี่ยนอาชีพรอบที่3[4]"	,	"เควสเปลี่ยนอาชีพรอบที่3(สําเร็จ)",	"Quest4\\ChangeJob4_4.msg" ,	"Quest4\\ChangeJob4_5.msg" }	//33

};

*/
char *mgRefuseWhisper =  "PM ของท่านถูกปฏิเสธ " ;
char *mgWeightOver =  "น้ำหนักเกิน.. " ;

char *mgYahoo =  "Yes!" ;
char *mgContinueChat = "%s :  โม้มากไปหน่อย  คอแห้งเลย เหอเหอ -_-; ";
char *mgRecvItem = "   ได้รับไอเทม  ( %s ) แล้ว";

char *mgItemTimeOut = " ไอเทม  ( %s ) หายไปเนื่องจากหมดอายุการใช้ ";
char *mgSOD_Clear = " ขอแสดงความยินดี กับเงินรางวัลที่ท่านได้รับÝ ( %dGold) ";

char *mgBlessCrystal_01 = "เกินจำนวนที่สามารถเรียกได้";
char *mgBlessCrystal_02 = "การเรียกสามารถเรียกได้ทีละครั้งเท่านั้น ";
char *mgBlessCrystal_03 = "ใช้คริสตัลไม่ได้";

// Bellatra
char *g_lpBellatraTeamNameText[] = 
{
	"Tribulation of Water",
	"Tribulation of Ground",
	"Tribulation of Wind",
	"Tribulation of Fire",
	"The Stage of Sun",
	"The Stage of Moon",
};

char *g_lpBellatraResult_Text1 = "%s ของ ";
char *g_lpBellatraResult_Text2 = "%s และ %s ของ ";
char *g_lpBellatraResult_Text3 = "เข้าร่วมทีม ";
char *g_lpBellatraResult_Text4 = "ขึ้นสู่ชั้นบนของทาวเวอร์.";
