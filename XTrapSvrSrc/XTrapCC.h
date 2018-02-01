
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the XTRAPCC_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// XTRAPCC_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
/*
#ifdef XTRAPCC_EXPORTS
#define XTRAPCC_API __declspec(dllexport)
#else
#define XTRAPCC_API __declspec(dllimport)
#endif

EXTERN_C XTRAPCC_API int fnXTrapCC(int, int);
*/

/*////////////////////////////////////////////////////////////////////

Copyright (c) 2005 WiseLogic Corporation

Author:
 WiseLogic Apr, 13, 2006

*//////////////////////////////////////////////////////////////////////

#ifndef __XTRAPCCMODULE_H
#define __XTRAPCCMODULE_H

#if		defined(XTRAPCC_EXPORTS)
#define XTRAPCC_API __declspec(dllexport)
#elif	defined(XTRAPCC_IMPORTS)
#define XTRAPCC_API __declspec(dllimport)
#else
#define XTRAPCC_API
#endif

#define			XC_CMF_SIZE				4128
#define			XC_KEYVALUE_SIZE		12
#define			XC_ADDR_SIZE			264
#define			XC_CLIENTBUF_SIZE		544

typedef unsigned char XC_CMF		[XC_CMF_SIZE		];
typedef unsigned char XC_KEYVALUE	[XC_KEYVALUE_SIZE	];
typedef unsigned char XC_ADDR		[XC_ADDR_SIZE		];
typedef unsigned char XC_CLIENTBUF	[XC_CLIENTBUF_SIZE	];



#ifdef __cplusplus
extern "C" {
#endif

/* Old Style CrackCheck */
	XTRAPCC_API void SeedKeyGen(char * );				/* Output Generated First Key	*/

	XTRAPCC_API int XCrackCheck(char *,					/* Input Verify Key(From Client)*/
								char *,					/* Input Generated First Key	*/
								char *);				/* Input Client Hash Value		*/

/* New Style CrackCheck */
	XTRAPCC_API void SeedKeyGenEx(	XC_CMF*,			/* Input CMF Pointer			*/
									unsigned char,		/* Input CMF Count				*/
									XC_KEYVALUE*,		/* Output KeyValue				*/
									XC_ADDR*);			/* Output Addr(To Client)		*/

	XTRAPCC_API int XCrackCheckEx(	XC_CMF*,			/* Input CMF Pointer			*/
									unsigned char,		/* Input CMF Count				*/
									XC_KEYVALUE*,		/* Input KeyValue				*/
									XC_CLIENTBUF*);		/* Input ClientBuf				*/
#ifdef __cplusplus
}
#endif

#endif