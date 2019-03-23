#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

//Node Graph
struct SNavigationNodes
{
	struct SNavNode
	{
		using FNavNodeLinks = std::vector<short>;

		sf::Vector2f Position;
		FNavNodeLinks Links;
	};

	using FNavNodeData = std::vector<SNavNode>;

	FNavNodeData NavNodeData;

};

//Tile Graph
struct STileMap
{
	using FTileData = std::vector<short>;

	FTileData TileData;
	short TileDimension;
	short MapDimension;
};

