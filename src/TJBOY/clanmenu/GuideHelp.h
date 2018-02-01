
//---------------------------------------------------------------------------
// GuideHelp.h : 캐릭터가 레벨업이 되었을때 해당레벨에 맞는 가이드를 자동
//                 으로 보여주는 오토가이드의 선언 부분이다.
//
// latest modify : 2004. 03. 04 by teze(Tae-Jin Kim.)
// Original Developer : Gwang-Yul Yoo
//
//
// (주)프리스톤 소스코드 제한 사항
//
// 이 소스 코드는 (주)트라이글로우픽쳐스 내부에서만 사용이 유효합니다. 
// (주)트라이글로우픽쳐스 외에서 사용할 경우 그에 합당한 법적 조치가
// 취해질수 있습니다. 
//
// 프리스톤 테일에 관한 모든 권리는 (주)프리스톤 에 있습니다.
//
//
//      Copyright (c) 2003 PRISTON.
//      All Rights Reserved.
//
// (주)PRISTON Seoul South. Korea
// http://kr.pristontale.com
//
// teze에 의해 작성된 주석은 명확한 확인을 거친 것은 아니다. 그리고 나름대로
// 개선해야할 방안에 대해 조금씩 적어 두었다. teze가 작성한 주선은 by teze라
// 는 키워드를 달아 두었다. 언제든 삭제해도 된다.
//---------------------------------------------------------------------------

#pragma once

#ifndef __GUIDEHELP_H__
#define __GUIDEHELP_H__

#include "clan_Enti.h"

#define NOTICE_X	208
#define NOTICE_Y	61


#define GUIDEHELP_LIST		0
#define GUIDEHELP_CONTENT    1


#define HELP_CONTENT	"./image/clanImage/Help/AutoHelp/LevelUp_Content.ini"
#define HELPCONTENT_WIDTH 100
#define HELPCONTENT_HEIGHT 100
#define HEIGHT_MAX 14

//#define LEVELHELP_MAX   25
#define LEVELHELP_MAX   28 //by teze

#define LEVELHELP_WIDTH	100
#define LEVELHELP_COUNT_MAX 10

#define GUIDEHLEP_CONTENT_HEIGHT_MAX  13

class CGuideHelp: public CLANEntity
{
public:
	CGuideHelp();
	~CGuideHelp();
public:
	int Init(int Life);
	int Clear();

	void Main();
	void Draw();
	void Load();
	void menuInit(int num);
	void SetHelpN(int num);
	int GetHelpN(){return m_GuideHelpN;}
	void SetStartPos(int x, int y);
	void InitLevelHelpLabel();

	void CheckLevel(int level);
	void GetHelpContent(char* section,char* key,char* ImageKey);
	void Parsing(char* str);
	void CheckLevel(int level,int type);
	void Draw_Help_Text(char *str, int x, int y, int sw=0);
	void Draw_Help_Text2(char *str, int x, int y, int sw=0);
	void SetDoing(BOOL bFlag){bDoing=bFlag;}
	BOOL GetIsOn(){return bIsOn;}
	void Draw_Title_Text(char *str, int x, int y, int sw=0);
	void ClearImage();
	void LoadGuideImage(char* file);
	int dsDrawTexImageFloat( int Mat , float x, float y, float w, float h , int Transp , int specular=0 );
	void GuidHelpEnd();
	
	
private:
	POINT	m_Start;
	int		m_GuideHelpN;
	BOOL		m_bDraw;	

	BOOL m_bIsMouseOver; //마우스가 해당 이미지 위에 올라 왔는지 체크	
	BOOL bIsOn;

	char	m_HelpContent[HELPCONTENT_HEIGHT][HELPCONTENT_WIDTH];  //헬프 내용
	int nHeight_Count;

	RECT scrIconPos;		//스크롤바의 움직이는아이콘위치설정
	int nScl_Bar;

	int nQuetion_Icon,nQuetion_Icon1;
	int nHelp,nHelpSee,nQuideHelp,nDuru,nDuru1;
	int nLine,nScl_Bar_tj,nScl_icon_tj;
	int nGuideList;

	DIRECTDRAWSURFACE hOn;
	DIRECTDRAWSURFACE hOff;

	char LevelHelp[LEVELHELP_MAX][LEVELHELP_WIDTH];
	int nLevelHelpCount;

	BOOL bHelpIcon[50];
	BOOL bDoing;

	int nHelpCountNamugi;

	smMATERIAL_GROUP*  GuideImage;
	int			   nGuideImageNum;
	int				nSaveNamugi;
	
	
};

#endif //__GUIDEHELP_H__


// Extern 선언을 위한 전처리부분
#ifdef GUIDEHELP_CPP
class CGuideHelp  g_GuideHelp;
#else
extern class CGuideHelp  g_GuideHelp;
#endif


