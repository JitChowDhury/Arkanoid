#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Arkanoid");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type==sf::Event::Closed || (event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
