#pragma once
#include <map>
#include "Object2D.h"
struct MugShot {
	float left;
	float top;
	float right;
	float bottom;
};
class StageUI : public Object2D
{
	class TextLoader* Loader;
	struct MugShot Mug;
	std::vector<Rect> BossImgList;
	std::map<std::wstring, std::vector<Rect>> FileList;
	int Index = 0;
public:
	bool ChangeScene = false;
	bool UiChange = false;
public:
	bool Init();
	bool Frame();
	std::vector<Rect> FindSprite(std::wstring name);
	void TextInit();
	void ChangeUi(bool Change, std::wstring name);
};

