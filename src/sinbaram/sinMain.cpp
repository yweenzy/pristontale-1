/*----------------------------------------------------------------------------*
*	파일명 :  sinMain.cpp 
*	하는일 :  신바람 메인 
*	작성일 :  최종업데이트 12월 
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#define _SINBARAM_TEST   //빌드시에는 항상 꺼준다 

#include "sinLinkHeader.h"

/*----------------------------------------------------------------------------*
*					         전역 변수 
*-----------------------------------------------------------------------------*/

smCHAR_INFO *sinChar;		 //캐릭터 정보 구조체 
smCHAR_INFO sinCharDisplay;  //캐릭터 정보 구조체 
int sinbaram_Stop = 0;


/////////////////////////
/*----------------------------------------------------------------------------*
*						  게임을 초기화한다	
*-----------------------------------------------------------------------------*/	
void sinInit()
{

	InitSub();					//서브메인 초기화 
	InitCursor();				//커서 이미지를 초기화한다 
	cItem.Init();				//아이템 초기화
	cSkill.Init();				//스킬창 초기화 
	cInvenTory.Init();			//인벤토리 초기화 
	cCharStatus.Init();			//캐릭터스테이터스 초기화 
	cInterFace.Init();			//인터페이스 초기화 
	cShop.Init();				//상점 초기화 
	cTrade.Init();
	cMessageBox.Init();			//메세지 박스 초기화 
	cSin3D.Init();				//신바람 3D
	cSinHelp.Init();			//신바람 도우미 초기화
	cSinWarpGate.Init();
	g_CreatePetSystem();
	cHelpPet.Init();
	cSinSod2.Init();
	
	// PC방 펫생성  박철호!!
	g_PCBang_CreatePetSystem(); 
	cPCBANGPet.Init();         


	//하군.. 
	chaSiege.init();
	chaQuest.init();
	chaPremiumitem.init();


	//ktj : 웹db용 임시설정함수.  =============================== start
	void web_DB_start();		//이전에 이미하기 때문에 안함.
	//web_DB_start();
	//ktj : 임시로 넣은것.
	void clanMENU_INIT(int setN);
	clanMENU_INIT(1);				//2번째 init
	//clanMENU_INIT(-1);			//이것은 임시
	//=========================================================== end


}
/*----------------------------------------------------------------------------*
*							 게임 메인(70프레임)							  *
*-----------------------------------------------------------------------------*/	
DWORD dwSinTime = 0;
void sinMain()
{

	sinMouseMain();				//마우스 클릭을 한번만 체크한다 
	sinKeyClickMain();			//키입력을 한번으로 제한한다 

//	sinProc(SINKEYDOWN);		//키입력이 있을때 	

	if(sinGetMouseButton(0) == TRUE)
			sinProc(SINLBUTTONDOWN);  //마우스 왼쪽 버튼  다운했을때 이벤트 
	if(sinGetMouseButton(1) == TRUE)	
			sinProc(SINRBUTTONDOWN);  //마우스 오른쪽 버튼 다운했을때 이벤트 

	if(MouseButtonUpEvent == SINLBUTTONUP){
		sinProc(SINLBUTTONUP);
		MouseButtonUpEvent = 0; //버튼 Up이벤트 초기화 

	}

	if(MouseButtonUpEvent == SINRBUTTONUP){
		sinProc(SINRBUTTONUP);
		MouseButtonUpEvent = 0; //버튼 Up이벤트 초기화 

	}

	sinProc(SINMOUSEMOVE);      //마우스를 움직였을때 

	
	MainSub();
	cItem.Main();
	cInterFace.Main();
	cSkill.Main();
	cInvenTory.Main();
	cCharStatus.Main();
	cShop.Main();
	cTrade.Main();
	cMessageBox.Main();
	//cSin3D.Main(); 우동동 호출 ioi
	cSinHelp.Main();
	cSinWarpGate.Main();
	cHelpPet.Main();
	cSinSod2.Main();

	//하군.. 
	chaSiege.Main();
	chaQuest.Main();
	chaPremiumitem.Main();

	//ktj : 임시로 넣은것.
	void ktj_imsi_clanMENU_Main();
	ktj_imsi_clanMENU_Main();

	ShowInterFace(); //각종 인터페이스를 보여준다 

	//박철호 : 2005-11-21 오후 8:59:05
	cPCBANGPet.Main();



	////// 이벤트를 정지해놓은것을 시간이 지나면 활성화해준다
	if(sinbaram_Stop){
		dwSinTime++;
		if(dwSinTime >= 3*70) sinbaram_Stop = 0;
	}
	else dwSinTime = 0;

}
/*----------------------------------------------------------------------------*
*							 이미지를 그린다 								  *
*-----------------------------------------------------------------------------*/
void sinDraw()
{
	
	renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

	renderDevice.BeginScene();
	DrawSub();
	renderDevice.EndScene();
	dsDrawOffsetArray = dsARRAY_BOTTOM;

	///////////캐릭터 스테이터스 
	renderDevice.BeginScene();
	cCharStatus.Draw();
	renderDevice.EndScene();
	cCharStatus.DrawCharText();  


	dsDrawOffsetArray = dsARRAY_TOP;
	//프리미엄 서비스 아이템
	renderDevice.BeginScene();
	chaPremiumitem.DrawUp();
	renderDevice.EndScene();


	dsDrawOffsetArray = dsARRAY_BOTTOM;

	///////////스킬 
	renderDevice.BeginScene();
	cSkill.Draw();			 
	renderDevice.EndScene();

	dsDrawOffsetArray = dsARRAY_TOP;
	renderDevice.BeginScene();
	cSkill.DrawUp();
	renderDevice.EndScene();
	

	dsDrawOffsetArray = dsARRAY_BOTTOM;
	///////////인벤토리 
	renderDevice.BeginScene();
	cInvenTory.Draw();		
	renderDevice.EndScene();
	cInvenTory.DrawInvenText();   
	
	dsDrawOffsetArray = dsARRAY_TOP;

	///////////상점 
	
	renderDevice.BeginScene();
	cShop.Draw();			
	renderDevice.EndScene();
	cShop.DrawShopText(); 
	
	
	///////////트레이드 
	renderDevice.BeginScene();
	cTrade.Draw();			
	renderDevice.EndScene();
	cTrade.DrawTradeText();


	dsDrawOffsetArray = dsARRAY_BOTTOM;	
	///////////인터페이스
	renderDevice.BeginScene();
	cInterFace.Draw();		
	renderDevice.EndScene();
	cInterFace.DrawInterText();
	
	///////////아이템 
	renderDevice.BeginScene();
	cItem.Draw();			
	renderDevice.EndScene();
	cItem.DrawItemText();          


	dsDrawOffsetArray = dsARRAY_TOP;
	///////////신바람 도우미 
	renderDevice.BeginScene();
	cSinHelp.Draw();
	renderDevice.EndScene();
	cSinHelp.DrawText();

	///////////신바람 위프게이트
	renderDevice.BeginScene();
	cSinWarpGate.Draw();
	renderDevice.EndScene();
	cSinWarpGate.DrawText();

	///////////인터페이스 이펙트 
	sinDrawInterEffect();

	//ktj :임시
	dsDrawOffsetArray = dsARRAY_TOP;
	void ktj_imsi_clanMENU_Draw();
	ktj_imsi_clanMENU_Draw();



	//DrawMenuFlame(); //함수 안에서 BeginScene 과 EndScene을 한다 
	
	
	dsDrawOffsetArray = dsARRAY_BOTTOM;

	
	//텍스트는 렌더링한후 찍어준다 
	sinDrawText();

	dsDrawOffsetArray = dsARRAY_TOP;
	///////////신바람 도우미 펫
	renderDevice.BeginScene();
	cHelpPet.Draw(); 
	renderDevice.EndScene();
	cHelpPet.DrawText();


	//신바람 Sod2
	renderDevice.BeginScene();
	cSinSod2.Draw(); 
	renderDevice.EndScene();
	cSinSod2.DrawText();

	//공성전  
	renderDevice.BeginScene();
	chaSiege.Draw();		
	renderDevice.EndScene();
	chaSiege.DrawText();

	//퀘스트  
	renderDevice.BeginScene();
	chaQuest.Draw();
	renderDevice.EndScene();

	//프리미엄 서비스 아이템
	renderDevice.BeginScene();
	chaPremiumitem.Draw();
	renderDevice.EndScene();
	chaPremiumitem.DrawText();


	///////////메세지 박스 
	renderDevice.BeginScene();
	cMessageBox.Draw();		
	renderDevice.EndScene();
	cMessageBox.DrawMessageText();

	dsDrawOffsetArray = dsARRAY_TOP;

	if (renderDevice.IsDevice())
	{
		renderDevice.BeginScene();
		DrawCursor();
		renderDevice.EndScene();
	}	
}

