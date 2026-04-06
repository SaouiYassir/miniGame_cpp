#ifndef Player_hpp
#define Player_hpp
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture1, texture2;

    // Constantes de mouvement (plus facile à régler ici)
    const float moveSpeed = 5.0f;
    const float gravity = 0.8f;
    const float jumpForce = -20.0f;
    const float groundY = 350.0f;
    
    // États
    float velocityY = 0.0f;
    bool isJumping = false;
    bool isCrouching = false;

    // Helper pour éviter la répétition dans l'update
    void handleInput();
    void applyPhysics();

public:
    Player();
    
    void update();
    void render(sf::RenderWindow& window);
    
    sf::FloatRect getBounds() const; // Ajout de 'const' car ne modifie pas l'objet
};

#endif