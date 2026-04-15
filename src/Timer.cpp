#include "Timer.hpp"

Timer::Timer() {
    pausedTime = 0.0f;
    totalPausedDuration = 0.0f;
    isPaused = false;
    accumulatedTime = 0.0f;
}

void Timer::start() {
    clock.restart();
    isPaused = false;
    totalPausedDuration = 0.0f;
    accumulatedTime = 0.0f;
}

void Timer::pause() {
    if (!isPaused) {
        pausedTime = clock.getElapsedTime().asSeconds();
        isPaused = true;
    }
}

void Timer::resume() {
    if (isPaused) {
        float currentTime = clock.getElapsedTime().asSeconds();
        float pauseDuration = currentTime - pausedTime;
        totalPausedDuration += pauseDuration;
        isPaused = false;
    }
}

float Timer::getElapsedTime() {
    if (isPaused) {
        return pausedTime - totalPausedDuration;
    } else {
        return clock.getElapsedTime().asSeconds() - totalPausedDuration;
    }
}

void Timer::reset() {
    clock.restart();
    isPaused = false;
    totalPausedDuration = 0.0f;
    pausedTime = 0.0f;
}

bool Timer::getIsPaused() const {
    return isPaused;
}