#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

class CRenderQueue;

struct SWorldRepresentationNode
{
	int ID;
	bool Passable;
	sf::Vector2f Position;
};

class CWorldRepresentationBase
{
public:
	using FNodesContainer = std::vector<SWorldRepresentationNode>;

	CWorldRepresentationBase() = default;
	virtual sf::Vector2f GetNodePosition(int NodeID) const;
	virtual int GetNodeIDAt(const sf::Vector2f& AtPosition) const = 0;
	virtual void GetNeighbourIDs(const int InNodeID, std::vector<int>& InOutNeigbourIDs) const = 0;
	virtual void Draw(CRenderQueue& InRenderQueue) const = 0;
protected:
	FNodesContainer Nodes;
};