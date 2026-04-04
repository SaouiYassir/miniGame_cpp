#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

class Obstacle {
private:
    sf::RectangleShape corps; 
    float vitesse;            

public:
    Obstacle(bool estEnHaut, float v);

    void update();

    // Renommé pour correspondre au main.cpp
    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
};

#endif