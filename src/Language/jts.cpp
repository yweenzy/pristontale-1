#include "jts.h"

/*////////////////////////////////////////////////////////////////////////////////////////////////////////
 함수명 : GetTXT
 설명   : txt파일에서 문자열을 읽어옴
파라미터 : SaveFile은 텍스트 파일을 읽어 들여서 저장할 변수
           FileName은 읽어올 파일이름
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int GetTXT(char* FileName,char* SaveFile)
{
	FILE* rFile = NULL;	
	int nStrlen = 0;

	rFile = fopen(FileName,"r");

	if(!rFile)
	{
		return -1;
	}
	if(SaveFile[0] !=0)
	{
		memset(SaveFile,0,sizeof(SaveFile));
	}	
	fread(SaveFile,MAXTXTFILE,1,rFile);
	fclose(rFile);
	nStrlen = strlen(SaveFile);
	if(nStrlen > MAXTXTFILE)
	{
		return 0;
	}

	return 1;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////
 함수명 : CheckJTS
 설명   : 일본어는 2byte또는 1byte로 처리하는 2가지 경우가 있다.
          TXT파일에서 파일에서 읽어 문자열들을 그 각각의 값을 비교하여서 2byte,1byte로 처리할치 검사한다.
		  10진주 129~159,224~239 16진수0x81~0x9f,0xe0~0xef사이의 값일 경우 2byte문자의 1byt로 처리하고
		  이어서 10진수 64~126, 128~252 16진수0x40~0x7e,0x80~0xfc일 경우 나머지 1byte를 처리면서 리턴값을 2로처리한다.
		  영어,숫자(ASCII, 0x21-0x7E)나 반각,가나의 0xA1-0xDF일 경우 1byte로 처리하면서 리턴값 1로처리한다.
		  나머지 일경우 리턴값 -1로 처리한다.
파라미터 : SaveFile은 텍스트 파일을 읽어 들여서 저장한 변수가 위치
		   num 원하는 위치
////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
int CheckJTS(char* SaveFile,int num)
{	
	if(((*(SaveFile + num) >= 129) && (*(SaveFile + num) <= 159)) || ((*(SaveFile + num) >= 224) && (*(SaveFile + num) <= 239)) || ((*(SaveFile + num) >= 0xFFFFFF81) && (*(SaveFile + num) <= 0xFFFFFF9F)) || ((*(SaveFile + num) >= 0XFFFFFFE0) && (*(SaveFile + num) <= 0XFFFFFFEF)))
	{	
		if(((*(SaveFile + num + 1) >= 0xFFFFFF40) && (*(SaveFile + num + 1) <= 0xFFFFFF7E)) || ((*(SaveFile + num + 1) >= 0xFFFFFF80)&& (*(SaveFile + num + 1) <= 0xFFFFFFFC)) || ((*(SaveFile + num + 1) >= 64)&& (*(SaveFile + num + 1) <= 126)) || ((*(SaveFile + num + 1) >= 128)&& (*(SaveFile + num + 1) <= 252)))
		{				
			return 2;
		}		
	}
	if(((*(SaveFile + num) >= 0xFFFFFF21) && (*(SaveFile + num) <= 0xFFFFFF7E)) || ((*(SaveFile + num) >= 0xFFFFFFA1) && (*(SaveFile + num) <= 0xFFFFFFDF)))
	{		
		return 1;
	}

	return -1;
}*/
int CheckJTS(char* SaveFile,int num)
{	
	if((((*(SaveFile + num)&0xff) >= 129) && ((*(SaveFile + num)&0xff) <= 159)) || (((*(SaveFile + num)*0xff) >= 224) && ((*(SaveFile + num)&0xff) <= 239)))
	{	
		if((((*(SaveFile + num + 1)&0xff) >= 64)&& ((*(SaveFile + num + 1)&0xff) <= 126)) || (((*(SaveFile + num + 1)&0xff) >= 128)&& ((*(SaveFile + num + 1)&0xff) <= 252)))
		{				
			return 2;
		}		
	}
	if((((*(SaveFile + num)&0xff) >= 0x21) && ((*(SaveFile + num)&0xff) <= 0x7E)) || ((*(SaveFile + num) >= 0xFFFFFFA1) && ((*(SaveFile + num)&0xff) <= 0xDF)))
	{		
		return 1;
	}

	return -1;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////
  함수명 : GetCharacterJTS
  설명   : txt파일에서 읽어온 문자열을 문자로 출력하는 함수.
           CheckJTS함수를 사용하여 일본어의 문자처리를 파싱했다.
 파라미터 : SaveFile은 텍스트 파일을 읽어 들여서 저장한 변수가 위치
            SaveCh 읽어온 문자를 저장할 변수가 위치
			 num 원하는 위치
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

char* GetCharacterJTS(char* SaveFile, char* SaveCh, int num)
{
	int nCheck = 0;
	int nNum = 0;
	int nCount = 0;

	while(1)
	{	
		if(nCount+1 == num)
		{
			break;
		}		
		nCheck = CheckJTS(SaveFile,nNum);
		if(nCheck == 2)
		{
			nNum+=2;		
		}
		else//(nCheck == 1)
		{
			nNum+=1;
		}
		//else return FALSE;
		nCount++;
	}
    
	nCheck = CheckJTS(SaveFile,nNum);
	if(SaveCh[0] !=0)
	{
		memset(SaveCh,0,sizeof(SaveCh));
	}	

	if(nCheck == 2)
	{
		SaveCh[0] = SaveFile[nNum];
		SaveCh[1] = SaveFile[nNum+1];		
	}
	else 
	{
		SaveCh[0] = SaveFile[nNum];
	}	
	
	return SaveCh;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////
  함수명 : CheckJTS_ptr
  설명   : num에 위치한 문자 메모리 주소를 처리하기 위한 함수
           리턴값 1 : 1byte로 처리될 경우
		   리턴값 2 : 2byte로 처리되므로 그 전 메모리를 위치시킴
		   리턴값 3 : 2byte로 처리되나 마지막 1byte로 처리되기 때문에 그 메모리 주소를 리턴
		   리턴값 4 : 0x0D 일경우
		   리턴값 5 : 0x0A 일경우
파라미터 : pos 원하는 위치
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int CheckJTS_ptr(char* SaveFile,int pos)
{	
	if((((*(SaveFile + pos)&0xff) >= 0x21) && ((*(SaveFile + pos)&0xff) <= 0x7E)) //ascii 영푳E 숫자
			|| (((*(SaveFile + pos)&0xff) >= 0xA1) && ((*(SaveFile + pos)&0xff) <= 0xDF))) //1BYTE 가나 (반각 가나)
	{		
		return 1;
	}	

	if(((*(SaveFile + pos) >= 129) && (*(SaveFile + pos) <= 159)) || ((*(SaveFile + pos) >= 224) && (*(SaveFile + pos) <= 239)) || ((*(SaveFile + pos) >= 0xFFFFFF81) && (*(SaveFile + pos) <= 0xFFFFFF9F)) || ((*(SaveFile + pos) >= 0XFFFFFFE0) && (*(SaveFile + pos) <= 0XFFFFFFEF)))
	{
		return 2;
	}

	if(((*(SaveFile + pos -1) >= 129) && (*(SaveFile + pos -1) <= 159)) || ((*(SaveFile + pos -1) >= 224) && (*(SaveFile + pos -1) <= 239)) || ((*(SaveFile + pos -1) >= 0xFFFFFF81) && (*(SaveFile + pos -1) <= 0xFFFFFF9F)) || ((*(SaveFile + pos -1) >= 0XFFFFFFE0) && (*(SaveFile + pos -1) <= 0XFFFFFFEF)))
	{		
		return 3;		
	}

	if(*(SaveFile + pos) == 0x0D)
	{
		return 4;
	}

	if(*(SaveFile + pos) == 0x0A)
	{
		return 5;
	}

	return -1;
}
/*////////////////////////////////////////////////////////////////////////////////////////////////////////
  함수명 : CheckTHAI_ptr
  설명   : num에 위치한 문자 메모리 주소를 처리하기 위한 함수
           리턴값 1 : 1byte로 처리될 경우
		   리턴값 2 : 2byte로 처리되므로 그 전 메모리를 위치시킴		   
		   리턴값 4 : 0x0D 일경우
		   리턴값 5 : 0x0A 일경우
파라미터 : pos 원하는 위치
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int CheckTHAI_ptr(char* SaveFile,int pos)
{	
	if(((*(SaveFile + pos)&0xff) >= 0x21) && ((*(SaveFile + pos)&0xff) <= 0x7E)) //ascii 영푳E 숫자
	{		
		return 1;
	}	
	/*
	if( ( SaveFile[pos] >= 0x21 )   && 	    ( SaveFile[pos] <= 0x7e ) )  // 영문 ascii 코드임 
	{
		return 1;
	}
	*/

	if(((((*(SaveFile + pos+1)&0xff) >= 0xd4) && ((*(SaveFile + pos+1)&0xff) <= 0xff)) 
		|| (((*(SaveFile + pos+1)&0xff) >= 0) && ((*(SaveFile + pos+1)&0xff) <= 0x4a)))
		&& ((*(SaveFile + pos) == 1) && (*(SaveFile + pos) == 2)))
	{
		return 2;
	}
	/*
	if( ( ( SaveFile[pos+1] >= 0xd4 ) && ( SaveFile[pos+1] <= 0xff ) ) ||
	    ( ( SaveFile[pos+1] >= 0xd4 ) &&

	*/

	if(*(SaveFile + pos) == 0x0D)
	{
		return 4;
	}

	if(*(SaveFile + pos) == 0x0A)
	{
		return 5;
	}

	return -1;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////
  함수명 : GetCharacter_ptr
  설명   : pos에 위치한 문자 메모리 주소를 처리하기 위한 함수
			case 1 : 1byte로 처리될 경우
		    case 2 : 2byte로 처리되므로 그 전 메모리를 위치시킴
		    case 3 : 2byte로 처리되나 마지막 1byte로 처리되기 때문에 그 메모리 주소를 리턴
		    case 4 : 0x0D일 경우 그전 메모리 주소를 리턴
			csse 5 : 0x0A일 경우 그 전전 메모리 준소를 리턴
 파라미터 : pos 원하는 위치
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

char* GetCharacter_ptr(char* SaveFile,int pos)
{
	int nReturnValue = 0;
	nReturnValue = CheckJTS_ptr(SaveFile,pos);
	switch(nReturnValue)
	{
	case 1:
		return (SaveFile + pos);
	case 2:
		return (SaveFile + pos -1);
	case 3:
		return (SaveFile + pos);
	case 4:
		return (SaveFile + pos - 1);
	case 5:
		return (SaveFile + pos - 2);
	case -1:
		return 0;
	}
	return 0;
}
/*////////////////////////////////////////////////////////////////////////////////////////////////////////
  함수명 : GetPointerPos
  설명   : pos에 위치한 위치 처리 함수
			case 1 : 1byte로 처리될 경우
		    case 2 : 2byte로 처리되므로 그 전 위치를 체크
		    case 3 : 2byte로 처리되나 마지막 1byte로 처리되기 때문에 그 전 위치를 리턴
		    case 4 : 0x0D일 경우 그 전 위치를 리턴
			csse 5 : 0x0A일 경우 그 전전 위치를 리턴
파라미터 : pos 원하는 위치
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int GetPointerPos(char* SaveFile,int pos)
{
	int nPos;
	int nReturnValue = 0;

	nReturnValue = CheckJTS_ptr(SaveFile,pos);

	switch(nReturnValue)
	{
	case 1:
		nPos = pos;
		break;
	case 2:
		nPos = pos -1;
		break;
	case 3:
		nPos = pos;
		break;
	case 4:
		nPos = pos -1;
		break;
	case 5:
		nPos = pos -2;
	case -1:
		return 0;
	}	

	return nPos;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////
 함수명: IsJTS
 설명  : 일본어인지체크한다
파라미터 : SaveFile은 텍스트 파일을 읽어들여서 저장할 변수
리턴값  : 일본어 이면 TRUE, 일본어가 아니면 FALSE		
예외 발생 : ㄱ의 16진수값은 ffffffa1이므로 1byte가나(반각 가나 범위 0xA1~0xDF) 값과 동일하다.
            만약 일본어와 한글 자음과 모음이 썩어서 들어오면 일본어로(TRUE) 처리가된다.
			그러나 한글조합와(예 : 가나다)일본어가 썩어서 들어오면 일본어가 아니라고(FALSE)  제대로 처리가 된다.
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int IsJTS(char* SaveFile)
{
	int nCount = 0;
	int nStrlen = 0;
	int nReturnValue = -1;
    BOOL bJTS = FALSE;
	nStrlen = strlen(SaveFile);

	while(1)
	{		
		if(SaveFile[nCount] == 0)
		{
			if(nStrlen == nCount)
			{
				bJTS = TRUE;
				nReturnValue = -1;
				break;
			}
			
		}
		if((((*(SaveFile + nCount)&0xff) >= 0x21) && ((*(SaveFile + nCount)&0xff) <= 0x7E)) //ascii 영푳E 숫자
			|| (((*(SaveFile + nCount)&0xff) >= 0xA1) && ((*(SaveFile + nCount)&0xff) <= 0xDF))) //1BYTE 가나 (반각 가나)
		{
			nCount+=1;
		}
		else if((((*(SaveFile + nCount)&0xff) >= 0x81) && ((*(SaveFile + nCount)&0xff) <= 0x9F))
			||  (((*(SaveFile + nCount)&0xff) >= 0xE0) && ((*(SaveFile + nCount)&0xff) <= 0xEF)))
		{
			if((((*(SaveFile + nCount)&0xff) >= 0x40) && ((*(SaveFile + nCount)&0xff) <= 0x7E))
			|| (((*(SaveFile + nCount)&0xff) >= 0x80) && ((*(SaveFile + nCount)&0xff) <= 0xFC)))
			{
				nCount+=2;
			}
			else
			{
				bJTS = FALSE;
				nReturnValue = nCount;
				break;
			}
		}
		else
		{
			bJTS = FALSE;
			nReturnValue = nCount;
			break;
		}
	}
	if(!bJTS)
	{
		return nReturnValue;
	}

	return nReturnValue;
}
/*////////////////////////////////////////////////////////////////////////////////////////////////////////
 함수명: IsTHAI
 설명  : 태국어인지체크한다
파라미터 : SaveFile은 텍스트 파일을 읽어들여서 저장할 변수
리턴값  : 태국어 이면 TRUE, 태국어 아니면 FALSE		
////////////////////////////////////////////////////////////////////////////////////////////////////////*/
int IsENG(char* SaveFile)
{
	int nCount = 0;
	int nStrlen = 0;
	int nReturnValue = -1;
    BOOL bJTS = FALSE;
	nStrlen = strlen(SaveFile);

	while(1)
	{		
		if(SaveFile[nCount] == 0)
		{
			if(nStrlen == nCount)
			{
				bJTS = TRUE;
				nReturnValue = -1;
				break;
			}
			
		}
		if((((*(SaveFile + nCount)&0xff) >= 0x30) && ((*(SaveFile + nCount)&0xff) <= 0x39))||
		   (((*(SaveFile + nCount)&0xff) >= 0x41) && ((*(SaveFile + nCount)&0xff) <= 0x5a))||
		   (((*(SaveFile + nCount)&0xff) >= 0x61) && ((*(SaveFile + nCount)&0xff) <= 0x7a))||
			((*(SaveFile + nCount)&0xff) == 0x28) ||
			((*(SaveFile + nCount)&0xff) == 0x29) ||
			((*(SaveFile + nCount)&0xff) == 0x5b) ||
			((*(SaveFile + nCount)&0xff) == 0x5d) ||
			((*(SaveFile + nCount)&0xff) == 0x5f) ||
			((*(SaveFile + nCount)&0xff) == 0x2d))
		{
			nCount+=1;
		}
		else
		{
			bJTS = FALSE;
			nReturnValue = nCount;
			break;
		}
	}
	if(!bJTS)
	{
		return nReturnValue;
	}
	return nReturnValue;
}
/*////////////////////////////////////////////////////////////////////////////////////////////////////////
 함수명: IsTHAI
 설명  : 태국어인지체크한다
파라미터 : SaveFile은 텍스트 파일을 읽어들여서 저장할 변수
리턴값  : 태국어 이면 TRUE, 태국어 아니면 FALSE		
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int IsTHAI(char* SaveFile)
{
	int nCount = 0;
	int nStrlen = 0;
	int nReturnValue = -1;
    BOOL bJTS = FALSE;
	nStrlen = strlen(SaveFile);

	if(SaveFile[0] == 0) return -1;
	while(1)
	{		
		/*if(SaveFile[nCount] == 0)
		{
			if(nStrlen == nCount)
			{
				bJTS = TRUE;
				nReturnValue = -1;
				break;
			}
			
		}*/
		if((((*(SaveFile + nCount)&0xff) >= 0x30) &&((*(SaveFile + nCount)&0xff) >= 0x39))|| //문제있어보임 _ignore_		//해외
			(((*(SaveFile + nCount)&0xff) >= 0x41)&&((*(SaveFile + nCount)&0xff) <= 0x5a))||
			(((*(SaveFile + nCount)&0xff) >= 0x61)&&((*(SaveFile + nCount)&0xff) <= 0x7a))) //ascii 영푳E 숫자
			
		{
			nCount+=1;
		}
		else if((((*(SaveFile + nCount)&0xff) == 0x01) || ((*(SaveFile + nCount)&0xff) == 0x02)))
		{
			if(((((*(SaveFile + nCount+1)&0xff) >= 0xd4) && ((*(SaveFile + nCount+1)&0xff) <= 0xff)) 
   			|| (((*(SaveFile + nCount+1)&0xff) >= 0) && ((*(SaveFile + nCount+1)&0xff) <= 0x4a))))
			{
				nCount+=2;
			}
			else
			{
				bJTS = FALSE;
				nReturnValue = nCount;
				break;
			}
		}
		else
		{
			bJTS = FALSE;
			nReturnValue = nCount;
			break;
		}
	}
	if(!bJTS)
	{
		return -1;
	}

	return nReturnValue;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////
 함수명		: Check_T
 설명		: 대만어 1byte처리할 경우와 2byte처리할 경우를 체크한다.
              대만어는 덱시멀 128(hex : 0x80)이하 일경우 1byte처리하고, 그 이상일 경우 2byte에서 첫바이트
			  범위는 0xa1~f9 에 속하면 두번재 바이트 0x40~0x7e, 0xa1~0xfe이다.
 파라미터	: saveFile,대만어를 저장한 변수, 체크할 대만어 위치 
////////////////////////////////////////////////////////////////////////////////////////////////////////*/
int Check_T(char* SaveFile,int num)
{	
	if(((*(SaveFile + num)&0xff) < 0x80))
	{
		return 1;
	}
	else
	{
		if((((*(SaveFile + num)&0xff) >= 0xA1) && ((*(SaveFile + num)&0xff) <= 0xF9)))
		{
			if((((*(SaveFile + num + 1)&0xff) >= 0x40)&& ((*(SaveFile + num + 1)&0xff) <= 0x7E)) || (((*(SaveFile + num + 1)&0xff) >= 0xA1)&& ((*(SaveFile + num + 1)&0xff) <= 0xFE)))
			{
				return 2;
			}
		}
	}	

	return -1;
}


/*////////////////////////////////////////////////////////////////////////////////////////////////////////
 함수명 : GetCharacter_T
 설명   : 원하는 위치의 대만어를 출력한다.
 파라미터 : SaveFile은 텍스트 파일을 읽어 들여서 저장한 변수가 위치
            SaveCh 읽어온 문자를 저장할 변수가 위치
			 num 원하는 위치
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void GetCharacter_T(char* SaveFile, char* SaveCh, int num)
{
	int nCheck = 0;
	int nNum = 0;
	int nCount = 0;

	while(1)
	{	
		if(nCount+1 == num)
		{
			break;
		}		
		nCheck = Check_T(SaveFile,nNum);
		if(nCheck == 2)
		{
			nNum+=2;		
		}
		else if((nCheck == 1))
		{
			nNum+=1;		
		}
		nCount++;
	}
    
	nCheck = Check_T(SaveFile,nNum);
	if(SaveCh[0] !=0)
	{
		memset(SaveCh,0,sizeof(SaveCh));
	}	

	if(nCheck == 2)
	{
		SaveCh[0] = SaveFile[nNum];
		SaveCh[1] = SaveFile[nNum+1];		
	}
	else if((nCheck == 1))
	{
		SaveCh[0] = SaveFile[nNum];		
	}	
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////
  함수명 :Check_ptr_T
  설명   : 원하는 위치의 원바이트인지, 투바이트인지 체크한다.
파라미터 : pos 원하는 위치
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int Check_ptr_T(char* SaveFile,int pos)
{	
	if(((*(SaveFile + pos)&0xff) < 0x80))
	{
		return 1;
	}
	
	if((((*(SaveFile + pos)&0xff) >= 0xA1) && ((*(SaveFile + pos)&0xff) <= 0xF9)))
	{	
		return 2;
	}

   	if((((*(SaveFile + pos - 1)&0xff) >= 0xA1) && ((*(SaveFile + pos - 1)&0xff) <= 0xF9)))
	{				
		return 3;
	}		

	if(*(SaveFile + pos) == 0x0D)
	{
		return 4;
	}

	if(*(SaveFile + pos) == 0x0A)
	{
		return 5;
	}

	return -1;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////
  함수명 : GetCharacter_ptr_T
  설명   : pos에 위치한 문자 메모리 주소를 처리하기 위한 함수
			case 1 : 1byte로 처리될 경우
		    case 2 : 2byte로 처리되므로 그 전 메모리를 위치시킴
		    case 3 : 2byte로 처리되나 마지막 1byte로 처리되기 때문에 그 메모리 주소를 리턴
		    case 4 : 0x0D일 경우 그전 메모리 주소를 리턴
			csse 5 : 0x0A일 경우 그 전전 메모리 준소를 리턴
 파라미터 : pos 원하는 위치
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

char* GetCharacter_ptr_T(char* SaveFile,int pos)
{
	int nReturnValue = 0;
	nReturnValue = CheckJTS_ptr(SaveFile,pos);
	switch(nReturnValue)
	{
	case 1:
		return (SaveFile + pos);
	case 2:
		return (SaveFile + pos -1);
	case 3:
		return (SaveFile + pos);
	case 4:
		return (SaveFile + pos - 1);
	case 5:
		return (SaveFile + pos - 2);
	case -1:
		return 0;
	}
	return 0;
}
/*////////////////////////////////////////////////////////////////////////////////////////////////////////
함수명 : GetPointerPos_T
설명   : pos에 위치한 위치 처리 함수
			case 1 : 1byte로 처리될 경우
		    case 2 : 2byte로 처리되므로 그 전 위치를 체크
		    case 3 : 2byte로 처리되나 마지막 1byte로 처리되기 때문에 그 전 위치를 리턴
		    case 4 : 0x0D일 경우 그 전 위치를 리턴
			csse 5 : 0x0A일 경우 그 전전 위치를 리턴
파라미터 : pos 원하는 위치
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int GetPointerPos_T(char* SaveFile,int pos)
{
	int nPos;
	int nReturnValue = 0;

	nReturnValue = CheckJTS_ptr(SaveFile,pos);

	switch(nReturnValue)
	{
	case 1:
		nPos = pos;
		break;
	case 2:
		nPos = pos -1;
		break;
	case 3:
		nPos = pos;
		break;
	case 4:
		nPos = pos -1;
		break;
	case 5:
		nPos = pos -2;
	case -1:
		return 0;
	}	

	return nPos;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////
함수명: IsTaiwan
설명  : 대만어인지 체크한다.
파라미터 : SaveFile은 텍스트 파일을 읽어들여서 저장할 변수
리턴값  : -1이면 대만어이고 그렇이 않으면 대만어가 아니부분의 위치를 넘겨준다.
예외 발생 : 대만어의 헥사값과 한글의 값 범위와 거진 같기때문에 이 함수는 거진 필요하지 않다.
////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int IsTaiwan(char* SaveFile)
{
	int nCount = 0;
	int nStrlen = 0;
	int nReturnValue = -1;
    BOOL bTaiwan = FALSE;
	nStrlen = strlen(SaveFile);

	while(1)
	{		
		if(SaveFile[nCount] == 0)
		{
			if(nStrlen == nCount)
			{
				bTaiwan = TRUE;
				nReturnValue = -1;
				break;
			}
			else
			{
				bTaiwan = FALSE;
				break;
			}
		}
		if(((*(SaveFile + nCount)&0xff) < 0x80)) 
		{
			nCount+=1;
		}
		else if((((*(SaveFile + nCount)&0xff) >= 0xA1) && ((*(SaveFile + nCount)&0xff) <= 0xF9)))
		{
			if((((*(SaveFile + nCount + 1)&0xff) >= 0x40)&& ((*(SaveFile + nCount + 1)&0xff) <= 0x7E))
				|| (((*(SaveFile + nCount + 1)&0xff) >= 0xA1)&& ((*(SaveFile + nCount + 1)&0xff) <= 0xFE)))
			{
				nCount+=2;
			}
			else
			{
				bTaiwan = FALSE;
				nReturnValue = nCount;
				break;
			}
		}
		else
		{
			bTaiwan = FALSE;
			nReturnValue = nCount;
			break;
		}
	}
	if(!bTaiwan)
	{
		return nReturnValue;
	}

	return nReturnValue;
}

