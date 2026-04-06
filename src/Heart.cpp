#include "Heart.hpp"
#include <iostream>

Heart::Heart() {
    health = maxHealth;

    if (!redTexture.loadFromFile("assets/imgs/heart.png")) {
        cout << "Error loading red heart\n";
    }

    if (!grayTexture.loadFromFile("assets/imgs/gray_heart.png")) {
        cout << "Error loading gray heart\n";
    }

    for (int i = 0; i < maxHealth; i++) {
        Sprite heart;
        heart.setTexture(redTexture);
        heart.setScale(0.2f, 0.2f);
        heart.setPosition(20.f + i * 50.f, 20.f);
        hearts.push_back(heart);
    }
}

void Heart::hit() {
    if (health > 0) {
        health--;
    }
}

int Heart::getHealth() const {
    return health;
}

void Heart::draw(RenderWindow& window) {
    for (int i = 0; i < maxHealth; i++) {
        if (i < health)
            hearts[i].setTexture(redTexture);
        else
            hearts[i].setTexture(grayTexture);

        window.draw(hearts[i]);
    }
}

void Heart::reset() {
    health = maxHealth;
}