#include "JumpState.h"
#include "IdleState.h"
#include "DashState.h"
#include "WallClingState.h"
#include "AirDashState.h"
#include "Input.h"
#include "Player.h"
void JumpState::Enter()
{
	Owner->SetAnimation(Owner->FindSprite(L"Jump.txt"));
	Tag = JUMP;
	Owner->SetJumpState(true);
	Owner->UpdateJumpSpeed();
}

void JumpState::Update()
{
	Owner->JumpAction();
	Owner->PlayAnimation();
	if (GameInput.GetKey(VK_LEFT) == KEY_HOLD)
	{
		Owner->SetInverse(true);
		if (Owner->GetLeftWallState() == false)
		{
			Owner->PlayerMove(LEFT);
		}
		else
		{
			Owner->ChangeState(new WallClingState());
			return;
		}
	}
	else if (GameInput.GetKey(VK_RIGHT) == KEY_HOLD)
	{
		Owner->SetInverse(false);
		if (Owner->GetRightWallState() == false)
		{
			Owner->PlayerMove(RIGHT);
		}
		else
		{
			Owner->ChangeState(new WallClingState());
			return;
		}
	}
	if (GameInput.GetKey('X') == KEY_PUSH) 
	{
		WaitTime = 0.0f;
		Owner->SetAnimation(Owner->FindSprite(L"ShootJump.txt"));
	}
	else if (GameInput.GetKey('X') == KEY_FREE) 
	{
		/*if (ChargeState == CHARGEND)
		{
			SetSprite(FindSprite(L"ShootJump.txt"));
		}*/
		WaitTime += gSecondPerFrame;
		if (WaitTime > 0.1f) {
			Owner->SetAnimation(Owner->FindSprite(L"Jump.txt"));
		}
	}
	if (GameInput.GetKey('Z') == KEY_PUSH)
	{
		Owner->ChangeState(new AirDashState());
		return;
	}
	if (Owner->CheckJumpAccel())
	{
		Owner->ChangeState(new IdleState());
	}
}

void JumpState::Exit()
{
	Owner->SetJumpState(false);
	Owner->ResetAnimIndex();
}
