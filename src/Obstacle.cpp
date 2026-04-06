#include "Obstacle.hpp"
#include <iostream>

// --- INITIALISATION DES STATICS ---
sf::Texture Obstacle::textureHaut;
sf::Texture Obstacle::textureBas;
bool Obstacle::texturesChargees = false;

Obstacle::Obstacle(bool estEnHaut, float v) {
    vitesse = v;

    // On ne charge les images qu'UNE SEULE FOIS pour tout le jeu
    if (!texturesChargees) {
        if (!textureHaut.loadFromFile("assets/imgs/centipede_light_shadow2.png") ||
            !textureBas.loadFromFile("assets/imgs/white_crystal_light_shadow1.png")) {
            std::cerr << "Erreur : Impossible de charger les textures !" << std::endl;
        }
        texturesChargees = true;
    }

    // Attribution de la texture au sprite
    if (estEnHaut) {
        sprite.setTexture(textureHaut);
        sprite.setPosition(1080.f, 250.f);
    } 
    else {
        sprite.setTexture(textureBas);
        sprite.setPosition(1080.f, 360.f);       
    }
}

void Obstacle::update() {
    sprite.move(-vitesse, 0.f);
}

void Obstacle::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Obstacle::getBounds() const {
    return sprite.getGlobalBounds();
}