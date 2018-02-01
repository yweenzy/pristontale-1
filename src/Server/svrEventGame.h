
#define _EVENT_GAME_
//#define _EVENT_GAME_STATE_INIT
//#define _EVENT_GAME_CHUSUK_GIFT
//#define _EVENT_GAME_ATTENDANCE
//#define _EVENT_PCBANG_ATTENDANCE_
//#define _EVENT_GAME_SEOLLAL_GIFT
//#define _EVENT_GAME_CHRISTMAS_

#ifdef _EVENT_GAME_

#define NPC_NUM			2
#define REVEDUSER_MAX	5000

static int rsFlag_rsFiltChatMsg = 0;

struct rsEVENT_REVEDUSER {
	DWORD	dwIDCode;
	char	szID[32];
};

static int rsHopeEventNpcPos[][3] = {
    //field, x좌표,  z좌표  
	///// PC방, 출석, 재분배 이벤트할때는 물품 교부처 NPC만 사용한다.
	{ 3 , 2419 , -16324 }, // : 크리스  [0] 리카르텐
	{ 0 , 0 , 0 }, // : 크리스  [1]
	{ 0,0,0 }               //						  [2]

};


// 장별 - 재분배 이벤트
extern char *StateInitEvent1;
extern char *StateInitEvent2;
extern char *StateInitEvent3;
extern char *StateInitEvent4;


	
	///////////////////////////////////////// 박재원 : 재분배 이벤트 ///////////////////////////////////////////////////////    // 장별 - 재분배 이벤트 
	#ifdef _EVENT_GAME_STATE_INIT
	extern char *szEvent_HopeMsg_StateInit;  // "재분배 하고 싶어요"  // "신필드 구경하러 왔어요" - 신규필드 끝없는 탑 3층 업데이트 기념 이벤트

	rsEVENT_REVEDUSER rsEventUser_RecedList_StateInit[REVEDUSER_MAX];
	int rsEventUser_RecvedCount_StateInit = 0;
	#endif



#endif


// 일정지역 범위안에서 특정 문자열 필터링
int sveFiltChatMsg( rsPLAYINFO *lpPlayInfo , char *szMsg , int len )
{
#ifdef _EVENT_GAME_

	int x=0;
	int z=0;
	int dist=0;
	int cnt=0;


	#ifdef _EVENT_GAME_STATE_INIT  // 재분배 이벤트 // 장별 - 재분배 이벤트
	cnt = 0;	// 신규필드 끝없는 탑 3층 업데이트 기념 이벤트
	while(1){
		if ( rsHopeEventNpcPos[cnt][0]==0 ) break;
		if ( lpPlayInfo->Position.Area==rsHopeEventNpcPos[cnt][0] ) 
		{
			x = abs(lpPlayInfo->Position.x/fONE - rsHopeEventNpcPos[cnt][1]);
			z = abs(lpPlayInfo->Position.z/fONE - rsHopeEventNpcPos[cnt][2]);
			dist = x*x+z*z;
			if ( dist<150*150 ) 
			{
				if ( strstr( szMsg , szEvent_HopeMsg_StateInit )>0 ) 
				{
					smTRANS_COMMAND smTransCommand;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.code = smTRANSCODE_EVENT_GAME;
					smTransCommand.WParam = smCODE_EVENT_STATE_INIT;
					smTransCommand.SParam = lpPlayInfo->Position.Area;
					smTransCommand.LParam = rsServerConfig.ServerCode;
					rsSendDataServer( lpPlayInfo->lpsmSock , &smTransCommand );  // 로그인 서버로 보내준다
					break;
				}
			}
		}
		cnt++;
	}
	#endif // 재분배 이벤트
	

	


#endif

	return TRUE;
}




