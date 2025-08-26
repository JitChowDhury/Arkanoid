#include "Game.h"

Game::Game():window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Arkanoid"),paddle(window),deltaTime(0.f)
{
	window.setFramerateLimit(60);
}

void Game::Update()
{
	deltaTime = clock.restart().asSeconds();
	paddle.HandleEvents(deltaTime);
}

void Game::HandleEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			window.close();
		}
	
	}
}

void Game::Render()
{
	window.clear();
	paddle.Render(window);
	window.display();
}

void Game::Run()
{

	while (window.isOpen())
	{
		Update();
		HandleEvent();
		Render();

		
	}
}
