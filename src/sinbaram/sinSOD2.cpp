/*----------------------------------------------------------------------------*
*	파일명 :  sinSOD2.cpp
*	하는일 :  현재 Test 용으로 쓰이고 있따
*	작성일 :  최종업데이트 4월 
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\clan_Enti.h"
#include "tjboy\\isaocheck\\auth.h"
#include "..\\FontImage.h"
#include "..\\bellatraFontEffect.h" //폰트 이펙트
#include "..\\field.h"
#include "Server\\onserver.h"


cSINSOD2 cSinSod2;
cSINSIEGE cSinSiege;
sinMESSAGEBOX_NEW sinMessageBox_New;

DIRECTDRAWSURFACE	lpbltr_clanN;
DIRECTDRAWSURFACE	lpbltr_clanB;
int Matbltr_Paper291;
int Matbltr_Paper291_Text;

DIRECTDRAWSURFACE	lpbltr_ButtonBox;
DIRECTDRAWSURFACE	lpbltr_Button_Clan;
DIRECTDRAWSURFACE	lpbltr_Button_Clan_G;
DIRECTDRAWSURFACE	lpbltr_Button_Prize;
DIRECTDRAWSURFACE	lpbltr_Button_Prize_G;
DIRECTDRAWSURFACE	lpbltr_Button_OK;
DIRECTDRAWSURFACE	lpbltr_Button_OK_G;

int Matbltr_Logo;
DIRECTDRAWSURFACE    lpbltr_ClanRank_Title;
int Matbltr_ClanRank_KindBar;
DIRECTDRAWSURFACE    Matbltr_ClanRank_ListLine;


RECT SodButtonRect[3] = {
	{111,393,111+68,393+23},
	{189,393,189+68,393+23},
	{267,393,267+68,393+23},

};

int MatSod2Box[10]; //박스 Mat

/*----------------------------------------------------------------------------*
*						 Init
*-----------------------------------------------------------------------------*/	
void cSINSOD2::Init()
{
	char szBuff[128];
	for(int i = 0 ; i < 9 ; i++){
		wsprintf(szBuff,"Image\\SinImage\\Help\\box%d.tga",i+1);
		MatSod2Box[i] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	}
	MatSod2Box[9] = CreateTextureMaterial( "Image\\SinImage\\Help\\Box_Line.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	Matbltr_Paper291 = CreateTextureMaterial( "Image\\SinImage\\Help\\bltr_paper291_145.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	Matbltr_Paper291_Text = CreateTextureMaterial( "Image\\SinImage\\Help\\bltr_paper_txt.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	Matbltr_Logo = CreateTextureMaterial( "Image\\SinImage\\Help\\bltr.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	Matbltr_ClanRank_KindBar = CreateTextureMaterial( "Image\\SinImage\\Help\\bltr_list-title.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	Load();
}
/*----------------------------------------------------------------------------*
*						 Load
*-----------------------------------------------------------------------------*/	
void cSINSOD2::Load()
{

	//벨라트라 운영클랜
	lpbltr_clanN = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_clanN.bmp" );
	lpbltr_clanB = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_clanB.bmp" );
	lpbltr_ButtonBox = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_box.bmp" );
	lpbltr_Button_Clan = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_bt1.bmp" );
	lpbltr_Button_Clan_G = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_bt1_.bmp" );
	lpbltr_Button_Prize = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_bt2.bmp" );
	lpbltr_Button_Prize_G = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_bt2_.bmp" );
	lpbltr_Button_OK = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_bt3.bmp" );
	lpbltr_Button_OK_G = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_bt3_.bmp" );
	lpbltr_ClanRank_Title = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_list-title.bmp" );
	Matbltr_ClanRank_ListLine = LoadDibSurfaceOffscreen( "Image\\SinImage\\Help\\bltr_list-line.bmp" );

}
/*----------------------------------------------------------------------------*
*						Release
*-----------------------------------------------------------------------------*/	
void cSINSOD2::Release()
{

}
/*----------------------------------------------------------------------------*
*						Draw
*-----------------------------------------------------------------------------*/	
void cSINSOD2::Draw()
{

	
	int i = 0, j =0 , t = 0;   

	//박스를 그린다
	if(sinMessageBox_New.Flag){          
		for(i = 0 ; i < 9 ; i++){ 
			switch(i){
				case 0: //상단 왼쪽 귀퉁이
					dsDrawTexImage( MatSod2Box[i] , sinMessageBox_New.PosiX, sinMessageBox_New.PosiY
						, 64, 32 , 255 );  //인터페이스 메인   
				break;
				case 1: //상단 중간
					dsDrawTexImage( MatSod2Box[i] , sinMessageBox_New.PosiX+64, sinMessageBox_New.PosiY
						, sinMessageBox_New.SizeW-(64*2), 32 , 255 );  //인터페이스 메인   
				break;

				case 2: //상단 오른쪽
					dsDrawTexImage( MatSod2Box[i] , sinMessageBox_New.PosiX+sinMessageBox_New.SizeW-64, sinMessageBox_New.PosiY
						, 64, 32 , 255 );  //인터페이스 메인   
				break;
				case 3: //중단 왼쪽
					dsDrawTexImage( MatSod2Box[i] , sinMessageBox_New.PosiX-1, sinMessageBox_New.PosiY+32
						, 64, sinMessageBox_New.SizeH-(64+32), 255 );  //인터페이스 메인     
				break;
				case 4: //중단 가운데 
					dsDrawTexImage( MatSod2Box[i] , sinMessageBox_New.PosiX+64-1, sinMessageBox_New.PosiY+32
						, sinMessageBox_New.SizeW-(64*2)+1, sinMessageBox_New.SizeH-(64+32) , 255 );  //인터페이스 메인      
				break;
				case 5: //중단 오른쪽
					dsDrawTexImage( MatSod2Box[i] , sinMessageBox_New.PosiX+sinMessageBox_New.SizeW-64, sinMessageBox_New.PosiY+32
						, 64, sinMessageBox_New.SizeH-(64+32) , 255 );  //인터페이스 메인   
				break; 

				case 6: //하단 왼쪽 
					dsDrawTexImage( MatSod2Box[i] , sinMessageBox_New.PosiX, sinMessageBox_New.PosiY+sinMessageBox_New.SizeH-64
						, 64, 64 , 255 );  //인터페이스 메인   
				break;
				case 7: //하단 중간 
					for(t = 0 ; t < 6; t++){ //귀찮아서 살짝땜빵 하핫       
						dsDrawTexImage( MatSod2Box[i] , sinMessageBox_New.PosiX+64+(t*(32)), sinMessageBox_New.PosiY+sinMessageBox_New.SizeH-64
							, 32, 64 , 255 );  //인터페이스 메인   

					//	dsDrawTexImage( MatSod2Box[i] , sinMessageBox_New.PosiX+64, sinMessageBox_New.PosiY+sinMessageBox_New.SizeH-64
					//		, sinMessageBox_New.SizeW-(64*2), 64 , 255 );  //인터페이스 메인   
					}
				break;
				case 8: //하단 오른쪽 
					dsDrawTexImage( MatSod2Box[i] , sinMessageBox_New.PosiX+sinMessageBox_New.SizeW-64, sinMessageBox_New.PosiY+sinMessageBox_New.SizeH-64
						, 64, 64 , 255 );  //인터페이스 메인    
				break;

			}

		}
		//라인
		dsDrawTexImage( MatSod2Box[9] , sinMessageBox_New.PosiX+7, sinMessageBox_New.PosiY+50
			, sinMessageBox_New.SizeW-(7*2), 16 , 255 );  //인터페이스 메인    

	}

	if(BoxIndex == 1 ){ //첫페이지의 일반유저 
		
		//벨라트라 로고
		dsDrawTexImage( Matbltr_Logo , 152, 97 , 128, 64 , 255 );    

		//벨라트라 운영클랜
		DrawSprite(97,156 , lpbltr_clanN,0,0,116,12);    

		//벨라트라 운영클랜 페이퍼
		dsDrawTexImage( Matbltr_Paper291 , 78, 241 , 291, 145 , 255 );    


		switch(UserType){
			case 1: //일반유저 
			//운영클랜 클랜마크 박스
			DrawSprite(97,284 , lpbltr_clanB,0,0,49,49);       
			DrawSprite(105,292 , ClanMark_32,0,0,32,32);    
			break;
			case 2:
				dsDrawTexImage( Matbltr_Paper291_Text , 95, 255 , 256, 128 , 255 );   

			break;
			case 3:
				dsDrawTexImage( Matbltr_Paper291_Text , 95, 255 , 256, 128 , 255 );   
				//상금찾기 박스
				DrawSprite(189,393 , lpbltr_ButtonBox,0,0,68,23);    
				//상금찾기 (그레이
				DrawSprite(199,399 , lpbltr_Button_Prize_G,0,0,47,12);    
			break;
			case 4:
				//운영클랜 클랜마크 박스
				DrawSprite(97,284 , lpbltr_clanB,0,0,49,49);       
				DrawSprite(105,292 , ClanMark_32,0,0,32,32);    

				//상금찾기 박스
				DrawSprite(189,393 , lpbltr_ButtonBox,0,0,68,23);    
				//상금찾기 (그레이
				DrawSprite(199,399 , lpbltr_Button_Prize_G,0,0,47,12);    
			break;
			case 6:
				//상금찾기 박스
				DrawSprite(189,393 , lpbltr_ButtonBox,0,0,68,23);    
				//상금찾기 (그레이
				DrawSprite(199,399 , lpbltr_Button_Prize_G,0,0,47,12);    

			break;
		}
		/////////////////////////////버튼
		//클랜순위 박스
		DrawSprite(111,393 , lpbltr_ButtonBox,0,0,68,23);    
		//확인 박스
		DrawSprite(267,393 , lpbltr_ButtonBox,0,0,68,23);    
		//클랜순위 버튼 (그레이)
		DrawSprite(121,399 , lpbltr_Button_Clan_G,0,0,47,12);    
		//확인 버튼 (그레이)
		DrawSprite(277,399 , lpbltr_Button_OK_G,0,0,47,12);    

	}
	vector<string>::size_type k = 0;
	if(BoxIndex == 2 ){ //클랜순위 페이지
		//클랜순위 타이틀
		DrawSprite(152,97 , lpbltr_ClanRank_Title,0,0,143,19);    
		
		//No . 클랜 . 포인트 . 기록일시 Bar
		dsDrawTexImage( Matbltr_ClanRank_KindBar , 78, 147 , 512, 32 , 255 );   

		//List Line
		for(j = 0; j < 10 ; j++){
			DrawSprite(78,173+(j*20) , Matbltr_ClanRank_ListLine,0,0,287,20);    
			
		}
		//확인 박스
		DrawSprite(189,393 , lpbltr_ButtonBox,0,0,68,23);    
		//확인 (그레이)
		DrawSprite(199,399 , lpbltr_Button_OK_G,0,0,47,12);   

		for(int t = 0; t < 10 ; t++){      
			if(ClanMarkIndex[t] >= 0){
				DrawSprite(103,174+(t*20) , ClanMark[t],0,0,16,16);
			}
		}
	}


	if(sinMessageBox_New.ButtonIndex){ 
		if(BoxIndex == 1){
			switch(sinMessageBox_New.ButtonIndex){
				case 1:
					//클랜순위 버튼 (활성)
					DrawSprite(121,399 , lpbltr_Button_Clan,0,0,47,12);    
				break;
				case 2:
					//상금찾기 (활성)
					DrawSprite(199,399 , lpbltr_Button_Prize,0,0,47,12);    

				break;
				case 3:
					//확인 버튼 (활성)
					DrawSprite(277,399 , lpbltr_Button_OK,0,0,47,12);    
				break;
			}
		}
		if(BoxIndex == 2){
			if(sinMessageBox_New.ButtonIndex == 2){
				//상금찾기 (활성)
				DrawSprite(199,399 , lpbltr_Button_OK,0,0,47,12);    
			}
		}
	}
}
/*----------------------------------------------------------------------------*
*						DrawText
*-----------------------------------------------------------------------------*/	
void cSINSOD2::DrawText()
{
	int Posi[] = {103,120,230,296};  
	int i = 0, k=0;
	vector<string>::size_type j = 0;
	HDC	hdc;
	renderDevice.lpDDSBack->GetDC(&hdc);
	SelectObject( hdc, sinFont); 
    SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, RGB(255,244,201) ); 

	char szTempBuff[128];

	//문구
	if(BoxIndex == 1){   
		switch(UserType){
			case 1: //일반유저
				for( i = 0 ; i < 3; i++){   
					if(i ==2){
						wsprintf(szTempBuff,SodMessage_Etc[i],Tax,"%");
						dsTextLineOut(hdc,97,182+(14*i), szTempBuff, lstrlen(szTempBuff));
					}
					else{
						dsTextLineOut(hdc,97,182+(14*i), SodMessage_Etc[i], lstrlen(SodMessage_Etc[i]));
					}
				}
				//클랜 메세지가 들어간다
				while(j != sinClanMessage.size()){
					dsTextLineOut(hdc,154,281+(j*20),sinClanMessage[j].c_str() , lstrlen(sinClanMessage[j].c_str()));
					j++;
				}

				//클랜 장
				wsprintf(szTempBuff,"%s : %s",sinClanMaster7,szClanMaster);
				dsTextLineOut(hdc,230,355, szTempBuff, lstrlen(szTempBuff));

				//운영클랜
				SelectObject( hdc, sinBoldFont);
				SetTextColor( hdc, RGB(255,244,201) );   
				dsTextLineOut(hdc,185,255, szClanName, lstrlen(szClanName));


			break;
			case 2: //클랜 유저
				for( i = 0 ; i < 2; i++){    
					dsTextLineOut(hdc,97,182+(14*i), SodMessage_Clan[i], lstrlen(SodMessage_Clan[i]));
				}
				
				memset(&szTempBuff,0,sizeof(szTempBuff));
				NumLineComa(TotalEMoney,szTempBuff);
				dsTextLineOut(hdc,170,283, szTempBuff, lstrlen(szTempBuff));

				wsprintf(szTempBuff,"%d%s",Tax,"%");
				dsTextLineOut(hdc,170,301, szTempBuff, lstrlen(szTempBuff));

				memset(&szTempBuff,0,sizeof(szTempBuff));
				NumLineComa(TotalMoney,szTempBuff);
				dsTextLineOut(hdc,170,320, szTempBuff, lstrlen(szTempBuff));

			break;
			case 3: //클랜 마스터
				for( i = 0 ; i < 3; i++){   
					dsTextLineOut(hdc,97,182+(14*i), SodMessage_Master[i], lstrlen(SodMessage_Master[i]));
				}
				memset(&szTempBuff,0,sizeof(szTempBuff));
				NumLineComa(TotalEMoney,szTempBuff);
				dsTextLineOut(hdc,170,283, szTempBuff, lstrlen(szTempBuff));

				wsprintf(szTempBuff,"%d%s",Tax,"%");
				dsTextLineOut(hdc,170,301, szTempBuff, lstrlen(szTempBuff));

				memset(&szTempBuff,0,sizeof(szTempBuff));
				NumLineComa(TotalMoney,szTempBuff);
				dsTextLineOut(hdc,170,320, szTempBuff, lstrlen(szTempBuff));

			break;
			case 4: //찾을돈이 있는 클랜
				for( i = 0 ; i < 3; i++){    
					if(i ==2){
						wsprintf(szTempBuff,SodMessage_Etc[i],Tax,"%");
						dsTextLineOut(hdc,97,182+(14*i), szTempBuff, lstrlen(szTempBuff));
					}
					else{
						dsTextLineOut(hdc,97,182+(14*i), SodMessage_Etc[i], lstrlen(SodMessage_Etc[i]));
					}
				}
				//클랜 메세지가 들어간다
				while(j != sinClanMessage.size()){
					dsTextLineOut(hdc,154,281+(j*20),sinClanMessage[j].c_str() , lstrlen(sinClanMessage[j].c_str()));
					j++;
				}

				//클랜 장
				wsprintf(szTempBuff,"%s : %s",sinClanMaster7,szClanMaster);
				dsTextLineOut(hdc,230,355, szTempBuff, lstrlen(szTempBuff));

				//운영클랜
				SelectObject( hdc, sinBoldFont);
				SetTextColor( hdc, RGB(255,244,201) );   
				dsTextLineOut(hdc,185,255, szClanName, lstrlen(szClanName));

			break;
			case 6:
				for( i = 0 ; i < 3; i++){   
					if(i ==2){
						wsprintf(szTempBuff,SodMessage_Etc[i],Tax,"%");
						dsTextLineOut(hdc,97,182+(14*i), szTempBuff, lstrlen(szTempBuff));

					}
					else{
						dsTextLineOut(hdc,97,182+(14*i), SodMessage_Etc[i], lstrlen(SodMessage_Etc[i]));
					}
				}
			
				SelectObject( hdc, sinBoldFont); 
				SetTextColor( hdc, RGB(255,244,201) );   
				dsTextLineOut(hdc,185,255, cldata.name, lstrlen(cldata.name)); 

				SelectObject( hdc, sinFont);  
				wsprintf(szTempBuff,"%s : ",sinPrize7);
				dsTextLineOut(hdc,110,283, szTempBuff, lstrlen(szTempBuff));

				memset(&szTempBuff,0,sizeof(szTempBuff));   
				NumLineComa(ClanMoney,szTempBuff);
				dsTextLineOut(hdc,152,283, szTempBuff, lstrlen(szTempBuff));

				dsTextLineOut(hdc,110,301, OtherClanMaster[0], lstrlen(OtherClanMaster[0]));
				dsTextLineOut(hdc,110,320, OtherClanMaster[1], lstrlen(OtherClanMaster[1]));
			break;
		}
		//운영클랜
		SelectObject( hdc, sinBoldFont);
		SetTextColor( hdc, RGB(255,205,4) );   
		dsTextLineOut(hdc,223,157, szClanName, lstrlen(szClanName));
	}
	char szTempNum[16];
	int  TempNum;
	char szTempBuff2[128];
	memset(&szTempBuff2,0,sizeof(szTempBuff2));
	if(BoxIndex == 2){       
		while(j != sinClanRank.size()){
			if((j%4)!=0){
				SelectObject( hdc, sinBoldFont);
				SetTextColor( hdc, RGB(255,205,4) ); //순번
				wsprintf(szTempNum,"%d",k+1);
				if(k+1 == 10){
					dsTextLineOut(hdc,82,177+(k*20),szTempNum , lstrlen(szTempNum));
				}
				else{
					dsTextLineOut(hdc,86,177+(k*20),szTempNum , lstrlen(szTempNum));
				}
				SelectObject( hdc, sinFont); 
				SetTextColor( hdc, RGB(255,255,255) );
				if((j%4)== 2){
					memset(&szTempBuff2,0,sizeof(szTempBuff2));
					TempNum = atoi(sinClanRank[j].c_str());
					NumLineComa(TempNum,szTempBuff2);
					dsTextLineOut(hdc,5+Posi[j%4],177+(k*20),szTempBuff2 , lstrlen(szTempBuff2));

				}
				else{
					dsTextLineOut(hdc,5+Posi[j%4],177+(k*20),sinClanRank[j].c_str() , lstrlen(sinClanRank[j].c_str()));
				}
			}
			j++;
			if((j%4)==0){
				k++;
			}

		}
	}
	renderDevice.lpDDSBack->ReleaseDC(hdc);
}
/*----------------------------------------------------------------------------*
*						Main
*-----------------------------------------------------------------------------*/	
DWORD ClanRankFlagTime = 0;
void cSINSOD2::Main()
{

	if(sinMessageBox_New.Flag){        
		sinMessageBoxShowFlag = 1; //메세지 박스때문에 일케한다
		sinMessageBox_New.ButtonIndex = 0;
		for(int i = 0 ; i < 3 ; i++){
			if (  sinMessageBox_New.ButtonRect[i].left< pCursorPos.x  && sinMessageBox_New.ButtonRect[i].right > pCursorPos.x  && 
				sinMessageBox_New.ButtonRect[i].top < pCursorPos.y  && sinMessageBox_New.ButtonRect[i].bottom > pCursorPos.y  ){
				if(ClanMasterMessageBoxFlag)break;
				if(BoxIndex == 1){
					if((UserType == 3 || UserType == 4 || UserType == 6)){
						sinMessageBox_New.ButtonIndex = i+1;
					}
					else{
						if(i ==1)continue;
						sinMessageBox_New.ButtonIndex = i+1;

					}
				}
				if(BoxIndex == 2){
					if(i != 1)continue;
					sinMessageBox_New.ButtonIndex = i+1;
				}
			}
		}
		if(BoxIndex == 1){
			if(!ClanMark_32){
				ClanMark_32Time++;
				if(ClanMark_32Time >= 70*3){
					ClanMark_32Time = 0;     
					ClanMark_32Index = ReadClanInfo_32X32(ClanImageNum);
					ClanMark_32 = ClanInfo[ClanMark_32Index].hClanMark32;
				}
			}
			if(ClanRankFlag){
				ClanRankFlagTime++;
				if(ClanRankFlagTime >= 70*2){
					ClanRankFlag = 0;
				}
			}
		}
		if(BoxIndex == 2){ 
			for(int t = 0; t < 10 ; t++){ 
				if(!ClanMark[t] ){
					ClanMarkLoadTime[t]++;
					if(ClanMarkLoadTime[t] >= 70*3){
		 				ClanMarkLoadTime[t] = 0;
						ClanMarkIndex[t] = ReadClanInfo( ClanMarkNum[t]);
						if(ClanInfo[ClanMarkIndex[t]].hClanMark){
							ClanMark[t] = ClanInfo[ClanMarkIndex[t]].hClanMark;
						}
					}
				}
			}
		}
	}
}
/*----------------------------------------------------------------------------*
*						Close
*-----------------------------------------------------------------------------*/	
void cSINSOD2::Close()
{

}
/*----------------------------------------------------------------------------*
*						LbuttonDown
*-----------------------------------------------------------------------------*/	
void cSINSOD2::LButtonDown(int x , int y)
{

	if(sinMessageBox_New.Flag){  
		if(sinMessageBox_New.ButtonIndex){
			if(BoxIndex == 1){
				switch(sinMessageBox_New.ButtonIndex){
					case 1:
						//클랜순위 버튼 (활성)
						if(!ClanRankFlag){
							sod2INFOindex(UserAccount, sinChar->szName,szConnServerName,3);
							ClanRankFlag = 1;
							
						}
						//sod2INFOindex("inouess", "아처2002","아웰",3);
						//RecvClanRank(szTemp);
		
					break;
					case 2:
						if(UserType != 6 ){ 
							SendClanMoneyToServer(0,0);
						}
						if(UserType == 6){
							if(ClanMoney){
								cMessageBox.ShowMessage2(MESSAGE_SOD2_GET_MONEY);
								ClanMasterMessageBoxFlag = 1;
							}
							else{
								cMessageBox.ShowMessage(MESSAGE_DONT_HAVE_CLANMONEY);
							}
						}
					break;
					case 3:
						//확인 버튼 (활성)
						CloseSod2MessageBox();		
					break;

				}
			}
			if(BoxIndex == 2){
				if(sinMessageBox_New.ButtonIndex == 2){
					//확인 버튼 (활성)
					CloseSod2MessageBox();
				}
			}
		}
	}
}
/*----------------------------------------------------------------------------*
*						LbuttonUp
*-----------------------------------------------------------------------------*/	
void cSINSOD2::LButtonUp(int x , int y)
{


}
/*----------------------------------------------------------------------------*
*						RbuttonDown
*-----------------------------------------------------------------------------*/	
void cSINSOD2::RButtonDown(int x , int y)
{

}
/*----------------------------------------------------------------------------*
*						RbuttonUp
*-----------------------------------------------------------------------------*/	
void cSINSOD2::RButtonUp(int x, int y)
{

}
/*----------------------------------------------------------------------------*
*						KeyDown
*-----------------------------------------------------------------------------*/	
void cSINSOD2::KeyDown()
{

}
/*----------------------------------------------------------------------------*
*						Sod2박스를 닫는다
*-----------------------------------------------------------------------------*/	
void cSINSOD2::CloseSod2MessageBox()
{
	memset(&sinMessageBox_New,0,sizeof(sinMESSAGEBOX_NEW));
	BoxIndex = 0;
	UserType = 0;
	sinMessageBoxShowFlag = 0;
	ClanRankFlag = 0;
}
/*----------------------------------------------------------------------------*
*						Sod2박스를 보여준다
*-----------------------------------------------------------------------------*/	
void cSINSOD2::ShowSod2MessageBox()
{
	//웹 DB에 접속해서 데이타를 가져온다
	//sod2INFOindex("inouess", "아처2002","아웰", 1);
	sod2INFOindex(UserAccount, sinChar->szName,szConnServerName,1);
	
}

//새로운 메세지 박스를 띄운다
int ShowSinMessageBox_New(int PosiX , int PosiY , int SizeW , int SizeH , RECT *rect ,int ButtonNum)
{
	if(sinMessageBox_New.Flag)return FALSE; //메세지 박스를 닫고와야한다 안그럼 즐~
	sinMessageBox_New.ButtonRect[0] = rect[0]; //3개까지만된다
	sinMessageBox_New.ButtonRect[1] = rect[1];  
	sinMessageBox_New.ButtonRect[2] = rect[2]; 
	sinMessageBox_New.PosiX = PosiX;
	sinMessageBox_New.PosiY = PosiY;
	sinMessageBox_New.SizeW = SizeW;
	sinMessageBox_New.SizeH = SizeH;
	sinMessageBox_New.ButtonNum = ButtonNum;
	sinMessageBox_New.Flag = 1;
	sinMessageBoxShowFlag = 1;
	return TRUE;
}

/*----------------------------------------------------------------------------*
*						Web Data 클라이언트로 파싱
*-----------------------------------------------------------------------------*/	
void cSINSOD2::RecvWebDaTa() //현재는 테스트로 쓴다
{
	

}
void cSINSOD2::RecvClanRank(char *szBuff)
{
	//115001132 -아마게돈- 1329660 2004-05-07
	//string Test ="1 호동프린스클랜 10010020 2004/05/05 2 신바람클랜 553340 2004/2332/1 3 펭귄클랜 12131001 2003/05/23";
	//string Test = "Code=2 CIMG=121000196 CName=BS-ClaN_아웰 CPoint=591260 CRegistDay=2004/05/04 CIMG=103001219 CName=별난온달 CPoint=546943 CRegistDay=2004/05/04 CIMG=104000979 CName=[NEO]오메가 CPoint=479030 CRegistDay=2004/05/05 CIMG=112000075 CName=도깨비 CPoint=454562 CRegistDay=2004/05/04 CIMG=115001132 CName=-아마게돈- CPoint=451679 CRegistDay=2004/05/04 CIMG=102001120 CName=[희진사랑] CPoint=438589 CRegistDay=2004/05/05 CIMG=109000660 CName=GladiaTor CPoint=364726 CRegistDay=2004/05/04 CIMG=118000957 CName=pUrplEviShop CPoint=357253 CRegistDay=2004/05/04 CIMG=111001179 CName=엽긔호러가족 CPoint=302324 CRegistDay=2004/05/04";
	//sinClanRank = Split_ClanRankDaTa(Test);

}

// Space를 키값으로 스트링을 분리한다
vector<string> cSINSOD2::Split_ClanRankDaTa(const string& s)
{

	vector<string> ret; 
	typedef string::size_type string_size;
	string_size i = 0;
	while(i != s.size()){ 
		while(i != s.size()){
			if(s[i] & 0x80)break; //한글이면 건너뛰자
			if(isspace(s[i])){
				++i;
			}
			else break;
		}
		string_size j =i;
		while(j != s.size()){
			if((j-i) > 200 ){
				i = s.size();
				j = i;
				break;
			}
			if(s[j] & 0x80){ //한글이면 인덱스 2칸을지나 다시체크 (0x80을 이진수로하면 128 ) 
				j +=2;       // 0000 0000 중에 뒷부분을 다채우고 옆으로 넘어가게되면 2Byte를 사용하는 한글이란뜻임
				continue;
			}
			if(!isspace(s[j])){
				++j;
			}
			else break;
		}
		if(i != j ){
			ret.push_back(s.substr(i,j-i));
			i = j;
		}
	}

	//Code별로 다시 파싱한다
	vector<string> ret2;
	string_size k = 0;
	string_size e = 0;
	string STempNum;
	string CodeTemp;
	int TempNumCnt = 0;

	//요기서 초기화
	for(int p = 0; p < 10 ; p++){
		ClanMarkNum[p] = -1;
	}

	i = 0; //앞부분에는 CODE가 있다
	while(i < ret.size()){ 
		while(k != ret[i].size()){
			if(ret[i][k] == '='){ 
				CodeTemp.clear();
				CodeTemp = ret[i].substr(0,k);
				if( i ==0 && CodeTemp == "Code"){
					STempNum.clear(); //이거안해주고 atoi하다가 뻑날때있다 어찌나 까다로운 string인지
					STempNum = ret[i].substr(k+1,ret[i].size()-(k+1));
					if(atoi(STempNum.c_str()) == 2){
						ret2.clear();
						return ret2;
					}
					else break;
				}
				
				ret2.push_back(ret[i].substr(k+1,ret[i].size()-(k+1)));
				if(CodeTemp == "CIMG"){
					STempNum.clear(); //이거안해주고 atoi하다가 뻑날때있다 어찌나 까다로운 string인지
					STempNum = ret[i].substr(k+1,ret[i].size()-(k+1));
					ClanMarkNum[TempNumCnt] = atoi(STempNum.c_str());
					ClanMarkIndex[TempNumCnt] = ReadClanInfo( ClanMarkNum[TempNumCnt] );
					TempNumCnt++;
				}
				k = 0;
				break;
			}
			k++;
		}
		i++;
	}

	//클랜마크를 로드한다
	for(int t = 0 ;t < TempNumCnt ; t++){ 
		if(ClanMarkIndex[t] >= 0){
			if(ClanInfo[ClanMarkIndex[t]].hClanMark){ //TempNumCnt이 한개라도 있어야 로드할이미지가있는거다
				ClanMark[t] = ClanInfo[ClanMarkIndex[t]].hClanMark;
			}
		}
	}
	return ret2;		
}
// 분할될 스트링의 길이를 기준으로 분할한다
vector<string> cSINSOD2::Split_ClanMessage(const string& s , const int Len[])
{

	vector<string> ret;  
	typedef string::size_type string_size; 
	string_size i = 0;
	string_size j = 0;
	int LenCnt = 0;
	while(i < s.size()){
		if(s[i] & 0x80)i += 2;  //한글
		else i++;
		if( (int)i-(int)j >= Len[LenCnt]){
			if(Len[LenCnt+1] == 0){
				ret.push_back(s.substr(j,i-j));
				break;
			}
			ret.push_back(s.substr(j,i-j));
			j = i;
			LenCnt++;
		}
		if(s[i] == '|'){
			ret.push_back(s.substr(j,i-j));
			break;
		}
	}

	/*
	int LenCnt = 0;  
	vector<string> ret; 
	typedef string::size_type string_size; 
	string_size i = 0;
	string_size j = 0;
	string_size k = 0;
	while(i < s.size()){ 
		if(s[i] & 0x80){
			i +=2;
			if(i == s.size()){
				ret.push_back(s.substr(j,i-j));
				break;
			}
			continue;
		}
		else{
			if( (int)i-(int)j >= Len[LenCnt]){
				if(isspace(s[i])){
					if(Len[LenCnt+1] == 0){
						i = s.size(); //짜투리 글씨는 다찍어준다
						ret.push_back(s.substr(j,i-j));
						break;
					}
					ret.push_back(s.substr(j,i-j));
					++i; 
					j = i;
					LenCnt++;
				}
			}
			++i;
			if(i == s.size()){
				ret.push_back(s.substr(j,i-j));
				break;
			}

		}
	}
	*/
	return ret;		
}

// 웹 DB에서 받은 데이타를 구분한다
vector<string> cSINSOD2::Split_Sod2DaTa(const string& s)
{
	string Temp33;
	vector<string> ret; 
	typedef string::size_type string_size;
	string_size i = 0;
	while(i < s.size()){ 
		while(i < s.size()){
			if(s[i] == '|'){
				++i;
			}
			else break;
		}
		string_size j = i;
		while(j < s.size()){
			if((j - i) > 200){
				i = s.size(); //while루프를 끝낸다
				j = i; 
				break;
			}
			if(s[j] != '|'){
				++j;
			}
			else break;
		}
		if(i != j ){
			Temp33 = s.substr(i,j-i);
			ret.push_back(s.substr(i,j-i));
			i = j;
		}
	}

	//Code별로 다시 파싱한다
	string Temp;
	string Temp2;
	string_size k = 0;
	string_size e = 0; 
	int NumTemp = 0;
	int TempArray[] = {28,22,26,0}; 
	i = 0; 
	while(i < ret.size()){
		while(k < ret[i].size()){
			if(ret[i][k] == '='){ 
				Temp.clear();
				Temp = ret[i].substr(0,k);

				Temp2.clear();
				Temp2 = ret[i].substr(k+1,ret[i].size()-(k+1));

				/*
				if(k+1 == ret[i].size()){
					if(i+1 != ret.size()){
						if(ret[i+1][0] != 'C'){  //또땜빵 -_- 바쁘다보니 할수없다
							Temp2.clear();
							Temp2 = ret[i+1].c_str();
						}
					}
				}
				*/
				
				if(Temp == "Code"){
					NumTemp = atoi(Temp2.c_str());
					switch(NumTemp){
						case 0:
						case 5:
						case 6:
							UserType = 1;
						break;
						case 1:
							UserType = 3;
						break;
						case 2:
						case 3:
							UserType = 2;
						break;
						case 4:
							UserType = 4;
						break;
					}
		
				}
				if(Temp == "CName"){
					lstrcpy(szClanName,Temp2.c_str());
				}
				if(Temp == "CNote"){
					//Temp2 ="한글한글한글한글한글한글한글한글한글한글한글한글한글한글한글한글한글한글한글한글";
					Temp2.push_back('|');
					sinClanMessage = Split_ClanMessage(Temp2 , TempArray);
				}
				if(Temp == "CZang"){
					lstrcpy(szClanMaster,Temp2.c_str());

				}
				if(Temp == "CIMG"){
					ClanImageNum = atoi(Temp2.c_str());
					ClanMark_32Index = ReadClanInfo_32X32(ClanImageNum);
					ClanMark_32 = ClanInfo[ClanMark_32Index].hClanMark32;

				}
				if(Temp == "TotalEMoney"){
					TotalEMoney = atoi(Temp2.c_str());

				}
				if(Temp == "CTax"){
					Tax = atoi(Temp2.c_str());

				}
				if(Temp == "TotalMoney"){
					TotalMoney = atoi(Temp2.c_str());

				}
				if(Temp == "CClanMoney"){
					ClanMoney = atoi(Temp2.c_str());
				}
				k = 0;
				break;
			}
			k++;
		}
		i++;
	}

	return ret;		
}


//웹 DB에서 메세지를 받는다
int cSINSOD2::RecvWebData(int Index , const string& s)
{
	vector<string> Temp_V;   
	if(bip_port_error)return FALSE;   
	if(Index){     
		//Init(); 
		if(Index == 1){     
			Temp_V = Split_Sod2DaTa(s);  
			if(Temp_V.size() <= 0)return FALSE;
			BoxIndex = 1;      
			ShowSinMessageBox_New(62,78,381-62,426-78 ,SodButtonRect );
			//UserType = 2; //1 일반유저 , 2 클랜원 ,3 클랜마스터 ,4 돈찾을거 있는 클랜마스터
			//if(UserType == 4 || UserType == 3){
			//	SendClanMoneyToServer(0,0);
			//}
		}
		else if(Index == 3){
			//ClanRankFlag = 1;
			sinClanRank = Split_ClanRankDaTa(s);
			if(sinClanRank.size() <= 0)return FALSE;
			BoxIndex = 2;
			//ShowSinMessageBox_New(62,78,381-62,426-78 ,SodButtonRect );
		}
		//여기서 Clan 마스터인지 Clan 원인지 일반 유저인지를 가려서 메뉴를 보여준다
	}
	return TRUE;
}

//클랜칩이 금액을 찾는다
int sinRecvClanMoney(int RemainMoney , int GetMoney)
{
	//공성전 세금총액을 세팅한다.
	if(haSiegeMenuFlag){
		if(RemainMoney){
			cSinSiege.TotalTax = RemainMoney;
			cSinSiege.ExpectedTotalTax = RemainMoney; //해외세금
		}
		if(GetMoney){
			CheckCharForm();//인증 
			sinPlusMoney2(GetMoney); 
			sinPlaySound(SIN_SOUND_COIN);
			ReformCharForm();//재인증 	
			SendSaveMoney(); //금액 조작을 못하게하기위해 호출한다 
			cSinSiege.TotalTax = RemainMoney;
			cSinSiege.ExpectedTotalTax = RemainMoney; //해외세금

		}
		return TRUE;
	}

	if(cSinSod2.UserType == 4 || cSinSod2.UserType ==3){ 
		cSinSod2.ClanMoney = RemainMoney;
		if(RemainMoney){
			cMessageBox.ShowMessage2(MESSAGE_SOD2_GET_MONEY);
			cSinSod2.ClanMasterMessageBoxFlag = 1;
			cSinSod2.UserType = 6; 
		}
		else{
			if(cSinSod2.UserType == 4){
				cSinSod2.UserType = 1; //찾을 돈없는 클랜장은 일반회원으로 강등 -0-
			}
			else
				cMessageBox.ShowMessage(MESSAGE_DONT_HAVE_CLANMONEY);

		}
	}
	if(GetMoney){
		CheckCharForm();//인증 
		sinPlusMoney2(GetMoney); 
		sinPlaySound(SIN_SOUND_COIN);
		ReformCharForm();//재인증 	
		SendSaveMoney(); //금액 조작을 못하게하기위해 호출한다 
		cSinSod2.ClanMoney = RemainMoney;
	}

	return TRUE;
}

/*----------------------------------------------------------------------------*
*	
*							( 공 성 전 )
*	
*-----------------------------------------------------------------------------*/	
int sinShowSeigeMessageBox()
{
	//SeigeINFOindex(UserAccount, sinChar->szName,szConnServerName,1);
	return TRUE;
}

int RecvSeigeWebData(int Index , char *string)
{
	//char szTemp[65000];
	//lstrcpy(szTemp,string);

	return TRUE;
}





/*----------------------------------------------------------------------------*
*		 테스트				<ha>공성전 메뉴박스 
*-----------------------------------------------------------------------------*/	

//임시객체
cHASIEGE chaSiege;

/*---사용돼는 각종 플래그----*/
int haSiegeMenuFlag=0;    //공성전 메뉴플랙
int haSiegeMenuKind=0;    //공성전 메뉴종류
int ScrollButtonFlag=0;   //스크롤 사용시 필요한 플랙
int GraphLineFlag=0;    
int haSiegeBoardFlag=0;   //공성 클랜 점수창 플랙
int haSiegeMerFlag=0;     //용병 설정 플랙


/*---정보박스 관련 위치정보---*/
POINT ClanSkillBoxSize={0,0};  //클랜스킬 정보 박스 사이즈
POINT ClanSkillBoxPosi={0,0};  //클랜스킬 정보 박스 포지션

/*---수성설정 관련  인덱스들---*/
int CastleKindIndex  = 0;  //성의 종류 관련 인덱스
int TowerIconIndex = 0;  //타워 종류
int haSendTowerIndex = 0;
int MenuButtonIndex  = 0;  //메뉴 버튼 관련 인덱스

/*--저장돼고 세팅될때  사용될 임시함수들---*/
int HaTestMoney =0;        //임시세금  금액
int HaTaxRate =0;

/*----클랜 보드 설정-----*/
sHACLANDATA sHaClanData[HACLAN_MAX];  //임의 클랜 개수

int  haAlpha   = 0;				//보드의 알파값
int  BoardTime = 0; 
int  haClanSkillTime=0;

int  haTotalDamage =  0;		//토탈 데미지를 찍어줄때 사용한다.
int  haPlayTime[3] = {0};		//보드타임

/*---용병 설정 가격----*/
//임시
int haMercenrayMoney[3] = {50000,100000,300000};    //용병 가격
int	haMercenrayIndex = 0;                           //용병 설정 인덱스
int haTowerMoney =500000;

//크리스탈 카운트를 받는다.
short haCrystalTowerCount[4];    //크리스탈 카운트   

char *haC_CastleWinFilePath   = "image\\Sinimage\\help\\CastleWin.sin" ;
char *haC_CastleLoseFilePath  = "image\\Sinimage\\help\\CastleLose.sin";

char *haC_CastleWin_FilePath  = "image\\Sinimage\\help\\CastleWining.sin" ;
char *haC_CastleLose_FilePath  = "image\\Sinimage\\help\\CastleLoseing.sin";


/*---보드 클랜 이름위치-----*/
char *ScoreBoardName[] = {
	"Battle Point",    //플레이어 스킬 점수          
	"Con Rate",        //자신에 클랜 점수 기여도
	"B.P",
	"PlayTime",        //타임
	"Hit  Rate",	   //자기 클랜의 점수
	"BLESS CASTLE",    //문구
};

//버튼 위치
int SiegeButtonPosi[][4]={
	{70    ,70     ,268,302},    //메인
	{29+70 ,269+70 ,68 ,23},     //재정/방어 설정
	{144+70,269+70 ,48 ,23},     //확인
	{197+70,269+70 ,48 ,23},     //취소
	{270   ,236+70 ,48 ,23},     //돈찾기 확인
	{77+70 ,21+70  ,49 ,11},     //타워 설정버튼
	{179+70-3,21+70,49 ,11},   //용병 설정버튼
};

//공성전 아이콘 위치
int SiegeIconPosi[][4]={
	{26+70,83+70 ,16,16},        //스크롤
	{36+70,94+70 ,30,30},        //타워속성
	{36+70,216+70,30,30},        //클랜스킬 위치
	{8+70 ,45+70 ,51,22},        //성타입
	{10+70 ,63+70 ,12,13},       //타워 테두리
	{26+70,59+70,16,16},         //실제 세율 스크롤
};  
///동영상 플레이어
int  haMatPlayMenu[8]={0};
int  haMovieFlag = 0;
int  haMovieKind = 0;
char haMovieName[64];

int haPlayerPosi[4][4] = {
	{64+68+8,359,32,32},//상중하버튼
	{270    ,363,48,23},//
};

cHASIEGE::cHASIEGE()
{
	int i;
	for(i=0;i<6;i++){
		cSinSiege.TowerTypeDraw[i][1]=0;
	}
	for(i=0;i<4;i++){
		cSinSiege.MercenaryNum[i] =  0;
	}
	
}
cHASIEGE::~cHASIEGE()
{

}

void cHASIEGE::init()
{
	
	
	
}

void cHASIEGE::ImageLoad()
{
 
	lpSiegeTax     = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_tax.bmp");    //재정메인
	lpSiegeDefense = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_menu.bmp");   //방어메인
	lpCastleButton = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button.bmp"); //성메인
	lpMercenary    = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_box.bmp");//용병메인

	lpDefenseButton[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_text.bmp");//방어/용병 설정
	lpDefenseButton[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_tower_text.bmp");

	lpTax_Ok[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button_ok01_.bmp"); //돈찾기 확인버튼
	//lpTax_Ok[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button_ok01.bmp");  
	
	lpSiegeMercenaryIcon[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_ricaM.bmp");
	lpSiegeMercenaryIcon[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_ricaY.bmp");
	lpSiegeMercenaryIcon[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_bress.bmp");

	lpSiegeMercenaryIcon_[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_ricaM_01.bmp");
	lpSiegeMercenaryIcon_[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_ricaY_01.bmp");
	lpSiegeMercenaryIcon_[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_soldier_bress_01.bmp");

	lpSiegeDefeseIcon[0]	= LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_ice.bmp");
	lpSiegeDefeseIcon[1]	= LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_ele.bmp");
	lpSiegeDefeseIcon[2]	= LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_fire.bmp");

	lpSiegeDefeseIcon_[0]  = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_ice01.bmp");
	lpSiegeDefeseIcon_[1]  = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_ele01.bmp"); 
	lpSiegeDefeseIcon_[2]  = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_fire01.bmp"); 

    lpSiegeClanskillIcon[0]	= LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_hp.bmp");
    lpSiegeClanskillIcon[1]	= LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_attack.bmp");
    lpSiegeClanskillIcon[2]	= LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_eva.bmp");


	lpSiegeTaxButton      = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button_creat.bmp");
	lpSiegeDefenseButton  = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_tax_button_defense.bmp");
	lpSiegeOkButton       = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button_ok.bmp");
	lpSiegeCancelButton   = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_button_cancel.bmp");

	lpCastleIcon[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_outa.bmp");
	lpCastleIcon[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_outb.bmp");
	lpCastleIcon[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_ina.bmp");
	lpCastleIcon[3] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_inb.bmp");
	lpCastleIcon[4] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_inc.bmp");
	lpCastleIcon[5] = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_castle_ind.bmp");


	lpTaxScroll[0]   =  LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_arrow01.bmp");
	lpTaxScroll[1]   =  LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_arrow02.bmp");

	lpTaxGraph       =  LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\war_tax_graph.bmp");
}

/*----------------------------------------------------------------------------*
*		              Release
*-----------------------------------------------------------------------------*/
void cHASIEGE::Release()
{
	halpRelease(lpSiegeTaxButton);
	halpRelease(lpSiegeDefenseButton);
	halpRelease(lpSiegeOkButton);
	halpRelease(lpSiegeCancelButton);
	halpRelease(lpTaxScroll[0]);
	halpRelease(lpTaxScroll[1]);
	halpRelease(lpTaxGraph);
	
	for(int i=0;i<6;i++){
		halpRelease(lpCastleIcon[i]);
	}
	for(int i=0;i<3;i++){
		halpRelease(lpSiegeDefeseIcon[i]);
		halpRelease(lpSiegeClanskillIcon[i]);
		halpRelease(haPlayerButton_G[i]);
		halpRelease(haPlayerButton[i]);
		halpRelease(haPlayerButtonBox[i]);
		halpRelease(haPlayerButtonDown[i]);
	}
	halpRelease(lpTwoerImage);

}
//폰트 x좌표


/*----------------------------------------------------------------------------*
*		              메인
*-----------------------------------------------------------------------------*/
void cHASIEGE::Main()
{
	int i;
	
	//==================================================================//
	//               성주가 바뀌면 클랜스킬을 없애준다. 
	//==================================================================//
	if(haClanSkillTime < 70*60*10){
		if(haClanSkillTime > 70*60*7){
			cSkill.CancelContinueSkill(CLANSKILL_ATTACK);
			cSkill.CancelContinueSkill(CLANSKILL_EVASION);
			cSkill.CancelContinueSkill(CLANSKILL_ABSORB);
			haClanSkillTime =70*60*10;
		}
		else{
			haClanSkillTime++;
		}
	}
	//==================================================================//
	//                  공성전 메뉴 설정
	//==================================================================//
	if(haSiegeMenuFlag){
		switch(haSiegeMenuKind){
			case HASIEGE_TAXRATES: //세율 조정
				if(96 < pCursorPos.x &&96+218 > pCursorPos.x && SiegeIconPosi[0][1] < pCursorPos.y && SiegeIconPosi[0][1] +16 > pCursorPos.y ){
					GraphLineFlag   = 1;
				}
				else{
					GraphLineFlag   = 0;
				}
				//확인버튼 관련 플랙
				for(i=1;i<4;i++){
					if(SiegeButtonPosi[i+1][0] < pCursorPos.x && SiegeButtonPosi[i+1][0]+SiegeButtonPosi[i+1][2]> pCursorPos.x 
					 && SiegeButtonPosi[i+1][1]< pCursorPos.y && SiegeButtonPosi[i+1][1]+SiegeButtonPosi[i+1][3] > pCursorPos.y ){
						MenuButtonIndex=i+1;
						break;
					}
					//방어설정 버튼
					else if(SiegeButtonPosi[1][0]  < pCursorPos.x && SiegeButtonPosi[1][0]+SiegeButtonPosi[1][2]> pCursorPos.x 
						   && SiegeButtonPosi[1][1]< pCursorPos.y && SiegeButtonPosi[1][1]+SiegeButtonPosi[1][3] > pCursorPos.y ){
						MenuButtonIndex=7;
						break;
					}
					else{
						MenuButtonIndex=0;
					}
				}
			break;
			case HASIEGE_DEFENSE: //방어 설정
				
				//확인버튼 관련 인덱스
				for(i=1;i<6;i++){
					if(SiegeButtonPosi[i+1][0]  < pCursorPos.x  && SiegeButtonPosi[i+1][0]+SiegeButtonPosi[i+1][2]> pCursorPos.x 
					   && SiegeButtonPosi[i+1][1]< pCursorPos.y && SiegeButtonPosi[i+1][1]+SiegeButtonPosi[i+1][3] > pCursorPos.y ){
							MenuButtonIndex=i+1;
							break;
					}
					//재정설정 버튼
					else if(SiegeButtonPosi[1][0]  < pCursorPos.x && SiegeButtonPosi[1][0]+SiegeButtonPosi[1][2]> pCursorPos.x 
						   && SiegeButtonPosi[1][1]< pCursorPos.y && SiegeButtonPosi[1][1]+SiegeButtonPosi[1][3]> pCursorPos.y ){
							MenuButtonIndex=8;
							break;
					}
					else{
						MenuButtonIndex=0;
					}
				}
				//타워버튼 관련 인덱스
				for(i=0;i<3;i++){
					if(SiegeIconPosi[1][0]+i*84 < pCursorPos.x && SiegeIconPosi[1][0]+SiegeIconPosi[1][2]+i*84 > pCursorPos.x &&
						SiegeIconPosi[1][1] < pCursorPos.y     && SiegeIconPosi[1][1]+SiegeIconPosi[1][3] > pCursorPos.y  ){
							TowerIconIndex = i+1; 
							break;
							
					}
				    else if(SiegeIconPosi[2][0]+i*84 < pCursorPos.x && SiegeIconPosi[2][0]+SiegeIconPosi[2][2]+i*84 > pCursorPos.x &&
						     SiegeIconPosi[2][1] < pCursorPos.y     && SiegeIconPosi[2][1]+SiegeIconPosi[2][3] > pCursorPos.y  ){
							TowerIconIndex = i+4;
							break;
					}		
					else{
						TowerIconIndex=0;
					}
				}

				//성의 현재 타입
				for(i=0;i<6;i++){
					if(SiegeIconPosi[3][0]+i*40 < pCursorPos.x && SiegeIconPosi[3][0]+ SiegeIconPosi[3][2]+i*40 > pCursorPos.x &&
						SiegeIconPosi[3][1] < pCursorPos.y     && SiegeIconPosi[3][1]+ SiegeIconPosi[3][3]> pCursorPos.y  ){
							 CastleKindIndex=i+1;
							 break;
					}
					else{
							 CastleKindIndex=0;
					}
				}
			break;
		}
		//스크롤 움직인다.
		if(ScrollButtonFlag==1){
			if(SiegeIconPosi[0][0]<96){
				SiegeIconPosi[0][0]=96;
				ScrollButtonFlag=0;
			}
			else if(SiegeIconPosi[0][0]>315){
				SiegeIconPosi[0][0]=314;
				ScrollButtonFlag=0;
			}
			else{
				if(95<SiegeIconPosi[0][0]&&SiegeIconPosi[0][0]<316)
					 SiegeIconPosi[0][0] =pCursorPos.x;
			}
		}
	}
	//==================================================================//
	//                  공성전 보드 설정
	//==================================================================//
	//공성전 점수 보드를 띠운다.
	if(haSiegeBoardFlag){
		BoardTime++;
		if(BoardTime>60*30){
			haSiegeBoardFlag = 0;
			SetCastleInit();
		}
	}
	//==================================================================//
	//                동영상 재생 메뉴
	//==================================================================//
	if(haMovieFlag){
		for(i=0;i<3;i++){
			if(haPlayerPosi[0][0]+i*34 < pCursorPos.x && haPlayerPosi[0][0]+haPlayerPosi[0][2]+i*34 > pCursorPos.x &&
				haPlayerPosi[0][1] < pCursorPos.y     && haPlayerPosi[0][1]+haPlayerPosi[0][3] > pCursorPos.y  ){
					haMovieKind  = i+1;
					break;
			}
			else if(haPlayerPosi[1][0] < pCursorPos.x && haPlayerPosi[1][0]+haPlayerPosi[1][2] > pCursorPos.x &&
					 haPlayerPosi[1][1] < pCursorPos.y&& haPlayerPosi[1][1]+haPlayerPosi[1][3] > pCursorPos.y  ){
					haMovieKind = 4;
					break;
			}
			else{
					haMovieKind = 0;
			}
		}
			
	}

}
/*----------------------------------------------------------------------------*
*		              그림을 그리다.
*-----------------------------------------------------------------------------*/
int   haStartTga=0;                //보드 그림시 사용돼는 임시 변수들
int   haTempScore[2]={0};
int	  haStartPosiX=0,haStartPosiY=100;
void cHASIEGE::Draw()
{
	
	int i,j;
	//==================================================================//
	//                  공성전 메뉴 설정
	//==================================================================//
	if(haSiegeMenuFlag){
		switch(haSiegeMenuKind){
			case HASIEGE_TAXRATES:   //세율 조정
				DrawSprite(SiegeButtonPosi[0][0],SiegeButtonPosi[0][1],lpSiegeTax ,0, 0, SiegeButtonPosi[0][2], SiegeButtonPosi[0][3], 1);  //세율 설정 메인
				DrawSprite(SiegeButtonPosi[4][0],SiegeButtonPosi[4][1],lpTax_Ok[0] ,0, 0, SiegeButtonPosi[4][2], SiegeButtonPosi[4][3], 1); //세금찾기버튼
				DrawSprite(SiegeIconPosi[5][0],SiegeIconPosi[5][1],lpTaxScroll[1] ,0, 0,SiegeIconPosi[5][2], SiegeIconPosi[5][3], 1);         //스크롤
				DrawSprite(SiegeIconPosi[0][0]-8,SiegeIconPosi[0][1],lpTaxScroll[0] ,0, 0, SiegeIconPosi[0][2],SiegeIconPosi[0][3], 1);         //스크롤
				DrawSprite(70+26,SiegeIconPosi[0][1]-10,lpTaxGraph ,0, 0, SiegeIconPosi[0][0]-(70+26), 10, 1);         //스크롤
				
			break;
			case HASIEGE_DEFENSE:    //방어 설정
				DrawSprite(SiegeButtonPosi[0][0],SiegeButtonPosi[0][1],lpSiegeDefense ,0, 0, SiegeButtonPosi[0][2], SiegeButtonPosi[0][3], 1); //방어 설정 메인
				DrawSprite(SiegeButtonPosi[0][0]+10,SiegeButtonPosi[0][1]+63,lpMercenary ,0, 0,248, 88, 1); //메뉴 박스
				
				//클랜스킬 표시	
				if(cSinSiege.ClanSkill){
					DrawSprite(SiegeIconPosi[2][0]+(cSinSiege.ClanSkill-1)*84,SiegeIconPosi[2][1],lpSiegeClanskillIcon[cSinSiege.ClanSkill-1] ,0, 0, SiegeIconPosi[2][2], SiegeIconPosi[2][3], 1);//   
				}
			
				//타워방어설정일 경우 (기본은 타워방어설정 )
				if(!haSiegeMerFlag){
					DrawSprite(SiegeButtonPosi[0][0]+10,SiegeButtonPosi[0][1]+43,lpCastleButton ,0, 0, 249, 22, 1); //성 메인
					for(i=0;i<3;i++){
						DrawSprite(SiegeIconPosi[1][0]+(i*82),SiegeIconPosi[1][1],lpSiegeDefeseIcon_[i] ,0, 0, SiegeIconPosi[1][2], SiegeIconPosi[1][3], 1);   
					}

					//성의 종류와 타워 타입표시
					for( i=0;i<6;i++){
						for( j=0;j<2;j++){
							if(cSinSiege.TowerTypeDraw[i][0]){
									//그림 보정
								if(cSinSiege.TowerTypeDraw[i][0]==1)
									DrawSprite(SiegeIconPosi[3][0]+2,SiegeIconPosi[3][1]-2,lpCastleIcon[i] ,0, 0,SiegeIconPosi[3][2], SiegeIconPosi[3][3], 1);   
								else if(cSinSiege.TowerTypeDraw[i][0]==3)
									DrawSprite(SiegeIconPosi[3][0]+80-1,SiegeIconPosi[3][1]-2,lpCastleIcon[i] ,0, 0,SiegeIconPosi[3][2], SiegeIconPosi[3][3], 1);   	
								else
									DrawSprite(SiegeIconPosi[3][0]+(cSinSiege.TowerTypeDraw[i][0]-1)*40,SiegeIconPosi[3][1]-2,lpCastleIcon[i] ,0, 0,SiegeIconPosi[3][2], SiegeIconPosi[3][3], 1);   
								

							    if(cSinSiege.TowerTypeDraw[i][1]){
									DrawSprite(SiegeIconPosi[1][0]+(cSinSiege.TowerTypeDraw[i][1]-1)*82,SiegeIconPosi[1][1],lpSiegeDefeseIcon[cSinSiege.TowerTypeDraw[i][1]-1] ,0, 0, SiegeIconPosi[1][2], SiegeIconPosi[1][3], 1);   
								}
							}			
					   	}
					}
				}
				//용병설정 일경우
				if(haSiegeMerFlag){
					for(i=0;i<3;i++){
						DrawSprite(SiegeIconPosi[1][0]+(i*82),SiegeIconPosi[1][1],lpSiegeMercenaryIcon_[i] ,0, 0, 30, 30, 1);
						if(cSinSiege.MercenaryNum[i]){
							DrawSprite(SiegeIconPosi[1][0]+i*82,SiegeIconPosi[1][1],lpSiegeMercenaryIcon[i] ,0, 0, SiegeIconPosi[1][2], SiegeIconPosi[1][3], 1);   	
						}
					}
					if(TowerIconIndex  > 0){
						DrawSprite(SiegeIconPosi[1][0]+(TowerIconIndex-1)*82,SiegeIconPosi[1][1],lpSiegeMercenaryIcon[TowerIconIndex-1] ,0, 0, SiegeIconPosi[1][2], SiegeIconPosi[1][3], 1);	
					}
				}
				if(!haSiegeMerFlag)//용병설정 / 방어설정 버튼 활성화
					DrawSprite(SiegeButtonPosi[5][0],SiegeButtonPosi[5][1],lpDefenseButton[1] ,0, 0, SiegeButtonPosi[5][2], SiegeButtonPosi[5][3], 1); //방어설정버튼
				else
					DrawSprite(SiegeButtonPosi[6][0],SiegeButtonPosi[6][1],lpDefenseButton[0] ,0, 0, SiegeButtonPosi[6][2], SiegeButtonPosi[6][3], 1); //용병설정버튼

				//정보박스를  보여준다.
   				if(TowerIconIndex > 0){
					if(TowerIconIndex>3){						//클랜스킬 정보박스를 띠운다.
						ClanSkillBoxPosi.x=SiegeIconPosi[2][0]+(TowerIconIndex-4)*84;
						ClanSkillBoxPosi.y=SiegeIconPosi[2][1]-96;
						ClanSkillBoxSize.x=11;
						ClanSkillBoxSize.y=6;
					}
					else if(TowerIconIndex<4 && haSiegeMerFlag){ //용병설정 정보 박스를 띠운다.
						ClanSkillBoxPosi.x=SiegeIconPosi[2][0]+(TowerIconIndex-1)*84;;
						ClanSkillBoxPosi.y=SiegeIconPosi[2][1]-216-20;
						ClanSkillBoxSize.x=15;
						ClanSkillBoxSize.y=7;
		
					}
					else{                                   //기본 설정 정보박스를 띠운다.
						ClanSkillBoxPosi.x=SiegeIconPosi[2][0]+(TowerIconIndex-1)*84;;
						ClanSkillBoxPosi.y=SiegeIconPosi[2][1]-216;
						ClanSkillBoxSize.x=15;
						ClanSkillBoxSize.y=6;
		
					}
					for(i = 0; i < ClanSkillBoxSize.x ; i++){
						for(int j = 0; j< ClanSkillBoxSize.y ; j++){
							if(i == 0 && j == 0 ) //좌측상단 
								dsDrawTexImage( cItem.MatItemInfoBox_TopLeft , ClanSkillBoxPosi.x+(i*16) , ClanSkillBoxPosi.y+(j*16), 16, 16 , 255 );
							if(j == 0 && i !=0 && i+1 < ClanSkillBoxSize.x ) //가운데
								dsDrawTexImage( cItem.MatItemInfoBox_TopCenter , ClanSkillBoxPosi.x+(i*16) , ClanSkillBoxPosi.y+(j*16), 16, 16 , 255 );
							if(j == 0 && i+1 == ClanSkillBoxSize.x) //우측상단
								dsDrawTexImage( cItem.MatItemInfoBox_TopRight , ClanSkillBoxPosi.x+(i*16) , ClanSkillBoxPosi.y+(j*16), 16, 16 , 255 );
							if(i == 0 && j != 0 && j+1 != ClanSkillBoxSize.y) //좌측 줄거리 
								dsDrawTexImage( cItem.MatItemInfoBox_Left , ClanSkillBoxPosi.x+(i*16) , ClanSkillBoxPosi.y+(j*16), 16, 16 , 255 );
							if(i != 0 && j != 0 && i+1 !=ClanSkillBoxSize.x && j+1 !=ClanSkillBoxSize.y) //가운데 토막
								dsDrawTexImage( cItem.MatItemInfoBox_Center , ClanSkillBoxPosi.x+(i*16) , ClanSkillBoxPosi.y+(j*16), 16, 16 , 255 );
							if(i+1 == ClanSkillBoxSize.x && j != 0 && j+1 != ClanSkillBoxSize.y) //우측 줄거리 
								dsDrawTexImage( cItem.MatItemInfoBox_Right , ClanSkillBoxPosi.x+(i*16) , ClanSkillBoxPosi.y+(j*16), 16, 16 , 255 );
							if(i == 0 && j+1 == ClanSkillBoxSize.y) //밑바닥 왼쪽
								dsDrawTexImage( cItem.MatItemInfoBox_BottomLeft , ClanSkillBoxPosi.x+(i*16) , ClanSkillBoxPosi.y+(j*16), 16, 16 , 255 );
							if(i != 0 && j+1 == ClanSkillBoxSize.y && i+1 !=ClanSkillBoxSize.x)//밑바닥 가운데
								dsDrawTexImage( cItem.MatItemInfoBox_BottomCenter , ClanSkillBoxPosi.x+(i*16) , ClanSkillBoxPosi.y+(j*16), 16, 16 , 255 );
							if(j+1 == ClanSkillBoxSize.y && i+1 ==ClanSkillBoxSize.x)//밑바닥 오른쪽 
								dsDrawTexImage( cItem.MatItemInfoBox_BottomRight , ClanSkillBoxPosi.x+(i*16) , ClanSkillBoxPosi.y+(j*16), 16, 16 , 255 );
						}
					}
				} 
				//선택된 창에 한에서 테두리를 보여준다.
			break;
		}
		switch(MenuButtonIndex){ //메뉴 버튼 관련 
			case 2:
				DrawSprite(SiegeButtonPosi[2][0],SiegeButtonPosi[2][1],lpSiegeOkButton,0, 0, SiegeButtonPosi[2][2], SiegeButtonPosi[2][3], 1);   
			break;
			case 3:
				DrawSprite(SiegeButtonPosi[3][0],SiegeButtonPosi[3][1],lpSiegeCancelButton ,0, 0, SiegeButtonPosi[3][2], SiegeButtonPosi[3][3], 1);   
			break;
			case 4:
				if(haSiegeMenuKind==HASIEGE_TAXRATES) //돈찾기 버튼을 활성화 시킨다.
					DrawSprite(SiegeButtonPosi[4][0],SiegeButtonPosi[4][1],lpSiegeOkButton ,0, 0, SiegeButtonPosi[4][2], SiegeButtonPosi[4][3], 1); //세금찾기버튼
			break;
			case 5:
				DrawSprite(SiegeButtonPosi[5][0],SiegeButtonPosi[5][1],lpDefenseButton[1] ,0, 0, SiegeButtonPosi[5][2], SiegeButtonPosi[5][3], 1); //방어설정버튼
			break;
			case 6:
				DrawSprite(SiegeButtonPosi[6][0],SiegeButtonPosi[6][1],lpDefenseButton[0] ,0, 0, SiegeButtonPosi[6][2], SiegeButtonPosi[6][3], 1); //용병설정버튼
			break;
			case 7:
				DrawSprite(SiegeButtonPosi[1][0],SiegeButtonPosi[1][1],lpSiegeDefenseButton ,0, 0,SiegeButtonPosi[1][2],SiegeButtonPosi[1][3], 1);//방어메인설정 버튼
			break;
			case 8:
				DrawSprite(SiegeButtonPosi[1][0],SiegeButtonPosi[1][1],lpSiegeTaxButton ,0, 0, SiegeButtonPosi[1][2], SiegeButtonPosi[1][3], 1);//재정메인설정 버튼
			break;
			
		}
	
	}
	//==================================================================//
	//                  공성전 보드 설정
	//==================================================================//	
	
	if(haSiegeBoardFlag){
		
		char  TempBuff[64];
		memset(&TempBuff,0,sizeof(TempBuff));

		if(rsBlessCastle.TimeSec[0] < 10){
			if(haStartPosiX < WinSizeX/2+256/2){
				haStartPosiX+=8+haStartPosiX/2;
				if(haAlpha < 255)
					haAlpha+=20;
				else
					haAlpha=255;
			}
			else{
				haStartPosiX = WinSizeX/2+256/2;
				if(haAlpha > 0)
					haAlpha-=5;
				else
					haAlpha=0;
			}
			dsDrawTexImage(haStartTga,haStartPosiX-256,haStartPosiY, 256, 64 , haAlpha );
		}
		
		DrawFontImage(ScoreBoardName[5],WinSizeX/2-200, 5,RGBA_MAKE(0,255,0,255),1.0f);   
		DrawFontImage(ScoreBoardName[4],WinSizeX/2-200,30,RGBA_MAKE(255,255,0,255),0.7f);
		DrawFontImage(ScoreBoardName[1],WinSizeX/2-200,49,RGBA_MAKE(255,255,0,255),0.7f); 
		
		DrawFontImage(ScoreBoardName[3],WinSizeX/2+20,7,RGBA_MAKE(100,100,255,255),0.8f);
		wsprintf(TempBuff,"%d:%d:%d",haPlayTime[2],haPlayTime[1],haPlayTime[0]);
		DrawFontImage(TempBuff,WinSizeX/2+115,7,RGBA_MAKE(100,100,255,255),0.8f);
		
		DrawFontImage(ScoreBoardName[0],WinSizeX/2-360,7,RGBA_MAKE(0,255,0,255),0.7f); 
		wsprintf(TempBuff,"%d",lpCurPlayer->sBlessCastle_Damage[1]);
		DrawFontImage(TempBuff,WinSizeX/2-240,7,RGBA_MAKE(200,0,0,255),0.7f);
		
		if(!haStartTga){
			haStartTga=CreateTextureMaterial("image\\Bellatra\\T_Start_278_65.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA); 
			ReadTextures();	//텍스쳐 로딩
		}
		
		for( i=0;i<10;i++){
			if(sHaClanData[i].Flag){
				if(GetClanCode(lpCurPlayer->smCharInfo.ClassClan) == sHaClanData[i].CLANCODE){
					wsprintf(TempBuff,"%d",sHaClanData[i].Score*100/haTotalDamage);
					if(haTempScore[0]==sHaClanData[i].Score*100/haTotalDamage)
						DrawFontImage(TempBuff,WinSizeX/2-100,30,RGBA_MAKE(255,255,0,255),0.8f);	
					else
						DrawFontImage(TempBuff,WinSizeX/2-100,29,RGBA_MAKE(255,0,0,255),0.8f);	
					haTempScore[0]=sHaClanData[i].Score*100/haTotalDamage;

					wsprintf(TempBuff,"%d",(int)lpCurPlayer->sBlessCastle_Damage[0]*100/sHaClanData[i].Score);
					if(haTempScore[1]==(int)lpCurPlayer->sBlessCastle_Damage[0]*100/sHaClanData[i].Score)
						DrawFontImage(TempBuff,WinSizeX/2-100,49,RGBA_MAKE(255,255,0,255),0.8f);
					else
						DrawFontImage(TempBuff,WinSizeX/2-100,48,RGBA_MAKE(255,0,0,255),0.8f);	
					haTempScore[1] = (int)lpCurPlayer->sBlessCastle_Damage[0]*100/sHaClanData[i].Score;
				}
			}
		}
		int TempCount=0;
		for(i=0;i<5;i++){
			if(sHaClanData[i].Flag){
				//디버그 모드일때
				if(smConfig.DebugMode){ 
					wsprintf(TempBuff,"%d",sHaClanData[i].Score);
					if(GetClanCode(lpCurPlayer->smCharInfo.ClassClan) == sHaClanData[i].CLANCODE){
						DrawFontImage(TempBuff,WinSizeX/2+120,30+i*17,RGBA_MAKE(255,255,0,255),0.6f);
					}	
					else{
						DrawFontImage(TempBuff,WinSizeX/2+120,30+i*17,RGBA_MAKE(255,128,0,255),0.6f);
					}
				}
				DrawSprite(WinSizeX/2+20,30+i*17,sHaClanData[i].lpClanMark,0, 0, 16, 16, 1); 
			}
			if(haCrystalTowerCount[i] && i<4){
				TempCount+= haCrystalTowerCount[i];
				if(lpTwoerImage==NULL){
					lpTwoerImage = LoadDibSurfaceOffscreen("image\\Sinimage\\Siege\\Tower_image.bmp");
				}			
			}
		}
		for(i=0;i<TempCount;i++){
			DrawSprite(WinSizeX/2-360+i*20,30,lpTwoerImage ,0, 0, 16, 32, 1);   
		}
	}
	//-----------------------------------------------------------------------------------/
	//              공성전 동영상 플레이어 그림
	//-----------------------------------------------------------------------------------/
	if(haMovieFlag){
		char szBuff[128];
		
		for(i = 0 ; i < 9 ; i++){
			wsprintf(szBuff,"Image\\SinImage\\Player\\ha_B%d.tga",i+1);
			if(haMatPlayMenu[i]==NULL){
				haMatPlayMenu[i] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
				ReadTextures();
			}
		}
		//int BoxSizeX=10,BoxSizeY=10;
		for(i=0;i<7;i++){
			dsDrawTexImage( haMatPlayMenu[1] ,26+64+(i*32), 70, 32, 64 , 255 );
			if(i<6){
				dsDrawTexImage( haMatPlayMenu[3] ,64+(8*32),70+64+(i*32), 32, 32 , 255 );
				dsDrawTexImage( haMatPlayMenu[7] ,40,70+64+(i*32), 32, 32 , 255 );
			}
			dsDrawTexImage( haMatPlayMenu[5] ,26+32+(i*32),70+64+(6*32), 64, 64 , 255 );
		}
		dsDrawTexImage( haMatPlayMenu[0],40, 70, 64, 64 , 255 );
		dsDrawTexImage(	haMatPlayMenu[2] ,64+(i*32),70,64,64,255 );
		dsDrawTexImage( haMatPlayMenu[4] ,64+(i*32),70+64+((i-1)*32), 64, 64 , 255 );
		dsDrawTexImage( haMatPlayMenu[6] ,40 ,70+64+((i-1)*32), 64, 64 , 255 );
		dsDrawTexImage( haMatPlayMenu[5] ,26+32+(8*32),70+64+(6*32), 18, 64 , 255 );

		for(i =0;i<3;i++){
			wsprintf(szBuff,"Image\\SinImage\\Player\\habox_0%d.bmp",i+1);
			if(haPlayerButtonBox[i]==NULL){
				haPlayerButtonBox[i] = LoadDibSurfaceOffscreen(szBuff);
			}
			wsprintf(szBuff,"Image\\SinImage\\Player\\ha_S%d_.bmp",i+1);
			if(haPlayerButton_G[i]==NULL){
				haPlayerButton_G[i] = LoadDibSurfaceOffscreen(szBuff);
			}
			wsprintf(szBuff,"Image\\SinImage\\Player\\ha_S%d.bmp",i+1);
			if(haPlayerButton[i]==NULL){
				haPlayerButton[i] = LoadDibSurfaceOffscreen(szBuff);
			}
			wsprintf(szBuff,"Image\\SinImage\\Player\\ha0%d.bmp",i+1);
			if(haPlayerButtonDown[i]==NULL){
				haPlayerButtonDown[i] = LoadDibSurfaceOffscreen(szBuff);
			}
			DrawSprite(haPlayerPosi[0][0]+(i*34),haPlayerPosi[0][1],haPlayerButton_G[i],0, 0,haPlayerPosi[0][2],haPlayerPosi[0][3], 1); 
			
		}
		DrawSprite(haPlayerPosi[0][0]+((ParkPlayMode/150)*34),haPlayerPosi[0][1],haPlayerButton[ParkPlayMode/150] ,0, 0,32,32, 1);   			
		DrawSprite(120,74 ,haPlayerButtonBox[0] ,0, 0,149,23, 1);   //
		DrawSprite(64,363 ,haPlayerButtonBox[1] ,0, 0,68 ,23, 1);
		DrawSprite(haPlayerPosi[1][0],haPlayerPosi[1][1],haPlayerButtonBox[2] ,0, 0,haPlayerPosi[1][2] ,haPlayerPosi[1][3], 1);
        DrawSprite(78,368,haPlayerButtonDown[2] ,0, 0,36,12, 1); 
		if(haMovieKind==4){
			DrawSprite(haPlayerPosi[1][0]+8,haPlayerPosi[1][1]+5,haPlayerButtonDown[0] ,0, 0,32,16, 1); 
		}
		else{
			DrawSprite(haPlayerPosi[1][0]+8,haPlayerPosi[1][1]+5,haPlayerButtonDown[1] ,0, 0,32,16, 1); 
		}
	

	}

}

/*----------------------------------------------------------------------------*
*		             서버에서 호출돼는 함수
*-----------------------------------------------------------------------------*/
//<ha>공성전 메뉴를 열어준다.
int cHASIEGE::ShowSiegeMenu(smTRANS_BLESSCASTLE *pData)
{	

	int i;
	//클랜칩 부클랜칩이 아닐경우 리턴
#ifdef _WINMODE_DEBUG
#else
	if(rsBlessCastle.dwMasterClan != GetClanCode(lpCurPlayer->smCharInfo.ClassClan))return TRUE;
#endif
	SendClanMoneyToServer(0,0,1);
	cSinSiege.ClanSkill = pData->ClanSkill;					  //클랜 스킬
	for(i=0;i<3;i++){
		cSinSiege.MercenaryNum[i] = pData->MercenaryNum[i];   //용병타입
	}
	for(i=0;i<6;i++){
		cSinSiege.TowerTypeDraw[i][0] = 0;
		cSinSiege.TowerTypeDraw[0][0] = 1;					  //내성 A를 활성화 시킨다.
		cSinSiege.TowerTypeDraw[i][1] = pData->Tower[i];      //성타입의 타워만 저장 
		
	}
 	ImageLoad();											  //이미지를 로드
	
	int Temp=0,Temp2=0;
	Temp  = (pData->TaxRate*22)+96;   
	Temp2 = (cSinSiege.TaxRate*22)+96-8;                      //현재 적용돼는 세율


	//현재의 세율을 세팅한다.
	SiegeIconPosi[0][0] = Temp-2;
	SiegeIconPosi[5][0] = Temp2-2;
	HaTaxRate = pData->TaxRate;

	
	//공성전 메뉴를 연다.
	haSiegeMenuFlag = 1;
	haSiegeMenuKind = HASIEGE_TAXRATES;//재정설정을 연다.
	
	return TRUE;
}
/*----------------------------------------------------------------------------*
*					  서버로부터 공성 점수를 받는다. 
*-----------------------------------------------------------------------------*/
int cHASIEGE::ShowSiegeScore(rsUSER_LIST_TOP10 *pData)
{
	int i;
	//클랜 정보를 받아서 저장한다.
	for(i=0;i<HACLAN_MAX ;i++){
		 if(pData->dwUserCode[i] && pData->Damage[i]){
			
			sHaClanData[i].CLANCODE = pData->dwUserCode[i];
			sHaClanData[i].Score    = pData->Damage[i];
			haTotalDamage           = pData->dwTotalDamage;									  
			sHaClanData[i].Flag     = 1; 

			sHaClanData[i].ClanInfoNum = ReadClanInfo(sHaClanData[i].CLANCODE);
			if(sHaClanData[i].ClanInfoNum >=0){
				lstrcpy(sHaClanData[i].ClanName , ClanInfo[sHaClanData[i].ClanInfoNum].ClanInfoHeader.ClanName);
				sHaClanData[i].lpClanMark = ClanInfo[sHaClanData[i].ClanInfoNum].hClanMark;
			}
		 }
	}
	//크리스탈 카운트 를 받는다.
	for(i=0;i<4;i++){
		haCrystalTowerCount[i] = pData->bCrystalTowerCount[i];
	}
	
	    
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						 <ha>공성전 종료 메세지를 보여준다.
*-----------------------------------------------------------------------------*/
int cHASIEGE::ShowExitMessage()
{
	//공성전 진행중 메세지
	haSiegeBoardFlag = 0;
	SetCastleInit();

	//승리와 패배 메세지
	if(rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->smCharInfo.ClassClan)){
		cSinHelp.sinShowHelp(SIN_HELP_KIND_C_TELEPORT,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, RGBA_MAKE(0,15,128,125),haC_CastleWinFilePath);  
	}
	else{
		cSinHelp.sinShowHelp(SIN_HELP_KIND_C_TELEPORT,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, RGBA_MAKE(0,15,128,125),haC_CastleLoseFilePath);  

	}
	return TRUE;	
}
/*----------------------------------------------------------------------------*
*			<ha>공성전 보드  초기화 함수
*-----------------------------------------------------------------------------*/
int cHASIEGE::SetCastleInit()
{
	for(int i=0;i<3;i++){
		haPlayTime[i]=0;
	}
	for ( int i = 0; i<HACLAN_MAX; i++ )
	{
		sHaClanData[i].CLANCODE=0;
		sHaClanData[i].Flag=0;
		sHaClanData[i].lpClanMark=0;
		sHaClanData[i].Score=0;
		
		if(i<4){
			haCrystalTowerCount[i]=0;
		}
	}
	BoardTime = 60*30;
	
	return TRUE;
}
/*----------------------------------------------------------------------------*
*			       플레이 타임 표시
*-----------------------------------------------------------------------------*/
int cHASIEGE::ShowPlayTime(int StartTime)
{
	if(StartTime==0){
		SetCastleInit();
		return TRUE;
	}
	//플레이 타임을 세팅한다.
	haPlayTime[0] = StartTime%60;     //초
	haPlayTime[1] = StartTime/60;
	haPlayTime[1]-= StartTime/3600*60;
	haPlayTime[2] = StartTime/3600;   //시간

	//1시간 간격으로 초기화 해준다.
	//if(StartTime%60*10 == 0){
	//	SetCastleInit();
	//}

	
	if(rsBlessCastle.TimeSec[1] > 0 ){
		haSiegeBoardFlag = 1;//초기화 해준다.
		BoardTime = 0;
	}
	else{
		haSiegeBoardFlag = 0;
		haStartPosiX = 0;
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*			<ha>
*-----------------------------------------------------------------------------*/
int cHASIEGE::ShowPickUserKillPoint(int x,int y,int KillCount)
{
	char TempBuff[32];
	memset(&TempBuff,0,sizeof(TempBuff));

	DrawFontImage(ScoreBoardName[2],x,y,RGBA_MAKE(0,255,0,255),0.7f);
	wsprintf(TempBuff,"%d",KillCount);
	DrawFontImage(TempBuff,x+24,y,RGBA_MAKE(255,0,0,255),0.7f);
	
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						 클랜스킬 관련
*-----------------------------------------------------------------------------*/
//클랜스킬이 있으면 세팅한다.
int cHASIEGE::SetClanSkill(int ClanSkill) 
{
	DWORD SkillCode;
	
	haClanSkillTime = 0;
	//초기화 
	switch(ClanSkill){
		case SIN_CLANSKILL_ABSORB:
			SkillCode = CLANSKILL_ABSORB;
		break;
		case SIN_CLANSKILL_DAMAGE:
			SkillCode = CLANSKILL_ATTACK;
		break;
		case SIN_CLANSKILL_EVASION:
			SkillCode = CLANSKILL_EVASION;
		break;
	}
    
	if(rsBlessCastle.dwMasterClan == GetClanCode(lpCurPlayer->smCharInfo.ClassClan)){
		if(cSkill.SearchContiueSkillCODE(SkillCode)==SkillCode){
			return TRUE;
		}
		else{
			cSkill.CancelContinueSkill(CLANSKILL_ATTACK);
			cSkill.CancelContinueSkill(CLANSKILL_EVASION);
			cSkill.CancelContinueSkill(CLANSKILL_ABSORB);	
		}
	}
	else{
		cSkill.CancelContinueSkill(CLANSKILL_ATTACK);
		cSkill.CancelContinueSkill(CLANSKILL_EVASION);
		cSkill.CancelContinueSkill(CLANSKILL_ABSORB);
		return TRUE;
	}

	//클랜원이 맞으면 클랜스킬을 세팅한다.
	sSKILL haClanSkill;
    
	for(int j = 0 ; j < SIN_MAX_SKILL; j++){
		if(sSkill[j].CODE == SkillCode){
			memcpy(&haClanSkill,&sSkill[j],sizeof(sSKILL));
		    haClanSkill.UseTime=60;
			sinContinueSkillSet(&haClanSkill);
			break;
		}
	}
	cInvenTory.SetItemToChar();
	
	return TRUE;
}
/*----------------------------------------------------------------------------*
*				 haGoon 공성전 전용 아이템을 사용한다.
*-----------------------------------------------------------------------------*/	
int haCastleSkillUseFlag =0;
int cHASIEGE::SetCastleItemSkill(int ItemKind)
{
	DWORD CastleSkillCode;
	int   CastleSkillUseTime=0;

	switch(ItemKind){
		case SIN_CASTLEITEMSKILL_S_INVU:
			CastleSkillCode = SCROLL_INVULNERABILITY;
			CastleSkillUseTime = 30;
		break;
		case SIN_CASTLEITEMSKILL_S_CRITICAL:
			CastleSkillCode = SCROLL_CRITICAL;
			CastleSkillUseTime = 30;
		break;
		case SIN_CASTLEITEMSKILL_S_EVASION:
			CastleSkillCode = SCROLL_EVASION;
			CastleSkillUseTime = 30;
		break;
		case SIN_CASTLEITEMSKILL_S_P_LIFE:
			CastleSkillCode = 0;
		break;
		case SIN_CASTLEITEMSKILL_S_RES:
			CastleSkillCode = 0;
		break;
		case SIN_CASTLEITEMSKILL_R_FIRE_C:
			CastleSkillCode = STONE_R_FIRECRYTAL;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_R_ICE_C:
			CastleSkillCode = STONE_R_ICECRYTAL;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_R_LIGHTING_C:
			CastleSkillCode = STONE_R_LINGHTINGCRYTAL;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_FIGHTER:
			CastleSkillCode = STONE_A_FIGHTER;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_MECHANICIAN:
			CastleSkillCode = STONE_A_MECHANICIAN;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_PIKEMAN:
			CastleSkillCode = STONE_A_PIKEMAN;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_ARCHER:
			CastleSkillCode = STONE_A_ARCHER;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_KNIGHT:
			CastleSkillCode = STONE_A_KNIGHT;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_ATALANTA:
			CastleSkillCode = STONE_A_ATALANTA;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_MAGICIAN:
			CastleSkillCode = STONE_A_MAGICIAN;
			CastleSkillUseTime = 60;
		break;
		case SIN_CASTLEITEMSKILL_A_PRIESTESS:
			CastleSkillCode = STONE_A_PRIESTESS;
			CastleSkillUseTime = 60;
		break;
	}
	//해당 돼는 아이템이 맞으면 아이템스킬을 세팅한다.
	sSKILL haCastleSkill;

    if(cSkill.SearchContiueSkillCODE(CastleSkillCode)==CastleSkillCode && CastleSkillCode != 0){
			cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
			haCastleSkillUseFlag = 0;
			return TRUE;
	}
	haCastleSkillUseFlag =1;
    if(CastleSkillCode==0)return TRUE; //유지형 아이콘을 띄어주지 않는 것은 리턴 시켜준다.  

	for(int j = 0 ; j < SIN_MAX_SKILL; j++){
		if(sSkill[j].CODE == CastleSkillCode){
			memcpy(&haCastleSkill,&sSkill[j],sizeof(sSKILL));
			haCastleSkill.UseTime=CastleSkillUseTime;
			sinContinueSkillSet(&haCastleSkill);
			SwitchSkill(&haCastleSkill);
			break;
		}
	}
	
	return TRUE;
}

/*----------------------------------------------------------------------------*
*						서버로 공성메뉴 데이타를 보낸다
*-----------------------------------------------------------------------------*/	
int cHASIEGE::SendServerSiegeData()
{
	int i;

	smTRANS_BLESSCASTLE TempBlessCastle;
	//TempBlessCastle 서버에 보낸다
	TempBlessCastle.TaxRate        = HaTaxRate;							//세율
	TempBlessCastle.ClanSkill      = cSinSiege.ClanSkill;				//클랜스킬
	TempBlessCastle.Price          = cSinSiege.Price;
	for(i=0;i<3;i++){
		TempBlessCastle.MercenaryNum[i]  = cSinSiege.MercenaryNum[i];   //용병
	}
	for(i=0;i<6;i++){
		TempBlessCastle.Tower[i] = cSinSiege.TowerTypeDraw[i][1];  //성타입의 타워만 저장 
	}

	SendBlessCastleToServer(&TempBlessCastle,0);//서버로 보내다.
	SaveGameData();
	return TRUE;
}


/*----------------------------------------------------------------------------*
*				메뉴 초기화를 해준다.
*-----------------------------------------------------------------------------*/
int cHASIEGE::SetCastleMenuInit()
{
	haSiegeMenuFlag=0;			 //메뉴를 닫아준다.
	haSiegeMenuKind=0;			 //메뉴종류를 초기화 해준다.
	haSiegeMerFlag=0;			 //용병 플랙을 초기화 해준다.
	SiegeIconPosi[0][0]=70+20-7; //스크롤은 다시 배치
    SiegeIconPosi[5][0]=70+20-7; //스크롤은 다시 배치

	return TRUE;	
}
/*----------------------------------------------------------------------------*
*						 키다운
*-----------------------------------------------------------------------------*/
void cHASIEGE::KeyDown()
{
	
}
/*----------------------------------------------------------------------------*
*						 LButtonDown/UP
*-----------------------------------------------------------------------------*/
void cHASIEGE::LButtonDown(int x,int y)
{

	int i;
	//==================================================================//
	//                  haGoon공성전 메뉴 설정
	//==================================================================//
	if(haSiegeMenuFlag){
		//클랜칩과 부클랜칩만이 변경  할수있다.
		if(cldata.myPosition == 101 ){
			if(GraphLineFlag){			//스크롤 
				if(SiegeIconPosi[0][0]-16  < pCursorPos.x && SiegeIconPosi[0][0]+SiegeIconPosi[0][2]+16> pCursorPos.x && SiegeIconPosi[0][1]-16< pCursorPos.y && SiegeIconPosi[0][1]+SiegeIconPosi[0][3]+16> pCursorPos.y ){
					ScrollButtonFlag=1;
				}
				else{
					SiegeIconPosi[0][0] = pCursorPos.x;
				}
			}
			if(CastleKindIndex){		//성의종류 인덱스를 넘겨준다.
				for( i=0;i<6;i++){
					if((CastleKindIndex-1)==i){
						cSinSiege.TowerTypeDraw[CastleKindIndex-1][0] = CastleKindIndex;//선택된 성의 종류만 활성화 시킨다.
					}
					else{
						cSinSiege.TowerTypeDraw[i][0] = 0;//선택돼지않은 성의 종류는 비활성화

					}
				}
			}
			if(TowerIconIndex){								  //현재 성의 타입에 속성타워를 넘겨준다.
				if(TowerIconIndex<4){
					if(haSiegeMerFlag){       				//용병설정
				   		haMercenrayIndex=TowerIconIndex;
						if(cSinSiege.MercenaryNum[haMercenrayIndex-1] < 20){
							cMessageBox.ShowMessage2(MESSAGE_SIEGE_SET_MERCENRAY);//확인창을 띠운다.
						}
					}
					else{                  //현재성의 종류에 타워 인덱스를 넘겨준다.
						for( i=0;i<6;i++){
							if(cSinSiege.TowerTypeDraw[i][0]){
								haSendTowerIndex=TowerIconIndex;
								if(cSinSiege.TowerTypeDraw[i][1]==0){
									switch(TowerIconIndex){
										case 1:
											cMessageBox.ShowMessage3(MESSAGE_CASTLE_BUYTOWER,"ICE");
										break;
										case 2:
											cMessageBox.ShowMessage3(MESSAGE_CASTLE_BUYTOWER,"LIGHTING");
										break;
										case 3:
											cMessageBox.ShowMessage3(MESSAGE_CASTLE_BUYTOWER,"FIRE");
										break;
									}
								}
								else{
									cSinSiege.TowerTypeDraw[i][1]=TowerIconIndex;
								}
							}
						}
					}
				}
				else{
					//현재 클랜 스킬에 클랜 인덱스를 넘겨준다.
					cSinSiege.ClanSkill = TowerIconIndex-3;
				}
			}
		}
		switch(MenuButtonIndex){				//메뉴 버튼 관련
			case 2:  
				if(cldata.myPosition == 101 ){
					SendServerSiegeData();		//메뉴정보를 저장한다.
					SetCastleMenuInit();	    //초기화
				}
			break;
			case 3: 
				SetCastleMenuInit();			//초기화
			break;
			case 4: //세금회수 버튼을 클릭하면 이 쪽으로 들어온다
				if(cldata.myPosition == 101 ){
					if(haSiegeMenuKind==HASIEGE_TAXRATES){
						//찾을 돈이 0이면 찾을수 없다.
						if((int)cSinSiege.TotalTax <= 0){
							cMessageBox.ShowMessage(MESSAGE_NOT_CASTLE_TOTALMONEY);
						}
						else{
							cMessageBox.ShowMessage2(MESSAGE_SIEGE_GET_MONEY);//돈을 찾다.
						}
					}
				}
			break;
			case 5: 
				haSiegeMerFlag =0;             //방어설정
			break;
			case 6: 
				haSiegeMerFlag =1;			   //용병설정
			break;
			case 7:
				haSiegeMenuKind=2;             //방어설정
			break;
			case 8:
				haSiegeMenuKind=1;             //재정설정
			break;
		}
	}
	//==================================================================//
	//         동영상 재생 메뉴버튼           
	//==================================================================//
	if(haMovieFlag){
		switch(haMovieKind){
			case 1:  //동영상 프레임 상
				ParkPlayMode = 0;
			break;
			case 2:  //중
				ParkPlayMode = 150;
			break;
			case 3:  //하
				ParkPlayMode = 300;
			break;
			case 4: //exit
				haMovieFlag = 0;
				Stop_ParkPlayer();
			break;
		}
	}

}
void cHASIEGE::LButtonUp(int x,int y)
{
	if(haSiegeMenuFlag){
		if(ScrollButtonFlag){ //스크롤을 죽여준다.
			ScrollButtonFlag=0;
		}
	}
}
/*----------------------------------------------------------------------------*
*						DrawText
*-----------------------------------------------------------------------------*/
void cHASIEGE::DrawText()
{
	HDC	hdc;
	renderDevice.lpDDSBack->GetDC(&hdc);
	SelectObject( hdc, sinFont); 
    SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, RGB(255,255,255) ); 

	char szTempBuff[128];
	char haTempBuffer[128];//임시 버퍼
	
	//==================================================================//
	//                  haGoon공성전 메뉴 설정
	//==================================================================//
	//공성전 설정을 보여준다.
	if(haSiegeMenuFlag){
		/*문자열을 출력한다*/
		int  TempCount =0;
		int  Skilllen=0;
		int  cnt=0,cnt1=0,cnt2=0;
		int  i=0,j=0;
		int  stringcut=18;      //문자열을 자를 크기

		int  LineCount[10]={0}; //10줄 까지의 정보를 저장한다.
		char TempBuffer[64];   //임시 버퍼
		int  Taxlen=0;          //세금총액의 길이를 구한다.
		
		switch(haSiegeMenuKind){
			case HASIEGE_TAXRATES: //재정 설정
				//현재 세율 (스크롤)
				HaTaxRate= SiegeIconPosi[0][0]-(73+24-9);
				HaTaxRate =HaTaxRate/22;
					
				SelectObject( hdc, sinBoldFont); 
				SetTextColor( hdc, RGB(100,200,200) );
				//세율
				wsprintf(szTempBuff,SiegeMessage_Taxrates[4],cSinSiege.TaxRate,"%");
				dsTextLineOut(hdc,97,112, szTempBuff, lstrlen(szTempBuff));

				wsprintf(szTempBuff,SiegeMessage_Taxrates[0],HaTaxRate,"%");
				dsTextLineOut(hdc,97,182, szTempBuff, lstrlen(szTempBuff));

				memset(szTempBuff,0,sizeof(szTempBuff));
				NumLineComa(cSinSiege.TotalTax, szTempBuff); //세금총액
				lstrcat(szTempBuff,SiegeMessage_Taxrates[2]);
				
				Taxlen=lstrlen(szTempBuff);
				dsTextLineOut(hdc,247-((Taxlen-8)*8),260, szTempBuff, lstrlen(szTempBuff));


				SelectObject( hdc, sinFont);
				SetTextColor( hdc, RGB(255,255,255) );
				wsprintf(szTempBuff,SiegeMessage_Taxrates[1]);  //세금 총액 
				dsTextLineOut(hdc,97,244, szTempBuff, lstrlen(szTempBuff));
				
				SetTextColor( hdc, RGB(255,255,255) );
				wsprintf(szTempBuff,SiegeMessage_Taxrates[3],HaTestMoney);
				dsTextLineOut(hdc,97,310, szTempBuff, lstrlen(szTempBuff));

			break;
			case HASIEGE_DEFENSE: //방어 설정
				
				int LinePosX = 0;
				int Linelen  = 0;
				int LineSetX = 0;
				
				/*----클랜스킬 정보를 보여주다.--------*/
				SelectObject( hdc, sinBoldFont); 
				SetBkMode( hdc, TRANSPARENT );
				SetTextColor( hdc, RGB(255,200,100) );
				//현재의 아이콘인덱스에 해당하는 스킬 정보를 보여준다.
				if(TowerIconIndex>3){
					for( i=0;i<160;i++){
						if(sSkill_Info[i].CODE == CLANSKILL_ABSORB  && TowerIconIndex-3== 1){
							TempCount=i;
							break;
						}
						if(sSkill_Info[i].CODE == CLANSKILL_ATTACK  && TowerIconIndex-3== 2){
							TempCount=i;
							break;
						}
						if(sSkill_Info[i].CODE == CLANSKILL_EVASION && TowerIconIndex-3== 3){
							TempCount=i;
							break;
						}
					}

					//스킬의 이름을 보여준다.
					wsprintf(szTempBuff,sSkill_Info[TempCount].SkillName); 
					LineSetX  = 4;
					Linelen   = lstrlen(szTempBuff);
					LinePosX  = (ClanSkillBoxSize.x*16-(Linelen*8))/2;
					
					LineSetX+=Linelen/8*5;
					
					dsTextLineOut(hdc,ClanSkillBoxPosi.x+LineSetX+LinePosX ,ClanSkillBoxPosi.y+20, szTempBuff, lstrlen(szTempBuff));
					
					
				 	SelectObject( hdc, sinFont); 
				 	SetTextColor( hdc, RGB(250,250,250) );
				
					Skilllen = lstrlen(sSkill_Info[TempCount].SkillDoc);
					lstrcpy(haTempBuffer,sSkill_Info[TempCount].SkillDoc);
					
					//띄어쓰기 돼있는 문자열을 자른다. 
					for(cnt=0;cnt<Skilllen;cnt++){
						if(cnt1*stringcut+stringcut > cnt)continue;
						if(haTempBuffer[cnt] == ' ' ){
							if(LineCount[cnt1]-cnt)
								LineCount[cnt1++]=cnt+1;
						}
					}
					//마지막엔 전체값을 넣어준다.
					LineCount[cnt1++]=Skilllen;

					
					//자른문자열만큼 보여준다.
					for(j=0;j<cnt1+1;j++){
						//다시 초기화 해준다.
						memset(TempBuffer,0,sizeof(TempBuffer));
						for(i=0;cnt2<LineCount[j*1];i++,cnt2++){
							TempBuffer[i]=haTempBuffer[cnt2];
						}
						//해당돼는 클랜스킬을 보여준다.
						lstrcpy(szTempBuff,TempBuffer);
						Linelen = lstrlen(szTempBuff);
						LineSetX=0;
						LineSetX+=Linelen/4*5;
						LinePosX = (ClanSkillBoxSize.x*16-(Linelen*8))/2;
						dsTextLineOut(hdc,ClanSkillBoxPosi.x+LineSetX+LinePosX,ClanSkillBoxPosi.y+40+j*18, szTempBuff, lstrlen(szTempBuff));
					}	
				}
				//타워설정/용병 설정을 보여주다.
				memset(TempBuffer,0,sizeof(TempBuffer));
				if(TowerIconIndex>0){
					cSinSiege.MercenaryNumDraw = cSinSiege.MercenaryNum[TowerIconIndex-1];
					for(i=0;i<5;i++){
						switch(TowerIconIndex){    //현재 타워/용병 종류
							case 1:
							   	if(haSiegeMerFlag){
									if(i==3){
										wsprintf(szTempBuff,SiegeMessage_MercenrayA[i],cSinSiege.MercenaryNumDraw);
									}
									else
										lstrcpy(szTempBuff,SiegeMessage_MercenrayA[i]);
								}
								else{
									if(i>3)break;
									lstrcpy(szTempBuff,SiegeMessage_TowerIce[i]);
								}
							break;
							case 2:
								if(haSiegeMerFlag){
									if(i==3){
										wsprintf(szTempBuff,SiegeMessage_MercenrayB[i],cSinSiege.MercenaryNumDraw);
									}
									else
										lstrcpy(szTempBuff,SiegeMessage_MercenrayB[i]);
								
								}
									
								else{
									if(i>3)break;
									lstrcpy(szTempBuff,SiegeMessage_TowerLighting[i]);
								}
							break;
							case 3:
								if(haSiegeMerFlag){
									if(i==3){
										wsprintf(szTempBuff,SiegeMessage_MercenrayC[i],cSinSiege.MercenaryNumDraw);
									}
									else
										lstrcpy(szTempBuff,SiegeMessage_MercenrayC[i]);
								}
								else{
									if(i>3)break;
									lstrcpy(szTempBuff,SiegeMessage_TowerFire[i]);
								}
							break;
						}
						//현재성의 종류를 얻어온다.
						int TempIndex=0;
						int TempIconIndex[3]={0};
						for(int k=0;k<6;k++){
							if(cSinSiege.TowerTypeDraw[k][0]){
								TempIndex = cSinSiege.TowerTypeDraw[k][0];
								break;
							}	
						}
						if(TowerIconIndex){
							if(cSinSiege.MercenaryNum[TowerIconIndex-1]){
								TempIconIndex[TowerIconIndex-1]=cSinSiege.MercenaryNum[TowerIconIndex-1];
							}
						}

						SelectObject( hdc, sinBoldFont);
						LineSetX  = 4;	
						Linelen   = lstrlen(szTempBuff);
						LinePosX  = (ClanSkillBoxSize.x*16-(Linelen*8))/2;
						LineSetX+= Linelen/8*5;
	
						//텍스트 표시
						if(i==0){								               //이름
							SetTextColor( hdc, RGB(100,100,200));
						}
						else if(i==3 && cSinSiege.TowerTypeDraw[TempIndex-1][1]==TowerIconIndex && !haSiegeMerFlag){ //타워설정
							SetTextColor( hdc, RGB(200,200,100));
						}
						else if(i==4 && haSiegeMerFlag && cSinSiege.MercenaryNumDraw == 20){
							SetTextColor( hdc, RGB(200,200,100));
			
						}
						else{                                                  //기본
							SelectObject( hdc, sinFont);
							SetTextColor( hdc, RGB(250,250,250));
							Linelen = lstrlen(szTempBuff);
						    LineSetX=-4;
						    LineSetX+=Linelen/4*5;
						    LinePosX = (ClanSkillBoxSize.x*16-(Linelen*8))/2;
				
						}
						char TempBuff[32];
						
						memset(&TempBuff,0,sizeof(TempBuff));

					    switch(i){
							case 0:   //이름
								dsTextLineOut(hdc,ClanSkillBoxPosi.x+LineSetX+LinePosX ,ClanSkillBoxPosi.y+14, szTempBuff, lstrlen(szTempBuff));
							break;
							case 1:
							case 2:   //내용
							case 3:
								if(cSinSiege.TowerTypeDraw[TempIndex-1][1]==TowerIconIndex && !haSiegeMerFlag){
									dsTextLineOut(hdc,ClanSkillBoxPosi.x+LineSetX+LinePosX,ClanSkillBoxPosi.y+20+i*18, szTempBuff, lstrlen(szTempBuff));	
								}
								if(cSinSiege.TowerTypeDraw[TempIndex-1][1]==0 && !haSiegeMerFlag && i==3 && TowerIconIndex<4){
									lstrcpy(szTempBuff,SiegeMessage_TowerMoney);
									NumLineComa(haTowerMoney,TempBuff);
									lstrcat(szTempBuff,TempBuff);
									lstrcat(szTempBuff,Won);
									
									Linelen = lstrlen(szTempBuff);
									LineSetX=-4;
									LineSetX+=Linelen/4*5;
									LinePosX = (ClanSkillBoxSize.x*16-(Linelen*8))/2;
									dsTextLineOut(hdc,ClanSkillBoxPosi.x+LineSetX+LinePosX,ClanSkillBoxPosi.y+20+i*18, szTempBuff, lstrlen(szTempBuff));	
			
								}
								if(i==3&&haSiegeMerFlag){
									dsTextLineOut(hdc,ClanSkillBoxPosi.x+LineSetX+LinePosX,ClanSkillBoxPosi.y+20+i*18, szTempBuff, lstrlen(szTempBuff));
								}
								else{
									dsTextLineOut(hdc,ClanSkillBoxPosi.x+LineSetX+LinePosX,ClanSkillBoxPosi.y+20+i*18, szTempBuff, lstrlen(szTempBuff));
								}
							break;
							case 4:
								if(!haSiegeMerFlag || TowerIconIndex >3) break;
								//용병 가격 표시
								if(haSiegeMerFlag && cSinSiege.MercenaryNumDraw < 20){	
									lstrcpy(szTempBuff,SiegeMessage_MerMoney);
									NumLineComa(haMercenrayMoney[TowerIconIndex-1],TempBuff);
									lstrcat(szTempBuff,TempBuff);
									lstrcat(szTempBuff,Won);
								}
								else{
									lstrcpy(szTempBuff,SiegeMessage_MerComplete); //용병설정 완료
								}
								Linelen = lstrlen(szTempBuff);
								LineSetX=-4;
								LineSetX+=Linelen/4*5;
								LinePosX = (ClanSkillBoxSize.x*16-(Linelen*8))/2;
								dsTextLineOut(hdc,ClanSkillBoxPosi.x+LineSetX+LinePosX,ClanSkillBoxPosi.y+20+i*18, szTempBuff, lstrlen(szTempBuff));	
			
						    break;
						}
					}
				}//if(TowerIconIndex>0){ 종료
				break;
		}//haSiegeMenuKind
	}//haSiegeMenuFlag
	//==================================================================//
	//                  공성전 보드 설정
	//==================================================================//
	//공성전 보드에 데이타를 보여준다.
	if(haSiegeBoardFlag){
		SelectObject( hdc, sinBoldFont); 
		for(int i=0;i<5 ;i++){
			if(sHaClanData[i].Flag ){
				if(sHaClanData[i].ClanInfoNum >=0){
					if(sinChar->ClassClan == sHaClanData[i].CLANCODE){
					    SetTextColor( hdc, RGB(200,200,0));
					}
					else{
					    SetTextColor( hdc, RGB(200,128,0));
					}
					lstrcpy(szTempBuff,sHaClanData[i].ClanName);
					dsTextLineOut(hdc,WinSizeX/2+40,32+i*17,szTempBuff, lstrlen(szTempBuff));
				}
			}
		}
	}
	//==================================================================//
	//                  공성전 동영상 플레이를 보여준다.
	//==================================================================//
	if(haMovieFlag){
		SelectObject( hdc, sinBoldFont); 
		SetTextColor( hdc, RGB(255,255,255));
		dsTextLineOut(hdc,152,80,haMovieName, lstrlen(haMovieName));
	}
	
	renderDevice.lpDDSBack->ReleaseDC(hdc);
}

/*----------------------------------------------------------------------------*
*						 Class cSINSIEGE
*-----------------------------------------------------------------------------*/	
int cSINSIEGE::GetTaxRate()
{	
	return TaxRate;
}
int cSINSIEGE::SetTaxRate(int TempTaxRate)
{
	TaxRate = TempTaxRate;
	return TRUE;
}

int cSINSIEGE::GetTotalTax()
{
	//서버에 클랜머니금액 정보를 요구한다
	//TotalTax = getSiegeClanMoneyToServer(0,0); 대략
	return TotalTax;
}
int cSINSIEGE::GetTaxMoney(int Money )
{
	//찾고싶은 만큼의 돈을 요구한다
	return TRUE;
}

/*----------------------------------------------------------------------------*
*					공성전 동영상 플레이를 보여준다.
*-----------------------------------------------------------------------------*/	
int cHASIEGE::ShowCastlePlayMovie(char *szPath,char *TitleName,int Option)
{

	memset(haMovieName ,0,sizeof(haMovieName));
	lstrcpy(haMovieName,TitleName);

	haMovieFlag = 1;  //플랙을 열어준다.

	if(haMovieFlag){ 
		Play_ParkPlayer( szPath ,42,100, 307,260 ,150);
	}
	return TRUE;
}





