#include "Level.hpp"
#include <iostream>

sf::Texture Level::tex1;
sf::Texture Level::tex2;
sf::Texture Level::tex3;
bool Level::charge = false;

Level::Level() {
    if (!charge) {
        if (!tex1.loadFromFile("assets/imgs/bamboo bridge.png") ||
            !tex2.loadFromFile("assets/imgs/forest bridge.png") ||
            !tex3.loadFromFile("assets/imgs/sky bridge.png")) {
            std::cerr << "Erreur de chargement des fonds !" << std::endl;
        }
        charge = true;
    }
    // Par défaut, on commence au niveau 1
    sprite.setTexture(tex1);
}

void Level::setNiveau(int niveau) {
    if (niveau == 1) {
        sprite.setTexture(tex1);
    } else if (niveau == 2) {
        sprite.setTexture(tex2);
    } else if (niveau == 3) {
        sprite.setTexture(tex3);
    } 
    
    float scaleX = 1080.f / sprite.getLocalBounds().width;
    float scaleY = 720.f / sprite.getLocalBounds().height;
    sprite.setScale(scaleX, scaleY);
}

void Level::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}