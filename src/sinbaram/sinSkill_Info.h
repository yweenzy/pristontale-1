
#define SIN_SKILL_USE_RIGHT		0x01000000		//오른쪽에만 사용가능 
#define SIN_SKILL_USE_LEFT		0x02000000		//왼쪽에만 사용가능 
#define SIN_SKILL_USE_ALL		0x03000000		//오른쪽 왼쪽 아무곳이나 사용가능 
#define SIN_SKILL_USE_NOT		0x04000000		//사용하는 스킬이 아님(패시브)

#include "Language\\Language.h"

#ifdef	_LANGUAGE_KOREAN

/*----------------------------------------------------------------------------*
*							템스크론
*-----------------------------------------------------------------------------*/	

//메카니션 
{"익스트림 쉴드",		"방패를 최대한 가공해 블럭 능력을 향상 시킨다",
10,		34,2,		110,4,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0},
F_Extreme_Shield,SKILL_EXTREME_SHIELD,SIN_SKILL_USE_RIGHT,E_Shield_UseMana},

{"메카닉 범",			"기계화 폭탄을 던져 해당 범위내 적에게 타격을 준다",
12,		28,2,		73,3,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Mechanic_Bomb,SKILL_MECHANIC_BOMB,SIN_SKILL_USE_RIGHT,Mechanic_Bomb_UseMana},

{"포이즌 어트리븃",		"독에 대한 적응력을 키워 영구적으로 속성을 상승시킨다",
14,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Poison_Attribute,SKILL_POISON_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

{"피지컬 앱소션",		"일시적으로 신체를 기계화하여 일정 시간동안 흡수력을 상승시킨다",
17,		30,2,		110,5,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Physical_Absorption,SKILL_PHYSICAL_ABSORB,SIN_SKILL_USE_RIGHT,P_Absor_bUseMana},

{"그레이트 스매쉬",		"힘을 모아 강한 일격을 가한다",
20,		38,2,		73,3,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0},
F_Great_Smash,SKILL_GREAT_SMASH,SIN_SKILL_USE_ALL,G_Smash_UseMana},

{"맥시마이즈",			"무기에 대한 최적화로 일정 시간동안 최대 공격력을 상승시킨다",
23,		41,2,		110,4,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,sinWS1,sinWT1,0},
F_Maximize,SKILL_MAXIMIZE,SIN_SKILL_USE_RIGHT,Maximize_UseMana},

{"오토메이션",			"발사형 무기를 자동화 하여 일정시간 동안 무기의 속도와 공격력을 상승시킨다",
26,		42,2,		110,4,
{0,0,0},			{sinWS1,sinWT1,0,0,0,0,0,0},
F_Automation,SKILL_AUTOMATION,SIN_SKILL_USE_RIGHT,Automation_UseMana},

{"스파크",			"강한 전기 에너지를 날려보내 범위내 적들을 공격한다",
30,		40,2,		82,2,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Spark,SKILL_SPARK,SIN_SKILL_USE_RIGHT,Spark_UseMana},

{"메탈 아머",		"일정 시간동안 메카니션 특성의 갑옷을 철갑화 시켜 방어력을 향상 시킨다",
40,		48,2,		110,5,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Metal_Armor,SKILL_METAL_ARMOR,SIN_SKILL_USE_RIGHT,Metal_Armor_UseMana},

{"그랜드 스매쉬",	"정교한 연타공격으로 명중력을 상승시켜 적에게 연타를 가한다", // 장별 - 스킬밸런스 조정(10.08.10)
43,		44,2,		82,2,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,sinWH1,0,0,0},
F_Grand_Smash,SKILL_GRAND_SMASH,SIN_SKILL_USE_RIGHT,Grand_Smash_UseMana},

{"메카닉웨펀마스터리",	"메카니션 특화 무기의 능력을 최적화 시킨다",
46,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_M_W_Mastery,SKILL_MECHANIC_WEAPON,SIN_SKILL_USE_NOT,0},

{"스파크 쉴드",		"강력한 스파크를 동반하는 방패를 생성한다.",
50,		52,2,		110,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0},
F_Spark_Shield,SKILL_SPARK_SHIELD,SIN_SKILL_USE_RIGHT,Spark_Shield_UseMana},

//[메카니션]4차 스킬
{"임펄션",		"강한 전류가 흐르는 일격으로 주변적을 공격한다.",
60,     	55,2,		130,0,
{1,0,0},            {sinWC1,sinWH1,sinWP1,sinWS2,0,0,0,0},
F_Impulsion,SKILL_IMPULSION,SIN_SKILL_USE_RIGHT,Impulsion_UseMana},

{"컴펄션",		"강한 기합으로 주변적들을 자신에게 끌어모은다.",
63,     	65,2,		440,0,
{1,0,0},            {0,0,0,0,0,0,0,0},
F_Compulsion,SKILL_COMPULSION,SIN_SKILL_USE_RIGHT,Compulsion_UseMana},

{"마그네틱 스피어",	"몸 주변에 강한 자기가 흐르는 구체를 생성한다.",
66,     	71,2,		600,0,
{1,0,0},            {0,0,0,0,0,0,0,0},
F_Magnetic_Sphere,SKILL_MAGNETIC_SPHERE,SIN_SKILL_USE_RIGHT,Magnetic_Sphere_UseMana},

{"메탈 고렘",		"메카닉 고렘을 소환한다.",
70,     	71,2,		1000,0,
{1,0,0},            {0,0,0,0,0,0,0,0},
F_Metal_Golem,SKILL_METAL_GOLEM,SIN_SKILL_USE_RIGHT,Metal_Golem_UseMana},


