#include <SFML/Graphics.hpp>

class Paddle
{
private:
	sf::Texture paddleTexture;
	sf::Sprite paddleSprite;
public:
	Paddle(sf::RenderWindow& window);
	void HandleEvents(float dt);
	void Update(int windowWidth);
	void Render(sf::RenderWindow& window);
};