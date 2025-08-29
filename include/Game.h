#include <SFML/Graphics.hpp>
#include <vector>
#include "paddle.h"
#include "Ball.h"
#include "Brick.h"

enum class State { PLAYING, WON, LOST };
class Game
{
private:
	//1024 × 768
	const unsigned int WINDOW_WIDTH{ 1024 };
	const unsigned int WINDOW_HEIGHT{ 768 };
	float deltaTime;
	int score;
	int lives;
	sf::RenderWindow window;
	sf::Clock clock;

	sf::RectangleShape overlay;
	sf::Texture backgroundTexture;
	sf::Sprite backgroudSprite;

	
	Paddle paddle;
	Ball ball;
	std::vector<Brick> bricks;
	State state;
	
public:
	Game();
	void Update();
	void HandleEvent();
	void Render();
	void Run();
	void InitializeBricks(bool useFullSize);
	int GetScore() const;
	State GetGameState() const;

};