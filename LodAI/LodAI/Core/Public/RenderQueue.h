#pragma once
#include <vector>
#include <array>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

using FVertexArray = std::array<sf::Vertex, 2>;

struct SRenderCommand
{
	SRenderCommand(const sf::CircleShape& InCircleShape)
		: Shape(EShape::Circle)
		, CircleShape(InCircleShape)
	{
	}

	SRenderCommand(const sf::RectangleShape& InRectangleShape)
		: Shape(EShape::Rectangle)
		, RectangleShape(InRectangleShape)
	{
	}

	SRenderCommand(const FVertexArray& InVertices)
		: Shape(EShape::Vertices)
		, VertexArray(InVertices)
	{
	}

	enum class EShape
	{
		Circle,
		Rectangle,
		Vertices,
	} Shape;

	sf::CircleShape CircleShape;
	sf::RectangleShape RectangleShape;
	FVertexArray VertexArray;
};

class CRenderQueue
{
public:
	void PushRenderCommand(const sf::CircleShape& InCircleShape);
	void PushRenderCommand(const sf::RectangleShape& InRectangleShape);
	void PushRenderCommand(const FVertexArray& InVertexArray);
	void ClearQueue();
	const std::vector<SRenderCommand>& GetQueue() const;
private:
	std::vector<SRenderCommand> Commands;
};