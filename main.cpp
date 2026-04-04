#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>
#include "src/Player.hpp"
#include "src/Obstacle.hpp"
#include "src/Menu.hpp"
#include "src/Timer.hpp"

enum GameState { MENU_STATE, GAMEPLAY_STATE, ABOUT_STATE };

int main() {
    int windowWidth = 1300;
    int windowHeight = 1000;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Game Linux");
    window.setFramerateLimit(60);

    GameState state = MENU_STATE;
    Menu menu(windowWidth, windowHeight); 
    Player player;
    std::vector<Obstacle> obstacles;
    sf::Clock spawnTimer;

    // --- SOLUTION : ON DÉCLARE TOUT ICI ---
    Timer gameTimer;
    sf::Font font;
    sf::Text timerText; // <--- C'est cette ligne qui manquait ou était mal placée !

    // Chargement de la police Ubuntu
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police !" << std::endl;
    }

    // Configuration de l'affichage du chrono
    timerText.setFont(font);
    timerText.setCharacterSize(60); 
    timerText.setFillColor(sf::Color::Blue);
    timerText.setPosition(windowWidth - 200, 20); 
    // ---------------------------------------

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (state == MENU_STATE) {
                int selection = menu.handleInput(window, event);
                if (selection == 1) {
                    state = GAMEPLAY_STATE;
                    obstacles.clear();
                    spawnTimer.restart();
                    gameTimer.reset();
                    gameTimer.resume();
                } else if (selection == 2) {
                    state = ABOUT_STATE;
                }
            } 
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                state = MENU_STATE;
                gameTimer.pause();
            }
        }

        window.clear();

        if (state == MENU_STATE) {
            menu.update(window);
            menu.draw(window);
        } 
        else if (state == ABOUT_STATE) {
            menu.drawAbout(window);
        } 
        else if (state == GAMEPLAY_STATE) {
            gameTimer.update();
            timerText.setString(gameTimer.getTimeString());

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
                    gameTimer.pause();
                }
                if (obstacles[i].getBounds().left + obstacles[i].getBounds().width < 0) {
                    obstacles.erase(obstacles.begin() + i--);
                }
            }

            // Affichage final
            window.draw(timerText);
        }
        window.display();
    }
    return 0;
}