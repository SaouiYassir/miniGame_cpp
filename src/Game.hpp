#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <cmath> 
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Menu.hpp"
#include "Timer.hpp"
#include "Level.hpp"
#include "Heart.hpp"
#include "FlyingObstacle.hpp" 
#include "GroundObstacle.hpp"

using namespace sf;
using namespace std;

class Game {
private:
    enum GameState {
        MENU_STATE,
        GAMEPLAY_STATE,
        PAUSED_STATE,   
        ABOUT_STATE,
        GAME_OVER_STATE
    };

    GameState state;
    
    int windowWidth;
    int windowHeight;
    
    RenderWindow window;
    
    Menu menu;
    Player player;
    Heart hp;
    Level level;
    Timer gameTimer;

    vector<Obstacle*> obstacles;

    Clock spawnTimer;
    Clock damageTimer;
    Clock levelDisplayTimer;

    Font font1, font2, font3;
    Text timerText;
    Text centerText;

    Music backgroundMusic;
    Music gameOverEffect;
    Music damageEffect;

    float vitesseActuelle;
    float finalGameTime;
    int lastLevel;
    bool showLevelMessage;

    void processEvents();
    void update();
    void render();

    void updateGameplay();
    void renderGameplay();
    void togglePause();
    void resetGame();

public:
    Game();
    ~Game();
    void run();
};

#endif