//파이터 
{"멜레이 마스터리",		"근접 무기에 대한 훈련으로 영구적으로 공격능력을 향상 시킨다",
10,		0,0,		0,0,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWS2,0,0,0,0},
F_Melee_Mastery,SKILL_MELEE_MASTERY,SIN_SKILL_USE_NOT,0},

{"파이어 어트리븃",		"불에 대한 적응력을 키워 영구적으로 속성을 상승시킨다",
12,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Fire_Attribute,SKILL_FIRE_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

{"레이빙",			"짧은 시간 광분상태가 되어 강력한 공격을 한다. 그러나 공격시 생명력이 감소한다.",
14,		35,2,		93,3,
{0,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,0,0,0},
F_Raving,SKILL_RAVING,SIN_SKILL_USE_ALL,Raving_UseMana},

{"임팩트",			"정교한 연타 공격으로 명중력을 상승시켜 적에게 강한 타격을 가한다",
17,		37,2,		86,4,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,0,0,0,0},
F_Impact,SKILL_IMPACT,SIN_SKILL_USE_ALL,Impact_UseMana},

{"트리플 임팩트",		"가공할 연타로 강력한 공격을 한다",
20,		39,2,		80,4,
{0,0,0},			{sinWA1,sinWC1,sinWP1,sinWS2,0,0,0,0},
F_Triple_Impact,SKILL_TRIPLE_IMPACT,SIN_SKILL_USE_ALL,T_Impact_UseMana},

{"부르틀 스윙",			"광폭한 공격으로 적에게 치명타를 가한다",
23,		41,2,		82,2,
{0,0,0},			{sinWA1,sinWS2,0,0,0,0,0,0},
F_Brutal_Swing,SKILL_BRUTAL_SWING,SIN_SKILL_USE_ALL,B_Swing_UseMana},

{"로어",			"강한 기를 분출하여 일시적으로 적들을 혼란에 빠뜨린다",
26,		39,2,		112,4,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Roar,SKILL_ROAR,SIN_SKILL_USE_RIGHT,Roar_UseMana},

{"레이지 of 제크람",		"영웅 제크람의 기술을 사용하여 적에게 화계의 타격을 가한다",
30,		45,2,		84,4,
{0,0,0},			{sinWA1,sinWH1,sinWS2,0,0,0,0,0},
F_RageOfZecram,SKILL_RAGE_OF_ZECRAM,SIN_SKILL_USE_RIGHT,R_Zecram_UseMana},

{"컨센트레이션",	"고도의 집중력을 발휘하여 일정시간동안 명중력을 상승시킨다",
40,		53,2,		110,3,
{0,0,0},			{sinWA1,sinWS2,0,0,0,0,0,0},
F_Concentration,SKILL_CONCENTRATION,SIN_SKILL_USE_RIGHT,Concentration_UseMana},

{"어벤징 크래쉬",	"복수의 불타는 강력한 연타 공격으로 막대한 피해를 입힌다",
43,		48,2,		73,3,
{0,0,0},			{sinWA1,sinWP1,sinWS2,0,0,0,0,0},
F_Avanging_Crash,SKILL_AVANGING_CRASH,SIN_SKILL_USE_RIGHT,A_Crash_UseMana},

{"스위프트 엑스",	"도끼의 사용을 능숙하게 하여 일정시간동안 공격속도를 향상시킨다",
46,		53,2,		200,3,
{0,0,0},			{sinWA1,0,0,0,0,0,0,0},
F_Swift_Axe,SKILL_SWIFT_AXE,SIN_SKILL_USE_RIGHT,Swift_Axe_UseMana},

{"본 크래쉬",		"고대인들이 디먼을 물리치던 기술로 강력한 회전 연타를 가한다",
50,		54,2,		73,3,
{0,0,0},			{sinWA1,sinWP1,sinWS2,0,0,0,0,0},
F_Bone_Crash,SKILL_BONE_CRASH,SIN_SKILL_USE_RIGHT,B_Crash_UseMana},

//[파이터]4차 스킬
{"디스트로이어",	"적을 파멸시키는 강력한 연타공격을 가한다.",
60,		45,2,		150,0,
{1,0,0},			{sinWA1,sinWH1,0,0,0,0,0,0},
F_Destoryer,SKILL_DETORYER,SIN_SKILL_USE_ALL,Destoryer_UseMana},

{"버서커",		"스스로를 통제 할수 없을 정도로 광폭한 상태로 돌변한다.하지만 흡수력이 극도로 하락한다",
63,		60,2,		700,0,
{1,0,0},			{0,0,0,0,0,0,0,0},
F_Berserker,SKILL_BERSERKER,SIN_SKILL_USE_RIGHT,Berserker_UseMana},

{"싸이클론 스트라이크",	"강력한 회전공격으로 다수의 적을 타격한다.",
66,		55,2,		135,0,
{1,0,0},			{sinWA1,sinWH1,sinWP1,sinWS2,0,0,0,0},
F_Cyclone_Strike,SKILL_CYCLONE_STRIKE,SIN_SKILL_USE_RIGHT,Cyclone_Strike_UseMana},

{"부스트 헬스",	"생명력을 영구적으로 증가 시킨다.",
70,		0,0,		0,0,
{1,0,0},			{0,0,0,0,0,0,0,0},
F_Boost_Health,SKILL_BOOST_HEALTH,SIN_SKILL_USE_NOT,},

//파이크맨 
{"파이크 윈드",			"창을 강하게 돌려 만든 바람으로 적을 밀어내며 공격한다",
10,		27,2,		80,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0},
F_Pike_Wind,SKILL_PIKE_WIND,SIN_SKILL_USE_RIGHT,Pike_Wind_UseMana},

