#pragma once
#include <vector>
#include "GameCore.h"
class Sample :public GameCore
{
	class TitleScene* TitleStage;
	class StageScene* SelectStage;
	class BossIntroScene* IntroScene;
	std::vector<class Scene*>  SceneList;
	int SceneIndex = 0;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};