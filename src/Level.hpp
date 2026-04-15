#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace sf;

class Level {
private:
    Sprite sprite;
    static Texture tex1, tex2, tex3;
    static bool charge;

public:
    Level();
    void setNiveau(int niveau);
    void draw(RenderWindow& window);
};

#endif