// 재분배 스탯 초기화(블루스톤 아이템 지급)
int rsEventGame_State_Init (rsPLAYINFO *lpPlayInfo , smTRANS_COMMAND *lpTransCommand)
{
#ifdef _EVENT_GAME_STATE_INIT

	SYSTEMTIME	st;
	GetLocalTime( &st );
/*
	if ( rsServerConfig.TestSeverMode ) 
	{
		if ( lpPlayInfo->AdminMode<2 && (st.wYear!=2009 || st.wMonth!=4 || st.wDay<16 || st.wDay>22) ) //이벤트 조건 ( 날짜 조건에 맞아야 됨 )
			return FALSE;
	}
	else 
	{
		if ( lpPlayInfo->AdminMode<2 && (st.wYear!=2009 || st.wMonth!=4 || st.wDay<16 || st.wDay>22) ) //이벤트 조건 ( 날짜 조건에 맞아야 됨 )
			return FALSE;
	}
*/	

	TRANS_CHATMESSAGE	TransChatMessage;
	int cnt;

	if ( rsEventUser_RecvedCount_StateInit>=REVEDUSER_MAX ) { // 장별 - 재분배 이벤트
	//	wsprintf( TransChatMessage.szMessage , "물품교부처: 준비된 아이템이 전부 팔려버렸네.. ㅠ.ㅠ" );
		wsprintf( TransChatMessage.szMessage , "%s", StateInitEvent1 ); // 신규필드 끝없는 탑 3층 업데이트 기념 이벤트
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 1;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );
		return FALSE;
	}


	for(cnt=0;cnt<rsEventUser_RecvedCount_StateInit;cnt++) { // 장별 - 재분배 이벤트
		if ( lpPlayInfo->dwCode_ID==rsEventUser_RecedList_StateInit[cnt].dwIDCode && lstrcmpi(lpPlayInfo->szID,rsEventUser_RecedList_StateInit[cnt].szID)==0 )
		{
			//이미 받았다
		//	wsprintf( TransChatMessage.szMessage , "물품교부처: 자네는 이미 받았다네~ 또 원하거든 아이템샵으로 가보게! " );
			wsprintf( TransChatMessage.szMessage , "%s", StateInitEvent2 ); // 신규필드 끝없는 탑 3층 업데이트 기념 이벤트
			TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
			TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
			TransChatMessage.dwIP = 1;
			TransChatMessage.dwObjectSerial = 0;
			lpPlayInfo->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );

			return FALSE;
		}
	}

	//우편함 비활성화된경우 활성화 시킴
	if ( !lpPlayInfo->lpPostBoxItem ) rsLoadPostBox(lpPlayInfo);
	//if ( !lpPlayInfo->lpPostBoxItem ) return FALSE;
	if ( lpPlayInfo->lpPostBoxItem && lpPlayInfo->lpPostBoxItem->ItemCounter>POST_ITEM_MAX-1 ) return FALSE;


	rsPOST_BOX_ITEM		*lpPostBox = new rsPOST_BOX_ITEM;
	if ( !lpPostBox ) return FALSE;

	ZeroMemory( lpPostBox , sizeof(rsPOST_BOX_ITEM) );

	
	lpPostBox->PostItem[0].dwItemCode = (sinBI1|sin02); // 신규필드 끝없는 탑 3층 업데이트 기념 이벤트
	lpPostBox->PostItem[0].Flag++;
	lstrcpy( lpPostBox->PostItem[0].szCharName , "***" );
	lstrcpy( lpPostBox->PostItem[0].szDoc , StateInitEvent3 );	// 신규필드 끝없는 탑 3층 업데이트 기념 이벤트
//	lstrcpy( lpPostBox->PostItem[0].szDoc , "스킬 재분배 이벤트" );
	lstrcpy( lpPostBox->PostItem[0].szFormCode , "0" );
	lstrcpy( lpPostBox->PostItem[0].szItemCode , "BI102" ); // 신규필드 끝없는 탑 3층 업데이트 기념 이벤트
	lstrcpy( lpPostBox->PostItem[0].szSpeJob , "0" );
	

	if(lpPlayInfo->lpPostBoxItem) {
		memcpy( &lpPostBox->PostItem[1] , &lpPlayInfo->lpPostBoxItem->PostItem[0] , sizeof(_POST_BOX_ITEM)*lpPlayInfo->lpPostBoxItem->ItemCounter );
		lpPostBox->ItemCounter = lpPlayInfo->lpPostBoxItem->ItemCounter+1;
		lpPostBox->dwHead = lpPlayInfo->lpPostBoxItem->dwHead;

		delete lpPlayInfo->lpPostBoxItem ;
		lpPlayInfo->lpPostBoxItem  = lpPostBox;
	}
	else {
		lpPostBox->ItemCounter = 1;
		lpPlayInfo->lpPostBoxItem  = lpPostBox;
	}


	rsEventUser_RecedList_StateInit[rsEventUser_RecvedCount_StateInit].dwIDCode = lpPlayInfo->dwCode_ID;
	lstrcpy(rsEventUser_RecedList_StateInit[rsEventUser_RecvedCount_StateInit].szID,lpPlayInfo->szID );
	rsEventUser_RecvedCount_StateInit++;


	//성공 ++ 아이템 지급
//	wsprintf( TransChatMessage.szMessage , "물품교부처: 자네의 소원을 들어주겠네~ 그대의 스킬을 신중하게 분배하도록 하게나 " );
	wsprintf( TransChatMessage.szMessage , "%s", StateInitEvent4 );
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32+lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 1;
	TransChatMessage.dwObjectSerial = 0;
	lpPlayInfo->lpsmSock->Send( (char *)&TransChatMessage , TransChatMessage.size , TRUE );


	smTRANS_COMMAND smTransCommand;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_YAHOO_MOTION;
	lpPlayInfo->lpsmSock->Send2( (char *)&smTransCommand , smTransCommand.size , TRUE );

#endif

	return TRUE;


}

