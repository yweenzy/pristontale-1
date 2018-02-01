#include <windows.h>
#include <math.h>
#include <stdio.h>
#include "dsx.h"
#include "sin.h"
#include "obj3d.h"
#include "map3d.h"
#include "texture.h"

extern smGEOMAP	*GEOMAPp;
extern smMAPLINK	MAPLINKp[MAP_SIZE][MAP_SIZE];
static D3DTLVERTEX D3Dvt[4][ MAX_CELL*8 ];

extern int GetMapHeight( int x, int z );
extern HWND hwnd;
extern LPDIRECT3DTEXTURE2 hMapTexture[4];


RECT rectEditWin;

static int wWidth = 640 ;
static int wHeight = 480 ;
static int MapsX = 0;
static int MapsY = 0;
static int CellSize =0;


BYTE MapSelectBuff[ MAP_SIZE * MAP_SIZE ];

int DisplayEditMap( int cellSize , int mx , int my, int mw , int mh )
{

	int x,y;
	int sw,sh;
	int cntX , cntY;
	int cntW , cntH;
	int rcnt[4],cntR;
	int cnt,cnt2;
	int dx[6] = { 0, 1, 0, 1, 1, 0};
	int dy[6] = { 0, 0, 1, 0, 1, 1};
	float tu[6];
	float tv[6];
	int mpX,mpY;
	int tx;

	POINT		p;
	int spec;
	RECT rect;

    GetClientRect(hwnd,&rect);
	
	if ( mw==0 ) mw = 1;
	if ( mh==0 ) mh = 1;

	MapsX = mx; MapsY = my;
	CellSize = cellSize;

	wWidth = rect.right-rect.left;
	wHeight = rect.bottom-rect.top;

	sw = cellSize;
	sh = cellSize;

	rcnt[0] = 0;
	rcnt[1] = 0;
	rcnt[2] = 0;
	rcnt[3] = 0;

	y= my;
	for( cntY=0; cntY<wHeight+sh; cntY+=sh ) {
		x = mx;
		for( cntX=0; cntX<wWidth+sw; cntX+=sw ) {
			cntR = 0;
			tu[0] = MAPLINKp[x][y].u;
			tv[0] = MAPLINKp[x][y].v;
			tu[1] = MAPLINKp[x][y].w;
			tv[1] = MAPLINKp[x][y].v;
			tu[2] = MAPLINKp[x][y].u;
			tv[2] = MAPLINKp[x][y].h;

			tu[3] = MAPLINKp[x][y].w;
			tv[3] = MAPLINKp[x][y].v;
			tu[4] = MAPLINKp[x][y].w;
			tv[4] = MAPLINKp[x][y].h;
			tu[5] = MAPLINKp[x][y].u;
			tv[5] = MAPLINKp[x][y].h;

			tx = MAPLINKp[x][y].texture&3;

			if ( x<MAP_SIZE && y<MAP_SIZE ) {
				for(cnt=0;cnt<6;cnt++) {
					p.x = cntX + sw*dx[cntR];
					p.y = cntY + sh*dy[cntR];
					spec = GetMapHeight( (x+dx[cntR])&0xFF , (y+dy[cntR])&0xFF )>>(SHIFT_MAPHEIGHT-2);

					D3Dvt[tx][rcnt[tx]].sx		= p.x;
					D3Dvt[tx][rcnt[tx]].sy		= p.y;
					D3Dvt[tx][rcnt[tx]].sz		= 0;
					D3Dvt[tx][rcnt[tx]].rhw		= 1;	
					D3Dvt[tx][rcnt[tx]].tu		= tu[cnt];
					D3Dvt[tx][rcnt[tx]].tv		= tv[cnt];
					D3Dvt[tx][rcnt[tx]].color	= RGB_MAKE( 255,255,255 );
					D3Dvt[tx][rcnt[tx]].specular= RGB_MAKE( spec,spec,spec );
					rcnt[tx]++;
					cntR++;
				}
			}
			x++;
		}
		y++;
	}

	for(cnt=0;cnt<4;cnt++) {
	    lpD3DDevice->SetTexture( 0, hMapTexture[cnt] );
		lpD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,
									D3DFVF_TLVERTEX ,
									(LPVOID)D3Dvt[cnt],
									rcnt[cnt],
									NULL);
	}



    // Back Surface Áö¿ì±â
    DDBLTFX bltFx;
    ZeroMemory( &bltFx, sizeof(DDBLTFX) );
    bltFx.dwSize        = sizeof(DDBLTFX);
    bltFx.dwFillColor   = 0;

	if ( cellSize>8 ) {

	  y= my;
	  for( cntY=0; cntY<wHeight+sh; cntY+=sh ) {
		x=mx;
		for( cntX=0; cntX<wWidth+sw; cntX+=sw ) {
			if ( MapSelectBuff[ y*MAP_SIZE + x ] ) bltFx.dwFillColor   = 0x00FF;
			else bltFx.dwFillColor   = 0;

			rect.left = cntX-4;
			rect.right = cntX+4;
			rect.top = cntY;
			rect.bottom = cntY+1;
		    lpDDSBack->Blt( &rect, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &bltFx );

			rect.left = cntX;
			rect.right = cntX+1;
			rect.top = cntY-4;
			rect.bottom = cntY+4;
		    lpDDSBack->Blt( &rect, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &bltFx );
			x++;
		}
		y++;
	  }

	}

	return TRUE;

}

#define DLLEXPORT __declspec(dllexport)

