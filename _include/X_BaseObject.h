#pragma once


#include <fstream>
#include "X_Rect.h"
#include "X_Vertex.h"
#include "X_Math.h"
class X_BaseObject
{

public:
	ID3D11Device* _Device;
	ID3D11DeviceContext* _Context;
	RECT _ClientRt;
	X_Vertex _ObjVertex;

	X_Texture* _Mask = nullptr;
	X_Texture* _Texture;
	X_Shader* _Shader;

	std::vector<vertex> _VertexList;
	std::vector<vertex> _InitVertexList;
	std::vector<DWORD> _IndexList;

public:
	float _Mass;
	float _Speed;
	bool _Inverse = true;
public:
	X_BaseObject() {
		SetListSize();
	};
	virtual ~X_BaseObject() {};
protected:
	virtual HRESULT ShaderCompile(std::wstring ShaderFile);
	virtual HRESULT LoadTexture(std::wstring TextureFile);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool PreRender();
	virtual bool PostRender();
	void UpdateVertexList();
	virtual void UpdatePosition() {};
	virtual void SetMatrix(H_Matrix* world, H_Matrix* view, H_Matrix* proj);
public:
	virtual void SetPhysics() {};
	virtual void SetPosition(H_Vector2 pos) {};
	void SetMask(std::wstring MaskFile);
	void SetClientSize(RECT clientRt);
	virtual void SetVertexList();
	virtual void SetIndexList();
	virtual void SetListSize();
	void SetSRV(ID3D11ShaderResourceView* srv);
public:
	virtual bool SetData(ID3D11Device* device, ID3D11DeviceContext* context, RECT clientRt);
	virtual bool Load(std::wstring ShaderFile, std::wstring TextureFile);
	virtual bool CreateVertex();
};

