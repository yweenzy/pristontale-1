/*----------------------------------------------------------------------------*
*	파일명 :  sinPublicEffect.h	
*	하는일 :  각종 이펙트에 쓰일 각각의 이펙트 
*	작성일 :  최종업데이트 2002년 10월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

int sinPublicEffectTestKey(); //스킬 테스트 Key

/*----------------------------------------------------------------------------*
*							시스템
*-----------------------------------------------------------------------------*/	
void sinInitPublicEffect();
void sinPublicEffectMove(cSINEFFECT2 *pEffect);	

/*----------------------------------------------------------------------------*
*							공용 이펙트 
*-----------------------------------------------------------------------------*/	
int sinEffect_WideLine(POINT3D *pPosi , int Mat , int Lenght , int Num);  //퍼지는 라인
int sinEffect_WideParticle_Bone(POINT3D *pPosi , int Mat , int Size , int Time , int Num , int Speed); 	//퍼지는 파티클 
int sinEffect_WideParticle(POINT3D *pPosi , int Mat , int Size);
int sinEffect_BombParticle(POINT3D *pPosi , int Mat , int Size , int Num);
int sinEffect_Light5(POINT3D *pPosi , int Size );
int sinEffect_SpoutParticle(POINT3D *pPosi ,int Mat ,int Num , int Size , int Time , int Gravity );
int sinEffect_GatherLine(smCHAR *pChar  , int Mat ,int Time);
int sinEffect_GatherLine2(smCHAR *pChar  , int Mat );
int sinEffect_WideContinueLine(smCHAR *pChar , int Mat ,int Time,int Height);
int sinEffect_WideContinueLine2(POINT3D *pPosi , int Mat );
int sinEffect_GatherCircleParticle(POINT3D *pPosi ,int Mat );
int sinEffect_Hit2(POINT3D *pPosi ,int Mat );


/*----------------------------------------------------------------------------*
*							몬스터 이펙트
*-----------------------------------------------------------------------------*/	
int sinEffect_Sen(POINT3D *pPosi); //센 이펙트 
int sinEffect_Sen_Particle(POINT3D *pPosi); 
int sinEffect_MutentTree_Smoke(POINT3D *pPosi); //뮤턴트 트리 
int sinEffect_MutentTree_Smoke_Particle(POINT3D *pPosi);
int sinEffect_MutentTree_Attack(smCHAR *pChar , smCHAR *desChar);
int sinEffect_MutentTree_Attack_Particle(POINT3D *pPosi);
int sinEffect_MutentTree_Attack_Particle2(POINT3D *pPosi);
int sinEffect_MutentTree_Hit_Particle(POINT3D *pPosi);
int sinEffect_MutentTree_Fire(POINT3D *pPosi);
int sinEffect_MutentTree_Fire_Particle(POINT3D *pPosi);
int sinEffect_Ratoo(smCHAR *pChar); //라투 
int sinEffect_Ratoo_Vigor(smCHAR *pChar); //라투 기 
int sinEffect_Ratoo_Vigor_Partilce(POINT3D *pPosi);