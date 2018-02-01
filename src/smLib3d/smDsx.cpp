#include <math.h>
#include <stdio.h>
#include "common.h"
#include "smd3d.h"


/***************************************
* Global Variables
***************************************/
static LPDEVICEDESC		lpDeviceDesc = NULL;

//The RenderDevice Object
RenderDevice			renderDevice;


extern int ParkPlaying;			//Of the video player
extern RECT ParkPlayRect;		//

extern HWND hwnd;
extern HWND hFocusWnd;

extern DWORD smBackColor;

static DWORD FlagsToBitDepth(DWORD dwFlags)
{
	if (dwFlags & DDBD_1)
		return 1L;
	else if (dwFlags & DDBD_2)
		return 2L;
	else if (dwFlags & DDBD_4)
		return 4L;
	else if (dwFlags & DDBD_8)
		return 8L;
	else if (dwFlags & DDBD_16)
		return 16L;
	else if (dwFlags & DDBD_24)
		return 24L;
	else if (dwFlags & DDBD_32)
		return 32L;
	else
		return 0L;
}

// Direct3D Device EnumCallback Functions
HRESULT WINAPI DeviceEnumCallback(LPGUID lpGuid, LPSTR lpDeviceDescription, LPSTR lpDeviceName, LPD3DDEVICEDESC lpD3DHWDeviceDesc, LPD3DDEVICEDESC lpD3DHELDeviceDesc, LPVOID lpUserArg)
{
	if (!lpUserArg)
		return DDENUMRET_OK;

	// Direct3D Device Add to the list
	LPDEVICEDESC desc, *lpDesc = (LPDEVICEDESC *)lpUserArg;
	if (!*lpDesc)
		desc = *lpDesc = renderDevice.CreateDevice();
	else
		desc = renderDevice.CreateDevice(*lpDesc);

	// Guid값 복사
	memcpy(&desc->guid, lpGuid, sizeof(GUID));

	// 디바이스 정보 복사
	strcpy(desc->szName, lpDeviceName);
	strcpy(desc->szDesc, lpDeviceDescription);


	// 하드웨어 드라이브 인지 검사 하고 드라이브 정보 복사
	if (lpD3DHWDeviceDesc->dcmColorModel)
	{
		desc->bIsHardware = TRUE;
		memcpy(&desc->Desc, lpD3DHWDeviceDesc, sizeof(D3DDEVICEDESC));
	}
	else
	{
		desc->bIsHardware = FALSE;
		memcpy(&desc->Desc, lpD3DHELDeviceDesc, sizeof(D3DDEVICEDESC));
	}

	return DDENUMRET_OK;
}

// Direct3D Device EnumCallback Functions
static HRESULT WINAPI EnumZBufferCallback(DDPIXELFORMAT *DDP_Format, VOID *DDP_Desired)
{
	if (DDP_Format->dwFlags == DDPF_ZBUFFER)
	{
		memcpy(DDP_Desired, DDP_Format, sizeof(DDPIXELFORMAT));
		return D3DENUMRET_CANCEL;
	}
	return D3DENUMRET_OK;
}

RenderDevice::RenderDevice()
{
	WindowMode = WINMODE;
	smTextureBPP = 16;
	smScreenWidth = 0;
	smScreenHeight = 0;

	smFlipCount = 0;

	lpD3DDeviceDesc = NULL;

	// DirectDraw          
	lpDD = NULL;
	lpDDSPrimary = NULL;
	lpDDSBack = NULL;
	lpDDClipper = NULL;

	// Direct3D
	lpD3D = NULL;
	lpD3DDevice = NULL;
	lpD3DViewport = NULL;
	lpDDSZBuffer = NULL;
}

RenderDevice::~RenderDevice()
{

}

void RenderDevice::SetWindowMode(int _WindowMode)
{
	WindowMode = _WindowMode;
}

