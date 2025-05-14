#include <SFML/Graphics.hpp>

const int Width = 800;
const int Height = 600;
const int Grid = 20;

int main() {
    sf::RenderWindow window(sf::VideoMode(Width, Height), "Snake Game");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
