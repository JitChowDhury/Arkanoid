#include "Game.h"

Game::Game():window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Arkanoid"),paddle(window),deltaTime(0.f),ball(paddle),score(0),lives(100),state(State::PLAYING),scrollSpeed(100.f)
{
	window.setFramerateLimit(60);
	if (!backgroundTexture.loadFromFile("assets/textures/background.png"))
	{
		
	}
	backgroudSprite.setTexture(backgroundTexture);
	backgroudSprite2.setTexture(backgroundTexture);
	backgroudSprite2.setPosition(backgroundTexture.getSize().x, 0.f);
	sf::Vector2u textureSize = backgroundTexture.getSize();
	sf::Vector2u windowSize = window.getSize();
	

	
	float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
	float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

	backgroudSprite.setScale(scaleX, scaleY);
	backgroudSprite2.setScale(scaleX, scaleY);

	overlay.setSize((sf::Vector2f)window.getSize());
	overlay.setFillColor(sf::Color(0, 0, 0, 150));

	InitializeBricks(false);

	if (!font.loadFromFile("assets/fonts/VT323-Regular.ttf"))
	{

	}

	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10.f, 10.f);
	livesText.setFont(font);
	livesText.setCharacterSize(24);
	livesText.setFillColor(sf::Color::White);
	livesText.setPosition(900.f, 10.f);
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(48);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setPosition(300.f, 300.f);
}

void Game::Update()
{
	if (state != State::PLAYING)return;

	deltaTime = clock.restart().asSeconds();

	backgroudSprite.move(-scrollSpeed * deltaTime, 0.f);
	backgroudSprite2.move(-scrollSpeed * deltaTime, 0.f);


	if (backgroudSprite.getPosition().x + backgroundTexture.getSize().x < 0)
		backgroudSprite.setPosition(backgroudSprite2.getPosition().x + backgroundTexture.getSize().x, 0);

	if (backgroudSprite2.getPosition().x + backgroundTexture.getSize().x < 0)
		backgroudSprite2.setPosition(backgroudSprite.getPosition().x + backgroundTexture.getSize().x, 0);

	paddle.HandleEvents(deltaTime);
	paddle.Update(WINDOW_WIDTH);
	ball.Update(deltaTime,lives);

	for (auto& brick : bricks)
	{
		if (brick.IsActive() && ball.GetBounds().intersects(brick.GetBounds()))
		{
			brick.Destroy();
			score += 10;
			sf::Vector2f& velocity = ball.GetVelocity();
			velocity.y = -velocity.y;
			ball.SetVelocity(velocity);

			break;
		}
	}
	bool allBrickIsDestroyed = true;
	for (const auto& brick : bricks)
	{
		if (brick.IsActive())
		{
			allBrickIsDestroyed = false;
			break;
		}
	}
	if (allBrickIsDestroyed)
	{
		state = State::WON;
	}
	if (lives <= 0)
	{
		state = State::LOST;
	}

	scoreText.setString("Score: " + std::to_string(score));
	livesText.setString("Lives: " + std::to_string(lives));

	if (state == State::WON) {
		gameOverText.setString("You Win!");
	}
	else if (state == State::LOST) {
		gameOverText.setString("Game Over");
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
	window.draw(backgroudSprite2);
	window.draw(overlay);
	paddle.Render(window);
	ball.Render(window);
	for (const auto& brick : bricks) {
		brick.Draw(window);
	}
	window.draw(scoreText);
	window.draw(livesText);
	if (state != State::PLAYING) {
		window.draw(gameOverText);
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

int Game::GetScore() const
{
	 return score; 
}

State Game::GetGameState() const
{
	return State();
}

void Game::InitializeBricks(bool useFullSize) {
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
