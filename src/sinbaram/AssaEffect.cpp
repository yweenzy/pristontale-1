/*----------------------------------------------------------------------------*
*	파일명 :  AssaEffect.cpp	
*	하는일 :  이펙트 
*	작성일 :  최종업데이트 2002년 11월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"
#include "..\\field.h"
/*----------------------------------------------------------------------------*
*							전역 변수 
*-----------------------------------------------------------------------------*/	

cASSAEFFECT *cAssaEffect[cASSAEFFECT_MAX]; //이펙트 버퍼 
sinEFFECT_ZDEPTH sinEffect_Zdepth3[cASSAEFFECT_MAX];//소팅을 위한 인덱스 구조체 
int Assa;

/*----------------------------------------------------------------------------*
*							Key Down
*-----------------------------------------------------------------------------*/	
void AssaEffectKeyDown()
{
	sinAssaSkillEffectKeyDown();	// Assa 스킬 이펙트 Keydown
	sinAssaParticleKeyDown();		// Assa 파티클 이펙트 Keydown
	sinAssaParticleTestKeyDown();   // Assa 파티클 Test 이펙트 Keydown
	YameEffectKeyDown();            // Yame Effect Keydown
//	sinAssaParticle7KeyDown();		// Assa 묶음형 파티클 이펙트 

	////////////////// 테스트 이미지 
	/*
	if(sinGetKeyClick('N')){
		InitAssaEffect();    //이미지 리로드 

	}
	if(sinGetKeyClick('A')){    
		AssaTestEffectImage();
		
	}
	*/

	//lpCharSelPlayer	//한번 선택한 대상의 포인터 
	//lpCharMsTrace		//계속 선택한 대상의 포인터
	
	POINT3D Posi = {lpCurPlayer->pX,lpCurPlayer->pY+10000,lpCurPlayer->pZ};  


}
/*----------------------------------------------------------------------------*
*								Init
*-----------------------------------------------------------------------------*/	
void InitAssaEffect()
{
	/////////// 리소스 초기화 
	InitAssaRes(); 

	/////////// 리소스를 읽는 함수.
	LoadAssaRes();

	/////////// 아싸 이펙트 초기화 
	memset(cAssaEffect,0,sizeof(cASSAEFFECT));

}
/*----------------------------------------------------------------------------*
*								Draw
*-----------------------------------------------------------------------------*/	
void DrawAssaEffect(POINT3D *pPosi , POINT3D *pAngle)
{

	int i=0;
	int IndexCount = 0;
	//sinEffect_Ratoo_Aura2(lpCurPlayer); 막아둔다

	///////////////////  ZDepth를 구한다
	for(i = 0 ; i < cASSAEFFECT_MAX ; i++){          
		if(cAssaEffect[i] && !cAssaEffect[i]->Bone && cAssaEffect[i]->Time >0){
			smRender.SetCameraPosi(pPosi->x,pPosi->y,pPosi->z,pAngle->x,pAngle->y,pAngle->z);
			for(int j = 0 ; j < cASSAEFFECT_MAX ;j++){   
				if(!sinEffect_Zdepth3[j].Index){
					sinEffect_Zdepth3[j].ZDepth = smRender.GetDepthZ(cAssaEffect[i]->Posi.x   , cAssaEffect[i]->Posi.y , cAssaEffect[i]->Posi.z);
					sinEffect_Zdepth3[j].Index = i+1;
					IndexCount++;
					break;
				}
			}
		}
	}
	//////////////////// 소팅   
	sinBubbleSort(sinEffect_Zdepth3,IndexCount-1);
	for(i = 0 ; i < IndexCount ; i++){   
		if(sinEffect_Zdepth3[i].Index){ 
			renderDevice.BeginScene();
			if(cAssaEffect[sinEffect_Zdepth3[i].Index-1]->pChar){
				if(cAssaEffect[sinEffect_Zdepth3[i].Index-1]->pChar->FlagShow !=0){ //캐릭터를 그리지않을때는 이펙트도 그리지않는다
					cAssaEffect[sinEffect_Zdepth3[i].Index-1]->Draw(pPosi,pAngle);	
				}
			}
			else
				cAssaEffect[sinEffect_Zdepth3[i].Index-1]->Draw(pPosi,pAngle);	
			renderDevice.EndScene();
		}
	}	
	memset(sinEffect_Zdepth3,0,sizeof(sinEFFECT_ZDEPTH)*cASSAEFFECT_MAX);

}
/*----------------------------------------------------------------------------*
*								Main
*-----------------------------------------------------------------------------*/	
void MainAssaEffect()
{

	for(int  i = 0 ; i < cASSAEFFECT_MAX ; i++){ 
		if(cAssaEffect[i]){
			cAssaEffect[i]->Time++;
			cAssaEffect[i]->Main();

			if(cAssaEffect[i]->Time > 0 ) // -Time 적용
				MoveAssaEffect(cAssaEffect[i]);

			if(cAssaEffect[i]->Time >= cAssaEffect[i]->Max_Time){
				delete cAssaEffect[i];
				cAssaEffect[i] = NULL;

			}
		}
	}
}
/*----------------------------------------------------------------------------*
*								Close
*-----------------------------------------------------------------------------*/	
void CloseAssaEffect()
{


}
/*----------------------------------------------------------------------------*
*							  Move
*-----------------------------------------------------------------------------*/	
void MoveAssaEffect(cASSAEFFECT *pEffect)
{
	sinAssaSkillEffectProcess(pEffect);   //세부 움직임
	sinAssaParticleProcess(pEffect);      //세부 움직임
	sinAssaParticleTestProcess(pEffect);  //세부 움직임
//	sinAssaParticle7Process(pEffect);     //세부 움직임

	///////////////////////// FACE TYPE 에 대한 MOVE
	switch(pEffect->FACE_TYPE){ 
		case ASSAFACE_SCALE: 
			pEffect->ScalePosi.x += pEffect->ScaleSpeed.x;
			pEffect->ScalePosi.y += pEffect->ScaleSpeed.y;
			pEffect->ScalePosi.z += pEffect->ScaleSpeed.z;
		break;
		case ASSAFACE_TRACE:
			//if(!pEffect->Type && (pEffect->Time%5)==0) //Type 설정일때는 연결리스트를 없앤다 
			pEffect->cAssaTrace->AddData(&pEffect->Posi);

		break;

	}


	///////////// 각각 움직임 /////////////
	if(pEffect->MOVECODE == ASSA_MOVE_RANDOM_ROTATE){ 
		pEffect->Angle.y += pEffect->RAngleSpeed; 
		pEffect->Angle.y &=ANGCLIP;
		GetMoveLocation(pEffect->MoveSpeed.x, pEffect->MoveSpeed.y, pEffect->MoveSpeed.z, 0, pEffect->Angle.y, 0);
		POINT3D tempGeoResult;
		tempGeoResult.x = GeoResult_X;
		tempGeoResult.y = GeoResult_Y;
		tempGeoResult.z = GeoResult_Z;
		GetMoveLocation(tempGeoResult.x, tempGeoResult.y, tempGeoResult.z, pEffect->Angle.x, 0, 0);
		if(pEffect->MOVECODESUB & ASSA_CHAR_POSI){
			pEffect->Posi.x = pEffect->pChar->pX+GeoResult_X;
			pEffect->Posi.z = pEffect->pChar->pZ+GeoResult_Z;
			pEffect->Posi.y = pEffect->pChar->pY+GeoResult_Y+pEffect->AddHeight; 
		}
		else{
			pEffect->Posi.x = pEffect->CenterPosi.x+GeoResult_X;
			pEffect->Posi.z = pEffect->CenterPosi.z+GeoResult_Z;
			pEffect->Posi.y = pEffect->CenterPosi.y+GeoResult_Y; 
		}
		return ;
	}

	if(pEffect->MOVECODE == ASSA_MOVE_SPREAD){ 
		//pEffect->RAngle += pEffect->RAngleSpeed; 
		pEffect->RPosi.x  = pEffect->RDistance.y*GetCos[ pEffect->RAngle&ANGCLIP ] + pEffect->RDistance.z*GetSin[ pEffect->RAngle&ANGCLIP ];     
		pEffect->RPosi.z = -pEffect->RDistance.y*GetSin[ pEffect->RAngle&ANGCLIP ] + pEffect->RDistance.z*GetCos[ pEffect->RAngle&ANGCLIP ];

		pEffect->RPosi.x >>=16;
		pEffect->RPosi.z >>=16;
		pEffect->Posi.x += pEffect->RPosi.x;
		pEffect->Posi.z += pEffect->RPosi.z;
		pEffect->MoveSpeed.y -= pEffect->Gravity;
		pEffect->Posi.y +=  pEffect->MoveSpeed.y ; 
		return ;

	}

	///////////// 기본 움직임 ///////////// 
	if(pEffect->MOVECODE & ASSA_ROTATE ){ //ROTATE
		pEffect->RAngle += pEffect->RAngleSpeed; 
		pEffect->RPosi.x  = pEffect->RDistance.y*GetCos[ pEffect->RAngle&ANGCLIP ] + pEffect->RDistance.z*GetSin[ pEffect->RAngle&ANGCLIP ];     
		pEffect->RPosi.z = -pEffect->RDistance.y*GetSin[ pEffect->RAngle&ANGCLIP ] + pEffect->RDistance.z*GetCos[ pEffect->RAngle&ANGCLIP ];

		pEffect->RPosi.x >>=16;
		pEffect->RPosi.z >>=16;
		pEffect->Posi.x =  pEffect->CenterPosi.x + pEffect->RPosi.x;
		pEffect->Posi.z =  pEffect->CenterPosi.z + pEffect->RPosi.z;
//		pEffect->Posi.y =  pEffect->CenterPosi.y + pEffect->AddHeight;
		if(pEffect->MOVECODE & ASSA_CHAR_POSI){
			if(pEffect->pChar){
				pEffect->Posi.x = pEffect->pChar->pX + pEffect->RPosi.x;
				pEffect->Posi.z = pEffect->pChar->pZ + pEffect->RPosi.z;
				//pEffect->Posi.y = pEffect->pChar->pY + pEffect->AddHeight;
			}
		}
	}
	if(pEffect->MOVECODE & ASSA_MOVE){ //MOVE
		pEffect->Posi.x += pEffect->MoveSpeed.x;
		pEffect->Posi.y += pEffect->MoveSpeed.y;
		pEffect->Posi.z += pEffect->MoveSpeed.z;

		//pEffect->CenterPosi.y = pEffect->Posi.y; //ROTATE시 좌표 보정을 위해 (안사용해두 될껄 ...)

		if(pEffect->MOVECODE & ASSA_CHAR_POSI){
			if(pEffect->pChar){
				pEffect->MovePosi.x += pEffect->MoveSpeed.x;
				pEffect->MovePosi.y += pEffect->MoveSpeed.y;
				pEffect->MovePosi.z += pEffect->MoveSpeed.z;

				//pEffect->Posi.x = pEffect->pChar->pX + pEffect->MovePosi.x; //흠흠 일단은 뺀다 왠지 껄쩍지근하다요잉
				//pEffect->Posi.y = pEffect->pChar->pY + pEffect->MovePosi.y;
				//pEffect->Posi.z = pEffect->pChar->pZ + pEffect->MovePosi.z;
			}
		}
	}
	if(pEffect->MOVECODE & ASSA_ANGLE_ROTATE){ //ANGLE ROTATE 
		if(pEffect->ARotateSpeed.x != 0){
			pEffect->ARotate.x += pEffect->ARotateSpeed.x;
			pEffect->Angle.x = (pEffect->ARotate.x+ANGLE_90)&ANGCLIP; 

		}
		if(pEffect->ARotateSpeed.y != 0){
			if(pEffect->ARotateSpeed.y != 10000){
				pEffect->ARotate.y += pEffect->ARotateSpeed.y;
			}
			pEffect->Angle.y = (pEffect->ARotate.y+ANGLE_90)&ANGCLIP; 

		}
		if(pEffect->ARotateSpeed.z != 0){
			pEffect->ARotate.z += pEffect->ARotateSpeed.z;
			pEffect->Angle.z = (pEffect->ARotate.z+ANGLE_90)&ANGCLIP; 

		}
		if(pEffect->MOVECODE & ASSA_CHAR_POSI){ //약간은 임시적이다 
			if(pEffect->pChar){
				pEffect->Posi.x = pEffect->pChar->pX; 
				pEffect->Posi.y = pEffect->pChar->pY + pEffect->AddHeight;
				pEffect->Posi.z = pEffect->pChar->pZ; 
				//ANGLE을 임의대로 보정하면 회전에 문제가 생긴다 
				//pEffect->Angle.y = (-(pEffect->pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;
			}
		}

	} 
	if(pEffect->MOVECODE & ASSA_MOVE_ANGLE_SPEED){ //각도와 속도에 맞게 이동
		if(!pEffect->Angle.x && !pEffect->Angle.y && !pEffect->Angle.z){ //Angle이 없으면 랜덤으로 설정
			pEffect->Angle.x = rand()%4096; 
			pEffect->Angle.y = rand()%4096;
		}
		AssaGetMoveLocation(pEffect); //각도와 속도의 설정을 해야한다 (잠시뺀다)

	}
	if(pEffect->MOVECODE & ASSA_DECRESIZE){ //크기를 조절한다 
		if(!pEffect->ReSize.w)pEffect->ReSize.w =   pEffect->Size.w/pEffect->Max_Time;
		if(!pEffect->ReSize.h)pEffect->ReSize.h =   pEffect->Size.h/pEffect->Max_Time;
		pEffect->Size.w -= pEffect->ReSize.w;
		pEffect->Size.h -= pEffect->ReSize.h;
	}

	if(pEffect->MOVECODE & ASSA_INCRESIZE){ //크기를 조절한다 
		if(!pEffect->ReSize.w)pEffect->ReSize.w =   pEffect->Size.w/pEffect->Max_Time;
		if(!pEffect->ReSize.h)pEffect->ReSize.h =   pEffect->Size.h/pEffect->Max_Time;
		pEffect->Size.w += pEffect->ReSize.w;
		pEffect->Size.h += pEffect->ReSize.h;
	}
	if(pEffect->MOVECODE & ASSA_MOVE_GATHER ){  
		if(pEffect->Temp[9] == 0 ){ //값을 한번만 구해놓는다 
			pEffect->TempPosi.x = pEffect->CenterPosi.x - pEffect->Posi.x;
			pEffect->TempPosi.y = pEffect->CenterPosi.y - pEffect->Posi.y;
			pEffect->TempPosi.z = pEffect->CenterPosi.z - pEffect->Posi.z;
			pEffect->Temp[9] = 1;
		}
		if(pEffect->Posi.x-500 < pEffect->CenterPosi.x && pEffect->Posi.x+500 >= pEffect->CenterPosi.x){
			//StopAssaEffect(pEffect); //일단은 뺀다 

		}
		else pEffect->Posi.x += pEffect->TempPosi.x/pEffect->GatherSpeed;
		if(pEffect->Posi.z-500 < pEffect->CenterPosi.z && pEffect->Posi.z+500 >= pEffect->CenterPosi.z){
			//StopAssaEffect(pEffect);

		}
		else pEffect->Posi.z += pEffect->TempPosi.z/pEffect->GatherSpeed;


		/// 회전을 뺀 Y 값만을 세부조정한다 
		if(pEffect->Posi.y-500 < pEffect->CenterPosi.y && pEffect->Posi.y+500 >= pEffect->CenterPosi.y){
			//StopAssaEffect(pEffect);
		}
		else{
			
			pEffect->Posi.y += pEffect->TempPosi.y/pEffect->GatherSpeed;


		}
	}
	//캐릭터 포지션을 경우 
	if(pEffect->MOVECODE == ASSA_CHAR_POSI){
		if(pEffect->Temp[8] == 0 ){ //값을 한번만 구해놓는다 
			pEffect->TempPosi.x = pEffect->pChar->pX - pEffect->Posi.x;
			pEffect->TempPosi.y = (pEffect->pChar->pY+pEffect->AddHeight) - pEffect->Posi.y;
			pEffect->TempPosi.z = pEffect->pChar->pZ - pEffect->Posi.z;
			pEffect->Temp[8] = 1;
		}
		pEffect->Posi.x = pEffect->pChar->pX + pEffect->TempPosi.x;
		pEffect->Posi.y = pEffect->pChar->pY + pEffect->TempPosi.y+pEffect->AddHeight;
		pEffect->Posi.z = pEffect->pChar->pZ + pEffect->TempPosi.z;
		pEffect->Angle.y = (-(pEffect->pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;

	}
}

/*----------------------------------------------------------------------------*
*							  Stop
*-----------------------------------------------------------------------------*/	
void StopAssaEffect(cASSAEFFECT *pEffect)
{
	//시간으로 끝을낸다 
	pEffect->Time = pEffect->Max_Time; 
}

/******************************************************************************************
*								Setting 함수 
*******************************************************************************************/	
/*----------------------------------------------------------------------------*
*							Set Assa Effect
*-----------------------------------------------------------------------------*/	
int  SetAssaEffect(int MaxTime , char *FileName , smCHAR *pChar , POINT3D *pPosi , int AddHeight ,int BlendTpye)
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
	
	for(int  i = 0 ; i < cASSAEFFECT_MAX ; i++){
		if(!cAssaEffect[i]){ 
			//////// BONE 셋팅
			if( stricmp(FileName, "Bone") == 0 ){
				cASSAFACE *pFace = new cASSAFACE; 
				cAssaEffect[i] = pFace; //기본 클래스에 할당 
				cAssaEffect[i]->Bone = 1;


			}
			if( stricmp(FileFormat, "bmp") == 0 || stricmp(FileFormat, "tga") == 0){
				cASSAFACE *pFace = new cASSAFACE; 
				cAssaEffect[i] = pFace; //기본 클래스에 할당 
				cAssaEffect[i]->Face.r = 255;
				cAssaEffect[i]->Face.g = 255;
				cAssaEffect[i]->Face.b = 255;
				cAssaEffect[i]->Face.Transparency = 255;
				cAssaEffect[i]->Face.TexRect = sinTexRect;
				cAssaEffect[i]->Face.MatNum = *(int *)AssaSearchRes(FileName,wBlendType);
				
			}
			if(stricmp(FileFormat, "ase") == 0 ){
				cASSAMESH *pMesh = new cASSAMESH;
				cAssaEffect[i] = pMesh; //기본 클래스에 할당 
				cAssaEffect[i]->PatMesh = (smPAT3D *)AssaSearchRes(FileName,wBlendType);

			}
			if(pChar){
				cAssaEffect[i]->Posi.x = pChar->pX;
				cAssaEffect[i]->Posi.y = pChar->pY;
				cAssaEffect[i]->Posi.z = pChar->pZ;
				cAssaEffect[i]->pChar = pChar;
				if(cAssaEffect[i]->pChar == lpCurPlayer)cAssaEffect[i]->MyPointerFlag = 1;

			}
			if(pPosi){
				cAssaEffect[i]->Posi.x = pPosi->x;
				cAssaEffect[i]->Posi.y = pPosi->y;
				cAssaEffect[i]->Posi.z = pPosi->z;
			}
			lstrcpy(cAssaEffect[i]->szFileName,FileName); //파일이름을 카피한다
			cAssaEffect[i]->AddHeight = AddHeight;
			cAssaEffect[i]->Posi.y += AddHeight;
			cAssaEffect[i]->Max_Time = MaxTime;
			cAssaEffect[i]->CenterPosi = cAssaEffect[i]->Posi;
			if(pChar){ //기본적으로 Angle을 자신의 방향으로 한다 
				cAssaEffect[i]->Angle.y = (-(pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;
			}
			return i;
		}
	}
	return FALSE;
	
}
/*----------------------------------------------------------------------------*
*							  Set Angle 
*-----------------------------------------------------------------------------*/	
int AssaSetAngle(cASSAEFFECT *pEffect , int AngleKind)
{
	switch(AngleKind){
		case ASSA_ANG_CHAR: //캐릭터 자신의 방향
			if(pEffect->pChar){ 
				pEffect->Angle.y = (-(pEffect->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP;

			}
		break;
		case ASSA_ANG_DESCHAR: //상대와 자신의 각의 방향
			if(pEffect->pChar && pEffect->desChar ){ 
				GetRadian3D( pEffect->pChar->pX, pEffect->pChar->pY, pEffect->pChar->pZ, pEffect->desChar->pX, pEffect->desChar->pY, pEffect->desChar->pZ );
				pEffect->Angle.x = GeoResult_X;
				pEffect->Angle.y = (-(GeoResult_Y&ANGCLIP)+ANGLE_180)&ANGCLIP;
			}
		break;
		case ASSA_ANG_BONE: //OBJ 각이 아닌 Bone의각 
			if(pEffect->pChar && pEffect->desChar ){ 
				GetRadian3D( pEffect->pChar->pX, pEffect->pChar->pY, pEffect->pChar->pZ, pEffect->desChar->pX, pEffect->desChar->pY, pEffect->desChar->pZ );
				pEffect->Angle.x = GeoResult_X;
				pEffect->Angle.y = GeoResult_Y;  
			}
		break;

	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*							  Set Start Posi
*-----------------------------------------------------------------------------*/	
int AssaSetStartPosi(cASSAEFFECT *pEffect)
{
	if(!pEffect->Angle.x && !pEffect->Angle.y && !pEffect->Angle.z){ //Angle이 없으면 랜덤으로 설정
		pEffect->Angle.x = rand()%4096; 
		pEffect->Angle.y = rand()%4096;
	}

	//GetMoveLocation(  pEffect->StartPosi.x, pEffect->StartPosi.y,pEffect->StartPosi.z , pEffect->Angle.x, (-(pEffect->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP, 0 );
	GetMoveLocation(  pEffect->StartPosi.x, pEffect->StartPosi.y,pEffect->StartPosi.z , pEffect->Angle.x, pEffect->Angle.y, 0 );
	pEffect->Posi.x += GeoResult_X;
	pEffect->Posi.y += GeoResult_Y;
	pEffect->Posi.z += GeoResult_Z;

	return TRUE;
}
/*----------------------------------------------------------------------------*
*							  Copy Effect
*-----------------------------------------------------------------------------*/	
int AssaCopyEffect(cASSAEFFECT *pEffect)
{
	///////현재 실패 ㅜ.ㅜ

	return FALSE;
}

/*----------------------------------------------------------------------------*
*							  Set FaceAni
*-----------------------------------------------------------------------------*/	
int AssaGetAniFileMat(cASSAEFFECT *pEffect)
{

	char TempFileName[64];
	char FirstFileName[64];
	char FileFormat[32];
	char TotalFileName[128];
	char szIndex[2];
	int  FileIndex = 0;
	int  *MatNum = 0;

	lstrcpy(TempFileName , pEffect->szFileName);
	for(int i = 0; i < lstrlen(TempFileName) ; i++){
		if(TempFileName[i+1] == '.'){
			memcpy(&szIndex, &TempFileName[i],2);
			TempFileName[i] = '\0'; TempFileName[i+1] = '\0';
			FileIndex = atoi(szIndex);				//파일 인덱스 
			strcpy(FirstFileName,TempFileName);		//파일 이름
			strcpy(FileFormat,&TempFileName[i+2]);  //확장자 
			break;
		}
	}
	//cAssaEffect[Index]->Face.MatNum = *(int *)AssaSearchRes(FileName,SMMAT_BLEND_LAMP);
	for(int i = 0 ; i < 10 ; i++){
		wsprintf(TotalFileName,"%s%d.%s",FirstFileName,FileIndex++,FileFormat);
		int *MatNum = (int *)AssaSearchRes(TotalFileName,SMMAT_BLEND_LAMP);
		if(MatNum){
			pEffect->AniMatIndex[i] = *MatNum;
			pEffect->AniMaxCount++;
		}
		else break;

	}
	return TRUE;
}
/******************************************************************************************
*								좌표 계산 함수 
*******************************************************************************************/	
/*----------------------------------------------------------------------------*
*							  Move Angle Posi
*-----------------------------------------------------------------------------*/	
#define ASSA_ANG_FLOAT	(5+FLOATNS) 
int AssaGetMoveLocation(cASSAEFFECT *pEffect) //각도와 Speed에 맞게 움직인다 
{
	int i,j,k;
	int dx,dy,dz;

	int sinX, sinY, sinZ;
	int cosX, cosY, cosZ;

	pEffect->Angle.x &=ANGCLIP; 
	pEffect->Angle.y &=ANGCLIP;
	pEffect->Angle.z &=ANGCLIP;

	sinX = sdGetSin[pEffect->Angle.x]>>2;
	sinY = sdGetSin[pEffect->Angle.y]>>2;
	sinZ = sdGetSin[pEffect->Angle.z]>>2;
	cosX = sdGetCos[pEffect->Angle.x]>>2;
	cosY = sdGetCos[pEffect->Angle.y]>>2;
	cosZ = sdGetCos[pEffect->Angle.z]>>2;

	// now Z axis rotation
    i = (pEffect->MoveSpeed.x * cosZ - pEffect->MoveSpeed.y * sinZ) >> ASSA_ANG_FLOAT;
    j = (pEffect->MoveSpeed.x * sinZ + pEffect->MoveSpeed.y * cosZ) >> ASSA_ANG_FLOAT;
	k = pEffect->MoveSpeed.z;

	// now X axis rotation
    dy = (j * cosX - k * sinX) >> ASSA_ANG_FLOAT;
    dz = (j * sinX + k * cosX) >> ASSA_ANG_FLOAT;
	k = dz;

	// now Y axis
    dx = (k * sinY + i * cosY) >> ASSA_ANG_FLOAT;
    dz = (k * cosY - i * sinY) >> ASSA_ANG_FLOAT;

	pEffect->Posi.x +=dx;
	pEffect->Posi.y +=dy;
	pEffect->Posi.z +=dz;

	return TRUE;
}

/*----------------------------------------------------------------------------*
*								Get Circle
*-----------------------------------------------------------------------------*/	
int AssaGetCirclePosi(cASSAEFFECT *pEffect, int DistanceZ , int Angle)
{
	
	POINT3D Posi = {0,0,0};
	pEffect->RAngle = Angle;
	pEffect->RDistance.z = DistanceZ;
	
	Posi.x = GetCos[ Angle&ANGCLIP ] + DistanceZ*GetSin[ Angle&ANGCLIP ];     
	Posi.z = -GetSin[ Angle&ANGCLIP ] + DistanceZ*GetCos[ Angle&ANGCLIP ];

	Posi.x >>= 16;
	Posi.z >>= 16;

	pEffect->Posi.x += Posi.x;
	pEffect->Posi.z += Posi.z;
	pEffect->Posi.y += Posi.y;
	return TRUE;
}

/*----------------------------------------------------------------------------*
*								StageCrash
*-----------------------------------------------------------------------------*/	
int AssaCheckStageCrash(cASSAEFFECT *pEffect)
{

	int pY;
	int sy;

	if ( smGameStage[0] )
		pY = smGameStage[0]->GetHeight( pEffect->Posi.x , pEffect->Posi.z);

	if ( smGameStage[1] ) {
		sy = smGameStage[1]->GetHeight( pEffect->Posi.x , pEffect->Posi.z);
		if ( pY<sy ) pY = sy;
	}

	if(pY >= pEffect->Posi.y )return TRUE;

	return FALSE;
	
}
/*----------------------------------------------------------------------------*
*								ReSet CharPointer
*-----------------------------------------------------------------------------*/	
int cASSAEFFECT::AssaReSetCharPointer()
{
	
	if(pChar){
		if(pChar != lpCurPlayer && MyPointerFlag){
			pChar = lpCurPlayer;

		}
		if(!pChar->Flag || sinGetLife()==0){ //캐릭이 죽었거나 그자리에서 사라진경우 
			Time = Max_Time;
		}
		//마을로 들어온경우 이펙트를 꺼준다 
		if(CODE != SKILL_HOLY_REFLECTION && CODE != ASSA_PARTICLE_UNIONCORE){
			if(pChar->OnStageField>=0 && StageField[ pChar->OnStageField ]->State == FIELD_STATE_VILLAGE){
				Time = Max_Time;
			}
		}
	}

	return TRUE;
}