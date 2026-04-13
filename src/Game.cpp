#include "Game.hpp"
#include <ctime>

Game::Game() : windowWidth(1080), windowHeight(720), window(VideoMode(1080, 720), "SFML Game"), menu(windowWidth, windowHeight) {
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
            
            if (event.key.code == Keyboard::Escape || event.key.code == Keyboard::P) {
                if (state == GAMEPLAY_STATE || state == PAUSED_STATE) {
                    togglePause();
                } else if (state == ABOUT_STATE || state == GAME_OVER_STATE) {
                    state = MENU_STATE;
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

void Game::update() {
    if (state == GAMEPLAY_STATE) {
        updateGameplay();
    }
}

void Game::updateGameplay() {
    gameTimer.update();
    timerText.setString(gameTimer.getTimeString());

    float secondes = gameTimer.getElapsedTime().asSeconds();
    int currentLevel = 1;

    if (secondes < 15.f) { currentLevel = 1; vitesseActuelle = 6.5f; }
    else if (secondes < 30.f) { currentLevel = 2; vitesseActuelle = 10.5f; }
    else { currentLevel = 3; vitesseActuelle = 15.0f; }

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
        FloatRect playerHitbox(pBox.left + pBox.width * 0.15f, pBox.top + pBox.height * 0.1f, 
                               pBox.width * 0.7f, pBox.height * 0.8f);

        FloatRect oBox = obstacles[i].getBounds();
        if (playerHitbox.intersects(oBox)) {
            if (damageTimer.getElapsedTime().asSeconds() > 1.0f) {
                hp.hit();
                damageEffect.play();
                damageTimer.restart();
                if (hp.getHealth() <= 0) {
                    state = GAME_OVER_STATE;
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
            dimmer.setFillColor(Color(0, 0, 0, 150));
            window.draw(dimmer);

        
            centerText.setString("PAUSED");
            centerText.setFillColor(Color::Yellow);
            FloatRect bounds = centerText.getLocalBounds();
            centerText.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
            centerText.setPosition(windowWidth/2.f, windowHeight/2.f);
            window.draw(centerText);
        }
    } else if (state == GAME_OVER_STATE) {
        renderGameplay();
        RectangleShape dimmer(Vector2f(windowWidth, windowHeight));
        dimmer.setFillColor(Color(0, 0, 0, 200));
        window.draw(dimmer);

        centerText.setString("GAME OVER");
        centerText.setFillColor(Color::Red);
        FloatRect bounds = centerText.getLocalBounds();
        centerText.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
        centerText.setPosition(windowWidth/2.f, windowHeight/2.f - 50);
        window.draw(centerText);
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
    backgroundMusic.play();
}