#pragma once
#include <array>
#include <functional>
#include <type_traits>

#include <SFML/System/Vector2.hpp>

class CActor;
class CWorldRepresentationBase;

enum class EWorldRepresentationTypes
{
	NodeGraph,
	TileGraph,
	Count,
};

class CWorldRepresentationSelector
{
public:
	CWorldRepresentationSelector();

	void SetCullFromActor(const CActor& InCullFrom);
	void SetTypeAllowedDistance(EWorldRepresentationTypes Type, float InAllowedDistance);

	const CWorldRepresentationBase& GetGurrentAllowedWorldRepresentation(const sf::Vector2f& InNavAgentPosition);

	template<typename WorldRepresentation>
	void AttachWorldRepresentationToType(const WorldRepresentation& InWorldRepresentation, EWorldRepresentationTypes Type);

private:
	std::array<const CWorldRepresentationBase*, static_cast<unsigned int>(EWorldRepresentationTypes::Count)> WorldRepresentations;
	std::array<float, static_cast<unsigned int>(EWorldRepresentationTypes::Count)> AllowedDistances;
	std::function<const sf::Vector2f&()> GetCullingPosition;

	float LongestAllowedDistance;
	EWorldRepresentationTypes TypeWithLongestAllowedDistance;
};

template<typename WorldRepresentation>
inline void CWorldRepresentationSelector::AttachWorldRepresentationToType(const WorldRepresentation & InWorldRepresentation, EWorldRepresentationTypes Type)
{
	static_assert(std::is_base_of<CWorldRepresentationBase, WorldRepresentation>(), "World representations must derive from CWorldRepresentationBase");
	static_assert(!std::is_abstract<WorldRepresentation>(), "World Representations should not be abstract! Did you try to attach CWorldRepresentationBase?");

	WorldRepresentations[static_cast<unsigned int>(Type)] = &InWorldRepresentation;
}
