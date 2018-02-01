#ifndef _NSPRTSVR_H_
#define _NSPRTSVR_H_

#define NSPRITE_OK	0x0	//All is OK
#define VERSION_OLD	0x1	//The nsprite is old and must be updated
#define EXIST_CHEAT	0x2	//One or more cheat program is running

void __stdcall InitNSprtsvr();
DWORD __stdcall ParseNSpriteVersion(DWORD dwVersion);

#endif
