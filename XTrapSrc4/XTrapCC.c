
#include "XTrapCC.h"

#ifdef _WIN32


 PFN_XTrapCC_ServerInit		XTrapCC_ServerInit		= NULL;
 PFN_XTrapCC_SessionInit	XTrapCC_SessionInit		= NULL;
 PFN_XTrapCC_STEP1			XTrapCC_STEP1			= NULL;
 PFN_XTrapCC_STEP3			XTrapCC_STEP3			= NULL;


unsigned long XTrapCCLoadDll()
{
	unsigned long	ulError			= 0;
	char			sDllBinFile[]	="XTrapCC.Dll";
	void*			hDll_XTrapCC	= NULL;
	
	hDll_XTrapCC = LoadLibrary(sDllBinFile);
	if (hDll_XTrapCC == NULL)
	{	ulError = GetLastError();	return 0x10000000|ulError;	}

	XTrapCC_ServerInit	= (PFN_XTrapCC_ServerInit)	GetProcAddress(hDll_XTrapCC, "XTrapCC_ServerInit");
	XTrapCC_SessionInit	= (PFN_XTrapCC_SessionInit)	GetProcAddress(hDll_XTrapCC, "XTrapCC_SessionInit");
	XTrapCC_STEP1		= (PFN_XTrapCC_STEP1)		GetProcAddress(hDll_XTrapCC, "XTrapCC_STEP1"	);
	XTrapCC_STEP3		= (PFN_XTrapCC_STEP3)		GetProcAddress(hDll_XTrapCC, "XTrapCC_STEP3"	);

	if(	(XTrapCC_ServerInit		== NULL	)	||
		(XTrapCC_SessionInit	== NULL	)	||
		(XTrapCC_STEP1			== NULL	)	||
		(XTrapCC_STEP3			== NULL	)	)
	{
		return	0x20000000;
	}

	return XTRAP_CC_RETURN_OK;
}

#endif