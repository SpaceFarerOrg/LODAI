#include "ActorControllerSystem/Public/Player/PlayerController.h"

#include "VectorMath.h"

#include <SFML/Window/Keyboard.hpp>

//---------------------------------------------------

CPlayerController::CPlayerController()
{
}

//---------------------------------------------------

void CPlayerController::Tick(float TimeDelta)
{
	sf::Vector2f Move(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		Move.x -= 1.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		Move.x += 1.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		Move.y -= 1.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		Move.y += 1.f;
	}

	VectorMath::Normalize(Move);

	Move *= MovementSpeed * TimeDelta;

	MoveFunction(Move);
}

//---------------------------------------------------
//---------------------------------------------------
//---------------------------------------------------
