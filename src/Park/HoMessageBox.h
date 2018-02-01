#ifndef _HoMessageBox_H_
#define _HoMessageBox_H_

#define	BUTTON_STATE_NONE	0
#define BUTTON_STATE_IN		1
#define BUTTON_STATE_DOWN	2


#define BOX_ONE				0
#define BOX_TWO				1
#define BOX_THREE			2
#include <string>
using namespace std;

int HoDrawTexImage(int Mat, float x, float y, float w, float h, float texX, float texY, float texW, float texH, int Transp);
int HoDrawTexImage(int Mat , int x, int y, int texX, int texY, int texW, int texH, int Transp);

//겉 테두리와 메시지를 출력하는 Class
class HoMessage
{
private:
	int						BoxImage1[9];
	int						BoxImage2[4];
	int						BoxImage3[10];
	int                     BoxImage4[10];
    
	int						ClanBoxImage[3];
	int                     ClanBoxImage2[9];

	int						ShopBoxSellImage1[10];
	int						ShopBoxSellImage2[10];

	int						ShopBoxByeImage1[10];
	int						ShopBoxByeImage2[10];

	int						BellaIconImage[3];
	

	//이 아래 변수들은 건들지 마시오
	int						Width;
	int						TextStartPosY;
	static BOOL				MessageFrameSelectFlag;   //메시지를 선택 했을 경우 Frame을 더 그리는지 아닌지..

public:
	HDC						TextDC;
	HFONT					OldFont;

public:
	int						PosX, PosY;
	char					DrawMessageBuffer[256];
	char					DrawCharacterNameBuffer[256];

	HoMessage();
	~HoMessage();
	int Init();
	
	//message1과 message2가 아래,위로 그려지는 메시지창
	void DrawTwoLineMessage(int x, int y, char *message1, char *message2, DWORD color1 = RGB(0,0,0), DWORD color2 = RGB(0,0,0), DIRECTDRAWSURFACE clanMark = NULL, BOOL selected = FALSE, int bellaMarkIndex = -1);
	
	//일반적인 채팅 메시지 창(message에 들어오는 사람이름에서 :로 사람이름 구별해서 사람이름을 color1값으로 찍고 나머지 문자는 디폴트 색으로 칠한다.)
	void DrawCharacterMessage(int x, int y, char *message, int lineSize = 30, DIRECTDRAWSURFACE clanMark = NULL, char *clanName = NULL, DWORD color1 = RGB(0,0,0), BOOL selected = FALSE, int bellaMarkIndex = -1);
	//일반적인 채팅 메시지를 출력할 때 껍데기를 찍는다.
	void DrawCharacterMessageFrame(int x, int y, int messageWidth, int messageHeight, bool tailFlag = false, BOOL selected = FALSE); 
	//채팅 메시지에서 클랜 메시지가 있는 경우 클랜 메시지를 찍는 함수
	void DrawClanMessage(int x, int y, char *message, int lineSize, DWORD color = RGB(255,255,255));
	//클랜 메시지 메시지창 이미지
	void DrawClanMessageFrame(int x, int y, int messageWidth, int messageHeight);
	//클랜 마크
	void DrawClanMark(DIRECTDRAWSURFACE clanMark, char *clanName, int x, int y, BOOL frameFlag = FALSE);
	//클랜 이름 
	void DrawClanName(int x, int y, char *clanName);
	//벨라 트라 마크 찍는 함수.
	void DrawBellaIcon(int x, int y, int bellaIndex = 1);
	

	//개인 상점 살때 메시지
	void DrawShopSellMessage(int x, int y, char *message, int lineSize = 30, DIRECTDRAWSURFACE clanMark = NULL,DWORD color1 = RGB(0,0,0), BOOL selected = FALSE);
	void DrawShopSellMessageFrame(int x, int y, int messageWidth, int messageHeight, bool tailFlag = false, BOOL selected = FALSE);
	
	//개임 상점 팔때 메시지
	void DrawShopByeMessage(int x, int y, char *message, int lineSize = 30, DIRECTDRAWSURFACE clanMark = NULL,DWORD color1 = RGB(0,0,0), BOOL selected = FALSE);
	void DrawShopByeMessageFrame(int x, int y, int messageWidth,  int messageHeight, bool tailFlag = false, BOOL selected = FALSE);
	
	
	

	//이 아래 함수들은 건들지 마세요
	int GetWidth()			{return Width;}
	static void SetMessageFrameSelect(BOOL flag = TRUE)
	{
		MessageFrameSelectFlag = flag;
	}
	void Draw(int x, int y, char *message, int lineSize = 0, int addLine = 0, int boxAttrib = BOX_ONE);
	void DrawMessageBox(int x, int y, char *message, int boxAttrib = BOX_ONE, int Color = RGB(255, 255, 255));

	//해외 함수선언부분
	char	textdata[12][64];
	POINT	textsize;
	int textarrange(char *teststr,bool clanm);
	void DrawCharacterMessageFrame1(int x, int y, int messageWidth, int messageHeight,int linecount, bool tailFlag, BOOL selected);
	void DrawShopSellMessageFrame1(int x, int y, int messageWidth, int messageHeight,int linecount, bool tailFlag,  BOOL selected);
	void DrawShopByeMessageFrame1(int x, int y, int messageWidth, int messageHeight,int linecount, bool tailFlag, BOOL selected);
};








//버튼 한개를 출력하는 Class
//3버튼 (이미지 두개) 마우스가 버튼위에 있을 경우 블렌딩하고 누르면 버튼을 아래로 조금 움직인다.
class HoButton
{
private:
	int				StateFirstImage;
	int				StateThirdImage;
	
	BOOL			ButtonInDownFlag;			//Button 안에서 MouseDown 인지..
	
	static	BOOL	ButtonUseFlag;

	int				State;						//Button의 상태...
	int				PosX;
	int				PosY;

public:
	BOOL Main(int mouseX, int mouseY,int downFlag = 0);
	BOOL Draw(int x, int y, int BlendFlag = 255);
	void Init(char *stateFirstImage, char *stateThirdImage = NULL);
	void Init(char *stateFirstImage, int sizeWidth, int sizeHeight);
	
	void InitCrashRect(int left, int top, int right, int bottom);
	
	int				SizeWidth;
	int				SizeHeight;

	RECT			CrashRect;		//그림의 충돌 영역 검사 (상대 좌표이다)

	HoButton();
	~HoButton();

};

class HoMessageBox
{
private:
	HoMessage	Message;		//Message출력..
	HoButton	Button[2];		//Button을 출력...
	
public:
	BOOL		Flag;
	HoMessageBox();
	~HoMessageBox();

	BOOL	Main(int mouseX, int mouseY, int downFlag = 0);
	BOOL	Draw(int x, int y, char *message, int Color = RGB(255, 255, 255));
	void	Init();

};

extern HoMessage	ChatMessage;

BOOL	TextGetDC();
BOOL	TextReleaseDC();
BOOL	TextSelectObject(HFONT font);
BOOL    TextSetColor(COLORREF color);
BOOL	dsTextLineOut(int x, int y, char *lpszString, int nCount);


BOOL	EngSetFont(int fontSize);
BOOL	EngSetTextColor(COLORREF color);
BOOL	EngdsTextLineOut(int x, int y, char *message, int nCount);

void    SetMessageFrameSelect(BOOL flag = TRUE);

//#define dsTextLineOut_ENGLISH
#endif