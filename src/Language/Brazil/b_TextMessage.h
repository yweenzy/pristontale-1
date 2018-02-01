#include "TextMessage.h"

char *szAppName="Priston Tale";


char *mgRequestTrade = "Pedido de Troca enviado para %s";
char *mgRequestTrade2 = "%s está muito longe para realizar a Troca";

char *mgDiconnect = "Conexão perdida com o Servidor";
char *mgDiconnect1 = "Conexão perdida com o Servidor (1)";
char *mgDiconnect2 = "Conexão perdida com o Servidor (2)";
char *mgDiconnect3 = "Conexão perdida com o Servidor (3)";
char *mgDiconnect4 = "Conexão perdida com o Servidor (4)";

char *mgCloseGame = "Saindo do Jogo";
char *mgCloseWindow = "Por favor, feche as janelas abertas, antes de sair do Jogo";
char *mgCloseBattle = "Você não pode sair durante a batalha";
/*
char *mgQuestName[][4] = {
	{	"Desafio de Classe"	,	"Desafio de Classe(completo)" , "ChangeJob1a.Msg" , "ChangeJob1b.Msg" },
	{	"Desafio de Classe"	,	"Desafio de Classe (completo)" , "ChangeJob2a.Msg" , "ChangeJob1b.Msg" },
	{	"Desafio de Classe"	,	"Desafio de Classe(completo)" , "ChangeJob3a.Msg" , "ChangeJob1b.Msg" },

	{	"2o Desafio de Classe"		,	"Rank up quest [Second]" , "ChangeJob3-1.msg" , "ChangeJob3-2.msg" },
	{	"2o Desafio de Classe"		,	"Rank up quest (Completed)" , "ChangeJob3-3.msg" , "ChangeJob3-4.msg" },

	//Fighter Pikeman Mecanicion Knight
	{	"2o Desafio de Classe[1]"		,	"2o Desafio de Classe[2]"		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-W1-2.msg" },
	{	"2o Desafio de Classe[3]"		,	"2o Desafio de Classe[4]"		, "Quest3\\ChangeJob3-W2-2.msg" , "Quest3\\ChangeJob3-W3-2.msg" },
	{	"2o Desafio de Classe[5]"		,	"2o Desafio de Classe(completo)"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//Archer Atalanta
	{	"2o Desafio de Classe[1]"		,	"2o Desafio de Classe[2]"		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-R1-2.msg" },
	{	"2o Desafio de Classe[3]"		,	"2o Desafio de Classe[4]"		, "Quest3\\ChangeJob3-R2-2.msg" , "Quest3\\ChangeJob3-R3-2.msg" },
	{	"2o Desafio de Classe[5]"		,	"2o Desafio de Classe(completo)"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//Priestess Magicion
	{	"2o Desafio de Classe[1]"		,	"2o Desafio de Classe[2]"		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-M1-2.msg" },
	{	"2o Desafio de Classe[3]"		,	"2o Desafio de Classe[4]"		, "Quest3\\ChangeJob3-M2-2.msg" , "Quest3\\ChangeJob3-M3-2.msg" },
	{	"2o Desafio de Classe[5]"		,	"2o Desafio de Classe(completo)"	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },
	
	//·¹º§º° Äù½ºÆ®
	{	"Por ela"	,	"Por ela (completo)" ,	"LevelQuest\\Quest30.Msg" , "LevelQuest\\Quest30a.Msg" },	//14
	{	"A Caverna"	,	"A Caverna (completo)" ,					"LevelQuest\\Quest55.Msg" , "LevelQuest\\Quest55a.Msg" },	//15
	{	"A Caverna"	,	"A Caverna (completo)" ,					"LevelQuest\\Quest55_2.Msg" , "LevelQuest\\Quest55_2a.Msg" }, //16
	{	"Amizade de Michelle"	,	"Amizade de Michelle (completo)" ,	"LevelQuest\\Quest70.Msg" , "LevelQuest\\Quest70a.Msg" },	//17
	{	"O Fúria aprisionado",	"O Fúria aprisionado (completo)" ,				"LevelQuest\\Quest80.Msg" , "LevelQuest\\Quest80a.Msg" },	//18
	{	"Lágrimas de Khália","Lágrimas de Khália (completo)" ,				"LevelQuest\\Quest85.Msg" , "LevelQuest\\Quest85a.Msg" },	//19
	{	"A Vila de Eura","A Vila de Eura (ccompleto)" ,					"LevelQuest\\Quest90.Msg" , "LevelQuest\\Quest90a.Msg" },	//20

	//º¸³Ê½º ½ºÅÝ Äù½ºÆ®
	{	"Teste Real",	"Teste Real (completo)" ,	"LevelQuest\\Quest_7State_1.msg" , "LevelQuest\\Quest_7State_end.msg" },	//21
	{	"Teste Real",	"Teste Real (completo)",	"LevelQuest\\Quest_7State_2.msg" , "LevelQuest\\Quest_7State_end.msg" },	//22
	{	"Teste Real",	"Teste Real (completo)",	"LevelQuest\\Quest_7State_3.msg" , "LevelQuest\\Quest_7State_end.msg" },	//23

	{	"Desafio amargo"	,	"Desafio amargo (completo)" ,		"LevelQuest\\Quest_10State_1.msg" , "LevelQuest\\Quest_10State_end.msg" },	//24
	{	"Desafio amargo"	,	"Desafio amargo (completo)" ,		"LevelQuest\\Quest_10State_2_1.msg" , "LevelQuest\\Quest_10State_end.msg" },//25
	{	"Desafio amargo"	,	"Desafio amargo (completo)" ,		"LevelQuest\\Quest_10State_2_2.msg" , "LevelQuest\\Quest_10State_end.msg" },//26
	{	"Desafio amargo"	,	"Desafio amargo (completo)" ,		"LevelQuest\\Quest_10State_2_3.msg" , "LevelQuest\\Quest_10State_end.msg" },//27

	//3Â÷ Àü¾÷ Äù½ºÆ®
	{	"3o Desafio de Classe[1]"	,	"3o Desafio de Classe(completo)" ,	"Quest4\\ChangeJob4_1.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//28
	{	"3o Desafio de Classe[2]"	,	"3o Desafio de Classe(completo)" ,	"Quest4\\ChangeJob4_2.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//29
	{	"3o Desafio de Classe[3]"	,	"3o Desafio de Classe(completo)" ,	"Quest4\\ChangeJob4_3_1.msg" ,	"Quest4\\ChangeJob4_3_2.msg" },	//30
	{	"3o Desafio de Classe[3]"	,	"3o Desafio de Classe(completo)" ,	"Quest4\\ChangeJob4_3_3.msg" ,	"Quest4\\ChangeJob4_3_4.msg" },	//31
	{	"3o Desafio de Classe[3]"	,	"3o Desafio de Classe(completo)" ,	"Quest4\\ChangeJob4_3_5.msg" ,	"Quest4\\ChangeJob4_3_6.msg" },	//32
	{	"3o Desafio de Classe[4]"	,	"3o Desafio de Classe(completo)" ,	"Quest4\\ChangeJob4_4.msg" ,	"Quest4\\ChangeJob4_5.msg" }	//33

};
*/
char *mgRefuseWhisper = "Msg pessoal recusada";
char *mgWeightOver = "Limite de Peso ";

char *mgYahoo = "Sim!";
char *mgContinueChat = "%s : Eu falo demais! Acho que minha língua vai congelar... Ai... -_-;";
char *mgRecvItem = "  Você recebeu o item( %s )  ";

char *mgItemTimeOut = "O item foi deletado pelo término ( %s ) do prazo de validade";
char *mgSOD_Clear = " Parabéns! Você ganhou a recompensa de ( %dOuro) ";


char *mgBlessCrystal_01 = "  O limite de invocações já foi ultrapassado  ";
char *mgBlessCrystal_02 = "   Você só pode invocar um monstro, por vez   ";
char *mgBlessCrystal_03 = "   Você não pode usar este Cristal   ";


// Bellatra
char *g_lpBellatraTeamNameText[] = 
{
	"Batalha da Água",
	"Batalha da Terra",
	"Batalha do Vento",
	"Batalha do Fogo",
	"Batalha do Sol",
	"Batalha da Lua",
};

char *g_lpBellatraResult_Text1 = "%s de";
char *g_lpBellatraResult_Text2 = "%s e %s of";
char *g_lpBellatraResult_Text3 = "Juntar-se ao grupo";
char *g_lpBellatraResult_Text4 = "Avançar para Torre superior.";