//텍스트를 찍어준다
void sinDrawText()
{

	cSkill.DrawSkillText();		   	
	sinTestDrawText();             //테스트 메세지 
	EffectTestDrawText();		   //이펙트 테스트 DrawTest;
	EffectTestDrawText2();
/*
	HDC	hdc;
	lpDDSBack->GetDC( &hdc );
	SelectObject( hdc, sinFont);
    SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, RGB(255,255,255) );
	if(smConfig.DebugMode){
		dsTextLineOut(hdc,0,0,"i",1);
	}
	lpDDSBack->ReleaseDC( hdc );
*/

}
/*----------------------------------------------------------------------------*
*			마우스다운  , 키입력  , 마우스 무브등의 메세지를 받는다 
*-----------------------------------------------------------------------------*/	
void sinProc(int Message)
{

	switch(Message)
	{ 
	case SINLBUTTONDOWN:
		if(sinbaram_Stop)return; 
		cInvenTory.CheckMousePotionNumForm();               //마우스 물약을체크하고
		cMessageBox.LButtonDown(pCursorPos.x,pCursorPos.y); //메세지 박스
		cSinSod2.LButtonDown(pCursorPos.x,pCursorPos.y);    //신바람 Sod2
		if(sinMessageBoxShowFlag && !MyShopExpBox && !nName )return;   //홍보문구 입력때문에 날치기 땜빵 ㅠ.ㅠ 크흑 // 장별 - 입력창
		cInterFace.LButtonDown(pCursorPos.x,pCursorPos.y);  //인터페이스 
		cCharStatus.LButtonDown(pCursorPos.x,pCursorPos.y); //캐릭터 스테이터스 
		cInvenTory.LButtonDown(pCursorPos.x,pCursorPos.y);  //인벤토리 
		cSkill.LButtonDown(pCursorPos.x,pCursorPos.y);      //스킬 
		cTrade.LButtonDown(pCursorPos.x,pCursorPos.y);      //트레이드 
		cItem.LButtonDown(pCursorPos.x,pCursorPos.y);       //아이템 
		cShop.LButtonDown(pCursorPos.x,pCursorPos.y);       //상점 
		cSin3D.LButtonDown(pCursorPos.x,pCursorPos.y);      //신바람 3D
		cSinHelp.LButtonDown(pCursorPos.x,pCursorPos.y);    //신바람 도우미
		cSinWarpGate.LButtonDown(pCursorPos.x,pCursorPos.y);//신바람 워프게이트
		cHelpPet.LButtonDown(pCursorPos.x,pCursorPos.y);    //신바람 펫 도우미
		cInvenTory.ReFormMousePotionNum();                  //인증해준다 

		//하군.. 
		chaSiege.LButtonDown(pCursorPos.x,pCursorPos.y);
		chaQuest.LButtonDown(pCursorPos.x,pCursorPos.y);
		chaPremiumitem.LButtonDown(pCursorPos.x,pCursorPos.y);
	break;
	case SINLBUTTONUP:
		if(sinbaram_Stop)return;
		cMessageBox.LButtonUp(pCursorPos.x,pCursorPos.y);   //메세지 박스 
		if(sinMessageBoxShowFlag)return;
		cInterFace.LButtonUp(pCursorPos.x,pCursorPos.y);    //인터페이스 
		cCharStatus.LButtonUp(pCursorPos.x,pCursorPos.y);   //캐릭터 스테이터스 
		cInvenTory.LButtonUp(pCursorPos.x,pCursorPos.y);    //인벤토리 
		cShop.LButtonUp(pCursorPos.x,pCursorPos.y);		    //상점 
		cSkill.LButtonUp(pCursorPos.x,pCursorPos.y);	    //스킬 
		cTrade.LButtonUp(pCursorPos.x,pCursorPos.y);	    //트레이드 
		cSin3D.LButtonUp(pCursorPos.x,pCursorPos.y);        //신바람 3D
		cSinHelp.LButtonUp(pCursorPos.x,pCursorPos.y);      //신바람 도우미
		cSinWarpGate.LButtonUp(pCursorPos.x,pCursorPos.y);  //신바람 워프게이트
		cHelpPet.LButtonUp(pCursorPos.x,pCursorPos.y);      //신바람 펫 도우미
		cSinSod2.LButtonUp(pCursorPos.x,pCursorPos.y);      //신바람 Sod2
		//공성전 테스트
		chaSiege.LButtonUp(pCursorPos.x,pCursorPos.y);
	break;

	case SINRBUTTONDOWN:
		if(MyShopSendButton)return;
		if(sinbaram_Stop)return;
		cMessageBox.RButtonDown(pCursorPos.x,pCursorPos.y); //메세지 박스 
		if(sinMessageBoxShowFlag)return;
		cInterFace.RButtonDown(pCursorPos.x,pCursorPos.y);  //인터페이스 
		cCharStatus.RButtonDown(pCursorPos.x,pCursorPos.y); //캐릭터 스테이터스 
		cShop.RButtonDown(pCursorPos.x,pCursorPos.y);       //상점 
		cInvenTory.RButtonDown(pCursorPos.x,pCursorPos.y);  //인벤토리 
		cSkill.RButtonDown(pCursorPos.x,pCursorPos.y);      //스킬 
		cTrade.RButtonDown(pCursorPos.x,pCursorPos.y);      //트레이드 
		cItem.RButtonDown(pCursorPos.x,pCursorPos.y);       //아이템 
		cSin3D.RButtonDown(pCursorPos.x,pCursorPos.y);      //신바람 3D
		cSinHelp.RButtonDown(pCursorPos.x,pCursorPos.y);    //신바람 도우미
		cSinWarpGate.RButtonDown(pCursorPos.x,pCursorPos.y);//신바람 워프게이트
		cHelpPet.RButtonDown(pCursorPos.x,pCursorPos.y);    //신바람 펫 도우미
		cSinSod2.RButtonDown(pCursorPos.x,pCursorPos.y);    //신바람 Sod2

	break;

	case SINRBUTTONUP:
		if(sinbaram_Stop)return;
		cMessageBox.RButtonUp(pCursorPos.x,pCursorPos.y);   //메세지 박스 
		if(sinMessageBoxShowFlag)return;		
		cInterFace.RButtonUp(pCursorPos.x,pCursorPos.y);    //인터페이스 
		cCharStatus.RButtonUp(pCursorPos.x,pCursorPos.y);   //캐릭터 스테이터스 
		cInvenTory.RButtonUp(pCursorPos.x,pCursorPos.y);    //인벤토리 
		cShop.RButtonUp(pCursorPos.x,pCursorPos.y);		    //상점 
		cSkill.RButtonUp(pCursorPos.x,pCursorPos.y);	    //스킬 
		cTrade.RButtonUp(pCursorPos.x,pCursorPos.y);	    //트레이드 
		cMessageBox.RButtonUp(pCursorPos.x,pCursorPos.y);   //메세지 박스 
		cSin3D.RButtonUp(pCursorPos.x,pCursorPos.y);        //신바람 3D
		cSinHelp.RButtonUp(pCursorPos.x,pCursorPos.y);      //신바람 도우미
		cSinWarpGate.RButtonUp(pCursorPos.x,pCursorPos.y);  //신바람 워프게이트
		cHelpPet.RButtonUp(pCursorPos.x,pCursorPos.y);		//신바람 펫 도우미
		cSinSod2.RButtonUp(pCursorPos.x,pCursorPos.y);		//신바람 Sod2
	break;

	case SINMOUSEMOVE:

	break;
	
	case SINKEYDOWN:
		if(sinbaram_Stop)return;
		cMessageBox.KeyDown();   //메세지 박스 
		if(sinMessageBoxShowFlag)return;

		cInterFace.KeyDown();    //인터페이스 
		cCharStatus.KeyDown();   //캐릭터 스테이터스 
		cInvenTory.KeyDown();    //인벤토리 
		cShop.KeyDown();		 //상점 
		cSkill.KeyDown();	     //스킬 
		cTrade.KeyDown();	     //트레이드 
		cSin3D.KeyDown();		 //신바람 3D 
		cSinHelp.KeyDown();		 //신바람 도우미
		cSinWarpGate.KeyDown();  //신바람 워프게이트
		cHelpPet.KeyDown();      //신바람 키다운
		cSinSod2.KeyDown();		 //신바람 Sod2
		chaSiege.KeyDown();

		

		/////////////////////////////펑션 키 
		if(sinGetKeyClick('X')){
			cHelpPet.PetMessage("*System",3);
			if(!ExitButtonClick)ExitButtonClick =1;
			else ExitButtonClick = 0;
			cInterFace.CheckAllBox(SIN_SYSTEM); //창을 하나만 띄운다 
		}
		if(sinGetKeyClick('R')){
			cHelpPet.PetMessage("*RunAndWalk",3);
			if(cInterFace.sInterFlags.RunFlag)cInterFace.sInterFlags.RunFlag = 0;
			else cInterFace.sInterFlags.RunFlag =1;
		}
		if(sinGetKeyClick(VK_TAB)){
			cHelpPet.PetMessage("*Mini_Map",3);
			if(cInterFace.sInterFlags.MapOnFlag)cInterFace.sInterFlags.MapOnFlag = 0;
			else cInterFace.sInterFlags.MapOnFlag = 1;
		}
		if(sinGetKeyClick('Z')){
			cInterFace.sInterFlags.CameraAutoFlag++;
			if(cInterFace.sInterFlags.CameraAutoFlag > 2)cInterFace.sInterFlags.CameraAutoFlag = 0;

		}
		if(sinGetKeyClick('D')){
			cHelpPet.PetMessage("*Party",3);
			ShowParty();
		}
		if(sinGetKeyClick('Q')){
			cHelpPet.PetMessage("*Quest",3);
			ShowQuest();
		}

		if(sinGetKeyClick(VK_SPACE)){ //창을 닫아준다 
			cMessageBox.CloseMessage();
			if(!cCraftItem.OpenFlag && !cAging.OpenFlag && !SmeltingItem.OpenFlag && !ManufactureItem.m_OpenFlag || !cMixtureReset.OpenFlag) //에이징과 믹스아이템이 닫혀있을때만 ESC가 먹는다 // 석지용 - 믹스쳐 리셋 창 추가
				cInterFace.CheckAllBox(SIN_ALL_CLOSE); //창을 다 닫아준다 

		}
		if(smConfig.DebugMode){ // 수치를 보기위한 테스트 키    
			if(sinGetKeyClick('T') && sinGetKeyClick(VK_CONTROL) ){
				if(sinTestFlag)sinTestFlag = 0;
				else sinTestFlag = 1;
			}

			if(sinGetKeyClick('F') && sinGetKeyClick(VK_CONTROL) ){ //가짜 상점  
				if(cShop.OpenFlag == SIN_CLOSE)cShop.OpenFlag = SIN_OPEN; 
				else cShop.OpenFlag = SIN_CLOSE;
			
			}
			if(sinGetKeyClick('G') && sinGetKeyClick(VK_CONTROL) ){ //가짜 조합 
				if(cCraftItem.OpenFlag== SIN_CLOSE)cCraftItem.OpenFlag = SIN_OPEN; 
				else cCraftItem.OpenFlag = SIN_CLOSE;
			}
			if(sinGetKeyClick('H') && sinGetKeyClick(VK_CONTROL) ){ //가짜 에이징 
				if(cCraftItem.ForceFlag== SIN_CLOSE)cCraftItem.ForceFlag = SIN_OPEN; 
				else cCraftItem.ForceFlag = SIN_CLOSE;
			}
			//if(sinGetKeyClick('J') && sinGetKeyClick(VK_CONTROL) ){ //가짜 창고 
			//	if(cCraftItem.ForceFlag== SIN_CLOSE)cCraftItem.ForceFlag = SIN_OPEN; 
			//	else cCraftItem.ForceFlag = SIN_CLOSE;
			//}
			//if(sinGetKeyClick('K') && sinGetKeyClick(VK_CONTROL) ){ //가짜 스킬  
			//	if(SkillMasterFlag== SIN_CLOSE)SkillMasterFlag = SIN_OPEN; 
			//	else SkillMasterFlag = SIN_CLOSE;
			//}

		}
#ifdef _SINBARAM_TEST
		sinTestKey(); //테스트 키 (빌드시에는 실행하지 않는다)
#endif


	break;

	}

}

/*----------------------------------------------------------------------------*
*							    게임 종료 									  *
*-----------------------------------------------------------------------------*/	
void sinClose()
{
	//ktj : 웹db용 임시설정함수.  =============================== start
	void clanMENU_close();
	clanMENU_close();
	//=========================================================== end

	CloseSub();			 //서브메인 종료 
	cInvenTory.Close();  //인벤토리 종료 
	cCharStatus.Close(); //캐릭터 스테이터스 종료 
	cInterFace.Close();  //인터페이스 종료 
	cItem.Close();       //아이템 종료
	cSkill.Close();		 //스킬창 종료 
	cShop.Close();		 //상점 종료 
	cTrade.Close();
	cMessageBox.Close(); //메세지 박스 종료 
	cSin3D.Close();
	cSinHelp.Close();    //신바람 도우미
	cSinWarpGate.Close();//신바람 워프게이트
	cHelpPet.Close();	 //신바람 펫도우미
	cSinSod2.Close();	 //신바람 Sod2
	//박철호 : 2005-11-21 오후 9:00:31
	cPCBANGPet.Close();	
}

