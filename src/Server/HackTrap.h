/*
#define sinNPC_SHOP				0x00000001	//상점 NPC
#define sinNPC_MIX				0x00000002	//조합 NPC
#define sinNPC_AGING			0x00000004	//에이징 NPC
#define sinNPC_WARE				0x00000008	//창고 NPC
#define sinNPC_SKILL			0x00000010	//스킬 NPC
*/

int	rsHackTrap_FieldNPC[] = {
	sinNPC_SHOP,															//0
	0,																		//1
	0,																		//2
	sinNPC_SHOP|sinNPC_MIX|sinNPC_WARE|sinNPC_SKILL|sinNPC_FORCE|sinNPC_MANUFACTURE,			//3
	0,																		//4
	0,																		//5
	sinNPC_SHOP|sinNPC_WARE,												//6
	sinNPC_SHOP,															//7
	0,																		//8
	sinNPC_SHOP,															//9
	0,																		//10
	0,																		//11
	0,																		//12
	0,																		//13
	0,																		//14
	0,																		//15
	0,																		//16
	0,																		//17
	sinNPC_SHOP,															//18
	0,																		//19
	0,																		//20
	sinNPC_SHOP|sinNPC_AGING|sinNPC_WARE|sinNPC_SKILL|sinNPC_FORCE|sinNPC_SMELTING,			//21
	0,																		//22
	0,																		//23
	0,																		//24
	0,																		//25
	0,																		//26
	0,																		//27
	0,																		//28
	sinNPC_SHOP|sinNPC_WARE|sinNPC_FORCE,									//29
	0,																		//30
	0,																		//31
	0,																		//32
	sinNPC_SHOP|sinNPC_WARE,												//33
	0,																		//34
	0,																		//35
	0,																		//36
	0,																		//37
	0,																		//38
	0,																		//39
	0,																		//40
	0,																		//41
	0,																		//42
	0,																		//43
	0,																		//44
	0,																		//45
	0,																		//46
	0,																		//47
	0,																		//48
	0,																		//49
	0,																		//50
};

