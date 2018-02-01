/*----------------------------------------------------------------------------*
*	파일명 :  AssaEffect
*	하는일 :  이펙트 
*	작성일 :  최종업데이트 2002년 11월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#ifndef _ASSAEFFECT_HEADER_

#define _ASSAEFFECT_HEADER_

#define cASSAEFFECT_MAX		5000

//////////////////// 셋팅옵션 
#define ASSA_ROTATE				0x0000000F //회전
#define ASSA_MOVE				0x000000F0 //이동
#define ASSA_ANGLE_ROTATE		0x00000F00 //각도회전
#define ASSA_CHAR_POSI			0x0000F000 //캐릭터 좌표이동에 따른 움직임 
#define ASSA_MOVE_ANGLE_SPEED	0x000F0000 //각도와 속도에 맞게 이동 
#define ASSA_DECRESIZE			0x00F00000 //사이즈가 줄어든다
#define ASSA_INCRESIZE			0x0F000000 //사이즈가 늘어난다
#define ASSA_MOVE_GATHER		0xF0000000 //모으다

//////////////////// 예외 셋팅 (8개가 넘어가기때문) 
#define ASSA_MOVE_SPREAD		0x70000000 //분출형
#define ASSA_MOVE_RANDOM_ROTATE 0x70000001 //Ball Rotate

#define ASSA_ANG_CHAR			0x00000001 //자신의 각
#define ASSA_ANG_DESCHAR		0x00000002 //상대와 자신의 각 (OBJ)
#define ASSA_ANG_BONE			0x00000003 //상대와 자신의 실제 각 
////////////////////

#define ASSAFADEOUT			0		//셋팅되지않는 기본옵션
#define ASSAFADEIN			1

////////////////////
#define ASSAFACE_BILLBOARD	0
#define ASSAFACE_WORLD		1
#define ASSAFACE_SCALE		2
#define ASSAFACE_TRACE		3


/////////////////// Type
#define ASSATYPE_CIRCLE		1


/////////////////// Particle Code
//#define ASSA_PARTICLE_WAVE			0x10000000


class cASSAEFFECT;
struct sASSACOLOR {int R; int G; int B; int A;};
struct sASSASIZE  {int SameSize; int w; int h;};

/*----------------------------------------------------------------------------*
*						  ASSAEFFECT 메인 클래스  
*-----------------------------------------------------------------------------*/	
class  cASSAEFFECT{
public:
	DWORD	MOVECODE;
	DWORD	MOVECODESUB; //코드 중복될때 잠시 사용
	DWORD   CODE;
	int		Time;		
	int		Max_Time;
	int		Bone;
	char    szFileName[128];
	int		Power;

	///////////// 종류
	smFACE2D	Face;
	smPAT3D		*PatMesh;
	int			Mat;
	smOBJ3D     *Obj;		//특정오브젝트
	///////////// 소팅
	int		Index;
	int		ZDepth;

	///////////// FACE 연결리스트 
	cASSATrace *cAssaTrace; 

	///////////// 좌표 설정
	POINT3D	Posi;			//좌표
	POINT3D	Angle;			//앵글
	POINT3D	TempPosi;		//계산에 사용되는 좌표 
	POINT3D	TempAngle;		//계산에 사용되는 앵글 
	POINT3D StartPosi;		//중심점으로부터의 시작좌표
	int		AddHeight;		//보정된 좌표
	POINT3D	DesPosi;		//설정된 위치 좌표

	///////////// 애니메이션
	int		AniCount;
	int		AniDelayTime;
	int		AniMaxCount;
	int		AniMatIndex[10];//애니메이션이 될 메트리얼 번호 인덱스 
	int		AniReverse;		//애니메이션 역순플렉 ( 1바른차순 2 역순 ) 

	///////////// 움직임
	POINT3D	MoveSpeed;
	POINT3D	MovePosi;
	int     GatherSpeed;
	int		Gravity;

