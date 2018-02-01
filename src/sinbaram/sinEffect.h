/*----------------------------------------------------------------------------*
*	파일명 :  sinEffect.h	
*	하는일 :  이펙트 관련 작업 
*	작성일 :  최종업데이트 2002년 6월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#define		SIN_MAX_EFFECT				1000	//이펙트 이미지 갯수의 최대치 
#define		SIN_MAX_PROCESS				100		//이펙트 프로세스 

//////// 이펙트의 TYPE
#define		SIN_EFFECT_PARTICLE			0x01000000
#define		SIN_EFFECT_FACE2D			0x02000000
#define		SIN_EFFECT_OBJECT			0x03000000
#define		SIN_EFFECT_PATMESH			0x04000000

/////// 이펙트 갯수
#define SIN_EFFECT_1					0x00000001
#define SIN_EFFECT_2					0x00000002
#define SIN_EFFECT_3					0x00000003
#define SIN_EFFECT_4					0x00000004
#define SIN_EFFECT_5					0x00000005
#define SIN_EFFECT_6					0x00000006
#define SIN_EFFECT_7					0x00000007
#define SIN_EFFECT_8					0x00000008
#define SIN_EFFECT_9					0x00000009
#define SIN_EFFECT_10					0x00000010

/////// 이펙트 마스크 

#define	sinEFFECT_MASK1	0xFF000000
#define	sinEFFECT_MASK2	0xFFFF0000
#define	sinEFFECT_MASK3	0x0000FFFF


////////종류별 이펙트

#define		SIN_PARTICLE_SPOUT			(SIN_EFFECT_PARTICLE | SIN_EFFECT_1)		//분출형
#define		SIN_PARTICLE_GATHER			(SIN_EFFECT_PARTICLE | SIN_EFFECT_2)		//모임형
#define		SIN_PARTICLE_ROTATE_RISE	(SIN_EFFECT_PARTICLE | SIN_EFFECT_3)		//회전 상승형 
#define		SIN_PARTICLE_WIDE			(SIN_EFFECT_PARTICLE | SIN_EFFECT_4)		//넓게 퍼지는형

#define		SIN_EFFECT_WIDE_LINE		(SIN_EFFECT_OBJECT | SIN_EFFECT_1)			//오브젝트 분출라인 
#define		SIN_EFFECT_RISE_LINE		(SIN_EFFECT_OBJECT | SIN_EFFECT_2)			//오브젝트 상승라인 

///////색상 별 파티클
#define		SIN_PARTICLE_COLOR_GOLD		1		//금색
#define		SIN_PARTICLE_COLOR_BLUE		2		//청색
#define		SIN_PARTICLE_COLOR_RED		3		//적색
#define		SIN_PARTICLE_COLOR_GREEN	4		//녹색

///////이펙트의 형태
#define		SIN_EFFECT_TYPE_NORMAL		1		//보통
#define		SIN_EFFECT_TYPE_FADEON		2		//파티클의 시작 (희미한상태)
#define		SIN_EFFECT_TYPE_EXPAND		3		//파티클이 커진다 
#define		SIN_EFFECT_TYPE_DECREASE	4		//파티클이 작아진다 
#define		SIN_EFFECT_TYPE_FLICKER		5		//깜빡이다
#define		SIN_EFFECT_TYPE_FADEOUT		6		//서서히 사라지다

///////이펙트의 상태
#define		SIN_EFFECT_DEAD				0		//파티클이 사라진다
#define		SIN_EFFECT_ALIVE			1		//파티클이 살아있다


/*----------------------------------------------------------------------------*
*						    이펙트 구조체 
*-----------------------------------------------------------------------------*/	
struct sinEFFECT{
	int			CODE;				//종류
	int			Color;				//색
	int			State;				//상태 
	
	smFACE2D	sinFace;			//페이스
	
	POINT3D		MoveSpeed;			//이동 속도
	POINT3D		MoveAngle;			//회전 좌표
	int			MoveGravity;		//이동 중력
	
	POINT3D		ObjectPosi;			//오브젝트의 로컬좌표 (FACE를 사용하지 않을때 쓴다)
	int			ObjectMat;			//오브젝트 메트리얼
	POINT3D		ObjectSize;			//오브젝트 사이즈 
	
	
	int			FaceAngle;			//회전각
	
	int			LifeTime;			//경과 시간 (70프레임)
	int			LifeTime_MAX;		//경과 시간 최대치

	int			AniCount;			//에니매이션 카운트
	int			ChangeSize;			//페이스의 크기를 변화시킨다

	int			RotateRadian;		//회전시 각도
	int			RotateDistance;		//회전시 축과의 거리 

	int			TypeSize;			//크기관련 타입
	int			TypeFade;			//Fade관련 타입
	smPAT3D     *sinPatMesh;		//패턴 
	smOBJ3D		*sinObj;			//오브젝트 
	
	int			MeshFlag;			//패턴 매쉬인지를 체크한다 
	
};
/*----------------------------------------------------------------------------*
*						    이펙트 표현을 위한 구조체
*-----------------------------------------------------------------------------*/	
struct sinEFFECT_PROCESS{
	int Kind;
	int Time;
	POINT3D	Posi;
	int Index[100];

};

/*----------------------------------------------------------------------------*
*						    소팅을 하기위한 구조체
*-----------------------------------------------------------------------------*/	
struct sinEFFECT_ZDEPTH{
	int		Index;
	int		ZDepth;
	
};

/*----------------------------------------------------------------------------*
*						      함수 
*-----------------------------------------------------------------------------*/	
smFACE2D sinSetFace(int Mat,int x , int y, int z, int w, int h , int R , int G , int B , int A);

//이펙트 실행 
int sinStartEffect(int Name , int x , int y, int z);

//이펙트를 셋팅한다 
int sinSetEffect(int CODE , int x, int y, int z , int Size , int Color=0 , int AngleY = 0 ); 

//이펙트 변화
int sinActiveEffect();

//애니메이션 
int sinEffectAni(sinEFFECT *pEffect);

//이펙트를 움직인다 
int sinMoveEffect(sinEFFECT *pEffect);

//이펙트를 그린다 
int sinDrawEffect(int x, int y,int z,int ax, int ay, int az);

//이펙트를 ZDepth에 따라 소팅한다 
int sinBubbleSort(sinEFFECT_ZDEPTH *list, int num);

//이펙트 Process
int sinEffectProcess();

//이펙트 Process셋팅
int sinSetEffectProcess(int Kind , int x, int y , int z);

//이펙트 Object를 생성한다 
int sinCreateEffectObject(sinEFFECT *pEffect);

//이동된 지역 좌표값을 구한다 
int sinGetMoveLocation(sinEFFECT *pEffect);

//디버그용 TEXT를 찍어준다 
int EffectTestDrawText();

////////////TEST
int TestObjectDraw(int x, int y, int z, int ax, int ay, int az );

int TestCreateEffectObject(); //임시 오브젝트를 만들어준다 
/*----------------------------------------------------------------------------*
*						   Extern
*-----------------------------------------------------------------------------*/	
extern smTEXRECT sinTexRect;
extern sinEFFECT sinEffect[SIN_MAX_EFFECT];
extern sinEFFECT_ZDEPTH	sinEffect_ZDepth[SIN_MAX_EFFECT];
