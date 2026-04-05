#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Timer {
private:
    sf::Clock clock;
    sf::Time elapsedTime;
    bool isRunning;

public:
    Timer();
    void update();
    void pause();
    void resume();
    void reset();

    sf::Time getElapsedTime() const { return elapsedTime; }
    std::string getTimeString() const;
};

#endif