#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Obstacle {
private:
    // "static" signifie que la texture appartient à la CLASSE, pas à l'objet.
    // Elle reste en mémoire tant que le programme tourne.
    static Texture flyingTexture;
    static Texture groundTexture;
    static bool texturesChargees;
    bool isFlying;

    Sprite sprite;   
    float vitesse;            

public:
    Obstacle(bool, float);
    void update();
    void render(RenderWindow& window);
    FloatRect getBounds() const;
    bool getIsFlying() const;
};

#endif