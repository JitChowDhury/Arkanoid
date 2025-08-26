#include "Game.h"

Game::Game():window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Arkanoid"),paddle(window),deltaTime(0.f)
{
	window.setFramerateLimit(60);
	if (!backgroundTexture.loadFromFile("assets/textures/background.png"))
	{
		
	}
	backgroudSprite.setTexture(backgroundTexture);
	sf::Vector2u textureSize = backgroundTexture.getSize();
	sf::Vector2u windowSize = window.getSize();

	
	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	backgroudSprite.setScale(scaleX, scaleY);

	overlay.setSize((sf::Vector2f)window.getSize());
	overlay.setFillColor(sf::Color(0, 0, 0, 150));
}

void Game::Update()
{
	deltaTime = clock.restart().asSeconds();
	paddle.HandleEvents(deltaTime);
	paddle.Update(WINDOW_WIDTH);
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
	window.draw(backgroudSprite);
	window.draw(overlay);
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
