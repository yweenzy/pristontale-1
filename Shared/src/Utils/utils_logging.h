#ifndef _UTILS_LOGGING_H_
#define _UTILS_LOGGING_H_

#include <cstdio>
#include <cstdlib>

#define GameLogFile "game.log"
#define ErrorLogFile "error.log"
#define DebugLogFile "debug.log"

#define LOG_ERROR 1
#define LOG_GAME 2
#define LOG_DEBUG 3

void Utils_DeleteLogFiles();

void Utils_Log(DWORD type, char* msg, ...);

void Utils_DumpPacket(char* pckname, BYTE* buffer, int size);

#endif