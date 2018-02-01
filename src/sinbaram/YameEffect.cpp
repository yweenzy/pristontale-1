/*----------------------------------------------------------------------------*
*	파일명 :  AssaEffect.cpp	
*	하는일 :  이펙트 
*	작성일 :  최종업데이트 2002년 11월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"

/*----------------------------------------------------------------------------*
*							전역 변수 
*-----------------------------------------------------------------------------*/	

cYAMEEFFECT *cYameEffect[YAMEEFFECT_MAX];  //이펙트 버퍼 
sinEFFECT_ZDEPTH sinEffect_Zdepth4[YAMEEFFECT_MAX];//소팅을 위한 인덱스 구조체 
int Yame;

/*----------------------------------------------------------------------------*
*							Key Down
*-----------------------------------------------------------------------------*/	
void YameEffectKeyDown()
{

	POINT3D Posi = {lpCurPlayer->pX,lpCurPlayer->pY+10000,lpCurPlayer->pZ};  
	
	if(sinGetKeyClick('9')){  
		//SetYameEffect(500,"star01M_04.bmp",lpCurPlayer,0);
		//SetAssaEffect(100,"spark01_01.bmp",0,&Posi,0);

	}
	//lpCharSelPlayer	//한번 선택한 대상의 포인터 
	//lpCharMsTrace		//계속 선택한 대상의 포인터
	


}
/*----------------------------------------------------------------------------*
*								Init
*-----------------------------------------------------------------------------*/	
void InitYameEffect()
{
	/////////// 리소스 초기화 
	//InitAssaRes(); 

	/////////// 리소스를 읽는 함수.
	//LoadAssaRes();

	/////////// 야매 이펙트 초기화 
	memset(cYameEffect,0,sizeof(cYAMEEFFECT));

}
/*----------------------------------------------------------------------------*
*								Draw
*-----------------------------------------------------------------------------*/	
void DrawYameEffect(POINT3D *pPosi , POINT3D *pAngle)
{

	int i=0;
	int IndexCount = 0;

	///////////////////  ZDepth를 구한다
	for(i = 0 ; i < YAMEEFFECT_MAX ; i++){          
		if(cYameEffect[i] && !cYameEffect[i]->Bone && cYameEffect[i]->Time >0){
			smRender.SetCameraPosi(pPosi->x,pPosi->y,pPosi->z,pAngle->x,pAngle->y,pAngle->z);
			for(int j = 0 ; j < YAMEEFFECT_MAX ;j++){   
				if(!sinEffect_Zdepth4[j].Index){
					sinEffect_Zdepth4[j].ZDepth = smRender.GetDepthZ(cYameEffect[i]->Posi.x   , cYameEffect[i]->Posi.y , cYameEffect[i]->Posi.z);
					sinEffect_Zdepth4[j].Index = i+1;
					IndexCount++;
					break;
				}
			}
		}
	}
	//////////////////// 소팅   
	sinBubbleSort(sinEffect_Zdepth4,IndexCount-1);
	for(i = 0 ; i < IndexCount ; i++)
	{   
		if(sinEffect_Zdepth4[i].Index)
		{ 
			renderDevice.BeginScene();
			if(cYameEffect[sinEffect_Zdepth4[i].Index-1]->pChar)
			{
				if(cYameEffect[sinEffect_Zdepth4[i].Index-1]->pChar->FlagShow !=0){ //캐릭터를 그리지않을때는 이펙트도 그리지않는다
					cYameEffect[sinEffect_Zdepth4[i].Index-1]->Draw(pPosi,pAngle);	
				}
			}
			else
				cYameEffect[sinEffect_Zdepth4[i].Index-1]->Draw(pPosi,pAngle);	
			renderDevice.EndScene();
		}
	}	
	memset(sinEffect_Zdepth4,0,sizeof(sinEFFECT_ZDEPTH)*YAMEEFFECT_MAX);
}
/*----------------------------------------------------------------------------*
*								Main
*-----------------------------------------------------------------------------*/	
void MainYameEffect()
{

	for(int  i = 0 ; i < YAMEEFFECT_MAX ; i++){ 
		if(cYameEffect[i]){
			cYameEffect[i]->Time++;
			cYameEffect[i]->Main();

			if(cYameEffect[i]->Time > 0 ) // -Time 적용
				//MoveAssaEffect(cYameEffect[i]);

			if(cYameEffect[i]->Time >= cYameEffect[i]->Max_Time){
				delete cYameEffect[i];
				cYameEffect[i] = NULL;

			}
		}
	}
}
/*----------------------------------------------------------------------------*
*								Close
*-----------------------------------------------------------------------------*/	
void CloseYameEffect()
{


}
/*----------------------------------------------------------------------------*
*							  Move
*-----------------------------------------------------------------------------*/	
void MoveYameEffect(cASSAEFFECT *pEffect)
{

}
/*----------------------------------------------------------------------------*
*							  Stop
*-----------------------------------------------------------------------------*/	
void StopYameEffect(cASSAEFFECT *pEffect)
{
	//시간으로 끝을낸다 
	//pEffect->Time = pEffect->Max_Time; 
}

