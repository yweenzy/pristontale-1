#define CLAN_VIEWCLANINFO_CPP
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

#include "tjclan.h"
#include "cE_report.h"
#include "cE_CJoin.h"
#include "cE_CViewClanInfo.h"


#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"

extern char szConnServerName[16];	



CViewClanInfo::CViewClanInfo()
{
	bFlag  = FALSE;
	ClanInfo_nNum = -1;	 
	//nCheckDownLoad = 0;
	
	ZeroMemory(ClanInfo,sizeof(CLANINFO)*CLAN_MAX);
	ZeroMemory(szClanMarkNum,sizeof(szClanMarkNum));

	//InitializeCriticalSection(&cs);

	//if(!SearchDirectory()) {
	//	MakeDirectory();	
	//}
}
	
CViewClanInfo::~CViewClanInfo()
{
	int i;
	for(i=0; i<CLAN_MAX; i++)
	{
#ifdef USE_PROSTONTALE
		if(ClanInfo[i].hClanMark){
			ClanInfo[i].hClanMark->Release();
			ClanInfo[i].hClanMark = NULL;
		}

		if(ClanInfo[i].hClanMark32){
			ClanInfo[i].hClanMark32->Release();
			ClanInfo[i].hClanMark32 = NULL;
		}
#else
		DeleteObject(ClanInfo[i].hClanMark);
#endif
	}

	//DeleteCriticalSection(&cs);
}













//1. info용 메모리에 있는지 검사
//2. 하드에 있는지 검사(*.rep파일, *.bmp(32*32, 16*16)중 한개라도 없으면 다운받아야함)
//3. 없으면 다운로드
//4. 전과정에 번호리턴
int CViewClanInfo::readFILE_ClanInfo(DWORD clanNum)
{
	char GServer[4];
	char ClanUnique[64];
	char szClanNum[64];
	char szTemp[256];
	int nClanMarklen =0;

	CLANINFO *pCL = &ClanInfo[0];
	int nCount =0;
	ZeroMemory(szClanNum,sizeof(szClanNum));
	ZeroMemory(GServer,sizeof(GServer));
	ZeroMemory(ClanUnique,sizeof(ClanUnique));

	for(int i = 0; i < CLAN_MAX; i++, pCL++)
	{	
		if((pCL->nStatus == 0) || pCL->nStatus ==3 ) 
		{
			nCount = i;
			
			break;
		}
	}

	//itoa(clanNum,szClanNum,10);
	wsprintf(szClanNum,"%u",clanNum);

	nClanMarklen = lstrlen(szClanNum);

	if(nClanMarklen == 9) {
		GServer[0] = szClanNum[0];
		
		strcpy(ClanUnique,&szClanNum[3]);
	}
	else{
		GServer[0] = szClanNum[0];
		GServer[1] = szClanNum[1];
		strcpy(ClanUnique,&szClanNum[4]);
	}

	//GServer = szClanNum[0];
	//strcpy(ClanUnique,&szClanNum[3]);

	
	#ifdef  USE_PROSTONTALE	
	ClanInfo[nCount].dwTime = GetCurrentTime();
	wsprintf(szTemp,"%s\\%s\\%s_%s.rep",CLANINFO_DIR,szConnServerName,GServer,ClanUnique);
	/*
	//ktj : 원본
	FILE *fp;
	fp = fopen(szTemp,"rb");
	fread(&ClanInfo[nCount].ClanInfoHeader,sizeof(CLANINFOHEADER),1,fp);
	fclose(fp);
	*/

	//ktj : 고친것
	HANDLE hFile;
	DWORD dwRead;
	hFile = CreateFile( szTemp, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile != INVALID_HANDLE_VALUE ) {
		
		ReadFile(hFile,&ClanInfo[nCount].ClanInfoHeader,sizeof(CLANINFOHEADER),  &dwRead,NULL);
		CloseHandle(hFile);
	}


	wsprintf(szTemp,"%s\\%s\\%s_%s_16.%s",CLANINFO_DIR,szConnServerName,GServer,ClanUnique,SAVE_EXE);
	
	if(ClanInfo[nCount].hClanMark != NULL)
	{
		ClanInfo[nCount].hClanMark->Release();
		ClanInfo[nCount].hClanMark = NULL;
	}

	if(ClanInfo[nCount].hClanMark32 != NULL)
	{
		ClanInfo[nCount].hClanMark32->Release();
		ClanInfo[nCount].hClanMark32 = NULL;
	}

	ClanInfo[nCount].hClanMark = LoadDibSurfaceOffscreen(szTemp);
	if(ClanInfo[nCount].hClanMark != NULL){
		ClanInfo[nCount].nStatus =2;
		return nCount;
	}
	else return 0;
	#else
	ClanInfo[nCount].dwTime = GetCurrentTime();
	wsprintf(szTemp,"%s\\%s\\%s_%s.rep",CLANINFO_DIR,szConnServerName,GServer,ClanUnique);
	FILE *fp;
	fp = fopen(szTemp,"rb");
	fread(&ClanInfo[nCount].ClanInfoHeader,sizeof(CLANINFOHEADER),1,fp);
	fclose(fp);
	wsprintf(szTemp,"%s\\%s\\%s_%s_16.%s",CLANINFO_DIR,szConnServerName,GServer,ClanUnique,SAVE_EXE);
	ClanInfo[nCount].hClanMark  = (HBITMAP)LoadImage(NULL,szTemp,
						IMAGE_BITMAP,
						0,0,LR_LOADFROMFILE);	
	if(ClanInfo[nCount].hClanMark != NULL){
		ClanInfo[nCount].nStatus =2;
		return nCount;
	}
	else return 0;

	

	#endif

#ifdef CLAN_DEBUG
	DebugMessage("CViewClanInfo::readFILE_ClanInfo(클랜번호 : %d)",clanNum);
#endif

	

	return nCount;
}

