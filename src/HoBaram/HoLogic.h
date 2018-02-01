#ifndef _HO_LOGIC_H_
#define _HO_LOGIC_H_

/*
//고장난 무기 치료...
class HoWeaponFix : public HoEffectObject
{
public:
	HoWeaponFix();
	~HoWeaponFix();

private:	
	int	TimeCount;    //시간 카운트
	
	int CurrentBlendValue;
	int BlendStep;
	
	int VertexCount;
	int WeaponFixImage;

	int DestX;
	int DestY;
	int DestWidth;
	int DestHeight;


	int CurrentWidth, CurrentHeight;
	int WidthStep, HeightStep;
public:
	int Start(int x, int y, int sizeX, int sizeY);
	int Draw();
	int Init();

	int Main();
};
*/

/*
//Potion에 쓰는 Particle
class HoPotionParticle : public HoEffectParticle
{
public:
	HoPotionParticle();
	~HoPotionParticle();
private:
	int		LocalAngle;

public:
	int Main();
	void Init();

	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Start(int x, int y, int z, float xv, float yv, float zv, char *iniName);
};
*/

#define PAT_PROCESS		2000
#define PAT_END			3000


#define MAX_BLUR_LIST		15
#define	MAX_BLUR_VERTEX		300
#define	MAX_BLUR_FACE		200
#define	MAX_BLUR_TEXLINK	200


//직선으로 날아가는 오브젝트..
class HoEffectPatDest : public HoEffectPat
{
private:
	int Level;
	int DestX, DestY, DestZ;
	int DestAngleX, DestAngleY, DestAngleZ;
	

	float VelocityY;
	int   Step;

	HoPrimitiveBillboard PrimitiveBillBoard; //Event용 Effect Object에 덧쒸우는 이펙트..
	
	int SkillType;
	int WorkState;
	
	
	//잔상용...
	BOOL BlurStartFlag;
	POINT3D	PosList[MAX_BLUR_LIST];
	int		PosListCount;
	
	smSTAGE_VERTEX		Vertex[MAX_BLUR_VERTEX];
	int					VertexCount;
	
	smSTAGE_FACE		Face[MAX_BLUR_FACE];
	int					FaceCount;
	
	smTEXLINK			TexLink[MAX_BLUR_TEXLINK];
	int					TexLinkCount;
	int					SumCount;
	
	int					CreatePathFace();
	
	int					AniDataIndex;
	int					BlurBlendValue;//CurrentBlendValue;
	int					BlurTimeCount;
	int					BlurCurrentFrame;
	int					SizeWidth;


public:
	HoEffectPatDest();
	~HoEffectPatDest();
	
public:
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();

	//날라가는 오브젝트..
	int StartDest(POINT3D currentPos, POINT3D destPos, smPAT3D *pat, int SkillType, int level = 0);
	int StartAni(int x, int y, int z, int angleX, int angleY, int angleZ, int destX, int destY, int destZ, smPAT3D *pat, char *addEffectName = NULL);
	int EventEnd();
	

	//잔상용.
	int StartBlur(char *iniName);
	int MainBlur();
	int	DrawBlur(int x, int y, int z, int ax, int ay, int az);
};




//방어 쉴드.
#define		POS_LIST_MAX	15

#define		MAX_SHIELD_VERTEX	300
#define		MAX_SHIELD_FACE		200
#define		MAX_SHIELD_TEXLINK	200

class HoEffectShield : public HoEffectObject
{
public:
	HoEffectShield();
	~HoEffectShield();
	
	HoPrimitiveBillboard	BackBillBoard;		//Shile1에서 따라가는 동그란 빌보드..
	HoEffectPat				UnderPat;
	
	int AniDataIndex;
	int	CurrentFrame;
	int TimeCount;
	int BlendStep;
	int CurrentBlendValue;
	
	smFACE2D			Face2d;
	
	int SizeWidth;
	int SizeHeight;
	
	POINT3D DirectionAngle;	
	POINT3D	PosList[POS_LIST_MAX];
	int		PosListCount;
	
	smSTAGE_VERTEX		Vertex[MAX_SHIELD_VERTEX];
	int					VertexCount;
	
