#pragma once
class State
{
protected:
	class Player* Owner;
public:
	virtual ~State() {}
	virtual void Enter();
	virtual void Update() = 0;
	virtual void Exit() = 0;
};

