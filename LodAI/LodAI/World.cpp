#include "World.h"

#include "Core/Public/RenderQueue.h"

#include <SFML/Graphics/Rect.hpp>

#include "Navigation/Public/TileWorldRepresentation.h"
#include "Navigation/Public/NodeGraphWorldRepresentation.h"

//------------------------------------------------

CWorld::CWorld()
	: RenderNavData(false)
{
}

//------------------------------------------------

void CWorld::BuildWorld(const STileMap& InTileMap, const SNavigationNodes& InNavigationNodes, const CActor& LODFromActor)
{
	WorldRepresentationSelector.SetCullFromActor(LODFromActor);
	WorldTileMap = InTileMap;

	//Begin Create Tile Graph
	TileWorldRepresentation = new CTileWorldRepresentation(InTileMap);

	WorldRepresentationSelector.AttachWorldRepresentationToType(*TileWorldRepresentation, EWorldRepresentationTypes::TileGraph);
	WorldRepresentationSelector.SetTypeAllowedDistance(EWorldRepresentationTypes::TileGraph, 200.f);
	//End Create Tile Graph

	//Begin Create Node Graph
	NodeGraphRepresentation = new CNodeGraphWorldRepresentation(InNavigationNodes);

	WorldRepresentationSelector.AttachWorldRepresentationToType(*NodeGraphRepresentation, EWorldRepresentationTypes::NodeGraph);
	WorldRepresentationSelector.SetTypeAllowedDistance(EWorldRepresentationTypes::NodeGraph, 700.f);
	//End Create Node Graph

	CurrentWorldRepresentation = TileWorldRepresentation;
}

//------------------------------------------------

const CWorldRepresentationBase& CWorld::GetCurrentWorldRepresentation(const sf::Vector2f& InAIPosition) const
{
	CurrentWorldRepresentation = &WorldRepresentationSelector.GetGurrentAllowedWorldRepresentation(InAIPosition);
	return *CurrentWorldRepresentation;
}

//------------------------------------------------

void CWorld::Tick()
{

}

//------------------------------------------------

void CWorld::Render(CRenderQueue & InRenderQueue)
{
	const float TileDimensionAsFloat = static_cast<float>(WorldTileMap.TileDimension);

	for (auto i = 0; i < WorldTileMap.TileData.size(); ++i)
	{
		short TileX = i % WorldTileMap.MapDimension;
		short TileY = i / WorldTileMap.MapDimension;

		sf::Vector2f TilePosition;
		TilePosition.x = static_cast<float>(TileX) * TileDimensionAsFloat;
		TilePosition.y = static_cast<float>(TileY) * TileDimensionAsFloat;
		
		sf::RectangleShape RenderCommand;
		RenderCommand.setSize(sf::Vector2f(TileDimensionAsFloat, TileDimensionAsFloat));
		sf::Color Color = WorldTileMap.TileData[i] == 0 ? sf::Color(200, 200, 200, 255) : sf::Color::Red;
		RenderCommand.setFillColor(Color);
		RenderCommand.setPosition(TilePosition);

		InRenderQueue.PushRenderCommand(RenderCommand);
	}

	if (RenderNavData)
	{
		CurrentWorldRepresentation->Draw(InRenderQueue);
	}
}

//------------------------------------------------

void CWorld::ToggleRenderNavData()
{
	RenderNavData = !RenderNavData;
}

//------------------------------------------------
//------------------------------------------------
//------------------------------------------------
