#include "Player.hpp"

// Helper function to keep the constructor clean
void Player::loadFrames(vector<Texture>& container, string path, int count) {
    container.reserve(count); // Pre-allocate memory
    for (int i = 0; i < count; i++) {
        container.emplace_back(); // Create texture directly in the vector
        if (!container.back().loadFromFile(path + to_string(i) + ".png")) {
            cout << "Error loading: " << path << i << ".png" << endl;
        }
    }
}

Player::Player() {
    // Load all animations using the helper
    loadFrames(idleFrames, "assets/imgs/Idle/0_Bloody_Alchemist_Idle_", 18);
    loadFrames(runFrames, "assets/imgs/Running/0_Bloody_Alchemist_Running_", 12);
    loadFrames(slidingFrames, "assets/imgs/Sliding/0_Bloody_Alchemist_Sliding_", 6);

    if (!idleFrames.empty()) {
        sprite.setTexture(idleFrames[0]);
    }
    
    // Formatting the sprite
    FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    sprite.setScale(0.25f, 0.25f);
    sprite.setPosition(100.f, groundY);
}

void Player::handleInput() {
    isMoving = false; 
    isCrouching = false;
    float direction = (sprite.getScale().x > 0) ? 1.f : -1.f;

    if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
        sprite.move(moveSpeed, 0.f);
        sprite.setScale(0.25f, 0.25f); 
        isMoving = true;
    } 
    else if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
        sprite.move(-moveSpeed, 0.f);
        sprite.setScale(-0.25f, 0.25f); 
        isMoving = true;
    }

    if ((Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up)) && !isJumping) {
        isJumping = true;
        velocityY = jumpForce;
    }

    if ((Keyboard::isKeyPressed(Keyboard::C) || Keyboard::isKeyPressed(Keyboard::Down)) && !isJumping) {
        isCrouching = true;
        sprite.move(moveSpeed * 1.f * direction, 0.f);
    }
    else {
        float scaleX = sprite.getScale().x > 0 ? 0.25f : -0.25f;
        sprite.setScale(scaleX, 0.25f);
    }
}

void Player::applyPhysics() {
    if (isJumping) {
        velocityY += gravity;
        sprite.move(0.f, velocityY);

        if (sprite.getPosition().y >= groundY) {
            sprite.setPosition(sprite.getPosition().x, groundY);
            isJumping = false;
            velocityY = 0.f;
        }
    }
}

void Player::updateAnimation() {
    vector<Texture>& currentSet =
        isCrouching ? slidingFrames :
        isMoving ? runFrames :
        idleFrames;

    if (currentSet.empty()) return;

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

void Player::resetPosition() {
    sprite.setPosition(100.f, groundY);
}

FloatRect Player::getBounds() const { 
    FloatRect bounds = sprite.getGlobalBounds();

    float widthReduction = bounds.width * 0.4f; 
    bounds.width -= widthReduction;
    bounds.left += widthReduction / 2.0f;

    if (isCrouching) {
        bounds.height *= 0.5f;
        bounds.top += bounds.height; 
    } else {
        bounds.height *= 0.9f;
        bounds.top += sprite.getGlobalBounds().height * 0.1f;
    }

    return bounds;
}