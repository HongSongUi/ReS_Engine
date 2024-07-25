#include "Player.h"
#include "TextLoader.h"
#include <fstream>
void Player::Falling()
{
	JumpForce = 0.5f;
	Postion.y += 1.0f * gSecondPerFrame * 9.8 * JumpForce * JumpForce;
}

bool Player::GetIsGround()
{
	return IsGround;
}

void Player::SetChargeState(ChargeState state)
{
	Charge = state;
}

ChargeState Player::GetChargeState()
{
	return Charge;
}

bool Player::CheckAnimationIndex(int adjust)
{
	if (Index >= CurrentAnimation->size() - adjust)
	{
		return true;
	}
	return false;
}

void Player::SetAnimation(std::vector<Rect>& Animation)
{
	CurrentAnimation = &Animation;
}

void Player::InitAnimation()
{
	for (int i = 0; i < Loader->fileList.size(); i++) 
	{
		int num = 0;
		std::ifstream file(Loader->fileList[i]);
		std::wstring name = Loader->GetSplitName(Loader->fileList[i]);
		file >> num;
		AnimationList.reserve(num);
		while (file.eof() == false) 
		{
			file >> Sprite.Left >> Sprite.Top >> Sprite.Right >> Sprite.Bottom;
			AnimationList.push_back({ Sprite.Left,Sprite.Top, Sprite.Right,Sprite.Bottom });
		}
		FileList.insert(std::make_pair(name, AnimationList));
		AnimationList.clear();
		file.close();
	}
}

std::vector<Rect> Player::FindSprite(std::wstring name)
{
	auto iter = FileList.find(name);
	if (iter != FileList.end())
	{
		return iter->second;
	}

	return std::vector<Rect>();
}

void Player::SetCurrentState()
{
	if (CurHealth <= MaxHealth / 2.0f) {
		SetAnimation(FindSprite(L"IdleLowHp.txt"));
	}
	else {
		SetAnimation(FindSprite(L"Idle.txt"));
	}
}

void Player::ChangeState(State* NewState)
{
	if (CurrentState)
	{
		PrevState = CurrentState;
		CurrentState->Exit();
		delete CurrentState;
	}
	CurrentState = NewState;
	CurrentState->SetOwner(this);
	CurrentState->Enter();
}

void Player::SetInverse(bool state)
{
	Inverse = state;
}