	///////////// 좌표 회전
	POINT3D	RDistance;
	int		RAngle;
	int		RAngleSpeed;
	POINT3D RPosi; 
	POINT3D CenterPosi; //회전중심좌표

	///////////// Angle 회전
	POINT3D	ARotate;
	POINT3D	ARotateSpeed;
	int     FACEY;

	///////////// 캐릭터
	smCHAR	*pChar;			//자신
	smCHAR	*desChar;		//선택된 캐릭터

	///////////// 알파 블렌딩
	int		NotFadeIn;		//Fade In Fade Out 을 분류한다 
	int		NotFadeOut;		//Fade In Fade Out 을 분류한다 
	int     MaxAlphaAmount; //임의 알파값을 정한다 
	float   AlphaAmount;	
	int		AlphaStartTime;
	
	sASSACOLOR Color;
	sASSACOLOR BackUpColor;

	/////////////FACE TYPE
	int FACE_TYPE;

	///////////// 스케일
	POINT3D ScalePosi;
	POINT3D ScaleSpeed;

	int CenterFlag;

	///////////// 충돌 체크
	int		CrashFlag;

	///////////// Size
	sASSASIZE Size;
	sASSASIZE ReSize;
	///////////// Type
	int     Type;		 //원 , 네모 , 세모 , 등등의 Type 

	///////////// 액션 리스트
	int		ActionIndex[10]; //10개의 액션을 가질수있다 
	int		ActionTime[10];  //10개의 액션의 시간을 가질수있다 

	///////////// 액션 코드 
	DWORD   MOVECODE_List[10]; //코드를 바꿔준
	int     MOVECODE_Time[10];


	int     ZposiFlag;       //캐릭터 앞쪽부분에 페이스를찍을때 플렉을 세운다 
	///////////// Temp
	int		Temp[10];		 //계산등에 쓰이는 Ttemp
	float	fTemp[10];		 //계산등에 쓰이는 Ttemp


	///////////// 자신의 이펙트인지 아닌지를 체크하는 플렉
	int     MyPointerFlag;

public:
	cASSAEFFECT()
	{
		memset(this,0,sizeof(cASSAEFFECT));
		cASSATrace *pAssaTrace = new cASSATrace; //Face 연결리스트 
		cAssaTrace = pAssaTrace;

	}
	virtual ~cASSAEFFECT()
	{
		if(cAssaTrace)delete cAssaTrace;
	}
	virtual	void Main(){}
	virtual void Draw(POINT3D *pPosi , POINT3D *pAngle){}
	
	//캐릭의 현제 상태를 체크한다 (바뀐포인다 , 죽었거나 , 마을에 들어섰을경우)
	int AssaReSetCharPointer();

};

/*----------------------------------------------------------------------------*
*						  ASSAEFFECT FACE 클래스 
*-----------------------------------------------------------------------------*/	
class cASSAFACE : public cASSAEFFECT{
public:
	
