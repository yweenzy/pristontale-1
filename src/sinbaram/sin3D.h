/*----------------------------------------------------------------------------*
*	파일명 :  sin3D.h	
*	하는일 :  3D관련 작업을 한다 
*	작성일 :  최종업데이트 2002년 1월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

////////////////////DEFINE
#define SIN_EFFECT_RAGE_OF_SINBARAM			100	//레이지 오브 신바람 


#define SIN_RAND_1000000  (rand()%1000000) 
#define SIN_RAND_100000   (rand()%100000) 
#define SIN_RAND_10000    (rand()%10000) 
#define SIN_RAND_1000     (rand()%1000) 
#define SIN_RAND_100      (rand()%100) 
#define SIN_RAND_10       (rand()%10) 


/////////////////////신바람 3D
class cSIN3D{

public:
	int sinEffect2D_Line;		//파티클 메트리얼 
	int MatParticleRed[4];		//파티클 레드
	int MatParticleBlue[4];		//파티클 블루
	int MatParticleGreen[4];	//파티클 그린
	int	MatParticleGold[4];		//파티클 금가루 
	int	MatEffectLine;			//라인형 이펙트 

	int MatParticle1;			//그냥 파티클 
	

	////////////2D이펙트 
	int	MatWideCircle;			//넓게 퍼지는원 
	

	////////////모델링 데이타 
	smPAT3D     *Rage_Of_SinBaRam;


public:

	cSIN3D();
	~cSIN3D();

	void Init(); //클래스 초기화
	void Load();
	void Release();
	void Draw(int x, int y,int z,int ax, int ay, int az);		//호이펙트 그리기);
	void DrawText();
	void Close();//클래스 종료 
	void Main();
	void LButtonDown(int x , int y);
	void LButtonUp(int x , int y);
	void RButtonDown(int x , int y);
	void RButtonUp(int x, int y);
	void KeyDown(); 

	//////////////////////////3D관련 함수
	//이펙트 그리기 
	int sinDrawTexture(int x ,int y, int z , int AngleX, int AngleY ,int AngleZ , smFACE2D *lpFace,int sinAngle);

};

extern cSIN3D cSin3D;