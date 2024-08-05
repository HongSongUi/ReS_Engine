#pragma once
#include <map>
#include "Object2D.h"

enum Owner
{
	PLAYER,
	NPC,
};

enum BulletType
{
	NORMAL,
	SEC_CHARGE,
	FULL_CHARGE,
};

class Bullet : public Object2D
{
	SpriteRect BulletRect;
	std::vector<Rect> BulletList;
	class TextLoader* Loader;
	std::map<std::wstring, std::vector<Rect>> AnimationFiles;


	Vector2 Position;
	float Time;
	float Damage;
	float LifeTime;
	std::vector<Rect> CurrentAnimation;
	int AnimIndex;
	BulletType Type;
	float NormalDamage;
	float SecondDamage;
	float FullDamage;
public:
	bool Init()override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	std::vector<Rect> GetAnimation(std::wstring name);
	void MoveBullet();
	void AnimationInit();
	void Play();
	void SetAnimaiton(std::vector<Rect>& texture);
	void SetType(BulletType type);
};

