#include "TextMessage.h"

char *szAppName=" Mundo Priston ";


char *mgRequestTrade = " Se envió un pedido de intercambio a %s ";
char *mgRequestTrade2 = " %s está demasiado lejos para pedir un intercambio ";

char *mgDiconnect = " Se perdió la conexión con el Servidor ";
char *mgDiconnect1 = " Se perdió la conexión con el Servidor (1) ";
char *mgDiconnect2 = " Se perdió la conexión con el Servidor (2) ";
char *mgDiconnect3 = " Se perdió la conexión con el Servidor (3) ";
char *mgDiconnect4 = " Se perdió la conexión con el Servidor (4) ";

char *mgCloseGame = " Abandonando el Juego... ";
char *mgCloseWindow = " Por favor, cierra la ventana actual antes de salir del juego ";
char *mgCloseBattle = " No se puede abandonar mientras se combate ";
/*
char *mgQuestName[][4] = {
	{	" Misión de cambio de Rango "	,	" Misión de Rank up(Completada) " , "ChangeJob1a.Msg" , "ChangeJob1b.Msg" },
	{	" Misión de cambio de Rango ",	" Examen de Rank-up(Hecho) " , "ChangeJob2a.Msg" , "ChangeJob1b.Msg" },
	{	" Misión de cambio de Rango "	,	" Misión de Rank up(Completada) " , "ChangeJob3a.Msg" , "ChangeJob1b.Msg" },

	{	" Misión de cambio de Rango [Segunda] "		,	" Misión de cambio de Rango[Segunda] " , "ChangeJob3-1.msg" , "ChangeJob3-2.msg" },
	{	" Misión de cambio de Rango [Segunda] "		,	" Misión de cambio de Rango(Completada) " , "ChangeJob3-3.msg" , "ChangeJob3-4.msg" },

	//Luchador Piquero Mecánico Caballero
	{	"Misión de cambio de Rango segunda[1] "		,	"Misión de cambio de Rango segunda[2] "		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-W1-2.msg" },
	{	"Misión de cambio de Rango segunda[3] "		,	"Misión de cambio de Rango segunda[4] "		, "Quest3\\ChangeJob3-W2-2.msg" , "Quest3\\ChangeJob3-W3-2.msg" },
	{	"Misión de cambio de Rango segunda[5] "		,	"Misión de cambio de Rango segunda[Completada] "	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//Arquero Atalanta
	{	"Misión de cambio de Rango segunda[1] "		,	"Misión de cambio de Rango segunda[2] "		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-R1-2.msg" },
	{	"Misión de cambio de Rango segunda[3] "		,	"Misión de cambio de Rango segunda[4] "		, "Quest3\\ChangeJob3-R2-2.msg" , "Quest3\\ChangeJob3-R3-2.msg" },
	{	"Misión de cambio de Rango segunda[5] "		,	"Misión de cambio de Rango segunda[Completada] "	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//Sacerdotisa Mago
	{	"Misión de cambio de Rango segunda[1] "		,	"Misión de cambio de Rango segunda[2] "		, "Quest3\\ChangeJob3-1.msg" , "Quest3\\ChangeJob3-M1-2.msg" },
	{	"Misión de cambio de Rango segunda[3] "		,	"Misión de cambio de Rango segunda[4] "		, "Quest3\\ChangeJob3-M2-2.msg" , "Quest3\\ChangeJob3-M3-2.msg" },
	{	"Misión de cambio de Rango segunda[5] "		,	"Misión de cambio de Rango segunda[Completada] "	, "Quest3\\ChangeJob3-3.msg" , "Quest3\\ChangeJob3-4.msg" },

	//·¹º§º° Äù½ºÆ®
	{	" Para ella "	,	" Para ella(completada) " ,	"LevelQuest\\Quest30.Msg" , "LevelQuest\\Quest30a.Msg" },	//14
	{	" La Cueva "	,	" La Cueva(completada) " ,					"LevelQuest\\Quest55.Msg" , "LevelQuest\\Quest55a.Msg" },	//15
	{	" La Cueva "	,	" La Cueva(completada) " ,					"LevelQuest\\Quest55_2.Msg" , "LevelQuest\\Quest55_2a.Msg" }, //16
	{	" Ayudando a Michel"	,	" Ayudando a Michel(completada) " ,	"LevelQuest\\Quest70.Msg" , "LevelQuest\\Quest70a.Msg" },	//17
	{	" Furia Encerrada ",	" Furia Encerrada(completada) " ,				"LevelQuest\\Quest80.Msg" , "LevelQuest\\Quest80a.Msg" },	//18
	{	" Lágrimas de Chalia "," Lágrimas de Chalia(completada) " ,				"LevelQuest\\Quest85.Msg" , "LevelQuest\\Quest85a.Msg" },	//19
	{	" Villa de Eura "," Villa de Eura(completada) " ,					"LevelQuest\\Quest90.Msg" , "LevelQuest\\Quest90a.Msg" },	//20

	//º¸³Ê½º ½ºÅÝ Äù½ºÆ®
	{	" Prueba del Reino ",	" Prueba del Reino(Completada) " ,	"LevelQuest\\Quest_7State_1.msg" , "LevelQuest\\Quest_7State_end.msg" },	//21
	{	" Prueba del Reino ",	" Prueba del Reino(Completada) ",	"LevelQuest\\Quest_7State_2.msg" , "LevelQuest\\Quest_7State_end.msg" },	//22
	{	" Prueba del Reino ",	" Prueba del Reino(Completada) ",	"LevelQuest\\Quest_7State_3.msg" , "LevelQuest\\Quest_7State_end.msg" },	//23

	{	" Amargo Sufrimiento "	,	" Amargo Sufrimiento(Completada) " ,	"LevelQuest\\Quest_10State_1.msg" , "LevelQuest\\Quest_10State_end.msg" },	//24
	{	" Amargo Sufrimiento "	,	" Amargo Sufrimiento(Completada) " ,	"LevelQuest\\Quest_10State_2_1.msg" , "LevelQuest\\Quest_10State_end.msg" },//25
	{	" Amargo Sufrimiento "	,	" Amargo Sufrimiento(Completada) " ,	"LevelQuest\\Quest_10State_2_2.msg" , "LevelQuest\\Quest_10State_end.msg" },//26
	{	" Amargo Sufrimiento "	,	" Amargo Sufrimiento(Completada) " ,	"LevelQuest\\Quest_10State_2_3.msg" , "LevelQuest\\Quest_10State_end.msg" },//27

	//3Â÷ Àü¾÷ Äù½ºÆ®
	{	" Misión de Trabajo 3[1] "	,	" Misión de Trabajo 3(Completada) " ,	"Quest4\\ChangeJob4_1.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//28
	{	" Misión de Trabajo 3[2] "	,	" Misión de Trabajo 3(Completada) " ,	"Quest4\\ChangeJob4_2.msg" ,	"Quest4\\ChangeJob4_5.msg" },	//29
	{	" Misión de Trabajo 3[3] "	,	" Misión de Trabajo 3(Completada) " ,	"Quest4\\ChangeJob4_3_1.msg" ,	"Quest4\\ChangeJob4_3_2.msg" },	//30
	{	" Misión de Trabajo 3[3] "	,	" Misión de Trabajo 3(Completada) " ,	"Quest4\\ChangeJob4_3_3.msg" ,	"Quest4\\ChangeJob4_3_4.msg" },	//31
	{	" Misión de Trabajo 3[3] "	,	" Misión de Trabajo 3(Completada) " ,	"Quest4\\ChangeJob4_3_5.msg" ,	"Quest4\\ChangeJob4_3_6.msg" },	//32
	{	" Misión de Trabajo 3[4] "	,	" Misión de Trabajo 3(Completada) " ,	"Quest4\\ChangeJob4_4.msg" ,	"Quest4\\ChangeJob4_5.msg" }	//33

};
*/
char *mgRefuseWhisper = " El Mensaje Privado fue rehusado ";
char *mgWeightOver = " Sobrepasado ";

char *mgYahoo = " !Sí! ";
char *mgContinueChat = " %s : hablo demasiado, !mi lengua se congeló! WOW -_-; ";
char *mgRecvItem = "  Has recibido el objeto( %s )  ";

char *mgItemTimeOut = " El objeto fue borrado por su tiempo de validez ";
char *mgSOD_Clear = " !Felicitaciones!!! Ganaste el premio de ( %dGold) ";


char *mgBlessCrystal_01 = "  Se ha excedido la cantidad de invocaciones  ";
char *mgBlessCrystal_02 = "   Puedes invocar sólo una vez   ";
char *mgBlessCrystal_03 = "   No puedes usar este cristal   ";


// Bellatra
char *g_lpBellatraTeamNameText[] =
{
	" Tribulación de Agua ",
	" Tribulación de Suelo ",
	" Tribulación de Viento ",
	" Tribulación de Fuego ",
	" Escenario del Sol ",
	" Escenario de la Luna ",
};

char *g_lpBellatraResult_Text1 = " %s de ";
char *g_lpBellatraResult_Text2 = " %s y %s de ";
char *g_lpBellatraResult_Text3 = " Une equipo ";
char *g_lpBellatraResult_Text4 = " Cambio de Rango para la Torre Alta. ";
