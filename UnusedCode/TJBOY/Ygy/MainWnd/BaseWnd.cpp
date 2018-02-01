#include "GlobalHeader.h"
#include "BaseWnd.h"
CBaseWnd::CBaseWnd()
{
	m_hMainWnd = NULL;
}

CBaseWnd::~CBaseWnd()
{
}

BOOL CBaseWnd::SetWndClass(WNDCLASS* wc)
{
	return RegisterClass(wc);
}

BOOL CBaseWnd::InitClass(WNDCLASSEX wc,WNDPROC wndproc)
{
	WNDCLASSEX WcEx;

	memset(&WcEx,0,sizeof(WNDCLASSEX));

	memcpy(&WcEx,&wc,sizeof(WNDCLASSEX));
	

	
	WcEx.lpfnWndProc = wndproc;
	
	
	if(!RegisterClassEx(&WcEx))
	{
		return FALSE;
	}
	return TRUE;
}

HWND CBaseWnd::InitWindow(char* clanname,int x, int y, int width, int height,HWND hParent)
{
	DWORD dwWindowStyle;

	dwWindowStyle = WS_POPUP|WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|
                          WS_MINIMIZEBOX|WS_VISIBLE;        

	m_hMainWnd = CreateWindowEx(0,clanname,m_szWindowName,dwWindowStyle,
		x,y,width,height,hParent,NULL,m_hInstance,0);

	if(m_hMainWnd == NULL)
		return NULL;

	return m_hMainWnd;


}

HWND CBaseWnd::InitWindow(char* clanname,int x, int y, int width, int height,DWORD WndStyle,HWND hParent)
{	
	m_hMainWnd = CreateWindowEx(0,clanname,m_szWindowName,WndStyle,
		x,y,width,height,hParent,NULL,m_hInstance,0);	

	if(m_hMainWnd == NULL)
		return NULL;

	return m_hMainWnd;
}

HWND CBaseWnd::InitStyleWindow(char *styleEx,int x, int y, int width, int height, DWORD WndStyle, HWND parent, HMENU idnum)
{
	m_hMainWnd = CreateWindow(styleEx,NULL,WndStyle,
		x,y,width,height,parent,idnum,m_hInstance,0);	

	if(m_hMainWnd == NULL)
		return NULL;

	ShowWindow(m_hMainWnd,SW_SHOW);

	return m_hMainWnd;
}


VOID CBaseWnd::SetWindowName(char* name)
{
	strcpy(m_szWindowName,name);
}

VOID CBaseWnd::SetInstance(HINSTANCE hInst)
{
	m_hInstance = hInst;
}

HINSTANCE CBaseWnd::GetInstance()
{
	return m_hInstance;
}

VOID CBaseWnd::SetParentWnd(HWND hWnd)
{
	m_hParentWnd = hWnd;
}

HWND CBaseWnd::GetParentWnd()
{
	return m_hParentWnd;
}

