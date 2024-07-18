#pragma once
#include <map>
#include "X_Texture.h"
class TextureManager : public X_Singleton<TextureManager>
{
public:
	ID3D11Device* _Device = nullptr;
	ID3D11DeviceContext* _Context = nullptr;
private:
	friend class X_Singleton<TextureManager>;
	std::map<std::wstring, X_Texture*> _DataList;
public:
	X_Texture* Load(std::wstring name);
	X_Texture* Find(std::wstring name);
	std::wstring GetSplitName(std::wstring path);

	bool Release();
	void SetDevice(ID3D11Device*, ID3D11DeviceContext*);
private:
	TextureManager() {};
public:
	~TextureManager();
};
#define TextureMgr TextureManager::GetInstance()

