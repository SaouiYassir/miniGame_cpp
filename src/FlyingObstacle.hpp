#ifndef FLYINGOBSTACLE_HPP
#define FLYINGOBSTACLE_HPP

#include "Obstacle.hpp"


class FlyingObstacle : public Obstacle {
private:
    static Texture texture;
    static bool loaded;

public:
    FlyingObstacle(float speed);
    bool getIsFlying() const override;
};

#endif