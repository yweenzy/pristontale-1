/*===========================================================================================
============================================================================================*/
#ifndef __PACKETSTRUCT_H__
#define __PACKETSTRUCT_H__


#define STRING_MAX			(64+4)


//#define ID_MAX			64
#define CHANAME_MAX		64
#define CLANNAME_MAX    64
//#define CLANWON_MAX      90   //현재 최대 클랜원수는 90명
//#define CLANWONLIST      3    //패켓 길이 256넘으면 안됨



#define P_IDANDNAME				10001
#define P_OUT					10002
#define P_CLANINFO				10003


//프로세스간의 대화
#define INSIDE_IPPORT						20010 //게임에서 아이피,포트를 받음
#define INSIDE_USERINFO						20001
#define INSIDE_USERINFOCHG					20030 //클랜이없어지거나 바뀐경우 db를 바꾸기위함.
#define INSIDE_GAME_OUT						20003
#define INSIDE_CLANCHAT                     20011 //클랜 채팅메세지
#define INSIDE_VD		                    20012
#define GOPRIS_VUSERIDs         200030		//보이스말한사람의 id들
#define GOPRIS_VCLIENTINFO      200031		//보이스클라이언트 정보(보이스서버없다.접속안됨,접속끊어짐,접속유지중 등..)
//priston->보이스클라이언트로..
#define INSIDE_MICONOFF         200050		//프테에서 마이크 온오프해준다.


#define INSIDE_GAMELOGIN					20000
#define INSIDE_GETWND                       20004
#define INSIDE_CLAWONLIST                   20005

#define INSIDE_DELCLANWON                20013 //클랜원 삭제
#define INSIDE_DELCLAN                   20014 //클랜   삭제
#define INSIDE_MAKECLAN					 20015 //클랜   만들기


//클라->서버로 보내는 메시지
#define INSIDE_CLIENTINFO			250000   //런처의 정보(섭에서 접속가능여부를 알수있다)



//서버가 보낸 메세지
#define SERVER_CLANWONLS			30000
#define SERVER_CLANCHAT				30001
#define SERVER_CLWIN				30002
#define SERVER_CLWOUT				30003
#define SERVER_SENDVOC				30004






typedef struct _tagIndex
{
	DWORD		dwIndex;
}INDEX,*LPINDEX;


//ktj : OK
//게임에서 보내주는 아이피와 포트
//INSIDE_IPPORT						
typedef struct __tagIpPort
{
	INDEX           sIndex;
	char            ip[16];
	int				port;
	//HWND Chwnd;

}IPPORT,*LPIPPORT;

//INSIDE_USERINFO
//INSIDE_USERINFOCHG
typedef struct _tagUserInfo
{
	INDEX   sIndex;

	DWORD	dwClanNum;					//클랜번호
	char	szClanName[STRING_MAX];		//클랜이름

	int     utype;						//클랜상의 유저attr 
	char	szCharName[STRING_MAX];		//유저의 캐릭터 이름.
	char	szID      [STRING_MAX];		//유저 아디
	char	szConnServerName[16];		//접속한 서버이름이 들어있는 버퍼
}USERINFO;


//INSIDE_GAME_OUT
typedef struct __tagPacketOut
{
	INDEX			sIndex;			//기타데이타는 필요없다.
}P_Out;


//INSIDE_CLANCHAT 클랜 채팅 스트럭처
typedef struct __tagClanChat
{
	INDEX		sIndex;
	char		szMsg[256];
}CLANCHAT;


//INSIDE_VD    ktj : voice는 데이타크기가 유동적이라서 이렇게 한다.
typedef struct
{
	INDEX	sIndex;
	int		vSize;
	char	vData[4];
}VOICEDATA;


//프리스턴으로 sendMessage사용해가는데이타 ======================= 
//GOPRIS_VUSERIDs    //말하는유저의 데이타
#define STREAMDATACNT 8 //주의 : packetstruct.h와 같아야함.
typedef struct
{
	INDEX	sIndex;
	DWORD	time;			//2초정도의 타이머첵크용으로 데이타를 지우기위한용도임.
	char	uID[STREAMDATACNT][32];		//현재8명
}VOICTALKUSERDATA;
//VOICTALKUSERDATA vUserData;

//INSIDE_MICONOFF
typedef struct
{
	INDEX	sIndex;
	BOOL	bMicONOFF;
}VOICEONOFF;





//아래 스트럭처와 연계
enum {
	VC_STATE_NOSERVER,		//보이스서버가 없다.
	VC_STATE_NOTCONNECT,	//보이스서버에 접속할수 없다.
	VC_STATE_CONNECT,		//보이스서버와 connect
	VC_STATE_DISCONNECT,	//보이스서버와 disconnect
};
#define VC_STATE_NOSERVER_STR	"보이스서버가 없다."
#define VC_STATE_NOTCONNECT_STR	"보이스서버에 접속할수 없다."
#define VC_STATE_CONNECT_STR	"보이스서버와 connect"
#define VC_STATE_DISCONNECT_STR	"보이스서버와 disconnect"
//GOPRIS_VCLIENTINFO
typedef struct
{
	INDEX	sIndex;
	int		vcl_state;
}VCLIENTINFO;










