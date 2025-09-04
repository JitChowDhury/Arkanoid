#pragma once
#include <SFML/Graphics.hpp>
#include "paddle.h"



class Ball
{
private:
	float speed;
	static sf::Texture ballTexture;
	sf::Sprite ballSprite;
	sf::Vector2f ballVelocity;
	sf::Vector2f ballStartPos;
	Paddle* paddle;
	bool active;

public:
	Ball(Paddle* paddle);


	void Update(float dt, int& lives);
	void Render(sf::RenderWindow& window) const;
	sf::FloatRect GetBounds();
	//sf::Vector2f GetVelocity();

	void Reset();
	bool IsActive() const { return active; }
	sf::Vector2f& GetVelocity() { return ballVelocity; }
	const sf::Vector2f& GetVelocity() const { return ballVelocity; }
	void SetVelocity(const sf::Vector2f& v);

};