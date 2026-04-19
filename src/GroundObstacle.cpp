#include "GroundObstacle.hpp"
#include <iostream>

sf::Texture GroundObstacle::texture;
bool GroundObstacle::loaded = false;

GroundObstacle::GroundObstacle(float speed) : Obstacle(speed) {
    if (!loaded) {
        if (!texture.loadFromFile("assets/imgs/obstacles/white_crystal_light_shadow1.png")) {
            std::cerr << "Error loading ground texture" << std::endl;
        }
        loaded = true;
    }
    sprite.setTexture(texture);
    sprite.setPosition(1080.f, 330.f);
}

bool GroundObstacle::getIsFlying() const {
    return false;
}