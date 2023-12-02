#include <SFML/Graphics.hpp>
#include <Player.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");

    // Crear un jugador
    Player player;

    // Bucle principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualizar el jugador con el tiempo transcurrido desde el último fotograma
        player.update(0.016); // Utiliza un valor adecuado para el tiempo delta

        // Limpiar la ventana
        window.clear();

        // Renderizar el jugador
        player.render(window);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}
