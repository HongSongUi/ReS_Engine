#pragma once
#include "Device.h"
class X_Shader 
{
	ID3D11Device* _Device;
	ID3D11DeviceContext* _Context;
public:
	ID3D11VertexShader* _VShader;
	ID3D11PixelShader* _PShader;
	ID3DBlob* _VsCode;
	ID3DBlob* _PsCode;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	HRESULT Load(std::wstring);
	void SetDevice(ID3D11Device*, ID3D11DeviceContext*);
};

