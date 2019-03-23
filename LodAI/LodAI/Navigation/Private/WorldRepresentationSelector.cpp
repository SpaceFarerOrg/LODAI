#include "Navigation/Public/WorldRepresentationSelector.h"

#include "ActorControllerSystem/Public/Actor.h"
#include "VectorMath.h"
#include "Navigation/Public/WorldRepresentationBase.h"

//-----------------------------------------------------------------

CWorldRepresentationSelector::CWorldRepresentationSelector()
	: WorldRepresentations()
	, AllowedDistances()
	, GetCullingPosition()
	, LongestAllowedDistance(0.f)
	, TypeWithLongestAllowedDistance(EWorldRepresentationTypes::Count)
{
}

//-----------------------------------------------------------------

void CWorldRepresentationSelector::SetCullFromActor(const CActor & InCullFrom)
{
	GetCullingPosition = [&InCullFrom](){ return InCullFrom.GetPosition(); };
}

//-----------------------------------------------------------------

void CWorldRepresentationSelector::SetTypeAllowedDistance(EWorldRepresentationTypes Type, float InAllowedDistance)
{
	if (InAllowedDistance >= LongestAllowedDistance)
	{
		LongestAllowedDistance = InAllowedDistance;
		TypeWithLongestAllowedDistance = Type;
	}

	AllowedDistances[static_cast<unsigned int>(Type)] = InAllowedDistance;
}

//-----------------------------------------------------------------

const CWorldRepresentationBase & CWorldRepresentationSelector::GetGurrentAllowedWorldRepresentation(const sf::Vector2f& InNavAgentPosition)
{
	const sf::Vector2f& CullRelevantPosition = GetCullingPosition();
	const float DistanceFromNavAgentToPlayer = VectorMath::DistanceBetween(InNavAgentPosition, CullRelevantPosition);

	const CWorldRepresentationBase* AllowedWorldRepresentation = nullptr;

	if (DistanceFromNavAgentToPlayer > LongestAllowedDistance)
	{
		AllowedWorldRepresentation = WorldRepresentations[static_cast<unsigned int>(TypeWithLongestAllowedDistance)];
	}
	else
	{
		int IndexOfLowestAllowanceWithinCurrentDistance = -1;
		float LowestChecked = FLT_MAX;

		for (int i = 0; i < AllowedDistances.size(); ++i)
		{
			const float AllowedDistance = AllowedDistances[i];

			if (AllowedDistance > DistanceFromNavAgentToPlayer &&
				AllowedDistance < LowestChecked)
			{
				LowestChecked = AllowedDistance;
				IndexOfLowestAllowanceWithinCurrentDistance = i;
			}
		}

		AllowedWorldRepresentation = WorldRepresentations[IndexOfLowestAllowanceWithinCurrentDistance];
	}

	return *AllowedWorldRepresentation;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
