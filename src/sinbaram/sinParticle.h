/*----------------------------------------------------------------------------*
*	파일명 :  sinParticle.h	
*	하는일 :  이펙트 관련 작업 
*	작성일 :  최종업데이트 2002년 6월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/

#define SIN_MAX_INTER_EFFECT		300

#define SIN_INTER_EFFECT_AGING				1		//에이징과 믹스시의 이펙트 
#define SIN_INTER_EFFECT_AGING2				2		//에이징과 믹스시의 이펙트 
#define SIN_INTER_EFFECT_AGING_SUCCESS		3		//성공이펙트 
/*----------------------------------------------------------------------------*
*						   인터페이스 이펙트 구조체 
*-----------------------------------------------------------------------------*/	
struct sINTER_EFFECT{
	smFACE2D Face;
	int Time;
	int Max_Time;
	POINT Speed;
	POINT Speed2;		//왕 날치기 순 개판 짜잔!
	int Direction;
	int AniCount;
	int AniKeyFlag;		//하하하 범상치않은 이름이로다 
	int AniKeyFlag2;	//오호! 이거또한 범상치 않구나 얼씨구 지화자
	int FadeType;
	int Kind;			//이펙트 종류
	int Gravity;		//중력 

	///// 움직임 방향 

};
/*----------------------------------------------------------------------------*
*						   날치기 구조체 
*-----------------------------------------------------------------------------*/	
struct sINTER_EFFECT3{
	DIRECTDRAWSURFACE lpSuccessEffectAging;
	int Flag;
	int x;
	int y;

	int w;
	int h;

	int MoveX;
	int MoveY;

	int MoveX2;
	int MoveY2;

	int Speed;


};


/*----------------------------------------------------------------------------*
*						          함수 
*-----------------------------------------------------------------------------*/	
int sinSetParticle(int Kind ,int Color ,  int x , int y, int z);


/*----------------------------------------------------------------------------*
*						      인터 페이스 파티클    
*-----------------------------------------------------------------------------*/	
 //이미지를 로드한다 
int InitInterEffect();

//에이징 이펙트를 셋팅한다
int SetInterEffectAging();

//에이징 이펙트 투!!
int SetInterEffectAging2();

//인터페이스 이펙트를 움직인다 
int sinActiveInterEffect();

//인터페이스 이펙트를 그린다 
int sinDrawInterEffect();

//인터페이스 이펙트 프로세스 순 날치기 음하하하 
int InterEffectAging2Process();

//믹스, 에이징 성공 이펙트 
int sinSuccessCraftEffect();

//믹스, 에이징 성공 이펙트 2
int sinSuccessCraftEffect2();

//성공이펙트 2를 움직인다 
int MoveSuccessCraftEffect2();

//성공 이펙트 2를 그린다 
int DrawSuccessCraftEffect2();

//퍼즐 이펙트
int SetPuzzleEffect(int x , int y);

// pluto 제련 이펙트를 셋팅한다
int SetInterEffectSmelting();

// pluto 제작 이펙트를 셋팅한다
int SetInterEffectManufacture();

int SetInterEffectMixtureReset();	// 석지용 - 믹스쳐 리셋 창의 첫번재 이펙트 세팅

/*----------------------------------------------------------------------------*
*						          Extern 
*-----------------------------------------------------------------------------*/	
extern int   StartInterEffectAging2; //이펙트의 시작을 알린다 
extern int   sinCraftItemStartFlag;
extern int   sinCraftItemStartFlag2;


extern int  sinAgingSuccessFlag2;    //에이징과 믹스쳐의 성공 플렉 
extern DWORD InitCancelMixTime;