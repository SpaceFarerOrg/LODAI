#include "Navigation/Public/Pathfinder.h"

#include "VectorMath.h"
#include "Navigation/Public/WorldRepresentationBase.h"

#include <cassert>
#include <set>

//---------------------------------------------------------

namespace
{
	float GetHeuristicCost(const sf::Vector2f& From, const sf::Vector2f& To)
	{
		return fabsf(From.x - To.x) + fabsf(From.y - To.y);
	}

	void EnsureMapDefaultsToFltMax(std::map<int, float>& Map, int Value)
	{
		if (Map.find(Value) == Map.end())
		{
			Map[Value] = FLT_MAX;
		}
	}

	int GetLowestFScoreNodeID(const std::set<int>& OpenSet, const std::map<int, float>& FScores)
	{
		int LowestID = -1;
		float CurrentLowest = FLT_MAX;

		for (int ID : OpenSet)
		{
			const float Score = FScores.at(ID);

			if(Score < CurrentLowest)
			{
				CurrentLowest = Score;
				LowestID = ID;
			}
		}

		return LowestID;
	}
}

//---------------------------------------------------------

CPathfinder::CPathfinder()
	: CurrentWorldRepresentation(nullptr)
{
}

//---------------------------------------------------------

void CPathfinder::SetWorldRepresentation(const CWorldRepresentationBase & InWorldRepresentation)
{
	CurrentWorldRepresentation = &InWorldRepresentation;
}

//---------------------------------------------------------

CPathfinder::Path CPathfinder::Pathfind(const sf::Vector2f & StartPos, const sf::Vector2f & EndPos)
{
	assert(CurrentWorldRepresentation != nullptr && "World Representation can not be unset when trying to find path!");

	const int StartID = CurrentWorldRepresentation->GetNodeIDAt(StartPos);
	const int EndID = CurrentWorldRepresentation->GetNodeIDAt(EndPos);

	std::set<int> OpenNodeIDs;
	std::set<int> ClosedNodeIDs;
	std::map<int, float> GScores;
	std::map<int, float> FScores;
	std::map<int, int> ToPreviousLookup;

	GScores[StartID] = 0.f;
	FScores[StartID] = GetHeuristicCost(StartPos, EndPos);

	OpenNodeIDs.insert(CurrentWorldRepresentation->GetNodeIDAt(StartPos));

	while (!OpenNodeIDs.empty())
	{
		int CurrentID = GetLowestFScoreNodeID(OpenNodeIDs, FScores);

		if (CurrentID == EndID)
		{
			return std::move(CreatePath(ToPreviousLookup, EndID));
		}

		OpenNodeIDs.erase(CurrentID);
		ClosedNodeIDs.insert(CurrentID);

		std::vector<int> NeighboursToCurrent;
		CurrentWorldRepresentation->GetNeighbourIDs(CurrentID, NeighboursToCurrent);

		for (int NeighbourID : NeighboursToCurrent)
		{
			if (ClosedNodeIDs.find(NeighbourID) != ClosedNodeIDs.end())
			{
				continue;
			}

			EnsureMapDefaultsToFltMax(GScores, NeighbourID);
			EnsureMapDefaultsToFltMax(FScores, NeighbourID);
			
			const sf::Vector2f CurrentPos = CurrentWorldRepresentation->GetNodePosition(CurrentID);
			const sf::Vector2f NeighbourPos = CurrentWorldRepresentation->GetNodePosition(NeighbourID);
			float SpeculativeGScore = GScores[CurrentID] + VectorMath::DistanceBetween(CurrentPos, NeighbourPos);

			if (OpenNodeIDs.find(NeighbourID) == OpenNodeIDs.end())
			{
				OpenNodeIDs.insert(NeighbourID);
			}
			else if (SpeculativeGScore >= GScores[NeighbourID])
			{
				continue;
			}

			ToPreviousLookup[NeighbourID] = CurrentID;
			GScores[NeighbourID] = SpeculativeGScore;
			FScores[NeighbourID] = SpeculativeGScore + GetHeuristicCost(NeighbourPos, EndPos);
		}
	}

	return Path();
}

//---------------------------------------------------------

CPathfinder::Path CPathfinder::CreatePath(const std::map<int, int>& ToPreviousLookUp, int EndID) const
{
	int CurrentID = EndID;
	CPathfinder::Path CreatedPath;

	while (ToPreviousLookUp.find(CurrentID) != ToPreviousLookUp.end())
	{
		const sf::Vector2f PositionOfCurrent = CurrentWorldRepresentation->GetNodePosition(CurrentID);
		CreatedPath.push_back(PositionOfCurrent);

		CurrentID = ToPreviousLookUp.at(CurrentID);
	}

	return std::move(CreatedPath);
}

//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------