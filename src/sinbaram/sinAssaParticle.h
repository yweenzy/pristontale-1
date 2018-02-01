/*----------------------------------------------------------------------------*
*	파일명 :  AssaParticle
*	하는일 :  아싸! 파티클
*	작성일 :  최종업데이트 2002년 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#ifndef _ASSAPARTICLE_HEADER_

#define _ASSAPARTICLE_HEADER_

#define ASSA_COLOR_CODE_YELLOW		0x00000001
#define ASSA_COLOR_CODE_BLUE		0x00000002
#define ASSA_COLOR_CODE_GREEN		0x00000003
#define ASSA_COLOR_CODE_VIOLET		0x00000004
#define ASSA_COLOR_CODE_RED			0x00000005


//예외 이펙트 코드 
#define ASSA_PARTICLE_UNIONCORE		0x70000001
#define ASSA_EFFECT_RATOO3			0x70000002

/*----------------------------------------------------------------------------*
*								함수 
*-----------------------------------------------------------------------------*/	
void sinAssaParticleProcess(cASSAEFFECT *pEffect); 
int  sinAssaParticleKeyDown();


/*----------------------------------------------------------------------------*
*							Particle	함수 
*-----------------------------------------------------------------------------*/	

// 스턴 
int AssaParticle_Stune(smCHAR *pChar , int Time);

// 원 만들기 
int AssaMakeCircle(POINT3D *pPosi , char *FileName , int Radius);

// 벨트 올리기
int AssaParticle_RisingBelt(POINT3D *pPosi ,char *FileName,int ContinueTime , int SpeedY );

//상승형 파티클 
int AssaParticle_RisingParticle(POINT3D *pPosi , char *FileName ,int Size ,  int ContinueTime , int Range , int Count , int SpeedY);

//상승형 라인
int AssaParticle_RisingLine(POINT3D *pPosi , char *FileName , int Size, int ContinueTime , int Range , int Count , int SpeedY);

//상승 곡선형 라인 
int AssaParticle_RisingRotateLine(POINT3D *pPosi , char *FileName , int ContinueTime , int Range , int Count , int SpeedY);

//상승 곡선형 좀더 쎈놈
int AssaParticle_RisingRotateLinePower(POINT3D *pPosi , char *FileName,int Range ,int Speed );

//물결형 파티클 
int AssaParticle_Wave(POINT3D *pPosi , char *FileName ,int Size);

//Light
int AssaParticle_Light(POINT3D *pPosi , char *FileName ,int Size , int Height , int Time);

//분출형 파티클 
int AssaParticle_Spread(POINT3D *pPosi , char *FileName );

//그냥 넓어지는 이미지 파티클 
int AssaParticle_WideFace(POINT3D *pPosi , char *FileName , int Size);

//모이는 파티클
int AssaParticle_Gather(POINT3D *pPosi , char *FileName ,int Range , int Speed ,int Num);

//돌면서 모이는 파티클 
int AssaParticle_RotateGather(POINT3D *pPosi , char *FileName , int Num);

//구모양에 빛을 모은다 
int AssaParticle_BALLLIGHT_GATHER(POINT3D *pPosi , char *FileName );

//구모양에 빛을 돌린다 
int AssaParticle_BALLLIGHT_ROTATE(POINT3D *pPosi , char *FileName ,int Range , int Speed);

//작은범위의 라이징 파티클 
int AssaParticle_RisingParticleContinue(POINT3D *pPosi , char *FileName ,int Size ,int Range , int SpeedY);

//돌면서 퍼지는 파티클 
int AssaParticle_RotateWide(POINT3D *pPosi , char *FileName ,int Range , int SpeedY );

//퍼지는 파티클 
int AssaParticle_Wide(POINT3D *pPosi , char *FileName ,int Num , int Time);

//터졌다가 모인다 
int AssaParticle_BombGather(cASSAEFFECT *pEffect);

//주변지역의 파티클 
int AssaParticle_Area_Particle(POINT3D *Posi , char *FileName , int Range , int Time);

//스페셜 Hit
int AssaParticle_SpecialHit(POINT3D *pPosi , int Time); 

//날치기 잔상 
int AssaParticle_After_Image(POINT3D *Posi , char *FileName , int Range , int Time);

//피어싱 파티클
int AssaParticle_Piercing(cASSAEFFECT *pEffect);

//피어싱 칼 주변 잔상 
int AssaParticle_Piercing_Aura(cASSAEFFECT *pEffect);

//타격 파티클 (Brandish에서 사용)
int AssaParticle_SpecialHit2(POINT3D *pPosi , int Time,int Kind=0);

//윈디용 파티클 
int AssaParticle_Windy2(smCHAR *pChar);

//홀리 리플렉션형 파티클 
int AssaParticle_Holy_Reflection(cASSAEFFECT *pEffect);

//홀리 마인드 
int AssaParticle_HolyMind(POINT3D *pPosi , int Flag=0);

//Light
int AssaParticle_Char_Light(smCHAR *pChar ,  DWORD ColorCODE , int Time ,int MaxAlpha, int  SizeW ,int SizeH=0 );

//Light2
int AssaParticle_Char_Light2(smCHAR *pChar ,  DWORD ColorCODE , int Time );

//UnionCore
int sinAssaUnionCoreEffect(smCHAR *pChar);

int sinEffect_Ratoo_Aura(smCHAR *pChar );

int sinEffect_Ratoo_Aura2(smCHAR *pChar );
#endif
