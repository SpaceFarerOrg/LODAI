#pragma once
#include <SFML/System/Vector2.hpp>
#include <functional>

class CController
{
	using MoveFunc = std::function<void(const sf::Vector2f&)>;

public:
	CController();
	void SetMovementSpeed(float InMovementSpeed);
	void AttachMoveFunction(MoveFunc InMoveFunction);

	virtual void Tick(float TimeDelta) = 0;
protected:
	MoveFunc MoveFunction;
	float MovementSpeed;
};