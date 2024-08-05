#include "Player.h"
#include "IdleState.h"
#include "TextLoader.h"
#include "Bullet.h"
#include <fstream>
void Player::Falling(float FallingSpeed)
{
	JumpForce = 0.5f;
	Position.y += 1.0f * gSecondPerFrame * 9.8 * FallingSpeed * JumpForce;
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
	if (AnimationIndex >= CurrentAnimation.size() - adjust)
	{
		return true;
	}
	return false;
}

void Player::SetAnimation(std::vector<Rect>& Animation)
{
	CurrentAnimation = std::move(Animation);
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

bool Player::Init()
{
	Inverse = false;
	//IsGround = true; // test code
	JumpForce = 0.5f;
	BulletCoolTime = 0.25f;
	CoolTime = 0.f;
	Loader = new TextLoader;
	Loader->LoadDir(L"../_Animation/RockMan/");
	SetMask(L"../_Texture/RockManmask.bmp");
	SetPhysics();
	Load(L"../_shader/DefaultMaskShader.txt", L"../_Texture/RockMan.bmp");
	InitAnimation();
	SetRect(FindSprite(L"Idle.txt")[0]);
	CurrentAnimation = FindSprite(L"Idle.txt");
	SetPosition({ 150,-100 });
	ChangeState(new IdleState);
	CreateVertex();
	return true;
}

bool Player::Frame()
{
	Position = WorldPos;
	CurrentState->Update();
	if (PlayerBullet != nullptr)
	{
		PlayerBullet->Frame();
	}
	SetPosition(Position);
	return true;
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
		PrevTag = CurrentState->GetTag();
		CurrentState->Exit();
		delete CurrentState;
		CurrentState = nullptr;
	}
	CurrentState = NewState;
	CurrentState->SetOwner(this);
	CurrentState->Enter();
	CurrentTag = CurrentState->GetTag();
}

void Player::PlayAnimation()
{
	/*if (_State != _PreState) {
		AnimationIndex = 0;
	}*/
	if (AnimationIndex >= CurrentAnimation.size())
	{
		AnimationIndex = 0;
	}
	SetRect(CurrentAnimation[AnimationIndex]);
	float LifeTime = CurrentAnimation.size() * 0.1;
	float frame = 0.0f;
	Time += gSecondPerFrame;
	frame = LifeTime / CurrentAnimation.size();
	if (Time >= frame)
	{
		AnimationIndex++;
		HandleAnimationLoop();
		Time = Time - frame;
	}
}
void Player::HandleAnimationLoop()
{
	if (AnimationIndex >= CurrentAnimation.size())
	{
		if (AnimLoop)
		{
			AnimationIndex = 2;
		}
		if (AnimEndLoop)
		{
			AnimationIndex = CurrentAnimation.size() - 1;
		}
		else
		{
			AnimationIndex = 1;
		}
		/*	if (_State == HIT) {
				_Index = _Play.size();
			}*/

	}
}

void Player::SetAinmationIndex(int idx)
{
	AnimationIndex = idx;
}

bool Player::CheckJumpAccel()
{
	if (JumpForce <0.f)
	{
		if (IsGround == true) 
		{
			AnimEndLoop = false;
			//Landing->PlayEffect(0.65f);
			return true;
		}
		return false;
	}
	return false;
}

void Player::ResetAnimIndex()
{
	AnimationIndex = 0;
}

void Player::PlayerMove(int Dir)
{
	if (Dir == LEFT)
	{
		Position.x += -1.0f * gSecondPerFrame * Speed;
	}
	else if (Dir == RIGHT) 
	{
		Position.x += 1.0f * gSecondPerFrame * Speed;
	}
}

void Player::PlayerDash(float PlayerSpeed)
{
	if (Inverse == true)
	{
		Position.x += -1.0f * gSecondPerFrame * PlayerSpeed;
	}
	else if (Inverse == false)
	{
		Position.x += 1.0f * gSecondPerFrame * PlayerSpeed;
	}
}

bool Player::GetInverseState()
{
	return Inverse;
}

void Player::SetLeftWallState(bool state)
{
	LeftWall = state;
}

void Player::SetRightWallState(bool state)
{
	RightWall = state;
}

void Player::SetGroundState(bool state)
{
	IsGround = state;
}


void Player::SpawnBullet()
{
	if (CoolTime < 0.f)
	{
		//bulletInit
		InitBullet();
		CoolTime = BulletCoolTime;
	}
	else
	{
		CoolTime -= gSecondPerFrame;
	}
}

void Player::SetFallingAnim()
{
	SetAinmationIndex(FindSprite(L"Jump.txt").size()-1);
}

bool Player::GetRightWallState()
{
	return RightWall;
}

void Player::InitBullet()
{
	PlayerBullet = new Bullet;
	PlayerBullet->SetData(D3D11Device, D3D11Context, ClientRect);
	PlayerBullet->Init();
	PlayerBullet->SetType(NORMAL);
	//AddBullet(L"Normal.txt", Player, NOR);
}

void Player::SetInverse(bool state)
{
	Inverse = state;
}

void Player::SetJumpState(bool state)
{
	AnimEndLoop = state;
	IsJump = state;
}

void Player::JumpAction()
{
	Position.y += -1.0f * gSecondPerFrame * 9.8 * Y_Speed * JumpForce;
	JumpForce -= gSecondPerFrame;
}

void Player::UpdateJumpSpeed(float Force)
{
	if (PrevTag != AIRDASH)
	{
		JumpForce = Force;
	}
	else
	{
		JumpForce = 0.f;
	}
}

bool Player::GetLeftWallState()
{
	return LeftWall;
}