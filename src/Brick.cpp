#include "Brick.h"

sf::Texture Brick::standardTexture;
sf::Texture Brick::strongTexture;
sf::Texture Brick::strongDamagedTexture;

Brick::Brick(float x, float y, BrickType t, float width, float height, bool useSprite, float scaleX, float scaleY)
    : active(true), type(t), hitPoints(0), points(0)
{
    if (useSprite) {
        if (standardTexture.getSize().x == 0)
            standardTexture.loadFromFile("assets/textures/brick_standard.png");

        if (strongTexture.getSize().x == 0)
            strongTexture.loadFromFile("assets/textures/brick_strong.png");

        if (strongDamagedTexture.getSize().x == 0)
            strongDamagedTexture.loadFromFile("assets/textures/brick_strong_damaged.png");

        switch (type) {
        case BrickType::Standard:
            brickSprite.setTexture(standardTexture);
            hitPoints = 1;
            points = 10;
            break;
        case BrickType::Strong:
            brickSprite.setTexture(strongTexture);
            hitPoints = 2;
            points = 20;
            break;
        }

        brickSprite.setPosition(x, y);
        brickSprite.setScale(scaleX, scaleY);
    }
}

void Brick::Draw(sf::RenderWindow& window) const
{
	if (active) window.draw(brickSprite);
}

bool Brick::IsActive() const
{ 
	return active;
}

void Brick::Destroy()
{
	active = false;
}

sf::FloatRect Brick::GetBounds() const
{
	return brickSprite.getGlobalBounds();
}

int Brick::hit()
{
	if (!active) return 0;
	if (hitPoints > 0) {
		hitPoints--;

		if (type == BrickType::Strong && hitPoints == 1)
		{
			brickSprite.setTexture(strongDamagedTexture, true);
		}
		if (hitPoints == 0) {
			active = false;
			return points;
		}
	}
	return 0;
}


