#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Menu.hpp"
#include "Timer.hpp"
#include "Level.hpp"
#include "Heart.hpp"

using namespace sf;
using namespace std;

class Game {
private:
    enum GameState {
        MENU_STATE,
        GAMEPLAY_STATE,
        ABOUT_STATE,
        GAME_OVER_STATE
    };

    RenderWindow window;
    GameState state;

    int windowWidth;
    int windowHeight;

    Menu menu;
    Player player;
    vector<Obstacle> obstacles;
    Heart hp;
    Level level;
    Timer gameTimer;

    Clock spawnTimer;
    Clock damageTimer;
    Clock levelDisplayTimer;

    Font font;
    Text timerText;
    Text centerText;

    Music backgroundMusic;
    Music gameOverEffect;
    Music damageEffect;

    float vitesseActuelle;
    int lastLevel;
    bool showLevelMessage;

    void processEvents();
    void update();
    void render();

    void updateGameplay();
    void renderGameplay();
    void resetGame();

public:
    Game();
    void run();
};

#endif