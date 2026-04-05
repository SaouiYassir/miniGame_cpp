#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

class Obstacle {
private:
    // "static" signifie que la texture appartient à la CLASSE, pas à l'objet.
    // Elle reste en mémoire tant que le programme tourne.
    static sf::Texture textureHaut;
    static sf::Texture textureBas;
    static bool texturesChargees;

    sf::Sprite sprite;   
    float vitesse;            

public:
    Obstacle(bool estEnHaut, float v);
    void update();
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};

#endif