#pragma once
enum StateTag
{
	IDLE,
	WALK,
	CROUCH,
	JUMP,
	SHOOT,
	WALLCLING,
	DASH,
	AIRDASH,
};
class State
{
protected:
	StateTag Tag;
	class Player* Owner;
public:
	virtual ~State() {}
	virtual void Enter();
	virtual void Update() = 0;
	virtual void Exit() = 0;
	virtual void SetOwner(class Player* player);
	virtual StateTag GetTag();
};

