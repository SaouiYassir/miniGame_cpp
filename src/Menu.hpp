#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Menu {
private:
    Texture menuTexture;
    Sprite menuSprite;
    RectangleShape playButton;
    Text playText;
    RectangleShape aboutButton;
    Text aboutText;
    Texture aboutTexture;
    Sprite aboutSprite;
    RectangleShape quitButton;
    Text quitText;
    Font font;

public:
    Menu(float width, float height);
    void draw(RenderWindow& window);
    void drawAbout(RenderWindow& window);
    void update(RenderWindow& window);
    int handleInput(RenderWindow& window, Event& event); // Must be int
};

#endif