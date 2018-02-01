/*----------------------------------------------------------------------------*
*	파일명 :  sinPublicEffect.cpp	
*	하는일 :  각종 이펙트에 쓰일 각각의 이펙트 
*	작성일 :  최종업데이트 2002년 10월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#include "sinLinkHeader.h"

#define SIN_EFFECT_WIDELINE			1001
#define	SIN_EFFECT_WIDEPARTICLE		1002
#define SIN_EFFECT_BOMBPARTICLE		1003
#define SIN_EFFECT_LIGHT5			1004
#define SIN_EFFECT_SPOUT2			1005
#define SIN_EFFECT_GATHERLINE		1006
#define SIN_EFFECT_GATHERLINE2		1007
#define SIN_EFFECT_WIDECONTINUELINE		1008
#define SIN_EFFECT_WIDECONTINUELINE2	1009
#define SIN_EFFECT_GATHERCIRCLEPARTICLE	1010

#define SIN_EFFECT_HIT2				1011
#define SIN_EFFECT_HIT2_PARTICLE	1012

//////////// 몬스터 이펙트
#define SIN_EFFECT_SEN							2000
#define SIN_EFFECT_SEN_PARTICLE					2001
#define SIN_EFFECT_MUTENTTREE_SMOKE				2002
#define SIN_EFFECT_MUTENTTREE_SMOKE_PARTICLE	2003
#define SIN_EFFECT_MUTENTTREE_ATTACK			2004
#define SIN_EFFECT_MUTENTTREE_ATTACK_PARTICLE	2005
#define SIN_EFFECT_MUTENTTREE_ATTACK_PARTICLE2  2006
#define SIN_EFFECT_MUTENTTREE_HIT				2007
#define SIN_EFFECT_MUTENTTREE_FIRE				2008
#define SIN_EFFECT_MUTENTTREE_FIRE_PARTICLE		2009	
#define SIN_EFFECT_RATOO						2010
#define SIN_EFFECT_RATOO_PARTICLE				2011


int MatLine2[5];
int MatLight5[5];
int MatHit2Circle[3];
int MatMonParticle[10];
int MatMonVigorRatoo[5];
/*----------------------------------------------------------------------------*
*					        Init
*-----------------------------------------------------------------------------*/	
void sinInitPublicEffect()
{
	int i = 0;
	char *Path = "Image\\SinImage\\Effect\\PublicEffect";
	char *Path2 = "Image\\SinImage\\Effect\\MonsterEffect";

	char szBuff[128];

	wsprintf(szBuff,"%s\\Line\\Line01.tga",Path);
	MatLine2[0] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_LAMP );	

	for(i = 0 ; i < 5 ; i++){
		wsprintf(szBuff,"%s\\Light\\Light0%d.tga",Path,i+1);
		MatLight5[i] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	}
	for(i = 0 ; i < 3 ; i++){
		wsprintf(szBuff,"%s\\Hit\\HitYellow%d.tga",Path,i+1);
		MatHit2Circle[i] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	}
	for(i = 0 ; i < 3 ; i++){
		wsprintf(szBuff,"%s\\Hit\\HitYellow%d.tga",Path,i+1);
		MatHit2Circle[i] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	}

	wsprintf(szBuff,"%s\\Particle\\MonParticle01.tga",Path2);
	MatMonParticle[0] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_SHADOW );	

	for(i = 1 ; i < 10 ; i++){
		wsprintf(szBuff,"%s\\Particle\\MonParticle0%d.tga",Path2,i+1);
		MatMonParticle[i] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	
	}

	wsprintf(szBuff,"%s\\Ratoo\\glow.tga",Path2);
	MatMonVigorRatoo[0] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_LAMP );	
	wsprintf(szBuff,"%s\\Ratoo\\glow1.tga",Path2);
	MatMonVigorRatoo[1] = CreateTextureMaterial( szBuff , 0, 0, 0,0, SMMAT_BLEND_LAMP );	

}
/*----------------------------------------------------------------------------*
*					       TEST KEY
*-----------------------------------------------------------------------------*/	
int sinPublicEffectTestKey()
{
	//lpCharSelPlayer	//한번 선택한 대상의 포인터 
	//lpCharMsTrace		//계속 선택한 대상의 포인터
	
	POINT3D Posi = {lpCurPlayer->pX,lpCurPlayer->pY+10000,lpCurPlayer->pZ};  

	//sinEffect_Sen(&Posi); 
	if(smConfig.DebugMode){
		//sinEffect_Ratoo_Vigor(lpCurPlayer);
		//sinEffect_MutentTree_Smoke(&Posi); 
		//sinEffect_Sen(&Posi);

	}

	/*
	if(sinGetKeyClick('9')){      
		//sinEffect_Ratoo(lpCurPlayer);
		//sinEffect_MutentTree_Attack(lpCurPlayer,lpCharSelPlayer);
		//sinEffect_WideLine(&Posi,MatLine2[0],128,30);
		//sinEffect_BombParticle(&Posi,MatLine2[0],1000,30);
		//sinEffect_Light5(&Posi,10000);
		//sinEffect_SpoutParticle(&Posi,MatLine2[0],1,500,30,10); 
		//sinEffect_GatherLine(lpCurPlayer,MatLine2[0],70);
		//sinEffect_WideContinueLine(lpCurPlayer,MatLine2[0],70,7000);
		//Posi.y -= 3000;
		//sinEffect_GatherCircleParticle(&Posi,MatLine2[0]);
		//sinEffect_Hit2(&Posi,MatHit2Circle[0]);
		//sinEffect_Hit2(&Posi,MatLine2[0]);

	} 
	*/

	return TRUE;  
}
/*----------------------------------------------------------------------------*
*					        MOVE
*-----------------------------------------------------------------------------*/	
void sinPublicEffectMove(cSINEFFECT2 *pEffect)
{
	POINT3D Posi;
	switch(pEffect->CODE){      
		case SIN_EFFECT_WIDELINE:   
			sinGetMoveLocation2(pEffect);         
			GetMoveLocation( 0 , 0, pEffect->MoveSpeed.z, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->Posi.x  += GeoResult_X;
			pEffect->Posi.y  += GeoResult_Y;
			pEffect->Posi.z  += GeoResult_Z;
			pEffect->RanderAngle.y = (-pEffect->Angle.y+ANGLE_180)&ANGCLIP; 
			pEffect->Angle.z +=16;
			pEffect->Angle.z &= ANGCLIP;
//			pEffect->RanderAngle.z +=16;
//			pEffect->RanderAngle.z &= ANGCLIP;


		break;
		case SIN_EFFECT_WIDEPARTICLE:
			sinGetMoveLocation2(pEffect);       
			GetMoveLocation( 0 , 0, pEffect->MoveSpeed.z, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->sinFace.x  += GeoResult_X;
			pEffect->sinFace.y  += GeoResult_Y;
			pEffect->sinFace.z  += GeoResult_Z;
			Posi.x = pEffect->sinFace.x;
			Posi.y = pEffect->sinFace.y;
			Posi.z = pEffect->sinFace.z;
			sinEffect_WideParticle(&Posi,pEffect->sinFace.MatNum , pEffect->Size.x);
		break;
		case SIN_EFFECT_BOMBPARTICLE:   
			pEffect->RotatePosi.x =  GetCos[ pEffect->RotateAngle&ANGCLIP ] + pEffect->RotateDistance.z*GetSin[ pEffect->RotateAngle&ANGCLIP ];     
			pEffect->RotatePosi.z = -GetSin[ pEffect->RotateAngle&ANGCLIP ] + pEffect->RotateDistance.z*GetCos[ pEffect->RotateAngle&ANGCLIP ];
			pEffect->RotatePosi.x >>=16;
			pEffect->RotatePosi.z >>=16;
			pEffect->sinFace.x += pEffect->RotatePosi.x;
			pEffect->sinFace.z += pEffect->RotatePosi.z;
			pEffect->Gravity -=4;
			pEffect->sinFace.y += pEffect->MoveSpeed.y+pEffect->Gravity;
		break;
		case SIN_EFFECT_SPOUT2:
			pEffect->RotatePosi.x =  GetCos[ pEffect->RotateAngle&ANGCLIP ] + pEffect->RotateDistance.z*GetSin[ pEffect->RotateAngle&ANGCLIP ];     
			pEffect->RotatePosi.z = -GetSin[ pEffect->RotateAngle&ANGCLIP ] + pEffect->RotateDistance.z*GetCos[ pEffect->RotateAngle&ANGCLIP ];
			pEffect->RotatePosi.x >>=16;
			pEffect->RotatePosi.z >>=16;
			pEffect->sinFace.x += pEffect->RotatePosi.x;
			pEffect->sinFace.z += pEffect->RotatePosi.z;
			pEffect->Gravity -=5;
			pEffect->sinFace.y += pEffect->MoveSpeed.y+pEffect->Gravity;
		break;
		case SIN_EFFECT_GATHERLINE:
			sinEffect_GatherLine2(pEffect->pChar,pEffect->ObjMat);

		break;
		case SIN_EFFECT_GATHERLINE2:   
			sinGetMoveLocation2(pEffect);           
			GetMoveLocation( 0 , 0, -pEffect->MoveSpeed.z, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->Posi.x  += GeoResult_X;
			pEffect->Posi.y  += GeoResult_Y;
			pEffect->Posi.z  += GeoResult_Z;
			pEffect->RanderAngle.y = (-pEffect->Angle.y+ANGLE_180)&ANGCLIP; 
			pEffect->Angle.z +=16;
			pEffect->Angle.z &= ANGCLIP;
			
			/*
			pEffect->RanderAngle.y = (-pEffect->Angle.y+ANGLE_180)&ANGCLIP;    
			pEffect->Posi.x  -= pEffect->MoveSpeed.x;
			pEffect->Posi.y  -= pEffect->MoveSpeed.y;
			pEffect->Posi.z  -= pEffect->MoveSpeed.z;
			pEffect->Angle.z +=16;
			pEffect->Angle.z &= ANGCLIP;
			*/


		break; 
		case SIN_EFFECT_WIDECONTINUELINE:
			sinEffect_WideContinueLine2(&pEffect->Posi,pEffect->ObjMat);

		break;

		case SIN_EFFECT_WIDECONTINUELINE2:
			sinGetMoveLocation2(pEffect);            
			GetMoveLocation( 0 , 0, pEffect->MoveSpeed.z, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->Posi.x  += GeoResult_X;
			pEffect->Posi.y  += GeoResult_Y;
			pEffect->Posi.z  += GeoResult_Z;
			pEffect->RanderAngle.y = (-pEffect->Angle.y+ANGLE_180)&ANGCLIP; 
			pEffect->Angle.z +=8;
			pEffect->Angle.z &= ANGCLIP;
		break;
		case SIN_EFFECT_GATHERCIRCLEPARTICLE:
			pEffect->RotateAngle += 50;                      
			pEffect->RotateDistance.z +=16;

			pEffect->RotatePosi.x =  pEffect->RotateDistance.y*GetCos[ pEffect->RotateAngle&ANGCLIP ] + pEffect->RotateDistance.z*GetSin[ pEffect->RotateAngle&ANGCLIP ];     
			pEffect->RotatePosi.z = -pEffect->RotateDistance.y*GetSin[ pEffect->RotateAngle&ANGCLIP ] + pEffect->RotateDistance.z*GetCos[ pEffect->RotateAngle&ANGCLIP ];
			
			pEffect->RotatePosi.x >>=16;
			pEffect->RotatePosi.z >>=16;

			
			pEffect->sinFace.x =  pEffect->Posi.x +	pEffect->RotatePosi.x;
			pEffect->sinFace.z =  pEffect->Posi.z + pEffect->RotatePosi.z;
			
			/*
			if(pEffect->Index == 1)
				pEffect->sinFace.y +=  200;
			else
				pEffect->sinFace.y -=  200;
			*/

			//pEffect->Posi.x = lpCurPlayer->pX+pEffect->RotatePosi.x;
			//pEffect->Posi.z =lpCurPlayer->pZ+pEffect->RotatePosi.z;
			//pEffect->Posi.y +=  100;

			
			
			//pEffect->MoveSpeed.y +=20;
		break;
		case SIN_EFFECT_HIT2:

		break;
		case SIN_EFFECT_HIT2_PARTICLE:
			sinGetMoveLocation2(pEffect);              
			GetMoveLocation( 0 , 0, 32, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->sinFace.x  += GeoResult_X;
			pEffect->sinFace.y  += GeoResult_Y;
			pEffect->sinFace.z  += GeoResult_Z;

		break;
		case SIN_EFFECT_SEN:
			sinGetMoveLocation2(pEffect);                            
			GetMoveLocation( 0 , 0, 50, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->sinFace.x  += GeoResult_X;
			pEffect->sinFace.y  += GeoResult_Y;
			pEffect->sinFace.z  += GeoResult_Z;
			//pEffect->Gravity -=2;
			pEffect->sinFace.y  += pEffect->MoveSpeed.y+pEffect->Gravity;
			pEffect->Posi.x = pEffect->sinFace.x;
			pEffect->Posi.y = pEffect->sinFace.y;
			pEffect->Posi.z = pEffect->sinFace.z;
			//if((pEffect->Time % 3) ==0)
			//	sinEffect_Sen_Particle(&pEffect->Posi);

		break;
		case SIN_EFFECT_SEN_PARTICLE:
			sinGetMoveLocation2(pEffect);                    
			GetMoveLocation( 0 , 0, 64, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->sinFace.x  += GeoResult_X;
			pEffect->sinFace.y  += GeoResult_Y;
			pEffect->sinFace.z  += GeoResult_Z;
		break;
		case SIN_EFFECT_MUTENTTREE_SMOKE:
			sinGetMoveLocation2(pEffect);                     
			GetMoveLocation( 0 , 0, 50, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->sinFace.x  += GeoResult_X;
			pEffect->sinFace.y  += GeoResult_Y;
			pEffect->sinFace.z  += GeoResult_Z;
			pEffect->sinFace.y  += pEffect->MoveSpeed.y;
			pEffect->Posi.x = pEffect->sinFace.x;
			pEffect->Posi.y = pEffect->sinFace.y;
			pEffect->Posi.z = pEffect->sinFace.z;
			sinEffect_MutentTree_Smoke_Particle(&pEffect->Posi);
			

		break;
		case SIN_EFFECT_MUTENTTREE_SMOKE_PARTICLE:
			sinGetMoveLocation2(pEffect);                    
			GetMoveLocation( 0 , 0, 64, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->sinFace.x  += GeoResult_X;
			pEffect->sinFace.y  += GeoResult_Y;
			pEffect->sinFace.z  += GeoResult_Z;
			//pEffect->sinFace.y  += pEffect->MoveSpeed.y;
		break;

		case SIN_EFFECT_MUTENTTREE_ATTACK:   //산만의 극치 걍 냅두자 
			pEffect->Posi.x += pEffect->MoveSpeed.x;            
			pEffect->Posi.z += pEffect->MoveSpeed.z;
			pEffect->Gravity -= 10;
			pEffect->MoveSpeed.y -= 20;
			pEffect->Posi.y += pEffect->MoveSpeed.y+pEffect->Gravity;
			sinEffect_MutentTree_Attack_Particle(&pEffect->Posi);
			if(sinEfect_CheckCrash(pEffect)){ //충돌체크
				sinEffect_MutentTree_Fire(&pEffect->Posi);
				memset(pEffect,0,sizeof(cSINEFFECT2)); //초기화 한다 
			}

			if(pEffect->Flag && pEffect->Time >= pEffect->Max_Time-1){
				sinEffect_MutentTree_Fire(&pEffect->Posi);
				memset(pEffect,0,sizeof(cSINEFFECT2)); //초기화 한다 
			}

			
		break;

		case SIN_EFFECT_MUTENTTREE_FIRE:
			sinGetMoveLocation2(pEffect);                       
			GetMoveLocation( 0 , 0, 50, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->sinFace.x  += GeoResult_X;
			pEffect->sinFace.y  += GeoResult_Y;
			pEffect->sinFace.z  += GeoResult_Z;
			pEffect->sinFace.y  += pEffect->MoveSpeed.y;
			pEffect->Posi.x = pEffect->sinFace.x;
			pEffect->Posi.y = pEffect->sinFace.y;
			pEffect->Posi.z = pEffect->sinFace.z;
			if((pEffect->Time % 2) == 0)
				sinEffect_MutentTree_Fire_Particle(&pEffect->Posi); 
		break;
		case SIN_EFFECT_MUTENTTREE_FIRE_PARTICLE:
			sinGetMoveLocation2(pEffect);                     
			GetMoveLocation( 0 , 0, 128, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->sinFace.x  += GeoResult_X;
			pEffect->sinFace.y  += GeoResult_Y;
			pEffect->sinFace.z  += GeoResult_Z;
			//pEffect->sinFace.y  += pEffect->MoveSpeed.y;

		break;

		case SIN_EFFECT_MUTENTTREE_ATTACK_PARTICLE2:
			sinGetMoveLocation2(pEffect);                        
			GetMoveLocation( 0 , 0, 64 , pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->sinFace.x  += GeoResult_X;
			pEffect->sinFace.y  += GeoResult_Y;
			pEffect->sinFace.z  += GeoResult_Z;

			pEffect->sinFace.y += pEffect->MoveSpeed.y; 

		break;
		case SIN_EFFECT_MUTENTTREE_ATTACK_PARTICLE:
			pEffect->sinFace.y += pEffect->MoveSpeed.y; 

		break;
		case SIN_EFFECT_MUTENTTREE_HIT:
			sinGetMoveLocation2(pEffect);                     
			GetMoveLocation( 0 , 0, 256, pEffect->Angle.x, pEffect->Angle.y, 0 );
			pEffect->sinFace.x  += GeoResult_X;
			pEffect->sinFace.z  += GeoResult_Z;
			pEffect->Gravity -= 5;
			pEffect->sinFace.y  += GeoResult_Y+pEffect->MoveSpeed.y+pEffect->Gravity;

		break;
		case SIN_EFFECT_RATOO:
			if(pEffect->Time == 1 && pEffect->ActionTime[0]==3){    
				sinGetMoveLocation2(pEffect);   
				GetMoveLocation(  0, 0,256*32*4 , pEffect->Angle.x, (-(pEffect->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP, 0 );
				Posi.x = pEffect->Posi.x;
				Posi.y = pEffect->Posi.y;
				Posi.z = pEffect->Posi.z;

				Posi.x += GeoResult_X;
				Posi.y += GeoResult_Y;
				Posi.z += GeoResult_Z;
				sinEffect_Light5(&Posi,20000); 
				SetDynLight( Posi.x , Posi.y , Posi.z ,255, 255, 255, 255, 200 ,1);          
			}
		break;
		case SIN_EFFECT_RATOO_PARTICLE:
			pEffect->sinFace.y +=100; 
			Posi.x = pEffect->sinFace.x;
			Posi.y = pEffect->sinFace.y;
			Posi.z = pEffect->sinFace.z;

			if((pEffect->Time %20)==0)
				sinEffect_Ratoo_Vigor_Partilce(&Posi);

		break;

	}
}

/*----------------------------------------------------------------------------*
*					        Wide Lind
*-----------------------------------------------------------------------------*/	
int sinEffect_WideContinueLine(smCHAR *pChar , int Mat ,int Time,int Height)
{
	Index2 = sinSearchEmptyIndex();                       
	sinEffectDefaultSet(Index2 , SIN_EFFECT_MESH ,  pChar,0,Height);
	cSinEffect2[Index2].ObjMat = Mat;
	cSinEffect2[Index2].Max_Time = Time;
	cSinEffect2[Index2].CODE = SIN_EFFECT_WIDECONTINUELINE;
	cSinEffect2[Index2].BoneFlag = 1;
	return TRUE;
}
int sinEffect_WideContinueLine2(POINT3D *pPosi , int Mat )
{
	int  i = 0;
	int  Size = 0; 
	int  distance = 0;
	Index2 = sinSearchEmptyIndex();                            
	sinEffectDefaultSet(Index2 , SIN_EFFECT_MESH ,  0,pPosi,0);     
	cSinEffect2[Index2].ObjMat = Mat;
	cSinEffect2[Index2].Size.x = 512; 
	cSinEffect2[Index2].Size.y = 40*128; 
	cSinEffect2[Index2].Max_Time = rand()%20+40;
	cSinEffect2[Index2].Angle.x = rand()%(4096)&ANGCLIP;//((rand()%(4096/2))-ANGLE_90)&ANGCLIP; 
	cSinEffect2[Index2].Angle.y = rand()%(4096)&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.z = 128;
	sinCreateObject(&cSinEffect2[Index2]);
	cSinEffect2[Index2].CODE = SIN_EFFECT_WIDECONTINUELINE2;
	cSinEffect2[Index2].AniCount = 1;

	distance = rand()%5+1;

	sinGetMoveLocation2(&cSinEffect2[Index2]);       
	GetMoveLocation( 0 , 0, distance*512*4, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].Posi.x  += GeoResult_X;
	cSinEffect2[Index2].Posi.y  += GeoResult_Y;
	cSinEffect2[Index2].Posi.z  += GeoResult_Z;

	cSinEffect2[Index2].AlphaAmount = 10;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 10;
	//페이드 인
	cSinEffect2[Index2].AlphaFadeInFlag = 1;
	cSinEffect2[Index2].Color_A = 200;

	return TRUE;
}


int sinEffect_WideLine(POINT3D *pPosi , int Mat , int Lenght , int Num)
{
	int  i = 0;
	int  Size = 0; 
	for(i = 0 ; i < Num ; i++){         
		//한쪽면  
		Index2 = sinSearchEmptyIndex();                      
		sinEffectDefaultSet(Index2 , SIN_EFFECT_MESH ,  0,pPosi,0);
		cSinEffect2[Index2].ObjMat = Mat;
		cSinEffect2[Index2].Size.x = 512; 
		cSinEffect2[Index2].Size.y = 40*Lenght; 
		cSinEffect2[Index2].Max_Time = rand()%20+50;
		cSinEffect2[Index2].Angle.x = rand()%(4096)&ANGCLIP;//((rand()%(4096/2))-ANGLE_90)&ANGCLIP; 
		cSinEffect2[Index2].Angle.y = rand()%(4096)&ANGCLIP;
		cSinEffect2[Index2].MoveSpeed.z = 128;
		sinCreateObject(&cSinEffect2[Index2]);
		cSinEffect2[Index2].CODE = SIN_EFFECT_WIDELINE;
		cSinEffect2[Index2].AniCount = 1;
		cSinEffect2[Index2].AlphaAmount = 10;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 10;
		//cSinEffect2[Index2].Time = (i%10)*-1;

	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*					        Gather Line
*-----------------------------------------------------------------------------*/	
int sinEffect_GatherLine(smCHAR *pChar , int Mat ,int Time)
{
	Index2 = sinSearchEmptyIndex();                      
	sinEffectDefaultSet(Index2 , SIN_EFFECT_MESH ,  pChar,0,0);
	cSinEffect2[Index2].ObjMat = Mat;
	cSinEffect2[Index2].Max_Time = Time;
	cSinEffect2[Index2].CODE = SIN_EFFECT_GATHERLINE;
	cSinEffect2[Index2].BoneFlag = 1;
	return TRUE;
}
int sinEffect_GatherLine2(smCHAR *pChar , int Mat )
{
	int  i = 0;
	int  Size = 0;  
	int  distance = 0;
	Index2 = sinSearchEmptyIndex();                          
	sinEffectDefaultSet(Index2 , SIN_EFFECT_MESH ,  pChar,0,7000);     
	cSinEffect2[Index2].ObjMat = Mat;
	cSinEffect2[Index2].Size.x = 512; 
	cSinEffect2[Index2].Size.y = 40*128; 
	cSinEffect2[Index2].Max_Time = rand()%20+40;
	cSinEffect2[Index2].Angle.x = rand()%(4096)&ANGCLIP;//((rand()%(4096/2))-ANGLE_90)&ANGCLIP; 
	cSinEffect2[Index2].Angle.y = rand()%(4096)&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.z = 128;
	sinCreateObject(&cSinEffect2[Index2]);
	cSinEffect2[Index2].CODE = SIN_EFFECT_GATHERLINE2;
	cSinEffect2[Index2].AniCount = 1;

	distance = rand()%10+1;

	sinGetMoveLocation2(&cSinEffect2[Index2]);       
	GetMoveLocation( 0 , 0, distance*512*4, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].Posi.x  += GeoResult_X;
	cSinEffect2[Index2].Posi.y  += GeoResult_Y;
	cSinEffect2[Index2].Posi.z  += GeoResult_Z;

	cSinEffect2[Index2].pChar = pChar;

	cSinEffect2[Index2].AlphaAmount = 10;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 10;
	//cSinEffect2[Index2].Time = (i%10)*-1;

	/*
	if(cSinEffect2[Index2].pChar){  
		cSinEffect2[Index2].MoveSpeed.x = (cSinEffect2[Index2].Posi.x - pChar->pX)/50; 
		cSinEffect2[Index2].MoveSpeed.y = (cSinEffect2[Index2].Posi.y - pChar->pY)/50;
		cSinEffect2[Index2].MoveSpeed.z = (cSinEffect2[Index2].Posi.z - pChar->pZ)/50;
	}
	*/

	//페이드 인
	cSinEffect2[Index2].AlphaFadeInFlag = 1;
	cSinEffect2[Index2].Color_A = 200;

	return TRUE;
}
/*----------------------------------------------------------------------------*
*					        Wide Particle
*-----------------------------------------------------------------------------*/	
int sinEffect_WideParticle_Bone(POINT3D *pPosi , int Mat , int Size , int Time , int Num , int Speed)
{
	for(int i = 0 ; i < Num ; i++){        
		Index2 = sinSearchEmptyIndex();           
		sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
		cSinEffect2[Index2].sinFace.MatNum = Mat;
		cSinEffect2[Index2].Size.x = Size; //사이즈는 편의상 X에만 넣어둔다 
		cSinEffect2[Index2].Max_Time = rand()%Time + (Time/2);
		cSinEffect2[Index2].Angle.x = ((rand()%(4096/2))-ANGLE_90)&ANGCLIP; 
		cSinEffect2[Index2].Angle.y = rand()%2048+(i*16);
		cSinEffect2[Index2].MoveSpeed.z = Speed;
		cSinEffect2[Index2].CODE = SIN_EFFECT_WIDEPARTICLE;
		cSinEffect2[Index2].BoneFlag = 1;

	}


	return TRUE;
}
int sinEffect_WideParticle(POINT3D *pPosi , int Mat , int Size)
{

	int TotalSize;
	Index2 = sinSearchEmptyIndex();                                                              
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE , 0  , pPosi,0);  
	TotalSize = rand()%Size + Size;
	cSinEffect2[Index2].sinFace.height = TotalSize;
	cSinEffect2[Index2].sinFace.width  = TotalSize;
	cSinEffect2[Index2].sinFace.MatNum = Mat;
	cSinEffect2[Index2].Max_Time = rand()%3+10;
	cSinEffect2[Index2].AlphaTime = 10;
	cSinEffect2[Index2].AlphaAmount = 10;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].Angle.x = rand()%(4096)&ANGCLIP;//((rand()%(4096/2))-ANGLE_90)&ANGCLIP; 
	cSinEffect2[Index2].Angle.y = rand()%(4096)&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.z = 128;
	sinGetMoveLocation2(&cSinEffect2[Index2]);   
  	GetMoveLocation( 0 , 0, 128, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;

	//사이즈
	cSinEffect2[Index2].SizeDecreTime = 1;
	cSinEffect2[Index2].SizeAmount = 100;

	return TRUE;
}

/*----------------------------------------------------------------------------*
*					        Bomb Particle
*-----------------------------------------------------------------------------*/	
int sinEffect_BombParticle(POINT3D *pPosi , int Mat , int Size , int Num)
{

	int  i = 0;
	for(i = 0 ; i < Num ; i++){          
		Index2 = sinSearchEmptyIndex();                         
		sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
		cSinEffect2[Index2].sinFace.MatNum = Mat;
		cSinEffect2[Index2].sinFace.height = Size; 
		cSinEffect2[Index2].sinFace.width  = Size; 
		cSinEffect2[Index2].Max_Time = rand()%20+50;
		cSinEffect2[Index2].CODE = SIN_EFFECT_BOMBPARTICLE;
		cSinEffect2[Index2].AniCount = 1;
		cSinEffect2[Index2].AlphaAmount = 10;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 22;
		cSinEffect2[Index2].Time = (i%10)*-1;
		cSinEffect2[Index2].RotateAngle = ((rand()%256)*i)+Num;
		cSinEffect2[Index2].RotateDistance.z = 128;
		cSinEffect2[Index2].RotatePosi.x =  GetCos[ cSinEffect2[Index2].RotateAngle&ANGCLIP ] + cSinEffect2[Index2].RotateDistance.z*GetSin[ cSinEffect2[Index2].RotateAngle&ANGCLIP ];     
		cSinEffect2[Index2].RotatePosi.z = -GetSin[ cSinEffect2[Index2].RotateAngle&ANGCLIP ] + cSinEffect2[Index2].RotateDistance.z*GetCos[ cSinEffect2[Index2].RotateAngle&ANGCLIP ];
		cSinEffect2[Index2].RotatePosi.x >>=16;
		cSinEffect2[Index2].RotatePosi.z >>=16;
		cSinEffect2[Index2].sinFace.x += cSinEffect2[Index2].RotatePosi.x;
		cSinEffect2[Index2].sinFace.z += cSinEffect2[Index2].RotatePosi.z;
		cSinEffect2[Index2].MoveSpeed.y = rand()%100+50;

	}

	return TRUE;
}
/*----------------------------------------------------------------------------*
*					        Light
*-----------------------------------------------------------------------------*/	
int sinEffect_Light5(POINT3D *pPosi , int Size )
{
	Index2 = sinSearchEmptyIndex();                           
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatLight5[0];
	cSinEffect2[Index2].sinFace.height = Size*2; 
	cSinEffect2[Index2].sinFace.width  = Size*2; 
	cSinEffect2[Index2].Max_Time = 50;
	cSinEffect2[Index2].CODE = SIN_EFFECT_LIGHT5;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 10;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 22;
	cSinEffect2[Index2].lpMatAni = MatLight5;
	cSinEffect2[Index2].AniMax = 5;
	cSinEffect2[Index2].AniCount = 10;
	cSinEffect2[Index2].AniTime = 10;
	cSinEffect2[Index2].SizeIncreTime = 1;
	cSinEffect2[Index2].SizeAmount = 100;
	return TRUE;
}	

int sinEffect_SpoutParticle(POINT3D *pPosi ,int Mat ,int Num , int Size , int Time , int Gravity )
{
	int i; 
	int TotalSize = 0;
	for(i = 0 ; i < Num ; i++){          
		Index2 = sinSearchEmptyIndex();                          
		sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
		cSinEffect2[Index2].sinFace.MatNum = Mat;
		TotalSize = rand()%Size+200;
		cSinEffect2[Index2].sinFace.height = TotalSize; 
		cSinEffect2[Index2].sinFace.width  = TotalSize; 
		cSinEffect2[Index2].Max_Time = rand()%20+Time;
		cSinEffect2[Index2].CODE = SIN_EFFECT_SPOUT2;
		cSinEffect2[Index2].AniCount = 1;
		cSinEffect2[Index2].AlphaAmount = 10;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 22;
		cSinEffect2[Index2].Time = (i%10)*-1;
		cSinEffect2[Index2].RotateAngle = ((rand()%4096))+Num;
		cSinEffect2[Index2].RotateDistance.z = 32;
		cSinEffect2[Index2].RotatePosi.x =  GetCos[ cSinEffect2[Index2].RotateAngle&ANGCLIP ] + cSinEffect2[Index2].RotateDistance.z*GetSin[ cSinEffect2[Index2].RotateAngle&ANGCLIP ];     
		cSinEffect2[Index2].RotatePosi.z = -GetSin[ cSinEffect2[Index2].RotateAngle&ANGCLIP ] + cSinEffect2[Index2].RotateDistance.z*GetCos[ cSinEffect2[Index2].RotateAngle&ANGCLIP ];
		cSinEffect2[Index2].RotatePosi.x >>=16;
		cSinEffect2[Index2].RotatePosi.z >>=16;
		cSinEffect2[Index2].sinFace.x += cSinEffect2[Index2].RotatePosi.x;
		cSinEffect2[Index2].sinFace.z += cSinEffect2[Index2].RotatePosi.z;
		cSinEffect2[Index2].MoveSpeed.y = rand()%20+10;
		cSinEffect2[Index2].Gravity = Gravity;

	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*					       RiseParticle
*-----------------------------------------------------------------------------*/	
int sinEffect_GatherCircleParticle(POINT3D *pPosi ,int Mat )
{

	int i; 
	int TotalSize = 0;
	for(i = 0 ; i < 200 ; i++){           
		Index2 = sinSearchEmptyIndex();                             
		sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
		cSinEffect2[Index2].sinFace.MatNum = Mat;
		TotalSize = rand()%1000+200;
		cSinEffect2[Index2].sinFace.height = TotalSize; 
		cSinEffect2[Index2].sinFace.width  = TotalSize; 
		cSinEffect2[Index2].Max_Time = rand()%10+25;
		cSinEffect2[Index2].CODE = SIN_EFFECT_GATHERCIRCLEPARTICLE;
		cSinEffect2[Index2].AniCount = 1;
		cSinEffect2[Index2].AlphaAmount = 10;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 22;
		cSinEffect2[Index2].RotateAngle = (rand()%256)*(i+1);   
		cSinEffect2[Index2].RotateDistance.z = 128*18*2;
		cSinEffect2[Index2].RotatePosi.x = GetCos[ cSinEffect2[Index2].RotateAngle&ANGCLIP ] + cSinEffect2[Index2].RotateDistance.z*GetSin[ cSinEffect2[Index2].RotateAngle&ANGCLIP ];     
		cSinEffect2[Index2].RotatePosi.z = -GetSin[ cSinEffect2[Index2].RotateAngle&ANGCLIP ] + cSinEffect2[Index2].RotateDistance.z*GetCos[ cSinEffect2[Index2].RotateAngle&ANGCLIP ];     
		cSinEffect2[Index2].RotatePosi.x >>=16;
		cSinEffect2[Index2].RotatePosi.z >>=16;

		cSinEffect2[Index2].Posi.x +=cSinEffect2[Index2].RotatePosi.x;
		cSinEffect2[Index2].Posi.z +=cSinEffect2[Index2].RotatePosi.z;
		cSinEffect2[Index2].Time = (rand()%50) * -1;
		cSinEffect2[Index2].Index = i%2;
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*					       Hit
*-----------------------------------------------------------------------------*/	
int sinEffect_Hit2(POINT3D *pPosi ,int Mat )
{
	int Size = 2000;  
	int TempIndex = 0;
	Index2 = sinSearchEmptyIndex();                                 
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = Mat; 
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size;  
	cSinEffect2[Index2].Max_Time = 20;
	cSinEffect2[Index2].CODE = SIN_EFFECT_HIT2;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 10;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 22;
	cSinEffect2[Index2].SizeIncreTime = 1;
	cSinEffect2[Index2].SizeAmount = 1000; 
	TempIndex = Index2;
	Index2 = sinSearchEmptyIndex();                                 
	memcpy(&cSinEffect2[Index2],&cSinEffect2[TempIndex],sizeof(cSINEFFECT2));


	Index2 = sinSearchEmptyIndex();                              
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatHit2Circle[1];
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = 20;
	cSinEffect2[Index2].CODE = SIN_EFFECT_HIT2;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 10;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 22;
	cSinEffect2[Index2].SizeIncreTime = 1;
	cSinEffect2[Index2].SizeAmount = 500;
	cSinEffect2[Index2].FaceAngleY = -512;
	cSinEffect2[Index2].Time = -10;

	TempIndex = Index2;
	Index2 = sinSearchEmptyIndex();                                 
	memcpy(&cSinEffect2[Index2],&cSinEffect2[TempIndex],sizeof(cSINEFFECT2));

	for(int i = 0 ; i < 20 ; i++){
		Index2 = sinSearchEmptyIndex();                              
		sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
		cSinEffect2[Index2].sinFace.MatNum = MatLine2[0];
		cSinEffect2[Index2].sinFace.height = Size/2; 
		cSinEffect2[Index2].sinFace.width  = Size/2; 
		cSinEffect2[Index2].Max_Time = 30;
		cSinEffect2[Index2].CODE = SIN_EFFECT_HIT2_PARTICLE;
		cSinEffect2[Index2].AniCount = 1;
		cSinEffect2[Index2].AlphaAmount = 10;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 22;
//		cSinEffect2[Index2].SizeIncreTime = 1;
//		cSinEffect2[Index2].SizeAmount = 500;

		cSinEffect2[Index2].Angle.x = rand()%(4096)&ANGCLIP;//((rand()%(4096/2))-ANGLE_90)&ANGCLIP; 
		cSinEffect2[Index2].Angle.y = rand()%(4096)&ANGCLIP;
		cSinEffect2[Index2].Time = -12;
		sinGetMoveLocation2(&cSinEffect2[Index2]);   
  		GetMoveLocation( 0 , 0, 1024, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
		cSinEffect2[Index2].sinFace.x  += GeoResult_X;
		cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
		cSinEffect2[Index2].sinFace.z  += GeoResult_Z;

	}

	return TRUE;
}

/**************************************************************************************
*								몬스터 이펙트 
/**************************************************************************************/
/*----------------------------------------------------------------------------*
*					       Sen
*-----------------------------------------------------------------------------*/	
int EffectCount3;
int sinEffect_Sen(POINT3D *pPosi) //센 이펙트 
{

	int Size;
	
	
	Size = 10000;        
 	Index2 = sinSearchEmptyIndex();                                        
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatLight5[0];  
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size;
	cSinEffect2[Index2].Max_Time = 4;
	cSinEffect2[Index2].sinFace.Transparency = 150;
	
	
	//return TRUE;
	EffectCount3++;                         
	if(EffectCount3 <= 8)return FALSE;
	EffectCount3 = 0;


	Size = 2500;      
 	Index2 = sinSearchEmptyIndex();                                        
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatLight5[1];  
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = rand()%20+40;
	cSinEffect2[Index2].CODE = SIN_EFFECT_SEN;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 30;
	cSinEffect2[Index2].SizeDecreTime = cSinEffect2[Index2].Max_Time-10;
	cSinEffect2[Index2].SizeAmount = 100; 
	cSinEffect2[Index2].Angle.x = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;

//	cSinEffect2[Index2].Angle.x = (rand()%2047&ANGCLIP)+2047;
//	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	//cSinEffect2[Index2].MoveSpeed.y = rand()%15 + 15;
	//cSinEffect2[Index2].Gravity = 10;

	sinGetMoveLocation2(&cSinEffect2[Index2]);   
  	GetMoveLocation( 0 , 0, 1024*2, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;

//	cSinEffect2[Index2].sinFace.r = rand()%255;
//	cSinEffect2[Index2].sinFace.g = rand()%255;
//	cSinEffect2[Index2].sinFace.b = rand()%255;
	return TRUE;

}
int sinEffect_Sen_Particle(POINT3D *pPosi)
{
	return TRUE; 
	int Size = 2000;     
 	Index2 = sinSearchEmptyIndex();                                         
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatMonParticle[1]; 
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = rand()%10+25;
	cSinEffect2[Index2].CODE = SIN_EFFECT_SEN_PARTICLE;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = 1;
	cSinEffect2[Index2].SizeDecreTime = 1;
	cSinEffect2[Index2].SizeAmount = 20; 
	cSinEffect2[Index2].Angle.x = (rand()%2047&ANGCLIP)+2047;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.y = rand()%10 + 5;
	
	sinGetMoveLocation2(&cSinEffect2[Index2]);   
  	GetMoveLocation( 0 , 0, 256, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;

	return TRUE;
}
/*----------------------------------------------------------------------------*
*					       Mutent Tree
*-----------------------------------------------------------------------------*/	
int EffectCount2;
int sinEffect_MutentTree_Smoke(POINT3D *pPosi) //뮤턴트 트리 
{
	EffectCount2++;               
	if(EffectCount2 <= 15)return FALSE;
	EffectCount2 = 0;

	int Size = 3000;     
 	Index2 = sinSearchEmptyIndex();                                        
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatMonParticle[0]; 
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = rand()%20+40;
	cSinEffect2[Index2].CODE = SIN_EFFECT_MUTENTTREE_SMOKE;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 30;
	cSinEffect2[Index2].SizeDecreTime = cSinEffect2[Index2].Max_Time-10;
	cSinEffect2[Index2].SizeAmount = 50; 
	cSinEffect2[Index2].Angle.x = (rand()%2047&ANGCLIP)+2047;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.y = rand()%25 + 25;
	sinGetMoveLocation2(&cSinEffect2[Index2]);   
  	GetMoveLocation( 0 , 0, 256, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;
	return TRUE;

}
int sinEffect_MutentTree_Smoke_Particle(POINT3D *pPosi)
{
	int Size = 3000;     
 	Index2 = sinSearchEmptyIndex();                                         
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatMonParticle[0]; 
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = rand()%10+25;
	cSinEffect2[Index2].CODE = SIN_EFFECT_MUTENTTREE_SMOKE_PARTICLE;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = 1;
	cSinEffect2[Index2].SizeDecreTime = 1;
	cSinEffect2[Index2].SizeAmount = 20; 
	cSinEffect2[Index2].Angle.x = (rand()%2047&ANGCLIP)+2047;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.y = rand()%25 + 25;
	
	sinGetMoveLocation2(&cSinEffect2[Index2]);   
  	GetMoveLocation( 0 , 0, 256, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;
	
	return TRUE;
}

int sinEffect_MutentTree_Attack(smCHAR *pChar , smCHAR *desChar)
{

 	Index2 = sinSearchEmptyIndex();                                                            
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  pChar,0,6000);
	cSinEffect2[Index2].Max_Time = 50;
	cSinEffect2[Index2].CODE = SIN_EFFECT_MUTENTTREE_ATTACK;
	cSinEffect2[Index2].pChar = pChar;
	cSinEffect2[Index2].DesChar = desChar;

	if(pChar && desChar){ 
		GetRadian3D( pChar->pX, pChar->pY, pChar->pZ, cSinEffect2[Index2].DesChar->pX, cSinEffect2[Index2].DesChar->pY, cSinEffect2[Index2].DesChar->pZ );
		cSinEffect2[Index2].Angle.x = GeoResult_X; 
		cSinEffect2[Index2].Angle.y = (-(GeoResult_Y&ANGCLIP)+ANGLE_180)&ANGCLIP;
	
		cSinEffect2[Index2].MoveSpeed.x = (desChar->pX - pChar->pX )/40;
		cSinEffect2[Index2].MoveSpeed.z = (desChar->pZ - pChar->pZ )/40;
		cSinEffect2[Index2].MoveSpeed.y = (desChar->pY - pChar->pY )/20;

		//sinGetMoveLocation2(&cSinEffect2[Index2]);
		//GetMoveLocation( 256*16*2 , 0, 256*16*2, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );  
		//cSinEffect2[Index2].Posi.x  += GeoResult_X; 
		//cSinEffect2[Index2].Posi.z  += GeoResult_Z;

	}

//	pEffect->Posi.x += pEffect->MoveSpeed.x;            
//	pEffect->Posi.z += pEffect->MoveSpeed.z;
	cSinEffect2[Index2].Posi.x += cSinEffect2[Index2].MoveSpeed.x*13; //입위치를 맞추려고 날치기로 보정
	cSinEffect2[Index2].Posi.z += cSinEffect2[Index2].MoveSpeed.z*13;

//	GetMoveLocation( 0 , 0, 256*2*6, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );  
//	cSinEffect2[Index2].Posi.x  += GeoResult_X;
//	cSinEffect2[Index2].Posi.z  += GeoResult_Z;

	cSinEffect2[Index2].MoveSpeed.y = 600;
	cSinEffect2[Index2].BoneFlag = 1;

	return TRUE;
}

int EffectCount7;
int sinEffect_MutentTree_Fire(POINT3D *pPosi) //뮤턴트 트리 
{
//	EffectCount7++;             
//	if(EffectCount7 <= 0)return FALSE;
//	EffectCount7 = 0;
	int Cnt = 4; 
	int Size = 5000;           
	while( Cnt--){
	Index2 = sinSearchEmptyIndex();                                             
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatMonParticle[3]; 
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = rand()%20+40;
	cSinEffect2[Index2].CODE = SIN_EFFECT_MUTENTTREE_FIRE;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 30;
	cSinEffect2[Index2].SizeDecreTime = cSinEffect2[Index2].Max_Time-10;
	cSinEffect2[Index2].SizeAmount = 125; 
	cSinEffect2[Index2].Angle.x = (rand()%2047&ANGCLIP)+2047;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.y = rand()%25 + 25;
	sinGetMoveLocation2(&cSinEffect2[Index2]);   
  	GetMoveLocation( 0 , 0, 256*2, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;
	cSinEffect2[Index2].Time = -(Cnt/2);
	}
	return TRUE;

}
int IndexCnt5=0;
int sinEffect_MutentTree_Fire_Particle(POINT3D *pPosi)
{
	int Size = 5000;     
	
 	Index2 = sinSearchEmptyIndex();                                          
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	IndexCnt5++;
	if((IndexCnt5 % 3) == 0 )
		cSinEffect2[Index2].sinFace.MatNum = MatMonParticle[0]; 
	else
		cSinEffect2[Index2].sinFace.MatNum = MatMonParticle[3]; 

	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = rand()%8+20;
	cSinEffect2[Index2].CODE = SIN_EFFECT_MUTENTTREE_FIRE_PARTICLE;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = 1;
	cSinEffect2[Index2].SizeDecreTime = 1;
	cSinEffect2[Index2].SizeAmount = 100; 
	cSinEffect2[Index2].Angle.x = (rand()%2047&ANGCLIP)+2047;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.y = rand()%25 + 25;
	
	sinGetMoveLocation2(&cSinEffect2[Index2]);   
  	GetMoveLocation( 0 , 0, 256*2, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;
	
	return TRUE;
}
int sinEffect_MutentTree_Attack_Particle(POINT3D *pPosi)
{
	int Size = 3000; 
	int Cnt = 2;
	while(Cnt--){   
 	Index2 = sinSearchEmptyIndex();                                               
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatMonParticle[3]; 
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = rand()%3+5;
	cSinEffect2[Index2].SizeDecreTime = cSinEffect2[Index2].Max_Time-5;
	cSinEffect2[Index2].SizeAmount = 250; 
	cSinEffect2[Index2].AlphaAmount =5;
	cSinEffect2[Index2].CODE = SIN_EFFECT_MUTENTTREE_ATTACK_PARTICLE;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = 1;
	cSinEffect2[Index2].Angle.x = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.y = rand()%100 + 100;

	sinGetMoveLocation2(&cSinEffect2[Index2]);
	GetMoveLocation( 0 , 0, 64*7, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;
	}
	
	return TRUE;
}

/*
int EffectCount5;
int sinEffect_MutentTree_Attack_Particle2(POINT3D *pPosi) //뮤턴트 트리 
{
	EffectCount5++;                 
	if(EffectCount5 <= 0)return FALSE;
	EffectCount5 = 0;

	int Size = 2000;      
	int Cnt = 2;
	while(Cnt--){
 	Index2 = sinSearchEmptyIndex();                                          
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatFireBolt[0]; 
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = rand()%15+20;
	cSinEffect2[Index2].CODE = SIN_EFFECT_MUTENTTREE_ATTACK_PARTICLE2;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 30;
	cSinEffect2[Index2].SizeDecreTime = cSinEffect2[Index2].Max_Time-10;
	cSinEffect2[Index2].SizeAmount = 100; 
	cSinEffect2[Index2].Angle.x = (rand()%2047&ANGCLIP)+2047;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.y = rand()%100 + 100;
	sinGetMoveLocation2(&cSinEffect2[Index2]);
	GetMoveLocation( 0 , 0, 64*4, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;

	}
	return TRUE;

}
*/

/*
int sinEffect_MutentTree_Hit_Particle(POINT3D *pPosi)
{
	int Size = 2000;
	int Cnt = 20;
	while(Cnt--){
 	Index2 = sinSearchEmptyIndex();                                                
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatFireBolt[0]; 
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = rand()%10+20;
	cSinEffect2[Index2].CODE = SIN_EFFECT_MUTENTTREE_HIT;
	cSinEffect2[Index2].AlphaAmount =5;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = 1;
	cSinEffect2[Index2].Angle.x = (rand()%2047&ANGCLIP)+2047;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.y = rand()%25 + 25;
	cSinEffect2[Index2].sinFace.r = 0;
	cSinEffect2[Index2].sinFace.g = rand()%150+100;
	cSinEffect2[Index2].sinFace.b = 0;
	}
	///////라이트
	Index2 = sinSearchEmptyIndex();                           
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatLight5[0];
	cSinEffect2[Index2].sinFace.height = 5000*2; 
	cSinEffect2[Index2].sinFace.width  = 5000*2; 
	cSinEffect2[Index2].Max_Time = 50;
	cSinEffect2[Index2].CODE = SIN_EFFECT_LIGHT5;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 10;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 22;
	cSinEffect2[Index2].lpMatAni = MatLight5;
	cSinEffect2[Index2].AniMax = 5;
	cSinEffect2[Index2].AniCount = 10;
	cSinEffect2[Index2].AniTime = 10;
	cSinEffect2[Index2].SizeIncreTime = 1;
	cSinEffect2[Index2].SizeAmount = 100;
	return TRUE;

}
*/

int sinEffect_Ratoo(smCHAR *pChar) //라투 (현제 미적용)
{
	//기둥
	int  i = 0;
	for(i = 1; i < 7 ; i++){      
		Assa = SetAssaEffect(0,"monratoo.ASE",pChar,0,1000);                              
		cAssaEffect[Assa]->AniMaxCount = 20; 
		cAssaEffect[Assa]->AniDelayTime = 4;
		//cAssaEffect[Assa]->StartPosi.x = 256*8*6;

		//cAssaEffect[Assa]->Angle.y =  ((pChar->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;
		//cAssaEffect[Assa]->StartPosi.z = (512*i)*8*6;
		AssaGetCirclePosi(cAssaEffect[Assa],256*64,(i)*(4096/6));
		//AssaSetStartPosi(cAssaEffect[Assa]);
		//AssaEffect[Assa]->Angle.y =  -((pChar->Angle.y&ANGCLIP))&ANGCLIP;
		AssaParticle_SpecialHit2(&cAssaEffect[Assa]->Posi,0,1);
	}


	//바닥
	for(i = 0; i < 2 ; i++){         
		Assa = SetAssaEffect(85,"monratoo-1.bmp",pChar,0,7000);                     
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
		cAssaEffect[Assa]->Size.w = 10000*3;
		//cAssaEffect[Assa]->MOVECODE =  ASSA_ANGLE_ROTATE |ASSA_CHAR_POSI;
		cAssaEffect[Assa]->ARotateSpeed.y = 3;
		cAssaEffect[Assa]->CODE = ASSA_EFFECT_RATOO3;
		cAssaEffect[Assa]->Time = i*-10;

		//cAssaEffect[Assa]->StartPosi.z = (512*i)*8*6;
		//AssaGetCirclePosi(cAssaEffect[Assa],256*64,(i)*(4096/6));
		//AssaSetStartPosi(cAssaEffect[Assa]);

	}
	//for(i = 1; i < 7 ; i++){      
		Assa = SetAssaEffect(0,"ratoo.ASE",pChar,0,1000);                              
		cAssaEffect[Assa]->AniMaxCount = 20; 
		cAssaEffect[Assa]->AniDelayTime = 4;
		//cAssaEffect[Assa]->StartPosi.x = 256*8*6;

		//cAssaEffect[Assa]->Angle.y =  ((pChar->Angle.y&ANGCLIP)+ANGLE_270)&ANGCLIP;
		//cAssaEffect[Assa]->StartPosi.z = (512*i)*8*6;
	
		//AssaSetStartPosi(cAssaEffect[Assa]);
		//AssaEffect[Assa]->Angle.y =  -((pChar->Angle.y&ANGCLIP))&ANGCLIP;
		AssaParticle_SpecialHit2(&cAssaEffect[Assa]->Posi,0,1);
	//}

	


	/*
	int i = 0 , j = 0;  
	char szBuff[128];
	char *Path = "image\\Sinimage\\Effect\\MonsterEffect\\Ratoo\\ratohit";  
	for(i = 0 ; i < 2 ; i++){          
		smASE_SetPhysique( 0 ); //physique 초기화                                                                             
		Index2 = sinSearchEmptyIndex();                                                       
		sinEffectDefaultSet(Index2 , SIN_EFFECT_MESH ,  pChar,0,7000);
		wsprintf(szBuff,"%s%d.ASE",Path,i+1);
		cSinEffect2[Index2].sinPatMesh = smASE_Read(szBuff);
		for(j = 0; j< int(cSinEffect2[Index2].sinPatMesh->smMaterialGroup->MaterialCount); j++){
			cSinEffect2[Index2].sinPatMesh->smMaterialGroup->smMaterial[j].BlendType = SMMAT_BLEND_LAMP;

		}
		//cSinEffect2[Index2].CODE = SIN_EFFECT_RATOO; //잠시 대기 
		cSinEffect2[Index2].Angle.y = (-(pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP; //자신의 방향으로 오브젝트를찍는다 
		cSinEffect2[Index2].Max_Time = 30;
		cSinEffect2[Index2].AniTime = 4;
		cSinEffect2[Index2].AniMax = 8+i;
		cSinEffect2[Index2].AniCount = i;
		cSinEffect2[Index2].AlphaAmount = 8;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 30;

	}
	*/


/*
	int i = 0 , j = 0; 
	char szBuff[128];
	int TempIndex=0;
	char *Path = "image\\Sinimage\\Effect\\MonsterEffect\\Ratoo\\ratooblade";  
	//SetDynLight( pChar->pX , pChar->pY , pChar->pZ ,255, 255, 255, 255, 200 ,1);          
	for(i = 0 ; i < 11 ; i++){          
		smASE_SetPhysique( 0 ); //physique 초기화                                                                             
		Index2 = sinSearchEmptyIndex();                                                       
		sinEffectDefaultSet(Index2 , SIN_EFFECT_MESH ,  pChar,0,0);
		wsprintf(szBuff,"%s%d.ASE",Path,i+1);
		cSinEffect2[Index2].sinPatMesh = smASE_Read(szBuff);
		for(j = 0; j< int(cSinEffect2[Index2].sinPatMesh->smMaterialGroup->MaterialCount); j++){
			cSinEffect2[Index2].sinPatMesh->smMaterialGroup->smMaterial[j].BlendType = SMMAT_BLEND_LAMP;
		}
		//cSinEffect2[Index2].sinPatMesh = smASE_Read("image\\Sinimage\\Effect\\SkillEffect\\HolyBody\\h_bodyteg.ASE");
		cSinEffect2[Index2].CODE = SIN_EFFECT_RATOO;
		cSinEffect2[Index2].Angle.y = (-(pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP; //자신의 방향으로 오브젝트를찍는다 
		cSinEffect2[Index2].Max_Time = 30;
		cSinEffect2[Index2].AniTime = 4;
		cSinEffect2[Index2].AniMax = 8+i;
		cSinEffect2[Index2].AniCount = i;
		cSinEffect2[Index2].AlphaAmount = 8;
		cSinEffect2[Index2].AlphaCount = 1;
		cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 30;
		cSinEffect2[Index2].Time = - i*1;

		/////////////////// 요기는 HIT (현제 잠쉬 대기 )
		if(i == 9 ){  
			cSinEffect2[Index2].Max_Time = 100;      
			cSinEffect2[Index2].AniTime = 5;
			cSinEffect2[Index2].AniMax = 20;
			cSinEffect2[Index2].AniCount = 1;
			cSinEffect2[Index2].Posi.y += 7000;

			cSinEffect2[Index2].AlphaAmount = 8;
			cSinEffect2[Index2].AlphaCount = 1;
			cSinEffect2[Index2].AlphaTime = 1;
			cSinEffect2[Index2].Time = -20;
			cSinEffect2[Index2].ActionTime[0] = 1;

			
		}
		if(i == 10 ){
			cSinEffect2[Index2].Max_Time = 20;            
			cSinEffect2[Index2].AniTime = 2;
			cSinEffect2[Index2].AniMax = 15;
			cSinEffect2[Index2].AniCount = 1;
			cSinEffect2[Index2].Posi.y += 7000;


			cSinEffect2[Index2].AlphaAmount = 13;
			cSinEffect2[Index2].AlphaCount = 1;
			cSinEffect2[Index2].AlphaTime = 1;
			cSinEffect2[Index2].Time =-20;
			cSinEffect2[Index2].ActionTime[0] = 3;


		}
		if(i == 11 ){
			cSinEffect2[Index2].Max_Time = 17*3;                  
			cSinEffect2[Index2].AniTime = 3;
			cSinEffect2[Index2].AniMax = 17;
			cSinEffect2[Index2].AniCount = 1;
			cSinEffect2[Index2].Posi.y += 3000;


			cSinEffect2[Index2].AlphaAmount = 10;
			cSinEffect2[Index2].AlphaCount = 1;
			cSinEffect2[Index2].AlphaTime = 3;
			cSinEffect2[Index2].Time =-20;
			
			sinGetMoveLocation2(&cSinEffect2[Index2]);   
			GetMoveLocation(  0, 0,256*32*4 , cSinEffect2[Index2].Angle.x, (-(cSinEffect2[Index2].Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP, 0 );
			cSinEffect2[Index2].Posi.x += GeoResult_X;
			cSinEffect2[Index2].Posi.y += GeoResult_Y;
			cSinEffect2[Index2].Posi.z += GeoResult_Z;

		}
		
	}
	*/
	//ReadTextures();	//텍스쳐 로딩 

	return TRUE;
}

int sinEffect_Ratoo_Vigor(smCHAR *pChar) 
{

	int Size = 3000;     
 	Index2 = sinSearchEmptyIndex();                                            
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,  pChar,0,0);
	cSinEffect2[Index2].sinFace.MatNum = MatMonParticle[1];
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = 500;
	cSinEffect2[Index2].CODE = SIN_EFFECT_RATOO_PARTICLE;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 30;
	cSinEffect2[Index2].SizeDecreTime = cSinEffect2[Index2].Max_Time-10;
	cSinEffect2[Index2].SizeAmount = 50; 
	//cSinEffect2[Index2].Angle.x = (rand()%2047&ANGCLIP)+2047;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.y = rand()%25 + 25;
	sinGetMoveLocation2(&cSinEffect2[Index2]);   
  	GetMoveLocation( 0 , 0, 256*64, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;
	return TRUE;

}
int sinEffect_Ratoo_Vigor_Partilce(POINT3D *pPosi)
{

	int Size = 3000;     
 	Index2 = sinSearchEmptyIndex();                                          
	sinEffectDefaultSet(Index2 , SIN_EFFECT_FACE ,0,pPosi,0);
	cSinEffect2[Index2].sinFace.MatNum = MatMonParticle[1];
	cSinEffect2[Index2].sinFace.height = Size; 
	cSinEffect2[Index2].sinFace.width  = Size; 
	cSinEffect2[Index2].Max_Time = rand()%20+40;
	//cSinEffect2[Index2].CODE = SIN_EFFECT_MUTENTTREE_SMOKE;
	cSinEffect2[Index2].AniCount = 1;
	cSinEffect2[Index2].AlphaAmount = 5;
	cSinEffect2[Index2].AlphaCount = 1;
	cSinEffect2[Index2].AlphaTime = cSinEffect2[Index2].Max_Time - 30;
	cSinEffect2[Index2].SizeDecreTime = cSinEffect2[Index2].Max_Time-10;
	cSinEffect2[Index2].SizeAmount = 50; 
	cSinEffect2[Index2].Angle.x = (rand()%2047&ANGCLIP)+2047;
	cSinEffect2[Index2].Angle.y = rand()%4096&ANGCLIP;
	cSinEffect2[Index2].MoveSpeed.y = rand()%25 + 25;
	sinGetMoveLocation2(&cSinEffect2[Index2]);   
  	GetMoveLocation( 0 , 0, 256, cSinEffect2[Index2].Angle.x, cSinEffect2[Index2].Angle.y, 0 );
	cSinEffect2[Index2].sinFace.x  += GeoResult_X;
	cSinEffect2[Index2].sinFace.y  += GeoResult_Y;
	cSinEffect2[Index2].sinFace.z  += GeoResult_Z;
	return TRUE;

}






