#ifndef __IME_CONTROL_INCLUDE__
#define __IME_CONTROL_INCLUDE__

#include <imm.h>
#include "strclass.h"

class ImeClass
{
//private:
public:
	HWND	m_hWnd;
	HIMC	m_hIMC;

	BOOL	bCandList;
	int		nCandState;
	int		nStartListIdx;
	int		nCandListCount;

	void	GetCompositionString();
	void	GetCompositionStringInfo();
	void	GetCandidateList();
	void	GetImeInfo();
	void	SetCandidateInfo(LPCANDIDATELIST lpCandList);
	void	OnButtonChangemode();

	CStrClass	m_szTitle;
	CStrClass	m_szConvMode;
	CStrClass	m_szHalfMode;
	CStrClass	m_szCOMPOSTR;
	CStrClass	m_szCandList[10];

	CStrClass	m_szResultReadStr;
	CStrClass	m_szCompReadStr;
//public:
	ImeClass();
	virtual ~ImeClass();

	void	GetInfoPerTime();

	void	SetHWND(HWND hWnd){m_hWnd = hWnd;};

	//virtual	void	OPEN();
	//virtual	void	CLOSE();

	int		nTX1;
	//NWRECT	R_MOVE;
	//NWRECT	R_X;
	//NWRECT	R_IMETITLE;
	//NWRECT	R_CONVMODE;
	//NWRECT	R_HALFMODE;
	//NWRECT	R_COMPOSTR;
	//NWRECT	R_CANDLIST[10];

	//void	InitRect();
	//void	RenderContent();
	//void	DrwaText(LPD3DXFONT	_pd3dxFont);

	//BOOL	LbuttonDown(int x,int y);
	//BOOL	LbuttonUp(int x,int y);
	//void	MouseMove(int x,int y);
	//void	MouseOut();

	int		CUR_ON;
	BOOL	bMove;

	POINT	P_MOUSE;

	int		nCurrCompLen;
	int		nPrevCompLen;
};

#endif 
