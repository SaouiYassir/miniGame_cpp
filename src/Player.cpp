#include "Player.hpp"

Player::Player() {
    if (!texture1.loadFromFile("assets/imgs/player.png")) {
        // En C++, on préfère souvent une exception ou un log plus sérieux
        cout << "Error loading player image" << endl;
    }
    if (!texture2.loadFromFile("assets/imgs/player2.png")) {
        // En C++, on préfère souvent une exception ou un log plus sérieux
        cout << "Error loading player image" << endl;
    }
    sprite.setTexture(texture1);
    sprite.setScale(0.25f, 0.25f);
    sprite.setPosition(10.f, groundY);
}

void Player::handleInput() {
    // Mouvements horizontaux
    if (Keyboard::isKeyPressed(Keyboard::D)) 
        sprite.move(moveSpeed, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::A)) 
        sprite.move(-moveSpeed, 0.f);

    // Saut
    if (Keyboard::isKeyPressed(Keyboard::Space) && !isJumping) {
        isJumping = true;
        velocityY = jumpForce;
    }

    // Accroupissement (Optimisé : On ne change le scale que si nécessaire)
    bool cPressed = Keyboard::isKeyPressed(Keyboard::C);
    if (cPressed && !isCrouching) {
        sprite.setTexture(texture2);
        sprite.setScale(0.25f, 0.25f);
        sprite.move(0.f, 25.f); // Ajusté selon le scale pour rester au sol
        isCrouching = true;
    } 
    else if (!cPressed && isCrouching) {
        sprite.setTexture(texture1);
        sprite.move(0.f, -25.f);
        isCrouching = false;
    }
}

void Player::applyPhysics() {
    if (isJumping) {
        velocityY += gravity;
        sprite.move(0.f, velocityY);

        // Atterrissage
        if (sprite.getPosition().y >= groundY) {
            sprite.setPosition(sprite.getPosition().x, groundY);
            isJumping = false;
            velocityY = 0.f;
        }
    }
}

void Player::update() {
    handleInput();
    applyPhysics();
}

void Player::render(RenderWindow& window) {
    window.draw(sprite);
}

FloatRect Player::getBounds() const { 
    return sprite.getGlobalBounds(); 
}