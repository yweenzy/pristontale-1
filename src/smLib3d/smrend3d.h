#ifndef _SMREND3D_H_
#define _SMREND3D_H_

//D3D의 TLVERTEX 멀티 텍스쳐 포맷
struct D3DTLVERTEX8 {
    float sx, sy, sz;
	float rhw;
	D3DCOLOR color;
	D3DCOLOR specular;
	float tu1, tv1;
	float tu2, tv2;
	float tu3, tv3;
	float tu4, tv4;
	float tu5, tv5;
	float tu6, tv6;
	float tu7, tv7;
	float tu8, tv8;
};

struct DRZD3DTLVERTEX{
	float sx;
	float sy;
	float sz;
	float rhw;
	D3DCOLOR color;
	D3DCOLOR specular;
	float tu;
	float tv;
};

#define D3DFVF_TLVERTEX0		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX0
#define D3DFVF_TLVERTEX1		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX1
#define D3DFVF_TLVERTEX2		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX2
#define D3DFVF_TLVERTEX3		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX3
#define D3DFVF_TLVERTEX4		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX4
#define D3DFVF_TLVERTEX5		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX5
#define D3DFVF_TLVERTEX6		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX6
#define D3DFVF_TLVERTEX7		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX7
#define D3DFVF_TLVERTEX8		D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_SPECULAR |D3DFVF_TEX8



// 한번에 렌더링 하는 페이스와 버텍스의 최대치
#define RENDER_FACE_MAX		20000
#define RENDER_VERTEX_MAX	20000

#define TEMPTEXLINK_MAX		20000
#define REND_LIGHT_MAX		64

//기본 클리핑 설정 값
#define RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH		1
#define RENDCLIP_WIDE_MULT_PERSPECTIVE_HEIGHT			(int)( ((float)3.36) * fONE )
#define RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT		(int)( ((float)2.7) * fONE )


//######################################################################################
//작 성 자 : 오 영 석
#define smRENDER_TYPE_ICE			0x01
//######################################################################################


class smRENDER3D {

public:
	//######################################################################################
	//작 성 자 : 오 영 석	
	DWORD		m_dwRenderType;
	//######################################################################################

	//######################################################################################
	// 작 성 자 : 오 영 석
	int			m_FogIsRend;
	int			m_FogMode;
	float		m_fFogStNum;
	float		m_fFogEndNum;
	DWORD		m_dwFogColor;
	//######################################################################################

	//######################################################################################
	//작 성 자 : 오 영 석
	int				m_GameFieldView;
	int				m_GameFieldViewStep;
	
	smRENDVERTEX   *RendVertex;								//렌더링 할 버텍스 
	smRENDFACE	   *RendFace;								//렌더링 할 페이스
	//######################################################################################

	smTEXLINK		TempTexLink[ TEMPTEXLINK_MAX ];		//임시 텍스쳐 링크
	smRENDMATRIAL	RendMatrial[ MATRIAL_MAX ];			//렌더링할 페이스의 메트리얼 테이블

	DWORD			RendMatrialList[ MATRIAL_MAX ];		//실제 렌더링에 필요한 메트리얼 테이블의 포인터 목록

	smMATERIAL		*smRendMaterial;		//렌더링 할메트리얼 포인터
	int				nMaterial;				//렌더링 할 전체 메트리얼 갯수

	DWORD			dwMatDispMask;			//메트리얼 속성 표시 마스크
	DWORD			DeviceRendMode;			//렌더링 시작 마무리 방식 (비디오카드)

	int RMatListCnt;						//렌더링 메트리얼 리스트의 카운터 정방향
	int RMatListRearCnt;					//렌더링 메트리얼 리스트 카운터 역방향

	int nRendVertex;						//렌더링 할 버텍스 수
	int nRendFace;							//렌더링 할 페이스 수
	int nTempTexLink;						//임시 텍스쳐좌표 연결 수

	int	SMSHIFT_PERSPECTIVE_WIDTH;			//좌우 클리핑 영역값 ( 1 -> 전체 2-> 절반 ) 
	int	SMMULT_PERSPECTIVE_HEIGHT;			//상하 클리핑 영역값 ( (float)3.36*fONE 전체 (float)2.7)*fONE 와이드 )

