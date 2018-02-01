//#include "nProtect.h"

#include "stdafx.h"
#include <process.h>

class nP nPro;


/*	화일이름	암호화된변수	암호화푼변수
findhack.exe	securetext[0]	pass_char[0]
NPCHK.DLL		securetext[1]	pass_char[1]
CheckCRC		securetext[2]	pass_char[2]
npmon.exe		securetext[3]	pass_char[3]
NPPSK.DLL		securetext[4]	pass_char[4]
KillTask		securetext[5]	pass_char[5]
*/


char securetext[6][20]={	//암호화된변수
	{-103,-106,-111,-101,-105,-98,-100,-108,-47,-102,-121,-102,-1,-1,-1,-1,-6,-1,-1,-1},
	{-79,-81,-68,-73,-76,-47,-69,-77,-77,-1,120,101,0,0,0,0,5,0,0,0},
	{-68,-105,-102,-100,-108,-68,-83,-68,-1,0,-121,-102,-1,-1,-1,-1,-6,-1,-1,-1},
	{-111,-113,-110,-112,-111,-47,-102,-121,-102,-1,120,101,0,0,0,0,5,0,0,0},
	{-79,-81,-81,-84,-76,-47,-69,-77,-77,-1,-121,-102,-1,-1,-1,-1,-6,-1,-1,-1},
	{-76,-106,-109,-109,-85,-98,-116,-108,-1,0,120,101,0,0,0,0,5,0,0,0}};

char pass_char[6][20];	//암호화푼변수

nP::nP()
{
	
}

nP::~nP()
{

}




//////////////////// 암호화 된부분을 정상적으로 돌려주는 함수///////////////////////
void nP::Init()
{	
	for(int j=0;j<6;j++) for(int i=0;i<20;i++) pass_char[j][i] = securetext[j][i] ^ 0xff;
}



/*
Return 값에 대한 결과값

0	:	정상적 처리
1	:	Can't Load Dll
2	:	Can't Load Funcation
3	:	Alert!! Modified File
4	:	Can't Free Dll
5	:	Error Kill
*/




////////////////////////////// nProtect 의 화일 변조여부 체크해주는 함수//////////////////
int nP::NProtectCheck(void)		
{
	nPro.Init();		// 암호화 부분 초기화

	if(m_hInstDll == NULL)
	{
		m_hInstDll = LoadLibrary(pass_char[1]);
		if(m_hInstDll == NULL)	//에러처리
		{
			// dll이 로드가 안됬을때
			return 1;
		}
		else
		{
 			pFunc_npchk = (bool(*)(char*))GetProcAddress(m_hInstDll,pass_char[2]);

			if(pFunc_npchk == NULL)
			{
				//MessageBox(NULL,"Can't Load Funcation","Can't Load",MB_OK);
				return  2;
			}
			//UpdateData(true);		<< 이부분은 nProtect 사에 문의중입니다
			if(pass_char[0] !="")		// finehack.exe 체크
			{
				if(pFunc_npchk(pass_char[0])){
					//체크를 해서 변조가 없을때의 처리
					//MessageBox(NULL,"Safe File","Safe",MB_OK);
				}
				else {
					// 체크를 했을때 화일 변조가 있을경우의 처리
					//MessageBox(NULL,"Alert!! Modified File","Alert!!",MB_OK);
					return 3;
				}
			}
		}
	}

	if(m_hInstDll != NULL)
	{
		if(FreeLibrary(m_hInstDll)){
			m_hInstDll = NULL;
			// dll을 메모리상에서 날려주는 부분
			//MessageBox(NULL,"Free Dll","Free",MB_OK);
		}
		else {
			// dll을 메모리상에서 날리지 못 했을때의 처리
			//MessageBox(NULL,"Can't Free Dll","Can't Free",MB_OK);
			return 4;
		}
	}
	return 0;
}








////////////////////////   nProtect의 실행 함수  /////////////////////////////
/*
nProtect 로드시 리턴값의 결과값
1024 : 진단결과 메모리상에 해킹툴이 존재하지 않을경우
1025 : 진단결과 메모리상에 해킹둘이 존재하나 정상적으로 치료했을경우
1026 : 진단결과 메모리상의 해킹툴을 감지했으나 사용자가 치료를 선택하지 않거나 프로그램에서 치료를 정상적으로 하지 못했을경우
1027 : 해킹툴 진단 프로그램이 정상적으로 다운로드 되지 않았을경우. URL이 잘못되거나 서버가 정상적으로 동작하지 않을 경우
1028 : NPX.DLL등록 에러 및 nProtect 구동에 필요한 파일이 없을경우
1029 : 프로그램내에서 예외사항이 발생했을 경우
1030 : 사용자가 "종료" 버튼을 클릭했을 경우의 처리값
*/

int nP::NProtectRun(void)		// nProtect의 실행
{
	nPro.Init();		// 암호화 부분 초기화
	// findhack.exe를 실행시키는 부분
	result = spawnl(P_WAIT,pass_char[0],pass_char[0],NULL);
	return result;

}





/////////////////////////////////// nProtect를 메모리에서의 지워주는 함수 ////////////////////

int nP::NProtectFree(void)		
{
	nPro.Init();		// 암호화 부분 초기화
	
	if(m_hInstDll == NULL)
	{
		m_hInstDll = LoadLibrary(pass_char[4]);
		if(m_hInstDll == NULL)
		{
			// dll로드가 안됬을때 에러처리
			//MessageBox(NULL,"Can't Load Dll","Error",MB_OK);
			return 1;
		}
		else
		{
			// dll로드가 성공적으로 이루어 졌을때
 			//MessageBox(NULL,"Success Load Dll","Success",MB_OK);
			
			pFunc_npkill = (int(*)(char*))GetProcAddress(m_hInstDll,pass_char[5]);

			if(pFunc_npkill == NULL)
			{
				//MessageBox(NULL,"Can't Load Funcation","Can't Load",MB_OK);
				return 2;
			}
			//UpdateData(true);
			if(pass_char[3] !="")		// 메모리상에 npmon.exe가 뛰어져있는지 체크
			{
				temp = pFunc_npkill(pass_char[3]);

				if(temp !=0) {
					// 메모리상의 npmon.exe를 성공적으로 Remove시켰을때
					//MessageBox(NULL,"Sucess Kill","Sucess",MB_OK);
				}
				else {
					// 메모리상의 npmon.exe를 Remove를 실패하였을때
					//MessageBox(NULL,"Error Kill","Error",MB_OK);
					return 5;
				}
			}
		}
	}

	if(m_hInstDll != NULL)
	{
		if(FreeLibrary(m_hInstDll)){
			m_hInstDll = NULL;
			// dll을 메모리상에서 날려주는 부분
			//MessageBox(NULL,"Free Dll","Free",MB_OK);
		}
		else {
			// dll을 메모리상에서 날리지 못 했을때의 처리
			return 4;
		}
	}
	return 0;
}