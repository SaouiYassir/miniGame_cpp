#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Background {
private:
    sf::Sprite sprite;
    static sf::Texture tex1, tex2, tex3;
    static bool charge;

public:
    Background();
    void setNiveau(int niveau); // Change la texture selon le niveau (1, 2 ou 3)
    void draw(sf::RenderWindow& window);
};

#endif