	//////////// STAGE3D용 포인터정보가 필요할 경우 /////////////
	smSTAGE_VERTEX	*Vertex;				//버텍스 리스트
	smSTAGE_FACE	*Face;					//페이스 리스트
	smTEXLINK		*TexLink;				//텍스쳐 좌표 리스트
	/////////////////////////////////////////////////////////////

	//######################################################################################
	//작 성 자 : 오 영 석
	smRENDLIGHT		smRendObjLight[REND_LIGHT_MAX];
	int				nRendObjLight;

	int				bApplyRendObjLight;
	//######################################################################################

	smRENDLIGHT		smRendLight[REND_LIGHT_MAX];	//렌더링용 빛
	int	nRendLight;									//렌더링할 빛의 수


	DWORD SumCount;							// 렌더링 첵크 카운터 

	int		CameraPosiMask;					// 카메라 위치 마스크 ( TRUE 시 카메라 입력 불가 )

	smMATRIX	mCamera;					// 카메라 좌표 변환 행렬

	int		CameraPosiX , CameraPosiY, CameraPosiZ;	//카메라 좌표
	int		CameraAngX , CameraAngY , CameraAngZ;	//카메라 각도

	int		TexPosiX,TexPosiY,TexPosiZ;				//텍스쳐 좌표 변형의 중심 위치
	int		TexSizeX,TexSizeY,TexSizeZ;				//텍스쳐 변형 크기

	DWORD	ClipStates;						// 클리핑값 ( 각종 클리핑의 실행 유무가 비트별 설정 )
	DWORD	RendStatTime;

	int		Color_R, Color_G , Color_B , Color_A ;		// 렌더링시 색상 값

	int		TextureFormState[8];						//텍스쳐 좌표 변형 속성

	DWORD	AlphaTestDepth;								//알파 테스트 값

	int RendAlphaFlag;

	int	ObjectVertexScale;								//오브젝트의 버텍스 스케일 변환
	int	ZWriteAuto;										//Z버퍼 쓰기 자동 설정

	int	DistortionMesh;									//메쉬 왜곡

	
	//######################################################################################
	// 작 성 자 : 오 영 석
	int   isRenderOutLine;
	float fOutLineRatio;
	float fOutLineX;
	float fOutLineY; 
	DWORD OutLineColor;
	//######################################################################################

	smRENDER3D();
	~smRENDER3D();

	//######################################################################################
	//작 성 자 : 오 영 석
	void CreateRenderBuff( int FieldViewType );
	void SetGameFieldViewStep(void);
	//######################################################################################

	// 렌더링할 카메라 위치를 입력 
	int SetCameraPosi ( int x, int y, int z, int angX, int angY, int angZ );
	// 렌더링할 카메라 위치를 입력 ( 회전은 행렬로 받음 )
	int SetCameraPosi ( int x, int y, int z, smEMATRIX *lpeMatrix );

	// 렌더링할 카메라 위치를 입력 ( 회전은 행렬로 받음 ) - Close까지 유효
	int OpenCameraPosi ( int x, int y, int z, smEMATRIX *lpeMatrix );
	// 카메라 위치 닫음
	int CloseCameraPosi();

	//######################################################################################
	//작 성 자 : 오 영 석
	// 렌더링할 빛을 추가 한다
	int	AddDynamicLight( int type, int x, int y, int z, int r, int g, int b, int a, int Range );

	// 빛을 모두 제거 한다
	int ClearObjLight();
	//######################################################################################

	// 렌더링할 빛을 추가 한다
	int	AddDynamicLight( int x, int y, int z, int r, int g, int b, int a, int Range );
	// 빛을 모두 제거 한다
	int ClearLight();

	// 좌표를 2D 영역으로 변환하여 돌려준다  
	int GetRect2D ( int x, int y, int z, int width, int height, RECT *Rect , POINT *Pos=0 );
	// 카메라 Z좌표를 구해줌  
	int GetDepthZ ( int x, int y, int z );

