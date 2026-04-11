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
    centerText.setCharacterSize(120);
    centerText.setStyle(Text::Bold);

    if (!backgroundMusic.openFromFile("assets/music/Bonkers-for-Arcades.ogg")) {
        std::cout << "Error loading about backgroung music" << std::endl;
    }

    if (!gameOverEffect.openFromFile("assets/music/game-over.ogg")) {
        std::cout << "Error loading about game over effect" << std::endl;
    }

    if (!damageEffect.openFromFile("assets/music/damage.ogg")) {
        std::cout << "Error loading about damage effect" << std::endl;
    }

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

        // --- Handle Game Over State ---
        if (state == GAME_OVER_STATE) {
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                state = MENU_STATE;
                // No need to reset here, we reset when selection == 1 in MENU_STATE
            }
            continue; // Skip other input processing while in Game Over
        }

        if (state == MENU_STATE) {
            int selection = menu.handleInput(window, event);
            if (selection == 1) {
                resetGame();
                state = GAMEPLAY_STATE;
            }
            else if (selection == 2) {
                state = ABOUT_STATE;
            }
        }
        // --- Handle Escape during Gameplay ---
        else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
            state = MENU_STATE;
            gameTimer.pause();
            backgroundMusic.stop();
        }
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

    // --- 1. Logique de Niveau ---
    if (secondes < 15.f) { currentLevel = 1; vitesseActuelle = 6.5f; }
    else if (secondes < 30.f) { currentLevel = 2; vitesseActuelle = 10.5f; }
    else { currentLevel = 3; vitesseActuelle = 15.0f; }

    if (currentLevel > lastLevel) {
        showLevelMessage = true;
        levelDisplayTimer.restart();
        lastLevel = currentLevel;
        
        // Optionnel : on peut vider les obstacles actuels pour nettoyer le terrain
        // obstacles.clear(); 
    }

    level.setNiveau(currentLevel);

    // --- 2. Logique de Spawn avec GAP ---
    // On n'autorise le spawn QUE si le message n'est pas affiché
    if (!showLevelMessage) {
        if (spawnTimer.getElapsedTime().asSeconds() > 1.5f) {
            obstacles.push_back(Obstacle(rand() % 2 == 0, vitesseActuelle));
            spawnTimer.restart();
        }
    } else {
        // IMPORTANT : On reset le timer de spawn pendant que le message s'affiche
        // Sinon, un obstacle apparaîtrait instantanément à la fin du message.
        spawnTimer.restart();
    }

    player.update();

    // --- 3. Update des obstacles existants ---
    for (size_t i = 0; i < obstacles.size(); i++) {
        // Optionnel : Si tu veux que les obstacles s'arrêtent pendant le message,
        // mets "if (!showLevelMessage)" ici aussi.
        obstacles[i].update();

        // On récupère la box d'origine du joueur
        FloatRect pBox = player.getBounds();
        // On réduit la largeur de 30% et la hauteur de 10% pour ignorer le vide
        float pShrinkX = pBox.width * 0.3f;
        float pShrinkY = pBox.height * 0.1f;
        FloatRect playerHitbox(pBox.left + pShrinkX / 2.f, pBox.top + pShrinkY, 
                               pBox.width - pShrinkX, pBox.height - pShrinkY);

        // On récupère la box d'origine de l'obstacle
        FloatRect oBox = obstacles[i].getBounds();
        // Pour l'araignée/monstre, on réduit la largeur de 40% (car les pattes sont très larges et fines)
        float oShrinkX = oBox.width * 0.4f;
        float oShrinkY = oBox.height * 0.2f;
        FloatRect obstacleHitbox(oBox.left + oShrinkX / 2.f, oBox.top + oShrinkY / 2.f, 
                                 oBox.width - oShrinkX, oBox.height - oShrinkY);

        // On teste l'intersection sur les hitboxes réduites
        if (playerHitbox.intersects(obstacleHitbox)) {
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

    // --- 4. Gestion de la fin du message ---
    // (Si tu ne le fais pas déjà dans render ou une autre fonction)
    if (showLevelMessage && levelDisplayTimer.getElapsedTime().asSeconds() > 2.0f) {
        showLevelMessage = false;
    }
}

void Game::render() {
    window.clear();

    if (state == MENU_STATE) {
        menu.update(window);
        menu.draw(window);
    }
    else if (state == ABOUT_STATE) {
        menu.drawAbout(window);
    }
    else if (state == GAMEPLAY_STATE) {
        renderGameplay();
    }
    else if (state == GAME_OVER_STATE) {
        // 1. Keep drawing the game elements so they are visible behind the overlay
        renderGameplay();

        // 2. Add a semi-transparent "Dimmer" to push the game into the background
        RectangleShape dimmer(Vector2f(windowWidth, windowHeight));
        dimmer.setFillColor(Color(0, 0, 0, 180)); // Black with 180/255 transparency
        window.draw(dimmer);

        // 3. Setup and draw Game Over Text
        centerText.setString("GAME OVER");
        centerText.setFillColor(Color::Red);
        centerText.setCharacterSize(100); // Slightly smaller to fit hints

        FloatRect bounds = centerText.getLocalBounds();
        centerText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        centerText.setPosition(windowWidth / 2.0f, windowHeight / 2.0f - 50);
        window.draw(centerText);

        // 4. Setup and draw Hint Text
        Text hintText("Press [ESC] to Return to Menu", font, 30);
        hintText.setFillColor(Color::White);
        
        FloatRect hBounds = hintText.getLocalBounds();
        hintText.setOrigin(hBounds.left + hBounds.width / 2.0f, hBounds.top + hBounds.height / 2.0f);
        hintText.setPosition(windowWidth / 2.0f, windowHeight / 2.0f + 60);
        window.draw(hintText);
    }

    window.display();
}

void Game::renderGameplay() {
    level.draw(window);
    player.render(window);

    for (auto& obstacle : obstacles)
        obstacle.render(window);

    hp.draw(window);
    window.draw(timerText);

    if (showLevelMessage) {
        centerText.setString("Level " + to_string(lastLevel));
        centerText.setFillColor(Color::Cyan);

        FloatRect bounds = centerText.getLocalBounds();
        centerText.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        centerText.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);

        window.draw(centerText);

        if (levelDisplayTimer.getElapsedTime().asSeconds() > 2.0f) {
            showLevelMessage = false;
        }
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