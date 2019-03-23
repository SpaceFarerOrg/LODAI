#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class CRenderQueue;

class CActor
{
public:
	CActor();

	CActor& SetSize(float InSize);
	CActor& SetColor(const sf::Color& InColor);

	void Render(CRenderQueue& RenderQueue);

	void Move(const sf::Vector2f& InOffset);
	const sf::Vector2f& GetPosition() const;
private:
	sf::CircleShape Shape;
	sf::Vector2f Position;
};