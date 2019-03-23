#pragma once
#include "Navigation/Public/WorldRepresentationBase.h"
#include "Navigation/Public/NavDataStructs.h"

class CNodeGraphWorldRepresentation final
	: public CWorldRepresentationBase
{
public:
	using FNodeNeighbourLUT = std::vector<std::vector<short>>;

	CNodeGraphWorldRepresentation(const SNavigationNodes& InNavNodes);
	int GetNodeIDAt(const sf::Vector2f& AtPosition) const override;
	void GetNeighbourIDs(const int InNodeID, std::vector<int>& InOutNeigbourIDs) const override;
	void Draw(CRenderQueue& InRenderQueue) const override;
private:
	FNodeNeighbourLUT NodeNeighbourLUT;
};