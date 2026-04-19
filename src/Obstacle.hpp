#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Obstacle {
protected:
    Sprite sprite;
    float vitesse;

public:
    Obstacle(float v);
    virtual ~Obstacle(); 

    virtual void update();
    void render(RenderWindow& window);
    FloatRect getBounds() const;
    
    virtual bool getIsFlying() const = 0; 
};

#endif