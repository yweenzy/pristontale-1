#include <iostream>
#include "utils_filesystem.h"
#include "utils_logging.h"

void Utils_DeleteLogFiles()
{
	DeleteFile( "error.log");
	DeleteFile( "debug.log");
}

void Utils_Log(DWORD type, char* msg, ...)
{
	if(type == LOG_DEBUG)
	{
		#if !defined(_DEBUG) && !defined(DEBUG)
			return;
		#endif
	}

	char buffer[1024];
	va_list args;
    va_start (args, msg);
	vsprintf (buffer, msg, args);

	//Console Log
	if(type == LOG_ERROR)
		std::cout << "ERROR: " << buffer << std::endl;
	else if(type == LOG_GAME)
		std::cout << "GAME: " << buffer << std::endl;
	else if(type == LOG_DEBUG)
		std::cout << "DEBUG: " << buffer << std::endl;

	FILE *fpc_log = NULL;

	if(type == LOG_ERROR)
		fpc_log = fopen(ErrorLogFile,"a+t");
	else if(type == LOG_GAME)
		fpc_log = fopen(GameLogFile,"a+t");
	else if(type == LOG_DEBUG)
		fpc_log = fopen(DebugLogFile,"a+t");

	if( fpc_log == NULL )
		return;
	
	fprintf(fpc_log,"%s\n",buffer);
	fclose(fpc_log);
	fpc_log = NULL;
}

void Utils_DumpPacket(char* pckname, BYTE* buffer, int size)
{
	FILE *fpc = NULL;

	fpc = fopen(pckname, "wb");

	fwrite(buffer, sizeof(BYTE), size, fpc);

	fclose(fpc);
}