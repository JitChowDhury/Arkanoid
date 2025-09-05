#pragma once
#include <SFML/Graphics.hpp>
#include<vector>

class Paddle
{
private:
	std::vector<sf::Texture> paddleFrames;
	//sf::Texture paddleTexture;
	sf::Texture paddleLargeTexture;
	sf::Sprite paddleSprite;

	sf::Vector2f startPosition;


	float baseWidth = 170.f;   // original target width
	float baseHeight = 50.f;   // original target height
	float currentScaleFactor = 1.f; // multiplier for scaling 



	float animationTimer = 0.f;
	float frameDuration = 0.15f; 
	int currentFrame = 0;
public:
	Paddle(sf::RenderWindow& window);
	void HandleEvents(float dt);
	void Update(int windowWidth,float dt);
	void Render(sf::RenderWindow& window);
	sf::Vector2f GetPosition() const;
	sf::FloatRect GetGlobalBounds() const;
	void SetScale(float x, float y) { paddleSprite.setScale(x, y); }
	sf::Vector2f GetScale();
	void SetSprite();
	void SetScaleFactor(float factor);

};