{"아이스 어티리븃",		"빙계에 대한 적응력을 키워 영구적으로 속성을 상승시킨다",
12,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Ice_Attribute,SKILL_ICE_ATTRIBUTE,SIN_SKILL_USE_NOT,0},

{"크리티컬 힛",			"적의 치명적인 부분을 연타하여 크리티컬 공격이 될 확률을 상승시킨다",
14,		31,2,		84,3,
{0,0,0},			{sinWP1,sinWC1,sinWH1,sinWS2,0,0,0,0},
F_Critical_Hit,SKILL_CRITICAL_HIT,SIN_SKILL_USE_ALL,Critical_Hit_UseMana},

{"점핑 크래쉬",			"높은 점프로 뛰어 올라 적에게 강력한 일격을 가한다",
17,		34,2,		76,4,
{0,0,0},			{sinWA1,sinWP1,sinWS2,0,0,0,0,0},
F_Jumping_Crash,SKILL_JUMPING_CRASH,SIN_SKILL_USE_ALL,Jumping_Crash_UseMana},

{"그라운드 파이크",		"무기를 강하게 내리 쳐서 빙계의 강력한 공격을 한다",
20,		36,2,		84,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0},
F_Ground_Pike,SKILL_GROUND_PIKE,SIN_SKILL_USE_RIGHT,G_Pike_UseMana},

{"토네이도",			"근접한 적들에게 강한 회전 공격을 가한다",
23,		38,2,		83,4,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0},
F_Tornado_Pike,SKILL_TORNADO,SIN_SKILL_USE_RIGHT,Tornado_UseMana},

{"웨펀 디펜스 마스터리",	"양손 무기로 교전시 무기를 이용한 방어 능력을 영구적으로 상승시킨다.",
26,		0,0,		0,0,
{0,0,0},			{sinWA1,sinWH1,sinWP1,sinWS2,0,0,0,0},
F_Weapone_Defence_Mastery,SKILL_WEAPONE_DEFENCE_MASTERY,SIN_SKILL_USE_NOT,0},

{"익스팬션",			"무기와 기를 결합하여 거대화 한 후 관통 공격을 가한다",
30,		42,2,		82,4,
{0,0,0},			{sinWA1,sinWH1,sinWP1,0,0,0,0,0},
F_Expansion,SKILL_EXPANSION,SIN_SKILL_USE_ALL,Expansion_UseMana},

{"베놈 스피어",			"강한 정신력으로 창을 바닥에 찍어 다수의 적에 대해 독속성의 공격을 가한다.",
40,		50,2,		110,2,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0},
F_Venom_Spear,SKILL_VENOM_SPEAR,SIN_SKILL_USE_RIGHT,VenomSpear_UseMana},

{"배니쉬",			"스스로의 모습을 흐리게 하여 적이 정상적으로 인지하지 못하게 한다.",
43,		53,2,		140,2,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Vanish,SKILL_VANISH,SIN_SKILL_USE_RIGHT,Vanish_UseMana},

{"크리티컬 마스터리",		"창을 사용함에 있어 크리티컬 공격이 될 확률을 영구적으로 상승 시켜준다",
46,		0,0,		0,0,
{0,0,0},			{sinWP1,0,0,0,0,0,0,0},
F_Critical_Mastery,SKILL_CRITICAL_MASTERY,SIN_SKILL_USE_NOT,0},

{"채인 랜스",	  		  "강력하고 치명적인 회전 연속 공격을 가한다",
50,		51,2,		88,3,
{0,0,0},			{sinWC1,sinWP1,sinWS2,0,0,0,0,0},
F_Chain_Lance,SKILL_CHAIN_LANCE,SIN_SKILL_USE_RIGHT,Chain_Lance_UseMana},

//[파이크맨]4차 스킬
{"어쌔신 아이",		"몬스터의 약점을 파악하여, 크리티컬 공격이 발생될 확률을 올려준다.",
60,		61,2,		520,0,
{1,0,0},			{sinWP1,0,0,0,0,0,0,0},
F_Assassin_Eye,SKILL_ASSASSIN_EYE,SIN_SKILL_USE_RIGHT,Assassin_Eye_UseMana},

{"차징 스트라이크",	 "기를 모아 치명적인 연속공격을 가한다.",
63,		75,2,		150,0,
{1,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0},
F_Charging_Strike,SKILL_CHARGING_STRIKE,SIN_SKILL_USE_RIGHT,Charging_Strike_UseMana},

{"베이그",		"자신의 형체를 알아보기 힘들게 하여 회피력을 향상 시킨다.",
66,		71,2,		650,0,
{1,0,0},			{sinWP1,0,0,0,0,0,0,0},
F_Vague,SKILL_VAGUE,SIN_SKILL_USE_RIGHT,Vague_UseMana},

{"쉐도우 마스터",	"매우 빠른 속도의 연속적인 공격을 가한다.",
70,		51,2,		160,0,
{1,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0},
F_Shadow_Master,SKILL_SHADOW_MASTER,SIN_SKILL_USE_RIGHT,Shadow_Master_UseMana},



//아쳐 
{"스카웃 호크",			"고도의 정신력과 자연의 힘으로 만들어진 매를 소환, 시야를 확보해 일정 시간 명중력을 상승시킨다",
10,		25,2,		115,5,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Scout_Hawk ,SKILL_SCOUT_HAWK,SIN_SKILL_USE_RIGHT,Scout_Hawk_UseMana },

{"슈팅 마스터리",		"활계열 무기에 대한 훈련으로 공격력을 영구적으로 상승시킨다",
12,		0,0,		0,0,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Shooting_Mastery,SKILL_SHOOTING_MASTERY,SIN_SKILL_USE_NOT,0},

