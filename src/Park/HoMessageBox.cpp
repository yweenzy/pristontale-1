#include "sinbaram\\SinLinkHeader.h"
#include "..\\HoBaram\\HoLinkHeader.h"

HoMessage	ChatMessage;
BOOL    HoMessage::MessageFrameSelectFlag = TRUE;

//Data Resource를 읽어온다.
HoMessage::HoMessage( )
{
}

HoMessage::~HoMessage( )
{
}


int HoMessage::Init( )
{
	TextStartPosY = 0;

	BoxImage1[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox0.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage1[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage1[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage1[ 3 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox3.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage1[ 4 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox4.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage1[ 5 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox5.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage1[ 6 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox6.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage1[ 7 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox7.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage1[ 8 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox8.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );

	BoxImage2[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox00.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage2[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox22.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage2[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox66.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage2[ 3 ] = CreateTextureMaterial( "StartImage\\MessageBox\\NormalBox\\MessageBox88.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );

	BoxImage3[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBox000.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage3[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBox001.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage3[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBox002.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage3[ 3 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBox003.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage3[ 4 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBox004.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage3[ 5 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBox005.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage3[ 6 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBox006.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage3[ 7 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBox007.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage3[ 8 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBox008.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage3[ 9 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBox009.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );

	//선택 박스
	BoxImage4[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBoxa000.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage4[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBoxa001.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage4[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBoxa002.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage4[ 3 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBoxa003.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage4[ 5 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBoxa005.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage4[ 6 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBoxa006.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage4[ 7 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBoxa007.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage4[ 8 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBoxa008.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BoxImage4[ 9 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\MessageBoxa009.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );

	ClanBoxImage[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\clanNameBox01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ClanBoxImage[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\clanNameBox02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ClanBoxImage[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\clanNameBox03.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );

	ClanBoxImage2[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\BoxTopLeft.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ClanBoxImage2[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\BoxTopCenter.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ClanBoxImage2[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\BoxTopRight.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ClanBoxImage2[ 3 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\BoxLeft.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ClanBoxImage2[ 4 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\BoxCenter.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ClanBoxImage2[ 5 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\BoxRight.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ClanBoxImage2[ 6 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\BoxBottomLeft.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ClanBoxImage2[ 7 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\BoxBottomCenter.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ClanBoxImage2[ 8 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ClanBox\\BoxBottomRight.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );


	ShopBoxByeImage1[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBox000.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage1[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBox001.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage1[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBox002.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage1[ 3 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBox003.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage1[ 5 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBox005.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage1[ 6 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBox006.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage1[ 7 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBox007.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage1[ 8 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBox008.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage1[ 9 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBox009.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );

	ShopBoxByeImage2[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBoxA000.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage2[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBoxA001.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage2[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBoxA002.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage2[ 3 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBoxA003.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage2[ 5 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBoxA005.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage2[ 6 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBoxA006.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage2[ 7 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBoxA007.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage2[ 8 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBoxA008.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxByeImage2[ 9 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\BMessageBoxA009.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );



	ShopBoxSellImage1[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBox000.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage1[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBox001.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage1[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBox002.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage1[ 3 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBox003.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage1[ 5 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBox005.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage1[ 6 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBox006.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage1[ 7 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBox007.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage1[ 8 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBox008.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage1[ 9 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBox009.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );

	ShopBoxSellImage2[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBoxA000.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage2[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBoxA001.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage2[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBoxA002.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage2[ 3 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBoxA003.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage2[ 5 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBoxA005.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage2[ 6 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBoxA006.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage2[ 7 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBoxA007.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage2[ 8 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBoxA008.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	ShopBoxSellImage2[ 9 ] = CreateTextureMaterial( "StartImage\\MessageBox\\ChatBox\\GMessageBoxA009.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );


	BellaIconImage[ 0 ] = CreateTextureMaterial( "StartImage\\MessageBox\\BellaBox\\Bella_01.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BellaIconImage[ 1 ] = CreateTextureMaterial( "StartImage\\MessageBox\\BellaBox\\Bella_02.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	BellaIconImage[ 2 ] = CreateTextureMaterial( "StartImage\\MessageBox\\BellaBox\\Bella_03.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA );

	TextDC = NULL;
	OldFont = NULL;

	return TRUE;
}

void HoMessage::DrawMessageBox( int x, int y, char *message, int boxAttrib, int Color )
{
	int messageSize = strlen( message );
	int messageWidth = messageSize / 2;
	if ( messageWidth < 16 )
		messageWidth = 16;

	int messageHeight = 4;

	TextStartPosY = y + 6;
	if ( messageWidth == 0 )
		return;

	if ( x <= 0 )
		x = 0;
	if ( y <= 0 )
		y = 0;

	if (x + 16 * 2 + messageWidth * 12 >= renderDevice.GetScreenWidth())
		x = renderDevice.GetScreenWidth() - messageWidth * 12 - 16 * 2;

	if (y + 16 * 2 + messageHeight * 12 >= renderDevice.GetScreenHeight())
		y = renderDevice.GetScreenHeight() - messageHeight * 12 - 16 * 2;

	renderDevice.BeginScene();

	//귀퉁이 4개를 그린다..
	if ( boxAttrib == BOX_ONE )
	{
		dsDrawTexImage( BoxImage1[ 0 ], x, y, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage1[ 2 ], x + 16 + messageWidth * 12, y, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage1[ 6 ], x, y + 16 + messageHeight * 12, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage1[ 8 ], x + 16 + messageWidth * 12, y + 16 + messageHeight * 12, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
	}
	else if ( boxAttrib == BOX_TWO )
	{
		dsDrawTexImage( BoxImage2[ 0 ], x, y, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage2[ 1 ], x + 16 + messageWidth * 12, y, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage2[ 2 ], x, y + 16 + messageHeight * 12, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage2[ 3 ], x + 16 + messageWidth * 12, y + 16 + messageHeight * 12, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
	}

	int m, n;
	if ( boxAttrib == BOX_ONE || boxAttrib == BOX_TWO )
	{
		//가로 위, 가로 아래, 가운데...
		for ( m = 0; m < messageWidth; m++ )
		{
			dsDrawTexImage( BoxImage1[ 1 ], x + 16 + 12 * m, y, 12, 16, 16, 16, 0, 0, 12, 16, 255 );
			dsDrawTexImage( BoxImage1[ 7 ], x + 16 + 12 * m, y + 16 + ( 12 * messageHeight ), 12, 16, 16, 16, 0, 0, 12, 16, 255 );
		}

		//세로 왼쪽, 오른쪽
		for ( m = 0; m < messageHeight; m++ )
		{
			dsDrawTexImage( BoxImage1[ 3 ], x, y + 16 + ( 12 * m ), 16, 12, 16, 16, 0, 0, 16, 12, 255 );
			dsDrawTexImage( BoxImage1[ 5 ], x + 16 + 12 * messageWidth, y + 16 + ( 12 * m ), 16, 12, 16, 16, 0, 0, 16, 12, 255 );
		}

		//중간 뚤린곳...
		for ( m = 0; m < messageWidth; m++ )
		{
			for ( n = 0; n < messageHeight; n++ )
				dsDrawTexImage( BoxImage1[ 4 ], x + 16 + 12 * m, y + 16 + 12 * n, 12, 12, 32, 32, 0, 0, 12, 12, 255 );
		}
	}

	renderDevice.EndScene();

	HDC hdc;
	HFONT oldFont;
	renderDevice.lpDDSBack->GetDC(&hdc);

	if ( hFont != NULL )
		oldFont = ( HFONT )SelectObject( hdc, hFont );

	SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, Color );

	char buffer[ 1024 ];
	memset( buffer, 0, sizeof( buffer ) );
	memcpy( buffer, message, sizeof( message ) );

	int	textStartPosX;

	Width = messageWidth * 12 + 16 * 2;

	if ( messageSize <= 16 )
		textStartPosX = Width / 2 - ( messageSize / 4 ) * 12 - 6;
	else
		textStartPosX = Width / 2 - ( messageSize / 4 ) * 12;

	dsTextLineOut( hdc, x + textStartPosX, TextStartPosY + 16, message, lstrlen( message ) );

	if ( oldFont )
		SelectObject( hdc, oldFont );

	renderDevice.lpDDSBack->ReleaseDC(hdc);

	PosX = x;
	PosY = y;

}


#include "Language\\language.h"


int HoDrawLinearTexImage( int Mat, float x, float y, float w, float h, float texX, float texY, float texW, float texH, DWORD color )
{
	int specular = 0;
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;

	clipLeft = 0;
	clipTop = 0;
	clipRight = renderDevice.GetScreenWidth();
	clipBottom = renderDevice.GetScreenHeight();

	//Clipping 영역을 완전히 벗어나면...
	if ( ( x >= clipRight ) || ( y >= clipBottom ) || ( ( x + texW ) <= clipLeft ) || ( ( y + texH ) <= clipTop ) )
		return FALSE;

	//원래 사각 영역의 크기는 0, 0, 127, 127 이지만 이렇게 찍을 경우. 한 픽셀이 빠져서 0, 0, 128, 128로 보정한다.

	//화면에 찍히는 영역..
	float x1 = x - 0.5f;
	float y1 = y - 0.5f;
	float x2 = x1 + w;
	float y2 = y1 + h;

	float texSizeWidth = ( float )smMaterialGroup->smMaterial[ Mat ].smTexture[ 0 ]->Width;
	float texSizeHeight = ( float )smMaterialGroup->smMaterial[ Mat ].smTexture[ 0 ]->Height;

	//텍스쳐 u,v 좌표..
	float u1 = ( ( float )texX / ( float )texSizeWidth );
	float v1 = ( ( float )texY / ( float )texSizeHeight );

	float u2 = ( ( float )texX + texW ) / ( float )texSizeWidth;
	float v2 = ( ( float )texY + texH ) / ( float )texSizeHeight;

	//x1, y1, x2, y2 는 클립된 사각영역이다..
	DRZD3DTLVERTEX tlVertex[4];
	int cnt;

	int r, g, b;
	r = color & 0xff;
	g = ( color & 0xff00 ) >> 8;
	b = ( color & 0xff0000 ) >> 16;


	for ( cnt = 0; cnt < 4; cnt++ )
	{
		tlVertex[ cnt ].rhw = 1.f;
		tlVertex[ cnt ].color = RGBA_MAKE( r, g, b, 255 );
		tlVertex[ cnt ].specular = RGBA_MAKE( specular, specular, specular, 0 );
		tlVertex[ cnt ].sz = 0;
	}

	DDSURFACEDESC2	ddTemp;
	memset( &ddTemp, 0, sizeof( DDSURFACEDESC2 ) );
	ddTemp.dwSize = sizeof( ddTemp );



	tlVertex[ 0 ].sx = x1;
	tlVertex[ 0 ].sy = y1;
	tlVertex[ 0 ].tu = u1;
	tlVertex[ 0 ].tv = v1;

	tlVertex[ 1 ].sx = x1;
	tlVertex[ 1 ].sy = y2;
	tlVertex[ 1 ].tu = u1;
	tlVertex[ 1 ].tv = v2;

	tlVertex[ 2 ].sx = x2;
	tlVertex[ 2 ].sy = y1;
	tlVertex[ 2 ].tu = u2;
	tlVertex[ 2 ].tv = v1;

	tlVertex[ 3 ].sx = x2;
	tlVertex[ 3 ].sy = y2;
	tlVertex[ 3 ].tu = u2;
	tlVertex[ 3 ].tv = v2;

	//뒤집힌면 그리기
	//lpD3DDevice->SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_NONE );
	if (renderDevice.IsDevice() != NULL)
	{
		// Turn on Z-buffering
		renderDevice.SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		//renderDevice.SetRenderState( D3DRENDERSTATE_ZFUNC,   D3DCMP_LESSEQUAL );
		//renderDevice.SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_USEW );//TRUE );


		// null out the texture handle
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);

		// turn on dithering
		renderDevice.SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);

		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE ); 

		// D3DFILTER_LINEAR
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );

		renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE );

		renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

		smRender.AlphaTestDepth = 60;

		renderDevice.SetTextureStageState(0, D3DTSS_MINFILTER, D3DFILTER_LINEAR);
		renderDevice.SetTextureStageState(0, D3DTSS_MAGFILTER, D3DFILTER_LINEAR);

		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DTFN_POINT );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DTFN_POINT );


		if ( smMaterial[ Mat ].smTexture[ 0 ] != NULL )
		{
			if ( smMaterial[ Mat ].smTexture[ 0 ]->lpD3DTexture != NULL )
			{
				if (FAILED(renderDevice.SetTexture(0, smMaterial[Mat].smTexture[0]->lpD3DTexture)))
				{
					OutputDebugString( "SetTexture Error" );
					return FALSE;
				}


				if (FAILED(renderDevice.DrawPrimitive(D3DPT_TRIANGLESTRIP, D3DFVF_TLVERTEX, tlVertex, 4, NULL )))
				{
					OutputDebugString( "DrawPrimitive Error" );
					return FALSE;
				}
			}
		}

		renderDevice.SetTextureStageState(cnt, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		renderDevice.SetTextureStageState(cnt, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
		//D3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
	}
	//lpD3DDevice->SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_CW );
	return TRUE;

}

int HoDrawTexImage( int Mat, float x, float y, float w, float h, float texX, float texY, float texW, float texH, int Transp )
{
	int specular = 0;
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;

	clipLeft = 0;
	clipTop = 0;
	clipRight = renderDevice.GetScreenWidth();
	clipBottom = renderDevice.GetScreenHeight();

	//Clipping 영역을 완전히 벗어나면...
	if ( ( x >= clipRight ) || ( y >= clipBottom ) || ( ( x + texW ) <= clipLeft ) || ( ( y + texH ) <= clipTop ) )
		return FALSE;

	//원래 사각 영역의 크기는 0, 0, 127, 127 이지만 이렇게 찍을 경우. 한 픽셀이 빠져서 0, 0, 128, 128로 보정한다.

	//화면에 찍히는 영역..
	float x1 = x - 0.5f;
	float y1 = y - 0.5f;
	float x2 = x1 + w;
	float y2 = y1 + h;

	float texSizeWidth = ( float )smMaterialGroup->smMaterial[ Mat ].smTexture[ 0 ]->Width;
	float texSizeHeight = ( float )smMaterialGroup->smMaterial[ Mat ].smTexture[ 0 ]->Height;

	//텍스쳐 u,v 좌표..
	float u1 = ( ( float )texX / ( float )texSizeWidth );
	float v1 = ( ( float )texY / ( float )texSizeHeight );

	float u2 = ( ( float )texX + texW ) / ( float )texSizeWidth;
	float v2 = ( ( float )texY + texH ) / ( float )texSizeHeight;

	//x1, y1, x2, y2 는 클립된 사각영역이다..
	DRZD3DTLVERTEX tlVertex[4];
	int cnt;

	for ( cnt = 0; cnt < 4; cnt++ )
	{
		tlVertex[ cnt ].rhw = 1.f;
		tlVertex[ cnt ].color = RGBA_MAKE( 255, 255, 255, Transp );
		tlVertex[ cnt ].specular = RGBA_MAKE( specular, specular, specular, 0 );
		tlVertex[ cnt ].sz = 0;
	}

	DDSURFACEDESC2	ddTemp;
	memset( &ddTemp, 0, sizeof( DDSURFACEDESC2 ) );
	ddTemp.dwSize = sizeof( ddTemp );



	tlVertex[ 0 ].sx = x1;
	tlVertex[ 0 ].sy = y1;
	tlVertex[ 0 ].tu = u1;
	tlVertex[ 0 ].tv = v1;

	tlVertex[ 1 ].sx = x1;
	tlVertex[ 1 ].sy = y2;
	tlVertex[ 1 ].tu = u1;
	tlVertex[ 1 ].tv = v2;

	tlVertex[ 2 ].sx = x2;
	tlVertex[ 2 ].sy = y1;
	tlVertex[ 2 ].tu = u2;
	tlVertex[ 2 ].tv = v1;

	tlVertex[ 3 ].sx = x2;
	tlVertex[ 3 ].sy = y2;
	tlVertex[ 3 ].tu = u2;
	tlVertex[ 3 ].tv = v2;

	//뒤집힌면 그리기
	//lpD3DDevice->SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_NONE );
	if (renderDevice.IsDevice() != NULL)
	{
		// Turn on Z-buffering
		renderDevice.SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		//renderDevice.SetRenderState( D3DRENDERSTATE_ZFUNC,   D3DCMP_LESSEQUAL );
		//renderDevice.SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_USEW );//TRUE );


		// null out the texture handle
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);

		// turn on dithering
		//renderDevice.D3DDevice->SetRenderState( D3DRENDERSTATE_DITHERENABLE, TRUE );

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE ); 

		// D3DFILTER_LINEAR
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );

		renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

		renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

		smRender.AlphaTestDepth = 60;

		renderDevice.SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
		renderDevice.SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);

		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DTFN_POINT );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DTFN_POINT );


		if ( smMaterial[ Mat ].smTexture[ 0 ] != NULL )
		{
			if ( smMaterial[ Mat ].smTexture[ 0 ]->lpD3DTexture != NULL )
			{
				if (FAILED(renderDevice.SetTexture(0, smMaterial[Mat].smTexture[0]->lpD3DTexture)))
				{
					OutputDebugString( "SetTexture Error" );
					return FALSE;
				}


				if (FAILED(renderDevice.DrawPrimitive(D3DPT_TRIANGLESTRIP,
					D3DFVF_TLVERTEX,
					tlVertex,
					4,
					NULL ) ) )
				{
					OutputDebugString( "DrawPrimitive Error" );
					return FALSE;
				}
			}
		}

		renderDevice.SetTextureStageState(cnt, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		renderDevice.SetTextureStageState(cnt, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
		//D3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
	}
	//lpD3DDevice->SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_CW );
	return TRUE;
}

int HoDrawTexImage( int Mat, int x, int y, int w, int h, int texX, int texY, int texW, int texH, int Transp )
{
	int specular = 0;
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;

	clipLeft = 0;
	clipTop = 0;
	clipRight = renderDevice.GetScreenWidth();
	clipBottom = renderDevice.GetScreenHeight();

	//Clipping 영역을 완전히 벗어나면...
	if ( ( x >= clipRight ) || ( y >= clipBottom ) || ( ( x + texW ) <= clipLeft ) || ( ( y + texH ) <= clipTop ) )
		return FALSE;

	//원래 사각 영역의 크기는 0, 0, 127, 127 이지만 이렇게 찍을 경우. 한 픽셀이 빠져서 0, 0, 128, 128로 보정한다.

	//화면에 찍히는 영역..
	float x1 = ( float )x - 0.5f;
	float y1 = ( float )y - 0.5f;
	float x2 = x1 + ( float )w;
	float y2 = y1 + ( float )h;

	float texSizeWidth = ( float )smMaterialGroup->smMaterial[ Mat ].smTexture[ 0 ]->Width;
	float texSizeHeight = ( float )smMaterialGroup->smMaterial[ Mat ].smTexture[ 0 ]->Height;

	//텍스쳐 u,v 좌표..
	float u1 = ( ( float )texX / ( float )texSizeWidth );
	float v1 = ( ( float )texY / ( float )texSizeHeight );

	float u2 = ( ( float )texX + texW ) / ( float )texSizeWidth;
	float v2 = ( ( float )texY + texH ) / ( float )texSizeHeight;

	//x1, y1, x2, y2 는 클립된 사각영역이다..
	DRZD3DTLVERTEX tlVertex[4];
	int cnt;

	for ( cnt = 0; cnt < 4; cnt++ )
	{
		tlVertex[ cnt ].rhw = 1.f;
		tlVertex[ cnt ].color = RGBA_MAKE( 255, 255, 255, Transp );
		tlVertex[ cnt ].specular = RGBA_MAKE( specular, specular, specular, 0 );
		tlVertex[ cnt ].sz = 0;
	}

	DDSURFACEDESC2	ddTemp;
	memset( &ddTemp, 0, sizeof( DDSURFACEDESC2 ) );
	ddTemp.dwSize = sizeof( ddTemp );



	tlVertex[ 0 ].sx = x1;
	tlVertex[ 0 ].sy = y1;
	tlVertex[ 0 ].tu = u1;
	tlVertex[ 0 ].tv = v1;

	tlVertex[ 1 ].sx = x1;
	tlVertex[ 1 ].sy = y2;
	tlVertex[ 1 ].tu = u1;
	tlVertex[ 1 ].tv = v2;

	tlVertex[ 2 ].sx = x2;
	tlVertex[ 2 ].sy = y1;
	tlVertex[ 2 ].tu = u2;
	tlVertex[ 2 ].tv = v1;

	tlVertex[ 3 ].sx = x2;
	tlVertex[ 3 ].sy = y2;
	tlVertex[ 3 ].tu = u2;
	tlVertex[ 3 ].tv = v2;

	//뒤집힌면 그리기
	//lpD3DDevice->SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_NONE );
	if (renderDevice.IsDevice() != NULL)
	{
		// Turn on Z-buffering
		renderDevice.SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		//renderDevice.SetRenderState( D3DRENDERSTATE_ZFUNC,   D3DCMP_LESSEQUAL );
		//renderDevice.SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_USEW );//TRUE );


		// null out the texture handle
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);

		// turn on dithering
		//renderDevice.D3DDevice->SetRenderState( D3DRENDERSTATE_DITHERENABLE, TRUE );

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE ); 

		// D3DFILTER_LINEAR
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );

		renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

		renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

		smRender.AlphaTestDepth = 60;

		renderDevice.SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
		renderDevice.SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);

		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DTFN_POINT );
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DTFN_POINT );


		if ( smMaterial[ Mat ].smTexture[ 0 ] != NULL )
		{
			if ( smMaterial[ Mat ].smTexture[ 0 ]->lpD3DTexture != NULL )
			{
				if (FAILED(renderDevice.SetTexture(0, smMaterial[Mat].smTexture[0]->lpD3DTexture)))
				{
					OutputDebugString( "SetTexture Error" );
					return FALSE;
				}


				if (FAILED(renderDevice.DrawPrimitive(D3DPT_TRIANGLESTRIP,
					D3DFVF_TLVERTEX,
					tlVertex,
					4,
					NULL ) ) )
				{
					OutputDebugString( "DrawPrimitive Error" );
					return FALSE;
				}
			}
		}

		renderDevice.SetTextureStageState(cnt, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		renderDevice.SetTextureStageState(cnt, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
		//D3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );
		//lpD3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
	}
	//lpD3DDevice->SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_CW );

	return TRUE;
}

//그림 출력
//x,y, w, h 영역에 있는 텍스쳐 이미지를 그대로 찍는다.
int HoDrawTexImage( int Mat, int x, int y, int texX, int texY, int texW, int texH, int Transp )
{
	int specular = 0;
	int clipLeft;
	int clipTop;
	int clipRight;
	int clipBottom;

	clipLeft = 0;
	clipTop = 0;
	clipRight = renderDevice.GetScreenWidth();
	clipBottom = renderDevice.GetScreenHeight();

	//Clipping 영역을 완전히 벗어나면...
	if ( ( x >= clipRight ) || ( y >= clipBottom ) || ( ( x + texW ) <= clipLeft ) || ( ( y + texH ) <= clipTop ) )
		return FALSE;

	//원래 사각 영역의 크기는 0, 0, 127, 127 이지만 이렇게 찍을 경우. 한 픽셀이 빠져서 0, 0, 128, 128로 보정한다.
	//화면에 찍히는 영역..
	float x1 = ( float )x - 0.5f;
	float y1 = ( float )y - 0.5f;
	float x2 = x1 + ( float )texW;
	float y2 = y1 + ( float )texH;

	float texSizeWidth = ( float )smMaterialGroup->smMaterial[ Mat ].smTexture[ 0 ]->Width;
	float texSizeHeight = ( float )smMaterialGroup->smMaterial[ Mat ].smTexture[ 0 ]->Height;

	//텍스쳐 u,v 좌표..
	float u1 = ( ( float )texX / ( float )texSizeWidth );
	float v1 = ( ( float )texY / ( float )texSizeHeight );

	float u2 = ( ( float )texX + texW ) / ( float )texSizeWidth;
	float v2 = ( ( float )texY + texH ) / ( float )texSizeHeight;

	/*
	if(u1 < 0 || v1 < 0 || u2 > 1 || v2 > 1)
	{
	OutputDebugString("kslfdlksfdkl");

	}

	if( (texX+texW) > texSizeWidth ||
	(texY+texH) > texSizeHeight)
	{
	OutputDebugString("dkfj");
	}

	float test1 = (float)texW/(float)texH;
	float test2 = (u2-u1)/(v2-v1);
	if( test1 != test2)
	{
	OutputDebugString("kslfdlksfdkl");
	}
	*/

	//x1, y1, x2, y2 는 클립된 사각영역이다..
	DRZD3DTLVERTEX tlVertex[4];
	int cnt;

	for ( cnt = 0; cnt < 4; cnt++ )
	{
		tlVertex[ cnt ].rhw = 1.f;
		tlVertex[ cnt ].color = RGBA_MAKE( 255, 255, 255, Transp );
		tlVertex[ cnt ].specular = RGBA_MAKE( specular, specular, specular, 0 );
		tlVertex[ cnt ].sz = 0;
	}

	DDSURFACEDESC2	ddTemp;
	memset( &ddTemp, 0, sizeof( DDSURFACEDESC2 ) );
	ddTemp.dwSize = sizeof( ddTemp );



	tlVertex[ 0 ].sx = x1;
	tlVertex[ 0 ].sy = y1;
	tlVertex[ 0 ].tu = u1;
	tlVertex[ 0 ].tv = v1;

	tlVertex[ 1 ].sx = x1;
	tlVertex[ 1 ].sy = y2;
	tlVertex[ 1 ].tu = u1;
	tlVertex[ 1 ].tv = v2;

	tlVertex[ 2 ].sx = x2;
	tlVertex[ 2 ].sy = y1;
	tlVertex[ 2 ].tu = u2;
	tlVertex[ 2 ].tv = v1;

	tlVertex[ 3 ].sx = x2;
	tlVertex[ 3 ].sy = y2;
	tlVertex[ 3 ].tu = u2;
	tlVertex[ 3 ].tv = v2;

	//뒤집힌면 그리기
	//renderDevice.SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_NONE );
	if (renderDevice.IsDevice() != NULL)
	{
		// Turn on Z-buffering
		renderDevice.SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		//renderDevice.SetRenderState( D3DRENDERSTATE_ZFUNC,   D3DCMP_LESSEQUAL );
		//renderDevice.SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_USEW );//TRUE );


		// null out the texture handle
		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);

		// turn on dithering
		//renderDevice.D3DDevice->SetRenderState( D3DRENDERSTATE_DITHERENABLE, TRUE );

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE ); 

		// D3DFILTER_LINEAR
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );

		renderDevice.SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		renderDevice.SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

		renderDevice.SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		renderDevice.SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
		renderDevice.SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

		smRender.AlphaTestDepth = 60;

		renderDevice.SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_POINT);
		renderDevice.SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_POINT);

		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DTFN_POINT );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DTFN_POINT );


		if ( smMaterial[ Mat ].smTexture[ 0 ] != NULL )
		{
			if ( smMaterial[ Mat ].smTexture[ 0 ]->lpD3DTexture != NULL )
			{
				if (FAILED(renderDevice.SetTexture(0, smMaterial[Mat].smTexture[0]->lpD3DTexture)))
				{
					OutputDebugString( "SetTexture Error" );
					return FALSE;
				}


				if (FAILED(renderDevice.DrawPrimitive(D3DPT_TRIANGLESTRIP,
					D3DFVF_TLVERTEX,
					tlVertex,
					4,
					NULL ) ) )
				{
					OutputDebugString( "DrawPrimitive Error" );
					return FALSE;
				}
			}
		}

		renderDevice.SetTextureStageState(cnt, D3DTSS_MINFILTER, D3DTFN_LINEAR);
		renderDevice.SetTextureStageState(cnt, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
		//renderDevice.D3DDevice->SetRenderState( D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );
		//renderDevice.SetRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
	}
	//renderDevice.SetRenderState( D3DRENDERSTATE_CULLMODE , D3DCULL_CW );

	return TRUE;
}

//넘어오는 좌표.. 창에서 제일 왼쪽, 오른쪽 위..
void HoMessage::DrawClanName( int x, int y, char *clanName )
{
	x = x + 3;
	y = y - 12;

	if ( clanName == NULL )
		return;
	int length = strlen( clanName );
	if ( length < 1 )
		return;

	//클랜 이름 껍떼기..
	renderDevice.BeginScene();
	HoDrawTexImage( ClanBoxImage[ 0 ], x, y, 16, 14, 0, 0, 16, 14, 255 );
	for ( int index = 0; index <= length; index++ )
	{
		HoDrawTexImage( ClanBoxImage[ 1 ], float( x + 16 ) + ( float )index*5.5f, ( float )y, 5.5f, 14.f, 0.f, 0.f, 5.5f, 14.f, 255 );
	}

	HoDrawTexImage( ClanBoxImage[ 2 ], float( x + 16 ) + ( float )( length + 1 )*5.5f, ( float )y, 16.f, 14.f, 0.f, 0.f, 16.f, 14.f, 255 );
	renderDevice.EndScene();

	HDC hdc;
	renderDevice.lpDDSBack->GetDC(&hdc);
	if ( sinFont != NULL )
		SelectObject( hdc, sinFont );

	SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, RGB( 0, 0, 0 ) );
	dsTextLineOut( hdc, x + 15, y + 3, clanName, lstrlen( clanName ) );

	SetTextColor( hdc, RGB( 230, 255, 160 ) );
	dsTextLineOut( hdc, x + 15, y + 2, clanName, lstrlen( clanName ) );

	renderDevice.lpDDSBack->ReleaseDC(hdc);
}

void HoMessage::DrawClanMark( DIRECTDRAWSURFACE clanMark, char *clanName, int x, int y, BOOL frameFlag )
{
	if ( clanMark == NULL )
		return;

	if ( frameFlag )
	{
		renderDevice.BeginScene();
		HoDrawTexImage( BoxImage3[ 0 ], x, y, 0, 0, 8, 8, 255 );
		HoDrawTexImage( BoxImage3[ 2 ], x + 11 + 6, y, 0, 0, 8, 8, 255 );
		HoDrawTexImage( BoxImage3[ 6 ], x, y + 5 + 11, 0, 0, 8, 8, 255 );
		HoDrawTexImage( BoxImage3[ 8 ], x + 11 + 6, y + 5 + 11, 0, 0, 8, 8, 255 );

		//세로..
		HoDrawTexImage( BoxImage3[ 3 ], x, y + 8, 0, 0, 8, 9, 255 );
		HoDrawTexImage( BoxImage3[ 5 ], x + 11 + 6, y + 8, 0, 0, 8, 9, 255 );

		//가로.
		HoDrawTexImage( BoxImage3[ 1 ], x + 8, y, 0, 0, 9, 8, 255 );
		HoDrawTexImage( BoxImage3[ 7 ], x + 8, y + 8 + 8, 0, 0, 9, 8, 255 );
		renderDevice.EndScene();
	}

	//RECT destRect;
	RECT surRect;
	surRect.left = 0;
	surRect.top = 0;
	surRect.right = 16;
	surRect.bottom = 16;

	//renderDevice.lpDDSBack->BltFast(x + 4, y + 4, clanMark, &surRect, DDBLTFAST_WAIT);
	renderDevice.BltFast(renderDevice.lpDDSBack, x + 4, y + 4, clanMark, &surRect, DDBLTFAST_WAIT);

	if ( clanName != NULL )
		DrawClanName( x, y, clanName ); //클랜 백그라운드가 세로가 32이기 땜시로..
}

void HoMessage::DrawTwoLineMessage( int x, int y, char *message1, char *message2, DWORD color1, DWORD color2, DIRECTDRAWSURFACE clanMark, BOOL selected, int bellaMarkIndex )
{

	char MessageOne[ 64 ];
	char MessageTwo[ 64 ];

	if ( message1 != NULL )
		strcpy( MessageOne, message1 );

	if ( message2 != NULL )
		strcpy( MessageTwo, message2 );

	int messageWidth = 0;
	int messageHeight = 2;

	int messageTempLen1 = strlen( MessageOne );
	int messageTempLen2 = strlen( MessageTwo );

	int messageLen = messageTempLen2;
	if ( messageTempLen1 > messageTempLen2 )
		messageLen = messageTempLen1;

	if ( clanMark != NULL )
	{
		if ( messageLen < messageTempLen1 + 3 )
			messageLen += 3;
	}

	int lineSize = messageLen;
	messageWidth = lineSize;
	x -= messageWidth / 2 * 6 + 18 / 2;
	y -= messageHeight * 14 + 8 * 2 + 8;

	DrawCharacterMessageFrame( x, y, messageWidth, messageHeight, false, selected );
	if ( bellaMarkIndex != -1 )
		DrawBellaIcon( x + 3 * messageWidth - 6, y - 30, bellaMarkIndex );

	HDC hdc;
	renderDevice.lpDDSBack->GetDC(&hdc);
	if ( hFont != NULL )
		SelectObject( hdc, hFont );
	SetBkMode( hdc, TRANSPARENT );

	if ( color1 == 0 )
		SetTextColor( hdc, RGB( 255, 255, 255 ) );
	else
		SetTextColor( hdc, color1 );

	if ( messageTempLen1 > 1 )
	{
		if ( clanMark == NULL )
			dsTextLineOut( hdc, x + 9 + messageWidth * 6 / 2 - messageTempLen1 * 6 / 2, y + 5 + 2, MessageOne, messageTempLen1 );
		else
			dsTextLineOut( hdc, x + 9 + 6 * 3, y + 5 + 2, MessageOne, messageTempLen1 );
	}

	if ( color2 == 0 )
		SetTextColor( hdc, RGB( 255, 255, 255 ) );
	else
		SetTextColor( hdc, color2 );

	if ( messageTempLen2 > 0 )
		dsTextLineOut( hdc, x + 9 + messageWidth * 6 / 2 - messageTempLen2 * 6 / 2, y + 5 + 2 + 16, MessageTwo, messageTempLen2 );

	renderDevice.lpDDSBack->ReleaseDC(hdc);


	if ( clanMark != NULL )
	{
		if ( MessageFrameSelectFlag )
			DrawClanMark( clanMark, NULL, x + 3, y );
		else
			DrawClanMark( clanMark, NULL, x + 7, y + 1 );
	}
}

void HoMessage::DrawBellaIcon( int x, int y, int bellaIndex )
{
	if ( bellaIndex == 1 ||
		 bellaIndex == 2 ||
		 bellaIndex == 3 )
	{
		renderDevice.BeginScene();

		if ( bellaIndex == 1 )
			HoDrawTexImage( BellaIconImage[ 0 ], x, y, 0, 0, 32, 32, 255 );
		else if ( bellaIndex == 2 )
			HoDrawTexImage( BellaIconImage[ 1 ], x, y, 0, 0, 32, 32, 255 );
		else if ( bellaIndex == 3 )
			HoDrawTexImage( BellaIconImage[ 2 ], x, y, 0, 0, 32, 32, 255 );

		renderDevice.EndScene();
	}
}

void HoMessage::DrawClanMessageFrame( int x, int y, int messageWidth, int messageHeight )
{
	renderDevice.BeginScene();
	//양귀퉁이..
	HoDrawTexImage( ClanBoxImage2[ 0 ], x, y, 0, 0, 11, 13, 255 );
	HoDrawTexImage( ClanBoxImage2[ 2 ], x + 11 + messageWidth * 6, y, 5, 0, 11, 13, 255 );
	HoDrawTexImage( ClanBoxImage2[ 6 ], x, y + 13 + ( messageHeight - 1 ) * 14 + 14, 0, 3, 11, 13, 255 );
	HoDrawTexImage( ClanBoxImage2[ 8 ], x + 11 + messageWidth * 6, y + 13 + ( messageHeight - 1 ) * 14 + 14, 5, 3, 11, 13, 255 );

	//세로 왼쪽, 오른쪽
	for ( int m = 0; m < messageHeight; m++ )
	{
		HoDrawTexImage( ClanBoxImage2[ 3 ], x, y + 13 + ( 14 * m ), 0, 0, 11, 14, 255 );
		HoDrawTexImage( ClanBoxImage2[ 5 ], x + 11 + messageWidth * 6, y + 13 + ( 14 * m ), 5, 0, 11, 14, 255 );
	}

	//가로 위, 가로 아래, 가운데...
	for ( int m = 0; m < messageWidth; m++ )
	{
		HoDrawTexImage( ClanBoxImage2[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 13, 255 );
		HoDrawTexImage( ClanBoxImage2[ 7 ], x + 11 + 6 * m, y + 13 + ( 14 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 13, 255 );
	}


	//중간 뚤린곳...
	for ( int n = 0; n < messageHeight; n++ )
		for ( int m = 0; m < messageWidth; m++ )
		{
			if ( n == 0 )
			{
				HoDrawTexImage( ClanBoxImage2[ 4 ], x + 11 + m * 6, y + 13, 0, 0, 6, 14, 255 );
			}
			else
			{
				HoDrawTexImage( ClanBoxImage2[ 4 ], x + 11 + m * 6, y + 13 + ( n - 1 ) * 14 + 14, 0, 0, 6, 14, 255 );
			}
		}
	renderDevice.EndScene();
}

void HoMessage::DrawCharacterMessageFrame( int x, int y, int messageWidth, int messageHeight, bool tailFlag, BOOL selected )
{
	renderDevice.BeginScene();
	if ( MessageFrameSelectFlag == TRUE || tailFlag == TRUE )
	{
		//8.8
		//양귀퉁이..
		HoDrawTexImage( BoxImage3[ 0 ], x, y, 0, 0, 11, 5, 255 );
		HoDrawTexImage( BoxImage3[ 2 ], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255 );
		HoDrawTexImage( BoxImage3[ 6 ], x, y + 5 + ( messageHeight - 1 ) * 16 + 14, 0, 3, 11, 5, 255 );
		HoDrawTexImage( BoxImage3[ 8 ], x + 11 + messageWidth * 6, y + 5 + ( messageHeight - 1 ) * 16 + 14, 9, 3, 7, 5, 255 );
		if ( selected )
		{
			//양귀퉁이..
			HoDrawTexImage( BoxImage4[ 0 ], x, y, 0, 0, 11, 5, 255 );
			HoDrawTexImage( BoxImage4[ 2 ], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255 );
			HoDrawTexImage( BoxImage4[ 6 ], x, y + 5 + ( messageHeight - 1 ) * 16 + 14, 0, 3, 11, 5, 255 );
			HoDrawTexImage( BoxImage4[ 8 ], x + 11 + messageWidth * 6, y + 5 + ( messageHeight - 1 ) * 16 + 14, 9, 3, 7, 5, 255 );
		}


		//세로 왼쪽, 오른쪽
		for ( int m = 0; m < messageHeight; m++ )
		{
			if ( m == 0 )
			{
				HoDrawTexImage( BoxImage3[ 3 ], x, y + 5, 0, 0, 8, 14, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5, 0, 0, 3, 14, 255 ); //땜빵
				HoDrawTexImage( BoxImage3[ 5 ], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255 );
			}
			else
			{
				HoDrawTexImage( BoxImage3[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 3, 16, 255 ); //땜빵
				HoDrawTexImage( BoxImage3[ 5 ], x + 11 + messageWidth * 6, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
			}

			if ( selected )
			{
				if ( m == 0 )
				{
					HoDrawTexImage( BoxImage4[ 3 ], x, y + 5, 0, 0, 8, 14, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( BoxImage4[ 5 ], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255 );
				}
				else
				{
					HoDrawTexImage( BoxImage4[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( BoxImage4[ 5 ], x + 11 + messageWidth * 6, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
				}
			}
		}


		//가로 위, 가로 아래, 가운데...
		for ( int m = 0; m < messageWidth; m++ )
		{

			if ( tailFlag )
			{
				HoDrawTexImage( BoxImage3[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				if ( selected )
					HoDrawTexImage( BoxImage4[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );

				if ( m != ( messageWidth / 2 - 1 ) && m != ( messageWidth / 2 ) )
				{
					HoDrawTexImage( BoxImage3[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );
					if ( selected )
						HoDrawTexImage( BoxImage4[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}

				//말꼬리 찍기...
				if ( m == messageWidth / 2 - 1 )
				{

					HoDrawTexImage( BoxImage3[ 9 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 12, 13, 255 );
					if ( selected )
						HoDrawTexImage( BoxImage4[ 9 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 12, 13, 255 );
				}
			}
			else
			{
				HoDrawTexImage( BoxImage3[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				HoDrawTexImage( BoxImage3[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );

				if ( selected )
				{
					HoDrawTexImage( BoxImage4[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
					HoDrawTexImage( BoxImage4[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}
			}
		}
	}


	//중간 뚤린곳...
	for ( int n = 0; n < messageHeight; n++ )
		for ( int m = 0; m < messageWidth; m++ )
		{
			if ( n == 0 )
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m * 6, y + 5, 0, 0, 6, 14, 255 );
			}
			else
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m * 6, y + 5 + ( n - 1 ) * 16 + 14, 0, 0, 6, 16, 255 );
			}
		}
	renderDevice.EndScene();
}

//해외
#include <Wingdi.h>
int HoMessage::textarrange( char *teststr, bool clanm )
{
	int		len = 0;
	int		array1 = 0;
	int		array2 = 0;
	int		array3 = 0;
	BOOL	check = 0;

	ZeroMemory( textdata, sizeof( char ) * 12 * 64 );
	if ( clanm )
	{
		textdata[ 0 ][ 0 ] = 0x20;
		textdata[ 0 ][ 1 ] = 0x20;
		textdata[ 0 ][ 2 ] = 0x20;
		textdata[ 0 ][ 3 ] = 0x20;
		array2 = 4;
	}
	len = ( int )strlen( teststr );

	for ( int i = 0; i < len; i++ )
	{
		textdata[ array1 ][ array2 ] = teststr[ i ];
		if ( array2 >= 30 || i == len - 1 )
		{
			if ( i != ( len - 1 ) && CheckCode_2Byte( &teststr[ i ] ) == 1 && teststr[ i ] == 0x20 ) array2 = -1;
			else if ( i != ( len - 1 ) && CheckCode_2Byte( &teststr[ i + 1 ] ) == 1 && teststr[ i + 1 ] == 0x20 ) array2 = -1;
			else if ( i != ( len - 1 ) && CheckCode_2Byte( &teststr[ i ] ) == 1 && teststr[ i ] != 0x20 )
			{
				for ( array3 = 0; array3 < 6; array3++ )
				{
					check = 1;
					if ( teststr[ i - array3 ] == 0x20 && CheckCode_2Byte( &teststr[ i - array3 ] ) == 1 ) break;
					check = 0;
				}
				if ( check )
				{
					memcpy( textdata[ array1 + 1 ], teststr + ( i - ( array3 - 1 ) ), array3 );
					for ( int z = 0; z < array3; z++ ) textdata[ array1 ][ array2 - z ] = 0x20;
					array2 = ( array3 - 1 );
				}
				else
				{
					if ( textdata[ array1 ][ array2 ] >= 65 && textdata[ array1 ][ array2 ] <= 90 ||
						 textdata[ array1 ][ array2 ] >= 97 && textdata[ array1 ][ array2 ] <= 122 )
					{
						textdata[ array1 + 1 ][ 0 ] = textdata[ array1 ][ array2 ];
						textdata[ array1 ][ array2 ] = '-';
						array2 = 0;
					}
					else array2 = -1;
				}
			}
			else if ( i != ( len - 1 ) && CheckCode_2Byte( &teststr[ i ] ) == 2 )
			{
				if ( CheckCode_2Byte( &teststr[ i + 1 ] ) == 1 && teststr[ i + 1 ] == 0x20 ) array2 = -1;
				else
				{
					for ( array3 = 0; array3 < 6; array3++ )
					{
						check = 1;
						if ( teststr[ i - array3 ] == 0x20 && CheckCode_2Byte( &teststr[ i - array3 ] ) == 1 ) break;
						check = 0;
					}
					if ( check )
					{
						memcpy( textdata[ array1 + 1 ], teststr + ( i - ( array3 - 1 ) ), array3 );
						for ( int z = 0; z < array3; z++ ) textdata[ array1 ][ array2 - z ] = 0x20;
						array2 = ( array3 - 1 );
					}
					else
					{
						if ( textdata[ array1 ][ array2 ] >= 65 && textdata[ array1 ][ array2 ] <= 90 ||
							 textdata[ array1 ][ array2 ] >= 97 && textdata[ array1 ][ array2 ] <= 122 )
						{
							textdata[ array1 + 1 ][ 0 ] = textdata[ array1 ][ array2 ];
							textdata[ array1 ][ array2 ] = '-';
							array2 = 0;
						}
						else array2 = -1;
					}
				}
			}
			array1++;
		}
		array2++;
	}
	return array1;
}

void HoMessage::DrawClanMessage( int x, int y, char *message, int lineSize, DWORD color )
{
	//메시지의 전체 길이를 구한다.
	int messageLen = strlen( message );

	int messageWidth = 0;
	int messageHeight = 1;

	if ( lineSize != 0 && messageLen > lineSize ) //Message의 가로 크기가 정해 졌으면
	{
		messageHeight = messageLen / lineSize;
		if ( messageHeight%lineSize )
			messageHeight += 1;

		messageWidth = lineSize;
	}
	else
		messageWidth = messageLen;

	if ( messageWidth != 0 )
		x -= messageWidth * 6 + 20;
	//if(messageHeight != 0)
	//y -= messageHeight*14+8*2+8;
	DrawClanMessageFrame( x, y, messageWidth, messageHeight );

	HDC hdc;
	renderDevice.lpDDSBack->GetDC(&hdc);
	if ( hFont != NULL )

		SelectObject( hdc, hFont );
	SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, color );

#ifdef _LANGUAGE_ENGLISH //영문 줄바꿈 kyle
	if ( lineSize > 10 )
	{
		lineSize--;
		if ( lineSize < messageWidth )
		{
			messageWidth--;
			lineSize++;
		}

	}
#endif
#ifdef _LANGUAGE_ARGENTINA // 아르헨티나 줄바꿈 kyle
	if ( lineSize>10) {
		lineSize--;
		if ( lineSize<messageWidth ) {
			messageWidth--;
			lineSize++;
		}

	}
#endif

	char buffer[ 1024 ];
	if ( lineSize != 0 ) //한라인의 수가 결정 되지 않았을 때...
	{
		int start = 0;
		int end = 0;
		int lineCount = 0;

		for ( int m = 0; m < messageHeight; m++ )
		{
			memset( buffer, 0, sizeof( buffer ) );
			while ( 1 )
			{
				if ( message[ end ] == NULL )
					break;

				if ( CheckCode_2Byte( &message[ end ] ) == 2 ) //2바이트 검사
				{
					if ( ( lineCount + 2 ) > messageWidth )
						break;
					lineCount += 2;
					end += 2;

				}
				else
				{
					if ( ( lineCount + 1 ) > messageWidth )
						break;

					lineCount += 1;
					end += 1;

				}
			}
			memcpy( buffer, &message[ start ], end - start );

#ifdef _LANGUAGE_ENGLISH
			if ( message[ end + 1 ] && message[ end - 1 ] > ' ' && message[ end ] > ' ' )
			{
				lstrcat( buffer, "-" );
			}
			if ( message[ end + 1 ] == 0 )
			{
				buffer[ end - start ] = message[ end ];
			}
#endif
#ifdef _LANGUAGE_ARGENTINA // 아르헨티나 줄바꿈 kyle
			if ( message[end+1] && message[end-1]>' ' && message[end]>' ' ) {
				lstrcat( buffer , "-" );
			}
			if ( message[end+1]==0 ) {
				buffer[end-start] = message[end];
			}
#endif
			dsTextLineOut( hdc, x + 11, y + 13 + m * 14, buffer, lstrlen( buffer ) );

			if ( message[ end ] != NULL )
			{
				start = end;
				lineCount = 0;
			}
			else
				break;
		}
	}
	else
		dsTextLineOut( hdc, x + 11, y + 13, message, lstrlen( message ) );

	renderDevice.lpDDSBack->ReleaseDC(hdc);

}
void HoMessage::DrawCharacterMessage( int x, int y, char *message, int lineSize, DIRECTDRAWSURFACE clanMark, char *clanName, DWORD color1, BOOL selected, int bellaMarkIndex )
{
	bool CharNameFlag = false; //캐릭터 이름이 있는지..
	bool MessageFlag = false; //메시지가 있는지..
	bool ClanMarkFlag = false; //클랜 마크가 있는지..

	if ( clanMark != NULL )
		ClanMarkFlag = true;

#ifdef	_LANGUAGE_VEITNAM					
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef _LANGUAGE_THAI
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef _LANGUAGE_BRAZIL
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
	//아르헨티나
#ifdef _LANGUAGE_ARGENTINA
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
	//중국
#ifdef	_LANGUAGE_CHINESE
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef	_LANGUAGE_ENGLISH
	char	cname[ 256 ];
	int linesize = 0;
	ZeroMemory( cname, sizeof( char ) * 256 );
	linesize = textarrange( message, ClanMarkFlag );
#endif

	//메시지의 크기가 16보다 크면 메시지로 의심..
	if ( message != NULL )
	{
		int searchCount = 0;
		if ( strlen( message ) > 20 )
			searchCount = 20;
		else
			searchCount = strlen( message );
		bool succeed = false;
		for ( int index = 0; index < searchCount; index++ )
		{
			if ( message[ index ] == ':' )
			{
				succeed = true;

				memset( DrawMessageBuffer, 0, sizeof( DrawMessageBuffer ) );
				memset( DrawMessageBuffer, 32, sizeof( DrawMessageBuffer ) );
				if ( ClanMarkFlag == false )
				{
					strcpy( &DrawMessageBuffer[ index + 1 ], &message[ index + 1 ] );
#ifdef	_LANGUAGE_VEITNAM				
					memcpy(cname, message, index+1);
#endif
#ifdef _LANGUAGE_THAI
					memcpy(cname, message, index+1);
#endif
#ifdef _LANGUAGE_BRAZIL
					memcpy(cname, message, index+1);
#endif
#ifdef _LANGUAGE_ARGENTINA
					memcpy(cname, message, index+1);
#endif
#ifdef	_LANGUAGE_ENGLISH
					memcpy( cname, message, index + 1 );
#endif
					//중국
#ifdef	_LANGUAGE_CHINESE
					memcpy(cname, message, index+1);
#endif
				}
				else
				{
					strcpy( &DrawMessageBuffer[ index + 4 ], &message[ index + 1 ] );
#ifdef	_LANGUAGE_VEITNAM				
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef _LANGUAGE_THAI
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef _LANGUAGE_BRAZIL
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef _LANGUAGE_ARGENTINA
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef	_LANGUAGE_ENGLISH
					memcpy( cname, message, index + 1 );
					memcpy( cname + 4, message, index + 1 );
					cname[ 0 ] = 0x20;
					cname[ 1 ] = 0x20;
					cname[ 2 ] = 0x20;
					cname[ 3 ] = 0x20;
#endif
					//중국
#ifdef	_LANGUAGE_CHINESE
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
				}
				memset( DrawCharacterNameBuffer, 0, sizeof( DrawCharacterNameBuffer ) );
				memcpy( DrawCharacterNameBuffer, message, index + 1 );
				break;
			}
		}
		if ( succeed )
		{
			CharNameFlag = true;
			MessageFlag = true;
		}
		else
		{
			//CharNameFlag = true;
			MessageFlag = true;
			memset( DrawMessageBuffer, 0, sizeof( DrawMessageBuffer ) );
			if ( ClanMarkFlag == false ) //클랜 마크가 없으면 메시지만 입력하고 클랜 마트가 있으면 크랜마크 영역을 조금 남기고 메시지를 입력한다.
			{
				strcpy( DrawMessageBuffer, message );
			}
			else
			{
				memset( DrawMessageBuffer, 32, strlen( message ) + 2 ); //클랜 마크가 보이는 영역을 위해서 빈칸을 만든다.
				strcpy( &DrawMessageBuffer[ 2 + 1 ], message );
			}

		}
	}

	int messageWidth = 0;
	int messageHeight = 1;

#ifdef	_LANGUAGE_VEITNAM				
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef _LANGUAGE_THAI
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef _LANGUAGE_BRAZIL
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef _LANGUAGE_ARGENTINA
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef	_LANGUAGE_ENGLISH
	HDC hdc;
	renderDevice.lpDDSBack->GetDC(&hdc);
	if ( hFont != NULL )
		SelectObject( hdc, hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;

	for ( int i = 0; i < linesize; i++ )
	{
		GetTextExtentPoint32( hdc, textdata[ i ], lstrlen( textdata[ i ] ), &sizecheck );
		if ( textsize.x < sizecheck.cx ) textsize.x = sizecheck.cx;
		if ( textsize.y < sizecheck.cy ) textsize.y = sizecheck.cy;
	}
	renderDevice.lpDDSBack->ReleaseDC(hdc);
#endif
	//중국
#ifdef	_LANGUAGE_CHINESE
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif

	if ( MessageFlag || CharNameFlag )
	{
		//메시지의 전체 길이를 구한다.
		int messageLen = strlen( DrawMessageBuffer );
		if ( lineSize != 0 && messageLen > lineSize ) //Message의 가로 크기가 정해 졌으면
		{
			messageHeight = messageLen / lineSize;
			if ( messageHeight%lineSize )
				messageHeight += 1;

			messageWidth = lineSize;
		}
		else
			messageWidth = messageLen;

		if ( messageWidth != 0 )
			x -= messageWidth / 2 * 6 + 18 / 2;
		if ( messageHeight != 0 )
			y -= ( messageHeight - 1 ) * 16 + 14 + 5 * 2 + 12;

		//화면 바깥으로 나갔는지..
		if ( x < 0 || y < 0 ||
			(x + 18 + messageWidth * 6) >= renderDevice.GetScreenWidth() ||
			(y + 5 * 2 + ((messageHeight - 1) * 16 + 14) >= renderDevice.GetScreenHeight()))
			 return;

		//SetMessageFrameSelect(FALSE);
#ifdef	_LANGUAGE_VEITNAM				
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawCharacterMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawCharacterMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 
#ifdef _LANGUAGE_THAI
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawCharacterMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawCharacterMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 
#ifdef _LANGUAGE_BRAZIL
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawCharacterMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawCharacterMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 
#ifdef _LANGUAGE_ARGENTINA
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawCharacterMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawCharacterMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 
		//중국
#ifdef	_LANGUAGE_CHINESE
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawCharacterMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawCharacterMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 
#ifdef	_LANGUAGE_ENGLISH
		if ( MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE )
			DrawCharacterMessageFrame1( x - 2, y, textsize.x, textsize.y, linesize, CharNameFlag, selected );
		else
			DrawCharacterMessageFrame1( x, y, textsize.x, textsize.y, linesize, CharNameFlag, selected );
#else 

		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawCharacterMessageFrame(x-2, y, messageWidth, messageHeight, CharNameFlag, selected);
		else
			DrawCharacterMessageFrame(x, y, messageWidth, messageHeight, CharNameFlag, selected);
#endif
#endif
#endif
#endif
#endif
#endif

	}

	if ( bellaMarkIndex != -1 )
		DrawBellaIcon( x + 3 * messageWidth - 6, y - 30, bellaMarkIndex );

	if ( ClanMarkFlag )
	{
		int clanX = x;
		int clanY = y;
		//클랜 마크 찍기..
		if ( MessageFlag == false && CharNameFlag == false )
		{
			messageWidth = 1;
			if ( messageWidth != 0 )
				clanX -= messageWidth / 2 * 6 + 13;
			if ( messageHeight != 0 )
				clanY -= ( messageHeight - 1 ) * 16 + 14 + 5 * 2 + 8;
		}
		if ( CharNameFlag == false && MessageFlag == false )
			DrawClanMark( clanMark, clanName, clanX + 3, clanY, true );
		else
			DrawClanMark( clanMark, clanName, clanX + 3, clanY );

	}

#ifdef	_LANGUAGE_VEITNAM					
#else 
#ifdef _LANGUAGE_THAI
#else
#ifdef _LANGUAGE_BRAZIL
#else
#ifdef _LANGUAGE_ARGENTINA
#else
	// 중국
#ifdef _LANGUAGE_CHINESE
#else
#ifdef	_LANGUAGE_ENGLISH
#else
	HDC hdc;
#endif
#endif
#endif
#endif
#endif
#endif
	renderDevice.lpDDSBack->GetDC(&hdc);
	if ( hFont != NULL )
		SelectObject( hdc, hFont );
	SetBkMode( hdc, TRANSPARENT );

	if ( CharNameFlag == false )
	{
		if ( color1 == 0 )
			SetTextColor( hdc, RGB( 255, 255, 255 ) );
		else
			SetTextColor( hdc, color1 );
	}
	else
	{
		SetTextColor( hdc, RGB( 255, 255, 255 ) );
	}

	if ( MessageFlag )
	{
#ifdef	_LANGUAGE_VEITNAM
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef _LANGUAGE_THAI
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef _LANGUAGE_BRAZIL
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef _LANGUAGE_ARGENTINA
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
		//중국
#ifdef _LANGUAGE_CHINESE
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef	_LANGUAGE_ENGLISH
		for ( int m = 0; m < linesize; m++ )
		{
			TextOut( hdc, x + 9, y + 5 + m*textsize.y + 2, textdata[ m ], lstrlen( textdata[ m ] ) );
		}
#else
#ifdef _LANGUAGE_ENGLISH	//영문 줄바꿈 관련 kyle
		if ( lineSize>10) {
			lineSize--;
			if ( lineSize<messageWidth ) {
				messageWidth--;
				lineSize++;
			}

		}
#endif
#ifdef _LANGUAGE_ARGENTINA	//아르헨티나 줄바꿈 관련 kyle
		if ( lineSize>10) {
			lineSize--;
			if ( lineSize<messageWidth ) {
				messageWidth--;
				lineSize++;
			}

		}
#endif

		char buffer[1024];
		if(lineSize != 0) //한라인의 수가 결정 되지 않았을 때...
		{
			int start = 0;
			int end = 0;
			int lineCount = 0;

			for(int m = 0; m < messageHeight; m++)
			{
				memset(buffer, 0, sizeof(buffer));
				while(1)
				{
					if(DrawMessageBuffer[end] == NULL)
						break;

					if( CheckCode_2Byte( &DrawMessageBuffer[end] )==2 ) //2바이트 검사
					{
						if( (lineCount+2) > messageWidth)
							break;
						lineCount += 2;
						end += 2;

					}
					else
					{
						if( (lineCount+1) > messageWidth)
							break;

						lineCount += 1;
						end += 1;

					}
				}
				memcpy(buffer, &DrawMessageBuffer[start], end-start);

#ifdef _LANGUAGE_ENGLISH
				if ( DrawMessageBuffer[end+1] && DrawMessageBuffer[end-1]>' ' && DrawMessageBuffer[end]>' ' ) {
					lstrcat( buffer , "-" );
				}
				if ( DrawMessageBuffer[end+1]==0 ) {
					buffer[end-start] = DrawMessageBuffer[end];
				}
#endif
#ifdef _LANGUAGE_ARGENTINA	//아르헨티나 줄바꿈 관련 kyle
				if ( DrawMessageBuffer[end+1] && DrawMessageBuffer[end-1]>' ' && DrawMessageBuffer[end]>' ' ) {
					lstrcat( buffer , "-" );
				}
				if ( DrawMessageBuffer[end+1]==0 ) {
					buffer[end-start] = DrawMessageBuffer[end];
				}
#endif
				TextOut(hdc, x+9, y+5+m*16+2, buffer, lstrlen(buffer));
				//dsTextLineOut(x+9, y+5+m*16+2, buffer, lstrlen(buffer));
				if(DrawMessageBuffer[end] != NULL)
				{
					start = end;
					lineCount = 0;
				}
				else
					break;
			}
		}
		else
			TextOut(hdc, x+9, y+5+2, DrawMessageBuffer, lstrlen(DrawMessageBuffer));
		//dsTextLineOut(hdc, x+9, y+5+2, DrawMessageBuffer, lstrlen(DrawMessageBuffer));
#endif
#endif
#endif
#endif
#endif
#endif
	}

	//캐릭터 이름이 있는 경우는 이름만 다른색으로 찍는다..
	if ( CharNameFlag )
	{
		if ( color1 == 0 )
			//TextSetColor(RGB(255, 220, 100));
			SetTextColor( hdc, RGB( 255, 220, 100 ) );
		else
			//TextSetColor(color1);
			SetTextColor( hdc, color1 );

#ifdef	_LANGUAGE_VEITNAM
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef _LANGUAGE_THAI
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef _LANGUAGE_BRAZIL
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef _LANGUAGE_ARGENTINA
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
		//중국
#ifdef _LANGUAGE_CHINESE
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef	_LANGUAGE_ENGLISH
		TextOut( hdc, x + 9, y + 5 + 2, cname, lstrlen( cname ) );
#else


		if(ClanMarkFlag == false)
			TextOut(hdc, x+9, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer));
		//dsTextLineOut(hdc, x+9, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer));
		else
			TextOut(hdc, x+9+6*3, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer));
		//dsTextLineOut(hdc, x+9+6*3, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer));
#endif
#endif
#endif
#endif
#endif
#endif
	}

	//TextReleaseDC();
	renderDevice.lpDDSBack->ReleaseDC(hdc);
}

void HoMessage::DrawShopSellMessage( int x, int y, char *message, int lineSize, DIRECTDRAWSURFACE clanMark, DWORD color1, BOOL selected )
{
	bool CharNameFlag = false; //캐릭터 이름이 있는지..
	bool MessageFlag = false; //메시지가 있는지..
	bool ClanMarkFlag = false; //클랜 마크가 있는지..

	if ( clanMark != NULL )
		ClanMarkFlag = true;

#ifdef	_LANGUAGE_VEITNAM					
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef _LANGUAGE_THAI
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef _LANGUAGE_BRAZIL
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef _LANGUAGE_ARGENTINA
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
	//중국
#ifdef _LANGUAGE_CHINESE
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef	_LANGUAGE_ENGLISH
	char	cname[ 256 ];
	int linesize = 0;
	ZeroMemory( cname, sizeof( char ) * 256 );
	linesize = textarrange( message, ClanMarkFlag );
#endif

	//메시지의 크기가 16보다 크면 메시지로 의심..
	if ( message != NULL )
	{
		int searchCount = 0;
		if ( strlen( message ) > 20 )
			searchCount = 20;
		else
			searchCount = strlen( message );
		bool succeed = false;
		for ( int index = 0; index < searchCount; index++ )
		{
			if ( message[ index ] == ':' )
			{
				succeed = true;

				memset( DrawMessageBuffer, 0, sizeof( DrawMessageBuffer ) );
				memset( DrawMessageBuffer, 32, sizeof( DrawMessageBuffer ) );
				if ( ClanMarkFlag == false )
				{
					strcpy( &DrawMessageBuffer[ index + 1 ], &message[ index + 1 ] );
#ifdef	_LANGUAGE_VEITNAM				
					memcpy(cname, message, index+1);
#endif
#ifdef _LANGUAGE_THAI
					memcpy(cname, message, index+1);
#endif
#ifdef _LANGUAGE_BRAZIL
					memcpy(cname, message, index+1);
#endif
#ifdef _LANGUAGE_ARGENTINA
					memcpy(cname, message, index+1);
#endif
					//중국
#ifdef _LANGUAGE_CHINESE
					memcpy(cname, message, index+1);
#endif
#ifdef	_LANGUAGE_ENGLISH
					memcpy( cname, message, index + 1 );
#endif
				}
				else
				{
					strcpy( &DrawMessageBuffer[ index + 4 ], &message[ index + 1 ] );
#ifdef	_LANGUAGE_VEITNAM				
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef _LANGUAGE_THAI
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef _LANGUAGE_BRAZIL
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef _LANGUAGE_ARGENTINA
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
					//중국
#ifdef	_LANGUAGE_CHINESE
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef	_LANGUAGE_ENGLISH
					memcpy( cname, message, index + 1 );
					memcpy( cname + 4, message, index + 1 );
					cname[ 0 ] = 0x20;
					cname[ 1 ] = 0x20;
					cname[ 2 ] = 0x20;
					cname[ 3 ] = 0x20;
#endif
				}
				memset( DrawCharacterNameBuffer, 0, sizeof( DrawCharacterNameBuffer ) );
				memcpy( DrawCharacterNameBuffer, message, index + 1 );
				break;
			}
		}
		if ( succeed )
		{
			CharNameFlag = true;
			MessageFlag = true;
		}
		else
		{
			//CharNameFlag = true;
			MessageFlag = true;
			memset( DrawMessageBuffer, 0, sizeof( DrawMessageBuffer ) );
			if ( ClanMarkFlag == false ) //클랜 마크가 없으면 메시지만 입력하고 클랜 마트가 있으면 크랜마크 영역을 조금 남기고 메시지를 입력한다.
			{
				strcpy( DrawMessageBuffer, message );
			}
			else
			{
				memset( DrawMessageBuffer, 32, strlen( message ) + 2 ); //클랜 마크가 보이는 영역을 위해서 빈칸을 만든다.
				strcpy( &DrawMessageBuffer[ 2 + 1 ], message );
			}

		}
	}

	int messageWidth = 0;
	int messageHeight = 1;

#ifdef	_LANGUAGE_VEITNAM				
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef _LANGUAGE_THAI
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef _LANGUAGE_BRAZIL
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef _LANGUAGE_ARGENTINA
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
	//중국
#ifdef	_LANGUAGE_CHINESE
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef	_LANGUAGE_ENGLISH
	HDC hdc;
	renderDevice.lpDDSBack->GetDC(&hdc);
	if ( hFont != NULL )
		SelectObject( hdc, hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;

	for ( int i = 0; i < linesize; i++ )
	{
		GetTextExtentPoint32( hdc, textdata[ i ], lstrlen( textdata[ i ] ), &sizecheck );
		if ( textsize.x < sizecheck.cx ) textsize.x = sizecheck.cx;
		if ( textsize.y < sizecheck.cy ) textsize.y = sizecheck.cy;
	}
	renderDevice.lpDDSBack->ReleaseDC(hdc);
#endif

	if ( MessageFlag || CharNameFlag )
	{
		//메시지의 전체 길이를 구한다.
		int messageLen = strlen( DrawMessageBuffer );
		if ( lineSize != 0 && messageLen > lineSize ) //Message의 가로 크기가 정해 졌으면
		{
			messageHeight = messageLen / lineSize;
			if ( messageHeight%lineSize )
				messageHeight += 1;

			messageWidth = lineSize;
		}
		else
			messageWidth = messageLen;

		if ( messageWidth != 0 )
			x -= messageWidth / 2 * 6 + 18 / 2;
		if ( messageHeight != 0 )
			y -= ( messageHeight - 1 ) * 16 + 14 + 5 * 2 + 12;

		//화면 바깥으로 나갔는지..
		if ( x < 0 || y < 0 ||
			(x + 18 + messageWidth * 6) >= renderDevice.GetScreenWidth() ||
			(y + 5 * 2 + ((messageHeight - 1) * 16 + 14) >= renderDevice.GetScreenHeight()))
			 return;

#ifdef	_LANGUAGE_VEITNAM
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopSellMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawShopSellMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 
#ifdef _LANGUAGE_THAI
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopSellMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawShopSellMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 	
#ifdef _LANGUAGE_BRAZIL
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopSellMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawShopSellMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 	
#ifdef _LANGUAGE_ARGENTINA
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopSellMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawShopSellMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 	
		//중국
#ifdef _LANGUAGE_CHINESE
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopSellMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawShopSellMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 	
#ifdef	_LANGUAGE_ENGLISH
		if ( MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE )
			DrawShopSellMessageFrame1( x - 2, y, textsize.x, textsize.y, linesize, CharNameFlag, selected );
		else
			DrawShopSellMessageFrame1( x, y, textsize.x, textsize.y, linesize, CharNameFlag, selected );
#else 	

		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopSellMessageFrame(x-2, y, messageWidth, messageHeight, CharNameFlag, selected);
		else
			DrawShopSellMessageFrame(x, y, messageWidth, messageHeight, CharNameFlag, selected);
#endif
#endif
#endif
#endif
#endif
#endif

	}

	if ( ClanMarkFlag )
	{
		int clanX = x;
		int clanY = y;
		//클랜 마크 찍기..
		if ( MessageFlag == false && CharNameFlag == false )
		{
			messageWidth = 1;
			if ( messageWidth != 0 )
				clanX -= messageWidth / 2 * 6 + 13;
			if ( messageHeight != 0 )
				clanY -= ( messageHeight - 1 ) * 16 + 14 + 5 * 2 + 8;
		}

		DrawClanMark( clanMark, NULL, clanX + 3, clanY );
	}

#ifdef	_LANGUAGE_VEITNAM					
#else 
#ifdef _LANGUAGE_THAI
#else
#ifdef _LANGUAGE_BRAZIL
#else
#ifdef _LANGUAGE_ARGENTINA
#else
	//중국
#ifdef _LANGUAGE_CHINESE
#else
#ifdef	_LANGUAGE_ENGLISH
#else
	HDC hdc;
#endif
#endif
#endif
#endif
#endif
#endif

	renderDevice.lpDDSBack->GetDC(&hdc);
	if ( hFont != NULL )
		SelectObject( hdc, hFont );
	SetBkMode( hdc, TRANSPARENT );

	if ( CharNameFlag == false )
	{
		if ( color1 == 0 )
			SetTextColor( hdc, RGB( 255, 255, 255 ) );
		else
			SetTextColor( hdc, color1 );
	}
	else
	{
		SetTextColor( hdc, RGB( 255, 255, 255 ) );
	}

	if ( MessageFlag )
	{
#ifdef	_LANGUAGE_VEITNAM
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef _LANGUAGE_THAI
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef _LANGUAGE_BRAZIL
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef _LANGUAGE_ARGENTINA
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
		//중국
#ifdef _LANGUAGE_CHINESE
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef	_LANGUAGE_ENGLISH
		for ( int m = 0; m < linesize; m++ )
		{
			TextOut( hdc, x + 9, y + 5 + m*textsize.y + 2, textdata[ m ], lstrlen( textdata[ m ] ) );
		}
#else
#ifdef _LANGUAGE_ENGLISH
		if ( lineSize>10) {
			lineSize--;
			if ( lineSize<messageWidth ) {
				messageWidth--;
				lineSize++;
			}

		}
#endif
#ifdef _LANGUAGE_ARGENTINA	//아르헨티나 줄바꿈 관련 kyle
		if ( lineSize>10) {
			lineSize--;
			if ( lineSize<messageWidth ) {
				messageWidth--;
				lineSize++;
			}

		}
#endif

		char buffer[1024];
		if(lineSize != 0) //한라인의 수가 결정 되지 않았을 때...
		{
			int start = 0;
			int end = 0;
			int lineCount = 0;

			for(int m = 0; m < messageHeight; m++)
			{
				memset(buffer, 0, sizeof(buffer));
				while(1)
				{
					if(DrawMessageBuffer[end] == NULL)
						break;

					if( CheckCode_2Byte( &DrawMessageBuffer[end] )==2 ) //2바이트 검사
					{
						if( (lineCount+2) > messageWidth)
							break;
						lineCount += 2;
						end += 2;

					}
					else
					{
						if( (lineCount+1) > messageWidth)
							break;

						lineCount += 1;
						end += 1;

					}
				}
				memcpy(buffer, &DrawMessageBuffer[start], end-start);

#ifdef _LANGUAGE_ENGLISH
				if ( DrawMessageBuffer[end+1] && DrawMessageBuffer[end-1]>' ' && DrawMessageBuffer[end]>' ' ) {
					lstrcat( buffer , "-" );
				}
				if ( DrawMessageBuffer[end+1]==0 ) {
					buffer[end-start] = DrawMessageBuffer[end];
				}
#endif
#ifdef _LANGUAGE_ARGENTINA	//아르헨티나 줄바꿈 관련 kyle
				if ( DrawMessageBuffer[end+1] && DrawMessageBuffer[end-1]>' ' && DrawMessageBuffer[end]>' ' ) {
					lstrcat( buffer , "-" );
				}
				if ( DrawMessageBuffer[end+1]==0 ) {
					buffer[end-start] = DrawMessageBuffer[end];
				}
#endif
				dsTextLineOut(hdc, x+9, y+5+m*16+2, buffer, lstrlen(buffer));
				if(DrawMessageBuffer[end] != NULL)
				{
					start = end;
					lineCount = 0;
				}
				else
					break;
			}
		}
		else
			dsTextLineOut(hdc, x+9, y+5+2, DrawMessageBuffer, lstrlen(DrawMessageBuffer));
#endif
#endif	
#endif	
#endif
#endif
#endif
	}

	//캐릭터 이름이 있는 경우는 이름만 다른색으로 찍는다..
	if ( CharNameFlag )
	{
		if ( color1 == 0 )
			SetTextColor( hdc, RGB( 255, 220, 100 ) );
		else
			SetTextColor( hdc, color1 );

#ifdef	_LANGUAGE_VEITNAM
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef _LANGUAGE_THAI
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef _LANGUAGE_BRAZIL
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef _LANGUAGE_ARGENTINA
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef _LANGUAGE_CHINESE
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef	_LANGUAGE_ENGLISH
		TextOut( hdc, x + 9, y + 5 + 2, cname, lstrlen( cname ) );
#else

		if(ClanMarkFlag == false)
			dsTextLineOut(hdc, x+9, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer));
		else
			dsTextLineOut(hdc, x+9+6*3, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer));
#endif	
#endif	
#endif	
#endif
#endif
#endif
	}

	//TextReleaseDC();
	renderDevice.lpDDSBack->ReleaseDC(hdc);
}

//해외
void HoMessage::DrawCharacterMessageFrame1( int x, int y, int messageWidth, int messageHeight, int linecount, bool tailFlag, BOOL selected )
{
	renderDevice.BeginScene();
	if ( MessageFrameSelectFlag == TRUE || tailFlag == TRUE )
	{
		//8.8
		//양귀퉁이..
		HoDrawTexImage( BoxImage3[ 0 ], x, y, 0, 0, 11, 5, 255 );
		HoDrawTexImage( BoxImage3[ 2 ], x + 11 + messageWidth, y, 9, 0, 7, 5, 255 );
		HoDrawTexImage( BoxImage3[ 6 ], x, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 11, 5, 255 );
		HoDrawTexImage( BoxImage3[ 8 ], x + 11 + messageWidth, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 9, 3, 7, 5, 255 );
		if ( selected )
		{
			//양귀퉁이..
			HoDrawTexImage( BoxImage4[ 0 ], x, y, 0, 0, 11, 5, 255 );
			HoDrawTexImage( BoxImage4[ 2 ], x + 11 + messageWidth, y, 9, 0, 7, 5, 255 );
			HoDrawTexImage( BoxImage4[ 6 ], x, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 11, 5, 255 );
			HoDrawTexImage( BoxImage4[ 8 ], x + 11 + messageWidth, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 9, 3, 7, 5, 255 );
		}

		//세로 왼쪽, 오른쪽
		for ( int m = 0; m < linecount; m++ )
		{
			if ( m == 0 )
			{
				HoDrawTexImage( BoxImage3[ 3 ], x, y + 5, 0, 0, 8, 14, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5, 0, 0, 3, 14, 255 ); //땜빵
				HoDrawTexImage( BoxImage3[ 5 ], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255 );
			}
			else
			{
				HoDrawTexImage( BoxImage3[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 3, 16, 255 ); //땜빵
				HoDrawTexImage( BoxImage3[ 5 ], x + 11 + messageWidth, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
			}

			if ( selected )
			{
				if ( m == 0 )
				{
					HoDrawTexImage( BoxImage4[ 3 ], x, y + 5, 0, 0, 8, 14, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( BoxImage4[ 5 ], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255 );
				}
				else
				{
					HoDrawTexImage( BoxImage4[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( BoxImage4[ 5 ], x + 11 + messageWidth, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
				}
			}
		}

		//가로 위, 가로 아래, 가운데...
		for ( int m = 0; m < ( messageWidth / 6 ) + 1; m++ )
		{

			if ( tailFlag )
			{
				HoDrawTexImage( BoxImage3[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				if ( selected )
					HoDrawTexImage( BoxImage4[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );

				if ( m != ( ( messageWidth / 6 + 1 ) / 2 - 1 ) && m != ( ( messageWidth / 6 + 1 ) / 2 ) )
				{
					HoDrawTexImage( BoxImage3[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );
					if ( selected )
						HoDrawTexImage( BoxImage4[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}

				//말꼬리 찍기...
				if ( m == ( messageWidth / 6 + 1 ) / 2 - 1 )
				{

					HoDrawTexImage( BoxImage3[ 9 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 12, 13, 255 );
					if ( selected )
						HoDrawTexImage( BoxImage4[ 9 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 12, 13, 255 );
				}
			}
			else
			{
				HoDrawTexImage( BoxImage3[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				HoDrawTexImage( BoxImage3[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );

				if ( selected )
				{
					HoDrawTexImage( BoxImage4[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
					HoDrawTexImage( BoxImage4[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}
			}
		}
	}

	//중간 뚤린곳...
	for ( int n = 0; n < linecount; n++ )
		for ( int m = 0; m < messageWidth + 1; m++ )
		{
			if ( n == 0 )
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m, y + 5, 0, 0, 6, 14, 255 );
			}
			else
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m, y + 5 + ( n - 1 )*messageHeight + 14, 0, 0, 6, 16, 255 );
			}
		}
	if ( MessageFrameSelectFlag == TRUE || tailFlag == TRUE )
	{
		//8.8
		//양귀퉁이..
		HoDrawTexImage( BoxImage3[ 0 ], x, y, 0, 0, 11, 5, 255 );
		HoDrawTexImage( BoxImage3[ 2 ], x + 11 + messageWidth, y, 9, 0, 7, 5, 255 );
		HoDrawTexImage( BoxImage3[ 6 ], x, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 11, 5, 255 );
		HoDrawTexImage( BoxImage3[ 8 ], x + 11 + messageWidth, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 9, 3, 7, 5, 255 );
		if ( selected )
		{
			//양귀퉁이..
			HoDrawTexImage( BoxImage4[ 0 ], x, y, 0, 0, 11, 5, 255 );
			HoDrawTexImage( BoxImage4[ 2 ], x + 11 + messageWidth, y, 9, 0, 7, 5, 255 );
			HoDrawTexImage( BoxImage4[ 6 ], x, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 11, 5, 255 );
			HoDrawTexImage( BoxImage4[ 8 ], x + 11 + messageWidth, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 9, 3, 7, 5, 255 );
		}
	}
	renderDevice.EndScene();
}

//해외
void HoMessage::DrawShopByeMessageFrame1( int x, int y, int messageWidth, int messageHeight, int linecount, bool tailFlag, BOOL selected )
{
	renderDevice.BeginScene();
	if ( MessageFrameSelectFlag == TRUE || tailFlag == TRUE )
	{
		//8.8
		//양귀퉁이..
		HoDrawTexImage( ShopBoxByeImage1[ 0 ], x, y, 0, 0, 11, 5, 255 );
		HoDrawTexImage( ShopBoxByeImage1[ 2 ], x + 11 + messageWidth, y, 9, 0, 7, 5, 255 );
		HoDrawTexImage( ShopBoxByeImage1[ 6 ], x, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 11, 5, 255 );
		HoDrawTexImage( ShopBoxByeImage1[ 8 ], x + 11 + messageWidth, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 9, 3, 7, 5, 255 );
		if ( selected )
		{
			//양귀퉁이..
			HoDrawTexImage( ShopBoxByeImage2[ 0 ], x, y, 0, 0, 11, 5, 255 );
			HoDrawTexImage( ShopBoxByeImage2[ 2 ], x + 11 + messageWidth, y, 9, 0, 7, 5, 255 );
			HoDrawTexImage( ShopBoxByeImage2[ 6 ], x, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 11, 5, 255 );
			HoDrawTexImage( ShopBoxByeImage2[ 8 ], x + 11 + messageWidth, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 9, 3, 7, 5, 255 );
		}


		//세로 왼쪽, 오른쪽
		for ( int m = 0; m < linecount; m++ )
		{
			if ( m == 0 )
			{
				HoDrawTexImage( ShopBoxByeImage1[ 3 ], x, y + 5, 0, 0, 8, 14, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5, 0, 0, 3, 14, 255 ); //땜빵
				HoDrawTexImage( ShopBoxByeImage1[ 5 ], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255 );
			}
			else
			{
				HoDrawTexImage( ShopBoxByeImage1[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 3, 16, 255 ); //땜빵
				HoDrawTexImage( ShopBoxByeImage1[ 5 ], x + 11 + messageWidth, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
			}

			if ( selected )
			{
				if ( m == 0 )
				{
					HoDrawTexImage( ShopBoxByeImage2[ 3 ], x, y + 5, 0, 0, 8, 14, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( ShopBoxByeImage2[ 5 ], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255 );
				}
				else
				{
					HoDrawTexImage( ShopBoxByeImage2[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( ShopBoxByeImage2[ 5 ], x + 11 + messageWidth, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
				}
			}
		}


		//가로 위, 가로 아래, 가운데...
		for ( int m = 0; m < ( messageWidth / 6 ) + 1; m++ )
		{

			if ( tailFlag )
			{
				HoDrawTexImage( ShopBoxByeImage1[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				if ( selected )
					HoDrawTexImage( ShopBoxByeImage2[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );

				if ( m != ( messageWidth / 2 - 1 ) && m != ( messageWidth / 2 ) )
				{
					HoDrawTexImage( ShopBoxByeImage1[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );
					if ( selected )
						HoDrawTexImage( ShopBoxByeImage2[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}

				//말꼬리 찍기...
				if ( m == ( ( messageWidth / 6 ) + 1 ) / 2 - 1 )
				{

					HoDrawTexImage( ShopBoxByeImage1[ 9 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 12, 13, 255 );
					if ( selected )
						HoDrawTexImage( ShopBoxByeImage2[ 9 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 12, 13, 255 );
				}
			}
			else
			{
				HoDrawTexImage( ShopBoxByeImage1[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				HoDrawTexImage( ShopBoxByeImage1[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );

				if ( selected )
				{
					HoDrawTexImage( ShopBoxByeImage2[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
					HoDrawTexImage( ShopBoxByeImage2[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}
			}
		}
	}


	//중간 뚤린곳...
	for ( int n = 0; n < linecount; n++ )
		for ( int m = 0; m < messageWidth + 1; m++ )
		{
			if ( n == 0 )
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m, y + 5, 0, 0, 6, 14, 255 );
			}
			else
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m, y + 5 + ( n - 1 )*messageHeight + 14, 0, 0, 6, 16, 255 );
			}
		}

	renderDevice.EndScene();
}

//해외
void HoMessage::DrawShopSellMessageFrame1( int x, int y, int messageWidth, int messageHeight, int linecount, bool tailFlag, BOOL selected )
{
	renderDevice.BeginScene();
	if ( MessageFrameSelectFlag == TRUE || tailFlag == TRUE )
	{
		//8.8
		//양귀퉁이..
		HoDrawTexImage( ShopBoxSellImage1[ 0 ], x, y, 0, 0, 11, 5, 255 );
		HoDrawTexImage( ShopBoxSellImage1[ 2 ], x + 11 + messageWidth, y, 9, 0, 7, 5, 255 );
		HoDrawTexImage( ShopBoxSellImage1[ 6 ], x, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 11, 5, 255 );
		HoDrawTexImage( ShopBoxSellImage1[ 8 ], x + 11 + messageWidth, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 9, 3, 7, 5, 255 );
		if ( selected )
		{
			//양귀퉁이..
			HoDrawTexImage( ShopBoxSellImage2[ 0 ], x, y, 0, 0, 11, 5, 255 );
			HoDrawTexImage( ShopBoxSellImage2[ 2 ], x + 11 + messageWidth, y, 9, 0, 7, 5, 255 );
			HoDrawTexImage( ShopBoxSellImage2[ 6 ], x, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 11, 5, 255 );
			HoDrawTexImage( ShopBoxSellImage2[ 8 ], x + 11 + messageWidth, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 9, 3, 7, 5, 255 );
		}


		//세로 왼쪽, 오른쪽
		for ( int m = 0; m < linecount; m++ )
		{
			if ( m == 0 )
			{
				HoDrawTexImage( ShopBoxSellImage1[ 3 ], x, y + 5, 0, 0, 8, 14, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5, 0, 0, 3, 14, 255 ); //땜빵
				HoDrawTexImage( ShopBoxSellImage1[ 5 ], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255 );
			}
			else
			{
				HoDrawTexImage( ShopBoxSellImage1[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 3, 16, 255 ); //땜빵
				HoDrawTexImage( ShopBoxSellImage1[ 5 ], x + 11 + messageWidth, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
			}

			if ( selected )
			{
				if ( m == 0 )
				{
					HoDrawTexImage( ShopBoxSellImage2[ 3 ], x, y + 5, 0, 0, 8, 14, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( ShopBoxSellImage2[ 5 ], x + 11 + messageWidth, y + 5, 9, 0, 7, 14, 255 );
				}
				else
				{
					HoDrawTexImage( ShopBoxSellImage2[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( ShopBoxSellImage2[ 5 ], x + 11 + messageWidth, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
				}
			}
		}


		//가로 위, 가로 아래, 가운데...
		for ( int m = 0; m < ( messageWidth / 6 ) + 1; m++ )
		{

			if ( tailFlag )
			{
				HoDrawTexImage( ShopBoxSellImage1[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				if ( selected )
					HoDrawTexImage( ShopBoxSellImage2[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );

				if ( m != ( messageWidth / 2 - 1 ) && m != ( messageWidth / 2 ) )
				{
					HoDrawTexImage( ShopBoxSellImage1[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );
					if ( selected )
						HoDrawTexImage( ShopBoxSellImage2[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}

				//말꼬리 찍기...
				if ( m == ( ( messageWidth / 6 ) + 1 ) / 2 - 1 )
				{

					HoDrawTexImage( ShopBoxSellImage1[ 9 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 12, 13, 255 );
					if ( selected )
						HoDrawTexImage( ShopBoxSellImage2[ 9 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 12, 13, 255 );
				}
			}
			else
			{
				HoDrawTexImage( ShopBoxSellImage1[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				HoDrawTexImage( ShopBoxSellImage1[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );

				if ( selected )
				{
					HoDrawTexImage( ShopBoxSellImage2[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
					HoDrawTexImage( ShopBoxSellImage2[ 7 ], x + 11 + 6 * m, y + 5 + ( messageHeight*( linecount - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}
			}
		}
	}


	//중간 뚤린곳...
	for ( int n = 0; n < linecount; n++ )
		for ( int m = 0; m < messageWidth + 1; m++ )
		{
			if ( n == 0 )
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m, y + 5, 0, 0, 6, 14, 255 );
			}
			else
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m, y + 5 + ( n - 1 )*messageHeight + 14, 0, 0, 6, 16, 255 );
			}
		}

	renderDevice.EndScene();
}

void HoMessage::DrawShopSellMessageFrame( int x, int y, int messageWidth, int messageHeight, bool tailFlag, BOOL selected )
{
	renderDevice.BeginScene();
	if ( MessageFrameSelectFlag == TRUE || tailFlag == TRUE )
	{
		//8.8
		//양귀퉁이..
		HoDrawTexImage( ShopBoxSellImage1[ 0 ], x, y, 0, 0, 11, 5, 255 );
		HoDrawTexImage( ShopBoxSellImage1[ 2 ], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255 );
		HoDrawTexImage( ShopBoxSellImage1[ 6 ], x, y + 5 + ( messageHeight - 1 ) * 16 + 14, 0, 3, 11, 5, 255 );
		HoDrawTexImage( ShopBoxSellImage1[ 8 ], x + 11 + messageWidth * 6, y + 5 + ( messageHeight - 1 ) * 16 + 14, 9, 3, 7, 5, 255 );
		if ( selected )
		{
			//양귀퉁이..
			HoDrawTexImage( ShopBoxSellImage2[ 0 ], x, y, 0, 0, 11, 5, 255 );
			HoDrawTexImage( ShopBoxSellImage2[ 2 ], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255 );
			HoDrawTexImage( ShopBoxSellImage2[ 6 ], x, y + 5 + ( messageHeight - 1 ) * 16 + 14, 0, 3, 11, 5, 255 );
			HoDrawTexImage( ShopBoxSellImage2[ 8 ], x + 11 + messageWidth * 6, y + 5 + ( messageHeight - 1 ) * 16 + 14, 9, 3, 7, 5, 255 );
		}


		//세로 왼쪽, 오른쪽
		for ( int m = 0; m < messageHeight; m++ )
		{
			if ( m == 0 )
			{
				HoDrawTexImage( ShopBoxSellImage1[ 3 ], x, y + 5, 0, 0, 8, 14, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5, 0, 0, 3, 14, 255 ); //땜빵
				HoDrawTexImage( ShopBoxSellImage1[ 5 ], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255 );
			}
			else
			{
				HoDrawTexImage( ShopBoxSellImage1[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 3, 16, 255 ); //땜빵
				HoDrawTexImage( ShopBoxSellImage1[ 5 ], x + 11 + messageWidth * 6, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
			}

			if ( selected )
			{
				if ( m == 0 )
				{
					HoDrawTexImage( ShopBoxSellImage2[ 3 ], x, y + 5, 0, 0, 8, 14, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( ShopBoxSellImage2[ 5 ], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255 );
				}
				else
				{
					HoDrawTexImage( ShopBoxSellImage2[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( ShopBoxSellImage2[ 5 ], x + 11 + messageWidth * 6, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
				}
			}
		}


		//가로 위, 가로 아래, 가운데...
		for ( int m = 0; m < messageWidth; m++ )
		{

			if ( tailFlag )
			{
				HoDrawTexImage( ShopBoxSellImage1[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				if ( selected )
					HoDrawTexImage( ShopBoxSellImage2[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );

				if ( m != ( messageWidth / 2 - 1 ) && m != ( messageWidth / 2 ) )
				{
					HoDrawTexImage( ShopBoxSellImage1[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );
					if ( selected )
						HoDrawTexImage( ShopBoxSellImage2[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}

				//말꼬리 찍기...
				if ( m == messageWidth / 2 - 1 )
				{

					HoDrawTexImage( ShopBoxSellImage1[ 9 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 12, 13, 255 );
					if ( selected )
						HoDrawTexImage( ShopBoxSellImage2[ 9 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 12, 13, 255 );
				}
			}
			else
			{
				HoDrawTexImage( ShopBoxSellImage1[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				HoDrawTexImage( ShopBoxSellImage1[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );

				if ( selected )
				{
					HoDrawTexImage( ShopBoxSellImage2[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
					HoDrawTexImage( ShopBoxSellImage2[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}
			}
		}
	}


	//중간 뚤린곳...
	for ( int n = 0; n < messageHeight; n++ )
		for ( int m = 0; m < messageWidth; m++ )
		{
			if ( n == 0 )
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m * 6, y + 5, 0, 0, 6, 14, 255 );
			}
			else
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m * 6, y + 5 + ( n - 1 ) * 16 + 14, 0, 0, 6, 16, 255 );
			}
		}

	renderDevice.EndScene();
}

void HoMessage::DrawShopByeMessage( int x, int y, char *message, int lineSize, DIRECTDRAWSURFACE clanMark, DWORD color1, BOOL selected )
{
	bool CharNameFlag = false; //캐릭터 이름이 있는지..
	bool MessageFlag = false; //메시지가 있는지..
	bool ClanMarkFlag = false; //클랜 마크가 있는지..

	if ( clanMark != NULL )
		ClanMarkFlag = true;

#ifdef	_LANGUAGE_VEITNAM					
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef _LANGUAGE_THAI
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef _LANGUAGE_BRAZIL
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef _LANGUAGE_ARGENTINA
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
	//중국
#ifdef _LANGUAGE_CHINESE
	char	cname[256];
	int linesize=0;
	ZeroMemory(cname,sizeof(char)*256);
	linesize = textarrange(message,ClanMarkFlag);
#endif
#ifdef	_LANGUAGE_ENGLISH
	char	cname[ 256 ];
	int linesize = 0;
	ZeroMemory( cname, sizeof( char ) * 256 );
	linesize = textarrange( message, ClanMarkFlag );
#endif

	//메시지의 크기가 16보다 크면 메시지로 의심..
	if ( message != NULL )
	{
		int searchCount = 0;
		if ( strlen( message ) > 20 )
			searchCount = 20;
		else
			searchCount = strlen( message );
		bool succeed = false;
		for ( int index = 0; index < searchCount; index++ )
		{
			if ( message[ index ] == ':' )
			{
				succeed = true;

				memset( DrawMessageBuffer, 0, sizeof( DrawMessageBuffer ) );
				memset( DrawMessageBuffer, 32, sizeof( DrawMessageBuffer ) );
				if ( ClanMarkFlag == false )
				{
					strcpy( &DrawMessageBuffer[ index + 1 ], &message[ index + 1 ] );
#ifdef	_LANGUAGE_VEITNAM				
					memcpy(cname, message, index+1);
#endif
#ifdef _LANGUAGE_THAI
					memcpy(cname, message, index+1);
#endif
#ifdef _LANGUAGE_BRAZIL
					memcpy(cname, message, index+1);
#endif
#ifdef _LANGUAGE_ARGENTINA
					memcpy(cname, message, index+1);
#endif
					//중국
#ifdef _LANGUAGE_CHINESE
					memcpy(cname, message, index+1);
#endif
#ifdef	_LANGUAGE_ENGLISH
					memcpy( cname, message, index + 1 );
#endif
				}
				else
				{
					strcpy( &DrawMessageBuffer[ index + 4 ], &message[ index + 1 ] );
#ifdef	_LANGUAGE_VEITNAM				
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef _LANGUAGE_THAI
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef _LANGUAGE_BRAZIL
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
#ifdef _LANGUAGE_ARGENTINA
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif
					//중국
#ifdef	_LANGUAGE_CHINESE
					memcpy(cname, message, index+1);
					memcpy(cname+4, message, index+1);
					cname[0] = 0x20;
					cname[1] = 0x20;
					cname[2] = 0x20;
					cname[3] = 0x20;
#endif		
#ifdef	_LANGUAGE_ENGLISH
					memcpy( cname, message, index + 1 );
					memcpy( cname + 4, message, index + 1 );
					cname[ 0 ] = 0x20;
					cname[ 1 ] = 0x20;
					cname[ 2 ] = 0x20;
					cname[ 3 ] = 0x20;
#endif
				}
				memset( DrawCharacterNameBuffer, 0, sizeof( DrawCharacterNameBuffer ) );
				memcpy( DrawCharacterNameBuffer, message, index + 1 );
				break;
			}
		}
		if ( succeed )
		{
			CharNameFlag = true;
			MessageFlag = true;
		}
		else
		{
			//CharNameFlag = true;
			MessageFlag = true;
			memset( DrawMessageBuffer, 0, sizeof( DrawMessageBuffer ) );
			if ( ClanMarkFlag == false ) //클랜 마크가 없으면 메시지만 입력하고 클랜 마트가 있으면 크랜마크 영역을 조금 남기고 메시지를 입력한다.
			{
				strcpy( DrawMessageBuffer, message );
			}
			else
			{
				memset( DrawMessageBuffer, 32, strlen( message ) + 2 ); //클랜 마크가 보이는 영역을 위해서 빈칸을 만든다.
				strcpy( &DrawMessageBuffer[ 2 + 1 ], message );
			}

		}
	}

	int messageWidth = 0;
	int messageHeight = 1;

#ifdef	_LANGUAGE_VEITNAM				
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef _LANGUAGE_THAI
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef _LANGUAGE_BRAZIL
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef _LANGUAGE_ARGENTINA
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
	//중국
#ifdef _LANGUAGE_CHINESE
	HDC hdc;
	lpDDSBack->GetDC(&hdc);
	if(hFont != NULL)
		SelectObject( hdc , hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;	

	for(int i=0;i<linesize;i++)
	{
		GetTextExtentPoint32(hdc,textdata[i],lstrlen(textdata[i]),&sizecheck);
		if(textsize.x<sizecheck.cx) textsize.x = sizecheck.cx;
		if(textsize.y<sizecheck.cy) textsize.y = sizecheck.cy;
	}
	lpDDSBack->ReleaseDC(hdc);
#endif
#ifdef	_LANGUAGE_ENGLISH
	HDC hdc;
	renderDevice.lpDDSBack->GetDC(&hdc);
	if ( hFont != NULL )
		SelectObject( hdc, hFont );
	SetBkMode( hdc, TRANSPARENT );

	SIZE	sizecheck;
	textsize.x = 0;
	textsize.y = 0;

	for ( int i = 0; i < linesize; i++ )
	{
		GetTextExtentPoint32( hdc, textdata[ i ], lstrlen( textdata[ i ] ), &sizecheck );
		if ( textsize.x < sizecheck.cx ) textsize.x = sizecheck.cx;
		if ( textsize.y < sizecheck.cy ) textsize.y = sizecheck.cy;
	}
	renderDevice.lpDDSBack->ReleaseDC(hdc);
#endif

	if ( MessageFlag || CharNameFlag )
	{
		//메시지의 전체 길이를 구한다.
		int messageLen = strlen( DrawMessageBuffer );
		if ( lineSize != 0 && messageLen > lineSize ) //Message의 가로 크기가 정해 졌으면
		{
			messageHeight = messageLen / lineSize;
			if ( messageHeight%lineSize )
				messageHeight += 1;

			messageWidth = lineSize;
		}
		else
			messageWidth = messageLen;

		if ( messageWidth != 0 )
			x -= messageWidth / 2 * 6 + 18 / 2;
		if ( messageHeight != 0 )
			y -= ( messageHeight - 1 ) * 16 + 14 + 5 * 2 + 12;

		//화면 바깥으로 나갔는지..
		if ( x < 0 || y < 0 ||
			(x + 18 + messageWidth * 6) >= renderDevice.GetScreenWidth() ||
			(y + 5 * 2 + ((messageHeight - 1) * 16 + 14) >= renderDevice.GetScreenHeight()))
			 return;

#ifdef	_LANGUAGE_VEITNAM				
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopByeMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawShopByeMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 
#ifdef _LANGUAGE_THAI
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopByeMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawShopByeMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 	
#ifdef _LANGUAGE_BRAZIL
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopByeMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawShopByeMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 	
#ifdef _LANGUAGE_ARGENTINA
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopByeMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawShopByeMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else 	
		//중국
#ifdef	_LANGUAGE_CHINESE
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopByeMessageFrame1(x-2, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
		else
			DrawShopByeMessageFrame1(x, y, textsize.x, textsize.y,linesize, CharNameFlag, selected);
#else
#ifdef	_LANGUAGE_ENGLISH
		if ( MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE )
			DrawShopByeMessageFrame1( x - 2, y, textsize.x, textsize.y, linesize, CharNameFlag, selected );
		else
			DrawShopByeMessageFrame1( x, y, textsize.x, textsize.y, linesize, CharNameFlag, selected );
#else 
		if(MessageFrameSelectFlag == FALSE && CharNameFlag == FALSE)
			DrawShopByeMessageFrame(x-2, y, messageWidth, messageHeight, CharNameFlag, selected);
		else
			DrawShopByeMessageFrame(x, y, messageWidth, messageHeight, CharNameFlag, selected);
#endif
#endif
#endif
#endif
#endif
#endif

	}

	if ( ClanMarkFlag )
	{
		int clanX = x;
		int clanY = y;
		//클랜 마크 찍기..
		if ( MessageFlag == false && CharNameFlag == false )
		{
			messageWidth = 1;
			if ( messageWidth != 0 )
				clanX -= messageWidth / 2 * 6 + 13;
			if ( messageHeight != 0 )
				clanY -= ( messageHeight - 1 ) * 16 + 14 + 5 * 2 + 8;
		}

		DrawClanMark( clanMark, NULL, clanX + 3, clanY );
	}

#ifdef	_LANGUAGE_VEITNAM
#else 
#ifdef _LANGUAGE_THAI
#else
#ifdef _LANGUAGE_BRAZIL
#else
#ifdef _LANGUAGE_ARGENTINA
#else
	//중국
#ifdef _LANGUAGE_CHINESE
#else
#ifdef	_LANGUAGE_ENGLISH
#else
	HDC hdc;
#endif
#endif
#endif
#endif
#endif
#endif

	renderDevice.lpDDSBack->GetDC(&hdc);
	if ( hFont != NULL )
		SelectObject( hdc, hFont );
	SetBkMode( hdc, TRANSPARENT );

	if ( CharNameFlag == false )
	{
		if ( color1 == 0 )
			SetTextColor( hdc, RGB( 255, 255, 255 ) );
		else
			SetTextColor( hdc, color1 );
	}
	else
	{
		SetTextColor( hdc, RGB( 255, 255, 255 ) );
	}

	if ( MessageFlag )
	{
#ifdef	_LANGUAGE_VEITNAM
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef _LANGUAGE_THAI
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef _LANGUAGE_BRAZIL
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef _LANGUAGE_ARGENTINA
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
		//중국
#ifdef _LANGUAGE_CHINESE
		for(int m = 0; m < linesize; m++)
		{
			TextOut(hdc, x+9, y+5+m*textsize.y+2, textdata[m], lstrlen(textdata[m]));
		}
#else
#ifdef	_LANGUAGE_ENGLISH
		for ( int m = 0; m < linesize; m++ )
		{
			TextOut( hdc, x + 9, y + 5 + m*textsize.y + 2, textdata[ m ], lstrlen( textdata[ m ] ) );
		}
#else
#ifdef _LANGUAGE_ENGLISH
		if ( lineSize>10) {
			lineSize--;
			if ( lineSize<messageWidth ) {
				messageWidth--;
				lineSize++;
			}

		}
#endif
#ifdef _LANGUAGE_ARGENTINA	//아르헨티나 줄바꿈 관련 kyle
		if ( lineSize>10) {
			lineSize--;
			if ( lineSize<messageWidth ) {
				messageWidth--;
				lineSize++;
			}

		}
#endif

		char buffer[1024];
		if(lineSize != 0) //한라인의 수가 결정 되지 않았을 때...
		{
			int start = 0;
			int end = 0;
			int lineCount = 0;

			for(int m = 0; m < messageHeight; m++)
			{
				memset(buffer, 0, sizeof(buffer));
				while(1)
				{
					if(DrawMessageBuffer[end] == NULL)
						break;

					if( CheckCode_2Byte( &DrawMessageBuffer[end] )==2 ) //2바이트 검사
					{
						if( (lineCount+2) > messageWidth)
							break;
						lineCount += 2;
						end += 2;

					}
					else
					{
						if( (lineCount+1) > messageWidth)
							break;

						lineCount += 1;
						end += 1;

					}
				}
				memcpy(buffer, &DrawMessageBuffer[start], end-start);

#ifdef _LANGUAGE_ENGLISH
				if ( DrawMessageBuffer[end+1] && DrawMessageBuffer[end-1]>' ' && DrawMessageBuffer[end]>' ' ) {
					lstrcat( buffer , "-" );
				}
				if ( DrawMessageBuffer[end+1]==0 ) {
					buffer[end-start] = DrawMessageBuffer[end];
				}
#endif
#ifdef _LANGUAGE_ARGENTINA	//아르헨티나 줄바꿈 관련 kyle
				if ( DrawMessageBuffer[end+1] && DrawMessageBuffer[end-1]>' ' && DrawMessageBuffer[end]>' ' ) {
					lstrcat( buffer , "-" );
				}
				if ( DrawMessageBuffer[end+1]==0 ) {
					buffer[end-start] = DrawMessageBuffer[end];
				}
#endif
				dsTextLineOut(hdc, x+9, y+5+m*16+2, buffer, lstrlen(buffer));
				if(DrawMessageBuffer[end] != NULL)
				{
					start = end;
					lineCount = 0;
				}
				else
					break;
			}
		}
		else
			dsTextLineOut(hdc, x+9, y+5+2, DrawMessageBuffer, lstrlen(DrawMessageBuffer));
#endif	
#endif	
#endif	
#endif
#endif
#endif
	}

	//캐릭터 이름이 있는 경우는 이름만 다른색으로 찍는다..
	if ( CharNameFlag )
	{
		if ( color1 == 0 )
			SetTextColor( hdc, RGB( 255, 220, 100 ) );
		else
			SetTextColor( hdc, color1 );
#ifdef	_LANGUAGE_VEITNAM
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef _LANGUAGE_THAI
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef _LANGUAGE_BRAZIL
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef _LANGUAGE_ARGENTINA
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
		//중국
#ifdef _LANGUAGE_CHINESE
		TextOut(hdc, x+9, y+5+2, cname, lstrlen(cname));
#else
#ifdef	_LANGUAGE_ENGLISH
		TextOut( hdc, x + 9, y + 5 + 2, cname, lstrlen( cname ) );
#else

		if(ClanMarkFlag == false)
			dsTextLineOut(hdc, x+9, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer));
		else
			dsTextLineOut(hdc, x+9+6*3, y+5+2, DrawCharacterNameBuffer, lstrlen(DrawCharacterNameBuffer));
#endif
#endif
#endif
#endif
#endif
#endif
	}

	//TextReleaseDC();
	renderDevice.lpDDSBack->ReleaseDC(hdc);
}

void HoMessage::DrawShopByeMessageFrame( int x, int y, int messageWidth, int messageHeight, bool tailFlag, BOOL selected )
{
	renderDevice.BeginScene();
	if ( MessageFrameSelectFlag == TRUE || tailFlag == TRUE )
	{
		//8.8
		//양귀퉁이..
		HoDrawTexImage( ShopBoxByeImage1[ 0 ], x, y, 0, 0, 11, 5, 255 );
		HoDrawTexImage( ShopBoxByeImage1[ 2 ], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255 );
		HoDrawTexImage( ShopBoxByeImage1[ 6 ], x, y + 5 + ( messageHeight - 1 ) * 16 + 14, 0, 3, 11, 5, 255 );
		HoDrawTexImage( ShopBoxByeImage1[ 8 ], x + 11 + messageWidth * 6, y + 5 + ( messageHeight - 1 ) * 16 + 14, 9, 3, 7, 5, 255 );
		if ( selected )
		{
			//양귀퉁이..
			HoDrawTexImage( ShopBoxByeImage2[ 0 ], x, y, 0, 0, 11, 5, 255 );
			HoDrawTexImage( ShopBoxByeImage2[ 2 ], x + 11 + messageWidth * 6, y, 9, 0, 7, 5, 255 );
			HoDrawTexImage( ShopBoxByeImage2[ 6 ], x, y + 5 + ( messageHeight - 1 ) * 16 + 14, 0, 3, 11, 5, 255 );
			HoDrawTexImage( ShopBoxByeImage2[ 8 ], x + 11 + messageWidth * 6, y + 5 + ( messageHeight - 1 ) * 16 + 14, 9, 3, 7, 5, 255 );
		}


		//세로 왼쪽, 오른쪽
		for ( int m = 0; m < messageHeight; m++ )
		{
			if ( m == 0 )
			{
				HoDrawTexImage( ShopBoxByeImage1[ 3 ], x, y + 5, 0, 0, 8, 14, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5, 0, 0, 3, 14, 255 ); //땜빵
				HoDrawTexImage( ShopBoxByeImage1[ 5 ], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255 );
			}
			else
			{
				HoDrawTexImage( ShopBoxByeImage1[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 ); //왼쪽 오른쪽..
				HoDrawTexImage( BoxImage3[ 4 ], x + 8, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 3, 16, 255 ); //땜빵
				HoDrawTexImage( ShopBoxByeImage1[ 5 ], x + 11 + messageWidth * 6, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
			}

			if ( selected )
			{
				if ( m == 0 )
				{
					HoDrawTexImage( ShopBoxByeImage2[ 3 ], x, y + 5, 0, 0, 8, 14, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( ShopBoxByeImage2[ 5 ], x + 11 + messageWidth * 6, y + 5, 9, 0, 7, 14, 255 );
				}
				else
				{
					HoDrawTexImage( ShopBoxByeImage2[ 3 ], x, y + 5 + ( 16 * ( m - 1 ) ) + 14, 0, 0, 8, 16, 255 );
					//HoDrawTexImage( BoxImage3[4], x+8,                 y+5+(16*m), 0, 0,  3, 16, 255); //땜빵
					HoDrawTexImage( ShopBoxByeImage2[ 5 ], x + 11 + messageWidth * 6, y + 5 + ( 16 * ( m - 1 ) ) + 14, 9, 0, 7, 16, 255 );
				}
			}
		}


		//가로 위, 가로 아래, 가운데...
		for ( int m = 0; m < messageWidth; m++ )
		{

			if ( tailFlag )
			{
				HoDrawTexImage( ShopBoxByeImage1[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				if ( selected )
					HoDrawTexImage( ShopBoxByeImage2[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );

				if ( m != ( messageWidth / 2 - 1 ) && m != ( messageWidth / 2 ) )
				{
					HoDrawTexImage( ShopBoxByeImage1[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );
					if ( selected )
						HoDrawTexImage( ShopBoxByeImage2[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}

				//말꼬리 찍기...
				if ( m == messageWidth / 2 - 1 )
				{

					HoDrawTexImage( ShopBoxByeImage1[ 9 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 12, 13, 255 );
					if ( selected )
						HoDrawTexImage( ShopBoxByeImage2[ 9 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 12, 13, 255 );
				}
			}
			else
			{
				HoDrawTexImage( ShopBoxByeImage1[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
				HoDrawTexImage( ShopBoxByeImage1[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );

				if ( selected )
				{
					HoDrawTexImage( ShopBoxByeImage2[ 1 ], x + 11 + 6 * m, y, 0, 0, 6, 5, 255 );
					HoDrawTexImage( ShopBoxByeImage2[ 7 ], x + 11 + 6 * m, y + 5 + ( 16 * ( messageHeight - 1 ) ) + 14, 0, 3, 6, 5, 255 );
				}
			}
		}
	}


	//중간 뚤린곳...
	for ( int n = 0; n < messageHeight; n++ )
		for ( int m = 0; m < messageWidth; m++ )
		{
			if ( n == 0 )
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m * 6, y + 5, 0, 0, 6, 14, 255 );
			}
			else
			{
				HoDrawTexImage( BoxImage3[ 4 ], x + 11 + m * 6, y + 5 + ( n - 1 ) * 16 + 14, 0, 0, 6, 16, 255 );
			}
		}

	renderDevice.EndScene();
}

// x, y 위치에 message를 출력한다...(박스를 그리고)
// lineSize: 글자를 가로크기를 제한..(boxAttrib: BOX_ONE 기본 메시지 창)
void HoMessage::Draw( int x, int y, char *message, int lineSize, int addLine, int boxAttrib )
{
	//Message의 전체 크기를 구한다.
	int messageSize = strlen( message );//GetMessageSize(message);

	int messageWidth = 0;
	int messageHeight = 1;

	//글자의 가로, 세로 사이즈를 구한다...
	if ( lineSize != 0 && messageSize > lineSize )	//Message의 가로 크기가 정해 졌으면...
	{
		messageHeight = messageSize / lineSize;
		if ( messageHeight % ( lineSize ) )
			messageHeight += 1;

		messageWidth = lineSize;
	}
	else
	{
		//Message의 가로 크기가 정해 지지 않았으면..
		messageWidth = messageSize;
		if ( messageWidth % 2 )
			messageWidth++;
	}


	//messageWidth = messageWidth/2;

	if ( messageWidth == 0 )
		return;



	messageHeight += addLine;
	//Clipping
	if ( boxAttrib == BOX_ONE || boxAttrib == BOX_TWO )
	{
		if ( x < 0 || y < 0 ||
			(x + 16 * 2 + messageWidth * 6) >= renderDevice.GetScreenWidth() || y < 0 ||
			x < 0 || (y + 16 * 2 + messageHeight * 6) >= renderDevice.GetScreenHeight() ||
			(x + 16 * 2 + messageWidth * 6) >= renderDevice.GetScreenWidth() || (y + 16 * 2 + messageHeight * 6) >= renderDevice.GetScreenHeight())
			 return;
	}

	renderDevice.BeginScene();



	//lpD3DDevice->BeginScene();
	//귀퉁이 4개를 그린다..
	if ( boxAttrib == BOX_ONE )
	{
		dsDrawTexImage( BoxImage1[ 0 ], x, y, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage1[ 2 ], x + messageWidth * 6 + 16, y, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage1[ 6 ], x, y + messageHeight * 14 + 16, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage1[ 8 ], x + messageWidth * 6 + 16, y + messageHeight * 14 + 16, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
	}
	else if ( boxAttrib == BOX_TWO )
	{
		dsDrawTexImage( BoxImage2[ 0 ], x, y, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage2[ 1 ], x + 16 + messageWidth * 6, y, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage2[ 2 ], x, y + 16 + messageHeight * 14, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
		dsDrawTexImage( BoxImage2[ 3 ], x + 16 + messageWidth * 6, y + 16 + messageHeight * 14, 16, 16, 16, 16, 0, 0, 16, 16, 255 );
	}


	int m, n;
	if ( boxAttrib == BOX_ONE || boxAttrib == BOX_TWO )
	{
		for ( m = 0; m < messageWidth; m++ )
		{
			//dsDrawTexImage( BoxImage1[1], x+16+6*m, y,						  6, 14, 16, 16, 0, 0, 6, 14, 255);
			//dsDrawTexImage( BoxImage1[7], x+16+6*m, y+16+(14*messageHeight),  6, 14, 16, 16, 0, 0, 6, 16, 255);

			dsDrawTexImage( BoxImage1[ 1 ], x + 16 + 6 * m, y, 6, 16, 16, 16, 0, 0, 6, 16, 255 );
			dsDrawTexImage( BoxImage1[ 7 ], x + 16 + 6 * m, y + 16 + ( 14 * messageHeight ), 6, 16, 16, 16, 0, 0, 6, 16, 255 );
		}


		//세로 왼쪽, 오른쪽
		for ( m = 0; m < messageHeight; m++ )
		{
			dsDrawTexImage( BoxImage1[ 3 ], x, y + 16 + ( 14 * m ), 16, 14, 16, 16, 0, 0, 16, 12, 255 );
			dsDrawTexImage( BoxImage1[ 5 ], x + 16 + 6 * messageWidth, y + 16 + ( 14 * m ), 16, 14, 16, 16, 0, 0, 16, 12, 255 );
		}

		//중간 뚤린곳...
		for ( m = 0; m < messageWidth; m++ )
		{
			for ( n = 0; n < messageHeight; n++ )
				dsDrawTexImage( BoxImage1[ 4 ], x + 16 + 6 * m, y + 16 + 14 * n, 6, 14, 32, 32, 0, 0, 12, 12, 255 );
		}
	}

	messageWidth = messageWidth / 2;
	//lpD3DDevice->EndScene();
	renderDevice.EndScene();

	TextStartPosY = y;
	messageHeight = messageHeight - addLine;
	HDC hdc;
	renderDevice.lpDDSBack->GetDC(&hdc);
	if ( hFont != NULL )

		SelectObject( hdc, hFont );
	SetBkMode( hdc, TRANSPARENT );
	SetTextColor( hdc, RGB( 255, 255, 255 ) );

	char buffer[ 1024 ];
	if ( lineSize != 0 ) //한라인의 수가 결정 되지 않았을 때...
	{
		int start = 0;
		int end = 0;
		int lineCount = 0;
		for ( m = 0; m < messageHeight; m++ )
		{
			memset( buffer, 0, sizeof( buffer ) );

			while ( 1 )
			{
				if ( message[ end ] == NULL )
					break;
				if ( message[ end ] & 0x80 ) //한글인지 검사.
				{
					lineCount += 2;
					end += 2;
				}
				else
				{
					lineCount += 1;
					end += 1;
				}
				if ( lineCount > messageWidth * 2 - 1 )
					break;
			}
			memcpy( buffer, &message[ start ], end - start );
			dsTextLineOut( hdc, x + 17, TextStartPosY + 16 + m * 15, buffer, lstrlen( buffer ) );

			if ( message[ end ] != NULL )
			{

				if ( message[ end ] == ' ' )
					end += 1;

				start = end;
				lineCount = 0;
			}
			else
				break;
		}
	}
	else
		dsTextLineOut( hdc, x + 17, y + 16, message, lstrlen( message ) );
	renderDevice.lpDDSBack->ReleaseDC(hdc);
	Width = messageWidth * 12 + 16 * 2;

}

int DrawCharacterShopSellMessage( int x, int y, char*message, int lineSize, DIRECTDRAWSURFACE clanMark, DWORD charColor, BOOL selected )
{
	ChatMessage.DrawShopSellMessage( x, y, message, lineSize, clanMark, charColor, selected );
	return TRUE;
}

int DrawCharacterShopByeMessage( int x, int y, char*message, int lineSize, DIRECTDRAWSURFACE clanMark, DWORD charColor, BOOL selected )
{
	ChatMessage.DrawShopByeMessage( x, y, message, lineSize, clanMark, charColor, selected );
	return TRUE;
}

int DrawCharacterMessage( int x, int y, char *message, int lineSize, DIRECTDRAWSURFACE clanMark, char *clanName, DWORD color1, BOOL selected, int bellaMarkIndex )
{
	ChatMessage.DrawCharacterMessage( x, y, message, lineSize, clanMark, clanName, color1, selected, bellaMarkIndex );
	return TRUE;
}

int DrawTwoLineMessage( int x, int y, char *messageOne, char *messageTwo, DWORD color1, DWORD color2, DIRECTDRAWSURFACE clanMark, BOOL selected, int bellaMarkIndex )
{
	ChatMessage.DrawTwoLineMessage( x, y, messageOne, messageTwo, color1, color2, clanMark, selected, bellaMarkIndex );
	return TRUE;
}

//클랜 설명하는 메시지 박스..
int DrawClanMessage( int x, int y, char *message, int lineSize, DWORD color )
{
	//682, 14이다..
	ChatMessage.DrawClanMessage( x, y, message, lineSize, color );
	return TRUE;
}



int DrawMessage( int x, int y, char *message, int lineSize, int boxAttrib )
{

	ChatMessage.Draw( x, y, message, lineSize, 0, boxAttrib );
	return TRUE;
}

BOOL TextGetDC( )
{
	renderDevice.lpDDSBack->GetDC(&ChatMessage.TextDC);
#ifndef dsTextLineOut_ENGLISH	
	SetBkMode( ChatMessage.TextDC, TRANSPARENT );
#endif

	return TRUE;
}

BOOL TextReleaseDC( )
{

#ifndef dsTextLineOut_ENGLISH
	if ( ChatMessage.OldFont )
		SelectObject( ChatMessage.TextDC, ChatMessage.OldFont );
	renderDevice.lpDDSBack->ReleaseDC(ChatMessage.TextDC);
#endif
	return TRUE;
}

BOOL TextSelectObject( HFONT font )
{
	if ( font != NULL )
	{
		ChatMessage.OldFont = NULL;
		ChatMessage.OldFont = ( HFONT )SelectObject( ChatMessage.TextDC, font );
	}

#ifdef dsTextLineOut_ENGLISH
	TEXTMETRIC textMetric; 
	GetTextMetrics(ChatMessage.TextDC, &textMetric);
	EngSetFont(textMetric.tmMaxCharWidth);

	if(ChatMessage.OldFont)
		SelectObject( ChatMessage.TextDC, ChatMessage.OldFont);
	lpDDSBack->ReleaseDC(ChatMessage.TextDC);

	//TextReleaseDC();
#endif

	return TRUE;
}
BOOL TextSetColor( COLORREF color )
{
#ifndef dsTextLineOut_ENGLISH	
	SetTextColor( ChatMessage.TextDC, color );
#endif

#ifdef  dsTextLineOut_ENGLISH
	EngSetColor(color);
#endif
	return TRUE;
}

BOOL dsTextLineOut( int x, int y, char *lpszString, int nCount )
{
#ifndef dsTextLineOut_ENGLISH
	dsTextLineOut( ChatMessage.TextDC, x, y, lpszString, nCount );
#endif

#ifdef	dsTextLineOut_ENGLISH
	EngdsTextLineOut(x, y, lpszString, nCount);
#endif
	return TRUE;
}

void	SetMessageFrameSelect( BOOL flag )
{
	ChatMessage.SetMessageFrameSelect( flag );
}

int InitMessageBox( )
{
	ChatMessage.Init( );
	return TRUE;
}

BOOL	HoButton::ButtonUseFlag = FALSE;
HoButton::HoButton( )
{
	ButtonInDownFlag = FALSE;
	State = BUTTON_STATE_NONE;
	SizeWidth = 64;
	SizeHeight = 32;

}

HoButton::~HoButton( )
{

}

void HoButton::Init( char *stateFirstIamge, char *stateThirdImage )
{
	StateFirstImage = CreateTextureMaterial( stateFirstIamge, 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	//StateThirdImage  = CreateTextureMaterial( stateThirdImage, 0, 0, 0,0, SMMAT_BLEND_ALPHA );	
}

void HoButton::InitCrashRect( int left, int top, int right, int bottom )
{
	CrashRect.left = left;
	CrashRect.top = top;
	CrashRect.right = right;
	CrashRect.bottom = bottom;
}

void HoButton::Init( char *stateFirstImage, int sizeWidth, int sizeHeight )
{
	StateFirstImage = CreateTextureMaterial( stateFirstImage, 0, 0, 0, 0, SMMAT_BLEND_ALPHA );
	SizeWidth = sizeWidth;
	SizeHeight = sizeHeight;

	CrashRect.left = 0;
	CrashRect.top = 0;
	CrashRect.right = SizeWidth;
	CrashRect.bottom = SizeHeight;
}

//return 값: 마우스가 Button위에 있는지...
BOOL HoButton::Draw( int x, int y, int BlendFlag )
{
	PosX = x;
	PosY = y;

	if ( BlendFlag < 255 )
		dsDrawTexImage( StateFirstImage, x, y, SizeWidth, SizeHeight, BlendFlag );
	else
	{
		if ( State == 0 )
		{
			dsDrawTexImage( StateFirstImage, x, y, SizeWidth, SizeHeight, 255 );
		}
		else if ( State == 1 )
		{
			dsDrawTexImage( StateFirstImage, x, y, SizeWidth, SizeHeight, 255, 40 );
			return TRUE;
		}
		else if ( State == 2 )
		{
			dsDrawTexImage( StateFirstImage, x + 1, y + 1, SizeWidth, SizeHeight, 255, 40 );
			//dsDrawTexImage( StateThirdImage, x+2, y+2, 8, 8, 255);
		}
	}
	return FALSE;
}

BOOL HoButton::Main( int mouseX, int mouseY, int downFlag )
{
	//마우스가 버튼 영역 안으로 들어 왔을 때...
	if ( mouseX > ( PosX + CrashRect.left ) && mouseX < PosX + ( CrashRect.right )
		 && mouseY >( PosY + CrashRect.top ) && mouseY < PosY + ( CrashRect.bottom ) )
	{
		if ( ButtonUseFlag == FALSE )
		{
			State = BUTTON_STATE_IN;
			//마우스 Down일 때
			if ( downFlag )
			{
				ButtonUseFlag = TRUE;
				ButtonInDownFlag = TRUE;
				State = BUTTON_STATE_DOWN;
			}

			//마우스로 버튼을 한번 누르고, Up일 경우..
			if ( ButtonInDownFlag && downFlag == FALSE )
			{
				ButtonInDownFlag = FALSE;
				State = BUTTON_STATE_NONE;
				return TRUE;
			}
		}
	}
	else
	{
		if ( ButtonInDownFlag == TRUE )
			State = BUTTON_STATE_IN;
		else
			State = BUTTON_STATE_NONE;

		if ( downFlag == FALSE )
			ButtonInDownFlag = FALSE;
	}

	if ( downFlag == FALSE )
		ButtonUseFlag = FALSE;
	return FALSE;
}

HoMessageBox::HoMessageBox( )
{
	Flag = FALSE;
}

HoMessageBox::~HoMessageBox( )
{

}

//return 1이면 Ok
//return 2이면 Cancel
BOOL HoMessageBox::Main( int mouseX, int mouseY, int downFlag )
{
	if ( Flag )
	{
		if ( Button[ 0 ].Main( mouseX, mouseY, downFlag ) )
		{
			Flag = FALSE;
			return 1;
		}

		if ( Button[ 1 ].Main( mouseX, mouseY, downFlag ) )
		{
			Flag = FALSE;
			return 2;
		}
	}
	return FALSE;
}


BOOL HoMessageBox::Draw( int x, int y, char *message, int Color )
{
	if ( Flag )
	{
		Message.DrawMessageBox( x, y, message, BOX_ONE, Color );
		int messageWidth = Message.GetWidth( );
		x = Message.PosX;
		y = Message.PosY;

		renderDevice.BeginScene();

		Button[ 0 ].Draw( x + messageWidth / 2 - 54 - 13, 40 + y );
		Button[ 1 ].Draw( x + messageWidth / 2 + 7, 40 + y );

		renderDevice.EndScene();
	}
	return TRUE;
}

void HoMessageBox::Init( )
{
	Button[ 0 ].Init( "StartImage\\Login\\CharSelect\\Bt_ok.tga", 64, 32 );
	Button[ 1 ].Init( "StartImage\\Login\\CharSelect\\Bt_cancel.tga", 64, 32 );
	Message.Init( );
}

