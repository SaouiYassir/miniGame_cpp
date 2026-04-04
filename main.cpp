#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "src/Player.hpp"
#include "src/Obstacle.hpp"

using namespace sf;

int main() {
    // Initialisation du hasard
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Fenêtre de jeu
    RenderWindow window(VideoMode(800, 600), "SFML Runner - Game");
    window.setFramerateLimit(60);

    // Instances
    Player player;
    std::vector<Obstacle> obstacles;
    
    // Gestion du temps pour les obstacles
    Clock chronoApparition;
    float delaiSpawn = 1.5f;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) 
                window.close();
        }

        // 1. LOGIQUE DE GÉNÉRATION (SPAWN)
        if (chronoApparition.getElapsedTime().asSeconds() > delaiSpawn) {
            // Alternance aléatoire entre obstacle haut et bas
            bool typeAleatoire = (std::rand() % 2 == 1);
            
            // Ajout d'un nouvel obstacle (vitesse de 6.5f par défaut)
            obstacles.push_back(Obstacle(typeAleatoire, 6.5f));
            
            chronoApparition.restart();
        }

        // 2. MISE À JOUR DU JOUEUR
        player.update();

        // 3. MISE À JOUR DES OBSTACLES & COLLISIONS
        for (size_t i = 0; i < obstacles.size(); i++) {
            obstacles[i].update(); // Déplacement

            // Test de collision
            // On utilise getGlobalBounds() car c'est la méthode standard de SFML
            if (player.getBounds().intersects(obstacles[i].getBounds())) {
                std::cout << "Game Over!" << std::endl;
                window.close(); 
            }

            // Nettoyage : si l'obstacle sort de l'écran à gauche
            if (obstacles[i].getBounds().left + obstacles[i].getBounds().width < 0) {
                obstacles.erase(obstacles.begin() + i);
                i--; // Ajuste l'index suite à la suppression
            }
        }

        // 4. RENDU (AFFICHAGE)
        window.clear();

        // On dessine le joueur
        player.render(window); 

        // On dessine tous les obstacles
        for (auto& obs : obstacles) {
            obs.render(window); 
        }

        window.display();
    }

    return 0;
}