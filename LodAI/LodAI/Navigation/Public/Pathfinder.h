#pragma once
#include <vector>
#include <map>
#include <SFML/System/Vector2.hpp>

class CWorldRepresentationBase;

class CPathfinder
{
public:
	using Path = std::vector<sf::Vector2f>;

	CPathfinder();
	void SetWorldRepresentation(const CWorldRepresentationBase& InWorldRepresentation);
	Path Pathfind(const sf::Vector2f& Start, const sf::Vector2f& End);
private:
	Path CreatePath(const std::map<int, int>& ToPreviousLookUp, int EndID) const;

	const CWorldRepresentationBase * CurrentWorldRepresentation;
};