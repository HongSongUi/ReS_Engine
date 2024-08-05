#include "DashState.h"
#include "IdleState.h"
#include "JumpState.h"
#include "Player.h"
#include "Input.h"
void DashState::Enter()
{
	Owner->SetAnimation(Owner->FindSprite(L"Dash.txt"));
	Tag = DASH;
	DashTime = 0.55f;
}

void DashState::Update()
{
	Owner->PlayAnimation();
	if (!Owner->GetLeftWallState() && !Owner->GetRightWallState())
	{
		Owner->PlayerDash(500.f);
	}
	DashTime -= gSecondPerFrame;
	if (DashTime < 0.f)
	{
		Owner->ChangeState(new IdleState);
	}

	if (GameInput.GetKey('X') == KEY_PUSH)
	{
		WaitTime = 0.f;
		Owner->SetAnimation(Owner->FindSprite(L"ShootDash.txt"));
	}
	else if (GameInput.GetKey('X') == KEY_FREE)
	{
		WaitTime += gSecondPerFrame;
		if (WaitTime > 0.1f)
		{
			Owner->SetAnimation(Owner->FindSprite(L"Dash.txt"));
		}
	}

	if (GameInput.GetKey('C') == KEY_PUSH)
	{
		Owner->ChangeState(new JumpState);
	}
}

void DashState::Exit()
{
	Owner->ResetAnimIndex();
}