	// 각메시 값을 초기화 ( 스테이지 속성 설정 )
	int InitStageMesh ( smSTAGE_VERTEX *StageVertex , DWORD sum );
	// 각메시 값을 초기화 
	int Init();
	// 텍스쳐 중심 좌표 설정
	int SetTexPosi( int x, int y, int z , int sx, int sy, int sz );
	// 클리핑값 설정
	int SetClipStates( DWORD States );
	// 메트리얼 그룹 변경
	int SetMaterialGroup( smMATERIAL_GROUP *MatGroup );
	//텍스쳐 좌표연결을 추가한다 
	int AddRendTempTexLink( smRENDFACE *lpRendFace , DWORD *hTex , 
							  float u0 , float v0 , float u1 , float v1 , float u2 , float v2 );

	//스테이지 버텍스로 렌더링 버텍스 추가 ( 월드 좌표 소스 사용 )
	smRENDVERTEX *AddStageVertex ( smSTAGE_VERTEX *sv , smMATERIAL *lpMaterial  );
	//스테이지 페이스로 렌더링 페이스 추가
	smRENDFACE *AddStageFace ( smSTAGE_FACE *face );


	//오브젝트 버텍스로 렌더링 버텍스 추가 ( 월드 좌표 소스 사용 )
	//######################################################################################
	//작 성 자 : 오 영 석
	//smRENDVERTEX *AddObjectVertex ( smVERTEX *sv );
	smRENDVERTEX *AddObjectVertex( smVERTEX *sv, DWORD dwObjHead=0 );
	//######################################################################################

	//오브젝트 페이스로 렌더링 페이스 추가
	smRENDFACE *AddObjectFace ( smFACE *face );

	//2D 이미지 오브젝트 추가
	smRENDFACE *AddFace2D ( smFACE2D *face );
	//2D 이미지 오브젝트 추가 ( 회전 적용 )
	smRENDFACE *AddFace2D ( smFACE2D *face , int angle );

	//2D 이미지 오브젝트 추가 ( 화면좌표에 직접 그린다 )
	smRENDFACE *AddFace2D_Direct ( smFACE2D *face );

	//######################################################################################
	//작 성 자 : 오 영 석
	//렌더링 버텍스 추가 ( 좌표 직접 입력 )
	//smRENDVERTEX *AddRendVertex ( int x, int y, int z, short *pLight );
	smRENDVERTEX *AddRendVertex ( int x, int y, int z, short *pLight, int nx=0, int ny=0, int nz=0 );
	//######################################################################################

	//렌더링 페이스 추가 ( 버텍스 포인터 직접 입력 )
	smRENDFACE *AddRendFace ( smRENDVERTEX *v0 , smRENDVERTEX *v1, smRENDVERTEX *v2 , 
										DWORD matrial , smTEXLINK *lpTexLink );
	//페이스 사이드값 구함 ( DotProduct )
	int GetFaceSide( smRENDFACE *rendface );
	// 렌더링 페이스를 클리핑 ( dwClipMode는 SMCLIP_[방향] ) 
	int AddRendFaceClip( smRENDFACE *rendface , DWORD dwClipMode );
	// 렌더링 페이스를 텍스쳐 클리핑 
	int AddRendFaceTextureClip( smRENDFACE *rendface );

	//메트리얼 리스트에 목록 추가
	int AddRendMaterialList( int MatNum );

	//######################################################################################
	//작 성 자 : 오 영 석
	int SetDynamicObjLight( smRENDVERTEX *sv, int z );
	//######################################################################################
	
