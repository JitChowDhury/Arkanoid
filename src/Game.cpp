#include "Game.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid"),
    paddle(window), deltaTime(0.f), score(0), lives(2), state(State::PLAYING), scrollSpeed(100.f)
{
    balls.emplace_back(&paddle);
    window.setFramerateLimit(60);
    if (!backgroundTexture.loadFromFile("assets/textures/background.png"))
    {

    }
    backgroudSprite.setTexture(backgroundTexture);
    backgroudSprite2.setTexture(backgroundTexture);
    backgroudSprite2.setPosition(backgroundTexture.getSize().x, 0.f);
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroudSprite.setScale(scaleX, scaleY);
    backgroudSprite2.setScale(scaleX, scaleY);

    overlay.setSize((sf::Vector2f)window.getSize());
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    if (!brickHitBuffer1.loadFromFile("assets/sounds/hit1.wav")) {

    }
    if (!brickHitBuffer2.loadFromFile("assets/sounds/hit2.wav")) {

    }

    brickHitSound1.setBuffer(brickHitBuffer1);
    brickHitSound2.setBuffer(brickHitBuffer2);

    if (!backgroundMusic.openFromFile("assets/sounds/bg.mp3")) {

    }

    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(50.f);
    backgroundMusic.play();

    InitializeBricks();

    if (!font.loadFromFile("assets/fonts/VT323-Regular.ttf"))
    {

    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);

    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(900.f, 10.f);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::White);
    // REMOVED fixed position here – will center dynamically later
}

void Game::Update()
{
    if (state != State::PLAYING) return;

    deltaTime = clock.restart().asSeconds();

    backgroudSprite.move(-scrollSpeed * deltaTime, 0.f);
    backgroudSprite2.move(-scrollSpeed * deltaTime, 0.f);

    if (backgroudSprite.getPosition().x + backgroundTexture.getSize().x < 0)
        backgroudSprite.setPosition(backgroudSprite2.getPosition().x + backgroundTexture.getSize().x, 0);

    if (backgroudSprite2.getPosition().x + backgroundTexture.getSize().x < 0)
        backgroudSprite2.setPosition(backgroudSprite.getPosition().x + backgroundTexture.getSize().x, 0);

    paddle.HandleEvents(deltaTime);
    paddle.Update(WINDOW_WIDTH, deltaTime);

    for (auto it = balls.begin(); it != balls.end();) {
        it->Update(deltaTime, lives);
        if (!it->IsActive()) it = balls.erase(it);
        else ++it;
    }

    bool allBallsInactive = true;
    for (const auto& ball : balls) {
        if (ball.IsActive()) allBallsInactive = false;
    }
    if (allBallsInactive && !balls.empty()) {
        lives--;
        balls[0].Reset();
    }

    for (auto& brick : bricks) {
        if (!brick.IsActive()) continue;
        for (auto& ball : balls) {
            if (ball.IsActive() && ball.GetBounds().intersects(brick.GetBounds())) {
                int points = brick.hit();
                float randomPitch = 0.9f + static_cast<float>(rand()) / RAND_MAX * 0.2f;
                if (rand() % 2 == 0) {
                    brickHitSound1.setPitch(randomPitch);
                    brickHitSound1.play();
                }
                else {
                    brickHitSound2.setPitch(randomPitch);
                    brickHitSound2.play();
                }
                if (points > 0) {
                    float x = brick.GetBounds().left + brick.GetBounds().width / 2;
                    float y = brick.GetBounds().top + brick.GetBounds().height / 2;
                    SpawnPowerUp(x, y);
                }
                sf::Vector2f velocity = ball.GetVelocity();
                velocity.y = -velocity.y;
                ball.SetVelocity(velocity);
                break;
            }
        }
    }

    for (auto it = powerUps.begin(); it != powerUps.end();) {
        it->Update(deltaTime, paddle, *this);
        if (!it->IsActive()) it = powerUps.erase(it);
        else ++it;
    }

    if (paddleExpanded && powerUpTimer.getElapsedTime().asSeconds() > 10.f) {
        paddle.SetScaleFactor(1.0f);
        paddleExpanded = false;
    }

    bool allBrickIsDestroyed = true;
    for (const auto& brick : bricks) {
        if (brick.IsActive()) {
            allBrickIsDestroyed = false;
            break;
        }
    }
    if (allBrickIsDestroyed) {
        state = State::WON;
    }
    if (lives <= 0) {
        state = State::LOST;
    }

    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(lives));

    if (state == State::WON) {
        gameOverText.setString("You Win! Press R to Restart");  //  Added restart text
    }
    else if (state == State::LOST) {
        gameOverText.setString("Game Over! Press R to Restart"); //  Added restart text
    }

    // CENTER the text dynamically
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    gameOverText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
}

void Game::HandleEvent()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }

       
        if (state != State::PLAYING && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            RestartGame();
        }
    }
}

void Game::Render()
{
    window.clear();
    window.draw(backgroudSprite);
    window.draw(backgroudSprite2);
    window.draw(overlay);
    paddle.Render(window);

    for (const Ball& ball : balls) ball.Render(window);
    for (const auto& brick : bricks) brick.Draw(window);
    for (const auto& powerUp : powerUps) powerUp.Draw(window);

    window.draw(scoreText);
    window.draw(livesText);

    if (state != State::PLAYING) {
        window.draw(gameOverText);
    }

    window.display();
}

void Game::Run()
{
    while (window.isOpen())
    {
        HandleEvent();
        Update();
        Render();
    }
}

int Game::GetScore() const
{
    return score;
}

State Game::GetGameState() const
{
    return State();
}

void Game::SpawnPowerUp(float x, float y) {
    if (rand() % 5 == 0) {
        PowerUpType type = (rand() % 2 == 0) ? ExpandPaddle : MultiBall;
        powerUps.emplace_back(x, y, type);
    }
}

void Game::InitializeBricks() {
    bricks.clear();
    int rows = 8;
    int cols = 7;
    float width = 128.f;
    float height = 48.f;
    float scaleX = 0.333f;
    float scaleY = 0.375f;
    float offsetX = (1024.f - (cols * (width + 5.f) - 5.f)) / 2;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            Brick::BrickType type = (row >= 2)
                ? ((row >= 4) ? ((row >= 6) ? Brick::BrickType::Standard : Brick::BrickType::Purple) : Brick::BrickType::Green)
                : Brick::BrickType::Strong;
            bricks.emplace_back(col * (width + 5.f) + offsetX, row * (height + 5.f), type,
                width, height, true, scaleX, scaleY);

        }
    }
}


void Game::RestartGame() {
    score = 0;
    lives = 5;
    state = State::PLAYING;
    paddle.ResetPosition(window);
    balls.clear();
    balls.emplace_back(&paddle);
    balls.back().Reset();  
    paddle.SetScaleFactor(1.0f);
    paddleExpanded = false;
    powerUps.clear();
    InitializeBricks();
}
