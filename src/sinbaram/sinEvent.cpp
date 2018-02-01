/*----------------------------------------------------------------------------*
*	파일명 :  sinEvent.cpp	
*	하는일 :  신바람 이벤트 
*	작성일 :  최종업데이트 2002년 9월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"

/*----------------------------------------------------------------------------*			
*							전역 변수 						
*-----------------------------------------------------------------------------*/	
//이벤트 설명 파일의 경로 
char *EvnetDocFilePath[] ={
	"image\\Sinimage\\Event\\SmashTV.sin",
	

};
/*----------------------------------------------------------------------------*
*
*-----------------------------------------------------------------------------*/	
int sinShowEventSmashingTV()
{
	HelpBoxKindIndex = SIN_EVENT_SMASHTV;
	cSinHelp.sinShowHelp(SIN_HELP_KIND_SMASHTV,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y, RGBA_MAKE(0,15,128,125),EvnetDocFilePath[0]);  

	return TRUE;
}

int sinSendEventItem(int Send) //서버로 이벤트 아이템을 보낸다 (1 서버로보냄 0은 검색)
{
	int MessageFlag = 0;
	for(int i= 0 ; i < INVENTORY_MAXITEM ; i++){
		if(cInvenTory.InvenItem[i].Flag){
			if( (cInvenTory.InvenItem[i].sItemInfo.CODE & sinITEM_MASK2 )== sinGP1 ){
				if(Send){
					SendUseItemCodeToServer(&cInvenTory.InvenItem[i].sItemInfo);
					cInvenTory.InvenItem[i].Flag = 0;
					cInvenTory.ReFormInvenItem();
					ResetInvenItemCode();
					MessageFlag = 1;
				}
				else return TRUE;
			}

		}
		if(cInvenTory.InvenItemTemp[i].Flag){
			if( (cInvenTory.InvenItemTemp[i].sItemInfo.CODE & sinITEM_MASK2 )== sinGP1 ){
				if(Send){
					SendUseItemCodeToServer(&cInvenTory.InvenItemTemp[i].sItemInfo);
					cInvenTory.InvenItemTemp[i].Flag = 0;
					cInvenTory.ReFormInvenItem();
					ResetInvenItemCode();
					MessageFlag = 1;
				}
				else return TRUE;
					
			}
		}
	}
	if(Send){
		if(MessageFlag){
			cMessageBox.ShowMessage(MESSAGE_GYUNGFUM_OK);

		}
	}
	else return FALSE;

	return FALSE;
}

