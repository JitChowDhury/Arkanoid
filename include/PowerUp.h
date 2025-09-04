
#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"


enum PowerUpType { ExpandPaddle, MultiBall };
class Game;
class PowerUp {
private:
    static sf::Sprite sprite;
    sf::Texture texture;
    PowerUpType type;
    bool active = true;
    sf::Vector2f velocity{ 0.f, 200.f }; 
public:
    PowerUp(float x, float y, PowerUpType t);
    void Update(float dt, Paddle& paddle, Game& game);
    void Apply(Game& game);
    void Draw(sf::RenderWindow& window) const;
    sf::FloatRect GetBounds() const;
    bool IsActive() const { return active; }
};