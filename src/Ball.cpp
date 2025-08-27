#include <iostream>
#include "Ball.h"


Ball::Ball(const Paddle& paddle):paddle(paddle)
{
	if (!ballTexture.loadFromFile("assets/textures/ball.png"))
	{
		std::cout << "Ball sprite not loaded" << std::endl;
	}
	ballSprite.setTexture(ballTexture);
	ballSprite.setScale(0.35f, 0.35f);


	sf::Vector2f pos = paddle.GetPosition();
	sf::FloatRect bounds = ballSprite.getLocalBounds();

	sf::Vector2f paddlePos = paddle.GetPosition();
	sf::FloatRect paddleBounds = paddle.getGlobalBounds(); 
	ballSprite.setOrigin(
		ballSprite.getLocalBounds().width / 2.f,
		ballSprite.getLocalBounds().height / 2.f
	);
	float paddleCenterX = paddlePos.x + paddleBounds.width / 2.f;
	float paddleTopY = paddlePos.y;
	ballSprite.setPosition(paddleCenterX, paddleTopY - bounds.height / 2.f);

	
	


}



void Ball::Update(float dt)
{
	ballSprite.move(ballVelocity * dt);
}

void Ball::Render(sf::RenderWindow& window)
{
	window.draw(ballSprite);
}

