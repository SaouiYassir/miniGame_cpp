#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <iostream>
#include "src/Player.hpp"
#include "src/Obstacle.hpp"
#include "src/Menu.hpp"
#include "src/Timer.hpp"
#include "src/Level.hpp"
#include "src/Heart.hpp" // --- AJOUT : Inclusion de la classe Heart ---

enum GameState { MENU_STATE, GAMEPLAY_STATE, ABOUT_STATE };

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

    // --- AJOUT : Système de vie et timer d'invulnérabilité ---
    Heart hp; 
    sf::Clock damageTimer; // Pour éviter de perdre toutes les vies d'un coup
    // ---------------------------------------------------------

    Level level;
    float vitesseActuelle = 6.5f; 

    Timer gameTimer;
    sf::Font font;
    sf::Text timerText;

    if (!font.loadFromFile("arial.ttf")) { 
        font.loadFromFile("assets/fonts/font1.ttf");
    }

    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setOutlineThickness(2);
    timerText.setOutlineColor(sf::Color::Black);  
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
                    hp.reset(); // --- AJOUT : Réinitialise les coeurs au début d'une partie ---
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

            float secondes = gameTimer.getElapsedTime().asSeconds();

            if (secondes < 15.f) { 
                level.setNiveau(1);
                vitesseActuelle = 6.5f;
            } 
            else if (secondes < 30.f) { 
                level.setNiveau(2);
                vitesseActuelle = 10.5f;
            } 
            else { 
                level.setNiveau(3);
                vitesseActuelle = 15.0f;
            }

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

                // --- MODIFICATION DE LA LOGIQUE DE COLLISION ---
                if (player.getBounds().intersects(obstacles[i].getBounds())) {
                    // On vérifie si 1 seconde s'est écoulée depuis le dernier dégât (invulnérabilité)
                    if (damageTimer.getElapsedTime().asSeconds() > 1.0f) {
                        hp.hit(); // Réduit la vie
                        damageTimer.restart(); // Relance le timer d'invulnérabilité
                        
                        // Si plus de vie, Game Over
                        if (hp.getHealth() <= 0) {
                            window.close(); // Ferme la fenêtre comme demandé
                        }
                    }
                }
                
                if (obstacles[i].getBounds().left + obstacles[i].getBounds().width < 0) {
                    obstacles.erase(obstacles.begin() + i);
                    i--; 
                }
            }

            // --- AJOUT : Dessiner la barre de vie et le timer ---
            hp.draw(window); 
            window.draw(timerText);
        }
        window.display();
    }
    return 0;
}