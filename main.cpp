#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Player.hpp"

using namespace std;
using namespace sf;

int main() {
    
    RenderWindow window(VideoMode(800, 600), "SFML Game");
    window.setFramerateLimit(60);

    Player player;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        player.update();
        window.clear();
        player.render(window);
        window.display();

    }

    return 0;

}