int CViewClanInfo::Search_Memory(char *clanNum)
{
	CLANINFO *pCL = &ClanInfo[0];

	struct clanMarkNUMS{
		char gn[2];
		char cnt[2];
		char cNum[6];
		char notuse;
	};
	union Uni_cl{
		char buf[100];
		clanMarkNUMS cl;
	};
	Uni_cl uni_cl;


	int l = strlen(clanNum);

	//strcpy(uni_cl.buf, clanNum);
	char buf[10];
	int nstr = lstrlen(clanNum);
	if(l>= 10)
	{
		uni_cl.cl.gn[0] = clanNum[0];
		uni_cl.cl.gn[1] = clanNum[1];
		uni_cl.cl.cnt[0] = clanNum[2];
		uni_cl.cl.cnt[1] = clanNum[3];
		strcpy(uni_cl.cl.cNum , &clanNum[4]);
	}
	else
	{
		uni_cl.cl.gn[0] = clanNum[0];		
		uni_cl.cl.cnt[0] = clanNum[1];
		uni_cl.cl.cnt[1] = clanNum[2];
		strcpy(uni_cl.cl.cNum , &clanNum[3]);
	}
	if(l>= 10)
	{
		buf[0] = uni_cl.cl.gn[0];
		buf[1] = uni_cl.cl.gn[1];
	}
	else
	{
		buf[0] = uni_cl.cl.gn[0];
		buf[1] = 0;
	}
	int  gn = atoi(buf);
	buf[0] = uni_cl.cl.cnt[0]; 
	buf[1] = uni_cl.cl.cnt[1]; 
	buf[2] = 0;
	int  cnt = atoi(buf);
	int  int_Cmark = atoi(uni_cl.cl.cNum);

	
	//1. 메모리에 있는지 체크
	for(int i = 0; i < CLAN_MAX; i++, pCL++)
	{	
		if(pCL->nStatus == 0) continue;

		int l2 = strlen(pCL->ClanInfoHeader.ClanMark_Num);

		if(l==l2 &&  strcmp(pCL->ClanInfoHeader.ClanMark_Num, clanNum)==0)
		{
			pCL->dwTime = GetCurrentTime();
			return (0x8000 | i);				//메모리에 있으며 데이타도 같다.
		}


		l = lstrlen(pCL->ClanInfoHeader.ClanMark_Num);
		if(l>= 10)
		{
			uni_cl.cl.gn[0] = pCL->ClanInfoHeader.ClanMark_Num[0];
			uni_cl.cl.gn[1] = pCL->ClanInfoHeader.ClanMark_Num[1];
			uni_cl.cl.cnt[0] = pCL->ClanInfoHeader.ClanMark_Num[2];
			uni_cl.cl.cnt[1] = pCL->ClanInfoHeader.ClanMark_Num[3];
			strcpy(uni_cl.cl.cNum , &pCL->ClanInfoHeader.ClanMark_Num[4]);
		}
		else
		{
			uni_cl.cl.gn[0] = pCL->ClanInfoHeader.ClanMark_Num[0];		
			uni_cl.cl.cnt[0] = pCL->ClanInfoHeader.ClanMark_Num[1];
			uni_cl.cl.cnt[1] = pCL->ClanInfoHeader.ClanMark_Num[2];
			strcpy(uni_cl.cl.cNum , &pCL->ClanInfoHeader.ClanMark_Num[3]);
		}
		//strcpy(uni_cl.buf, pCL->ClanInfoHeader.ClanMark_Num);
		if(l>= 10)
		{
			buf[0] = uni_cl.cl.gn[0];
			buf[1] = uni_cl.cl.gn[1];
		}
		else
		{
			buf[0] = uni_cl.cl.gn[0];
			buf[1] = 0;
		}
		
		int  gn2 = atoi(buf);
		buf[0] = uni_cl.cl.cnt[0];
		buf[1] = uni_cl.cl.cnt[1];
		buf[2] = 0;
		int  cnt2 = atoi(buf);
		int  int_Cmark2 = atoi(uni_cl.cl.cNum);

		if(l==l2 &&  int_Cmark== int_Cmark2 )
		{
			pCL->dwTime = GetCurrentTime();
			return (0xC000 | i);				//메모리에 있는데 데이타가 틀리므로
												//현재 메모리에 새로 다운로드 받을것
		}
	}

	return 0;
}


