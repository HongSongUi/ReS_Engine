#pragma once
#include "Device.h"
class DxState
{
public:
	static ID3D11SamplerState* _DefaultSS;
	static ID3D11BlendState* _DefaultBS;
	static ID3D11RasterizerState* _DefaultRSWireFrame;
	static ID3D11RasterizerState* _DefaultRSSolid;
	static ID3D11DepthStencilState* _DefaultDepthStencil;
	static HRESULT SetState(ID3D11Device* );
	static bool Release();
};

