//공격 수신 받음
int rsRecvAttackData_Old( rsPLAYINFO *lpPlayInfo , TRANS_ATTACKDATA *lpTransAttackData , smCHAR *lpTargetChar , int Type );
//공격 범위형 수신
int rsRecvRangeAttackData_Old( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData , int Type );
//공격 범위형 유저 수신
int rsRecvRangeAttackUserData_Old( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA *lpTransSkilAttackData );


//공격 수신 받음
int rsRecvAttackData( rsPLAYINFO *lpPlayInfo , TRANS_ATTACKDATA2 *lpTransAttackData );
//범위공격 수신 받음
int rsRecvRangeAttackData( rsPLAYINFO *lpPlayInfo , TRANS_SKIL_ATTACKDATA2 *lpTransRangeAttackData );;

//범위 공격 첵크섬
DWORD	dm_GetRangeDamgeChkSum( TRANS_SKIL_ATTACKDATA2 *lpTransSkilAttackData2 );
//범위 공격 첵크섬
DWORD	dm_GetDamgeChkSum( TRANS_ATTACKDATA2 *lpTransAttackData2 );
//코맨드 첵크섬
DWORD	dm_GetCommandChkSum( smTRANS_COMMAND *lpTransCommand , DWORD dwObjectSerial );

//레벨로 정상적인 스킬 코드인지 검사
int rsCheckSkillLevel( rsPLAYINFO *lpPlayInfo , DWORD dwSkillCode );

//데미지 암호 풀기 함수
int	rsDecodeDamagePacket( rsPLAYINFO *lpPlayInfo , void *lpPacket );
//데미지 암호 묶기 함수
int	rsEncodeDamagePacket( rsPLAYINFO *lpPlayInfo , void *lpPacket );
//데미지 암호화 펑션을 통채로 클라이언트에 보낸다
int rsSendDamageFuncToClient( rsPLAYINFO *lpPlayInfo );
//데미지 암호화 펑션을 통채로 클라이언트에 보낸다
int rsSendDamageFuncToClient2( rsPLAYINFO *lpPlayInfo );
//데미지 암호화 키설정
int rsSetDamagePacketKey( rsPLAYINFO *lpPlayInfo );
//암호 모듈 시행
int	rsProcessSafePacket( rsPLAYINFO *lpPlayInfo );
//암호 모듈인지 확인하여 적용
int	rsCompareSafePacket( rsPLAYINFO *lpPlayInfo , DWORD dwRcvPacketCode );

//데미지 데이타 오류를 군서버 로그에 기록
int rsRecordDamageError( rsPLAYINFO *lpPlayInfo , smTRANS_COMMAND *lpTransCommand );
