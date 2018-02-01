//-----------------------------------------------------------------------
//
//  isaoÀÇ ¼­¹ö¿¡ ssl·Î Ã¼Å©.
//
//-----------------------------------------------------------------------
#define __ISAOCHECK_CPP__
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <Winsock.h>
#include <wininet.h>
#include <time.h>

#include "../clanmenu/tjclanDEF.h"
#include "Language\\language.h"

#ifdef USE_PROSTONTALE		//=========== ÇÁ¸®½ºÅÏ¼Ò½ºÀÎ°æ¿ì
	#include "sinbaram\\SinLinkHeader.h"
	#include "HoBaram\\HoLinkHeader.h"
	#include "HoBaram\\HoTextFile.h"
	#include "..\\clanmenu\\cE_CViewClanInfo.h"
#endif


#include "..\\clanmenu\\BMPsmooth.h"
#include "..\\clanmenu\\tjclan.h"
#include "..\\clanmenu\\cE_CViewClanInfo.h"
//#include "..\\clanmenu\\Zip.h"
#include <wininet.h>
#pragma comment(lib,"wininet.lib")


//ktj : ¿ø·¡ ¾²·¹µå·Î »ç¿ëÇØ¾ß À©¼Ó ºí·°Å·ÀÌ ¾ÈµÊ¿¡ ÁÖÀÇÇÒ°Í.
#include "isaocheck.h"

extern void fd( char *fmt, ...);
extern void fd2( char *fmt, ...);

#define BUF_LEN 4096

extern char szConnServerName[16];
extern int  nClanTicket; //ticket¹øÈ£ (°³¹ß¿ë ÀÓ½Ã Æ¼ÄÏ¹øÈ£ 9999)

