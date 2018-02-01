
// ***************************************************************
//  X-Trap API for Client (Extra1)
//  -------------------------------------------------------------
//  Copyright (C)WiseLogic 2007 - All Rights Reserved
// ***************************************************************

#pragma once

DWORD XTrap_CE1_Func0_Init		();
DWORD XTrap_CE1_Func0_Init_T	();
DWORD XTrap_CE1_Func0_Init_D	(PUINT	pFunErr, PUINT pLibErr,	PUINT pErrCode);

DWORD XTrap_CE1_Func1_Memory	(LPVOID	lpAddr,	SIZE_T	dwSize);
DWORD XTrap_CE1_Func1_Memory_T	(LPVOID	lpAddr,	SIZE_T	dwSize);
DWORD XTrap_CE1_Func1_Memory_D	(LPVOID	lpAddr,	SIZE_T	dwSize,	PUINT	pFunErr, PUINT	pLibErr, PUINT	pErrCode);

DWORD XTrap_CE1_Func2_Memory	(LPVOID	lpAddr);
DWORD XTrap_CE1_Func2_Memory_T	(LPVOID	lpAddr);
DWORD XTrap_CE1_Func2_Memory_D	(LPVOID	lpAddr,	PUINT pFunErr,	PUINT pLibErr,	PUINT pErrCode);

DWORD XTrap_CE1_Func3_Module	(LPVOID	lpBaseAddr);
DWORD XTrap_CE1_Func3_Module_T	(LPVOID	lpBaseAddr);
DWORD XTrap_CE1_Func3_Module_D	(LPVOID	lpBaseAddr,	PUINT pFunErr, PUINT pLibErr, PUINT	pErrCode);

DWORD XTrap_CE1_Func4_Module	(LPVOID	lpBaseAddr);
DWORD XTrap_CE1_Func4_Module_T	(LPVOID	lpBaseAddr);
DWORD XTrap_CE1_Func4_Module_D	(LPVOID	lpBaseAddr,	PUINT	pFunErr, PUINT pLibErr,	PUINT pErrCode);

DWORD XTrap_CE1_Func5_Init		();
DWORD XTrap_CE1_Func6_Payment	();
DWORD XTrap_CE1_Func7_Payment	();

// 2008-01-21 ADD
DWORD XTrap_CE1_Func10_Init		();
DWORD XTrap_CE1_Func10_Init_D	(PUINT pFuncErr, PUINT pLibErr, PUINT pErrCode);

DWORD XTrap_CE1_Func11_Protect	(LPVOID lpBaseAddr, SIZE_T dwSize);
DWORD XTrap_CE1_Func11_Protect_D(LPVOID lpBaseAddr, SIZE_T dwSize, PUINT pFuncErr, PUINT pLibErr, PUINT pErrCode);

DWORD XTrap_CE1_Func12_Protect	(LPVOID lpBaseAddr, SIZE_T dwSize);
DWORD XTrap_CE1_Func12_Protect_D(LPVOID lpBaseAddr, SIZE_T dwSize, PUINT pFuncErr, PUINT pLibErr, PUINT pErrCode);

DWORD XTrap_CE1_Func13_Free		(LPVOID lpBaseAddr, SIZE_T dwSize);
DWORD XTrap_CE1_Func13_Free_D	(LPVOID lpBaseAddr, SIZE_T dwSize, PUINT pFuncErr, PUINT pLibErr, PUINT pErrCode);

