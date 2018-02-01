/*----------------------------------------------------------------------------*
*	파일명 :  sinAssaSkillEffect
*	하는일 :  Assa 스킬 이펙트
*	작성일 :  최종업데이트 2002년 12월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

int sinAssaSkillEffectKeyDown(); //스킬이펙트 테스트 

int sinAssaSkillEffectProcess(cASSAEFFECT *pEffect);

/*----------------------------------------------------------------------------*
*						  Assa 스킬 이펙트 
*-----------------------------------------------------------------------------*/	
////////나이트 
int sinSkillEffect_Brandish(smCHAR *pChar);  
int sinSkillEffect_Piercing(smCHAR *pChar);
int sinSkillEffect_Piercing_Attack(smCHAR *pChar);
int sinSkillEffect_DrasticSpirit(smCHAR *pChar);

////////메지션
int sinSkillEffect_Energy_Shelter(smCHAR *pChar);

////////프리스티스
int sinSkillEffect_Great_Healing(smCHAR *pChar);
int sinSkillEffect_Great_Healing_Party(smCHAR *pChar);
int sinSkillEffect_Holy_Reflection(smCHAR *pChar , int Time);
int sinSkillEffect_Holy_Reflection_Defense(smCHAR *pChar);
// 1차 스킬 수정
int sinSkillEffect_HolyMind(smCHAR *pChar,int Time);

////////아탈란타
int sinSkillEffect_Soul_Sucker(smCHAR *pChar , smCHAR *DesChar);
//int sinSkillEffect_Twist_Javelin(smCHAR *pChar , smCHAR *DesChar);
int sinSkillEffect_Windy(smCHAR *pChar);
int sinSkillEffect_Windy_Gather(smCHAR *pChar);

/*----------------------------------------------------------------------------*
*						        Extern 
*-----------------------------------------------------------------------------*/	

