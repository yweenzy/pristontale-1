/*----------------------------------------------------------------------------*
*	파일명 :  sinParkPcBangPet.h
*	하는일 :  PCBang 펫을 맹근다 
*	작성일 :  최종업데이트 3월 
*	적성자 :  박상열 // 박철호 수정
*-----------------------------------------------------------------------------*/	
#ifndef _SINPCBANGPET_HEADER_

#define _SINPCBANGPET_HEADER_

#include <string>
#include <map>
#include <vector>

//pet message list
typedef vector<string*> PetMessage;
typedef map< string , PetMessage> PetmsgMap;
typedef vector<int> MessageList;
typedef list<string> MessageKeep;
typedef list<int> MessageIndex;

/*----------------------------------------------------------------------------*
*							cHELPPET 	class		
*-----------------------------------------------------------------------------*/	
class cPCBANGPET{

public:
	PetmsgMap	PetMsg_Map;
	MessageList BattleM_List;
	MessageKeep Message_Keep;
	MessageIndex BattleMsg_Index;
	MessageIndex NormalMsg_Index;

	///////////// 모델 
	smPAT3D		*PatPetMesh_Bone; //Pet모델 Bone
	smPAT3D		*PatPetMesh; //Pet모델

	///////////// 좌표 , Angle 
	POINT3D		PetPosi;	   //Pet좌표
	POINT3D		PetAngle;	   //Pet앵글
	POINT3D     PetRendPoint;  //화면 Point좌표
	RECT		PetRendRect2D; //화면 Rect;	

	POINT3D		CameraPetAngle;	//카메라 Anlge
	POINT3D     CameraPetPosi;  //카메라 Posi

	///////////// 애니메이션
	int		AniCount;
	int		AniMaxCount;
	int     AniTime;

	//////////// 컬러
	sASSACOLOR Color;

	//////////// 메시지관련
	char szPetBuff[256];
	int MsgFlag;  //메세지 flag이 있을경우 호출하지않는다
	int MsgTime;  //시간을 나타낸다
	int MessageIndex; //0 메세지ID 1 메세지 인덱스
	char szTempId[32];

	int HelpMsgFlag;  //메세지 flag이 있을경우 호출하지않는다
	int HelpMsgTime;  //시간을 나타낸다
	char HelpMsgId[32];

	/////////// Pet종류
	int PetKind; //1 화룡(테리) 2 수룡(넵시스) 3풍룡(이오) 4지룡(무트)
	int PetShow;

	/////////// 전투 메세지관련 경험치
	int PetExp;
	int LevelFlag;

	/////////// 로딩 관련
	int LoadingPet;
	
public:
	cPCBANGPET(){};
	~cPCBANGPET(){};

	void Init(); //클래스 초기화
	void Load();
	void Release();
	void Draw();
	void Draw(POINT3D *pPosi , POINT3D *pAngle);
	void DrawText();
	void Close();//클래스 종료 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); //키 체크 

	//메세지 파싱
	int GetFileData();

	//Pet메세지를 셋팅한다
	int PetMessage(char *Id , int Index);

	//Pet메세지 도움말을 보여준다 (상단)
	int PetMessageHelp(char *Id); //상단 도움말 메세지

	//Pet 2D좌표를 구한다
	int GetPetMessagePosi();

	//Pet 메세지를 그려준다
	int DrawPetMessage();

	//Pet 을 사용관련 체크한다
	int CheckPetData();

	//Random 메세지
	int PetRandomBattleMessage();
	int PetRandomNormalMessage();

	//Pet을 호출한다
	int ShowPet();
	int ClosePet();

	int PetOnOff(char *szBuff);

};

extern cPCBANGPET cPCBANGPet;
//extern int PetMessageOkButtonFlag;




//class cSINPET  cSINBARAM_UI


#endif
