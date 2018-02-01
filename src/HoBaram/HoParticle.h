#ifndef _HO_PARTICLE_H_
#define _HO_PARTICLE_H_

#ifndef D3D_OVERLOADS
#define D3D_OVERLOADS
#endif


//계속 생성 되어야 하는 파티클들에 대한 정리...(불, 먼지, 피등) 
#define MAX_PARTICLES	200
#define RANDOM_NUM	(((FLOAT)rand()-(FLOAT)rand())/RAND_MAX)

#define MIN_SPEED		0.0f	// unit/초    (한프레임)
#define MIN_LIFETIME	0.1f	// 최소 생명. (초단위)
#define MIN_SIZE		2.0f	// Particle의 최소 크기.

#define MIN_SPREAD		0.01f	// in degrees
#define MIN_EMISSION	1.0f	// in particles / sec
#define MIN_GRAVITY		-3.0f	// as a multiple of normal gravity 
#define MIN_ALPHA		0.0f	// as a ratio 

#define MAX_SPEED		500.0f	// unit/초 (한프레임)
#define MAX_LIFETIME	10.0f	// Frame당 최고 생명(초단위)
#define MAX_SIZE		20.0f	// Particle의 최고 크기.

#define MAX_SPREAD		180.0f	// in degrees
#define MAX_EMISSION    1000.0f	// in particles / sec
#define MAX_GRAVITY		3.0f	// as a multiple of normal gravity 
#define MAX_ALPHA		255.0f	// as a ratio 


// Radnom값이 최소, 최대 범위 안에 들게 한다.
#define Clamp(x, min, max)  x = (x<min  ? min : x<max ? x : max);

enum ParticleSystemType
{
	PS_FIRE,
	PS_DUST,
	PS_BLOOD
};

class HoParticleSystem;
class HoParticle
{
public:
	HoParticle();
	~HoParticle();
public:
	D3DVECTOR		PrevLocation;	//마지막으로 업데이트된 파티클의 위치.
	D3DVECTOR		Location;		//현재의 파티클의 위치.
	
	D3DVECTOR		Velocity;		//파티클의 속도 벡터.
	
	D3DCOLORVALUE	Color;			//현재의 칼라.
	D3DCOLORVALUE	ColorDelta;     //칼라의 변화율
	
	float			Age;			//파티클의 경과된 시간..
	float			LifeTime;		//파티클이 살아있을 시간.
	
	float			Size;			//파티클의 사이즈...
	float			SizeDelta;		//파티클의 사이즈 변화율..
	
	float			Alpha;			//알파값..
	float			AlphaDelta;		//알파 변화율...

	float			Gravity;		//중력...
	float			GravityDelta;	//중력 변화율...

	float			TimeCount;
	
	HoParticleSystem*	Parent;
	void			SetParent(HoParticleSystem* parent){ Parent = parent;}

public:
	bool Main();
};


class HoParticleSystem : public HoEffectObject
{
public:
	HoParticleSystem();
	virtual ~HoParticleSystem();
	
	void SetState(BOOL startFlag) { Age = -1.0f;}
	//모든 파티클들을 갱신한다.
	virtual int	  Main();
	virtual int	  Draw(int x, int y, int z, int ax, int ay, int az);
	virtual void  Init();
			int	  Start(int x, int y, int z, int matNum, int particleCode = 0);
	void		  GetLocation(D3DVECTOR& vLocation);
	void		  TranslateWorld(int x, int y, int z);


	//ktj : MONSTER_IMP_SHOT3의경우 shadow로 찍을때 파티클이 겹치면 검게나오므로 한개만 찍히도록한것임.

	int make_pSu;
	int ParticleCode;

public:

	

	BOOL		 AutoDieFlag;		 //자동으로 시간이 되면 소멸되는 파티클...
	int			 MaterialNum;		//현재 사용하는 파티클의 Texture(번호)
	
	unsigned int ParticlesAlive;	//파티클이 살아 있는지..
	unsigned int ParticlesPerSec;	//파티클 초당 뿌리는 갯수...

	D3DVECTOR	 PrevLocation;		//파티클의 이전 위치
	D3DVECTOR	 Location;			//파티클의 현재 위치

	D3DVECTOR	 Velocity;			//파티클의 속도
	D3DVECTOR    Direction;			//파티클의 방향..

	//Var들은 값을 더 주고 싶을 때 쓰면 된다.(기본적으로는 0이다)
	float	GravityStart;			//중력 시작값.
	float	GravityEnd;

	float	SizeStart;				//사이즈 시작값.
	float	SizeEnd;

	float   AlphaStart;				//알파 시작값.
	float	AlphaEnd;
	
	D3DCOLORVALUE	ColorStart;		//칼라 스타트 값.
	D3DCOLORVALUE	ColorEnd;
	
	//파티클이 튀는 방향을 렌덤하게....(파티클을 생성할 때 필요한 루틴)..
	float	Theta;
	float	Speed;				//파티클이 조금씩 흔들린다...
	float	Life;				//파티클이 살아 있는 시간...

	float	EmissionResidue;	//파티클을 좀더 뿌리고 싶을 때 사용하는 변수...
	float	Age;				//파티클 시스템이 살아 있을 시간..
	
	float	TimeCount;
	HoParticle Particles[MAX_PARTICLES];
	smFACE2D			Face2d;
};


class HoParticleBow : public HoParticleSystem
{
public:
	HoParticleBow();
	~HoParticleBow();
	
	int Main();
	int Start(int x, int y, int z, int r, int g, int b, int a, int matNum);
	int StartFire(int x, int y, int z, int r, int g, int b, int a, int matNum);

};

//PikeMan의 PikeWind에 쓰는 기술... 현재는 위로 올라가는것만 됨..
class HoParticleTornado : public HoParticleSystem
{
public:
	int LocalAngle;
	HoParticleTornado();
	~HoParticleTornado();

	int Main();
	int Start(int originX, int originY, int originZ, int localX, int localY, int localZ, int matNum);
};


//어떤 지점으로 날아 가는 파티클.. (시작 지점과 끝 지점을 세팅하면 시작 지점에서 끝지점까지
//                                  파티클을 뿌리며 날아 간다.)
class HoParticleDest : public HoParticleSystem
{
public:
	int DestX, DestY, DestZ;
	int LocalAngle;
	BOOL EndWaveFlag;
	HoParticleDest();
	~HoParticleDest();
	
	int Main();
	void SetAge(float age) { Age = age;}
	int Start(int worldX, int worldY, int worldZ, int destX, int destY, int destZ, int matNum, int type);
	
};

class HoParticleSpark : public HoParticleSystem
{
public:
	HoParticleSpark();
	~HoParticleSpark();
	void  Init();
	//int   Main();
	int   Draw(int x, int y, int z, int ax, int ay, int az);
	
	bool AddFace2D( smFACE2D *face, int particleIndex);

	//void SetMaterialNum(int matNum);
	void Start(int x, int y, int z, int matNum, int type);

};



#endif