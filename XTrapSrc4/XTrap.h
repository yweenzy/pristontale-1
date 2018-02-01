///////////////////////////////////////////////////////////////////////////////
// X-Trap Interface Core
// Version 0xD5000023
///////////////////////////////////////////////////////////////////////////////

#ifndef __XTRAPMODULE_H
#define __XTRAPMODULE_H

/*********************************************************
 X-Trap Interface External Variable
*********************************************************/

extern BOOL g_bApiMal;			/* XTRAP_API_MDL	   : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bMemoryMdl;		/* XTRAP_MEMORY_MDL    : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bAutoMousMdl;		/* XTRAP_AUTOMOUS_MDL  : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bAutoKeybMdl;		/* XTRAP_AUTOKEYB_MDL  : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bMalMdl;			/* XTRAP_MAL_MDL       : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bSpeedMdl;		/* XTRAP_SPEED_MDL     : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bFileMdl;			/* XTRAP_FILE_MDL      : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bApiHookMdl;		/* XTRAP_APIHOOK_MDL   : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bDebugModMdl;		/* XTRAP_DEBUGMOD_MDL  : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bOsMdl;			/* XTRAP_OS_MDL        : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bPatchMdl;		/* XTRAP_PATCH_MDL	   : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */

extern BOOL g_bMemoryCrack;		/* XTRAP_MEMORY_CRACK  : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bFileCrack;		/* XTRAP_FILE_CRACK    : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bApiHookCrack;	/* XTRAP_APIHOOK_CRACK : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */
extern BOOL g_bApiCrack;		/* XTRAP_API_CRACK	   : ACTIVE_DETECT_HACK : ACTIVE_FLAG_NONE */

extern BOOL g_bStartXTrap;		/* XTrap cannot find the file/path specified       */
								/* XTrap program reguires a newer version of Games */


/*********************************************************
 X-Trap Interface External Function
*********************************************************/

/*required*/void XTrapStart				(IN UCHAR *pArgv);
/*Optional*/void XTrapStart				(IN UCHAR *pArgv, IN CHAR *pXTrapPath/*Example:C:\\Game\\Bin*/);
/*required*/void XTrapKeepAlive			();
/*Optional*/void XTrapStop				();

/*optional*/void SetXTrapMgrInfo		(IN CHAR *pMgrIp);
/*optional*/void SetOptGameInfo			(IN CHAR *pUserName,  
										 IN CHAR *pGameServerName, 
										 IN CHAR *pCharacterName, 
									     IN CHAR *pClassName, 
										 IN long UserLevel);

/*Optional*/void SetKeyboardModule		(HINSTANCE hInstance, BOOL bKeybdModule, LPVOID lpvReserved);


///////////////////////////////////////////////////////////////////////////////
// X-Trap Patch Interface Core
///////////////////////////////////////////////////////////////////////////////

/*optional*/VOID XPatchStart			(IN LPSTR pArgv1, IN LPSTR pGamePath);
/*optional*/VOID XPatchStart			(IN LPSTR pArgv1, IN LPSTR pGamePath, IN DWORD dwTimeout/*1000:1second*/);



///////////////////////////////////////////////////////////////////////////////
// X-Trap CrackDefence Core
///////////////////////////////////////////////////////////////////////////////


//----< Buffer Size >
//----[]
#define XTRAP_CC4_BUFFERSIZE_COMMUNICATION_BASE		128

#define XTRAP_CC4_BUFFERSIZE_SESSION_BASE			320
#define XTRAP_CC4_BUFFERSIZE_SESSION_ADDON			80

// XTRAP_CC4_BUFFERSIZE_SESSION_BASE + XTRAP_CC4_BUFFERSIZE_SESSION_ADDON * MAPÆÄÀÏ °¹¼ö = 320 + 80 * 2
#define XTRAP_CC4_BUFFERSIZE_SESSION				480

#define	XTRAP_CC4_FILESIZE_MAP						45000


// Return Value
#define XTRAP_CC_RETURN_OK					0x00000000
#define XTRAP_CC_RETURN_ERROR				0x00000001
#define XTRAP_CC_RETURN_UNKNOWN				0x00000002
#define XTRAP_CC_RETURN_INVALID_PARAMETER	0x00000003
#define XTRAP_CC_RETURN_INVALID_CRC			0x00000004
#define XTRAP_CC_RETURN_TIMEOUT				0x00000005

#define XTRAP_CC_RETURN_DETECTHACK			0x0000000F


// Protect Option
#define	XTRAP_PROTECT_PE					0x00000001
#define	XTRAP_PROTECT_TEXT					0x00000010
#define	XTRAP_PROTECT_RDATA					0x00000100
#define	XTRAP_PROTECT_EDATA					0x00001000
#define	XTRAP_PROTECT_RSRC					0x00010000
#define	XTRAP_PROTECT_RELOC					0x00100000

#define XTRAP_PROTECT_EXCEPT_VIRUS			0x00000002


// Timeout Limit
#define XTRAP_CC_MAXTIMEOUT					(int)600
#define XTRAP_CC_MINTIMEOUT					(int)100


/*********************************************************
 X-Trap CC Ver1,2 Function Define
*********************************************************/

#define		CREATEKF_OUT_SIZE		544
#define		CREATEKF_IN_SIZE		264

/*Optional*/DWORD CreateKF			(IN char *VerHash, IN char *InBuf, OUT char *OutBuf);
/*Optional*/DWORD CreateKFEx		(IN PUCHAR pVerHash, IN PUCHAR pInBuf, IN UCHAR CMF_Cnt, OUT PUCHAR pOutBuf);
/*Optional*/void  SendLogToMgr		();

/*********************************************************
 X-Trap CC Ver3 Function Define
*********************************************************/

DWORD __cdecl XTrapCS_RecvSeedKey	(PUCHAR pSeedKey, DWORD dwMethod);
DWORD __cdecl XTrapCS_DetectCrack	();	

/* Callback Func */
VOID __stdcall XTrapCS_SendUniqKey	(PUCHAR pUniqKey);


/*********************************************************
 X-Trap CC Ver3.1 Function Define
*********************************************************/

DWORD __cdecl XTrapCC_RecvSeedKey	(IN OUT PUCHAR pUserComBuf,	IN DWORD dwMethod );
DWORD __cdecl XTrapCC_DetectCrack	(IN PUCHAR pUserComBuf);


/*********************************************************
 X-Trap CC Ver4 Function Define
*********************************************************/

DWORD __cdecl XTrapCC_STEP2	(
					IN	PUCHAR	pPacketBuf_IN, 
					OUT	PUCHAR	pPacketBuf_OUT, 
					IN	DWORD	dwMethod				);


#endif
