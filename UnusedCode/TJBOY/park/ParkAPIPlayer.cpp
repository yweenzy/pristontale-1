#define CPARKAPIPLAYER_CPP

#include "parkapiplayer.h"

#pragma comment(lib,"vfw32.lib")

CParkAPIPlayer::CParkAPIPlayer(void)
{
}

CParkAPIPlayer::~CParkAPIPlayer(void)
{
}

void CParkAPIPlayer::InitPlayer(void)
{
	hAPIPlay=NULL;
}

BOOL CParkAPIPlayer::LoadPlayerFile(HWND PlayhWnd, HINSTANCE PlayhInst, char *szFileName)
{
	hAPIPlay=MCIWndCreate(PlayhWnd, PlayhInst, WS_CHILD | WS_VISIBLE | MCIWNDF_NOOPEN | MCIWNDF_NOMENU | MCIWNDF_NOPLAYBAR, szFileName);

	if(!hAPIPlay)
		return FALSE;

	return TRUE;
}

void CParkAPIPlayer::PlaySize(int x, int y, int cx, int cy)
{
	MoveWindow(hAPIPlay, x, y, x+cx, y+cy, TRUE);
}

void CParkAPIPlayer::PlayPlayer(void)
{
	if (hAPIPlay) {
		MCIWndPlay(hAPIPlay);
		UpdateWindow( hAPIPlay );
	}
}

void CParkAPIPlayer::StopPlayer(void)
{
	if (hAPIPlay) {
		MCIWndClose(hAPIPlay);
		MCIWndDestroy(hAPIPlay);
		hAPIPlay=0;
	}
}