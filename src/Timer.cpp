#include "Timer.hpp"
#include <sstream>
#include <iomanip>

Timer::Timer() : isRunning(false), elapsedTime(sf::Time::Zero) {}

void Timer::update() {
    if (isRunning) {
        elapsedTime += clock.restart();
    } else {
        clock.restart();
    }
}

void Timer::pause() { isRunning = false; }
void Timer::resume() { isRunning = true; }
void Timer::reset() { elapsedTime = sf::Time::Zero; clock.restart(); }

std::string Timer::getTimeString() const {
    int total = static_cast<int>(elapsedTime.asSeconds());
    int mins = total / 60;
    int secs = total % 60;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << mins << ":" 
       << std::setfill('0') << std::setw(2) << secs;
    return ss.str();
}