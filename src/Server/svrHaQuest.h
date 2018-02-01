/*----------------------------------------------------------------------------*
*		신규 튜토리얼 퀘스트 보상아이템 주기			
*-----------------------------------------------------------------------------*/
	switch( lpTransCommand->WParam )
	{
		//피곤한 창고지기
		case HAQUEST_CODE_ELEMENTARY_A:
			if ( lpTransCommand->LParam==1 )
			{
				rsPutItem( lpPlayInfo , sinQT1|sin15 );			//빵 준다
			}

			if ( lpTransCommand->LParam==2 ) {					//보상 아이템 직업 별로 지급
				dwItemCode = 0;

				switch( lpPlayInfo->smCharInfo.JOB_CODE )
				{
				case JOBCODE_MECHANICIAN:
					dwItemCode = sinWC1|sin02;					
					break;
				case JOBCODE_FIGHTER:
					dwItemCode = sinWA1|sin02;					
					break;
				case JOBCODE_PIKEMAN:
					dwItemCode = sinWP1|sin02;					
					break;
				case JOBCODE_ARCHER:
					dwItemCode = sinWS1|sin02;
					break;
				case JOBCODE_KNIGHT:
					dwItemCode = sinWS2|sin02;				
					break;
				case JOBCODE_ATALANTA:
					dwItemCode = sinWT1|sin02;			
					break;
				case JOBCODE_PRIESTESS:
					dwItemCode = sinWM1|sin01;		
					break;
				case JOBCODE_MAGICIAN:
					dwItemCode = sinWM1|sin01;		
					break;
				}
				if ( dwItemCode )
				{
					rsPutItem( lpPlayInfo , dwItemCode ,lpPlayInfo->smCharInfo.JOB_CODE);
				}
#ifdef _BEGINNER_EVENT// 초보퀘스트 이벤트시 추가 방어구 증정(피곤한 창고지기)
				
				dwItemCode = 0;

				switch( lpPlayInfo->smCharInfo.JOB_CODE )
				{
				case JOBCODE_MECHANICIAN:
					dwItemCode = sinDA1|sin02;
					
					break;
				case JOBCODE_FIGHTER:
					dwItemCode = sinDA1|sin02;
					
					break;
				case JOBCODE_PIKEMAN:
					dwItemCode = sinDA1|sin02;
					
					break;
				case JOBCODE_ARCHER:
					dwItemCode = sinDA1|sin02;
					
					break;
				case JOBCODE_KNIGHT:
					dwItemCode = sinDA1|sin02;
					
					break;
				case JOBCODE_ATALANTA:
					dwItemCode = sinDA1|sin02;
					
					break;
				case JOBCODE_PRIESTESS:
					dwItemCode = sinDA2|sin02;
					
					break;
				case JOBCODE_MAGICIAN:
					dwItemCode = sinDA2|sin02;
					break;
				}
				if ( dwItemCode )
				{
					rsPutItem( lpPlayInfo , dwItemCode ,lpPlayInfo->smCharInfo.JOB_CODE);
				}
#endif
			}
			break;
		//두려운 기운
		case HAQUEST_CODE_ELEMENTARY_B:
			if ( lpTransCommand->LParam==2 ) {   //보상 아이템 암릿 
				rsPutItem( lpPlayInfo ,sinOA2|sin02,lpPlayInfo->smCharInfo.JOB_CODE);

#ifdef _BEGINNER_EVENT	//초보퀘스트 추가 아이템 지급 (두려운기운)
				rsPutItem( lpPlayInfo ,sinPL1|sin01,10);   //생
				rsPutItem( lpPlayInfo ,sinPS1|sin01,10);   //근
				rsPutItem( lpPlayInfo ,sinPM1|sin01,10);   //기	

				rsSendMoneyToUser(lpPlayInfo ,1000);		//돈
#endif
			}
			break;
		//사탕 배달
		case HAQUEST_CODE_ELEMENTARY_C:
			if ( lpTransCommand->LParam==1 )  //사탕을 주다.
			{
				rsPutItem( lpPlayInfo ,sinQT1|sin14);
			}
			if ( lpTransCommand->LParam==2 )  //보상 아이템 물약
			{
				rsPutItem( lpPlayInfo ,sinPL1|sin01,10);   //생
				rsPutItem( lpPlayInfo ,sinPS1|sin01,10);   //근
				rsPutItem( lpPlayInfo ,sinPM1|sin01,10);   //기

#ifdef _BEGINNER_EVENT
				rsPutItem( lpPlayInfo ,sinGP1|sin17);		//스켈레톤 크리스탈
				rsPutItem( lpPlayInfo ,sinGP1|sin17);		//스켈레톤 크리스탈
#endif
			}
			break;
		//고블린 동산
		case HAQUEST_CODE_ELEMENTARY_D:
			if ( lpTransCommand->LParam==2 )  //보상 아이템 젬  
			{
				rsPutItem( lpPlayInfo ,sinOA1|sin06,lpPlayInfo->smCharInfo.JOB_CODE);   //젬 아뮬렛
				rsPutItem( lpPlayInfo ,sinOR1|sin06,lpPlayInfo->smCharInfo.JOB_CODE);   //젬링
				rsPutItem( lpPlayInfo ,sinOR1|sin06,lpPlayInfo->smCharInfo.JOB_CODE);   //젬링			
			}
#ifdef	_BEGINNER_EVENT
			if ( lpTransCommand->LParam==2 )
			{					//보상 아이템 직업 별로 지급
				dwItemCode = 0;

				switch( lpPlayInfo->smCharInfo.JOB_CODE )
				{
				case JOBCODE_MECHANICIAN:
					dwItemCode = sinWC1|sin06;
					
					break;
				case JOBCODE_FIGHTER:
					dwItemCode = sinWA1|sin06;
					
					break;
				case JOBCODE_PIKEMAN:
					dwItemCode = sinWP1|sin06;
					
					break;
				case JOBCODE_ARCHER:
					dwItemCode = sinWS1|sin06;
					
					break;
				case JOBCODE_KNIGHT:
					dwItemCode = sinWS2|sin06;
					
					break;
				case JOBCODE_ATALANTA:
					dwItemCode = sinWT1|sin06;
					
					break;
				case JOBCODE_PRIESTESS:
					dwItemCode = sinWM1|sin06;
					
					break;
				case JOBCODE_MAGICIAN:
					dwItemCode = sinWM1|sin06;
					break;
				}
				if ( dwItemCode )
				{
					rsPutItem( lpPlayInfo , dwItemCode ,lpPlayInfo->smCharInfo.JOB_CODE);
				}
			}
#endif
			break;
		//언데드의 위협
		case HAQUEST_CODE_ELEMENTARY_E:
			if ( lpTransCommand->LParam==2 ) {  //보상 아이템 포스 
				rsPutItem( lpPlayInfo ,sinFO1|sin04);   //스파키 포스
				rsPutItem( lpPlayInfo ,sinFO1|sin04);   //스파키 포스
#ifdef _BEGINNER_EVENT
			rsPutItem( lpPlayInfo ,sinGP1|sin17);		//스켈레톤 크리스탈
			rsPutItem( lpPlayInfo ,sinGP1|sin17);		//스켈레톤 크리스탈
			rsPutItem( lpPlayInfo ,sinGP1|sin17);		//스켈레톤 크리스탈
			rsPutItem( lpPlayInfo ,sinGP1|sin17);		//스켈레톤 크리스탈
			rsPutItem( lpPlayInfo ,sinGP1|sin17);		//스켈레톤 크리스탈
#endif
			}
			break;
		//외눈박이 괴물
		case HAQUEST_CODE_ELEMENTARY_F:
			if ( lpTransCommand->LParam==2 )  //보상 아이템 물약
			{
				rsPutItem( lpPlayInfo ,sinPL1|sin03,20);   //생
				rsPutItem( lpPlayInfo ,sinPS1|sin03,20);   //근
				rsPutItem( lpPlayInfo ,sinPM1|sin03,20);   //기
#ifdef _BEGINNER_EVENT
				rsPutItem( lpPlayInfo ,sinBI2|sin01);		//브론즈 패키지(3시간)
#endif
			}
			break;
		//잃어버린 망치
		case HAQUEST_CODE_ELEMENTARY_G:
			if ( lpTransCommand->LParam==2 )  //보상 아이템 포스
			{
				rsPutItem( lpPlayInfo ,sinFO1|sin06);   //트랜스 포스
				rsPutItem( lpPlayInfo ,sinFO1|sin06);   //트랜스 포스

#ifdef	_BEGINNER_EVENT
				rsPutItem( lpPlayInfo ,sinBI1|sin13);   //경험치증가 포션(1일)
#endif
			}

#ifdef	_BEGINNER_EVENT
			if ( lpTransCommand->LParam==2 )
			{					//보상 아이템 직업 별로 지급
				dwItemCode = 0;

				switch( lpPlayInfo->smCharInfo.JOB_CODE )
				{
				case JOBCODE_MECHANICIAN:
					dwItemCode = sinWC1|sin11;
					
					break;
				case JOBCODE_FIGHTER:
					dwItemCode = sinWA1|sin11;
					
					break;
				case JOBCODE_PIKEMAN:
					dwItemCode = sinWP1|sin11;
					
					break;
				case JOBCODE_ARCHER:
					dwItemCode = sinWS1|sin11;
					
					break;
				case JOBCODE_KNIGHT:
					dwItemCode = sinWS2|sin11;
					
					break;
				case JOBCODE_ATALANTA:
					dwItemCode = sinWT1|sin11;
					
					break;
				case JOBCODE_PRIESTESS:
					dwItemCode = sinWM1|sin11;
					
					break;
				case JOBCODE_MAGICIAN:
					dwItemCode = sinWM1|sin11;
					break;
				}
				if ( dwItemCode )
				{
					rsPutItem( lpPlayInfo , dwItemCode ,lpPlayInfo->smCharInfo.JOB_CODE);
				}
			}
#endif
			break;
		case HAQUEST_CODE_FURYOFPHANTOM:
			if ( lpTransCommand->LParam==2 )
			{
				switch(lpTransCommand->SParam)  //선택한 무기를 준다.
				{
					case 1: //도끼
						rsPutItemUnique(lpPlayInfo ,sinWA1|sin20,lpPlayInfo->smCharInfo.JOB_CODE,ITEM_UNIQUE_CODE_QUEST);
					break;
					case 2: //클러
						rsPutItemUnique(lpPlayInfo ,sinWC1|sin20,lpPlayInfo->smCharInfo.JOB_CODE,ITEM_UNIQUE_CODE_QUEST);
					break;
					case 3: //해머
						rsPutItemUnique(lpPlayInfo ,sinWH1|sin21,lpPlayInfo->smCharInfo.JOB_CODE,ITEM_UNIQUE_CODE_QUEST);
					break;
					case 4: //창
						rsPutItemUnique(lpPlayInfo ,sinWP1|sin21,lpPlayInfo->smCharInfo.JOB_CODE,ITEM_UNIQUE_CODE_QUEST);
					break;
					case 5: //활
						rsPutItemUnique(lpPlayInfo ,sinWS1|sin22,lpPlayInfo->smCharInfo.JOB_CODE,ITEM_UNIQUE_CODE_QUEST);
					break;
					case 6: //검
						rsPutItemUnique(lpPlayInfo ,sinWS2|sin23,lpPlayInfo->smCharInfo.JOB_CODE,ITEM_UNIQUE_CODE_QUEST);
					break;
					case 7: //투창
						rsPutItemUnique(lpPlayInfo ,sinWT1|sin21,lpPlayInfo->smCharInfo.JOB_CODE,ITEM_UNIQUE_CODE_QUEST);
					break;
					case 8: //완드
						rsPutItemUnique(lpPlayInfo ,sinWM1|sin21,lpPlayInfo->smCharInfo.JOB_CODE,ITEM_UNIQUE_CODE_QUEST);
					break;				
				}
			}
			break;
	}

	//lpPlayInfo->dwHaQuestItemCount ++;