	//다이나믹 라이트 설정
	int SetDynamicLight( smRENDVERTEX *sv , int z );
	// Z 값에 따른 색상치를 BackColor값에 가깝도록 조절한다 
	int SetColorZclip( smRENDVERTEX *sv , int z );
	// 버텍스의 색상을 주어진 값에 가깝도록 단계적으로 조절
	int ShiftLight( smRENDVERTEX *sv , int lev , int r,int g,int b, int a );
	// 렌더버텍스에 색상을 더한다
	int AddLight( smRENDVERTEX *sv, int r,int g,int b , int a);
	//렌더버텍스의 sLight를 Color 와 Specular 로 설정 한다
	int SetRendColor( smRENDVERTEX *sv );
	// 전체 렌더링 페이스를 클리핑  
	int ClipRendFace();
	// 버텍스를 2D좌표로 변환  
	int GeomVertex2D( int ColorEffect=TRUE );
	// 윈쪽을 클리핑점을 구하여 렌더링 버텍스에 추가한다 ( fMultPoint 교점 좌표를 구하기 위한 방정식의 값  ) 
	smRENDVERTEX * AddRendVertex_ClipLeft( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	// 오른쪽을 클리핑점을 구하여 렌더링 버텍스에 추가한다 ( fMultPoint 교점 좌표를 구하기 위한 방정식의 값  ) 
	smRENDVERTEX * AddRendVertex_ClipRight( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	// 위쪽 클리핑점을 구하여 렌더링 버텍스에 추가한다 ( fMultPoint 교점 좌표를 구하기 위한 방정식의 값  ) 
	smRENDVERTEX * AddRendVertex_ClipTop( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	// 아래쪽 클리핑점을 구하여 렌더링 버텍스에 추가한다 ( fMultPoint 교점 좌표를 구하기 위한 방정식의 값  ) 
	smRENDVERTEX * AddRendVertex_ClipBottom( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	// Z NEAR 클리핑점을 구하여 렌더링 버텍스에 추가한다 ( fMultPoint 교점 좌표를 구하기 위한 방정식의 값  ) 
	smRENDVERTEX * AddRendVertex_ClipNearZ( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	// Z FAR 클리핑점을 구하여 렌더링 버텍스에 추가한다 ( fMultPoint 교점 좌표를 구하기 위한 방정식의 값  ) 
	smRENDVERTEX * AddRendVertex_ClipFarZ( smRENDFACE *rendface , int a, int b , float *fMultPoint );
	// TEXTURE 클리핑점을 구하여 렌더링 버텍스에 추가한다 ( fMultPoint 교점 좌표를 구하기 위한 방정식의 값  ) 
	smRENDVERTEX * AddRendVertex_ClipTexture( smRENDFACE *rendface , int a, int b , float *fMultPoint );

	int SetD3DRendBuff(float *RenderBuff, int matrial, int TexClip);
	int SetD3DRendBuff2(float *RenderBuff, int matrial, int TexClip);

	//######################################################################################
	// 작 성 자 : 오 영 석
	int SetD3DRendBuff3(float *RenderBuff, int matrial, int TexClip, short sColors[4]);
	//######################################################################################

	//######################################################################################
	// 작 성 자 : 오 영 석
	int SetItem2PassD3DRendState( smMATERIAL *lpMaterial );
	//######################################################################################

	// D3D렌더링 속성 설정 
	int SetD3DRendState( smMATERIAL *lpMaterial , int TexClip );
	// D3D렌더링 속성 설정 알파만 설정
	int SetD3DRendStateOnlyAlpha( smMATERIAL *lpMaterial , int TexClip );

	//메트리얼 블록을 D3D로 렌더링
	int RenderD3D( int MatNum );
	// D3D로 렌더링
	int RenderD3D();

	//######################################################################################
	// 작 성 자 : 오 영 석
	void SetD3D_OutLine( int isSet, int Dist=0, float fsetX=0, float fsetY=0, DWORD Color=0 );
	int  RenderD3D_OutLine(void);
	int	 RenderD3D_OutLine( int MatNum );
	//######################################################################################

	//2d 좌표가 포함된 렌더링된 페이스를 찾는다
	int FindRenderFace2D( smRENDFACE **lpRendFace , int x, int y );

};

//렌더링 클래스 
extern smRENDER3D	smRender;

//렌더링용 라이트 벡터
void smSetRendLightVect( int x, int y, int z );


//######################################################################################
//작 성 자 : 오 영 석
extern int   g_IsDxProjectZoomIn;
extern float g_fZoomInAdd_x;
extern float g_fZoomInAdd_y;
extern float g_fZoomInDiv_x;
extern float g_fZoomInDiv_y;

extern void SetDxProjection( float radians, int SizeX, int SizeY, float near_z, float far_z );
extern void DxProjectionWork( smRENDVERTEX *lpRendVer );
//######################################################################################


//######################################################################################
//작 성 자 : 오 영 석
extern int  CreateItem2PassTexture(void);
extern void SetItem2PassTexture( int TexHandleNum, int TexFormState = smTEXSTATE_FS_SCROLL10 );
//######################################################################################

#endif