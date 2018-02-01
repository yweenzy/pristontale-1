/*----------------------------------------------------------------------------*
*	파일명 :  Morayion.h	
*	하는일 :  모라이온의 스킬 헤더
*	작성일 :  최종업데이트 9월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#define MAX_CONTINUE_SKILL		10

//////////////// 공통적용부분
int sinCheckSkillUseOk(sSKILL *lpSkill);
int sinUseManaStamina(sSKILL *lpSkill);
int sinContinueSkillSet(sSKILL *lpSkill);
int sinCheckContinueSkill();
int sinSwitchSkill(sSKILL *pSkill);

//////////////// 나이트
int F_Sword_Blast();
int F_HolyBody();	
int F_Physical_Traning();
int F_Double_Crash();	

int F_Holy_Valor();
int F_Brandish();
int F_Piercing();
int F_Drastic_Spirit();

int F_S_Mastery();
int F_D_Inhalation();
int F_Holy_Incantation();
int F_Grand_Cross();

//4차 스킬
int F_Divine_Piercing();   //디바인 피어싱 
int F_Godly_Shield();      //갓들리 쉴드
int F_God_Bless();         //갓 블레스 
int F_Sword_Of_Justice();  //스워드 오브 저스틱

/////////// 아틀란타
int F_S_Strike();
int F_Farina();
int F_D_Mastery();
int F_V_Spear();

int F_Windy();
int F_Twist_Javelin();
int F_Soul_Sucker();
int F_Fire_Javelin();

int F_Split_Javelin();
int F_T_Of_Valhalla();
int F_Lightning_Javelin();
int F_Storm_Javelin();

//4차 스킬
int F_Hall_Of_Valhalla();  //헬오브 발헬라
int F_X_Rage();            //엑스 라지
int F_Frost_Javelin();     //프로스트 재블린
int F_Vengeance();         //벤첸스

/////////// 프리스티스
int F_Healing();
int F_HolyBolt();
int F_M_Spark();
int F_HolyMind();

int F_Meditation();
int F_Divine_Lightning();
int F_Holy_Reflection();
int F_Grand_Healing();

int F_Vigor_Ball();
int F_Resurrection();
int F_Extinction();
int F_Virtual_Life();

//4차 스킬
int F_Glacial_Spike();      //클래셔 스파이크
int F_Regeneration_Field(); //리제너레이션 필드
int F_Chain_Lightning();    //체인 라이팅
int F_Summon_Muspell();     //서몬 뮤스펠



/////////// 메지션
int F_Agony();
int F_FireBolt();
int F_Zenith();
int F_ZenithFromServer(int Time); //파티원적용원소속성
int F_FireBall();

int F_Mental_Mastery();
int F_Watornado();
int F_Enchant_Weapon();
int F_Dead_Ray();

int F_Energy_Shield();
int F_Diastrophism();
int F_Spirit_Elemental();
int F_D_Sword();

//4차 스킬
int F_Fire_Elemental(); //파이어 엘레멘탈
int F_Flame_Wave();     //플레림 웨이브
int F_Distortion();		//디스트럭션  
int F_Meteo();			//메테오

/////////////// 나이트
//스워드 블레스트
extern int Sword_Blast_UseMana[10];
extern int Sword_Blast_Damage[10][2];
extern int Sword_Blast_ShootingRange[10];

//홀리 바디
extern int HolyBody_UseMana[10];
extern int HolyBody_Absorb[10];
extern int HolyBody_Time[10];

//피지컬 트레이닝
extern int P_Traning_Stamina[10];

//더블 크래쉬
extern int D_Crash_UseMana[10];
extern int D_Crash_Damage[10];
extern int D_Crash_Critical[10];

//홀리 벨러 
extern int Holy_Valor_Damage[10];
extern int Holy_Valor_Time[10];
extern int Holy_Valor_Mana[10];

//브렌디쉬
extern int Brandish_Range[10];
extern int Brandish_Damage[10];
extern int Brandish_Mana[10];

//피어싱
extern int Piercing_Damage[10];
extern int Piercing_Attack_Rating[10];
extern int Piercing_Mana[10];

//드레스틱 스피릿
extern int Drastic_Spirit_Defense[10];
extern int Drastic_Spirit_Time[10];
extern int Drastic_Spirit_Mana[10];

//스워드 마스터리
//extern int Flame_Brandish_Damage[10][2];
//extern int Flame_Brandish_UseMana[10];
extern int Sword_Mastery_DamagePercent[10];

//디바인 인홀레이션
extern int D_Inhalation_Life[10];
extern int D_Inhalation_Block[10];
extern int D_Inhalation_Time[10];
extern int D_Inhalation_UseMana[10];

//홀리 인켄테이션
extern int H_Incantation_Success[10];
extern int H_Incantation_AddLife[10];
extern int H_Incantation_Time[10];
extern int H_Incantation_UseMana[10];

//그랜드 크로스
extern int Grand_Cross_Damage[10];
extern int Grand_Cross_AttackRate[10];
extern int Grand_Cross_UndeadDamage[10];
extern int Grand_Cross_UseMana[10];

//4차 스킬
//디바인 피어싱
extern int  Divine_Piercing_DamagePercent[10];
extern int  Divine_Piercing_AddHit[10];
extern int	Divine_Piercing_AttackNum[10];
extern int  Divine_Piercing_UseMana[10];

//갓들 쉴드
extern int Godly_Shield_AbsorbPercent[10];
extern int Godly_Shield_Time[10];
extern int Godly_Shield_UseMana[10];

//갓 블레스
extern int God_Bless_AddDamage[10];
extern int God_Bless_Time[10];
extern int God_Bless_UseMana[10];

//스워드 오브 저스틱스
extern int Sword_Of_Justice_DamagePercent[10];
extern int Sword_Of_Justice_Area[10];
extern int Sword_Of_Justice_UseMana[10];


/////////// 아틀란타
//쉴드 스트라이크
extern int S_Strike_UseMana[10];
extern int S_Strike_Damage[10][2];
//extern int S_Strike_Stun[10]; 현제 미사용

//파리나
extern int Farina_UseMana[10];
extern int Farina_Speed[10];
extern int Farina_AttackRate[10];

//드로윙마스터리
extern int T_Mastery_Damage[10];

//비거 스피어
extern int V_Spear_UseMana[10];
extern int V_Spear_Damage[10][2];

//윈디
extern int Windy_Attack_Rating[10];
extern int Windy_Time[10];      
extern int Windy_Mana[10];     

//트위스트 재블린
extern int Twist_Javelin_Damage[10];
extern int Twist_Javelin_Attack_Rating[10];
extern int Twist_Javelin_Mana[10];      

//소울 썩커
extern int Soul_Sucker_Absorb[10];  
extern int Soul_Sucker_Mana[10];    

//파이어 재블린
extern int Fire_Javelin_Damage[10][2];
extern int Fire_Javelin_Mana[10];

//스플릿 재블린
extern int Split_Javelin_AttackNum[10];
extern int Split_Javelin_Damage[10];
extern int Split_Javelin_AttackRate[10];
extern int Split_Javelin_UseMana[10];

//트라이엄프 오브 발할라
extern int T_Of_Valhalla_Damage[10];
extern int T_Of_Valhalla_Time[10];
extern int T_Of_Valhalla_UseMana[10];

//라이트닝 자벨린
extern int Lightning_Javelin_Damage[10][2];
extern int Lightning_Javelin_UseMana[10];

//스톰 자벨린
extern int Storm_Javelin_Damage[10];
extern int Storm_Javelin_UseMana[10];

//4차 스킬
//헬오브 발할라
extern int Hall_Of_Valhalla_AddEvation[10];  //추가 회피력 상승
extern int Hall_Of_Valhalla_Time[10];        //유지시간
extern int Hall_Of_Valhalla_UseMana[10];

//엑스 라지
extern int X_Rage_DamagePercent[10];   //공격력 가중
extern int X_Rage_Area[10];            //공격 범위
extern int X_Rage_UseMana[10];

//프로스트 재블린
extern int Frost_Javelin_IceAddDamage[10][2];  //ice추가 공격력
extern int Frost_Javelin_SpeedSubPercent[10];   //타격된 적의 속도 저하치
extern int Frost_Javelin_IceTime[10];           //아이싱 시간
extern int Frost_Javelin_Time[10];              //유지타임
extern int Frost_Javelin_UseMana[10];


//벤첸스
extern int Vengeance_DamagePercent[10];         //공격력 가중
extern int Vengeance_AddCritical[10];			//크리티컬 추가  // 장별 - 스킬밸런스 조정(10.08.10)
extern int Vengeance_Range[10];                  //사정거리  
extern int Vengeance_UseMana[10];


////////////프리스티스
//힐링
extern int Healing_UseMana[10];
extern int Healing_Heal[10][2];

//홀리 볼트
extern int HolyBolt_UseMana[10];
extern int HolyBolt_Damage[10][2];

//멀티스파크
extern int M_Spark_UseMana[10];
extern int M_Spark_Damage[10][2];
extern int M_Spark_Num[10];


//홀리 마인드
extern int HolyMind_UseMana[10];
extern int HolyMind_DecDamage[10];
extern int HolyMind_Time[10];

//메디테이션
extern float Meditation_Regen[10];

//디바인 라이트닝
extern int Divine_Lightning_Damage[10][2];
extern int Divine_Lightning_Num[10];
extern int Divine_Lightning_Mana[10];

//홀리 리플렉션
extern int Holy_Reflection_Return_Damage[10];
extern int Holy_Reflection_Time[10];
extern int Holy_Reflection_Mana[10];

//그랜드 힐링
extern int Grand_Healing[10][2];
extern int Grand_Healing_Range[10];
extern int Grand_Healing_Mana[10];

//비거 볼
extern int Vigor_Ball_Damage[10][2];
extern int Vigor_Ball_UseMana[10];

//리져렉션
extern int Resurrection_Percent[10];
extern int Resurrection_Exp[10];
extern int Resurrection_UseMana[10];

//익스팅션
extern int Extinction_Percent[10];
extern int Extinction_Amount[10];
extern int Extinction_UseMana[10];

//버추얼 라이프
extern int Virtual_Life_Percent[10];
extern int Virtual_Life_Time[10];
extern int Virtual_Life_UseMana[10];

//4차 스킬
//글래이셔 스트라이크
extern int Glacial_Spike_Damage[10][2];       //공격력
extern int Glacial_Spike_Area[10];            //공격 범위      
extern int Glacial_Spike_UseMana[10]; 

//리제너레이션 필드
extern float Regeneration_Field_LifeRegen[10];   //체력 재생력 추가
extern float Regeneration_Field_ManaRegen[10];   //기력 재생력 추가
extern int   Regeneration_Field_Time[10];        //지속시간
extern int   Regeneration_Field_Area[10];        //유효범위
extern int   Regeneration_Field_UseMana[10];

//체인라이트닝
extern int Chain_Lightning_Damage[10][2];           //공격력
extern int Chain_Lightning_Num[10];                 //연결 갯수
extern int Chain_Lightning_Range[10];               //연결 거리
extern int Chain_Lightning_UseMana[10];

//서몬 뮤스펠
extern int Summon_Muspell_Damage[10][2];
extern int Summon_Muspell_Attack_Delay[10];			// 공격딜레이
extern int Summon_Muspell_UndeadAbsorbPercent[10];  //언데드의 공격력 흡수치
extern int Summon_Muspell_BlockPercent[10];         //유저 블록율
extern int Summon_Muspell_Time[10];					//유지시간
extern int Summon_Muspell_UseMana[10];   

/////////////메지션
//어고니
extern int Agony_UseMana[10];
extern int Agony_ConvLife[10];

//파이어 볼트
extern int FireBolt_UseMana[10];
extern int FireBolt_Damage[10][2];

//제니쓰
extern int Zenith_UseMana[10];
extern int Zenith_Element[10];
extern int Zenith_Time[10];


//파이어 볼
extern int FireBall_UseMana[10];
extern int FireBall_Damage[10][2];
extern int FireBall_Range[10];
extern int FireBall_Area[10];

//에너지 쉘터
extern int Mental_Mastery_Mana[10];
//extern int Energy_Shelter_Down_Damage[10];
//extern int Energy_Shelter_Time[10];
//extern int Energy_Shelter_Mana[10];

//워토네이토
extern int Watornado_Damage[10][2];
extern int Watornado_Range[10];
extern int Watornado_Mana[10];
extern int Watornado_Area[10];

//인헨스 웨폰
extern int Enchant_Weapon_Damage_Ice[10][2];
extern int Enchant_Weapon_Damage_Fire[10][2];
extern int Enchant_Weapon_Damage_Lightning[10][2];
extern int Enchant_Weapon_Time[10];
extern int Enchant_Weapon_Mana[10];

//데드 레이
extern int Dead_Ray_Damage[10][2];
extern int Dead_Ray_Range[10];
extern int Dead_Ray_Mana[10];

//에너지 쉴드
extern int Energy_Shield_DecDamage[10];
extern int Energy_Shield_Time[10];
extern int Energy_Shield_UseMana[10];

//다이에 스트러피즘
extern int Diastrophism_Damage[10][2];
extern int Diastrophism_Area[10];
extern int Diastrophism_UseMana[10];

//스피릿 엘레멘탈
extern float Spirit_Elemental_RegenMana[10];
extern int Spirit_Elemental_Damage[10];
extern int Spirit_Elemental_Time[10];
extern int Spirit_Elemental_UseMana[10];

//댄싱 스워드
extern int Dancing_Sword_IceDamage[10][2];
extern int Dancing_Sword_FireDamage[10][2];
extern int Dancing_Sword_AttackDelay[10];
extern int Dancing_Sword_Time[10];
extern int Dancing_Sword_UseMana[10];

//**4차 스킬

//파이어 엘레멘탈 
extern int Fire_Elemental_Damage[10][2];  //엘레멘타 공격력
extern int Fire_Elemental_Hit[10];        //명중력
extern int Fire_Elemental_Life[10];       //생명력
extern int Fire_Elemental_UseMana[10];

//플레임 웨이브
extern int Flame_Wave_FireDamage[10][2];	  //불 공격력
extern int Flame_Wave_Area[10];			      //공격 범위
extern int Flame_Wave_UseMana[10];

//디스트록션
extern int Distortion_SpeedSubPercent[10];    //속도 저하 
extern int Distortion_DamageSubPercent[10];   //공격력 저하
extern int Distortion_Area[10];     
extern int Distortion_Time[10];
extern int Distortion_UseMana[10];   

//메테오
extern int Meteo_Damage[10][2];	               //공격력
extern int Meteo_Area[10];                     //범위
extern int Meteo_UseMana[10];