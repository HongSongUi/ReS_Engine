#pragma once
#include "GameCore.h"
#include "Title.h"
class Sample :public GameCore
{
	Title Test;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};