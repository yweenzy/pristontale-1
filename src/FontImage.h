//######################################################################################
//작 성 일 : 2004-04-20 오전 10:53:30
//리 턴 값 :
//설    명 :
//작 성 자 : 오 영 석
//######################################################################################//
#pragma once


//
void CreateFontImage(void);

// fRatio=1.f 이면 정상 크기.
int  DrawFontImage( char *lpStr, int xPos, int yPos, DWORD rgba, float fRatio=1.f );
int  DrawSpecialFontImage( int SpecialNum, int xPos, int yPos, DWORD rgba, float fRatio=1.f );

