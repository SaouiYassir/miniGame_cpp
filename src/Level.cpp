#include "Level.hpp"
#include <iostream>

sf::Texture Level::tex1;
sf::Texture Level::tex2;
sf::Texture Level::tex3;
bool Level::charge = false;

Level::Level() {
    if (!charge) {
        if (!tex1.loadFromFile("assets/imgs/bg1.png") ||
            !tex2.loadFromFile("assets/imgs/menuBackground.png") ||
            !tex3.loadFromFile("assets/imgs/bg1.png")) {
            std::cerr << "Erreur de chargement des fonds !" << std::endl;
        }
        charge = true;
    }
    // Par défaut, on commence au niveau 1
    sprite.setTexture(tex1);
}

void Level::setNiveau(int niveau) {
    if (niveau == 1) sprite.setTexture(tex1);
    else if (niveau == 2) sprite.setTexture(tex2);
    else if (niveau == 3) sprite.setTexture(tex3);
    
    // Optionnel : Redimensionner le fond pour remplir l'écran de 1300x1000
    // float scaleX = 1300.f / sprite.getLocalBounds().width;
    // float scaleY = 1000.f / sprite.getLocalBounds().height;
    // sprite.setScale(scaleX, scaleY);
}

void Level::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}