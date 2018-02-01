#ifndef _HoLinkHeader_H_
#define _HoLinkHeader_H_

#include "smlib3d\\smd3d.h"

#include "..\\drawsub.h"
#include "..\\smwsock.h"


#include "Sound\\dxwav.h"
#include "..\\character.h"
#include "..\\playmain.h"

#include "..\\smpacket.h"
#include "..\\record.h"
#include "..\\netplay.h"
#include "..\\fileread.h"

#include <stdlib.h>
#include "HoBaram\\HoAnimData.h"
#include "HoBaram\\HoPhysics.h"

#include "HoBaram\\HoEffect.h"
#include "HoBaram\\HoLogic.H"

#include "HoBaram\\HoParticle.h"
#include "Park\\HoMessageBox.H"

#include "HoBaram\\HoOpening.H"
#include "HoBaram\\HoLogin.H"
#include "HoBaram\\HoParty.H"

#include "HoBaram\\hoAssaParticleEffect.h"

#include "HoBaram\\HoSky.h"
#include "HoBaram\\LowLevelPetSystem.h"
#include "HoBaram\\NewEffect\\HoNewEffectFunction.h"

//박철호 : 2005-11-15 오후 7:52:17
// pc방 펫 관련
#include "HoBaram\\PCBangPetSystem.h"

//네트워크 관련...
extern smWINSOCK *ConnectServer_Main();
extern int HoRecvMessage( DWORD dwCode , void *RecvBuff );

extern char CharacterName1[256];
extern char CharacterName2[256];
extern int  CharacterPosX;
extern int  CharacterPosZ;

extern char		UserAccount[256];
extern char		UserPassword[256];

extern int GameStartField;

#define		MODE_NONE		0
#define		OPENING_MODE	1
#define		LOGIN_MODE		2
extern int	 MouseDblClick;

extern int InitOpening();
extern int MainOpening();
extern int DrawOpening();
extern int CloseOpening();


//extern int DrawChatMessage(int x, int y, char *message, int lineSize=0);
extern int DrawTwoLineMessage(int x, int y, char *messageOne, char *messageTwo, DWORD color1, DWORD color2, DIRECTDRAWSURFACE clanMark = NULL, BOOL selected = FALSE, int bellaMarkIndex = -1);
extern int DrawCharacterMessage(int x, int y, char *message, int lineSize = 30, DIRECTDRAWSURFACE clanMark = NULL, char *clanName = NULL, DWORD color1 = RGB(0,0,0), BOOL selected = FALSE, int bellaMarkIndex = -1);
extern int DrawClanMessage(int x, int y, char *message, int lineSize = 20, DWORD color = RGB(255, 255, 255) );

extern int DrawCharacterShopSellMessage(int x, int y, char*message, int lineSize = 30, DIRECTDRAWSURFACE clanMark = NULL, DWORD charColor = RGB(0,0,0), BOOL selected = FALSE);
extern int DrawCharacterShopByeMessage(int x, int y, char*message, int lineSize = 30, DIRECTDRAWSURFACE clanMark = NULL, DWORD charColor = RGB(0,0,0), BOOL selected = FALSE);



extern int DrawMessage(int x, int y, char *message, int lineSize=0, int boxAttrib = BOX_ONE);
extern int InitMessageBox();
#define CAPTURE_BMP		100
#define CAPTURE_JPG		200

//Capture관련..
extern void Capture(HWND handle, int fileFormatFlag = CAPTURE_BMP);
extern void HoReLoad();

extern TRANS_USERCHAR_INFO		 *ServerUserCharacterInfo;
extern smTRANS_CHAR_COMMAND2	 *ServerReturn;
extern smTRANS_COMMAND			 *ServerLoginError;
extern TRANS_SERVER_LIST		 *DownServerListInfo;

extern int CharacterJob;
extern HoNewCharInfo	NewCharInfo;
extern int GameErrorValue;
extern int SetGameError(int num);

struct hoServerListInfo
{
	char	szServerName[32];
	char	szServerIp1[20];
	char	szServerIp2[20];
	char	szServerIp3[20];

	DWORD	dwServerPort1;
	DWORD	dwServerPort2;
	DWORD	dwServerPort3;
};

struct HoUserCharacterInfo
{
	char	Name[100];
	char	BodyName[256];
	char	FaceName[256];
	char    ClanName[256];
	bool    ClanFlag;
	DIRECTDRAWSURFACE ClanMark;
	int		Level;	//레벨
	int		Race;	//종족
	int		Job;	//직업
	int     StartField;
	
	int		PosX;
	int     PosZ;
};

#define MAX_DOWN_SERVER_LIST_INFO	10
#define MAX_DOWN_USER_LIST_INFO		10

//Game에서 바로 선택할 Character
extern  HoUserCharacterInfo		DownUserCharacterInfo[MAX_DOWN_USER_LIST_INFO];	//유저의 정보..
extern  int						DownUserCharacterCount;

//서버 정보 관련.
extern hoServerListInfo	UserServerListInfo[MAX_DOWN_SERVER_LIST_INFO];
extern int				UserServerListInfoCount;



//인터페이스 관련..
extern HoParty		InterfaceParty;
extern		int		SetInterfaceParty(char *chrName, DWORD chrCode);
extern      int		MainInterfaceParty(int x, int y);
extern      int     DrawInterfaceParty(int x, int y);

extern		int		DrawInterfaceParty();
extern		int		MainInterfaceParty();
extern		int		CloseInterfaceParty();


extern BOOL GetCameraCoord(POINT3D &world);
extern BOOL HoStopCharMotion();


extern HoEffectHitBoard		EffectHitBoard;

int hoDrawTexImageFloat(int Mat, float putX, float putY, float putSizeX, float putSizeY, float getTexX, float getTexY, float getTexSizeX, float getTexSizeY, float texSizeX, float texSizeY, int alpha);
char *CpFindString( char *lpData , char *lpFindWord , char *lpSaveBuff , int buffSize );

struct hoCommandInfo
{
	//char Ip[64];
	char Id[64];
	char Pass[64];
};

//extern void				HoCommandLineDecoder();	// 해외 블럭
extern hoCommandInfo	HoCommandInfo;
extern BOOL				HoCommandLineFlag;

enum {COMMUNITY_TRIGLOW, COMMUNITY_HANGAME};
extern int				HoCommunity;

#define _EFFECT_RES_LOADING_
//extern bool OldSkyDrawFlag;

extern BOOL		HoEffectResLoadingFlag;
extern void		HoSetEffectResLoading(BOOL flag);
extern void		EffectWaveCamera(int factor, int delay = 0);

#endif