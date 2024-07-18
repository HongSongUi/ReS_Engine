#pragma once

#include <map>
#include "X_Header.h"
#include "X_Shader.h"
class ShaderManager:public X_Singleton<ShaderManager>
{
public:
	ID3D11Device* _Device = nullptr;
	ID3D11DeviceContext* _Context = nullptr;
private:
	friend class X_Singleton<ShaderManager>;
	std::map<std::wstring, X_Shader*> _List;
public:
	void SetDevice(ID3D11Device*, ID3D11DeviceContext*);
	X_Shader* Load(std::wstring);

	bool Release();
private:
	ShaderManager() {};
public:
	~ShaderManager();
};
#define ShaderMgr ShaderManager::GetInstance()