extern BOOL	g_bDebugOption;
void debug_fd2( char *fmt, ...)
{
	if (g_bDebugOption == FALSE) {
		return;
	}

	char buff[4096];
	
    va_list args;

    va_start( args, fmt );
    vsprintf( buff, fmt, args );
    va_end( args );

    strcat( buff, "\r\n" );


	int errorMSGdr=0;
	if(strlen(buff)>2048 ) {
		buff[1024] = 0;
		errorMSGdr= 1;

		HANDLE hFile;
		DWORD dwAcess =0;
		hFile = CreateFile( "DDD2.txt", GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
							NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

		if( hFile != INVALID_HANDLE_VALUE ) {
			SetFilePointer( hFile , 0 , NULL , FILE_END );

			//µ¥ÀÌÅ¸ ¾²±â     ¹öÆÛ    ¾µÅ©±â    ½ÇÁ¦·Î ¾²¿©Áø ¹ÙÀÌÆ®¼ö
			int chk = WriteFile( hFile , buff , lstrlen(buff) , &dwAcess , NULL );


			//µ¥ÀÌÅ¸ ¾²±â     ¹öÆÛ    ¾µÅ©±â    ½ÇÁ¦·Î ¾²¿©Áø ¹ÙÀÌÆ®¼ö
			if(errorMSGdr== 1) {
				char msg[256] = "..\n¸Þ½ÃÁö°¡ ³Ê¹«±æ¾î¼­ Àß¶úÀ½";
				WriteFile( hFile , msg, lstrlen(msg) , &dwAcess , NULL );
			}
			
			//ÆÄÀÏ ´Ý±â
			CloseHandle( hFile );
		}

		return;	
	}

	HANDLE hFile;
    DWORD dwAcess =0;
    hFile = CreateFile( "DDD2.txt", GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

    if( hFile != INVALID_HANDLE_VALUE ) {
        SetFilePointer( hFile , 0 , NULL , FILE_END );
        //µ¥ÀÌÅ¸ ¾²±â     ¹öÆÛ    ¾µÅ©±â    ½ÇÁ¦·Î ¾²¿©Áø ¹ÙÀÌÆ®¼ö
        int chk = WriteFile( hFile , buff , lstrlen(buff) , &dwAcess , NULL );


		if(errorMSGdr== 1) {
			char msg[256] = "\n¸Þ½ÃÁö°¡ ³Ê¹«±æ¾î¼­ Àß¶úÀ½";
			WriteFile( hFile , msg, lstrlen(msg) , &dwAcess , NULL );
		}
		

        //ÆÄÀÏ ´Ý±â
        CloseHandle( hFile );
    }
}










BOOL GetHttpRequest(LPSTR httpname,LPSTR Request,DWORD MaxBuffer,int *len)
{
	char szSizeBuffer[32];
    DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
    DWORD dwFileSize = 0;
    DWORD dwBytesRead = 0;
    BOOL bSuccessful = FALSE;
    //int i;
 
    HINTERNET m_Session = NULL;
    m_Session = InternetOpen("AppName",  //¾îÇÃ¸®ÄÉÀÌ¼ÇÀÇ ÀÌ¸§
							INTERNET_OPEN_TYPE_PRECONFIG,  
							// Use registry settings.
                            NULL,
							// Proxy name. NULL indicates use default.
                            NULL,  
							// List of local servers. NULL indicates default.
                            0) ;
 	HINTERNET hHttpFile = NULL;
    hHttpFile = InternetOpenUrl(m_Session, (const char *) httpname, NULL,
								0, 0, 0);
    if (hHttpFile)
    {
		BOOL bQuery = HttpQueryInfo(hHttpFile,HTTP_QUERY_CONTENT_LENGTH, szSizeBuffer,
					    &dwLengthSizeBuffer, NULL) ;
	    //BOOL bQuery = InternetQueryDataAvailable(hHttpFile,&dwLengthSizeBuffer,0,0);
        if(bQuery==TRUE)
        {
			dwFileSize=atol(szSizeBuffer);                                                          
            dwFileSize > MaxBuffer ? dwFileSize = MaxBuffer :
			dwFileSize = dwFileSize;
 
            BOOL bRead = InternetReadFile(hHttpFile, Request,dwFileSize, &dwBytesRead);
            if (bRead)
            {
				bSuccessful = TRUE;
				*len = dwBytesRead;
		
				//i = lstrlen(Request);
            }
            InternetCloseHandle(hHttpFile);
		}
	}
    if(hHttpFile) InternetCloseHandle(hHttpFile);
    if(m_Session) InternetCloseHandle(m_Session);
    return bSuccessful;
 }            




/*///////////////////////////////////////////////////////////////////////////
: Å¬¶ó½º ¸í: class ISAOCHECK
: ÇÏ ´Â ÀÏ : À¥db¸¦ ÀÌ¿ë µ¥ÀÌÅ¸¸¦ °¡Á®¿Â´Ù.
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò : À¥db¸¦ »ç¿ëÇØ µ¥ÀÌÅ¸¸¦ »Ì¾Æ³»¾ß ÇÒ°æ¿ì º» Å¬¶ó½º¸¦ ÀÌ¿ëÇÑ´Ù.
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
ISAOCHECK::ISAOCHECK()
{

	HSsu = 0;						//Çí»ç½ºÆ®¸µÀÇ °¹¼ö
	for(int i=0; i<30; i++)
		fileDATA_HS[i]= NULL;		//ÃÑ 2048binaryÀÇ µ¥ÀÌÅ¸°¡ 4096 hexa stringÀ¸·Î ¹Ù²î¾îµé¾î°¨.
}

ISAOCHECK::~ISAOCHECK()
{
}

void ISAOCHECK::init()
{
	iCheckFlag = 0;
	hostPORT = 0;
}

void ISAOCHECK::init_HostName_Port(char *hostname, int port )
{
	if(hostname==NULL) return;

	hostPORT = port;
	ZeroMemory(hostName, sizeof(char)*64 );
//#ifdef __CLANSERVER__
	//strcpy(hostName, "211.44.231.10");
//#else
	strcpy(hostName, hostname);
///#endif
}

void ISAOCHECK::init_HostName_Port1(char *hostname, int port )
{
	if(hostname==NULL) return;

	hostPORT1 = port;
	ZeroMemory(hostName1, sizeof(char)*64 );
	strcpy(hostName1, hostname);
}

void ISAOCHECK::init(int iCheckON, int iTimeOUT )
{
	iCheckFlag = iCheckON;	//config.isaocheck¿¡¼­ Ã½Å©µÊ
	iTimeOut = iTimeOUT;
}

void ISAOCHECK::close()
{
}


void ISAOCHECK::main()
{

}



/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :  int connect_WEBdb( char *szWriteBuffer, char *szReadBuffer , long StartTime )
: ÇÏ ´Â ÀÏ :  À¥db¿¡ Á¢¼ÓÇØ µ¥ÀÌÅ¸¸¦ ±¸ÇÏ´Â ÇÔ¼ö
: ¼­    ½Ä :
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò :  ÀÌ Å¬¶ó½ºÀÇ ÇÙ½É ÇÔ¼öÀÓ.
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/

int ISAOCHECK::connect_WEBdb( char *szWriteBuffer, char *szReadBuffer)
{
	char szSizeBuffer[32];
    DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
    DWORD dwFileSize = 0;
    DWORD dwBytesRead = 0;
    
    int iRet= ISAO_ERR_WINSOCK_NOERR;

    ZeroMemory(szReadBuffer,BUF_LEN);
    //int i;
 
    HINTERNET m_Session = NULL;
    
    m_Session = InternetOpen("AppName",  //¾îÇÃ¸®ÄÉÀÌ¼ÇÀÇ ÀÌ¸§
							INTERNET_OPEN_TYPE_PRECONFIG,  
							// Use registry settings.
                            NULL,
							// Proxy name. NULL indicates use default.
                            NULL,  
							// List of local servers. NULL indicates default.
                            0) ;
    if(!m_Session) 
    {
	    iRet = ISAO_ERR_TCP_CONNECT;
	    return iRet;
    }
 	HINTERNET hHttpFile = NULL;
    hHttpFile = InternetOpenUrl(m_Session, (const char *) szWriteBuffer, NULL,
								0, 0, 0);
    if (hHttpFile)
    {
		BOOL bQuery = HttpQueryInfo(hHttpFile,HTTP_QUERY_CONTENT_LENGTH, szSizeBuffer,
					    &dwLengthSizeBuffer, NULL) ;
	    //BOOL bQuery = InternetQueryDataAvailable(hHttpFile,&dwLengthSizeBuffer,0,0);
        if(bQuery==TRUE)
        {
			dwFileSize=atol(szSizeBuffer);                                                          
            dwFileSize > BUF_LEN ? dwFileSize = BUF_LEN :
			dwFileSize = dwFileSize;
 
            BOOL bRead = InternetReadFile(hHttpFile, szReadBuffer,dwFileSize, &dwBytesRead);
            if (bRead)
            {
				
				if((bRead == TRUE)&&(dwFileSize !=dwBytesRead))
				{			
					iRet = ISAO_ERR_RECONNECT;
				}
		
				
            }
		   else iRet = ISAO_ERR_RECONNECT;
            InternetCloseHandle(hHttpFile);
		}
	}
    else
    {
	    iRet = ISAO_ERR_TCP_CONNECT;
    }
    if(hHttpFile) InternetCloseHandle(hHttpFile);
    if(m_Session) InternetCloseHandle(m_Session);
    return iRet;
}

int ISAOCHECK::connect_WEBdb_1( char *szWriteBuffer, char *szReadBuffer)
{
	char szSizeBuffer[32];
    DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
    DWORD dwFileSize = 0;
    DWORD dwBytesRead = 0;    
    int iRet= ISAO_ERR_WINSOCK_NOERR;

    ZeroMemory(szReadBuffer,BUF_LEN);
    //int i;
 
    HINTERNET m_Session = NULL;
    m_Session = InternetOpen("AppName",  //¾îÇÃ¸®ÄÉÀÌ¼ÇÀÇ ÀÌ¸§
							INTERNET_OPEN_TYPE_PRECONFIG,  
							// Use registry settings.
                            NULL,
							// Proxy name. NULL indicates use default.
                            NULL,  
							// List of local servers. NULL indicates default.
                            0) ;
    if(!m_Session) 
    {
	    iRet = ISAO_ERR_TCP_CONNECT;
	    return iRet;
    }
 	HINTERNET hHttpFile = NULL;
    hHttpFile = InternetOpenUrl(m_Session, (const char *) szWriteBuffer, NULL,
								0, 0, 0);
    if (hHttpFile)
    {
		BOOL bQuery = HttpQueryInfo(hHttpFile,HTTP_QUERY_CONTENT_LENGTH, szSizeBuffer,
					    &dwLengthSizeBuffer, NULL) ;
	    //BOOL bQuery = InternetQueryDataAvailable(hHttpFile,&dwLengthSizeBuffer,0,0);
        if(bQuery==TRUE)
        {
			dwFileSize=atol(szSizeBuffer);                                                          
            dwFileSize > BUF_LEN ? dwFileSize = BUF_LEN :
			dwFileSize = dwFileSize;
 
            BOOL bRead = InternetReadFile(hHttpFile, szReadBuffer,dwFileSize, &dwBytesRead);
            if (bRead)
            {
				if((bRead == TRUE)&&(dwFileSize !=dwBytesRead))
				{			
					iRet = ISAO_ERR_RECONNECT;
				}		
				
            }
		   else iRet = ISAO_ERR_RECONNECT;
            InternetCloseHandle(hHttpFile);
		}
	}
    else
    {
	    iRet = ISAO_ERR_TCP_CONNECT;
	    return iRet;
    }
    if(hHttpFile) InternetCloseHandle(hHttpFile);
    if(m_Session) InternetCloseHandle(m_Session);
    return iRet;
}
/*
int ISAOCHECK::connect_WEBdb( char *szWriteBuffer, char *szReadBuffer)
{
	struct timeval tmv;    //timeval
	struct sockaddr_in server;
	char Value = '\0';
	char Msg[1024] = "";
	SOCKET Fd;
	
	int iLen;
	int iRet= ISAO_ERR_WINSOCK_NOERR;
	int iSelectRet;
	
    fd_set fdset;

	//-----------------------------------------------
	// º¸Åë »ç¿ëµÇ´Â TCP ¼ÒÄÏ ÀÛ¼º
	//-----------------------------------------------
	WORD         wSocketVersion;
	WSADATA      wsaData;
    int          iError;

	wSocketVersion = MAKEWORD(1,1);
	iError = WSAStartup(wSocketVersion,&wsaData);
	if(iError != 0)
	{
		return ISAO_ERR_WINSOCK_START;
	}
	if(HIBYTE(wsaData.wVersion) != 1 || LOBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return ISAO_ERR_WINSOCK_VERSION;
	}	

	Fd = socket (AF_INET,SOCK_STREAM,0);
	memset(&server,0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(hostPORT );					//Å¬¶ó½º³»¿¡¼­ ¼ÂÆÃ 
	server.sin_addr.s_addr = inet_addr(hostName);		//hostPORT hostName

	//ygy : ¼öÁ¤ ºÎºÐ
	//struct hostent* ClanHostName = gethostbyname(hostName);
	//memcpy(&server.sin_addr.s_addr , ClanHostName->h_addr_list[0],ClanHostName->h_length);
	//end ygy
	//connect
	if (connect( Fd, (struct sockaddr *)&server,sizeof(server)) == -1){
		return ISAO_ERR_TCP_CONNECT;
	}


   	
	//ktj : ÀÓ½Ã
	//fd2( "send( %s )", szWriteBuffer  );
	send(Fd,szWriteBuffer,strlen(szWriteBuffer)+1,0);

	tmv.tv_sec = iTimeOut;		// º¸³½ÈÄ ´ë±â½Ã°£¸¸Å­¸¸ ´äº¯À» ±â´Ù¸²
	tmv.tv_usec = 0;
	FD_ZERO( &fdset );			// read select
    FD_SET( Fd, &fdset );		// fdÀÇ ÇÃ·¡±× ¼ÂÆÃ
	iSelectRet = select( Fd + 1, &fdset, (fd_set*)NULL,(fd_set*)NULL,&tmv);		// ´äº¯À» ¹Þ´Âµ¿¾È °è¼Ó ´ë±âÇÔ.

	if( iSelectRet > 0 && FD_ISSET( Fd, &fdset ) ){		// ¼º°øÇß´Ù

	}else{												// ½ÇÆÐÇß´Ù
		iRet = ISAO_ERR_SSL_TIMEOUT;
		goto IsaoCheck_Free;
	}




	ZeroMemory(szReadBuffer,sizeof(szReadBuffer));
	long startTime, endTime ;
	time( &startTime  );

	int rcnt=0;
	while(1) {
		iLen = recv(Fd,szReadBuffer,BUF_LEN-1,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		//iLen = recv(Fd,szReadBuffer,20,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		
		if(iLen==0) {
			Sleep(100);
		}
		else if(iLen == SOCKET_ERROR)				// error
		{
	        int error = WSAGetLastError();
			if(error==10054)    {
				iRet = ISAO_ERR_SSL_TIMEOUT;
				goto IsaoCheck_Free;
			}
		}
		else {					//µ¥ÀÌÅ¸¹Þ¾ÒÀ¸¹Ç·Î ³¡³½´Ù.
			break;
		}

		time( &endTime);
		if( (endTime-startTime) > 2) {		//2ÃÊÁ¤µµ±â´Ù·Á¼­ ´äÀÌ¾È¿À¸é ¸®ÄÁ³ØÇÏµµ·ÏÇÔ.
			iRet = ISAO_ERR_RECONNECT;
			goto IsaoCheck_Free;
		}
	}


	if( iLen < 0 ){
		iRet = ISAO_ERR_SSL_READ;				// ÀÐÀ» ¼ö ¾ø¾ú´Ù£®½ÇÆÐÀÌ´Ù£®

		
		goto IsaoCheck_Free;
	}
	szReadBuffer[iLen] = 0;
	
	//µð¹ö±×¿ëÀ¸·Î Ç¥½ÃÇÔ.
	//fd2( "\nFrom server: ---from--\n%s--end--\n ÀÐÀº ±æÀÌ´Â %d ",szReadBuffer, iLen );
	
IsaoCheck_Free:

	closesocket( Fd );
	fd2("\n À¥db Á¢±Ù ³¡³²." );

	return iRet;
}


//ygy
int ISAOCHECK::connect_WEBdb_1( char *szWriteBuffer, char *szReadBuffer)
{
	struct timeval tmv;    //timeval
	struct sockaddr_in server;
	char Value = '\0';
	char Msg[1024] = "";
	SOCKET Fd;
	
	int iLen;
	int iRet= ISAO_ERR_WINSOCK_NOERR;
	int iSelectRet;
	
    fd_set fdset;

	//-----------------------------------------------
	// º¸Åë »ç¿ëµÇ´Â TCP ¼ÒÄÏ ÀÛ¼º
	//-----------------------------------------------
	WORD         wSocketVersion;
	WSADATA      wsaData;
    int          iError;

	wSocketVersion = MAKEWORD(1,1);
	iError = WSAStartup(wSocketVersion,&wsaData);
	if(iError != 0)
	{
		return ISAO_ERR_WINSOCK_START;
	}
	if(HIBYTE(wsaData.wVersion) != 1 || LOBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return ISAO_ERR_WINSOCK_VERSION;
	}	

	Fd = socket (AF_INET,SOCK_STREAM,0);
	memset(&server,0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(hostPORT1 );
	server.sin_addr.s_addr = inet_addr(hostName1);		//hostPORT hostName//Å¬¶ó½º³»¿¡¼­ ¼ÂÆÃ 	

	//ygy : ¼öÁ¤ ºÎºÐ
	//struct hostent* ClanHostName = gethostbyname(hostName1);
	//memcpy(&server.sin_addr.s_addr , ClanHostName->h_addr_list[0],ClanHostName->h_length);
	//ygy

	//connect
	if (connect( Fd, (struct sockaddr *)&server,sizeof(server)) == -1){
		return ISAO_ERR_TCP_CONNECT;
	}


   	
	//ktj : ÀÓ½Ã
	//fd2( "send( %s )", szWriteBuffer  );
	send(Fd,szWriteBuffer,strlen(szWriteBuffer)+1,0);

	tmv.tv_sec = iTimeOut;		// º¸³½ÈÄ ´ë±â½Ã°£¸¸Å­¸¸ ´äº¯À» ±â´Ù¸²
	tmv.tv_usec = 0;
	FD_ZERO( &fdset );			// read select
    FD_SET( Fd, &fdset );		// fdÀÇ ÇÃ·¡±× ¼ÂÆÃ
	iSelectRet = select( Fd + 1, &fdset, (fd_set*)NULL,(fd_set*)NULL,&tmv);		// ´äº¯À» ¹Þ´Âµ¿¾È °è¼Ó ´ë±âÇÔ.

	if( iSelectRet > 0 && FD_ISSET( Fd, &fdset ) ){		// ¼º°øÇß´Ù

	}else{												// ½ÇÆÐÇß´Ù
		iRet = ISAO_ERR_SSL_TIMEOUT;
		goto IsaoCheck_Free;
	}


	


	long startTime, endTime ;
	time( &startTime  );

	int rcnt=0;
	while(1) {
		iLen = recv(Fd,szReadBuffer,BUF_LEN,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		//iLen = recv(Fd,szReadBuffer,20,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		
		if(iLen==0) {
			Sleep(100);
		}
		else if(iLen == SOCKET_ERROR)				// error
		{
	        int error = WSAGetLastError();
			if(error==10054)    {
				iRet = ISAO_ERR_SSL_TIMEOUT;
				goto IsaoCheck_Free;
			}
		}
		else {					//µ¥ÀÌÅ¸¹Þ¾ÒÀ¸¹Ç·Î ³¡³½´Ù.
			break;
		}

		time( &endTime);
		if( (endTime-startTime) > 2) {		//2ÃÊÁ¤µµ±â´Ù·Á¼­ ´äÀÌ¾È¿À¸é ¸®ÄÁ³ØÇÏµµ·ÏÇÔ.
			iRet = ISAO_ERR_RECONNECT;
			goto IsaoCheck_Free;
		}
	}


	if( iLen < 0 ){
		iRet = ISAO_ERR_SSL_READ;				// ÀÐÀ» ¼ö ¾ø¾ú´Ù£®½ÇÆÐÀÌ´Ù£®

		
		goto IsaoCheck_Free;
	}
	szReadBuffer[iLen] = 0;
	
	//µð¹ö±×¿ëÀ¸·Î Ç¥½ÃÇÔ.
	//fd2( "\nFrom server: ---from--\n%s--end--\n ÀÐÀº ±æÀÌ´Â %d ",szReadBuffer, iLen );
	
IsaoCheck_Free:

	closesocket( Fd );
	fd2("\n À¥db Á¢±Ù ³¡³²." );

	return iRet;
}
*/


//binaryµ¥ÀÌÅ¸¸¦ ÀÐ´Â°æ¿ì¿¡ »ç¿ëÇÔ.(ÆÄÀÏµî..)
int ISAOCHECK::connect_WEBdb_BINARY( char *szWriteBuffer, char *szReadBuffer, int *dataSize)
{
	struct timeval tmv;    //timeval
	struct sockaddr_in server;
	char Value = '\0';
	char Msg[1024] = "";
	SOCKET Fd;
	
	int iLen;
	int iRet= ISAO_ERR_WINSOCK_NOERR;
	int iSelectRet;
	
    fd_set fdset;
		
	//-----------------------------------------------
	// º¸Åë »ç¿ëµÇ´Â TCP ¼ÒÄÏ ÀÛ¼º
	//-----------------------------------------------
	WORD         wSocketVersion;
	WSADATA      wsaData;
    int          iError;
    
	wSocketVersion = MAKEWORD(1,1);
	iError = WSAStartup(wSocketVersion,&wsaData);
	if(iError != 0)
	{
		return ISAO_ERR_WINSOCK_START;
	}
	if(HIBYTE(wsaData.wVersion) != 1 || LOBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return ISAO_ERR_WINSOCK_VERSION;
	}	

	Fd = socket (AF_INET,SOCK_STREAM,0);
	memset(&server,0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(hostPORT1 );					//Å¬¶ó½º³»¿¡¼­ ¼ÂÆÃ 
	//server.sin_addr.s_addr = inet_addr(hostName);		//hostPORT hostName
	//server.sin_addr.s_addr = inet_addr(hostName1);		//hostPORT hostName
	//ygy
	struct hostent* ClanHostName = gethostbyname(hostName1);
	memcpy(&server.sin_addr.s_addr , ClanHostName->h_addr_list[0],ClanHostName->h_length);
	//ygy
	//connect
	if (connect( Fd, (struct sockaddr *)&server,sizeof(server)) == -1){
		return ISAO_ERR_TCP_CONNECT;
	}
   	
	//ktj : ÀÓ½Ã
	//fd2( "send( %s )", szWriteBuffer  );
	send(Fd,szWriteBuffer,strlen(szWriteBuffer)+1,0);

	tmv.tv_sec = iTimeOut;		// º¸³½ÈÄ ´ë±â½Ã°£¸¸Å­¸¸ ´äº¯À» ±â´Ù¸²
	tmv.tv_usec = 0;
	FD_ZERO( &fdset );			// read select
    FD_SET( Fd, &fdset );		// fdÀÇ ÇÃ·¡±× ¼ÂÆÃ
	iSelectRet = select( Fd + 1, &fdset, (fd_set*)NULL,(fd_set*)NULL,&tmv);		// ´äº¯À» ¹Þ´Âµ¿¾È °è¼Ó ´ë±âÇÔ.

	if( iSelectRet > 0 && FD_ISSET( Fd, &fdset ) ){		// ¼º°øÇß´Ù

	}else{												// ½ÇÆÐÇß´Ù
		iRet = ISAO_ERR_SSL_TIMEOUT;
		goto IsaoCheck_Free;
	}

	//ktj : °íÄ§

	
	/*
	int rcnt=0;
	while(1) {
		iLen = recv(Fd,&szReadBuffer[rcnt],BUF_LEN,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		rcnt += iLen;
		if(iLen==0) break;
	}
	*/

	time_t startTime, endTime ;
	time( ( time_t* )&startTime );

	
	int rcnt=0;

	/*
	//ktj : ¿øº»
	while(1) {
		iLen = recv(Fd,szReadBuffer,BUF_LEN,0);		//½ÇÁ¦ ÀÐ´Â´Ù.

		rcnt+=iLen;
		//iLen = recv(Fd,szReadBuffer,20,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		
		if(iLen==0) {
			Sleep(100);
		}
		else if(iLen == SOCKET_ERROR)				// error
		{
	        int error = WSAGetLastError();
			if(error==10054)    {
				iRet = ISAO_ERR_SSL_TIMEOUT;
				goto IsaoCheck_Free;
			}
		}
		else {					//µ¥ÀÌÅ¸¹Þ¾ÒÀ¸¹Ç·Î ³¡³½´Ù.
			if(rcnt >= 3128) break;
		}

		
		time( &endTime);
		if( (endTime-startTime) > 2) {		//2ÃÊÁ¤µµ±â´Ù·Á¼­ ´äÀÌ¾È¿À¸é ¸®ÄÁ³ØÇÏµµ·ÏÇÔ.
			iRet = ISAO_ERR_RECONNECT;
			goto IsaoCheck_Free;
		}
	}

	*/

	
	while(1) {
		iLen = recv(Fd,&szReadBuffer[rcnt],100,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		rcnt+=iLen;
		//iLen = recv(Fd,szReadBuffer,20,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		if(iLen==0) {
			//Sleep(100);
			if(rcnt >= 3126)		//µ¥ÀÌÅ¸¹Þ¾ÒÀ¸¹Ç·Î ³¡³½´Ù.
				break;
		}
		else if(iLen == SOCKET_ERROR)				// error
		{
	        int error = WSAGetLastError();
			if(error==10054)    {
				iRet = ISAO_ERR_SSL_TIMEOUT;
				goto IsaoCheck_Free;
			}
		}
		else 
		{					

		}

		time( ( time_t* )&endTime );
		if( (endTime-startTime) > 10) {		//10ÃÊÁ¤µµ±â´Ù·Á¼­ ´äÀÌ¾È¿À¸é ¸®ÄÁ³ØÇÏµµ·ÏÇÔ.
			iRet = ISAO_ERR_RECONNECT;
			goto IsaoCheck_Free;
		}
	}







	*dataSize = rcnt ;
	

	if( iLen < 0 ){
		iRet = ISAO_ERR_SSL_READ;				// ÀÐÀ» ¼ö ¾ø¾ú´Ù£®½ÇÆÐÀÌ´Ù£®
		
		goto IsaoCheck_Free;
	}
	//szReadBuffer[iLen] = 0;
	
	//µð¹ö±×¿ëÀ¸·Î Ç¥½ÃÇÔ.
	//fd2( "\nFrom server: ---from--\n%s--end--\n ÀÐÀº ±æÀÌ´Â %d ",szReadBuffer, iLen );
	
IsaoCheck_Free:

	closesocket( Fd );
	fd2("\n À¥db Á¢±Ù ³¡³²." );

	return iRet;
}



/*
if( (i = send(iSock, (char*)data, l, 0)) == SOCKET_ERROR)
    //if( (i = send(iSock, (char*)cmd.data, cmd.dataLen, 0)) == SOCKET_ERROR)
    {
        error = WSAGetLastError();
        if(error==10054) {
			//ktj
            //fd(" sW Error %d: cmd.dataLen %d ret %d  closeCLIENT", error, cmd.dataLen);
            closeCLIENT();   //ÀÏ´Ü ´ÝÀ½
        }
        if(error == 10035) {
            fdWrite = 0;            //¾²±â ±ÝÁöÇÑ´Ù.
        }
        return 0;
    }



//binaryµ¥ÀÌÅ¸¸¦ ÀÐ´Â°æ¿ì¿¡ »ç¿ëÇÔ.(ÆÄÀÏµî..)
int ISAOCHECK::connect_WEBdb_BINARY( char *szWriteBuffer, char *szReadBuffer, int *dataSize)
{
	struct timeval tmv;    //timeval
	struct sockaddr_in server;
	char Value = '\0';
	char Msg[1024] = "";
	SOCKET Fd;
	
	int iLen;
	int iRet= ISAO_ERR_WINSOCK_NOERR;
	int iSelectRet;
	
    fd_set fdset;
		
	//-----------------------------------------------
	// º¸Åë »ç¿ëµÇ´Â TCP ¼ÒÄÏ ÀÛ¼º
	//-----------------------------------------------
	WORD         wSocketVersion;
	WSADATA      wsaData;
    int          iError;
    
	wSocketVersion = MAKEWORD(1,1);
	iError = WSAStartup(wSocketVersion,&wsaData);
	if(iError != 0)
	{
		return ISAO_ERR_WINSOCK_START;
	}
	if(HIBYTE(wsaData.wVersion) != 1 || LOBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return ISAO_ERR_WINSOCK_VERSION;
	}	

	Fd = socket (AF_INET,SOCK_STREAM,0);
	memset(&server,0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(hostPORT );					//Å¬¶ó½º³»¿¡¼­ ¼ÂÆÃ 
	server.sin_addr.s_addr = inet_addr(hostName);		//hostPORT hostName
	//connect
	if (connect( Fd, (struct sockaddr *)&server,sizeof(server)) == -1){
		return ISAO_ERR_TCP_CONNECT;
	}
   	
	//ktj : ÀÓ½Ã
	//fd2( "send( %s )", szWriteBuffer  );
	send(Fd,szWriteBuffer,strlen(szWriteBuffer)+1,0);

	tmv.tv_sec = iTimeOut;		// º¸³½ÈÄ ´ë±â½Ã°£¸¸Å­¸¸ ´äº¯À» ±â´Ù¸²
	tmv.tv_usec = 0;
	FD_ZERO( &fdset );			// read select
    FD_SET( Fd, &fdset );		// fdÀÇ ÇÃ·¡±× ¼ÂÆÃ
	iSelectRet = select( Fd + 1, &fdset, (fd_set*)NULL,(fd_set*)NULL,&tmv);		// ´äº¯À» ¹Þ´Âµ¿¾È °è¼Ó ´ë±âÇÔ.

	if( iSelectRet > 0 && FD_ISSET( Fd, &fdset ) ){		// ¼º°øÇß´Ù

	}else{												// ½ÇÆÐÇß´Ù
		iRet = ISAO_ERR_SSL_TIMEOUT;
		goto IsaoCheck_Free;
	}

	//ktj : °íÄ§
	
	int rcnt=0;
	while(1) {
		iLen = recv(Fd,&szReadBuffer[rcnt],BUF_LEN,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		rcnt += iLen;
		if(iLen==0) break;
	}
	*dataSize = rcnt ;

	if( iLen < 0 ){
		iRet = ISAO_ERR_SSL_READ;				// ÀÐÀ» ¼ö ¾ø¾ú´Ù£®½ÇÆÐÀÌ´Ù£®
		
		goto IsaoCheck_Free;
	}
	//szReadBuffer[iLen] = 0;
	
	//µð¹ö±×¿ëÀ¸·Î Ç¥½ÃÇÔ.
	//fd2( "\nFrom server: ---from--\n%s--end--\n ÀÐÀº ±æÀÌ´Â %d ",szReadBuffer, iLen );
	
IsaoCheck_Free:

	closesocket( Fd );
	fd2("\n À¥db Á¢±Ù ³¡³²." );

	return iRet;
}
*/




//À¥db¿¡¼­ µÇµ¹¾Æ¿Â½ºÆ®¸µ¿¡¼­ intÇü µ¥ÀÌÅ¸¸¦ »Ì¾Æ³¿.
int ISAOCHECK::chk_readbuffer(char *cmd, char *readbuf, int *iRejectC )
{
	int iRejectCode = 111111;			//1Àº Á¦´ë·Î µé¾î¿Â°ÍÀÓ.
	char *pBuf;

	//pBuf = strstr(readbuf,"account=");
	pBuf = strstr(readbuf,cmd);
    if( pBuf == NULL)	//¹ß°ßÇÒ ¼ö ¾ø¾ú´Ù.
	{
		return ISAO_ERR_NONE_REEJCT;
	}

	//pBuf = pBuf + strlen( "account:" );
	pBuf = pBuf + strlen( cmd );
	while(1) {			//½ºÆäÀÌ½º¸¦ ¾ø¾Ø´Ù.
		if(*pBuf != ' ') break;
		pBuf ++;
	}
	sscanf( pBuf , "%d", &iRejectCode );

	return iRejectCode;
}


//À¥ db¿¡¼­ ¿Â ½ºÆ®¸µ¿¡¼­ ¿øÇÏ´Â ½ºÆ®¸µÀ» »Ì¾Æ³¿.
int ISAOCHECK::chk_readStrBuf(char *cmd, char *readbuf, char *retBuf)
{
	int iRejectCode = 111111;			//1Àº Á¦´ë·Î µé¾î¿Â°ÍÀÓ.
	char *pBuf;

	//pBuf = strstr(readbuf,"account=");
	pBuf = strstr(readbuf,cmd);
    if( pBuf == NULL)	//¹ß°ßÇÒ ¼ö ¾ø¾ú´Ù.
	{
		return ISAO_ERR_NONE_REEJCT;
	}

	//pBuf = pBuf + strlen( "account:" );
	pBuf = pBuf + strlen( cmd );
	while(1) {			//½ºÆäÀÌ½º¸¦ ¾ø¾Ø´Ù.
		if(*pBuf != ' ') break;
		pBuf ++;
	}
	sscanf( pBuf , "%s", retBuf );

	return iRejectCode;
}









/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :  int IsaoCheck()
: ÇÏ ´Â ÀÏ :  id¿Í pwdÀÇ À¯È¿¿©ºÎ¸¦ ¾Ë¾Æ³»´Â ÇÔ¼ö·Î
: ¼­    ½Ä :  À¯Àú°¡ °×¼­¹ö¿¡ ÃÖÃÊÁ¢¼Ó½Ã id,pwd°¡ÀÖ´Â À¥db¼­¹ö¿¡ µé¾î°¡ ¾Ë¾Æ³½´Ù.
: ÀÎ    ÀÚ :  
: ¹Ý È¯ °ª :
: ³í    Æò :  ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::IsaoCheck( char *id, char *pass, char *ipaddr, long StartTime )
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
	
	
	sprintf( szWriteBuffer,
		//"POST http://%s/login.php?UserID=%s&PassWord=%s\r\n\r\n\r\n", hostName, id,pass );
		"http://%s/login.php?UserID=%s&PassWord=%s", hostName, id,pass );
	ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
	
	//ktj : ÀÓ½Ã
	fd2(" À¥ db¿¡¼­ ÀÐÀº°Í %s ", szReadBuffer);

	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	
	ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
	case 0: //¾ÆÀÌµð, ÆÐ½º¿öµå Á¤È®	
		//ret_chk = LoginCheck(id,StartTime);			//¸®ÅÏ °ªÀÌ 13ÀÌ¸é Login Å×ÀÌºí¿¡ µî·Ï 14 ÀÌ¸é µî·Ï ½ÇÆÐ
		sprintf(szWriteBuffer,
			//"POST http://%s/LoginCheck.php?UserID=%s&StartTime=%d\r\n\r\n\r\n",hostName, id, StartTime );
			"http://%s/LoginCheck.php?UserID=%s&StartTime=%d", hostName, id, StartTime );
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
		switch(ret_chk)
		{
		case 13:
			goto IsaoCheck_Free;
		case 14:
			goto IsaoCheck_Free;
		}
		goto IsaoCheck_Free;
	case 1: //ÆÐ½º¿öµå ºÒ·®		
		goto IsaoCheck_Free;
	case 2: //¾ÆÀÌµð°¡ µî·ÏµÇÁö ¾Ê¾ÒÀ½
		 //ret_chk = InsertUser(id,pass,"aaaa");
		 sprintf(szWriteBuffer,
			//"POST http://%s/InsertUser.php?UserID=%s&PassWord=%s&UserName=%s\r\n\r\n\r\n",hostName, id,pass,"aaaa");
			"http://%s/InsertUser.php?UserID=%s&PassWord=%s&UserName=%s",hostName, id,pass,"aaaa");
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );

		switch(ret_chk)
		{
		case 3: //µî·Ï Á¤È® 
			//ret_chk = LoginCheck(id,12);		//¸®ÅÏ °ªÀÌ 5ÀÌ¸é Login Å×ÀÌºí¿¡ µî·Ï 6 ÀÌ¸é µî·Ï ½ÇÆÐ
			sprintf(szWriteBuffer,
				//"POST http://%s/LoginCheck.php?UserID=%s&StartTime=%d\r\n\r\n\r\n",hostName, id, StartTime );
			"http://%s/LoginCheck.php?UserID=%s&StartTime=%d",hostName, id, StartTime );
			ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
			ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
		    switch(ret_chk)
			{
		    case 5:
			    goto IsaoCheck_Free;
		    case 6:
			    goto IsaoCheck_Free;
			}
			goto IsaoCheck_Free;
		case 4: //µî·Ï½ÇÆÐ
			goto IsaoCheck_Free;
		 }	
		goto IsaoCheck_Free;


	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}








/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :  int IsaoCheck2()
: ÇÏ ´Â ÀÏ :  À¯Àú°¡ Á¢¼ÓÀ» ²÷À»¶§ »ç¿ëµÊ
: ¼­    ½Ä :  
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò :
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
//°ú±Ý¼­¹ö¿¡ id, ip, Á¢¼ÓÇÏ°í ÀÖ´Â ÃÊ¸¦ ³Ñ°ÜÁØ´Ù.
int ISAOCHECK::IsaoCheck_GameExit(char *id, char *pass, char *ipaddr, long usertime)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
	
	
	
	sprintf( szWriteBuffer, 
	//"POST http://%s/Login_End.php?UserID=%s&IP=%s&EndTime=%d&UseTime=%d\r\n\r\n\r\n",hostName, id,ipaddr,iTimeOut,usertime);
	"http://%s/Login_End.php?UserID=%s&IP=%s&EndTime=%d&UseTime=%d",hostName, id,ipaddr,iTimeOut,usertime);
	ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);

	//ktj : ÀÓ½Ã
	fd2(" À¥ db¿¡¼­ ÀÐÀº°Í %s ", szReadBuffer);
	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
	case 7: //¸®ÅÏ °ªÀÌ 7ÀÌ¸é LogÅ×ÀÌºí(´©Àû Å×ÀÌºí)¿¡ µî·Ï ¼º°øÇÏ¸é¼­ Login Å×ÀÌºí¿¡ ÀÖ´Â µ¥ÀÌÅÍ´Â »èÁ¦
		goto IsaoCheck_Free;

	case 8: //¸®ÅÏ °ªÀÌ 8ÀÌ¸é LogÅ×ÀÌºí(´©Àû Å×ÀÌºí)¿¡ µî·Ï ½ÇÆÐ
		goto IsaoCheck_Free;
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:

	return ret_chk ;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}

