{"윈드 애로우",			"바람과 같이 빠른 활을 발사하여 공격력을 상승시킨다",
14,		25,2,		82,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Wind_Arrow,SKILL_WIND_ARROW,SIN_SKILL_USE_ALL,Wind_Arrow_UseMana},

{"퍼펙트 에임",			"정교한 공격으로 명중력과 공격력을 상승시켜 적을 정확하게 타격한다",
17,		29,2,		81,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Perfect_Aim,SKILL_PERFECT_AIM,SIN_SKILL_USE_ALL,Perfect_Aim_UseMana},


{"디온스 아이",			"전설적인 궁수 디온처럼 무기의 명중력을 극대화 시킨다",
20,		0,0,		0,0,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Dions_Eye,SKILL_DIONS_EYE,SIN_SKILL_USE_NOT,0},

{"스피릿 팰컨",			"강력한 기로 만들어진 공격성향의 매를 소환한다",
23,		36,2,		115,4,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Falcon ,SKILL_FALCON,SIN_SKILL_USE_RIGHT,Falcon_UseMana },

{"애로우 of 레이지",		"하늘로 활을 쏴 올려 지정된 위치로 산발적인 공격을 가한다",
26,		38,2,		82,4,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Arrow_of_Rage,SKILL_ARROW_OF_RAGE,SIN_SKILL_USE_RIGHT,A_Rage_UseMana},

{"애벌랜츠",			"지정한 적에게 집중적으로 화살을 발사한다",
30,		41,2,		103,2,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Avalanche,SKILL_AVALANCHE,SIN_SKILL_USE_RIGHT,Avalanche_UseMana},

{"엘레멘탈 샷",		"원소와 결합된 강력하고 빠른 화살을 발사한다.",
40,		43,2,		82,2,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_E_Shot,SKILL_ELEMENTAL_SHOT,SIN_SKILL_USE_RIGHT,Elemental_Shot_UseMana},

{"골덴 팰컨",		"공격과 치유의 능력을 가진 더욱 진화된 팰컨을 소환한다.",
43,		52,2,		120,4,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_G_Falcon,SKILL_GOLDEN_FALCON,SIN_SKILL_USE_RIGHT,Golden_Falcon_UseMana},

{"범 샷",		"폭발성 화살을 연속으로 발사하여 넓은지역에 피해를 입힌다",
46,		46,2,		87,3,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_B_Shot,SKILL_BOMB_SHOT,SIN_SKILL_USE_RIGHT,BombShot_UseMana},

{"퍼포레이션",		"정확하고 강력한 공격으로 적을 관통하는 치명적인 공격을 가한다",
50,		48,2,		82,2,
{0,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Perforation,SKILL_PERFORATION,SIN_SKILL_USE_RIGHT,Perforation_UseMana},

//[아쳐]4차 스킬
{"리콜 울버린",		"소환자를 따르는 울버린을 소환한다.",
60,		58,2,		900,0,
{1,0,0},			{0,0,0,0,0,0,0,0},
F_Recall_Wolverin,SKILL_RECALL_WOLVERIN,SIN_SKILL_USE_RIGHT,Recall_Wolverin_UseMana},

{"이베이션 마스터리",	"적의 공격을 효과적으로 회피한다.",
63,		0,0,		0,0,
{1,0,0},			{0,0,0,0,0,0,0,0},
F_Evasion_Mastery,SKILL_EVASION_MASTERY,SIN_SKILL_USE_NOT,0},

{"피닉스  샷",		"피닉스의 기운을 담은 광범위 공격을 가한다.",
66,		55,2,		100,0,
{1,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Phoenix_Shot,SKILL_PHOENIX_SHOT,SIN_SKILL_USE_RIGHT,Phoenix_Shot_UseMana},

{"포스 오브 네이처",	"자연과 완전히 동화돼 캐릭터의 능력을 극대화 시킨다.",
70,		56,2,		900,0,
{1,0,0},			{sinWS1,0,0,0,0,0,0,0},
F_Force_Of_Nature,SKILL_FORCE_OF_NATURE,SIN_SKILL_USE_RIGHT,Force_Of_Nature_UseMana},


/*----------------------------------------------------------------------------*
*							모라이온
*-----------------------------------------------------------------------------*/	
/////// 나이트
{"소드 블레스트",		"강력한 검기를 날려 적을 공격한다.",
10,		22,2,		82,2,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0},
F_Sword_Blast,SKILL_SWORD_BLAST,SIN_SKILL_USE_ALL,Sword_Blast_UseMana},

{"홀리 바디",			"신체를 신성하게 하여 언데드계열의 공격을 흡수한다.",
12,		28,2,		110,3,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_HolyBody ,SKILL_HOLY_BODY,SIN_SKILL_USE_RIGHT,HolyBody_UseMana },

{"피지컬 트레이닝",		"강인한 훈련으로 근력을 영구적으로 증가 시킨다.",
14,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Physical_Traning,SKILL_PHYSICAL_TRANING,SIN_SKILL_USE_NOT,0},

{"더블 크래쉬",			"치명적이고 강력한 연타 공격으로 적을 제압한다.",
17,		35,2,		82,2,
{0,0,0},			{sinWA1,sinWC1,sinWS2,0,0,0,0,0},
F_Double_Crash,SKILL_DOUBLE_CRASH,SIN_SKILL_USE_RIGHT,D_Crash_UseMana},

{"홀리 벨러",			"신성한 힘을 부여하여, 파티원들과 함께 언데드 적에 대한 공격력을 강화한다.",
20,		36,2,		100,3,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Holy_Valor,SKILL_HOLY_VALOR,SIN_SKILL_USE_RIGHT,Holy_Valor_Mana},

{"브랜디쉬",			"검사의 용맹함으로 넓은 범위에 대해 강력한 일격을 가한다.",
23,		38,2,		82,2,
{0,0,0},			{sinWP1,sinWS2,0,0,0,0,0,0},
F_Brandish,SKILL_BRANDISH,SIN_SKILL_USE_ALL,Brandish_Mana},

{"피어싱",			"검투사의 강력한 검기로 여러적을 관통하는 공격을 가한다.",
26,		41,2,		82,2,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0},
F_Piercing,SKILL_PIERCING,SIN_SKILL_USE_ALL,Piercing_Mana},

