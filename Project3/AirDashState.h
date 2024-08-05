#pragma once
#include "State.h"
class AirDashState : public State
{
	float DashTime;
public:
	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};