//ygy
/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :  int isCheckClanJang()
: ÇÏ ´Â ÀÏ :  °èÁ¤¿¡ Å¬·£ÀåÀ¸·Î µî·ÏµÇ¾î ÀÖ´ÂÁö Ã¼Å©(100:Å¬·£¸â¹ö, 101:Å¬·£Àå  102:Å¬·£¿øÀÌ ¾Æ´Ï´Ù)
: ¼­    ½Ä :  
: ÀÎ    ÀÚ :  id, °ÔÀÓ¼­¹ö
: ¹Ý È¯ °ª :
: ³í    Æò :  ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :  100,101Àº Å¬·£ÀÌ¸§µµ °¡Á®¿È.
: PROJECT  :  tjboyh/isClanMember.php¿Í ¿¬µ¿µÊ.
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::isCheckClanJang(char *ClanZang_id, char* gserver)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
	
	//ÀÏº»Å¬·£
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/isCheckClanJang.asp?userid=%s&gserver=%s&ticket=%d", hostName, hostPORT, ClanZang_id,gserver,nClanTicket);
	
	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}
	
	//ktj : ÀÓ½Ã
	
	debug_fd2( "isCheckClanJang() SendLen : %d(ret_chk %d) Content:  : %s ", strlen(szWriteBuffer), ret_chk, szWriteBuffer);
	debug_fd2( "isCheckClanJang() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	



	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		//fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			

		//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
		ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
		switch(ret_chk)
		{
		case 0: //Å¬·£ÀÌ µî·ÏµÇ¾î ÀÖÁö ¾ÊÀ½
			break;
		case 1: //Å¬·£¿ø µî·Ï
			break;
		case 5:
			break;
		
		/*
		case 100:	//Å¬·£¿ø
		case 101:	//Å¬·£¯…(°á¼º½É»ç¿Ï·áÈÄ)
		case 102:	//Å¬·£¿øÀ¸·Î °¡ÀÔµÇÀÖÁö ¾ÊÀ½
		case 103:	//°á¼º½É»çÀüÀÌ¸ç 10ÀÏÀÌ Áö³­°æ¿ì
		case 104:	//°á¼º½É»çÀüÀÌ¸ç 10ÀÏÀÌ ¾ÈÁö³­°æ¿ì
		case 105:	//Á¢¼Ó¿¡·¯
		*/			
			break;
			

		case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
			fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
			goto IsaoCheck_Free;
		}



		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}

/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :  int isCheckClanName()
: ÇÏ ´Â ÀÏ :  Å¬·£ ÀÌ¸§ÀÌ Áßº¹µÇ¾ú´ÂÁö Ã¼Å©
: ¼­    ½Ä :  
: ÀÎ    ÀÚ :  id, °ÔÀÓ¼­¹ö
: ¹Ý È¯ °ª :
: ³í    Æò :  ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :  
: PROJECT  :  
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::isCheckClanName(char *ClanName,char *gserver)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];

/*	
//ÀÏº»Å¬·£ÀÌ¸§°Ë»ç
#ifdef _LANGUAGE_JAPANESE

	char UTF8_ClanName[1024];				memset(UTF8_ClanName,0,sizeof(UTF8_ClanName));
	MBCSToWeb(ClanName,				UTF8_ClanName,932);

	
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/isCheckClanName.php?ClName=%s&gserver=%s&ticket=%d", hostName, hostPORT,
	UTF8_ClanName,
	gserver,nClanTicket);

#else
*/	
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/isCheckClanName.asp?ClName=%s&gserver=%s&ticket=%d", hostName, hostPORT, ClanName,gserver,nClanTicket);
//#endif
	

	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	//ktj : ÀÓ½Ã
	

	debug_fd2( "isCheckClanName() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "isCheckClanName() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	

	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		//fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			

		//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
		ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
		switch(ret_chk)
		{
		case 0: //Å¬·£ÀÌ µî·ÏµÇ¾î ÀÖÁö ¾ÊÀ½
			break;
		case 1: //Å¬·£¿ø µî·Ï
			break;
		
		/*
		case 100:	//Å¬·£¿ø
		case 101:	//Å¬·£¯…(°á¼º½É»ç¿Ï·áÈÄ)
		case 102:	//Å¬·£¿øÀ¸·Î °¡ÀÔµÇÀÖÁö ¾ÊÀ½
		case 103:	//°á¼º½É»çÀüÀÌ¸ç 10ÀÏÀÌ Áö³­°æ¿ì
		case 104:	//°á¼º½É»çÀüÀÌ¸ç 10ÀÏÀÌ ¾ÈÁö³­°æ¿ì
		case 105:	//Á¢¼Ó¿¡·¯
		*/				

		case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
			fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
			goto IsaoCheck_Free;
		}



		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}


