#pragma once

#include <vector>
#include <string>

#include "Components/Bullet.h"

/// @brief an infinite map object that manage the entity loaded on it
class Map {
public:
    Map();
    ~Map();

    void init();
    void update();
    void render();
    void destroy();

    void addBullet(const Vector2D& pos, const Orientation o);
    // remove oldest bullet
    void removeBullet();

private:
    std::vector<Bullet*> bullets;
};
