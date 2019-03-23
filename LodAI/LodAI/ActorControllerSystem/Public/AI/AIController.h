#pragma once
#include "ActorControllerSystem/Public/Controller.h"
#include "Navigation/Public/Pathfinder.h"
#include <functional>

class CAIController final
	: public CController
{
public:
	using FGetPosFunc = std::function<const sf::Vector2f&()>;

	CAIController();
	
	void SetWorldRepresentation(const CWorldRepresentationBase& InWorldRepresentation);

	void AttachGetPositionFunc(FGetPosFunc InGetPosFunction);
	
	void Tick(float TimeDelta) override;

private:
	void StartNewPath(const sf::Vector2f& CurrentPosition, const sf::Vector2f& TargetPosition);

	CPathfinder Pathfinder;
	CPathfinder::Path CurrentPath;
	short NextMoveToIndex;

	sf::Vector2f TargetPosition;

	FGetPosFunc GetPositionFunction;
};