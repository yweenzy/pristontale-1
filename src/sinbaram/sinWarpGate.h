/*----------------------------------------------------------------------------*
*	파일명 :  sinWarpGate.h	
*	하는일 :  신바람 워프게이트
*	작성일 :  최종업데이트 2003년 6월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	


/*----------------------------------------------------------------------------*
*						신바람 워프게이트 struct
*-----------------------------------------------------------------------------*/	
struct sSINWARPGATE{
	POINT GatePosi[10];	//일단은 10군대정도를 움직일수있게 잡는다
	int ShowFlag;		//맵을 보여준다
	int GateSelect;		//이동할곳의 위치를 인덱스화해서 선택한다
	int MoveFieldNum;	//이동할곳의 인덱스 
	int SameAreaFlag;   //같은 지역인지 체크한다

	int GateUseIndex;	//윙에따른 활성화 
	POINT MapPosi;		//맵이 표시되는 위치
	DWORD EffectTime;	//이펙트 시간을 카운트한다
	int   EffectFlag;	//이펙트를 표시할수있나를 확인한다

	POINT CancelPosi;	//닫기버튼 
	int   CancelFlag;   //닫기 플렉

};

/*----------------------------------------------------------------------------*
*						신바람 워프게이트 class
*-----------------------------------------------------------------------------*/	
class cSINWARPGATE{

public:

	int MatWarpMap;
	int MatIcon;
	int MatSelect;

	DIRECTDRAWSURFACE lpCancelBox;
	DIRECTDRAWSURFACE lpCancelButton;
	DIRECTDRAWSURFACE lpCancelButton_G;

//	DIRECTDRAWSURFACE	lpHelpTitle;

public:

	cSINWARPGATE();
	~cSINWARPGATE();

	void Init(); //클래스 초기화
	void Load();
	void Release();
	void Draw();	
	void DrawText();
	void Close();//클래스 종료 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); 

	////////////워프게이트 관련함수
	
	//사용할수있는 워프게이트를 찾는다
	int SerchUseWarpGate();

	//워프게이트 이펙트
	int SetWarGateSelectEffect(int x , int y);

};

/*----------------------------------------------------------------------------*
*							extern
*-----------------------------------------------------------------------------*/	
extern cSINWARPGATE cSinWarpGate;
extern sSINWARPGATE sSinWarpGate;
extern int WarpGateUseCost[10];
extern int sinWarpGateCODE[10];
extern int FieldLimitLevel_Table[];

extern sSINWARPGATE sHaWarpGate;
extern int haWarpGateCODE[10];

