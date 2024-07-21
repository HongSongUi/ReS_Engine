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

	class Texture* MaskTexture = nullptr;
	class Texture* TextureFile;
	class Shader* ShaderFile;

	std::vector<Vertex> VertexList;
	std::vector<Vertex> InitVertexList;
	std::vector<unsigned int> IndexList;

	//Matrix _worldMat;
	//Matrix _viewMat;
	//Matrix _projMat;

	//Vector4 _lightDir;
	//Vector4 _lightPos;
	//Vector4 _eyeDir;
	//Vector4 _eyePos;

public:
	float Mass;
	float Speed;
	bool Inverse = true;
public:
	BaseObject() {
		SetListSize();
	};
	virtual ~BaseObject() {};
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
	virtual void SetMatrix(Matrix* world, Matrix* view, Matrix* proj) {};
	virtual void SetLight(Vector4* lightDir, Vector4* lightPos, Vector4* eyePos, Vector4* eyeDir) {};
public:
	virtual void SetPhysics() {};
	virtual void SetPosition(Vector2 pos) {};
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

