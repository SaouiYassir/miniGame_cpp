#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
private:
    sf::RectangleShape playButton;
    sf::Text playText;
    sf::RectangleShape aboutButton;
    sf::Text aboutText;
    sf::Texture aboutTexture;
    sf::Sprite aboutSprite;
    sf::RectangleShape quitButton;
    sf::Text quitText;
    sf::Font font;

public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void drawAbout(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    int handleInput(sf::RenderWindow& window, sf::Event& event); // Must be int
};

#endif