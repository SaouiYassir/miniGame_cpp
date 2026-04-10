#ifndef Player_hpp
#define Player_hpp
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player {
private:
    Sprite sprite;

    vector<Texture> idleFrames;
    vector<Texture> runFrames;
    
    int currentFrame = 0;
    Clock animationClock;  // Tracks time passed
    float frameDuration = 0.05f; // Speed of animation (0.1 seconds per frame)
    bool isMoving = false;

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
    
    void animate();
    void update();
    void updateAnimation();
    void render(RenderWindow& window);
    
    FloatRect getBounds() const; // Ajout de 'const' car ne modifie pas l'objet
};

#endif