#pragma once
#include <array>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Navigation/Public/NavDataStructs.h"
#include "Navigation/Public/WorldRepresentationSelector.h"

class CRenderQueue;
class CTileWorldRepresentation;
class CNodeGraphWorldRepresentation;
struct STileMap;
struct SNavigationNodes;

//---------------------------------------------------------

class CWorld
{
public:
	CWorld();

	void BuildWorld(const STileMap& InTileMap, const SNavigationNodes& InNavigationNodes, const CActor& LODFromActor);

	const CWorldRepresentationBase& GetCurrentWorldRepresentation(const sf::Vector2f& AIPosition) const;

	void Tick();
	void Render(CRenderQueue& InRenderQueue);

	void ToggleRenderNavData();
private:
	STileMap WorldTileMap;

	mutable CWorldRepresentationSelector WorldRepresentationSelector;
	mutable const CWorldRepresentationBase* CurrentWorldRepresentation;

	CTileWorldRepresentation* TileWorldRepresentation;
	CNodeGraphWorldRepresentation* NodeGraphRepresentation;

	bool RenderNavData;
	
};