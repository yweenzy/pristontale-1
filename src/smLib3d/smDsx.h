#ifndef _SMDSX_H_
#define _SMDSX_H_

#define WINMODE			01

#include "..\Dependency\\DirectX8\\DXSDK\\include\\ddraw.h"
#include "..\Dependency\\DirectX8\\DXSDK\\include\\d3d.h"


/***************************************
* Direct3D Structures for initialization
***************************************/

// Direct3D Device Information
// Use the yijeongbo to create a IDirect3DDevice2.
typedef struct _DEVICEDESC
{
	// Device Info
	GUID  guid;                 // GUID
	char  szName[256];          // 이름
	char  szDesc[256];          // 설명
	BOOL  bIsHardware;          // 하드웨어 드라이브 인가?

	// Device Caps
	D3DDEVICEDESC   Desc;
	_DEVICEDESC		*lpNext;
} DEVICEDESC, *LPDEVICEDESC;

typedef struct
{
	float r, g, b, a;
} COLORVALUE, *LPCOLORVALUE;

typedef struct
{
	float	x, y, z;
} VECTOR, *LPVECTOR;

typedef struct
{
	float   tu, tv;
} TVERTEX, *LPTVERTEX;

#define DIRECTDRAWSURFACE	LPDIRECTDRAWSURFACE4
#define DRZTEXTURE2			LPDIRECT3DTEXTURE2

//The RenderDevice Class
class RenderDevice
{
public:
	RenderDevice();

	~RenderDevice();

	// Direct3D Generation
	BOOL CreateD3D();

	// Direct3D Removal
	void ReleaseD3D();

	// Video mode switching
	BOOL SetDisplayMode(HWND hWnd, DWORD Width, DWORD Height, DWORD BPP);

	// Render initializing
	void InitRender();

	LPDEVICEDESC CreateDevice();
	LPDEVICEDESC CreateDevice(LPDEVICEDESC lpDesc);

	// Page-flipping
	int Flip();
	int GetFlipCount() { return smFlipCount; }

	BOOL IsDevice();

	void SetRenderState(_D3DRENDERSTATETYPE stateType, DWORD value);

	void SetTextureStageState(DWORD stage, D3DTEXTURESTAGESTATETYPE type, DWORD value);

	HRESULT SetTexture(DWORD sampler, DRZTEXTURE2 texture);

	HRESULT DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, DWORD VertexTypeDesc, LPVOID Vertices, DWORD VertexCount, DWORD Flags);

	HRESULT SetRenderTarget(DIRECTDRAWSURFACE pRenderTarget, DWORD RenderTargetIndex);

	HRESULT GetRenderTarget(DIRECTDRAWSURFACE* renderTarget);

	HRESULT EnumTextureFormats(LPD3DENUMPIXELFORMATSCALLBACK Textures, LPVOID TexturePixelFormat);

	HRESULT SetTransform(D3DTRANSFORMSTATETYPE type, LPD3DMATRIX matrix);

	HRESULT Blt(DIRECTDRAWSURFACE targetSurface, LPRECT lpDestRect, DIRECTDRAWSURFACE srcSurface, LPRECT srcRect, DWORD dwFlags, LPDDBLTFX  lpDDBltFx);

	HRESULT BltFast(DIRECTDRAWSURFACE targetSurface, DWORD dwX, DWORD dwY, DIRECTDRAWSURFACE srcSurface, LPRECT srcRect, DWORD dwFlags);

	HRESULT CreateSurface(LPDDSURFACEDESC2 SurfaceDesc, DIRECTDRAWSURFACE* surface, IUnknown* UnkPointer);

	void ClearViewport(DWORD flags);

	void BeginScene();

	void EndScene();

	int GetWindowMode() { return WindowMode; }
	void SetWindowMode(int _WindowMode);

	int GetTextureBPP() { return smTextureBPP; }

	int GetScreenWidth() { return smScreenWidth; }

	int GetScreenHeight() { return smScreenHeight; }

	BOOL GetDeviceDesc_IsHardware() { return lpD3DDeviceDesc->bIsHardware; }
	DWORD GetDeviceDesc_MaxTextureWidth() { return lpD3DDeviceDesc->Desc.dwMaxTextureWidth; }
	DWORD GetDeviceDesc_MaxTextureHeight() { return lpD3DDeviceDesc->Desc.dwMaxTextureHeight; }

	DWORD GetDeviceDesc_TextureFilterCaps() { return lpD3DDeviceDesc->Desc.dpcTriCaps.dwTextureFilterCaps; }
	DWORD GetDeviceDesc_TextureCaps() { return lpD3DDeviceDesc->Desc.dpcTriCaps.dwTextureCaps; }
	DWORD GetDeviceDesc_RasterCaps() { return lpD3DDeviceDesc->Desc.dpcTriCaps.dwRasterCaps; }

private:
	LPDEVICEDESC FindBestDevice(LPDEVICEDESC lpDesc);
	LPDEVICEDESC FindDevice(LPDEVICEDESC lpDesc, LPGUID lpGuid);

	void RenderDevice::DestroyDevice(LPDEVICEDESC lpDesc);

	BOOL SetDisplayModeWin(HWND hWnd, DWORD Width, DWORD Height, DWORD BPP);

	BOOL CreateViewport();

	void updateFrameWin_Video();

	void updateFrameWin();

private:

	int smFlipCount;					//Flipping counter

	int WindowMode;
	int	smTextureBPP;

	int smScreenWidth;
	int smScreenHeight;

	// Direct3D
	LPDIRECT3D3             lpD3D;
	DIRECTDRAWSURFACE		lpDDSZBuffer;
	LPDIRECT3DVIEWPORT3     lpD3DViewport;
	LPDEVICEDESC			lpD3DDeviceDesc;
	LPDIRECT3DDEVICE3       lpD3DDevice;

public:

	// DirectDraw          
	LPDIRECTDRAW4           lpDD;
	DIRECTDRAWSURFACE		lpDDSPrimary;
	DIRECTDRAWSURFACE		lpDDSBack;
	LPDIRECTDRAWCLIPPER     lpDDClipper;

	D3DRECT                 D3DRect;
};


#endif

//do the render Device public
extern RenderDevice				renderDevice;