#ifndef __BASEWND_H__
#define __BASEWND_H__
class CBaseWnd
{
public:
	CBaseWnd();
	virtual ~CBaseWnd();
public:
	virtual BOOL SetWndClass(WNDCLASS* wc);
	virtual VOID SetWindowName(char* name);
	virtual VOID SetInstance(HINSTANCE hInst);
	virtual VOID SetParentWnd(HWND hWnd);
	virtual HWND GetParentWnd();	
	virtual HINSTANCE GetInstance();
	virtual BOOL InitClass(WNDCLASSEX wc,WNDPROC wndproc);
	virtual HWND InitWindow(char* clanname= NULL,int x=0, int y=0, int width = 100, int height = 100,HWND hParent = NULL);
	virtual HWND InitWindow(char* clanname,int x, int y, int width, int height,DWORD WndStyle,HWND hParent);
	virtual HWND InitStyleWindow(char *styleEx,int x, int y, int width, int height, DWORD WndStyle, HWND parent, HMENU idnum);

public:
	virtual inline HWND GetWnd(){return m_hMainWnd;}
	virtual inline Show(){ShowWindow(m_hMainWnd,SW_SHOW);}
	virtual inline Hide(){ShowWindow(m_hMainWnd,SW_HIDE);}
private:
	HWND m_hParentWnd;
	HWND m_hMainWnd;
	char m_szWindowName[50];
	HINSTANCE m_hInstance;
};


class CListCtrl : public CBaseWnd
{
public:
	HWND ListCtrl_Create(int x, int y, int width, int height,DWORD WndStyle,HWND parent,HMENU num)
	{		
		m_hMainWnd = InitStyleWindow(WC_LISTVIEW,x,y,width,height,WndStyle,parent,num);		

		return m_hMainWnd;
	}
public:
	HWND m_hMainWnd;
};
#endif