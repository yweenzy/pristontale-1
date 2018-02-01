/*----------------------------------------------------------------------------*
*	파일명 :  YameEffect
*	하는일 :  새로운 이펙트 
*	작성일 :  최종업데이트 2003년 6월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#ifndef _YAMEEFFECT_HEADER_

#define _YAMEEFFECT_HEADER_

#define YAMEEFFECT_MAX		5000

/*----------------------------------------------------------------------------*
*							FADE OPTION
*-----------------------------------------------------------------------------*/	
#define YAME_DEFAULT_FADE	0x00000000
#define YAME_SMOOTH_FADE	0x00000001
#define YAME_NOT_FADEIN		0x00000010
#define YAME_NOT_FADEOUT	0x00000100


/*----------------------------------------------------------------------------*
*							FACE KIND
*-----------------------------------------------------------------------------*/	
#define YAMEFACE_BILLBOARD	0
#define YAMEFACE_WORLD		1
#define YAMEFACE_SCALE		2
#define YAMEFACE_TRACE		3

/*----------------------------------------------------------------------------*
*							YAME STRUCT
*-----------------------------------------------------------------------------*/	
// 애니메이션
struct sYAME_ANI{
	int		Cnt;
	int		DelayTime;
	int		MaxCnt;
	int		MatIndex[10];   //애니메이션이 될 메트리얼 번호 인덱스 
	int		Reverse;		//애니메이션 역순플렉 ( 1바른차순 2 역순 ) 

};

// 알파 블렌딩
struct sYAME_FADE{
	DWORD   FADE_CODE;
	int     MaxAlpha; //임의 알파값을 정한다 
	int     NowAlpha; //임의 알파값을 정한다 
	float   AlphaAmount;	
	int		AlphaStartTime;

};

// 회전 
struct sYAME_ROTATE{
	int		RAngle;
	int		RAngleSpeed;
	POINT3D RPosi; 
	POINT3D CenterPosi; //회전중심좌표
};

// Angle 회전 
struct sYAME_ANGLE_ROTATE{
	POINT3D	ARotate;
	POINT3D	ARotateSpeed;
	int     FACEY;

};

// 색 
struct sYAME_COLOR{
	int r;
	int g;
	int b;
	int a;

};

// 스케일 
struct sYAME_SCALE{
	POINT3D ScalePosi;
	POINT3D ScaleSpeed;
	int     CenterFlag;

};

struct sYAME_BILLBOARD{
	int FaceY;
	int ZposiFlag;

};




class cYAMEEFFECT;

/*----------------------------------------------------------------------------*
*						  YAMEEFFECT 메인 클래스  
*-----------------------------------------------------------------------------*/	
class  cYAMEEFFECT{
public:
	
	DWORD   CODE;				//이펙트 고유 코드 
	DWORD	MOVECODE;			//기본 움직임 
	int		Time;				
	int		Max_Time;
	int		Bone;

	///////////// 종류
	smFACE2D	Face;
	smPAT3D		*PatMesh;
	///////////// 소팅
	int		Index;
	int		ZDepth;

	///////////// 좌표 설정
	POINT3D	Posi;			//좌표
	POINT3D	DesPosi;		//설정된 위치 좌표
	POINT3D	Angle;			//앵글

	int		AddHeight;		//보정된 좌표
	
	///////////// 움직임
	POINT3D	MoveSpeed;

	///////////// 캐릭터
	smCHAR	*pChar;			//자신
	smCHAR	*desChar;		//선택된 캐릭터
	
	/////////////FACE TYPE
	int FACE_TYPE;
	int FACE_POSI;
	///////////// Size
	int w;
	int h;
	
	///////////// 애니메이션
	sYAME_ANI	Ani;
	
	///////////// 페이드 
	sYAME_FADE  Fade;

	///////////// 회전  
	sYAME_ROTATE Rotate;

	///////////// Angle 회전 
	sYAME_ANGLE_ROTATE Angle_Rotate;

	///////////// 컬러 
	sYAME_COLOR	Color;

	///////////// 스케일 
	sYAME_SCALE	Scale;

	///////////// 빌보드 
	sYAME_BILLBOARD BillBoard;

