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

    // 3/ Load Sliding Frames
    for (int i=0; i<6; i++) {
        Texture t;
        if (t.loadFromFile("assets/imgs/Sliding/0_Bloody_Alchemist_Sliding_" + to_string(i) + ".png")) {
            slidingFrames.push_back(t);
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
    isCrouching = false;

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

    if (Keyboard::isKeyPressed(Keyboard::C) && !isJumping) {
        isCrouching = true;
        sprite.move(moveSpeed * 1.5f, 0.f);
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

        // Ground collision check
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

FloatRect Player::getBounds() const { 
    FloatRect bounds = sprite.getGlobalBounds();

    // 1. RÉDUCTION DE LA LARGEUR (Padding horizontal)
    // On réduit la largeur et on décale la gauche pour centrer la hitbox sur le corps
    float widthReduction = bounds.width * 0.4f; // On enlève 40% de la largeur totale
    bounds.width -= widthReduction;
    bounds.left += widthReduction / 2.0f;

    // 2. LOGIQUE D'ACCROUPISSEMENT ET HAUTEUR
    if (isCrouching) {
        // Hitbox courte quand il est accroupi
        bounds.height *= 0.5f;
        bounds.top += bounds.height; // On descend le haut de la box vers le sol
    } else {
        // Optionnel : Réduire un peu la hauteur même debout pour éviter de 
        // se prendre un obstacle à cause d'un chapeau ou d'une mèche de cheveux
        bounds.height *= 0.9f;
        bounds.top += sprite.getGlobalBounds().height * 0.1f;
    }

    return bounds;
}