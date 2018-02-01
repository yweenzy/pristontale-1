#define LEVELUP_HELP_CPP
#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <stdio.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우

	#include "sinbaram\\SinLinkHeader.h"
	#include "HoBaram\\HoLinkHeader.h"
	#include "Language\\language.h"
	#include "HoBaram\\HoTextFile.h"
	#include "cE_CViewClanInfo.h"
#endif
#include "tjscroll.h"
#include "tjclan.h"
#include "clan_enti.h"
#include "cE_Notice.h"


#include "Help.h"
#include "GuideHelp.h"

//haGoon 가이드 도울 플래그
int  haGuidHelpLevel_1Flag=0;
CHelp cHelp_Menu;
extern int LevelpUpButton[3]; //레벨업 도움말

CHelp::CHelp()
{
	m_HelpN = -1;
	m_bDraw = TRUE;

	nHelp0=nHelp1 = 0;	
	m_ImageCount = 0;
	nBox1=nBox2=nBox3=nBox4=nBox5=nBox6=nBox7=nBox8=nBox9=0;
	
	ZeroMemory(m_HelpContent,sizeof(m_HelpContent));
	nHeight_Count = 0;
	Box_x = 5;
	Box_y = 5;
	nBoxWidth_Count=BOX_WIDTH_COUNT;
	nBoxHeight_Count=5;
	ZeroMemory(HelpMenu,sizeof(HelpMenu));
	top_right = 0;
	nGuideHelp = 0;
	GuideImage = new smMATERIAL_GROUP(1);
	nGuideImageNum = 0;
	for(int i=0; i<2; i++)
	{
		hClose[i] = NULL;
	}

	m_bTime = TRUE;
	m_bOnce = FALSE;
	m_dwTime = 0;
}

CHelp::~CHelp()
{
	Clear();
}

int CHelp::Init(int Life)
{
	life = Life;
	
	return 1;
}

int CHelp::Clear()
{
	for(int i =0; i< 2; i++)
	{
		if(hClose[i]) 
		{
			hClose[i]->Release();
			
			hClose[i] = NULL;
		}
	}
	return 1;
}

void CHelp::Load()
{
	nHelp0 = CreateTextureMaterial( "image\\Sinimage\\Help\\help_icon03.tga", 0, 0, 64,64, SMMAT_BLEND_ALPHA );
	nHelp1 = CreateTextureMaterial( "image\\Sinimage\\Help\\help_icon04.tga", 0, 0, 64,64, SMMAT_BLEND_ALPHA );

	nBox1  = CreateTextureMaterial( "image\\Sinimage\\Help\\GH-Box01.tga", 0, 0, 32,32, SMMAT_BLEND_ALPHA );
	nBox2  = CreateTextureMaterial( "image\\Sinimage\\Help\\GH-Box02.tga", 0, 0, 16,32, SMMAT_BLEND_ALPHA );
	nBox3  = CreateTextureMaterial( "image\\Sinimage\\Help\\GH-Box03.tga", 0, 0, 32,32, SMMAT_BLEND_ALPHA );
	nBox4  = CreateTextureMaterial( "image\\Sinimage\\Help\\GH-Box04.tga", 0, 0, 32,16, SMMAT_BLEND_ALPHA );
	nBox5  = CreateTextureMaterial( "image\\Sinimage\\Help\\GH-Box05.tga", 0, 0, 16,16, SMMAT_BLEND_ALPHA );
	nBox6  = CreateTextureMaterial( "image\\Sinimage\\Help\\GH-Box06.tga", 0, 0, 32,16, SMMAT_BLEND_ALPHA );
	nBox7  = CreateTextureMaterial( "image\\Sinimage\\Help\\GH-Box07.tga", 0, 0, 32,32, SMMAT_BLEND_ALPHA );
	nBox8  = CreateTextureMaterial( "image\\Sinimage\\Help\\GH-Box08.tga", 0, 0, 16,32, SMMAT_BLEND_ALPHA );
	nBox9  = CreateTextureMaterial( "image\\Sinimage\\Help\\GH-Box09.tga", 0, 0, 32,32, SMMAT_BLEND_ALPHA );

	hClose[0] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c.bmp");
	hClose[1] = LoadDibSurfaceOffscreen("image\\clanImage\\MessageBox\\c1.bmp");

	nGuideHelp = CreateTextureMaterial(  "image\\Sinimage\\Help\\help_icon02t.tga", 0, 0, 64,64, SMMAT_BLEND_ALPHA );
	
	
}
void CHelp::Main()
{
	int i;
    
	//if(life ==0) return;
	if(haGuidHelpLevel_1Flag){
		if(haGuidHelpLevel_1Flag==1)  //무기 
			GetHelpContent("Level_1_W","Key29","Guide25");
		else                          //방어구
			GetHelpContent("Level_1_D","Key30","Guide26");
		menuInit(1);
		m_HelpN = 1;
		haGuidHelpLevel_1Flag = 0;
	}
	switch(m_HelpN)
	{	
	
	case LEVELUP_HELP:
		if(!m_bOnce)
		{
			m_dwTime = dwPlayTime;
			m_bOnce = !m_bOnce;
		}
		if((dwPlayTime - m_dwTime) >= 700)
		{
			m_dwTime = dwPlayTime;
			m_bTime = !m_bTime;
		}
		
		i = chkeckMenuN();
		switch(i) {
		case 0:	
		case 1:
			isDrawClanMenu = 1;
			break;
		default:
			memset(menuMouseOver,-1,sizeof(int)*30);
			isDrawClanMenu = 0;
			break;
		}
		//if(MOUSE0())			
		if(LevelpUpButton[0])
		{	
			//MOUSE0()=0;
			LevelpUpButton[0] = 0;
			
			switch(i) 
			{
			case 1:
			case 0:
				isDrawClanMenu = 1;
				m_HelpN = LEVELUP_HELP_CONTENT;
				menuInit(m_HelpN);	
				break;
			default:
				isDrawClanMenu = 0;
				break;

			}
		}
		break;

	case LEVELUP_HELP_CONTENT:
		i = chkeckMenuN();
		switch(i) {		
		case 0:
			menuMouseOver[0] = 1;  //닫기
			break;
		case 5:
			isDrawClanMenu = 1;
			break;
		case 1:
			menuMouseOver[1] = 1;
			break;
		default:
			isDrawClanMenu = 0;
			memset(menuMouseOver,-1,sizeof(int)*30);			

			break;
		}
		if(LevelpUpButton[0])
		{	
			//MOUSE0()=0;
			LevelpUpButton[0] = 0;
			
			switch(i) 
			{
			case 1:				 //닫기
				m_HelpN = -1;	
				isDrawClanMenu = 0;
				break;
			case 5: //전체사이즈
				isDrawClanMenu = 1;
				break;
			case 0:
				m_HelpN = -1;	
				isDrawClanMenu = 0;
				void InitGuideContentHelp();
				InitGuideContentHelp();
				break;
			default:
				isDrawClanMenu = 0;
				break;

			}
		}
		break;
		
	
	}
}

