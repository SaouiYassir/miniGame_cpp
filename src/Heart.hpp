#ifndef HEART_HPP
#define HEART_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Heart {
private:
    int health;
    int maxHealth = 3;
    Texture redTexture;
    Texture grayTexture;
    vector<Sprite> hearts;
    
    void updateVisuals(); 

public:
    Heart();
    void hit();           
    int getHealth() const;
    void draw(RenderWindow& window);
    void reset();
};

#endif 