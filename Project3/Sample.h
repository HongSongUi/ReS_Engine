#pragma once
#include "GameCore.h"
#include "TitleScene.h"
class Sample :public GameCore
{
	TitleScene Test;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};