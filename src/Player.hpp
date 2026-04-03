#ifndef Player_hpp
#define Player_hpp
#include <SFML/Graphics.hpp>

unsing namespace sf;

class Player {

private:
    Sprite sprite;
    float velocityY;
    bool jumping;
    bool crouching;
    int health;

public:
    void move();
    void jump();
    void crouch();
    void update();
    sf::FloatRect getBounds();

}

#endif