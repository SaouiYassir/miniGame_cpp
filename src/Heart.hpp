#ifndef HEART_HPP
#define HEART_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Heart {
private:
    int health;
    int maxHealth = 3;
    Texture redTexture;
    Texture grayTexture;
    vector<Sprite> hearts;
    
    void updateVisuals(); // Met à jour l'affichage selon les PV restants

public:
    Heart();
    void hit();               // Appelée quand le joueur touche un obstacle
    int getHealth() const;    // Pour savoir si on est à 0 (Game Over)
    void draw(RenderWindow& window);
    void reset();
};

#endif 