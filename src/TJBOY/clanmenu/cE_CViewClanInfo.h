#pragma once

#include "tjclanDEF.h"

#ifndef __CLAN_VIEWCLANINFO_HPP__
#define __CLAN_VIEWCLANINFO_HPP__



#define CLAN_MAX		500
//#define CLAN_MAX		4
#define CLANINFO_DIR	"savedata\\clanDATA"  //클랜 정보가 저장되는 디렉토리
typedef struct _tagClanInfoHeader
{
	char		ClanMark_Num[40];   //클랜 마크 번호
	DWORD		nClanMark;
	char		ClanName[40];   //클랜 이름		
	char		ClanReport[90];
	char		Gserver[4];
	char		UniqueClaClanInfo_nNum[64];
	
}CLANINFOHEADER;

typedef struct _tagClanInfo
{
	CLANINFOHEADER ClanInfoHeader;
	
#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우
	DIRECTDRAWSURFACE    hClanMark;		//16*16파일로드
	DIRECTDRAWSURFACE    hClanMark32;	//32*32파일로드(sod에서 보여주기위함)
#else
	HBITMAP					hClanMark;
#endif
	DWORD	dwTime;
	int		nStatus;   //0:작업 안함 1: 작업진행중 2: 작업완료 3: 에러
	int		nSaveNum;

}CLANINFO;



class CViewClanInfo
{
public:
	CViewClanInfo();
	~CViewClanInfo();
public:
	int Init(int Life);
	int Clear();
	

	void Main();
	char* AddClanInfo(char *marknum,char *szInfo,CLANINFO* ci);
	int DownLoadClanInfo(int num,DWORD dwClanNum );
	int chk_readStrBuf(char *cmd, char *readbuf, char *retBuf);
	void SortDelete();
	void LoadData();
	BOOL SearchDirectory();
	void ReadToFile(char *file,int count);
	void ReadToImage(char *file,int count);
	void MakeDirectory();	
	BOOL CheckWhere(char *MarkNum);
	inline BOOL GetFlag(){return bFlag;}
	void ParsingData(char* cmd, char* data, char* save);
	int readFILE_ClanInfo(DWORD clanNum);
	//inline int  GetCheckDownLoad(){return nCheckDownLoad;}
	//inline void SetCheckDownLoad(int flag){nCheckDownLoad = flag;}
private:

	BOOL bFlag;
	

     
	int		nClanInfo_Menu;
	int		nClanInfo_Menu2;
	char	szClanMarkNum[64];
	int		nLowTime;
	



public:
	//클랜정보찾기의 메인함수
	int SearchClan(DWORD dwClanNum );
		//서브함수 1.메모리에서 찾기
		int Search_Memory(char *clanNum);
		//서브함수 2.파일에서 찾기
		int Search_Files(char *clanNum);

	
};
#endif









#ifdef CLAN_VIEWCLANINFO_CPP


	class CViewClanInfo g_ViewClanInfo;
	CLANINFO ClanInfo[CLAN_MAX]; //클랜 정보 저장
	int	ClanInfo_nNum;	 //클랜 인포에 저장된 위치
	int		nDoCheck = 0;
	int	nCheckDownLoad = -1;



#else



extern int	nCheckDownLoad;
extern int		nDoCheck;

extern class CViewClanInfo g_ViewClanInfo;
extern CLANINFO ClanInfo[CLAN_MAX];
extern int ClanInfo_nNum;	


#endif