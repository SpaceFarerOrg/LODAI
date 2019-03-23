#include "Navigation/Public/WorldRepresentationBase.h"
#include <algorithm>

sf::Vector2f CWorldRepresentationBase::GetNodePosition(int NodeID) const
{
	return Nodes[NodeID].Position;
}

