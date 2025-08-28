#include "Brick.h"

sf::Texture Brick::texture;

Brick::Brick(float x, float y, float width, float height, bool useSprite, float scaleX, float scaleY):active(true)
{
	if (useSprite) {
		if (!texture.loadFromFile("assets/textures/brick.png")) {  }
		brickSprite.setTexture(texture);
		brickSprite.setPosition(x, y);
		brickSprite.setScale(scaleX, scaleY); // For scaling
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
