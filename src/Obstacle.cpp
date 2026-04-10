#include "Obstacle.hpp"
#include <iostream>

// Static textures
Texture Obstacle::flyingTexture;
Texture Obstacle::groundTexture;
bool Obstacle::texturesChargees = false;

Obstacle::Obstacle(bool flying, float speed)
    : isFlying(flying), vitesse(speed)
{
    if (!texturesChargees) {
        if (!flyingTexture.loadFromFile("assets/imgs/centipede_light_shadow2.png") ||
            !groundTexture.loadFromFile("assets/imgs/white_crystal_light_shadow1.png")) {
            std::cerr << "Erreur : Impossible de charger les textures !" << std::endl;
        }
        texturesChargees = true;
    }

    if (isFlying) {
        sprite.setTexture(flyingTexture);

        // Flying enemy = head level
        sprite.setPosition(1080.f, 220.f);
        sprite.setScale(1.f, 1.f);
    }
    else {
        sprite.setTexture(groundTexture);

        // Ground enemy = near floor
        sprite.setPosition(1080.f, 330.f);
        sprite.setScale(1.f, 1.f);
    }
}

void Obstacle::update() {
    sprite.move(-vitesse, 0.f);
}

void Obstacle::render(RenderWindow& window) {
    window.draw(sprite);
}

FloatRect Obstacle::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Obstacle::getIsFlying() const {
    return isFlying;
}