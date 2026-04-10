#include "Player.hpp"

Player::Player() {
    // 1. Load Idle Frames (Assuming 18 frames based on your previous code)
    for (int i = 0; i < 18; i++) {
        Texture t;
        if (t.loadFromFile("assets/imgs/Idle/0_Bloody_Alchemist_Idle_" + to_string(i) + ".png")) {
            idleFrames.push_back(t);
        }
    }

    // 2. Load Run Frames (Adjust the loop limit to your actual number of run files)
    for (int i = 0; i < 12; i++) {
        Texture t;
        if (t.loadFromFile("assets/imgs/Running/0_Bloody_Alchemist_Running_" + to_string(i) + ".png")) {
            runFrames.push_back(t);
        }
    }

    // Initialize Sprite with the first idle frame
    if (!idleFrames.empty()) {
        sprite.setTexture(idleFrames[0]);
    }
    
    // Set origin to center so flipping (A/D) doesn't cause "teleporting"
    FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    
    sprite.setScale(0.25f, 0.25f);
    sprite.setPosition(100.f, groundY);
}

void Player::handleInput() {
    isMoving = false; // Assume not moving unless a key is pressed

    if (Keyboard::isKeyPressed(Keyboard::D)) {
        sprite.move(moveSpeed, 0.f);
        sprite.setScale(0.25f, 0.25f); // Face Right
        isMoving = true;
    } 
    else if (Keyboard::isKeyPressed(Keyboard::A)) {
        sprite.move(-moveSpeed, 0.f);
        sprite.setScale(-0.25f, 0.25f); // Face Left
        isMoving = true;
    }

    if (Keyboard::isKeyPressed(Keyboard::Space) && !isJumping) {
        isJumping = true;
        velocityY = jumpForce;
    }
}

void Player::applyPhysics() {
    if (isJumping) {
        velocityY += gravity;
        sprite.move(0.f, velocityY);

        // Ground collision check
        if (sprite.getPosition().y >= groundY) {
            sprite.setPosition(sprite.getPosition().x, groundY);
            isJumping = false;
            velocityY = 0.f;
        }
    }
}

void Player::updateAnimation() {
    // Determine which set of textures to cycle through
    vector<Texture>& currentSet = isMoving ? runFrames : idleFrames;

    if (currentSet.empty()) return;

    // Timer logic: Change frame only if enough time has passed
    if (animationClock.getElapsedTime().asSeconds() >= frameDuration) {
        currentFrame = (currentFrame + 1) % currentSet.size();
        sprite.setTexture(currentSet[currentFrame]);
        animationClock.restart();
    }
}

void Player::update() {
    handleInput();
    applyPhysics();
    updateAnimation();
}

void Player::render(RenderWindow& window) {
    window.draw(sprite);
}

FloatRect Player::getBounds() const { 
    return sprite.getGlobalBounds(); 
}