LPDEVICEDESC RenderDevice::FindDevice(LPDEVICEDESC lpDesc, LPGUID lpGuid)
{
	LPDEVICEDESC desc = lpDesc;

	while (desc)
	{
		if (!memcmp(lpGuid, &desc->guid, sizeof(GUID)))
			break;

		desc = desc->lpNext;
	}

	return desc;
}

LPDEVICEDESC RenderDevice::FindBestDevice(LPDEVICEDESC lpDesc)
{
	LPDEVICEDESC desc = FindDevice(lpDesc, (LPGUID)&IID_IDirect3DHALDevice);

	if (!desc)
		desc = FindDevice(lpDesc, (LPGUID)&IID_IDirect3DMMXDevice);

	if (!desc)
		desc = FindDevice(lpDesc, (LPGUID)&IID_IDirect3DRGBDevice);

	return desc;
}

LPDEVICEDESC RenderDevice::CreateDevice()
{
	LPDEVICEDESC desc = new DEVICEDESC;
	if (!desc)
		return NULL;

	ZeroMemory(desc, sizeof(DEVICEDESC));

	return desc;
}

LPDEVICEDESC RenderDevice::CreateDevice(LPDEVICEDESC lpDesc)
{
	if (!lpDesc)
		return CreateDevice();

	LPDEVICEDESC desc = new DEVICEDESC;
	if (!desc)
		return NULL;

	ZeroMemory(desc, sizeof(DEVICEDESC));

	LPDEVICEDESC lastDesc = lpDesc;
	while (lastDesc->lpNext)
		lastDesc = lastDesc->lpNext;

	lastDesc->lpNext = desc;

	return desc;
}

// Direct3D Generation
BOOL RenderDevice::CreateD3D()
{
	// DirectDraw Interface generation
	LPDIRECTDRAW lpdd;

	//Set DirectDraw Device
	HRESULT hresult = DirectDrawCreate(NULL, &lpdd, NULL);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "DirectDrawCreate");
		return FALSE;
	}

	// DirectDraw2 Get Interface
	hresult = lpdd->QueryInterface(IID_IDirectDraw4, (LPVOID*)&lpDD);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "lpdd->QueryInterface");
		return FALSE;
	}

	// DirectDraw Interfaces removed
	lpdd->Release();


	// Direct3D Get Interface
	hresult = lpDD->QueryInterface(IID_IDirect3D3, (LPVOID*)&lpD3D);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "lpDD3->QueryInterface");
		return FALSE;
	}

	// Direct3D Device Get Interface
	hresult = lpD3D->EnumDevices(DeviceEnumCallback, (LPVOID)&lpDeviceDesc);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "lpD3D->EnumDevices");
		return FALSE;
	}

	lpD3DDeviceDesc = FindBestDevice(lpDeviceDesc);
	if (!lpD3DDeviceDesc)
		return FALSE;

	return TRUE;
}

// Direct3D Removal
void RenderDevice::ReleaseD3D()
{
	//######################################################################################
	//작 성 자 : 오 영 석
	DestroyDevice(lpDeviceDesc);
	//######################################################################################

	//######################################################################################
	//작 성 자 : 오 영 석
	ReleaseNewRenderTarget();
	//######################################################################################

	// Viewport 제거
	if (lpD3DViewport)
	{
		// Direct3D Device 에서 Viewport 제거
		lpD3DDevice->DeleteViewport(lpD3DViewport);

		lpD3DViewport->Release();
		lpD3DViewport = NULL;
	}

	// Direct3D Device 제거
	if (lpD3DDevice)
	{
		lpD3DDevice->Release();
		lpD3DDevice = NULL;
	}


	// Z-Buffer Surface 제거
	if (lpDDSZBuffer)
	{
		// Back Surface 에서 Z-Buffer Surface 제거
		if (lpDDSBack)
			lpDDSBack->DeleteAttachedSurface(0L, lpDDSZBuffer);

		lpDDSZBuffer->Release();
		lpDDSZBuffer = NULL;
	}

	//######################################################################################
	//작 성 자 : 오 영 석
	if (lpDDSBack)
	{
		lpDDSBack->Release();
		lpDDSBack = NULL;
	}
	//######################################################################################

	// Direct3D Interface 제거
	if (lpD3D)
	{
		lpD3D->Release();
		lpD3D = NULL;
	}

	// Primary Surface 제거
	if (lpDDSPrimary)
	{
		lpDDSPrimary->Release();
		lpDDSPrimary = NULL;
	}

	// DirectDraw2 Interface 제거
	if (lpDD)
	{
		// 비디오 모드 복귀
		lpDD->RestoreDisplayMode();

		lpDD->Release();
		lpDD = NULL;
	}
}

