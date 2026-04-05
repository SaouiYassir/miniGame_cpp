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

    
    // On essaie plusieurs chemins pour trouver la police
    bool fontLoaded = false;
    if (font.loadFromFile("arial.ttf")) fontLoaded = true;
    else if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) fontLoaded = true;
    else if (font.loadFromFile("assets/arial.ttf")) fontLoaded = true;

    if (!fontLoaded) {
        std::cerr << "ERREUR : arial.ttf introuvable ! Verifie le dossier du projet." << std::endl;
    }

    timerText.setFont(font);
    timerText.setCharacterSize(60); 
    timerText.setFillColor(sf::Color::Blue);
    timerText.setPosition(windowWidth - 250, 20); 
    // -----------------------------------------

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (state == MENU_STATE) {
                int selection = menu.handleInput(window, event);
                if (selection == 1) { // Jouer
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

            // Apparition des obstacles
            if (spawnTimer.getElapsedTime().asSeconds() > 1.5f) {
                // Utilise ton nouveau constructeur (true/false, vitesse)
                obstacles.push_back(Obstacle(std::rand() % 2 == 0, 6.5f)); 
                spawnTimer.restart();
            }

            player.update();
            player.render(window);

            for (size_t i = 0; i < obstacles.size(); i++) {
                obstacles[i].update();
                obstacles[i].render(window);

                // Collision
                if (player.getBounds().intersects(obstacles[i].getBounds())) {
                    state = MENU_STATE; 
                    gameTimer.pause();
                }
                
                // Nettoyage hors écran
                if (obstacles[i].getBounds().left + obstacles[i].getBounds().width < 0) {
                    obstacles.erase(obstacles.begin() + i);
                    i--; 
                }
            }

            // Dessin du texte du chrono
            window.draw(timerText);
        }
        window.display();
    }
    return 0;
}