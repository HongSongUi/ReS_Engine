#pragma once
#include "X_Header.h"
#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib,"fmod_vc.lib")

class X_Sound
{
public:
	FMOD::System* _System = nullptr;
	FMOD::Sound* _Sound = nullptr;
	FMOD::Channel* _Channel = nullptr;
	float _Volume;
	std::wstring _Buffer;
public:
	void Pause();
	void VolumeAdj(bool state);
	bool Play(bool loop = false);
	bool PlayEffect(float volume,bool loop = false);
	void Stop();
	void SetLoop(bool loop = false);
	bool IsPlay();
	void SetVolume(float volume);
public:
	FMOD_RESULT Load(FMOD::System* system,std::wstring filename);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

