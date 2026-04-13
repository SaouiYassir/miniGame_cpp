#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Level {
private:
    sf::Sprite sprite;
    static sf::Texture tex1, tex2, tex3;
    static bool charge;

public:
    Level();
    void setNiveau(int niveau);
    void draw(sf::RenderWindow& window);
};

#endif