//Destroy the DirectX Device
void RenderDevice::DestroyDevice(LPDEVICEDESC lpDesc)
{
	LPDEVICEDESC desc;

	while (lpDesc->lpNext)
	{
		desc = lpDesc->lpNext;
		lpDesc->lpNext = lpDesc->lpNext->lpNext;

		delete[] desc;
	}

	delete[] lpDesc;
}

// Video mode switching (fullmode)
BOOL RenderDevice::SetDisplayMode(HWND hWnd, DWORD Width, DWORD Height, DWORD BPP)
{
	Utils_Log(LOG_DEBUG, "D3DX SetDisplayMode()  Width(%d)  Height(%d)  Color(%d)", Width, Height, BPP);

	// Set Cooperative Level
	smTextureBPP = BPP;

	if (WindowMode)
		return SetDisplayModeWin(hWnd, Width, Height, BPP);

	HRESULT hresult = lpDD->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWMODEX);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "lpDD->SetCooperativeLevel");
		return FALSE;
	}

	// 풀화면 모드로 전환
	hresult = lpDD->SetDisplayMode(Width, Height, BPP, 0, 0);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "lpDD3->SetDisplayMode");
		return FALSE;
	}

	// Primary Surface 생성
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwBackBufferCount = 1;
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_VIDEOMEMORY | DDSCAPS_3DDEVICE;

	// Primary surface 생성
	hresult = CreateSurface(&ddsd, &lpDDSPrimary, NULL);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "CreateSurface(lpDDSPrimary)");
		return FALSE;
	}

	// Back Surface 생성(?)
	DDSCAPS2 ddscaps;
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
	hresult = lpDDSPrimary->GetAttachedSurface(&ddscaps, &lpDDSBack);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "lpDDSPrimary->GetAttachedSurface");
		return FALSE;
	}

	//////////// 클리퍼 생성 ////////////////////////
	lpDD->CreateClipper(0, &lpDDClipper, NULL);
	lpDDClipper->SetHWnd(0, hWnd);
	lpDDSPrimary->SetClipper(lpDDClipper);
	lpDDClipper->Release();

	// z-buffer Surface 생성
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
	ddsd.dwWidth = Width;
	ddsd.dwHeight = Height;

	lpD3D->EnumZBufferFormats(IID_IDirect3DHALDevice, EnumZBufferCallback, (VOID *)&ddsd.ddpfPixelFormat);

	//######################################################################################
	//작 성 자 : 오 영 석
	::CopyMemory(&g_ddpfPixelFormatZ, &ddsd.ddpfPixelFormat, sizeof(g_ddpfPixelFormatZ));
	//######################################################################################

	// 하드웨어 이면 z-buffer를 비디오 메모리에 만든다.
	if (lpD3DDeviceDesc->bIsHardware)
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
	else
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_SYSTEMMEMORY;

	// Create the ZBuffer surface.
	hresult = CreateSurface(&ddsd, &lpDDSZBuffer, NULL);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "CreateSurface(lpDDSZBuffer)");
		return FALSE;
	}

	// Back Surface에 Z-buffer를 붙인다.
	hresult = lpDDSBack->AddAttachedSurface(lpDDSZBuffer);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "lpDDSBack->AddAttachedSurface");
		return FALSE;
	}

	// Direct3D Device 생성
	hresult = lpD3D->CreateDevice(lpD3DDeviceDesc->guid, lpDDSBack, &lpD3DDevice, NULL);
	if (hresult != D3D_OK)
	{
		Utils_Log(LOG_ERROR, "lpD3D->CreateDevice");
		return FALSE;
	}

	// Viewport Size Settings
	D3DRect.x1 = 0;
	D3DRect.y1 = 0;
	D3DRect.x2 = Width;
	D3DRect.y2 = Height;

	smScreenWidth = Width;
	smScreenHeight = Height;

	return CreateViewport();
}

