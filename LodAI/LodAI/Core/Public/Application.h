#pragma once
#include <SFML/System/Clock.hpp>

#include "ActorControllerSystem/Public/Actor.h"
#include "ActorControllerSystem/Public/Player/PlayerController.h"
#include "ActorControllerSystem/Public/AI/AIController.h"
#include "Core/Public/RenderQueue.h"
#include "Core/Public/Renderer.h"
#include "World.h"


class CApplication
{
public:
	CApplication() = delete;
	CApplication(bool& InShouldRun);
	void Initialize();
	void Tick();

	void ToggleRenderNavData();
private: 
	float GetTickTimeDelta();

	void CheckForWindowEvents();

	CRenderer Renderer;
	CRenderQueue RenderQueue;
	
	sf::Clock Clock;
	bool& ShouldRun;

	CWorld World;

	CActor PlayerActor;
	CActor AIActor;

	CPlayerController PlayerController;
	CAIController AIController;
};