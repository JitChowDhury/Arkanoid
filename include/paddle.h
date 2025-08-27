#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
private:
	sf::Texture paddleTexture;
	sf::Sprite paddleSprite;
	sf::Vector2f startPosition;
public:
	Paddle(sf::RenderWindow& window);
	void HandleEvents(float dt);
	void Update(int windowWidth);
	void Render(sf::RenderWindow& window);
	sf::Vector2f GetPosition() const;
	sf::FloatRect getGlobalBounds() const;

};