#include "Core/Public/RenderQueue.h"

//------------------------------------------------------------

void CRenderQueue::PushRenderCommand(const sf::CircleShape& InCircleShape)
{
	Commands.push_back(SRenderCommand(InCircleShape));
}

//------------------------------------------------------------


void CRenderQueue::PushRenderCommand(const sf::RectangleShape & InRectangleShape)
{
	Commands.push_back(SRenderCommand(InRectangleShape));
}

//------------------------------------------------------------

void CRenderQueue::PushRenderCommand(const FVertexArray& InVertexArray)
{
	Commands.push_back(SRenderCommand(InVertexArray));
}

//------------------------------------------------------------

void CRenderQueue::ClearQueue()
{
	Commands.clear();
}

//------------------------------------------------------------

const std::vector<SRenderCommand>& CRenderQueue::GetQueue() const
{
	return Commands;
}

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------