/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :  int ReadClanInfo(char *clanNum)
: ÇÏ ´Â ÀÏ :  Å¬·£¸¶Å© ¹øÈ£·Î Å¬·£ Á¤º¸ ÀÐ¾î¿À±â
: ¼­    ½Ä :  
: ÀÎ    ÀÚ :  clannum
: ¹Ý È¯ °ª :
: ³í    Æò :  ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :  
: PROJECT  :  
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::ReadClanInfo(char *clanNum,char* ret_Buf)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
	
	//ÀÏº»Å¬·£¹øÈ£
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/isCheckClanNum.asp?num=%s&ticket=%d", hostName, hostPORT, clanNum,nClanTicket);
	
	

	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	//ktj : ÀÓ½Ã
	
	debug_fd2( "ReadClanInfo() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "ReadClanInfo() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	


	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		//fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			

		//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
		ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
		switch(ret_chk)
		{
		case 0: //Å¬·£ÀÌ µî·ÏµÇ¾î ÀÖÁö ¾ÊÀ½
			break;
		case 1: //Å¬·£ Á¤º¸ ÀÐ¾î¿À±â ¼º°ø
			strcpy( ret_Buf, szReadBuffer);
			break;			

		case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
			fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
			goto IsaoCheck_Free;
		}



		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}



//È£µ¿ClanÃß°¡
int ISAOCHECK::isCheckClanMember(char *pszServerName, char *pszUserName)
{
	int		iRejectCode = 111111;
	char	szWriteBuffer[BUF_LEN];
	char	szReadBuffer[BUF_LEN];
	int		receiveCode;

	ZeroMemory(szReadBuffer, sizeof(szReadBuffer));

	sprintf(szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/isCheckClanwon.asp?gserver=%s&clwon=%s",hostName, hostPORT,
	pszServerName,pszUserName);
	
	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		receiveCode = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(receiveCode != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}
	
	if(strlen(szReadBuffer) > 2048) {
		szReadBuffer[2048] = 0;
		debug_fd2( "isClanMember() ³Ê¹«±æ¾î¼­ Àß¶ú´Ù.");
	}

	switch(receiveCode)
	{
		case ISAO_ERR_WINSOCK_NOERR:
		{
			receiveCode = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
			if(receiveCode == ISAO_ERR_NONE_REEJCT)
			{
				fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
			}
		}

		case ISAO_ERR_WINSOCK_START:		//À©¼Ó Start ¿¡·¯ ¹ß»ý
		{
			fd2("WSAStartup()¿¡¶ó");
			break;
		}
		case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó ¹öÀüÀÌ Æ²¸²
		{
			fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
			break;
		}

		case ISAO_ERR_TCP_CONNECT:			//Á¢¼Ó ½ÇÆÐ
		{
			fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
			break;
		}
		case ISAO_ERR_SSL_READ:				//Read ½ÇÆÐ
		{
			fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
			break;
		}
		case ISAO_ERR_SSL_TIMEOUT:			//TimeOut
		{
			fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
			break;
		}
	}
	
	return receiveCode;
}

/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :  int isClanMember()
: ÇÏ ´Â ÀÏ :  Å¬·£¸â¹öÀÎÁö¿©ºÎ(100:Å¬·£¸â¹ö, 101:Å¬·£Àå  102:Å¬·£¿øÀÌ ¾Æ´Ï´Ù)
: ¼­    ½Ä :  
: ÀÎ    ÀÚ :  id, Å¬·£ÀÌ¸§¹ÞÀ» ¹öÆÛ
: ¹Ý È¯ °ª :
: ³í    Æò :  ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :  100,101Àº Å¬·£ÀÌ¸§µµ °¡Á®¿È.
: PROJECT  :  tjboyh/isClanMember.php¿Í ¿¬µ¿µÊ.
///////////////////////////////////////////////////////////////////////////*/

//ktj : isClanMember.php: ¸¦ ¸¸µé¾î³Ö¾î¾ßÇÔ.
int ISAOCHECK::isClanMember(char *ClanZang_id, char* gserver,char* ClanZang_ChaName,char* ret_Buf)
{

	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
	
	ZeroMemory(szReadBuffer , sizeof(szReadBuffer ));

	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/isClanMember.asp?userid=%s&gserver=%s&chname=%s&ticket=%d", hostName, hostPORT, ClanZang_id,gserver,ClanZang_ChaName,nClanTicket);

	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	if(strlen(szReadBuffer) > 2048) {
		szReadBuffer[2048] = 0;
		debug_fd2( "isClanMember() ³Ê¹«±æ¾î¼­ Àß¶ú´Ù.");
	}
	//ktj : ÀÓ½Ã
	
	debug_fd2( "isClanMember() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "isClanMember() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	

	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		//fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			

		//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
		ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
		switch(ret_chk)
		{
		case 0: //Å¬·£ÀÌ µî·ÏµÇ¾î ÀÖÁö ¾ÊÀ½
			strcpy( ret_Buf, szReadBuffer);
			break;
		case 1: //Å¬·£¿ø µî·Ï
//			break;
		case 5:
		case 4:
		case 3:
		case 2: //Å¬·£Àå µî·Ï
			strcpy( ret_Buf, szReadBuffer);
			break;
		/*
		case 100:	//Å¬·£¿ø
		case 101:	//Å¬·£¯…(°á¼º½É»ç¿Ï·áÈÄ)
		case 102:	//Å¬·£¿øÀ¸·Î °¡ÀÔµÇÀÖÁö ¾ÊÀ½
		case 103:	//°á¼º½É»çÀüÀÌ¸ç 10ÀÏÀÌ Áö³­°æ¿ì
		case 104:	//°á¼º½É»çÀüÀÌ¸ç 10ÀÏÀÌ ¾ÈÁö³­°æ¿ì
		case 105:	//Á¢¼Ó¿¡·¯
		*/

			strcpy( ret_Buf, szReadBuffer);
			break;
			

		case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
			fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
			goto IsaoCheck_Free;
		}



		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}




/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :  int joinClanMember()
: ÇÏ ´Â ÀÏ :  Å¬·£¿¡ ¸â¹ö·Î µî·Ï
: ¼­    ½Ä :  
: ÀÎ    ÀÚ :  Å¬·£¿ø id, Å¬·£¿øÀÇ Ä³¸¯ÅÍ id
: ¹Ý È¯ °ª :
: ³í    Æò :  ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :  
: PROJECT  : 
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName,char* ClanName,char* ClanWon,char* ClanWon_ID,int level,DWORD chtype,int joinlevel,char *chipflag)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
/*
//ÀÏº»Å¬·£°¡ÀÔ
#ifdef _LANGUAGE_JAPANESE

	char UTF8_ClanZang_ChaName[1024];		memset(UTF8_ClanZang_ChaName,0,sizeof(UTF8_ClanZang_ChaName));
	char UTF8_ClanName[1024];				memset(UTF8_ClanName,0,sizeof(UTF8_ClanName));
	char UTF8_ClanWon[1024];			memset(UTF8_ClanWon,0,sizeof(UTF8_ClanWon));
	
	MBCSToWeb(ClanZang_ChaName,		UTF8_ClanZang_ChaName,932);
	MBCSToWeb(ClanName,				UTF8_ClanName,932);
	MBCSToWeb(ClanWon,				UTF8_ClanWon,932);

	
	sprintf( szWriteBuffer,
			"http://%s:%d/clanfiles/ServerMain/clanInsertClanWon.php?userid=%s&gserver=%s&chname=%s&clName=%s&clwon=%s&clwonUserid=%s&lv=%d&ticket=%d&chtype=%d&chlv=%d&chipflag=%s", 
			hostName,hostPORT,
			ClanZang_ID,
			gserver,
				UTF8_ClanZang_ChaName,
				UTF8_ClanName,
				UTF8_ClanWon,
			ClanWon_ID,level,nClanTicket,chtype,joinlevel,chipflag);

#else
*/
	sprintf( szWriteBuffer,
			"http://%s:%d/clanfiles/ServerMain/clanInsertClanWon.asp?userid=%s&gserver=%s&chname=%s&clName=%s&clwon=%s&clwonUserid=%s&lv=%d&ticket=%d&chtype=%d&chlv=%d&chipflag=%s", 
			hostName, hostPORT, ClanZang_ID,gserver,ClanZang_ChaName,ClanName,ClanWon,ClanWon_ID,level,nClanTicket,chtype,joinlevel,chipflag);
//#endif



	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	//ktj : ÀÓ½Ã
	
	debug_fd2( "joinClanMember() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "joinClanMember() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	


	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		//fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			

		ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
		switch(ret_chk)
		{
		case 0: //Æ®·£Àè¼Ç ¿À·ù
			break;
		case 1: //Å¬·£¿ø °¡ÀÔ ¼º°ø
			break;
		case 2: //ÇöÀç °¡ÀÔ½ÃÅ°·Á´Â Å¬·£¿øÀÌ ÀÌ¹Ì ´Ù¸¥ Å¬·£¿¡ °¡ÀÔÇØÀÖÀ» °æ¿ì(ÀÚ±â Å¬·£Æ÷ÇÔ)
			break;
		case 3: //Å¬·£ÀÌ Á¸ÀçÇÏÁö ¾Ê°Å³ª Å¬·£ ÀåÀÌ ¾Æ´Ñ°æ¿ì
			break;
		case 4: //Å¬·£ ¸â¹ö°¡ 32 ÀÌ»óÀÏ °æ¿ì(Max : 32)
			break;
		case 100:	//¼º°ø
		case 101:	//Å¬·£ÀÌ¸§ Á¸Àç¾ÈÇÔ.
		case 102:	//Å¬·£¿øÃß°¡½ÇÆÐ
		case 103:	//
			break;

		case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
			fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
			goto IsaoCheck_Free;
		}


		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}




/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :  int makeClan()
: ÇÏ ´Â ÀÏ :  Å¬·£À» »õ·Î¸¸µé°æ¿ìÀÇ ÇÔ¼ö
: ¼­    ½Ä :  
: ÀÎ    ÀÚ :  Å¬·£ÀÌ¸§, ¼³¸í, Å¬·£ÀåÀÇ id°¡ ÇÊ¿äÇÔ.
: ¹Ý È¯ °ª :
: ³í    Æò :  ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::makeClan(char *ClanZang_ID, char* gserver,char* ClanZang_ChaName,char* ClanName,char *explanation,DWORD chtype,int level,char* data)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];

	int chkCnt=0;
	

//ÀÏº»Å¬·£»ý¼º	
 #ifdef _LANGUAGE_JAPANESE

	char UTF8_ClanZang_ChaName[1024];		memset(UTF8_ClanZang_ChaName,0,sizeof(UTF8_ClanZang_ChaName));
	char UTF8_ClanName[1024];				memset(UTF8_ClanName,0,sizeof(UTF8_ClanName));
	char UTF8_explanation[1024];			memset(UTF8_explanation,0,sizeof(UTF8_explanation));
	
	MBCSToWeb(ClanZang_ChaName,		UTF8_ClanZang_ChaName,932);
	MBCSToWeb(ClanName,				UTF8_ClanName,932);
	MBCSToWeb(explanation,			UTF8_explanation,932);
	
	sprintf	//ÀÌºÎºÐ¸¸ ³²°Ü³õÀ½
	(
	szWriteBuffer,
	"http://%s/Clan/clanInsert.asp?userid=%s&gserver=%s&chname=%s&clName=%s&expl=%s&ticket=%d&chtype=%d&lv=%d",
	hostName1,ClanZang_ID, gserver,
		UTF8_ClanZang_ChaName,
		UTF8_ClanName,
		UTF8_explanation,
		nClanTicket,chtype,level 
	);

 #else  

	sprintf
	(
	szWriteBuffer,
	"http://%s/Clan/clanInsert.asp?userid=%s&gserver=%s&chname=%s&clName=%s&expl=%s&ticket=%d&chtype=%d&lv=%d",
	hostName1,ClanZang_ID, gserver,ClanZang_ChaName,ClanName,explanation,nClanTicket,chtype,level 
	);

