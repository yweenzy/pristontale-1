/*----------------------------------------------------------------------------*
*	파일명 :  AssaParticle.cpp	
*	하는일 :  아싸! 파티클 
*	작성일 :  최종업데이트 2002년 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"
#include "..\\HoBaram\\HoNewParticleLinkHeader.h" //새로운 호바람
/*----------------------------------------------------------------------------*
*							 CODE
*-----------------------------------------------------------------------------*/	
#define ASSA_PARTICLE_BELT				0x50000000 // 현제 사용하고있지않다 
#define ASSA_PARTICLE_ROTATE_GATHER		0x50000001 // 돌면서 모인다 
#define ASSA_PARTICLE_ROTATE_WIDE		0x50000002 // 돌면서 퍼진다
#define ASSA_PARTICLE_SPECIAL_HIT		0x50000003 // 타격파티클
#define ASSA_PARTICLE_PIERCING			0x50000004 // 피어싱파티클
#define ASSA_PARTICLE_WINDY				0x50000005 // 윈디
#define ASSA_PARTICLE_CHAR_LIGHT		0x50000006 // 라이트
#define ASSA_PARTICLE_STUNE				0x50000007 // 스턴
#define ASSA_PARTICLE_HOLY_MIND			0x50000008 // 스턴


//몬스터 이펙트 
#define ASSA_EFFECT_RATOO_AURA			0x60000100 // 라투 오라
#define ASSA_EFFECT_RATOO_AURA2			0x60000200 // 라투 오라 

int AssaTest_Shot(POINT3D *pPosi, int n);

/*----------------------------------------------------------------------------*
*							 KeyDown
*-----------------------------------------------------------------------------*/	
int sinAssaParticleKeyDown() //파티클 테스트( 이펙트 테스트) 
{
	////lpCharSelPlayer	//한번 선택한 대상의 포인터 
	////lpCharMsTrace		//계속 선택한 대상의 포인터

	//POINT3D Posi = {lpCurPlayer->pX,lpCurPlayer->pY,lpCurPlayer->pZ};   

	//if(sinGetKeyClick('Y')){  
	//	//sinEffect_Ratoo(lpCurPlayer);
	//	//sinEffect_Ratoo_Aura(lpCurPlayer);
	//	//cInvenTory.UnionCoreParticle2(300,300);
	//	//cInvenTory.SetUnionCoreEffect(300,600);
	//	//sinAssaUnionCoreEffect(lpCurPlayer);
	//	//AssaParticle_Stune(lpCurPlayer,7);
	//	AssaTest_Shot(NULL,0);
	//}
	//else if(sinGetKeyClick('U')){  
	//	AssaTest_Shot(NULL,1);
	//}

	//else if(sinGetKeyClick('I')){  
	//	AssaTest_Shot(NULL,2);
	//	

	//}
	//else if(sinGetKeyClick('O')){  
	//	AssaTest_Shot(NULL,3);
	//	

	//}
	//else if(sinGetKeyClick('P')){  
	//	AssaTest_Shot(NULL,4);

	//}

/*
	if(sinGetKeyClick('8')){    
		AssaParticle_RisingBelt(&Posi,"belt-02.ASE",3,100);
		//AssaParticle_Summon(lpCurPlayer);
	}

*/ 	
	return TRUE;
}

