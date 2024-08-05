#pragma once
#include "Object2D.h"
#include "State.h"
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
	class Bullet* PlayerBullet;
	State* CurrentState;
	bool IsGround = false;
	bool LeftWall = false;
	bool RightWall = false;
	bool IsJump;
	bool AnimLoop;
	bool AnimEndLoop;
	ChargeState Charge;
	Vector2 Position;

	SpriteRect Sprite;
	
	StateTag PrevTag;
	StateTag CurrentTag;

	std::map<std::wstring, std::vector<Rect>> FileList;
	std::vector<Rect> CurrentAnimation;
	std::vector<Rect> AnimationList;
	int	AnimationIndex;
	float JumpForce;
	float Speed = 350.f;
	float Time = 0.f;
	float MaxHealth = 100.f;
	float CurHealth = MaxHealth;
	float Y_Speed = 100.f;
	float BulletCoolTime;
	float CoolTime;
public:
	bool Init() override;
	bool Frame() override;
	void Falling(float FallingSpeed = 100.f);
	bool GetIsGround();
	void SetChargeState(ChargeState state);
	void PlayAnimation();
	ChargeState GetChargeState();
	bool CheckAnimationIndex(int adjust = 0);
	void SetAnimation(std::vector<Rect>& Animation);
	void InitAnimation();
	std::vector<Rect> FindSprite(std::wstring name);
	void SetCurrentState();
	void ChangeState(State* NewState);
	void SetInverse(bool state);
	void SetJumpState(bool state);
	void SetAinmationIndex(int Idx);
	void JumpAction();
	void UpdateJumpSpeed(float Force = 0.5f);
	void HandleAnimationLoop();
	void ResetAnimIndex();
	void PlayerMove(int Dir);
	void PlayerDash(float PlayerSpeed);
	bool CheckJumpAccel();
	bool GetInverseState();
	void SetLeftWallState(bool state);
	void SetRightWallState(bool state);
	void SetGroundState(bool state);
	void SetFallingAnim();
	void SpawnBullet();
	void InitBullet();
	bool GetLeftWallState();
	bool GetRightWallState();
};