//1.*rep가 있는지 체크 
//2.비트맵이 없으면 처음부터 다운
int CViewClanInfo::Search_Files(char *clanNum)
{
	char GServer[4];
	char szClanNum[64];
	char szTemp[256];
	int nClanNum;
	int nClanNum1;
	int nClanMarklen = 0;
	CLANINFOHEADER claninfoheader;

	CLANINFO *pCL = &ClanInfo[0];

	nClanNum = atoi(clanNum);
   
	//FILE *fp;


	//GServer = clanNum[0];
	//strcpy(szClanNum,&clanNum[3]);

	nClanMarklen = lstrlen(clanNum);
	ZeroMemory(GServer,sizeof(GServer));
	ZeroMemory(szClanNum,sizeof(szClanNum));	

	if(nClanMarklen == 9) {
		GServer[0] = clanNum[0];
		strcpy(szClanNum,&clanNum[3]);
	}
	else{
		GServer[0] = clanNum[0];
		GServer[1] = clanNum[1];
		strcpy(szClanNum,&clanNum[4]);
	}




	wsprintf(szTemp,"%s\\%s\\%s_%s.rep",CLANINFO_DIR,szConnServerName,GServer,szClanNum);
	/*
	//ktj : 원본
	fp = fopen(szTemp,"rb");
	if(fp > 0){
		fread(&claninfoheader,sizeof(CLANINFOHEADER),1,fp);
		fclose(fp);
	*/


	//ktj : 고친것

	HANDLE hFile;
	DWORD dwRead;
	hFile = CreateFile( szTemp, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile != INVALID_HANDLE_VALUE ) {
		ReadFile(hFile, &claninfoheader,sizeof(CLANINFOHEADER),  &dwRead,NULL);
		CloseHandle(hFile);


		nClanNum1 = atoi(claninfoheader.ClanMark_Num);
		if(nClanNum != nClanNum1){			
			return 0;
		}
		else{	
			#ifdef  USE_PROSTONTALE
			wsprintf(szTemp,"%s\\%s\\%s_%s_16.%s",CLANINFO_DIR,szConnServerName,GServer,szClanNum,SAVE_EXE);
			DIRECTDRAWSURFACE ld = NULL;
			ld = LoadDibSurfaceOffscreen(szTemp);
			if(ld != NULL){

				ld->Release();
				ld = NULL;

				return 1;
			}
			else return 0;
			#else
			wsprintf(szTemp,"%s\\%s\\%s_%s_16.%s",CLANINFO_DIR,szConnServerName,GServer,szClanNum,SAVE_EXE);
			HBITMAP ld = NULL;
			ld = (HBITMAP)LoadImage(NULL,szTemp,
						IMAGE_BITMAP,
						0,0,LR_LOADFROMFILE);	
			
			if(ld != NULL){

				

				DeleteObject(ld);
				
				ld = NULL;

				return 1;
			}
			else return 0;
			#endif
	
		}
	}
	
	return 0;
}


