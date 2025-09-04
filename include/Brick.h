#pragma once
#include <SFML/Graphics.hpp>
class Brick
{
public:
	enum class BrickType
	{
		Standard,
		Strong,
		Purple,
		Green,
	};
private:
	sf::Sprite brickSprite;
	static sf::Texture standardTexture;
	static sf::Texture purpleTexture;
	static sf::Texture greenTexture;
	static sf::Texture strongTexture;
	static sf::Texture strongDamagedTexture;
	static sf::Texture purpleDamagedTexture;
	bool active;
	BrickType type;
	int hitPoints;
	int points;

public:
	Brick(float x, float y, BrickType t, float width, float height,
		bool useSprite = true, float scaleX = 1.f, float scaleY = 1.f);
	void Draw(sf::RenderWindow& window) const;
	bool IsActive() const;
	void Destroy();
	sf::FloatRect GetBounds() const;
	int hit();
	

};