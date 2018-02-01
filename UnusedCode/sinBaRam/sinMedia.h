/*----------------------------------------------------------------------------*
*	파일명 :  sinMedia.h
*	하는일 :  동영상 재생
*	작성일 :  최종업데이트 2005년 1월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#ifndef _SINMEDIA_HEADER_ 
#define _SINMEDIA_HEADER_ 


#include "amstream.h"
/*----------------------------------------------------------------------------*
*						Movie 클래스 
*-----------------------------------------------------------------------------*/	
class SINMOVIE
{ 
	
	int StartMovie();

	IMultiMediaStream *pMMStream;              // 스트림관련
	IMediaStream *pPrimaryVidStream;     
	IDirectDrawMediaStream *pDDStream;     
	IDirectDrawSurface *pSurface;     
	IDirectDrawStreamSample *pSample;
	IDirectDrawSurface      *pMovieSurface;
	char FileName[MAX_PATH];
	RECT DRect,SRect;  // SRect : Clip Size(Prepare에서 세팅)    DRect : 찍을 위치 및 크기
	int MovieState; // 0:NULL 1:PLAYING 2 :END OR STOP 제가 알아보기 쉽게 사용했습니다. ^^;;
	bool Open(IDirectDraw* pDD, char* name, IMultiMediaStream** ptMMStream);
	public :
	SINMOVIE();
	~SINMOVIE(); // call ShutDown();
	void SetBlitPos(int t,int b,int l,int r); 
	void SetBlitPos(RECT dest); 
	int GetMovieState() { return MovieState; }
	void ShutDown();
	bool PrepareMovie(IDirectDraw* pDD, IDirectDrawSurface *pDDSurface, char* FName);
	bool RenderStreamToSurface();
	void RenderStreamToSurfaceAll();

};
extern SINMOVIE sinMovie;
#endif