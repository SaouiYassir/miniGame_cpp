#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>
#include "src/Player.hpp"
#include "src/Obstacle.hpp"
#include "src/Menu.hpp"
#include "src/Timer.hpp"
#include "src/Level.hpp" // Ajout de la nouvelle classe

enum GameState { MENU_STATE, GAMEPLAY_STATE, ABOUT_STATE };

int main() {
    // Dimensions de la fenêtre (inchangées)
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

    // --- INITIALISATION DU level ET VARIABLES DE NIVEAU ---
    Level level;
    float vitesseActuelle = 6.5f; // Vitesse initiale (Niveau 1)
    // -----------------------------------------------------------

    Timer gameTimer;
    sf::Font font;
    sf::Text timerText;

    if (!font.loadFromFile("arial.ttf")) { 
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }

    timerText.setFont(font);
    timerText.setCharacterSize(60); 
    timerText.setFillColor(sf::Color::Blue);
    timerText.setPosition(windowWidth - 200, 20); 

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

            // --- LOGIQUE DE PROGRESSION DES NIVEAUX ---
            // On récupère le temps écoulé en secondes depuis le début de la partie
            float secondes = gameTimer.getElapsedTime().asSeconds();

            if (secondes < 15.f) { 
                // NIVEAU 1 : Vitesse normale
                level.setNiveau(1);
                vitesseActuelle = 6.5f;
            } 
            else if (secondes < 30.f) { 
                // NIVEAU 2 : Vitesse augmentée + Nouveau décor
                level.setNiveau(2);
                vitesseActuelle = 10.5f;
            } 
            else { 
                // NIVEAU 3 : Vitesse maximale + Décor final
                level.setNiveau(3);
                vitesseActuelle = 15.0f;
            }

            // 1. DESSINER LE level EN PREMIER (fond de l'écran)
            level.draw(window);

            // 2. GESTION DES OBSTACLES (utilise la vitesse du niveau actuel)
            if (spawnTimer.getElapsedTime().asSeconds() > 1.5f) {
                obstacles.push_back(Obstacle(std::rand() % 2 == 0, vitesseActuelle)); 
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