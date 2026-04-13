#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class Menu {
private:
    float screenWidth;
    float screenHeight;
    float buttonWidth;
    float buttonHeight;
    float spacing;
    float xPos;
    float centerY;
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
    int handleInput(RenderWindow& window, Event& event); 
};

#endif