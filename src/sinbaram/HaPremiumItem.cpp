/*----------------------------------------------------------------------------*
*	파일명 :  haPremiumItemItem.h	
*	하는일 :  프리미엄 아이템 서비스관련  
*	작성일 :  최종업데이트 2005년 9월
*	작성자 :  하대용 
*-----------------------------------------------------------------------------*/
#include "sinLinkHeader.h"
#include "..\\field.h"
#include "..\\AreaServer.h"

#include <string>

using namespace std;

cHaPremiumItem  chaPremiumitem;


// 장별 - 텔레포트 코어 필드 추가
#define  TELEPORT_FIELDMAX 33
int TelePort_FieldNum[TELEPORT_FIELDMAX][3] = {
	// (Number, FieldNum, FieldLevel)

	// Page1 -> 바람이이끄는길, 고요의계곡, 정령의숲, 아카시아숲, 자유의정원, 고대인의안식처, 폐성곽, 저주받은땅, 잊혀진땅, 오아시스
	{ 0,20, 0}, { 1,19, 0}, { 2,17, 0}, { 3, 0, 0}, { 4, 2, 0}, { 5, 4, 0}, { 6, 5, 0}, { 7, 7, 0},  { 8, 8, 0},  { 9,10, 0},  

	// Page2 -> 고대인의전장, 금단의땅, 벌집동굴, 버섯동굴, 어둠의성전, 고대감옥1층, 고대감옥2층, 고대감옥3층, 저주받은신전1층, 저주받은신전2층
	{10,11,55}, {11,12,55}, {12,25,55}, {13,24,55}, {14,26,65}, {15,13,40}, {16,14,50}, {17,15,60},	 {18,22,70},  {19,23,75},  

	// Page3 -> 저주받은신전3층, 그리디호수, 혼돈의철로, 페룸의심장, 유라빌리지, 겔루비아계곡, 얼어붙은신전, 켈베쥬레어, 혼란스런주둔지, 잃어버린사원
	{20,42,80}, {21,34,70}, {22,27,80}, {23,28,85}, {24,29,90}, {25,31,90}, {26,35,90}, {27,36,90}, {28,37,95}, {29,38,100}, 

	// Page4 -> 끝없는탑1층, 끝없는탑2층, 끝없는탑3층
	{30,40,100}, {31,41,100}, {32,43,102}
};


//
char *haTeleport_Field[] = {
	"image\\Sinimage\\help\\haTeleport_Field[1].sin",
	"image\\Sinimage\\help\\haTeleport_Field[2].sin",
	"image\\Sinimage\\help\\haTeleport_Field[3].sin",
	"image\\Sinimage\\help\\haTeleport_Field[4].sin",
};
/*----------------------------------------------------------------------------*
*					  생성자		
*-----------------------------------------------------------------------------*/
cHaPremiumItem::cHaPremiumItem()
{
	TelePortCore.PageButtonFlag[0] = 0;
	TelePortCore.PageButtonFlag[1] = 0;
	TelePortCore.FieldIndex[0]     = 0;
	TelePortCore.FieldIndex[1]     = 0;
	TelePortCore.PageIndex         = 0;
	Using_ItemKind                 = 0;
	Using_SelectInvenItemIndex	   = 0; // 박재원 - 이동 상점 아이템(인벤에서 선택된 아이템 인덱스를 가진다.)
	int i;
	for( i = 0 ; i < SINUPKEEPITEM_MAX ; i++ ){
		UpKeepItem[i].PosiX   = 0;
		UpKeepItem[i].PosiY   = 0;
		UpKeepItem[i].Visible = false;
		UpKeepItem[i].IconTime[0] = 0;   
		UpKeepItem[i].IconTime[1] = 0;
		UpKeepItem[i].Alpha       = 255;
		UpKeepItem[i].Alphakind   = 0;
		UpKeepItem[i].Per		  = 0;
		memset(UpKeepItem[i].Id,NULL,sizeof(UpKeepItem[i].Id));
	}

	UseClickPremiumItemFlag = false;

	//멤버 변수 초기화
	m_ThirdEyesTime   = 0;
	m_ExpUpPotionTime = 0;
	m_VampiricCuspidTime  = 0;
	m_ManaRechargingPTime = 0;
	m_ManaReducePotiontime = 0; // pluto 마나 리듀스 포션
	m_ManaReducePotionValue = 0;		// pluto 마나 리듀스 포션 감소 %값
	m_MightofAwellTime = 0;		// pluto 마이트 오브 아웰
	m_MightofAwellWeight = 0;	// pluto 마이트 오브 아웰 소지량
	m_PhenixPetTime = 0;		// pluto 펫(해외)
	m_HelpPetTime = 0; // 박재원 - 빌링 도우미 펫 추가
	m_VampiricCuspidEXTime  = 0;		// 장별 - 뱀피릭 커스핏 EX
	m_StaminaReducePotiontime = 0;	// 박재원 - 근력 리듀스 포션
	m_StaminaReducePotionValue = 0; // 박재원 - 근력 리듀스 포션 감소 %값
	
}
/*----------------------------------------------------------------------------*
*					  소멸자		
*-----------------------------------------------------------------------------*/
cHaPremiumItem::~cHaPremiumItem()
{
	//int i;
	//for( i = 0 ; i < SINUPKEEPITEM_MAX ; i++ ){
	//	if(UpKeepItem[i].lpImage){
	//		UpKeepItem[i].lpImage->Release();
	//		UpKeepItem[i].lpImage = 0;
	//	}
	//}
}

