

char *GetString(char *q , char *p);
char *GetWord(char *q , char *p);
//파일 이름으로 부터 디렉토리를 찾아 설정
char *SetDirectoryFromFile( char *filename );



//파일 찾기
char *smFindFile( char *szfile , char *FileExt=0 , DWORD *lpFileLen=0 );

//파일명의 확장자를 변경한다
char *ChangeFileExt( char *filename , char *FileExt );

//피지크 설정 값을 설정 ( 모델 파일에 적용될 )
void  smASE_SetPhysique( smPAT3D *p );
//피지크 설정 값을 구함 ( 모델 파일에 적용될 )
smPAT3D *smASE_GetPhysique();

smPAT3D *smASE_ReadBone( char *file );
smPAT3D *smASE_Read( char *file , char *szModelName=0 );

//######################################################################################
//작 성 자 : 오 영 석
smPAT3D* smASE_TalkReadBone( char *file );
//######################################################################################

//######################################################################################
//작 성 자 : 오 영 석
//모델 에니메이션 데이타를 몽땅 합친다
smPAT3D *smASE_MergeBone( char *szMeshFile, char **FileList, int FileCnt, int ReadType = 1 );
//######################################################################################

int smMAP3D_ReadASE( char *file );

//무대 모델 파일을 읽어 온다
smSTAGE3D *smSTAGE3D_ReadASE( char *file , smSTAGE3D *smStagep = NULL );

//자동 Mesh데이타 저장/재로드 설정
void smSetMeshReload( int flag , int MeshSave =0 );


#define sMATS_SCRIPT_WIND		1
#define sMATS_SCRIPT_ANIM2		2
#define sMATS_SCRIPT_ANIM4		4
#define sMATS_SCRIPT_ANIM8		8
#define sMATS_SCRIPT_ANIM16		16

#define sMATS_SCRIPT_WINDZ1		0x0020
#define sMATS_SCRIPT_WINDZ2		0x0040
#define sMATS_SCRIPT_WINDX1		0x0080
#define sMATS_SCRIPT_WINDX2		0x0100

#define sMATS_SCRIPT_WATER		0x0200
#define sMATS_SCRIPT_NOTVIEW	0x0400

#define sMATS_SCRIPT_PASS		0x0800
#define sMATS_SCRIPT_NOTPASS	0x1000

#define sMATS_SCRIPT_RENDLATTER	0x2000

//######################################################################################
// 작 성 자 : 오 영 석
#define sMATS_SCRIPT_BLINK_COLOR		0x4000
//######################################################################################


//######################################################################################
//작 성 자 : 오 영 석
#define sMATS_SCRIPT_CHECK_ICE			0x8000
//######################################################################################


//######################################################################################
//작 성 자 : 오 영 석
#define sMATS_SCRIPT_ORG_WATER			0x10000
//######################################################################################

