#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include "src/Player.hpp"
#include "src/Obstacle.hpp"
#include "src/Menu.hpp"

enum GameState { MENU_STATE, GAMEPLAY_STATE, ABOUT_STATE };

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML Mini-Game");
    window.setFramerateLimit(60);

    GameState state = MENU_STATE;
    Menu menu(800, 600);
    Player player;
    std::vector<Obstacle> obstacles;
    sf::Clock spawnTimer;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // --- INPUT HANDLING ---
            if (state == MENU_STATE) {
                int selection = menu.handleInput(window, event);
                if (selection == 1) {
                    state = GAMEPLAY_STATE;
                    obstacles.clear();
                    spawnTimer.restart();
                } else if (selection == 2) {
                    state = ABOUT_STATE;
                }
            } 
            // Press Escape to return to menu from anywhere
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                state = MENU_STATE;
            }
        }

        window.clear();

        if (state == MENU_STATE) {
            menu.update(window);
            menu.draw(window);
        } 
        else if (state == ABOUT_STATE) {
            menu.drawAbout(window); // Show the image
        } 
        else if (state == GAMEPLAY_STATE) {
            // Gameplay Logic
            if (spawnTimer.getElapsedTime().asSeconds() > 1.5f) {
                obstacles.push_back(Obstacle(std::rand() % 2, 6.5f));
                spawnTimer.restart();
            }

            player.update();
            player.render(window);

            for (size_t i = 0; i < obstacles.size(); i++) {
                obstacles[i].update();
                obstacles[i].render(window);

                if (player.getBounds().intersects(obstacles[i].getBounds())) {
                    state = MENU_STATE; 
                }
                if (obstacles[i].getBounds().left + obstacles[i].getBounds().width < 0) {
                    obstacles.erase(obstacles.begin() + i--);
                }
            }
        }
        window.display();
    }
    return 0;
}