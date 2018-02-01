#ifndef	_DRAWSUB_HEADER

#define _DRAWSUB_HEADER

#define	dsARRAY_LEFT	0
#define	dsARRAY_TOP		0
#define	dsARRAY_RIGHT	1
#define	dsARRAY_BOTTOM	2


extern int	dsDrawOffsetArray;

extern int	dsDrawOffset_X;
extern int	dsDrawOffset_Y;


int dsTextLineOut( HDC hdc , int x, int y, LPCTSTR lpszString , int nCount );		//문자열 출력
int dsGetDrawOffset( int *sx , int *sy );		//메뉴 좌표 보정
int dsMenuCursorPos( POINT *lpCursorPos , int Mode );	//메뉴커서 시물레이션

//색깔있는 상자 그린다
int dsDrawColorBox( DWORD Color ,int x, int y, int sizeX, int sizeY );
int dsDrawColorBoxFloat( DWORD Color ,float x, float y, float sizeX, float sizeY );

//그림 출력
int dsDrawTexImage( int Mat , int x, int y, int w, int h , DWORD Transp , int specular = 0);

int dsDrawTexImageFloat( int Mat , float x, float y, float w, float h , DWORD dwColor , int specular =0 );

int dsDrawTexImage( int Mat, int x, int y, int w, int h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp);
int dsDrawTexImageFloat( int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp);

int dsDrawTexImageFloatColor( int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, DWORD dwColor );

#endif