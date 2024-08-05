#include "ShootState.h"
#include "WalkState.h"
#include "IdleState.h"
#include "Player.h"
#include "Input.h"
void ShootState::Enter()
{
	Owner->SetAnimation(Owner->FindSprite(L"Shoot.txt"));
	Tag = SHOOT;
}

void ShootState::Update()
{
	Owner->PlayAnimation();
	if (GameInput.GetKey('X') == KEY_PUSH)
	{
		Owner->SetAinmationIndex(0);
	}
	else if(GameInput.GetKey('X') == KEY_FREE)
	{
		if (Owner->CheckAnimationIndex(1))
		{
			Owner->ChangeState(new IdleState());
		}
	}

	else if (GameInput.GetKey(VK_LEFT) == KEY_HOLD)
	{
		Owner->SetInverse(true);
		Owner->ChangeState(new WalkState());
	}
	else if (GameInput.GetKey(VK_RIGHT) == KEY_HOLD)
	{
		Owner->SetInverse(false);
		Owner->ChangeState(new WalkState());
	}

}

void ShootState::Exit()
{
	Owner->ResetAnimIndex();
}
