#include "Game.hpp"

Game::Game() : windowWidth(1080), windowHeight(720), window(VideoMode(windowWidth, windowHeight), "SFML Game"), menu(windowWidth, windowHeight), gameTimer(), finalGameTime(0) {
    window.setFramerateLimit(60);
    state = MENU_STATE;

    srand(static_cast<unsigned>(time(nullptr)));

    vitesseActuelle = 6.5f;
    lastLevel = 1;
    showLevelMessage = false;

    font.loadFromFile("assets/fonts/font1.ttf");

    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(Color::White);
    timerText.setPosition(windowWidth - 200, 20);

    centerText.setFont(font);
    centerText.setCharacterSize(100);
    centerText.setStyle(Text::Bold);

    if (!backgroundMusic.openFromFile("assets/music/Bonkers-for-Arcades.ogg")) 
        cout << "Error loading background music" << endl;
    if (!gameOverEffect.openFromFile("assets/music/game-over.ogg")) 
        cout << "Error loading game over effect" << endl;
    if (!damageEffect.openFromFile("assets/music/damage.ogg")) 
        cout << "Error loading damage effect" << endl;

    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(40.f);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    Event event;

    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();

        if (event.type == Event::KeyPressed) {
            // Q to quit the entire game when paused
            if (state == PAUSED_STATE && event.key.code == Keyboard::Q) {
                window.close();
            }

            // M to go back to menu (from gameplay, paused, OR GAME OVER)
            if ((state == GAMEPLAY_STATE || state == PAUSED_STATE || state == GAME_OVER_STATE) && event.key.code == Keyboard::M) {
                state = MENU_STATE;
                backgroundMusic.stop();
                resetGame(); // Reset the game when going to menu
            }

            // R to resume when paused
            if (state == PAUSED_STATE && event.key.code == Keyboard::R) {
                togglePause();
            }
            
            // R to restart when game over
            if (state == GAME_OVER_STATE && event.key.code == Keyboard::R) {
                resetGame();
                state = GAMEPLAY_STATE;
                backgroundMusic.play();
            }

            // P to pause from gameplay
            if (state == GAMEPLAY_STATE && event.key.code == Keyboard::P) {
                togglePause();
            }

            // ESC: pause from gameplay, or back to menu from about/game over
            if (event.key.code == Keyboard::Escape) {
                if (state == GAMEPLAY_STATE) {
                    togglePause();
                } else if (state == ABOUT_STATE || state == GAME_OVER_STATE) {
                    state = MENU_STATE;
                    resetGame(); // Reset when going back to menu from game over
                }
            }
        }

        if (state == MENU_STATE) {
            int selection = menu.handleInput(window, event);
            if (selection == 1) {
                resetGame();
                state = GAMEPLAY_STATE;
            } else if (selection == 2) {
                state = ABOUT_STATE;
            }
        }
    }
}

void Game::togglePause() {
    if (state == GAMEPLAY_STATE) {
        state = PAUSED_STATE;
        backgroundMusic.pause();
        gameTimer.pause();
    } else if (state == PAUSED_STATE) {
        state = GAMEPLAY_STATE;
        backgroundMusic.play();
        gameTimer.resume();
        spawnTimer.restart();
    }
}

string formatTime(float seconds) {
    int minutes = static_cast<int>(seconds) / 60;
    int secs = static_cast<int>(seconds) % 60;
    stringstream ss;
    ss << setw(2) << setfill('0') << minutes << ":"
       << setw(2) << setfill('0') << secs;
    return ss.str();
}

void Game::update() {
    if (state == GAMEPLAY_STATE) {
        updateGameplay();
    }
}

void Game::updateGameplay() {    
    float secondes = gameTimer.getElapsedTime();
    
    timerText.setString(formatTime(secondes));

    int currentLevel = 1;

    if (secondes < 15.f) { 
        currentLevel = 1; 
        vitesseActuelle = 6.5f; 
    }
    else if (secondes < 30.f) { 
        currentLevel = 2; 
        vitesseActuelle = 10.5f; 
    }
    else { 
        currentLevel = 3; 
        vitesseActuelle = 15.0f; 
    }

    if (currentLevel > lastLevel) {
        showLevelMessage = true;
        levelDisplayTimer.restart();
        lastLevel = currentLevel;
    }

    level.setNiveau(currentLevel);

    if (!showLevelMessage) {
        if (spawnTimer.getElapsedTime().asSeconds() > 1.5f) {
            obstacles.push_back(Obstacle(rand() % 2 == 0, vitesseActuelle));
            spawnTimer.restart();
        }
    } else {
        spawnTimer.restart();
    }

    player.update();

    for (size_t i = 0; i < obstacles.size(); i++) {
        obstacles[i].update();

        FloatRect pBox = player.getBounds();
        FloatRect playerHitbox(pBox.left + pBox.width * 0.15f, pBox.top + pBox.height * 0.1f, pBox.width * 0.7f, pBox.height * 0.8f);

        FloatRect oBox = obstacles[i].getBounds();
        if (playerHitbox.intersects(oBox)) {
            if (damageTimer.getElapsedTime().asSeconds() > 1.0f) {
                hp.hit();
                damageEffect.play();
                damageTimer.restart();
                if (hp.getHealth() <= 0) {
                    state = GAME_OVER_STATE;
                    finalGameTime = gameTimer.getElapsedTime();
                    backgroundMusic.stop();
                    gameOverEffect.play();
                }
            }
        }

        if (obstacles[i].getBounds().left + obstacles[i].getBounds().width < 0) {
            obstacles.erase(obstacles.begin() + i);
            i--;
        }
    }

    if (showLevelMessage && levelDisplayTimer.getElapsedTime().asSeconds() > 2.0f) {
        showLevelMessage = false;
    }
}

