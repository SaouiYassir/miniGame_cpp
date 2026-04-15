#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace sf;

class Timer {
private:
    Clock clock;
    float pausedTime;
    float totalPausedDuration;
    bool isPaused;
    float accumulatedTime;

public:
    Timer();
    void start();
    void pause();
    void resume();
    float getElapsedTime();
    void reset();
    bool getIsPaused() const;
};

#endif