/*----------------------------------------------------------------------------*
*					  init		
*-----------------------------------------------------------------------------*/
void cHaPremiumItem::init()
{
	//프리미엄 아이템 사용시 버프 표시 이미지 로딩 
	UpKeepItemTGAImage[0]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\ThirdEyes.tga"     ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );
	UpKeepItemTGAImage[1]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\ExpUpPotion.tga"   ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );
	UpKeepItemTGAImage[2]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\Vampiric.tga"      ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );
	UpKeepItemTGAImage[3]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\M_Rechar.tga"      ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );

	UpKeepItemTGAImage[4]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\M_Might.tga"   ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );	// pluto 마이트 오브 아웰 이미지
	UpKeepItemTGAImage[5]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\M_Reduce.tga"     ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );	// pluto 마나 리듀스 포션 이미지
	UpKeepItemTGAImage[6]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\M_Phoenix.TGA"     ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );	// pluto 펫(해외)
	UpKeepItemTGAImage[7]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\Pet_terry-pose.tga"  ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );	// 박재원 - 빌링 도우미 펫 추가(테리)
	UpKeepItemTGAImage[8]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\Pet_nepsys-pose.tga"  ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );	// 박재원 - 빌링 도우미 펫 추가(넵시스)
	UpKeepItemTGAImage[9]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\Pet_io-pose.tga"  ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );	// 박재원 - 빌링 도우미 펫 추가(이오)
	UpKeepItemTGAImage[10]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\Pet-mute-pose.tga"  ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );	// 박재원 - 빌링 도우미 펫 추가(무트)
	UpKeepItemTGAImage[11]     = CreateTextureMaterial( "image\\Sinimage\\Premium\\Vampiric_EX.tga"      ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA ); // 장별 - 뱀피릭 커스핏 EX
	UpKeepItemTGAImage[12]    = CreateTextureMaterial( "image\\Sinimage\\Premium\\S_Reduce.tga"  ,0 ,0 ,0 ,0 , SMMAT_BLEND_ALPHA );	// 박재원 - 근력 리듀스 포션
	//
	lpUpKeepItemBackImage[0]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\ThirdEyes_Back.bmp" );  	
	lpUpKeepItemBackImage[1]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\ExpUpPotion_Back.bmp" );
	lpUpKeepItemBackImage[2]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\Vampiric_back.bmp" );
	lpUpKeepItemBackImage[3]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\M_Rechar_back.bmp" );

	lpUpKeepItemBackImage[4]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\M_Might_back.bmp" );	// pluto 마이트 오브 아웰 이미지
	lpUpKeepItemBackImage[5]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\M_Reduce_back.bmp" );  	// pluto 마나 리듀스 포션 이미지
	lpUpKeepItemBackImage[6]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\M_Phoenix_back.BMP" );  	// pluto 펫(해외)
	lpUpKeepItemBackImage[7]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\M_Phoenix_back.BMP" );	// 박재원 - 빌링 도우미 펫 추가
	lpUpKeepItemBackImage[8]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\M_Phoenix_back.BMP" );	// 박재원 - 빌링 도우미 펫 추가
	lpUpKeepItemBackImage[9]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\M_Phoenix_back.BMP" );	// 박재원 - 빌링 도우미 펫 추가
	lpUpKeepItemBackImage[10]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\M_Phoenix_back.BMP" );	// 박재원 - 빌링 도우미 펫 추가
	lpUpKeepItemBackImage[11]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\Vampiric_back_EX.bmp" ); // 장별 - 뱀피릭 커스핏 EX
	lpUpKeepItemBackImage[12]  = LoadDibSurfaceOffscreen( "image\\Sinimage\\Premium\\S_Reduce_back.bmp" );	// 박재원 - 근력 리듀스 포션
	
	haItemUseDelayFlag = false;
}
/*----------------------------------------------------------------------------*
*					  Main		
*-----------------------------------------------------------------------------*/
//왼쪽에 찍일 포지션 좌표값
int ItemUseLeftPosi[SINUPKEEPITEM_MAX][2]={				// pluto 마나 리듀스 포션 마이트 오브 아웰 버프 찍힐 위치
	{8,80},{8,116},{8,152},{8,188},{8,224},{8,260},{8,296}, {8, 332}  // 박재원 - 빌링 도우미 펫 추가후 버프 위치 하나 더 추가함. // 장별 - 뱀피릭 커스핏 EX
};																	  // 박재원 - 근력 리듀스 포션 추가
DWORD dwDelayTime = 0; 
void cHaPremiumItem::Main()
{
	//몬스터 크리스탈 아이템 사용시 딜레이를 준다,
	if( chaPremiumitem.haItemUseDelayFlag == true){
		dwDelayTime++;
		if( dwDelayTime > 210){  //3초로 제한한다.{
			chaPremiumitem.haItemUseDelayFlag = false;
			dwDelayTime = 0;
		}
	}


	//유지형으로 사용돼는 아이콘의 위치정보
	int i,cnt=0;	
	UseClickPremiumItemFlag = false;
	for( i = 0 ; i < SINUPKEEPITEM_MAX ; i++ ){
		////시간 체크
		if(UpKeepItem[i].IconTime[0] < UpKeepItem[i].IconTime[1]){
			if(UpKeepItem[i].Visible == true ){
				if(UpKeepItem[i].IconTime[1]-UpKeepItem[i].IconTime[0] <= 0 ){
					UpKeepItem[i].Visible = false;
					CheckUpKeepItem();  //종료시 한번씩 호출해준다.
				}
				cnt++;
				//서버 시간을 받아 와서 찍어준다.
				DWORD NowTime = GetPlayTime_T();			
				switch(UpKeepItem[i].TGAImageNumber){
					case nsPremiumItem::THIRD_EYES:   //써드 아이즈
						if( m_ThirdEyesTime > 0){
							UpKeepItem[i].IconTime[0] = NowTime;
						}
					break;
					case nsPremiumItem::EXPUP_POTION:  //경험치 증가 포션
						if( m_ExpUpPotionTime > 0){
							UpKeepItem[i].IconTime[0] = NowTime;
						}
					break;
					case nsPremiumItem::VAMPIRIC_CUS:  //뱀피릭 커스핏
						if( m_VampiricCuspidTime > 0){
							UpKeepItem[i].IconTime[0] = NowTime;
						}						
					break;

					
					case nsPremiumItem::VAMPIRIC_CUS_EX:  // 장별 - 뱀피릭 커스핏 EX
						if( m_VampiricCuspidEXTime > 0){
							UpKeepItem[i].IconTime[0] = NowTime;
						}						
					break;
					

					case nsPremiumItem::MANA_RECHAR_P:  //마나 리차징  포션
						if( m_ManaRechargingPTime > 0){
							UpKeepItem[i].IconTime[0] = NowTime;
						}						
					break;
					case nsPremiumItem::MIGHT_OF_AWELL:	// pluto 마이트 오브 아웰
						if( m_MightofAwellTime > 0 )
						{
							UpKeepItem[i].IconTime[0] = NowTime;
						}
						break;
					case nsPremiumItem::MANA_REDUCE_P:	// pluto 마나 리듀스 포션
						if( m_ManaReducePotiontime > 0 )
						{
							UpKeepItem[i].IconTime[0] = NowTime;
						}
						break;
					case nsPremiumItem::PHENIX_PET:	// pluto 펫(해외)
						if( m_PhenixPetTime > 0 )
						{
							UpKeepItem[i].IconTime[0] = NowTime;
						}
						break;
					case nsPremiumItem::HELP_PET_TERRY: // 박재원 - 빌링 도우미 펫 추가
						if(m_HelpPetTime > 0 ) 
						{
							UpKeepItem[i].IconTime[0] = NowTime;
						}
						break;
					case nsPremiumItem::HELP_PET_NEPSYS: // 박재원 - 빌링 도우미 펫 추가
						if(m_HelpPetTime > 0 ) 
						{
							UpKeepItem[i].IconTime[0] = NowTime;
						}
						break;
					case nsPremiumItem::HELP_PET_IO: // 박재원 - 빌링 도우미 펫 추가
						if(m_HelpPetTime > 0 ) 
						{
							UpKeepItem[i].IconTime[0] = NowTime;
						}
						break;
					case nsPremiumItem::HELP_PET_MUTE: // 박재원 - 빌링 도우미 펫 추가
						if(m_HelpPetTime > 0 ) 
						{
							UpKeepItem[i].IconTime[0] = NowTime;
						}
						break;
					case nsPremiumItem::STAMINA_REDUCE_P:  // 박재원 - 근력 리듀스 포션 
						if( m_StaminaReducePotiontime > 0){
							UpKeepItem[i].IconTime[0] = NowTime;
						}						
						break;
				}
			}
		}
		else
			UpKeepItem[i].Visible = false;
		if(UpKeepItem[i].Visible == true){
			//위치 변경
			if(UpKeepItem[i].PosiY > ItemUseLeftPosi[cnt-1][1])
				UpKeepItem[i].PosiY-=1;
			else{
				UpKeepItem[i].PosiY = ItemUseLeftPosi[cnt-1][1];
				UpKeepItem[i].PosiX = ItemUseLeftPosi[cnt-1][0];
			}
			//마우스 위치 체크
			if(pCursorPos.x  > UpKeepItem[i].PosiX && pCursorPos.x < UpKeepItem[i].PosiX + 30 &&
				pCursorPos.y > UpKeepItem[i].PosiY && pCursorPos.y < UpKeepItem[i].PosiY + 30 ){
					UpKeepItem[i].Infoflag = true;
					UseClickPremiumItemFlag = true;
			}
			else{
				UpKeepItem[i].Infoflag = false;
				UseClickPremiumItemFlag = false;
			}
		}
	}
	//버튼 처리가 들어가는 아이템일경우
	switch(Using_ItemKind){
		case 8:    //텔레포트 코어
			if(pCursorPos.x > 100 && pCursorPos.x < 100+20 && 
				pCursorPos.y > 365 && pCursorPos.y < 365+20)
					TelePortCore.PageButtonFlag[0] = 1;
			else if(pCursorPos.x >330 && pCursorPos.x < 330+20 &&
				pCursorPos.y > 365 && pCursorPos.y < 365+20)
					TelePortCore.PageButtonFlag[1] = 1;
			else{
				TelePortCore.PageButtonFlag[0] = 0;
				TelePortCore.PageButtonFlag[1] = 0;
			}		
		break;
	}
}
/*----------------------------------------------------------------------------*
*					  Draw		
*-----------------------------------------------------------------------------*/
void cHaPremiumItem::Draw()
{
	//아이템 사용시 버튼 처리 
	switch(Using_ItemKind){
		case 8:
		if(TelePortCore.PageButtonFlag[0])
			DrawSprite(100,365,chaQuest.lpQuestButtonImage[2],0,0,20,20);
		else	
			DrawSprite(100,365,chaQuest.lpQuestButtonImage[0],0,0,20,20);
		if(TelePortCore.PageButtonFlag[1])
			DrawSprite(330,365,chaQuest.lpQuestButtonImage[3],0,0,20,20); 
		else
			DrawSprite(330,365,chaQuest.lpQuestButtonImage[1],0,0,20,20); 
	}
}

