#include "ActorControllerSystem/Public/AI/AIController.h"

#include <SFML/Window/Mouse.hpp>

#include "MouseData.h"
#include "VectorMath.h"
#include <algorithm>

CAIController::CAIController()
	: CController()
{
}

//---------------------------------------------------------

void CAIController::AttachGetPositionFunc(FGetPosFunc InGetPosFunction)
{
	GetPositionFunction = InGetPosFunction;
}

//---------------------------------------------------------

void CAIController::SetWorldRepresentation(const CWorldRepresentationBase& InWorldRepresentation)
{
	Pathfinder.SetWorldRepresentation(InWorldRepresentation);
}

//---------------------------------------------------------

void CAIController::Tick(float TimeDelta)
{

	const sf::Vector2f CurrentPos = GetPositionFunction();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		TargetPosition = CMouseData::Instance().Position();
		StartNewPath(CurrentPos, TargetPosition);
	}

	if (CurrentPath.empty())
	{
		return;
	}
	
	if (NextMoveToIndex == -1)
	{
		return;
	}

	sf::Vector2f Movement;


	Movement = CurrentPath[NextMoveToIndex] - CurrentPos;

	VectorMath::Normalize(Movement);

	Movement *= MovementSpeed * TimeDelta;

	MoveFunction(Movement);
	
	if (VectorMath::IsEqual(CurrentPos, CurrentPath[NextMoveToIndex], 10.f))
	{
		NextMoveToIndex--;
	}
}

//---------------------------------------------------------

void CAIController::StartNewPath(const sf::Vector2f& CurrentPosition, const sf::Vector2f& TargetPosition)
{
	CurrentPath = Pathfinder.Pathfind(CurrentPosition, TargetPosition);
	NextMoveToIndex = CurrentPath.size() - 1;
}

//---------------------------------------------------------