int CViewClanInfo::SearchClan(DWORD dwClanNum )//char *MarkNum)
{

    char ClanMarkNum[100];

    char GServer[3];
	char szNum[64];
    int i;
    ZeroMemory(ClanMarkNum,sizeof(char)*100);
    
	
	sprintf(ClanMarkNum,"%u",dwClanNum);	
	if(ClanMarkNum== NULL) return 0;
	int nStr = lstrlen(ClanMarkNum);
	if(nStr >=10)
	{
		GServer[0] = ClanMarkNum[0];
		GServer[1] = ClanMarkNum[1];
		strcpy(szNum,&ClanMarkNum[4]);
	}
	else
	{
		

		GServer[0] = ClanMarkNum[0];
		strcpy(szNum,&ClanMarkNum[3]);
	}

	
	
	

	ClanInfo_nNum = -1;
	bFlag = FALSE;	


	


	//1. 메모리에 있는지 체크
	i = Search_Memory(ClanMarkNum);
	if(i != 0) {							
		int chk = (i >> 8);
		if(chk==0x80) {						//인포가 있는 메모리의 번호
			ClanInfo_nNum = (i & 0x0fff);
			return 1;
		}
		if(chk==0xC0) {						//인포는있으나 버전이 틀려 다운받아야하는 번호
			int infoN = i & 0x0fff;
			DownLoadClanInfo(infoN , dwClanNum);
			ClanInfo_nNum = infoN ;
			return 1;
		}
	}

	//2. 파일에서 찾는다.
	i = Search_Files(ClanMarkNum);
	if(i == 1) {							
								//파일이 있어 로드함.
			//===============================================
			//파일에서 로드하는 함수를 받을것
			ClanInfo_nNum = readFILE_ClanInfo(dwClanNum);
			//===============================================
			return 1;
		}
	else	{					//파일이 있으나 버전이 틀려 다운받아야함.
			ClanInfo_nNum  = DownLoadClanInfo(-1, dwClanNum);
			return 1;
		
	}

	//3. 1,2에서 못찾아서 다운받아야한다.
	ClanInfo_nNum = DownLoadClanInfo(-1, dwClanNum);		//-1은 다운받을 버퍼를 찾아 리턴해줄것을 명령함.
	return 0;








	/*
	if(i == 100)
	{
		SortDelete();
		ClanInfo_nNum = nLowTime;
	}
	*/



	/*

	wsprintf(szTemp,"%s\\%s\\%c_%s.rep",CLANINFO_DIR,szConnServerName,GServer,szNum);
	fp = fopen(szTemp,"rb");
	if(fp > 0){
		fread(&claninfoheaer,sizeof(CLANINFOHEADER),1,fp);
		fclose(fp);

		nClanNum = atoi(claninfoheaer.ClanMark_Num);
		if(nClanNum != dwClanNum){
			bFlag = FALSE;	
			return 0;
		}
	}
	else{

		for(i = 0; i < CLAN_MAX; i++)
		{		
			//if(strcmp(ClanInfo[i].ClanInfoHeader.ClanMark_Num,   MarkNum) == 0)
			if(ClanInfo[i].ClanInfoHeader.nClanMark == dwClanNum )
			{
				if(ClanInfo[i].nStatus != 1) ClanInfo[i].nStatus = 2;
				
				ClanInfo[i].dwTime = GetCurrentTime();
				//
				bFlag = TRUE;
				ClanInfo_nNum = i;
				ClanInfo[i].nSaveNum = i;
				break;
			}

			if((ClanInfo[i].ClanInfoHeader.nClanMark  == 0) &&(ClanInfo[i].nStatus !=1)){

				ClanInfo[i].dwTime = GetCurrentTime();
				ClanInfo[i].nStatus = 0;			//다운받아야함.
				ClanInfo_nNum = i;
				ClanInfo[i].nSaveNum = i;
				break;
			}
			
		}


		return 0;
	}
	*/


	
	
	/*
	if(!bFlag){
		

		FILE *fp;
		
		ZeroMemory(szTemp,sizeof(szTemp));
		wsprintf(szTemp,"%s\\%s\\%c_%s.rep",CLANINFO_DIR,szConnServerName,GServer,szNum);
		fp = fopen(szTemp,"rb");
		if(fp <= 0) 
		{
		}else{
			fread(&ClanInfo[ClanInfo_nNum].ClanInfoHeader,sizeof(CLANINFOHEADER),1,fp);
			fclose(fp);

			wsprintf(szTemp,"%s\\%s\\%c_%s_16.%s",CLANINFO_DIR,szConnServerName,GServer,szNum,SAVE_EXE);

	#ifdef  USE_PROSTONTALE
			ClanInfo[ClanInfo_nNum].hClanMark = LoadDibSurfaceOffscreen(szTemp);
	#else			
			ClanInfo[ClanInfo_nNum].hClanMark = (HBITMAP)LoadImage(NULL,szTemp,
						IMAGE_BITMAP,
						0,0,LR_LOADFROMFILE);	
	#endif			

			if(ClanInfo[ClanInfo_nNum].hClanMark  == NULL){
				ClanInfo[ClanInfo_nNum].nStatus = 0;

				//ZeroMemory(&ClanInfo[ClanInfo_nNum].ClanInfoHeader,sizeof(CLANINFOHEADER));

			}
			else{
				ClanInfo[ClanInfo_nNum].dwTime = GetCurrentTime();
				ClanInfo[ClanInfo_nNum].nStatus = 2;	
				bFlag = TRUE;
			}
		}
		//fread(&ClanInfoheader,sizeof(CLANINFOHEADER),1,fp);
		
		//memcpy(&ClanInfo[ClanInfo_nNum].ClanInfoHeader ,&ClanInfoheader,sizeof(CLANINFOHEADER));
	}

	if(!bFlag)
	{
		strcpy(ClanInfo[ClanInfo_nNum].ClanInfoHeader.ClanMark_Num,ClanMarkNum);
		ClanInfo[ClanInfo_nNum].ClanInfoHeader.nClanMark = dwClanNum ;
	}
	*/
	return 0;
}



//ktj : 다운중인 갯수첵크
int downClanSu = 0;
void is_allDown()					//rep, bmp를 다운받는게 모두 끝났다면 Suspend를 해주어야함.
{
	if(OpenFlag==0 && downClanSu==0) {
			WebDB.Suspend();			//웹디비를 죽인다.
	}
}


void debug_fd2( char *fmt, ...);




//2로 설정해 다운이 완료됐음을 알려준다.
int clanINFO_result2(int ret_code, char *marknum,CLANINFO *ci)
{
#ifdef CLAN_DEBUG
	DebugMessage("clanINFO_result2에서 클랜마크 읽어옴(클랜번호 : %s)",marknum);
#endif
	char szTemp[256];
	 wsprintf(szTemp,"%s\\%s\\%s_%s_16.%s",CLANINFO_DIR,szConnServerName,ci->ClanInfoHeader.Gserver,
				ci->ClanInfoHeader.UniqueClaClanInfo_nNum,SAVE_EXE);

#ifdef  USE_PROSTONTALE
	 if(ci->hClanMark != NULL){
		ci->hClanMark->Release();
		ci->hClanMark = NULL;
	}
	 ci->hClanMark = LoadDibSurfaceOffscreen(szTemp);
#else
#endif

	//downClanSu--;
	//is_allDown();

	return 0;
	
}

