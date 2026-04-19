#include "FlyingObstacle.hpp"

Texture FlyingObstacle::texture;
bool FlyingObstacle::loaded = false;

FlyingObstacle::FlyingObstacle(float speed) : Obstacle(speed) {
    if (!loaded) {
        if (!texture.loadFromFile("assets/imgs/obstacles/centipede_light_shadow2.png")) {
            std::cerr << "Error loading flying texture" << std::endl;
        }
        loaded = true;
    }
    sprite.setTexture(texture);
    sprite.setPosition(1080.f, 220.f);
}

bool FlyingObstacle::getIsFlying() const {
    return true;
}