#pragma once
#include "X_Header.h"
#include <d3dcompiler.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")
class Device
{
public:

	ID3D11Device* _p3dDevice = nullptr;
	ID3D11DeviceContext* _p3dContext = nullptr;
	IDXGIFactory* _pGIFactory = nullptr;
	IDXGISwapChain* _pSwapChain = nullptr;
	ID3D11RenderTargetView* _pRenderTargetView = nullptr;
	ID3D11DepthStencilView* _pDepthStencilView = nullptr;
	D3D11_VIEWPORT _ViewPort;
private:
	RECT _ClientRt;
	HWND _Hwnd;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool PreRender();
	bool PostRender();
	bool Release();
public:
	HRESULT CreateDevice();
	HRESULT CreateFactory();
	HRESULT CreateSwapChain();
	HRESULT CreateRenderTargetView();
	HRESULT ResizeWindow(UINT width, UINT height);
	HRESULT CreateDepthStencilView();
	void	CreateViewPort();
	void	SetWindowData(RECT ClientRt, HWND Hwnd);
};