{"드래스틱 스피릿",		"팔라딘의 강인한 정신력으로 일정한 시간동안 방어력을 상승 시킨다.",
30,		44,2,		100,2,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Drastic_Spirit,SKILL_DRASTIC_SPIRIT,SIN_SKILL_USE_RIGHT,Drastic_Spirit_Mana},


{"소드 마스터리",	"검에 대한 훈련으로 인해 공격능력을 영구적으로 향상 시킨다.",
40,		0,0,		0,0,
{0,0,0},			{sinWS2,0,0,0,0,0,0,0},
F_S_Mastery,SKILL_SWORD_MASTERY,SIN_SKILL_USE_NOT,0},

{"디바인 쉴드",		"신성 방패를 만들어 성능을 향상시킨 후 언데드 적의 공격을 흡수하여 자신의 생명으로 환원시킨다.",
43,		46,2,		130,1,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0},
F_D_Inhalation,SKILL_DIVINE_INHALATION,SIN_SKILL_USE_RIGHT,D_Inhalation_UseMana},

{"홀리 인켄테이션",	"신성한 주문을 외워 언데드 몬스터를 현혹한다.",
46,		50,2,		120,1,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Holy_Incantation,SKILL_HOLY_INCANTATION,SIN_SKILL_USE_RIGHT,H_Incantation_UseMana},

{"그랜드 크로스",	"성기사의 이름으로 신을 대신하는 연타를 가한다.",
50,		45,2,		82,2,
{0,0,0},			{sinWH1,sinWS2,0,0,0,0,0,0},
F_Grand_Cross,SKILL_GRAND_CROSS,SIN_SKILL_USE_RIGHT,Grand_Cross_UseMana},

//[나이트]4차 스킬
{"디바인 피어싱",	"신의 힘을 받아 강력한 검무로 적을 공격한다.",
70,		51,2,		160,0,
{1,0,0},			{sinWS2,0,0,0,0,0,0,0},
F_Divine_Piercing,SKILL_DIVINE_PIERCING,SIN_SKILL_USE_RIGHT,Divine_Piercing_UseMana},

{"가들리 쉴드",	"신에게 은총받은 신성한 방패를 생성한다.",
63,		50,2,		400,0,
{1,0,0},			{sinDS1,0,0,0,0,0,0,0},
F_Godly_Shield,SKILL_GODLY_SHIELD,SIN_SKILL_USE_RIGHT,Godly_Shield_UseMana},

{"갓스 블레스",	"신의 은총으로 성스러운 힘을 받아 성기사 최고의 위력을 발휘한다.",
66,		51,2,		330,0,
{1,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS2,sinWS1,sinWT1,0},
F_God_Bless,SKILL_GOD_BLESS,SIN_SKILL_USE_RIGHT,God_Bless_UseMana},

{"소드 오브 저스티스",	"성스럽고 거대한 일격을 가한다.",
60,		53,2,		250,0,
{1,0,0},			{sinWS2,0,0,0,0,0,0,0},
F_Sword_Of_Justice,SKILL_SWORD_OF_JUSTICE,SIN_SKILL_USE_RIGHT,Sword_Of_Justice_UseMana},
/////////// 아탈란타
{"쉴드 스트라이크",		"방패를 던져 적을 관통하는 스턴형 공격을 가한다.",
10,		23,2,		82,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0},
F_S_Strike ,SKILL_SHIELD_STRIKE,SIN_SKILL_USE_RIGHT,S_Strike_UseMana },

{"퍼리너",			"잔상을 날리는 빠른창을 투척한다",
12,		26,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Farina,SKILL_FARINA,SIN_SKILL_USE_ALL,Farina_UseMana},

{"쓰로잉 마스터리",		"투창계열 무기에 대한 훈련으로 공격력을 영구적으로 상승시킨다.",
14,		0,0,		0,0,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_D_Mastery,SKILL_THROWING_MASTERY,SIN_SKILL_USE_NOT,0},

{"비거 스피어",			"투창에 기를 부여해 공격한다.",
17,		32,2,		82,2,
{0,0,0},			{sinWP1,sinWT1,0,0,0,0,0,0},
F_V_Spear,SKILL_VIGOR_SPEAR,SIN_SKILL_USE_ALL,V_Spear_UseMana},

{"윈디",			"투창을 바람처럼 가볍게 만들어 정확하고 멀리 공격할 수 있도록 한다.",
20,		34,2,		100,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Windy,SKILL_WINDY,SIN_SKILL_USE_RIGHT,Windy_Mana},

{"트위스트 재블린",		"투창을 강하게 회전시켜 정확하고 강력한 공격을 가한다.",
23,		36,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Twist_Javelin,SKILL_TWIST_JAVELIN,SIN_SKILL_USE_RIGHT,Twist_Javelin_Mana},

{"쏘울 썩커",			"방패와 쉘텀의 힘으로 적의 생명력을 흡수해 버린다.",
26,		42,2,		110,2,
{0,0,0},			{sinDS1,0,0,0,0,0,0,0},
F_Soul_Sucker,SKILL_SOUL_SUCKER,SIN_SKILL_USE_RIGHT,Soul_Sucker_Mana},

