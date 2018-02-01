#define CE_SUBCHIP_CPP

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
#include "cE_user.h"
#include "tjscroll.h"
#include "cE_report.h"
#include "cE_SubChip.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
CLANEntity_SubChip::CLANEntity_SubChip()
{
}

CLANEntity_SubChip::~CLANEntity_SubChip()
{
}

int CLANEntity_SubChip::Init(int Life)
{
	life = Life;
	
	return 1;
}

int CLANEntity_SubChip::Clear()
{
	return 1;
}

void CLANEntity_SubChip::Main()
{
}

void CLANEntity_SubChip::Draw()
{	
}

void CLANEntity_SubChip::menuInit(int num)
{	
}

