#include "Menu.hpp"

Menu::Menu(float width, float height) {

    float screenWidth = 1080;
    float screenHeight = 720;
    float buttonWidth = 250;
    float buttonHeight = 80;
    float spacing = 20;

    float xPos = (screenWidth - buttonWidth) / 2;
    float centerY = (screenHeight - buttonHeight) / 2;

    if (!font.loadFromFile("assets/fonts/font.ttf")) {
        cout << "Error loading font" << endl;
    }

    if (!menuTexture.loadFromFile("assets/imgs/backgrounds/menuBackground.png")) {
        cout << "Error loading menu image" << endl;
    }

    if (!aboutTexture.loadFromFile("assets/imgs/backgrounds/aboutBackground.png")) {
        cout << "Error loading about image" << endl;
    }

    // --- PLAY BUTTON ---
    playButton.setSize(Vector2f(buttonWidth, buttonHeight));
    playButton.setFillColor(Color(30, 30, 30, 180));
    playButton.setPosition(Vector2f(xPos, centerY - buttonHeight - spacing));

    playText.setFont(font);
    playText.setString("PLAY");
    playText.setCharacterSize(45);
    FloatRect pRect = playText.getLocalBounds();
    playText.setOrigin(pRect.left + pRect.width / 2.0f, pRect.top + pRect.height / 2.0f);
    playText.setPosition(playButton.getPosition().x + (buttonWidth / 2), playButton.getPosition().y + (buttonHeight/2));

    // --- ABOUT BUTTON ---
    aboutButton.setSize(Vector2f(buttonWidth, buttonHeight));
    aboutButton.setFillColor(Color(30, 30, 30, 180));
    aboutButton.setPosition(Vector2f(xPos, centerY));

    aboutText.setFont(font);
    aboutText.setString("ABOUT GAME");
    aboutText.setCharacterSize(45);
    FloatRect aRect = aboutText.getLocalBounds();
    aboutText.setOrigin(aRect.left + aRect.width / 2.0f, aRect.top + aRect.height / 2.0f);
    aboutText.setPosition(aboutButton.getPosition().x + (buttonWidth / 2), aboutButton.getPosition().y + (buttonHeight/2));


    // --- QUIT BUTTON ---
    quitButton.setSize(Vector2f(buttonWidth, buttonHeight));
    quitButton.setFillColor(Color(30, 30, 30, 180));
    quitButton.setPosition(Vector2f(xPos, centerY + buttonHeight + spacing));

    quitText.setFont(font);
    quitText.setString("QUIT");
    quitText.setCharacterSize(45);
    FloatRect qRect = quitText.getLocalBounds();
    quitText.setOrigin(qRect.left + qRect.width / 2.0f, qRect.top + qRect.height / 2.0f);
    quitText.setPosition(quitButton.getPosition().x + (buttonWidth / 2), quitButton.getPosition().y + (buttonHeight/2));

    menuSprite.setTexture(menuTexture);
    menuSprite.setPosition(0, 0);
    menuSprite.setScale(0.8f, 0.8f);

    aboutSprite.setTexture(aboutTexture);
    aboutSprite.setPosition(0, 0);
    aboutSprite.setScale(0.7f, 0.7f);
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