#endif

	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb_1( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	//ktj : ÀÓ½Ã
	
	debug_fd2( "makeClan() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "makeClan() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	



	
	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	//ygy
	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
		//ygy
	case 0: //Æ®·£Àè¼Ç ¿À·ù
		break;
	case 1: //Å¬·£¿ø °¡ÀÔ¼º°ø
		strcpy( data, szReadBuffer);
		break;
	case 2: //ÇöÀç °¡ÀÔ½ÃÅ°·Á´Â Å¬·£¿øÀÌ ÀÌ¹Ì ´Ù¸¥ Å¬·£¿¡ °¡ÀÔÇØÀÖÀ» °æ¿ì(ÀÚ±â Å¬·£Æ÷ÇÔ)
		break;
	case 3: //Å¬·£ÀÌ Á¸ÀçÇÏÁö ¾Ê°Å³ª Å¬·£ ÀåÀÌ ¾Æ´Ñ°æ¿ì	
		break;
	case 4: //Å¬·£ ¸â¹ö°¡ 32 ÀÌ»óÀÏ °æ¿ì(Max : 32)
		break;
	case 100:
		break;
		/*
	case 0: 
		goto IsaoCheck_Free;
	case 1: //ÆÐ½º¿öµå ºÒ·®		
		goto IsaoCheck_Free;
	case 2: //¾ÆÀÌµð°¡ µî·ÏµÇÁö ¾Ê¾ÒÀ½
		goto IsaoCheck_Free;*/

	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}




/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :int ISAOCHECK::read_ClanName(int readClumns)
: ÇÏ ´Â ÀÏ :
: ¼­    ½Ä : ÄÃ·³À» ³ÖÀ¸¸é ÇØ´ç µ¥ÀÌÅ¸ ¸®ÅÏ
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò :  ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::read_ClanName(int readClumns)
{
	char *clumns[] = {
		"name",
		"explanation",
		"date",
		"Image",
		"clanZang",
		"clanWon1",
		"clanWon2",
		"clanWon3",
		"clanWon4",
		"clanWon5",
		"clanWon6",
	};

	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
	
	sprintf( szWriteBuffer,
		//"POST http://%s/tjboyh/clan_readClanName.php?columnName=%s&ticket=%d\r\n\r\n\r\n", hostName, clumns[readClumns] ,nClanTicket);
		"http://%s/tjboyh/clan_readClanName.asp?columnName=%s&ticket=%d", hostName, clumns[readClumns] ,nClanTicket);
	ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
	
	//ktj : ÀÓ½Ã
	fd2(" À¥ db¿¡¼­ ÀÐÀº°Í %s ", szReadBuffer);


	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	ret_chk = chk_readbuffer("account:", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
	case 0: 
		goto IsaoCheck_Free;
	case 1: //ÆÐ½º¿öµå ºÒ·®		
		goto IsaoCheck_Free;
	case 2: //¾ÆÀÌµð°¡ µî·ÏµÇÁö ¾Ê¾ÒÀ½
		goto IsaoCheck_Free;

	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}






/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :int ISAOCHECK::read_ClanName(int readClumns)
: ÇÏ ´Â ÀÏ :
: ¼­    ½Ä : Å¬¶óÀÌ¾ðÆ® ÀÌ¸§À» ³Ö¾î¼­ Àü Ä®·³ Ãâ·Â
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò :  ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::read_ClanData(char *ClanZang_ID,char* gserver,char* ClanZang_ChaName,char* ret_Buf)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
/*
//ÀÏº»Å¬·£ Å¬·£¿øÀüºÎº¸¿©ÁÜ
#ifdef _LANGUAGE_JAPANESE

	char UTF8_ClanZang_ChaName[1024];		memset(UTF8_ClanZang_ChaName,0,sizeof(UTF8_ClanZang_ChaName));
	
	MBCSToWeb(ClanZang_ChaName,		UTF8_ClanZang_ChaName,932);

	
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/GetAllMyClanMember.php?userid=%s&gserver=%s&chname=%s&ticket=%d", 
		hostName,ClanZang_ID,gserver,
		UTF8_ClanZang_ChaName,
		nClanTicket);

#else
*/
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/GetAllMyClanMember.asp?userid=%s&gserver=%s&chname=%s&ticket=%d", hostName, hostPORT, ClanZang_ID,gserver,ClanZang_ChaName,nClanTicket);
//#endif
	
	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	
	debug_fd2( "read_ClanData() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "read_ClanData() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	

	//fd2(" À¥ db¿¡¼­ ÀÐÀº°Í %s ", szReadBuffer);
	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
		//ygy
	case 0: //°¡ÀÔÇÑ Å¬·£ÀÌ ¾øÀ½
		break;
	case 1://Á¤»ó Ãâ·Â
		strcpy( ret_Buf, szReadBuffer);
		break;
	case 100:					//ok
		strcpy( ret_Buf, szReadBuffer);
	case 101:					//¸øÀÐÀ½.
		goto IsaoCheck_Free;
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}



/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :int ISAOCHECK::BreakUPClan()
: ÇÏ ´Â ÀÏ :
: ¼­    ½Ä : Å¬·£À» »èÁ¦ÇÔ.
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò : ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::BreakUPClan(char *ClanZang_ID,char *gserver,char *ClanZang_ChaName, char *ClanName)
{
	//return -1;		//¸¸µé¾î¾ßÇÔ.

	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
/*
//ÀÏº»Å¬·£»èÁ¦
#ifdef _LANGUAGE_JAPANESE
	char UTF8_ClanZang_ChaName[1024];		memset(UTF8_ClanZang_ChaName,0,sizeof(UTF8_ClanZang_ChaName));
	char UTF8_ClanName[1024];				memset(UTF8_ClanName,0,sizeof(UTF8_ClanName));
	char UTF8_explanation[1024];			memset(UTF8_explanation,0,sizeof(UTF8_explanation));
	
	MBCSToWeb(ClanZang_ChaName,		UTF8_ClanZang_ChaName,932);
	MBCSToWeb(ClanName,				UTF8_ClanName,932);
	
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/clanRemove.php?userid=%s&gserver=%s&chname=%s&clName=%s&ticket=%d",
	hostName,hostPORT,ClanZang_ID,gserver,
		UTF8_ClanZang_ChaName, 
		UTF8_ClanName,
	nClanTicket);

#else
*/
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/clanRemove.asp?userid=%s&gserver=%s&chname=%s&clName=%s&ticket=%d",
	hostName, hostPORT, ClanZang_ID,gserver,ClanZang_ChaName, ClanName,nClanTicket);
//#endif

	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	fd2(" À¥ db¿¡¼­ ÀÐÀº°Í %s ", szReadBuffer);
	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
	case 0: //Æ®·£Àè¼Ç ¿À·ù
		break;
	case 1: //»èÁ¦ ¼º°ø
		break;
	case 2: //ÇöÀç Ä³¸¯¸íÀÌ ÇöÀç Å¬·£ÀÇ ÀåÀÌ ¾Æ´Ï°Å³ª ÇØ´çÅ¬·£ÀÌ ¾øÀ½
		break;
	/*case 100:					//¼º°ø
	case 101:					//clanName Å×ÀÌºí¿¡ Å¬·£¿øÀÌ ÀÖ´Âµ¥ clanWonÅ×ÀÌºí¿¡ ¾øÀ½.
	case 102:					//clanWonÅ×ÀÌºí¿¡¼­ Å¬·£¿ø»èÁ¦ ½ÇÆÐ
	case 103:					//clanName¾È¿¡ Å¬·£ÀÌ¸§ Á¸Àç¾ÈÇÔ.
	case 104:					//clanNameÅ×ÀÌºí¿¡¼­ Å¬·£»èÁ¦ ½ÇÆÐ
		goto IsaoCheck_Free;
		*/
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}


/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :int ISAOCHECK::ReadNotice()
: ÇÏ ´Â ÀÏ :
: ¼­    ½Ä : Å¬·£¿øÀ» Ãß¹æÇÑ´Ù.
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò : ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/

extern char szNoticeUrl[255];


/*///////////////////////////////////////////////////////////////////////////
//noticeÀü¿ë
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::connect_WEBdb_NOTICE(char *szWriteBuffer, char *szReadBuffer)
{
		char szSizeBuffer[32];
    DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
    DWORD dwFileSize = 0;
    DWORD dwBytesRead = 0;    
    int iRet= ISAO_ERR_WINSOCK_NOERR;

    ZeroMemory(szReadBuffer,BUF_LEN);
    //int i;
 
    HINTERNET m_Session = NULL;
    m_Session = InternetOpen("AppName",  //¾îÇÃ¸®ÄÉÀÌ¼ÇÀÇ ÀÌ¸§
							INTERNET_OPEN_TYPE_PRECONFIG,  
							// Use registry settings.
                            NULL,
							// Proxy name. NULL indicates use default.
                            NULL,  
							// List of local servers. NULL indicates default.
                            0) ;
    if(!m_Session) 
    {
	    iRet = ISAO_ERR_TCP_CONNECT;
	    return iRet;
    }
 	HINTERNET hHttpFile = NULL;
    hHttpFile = InternetOpenUrl(m_Session, (const char *) szWriteBuffer, NULL,
								0, 0, 0);
    if (hHttpFile)
    {
		BOOL bQuery = HttpQueryInfo(hHttpFile,HTTP_QUERY_CONTENT_LENGTH, szSizeBuffer,
					    &dwLengthSizeBuffer, NULL) ;
	    //BOOL bQuery = InternetQueryDataAvailable(hHttpFile,&dwLengthSizeBuffer,0,0);
        if(bQuery==TRUE)
        {
			dwFileSize=atol(szSizeBuffer);                                                          
            dwFileSize > BUF_LEN ? dwFileSize = BUF_LEN :
			dwFileSize = dwFileSize;
 
            BOOL bRead = InternetReadFile(hHttpFile, szReadBuffer,dwFileSize, &dwBytesRead);
            if (bRead)
            {
				if((bRead == TRUE)&&(dwFileSize !=dwBytesRead))
				{			
					iRet = ISAO_ERR_RECONNECT;
				}
		
				
            }
		   else iRet = ISAO_ERR_RECONNECT;
		}
	}
    else
    {
	    iRet = ISAO_ERR_TCP_CONNECT;
	    return iRet;
    }
    if(hHttpFile) InternetCloseHandle(hHttpFile);
    if(m_Session) InternetCloseHandle(m_Session);
    return iRet;
}
/*
int ISAOCHECK::connect_WEBdb_NOTICE(char *szServerDomain, int port, char *szWriteBuffer, char *szReadBuffer)
{
	struct timeval tmv;    //timeval
	struct sockaddr_in server;
	char Value = '\0';
	char Msg[1024] = "";
	SOCKET Fd;
	
	int iLen;
	int iRet= ISAO_ERR_WINSOCK_NOERR;
	int iSelectRet;
	
    fd_set fdset;

	//-----------------------------------------------
	// º¸Åë »ç¿ëµÇ´Â TCP ¼ÒÄÏ ÀÛ¼º
	//-----------------------------------------------
	WORD         wSocketVersion;
	WSADATA      wsaData;
    int          iError;

	wSocketVersion = MAKEWORD(1,1);
	iError = WSAStartup(wSocketVersion,&wsaData);
	if(iError != 0)
	{
		return ISAO_ERR_WINSOCK_START;
	}
	if(HIBYTE(wsaData.wVersion) != 1 || LOBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return ISAO_ERR_WINSOCK_VERSION;
	}	



	
	PHOSTENT phe;
	char szIP[16];
	in_addr  ia;
	int cnt,len;
	// µµ¸ÞÀÎÀÌ IPÁÖ¼ÒÀÎÁö È®ÀÎ
	len = lstrlen(szServerDomain);
	for(cnt=0;cnt<len;cnt++) {
		if ( szServerDomain[cnt]!='.' && (szServerDomain[cnt]<'0' || szServerDomain[cnt]>'9') ) break;
	}
	if ( cnt<len ) {
		//DNS ±¸ÇÏ±â
		phe = gethostbyname( szServerDomain );
		if ( phe ) {
			ia.S_un.S_addr = ((unsigned long *)phe->h_addr)[0];
			lstrcpy( szIP , inet_ntoa (ia) );
		}
		else
			return FALSE;
	}
	else {
		//µµ¸ÞÀÎÀÌ IP·Î È®ÀÎ
		lstrcpy( szIP , szServerDomain );
	}



	Fd = socket (AF_INET,SOCK_STREAM,0);
	memset(&server,0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons( port);					//Å¬¶ó½º³»¿¡¼­ ¼ÂÆÃ 
	//server.sin_addr.s_addr = inet_addr(severIP);		//hostPORT hostName
	server.sin_addr.S_un.S_addr = inet_addr ( szIP );

	//connect
	if (connect( Fd, (struct sockaddr *)&server,sizeof(server)) == -1){
		return ISAO_ERR_TCP_CONNECT;
	}


   	
	//ktj : ÀÓ½Ã
	//fd2( "send( %s )", szWriteBuffer  );
	send(Fd,szWriteBuffer,strlen(szWriteBuffer)+1,0);

	tmv.tv_sec = iTimeOut;		// º¸³½ÈÄ ´ë±â½Ã°£¸¸Å­¸¸ ´äº¯À» ±â´Ù¸²
	tmv.tv_usec = 0;
	FD_ZERO( &fdset );			// read select
    FD_SET( Fd, &fdset );		// fdÀÇ ÇÃ·¡±× ¼ÂÆÃ
	iSelectRet = select( Fd + 1, &fdset, (fd_set*)NULL,(fd_set*)NULL,&tmv);		// ´äº¯À» ¹Þ´Âµ¿¾È °è¼Ó ´ë±âÇÔ.

	if( iSelectRet > 0 && FD_ISSET( Fd, &fdset ) ){		// ¼º°øÇß´Ù

	}else{												// ½ÇÆÐÇß´Ù
		iRet = ISAO_ERR_SSL_TIMEOUT;
		goto IsaoCheck_Free;
	}




	ZeroMemory(szReadBuffer,sizeof(szReadBuffer));
	long startTime, endTime ;
	time( &startTime  );

	int rcnt=0;
	while(1) {
		iLen = recv(Fd,szReadBuffer,BUF_LEN-1,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		//iLen = recv(Fd,szReadBuffer,20,0);		//½ÇÁ¦ ÀÐ´Â´Ù.
		
		if(iLen==0) {
			Sleep(100);
		}
		else if(iLen == SOCKET_ERROR)				// error
		{
	        int error = WSAGetLastError();
			if(error==10054)    {
				iRet = ISAO_ERR_SSL_TIMEOUT;
				goto IsaoCheck_Free;
			}
		}
		else {					//µ¥ÀÌÅ¸¹Þ¾ÒÀ¸¹Ç·Î ³¡³½´Ù.
			break;
		}

		time( &endTime);
		if( (endTime-startTime) > 2) {		//2ÃÊÁ¤µµ±â´Ù·Á¼­ ´äÀÌ¾È¿À¸é ¸®ÄÁ³ØÇÏµµ·ÏÇÔ.
			iRet = ISAO_ERR_RECONNECT;
			goto IsaoCheck_Free;
		}
	}


	if( iLen < 0 ){
		iRet = ISAO_ERR_SSL_READ;				// ÀÐÀ» ¼ö ¾ø¾ú´Ù£®½ÇÆÐÀÌ´Ù£®

		
		goto IsaoCheck_Free;
	}
	szReadBuffer[iLen] = 0;
	
	//µð¹ö±×¿ëÀ¸·Î Ç¥½ÃÇÔ.
	//fd2( "\nFrom server: ---from--\n%s--end--\n ÀÐÀº ±æÀÌ´Â %d ",szReadBuffer, iLen );
	
IsaoCheck_Free:

	closesocket( Fd );
	fd2("\n À¥db Á¢±Ù ³¡³²." );

	return iRet;
}
*/

int ConvertURL( char *szURL , char *szServer , char *szPath )
{
	int  cnt,len;
	char *lpServer=0;
	char *lpPath=0;
	char szbuff[256];

	lstrcpy( szbuff, szURL );

	len = lstrlen( szbuff );

	for(cnt=0;cnt<len;cnt++) {
		//(http://)
		if( !lpServer && szbuff[cnt]=='/' && szbuff[cnt+1]=='/' ) {
			lpServer = &szbuff[cnt+2];
			cnt+=2;
		}

		if ( !lpPath && szbuff[cnt]=='/' && szbuff[cnt+1]!='/' ) {
			lpPath = &szbuff[cnt];
		}
	}

	if ( lpPath ) {
		if ( szPath ) 
			lstrcpy( szPath , lpPath );
		lpPath[0] = 0;
	}
	else
		if ( szPath ) szPath[0]=0;

	if ( szServer ) {
		if ( lpServer ) {
			lstrcpy( szServer , lpServer );
		}
		else {
			lstrcpy( szServer , szbuff );
		}
	}

	return TRUE;
}


int ISAOCHECK::ReadNotice(char *userid,char *chaname,char *gserver,char *buf)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];


	char szServer[256], szPath[256];
	ConvertURL( szNoticeUrl, szServer , szPath );

	sprintf( szWriteBuffer,
		"%s?userid=%s&gserver=%s&chname=%s&ticket=%d\r\n\r\n\r\n", szNoticeUrl,userid,gserver,chaname,nClanTicket);

	//sprintf( szWriteBuffer,
	//	"POST %s?userid=%s&gserver=%s&chname=%s\r\n\r\n\r\n", szNoticeUrl, "yuri", "Å×½ºÆ®¼­¹ö", "À¯¸®");

	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		//ret_chk = connect_WEBdb_NOTICE( szServer, 80, szWriteBuffer, szReadBuffer);
		ret_chk = connect_WEBdb_NOTICE(szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;		
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	
	debug_fd2( "ReadNotice() SendLen : %d(ret_chk %d) Content:  : %s ", strlen(szWriteBuffer), ret_chk, szWriteBuffer);
	debug_fd2( "ReadNotice() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	



	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	//ygy
	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	
	//for(int index = 0; index < 10; index++)
		//strcat(szReadBuffer, "skjdflsdklfjlksdjf\n");

	switch(ret_chk)
	{
		//ygy
	case 0: //Æ®·£Àè¼Ç ¿À·ù
		break;
	case 1:
		strcpy( buf, szReadBuffer);
		break;
	case 2: 
		break;
	case 3: 
		break;
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//clanName¿¡ Ãß¹æ À¯Àú ¾÷µ¥ÀÌÆ® ½ÇÆÐ
	case 103:					//clanWon¿¡ Á¢±Ù ½ÇÆÐ
		goto IsaoCheck_Free;
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}
/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :int ISAOCHECK::Banishiment()
: ÇÏ ´Â ÀÏ :
: ¼­    ½Ä : Å¬·£¿øÀ» Ãß¹æÇÑ´Ù.
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò : ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::Banishiment(char *ClanZang_ID,char *gserver,char *ClanZang_ChaName,char *ClanName, char *ClanWon)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
/*
//ÀÏº»Å¬·£¿øÃß¹æ
#ifdef _LANGUAGE_JAPANESE

	char UTF8_ClanZang_ChaName[1024];		memset(UTF8_ClanZang_ChaName,0,sizeof(UTF8_ClanZang_ChaName));
	char UTF8_ClanName[1024];				memset(UTF8_ClanName,0,sizeof(UTF8_ClanName));
	char UTF8_ClanWon[1024];			memset(UTF8_ClanWon,0,sizeof(UTF8_ClanWon));
	
	MBCSToWeb(ClanZang_ChaName,		UTF8_ClanZang_ChaName,932);
	MBCSToWeb(ClanName,				UTF8_ClanName,932);
	MBCSToWeb(ClanWon,				UTF8_ClanWon,932);
	
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/clanWonRelease.php?userid=%s&gserver=%s&chname=%s&clName=%s&%s&ticket=%d",
	hostName,hostPORT,ClanZang_ID,gserver,
	UTF8_ClanZang_ChaName,
	UTF8_ClanName,
	UTF8_ClanWon,
	nClanTicket);
#else
*/
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/clanWonRelease.asp?userid=%s&gserver=%s&chname=%s&clName=%s&%s&ticket=%d", hostName, hostPORT, ClanZang_ID,gserver,ClanZang_ChaName,ClanName,ClanWon,nClanTicket);
//#endif
		

	
	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	
	debug_fd2( "Banishiment() SendLen : %d(ret_chk %d) Content:  : %s ", strlen(szWriteBuffer), ret_chk, szWriteBuffer);
	debug_fd2( "Banishiment() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	



	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	//ygy
	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
		//ygy
	case 0: //Æ®·£Àè¼Ç ¿À·ù
		break;
	case 1: //Å¬·£¿ø Å»Åð ¼º°ø
		break;
	case 2: //Å¬·£ÀÌ Á¸ÀçÇÏÁö ¾Ê°Å³ª Å¬·£ ÀåÀÌ ¾Æ´Ñ°æ¿ì ¶Ç´Â Å¬·£¿øÀÌ ¾Æ´Ñ°æ¿ì
		break;
	case 3: //Å»Åð´Â ¼º°øÇßÀ¸³ª Å¬·£È¸¿ø¼ö°¡ 6¸íÀÌÇÏ·Î ¶³¾îÁ³À» °æ¿ì(LimitDate ¼³Á¤)
		break;
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//clanName¿¡ Ãß¹æ À¯Àú ¾÷µ¥ÀÌÆ® ½ÇÆÐ
	case 103:					//clanWon¿¡ Á¢±Ù ½ÇÆÐ
		goto IsaoCheck_Free;
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}





//ºÎÅ¬·£Àå ÀÓ¸í==================================================================
int ISAOCHECK::AppointSubChip(char *gserver,char* clanwon)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];

/*
//ÀÏº»Å¬·£ºÎÅ¬·£ÀåÀÓ¸í
#ifdef _LANGUAGE_JAPANESE

	char UTF8_clanwon[1024];		memset(UTF8_clanwon,0,sizeof(UTF8_clanwon));
	MBCSToWeb(clanwon,		UTF8_clanwon,932);

	
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/ClanSubChipUpdate.php?chname=%s&gserver=%s&ticket=%d", hostName,hostPORT,
	UTF8_clanwon,
	gserver,9999);//nClanTicket);

#else
*/
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/ClanSubChipUpdate.asp?chname=%s&gserver=%s&ticket=%d", hostName, hostPORT, clanwon,gserver,9999);//nClanTicket);
//#endif
	
	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	debug_fd2( "AppointSubChip() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "AppointSubChip() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);


	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	}
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	//ygy
	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
		//ygy	
	case 0:  //Å¬·£¿øÀÌ ¾Æ´Ô
		break;
	case 2:	//Å¬·£Ä¨ÀÏ¶§
		break;
	case 1:	//ºÎÅ¬·£Ä¨ ÀÓ¸í ¼º°ø
		break;	
	case 3: //ºÎÅ¬·£Ä¨ÀÌ Á¸ÀçÇÔ
		break;
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//clanName¿¡ Ãß¹æ À¯Àú ¾÷µ¥ÀÌÆ® ½ÇÆÐ
	case 103:					//clanWon¿¡ Á¢±Ù ½ÇÆÐ
		goto IsaoCheck_Free;
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}