void CHelp::SetStartPos(int x, int y)
{
	m_Start.x = x;
	m_Start.y = y;
}


void CHelp::Draw(BOOL bFlag)
{	
	int nCap = 0,i =0;
	if(bFlag)
	{
		switch(m_HelpN)
		{
		case LEVELUP_HELP:			
			//Draw_C_Text("testestest", HelpMenu[0].left, HelpMenu[0].top);
			break;
		}
	}
	else
	{		
		switch(m_HelpN)
		{
		case LEVELUP_HELP:
			
			//DrawSprite(HelpMenu[0].left,HelpMenu[0].top, hTxt_Release[0],  0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);	h


			if(m_bTime)
			{
				renderDevice.BeginScene();
				sinDrawTexImage( nHelp0 , (float)HelpMenu[0].left, (float)HelpMenu[0].top, 64, 64);
				renderDevice.EndScene();
			}
			else
			{
				renderDevice.BeginScene();
				sinDrawTexImage( nHelp1 , (float)HelpMenu[0].left, (float)HelpMenu[0].top, 64, 64);
				renderDevice.EndScene();
			}

			renderDevice.BeginScene();
			sinDrawTexImage( nGuideHelp, (float)HelpMenu[1].left, (float)HelpMenu[1].top, 64, 32);
			renderDevice.EndScene();
			break;
		
		case LEVELUP_HELP_CONTENT:
			DrawBox(Box_x,Box_x,BOX_WIDTH_COUNT,nHeight_Count);//nBoxHeight_Count);
			renderDevice.BeginScene();
			sinDrawTexImage( nHelp0 , (float)HelpMenu[2].left, (float)HelpMenu[2].top, 64, 64);
			if((sinChar->Level != 9) && (sinChar->Level != 39))
				dsDrawTexImageFloat( nGuideImageNum, (float)HelpMenu[4].left, (float)HelpMenu[4].top, 64, 64,255);

			renderDevice.EndScene();



			for(i=0; i < nHeight_Count; i++)
			{
				//6줄 까지만 출력
				if(m_bIsContentOver&&(i >=CONTENT_MAX-1))
				{
					 break;
				}
				
				Draw_Help_Text(m_HelpContent[i], HelpMenu[3].left, HelpMenu[3].top +nCap,2);
				
				nCap+=15;

			}

			//DrawSprite(HelpMenu[3].left,HelpMenu[3].top, hButton_Box,  0, 0, 48, 23, 1);		
			if(menuMouseOver[1]>0) DrawSprite(HelpMenu[1].left,HelpMenu[1].top, hClose[1],  0, 0, 32, 16, 1);
			else	DrawSprite(HelpMenu[1].left,HelpMenu[1].top, hClose[0],  0, 0, 32, 16, 1);

			if(m_bIsContentOver)
			{
				if(menuMouseOver[0] > 0)
				{
					Draw_Help_Text2(LookHelp, HelpMenu[0].left, HelpMenu[0].top);
				}
				else
				{
					Draw_Help_Text3(LookHelp, HelpMenu[0].left, HelpMenu[0].top);
				}
			}



			break;

		}
	}
}