	void Main()
	{
		//기본셋
		Face.x = this->Posi.x;			//좌표 셋팅
		Face.y = this->Posi.y; 
		Face.z = this->Posi.z; 
		Face.width = this->Size.w;		//크기 셋팅 
		Face.height = this->Size.h;
		if(!Face.height){
			this->Size.h = this->Size.w;
			Face.height = Face.width; //크기보정
		}

		//////// FADE IN
		if(!MaxAlphaAmount){
			if(!NotFadeIn){
				if(Time == 1 )Face.Transparency = 0;
				AlphaStartTime = (int)((float)Max_Time/100.0f*25.5f);
				AlphaAmount = 255.0f/(float)AlphaStartTime;
				if(Time <= AlphaStartTime ){
					Face.Transparency += (int)AlphaAmount; 
					if(Face.Transparency >255)
						Face.Transparency = 255;
				}
			}
		}
		else{
			if(!NotFadeIn){
				if(Time == 1 )Face.Transparency = 0;
				AlphaStartTime = (int)((float)Max_Time/100.0f*25.5f);
				AlphaAmount = (float)MaxAlphaAmount/(float)AlphaStartTime;
				if(Time <= AlphaStartTime ){
					if(AlphaAmount < 0 ) AlphaAmount = 1;
					Face.Transparency += (int)AlphaAmount; 
					if(Face.Transparency >MaxAlphaAmount)
						Face.Transparency = MaxAlphaAmount;
				}
			}
			else{
				if(Time == 1 ) //한번만 알파값을 셋팅해준다 
					Face.Transparency = MaxAlphaAmount;
			}
		}
		
		//////// FADE OUT
		if(!NotFadeOut){
			if(!MaxAlphaAmount){
				AlphaStartTime = (int)((float)Max_Time/100.0f*25.5f);
				if((255.0f/(float)AlphaStartTime) >= 1){
					AlphaAmount = 255.0f/(float)AlphaStartTime;

				}
				if(Time > AlphaStartTime && AlphaAmount >= 1)
					Face.Transparency -= (int)AlphaAmount;
			}
			else{
				AlphaStartTime = (int)((float)Max_Time/100.0f*25.5f);
				if(((float)MaxAlphaAmount/(float)AlphaStartTime) >= 1){
					AlphaAmount = (float)MaxAlphaAmount/(float)AlphaStartTime;

				}
				if(Time > AlphaStartTime && AlphaAmount >= 1)
					Face.Transparency -= (int)AlphaAmount;

			}
		}
		//////// Animation
		if(AniReverse == 2){ //역순
			if(AniDelayTime &&  (Time % AniDelayTime) == 0 ){
				AniCount--;
				if(AniCount < 1){
					if(	AniReverse == 2)AniReverse = 1;

				}
				Face.MatNum = AniMatIndex[AniCount];
			}

		}
		else{ //바른 차순
			if(Time >0  && AniDelayTime &&  (Time % AniDelayTime) == 0 ){
				Face.MatNum = AniMatIndex[AniCount];
				AniCount++;
				if(AniCount > AniMaxCount-1){
					if(	AniReverse == 1)AniReverse = 2;
					else AniCount = 0;
				}
			}
		}
		//캐릭의 현제상태를 체크해서 이펙트를 꺼준다 
		AssaReSetCharPointer();

	}
	void Draw(POINT3D *pPosi , POINT3D *pAngle)
	{
		
		if(!Face.MatNum)return;
		
		// Turn on Z-buffering
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, TRUE ); (문제가 생기는거 같아서 빼줬다)
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE );
		renderDevice.SetRenderState( D3DRENDERSTATE_ZFUNC,   D3DCMP_LESSEQUAL );
		//	lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_USEW );//TRUE );


		// null out the texture handle
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);

		// turn on dithering
		renderDevice.SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);

		// D3DFILTER_LINEAR
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR);
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR);

		renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

		renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

		renderDevice.SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		renderDevice.SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFN_LINEAR);


		smRender.Init(); //데이터 초기화 

		smMaterialGroup->smMaterial[Face.MatNum].TwoSide = TRUE; //카메라 회전과 상관없이 보이기 
			
		smRender.SetMaterialGroup(smMaterialGroup);  //읽어드린 메트리얼을 연결 
			

		//현재 찍을 Frame을 세팅한다..
		smMaterialGroup->SetMaterialAnimFrame( &smMaterial[Face.MatNum], 2);
			
		//Camera각도 입력.
		smRender.SetCameraPosi(pPosi->x, pPosi->y, pPosi->z,pAngle->x,pAngle->y,pAngle->z);

		switch(FACE_TYPE){
			case ASSAFACE_BILLBOARD:
				if(!AssaAddFace2D(&Face,ZposiFlag,FACEY))return;
			break;
			case ASSAFACE_WORLD:
				if(!AssaAddFaceWorld(&Face,&Angle))return;
			break;
			case ASSAFACE_SCALE:
				if(!AssaAddFace2DLine(&Face,&ScalePosi,CenterFlag))return;
			break;
			case ASSAFACE_TRACE:
				if(!AssaAddFaceTrace(&Face,cAssaTrace))return;
			break;
		}

		smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		smRender.RenderD3D();
	}
};

