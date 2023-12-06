#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "LevelSystem.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");

    // Load level file
    try
    {
        LevelSystem::loadLevelFile("docs/level.txt", 100.0f);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    Player player;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        double dt = clock.restart().asSeconds();

        player.update(dt);

        window.clear();
        LevelSystem::render(window);
        player.render(window);
        window.display();
    }

    return EXIT_SUCCESS;
}