{"파이어 재블린",		"불의 속성을 추가한 투창으로 적을 불태운다.",
30,		40,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Fire_Javelin,SKILL_FIRE_JAVELIN,SIN_SKILL_USE_ALL,Fire_Javelin_Mana},

{"스플릿 재블린",	"매우 빠른 속도의 산발적인 연속 공격을 가한다.",
40,		43,2,		115,1,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Split_Javelin,SKILL_SPLIT_JAVELIN,SIN_SKILL_USE_RIGHT,Split_Javelin_UseMana},

{"트라이엄프 오브 발할라",	"강력한 기합으로 자신이나 아군의 사기를 올려 공격력을 향상 시켜준다.",
43,		50,2,		120,1,
{0,0,0},			{sinWT1,sinWS2,sinWS1,sinWP1,sinWH1,sinWA1,sinWC1,sinWM1},
F_T_Of_Valhalla,SKILL_TRIUMPH_OF_VALHALLA,SIN_SKILL_USE_RIGHT,T_Of_Valhalla_UseMana},

{"라이트닝 재블린",	"강력한 뢰 속성의 투창으로 적을 공격한다.",
46,		46,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Lightning_Javelin,SKILL_LIGHTNING_JAVELIN,SIN_SKILL_USE_ALL,Lightning_Javelin_UseMana},

