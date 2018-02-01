#include "smDsx.h"

//#include "smMatrix.h"
class smPAT3D;

#define OBJ_FRAME_SEARCH_MAX		32

//######################################################################################
//작 성 자 : 오 영 석
#define OBJ_HEAD_TYPE_NEW_NORMAL				0x80000000
//######################################################################################

// 렌더링용 버텍스 포인터
class smPOINT3D {
public:

	smVERTEX	*pVertex;			// 좌표 포인트

	int			rx , ry , rz;		// 회전 좌표
	int			wx , wy , wz;		// 월드 좌표
	int			sx , sy , sz;
	int			ox , oy , oz;

	int			X,Y,Z;				// 카메라 시점 좌표
	int			x2d,y2d;			//렌더링 될 2D 좌표
	BYTE		Clip2d[4];			//화면밖 버텍스 확인

	smPOINT3D();
	smPOINT3D( smVERTEX *pv );
	~smPOINT3D();

	void SetTo( smVERTEX *pv );
	void xform2d();
	void GlobalRotate(int *trig);
	//   지역 중심 좌표 이동
	void Move(int dx, int dy, int dz);
	//   카메라 좌표
	void GlobalXform();

};


//TM 포지션 
struct smFRAME_POS {
	int StartFrame;
	int EndFrame;
	int PosNum;
	int PosCnt;
};

struct smDFILE_HEADER {
	char szHeader[24];
	int ObjCounter;
	int MatCounter;
	int MatFilePoint;
	int First_ObjInfoPoint;
	int TmFrameCounter;
	smFRAME_POS TmFrame[OBJ_FRAME_SEARCH_MAX];		//여러개의 프레임파일 연결 정보임
};

struct smDFILE_OBJINFO {
	char szNodeName[32];
	int Length;
	int ObjFilePoint;
};

//######################################################################################
//작 성 자 : 오 영 석
struct SMotionStEndInfo
{
	DWORD	StartFrame;
	DWORD	EndFrame;
};
//######################################################################################

class smOBJ3D {
	DWORD		Head;
public:

	smVERTEX	*Vertex;				// 버텍스
	smFACE		*Face;					// 페이스
	smTEXLINK	*TexLink;				//텍스쳐 좌표 리스트

	smOBJ3D		**Physique;				// 각 버텍스의 피지크 오브젝트

	smVERTEX	ZeroVertex;				// 오브젝트 중앙 버텍스 값

	int maxZ,minZ;
	int maxY,minY;
	int maxX,minX;

	int dBound;							// 바운딩 스페어 값 ^2
	int Bound;							// 바운딩 스페어 값

	int MaxVertex;
	int MaxFace;

	int nVertex;
	int nFace;

	int nTexLink;

	int ColorEffect;					// 색상효과 사용 유무
	DWORD ClipStates;					// 클리핑 마스크 ( 각 클리핑별 사용 유무 ) 

	POINT3D Posi;
	POINT3D CameraPosi;
	POINT3D Angle;
	int	Trig[8];

	// 애니메이션 관련
	char	NodeName[32];		// 오브젝트의 노드 이름
	char	NodeParent[32];		// 부모 오브젝트의 이름
	smOBJ3D	*pParent;			// 부모 오브젝트 포인터

	smMATRIX	Tm;				// 기본 TM 행렬
	smMATRIX	TmInvert;		// Tm 의 역행렬 
	//smMATRIX	TmResult;		// 애니메이션 행렬
	smFMATRIX	TmResult;		// 애니메이션 행렬
	smMATRIX	TmRotate;		// 기본적 회전 행렬 

	smMATRIX	mWorld;			// 월드좌표 변환 행렬
	smMATRIX	mLocal;			// 로칼좌표 변환 행렬

	int		lFrame;				// 최후 프레임

	float	qx,qy,qz,qw;		// 회전 쿼터니언
	int		sx,sy,sz;			// 스케일 좌표
	int		px,py,pz;			// 포지션 좌표

	smTM_ROT	*TmRot;			// 프레임별 회전 애니메이션
	smTM_POS	*TmPos;			// 프레임별 포지션 애니메이션
	smTM_SCALE	*TmScale;		// 프레임별 스케일 애니메이션

	//######################################################################################
	//작 성 자 : 오 영 석
	smFMATRIX	*TmPrevRot;		// 프레임별 애니메이션 행렬
	//######################################################################################

	int TmRotCnt;
	int TmPosCnt;
	int TmScaleCnt;

	//TM 프레임 서치 ( 프레임이 많으면 찾기가 힘듬 )
	smFRAME_POS TmRotFrame[OBJ_FRAME_SEARCH_MAX];		//ROT프레임 [프레임 , 위치]
	smFRAME_POS TmPosFrame[OBJ_FRAME_SEARCH_MAX];		//POS프레임 [프레임 , 위치]
	smFRAME_POS TmScaleFrame[OBJ_FRAME_SEARCH_MAX];		//SCALE프레임 [프레임 , 위치]
	int TmFrameCnt;									//TM프레임 카운터 (전체갯수)

