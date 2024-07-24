#pragma once
#include "Object2D.h"

#define LEFT 0
#define RIGHT 1

enum ChargeState {
	NOCHARGE,
	CHARGING,
	CHARGEND,
};
class Player : public Object2D
{
	bool IsGround;
	ChargeState State;
	Vector2 Postion;

	float JumpForce;
	float Speed;
public:
	void Falling();
	bool GetIsGround();
	void SetChargeState(ChargeState state);
	ChargeState GetChargeState();
};

