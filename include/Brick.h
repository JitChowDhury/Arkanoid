#include <SFML/Graphics.hpp>

class Brick
{
private:
	sf::Sprite brickSprite;
	static sf::Texture texture;
	bool active;
public:
	Brick(float x, float y, float width, float height, bool useSprite = true, float scaleX = 1.f, float scaleY = 1.f);
	void Draw(sf::RenderWindow& window) const;
	bool IsActive() const;
	void Destroy();
	sf::FloatRect GetBounds() const;


};