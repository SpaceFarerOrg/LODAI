#include "MouseData.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

//-------------------------------------------------------------

CMouseData & CMouseData::Instance()
{
	static CMouseData Instance;

	return Instance;
}

//-------------------------------------------------------------

void CMouseData::BindWindow(const sf::RenderWindow & InWindow)
{
	BoundWindow = &InWindow;
}

//-------------------------------------------------------------

sf::Vector2f CMouseData::Position() const
{
	sf::Vector2f MousePos;

	if (BoundWindow)
	{
		sf::Vector2i MousePosV2I = sf::Mouse::getPosition(*BoundWindow);
		MousePos.x = static_cast<float>(MousePosV2I.x);
		MousePos.y = static_cast<float>(MousePosV2I.y);
	}

	return MousePos;
}

//-------------------------------------------------------------

CMouseData::CMouseData()
	: BoundWindow(nullptr)
{
}

//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
