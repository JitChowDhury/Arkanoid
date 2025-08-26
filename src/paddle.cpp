#include<iostream>
#include "paddle.h"

Paddle::Paddle(sf::RenderWindow& window)
{
	if (!paddleTexture.loadFromFile("assets/textures/player.png"))
	{
		std::cout << "Error Loading Paddle Sprite" << std::endl;
	}
	paddleSprite.setTexture(paddleTexture);
	
	float desiredWidth = 170.f;  
	float desiredHeight = 50.f;   

	float scaleX = desiredWidth / paddleTexture.getSize().x;
	float scaleY = desiredHeight / paddleTexture.getSize().y;

	paddleSprite.setScale(scaleX, scaleY);

	//acutual width after scale
	float paddleWidth = paddleTexture.getSize().x * scaleX;
	float paddleHeight = paddleTexture.getSize().y * scaleY;

	// position centered horizontally, a bit above bottom
	float x = window.getSize().x / 2.f - paddleWidth / 2.f;
	float y = window.getSize().y - paddleHeight - 20.f; // 20px gap from bottom

	paddleSprite.setPosition(x, y);
}

void Paddle::Render(sf::RenderWindow& window)
{
	window.draw(paddleSprite);
}
