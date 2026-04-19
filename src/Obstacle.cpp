#include "Obstacle.hpp"

Obstacle::Obstacle(float speed) : vitesse(speed) {}

Obstacle::~Obstacle() {}

void Obstacle::update() {
    sprite.move(-vitesse, 0.f);
}


void Obstacle::render(RenderWindow& window) {
    window.draw(sprite);
}

FloatRect Obstacle::getBounds() const {
    return sprite.getGlobalBounds();
}