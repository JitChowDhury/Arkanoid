#include<iostream>
#include "paddle.h"


Paddle::Paddle(sf::RenderWindow& window)
{
	std::vector<std::string> textureFiles = {
	"assets/textures/player.png",
	"assets/textures/paddleAnim1.png",
	"assets/textures/paddleAnim2.png"
	};

	for (auto& file : textureFiles)
	{
		sf::Texture tex;
		if (!tex.loadFromFile(file))
		{
			std::cout << "Error loading texture: " << file << std::endl;
		}
		paddleFrames.push_back(tex);
	}

	paddleSprite.setTexture(paddleFrames[0]);

	//if (!paddleTexture.loadFromFile("assets/textures/player.png"))
	//{
	//	std::cout << "Error Loading Paddle Sprite" << std::endl;
	//}
	if (!paddleLargeTexture.loadFromFile("assets/textures/paddleLarge.png"))
	{
		std::cout << "Error Loading Paddle Sprite" << std::endl;
	}
	
	
	float desiredWidth = 170.f;  
	float desiredHeight = 50.f;   

	float scaleX = desiredWidth / paddleFrames[0].getSize().x;
	float scaleY = desiredHeight / paddleFrames[0].getSize().y;
	

	paddleSprite.setScale(scaleX, scaleY);
	std::cout << "Scale: " << scaleX << " " << scaleY;

	//acutual width after scale
	float paddleWidth = paddleFrames[0].getSize().x * scaleX;
	float paddleHeight = paddleFrames[0].getSize().y * scaleY;

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



void Paddle::Update(int windowWidth,float dt)
{
	// animate
	animationTimer += dt;
	if (animationTimer >= frameDuration)
	{
		animationTimer = 0.f;
		currentFrame = (currentFrame + 1) % paddleFrames.size();
		paddleSprite.setTexture(paddleFrames[currentFrame], true);
	}




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

void Paddle::SetScaleFactor(float factor)
{
	currentScaleFactor = factor;

	float scaleX = (baseWidth * factor) / paddleFrames[0].getSize().x;
	float scaleY = (baseHeight * factor) / paddleFrames[0].getSize().y;

	paddleSprite.setScale(scaleX, scaleY);
}
