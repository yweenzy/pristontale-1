//######################################################################################
//작 성 일 : 2003-10-10 오후 4:45:50
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################
#pragma once


//
struct SWavDownUrl
{
	// 더 추가해야 하는 데이타 정보가 없다.  ㅡ_ㅡa
	char szRemainderUrl[128];
};


//
extern int  CreateWavIntHttp( char *lpWavUrlBasis );
extern void DestroyWavIntHttp(void);

extern int WavIntHttpPush( char *lpRemainderUrl );
//extern int WavIntHttpPop( SWavDownUrl *lpWavDownInfo );

extern void MainWavIntHttp(void);