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
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"

#include "NpcWav.h"



CNpcWav::CNpcWav()
{
	m_nNpcWav = -1;
	ZeroMemory(m_chFileName,sizeof(m_chFileName));
}

CNpcWav::~CNpcWav()
{
}

void CNpcWav::Main()
{
	switch(m_nNpcWav)
	{
	case NPCWAVE_CALL:
		switch(m_nNpcWav2)
		{
		case 0:
			ANSdata.ret_val= -1;			
			WebDB.Resume() ;		//웹db를 재개한다.
			WebDB.GetWavFile(m_chFileName);
			m_nNpcWav2 = 1;
		case 1:
			switch(ANSdata.ret_val)
			{
			case 1:
				WebDB.Suspend();	
				m_nNpcWav2 = -1;
				m_nNpcWav = -1;
				OpenFlag = 0;
				break;
			default:
				if(ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();
					m_nNpcWav2 = -1;
					m_nNpcWav = -1;
					OpenFlag = 0;
				}
			}
		}				
		break;
	}
}

void CNpcWav::SetNpcWavNum(int num)
{
	m_nNpcWav = num;
}

void CNpcWav::SetFileName(char* FileName)
{
	if(FileName[0] == 0) return;
	ZeroMemory(m_chFileName,sizeof(m_chFileName));
	strcpy(m_chFileName,FileName);
}