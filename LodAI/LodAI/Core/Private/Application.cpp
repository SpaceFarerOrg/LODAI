#include "Core/Public/Application.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "Navigation/Public/TileWorldRepresentation.h"
#include "Navigation/Public/NodeGraphWorldRepresentation.h"

#include <SFML/Window/Event.hpp>

//--------------------------------------------------------------

namespace 
{
	void MakeMap(STileMap& TileMap, SNavigationNodes& NavNodes)
	{
		TileMap.MapDimension = 10;
		TileMap.TileDimension = 64;

		short Map[10 * 10] =
		{
		  //0,1,2,3,4,5,6,7,8,9
			1,1,1,1,1,1,1,1,1,1,//0
			1,0,0,0,1,0,0,0,0,1,//1
			1,0,0,0,0,0,0,0,0,1,//2
			1,0,0,0,1,0,0,0,0,1,//3
			1,1,1,0,1,1,1,1,0,1,//4
			1,0,0,0,1,0,0,0,0,1,//5
			1,0,0,0,0,0,0,0,0,1,//6
			1,1,0,1,1,1,1,0,1,1,//7
			1,0,0,0,0,0,0,0,0,1,//8
			1,1,1,1,1,1,1,1,1,1 //9
		};

		TileMap.TileData.reserve(TileMap.MapDimension * TileMap.MapDimension);

		for (int i = 0; i < 100; ++i)
		{
			TileMap.TileData.push_back(Map[i]);
		}

		SNavigationNodes::SNavNode Node;

		//Node 0 (2,2) N: 1
		Node.Links.push_back(1);
		Node.Position = sf::Vector2f(2.f, 2.f) * 64.f;
		NavNodes.NavNodeData.push_back(Node);

		Node.Links.clear();

		//Node 1 (3,2) N: 0, 2
		Node.Links.push_back(0);
		Node.Links.push_back(2);
		Node.Position = sf::Vector2f(3.f, 2.f) * 64.f;
		NavNodes.NavNodeData.push_back(Node);

		Node.Links.clear();

		//Node 2 (8,2) N: 1, 3 
		Node.Links.push_back(1);
		Node.Links.push_back(3);
		Node.Position = sf::Vector2f(8.f, 2.f) * 64.f;
		NavNodes.NavNodeData.push_back(Node);

		Node.Links.clear();

		//Node 3 (8,6) N: 2, 8
		Node.Links.push_back(2);
		Node.Links.push_back(8);
		Node.Position = sf::Vector2f(8.f, 6.f) * 64.f;
		NavNodes.NavNodeData.push_back(Node);

		Node.Links.clear();

		//Node 4 (3,6) N: 1, 8
		Node.Links.push_back(1);
		Node.Links.push_back(8);
		Node.Position = sf::Vector2f(3.f, 6.f) * 64.f;
		NavNodes.NavNodeData.push_back(Node);

		Node.Links.clear();

		//Node 5 (2,6) N: 4, 6
		Node.Links.push_back(4);
		Node.Links.push_back(6);
		Node.Position = sf::Vector2f(2.f, 6.f) * 64.f;
		NavNodes.NavNodeData.push_back(Node);

		Node.Links.clear();

		//Node 6 (2,8) N: 5, 7
		Node.Links.push_back(5);
		Node.Links.push_back(7);
		Node.Position = sf::Vector2f(2.f, 8.f) * 64.f;
		NavNodes.NavNodeData.push_back(Node);

		Node.Links.clear();

		//Node 7 (7,8) N: 6, 8
		Node.Links.push_back(6);
		Node.Links.push_back(8);
		Node.Position = sf::Vector2f(7.f, 8.f) * 64.f;
		NavNodes.NavNodeData.push_back(Node);

		Node.Links.clear();

		//Node 8 (7,6) N: 7, 4
		Node.Links.push_back(7);
		Node.Links.push_back(4);
		Node.Position = sf::Vector2f(7.f, 6.f) * 64.f;
		NavNodes.NavNodeData.push_back(Node);
	}
}

//--------------------------------------------------------------

CApplication::CApplication(bool& InShouldRun)
	: ShouldRun(InShouldRun)
{
}

//--------------------------------------------------------------

void CApplication::Initialize()
{
	Renderer.Initialize();
	Renderer.RegisterRenderQueue(RenderQueue);

	STileMap TileMap;
	SNavigationNodes NavNodes;
	MakeMap(TileMap, NavNodes);

	World.BuildWorld(TileMap, NavNodes, PlayerActor);

	//Create AI
	AIActor.SetSize(40.f).SetColor(sf::Color::Blue);
	AIActor.Move(sf::Vector2f(148.f, 148.f));
	AIController.SetMovementSpeed(50.f);
	AIController.AttachMoveFunction([&](const sf::Vector2f& InMove) {AIActor.Move(InMove); });
	AIController.AttachGetPositionFunc([&]() { return AIActor.GetPosition(); });

	//Create Player
	PlayerActor.SetSize(64.f).SetColor(sf::Color::Green);
	PlayerController.SetMovementSpeed(100.f);
	PlayerController.AttachMoveFunction([&](const sf::Vector2f& InMove) { PlayerActor.Move(InMove); });
}

//--------------------------------------------------------------

void CApplication::Tick()
{
	const float DeltaTime = GetTickTimeDelta();
	CheckForWindowEvents();
	
	AIController.SetWorldRepresentation(World.GetCurrentWorldRepresentation(AIActor.GetPosition()));

	PlayerController.Tick(DeltaTime);
	AIController.Tick(DeltaTime);

	World.Render(RenderQueue);
	PlayerActor.Render(RenderQueue);
	AIActor.Render(RenderQueue);

	Renderer.RenderAll();
}

//--------------------------------------------------------------

float CApplication::GetTickTimeDelta()
{
	const float TimeDelta = Clock.getElapsedTime().asSeconds();
	Clock.restart();

	return TimeDelta;
}

//--------------------------------------------------------------

void CApplication::CheckForWindowEvents()
{
	sf::Window& ApplicationWindow = Renderer.GetWindow();

	sf::Event e;
	while (ApplicationWindow.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			ShouldRun = false;
		}

		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Key::Num1)
			{
				World.ToggleRenderNavData();
			}
		}
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------