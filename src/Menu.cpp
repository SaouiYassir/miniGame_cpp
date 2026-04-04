#include "Menu.hpp"
#include <iostream> 

using namespace sf;

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("assets/fonts/font1.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    if (!menuTexture.loadFromFile("assets/imgs/menuBackground.png")) {
        std::cout << "Error loading menu image" << std::endl;
    }

    if (!aboutTexture.loadFromFile("assets/imgs/aboutBackground.png")) {
        std::cout << "Error loading about image" << std::endl;
    }

    // --- PLAY BUTTON ---
    playButton.setSize(Vector2f(200, 60));
    playButton.setFillColor(Color::Blue);
    playButton.setPosition(Vector2f(width / 2 , height / 2 - 100));

    playText.setFont(font);
    playText.setString("PLAY");
    playText.setCharacterSize(30);
    FloatRect pRect = playText.getLocalBounds();
    playText.setOrigin(pRect.left + pRect.width / 2.0f, pRect.top + pRect.height / 2.0f);
    playText.setPosition(playButton.getPosition().x + 100, playButton.getPosition().y + 30);

    // --- ABOUT BUTTON ---
    aboutButton.setSize(Vector2f(200, 60));
    aboutButton.setFillColor(Color::Green);
    aboutButton.setPosition(Vector2f(width / 2 , height / 2));

    aboutText.setFont(font);
    aboutText.setString("ABOUT GAME");
    aboutText.setCharacterSize(30);
    FloatRect aRect = aboutText.getLocalBounds();
    aboutText.setOrigin(aRect.left + aRect.width / 2.0f, aRect.top + aRect.height / 2.0f);
    aboutText.setPosition(aboutButton.getPosition().x + 100, aboutButton.getPosition().y + 30);


    // --- QUIT BUTTON ---
    quitButton.setSize(Vector2f(200, 60));
    quitButton.setFillColor(Color::Red);
    quitButton.setPosition(Vector2f(width / 2 , height / 2 + 100));

    quitText.setFont(font);
    quitText.setString("QUIT");
    quitText.setCharacterSize(30);
    FloatRect qRect = quitText.getLocalBounds();
    quitText.setOrigin(qRect.left + qRect.width / 2.0f, qRect.top + qRect.height / 2.0f);
    quitText.setPosition(quitButton.getPosition().x + 100, quitButton.getPosition().y + 30);

    menuSprite.setTexture(menuTexture);
    menuSprite.setPosition(0, 0);

    aboutSprite.setTexture(aboutTexture);
    aboutSprite.setPosition(0, 0);
}

void Menu::update(RenderWindow& window) {
    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
}

int Menu::handleInput(RenderWindow& window, Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

        if (playButton.getGlobalBounds().contains(mousePos)) return 1; 
        if (aboutButton.getGlobalBounds().contains(mousePos)) return 2;
        if (quitButton.getGlobalBounds().contains(mousePos)) window.close();
    }
    return 0; 
}

void Menu::draw(RenderWindow& window) {
    window.draw(menuSprite);
    window.draw(playButton);
    window.draw(playText);
    window.draw(aboutButton);
    window.draw(aboutText);
    window.draw(quitButton);
    window.draw(quitText);
}

void Menu::drawAbout(RenderWindow& window) {
    window.draw(aboutSprite);
}
