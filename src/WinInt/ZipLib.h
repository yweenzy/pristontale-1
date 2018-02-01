//######################################################################################
//작 성 일 : 2003-10-13 오후 1:14:50
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
#pragma once

// 압축 대상 BUFF 싸이즈. 5 MByte. 로 한정. 
#define MAX_ZIP_BUFF_SIZE			((1024*1024) * 5)
#define MAX_FILE_NAME				64
#define ZIP_LIB_VER					"100"

//
enum eZIP_ERROR
{
	ZIP_OK					=  1,
	ZIP_ERROR				= -1,
	ZIP_UN_ERROR			= -2,	
	ZIP_BUFF_SIZE_ERROR		= -3,
	ZIP_TYPE_ERROR			= -4,
	ZIP_FILE_ERROR			= -5,
	ZIP_NAME_ERROR			= -6,
};

//
struct SZIP_HEADER
{
	DWORD Type;
	DWORD TotalFileSize;
	DWORD TotalOrgSize;
	DWORD ZipSize;
	char  OrgFileName[ MAX_FILE_NAME ];
	DWORD Reserved;
};


extern "C" __declspec(dllexport) int SetExtChangeZip( char *szDest );

// OrgFileName 에는 값이 셋팅 되지 않는다. ( 메모리 대 메모리 )
extern "C" __declspec(dllexport) int ZipData( BYTE *lpDestBuff, DWORD *lpDestBuffSize, BYTE *lpSrcBuff, DWORD SrcBuffSize );
extern "C" __declspec(dllexport) int UnZipData( BYTE *lpDestBuff, DWORD *lpDestBuffSize, BYTE *lpSrcBuff );

// lpSrcFileName 확장자가 변경(".zpt") 돼서 Zip 파일 생성되고. lpOrgFileName 값이. OrgFileName 으로 셋팅.
extern "C" __declspec(dllexport) int ZipFile( char *lpSrcFileName );
// OrgFileName 으로 압축이 풀린다.
extern "C" __declspec(dllexport) int UnZipFile( char *lpSrcFileName );

// OrgFileName 으로 압축이 풀린다.
extern "C" __declspec(dllexport) int UnZipDataToFile( BYTE *lpSrcBuff );

// OrgFileName 으로 해당 Directory 압축이 풀린다.
extern "C" __declspec(dllexport) int UnZipDataToDirectory( char *Directory, BYTE *lpSrcBuff );