	smOBJ3D();
	~smOBJ3D();
	smOBJ3D( int nv , int nf );
	// 초기화루틴 ( 버텍스 , 페이스의 수 , 그리고 피지크 사용여부  )
	void Init( int nv, int nf , int pFlag=0 );
	// 버텍스 좌표 추가
	int AddVertex( int x, int y, int z );
	// 페이스에 버텍스 번호 추가
	int AddFace( int a, int b, int c );

	//텍스쳐 좌표를 형태에 맟춰서 변경한다
	int ReformTexture( int Type , int MatNum , int MatCnt , POINT3D *pos , POINT3D *size );

	//페이스에 메트리얼 입력
	int SetFaceMaterial( int FaceNum , int MatNum  );
	//텍스쳐 좌표연결을 추가한다 
	int AddTexLink( int FaceNum , DWORD *hTex , smFTPOINT *t1 , smFTPOINT *t2 , smFTPOINT *t3 );
	//텍스쳐 좌표연결을 추가한다 ( TPOINT 사용 )
	int AddTexLinkTP( int FaceNum , DWORD *hTex , smTPOINT *t1 , smTPOINT *t2 , smTPOINT *t3 );

	// 페이스 와 텍스쳐 동시에 추가
	int AddFace( int a, int b, int c , smTPOINT *t1 , smTPOINT *t2, smTPOINT *t3 );

	// 노말값 삭제 ( 0으로 초기화 )
	void ZeroNormals();
	// 쉐이드 노말값 생성
	void SetGNormals();
	// 페이스를 메트리얼별로 정렬
	void SortMatrial();
	// 겹치거나 사용되지 않는 VERTEX를 찾아내어 정리한다
	void SortVertex();
	// TM의 역행렬을 계산하여 지역 좌표 변환
	void ReformTM();
	// 피지크의 대응 TM의 역행렬을 계산하여 지역 좌표 변환
	void ReformPhysique();

	// 오브젝트 렌더링 준비
	int	 BeginRender();
	// 이건 바보다.
	int  TestRotate( int x , int y , int z ,  POINT3D *LocalAngle , POINT3D *GlobalAngle );
	// 월드행렬에의한 월드좌표 구하기  
	int  WorldForm();

	//######################################################################################
	//작 성 자 : 오 영 석
	//회전 쿼터니언을 보간 , 중간 프레임의 행열을 구함 
	int GetRotFrame( smFMATRIX &gmat, smFMATRIX *PrevRot, smTM_ROT *tmRot, int frame, SMotionStEndInfo *lpFrameInfo=NULL );

	//이동 좌표를 보간 , 중간 프레임의 이동 좌표를 구함 
	int GetPosFrame( float &x, float &y, float &z, smTM_POS *tmPos, int frame );
	//######################################################################################

	//스케일 좌표를 보간 , 중간 프레임의 스케일 좌표를 구함 
	int GetScaleFrame( int &x, int &y, int &z , smTM_SCALE *tmSclae , int frame );

	//애니메이션 프레임  위치를 찾는다 ( 다중 결합 애니메이션 경우 )
	int GetTmFramePos( int frame );
	//애니메이션 프레임 회전 위치를 찾는다 ( 다중 결합 애니메이션 경우 )
	int GetTmFrameRot( int frame );
	//애니메이션 프레임 크기를 찾는다 ( 다중 결합 애니메이션 경우 )
	int GetTmFrameScale( int frame );

	//######################################################################################
	//작 성 자 : 오 영 석	
	int TmTalkAnimation( int frame );
	int TmAnimation( int frame, int ax, int ay, int az, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo=NULL );
	
	// 애니메이션 과 지역좌표 회전 행렬 만들기
	int  TmAnimation( int frame, int ax , int ay , int az, SMotionStEndInfo *lpFrameInfo=NULL );
	//######################################################################################

	// 광원 계산용
	//void SetColor( int flag , int alpha );

	// 오브젝트의 좌표 와 각도 설정
	void SetPosi( POINT3D *point , POINT3D *angle );
	// D3D방식으로 프리미티브에 렌더링 ( 카메라 좌표와 카메라 각도 입력 )
	int  RenderD3D( POINT3D *camera , POINT3D *angle );

	//######################################################################################
	//작 성 자 : 오 영 석
	int	 RenderD3dOpening( POINT3D *camera, POINT3D *angle );
	//######################################################################################

	// 렌더링 할지를 테스트 (카메라 좌표와 카메라 각도 입력 )
	int TestRender(POINT3D *camera , POINT3D *angle );
	//테스트 완료된후의 레더링을 재개 한다
	int ActionRenderD3D();


