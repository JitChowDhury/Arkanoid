#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "PowerUp.h"
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
	float scrollSpeed;
	int score;
	int lives;
	
	sf::RenderWindow window;
	sf::Clock clock;

	sf::RectangleShape overlay;
	sf::Texture backgroundTexture;
	sf::Sprite backgroudSprite;
	sf::Sprite backgroudSprite2;
	sf::Font font;
	sf::Text scoreText;
	sf::Text livesText;
	sf::Text gameOverText;

	sf::SoundBuffer brickHitBuffer1;
	sf::SoundBuffer brickHitBuffer2;

	sf::Sound brickHitSound1;
	sf::Sound brickHitSound2;

	sf::Music backgroundMusic;

	
	Paddle paddle;
	std::vector<Ball> balls; 
	std::vector<Brick> bricks;
	std::vector<PowerUp> powerUps;
	State state;
	
public:
	sf::Clock powerUpTimer;
	bool paddleExpanded = false;
	Game();
	void Update();
	void HandleEvent();
	void Render();
	void Run();
	void InitializeBricks();
	int GetScore() const;
	State GetGameState() const;
	void SpawnPowerUp(float x, float y); 
	Paddle& GetPaddle() { return paddle; } 
	std::vector<Ball>& GetBalls() { return balls; } 
	void RestartGame();
};