#include <iostream>
#include "Ball.h"


Ball::Ball(const Paddle& paddle):paddle(paddle),speed(2.f)
{
	if (!ballTexture.loadFromFile("assets/textures/ball.png"))
	{
		std::cout << "Ball sprite not loaded" << std::endl;
	}
	ballVelocity = sf::Vector2f(-150.f, -150.f);

	ballSprite.setTexture(ballTexture);
	ballSprite.setScale(0.35f, 0.35f);


	sf::Vector2f pos = paddle.GetPosition();
	sf::FloatRect bounds = ballSprite.getLocalBounds();
	ballSprite.setOrigin(
		ballSprite.getLocalBounds().width / 2.f,
		ballSprite.getLocalBounds().height / 2.f
	);

	sf::Vector2f paddlePos = paddle.GetPosition();
	sf::FloatRect paddleBounds = paddle.GetGlobalBounds();

	float paddleCenterX = paddlePos.x + paddleBounds.width / 2.f;
	float paddleTopY = paddlePos.y;
	ballSprite.setPosition(paddleCenterX, paddleTopY - bounds.height / 2.f);
	ballStartPos = sf::Vector2f(paddleCenterX, paddleTopY - bounds.height / 2.f);

	
	


}



void Ball::Update(float dt, int& lives)
{
	ballSprite.move(ballVelocity *speed* dt);
	sf::FloatRect ballBounds = ballSprite.getGlobalBounds();
	if (ballBounds.left < 0) {
		ballVelocity.x = std::abs(ballVelocity.x); // Bounce right
	}
	if (ballBounds.left + ballBounds.width > 1024) {
		ballVelocity.x = -std::abs(ballVelocity.x); // Bounce left
	}
	if (ballBounds.top < 0) {
		ballVelocity.y = std::abs(ballVelocity.y); // Bounce down
	}
	if (ballBounds.top + ballBounds.height > 768) {
		ballSprite.setPosition(ballStartPos); // Reset
		lives--;
		ballVelocity = sf::Vector2f(-150.f, -150.f);
	}

	if (ballSprite.getGlobalBounds().intersects(paddle.GetGlobalBounds()))
	{
		ballVelocity.y = -std::abs(ballVelocity.y);
		float hitPoint = (ballBounds.left + ballBounds.width / 2) -
			(paddle.GetGlobalBounds().left + paddle.GetGlobalBounds().width / 2);
		ballVelocity.x = hitPoint * 2.f;

	}
}

void Ball::Render(sf::RenderWindow& window)
{
	window.draw(ballSprite);
}

sf::FloatRect Ball::GetBounds()
{
	return ballSprite.getGlobalBounds();
}

sf::Vector2f Ball::GetVelocity()
{
	return ballVelocity;
}

void Ball::SetVelocity(const sf::Vector2f& v)
{
	ballVelocity = v;
}

