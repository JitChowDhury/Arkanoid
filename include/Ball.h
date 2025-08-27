#pragma once
#include <SFML/Graphics.hpp>
#include "paddle.h"



class Ball
{
private:
	float speed;
	sf::Texture ballTexture;
	sf::Sprite ballSprite;
	sf::Vector2f ballVelocity;
	sf::Vector2f ballStartPos;
	const Paddle& paddle;

public:
	Ball(const Paddle& paddle);
	void Update(float dt);
	void Render(sf::RenderWindow& window);
	

};