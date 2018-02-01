#define NPCWAV_CPP

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우

	#include "..\\sinbaram\\SinLinkHeader.h"
	#include "..\\HoBaram\\HoLinkHeader.h"
	#include "Language\\language.h"
	#include "..\\HoBaram\\HoTextFile.h"
#endif


#include "tjclan.h"
#include "WavDown.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"



CNpcWav::CNpcWav()
{
	m_nNpcWav = -1;
}

CNpcWav::~CNpcWav()
{
}

void CNpcWav::Main()
{
	switch(m_nNpcWav)
	{
	case NPCWAVE_CALL:
		break;
	}
}