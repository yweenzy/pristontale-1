/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: directx.h
 *
 ***************************************************************************/

#ifndef __DXWAV_H_
#define __DXWAV_H_

// Includes....
//#include "d3drmwin.h"
#include <dsound.h>
#include <stdio.h>

// Defines.... : 사운드의 갯수는 총 15개( ref에서 0은 공통으로 사용하고 1~8은 메모리에 상주되 사용)
#define NUM_SOUNDS      1700

// Structures....
#pragma pack(1)
//wav의 포맷이 다른관계로 2가지로 읽는다.
//DATA[..]의 크기가 4와 18의 2개로 되어있어,
//우선 18로 읽어 DATA[0],DATA[1]이 0인경우에는 그대로 읽고 각기 'd','a'이면 
//다시 처음부터 DATA[4]짜리로 읽어서 사용한다.
struct WaveHeader0	
{
    BYTE        RIFF[4];          // "RIFF"
    DWORD       dwSize;           // Size of data to follow
    BYTE        WAVE[4];          // "WAVE"
    BYTE        fmt_[4];          // "fmt "
    DWORD       dw16;             // 16
    WORD        wOne_0;           // 1
    WORD        wChnls;           // Number of Channels
    DWORD       dwSRate;          // Sample Rate
    DWORD       BytesPerSec;      // Sample Rate
    WORD        wBlkAlign;        // 1
    WORD        BitsPerSample;    // Sample size
    BYTE        DATA[18];          // "DATA"=>00face.....data로 되어 있다.
    DWORD       dwDSize;          // Number of Samples
};


struct WaveHeader1
{
    BYTE        RIFF[4];          // "RIFFFF"의 경우 DATA가 18임에 주의
    DWORD       dwSize;           // Size of data to follow
    BYTE        WAVE[4];          // "WAVE"
    BYTE        fmt_[4];          // "fmt "
    DWORD       dw16;             // 16
    WORD        wOne_0;           // 1
    WORD        wChnls;           // Number of Channels
    DWORD       dwSRate;          // Sample Rate
    DWORD       BytesPerSec;      // Sample Rate
    WORD        wBlkAlign;        // 1
    WORD        BitsPerSample;    // Sample size
    BYTE        DATA[4];          // "DATA"
    DWORD       dwDSize;          // Number of Samples
};


struct WaveHeader2	//DATA[16] : 'fact'로 시작함.
{
    BYTE        RIFF[4];          // "RIFFFF"의 경우 DATA가 18임에 주의
    DWORD       dwSize;           // Size of data to follow
    BYTE        WAVE[4];          // "WAVE"
    BYTE        fmt_[4];          // "fmt "
    DWORD       dw16;             // 16
    WORD        wOne_0;           // 1
    WORD        wChnls;           // Number of Channels
    DWORD       dwSRate;          // Sample Rate
    DWORD       BytesPerSec;      // Sample Rate
    WORD        wBlkAlign;        // 1
    WORD        BitsPerSample;    // Sample size
    BYTE        DATA[16];          // "fact...data"
    DWORD       dwDSize;          // Number of Samples
};



#pragma pack()



// Functions ...

BOOL CreateSoundBuffer(DWORD dwBuf, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo, BOOL bStaticBuf);
BOOL ReadData(LPDIRECTSOUNDBUFFER lpDSB, FILE* pFile, DWORD dwSize, DWORD dwPos);
BOOL CreateBufferFromWaveFile(char* FileName, DWORD dwBuf);


// ======================= 실제 사용하실 함수군들 ==============================
BOOL InitDX_Wav(HWND g_hwnd); //초기화 
void TermDX_Wav();            //말기화
BOOL StopAllWav();            //몽땅 소리제거




//---------- 주의 : 여기에 쓰는 wav 포맷은 freq 2205*10HZ을 위주로 되어있어
//           다른 포맷일 경우 제대로 안될 가능성이 있음
//----------------------------------------------------------------------
// 
// Function     : PlaySoundDS()
//                dwSound : wav의 번호,  dwFlags : 0-한번만소리내기,1-루프를 돌아 계속소리내기
//				  dwVol  : 0~400     (실제로는 -400~0이고 *10한값)
//				  dwfreq : 441~4410  (실제로는 4410~44100HZ까지)
BOOL PlayWav(DWORD dwSound, DWORD dwFlags=0, DWORD dwVol=400, DWORD dwfreq=2205);

BOOL PlayWav2(DWORD dwSound, DWORD dwFlags=0, DWORD dwVol=400, DWORD dwfreq=2205);

//dwfreq : 441~4410(주파수 4410~44100HZ까지 지원하므로 44100hz의 wav는 주파수가 더이상
			//올라가지 않음에주의:녹음기를 이용해 22050hz으로 다운시켜쓸것)
//dwPan : 0~800(0:왼쪽 스피커, 400:중간 800:오른쪽 스피커쪽으로 소리가 더난다.)
BOOL PlayWav3(DWORD dwSound, DWORD dwFlags=0, DWORD dwVol=400, DWORD dwfreq=2205, DWORD dwPan=400);


//플레이도중에 volume change
BOOL PlayWav_VolChange(DWORD dwSound, DWORD dwVol=400);
//플레이도중에 Frequency Change
BOOL PlayWav_FrequencyChange(DWORD dwSound, DWORD dwfreq=2205);
//플레이도중에 Panning Change
BOOL PlayWav_PanChange(DWORD dwSound, DWORD dwPan=400);