/******************************************************************************************
*								Setting 함수 
*******************************************************************************************/	
/*----------------------------------------------------------------------------*
*							Set Assa Effect
*-----------------------------------------------------------------------------*/	
int  SetYameEffect(int MaxTime , char *FileName , smCHAR *pChar , POINT3D *pPosi , int AddHeight ,int BlendTpye)
{
	char TempFileName[64];
	char FileFormat[32];

	WORD wBlendType = 0;
	switch(BlendTpye){
		case 0:
			wBlendType = SMMAT_BLEND_LAMP; //현제 기본적으로 블렌드 Tpye은 LAMP로 설정되어있다
		break;
		case 1:
			wBlendType = SMMAT_BLEND_ALPHA;
		break;
		case 2:
			wBlendType = SMMAT_BLEND_COLOR;
		break;
		case 3:
			wBlendType = SMMAT_BLEND_SHADOW;
		break;
		case 4:
			wBlendType = SMMAT_BLEND_ADDCOLOR;
		break;
		case 5:
			wBlendType = SMMAT_BLEND_INVSHADOW;
		break;
	}

	FileFormat[0] = 0; //혹시모를 쓰레기 값이 있을경우를 대비해 초기화해준다

	lstrcpy(TempFileName , FileName);
	int len=lstrlen(TempFileName);
	for(int i = 0; i < len ; i++){
		if(TempFileName[i] == '.'){
			strcpy(FileFormat,&TempFileName[i+1]);  //확장자 
			break;
		}
	}
	
	for(int  i = 0 ; i < YAMEEFFECT_MAX ; i++){
		if(!cYameEffect[i]){ 
			//////// BONE 셋팅
			if( stricmp(FileName, "Bone") == 0 ){
				cYAMEFACE *pFace = new cYAMEFACE; 
				cYameEffect[i] = pFace; //기본 클래스에 할당 
				cYameEffect[i]->Bone = 1;


			}
			if( stricmp(FileFormat, "bmp") == 0 || stricmp(FileFormat, "tga") == 0){
				cYAMEFACE *pFace = new cYAMEFACE; 
				cYameEffect[i] = pFace; //기본 클래스에 할당 
				cYameEffect[i]->Face.r = 255;
				cYameEffect[i]->Face.g = 255;
				cYameEffect[i]->Face.b = 255;
				cYameEffect[i]->Face.Transparency = 255;
				cYameEffect[i]->Face.TexRect = sinTexRect;
				cYameEffect[i]->Face.MatNum = *(int *)AssaSearchRes(FileName,wBlendType);
				
			}
			if(stricmp(FileFormat, "ase") == 0 ){
				cYAMEMESH *pMesh = new cYAMEMESH;
				cYameEffect[i] = pMesh; //기본 클래스에 할당 
				cYameEffect[i]->PatMesh = (smPAT3D *)AssaSearchRes(FileName,wBlendType);

			}
			if(pChar){
				cYameEffect[i]->Posi.x = pChar->pX;
				cYameEffect[i]->Posi.y = pChar->pY;
				cYameEffect[i]->Posi.z = pChar->pZ;
				cYameEffect[i]->pChar = pChar;
//				if(cYameEffect[i]->pChar == lpCurPlayer)cYameEffect[i]->MyPointerFlag = 1;

			}
			if(pPosi){
				cYameEffect[i]->Posi.x = pPosi->x;
				cYameEffect[i]->Posi.y = pPosi->y;
				cYameEffect[i]->Posi.z = pPosi->z;
			}
			//lstrcpy(cYameEffect[i]->szFileName,FileName); //파일이름을 카피한다
			cYameEffect[i]->AddHeight = AddHeight;
			cYameEffect[i]->Posi.y += AddHeight;
			cYameEffect[i]->Max_Time = MaxTime;
//			cYameEffect[i]->CenterPosi = cYameEffect[i]->Posi;
			if(pChar){ //기본적으로 Angle을 자신의 방향으로 한다 
				cYameEffect[i]->Angle.y = (-(pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;
			}
			return i;
		}
	}
	return FALSE;
	
}
