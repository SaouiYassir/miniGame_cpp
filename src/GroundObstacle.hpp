#ifndef GROUNDOBSTACLE_HPP
#define GROUNDOBSTACLE_HPP

#include "Obstacle.hpp"

class GroundObstacle : public Obstacle {
private:
    static sf::Texture texture;
    static bool loaded;

public:
    GroundObstacle(float speed);
    bool getIsFlying() const override;
};

#endif