	///////////// FACE 연결리스트 
	cASSATrace *cAssaTrace; 



public:
	cYAMEEFFECT()
	{
		memset(this,0,sizeof(cASSAEFFECT));
		cASSATrace *pAssaTrace = new cASSATrace; //Face 연결리스트 
		cAssaTrace = pAssaTrace;

	}
	virtual ~cYAMEEFFECT()
	{
		if(cAssaTrace)delete cAssaTrace;
	}
	virtual	void Main(){}
	virtual void Draw(POINT3D *pPosi , POINT3D *pAngle){}
	
	//캐릭의 현제 상태를 체크한다 (바뀐포인다 , 죽었거나 , 마을에 들어섰을경우)
	//int AssaReSetCharPointer(); AssaEffect에서사용했다 

};

/*----------------------------------------------------------------------------*
*						  YAMEEFFECT FACE 클래스 
*-----------------------------------------------------------------------------*/	
class cYAMEFACE : public cYAMEEFFECT{
public:
	
	void Main()
	{
		Face.x = Posi.x;	//좌표 셋팅
		Face.y = Posi.y; 
		Face.z = Posi.z; 
		Face.width  = w;	//크기 셋팅 
		Face.height = h;
		if(!Face.height){
			h = w;
			Face.height = Face.width; //크기보정
		}
		if(!Fade.MaxAlpha)Fade.MaxAlpha = 255; 

		switch(Fade.FADE_CODE){
			case YAME_DEFAULT_FADE: 
				/*
				AlphaStartTime = (int)((float)Max_Time/100.0f*25.5f);
				AlphaAmount = 255.0f/(float)AlphaStartTime;
				if(Time <= AlphaStartTime ){
					Face.Transparency += (int)AlphaAmount; 
					if(Face.Transparency >255)
						Face.Transparency = 255;
				}
				*/

			break;
			case YAME_SMOOTH_FADE:  

			break;
			case YAME_NOT_FADEIN: 

			break;
			case YAME_NOT_FADEOUT: 

			break;
		}

		/*
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
		*/
		/*
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
		*/

	}
	void Draw(POINT3D *pPosi , POINT3D *pAngle)
	{
		
		if(!Face.MatNum)
			return;
		
		// Turn on Z-buffering
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, TRUE ); (문제가 생기는거 같아서 빼줬다)
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE );
		renderDevice.SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
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
			case YAMEFACE_BILLBOARD:
				//BillBoard
				if(!AssaAddFace2D(&Face,BillBoard.ZposiFlag,BillBoard.FaceY))return;
			break;
			case YAMEFACE_WORLD:
				//if(!AssaAddFaceWorld(&Face,&Angle))return;
			break;
			case YAMEFACE_SCALE:
				//if(!AssaAddFace2DLine(&Face,&ScalePosi,CenterFlag))return;
			break;
			case YAMEFACE_TRACE:
				//if(!AssaAddFaceTrace(&Face,cAssaTrace))return;
			break;
		}

		smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		smRender.RenderD3D();
	}
};

/*----------------------------------------------------------------------------*
*						  YAMEEFFECT MESH 클래스 
*-----------------------------------------------------------------------------*/	
class cYAMEMESH : public cYAMEEFFECT{
public:
/*
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
*/
};

/*----------------------------------------------------------------------------*
*						  AssaEffect 기본 함수
*-----------------------------------------------------------------------------*/	
void InitYameEffect();

void DrawYameEffect(POINT3D *pPosi , POINT3D *pAngle);

void MainYameEffect();

void MoveYameEffect(cASSAEFFECT *pEffect);

void CloseYameEffect();

void StopYameEffect(cASSAEFFECT *pEffect);

void YameEffectKeyDown();

/*----------------------------------------------------------------------------*
*							  Setting 함수 
*-----------------------------------------------------------------------------*/	
//AssaEffect셋팅
int  SetYameEffect(int MaxTime , char *FileName , smCHAR *pChar , POINT3D *pPosi , int AddHeight=0 , int BlendType=0); 

extern int Yame;  //인덱스 
extern cYAMEEFFECT *cYameEffect[YAMEEFFECT_MAX]; //이펙트 버퍼 
#endif