//rep,cl파일이 모두 다운된 후에 읽혀진다.
int clanINFO_Load32X32(int clinfo_n)
{
#ifdef CLAN_DEBUG
	DebugMessage("clanINFO_Load32X32에서32x32 클랜마크 읽어옴(클랜 인포 번호 : %d)",clinfo_n);
#endif

	CLANINFO *ci = &ClanInfo[clinfo_n];

	char szTemp[256];
	 wsprintf(szTemp,"%s\\%s\\%s_%s.%s",CLANINFO_DIR,szConnServerName,ci->ClanInfoHeader.Gserver,
				ci->ClanInfoHeader.UniqueClaClanInfo_nNum,SAVE_EXE);

	if(ci->hClanMark32 != NULL)
	{
		ci->hClanMark32->Release();
		ci->hClanMark32 = NULL;
	}
	 ci->hClanMark32 = LoadDibSurfaceOffscreen(szTemp);
	 return 0;
}


/*
int clanINFO_result2(int ret_code, char *marknum,CLANINFO *ci)
{
	char szTemp[64];
	if(ret_code != 1) {
		goto errorjmp;
	}

	int i=0; 
	

	//메모리에 있는지 체크
	//for(i = 0; i < CLAN_MAX; i++)
	//{		
	//	if(strcmp(ClanInfo[i].ClanInfoHeader.ClanMark_Num,   marknum) == 0)
	//	{
	ci->dwTime = GetCurrentTime();
	ci->nStatus = 2;	

			

			//ygy : 비트맵 로드하기
	wsprintf(szTemp,"%s\\%s\\%c_%s_16.cl",CLANINFO_DIR,szConnServerName,ci->ClanInfoHeader.Gserver,ci->ClanInfoHeader.UniqueClaClanInfo_nNum);

#ifdef  USE_PROSTONTALE
	if(ci->hClanMark != NULL){
		ci->hClanMark->Release();
		ci->hClanMark = NULL;
	}			

	ci->hClanMark = LoadDibSurfaceOffscreen(szTemp);
	

	
	
			
			


#else		
			
			ClanInfo[i].hClanMark = (HBITMAP)LoadImage(NULL,wsprintf(szTemp,"%s\\%s\\%c_%s.%s",CLANINFO_DIR,szConnServerName,ClanInfo[i].ClanInfoHeader.Gserver,
				ClanInfo[i].ClanInfoHeader.UniqueClaClanInfo_nNum,SAVE_EXE);szTemp,
				IMAGE_BITMAP,
				0,0,LR_LOADFROMFILE);	
			if(!bcldataclanmark){
				if(!cldata.hClanMark) cldata.hClanMark = (HBITMAP)LoadImage(NULL,szTemp,
				IMAGE_BITMAP,
				0,0,LR_LOADFROMFILE);
				

				if(!cldata.hClanMark16){
					wsprintf(szTemp,"%s\\%s\\%c_%s_16.%s",CLANINFO_DIR,szConnServerName,ClanInfo[i].ClanInfoHeader.Gserver,
						ClanInfo[i].ClanInfoHeader.UniqueClaClanInfo_nNum,SAVE_EXE);
					cldata.hClanMark16 = (HBITMAP)LoadImage(NULL,szTemp,
				IMAGE_BITMAP,
				0,0,LR_LOADFROMFILE);
				}
				bcldataclanmark = TRUE;
			}

			FILE *fp;
			CLANINFOHEADER claninfoheader;
			ZeroMemory(szTemp,sizeof(szTemp));

			wsprintf(szTemp,"%s\\%s\\%c_%s.rep",CLANINFO_DIR,szConnServerName,ClanInfo[i].ClanInfoHeader.Gserver,ClanInfo[i].ClanInfoHeader.UniqueClaClanInfo_nNum);
			fp = fopen(szTemp,"rb");
			if(fp > 0){
				fread(&claninfoheader,sizeof(CLANINFOHEADER),1,fp);
				fclose(fp);

				memcpy(&ClanInfo[i].ClanInfoHeader,&claninfoheader,sizeof(claninfoheader));


			}
			
#endif			





	debug_fd2( "clanINFO_result2 시작====================================00 ");
	int i2;
	for(i2=0; i2<100; i2++) {
		if(ClanInfo[i2].nStatus==0) continue;

		char buf[256];
		wsprintf(buf, "ClanInfo[%d] %s %s %s ", i2, 
				ClanInfo[i2].ClanInfoHeader.ClanMark_Num,
				ClanInfo[i2].ClanInfoHeader.ClanName,
				ClanInfo[i2].ClanInfoHeader.ClanReport);
		debug_fd2( buf);
	}
	debug_fd2( "clanINFO_result2 끝====================================00 ");




			//ktj : 다운중인 갯수첵크
			downClanSu--;

			//=======================================================================
			is_allDown();		//ktj : 임시
			//=======================================================================
			return 1;
		}
	}

errorjmp:

	//debug_fd2( "clanINFO_result2 이건 에러 ");


	//잘못된 데이타가 들어와도 쓰레드는 멈춰야하므로..
	downClanSu--;
	is_allDown();
	return 0;
}
*/