void CHelp::menuInit(int num)
{	
	int nScrollPos = 0;
	switch(num)
	{

	case LEVELUP_HELP:		
		HelpMenuSu  = 2;
		HelpMenu[0].left = m_Start.x + 4+5;
		HelpMenu[0].top = m_Start.y + 7+5;
		HelpMenu[0].right = HelpMenu[0].left + 64;
		HelpMenu[0].bottom = HelpMenu[0].top + 64;

		HelpMenu[1].left = HelpMenu[0].right-24;
		HelpMenu[1].top = m_Start.y + 7+12;
		HelpMenu[1].right = HelpMenu[1].left + 64;
		HelpMenu[1].bottom = HelpMenu[1].top + 32;


		break;
	
	case LEVELUP_HELP_CONTENT:
		HelpMenuSu  = 6;					

		bottom_left=(Box_y+32)+(nHeight_Count*13+32);
		top_right  = (Box_x+32)+(16*BOX_WIDTH_COUNT+32+13);
		
		HelpMenu[2].left = 13 + Box_x+5;		//두루마기
		HelpMenu[2].top = 13 + Box_y+5;
		HelpMenu[2].right = HelpMenu[2].left + 64;
		HelpMenu[2].bottom = HelpMenu[2].top + 64;

		

		bottom_left=(Box_y+32)+(nHeight_Count*13);
		top_right  = (Box_x+32)+(16*BOX_WIDTH_COUNT);

		


		//텍스트 출력
		HelpMenu[3].left = HelpMenu[2].left + 50+2;
		HelpMenu[3].top = HelpMenu[2].top + 10;

		HelpMenu[4].left = top_right-28+37;
		HelpMenu[4].top =bottom_left+4 -54;

		HelpMenu[0].left = 13 + Box_x+5 +  50+2; //HelpMenu[3].left;
		HelpMenu[0].top = bottom_left+4;
		HelpMenu[0].right = HelpMenu[0].left + lstrlen(DETAIL_SEE)*12;
		HelpMenu[0].bottom = HelpMenu[0].top + 12;

		HelpMenu[1].left = top_right-32;//Box_y + 7+13;		//닫기
		HelpMenu[1].top = bottom_left+4;
		HelpMenu[1].right = HelpMenu[1].left+32;//32*2 + 16*nBoxWidth_Count+Box_x;
		HelpMenu[1].bottom = HelpMenu[1].top+16;//32*2 + 16*nBoxHeight_Count+Box_y;	

		HelpMenu[5].left = Box_x;		//전체 사이즈
		HelpMenu[5].top =  Box_y;
		HelpMenu[5].right = HelpMenu[5].left + top_right;
		HelpMenu[5].bottom = HelpMenu[5].top + bottom_left;
		





		/*
		bottom_left=(Box_y+32)+(nHeight_Count*13);
		top_right  = (Box_x+32)+(16*25);
		HelpMenu[3].left = Box_y + 13;//Box_x;		//박스
		HelpMenu[3].top = bottom_left;
		HelpMenu[3].right = HelpMenu[3].left+48;//32*2 + 16*nBoxWidth_Count+Box_x;
		HelpMenu[3].bottom = HelpMenu[3].top+23;//32*2 + 16*nBoxHeight_Count+Box_y;	

		*/
		break;
	}
}


void CHelp::DrawBox(int x,int y,int x_width,int y_height)
{
#define ALPHA   250

	if (renderDevice.IsDevice() == NULL)
		return;

	int nCnt;
	top_right=0;
	bottom_left=0;
	int ypos = y+32;
	int xpos = x+32;
	nStart_x = x;
	

	renderDevice.BeginScene();


	
	
	
	dsDrawTexImage(nBox1,x,y,32,32,ALPHA);		//top-left
	

	top_right = (x+32)+(16*x_width);
	
	dsDrawTexImage(nBox3,top_right,y,32,32,ALPHA);		//top-right

	
	
	for(nCnt = 0; nCnt < y_height; nCnt++)
	{
		
		dsDrawTexImage(nBox4,x,ypos,32,16,ALPHA);			//left_center
		
		dsDrawTexImage(nBox6,top_right,ypos,32,16,ALPHA);	//right-center	
		
		ypos+=13;
	}
	ypos = y+32;
	
	//뒷배경찍기	
	for(nCnt =0; nCnt < y_height; nCnt++)
	{
		for(int nCnt2 =0; nCnt2 < x_width; nCnt2++)
		{
			dsDrawTexImage(nBox5,xpos,ypos,16,16 ,ALPHA);
			xpos+=16;
		}
		xpos = x+32;
		ypos+=13;
	}
	//dsDrawTexImage(nBox5,x+32,y+32,(x_width*16),ypos-13    ,ALPHA);//((y_height +2)*16),ALPHA);

	
	bottom_left=(y+32)+(ypos-37);
	dsDrawTexImage(nBox7,x,bottom_left,32,32,ALPHA);		//bottom-left
	

	
	dsDrawTexImage(nBox9,top_right,bottom_left,32,32,ALPHA);	//bottom-right
	

	
	xpos = x+32;
	for(nCnt = 0; nCnt < x_width; nCnt++)
	{
		
		dsDrawTexImage(nBox2,xpos,y,16,32,ALPHA);	//top_center
		dsDrawTexImage(nBox8,xpos,bottom_left,16,32,ALPHA);	//bottom-center
		

		xpos+=16;
	}

	renderDevice.EndScene();
}
void CHelp::SetHelpN(int num)
{
	m_HelpN = num;
}

