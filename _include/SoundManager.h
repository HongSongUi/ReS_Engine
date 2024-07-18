#pragma once
#include <map>
#include <list>
#include "X_Sound.h"
class SoundManager:public X_Singleton<SoundManager>
{
public:
	FMOD::System* _System;
	std::list<std::wstring> fileList;
private:
	friend class X_Singleton<SoundManager>;
	std::map<std::wstring, X_Sound*> DataList;
public:
	X_Sound* Load(std::wstring filename);
	X_Sound* Find(std::wstring name);
	void LoadDir(std::wstring path);
	void LoadAll(std::wstring path);
	std::wstring GetSplitName(std::wstring path);
public:
	bool Init();
	bool Frame();
	bool Release();
private:
	SoundManager();
public:
	~SoundManager();
};

#define SoundMgr SoundManager::GetInstance()