#include "Timer.hpp"

Timer::Timer() : isRunning(false), elapsedTime(Time::Zero) {}

void Timer::update() {
    if (isRunning) {
        elapsedTime += clock.restart();
    } else {
        clock.restart();
    }
}

void Timer::pause() { isRunning = false; }
void Timer::resume() { isRunning = true; }
void Timer::reset() { elapsedTime = Time::Zero; clock.restart(); }

string Timer::getTimeString() const {
    int total = static_cast<int>(elapsedTime.asSeconds());
    int mins = total / 60;
    int secs = total % 60;
    stringstream ss;
    ss << setfill('0') << setw(2) << mins << ":" 
       << setfill('0') << setw(2) << secs;
    return ss.str();
}