DWORD dwKeepItemTime[6] = {0, SINITEM_TIME_1HOURS, SINITEM_TIME_3HOURS, SINITEM_TIME_ONEDAY, SINITEM_TIME_SEVENDAY, SINITEM_TIME_30DAY};		//시간테이블
/*----------------------------------------------------------------------------*
*					  시간타임에따라 분류해주기위한 함수 	
*-----------------------------------------------------------------------------*/
int  cHaPremiumItem::CheckTime(DWORD CurrentTime)
{

	//현재 시간을  
	for( int i = 0 ; i < 5 ; i++ ){ // 장별 - 1시간 아이템 추가로 수정
		if( dwKeepItemTime[i] < CurrentTime  &&  CurrentTime < dwKeepItemTime[i+1] ){
			return i+1;
		}
	}

	return false;
}
/*----------------------------------------------------------------------------*
*					  스킬 유지형 아이콘 Draw		
*-----------------------------------------------------------------------------*/
void cHaPremiumItem::DrawUp()
{
		//
	int i;
	for( i = 0 ; i < SINUPKEEPITEM_MAX ; i++ ){
		if(UpKeepItem[i].Visible == true){
			dsDrawTexImage( UpKeepItemTGAImage[UpKeepItem[i].TGAImageNumber-1] ,UpKeepItem[i].PosiX,UpKeepItem[i].PosiY, 32, 32 , UpKeepItem[i].Alpha );  //좌측 
			
			if(UpKeepItem[i].Infoflag == true){
				InfoBox(UpKeepItem[i].PosiX+30,UpKeepItem[i].PosiY,10,6);
			}
			//BackBoxImage
			int    MinLen = 0;  //현재 찍어줄 백 이미지 계산
			DWORD  dwCurrentTime = UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0];
			switch(UpKeepItem[i].TGAImageNumber){
				case nsPremiumItem::THIRD_EYES:    //써드 아이즈									
					switch( CheckTime( dwCurrentTime ) ){
						case 1:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_1HOURS/32));     //한칸당 초 (1시간)
						break;
						case 2:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_3HOURS/32));    //한칸당 초 (3시간)
						break;
						case 3:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_ONEDAY/32));    //한칸당 초 (1일)
						break;
						case 4:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_SEVENDAY/32));  //한칸당 초 (7일 )
						break;
						case 5:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_30DAY/32));     //한칸당 초 (30일)
						break;
					}

					if(dwCurrentTime <= 0)
					{
						chaPremiumitem.m_ThirdEyesTime = 0;
					}

				break;
				case nsPremiumItem::EXPUP_POTION:
					switch( CheckTime( dwCurrentTime ) ){
						case 1:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_1HOURS/32));     //한칸당 초 (1시간)
						break;
						case 2:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_3HOURS/32));    //한칸당 초 (3시간)
						break;
						case 3:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_ONEDAY/32));    //한칸당 초 (1일)
						break;
						case 4:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_SEVENDAY/32));  //한칸당 초 (7일 )
						break;
						case 5:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_30DAY/32));     //한칸당 초 (30일)
						break;						
					}

					if(dwCurrentTime <= 0)
					{
						chaPremiumitem.m_ExpUpPotionTime = 0;
					}

				break;
				case nsPremiumItem::MIGHT_OF_AWELL:		// pluto 마이트 오브 아웰
					switch( CheckTime( dwCurrentTime ) )
					{
						case 1:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_1HOURS/32));     //한칸당 초 (1시간)
						break;
						case 2:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_3HOURS/32));    //한칸당 초 (3시간)
						break;
						case 3:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_ONEDAY/32));    //한칸당 초 (1일)
						break;
						case 4:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_SEVENDAY/32));  //한칸당 초 (7일 )
						break;
						case 5:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_30DAY/32));     //한칸당 초 (30일)
						break;
					}
					break;
				case nsPremiumItem::MANA_REDUCE_P:		// pluto 마나 리듀스 포션
					switch( CheckTime( dwCurrentTime ) )
					{
						case 1:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_1HOURS/32));     //한칸당 초 (1시간)
						break;
						case 2:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_3HOURS/32));    //한칸당 초 (3시간)
						break;
						case 3:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_ONEDAY/32));    //한칸당 초 (1일)
						break;
						case 4:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_SEVENDAY/32));  //한칸당 초 (7일 )
						break;
						case 5:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_30DAY/32));     //한칸당 초 (30일)
						break;

					}

					if(dwCurrentTime <= 0)
					{
						chaPremiumitem.m_ManaReducePotiontime = 0;
						chaPremiumitem.m_ManaReducePotionValue = 0;
						chaPremiumitem.SetManaReducePotionTime(chaPremiumitem.m_ManaReducePotiontime);
					}
				break;

				/*
				case nsPremiumItem::VAMPIRIC_CUS:  //뱀피릭 커스핏
					if( SINITEM_TIME_5MINUTE >  dwCurrentTime)
						MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_5MINUTE/32));	//한칸당 찍이는초 
					else
						MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_10MINUTE/32));	//한칸당 찍이는초 
				break;
				case nsPremiumItem::MANA_RECHAR_P:  //마나 리차징 포션
					if( SINITEM_TIME_5MINUTE >  dwCurrentTime)
						MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_5MINUTE/32));	//한칸당 찍이는초 
					else
						MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_10MINUTE/32));	//한칸당 찍이는초 
				break;
				*/
				case nsPremiumItem::VAMPIRIC_CUS:  // pluto 뱀피릭 커스핏
					switch( CheckTime( dwCurrentTime ) )
					{
						case 1:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_1HOURS/32));     //한칸당 초 (1시간)
						break;
						case 2:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_3HOURS/32));    //한칸당 초 (3시간)
						break;
						case 3:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_ONEDAY/32));    //한칸당 초 (1일)
						break;
						case 4:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_SEVENDAY/32));  //한칸당 초 (7일 )
						break;
						case 5:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_30DAY/32));     //한칸당 초 (30일)
						break;

					}

					if(dwCurrentTime <= 0)
					{
						chaPremiumitem.m_VampiricCuspidTime = 0;
					}
				break;

				
				case nsPremiumItem::VAMPIRIC_CUS_EX:  //	장별 - 뱀피릭 커스핏 EX
					switch( CheckTime( dwCurrentTime ) )
					{
						case 1:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_1HOURS/32));     //한칸당 초 (1시간)
						break;
						case 2:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_3HOURS/32));    //한칸당 초 (3시간)
						break;
						case 3:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_ONEDAY/32));    //한칸당 초 (1일)
						break;
						case 4:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_SEVENDAY/32));  //한칸당 초 (7일 )
						break;
						case 5:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_30DAY/32));     //한칸당 초 (30일)
						break;

					}

					if(dwCurrentTime <= 0)
					{
						chaPremiumitem.m_VampiricCuspidEXTime = 0;
					}
				break;
				

				case nsPremiumItem::MANA_RECHAR_P:  // pluto 마나 리차징 포션
					switch( CheckTime( dwCurrentTime ) )
					{
						case 1:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_1HOURS/32));     //한칸당 초 (1시간)
						break;
						case 2:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_3HOURS/32));    //한칸당 초 (3시간)
						break;
						case 3:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_ONEDAY/32));    //한칸당 초 (1일)
						break;
						case 4:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_SEVENDAY/32));  //한칸당 초 (7일 )
						break;
						case 5:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_30DAY/32));     //한칸당 초 (30일)
						break;
					}

					if(dwCurrentTime <= 0)
					{
						chaPremiumitem.m_ManaRechargingPTime = 0;
						chaPremiumitem.SetManaRechargingPTime(chaPremiumitem.m_ManaRechargingPTime);
					}
				break;

				case nsPremiumItem::STAMINA_REDUCE_P:	// 박재원 - 근력 리듀스 포션
					switch( CheckTime( dwCurrentTime ) )
					{
						case 1:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_1HOURS/32));     //한칸당 초 (1시간)
						break;
						case 2:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_3HOURS/32));    //한칸당 초 (3시간)
						break;
						case 3:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_ONEDAY/32));    //한칸당 초 (1일)
						break;
						case 4:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_SEVENDAY/32));  //한칸당 초 (7일 )
						break;
						case 5:
							MinLen =(32-(dwCurrentTime)/(SINITEM_TIME_30DAY/32));     //한칸당 초 (30일)
						break;
					}

					if(dwCurrentTime <= 0)
					{
						chaPremiumitem.m_StaminaReducePotiontime = 0;
						chaPremiumitem.m_StaminaReducePotionValue = 0;
						chaPremiumitem.SetStaminaReducePotionTime(chaPremiumitem.m_StaminaReducePotiontime);
					}
					break;
			}
			//10초
			if(UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0] <= 10)
			{
				if( UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_TERRY || UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_NEPSYS ||
					UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_IO || UpKeepItem[i].TGAImageNumber == nsPremiumItem::HELP_PET_MUTE )
				{
					if( UpKeepItem[i].IconTime[1] - UpKeepItem[i].IconTime[0] <= 0 ) // 박재원 - 빌링 도우미 펫 추가
					{
						chaPremiumitem.UpKeepItem[i].PosiX   = 0;
						chaPremiumitem.UpKeepItem[i].PosiY   = 0;
						chaPremiumitem.UpKeepItem[i].Visible = false;
						chaPremiumitem.UpKeepItem[i].TGAImageNumber = 0;
						chaPremiumitem.UpKeepItem[i].IconTime[0] = 0;   
						chaPremiumitem.UpKeepItem[i].IconTime[1] = 0;
						chaPremiumitem.UpKeepItem[i].Alpha       = 255;
						chaPremiumitem.UpKeepItem[i].Alphakind   = 0;
						chaPremiumitem.UpKeepItem[i].Per		 = 0;
						memset(chaPremiumitem.UpKeepItem[i].Id,NULL,sizeof(chaPremiumitem.UpKeepItem[i].Id));

						m_HelpPetTime = 0;
						// 장별 - 테리
						sinChar->GravityScroolCheck[1] = 0;
						cHelpPet.ClosePet();
					}
				}

				if(UpKeepItem[i].Alpha == 255)
					UpKeepItem[i].Alphakind = 1;
				if(UpKeepItem[i].Alpha == 50)
					UpKeepItem[i].Alphakind = 2;				
			}
			else{
				if(UpKeepItem[i].Alpha == 0){
					UpKeepItem[i].Alphakind = 0;
				}
			}
			if(UpKeepItem[i].Alphakind == 0){
				DrawSprite(UpKeepItem[i].PosiX ,UpKeepItem[i].PosiY+(32-MinLen), lpUpKeepItemBackImage[UpKeepItem[i].TGAImageNumber-1],0,32-MinLen,32,32); 
			}	
			//Fade효과
			switch(UpKeepItem[i].Alphakind)
			{
				case 0:
					if(UpKeepItem[i].Alpha < 255)
						UpKeepItem[i].Alpha++;
					else
						UpKeepItem[i].Alpha = 255;
				break;
				case 1:
					if(UpKeepItem[i].Alpha  > 50)
						UpKeepItem[i].Alpha-=5;
					else
						UpKeepItem[i].Alpha =50;
				break;
				case 2:
					if(UpKeepItem[i].Alpha < 255)
						UpKeepItem[i].Alpha+=5;
					else
						UpKeepItem[i].Alpha = 255;
				break;
			}
		}
	}
}
/*----------------------------------------------------------------------------*
*					  LButtonDown		
*-----------------------------------------------------------------------------*/
void cHaPremiumItem::LButtonDown(int x,int y)
{
	//텔레포트 코어 버튼 처리 // 장별 - 텔레포트코어
	if(TelePortCore.PageButtonFlag[1]){
		if( TelePortCore.PageIndex < 3 )
			TelePortCore.PageIndex++;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT_SCROLL,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, RGBA_MAKE(0,15,128,125),haTeleport_Field[TelePortCore.PageIndex]);  																
	}
	if(TelePortCore.PageButtonFlag[0]){
		if( 0 < TelePortCore.PageIndex )
			TelePortCore.PageIndex--;
		cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT_SCROLL,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, RGBA_MAKE(0,15,128,125),haTeleport_Field[TelePortCore.PageIndex]);  																
	}	
}
/*----------------------------------------------------------------------------*
*					  LButtonUp		
*-----------------------------------------------------------------------------*/
void cHaPremiumItem::LButtonUp(int x,int y)
{

}
DWORD dwPremiumItemCode[]={(sinBI1|sin01),(sinBI1|sin02),(sinBI1|sin03),(sinBI1|sin04),(sinBI1|sin05),(sinBI1|sin06),(sinBI1|sin07)};
/*----------------------------------------------------------------------------*
*Desc: 프리미엄 아이템 사용시  호출		
*-----------------------------------------------------------------------------*/
int cHaPremiumItem::UsePremiumItem(int kind)
{
	Using_ItemKind =0;
	switch(kind){
		case 1:   //블루 스톤
			cCharStatus.InitCharStatus(1);
			cInvenTory.SetItemToChar();
			if ( sinChar->Life[1]<sinGetLife() ) {
				sinSetLife( sinChar->Life[1] );
				ReformCharForm();//재인증 
				ResetEnergyGraph(4);
			}
			haCastleSkillUseFlag = 1;
		break;
		case 2:   //레드스톤
			cSkill.InitSkillPoint(1);
			haCastleSkillUseFlag = 1;
		break;
		case 3:   //그린스톤
			cSkill.InitSkillPoint(1);
			cCharStatus.InitCharStatus(1);
			cInvenTory.SetItemToChar();
			if ( sinChar->Life[1]<sinGetLife() ) {
				sinSetLife( sinChar->Life[1] );
				ReformCharForm();//재인증 
				ResetEnergyGraph(4);
			}
			haCastleSkillUseFlag = 1;
		break;
		case 5:    //이터널 라이프
			SetPremiumItemSkill(1);	
			cInvenTory.SetItemToChar();
		break;
		case 6:    //페이틀 에지
			SetPremiumItemSkill(2);		
		break;		
		case 7:    //어버트 스크롤
			SetPremiumItemSkill(3);		
		break;
		case 8:    //텔레포트 코어
			if(!CheckWindowOpen())break;
			Using_ItemKind = kind;
			cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT_SCROLL,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y,
			RGBA_MAKE(0,15,128, 125),haTeleport_Field[TelePortCore.PageIndex]);  	
			haCastleSkillUseFlag = 0;
			HelpBoxKindIndex = 0;
			//cSinHelp.NPCTeleportFlag = 1; // pluto
 			break;
		case 9:
			haCastleSkillUseFlag = 1;
		break;
		case 10:   //사용돼서는 안돼는 아이템은 플랙을 없애준다,
		case 11:
			haCastleSkillUseFlag = 0;
		break;
		case 12:   //써드 아이즈(1일)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_ONEDAY,true,UpKeepItemName[0], 50);
			
		break;
		case 13:   //경험치 증가 포션(1일)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1], 30);
			//SetExpUpPotionTime(SINITEM_TIME_ONEDAY);
		break;
		case 14:   //써드 아이즈(7일)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[0], 50);
			//SetVampiricCuspidTime(SINITEM_TIME_SEVENDAY);
		break;
		case 15:   //경험치 증가 포션(7일)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1],30);
			//SetExpUpPotionTime(SINITEM_TIME_SEVENDAY);
		break;
		case 16:   //헤어틴트 A형
			if(UseHairtintPotion(1))
				haCastleSkillUseFlag = 1;
		break;
		case 17:   //헤어틴트 B형
			if(UseHairtintPotion(2))
				haCastleSkillUseFlag = 1;
		break;
		case 18:   //헤어틴트 C형
			if(UseHairtintPotion(3))
				haCastleSkillUseFlag = 1;
		break;
		case 19:  // pluto 뱀피릭 커스핏 3시간
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS,SINITEM_TIME_3HOURS,true,UpKeepItemName[2]);
			SetVampiricCuspidTime(SINITEM_TIME_3HOURS);
		break;
		case 20:  // pluto 뱀피릭 커스핏 1일
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS,SINITEM_TIME_ONEDAY,true,UpKeepItemName[2]);
			SetVampiricCuspidTime(SINITEM_TIME_ONEDAY);
		break;
		case 21:  // pluto 마나 리차징 포션 3시간
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::MANA_RECHAR_P,SINITEM_TIME_3HOURS,true,UpKeepItemName[3]);
			SetManaRechargingPTime(SINITEM_TIME_3HOURS);
		break;
		case 22:  // pluto 마나 리차징 포션 1일
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::MANA_RECHAR_P,SINITEM_TIME_ONEDAY,true,UpKeepItemName[3]);	
			SetManaRechargingPTime(SINITEM_TIME_ONEDAY);
		break;
		case 23:  //폭죽
			haCastleSkillUseFlag = 1;		
		break;

		case 24: //브론즈 패키지(3시간)  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_3HOURS,true,UpKeepItemName[0],20,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_3HOURS,true,UpKeepItemName[1],10);

		break;
		case 25: //브론즈 패키지(1일 )  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_ONEDAY,true,UpKeepItemName[0],20,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1],10);
			
		break;
		case 26: //브론즈 패키지(7일 )  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[0],20,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1],10);

		break;
		case 27: //브론즈 패키지(30일 )  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_30DAY,true,UpKeepItemName[0],20,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_30DAY,true,UpKeepItemName[1],10);

		break;
		case 28: //실버 패키지(3시간)  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_3HOURS,true,UpKeepItemName[0],30,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_3HOURS,true,UpKeepItemName[1],20);

		break;
		case 29: //실버 패키지(1일 )  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_ONEDAY,true,UpKeepItemName[0],30,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1],20);

		break;
		case 30: //실버 패키지(7일 )  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[0],30,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1],20);

			
		break;
		case 31: //실버 패키지(30일 )  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_30DAY,true,UpKeepItemName[0],30,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_30DAY,true,UpKeepItemName[1],20);
			
		break;

		case 32: //골드 패키지(3시간)  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_3HOURS,true,UpKeepItemName[0],40,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_3HOURS,true,UpKeepItemName[1],30);
			
		break;

		case 33: //골드 패키지(1일 )  
			haCastleSkillUseFlag = 1;																		
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_ONEDAY,true,UpKeepItemName[0],40,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1],30);

		break;
		case 34: //골드 패키지(7일 )  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[0],40,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1],30);

		break;
		case 35: //골드 패키지(30일 )  
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_30DAY,true,UpKeepItemName[0],40,1))
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_30DAY,true,UpKeepItemName[1],30);		
		break;

		//-------------------------------2차 헤어포션 ----- 성근 060524 -------------------------
		case 36:   //헤어틴트 D형
			if(UseHairtintPotion(4))
				haCastleSkillUseFlag = 1;
		break;
		case 37:   //헤어틴트 E형
			if(UseHairtintPotion(5))
				haCastleSkillUseFlag = 1;
		break;
		case 38:   //헤어틴트 F형
			if(UseHairtintPotion(6))
				haCastleSkillUseFlag = 1;
		break;
		case 39:   //헤어틴트 G형
			if(
				UseHairtintPotion(7))
				haCastleSkillUseFlag = 1;
		break;
		case 40:   //헤어틴트 H형
			if(UseHairtintPotion(8))
				haCastleSkillUseFlag = 1;
		break;
		
		//-------------------------------3차 헤어포션 ----- 성근 060809 -------------------------

		case 41:   //헤어틴트 I형
			if(UseHairtintPotion(9))
				haCastleSkillUseFlag = 1;
		break;
		case 42:   //헤어틴트 J형
			if(UseHairtintPotion(10))
				haCastleSkillUseFlag = 1;
		break;
		case 43:   //헤어틴트 K형
			if(UseHairtintPotion(11))
				haCastleSkillUseFlag = 1;
		break;
		case 44:   //헤어틴트 L형
			if(UseHairtintPotion(12))
				haCastleSkillUseFlag = 1;
		break;
		case 45:   //헤어틴트 M형
			if(UseHairtintPotion(13))
				haCastleSkillUseFlag = 1;
		break;
		//----------------------------- 베트남요청 50% 경치 업 --------------- //
		
		case 46:   //경험치 증가 포션(1일)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1], 50);
			
		break;
		case 47:   //경험치 증가 포션(7일)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1], 50);
		break;
		case 48:	// pluto 마이트 오브 아웰 7일
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[4], 300 );
			break;
		case 49:	// pluto 마이트 오브 아웰 30일
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_30DAY, true, UpKeepItemName[4], 300 );
			break;
		case 50:	// pluto 마나 리듀스 포션 1일
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_ONEDAY, true, UpKeepItemName[5], 30 );
			break;
		case 51:	// pluto 마나 리듀스 포션 7일
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[5], 30 );
			break;
		case 52:	// pluto 브론즈 패키지2 3시간
			haCastleSkillUseFlag = 1;
            if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_3HOURS,true,UpKeepItemName[5],10,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_3HOURS,true,UpKeepItemName[1],10);
			}
			break;
		case 53:	// pluto 브론즈 패키지2 1일
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_ONEDAY,true,UpKeepItemName[5],10,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1],10);
			}
			break;
		case 54:	// pluto 브론즈 패키지2 7일
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[5],10,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1],10);
			}
			break;
		case 55:	// pluto 실버 패키지2 3시간
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_3HOURS,true,UpKeepItemName[5],20,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_3HOURS,true,UpKeepItemName[1],20);
			}
			break;
		case 56:	// pluto 실버 패키지2 1일
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_ONEDAY,true,UpKeepItemName[5],20,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1],20);
			}
			break;
		case 57:	// pluto 실버 패키지2 7일
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[5],20,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1],20);
			}
			break;
		case 58:	// pluto 골드 패키지2 3시간
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_3HOURS,true,UpKeepItemName[5],30,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_3HOURS,true,UpKeepItemName[1],30);
			}
			break;
		case 59:	// pluto 골드 패키지2 1일
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_ONEDAY,true,UpKeepItemName[5],30,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1],30);
			}
			break;
		case 60:	// pluto 골드 패키지2 7일
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[5],30,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1],30);
			}
			break;
		case 61:	// pluto 슈페리어 패키지2 3시간
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_3HOURS,true,UpKeepItemName[5],40,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_3HOURS,true,UpKeepItemName[1],40);
			}
			break;
		case 62:	// pluto 슈페리어 패키지2 1일
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_ONEDAY,true,UpKeepItemName[5],40,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1],40);
			}
			break;
		case 63:	// pluto 슈페리어 패키지2 7일
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::MANA_REDUCE_P,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[5],40,2))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1],40);
			}
			break;
		case 64:	// pluto 마이트 오브 아웰2 7일
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[4], 500 );
			break;
		case 65:	// pluto 마이트 오브 아웰2 30일
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::MIGHT_OF_AWELL, SINITEM_TIME_30DAY, true, UpKeepItemName[4], 500 );
			break;
		case 66:	// pluto 슈페리어 패키지 3시간
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_3HOURS,true,UpKeepItemName[0],50,1))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_3HOURS,true,UpKeepItemName[1],40);
			}
			break;
		case 67:	// pluto 슈페리어 패키지 1일
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_ONEDAY,true,UpKeepItemName[0],50,1))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1],40);
			}
			break;
		case 68:	// pluto 슈페리어 패키지 7일
			haCastleSkillUseFlag = 1;
			if(SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[0],50,1))
			{
				SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1],40);
			}
			break;
		case 69:	// pluto 펫(해외)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::PHENIX_PET, SINITEM_TIME_ONEDAY, true, UpKeepItemName[6], 30 );
			//cPCBANGPet.PetKind = TRUE;
			//cPCBANGPet.ShowPet();
			break;
		case 70:	// pluto 펫(해외)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::PHENIX_PET, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[6], 30 );
			break;
		case 71:	// pluto 펫(해외)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::PHENIX_PET, SINITEM_TIME_3HOURS, true, UpKeepItemName[6], 30 );
			break;

		// 박재원  72번은 비워둠.

		case 73:	// 박재원 - 에이징 마스터(무기)
			haCastleSkillUseFlag = 1;
			UseAgingMaster(0);
			break;
		case 74:	// 박재원 - 에이징 마스터(방패, 오브, 비즈)
			haCastleSkillUseFlag = 1;
			UseAgingMaster(1);
			break;
		case 75:	// 박재원 - 에이징 마스터(갑옷, 로브)
			haCastleSkillUseFlag = 1;
			UseAgingMaster(2);
			break;
		case 76: // 박재원 - 스킬 마스터(1차)
			haCastleSkillUseFlag = 1;
			UseSkillMaster(1); // 1차 전직 스킬
			break;
		case 77: // 박재원 - 스킬 마스터(2차)
			haCastleSkillUseFlag = 1;
			UseSkillMaster(2); // 2차 전직 스킬
			break;
		case 78: // 박재원 - 스킬 마스터(3차)
			haCastleSkillUseFlag = 1;
			UseSkillMaster(3); // 3차 전직 스킬
			break;
		case 79: // 박재원 - 이동 상점 아이템
			haCastleSkillUseFlag = 1;
			cInvenTory.InvenItem[Using_SelectInvenItemIndex].sItemInfo.PotionCount = 300;
			sinThrowItemToFeild(&cInvenTory.InvenItem[Using_SelectInvenItemIndex]);
			cInvenTory.InvenItem[Using_SelectInvenItemIndex].Flag = 0;
			cInvenTory.CheckWeight();//무게를 보정해준다
			cInvenTory.ReFormInvenItem();
			SaveGameData();
			UseMoveShop();	
			break;
		case 80:   // 박재원 - 경험치증가 포션(100% 1일 추가)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_ONEDAY,true,UpKeepItemName[1], 100);
			break;
		case 81:   // 박재원 - 경험치증가 포션(100% 7일 추가)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_SEVENDAY,true,UpKeepItemName[1], 100);
			break;
		case 82: // 박재원 - 캐릭터 속성별 스탯 초기화 아이템(5종 - 힘)
			cCharStatus.InitCharStatus_Attribute(1); // 힘
			cInvenTory.SetItemToChar();
			if ( sinChar->Life[1]<sinGetLife() ) {
				sinSetLife( sinChar->Life[1] );
				ReformCharForm();//재인증 
				ResetEnergyGraph(4);
			}
			haCastleSkillUseFlag = 1;
			break;
		case 83: // 박재원 - 캐릭터 속성별 스탯 초기화 아이템(5종 - 정신력)
			cCharStatus.InitCharStatus_Attribute(2); // 정신력
			cInvenTory.SetItemToChar();
			if ( sinChar->Life[1]<sinGetLife() ) {
				sinSetLife( sinChar->Life[1] );
				ReformCharForm();//재인증 
				ResetEnergyGraph(4);
			}
			haCastleSkillUseFlag = 1;
			break;
		case 84: // 박재원 - 캐릭터 속성별 스탯 초기화 아이템(5종 - 재능)
			cCharStatus.InitCharStatus_Attribute(3); // 재능
			cInvenTory.SetItemToChar();
			if ( sinChar->Life[1]<sinGetLife() ) {
				sinSetLife( sinChar->Life[1] );
				ReformCharForm();//재인증 
				ResetEnergyGraph(4);
			}
			haCastleSkillUseFlag = 1;
			break;
		case 85: // 박재원 - 캐릭터 속성별 스탯 초기화 아이템(5종 - 민첩성)
			cCharStatus.InitCharStatus_Attribute(4); // 민첩성
			cInvenTory.SetItemToChar();
			if ( sinChar->Life[1]<sinGetLife() ) {
				sinSetLife( sinChar->Life[1] );
				ReformCharForm();//재인증 
				ResetEnergyGraph(4);
			}
			haCastleSkillUseFlag = 1;
			break;
		case 86: // 박재원 - 캐릭터 속성별 스탯 초기화 아이템(5종 - 건강)
			cCharStatus.InitCharStatus_Attribute(5); // 건강
			cInvenTory.SetItemToChar();
			if ( sinChar->Life[1]<sinGetLife() ) {
				sinSetLife( sinChar->Life[1] );
				ReformCharForm();//재인증 
				ResetEnergyGraph(4);
			}
			haCastleSkillUseFlag = 1;
			break;
		case 87:   // 박재원 - 경험치증가 포션(100% 30일 추가)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_30DAY,true,UpKeepItemName[1], 100);
			break;
		case 88:	// 박재원 - 픽닉스 펫(30일) 추가
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::PHENIX_PET, SINITEM_TIME_30DAY, true, UpKeepItemName[6], 30 );
			break;

		case 97: // 박재원 - 엘더 코퍼 오어 추가   
		case 98: // 박재원 - 슈퍼 에이징 스톤 추가
			haCastleSkillUseFlag = 0;
			break;
		case 99:	// 박재원 - 빌링 도우미 펫 추가(테리)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_30DAY, true, UpKeepItemName[7], 30, 3);
			sinChar->GravityScroolCheck[1] = 1;
			break;
		case 100:	// 박재원 - 빌링 도우미 펫 추가(넵시스)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_30DAY, true, UpKeepItemName[8], 30, 3);
			break;
		case 101:	// 박재원 - 빌링 도우미 펫 추가(이오)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_IO, SINITEM_TIME_30DAY, true, UpKeepItemName[9], 30, 3);
			break;
		case 102:	// 박재원 - 빌링 도우미 펫 추가(무트)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_30DAY, true, UpKeepItemName[10], 30, 3);
			sinChar->GravityScroolCheck[1] = 2;
			break;

		case 103:	// 장별 - 빌링 도우미 펫 추가(테리) // 1일
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_ONEDAY, true, UpKeepItemName[7], 30, 3);
			sinChar->GravityScroolCheck[1] = 1;
			break;
		case 104:	// 장별 - 빌링 도우미 펫 추가(넵시스)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_ONEDAY, true, UpKeepItemName[8], 30, 3);
			break;
		case 105:	// 장별 - 빌링 도우미 펫 추가(이오)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_IO, SINITEM_TIME_ONEDAY, true, UpKeepItemName[9], 30, 3);
			break;
		case 106:	// 장별 - 빌링 도우미 펫 추가(무트)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_ONEDAY, true, UpKeepItemName[10], 30, 3);
			sinChar->GravityScroolCheck[1] = 2;
			break;
		
		case 107:   // 장별 - 경험치증가 포션(100% 1시간)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_1HOURS,true,UpKeepItemName[1], 100);
		break;
			
		case 108:	// 장별 - 피닉스펫(1시간)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::PHENIX_PET, SINITEM_TIME_1HOURS, true, UpKeepItemName[6], 30 );
		break;

		case 109:	// 장별 - 빌링 도우미 펫 추가(테리)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[7], 30, 3);
			sinChar->GravityScroolCheck[1] = 1;
			break;
		case 110:	// 장별 - 빌링 도우미 펫 추가(넵시스)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[8], 30, 3);
			break;
		case 111:	// 장별 - 빌링 도우미 펫 추가(이오)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_IO, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[9], 30, 3);
			break;
		case 112:	// 장별 - 빌링 도우미 펫 추가(무트)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[10], 30, 3);
			sinChar->GravityScroolCheck[1] = 2;
		break;
		case 113:	// 박재원 - 에이징 마스터(2차) - 암릿
			haCastleSkillUseFlag = 1;
			UseAgingMaster(3);
			break;
		case 114:	// 박재원 - 에이징 마스터(2차) - 장갑
			haCastleSkillUseFlag = 1;
			UseAgingMaster(4);
			break;
		case 115:	// 박재원 - 에이징 마스터(2차) - 부츠
			haCastleSkillUseFlag = 1;
			UseAgingMaster(5);
			break;

		case 116:	// 장별 - 그라비티 스크롤

			if( sinChar->GravityScroolCheck[0] == 5 ) 
			{
				cMessageBox.ShowMessage(MESSAGE_GRAVITYSCROOLFAIL);
				return FALSE;
			}

			cMessageBox.ShowMessage(MESSAGE_GRAVITYSCROOLOK);

			sinChar->GravityScroolCheck[0] += 1;

			
			cCharStatus.UseGravityScrool();
			cInvenTory.SetItemToChar();
			ReformCharForm();

			haCastleSkillUseFlag = 1;
			
		break;


		case 117:	// 장별 - 빌링 도우미 펫 추가(테리 1시간) 
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_TERRY, SINITEM_TIME_1HOURS, true, UpKeepItemName[7], 30, 3);
			sinChar->GravityScroolCheck[1] = 1;
			break;
		case 118:	// 장별 - 빌링 도우미 펫 추가(넵시스 1시간)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_NEPSYS, SINITEM_TIME_1HOURS, true, UpKeepItemName[8], 30, 3);
			break;
		case 119:	// 장별 - 빌링 도우미 펫 추가(이오 1시간)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_IO, SINITEM_TIME_1HOURS, true, UpKeepItemName[9], 30, 3);
			break;
		case 120:	// 장별 - 빌링 도우미 펫 추가(무트 1시간)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::HELP_PET_MUTE, SINITEM_TIME_1HOURS, true, UpKeepItemName[10], 30, 3); 
			sinChar->GravityScroolCheck[1] = 2;
		break;

		case 121:   // 장별 - 써드 아이즈(1시간)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::THIRD_EYES,SINITEM_TIME_1HOURS,true,UpKeepItemName[0], 50);
			
		break;

		case 122: // 장별 - 슈퍼 에이징 스톤 1.5
			haCastleSkillUseFlag = 0;
		break;

		case 123:   // 장별 - 경험치증가포션(1시간)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::EXPUP_POTION,SINITEM_TIME_1HOURS,true,UpKeepItemName[1], 50);
		break;

		case 124:  // 장별 - 뱀피릭 커스핏(1시간)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS,SINITEM_TIME_1HOURS,true,UpKeepItemName[2]);
			SetVampiricCuspidTime(SINITEM_TIME_1HOURS);
		break;
		
		case 125:  // 장별 - 마나 리차징 포션(1시간)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::MANA_RECHAR_P,SINITEM_TIME_1HOURS,true,UpKeepItemName[3]);
			SetManaRechargingPTime(SINITEM_TIME_1HOURS);
		break;

		case 126:	// 장별 - 마나 리듀스(1시간)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::MANA_REDUCE_P, SINITEM_TIME_1HOURS, true, UpKeepItemName[5], 30 );
		break;

		case 127:  // 장별 - 뱀피릭 커스핏 EX
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS_EX,SINITEM_TIME_1HOURS,true,UpKeepItemName[11]); 
			SetVampiricCuspidEXTime(SINITEM_TIME_1HOURS);
		break;

		case 128:  // 장별 - 뱀피릭 커스핏 EX
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS_EX,SINITEM_TIME_3HOURS,true,UpKeepItemName[11]);
			SetVampiricCuspidEXTime(SINITEM_TIME_3HOURS);
		break;

		case 129:  // 장별 - 뱀피릭 커스핏 EX
			haCastleSkillUseFlag = 1;
			SetUpKeepItem(nsPremiumItem::VAMPIRIC_CUS_EX,SINITEM_TIME_ONEDAY,true,UpKeepItemName[11]);
			SetVampiricCuspidEXTime(SINITEM_TIME_ONEDAY);
		break;
		case 130:	// 석지용 - 믹스쳐 리셋 스톤
			haCastleSkillUseFlag = 0;
			break;
		case 131: // 박재원 - 리스펙 스톤
			haCastleSkillUseFlag = 0;
			break;
		case 132: // 박재원 - 근력 리듀스 포션(1일)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::STAMINA_REDUCE_P, SINITEM_TIME_ONEDAY, true, UpKeepItemName[12], 30 ); //SINITEM_TIME_ONEDAY
			break;
		case 133: // 박재원 - 근력 리듀스 포션(7일)
			haCastleSkillUseFlag = 1;
			SetUpKeepItem( nsPremiumItem::STAMINA_REDUCE_P, SINITEM_TIME_SEVENDAY, true, UpKeepItemName[12], 30 ); //SINITEM_TIME_SEVENDAY
			break;
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*Desc: 스킬 게이지가 생성돼는  아이템일경우 호출	
*-----------------------------------------------------------------------------*/
int cHaPremiumItem::SetPremiumItemSkill(int kind)
{

	haCastleSkillUseFlag =0;
	DWORD SkillCODE;
	int   SkillTime;
	switch(kind){
		case 1:
			SkillCODE = SCROLL_P_INVULNERABILITY;
			SkillTime = 30;
		break;	
		case 2:
			SkillCODE = SCROLL_P_CRITICAL;
			SkillTime = 60*60;//60*10;	//pluto 1시간으로 증가
		break;
		case 3:
			SkillCODE = SCROLL_P_EVASION;
			SkillTime = 60*60;//60*10;	//pluto 1시간으로 증가
		break;
	}
	//해당 돼는 아이템이 맞으면 아이템스킬을 세팅한다.
	sSKILL TempSkill;

    if(cSkill.SearchContiueSkillCODE(SkillCODE)==SkillCODE && SkillCODE != 0){
			cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
			haCastleSkillUseFlag = 0;
			return TRUE;
	}
	haCastleSkillUseFlag =1;

	for(int j = 0 ; j < SIN_MAX_SKILL; j++){
		if(sSkill[j].CODE == SkillCODE){
			memcpy(&TempSkill,&sSkill[j],sizeof(sSKILL));
			TempSkill.UseTime=SkillTime;
			sinContinueSkillSet(&TempSkill);
			SwitchSkill(&TempSkill);
			break;
		}
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*Desc: 텔레포트 코어 사용시 호출						
*-----------------------------------------------------------------------------*/
int cHaPremiumItem::UseTeleportScrollItem(short ItemIndex)
{	
	if(!chaPremiumitem.TelePortCore.FieldIndex[1])return FALSE;

	if ( StageField[lpCurPlayer->OnStageField]->State==FIELD_STATE_ROOM )		// 알까기 맵에서 텔레포트 코어 막는거
	{
		cMessageBox.ShowMessage(MESSAGE_NO_USE_ITEM); //텔레포트 불가
		return FALSE;
	}

	int i;
	for(i=0;i<TELEPORT_FIELDMAX;i++)
	{
		if((chaPremiumitem.TelePortCore.FieldIndex[1]-1) == TelePort_FieldNum[i][0]){

			if(TelePort_FieldNum[i][2] <= sinChar->Level) // 장별 - 필드 레벨 제한 해제 이벤트 종료시 원복
			{
			//	if( i < 10 || sinChar->Level > 19 )		// <2010.04.29> 석지용 - 제벨제한 없는 필드면 워프 or 레벨제한 있는 필드(던전)이면 레벨20부터 워프 // 장별 - 필드 레벨 제한 해제 이벤트
			//	{
					WarpField2( TelePort_FieldNum[i][1]);              //워프한다.
					cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex].sItemInfo.PotionCount = 300;
					sinThrowItemToFeild(&cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex]);
					cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex].Flag = 0;
					cInvenTory.CheckWeight();//무게를 보정해준다
					cInvenTory.ReFormInvenItem();
			//	}
			}

			else
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_LEVEL); //레벨로 인해 이동할수 없다.
		}
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*Desc: 다른 인터페이스창이 떠잇을경우 리턴한다.		
*-----------------------------------------------------------------------------*/
int cHaPremiumItem::CheckWindowOpen()
{
	haCastleSkillUseFlag = 0;
	if(cWareHouse.OpenFlag)return false;
	if(cTrade.OpenFlag)return false;
	if(cAging.OpenFlag)return false;
	if(cCraftItem.OpenFlag)return false;
	if(sSinWarpGate.ShowFlag)return false;
	if(cSinHelp.NPCTeleportFlag)return false;
	if(isDrawClanMenu)return false; //클랜메뉴가 있을때는 리턴한다  
	if(haMovieFlag)return false;
	// pluto 제련
	if( SmeltingItem.OpenFlag )
	{
		return false;
	}
	// pluto 제작
	if( ManufactureItem.m_OpenFlag )
	{
		return false;
	}
	if(cMixtureReset.OpenFlag)	return false;	// 석지용 - 믹스쳐 리셋 추가
	return true;
}
/*----------------------------------------------------------------------------*
*Desc: 빈배열을 댕겨준다.		
*-----------------------------------------------------------------------------*/
int cHaPremiumItem::CheckUpKeepItem()
{
	int i;
	//아이템체크
	for( i = 0 ; i < SINUPKEEPITEM_MAX ; i++ ){
		if(UpKeepItem[i].Visible == false){
			if(UpKeepItem[i+1].Visible == true){
				memcpy(&UpKeepItem[i],&UpKeepItem[i+1],sizeof(sUpKeepItem));
				UpKeepItem[i+1].Visible = false;
				break;
			}			
		}
	}
	return true;
}
/*----------------------------------------------------------------------------*
*Desc: 유지형 소모성 아이템을 사용할 경우 디스플레이  	
*-----------------------------------------------------------------------------*/
int cHaPremiumItem::SetUpKeepItem(int kind,DWORD dwTime,bool visible,char* id, int Percent , short ItemType)
{
	haCastleSkillUseFlag = 0;
	int i;

	for( i = 0 ; i < SINUPKEEPITEM_MAX ; i++)
	{
		if( m_VampiricCuspidEXTime > 0 && UpKeepItem[i].Visible == false)
		{
			if( UpKeepItem[i].TGAImageNumber == VAMPIRIC_CUS_EX ) 
			{
				UpKeepItem[i].TGAImageNumber = 0;
				UpKeepItem[i].Visible = false;
				haCastleSkillUseFlag = 0;
			//	return FALSE;
			}
		}

		if( (UpKeepItem[i].TGAImageNumber == VAMPIRIC_CUS_EX || UpKeepItem[i].TGAImageNumber == VAMPIRIC_CUS) && ( m_VampiricCuspidEXTime > 0 || m_VampiricCuspidTime > 0)) 
		{
			if( kind == 3 || kind == 12 )	
			{
					cMessageBox.ShowMessage(MESSAGE_ASATTRIBUTE_USE);
					haCastleSkillUseFlag = 0;
					return  FALSE;
			}			
		}
	}

	
	
	for( i = 0 ; i < SINUPKEEPITEM_MAX ; i++)
	{
		 if( UpKeepItem[i].Visible == false )
		{

			UpKeepItem[i].TGAImageNumber = kind;     //이미지 인덱스
			UpKeepItem[i].Visible        = true;
			UpKeepItem[i].IconTime[0]    = 1;
			UpKeepItem[i].IconTime[1]    = GetPlayTime_T() + dwTime;
			UpKeepItem[i].Alpha          = 0;
			UpKeepItem[i].Alphakind      = 0;
			UpKeepItem[i].Per	         = Percent;	//퍼센트 옵션을 찍기위해 추가 
			
			strcpy(UpKeepItem[i].Id,id);
			haCastleSkillUseFlag = 1;
			return TRUE;
		}
		else{

		

			/*
				ItemType  0 일반 아이템 
				ItemType  1 packge 아이템 
			*/
			switch( ItemType ){
				case 0:
					if(UpKeepItem[i].TGAImageNumber == kind){
						cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
						haCastleSkillUseFlag = 0;
						return FALSE;
					}

				break;
				case 1:
					for( int j = 0 ; j < SINUPKEEPITEM_MAX ; j++){
						if( UpKeepItem[j].TGAImageNumber  == THIRD_EYES || UpKeepItem[j].TGAImageNumber  == EXPUP_POTION ){
							cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
							haCastleSkillUseFlag = 0;
							return  FALSE;
						}
					}
				break;
				case 2:		// pluto  마나 리듀스 포션 패키지2
					for( int j = 0 ; j < SINUPKEEPITEM_MAX ; j++){
						if( UpKeepItem[j].TGAImageNumber  == MANA_REDUCE_P || UpKeepItem[j].TGAImageNumber  == EXPUP_POTION ){
							cMessageBox.ShowMessage(MESSAGE_CLANSKILL_USE);
							haCastleSkillUseFlag = 0;
							return  FALSE;
						}
					}
				break;
				case 3:		// 박재원 - 빌링 도우미 펫 추가
					for( int j = 0 ; j < SINUPKEEPITEM_MAX ; j++)
					{
						//	if( UpKeepItem[j].TGAImageNumber == HELP_PET_NEPSYS || UpKeepItem[j].TGAImageNumber == HELP_PET_IO ||
						//		UpKeepItem[j].TGAImageNumber == HELP_PET_TERRY  || UpKeepItem[j].TGAImageNumber == HELP_PET_MUTE )
						if(cHelpPet.PetShow == 1)
						{
							cMessageBox.ShowMessage(MESSAGE_ASATTRIBUTE_USE);
							haCastleSkillUseFlag = 0;
							return  FALSE;
						}
					}
				break;
			}
		}
	}
	return TRUE;
	
}
/*----------------------------------------------------------------------------*
*Desc: 유지형아이콘 설명박스 		
*-----------------------------------------------------------------------------*/
void cHaPremiumItem::InfoBox(int PoisX,int PosiY,int Width,int Height)
{
	int i,j;
	for(i = 0; i < Width ; i++){
		for( j = 0; j< Height ; j++){
			if(i == 0 && j == 0 )                               //좌측상단 
				dsDrawTexImage( cItem.MatItemInfoBox_TopLeft , PoisX+(i*16) , PosiY+(j*16), 16, 16 , 255 );
			if(j == 0 && i !=0 && i+1 < Width )                 //가운데
				dsDrawTexImage( cItem.MatItemInfoBox_TopCenter , PoisX+(i*16) , PosiY+(j*16), 16, 16 , 255 );
			if(j == 0 && i+1 == Width)                          //우측상단
				dsDrawTexImage( cItem.MatItemInfoBox_TopRight , PoisX+(i*16) , PosiY+(j*16), 16, 16 , 255 );
			if(i == 0 && j != 0 && j+1 != Height)               //좌측 줄거리 
				dsDrawTexImage( cItem.MatItemInfoBox_Left , PoisX+(i*16) , PosiY+(j*16), 16, 16 , 255 );
			if(i != 0 && j != 0 && i+1 !=Width && j+1 !=Height) //가운데 토막
				dsDrawTexImage( cItem.MatItemInfoBox_Center , PoisX+(i*16) , PosiY+(j*16), 16, 16 , 255 );
			if(i+1 == Width && j != 0 && j+1 != Height)         //우측 줄거리 
				dsDrawTexImage( cItem.MatItemInfoBox_Right , PoisX+(i*16) , PosiY+(j*16), 16, 16 , 255 );				
			if(i == 0 && j+1 == Height)                         //밑바닥 왼쪽
				dsDrawTexImage( cItem.MatItemInfoBox_BottomLeft , PoisX+(i*16) , PosiY+(j*16), 16, 16 , 255 );
			if(i != 0 && j+1 == Height && i+1 !=Width)          //밑바닥 가운데
				dsDrawTexImage( cItem.MatItemInfoBox_BottomCenter , PoisX+(i*16) , PosiY+(j*16), 16, 16 , 255 );
			if(j+1 == Height && i+1 ==Width)                    //밑바닥 오른쪽 
				dsDrawTexImage( cItem.MatItemInfoBox_BottomRight , PoisX+(i*16) , PosiY+(j*16), 16, 16 , 255 );
		}
	}
}
/*----------------------------------------------------------------------------*
*Desc: 유지형아이콘 설명(이름/유지시간 ) 		
*-----------------------------------------------------------------------------*/
int cHaPremiumItem::DrawText()
{
	HDC	hdc;
	renderDevice.lpDDSBack->GetDC(&hdc);
	SelectObject( hdc, sinBoldFont);
	SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, RGB(255,255,255) );  
	char strBuff[32];
	memset(strBuff,0,sizeof(strBuff));
	int i,cnt = 0;
	for( i = 0 ; i < SINUPKEEPITEM_MAX ; i++ ){
		if(cSinHelp.sinGetHelpShowFlag())break;
		if(!CheckWindowOpen())break;
		if(UpKeepItem[i].Visible == true){
			if(UpKeepItem[i].Infoflag == true){
				dsTextLineOut(hdc,UpKeepItem[i].PosiX+50,UpKeepItem[i].PosiY+20,UpKeepItem[i].Id,strlen(UpKeepItem[i].Id));
				SelectObject( hdc, sinFont);
				SetTextColor( hdc, RGB(50,250,50) ); 
				switch(UpKeepItem[i].TGAImageNumber){
					case nsPremiumItem::THIRD_EYES:   ///써드 아이즈
						wsprintf(strBuff,UpKeepItemDoc[1],UpKeepItem[i].Per,"%");						
					break;
					case nsPremiumItem::EXPUP_POTION: ///경험치 증가 포션
						wsprintf(strBuff,UpKeepItemDoc[2],UpKeepItem[i].Per,"%");						
					break;
					case nsPremiumItem::VAMPIRIC_CUS:
						wsprintf(strBuff,UpKeepItemDoc[4]);						
					break;
					case nsPremiumItem::MANA_RECHAR_P:
						wsprintf(strBuff,UpKeepItemDoc[5]);						
					break;
					case nsPremiumItem::MIGHT_OF_AWELL:	// pluto 마이트 오브 아웰
						wsprintf( strBuff, UpKeepItemDoc[6], UpKeepItem[i].Per );
						break;
					case nsPremiumItem::MANA_REDUCE_P:		// pluto 마나 리듀스 포션
						wsprintf( strBuff, UpKeepItemDoc[7], UpKeepItem[i].Per, "%" );
						break;
					case nsPremiumItem::HELP_PET_TERRY:		// 박재원 - 빌링 도우미 펫 추가
						wsprintf( strBuff, UpKeepItemDoc[8]);
						break;
					case nsPremiumItem::HELP_PET_NEPSYS:		// 박재원 - 빌링 도우미 펫 추가
						wsprintf( strBuff, UpKeepItemDoc[9]);
						break;
					case nsPremiumItem::HELP_PET_IO:		// 박재원 - 빌링 도우미 펫 추가
						wsprintf( strBuff, UpKeepItemDoc[10]);
						break;
					case nsPremiumItem::HELP_PET_MUTE:		// 박재원 - 빌링 도우미 펫 추가
						wsprintf( strBuff, UpKeepItemDoc[11]);
						break;
					case nsPremiumItem::VAMPIRIC_CUS_EX:		// 장별 - 뱀피릭 커스핏 EX
						wsprintf(strBuff,UpKeepItemDoc[12]);						
					break;
					case nsPremiumItem::STAMINA_REDUCE_P:		// 박재원 - 근력 리듀스 포션
						wsprintf( strBuff, UpKeepItemDoc[13], UpKeepItem[i].Per, "%" );
					break;
					
				
				}
				
				dsTextLineOut(hdc,UpKeepItem[i].PosiX+50,UpKeepItem[i].PosiY+20+30,strBuff,strlen(strBuff));  //첫번째 줄
				
				wsprintf(strBuff,UpKeepItemDoc[0],(UpKeepItem[i].IconTime[1]-UpKeepItem[i].IconTime[0])/60);
				dsTextLineOut(hdc,UpKeepItem[i].PosiX+50,UpKeepItem[i].PosiY+20+46,strBuff,strlen(strBuff));

							
			}
		}
	}

	renderDevice.lpDDSBack->ReleaseDC(hdc);
	return TRUE;
}
/*----------------------------------------------------------------------------*
*Desc: 헤어틴트포션 사용 		
*-----------------------------------------------------------------------------*/
int cHaPremiumItem::UseHairtintPotion(int ItemKind)
{
	switch(ItemKind){
		case 1:  //A형
			if( ChangeHairModel(0) )
				return TRUE;
		break;
		case 2:  //B형
			if( ChangeHairModel(1) )
				return TRUE;
		break;
		case 3:  //C형
			if( ChangeHairModel(2) )
				return TRUE;
		break;
		case 4:  //D형
			if( ChangeHairModel(3) )
				return TRUE;
		break;
		case 5:  //E형
			if( ChangeHairModel(4) )
				return TRUE;
		break;
		case 6:  //F형
			if( ChangeHairModel(5) )
				return TRUE;
		break;
		case 7:  //G형
			if( ChangeHairModel(6) )
				return TRUE;
		break;
		case 8:  //H형
			if( ChangeHairModel(7) )
				return TRUE;
		break;
			
		case 9:  //I형
			if( ChangeHairModel(8) )
				return TRUE;
		break;
		case 10:  //J형
			if( ChangeHairModel(9) )
				return TRUE;
		break;
		case 11:  //K형
			if( ChangeHairModel(10) )
				return TRUE;
		break;
		case 12:  //L형
			if( ChangeHairModel(11) )
				return TRUE;
		break;
		case 13:  //M형
			if( ChangeHairModel(12) )
				return TRUE;
		break;
		

	}	
	cMessageBox.ShowMessage(MESSAGE_NOT_HAIRTINTPOTION); //같은머리능 사용할수 없습니다.
	return FALSE; 
}

