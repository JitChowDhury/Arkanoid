#include <SFML/Graphics.hpp>
#include "paddle.h"

class Game
{
private:
	//1024 × 768
	const unsigned int WINDOW_WIDTH{ 1024 };
	const unsigned int WINDOW_HEIGHT{ 768 };

	sf::RenderWindow window;
	Paddle paddle;
	
public:
	Game();
	void Update();
	void HandleEvent();
	void Render();
	void Run();

};