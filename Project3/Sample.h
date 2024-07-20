#pragma once
#include "GameCore.h"
class Sample :public GameCore
{

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};