	//파일로 저장할 크기를 미리 얻는다
	int  GetSaveSize();
	//파일로 저장
	int  SaveFile( HANDLE hFile );
	//파일로 부터 데이타 로드
	int  LoadFile( HANDLE hFile , smPAT3D *PatPhysique=0 );
};

class smPAT3D {
	DWORD		Head;
public:
	smOBJ3D		*obj3d[128];
	BYTE		TmSort[128];					// 에니메이션 계산 순서 (링크 레벨순)

	smPAT3D		*TmParent;

	smMATERIAL_GROUP	*smMaterialGroup;		//메트리얼 그룹

	int MaxFrame;
	int Frame;

	int SizeWidth , SizeHeight;					// 높이 넓이 의 최대치 

	int nObj3d;
	DRZTEXTURE2 *hD3DTexture;

	POINT3D Posi;
	POINT3D Angle;
	POINT3D CameraPosi;

	int dBound;							// 바운딩 스페어 값 ^2
	int Bound;							// 바운딩 스페어 값

	smFRAME_POS TmFrame[OBJ_FRAME_SEARCH_MAX];		//여러개의 프레임파일 연결 정보임
	int TmFrameCnt;

	int		TmLastFrame;
	POINT3D TmLastAngle;

	smPAT3D();
	~smPAT3D();

	//초기화
	void	Init();
	//이 클래스 닫기
	void	Close();

	// 오브젝트 추가
	int		AddObject( smOBJ3D *obj );
	// 오브젝트 별 부모 자식 관계를 고려하여 연결 
	int		LinkObject();
	//부모를 정하구 모든 오브젝트를 부모의 특정 오브젝트로 연결 시킨다
	int		LinkParentObject( smPAT3D *patParent , smOBJ3D *objParent=0 );
	// 각 오브젝트의 피지크별 지역좌표 변환
	int		ReformPhysique();
	// 각 오브젝트의 지역좌표 변환
	int		ReformTM();

	// 노드네임으로 오브젝트 구하기
	smOBJ3D *GetObjectFromName( char *name );
	
	//######################################################################################
	//작 성 자 : 오 영 석
	int		SetFrame( int frame, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo=NULL );
	int		TmTalkAnimation( int frame );
	int		TmAnimation( int frame , int ax, int ay, int az, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo=NULL );

	// 프레임에 따른 애니메이션 값 구하기 
	int		SetFrame( int frame, SMotionStEndInfo *lpFrameInfo=NULL );
	// 오브젝트별 애니메이션 과 회전 등 월드행렬 설정
	int		TmAnimation( int frame , int ax, int ay, int az, SMotionStEndInfo *lpFrameInfo=NULL );
	//######################################################################################

	// 각 오브젝트의 노말값 제거( 0의로 초기화 )
	void	ZeroNormals();
	// 패턴의 좌표 와 각도 설정
	void	SetPosi( POINT3D *point , POINT3D *angle );
	// 패턴의 좌표를 원좌표로 고정
	void	SetFixPosi();

	//######################################################################################
	//작 성 자 : 오 영 석
	int		RenderD3D( POINT3D *camera, POINT3D *angle, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo=NULL );
	int		ChoiseRenderD3D( POINT3D *camera, POINT3D *angle, char **szNodeList, int ListCnt, smPAT3D *TalkPattern, SMotionStEndInfo *lpFrameInfo=NULL );

	// D3D방식으로 프리미티브에 렌더링 ( 카메라 좌표와 카메라 각도 입력 )
	int		RenderD3D( POINT3D *camera , POINT3D *angle, SMotionStEndInfo *lpFrameInfo=NULL );
	// D3D방식으로 프리미티브에 선택형 렌더링 ( 카메라 좌표와 카메라 각도 입력 )
	int		ChoiseRenderD3D( POINT3D *camera , POINT3D *angle , char **szNodeList , int ListCnt, SMotionStEndInfo *lpFrameInfo=NULL );
	//######################################################################################

	//######################################################################################
	//작 성 자 : 오 영 석
	int		RenderD3dOpening( POINT3D *camera, POINT3D *angle );
	//######################################################################################

	//데이타를 파일로 저장
	int		SaveFile( char *szFile );
	//데이타를 파일에서 로드
	int		LoadFile( char *szFile , char *szNodeName=0 );

};

extern	DWORD		smObjFixPos;			//렌더링 좌표 고정

int smGetMapHeight( int x, int z );
int smAddVertexLight( smRGB *LightRGB , smLIGHT3D *light , POINT3D *posi , POINT3D *normal );
int smAddVertexLightSpot( smRGB *LightRGB , smLIGHT3D *light , POINT3D *posi , POINT3D *normal );

//패턴 저장 파일을 찾아 올바른지 확인 (버전 확인) 
int smFindPatFile( char *szfile , char *FileExt );


