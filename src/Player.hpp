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
    vector<Texture> slidingFrames;
    
    int currentFrame = 0;
    Clock animationClock;  
    float frameDuration = 0.05f; 
    bool isMoving = false;

    const float moveSpeed = 5.0f;
    const float gravity = 0.8f;
    const float jumpForce = -20.0f;
    const float groundY = 380.0f;
    
    float velocityY = 0.0f;
    bool isJumping = false;
    bool isCrouching = false;

    void handleInput();
    void applyPhysics();

public:
    Player();
    
    void animate();
    void update();
    void updateAnimation();
    void render(RenderWindow& window);
    void resetPosition();
    
    FloatRect getBounds() const; 
};

#endif