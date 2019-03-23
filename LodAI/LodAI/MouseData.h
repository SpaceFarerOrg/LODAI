#pragma once
#include <SFML/System/Vector2.hpp>

namespace sf
{
	class RenderWindow;
}

class CMouseData
{
public:
	static CMouseData& Instance();
	void BindWindow(const sf::RenderWindow& InWindow);
	sf::Vector2f Position() const;
private:
	CMouseData();
	const sf::RenderWindow* BoundWindow;
};