#pragma once
#include "Device.h"
class RenderToTexture
{
public:
	ID3D11RenderTargetView*			_RenderTargetView;
	ID3D11DepthStencilView*			_DepthStencilView;
	ID3D11ShaderResourceView*		_ShaderResourceView;
	ID3D11ShaderResourceView*		_DepthSRV;
	ID3D11Texture2D*				_Texture2D;
	D3D11_DEPTH_STENCIL_VIEW_DESC	_DepthStencilDesc;
	D3D11_TEXTURE2D_DESC	_TextureDesc;
	D3D11_VIEWPORT _ViewPort;

	ID3D11RenderTargetView* _OldRenderTarget;
	ID3D11DepthStencilView* _OldDepthStencil;
	D3D11_VIEWPORT _OldViewPort[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
public:
	bool Create(ID3D11Device* _Device, FLOAT width = 1000.0f, FLOAT height = 700.0f);
	bool Begin( ID3D11DeviceContext* _Context);
	void End( ID3D11DeviceContext* _Context);
	bool Release();
};

