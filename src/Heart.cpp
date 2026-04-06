#include "Heart.hpp"

Heart::Heart() {
    health = maxHealth;

    // Création des 3 barres rouges
    for (int i = 0; i < maxHealth; i++) {
        sf::RectangleShape bar(sf::Vector2f(40.f, 20.f)); // Taille d'une barre
        bar.setFillColor(sf::Color::Red);
        bar.setOutlineThickness(2);
        bar.setOutlineColor(sf::Color::White);
        
        // Positionnement en haut à gauche avec un petit espace
        bar.setPosition(20.f + (i * 50.f), 20.f); 
        
        bars.push_back(bar);
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

void Heart::draw(sf::RenderWindow& window) {
    // On ne dessine que le nombre de barres correspondant à la santé actuelle
    for (int i = 0; i < health; i++) {
        window.draw(bars[i]);
    }
}

void Heart::reset() {
    health = maxHealth; // On remet la vie au maximum
}