// Video mode switching (winmode)
BOOL RenderDevice::SetDisplayModeWin(HWND hWnd, DWORD Width, DWORD Height, DWORD BPP)
{
	Utils_Log(LOG_DEBUG, "D3DX SetDisplayModeWin()  Width(%d)  Height(%d)  Color(%d)", Width, Height, BPP);

	// Set Cooperative Level
	HRESULT hresult = lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);

	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "lpDD->SetCooperativeLevel");
		return FALSE;
	}


	// Primary Surface 생성
	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd, sizeof(ddsd));

	ddsd.dwSize = sizeof(ddsd);
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
		DDSCAPS_3DDEVICE;

	// Primary surface 생성
	hresult = CreateSurface(&ddsd, &lpDDSPrimary, NULL);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "CreateSurface(lpDDSPrimary)");
		return FALSE;
	}


	int w, h;
	RECT lpRect;
	GetWindowRect(GetDesktopWindow(), &lpRect);
	w = lpRect.right - lpRect.left;
	h = lpRect.bottom - lpRect.top;

	// 백 버퍼 1 생성
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE | DDSCAPS_VIDEOMEMORY;
	ddsd.dwWidth = w;
	ddsd.dwHeight = h;
	CreateSurface(&ddsd, &lpDDSBack, NULL);

	lpDD->CreateClipper(0, &lpDDClipper, NULL);
	lpDDClipper->SetHWnd(0, hWnd);
	lpDDSPrimary->SetClipper(lpDDClipper);
	lpDDClipper->Release();


	DDPIXELFORMAT	ddpx;
	// z-buffer Surface 생성
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS |
		DDSD_WIDTH |
		DDSD_HEIGHT |
		DDSD_PIXELFORMAT;

	ddsd.dwWidth = w;
	ddsd.dwHeight = h;

	lpD3D->EnumZBufferFormats(lpD3DDeviceDesc->guid, EnumZBufferCallback, (VOID *)&ddpx);

	memcpy(&ddsd.ddpfPixelFormat, &ddpx, sizeof(DDPIXELFORMAT));

	//######################################################################################
	//작 성 자 : 오 영 석
	::CopyMemory(&g_ddpfPixelFormatZ, &ddsd.ddpfPixelFormat, sizeof(g_ddpfPixelFormatZ));
	//######################################################################################

	// 하드웨어 이면 z-buffer를 비디오 메모리에 만든다.
	if (lpD3DDeviceDesc->bIsHardware)
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_VIDEOMEMORY;
	else
		ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER | DDSCAPS_SYSTEMMEMORY;

	// Create the ZBuffer surface.
	hresult = CreateSurface(&ddsd, &lpDDSZBuffer, NULL);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "CreateSurface(lpDDSZBuffer)");
		return FALSE;
	}

	// Back Surface에 Z-buffer를 붙인다.
	hresult = lpDDSBack->AddAttachedSurface(lpDDSZBuffer);
	if (hresult != DD_OK)
	{
		Utils_Log(LOG_ERROR, "lpDDSBack->AddAttachedSurface");
		return FALSE;
	}

	// Direct3D Device 생성
	hresult = lpD3D->CreateDevice(lpD3DDeviceDesc->guid,
		lpDDSBack,
		&lpD3DDevice,
		NULL);
	if (hresult != D3D_OK)
	{
		Utils_Log(LOG_ERROR, "lpD3D->CreateDevice");
		return FALSE;
	}

	// Viewport Size Settings
	D3DRect.x1 = 0;
	D3DRect.y1 = 0;
	D3DRect.x2 = w;
	D3DRect.y2 = h;

	smScreenWidth = Width;
	smScreenHeight = Height;

	return CreateViewport();
}

