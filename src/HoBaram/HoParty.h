#ifndef _HO_PARTY_H_
#define _HO_PARTY_H_

#define MAX_PARTY_MEMBER	6

struct hoPartyMember
{
	char	Name[256];
	DWORD	ChrCode;
	int		Life;
	int		Level;
	
	POINT3D CharacterPos;	//캐릭터의 위치.
	BOOL	JangFlag;		//방장인지..

	char	ModelName1[64];
	char	ModelName2[64];
};

#define PARTY_NONE		500
#define PARTY_START		1000
#define PARTY_PROCESS	2000
#define PARTY_END		3000

class HoParty
{
public:
	HoParty();
	~HoParty();




	

	//========================= 퀘스트 메뉴 관련 데이타 셋팅 ============================= start
	void quest_Progress_Clear();
	void quest_End_Clear();
	void quest_Progress_Set(char *q_name, char *f_name);
	void quest_End_Set(char *q_name, char *f_name);
	void qN_Pressf_CLEAR();
	void quest_Sel_Progress();	//퀘스트진행버튼누른걸로 셋팅함.
	//========================= 퀘스트 메뉴 관련 데이타 셋팅 ============================= end
	//========================= 동료->친구 메뉴 관련 데이타 셋팅 ============================= start
	void latest_Insert(char *namest);	//최근목록==귓속말한사람의 리스트 추가.
	void friend_Insert(char *id);		//친구목록
	void chat_isLOG(char *id, int flag);	//id의 접속여부를 알려줌.
	int  chat_IDs(int dataN, int cnt, char *id); //id를 가져간다.(접속여부를 알려주기 위함임)
	
	
	void Main_menuSet(int menuN);	//메인메뉴 퀘스트, 동료, 친구를 바꿈.
	void chat_changeMENU(int sw);	//친구중 최근목록(0), 친구목록(1), 거부자목록을바꿈.
	int chatbuild_INIfiles();	//동료->친구
	
	void chat_WhisperPartyPlayer_close();	//귓말하고 엔터치면 부를것.

	//========================= 동료->친구 메뉴 관련 데이타 셋팅 ============================= end

	




	void InitMenuSet(int menuN);	//퀘스트, 동료메뉴가 같이붙어있어서넣음(퀘스트0, 메뉴, 동료 1)


public:
	hoPartyMember	PartyMember[MAX_PARTY_MEMBER];	//파티맴버 정보 구조체..
	int				PartyMemberCount;				//현재 인원수...

	int									PartyPosState;
	int									MouseDownPartyMember;

private:
	

	int									MouseDownButton;
	
	
	//PartyInterface 리소스..
	int									MatPartyBackGround;
	DIRECTDRAWSURFACE				BmpMan[3];

	DIRECTDRAWSURFACE				BmpLifeBlue;
	DIRECTDRAWSURFACE				BmpLifeRed;

	DIRECTDRAWSURFACE				ToolTip[5];
	DIRECTDRAWSURFACE				Button[5];

	POINT								BackStartPos;
	POINT								TextStartPos;
	
	//PartyMessageBox 리소스..
	int									MatMessageBoxBackGround;
	POINT								MessageBoxStartPos;
	
	char								PartyMessageBoxChrName[128];
	DWORD								PartyMessageBoxChrCode;

	DIRECTDRAWSURFACE				BmpMessageOk[2];
	DIRECTDRAWSURFACE				BmpMessageCancel[2];

	int				MessageBoxDrawCount;
public:
	BOOL			MessageBoxOpenFlag;			//Message창 오픈 플래그이다.
	
	void Init();
	void Load();
	void Close();

	int	 Draw();
	int	 Main();
	
	int	AddMember(char *member,DWORD chrCode, int life, int level=1);

	//ktj : 새로 만듦.
	int	 AddMember(hoPartyMember *member,int cnt);
	void AddMember_memberSu(int memberSu);
	int  PARTY_PLAYUPDATE(hoPartyMember *member,int cnt);
	void PARTY_RELEASE();


	

	int SetParty(char *chrName, DWORD chrCode)
	{
		memset(PartyMessageBoxChrName, 0, sizeof(PartyMessageBoxChrName));
		wsprintf(PartyMessageBoxChrName, "%s", chrName);
		
		PartyMessageBoxChrCode = chrCode;
		MessageBoxOpenFlag = TRUE;
		
		return TRUE;
	}

	void DrawPartyMessage(int x, int y);
	void MainPartyMessage(int x, int y);
};


class HoEffectHitBoard
{
public:
	HoEffectHitBoard();
	~HoEffectHitBoard();

	float   BackPutSizeX;
	float   BackPutSizeY;
	float   BackPutAlpha;
	

	float  TextPutSizeX;
	float  TextPutSizeY;
	float  TextPutAlpha;

	float	CriticalPutSizeX;
	float	CriticalPutSizeY;
	float	CriticalPutAlpha;

	int MatHitBackBoard;
	int MatHitCount;
	
	BOOL CriticalFlag;
	char BufferNum[256];
	void Load();

	int Draw();
	int Main();

	int Start(char *num, BOOL criticalFlag = FALSE);

private:
	int StartFlag;
};


















#endif
