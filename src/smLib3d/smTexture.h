/*
typedef struct _TEXTURE {
	DIRECTDRAWSURFACE lpDDSurface;  // memory texture
	D3DTEXTUREHANDLE    Handle;

	char    			szName[100];
	_TEXTURE			*lpNext;
} TEXTURE, *LPTEXTURE;
*/



#define SWAPTEXTURE_MAX		64


//######################################################################################
//작 성 자 : 오 영 석
extern int		g_IsReadTextures;

extern int		g_DibLastReadWidth;
extern int		g_DibLastReadHeight;
//######################################################################################

//######################################################################################
//작 성 자 : 오 영 석
#define		MIPMAP_FILELIST				5
#define		SQUARE_MODE					1
#define		NOSQUARE_MODE				2

extern int MipMapModeCreate;
extern int TextureSwapMode;
//######################################################################################


//텍스쳐를 SWAP 하기 위한 버퍼 구조체
struct smSWAPTEXTURE {

	int		UsedTime;				//마지막으로 사용된 시간 ( 프레임 카운터 값 )
	int		SwapState;				//상태 TRUE 이면 현재 사용중

    DRZTEXTURE2 lpD3DTexture;
	DIRECTDRAWSURFACE lpDDSurface;

	smTEXTUREHANDLE *smTextureMaster;
};


class smTEXTURE {
public:

	//######################################################################################
	//작 성 자 : 오 영 석
	DWORD			TexSpeedSum[ MAX_TEXTURE ];
	//######################################################################################

	smTEXTUREHANDLE Texture[MAX_TEXTURE];
	DIRECTDRAWSURFACE *lpLastTextureSurface;
    DRZTEXTURE2 *lpLastTexture;

	CRITICAL_SECTION	cTextureSection;			//크리티컬 섹션

	//텍스쳐를 메모리와 SWAP 
	smSWAPTEXTURE		SwapTexture[SWAPTEXTURE_MAX];
	int					SwapCount;

	int LastTextureCnt;
	int TextureCnt;


	smTEXTURE();
	~smTEXTURE();

	void Init();
	int	 Remove();

	//######################################################################################
	//작 성 자 : 오 영 석
	//int Find( char *name );
	int Find( DWORD dwCode, char *Name );
	//######################################################################################

	smTEXTUREHANDLE *Add( char *name , char *nameA=0 );

	//DRZTEXTURE2 *AddName( char *name );
	//DRZTEXTURE2 *AddName( char *name , char *nameA );

	//텍스쳐를 제거한다 ( 1단계식 제거하여 메트리얼과의 링크가 없을 경우 완전 제거 )
	int Delete( smTEXTUREHANDLE *lpTex );
	//SWAP 텍스쳐를 지움
	int DeleteSwapTexture( int TexNum );
	//큰텍스쳐를 SWAP 하여 만든다 
	int SetLargeTexture( smTEXTUREHANDLE *TexHandle );

	//텍스쳐를 읽어 들인다
	int ReadTexture();

	//잃어 버린 텍스쳐를 다시 불러 들인다
	int Restore();

};

class smMATERIAL_GROUP {
	DWORD	Head;
public:
	smMATERIAL *smMaterial;
	DWORD MaterialCount;

	int ReformTexture;		//리폼할 텍스쳐 유무

	int MaxMaterial;

	int LastSearchMaterial;
	char szLastSearchName[64];

	smMATERIAL_GROUP();
	smMATERIAL_GROUP( int MaterialMax );
	~smMATERIAL_GROUP();

	// 메트리얼 초기화
	void Init( int MaterialMax );
	// 메트리얼 말기화
	int Close();

	//저장할 데이타의 크기를 미리 알려줌
	int GetSaveSize();
	//데이타를 파일로 저장 
	int SaveFile( HANDLE hFile );
	//파일에서 데이타를 읽어옴
	int LoadFile( HANDLE hFile );

	//사용되지 않는 메트리얼 제거
	int DeleteUnuseMaterial();
	//메트리얼을 등록
	int AddMaterial( ASE_MATERIAL *aseMaterial , char *szScript=0 );
	//텍스쳐 메트리얼 생성
	int CreateTextureMaterial( char *szBitmap , char *szOpacity , int TwoSide ,int Shade , DWORD TexSwap , DWORD BlendType );
	//메트리얼에 텍스쳐를 추가한다
	int	AddTexture( int MatNum , char *szBitmap , char *szOpacity=0 );

	//메트리얼의 스와핑 텍스쳐를 찾아 설정한다
	int ReSwapMaterial( smMATERIAL *lpMaterial );
	//메트리얼의 텍스쳐 스와핑값을 조사후 설정한다 ( 로딩 완료후 가능 )
	int CheckMatreialTextureSwap();
	//텍스쳐 갱신용 프레임
	int IncTextureFrame();
	//애니메이션 메트리얼 생성
	int CreateAnimationMaterial( char **szBitmap , int NumTex , DWORD BlendType , int AutoAnimMode );
	//메트리얼을 에니메이션 가능하게 변경
	int ChangeMaterialToAnimation( smMATERIAL *lpMaterial , char **szBitmap , int NumTex , DWORD BlendType , int AutoAnimMode );
	//메트리얼의 에니메이션 프레임을 설정
	int SetMaterialAnimFrame( smMATERIAL *lpMaterial , int frame );
	//텍스쳐 이름으로 메트리얼을 찾는다
	smMATERIAL *FindMaterialFromTextureName( char *szName );
	//텍스쳐 이름으로 다음 메트리얼을 찾는다
	smMATERIAL *FindNextMaterialFromTextureName();