// Viewport Generation
BOOL RenderDevice::CreateViewport()
{
	// Viewport 생성
	HRESULT hresult = lpD3D->CreateViewport(&lpD3DViewport, NULL);
	if (hresult != D3D_OK)
	{
		Utils_Log(LOG_ERROR, "Failed to set CreateViewport()");
		return FALSE;
	}

	// Direct3D Device 에 Viewport 추가
	hresult = lpD3DDevice->AddViewport(lpD3DViewport);
	if (hresult != D3D_OK)
	{
		Utils_Log(LOG_ERROR, "Failed to set AddViewport()");
		return FALSE;
	}

	D3DVIEWPORT2 Viewdata;
	ZeroMemory(&Viewdata, sizeof(D3DVIEWPORT2));

	Viewdata.dwSize = sizeof(Viewdata);
	Viewdata.dwX = D3DRect.x1;
	Viewdata.dwY = D3DRect.y1;

	Viewdata.dwWidth = D3DRect.x2;
	Viewdata.dwHeight = D3DRect.y2;
	Viewdata.dvClipWidth = 2.0f;
	Viewdata.dvClipHeight = (float)(D3DRect.y2 * 2.0 / D3DRect.x2);
	Viewdata.dvClipX = -1.0f;
	Viewdata.dvClipY = Viewdata.dvClipHeight / 2.0f;
	Viewdata.dvMinZ = 0.0f;
	Viewdata.dvMaxZ = 1.0f;

	//viewport.dvMinZ         = 0.0f;
	//viewport.dvMaxZ         = 1.0f;

	// lpD3DViewport2 설정
	hresult = lpD3DViewport->SetViewport2(&Viewdata);
	if (hresult != D3D_OK)
	{
		Utils_Log(LOG_ERROR, "Failed to set SetViewport2()");
		return FALSE;
	}

	// 현제 Viewport를 lpD3DViewport2로 설정
	hresult = lpD3DDevice->SetCurrentViewport(lpD3DViewport);
	if (hresult != D3D_OK)
	{
		Utils_Log(LOG_ERROR, "Failed to set SetCurrentViewport()");
		return FALSE;
	}
	//######################################################################################
	//작 성 자 : 오 영 석
	if (g_IsCreateFilterEffect)
		CreateNewRenderTarget();
	//######################################################################################

	return TRUE;
}

// Initialze the Render
void RenderDevice::InitRender()
{
	// Turn on Z-buffering
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
	//lpD3DDevice->SetRenderState( D3DRENDERSTATE_ZENABLE, D3DZB_USEW );//TRUE );


	// null out the texture handle
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);

	// turn on dithering
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);

	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREADDRESS, D3DTADDRESS_WRAP);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);

	// D3DFILTER_LINEAR
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR);

	lpD3DDevice->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

	lpD3DDevice->SetRenderState(D3DRENDERSTATE_TEXTUREMAPBLEND, D3DTBLEND_MODULATE);

	lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);

	smRender.AlphaTestDepth = 60;
	smRender.dwMatDispMask = sMATS_SCRIPT_NOTVIEW;
	smRender.DeviceRendMode = TRUE;
	smRender.ZWriteAuto = FALSE;
}

// Page-flipping
int RenderDevice::Flip()
{
	//동영상 재생
	if (ParkPlaying && (smFlipCount & 1) == 0)
	{
		updateFrameWin_Video();
		return TRUE;
	}

	if (WindowMode || (hFocusWnd && (smFlipCount & 1) == 0))
	{
		updateFrameWin();
		return TRUE;
	}


	HRESULT hresult = lpDDSPrimary->Flip(NULL, DDFLIP_WAIT);
	if (hresult == DDERR_SURFACELOST)
	{
		lpDDSPrimary->Restore();
		return FALSE;
	}
	smFlipCount++;			//플리핑 카운터

	return TRUE;
}