{"스톰 재블린",	    "강한 폭풍을 일으키는 창을 연속적으로 투척한다.",
50,		48,2,		82,2,
{0,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Storm_Javelin,SKILL_STORM_JAVELIN,SIN_SKILL_USE_RIGHT,Storm_Javelin_UseMana},

//[아틀란타]4차 스킬
{"홀 오브 발할라",	"발할라의 기운이 회피능력을 증가 시킨다.",
60,		52,2,		750,0,
{1,0,0},			{sinWA1,sinWC1,sinWH1,sinWP1,sinWS1,sinWT1,0,0},
F_Hall_Of_Valhalla,SKILL_HALL_OF_VALHALLA,SIN_SKILL_USE_RIGHT,Hall_Of_Valhalla_UseMana},

{"익스트림 레이지",	"높이 뛰어 올라 분노의 기운을 담아 적진을 향해 강력한 공격을 가한다.",
63,		48,2,		210,0,
{1,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_X_Rage,SKILL_X_RAGE,SIN_SKILL_USE_RIGHT,X_Rage_UseMana},

{"프로스트 재블린",	"투창 사용시 일정시간동안 얼음 속성 능력을 부여한다.",
66,		50,2,		720,0,
{1,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Frost_Javelin,SKILL_FROST_JAVELIN,SIN_SKILL_USE_RIGHT,Frost_Javelin_UseMana},

{"벤젼스",	"빠르고 날렵한 연속공격을 가한다.", // 장별 - 스킬밸런스 조정(10.08.10) 55 -> 45
70,		45,2,		100,0,
{1,0,0},			{sinWT1,0,0,0,0,0,0,0},
F_Vengeance,SKILL_VENGEANCE,SIN_SKILL_USE_RIGHT,Vengeance_UseMana},

///////////프리스티스
{"힐링",			"신성한 마법으로 생명력을 회복 시켜준다.",
10,		15,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Healing,SKILL_HEALING,SIN_SKILL_USE_RIGHT,Healing_UseMana},

{"홀리 볼트",			"신성한 기 덩어리를 발사한다. (언데드 적에게 100% 가중되며, 정신력에 비례하여 공격력 증가)",
12,		11,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_HolyBolt,SKILL_HOLY_BOLT,SIN_SKILL_USE_ALL,HolyBolt_UseMana},

{"멀티 스파크",			"마법으로 만들어진 조각들을 날려 공격한다.",
14,		14,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_M_Spark,SKILL_MULTISPARK,SIN_SKILL_USE_RIGHT,M_Spark_UseMana},

{"홀리 마인드",			"신성한 기도로 적의 공격력을 약화시킨다.",
17,		19,1,		100,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_HolyMind,SKILL_HOLY_MIND,SIN_SKILL_USE_RIGHT,HolyMind_UseMana},

{"메디테이션",			"참선을 통해 기력 회복 능력을 영구적으로 향상 시킨다.",
20,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Meditation,SKILL_MEDITATION,SIN_SKILL_USE_NOT,0},

{"디바인 라이트닝",		"신성한 번개가 소환되어 적들의 머리위에 작렬한다. (정신력에 비례하여 공격력 증가)",
23,		21,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Divine_Lightning,SKILL_DIVINE_LIGHTNING,SIN_SKILL_USE_RIGHT,Divine_Lightning_Mana},

{"홀리 리플렉션",		"신성한 방어막을 형성하여, 언데드의 공격을 역 이용한다.",
26,		23,1,		120,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Holy_Reflection,SKILL_HOLY_REFLECTION,SIN_SKILL_USE_RIGHT,Holy_Reflection_Mana},

{"그랜드 힐링",			"신의 은총으로 파티원들의 생명력을 회복시켜 준다.",
30,		27,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Grand_Healing,SKILL_GRAND_HEALING,SIN_SKILL_USE_RIGHT,Grand_Healing_Mana},

{"비거 볼",			"강한 정신력으로 만든 마법의 덩어리를 연속적으로 발사한다.",
40,		24,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Vigor_Ball,SKILL_VIGOR_BALL,SIN_SKILL_USE_ALL,Vigor_Ball_UseMana},

{"레저렉션",		"성자의 힘으로 사망한 동료를 소생시킨다.",
43,		31,1,		130,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Resurrection,SKILL_RESURRECTION,SIN_SKILL_USE_RIGHT,Resurrection_UseMana},

{"익스팅션",		"성스러운 주문으로 언데드 몬스터의 생명의 일부를 완전히 소멸시킨다.",
46,		28,1,		120,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Extinction,SKILL_EXTINCTION,SIN_SKILL_USE_RIGHT,Extinction_UseMana},

{"버츄얼 라이프",	"신의 은총으로 생명력을 일시적으로 상승 시켜준다.",
50,		31,1,		134,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Virtual_Life,SKILL_VIRTUAL_LIFE,SIN_SKILL_USE_RIGHT,Virtual_Life_UseMana},

//[프리스티스]4차 스킬
{"글레셜 스파이크",	"거대한 얼음 결정들이 적진을 향해 치솟아 올라 커다란 피해를 가한다.",
60,		35,1,		120,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Glacial_Spike,SKILL_GLACIAL_SPIKE,SIN_SKILL_USE_RIGHT,Glacial_Spike_UseMana},

{"리제너레이션 필드",	"신성한 기도로 생명력과 기력을 재생하며, 주변에 있는 자들은 50% 회복시켜 준다.",
63,		41,1,		950,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Regeneration_Field,SKILL_REGENERATION_FIELD,SIN_SKILL_USE_RIGHT,Regeneration_Field_UseMana},

{"체인 라이트닝",	"적들을 연결하여 공격하는 강력한 번개 공격을 가한다.",
66,		41,1,		120,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Chain_Lightning,SKILL_CHAIN_LIGHTNING,SIN_SKILL_USE_RIGHT,Chain_Lightning_UseMana},

{"서몬 무스펠",		"신계의 수호자를 소환한다.",
70,		47,1,		800,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Summon_Muspell,SKILL_SUMMON_MUSPELL,SIN_SKILL_USE_RIGHT,Summon_Muspell_UseMana},


///////////매지션
{"애거니",			"스스로의 신체를 희생하여 기력을 증가시킨다.",
10,		12,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Agony,SKILL_AGONY,SIN_SKILL_USE_RIGHT,Agony_UseMana},

{"파이어 볼트",			"마법으로 생성된 작은 불덩어리로 적을 공격한다.",
12,		11,1,		84,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_FireBolt,SKILL_FIRE_BOLT,SIN_SKILL_USE_ALL,FireBolt_UseMana},

{"제니쓰",			"강력한 정신력으로 일정 시간동안 원소속성을 상승시킨다.",
14,		15,1,		100,3,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Zenith,SKILL_ZENITH,SIN_SKILL_USE_RIGHT,Zenith_UseMana},

{"파이어 볼",			"강력한 마법의 불덩어리로 범위내의 적들을 공격한다. (정신력에 비례하여 공격력 증가)",
17,		19,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_FireBall,SKILL_FIRE_BALL,SIN_SKILL_USE_RIGHT,FireBall_UseMana},

{"멘탈 마스터리",		"고대인들의 강한 정신력을 이어받는 정신적 수양으로 영구적으로 기력을 상승시킨다.",
20,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
F_Mental_Mastery,SKILL_MENTAL_MASTERY,SIN_SKILL_USE_NOT,0},

{"워토네이도",			"강력한 마법의 힘으로 물과 바람을 섞어 만든 물기둥이 적들을 강타한다. (정신력에 비례하여 공격력 증가)",
23,		21,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Watornado,SKILL_WATORNADO,SIN_SKILL_USE_RIGHT,Watornado_Mana},

{"인첸트 웨폰",			"사용하고 있는 장비에 원소의 힘을 섞어 더욱 강력한 힘을 발휘하게 한다.",
26,		28,1,		104,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Enchant_Weapon,SKILL_ENCHANT_WEAPON,SIN_SKILL_USE_RIGHT,Enchant_Weapon_Mana},

{"데쓰 레이",			"손바닥에서 죽음을 부르는 빛을 발사 한다. (정신력에 비례하여 공격력 증가)",
30,		26,1,		82,2,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Dead_Ray,SKILL_DEAD_RAY,SIN_SKILL_USE_ALL,Dead_Ray_Mana},

{"에너지 쉴드",			"강한 정신 에너지로 적의 공격을 흡수하는 방어막을 만든다.",
40,		40,1,		150,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Energy_Shield,SKILL_ENERGY_SHIELD,SIN_SKILL_USE_RIGHT,Energy_Shield_UseMana},

{"디아스트로피즘",		"지각을 변동시키는 강력한 마법으로 유효 반경내의 적들에게 강력한 공격을 가한다",
43,		33,1,		106,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Diastrophism,SKILL_DIASTROPHISM,SIN_SKILL_USE_RIGHT,Diastrophism_UseMana},

{"스피릿 엘레멘탈",		"정신의 정령을 소환해 마법 공격능력을 증가시킨다",
46,		35,1,		150,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Spirit_Elemental,SKILL_SPIRIT_ELEMENTAL,SIN_SKILL_USE_RIGHT,Spirit_Elemental_UseMana},

{"댄싱 소드",			"원소의 힘을 가진 칼의 환영을 소환해 적을 공격한다",
50,		30,1,		150,1,
{0,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_D_Sword,SKILL_DANCING_SWORD,SIN_SKILL_USE_RIGHT,Dancing_Sword_UseMana},

//[메지션]4차 스킬
{"파이어 엘레멘탈",	"화염으로 만들어진 강력한 엘레멘탈을 소환한다.",
60,		120,2,		900,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Fire_Elemental,SKILL_FIRE_ELEMENTAL,SIN_SKILL_USE_RIGHT,Fire_Elemental_UseMana},

{"플레임 웨이브",	"강력한 화염을 만들어 전방의 적들을 공격 한다.",
63,		32,1,		124,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Flame_Wave,SKILL_FLAME_WAVE,SIN_SKILL_USE_RIGHT,Flame_Wave_UseMana},

{"디스토션",		"공간을 왜곡시켜 적들의 능력을 떨어뜨린다.",
66,		43,1,		460,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Distortion,SKILL_DISTORTION,SIN_SKILL_USE_RIGHT,Distortion_UseMana},

{"미티어라이트",	"우주를 헤아리는 자의 지혜로 거대한 운석들을 소환하여 적진을 강타한다.",
70,		39,1,		190,0,
{1,0,0},			{sinWM1,0,0,0,0,0,0,0},
F_Meteo,SKILL_M_METEO,SIN_SKILL_USE_RIGHT,Meteo_UseMana},

//포스 오브 테이블
{"오브",		"오브에 담겨진 힘으로 공격력을 향상시킨다",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,SKILL_FORCE_ORB,0,0},

//퀘스트 타임 테이블
{"퀘스트",		"몬스터를 사냥해오시오!",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,CHANGE_JOB3_QUEST,0,0},

//퀘스트 타임 테이블
{"퀘스트",		"몬스터를 사냥해오시오!",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,CHANGE_ELEMENTARY_QUEST,0,0},

//공성전 클랜스킬 테이블
{"앱소션 오브 글로리","일주일동안 흡수력을 +20시킨다.",	// 박재원 - 공성전 수성 클랜 스킬 상향 조정
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,CLANSKILL_ABSORB,0,0},

{"파워 서지","일주일동안 공격력를 15%상승 시킵니다.",	// 박재원 - 공성전 수성 클랜 스킬 상향 조정
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,CLANSKILL_ATTACK,0,0},

{"이베이드 어뎁트","일주일동안 Evade 될 확률을 20%증가 시킵니다.",	// 박재원 - 공성전 수성 클랜 스킬 상향 조정
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,CLANSKILL_EVASION,0,0},

//공성전 아이템 사용 스킬
{"아타나시아","일정시간 무적상태가 됨 1/2 공격력 감소",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,SCROLL_INVULNERABILITY,0,0},

{"데드리 에지","크리티컬 확률 5% 증가",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,SCROLL_CRITICAL,0,0},

{"어베일 오브 이베이드","이베이드 확률 5%증가",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,SCROLL_EVASION,0,0},

{"디파이언스 스톤","파이어 크리스탈 타워의 공격을 50% 상쇄한다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_R_FIRECRYTAL,0,0},

{"디파이언스 스톤","아이스 크리스탈 타워의 공격을 50% 상쇄한다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_R_ICECRYTAL,0,0},

{"디파이언스 스톤","라이트닝 크리스탈 타워의 공격을 50% 상쇄한다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_R_LINGHTINGCRYTAL,0,0},

{"마이트 스톤","파이터 타격시 최종공격력을 20% 가중시킨다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_A_FIGHTER,0,0},

{"마이트 스톤","메카니션 타격시 최종공격력을 20% 가중시킨다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_A_MECHANICIAN,0,0},

{"마이트 스톤","파이크맨 타격시 최종공격력을 20% 가중시킨다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_A_PIKEMAN,0,0},

{"마이트 스톤","아쳐 타격시 최종공격력을 20% 가중시킨다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_A_ARCHER,0,0},

{"마이트 스톤","나이트 타격시 최종공격력을 20% 가중시킨다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_A_KNIGHT,0,0},

{"마이트 스톤","아틀란타 타격시 최종공격력을 20% 가중시킨다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_A_ATALANTA,0,0},

{"마이트 스톤","메지션 타격시 최종공격력을 20% 가중시킨다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_A_MAGICIAN,0,0},

{"마이트 스톤","프리스티스 타격시 최종공격력을 20% 가중시킨다.",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,STONE_A_PRIESTESS,0,0},
//프리미엄 부분 유료화 아이템
{"이터널 라이프","일정시간 무적상태가 됨 1/2 공격력 감소",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,SCROLL_P_INVULNERABILITY,0,0},

{"페이틀 에지","크리티컬 확률 15% 증가",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,SCROLL_P_CRITICAL,0,0},

{"어버트 스크롤","이베이드 확률 15%증가",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,SCROLL_P_EVASION,0,0},

// 박재원 - 부스터 아이템(생명력)
{"생명력 부스터","생명력을 15% 상승시킨다",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,BOOSTER_ITEM_LIFE,0,0},

// 박재원 - 부스터 아이템(기력)
{"기력 부스터","기력을 15% 상승시킨다",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,BOOSTER_ITEM_MANA,0,0},

// 박재원 - 부스터 아이템(근력)
{"근력 부스터","근력을 15% 상승시킨다",
0,		0,0,		0,0,
{0,0,0},			{0,0,0,0,0,0,0,0},
NULL,BOOSTER_ITEM_STAMINA,0,0},

#endif

#ifdef	_LANGUAGE_CHINESE
#include "Language\\chinese\\C_sinSkill_Info.h"
#endif

#ifdef	_LANGUAGE_JAPANESE
#include "Language\\Japanese\\J_sinSkill_Info.h"
#endif

#ifdef	_LANGUAGE_TAIWAN
#include "Language\\Taiwan\\T_sinSkill_Info.h"
#endif

#ifdef	_LANGUAGE_ENGLISH
#include "Language\\English\\E_sinSkill_Info.h"
#endif

#ifdef	_LANGUAGE_THAI
#include "Language\\THAI\\TH_sinSkill_Info.h"
#endif

#ifdef _LANGUAGE_VEITNAM
#include "Language\\VEITNAM\\V_sinSkill_Info.h"
#endif

#ifdef _LANGUAGE_BRAZIL
#include "Language\\BRAZIL\\B_sinSkill_Info.h"
#endif

#ifdef _LANGUAGE_ARGENTINA
#include "Language\\ARGENTINA\\A_sinSkill_Info.h"
#endif