void CHelp::ClearImage()
{
	GuideImage->Close();
}

void CHelp::LoadGuideImage(char* file)
{
	ClearImage();
	GuideImage->Init(1);
	nGuideImageNum = GuideImage->CreateTextureMaterial(file,0, 0, 128,128, SMMAT_BLEND_ALPHA );
	GuideImage->ReadTextures();

}


void CHelp::GetHelpContent(char* section,char* key,char* ImageKey)
{
	DWORD dwSaveSize = 100;
	char  szSaveStr[100];
	char  szImageDir[100];
	DWORD dwReturn,dwFileSize=0,dwRead = 0;
	HANDLE hFile = NULL;
	char *HelpContent;

	ZeroMemory(m_HelpContent,sizeof(m_HelpContent));
	ZeroMemory(szImageDir,sizeof(szImageDir));

	dwReturn = GetPrivateProfileString(section,key,"Error",szSaveStr,1024,HELP_CONTENT);

	if(dwReturn == 0) return;
	dwReturn = GetPrivateProfileString(section,ImageKey,"Error",szImageDir,1024,HELP_CONTENT);
	if(dwReturn == 0) return;

	LoadGuideImage(szImageDir);

	hFile = CreateFile( szSaveStr, GENERIC_READ, FILE_SHARE_READ,
                        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL , NULL );

	if(hFile == INVALID_HANDLE_VALUE) return ;

	dwFileSize = GetFileSize(hFile,NULL);

	HelpContent = new char[dwFileSize];
	ZeroMemory(HelpContent,sizeof(char)*dwFileSize);

	ReadFile(hFile,HelpContent,dwFileSize,&dwRead,NULL);
	CloseHandle(hFile);

	Parsing(HelpContent);

	delete[] HelpContent;	

}

void CHelp::Parsing(char* str)
{
	int nCnt,nCnt2,nCnt3;
	nCnt=nCnt2=nCnt3 = 0;
	nHeight_Count = 0;
	while(1)
	{
		if(str[nCnt3] == 0) break;
		
		if(str[nCnt3] == 0x0d)
		{
			nCnt3++;
			if(str[nCnt3] == 0) break;
			if(str[nCnt3] ==0x0a)
			{
				if(str[nCnt3+1] == 0x0d) break;
				else
				{
					nCnt3++;
					nCnt++;
					nCnt2 = 0;
				}
			}
			else
			{
				nCnt++;
				nCnt2 = 0;
				m_HelpContent[nCnt][nCnt2] = str[nCnt3];
			}
			
			continue;
		}
		else
		{
			m_HelpContent[nCnt][nCnt2] = str[nCnt3];
		}
		nCnt3++;
		nCnt2++;
	}

	nHeight_Count = nCnt+1;
	m_bIsContentOver= FALSE;

	if(nHeight_Count > CONTENT_MAX )
	{
		m_bIsContentOver = TRUE;
		nHeight_Count = 6;
	}
}

