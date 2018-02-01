/*----------------------------------------------------------------------------*
*	파일명 :  sinUtil.cpp
*	하는일 :  하는일 많음
*	작성일 :  최종업데이트 2004년 11월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	

#include "sinLinkHeader.h"

/*----------------------------------------------------------------------------*
*						문자열 클래스 (신바람 스트링)
*-----------------------------------------------------------------------------*/	
//Constructors
sinSTRING::sinSTRING(void) 
{
	m_aString = new char;

}
sinSTRING::sinSTRING(sinSTRING &rString)
{
	if(rString.GetLength() > 0){
		m_aString = new char[rString.GetLength()+1];  //'\0' 까지 넣기위해 메모리를 +1더 잡아준다
		strcpy(m_aString,rString.GetString());
	}
	else m_aString[0] = '\0';

}
sinSTRING::sinSTRING(char *pString)
{
	if(pString){
		m_aString = new char[lstrlen(pString)+1];
		strcpy(m_aString , pString);

	}
	else m_aString[0] = '\0';

}
//Destructor
sinSTRING::~sinSTRING(void)
{
	m_aString[0] = '\0';
}

//Operators
sinSTRING & sinSTRING::operator = (sinSTRING & rString)
{
	if(rString.GetLength() > 0)
		strcpy(m_aString , rString.GetString());
	else m_aString[0] = '\0';
	return *this;
}
sinSTRING & sinSTRING::operator = (char *pString)
{
	if(pString)
		strcpy(m_aString , pString);
	else m_aString[0] = '\0';
	return *this;
}

bool sinSTRING::operator == (sinSTRING &rString)
{
	if(strcmp(rString.GetString() , m_aString) == 0 )return TRUE;
	else return FALSE;

}
bool sinSTRING::operator == (char *pString)
{
	if(strcmp(pString , m_aString) == 0 )return TRUE;
	else return FALSE;
}
bool sinSTRING::operator != (sinSTRING &rString)
{
	if(strcmp(rString.GetString() , m_aString) != 0)return TRUE;
	else return FALSE;

}

bool sinSTRING::operator != (char *pString)
{
	if(strcmp(pString , m_aString) != 0)return TRUE;
	else return FALSE;
}

//Functions
char *sinSTRING::GetString(void)
{
	return m_aString;
}
int sinSTRING::GetLength(void)
{
	return strlen(m_aString);
}

//인자값의 서페이스를 제거 해준다.
int halpRelease(DIRECTDRAWSURFACE lpTemp)
{
	if(!lpTemp) return FALSE;

	if(lpTemp){
		lpTemp->Release();
		lpTemp = 0;
	}
	return TRUE;
}
//문자열에서 키값을 찾는다.
int haSearchString(char *StrBuffer,char KeyBuffer) 
{
	int  TotalNum=0;

	TotalNum=lstrlen(StrBuffer);
	
	for(int i=0;i<TotalNum;i++){
		if(StrBuffer[i]==KeyBuffer){
			return i+1;
		}
	}
	return 0;
}
//문자열을 중앙에 맟춘다.
int haStringCenter(int PosiX,char *strbuff)
{
	
	int len=0;
	int rPosiX=0;
	len=lstrlen(strbuff);
	
	//보정
	if(len%2)
		rPosiX+=4;
	
	if(PosiX%2)
		rPosiX+=1;

	//결과 리턴
	rPosiX = PosiX/2-(len/2*8);


	return rPosiX;
}
