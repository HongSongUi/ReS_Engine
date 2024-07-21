#pragma once
#include <map>
#include "Object2D.h"
#include "TextLoader.h"
#include <X_Rect.h>
struct UI
{
	float left;
	float top;
	float right;
	float bottom;
};
class TitleUI : public Object2D
{
	class GameSound* SelectSound;
	class GameSound* ChooseSound;
	TextLoader Loader;
	UI InGameUI;
	std::vector<Rect> UIList;
	std::map<std::wstring, std::vector<Rect>> FileList;

	float Timer = 0.f;
	int Index = 0;
	std::vector<Rect> Sprite;

public:
	bool ChangeScene = false;
	bool UiChange = false;
public:
	bool Init();
	void SetTexture(std::vector<Rect> TextureName);
	bool Frame();
	std::vector<Rect> FindSprite(std::wstring name);
	void TextInit();
};

