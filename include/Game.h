#include <SFML/Graphics.hpp>
#include "paddle.h"
#include "Ball.h"

class Game
{
private:
	//1024 × 768
	const unsigned int WINDOW_WIDTH{ 1024 };
	const unsigned int WINDOW_HEIGHT{ 768 };
	float deltaTime;
	sf::RenderWindow window;
	sf::Clock clock;

	sf::RectangleShape overlay;
	sf::Texture backgroundTexture;
	sf::Sprite backgroudSprite;
	Paddle paddle;
	Ball ball;
	
public:
	Game();
	void Update();
	void HandleEvent();
	void Render();
	void Run();

};