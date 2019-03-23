#include "Navigation/Public/NodeGraphWorldRepresentation.h"

#include "Core/Public/RenderQueue.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include "VectorMath.h"

//---------------------------------------------------------

namespace
{
	void MakeNodes(const SNavigationNodes& InNavNodes, CWorldRepresentationBase::FNodesContainer& InNodesContainer, CNodeGraphWorldRepresentation::FNodeNeighbourLUT& InNodeNeighboirLUT)
	{
		const auto NodeCount = InNavNodes.NavNodeData.size();
		InNodesContainer.reserve(NodeCount);
		InNodeNeighboirLUT.reserve(NodeCount);

		for (auto i = 0u; i < NodeCount; ++i)
		{
			//Build Node
			SWorldRepresentationNode CreatedNode;
			CreatedNode.ID = i;
			CreatedNode.Passable = true; //All nodes in here are passable as it is a designer created structure for path finding
			CreatedNode.Position = InNavNodes.NavNodeData[i].Position;

			InNodesContainer.push_back(CreatedNode);

			InNodeNeighboirLUT.push_back(std::vector<short>());

			//Build Links
			for (auto NeighbourID : InNavNodes.NavNodeData[i].Links)
			{
				InNodeNeighboirLUT[i].push_back(NeighbourID);
			}
		}
	}
}

//---------------------------------------------------------

CNodeGraphWorldRepresentation::CNodeGraphWorldRepresentation(const SNavigationNodes& InNavNodes)
	: CWorldRepresentationBase()
{
	::MakeNodes(InNavNodes, Nodes, NodeNeighbourLUT);
}

//---------------------------------------------------------

int CNodeGraphWorldRepresentation::GetNodeIDAt(const sf::Vector2f& AtPosition) const
{
	int ClosestNodeID = -1;
	float ClosestNodeDistance = FLT_MAX;

	for (auto i = 0; i < Nodes.size(); ++i)
	{
		const auto& Node = Nodes[i];

		float DistanceToNode = VectorMath::DistanceBetween(AtPosition, Node.Position);

		if (DistanceToNode < ClosestNodeDistance)
		{
			ClosestNodeDistance = DistanceToNode;
			ClosestNodeID = i;
		}
	}

	return ClosestNodeID;
}

//---------------------------------------------------------

void CNodeGraphWorldRepresentation::GetNeighbourIDs(const int InNodeID, std::vector<int>& InOutNeigbourIDs) const
{
	for (auto NeighbourID : NodeNeighbourLUT[InNodeID])
	{
		InOutNeigbourIDs.push_back(NeighbourID);
	}
}

//---------------------------------------------------------

void CNodeGraphWorldRepresentation::Draw(CRenderQueue& InRenderQueue) const
{
	for (auto i = 0; i < Nodes.size(); ++i)
	{
		sf::RectangleShape NodeRenderCommand;
		NodeRenderCommand.setSize(sf::Vector2f(32.f, 32.f));
		NodeRenderCommand.setFillColor(sf::Color(0, 0, 255, 100));
		NodeRenderCommand.setPosition(Nodes[i].Position);

		InRenderQueue.PushRenderCommand(NodeRenderCommand);

		const sf::Vector2f LinkLineOffset = sf::Vector2f(16.f, 16.f);

		FVertexArray LinkPoints;
		LinkPoints[0] = Nodes[i].Position + LinkLineOffset;
		LinkPoints[0].color = sf::Color::Blue;
		LinkPoints[1].color = sf::Color::Blue;

		for (auto Neighbour : NodeNeighbourLUT[i])
		{
			LinkPoints[1].position = Nodes[Neighbour].Position + LinkLineOffset;
			InRenderQueue.PushRenderCommand(LinkPoints);
		}

	}
}

//---------------------------------------------------------