/*----------------------------------------------------------------------------*
*							  Process 
*-----------------------------------------------------------------------------*/	
void sinAssaParticleProcess(cASSAEFFECT *pEffect)
{

	D3DVECTOR TempVector;

	//움직임 코드 
	switch(pEffect->CODE){       
		case ASSA_PARTICLE_WINDY:
			if(&pEffect->Posi){   
				pEffect->fTemp[0] += 0.025f;
				AssaSearchWeaponPos(pEffect->pChar,&pEffect->Posi,pEffect->fTemp[0]);            
				if(pEffect->Time+30 <= pEffect->Max_Time &&  pEffect->Time == GetRandomPos(0,pEffect->Max_Time))
					AssaParticle_RisingParticleContinue(&pEffect->Posi,"star01Y_02.bmp",500,0,GetRandomPos(50,80));

			}
			pEffect->Size.w -=5;
			pEffect->Size.h -=5;

		break;
		case ASSA_PARTICLE_ROTATE_GATHER: 
			pEffect->RDistance.z -= 256;
		break;
		case ASSA_PARTICLE_ROTATE_WIDE:
			pEffect->RDistance.z += 32;
		break;
		case ASSA_PARTICLE_SPECIAL_HIT:  //규격화되지않은 왕 날치기 
			if(pEffect->ActionIndex[0] == 1){  //선
				pEffect->FACEY += 3;
				if(pEffect->Time < 10)
					pEffect->Size.w += 400;
				else
					pEffect->Size.w -= 400;

			}
			if(pEffect->ActionIndex[1] == 1){ //면
				pEffect->Size.w +=150;
				pEffect->Size.h +=150;

			}
			if(pEffect->ActionIndex[2] ==1){//파티클 
				pEffect->Gravity -=2;
				pEffect->Posi.y += pEffect->Gravity;

			}
			if(pEffect->ActionIndex[3] ==1){//퍼지는 라이트 
				pEffect->Size.w +=50;
				pEffect->Size.h +=50;

			}
		break;
		case ASSA_PARTICLE_PIERCING:
			//호바람 잔상 
			TempVector.x = (float)pEffect->Posi.x; 
			TempVector.y = (float)pEffect->Posi.y;
			TempVector.z = (float)pEffect->Posi.z;
			g_NewParticleMgr.SetPos(pEffect->Face.MatNum, TempVector);
			if(pEffect->Time>= pEffect->Max_Time-11)
				g_NewParticleMgr.SetStop(pEffect->Face.MatNum);
			if(pEffect->Time < (pEffect->Max_Time-11)) 
				AssaParticle_Wave(&pEffect->Posi,"water3.tga",pEffect->Time);

		break;
		case ASSA_PARTICLE_CHAR_LIGHT:
			if((pEffect->Max_Time / pEffect->Time ) < 1 ){
				if(pEffect->Face.Transparency < 150 )pEffect->Face.Transparency++;
			}
			else{
				if(pEffect->Max_Time <= pEffect->Time + 150)
					if(pEffect->Face.Transparency > 0 )pEffect->Face.Transparency--;
			}
		break;
		case ASSA_PARTICLE_HOLY_MIND:
			if((pEffect->Time % 3) == 0) 
				AssaParticle_HolyMind(&pEffect->Posi,1);

			if(pEffect->ActionIndex[0] == 1){  //선
				pEffect->FACEY += 3;
				if(pEffect->Time < 10)
					pEffect->Size.w += 400;
				else
					pEffect->Size.w -= 400;

			}
		break;
		case ASSA_EFFECT_RATOO_AURA:
			if((pEffect->Time % 100) == 0  || pEffect->Time == 1 )  
				sinEffect_Ratoo_Aura2(pEffect->pChar); 
			if(pEffect->Temp[0] == 0){         
				pEffect->Face.Transparency --;
				//pEffect->Size.w -= 40; 
				//pEffect->Size.h -= 40;
				if(pEffect->Face.Transparency < 100){
					pEffect->Temp[0] = 1;
				}
			}
			else{
				pEffect->Face.Transparency ++;
				//pEffect->Size.w += 40; 
				//pEffect->Size.h += 40;
				if(pEffect->Face.Transparency > 250 ){
					pEffect->Temp[0] = 0;

				}
			}
		break;
		case ASSA_EFFECT_RATOO_AURA2:
			pEffect->Size.w += 100;      
			pEffect->Size.h += 100;
			if((pEffect->Time % 2 ) == 0)
				pEffect->Face.Transparency -=1;


		break;
		case ASSA_EFFECT_RATOO3:
			pEffect->Size.w += 3000; 
			pEffect->Size.h += 3000;

		break;
	}

	//코드 변환 적용
	for(int i = 0 ; i < 10 ; i++){ 
		if(pEffect->MOVECODE_Time[i]){
			if(pEffect->Time == pEffect->MOVECODE_Time[i]){
				pEffect->MOVECODE = pEffect->MOVECODE_List[i];
			}
		}
	}

	//지속되는 스킬적용
	/* (너무 야매스러워서 뺐다 )
	for(int i = 0 ; i < MAX_CONTINUE_SKILL ; i++){ 
		if(ContinueSkill[i].Flag){
			ContinueSkill[i].Time[0]++;
			switch(ContinueSkill[i].CODE){
				case SKILL_WINDY:
					if(ContinueSkill[i].Time[0] >= 3000 && (ContinueSkill[i].Time[0] % 3000)==0){
						AssaParticle_Windy2(lpCurPlayer);
					}
				break;
			}
		}
	}
	*/
}
/*----------------------------------------------------------------------------*
*							 스페셜 HIT +_+
*-----------------------------------------------------------------------------*/	
int AssaParticle_SpecialHit(POINT3D *pPosi , int Time)
{
	//선  
	for(int i = 0 ; i < 4 ; i++){                                                     
		Assa = SetAssaEffect(90,"flare.tga",0,pPosi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(7000,10000); 
		cAssaEffect[Assa]->Size.h = GetRandomPos(500,1200); 
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->ZposiFlag = 1;
		cAssaEffect[Assa]->ActionIndex[0] = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 0;
		cAssaEffect[Assa]->Time = -5*i+Time;

	}	
	//선 2
	for(int i = 0 ; i < 4 ; i++){                  
		Assa = SetAssaEffect(90,"flare.tga",0,pPosi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(10000,15000);
		cAssaEffect[Assa]->Size.h = GetRandomPos(500,1200); 
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->ActionIndex[0] = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 200;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->Time = -5*i+Time;
		cAssaEffect[Assa]->ZposiFlag = 1;

		
	}	

	//면 
	for(int i = 0 ; i < 2 ; i++){                
		Assa = SetAssaEffect(70,"water2.tga",0,pPosi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(3000,3001);
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->ActionIndex[1] = 1;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 0;
		cAssaEffect[Assa]->Time = (i*-10)+Time;
		cAssaEffect[Assa]->ZposiFlag = 1;

	}	
	
	//면 2
	for(int i = 0 ; i < 1 ; i++){                      
		Assa = SetAssaEffect(60,"Light01.tga",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = GetRandomPos(10000,10001);
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 200;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->ZposiFlag = 1;
		cAssaEffect[Assa]->Time = Time;

	}	

	//파티클  
	for(int i = 0 ; i < 15 ; i++){        
		Assa = SetAssaEffect(100,"flare.tga",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = GetRandomPos(500,1300);
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 0;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
		cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(128,256);
		cAssaEffect[Assa]->ActionIndex[2] =1;
		cAssaEffect[Assa]->Time = GetRandomPos(-20,0)+Time;
		cAssaEffect[Assa]->Gravity = 50;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->ZposiFlag = 1;
	}	

	for(int i = 0 ; i < 15 ; i++){         
		Assa = SetAssaEffect(100,"flare.tga",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = GetRandomPos(500,1300);
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 200;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
		cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(128,256);
		cAssaEffect[Assa]->ActionIndex[2] =1;
		cAssaEffect[Assa]->Time = GetRandomPos(-20,0)+Time;
		cAssaEffect[Assa]->Gravity = 50;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->ZposiFlag = 1;
	}	


	return TRUE;
}
int AssaParticle_SpecialHit2(POINT3D *pPosi , int Time ,int Kind) //현제 Brandish에서 사용
{
	
	//선  
	if(Kind == 0){ 
		for(int i = 0 ; i < 6 ; i++){                                                      
			Assa = SetAssaEffect(50,"flare.tga",0,pPosi,0);      
			cAssaEffect[Assa]->Size.w = GetRandomPos(10000,20000); 
			cAssaEffect[Assa]->Size.h = GetRandomPos(500,1200); 
			cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
			cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
			cAssaEffect[Assa]->NotFadeIn = 1;
			cAssaEffect[Assa]->ZposiFlag = 1;
			cAssaEffect[Assa]->ActionIndex[0] = 1;
			cAssaEffect[Assa]->Face.r = 255;
			cAssaEffect[Assa]->Face.g = 150;
			cAssaEffect[Assa]->Face.b = 0;
			cAssaEffect[Assa]->Time = -5*i+Time;


		}	
		//선 2
		for(int i = 0 ; i < 6 ; i++){                   
			Assa = SetAssaEffect(50,"flare.tga",0,pPosi,0);      
			cAssaEffect[Assa]->Size.w = GetRandomPos(15000,25000);
			cAssaEffect[Assa]->Size.h = GetRandomPos(500,1200); 
			cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
			cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
			cAssaEffect[Assa]->NotFadeIn = 1;
			cAssaEffect[Assa]->ActionIndex[0] = 1;
			cAssaEffect[Assa]->Face.r = 255;
			cAssaEffect[Assa]->Face.g = 200;
			cAssaEffect[Assa]->Face.b = 50;
			cAssaEffect[Assa]->Time = -5*i+Time;
			cAssaEffect[Assa]->ZposiFlag = 1;

			
		}	
	}
	//면 
	if(Kind ==0 ){
		for(int i = 0 ; i < 2 ; i++){                    
			Assa = SetAssaEffect(70,"water2.tga",0,pPosi,1500);      
			cAssaEffect[Assa]->Size.w = GetRandomPos(20000,10001);
			cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
			cAssaEffect[Assa]->ActionIndex[1] = 1;
			cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
			cAssaEffect[Assa]->Face.r = 255;
			cAssaEffect[Assa]->Face.g = 150;
			cAssaEffect[Assa]->Face.b = 0;
			cAssaEffect[Assa]->Time = (i*-10)+Time;
			cAssaEffect[Assa]->FACE_TYPE  = ASSAFACE_WORLD;
			//cAssaEffect[Assa]->ZposiFlag = 1;

		}	
	}
	if(Kind == 1){
		for(int i = 0 ; i < 2 ; i++){                    
			Assa = SetAssaEffect(70,"water2.tga",0,pPosi,1500);      
			cAssaEffect[Assa]->Size.w = GetRandomPos(10000,5001);
			cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
			cAssaEffect[Assa]->ActionIndex[1] = 1;
			cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
			cAssaEffect[Assa]->Face.r = 255;
			cAssaEffect[Assa]->Face.g = 150;
			cAssaEffect[Assa]->Face.b = 0;
			cAssaEffect[Assa]->Time = (i*-10)+Time;
			cAssaEffect[Assa]->FACE_TYPE  = ASSAFACE_WORLD;
			//cAssaEffect[Assa]->ZposiFlag = 1;

		}	
	}
	//면 2
	for(int i = 0 ; i < 1 ; i++){                      
		Assa = SetAssaEffect(60,"Light01.tga",0,pPosi,1500);       
		cAssaEffect[Assa]->Size.w = GetRandomPos(20000,10001);
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 200;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->FACE_TYPE  = ASSAFACE_WORLD;
		//cAssaEffect[Assa]->ZposiFlag = 1;
		cAssaEffect[Assa]->Time = Time;

	}	

	//야매루 대충 보정한다 움하하하하
	if(Kind == 0){
		//파티클  
		for(int i = 0 ; i < 30 ; i++){        
			Assa = SetAssaEffect(100,"flare.tga",0,pPosi,0);       
			cAssaEffect[Assa]->Size.w = GetRandomPos(500,1300);
			cAssaEffect[Assa]->NotFadeIn = 1;
			cAssaEffect[Assa]->Face.r = 255;
			cAssaEffect[Assa]->Face.g = 150;
			cAssaEffect[Assa]->Face.b = 0;
			cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
			cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(256,256*2);
			cAssaEffect[Assa]->ActionIndex[2] =1;
			cAssaEffect[Assa]->Time = GetRandomPos(-20,0)+Time;
			cAssaEffect[Assa]->Gravity = 50;
			cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
			cAssaEffect[Assa]->ZposiFlag = 1;
		}	

		for(int i = 0 ; i < 30 ; i++){         
			Assa = SetAssaEffect(100,"flare.tga",0,pPosi,0);       
			cAssaEffect[Assa]->Size.w = GetRandomPos(500,1300);
			cAssaEffect[Assa]->NotFadeIn = 1;
			cAssaEffect[Assa]->Face.r = 255;
			cAssaEffect[Assa]->Face.g = 200;
			cAssaEffect[Assa]->Face.b = 50;
			cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
			cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(256,256*2);
			cAssaEffect[Assa]->ActionIndex[2] =1;
			cAssaEffect[Assa]->Time = GetRandomPos(-20,0)+Time;
			cAssaEffect[Assa]->Gravity = 50;
			cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
			cAssaEffect[Assa]->ZposiFlag = 1;
		}	

	}
	return TRUE;
}




/*----------------------------------------------------------------------------*
*							 스턴 파티클 
*-----------------------------------------------------------------------------*/	
int AssaParticle_Stune(smCHAR *pChar , int Time)
{
	int Count = 0;
	//이미실행되어있는 스턴효과는 시간만 갱신한다
	for(int k = 0 ; k < cASSAEFFECT_MAX ; k++){  
		if(cAssaEffect[Assa]){
			if(cAssaEffect[Assa]->CODE ==  ASSA_PARTICLE_STUNE){
				if(cAssaEffect[Assa]->pChar){
					if(cAssaEffect[Assa]->pChar == pChar){
						cAssaEffect[Assa]->Max_Time += Time*80;
						return TRUE;
					}
				}
			}
		}
	}
	for(int j = 0 ; j < 3 ; j++){     
		for(int i = 0 ; i < 4 ; i++){          
			Assa = SetAssaEffect(Time*85,"Star.tga",pChar,0,pChar->PatHeight+2000);                 
			cAssaEffect[Assa]->MOVECODE = ASSA_ROTATE | ASSA_CHAR_POSI;
			Count++;
			cAssaEffect[Assa]->StartPosi.z = 256*4; //현제 적용되고있지않다 귀찮아서 걍냅뒀다 ㅡ.ㅡ
			AssaSetStartPosi(cAssaEffect[Assa]);
			cAssaEffect[Assa]->RAngleSpeed = 16*3;
			cAssaEffect[Assa]->Size.h = 500+(i*220);
			cAssaEffect[Assa]->Size.w = 500+(i*220);
			cAssaEffect[Assa]->Face.Transparency = 255 - (i*25);
			AssaGetCirclePosi(cAssaEffect[Assa],256*8,16*2*(Count*6)+(j*200*3));

		}
	}
	
	return TRUE;
}
/*----------------------------------------------------------------------------*
*							  원 만들기 
*-----------------------------------------------------------------------------*/	
int AssaMakeCircle(POINT3D *pPosi , char *FileName , int Radius)
{
	int Temp = Radius/256;  
	Assa = SetAssaEffect(500,FileName,0,pPosi,3000);                         
	cAssaEffect[Assa]->Size.w = 1000;
	cAssaEffect[Assa]->RDistance.z = Radius;

	for(int i = 0 ; i < Temp ; i++){     
		cAssaEffect[Assa]->RAngle += 15*Temp;
		cAssaEffect[Assa]->RPosi.x  = GetCos[ cAssaEffect[Assa]->RAngle&ANGCLIP ] + Radius*GetSin[ cAssaEffect[Assa]->RAngle&ANGCLIP ];     
		cAssaEffect[Assa]->RPosi.z  = -GetSin[ cAssaEffect[Assa]->RAngle&ANGCLIP ] + Radius*GetCos[ cAssaEffect[Assa]->RAngle&ANGCLIP ];
		cAssaEffect[Assa]->RPosi.x >>=16;
		cAssaEffect[Assa]->RPosi.z >>=16;
		cAssaEffect[Assa]->Posi.x =  cAssaEffect[Assa]->CenterPosi.x + cAssaEffect[Assa]->RPosi.x;
		cAssaEffect[Assa]->Posi.z =  cAssaEffect[Assa]->CenterPosi.z + cAssaEffect[Assa]->RPosi.z;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->AddData(&cAssaEffect[Assa]->Posi);
		cAssaEffect[Assa]->Type = ASSATYPE_CIRCLE;
		
	}

	return Assa;
}

/*----------------------------------------------------------------------------*
*							  벨트형 파티클 
*-----------------------------------------------------------------------------*/	
int AssaParticle_RisingBelt(POINT3D *pPosi ,char *FileName,int ContinueTime , int SpeedY )
{ 

	int Temp = 1; 
	for(int i = 0 ; i < ContinueTime * 7 ; i++){               
		if((i%7)!=0)continue; 
		Assa = SetAssaEffect(250-(SpeedY/2),FileName,0,pPosi,0);                 
		cAssaEffect[Assa]->MOVECODE = ASSA_ANGLE_ROTATE | ASSA_MOVE;
		if(Temp == -1 )Temp = 1;
		else Temp = -1; 
		cAssaEffect[Assa]->ARotateSpeed.y = GetRandomPos(30,35)*Temp; 
		cAssaEffect[Assa]->MoveSpeed.y = SpeedY;
		cAssaEffect[Assa]->AniCount = rand()%5+5;
		cAssaEffect[Assa]->Time = GetRandomPos(-10*i,-i*9);
	}
	return TRUE; 
}
/*----------------------------------------------------------------------------*
*							  상승 파티클 
*-----------------------------------------------------------------------------*/	
int AssaParticle_RisingParticle(POINT3D *pPosi , char *FileName ,int Size ,  int ContinueTime , int Range , int Count , int SpeedY)
{
	for(int i = 0; i < ContinueTime*7 ; i++){              
		for(int j = 0; j < Count ; j++){    
		  Assa = SetAssaEffect(350-(SpeedY/2),FileName,0,pPosi,0);   
		  AssaGetAniFileMat(cAssaEffect[Assa]);
		  cAssaEffect[Assa]->AniDelayTime = GetRandomPos(4,10);
		  cAssaEffect[Assa]->AniCount = GetRandomPos(0,cAssaEffect[Assa]->AniMaxCount);
		  cAssaEffect[Assa]->AniReverse = 1;
		  cAssaEffect[Assa]->Size.w = GetRandomPos(Size-500,Size+500);
		  cAssaEffect[Assa]->MoveSpeed.y = rand()%50+SpeedY;
		  AssaGetCirclePosi(cAssaEffect[Assa],GetRandomPos(0,Range*10),GetRandomPos(0,4096));
		  cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		  cAssaEffect[Assa]->Time = GetRandomPos(-10*i,-i*9)-j;

		}
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*							  상승 파티클 
*-----------------------------------------------------------------------------*/	
int AssaParticle_RisingLine(POINT3D *pPosi , char *FileName , int Size, int ContinueTime , int Range , int Count , int SpeedY)
{
	for(int i = 0; i < ContinueTime*7 ; i++){                       
		for(int j = 0; j < Count ; j++){    
		  Assa = SetAssaEffect(350-(SpeedY/2),FileName,0,pPosi,0);   
		  cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		  cAssaEffect[Assa]->ScalePosi.y = GetRandomPos(Size*100,(Size+1)*100);
		  cAssaEffect[Assa]->Size.w = GetRandomPos(Size-500,Size+500);
		  cAssaEffect[Assa]->MoveSpeed.y = rand()%50+SpeedY;
		  cAssaEffect[Assa]->Posi.y -= 50*Size; //Scale시 좌표가 옮겨지는걸 보정
		  AssaGetCirclePosi(cAssaEffect[Assa],GetRandomPos(0,Range*10),GetRandomPos(0,4096));
		  cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		  cAssaEffect[Assa]->Time = GetRandomPos(-10*i,-i*9)-j;
		}
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*							  상승 곡선형 파티클
*-----------------------------------------------------------------------------*/	
int AssaParticle_RisingRotateLine(POINT3D *pPosi , char *FileName , int ContinueTime , int Range , int Count , int SpeedY)
{ 
	int Temp =1;
	for(int i = 0; i < ContinueTime*7 ; i++){                            
		for(int j = 0; j < Count ; j++){       
		  Assa = SetAssaEffect(350-(SpeedY/2),FileName,0,pPosi,0);   
		  cAssaEffect[Assa]->Size.w = 1000; 
		  cAssaEffect[Assa]->MoveSpeed.y = rand()%50+SpeedY;
		  AssaGetCirclePosi(cAssaEffect[Assa],GetRandomPos(0,Range*10),GetRandomPos(0,4096));
		  cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE;
		  if(Temp > 0 )Temp = -1;
		  else Temp = 1;
		  cAssaEffect[Assa]->RAngleSpeed = 50*Temp;
		  cAssaEffect[Assa]->RDistance.z = 256*16;
		  cAssaEffect[Assa]->Time = GetRandomPos(-10*i,-i*9)-j;
		  cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		  cAssaEffect[Assa]->cAssaTrace->SetLength(50); //연결길이를 잡는다
		}
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*							  물결형 파티클 (피어싱에서 사용)
*-----------------------------------------------------------------------------*/	
int AssaParticle_Wave(POINT3D *pPosi , char *FileName ,int Size)
{
	//현제 피어싱에만 사용된다  (Size인자는 알파값이다 )귀찮아서 안바꿨다 ㅡ,.ㅡ
	
	for(int i = 0; i < 1 ; i++){                  
		Assa = SetAssaEffect(GetRandomPos(31-Size,32-Size),"star05B_03.bmp",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = 4000;//-(Size*(4000/30)); 
		cAssaEffect[Assa]->ReSize.w = 600;//-(Size*(600/30));
		cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;
		cAssaEffect[Assa]->MOVECODE = ASSA_INCRESIZE;
		cAssaEffect[Assa]->FACEY = GetRandomPos(0,4096);

		//cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Face.Transparency = 255-(Size*8);
	}
	
	for(int i = 0; i < 1 ; i++){            
		Assa = SetAssaEffect(GetRandomPos(31-Size,32-Size),"twist.bmp",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = 1000;//-(Size*(1000/30)); 
		cAssaEffect[Assa]->ReSize.w = 600;//-(Size*(600/30));
		cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;
		cAssaEffect[Assa]->MOVECODE = ASSA_INCRESIZE;
		cAssaEffect[Assa]->FACEY = GetRandomPos(0,4096);
		cAssaEffect[Assa]->Face.Transparency = 255-(Size*8);
		
	}

	return TRUE;
}

/*----------------------------------------------------------------------------*
*					        Light (현제 사용하지않음)
*-----------------------------------------------------------------------------*/	
int AssaParticle_Light(POINT3D *pPosi , char *FileName ,int Size , int Height , int Time)
{
	Assa = SetAssaEffect(40,FileName,0,pPosi,Height);           
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 25;
	cAssaEffect[Assa]->Size.w = Size;
	cAssaEffect[Assa]->ReSize.w = 600;
	cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;
	cAssaEffect[Assa]->MOVECODE = ASSA_INCRESIZE;
	cAssaEffect[Assa]->Time = Time;
	cAssaEffect[Assa]->MOVECODE_List[0] = ASSA_DECRESIZE;
	cAssaEffect[Assa]->MOVECODE_Time[0] = 25;

	return TRUE;
}

/*----------------------------------------------------------------------------*
*					     상승 곡선 조금떠 빠른거
*-----------------------------------------------------------------------------*/	
int AssaParticle_RisingRotateLinePower(POINT3D *pPosi , char *FileName,int Range ,int Speed )
{ 
	
	int Temp =1;
	for(int i = 0; i < 7 ; i++){                                   
		for(int j = 0; j < 3 ; j++){           
		  Assa = SetAssaEffect(350-(Speed/2),FileName,0,pPosi,0);   
		  cAssaEffect[Assa]->Size.w = 1000; 
		  cAssaEffect[Assa]->MoveSpeed.y = Speed;
		  AssaGetCirclePosi(cAssaEffect[Assa],Range*4,GetRandomPos(0,4096));
		  cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE;
		  if(Temp > 0 )Temp = -1;
		  else Temp = 1;
		  cAssaEffect[Assa]->RAngleSpeed = 100*Temp;
		  cAssaEffect[Assa]->Time = GetRandomPos(-5*i,-i*4)-j;
		  cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		  cAssaEffect[Assa]->cAssaTrace->SetLength(50); //연결길이를 잡는다
		  cAssaEffect[Assa]->NotFadeIn = 1;
		  
		}
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*							분출형 파티클 
*-----------------------------------------------------------------------------*/	
int AssaParticle_Spread(POINT3D *pPosi , char *FileName ) 
{
	Assa = SetAssaEffect(70,FileName,0,pPosi,0);                   
	cAssaEffect[Assa]->Size.w = 500;  
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_SPREAD;
	cAssaEffect[Assa]->RAngle = rand()%4096;
	cAssaEffect[Assa]->RDistance.z = 64;
	cAssaEffect[Assa]->Gravity = 10;
	cAssaEffect[Assa]->MoveSpeed.y = 50;
	cAssaEffect[Assa]->NotFadeIn = 1;

	return TRUE;

}

/*----------------------------------------------------------------------------*
*							퍼지는 Face
*-----------------------------------------------------------------------------*/	
int AssaParticle_WideFace(POINT3D *pPosi , char *FileName , int Size)
{
	Assa = SetAssaEffect(40,FileName,0,pPosi,0);                    
	cAssaEffect[Assa]->Size.w = Size; 
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
	cAssaEffect[Assa]->MOVECODE = ASSA_INCRESIZE;
	cAssaEffect[Assa]->ReSize.w = 200;
	cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;

	return TRUE;
}
/*----------------------------------------------------------------------------*
*							   GATHER
*-----------------------------------------------------------------------------*/	
int AssaParticle_Gather(POINT3D *pPosi , char *FileName ,int Range , int Speed ,int Num)
{
	//세부설정은 되어있지않다 
	for(int j = 0; j < Num ; j++){       
		Assa = SetAssaEffect(300,FileName,0,pPosi,0);            
		cAssaEffect[Assa]->Size.w = 1000;  
		cAssaEffect[Assa]->GatherSpeed = 20;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_GATHER;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(100); //연결길이를 잡는다
		cAssaEffect[Assa]->RDistance.z = GetRandomPos(Range*16,Range*16*2);
		cAssaEffect[Assa]->RAngle = GetRandomPos(0,4096);
		cAssaEffect[Assa]->StartPosi.z = cAssaEffect[Assa]->RDistance.z;
		AssaSetStartPosi(cAssaEffect[Assa]);
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*							  ROTATE GATHER
*-----------------------------------------------------------------------------*/	
int AssaParticle_RotateGather(POINT3D *pPosi , char *FileName , int Num)
{
	for(int i = 0; i < Num ; i++){           
		Assa = SetAssaEffect(120,FileName,0,pPosi,0);                 
		cAssaEffect[Assa]->Size.w = 1000;    
		cAssaEffect[Assa]->GatherSpeed = 30;
		cAssaEffect[Assa]->MOVECODE = ASSA_ROTATE;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(70); //연결길이를 잡는다
		cAssaEffect[Assa]->RDistance.z = GetRandomPos(256*16*3 ,256*16*3);
		cAssaEffect[Assa]->RAngle = GetRandomPos(0,4096);
		cAssaEffect[Assa]->RAngleSpeed = GetRandomPos(100,150);
		cAssaEffect[Assa]->AddHeight = GetRandomPos(0,15000);
		cAssaEffect[Assa]->CODE = ASSA_PARTICLE_ROTATE_GATHER;

	}

	return TRUE;
}

/*----------------------------------------------------------------------------*
*							   BALLLINGT GATHER 
*-----------------------------------------------------------------------------*/	
int AssaParticle_BALLLIGHT_GATHER(POINT3D *pPosi , char *FileName )
{
	Assa = SetAssaEffect(60,FileName,0,pPosi,0);                    
	cAssaEffect[Assa]->Size.w = 500;  
	cAssaEffect[Assa]->GatherSpeed = 30;
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_GATHER;
	//cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
	//cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
    //cAssaEffect[Assa]->cAssaTrace->SetLength(20); //연결길이를 잡는다
	cAssaEffect[Assa]->StartPosi.z = 256*8;
	AssaSetStartPosi(cAssaEffect[Assa]);
	return TRUE;
}

/*----------------------------------------------------------------------------*
*							   BALLLINGT ROTATE 
*-----------------------------------------------------------------------------*/	
int AssaParticle_BALLLIGHT_ROTATE(POINT3D *pPosi , char *FileName ,int Range , int Speed)
{
	Assa = SetAssaEffect(50,FileName,0,pPosi,0);                           
	cAssaEffect[Assa]->Size.w = 500;    
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = GetRandomPos(10,15);
	cAssaEffect[Assa]->AniCount = GetRandomPos(0,cAssaEffect[Assa]->AniMaxCount);
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_RANDOM_ROTATE;
	//cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
	//cAssaEffect[Assa]->cAssaTrace->SetLength(20); //연결길이를 잡는다
	cAssaEffect[Assa]->Angle.x = GetRandomPos(0,4096);
	cAssaEffect[Assa]->Angle.y = GetRandomPos(0,4096);
	cAssaEffect[Assa]->MoveSpeed.z = Range;
	cAssaEffect[Assa]->RAngleSpeed = Speed;

	return TRUE;
}
/*----------------------------------------------------------------------------*
*							   BALLL PARTICLE RISING 
*-----------------------------------------------------------------------------*/	
int AssaParticle_RisingParticleContinue(POINT3D *pPosi , char *FileName ,int Size ,int Range , int SpeedY)
{ 
	Assa = SetAssaEffect(GetRandomPos(50,70),FileName,0,pPosi,0);   
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = cAssaEffect[Assa]->Max_Time/7;
	cAssaEffect[Assa]->AniCount = GetRandomPos(0,cAssaEffect[Assa]->AniMaxCount);
	cAssaEffect[Assa]->Size.w = GetRandomPos(Size-200,Size+200);
	cAssaEffect[Assa]->MoveSpeed.y = rand()%50+SpeedY;
	AssaGetCirclePosi(cAssaEffect[Assa],GetRandomPos(0,Range*10),GetRandomPos(0,4096));
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
	cAssaEffect[Assa]->NotFadeIn = 1;

	return TRUE;
}
/*----------------------------------------------------------------------------*
*							   Rotate Wide
*-----------------------------------------------------------------------------*/	
int AssaParticle_RotateWide(POINT3D *pPosi , char *FileName ,int Range , int SpeedY )
{
	int Temp =1;
	for(int i = 0; i < 3 ; i++){                                    
		for(int j = 0; j < 3 ; j++){           
		  Assa = SetAssaEffect(120,FileName,0,pPosi,0);      
		  cAssaEffect[Assa]->Size.w = 1000; 
		  cAssaEffect[Assa]->MoveSpeed.y = SpeedY;
		  AssaGetCirclePosi(cAssaEffect[Assa],Range*4,GetRandomPos(0,4096));
		  cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE;
		  if(Temp > 0 )Temp = -1;
		  else Temp = 1;
		  cAssaEffect[Assa]->RAngleSpeed = 100*Temp;
		  cAssaEffect[Assa]->Time = GetRandomPos(-5*i,-i*4)-j;
		  cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		  cAssaEffect[Assa]->cAssaTrace->SetLength(50); //연결길이를 잡는다
		  cAssaEffect[Assa]->NotFadeIn = 1;
		  cAssaEffect[Assa]->CODE = ASSA_PARTICLE_ROTATE_WIDE; 
		   
		}
	}

	return TRUE;
}
/*----------------------------------------------------------------------------*
*							   Wide
*-----------------------------------------------------------------------------*/	
int AssaParticle_Wide(POINT3D *pPosi , char *FileName ,int Num , int Time)
{
	for(int i = 0 ; i < Num ; i++){
		//선
		Assa = SetAssaEffect(100,FileName,0,pPosi,0);             
		cAssaEffect[Assa]->Size.w = 1000; 
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
		cAssaEffect[Assa]->MoveSpeed.z = 400;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->StartPosi.z = 256*2;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->cAssaTrace->SetLength(50); //연결길이를 잡는다
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Time = Time;


		//파티클
		/*
		Assa = SetAssaEffect(120,FileName,0,pPosi,0);      
		AssaGetAniFileMat(cAssaEffect[Assa]);
		cAssaEffect[Assa]->AniDelayTime = GetRandomPos(4,10);
		cAssaEffect[Assa]->AniCount = GetRandomPos(0,cAssaEffect[Assa]->AniMaxCount);
		cAssaEffect[Assa]->Size.w = 1000; 
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
		cAssaEffect[Assa]->MoveSpeed.z = 256;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Time = Time;
		*/
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*				   BombGather (미사용)
*-----------------------------------------------------------------------------*/	
int AssaParticle_BombGather(cASSAEFFECT *pEffect)
{
	for(int i = 0 ; i < 20 ; i++){
		Assa = SetAssaEffect(100,pEffect->szFileName,0,&pEffect->Posi,0);                   
		cAssaEffect[Assa]->Size.w = 1000;  
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_SPREAD;
		cAssaEffect[Assa]->RAngle = rand()%4096;
		cAssaEffect[Assa]->RDistance.z = 64;
		cAssaEffect[Assa]->Gravity = 10;
		cAssaEffect[Assa]->MoveSpeed.y = 50;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->MOVECODE_List[0] = ASSA_MOVE_GATHER;
		cAssaEffect[Assa]->MOVECODE_Time[0] = 70;
		cAssaEffect[Assa]->GatherSpeed = 20;
		cAssaEffect[Assa]->CenterPosi = pEffect->CenterPosi;

	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*				          Area   Particle 
*-----------------------------------------------------------------------------*/	
int AssaParticle_Area_Particle(POINT3D *Posi , char *FileName , int Range , int Time)
{
	for(int i = 0 ; i < 10 ; i++){ 
		Assa = SetAssaEffect(100,FileName,0,Posi,0);                   
		cAssaEffect[Assa]->Size.w = 1000;  
		AssaGetAniFileMat(cAssaEffect[Assa]);
		cAssaEffect[Assa]->AniCount = GetRandomPos(0,cAssaEffect[Assa]->AniMaxCount);
		cAssaEffect[Assa]->AniReverse = 1;
		cAssaEffect[Assa]->AniDelayTime = GetRandomPos(4,8);
		cAssaEffect[Assa]->StartPosi.z = GetRandomPos(256,256*Range*2);
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Time = Time;
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*				          Particle After Image (날치기 잔상) (에너쥐 쉴터에서 사용중)
*-----------------------------------------------------------------------------*/	
int AssaParticle_After_Image(POINT3D *Posi , char *FileName , int Range , int Time)
{
	//파티클
	/*
	Assa = SetAssaEffect(70,FileName,0,Posi,0);                                 
	cAssaEffect[Assa]->Size.w = 1500;  
	cAssaEffect[Assa]->StartPosi.z = GetRandomPos(16*Range,16*Range*2); 
	AssaSetStartPosi(cAssaEffect[Assa]);
	cAssaEffect[Assa]->Time = Time;
	cAssaEffect[Assa]->MOVECODE = ASSA_DECRESIZE;
	cAssaEffect[Assa]->ReSize.w = 10;
	cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;
	*/

	//요건 선형 파티클 
	for(int i = 0 ; i < 3 ; i++){              
		Assa = SetAssaEffect(10,"flare.tga",0,Posi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(6000,7000); 
		cAssaEffect[Assa]->Size.h = GetRandomPos(300,500); 
		cAssaEffect[Assa]->FACEY  = (i+1)*(4096/6);
		cAssaEffect[Assa]->NotFadeIn = 1;
		//cAssaEffect[Assa]->ZposiFlag = 1;
		cAssaEffect[Assa]->Face.r = 0;
		cAssaEffect[Assa]->Face.g = 255;
		cAssaEffect[Assa]->Face.b = 255;
	}

	return TRUE;
}

/*----------------------------------------------------------------------------*
*				       PIERCING Paticle
*-----------------------------------------------------------------------------*/	
int AssaParticle_Piercing(cASSAEFFECT *pEffect)
{
	POINT3D TempPosi;
	//무기의 앞부분 과 캐릭의 1직선 방향으로 날린다  
	AssaSearchWeaponPos(pEffect->pChar,&pEffect->Posi,1);            
	cAssaEffect[Assa]->Face.MatNum = g_NewParticleMgr.Start("Piercing1", pEffect->Posi); //호바람 파티클을 붙인다 

	//날아갈곳 지점을 구한다 
	GetMoveLocation(  0, 0,256*128 , pEffect->Angle.x, ((pEffect->pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP, 0 );
	TempPosi.x = pEffect->Posi.x+GeoResult_X;
	TempPosi.y = pEffect->Posi.y;
	TempPosi.z = pEffect->Posi.z+GeoResult_Z;

	pEffect->MOVECODE = ASSA_MOVE;
	pEffect->MoveSpeed.x = (pEffect->Posi.x - TempPosi.x)/20;
	pEffect->MoveSpeed.z = (pEffect->Posi.z - TempPosi.z)/20;
	pEffect->CODE = ASSA_PARTICLE_PIERCING; 


	return TRUE;
}

/*----------------------------------------------------------------------------*
*				       PIERCING Paticle Aura
*-----------------------------------------------------------------------------*/	
int AssaParticle_Piercing_Aura(cASSAEFFECT *pEffect)
{
/*
	for(int i = 0; i < 100 ; i++){            
		Assa = SetAssaEffect(100,"line.bmp",0,&pEffect->CenterPosi,0);              
		cAssaEffect[Assa]->Size.w = 250;
		cAssaEffect[Assa]->GatherSpeed = 40;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_GATHER;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		cAssaEffect[Assa]->RDistance.z = GetRandomPos(256*16,256*16*2);
		cAssaEffect[Assa]->RAngle = GetRandomPos(0,4096);
		cAssaEffect[Assa]->StartPosi.z = cAssaEffect[Assa]->RDistance.z;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Time = GetRandomPos(0,-300);

		//각에따른 방향으로 Face를 Scale한다 
		GetMoveLocation(  cAssaEffect[Assa]->StartPosi.x, cAssaEffect[Assa]->StartPosi.y,cAssaEffect[Assa]->StartPosi.z*2 , cAssaEffect[Assa]->Angle.x, cAssaEffect[Assa]->Angle.y, 0 );
		cAssaEffect[Assa]->ScalePosi.x = GeoResult_X/2;
		cAssaEffect[Assa]->ScalePosi.y = GeoResult_Y/2;
		cAssaEffect[Assa]->ScalePosi.z = GeoResult_Z/2;

	}
*/

	return TRUE;
} 
/*----------------------------------------------------------------------------*
*				       WINDY Paticle 
*-----------------------------------------------------------------------------*/	
int AssaParticle_Windy2(smCHAR *pChar)
{
	for(int i=0 ; i< 20 ; i++){           
		Assa = SetAssaEffect(100,"star05Y_03.bmp",pChar,0,0);                                 
		cAssaEffect[Assa]->fTemp[0] = ((float)i)/30.0f;
		AssaSearchWeaponPos(pChar,&cAssaEffect[Assa]->Posi,cAssaEffect[Assa]->fTemp[0]);            
		cAssaEffect[Assa]->Size.w = 1700; 
		cAssaEffect[Assa]->MaxAlphaAmount = 50;
		cAssaEffect[Assa]->CODE = ASSA_PARTICLE_WINDY;
		cAssaEffect[Assa]->NotFadeIn = 1;

/*
		if( (i % 2) == 0)
			AssaParticle_RisingParticleContinue(&cAssaEffect[Assa]->Posi,"star01Y_02.bmp",500,0,GetRandomPos(50,80));
*/
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*				       Holy Reflection 
*-----------------------------------------------------------------------------*/	
int AssaParticle_Holy_Reflection(cASSAEFFECT *pEffect)
{
	//원형이미지 
	Assa = SetAssaEffect(GetRandomPos(80,100),"star01M_04.bmp",0,&pEffect->Posi,0);     
	AssaSearchWeaponPos(pEffect->pChar,&cAssaEffect[Assa]->Posi,1);            
	cAssaEffect[Assa]->Size.w = GetRandomPos(500,1000);
	cAssaEffect[Assa]->MoveSpeed.y = rand()%50;
	AssaGetCirclePosi(cAssaEffect[Assa],GetRandomPos(0,64*10),GetRandomPos(0,4096));
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
	return TRUE;
}
/*----------------------------------------------------------------------------*
*				       HOLYMIND Paticle 
*-----------------------------------------------------------------------------*/	
int AssaParticle_HolyMind(POINT3D *pPosi , int Flag)
{
	
	if(!Flag){      
		//Assa = SetAssaEffect(15,"holy-m.tga",0,pPosi,0);                   
		//cAssaEffect[Assa]->Size.w = GetRandomPos(1000,1500);
		//cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED | ASSA_CHAR_POSI;
		//cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(24,42);
		//cAssaEffect[Assa]->NotFadeIn = 1; 
		//cAssaEffect[Assa]->CODE = ASSA_PARTICLE_HOLY_MIND;
		//cAssaEffect[Assa]->ZposiFlag = 1;
		
		//요건 선 
		Assa = SetAssaEffect(90,"flare.tga",0,pPosi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(7000,10000); 
		cAssaEffect[Assa]->Size.h = GetRandomPos(500,1200); 
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_HOLY_MIND;
		cAssaEffect[Assa]->NotFadeIn = 1;
		//cAssaEffect[Assa]->ZposiFlag = 1;
		cAssaEffect[Assa]->ActionIndex[0] = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 0;

	}
	else{
		//Assa = SetAssaEffect(40,"holy-m.tga",0,pPosi,0);           
		//cAssaEffect[Assa]->Size.w = GetRandomPos(1000,1500);
		//cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED | ASSA_DECRESIZE | ASSA_CHAR_POSI;
		//cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(16,32);
		//cAssaEffect[Assa]->NotFadeIn = 1; 
		//cAssaEffect[Assa]->ReSize.w = 50;
		//cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;
		//cAssaEffect[Assa]->ZposiFlag = 1;
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*
*				          LIGHT
*-----------------------------------------------------------------------------*/	
/*
#define ASSA_COLOR_CODE_YELLOW		0x00000001
#define ASSA_COLOR_CODE_BLUE		0x00000002
#define ASSA_COLOR_CODE_GREEN		0x00000003
#define ASSA_COLOR_CODE_VIOLET		0x00000004
#define ASSA_COLOR_CODE_RED			0x00000005
*/

int AssaParticle_Char_Light(smCHAR *pChar ,  DWORD ColorCODE , int Time ,int MaxAlpha, int  SizeW ,int SizeH )
{
	switch(ColorCODE){     
		case ASSA_COLOR_CODE_YELLOW:
			Assa = SetAssaEffect(Time,"star05Y_04.bmp",pChar,0,7000);     
		break;
		case ASSA_COLOR_CODE_BLUE:
			Assa = SetAssaEffect(Time,"star05B_04.bmp",pChar,0,7000);     
		break;
		case ASSA_COLOR_CODE_GREEN:
			Assa = SetAssaEffect(Time,"star05G_04.bmp",pChar,0,7000);     
		break;
		case ASSA_COLOR_CODE_VIOLET:
			Assa = SetAssaEffect(Time,"star05M_04.bmp",pChar,0,7000);     
		break;
		case ASSA_COLOR_CODE_RED:
			Assa = SetAssaEffect(Time,"star05R_04.bmp",pChar,0,7000);     
		break;

	}
	cAssaEffect[Assa]->Size.w = SizeW;
	cAssaEffect[Assa]->Size.h = SizeH;
	cAssaEffect[Assa]->MOVECODE = ASSA_CHAR_POSI;
	cAssaEffect[Assa]->MaxAlphaAmount = MaxAlpha;
	return TRUE;
}

int AssaParticle_Char_Light2(smCHAR *pChar ,  DWORD ColorCODE , int Time )
{
	Assa = SetAssaEffect(Time,"flare.tga",pChar,0,6000);        
	switch(ColorCODE){      
		case ASSA_COLOR_CODE_YELLOW:
			cAssaEffect[Assa]->Face.r = 255;
			cAssaEffect[Assa]->Face.g = 180;
			cAssaEffect[Assa]->Face.b = 120;
		break;
		case ASSA_COLOR_CODE_BLUE:
			cAssaEffect[Assa]->Face.r = 100;
			cAssaEffect[Assa]->Face.g = 150;
			cAssaEffect[Assa]->Face.b = 255;
		break;
		case ASSA_COLOR_CODE_GREEN:
			cAssaEffect[Assa]->Face.r = 100;
			cAssaEffect[Assa]->Face.g = 255;
			cAssaEffect[Assa]->Face.b = 100;
		break;
		case ASSA_COLOR_CODE_VIOLET:
			cAssaEffect[Assa]->Face.r = 255;
			cAssaEffect[Assa]->Face.g = 100;
			cAssaEffect[Assa]->Face.b = 230;
		break;
		case ASSA_COLOR_CODE_RED:
			cAssaEffect[Assa]->Face.r = 255;
			cAssaEffect[Assa]->Face.g = 100;
			cAssaEffect[Assa]->Face.b = 100;
		break;

	}
	cAssaEffect[Assa]->Size.w = 10000;
	cAssaEffect[Assa]->MOVECODE = ASSA_CHAR_POSI;
	cAssaEffect[Assa]->MaxAlphaAmount = 150;
	cAssaEffect[Assa]->NotFadeIn = 1;
	cAssaEffect[Assa]->NotFadeOut = 1;
	cAssaEffect[Assa]->ZposiFlag = 1;

	cAssaEffect[Assa]->CODE = ASSA_PARTICLE_CHAR_LIGHT;


	return TRUE;
}

//유니온 코어 이펙트 
int sinAssaUnionCoreEffect(smCHAR *pChar )
{

	POINT3D TempPosi = {pChar->pX,pChar->pY,pChar->pZ};	                            	  
	int Temp =1 , Temp2 =1 ,  Temp3 = 1 , Temp4 = 1;;

	SetDynLight( pChar->pX, pChar->pY , pChar->pZ ,255, 150, 100, 150, 100 ,1);   
	for(int i = 0 ; i < 10 ; i++){ 	    
/*
		///////라인  
		Assa = SetAssaEffect(120,"fire01_02.bmp",pChar,0,0);          
		cAssaEffect[Assa]->Size.w = 600; 
		cAssaEffect[Assa]->MoveSpeed.y = 300;
		AssaGetCirclePosi(cAssaEffect[Assa],256*6,GetRandomPos(0,4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE |ASSA_CHAR_POSI;
		if(Temp > 0 )Temp = -1;
		else Temp = 1;
		cAssaEffect[Assa]->RAngleSpeed = 100*Temp;
		cAssaEffect[Assa]->Time = GetRandomPos(-5*i,-i*4);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(30); //연결길이를 잡는다
		cAssaEffect[Assa]->NotFadeIn = 1;

		/////// 파티클  
		Assa = SetAssaEffect(120,"star01Y_01.bmp",pChar,0,0);         
		cAssaEffect[Assa]->Size.w = 2000;  
		cAssaEffect[Assa]->MoveSpeed.y = 200;
		AssaGetCirclePosi(cAssaEffect[Assa],256*8,GetRandomPos(0,4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE | ASSA_CHAR_POSI;
		if(Temp2 > 0 )Temp2 = -1;
		else Temp2 = 1;
		cAssaEffect[Assa]->RAngleSpeed = 50*Temp2;
		cAssaEffect[Assa]->Time = GetRandomPos(-5*i,-i*4);
		cAssaEffect[Assa]->cAssaTrace->SetLength(30); //연결길이를 잡는다
		cAssaEffect[Assa]->NotFadeIn = 1;
		AssaGetAniFileMat(cAssaEffect[Assa]);
		cAssaEffect[Assa]->AniDelayTime = GetRandomPos(10,15);
		cAssaEffect[Assa]->AniCount = GetRandomPos(0,cAssaEffect[Assa]->AniMaxCount);

		//메쉬 
		Assa = SetAssaEffect(70,"GreatHealing.ASE",pChar,0,4000);         
		cAssaEffect[Assa]->AniMaxCount = 32; 
		cAssaEffect[Assa]->AniDelayTime = 4;
		AssaGetCirclePosi(cAssaEffect[Assa],256*8,GetRandomPos(0,4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE|ASSA_CHAR_POSI;
		cAssaEffect[Assa]->MoveSpeed.y = 200;
		if(Temp3 > 0 )Temp3 = -1;
		else Temp3 = 1;
		cAssaEffect[Assa]->RAngleSpeed = 50 *Temp3;
		cAssaEffect[Assa]->CODE = SKILL_GRAND_HEALING;
		cAssaEffect[Assa]->Time = GetRandomPos(-5*i,-i*4);
*/
		/*
		//회전 
		Assa = SetAssaEffect(120,"star06Y_04.bmp",pChar,0,0);                               
		cAssaEffect[Assa]->Size.w = 1000;  
		//cAssaEffect[Assa]->MoveSpeed.y = 300;
		AssaGetCirclePosi(cAssaEffect[Assa],256*7,GetRandomPos(0,4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE |ASSA_CHAR_POSI;
		if(Temp4 > 0 )Temp4 = -1;
		else Temp4 = 1;
		cAssaEffect[Assa]->RAngleSpeed = 50*Temp4;
		cAssaEffect[Assa]->Time = GetRandomPos(-5*i,-i*4);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		cAssaEffect[Assa]->ScalePosi.y = 15000;
		cAssaEffect[Assa]->NotFadeIn = 1;
		*/

		//회전 라인 
		Assa = SetAssaEffect(200,"star06B_04.bmp",pChar,0,-3000);                
		cAssaEffect[Assa]->Size.w = 1000; 
		cAssaEffect[Assa]->MoveSpeed.y = 10000;
		AssaGetCirclePosi(cAssaEffect[Assa],256*3,GetRandomPos(0,4096));
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE |ASSA_CHAR_POSI;
		if(Temp4 > 0 )Temp4 = -1;
		else Temp4 = 1;
		cAssaEffect[Assa]->RAngleSpeed = 200*Temp4;
		//cAssaEffect[Assa]->Time = GetRandomPos(-5*i,-i*4);
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(30); //연결길이를 잡는다
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->CODE = ASSA_PARTICLE_UNIONCORE;
		//cAssaEffect[Assa]->Temp[0] = x;
		//cAssaEffect[Assa]->Temp[1] = y;

	}


	return TRUE;
}

//라투 이펙트 
int sinEffect_Ratoo_Aura(smCHAR *pChar )
{

	//Assa = SetAssaEffect(1000,"m_ratoo.tga",pChar,0,5000);                     
	Assa = SetAssaEffect(1000,"Bone",pChar,0,5000);                      
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD; 
	cAssaEffect[Assa]->Size.w = 11000*3;
	cAssaEffect[Assa]->MOVECODE =  ASSA_ANGLE_ROTATE |ASSA_CHAR_POSI;
	cAssaEffect[Assa]->ARotateSpeed.y = -1;
	cAssaEffect[Assa]->CODE = ASSA_EFFECT_RATOO_AURA;
	cAssaEffect[Assa]->NotFadeIn = 1;
	cAssaEffect[Assa]->NotFadeOut = 1;

	return TRUE;
}

//라투 이펙트 십자형 
int Ratoo_Aura2Count = 0;
int sinEffect_Ratoo_Aura2(smCHAR *pChar )
{
	Ratoo_Aura2Count++;
	if(Ratoo_Aura2Count < 70)return TRUE;
	Ratoo_Aura2Count = 0;

	Assa = SetAssaEffect(300,"m_ratoo2.tga",pChar,0,5000);                                
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD; 
	cAssaEffect[Assa]->Size.w = 8000*3;
	cAssaEffect[Assa]->MOVECODE =  ASSA_CHAR_POSI | ASSA_ANGLE_ROTATE;
	cAssaEffect[Assa]->ARotateSpeed.y = 10000; //돌리지않고 그냥 땜빵을 하기위한 응급처치 
	cAssaEffect[Assa]->CODE = ASSA_EFFECT_RATOO_AURA2;
	//cAssaEffect[Assa]->NotFadeIn = 1;
	cAssaEffect[Assa]->NotFadeOut = 1;
	cAssaEffect[Assa]->MaxAlphaAmount = 200;

	Assa = SetAssaEffect(300,"flare.bmp",pChar,0,pChar->PatHeight/4);                   
	cAssaEffect[Assa]->Size.w = 8000*3;
	cAssaEffect[Assa]->MOVECODE = ASSA_CHAR_POSI;
	cAssaEffect[Assa]->CODE = ASSA_EFFECT_RATOO_AURA;
	//cAssaEffect[Assa]->NotFadeOut = 1;
	//cAssaEffect[Assa]->NotFadeIn = 1;
	cAssaEffect[Assa]->ZposiFlag = 1;
	cAssaEffect[Assa]->Face.r = 50;
	cAssaEffect[Assa]->Face.g = 100;
	cAssaEffect[Assa]->Face.b = 50;


	return TRUE;
}