BOOL bViewClanInfoDown = FALSE;
int CViewClanInfo::DownLoadClanInfo(int num,DWORD dwClanNum )
{	

	int nNum;
	char MarkNum[64];
	wsprintf(MarkNum, "%u", dwClanNum );

	//ktj : 웹디비 ============================================== start
	nCheckDownLoad = 1;
	CLANINFO *pCL = &ClanInfo[0];		
	

	bViewClanInfoDown = TRUE;

	if(num < 0)
	{
		int i = 0;
		for(i = 0; i < CLAN_MAX; i++, pCL++)
		{	
			if((pCL->nStatus == 0) || pCL->nStatus ==3 ) 			
			{
				nNum = i;
				pCL->nStatus= 1; //다운로드 수행중
				strcpy(pCL->ClanInfoHeader.ClanMark_Num, MarkNum);
				break;
			}
		}

		if(i == CLAN_MAX)
		{
			SortDelete();
			nNum = nLowTime;
		}
	}
	else nNum = num;
	WebDB.Suspend();
	WebDB.Resume();		//웹db를 재개한다.

	
	

	WebDB.ReadClanInfo(MarkNum,  &ClanInfo[nNum]);		//이 id가 클랜원인지를 파악한다.

	//ktj : 다운중인 갯수첵크
	downClanSu++;
	//ktj : 웹디비 ============================================== end

#ifdef CLAN_DEBUG
	DebugMessage("DownLoadClanInfo(%d,클랜번호 : %d )에서 클랜정보를 다운 받음",num,dwClanNum);
#endif

	return nNum;
}



void CViewClanInfo::Main()
{
}




char* clanINFO_result(char *marknum,char *szInfo,CLANINFO* ci)
{
	debug_fd2( "clanINFO_result marknum %s ", marknum);
	return g_ViewClanInfo.AddClanInfo(marknum,szInfo,ci);
}