	//######################################################################################
	//작 성 자 : 오 영 석
	//해당 메트리얼의 모든 텍스쳐를 로딩
	int ReadTextures( int MipMap = 0 );
	//######################################################################################

};


//메트리얼의 최대치
#define MATRIAL_MAX			5000

//extern smMATERIAL smMaterial[ MATRIAL_MAX ];
extern smMATERIAL *smMaterial;
extern smMATERIAL_GROUP	*smMaterialGroup;

extern smTEXTURE smTexture;


//비디오 사용 메모리 예상치
extern DWORD	VramTotal;


// 메트리얼 초기화
int InitMaterial();
//메트리얼 종료
int CloseMaterial();

//메트리얼을 등록
int AddMaterial( ASE_MATERIAL *aseMaterial );
//사용되지 않는 메트리얼 제거
int DeleteUnuseMaterial();
//텍스쳐 메트리얼 생성
int CreateTextureMaterial( char *szBitmap , char *szOpacity , int TwoSide ,int Shade , DWORD TexSwap , DWORD BlendType );
//메트리얼에 텍스쳐를 추가한다
int	AddTexture( int MatNum , char *szBitmap , char *szOpacity=0 );
//애니메이션 메트리얼 생성
int CreateAnimationMaterial( char **szBitmap , int NumTex , DWORD BlendType , int AutoAnimMode=TRUE );
//메트리얼을 에니메이션 가능하게 변경
int ChangeMaterialToAnimation( smMATERIAL *lpMaterial , char **szBitmap , int NumTex , DWORD BlendType , int AutoAnimMode=TRUE );
//메트리얼의 에니메이션 프레임을 설정
int SetMaterialAnimFrame( smMATERIAL *lpMaterial , int frame );

//메트리얼의 텍스쳐 스와핑값을 조사후 설정한다 ( 로딩 완료후 가능 )
int CheckMatreialTextureSwap();
//메트리얼의 스와핑 텍스쳐를 찾아 설정한다
int ReSwapMaterial( smMATERIAL *lpMaterial );
//메트리얼 검사용 타임 프레임
extern int MaterialFrame;
//텍스쳐 갱신용 프레임
int IncTextureFrame();

//텍스쳐 메모리 스왑 모드 설정
int SetTextureSwapMode( int mode );

//텍스쳐의 레벨 설정 ( 0-고화질 1-보통 2-저화질 3-초저화질 )
int smSetTextureLevel( int Level );


//텍스쳐 이름으로 메트리얼을 찾는다
smMATERIAL *FindMaterialFromTextureName( char *szName );
//텍스쳐 이름으로 다음 메트리얼을 찾는다
smMATERIAL *FindNextMaterialFromTextureName();






//텍스쳐 초기화
int InitTexture();
//모든 텍스쳐를 닫음
int CloseTexture();

//모든 텍스쳐를 읽어 들인다
int ReadTextures();
//텍스쳐를 첵크하여 잃어버린 텍스쳐를 다시 만든다
int RestoreTextures();

void ReleaseTextureAll();
int PopReleaseTexture();

//텍스쳐 영역 크리티칼 섹션 해제
void smLeaveTextureCriticalSection();
//텍스쳐 영역 크리티칼 섹션 선언
void smEnterTextureCriticalSection();


DIRECTDRAWSURFACE *GetLastTextureSurface();
DRZTEXTURE2 *GetLastTexture();

/////////////////////////[ BMP 파일 로드 ]///////////////////////////////
BYTE *LoadDib( char *Filename );
// Dib를 서페이스에 그린다
int DrawSurfaceFromDib( DIRECTDRAWSURFACE lpDDSurface , BYTE *lpDib );

//////////////// [ BMP파일을 텍스쳐 서페이스로 만든다 ] ///////////////
DIRECTDRAWSURFACE LoadDibSurface( char *Filename , int SysMem=FALSE );
////////// [ BMP파일을 텍스쳐 서페이스로 만든다 (알파텍스쳐랑 합성 ) ] ///////
DIRECTDRAWSURFACE LoadDibSurfaceAlpha( char *Filename , char *FileAlpha , int SysMem=FALSE );

//######################################################################################
//작 성 자 : 오 영 석
//////////////// [ BMP파일을 텍스쳐 서페이스로 만든다 (자동 스왑) ] ///////////////
int smCreateTexture( smTEXTUREHANDLE *lpTexHandle, int MipMap = 0 );
//######################################################################################

DIRECTDRAWSURFACE LoadDibSurfaceOffscreen( char *Filename );

//DRZTEXTURE2 *LoadDibTexture( char *Filename );
//DRZTEXTURE2 *LoadDibTextureAlpha( char *Filename, char *FileAlpha );
int LoadDibTextureNum( char *Filename );


DRZTEXTURE2 GetTextureHandle( int num );
DRZTEXTURE2 GetTextureChildHandle( int num );





int LoadDibMapTexture( char *Filename, int tSize );
int RemoveMapTexture();
int SetMapImage( int x , int y );

int DrawAnimBG( DIRECTDRAWSURFACE lpDDSSrc , int frame );
int LoadAnimBG();
int CloseAnimBG();
int ClearBG( DIRECTDRAWSURFACE lpDDSSrc, DWORD color );



//오류 관련
int DisplayError( HDC hdc , int x, int y );
int AddErrorList( char *szErrMsg );


