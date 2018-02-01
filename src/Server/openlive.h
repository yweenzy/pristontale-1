
typedef struct _gamedate {
	char	UserID[30];		// 사용자 ID
	char	GPCode[16];		// GP코드 
	char	DisuseDay[30];		// 종료날짜
	char    UsePeriod[30];		// 남은시간
	char	Guid[50];		// GUID
	char	PCRno[14];		// PCRNo
} gamedate;

typedef struct _PACKET {
  int size;
  int code;
  int OpenLiveCode;
  _gamedate jungdata;
} PACKET;

//Code 코드는 0x38000000
//OpenLiveCode 1  : 정량사용자 정액으로 변환

//* 리턴 값
typedef struct _RPACKET {
  int size;
  int code;
  char UserID[30];		// 사용자 ID
} RPACKET;

//Code : 0 실패 , 1 성공
//UserID : 처리한 사용자 ID


int	RecvOpenLivePacket( smWINSOCK *lpsmSock , void *Packet );



