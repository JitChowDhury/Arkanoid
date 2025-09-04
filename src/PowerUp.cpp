#include "PowerUp.h"
#include "Game.h" 
sf::Sprite PowerUp::sprite;
PowerUp::PowerUp(float x, float y, PowerUpType t) : type(t) {
    std::string textureFile;

    if (type == ExpandPaddle) {
        textureFile = "assets/textures/powerup_expand.png";
    }
    else if (type == MultiBall) {
        textureFile = "assets/textures/powerup_multiball.png";
    }

    if (!texture.loadFromFile(textureFile)) {
        // Handle error: maybe fallback to a default texture
    }
    sprite.setTexture(texture);
    sprite.setScale(0.350515f, 0.390625427f);
    sprite.setPosition(x, y);

}

void PowerUp::Update(float dt, Paddle& paddle, Game& game) {
    if (!active) return;
    sprite.move(velocity * dt);
    if (sprite.getGlobalBounds().intersects(paddle.GetGlobalBounds())) { // Fixed to match Paddle method
        Apply(game);
        active = false;
    }
    if (sprite.getPosition().y > 768.f) active = false;
}

void PowerUp::Apply(Game& game) {
    if (type == ExpandPaddle && !game.paddleExpanded) {
        game.GetPaddle().SetSprite();
        game.paddleExpanded = true;
        game.powerUpTimer.restart();
    }
    else if (type == MultiBall && game.GetBalls().size() < 3) {
        sf::Vector2f pos(game.GetBalls()[0].GetBounds().left,
            game.GetBalls()[0].GetBounds().top);
        game.GetBalls().emplace_back(&game.GetPaddle());
        game.GetBalls().back().GetVelocity().x += (rand() % 100 - 50);
    }
}

void PowerUp::Draw(sf::RenderWindow& window) const {
    if (active) window.draw(sprite);
}

sf::FloatRect PowerUp::GetBounds() const {
    return sprite.getGlobalBounds();
}