char* CViewClanInfo::AddClanInfo(char *marknum,char *szInfo,CLANINFO* ci)
{	
	char szClanReport[90];
	char szTemp[100];
	BOOL bFlag = FALSE;
	//char Gserver;
	//char UniqueClanNum[100];
	HANDLE hFile = NULL;
	DWORD dwWrite;
	int nClanMarklen =0;

	//int nMarkNum,nMarkNum1;
	//int ClanNum;
	//int ClanNum1;

	//int i;

	//ZeroMemory(szClanReport,sizeof(szClanReport));
	//ZeroMemory(szTemp,sizeof(szTemp));

	//if(szInfo == NULL) return NULL;

	//nMarkNum1 = atoi(marknum);
	//ClanNum1 = atoi(&marknum[3]);

	/*for(i = 0; i < CLAN_MAX; i++){
		if(ci->ClanInfoHeader.ClanMark_Num[0] == 0) {
			bFlag = TRUE;
			break;
		}

		//nMarkNum = atoi(ci[i].ClanInfoHeader.ClanMark_Num);
		ClanNum = atoi(ci->ClanInfoHeader.UniqueClaClanInfo_nNum);

		if(ClanNum1 == ClanNum)
		{			
			bFlag = TRUE;
			break;			
		}

		//if(strcmp(ci[i].ClanInfoHeader.ClanMark_Num,marknum) == 0)
		
		
	}*/

	//if(bFlag)
	//{
		//ZeroMemory(ci[i].ClanInfoHeader.ClanName,sizeof(ci[i].ClanInfoHeader.ClanName));
		//ZeroMemory(ci[i].ClanInfoHeader.ClanReport,sizeof(ci[i].ClanInfoHeader.ClanReport));
		ci->ClanInfoHeader.nClanMark = atoi(marknum);
		chk_readStrBuf("CName=", szInfo, ci->ClanInfoHeader.ClanName);
		
		//chk_readStrBuf("CNote=", szInfo, ci[i].ClanInfoHeader.ClanReport);			
		ParsingData("CNote=", szInfo, ci->ClanInfoHeader.ClanReport);
		
		strcpy(szClanReport,ci->ClanInfoHeader.ClanReport);
		strcpy(ci->ClanInfoHeader.ClanMark_Num,marknum);			
		
		//ci->ClanInfoHeader.Gserver = ci->ClanInfoHeader.ClanMark_Num[0];
		//strcpy(ci->ClanInfoHeader.UniqueClaClanInfo_nNum,&ci->ClanInfoHeader.ClanMark_Num[3]);

		nClanMarklen = lstrlen(ci->ClanInfoHeader.ClanMark_Num);

		if(nClanMarklen == 9) {
			ci->ClanInfoHeader.Gserver[0] = ci->ClanInfoHeader.ClanMark_Num[0];
			strcpy(ci->ClanInfoHeader.UniqueClaClanInfo_nNum,&ci->ClanInfoHeader.ClanMark_Num[3]);
		}
		else{
			ci->ClanInfoHeader.Gserver[0] = ci->ClanInfoHeader.ClanMark_Num[0];
			ci->ClanInfoHeader.Gserver[1] = ci->ClanInfoHeader.ClanMark_Num[1];
			strcpy(ci->ClanInfoHeader.UniqueClaClanInfo_nNum,&ci->ClanInfoHeader.ClanMark_Num[4]);
		}
		
		ci->dwTime = GetCurrentTime();			
		
		wsprintf(szTemp,"%s\\%s\\%s_%s.rep",CLANINFO_DIR,szConnServerName,ci->ClanInfoHeader.Gserver,ci->ClanInfoHeader.UniqueClaClanInfo_nNum);
		hFile = CreateFile( szTemp, GENERIC_WRITE, FILE_SHARE_WRITE,
						NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

		if( hFile != INVALID_HANDLE_VALUE ) {        
			WriteFile( hFile , &ci->ClanInfoHeader, sizeof(CLANINFOHEADER), &dwWrite , NULL );        
			CloseHandle( hFile );
		}

		//ClanInfo_nNum = i;

	//}


	/*
	debug_fd2( "ViewClanInfo 시작====================================00 ");
	int i2;
	for(i2=0; i2<100; i2++) {
		if(ClanInfo[i2].nStatus==0) continue;

		char buf[256];
		wsprintf(buf, "ClanInfo[%d] %s %s %s ", i2, 
				ClanInfo[i2].ClanInfoHeader.ClanMark_Num,
				ClanInfo[i2].ClanInfoHeader.ClanName,
				ClanInfo[i2].ClanInfoHeader.ClanReport);
		debug_fd2( buf);
	}
	debug_fd2( "ViewClanInfo 끝====================================00 ");
	*/

#ifdef CLAN_DEBUG
		DebugMessage("AddClanInfo()호출 마크번호 : %s",marknum);
#endif
    return ci->ClanInfoHeader.ClanName;

}

//웹 db에서 온 스트링에서 원하는 스트링을 뽑아냄.
int CViewClanInfo::chk_readStrBuf(char *cmd, char *readbuf, char *retBuf)
{
	int iRejectCode = -1;			//1은 제대로 들어온것임.
	char *pBuf;

	pBuf = strstr(readbuf,cmd);
    if( pBuf == NULL)	//발견할 수 없었다.
	{
		return iRejectCode ;
	}

	pBuf = pBuf + strlen( cmd );
	while(1) {			//스페이스를 없앤다.
		if(*pBuf == '\n') return 0;
		if(*pBuf != ' ') break;
		pBuf ++;
	}
	sscanf( pBuf , "%s", retBuf );

	return iRejectCode;
}

void CViewClanInfo::ParsingData(char* cmd, char* data, char* save)
{	
	char *pBuf;
	int nCount = 0;
	char szTemp[500];
	ZeroMemory(szTemp,sizeof(char)*500);
	pBuf = strstr(data,cmd);
	pBuf = pBuf + strlen( cmd );
	strcpy(szTemp,pBuf);
    if( pBuf == NULL)	//발견할 수 없었다.
	{
		return;
	}

	pBuf = pBuf + strlen( cmd );
		while(1) {			//스페이스를 없앤다.		
		
		if(szTemp[nCount] == '\r') break;		
		save[nCount] = szTemp[nCount];
		nCount++;
		
	}
	
}

void CViewClanInfo::SortDelete()
{
	int i;
	DWORD dwTimeSave;
	nLowTime = 0;
	dwTimeSave = ClanInfo[0].dwTime;
	for(i = 1; i < CLAN_MAX; i++)
	{
		if(ClanInfo[i].dwTime < dwTimeSave)
		{
			dwTimeSave = ClanInfo[i].dwTime;
			nLowTime = i;
		}
	}
#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우
	if(ClanInfo[nLowTime].hClanMark !=NULL){

		ClanInfo[nLowTime].hClanMark->Release();
		ClanInfo[nLowTime].hClanMark = NULL;
	}
#else
	if(ClanInfo[nLowTime].hClanMark !=NULL){

		DeleteObject(ClanInfo[nLowTime].hClanMark);
		
	}
#endif
	ZeroMemory(&ClanInfo[nLowTime],sizeof(CLANINFO));
}


BOOL CViewClanInfo::SearchDirectory()
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;	
	char t[50];
	wsprintf(t,"%s\\*.dat",CLANINFO_DIR);
	hFind = FindFirstFile(t,&wfd);
	if(hFind == INVALID_HANDLE_VALUE)
	{		
		return FALSE;
	}	

	return TRUE;	
}

void CViewClanInfo::MakeDirectory()
{
	//char szTemp[100];
	//FILE* FileWrite;
	
	CreateDirectory(CLANINFO_DIR,NULL);

	/*
	//ktj : 이게 뭐다냐?????
	memset(szTemp,0,sizeof(szTemp));
	wsprintf(szTemp,"%s\\%s",CLANINFO_DIR,".dat");
	FileWrite = fopen( szTemp , "wb" );
	fwrite( szTemp, sizeof(szTemp) , 1, FileWrite );
	fclose(FileWrite);
	*/
}

