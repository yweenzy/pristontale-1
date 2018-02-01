#define CE_UPDATECLDATA_CPP

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우

#include "sinbaram\\SinLinkHeader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "Language\\language.h"
#include "HoBaram\\HoTextFile.h"
#endif

#include <stdio.h>
#include "tjclan.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "cE_Updatecldata.h"
#include "..\\ygy\\ygyheader.h"


//클랜권유받은사람이 클랜에 가입시 클랜데이타를 업데이트 하라고 명령한다.

CUpdateCldata::CUpdateCldata()
{
}

CUpdateCldata::~CUpdateCldata()
{
}


void CUpdateCldata::Updatecldata()
{
	static cnt=0;
	extern char updateis[256];
	wsprintf(updateis, "Updatecldata : %d ", cnt++);

	WebDB.Resume() ;		//웹db를 재개한다.
	WebDB.Updatcldata(cldata.szID, cldata.gserver, cldata.ChaName);
}


//auth.cpp에서 사용함.
void g_UpdateCldata_Close() //쓰레드 죽임
{
	g_UpdateCldata.Close();



	
#ifdef VOICE_CHAT
	if(bCheckClan)
	{
		if(cldata.intClanMark) {

			g_CtrlProcess.SetSelectCha(cldata.szID,cldata.ChaName,
				cldata.name,(DWORD)cldata.intClanMark, cldata.myPosition);
		}
		else {

			g_CtrlProcess.SetSelectCha(cldata.szID,cldata.ChaName,
				NULL,0, cldata.myPosition);
		}
	   //bCheckClan = FALSE;
	}
#endif


}

extern int downClanSu;		//클랜인포와 관련bmp받는 부분도 첵크서 서스팬디드함
void CUpdateCldata::Close()
{
	if(OpenFlag==0 && downClanSu==0) {	//클랜인포와 관련bmp받는 부분도 첵크서 서스팬디드함
		WebDB.Suspend();			//웹디비를 죽인다.
	}
}