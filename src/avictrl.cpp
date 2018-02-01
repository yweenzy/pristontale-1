#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
#include <stdlib.h>
#include <stdarg.h>
#include <mmsystem.h>
#include <vfw.h>

#include <ddraw.h>

#include "avictrl.h"

#define	SCREEN_BPP		16			//  ( Bit / Pixel )  

// -- Multimedia/AVI globals
PAVISTREAM pas;
LONG lFmtLength;
LPBITMAPINFOHEADER lpSrcFmt;
LPBITMAPINFOHEADER lpTarget;
LONG lLength;
AVISTREAMINFO si;
LPBYTE lpB, lpI;
DWORD lpISize;

LONG lIndex;
LONG lFrames;
HIC hic;
OPENFILENAME ofn;

int VideoWidth,VideoHeight;

int PlayFrame;

/*
void SampleDraw (const LPBYTE pbBits)

{   // SampleDraw //
	HRESULT ddrval;
    DDSURFACEDESC ddsd;
    BYTE *src, *dst;
	int y;

    if (pbBits)
		{
		ddsd.dwSize = sizeof(ddsd);
		ddrval = lpDDSSource->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
		if( ddrval == DD_OK )
			{
				src = (BYTE *)pbBits + dwWidth * dwHeight;

				dst = (BYTE *)ddsd.lpSurface;
				for( y=0; y<(int)dwHeight;y++ )
				{
					memcpy(dst, src, dwWidth);
					dst += ddsd.lPitch;
					src -= dwWidth;
				}
				lpDDSSource->Unlock(NULL);
			}
		}

	RECT rc;
	RECT rcSrc;
	SetRect(&rc,0,0,320,240);
	SetRect(&rcSrc,0,0,dwWidth,dwHeight);
	lpDDSBack->Blt(&rc, lpDDSSource, &rcSrc, DDBLT_WAIT, NULL);

	// Flip the surfaces
	while( 1 )
       {
       ddrval = lpDDSPrimary->Flip( NULL, 0 );
       if( ddrval == DD_OK )
          {
          break;
          }
       if( ddrval == DDERR_SURFACELOST )
          {
          ddrval = restoreAll();
          if( ddrval != DD_OK )
              {
              break;
              }
          }
       if( ddrval != DDERR_WASSTILLDRAWING )
          {
              break;
          }
       }
}   // SampleDraw //
*/


int OpenVideoFile (char *AVIFile )

{   // SampleRun //

    AVIFileInit();

    AVIStreamOpenFromFile(&pas,
        AVIFile,						// AVI 파일이름
        streamtypeVIDEO,
        0,
        OF_READ | OF_SHARE_EXCLUSIVE,
        NULL);

    AVIStreamFormatSize(pas, 0, &lFmtLength);

    lpSrcFmt = (LPBITMAPINFOHEADER)malloc( lFmtLength);
    lpTarget = (LPBITMAPINFOHEADER)malloc( lFmtLength+(sizeof(RGBQUAD)*256));

    AVIStreamReadFormat(pas, 0, lpSrcFmt, &lFmtLength);
/*
    if ((lpSrcFmt->biWidth > 320) || (lpSrcFmt->biHeight > 240))

        {   // Image dimensions outside of maximum limit

            AVIStreamRelease(pas);
            AVIFileExit();
            return -1;

        }   // Image dimensions outside of maximum limit
*/
    lFrames = AVIStreamLength(pas);

    memcpy(lpTarget, lpSrcFmt, lFmtLength);
    lpTarget->biBitCount = SCREEN_BPP;					//8;
    lpTarget->biCompression = BI_RGB;
    lpTarget->biSizeImage = lpTarget->biHeight * lpTarget->biWidth;
	
	VideoWidth = lpTarget->biWidth ;
	VideoHeight= lpTarget->biHeight;


    AVIStreamInfo(pas, &si, sizeof AVISTREAMINFO);

    lLength = (ULONG)lpTarget->biSizeImage * (ULONG)(lpSrcFmt->biBitCount >> 3);

    if (si.dwSuggestedBufferSize)
        if ((LONG)si.dwSuggestedBufferSize < lLength)
            lLength = (LONG)si.dwSuggestedBufferSize;

    lpB = (LPBYTE)malloc( lLength);
	lpISize = lpTarget->biSizeImage * (SCREEN_BPP/8);
    lpI = (LPBYTE)malloc( lpISize );

    hic = ICDecompressOpen(ICTYPE_VIDEO, si.fccHandler, lpSrcFmt, lpTarget);

    lpSrcFmt = (LPBITMAPINFOHEADER)realloc(lpSrcFmt, lFmtLength+(sizeof(RGBQUAD)*256));

    ICDecompressGetPalette(hic, lpSrcFmt, lpTarget);

	PlayFrame = 0;


    return lFrames;

} 
/*
void SampleStream ()

{   // SampleStream //

//    SampleInit((LPBITMAPINFO)lpTarget);

    for (lIndex = 0; lIndex < lFrames; ++lIndex)

        {	// Extract individual frame!

            AVIStreamRead(pas, lIndex, 1, lpB, lLength, NULL, NULL);
            ICDecompress(hic, 0, lpSrcFmt, lpB, lpTarget, lpI);
//            SampleDraw(lpI);

        }	// Extract individual frame!

    ICClose(hic);
    AVIStreamRelease(pas);
    AVIFileExit();
//	PostMessage(hwnd, WM_KEYDOWN, VK_ESCAPE, 0);
		
}   // SampleStream //
*/


void CloseAVIData()
{
	free( lpI );
	free( lpB );
	free( lpTarget );
	free( lpSrcFmt );

    ICClose(hic);
    AVIStreamRelease(pas);
    AVIFileExit();

}

void AVIDrawSurface ( DIRECTDRAWSURFACE *lpDDSSource , int frame )

{   // SampleDraw //
	HRESULT ddrval;
	DIRECTDRAWSURFACE	lpDDSurface;
    DDSURFACEDESC2 ddsd;
    BYTE *src, *dst;
	int y;
	int dwHeight = VideoHeight;
	int dwWidth  = VideoWidth*2;
	int cnt;

	int a,b;

	lpDDSurface = *lpDDSSource;

    AVIStreamRead(pas, frame, 1, lpB, lLength, NULL, NULL);
    ICDecompress(hic, 0, lpSrcFmt, lpB, lpTarget, lpI);

	ddsd.dwSize = sizeof(ddsd);
	ddrval = lpDDSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);

	if( ddrval == DD_OK )
	{
		src = (BYTE *)lpI + dwWidth * dwHeight;
		dst = (BYTE *)ddsd.lpSurface;

		for( y=0; y<(int)dwHeight;y++ )
		{
//			memcpy(dst, src, dwWidth);
//			memcpy(dst, src, 256*2);
			
			for(cnt=0;cnt<256;cnt++) 
			{
				a = (WORD &)src[cnt<<1];
				b = a;
				b <<=1;
				a &= 0x001F;
				b &= 0xFFE0;
				(WORD &)dst[cnt<<1] = a|b;
			}

			dst += ddsd.lPitch;
			src -= dwWidth;
		}
		lpDDSurface->Unlock(NULL);
	}
}


void AVIFrameRead( int frame )
{

	if ( (frame - PlayFrame)>15 ) PlayFrame = frame - 15;

	while( frame>PlayFrame ) {

		AVIStreamRead(pas, PlayFrame, 1, lpB, lLength, NULL, NULL);
	    ICDecompress(hic, 0, lpSrcFmt, lpB, lpTarget, lpI);
		PlayFrame++;
	}
}


