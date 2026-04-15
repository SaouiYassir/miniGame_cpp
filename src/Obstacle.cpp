#include "Obstacle.hpp"

Texture Obstacle::flyingTexture;
Texture Obstacle::groundTexture;
bool Obstacle::texturesChargees = false;

Obstacle::Obstacle(bool flying, float speed): isFlying(flying), vitesse(speed) {
    if (!texturesChargees) {
        if (!flyingTexture.loadFromFile("assets/imgs/obstacles/centipede_light_shadow2.png") ||
            !groundTexture.loadFromFile("assets/imgs/obstacles/white_crystal_light_shadow1.png")) {
            cerr << "Erreur : Impossible de charger les textures !" << endl;
        }
        texturesChargees = true;
    }

    if (isFlying) {
        sprite.setTexture(flyingTexture);

        
        sprite.setPosition(1080.f, 220.f);
        sprite.setScale(1.f, 1.f);
    }
    else {
        sprite.setTexture(groundTexture);

        
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