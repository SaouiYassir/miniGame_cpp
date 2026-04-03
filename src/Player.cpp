#include "Player.hpp"

Player::Player() {
    rect.setSize(Vector2f(50, 50));
    rect.setOutlineColor(Color::Red);
    rect.setPosition(10, 20);
}

void Player::render(RenderWindow& window) {
    window.draw(rect);
}

void Player::update() {
    
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        rect.move(5.f, 0.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        rect.move(-5.f, 0.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        rect.move(0.f, 5.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        rect.move(0.f, -5.f);
    }
}

void Player::move() {}
void Player::jump() {}
sf::FloatRect Player::getBounds() { return rect.getGlobalBounds(); }