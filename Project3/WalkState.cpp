#include "WalkState.h"
#include "JumpState.h"
#include "DashState.h"
#include "IdleState.h"
#include "Input.h"
#include "Player.h"
void WalkState::Enter()
{
	Owner->SetAnimation(Owner->FindSprite(L"Walk.txt"));
	Tag = WALK;
}

void WalkState::Update()
{
	Owner->PlayAnimation();
	if (GameInput.GetKey(VK_LEFT) == KEY_HOLD)
	{
		Owner->SetInverse(true);
		if (Owner->GetLeftWallState() == false) 
		{
			Owner->PlayerMove(LEFT);
		}
		
		/**/
	}
	else if (GameInput.GetKey(VK_RIGHT) == KEY_HOLD)
	{
		Owner->SetInverse(false);
		if (Owner->GetRightWallState() == false) 
		{
			Owner->PlayerMove(RIGHT);
		}
	
	}
	else if (GameInput.GetKey(VK_LEFT) == KEY_UP || GameInput.GetKey(VK_RIGHT) == KEY_UP)
	{
		Owner->ChangeState(new IdleState());
	}
	if (GameInput.GetKey('C') == KEY_PUSH)
	{
		Owner->ChangeState(new JumpState());
	}
	else if (GameInput.GetKey('Z') == KEY_PUSH)
	{
		Owner->ChangeState(new DashState());
	}
	else if (GameInput.GetKey('X') == KEY_PUSH)
	{
		Owner->SetAnimation(Owner->FindSprite(L"ShootWalk.txt"));
	}
}

void WalkState::Exit()
{
	Owner->ResetAnimIndex();
}
