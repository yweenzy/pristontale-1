/*----------------------------------------------------------------------------*
*	파일명 :  sinUtil.h
*	하는일 :  하는일 많음
*	작성일 :  최종업데이트 2004년 11월
*	적성자 :  박상열 
*-----------------------------------------------------------------------------*/	
#ifndef _SINUTIL_HEADER_ 
#define _SINUTIL_HEADER_ 
/*----------------------------------------------------------------------------*
*						문자열 클래스 
*-----------------------------------------------------------------------------*/	
class sinSTRING{
private:

char			*m_aString;

public:
sinSTRING(void);
sinSTRING(sinSTRING &rString);
sinSTRING(char *pString);

~sinSTRING(void);

//Operators
sinSTRING & operator = (sinSTRING &rString);
sinSTRING & operator = (char *pString);
bool operator == (sinSTRING &rString);
bool operator == (char *pString);
bool operator != (sinSTRING &rString);
bool operator != (char *pString);

//Functions
char *GetString(void);
int  GetLength(void);
};

//
int halpRelease(DIRECTDRAWSURFACE lpTemp);
int haSearchString(char *strBuffer,char KeyBuffer);
int haStringCenter(int PosiX,char *strbuff);


#endif