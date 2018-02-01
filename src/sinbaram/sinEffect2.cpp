/*----------------------------------------------------------------------------*
*	파일명 :  sinEffect2.cpp	
*	하는일 :  이펙트 관련 작업 (각각 하나씩 된 이펙트 )
*	작성일 :  최종업데이트 2002년 6월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#include "sinLinkHeader.h"

/*----------------------------------------------------------------------------*
*							 이동방향 
*-----------------------------------------------------------------------------*/	
#define		SIN_MOVE_ROTATE				1
#define		SIN_MOVE_DOWN				2
#define		SIN_MOVE_BOMB				3
#define		SIN_MOVE_TORNADO			4
#define		SIN_MOVE_SPARK				5
#define		SIN_MOVE_LINE				6
#define		SIN_EFFECT_LIGHT			7
#define		SIN_MOVE_SONGPYEUN			8
/*----------------------------------------------------------------------------*
*						    이펙트 전역변수 
*-----------------------------------------------------------------------------*/	
cSINEFFECT2 cSinEffect2[SIN_MAX_EFFECT2];					//이펙트 클래스 1000개 
sinEFFECT_ZDEPTH sinEffect_Zdepth2[SIN_MAX_EFFECT2];		//소팅을 위한 인덱스 구조체 

POINT3D	sinPosi2;
POINT3D	sinAngle2;

int Index = 0;
int Matstun = 0;
int MatIceVigo[5];
int MatBossEffect[3];
int MatParticle2[2];

int MatTestParticle;
int MatParticleLine;
int MatLightEffect;
int MatSongPyeun;

////////////// 파티클 셋팅을 위한 Test 오브젝트
smCHAR	sinTestChar; 

