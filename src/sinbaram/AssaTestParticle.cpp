/*----------------------------------------------------------------------------*
*	파일명 :  AssaParticle.cpp	
*	하는일 :  아싸! 파티클 
*	작성일 :  최종업데이트 2002년 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"

#define ASSA_TEST_CODE		0x00010000
#define ASSA_TEST_CODE2		0x00010001
#define ASSA_TEST_CODE3		0x00010002

/*----------------------------------------------------------------------------*
*					         TEST
*-----------------------------------------------------------------------------*/	
int AssaParticle_TEST(smCHAR *pChar , char *FileName)
{ 
//	Assa = SetAssaEffect(300,"GreatHealing.ASE",0,pPosi,15000);                           
//	cAssaEffect[Assa]->AniMaxCount = 30;
	
	return TRUE;
}


int AssaParticle_TEST2(POINT3D *pPosi , char *FileName )
{
 
	Assa = SetAssaEffect(0,"GreatHealing.ASE",0,pPosi,15000);                            
	cAssaEffect[Assa]->AniMaxCount  = 30;
	cAssaEffect[Assa]->AniDelayTime = 5; 

	return TRUE;
}

/*----------------------------------------------------------------------------*
*							 KeyDown
*-----------------------------------------------------------------------------*/	
int sinAssaParticleTestKeyDown() //파티클 테스트 
{
	//lpCharSelPlayer	//한번 선택한 대상의 포인터 
	//lpCharMsTrace		//계속 선택한 대상의 포인터

	POINT3D Posi = {lpCurPlayer->pX,lpCurPlayer->pY,lpCurPlayer->pZ};    
 
	/*
	if(sinGetKeyClick('9')){          
		AssaParticle_TEST2(&Posi,"star05B_04.bmp");
		//AssaParticle_TEST2(&Posi,"star05B_04.bmp");
		//AssaParticle_TEST(lpCurPlayer,"energyshield.ASE" , 5000); 
		//AssaParticle_TEST(lpCurPlayer,"belt-02.ASE" , 5000);
		 
	}
	*/
	return TRUE;
}

/*----------------------------------------------------------------------------*
*							  Process 
*-----------------------------------------------------------------------------*/	
void sinAssaParticleTestProcess(cASSAEFFECT *pEffect)
{
	
	switch(pEffect->CODE){               
		case ASSA_TEST_CODE:    
			if(pEffect->Time <= 50){
				//AssaParticle_1(&pEffect->Posi,"star01Y_02.bmp");
			}

		break;
		case ASSA_TEST_CODE2: 

		break;
		case ASSA_TEST_CODE3:
		break;
	}

}

