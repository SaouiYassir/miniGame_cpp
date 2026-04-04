#include "Obstacle.hpp"

Obstacle::Obstacle(bool estEnHaut, float v) {
    vitesse = v;
    corps.setSize(sf::Vector2f(50.f, 50.f));

    if (estEnHaut) {
        corps.setFillColor(sf::Color::Yellow); 
        corps.setPosition(850.f, 350.f);       
    } 
    else {
        corps.setFillColor(sf::Color::Red);    
        corps.setPosition(850.f, 500.f);       
    }
}

void Obstacle::update() {
    corps.move(-vitesse, 0.f);
}

// Changé de "afficher" à "render"
void Obstacle::render(sf::RenderWindow& window) {
    window.draw(corps);
}

sf::FloatRect Obstacle::getBounds() const {
    return corps.getGlobalBounds();
}