/*================================================================
서버에서 보낸데이타
=================================================================*/
typedef struct {
	int     utype;						//클랜상의 유저attr 
	char	szCharName[STRING_MAX];		//유저의 캐릭터 이름.
	char	szID      [STRING_MAX];		//유저 아디
}SERVER_clanWon;
//SERVER_CLANWONLS
typedef struct __tagServer_ClanWonList
{
	INDEX               sIndex;
	int					clanwonSu;
	SERVER_clanWon		sclanwon[1];
}SERVER_CLANWONLIST;


//SERVER_CLANCHAT
typedef struct __tagServer_ClanChat
{
	INDEX               sIndex;
	SERVER_clanWon      clanwon;
	char				chat[256];
}SERVER_CLANCHATSTR;


//SERVER_CLWIN  SERVER_CLWOUT
typedef struct __tagServer_outClanWon
{
	INDEX               sIndex;
	SERVER_clanWon      clanwon;
}SERVER_inoutCLANWON;

//SERVER_SENDVOC    ktj : voice는 데이타크기가 유동적이라서 이렇게 한다.
typedef struct
{
	INDEX				sIndex;
	SERVER_clanWon		clanwon;
	int					vSize;
	char				vData[4];
}SERVER_VOICEDATA;

















/*
//===============================================================
//게임 로그인 할때
//================================================================

typedef struct _tagGameLogin
{
	INDEX     index;
	char      szID[CHANAME_MAX+1];
}GAMELOGIN,*LPGAMELOGIN;



//=====================================================
// User가 처음 접속할때
// User의 아이디와 캐릭터 이름을 세팅
//=====================================================
typedef struct _tagIDandChaName
{
	char szID[ID_MAX+1];
	char szChaName[CHANAME_MAX+1];
}IDandCHANAME,LPIDandCHANAME;

typedef struct _tagPacketIDandChaName
{
	INDEX			sIndex;
	IDandCHANAME	sIDandChaName;

}P_IDandCHANANE;



//=====================================================
// User의 클랜 정보를 세팅할때
// 클랜의 번호화 클랜 이름을 세팅
//=====================================================
typedef struct _tagClanInfo
{
	DWORD    dwClanNum;
	char     szClanName[CLANNAME_MAX+1];
}USER_CLANINFO;

typedef struct __tagClanInfo
{
	INDEX			     sIndex;
	USER_CLANINFO        ClanInfo;

}Packet_CLANINFO;







//====================================================================wav
//ktj : 일부 수정
//#define WAV_SIZE  512 //256  //150
//#define WAV_SIZE  10000  //150
//#define WAV_SIZE  1024 //256  //150
#define WAV_SIZE  4096//2048 //256  //150

//ktj : 웨이브 헤더부분의 사이즈를 첵크하기 위해 넣어둔것임.
typedef struct
{
	INDEX  sIndex;
	WORD  flag;						//마지막 데이타인경우 1임
	WORD  cnt;
	int  wavDataSize;
	char szChaName[CHANAME_MAX+1];
}WAVDATAHEADERchk;


typedef struct __tagWavData
{
	INDEX  sIndex;
	WORD  flag;						//마지막 데이타인경우 1임
	WORD  cnt;
	int  wavDataSize;
	char szChaName[CHANAME_MAX+1];
	char WavData[WAV_SIZE+1];
}WAVDATA,*LPWAVDATA;
//==============================================================//






typedef struct __tagWavChaName
{
	INDEX		sIndex;	
	char		szChaName[CHANAME_MAX+1];
}WAVCHANAME,*LPWAVCHANAME;

//클랜에서 클랜원을 삭제
typedef struct __tagDeleteClanWon
{
	INDEX		sIndex;	
	char		szChaName[CHANAME_MAX+1];
	char		szClanName[CLANNAME_MAX+1];
	DWORD       dwClanNum;
}DELETECLANWON,*LPDELETECLANWON;

//클랜을 삭제
typedef struct __tagDeleteClan
{
	INDEX		sIndex;	
	char		szClanName[CLANNAME_MAX+1];
	DWORD       dwClanNum;
}DELETECLAN,*LPDELETECLAN;


//클랜 만들기
typedef struct _TagMakeClan
{
	INDEX     index;
	DWORD     dwClanNum;
	char      szClanName[CLANNAME_MAX+1];
	char      szChaName[CHANAME_MAX+1];
	char      szID[CHANAME_MAX+1];
}MAKECLAN,*LPMAKECLAN;
*/



#endif //