void CViewClanInfo::LoadData()
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;	
	char szFile[100];
	char szFileName[100];
	BOOL bReturn = FALSE;
	BOOL bNext_Folder = TRUE;
	int nCount = 0;	

	ZeroMemory(szFile,sizeof(szFile));

	while(1)
	{
		wsprintf(szFile,"%s\\*.rep",CLANINFO_DIR);
		if(bNext_Folder == TRUE)
		{
			hFind = FindFirstFile(szFile,&wfd);
			if(hFind == INVALID_HANDLE_VALUE)
			{
				break;
			}
		}
		bNext_Folder = FALSE;		
		memset(szFileName,0,sizeof(szFileName));
		wsprintf(szFileName,"%s\\%s",CLANINFO_DIR,wfd.cFileName);				
		ReadToFile(szFileName,nCount);
		bReturn = FindNextFile(hFind,&wfd);
		
		if(!bReturn)
		{
			break;
		}		
		nCount++;
	}

	bReturn = FALSE;
	bNext_Folder = TRUE;
	nCount = 0;

	while(1)
	{
		wsprintf(szFile,"%s\\*.bmp",CLANINFO_DIR);
		if(bNext_Folder == TRUE)
		{
			hFind = FindFirstFile(szFile,&wfd);
			if(hFind == INVALID_HANDLE_VALUE)
			{
				break;
			}
		}
		bNext_Folder = FALSE;		
		memset(szFileName,0,sizeof(szFileName));
		wsprintf(szFileName,"%s\\%s",CLANINFO_DIR,wfd.cFileName);				
		ReadToImage(szFileName,nCount);
		bReturn = FindNextFile(hFind,&wfd);
		
		if(!bReturn)
		{
			break;
		}		
		nCount++;
	}
}

void CViewClanInfo::ReadToFile(char *file,int count)
{
	/*
	//ktj : 원본
	FILE *fp;
	fp = fopen(file,"rb");
	fread(&ClanInfo[count].ClanInfoHeader,sizeof(CLANINFOHEADER),1,fp);
	fclose(fp);
	*/


	//ktj : 고친것
	HANDLE hFile;
	DWORD dwRead;
	hFile = CreateFile( file, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile != INVALID_HANDLE_VALUE ) 
	{
		ReadFile(hFile,&ClanInfo[count].ClanInfoHeader,sizeof(CLANINFOHEADER),  &dwRead,NULL);
		CloseHandle(hFile);
	}
	
}

void CViewClanInfo::ReadToImage(char *file,int count)
{	
					
	#ifdef  USE_PROSTONTALE
	ClanInfo[count].hClanMark = LoadDibSurfaceOffscreen(file);					
	#else			
	ClanInfo[count].hClanMark = (HBITMAP)LoadImage(NULL,file,
				IMAGE_BITMAP,
				0,0,LR_LOADFROMFILE);
	
	#endif					
}


BOOL CViewClanInfo::CheckWhere(char *MarkNum)
{ 

	char ClanMarkNum[64];
	strcpy(ClanMarkNum,MarkNum);
	char szTemp[64];	
	//FILE *fp;
	wsprintf(szTemp,"%s\\%c_%s.rep",ClanMarkNum[0],ClanMarkNum[3]);
	/*
	//ktj : 원본
	fp = fopen(szTemp,"r");
	if(fp < 0) return FALSE;
	fwrite(&ClanInfo[ClanInfo_nNum].ClanInfoHeader,sizeof(CLANINFOHEADER),1,fp);
	fclose(fp);
	*/

	//ktj : 고친것
	HANDLE hFile;
    DWORD dwAcess =0;
    hFile = CreateFile( szTemp, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

    if( hFile != INVALID_HANDLE_VALUE ) {
        SetFilePointer( hFile , 0 , NULL , FILE_END );
        //데이타 쓰기     버퍼    쓸크기    실제로 쓰여진 바이트수
        int chk = WriteFile( hFile , &ClanInfo[ClanInfo_nNum].ClanInfoHeader,sizeof(CLANINFOHEADER) , &dwAcess , NULL );
        //파일 닫기
        CloseHandle( hFile );
    }


	


	wsprintf(szTemp,"%s\\%c_%s.bmp",ClanMarkNum[0],ClanMarkNum[3]);

#ifdef  USE_PROSTONTALE
	ClanInfo[ClanInfo_nNum].hClanMark = LoadDibSurfaceOffscreen(szTemp);					
#else			
	ClanInfo[ClanInfo_nNum].hClanMark = (HBITMAP)LoadImage(NULL,szTemp,
				IMAGE_BITMAP,
				0,0,LR_LOADFROMFILE);	
#endif			

	if(ClanInfo[ClanInfo_nNum].hClanMark  == NULL){
		ZeroMemory(&ClanInfo[ClanInfo_nNum].ClanInfoHeader,sizeof(CLANINFOHEADER));
		return FALSE;
	}

	ClanInfo[ClanInfo_nNum].dwTime = GetCurrentTime();
	ClanInfo[ClanInfo_nNum].nStatus = 2;	

	return TRUE;
}