	smSTAGE_FACE		Face[MAX_SHIELD_FACE];
	int					FaceCount;
	
	smTEXLINK			TexLink[MAX_SHIELD_TEXLINK];
	int					TexLinkCount;
	
	int					SumCount;
	
	smCHAR				*Character;
	
	int					EndCount; //넘 시간이 초과 했을 경우 끝내는거.

	int					ShieldType;

	

protected:
	//BOOL AddFace2D(smFACE2D *face);
	int	CreatePathFace();
public:
	void Init();
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();
	int Start(int x, int y, int z, int shieldType, int angle, int circleRadius, smCHAR *character); 
	
	void SetUnderPat(smPAT3D *pat, int aniEnd);
};


//손에 기를 모으는 경우..
class HoEffectPower : public HoEffectObject
{
public:
	HoEffectPower();
	~HoEffectPower();

	int  Skill_n;			//ktj : Power이펙트가 여러가지 모양이라 스위치가필요해서 일부러넣음.

private:
	HoPrimitiveBillboard	BackBillBoard;			//뒤에서 가물 가물 하는 이펙트
	
	HoPrimitiveBillboard	ParticleBillBoard[10];

	smCHAR					*Character;
	int						AniDataIndex;


public:
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();					//sw=1->power1.ini 2->power2.ini
	int Start(int x, int y, int z, int sw, int aniType = ANI_ONE, smCHAR *character = NULL);
};


//struct h
//새로운 타격...(빌보드 용으로 화면에 쭉 돌아 가면서 섬광이 나오는 경우)(Tornado)
class HoEffectHitLine : public HoEffectObject
{
public:
	HoEffectHitLine();
	~HoEffectHitLine();



	//ktj : 새로넣음. ==========================start
	int  Skill_n;			//ktj : 토네이도가 여러가지 모양이라 스위치가필요해서 일부러넣음.
	int  cntM, cnt0;
	int delayCount ;		//클라스변수로이동시킴.

	
	POINT3D DestPos;		//날아갈 목적지...
	float Vx;				//속도 벡터..
	float Vy;
	float Vz;
	//ktj : 새로넣음. ==========================end


private:

	POINT3D DirectionAngle;	
	POINT3D	PosList[POS_LIST_MAX];
	int		PosListCount;
	
	smSTAGE_VERTEX		Vertex[MAX_SHIELD_VERTEX];
	int					VertexCount;
	
	smSTAGE_FACE		Face[MAX_SHIELD_FACE];
	int					FaceCount;
	
	smTEXLINK			TexLink[MAX_SHIELD_TEXLINK];
	int					TexLinkCount;
	int					SumCount;
	
	int					CreatePathFace();
	
	int					AniDataIndex;
	int					CurrentBlendValue;
	int					TimeCount;
	int					CurrentFrame;
	
	int					SizeHeight;

public:
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();
	//ktj : 원본
	//int Start(int x, int y, int z, int destX, int destY, int destZ);
	int Start(int x, int y, int z, int destX, int destY, int destZ, int sw);
};


//방어 쉴드.
#define		STUN_POS_LIST_MAX	10

//몬스터 스턴용.. (?표 돌리기)
class HoEffectStun: public HoEffectObject
{
public:
	HoEffectStun();
	~HoEffectStun();


private:
	/*
	POINT3D					RotateAngle;
	HoPrimitiveBillboard	BackBillBoard;

	smCHAR					*Character;
	*/
	POINT3D DirectionAngle;	
	POINT3D	PosList[POS_LIST_MAX];
	int		PosListCount;
	
	smSTAGE_VERTEX		Vertex[MAX_SHIELD_VERTEX];
	int					VertexCount;
	
	smSTAGE_FACE		Face[MAX_SHIELD_FACE];
	int					FaceCount;
	
	smTEXLINK			TexLink[MAX_SHIELD_TEXLINK];
	int					TexLinkCount;
	int					SumCount;
	
	int					CreatePathFace();
	
	int					AniDataIndex;
	int					CurrentBlendValue;
	int					TimeCount;
	int					CurrentFrame;
	
	int					SizeHeight;

	smCHAR				*Character;

public:
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int Main();
	int Start(int worldX, int worldY, int worldZ, smCHAR *character);
};



#endif