/*----------------------------------------------------------------------------*
*						  ASSAEFFECT MESH 클래스 
*-----------------------------------------------------------------------------*/	
class cASSAMESH : public cASSAEFFECT{
public:

	void Main()
	{

		//////// 프레임에 맞게 Max_Time을 정한다 
		if(!Max_Time){
			Max_Time = AniMaxCount*AniDelayTime;
		}
		if(!AniCount)AniCount=1; //프레임을 보정해준다 
		if(!AniDelayTime)AniDelayTime=1; 

		////////Animation
		if(Time > 0 && AniDelayTime &&  (Time % AniDelayTime) == 0 ){
			AniCount++;
			if(AniCount >= AniMaxCount )
				AniCount = 0;
		}


		//////// FADE IN
		if(!NotFadeIn){
			if(!MaxAlphaAmount){
				if(Time == 1 ){
					Color.A = -255;Color.R = -255;Color.G = -255;Color.B = -255;
				}
				AlphaStartTime = (int)((float)Max_Time/100.0f*25.5f);
				if(AlphaStartTime > 255 )AlphaStartTime = 255; //최대시간을 보정해준다 
				AlphaAmount = 255.0f/(float)AlphaStartTime;
				if(Time <= AlphaStartTime ){
					Color.A += (int)AlphaAmount;Color.R += (int)AlphaAmount;Color.G += (int)AlphaAmount;Color.B += (int)AlphaAmount;
					if(Color.A > 0 )Color.A = 0;
					if(Color.R > 0 )Color.R = 0;
					if(Color.G > 0 )Color.G = 0;
					if(Color.B > 0 )Color.B = 0;
				}
			}
			else{
				if(Time == 1 ){
					Color.A = -255;Color.R = -255;Color.G = -255;Color.B = -255;
				}
				AlphaStartTime = (int)((float)Max_Time/100.0f*25.5f);
				if(AlphaStartTime > MaxAlphaAmount )MaxAlphaAmount = 255; //최대시간을 보정해준다 
				AlphaAmount = (float)MaxAlphaAmount/(float)AlphaStartTime;
				if(Time <= AlphaStartTime ){
					Color.A += (int)AlphaAmount;Color.R += (int)AlphaAmount;Color.G += (int)AlphaAmount;Color.B += (int)AlphaAmount;
					if(Color.A > 0 )Color.A = 0;
					if(Color.R > 0 )Color.R = 0;
					if(Color.G > 0 )Color.G = 0;
					if(Color.B > 0 )Color.B = 0;
				}
			}
		}		
		//////// FADE OUT
		if(!NotFadeOut){
			if(!MaxAlphaAmount){
				AlphaStartTime = (int)((float)Max_Time/100.0f*25.5f);
				if(AlphaStartTime > 255 )AlphaStartTime = 255; //최대시간을 보정해준다 
				AlphaAmount = 255.0f/(float)AlphaStartTime;
				if(Time >= (Max_Time - AlphaStartTime)){
					Color.A -= (int)AlphaAmount;
					Color.R -= (int)AlphaAmount;
					Color.G -= (int)AlphaAmount;
					Color.B -= (int)AlphaAmount;
				}
			}
			else{
				AlphaStartTime = (int)((float)Max_Time/100.0f*25.5f);
				if(AlphaStartTime > MaxAlphaAmount )AlphaStartTime = MaxAlphaAmount; //최대시간을 보정해준다 
				AlphaAmount = (float)MaxAlphaAmount/(float)AlphaStartTime;
				if(Time >= (Max_Time - AlphaStartTime)){
					Color.A -= (int)AlphaAmount;
					Color.R -= (int)AlphaAmount;
					Color.G -= (int)AlphaAmount;
					Color.B -= (int)AlphaAmount;
				}
			}
		}
		//캐릭의 현제상태를 체크해서 이펙트를 꺼준다 
		AssaReSetCharPointer();

	}
	void Draw(POINT3D *pPosi , POINT3D *pAngle)
	{

		BackUpColor.R = smRender.Color_R;	//현재 랜더링값의 Color를 백업한다 
		BackUpColor.G = smRender.Color_G;
		BackUpColor.B = smRender.Color_B; 
		BackUpColor.A = smRender.Color_A;

		smRender.Color_R = Color.R;			//Color 셋팅
		smRender.Color_G = Color.G;
		smRender.Color_B = Color.B;
		smRender.Color_A = Color.A;
		if(PatMesh){
			PatMesh->Frame = AniCount*160;
			PatMesh->SetPosi(&Posi , &Angle);
			PatMesh->RenderD3D(pPosi,pAngle);
		}
		smRender.Color_R = BackUpColor.R;	//현재 랜더링값의 Color를 복구 
		smRender.Color_G = BackUpColor.G;
		smRender.Color_B = BackUpColor.B; 
		smRender.Color_A = BackUpColor.A;

	}

};