extern "C" {
	DLLEXPORT int _stdcall smClearSelBuff();
	DLLEXPORT int _stdcall smDrawBoxArea( int x, int y, int w, int h );
	DLLEXPORT int _stdcall smDrawCircleArea( int x, int y, int w, int h );
	DLLEXPORT int _stdcall smDisplayShowMap( int x, int y, int z , int ax, int ay, int az );
	DLLEXPORT int _stdcall smDisplayEditMap( int cellSize , int mx , int my, int mw , int mh );
	DLLEXPORT int _stdcall updateFrame();
}

int _stdcall smClearSelBuff()
{
	int i;

	for( i=0; i<MAP_SIZE*MAP_SIZE ; i++ )
		MapSelectBuff[i]=0;

	return TRUE;
}


int _stdcall void updateFrame()
{
    RECT                rcRect;
    RECT                destRect;
    HRESULT             ddrval;
	POINT				pt;

    GetClientRect(hwnd,&destRect);

    pt.x=pt.y=0;
    ClientToScreen(hwnd,&pt);
    OffsetRect(&destRect,pt.x,pt.y);

	rcRect.left   = 0;
	rcRect.right  = wWidth;
	rcRect.top    = 0;
	rcRect.bottom = wHeight;


	while(1)
	{
		ddrval=lpDDSPrimary->Blt(&destRect,lpDDSBack,&rcRect,NULL,NULL);
		if(ddrval == DD_OK) break;
		if(ddrval == DDERR_SURFACELOST)
		{
	//		ddrval = restoreAll();
			if(ddrval != DD_OK)	return TRUE;
		}
		if(ddrval != DDERR_WASSTILLDRAWING) break;

	}

	return TRUE;
} 


int _stdcall smDrawBoxArea( int x, int y, int w, int h )
{
	HDC hdc;
	HBRUSH aBrush = CreateSolidBrush( RGB( 64,128,255 ) );
	RECT rect;

	rect.left   = x;
	rect.top    = y;
	rect.right  = x+w;
	rect.bottom = y+h;

	lpDDSBack->GetDC( &hdc );
	FrameRect( hdc , &rect ,  aBrush );
	lpDDSBack->ReleaseDC( hdc );

	int cntX,cntY;

	ZeroMemory( &MapSelectBuff , sizeof( MapSelectBuff ) );

	for( cntY=MapsY+(y/CellSize); cntY<MapsY+((y+h)/CellSize) ; cntY++ )
		for( cntX=MapsX+(x/CellSize); cntX<MapsX+((x+w)/CellSize) ; cntX++ ) {
			MapSelectBuff[ ((cntY+1)*MAP_SIZE)+cntX+1 ] = 1;
		}

	return TRUE;

}

int _stdcall smDrawCircleArea( int x, int y, int w, int h )
{
	HDC hdc;
	HBRUSH aBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HPEN aPen = CreatePen( PS_SOLID , 1, RGB( 64,128,255 ) );

	lpDDSBack->GetDC( &hdc );

	SelectObject( hdc , aPen );
	SelectObject( hdc , aBrush );
	Ellipse( hdc , x-w , y-h, x+w , y+h );

	lpDDSBack->ReleaseDC( hdc );
	DeleteObject( aPen );
	DeleteObject( aBrush );

	int cntX,cntY;
	int acnt;
	int dx;
	int sx,ex;
	int sy,ey;
	int sw,sh;

	sw = w /CellSize;
	sh = h /CellSize;

	ZeroMemory( &MapSelectBuff , sizeof( MapSelectBuff ) );

	if (h==0 || w==0 ) return TRUE;
	dx = (1024<<16) / (h*2);

	acnt = (dx*(CellSize>>1));
	for( cntY=y-h; cntY<y+h; cntY+=CellSize ) {

		sy = MapsY+(cntY/CellSize);

		ex = ( GetSin[(acnt>>16)] * w )>>16;
		ex = abs(ex);
		sx = -ex;
		sx =MapsX+((x+sx-(CellSize>>1))/CellSize);
		ex =MapsX+((x+ex+(CellSize>>1))/CellSize);
		acnt+=dx*CellSize;
		for( cntX=sx; cntX<ex ; cntX++ ) {
			MapSelectBuff[ ((sy+1)*MAP_SIZE)+cntX+1 ] = 1;
		}

	}

	return TRUE;

}



int _stdcall smDisplayShowMap( int x, int y, int z , int ax, int ay, int az )
{
	int mapY;

	mapY = smGetMapHeight( x , z )+96;
	if ( y<mapY ) y = mapY;

	BeginRender();
	lpD3DDevice->SetRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
	DrawBG( x, y, z, ax, ay, az );
	DisplayMap( x,y,z, ax, ay, az );
	EndRender();

	Flip();

	return TRUE;

}

int _stdcall smDisplayEditMap( int cellSize , int mx , int my, int mw , int mh )
{

//    lpD3DDevice->SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_NONE );

	BeginRender();

	DisplayEditMap( cellSize , mx , my, mw , mh );

	EndRender();




//	smDrawBoxArea( 128,128,100,50 );
//int smDrawCircleArea( int x, int y, int w, int h )

/*
	lpDDSBack->GetDC( &hSrcDC );

//	BitBlt( hdc , 0,0, wWidth, wHeight , hSrcDC, 0,0, SRCCOPY );
	BitBlt( hdc , 0,0, 200, 200 , hSrcDC, 0,0, SRCCOPY );

	lpDDSBack->ReleaseDC( hSrcDC );
*/
//	Flip();
//	updateFrame();

	return TRUE;
}
