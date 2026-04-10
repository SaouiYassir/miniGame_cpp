#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>
#include <string> // Pour std::to_string
#include "src/Player.hpp"
#include "src/Obstacle.hpp"
#include "src/Menu.hpp"
#include "src/Timer.hpp"
#include "src/Level.hpp"
#include "src/Heart.hpp"

// --- NOUVEAU : Ajout de GAME_OVER_STATE ---
enum GameState { MENU_STATE, GAMEPLAY_STATE, ABOUT_STATE, GAME_OVER_STATE };

int main() {
    int windowWidth = 1080;
    int windowHeight = 720;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Game");
    window.setFramerateLimit(60);

    GameState state = MENU_STATE;
    Menu menu(windowWidth, windowHeight); 
    Player player;
    std::vector<Obstacle> obstacles;
    sf::Clock spawnTimer;

    Heart hp; 
    sf::Clock damageTimer; 

    Level level;
    float vitesseActuelle = 6.5f; 

    Timer gameTimer;
    sf::Font font;
    sf::Text timerText;

    // --- NOUVEAU : Textes pour Level Up et Game Over ---
    sf::Text centerText; 
    if (!font.loadFromFile("arial.ttf")) { 
        font.loadFromFile("assets/fonts/font1.ttf");
    }

    // Configuration du texte central (Game Over / Level X)
    centerText.setFont(font);
    centerText.setCharacterSize(120);
    centerText.setStyle(sf::Text::Bold);

    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(windowWidth - 200, 20); 

    // Variables pour gérer l'affichage temporaire du niveau
    int lastLevel = 1;
    sf::Clock levelDisplayTimer;
    bool showLevelMessage = false;

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
                    hp.reset();
                    level.setNiveau(1); // Recommencer au niveau 1
                    lastLevel = 1;
                    showLevelMessage = false;
                } else if (selection == 2) { 
                    state = ABOUT_STATE;
                }
            } 
            // --- NOUVEAU : Retour au menu depuis Game Over ---
            else if (state == GAME_OVER_STATE && event.type == sf::Event::KeyPressed) {
                state = MENU_STATE;
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

            float secondes = gameTimer.getElapsedTime().asSeconds();

            // --- NOUVEAU : Logique de passage de niveaux (15s par niveau) ---
            int currentLevel = 1;
            if (secondes < 15.f) { 
                currentLevel = 1;
                vitesseActuelle = 6.5f;
            } 
            else if (secondes < 30.f) { 
                currentLevel = 2;
                vitesseActuelle = 10.5f;
            } 
            else { 
                currentLevel = 3;
                vitesseActuelle = 15.0f;
            }

            // Vérifier si on vient de monter de niveau
            if (currentLevel > lastLevel) {
                showLevelMessage = true;
                levelDisplayTimer.restart();
                lastLevel = currentLevel;
            }
            level.setNiveau(currentLevel);

            level.draw(window);

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
                    if (damageTimer.getElapsedTime().asSeconds() > 1.0f) {
                        hp.hit();
                        damageTimer.restart();
                        
                        // --- NOUVEAU : Changement vers l'état Game Over ---
                        if (hp.getHealth() <= 0) {
                            state = GAME_OVER_STATE;
                        }
                    }
                }
                
                if (obstacles[i].getBounds().left + obstacles[i].getBounds().width < 0) {
                    obstacles.erase(obstacles.begin() + i);
                    i--; 
                }
            }

            hp.draw(window); 
            window.draw(timerText);

            // --- NOUVEAU : Affichage temporaire "Level X" ---
            if (showLevelMessage) {
                centerText.setString("Level " + std::to_string(currentLevel));
                centerText.setFillColor(sf::Color::Cyan);
                
                // Centrage du texte
                sf::FloatRect bounds = centerText.getLocalBounds();
                centerText.setOrigin(bounds.left + bounds.width/2.0f, bounds.top + bounds.height/2.0f);
                centerText.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);
                
                window.draw(centerText);

                // Cacher le message après 2 secondes
                if (levelDisplayTimer.getElapsedTime().asSeconds() > 2.0f) {
                    showLevelMessage = false;
                }
            }
        }
        // --- NOUVEAU : Affichage de l'écran Game Over ---
        else if (state == GAME_OVER_STATE) {
            centerText.setString("GAME OVER");
            centerText.setFillColor(sf::Color::Red);
            
            sf::FloatRect bounds = centerText.getLocalBounds();
            centerText.setOrigin(bounds.left + bounds.width/2.0f, bounds.top + bounds.height/2.0f);
            centerText.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);
            
            window.draw(centerText);
            
            // Petit texte informatif
            sf::Text retryText(" Press a key to have the Menu ", font, 30);
            retryText.setPosition(windowWidth / 2.0f - 150, windowHeight / 2.0f + 60);
            window.draw(retryText);
        }

        window.display();
    }
    return 0;
}