//레벨체크
BOOL CHelp::CheckLevel(int level,int type)
{
	BOOL IsLevel = FALSE;;
	switch(level)
	{
	case 1: //1~4  템스크론, 5~8 모라이언
		if(type <5)
		{
			//템스크론에서 캐릭터 처음 생성할때
			GetHelpContent("CreateCha_Temscron","Key0","Guide1");
		}
		else
		{
			//모라이언에서 캐릭터 처음 생성할때
			GetHelpContent("CreateCha_Moraion","Key1","Guide2");	
		}
		IsLevel = TRUE;
		break;
	case 2: //레벨2
		GetHelpContent("Level_2","Key2","Guide3");
		IsLevel = TRUE;		
		break;
	case 3:
		GetHelpContent("Level_3","Key3","Guide4");
		IsLevel = TRUE;
		break;
	case 4:
		GetHelpContent("Level_4","Key4","Guide5");
		IsLevel = TRUE;
		break;
	case 5:
		GetHelpContent("Level_5","Key5","Guide6");
		IsLevel = TRUE;
		break;
	case 6:
		GetHelpContent("Level_6","Key6","Guide7");
		IsLevel = TRUE;
		
		break;
	case 7:
		GetHelpContent("Level_7","Key24","Guide26");
		IsLevel = TRUE;
		break;
	case 8:
		GetHelpContent("Level_8","Key7","Guide8");
		IsLevel = TRUE;
		break;
	case 9:
		GetHelpContent("Level_9","Key25","Guide27");
		IsLevel = TRUE;
		break;
	case 10:
		
		if(type <5)
		{
			//템스크론
			GetHelpContent("Level_10_Temscron","Key8","Guide9");
		}
		else
		{
			//모라이언
			GetHelpContent("Level_10_Moraion","Key9","Guide10");
		}
		IsLevel = TRUE;
		break;
	
	//by HoDong
	case 11:
		GetHelpContent("Level_11","Key11","Guide11");
		IsLevel = TRUE;
		break;

	case 12:		
		GetHelpContent("Level_12","Key10","Guide11");
		IsLevel = TRUE;
		break;
	case 15:		
		GetHelpContent("Level_15","Key11","Guide12");
		IsLevel = TRUE;
		break;
	case 17:
		GetHelpContent("Level_17","Key12","Guide13");
		IsLevel = TRUE;
		break;
	case 20:
		
		if(type<5)
		{		
			GetHelpContent("Level_20_Temscron","Key13","Guide14");
		}
		else
		{
			GetHelpContent("Level_20_Moraion","Key24","Guide15");
		}
		IsLevel = TRUE;
		break;
	case 22:		
		GetHelpContent("Level_22","Key14","Guide16");
		IsLevel = TRUE;
		break;
	case 25:		
		GetHelpContent("Level_25","Key15","Guide17");
		IsLevel = TRUE;
		break;
	case 30:		
		GetHelpContent("Level_30","Key16","Guide18");
		IsLevel = TRUE;
		break;
	case 39:
		GetHelpContent("Level_39","Key26","Guide26");
		IsLevel = TRUE;
		break;
	case 40:		
		GetHelpContent("Level_40","Key17","Guide19");
		IsLevel = TRUE;
		break;
	case 50:		
		GetHelpContent("Level_50","Key18","Guide20");
		IsLevel = TRUE;
		break;
	case 55:
		GetHelpContent("Level_55","Key19","Guide21");
		IsLevel = TRUE;
		break;
	case 60:
		GetHelpContent("Level_60","Key20","Guide22");
		IsLevel = TRUE;
		break;
	case 65:		
		GetHelpContent("Level_65","Key21","Guide23");
		IsLevel = TRUE;
		break;
	case 70:		
		GetHelpContent("Level_70","Key22","Guide24");
		IsLevel = TRUE;
		break;
		//by teze
	case 75:
		GetHelpContent("Level_75","Key28","Guide24");
		IsLevel = TRUE;
		break;

	//by HoDong
	case 79:
		GetHelpContent("Level_79","Key79","Guide79");
		IsLevel = TRUE;
		break;


	case 80:		
		GetHelpContent("Level_80","Key23","Guide25");
		IsLevel = TRUE;
		break;
	}

	return IsLevel;
	
}

