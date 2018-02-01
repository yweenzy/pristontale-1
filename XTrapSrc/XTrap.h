
/******************************************************************************
// XTrap.h Version 0xD5000001
// By WiseLogic
//****************************************************************************/

#ifndef __XTRAPMODULE_H
#define __XTRAPMODULE_H

#define		CREATEKF_OUT_SIZE	544
#define		CREATEKF_IN_SIZE	264

extern HANDLE	g_XTrapMsgEvent;

///////////////////////////////////////////////////////////////////////////////
// XTrap Interface External Variable
///////////////////////////////////////////////////////////////////////////////

extern char	g_sXTrapCode[MAX_PATH];		/* XTrap ErrorCode XX-XX-XXXX */

///////////////////////////////////////////////////////////////////////////////
// XTrap Interface External Function
///////////////////////////////////////////////////////////////////////////////

/*required*/void SetXTrapStartInfo		(CHAR *pGameName, 
										 DWORD ApiVersion, DWORD VendorCode, DWORD KeyboardType, DWORD PatchType, DWORD ModuleType);
/*required*/void XTrapStart				();
/*required*/void XTrapKeepAlive			();

/*optional*/void SetXTrapMgrInfo		(IN CHAR *pMgrIp);
/*optional*/void SetXTrapPatchHttpUrl	(IN CHAR *pHttpUrl);
/*optional*/void SetOptGameInfo			(IN CHAR *pUserName,  IN CHAR *pGameServerName, IN CHAR *pCharacterName, 
									     IN CHAR *pClassName, IN long UserLevel);

/*optional*/DWORD CreateKFEx			(IN  PUCHAR	pVerHash,	/* XTrapCC Version Verify Hash Value					*/
										 IN  PUCHAR	pInBuf,		/* Encyption[AddressTable(256byte) + RandomKey(8byte)]	*/
										 IN	 UCHAR	CMF_Cnt,	/* ServerSide CMF Count									*/
										 OUT PUCHAR	pOutBuf);	/* Generate Key											*/
/*Optional*/void SendLogToMgr			();

/*Optional*/void SetKeyboardModule		( HINSTANCE hInstance, BOOL bKeybdModule, LPVOID lpvReserved );

#endif