#include "Effect.h"
#include "TextLoader.h"
#include <fstream>
bool Effect::Init()
{
	Text = new TextLoader;
	Text->LoadDir(L"../_Animation/Effect/");
	TextInit();
	SetMask(MaskTexName);
	Load(L"../_shader/DefaultMaskShader.txt", TextureName);
	SetRect(FindSprite(L"Charging.txt")[0]);
	CreateVertex();
	return true;
}

bool Effect::Frame()
{
	Play();
	SetPosition(WorldPos);
	return true;
}

bool Effect::Release()
{
	Text = nullptr;
	return true;
}

std::vector<Rect> Effect::FindSprite(std::wstring name)
{

	auto iter = FileList.find(name);
	if (iter != FileList.end()) {
		return iter->second;
	}
	return std::vector<Rect>();
}

void Effect::TextInit()
{
	for (int i = 0; i < Text->fileList.size(); i++)
	{
		int num = 0;
		std::ifstream file(Text->fileList[i]);
		std::wstring name = Text->GetSplitName(Text->fileList[i]);
		file >> num;
		EffectList.reserve(num);
		while (file.eof() == false)
		{
			file >> Range.left >> Range.top >> Range.right >> Range.bottom;
			EffectList.push_back({ Range.left,Range.top, Range.right,Range.bottom });
		}
		FileList.insert(std::make_pair(name, EffectList));
		EffectList.clear();
		file.close();
	}
}

void Effect::Play()
{
	if (Sprite.size() == 0) 
	{
		return;
	}

	float LifeTime = Sprite.size() * 0.05f;
	float frame = 0.0f;
	EffectTimer += gSecondPerFrame;
	frame = LifeTime / Sprite.size();
	if (EffectTimer >= frame)
	{
		Index++;
		if (Index >= Sprite.size()) {
			if (Tag == CHRGING) {
				Index = (Sprite.size() / 2) + 3;
			}
			if (Tag == DASHDUST) {
				Index = 0;
				return;
			}
			else if (Tag == BOOSTER) {
				Index = 0;
			}
			else if (Tag == WALLDUST) {
				Index = 0;
			}

		}
		EffectTimer = EffectTimer - frame;
	}
	SetRect(Sprite[Index]);
}

void Effect::SetSprite(std::vector<Rect>& Texture)
{
	Sprite = Texture;
}

void Effect::SetTexture(std::wstring TexName, std::wstring MaskName)
{
	TextureName = TexName;
	MaskTexName = MaskName;
}