/*void CHelp::CheckLevel(int level,int type)
{	
	nBoxWidth_Count=24;
	nBoxHeight_Count=5;
	switch(level)
	{
	case 1: //1~4  템스크론, 5~8 모라이언
		if(type <5)
		{
			//템스크론에서 캐릭터 처음 생성할때
			GetHelpContent("CreateCha_Temscron","Key0",);
		}
		else
		{
			//모라이언에서 캐릭터 처음 생성할때
			GetHelpContent("CreateCha_Moraion","Key1");
		}
		break;
	case 2: //레벨2
		GetHelpContent("Level_2","Key2");
		nBoxHeight_Count+=2;
		break;
	case 3:
		GetHelpContent("Level_3","Key3");
		nBoxHeight_Count+=1;
		break;
	case 4:
		GetHelpContent("Level_4","Key4");
		break;
	case 5:
		GetHelpContent("Level_5","Key5");
		break;
	case 6:
		GetHelpContent("Level_6","Key6");
		nBoxHeight_Count+=3;
		break;
	case 8:
		GetHelpContent("Level_8","Key7");
		break;
	case 10:
		nBoxHeight_Count+=3;
		if(type <5)
		{
			//템스크론
			GetHelpContent("Level_10_Temscron","Key8");
		}
		else
		{
			//모라이언
			GetHelpContent("Level_10_Moraion","Key9");
		}
		break;
	case 12:
		nBoxHeight_Count+=1;
		GetHelpContent("Level_12","Key10");
		break;
	case 15:
		nBoxHeight_Count+=3;
		GetHelpContent("Level_15","Key11");
		break;
	case 17:
		GetHelpContent("Level_17","Key12");
		break;
	case 20:
		nBoxHeight_Count+=1;
		if(type<5)
		{		
			GetHelpContent("Level_20_Temscron","Key13");
		}
		else
		{
			GetHelpContent("Level_20_Moraion","Key24");
		}
		
		break;
	case 22:
		nBoxHeight_Count-=2;
		GetHelpContent("Level_22","Key14");
		break;
	case 25:
		nBoxHeight_Count+=2;
		GetHelpContent("Level_25","Key15");
		break;
	case 30:
		nBoxHeight_Count-=1;
		GetHelpContent("Level_30","Key16");
		break;
	case 40:
		nBoxHeight_Count-=1;
		GetHelpContent("Level_40","Key17");
		break;
	case 50:
		nBoxHeight_Count-=2;
		GetHelpContent("Level_50","Key18");
		break;
	case 55:
		GetHelpContent("Level_55","Key19");
		break;
	case 60:
		GetHelpContent("Level_60","Key20");
		break;
	case 65:
		nBoxHeight_Count-=1;
		GetHelpContent("Level_65","Key21");
		break;
	case 70:
		nBoxHeight_Count-=1;
		GetHelpContent("Level_70","Key22");
		break;
	case 80:
		nBoxHeight_Count+=2;
		GetHelpContent("Level_80","Key23");
		break;
	}
	
}
*/
void CHelp::Draw_Help_Text(char *str, int x, int y, int sw)
{
	char strbuf[1024];

	HDC hdc;
	HFONT oldFont;
	renderDevice.lpDDSBack->GetDC(&hdc);
	SetBkMode( hdc, TRANSPARENT );

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject( hdc , hFont );


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;

	while(1) 
	{
		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  
		{
			strbuf[i] =0;
			i=0;
jmp1:


			
			if(sw==2){
				SetTextColor( hdc, RGB(50, 50, 50));	//그림자용 글자색
				//SetTextColor( hdc, RGB(255, 255,255));	//그림자용 글자색
				dsTextLineOut(hdc, x+1, y+1, strbuf, lstrlen(strbuf));

				SetTextColor( hdc, RGB(255, 240, 200));	//일반글자색
				dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			else     {
				SetTextColor( hdc, RGB(255, 240, 200));	//일반글자색
				dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			
			/*
			if(sw==2){
				SetTextColor( hdc, RGB(255, 255, 255));	//클랜이름입력시 흰색				
			}
			else {
				SetTextColor( hdc, RGB(230, 255, 240));	//일반글자색
			}
			dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			*/
			

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	

	if(sw==1) 
	{
		static cnt=0;
		cnt++;
		if(cnt<20) {
			SetTextColor( hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, x + (lstrlen(str)*6) , y-16, "|", 1);
		}
		if(cnt>=40) cnt=0;
	}

	if(oldFont)
		SelectObject( hdc, oldFont);
	renderDevice.lpDDSBack->ReleaseDC(hdc);

}



/*///////////////////////////////////////////////////////////////////////////
: 클라스명 : 
: 하 는 일 : 마우스로 누른 메뉴 번호 첵크함수.
: 반 환 값 :
: 파라미터 :
///////////////////////////////////////////////////////////////////////////*/
int CHelp::chkMenu(int x, int y, RECT *r) 
{
	if(r->left <= x   &&   x<= r->right ) 
		if(r->top <= y   &&   y<= r->bottom ) 
			return 1;
	return 0;			//아무것도 선택안함.
}
int CHelp::chkeckMenuN()
{
	int i;
	
	for(i=0; i<HelpMenuSu; i++) {
		if(  chkMenu(pCursorPos.x, pCursorPos.y, &HelpMenu[i])  ) {
		//if(  chkMenu(400, 120, &HelpMenu[i])  ) {
			return i;
		}
	}
	return -1;
}

int CHelp::dsDrawTexImageFloat( int Mat , float x, float y, float w, float h , int Transp , int specular )
{
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;
	
	clipLeft = 0;
	clipTop = 0;
	clipRight = WinSizeX;
	clipBottom = WinSizeY;
	
	//Clipping 영역을 완전히 벗어나면...
	if ((x >= clipRight) || (y >= clipBottom) || ((x + w) <= clipLeft) || ((y+h) <= clipTop))
		return FALSE;
	
	//원래 사각 영역의 크기는 0, 0, 127, 127 이지만 이렇게 찍을 경우. 한 픽셀이 빠져서 0, 0, 128, 128로 보정한다.
	float x1 = x;
	float y1 = y;
	float x2 = (x+w);
	float y2 = (y+h);
	
	/*
	if(x1 < clipLeft)
		x1 = clipLeft;
	if(y1 < clipTop)
		y1 = clipTop;

	if(x2 >= clipRight)
		x2 = clipRight-1;

	if(y2 >= clipBottom)
		y2 = clipBottom-1;
	*/

	//x1, y1, x2, y2 는 클립된 사각영역이다..
	DRZD3DTLVERTEX tlVertex[4];
	int cnt;

	for(cnt=0;cnt<4;cnt++)
	{
		tlVertex[cnt].rhw = 1.f;
		tlVertex[cnt].color	= RGBA_MAKE( 255,255,255,Transp );
		tlVertex[cnt].specular  =  RGBA_MAKE( specular,specular,specular,0 );
		tlVertex[cnt].sz = 0;
	}
	/*
	tlVertex[0].sx = x1;
	tlVertex[0].sy = y1;
	tlVertex[0].tu = 1.0f*( (x1-(float)x)/w);
	tlVertex[0].tv = 1.0f*( (y1-(float)y)/h);
	
	tlVertex[1].sx = x1;
	tlVertex[1].sy = y2;
	tlVertex[1].tu = 1.0f*( (x1-(float)x)/w);
	tlVertex[1].tv = 1.0f*( (y2-(float)y)/h);
	
	tlVertex[2].sx = x2;
	tlVertex[2].sy = y1;
	tlVertex[2].tu = 1.0f*( (x2-(float)x)/w);
	tlVertex[2].tv = 1.0f*( (y1-(float)y)/h);
	
	tlVertex[3].sx = x2;
	tlVertex[3].sy = y2;
	tlVertex[3].tu = 1.0f*( (x2-(float)x)/w);
	tlVertex[3].tv = 1.0f*( (y2-(float)y)/h);
	*/
	
	//이게 진짜...
	/*
	tlVertex[0].sx = x1;
	tlVertex[0].sy = y1;
	tlVertex[0].tu = 1.0f*(float)( (x1-(float)x)/(float)w);
	tlVertex[0].tv = 1.0f*(float)( (y1-(float)y)/(float)h);
	
	tlVertex[1].sx = x1;
	tlVertex[1].sy = y2;
	tlVertex[1].tu = 1.0f*(float)( (x1-(float)x)/(float)w);
	tlVertex[1].tv = 1.0f*(float)( (y2-(float)y)/(float)h);
	
	tlVertex[2].sx = x2;
	tlVertex[2].sy = y1;
	tlVertex[2].tu = 1.0f*(float)( (x2-(float)x)/(float)w);
	tlVertex[2].tv = 1.0f*(float)( (y1-(float)y)/(float)h);
	
	tlVertex[3].sx = x2;
	tlVertex[3].sy = y2;
	tlVertex[3].tu = 1.0f*(float)( (x2-(float)x)/(float)w);
	tlVertex[3].tv = 1.0f*(float)( (y2-(float)y)/(float)h);
	*/

	
	tlVertex[0].sx = x1;
	tlVertex[0].sy = y1;
	tlVertex[0].tu = 0.0f;
	tlVertex[0].tv = 0.0f;
	
	tlVertex[1].sx = x1;
	tlVertex[1].sy = y2;
	tlVertex[1].tu = 0.0f;
	tlVertex[1].tv = 1.0f;
	
	tlVertex[2].sx = x2;
	tlVertex[2].sy = y1;
	tlVertex[2].tu = 1.0f;
	tlVertex[2].tv = 0.0f;
	
	tlVertex[3].sx = x2;
	tlVertex[3].sy = y2;
	tlVertex[3].tu = 1.0f;
	tlVertex[3].tv = 1.0f;
	
	/*
	tlVertex[0].sx = x;
	tlVertex[0].sy = y;
	tlVertex[0].tu = 0;
	tlVertex[0].tv = 0;

	tlVertex[1].sx = x;
	tlVertex[1].sy = y+h;
	tlVertex[1].tu = 0;
	tlVertex[1].tv = 1;

	tlVertex[2].sx = x+w;
	tlVertex[2].sy = y;
	tlVertex[2].tu = 1;
	tlVertex[2].tv = 0;

	tlVertex[3].sx = x+w;
	tlVertex[3].sy = y+h;
	tlVertex[3].tu = 1;
	tlVertex[3].tv = 1;
	*/

	//뒤집힌면 그리기
	//lpD3DDevice->SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_NONE );
	if (renderDevice.IsDevice() != NULL)
	{
		  // Turn on Z-buffering
		renderDevice.SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		//renderDevice.SetRenderState( D3DRENDERSTATE_ZFUNC,   D3DCMP_LESSEQUAL );
		//renderDevice.SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_USEW );//TRUE );


		// null out the texture handle
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);

		// turn on dithering
		//renderDevice.D3DDevice->SetRenderState( D3DRENDERSTATE_DITHERENABLE, TRUE );

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE ); 

		// D3DFILTER_LINEAR
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );
 
		renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

		renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

		smRender.AlphaTestDepth = 60;

		renderDevice.SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
		renderDevice.SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);

		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DTFN_POINT );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DTFN_POINT );
		

		if(GuideImage->smMaterial[Mat].smTexture[0] != NULL)
		{
			if(GuideImage->smMaterial[Mat].smTexture[0]->lpD3DTexture != NULL)
			{
				if (FAILED(renderDevice.SetTexture(0, GuideImage->smMaterial[Mat].smTexture[0]->lpD3DTexture)))
				{
					OutputDebugString("SetTexture Error");
					return FALSE;
				}

				
				if (FAILED(renderDevice.DrawPrimitive(D3DPT_TRIANGLESTRIP,
								D3DFVF_TLVERTEX  ,
								tlVertex,
								4,
								NULL)))
				{
					OutputDebugString("DrawPrimitive Error");
					return FALSE;
				}
			}
		}
		
		renderDevice.SetTextureStageState(cnt, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		renderDevice.SetTextureStageState(cnt, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
		//renderDevice.D3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
	}	
	//renderDevice.SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_CW );

	return TRUE;
}

