#include<iostream>
#include "paddle.h"


Paddle::Paddle(sf::RenderWindow& window)
{
	if (!paddleTexture.loadFromFile("assets/textures/player.png"))
	{
		std::cout << "Error Loading Paddle Sprite" << std::endl;
	}
	if (!paddleLargeTexture.loadFromFile("assets/textures/paddleLarge.png"))
	{
		std::cout << "Error Loading Paddle Sprite" << std::endl;
	}
	paddleSprite.setTexture(paddleTexture);
	
	float desiredWidth = 170.f;  
	float desiredHeight = 50.f;   

	float scaleX = desiredWidth / paddleTexture.getSize().x;
	float scaleY = desiredHeight / paddleTexture.getSize().y;
	

	paddleSprite.setScale(scaleX, scaleY);
	std::cout << "Scale: " << scaleX << " " << scaleY;

	//acutual width after scale
	float paddleWidth = paddleTexture.getSize().x * scaleX;
	float paddleHeight = paddleTexture.getSize().y * scaleY;

	// position centered horizontally, a bit above bottom
	float x = window.getSize().x / 2.f - paddleWidth / 2.f;
	float y = window.getSize().y - paddleHeight - 20.f; // 20px gap from bottom

	paddleSprite.setPosition(x, y);
	startPosition = sf::Vector2f(x, y);
	std::cout << x << " " << y << std::endl;
}

void Paddle::HandleEvents(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		paddleSprite.move(700.f * dt, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		paddleSprite.move(-700.f * dt, 0.f);
	}
}



void Paddle::Update(int windowWidth)
{
	sf::Vector2f pos = paddleSprite.getPosition();
	float width = paddleSprite.getGlobalBounds().width;
	if (pos.x < 5)paddleSprite.setPosition(5, pos.y);
	if (pos.x + width > windowWidth - 5) paddleSprite.setPosition(windowWidth - 5 - width, pos.y);
}

void Paddle::Render(sf::RenderWindow& window)
{
	window.draw(paddleSprite);
	
}

sf::Vector2f Paddle::GetPosition() const
{
	return startPosition;
}

sf::FloatRect Paddle::GetGlobalBounds() const
{
	return paddleSprite.getGlobalBounds();
}

sf::Vector2f Paddle::GetScale()
{
	return	paddleSprite.getScale();
}

void Paddle::SetSprite()
{
	paddleSprite.setTexture(paddleLargeTexture, true);
}
