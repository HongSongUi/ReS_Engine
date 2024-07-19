#include "BaseObject.h"
#include "ShaderManager.h"
#include "TextureManager.h"
void BaseObject::SetListSize()
{
    VertexList.resize(4);
    IndexList.resize(6);
}

bool BaseObject::Init()
{
    return true;
}

bool BaseObject::Frame()
{
    return true;
}

bool BaseObject::Render()
{
    Mesh.Render();
    return true;
}

bool BaseObject::Release()
{
    Mesh.Release();
    return true;
}

bool BaseObject::PreRender()
{
    Mesh.PreRender();
    return true;
}

bool BaseObject::PostRender()
{
    Mesh.PostRender();
    return true;
}

void BaseObject::SetVertexList()
{
    VertexList[0].Position = { -1.0f,1.0f,0.0f };
    VertexList[0].Color = { 1.0f,1.0f,1.0f,1.0f };
    VertexList[1].Position = { 1.0f,1.0f,0.0f };
    VertexList[1].Color = { 0.0f,1.0f,1.0f,1.0f };
    VertexList[2].Position = { -1.0f,-1.0f,0.0f };
    VertexList[2].Color = { 1.0f,1.0f,0.0f,1.0f };
    VertexList[3].Position = { 1.0f,-1.0f,0.0f };
    VertexList[3].Color = { 1.0f,1.0f,1.0f,1.0f };
    VertexList[0].Texture = { 0.0f, 0.0f };
    VertexList[1].Texture = { 1.0f, 0.0f };
    VertexList[2].Texture = { 0.0f, 1.0f };
    VertexList[3].Texture = { 1.0f, 1.0f };
}

void BaseObject::SetIndexList()
{
    IndexList[0] = 0;
    IndexList[1] = 1;
    IndexList[2] = 2;
    IndexList[3] = 2;
    IndexList[4] = 1;
    IndexList[5] = 3;
}

bool BaseObject::SetData(ID3D11Device* device, ID3D11DeviceContext* context, RECT clientRt)
{
    D3D11Device = device;
    D3D11Context = context;
    ClientRect = clientRt;
    return true;
}

bool BaseObject::Load(std::wstring ShaderFileName, std::wstring TextureFileName)
{
    if (FAILED(ShaderCompile(ShaderFileName)))
    {
        return false;
    }
    if (FAILED(LoadTexture(TextureFileName)))
    {
        return false;
    }
    return true;
}

bool BaseObject::Load(std::wstring ShaderFileName, std::wstring TextureFileName, std::wstring MaskFile)
{
    if (Load(ShaderFileName, TextureFileName) == false)
    {
        return false;
    }
    MaskTexture = TextureMgr.Load(MaskFile);
    if (MaskTexture == nullptr)
    {
        return false;
    }
    return true;
}

HRESULT BaseObject::ShaderCompile(std::wstring ShaderFileName)
{
    HRESULT hr;
    ShaderFile = ShaderMgr.Load(ShaderFileName);
    if (ShaderFile != nullptr) 
    {
        hr = S_OK;
    }
    else
    {
        hr = S_FALSE;
    }
    return hr;
}

HRESULT BaseObject::LoadTexture(std::wstring TextureFileName)
{
    HRESULT hr;
    TextureFile = TextureMgr.Load(TextureFileName);
    if (TextureFile != nullptr) 
    {
        Mesh.TextureSRV = TextureFile->TextureSRV;
        hr = S_OK;
    }
    else 
    {
        hr = S_FALSE;
    }
    return hr;
}
