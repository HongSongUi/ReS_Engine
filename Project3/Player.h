#pragma once
#include "Object2D.h"
#include "IdleState.h"
#include <map>
#define LEFT 0
#define RIGHT 1

enum ChargeState {
	NOCHARGE,
	CHARGING,
	CHARGEND,
};
class Player : public Object2D
{
	class TextLoader* Loader;
	State* CurrentState;
	State* PrevState;
	bool IsGround;
	ChargeState Charge;
	Vector2 Postion;

	SpriteRect Sprite;


	std::map<std::wstring, std::vector<Rect>> FileList;
	const std::vector<Rect>* CurrentAnimation = nullptr;
	std::vector<Rect> AnimationList;
	int	Index;
	float JumpForce;
	float Speed;
	float MaxHealth = 100.0f;
	float CurHealth = MaxHealth;

public:
	void Falling();
	bool GetIsGround();
	void SetChargeState(ChargeState state);
	ChargeState GetChargeState();
	bool CheckAnimationIndex(int adjust = 0);
	void SetAnimation(std::vector<Rect>& Animation);
	void InitAnimation();
	std::vector<Rect> FindSprite(std::wstring name);
	void SetCurrentState();
	void ChangeState(State* NewState);
	void SetInverse(bool state);
};