void CHelp::HelpEnd()
{
	m_HelpN = -1;	
	isDrawClanMenu = 0;
}

void CHelp::Draw_Help_Text3(char *str, int x, int y, int sw)
{

	char strbuf[1024];

	HDC hdc;
	HFONT oldFont;
	renderDevice.lpDDSBack->GetDC(&hdc);
	SetBkMode( hdc, TRANSPARENT );

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject( hdc , hFont );
	//if(sinBoldFont!= NULL)
	//	oldFont = (HFONT)SelectObject( hdc , sinBoldFont );


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;

	while(1) {
		

		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:


			
			if(sw==2){
				SetTextColor( hdc, RGB(100, 100, 100));	//그림자용 글자색
				//SetTextColor( hdc, RGB(255, 255,255));	//그림자용 글자색
				dsTextLineOut(hdc, x+1, y+1, strbuf, lstrlen(strbuf));

				SetTextColor( hdc, RGB(255, 240, 200));	//일반글자색
				dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			else     {
				SetTextColor( hdc, RGB(255, 240, 200));	//일반글자색
				dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			
			/*
			if(sw==2){
				SetTextColor( hdc, RGB(255, 255, 255));	//클랜이름입력시 흰색				
			}
			else {
				SetTextColor( hdc, RGB(230, 255, 240));	//일반글자색
			}
			dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			*/
			

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	

	if(sw==1) 
	{
		static cnt=0;
		cnt++;
		if(cnt<20) {
			SetTextColor( hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, x + (lstrlen(str)*6) , y-16, "|", 1);
		}
		if(cnt>=40) cnt=0;
	}

	if(oldFont)
		SelectObject( hdc, oldFont);
	renderDevice.lpDDSBack->ReleaseDC(hdc);

}

void CHelp::Draw_Help_Text2(char *str, int x, int y, int sw)
{

	char strbuf[1024];

	HDC hdc;
	HFONT oldFont;
	renderDevice.lpDDSBack->GetDC(&hdc);
	SetBkMode( hdc, TRANSPARENT );

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject( hdc , hFont );
	//if(sinBoldFont!= NULL)
	//	oldFont = (HFONT)SelectObject( hdc , sinBoldFont );


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;

	while(1) {
		

		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:


			
			if(sw==2){
				SetTextColor( hdc, RGB(100, 100, 100));	//그림자용 글자색
				//SetTextColor( hdc, RGB(255, 255,255));	//그림자용 글자색
				dsTextLineOut(hdc, x+1, y+1, strbuf, lstrlen(strbuf));

				SetTextColor( hdc, RGB(255, 200, 100));	//일반글자색
				dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			else     {
				SetTextColor( hdc, RGB(255, 200, 100));	//일반글자색
				dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			
			/*
			if(sw==2){
				SetTextColor( hdc, RGB(255, 255, 255));	//클랜이름입력시 흰색				
			}
			else {
				SetTextColor( hdc, RGB(230, 255, 240));	//일반글자색
			}
			dsTextLineOut(hdc, x, y, strbuf, lstrlen(strbuf));
			*/
			

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	

	if(sw==1) 
	{
		static cnt=0;
		cnt++;
		if(cnt<20) {
			SetTextColor( hdc, RGB(255, 255, 255));
			dsTextLineOut(hdc, x + (lstrlen(str)*6) , y-16, "|", 1);
		}
		if(cnt>=40) cnt=0;
	}

	if(oldFont)
		SelectObject( hdc, oldFont);
	renderDevice.lpDDSBack->ReleaseDC(hdc);

}

extern BOOL IsDrawGuideHelp;
//int g_LevelLabel2[] = {1,2,3,4,5,6,7,8,9,10,12,15,17,20,22,25,30,40,50,55,60,65,70,80};
void InitGuideContentHelp()
{	
	BOOL bisEqual = FALSE;
	int SaveLevel = 0;
	extern int g_LevelLabel[];
	for(int i = 0; g_LevelLabel[i] != 0; i++)
	{
		if(g_LevelLabel[i] == sinChar->Level)
		{
			bisEqual = TRUE;
			SaveLevel = i;
			break;
		}
	}
	if(!bisEqual) return;
	g_GuideHelp.SetDoing(TRUE);
	g_GuideHelp.SetStartPos(0,0);	
	g_GuideHelp.CheckLevel(sinChar->Level);
	
	//g_GuideHelp.CheckLevel(g_LevelLabel[nLevelHelpCount-nPos-1],sinChar->JOB_CODE);
	g_GuideHelp.CheckLevel(g_LevelLabel[SaveLevel],sinChar->JOB_CODE);
	g_GuideHelp.SetHelpN(GUIDEHELP_CONTENT);
	g_GuideHelp.menuInit(GUIDEHELP_CONTENT);

	IsDrawGuideHelp = TRUE;
}
//haGoon가이드 초보 도움말
int CHelp::haGuidHelpLevel_1(DWORD Code)
{
	if((Code&sinITEM_MASK2)==sinWA1||(Code&sinITEM_MASK2)==sinWC1||(Code&sinITEM_MASK2)==sinWH1||(Code&sinITEM_MASK2)==sinWM1||
		(Code&sinITEM_MASK2)==sinWP1||(Code&sinITEM_MASK2)==sinWS1||(Code&sinITEM_MASK2)==sinWS2||(Code&sinITEM_MASK2)==sinWT1){
		haGuidHelpLevel_1Flag = 1;
	}
	else
		haGuidHelpLevel_1Flag = 2;
	
	return TRUE;
}