// ======================= 실제 사용하실 함수군들 ==============================


//---------------- menu 선택에서만 사용하는 초기화임 ------------------//
//BOOL InitDX_Wav_MENU(HWND g_hwnd);  //초기화


BOOL InitDX_Wav2(HWND g_hwnd);  //초기화
void TermDX_Wav2();
BOOL CreateBufferFromWaveFile2(char* FileName, int sbufN);
BOOL CreateBufferFromWavBUF(unsigned char* wavBUf, unsigned int dwBuf);//메모리로부터읽기
BOOL sBufferClear(int sbufN);

void allWAVE_playORstop(int flag);	//화면이 손상된 경우(alttab등)의 경우 에 사용

BYTE getmouTH();		//입의 움직임을 알기위한것


BOOL StopWav(int i);




//========== dxwav.cpp의 백 뮤직관련 함수임. ====================
int  BackMusic_Load( int stageNumber );     //load 1~??까지
void BackMusicPlay();           //play
void BackMusicClr();            //메모리로 로드된 wav를 없앤다.
void BackMusic_Stop();


#endif


/*
char *sangJuWav[NUM_SOUNDS] = {      //상주 wav를 뽑는다.
"wav\\Ready.wav",              //게임모드 ready
"wav\\go.wav",                 //게임모드 gameing
"wav\\hurry.wav",              //특정시간안에 안눌르면 초당한번씩 나온다.
"wav\\se1.WAV",               //던질때 사용
"wav\\gameover.wav",			//game끝났을때.
"wav\\se2.WAV",               //붙을때 사용
"wav\\se6.WAV",               //우수수떨어질때
};
*/

#define WAV_READY()     PlayWav(1)		//자 시작
#define WAV_CLOCK()     PlayWav(2)		//시간읽기
#define WAV_SEND()      PlayWav(3)		//쏠때

#define WAV_CLEAVE()    PlayWav(4)		//붙을때
#define WAV_DRAP()      PlayWav(5)		//떨어질때
#define WAV_BANSA()     PlayWav(6)		//떨어지면서 벽에 부딫혀 반사될시..



#define WAV_VICTOR1()	PlayWav(7)	//"pbdou\\승리_박수.wav",	//점수가 양수일때
#define WAV_VICTOR2()	PlayWav(8)	//"pbdou\\승리1.wav.wav",	

#define WAV_LOSS1()	PlayWav(9)	//"pbdou\\패배1.wav",					//game끝났을때.
#define WAV_LOSS2()	PlayWav(10)	//"pbdou\\패배2.wav",
#define WAV_LOSS3()	PlayWav(11)	//"pbdou\\패배3.wav",
#define WAV_LOSS4()	PlayWav(12)	//"pbdou\\패배4.wav",


#define WAV_ENBALL1()	PlayWav(13)		//"적공올1.wav",//적의공이 많이 올라갈때..
#define WAV_ENBALL2()	PlayWav(14)		//"적공올2.wav",

#define WAV_BALLDOWN1() PlayWav(15)		//"공떨어뜨림1예쓰!.wav",//공떨어뜨릴때 많이 떨어지면 나옴.
#define WAV_BALLDOWN2() PlayWav(16)		//"공떨어뜨림2와우1.wav",

#define WAV_LINEDOWN()	PlayWav(17)		//"한줄down.wav",
#define WAV_JOJUN()		PlayWav(18)		//"조준기.wav",


#define WAV_WIN_M()		PlayWav(19)		//"wav\\win_m.wav",		//이겼을때 음악
#define WAV_LOSE_M()		PlayWav(20)		//"wav\\lose_m.wav",	//졌을때 음악.









BOOL Init_BGM(HWND hwnd);		//init
void Uninit_BGM(void);			//uninit
BOOL OpenBGM(LPSTR lpszFileName);	//bgm 운영
void PlayBGM(void);
void StopBGM(void);
void SetVolumeBGM( DWORD dwVol );		//볼륨 조절

//소리가 연주중인지 확인
BOOL IsPlayWav( DWORD dwSound );

void InitDirectSound();	// pluto 비스타에서 채팅 때문에 윈도우 생성전에 사운드 만든다


/*

class KSound
{
public:
    HWND    m_hWnd;

	LONG  m_lInTimer        ;
	BOOL  m_bTimerInit      ;
	BOOL  m_bPlaying        ;
	BOOL  m_bIsCloseOnRun   ;
	BOOL  m_bFileOpen       ;
	UINT  m_uTimerID        ;
	DWORD m_SecondBuffFocus ;

	//WAVEINFOCA  m_wiWave;



    //HRESULT CreateDirectSoundBuffer(LSFILEINFO*);
    //void    ReleaseDirectSoundBuffer(LSFILEINFO*);
    BOOL    IsPCMWave(LPSTR);

    HRESULT SetupStreamBuffer(LPSTR);


    BOOL  Init(HWND);
    void  Uninit(void);
    BOOL  OpenBGM(LPSTR);
    //LSFILEINFO *OpenFX(LPSTR);
    void  PlayBGM(void);
    void  StopBGM(void);
    //BOOL  PlayFX(LSFILEINFO*);
    //BOOL  StopFX(LSFILEINFO*);
    //BOOL  Volume(LSFILEINFO*);
    //BOOL  Pan(LSFILEINFO*);
    //BOOL  Freq(LSFILEINFO *pFileInfo);
};

*/