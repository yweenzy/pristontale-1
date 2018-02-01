/*----------------------------------------------------------------------------*
*	파일명 :  sinUtil.cpp
*	하는일 :  하는일 많음
*	작성일 :  최종업데이트 2004년 11월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"

#define  KeyState( KEY ) ( GetAsyncKeyState( KEY ) & 0x8000 ) 

SINMOVIE sinMovie;

/*----------------------------------------------------------------------------*
*						동영상 시작
*-----------------------------------------------------------------------------*/	

int SINMOVIE::StartMovie()
{
	/*

    // DirectDraw 인터페이스 생성
    LPDIRECTDRAW lpdd;
	LPDIRECTDRAWSURFACE lpddSurface;

    // 설정된 DirectDraw Device
    HRESULT hresult = DirectDrawCreate( NULL, &lpdd, NULL );
    if ( hresult != DD_OK )
	{
		MESSAGE( "DirectDrawCreate" );
        return FALSE;
	}

    // DirectDraw2 인터페이스 얻기
    hresult = lpdd->QueryInterface( IID_IDirectDraw4, (LPVOID*)&lpDD );
    if ( hresult != DD_OK )
	{
		MESSAGE( "lpdd->QueryInterface" );
        return FALSE;
	}

	hresult = lpddSurface->QueryInterface( IID_IDirectDrawSurface, (LPVOID*)&lpDDSPrimary );

	sinMovie.PrepareMovie(lpdd,lpddSurface,"water.mpg");
	sinMovie.SetBlitPos(0,480,0,640);
	
	
	//sinMovie.RenderStreamToSurface();   
	//sinMovie.RenderStreamToSurfaceAll();

    // DirectDraw 인터페이스 제거
    lpdd->Release();
	*/
	return TRUE;
}

SINMOVIE::SINMOVIE()
{ 
	pMMStream=NULL;
	pPrimaryVidStream=NULL;     
	pDDStream=NULL;     
	pSurface=NULL;     
	pSample=NULL;
	pMovieSurface=NULL;
	MovieState=0;
	CoInitialize(NULL);     
}

SINMOVIE::~SINMOVIE()
{
ShutDown();
}

void SINMOVIE::SetBlitPos(int t,int b,int l,int r)
{ 
DRect.top=t;
DRect.bottom=b;
DRect.left=l;
DRect.right=r; 
}
void SINMOVIE::SetBlitPos(RECT dest)
{
DRect.top=dest.top;
DRect.bottom=dest.bottom;
DRect.left=dest.left;
DRect.right=dest.right; 
}

void SINMOVIE::ShutDown()
{
if (pPrimaryVidStream) pPrimaryVidStream->Release();     
if (pDDStream) pDDStream->Release();
if (pSample) pSample->Release();
if (pSurface) pSurface->Release();   
if ((IMultiMediaStream *)pMMStream) (IMultiMediaStream *)pMMStream->Release();
CoUninitialize();  
}


bool SINMOVIE::Open(IDirectDraw* pDD, char* name, IMultiMediaStream** ptMMStream)
{
IAMMultiMediaStream  *pAMStream;     
WCHAR       wPath[MAX_PATH];     

if (FAILED(CoCreateInstance(CLSID_AMMultiMediaStream, NULL, CLSCTX_INPROC_SERVER, IID_IAMMultiMediaStream, (void **)&pAMStream))) 
{
  ShutDown();
  return false;
}
if (FAILED(pAMStream->Initialize(STREAMTYPE_READ, 0, NULL)))
{
  ShutDown();
  return false;
}
if (FAILED(pAMStream->AddMediaStream(pDD, &MSPID_PrimaryVideo, 0, NULL))) 
{
  ShutDown();
  return false;     
}
if (FAILED(pAMStream->AddMediaStream(NULL, &MSPID_PrimaryAudio, 
AMMSF_ADDDEFAULTRENDERER, NULL)))
{
  ShutDown();
  return false;  
}
MultiByteToWideChar(CP_ACP, 0, name, -1, wPath, sizeof(wPath)/sizeof(wPath[0]));    

if (FAILED(pAMStream->OpenFile(wPath, 0))) 
{
  ShutDown();
  return false;      
}
*ptMMStream = pAMStream;     
pAMStream->AddRef();  
  
pAMStream->Release();     
return true;
}


bool SINMOVIE::PrepareMovie(IDirectDraw* pDD, IDirectDrawSurface *pDDSurface, char* FName)
{
if (!Open(pDD,FName,&pMMStream)) return false;
if (FAILED(pMMStream->GetMediaStream(MSPID_PrimaryVideo, &pPrimaryVidStream)))
{
  ShutDown();
  return false;
};     
if (FAILED(pPrimaryVidStream->QueryInterface(IID_IDirectDrawMediaStream, (void **)&pDDStream)))
{
  ShutDown();      
  return false;
}
if (FAILED(pDDStream->CreateSample(NULL, NULL, 0, &pSample)))
{
  ShutDown();
  return false;     
}
if (FAILED(pSample->GetSurface(&pSurface, &SRect)))
{
  ShutDown();          
  return false;
}
if (FAILED(pMMStream->SetState(STREAMSTATE_RUN)))
{
  ShutDown();
  return false;    
}
pMovieSurface=pDDSurface;
MovieState=1;
  
return true;
}
bool SINMOVIE::RenderStreamToSurface()
{
if (KeyState(VK_RETURN)) {  MovieState=2; ShutDown();return false; } 
if (pSample->Update(0, NULL, NULL, 0) != S_OK) {  MovieState=2; ShutDown(); return 
false; } 
pMovieSurface->Blt(&DRect, pSurface, &SRect, DDBLT_WAIT, NULL); 
return true;
}

void SINMOVIE::RenderStreamToSurfaceAll()
{
while (1)
{
  if (KeyState(VK_RETURN)) {  MovieState=2; ShutDown(); return; } 
  if (pSample->Update(0, NULL, NULL, 0) != S_OK) {  MovieState=2; ShutDown(); return; } 
  pMovieSurface->Blt(&DRect, pSurface, &SRect, DDBLT_WAIT, NULL); 
}
}
