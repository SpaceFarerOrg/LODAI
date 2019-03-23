#pragma once
#include "ActorControllerSystem/Public/Controller.h"

class CPlayerController final 
	: public CController
{
public:
	CPlayerController();
	void Tick(float TimeDelta) override;
};