// 박재원 - 에이징 마스터 아이템 사용
int cHaPremiumItem::UseAgingMaster(int ItemKind)
{
	switch(ItemKind)
	{
	case 0:
		sinCheckAgingLevel(SIN_AGING_ATTACK, true);
		sinCheckAgingLevel(SIN_AGING_CRITICAL, true);
		ReformCharForm(); //재인증 
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	case 1:
		if((cInvenTory.InvenItem[sInven[1].ItemIndex-1].CODE &sinITEM_MASK2) == sinDS1)
		{
			sinCheckAgingLevel(SIN_AGING_BLOCK, true);
			ReformCharForm(); //재인증 
			cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		}
		else if((cInvenTory.InvenItem[sInven[1].ItemIndex-1].CODE &sinITEM_MASK2) == sinOM1)
		{
			sinCheckAgingLevel(SIN_AGING_DEFENSE_ORB, true);
			ReformCharForm(); //재인증 
			cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		}
		break;
	case 2:
		sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMOR, true);
		ReformCharForm(); //재인증 
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	case 3: // 박재원 - 에이징 마스터(2차) - 암릿
		sinCheckAgingLevel(SIN_AGING_DEFENSE_ARMLETS, true);
		ReformCharForm(); //재인증 
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	case 4: // 박재원 - 에이징 마스터(2차) - 장갑
		sinCheckAgingLevel(SIN_AGING_DEFENSE_GLOVES, true);
		ReformCharForm(); //재인증 
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	case 5: // 박재원 - 에이징 마스터(2차) - 부츠
		sinCheckAgingLevel(SIN_AGING_DEFENSE_BOOTS, true);
		ReformCharForm(); //재인증 
		cMessageBox.ShowMessage(MESSAGE_AGING_MATURE_SUCCESS);
		break;
	}

	return TRUE;
}

