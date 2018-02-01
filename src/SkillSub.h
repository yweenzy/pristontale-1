
//스킬을 오픈한다
int OpenPlaySkill( sSKILL *lpSkill );
//스킬 공격을 시도
int PlaySkillAttack( sSKILL *lpSkill , smCHAR *lpChar );
//스킬 적용 거리를 구한다
int GetSkillDistRange( sSKILL *lpSkill , int AttackRange , int AttackMode );
//스킬 공격을 시도
int PlaySkillLoop( int SkillCode , smCHAR *lpChar );

//잔상용 스킬색상 선택
int SetSkillMotionBlurColor( int dwSkillCode );
//범위 스킬 확인
int GetSkillPower( smCHAR *lpChar , smCHAR *lpChar2 , int dx, int dy, int dz );
//스킬 습득 이펙트
int	LearnSkillEffect( smCHAR *lpChar=0 );
//스킬감시
int CheckPlaySkill();