//ºÎÅ¬·£Àå ÇØÀÓ==================================================================
int ISAOCHECK::ReleaseSubChip(char *gserver,char* clanwon)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];

/*
//ÀÏº»Å¬·£ºÎÅ¬·£ÀåÇØÀÓ
#ifdef _LANGUAGE_JAPANESE

	char UTF8_clanwon[1024];		memset(UTF8_clanwon,0,sizeof(UTF8_clanwon));
	MBCSToWeb(clanwon,		UTF8_clanwon,932);

	
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/ClanSubChipRelease.php?chname=%s&gserver=%s&ticket=%d", 
		hostName,hostPORT,
		UTF8_clanwon,
		gserver,9999);//nClanTicket);

#else
*/
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/ClanSubChipRelease.asp?chname=%s&gserver=%s&ticket=%d", hostName, hostPORT, clanwon,gserver,9999);//nClanTicket);
//#endif
	
	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	debug_fd2( "ReleaseSubChip() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "ReleaseSubChip() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);


	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	}
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	//ygy
	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
		//ygy	
	case 0: //Å¬·£¿øÀÌ ¾Æ´Ô
		break;
	case 2: //Å¬·£Ä¨ÀÌ°Å³ª ºÎÅ¬·£
		break;
	case 1: //ÇØÀÓ¼º°ø
		break;
	
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//clanName¿¡ Ãß¹æ À¯Àú ¾÷µ¥ÀÌÆ® ½ÇÆÐ
	case 103:					//clanWon¿¡ Á¢±Ù ½ÇÆÐ
		goto IsaoCheck_Free;
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}

//ÀÌÀÓ==============================================================
int ISAOCHECK::LeaveClan(char *clanname,char *chaname,char *gserver)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
/*
//ÀÏº»Å¬·£Å¬·£Å»Åð
#ifdef _LANGUAGE_JAPANESE
	char UTF8_chaname[1024];				memset(UTF8_chaname,0,sizeof(UTF8_chaname));
	char UTF8_clanname[1024];			memset(UTF8_clanname,0,sizeof(UTF8_clanname));
	

	MBCSToWeb(chaname,				UTF8_chaname,932);
	MBCSToWeb(clanname,			UTF8_clanname,932);
	
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/clanChipChange.php?chname=%s&gserver=%s&clName=%s&ticket=%d", 
		hostName,hostPORT,
		UTF8_chaname,
		gserver,
		UTF8_clanname,
		nClanTicket);

#else
*/
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/clanChipChange.asp?chname=%s&gserver=%s&clName=%s&ticket=%d", hostName, hostPORT, chaname,gserver,clanname,nClanTicket);
//#endif
	
	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	debug_fd2( "LeaveClan() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "LeaveClan() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);


	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	}
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	//ygy
	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
		//ygy	
	case 1: //º¯°æ ¼º°ø
		break;
	case 2: //Å¬·£¿øÀÌ ¾Æ´Ô
		break;
	case 3: //Á¸ÀçÇÏÁö¾Ê´Â Å¬·£
		break;
	case 4://·¹º§50¹Ì¸¸
		break;
	case 5://±ÇÇÑ ÀÚ°Ý¸¸ ¼º°ø
		break;
	case 6: //ÁöÁ¤Ä³¸¯ÅÍÀÌ¤Ñ Æ÷¿ë ÃÖ´ëÀÎ¿ø¼ö º¸´Ù ÇöÀç ÀÎ¿ø¼ö°¡ Å­
		break;
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//clanName¿¡ Ãß¹æ À¯Àú ¾÷µ¥ÀÌÆ® ½ÇÆÐ
	case 103:					//clanWon¿¡ Á¢±Ù ½ÇÆÐ
		goto IsaoCheck_Free;
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}





/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :int ISAOCHECK::Secession()
: ÇÏ ´Â ÀÏ :
: ¼­    ½Ä : Å¬·£¿øÀ» Å»ÅðÇÑ´Ù.
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò : ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::Secession(char* clanzang,char* gserver,char* SecessionID,char* clanname)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
/*
//ÀÏº»Å¬·£Å»Åð
#ifdef _LANGUAGE_JAPANESE

	char UTF8_clanzang[1024];			memset(UTF8_clanzang,0,sizeof(UTF8_clanzang));
	char UTF8_SecessionID[1024];		memset(UTF8_SecessionID,0,sizeof(UTF8_SecessionID));
	char UTF8_clanname[1024];			memset(UTF8_clanname,0,sizeof(UTF8_clanname));
	
	MBCSToWeb(clanzang,			UTF8_clanzang,932);
	MBCSToWeb(SecessionID,		UTF8_SecessionID,932);
	MBCSToWeb(clanname,			UTF8_clanname,932);


	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/clanWonSelfLeave.php?userid=%s&gserver=%s&chname=%s&clName=%s&ticket=%d",
		hostName,hostPORT,
		UTF8_clanzang,
		gserver,
		UTF8_SecessionID,
		UTF8_clanname,
		nClanTicket);

#else
*/
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/clanWonSelfLeave.asp?userid=%s&gserver=%s&chname=%s&clName=%s&ticket=%d",
		hostName, hostPORT, clanzang,gserver,SecessionID,clanname,nClanTicket);
//#endif

	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	fd2("Secession() À¥ db¿¡¼­ ÀÐÀº°Í %s ", szReadBuffer);
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	}
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	//ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	//ygy
	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
		//ygy
	case 0: //Æ®·£Àè¼Ç ¿À·ù
		break;
	case 1: //Å¬·£¿ø Å»Åð ¼º°ø
		break;
	case 2: //Å¬·£ÀÌ Á¸ÀçÇÏÁö ¾Ê°Å³ª Å¬·£ ÀåÀÌ ¾Æ´Ñ°æ¿ì ¶Ç´Â Å¬·£¿øÀÌ ¾Æ´Ñ°æ¿ì
		break;
	case 3: //Å»Åð´Â ¼º°øÇßÀ¸³ª Å¬·£È¸¿ø¼ö°¡ 6¸íÀÌÇÏ·Î ¶³¾îÁ³À» °æ¿ì(LimitDate ¼³Á¤)
		break;
	case 4://Å»ÅðÇÏ·Á´Â ÀÚ°¡ ÇöÀç Å¬·£ÀÇ Å¬·£ÀåÀÏ °æ¿ì(¿À·ù)
		break;
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//clanName¿¡ Ãß¹æ À¯Àú ¾÷µ¥ÀÌÆ® ½ÇÆÐ
	case 103:					//clanWon¿¡ Á¢±Ù ½ÇÆÐ
		goto IsaoCheck_Free;
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}


/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :int 
: ÇÏ ´Â ÀÏ :
: ¼­    ½Ä : 
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò : ÀÌÀÓ °ü·Ã ÇÃ·¡±× 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::isKPFlag(char *userid,char *clanname, char *chaname,char *gserver,char *pflag, char *gunbun)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
/*
//ÀÏº»Å¬·£KPFlag
#ifdef _LANGUAGE_JAPANESE

	char UTF8_clannamee[1024];			memset(UTF8_clannamee,0,sizeof(UTF8_clannamee));
	char UTF8_chaname[1024];			memset(UTF8_chaname,0,sizeof(UTF8_chaname));

	MBCSToWeb(clanname,			UTF8_clannamee,932);
	MBCSToWeb(chaname,			UTF8_chaname,932);
	
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/isKflag.php?userid=%s&clName=%s&chName=%s&gserver=%s&KFlag=%s&Gubun=%s&ticket=%d",
		 hostName,hostPORT,userid,
		 UTF8_clannamee, 
		 UTF8_chaname,
		 gserver,pflag, gunbun,nClanTicket);

#else
*/
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/isKflag.asp?userid=%s&clName=%s&chName=%s&gserver=%s&KFlag=%s&Gubun=%s&ticket=%d",
		 hostName, hostPORT, userid,clanname, chaname,gserver,pflag, gunbun,nClanTicket);
//#endif
	
	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	
	debug_fd2( "isPFlag() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "isPFlag() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	

	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	}
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//clanName¿¡ ±ÇÇÑ ¾÷µ¥ÀÌÆ® ½ÇÆÐ
		goto IsaoCheck_Free;
	case ISAO_ERR_TCP_CONNECT:		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}

/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :int 
: ÇÏ ´Â ÀÏ :
: ¼­    ½Ä : 
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò : ÃÊ±âÈ­¸é °ü·Ã ÇÃ·¡±× 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::isPFlag(char *userid,char *clanname, char *chaname,char *gserver,char *pflag, char *gunbun)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
/*
//ÀÏº»Å¬·£ÃÊ±âÈ­ÇÃ·¡±×
#ifdef _LANGUAGE_JAPANESE

	char UTF8_clanname[1024];			memset(UTF8_clanname,0,sizeof(UTF8_clanname));
	char UTF8_chaname[1024];			memset(UTF8_chaname,0,sizeof(UTF8_chaname));
	
	MBCSToWeb(clanname,				UTF8_clanname,932);
	MBCSToWeb(chaname,				UTF8_chaname,932);

	
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/isPFlag.php?userid=%s&clName=%s&chName=%s&gserver=%s&PFlag=%s&Gubun=%s&ticket=%d",
		 hostName,hostPORT,userid,
		 UTF8_clanname, 
		 UTF8_chaname,
		 gserver,pflag, gunbun,nClanTicket);

#else
*/
	sprintf( szWriteBuffer,
		"http://%s:%d/clanfiles/ServerMain/isPFlag.asp?userid=%s&clName=%s&chName=%s&gserver=%s&PFlag=%s&Gubun=%s&ticket=%d",
		 hostName, hostPORT, userid,clanname, chaname,gserver,pflag, gunbun,nClanTicket);
