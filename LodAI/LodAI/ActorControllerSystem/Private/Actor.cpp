#include "ActorControllerSystem/Public/Actor.h"

#include "Core/Public/RenderQueue.h"

//------------------------------------------------

CActor::CActor()
	: Position(0.f, 0.f)
{
	Shape.setOutlineThickness(2.f);
	Shape.setFillColor(sf::Color::Transparent);
}

//------------------------------------------------

CActor & CActor::SetSize(float InSize)
{
	Shape.setRadius(InSize / 2.f);
	Shape.setOrigin(InSize / 2.f, InSize / 2.f);
	return *this;
}

//------------------------------------------------

CActor & CActor::SetColor(const sf::Color & InColor)
{
	Shape.setOutlineColor(InColor);
	return *this;
}

//------------------------------------------------

void CActor::Render(CRenderQueue & RenderQueue)
{
	Shape.setPosition(GetPosition());
	RenderQueue.PushRenderCommand(Shape);
}

//------------------------------------------------

void CActor::Move(const sf::Vector2f & InOffset)
{
	Position += InOffset;
}

//------------------------------------------------

const sf::Vector2f & CActor::GetPosition() const
{
	return Position;
}

//------------------------------------------------
//------------------------------------------------
//------------------------------------------------
