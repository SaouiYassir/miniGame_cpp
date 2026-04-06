#ifndef HEART_HPP
#define HEART_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Heart {
private:
    int health;
    int maxHealth = 3;
    std::vector<sf::RectangleShape> bars;
    
    void updateVisuals(); // Met à jour l'affichage selon les PV restants

public:
    Heart();
    void hit();               // Appelée quand le joueur touche un obstacle
    int getHealth() const;    // Pour savoir si on est à 0 (Game Over)
    void draw(sf::RenderWindow& window);
    void reset();
};

#endif 