//#endif
	

	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	
	debug_fd2( "isPFlag() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "isPFlag() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	

	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	}
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//clanName¿¡ ±ÇÇÑ ¾÷µ¥ÀÌÆ® ½ÇÆÐ
		goto IsaoCheck_Free;
	case ISAO_ERR_TCP_CONNECT:		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}





/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :int 
: ÇÏ ´Â ÀÏ :
: ¼­    ½Ä : 
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò : ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::WarhouseRight(char *clname, char *right_str)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
	
	sprintf( szWriteBuffer,
		//"POST http://%s/tjboyh/clan_WarehouseRight.php?clName=%s&whRight=%s&ticket=%d\r\n\r\n\r\n", hostName, clname,right_str ,nClanTicket);
		"http://%s/tjboyh/clan_WarehouseRight.asp?clName=%s&whRight=%s&ticket=%d", hostName, clname,right_str ,nClanTicket);
	
	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	fd2("WarhouseRight() À¥ db¿¡¼­ ÀÐÀº°Í %s ", szReadBuffer);
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	}
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//clanName¿¡ ±ÇÇÑ ¾÷µ¥ÀÌÆ® ½ÇÆÐ
		goto IsaoCheck_Free;
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}


/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :int 
: ÇÏ ´Â ÀÏ :
: ¼­    ½Ä : 
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò : ½ÇÁ¦ »ç¿ëÇÔ¼ö 
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/
int ISAOCHECK::updateFlag(char *clname)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
	
	sprintf( szWriteBuffer,
		//"POST http://%s/tjboyh/updateFlag.php?clName=%s&ticket=%d\r\n\r\n\r\n", hostName, clname,nClanTicket);
		"http://%s/tjboyh/updateFlag.asp?clName=%s&ticket=%d", hostName, clname,nClanTicket);
	
	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	
	//ktj : ÀÓ½Ã
	fd2("updateFlag() À¥ db¿¡¼­ ÀÐÀº°Í %s ", szReadBuffer);
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	ret_chk = chk_readbuffer("account=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//¾÷µ¥ÀÌÆ® ½ÇÆÐ
		goto IsaoCheck_Free;
		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}












void clanDATA_save(char *fname, char *buff, int dataLen)
{
    HANDLE hFile;
	char allFname[64];
	sprintf( allFname,
		"%s\\%s\\%s",SAVE_DIR,szConnServerName, fname);

    DWORD dwAcess =0;
    hFile = CreateFile( allFname, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

    if( hFile != INVALID_HANDLE_VALUE ) {
        //µ¥ÀÌÅ¸ ¾²±â     ¹öÆÛ    ¾µÅ©±â    ½ÇÁ¦·Î ¾²¿©Áø ¹ÙÀÌÆ®¼ö
        int chk = WriteFile( hFile , buff , dataLen , &dwAcess , NULL );
        //ÆÄÀÏ ´Ý±â
        CloseHandle( hFile );
    }
}

void clanDATA_save2(char *fname, char *buff, int dataLen)
{
    HANDLE hFile;
	char allFname[64];
	sprintf( allFname,
		"%s\\%s",CLANINFO_DIR,  fname);

    DWORD dwAcess =0;
    hFile = CreateFile( allFname, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

    if( hFile != INVALID_HANDLE_VALUE ) {
        //µ¥ÀÌÅ¸ ¾²±â     ¹öÆÛ    ¾µÅ©±â    ½ÇÁ¦·Î ¾²¿©Áø ¹ÙÀÌÆ®¼ö
        int chk = WriteFile( hFile , buff , dataLen , &dwAcess , NULL );
        //ÆÄÀÏ ´Ý±â
        CloseHandle( hFile );
    }
}

















/*///////////////////////////////////////////////////////////////////////
NPC WavÆÄÀÏ °¡Á®¿À±â
///////////////////////////////////////////////////////////////////////*/

//http://211.39.144.158/NPCSound/darksanc_amb.yul
extern char szWavUrl[255];
int	ISAOCHECK::GetWavFile(char* FileName)
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [BUF_LEN];
	
	strcpy(szNoticeUrl,"211.39.144.158/NPCSound");
	sprintf(szWriteBuffer,"http://%s/%s.yul",szNoticeUrl,FileName);

	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	//g_zip.DeComOpen("darksanc_amb.yul");

	
	//ktj : ÀÓ½Ã
	
	debug_fd2( "GetWavFile() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "GetWavFile() RecvLen : %d Content:  : %s ", strlen(szReadBuffer), szReadBuffer);
	

	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	}
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

	ret_chk = chk_readbuffer("Code=", szReadBuffer, &iRejectCode );
	switch(ret_chk)
	{
	case 100:					//¼º°ø
	case 101:					//±×·±Å¬·£ÀÌ¸§¾øÀ½.
	case 102:					//clanName¿¡ ±ÇÇÑ ¾÷µ¥ÀÌÆ® ½ÇÆÐ
		goto IsaoCheck_Free;
	case ISAO_ERR_TCP_CONNECT:		
	case ISAO_ERR_NONE_REEJCT:					//ÀÀ´ä¹øÈ£°¡ ¾øÀ½.
		fd2("ISAO_ERR_NONE_REEJCT  : ÀÀ´ä¹øÈ£°¡ ¾øÀ½" );
		goto IsaoCheck_Free;
	}
	

IsaoCheck_Free:
	return ret_chk;


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}


/*
//ktj : ¼­¹ö¿¡ÀÖ´Â ÆÄÀÏÀ» ´Ù¿î¹Þ¾Æ ÆÄÀÏ·Î ÀúÀåÇÏ´Â ÇÔ¼öÀÓ.
*/
int ISAOCHECK::read_ClanImage(char *clanname,char *filename)
{
	int dataSize=0;
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [65536];	//ÀÓ½Ã
	char szBMPName[255];
	//char GSever;
	//char UniqueClanNum[64];

	ZeroMemory(szBMPName,sizeof(char)*255);




/*

	//============¿øº» start

	//ktj : ÀÌ·¸°Ô ÇØµµ ÆÄÀÏÀ» °¡Á®¿À´Âµ¥ ÁöÀå¾ø½¿. "GET http://%s/tjboyh/a.bmp\n\r\n\r\n", hostName);
	sprintf( szWriteBuffer,
		  "GET http://%s/ClanContent/%s.bmp\r\n\r\n\r\n\r\n", hostName1, filename);

	int cnt=0;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		//ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		ret_chk = connect_WEBdb_BINARY( szWriteBuffer, szReadBuffer, &dataSize);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}
	//============¿øº» end
*/
	
	//ÃÖ±Ù °íÄ£°Í
	sprintf( szWriteBuffer,
		//"http://211.39.144.158/ClanContent/%s.bmp",filename);
		"http://%s/ClanContent/%s.bmp", hostName1, filename);
		  //"GET http://211.39.144.158/ClanContent/713000102.bmp\r\n\r\n\r\n\r\n");


	int cnt=0;
	BOOL bret_chk = FALSE;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		bret_chk = GetHttpRequest(szWriteBuffer,szReadBuffer,65536,&dataSize);
		if(bret_chk) break;
		else cnt++;
		if(cnt>5) break;
		
	}
	




	//ktj : ÀÓ½Ã
	
	debug_fd2( "read_ClanImage() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "read_ClanImage() RecvLen : %d Content:  : bmpÆÄÀÏ¾ÕÀÇ2°³¸¸ÂïÀ½ %c%c. ", strlen(szReadBuffer), szReadBuffer[0],szReadBuffer[1]);
	




	
	
	

	//ÀÓ½Ã
	if((szReadBuffer[0] == 'B')&&(szReadBuffer[1] == 'M'))
	{
		char server[4];
		char uniqueclannum[64];
		
		//server = filename[0];
		//strcpy(uniqueclannum,&filename[3]);

		int nClanMarklen =0;
		
		ZeroMemory(server,sizeof(server));
		nClanMarklen = lstrlen(filename);
		if(nClanMarklen == 9) {
			server[0] = filename[0];
			strcpy(uniqueclannum,&filename[3]);
		}
		else{
			server[0] = filename[0];
			server[1] = filename[1];
			strcpy(uniqueclannum,&filename[4]);
		}

		//wsprintf(szBMPName,"%s.bmp",filename);
		wsprintf(szBMPName,"%s_%s.%s",server ,uniqueclannum,SAVE_EXE);
		clanDATA_save(szBMPName, szReadBuffer, dataSize);

		char path[128];
		char path2[128];
		int bmpSAVE(char *loadfname, char *savefname);
		wsprintf(path,"%s\\%s\\%s",SAVE_DIR,szConnServerName,szBMPName);
		wsprintf(path2,"%s\\%s\\%s_%s_16.%s",SAVE_DIR,szConnServerName,server ,uniqueclannum,SAVE_EXE);

		bmpSAVE(path, path2);

		ret_chk = 1;
	}
	else
	{
		ret_chk = 2;
	}

	/*char *Convert_HS2bin(char *hs_buf, int len);
	char *banaryData = Convert_HS2bin(szReadBuffer, dataSize/2);


	char saveFname[64];
	sprintf( saveFname, "CLAN_%s", filename);		//¹ÞÀºÆÄÀÏÀº CLAN_ÀÌ¶ó´Â ÀÌ¸§ÀÌ ¸Ç¾Õ¿¡ ºÙÀ½.
	clanDATA_save(saveFname, banaryData , dataSize/2);
	delete banaryData ;
	*/



	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		//ktj : µ¥ÀÌÅ¸ ¿ö³«±æ¾î ÇÁ¸°Æ®±ÝÁö
		fd2( "¼­¹ö·Î ºÎÅÍ ÀÐÀº dataSize : %d ", dataSize);
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}

int ISAOCHECK::read_ClanImage2(char *clanname,char *filename,CLANINFO *ci)
{
	int dataSize=0;
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [65536];	//ÀÓ½Ã
	char szBMPName[255];

	ZeroMemory(szBMPName,sizeof(char)*255);





	/*
	//============¿øº» s

	//ktj : ÀÌ·¸°Ô ÇØµµ ÆÄÀÏÀ» °¡Á®¿À´Âµ¥ ÁöÀå¾ø½¿. "GET http://%s/tjboyh/a.bmp\n\r\n\r\n", hostName);
	sprintf( szWriteBuffer,
		//"POST http://%s/tjboyh/fileDOWN.php?filename=%s\r\n\r\n\r\n", hostName, filename);
		//"GET http://%s/tjboyh/clanimage/%s\n\r\n\r\n", hostName, filename);	//ktj.:OK -> ÀÌ·¸°Ô ÇÏ¸é ÆÄÀÏ¸¸ ¿Â´Ù.
		  "GET http://%s/ClanContent/%s.bmp\r\n\r\n\r\n\r\n", hostName1,filename);
	
	int cnt=0;
	
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		//ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		ret_chk = connect_WEBdb_BINARY( szWriteBuffer, szReadBuffer, &dataSize);
		if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		cnt++;
	}

	//============¿øº» e
	*/





	
	//ÃÖ±Ù °íÄ£°Í

	sprintf( szWriteBuffer,
		"http://%s/ClanContent/%s.bmp", hostName1,filename);
		  //"GET http://211.39.144.158/ClanContent/713000102.bmp\r\n\r\n\r\n\r\n");

	int cnt=0;
	BOOL bret_chk = FALSE;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		bret_chk = GetHttpRequest(szWriteBuffer,szReadBuffer,65536,&dataSize);
		if(bret_chk) break;
		else cnt++;
		//ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
		//ret_chk = connect_WEBdb_BINARY( szWriteBuffer, szReadBuffer, &dataSize);
		//if(ret_chk != ISAO_ERR_RECONNECT) break;
		if(cnt>5) break;
		//cnt++;
	}
	



	//ktj : ÀÓ½Ã
	
	debug_fd2( "read_ClanImage2() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	debug_fd2( "read_ClanImage2() RecvLen : %d Content:  : bmpÆÄÀÏ¾ÕÀÇ2°³¸¸ÂïÀ½ %c%c. ", strlen(szReadBuffer), szReadBuffer[0],szReadBuffer[1]);
	





	
	char path[128];
	char path1[128];
	//ÀÓ½Ã
	if((szReadBuffer[0] == 'B')&&(szReadBuffer[1] == 'M'))
	{

		//wsprintf(szFile,"%s\\%c_%s.bmp",CLANINFO_DIR,ClanInfo[ClanInfo_nNum].ClanInfoHeader.Gserver,ClanInfo[ClanInfo_nNum].ClanInfoHeader.UniqueClaClanInfo_nNum);
		//wsprintf(szBMPName,"%s.bmp",filename);	
		

		wsprintf(szBMPName,"%s_%s.%s",ci->ClanInfoHeader.Gserver ,
								ci->ClanInfoHeader.UniqueClaClanInfo_nNum,
								SAVE_EXE);
		clanDATA_save(szBMPName, szReadBuffer, dataSize);

		
		int bmpSAVE(char *loadfname, char *savefname);
		wsprintf(path,"%s\\%s\\%s",SAVE_DIR,szConnServerName,szBMPName);
		wsprintf(path1,"%s\\%s\\%s_%s_16.%s",SAVE_DIR,szConnServerName,ci->ClanInfoHeader.Gserver ,ci->ClanInfoHeader.UniqueClaClanInfo_nNum,SAVE_EXE);

		bmpSAVE(path, path1);

		ret_chk = 1;
	}
	else
	{
		ret_chk = 2;
	}

	/*char *Convert_HS2bin(char *hs_buf, int len);
	char *banaryData = Convert_HS2bin(szReadBuffer, dataSize/2);


	char saveFname[64];
	sprintf( saveFname, "CLAN_%s", filename);		//¹ÞÀºÆÄÀÏÀº CLAN_ÀÌ¶ó´Â ÀÌ¸§ÀÌ ¸Ç¾Õ¿¡ ºÙÀ½.
	clanDATA_save(saveFname, banaryData , dataSize/2);
	delete banaryData ;
	*/



	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		//ktj : µ¥ÀÌÅ¸ ¿ö³«±æ¾î ÇÁ¸°Æ®±ÝÁö
		fd2( "¼­¹ö·Î ºÎÅÍ ÀÐÀº dataSize : %d ", dataSize);
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}











//¹ÙÀÌ³Ê¸® sorce¸¦ dest¿¡ hexa½ºÆ®¸µÀ¸·Î ¹Ù²ãÀúÀåÇÔ.
void ISAOCHECK::Convert_bin2HS(char *sorce, int len)
{
	int i, j, Len;
	for(i=0; i<30; i++) {			//µ¥ÀÌÅ¸°¡ ÀÖÀ¸¸é Áö¿î´Ù.
		if(fileDATA_HS[i])	delete fileDATA_HS[i];
	}

	HSsu = len / 2048;
	if(len % 2048) HSsu++;
	char byte0, byte1;


	for(j=0; j<HSsu; j++)
	{
		if(j== (HSsu-1) ) {
			fileDATA_HS[j] = new char [ (len%2048)*2+1];			//hexa ½ºÆ®¸µÀº 2¹è°¡ µÊ.
			Len = len%2048;
		}
		else {
			fileDATA_HS[j] = new char [   (2048*2)+1];
			Len = 2048;
		}

		for(i=0; i<Len; i++) {
			byte0 = *sorce & 0x0f;
			byte1 = (*sorce & 0xf0)>>4;
			sorce++;

			if(byte0<10) {
				fileDATA_HS[j][i*2 + 0] = byte0+'0';
			}
			else {
				fileDATA_HS[j][i*2 + 0] = (byte0-10)+'A';
			}
	
			if(byte1<10) {
				fileDATA_HS[j][i*2 + 1] = byte1+'0';
			}
			else {
				fileDATA_HS[j][i*2 + 1] = (byte1-10)+'A';
			}
		}
		fileDATA_HS[j][i*2] = 0;		//½ºÆ®¸µÀÌ¶ó ¸¶Áö¸·¿¡ 0À» ºÙ¿©¾ßÇÔ.
	}
}


//hexa ½ºÆ®¸µÀ» ¹ÙÀÌ³Ê¸®·Î ¹Ù²ãÀúÀå.
char *Convert_HS2bin(char *hs_buf, int len)
{
	char *dest;
	char byte0, byte1;
	dest = new char [len];			

	for(int i=0; i<len; i++) {
		byte0 = hs_buf[i*2 + 0];		//hexa½ºÆ®¸µÀº ±æÀÌÀÇ µÎ¹è¶ó¼­..
		byte1 = hs_buf[i*2 + 1];
			
		if( byte0 <='9') {
			 byte0 -= '0';
		}
		else {
			 byte0 -= 'A';
			 byte0 += 10;
		}

		if( byte1 <='9') {
			 byte1 -= '0';
		}
		else {
			 byte1 -= 'A';
			 byte1 += 10;
		}
		dest[i] = (byte1<<4) | byte0;
	}
	return dest;
}



char *fileREAD(char *fileName, char *buf, int *len)
{
    HANDLE hFile;
    DWORD dwAcess =0;
	char *newBuf;
    hFile = CreateFile( fileName, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE,
                        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL , NULL );

    if ( hFile == INVALID_HANDLE_VALUE ) return 0;

    //SetFilePointer( hFile , 0, NULL , FILE_BEGIN );
	*len = GetFileSize( hFile , NULL );
	if(*len==0) goto closeJMP;

	if(buf == NULL) {
		newBuf= new char[*len];
	}
	else {
		newBuf= buf ;
	}
	ReadFile( hFile , newBuf , *len , &dwAcess , NULL );

    

closeJMP:
    CloseHandle( hFile );

    return newBuf;
}






//ÆÄÀÏÀÌ¹ÌÁö¸¦ ÀÐ¾î¼­ hexa½ºÆ®¸µÀ¸·Î ¹Ù²ã¼­ º¯¼ö¿¡ ³Ö¾îº¸³½´Ù.
int ISAOCHECK::write_ClanImageFile(char *fname)
{
	int i;
	int dataSize=0;
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN*5];
	char szReadBuffer [BUF_LEN*5];	//ÀÓ½Ã
	

	//char fileName[] = "image\\clanDATA\\a222.txt";
	char fileName[64];
	char OrigFName[] = "a.bmp";
	char *fileBuf=NULL;
	int len;

	sprintf( fileName,"%s\\%s\\%s",SAVE_DIR,szConnServerName, fname	);


	fileBuf = fileREAD(fileName, NULL, &len);

	Convert_bin2HS(fileBuf, len);		//binary->hexa stringÀ¸·Î º¯È¯
	if(fileBuf) 
		delete fileBuf;


	
	//ÀÌ°Ç ³ªÁß¿¡ ÆÄÀÏÀ» ÀÐ¾î¿À´Â ÇÔ¼ö¿¡ ³ÖÀ»°Í.
	//Convert_HS2bin(hs_fileBuf , len);

	/*
	//file_DATAºÎºÐÀÌ ±æ¸é ¼­¹ö¿¡¼­ too large ¿¡·¯¸¦ º¸³¿......
	sprintf( szWriteBuffer,
		"POST http://%s/tjboyh/clan_insertClanImage.php?file_name=%s&file_DATA=%s\r\n\r\n\r\n", hostName,OrigFName, fileDATA_HS[0]);
	//"GET http://%s/tjboyh/a.bmp\n\r\n\r\n", hostName);
	//"GET /tjboyh/ktj_login.php http/1.0\n\r\n\r\n");	//ktj.:OK
	//"GET http://%s/tjboyh/abc.txt\n\r\n\r\n", hostName);	//ktj.:OK -> ÀÌ·¸°Ô ÇÏ¸é ÆÄÀÏ¸¸ ¿Â´Ù.
	//"GET /tjboyh/abc.txt http/1.0\n\r\n\r\n");	//ktj.:OK -> ÀÌ·¸°Ô ÇÏ¸é ¼­¹öÆÄÀÏÀÇ Á¤º¸¿ÍÇÔ²² ÆÄÀÏÀÌ¿Â´Ù.
	
	while(1) {
	ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
	if(szReadBuffer[0]!=0) 
		break;
	}

	//ktj : ÀÓ½Ã
	fd2(" À¥ db¿¡¼­ ÀÐÀº°Í %s ", szReadBuffer);
	*/







	for(i=0; i<HSsu; i++) 
	{
		sprintf( szWriteBuffer,	//file_name=ÆÄÀÏÀÌ¸§&file_HSsu=2048¹ÙÀÌ³Ê¸®(4096Çí»ç½ºÆ®¸µ)µ¢¾î¸®°¹¼ö&file_cnt=µ¢¾î¸®Ä«¿îÆ®&file_DATA=ÆÄÀÏÀÇ µ¥ÀÌÅ¸.
			"POST http://%s/tjboyh/clan_insertClanImage.asp?file_name=%s&file_HSsu=%d&file_cnt=%d&file_DATA=%s\r\n\r\n\r\n", hostName,OrigFName,    HSsu,i+1,fileDATA_HS[i]);

		while(1) {
			ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
			if(szReadBuffer[0]!=0) 
				break;
		}
	}

	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		//fd2( "From server: ---from--\n%s--end--\n ",szReadBuffer);			
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end


IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}























