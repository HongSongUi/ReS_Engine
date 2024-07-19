#pragma once
#include "Collision.h"
#include "ObjectMesh.h"
#include "ReSUtility.h"
class BaseObject
{
public:
	ID3D11Device* D3D11Device;
	ID3D11DeviceContext* D3D11Context;
	RECT ClientRect;
	ObjectMesh Mesh;

	class Texture*	MaskTexture = nullptr;
	class Texture*	TextureFile;
	class Shader*	ShaderFile;

	std::vector<Vertex> VertexList;
	std::vector<Vertex> InitVertexList;
	std::vector<unsigned int> IndexList;
public:
	BaseObject() {
		SetListSize();
	};
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool PreRender();
	virtual bool PostRender();
	virtual void SetVertexList();
	virtual void SetIndexList();
	virtual void SetListSize();
public:
	virtual bool SetData(ID3D11Device* device, ID3D11DeviceContext* context, RECT clientRt);
	virtual bool Load(std::wstring ShaderFileName, std::wstring TextureFileName);
	virtual bool Load(std::wstring ShaderFileName, std::wstring TextureFileName, std::wstring MaskFile);
protected:
	virtual HRESULT ShaderCompile(std::wstring ShaderFileName);
	virtual HRESULT LoadTexture(std::wstring TextureFileName);
};

