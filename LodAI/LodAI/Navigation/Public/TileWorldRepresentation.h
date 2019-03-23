#pragma once
#include "Navigation/Public/WorldRepresentationBase.h"
#include "Navigation/Public/NavDataStructs.h"

class CTileWorldRepresentation final : public CWorldRepresentationBase
{
public:
	CTileWorldRepresentation(const STileMap& InTileMap);

	//Begin Implement WorldRepresentationBase
	int GetNodeIDAt(const sf::Vector2f& AtPosition) const override;
	void GetNeighbourIDs(const int InNodeID, std::vector<int>& InOutNeigbourIDs) const override;
	void Draw(CRenderQueue& InRenderQueue) const override; 
	//End Implement WorldRepresentationBase
private:
	void AddNodeToListIfPassable(int NodeID, std::vector<int>& InOutListOfIDs) const;

	short MapDimension;
	short TileDimension;
};
