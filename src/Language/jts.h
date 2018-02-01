/*////////////////////////////////////////////////////////////////////////////////////////////////////////
 작성자 : 유광열
 날짜   : 2002.7.9
 수정일 : 2002.7.22
////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#ifndef __JTS_H__
#define __JTS_H__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define MAXTXTFILE 516

/************************************japan************************************************/
int GetTXT(char* FileName,char* SaveFile);
int CheckJTS(int num);
char* GetCharacterJTS(char* SaveFile, char* SaveCh, int num);
char* GetCharacter_ptr(char* SaveFile,int pos);
int CheckJTS_ptr(char* SaveFile,int pos);
int GetPointerPos(char* Savefile,int pos);
int IsJTS(char* SaveFile);
int IsENG(char* SaveFile);

/**************************taiwan*********************************************************/

int Check_T(char* SaveFile,int num);
void GetCharacter_T(char* SaveFile, char* SaveCh, int num);
int Check_ptr_T(char* SaveFile,int pos);
char* GetCharacter_ptr_T(char* SaveFile,int pos);
int GetPointerPos_T(char* SaveFile,int pos);
int IsTaiwan(char* SaveFile);

/**************************thai*********************************************************/
int CheckTHAI_ptr(char* SaveFile,int pos);
int IsTHAI(char* SaveFile);


#endif