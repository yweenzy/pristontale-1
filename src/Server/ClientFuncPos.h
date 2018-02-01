//클라이언트 펑션 포지션 추가
int	rsAddClientFuncPos( TRANS_CLIENT_FUNPOS	*lpClentFuncPos );
//클라이언트 펑션 포지션 입수 ( 파일로 저장 )
int	rsRecvClientFuncPos( TRANS_CLIENT_FUNPOS	*lpClentFuncPos );
//클라이언트 펑션 포지션 얻기
TRANS_CLIENT_FUNPOS *rsGetClientPos( int Version );
//클라이언트 펑션 포지션 리셋
int	rsResetClientFuncPos();

//메모리 첵크섬 펑션을 통채로 클라이언트에 보낸다
int rsSendFuncMemToClient( rsPLAYINFO *lpPlayInfo , DWORD dwFuncMem , DWORD	dwLen );
//체크섬 비교
int	rsCompClientFuncMem( rsPLAYINFO *lpPlayInfo , DWORD	dwFunc , DWORD dwChkSum );
//체크섬 비교2
int	rsCompClientFuncMem2( rsPLAYINFO *lpPlayInfo , DWORD dwFuncCode );
//클라이언트 메모리 첵크 모듈 전송
int	rsCheckClientFuncMem( rsPLAYINFO *lpPlayInfo );
