#ifndef Player_hpp
#define Player_hpp
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Player {

private:
    RectangleShape rect;
    float velocityY;
    bool jumping;
    bool crouching;
    int health;

public:
    Player();
    void move();
    void jump();
    void crouch();
    void update();
    FloatRect getBounds();
    void render(RenderWindow& window);

};

#endif