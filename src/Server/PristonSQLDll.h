#ifdef PRISTONSQLDLL_EXPORTS
#define PRISTONSQLDLL_API __declspec(dllexport)
#else
#define PRISTONSQLDLL_API __declspec(dllimport)
#endif


//1) 로그인시 
PRISTONSQLDLL_API int SQLLoginProcess( char * lpUserID );

//2) 캐릭터 생성시
PRISTONSQLDLL_API int SQLAddCharProcess( char * lpUserID, char * lpCharID );

//3) 캐릭터 삭제시
PRISTONSQLDLL_API int SQLDelCharProcess( char * lpUserID, char * lpCharID );

//4) 로그아웃시, Client 접속 끊어졌을시
PRISTONSQLDLL_API int SQLLogoutProcess( char * lpUserID, char * lpCharID, char * lpRace, char * lpOccupation, unsigned long nExpPoint, int nLevel );