// 박재원 - 스킬 마스터 아이템 사용
int cHaPremiumItem::UseSkillMaster(int ItemKind)
{
	switch(ItemKind)
	{
	case 1:
		for(int j=1 ; j<5 ; j++) // 1차 전직후 생기는 스킬
		{
			if(sinSkill.UseSkill[j].UseSkillCount<10000)
			{
				if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
				{
					sinSkill.UseSkill[j].UseSkillCount += 10000;
					cSkill.ReformSkillMasteryForm(0,j); //데이타를 갱신한다
				}
			}
		}
		cMessageBox.ShowMessage(MESSAGE_SKILL_MATURE_SUCCESS);
		sinPlaySound(SIN_SOUND_EAT_POTION2);//대박 사운드
		sinEffect_Agony(lpCurPlayer);
		break;
	case 2:
		for(int j=5 ; j<9 ; j++) // 2차 전직후 생기는 스킬
		{
			if(sinSkill.UseSkill[j].UseSkillCount<10000)
			{
				if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
				{
					sinSkill.UseSkill[j].UseSkillCount += 10000;
					cSkill.ReformSkillMasteryForm(0,j); //데이타를 갱신한다
				}
			}
		}
		cMessageBox.ShowMessage(MESSAGE_SKILL_MATURE_SUCCESS);
		sinPlaySound(SIN_SOUND_EAT_POTION2);//대박 사운드
		sinEffect_Agony(lpCurPlayer);
		break;
	case 3:
		for(int j=9 ; j<13 ; j++) // 3차 전직후 생기는 스킬
		{
			if(sinSkill.UseSkill[j].UseSkillCount<10000)
			{
				if(sinSkill.UseSkill[j].Flag && sinSkill.UseSkill[j].Point)
				{
					sinSkill.UseSkill[j].UseSkillCount += 10000;
					cSkill.ReformSkillMasteryForm(0,j); //데이타를 갱신한다
				}
			}
		}
		cMessageBox.ShowMessage(MESSAGE_SKILL_MATURE_SUCCESS);
		sinPlaySound(SIN_SOUND_EAT_POTION2);//대박 사운드
		sinEffect_Agony(lpCurPlayer);
		break;
	}

	return TRUE;
}

// 박재원 - 이동 상점 아이템
int cHaPremiumItem::UseMoveShop()
{
	if(cShop.OpenFlag == SIN_CLOSE)
	{
		sinShopKind = 1;
		cShop.OpenFlag = SIN_OPEN; 
		cShop.UseItemFlag = 1;
	}
	else
	{
		cShop.OpenFlag = SIN_CLOSE;
		cShop.UseItemFlag = 0;
	}

	return TRUE;
}
