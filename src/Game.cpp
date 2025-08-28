#include "Game.h"

Game::Game():window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Arkanoid"),paddle(window),deltaTime(0.f),ball(paddle)
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

	initializeBricks(false);
}

void Game::Update()
{
	deltaTime = clock.restart().asSeconds();
	paddle.HandleEvents(deltaTime);
	paddle.Update(WINDOW_WIDTH);
	ball.Update(deltaTime);

	for (auto& brick : bricks)
	{
		if (brick.IsActive() && ball.GetBounds().intersects(brick.GetBounds()))
		{
			brick.Destroy();
			sf::Vector2f& velocity = ball.GetVelocity();
			velocity.y = -velocity.y;

			break;
		}
	}
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
	ball.Render(window);
	for (const auto& brick : bricks) {
		brick.Draw(window);
	}
	window.display();
}

void Game::Run()
{

	while (window.isOpen())
	{
		HandleEvent();
		Update();
		Render();

		
	}
}

void Game::initializeBricks(bool useFullSize) {
	bricks.clear();
	int rows = useFullSize ? 3 : 8;
	int cols = useFullSize ? 2 : 7;
	float width = useFullSize ? 384.f : 128.f;
	float height = useFullSize ? 128.f : 48.f;
	float scaleX = useFullSize ? 1.f : 0.333f;
	float scaleY = useFullSize ? 1.f : 0.375f;
	float offsetX = (1024.f - (cols * (width + 5.f) - 5.f)) / 2;
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			bricks.emplace_back(col * (width + 5.f) + offsetX, row * (height + 5.f),
				width, height, true, scaleX, scaleY);
		}
	}
}