void RenderDevice::updateFrameWin_Video()
{
	RECT                rcRect;
	RECT                rcRect1;
	RECT                rcRect2;
	RECT                rcRect3;
	RECT                rcRect4;

	RECT                destRect;
	RECT                destRect1;
	RECT                destRect2;
	RECT                destRect3;
	RECT                destRect4;
	HRESULT             ddrval;
	POINT				pt;

	GetClientRect(hwnd, &destRect);

	pt.x = pt.y = 0;
	ClientToScreen(hwnd, &pt);
	OffsetRect(&destRect, pt.x, pt.y);


	//////////////////////////////////////////////////////////////
	// 두개의 페이지 전환이 이루어 지는 곳 
	// Blt() 함수가 실제로 비트맵을 그리는 함수

	rcRect.left = 0;
	rcRect.right = smScreenWidth;
	rcRect.top = 0;
	rcRect.bottom = smScreenHeight;

	destRect1.left = 0;
	destRect1.right = smScreenWidth;
	destRect1.top = 0;
	destRect1.bottom = ParkPlayRect.top;

	destRect2.left = 0;
	destRect2.right = ParkPlayRect.left;
	destRect2.top = ParkPlayRect.top;
	destRect2.bottom = ParkPlayRect.bottom;

	destRect3.left = ParkPlayRect.right;
	destRect3.right = smScreenWidth;
	destRect3.top = ParkPlayRect.top;
	destRect3.bottom = ParkPlayRect.bottom;

	destRect4.left = 0;
	destRect4.right = smScreenWidth;
	destRect4.top = ParkPlayRect.bottom;
	destRect4.bottom = smScreenHeight;


	rcRect1.left = 0;
	rcRect1.right = smScreenWidth;
	rcRect1.top = 0;
	rcRect1.bottom = ParkPlayRect.top;


	rcRect2.left = 0;
	rcRect2.right = ParkPlayRect.left;
	rcRect2.top = ParkPlayRect.top;
	rcRect2.bottom = ParkPlayRect.bottom;


	rcRect3.left = ParkPlayRect.right;
	rcRect3.right = smScreenWidth;
	rcRect3.top = ParkPlayRect.top;
	rcRect3.bottom = ParkPlayRect.bottom;

	rcRect4.left = 0;
	rcRect4.right = smScreenWidth;
	rcRect4.top = ParkPlayRect.bottom;
	rcRect4.bottom = smScreenHeight;


	while (1)
	{
		ddrval = Blt(lpDDSPrimary, &destRect1, lpDDSBack, &rcRect1, NULL, NULL);
		ddrval = Blt(lpDDSPrimary, &destRect2, lpDDSBack, &rcRect2, NULL, NULL);
		ddrval = Blt(lpDDSPrimary, &destRect3, lpDDSBack, &rcRect3, NULL, NULL);
		ddrval = Blt(lpDDSPrimary, &destRect4, lpDDSBack, &rcRect4, NULL, NULL);
		if (ddrval == DD_OK) break;
		if (ddrval == DDERR_SURFACELOST)
		{
			//		ddrval = restoreAll();
			if (ddrval != DD_OK)
				return;
		}
		if (ddrval != DDERR_WASSTILLDRAWING)
			break;

	}

}

void RenderDevice::updateFrameWin()
{
	RECT                rcRect;
	RECT                destRect;
	HRESULT             ddrval;
	POINT				pt;

	GetClientRect(hwnd, &destRect);

	pt.x = pt.y = 0;
	ClientToScreen(hwnd, &pt);
	OffsetRect(&destRect, pt.x, pt.y);
	//////////////////////////////////////////////////////////////
	// Which consists of two pages where conversions
	// Blt() function is the function actually draws bitmaps

	rcRect.left = 0;
	rcRect.right = smScreenWidth;
	rcRect.top = 0;
	rcRect.bottom = smScreenHeight;

	while (1)
	{
		ddrval = Blt(lpDDSPrimary, &destRect, lpDDSBack, &rcRect, NULL, NULL);
		if (ddrval == DD_OK) 
			break;

		if (ddrval == DDERR_SURFACELOST)
		{
			if (ddrval != DD_OK)
				return;
		}
		if (ddrval != DDERR_WASSTILLDRAWING)
			break;

	}
}

