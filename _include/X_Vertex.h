#pragma once

#include "Device.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "X_Math.h"
struct vertex {
	H_Vector3 pos;
	H_Vector3 nor;
	H_Vector4 col;
	H_Vector2 tex;
	vertex() {};
	vertex(H_Vector3 p, H_Vector4 c, H_Vector2 t) {
		pos = p;
		col = c;
		tex = t;
	}
	vertex(H_Vector3 p, H_Vector3 n, H_Vector4 c, H_Vector2 t) {
		pos = p;
		nor = n;
		col = c;
		tex = t;
	}
	
};
struct Constant_Buffer {
	H_Matrix WorldMat;
	H_Matrix ViewMat;
	H_Matrix ProjMat;
};

struct IW_VERTEX {
	H_Vector4 i;
	H_Vector4 w;
	IW_VERTEX() {}
	IW_VERTEX(H_Vector4 index, H_Vector4 weight) {
		i = index;
		w = weight;
	}
};
struct VS_CONSTANT_BONE_BUFFER {
	H_Matrix _BoneMat[255];
};

class X_Vertex
{
protected:
	std::vector<vertex> _VertexList;
	std::vector<DWORD> _IndexList;
	ID3D11Device* _Device;
	ID3D11DeviceContext* _Context;

public:
	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
	H_Matrix _WorldMat;
	H_Matrix _ViewMat;
	H_Matrix _ProjMat;
public:
	ID3D11Buffer* _VertexBuffer;
	ID3D11Buffer* _IndexBuffer;
	ID3D11Buffer* _ConstantBuffer;
	Constant_Buffer _ConstBufferData;
	ID3D11InputLayout* _InputLayout;
	X_Shader* _Shader;
	X_Texture* _Texture;
public:
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateInputLayout();
	virtual HRESULT CreateConstantBuffer();
public:
	void SetDevice(ID3D11Device* device, ID3D11DeviceContext* context);
	bool Create();
	void UpdateVertexBuffer();
	void SetShader(X_Shader* shader);
	void SetTexture(X_Texture* texture);
	void SetVertexList(std::vector<vertex> list);
	void SetIndexList(std::vector<DWORD> list);
	void CreateConstantData();
	void SetMatrix(H_Matrix* world, H_Matrix* view, H_Matrix* proj);
	void UpdateConstBuffer();
	ID3D11Buffer* CreateSubBuffer(void* DataAddress, UINT VertexCount, UINT VertexSize);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool PreRender();
	virtual bool PostRender();
};

