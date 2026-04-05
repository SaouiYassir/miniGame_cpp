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
    // Dimensions de la fenêtre
    int windowWidth = 1300;
    int windowHeight = 1000;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Game");
    window.setFramerateLimit(60);

    GameState state = MENU_STATE;
    Menu menu(windowWidth, windowHeight); 
    Player player;
    std::vector<Obstacle> obstacles;
    sf::Clock spawnTimer;

    Timer gameTimer;
    sf::Font font;
    sf::Text timerText;

    // Chargement de la police
    if (!font.loadFromFile("arial.ttf")) { 
        // Secours pour Windows si arial.ttf n'est pas dans le dossier projet
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    // Configuration de l'affichage du chrono
    timerText.setFont(font);
    timerText.setCharacterSize(60); 
    timerText.setFillColor(sf::Color::Blue);
    timerText.setPosition(windowWidth - 200, 20); 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (state == MENU_STATE) {
                // Le menu garde son positionnement et sa logique intacte
                int selection = menu.handleInput(window, event);
                if (selection == 1) { // Jouer
                    state = GAMEPLAY_STATE;
                    obstacles.clear();
                    spawnTimer.restart();
                    gameTimer.reset();
                    gameTimer.resume();
                } else if (selection == 2) { // À propos
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

            // Gestion de l'apparition des obstacles (avec le nouveau système de textures)
            if (spawnTimer.getElapsedTime().asSeconds() > 1.5f) {
                // On passe 'true' ou 'false' au constructeur qui gère ses textures static
                obstacles.push_back(Obstacle(std::rand() % 2 == 0, 6.5f)); 
                spawnTimer.restart();
            }

            player.update();
            player.render(window);

            for (size_t i = 0; i < obstacles.size(); i++) {
                obstacles[i].update();
                // Affiche maintenant le sprite au lieu du rectangle
                obstacles[i].render(window);

                // Collision détectée via sprite.getGlobalBounds() (défini dans obstacle.cpp)
                if (player.getBounds().intersects(obstacles[i].getBounds())) {
                    state = MENU_STATE; 
                    gameTimer.pause();
                }
                
                // Nettoyage des obstacles hors écran
                if (obstacles[i].getBounds().left + obstacles[i].getBounds().width < 0) {
                    obstacles.erase(obstacles.begin() + i);
                    i--; 
                }
            }

            window.draw(timerText);
        }
        window.display();
    }
    return 0;
}