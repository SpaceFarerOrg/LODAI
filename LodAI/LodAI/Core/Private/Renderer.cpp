#include "Core/Public/Renderer.h"

#include "MouseData.h"
#include "Core/Public/RenderQueue.h"

#include <SFML/Graphics/Sprite.hpp>

//--------------------------------------------------

void CRenderer::Initialize()
{
	CreateWindow();

	CMouseData::Instance().BindWindow(Window);
}

//--------------------------------------------------

void CRenderer::RegisterRenderQueue(CRenderQueue& InRenderQueue)
{
	RenderQueue = &InRenderQueue;
}

//--------------------------------------------------

void CRenderer::RenderAll()
{
	Window.clear();

	auto& Queue = RenderQueue->GetQueue();

	for (const auto& RenderCommand : Queue)
	{
		const sf::Shape* ShapeToRender = nullptr;

		bool IsShape = true;

		switch (RenderCommand.Shape)
		{
		case SRenderCommand::EShape::Circle:
			ShapeToRender = &(RenderCommand.CircleShape);
			break;
		case SRenderCommand::EShape::Rectangle:
			ShapeToRender = &(RenderCommand.RectangleShape);
			break;
		case SRenderCommand::EShape::Vertices:
			IsShape = false;
			break;
		default:
			break;
		}

		if (IsShape)
		{
			Window.draw(*ShapeToRender);
		}
		else
		{
			Window.draw(&RenderCommand.VertexArray[0], 2, sf::PrimitiveType::Lines);
		}
	}

	RenderQueue->ClearQueue();

	Window.display();
}

//--------------------------------------------------

void CRenderer::CreateWindow()
{
	sf::VideoMode VM = sf::VideoMode::getDesktopMode();
	VM.height = 800u;
	VM.width = 800u;
	sf::ContextSettings Settings;
	Settings.antialiasingLevel = 8;

	Window.create(VM, "LOD AI - Kasper & Joakim", sf::Style::Titlebar, Settings);
}

//--------------------------------------------------

sf::Window& CRenderer::GetWindow()
{
	return Window;
}

//--------------------------------------------------
//--------------------------------------------------
//--------------------------------------------------
