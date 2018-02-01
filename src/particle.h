#define PARTICLE_MAX	500

//파티클 코드
#define SMPARTICLETYPE_SHINE1		0x0001
#define SMPARTICLETYPE_BLOOD1		0x0010
#define SMPARTICLETYPE_BLOOD2		0x0011

//파티클 초기화
int InitParticle();
//파티클 추가
int SetParticle( int x, int y, int z , int MatNum , int Type , int Param=0 );
//파티클 실행
int PlayParticle();
//파티클 드로윙
int DrawParticle(int x, int y, int z, int ax, int ay, int az );


//동적 광원 초기화
int InitDynLight();
//동적 광원 닫기
int CloseDynLight();
//동적 광원 설정
int SetDynLight( int x,int y,int z, int r, int g, int b, int a, int power , int DecPower=10 );
//동적 광원 렌더러에 적용
int DynLightApply();
//동적 광원 메인
int DynLightMain();