/*----------------------------------------------------------------------------*
*						  AssaEffect 기본 함수
*-----------------------------------------------------------------------------*/	
void InitAssaEffect();

void DrawAssaEffect(POINT3D *pPosi , POINT3D *pAngle);

void MainAssaEffect();

void MoveAssaEffect(cASSAEFFECT *pEffect);

void CloseAssaEffect();

void StopAssaEffect(cASSAEFFECT *pEffect);

void AssaEffectKeyDown();

/*----------------------------------------------------------------------------*
*							  Setting 함수 
*-----------------------------------------------------------------------------*/	
//AssaEffect셋팅
int  SetAssaEffect(int MaxTime , char *FileName , smCHAR *pChar , POINT3D *pPosi , int AddHeight=0 , int BlendType=0); 

//각도와 Speed에 맞게 움직인다 
int AssaGetMoveLocation(cASSAEFFECT *pEffect);			

// Angle을 셋팅한다
int AssaSetAngle(cASSAEFFECT *pEffect , int AngleKind);	 

//시작 Posi를 셋팅한다 
int AssaSetStartPosi(cASSAEFFECT *pEffect);
/*----------------------------------------------------------------------------*
*							  좌표 계산 함수 
*-----------------------------------------------------------------------------*/	
//각도와 Speed에 맞게 움직인다 
int AssaGetMoveLocation(cASSAEFFECT *pEffect); 

//원에 대한 좌표를 구한다 
int AssaGetCirclePosi(cASSAEFFECT *pEffect, int DistanceZ , int Angle);

//Stage와의 충돌을 체크한다 
int AssaCheckStageCrash(cASSAEFFECT *pEffect);
/*----------------------------------------------------------------------------*
*							   ETC 함수 
*-----------------------------------------------------------------------------*/	
//애니메이션을 셋팅한다 
int AssaGetAniFileMat(cASSAEFFECT *pEffect);

//이펙트를 카피한다 
int AssaCopyEffect(cASSAEFFECT *pEffect);

//캐릭터 포인터가 바뀔때 다시 셋팅해준다 
int AssaReSetCharPointer(cASSAEFFECT *pEffect);
/*----------------------------------------------------------------------------*
*							   extern 
*-----------------------------------------------------------------------------*/	
extern int Assa;  //인덱스 
extern cASSAEFFECT *cAssaEffect[cASSAEFFECT_MAX]; //이펙트 버퍼 
#endif