/*///////////////////////////////////////////////////////////////////////////
: ÇÔ ¼ö ¸í :  int Exam()
: ÇÏ ´Â ÀÏ :  À¥µðºñ¿Í ¿¬°áÇÏ±âÀ§ÇÑ example·Î
: ¼­    ½Ä :  ÀÌÇÔ¼ö¿¡¼­ °ËÁõÀ» °ÅÃÄº»´Ù.
: ÀÎ    ÀÚ :
: ¹Ý È¯ °ª :
: ³í    Æò :
: ¹ö    Àü :
: PROJECT  :
///////////////////////////////////////////////////////////////////////////*/

int ISAOCHECK::WEBdb_Exam()
{
	int ret_chk;
	int iRejectCode = 111111;
	char szWriteBuffer[1024];
	char szReadBuffer [1024]={0,};
	
	
	sprintf( szWriteBuffer,
		"POST http://%s/tjboyh/ktj_login.php\r\n\r\n\r\n" ,hostName);
	ret_chk = connect_WEBdb( szWriteBuffer, szReadBuffer);
	
	//ktj : ÀÓ½Ã
	fd2(" À¥ db¿¡¼­ ÀÐÀº°Í %s ", szReadBuffer);
	
	return ret_chk ;
}


void WEBdb_Exam()
{
	iCheck.init_HostName_Port("211.192.180.113", 80);
	iCheck.init(1, 20);
	iCheck.WEBdb_Exam();
}


/*
//ktj : ¼­¹ö¿¡ÀÖ´Â ÆÄÀÏÀ» ´Ù¿î¹Þ¾Æ ÆÄÀÏ·Î ÀúÀåÇÏ´Â ÇÔ¼öÀÓ.
*/
int ISAOCHECK::read_sod2(char *usid, char *charname,char *gserver, int index , char *szSod2Buff)
{
	int dataSize=0;
	int ret_chk = 0; 
	int iRejectCode = 111111;
	char szWriteBuffer[BUF_LEN];
	char szReadBuffer [65536];	//ÀÓ½Ã
	memset(szSod2Buff,0,sizeof(szSod2Buff));
	memset(szWriteBuffer,0,sizeof(szWriteBuffer[BUF_LEN]));
	memset(szReadBuffer,0,sizeof(szReadBuffer));

/*
//ÀÏº»Å¬·£ÀÌ¾Æ´Ï°íSOD
#ifdef _LANGUAGE_JAPANESE

	char UTF8_charname[1024];				memset(UTF8_charname,0,sizeof(UTF8_charname));

	MBCSToWeb(charname,				UTF8_charname,932);
	
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/sod2info.php?userid=%s&chname=%s&gserver=%s&index=%d", hostName,hostPORT, usid, 
	UTF8_charname, 
	gserver, index);

#else
*/
	sprintf( szWriteBuffer,
	"http://%s:%d/clanfiles/ServerMain/sod2info.asp?userid=%s&chname=%s&gserver=%s&index=%d", hostName, hostPORT, usid, charname, gserver, index);
//#endif

	int cnt=0;
	BOOL bret_chk = FALSE;
	while(1) {		//ÄÁ³ØÆ®µÇµµ ´äÀÌ ¾È¿À´Â°æ¿ì¸¦ À§ÇØ 5¹øÁ¤µµ ÀçÁ¢ÇÑ´Ù.
		bret_chk = GetHttpRequest(szWriteBuffer,szSod2Buff,65536,&dataSize);
		if(bret_chk) break;
		else cnt++;
		if(cnt>5) break;
		 
	}

	//ktj : ÀÓ½Ã
	//debug_fd2( "read_ClanImage() SendLen : %d Content:  : %s ", strlen(szWriteBuffer), szWriteBuffer);
	//debug_fd2( "read_ClanImage() RecvLen : %d Content:  : bmpÆÄÀÏ¾ÕÀÇ2°³¸¸ÂïÀ½ %c%c. ", strlen(szReadBuffer), szReadBuffer[0],szReadBuffer[1]);
	
	//ktj : ¾Æ·¡ Ã½Å©´Â ¸ðµÎ ÀÓ½ÃÀûÀ¸·Î ¿î¿µµÊ

	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== start
	switch(ret_chk) {
	case ISAO_ERR_WINSOCK_NOERR:		//¿¡·¯ ¾øÀ½.
		//ktj : ÀÓ½Ã·Î ¼­¹ö¿¡¼­ ¿Â µ¥ÀÌÅ¸¸¦ »Ñ·Áº½.
		//ktj : µ¥ÀÌÅ¸ ¿ö³«±æ¾î ÇÁ¸°Æ®±ÝÁö
		fd2( "¼­¹ö·Î ºÎÅÍ ÀÐÀº dataSize : %d ", dataSize);
		break;
	case ISAO_ERR_WINSOCK_START:		//À©¼Ó START½Ã ¿¡·¯¹ß»ý				//window only
		fd2("WSAStartup()¿¡¶ó");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_WINSOCK_VERSION:		//À©¼Ó¹öÀüÀÌ Æ²·Á ±¸µ¿µÇÁö¸øÇÔ.			//window only
		fd2("¹öÀüÀÌ ¸ÂÁö ¾ÊÀ½");
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_TCP_CONNECT:			// º¸Åë »ç¿ëµÇ´Â £Ô£Ã£ÐÄÚ³×ÄíÅä¿¡¶ó
		fd2( "connect() Á¢¼Ó ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_READ:				// £Ó£Ó£Ì ¸®µå ÇÒ ¼ö ¾ø¾ú´Ù£®
		fd2(" recv()  ÀÐ±â ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	case ISAO_ERR_SSL_TIMEOUT:			// Å¸ÀÓ ¾Æ¿ôÇß´Ù£®
		fd2("---------------- select() Å¸ÀÓ¾Æ¿ô ½ÇÆÐ" );
		goto IsaoCheck_winsockERR;
	};
	//winsock »óÀÇ ¿¡·¯ Ã½Å©ÇÔ.  ================================== end

IsaoCheck_winsockERR:			//winsockÀ¸·Î ¿¬°á½Ã¿¡·¯³²
	return ret_chk ;
}



bool UTF8ToWeb(char *szUTF8,char *szWeb)
{
	int iCount = 0;
	char chHigh;
	char chLow;
	for(int i=0;szUTF8[i]!=0;i++)
	{
		chHigh = chLow = 0;
		

		// %»ðÀÔ
		szWeb[iCount] = '%';
		iCount++;

		//»óÀ§ ºñÆ®
		chHigh = (szUTF8[i] & 0xf0) >> 4;

		if( (0<= chHigh) &&	(chHigh <= 9))
		{
			szWeb[iCount] = '0' + chHigh;
			iCount++;
		}
		else
		{
			szWeb[iCount] = 'a' + chHigh - 0x0a;
			iCount++;
		}

		//ÇÏÀ§ ºñÆ®
		chLow = szUTF8[i] & 0x0f;

		if( (0<= chLow) && (chLow <= 9) )
		{
			szWeb[iCount] = '0' +  chLow;
			iCount++;
		}
		else
		{
			szWeb[iCount] = 'a' + chLow - 0x0a;
			iCount++;
		}

	}
	szWeb[iCount] = 0;
	
	return true;	
}

bool MBCSToUTF8(char *szMBCS,char *szUTF8,int iMBCSCodePage)
{
	wchar_t wUniCode[1024];	memset(wUniCode,0,sizeof(wUniCode));

	//À¯´ÏÄÚµå·Î º¯È¯ => °ªÀº wUnicode¿¡
	MultiByteToWideCharByCodePage(szMBCS,wUniCode,iMBCSCodePage);

	//UTF8·Î º¯È¯ => °ªÀº szUTF8¿¡
	WideCharToMultiByteByCodePage(wUniCode,szUTF8,CP_UTF8);

	return true;
}

bool	MultiByteToWideCharByCodePage(char *szMBCS,wchar_t *szUnicode,int iCodePage)
{
	int iLen = MultiByteToWideChar(iCodePage, 0, szMBCS, lstrlen(szMBCS), NULL, NULL);
	MultiByteToWideChar(iCodePage, 0, szMBCS, lstrlen(szMBCS), szUnicode, iLen);

	return true;
}



bool	WideCharToMultiByteByCodePage(wchar_t *szUnicode,char *szMBCS,int iCodePage)
{//wcslen
	int iLen = WideCharToMultiByte(iCodePage, 0, szUnicode, wcslen(szUnicode), NULL, NULL,NULL,NULL);
	WideCharToMultiByte(iCodePage, 0, szUnicode, wcslen(szUnicode), szMBCS, iLen,NULL,NULL);

	return true;
}

bool MBCSToWeb(char *szMBCS,char *szWeb,int iMBCSCodePage)
{
	char szUTF8[1024];	memset(szUTF8,0,sizeof(szUTF8));
	MBCSToUTF8(szMBCS,szUTF8,iMBCSCodePage);
	UTF8ToWeb(szUTF8,szWeb);
	return true;
}

