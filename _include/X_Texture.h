#pragma once
#include "X_Header.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#ifdef _DEBUG
#pragma comment(lib, "DirectXTK_D.lib")
#else
#pragma comment(lib, "DirectXTK_R.lib")
#endif

class X_Texture
{
public:
	ID3D11Texture2D* _Texture = nullptr;
	ID3D11ShaderResourceView* _pTextureSRV = nullptr;
	D3D11_TEXTURE2D_DESC		_Desc;
public:
	HRESULT Load(ID3D11Device* , ID3D11DeviceContext* , std::wstring );
	void Apply(ID3D11DeviceContext* , UINT iSlot = 0);
	bool Release();
}; 

