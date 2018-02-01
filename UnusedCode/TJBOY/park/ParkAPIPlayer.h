#pragma once
#ifndef __PARKAPIPLAYER_H__
#define __PARKAPIPLAYER_H__

#include <windows.h>
#include <vfw.h>

class CParkAPIPlayer
{
public:
	CParkAPIPlayer(void);
	~CParkAPIPlayer(void);

	void InitPlayer(void);
	BOOL LoadPlayerFile(HWND PlayhWnd, HINSTANCE PlayhInst, char *szFileName);
	void PlaySize(int x, int y, int cx, int cy);
	void PlayPlayer(void);
	void StopPlayer(void);

public:
	HWND hAPIPlay;
};

#endif

#ifdef CPARKAPIPLAYER_CPP
	CParkAPIPlayer ParkAPIPlay;
#else
	extern CParkAPIPlayer ParkAPIPlay;
#endif