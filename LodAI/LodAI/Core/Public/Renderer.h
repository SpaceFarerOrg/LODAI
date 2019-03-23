#pragma once
#include <functional>
#include <SFML/Graphics/RenderWindow.hpp>
#include<vector>

struct SRenderCommand;
class CRenderQueue;

class CRenderer
{
public:
	CRenderer() = default;
	void Initialize();
	void RegisterRenderQueue(CRenderQueue& InRenderQueue);
	void RenderAll();

	sf::Window& GetWindow();
private:
	void CreateWindow();

	sf::RenderWindow Window;

	CRenderQueue* RenderQueue;
	
};