void Game::render() {
    window.clear();

    if (state == MENU_STATE) {
        menu.update(window);
        menu.draw(window);
    } else if (state == ABOUT_STATE) {
        menu.drawAbout(window);
    } else if (state == GAMEPLAY_STATE || state == PAUSED_STATE) {
        renderGameplay();

        if (state == PAUSED_STATE) {
            RectangleShape dimmer(Vector2f(windowWidth, windowHeight));
            dimmer.setFillColor(Color(0, 0, 0, 180));
            window.draw(dimmer);

            centerText.setString(">  GAME PAUSED  <");
            centerText.setFillColor(Color(255, 255, 100));
            centerText.setCharacterSize(48);
            centerText.setStyle(Text::Bold);

            FloatRect bounds = centerText.getLocalBounds();
            centerText.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
            centerText.setPosition(windowWidth/2.f, windowHeight/2.f - 50);
            window.draw(centerText);

            Text subText;
            subText.setString("Press [ R ] to resume  |  [ Q ] to quit  |  [ M ] to go to Menu");
            subText.setFont(font);
            subText.setFillColor(Color(200, 200, 200, 200));
            subText.setCharacterSize(20);
            bounds = subText.getLocalBounds();
            subText.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
            subText.setPosition(windowWidth/2.f, windowHeight/2.f + 50);
            window.draw(subText);
        }
    } else if (state == GAME_OVER_STATE) {
        renderGameplay();
        RectangleShape dimmer(Vector2f(windowWidth, windowHeight));
        dimmer.setFillColor(Color(0, 0, 0, 200));
        window.draw(dimmer);
        
        centerText.setString("GAME OVER");
        centerText.setFillColor(Color::Red);
        centerText.setCharacterSize(72);
        FloatRect bounds = centerText.getLocalBounds();
        centerText.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
        centerText.setPosition(windowWidth/2.f, windowHeight/2.f - 80);
        window.draw(centerText);
        
        // Add restart instructions
        Text restartText;
        restartText.setString("Press [ R ] to Restart  |  [ M ] for Menu  |  [ ESC ] to Menu");
        restartText.setFont(font);
        restartText.setFillColor(Color(200, 200, 200));
        restartText.setCharacterSize(24);
        bounds = restartText.getLocalBounds();
        restartText.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
        restartText.setPosition(windowWidth/2.f, windowHeight/2.f + 20);
        window.draw(restartText);
        
        // Show final time - USE THE STORED TIME
        Text finalTimeText;
        finalTimeText.setString("Time survived: " + formatTime(finalGameTime));  // Changed to finalGameTime
        finalTimeText.setFont(font);
        finalTimeText.setFillColor(Color::Yellow);
        finalTimeText.setCharacterSize(28);
        bounds = finalTimeText.getLocalBounds();
        finalTimeText.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
        finalTimeText.setPosition(windowWidth/2.f, windowHeight/2.f + 70);
        window.draw(finalTimeText);
    }

    window.display();
}

void Game::renderGameplay() {
    level.draw(window);
    player.render(window);
    for (auto& o : obstacles) o.render(window);
    hp.draw(window);
    window.draw(timerText);

    if (showLevelMessage) {
        centerText.setString("Level " + to_string(lastLevel));
        centerText.setFillColor(Color::Cyan);
        FloatRect bounds = centerText.getLocalBounds();
        centerText.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
        centerText.setPosition(windowWidth/2.f, windowHeight/2.f);
        window.draw(centerText);
    }
}

void Game::resetGame() {
    obstacles.clear();
    spawnTimer.restart();
    gameTimer.reset();
    gameTimer.resume();
    hp.reset();
    level.setNiveau(1);
    lastLevel = 1;
    showLevelMessage = false;
    vitesseActuelle = 6.5f;
    damageTimer.restart(); 
    finalGameTime = 0;
    player.resetPosition();
}