/*----------------------------------------------------------------------------*
*								Init 
*-----------------------------------------------------------------------------*/	
int InitEffect2()
{

	memset(cSinEffect2, 0 , sizeof(cSINEFFECT2)*SIN_MAX_EFFECT2);
	memset(sinEffect_Zdepth2, 0 , sizeof(sinEFFECT_ZDEPTH)*SIN_MAX_EFFECT2);

	int i=0;
	char szBuff[128];
	Matstun = CreateTextureMaterial( "image\\Sinimage\\Effect\\stun\\Star.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );	

	for(i = 0 ; i < 5 ; i++){
		wsprintf(szBuff,"image\\Sinimage\\Effect\\IceVigo\\0%d.tga",i+1);
		MatIceVigo[i] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_LAMP );	

	}

	MatBossEffect[0] = CreateTextureMaterial( "image\\Sinimage\\Effect\\BossMonster\\mamangjin1.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	MatBossEffect[1] = CreateTextureMaterial( "image\\Sinimage\\Effect\\BossMonster\\mamangjin2.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	MatBossEffect[2] = CreateTextureMaterial( "image\\Sinimage\\Effect\\BossMonster\\mamangjin3.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );	

	MatParticle2[0] = CreateTextureMaterial( "image\\Sinimage\\Effect\\Particle\\Par-1.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	MatParticle2[1] = CreateTextureMaterial( "image\\Sinimage\\Effect\\Particle\\Par-5.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );	

	MatTestParticle = CreateTextureMaterial( "image\\Sinimage\\Effect\\Particle2\\TestParticle.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );	

	MatParticleLine =  CreateTextureMaterial( "image\\Sinimage\\Effect\\Particle2\\raysoflight1.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	MatLightEffect = CreateTextureMaterial( "image\\Sinimage\\Effect\\Skill\\SwordBlast\\bal.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	MatSongPyeun = CreateTextureMaterial( "image\\Sinimage\\Effect\\Particle2\\song.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						 파티클 Hit
*-----------------------------------------------------------------------------*/	
int sinSetParticleHit(POINT3D Posi)
{
	int  i = 0;
	for(i = 0 ; i < 1 ; i++){  
		Index = sinSearchEmptyIndex();                            
		cSinEffect2[Index].Flag = 1; 
		cSinEffect2[Index].sinFace.r = 255;
		cSinEffect2[Index].sinFace.g = 255;
		cSinEffect2[Index].sinFace.b = 255;
		cSinEffect2[Index].sinFace.Transparency = 255;
		cSinEffect2[Index].sinFace.height = 1000;
		cSinEffect2[Index].sinFace.width  = 1000;
		cSinEffect2[Index].sinFace.MatNum = MatParticle2[0];
		cSinEffect2[Index].sinFace.x = Posi.x ;
		cSinEffect2[Index].sinFace.y = Posi.y+15000 ;
		cSinEffect2[Index].sinFace.z = Posi.z ;
		cSinEffect2[Index].Max_Time = 1000;
		cSinEffect2[Index].sinFace.TexRect = sinTexRect;


	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*							 차가운 기운 
*-----------------------------------------------------------------------------*/	
int sinSetEffect_IceVigo(smCHAR *pChar ,  int Time)
{
	Index = sinSearchEmptyIndex();                            
	cSinEffect2[Index].Flag = 1; 
	cSinEffect2[Index].Max_Time = Time;
	cSinEffect2[Index].pChar = pChar;

	cSinEffect2[Index].sinFace.width  = 3000;
	cSinEffect2[Index].sinFace.height = 3000;

	cSinEffect2[Index].sinFace.r  = 255;
	cSinEffect2[Index].sinFace.g  = 255;
	cSinEffect2[Index].sinFace.b  = 255;
	cSinEffect2[Index].sinFace.Transparency = 255;

	cSinEffect2[Index].sinFace.MatNum = MatIceVigo[0];

	cSinEffect2[Index].sinFace.TexRect = sinTexRect;

	cSinEffect2[Index].AniTime = 10;
	cSinEffect2[Index].AniMax = 5;

	cSinEffect2[Index].lpMatAni = MatIceVigo;

	cSinEffect2[Index].CODE  = SIN_EFFECT_ICEVIGO;

	return TRUE;
}
/*----------------------------------------------------------------------------*
*								스턴 
*-----------------------------------------------------------------------------*/	
int sinSetEffect_Stun(smCHAR *pChar ,int Time)
{
	int TempX=0,TempZ=0,TempSize;    
	for(int i = 0; i < 8 ; i++){                           
		Index = sinSearchEmptyIndex();                        
		cSinEffect2[Index].Flag = 1;
		cSinEffect2[Index].Max_Time = Time;

		cSinEffect2[Index].ObjMat = Matstun;//CreateTextureMaterial( "image\\Sinimage\\Effect\\Particle\\Particle1.tga" , 0, 0, 0,0, SMMAT_BLEND_LAMP );
		cSinEffect2[Index].Size.x  = 128;
		cSinEffect2[Index].Size.y  = 128;
		cSinEffect2[Index].pChar = pChar;
		cSinEffect2[Index].Posi.x = pChar->pX;
		cSinEffect2[Index].Posi.y = pChar->pY+13000;
		cSinEffect2[Index].Posi.z = pChar->pZ;

		cSinEffect2[Index].CODE = SIN_EFFECT_STUN;

		TempSize = (i%8)*64;

		cSinEffect2[Index].Size.x  += TempSize;
		cSinEffect2[Index].Size.y  += TempSize;

		cSinEffect2[Index].Angle.x = ANGLE_270;//ANGLE_270;  //x,z 축으로 회전하면 수직이 된다  
		cSinEffect2[Index].Angle.y = ANGLE_180;//AngleY;
		cSinEffect2[Index].Angle.z = 0;//ANGLE_270;
		
		cSinEffect2[Index].MoveKind = SIN_MOVE_ROTATE;
		cSinEffect2[Index].RotateDistance.z = 365;
		cSinEffect2[Index].RotateSpeed = 128;
		cSinEffect2[Index].RotateSpeedCnt = i*128;

		cSinEffect2[Index].RotatePosi.x =  GetCos[ cSinEffect2[Index].RotateSpeedCnt&ANGCLIP ] + cSinEffect2[Index].RotateDistance.z*GetSin[ cSinEffect2[Index].RotateSpeedCnt&ANGCLIP ];     
		cSinEffect2[Index].RotatePosi.z = -GetSin[ cSinEffect2[Index].RotateSpeedCnt&ANGCLIP ] + cSinEffect2[Index].RotateDistance.z*GetCos[ cSinEffect2[Index].RotateSpeedCnt&ANGCLIP ];
		
		cSinEffect2[Index].RotatePosi.x >>=16;
		cSinEffect2[Index].RotatePosi.z >>=16;

		cSinEffect2[Index].Posi.x += cSinEffect2[Index].RotatePosi.x+TempX;
		cSinEffect2[Index].Posi.z += cSinEffect2[Index].RotatePosi.z+TempZ;

		TempX += cSinEffect2[Index].RotatePosi.x;
		TempZ += cSinEffect2[Index].RotatePosi.z;

		cSinEffect2[Index].CharDistance.x = cSinEffect2[Index].Posi.x - cSinEffect2[Index].pChar->pX;
		cSinEffect2[Index].CharDistance.z = cSinEffect2[Index].Posi.z - cSinEffect2[Index].pChar->pZ;

		cSinEffect2[Index].Angle.y = -((i*256)+ANGLE_90)&ANGCLIP; 
		sinCreateObject(&cSinEffect2[Index]); //오브젝트를 생성한다 

	}	
	
	return TRUE;
}

/*----------------------------------------------------------------------------*
*						  보스 몬스터 이펙트 셋팅 
*-----------------------------------------------------------------------------*/	
int setBossMonsterEffect(smCHAR *pChar,int ProcessCount)
{
	Index = sinSearchEmptyIndex();                            

	smASE_SetPhysique( 0 ); //physique 초기화     

	cSinEffect2[Index].Flag = 1;  
	cSinEffect2[Index].sinPatMesh = smASE_Read("image\\Sinimage\\Effect\\BossMonster\\mon.ASE");
	cSinEffect2[Index].CODE = SIN_EFFECT_BOSSAURA;
	cSinEffect2[Index].Max_Time = SIN_EFFECT_NO_TIME;
	cSinEffect2[Index].Posi.x = pChar->pX;
	cSinEffect2[Index].Posi.y = pChar->pY+1500;
	cSinEffect2[Index].Posi.z = pChar->pZ;
	cSinEffect2[Index].pChar  = pChar; 
	cSinEffect2[Index].AniCount = 1;
	cSinEffect2[Index].AniTime = 3;
	cSinEffect2[Index].AniMax = 80;

	ReadTextures();	//텍스쳐 로딩 
	
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						   보스 이펙트 2 (흩날리는 이펙트) 
*-----------------------------------------------------------------------------*/	
int setBossMonsterEffect2(POINT3D Posi)
{
	int TempSize;
	Index = sinSearchEmptyIndex(); 
	smASE_SetPhysique( 0 ); 
	cSinEffect2[Index].Flag = 1;
	cSinEffect2[Index].Max_Time = 200+rand()%20;
	cSinEffect2[Index].ObjMat = MatParticle2[1];
	cSinEffect2[Index].Posi = Posi;
	TempSize = 200+rand()%200;

	cSinEffect2[Index].Size.x  = TempSize;
	cSinEffect2[Index].Size.y  = TempSize;

	cSinEffect2[Index].MoveKind = SIN_MOVE_DOWN;
	sinCreateObject(&cSinEffect2[Index]); //오브젝트를 생성한다 
	ReadTextures();	//텍스쳐 로딩 
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						    흩날리는 이펙트 
*-----------------------------------------------------------------------------*/	
int sinSetParticleTail(POINT3D Posi)
{

	int TempSize = 0; 
	for(int i = 0 ; i < 1 ; i++){  
		Index = sinSearchEmptyIndex();                            
		cSinEffect2[Index].Flag = 1; 
		cSinEffect2[Index].Max_Time = 200+rand()%20;

		TempSize = 200+rand()%200;
		cSinEffect2[Index].sinFace.width  = TempSize;
		cSinEffect2[Index].sinFace.height = TempSize;

		cSinEffect2[Index].sinFace.x = Posi.x+rand()%500 - rand()%500;
		cSinEffect2[Index].sinFace.y = Posi.y+rand()%500 - rand()%500;
		cSinEffect2[Index].sinFace.z = Posi.z+rand()%500 - rand()%500;

		cSinEffect2[Index].Posi.x = cSinEffect2[Index].sinFace.x;
		cSinEffect2[Index].Posi.y = cSinEffect2[Index].sinFace.y;
		cSinEffect2[Index].Posi.z = cSinEffect2[Index].sinFace.z;

		cSinEffect2[Index].sinFace.r  = 255;
		cSinEffect2[Index].sinFace.g  = 255;
		cSinEffect2[Index].sinFace.b  = 255;
		cSinEffect2[Index].sinFace.Transparency = 255;

		cSinEffect2[Index].sinFace.MatNum = MatParticle2[4];
		cSinEffect2[Index].sinFace.TexRect = sinTexRect;
		cSinEffect2[Index].MoveSpeed.y = 3;
		cSinEffect2[Index].MoveKind = SIN_MOVE_DOWN;
		//cSinEffect2[Index].Gravity = 5;
		cSinEffect2[Index].AlphaAmount = 8;
		cSinEffect2[Index].AlphaTime = 180;
		
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						    이펙트를 그린다 
*-----------------------------------------------------------------------------*/	
int IndexCount = 0;
int sinDrawEffect2(int x, int y,int z,int ax, int ay, int az)
{

	int i;
	POINT3D posi =  {x,y,z};
	POINT3D Angle = {ax,ay,az};
	IndexCount = 0;
	int sinColor_A = 0 , sinColor_R = 0 , sinColor_G = 0 , sinColor_B = 0;

	//////////좌표 정렬
	for(i = 0 ; i < SIN_MAX_EFFECT2 ; i++){         
		if(cSinEffect2[i].Flag && cSinEffect2[i].Time>0 && !cSinEffect2[i].BoneFlag){
			smRender.SetCameraPosi(x,y,z,ax,ay,az);
			for(int j = 0 ; j < SIN_MAX_EFFECT2 ;j++){   
				if(!sinEffect_Zdepth2[j].Index){
					if(!cSinEffect2[i].sinFace.MatNum){
						sinEffect_Zdepth2[j].ZDepth = smRender.GetDepthZ(cSinEffect2[i].Posi.x   , cSinEffect2[i].Posi.y , cSinEffect2[i].Posi.z);
						sinEffect_Zdepth2[j].Index = i+1;
						IndexCount++;
					}
					break;
				}
			}
		}
	}

	////////// 소팅   

	sinBubbleSort(sinEffect_Zdepth2,IndexCount-1);
	
	/////////// MESH를 먼저찍어준다 
	for(i = 0 ; i < IndexCount ; i++)
	{  
		if(sinEffect_Zdepth2[i].Index)
		{ 
			if(cSinEffect2[sinEffect_Zdepth2[i].Index-1].Flag && cSinEffect2[sinEffect_Zdepth2[i].Index-1].Time > 0)
			{
				renderDevice.BeginScene();
				if(cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_A || cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_R ||
					cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_G || cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_B ){
					sinColor_A = smRender.Color_A;
					sinColor_R = smRender.Color_R;
					sinColor_G = smRender.Color_G;
					sinColor_B = smRender.Color_B; 

					if(cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_A > 255)cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_A = 255;
					smRender.Color_A -= cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_A;

					smRender.Color_R = cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_R;
					smRender.Color_G = cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_G;
					smRender.Color_B = cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_B;

				}

				if(!cSinEffect2[sinEffect_Zdepth2[i].Index-1].sinPatMesh->smMaterialGroup)
					smRender.SetMaterialGroup(smMaterialGroup);
 				cSinEffect2[sinEffect_Zdepth2[i].Index-1].sinPatMesh->Frame = cSinEffect2[sinEffect_Zdepth2[i].Index-1].AniCount*160; 
				cSinEffect2[sinEffect_Zdepth2[i].Index-1].sinPatMesh->SetPosi( &cSinEffect2[sinEffect_Zdepth2[i].Index-1].Posi , &cSinEffect2[sinEffect_Zdepth2[i].Index-1].RanderAngle );
				cSinEffect2[sinEffect_Zdepth2[i].Index-1].sinPatMesh->RenderD3D( &posi , &Angle );		 
				if(cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_A || cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_R ||
					cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_G || cSinEffect2[sinEffect_Zdepth2[i].Index-1].Color_B ){

					smRender.Color_A = sinColor_A;
					smRender.Color_R = sinColor_R;
					smRender.Color_G = sinColor_G;
					smRender.Color_B = sinColor_B;
					
				}
				renderDevice.EndScene();
			}
		}
	}
	memset(sinEffect_Zdepth2,0,sizeof(sinEFFECT_ZDEPTH)*SIN_MAX_EFFECT2);

	IndexCount = 0;
	//////////좌표 정렬  // MESH를 찍고 난후 오브젝트를 찍는다 
	for(i = 0 ; i < SIN_MAX_EFFECT2 ; i++){        
		if(cSinEffect2[i].Flag && cSinEffect2[i].Time>0 && !cSinEffect2[i].BoneFlag){
			smRender.SetCameraPosi(x,y,z,ax,ay,az);
			for(int j = 0 ; j < SIN_MAX_EFFECT2 ;j++){   
				if(!sinEffect_Zdepth2[j].Index){
					if(cSinEffect2[i].sinFace.MatNum){
						sinEffect_Zdepth2[j].ZDepth = smRender.GetDepthZ(cSinEffect2[i].sinFace.x   , cSinEffect2[i].sinFace.y , cSinEffect2[i].sinFace.z);
						sinEffect_Zdepth2[j].Index = i+1;
						IndexCount++;

					}
					break;
				}
			}
		}
	}

	////////// 소팅   //smRender.Color_A
	sinBubbleSort(sinEffect_Zdepth2,IndexCount-1);
	for(i = 0 ; i < IndexCount ; i++){  
		if(sinEffect_Zdepth2[i].Index){ 
			if(cSinEffect2[sinEffect_Zdepth2[i].Index-1].Flag && cSinEffect2[sinEffect_Zdepth2[i].Index-1].Time > 0){
				if(cSinEffect2[sinEffect_Zdepth2[i].Index-1].sinFace.MatNum){
					sinDrawTexture2(&cSinEffect2[sinEffect_Zdepth2[i].Index-1]);
				}
			}
		}
	}
	memset(sinEffect_Zdepth2,0,sizeof(sinEFFECT_ZDEPTH)*SIN_MAX_EFFECT2);
	return TRUE;
}
/*----------------------------------------------------------------------------*
*				  이펙트가 셋팅될 빈곳을 찾아서 Index를 리턴한다 
*-----------------------------------------------------------------------------*/	
int sinSearchEmptyIndex()
{
	int i;
	for(i = 0 ; i < SIN_MAX_EFFECT2 ; i++){  
		if(!cSinEffect2[i].Flag){
			return i;

		}

	}
	return -1;
}
/*----------------------------------------------------------------------------*
*							오브젝트를 셋팅한다 
*-----------------------------------------------------------------------------*/	
int sinCreateObject(cSINEFFECT2 *pEffect)
{

	smTPOINT tPoint[4];

	smMaterial[pEffect->ObjMat].SelfIllum = 1;
	
	tPoint[0].u = 0; 
	tPoint[0].v = 0;  
	tPoint[1].u = 256;
	tPoint[1].v = 0;
	tPoint[2].u = 0;
	tPoint[2].v = 256;
	tPoint[3].u = 256; 
	tPoint[3].v = 256;

	pEffect->sinObj = new smOBJ3D( 4, 2 ); 

	pEffect->sinObj->AddVertex( -pEffect->Size.x , -pEffect->Size.y ,0);
	pEffect->sinObj->AddVertex(  pEffect->Size.x , -pEffect->Size.y ,0);
	pEffect->sinObj->AddVertex( -pEffect->Size.x ,  pEffect->Size.y ,0);
	pEffect->sinObj->AddVertex(  pEffect->Size.x ,  pEffect->Size.y ,0);

	pEffect->sinObj->AddFace( 0, 1, 2 , &tPoint[0], &tPoint[1], &tPoint[2] );
	pEffect->sinObj->AddFace( 2, 1, 3 , &tPoint[2], &tPoint[1], &tPoint[3] );
	pEffect->sinObj->ZeroNormals();

	pEffect->sinObj->SetFaceMaterial( 0 , pEffect->ObjMat );
	pEffect->sinObj->SetFaceMaterial( 1 , pEffect->ObjMat );


	smMaterial[pEffect->ObjMat].TwoSide = TRUE;

	pEffect->sinPatMesh = new smPAT3D;
	pEffect->sinPatMesh->AddObject(pEffect->sinObj);

	return TRUE;
}

/*----------------------------------------------------------------------------*
*							Effect를 움직인다 
*-----------------------------------------------------------------------------*/	
int sinMoveEffect2(cSINEFFECT2 *pEffect)
{
	int TempSpeed = 0;
		
	memcpy(&pEffect->RanderAngle , &pEffect->Angle , sizeof(POINT3D));
	switch(pEffect->MoveKind){
		case SIN_MOVE_ROTATE:
			pEffect->RotateSpeedCnt += pEffect->RotateSpeed;     
			pEffect->RotatePosi.x =  GetCos[ pEffect->RotateSpeedCnt&ANGCLIP ] + pEffect->RotateDistance.z*GetSin[ pEffect->RotateSpeedCnt&ANGCLIP ];     
			pEffect->RotatePosi.z = -GetSin[ pEffect->RotateSpeedCnt&ANGCLIP ] + pEffect->RotateDistance.z*GetCos[ pEffect->RotateSpeedCnt&ANGCLIP ];
			
			pEffect->RotatePosi.x >>=16;
			pEffect->RotatePosi.z >>=16;

			pEffect->Posi.x += pEffect->RotatePosi.x;
			pEffect->Posi.z += pEffect->RotatePosi.z;
			pEffect->Angle.y = -((pEffect->RotateSpeedCnt)+ANGLE_90)&ANGCLIP; 
			
		break;
		case SIN_MOVE_DOWN:
			pEffect->RotateSpeedCnt++;
			if((pEffect->RotateSpeedCnt % 10) == 0){
				pEffect->Posi.y -= pEffect->MoveSpeed.y; 
				pEffect->sinFace.y = pEffect->Posi.y; //페이스에 좌표를 넣어준다 
			}
		break;
		case SIN_MOVE_BOMB:
			TempSpeed++; 
			while(TempSpeed){
				pEffect->Gravity -= 3;    
				pEffect->RotatePosi.x =  GetCos[ pEffect->RotateSpeedCnt&ANGCLIP ] + pEffect->RotateDistance.z*GetSin[ pEffect->RotateSpeedCnt&ANGCLIP ];     
				pEffect->RotatePosi.z = -GetSin[ pEffect->RotateSpeedCnt&ANGCLIP ] + pEffect->RotateDistance.z*GetCos[ pEffect->RotateSpeedCnt&ANGCLIP ];
				
				pEffect->RotatePosi.x >>=16;
				pEffect->RotatePosi.z >>=16;

				pEffect->Posi.x += pEffect->RotatePosi.x;
				pEffect->Posi.z += pEffect->RotatePosi.z;
				pEffect->Posi.y += pEffect->MoveSpeed.y + pEffect->Gravity;
				
				pEffect->sinFace.x = pEffect->Posi.x;
				pEffect->sinFace.y = pEffect->Posi.y;
				pEffect->sinFace.z = pEffect->Posi.z;
				TempSpeed++;
				if(TempSpeed >= 3 )TempSpeed = 0;

			}
		break;
		case SIN_MOVE_TORNADO: 
			/*
			X축을 중심으로 회전.

			y' = ycos( ? ) - zsin( ? );
			z' = ysin( ? ) + zcos( ? );

			Y축을 중심으로 회전.

			x' = xcos( ? ) + zsin( ? );
			z' =-xsin( ? ) + zcos( ? );

			Z축을 중심으로 회전.

			x' = xcos( ? ) - ysin( ? );
			y' = xsin( ? ) + ycos( ? );
			*/

			pEffect->RotatePosi.x =  pEffect->RotateDistance.y*GetCos[ pEffect->RotateSpeedCnt&ANGCLIP ] + pEffect->RotateDistance.z*GetSin[ pEffect->RotateSpeedCnt&ANGCLIP ];     
			pEffect->RotatePosi.z = -pEffect->RotateDistance.y*GetSin[ pEffect->RotateSpeedCnt&ANGCLIP ] + pEffect->RotateDistance.z*GetCos[ pEffect->RotateSpeedCnt&ANGCLIP ];
			
			pEffect->RotatePosi.x >>=16;
			pEffect->RotatePosi.z >>=16;

			pEffect->Posi.y = lpCurPlayer->pX+pEffect->RotatePosi.y;
			pEffect->Posi.z = lpCurPlayer->pZ+pEffect->RotatePosi.z;
			
			pEffect->sinFace.x = pEffect->Posi.x;
			pEffect->sinFace.y = pEffect->Posi.y;
			pEffect->sinFace.z = pEffect->Posi.z;


		break;
		case SIN_MOVE_SPARK:
			TempSpeed++;    
			while(TempSpeed){
				pEffect->RotatePosi.x =  GetCos[ pEffect->RotateSpeedCnt&ANGCLIP ] + pEffect->RotateDistance.z*GetSin[ pEffect->RotateSpeedCnt&ANGCLIP ];     
				pEffect->RotatePosi.z = -GetSin[ pEffect->RotateSpeedCnt&ANGCLIP ] + pEffect->RotateDistance.z*GetCos[ pEffect->RotateSpeedCnt&ANGCLIP ];
				
				pEffect->RotatePosi.x >>=16;
				pEffect->RotatePosi.z >>=16;

				pEffect->Posi.x += pEffect->RotatePosi.x;
				pEffect->Posi.z += pEffect->RotatePosi.z;
				pEffect->Posi.y += pEffect->MoveSpeed.y;
				
				pEffect->sinFace.x = pEffect->Posi.x;
				pEffect->sinFace.y = pEffect->Posi.y;
				pEffect->sinFace.z = pEffect->Posi.z;
				TempSpeed++;
				if(TempSpeed >= 5 )TempSpeed = 0;

			}

		break;
		case SIN_MOVE_LINE:
			sinGetMoveLocation2(pEffect);   
  			GetMoveLocation( 0 , 0, 256, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->Posi.x += GeoResult_X;
			pEffect->Posi.y += GeoResult_Y;
			pEffect->Posi.z += GeoResult_Z;


			pEffect->sinFace.x  = pEffect->Posi.x;
			pEffect->sinFace.y  = pEffect->Posi.y;
			pEffect->sinFace.z  = pEffect->Posi.z;


			pEffect->RanderAngle.y = (-pEffect->Angle.y+ANGLE_180)&ANGCLIP; 

		break;

		case SIN_MOVE_SONGPYEUN:
			sinGetMoveLocation2(pEffect);    
  			GetMoveLocation( 0 , 0, 256, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->Posi.x += GeoResult_X;
			pEffect->Posi.y += GeoResult_Y;
			pEffect->Posi.z += GeoResult_Z;


			pEffect->sinFace.x  = pEffect->Posi.x;
			pEffect->sinFace.y  = pEffect->Posi.y;
			pEffect->sinFace.z  = pEffect->Posi.z;


			pEffect->RanderAngle.y = (-pEffect->Angle.y+ANGLE_180)&ANGCLIP; 
		break;
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*							Effect ACTIVE!!
*-----------------------------------------------------------------------------*/	
int sinActiveEffect2()
{

	sinProcess7(); //날치기 프로세서 
	int i = 0;
	
	for(i = 0 ; i < SIN_MAX_EFFECT2 ; i++){      
		if(cSinEffect2[i].Flag){
			cSinEffect2[i].Time++;
			if(cSinEffect2[i].Time < 0 )continue;
			sinMoveEffect2(&cSinEffect2[i]);    //캐릭터 이동 
			sinCheckCharState(&cSinEffect2[i]); //캐릭터 정보를 이펙트에 셋팅 

			////////////// 스킬 이펙트 
			sinSkillEffectMove(&cSinEffect2[i]);

			////////////// 공용 이펙트 
			sinPublicEffectMove(&cSinEffect2[i]);	

			/////페이드인
			if(cSinEffect2[i].AlphaFadeInFlag){
				if(cSinEffect2[i].sinFace.MatNum){ 
					if(cSinEffect2[i].sinFace.Transparency >=255){
						cSinEffect2[i].sinFace.Transparency = 255;
						cSinEffect2[i].AlphaFadeInFlag = 0;
					}
					else{
						cSinEffect2[i].sinFace.Transparency +=10;
					}

				}
				else{
					if(cSinEffect2[i].Color_A <=0){
						cSinEffect2[i].Color_A = 0; 
						cSinEffect2[i].AlphaFadeInFlag = 0;
					}
					else{
						cSinEffect2[i].Color_A -=10;
					}
				}
			}
			
			if( cSinEffect2[i].Time >= cSinEffect2[i].AlphaTime && cSinEffect2[i].AlphaCount) {  //Alpha를 빼준다
				if((cSinEffect2[i].Time % cSinEffect2[i].AlphaCount) == 0 ){
						if(cSinEffect2[i].AlphaReverseNum == 1){
						if(cSinEffect2[i].sinFace.MatNum){ 
							cSinEffect2[i].sinFace.Transparency -= cSinEffect2[i].AlphaAmount;
							if(cSinEffect2[i].sinFace.Transparency <= cSinEffect2[i].AlphaReverse_A){
								cSinEffect2[i].AlphaReverseNum = 2;
							}

						}
						else{
							cSinEffect2[i].Color_A +=cSinEffect2[i].AlphaAmount;
							if((255 - cSinEffect2[i].Color_A) <= cSinEffect2[i].AlphaReverse_A){
								cSinEffect2[i].AlphaReverseNum = 2;
							}
						}

					}
					else if(cSinEffect2[i].AlphaReverseNum == 2){
						if(cSinEffect2[i].sinFace.MatNum){
							cSinEffect2[i].sinFace.Transparency += cSinEffect2[i].AlphaAmount;
							if(cSinEffect2[i].sinFace.Transparency >= 255){
								cSinEffect2[i].AlphaReverseNum = 1;
							}

						}
						else{
							cSinEffect2[i].Color_A -=cSinEffect2[i].AlphaAmount;
							if( cSinEffect2[i].Color_A  <= cSinEffect2[i].AlphaReverse_A){
								cSinEffect2[i].AlphaReverseNum = 1;
							}
						}
					}
					else{
						if(cSinEffect2[i].sinFace.MatNum)
							cSinEffect2[i].sinFace.Transparency -= cSinEffect2[i].AlphaAmount;
						else{
							cSinEffect2[i].Color_A +=cSinEffect2[i].AlphaAmount;
						}
					}

				}

			}
			
			if(cSinEffect2[i].Max_Time != SIN_EFFECT_NO_TIME &&cSinEffect2[i].Time > cSinEffect2[i].Max_Time){
				memset(&cSinEffect2[i],0,sizeof(cSINEFFECT2));

			}
			if(cSinEffect2[i].AniTime){ //애니메이션 
				if((cSinEffect2[i].Time % cSinEffect2[i].AniTime)==0){
					if(!cSinEffect2[i].AniReverseNum){
						cSinEffect2[i].AniCount++; 
						if(cSinEffect2[i].AniCount >=cSinEffect2[i].AniMax)cSinEffect2[i].AniCount = 0;
						if(cSinEffect2[i].sinFace.MatNum){
							cSinEffect2[i].sinFace.MatNum = cSinEffect2[i].lpMatAni[cSinEffect2[i].AniCount];
						}
						if(cSinEffect2[i].ObjMat){
							cSinEffect2[i].ObjMat = cSinEffect2[i].lpMatAni[cSinEffect2[i].AniCount];
							sinCreateObject(&cSinEffect2[i]);
						}
					}
					else{ //애니메이션 리버스 
						switch(cSinEffect2[i].AniReverseNum){
							case 1:
								cSinEffect2[i].AniCount++; 
								if(cSinEffect2[i].AniCount >=cSinEffect2[i].AniMax-1){
									cSinEffect2[i].AniReverseNum = 2;
								}
								if(cSinEffect2[i].sinFace.MatNum){
									cSinEffect2[i].sinFace.MatNum = cSinEffect2[i].lpMatAni[cSinEffect2[i].AniCount];
								}
								if(cSinEffect2[i].ObjMat){
									cSinEffect2[i].ObjMat = cSinEffect2[i].lpMatAni[cSinEffect2[i].AniCount];
									sinCreateObject(&cSinEffect2[i]);
								}
							break;
							case 2:
								cSinEffect2[i].AniCount--; 
								if(cSinEffect2[i].AniCount <= 0 ){
									cSinEffect2[i].AniReverseNum = 1;
								}
								if(cSinEffect2[i].sinFace.MatNum){
									cSinEffect2[i].sinFace.MatNum = cSinEffect2[i].lpMatAni[cSinEffect2[i].AniCount];
								}
								if(cSinEffect2[i].ObjMat){
									cSinEffect2[i].ObjMat = cSinEffect2[i].lpMatAni[cSinEffect2[i].AniCount];
									sinCreateObject(&cSinEffect2[i]);
								}
								break;
						}
					}
				}
			}
			if(cSinEffect2[i].SizeIncreTime){
				if(cSinEffect2[i].Time >= cSinEffect2[i].SizeIncreTime){
					cSinEffect2[i].sinFace.width += cSinEffect2[i].SizeAmount;
					cSinEffect2[i].sinFace.height += cSinEffect2[i].SizeAmount;
				}

			}
			if(cSinEffect2[i].SizeDecreTime){
				if(cSinEffect2[i].Time > cSinEffect2[i].SizeDecreTime ){
					cSinEffect2[i].sinFace.width -= cSinEffect2[i].SizeAmount;
					cSinEffect2[i].sinFace.height-= cSinEffect2[i].SizeAmount;
				}

			}
			if(cSinEffect2[i].ReSizingNum == 1){
		         cSinEffect2[i].ActionTime[9]++; 
				 cSinEffect2[i].sinFace.width -= cSinEffect2[i].ReSizingAmount;
				 cSinEffect2[i].sinFace.height -= cSinEffect2[i].ReSizingAmount;
				 if(cSinEffect2[i].ActionTime[9] >= 30 ){
					 cSinEffect2[i].ActionTime[9] = 0;
					 cSinEffect2[i].ReSizingNum = 2;

				 }

			}
			else{
		         cSinEffect2[i].ActionTime[9]++;
				 cSinEffect2[i].sinFace.width += cSinEffect2[i].ReSizingAmount;
				 cSinEffect2[i].sinFace.height += cSinEffect2[i].ReSizingAmount;
				 if(cSinEffect2[i].ActionTime[9] >= 30 ){
					 cSinEffect2[i].ActionTime[9] = 0;
					 cSinEffect2[i].ReSizingNum = 1;

				 }
			}
		}
	}

	return TRUE;
}

/*----------------------------------------------------------------------------*
*							이펙트를 셋팅한다 
*-----------------------------------------------------------------------------*/	
int sinCheckCharState(cSINEFFECT2 *pEffect)
{
	if(pEffect->pChar){       
		switch(pEffect->CODE){ 
			case SIN_EFFECT_ICEVIGO:
				pEffect->Posi.x = pEffect->pChar->pX;
				pEffect->Posi.y = pEffect->pChar->pY+13000;
				pEffect->Posi.z = pEffect->pChar->pZ;
				pEffect->sinFace.x = pEffect->Posi.x;
				pEffect->sinFace.y = pEffect->Posi.y;
				pEffect->sinFace.z = pEffect->Posi.z;
			break;
			case SIN_EFFECT_STUN:  
				pEffect->Posi.x += (pEffect->pChar->pX +pEffect->RotatePosi.x)-pEffect->Posi.x+pEffect->CharDistance.x;				
				pEffect->Posi.z += (pEffect->pChar->pZ +pEffect->RotatePosi.z)- pEffect->Posi.z+pEffect->CharDistance.z;				
				pEffect->Posi.y += (pEffect->pChar->pY+13000) - pEffect->Posi.y;

				pEffect->CharDistance.x = pEffect->Posi.x - pEffect->pChar->pX; //간격보정 
				pEffect->CharDistance.z = pEffect->Posi.z - pEffect->pChar->pZ;

			break;
			case SIN_EFFECT_BOSSAURA:
				pEffect->Posi.x = pEffect->pChar->pX;     
				pEffect->Posi.y = pEffect->pChar->pY+1500;//+(pEffect->ProcessCount*250);   
				pEffect->Posi.z = pEffect->pChar->pZ;
				
				//회전 
				pEffect->RotateSpeedCnt += 20;
				pEffect->sinPatMesh->Angle.y  = pEffect->RotateSpeedCnt&ANGCLIP;
				pEffect->Angle.y = pEffect->RotateSpeedCnt&ANGCLIP;

				pEffect->RotateDistance.z = 256*16;
				pEffect->RotatePosi.x =  GetCos[ pEffect->RotateSpeedCnt&ANGCLIP ] + pEffect->RotateDistance.z*GetSin[ pEffect->RotateSpeedCnt&ANGCLIP ];     
				pEffect->RotatePosi.z = -GetSin[ pEffect->RotateSpeedCnt&ANGCLIP ] + pEffect->RotateDistance.z*GetCos[ pEffect->RotateSpeedCnt&ANGCLIP ];
				pEffect->RotatePosi.y = pEffect->RotateSpeedCnt;
				
				pEffect->RotatePosi.x >>=16;
				pEffect->RotatePosi.z >>=16;

				pEffect->RotatePosi.x +=  pEffect->Posi.x;
				pEffect->RotatePosi.z +=  pEffect->Posi.z;
				pEffect->RotatePosi.y +=  pEffect->Posi.y;

			break;
		
		}
		
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*							이펙트 디버깅용 텍스트
*-----------------------------------------------------------------------------*/	
int EffectTestDrawText2()
{
	HDC	hdc;

	char strBuff[128];
	memset(strBuff,0,sizeof(strBuff)); 
	renderDevice.lpDDSBack->GetDC(&hdc);
	SelectObject( hdc, sinFont);
    SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, RGB(255,255,255) );

/*
	for(int i = 0 ; i < 100 ; i++){     
		if(cSinEffect2[i].Flag){
			wsprintf(strBuff,"%d",cSinEffect2[i].Max_Time);
			dsTextLineOut(hdc,100+i*100,400,strBuff,lstrlen(strBuff));

			wsprintf(strBuff,"%d",cSinEffect2[i].Time);
			dsTextLineOut(hdc,100+i*100,300,strBuff,lstrlen(strBuff));

		}
	}

	wsprintf(strBuff,"%d",IndexCount);
	dsTextLineOut(hdc,300,500,strBuff,lstrlen(strBuff));
*/

	renderDevice.lpDDSBack->ReleaseDC(hdc);
	return TRUE;

}

/*----------------------------------------------------------------------------*
*							이펙트 초기화 
*-----------------------------------------------------------------------------*/	
int sinReleaseEffect()
{
	memset(cSinEffect2,0,sizeof(cSINEFFECT2)*SIN_MAX_EFFECT2); 

	return TRUE;
}

/*----------------------------------------------------------------------------*
*						    Face 를 그린다 
*-----------------------------------------------------------------------------*/	
int sinDrawTexture2(cSINEFFECT2 *pSinEffect2)
{
	if(!pSinEffect2->sinFace.MatNum)return FALSE;
	
	// Turn on Z-buffering
	//renderDevice.SetRenderState( D3DRENDERSTATE_ZENABLE, TRUE ); (문제가 생기는거 같아서 빼줬다)
	renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	renderDevice.SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
	//renderDevice.SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_USEW );//TRUE );


	// null out the texture handle
	renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);

	// turn on dithering
	renderDevice.SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);

	renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
	renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);

	// D3DFILTER_LINEAR
	renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR);
	renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR);

	renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
	renderDevice.SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

	renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

	renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

	renderDevice.SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
	renderDevice.SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFN_LINEAR);


	smRender.Init(); //데이터 초기화 

	smMaterialGroup->smMaterial[pSinEffect2->sinFace.MatNum].TwoSide = FALSE; //카메라 회전과 상관없이 보이기 
		
	smRender.SetMaterialGroup(smMaterialGroup);  //읽어드린 메트리얼을 연결 
		

	//현재 찍을 Frame을 세팅한다..
	smMaterialGroup->SetMaterialAnimFrame( &smMaterial[pSinEffect2->sinFace.MatNum], 2);
		
	//Camera각도 입력.
	smRender.SetCameraPosi(sinPosi2.x, sinPosi2.y, sinPosi2.z,
		sinAngle2.x, sinAngle2.y, sinAngle2.z);

	if(pSinEffect2->FaceAngleY){
		if(smRender.AddFace2D(&pSinEffect2->sinFace,pSinEffect2->FaceAngleY)){
			smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
			smRender.ClipRendFace();
			smRender.GeomVertex2D(FALSE);
			smRender.RenderD3D();
		}
	}
	else{
		if(smRender.AddFace2D(&pSinEffect2->sinFace)){
			smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
			smRender.ClipRendFace();
			smRender.GeomVertex2D(FALSE);
			smRender.RenderD3D();
		}

	}
	return TRUE;
}


/*----------------------------------------------------------------------------*
*						    테스트 이미지 
*-----------------------------------------------------------------------------*/	
static char sinDecode[512];
static char sinLine[512];
int CheeseTestEffectImage()
{

	char *szFilePath = "Image\\SinImage\\";
	char szTempBuffFile[128];
	char szTempBuff[128];
	int  FileFormatFlag = 0;
	POINT ImageSize;
	int  sinObjCount = 0;


	FILE	*fp;
	char strBuff[64];
	char *p;
//	char *pb;
//	int cnt;
	int Count = 0;
	int NextFlag = 0;

	wsprintf(szTempBuffFile,"%sCHEESE.INI",szFilePath);
	fp = fopen( szTempBuffFile , "rb" );
	if ( fp==NULL ) return FALSE;

	Index = sinSearchEmptyIndex();			//이펙트 구조체의 인덱스을 읽어온다                              

	smASE_SetPhysique( 0 ); //physique 초기화     
	cSinEffect2[Index].Flag = 1;  
	cSinEffect2[Index].Max_Time = SIN_EFFECT_NO_TIME;

	cSinEffect2[Index].Posi.x = lpCurPlayer->pX;
	cSinEffect2[Index].Posi.y = lpCurPlayer->pY+5000;
	cSinEffect2[Index].Posi.z = lpCurPlayer->pZ;
	cSinEffect2[Index].pChar  = lpCurPlayer; 

	while( !feof( fp ) )					//  feof: file end까지 읽어라 
	{
		NextFlag = 0;
		if( fgets( sinLine, 255, fp ) == NULL)	
			break;

		p = GetWord( sinDecode , sinLine);
		
		//pb=p;p=GetWord(strBuff,p);if(strBuff[0]==34)p=GetString(strBuff,pb);	 " " 묶인 스트링을 같이 찾을때 쓰임

		if ( !NextFlag && lstrcmp( sinDecode , "*파일형식" )==0 ) {
			
			if(sinObjCount){
				Index = sinSearchEmptyIndex();			//이펙트 구조체의 인덱스을 읽어온다                              

				smASE_SetPhysique( 0 ); //physique 초기화     
				cSinEffect2[Index].Flag = 1;  
				cSinEffect2[Index].Max_Time = SIN_EFFECT_NO_TIME;

				cSinEffect2[Index].Posi.x = lpCurPlayer->pX;
				cSinEffect2[Index].Posi.y = lpCurPlayer->pY+5000;
				cSinEffect2[Index].Posi.z = lpCurPlayer->pZ;
				cSinEffect2[Index].pChar  = lpCurPlayer; 

			}
			p=GetWord(strBuff,p);
			if(lstrcmp(strBuff,"TGA")==0)
				FileFormatFlag = 1;
			if(lstrcmp(strBuff,"ASE")==0)
				FileFormatFlag = 2;
			NextFlag = TRUE;
			sinObjCount++;

		}

		if ( !NextFlag && lstrcmp( sinDecode , "*이미지크기" )==0 ) {
			p=GetWord(strBuff,p);
			ImageSize.x   = atoi(strBuff);
			p=GetWord(strBuff,p);
			ImageSize.y   = atoi(strBuff);
			NextFlag = TRUE;

		}


		if ( !NextFlag && lstrcmp( sinDecode , "*이미지파일이름" )==0 ) {
			p=GetWord(strBuff,p);
			wsprintf(szTempBuff,"image\\Sinimage\\%s",strBuff);
			if(FileFormatFlag == 1){
				cSinEffect2[Index].sinFace.MatNum = CreateTextureMaterial( szTempBuff , 0, 0, 0,0, SMMAT_BLEND_LAMP );
				cSinEffect2[Index].sinFace.x = cSinEffect2[Index].Posi.x ;
				cSinEffect2[Index].sinFace.y = cSinEffect2[Index].Posi.y ;
				cSinEffect2[Index].sinFace.z = cSinEffect2[Index].Posi.z ;
				cSinEffect2[Index].sinFace.width = ImageSize.x;
				cSinEffect2[Index].sinFace.height = ImageSize.y;
				cSinEffect2[Index].sinFace.r  = 255;
				cSinEffect2[Index].sinFace.g  = 255;
				cSinEffect2[Index].sinFace.b  = 255;
				cSinEffect2[Index].sinFace.Transparency = 255;
				cSinEffect2[Index].sinFace.TexRect = sinTexRect;


			}
			if(FileFormatFlag == 2){
				cSinEffect2[Index].sinPatMesh = smASE_Read(szTempBuff);

			}
			NextFlag = TRUE;

		}

		if ( !NextFlag && lstrcmp( sinDecode , "*애니메이션시작" )==0 ) {
			p=GetWord(strBuff,p);
			cSinEffect2[Index].AniCount = atoi(strBuff);
			NextFlag = TRUE;

		}
		if ( !NextFlag && lstrcmp( sinDecode , "*애니메이션끝" )==0 ) {
			p=GetWord(strBuff,p);
			cSinEffect2[Index].AniMax = atoi(strBuff);
			NextFlag = TRUE;

		}
		if ( !NextFlag && lstrcmp( sinDecode , "*애니메이션타임" )==0 ) {
			p=GetWord(strBuff,p);
			cSinEffect2[Index].AniTime = atoi(strBuff);
			NextFlag = TRUE;

		}
		if ( !NextFlag && lstrcmp( sinDecode , "*이펙트시간" )==0 ) {
			p=GetWord(strBuff,p);
			cSinEffect2[Index].Max_Time = atoi(strBuff);
			NextFlag = TRUE;

		}
		if ( !NextFlag && lstrcmp( sinDecode , "*투명시작시간" )==0 ) {
			p=GetWord(strBuff,p);
			cSinEffect2[Index].AlphaTime = atoi(strBuff);
			NextFlag = TRUE;

		}
		if ( !NextFlag && lstrcmp( sinDecode , "*투명도" )==0 ) {
			p=GetWord(strBuff,p);
			cSinEffect2[Index].AlphaAmount = atoi(strBuff);
			NextFlag = TRUE;

		}
		if ( !NextFlag && lstrcmp( sinDecode , "*투명딜레이시간" )==0 ) {
			p=GetWord(strBuff,p);
			cSinEffect2[Index].AlphaCount = atoi(strBuff);
			NextFlag = TRUE;

		}
		if ( !NextFlag && lstrcmp( sinDecode , "*투명딜레이시간" )==0 ) {
			p=GetWord(strBuff,p);
			cSinEffect2[Index].AlphaCount = atoi(strBuff);
			NextFlag = TRUE;

		}
		if ( !NextFlag && lstrcmp( sinDecode , "*좌표" )==0 ) {
			p=GetWord(strBuff,p);
			cSinEffect2[Index].Posi.x += atoi(strBuff);
			p=GetWord(strBuff,p);
			cSinEffect2[Index].Posi.y += atoi(strBuff);
			p=GetWord(strBuff,p);
			cSinEffect2[Index].Posi.z += atoi(strBuff);
			NextFlag = TRUE;

		}

		if ( !NextFlag && lstrcmp( sinDecode , "*끝" )==0 ) {

			Count++; //아무일도 안한다

		}

	}
	if (fp) fclose(fp);
	ReadTextures();	//텍스쳐 로딩
	return TRUE;

}
/*----------------------------------------------------------------------------*
*					이동된 지역 좌표값을 구한다
*-----------------------------------------------------------------------------*/	

#define SHHH_ANGF_SFLOAT	(5+FLOATNS) //임시 
int sinGetMoveLocation2(cSINEFFECT2 *pEffect)
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
    i = (pEffect->MoveSpeed.x * cosZ - pEffect->MoveSpeed.y * sinZ) >> SHHH_ANGF_SFLOAT;
    j = (pEffect->MoveSpeed.x * sinZ + pEffect->MoveSpeed.y * cosZ) >> SHHH_ANGF_SFLOAT;
	k = pEffect->MoveSpeed.z;

	// now X axis rotation
    dy = (j * cosX - k * sinX) >> SHHH_ANGF_SFLOAT;
    dz = (j * sinX + k * cosX) >> SHHH_ANGF_SFLOAT;
	k = dz;

	// now Y axis
    dx = (k * sinY + i * cosY) >> SHHH_ANGF_SFLOAT;
    dz = (k * cosY - i * sinY) >> SHHH_ANGF_SFLOAT;

	pEffect->Posi.x +=dx;
	pEffect->Posi.y +=dy;
	pEffect->Posi.z +=dz;

	return TRUE;
}
/*----------------------------------------------------------------------------*
*						    Rotate 좌표 셋팅 
*-----------------------------------------------------------------------------*/	
int sinSetRotatePosiReSet(cSINEFFECT2 *pEffect)
{
	pEffect->RotatePosi.x >>=16;
	pEffect->RotatePosi.z >>=16;
	pEffect->Posi.x += pEffect->RotatePosi.x;
	pEffect->Posi.z += pEffect->RotatePosi.z;
	pEffect->Posi.y += pEffect->RotatePosi.y;
	
	pEffect->sinFace.x = pEffect->Posi.x;
	pEffect->sinFace.y = pEffect->Posi.y;
	pEffect->sinFace.z = pEffect->Posi.z;

	return TRUE;
}
/*----------------------------------------------------------------------------*
*						    기본 셋팅
*-----------------------------------------------------------------------------*/	
int sinEffectDefaultSet(int Index , int Kind ,  smCHAR *pChar , POINT3D *pPosi , int Y)
{
	cSinEffect2[Index].Flag = 1; 
	cSinEffect2[Index].Time = 1;
	cSinEffect2[Index].AddHeight = Y;

	if(pPosi){
		cSinEffect2[Index].sinFace.x = pPosi->x;
		cSinEffect2[Index].sinFace.y = pPosi->y+Y;
		cSinEffect2[Index].sinFace.z = pPosi->z;
		cSinEffect2[Index].Posi.x = pPosi->x;
		cSinEffect2[Index].Posi.y = pPosi->y+Y;
		cSinEffect2[Index].Posi.z = pPosi->z;

	}
	if(pChar){
		cSinEffect2[Index].Posi.x = pChar->pX;
		cSinEffect2[Index].Posi.y = pChar->pY+Y;
		cSinEffect2[Index].Posi.z = pChar->pZ;
		cSinEffect2[Index].pChar = pChar;
		cSinEffect2[Index].sinFace.x = pChar->pX;
		cSinEffect2[Index].sinFace.y = pChar->pY+Y;
		cSinEffect2[Index].sinFace.z = pChar->pZ;


	}

	switch(Kind){
		case SIN_EFFECT_FACE:
			//cSinEffect2[Index].sinFace.x = cSinEffect2[Index].Posi.x;
			//cSinEffect2[Index].sinFace.y = cSinEffect2[Index].Posi.y;
			//cSinEffect2[Index].sinFace.z = cSinEffect2[Index].Posi.z;
			cSinEffect2[Index].sinFace.r = 255;
			cSinEffect2[Index].sinFace.g = 255;
			cSinEffect2[Index].sinFace.b = 255;
			cSinEffect2[Index].sinFace.Transparency = 255;
			cSinEffect2[Index].sinFace.TexRect = sinTexRect;

		break;

	}

	return TRUE;

}
/*----------------------------------------------------------------------------*
*						    좌표 보정 
*-----------------------------------------------------------------------------*/	
int sinReSetObjPosi(cSINEFFECT2 *pEffect)
{
	if(pEffect->sinFace.MatNum){
		pEffect->SortPosi.x = pEffect->Posi.x + (pEffect->sinFace.width  /2 );
		pEffect->SortPosi.y = pEffect->Posi.y + (pEffect->sinFace.height /2 );

	}
	else{
		pEffect->SortPosi.x = pEffect->Posi.x + (pEffect->Size.x /2);
		pEffect->SortPosi.y = pEffect->Posi.x + (pEffect->Size.y /2);
	}

	return TRUE;
}

/*******************************************************************************************
*								파티클 시스템 
********************************************************************************************/	
/*----------------------------------------------------------------------------*
*						     Test Key
*-----------------------------------------------------------------------------*/	
int ParticleTestKey()
{
	//lpCurPlayer

	POINT3D TestPosi= {lpCurPlayer->pX,lpCurPlayer->pY+10000,lpCurPlayer->pZ};
	//if(sinGetKeyClick('8')){   
		//sinSongPyeunEffect(TestPosi); 
//		sinParticleLine(0,TestPosi,0,0,255); 
//		sinSetLightEffect(255 , 255 , 255 , 255 , TestPosi);
//		Sword_Blast_Effect(lpCurPlayer);
//		SetDynLight( TestPosi.x , TestPosi.y , TestPosi.z ,0, 0, 255, 255, 200 ,3);

	//}

	if(VRKeyBuff['5']){   
		//sinSparkParticle(0,TestPosi); 
		//sinSetLightEffect(255 , 255 , 255 , 150 , TestPosi);

	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						    번쩍 이펙트
*-----------------------------------------------------------------------------*/	
int sinSetLightEffect(int R , int G , int B , int A , POINT3D Posi)
{
	int Size;
 
	Index = sinSearchEmptyIndex();                                     
	cSinEffect2[Index].Flag = 1;       
	cSinEffect2[Index].sinFace.r = R;    
	cSinEffect2[Index].sinFace.g = G; 
	cSinEffect2[Index].sinFace.b = B;
	cSinEffect2[Index].sinFace.Transparency = A;
	Size = 5000;
	cSinEffect2[Index].sinFace.height = Size;
	cSinEffect2[Index].sinFace.width  = Size; 
	cSinEffect2[Index].sinFace.MatNum =MatLightEffect;//Mat;
	cSinEffect2[Index].sinFace.x = Posi.x;
	cSinEffect2[Index].sinFace.y = Posi.y; 
	cSinEffect2[Index].sinFace.z = Posi.z;
	cSinEffect2[Index].Posi.x = cSinEffect2[Index].sinFace.x;
	cSinEffect2[Index].Posi.y = cSinEffect2[Index].sinFace.y;
	cSinEffect2[Index].Posi.z = cSinEffect2[Index].sinFace.z;
	cSinEffect2[Index].Max_Time = 30;
	cSinEffect2[Index].sinFace.TexRect = sinTexRect;
	cSinEffect2[Index].MoveKind = SIN_EFFECT_LIGHT;
	cSinEffect2[Index].SizeIncreTime = 1;
	cSinEffect2[Index].SizeAmount = 3000;
	cSinEffect2[Index].SizeDecreTime = 5;
	cSinEffect2[Index].AlphaTime = 7;
	cSinEffect2[Index].AlphaAmount = 30;
	cSinEffect2[Index].AlphaCount = 1;

	Index = sinSearchEmptyIndex();                                     
	cSinEffect2[Index].Flag = 1;      
	cSinEffect2[Index].sinFace.r = R;   
	cSinEffect2[Index].sinFace.g = G;
	cSinEffect2[Index].sinFace.b = B;
	cSinEffect2[Index].sinFace.Transparency = A;
	Size = 5000;
	cSinEffect2[Index].sinFace.height = Size;
	cSinEffect2[Index].sinFace.width  = Size;
	cSinEffect2[Index].sinFace.MatNum = MatLightEffect;//Mat;
	cSinEffect2[Index].sinFace.x = Posi.x;
	cSinEffect2[Index].sinFace.y = Posi.y; 
	cSinEffect2[Index].sinFace.z = Posi.z;
	cSinEffect2[Index].Posi.x = cSinEffect2[Index].sinFace.x;
	cSinEffect2[Index].Posi.y = cSinEffect2[Index].sinFace.y;
	cSinEffect2[Index].Posi.z = cSinEffect2[Index].sinFace.z;
	cSinEffect2[Index].Max_Time = 35;
	cSinEffect2[Index].sinFace.TexRect = sinTexRect;
	cSinEffect2[Index].MoveKind = SIN_EFFECT_LIGHT;
	cSinEffect2[Index].SizeIncreTime = 1;
	cSinEffect2[Index].SizeAmount = 2000;
	cSinEffect2[Index].SizeDecreTime = 8;
	cSinEffect2[Index].AlphaTime = 8;
	cSinEffect2[Index].AlphaAmount = 15;
	cSinEffect2[Index].AlphaCount = 1;

	return TRUE;
}

/*----------------------------------------------------------------------------*
*						    Particle Line
*-----------------------------------------------------------------------------*/	
int sinParticleLine(int Mat , POINT3D Posi , int R ,int G , int B)
{

	int  i = 0;
	int  Size = 0; 
	for(i = 0 ; i < 30 ; i++){   
		Index = sinSearchEmptyIndex();                                    
		cSinEffect2[Index].Flag = 1;    
		cSinEffect2[Index].ObjMat = MatParticleLine;
		cSinEffect2[Index].Size.x = 64; 
		cSinEffect2[Index].Size.y = 8*256; 
		cSinEffect2[Index].Posi.x = Posi.x;
		cSinEffect2[Index].Posi.y = Posi.y;
		cSinEffect2[Index].Posi.z = Posi.z;
		cSinEffect2[Index].Max_Time = rand()%50;
		cSinEffect2[Index].Angle.x = ((rand()%(4096/2))-ANGLE_90)&ANGCLIP; 
		cSinEffect2[Index].Angle.z = 0;
		cSinEffect2[Index].Angle.y = rand()%4096;
		cSinEffect2[Index].MoveSpeed.z = 256;
		sinCreateObject(&cSinEffect2[Index]);
		cSinEffect2[Index].MoveKind = SIN_MOVE_LINE;
		cSinEffect2[Index].Color_R = R;
		cSinEffect2[Index].Color_G = G;
		cSinEffect2[Index].Color_B = B;




	}

/*
	int  i = 0;
	int  Size = 0;
	for(i = 0 ; i < 30 ; i++){   
		Index = sinSearchEmptyIndex();                                      
		cSinEffect2[Index].Flag = 1;    
		cSinEffect2[Index].sinFace.MatNum = MatParticleLine;
		cSinEffect2[Index].Size.x = 64; 
		cSinEffect2[Index].Size.y = 16*256; 

		cSinEffect2[Index].sinFace.width = 64;
		cSinEffect2[Index].sinFace.height = 16*256; 

		cSinEffect2[Index].Posi.x = Posi.x;
		cSinEffect2[Index].Posi.y = Posi.y;
		cSinEffect2[Index].Posi.z = Posi.z;
		cSinEffect2[Index].sinFace.x = cSinEffect2[Index].Posi.x;
		cSinEffect2[Index].sinFace.y = cSinEffect2[Index].Posi.y;
		cSinEffect2[Index].sinFace.z = cSinEffect2[Index].Posi.z;

		cSinEffect2[Index].sinFace.r = 255; 
		cSinEffect2[Index].sinFace.g = 255;
		cSinEffect2[Index].sinFace.b = 255;
		cSinEffect2[Index].sinFace.Transparency = 255;
		cSinEffect2[Index].sinFace.TexRect = sinTexRect;
		
		cSinEffect2[Index].Max_Time = 100;
		cSinEffect2[Index].Angle.x = ((rand()%(4096/2))-ANGLE_90)&ANGCLIP; 
		cSinEffect2[Index].Angle.z = 0;
		cSinEffect2[Index].Angle.y = rand()%4096;
		cSinEffect2[Index].MoveSpeed.z = 256;
		//sinCreateObject(&cSinEffect2[Index]);
		cSinEffect2[Index].MoveKind = SIN_MOVE_LINE;

	}
*/


	return TRUE;
}

/*----------------------------------------------------------------------------*
*						     Hit Particle 
*-----------------------------------------------------------------------------*/	
int sinHitParticle(int Mat , POINT3D Posi)
{
	int  i = 0;
	int  Size = 0;
	for(i = 0 ; i < 30 ; i++){  
		Index = sinSearchEmptyIndex();                                   
		cSinEffect2[Index].Flag = 1;    
		cSinEffect2[Index].sinFace.r = 255; 
		cSinEffect2[Index].sinFace.g = 255;
		cSinEffect2[Index].sinFace.b = 255;
		cSinEffect2[Index].sinFace.Transparency = 255;
		Size = rand()%500 + 500;
		cSinEffect2[Index].sinFace.height = Size;
		cSinEffect2[Index].sinFace.width  = Size;
		cSinEffect2[Index].sinFace.MatNum = MatTestParticle;//Mat;
		cSinEffect2[Index].sinFace.x = Posi.x;
		cSinEffect2[Index].sinFace.y = Posi.y; 
		cSinEffect2[Index].sinFace.z = Posi.z;
		cSinEffect2[Index].Posi.x = cSinEffect2[Index].sinFace.x;
		cSinEffect2[Index].Posi.y = cSinEffect2[Index].sinFace.y;
		cSinEffect2[Index].Posi.z = cSinEffect2[Index].sinFace.z;
		cSinEffect2[Index].Max_Time = rand()%50+50;
		cSinEffect2[Index].sinFace.TexRect = sinTexRect;
		cSinEffect2[Index].Gravity = rand()%100;
		cSinEffect2[Index].RotateSpeedCnt = rand()%4096;
		cSinEffect2[Index].RotateDistance.z = cSinEffect2[Index].Gravity+10;
		cSinEffect2[Index].MoveSpeed.y = rand()%50+50;
		cSinEffect2[Index].MoveKind = SIN_MOVE_BOMB;
		cSinEffect2[Index].AlphaTime = cSinEffect2[Index].Max_Time - 30;
		cSinEffect2[Index].AlphaCount = 1;
		cSinEffect2[Index].AlphaAmount = 5;

	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*						     Tornado Particle 
*-----------------------------------------------------------------------------*/	
int sinTornadoParticle(int Mat , POINT3D Posi)
{
	int  i = 0;
	int  Size = 0;
	
	Index = sinSearchEmptyIndex();                                    
	cSinEffect2[Index].Flag = 1;    
	cSinEffect2[Index].sinFace.r = 255; 
	cSinEffect2[Index].sinFace.g = 255;
	cSinEffect2[Index].sinFace.b = 255;
	cSinEffect2[Index].sinFace.Transparency = 255;
	Size = rand()%500 + 500;
	cSinEffect2[Index].sinFace.height = Size;
	cSinEffect2[Index].sinFace.width  = Size;
	cSinEffect2[Index].sinFace.MatNum = MatTestParticle;//Mat;
	cSinEffect2[Index].sinFace.x = Posi.x;
	cSinEffect2[Index].sinFace.y = Posi.y; 
	cSinEffect2[Index].sinFace.z = Posi.z;
	cSinEffect2[Index].Posi.x = cSinEffect2[Index].sinFace.x;
	cSinEffect2[Index].Posi.y = cSinEffect2[Index].sinFace.y;
	cSinEffect2[Index].Posi.z = cSinEffect2[Index].sinFace.z;
	cSinEffect2[Index].Max_Time = rand()%50+50+1000;
	cSinEffect2[Index].sinFace.TexRect = sinTexRect;
	cSinEffect2[Index].Gravity = rand()%100;
	cSinEffect2[Index].RotateDistance.z = cSinEffect2[Index].Gravity+10;
	cSinEffect2[Index].RotateDistance.y = cSinEffect2[Index].Gravity+10;

	cSinEffect2[Index].RotateSpeedCnt = rand()%4096;
	cSinEffect2[Index].MoveKind = SIN_MOVE_TORNADO;

	cSinEffect2[Index].AlphaTime = cSinEffect2[Index].Max_Time - 30;
	cSinEffect2[Index].AlphaCount = 1;
	cSinEffect2[Index].AlphaAmount = 5;

	return TRUE;
}

/*----------------------------------------------------------------------------*
*						     Spark Particle 
*-----------------------------------------------------------------------------*/	
int sinSparkParticle(int Mat , POINT3D Posi)
{
	int  i = 0;
	int  Size = 0;
	Index = sinSearchEmptyIndex();                                     
	cSinEffect2[Index].Flag = 1;    
	cSinEffect2[Index].sinFace.r = 255; 
	cSinEffect2[Index].sinFace.g = 255;
	cSinEffect2[Index].sinFace.b = 255;
	cSinEffect2[Index].sinFace.Transparency = 255;
	Size = rand()%250 + 150;
	cSinEffect2[Index].sinFace.height = Size;
	cSinEffect2[Index].sinFace.width  = Size;
	cSinEffect2[Index].sinFace.MatNum = MatTestParticle;//Mat;
	cSinEffect2[Index].sinFace.x = Posi.x;
	cSinEffect2[Index].sinFace.y = Posi.y; 
	cSinEffect2[Index].sinFace.z = Posi.z;
	cSinEffect2[Index].Posi.x = cSinEffect2[Index].sinFace.x;
	cSinEffect2[Index].Posi.y = cSinEffect2[Index].sinFace.y;
	cSinEffect2[Index].Posi.z = cSinEffect2[Index].sinFace.z;
	cSinEffect2[Index].Max_Time = rand()%50+50;
	cSinEffect2[Index].sinFace.TexRect = sinTexRect;
	cSinEffect2[Index].RotateDistance.z = cSinEffect2[Index].Gravity+10;
	cSinEffect2[Index].RotateSpeedCnt = rand()%4096;
	cSinEffect2[Index].MoveKind = SIN_MOVE_SPARK;
	cSinEffect2[Index].MoveSpeed.y = 5 - rand()%10; 

	cSinEffect2[Index].AlphaTime = cSinEffect2[Index].Max_Time - 30;
	cSinEffect2[Index].AlphaCount = 1;
	cSinEffect2[Index].AlphaAmount = 5;


	return TRUE;
}

/*----------------------------------------------------------------------------*
*						   송편 파티클 
*-----------------------------------------------------------------------------*/	
int sinSongPyeunEffect(POINT3D Posi)
{
	int  i = 0; 
	int  Size = 0; 
	SetDynLight( Posi.x  , Posi.y+5000 , Posi.z ,100, 100,100, 255, 100 ,1);         
	for( i = 0 ; i < 30 ; i++){ 
		Index = sinSearchEmptyIndex();                                                 
		sinEffectDefaultSet(Index , SIN_EFFECT_FACE ,  0,&Posi,5000); //테스트할때 +10000을 해줬다 
		cSinEffect2[Index].sinFace.MatNum = MatSongPyeun;
		cSinEffect2[Index].sinFace.width  = 1000;
		cSinEffect2[Index].sinFace.height = 1000;
	
		cSinEffect2[Index].Max_Time = rand()%20+10;
		cSinEffect2[Index].Angle.x = ((rand()%(4096/2))-ANGLE_90)&ANGCLIP; 
		cSinEffect2[Index].Angle.z = 0;
		cSinEffect2[Index].Angle.y = rand()%4096;
		cSinEffect2[Index].MoveSpeed.z = 64;
		cSinEffect2[Index].MoveKind = SIN_MOVE_SONGPYEUN;
		cSinEffect2[Index].AlphaTime = cSinEffect2[Index].Max_Time - 10;
		cSinEffect2[Index].AlphaCount = 1;
		cSinEffect2[Index].AlphaAmount = 15;
		cSinEffect2[Index].MoveSpeed.y = rand()%4 + 1;


	}
	/*
	int  i = 0; 
	int  Size = 0; 
	for( i = 0 ; i < 30 ; i++){
		Index = sinSearchEmptyIndex();                                          
		SetDynLight( Posi.x  , Posi.y , Posi.z ,100, 100,100, 255, 100 ,1);        
		Index = sinSearchEmptyIndex();                                     
		sinEffectDefaultSet(Index , SIN_EFFECT_FACE ,  0,&Posi,5000); //테스트할때 +10000을 해줬다 
		Size = rand()%1000 + 500;
		cSinEffect2[Index].sinFace.height = Size;
		cSinEffect2[Index].sinFace.width  = Size;
		cSinEffect2[Index].sinFace.MatNum = MatSongPyeun;//Mat;
		cSinEffect2[Index].Max_Time = rand()%50+50;
		cSinEffect2[Index].RotateDistance.z = cSinEffect2[Index].Gravity+10;
		cSinEffect2[Index].RotateSpeedCnt = rand()%4096;
		cSinEffect2[Index].MoveKind = SIN_MOVE_SONGPYEUN;
		cSinEffect2[Index].MoveSpeed.y = -(rand()%2+1);
		cSinEffect2[Index].AlphaTime = cSinEffect2[Index].Max_Time - 30;
		cSinEffect2[Index].AlphaCount = 1;
		cSinEffect2[Index].AlphaAmount = 5;
	}
	*/

	return TRUE;
}
