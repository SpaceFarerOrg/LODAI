#include "Navigation/Public/TileWorldRepresentation.h"

#include "Core/Public/RenderQueue.h"
#include <SFML/Graphics/RectangleShape.hpp>

//---------------------------------------------------------

namespace
{
	void MakeNodes(const STileMap& InTileMap, CWorldRepresentationBase::FNodesContainer& InNodesContainer)
	{
		const auto TileCount = InTileMap.TileData.size();

		InNodesContainer.reserve(TileCount);
		
		const float HalfTile = static_cast<float>(InTileMap.TileDimension) / 2.f;
		const sf::Vector2f TilePositionOffset = sf::Vector2f(HalfTile, HalfTile);

		for (size_t i = 0; i < TileCount; ++i)
		{
			SWorldRepresentationNode CreatedNode;
			CreatedNode.ID = i;
			CreatedNode.Passable = InTileMap.TileData[i] == 0 ? true : false ;
			CreatedNode.Position.x = static_cast<float>((i % InTileMap.MapDimension) * InTileMap.TileDimension);
			CreatedNode.Position.y = static_cast<float>((i / InTileMap.MapDimension) * InTileMap.TileDimension);
			CreatedNode.Position += TilePositionOffset;

			InNodesContainer.push_back(CreatedNode);
		}
	}
}

//---------------------------------------------------------

CTileWorldRepresentation::CTileWorldRepresentation(const STileMap& InTileMap)
	: CWorldRepresentationBase()
	, TileDimension(InTileMap.TileDimension)
	, MapDimension(InTileMap.MapDimension)
{
	MakeNodes(InTileMap, Nodes);
}

//---------------------------------------------------------

int CTileWorldRepresentation::GetNodeIDAt(const sf::Vector2f& AtPosition) const
{
	const int PosXInteger = static_cast<int>(AtPosition.x);
	const int PosYInteger = static_cast<int>(AtPosition.y);

	const int GridPosX = PosXInteger / TileDimension;
	const int GridPosY = PosYInteger / TileDimension;

	const int ID = GridPosY * MapDimension + GridPosX;

	return ID;
}

//---------------------------------------------------------

void CTileWorldRepresentation::GetNeighbourIDs(const int InNodeID, std::vector<int>& InOutNeigbourIDs) const
{
	const auto NodePosition = GetNodePosition(InNodeID);
	const short NodeGridPosX = static_cast<short>(NodePosition.x) / TileDimension;
	const short NodeGridPosY = static_cast<short>(NodePosition.y) / TileDimension;

	if (NodeGridPosX != 0) //Node is not to the Far left
	{
		AddNodeToListIfPassable(InNodeID - 1, InOutNeigbourIDs);
	}

	if (NodeGridPosX != MapDimension) //Node is not to the Far right
	{
		AddNodeToListIfPassable(InNodeID + 1, InOutNeigbourIDs);
	}

	if (NodeGridPosY != 0) //Node is not uppermost
	{
		AddNodeToListIfPassable(InNodeID - MapDimension, InOutNeigbourIDs);
	}

	if (NodeGridPosY != MapDimension) //Node is not lowermost
	{
		AddNodeToListIfPassable(InNodeID + MapDimension, InOutNeigbourIDs);
	}
}

//---------------------------------------------------------

void CTileWorldRepresentation::Draw(CRenderQueue& InRenderQueue) const
{
	const float HalfTile = static_cast<float>(TileDimension) / 2.f;
	const sf::Vector2f TileRenderPosOffset = sf::Vector2f(HalfTile, HalfTile);

	for (size_t i = 0; i < Nodes.size(); ++i)
	{
		const auto& Node = Nodes.at(i);

		if (Nodes[i].Passable == false)
		{
			continue;
		}

		const sf::Vector2f Position = GetNodePosition(i);

		sf::RectangleShape RenderCommand;
		RenderCommand.setPosition(Position - TileRenderPosOffset);
		RenderCommand.setSize({ static_cast<float>(TileDimension), static_cast<float>(TileDimension) });
		RenderCommand.setOutlineThickness(1.f);
		RenderCommand.setOutlineColor(sf::Color(0,0,200,100));
		RenderCommand.setFillColor(sf::Color::Transparent);

		InRenderQueue.PushRenderCommand(RenderCommand);
	}
}

//---------------------------------------------------------

void CTileWorldRepresentation::AddNodeToListIfPassable(int NodeID, std::vector<int>& InOutListOfIDs) const
{
	if (Nodes.at(NodeID).Passable)
	{
		InOutListOfIDs.push_back(NodeID);
	}
}

//---------------------------------------------------------

