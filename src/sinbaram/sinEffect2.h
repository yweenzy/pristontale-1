/*----------------------------------------------------------------------------*
*	파일명 :  sinEffect2.h	
*	하는일 :  이펙트 관련 작업 (각각의 이펙트 )
*	작성일 :  최종업데이트 2002년 6월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#define SIN_MAX_EFFECT2			1000

#define SIN_EFFECT_STUN			1
#define SIN_EFFECT_ICEVIGO		2
#define SIN_EFFECT_BOSSAURA		3
#define SIN_EFFECT_BOSSAURA2	4


#define SIN_EFFECT_NO_TIME		0xFFFF0000

#define SIN_EFFECT_FACE			1
#define SIN_EFFECT_MESH			2

/*----------------------------------------------------------------------------*
*						Effect2 클래스 
*-----------------------------------------------------------------------------*/	
class cSINEFFECT2{

public:

	DWORD CODE;
	int   Time;
	int   Max_Time;
	int   Index;

public:

	//////// 좌표관련 
	POINT3D		Posi;
	POINT3D		Angle;
	POINT3D		AngleTemp;			//계산에서만 사용된다 
	POINT3D		RanderAngle;		//렌더링 Angle
	POINT3D		SortPosi;			//소팅 좌표 
	int			FaceAngleY;			//페이스 앵글Y
	POINT3D		DesPosi;			//도달할 위치 좌표(임의설정으로 구현한다)
	int			AddHeight;			

	//////// Draw 관련 
	int			Flag;				//플랙 
	smFACE2D	sinFace;			//페이스 
	smPAT3D     *sinPatMesh;		//패턴 
	smOBJ3D		*sinObj;			//오브젝트 
	int			ObjMat;				//오브젝트 메트리얼

	//////// 애니메이션 
	int			AniCount;
	int			AniTime;
	int			AniMax;
	int			AniReverseNum;		//애니메이션 역순플렉 ( 1바른차순 2 역순 ) 

	int			*lpMatAni;

	//////// Move 관련 
	int			MoveKind;
	POINT3D		MoveSpeed;
	int			Gravity;
	int			DesSpeed;			//목적지 까지의 스피드 
	POINT3D		MoveAngle;			//각도에 의해서 움직임 
	int			MoveStartTime;		
	
	//////// Roatate 관련 
	POINT3D		RotateDistance;
	int			RotateSpeed;
	int			RotateSpeedCnt;
	POINT3D		RotatePosi;
	POINT3D		CharDistance;
	int			RotateAngle;

	//////// Size관련 			
	POINT		Size;
	int			SizeIncreTime;
	int			SizeDecreTime;
	int			SizeAmount;
	int			ReSizingNum;
	int			ReSizingAmount;

	//////// Char 관련 
	smCHAR		*pChar;		//자신 
	smCHAR		*DesChar;	//상대방(몬스터)
	POINT3D		CharPosi;		//나의 위치 
	POINT3D		DesCharPosi;	//상대방의 위치 

	//////// Color 관련 
	int			Color_A;
	int			Color_R;
	int			Color_G;
	int			Color_B;
	
	int			AlphaCount;
	int			AlphaTime;
	int			AlphaAmount;

	int			AlphaReverse_A;	 //리턴 할 알파 값
	int			AlphaReverseNum; //알파 리버스 

	int			AlphaFadeInFlag;	 //알파 페이드인

	//////// Process
	int			ProcessCount;

	////////
	int			CopyFlag;
	//////// Action
	int			ActionTime[10]; //다른 액션이 있을경우 
	int			BoneFlag;		//그려지지않는 뼈대

	int			CrashCheckCount[3];
public:


};
extern POINT3D	sinPosi2;
extern POINT3D	sinAngle2;

/*----------------------------------------------------------------------------*
*						 이펙트 종류 struct
*-----------------------------------------------------------------------------*/	

//보스 몬스터 이펙트 (바닦)
int setBossMonsterEffect(smCHAR *pChar,int ProcessCount);

//보스 몬스터 이펙트2 (주위)
int setBossMonsterEffect2(POINT3D Posi);

//스턴  
int sinSetEffect_Stun(smCHAR *pChar ,int Time);

//차가운 기운 
int sinSetEffect_IceVigo(smCHAR *pChar ,  int Time);
/*----------------------------------------------------------------------------*
*						     파티클 	
*-----------------------------------------------------------------------------*/	
int sinSetParticleRound(POINT3D Posi);   //둥글게 퍼지는 이펙트 

int sinSetParticleTail(POINT3D Posi);    //꼬리쪽에서 흩날리는 파티클 

int ParticleTestKey(); //파티클 테스트 키 

int sinHitParticle(int Mat , POINT3D Posi);		//타격 파티클 

int sinTornadoParticle(int Mat , POINT3D Posi); //회오리 파티클 

int sinSparkParticle(int Mat , POINT3D Posi);   //스파크 파티클 

int sinParticleLine(int Mat , POINT3D Posi , int R ,int G , int B); //파티클 라인 

int sinGetMoveLocation2(cSINEFFECT2 *pEffect);		//이동된 좌표를 구한다 

int sinSetLightEffect(int R , int G , int B , int A , POINT3D Posi);

int sinSongPyeunEffect(POINT3D Posi); //송편 파티클 

/*----------------------------------------------------------------------------*
*					
*-----------------------------------------------------------------------------*/	

//Effect 이미지 초기화 
int InitEffect2();

//이펙트가 셋팅될 빈곳을 찾아서 Index를 리턴한다 
int sinSearchEmptyIndex();

//이펙트를 그린다 
int sinDrawEffect2(int x, int y,int z,int ax, int ay, int az);

//2D 이미지를 그린다 
int sinDrawTexture2(cSINEFFECT2 *pSinEffect2);

//오브젝트를 셋팅한다 
int sinCreateObject(cSINEFFECT2 *pEffect);

//이펙트를 움직인다 
int sinMoveEffect2(cSINEFFECT2 *pEffect);

//EFFECT ACTIVE!
int sinActiveEffect2();

//버블 소팅 
int sinBubbleSort2(cSINEFFECT2 *list, int num);

//테스트 텍스트 
int EffectTestDrawText2();

//캐릭터 정보를 이펙트에 셋팅한다 
int sinCheckCharState(cSINEFFECT2 *pEffect);

//이펙트 초기화 
int sinReleaseEffect();

//좌표를 보정해서 소팅한다 
int sinReSetObjPosi(cSINEFFECT2 *pEffect);

//이펙트 기본셋팅 
int sinEffectDefaultSet(int Index , int Kind ,  smCHAR *pChar=0 , POINT3D *pPosi=0 , int Y=0 );

//Rotate 좌표 셋팅
int sinSetRotatePosiReSet(cSINEFFECT2 *pEffect);
////////////////// TEST
int CheeseTestEffectImage(); //치즈의 테스트 이미지 

/*----------------------------------------------------------------------------*
*								Extern 
*-----------------------------------------------------------------------------*/	
extern cSINEFFECT2 cSinEffect2[SIN_MAX_EFFECT2];					//이펙트 클래스 1000개 
extern sinEFFECT_ZDEPTH sinEffect_Zdepth2[SIN_MAX_EFFECT2];		    //소팅을 위한 인덱스 구조체 


int SetDynLight( int x,int y,int z, int r, int g, int b, int a, int power , int DecPower);

//날치기 이미지 
extern int Matstun;