void RenderDevice::ClearViewport(DWORD flags)
{
	lpD3DViewport->Clear2(1UL, &renderDevice.D3DRect, flags, smBackColor, 1, 0L);
}

BOOL RenderDevice::IsDevice()
{
	if (lpD3DDevice)
		return TRUE;

	return FALSE;
}

void RenderDevice::SetRenderState(_D3DRENDERSTATETYPE stateType, DWORD value)
{
	lpD3DDevice->SetRenderState(stateType, value);
}

void RenderDevice::SetTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value)
{
	lpD3DDevice->SetTextureStageState(stage, type, value);
}

HRESULT RenderDevice::EnumTextureFormats(LPD3DENUMPIXELFORMATSCALLBACK Textures, LPVOID TexturePixelFormat)
{
	return lpD3DDevice->EnumTextureFormats(Textures, TexturePixelFormat);
}

HRESULT RenderDevice::SetTransform(D3DTRANSFORMSTATETYPE type, LPD3DMATRIX matrix)
{
	return lpD3DDevice->SetTransform(type, matrix);
}

HRESULT  RenderDevice::SetTexture(DWORD sampler, DRZTEXTURE2 texture)
{
	return lpD3DDevice->SetTexture(sampler, texture);
}

HRESULT RenderDevice::SetRenderTarget(DIRECTDRAWSURFACE pRenderTarget, DWORD RenderTargetIndex)
{
	return lpD3DDevice->SetRenderTarget(pRenderTarget, RenderTargetIndex);
}

HRESULT RenderDevice::GetRenderTarget(DIRECTDRAWSURFACE* renderTarget)
{
	return lpD3DDevice->GetRenderTarget(renderTarget);

}

HRESULT RenderDevice::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, DWORD VertexTypeDesc, LPVOID Vertices, DWORD VertexCount, DWORD Flags)
{
	return lpD3DDevice->DrawPrimitive(PrimitiveType, VertexTypeDesc, Vertices, VertexCount, Flags);
}

HRESULT RenderDevice::Blt(DIRECTDRAWSURFACE targetSurface, LPRECT lpDestRect, DIRECTDRAWSURFACE srcSurface, LPRECT srcRect, DWORD dwFlags, LPDDBLTFX  lpDDBltFx)
{
	HRESULT hr = targetSurface->Blt(lpDestRect, srcSurface, srcRect, dwFlags, lpDDBltFx);
	
	if (FAILED(hr))
		Utils_Log(LOG_ERROR, "DirectX Error - Blt() failed");

	return hr;
}

HRESULT RenderDevice::BltFast(DIRECTDRAWSURFACE targetSurface, DWORD dwX, DWORD dwY, DIRECTDRAWSURFACE srcSurface, LPRECT srcRect, DWORD dwFlags)
{
	HRESULT hr = targetSurface->BltFast(dwX, dwY, srcSurface, srcRect, dwFlags);
	/*
	if (FAILED(hr))
		Utils_Log(LOG_ERROR, "DirectX Error - BltFast() failed");
	*/
	return hr;
}

HRESULT RenderDevice::CreateSurface(LPDDSURFACEDESC2 SurfaceDesc, DIRECTDRAWSURFACE* surface, IUnknown* UnkPointer)
{
	return lpDD->CreateSurface(SurfaceDesc, surface, UnkPointer);
}

void RenderDevice::BeginScene()
{
	lpD3DDevice->BeginScene();
}

void RenderDevice::EndScene()
{
	lpD3DDevice->EndScene();
}

